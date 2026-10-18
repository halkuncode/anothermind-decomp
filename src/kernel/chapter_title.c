#include "common.h"
#include "game.h"
#include "libgpu.h"

#define FRAMEBUFFER_HEIGHT (SCREEN_HEIGHT * 2) // 480

// Squaresoft logo fade animation parameters
#define LOGO_FADE_STEPS 0x43 // 67 frames
#define LOGO_COLOR_STEP 2
#define LOGO_COLOR_MAX 0x80
#define LOGO_COLOR_MASK 0xFFFE
#define LOGO_TPAGE_MODE 2 // 16-bit direct color

#define LOGO_FADE_BUFFER_SIZE 0xCC

typedef struct {
    /* 0x00 */ DRAWENV draw;
    /* 0x5C */ DISPENV disp;
    /* 0x70 */ u_long ot[1];
    /* 0x74 */ SPRT sprt[2];
    /* 0x9C */ u8 pad9C[LOGO_FADE_BUFFER_SIZE - 0x9C];
} LogoFadeBuffer; // size:0xCC

const u32 s_LogoEffectAnimData[15] = {
    0x00100000, 0x000014A0, 0x00A0FFFC, 0x14A00010, 0xFFFC0000, 0x009C0000, 0x000214A0, 0x00A000B0,
    0x14A0009C, 0x00B00002, 0x000000DC, 0x0001E064, 0x00000140, 0xE0640000, 0xFF9C0003,
};
const u32 s_ChapterTitlePrimitiveData1[20] = {
    0x00100000, 0xA0C00000, 0x00000000, 0x00000000, 0x00100080, 0xA0C00000, 0x00000000,
    0x00000000, 0x00240064, 0x78780000, 0x00000000, 0x00000000, 0x00680076, 0x10400000,
    0x00007800, 0x00000000, 0x0078009A, 0x10400040, 0x00007800, 0x00000000,
};
const u32 s_ChapterTitlePrimitiveData2[39] = {
    0x00000000, 0x00002878, 0x00000000, 0x00000000, 0x00002878, 0x00000000, 0x00000000, 0x00001078,
    0x00000000, 0x00000000, 0x00002878, 0x00000000, 0x00000000, 0x00000878, 0x00000000, 0x00000000,
    0x00001478, 0x00000000, 0x00000000, 0x00001478, 0x00000000, 0x00000000, 0x00001478, 0x00000000,
    0x00000000, 0x00001478, 0x00000000, 0x00000000, 0x00001478, 0x00000000, 0x00000000, 0x00001478,
    0x00000000, 0x00000000, 0x00001478, 0x00000000, 0x00000000, 0x00001478, 0x00000000,
};
// Chapter Title movie start frame offsets for Chapters 1-10 (-1 = no movie offset)
const s32 s_ChapterTitleTextureConfigA[10] = {
    -1, 227, 318, 447, 633, 660, 590, 950, -1, 589,
};
// Chapter Title sound/movie stream IDs for Chapters 1-10
const u32 s_ChapterTitleTextureConfigB[10] = {
    11, 12, 13, 14, 15, 16, 17, 18, 19, 17,
};
// Chapter Title texture IDs for Chapters 1-10
const u32 s_ChapterTitleTextureConfigC[10] = {
    20, 21, 22, 23, 24, 25, 26, 27, 28, 26,
};

INCLUDE_ASM("asm/jp/nonmatchings/kernel/chapter_title", DisplayChapterTitle);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/chapter_title", RunChapterTitleFadeIn);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/chapter_title", DrawLogoLines);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/chapter_title", AnimateChapterTitleLogoEffect);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/chapter_title", DrawChapterTitleOverlayPrimitives);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/chapter_title", InitChapterTitlePrimitives);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/chapter_title", LoadChapterTitleTextures);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/chapter_title", FadeInLogo);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/chapter_title", FadeOutChapterTitleLogoEffect);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/chapter_title", DrawChapterTitleLayoutA);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/chapter_title", DrawChapterTitleLayoutB);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/chapter_title", DrawChapterTitleLayoutC);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/chapter_title", SubmitChapterTitleDrawPrimitives);

void LoadProgdata(s32 fileId, s32 groupId);
void LoadSquaresoftLogo(void);
void InitFadeInPrimitives(LogoFadeBuffer* buf);
void EnqueueFadeInPrimitives(LogoFadeBuffer* buf);
void SetFadePrimitiveColor(LogoFadeBuffer* buf, s32 color);

void ShowSquaresoftLogo(void) {
    LogoFadeBuffer buf[2];
    RECT rect;
    LogoFadeBuffer* activeBuf;
    u_long* ot;
    s32 i = 0;

    SetDispMask(0);
    SetDefDrawEnv(&buf[0].draw, 0, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
    SetDefDrawEnv(&buf[1].draw, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    SetDefDispEnv(&buf[1].disp, 0, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
    SetDefDispEnv(&buf[0].disp, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    LoadSquaresoftLogo();
    InitFadeInPrimitives(&buf[0]);
    InitFadeInPrimitives(&buf[1]);

    rect.x = 0;
    rect.y = 0;
    rect.w = SCREEN_WIDTH;
    rect.h = FRAMEBUFFER_HEIGHT;
    ClearImage(&rect, 0, 0, 0);
    DrawSync(0);
    SetDispMask(1);

    for (i = 0; i < LOGO_FADE_STEPS; i++) {
        s32 color;
        activeBuf = (activeBuf == buf) ? &buf[1] : buf;
        ot = activeBuf->ot;
        ClearOTag(ot, 1);
        color = i * LOGO_COLOR_STEP;
        if ((u16)color >= LOGO_COLOR_MAX) {
            color = LOGO_COLOR_MAX;
        }
        SetFadePrimitiveColor(activeBuf, color & LOGO_COLOR_MASK);
        EnqueueFadeInPrimitives(activeBuf);
        DrawSync(0);
        VSync(0);
        PutDispEnv(&activeBuf->disp);
        PutDrawEnv(&activeBuf->draw);
        DrawOTag(ot);
    }
    DrawSync(0);
}

void LoadSquaresoftLogo(void) {
    TIM_IMAGE sp20;

    LoadProgdata(SQUARE_TIM, DIR_SYSTEM);
    OpenTIM((u_long*)PROGDATA_UNPACK_ADDR);
    ReadTIM(&sp20);
    LoadTPage(sp20.paddr, LOGO_TPAGE_MODE, 0, SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void SetFadePrimitiveColor(LogoFadeBuffer* buf, s32 color) {
    buf->sprt[0].r0 = color;
    buf->sprt[0].g0 = color;
    buf->sprt[0].b0 = color;
    buf->sprt[1].r0 = color;
    buf->sprt[1].g0 = color;
    buf->sprt[1].b0 = color;
}

const u32 s_FadeInSpriteTemplates[8] = {
    0x00000000, 0xF0C00000, 0x00000000, 0x00000000, 0x00000080, 0xF0C00000, 0x00000000, 0x00000000,
};

INCLUDE_ASM("asm/jp/nonmatchings/kernel/chapter_title", InitFadeInPrimitives);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/chapter_title", EnqueueFadeInPrimitives);
