//! CC1=2.7.2 G=0
#include "common.h"
#include "controller.h"

void GsGetAndClearControllerReadyFlag(void) { GetAndClearControllerReadyFlag(); }

void GsResetInterruptHandlers(void) { ResetInterruptHandlersAndTimers(); }

void GsRemoveInterruptHandlers(void) { RemoveInterruptHandlersAndTimers(); }

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", Controller_GetReverbMode);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", GetVibrationDeviceType);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", CheckVibrationPortMode);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", InitVibrationPlaybackPacket);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", SendVibrationDataPacket);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", QueueVibrationPlayback);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", SetupControllerVibrationIRQHandlers);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", SendVibrationCommand);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", CheckAndHandleControllerAuxInterrupt);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", SetupControllerIRQHandlers);
#else
// 94.09% exact match
extern void* g_ControllerIRQMainHandler;
void HandleControllerFrameInterrupt(void);
s32 CheckAndHandleControllerInterrupt(void);

void SetupControllerIRQHandlers(void) {
    void** handler = (void**)(s32)&g_ControllerIRQMainHandler;

    handler[0] = (void*)HandleControllerFrameInterrupt;
    handler[1] = (void*)CheckAndHandleControllerInterrupt;
    handler[-1] = NULL;
    handler[2] = NULL;
}
#endif

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

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", PollControllerTransferStatus);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", WaitControllerAckPulse);

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

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", ProcessControllerCommandState);

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

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", ProcessControllerFrameStep);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", SetVibrationMotorState);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", SetupControllerCommandGeneric);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller_api", ControllerCmd_SetupType1);

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
