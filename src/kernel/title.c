#include "common.h"
#include "game.h"

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
