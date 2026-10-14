//! CC1=2.7.2 G=0
#include "common.h"
#include "controller.h"

void GsGetAndClearControllerReadyFlag(void) { GetAndClearControllerReadyFlag(); }

void GsResetInterruptHandlers(void) { ResetInterruptHandlersAndTimers(); }

void GsRemoveInterruptHandlers(void) { RemoveInterruptHandlersAndTimers(); }

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", func_800467A8);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", GetVibrationDeviceType);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", func_800468C0);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", func_800469B8);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", func_80046A8C);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", QueueVibrationPlayback);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", func_80046B6C);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", SendVibrationCommand);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", func_80046C08);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", SetupControllerIRQHandlers);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", CheckAndHandleControllerInterrupt);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", HandleControllerFrameInterrupt);

s32 GetAndClearControllerReadyFlag(void) {
    s32 flag = g_ControllerReadyFlag;
    g_ControllerReadyFlag = 0;
    return flag;
}

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", ResetInterruptHandlersAndTimers);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", RemoveInterruptHandlersAndTimers);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", BeginControllerTransfer);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", StepControllerTransferPhase);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", func_8004748C);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", func_8004769C);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", WaitForControllerReady);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", WaitForControllerAckBit);

void SetVibrationData(ControllerState* controller, u8* vibebuff, s8 vibebuffLen) {
    controller->vibrationBuffer = vibebuff;
    controller->vibrationBufferLength = vibebuffLen;
}

void SetControllerConfig(ControllerState* controller, s8 mode, u8* buffer, s8 length) {
    controller->configMode = mode;
    controller->configBuffer = buffer;
    controller->configBufferLength = length;
}

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", func_800479F4);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", ProcessControllerPacketState);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", CalculateControllerPacketLength);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", SetupControllerPacketHandlers);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", HandleControllerPacketCommand);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", ProcessControllerPacketStep);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", SetVibrationPlaybackState);

void SetControllerRumbleMap(ControllerState* controller) {
    controller->configMode = CONTROLLER_RUMBLE_MAP;
    controller->configBufferLength = 6;
    controller->configBuffer = controller->rumbleMap;
}

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", func_80048318);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", func_800483E0);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", func_80048478);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", func_800484CC);

void SetControllerConfigMode(ControllerState* controller, u8 param) {
    controller->configMode = CONTROLLER_CONFIG_MODE;
    controller->configBuffer = &controller->configParam;
    controller->configParam = param;
    controller->configBufferLength = 1;
}

void SetControllerQueryStatus(ControllerState* controller) {
    controller->configMode = CONTROLLER_QUERY_STATUS;
    controller->configBuffer = NULL;
    controller->configBufferLength = 0;
}

void SetControllerQueryMap(ControllerState* controller, u8 param) {
    controller->configMode = CONTROLLER_QUERY_MAP;
    controller->configBuffer = &controller->configParam;
    controller->configParam = param;
    controller->configBufferLength = 1;
}

void SetControllerQueryActuator(ControllerState* controller, u8 param) {
    controller->configMode = CONTROLLER_QUERY_ACTUATOR;
    controller->configBuffer = &controller->configParam;
    controller->configParam = param;
    controller->configBufferLength = 1;
}

void SetControllerQueryParam(ControllerState* controller, u8 param) {
    controller->configMode = CONTROLLER_QUERY_PARAM;
    controller->configBuffer = &controller->configParam;
    controller->configParam = param;
    controller->configBufferLength = 1;
}

void SetControllerAbort(ControllerState* controller) {
    controller->configMode = CONTROLLER_ABORT;
    controller->configBuffer = NULL;
    controller->configBufferLength = 0;
}
