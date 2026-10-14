//! CC1=2.7.2 G=0
#include "common.h"
#include "controller.h"

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_sio", SetupControllerIRQFunctionPointers);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_sio", UpdateControllerState);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_sio", HandleControllerPacketState);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_sio", func_80049600);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_sio", func_800496E0);

void StartControllerTimeout(s32 duration) {
    g_ControllerTimeoutDuration = duration;
    g_ControllerTimeoutStartTime = RCNT_REG(RCNT2_COUNT);
}

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_sio", func_80049738);
