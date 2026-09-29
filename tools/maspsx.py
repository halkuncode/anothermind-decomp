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


def _is_code_line(line: str) -> bool:
    s = line.strip()
    return bool(s) and not s.startswith("#") and not s.startswith("//") and not s.startswith(".loc")


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


def main():
    in_text = sys.stdin.read()
    lines = in_text.splitlines(keepends=True)
    lines = strip_dead_epilogue(lines)
    lines = epilogue_delay_slot_swap(lines)
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
        sys.stdout.write(proc.stdout)

    sys.exit(proc.returncode)


if __name__ == "__main__":
    main()
