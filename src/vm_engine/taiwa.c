#include "common.h"

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/taiwa", InitTaiwaPrimitiveSystem);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/taiwa", DrawPortraitBackgroundBox);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/taiwa", DrawPortraitReveal);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/taiwa", DrawPortraitTileGrid);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/taiwa", SetupSecondPortraitAndRenderGrid);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/taiwa", SetupPortraitRenderContext);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/taiwa", DrawPortraitSelectionBoxes);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/taiwa", DrawPortrait);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/taiwa", DrawTaiwaHighlightBars);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/taiwa", DrawTaiwaHighlightBarSegment);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/taiwa", AnimateTaiwaHighlightSegments);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/taiwa", DrawPortraitSelectionHighlight);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/taiwa", DrawTaiwaSelectionBoxes);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/taiwa", DrawDebugTextOverlay);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/taiwa", DrawTwoDigitNumber);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/taiwa", DrawStoryDateDisplay);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/taiwa", DrawSaveSlotEntry);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/taiwa", AnimateTaiwaTextBarClut);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/taiwa", UpdateTaiwaFadeState);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/taiwa", UpdateTaiwaTextBarFade);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/taiwa", UpdateFadeSlotColor);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/taiwa", UpdateAllFadeSlotsFromScript);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/taiwa", DrawConditionalTaiwaHighlight);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/taiwa", UpdateTaiwaSelectionEffects);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/taiwa", DrawTaiwaScreenUI);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/taiwa", ResetPortraitClutAndUpload);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/taiwa", UploadPortraitSpriteToVram);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/taiwa", UploadPortraitClutToVram);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/taiwa", PreparePortraitSlot);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/taiwa", UpdatePortraitSlotDrawArea);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/taiwa", UpdatePortraitSlotLayout);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/taiwa", AllocatePortraitAnimSlot);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/taiwa", UpdateMessageBoxVisibility);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/taiwa", UpdatePortraitSlotTransitions);
