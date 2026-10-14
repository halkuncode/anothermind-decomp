#include "common.h"

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait_anim", LoadNameEntryGraphicAndPalettes);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait_anim", LoadMesconFontImage);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait_anim", InitAddressBookMenuAssets);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait_anim", LoadKanjiTimData);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait_anim", LoadAndPrepareChapterTimImage);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait_anim", InitPortraitAnimTileState);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait_anim", RunIdlePortraitTileAnimation);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait_anim", StepPortraitIdleAnimation);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait_anim", UpdatePortraitMouthAnimation);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait_anim", RunPortraitFadeOutTiles);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait_anim", RunPortraitFadeIn);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait_anim", UpdatePortraitBlinkAnimation);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait_anim", StepPortraitFadeInTiles);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait_anim", StepPortraitFadeOutTiles);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait_anim", ProcessPortraitDissolveStep);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait_anim", StepPortraitMosaicDissolve);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait_anim", StepPortraitHorizontalStripes);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait_anim", StepPortraitVerticalStripes);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait_anim", ProcessPortraitColorShift);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait_anim", RunPortraitFlashEffect);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait_anim", StepPortraitFlashAnimation);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait_anim", FinishPortraitAnimationTransition);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait_anim", HandleFunctionDispatch);
