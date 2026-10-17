#include "common.h"

// keep structs in c file
typedef struct {
    /* 0x00 */ u8 pad00[2];
    /* 0x02 */ s16 state;
    /* 0x04 */ u8 pad04[0x22 - 0x04];
    /* 0x22 */ s16 msgBoxType;
    /* 0x24 */ u8 pad24[0x36 - 0x24];
    /* 0x36 */ s16 unk36;
    /* 0x38 */ u8 pad38[0x3E - 0x38];
    /* 0x3E */ s16 unk3E;
    /* 0x40 */ u8 pad40[0x44 - 0x40];
} PortraitSlot; // size:0x44

typedef struct {
    /* 0x00 */ s16 newsModeActive;
    /* 0x02 */ s16 newsDisplayMode;
} NewsMode; // size:0x04

typedef struct {
    /* 0x000 */ u8 highlightSlotEnabled;
    /* 0x001 */ u8 pad01[0x17C - 0x001];
    /* 0x17C */ s16 newsFadeSlot1;
    /* 0x17E */ u8 pad17E[0x190 - 0x17E];
    /* 0x190 */ s16 newsFadeSlot2;
} TaiwaState; // size:0x192

typedef struct {
    /* 0x00 */ u8 pad00[4];
    /* 0x04 */ s16 mode;
    /* 0x06 */ u8 pad06[0x18 - 0x06];
} DrawBufferParam; // size:0x18

extern s16 g_DebugViewMode;
extern u8 g_MessageBoxType;
extern s16 g_CacheSlotStatus[];
extern u8 g_DebugTextBuffer[];
extern s32 g_DrawBufferIndex;
extern s16 g_Sss;
extern s32 g_DebugDisplayPageId;
extern s32 g_DebugTextCursorOffset;
extern u16 g_SavedScriptState;
extern u16 g_ScriptCurrentState;
extern s16 g_TaiwaBarX;
extern s16 g_ValidFunctionArgument;
extern s32 g_FunctionTableIndex;
extern s16 g_DemoFrameControlFlag;
extern s16 g_ScriptTimingFrameCount;
extern s16 g_CurrentMenuRequest;
extern s16 g_DebugMemoryCardSaveHeaderCount;
extern s16 g_DebugMemoryCardSaveBlockCount;
extern NewsMode g_NewsMode;
extern s16 g_SrlFlag;
extern s16 g_SrlShow;
extern s16 g_SrlFile;
extern s16 g_CurrentKanjiSet;
extern DrawBufferParam g_DrawBufferParams[];
extern PortraitSlot g_PortraitSlots[];
extern PortraitSlot D_80130D94;
extern s32 g_MoviePlaybackId;
extern s32 g_MoviePlaybackMode;
extern TaiwaState g_TaiwaState;
extern s16 g_DebugDrawPrimitiveIndex;
extern s16 g_PortraitCacheSlot2Status;
extern s16 g_PortraitCacheSlot1Status;
extern s16 g_PortraitCacheSlot0Status;

void DisplaySystemDebugPanel(void);
char* GetFilename(void);
void StartPlayMovie(void);
void SetupDebugOptionMenu(void);
void DbgScreenPrintInt(s32);
void DbgScreenPrintHex(s32);
void LoadKanjiTimData(s32);
void UploadFaceClutToVram(PortraitSlot*);
void ResetNewsSystem(void);
void DispatchInGameMenu(void);
void RunGameLoop(void);
void DrawDebugHorizontalCursorMarker(void);
void DrawChrSlotDebug(PortraitSlot*);
void DrawChrMsgBoxDebug(PortraitSlot*, s32);
void PrintCacheSlotStatus(s32);
void DisplayVMDebugPanel(void);

static inline void AdvanceDebugCursor(void) {
    s32 row = (g_DebugTextCursorOffset / DEBUG_TEXT_COLUMNS) + 1;
    if (row < DEBUG_TEXT_MAX_ROWS) {
        g_DebugTextCursorOffset = row * DEBUG_TEXT_COLUMNS;
    } else {
        g_DebugTextCursorOffset = DEBUG_TEXT_BOTTOM_ROW_OFFSET;
    }
}

static inline void WriteCharToDebugBuffer(s16 c) {
    if (c == '\n') {
        AdvanceDebugCursor();
    } else {
        if (g_DebugTextCursorOffset < DEBUG_TEXT_BUFFER_SIZE) {
            if ((u16)(c - 'a') < 26) {
                c -= 0x20;
            }
            g_DebugTextBuffer[g_DebugTextCursorOffset] = c;
            g_DebugTextCursorOffset++;
        }
    }
}

static inline void PrintDebugString(const char* str) {
    while (*str) {
        WriteCharToDebugBuffer(*str++);
    }
}

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

const char s_DebugMarkerA[] = "A";
const char s_DebugMarkerSpace[] = " ";
const char s_DebugChrFilePrefix[] = "CHR FILE ";
const char s_DebugDigit0[] = "0";
const char s_DebugDigit1[] = "1";
const char s_DebugSizePrefix[] = "SIZE=";
const char s_DebugComma[] = ",";
const char s_DebugXyPrefix[] = "XY  =";
const char s_DebugSpeedPrefix[] = "sped=";
const char s_DebugNormalSuffix[] = " / NORMAL";
const char s_DebugNextSuffix[] = " / NEXT";
const char s_DebugChrPrefix[] = "CHR ";
const char s_DebugMessagePrefix[] = " MESSAGE\n";
const char s_CacheStatusEmptyMarker[] = "- ";
const char s_CacheStatusWaitingMarker[] = "W ";
const char s_CacheStatusLoadedMarker[] = "L ";
const char s_CacheStatusCachedMarker[] = "C ";
const char s_DebugSpcNoLabel[] = "spcno  ";
const char s_DebugSlash[] = "/";
const char s_DebugMcLabel[] = "  mc.";
const char s_DebugSssLabel[] = "sss    ";
const char s_DebugSrlFlagLabel[] = "srl.flag ";
const char s_DebugSrlShowLabel[] = "srl.show ";
const char s_DebugSrlFileLabel[] = "srl.file ";
const char s_DebugCacheHeader[] = "CACHE \n";
const char s_DebugSceneScriptHeader[] = "SCEEN SCRIPT\n";
const char s_DebugBgFilePrefix[] = "BG FILE ";
const char s_Debug8BitMode[] = "/ 8BIT";
const char s_Debug16BitMode[] = "/ 16BIT";

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", DrawDebugHorizontalCursorMarker);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", DrawChrSlotDebug);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", DrawChrMsgBoxDebug);

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", PrintCacheSlotStatus);

void DisplayVMDebugPanel(void) {
    // Screen primitive packet count: active OT packets vs. hardware limit (0x4B = 75)
    PrintDebugString(s_DebugSpcNoLabel);
    DbgScreenPrintInt(g_DebugDrawPrimitiveIndex);
    PrintDebugString(s_DebugSlash);
    DbgScreenPrintInt(DEBUG_MAX_DRAW_PRIMITIVES);

    // Memory Card diagnostics: available save headers and detected save block count
    PrintDebugString(s_DebugMcLabel);
    DbgScreenPrintInt(g_DebugMemoryCardSaveHeaderCount);
    PrintDebugString(s_DebugSlash);
    DbgScreenPrintInt(g_DebugMemoryCardSaveBlockCount);
    AdvanceDebugCursor();

    // System Sub-State: VM engine internal execution sub-state (rendered in hex)
    PrintDebugString(s_DebugSssLabel);
    DbgScreenPrintHex(g_Sss);
    AdvanceDebugCursor();

    // Scenario Script (srl) Reel execution state:
    // - srl.flag: Active scenario branch condition / state flag
    // - srl.show: Script display visibility state (layer toggle)
    // - srl.file: Currently loaded scenario script asset ID (.ZZS)
    PrintDebugString(s_DebugSrlFlagLabel);
    DbgScreenPrintInt(g_SrlFlag);
    AdvanceDebugCursor();
    PrintDebugString(s_DebugSrlShowLabel);
    DbgScreenPrintInt(g_SrlShow);
    AdvanceDebugCursor();
    PrintDebugString(s_DebugSrlFileLabel);
    DbgScreenPrintInt(g_SrlFile);
    AdvanceDebugCursor();

    // Script cache slots: display status script cache slots 0, 1, and 2
    PrintDebugString(s_DebugCacheHeader);
    PrintCacheSlotStatus(0);
    PrintCacheSlotStatus(1);
    PrintCacheSlotStatus(2);
    AdvanceDebugCursor();

    // Launch interactive Page 0 VM debug options menu (step, watch, memory flags)
    SetupDebugOptionMenu();
}

void DrawDebugOverlay(void) {
    char* buf;
    s32 i;

    g_DebugTextCursorOffset = 0;
    buf = (char*)g_DebugTextBuffer;
    for (i = 0; i < DEBUG_TEXT_BUFFER_SIZE; i++) {
        *buf++ = ' ';
    }

    if (g_DebugViewMode == DEBUG_VIEW_VM) {
        DisplayVMDebugPanel();
    }
    if (g_DebugViewMode == DEBUG_VIEW_SYSTEM) {
        DisplaySystemDebugPanel();
    }

    if (g_DebugDisplayPageId == DEBUG_PAGE_SCENE_SCRIPT) {
        PrintDebugString(s_DebugSceneScriptHeader);
        DrawDebugHorizontalCursorMarker();
    }

    if (g_DebugDisplayPageId == DEBUG_PAGE_BACKGROUND) {
        s32 mode;

        PrintDebugString(s_DebugBgFilePrefix);
        DbgScreenPrintInt(g_ValidFunctionArgument);
        mode = g_DrawBufferParams[g_DrawBufferIndex].mode;
        if (mode == COLOR_MODE_8BIT) {
            PrintDebugString(s_Debug8BitMode);
        }
        if (mode == COLOR_MODE_16BIT) {
            PrintDebugString(s_Debug16BitMode);
        }
        AdvanceDebugCursor();
        PrintDebugString(GetFilename());
        AdvanceDebugCursor();
        DrawDebugHorizontalCursorMarker();
    }

    if (g_DebugDisplayPageId == DEBUG_PAGE_CHR_SLOT0) {
        DrawChrSlotDebug(&g_PortraitSlots[0]);
    }
    if (g_DebugDisplayPageId == DEBUG_PAGE_CHR_SLOT1) {
        DrawChrSlotDebug(&D_80130D94);
    }
    if (g_DebugDisplayPageId == DEBUG_PAGE_MSG_BOX_SLOT0) {
        DrawChrMsgBoxDebug(&g_PortraitSlots[0], 0);
    }
    if (g_DebugDisplayPageId == DEBUG_PAGE_MSG_BOX_SLOT1) {
        DrawChrMsgBoxDebug(&D_80130D94, 1);
    }

    if (g_ScriptTimingFrameCount && !g_DemoFrameControlFlag) {
        DispatchInGameMenu();
    }
}

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

void ClearNewsState(void) { ResetNewsSystem(); }

INCLUDE_ASM("asm/jp/nonmatchings/engine/game", SetNewsValue);

void LoadKanjiById(s32 kanjiSet) {
    g_CurrentKanjiSet = kanjiSet;
    LoadKanjiTimData(kanjiSet);
}

void ResetPortraitCacheStatus(void) {
    g_CacheSlotStatus[0] = 0;
    g_PortraitCacheSlot0Status = 0;
    g_PortraitCacheSlot1Status = 0;
    g_CacheSlotStatus[1] = 0;
    g_PortraitCacheSlot2Status = 0;
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
    g_MoviePlaybackId = effectParam1;
    g_MoviePlaybackMode = effectParam2;
    g_FunctionTableIndex = 0x14;
    g_SavedScriptState = g_ScriptCurrentState;
}

s32 GetPackedDisplayHeightOffset(void) { return (g_DrawBufferIndex << 8) | 0x01400000; }

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
