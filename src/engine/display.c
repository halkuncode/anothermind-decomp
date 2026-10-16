#include "common.h"

INCLUDE_ASM("asm/jp/nonmatchings/engine/display", SubmitDebugPrimitiveGrid);

INCLUDE_ASM("asm/jp/nonmatchings/engine/display", DrawTaiwaWordHighlight);

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
