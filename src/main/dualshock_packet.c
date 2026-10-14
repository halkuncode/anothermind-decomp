#include "common.h"

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_packet", ControllerCmd_SetupType3);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_packet", ControllerCmd_SetupType2);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_packet", ControllerCmd_SetupType4);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_packet", ControllerCmd_Abort);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_packet", InitControllerPacketIRQSystem);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_packet", InitControllerIRQSystem);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_packet", FlushControllerPacketBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_packet", HandleControllerPacketProcessed);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_packet", SaveAndClearControllerCommandCode);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_packet", HandleControllerBufferFilled);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_packet", HandleControllerPacketReady);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_packet", HandleControllerTransferComplete);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_packet", QueryControllerState);
