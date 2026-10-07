//! CC1=2.8.0
#include "common.h"
#include "akao_private.h"
#include "akao.h"
#include "libspu.h"

extern s32 g_AudioInitialized;
extern AkaoChannelConfig* g_AkaoChannelConfig;
extern s16 g_AkaoPitchMulMusicSlideSteps;
extern s32 g_AkaoPitchMulMusic;
extern s32 g_AkaoCdVol;

s32 InitSoundDriver(void) {
    SetupSpuAndAudioEvents();
    return 0;
}

s32 ShutdownSoundSystem(void) {
    StopAndCloseSoundEvents();
    return 0;
}

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

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoSendCmd_90_SetMuteMusicMask);

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

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoSendCmd_D4_SetPitch);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", ReleaseMusicLayerTrack);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoSendCmd_D6_PitchSlideBetweenTargets);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", ResetAndStopMusicLayer);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", OverrideMusicLayerTrack);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", OverrideMusicLayerTrackWithPan);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoSendCmd_F0_StopMusic);

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



void func_8002EFF0(void)
{
    SetSpuTransferCallback(0);
    g_AudioInitialized = 0;
}

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

void AkaoSpuKeyOn(u32 mask) {
    SPU_REG(SPU_VOICE_KEY_ON_LO) = mask;
    SPU_REG(SPU_VOICE_KEY_ON_HI) = mask >> 16;
}

void AkaoSpuKeyOff(u32 mask) {
    SPU_REG(SPU_VOICE_KEY_OFF_LO) = mask;
    SPU_REG(SPU_VOICE_KEY_OFF_HI) = mask >> 16;
}

void AkaoSpuReverbOn(u32 mask) {
    SPU_REG(SPU_VOICE_CHN_REVERB_LO) = mask;
    SPU_REG(SPU_VOICE_CHN_REVERB_HI) = mask >> 16;
}

void AkaoSpuNoiseOn(u32 mask) {
    SPU_REG(SPU_VOICE_CHN_NOISE_LO) = mask;
    SPU_REG(SPU_VOICE_CHN_NOISE_HI) = mask >> 16;
}

void AkaoSpuPitchLfoOn(u32 mask) {
    SPU_REG(SPU_VOICE_CHN_FM_LO) = mask;
    SPU_REG(SPU_VOICE_CHN_FM_HI) = mask >> 16;
}

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoSpuSetVoiceVolume);

void AkaoSpuSetVoicePitch(s32 voice, s16 pitch) { SPU_VOICE_REG(voice, SPU_VOICE_PITCH_OFFSET) = pitch; }

void AkaoSpuSetVoiceStartAddress(s32 voice, u32 addr) { SPU_VOICE_REG(voice, SPU_VOICE_START_ADDR_OFFSET) = addr >> 3; }

void AkaoSpuSetVoiceLoopAddress(s32 voice, u32 loopAddr) {
    SPU_VOICE_REG(voice, SPU_VOICE_LOOP_ADDR_OFFSET) = loopAddr >> 3;
}

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

void AkaoUpdateNoiseVoices(void) { g_AkaoControl.updateFlags |= AKAO_UPDATE_VOICE_MODES; }

void AkaoUpdateReverbVoices(void) { g_AkaoControl.updateFlags |= AKAO_UPDATE_VOICE_MODES; }

void AkaoUpdatePitchLfoVoices(void) { g_AkaoControl.updateFlags |= AKAO_UPDATE_VOICE_MODES; }

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

extern s16 g_AkaoTempoMulMusicSlideSteps;
extern s32 g_AkaoTempoMulMusic;

void AkaoCmd_D0_SetTempo(AkaoTempoPitchSlide* cmd) {
    s32 start = cmd->start;
    g_AkaoTempoMulMusicSlideSteps = 0;
    g_AkaoTempoMulMusic = start << 16;
}

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoCmd_D1_TempoSlideFromCurr);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoCmd_D2_TempoSlideBetweenTargets);

void AkaoCmd_D4_SetPitch(AkaoTempoPitchSlide* cmd) {
    s32 pitch = cmd->start;
    g_AkaoPitchMulMusicSlideSteps = 0;
    g_AkaoPitchMulMusic = pitch << 16;
}

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoCmd_D5_PitchSlideFromCurr);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoCmd_D6_PitchSlideBetweenTargets);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoCmd_F0_StopMusic);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoCmd_11_StopMusicLane);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoCmd_F1_StopAllSounds);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoCmd_80_SetStereoMode);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoCmd_81_SetMonoMode);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoCmd_90_SetMuteMusicMask);

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

extern s32 g_AkaoCdVol;

void AkaoUpdateCdVolume(void) {
    SPU_REG(SPU_CD_VOL_L) = (s16)(g_AkaoCdVol >> 16);
    SPU_REG(SPU_CD_VOL_R) = (s16)(g_AkaoCdVol >> 16);
}

void func_80034134(s32* src, s32* dst, u32 count) {
    count >>= 2;
    do {
        *dst++ = *src++;
    } while (--count != 0);
}

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
    u16 val = *seq++;
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
    u16 val = *seq;
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

void AkaoOp_BD_PanLfoDepth(AkaoChannel* track) {
    u8* seq = track->akaoSequencePointer;
    u16 val = *seq++;
    track->akaoSequencePointer = seq;

    track->panLfoDepth = val << 7;
}

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

void AkaoOp_ED_DrumModeOff(AkaoChannel* track) {
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

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoStopStream);

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

void AkaoCmd_E2_StopStream(void) { AkaoStopStream(); }

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
