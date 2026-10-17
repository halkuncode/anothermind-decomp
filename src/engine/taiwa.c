#include "common.h"

INCLUDE_ASM("asm/jp/nonmatchings/engine/taiwa", InitTaiwaMenu);

INCLUDE_ASM("asm/jp/nonmatchings/engine/taiwa", ResetTaiwaMenu);

INCLUDE_ASM("asm/jp/nonmatchings/engine/taiwa", InitTaiwaSelection);

INCLUDE_ASM("asm/jp/nonmatchings/engine/taiwa", ResetNewsSystem);

INCLUDE_ASM("asm/jp/nonmatchings/engine/taiwa", DrawTaiwaCursor);

INCLUDE_ASM("asm/jp/nonmatchings/engine/taiwa", UpdateTaiwaCursor);

INCLUDE_ASM("asm/jp/nonmatchings/engine/taiwa", ProcessTaiwaInput);

INCLUDE_ASM("asm/jp/nonmatchings/engine/taiwa", PruneTaiwaChoiceSlots);

INCLUDE_ASM("asm/jp/nonmatchings/engine/taiwa", FormatTaiwaText);

INCLUDE_ASM("asm/jp/nonmatchings/engine/taiwa", RenderTaiwaText);

INCLUDE_ASM("asm/jp/nonmatchings/engine/taiwa", RenderTaiwaBoxes);

INCLUDE_ASM("asm/jp/nonmatchings/engine/taiwa", HighlightActiveTaiwaOption);

INCLUDE_ASM("asm/jp/nonmatchings/engine/taiwa", ConfirmTaiwaSentence);

INCLUDE_ASM("asm/jp/nonmatchings/engine/taiwa", UpdateTaiwaInput);

INCLUDE_ASM("asm/jp/nonmatchings/engine/taiwa", HandleTaiwaConfirmation);

INCLUDE_ASM("asm/jp/nonmatchings/engine/taiwa", CloseTaiwaMenu);

INCLUDE_ASM("asm/jp/nonmatchings/engine/taiwa", CleanupTaiwaAssets);
