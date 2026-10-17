//! G=0
#include "common.h"
#include "akao.h"
#include "libspu.h"

extern s16 g_AkaoPitchMulMusicSlideSteps;
extern s16 g_AkaoTempoMulMusicSlideSteps;
extern s32 g_AkaoAudioSlot1Id;
extern s32 g_SeLoopBufferMain;
extern volatile s32 g_AudioInitialized; // voltile need for critical loop per style.md
extern s32 g_SeLoopChannelState;
extern s32 g_SeLoopMixBuffer;
extern s32 g_AkaoPitchMulMusic;
extern s32 g_AkaoTempoMulMusic;
extern s16 g_AkaoCdVolSlideSteps;

s32 InitSoundDriver(void) {
    SetupSpuAndAudioEvents();
    return 0;
}

s32 ShutdownSoundSystem(void) {
    StopAndCloseSoundEvents();
    return 0;
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", EnsureSeLoopBlockInitialized);

void AkaoCmd_10_PlayMusic(s32 trackId) {
    g_AkaoCommand.opcode = AKAO_PLAY_MUSIC;
    g_AkaoCommand.param0 = trackId;
    AkaoExec();
}

void ResetSoundSystem(void) {
    g_AkaoCommand.opcode = AKAO_STOP_MUSIC;
    AkaoExec();
}

void AkaoCmd_40_SaveChannelState(void) {
    g_AkaoCommand.opcode = AKAO_SAVE_CHANNEL_STATE;
    AkaoExec();
}

void AkaoCmd_12_PlayMusicFade(s32 trackId, s32 fadeDuration) {
    g_AkaoCommand.opcode = AKAO_PLAY_MUSIC_FADE;
    g_AkaoCommand.param0 = trackId;
    g_AkaoCommand.param1 = fadeDuration;
    AkaoExec();
}

s32 InitAkao(s32 wait) {
    if (wait) {
        while (g_SoundStatusFlags & 1)
            ;
        return 0;
    }
    return g_SoundStatusFlags & 1;
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoPlaySoundEffectDefault);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoCmd_24_PlayConsecutiveSound);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", StopSoundEffect);

void AkaoCmd_30_PlayMenuSound(s32 soundId) {
    g_AkaoCommand.opcode = AKAO_PLAY_MENU_SOUND;
    g_AkaoCommand.param0 = soundId & 0x3FF;
    AkaoExec();
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoInitSpuVoices);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", IsResourceLoaded);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoSetStereoMonoMode);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoSendCmd_90_SetMuteMusicMask);

void AkaoCmd_92_SetCondition(s32 condition) {
    g_AkaoCommand.opcode = AKAO_SET_CONDITION;
    g_AkaoCommand.param0 = condition;
    AkaoExec();
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", ApplySoundProfile);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoFlushPendingUpdates);

void AkaoCmd_A8_SetPanSlot2(s32 pan) {
    g_AkaoCommand.opcode = AKAO_SET_PAN_SLOT2;
    g_AkaoCommand.param0 = pan & 0x7F;
    AkaoExec();
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoCmd_A9_SetPanSlot1);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoCmd_A0_SetVolBalanceSlot2);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoCmd_A1_SetVolBalanceSlot1);

void AkaoCmd_AA_SetPanSlot0(s32 pan) {
    g_AkaoCommand.opcode = AKAO_SET_PAN_SLOT0;
    g_AkaoCommand.param0 = pan & 0xFF;
    AkaoExec();
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoCmd_AB_SetPanSlot3);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", PlaySystemSound);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoCmd_A3_SetVolBalanceSlot3);

void AkaoCmd_AC_SlidePanSlot2(s32 pan) {
    g_AkaoCommand.opcode = AKAO_SLIDE_PAN_SLOT2;
    g_AkaoCommand.param0 = pan & 0xFF;
    AkaoExec();
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoCmd_AD_SlidePanSlot1);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoPlaySoundEffectWithPan);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoCmd_A5_SlideVolBalanceSlot1);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoPlayMusicSequence);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", SendMusicStopCommand);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", PlayMusicTrackWithPanVol);

void AkaoCmd_C8_SetCdVol(s32 volume) {
    g_AkaoCommand.opcode = AKAO_SET_CD_VOL;
    g_AkaoCommand.param0 = volume;
    AkaoExec();
}

void AkaoCmd_C9_CdVolSlideFromCurr(s32 volume, s32 duration) {
    g_AkaoCommand.opcode = AKAO_CD_VOL_SLIDE_FROM_CURR;
    g_AkaoCommand.param0 = volume;
    g_AkaoCommand.param1 = duration;
    AkaoExec();
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", SendSoundConfigCommand);

void SendMusicLayerResetCommand(s32 layer) {
    g_AkaoCommand.opcode = AKAO_SET_TEMPO;
    g_AkaoCommand.param0 = layer & 0xFF;
    AkaoExec();
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", SetMusicLayerTrack);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", SetMusicLayerTrackPan);

void AkaoSendCmd_D4_SetPitch(s32 pitch) {
    g_AkaoCommand.opcode = AKAO_SET_PITCH;
    g_AkaoCommand.param0 = pitch & 0xFF;
    AkaoExec();
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", ReleaseMusicLayerTrack);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoSendCmd_D6_PitchSlideBetweenTargets);

void ResetAndStopMusicLayer(s32 layer) {
    g_AkaoCommand.opcode = AKAO_SET_TEMPO_AND_PITCH;
    g_AkaoCommand.param0 = layer & 0xFF;
    AkaoExec();
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", OverrideMusicLayerTrack);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", OverrideMusicLayerTrackWithPan);

void AkaoSendCmd_F0_StopMusic(void) {
    g_AkaoChannelConfig->musicId = 0;
    g_AkaoCommand.opcode = AKAO_STOP_MUSIC;
    AkaoExec();
}

void CutSoundEffect(void) {
    g_AkaoCommand.opcode = AKAO_STOP_ALL_SOUNDS;
    AkaoExec();
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", DecompressWaveMusic);

s32 IsAudioInitialized(void) { return g_AudioInitialized; }

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", InstallAkaoProgramFromBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoSpuDmaCallback);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoPlayMusicSequenceWithFade);

void StopAllMusic(void) {
    g_AkaoCommand.opcode = AKAO_STOP_STREAM;
    AkaoExec();
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", SetActiveMusicBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", CrossfadeToBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", SetSecondaryMusicBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoLoadSoundBank);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoSendStreamCommand);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoExecCommandIfValid);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoSetupStreamIRQ);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoProcessStreamBuffer);

s32 AkaoGetPlayingStreamTrack(void) {
    s32 ret = -1;
    if (!(g_AkaoStreamContext.flags & 0x02000000)) {
        ret = g_AkaoStreamContext.trackId;
    }
    return ret;
}

s32 VerifyAkaoMagic(s32* akaoBuffer) { return *akaoBuffer - AKAO_MAGIC; }

void AkaoSpuTransferCallback(void) {
    SetSpuTransferCallback(0);
    g_AudioInitialized = 0;
}

void AkaoSetSpuTransferCallback(void) {
    g_AudioInitialized = 1;
    SetSpuTransferCallback(AkaoSpuTransferCallback);
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", SetupAudioEventHandler);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoSpuReadWithCallback);

void WaitForAudioShutdown(void) {
    if (g_AudioInitialized == 1) {
        do {
        } while (g_AudioInitialized == 1);
    }
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", ProcessAkaoBlockIfValid);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", InstallAkaoAudioProgram);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", ResetAudioState);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", SetupSpuAndAudioEvents);

void InitSeLoopWorkArea(s32 baseAddress) {
    g_SeLoopBufferMain = baseAddress;
    baseAddress += 0x400;
    g_SeLoopChannelState = baseAddress;
    baseAddress += 0x200;
    g_SeLoopMixBuffer = baseAddress;
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", StopAndCloseSoundEvents);

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

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoSpuSetVoiceVolume);

void AkaoSpuSetVoicePitch(s32 voice, s16 pitch) { SPU_VOICE_REG(voice, SPU_VOICE_PITCH_OFFSET) = pitch; }

void AkaoSpuSetVoiceStartAddress(s32 voice, u32 addr) { SPU_VOICE_REG(voice, SPU_VOICE_START_ADDR_OFFSET) = addr >> 3; }

void AkaoSpuSetVoiceLoopAddress(s32 voice, u32 loopAddr) {
    SPU_VOICE_REG(voice, SPU_VOICE_LOOP_ADDR_OFFSET) = loopAddr >> 3;
}

void AkaoSpuSetVoiceAttackRate(s32 voice, s32 rate, u32 mode) {
    SPU_VOICE_REG(voice, SPU_VOICE_ADSR_AMODE_OFFSET) =
        SPU_VOICE_REG8(voice, SPU_VOICE_ADSR_AMODE_OFFSET) | (((mode >> 2) << 15) | (rate << 8));
}

void AkaoSpuSetVoiceDecayRate(s32 voice, s32 decay) {
    SPU_VOICE_REG(voice, SPU_VOICE_ADSR_AMODE_OFFSET) =
        (SPU_VOICE_REG(voice, SPU_VOICE_ADSR_AMODE_OFFSET) & 0xFF0F) | (decay << 4);
}

void AkaoSpuSetVoiceSustainLevel(s32 voice, s32 susLevel) {
    SPU_VOICE_REG(voice, SPU_VOICE_ADSR_AMODE_OFFSET) =
        (SPU_VOICE_REG(voice, SPU_VOICE_ADSR_AMODE_OFFSET) & 0xFFF0) | susLevel;
}

void AkaoSpuSetVoiceSustainRate(s32 voice, s32 rate, u32 mode) {
    SPU_VOICE_REG(voice, SPU_VOICE_ADSR_SMODE_OFFSET) =
        (SPU_VOICE_REG(voice, SPU_VOICE_ADSR_SMODE_OFFSET) & 0x3F) | (((mode >> 1) << 14) | (rate << 6));
}

void AkaoSpuSetVoiceReleaseRate(s32 voice, s32 rate, u32 mode) {
    SPU_VOICE_REG(voice, SPU_VOICE_ADSR_SMODE_OFFSET) =
        (SPU_VOICE_REG(voice, SPU_VOICE_ADSR_SMODE_OFFSET) & 0xFFC0) | (((mode >> 2) << 5) | rate);
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoUpdateChannelParamsToSpu);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoUpdateChannelAndOvlParamsToSpu);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoMusicUpdateSlideAndDelay);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoMusicUpdatePitchAndVol);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoSoundUpdatePitchAndVol);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoAllocateVoice);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoAllocateAndAssignVoice);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoReleaseVoice);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoPollVoiceEnvelopes);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoUpdateKeysOn);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoCollectChannelsVoicesMask);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoUpdateKeysOff);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoUpdateNoiseVoicesMask);

void AkaoUpdateNoiseVoices(void) { g_AkaoControl.updateFlags |= AKAO_UPDATE_VOICE_MODES; }

void AkaoUpdateReverbVoices(void) { g_AkaoControl.updateFlags |= AKAO_UPDATE_VOICE_MODES; }

void AkaoUpdatePitchLfoVoices(void) { g_AkaoControl.updateFlags |= AKAO_UPDATE_VOICE_MODES; }

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoInitChannelState);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoResetChannelVolPan);

void AdjustAudioEventAddresses(AkaoInstrument* inst, u32 offset, s32 count) {
    do {
        inst->addr += offset;
        inst->loopAddr += offset;
        inst++;
    } while (--count);
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoStartSequencePlayback);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoSetChannelMasks);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoPlaySoundPair);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoSetupChannelSequence);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoStopChannelPlayback);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoTriggerSoundEffectPair);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoSetSeLoopBufferPointers);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoClearChannelAllocation);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoStopAllActiveChannels);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoInitAudioSlot1);

s32 AkaoGetAudioSlot1Id(s32 id) {
    s32 ret = 0;
    if (!id) {
        return ret;
    }
    if (id == g_AkaoAudioSlot1Id) {
        ret = 1;
    }
    return ret;
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoPlayMusicOnSlot);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoFadeOutAudioSlot);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoCheckAndPlayPendingMusic);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoTriggerSfxTrack);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoTriggerSeLoopSlot0);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoTriggerSeLoopSlot1);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoTriggerSfxPriority);

void AkaoCmd_21_PlayTwoSounds(AkaoPlayTwoSoundsCommand* cmd) { AkaoPlaySoundPair(cmd->soundId1, cmd->soundId2); }

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoStopSfxChannel0);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoStopSfxChannel1);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoStopSfxChannel2);

void AkaoSetCdVolumeInstant(AkaoQueuedCommand* cmd) {
    g_AkaoCdVolSlideSteps = 0;
    g_AkaoCdVol.val = (u16)cmd->param0 << 16;
    AkaoUpdateCdVolume();
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoInitCdVolumeSlide);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoStepCdVolumeSlide);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoInitChannelVolSlide);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoStepChannelVolSlide);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoResetChannelVolSlide);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoApplyChannelVolSlide);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoInitChannelPanSlide);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoStepChannelPanSlide);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoResetChannelPanSlide);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoApplyChannelPanSlide);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoInitChannelPitchSlide);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoStepChannelPitchSlide);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoResetChannelPitchSlide);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoApplyChannelPitchSlide);

void AkaoCmd_D0_SetTempo(AkaoTempoPitchSlide* cmd) {
    s32 start = cmd->start;
    g_AkaoTempoMulMusicSlideSteps = 0;
    g_AkaoTempoMulMusic = start << 16;
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoCmd_D1_TempoSlideFromCurr);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoCmd_D2_TempoSlideBetweenTargets);

void AkaoCmd_D4_SetPitch(AkaoTempoPitchSlide* cmd) {
    s32 pitch = cmd->start;
    g_AkaoPitchMulMusicSlideSteps = 0;
    g_AkaoPitchMulMusic = pitch << 16;
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoCmd_D5_PitchSlideFromCurr);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoCmd_D6_PitchSlideBetweenTargets);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoCmd_F0_StopMusic);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoCmd_11_StopMusicLane);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoCmd_F1_StopAllSounds);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoCmd_80_SetStereoMode);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoCmd_81_SetMonoMode);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoCmd_90_SetMuteMusicMask);

void AkaoSetChannelCondition(AkaoQueuedCommand* cmd) { g_AkaoChannelConfig->condition = cmd->param0; }

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoFlushChannelVoiceToSpu);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoFlushGlobalVoiceModes);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoFlushAllChannelsToSpu);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoFlushActiveChannelModes);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoSetStreamVoiceLeftPitch);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoSetStreamVoiceRightPitch);

void AkaoOp_NOP_Channel(void) {}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoExecuteCommandsQueue);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoGetCommandQueue);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", SetReverbModeIfDifferent);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", ClearMusicStateIfMatches);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoExec);

void AkaoUpdateCdVolume(void) {
    SPU_REG(SPU_CD_VOL_L) = (s16)(g_AkaoCdVol.val >> 16);
    SPU_REG(SPU_CD_VOL_R) = (s16)(g_AkaoCdVol.val >> 16);
}

void AkaoCopyVoiceParamsNOP(s32* src, s32* dst, u32 count) {
    count >>= 2;
    do {
        *dst++ = *src++;
    } while (--count);
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoUpdateGlobalSlides);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoMainUpdate);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoMain);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoGetNextNote);

s32 AkaoAdjustInstrumentIndex(u32 flags, s32 instrument) {
    if ((flags & 2) && ((u32)(instrument - 0x80) < 0x80)) {
        return instrument + 0x40;
    }
    return instrument;
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoFindInstrumentKeySplitLow);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoFindInstrumentKeySplitHigh);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoResolveInstrumentSplit);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoCalcNotePitch);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoTriggerNoteOn);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoExecuteSequence);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoGetInstrumentSampleRate);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoInitInstrumentTuning);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoCheckVoiceBusy);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_A0_FinishChannel);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_E8_Tempo);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_E9_TempoSlide);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_EA_ReverbDepth);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_EB_ReverbDepthSlide);

void AkaoOp_EE_Jump(AkaoChannel* track) {
    u8* seq = track->akaoSequencePointer;
    track->akaoSequencePointer = seq + (s16)(seq[0] | (seq[1] << 8));
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_EF_JumpConditional);

void AkaoOp_A3_MasterVol(AkaoChannel* track) {
    u8* seq = track->akaoSequencePointer;
    u8 val = *seq++;
    track->akaoSequencePointer = seq;

    track->voiceAttr.mask |= SPU_VOICE_VOLL | SPU_VOICE_VOLR;
    track->masterVol = val << 8;
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_FA_VolSlideFromCurr);

void AkaoOp_A8_SetVol(AkaoChannel* track) {
    u8* seq = track->akaoSequencePointer;
    s32 val = *(s8*)seq++;
    track->akaoSequencePointer = seq;

    track->volSlideSteps = 0;
    track->voiceAttr.mask |= SPU_VOICE_VOLL | SPU_VOICE_VOLR;
    track->pad88 = 0;
    track->volumeLevel = val << 23;
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_A9_SetVolSlide);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_FE19_PanSlideFromCurr);

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

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_F7_OverlayVolBalanceSlide);

void AkaoOp_AA_SetPan(AkaoChannel* track) {
    u32 pan = *track->akaoSequencePointer++;
    track->volPanSlideSteps = 0;
    track->voiceAttr.mask |= AKAO_UPDATE_SPU_VOICE;
    track->volPan = ((pan + 0x40) & 0xFF) << 8;
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_AB_SetPanSlide);

void AkaoOp_A5_SetOctave(AkaoChannel* track) {
    u8* seq = track->akaoSequencePointer;
    u16 val = *seq++;
    track->akaoSequencePointer = seq;
    track->octave = val;
}

void AkaoOp_A6_IncOctave(AkaoChannel* track) { track->octave = (track->octave + 1) & 0xF; }

void AkaoOp_A7_DecOctave(AkaoChannel* track) { track->octave = (track->octave - 1) & 0xF; }

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_A1_LoadInstrument);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_F2_LoadInstrument);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_FC_CustomInstrumentMap);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_B3_ResetAdsr);

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

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_A4_PitchBendSlide);

void AkaoOp_DA_PortamentoOn(AkaoChannel* track) {
    u8* seq = track->akaoSequencePointer;
    u16 val = *seq;
    track->akaoSequencePointer = seq + 1;

    track->portamentoSteps = val;
    if (!val) {
        track->portamentoSteps = 0x100;
    }
    track->transposeStored = 0;
    track->keyStored = 0;
    track->sfxMask = 1;
}

void AkaoOp_DB_PortamentoOff(AkaoChannel* track) { track->portamentoSteps = 0; }

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_D8_FineTuningAbsolute);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_D9_FineTuningRelative);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_B4_Vibrato);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_B5_VibratoDepth);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_DD_VibratoDepthSlide);

void AkaoOp_B6_VibratoOff(AkaoChannel* track) {
    track->vibratoPitch = 0;
    track->updateFlags &= ~AKAO_UPDATE_VIBRATO;
    track->voiceAttr.mask |= SPU_VOICE_PITCH;
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_B8_Tremolo);

void AkaoOp_B9_TremoloDepth(AkaoChannel* track) {
    u8* seq = track->akaoSequencePointer;
    u8 val = *seq++;
    track->akaoSequencePointer = seq;

    track->tremoloDepth = (val & 0x7F) << 8;
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_DE_TremoloDepthSlideFromCurr);

void AkaoOp_BA_TremoloOff(AkaoChannel* track) {
    track->tremoloVol = 0;
    track->updateFlags &= ~AKAO_UPDATE_TREMOLO;
    track->voiceAttr.mask |= AKAO_UPDATE_SPU_VOICE;
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_BC_SetPanLfo);

void AkaoOp_BD_PanLfoDepth(AkaoChannel* track) {
    u8* seq = track->akaoSequencePointer;
    u16 val = *seq++;
    track->akaoSequencePointer = seq;

    track->panLfoDepth = val << 7;
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_DF_PanLfoDepthSlideFromCurr);

void AkaoOp_BE_PanLfoOff(AkaoChannel* track) {
    track->panLfoVol = 0;
    track->updateFlags &= ~AKAO_UPDATE_PAN_LFO;
    track->voiceAttr.mask |= AKAO_UPDATE_SPU_VOICE;
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_C4_NoiseOn);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_C5_NoiseOff);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_C6_PitchLfoOn);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_C7_PitchLfoOff);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_C2_ReverbOn);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_C3_ReverbOff);

void AkaoOp_CC_LegatoOn(AkaoChannel* track) { track->sfxMask = AKAO_SFX_LEGATO; }

void AkaoOp_CD_LegatoOff(void) {}

void AkaoOp_D0_FullLengthOn(void) {}

void AkaoOp_D1_FullLengthOff(void) {}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_AC_NoiseClockFreq);

void AkaoOp_AD_SetAr(AkaoChannel* track) {
    u8* seq = track->akaoSequencePointer;
    u16 val = *seq++;

    track->akaoSequencePointer = seq;
    track->voiceAttr.mask |= SPU_VOICE_ADSR_AR | SPU_VOICE_ADSR_AMODE;
    track->updateFlags |= AKAO_UPDATE_ADSR_AR;
    track->voiceAttr.ar = val;
}

void AkaoOp_AE_SetDr(AkaoChannel* track) {
    u8* seq = track->akaoSequencePointer;
    u32 mask = track->voiceAttr.mask;
    u16 val = *seq++;

    track->akaoSequencePointer = seq;
    track->voiceAttr.mask = mask | SPU_VOICE_ADSR_DR;
    track->voiceAttr.dr = val;
}

void AkaoOp_AF_SetSl(AkaoChannel* track) {
    u8* seq = track->akaoSequencePointer;
    u16 val = *seq++;

    track->akaoSequencePointer = seq;
    track->voiceAttr.mask |= SPU_VOICE_ADSR_SL;
    track->voiceAttr.sl = val;
}

void AkaoOp_B1_SetSr(AkaoChannel* track) {
    u8* seq = track->akaoSequencePointer;
    u16 val = *seq++;

    track->akaoSequencePointer = seq;
    track->voiceAttr.mask |= SPU_VOICE_ADSR_SR | SPU_VOICE_ADSR_SMODE;
    track->updateFlags |= AKAO_UPDATE_ADSR_SR;
    track->voiceAttr.sr = val;
}

void AkaoOp_B2_SetRr(AkaoChannel* track) {
    u8* seq = track->akaoSequencePointer;
    u16 val = *seq++;

    track->akaoSequencePointer = seq;
    track->voiceAttr.mask |= SPU_VOICE_ADSR_RR | SPU_VOICE_ADSR_RMODE;
    track->updateFlags |= AKAO_UPDATE_ADSR_RR;
    track->voiceAttr.rr = val;
}

void AkaoOp_B7_AttackMode(AkaoChannel* track) {
    u8* seq = track->akaoSequencePointer;
    u32 mask = track->voiceAttr.mask;
    u16 val = *seq++;

    track->akaoSequencePointer = seq;
    track->voiceAttr.mask = mask | SPU_VOICE_ADSR_AMODE;
    track->voiceAttr.aMode = val;
}

void AkaoOp_BB_SustainMode(AkaoChannel* track) {
    u8* seq = track->akaoSequencePointer;
    u32 mask = track->voiceAttr.mask;
    u16 val = *seq++;

    track->akaoSequencePointer = seq;
    track->voiceAttr.mask = mask | SPU_VOICE_ADSR_SMODE;
    track->voiceAttr.sMode = val;
}

void AkaoOp_BF_ReleaseMode(AkaoChannel* track) {
    u8* seq = track->akaoSequencePointer;
    u32 mask = track->voiceAttr.mask;
    u16 val = *seq++;

    track->akaoSequencePointer = seq;
    track->voiceAttr.mask = mask | SPU_VOICE_ADSR_RMODE;
    track->voiceAttr.rMode = val;
}

void AkaoOp_F8_AltVoiceOn(AkaoChannel* track) {
    u8* seq;
    u32 mask;
    u16 releaseRate;

    track->updateFlags |= AKAO_UPDATE_ALTERNATIVE;
    seq = track->akaoSequencePointer;
    releaseRate = *seq++;
    mask = track->voiceAttr.mask;
    track->akaoSequencePointer = seq;
    track->voiceAttr.mask = mask | SPU_VOICE_ADSR_RR | SPU_VOICE_ADSR_RMODE;
    track->voiceAttr.rr = releaseRate;
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_F9_AltVoiceOff);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_C8_LoopPoint);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_C9_LoopReturnTimes);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_F0_LoopJumpTimes);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_F1_LoopBreakTimes);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_CA_LoopReturn);

void AkaoOp_A2_NextNoteLength(AkaoChannel* channel) {
    u16 length = *channel->akaoSequencePointer++;
    channel->lengthFixed = 0;
    channel->length2 = length;
    channel->length1 = length;
    channel->lengthStored = length;
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_DC_FixNoteLength);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_EC_DrumModeOn);

void AkaoOp_ED_DrumModeOff(AkaoChannel* track) {
    track->voiceAttr.drumKey = 0;
    track->updateFlags &= ~AKAO_UPDATE_DRUM_MODE;
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_FD_TimeSignature);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_FE_MeasureNumber);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_B0_SetVoiceDrSl);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_CE_NoiseSwitch);

void AkaoOp_CF_NoiseSwitch(AkaoChannel* track) {
    u32 val = *track->akaoSequencePointer++;
    if (val) {
        track->noiseSwitchDelay = val + 1;
    } else {
        track->noiseSwitchDelay = 0x101;
    }
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_D2_FrequencyModulationSwitch);

void AkaoOp_D3_FrequencyModulationSwitch(AkaoChannel* track) {
    u32 val = *track->akaoSequencePointer++;
    if (val) {
        track->pitchLfoSwitchDelay = val + 1;
    } else {
        track->pitchLfoSwitchDelay = 0x101;
    }
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_CB_SfxReset);

void AkaoOp_D4_SideChainPlaybackOn(AkaoChannel* track) { track->updateFlags |= AKAO_UPDATE_SIDE_CHAIN_PITCH; }

void AkaoOp_D5_SideChainPlaybackOff(AkaoChannel* track) { track->updateFlags &= ~AKAO_UPDATE_SIDE_CHAIN_PITCH; }

void AkaoOp_D6_SideChainPitchVolOn(AkaoChannel* track) { track->updateFlags |= AKAO_UPDATE_SIDE_CHAIN_VOL; }

void AkaoOp_D7_SideChainPitchVolOff(AkaoChannel* track) { track->updateFlags &= ~AKAO_UPDATE_SIDE_CHAIN_VOL; }

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_F3_MuteMusic);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_FF_ReverbDelay);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoOp_FE18_ReverbDepthSlideFromCurr);

void AkaoOp_E0_VoiceBusRoutingOn(AkaoChannel* track) { track->updateFlags |= AKAO_UPDATE_VOICE_BUS; }

void AkaoOp_Null(void) { AkaoOp_A0_FinishChannel(); }

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoPollSoundCommandQueue);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoStopStream);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoAllocateStreamVoicePair);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoStreamDmaTransfer);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoSetupStreamPlayback);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoConfigureStreamVoices);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoInitStreamIrqAndCallbacks);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoStreamBuffer0Callback);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoStreamBuffer1Callback);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoStreamFeedBlock);

void AkaoStreamIrqHalf0(void) { AkaoStreamFeedBlock(0x1100, 0x1100, 0x800, AkaoStreamIrqHalf1); }

void AkaoStreamIrqHalf1(void) { AkaoStreamFeedBlock(0x2100, 0x2100, 0x800, AkaoStreamIrqHalf0); }

void AkaoStreamIrqAlt0(void) {
    AkaoStreamFeedBlock(AKAO_STREAM_BUF0_ADDR, AKAO_STREAM_BUF0_MID, AKAO_STREAM_BLOCK_SIZE, AkaoStreamIrqAlt1);
}

void AkaoStreamIrqAlt1(void) {
    AkaoStreamFeedBlock(AKAO_STREAM_BUF1_ADDR, AKAO_STREAM_BUF1_MID, AKAO_STREAM_BLOCK_SIZE, AkaoStreamIrqAlt0);
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoStartStreamWithMask);

void AkaoCmd_E2_StopStream(void) { AkaoStopStream(); }

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoSetStreamVolumeDirect);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoSetStreamVolumeTarget);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoStepStreamVolumeSlide);

void SetAkaoStopStreamCallback(void) {
    SpuSetIRQAddr(0x1038);
    SpuSetIRQCallback(AkaoStopStream);
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoStreamDmaCallback);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoStartStreamDma);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoStartStreamLoop);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoStartStreamTrack0);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoStartStreamTrack1);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoGetStreamStatus);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoStreamGetAvailableBytes);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoStreamInitRingBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoStreamTransferNextChunk);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoStreamWriteData);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoStreamSetupTransferIrq);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoStreamCallbackPrimary);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoStreamPumpBuffer);

void AkaoStreamIrqChain0(void) {
    AkaoStreamPumpBuffer(AKAO_STREAM_BUF0_ADDR, AKAO_STREAM_BUF0_MID, AKAO_STREAM_BLOCK_SIZE, AkaoStreamIrqChain1);
}

void AkaoStreamIrqChain1(void) {
    AkaoStreamPumpBuffer(AKAO_STREAM_BUF1_ADDR, AKAO_STREAM_BUF1_MID, AKAO_STREAM_BLOCK_SIZE, AkaoStreamIrqChain0);
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/akao", AkaoStreamHalt);
