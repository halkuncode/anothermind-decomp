//! PSYQ=4.0
#include "common.h"
#include "akao.h"
#include "libspu.h"

// keep stucts inside the C file.
//  16.16 fixed point volume
typedef union {
    s32 val;
    struct {
        s16 lo;
        s16 hi;
    } i;
} AkaoCdVol; /* size = 0x4 */

typedef struct {
    /* 0x0 */ s32 opcode;
    /* 0x4 */ s8 start;
    /* 0x5 */ s8 pad5[3];
    /* 0x8 */ s32 steps;
    /* 0xC */ s8 target;
} AkaoTempoPitchSlide;

typedef struct {
    /* 0x00 */ u32 voice_id;
    /* 0x04 */ u32 mask;
    /* 0x08 */ u32 addr;
    /* 0x0C */ u32 loop_addr;
    /* 0x10 */ s32 a_mode;
    /* 0x14 */ s32 s_mode;
    /* 0x18 */ s32 r_mode;
    /* 0x1C */ u16 pitch;
    /* 0x1E */ u16 ar;
    /* 0x20 */ u16 dr;
    /* 0x22 */ u16 sl;
    /* 0x24 */ s16 sr;
    /* 0x26 */ u16 rr;
    /* 0x28 */ u16 drumKey;
    /* 0x2A */ s16 vol_l;
    /* 0x2C */ s16 vol_r;
    /* 0x2E */ u16 pad2E;
} AkaoVoiceAttr; /* size = 0x30 */

typedef struct {
    /* 0x00 */ u32 addr;
    /* 0x04 */ u32 loopAddr;
    /* 0x08 */ s32 pitch[12];
    /* 0x38 */ u8 ar;
    /* 0x39 */ u8 dr;
    /* 0x3A */ u8 sl;
    /* 0x3B */ s8 sr;
    /* 0x3C */ u8 rr;
    /* 0x3D */ u8 aMode;
    /* 0x3E */ u8 sMode;
    /* 0x3F */ u8 rMode;
} AkaoInstrument; /* size = 0x40 */

typedef struct AkaoChannel {
    /* 0x00 */ u8* akaoSequencePointer;
    /* 0x04 */ u8* loopPoint[4];
    /* 0x14 */ u8* drumOffset;
    /* 0x18 */ s16* vibratoWave;
    /* 0x1C */ s16* tremoloWave;
    /* 0x20 */ s16* panLfoWave;
    /* 0x24 */ u32 overlayChannelId;
    /* 0x28 */ s32 alternativeChannelId;
    /* 0x2C */ s32 volumeMultiplier;
    /* 0x30 */ s32 basePitch;
    /* 0x34 */ u32 updateFlags;
    /* 0x38 */ u32 pitchMulSound;
    /* 0x3C */ s32 pitchMulSoundSlideStep;
    /* 0x40 */ s32 pitchSlide;
    /* 0x44 */ s32 volumeLevel;
    /* 0x48 */ s32 volSlideStep;
    /* 0x4C */ s32 pitchSlideStep;
    /* 0x50 */ u32 setToMinusOne;
    /* 0x54 */ u16 playingType;
    /* 0x56 */ u16 tempoSlideSteps;
    /* 0x58 */ u16 tempoSlideStep;
    /* 0x5A */ u16 pad5A;
    /* 0x5C */ u16 reverbDepthSlideSteps;
    /* 0x5E */ u16 noiseClockFreq;
    /* 0x60 */ u16 channelFlags;
    /* 0x62 */ u16 length1;
    /* 0x64 */ u16 length2;
    /* 0x66 */ u16 currentInstrument;
    /* 0x68 */ u16 pitchMulSoundSlideSteps;
    /* 0x6A */ u16 reverbDelay;
    /* 0x6C */ u16 reverbDelayCur;
    /* 0x6E */ u16 loopTimes0;
    /* 0x70 */ u16 loopTimes[4];
    /* 0x78 */ u16 loopTimes2[4];
    /* 0x80 */ u16 masterVol;
    /* 0x82 */ u16 pad82;
    /* 0x84 */ u16 pad84;
    /* 0x86 */ u16 volSlideSteps;
    /* 0x88 */ u16 pad88;
    /* 0x8A */ u16 volBalanceSlideSteps;
    /* 0x8C */ u16 volPan;
    /* 0x8E */ s16 volPanSlideSteps;
    /* 0x90 */ u16 pitchSlideStepsCur;
    /* 0x92 */ u16 octave;
    /* 0x94 */ u16 pitchSlideSteps;
    /* 0x96 */ u16 keyStored;
    /* 0x98 */ u16 portamentoSteps;
    /* 0x9A */ u16 sfxMask;
    /* 0x9C */ u16 pad9C;
    /* 0x9E */ u16 vibratoDelay;
    /* 0xA0 */ u16 vibratoDelayCur;
    /* 0xA2 */ u16 vibratoRate;
    /* 0xA4 */ u16 vibratoRateCur;
    /* 0xA6 */ u16 vibratoType;
    /* 0xA8 */ u16 vibratoBase;
    /* 0xAA */ u16 vibratoDepth;
    /* 0xAC */ u16 vibratoDepthSlideSteps;
    /* 0xAE */ s16 vibratoDepthSlideStep;
    /* 0xB0 */ u16 padB0;
    /* 0xB2 */ u16 tremoloDelay;
    /* 0xB4 */ u16 tremoloDelayCur;
    /* 0xB6 */ u16 tremoloRate;
    /* 0xB8 */ u16 tremoloRateCur;
    /* 0xBA */ u16 tremoloType;
    /* 0xBC */ u16 tremoloDepth;
    /* 0xBE */ u16 tremoloDepthSlideSteps;
    /* 0xC0 */ s16 tremoloDepthSlideStep;
    /* 0xC2 */ u16 padC2;
    /* 0xC4 */ u16 panLfoRate;
    /* 0xC6 */ u16 panLfoRateCur;
    /* 0xC8 */ u16 panLfoType;
    /* 0xCA */ u16 panLfoDepth;
    /* 0xCC */ u16 panLfoDepthSlideSteps;
    /* 0xCE */ s16 panLfoDepthSlideStep;
    /* 0xD0 */ u16 noiseSwitchDelay;
    /* 0xD2 */ u16 pitchLfoSwitchDelay;
    /* 0xD4 */ u16 loopId;
    /* 0xD6 */ s16 lengthStored;
    /* 0xD8 */ s16 lengthFixed;
    /* 0xDA */ s16 padDA;
    /* 0xDC */ s16 reverbDepthSlideStep;
    /* 0xDE */ s16 volBalance;
    /* 0xE0 */ s16 volBalanceSlideStep;
    /* 0xE2 */ s16 volPanSlideStep;
    /* 0xE4 */ u16 transpose;
    /* 0xE6 */ s16 fineTuning;
    /* 0xE8 */ u16 key;
    /* 0xEA */ s16 keyAdd;
    /* 0xEC */ u16 transposeStored;
    /* 0xEE */ s16 vibratoPitch;
    /* 0xF0 */ s16 tremoloVol;
    /* 0xF2 */ s16 panLfoVol;
    /* 0xF4 */ AkaoVoiceAttr voiceAttr;
} AkaoChannel; /* size = 0x124 */

// Each sound effect slot occupies a stereo voice pair (2 audio channels, 0x248 bytes).
typedef struct {
    AkaoChannel voices[2];
} AkaoSoundSlot; /* size = 0x248 */

typedef struct {
    /* 0x00 */ u32 stereoMono;
    /* 0x04 */ u32 activeMask;
    /* 0x08 */ u32 onMask;
    /* 0x0C */ u32 keyedMask;
    /* 0x10 */ u32 offMask;
    /* 0x14 */ u32 activeMaskStored;
    /* 0x18 */ u32 unk18;
    /* 0x1C */ u32 unk1C;
    /* 0x20 */ u32 tempo;
    /* 0x24 */ s32 tempoSlideStep;
    /* 0x28 */ u32 tempoUpdate;
    /* 0x2C */ u32 overMask;
    /* 0x30 */ u32 altMask;
    /* 0x34 */ u32 updateFlags;
    /* 0x38 */ u32 noiseMask;
    /* 0x3C */ u32 reverbMask;
    /* 0x40 */ u32 pitchLfoMask;
    /* 0x44 */ s32 reverbDepth;
    /* 0x48 */ s32 reverbDepthSlideStep;
    /* 0x4C */ s32 vol;
    /* 0x50 */ s32 volSlideStep;
    /* 0x54 */ s16 volSlideSteps;
    /* 0x56 */ u16 tempoSlideSteps;
    /* 0x58 */ u16 musicId;
    /* 0x5A */ u16 condition;
    /* 0x5C */ u16 reverbDepthSlideSteps;
    /* 0x5E */ u16 timerTopCur;
} AkaoChannelConfig;

typedef struct {
    /* 0x00 */ u16 opcode;
    /* 0x02 */ u16 pad;
    /* 0x04 */ u16 param0;
    /* 0x06 */ u16 param0_hi;
    /* 0x08 */ s32 param1;
    /* 0x0C */ s32 param2;
    /* 0x10 */ s32 param3;
    /* 0x14 */ s32 param4;
    /* 0x18 */ s32 param5;
    /* 0x1C */ s32 param6;
    /* 0x20 */ s32 param7;
} AkaoQueuedCommand; /* size = 0x24 */

typedef struct {
    /* 0x0 */ u32 opcode;
    /* 0x4 */ s32 steps;
    /* 0x8 */ s32 targetVol;
} AkaoVolSlideFromCurr;

typedef struct {
    /* 0x0 */ u32 opcode;
    /* 0x4 */ s32 steps;
    /* 0x8 */ s32 startVol;
    /* 0xC */ s32 targetVol;
} AkaoVolSlideBetweenTargets;

typedef struct {
    /* 0x0 */ u32 opcode;
    /* 0x4 */ s32 steps;
    /* 0x8 */ u16 targetVol;
} AkaoCdVolSlideFromCurr;

typedef struct {
    /* 0x0 */ u32 opcode;
    /* 0x4 */ s32 steps;
    /* 0x8 */ u16 startVol;
    /* 0xA */ u16 padA;
    /* 0xC */ u16 targetVol;
    /* 0xE */ u16 padE;
} AkaoCdVolSlideBetweenTargets;

typedef struct {
    /* 0x0 */ s32 opcode;
    /* 0x4 */ s32 steps;
    /* 0x8 */ s8 target;
} AkaoSlideFromCurr;

typedef struct {
    /* 0x0 */ u32 opcode;
    /* 0x4 */ u16 pan;
} AkaoSetReverbPan;

typedef struct {
    /* 0x0 */ u32 opcode;
    /* 0x4 */ u8 mul;
} AkaoSetReverbMul;

typedef struct {
    /* 0x0 */ s32 pitchSlide;
    /* 0x4 */ s32 volSlide;
    /* 0x8 */ s16 currentKey;
    /* 0xA */ s16 padA;
} AkaoVoiceWork; /* size = 0xC */

extern s32 g_AudioInitialized;
extern AkaoChannelConfig* g_AkaoChannelConfig;

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", InitSoundDriver);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", ShutdownSoundSystem);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", EnsureSeLoopBlockInitialized);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoCmd_10_PlayMusic);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", ResetSoundSystem);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_8002DF24);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoCmd_12_PlayMusicFade);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_8002DF80);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", PlaySoundEffect_8002DFB4);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoCmd_24_PlayConsecutiveSound);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", StopSoundEffect);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoCmd_30_PlayMenuSound);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_8002E104);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", IsResourceLoaded);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoSetStereoMonoMode);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoCmd_90_SetMuteMusicMask);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoCmd_92_SetCondition);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", ApplySoundProfile);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoFlushPendingUpdates);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoCmd_A8_SetPanSlot2);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoCmd_A9_SetPanSlot1);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoCmd_A0_SetVolBalanceSlot2);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoCmd_A1_SetVolBalanceSlot1);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoCmd_AA_SetPanSlot0);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoCmd_AB_SetPanSlot3);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", PlaySystemSound);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoCmd_A3_SetVolBalanceSlot3);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoCmd_AC_SlidePanSlot2);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoCmd_AD_SlidePanSlot1);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", PlaySoundEffect_8002E5F0);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoCmd_A5_SlideVolBalanceSlot1);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", PlayMusicTrack_8002E690);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", SendMusicStopCommand);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", PlayMusicTrackWithPanVol);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoCmd_C8_SetCdVol);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoCmd_C9_CdVolSlideFromCurr);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", SendSoundConfigCommand);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", SendMusicLayerResetCommand);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", SetMusicLayerTrack);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", SetMusicLayerTrackPan);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoCmd_D4_SetPitch);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", ReleaseMusicLayerTrack);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoCmd_D6_PitchSlideBetweenTargets);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", ResetAndStopMusicLayer);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", OverrideMusicLayerTrack);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", OverrideMusicLayerTrackWithPan);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoCmd_F0_StopMusic);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", CutSoundEffect);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", DecompressWaveMusic);

s32 IsAudioInitialized(void) { return g_AudioInitialized; }

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", InstallAkaoProgramFromBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_8002EB34);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", PlayMusicTrack_8002EBC8);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", StopAllMusic);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", SetActiveMusicBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", CrossfadeToBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", SetSecondaryMusicBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_8002ED04);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_8002EDD0);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_8002EE0C);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_8002EEB8);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_8002EF3C);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_8002EFB4);

s32 VerifyAkaoMagic(s32* akaoBuffer) { return *akaoBuffer - AKAO_MAGIC; }

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_8002EFF0);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_8002F014);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", SetupAudioEventHandler);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_8002F094);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", WaitForAudioShutdown);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", ProcessAkaoBlockIfValid);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", InstallAkaoAudioProgram);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", ResetAudioState);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", SetupSpuAndAudioEvents);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", InitSeLoopWorkArea);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", StopAndCloseSoundEvents);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoSpuKeyOn);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoSpuKeyOff);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoSpuNoiseOn);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoSpuPitchLfoOn);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoSpuReverbOn);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoSpuSetVoiceVolume);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoSpuSetVoicePitch);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoSpuSetVoiceStartAddress);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoSpuSetVoiceLoopAddress);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoSpuSetVoiceAttackRate);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoSpuSetVoiceDecayRate);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoSpuSetVoiceSustainLevel);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoSpuSetVoiceSustainRate);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoSpuSetVoiceReleaseRate);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoUpdateChannelParamsToSpu);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoUpdateChannelAndOvlParamsToSpu);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoMusicUpdateSlideAndDelay);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoMusicUpdatePitchAndVol);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoSoundUpdatePitchAndVol);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoAllocateVoice);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80030928);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80030BE4);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80030C1C);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoUpdateKeysOn);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoCollectChannelsVoicesMask);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoUpdateKeysOff);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80031134);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80031228);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80031244);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80031260);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_8003127C);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80031314);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AdjustAudioEventAddresses);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80031394);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_8003166C);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_800316F8);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80031A40);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80031B98);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80031BF4);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80031DEC);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80031E64);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80031EAC);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80031F00);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_8003214C);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_8003217C);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_8003220C);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80032260);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_800322B4);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80032300);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80032380);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_800323E8);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80032520);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_8003254C);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_800325B4);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80032668);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_8003272C);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80032760);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_800327C8);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80032838);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80032920);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80032AA0);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80032B1C);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80032BE4);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80032CC4);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80032E3C);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80032EB4);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80032F78);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80033058);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_800331E0);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80033258);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80033324);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80033340);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_800333A8);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_8003341C);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80033438);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_800334A0);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80033514);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_8003354C);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80033588);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80033678);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_800336B8);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_800336F8);

void AkaoSetChannelCondition(AkaoQueuedCommand* cmd) { g_AkaoChannelConfig->condition = cmd->param0; }

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_8003374C);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_8003383C);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_800338E0);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_800339FC);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80033A94);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80033AE4);

void func_80033B38(void) {}

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoExecuteCommandsQueue);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoGetCommandQueue);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", SetReverbModeIfDifferent);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", ClearMusicStateIfMatches);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoExec);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80034114);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80034134);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoUpdateGlobalSlides);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoMainUpdate);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoMain);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoGetNextNote);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80034C18);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80034C40);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80034D5C);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80034E78);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80034ECC);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80034F68);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoExecuteSequence);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80035878);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_8003591C);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80035954);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_A0_FinishChannel);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_E8_Tempo);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_E9_TempoSlide);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_EA_ReverbDepth);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_EB_ReverbDepthSlide);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_EE_Jump);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_EF_JumpConditional);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_A3_MasterVol);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_FA_VolSlideFromCurr);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_A8_SetVol);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_A9_SetVolSlide);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_FE19_PanSlideFromCurr);

void AkaoOp_FE1A_VoiceEffectOn(AkaoChannel* track) { track->updateFlags |= AKAO_UPDATE_VOICE_EFFECT; }

void AkaoOp_FE1B_VoiceEffectOff(AkaoChannel* track) { track->updateFlags &= ~AKAO_UPDATE_VOICE_EFFECT; }

void AkaoOp_F4_OverlayVoiceOn(AkaoChannel* track) {
    track->akaoSequencePointer += 2; // skip!
}

void AkaoOp_F5_OverlayVoiceOff(void) {}

void AkaoOp_F6_OverlayVolBalance(AkaoChannel* track) {
    u8 val = *track->akaoSequencePointer;
    track->akaoSequencePointer++;

    track->volBalanceSlideSteps = 0;
    track->volBalance = val << 8;
    if (track->updateFlags & AKAO_UPDATE_OVERLAY) {
        track->voiceAttr.mask |= AKAO_UPDATE_SPU_VOICE;
    }
}

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_F7_OverlayVolBalanceSlide);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_AA_SetPan);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_AB_SetPanSlide);

void AkaoOp_A5_SetOctave(AkaoChannel* track) {
    u8* seq = track->akaoSequencePointer;
    u8 val = *seq++;
    track->akaoSequencePointer = seq;
    track->octave = val;
}

void AkaoOp_A6_IncOctave(AkaoChannel* track) { track->octave = (track->octave + 1) & 0xF; }

void AkaoOp_A7_DecOctave(AkaoChannel* track) { track->octave = (track->octave - 1) & 0xF; }

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_A1_LoadInstrument);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_F2_LoadInstrument);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_FC_CustomInstrumentMap);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_B3_ResetAdsr);

void AkaoOp_C0_TransposeAbsolute(AkaoChannel* track) {
    u8* seq = track->akaoSequencePointer;
    s8 val = *seq++;
    track->akaoSequencePointer = seq;
    track->transpose = val;
}

void AkaoOp_C1_TransposeRelative(AkaoChannel* track) {
    u8* seq = track->akaoSequencePointer;
    s8 val = *seq++;
    track->akaoSequencePointer = seq;
    track->transpose = (track->transpose + val);
}

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_A4_PitchBendSlide);

void AkaoOp_DA_PortamentoOn(AkaoChannel* track) {
    u8* seq = track->akaoSequencePointer;
    u8 val = *seq;
    track->akaoSequencePointer = seq + 1;

    track->portamentoSteps = val;
    if (val == 0) {
        track->portamentoSteps = 0x100;
    }
    track->transposeStored = 0;
    track->keyStored = 0;
    track->sfxMask = 1;
}

void AkaoOp_DB_PortamentoOff(AkaoChannel* track) { track->portamentoSteps = 0; }

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_D8_FineTuningAbsolute);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_D9_FineTuningRelative);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_B4_Vibrato);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_B5_VibratoDepth);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_DD_VibratoDepthSlide);

void AkaoOp_B6_VibratoOff(AkaoChannel* track) {
    track->vibratoPitch = 0;
    track->updateFlags &= ~AKAO_UPDATE_VIBRATO;
    track->voiceAttr.mask |= SPU_VOICE_PITCH;
}

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_B8_Tremolo);

void AkaoOp_B9_TremoloDepth(AkaoChannel* track) {
    u8* seq = track->akaoSequencePointer;
    u8 val = *seq++;
    track->akaoSequencePointer = seq;

    track->tremoloDepth = (val & 0x7F) << 8;
}

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_DE_TremoloDepthSlideFromCurr);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_BA_TremoloOff);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_BC_SetPanLfo);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_BD_PanLfoDepth);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_DF_PanLfoDepthSlideFromCurr);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_BE_PanLfoOff);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_C4_NoiseOn);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_C5_NoiseOff);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_C6_PitchLfoOn);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_C7_PitchLfoOff);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_C2_ReverbOn);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_C3_ReverbOff);

void AkaoOp_CC_LegatoOn(AkaoChannel* track) { track->sfxMask = AKAO_SFX_LEGATO; }

void AkaoOp_CD_LegatoOff(void) {}

void AkaoOp_D0_FullLengthOn(void) {}

void AkaoOp_D1_FullLengthOff(void) {}

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_AC_NoiseClockFreq);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_AD_SetAr);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_AE_SetDr);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_AF_SetSl);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_B1_SetSr);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_B2_SetRr);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_B7_AttackMode);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_BB_SustainMode);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_BF_ReleaseMode);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_F8_AltVoiceOn);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_F9_AltVoiceOff);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_C8_LoopPoint);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_C9_LoopReturnTimes);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_F0_LoopJumpTimes);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_F1_LoopBreakTimes);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_CA_LoopReturn);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_A2_NextNoteLength);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_DC_FixNoteLength);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_EC_DrumModeOn);

void AkaoOp_ED_DrumModeOff(AkaoChannel* track)
{
    track->voiceAttr.drumKey = 0;
    track->updateFlags &= ~AKAO_UPDATE_DRUM_MODE;
}

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_FD_TimeSignature);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_FE_MeasureNumber);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_B0_SetVoiceDrSl);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_CE_NoiseSwitch);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_CF_NoiseSwitch);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_D2_FrequencyModulationSwitch);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_D3_FrequencyModulationSwitch);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_CB_SfxReset);

void AkaoOp_D4_SideChainPlaybackOn(AkaoChannel* track) { track->updateFlags |= AKAO_UPDATE_SIDE_CHAIN_PITCH; }

void AkaoOp_D5_SideChainPlaybackOff(AkaoChannel* track) { track->updateFlags &= ~AKAO_UPDATE_SIDE_CHAIN_PITCH; }

void AkaoOp_D6_SideChainPitchVolOn(AkaoChannel* track) { track->updateFlags |= AKAO_UPDATE_SIDE_CHAIN_VOL; }

void AkaoOp_D7_SideChainPitchVolOff(AkaoChannel* track) { track->updateFlags &= ~AKAO_UPDATE_SIDE_CHAIN_VOL; }

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_F3_MuteMusic);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_FF_ReverbDelay);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_FE18_ReverbDepthSlideFromCurr);

void AkaoOp_E0_VoiceBusRoutingOn(AkaoChannel* track) { track->updateFlags |= AKAO_UPDATE_VOICE_BUS; }

void AkaoOp_Null(void) { AkaoOp_A0_FinishChannel(); }

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80037578);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_8003760C);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80037690);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80037708);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80037750);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80037968);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80037B24);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80037BF4);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80037C58);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80037CBC);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80037E08);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80037E38);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80037E68);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80037E98);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80037EC8);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80037F10);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80037F30);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80037FA0);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80038020);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_8003816C);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80038198);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_8003826C);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80038434);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_800385D0);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_8003861C);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80038660);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80038698);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_800386E4);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80038830);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_800388AC);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80038948);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80038A18);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80038A7C);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80038BB8);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80038BE8);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80038C18);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80038C64);
