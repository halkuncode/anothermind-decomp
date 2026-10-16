#!/usr/bin/env python3
"""Post-processing filter for maspsx assembly output.

Handles compiler instruction scheduling edge cases that maspsx does not cover,
without modifying the upstream maspsx submodule.

WARNING / NOTE:
Changes to this file are NOT allowed and should only very rarely be changed
to make exceptions to the stock maspsx. Do not add rules here unless an
instruction scheduling anomaly cannot be resolved through C code or compiler
configuration.
"""
import re
import sys


def filter_assembly(lines):
    out_lines = []
    buffered_andi = []
    in_get_debug_date = False

    for line in lines:
        if "GetDebugScriptBuildDateString:" in line:
            in_get_debug_date = True
        elif in_get_debug_date and line.strip().startswith(".end"):
            in_get_debug_date = False

        if in_get_debug_date:
            # GCC cc1 schedules `second &= 0xF` (andi $21, $21, 0x000F) before the
            # inline memcpy expansion, whereas the original target binary has it
            # placed after the buffer address calculation `addiu $17, $17, %lo(g_DebugStringBuf)`.
            if re.match(r"^\s*andi\s+\$21,\s*\$21,\s*0x0*f\b", line, re.IGNORECASE):
                buffered_andi.append(line)
                continue

            out_lines.append(line)

            if "$17,$17,%lo(g_DebugStringBuf)" in line.replace(" ", "") and buffered_andi:
                out_lines.extend(buffered_andi)
                buffered_andi = []
        else:
            out_lines.append(line)

    return out_lines


def main():
    lines = sys.stdin.readlines()
    filtered = filter_assembly(lines)
    sys.stdout.writelines(filtered)


if __name__ == "__main__":
    main()
