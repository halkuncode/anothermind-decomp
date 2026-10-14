#include "common.h"

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_sio", BIOS_bzero);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_sio", SetupControllerIRQFunctionPointers);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_sio", UpdateControllerState);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_sio", HandleControllerPacketState);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_sio", StepControllerPacketTimeout);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_sio", CheckVibrationBusyStat);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_sio", StartControllerTimeout);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_sio", WaitRC2Ready);
