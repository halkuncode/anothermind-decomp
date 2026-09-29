#include "common.h"

INCLUDE_ASM("asm/jp/nonmatchings/sound", InitSoundDriver);

INCLUDE_ASM("asm/jp/nonmatchings/sound", ShutdownSoundSystem);

INCLUDE_ASM("asm/jp/nonmatchings/sound", EnsureSeLoopBlockInitialized);

INCLUDE_ASM("asm/jp/nonmatchings/sound", HandleMusicCommand);

INCLUDE_ASM("asm/jp/nonmatchings/sound", ResetSoundSystem);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002DF24);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002DF4C);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002DF80);

INCLUDE_ASM("asm/jp/nonmatchings/sound", PlaySoundEffect_8002DFB4);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002E008);

INCLUDE_ASM("asm/jp/nonmatchings/sound", StopSoundEffect);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002E0D0);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002E104);

INCLUDE_ASM("asm/jp/nonmatchings/sound", IsResourceLoaded);

INCLUDE_ASM("asm/jp/nonmatchings/sound", SetSoundMode);

INCLUDE_ASM("asm/jp/nonmatchings/sound", MuteAudioChannels);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002E250);

INCLUDE_ASM("asm/jp/nonmatchings/sound", ApplySoundProfile);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002E2F0);

INCLUDE_ASM("asm/jp/nonmatchings/sound", SetMusicVolumeLevel);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002E394);

INCLUDE_ASM("asm/jp/nonmatchings/sound", PlayMusicTrack_8002E3D0);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002E41C);

INCLUDE_ASM("asm/jp/nonmatchings/sound", SetMusicPan);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002E4A4);

INCLUDE_ASM("asm/jp/nonmatchings/sound", PlaySystemSound);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002E52C);

INCLUDE_ASM("asm/jp/nonmatchings/sound", StopMusicTrack);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002E5B4);

INCLUDE_ASM("asm/jp/nonmatchings/sound", PlaySoundEffect_8002E5F0);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002E63C);

INCLUDE_ASM("asm/jp/nonmatchings/sound", PlayMusicTrack_8002E690);

INCLUDE_ASM("asm/jp/nonmatchings/sound", SendMusicStopCommand);

INCLUDE_ASM("asm/jp/nonmatchings/sound", PlayMusicTrackWithPanVol);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002E748);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002E778);

INCLUDE_ASM("asm/jp/nonmatchings/sound", SendSoundConfigCommand);

INCLUDE_ASM("asm/jp/nonmatchings/sound", SendMusicLayerResetCommand);

INCLUDE_ASM("asm/jp/nonmatchings/sound", SetMusicLayerTrack);

INCLUDE_ASM("asm/jp/nonmatchings/sound", SetMusicLayerTrackPan);

INCLUDE_ASM("asm/jp/nonmatchings/sound", StopMusicLayer);

INCLUDE_ASM("asm/jp/nonmatchings/sound", ReleaseMusicLayerTrack);

INCLUDE_ASM("asm/jp/nonmatchings/sound", StopMusicLayerTrackWithPan);

INCLUDE_ASM("asm/jp/nonmatchings/sound", ResetAndStopMusicLayer);

INCLUDE_ASM("asm/jp/nonmatchings/sound", OverrideMusicLayerTrack);

INCLUDE_ASM("asm/jp/nonmatchings/sound", OverrideMusicLayerTrackWithPan);

INCLUDE_ASM("asm/jp/nonmatchings/sound", StopMusicNow);

INCLUDE_ASM("asm/jp/nonmatchings/sound", CutSoundEffect);

INCLUDE_ASM("asm/jp/nonmatchings/sound", DecompressWaveMusic);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002EA90);

INCLUDE_ASM("asm/jp/nonmatchings/sound", InstallOakaProgramFromBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002EB34);

INCLUDE_ASM("asm/jp/nonmatchings/sound", PlayMusicTrack_8002EBC8);

INCLUDE_ASM("asm/jp/nonmatchings/sound", StopAllMusic);

INCLUDE_ASM("asm/jp/nonmatchings/sound", SetActiveMusicBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/sound", CrossfadeToBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/sound", SetSecondaryMusicBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002ED04);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002EDD0);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002EE0C);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002EEB8);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002EF3C);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002EFB4);

INCLUDE_ASM("asm/jp/nonmatchings/sound", IsValidOakaMagic);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002EFF0);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002F014);

INCLUDE_ASM("asm/jp/nonmatchings/sound", SetupAudioEventHandler);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002F094);

INCLUDE_ASM("asm/jp/nonmatchings/sound", WaitForAudioShutdown);

INCLUDE_ASM("asm/jp/nonmatchings/sound", ProcessOakaBlockIfValid);

INCLUDE_ASM("asm/jp/nonmatchings/sound", InstallOakaAudioProgram);

INCLUDE_ASM("asm/jp/nonmatchings/sound", ResetAudioState);

INCLUDE_ASM("asm/jp/nonmatchings/sound", SetupSpuAndAudioEvents);

INCLUDE_ASM("asm/jp/nonmatchings/sound", InitSeLoopWorkArea);

INCLUDE_ASM("asm/jp/nonmatchings/sound", StopAndCloseSoundEvents);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002F670);

INCLUDE_ASM("asm/jp/nonmatchings/sound", StopSpuVoices);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002F6A8);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002F6C4);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002F6E0);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002F6FC);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002F744);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002F75C);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002F778);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002F794);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002F7C4);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002F7EC);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002F814);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002F848);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002F878);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002F9A4);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002FB5C);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8002FFC4);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80030420);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80030898);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80030928);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80030BE4);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80030C1C);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80030CD4);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80030FD8);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80031038);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80031134);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80031228);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80031244);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80031260);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8003127C);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80031314);

INCLUDE_ASM("asm/jp/nonmatchings/sound", AdjustAudioEventAddresses);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80031394);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8003166C);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_800316F8);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80031A40);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80031B98);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80031BF4);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80031DEC);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80031E64);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80031EAC);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80031F00);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8003214C);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8003217C);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8003220C);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80032260);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_800322B4);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80032300);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80032380);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_800323E8);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80032520);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8003254C);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_800325B4);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80032668);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8003272C);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80032760);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_800327C8);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80032838);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80032920);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80032AA0);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80032B1C);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80032BE4);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80032CC4);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80032E3C);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80032EB4);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80032F78);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80033058);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_800331E0);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80033258);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80033324);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80033340);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_800333A8);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8003341C);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80033438);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_800334A0);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80033514);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8003354C);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80033588);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80033678);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_800336B8);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_800336F8);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80033738);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8003374C);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_8003383C);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_800338E0);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_800339FC);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80033A94);

INCLUDE_ASM("asm/jp/nonmatchings/sound", func_80033AE4);

void func_80033B38(void) {}
