//! PSYQ=4.0
#include "common.h"

// Note 'volitile' is allowed here as a deviation from 
// STYLE.md due to the high degree of timing needed
// for the root counter, 
#define RCNT_REG(addr) (*(volatile u16*)(addr))
#define RCNT2_COUNT    0x1F801120
#define RCNT2_MODE     0x1F801124
#define RCNT2_TARGET   0x1F801128

typedef enum ControllerCommand {
    CONTROLLER_POLL = 0x42,
    CONTROLLER_CONFIG_MODE = 0x43,
    CONTROLLER_MODE_SELECT = 0x44,
    CONTROLLER_QUERY_STATUS = 0x45,
    CONTROLLER_QUERY_ACTUATOR = 0x46,
    CONTROLLER_QUERY_PARAM = 0x47,
    CONTROLLER_ABORT = 0x4B,
    CONTROLLER_QUERY_MAP = 0x4C,
    CONTROLLER_RUMBLE_MAP = 0x4D,
} ControllerCommand;

typedef struct ControllerState {
    /* 0x00 */ u8 pad0[0x20];
    /* 0x20 */ u8* rumbleMap;
    /* 0x24 */ u8 configParam;
    /* 0x25 */ u8 pad25[3];
    /* 0x28 */ u8* vibrationBuffer;
    /* 0x2C */ u8* configBuffer;
    /* 0x30 */ u8 pad30[4];
    /* 0x34 */ u8 vibrationBufferLength;
    /* 0x35 */ u8 pad35;
    /* 0x36 */ u8 configBufferLength;
    /* 0x37 */ u8 configMode;
} ControllerState;

typedef struct ControllerAttribute {
    /* 0x00 */ u8 pad0[0x37];
    /* 0x37 */ u8 currCmdType;
    /* 0x38 */ u8 savedCmdType;
} ControllerAttribute;

void GsGetAndClearControllerReadyFlag(void)
{
    GetAndClearControllerReadyFlag();
}


void GsResetInterruptHandlers(void)
{
    ResetInterruptHandlersAndTimers();
}


void GsRemoveInterruptHandlers(void)
{
    RemoveInterruptHandlersAndTimers();
}

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", func_800467A8);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", GetVibrationDeviceType);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", func_800468C0);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", func_800469B8);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", func_80046A8C);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", QueueVibrationPlayback);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", func_80046B6C);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", SendVibrationCommand);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", func_80046C08);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", SetupControllerIRQHandlers);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", CheckAndHandleControllerInterrupt);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", HandleControllerFrameInterrupt);

extern s32 g_ControllerReadyFlag;

s32 GetAndClearControllerReadyFlag(void) {
    s32 readyFlag;

    readyFlag = g_ControllerReadyFlag;
    g_ControllerReadyFlag = 0;
    return readyFlag;
}

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", ResetInterruptHandlersAndTimers);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", RemoveInterruptHandlersAndTimers);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", BeginControllerTransfer);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", StepControllerTransferPhase);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", func_8004748C);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", func_8004769C);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", WaitForControllerReady);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", WaitForControllerAckBit);

void SetVibrationData(ControllerState* controller, u8* vibebuff, s8 vibebuffLen) {
    controller->vibrationBuffer = vibebuff;
    controller->vibrationBufferLength = vibebuffLen;
}

void SetControllerConfig(ControllerState* controller, s8 mode, u8* buffer, s8 length) {
    controller->configMode = mode;
    controller->configBuffer = buffer;
    controller->configBufferLength = length;
}

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", func_800479F4);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", ProcessControllerPacketState);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", CalculateControllerPacketLength);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", SetupControllerPacketHandlers);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", HandleControllerPacketCommand);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", ProcessControllerPacketStep);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", SetVibrationPlaybackState);

void SetControllerRumbleMap(ControllerState* controller)
{
    controller->configMode = CONTROLLER_RUMBLE_MAP;
    controller->configBufferLength = 6;
    controller->configBuffer = controller->rumbleMap;
}

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", func_80048318);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", func_800483E0);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", func_80048478);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", func_800484CC);

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

void SetControllerAbort(ControllerState* controller)
{
    controller->configMode = CONTROLLER_ABORT;
    controller->configBuffer = NULL;
    controller->configBufferLength = 0;
}

//TU Split (?)
__asm__(".align 3\n");

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", func_800485D8);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", func_80048620);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", func_800486F8);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", func_800487A4);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", func_80048830);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", InitControllerIRQSystem);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", func_80048D48);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", func_80048DB0);

void SaveAndClearControllerCommandCode(ControllerAttribute* state) {
    u8 savedCommandType;

    savedCommandType = state->currCmdType;
    state->currCmdType = 0U;
    state->savedCmdType = savedCommandType;
}

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", func_80048EB4);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", func_80048F70);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", func_800491EC);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", func_80049224);

// BIOS syscall in assembly
INCLUDE_ASM("asm/jp/nonmatchings/main/controller", BIOS_bzero);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", SetupControllerIRQFunctionPointers);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", UpdateControllerState);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", HandleControllerPacketState);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", func_80049600);

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", func_800496E0);

extern s32 g_ControllerTimeoutStartTime;
extern s32 g_ControllerTimeoutDuration;

void StartControllerTimeout(s32 duration)
{
    g_ControllerTimeoutDuration = duration;
    g_ControllerTimeoutStartTime = RCNT_REG(RCNT2_COUNT);
}

INCLUDE_ASM("asm/jp/nonmatchings/main/controller", func_80049738);
