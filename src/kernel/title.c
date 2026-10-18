#include "common.h"
#include "game.h"

const u32 s_TitleFadeInCharCoordsA[12] = {
    52, 53, 54, 55, 40, 41, 42, 43, 56, 57, 58, 59,
};
const u32 s_TitleFadeInCharCoordsB[11] = {
    20, 21, 22, 23, 8, 9, 10, 11, 24, 25, 26,
};
const u32 s_TitleFadeInCharCoordsC[12] = {
    30, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
};
const u32 s_TitleMenuTransitionData[18] = {
    0x00890059, 0x00000000, 0x00980059, 0x00000001, 0x00A90059, 0x00000002, 0x009D0044, 0x00000003, 0x00A50044,
    0x00000004, 0x00AD0044, 0x00000005, 0x00B50044, 0x00000000, 0x00BD0044, 0x00000001, 0x00C50044, 0x00000002,
};
const u32 s_TitleMenuTimingData[7] = {
    292, 300, 316, 292, 300, 316, 292,
};
const char s_TitleDebugNewlines[] = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
const char s_TitleDebugFlagOn[] = "          Debug Flag ON\n";
const char s_TitleDebugFlagOff[] = "          Debug Flag OFF\n";
const char s_TitleChapterMenu[] = "          Chapter Menu\n";
const char s_TitleNewGame[] = "          New Game\n";
const char s_TitleLoadGame[] = "          Load Game\n";
const char s_TitleConfig[] = "          Config";
const u32 s_TitleAnimAssetConfigA[12] = {
    29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
};
const u32 s_TitleAnimAssetConfigB[12] = {
    256, 320, 384, 448, 512, 576, 640, 704, 512, 576, 640, 704,
};
const u32 s_TitleAnimAssetConfigC[12] = {
    256, 256, 256, 256, 0, 0, 0, 0, 256, 256, 256, 256,
};
const u32 s_TitleTilePrimitiveTable[24] = {
    0x00180000, 0xA0FF0000, 0x00007800, 0x00000000, 0x00180000, 0xA0FF0000, 0x00007AC0, 0x00000001,
    0x0084003A, 0x2D340000, 0x00007B00, 0x00000000, 0x00840026, 0x1010F000, 0x00007B40, 0x00000000,
    0x00180000, 0xA0FF0000, 0x00007800, 0x00000001, 0x00180000, 0xA0FF0000, 0x00007800, 0x00000001,
};
const u32 s_TitleTilePrimitiveOffsets[9] = {
    0x00180000, 0x0000A0FF, 0x00000001, 0x00180000, 0x0000F0FF, 0x00000001, 0x00180000, 0x0000A0FF, 0x00000001,
};

INCLUDE_ASM("asm/jp/nonmatchings/kernel/title", GoToTitleScreen);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/title", FadeInCharactersOnTitleScreen);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/title", UpdateTitleScreenMenuState);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/title", TitleFadeOutAfterSelection);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/title", LoadTitleAnimationAssets);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/title", GTitleTilePrimitiveTable);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/title", TitleScreenFadeIn);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/title", FadeInCharacterOverlay);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/title", AnimateTitleScreenIdleLoop);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/title", DrawTitleScreenDebugOverlay);

s32 LoadDebugTitleScreen(void) { return 0; }

INCLUDE_ASM("asm/jp/nonmatchings/kernel/title", DisplayEndTitle);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/title", AnimateEndTitleFadeIn);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/title", InitEndTitlePrimitives);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/title", AnimateEndTitleFadeOut);
