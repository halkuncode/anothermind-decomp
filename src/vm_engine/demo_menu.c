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

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", RunDebugSoundTestMenu);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", RunDebugScheduleViewer);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", RunDebugSceneJumpMenu);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", RunDebugFlagEditor);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", RunDebugMemoryViewer);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", RunDebugScriptViewer);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", RunDebugSaveDataManager);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", RunDebugPaletteEditor);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", RunDebugFontViewer);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", RunDebugVramViewer);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", RunDebugMovieViewer);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", RunDebugTaiwaViewer);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", TestGpuAndCdromEventState);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", CheckGpuEventStatus);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", WriteSaveMetadataBlock);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", LoadSaveSlotIconsToVram);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", LoadMemoryCardSaveHeaders);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", LoadSaveSlotNamesFromMemoryCard);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", PackSaveDataBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/demo_menu", ExecuteSaveGame);
