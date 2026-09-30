#!/usr/bin/env python3
"""
Another Mind (PSX) - CD / ISO Builder
Rebuilds a playable PlayStation ISO (disk/another_build.iso) from:
  - Compiled executable: build/jp/another.exe
  - Assets: assets/jp/progdata/ (recompressing modified files into Ampack format)
  - Layout: Dynamically recalculates CDPOS.DAT and ISO9660 directory tables.
"""

import argparse
import math
import os
import struct
import sys
import time

GROUP_BOUNDS = [2, 0x44, 0x81, 0xA9, 0xDE, 0x1CD, 0x324, 0x7E7, 0xB12, 0xC31, 0xC32]

GROUP_NAMES = [
    "video",
    "system",
    "dictionary",
    "dialogue",
    "menus",
    "scripts",
    "backgrounds",
    "animations",
    "audio",
    "dummy",
]

EXTENSION_REVERSE_MAP = {
    ".TIM": ".TIZ",
    ".ANM": ".ANZ",
    ".ZZS": ".ZZZ",
}


def compress_lzss(data: bytes) -> bytes:
    """Okumura 1989 LZSS encoder with Ampack 6-byte header."""
    buf = bytearray(4096)
    r = 4078

    payload = bytearray()
    flags = 0
    flag_bit = 1
    code_buf = bytearray([0])

    src_len = len(data)
    src_idx = 0

    # Index table for faster 3-byte prefix matching
    lookup = {}

    while src_idx < src_len:
        max_look = min(18, src_len - src_idx)
        best_len = 0
        best_off = 0

        if max_look >= 3:
            first3 = (data[src_idx], data[src_idx + 1], data[src_idx + 2])
            candidates = lookup.get(first3, [])
            for off in candidates:
                match_len = 3
                while match_len < max_look and buf[(off + match_len) & 0xFFF] == data[src_idx + match_len]:
                    match_len += 1
                if match_len > best_len:
                    best_len = match_len
                    best_off = off
                    if best_len == 18:
                        break

        if best_len >= 3:
            code_buf.append(best_off & 0xFF)
            code_buf.append(((best_off >> 4) & 0xF0) | ((best_len - 3) & 0x0F))

            for k in range(best_len):
                c = data[src_idx + k]
                buf[r] = c
                if r >= 2:
                    p = (buf[(r - 2) & 0xFFF], buf[(r - 1) & 0xFFF], c)
                    lookup.setdefault(p, []).append((r - 2) & 0xFFF)
                r = (r + 1) & 0xFFF
            src_idx += best_len
        else:
            flags |= flag_bit
            c = data[src_idx]
            code_buf.append(c)
            buf[r] = c
            if r >= 2:
                p = (buf[(r - 2) & 0xFFF], buf[(r - 1) & 0xFFF], c)
                lookup.setdefault(p, []).append((r - 2) & 0xFFF)
            r = (r + 1) & 0xFFF
            src_idx += 1

        flag_bit <<= 1
        if flag_bit == 0x100:
            code_buf[0] = flags
            payload.extend(code_buf)
            flags = 0
            flag_bit = 1
            code_buf = bytearray([0])

    if len(code_buf) > 1:
        while flag_bit != 0x100:
            flags |= flag_bit
            flag_bit <<= 1
        code_buf[0] = flags
        payload.extend(code_buf)

    total_sz = len(payload) + 6
    header = bytearray([0xC3, 0xFF]) + bytearray(struct.pack("<I", total_sz))
    return bytes(header + payload)


def load_group_manifest(cdlookup_path: str):
    """Parses docs/cdlookup.md to obtain group structure and disc filenames."""
    groups = []
    current_group = []
    with open(cdlookup_path, "r") as f:
        for line in f:
            if line.startswith("## Group "):
                if current_group:
                    groups.append(current_group)
                    current_group = []
            elif line.startswith("|") and not line.startswith("| File ID") and not line.startswith("|---"):
                parts = [p.strip().strip("`") for p in line.split("|")[1:-1]]
                if len(parts) >= 5:
                    try:
                        fid = int(parts[0])
                        disc_name = parts[1]
                        extracted_name = parts[2]
                        sec = int(parts[3])
                        sz = int(parts[4])
                        current_group.append({
                            "fid": fid,
                            "disc_name": disc_name,
                            "extracted_name": extracted_name,
                            "orig_sec": sec,
                            "orig_sz": sz,
                        })
                    except ValueError:
                        continue
    if current_group:
        groups.append(current_group)
    return groups


def main():
    parser = argparse.ArgumentParser(description="Build PlayStation ISO for Another Mind")
    parser.add_argument("--exe", default="build/jp/another.exe", help="Path to compiled executable")
    parser.add_argument("--assets", default="assets/jp/progdata", help="Extracted assets directory")
    parser.add_argument("--base-iso", default="disk/Another Mind (Japan).iso", help="Original ISO for template")
    parser.add_argument("--progdata-orig", default="disk/jp/PROGDATA", help="Original compressed files directory (cache)")
    parser.add_argument("--output", default="disk/another_build.iso", help="Output ISO path")
    args = parser.parse_args()

    if not os.path.exists(args.exe):
        # Fallback to SLPS_016.55 if another.exe not built
        fallback_exe = "disk/jp/SLPS_016.55"
        if os.path.exists(fallback_exe):
            print(f"Notice: '{args.exe}' not found, using '{fallback_exe}'")
            exe_path = fallback_exe
        else:
            print(f"Error: Executable not found at {args.exe}")
            sys.exit(1)
    else:
        exe_path = args.exe

    if not os.path.exists(args.assets):
        print(f"Error: Assets directory not found at {args.assets}. Run 'make assets' first.")
        sys.exit(1)

    if not os.path.exists(args.base_iso):
        print(f"Error: Base ISO not found at {args.base_iso}")
        sys.exit(1)

    cdlookup_path = os.path.join(os.path.dirname(__file__), "..", "docs", "cdlookup.md")
    if not os.path.exists(cdlookup_path):
        print(f"Error: {cdlookup_path} not found.")
        sys.exit(1)

    print("Loading CD layout manifest...")
    groups = load_group_manifest(cdlookup_path)
    total_files = sum(len(g) for g in groups)
    print(f"Found {len(groups)} groups with {total_files} total files.")

    # Read base ISO lead-in (sectors 0 to 713 = 1,462,272 bytes)
    print("Reading base ISO system lead-in...")
    with open(args.base_iso, "rb") as f_iso:
        lead_in = bytearray(f_iso.read(714 * 2048))

    # Read base PROGDATA directory sector table (sectors 621 to 713 = 93 sectors = 190,464 bytes)
    pdir_offset = 621 * 2048
    pdir_len = 93 * 2048
    progdata_dirtable = bytearray(lead_in[pdir_offset : pdir_offset + pdir_len])

    # Index directory record locations in progdata_dirtable by filename
    name_to_rec_offset = {}
    idx = 0
    while idx < len(progdata_dirtable):
        rlen = progdata_dirtable[idx]
        if rlen == 0:
            idx = ((idx // 2048) + 1) * 2048
            continue
        nlen = progdata_dirtable[idx + 32]
        fname = progdata_dirtable[idx + 33 : idx + 33 + nlen].decode("ascii", errors="replace").split(";")[0]
        if fname and fname not in (".", "\x01"):
            name_to_rec_offset[fname] = idx
        idx += rlen

    print(f"Indexed {len(name_to_rec_offset)} directory records in PROGDATA table.")

    # Prepare executable bytes
    with open(exe_path, "rb") as f_exe:
        exe_bytes = f_exe.read()
    exe_sectors = math.ceil(len(exe_bytes) / 2048)
    if exe_sectors > 584:
        print(f"Warning: Executable size ({len(exe_bytes)}) exceeds 584 sectors!")

    # Write executable into lead-in at Sector 37
    exe_lead_offset = 37 * 2048
    lead_in[exe_lead_offset : exe_lead_offset + len(exe_bytes)] = exe_bytes

    # New CDPOS table entries: 3,122 entries of 8 bytes (<II)
    new_cdpos = bytearray(3122 * 8)
    # Entry 0: SYSTEM.CNF (Sector 36, size 68)
    struct.pack_into("<II", new_cdpos, 0, 36, 68)
    # Entry 1: SLPS_016.55 (Sector 37, size len(exe_bytes))
    struct.pack_into("<II", new_cdpos, 8, 37, len(exe_bytes))

    # Output file setup
    os.makedirs(os.path.dirname(os.path.abspath(args.output)), exist_ok=True)
    f_out = open(args.output, "wb")
    # Reserve space for lead-in (we will seek back and write it after updating CDPOS & dir tables)
    f_out.write(lead_in)

    current_lba = 714
    recompressed_count = 0
    cached_count = 0

    # Load extracted manifest for change detection
    manifest_path = os.path.join(args.assets, ".extracted_manifest.json")
    extracted_manifest = {}
    if os.path.exists(manifest_path):
        import json
        with open(manifest_path, "r") as fp:
            extracted_manifest = json.load(fp)

    t0 = time.time()
    print(f"Packing assets starting at Sector {current_lba}...")

    entry_idx = 2
    for g, group_files in enumerate(groups):
        folder = GROUP_NAMES[g]
        group_dir = os.path.join(args.assets, folder)

        for item in group_files:
            disc_name = item["disc_name"]
            extracted_name = item["extracted_name"]
            src_asset_path = os.path.join(group_dir, extracted_name)
            if not os.path.exists(src_asset_path):
                import glob
                matches = glob.glob(os.path.join(group_dir, "**", os.path.basename(extracted_name)), recursive=True)
                if matches:
                    src_asset_path = matches[0]

            is_compressed_type = disc_name.endswith((".TIZ", ".ANZ", ".ZZZ", ".BIZ"))

            # Change detection
            rel_asset = os.path.relpath(src_asset_path, args.assets)
            cached_meta = extracted_manifest.get(rel_asset)
            is_modified = False
            if os.path.exists(src_asset_path):
                cur_stat = os.stat(src_asset_path)
                if cached_meta:
                    if cur_stat.st_size != cached_meta.get("size") or cur_stat.st_mtime != cached_meta.get("mtime"):
                        is_modified = True
            
            cache_file = os.path.join(args.progdata_orig, disc_name)
            pack_bytes = None

            if is_compressed_type:
                if not is_modified and os.path.exists(cache_file):
                    pack_bytes = open(cache_file, "rb").read()
                    cached_count += 1
                else:
                    with open(src_asset_path, "rb") as f_raw:
                        raw_data = f_raw.read()
                    pack_bytes = compress_lzss(raw_data)
                    recompressed_count += 1
            else:
                if os.path.exists(src_asset_path):
                    with open(src_asset_path, "rb") as f_raw:
                        pack_bytes = f_raw.read()
                elif os.path.exists(cache_file):
                    with open(cache_file, "rb") as f_raw:
                        pack_bytes = f_raw.read()
                else:
                    print(f"Error: Missing asset file {src_asset_path}")
                    sys.exit(1)
                cached_count += 1

            file_size = len(pack_bytes)
            num_sectors = math.ceil(file_size / 2048)

            # CDPOS records:
            # - Sector is LBA + 1
            # - Size for Group 0 STR files is XA payload size: num_sectors * 2336
            # - Size for all other groups is actual file_size
            cdpos_sec = current_lba + 1
            if g == 0 and disc_name.endswith(".STR"):
                cdpos_sz = num_sectors * 2336
            else:
                cdpos_sz = file_size

            struct.pack_into("<II", new_cdpos, entry_idx * 8, cdpos_sec, cdpos_sz)
            entry_idx += 1

            # Update ISO9660 directory record in progdata_dirtable
            rec_off = name_to_rec_offset.get(disc_name)
            if rec_off is not None:
                # Offset 2: Little-endian LBA
                # Offset 6: Big-endian LBA
                # Offset 10: Little-endian Data length
                # Offset 14: Big-endian Data length
                iso_data_len = num_sectors * 2048
                struct.pack_into("<I", progdata_dirtable, rec_off + 2, current_lba)
                struct.pack_into(">I", progdata_dirtable, rec_off + 6, current_lba)
                struct.pack_into("<I", progdata_dirtable, rec_off + 10, iso_data_len)
                struct.pack_into(">I", progdata_dirtable, rec_off + 14, iso_data_len)

            # Write file bytes and pad to 2048-byte sector boundary
            f_out.write(pack_bytes)
            pad_len = (num_sectors * 2048) - file_size
            if pad_len > 0:
                f_out.write(b"\x00" * pad_len)

            current_lba += num_sectors

    # Write 150-sector CD-ROM post-gap (standard run-out padding)
    postgap_sectors = 150
    f_out.write(b"\x00" * (postgap_sectors * 2048))
    total_disc_sectors = current_lba + postgap_sectors
    print(f"Wrote all assets with {postgap_sectors}-sector post-gap. Total disc sectors: {total_disc_sectors} ({total_disc_sectors * 2048 / 1024 / 1024:.2f} MB)")

    # Update VolumeSpaceSize in Primary Volume Descriptor (PVD, Sector 16)
    pvd_offset = 16 * 2048
    struct.pack_into("<I", lead_in, pvd_offset + 80, total_disc_sectors)
    struct.pack_into(">I", lead_in, pvd_offset + 84, total_disc_sectors)

    # Put updated CDPOS.DAT into lead-in at Sector 23 (size 24,976)
    cdpos_offset = 23 * 2048
    lead_in[cdpos_offset : cdpos_offset + len(new_cdpos)] = new_cdpos

    # Put updated PROGDATA directory table back into lead-in at Sector 621
    lead_in[pdir_offset : pdir_offset + pdir_len] = progdata_dirtable

    # Rewind and write updated lead-in to output file
    f_out.seek(0)
    f_out.write(lead_in)
    f_out.close()

    t1 = time.time()
    print(f"\nSuccessfully built '{args.output}' in {t1 - t0:.2f}s!")
    print(f"  - Cached/Unchanged files: {cached_count}")
    print(f"  - Recompressed files: {recompressed_count}")
    print(f"  - Output ISO size: {os.path.getsize(args.output)} bytes ({os.path.getsize(args.output) // 2048} sectors)")


if __name__ == "__main__":
    main()
