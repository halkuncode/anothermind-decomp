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
_SW_RA_RE      = re.compile(r"^\s*sw\s+(?:\$31|\$ra),\s*\d+\(\$sp\)")
_J_RA_RE       = re.compile(r"^\s*j\s+\$31\s*$")
_JAL_RE        = re.compile(r"^\s*jal\s+(\S+)")
_LA_RE         = re.compile(r"^\s*la\s+(\$[a-z0-9]+),\s*([A-Za-z0-9_]+)")
_LI_RE         = re.compile(r"^\s*li\s+(\$[a-z0-9]+),\s*(\S+)")
_STORE_BASE_RE = re.compile(r"^\s*(sw|sh|sb)\s+(\$[a-z0-9]+),\s*0\((\$[a-z0-9]+)\)")
_STORE_SYM_OFF_RE = re.compile(r"^\s*(sw|sh|sb)\s+(\$[a-z0-9]+),\s*([A-Za-z0-9_]+)\+(\d+)")
_LA_SYM_OFF_RE    = re.compile(r"^\s*la\s+(\$[a-z0-9]+),\s*([A-Za-z0-9_]+)\+(\d+)")
_STORE_SYM_RE = re.compile(r"^\s*(sw|sh|sb)\s+(\$[a-z0-9]+),\s*([A-Za-z_][A-Za-z0-9_]*)\s*$")
_STORE_INDIRECT_RE = re.compile(r"^\s*(sw|sh|sb)\s+(\$[a-z0-9]+),\s*(-?\d*)\((\$[a-z0-9]+)\)\s*$")
_BRANCH_LABEL_RE = re.compile(r"^(\$|\.)?L\d+:$")
_BNE_ZERO_RE = re.compile(r"^\s*bne\s+(\$[a-z0-9]+),\s*\$0,\s*(\S+)")


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

        # Check if the instruction immediately preceding lw $31 is an independent store.
        # ASPSX reorders such a store to fill the load delay slot of lw $31, avoiding a nop.
        prev_store_idx = None
        p = i - 1
        while p >= 0:
            line_p = result[p].strip()
            if not line_p or line_p.startswith("#") or line_p.startswith("//") or line_p.startswith("/*"):
                p -= 1
                continue
            if line_p.startswith("."):
                if line_p.startswith(".end") or line_p.startswith(".ent"):
                    break
                p -= 1
                continue
            if line_p.endswith(":"):
                if not (line_p.startswith("LM") or line_p.startswith("$Lb") or line_p.startswith("$Le")):
                    break
                p -= 1
                continue
            m_store = _STORE_SYM_RE.match(line_p) or _STORE_INDIRECT_RE.match(line_p)
            if m_store:
                store_reg = m_store.group(2)
                if store_reg not in ("$31", "$ra") and "$31" not in line_p and "$ra" not in line_p and "$sp" not in line_p:
                    prev_store_idx = p
            break

        # All three found: lw $31 at i, addu $sp at j, j $31 at k
        sp_restore = result[j]
        j_line     = result[k]
        indent = re.match(r"^(\s*)", j_line).group(1)

        prev_def_idx = None
        if prev_store_idx is not None:
            q = prev_store_idx - 1
            while q >= 0:
                line_q = result[q].strip()
                if not line_q or line_q.startswith("#") or line_q.startswith("//") or line_q.startswith("/*"):
                    q -= 1
                    continue
                if line_q.startswith(".") or line_q.endswith(":"):
                    q -= 1
                    continue
                m_def = re.match(r"^\s*(?:li|addiu|addu|move|lbu|lb|lhu|lh|lw)\s+(" + re.escape(store_reg) + r")\b", line_q)
                if m_def and "$31" not in line_q and "$ra" not in line_q and "$sp" not in line_q:
                    prev_def_idx = q
                break

        if prev_def_idx is not None:
            def_line = result[prev_def_idx]
            m_li = re.match(r"^(\s*)li\s+(\$[a-z0-9]+),\s*(0x[0-9a-fA-F]+|\d+)", def_line)
            if m_li:
                def_line = f"{m_li.group(1)}addiu\t{m_li.group(2)},$zero,{m_li.group(3)}\n"
            delay_slot_fill = def_line + result[prev_store_idx]
            result[prev_def_idx] = ""
            result[prev_store_idx] = ""
        elif prev_store_idx is not None:
            delay_slot_fill = result[prev_store_idx]
            result[prev_store_idx] = ""
        else:
            delay_slot_fill = indent + "nop\n"

        noreorder_line = indent + ".set\tnoreorder\n"
        reorder_line   = indent + ".set\treorder\n"

        before  = result[:j]        # up to (not including) addu $sp
        between = result[j + 1:k]   # lines between addu $sp and j $31 (.loc, blanks)
        after   = result[k + 1:]    # everything after j $31

        result = (before
                  + [delay_slot_fill]
                  + between
                  + [noreorder_line, j_line, sp_restore, reorder_line]
                  + after)
        result = [line for line in result if line != ""]
        n = len(result)
        i += 1  # keep scanning; don't re-examine swapped lines
    return result


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
    current_func = ""
    while i < n:
        line_s = result[i].strip()
        m_ent = re.match(r"^\.ent\s+(\S+)", line_s)
        if m_ent:
            current_func = m_ent.group(1)
        elif line_s.startswith(".end"):
            current_func = ""
        elif not current_func and line_s.endswith(":") and not line_s.startswith(".") and not line_s.startswith("$") and not line_s.startswith("LM"):
            current_func = line_s[:-1]

        if not _is_code_line(result[i]):
            i += 1
            continue
        m = _STORE_SYM_RE.match(result[i].strip())
        if m:
            op, reg, sym = m.group(1), m.group(2), m.group(3)
            j = i + 1
            while j < n and not _is_code_line(result[j]):
                s = result[j].strip()
                if _BRANCH_LABEL_RE.match(s) or s.startswith(".end") or s.startswith(".ent"):
                    break
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
                    n = len(result)
                    i = j + 4
                    continue

        if current_func.startswith("AkaoSpu"):
            m2 = _STORE_INDIRECT_RE.match(result[i].strip())
            if m2:
                j = i + 1
                while j < n and not _is_code_line(result[j]):
                    s = result[j].strip()
                    if _BRANCH_LABEL_RE.match(s) or s.startswith(".end") or s.startswith(".ent"):
                        break
                    j += 1
                if j < n and _J_RA_RE.match(result[j].strip()):
                    j_line = result[j]
                    indent = re.match(r"^(\s*)", j_line).group(1)
                    noreorder_line = f"{indent}.set\tnoreorder\n"
                    store_line     = f"{indent}{result[i].strip()}\n"
                    reorder_line   = f"{indent}.set\treorder\n"

                    k = j + 1
                    while k < n and not _is_code_line(result[k]):
                        if result[k].strip().startswith("nop"):
                            break
                        k += 1
                    if k < n and result[k].strip().startswith("nop"):
                        result = (result[:i]
                                  + result[i + 1:j]
                                  + [noreorder_line, j_line, store_line, reorder_line]
                                  + result[j + 1:k]
                                  + result[k + 1:])
                        n = len(result)
                        i = j + 3
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


def leaf_la_branch_delay_slot_swap(lines: list) -> list:
    """When a leaf function returns one of two symbol addresses based on a condition:
        la   $2, <sym2>
        bne  $cond, $0, <label>
        la   $2, <sym1>
      <label>:
        j    $31
    ASPSX expands this with separate returns and delay slots:
        beqz $cond, <label>
        nop
        lui  $2, %hi(<sym2>)
        j    $31
        addiu $2, $2, %lo(<sym2>)
      <label>:
        lui  $2, %hi(<sym1>)
        j    $31
        addiu $2, $2, %lo(<sym1>)
    """
    result = list(lines)
    n = len(result)
    i = 0
    while i < n:
        if not _is_code_line(result[i]):
            i += 1
            continue
        m_la1 = _LA_RE.match(result[i].strip())
        if not m_la1:
            i += 1
            continue
        reg1, sym2 = m_la1.group(1), m_la1.group(2)

        j = i + 1
        while j < n and not _is_code_line(result[j]):
            j += 1
        if j >= n:
            i += 1
            continue
        m_bne = _BNE_ZERO_RE.match(result[j].strip())
        if not m_bne:
            i += 1
            continue
        cond_reg, label = m_bne.group(1), m_bne.group(2)

        k = j + 1
        while k < n and not _is_code_line(result[k]):
            k += 1
        if k >= n:
            i += 1
            continue
        m_la2 = _LA_RE.match(result[k].strip())
        if not m_la2 or m_la2.group(1) != reg1:
            i += 1
            continue
        sym1 = m_la2.group(2)

        l = k + 1
        found_label = False
        while l < n:
            s = result[l].strip()
            if s == f"{label}:":
                found_label = True
                break
            if _is_code_line(result[l]):
                break
            l += 1
        if not found_label:
            i += 1
            continue

        m = l + 1
        while m < n and not _is_code_line(result[m]):
            m += 1
        if m >= n or not _J_RA_RE.match(result[m].strip()):
            i += 1
            continue

        indent = re.match(r"^(\s*)", result[i]).group(1)
        transformed = [
            f"{indent}.set\tnoreorder\n",
            f"{indent}beqz\t{cond_reg},{label}\n",
            f"{indent}nop\n",
            f"{indent}lui\t{reg1},%hi({sym2})\n",
            f"{indent}j\t$31\n",
            f"{indent}addiu\t{reg1},{reg1},%lo({sym2})\n",
            f"{label}:\n",
            f"{indent}lui\t{reg1},%hi({sym1})\n",
            f"{indent}j\t$31\n",
            f"{indent}addiu\t{reg1},{reg1},%lo({sym1})\n",
            f"{indent}.set\treorder\n",
        ]
        result = result[:i] + transformed + result[m + 1:]
        n = len(result)
        i = m + 1
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


def aspsx_consecutive_lw_pair_swap(lines: list, gp_symbols: set[str]) -> list:
    """When cc1 emits consecutive global symbol loads:
        lw  $r1, sym1
        lw  $r2, sym2
    where r1 != r2 and neither is in GP, ASPSX expands both and reorders
    them so both lui instructions come first:
        lui $r1, %hi(sym1)
        lui $r2, %hi(sym2)
        lw  $r1, %lo(sym1)($r1)
        lw  $r2, %lo(sym2)($r2)
    """
    result = list(lines)
    n = len(result)
    i = 0
    while i < n - 1:
        if not _is_code_line(result[i]):
            i += 1
            continue
        m1 = _LW_SYM_RE.match(result[i].strip())
        if not m1:
            i += 1
            continue
        reg1, sym1 = m1.group(1), m1.group(2)
        if is_gp_symbol(sym1, gp_symbols):
            i += 1
            continue

        j = i + 1
        while j < n and not _is_code_line(result[j]):
            j += 1
        if j >= n:
            break
        m2 = _LW_SYM_RE.match(result[j].strip())
        if not m2:
            i += 1
            continue
        reg2, sym2 = m2.group(1), m2.group(2)
        if reg1 == reg2 or is_gp_symbol(sym2, gp_symbols):
            i += 1
            continue

        indent = re.match(r"^(\s*)", result[i]).group(1)
        line1 = f"{indent}lui\t{reg1},%hi({sym1})\n"
        line2 = f"{indent}lui\t{reg2},%hi({sym2})\n"
        line3 = f"{indent}lw\t{reg1},%lo({sym1})({reg1})\n"
        line4 = f"{indent}lw\t{reg2},%lo({sym2})({reg2})\n"
        between = result[i + 1:j]

        result = result[:i] + [line1, line2] + between + [line3, line4] + result[j + 1:]
        n = len(result)
        i = j + 3
    return result


def leaf_la_multi_store_delay_slot_swap(lines: list) -> list:
    """When a leaf function loads a symbol address, stores to 0($reg) and <sym>+<offset>,
    followed by `j $31`, ASPSX splits `la` and places the second store in the delay slot.
    """
    result = list(lines)
    n = len(result)
    i = 0
    while i < n:
        if not _is_code_line(result[i]):
            i += 1
            continue
        m_la = _LA_RE.match(result[i].strip())
        if not m_la:
            i += 1
            continue
        reg1, sym = m_la.group(1), m_la.group(2)
        j = i + 1
        while j < n and not _is_code_line(result[j]):
            j += 1
        if j >= n:
            i += 1
            continue
        m_li = _LI_RE.match(result[j].strip())
        if not m_li:
            i += 1
            continue
        reg2 = m_li.group(1)
        k = j + 1
        while k < n and not _is_code_line(result[k]):
            k += 1
        if k >= n:
            i += 1
            continue
        m_sb = _STORE_BASE_RE.match(result[k].strip())
        if not m_sb or m_sb.group(2) != reg2 or m_sb.group(3) != reg1:
            i += 1
            continue
        op = m_sb.group(1)
        l = k + 1
        while l < n and not _is_code_line(result[l]):
            l += 1
        if l >= n:
            i += 1
            continue
        m_sso = _STORE_SYM_OFF_RE.match(result[l].strip())
        if not m_sso or m_sso.group(1) != op or m_sso.group(2) != reg2 or m_sso.group(3) != sym:
            i += 1
            continue
        offset = m_sso.group(4)
        m = l + 1
        while m < n and not _is_code_line(result[m]):
            m += 1
        if m >= n or not _J_RA_RE.match(result[m].strip()):
            i += 1
            continue

        indent = re.match(r"^(\s*)", result[i]).group(1)
        result[i] = f"{indent}lui\t{reg1},%hi({sym})\n"
        result[k] = f"{indent}{op}\t{reg2},%lo({sym})({reg1})\n{indent}addiu\t{reg1},{reg1},%lo({sym})\n"
        result[l] = ""
        result[m] = f"{indent}.set\tnoreorder\n{indent}j\t$31\n{indent}{op}\t{reg2},{offset}({reg1})\n{indent}.set\treorder\n"
        i = m + 1
    return [line for line in result if line != ""]


def leaf_struct_multi_store_delay_slot_swap(lines: list) -> list:
    """When a leaf function stores to a symbol at multiple offsets, e.g.:
        sh  $reg, <sym>+<off1>
        sh  $reg, <sym>+<off2>
        j   $31
    (optionally preceded by a direct symbol store):
        sh  $reg, <sym0>
    ASPSX loads the base address of <sym> into $2 ($v0), stores <off1>($2),
    and places the second store <off2>($2) into the delay slot of `j $31`.
    If preceded by `<op> $reg, <sym0>`, ASPSX also expands that with $2.
    """
    result = list(lines)
    n = len(result)
    i = 0
    while i < n:
        if not _is_code_line(result[i]):
            i += 1
            continue
        m1 = _STORE_SYM_OFF_RE.match(result[i].strip())
        if not m1:
            i += 1
            continue
        op1, reg1, sym1, off1 = m1.group(1), m1.group(2), m1.group(3), m1.group(4)
        j = i + 1
        while j < n and not _is_code_line(result[j]):
            s = result[j].strip()
            if _BRANCH_LABEL_RE.match(s) or s.startswith(".end") or s.startswith(".ent"):
                break
            j += 1
        if j >= n:
            i += 1
            continue
        m2 = _STORE_SYM_OFF_RE.match(result[j].strip())
        if not m2 or m2.group(1) != op1 or m2.group(2) != reg1 or m2.group(3) != sym1:
            i += 1
            continue
        off2 = m2.group(4)
        k = j + 1
        while k < n and not _is_code_line(result[k]):
            s = result[k].strip()
            if _BRANCH_LABEL_RE.match(s) or s.startswith(".end") or s.startswith(".ent"):
                break
            k += 1
        if k >= n or not _J_RA_RE.match(result[k].strip()):
            i += 1
            continue

        indent = re.match(r"^(\s*)", result[i]).group(1)
        h = i - 1
        while h >= 0 and not _is_code_line(result[h]):
            s = result[h].strip()
            if _BRANCH_LABEL_RE.match(s) or s.startswith(".end") or s.startswith(".ent"):
                h = -1
                break
            h -= 1
        if h >= 0:
            m_prev = _STORE_SYM_RE.match(result[h].strip())
            if m_prev and m_prev.group(1) == op1 and m_prev.group(2) == reg1:
                sym0 = m_prev.group(3)
                result[h] = f"{indent}lui\t$2,%hi({sym0})\n{indent}{op1}\t{reg1},%lo({sym0})($2)\n"

        result[i] = f"{indent}lui\t$2,%hi({sym1})\n{indent}addiu\t$2,$2,%lo({sym1})\n{indent}{op1}\t{reg1},{off1}($2)\n"
        result[j] = ""
        result[k] = f"{indent}.set\tnoreorder\n{indent}j\t$31\n{indent}{op1}\t{reg1},{off2}($2)\n{indent}.set\treorder\n"
        i = k + 1
    return [line for line in result if line != ""]


def leaf_la_offset_struct_access_swap(lines: list) -> list:
    """When cc1 accesses a struct field via `la $reg, <sym>+<offset>` followed by
    accesses to 0($reg), ASPSX materializes `<sym>` into $reg without adding <offset>,
    and instead adds <offset> to subsequent 0($reg) displacements:
        la   $reg, <sym>+<offset>
        lw   $dest, 0($reg)
        ...
        sw   $src, 0($reg)
    Becomes:
        lui   $reg, %hi(<sym>)
        addiu $reg, $reg, %lo(<sym>)
        lw    $dest, <offset>($reg)
        ...
        sw    $src, <offset>($reg)
    """
    result = list(lines)
    n = len(result)
    i = 0
    while i < n:
        if not _is_code_line(result[i]):
            i += 1
            continue
        m = _LA_SYM_OFF_RE.match(result[i].strip())
        if not m:
            i += 1
            continue
        reg, sym, off = m.group(1), m.group(2), m.group(3)
        indent = re.match(r"^(\s*)", result[i]).group(1)

        j = i + 1
        replaced_any = False
        target_pat = re.compile(r"(0\(" + re.escape(reg) + r"\))")
        while j < n:
            line_s = result[j].strip()
            if _BRANCH_LABEL_RE.match(line_s) or line_s.startswith(".end") or line_s.startswith(".ent"):
                break
            if _is_code_line(result[j]):
                if target_pat.search(result[j]):
                    result[j] = target_pat.sub(f"{off}({reg})", result[j])
                    replaced_any = True
                elif re.match(r"^\s*(?:[a-z]+)\s+" + re.escape(reg) + r"\b", line_s):
                    break
            j += 1

        if replaced_any:
            result[i] = f"{indent}lui\t{reg},%hi({sym})\n{indent}addiu\t{reg},{reg},%lo({sym})\n"
        i += 1
    return result


def leaf_store_multi_symbol_delay_slot_swap(lines: list, gp_symbols: set[str]) -> list:
    """When a leaf function stores to sym1, performs an op, and stores to sym2 before j $31,
    ASPSX expands sym1 with $3, loads %hi(sym2) into $3 before the operation, and puts the store to
    %lo(sym2)($3) in the delay slot of j $31:
        sh   $0, <sym1>
        sll  $reg, $reg, <shift>
        sw   $reg, <sym2>
        j    $31
    Becomes:
        lui  $3, %hi(<sym1>)
        sh   $0, %lo(<sym1>)($3)
        lui  $3, %hi(<sym2>)
        sll  $reg, $reg, <shift>
        .set noreorder
        j    $31
        sw   $reg, %lo(<sym2>)($3)
        .set reorder
    """
    result = list(lines)
    n = len(result)
    i = 0
    while i < n:
        if not _is_code_line(result[i]):
            i += 1
            continue
        m1 = _STORE_SYM_RE.match(result[i].strip())
        if not m1:
            i += 1
            continue
        op1, reg1, sym1 = m1.group(1), m1.group(2), m1.group(3)
        if is_gp_symbol(sym1, gp_symbols):
            i += 1
            continue

        j = i + 1
        while j < n and not _is_code_line(result[j]):
            if result[j].strip().startswith(".end") or result[j].strip().startswith(".ent"):
                break
            j += 1
        if j >= n or not _is_code_line(result[j]):
            i += 1
            continue

        k = j + 1
        while k < n and not _is_code_line(result[k]):
            if result[k].strip().startswith(".end") or result[k].strip().startswith(".ent"):
                break
            k += 1
        if k >= n:
            i += 1
            continue
        m2 = _STORE_SYM_RE.match(result[k].strip())
        if not m2:
            i += 1
            continue
        op2, reg2, sym2 = m2.group(1), m2.group(2), m2.group(3)
        if is_gp_symbol(sym2, gp_symbols):
            i += 1
            continue

        l = k + 1
        while l < n and not _is_code_line(result[l]):
            if result[l].strip().startswith(".end") or result[l].strip().startswith(".ent"):
                break
            l += 1
        if l >= n or not _J_RA_RE.match(result[l].strip()):
            i += 1
            continue

        indent = re.match(r"^(\s*)", result[i]).group(1)
        result[i] = f"{indent}lui\t$3,%hi({sym1})\n{indent}{op1}\t{reg1},%lo({sym1})($3)\n"
        result[j] = f"{indent}lui\t$3,%hi({sym2})\n{result[j]}"
        result[k] = ""
        result[l] = f"{indent}.set\tnoreorder\n{indent}j\t$31\n{indent}{op2}\t{reg2},%lo({sym2})($3)\n{indent}.set\treorder\n"
        i = l + 1
    return [line for line in result if line != ""]


def leaf_interleaved_store_swap(lines: list, gp_symbols: set[str]) -> list:
    """When a leaf function stores to a non-GP symbol, followed by a GP symbol,
    followed by another non-GP symbol:
        sw   $reg1, <sym1>   (non-gp)
        sb   $reg2, <sym2>   (gp)
        sw   $reg3, <sym3>   (non-gp)
    ASPSX expands sym1 with $2, loads %hi(sym3) into $2 before the GP store,
    and stores to %lo(sym3)($2):
        lui  $2, %hi(<sym1>)
        sw   $reg1, %lo(<sym1>)($2)
        lui  $2, %hi(<sym3>)
        sb   $reg2, <sym2>
        sw   $reg3, %lo(<sym3>)($2)
    """
    result = list(lines)
    n = len(result)
    i = 0
    while i < n:
        if not _is_code_line(result[i]):
            i += 1
            continue
        m1 = _STORE_SYM_RE.match(result[i].strip())
        if not m1:
            i += 1
            continue
        op1, reg1, sym1 = m1.group(1), m1.group(2), m1.group(3)
        if is_gp_symbol(sym1, gp_symbols):
            i += 1
            continue

        j = i + 1
        while j < n and not _is_code_line(result[j]):
            if result[j].strip().startswith(".end") or result[j].strip().startswith(".ent"):
                break
            j += 1
        if j >= n or not _is_code_line(result[j]):
            i += 1
            continue
        m2 = _STORE_SYM_RE.match(result[j].strip())
        if not m2:
            i += 1
            continue
        op2, reg2, sym2 = m2.group(1), m2.group(2), m2.group(3)
        if not is_gp_symbol(sym2, gp_symbols):
            i += 1
            continue

        k = j + 1
        while k < n and not _is_code_line(result[k]):
            if result[k].strip().startswith(".end") or result[k].strip().startswith(".ent"):
                break
            k += 1
        if k >= n or not _is_code_line(result[k]):
            i += 1
            continue
        m3 = _STORE_SYM_RE.match(result[k].strip())
        if not m3:
            i += 1
            continue
        op3, reg3, sym3 = m3.group(1), m3.group(2), m3.group(3)
        if is_gp_symbol(sym3, gp_symbols):
            i += 1
            continue

        if reg1 in ("$2", "$v0") or reg2 in ("$2", "$v0") or reg3 in ("$2", "$v0"):
            i += 1
            continue

        indent = re.match(r"^(\s*)", result[i]).group(1)
        h = i - 1
        while h >= 0 and not _is_code_line(result[h]):
            h -= 1
        m_br = _BNE_ZERO_RE.match(result[h].strip()) if h >= 0 else None
        if m_br:
            cond_reg, label = m_br.group(1), m_br.group(2)
            result[h] = f"{indent}.set\tnoreorder\n{indent}bnez\t{cond_reg},{label}\n{indent}lui\t$2,%hi({sym1})\n{indent}.set\treorder\n"
            result[i] = f"{indent}{op1}\t{reg1},%lo({sym1})($2)\n"
        else:
            result[i] = f"{indent}lui\t$2,%hi({sym1})\n{indent}{op1}\t{reg1},%lo({sym1})($2)\n"
        result[j] = f"{indent}lui\t$2,%hi({sym3})\n{result[j]}"
        result[k] = f"{indent}{op3}\t{reg3},%lo({sym3})($2)\n"
        i = k + 1
    return result


def leaf_repeated_store_scratch_swap(lines: list, gp_symbols: set[str]) -> list:
    """When a leaf function stores to the same non-GP symbol multiple times,
    ASPSX loads the symbol address into $2 ($v0) and reuses it for the subsequent stores:
        sh $reg1, <sym>
        ...
        sh $reg2, <sym>
    """
    result = list(lines)
    n = len(result)
    i = 0
    while i < n:
        if not _is_code_line(result[i]):
            i += 1
            continue
        m1 = _STORE_SYM_RE.match(result[i].strip())
        if not m1:
            i += 1
            continue
        op1, reg1, sym1 = m1.group(1), m1.group(2), m1.group(3)
        if is_gp_symbol(sym1, gp_symbols):
            i += 1
            continue

        j = i + 1
        found_second = False
        second_idx = -1
        while j < n:
            s = result[j].strip()
            if s.startswith(".end") or s.startswith(".ent"):
                break
            if _is_code_line(result[j]):
                m2 = _STORE_SYM_RE.match(s)
                if m2 and m2.group(1) == op1 and m2.group(3) == sym1:
                    found_second = True
                    second_idx = j
                    break
            j += 1
        if not found_second:
            i += 1
            continue

        indent = re.match(r"^(\s*)", result[i]).group(1)
        result[i] = f"{indent}# maspsx-repeated-store-start\n{indent}lui\t$2,%hi({sym1})\n{indent}{op1}\t{reg1},%lo({sym1})($2)\n"
        m2 = _STORE_SYM_RE.match(result[second_idx].strip())
        reg2 = m2.group(2)
        result[second_idx] = f"{indent}{op1}\t{reg2},%lo({sym1})($2)\n"

        k = second_idx + 1
        while k < n and not result[k].strip().startswith("j\t$31"):
            k += 1
        if k < n:
            result[k] = f"{result[k]}{indent}# maspsx-repeated-store-end\n"
        i = second_idx + 1
    return result


def expand_li_addiu(lines: list) -> list:
    """ASPSX expands small positive immediate constants (0 < val < 0x8000) using
    `addiu $reg, $zero, val` instead of `ori $reg, $zero, val`.
    """
    result = []
    for line in lines:
        m = re.match(r"^(\s*)li\s+(\$[a-z0-9]+),\s*(0x[0-9a-fA-F]+|-?\d+)(\s*#.*)?$", line)
        if m:
            indent, reg, val_str, comment = m.group(1), m.group(2), m.group(3), m.group(4) or ""
            try:
                val = int(val_str, 0)
                if 0 < val < 0x8000:
                    result.append(f"{indent}addiu\t{reg},$zero,{val}{comment}\n")
                    continue
            except ValueError:
                pass
        result.append(line)
    return result


def main():
    in_text = sys.stdin.read()
    lines = in_text.splitlines(keepends=True)
    gp_symbols = load_gp_symbols()

    is_unswapped_epilogue_file = any(
        line.strip().startswith(".file") and ("controller.c" in line or "movie.c" in line or "psxsdk.c" in line)
        for line in lines[:15]
    )

    lines = strip_dead_epilogue(lines)
    if not is_unswapped_epilogue_file:
        lines = epilogue_delay_slot_swap(lines)
    lines = leaf_la_branch_delay_slot_swap(lines)
    lines = leaf_la_delay_slot_swap(lines)
    lines = leaf_la_multi_store_delay_slot_swap(lines)
    lines = leaf_struct_multi_store_delay_slot_swap(lines)
    lines = leaf_la_offset_struct_access_swap(lines)
    lines = leaf_store_multi_symbol_delay_slot_swap(lines, gp_symbols)
    lines = leaf_interleaved_store_swap(lines, gp_symbols)
    lines = leaf_repeated_store_scratch_swap(lines, gp_symbols)
    lines = aspsx_consecutive_lw_pair_swap(lines, gp_symbols)
    lines = aspsx_load_symbol_scratch_swap(lines)
    lines = expand_li_addiu(lines)
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
        final_lines = []
        for line in out_lines:
            if "# maspsx-repeated-store-start" in line:
                final_lines.append(".set\tnoreorder\n")
            elif "# maspsx-repeated-store-end" in line:
                final_lines.append(".set\treorder\n")
            else:
                final_lines.append(line)
        sys.stdout.write("".join(final_lines))

    sys.exit(proc.returncode)



if __name__ == "__main__":
    main()
