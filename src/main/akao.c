//! PSYQ=4.0
#include "common.h"
#include "akao.h"

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

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_8002EA90);

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

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", IsValidAkaoMagic);

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

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80033738);

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

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80035D28);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_A8_SetVol);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_A9_SetVolSlide);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80035E68);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80035EF8);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80035F0C);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_F4_OverlayVoiceOn);

void AkaoOp_F5_OverlayVoiceOff(void) {}

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_F6_OverlayVolBalance);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_F7_OverlayVolBalanceSlide);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_AA_SetPan);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_AB_SetPanSlide);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_A5_SetOctave);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_A6_IncOctave);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_A7_DecOctave);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_A1_LoadInstrument);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_F2_LoadInstrument);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80036214);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_B3_ResetAdsr);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_C0_TransposeAbsolute);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_C1_TransposeRelative);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_A4_PitchBendSlide);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_DA_PortamentoOn);

void AkaoOp_DB_PortamentoOff(AkaoChannel* track)
{
    track->portamentoSteps = 0;
}

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_D8_FineTuningAbsolute);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_D9_FineTuningRelative);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_B4_Vibrato);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_B5_VibratoDepth);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_DD_VibratoDepthSlide);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_B6_VibratoOff);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_B8_Tremolo);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_B9_TremoloDepth);

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

void AkaoOp_CC_LegatoOn(AkaoChannel* track)
{
    track->sfxMask = AKAO_SFX_LEGATO;
}

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

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_ED_DrumModeOff);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_FD_TimeSignature);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_FE_MeasureNumber);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_B0_SetVoiceDrSl);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_CE_NoiseSwitch);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_CF_NoiseSwitch);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_D2_FrequencyModulationSwitch);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_D3_FrequencyModulationSwitch);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_CB_SfxReset);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_D4_SideChainPlaybackOn);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_D5_SideChainPlaybackOff);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_D6_SideChainPitchVolOn);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_D7_SideChainPitchVolOff);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_F3_MuteMusic);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_8003744C);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80037490);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", func_80037544);

INCLUDE_ASM("asm/jp/nonmatchings/main/akao", AkaoOp_Null);

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
