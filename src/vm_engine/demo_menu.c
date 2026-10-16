#include "common.h"

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", RecordDemoInputFrame);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", PlaybackDemoInputFrame);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", CancelDemoPlaybackAndResetState);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", PollAndProcessControllerInput);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", UpdateActiveDigitEditor);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", UpdatePortraitDebugSlot);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", SetupDebugHighlightDrawModes);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", InitDebugMenuBuffers);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", LoadInGameMenuBackground);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", InitSaveLoadMenuResources);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", UpdateDebugMenuState);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", RunDebugMenuPage1);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", RunDebugMenuPage2);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", RunDebugMenuPage3);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", CalcTaiwaWordSlotLayout);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", PositionTaiwaSelectionCursor);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", RunDebugSceneJumpMenu);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", ApplyTaiwaSpriteTintAndOffsets);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", UpdateTaiwaChoiceEntry);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", FreePortraitTileSlot);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", RunDebugSaveDataManager);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", ParseTaiwaSentenceAndConjugation);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", CalcTaiwaChoiceYPositions);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", RunDebugVramViewer);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", RunDebugMovieViewer);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", ProcessTaiwaStateMachine);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", TestGpuAndCdromEventState);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", CheckGpuEventStatus);
