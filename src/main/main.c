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

extern s32 g_DebugLockState; //!< Global debug lockout state flag.

/**
 * @brief Aborts program execution immediately.
 *
 * Triggers a hardware breakpoint (MIPS break instruction) to halt execution
 * and signal an unrecoverable abnormal termination.
 */
void abort(void) { M2C_BREAK(1); }

extern void DoGame(void);

int main(void) {
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

s32 GetDebugLockState(void) { return g_DebugLockState; }

void LockoutDebug(s32 state) { g_DebugLockState = state; }

INCLUDE_ASM("asm/jp/nonmatchings/main/main", GetDebugScriptBuildDateString);

INCLUDE_ASM("asm/jp/nonmatchings/main/main", IntToAscii);

INCLUDE_ASM("asm/jp/nonmatchings/main/main", ReportIssue);

INCLUDE_ASM("asm/jp/nonmatchings/main/main", UnpackAmpackArchiveData);

INCLUDE_ASM("asm/jp/nonmatchings/main/main", DecompressLZSS);

INCLUDE_ASM("asm/jp/nonmatchings/main/main", DebugUnpackAmpack);

INCLUDE_ASM("asm/jp/nonmatchings/main/main", CheckAndUnpackAmpack);

s32 ReadLittleEndian32(u8* data) {
    u32 ret = data[0];
    ret += data[1] << 8;
    ret += data[2] << 16;
    ret += data[3] << 24;
    return ret;
}

INCLUDE_ASM("asm/jp/nonmatchings/main/main", LoadProgdata);
