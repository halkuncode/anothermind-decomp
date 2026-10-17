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

extern void InitControllerIRQSystem(u8* port1Buf, u8* port2Buf);
extern void GsResetInterruptHandlers(void);

const u32 s_NameEntryTileDimensions[4] = {
    0x2020E000,
    0x2030E020,
    0x2040E050,
    0x2050E090,
};
const s32 s_NameEntryYOffsets[6] = {
    0, 0, 0, 0x90, 0x90, 0x90,
};
const s32 s_NameEntryXOffsets[6] = {
    0x38, 0x58, 0x78, 0x38, 0x58, 0x78,
};
const u32 s_DefaultHeroNameGlyphs[8] = {
    0x03B4070B, 0x00000000, 0x000005EB, 0x00000000, 0x06E50457, 0x00000000, 0x06810407, 0x00000000,
};
const u32 s_DrawEnvPrimitiveTemplates[92] = {
    0x00000000, 0xDDC00000, 0x00000000, 0x00000000, 0x00000080, 0xDDC00000, 0x00000000, 0x00000000, 0x00230059,
    0x1040F000, 0x00007800, 0x00000000, 0x002300A9, 0x1040F040, 0x00007800, 0x00000000, 0x00200000, 0x1000F080,
    0x00007800, 0x00000000, 0x00000020, 0xC8B00000, 0x00007800, 0x00000000, 0x009800E8, 0x102080C0, 0x00007880,
    0x00000000, 0x00A800E8, 0x104090C0, 0x00007880, 0x00000000, 0x009800E8, 0x1020A0C0, 0x00007880, 0x00000000,
    0x008800E8, 0x1020B0C0, 0x00007880, 0x00000000, 0x003800E8, 0x203030C8, 0x00007800, 0x00000000, 0x008800D8,
    0x301000F0, 0x00007A00, 0x00000000, 0x006800E8, 0x102068C8, 0x00007900, 0x00000000, 0x00600050, 0x2020E000,
    0x00007940, 0x00000001, 0x003A0020, 0xFFFF0000, 0x00007880, 0x00000000, 0x00500050, 0x3888C800, 0x000079C0,
    0x00000000, 0x00640061, 0x1080F000, 0x00007800, 0x00000000, 0x004A0020, 0x20FF0000, 0x000078C0, 0x00000000,
    0x003800D8, 0x201030B8, 0x00007A00, 0x00000000, 0x00180028, 0x20501800, 0x00007A40, 0x00000001, 0x00180078,
    0x20501800, 0x00007A40, 0x00000001, 0x002300A9, 0x102000B8, 0x00007800, 0x00000000, 0x00500050, 0x20707890,
    0x00007A80, 0x00000000,
};
const char s_ManoLabel[] = "mano :  ";
const char s_HitomiLabel[] = "\nhitomi :  ";

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

const char s_PadDebugNumber[] = "pad debug number = ";
const char s_PadType[] = "pad type =";
const char s_NegiCon[] = "negi con\n";
const char s_GunConKonami[] = "gun con -konami-\n";
const char s_AnalogJoyStick[] = "annlog joy stick\n";
const char s_GunConNamco[] = "gun con -namco-\n";
const char s_AnalogController[] = "analog controlor\n";
const char s_PadState[] = "pad state =";
const char s_NoController[] = "no controlor\n";
const char s_FindCtp1[] = "Find CTP1\n";
const char s_RequestInfo[] = "Reqest Info\n";
const char s_ExecCommand[] = "Exec Command\n";
const char s_Undifine[] = "undifine\n";
const char s_MotorH[] = "Motor H =";
const char s_MotorL[] = " : Motor L =";
const char s_VibrateState[] = "VibrateState = ";
const char s_VibrateOff[] = "Vibrate : OFF\n";
const char s_VibrateOn[] = "Vibrate : ON\n";

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

void ResetControllerIRQSystem(void) {
    InitControllerIRQSystem(g_ControllerPort1Buffer, g_ControllerPort2Buffer);
    GsResetInterruptHandlers();
}

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
