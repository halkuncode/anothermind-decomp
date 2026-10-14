#!/usr/bin/env python3
"""
tools/maspsx_exceptions.py

External post-processor for maspsx assembly output.

NOTE: This script is an external exception handler for maspsx.
This is a rare compiler/assembler edge case where Sony's ASPSX assembler
scheduled a non-GP synthetic macro store across a return jump delay slot:
    sw   $reg, <symbol>
    j    $31
became:
    lui  $at, %hi(<symbol>)
    j    $31
    sw   $reg, %lo(<symbol>)($at)

maspsx does not implement delay-slot instruction scheduling.
THIS IS A RARE EXCEPTION AND NO MORE EXCEPTIONS ARE TO BE ADDED.
(Kept here for future decompiles where making an external exception may be an option.)
"""

import sys
import re

# Targeted leaf functions where ASPSX split a macro store into the j $31 delay slot.
TARGET_FUNCTIONS = {
    "GetAndClearControllerReadyFlag",
    "StartControllerTimeout",
    "SetupControllerIRQFunctionPointers",
}

STORE_RE = re.compile(r"^\s*(s[wbh])\s+(\$[a-z0-9]+),\s*([A-Za-z0-9_]+)\s*$")
J31_RE = re.compile(r"^\s*j\s+\$31\s*$")

def is_debug_or_label(line: str) -> bool:
    s = line.strip()
    if not s or s.startswith("#"):
        return True
    if s.startswith(".loc"):
        return True
    if s.endswith(":") and not s.startswith(".ent") and not s.startswith(".end"):
        return True
    return False

def process(lines):
    out = []
    current_func = None
    i = 0
    n = len(lines)

    while i < n:
        line = lines[i]
        stripped = line.strip()

        if stripped.startswith(".ent\t") or stripped.startswith(".ent "):
            current_func = stripped.split()[1]
        elif stripped.startswith(".end\t") or stripped.startswith(".end "):
            current_func = None

        if current_func in TARGET_FUNCTIONS:
            m_store = STORE_RE.match(stripped)
            if m_store:
                # Look ahead for j $31, collecting debug info / labels between store and jump
                j = i + 1
                intervening = []
                while j < n and is_debug_or_label(lines[j]):
                    intervening.append(lines[j])
                    j += 1

                if j < n and J31_RE.match(lines[j].strip()):
                    op = m_store.group(1)
                    reg = m_store.group(2)
                    sym = m_store.group(3)

                    out.append(".set\tnoat\n")
                    out.append(f"lui\t$at,%hi({sym})\n")
                    out.extend(intervening)
                    out.append("j\t$31\n")
                    out.append(f"{op}\t{reg},%lo({sym})($at)\n")
                    out.append(".set\tat\n")

                    # Skip j $31 and any following nop / nop debug comment
                    k = j + 1
                    while k < n and (not lines[k].strip() or lines[k].strip().startswith("#")):
                        k += 1
                    if k < n and lines[k].strip().startswith("nop"):
                        k += 1

                    i = k
                    continue

        out.append(line)
        i += 1

    return out

def main():
    lines = sys.stdin.readlines()
    out = process(lines)
    sys.stdout.writelines(out)

if __name__ == "__main__":
    main()

