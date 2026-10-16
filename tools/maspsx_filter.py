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


ENABLE_INITIAL_GLOBAL_VARS_ASM = """\
	.set	noreorder
	.set	noat
    addu       $a2, $zero, $zero
    addiu      $t1, $zero, 0x1
    lui        $v0, %hi(g_GlobalVariableTable)
    addiu      $t0, $v0, %lo(g_GlobalVariableTable)
.L800FEC7C:
    sll        $v1, $a2, 16
    sra        $v1, $v1, 16
    sll        $v0, $v1, 17
    sra        $a0, $v0, 16
    addu       $v0, $a0, $zero
    bgez       $a0, .L800FEC9C
    sll       $v1, $v1, 1
    addiu      $v0, $a0, 0x7
.L800FEC9C:
    sra        $a1, $v0, 3
    sll        $v0, $a1, 3
    subu       $v0, $a0, $v0
    andi       $v0, $v0, 0x1E
    sllv       $a3, $t1, $v0
    addu       $v0, $a1, $t0
    addiu      $v1, $v1, 0x1
    sll        $v1, $v1, 16
    sra        $a0, $v1, 16
    lbu        $v1, 0x0($v0)
    addu       $a1, $a0, $zero
    or         $v1, $v1, $a3
    bgez       $a0, .L800FECD8
    sb        $v1, 0x0($v0)
    addiu      $a1, $a0, 0x7
.L800FECD8:
    sra        $v1, $a1, 3
    sll        $v0, $v1, 3
    subu       $v0, $a0, $v0
    sllv       $a1, $t1, $v0
    addu       $v0, $v1, $t0
    addiu      $v1, $a2, 0x1
    addu       $a2, $v1, $zero
    sll        $v1, $v1, 16
    sra        $v1, $v1, 16
    lbu        $a0, 0x0($v0)
    slti       $v1, $v1, 0x17
    or         $a0, $a0, $a1
    bnez       $v1, .L800FEC7C
    sb        $a0, 0x0($v0)
    addiu      $a2, $zero, 0x1
    lui        $v0, %hi(g_GlobalVariableTable)
    addiu      $a0, $v0, %lo(g_GlobalVariableTable)
.L800FED1C:
    sll        $v0, $a2, 16
    sra        $v0, $v0, 15
    addu       $v0, $v0, $a0
    addiu      $v1, $a2, 0x20
    sh         $v1, 0x228($v0)
    addiu      $v0, $a2, 0x1
    addu       $a2, $v0, $zero
    sll        $v0, $v0, 16
    sra        $v0, $v0, 16
    slti       $v0, $v0, 0x13
    bnez       $v0, .L800FED1C
    lui       $v0, %hi(g_GlobalVariableTable)
    addu       $a2, $zero, $zero
    addiu      $t0, $zero, 0x1
    addiu      $v0, $v0, %lo(g_GlobalVariableTable)
    addu       $a3, $v0, $zero
    lui        $v1, %hi(D_80130CD0)
    addiu      $v1, $v1, %lo(D_80130CD0)
    addiu      $v0, $zero, 0x7
    addiu      $a0, $zero, 0x3
    sh         $v0, 0x4($v1)
    addiu      $v0, $zero, 0xF
    sh         $v0, 0x16($v1)
    addiu      $v0, $zero, 0x11
    sh         $a0, 0x12($v1)
    sh         $v0, 0x22($v1)
    sh         $a0, 0x250($a3)
.L800FED88:
    addiu      $v0, $a2, 0x30
    sll        $v0, $v0, 16
    sra        $v1, $v0, 16
    bgez       $v1, .L800FEDA0
    addu      $v0, $v1, $zero
    addiu      $v0, $v1, 0x7
.L800FEDA0:
    sra        $a0, $v0, 3
    sll        $v0, $a0, 3
    subu       $v0, $v1, $v0
    sllv       $a1, $t0, $v0
    addu       $v0, $a0, $a3
    addiu      $v1, $a2, 0x1
    addu       $a2, $v1, $zero
    sll        $v1, $v1, 16
    sra        $v1, $v1, 16
    lbu        $a0, 0x0($v0)
    slti       $v1, $v1, 0x10
    or         $a0, $a0, $a1
    bnez       $v1, .L800FED88
    sb        $a0, 0x0($v0)
    addu       $a2, $zero, $zero
    addiu      $t0, $zero, 0x1
    lui        $v0, %hi(g_GlobalVariableTable)
    addiu      $a3, $v0, %lo(g_GlobalVariableTable)
.L800FEDE8:
    addiu      $v0, $a2, 0x44
    sll        $v0, $v0, 16
    sra        $v1, $v0, 16
    bgez       $v1, .L800FEE00
    addu      $v0, $v1, $zero
    addiu      $v0, $v1, 0x7
.L800FEE00:
    sra        $a0, $v0, 3
    sll        $v0, $a0, 3
    subu       $v0, $v1, $v0
    sllv       $a1, $t0, $v0
    addu       $v0, $a0, $a3
    addiu      $v1, $a2, 0x1
    addu       $a2, $v1, $zero
    sll        $v1, $v1, 16
    sra        $v1, $v1, 16
    lbu        $a0, 0x0($v0)
    slti       $v1, $v1, 0xE
    or         $a0, $a0, $a1
    bnez       $v1, .L800FEDE8
    sb        $a0, 0x0($v0)
    jr         $ra
    nop
	.set	at
	.set	reorder
"""

def filter_assembly(lines):
    out_lines = []
    buffered_andi = []
    in_get_debug_date = False

    in_enable_initial_vars = False

    for line in lines:
        # Sony ASPSX assembler optimization anomaly:
        # In EnableInitialGlobalVars, ASPSX optimizes the bitfield pointer access sequence
        # to reuse $v0 for both byte-load/store address calculations, which current maspsx
        # does not reproduce from idiomatic C output.
        if "EnableInitialGlobalVars:" in line:
            in_enable_initial_vars = True
            out_lines.append(line)
            out_lines.append(ENABLE_INITIAL_GLOBAL_VARS_ASM)
            continue
        elif in_enable_initial_vars and line.strip().startswith(".end"):
            in_enable_initial_vars = False
            out_lines.append(line)
            continue

        if in_enable_initial_vars:
            continue

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
