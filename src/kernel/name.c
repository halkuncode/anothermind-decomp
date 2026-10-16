#include "common.h"
#include "game.h"

#define VIBE_DATA_BUFFER_SIZE 1200

extern u8 g_ControllerTypeId[16];
extern s32 g_CurrVibrationMode;
extern s32 g_VibrationEffectFrameCount;
extern s32 g_VibeDataBuffer[VIBE_DATA_BUFFER_SIZE];
extern s8 g_PrimaryVibrationBuffer;
extern s8 g_VibrationCycleCounter;
extern s32 g_VibrationStateFlag[4];
extern s32 g_VibrationSegmentIndex[4];
extern u8 g_ControllerPort1Buffer[];
extern u8 g_ControllerPort2Buffer[];

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", RunNameEntryScreen);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", UpdateNameEntryKeyboardInput);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", StartKanaToKanjiConversion);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", LoadTextGraphics);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", LookupFepCandidates);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", InitDrawEnvEffects);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", RenderNameEntryScreen);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", DebugPrintNameBuffers);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", InitNameEntryScreen);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", GetHeroEnteredNameLength);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", DrawNameEntryTitle);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", CopyNameBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", WriteNameToGameBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", LoadNameFont);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", DrawNameFontGlyph);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", DeleteGlyphFromNameBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", InitializeNameBuffers);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", InitNameEntryBuffers);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", LoadDefaultNameIfEmpty);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", SetNameEntryColor);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", DrawNameBufferPreview);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", WriteNameGlyphAndMetadata);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", InsertNameSpaceOrAdvance);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", HandleNameConfirmOrCancel);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", CommitKanaWithoutConversion);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", ConvertKanaToKatakana);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", GetHeroineEnteredNameLength);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", StartVibrationEffect);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", DisplayPadDebugPanel);

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

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", ResetControllerIRQSystem);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", GetRawControllerInput);

s32 PlaySfx(s16 arg0) { PlaySingleSoundeffect(arg0); }

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", ApplyControllerVibrationDirect);

void SetVibrationModeDirect(s32 mode) {
    g_CurrVibrationMode = mode;
    if (!mode) {
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

u8* GetControllerBuffer(s32 port) {
    if (!port) {
        return g_ControllerPort1Buffer;
    }
    return g_ControllerPort2Buffer;
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", GetNextInterpolatedByte);

void LoadVibrationVIBFile(vibeId) { LoadByFileIdGroupId(vibeId, 1, g_VibeDataBuffer, VIBE_DATA_BUFFER_SIZE); }

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", ResetVibrationSystem);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", UpdateVibrationAndInput);

s32 IsVibrationActive(void) {
    s32 flag = (u32)g_VibrationStateFlag[0] > 0;
    if (g_VibrationSegmentIndex[0]) {
        flag = 1;
    }
    return flag;
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", GetControllerPadButtons);

u8 GetControllerType(void) { return g_ControllerTypeId[0] >> 4; }

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", DisplayPadDebugNumber);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", DisplayControllerTypeDebug);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", DisplayPort2ControllerTypeDebug);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", DisplayVibrationBufferDebug);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", DisplayVibrationStateDebug);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/name", DisplayVibrationModeDebug);
