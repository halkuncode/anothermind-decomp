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
} SaveFileMetadata; // size:0x10

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
} SaveSlotHeader; // size:0x12

extern SaveSlotHeader g_SaveSlotIndex[];

INCLUDE_ASM("asm/jp/nonmatchings/engine/memcard", WriteSaveMetadataBlock);

INCLUDE_ASM("asm/jp/nonmatchings/engine/memcard", LoadSaveSlotIconsToVram);

INCLUDE_ASM("asm/jp/nonmatchings/engine/memcard", LoadMemoryCardSaveHeaders);

INCLUDE_ASM("asm/jp/nonmatchings/engine/memcard", LoadSaveSlotNamesFromMemoryCard);

INCLUDE_ASM("asm/jp/nonmatchings/engine/memcard", PackSaveDataBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/engine/memcard", ExecuteSaveGame);

INCLUDE_ASM("asm/jp/nonmatchings/engine/memcard", TryLoadGameFromMemoryCard);
