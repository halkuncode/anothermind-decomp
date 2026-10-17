#include "common.h"

// keep structs in c file
typedef struct PortraitSlot {
    /* 0x00 */ u8 pad00[2];
    /* 0x02 */ s16 state;
    /* 0x04 */ u8 pad04[0x22 - 0x04];
    /* 0x22 */ s16 msgBoxType;
    /* 0x24 */ u8 pad24[0x36 - 0x24];
    /* 0x36 */ s16 unk36;
    /* 0x38 */ u8 pad38[0x3E - 0x38];
    /* 0x3E */ s16 unk3E;
    /* 0x40 */ u8 pad40[0x44 - 0x40]; // total size 0x44 (68 bytes)
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

extern u8 g_MessageBoxType;
extern s16 g_CacheSlotStatus[];
extern s32 g_PortraitSlotIndex;
extern u16 g_SavedScriptState;
extern u16 g_ScriptCurrentState;
extern s16 g_TaiwaBarX;
extern s32 g_FunctionTableIndex;
extern s16 g_CurrentMenuRequest;
extern NewsMode g_NewsMode;
extern s16 g_CurrentKanjiSet;
extern s32 D_80130E38;
extern s32 D_80130E3C;
extern TaiwaState g_TaiwaState;
extern s16 D_8017E804;
extern s16 D_8018F004;
extern s16 D_8019F804;

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", RunSaveLoadMenu);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", VerifyMemoryCardSlots);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", RunConfigMenu);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", RunDialogueHistoryMenu);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", ResetMenuSelectionState);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", ProcessSaveConfirmation);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", TrySaveGameToMemoryCard);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", FadeInMenuUI);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", FadeOutMenuUI);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", UpdateMenuEffectState);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", LoadChapterSceneBackground);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", UpdateInGameMenuTransitions);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", DispatchInGameMenu);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", RunGameLoop);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", RenderEngineDebugAndUI);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", ResetAndSubmitDebugOverlayPrimitives);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", ResetVMEngineRuntimeState);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", DrawDebugHorizontalCursorMarker);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", DrawPortraitSlotDebug);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", DrawFaceSlotBoxDebug);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", PrintCacheSlotStatus);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", DisplayVMDebugPanel);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", DrawTaiwaDebugOverlay);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", SendPortraitCommand);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", CallScriptFunctionById);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", DrawTaiwaBrainEffect);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", DoEffectB);

NewsMode* SetNews(void) {
    NewsMode* news = &g_NewsMode;

    news->newsModeActive = 1;
    news->newsDisplayMode = 1;

    return news;
}

void ClearNewsState(void) { ResetTaiwaNewsSystem(); }

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", SetNewsValue);

void LoadKanjiById(s32 kanjiSet) {
    g_CurrentKanjiSet = kanjiSet;
    LoadKanjiTimData(kanjiSet);
}

void ResetPortraitCacheStatus(void) {
    g_CacheSlotStatus[0] = 0;
    D_8019F804 = 0;
    D_8018F004 = 0;
    g_CacheSlotStatus[1] = 0;
    D_8017E804 = 0;
    g_CacheSlotStatus[2] = 0;
}

void OpenMenuById(s32 menuId) {
    g_CurrentMenuRequest = menuId;
    if (menuId < 3) {
        return;
    }
    g_CurrentMenuRequest = 0;
}

void PlayMovie(void) { StartPlayMovie(); }

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", SetupExtendedMovieFlashEffect);

void TriggerMovieFlashEffect(s32 effectParam1, s32 effectParam2) {
    D_80130E38 = effectParam1;
    D_80130E3C = effectParam2;
    g_FunctionTableIndex = 0x14;
    g_SavedScriptState = g_ScriptCurrentState;
}

s32 GetPackedDisplayHeightOffset(void) { return (g_PortraitSlotIndex << 8) | 0x01400000; }

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", ClearScreenAndResetDisplay);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", SetTPageParamForCurrentAndScreenPage);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", AdvanceDebugTextCursor);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", WriteCharToDebugBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", DbgScreenPrintString);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", CheckPortraitCoordinateBounds);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", AdvanceFramesWithDebugUpdate);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", LoadPortraitFileToBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", DispatchPortraitCommandMode);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", InitDrawBufferPortraitAnimTiles);

void StubPortraitCallback1(void) {}

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", ValidateOperandAndLoadPortraitImage);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", ResetPortraitSlotsAndDrawAreas);

void StubPortraitCallback2(void) {}

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", UpdatePortraitSlotVisibility);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", CalculatePortraitSlotScreenOffset);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", PlayPortraitConfirmationSfx);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", PlayPortraitCancelSfx);

// This changes the Portrait slot to state (expresion?) 3
void SetPortraitSlotStateTo3(PortraitSlot* slot) { slot->state = 3; }

void InitPortraitSlotMsgBoxType(PortraitSlot* slot) {
    if (g_MessageBoxType >= 8) {
        g_MessageBoxType = 0;
    }
    slot->msgBoxType = g_MessageBoxType;
}

void ClearPortraitSlotStateAndUploadClut(PortraitSlot* slot) {
    slot->unk36 = 0;
    slot->unk3E = 0;
    UploadFaceClutToVram(slot);
}

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", PreparePortraitSlotAndLoadAsset);

void ResetTaiwaFadeTimers(void) {
    g_TaiwaBarX = 0;
    g_TaiwaState.newsFadeSlot1 = 0;
    g_TaiwaState.newsFadeSlot2 = 0;
}

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", WaitWithDialogueUI);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", PlayDialogueMessage);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", PlaySystemMessage);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", StepGameFrameAndProcessInput);

void DoGame(void) { RunGameLoop(); }
