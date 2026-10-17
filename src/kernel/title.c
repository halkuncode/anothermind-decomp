#include "common.h"
#include "game.h"

const u32 s_TitleFadeInCharCoordsA[12] = {
    0x00000034, 0x00000035, 0x00000036, 0x00000037, 0x00000028, 0x00000029,
    0x0000002A, 0x0000002B, 0x00000038, 0x00000039, 0x0000003A, 0x0000003B,
};
const u32 s_TitleFadeInCharCoordsB[11] = {
    0x00000014, 0x00000015, 0x00000016, 0x00000017, 0x00000008, 0x00000009,
    0x0000000A, 0x0000000B, 0x00000018, 0x00000019, 0x0000001A,
};
const u32 s_TitleFadeInCharCoordsC[12] = {
    0x0000001E, 0x00000004, 0x00000004, 0x00000004, 0x00000004, 0x00000004,
    0x00000004, 0x00000004, 0x00000004, 0x00000004, 0x00000004, 0x00000004,
};
const u32 s_TitleMenuTransitionData[18] = {
    0x00890059, 0x00000000, 0x00980059, 0x00000001, 0x00A90059, 0x00000002, 0x009D0044, 0x00000003, 0x00A50044,
    0x00000004, 0x00AD0044, 0x00000005, 0x00B50044, 0x00000000, 0x00BD0044, 0x00000001, 0x00C50044, 0x00000002,
};
const u32 s_TitleMenuTimingData[7] = {
    0x00000124, 0x0000012C, 0x0000013C, 0x00000124, 0x0000012C, 0x0000013C, 0x00000124,
};
const char s_TitleDebugNewlines[] = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
const char s_TitleDebugFlagOn[] = "          Debug Flag ON\n";
const char s_TitleDebugFlagOff[] = "          Debug Flag OFF\n";
const char s_TitleChapterMenu[] = "          Chapter Menu\n";
const char s_TitleNewGame[] = "          New Game\n";
const char s_TitleLoadGame[] = "          Load Game\n";
const char s_TitleConfig[] = "          Config";
const u32 s_TitleAnimAssetConfigA[12] = {
    0x0000001D, 0x0000001E, 0x0000001F, 0x00000020, 0x00000021, 0x00000022,
    0x00000023, 0x00000024, 0x00000025, 0x00000026, 0x00000027, 0x00000028,
};
const u32 s_TitleAnimAssetConfigB[12] = {
    0x00000100, 0x00000140, 0x00000180, 0x000001C0, 0x00000200, 0x00000240,
    0x00000280, 0x000002C0, 0x00000200, 0x00000240, 0x00000280, 0x000002C0,
};
const u32 s_TitleAnimAssetConfigC[12] = {
    0x00000100, 0x00000100, 0x00000100, 0x00000100, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000100, 0x00000100, 0x00000100, 0x00000100,
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
