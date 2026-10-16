#include "common.h"

typedef struct {
    /* 0x00 */ s16 playTimeHours;
    /* 0x02 */ s16 playTimeMinutes;
    /* 0x04 */ s16 playTimeSeconds;
    /* 0x06 */ s16 chapterNumber;
    /* 0x08 */ s16 kanjiTileBlockId;
    /* 0x0A */ s16 scriptId;
    /* 0x0C */ s16 dataLength;
    /* 0x0E */ s16 expectedChecksum;
} SaveFileMetadata; /* size = 0x10 (16 bytes) */

typedef struct {
    /* 0x00 */ s16 slotIndex;
    /* 0x02 */ s16 titleId;
    /* 0x04 */ s16 checksum;
    /* 0x06 */ s16 timestampLow;
    /* 0x08 */ s16 timestampHigh;
    /* 0x0A */ s16 flags1;
    /* 0x0C */ s16 flags2;
    /* 0x0E */ s16 typeCode;
    /* 0x10 */ s16 pad10;
} SaveSlotHeader; /* size = 0x12 (18 bytes) */

extern SaveSlotHeader g_SaveSlotIndex[];

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/memcard", WriteSaveMetadataBlock);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/memcard", LoadSaveSlotIconsToVram);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/memcard", LoadMemoryCardSaveHeaders);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/memcard", LoadSaveSlotNamesFromMemoryCard);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/memcard", PackSaveDataBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/memcard", ExecuteSaveGame);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/memcard", TryLoadGameFromMemoryCard);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/memcard", LoadPortraitAnimationScript);

INCLUDE_ASM("asm/jp/nonmatchings/vm_engine/memcard", RunDebugChapterSelectionMenu);

extern s16 g_GlobalVariableTable[];
extern s16 D_80130CD0[];



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
