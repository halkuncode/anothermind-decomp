#include "common.h"

INCLUDE_ASM("asm/jp/nonmatchings/main/title", GoToTitleScreen);

INCLUDE_ASM("asm/jp/nonmatchings/main/title", FadeInCharactersOnTitleScreen);

INCLUDE_ASM("asm/jp/nonmatchings/main/title", UpdateTitleScreenMenuState);

INCLUDE_ASM("asm/jp/nonmatchings/main/title", TitleFadeOutAfterSelection);

INCLUDE_ASM("asm/jp/nonmatchings/main/title", LoadTitleAnimationAssets);

INCLUDE_ASM("asm/jp/nonmatchings/main/title", GTitleTilePrimitiveTable);

INCLUDE_ASM("asm/jp/nonmatchings/main/title", TitleScreenFadeIn);

INCLUDE_ASM("asm/jp/nonmatchings/main/title", FadeInCharacterOverlay);

INCLUDE_ASM("asm/jp/nonmatchings/main/title", AnimateTitleScreenIdleLoop);

INCLUDE_ASM("asm/jp/nonmatchings/main/title", DrawTitleScreenDebugOverlay);

s32 LoadDebugTitleScreen(void) { return 0; }

INCLUDE_ASM("asm/jp/nonmatchings/main/title", DisplayEndTitle);

INCLUDE_ASM("asm/jp/nonmatchings/main/title", AnimateEndTitleFadeIn);

INCLUDE_ASM("asm/jp/nonmatchings/main/title", InitEndTitlePrimitives);

INCLUDE_ASM("asm/jp/nonmatchings/main/title", AnimateEndTitleFadeOut);
