#ifndef GAME_H
#define GAME_H

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
