#ifndef GAME_H
#define GAME_H

/* Vibration effect IDs passed to StartVibrationEffect() */
typedef enum VibrationEffectId {
    VIBE_EFFECT_STOP = 0,
    VIBE_EFFECT_DIN = 1,
    VIBE_EFFECT_TAIWA = 2, /* Dialogue / conversation vibration */
    VIBE_EFFECT_FLASH = 3, /* Screen flash vibration (Cmd_vibrateflash) */
} VibrationEffectId;

#define VIBE_EFFECT_DEFAULT_DURATION 0x16 /* 22 frames */

#endif
