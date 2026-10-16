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

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", LoadChapterEndGraphic);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", GetCdFileSectorInfo);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", ProcessCdReadStateMachine);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", DisplayCdFileDebugStatus);

void LoadRawSectorData(s32 startSector, s32 byteCount, s32 destination) {
    g_CdReadStartSector = startSector;
    g_CdReadByteCount = byteCount;
    g_CdReadTargetAddr = destination;
    g_CdState = 1;
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", LoadCdPosTablefromCd);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", LoadByFileIdGroupId);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", LoadFileFromGroupByIndex);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", WaitForCdIdle);

char* GetFilename(void) { return s_cdFileName; }

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", GetFileCountInGroup);

s32 IsDebugDisabled(void) { return -1; }

s32 LoadScriptByFilename(void) { return 0; }

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", SeekToCdFileEntry);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", SeekCdToFileStart);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", PlayCdAudioTrack);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", DebugRunCdLoadTest);

s32 GetSectorForMovieId(s32 fileId, s32 groupId) { return GetCdFileSectorInfo(fileId, groupId).startSector; }

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", SeekCdFileHeader);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", PlayCdMusicTrack);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", LookupMovieSector);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", CheckCdTransferStatus);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", DbgPrintDebugStringTest);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", GetGroupFileCount);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", WaitForCdDriveIdle);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", UpdateCdTransferState);

void DebugOnController2L2Press(void) {}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", StartPlayMovie);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", PlayScriptedMovieCutscene);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", ProcessMovieInterruptAndDecode);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", UpdateMoviePlaybackFrame);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", DisplayMovieDebugPanel);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", InitMoviePlaybackContext);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", SetupMovieStream);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", ProcessNextVideoBlock);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", StGetNextBlock);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", WaitForFrameReadyOrFallback);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", GetNextMdecBitstream);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", SeekCdAndBeginStream);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", PlayMovieSegmentById);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", SetupMovieDecoder);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", SetCdAudioMonoStereo);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", PlayTitleScreenCutscene);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", StartScriptedMovieWithFade);

void StubStopXAPlayback(void) {}

void StubResetStreamRing(void) {}

void StopScriptedMovieDecoder(void) { ShutdownMovieDecoder(); }

s32 IsMovieDecoderActive(void) { return g_MovieDecoderActive; }

s32 GetCurrentMovieFrame(void) { return g_CurrentFrameNum[0]; }

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", PlayDefaultMovieSegment);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", PlayMovieSegmentUsingOffsetOrDefault);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", LoopMovieById);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", ShutdownMovieDecoder);

void ResetMovieDecoderState(void) { g_MovieDecoderActive = 0; }

s32 GetLastDisplayBufferIndex(void) { return g_LastDisplayBufferIndex; }

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", PlayDefaultMovieStream);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", PlayMovieStreamWithOffset);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", PlayMovieStreamLooping);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", AbortAndShutdownMovieDecoder);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", SetCdBusyStatus);

void ResetCdTransferReadyFlag(void) { g_CdTransferReady = 0; }

void ClearCdTransferReadyFlag(void) { g_CdTransferReady = 0; }

s32 IsCdTransferReady(void) { return g_CdTransferReady; }

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", ClearMovieDecoderActiveFlag);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", DisplayCdControlStatusToDebugScreen);
