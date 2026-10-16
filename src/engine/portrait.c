#include "common.h"

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait", LoadAndPrepareChapterTimImage);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait", InitPortraitAnimTileState);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait", RunIdlePortraitTileAnimation);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait", StepPortraitIdleAnimation);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait", UpdatePortraitMouthAnimation);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait", RunPortraitFadeOutTiles);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait", RunPortraitFadeIn);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait", UpdatePortraitBlinkAnimation);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait", StepPortraitFadeInTiles);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait", StepPortraitFadeOutTiles);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait", ProcessPortraitDissolveStep);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait", StepPortraitMosaicDissolve);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait", StepPortraitHorizontalStripes);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait", StepPortraitVerticalStripes);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait", ProcessPortraitColorShift);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait", RunPortraitFlashEffect);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait", StepPortraitFlashAnimation);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait", FinishPortraitAnimationTransition);

INCLUDE_ASM("asm/jp/nonmatchings/engine/portrait", HandleFunctionDispatch);
