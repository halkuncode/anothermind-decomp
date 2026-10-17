#include "common.h"

extern s16 g_GlobalVariableTable[];
extern s16 g_TitleSelectionSettings[];

INCLUDE_ASM("asm/jp/nonmatchings/engine/title", LoadPortraitAnimationScript);

const char s_DebugChapterMenuHeader[] = "         CHAPTER MENU\n\n";
const char s_DebugCursorPointer[] = "       > ";
const char s_DebugChapter1[] = "CHAPTER 1\n";
const char s_DebugCursorSpace[] = "         ";
const char s_DebugChapter2[] = "CHAPTER 2\n";
const char s_DebugChapter3[] = "CHAPTER 3\n";
const char s_DebugChapter4[] = "CHAPTER 4\n";
const char s_DebugChapter5[] = "CHAPTER 5\n";
const char s_DebugChapter6[] = "CHAPTER 6\n";
const char s_DebugChapter7[] = "CHAPTER 7\n";
const char s_DebugChapter8[] = "CHAPTER 8\n";
const char s_DebugChapter9[] = "CHAPTER 9\n";
const char s_DebugChapterA[] = "CHAPTER A\n";
const char s_DebugBreakMenuHeader[] = "         BREAK MENU\n\n";
const char s_DebugReturnString[] = "RETURN\n";
const char s_DebugBreak1[] = "BREAK 1\n";
const char s_DebugBreak2[] = "BREAK 2\n";
const char s_DebugBreak3[] = "BREAK 3\n";
const char s_DebugBreak4[] = "BREAK 4\n";
const char s_DebugBreak5[] = "BREAK 5\n";
const char s_DebugBreak6[] = "BREAK 6\n";
const char s_DebugBreak7[] = "BREAK 7\n";
const char s_DebugBreak8[] = "BREAK 8\n";
const char s_DebugBreak9[] = "BREAK 9\n";

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
