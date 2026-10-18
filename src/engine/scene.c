#include "common.h"

INCLUDE_ASM("asm/jp/nonmatchings/engine/scene", InitScreenUiPrimitives);

INCLUDE_ASM("asm/jp/nonmatchings/engine/scene", DrawFaceBackgroundBox);

INCLUDE_ASM("asm/jp/nonmatchings/engine/scene", DrawFaceReveal);

INCLUDE_ASM("asm/jp/nonmatchings/engine/scene", DrawFaceTileGrid);

INCLUDE_ASM("asm/jp/nonmatchings/engine/scene", SetupFaceSlot1AndRenderGrid);

INCLUDE_ASM("asm/jp/nonmatchings/engine/scene", SetupFaceRenderContext);

INCLUDE_ASM("asm/jp/nonmatchings/engine/scene", DrawScreenSelectionBoxes);

INCLUDE_ASM("asm/jp/nonmatchings/engine/scene", DrawFace);

INCLUDE_ASM("asm/jp/nonmatchings/engine/scene", DrawDialogHighlightBars);

const u8 g_TaiwaHighlightBarColors[24] = {
    0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0x90, 0x80,
    0x70, 0x60, 0x50, 0x40, 0x30, 0x20, 0x10, 0x00, 0xFF, 0x00, 0x00, 0x00,
};
const u8 g_TaiwaHighlightPulseColors[16] = {
    0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xA0, 0xA0, 0x90, 0x80, 0x70, 0x60, 0x50, 0x40, 0xFF, 0x00,
};

INCLUDE_ASM("asm/jp/nonmatchings/engine/scene", DrawDialogHighlightBarSegment);

INCLUDE_ASM("asm/jp/nonmatchings/engine/scene", AnimateDialogHighlightSegments);

INCLUDE_ASM("asm/jp/nonmatchings/engine/scene", DrawFaceSelectionHighlight);

INCLUDE_ASM("asm/jp/nonmatchings/engine/scene", DrawDialogSelectionBoxes);

INCLUDE_ASM("asm/jp/nonmatchings/engine/scene", DrawDebugTextOverlay);

INCLUDE_ASM("asm/jp/nonmatchings/engine/scene", DrawTwoDigitNumber);

INCLUDE_ASM("asm/jp/nonmatchings/engine/scene", DrawStoryDateDisplay);

INCLUDE_ASM("asm/jp/nonmatchings/engine/scene", DrawSaveSlotEntry);

const u32 g_TaiwaTextBarClutCycleTable[8] = {
    0x03011500, 0x03030302, 0x03050304, 0x03030304, 0x03010302, 0x00000000, 0x00000000, 0x00000000,
};
const u32 g_FadeControlByteTable[16] = {
    0x00080000, 0x00080003, 0x00080006, 0x00080009, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
};
const u32 g_FadeControlByteTableEnd[16] = {
    0x0006000C, 0x00060300, 0x00060303, 0x00060306, 0x00060309, 0x0006030C, 0x00060600, 0x00630600,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
};
const u32 g_FadeControlTable2End[6] = {
    0xC0D0E0F0, 0x8090A0B0, 0x70606070, 0xB0A09080, 0xF0E0D0C0, 0x00000000,
};

INCLUDE_ASM("asm/jp/nonmatchings/engine/scene", AnimateDialogTextBarClut);

INCLUDE_ASM("asm/jp/nonmatchings/engine/scene", UpdateDialogFadeState);

INCLUDE_ASM("asm/jp/nonmatchings/engine/scene", UpdateDialogTextBarFade);

INCLUDE_ASM("asm/jp/nonmatchings/engine/scene", UpdateFadeSlotColor);

INCLUDE_ASM("asm/jp/nonmatchings/engine/scene", UpdateAllFadeSlotsFromScript);

INCLUDE_ASM("asm/jp/nonmatchings/engine/scene", DrawConditionalDialogHighlight);

INCLUDE_ASM("asm/jp/nonmatchings/engine/scene", UpdateDialogSelectionEffects);

// "demo.bin\0\0\0\0" followed by developer credit "小久保\0" (Yasushi Kokubo)
const u32 s_DemoFileName[6] = {
    0x6F6D6564, 0x6E69622E, 0x00000000, // ASCII: "demo.bin\0"
    0x768BAC8F, 0x0000DB95, 0x00000000, // Shift-JIS: "小久保\0" (0x8FAC, 0x8B76, 0x95DB)
};

INCLUDE_ASM("asm/jp/nonmatchings/engine/scene", DrawScreenUI);

INCLUDE_ASM("asm/jp/nonmatchings/engine/scene", ResetFaceClutAndUpload);

INCLUDE_ASM("asm/jp/nonmatchings/engine/scene", UploadFaceSpriteToVram);

INCLUDE_ASM("asm/jp/nonmatchings/engine/scene", UploadFaceClutToVram);

INCLUDE_ASM("asm/jp/nonmatchings/engine/scene", PrepareFaceSlot);

INCLUDE_ASM("asm/jp/nonmatchings/engine/scene", UpdateFaceSlotDrawArea);

INCLUDE_ASM("asm/jp/nonmatchings/engine/scene", UpdateFaceSlotLayout);

INCLUDE_ASM("asm/jp/nonmatchings/engine/scene", AllocateFaceAnimSlot);

INCLUDE_ASM("asm/jp/nonmatchings/engine/scene", UpdateMessageBoxVisibility);

INCLUDE_ASM("asm/jp/nonmatchings/engine/scene", UpdateFaceSlotTransitions);
