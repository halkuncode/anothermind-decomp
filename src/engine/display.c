#include "common.h"
#include <libgpu.h>
INCLUDE_ASM("asm/jp/nonmatchings/engine/display", SubmitDebugPrimitiveGrid);

typedef struct {
    /* 0x00 */ s16 active;
    /* 0x02 */ u16 primIndex;
    /* 0x04 */ u16 cols;
    /* 0x06 */ u16 rows;
    /* 0x08 */ u8 pad08[4];
    /* 0x0C */ s16 x;
    /* 0x0E */ s16 y;
    /* 0x10 */ u16 clut;
    /* 0x12 */ u8 semiTrans;
    /* 0x13 */ u8 pad13;
} TaiwaHighlightSlot; // size:0x14

void SetShadeTexFlag(void* p, s32 t);
void SetPrimitiveSemiTrans(void* p, s32 abe);

extern s32 g_ActiveDrawContext;
extern TaiwaHighlightSlot g_TaiwaState[];

void DrawTaiwaWordHighlight(u_long* ot, s32 slotIndex) {
    TaiwaHighlightSlot* slot = &g_TaiwaState[(u16)slotIndex];

    if (slot->active != 0) {
        s32 row;
        s32 col;
        SPRT_16* sprt = (SPRT_16*)((u8*)g_ActiveDrawContext + (slot->primIndex * 0x10 + 0x51C0));

        for (row = 0; row < slot->rows * 16; row += 16) {
            for (col = 0; col < slot->cols * 16; col += 16) {
                SetShadeTexFlag(sprt, 0);
                SetPrimitiveSemiTrans(sprt, slot->semiTrans);
                sprt->x0 = slot->x + col;
                sprt->y0 = slot->y + row;
                sprt->clut = slot->clut;
                addPrim(ot, sprt);
                sprt++;
            }
        }

        addPrim(ot, (u8*)g_ActiveDrawContext + ((u16)slotIndex * 12 + 0x9CC0));
    }
}

INCLUDE_ASM("asm/jp/nonmatchings/engine/display", DrawTaiwaHighlightTileGrid);

INCLUDE_ASM("asm/jp/nonmatchings/engine/display", AddTaiwaTileGridToOrderingTable);

INCLUDE_ASM("asm/jp/nonmatchings/engine/display", DbgScreenPrintInt);

INCLUDE_ASM("asm/jp/nonmatchings/engine/display", DbgScreenPrintHex);

INCLUDE_ASM("asm/jp/nonmatchings/engine/display", FindAvailableCacheSlot);

INCLUDE_ASM("asm/jp/nonmatchings/engine/display", CacheFile);

INCLUDE_ASM("asm/jp/nonmatchings/engine/display", HandleYOSICommand);

INCLUDE_ASM("asm/jp/nonmatchings/engine/display", CheckByuuFadeEffectComplete);

INCLUDE_ASM("asm/jp/nonmatchings/engine/display", GetValidPortraitCacheSlot);

INCLUDE_ASM("asm/jp/nonmatchings/engine/display", LoadKanjiBlockToVRAM);

INCLUDE_ASM("asm/jp/nonmatchings/engine/display", SelectActivePortraitRenderSlot);

INCLUDE_ASM("asm/jp/nonmatchings/engine/display", InitGpuAndCdromEvents);

INCLUDE_ASM("asm/jp/nonmatchings/engine/display", InitDoubleBufferDrawEnvs);

INCLUDE_ASM("asm/jp/nonmatchings/engine/display", SubmitFrameOrderingTable);

INCLUDE_ASM("asm/jp/nonmatchings/engine/display", StubbedOnFrameUpdate);

INCLUDE_ASM("asm/jp/nonmatchings/engine/display", StepFrameAndSwapBuffers);
