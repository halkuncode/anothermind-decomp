#ifndef GAME_H
#define GAME_H

#include "progdata.h"

// Display resolution
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

// Ampack archive header magic bytes
#define AMPACK_MAGIC_0 0xC3
#define AMPACK_MAGIC_1 0xFF

// LZSS compression parameters
#define LZSS_WINDOW_SIZE 4096
#define LZSS_WINDOW_MASK (LZSS_WINDOW_SIZE - 1) // 0xFFF
#define LZSS_WINDOW_INIT_INDEX 0xFEE

// Well-known memory buffer addresses
#define PROGDATA_LOAD_ADDR ((u8*)0x80138000)
#define PROGDATA_LOAD_MAX_SIZE 0x30000
#define PROGDATA_UNPACK_ADDR ((u8*)0x80168000)
#define DEBUG_UNPACK_SRC_ADDR ((u8*)0x80160000)

typedef enum {
    /* 0x00 */ DIR_VIDEO = 0,
    /* 0x01 */ DIR_SYSTEM = 1,
    /* 0x02 */ DIR_DICT = 2,
    /* 0x03 */ DIR_DIALOG = 3,
    /* 0x04 */ DIR_MENU = 4,
    /* 0x05 */ DIR_SCRIPT = 5,
    /* 0x06 */ DIR_BACKGROUND = 6,
    /* 0x07 */ DIR_ANIMATION = 7,
    /* 0x08 */ DIR_AUDIO = 8,
    /* 0x09 */ DIR_DUMMY = 9,
} FileGroupType;

// Vibration effect IDs passed to StartVibrationEffect()
typedef enum VibrationEffectId {
    /* 0x00 */ VIBE_EFFECT_STOP = 0,
    /* 0x01 */ VIBE_EFFECT_DIN = 1,
    /* 0x02 */ VIBE_EFFECT_TAIWA = 2, // Dialogue / conversation vibration
    /* 0x03 */ VIBE_EFFECT_FLASH = 3, // Screen flash vibration (Cmd_vibrateflash)
} VibrationEffectId;

#define VIBE_EFFECT_DEFAULT_DURATION 0x16 // 22 frames

// Debug text overlay dimensions & buffer
#define DEBUG_TEXT_COLUMNS 32
#define DEBUG_TEXT_ROWS 20
#define DEBUG_TEXT_MAX_ROWS 21
#define DEBUG_TEXT_BUFFER_SIZE 0x280       // 640 bytes (32 * 20)
#define DEBUG_TEXT_BOTTOM_ROW_OFFSET 0x260 // Row 19 offset (19 * 32 = 608)
#define DEBUG_MAX_DRAW_PRIMITIVES 0x4B     // Maximum ordering-table primitive packets (75)

// Debug view panel modes (g_DebugViewMode)
#define DEBUG_VIEW_NONE 0
#define DEBUG_VIEW_VM 1     // Pad 1 Start: VM & Script Engine Debugger
#define DEBUG_VIEW_SYSTEM 2 // Pad 2 Start / R1: System, CD & Movie Diagnostics

// Debug display page IDs (g_DebugDisplayPageId, cycled with L2 / R2)
#define DEBUG_PAGE_MAIN_MENU 0     // Page 0: Main VM script debug menu
#define DEBUG_PAGE_SCENE_SCRIPT 1  // Page 1: Scene script inspector
#define DEBUG_PAGE_BACKGROUND 2    // Page 2: Background image & mode inspector
#define DEBUG_PAGE_CHR_SLOT0 3     // Page 3: Character slot 0 sprite viewer
#define DEBUG_PAGE_MSG_BOX_SLOT0 4 // Page 4: Character 0 message box layout
#define DEBUG_PAGE_CHR_SLOT1 5     // Page 5: Character slot 1 sprite viewer
#define DEBUG_PAGE_MSG_BOX_SLOT1 6 // Page 6: Character 1 message box layout

// Variable / memory inspection bit-width modes (8-bit vs 16-bit wide variables)
#define MEM_VIEW_8BIT 1
#define MEM_VIEW_16BIT 2

#endif
