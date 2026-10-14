#include "common.h"

INCLUDE_ASM("asm/jp/nonmatchings/engine/vram_cache", SubmitDebugPrimitiveGrid);

INCLUDE_ASM("asm/jp/nonmatchings/engine/vram_cache", DrawTaiwaWordHighlight);

INCLUDE_ASM("asm/jp/nonmatchings/engine/vram_cache", DrawTaiwaHighlightTileGrid);

INCLUDE_ASM("asm/jp/nonmatchings/engine/vram_cache", AddTaiwaTileGridToOrderingTable);

INCLUDE_ASM("asm/jp/nonmatchings/engine/vram_cache", DbgScreenPrintInt);

INCLUDE_ASM("asm/jp/nonmatchings/engine/vram_cache", DbgScreenPrintHex);

INCLUDE_ASM("asm/jp/nonmatchings/engine/vram_cache", FindAvailableCacheSlot);

INCLUDE_ASM("asm/jp/nonmatchings/engine/vram_cache", CacheFile);

INCLUDE_ASM("asm/jp/nonmatchings/engine/vram_cache", HandleYOSICommand);

INCLUDE_ASM("asm/jp/nonmatchings/engine/vram_cache", CheckByuuFadeEffectComplete);

INCLUDE_ASM("asm/jp/nonmatchings/engine/vram_cache", GetValidPortraitCacheSlot);

INCLUDE_ASM("asm/jp/nonmatchings/engine/vram_cache", LoadKanjiBlockToVRAM);

INCLUDE_ASM("asm/jp/nonmatchings/engine/vram_cache", SelectActivePortraitRenderSlot);

INCLUDE_ASM("asm/jp/nonmatchings/engine/vram_cache", InitGpuAndCdromEvents);

INCLUDE_ASM("asm/jp/nonmatchings/engine/vram_cache", InitDoubleBufferDrawEnvs);

INCLUDE_ASM("asm/jp/nonmatchings/engine/vram_cache", SubmitFrameOrderingTable);

INCLUDE_ASM("asm/jp/nonmatchings/engine/vram_cache", StubbedOnFrameUpdate);

INCLUDE_ASM("asm/jp/nonmatchings/engine/vram_cache", StepFrameAndSwapBuffers);

INCLUDE_ASM("asm/jp/nonmatchings/engine/vram_cache", LoadTimToVram);

INCLUDE_ASM("asm/jp/nonmatchings/engine/vram_cache", LoadPortraitImageToSlot);

INCLUDE_ASM("asm/jp/nonmatchings/engine/vram_cache", LoadTimAssetToVram);

INCLUDE_ASM("asm/jp/nonmatchings/engine/vram_cache", LoadPortraitAssetToSlot);

INCLUDE_ASM("asm/jp/nonmatchings/engine/vram_cache", LoadKanjiTimImages);

INCLUDE_ASM("asm/jp/nonmatchings/engine/vram_cache", Load8x8DebugFont);

INCLUDE_ASM("asm/jp/nonmatchings/engine/vram_cache", LoadBrainGraphic);
