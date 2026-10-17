#include "common.h"
#include "game.h"
#include "libgpu.h"

#define FRAMEBUFFER_HEIGHT (SCREEN_HEIGHT * 2) /* 480 */

/* Squaresoft logo fade animation parameters */
#define LOGO_FADE_STEPS 0x43 /* 67 frames */
#define LOGO_COLOR_STEP 2
#define LOGO_COLOR_MAX 0x80
#define LOGO_COLOR_MASK 0xFFFE
#define LOGO_TPAGE_MODE 2 /* 16-bit direct color */

#define LOGO_FADE_BUFFER_SIZE 0xCC

typedef struct {
    /* 0x00 */ DRAWENV draw;
    /* 0x5C */ DISPENV disp;
    /* 0x70 */ u_long ot[1];
    /* 0x74 */ SPRT sprt[2];
    /* 0x9C */ u8 pad9C[LOGO_FADE_BUFFER_SIZE - 0x9C];
} LogoFadeBuffer; // size:0xCC

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
