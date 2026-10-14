.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

.text

/*
 * BIOS bzero syscall trampoline (A0 table, function 0x28).
 * Fast kernel-level memory clear used by the controller subsystem.
 */
.globl BIOS_bzero
.type BIOS_bzero, @function
BIOS_bzero:
    addiu      $t2, $zero, 0xA0
    jr         $t2
    addiu      $t1, $zero, 0x28
    nop
.size BIOS_bzero, . - BIOS_bzero

