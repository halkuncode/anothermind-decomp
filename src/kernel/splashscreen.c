#include "common.h"
#include "libgpu.h"

typedef struct LogoFadeBuffer {
    DRAWENV draw;
    DISPENV disp;
    u_long ot[1];
    SPRT sprt[2];
} LogoFadeBuffer;

INCLUDE_ASM("asm/jp/nonmatchings/kernel/splashscreen", DisplayChapterTitle);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/splashscreen", RunChapterTitleFadeIn);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/splashscreen", DrawLogoLines);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/splashscreen", AnimateChapterTitleLogoEffect);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/splashscreen", DrawChapterTitleOverlayPrimitives);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/splashscreen", InitChapterTitlePrimitives);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/splashscreen", LoadChapterTitleTextures);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/splashscreen", FadeInLogo);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/splashscreen", FadeOutChapterTitleLogoEffect);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/splashscreen", DrawChapterTitleLayoutA);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/splashscreen", DrawChapterTitleLayoutB);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/splashscreen", DrawChapterTitleLayoutC);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/splashscreen", SubmitChapterTitleDrawPrimitives);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/splashscreen", ShowSquaresoftLogo);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/splashscreen", LoadSquaresoftLogo);

void SetFadePrimitiveColor(LogoFadeBuffer* buf, s16 color) {
    buf->sprt[0].r0 = color;
    buf->sprt[0].g0 = color;
    buf->sprt[0].b0 = color;
    buf->sprt[1].r0 = color;
    buf->sprt[1].g0 = color;
    buf->sprt[1].b0 = color;
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/splashscreen", InitFadeInPrimitives);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/splashscreen", EnqueueFadeInPrimitives);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/splashscreen", GoToTitleScreen);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/splashscreen", FadeInCharactersOnTitleScreen);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/splashscreen", UpdateTitleScreenMenuState);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/splashscreen", TitleFadeOutAfterSelection);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/splashscreen", LoadTitleAnimationAssets);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/splashscreen", GTitleTilePrimitiveTable);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/splashscreen", TitleScreenFadeIn);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/splashscreen", FadeInCharacterOverlay);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/splashscreen", AnimateTitleScreenIdleLoop);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/splashscreen", DrawTitleScreenDebugOverlay);

s32 LoadDebugTitleScreen(void) { return 0; }

INCLUDE_ASM("asm/jp/nonmatchings/kernel/splashscreen", DisplayEndTitle);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/splashscreen", AnimateEndTitleFadeIn);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/splashscreen", InitEndTitlePrimitives);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/splashscreen", AnimateEndTitleFadeOut);
