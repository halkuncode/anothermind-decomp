#include "common.h"

extern s16 g_GlobalVariableTable[];
extern s16 D_80130CD0[];

INCLUDE_ASM("asm/jp/nonmatchings/engine/title", LoadPortraitAnimationScript);

INCLUDE_ASM("asm/jp/nonmatchings/engine/title", RunDebugChapterSelectionMenu);

void EnableInitialGlobalVars(void) {
    s16 i;
    u8* table;

    for (i = 0; i < 23; i++) {
        s16 b = i * 2;
        u8 mask = 1 << (b % 8);
        ((u8*)g_GlobalVariableTable)[b / 8] |= mask;
        b++;
        mask = 1 << (b % 8);
        ((u8*)g_GlobalVariableTable)[b / 8] |= mask;
    }

    for (i = 1; i < 19; i++) {
        g_GlobalVariableTable[i + 0x114] = i + 0x20;
    }

    table = (u8*)g_GlobalVariableTable;
    i = 0;
    D_80130CD0[2] = 7;
    D_80130CD0[9] = 3;
    D_80130CD0[11] = 15;
    D_80130CD0[17] = 17;
    *(s16*)(table + 0x250) = 3;

    do {
        s16 b = i + 0x30;
        u8 mask = 1 << (b % 8);
        ((u8*)g_GlobalVariableTable)[b / 8] |= mask;
    } while (++i < 16);

    i = 0;
    table = (u8*)g_GlobalVariableTable;
    do {
        s16 b = i + 0x44;
        u8 mask = 1 << (b % 8);
        ((u8*)g_GlobalVariableTable)[b / 8] |= mask;
    } while (++i < 14);
}

INCLUDE_ASM("asm/jp/nonmatchings/engine/title", StartAttractModeDemo);

INCLUDE_ASM("asm/jp/nonmatchings/engine/title", DispatchTitleMenuAction);
