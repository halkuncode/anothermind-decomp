//! PSYQ=4.0
#include "common.h"


//keep structs in c file
typedef struct PortraitSlot {
    /* 0x00 */ u8 pad00[2];
    /* 0x02 */ s16 state;          // or u16 (written with 3 here)
    /* 0x04 */ u8 pad04[0x44 - 4]; // total size 0x44 (68 bytes)
} PortraitSlot;

typedef struct NewsMode {
    /* 0x00 */ s16 newsModeActive;
    /* 0x02 */ s16 newsDisplayMode;
} NewsMode;


typedef struct TaiwaState {
    /* 0x000 */ u8 highlightSlotEnabled;
    /* 0x001 */ u8 pad01[0x17C - 0x001];
    /* 0x17C */ s16 newsFadeSlot1;
    /* 0x17E */ u8 pad17E[0x190 - 0x17E];
    /* 0x190 */ s16 newsFadeSlot2;
} TaiwaState;

extern s16 g_TaiwaBarX;
extern TaiwaState g_TaiwaState;
extern NewsMode g_NewsMode;

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", func_80102DC8);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", func_80103604);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", func_80103914);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", func_80103E34);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", func_80104A64);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", func_80104AF4);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", func_80104E48);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", func_801050FC);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", func_801051CC);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", UpdateMenuEffectState);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", func_8010666C);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", func_801067C8);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", func_80106A84);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", RunGameLoop);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", func_80106D44);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", ResetAndSubmitDebugOverlayPrimitives);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", ResetFullGameRuntimeState_80109064);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", DrawDebugHorizontalCursorMarker);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", DrawPortraitSlotDebug);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", DrawFaceSlotBoxDebug);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", PrintCacheSlotStatus);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", DisplayVMDebugPanel);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", DrawTaiwaDebugOverlay);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", SendPortraitCommand);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", CallScriptFunctionById);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", func_8010BDA8);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", DoEffectB);

NewsMode* SetNews(void) {
    NewsMode* news = &g_NewsMode;

    news->newsModeActive = 1;
    news->newsDisplayMode = 1;

    return news;
}

                            // extern

void ClearNewsState(void)
{
    ResetNewsSystem();
}

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", SetNewsValue);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", LoadKanjiById);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", ResetPortraitCacheStatus);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", OpenMenuById);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", PlayMovie);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", SetupExtendedMovieFlashEffect);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", TriggerMovieFlashEffect);

extern s32 g_PortraitSlotIndex;

s32 GetPackedDisplayHeightOffset(void) { return (g_PortraitSlotIndex << 8) | 0x01400000; }

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", ClearScreenAndResetDisplay);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", SetTPageParamForCurrentAndScreenPage);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", AdvanceDebugTextCursor);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", WriteCharToDebugBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", DbgScreenPrintString);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", func_8010C300);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", AdvanceFramesWithDebugUpdate);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", func_8010C3D4);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", func_8010C45C);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", func_8010C530);

void func_8010C5F4(void) {}

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", func_8010C5FC);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", ResetPortraitSlotsAndDrawAreas);

void func_8010C704(void) {}

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", func_8010C70C);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", func_8010C768);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", func_8010C7DC);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", func_8010C820);

// This changes the Portrait slot to state (expresion?) 3
void func_8010C870(PortraitSlot* slot) { slot->state = 3; }

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", func_8010C87C);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", func_8010C8A4);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", func_8010C8C8);



void ResetTaiwaFadeTimers(void) {
    g_TaiwaBarX = 0;
    g_TaiwaState.newsFadeSlot1 = 0;
    g_TaiwaState.newsFadeSlot2 = 0;
}

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", WaitWithDialogueUI);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", PlayDialogueMessage);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", PlaySystemMessage);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", func_8010CB14);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game_loop", DoGame);
