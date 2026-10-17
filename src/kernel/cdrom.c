#include "common.h"

typedef struct {
    /* 0x00 */ s32 startSector;
    /* 0x04 */ s32 byteCount;
} CdFileSectorInfo; // size:0x08

extern const char s_CdControlState[];  // "CD CONTROL STATE = "
extern const char s_CdControlHeader[]; // "--- CD CONTROL ---\n"
extern s32 g_FileGroupOffsetTable[];
extern char s_cdFileName[];
extern const char s_NoUse[];  // "NO USE\n"
extern const char s_Load[];   // "LOAD\n"
extern const char s_LoadF[];  // "LOADF\n"
extern const char s_Movie[];  // "MOVIE\n"
extern const char s_MovieF[]; // "MOVIEF\n"
extern const char s_Da[];     // "DA\n"
extern const char s_SeekB[];  // "SEEKB\n"
extern const char s_SeekF[];  // "SEEKF\n"
extern s32 g_CdState;
extern s32 g_CdReadStartSector;
extern s32 g_CdReadByteCount;
extern s32 g_CdReadTargetAddr;
extern s32 g_LastDisplayBufferIndex;
extern s32 g_MovieDecoderActive;
extern s32 g_CdTransferReady;
extern s32 g_CurrentFrameNum[5];

void DbgScreenPrintString(const char*);

CdFileSectorInfo GetCdFileSectorInfo(s32 fileId, s32 groupId);
void ShutdownMovieDecoder(void);

INCLUDE_RODATA("asm/jp/nonmatchings/kernel/cdrom", D_80010968);
INCLUDE_RODATA("asm/jp/nonmatchings/kernel/cdrom", D_80010980);
INCLUDE_RODATA("asm/jp/nonmatchings/kernel/cdrom", D_80010994);
INCLUDE_RODATA("asm/jp/nonmatchings/kernel/cdrom", D_800109A8);
INCLUDE_RODATA("asm/jp/nonmatchings/kernel/cdrom", D_800109B4);
INCLUDE_RODATA("asm/jp/nonmatchings/kernel/cdrom", D_800109C0);
INCLUDE_RODATA("asm/jp/nonmatchings/kernel/cdrom", D_800109CC);
INCLUDE_RODATA("asm/jp/nonmatchings/kernel/cdrom", D_800109D8);
INCLUDE_RODATA("asm/jp/nonmatchings/kernel/cdrom", D_800109E8);
INCLUDE_RODATA("asm/jp/nonmatchings/kernel/cdrom", D_800109F4);
INCLUDE_RODATA("asm/jp/nonmatchings/kernel/cdrom", D_80010A04);
INCLUDE_RODATA("asm/jp/nonmatchings/kernel/cdrom", D_80010A14);
INCLUDE_RODATA("asm/jp/nonmatchings/kernel/cdrom", D_80010A28);
INCLUDE_RODATA("asm/jp/nonmatchings/kernel/cdrom", D_80010A38);
INCLUDE_RODATA("asm/jp/nonmatchings/kernel/cdrom", D_80010A44);
INCLUDE_RODATA("asm/jp/nonmatchings/kernel/cdrom", D_80010A50);

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

s32 GetFileCountInGroup(s32 groupId) {
    return g_FileGroupOffsetTable[groupId + 2] - g_FileGroupOffsetTable[groupId + 1];
}

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

INCLUDE_RODATA("asm/jp/nonmatchings/kernel/cdrom", D_80010A80);
INCLUDE_RODATA("asm/jp/nonmatchings/kernel/cdrom", D_80010A8C);
INCLUDE_RODATA("asm/jp/nonmatchings/kernel/cdrom", D_80010A9C);

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

INCLUDE_RODATA("asm/jp/nonmatchings/kernel/cdrom", D_80010AEC);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", SetCdBusyStatus);

INCLUDE_RODATA("asm/jp/nonmatchings/kernel/cdrom", s_CdControlState);
INCLUDE_RODATA("asm/jp/nonmatchings/kernel/cdrom", s_CdControlHeader);
INCLUDE_RODATA("asm/jp/nonmatchings/kernel/cdrom", jtbl_80010B5C);
INCLUDE_RODATA("asm/jp/nonmatchings/kernel/cdrom", jtbl_80010B7C);

void ResetCdTransferReadyFlag(void) { g_CdTransferReady = 0; }

void ClearCdTransferReadyFlag(void) { g_CdTransferReady = 0; }

s32 IsCdTransferReady(void) { return g_CdTransferReady; }

INCLUDE_ASM("asm/jp/nonmatchings/kernel/cdrom", ClearMovieDecoderActiveFlag);

void DisplayCdControlStatusToDebugScreen(void) {
    DbgScreenPrintString(s_CdControlHeader); // "--- CD CONTROL ---\n"
    DbgScreenPrintString(s_CdControlState);  // "CD CONTROL STATE = "
    switch (g_CdTransferReady) {
    case 0:
        DbgScreenPrintString(s_NoUse); // "NO USE\n"
        break;
    case 1:
        DbgScreenPrintString(s_Load); // "LOAD\n"
        break;
    case 2:
        DbgScreenPrintString(s_LoadF); // "LOADF\n"
        break;
    case 3:
        DbgScreenPrintString(s_Movie); // "MOVIE\n"
        break;
    case 4:
        DbgScreenPrintString(s_MovieF); // "MOVIEF\n"
        break;
    case 5:
        DbgScreenPrintString(s_Da); // "DA\n"
        break;
    case 6:
        DbgScreenPrintString(s_SeekB); // "SEEKB\n"
        break;
    case 7:
        DbgScreenPrintString(s_SeekF); // "SEEKF\n"
        break;
    }
}
