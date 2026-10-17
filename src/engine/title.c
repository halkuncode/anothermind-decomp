#include "common.h"

extern s16 g_GlobalVariableTable[];
extern s16 g_TitleSelectionSettings[];

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
    g_TitleSelectionSettings[2] = 7;
    g_TitleSelectionSettings[9] = 3;
    g_TitleSelectionSettings[11] = 15;
    g_TitleSelectionSettings[17] = 17;
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
