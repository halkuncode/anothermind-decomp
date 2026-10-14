#include "common.h"
#include "game.h"

#define VIBE_DATA_BUFFER_SIZE 1200



extern u8 g_ControllerTypeId[16];
extern s32 g_CurrVibrationMode;
extern s32 g_VibrationEffectFrameCount;
extern s32 g_VibeDataBuffer[VIBE_DATA_BUFFER_SIZE];




INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", RunNameEntryScreen);

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", func_80013CE4);

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", func_800141E8);

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", LoadTextGraphics);

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", func_80014530);

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", InitDrawEnvEffects);

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", RenderNameEntryScreen);

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", func_80014C90);

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", InitNameEntryScreen);

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", GetEnteredNameLength_80014F5C);

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", DrawNameEntryTitle);

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", CopyNameBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", WriteNameToGameBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", LoadNameFont);

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", DrawNameFontGlyph);

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", DeleteGlyphFromNameBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", InitializeNameBuffers);

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", InitNameEntryBuffers);

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", LoadDefaultNameIfEmpty);

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", SetNameEntryColor);

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", DrawNameBufferPreview);

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", WriteNameGlyphAndMetadata);

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", func_800156F8);

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", HandleNameConfirmOrCancel);

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", func_80015800);

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", func_80015868);

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", GetEnteredNameLength_800158E8);

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", StartVibrationEffect);

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", DisplayPadDebugPanel);

void BeginFlashVibration(void) {
    StartVibrationEffect(VIBE_EFFECT_FLASH);
    g_VibrationEffectFrameCount = VIBE_EFFECT_DEFAULT_DURATION;
}

void BeginTaiwaVibration(void) {
    StartVibrationEffect(VIBE_EFFECT_TAIWA);
    g_VibrationEffectFrameCount = VIBE_EFFECT_DEFAULT_DURATION;
}

void StopVibrationEffect(void);

void CancelVibrationEffect(void) {
    StopVibrationEffect();
    g_VibrationEffectFrameCount = 0;
}

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", ResetControllerIRQSystem);

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", GetRawControllerInput);

s32 PlaySfx(s16 arg0) { PlaySingleSoundeffect(arg0); }

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", SetVibrationMode_80015E70);

extern s8 g_PrimaryVibrationBuffer;
extern s8 g_VibrationCycleCounter;
extern s32 g_VibrationStateFlag[4];
extern s32 g_VibrationSegmentIndex[4];

void SetVibrationModeDirect(s32 mode) {
    g_CurrVibrationMode = mode;
    if (mode == 0) {
        g_VibrationStateFlag[0] = 0;
        g_PrimaryVibrationBuffer = 0;
        g_VibrationSegmentIndex[0] = 0;
        g_VibrationCycleCounter = 0;
    }
}

s32 IsVibrationEnabled(void) { return g_CurrVibrationMode; }

void StopVibrationEffect(void) {
    g_VibrationStateFlag[0] = 0;
    g_PrimaryVibrationBuffer = 0;
    g_VibrationSegmentIndex[0] = 0;
    g_VibrationCycleCounter = 0;
}

extern u8 g_ControllerPort1Buffer[];
extern u8 g_ControllerPort2Buffer[];

u8* GetControllerBuffer(s32 port) {
    if (port == 0) {
        return g_ControllerPort1Buffer;
    }
    return g_ControllerPort2Buffer;
}

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", GetNextInterpolatedByte);




void LoadVibrationVIBFile(vibeId)
{
    LoadByFileIdGroupId(vibeId, 1, g_VibeDataBuffer, VIBE_DATA_BUFFER_SIZE);
}

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", ResetVibrationSystem);

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", UpdateVibrationAndInput);

s32 IsVibrationActive(void) {
    s32 flag = (u32)g_VibrationStateFlag[0] > 0;
    if (g_VibrationSegmentIndex[0] != 0) {
        flag = 1;
    }
    return flag;
}

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", func_800161A0);

u8 GetControllerType(void) { return g_ControllerTypeId[0] >> 4; }

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", func_80016200);

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", func_8001623C);

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", func_80016300);

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", func_800163B0);

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", func_80016404);

INCLUDE_ASM("asm/jp/nonmatchings/main/name_entry", func_80016468);
