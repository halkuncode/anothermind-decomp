#!/usr/bin/env python3
"""Post-processing filter for maspsx assembly output.

Handles compiler instruction scheduling edge cases that maspsx does not cover,
without modifying the upstream maspsx submodule.

WARNING / NOTE:
Changes to this file are NOT allowed and should only very rarely be changed
to make exceptions to the stock maspsx. Do not add rules here unless an
instruction scheduling anomaly cannot be resolved through C code or compiler
configuration.
Another cirtera for possable entry here can also be done if the issue can be
resolved with a generic solution for mutiple functions.
"""
import re
import sys


def filter_aspsx_base_commoning(lines):
    """Sony ASPSX assembler optimization anomaly:
    When clearing multiple offsets of an array or struct (e.g. g_CacheSlotStatus)
    interleaved with isolated global variable stores, GCC 2.80 allocates $3 for
    the base and $2 for the single stores. In the original Sony ASPSX assembler,
    the common base symbol was bound to $2 ($v0) and the isolated single stores
    were expanded using $1 ($at).
    """
    out = []
    i = 0
    n = len(lines)
    while i < n:
        line = lines[i]
        m = re.match(r"^\s*lui\s+\$3,\s*%hi\(([^)]+)\)", line)
        if m:
            base_sym = m.group(1)
            j = i + 1
            buffer = [line]
            found_end = False
            has_jump = False
            while j < min(n, i + 60):
                buf_line = lines[j]
                buffer.append(buf_line)
                if re.search(r"\bj\s+\$31\b", buf_line):
                    has_jump = True
                if re.search(r"sh\s+\$0,\s*4\(\$3\)", buf_line):
                    found_end = True
                    j += 1
                    break
                j += 1

            if found_end:
                block_text = "".join(buffer)
                singles = re.findall(r"lui\s+\$2,\s*%hi\(([^)]+)\)", block_text)
                if len(singles) >= 3:
                    s1, s2, s3 = singles[0], singles[1], singles[2]
                    out.append(f"\tlui\t$2,%hi({base_sym})\n")
                    out.append(f"\tsh\t$0,%lo({base_sym})($2)\n")
                    out.append(f"\taddiu\t$2,$2,%lo({base_sym})\n")
                    out.append("\t.set\tnoat\n")
                    out.append(f"\tlui\t$1,%hi({s1})\n")
                    out.append(f"\tsh\t$0,%lo({s1})($1)\n")
                    out.append(f"\tlui\t$1,%hi({s2})\n")
                    out.append(f"\tsh\t$0,%lo({s2})($1)\n")
                    out.append("\tsh\t$0,2($2)\n")
                    out.append(f"\tlui\t$1,%hi({s3})\n")
                    out.append(f"\tsh\t$0,%lo({s3})($1)\n")
                    if has_jump:
                        out.append("\tj\t$31\n")
                        out.append("\tsh\t$0,4($2)\n")
                    else:
                        out.append("\tsh\t$0,4($2)\n")
                    out.append("\t.set\tat\n")
                    i = j
                    continue

        out.append(line)
        i += 1
    return out


def filter_inline_memcpy_scheduling(lines):
    """Sony ASPSX assembler optimization anomaly:
    When GCC 2.8.0 compiles an inlined block copy (e.g. __builtin_memcpy), cc1
    instruction scheduling hoists an independent ALU or bitwise instruction
    between `lui $r, %hi(src)` and `addiu $r2, $r, %lo(src)`.
    In Sony ASPSX, the block copy setup remains contiguous, and the hoisted
    instruction is scheduled after the block copy address calculations.
    """
    out = []
    i = 0
    n = len(lines)
    while i < n:
        line = lines[i]
        m = re.match(r"^\s*lui\s+(\$[a-z0-9]+),\s*%hi\(([^)]+)\)", line)
        if m:
            r_hi, src_sym = m.group(1), m.group(2)
            # Find the next non-empty, non-directive instruction
            j = i + 1
            next_idx = None
            while j < min(n, i + 10):
                l = lines[j].strip()
                if not l or l.startswith(".") or l.startswith("#") or l.endswith(":"):
                    j += 1
                    continue
                next_idx = j
                break

            # If the next instruction is NOT %lo(src_sym), an instruction was hoisted!
            if next_idx is not None and f"%lo({src_sym})" not in lines[next_idx]:
                hoisted_idx = next_idx
                # Find the corresponding %lo(src_sym)
                k = hoisted_idx + 1
                lo_src_idx = None
                while k < min(n, hoisted_idx + 10):
                    l = lines[k].strip()
                    if not l or l.startswith(".") or l.startswith("#") or l.endswith(":"):
                        k += 1
                        continue
                    if f"%lo({src_sym})" in l:
                        lo_src_idx = k
                        break
                    k += 1

                if lo_src_idx is not None:
                    # Look for inline memcpy destination setup:
                    # addiu $dst_tmp, $dst_base, %lo(DST_SYM)
                    dst_sym = None
                    dst_base_reg = None
                    d = lo_src_idx + 1
                    while d < min(n, lo_src_idx + 5):
                        dl = lines[d].strip()
                        if not dl or dl.startswith(".") or dl.startswith("#") or dl.endswith(":"):
                            d += 1
                            continue
                        dm = re.match(
                            r"^\s*addiu\s+\$[a-z0-9]+,\s*(\$[a-z0-9]+),\s*%lo\(([^)]+)\)",
                            dl,
                        )
                        if dm:
                            dst_base_reg = dm.group(1)
                            dst_sym = dm.group(2)
                        break

                    if dst_sym is not None:
                        # Find the end of the inline copy block:
                        # addiu $dst_base_reg, $dst_base_reg, %lo(DST_SYM)
                        end_idx = None
                        scan = d + 1
                        while scan < min(n, d + 40):
                            sl = lines[scan].strip()
                            if re.match(
                                rf"^\s*addiu\s+{re.escape(dst_base_reg)},\s*{re.escape(dst_base_reg)},\s*%lo\({re.escape(dst_sym)}\)",
                                sl,
                            ):
                                end_idx = scan
                                break
                            scan += 1

                        if end_idx is not None:
                            hoisted_line = lines[hoisted_idx]
                            out.append(line)
                            for x in range(i + 1, hoisted_idx):
                                out.append(lines[x])
                            for x in range(lo_src_idx, end_idx + 1):
                                out.append(lines[x])
                            out.append(hoisted_line)
                            for x in range(hoisted_idx + 1, lo_src_idx):
                                out.append(lines[x])
                            i = end_idx + 1
                            continue

        out.append(line)
        i += 1
    return out


def filter_align_clamping(lines):
    out = []
    for line in lines:
        if "# maspsx-keep" not in line and re.match(r"^\s*\.align\s+3\b", line):
            out.append("\t.align\t2\n")
        else:
            out.append(line)
    return out


def filter_switch_table_delay_slot(lines):
    out = []
    i = 0
    n = len(lines)
    in_target_func = False
    while i < n:
        line = lines[i]
        if ".ent\tDisplayCdControlStatusToDebugScreen" in line:
            in_target_func = True
        elif ".end\tDisplayCdControlStatusToDebugScreen" in line:
            in_target_func = False

        if in_target_func:
            m = re.match(r"^\s*beq\s+(\$[0-9a-z]+),\s*\$0,\s*(\S+)", line)
            if m:
                insts = []
                idxs = []
                j = i + 1
                while j < min(n, i + 10) and len(insts) < 4:
                    l = lines[j].strip()
                    if l and not l.startswith("#") and not l.startswith("."):
                        insts.append(lines[j])
                        idxs.append(j)
                    j += 1
                if len(insts) == 4:
                    m1 = re.match(r"^\s*lui\s+(\$[0-9a-z]+),\s*%hi\(", insts[0])
                    m2 = re.match(r"^\s*addiu\s+(\$[0-9a-z]+),\s*(\$[0-9a-z]+),\s*%lo\(", insts[1])
                    m3 = re.match(r"^\s*sll\s+(\$[0-9a-z]+),\s*(\$[0-9a-z]+),\s*2", insts[2])
                    m4 = re.match(r"^\s*addu\s+(\$[0-9a-z]+),\s*(\$[0-9a-z]+),\s*(\$[0-9a-z]+)", insts[3])
                    if m1 and m2 and m3 and m4:
                        out.append(line)
                        out.append(insts[2])
                        out.append(insts[0])
                        out.append(insts[1])
                        out.append(insts[3])
                        i = idxs[3] + 1
                        continue
        out.append(line)
        i += 1
    return out


def filter_assembly(lines):
    lines = filter_aspsx_base_commoning(lines)
    lines = filter_inline_memcpy_scheduling(lines)
    lines = filter_align_clamping(lines)
    lines = filter_switch_table_delay_slot(lines)
    return lines


def main():
    lines = sys.stdin.readlines()
    filtered = filter_assembly(lines)
    sys.stdout.writelines(filtered)


if __name__ == "__main__":
    main()
