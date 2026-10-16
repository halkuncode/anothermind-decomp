#include "common.h"

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/face_anim", LoadNameEntryGraphicAndPalettes);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/face_anim", LoadMesconFontImage);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/face_anim", InitAddressBookMenuAssets);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/face_anim", LoadKanjiTimData);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/face_anim", LoadAndPrepareChapterTimImage);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/face_anim", InitPortraitAnimTileState);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/face_anim", RunIdlePortraitTileAnimation);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/face_anim", StepPortraitIdleAnimation);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/face_anim", UpdatePortraitMouthAnimation);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/face_anim", RunPortraitFadeOutTiles);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/face_anim", RunPortraitFadeIn);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/face_anim", UpdatePortraitBlinkAnimation);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/face_anim", StepPortraitFadeInTiles);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/face_anim", StepPortraitFadeOutTiles);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/face_anim", ProcessPortraitDissolveStep);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/face_anim", StepPortraitMosaicDissolve);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/face_anim", StepPortraitHorizontalStripes);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/face_anim", StepPortraitVerticalStripes);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/face_anim", ProcessPortraitColorShift);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/face_anim", RunPortraitFlashEffect);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/face_anim", StepPortraitFlashAnimation);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/face_anim", FinishPortraitAnimationTransition);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/face_anim", HandleFunctionDispatch);

