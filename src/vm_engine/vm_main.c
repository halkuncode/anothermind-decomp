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

extern s16 g_TaiwaBarX;
extern TaiwaState g_TaiwaState;
extern NewsMode g_NewsMode;
extern s16 g_CurrentKanjiSet;
extern s16 g_CurrentMenuRequest;
extern s32 g_PortraitSlotIndex;
extern u8 g_MessageBoxType;

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", RunSaveLoadMenu);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", VerifyMemoryCardSlots);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", RunConfigMenu);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", RunDialogueHistoryMenu);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", ResetMenuSelectionState);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", ProcessSaveConfirmation);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", TrySaveGameToMemoryCard);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", FadeInMenuUI);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", FadeOutMenuUI);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", UpdateMenuEffectState);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", LoadChapterSceneBackground);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", UpdateInGameMenuTransitions);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", DispatchInGameMenu);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", RunGameLoop);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", RenderEngineDebugAndUI);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", ResetAndSubmitDebugOverlayPrimitives);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", ResetVMEngineRuntimeState);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", DrawDebugHorizontalCursorMarker);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", DrawPortraitSlotDebug);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", DrawFaceSlotBoxDebug);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", PrintCacheSlotStatus);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", DisplayVMDebugPanel);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", DrawTaiwaDebugOverlay);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", SendPortraitCommand);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", CallScriptFunctionById);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", DrawTaiwaBrainEffect);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", DoEffectB);

NewsMode* SetNews(void) {
    NewsMode* news = &g_NewsMode;

    news->newsModeActive = 1;
    news->newsDisplayMode = 1;

    return news;
}

void ClearNewsState(void) { ResetNewsSystem(); }

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", SetNewsValue);

void LoadKanjiById(s32 kanjiSet) {
    g_CurrentKanjiSet = kanjiSet;
    LoadKanjiTimData(kanjiSet);
}

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", ResetPortraitCacheStatus);

void OpenMenuById(s32 menuId) {
    g_CurrentMenuRequest = menuId;
    if (menuId < 3) {
        return;
    }
    g_CurrentMenuRequest = 0;
}

void PlayMovie(void) { StartPlayMovie(); }

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", SetupExtendedMovieFlashEffect);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", TriggerMovieFlashEffect);

s32 GetPackedDisplayHeightOffset(void) { return (g_PortraitSlotIndex << 8) | 0x01400000; }

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", ClearScreenAndResetDisplay);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", SetTPageParamForCurrentAndScreenPage);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", AdvanceDebugTextCursor);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", WriteCharToDebugBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", DbgScreenPrintString);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", CheckPortraitCoordinateBounds);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", AdvanceFramesWithDebugUpdate);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", LoadPortraitFileToBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", DispatchPortraitCommandMode);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", InitDrawBufferPortraitAnimTiles);

void StubPortraitCallback1(void) {}

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", ValidateOperandAndLoadPortraitImage);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", ResetPortraitSlotsAndDrawAreas);

void StubPortraitCallback2(void) {}

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", UpdatePortraitSlotVisibility);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", CalculatePortraitSlotScreenOffset);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", PlayPortraitConfirmationSfx);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", PlayPortraitCancelSfx);

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
    UploadPortraitClutToVram(slot);
}

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", PreparePortraitSlotAndLoadAsset);

void ResetTaiwaFadeTimers(void) {
    g_TaiwaBarX = 0;
    g_TaiwaState.newsFadeSlot1 = 0;
    g_TaiwaState.newsFadeSlot2 = 0;
}

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", WaitWithDialogueUI);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", PlayDialogueMessage);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", PlaySystemMessage);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/vm_main", StepGameFrameAndProcessInput);

void DoGame(void) { RunGameLoop(); }
