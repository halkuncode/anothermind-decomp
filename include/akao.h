#ifndef AKAO_H
#define AKAO_H

#include "common.h"

#define AKAO_MAGIC 0x4F414B41

#define AKAO_PAN_LEFT 0x00
#define AKAO_PAN_CENTER 0x40
#define AKAO_PAN_RIGHT 0x7F
#define AKAO_PAN_MAX 0x7F
#define AKAO_VOL_MAX 0x7F

#define AKAO_SFX_SLOT_0 0x30
#define AKAO_SFX_SLOT_1 0x32
#define AKAO_SFX_SLOT_2 0x34
#define AKAO_SFX_SLOT_3 0x36

#define AKAO_MUSIC 0x0
#define AKAO_SOUND 0x1
#define AKAO_MENU 0x2

#define AKAO_STEREO 0x1
#define AKAO_MONO 0x2
#define AKAO_STEREO_CHANNELS 0x4

#define AKAO_SFX_LEGATO 0x1
#define AKAO_SFX_FULL_LENGTH 0x4

#define AKAO_CONTROL_PAUSE_MUSIC_UPDATE 0x001
#define AKAO_CONTROL_PAUSE_UPDATE 0x002
#define AKAO_CONTROL_REVERB_ENABLE 0x010
#define AKAO_CONTROL_STATE_SAVED 0x100

#define AKAO_UPDATE_SPU_VOICE (SPU_VOICE_VOLL | SPU_VOICE_VOLR)
#define AKAO_UPDATE_SPU_ADSR                                                                                           \
    (SPU_VOICE_ADSR_AMODE | SPU_VOICE_ADSR_SMODE | SPU_VOICE_ADSR_RMODE | SPU_VOICE_ADSR_AR | SPU_VOICE_ADSR_DR |      \
     SPU_VOICE_ADSR_SR | SPU_VOICE_ADSR_RR | SPU_VOICE_ADSR_SL)
#define AKAO_UPDATE_SPU_BASE_WOR                                                                                       \
    (SPU_VOICE_WDSA | SPU_VOICE_ADSR_AMODE | SPU_VOICE_ADSR_SMODE | SPU_VOICE_ADSR_AR | SPU_VOICE_ADSR_DR |            \
     SPU_VOICE_ADSR_SR | SPU_VOICE_ADSR_SL | SPU_VOICE_LSAX)
#define AKAO_UPDATE_SPU_BASE (AKAO_UPDATE_SPU_BASE_WOR | SPU_VOICE_ADSR_RMODE | SPU_VOICE_ADSR_RR)
#define AKAO_UPDATE_SPU_ALL (AKAO_UPDATE_SPU_BASE | AKAO_UPDATE_SPU_VOICE | SPU_VOICE_PITCH)

#define AKAO_UPDATE_VIBRATO 0x1
#define AKAO_UPDATE_TREMOLO 0x2
#define AKAO_UPDATE_PAN_LFO 0x4
#define AKAO_UPDATE_DRUM_MODE 0x8
#define AKAO_UPDATE_SIDE_CHAIN_PITCH 0x10
#define AKAO_UPDATE_SIDE_CHAIN_VOL 0x20
#define AKAO_UPDATE_VOICE_EFFECT 0x40
#define AKAO_UPDATE_REVERB_DEPTH 0x80
#define AKAO_UPDATE_OVERLAY 0x100
#define AKAO_UPDATE_ALTERNATIVE 0x200
#define AKAO_UPDATE_VOICE_BUS 0x100000
#define AKAO_UPDATE_ADSR_AR 0x1000000
#define AKAO_UPDATE_ADSR_SR 0x8000000
#define AKAO_UPDATE_ADSR_RR 0x10000000

#define AKAO_UPDATE_LFO_MASK                                                                                           \
    (AKAO_UPDATE_VIBRATO | AKAO_UPDATE_TREMOLO | AKAO_UPDATE_PAN_LFO | AKAO_UPDATE_SIDE_CHAIN_PITCH |                  \
     AKAO_UPDATE_SIDE_CHAIN_VOL)

#define AKAO_UPDATE_NOISE_CLOCK 0x10
#define AKAO_UPDATE_REVERB 0x80
#define AKAO_UPDATE_VOICE_MODES 0x100

// SPU Audio Stream Buffer Layout (SPU SRAM addresses & sizes)
#define AKAO_STREAM_BLOCK_SIZE 0x1000
#define AKAO_STREAM_HALF_BLOCK_SIZE 0x800
#define AKAO_STREAM_BUF0_ADDR 0x1100
#define AKAO_STREAM_BUF0_MID (AKAO_STREAM_BUF0_ADDR + AKAO_STREAM_HALF_BLOCK_SIZE)
#define AKAO_STREAM_BUF1_ADDR 0x2100
#define AKAO_STREAM_BUF1_MID (AKAO_STREAM_BUF1_ADDR + AKAO_STREAM_HALF_BLOCK_SIZE)

typedef struct {
    /* 0x00 */ s32 stereoMode;
    /* 0x04 */ s32 updateFlags;
} AkaoControl; // size:0x08

extern AkaoControl g_AkaoControl;

void AkaoUpdateNoiseVoices(void);
void AkaoUpdateReverbVoices(void);
void AkaoUpdatePitchLfoVoices(void);
void AkaoStopStream(void);

// Sequence opcodes (0xA0..0xFF)
#define AKAO_OP_FINISH_CHANNEL 0xA0
#define AKAO_OP_LOOP_RETURN 0xCA

typedef enum {
    AKAO_PLAY_MUSIC = 0x10,
    AKAO_PLAY_MUSIC_FADE = 0x12,
    AKAO_PLAY_MUSIC_SAVE_CURR = 0x14,
    AKAO_PLAY_MUSIC_SWAP_SAVED = 0x15,
    AKAO_FADE_PLAY_MUSIC = 0x18,
    AKAO_FADE_PLAY_MUSIC_SAVE_CURR = 0x19,
    AKAO_PLAY_SOUND = 0x20,
    AKAO_PLAY_TWO_SOUNDS = 0x21,
    AKAO_PLAY_THREE_SOUNDS = 0x22,
    AKAO_PLAY_FOUR_SOUNDS = 0x23,
    AKAO_PLAY_ONE_CONSECUTIVE_SOUND = 0x24,
    AKAO_PLAY_TWO_CONSECUTIVE_SOUNDS = 0x25,
    AKAO_PLAY_THREE_CONSECUTIVE_SOUNDS = 0x26,
    AKAO_PLAY_FOUR_CONSECUTIVE_SOUNDS = 0x27,
    AKAO_PLAY_SLOT2 = 0x28, // Alias for AKAO_PLAY_SOUND
    AKAO_PLAY_SLOT1 = 0x29,
    AKAO_PLAY_SLOT0 = 0x2A,
    AKAO_PLAY_SLOT3 = 0x2B,
    AKAO_PLAY_MENU_SOUND = 0x30,
    AKAO_PLAY_DIRECT = 0x34,
    AKAO_SAVE_CHANNEL_STATE = 0x40,
    AKAO_SET_STEREO_MODE = 0x80,
    AKAO_SET_MONO_MODE = 0x81,
    AKAO_RESET_VOLUME = 0x82,
    AKAO_SET_MUTE_MUSIC_MASK = 0x90,
    AKAO_SET_CONDITION = 0x92,
    AKAO_FLUSH_ALL_PENDING_UPDATES = 0x98,
    AKAO_APPLY_ALL_PENDING_UPDATES = 0x99,
    AKAO_FLUSH_PENDING_MUSIC_UPDATES = 0x9A,
    AKAO_APPLY_PENDING_MUSIC_UPDATES = 0x9B,
    AKAO_FLUSH_PENDING_SFX_UPDATES = 0x9C,
    AKAO_APPLY_PENDING_SFX_UPDATES = 0x9D,
    AKAO_SET_VOL_BALANCE_SLOT2 = 0xA0,
    AKAO_SET_VOL_BALANCE_SLOT1 = 0xA1,
    AKAO_SET_VOL_BALANCE_SLOT0 = 0xA2,
    AKAO_SET_VOL_BALANCE_SLOT3 = 0xA3,
    AKAO_SLIDE_VOL_BALANCE_SLOT2 = 0xA4,
    AKAO_SLIDE_VOL_BALANCE_SLOT1 = 0xA5,
    AKAO_SLIDE_VOL_BALANCE_SLOT0 = 0xA6,
    AKAO_SLIDE_VOL_BALANCE_SLOT3 = 0xA7,
    AKAO_SET_PAN_SLOT2 = 0xA8,
    AKAO_SET_PAN_SLOT1 = 0xA9,
    AKAO_SET_PAN_SLOT0 = 0xAA,
    AKAO_SET_PAN_SLOT3 = 0xAB,
    AKAO_SLIDE_PAN_SLOT2 = 0xAC,
    AKAO_SLIDE_PAN_SLOT1 = 0xAD,
    AKAO_SLIDE_PAN_SLOT0 = 0xAE,
    AKAO_SLIDE_PAN_SLOT3 = 0xAF,
    AKAO_SET_PITCH_SLOT2 = 0xB0,
    AKAO_SET_PITCH_SLOT1 = 0xB1,
    AKAO_SET_PITCH_SLOT0 = 0xB2,
    AKAO_SET_PITCH_SLOT3 = 0xB3,
    AKAO_SLIDE_PITCH_SLOT2 = 0xB4,
    AKAO_SLIDE_PITCH_SLOT1 = 0xB5,
    AKAO_SLIDE_PITCH_SLOT0 = 0xB6,
    AKAO_SLIDE_PITCH_SLOT3 = 0xB7,
    AKAO_SET_ALL_VOL_BALANCE = 0xB8,
    AKAO_SLIDE_ALL_VOL_BALANCE = 0xB9,
    AKAO_SET_ALL_PAN = 0xBA,
    AKAO_SLIDE_ALL_PAN = 0xBB,
    AKAO_SET_ALL_PITCH = 0xBC,
    AKAO_SLIDE_ALL_PITCH = 0xBD,
    AKAO_VOLUME_SET = 0xC0,
    AKAO_VOL_SLIDE_FROM_CURR = 0xC1,
    AKAO_VOL_SLIDE_BETWEEN_TARGETS = 0xC2,
    AKAO_SET_CD_VOL = 0xC8,
    AKAO_CD_VOL_SLIDE_FROM_CURR = 0xC9,
    AKAO_CD_VOL_SLIDE_BETWEEN_TARGETS = 0xCA,
    AKAO_OP_LEGATO_ON = 0xCC,
    AKAO_OP_LEGATO_OFF = 0xCD,
    AKAO_SET_TEMPO = 0xD0,
    AKAO_OP_FULL_LENGTH_ON = 0xD0,
    AKAO_TEMPO_SLIDE_FROM_CURR = 0xD1,
    AKAO_OP_FULL_LENGTH_OFF = 0xD1,
    AKAO_TEMPO_SLIDE_BETWEEN_TARGETS = 0xD2,
    AKAO_SET_PITCH = 0xD4,
    AKAO_OP_SIDE_CHAIN_PLAYBACK_ON = 0xD4,
    AKAO_PITCH_SLIDE_FROM_CURR = 0xD5,
    AKAO_OP_SIDE_CHAIN_PLAYBACK_OFF = 0xD5,
    AKAO_PITCH_SLIDE_BETWEEN_TARGETS = 0xD6,
    AKAO_OP_SIDE_CHAIN_PITCH_VOL_ON = 0xD6,
    AKAO_OP_SIDE_CHAIN_PITCH_VOL_OFF = 0xD7,
    AKAO_SET_TEMPO_AND_PITCH = 0xD8,
    AKAO_TEMPO_AND_PITCH_SLIDE_FROM_CURR = 0xD9,
    AKAO_TEMPO_AND_PITCH_SLIDE_BETWEEN_TARGETS = 0xDA,
    AKAO_SET_REVERB_PAN = 0xE0,
    AKAO_OP_VOICE_BUS_ROUTING_ON = 0xE0,
    AKAO_STOP_STREAM = 0xE2,
    AKAO_SET_REVERB_MUL = 0xE4,
    AKAO_STOP_MUSIC = 0xF0,
    AKAO_STOP_ALL_SOUNDS = 0xF1,
    AKAO_CLEAR_SAVED_MUSIC0 = 0xF2,
    AKAO_CLEAR_SAVED_MUSIC1 = 0xF3,
    AKAO_SAVE_STATE = 0xF4,
    AKAO_RESTORE_STATE = 0xF5,
    AKAO_STREAM_REVERB_MASK_CLEAR = 0xF8,
    AKAO_STREAM_REVERB_MASK_RESTORE = 0xF9,
} AkaoCommands;

// 16.16 fixed point volume
typedef union {
    s32 val;
    struct {
        s16 lo;
        s16 hi;
    } i;
} AkaoCdVol; // size:0x04

extern AkaoCdVol g_AkaoCdVol;
extern volatile s32 g_SoundStatusFlags;

typedef struct {
    /* 0x00 */ s32 opcode;
    /* 0x04 */ s8 start;
    /* 0x05 */ s8 pad5[3];
    /* 0x08 */ s32 steps;
    /* 0x0C */ s8 target;
} AkaoTempoPitchSlide; // size:0x10

typedef struct {
    /* 0x00 */ u32 voiceId;
    /* 0x04 */ u32 mask;
    /* 0x08 */ u32 addr;
    /* 0x0C */ u32 loopAddr;
    /* 0x10 */ s32 aMode;
    /* 0x14 */ s32 sMode;
    /* 0x18 */ s32 rMode;
    /* 0x1C */ u16 pitch;
    /* 0x1E */ u16 ar;
    /* 0x20 */ u16 dr;
    /* 0x22 */ u16 sl;
    /* 0x24 */ s16 sr;
    /* 0x26 */ u16 rr;
    /* 0x28 */ u16 drumKey;
    /* 0x2A */ s16 volL;
    /* 0x2C */ s16 volR;
    /* 0x2E */ u16 pad2E;
} AkaoVoiceAttr; // size:0x30

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
} AkaoInstrument; // size:0x40

extern AkaoInstrument g_AkaoInstruments[];

typedef struct {
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
} AkaoChannel; // size:0x124

extern AkaoChannel g_AkaoChannels[];

// Each sound effect slot occupies a stereo voice pair (2 audio channels, 0x248 bytes).
typedef struct {
    AkaoChannel voices[2];
} AkaoSoundSlot; // size:0x248

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
} AkaoChannelConfig; // size:0x60

extern AkaoChannelConfig* g_AkaoChannelConfig;

typedef struct {
    /* 0x00 */ u32 opcode;
    /* 0x04 */ s32 param0;
    /* 0x08 */ s32 param1;
    /* 0x0C */ s32 param2;
    /* 0x10 */ s32 param3;
    /* 0x14 */ s32 param4;
    /* 0x18 */ s32 param5;
    /* 0x1C */ s32 param6;
    /* 0x20 */ s32 param7;
} AkaoQueuedCommand; // size:0x24

extern AkaoQueuedCommand g_AkaoCommand;

typedef struct {
    /* 0x00 */ u32 opcode;
    /* 0x04 */ s32 steps;
    /* 0x08 */ s32 targetVol;
} AkaoVolSlideFromCurr; // size:0x0C

typedef struct {
    /* 0x00 */ u32 opcode;
    /* 0x04 */ s32 steps;
    /* 0x08 */ s32 startVol;
    /* 0x0C */ s32 targetVol;
} AkaoVolSlideBetweenTargets; // size:0x10

typedef struct {
    /* 0x00 */ u32 opcode;
    /* 0x04 */ s32 steps;
    /* 0x08 */ u16 targetVol;
} AkaoCdVolSlideFromCurr; // size:0x0C

typedef struct {
    /* 0x00 */ u32 opcode;
    /* 0x04 */ s32 steps;
    /* 0x08 */ u16 startVol;
    /* 0x0A */ u16 padA;
    /* 0x0C */ u16 targetVol;
    /* 0x0E */ u16 padE;
} AkaoCdVolSlideBetweenTargets; // size:0x10

typedef struct {
    /* 0x00 */ s32 opcode;
    /* 0x04 */ s32 steps;
    /* 0x08 */ s8 target;
} AkaoSlideFromCurr; // size:0x0C

typedef struct {
    /* 0x00 */ u32 opcode;
    /* 0x04 */ u16 pan;
} AkaoSetReverbPan; // size:0x08

typedef struct {
    /* 0x00 */ u32 opcode;
    /* 0x04 */ u8 mul;
} AkaoSetReverbMul; // size:0x08

typedef struct {
    /* 0x00 */ s32 pitchSlide;
    /* 0x04 */ s32 volSlide;
    /* 0x08 */ s16 currentKey;
    /* 0x0A */ s16 padA;
} AkaoVoiceWork; // size:0x0C

typedef struct {
    /* 0x00 */ u8 pad00[8];
    /* 0x08 */ u32 flags;
    /* 0x0C */ u8 pad0C[0x28 - 0x0C];
    /* 0x28 */ s32 trackId;
} AkaoStreamContext; // size:0x2C

extern AkaoStreamContext g_AkaoStreamContext;

typedef struct {
    /* 0x00 */ u32 opcode;
    /* 0x04 */ s32 soundId1;
    /* 0x08 */ s32 soundId2;
} AkaoPlayTwoSoundsCommand; // size:0x0C

void AkaoPlaySoundPair(s32 soundId1, s32 soundId2);
void AkaoCmd_21_PlayTwoSounds(AkaoPlayTwoSoundsCommand* cmd);
void AkaoUpdateCdVolume(void);

void AkaoStreamFeedBlock(s32 bufStart, s32 bufMid, s32 blockSize, void (*nextIrq)(void));
void AkaoStreamPumpBuffer(s32 bufStart, s32 bufMid, s32 blockSize, void (*nextIrq)(void));
void AkaoStreamIrqAlt0(void);
void AkaoStreamIrqAlt1(void);
void AkaoStreamIrqChain0(void);
void AkaoStreamIrqChain1(void);
void AkaoStreamIrqHalf0(void);
void AkaoStreamIrqHalf1(void);

// SPU Hardware Registers & Macros
#define SPU_VOICE_REG(voice, offset) (*(u16*)(0x1F801C00 + (offset) + ((voice) * 0x10)))
#define SPU_VOICE_REG8(voice, offset) (*(u8*)(0x1F801C00 + (offset) + ((voice) * 0x10)))

// Voice channel register offsets (from 0x1F801C00 base)
#define SPU_VOICE_VOL_L_OFFSET 0x00
#define SPU_VOICE_VOL_R_OFFSET 0x02
#define SPU_VOICE_PITCH_OFFSET 0x04
#define SPU_VOICE_START_ADDR_OFFSET 0x06
#define SPU_VOICE_ADSR_AMODE_OFFSET 0x08
#define SPU_VOICE_ADSR_SMODE_OFFSET 0x0A
#define SPU_VOICE_LOOP_ADDR_OFFSET 0x0E

#define SPU_REG(addr) (*(u16*)(addr))

// SPU Control Register Addresses
#define SPU_VOICE_KEY_ON_LO 0x1F801D88
#define SPU_VOICE_KEY_ON_HI 0x1F801D8A
#define SPU_VOICE_KEY_OFF_LO 0x1F801D8C
#define SPU_VOICE_KEY_OFF_HI 0x1F801D8E
#define SPU_VOICE_CHN_FM_LO 0x1F801D90
#define SPU_VOICE_CHN_FM_HI 0x1F801D92
#define SPU_VOICE_CHN_NOISE_LO 0x1F801D94
#define SPU_VOICE_CHN_NOISE_HI 0x1F801D96
#define SPU_VOICE_CHN_REVERB_LO 0x1F801D98
#define SPU_VOICE_CHN_REVERB_HI 0x1F801D9A
#define SPU_CD_VOL_L 0x1F801DB0
#define SPU_CD_VOL_R 0x1F801DB2

#endif
