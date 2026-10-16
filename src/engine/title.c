#include "common.h"

extern s16 g_GlobalVariableTable[];
extern s16 D_80130CD0[];

INCLUDE_ASM("asm/jp/nonmatchings/engine/title", LoadPortraitAnimationScript);

INCLUDE_ASM("asm/jp/nonmatchings/engine/title", RunDebugChapterSelectionMenu);

void EnableInitialGlobalVars(void) {
    s16 i;

    for (i = 0; i < 23; i++) {
        SET_GLOBAL_FLAG(i * 2);
        SET_GLOBAL_FLAG((i * 2) + 1);
    }

    for (i = 1; i < 19; i++) {
        g_GlobalVariableTable[i + 0x114] = i + 0x20;
    }

    D_80130CD0[2] = 7;
    D_80130CD0[9] = 3;
    D_80130CD0[11] = 15;
    D_80130CD0[17] = 17;
    *(s16*)((u8*)g_GlobalVariableTable + 0x250) = 3;

    for (i = 0; i < 16; i++) {
        SET_GLOBAL_FLAG(i + 0x30);
    }

    for (i = 0; i < 14; i++) {
        SET_GLOBAL_FLAG(i + 0x44);
    }
}

INCLUDE_ASM("asm/jp/nonmatchings/engine/title", StartAttractModeDemo);

INCLUDE_ASM("asm/jp/nonmatchings/engine/title", DispatchTitleMenuAction);
