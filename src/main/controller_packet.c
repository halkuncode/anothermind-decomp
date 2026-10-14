//! CC1=2.7.2 G=0
#include "common.h"
#include "controller.h"

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_packet", ControllerCmd_SetupType3);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_packet", ControllerCmd_SetupType2);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_packet", ControllerCmd_SetupType4);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_packet", ControllerCmd_Abort);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_packet", InitControllerPacketIRQSystem);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_packet", InitControllerIRQSystem);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_packet", FlushControllerPacketBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_packet", HandleControllerPacketProcessed);

void SaveAndClearControllerCommandCode(ControllerAttribute* state) {
    u8 savedCommandType;

    savedCommandType = state->currCmdType;
    state->currCmdType = 0U;
    state->savedCmdType = savedCommandType;
}

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_packet", HandleControllerBufferFilled);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_packet", HandleControllerPacketReady);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_packet", HandleControllerTransferComplete);

ControllerState* QueryControllerState(s32 port) {
    ControllerState* controller = &g_Controllers[0];

    if (port & 0xF0) {
        controller = &g_Controllers[1];
    }
    return controller;
}
