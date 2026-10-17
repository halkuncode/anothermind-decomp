#include "common.h"

// keep structs in c file
typedef struct {
    /* 0x00 */ s16 active;
    /* 0x02 */ s16 x;
    /* 0x04 */ s16 y;
    /* 0x06 */ s16 groupId;
    /* 0x08 */ s16 tpage;
    /* 0x0A */ s16 baseX;
    /* 0x0C */ s16 baseY;
    /* 0x0E */ s16 clutId;
    /* 0x10 */ u8 u;
    /* 0x11 */ u8 v;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
} TaiwaTile; // size:0x16

typedef struct {
    /* 0x00 */ s16 state;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 selectedRow;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ s16 boxCount;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 shiftX;
    /* 0x18 */ s16 totalWidth;
    /* 0x1A */ s16 startX;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ u16 defaultWidth;
} TaiwaLayoutState; // size:0x24

typedef struct {
    /* 0x00 */ s16 length;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
} TaiwaSubBar; // size:0x08

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 baseX;
    /* 0x0A */ s16 baseY;
    /* 0x0C */ s16 prevX;
    /* 0x0E */ s16 prevY;
    /* 0x10 */ u16 curX;
    /* 0x12 */ u16 curY;
    /* 0x14 */ u16 width;
    /* 0x16 */ s16 unk16;
} TaiwaBox; // size:0x18

extern s16 g_TaiwaSlot;
extern TaiwaLayoutState g_TaiwaAltRenderMode;
extern u16 g_TaiwaBox1Width;
extern u16 g_TaiwaBox2Width;
extern u16 g_TaiwaBox3Width;
extern u16 g_TaiwaBox4Width;
extern u16 g_TaiwaCharSpacing;
extern TaiwaTile g_TaiwaTileTable[330];
extern u16 g_TaiwaBarX;
extern TaiwaSubBar g_TaiwaSubBar1Length;
extern TaiwaBox g_TaiwaBoxes[10];

void CenterTaiwaChoiceBoxes(void) {
    TaiwaLayoutState* state;
    TaiwaTile* entry;
    TaiwaSubBar* bar;
    s16 total;
    s16 i;
    s16 count;

    if (!g_TaiwaSlot) {
        return;
    }

    state = &g_TaiwaAltRenderMode;
    total = 0;
    if (state->boxCount >= 2) {
        total = g_TaiwaBox1Width;
    }
    if (state->boxCount >= 3) {
        total += g_TaiwaBox2Width;
    }
    if (state->boxCount >= 4) {
        total += g_TaiwaBox3Width;
    }
    if (state->boxCount >= 5) {
        total += g_TaiwaBox4Width;
    }

    count = 4;
    i = total;
    state->totalWidth = total;
    if (!total) {
        i = state->defaultWidth;
        count = 1;
    }

    state->startX = 160 - (s16)((u16)i * g_TaiwaCharSpacing + count * 8) / 2;

    entry = g_TaiwaTileTable;
    count = 0x1000;
    for (i = 0; i < 330; entry++, i++) {
        if (entry->active && entry->groupId >= 100) {
            if (entry->baseX < count) {
                count = entry->baseX;
            }
        }
    }

    state->shiftX = state->startX - count;

    entry = g_TaiwaTileTable;
    for (i = 0; i < 330; entry++, i++) {
        if (entry->active && entry->groupId >= 100) {
            entry->baseX += state->shiftX;
        }
    }

    if (total) {
        g_TaiwaBarX += state->shiftX;
    } else {
        g_TaiwaBarX = state->startX - 4;
    }

    bar = &g_TaiwaSubBar1Length;
    if (bar[0].length) {
        bar[0].length += state->shiftX;
    }
    if (bar[1].length) {
        bar[1].length += state->shiftX;
    }
    if (bar[2].length) {
        bar[2].length += state->shiftX;
    }
}

void ResetTaiwaChoiceBoxes(void) {
    TaiwaLayoutState* state;
    TaiwaTile* entry;
    TaiwaSubBar* bar;
    s16 i;

    if (!g_TaiwaSlot) {
        return;
    }

    state = &g_TaiwaAltRenderMode;
    entry = g_TaiwaTileTable;
    for (i = 0; i < 330; entry++, i++) {
        if (entry->active && entry->groupId >= 100) {
            entry->baseX -= state->shiftX;
        }
    }

    if (state->totalWidth) {
        g_TaiwaBarX -= state->shiftX;
    } else {
        g_TaiwaBarX = state->startX - 4;
    }

    bar = &g_TaiwaSubBar1Length;
    if (bar[0].length) {
        bar[0].length -= state->shiftX;
    }
    if (bar[1].length) {
        bar[1].length -= state->shiftX;
    }
    if (bar[2].length) {
        bar[2].length -= state->shiftX;
    }
}

void SyncTaiwaBoxTilePositions(void) {
    TaiwaBox* box;
    TaiwaTile* tile;
    s32 i;

    box = g_TaiwaBoxes;
    for (i = 0; i < 10; box++, i++) {
        box->curX = box->baseX;
        box->curY = box->baseY;
    }

    tile = g_TaiwaTileTable;
    for (i = 0; i < 330; tile++, i++) {
        if (tile->active && (s16)(u16)tile->groupId >= 100) {
            box = &g_TaiwaBoxes[(s16)tile->groupId / 100];
            if (box->baseX != box->prevX) {
                tile->baseX = box->curX;
                box->curX += g_TaiwaCharSpacing;
            }
            if (box->baseY != box->prevY) {
                tile->baseY = box->curY;
            }
        }
    }

    box = g_TaiwaBoxes;
    for (i = 0; i < 10; box++, i++) {
        box->prevX = box->baseX;
        box->prevY = box->baseY;
    }
}

INCLUDE_ASM("asm/jp/nonmatchings/engine/taiwa_state", CalcTaiwaWordSlotLayout);

INCLUDE_ASM("asm/jp/nonmatchings/engine/taiwa_state", PositionTaiwaSelectionCursor);

INCLUDE_ASM("asm/jp/nonmatchings/engine/taiwa_state", RunDebugSceneJumpMenu);

INCLUDE_ASM("asm/jp/nonmatchings/engine/taiwa_state", ApplyTaiwaSpriteTintAndOffsets);

INCLUDE_ASM("asm/jp/nonmatchings/engine/taiwa_state", UpdateTaiwaChoiceEntry);

INCLUDE_ASM("asm/jp/nonmatchings/engine/taiwa_state", FreePortraitTileSlot);

INCLUDE_ASM("asm/jp/nonmatchings/engine/taiwa_state", RunDebugSaveDataManager);

INCLUDE_ASM("asm/jp/nonmatchings/engine/taiwa_state", ParseTaiwaSentenceAndConjugation);

INCLUDE_ASM("asm/jp/nonmatchings/engine/taiwa_state", CalcTaiwaChoiceYPositions);

INCLUDE_ASM("asm/jp/nonmatchings/engine/taiwa_state", RunDebugVramViewer);

INCLUDE_ASM("asm/jp/nonmatchings/engine/taiwa_state", RunDebugMovieViewer);

INCLUDE_ASM("asm/jp/nonmatchings/engine/taiwa_state", ProcessTaiwaStateMachine);
