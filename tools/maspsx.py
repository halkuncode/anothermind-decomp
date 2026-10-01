#!/usr/bin/env python3
"""Wrapper for maspsx that applies project-specific assembly cleanups
before passing to maspsx:
 - Prunes dead epilogues after infinite loops.
 - Performs the ASPSX epilogue delay-slot swap:

     cc1 emits (in reorder mode):        We transform to:
       lw  $31, N($sp)                     lw  $31, N($sp)
       addu $sp, $sp, M          →         nop
       j   $31                             .set noreorder
                                           j   $31
                                           addu $sp, $sp, M
                                           .set reorder

   The original ASPSX assembler moved the stack restore into the jump
   delay slot and inserted a nop in the lw load-delay slot.  maspsx
   does not replicate this reordering.  We do it here *before* handing
   off to maspsx.  The .set noreorder / .set reorder wrapper prevents
   maspsx from inserting its own "branch/jump" nop into the delay slot.
"""

import re
import subprocess
import sys
from pathlib import Path

MASPSX_SCRIPT = Path(__file__).resolve().parent / "maspsx" / "maspsx.py"

# Match addu/addiu $sp, $sp, <imm>  (cc1 uses addu; addiu also handled for safety)
_SP_RESTORE_RE = re.compile(r"^\s*(?:addu|addiu)\s+\$sp,\s*\$sp,\s*\S+")
_LW_RA_RE      = re.compile(r"^\s*lw\s+\$31,\s*\d+\(\$sp\)")
_J_RA_RE       = re.compile(r"^\s*j\s+\$31\s*$")
_LA_RE         = re.compile(r"^\s*la\s+(\$[a-z0-9]+),\s*([A-Za-z0-9_]+)")


def _is_code_line(line: str) -> bool:
    s = line.strip()
    if not s or s.startswith("#") or s.startswith("//") or s.startswith("/*"):
        return False
    if s.startswith("."):
        return False
    if s.endswith(":"):
        return False
    return True



def epilogue_delay_slot_swap(lines: list) -> list:
    """Detect the ASPSX epilogue pattern and reorder instructions so the
    stack-pointer restore ends up in the jump delay slot (matching the
    original ASPSX output), wrapped in .set noreorder so maspsx won't
    insert an extra nop there.
    """
    result = list(lines)
    n = len(result)
    i = 0
    while i < n:
        if not _is_code_line(result[i]) or not _LW_RA_RE.match(result[i].strip()):
            i += 1
            continue

        # Scan forward to the next code line after lw $31
        j = i + 1
        while j < n and not _is_code_line(result[j]):
            j += 1
        if j >= n or not _SP_RESTORE_RE.match(result[j].strip()):
            i += 1
            continue

        # Scan forward to the next code line after addu $sp
        k = j + 1
        while k < n and not _is_code_line(result[k]):
            k += 1
        if k >= n or not _J_RA_RE.match(result[k].strip()):
            i += 1
            continue

        # All three found: lw $31 at i, addu $sp at j, j $31 at k
        sp_restore = result[j]
        j_line     = result[k]
        indent = re.match(r"^(\s*)", j_line).group(1)

        nop_line       = indent + "nop\n"
        noreorder_line = indent + ".set\tnoreorder\n"
        reorder_line   = indent + ".set\treorder\n"

        before  = result[:j]        # up to (not including) addu $sp
        between = result[j + 1:k]   # lines between addu $sp and j $31 (.loc, blanks)
        after   = result[k + 1:]    # everything after j $31

        result = (before
                  + [nop_line]
                  + between
                  + [noreorder_line, j_line, sp_restore, reorder_line]
                  + after)
        n = len(result)
        i += 1  # keep scanning; don't re-examine swapped lines
    return result


_STORE_SYM_RE = re.compile(r"^\s*(sw|sh|sb)\s+(\$[a-z0-9]+),\s*([A-Za-z0-9_]+)\s*$")


def leaf_store_delay_slot_swap(lines: list) -> list:
    """When a leaf function stores to a symbol via `sw/sh/sb $reg, <sym>` followed by
    `j $31`, ASPSX splits the store and places the low half into the jump delay slot.
    We transform:
        sw   $reg, <sym>
        j    $31
    Into:
        .set noat
        lui  $1, %hi(<sym>)
        .set noreorder
        j    $31
        sw   $reg, %lo(<sym>)($1)
        .set reorder
        .set at
    """
    result = list(lines)
    n = len(result)
    i = 0
    while i < n:
        if not _is_code_line(result[i]):
            i += 1
            continue
        m = _STORE_SYM_RE.match(result[i].strip())
        if not m:
            i += 1
            continue
        op, reg, sym = m.group(1), m.group(2), m.group(3)
        j = i + 1
        while j < n and not _is_code_line(result[j]):
            j += 1
        if j < n and _J_RA_RE.match(result[j].strip()):
            j_line = result[j]
            indent = re.match(r"^(\s*)", j_line).group(1)
            lui_line       = f"{indent}.set\tnoat\n{indent}lui\t$1,%hi({sym})\n"
            noreorder_line = f"{indent}.set\tnoreorder\n"
            store_line     = f"{indent}{op}\t{reg},%lo({sym})($1)\n"
            reorder_line   = f"{indent}.set\treorder\n{indent}.set\tat\n"

            k = j + 1
            while k < n and not _is_code_line(result[k]):
                if result[k].strip().startswith("nop"):
                    break
                k += 1
            if k < n and result[k].strip().startswith("nop"):
                result = (result[:i]
                          + [lui_line]
                          + result[i + 1:j]
                          + [noreorder_line, j_line, store_line, reorder_line]
                          + result[j + 1:k]
                          + result[k + 1:])
            else:
                result = (result[:i]
                          + [lui_line]
                          + result[i + 1:j]
                          + [noreorder_line, j_line, store_line, reorder_line]
                          + result[j + 1:])
            n = len(result)
            i = j + 4
            continue
        i += 1
    return result



def leaf_la_delay_slot_swap(lines: list) -> list:
    """When a leaf function returns a symbol address via `la $reg, <sym>` followed by
    `j $31`, ASPSX splits `la` and places `addiu` into the jump delay slot.
    We transform:
        la   $reg, <sym>
        j    $31
    Into:
        lui  $reg, %hi(<sym>)
        .set noreorder
        j    $31
        addiu $reg, $reg, %lo(<sym>)
        .set reorder
    """
    result = list(lines)
    n = len(result)
    i = 0
    while i < n:
        if not _is_code_line(result[i]):
            i += 1
            continue
        m = _LA_RE.match(result[i].strip())
        if not m:
            i += 1
            continue
        reg, sym = m.group(1), m.group(2)
        j = i + 1
        while j < n and not _is_code_line(result[j]):
            j += 1
        if j < n and _J_RA_RE.match(result[j].strip()):
            j_line = result[j]
            indent = re.match(r"^(\s*)", j_line).group(1)
            lui_line       = f"{indent}lui\t{reg},%hi({sym})\n"
            noreorder_line = f"{indent}.set\tnoreorder\n"
            addiu_line     = f"{indent}addiu\t{reg},{reg},%lo({sym})\n"
            reorder_line   = f"{indent}.set\treorder\n"

            result = (result[:i]
                      + [lui_line]
                      + result[i + 1:j]
                      + [noreorder_line, j_line, addiu_line, reorder_line]
                      + result[j + 1:])
            n = len(result)
            i = j + 3
            continue
        i += 1
    return result


def strip_dead_epilogue(lines: list) -> list:
    clean_lines = []
    skip_to_end = False
    last_label = None

    for line in lines:
        stripped = line.strip()
        if stripped.endswith(":") and not stripped.startswith("."):
            last_label = stripped[:-1]
        elif last_label and stripped == f"j\t{last_label}":
            clean_lines.append(line)
            skip_to_end = True
            continue
        elif skip_to_end:
            if (
                stripped.startswith(".end\t")
                or stripped.startswith(".ent\t")
                or (stripped.endswith(":") and not stripped.startswith("LM"))
            ):
                skip_to_end = False
            else:
                continue
        clean_lines.append(line)

    return clean_lines


_GP_ACCESS_RE = re.compile(
    r"^(\s*(?:lw|sw|lh|lhu|sh|lb|lbu|sb)\s+\$[a-z0-9]+),\s*([A-Za-z0-9_]+)(\s*#.*)?$"
)


def load_gp_symbols() -> set[str]:
    gp_symbols = set()
    root = Path(__file__).resolve().parent.parent
    sym_file = root / "config" / "symbols.another.jp.txt"
    if sym_file.exists():
        with open(sym_file) as f:
            for line in f:
                line = line.strip()
                if "=" in line and ";" in line:
                    name, val = line.split("=")
                    name = name.strip()
                    val = val.replace(";", "").strip()
                    try:
                        addr = int(val, 16)
                        if 0x80061A1C <= addr <= 0x80062170:
                            gp_symbols.add(name)
                    except ValueError:
                        pass
    return gp_symbols


def is_gp_symbol(symbol: str, gp_symbols: set[str]) -> bool:
    if symbol in gp_symbols:
        return True
    if symbol.startswith("D_80061") or symbol.startswith("D_800620") or symbol.startswith("D_800621"):
        return True
    return False


def rewrite_gp_rel(text: str, gp_symbols: set[str]) -> str:
    lines = text.splitlines(keepends=True)
    new_lines = []
    for line in lines:
        m = _GP_ACCESS_RE.match(line)
        if m and is_gp_symbol(m.group(2), gp_symbols):
            comm = m.group(3) if m.group(3) else ""
            new_lines.append(f"{m.group(1)},%gp_rel({m.group(2)})($gp){comm}\n")
        else:
            new_lines.append(line)
    return "".join(new_lines)


_LW_SYM_RE  = re.compile(r"^\s*lw\s+(\$[a-z0-9]+),\s*([A-Za-z0-9_]+)\s*$")
_DEST_V0_RE = re.compile(r"^\s*(?:lw|lh|lhu|lb|lbu|li|move|addiu|addu|subu|and|or|xor|nor)\s+\$2\b")


def aspsx_load_symbol_scratch_swap(lines: list) -> list:
    """ASPSX uses $2 ($v0) as the scratch register for symbol loads `lw $reg, <sym>`
    when the following instruction immediately overwrites $2 (meaning $2 was dead).
    GNU as expands `lw $reg, <sym>` using $reg as the temp register instead.
    We transform:
        lw   $reg, <sym>
        <op> $2, ...
    Into:
        lui  $2, %hi(<sym>)
        lw   $reg, %lo(<sym>)($2)
        <op> $2, ...
    """
    result = list(lines)
    n = len(result)
    i = 0
    while i < n:
        if not _is_code_line(result[i]):
            i += 1
            continue
        m = _LW_SYM_RE.match(result[i].strip())
        if not m:
            i += 1
            continue
        reg, sym = m.group(1), m.group(2)
        if reg == "$2" or reg == "$v0":
            i += 1
            continue
        j = i + 1
        while j < n and not _is_code_line(result[j]):
            j += 1
        if j < n and _DEST_V0_RE.match(result[j].strip()):
            indent = re.match(r"^(\s*)", result[i]).group(1)
            lui_line = f"{indent}lui\t$2,%hi({sym})\n"
            lw_line  = f"{indent}lw\t{reg},%lo({sym})($2)\n"
            result = result[:i] + [lui_line, lw_line] + result[i + 1:]
            n = len(result)
            i += 2
            continue
        i += 1
    return result


def main():
    in_text = sys.stdin.read()
    lines = in_text.splitlines(keepends=True)
    lines = strip_dead_epilogue(lines)
    lines = epilogue_delay_slot_swap(lines)
    lines = leaf_la_delay_slot_swap(lines)
    lines = aspsx_load_symbol_scratch_swap(lines)
    filtered_text = "".join(lines)

    proc = subprocess.run(
        [sys.executable, str(MASPSX_SCRIPT)] + sys.argv[1:],
        input=filtered_text,
        text=True,
        capture_output=True,
    )

    if proc.stderr:
        sys.stderr.write(proc.stderr)
    if proc.stdout:
        gp_symbols = load_gp_symbols()
        out_text = rewrite_gp_rel(proc.stdout, gp_symbols)
        out_lines = leaf_store_delay_slot_swap(out_text.splitlines(keepends=True))
        sys.stdout.write("".join(out_lines))

    sys.exit(proc.returncode)



if __name__ == "__main__":
    main()
