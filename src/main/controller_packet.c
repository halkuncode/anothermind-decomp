//! CC1=2.7.2 G=0
#include "common.h"
#include "controller.h"

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_packet", func_800485D8);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_packet", func_80048620);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_packet", func_800486F8);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_packet", func_800487A4);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_packet", func_80048830);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_packet", InitControllerIRQSystem);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_packet", func_80048D48);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_packet", func_80048DB0);

void SaveAndClearControllerCommandCode(ControllerAttribute* state) {
    u8 savedCommandType;

    savedCommandType = state->currCmdType;
    state->currCmdType = 0U;
    state->savedCmdType = savedCommandType;
}

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_packet", func_80048EB4);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_packet", func_80048F70);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_packet", func_800491EC);

ControllerState* QueryControllerState(s32 port) {
    ControllerState* controller = &g_Controllers[0];

    if (port & 0xF0) {
        controller = &g_Controllers[1];
    }
    return controller;
}
