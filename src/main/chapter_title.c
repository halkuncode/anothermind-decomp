#include "common.h"
#include "libgpu.h"

typedef struct LogoFadeBuffer {
    DRAWENV draw;
    DISPENV disp;
    u_long ot[1];
    SPRT sprt[2];
} LogoFadeBuffer;

INCLUDE_ASM("asm/jp/nonmatchings/main/chapter_title", DisplayChapterTitle);

INCLUDE_ASM("asm/jp/nonmatchings/main/chapter_title", RunChapterTitleFadeIn);

INCLUDE_ASM("asm/jp/nonmatchings/main/chapter_title", DrawLogoLines);

INCLUDE_ASM("asm/jp/nonmatchings/main/chapter_title", AnimateChapterTitleLogoEffect);

INCLUDE_ASM("asm/jp/nonmatchings/main/chapter_title", func_80016CDC);

INCLUDE_ASM("asm/jp/nonmatchings/main/chapter_title", InitChapterTitlePrimitives);

INCLUDE_ASM("asm/jp/nonmatchings/main/chapter_title", LoadChapterTitleTextures);

INCLUDE_ASM("asm/jp/nonmatchings/main/chapter_title", FadeInLogo);

INCLUDE_ASM("asm/jp/nonmatchings/main/chapter_title", FadeOutChapterTitleLogoEffect);

INCLUDE_ASM("asm/jp/nonmatchings/main/chapter_title", func_800173E4);

INCLUDE_ASM("asm/jp/nonmatchings/main/chapter_title", func_800174B0);

INCLUDE_ASM("asm/jp/nonmatchings/main/chapter_title", func_80017518);

INCLUDE_ASM("asm/jp/nonmatchings/main/chapter_title", SubmitChapterTitleDrawPrimitives);

INCLUDE_ASM("asm/jp/nonmatchings/main/chapter_title", ShowSquaresoftLogo);

INCLUDE_ASM("asm/jp/nonmatchings/main/chapter_title", LoadSquaresoftLogo);

void SetFadePrimitiveColor(LogoFadeBuffer* buf, s16 color) {
    buf->sprt[0].r0 = color;
    buf->sprt[0].g0 = color;
    buf->sprt[0].b0 = color;
    buf->sprt[1].r0 = color;
    buf->sprt[1].g0 = color;
    buf->sprt[1].b0 = color;
}

INCLUDE_ASM("asm/jp/nonmatchings/main/chapter_title", InitFadeInPrimitives);

INCLUDE_ASM("asm/jp/nonmatchings/main/chapter_title", EnqueueFadeInPrimitives);
