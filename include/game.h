#ifndef GAME_H
#define GAME_H

#include "progdata.h"

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
    DIR_VIDEO = 0,
    DIR_SYSTEM = 1,
    DIR_DICT = 2,
    DIR_DIALOG = 3,
    DIR_MENU = 4,
    DIR_SCRIPT = 5,
    DIR_BACKGROUND = 6,
    DIR_ANIMATION = 7,
    DIR_AUDIO = 8,
    DIR_DUMMY = 9
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
