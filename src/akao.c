#include "common.h"

INCLUDE_ASM("asm/jp/nonmatchings/akao", InitSoundDriver);

INCLUDE_ASM("asm/jp/nonmatchings/akao", ShutdownSoundSystem);

INCLUDE_ASM("asm/jp/nonmatchings/akao", EnsureSeLoopBlockInitialized);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoCmd_10_PlayMusic);

INCLUDE_ASM("asm/jp/nonmatchings/akao", ResetSoundSystem);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8002DF24);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoCmd_12_PlayMusicFade);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8002DF80);

INCLUDE_ASM("asm/jp/nonmatchings/akao", PlaySoundEffect_8002DFB4);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoCmd_24_PlayConsecutiveSound);

INCLUDE_ASM("asm/jp/nonmatchings/akao", StopSoundEffect);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoCmd_30_PlayMenuSound);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8002E104);

INCLUDE_ASM("asm/jp/nonmatchings/akao", IsResourceLoaded);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoSetStereoMonoMode);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoCmd_90_SetMuteMusicMask);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoCmd_92_SetCondition);

INCLUDE_ASM("asm/jp/nonmatchings/akao", ApplySoundProfile);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoFlushPendingUpdates);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoCmd_A8_SetPanSlot2);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoCmd_A9_SetPanSlot1);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoCmd_A0_SetVolBalanceSlot2);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoCmd_A1_SetVolBalanceSlot1);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoCmd_AA_SetPanSlot0);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoCmd_AB_SetPanSlot3);

INCLUDE_ASM("asm/jp/nonmatchings/akao", PlaySystemSound);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoCmd_A3_SetVolBalanceSlot3);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoCmd_AC_SlidePanSlot2);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoCmd_AD_SlidePanSlot1);

INCLUDE_ASM("asm/jp/nonmatchings/akao", PlaySoundEffect_8002E5F0);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoCmd_A5_SlideVolBalanceSlot1);

INCLUDE_ASM("asm/jp/nonmatchings/akao", PlayMusicTrack_8002E690);

INCLUDE_ASM("asm/jp/nonmatchings/akao", SendMusicStopCommand);

INCLUDE_ASM("asm/jp/nonmatchings/akao", PlayMusicTrackWithPanVol);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoCmd_C8_SetCdVol);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoCmd_C9_CdVolSlideFromCurr);

INCLUDE_ASM("asm/jp/nonmatchings/akao", SendSoundConfigCommand);

INCLUDE_ASM("asm/jp/nonmatchings/akao", SendMusicLayerResetCommand);

INCLUDE_ASM("asm/jp/nonmatchings/akao", SetMusicLayerTrack);

INCLUDE_ASM("asm/jp/nonmatchings/akao", SetMusicLayerTrackPan);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoCmd_D4_SetPitch);

INCLUDE_ASM("asm/jp/nonmatchings/akao", ReleaseMusicLayerTrack);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoCmd_D6_PitchSlideBetweenTargets);

INCLUDE_ASM("asm/jp/nonmatchings/akao", ResetAndStopMusicLayer);

INCLUDE_ASM("asm/jp/nonmatchings/akao", OverrideMusicLayerTrack);

INCLUDE_ASM("asm/jp/nonmatchings/akao", OverrideMusicLayerTrackWithPan);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoCmd_F0_StopMusic);

INCLUDE_ASM("asm/jp/nonmatchings/akao", CutSoundEffect);

INCLUDE_ASM("asm/jp/nonmatchings/akao", DecompressWaveMusic);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8002EA90);

INCLUDE_ASM("asm/jp/nonmatchings/akao", InstallAkaoProgramFromBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8002EB34);

INCLUDE_ASM("asm/jp/nonmatchings/akao", PlayMusicTrack_8002EBC8);

INCLUDE_ASM("asm/jp/nonmatchings/akao", StopAllMusic);

INCLUDE_ASM("asm/jp/nonmatchings/akao", SetActiveMusicBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/akao", CrossfadeToBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/akao", SetSecondaryMusicBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8002ED04);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8002EDD0);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8002EE0C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8002EEB8);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8002EF3C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8002EFB4);

INCLUDE_ASM("asm/jp/nonmatchings/akao", IsValidAkaoMagic);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8002EFF0);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8002F014);

INCLUDE_ASM("asm/jp/nonmatchings/akao", SetupAudioEventHandler);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8002F094);

INCLUDE_ASM("asm/jp/nonmatchings/akao", WaitForAudioShutdown);

INCLUDE_ASM("asm/jp/nonmatchings/akao", ProcessAkaoBlockIfValid);

INCLUDE_ASM("asm/jp/nonmatchings/akao", InstallAkaoAudioProgram);

INCLUDE_ASM("asm/jp/nonmatchings/akao", ResetAudioState);

INCLUDE_ASM("asm/jp/nonmatchings/akao", SetupSpuAndAudioEvents);

INCLUDE_ASM("asm/jp/nonmatchings/akao", InitSeLoopWorkArea);

INCLUDE_ASM("asm/jp/nonmatchings/akao", StopAndCloseSoundEvents);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoSpuKeyOn);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoSpuKeyOff);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoSpuNoiseOn);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoSpuPitchLfoOn);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoSpuReverbOn);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoSpuSetVoiceVolume);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoSpuSetVoicePitch);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoSpuSetVoiceStartAddress);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoSpuSetVoiceLoopAddress);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoSpuSetVoiceAttackRate);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoSpuSetVoiceDecayRate);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoSpuSetVoiceSustainLevel);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoSpuSetVoiceSustainRate);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoSpuSetVoiceReleaseRate);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoUpdateChannelParamsToSpu);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8002F9A4);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8002FB5C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8002FFC4);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80030420);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80030898);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80030928);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80030BE4);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80030C1C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80030CD4);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80030FD8);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80031038);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80031134);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80031228);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80031244);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80031260);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8003127C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80031314);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AdjustAudioEventAddresses);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80031394);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8003166C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_800316F8);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80031A40);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80031B98);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80031BF4);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80031DEC);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80031E64);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80031EAC);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80031F00);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8003214C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8003217C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8003220C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80032260);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_800322B4);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80032300);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80032380);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_800323E8);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80032520);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8003254C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_800325B4);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80032668);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8003272C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80032760);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_800327C8);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80032838);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80032920);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80032AA0);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80032B1C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80032BE4);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80032CC4);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80032E3C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80032EB4);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80032F78);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80033058);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_800331E0);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80033258);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80033324);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80033340);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_800333A8);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8003341C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80033438);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_800334A0);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80033514);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8003354C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80033588);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80033678);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_800336B8);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_800336F8);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80033738);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8003374C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8003383C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_800338E0);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_800339FC);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80033A94);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80033AE4);

void func_80033B38(void) {}

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80033B40);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoGetCommandQueue);

INCLUDE_ASM("asm/jp/nonmatchings/akao", SetReverbModeIfDifferent);

INCLUDE_ASM("asm/jp/nonmatchings/akao", ClearMusicStateIfMatches);

INCLUDE_ASM("asm/jp/nonmatchings/akao", UpdateSoundConfig);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80034114);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80034134);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80034158);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8003449C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoExec);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoCommandDispatcher);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80034C18);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80034C40);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80034D5C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80034E78);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80034ECC);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80034F68);

INCLUDE_ASM("asm/jp/nonmatchings/akao", AkaoExecuteChannel);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80035878);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8003591C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80035954);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_800359C0);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80035AA8);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80035AF4);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80035B94);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80035BDC);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80035C7C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80035CA8);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80035D00);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80035D28);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80035DAC);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80035DDC);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80035E68);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80035EF8);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80035F0C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80035F20);

void func_80035F34(void) {}

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80035F3C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80035F80);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8003600C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80036040);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_800360CC);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_800360E8);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80036100);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80036118);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_800361A8);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80036214);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_800362A8);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80036334);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80036358);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80036384);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_800363CC);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80036404);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8003640C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8003646C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_800364D0);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_800365C8);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80036628);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80036694);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_800366B8);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80036768);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8003678C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_800367FC);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80036820);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8003688C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_800368AC);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80036918);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8003693C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_800369B4);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80036A38);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80036AB0);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80036B20);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80036B84);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80036BE8);

void func_80036BF4(void) {}

void func_80036BFC(void) {}

void func_80036C04(void) {}

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80036C0C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80036CA8);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80036CDC);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80036D00);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80036D24);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80036D58);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80036D8C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80036DB0);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80036DD4);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80036DF8);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80036E28);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80036E64);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80036EB4);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80036F48);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80036FB4);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80037030);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80037084);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_800370AC);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_800370F4);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8003712C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80037144);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8003717C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_800371B8);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_800371F4);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80037238);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80037268);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_800372AC);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_800372DC);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80037344);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80037358);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8003736C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80037380);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80037394);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8003744C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80037490);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80037544);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80037558);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80037578);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8003760C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80037690);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80037708);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80037750);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80037968);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80037B24);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80037BF4);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80037C58);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80037CBC);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80037E08);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80037E38);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80037E68);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80037E98);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80037EC8);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80037F10);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80037F30);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80037FA0);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80038020);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8003816C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80038198);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8003826C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80038434);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_800385D0);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_8003861C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80038660);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80038698);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_800386E4);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80038830);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_800388AC);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80038948);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80038A18);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80038A7C);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80038BB8);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80038BE8);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80038C18);

INCLUDE_ASM("asm/jp/nonmatchings/akao", func_80038C64);
