#include "common.h"

typedef struct ControllerState {
    /* 0x00 */ u8 pad28[0x28];
    /* 0x28 */ u32 vibrationBuffer;
    /* 0x2C */ u8 pad2C[8];
    /* 0x34 */ u8 vibrationBufferLength;
    /* 0x35 */ u8 pad35[0xF0 - 0x35];
} ControllerState;

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", func_80046748);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", GsResetInterruptHandlers);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", func_80046788);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", func_800467A8);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", GetVibrationDeviceType);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", func_800468C0);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", func_800469B8);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", func_80046A8C);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", QueueVibrationPlayback);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", func_80046B6C);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", SendVibrationCommand);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", func_80046C08);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", SetupMovieIRQHandlers);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", CheckAndHandleMovieInterrupt);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", HandleMovieFrameInterrupt);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", func_80046F44);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", ResetInterruptHandlersAndTimers);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", func_80047024);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", BeginMovieFrameTransfer);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", StepMovieFrameDecodePhase);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", func_8004748C);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", func_8004769C);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", WaitForControllerReady);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", WaitForControllerAckBit);

void WriteVibrationData(ControllerState* controller, s32 vibebuff, s8 vibebuffLen) {
    controller->vibrationBuffer = vibebuff;
    controller->vibrationBufferLength = vibebuffLen;
}

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", func_800479E4);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", func_800479F4);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", ProcessMovieCommandState);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", CalculateTotalMovieChunkSize);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", SetupMovieFrameProcessing);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", HandleMovieFrameCommand);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", ProcessMovieFrameStep);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", SetVibrationPlaybackState);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", func_800482FC);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", func_80048318);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", func_800483E0);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", func_80048478);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", func_800484CC);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", SetupMovieCommandGeneric);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", func_8004854C);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", MovieCmd_SetupType3);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", MovieCmd_SetupType2);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", MovieCmd_SetupType4);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", MovieCmd_Abort);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", func_800485D8);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", func_80048620);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", func_800486F8);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", func_800487A4);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", func_80048830);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", InitMovieIRQSystem);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", func_80048D48);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", func_80048DB0);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", SaveAndClearMovieCommandCode);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", func_80048EB4);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", func_80048F70);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", func_800491EC);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", func_80049224);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", func_80049248);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", SetupMovieIRQFunctionPointers);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", UpdateMoviePlaybackControlState);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", HandleMoviePacketState);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", func_80049600);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", func_800496E0);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", func_80049718);

INCLUDE_ASM("asm/jp/nonmatchings/main/movie", func_80049738);
