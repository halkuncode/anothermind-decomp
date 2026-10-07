// For akao.c, stucts go here
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
    /* 0x00 */ u32 opcode;
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

typedef struct {
    /* 0x00 */ u8 pad00[8];
    /* 0x08 */ u32 flags;
    /* 0x0C */ u8 pad0C[0x28 - 0x0C];
    /* 0x28 */ s32 trackId;
} AkaoStreamContext;

extern AkaoStreamContext g_AkaoStreamContext;
