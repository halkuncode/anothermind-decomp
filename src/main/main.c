#include "common.h"
#include <libetc.h>
#include <libgpu.h>
#include <libsnd.h>

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

INCLUDE_ASM("asm/jp/nonmatchings/main/main", ResetToReleaseMode);

INCLUDE_ASM("asm/jp/nonmatchings/main/main", UpdateSystemPerFrame);

INCLUDE_ASM("asm/jp/nonmatchings/main/main", DisplaySystemDebugPanel);

INCLUDE_ASM("asm/jp/nonmatchings/main/main", GetDebugLockState);

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
