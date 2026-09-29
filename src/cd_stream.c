#include "common.h"

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", LoadChapterEndGraphic);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", GetCdFileSectorInfo);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", ProcessCdReadStateMachine);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", DisplayCdFileDebugStatus);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", LoadRawSectorData);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", LoadCdPosTablefromCd);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", LoadByFileIdGroupId);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", LoadFileFromGroupByIndex);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", WaitForCdIdle);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", GetFilename);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", GetFileCountInGroup);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", IsDebugDisabled);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", func_80019CF4);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", SeekToCdFileEntry);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", SeekCdToFileStart);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", PlayCdAudioTrack);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", func_80019E24);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", GetSectorForMovieId);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", func_80019EC4);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", func_80019F88);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", func_8001A01C);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", func_8001A0B0);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", func_8001A124);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", func_8001A160);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", func_8001A1F4);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", UpdateCdTransferState);

void func_8001A2A4(void) {}

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", StartPlayMovie);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", PlayScriptedMovieCutscene);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", func_8001A890);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", UpdateMoviePlaybackFrame);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", DisplayMovieDebugPanel);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", InitMoviePlaybackContext);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", SetupMovieStream);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", ProcessNextVideoBlock);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", func_8001B248);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", WaitForFrameReadyOrFallback);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", GetNextMdecBitstream);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", SeekCdAndBeginStream);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", PlayMovieSegmentById);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", SetupMovieDecoder);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", SetCdAudioMonoStereo);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", PlayTitleScreenCutscene);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", StartScriptedMovieWithFade);

void func_8001B854(void) {}

void func_8001B85C(void) {}

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", StopScriptedMovieDecoder);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", IsMovieDecoderActive);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", GetCurrentMovieFrame);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", PlayDefaultMovieSegment);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", PlayMovieSegmentUsingOffsetOrDefault);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", LoopMovieById);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", ShutdownMovieDecoder);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", ResetMovieDecoderState);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", func_8001B9C4);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", func_8001B9D0);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", func_8001BA64);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", func_8001BAC0);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", func_8001BB00);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", SetCdBusyStatus);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", ResetCdTransferReadyFlag);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", ClearCdTransferReadyFlag);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", IsCdTransferReady);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", func_8001BCE8);

INCLUDE_ASM("asm/jp/nonmatchings/cd_stream", DisplayCdControlStatusToDebugScreen);
