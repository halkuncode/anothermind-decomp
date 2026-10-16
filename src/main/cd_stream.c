#include "common.h"

typedef struct {
    /* 0x00 */ s32 startSector;
    /* 0x04 */ s32 byteCount;
} CdFileSectorInfo; // size:0x08

extern char s_cdFileName[];
extern s32 g_CdState;
extern s32 g_CdReadStartSector;
extern s32 g_CdReadByteCount;
extern s32 g_CdReadTargetAddr;
extern s32 g_LastDisplayBufferIndex;
extern s32 g_MovieDecoderActive;
extern s32 g_CdTransferReady;
extern s32 g_CurrentFrameNum[5];

CdFileSectorInfo GetCdFileSectorInfo(s32 fileId, s32 groupId);
void ShutdownMovieDecoder(void);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", LoadChapterEndGraphic);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", GetCdFileSectorInfo);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", ProcessCdReadStateMachine);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", DisplayCdFileDebugStatus);

void LoadRawSectorData(s32 startSector, s32 byteCount, s32 destination) {
    g_CdReadStartSector = startSector;
    g_CdReadByteCount = byteCount;
    g_CdReadTargetAddr = destination;
    g_CdState = 1;
}

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", LoadCdPosTablefromCd);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", LoadByFileIdGroupId);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", LoadFileFromGroupByIndex);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", WaitForCdIdle);

char* GetFilename(void) { return s_cdFileName; }

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", GetFileCountInGroup);

s32 IsDebugDisabled(void) { return -1; }

s32 LoadScriptByFilename(void) { return 0; }

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", SeekToCdFileEntry);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", SeekCdToFileStart);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", PlayCdAudioTrack);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", DebugRunCdLoadTest);

s32 GetSectorForMovieId(s32 fileId, s32 groupId) { return GetCdFileSectorInfo(fileId, groupId).startSector; }

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", SeekCdFileHeader);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", PlayCdMusicTrack);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", LookupMovieSector);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", CheckCdTransferStatus);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", DbgPrintDebugStringTest);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", GetGroupFileCount);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", WaitForCdDriveIdle);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", UpdateCdTransferState);

void DebugOnController2L2Press(void) {}

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", StartPlayMovie);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", PlayScriptedMovieCutscene);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", ProcessMovieInterruptAndDecode);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", UpdateMoviePlaybackFrame);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", DisplayMovieDebugPanel);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", InitMoviePlaybackContext);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", SetupMovieStream);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", ProcessNextVideoBlock);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", StGetNextBlock);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", WaitForFrameReadyOrFallback);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", GetNextMdecBitstream);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", SeekCdAndBeginStream);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", PlayMovieSegmentById);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", SetupMovieDecoder);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", SetCdAudioMonoStereo);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", PlayTitleScreenCutscene);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", StartScriptedMovieWithFade);

void StubStopXAPlayback(void) {}

void StubResetStreamRing(void) {}

void StopScriptedMovieDecoder(void) { ShutdownMovieDecoder(); }

s32 IsMovieDecoderActive(void) { return g_MovieDecoderActive; }

s32 GetCurrentMovieFrame(void) { return g_CurrentFrameNum[0]; }

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", PlayDefaultMovieSegment);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", PlayMovieSegmentUsingOffsetOrDefault);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", LoopMovieById);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", ShutdownMovieDecoder);

void ResetMovieDecoderState(void) { g_MovieDecoderActive = 0; }

s32 GetLastDisplayBufferIndex(void) { return g_LastDisplayBufferIndex; }

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", PlayDefaultMovieStream);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", PlayMovieStreamWithOffset);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", PlayMovieStreamLooping);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", AbortAndShutdownMovieDecoder);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", SetCdBusyStatus);

void ResetCdTransferReadyFlag(void) { g_CdTransferReady = 0; }

void ClearCdTransferReadyFlag(void) { g_CdTransferReady = 0; }

s32 IsCdTransferReady(void) { return g_CdTransferReady; }

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", ClearMovieDecoderActiveFlag);

INCLUDE_ASM("asm/jp/nonmatchings/main/cd_stream", DisplayCdControlStatusToDebugScreen);
