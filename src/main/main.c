//! PSYQ=4.0
#include "common.h"
#include <libetc.h>
#include <libgpu.h>
#include <libsnd.h>

extern s32 IsDebugDisabled();
extern void LoadCdPosTablefromCd(void);
extern void LockoutDebug(s32);
extern void ResetCdTransferReadyFlag(void);
extern void ResetMovieDecoderState(void);
extern void ResetVibrationSystem(void);
extern void ShowSquaresoftLogo(void);
extern void UpdateCdTransferState(void);
extern void UpdateMoviePlaybackFrame(void);
extern void UpdateVibrationAndInput(void);
extern void DisplayCdControlStatusToDebugScreen(void);
extern void DisplayCdFileDebugStatus(void);
extern void DisplayMovieDebugPanel(void);
extern void DisplayPadDebugPanel(void);

void abort(void) { M2C_BREAK(1); }

extern void DoGame(void);

void main(void) {
    StopCallback();
    ResetCallback();
    ResetGraph(0);
    SsUtReverbOff();
    DoGame();
    while (1)
        ;
}

void ResetToReleaseMode(void) {
    LockoutDebug(0);
    ResetCdTransferReadyFlag();
    LoadCdPosTablefromCd();
    if (IsDebugDisabled() == -1) {
        ShowSquaresoftLogo();
        LockoutDebug(1);
    }
    ResetMovieDecoderState();
    ResetVibrationSystem();
}

void UpdateSystemPerFrame(void) {
    UpdateCdTransferState();
    UpdateMoviePlaybackFrame();
    UpdateVibrationAndInput();
}

void DisplaySystemDebugPanel(void) {
    DisplayCdControlStatusToDebugScreen();
    DisplayCdFileDebugStatus();
    DisplayMovieDebugPanel();
    DisplayPadDebugPanel();
}

extern s32 g_DebugLockState;

s32 GetDebugLockState(void) { return g_DebugLockState; }



INCLUDE_ASM("asm/jp/nonmatchings/main/main", LockoutDebug);

INCLUDE_ASM("asm/jp/nonmatchings/main/main", GetDebugScriptBuildDateString);

INCLUDE_ASM("asm/jp/nonmatchings/main/main", IntToAscii);

INCLUDE_ASM("asm/jp/nonmatchings/main/main", ReportIssue);

INCLUDE_ASM("asm/jp/nonmatchings/main/main", func_80012DEC);

INCLUDE_ASM("asm/jp/nonmatchings/main/main", DecompressLZSS);

INCLUDE_ASM("asm/jp/nonmatchings/main/main", func_800130BC);

INCLUDE_ASM("asm/jp/nonmatchings/main/main", CheckAndUnpackAmpack);

INCLUDE_ASM("asm/jp/nonmatchings/main/main", ReadLittleEndian32);

INCLUDE_ASM("asm/jp/nonmatchings/main/main", LoadProgdata);
