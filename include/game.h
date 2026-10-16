#ifndef GAME_H
#define GAME_H

/* Display resolution */
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

/* Ampack archive header magic bytes */
#define AMPACK_MAGIC_0 0xC3
#define AMPACK_MAGIC_1 0xFF

/* LZSS compression parameters */
#define LZSS_WINDOW_SIZE 4096
#define LZSS_WINDOW_MASK (LZSS_WINDOW_SIZE - 1) /* 0xFFF */
#define LZSS_WINDOW_INIT_INDEX 0xFEE

/* Well-known memory buffer addresses */
#define PROGDATA_LOAD_ADDR ((u8*)0x80138000)
#define PROGDATA_LOAD_MAX_SIZE 0x30000
#define PROGDATA_UNPACK_ADDR ((u8*)0x80168000)
#define DEBUG_UNPACK_SRC_ADDR ((u8*)0x80160000)

typedef enum {
    FILE_VIDEO = 0,
    FILE_SYSTEM = 1,
    FILE_DICT = 2,
    FILE_DIALOG = 3,
    FILE_MENU = 4,
    FILE_SCRIPT = 5,
    FILE_BACKGROUND = 6,
    FILE_ANIMATION = 7,
    FILE_AUDIO = 8,
    FILE_DUMMY = 9
} FileGroupType;

/* Vibration effect IDs passed to StartVibrationEffect() */
typedef enum VibrationEffectId {
    VIBE_EFFECT_STOP = 0,
    VIBE_EFFECT_DIN = 1,
    VIBE_EFFECT_TAIWA = 2, /* Dialogue / conversation vibration */
    VIBE_EFFECT_FLASH = 3, /* Screen flash vibration (Cmd_vibrateflash) */
} VibrationEffectId;

#define VIBE_EFFECT_DEFAULT_DURATION 0x16 /* 22 frames */

#endif
