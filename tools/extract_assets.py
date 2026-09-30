#!/usr/bin/env python3
"""
Another Mind (PSX) - Asset Extractor & Decompressor
Extracts and decompresses game assets from disk/jp/PROGDATA/ into assets/jp/progdata/
organized by CDPOS.DAT groups.
"""

import argparse
import os
import re
import struct
import sys
import time
from concurrent.futures import ProcessPoolExecutor

# CDPOS boundary offsets from executable symbol D_8004B440
GROUP_BOUNDS = [2, 0x44, 0x81, 0xA9, 0xDE, 0x1CD, 0x324, 0x7E7, 0xB12, 0xC31, 0xC32]

GROUP_NAMES = [
    "video",        # Group 00: FMV video streams (.STR)
    "system",       # Group 01: Core UI, fonts, chapter cards, vibration
    "dictionary",   # Group 02: Kanji conversion dictionaries (.DCT, etc.)
    "dialogue",     # Group 03: Dialogue window chrome, text glyphs
    "menus",        # Group 04: Subsystem menus, scenario data (.BIZ)
    "scripts",      # Group 05: Scenario scripts / VM bytecode (.ZZZ -> .ZZS)
    "backgrounds",  # Group 06: Background graphics (.TIZ -> .TIM)
    "animations",   # Group 07: Character portrait animations (.ANZ -> .ANM)
    "audio",        # Group 08: Sound effects, sample banks, music (.DAT, .SNG)
    "dummy",        # Group 09: Disc dummy/padding
]

EXTENSION_MAP = {
    ".TIZ": ".TIM",
    ".ANZ": ".ANM",
    ".ZZZ": ".ZZS",
    ".BIZ": ".BIN",
}


def decompress_lzss(data: bytes) -> bytes:
    """
    Decompresses Ampack/LZSS data matching the in-game DecompressLZSS function.
    Header format (6 bytes):
      - Bytes 0..1: Magic 0xC3, 0xFF (0xFFC3 little-endian)
      - Bytes 2..5: Total compressed file size (uint32 LE)
      - Bytes 6.. : Raw LZSS compressed byte stream
    """
    if len(data) < 6 or data[0] != 0xC3 or data[1] != 0xFF:
        return data

    total_sz = struct.unpack_from("<I", data, 2)[0]
    payload = data[6:total_sz]

    buf = bytearray(4096)
    r = 4078  # 0xFEE initial ring buffer write position
    out = bytearray()

    p_len = len(payload)
    src_idx = 0
    flags = 0

    while src_idx < p_len:
        flags >>= 1
        if (flags & 0x100) == 0:
            if src_idx >= p_len:
                break
            flags = payload[src_idx] | 0xFF00
            src_idx += 1

        if flags & 1:
            if src_idx >= p_len:
                break
            c = payload[src_idx]
            src_idx += 1
            out.append(c)
            buf[r] = c
            r = (r + 1) & 0xFFF
        else:
            if src_idx + 1 >= p_len:
                break
            b0 = payload[src_idx]
            b1 = payload[src_idx + 1]
            src_idx += 2

            offset = b0 | ((b1 & 0xF0) << 4)
            length = (b1 & 0x0F) + 2

            for k in range(length + 1):
                c = buf[(offset + k) & 0xFFF]
                out.append(c)
                buf[r] = c
                r = (r + 1) & 0xFFF

    return bytes(out)


def get_decompressed_filename(filename: str) -> str:
    name, ext = os.path.splitext(filename)
    new_ext = EXTENSION_MAP.get(ext.upper(), ext)
    return name + new_ext


def parse_iso_directory(iso_path: str) -> dict:
    """Parses ISO9660 directory records in PROGDATA to map LBA -> filename."""
    if not os.path.exists(iso_path):
        return {}

    with open(iso_path, "rb") as f:
        # Read Primary Volume Descriptor at sector 16
        f.seek(16 * 2048)
        pvd = f.read(2048)
        if pvd[1:6] != b"CD001":
            return {}

        root_record = pvd[156 : 156 + 34]
        root_lba = struct.unpack_from("<I", root_record, 2)[0]
        root_len = struct.unpack_from("<I", root_record, 10)[0]

        f.seek(root_lba * 2048)
        root_dir = f.read(root_len)
        idx = 0
        progdata_lba = 0
        progdata_len = 0
        while idx < len(root_dir):
            rec_len = root_dir[idx]
            if rec_len == 0:
                idx = ((idx // 2048) + 1) * 2048
                continue
            lba = struct.unpack_from("<I", root_dir, idx + 2)[0]
            sz = struct.unpack_from("<I", root_dir, idx + 10)[0]
            nlen = root_dir[idx + 32]
            name = root_dir[idx + 33 : idx + 33 + nlen].decode("ascii", errors="replace")
            if "PROGDATA" in name:
                progdata_lba = lba
                progdata_len = sz
                break
            idx += rec_len

        if not progdata_lba:
            return {}

        f.seek(progdata_lba * 2048)
        pdir = f.read(progdata_len)
        pidx = 0
        iso_by_lba = {}
        while pidx < len(pdir):
            rlen = pdir[pidx]
            if rlen == 0:
                pidx = ((pidx // 2048) + 1) * 2048
                continue
            flba = struct.unpack_from("<I", pdir, pidx + 2)[0]
            nlen = pdir[pidx + 32]
            fname = pdir[pidx + 33 : pidx + 33 + nlen].decode("ascii", errors="replace").split(";")[0]
            if fname and fname not in (".", "\x01"):
                iso_by_lba[flba] = fname
            pidx += rlen

        return iso_by_lba


def parse_cdlookup_fallback() -> dict:
    """Fallback filename lookup from docs/cdlookup.md if ISO is missing."""
    lookup_file = os.path.join(os.path.dirname(__file__), "..", "docs", "cdlookup.md")
    if not os.path.exists(lookup_file):
        return {}

    mapping = {}
    with open(lookup_file, "r") as f:
        for line in f:
            if line.startswith("|") and not line.startswith("| File ID") and not line.startswith("|---"):
                parts = [p.strip().strip("`") for p in line.split("|")[1:-1]]
                if len(parts) >= 4:
                    try:
                        fid = int(parts[0])
                        disc_name = parts[1]
                        sec = int(parts[3])
                        mapping[sec - 1] = disc_name
                    except ValueError:
                        continue
    return mapping


def extract_zzs_author(data: bytes) -> str:
    """
    Extracts author name from script bytecode.
    Squaresoft Another Mind script compiler puts opcode 0x29 (Cmd_aurthor)
    followed by an 8-byte ASCII author string at the start of the script bytecode.
    """
    if len(data) >= 10:
        labels = struct.unpack(">H", data[8:10])[0]
        start = 10 + labels * 2
        for i in range(start, min(len(data) - 8, start + 128)):
            if data[i] == 0x29:
                chunk = data[i+1 : i+9].rstrip(b"\x00").rstrip(b" ")
                if len(chunk) >= 3 and all(b in b"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_-" for b in chunk):
                    return chunk.decode("ascii")

    for i in range(len(data) - 8):
        if data[i] == 0x29:
            chunk = data[i+1 : i+9].rstrip(b"\x00").rstrip(b" ")
            if len(chunk) >= 3 and all(b in b"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_-" for b in chunk):
                return chunk.decode("ascii")

    return None


def get_background_subfolder(fname: str) -> str:
    """Categorizes background TIM image into chapter subfolders."""
    base = os.path.splitext(fname)[0]
    if base.startswith("TA2049"):
        return "chapter_02"
    m = re.match(r"^M(\d{2})_\d+", base)
    if m:
        return f"chapter_{int(m.group(1)):02d}"
    if base.startswith("M4S2_") or base.startswith("S4_"):
        return "chapter_04"
    m = re.search(r"(\d{4,5})", base)
    if m:
        num = int(m.group(1))
        chap = num // 1000
        if chap > 0:
            return f"chapter_{chap:02d}"
    return "chapter_00_common"


ANIM_CHAR_NAMES = {
    "H": "hitomi",
    "HN": "hitomi_night",
    "M": "masato",
    "MY": "mayumi",
    "S": "shun",
    "N": "nurse",
    "NA": "nanami",
    "KR": "kurata",
    "RI": "ritsuko",
    "RE": "reiko",
    "AR": "arai",
    "AK": "akane",
    "KN": "kaneko",
    "HI": "hitoshi",
    "KI": "kitani",
    "Y": "yoshida",
    "SM": "shimada",
    "SH": "sahara",
    "KB": "kiba",
    "MD": "mukai",
    "HH": "hiura",
    "OK": "okada",
    "KA": "kazuo",
    "BRI": "bri",
    "NJ": "nj",
    "KG": "kg",
    "NN": "nn",
    "RK": "rk",
    "RY": "ry",
    "ST": "st",
    "JU": "ju",
    "OS": "os",
    "BL": "bl",
    "KAN": "kan",
    "SK": "sk",
    "U": "u",
    "YK": "yk",
    "B": "b",
    "BN": "bn",
    "CA": "ca",
    "IS": "is",
    "P": "p",
    "SUE": "sue",
    "WA": "wa",
    "KE": "ke",
    "common": "common",
}


def get_animation_subfolder(fname: str) -> str:
    """Categorizes animation ANM/TIM files into character subfolders named by character."""
    base = os.path.splitext(fname)[0]
    if base in ("NOISE", "NULL"):
        code = "common"
    elif base.startswith("R_MY"):
        code = "MY"
    else:
        m = re.match(r"^([A-Za-z]+)", base)
        code = m.group(1).upper() if m else "common"
    return ANIM_CHAR_NAMES.get(code, code.lower())


def get_audio_subfolder(fname: str) -> str:
    """Categorizes audio files into effect, music, and wave subfolders."""
    base = os.path.basename(fname).upper()
    if base.startswith("EFFECT"):
        return "effect"
    elif base.startswith("MUSIC") or base.startswith("SONG"):
        return "music"
    elif base.startswith("WAVE"):
        return "wave"
    return ""


def get_menu_subfolder(fname: str) -> str:
    """Categorizes menu subsystem assets into functional subfolders."""
    base = os.path.basename(fname).upper()
    if base.startswith("SROLL"):
        return "credits"
    elif base.startswith("NEWS") or base.startswith("D"):
        return "news"
    elif base.startswith("MB_"):
        return "memory_card"
    elif base.startswith("WEEK") or base == "SYODATA.BIN":
        return "schedule"
    elif base.startswith("T_") or base == "RING.TIM":
        return "terminal"
    return "investigation"


def process_file_task(task_args):
    src_path, dst_path, is_compressed = task_args
    try:
        with open(src_path, "rb") as f:
            raw = f.read()

        if is_compressed:
            out_bytes = decompress_lzss(raw)
        else:
            out_bytes = raw

        # Check if ZZS script has an author header
        if dst_path.endswith(".ZZS"):
            author = extract_zzs_author(out_bytes)
            if author:
                dst_path = os.path.join(os.path.dirname(dst_path), author, os.path.basename(dst_path))
        elif dst_path.endswith(".TIM") and "backgrounds" in dst_path:
            sub = get_background_subfolder(os.path.basename(dst_path))
            dst_path = os.path.join(os.path.dirname(dst_path), sub, os.path.basename(dst_path))
        elif (dst_path.endswith(".ANM") or dst_path.endswith(".TIM")) and "animations" in dst_path:
            sub = get_animation_subfolder(os.path.basename(dst_path))
            dst_path = os.path.join(os.path.dirname(dst_path), sub, os.path.basename(dst_path))
        elif "audio" in dst_path:
            sub = get_audio_subfolder(os.path.basename(dst_path))
            if sub:
                dst_path = os.path.join(os.path.dirname(dst_path), sub, os.path.basename(dst_path))
        elif "menus" in dst_path:
            sub = get_menu_subfolder(os.path.basename(dst_path))
            dst_path = os.path.join(os.path.dirname(dst_path), sub, os.path.basename(dst_path))

        os.makedirs(os.path.dirname(dst_path), exist_ok=True)
        with open(dst_path, "wb") as f:
            f.write(out_bytes)
        st = os.stat(dst_path)
        return True, dst_path, st.st_size, st.st_mtime
    except Exception as e:
        return False, src_path, 0, str(e)


def main():
    parser = argparse.ArgumentParser(description="Another Mind asset extractor & decompressor")
    parser.add_argument("--disk-dir", default="disk/jp", help="Path to extracted disc directory")
    parser.add_argument("--iso", default="disk/Another Mind (Japan).iso", help="Path to ISO image")
    parser.add_argument("--out-dir", default="assets/jp/progdata", help="Output directory for assets")
    args = parser.parse_args()

    progdata_dir = os.path.join(args.disk_dir, "PROGDATA")
    cdpos_path = os.path.join(args.disk_dir, "CDPOS.DAT")

    if not os.path.exists(progdata_dir) or not os.path.exists(cdpos_path):
        print(f"Error: {progdata_dir} or {cdpos_path} not found. Run 'make disk' first.")
        sys.exit(1)

    print("Resolving disc file layout...")
    iso_by_lba = parse_iso_directory(args.iso)
    if not iso_by_lba:
        print("Note: ISO not found or unreadable; using docs/cdlookup.md fallback table.")
        iso_by_lba = parse_cdlookup_fallback()

    with open(cdpos_path, "rb") as f:
        cdpos_data = f.read()

    tasks = []
    group_counts = [0] * len(GROUP_NAMES)

    for g, folder in enumerate(GROUP_NAMES):
        start = GROUP_BOUNDS[g]
        end = GROUP_BOUNDS[g + 1]
        out_subfolder = os.path.join(args.out_dir, folder)

        for entry_idx in range(start, end):
            sec, sz = struct.unpack_from("<II", cdpos_data, entry_idx * 8)
            iso_sec = sec - 1
            fname = iso_by_lba.get(iso_sec)

            if not fname:
                print(f"Warning: Could not find filename for sector {sec} in group {folder}")
                continue

            src_file = os.path.join(progdata_dir, fname)
            if not os.path.exists(src_file):
                print(f"Warning: File {src_file} does not exist!")
                continue

            dst_name = get_decompressed_filename(fname)
            dst_file = os.path.join(out_subfolder, dst_name)

            _, ext = os.path.splitext(fname)
            is_comp = ext.upper() in EXTENSION_MAP

            tasks.append((src_file, dst_file, is_comp))
            group_counts[g] += 1

    # Clean up any loose scripts, backgrounds, animations, audio, or menus before extraction
    for clean_folder in ["scripts", "backgrounds", "animations", "audio", "menus"]:
        d = os.path.join(args.out_dir, clean_folder)
        if os.path.exists(d):
            import shutil
            shutil.rmtree(d)

    scripts_dir = os.path.join(args.out_dir, "scripts")
    bg_dir = os.path.join(args.out_dir, "backgrounds")
    anim_dir = os.path.join(args.out_dir, "animations")
    audio_dir = os.path.join(args.out_dir, "audio")
    menus_dir = os.path.join(args.out_dir, "menus")

    print(f"Extracting {len(tasks)} files into '{args.out_dir}' across {os.cpu_count() or 4} cores...")
    t0 = time.time()

    with ProcessPoolExecutor() as executor:
        results = list(executor.map(process_file_task, tasks))

    t1 = time.time()

    manifest = {}
    errors = []
    for ok, dst_or_src, sz, mtime_or_err in results:
        if ok:
            rel = os.path.relpath(dst_or_src, args.out_dir)
            manifest[rel] = {"size": sz, "mtime": mtime_or_err}
        else:
            errors.append(f"Error processing {dst_or_src}: {mtime_or_err}")

    if errors:
        for err in errors[:10]:
            print(err)
        print(f"Encountered {len(errors)} errors during extraction.")
        sys.exit(1)

    import json
    with open(os.path.join(args.out_dir, ".extracted_manifest.json"), "w") as fp:
        json.dump(manifest, fp)

    print(f"\nSuccessfully extracted and decompressed {len(tasks)} assets in {t1 - t0:.2f}s:")
    for g, folder in enumerate(GROUP_NAMES):
        print(f"  - {args.out_dir}/{folder}/: {group_counts[g]} files")

    # Report menu breakdown
    if os.path.exists(menus_dir):
        menu_subdirs = [d for d in os.listdir(menus_dir) if os.path.isdir(os.path.join(menus_dir, d))]
        loose_menu = [f for f in os.listdir(menus_dir) if os.path.isfile(os.path.join(menus_dir, f))]
        print(f"\nMenus organized into categories ({len(menu_subdirs)} subfolders):")
        for md in sorted(menu_subdirs):
            count = len(os.listdir(os.path.join(menus_dir, md)))
            print(f"  - menus/{md}/: {count} files")
        if loose_menu:
            print(f"  - menus/ (root): {len(loose_menu)} files")

    # Report script author breakdown
    if os.path.exists(scripts_dir):
        author_dirs = [d for d in os.listdir(scripts_dir) if os.path.isdir(os.path.join(scripts_dir, d))]
        loose_files = [f for f in os.listdir(scripts_dir) if os.path.isfile(os.path.join(scripts_dir, f))]
        print(f"\nScripts organized by author ({len(author_dirs)} author folders):")
        for ad in sorted(author_dirs):
            count = len(os.listdir(os.path.join(scripts_dir, ad)))
            print(f"  - scripts/{ad}/: {count} files")
        if loose_files:
            print(f"  - scripts/ (root): {len(loose_files)} files")

    # Report background chapter breakdown
    if os.path.exists(bg_dir):
        chap_dirs = [d for d in os.listdir(bg_dir) if os.path.isdir(os.path.join(bg_dir, d))]
        loose_bg = [f for f in os.listdir(bg_dir) if os.path.isfile(os.path.join(bg_dir, f))]
        print(f"\nBackgrounds organized by chapter ({len(chap_dirs)} chapter folders):")
        for cd in sorted(chap_dirs):
            count = len(os.listdir(os.path.join(bg_dir, cd)))
            print(f"  - backgrounds/{cd}/: {count} files")
        if loose_bg:
            print(f"  - backgrounds/ (root): {len(loose_bg)} files")

    # Report animation character breakdown
    if os.path.exists(anim_dir):
        char_dirs = [d for d in os.listdir(anim_dir) if os.path.isdir(os.path.join(anim_dir, d))]
        loose_anim = [f for f in os.listdir(anim_dir) if os.path.isfile(os.path.join(anim_dir, f))]
        print(f"\nAnimations organized by character ({len(char_dirs)} character folders):")
        for cd in sorted(char_dirs):
            count = len(os.listdir(os.path.join(anim_dir, cd)))
            print(f"  - animations/{cd}/: {count} files")
        if loose_anim:
            print(f"  - animations/ (root): {len(loose_anim)} files")

    # Report audio breakdown
    if os.path.exists(audio_dir):
        audio_subdirs = [d for d in os.listdir(audio_dir) if os.path.isdir(os.path.join(audio_dir, d))]
        loose_audio = [f for f in os.listdir(audio_dir) if os.path.isfile(os.path.join(audio_dir, f))]
        print(f"\nAudio organized into categories ({len(audio_subdirs)} subfolders):")
        for sd in sorted(audio_subdirs):
            count = len(os.listdir(os.path.join(audio_dir, sd)))
            print(f"  - audio/{sd}/: {count} files")
        if loose_audio:
            print(f"  - audio/ (root): {len(loose_audio)} files")


if __name__ == "__main__":
    main()
