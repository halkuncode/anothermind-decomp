#include "common.h"
#include <libetc.h>
#include <libgpu.h>
#include <libsnd.h>

void abort(void) { M2C_BREAK(1); }

extern void DoGame(void);

void main(void) {
  StopCallback();
  ResetCallback();
  ResetGraph(0);
  SsUtReverbOff();
  DoGame();
  while (1)
    ;
}

INCLUDE_ASM("asm/jp/nonmatchings/main", ResetToReleaseMode);

INCLUDE_ASM("asm/jp/nonmatchings/main", UpdateSystemPerFrame);

INCLUDE_ASM("asm/jp/nonmatchings/main", DisplaySystemDebugPanel);

INCLUDE_ASM("asm/jp/nonmatchings/main", GetDebugLockState);

INCLUDE_ASM("asm/jp/nonmatchings/main", LockoutDebug);

INCLUDE_ASM("asm/jp/nonmatchings/main", GetDebugScriptBuildDateString);

INCLUDE_ASM("asm/jp/nonmatchings/main", IntToAscii);

INCLUDE_ASM("asm/jp/nonmatchings/main", ReportIssue);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80012DEC);

INCLUDE_ASM("asm/jp/nonmatchings/main", DecompressLZSS);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800130BC);

INCLUDE_ASM("asm/jp/nonmatchings/main", CheckAndUnpackAmpack);

INCLUDE_ASM("asm/jp/nonmatchings/main", ReadLittleEndian32);

INCLUDE_ASM("asm/jp/nonmatchings/main", LoadProgdata);

INCLUDE_ASM("asm/jp/nonmatchings/main", RunNameEntryScreen);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80013CE4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800141E8);

INCLUDE_ASM("asm/jp/nonmatchings/main", LoadTextGraphics);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80014530);

INCLUDE_ASM("asm/jp/nonmatchings/main", InitDrawEnvEffects);

INCLUDE_ASM("asm/jp/nonmatchings/main", RenderNameEntryScreen);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80014C90);

INCLUDE_ASM("asm/jp/nonmatchings/main", InitNameEntryScreen);

INCLUDE_ASM("asm/jp/nonmatchings/main", GetEnteredNameLength_80014F5C);

INCLUDE_ASM("asm/jp/nonmatchings/main", DrawNameEntryTitle);

INCLUDE_ASM("asm/jp/nonmatchings/main", CopyNameBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/main", WriteNameToGameBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/main", LoadNameFont);

INCLUDE_ASM("asm/jp/nonmatchings/main", DrawNameFontGlyph);

INCLUDE_ASM("asm/jp/nonmatchings/main", DeleteGlyphFromNameBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/main", InitializeNameBuffers);

INCLUDE_ASM("asm/jp/nonmatchings/main", InitNameEntryBuffers);

INCLUDE_ASM("asm/jp/nonmatchings/main", LoadDefaultNameIfEmpty);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetNameEntryColor);

INCLUDE_ASM("asm/jp/nonmatchings/main", DrawNameBufferPreview);

INCLUDE_ASM("asm/jp/nonmatchings/main", WriteNameGlyphAndMetadata);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800156F8);

INCLUDE_ASM("asm/jp/nonmatchings/main", HandleNameConfirmOrCancel);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80015800);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80015868);

INCLUDE_ASM("asm/jp/nonmatchings/main", GetEnteredNameLength_800158E8);

INCLUDE_ASM("asm/jp/nonmatchings/main", StartVibrationEffect);

INCLUDE_ASM("asm/jp/nonmatchings/main", DisplayPadDebugPanel);

INCLUDE_ASM("asm/jp/nonmatchings/main", DoVibeEffect3);

INCLUDE_ASM("asm/jp/nonmatchings/main", BeginTaiwaVibration);

INCLUDE_ASM("asm/jp/nonmatchings/main", CancelVibrationEffect);

INCLUDE_ASM("asm/jp/nonmatchings/main", ResetMovieIRQSystem);

INCLUDE_ASM("asm/jp/nonmatchings/main", GetRawControllerInput);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80015E4C);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetVibrationMode_80015E70);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetVibrationMode_80015EBC);

INCLUDE_ASM("asm/jp/nonmatchings/main", IsVibrationEnabled);

INCLUDE_ASM("asm/jp/nonmatchings/main", StopVibrationEffect);

INCLUDE_ASM("asm/jp/nonmatchings/main", GetMovieBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/main", GetNextInterpolatedByte);

INCLUDE_ASM("asm/jp/nonmatchings/main", LoadVibrationVIBFile);

INCLUDE_ASM("asm/jp/nonmatchings/main", ResetVibrationSystem);

INCLUDE_ASM("asm/jp/nonmatchings/main", UpdateVibrationAndInput);

INCLUDE_ASM("asm/jp/nonmatchings/main", IsVibrationActive);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800161A0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800161F0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80016200);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8001623C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80016300);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800163B0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80016404);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80016468);

INCLUDE_ASM("asm/jp/nonmatchings/main", DisplayChapterTitle);

INCLUDE_ASM("asm/jp/nonmatchings/main", RunChapterTitleFadeIn);

INCLUDE_ASM("asm/jp/nonmatchings/main", DrawLogoLines);

INCLUDE_ASM("asm/jp/nonmatchings/main", AnimateChapterTitleLogoEffect);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80016CDC);

INCLUDE_ASM("asm/jp/nonmatchings/main", InitChapterTitlePrimitives);

INCLUDE_ASM("asm/jp/nonmatchings/main", LoadChapterTitleTextures);

INCLUDE_ASM("asm/jp/nonmatchings/main", FadeInLogo);

INCLUDE_ASM("asm/jp/nonmatchings/main", FadeOutChapterTitleLogoEffect);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800173E4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800174B0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80017518);

INCLUDE_ASM("asm/jp/nonmatchings/main", SubmitChapterTitleDrawPrimitives);

INCLUDE_ASM("asm/jp/nonmatchings/main", ShowSquaresoftLogo);

INCLUDE_ASM("asm/jp/nonmatchings/main", LoadSquaresoftLogo);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetFadePrimitiveColor);

INCLUDE_ASM("asm/jp/nonmatchings/main", InitFadeInPrimitives);

INCLUDE_ASM("asm/jp/nonmatchings/main", EnqueueFadeInPrimitives);

INCLUDE_ASM("asm/jp/nonmatchings/main", GoToTitleScreen);

INCLUDE_ASM("asm/jp/nonmatchings/main", FadeInCharactersOnTitleScreen);

INCLUDE_ASM("asm/jp/nonmatchings/main", UpdateTitleScreenMenuState);

INCLUDE_ASM("asm/jp/nonmatchings/main", TitleFadeOutAfterSelection);

INCLUDE_ASM("asm/jp/nonmatchings/main", LoadTitleAnimationAssets);

INCLUDE_ASM("asm/jp/nonmatchings/main", GTitleTilePrimitiveTable);

INCLUDE_ASM("asm/jp/nonmatchings/main", TitleScreenFadeIn);

INCLUDE_ASM("asm/jp/nonmatchings/main", FadeInCharacterOverlay);

INCLUDE_ASM("asm/jp/nonmatchings/main", AnimateTitleScreenIdleLoop);

INCLUDE_ASM("asm/jp/nonmatchings/main", DrawTitleScreenDebugOverlay);

INCLUDE_ASM("asm/jp/nonmatchings/main", LoadDebugTitleScreen);

INCLUDE_ASM("asm/jp/nonmatchings/main", DisplayEndTitle);

INCLUDE_ASM("asm/jp/nonmatchings/main", AnimateEndTitleFadeIn);

INCLUDE_ASM("asm/jp/nonmatchings/main", InitEndTitlePrimitives);

INCLUDE_ASM("asm/jp/nonmatchings/main", AnimateEndTitleFadeOut);

INCLUDE_ASM("asm/jp/nonmatchings/main", LoadChapterEndGraphic);

INCLUDE_ASM("asm/jp/nonmatchings/main", GetCdFileSectorInfo);

INCLUDE_ASM("asm/jp/nonmatchings/main", ProcessCdReadStateMachine);

INCLUDE_ASM("asm/jp/nonmatchings/main", DisplayCdFileDebugStatus);

INCLUDE_ASM("asm/jp/nonmatchings/main", LoadRawSectorData);

INCLUDE_ASM("asm/jp/nonmatchings/main", LoadCdPosTablefromCd);

INCLUDE_ASM("asm/jp/nonmatchings/main", LoadByFileIdGroupId);

INCLUDE_ASM("asm/jp/nonmatchings/main", LoadFileFromGroupByIndex);

INCLUDE_ASM("asm/jp/nonmatchings/main", WaitForCdIdle);

INCLUDE_ASM("asm/jp/nonmatchings/main", GetFilename);

INCLUDE_ASM("asm/jp/nonmatchings/main", GetFileCountInGroup);

INCLUDE_ASM("asm/jp/nonmatchings/main", IsDebugDisabled);

s32 func_80019CF4(void) { return 0; }

INCLUDE_ASM("asm/jp/nonmatchings/main", SeekToCdFileEntry);

INCLUDE_ASM("asm/jp/nonmatchings/main", SeekCdToFileStart);

INCLUDE_ASM("asm/jp/nonmatchings/main", PlayCdAudioTrack);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80019E24);

INCLUDE_ASM("asm/jp/nonmatchings/main", GetSectorForMovieId);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80019EC4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80019F88);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8001A01C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8001A0B0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8001A124);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8001A160);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8001A1F4);

INCLUDE_ASM("asm/jp/nonmatchings/main", UpdateCdTransferState);

void func_8001A2A4(void) {}

INCLUDE_ASM("asm/jp/nonmatchings/main", StartPlayMovie);

INCLUDE_ASM("asm/jp/nonmatchings/main", PlayScriptedMovieCutscene);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8001A890);

INCLUDE_ASM("asm/jp/nonmatchings/main", UpdateMoviePlaybackFrame);

INCLUDE_ASM("asm/jp/nonmatchings/main", DisplayMovieDebugPanel);

INCLUDE_ASM("asm/jp/nonmatchings/main", InitMoviePlaybackContext);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetupMovieStream);

INCLUDE_ASM("asm/jp/nonmatchings/main", ProcessNextVideoBlock);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8001B248);

INCLUDE_ASM("asm/jp/nonmatchings/main", WaitForFrameReadyOrFallback);

INCLUDE_ASM("asm/jp/nonmatchings/main", GetNextMdecBitstream);

INCLUDE_ASM("asm/jp/nonmatchings/main", SeekCdAndBeginStream);

INCLUDE_ASM("asm/jp/nonmatchings/main", PlayMovieSegmentById);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetupMovieDecoder);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetCdAudioMonoStereo);

INCLUDE_ASM("asm/jp/nonmatchings/main", PlayTitleScreenCutscene);

INCLUDE_ASM("asm/jp/nonmatchings/main", StartScriptedMovieWithFade);

void func_8001B854(void) {}

void func_8001B85C(void) {}

INCLUDE_ASM("asm/jp/nonmatchings/main", StopScriptedMovieDecoder);

INCLUDE_ASM("asm/jp/nonmatchings/main", IsMovieDecoderActive);

INCLUDE_ASM("asm/jp/nonmatchings/main", GetCurrentMovieFrame);

INCLUDE_ASM("asm/jp/nonmatchings/main", PlayDefaultMovieSegment);

INCLUDE_ASM("asm/jp/nonmatchings/main", PlayMovieSegmentUsingOffsetOrDefault);

INCLUDE_ASM("asm/jp/nonmatchings/main", LoopMovieById);

INCLUDE_ASM("asm/jp/nonmatchings/main", ShutdownMovieDecoder);

INCLUDE_ASM("asm/jp/nonmatchings/main", ResetMovieDecoderState);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8001B9C4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8001B9D0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8001BA64);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8001BAC0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8001BB00);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetCdBusyStatus);

INCLUDE_ASM("asm/jp/nonmatchings/main", ResetCdTransferReadyFlag);

INCLUDE_ASM("asm/jp/nonmatchings/main", ClearCdTransferReadyFlag);

INCLUDE_ASM("asm/jp/nonmatchings/main", IsCdTransferReady);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8001BCE8);

INCLUDE_ASM("asm/jp/nonmatchings/main", DisplayCdControlStatusToDebugScreen);

INCLUDE_ASM("asm/jp/nonmatchings/main", InitOpcodeHandlerTable);

INCLUDE_ASM("asm/jp/nonmatchings/main", InitializeScriptInterpreter);

INCLUDE_ASM("asm/jp/nonmatchings/main", ResetFullGameRuntimeState_8001CA18);

INCLUDE_ASM("asm/jp/nonmatchings/main", LoadPortraitLoopCutData);

INCLUDE_ASM("asm/jp/nonmatchings/main", LoadPortraitTextGridData);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8001D48C);

INCLUDE_ASM("asm/jp/nonmatchings/main", ApplySaveGameState);

INCLUDE_ASM("asm/jp/nonmatchings/main", UpdateScriptStateAndDebugInput);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_interpreterStep);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_handleScriptBlock);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_print_a);

INCLUDE_ASM("asm/jp/nonmatchings/main", DecodePortraitAnimBlock);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_call);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_thread);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_bg2);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_kbg2);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_movie2);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_movieflash2);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_movieFstate);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_movieFframe);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_allmuisc);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_seloop);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_allSE);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_oneSE);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_allStream);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_setVariableByType);

INCLUDE_ASM("asm/jp/nonmatchings/main", ExecuteUnaryOpcode);

INCLUDE_ASM("asm/jp/nonmatchings/main", ExecuteEquationOpcode);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_ifv);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_ifs);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_ifs2);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_ifo);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_ifo2);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_ifc);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_ifc2);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_ifvar);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_face_a);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_facer_a);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_pset_a);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_mset_a);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_mwin);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_exec);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_enter);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_exit);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_pmove_a);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_facelight);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_faceEffect);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_din);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_dout);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_sjump);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_jsel);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_mdel_s);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_vardel_j);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_loaddict);

INCLUDE_ASM("asm/jp/nonmatchings/main", LoadDictionaryData);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_watch);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_watch16);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_watchflag);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_getRandom);

INCLUDE_ASM("asm/jp/nonmatchings/main", MatchNameExpression);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_newsel);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_getnews_80025CCC);

INCLUDE_ASM("asm/jp/nonmatchings/main", ValidateScriptHeader);

INCLUDE_ASM("asm/jp/nonmatchings/main", DecodeScriptOperand);

INCLUDE_ASM("asm/jp/nonmatchings/main", GetTaiwaNoun);

INCLUDE_ASM("asm/jp/nonmatchings/main", ReportSystemError);

INCLUDE_ASM("asm/jp/nonmatchings/main", CopyScriptToRuntimeBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/main", InitTitleScreenAudio);

INCLUDE_ASM("asm/jp/nonmatchings/main", ForceStopMusic);

INCLUDE_ASM("asm/jp/nonmatchings/main", LoadStoryScript);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetupDebugOptionMenu);

INCLUDE_ASM("asm/jp/nonmatchings/main", PlaySingleSoundeffect);

INCLUDE_ASM("asm/jp/nonmatchings/main", PlayConditionalSoundEffect);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80026CB0);

INCLUDE_ASM("asm/jp/nonmatchings/main", MaybeStartTaiwaVibration);

INCLUDE_ASM("asm/jp/nonmatchings/main", DispatchScriptOpcode);

INCLUDE_ASM("asm/jp/nonmatchings/main", JumpOpcodeFuncViaTable);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_errorUnknownOpcode);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_wait);

INCLUDE_ASM("asm/jp/nonmatchings/main", ResetPortraitState);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_mspeed);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_loadkanji);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_return);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_threadret);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_threadstop);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_bg);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_kbg);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_movie);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_movieflash);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_vibrateflash);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_movieF);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_movieF2);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_movieFstop);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_movieFblock);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_movieFloop);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_soundmode);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_music);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_musiccut);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_loadmusic);

INCLUDE_ASM("asm/jp/nonmatchings/main", LoadMusic);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_loadwavemusic);

INCLUDE_ASM("asm/jp/nonmatchings/main", LoadWaveMusic);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_channelMute);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_finale);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_se);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_sse);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_ve);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_vestop);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_seStop);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_secut);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_loadse);

INCLUDE_ASM("asm/jp/nonmatchings/main", LoadSoundEffect);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_loadwaveSE);

INCLUDE_ASM("asm/jp/nonmatchings/main", LoadAudioId);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_loadwaveStream);

INCLUDE_ASM("asm/jp/nonmatchings/main", LoadAudioStream);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_cdplay);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_if);

INCLUDE_ASM("asm/jp/nonmatchings/main", ComputeMovementStep);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_effectB);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_seekF);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_seekB);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_backF);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_talk);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_ltalk);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_tset);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_byuu);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_preDinXX);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_dinbrainoff);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_doutWithFaceSlotXX);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_nin);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_ninjump);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_nincall);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_ninwait);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_nout);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_end);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_bp);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_present);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_tagon);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80028FA4);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_brainon);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_brainoff);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_aurthor);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_place);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_date);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_time);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_chapter);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_chapterTitle);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_endTitle);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_scene);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_inputName);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_vibrateMode);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_menuMode);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_menuOpen);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_getnews_80029820);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_newsput);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_newsquit);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_logicalAnd);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_logicalOr);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_bitwiseAnd);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_bitwiseOr);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_bitwiseXor);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_logicalNot);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_negate);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_add);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_subtract);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_multiply);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_divide);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_modulo);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_setVariable);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_shiftLeft);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_shiftRight);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_equal);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_notEqual);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_lessThan);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_lessThanOrEqual);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_greaterThan);

INCLUDE_ASM("asm/jp/nonmatchings/main", Func_graterThanOrEqualTo);

INCLUDE_ASM("asm/jp/nonmatchings/main", ReadScript16bitBE);

INCLUDE_ASM("asm/jp/nonmatchings/main", ReportError);

INCLUDE_ASM("asm/jp/nonmatchings/main", DoDebugOptionMenu);

INCLUDE_ASM("asm/jp/nonmatchings/main", DrawGlobalInspectorList);

INCLUDE_ASM("asm/jp/nonmatchings/main", PrintScriptSystemDebug);

INCLUDE_ASM("asm/jp/nonmatchings/main", DrawWatchedScriptFlags);

INCLUDE_ASM("asm/jp/nonmatchings/main", PrintScriptBasicDebug);

INCLUDE_ASM("asm/jp/nonmatchings/main", ShowTaiwaDebugData);

INCLUDE_ASM("asm/jp/nonmatchings/main", DrawFlagInspectorList);

INCLUDE_ASM("asm/jp/nonmatchings/main", DbgPrintCallandJump);

INCLUDE_ASM("asm/jp/nonmatchings/main", DrawScriptExecutionLog);

INCLUDE_ASM("asm/jp/nonmatchings/main", DrawWatchDebugValues);

INCLUDE_ASM("asm/jp/nonmatchings/main", DrawWatch16ValuesHex);

INCLUDE_ASM("asm/jp/nonmatchings/main", DrawWatch16ValuesBinary);

INCLUDE_ASM("asm/jp/nonmatchings/main", DbgScreenPrintBinary);

INCLUDE_ASM("asm/jp/nonmatchings/main", PrintDebugBinaryGroupString);

INCLUDE_ASM("asm/jp/nonmatchings/main", LogDecimalNumber);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002B494);

INCLUDE_ASM("asm/jp/nonmatchings/main", LogCommand);

INCLUDE_ASM("asm/jp/nonmatchings/main", LogArgumentString);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetActiveScriptLabel);

INCLUDE_ASM("asm/jp/nonmatchings/main", RecordCallLabel);

INCLUDE_ASM("asm/jp/nonmatchings/main", ConvertIntToAscii);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002B680);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002BA98);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002BEF8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002C3CC);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002C5D8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002C6BC);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002C70C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002C7FC);

INCLUDE_ASM("asm/jp/nonmatchings/main", ResetDialogueTrackingState);

INCLUDE_ASM("asm/jp/nonmatchings/main", PreprocessScriptBlock);

INCLUDE_ASM("asm/jp/nonmatchings/main", AdvanceScriptOperandPtr);

INCLUDE_ASM("asm/jp/nonmatchings/main", ReadLE16FromScript);

INCLUDE_ASM("asm/jp/nonmatchings/main", SkipNext8ScriptBytes);

INCLUDE_ASM("asm/jp/nonmatchings/main", InitSoundDriver);

INCLUDE_ASM("asm/jp/nonmatchings/main", ShutdownSoundSystem);

INCLUDE_ASM("asm/jp/nonmatchings/main", EnsureSeLoopBlockInitialized);

INCLUDE_ASM("asm/jp/nonmatchings/main", HandleMusicCommand);

INCLUDE_ASM("asm/jp/nonmatchings/main", ResetSoundSystem);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002DF24);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002DF4C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002DF80);

INCLUDE_ASM("asm/jp/nonmatchings/main", PlaySoundEffect_8002DFB4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002E008);

INCLUDE_ASM("asm/jp/nonmatchings/main", StopSoundEffect);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002E0D0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002E104);

INCLUDE_ASM("asm/jp/nonmatchings/main", IsResourceLoaded);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetSoundMode);

INCLUDE_ASM("asm/jp/nonmatchings/main", MuteAudioChannels);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002E250);

INCLUDE_ASM("asm/jp/nonmatchings/main", ApplySoundProfile);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002E2F0);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetMusicVolumeLevel);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002E394);

INCLUDE_ASM("asm/jp/nonmatchings/main", PlayMusicTrack_8002E3D0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002E41C);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetMusicPan);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002E4A4);

INCLUDE_ASM("asm/jp/nonmatchings/main", PlaySystemSound);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002E52C);

INCLUDE_ASM("asm/jp/nonmatchings/main", StopMusicTrack);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002E5B4);

INCLUDE_ASM("asm/jp/nonmatchings/main", PlaySoundEffect_8002E5F0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002E63C);

INCLUDE_ASM("asm/jp/nonmatchings/main", PlayMusicTrack_8002E690);

INCLUDE_ASM("asm/jp/nonmatchings/main", SendMusicStopCommand);

INCLUDE_ASM("asm/jp/nonmatchings/main", PlayMusicTrackWithPanVol);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002E748);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002E778);

INCLUDE_ASM("asm/jp/nonmatchings/main", SendSoundConfigCommand);

INCLUDE_ASM("asm/jp/nonmatchings/main", SendMusicLayerResetCommand);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetMusicLayerTrack);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetMusicLayerTrackPan);

INCLUDE_ASM("asm/jp/nonmatchings/main", StopMusicLayer);

INCLUDE_ASM("asm/jp/nonmatchings/main", ReleaseMusicLayerTrack);

INCLUDE_ASM("asm/jp/nonmatchings/main", StopMusicLayerTrackWithPan);

INCLUDE_ASM("asm/jp/nonmatchings/main", ResetAndStopMusicLayer);

INCLUDE_ASM("asm/jp/nonmatchings/main", OverrideMusicLayerTrack);

INCLUDE_ASM("asm/jp/nonmatchings/main", OverrideMusicLayerTrackWithPan);

INCLUDE_ASM("asm/jp/nonmatchings/main", StopMusicNow);

INCLUDE_ASM("asm/jp/nonmatchings/main", CutSoundEffect);

INCLUDE_ASM("asm/jp/nonmatchings/main", DecompressWaveMusic);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002EA90);

INCLUDE_ASM("asm/jp/nonmatchings/main", InstallOakaProgramFromBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002EB34);

INCLUDE_ASM("asm/jp/nonmatchings/main", PlayMusicTrack_8002EBC8);

INCLUDE_ASM("asm/jp/nonmatchings/main", StopAllMusic);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetActiveMusicBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/main", CrossfadeToBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetSecondaryMusicBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002ED04);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002EDD0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002EE0C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002EEB8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002EF3C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002EFB4);

INCLUDE_ASM("asm/jp/nonmatchings/main", IsValidOakaMagic);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002EFF0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002F014);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetupAudioEventHandler);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002F094);

INCLUDE_ASM("asm/jp/nonmatchings/main", WaitForAudioShutdown);

INCLUDE_ASM("asm/jp/nonmatchings/main", ProcessOakaBlockIfValid);

INCLUDE_ASM("asm/jp/nonmatchings/main", InstallOakaAudioProgram);

INCLUDE_ASM("asm/jp/nonmatchings/main", ResetAudioState);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetupSpuAndAudioEvents);

INCLUDE_ASM("asm/jp/nonmatchings/main", InitSeLoopWorkArea);

INCLUDE_ASM("asm/jp/nonmatchings/main", StopAndCloseSoundEvents);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002F670);

INCLUDE_ASM("asm/jp/nonmatchings/main", StopSpuVoices);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002F6A8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002F6C4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002F6E0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002F6FC);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002F744);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002F75C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002F778);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002F794);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002F7C4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002F7EC);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002F814);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002F848);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002F878);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002F9A4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002FB5C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8002FFC4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80030420);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80030898);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80030928);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80030BE4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80030C1C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80030CD4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80030FD8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80031038);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80031134);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80031228);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80031244);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80031260);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003127C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80031314);

INCLUDE_ASM("asm/jp/nonmatchings/main", AdjustAudioEventAddresses);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80031394);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003166C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800316F8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80031A40);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80031B98);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80031BF4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80031DEC);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80031E64);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80031EAC);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80031F00);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003214C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003217C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003220C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80032260);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800322B4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80032300);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80032380);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800323E8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80032520);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003254C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800325B4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80032668);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003272C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80032760);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800327C8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80032838);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80032920);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80032AA0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80032B1C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80032BE4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80032CC4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80032E3C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80032EB4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80032F78);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80033058);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800331E0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80033258);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80033324);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80033340);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800333A8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003341C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80033438);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800334A0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80033514);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003354C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80033588);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80033678);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800336B8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800336F8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80033738);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003374C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003383C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800338E0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800339FC);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80033A94);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80033AE4);

void func_80033B38(void) {}

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80033B40);

INCLUDE_ASM("asm/jp/nonmatchings/main", AllocateSoundCommand);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetReverbModeIfDifferent);

INCLUDE_ASM("asm/jp/nonmatchings/main", ClearMusicStateIfMatches);

INCLUDE_ASM("asm/jp/nonmatchings/main", UpdateSoundConfig);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80034114);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80034134);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80034158);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003449C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003471C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800349F0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80034C18);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80034C40);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80034D5C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80034E78);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80034ECC);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80034F68);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80035168);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80035878);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003591C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80035954);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800359C0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80035AA8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80035AF4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80035B94);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80035BDC);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80035C7C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80035CA8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80035D00);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80035D28);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80035DAC);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80035DDC);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80035E68);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80035EF8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80035F0C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80035F20);

void func_80035F34(void) {}

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80035F3C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80035F80);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003600C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80036040);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800360CC);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800360E8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80036100);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80036118);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800361A8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80036214);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800362A8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80036334);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80036358);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80036384);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800363CC);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80036404);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003640C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003646C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800364D0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800365C8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80036628);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80036694);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800366B8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80036768);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003678C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800367FC);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80036820);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003688C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800368AC);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80036918);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003693C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800369B4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80036A38);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80036AB0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80036B20);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80036B84);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80036BE8);

void func_80036BF4(void) {}

void func_80036BFC(void) {}

void func_80036C04(void) {}

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80036C0C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80036CA8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80036CDC);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80036D00);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80036D24);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80036D58);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80036D8C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80036DB0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80036DD4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80036DF8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80036E28);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80036E64);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80036EB4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80036F48);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80036FB4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80037030);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80037084);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800370AC);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800370F4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003712C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80037144);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003717C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800371B8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800371F4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80037238);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80037268);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800372AC);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800372DC);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80037344);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80037358);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003736C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80037380);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80037394);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003744C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80037490);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80037544);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80037558);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80037578);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003760C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80037690);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80037708);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80037750);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80037968);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80037B24);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80037BF4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80037C58);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80037CBC);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80037E08);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80037E38);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80037E68);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80037E98);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80037EC8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80037F10);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80037F30);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80037FA0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80038020);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003816C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80038198);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003826C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80038434);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800385D0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003861C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80038660);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80038698);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800386E4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80038830);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800388AC);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80038948);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80038A18);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80038A7C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80038BB8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80038BE8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80038C18);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80038C64);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80038CF4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80038D24);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetGeomOffset);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetGeomScreen);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80038D74);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80038E20);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80038E54);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80038FCC);

INCLUDE_ASM("asm/jp/nonmatchings/main", ResetCallback);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80039094);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800390C4);

INCLUDE_ASM("asm/jp/nonmatchings/main", VSyncCallback);

INCLUDE_ASM("asm/jp/nonmatchings/main", VSyncCallbacks);

INCLUDE_ASM("asm/jp/nonmatchings/main", StopCallback);

INCLUDE_ASM("asm/jp/nonmatchings/main", RestartCallback);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800391B8);

INCLUDE_ASM("asm/jp/nonmatchings/main", GetIntrMask);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800391E0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800391F8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800392D0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800394A0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800395E8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80039688);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80039700);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80039724);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003977C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800397E8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80039814);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80039844);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80039890);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80039A10);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80039ABC);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80039AE4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80039B14);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80039B38);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80039D64);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80039DF4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80039E30);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80039E58);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80039E80);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80039EB4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80039EC4);

INCLUDE_ASM("asm/jp/nonmatchings/main", CdLastCom);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80039EE4);

INCLUDE_ASM("asm/jp/nonmatchings/main", CdReset);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80039F5C);

INCLUDE_ASM("asm/jp/nonmatchings/main", CdSetDebug);

INCLUDE_ASM("asm/jp/nonmatchings/main", CdComstr);

INCLUDE_ASM("asm/jp/nonmatchings/main", CdIntstr);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80039FF8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003A018);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003A038);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003A04C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003A060);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003A19C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003A2D0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003A41C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003A43C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003A45C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003A47C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003A4A0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003A4C0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003A5C4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003A644);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003ABA0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003AE20);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003B0E8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003B4F4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003B57C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003B650);

INCLUDE_ASM("asm/jp/nonmatchings/main", CD_initintr);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003B78C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003B96C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003BAD4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003BBD4);

INCLUDE_ASM("asm/jp/nonmatchings/main", CD_set_test_parmnum);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003BCCC);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003BDA4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003BDD8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003C04C);

INCLUDE_ASM("asm/jp/nonmatchings/main", ResetCdStateAndRead);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003C304);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003C4A4);

INCLUDE_ASM("asm/jp/nonmatchings/main", WaitForCdReady);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003C744);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003C758);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003C774);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003C7F8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003C824);

INCLUDE_ASM("asm/jp/nonmatchings/main", StUnSetRing);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003C904);

INCLUDE_ASM("asm/jp/nonmatchings/main", StGetBackloc);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003C9F4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003CA84);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003CB34);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003CB74);

INCLUDE_ASM("asm/jp/nonmatchings/main", StSetMask);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003CC54);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003D570);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003D59C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003D744);

INCLUDE_ASM("asm/jp/nonmatchings/main", DecDCTGetEnv);

INCLUDE_ASM("asm/jp/nonmatchings/main", DecDCTPutEnv);

INCLUDE_ASM("asm/jp/nonmatchings/main", DecDCTBufSize);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003D8A8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003D924);

INCLUDE_ASM("asm/jp/nonmatchings/main", DecDCTinSync);

INCLUDE_ASM("asm/jp/nonmatchings/main", DecDCToutSync);

INCLUDE_ASM("asm/jp/nonmatchings/main", DecDCTinCallback);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003D9E0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003DA04);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003DAF4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003DB84);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003DC10);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003DCA4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003DD38);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003DD50);

INCLUDE_ASM("asm/jp/nonmatchings/main", DecDCTvlcSize);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003DE04);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003E154);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003E17C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003E194);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003E1A4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003E1B4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003E1C4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003E1E4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003E1F4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003E204);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003E214);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003E224);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003E234);

INCLUDE_ASM("asm/jp/nonmatchings/main", EnterCriticalSection);

INCLUDE_ASM("asm/jp/nonmatchings/main", ExitCriticalSection);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetSp);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003E274);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003E2D4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003E2E4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003E2F4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003E390);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003E3C8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003E3F8);

INCLUDE_ASM("asm/jp/nonmatchings/main", ResetRCnt);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003E464);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003E600);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003E704);

INCLUDE_ASM("asm/jp/nonmatchings/main", Puts_A63);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003E734);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003E744);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003E754);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003E764);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003E774);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003E784);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003E794);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003E7A4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003E88C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003E8F0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003E954);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003EA08);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003EA44);

INCLUDE_ASM("asm/jp/nonmatchings/main", GsGetWorkBase);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003EA74);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003EAB4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003EB54);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003EE0C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003F128);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003F4F4);

INCLUDE_ASM("asm/jp/nonmatchings/main", ResetGraph);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003F678);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetGraphQueue);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003F778);

INCLUDE_ASM("asm/jp/nonmatchings/main", DrawSyncCallback);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003F7E8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003F880);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003F8E8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003FA04);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003FA94);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003FB2C);

INCLUDE_ASM("asm/jp/nonmatchings/main", StoreImage);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003FBEC);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003FCA4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003FD6C);

INCLUDE_ASM("asm/jp/nonmatchings/main", DrawPrim);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003FE74);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8003FEE4);

INCLUDE_ASM("asm/jp/nonmatchings/main", DrawOTagEnv);

INCLUDE_ASM("asm/jp/nonmatchings/main", GetDrawEnv);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800400B0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800405A8);

INCLUDE_ASM("asm/jp/nonmatchings/main", GetODE);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetTexWindow);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80040644);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetDrawOffset);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetPriority);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetDrawStp);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80040754);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetDrawEnv);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800409A0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80040C10);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80040C30);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80040CC8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80040D60);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80040D7C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80040DFC);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80040E14);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80040EF4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80041124);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80041360);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800415E0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80041604);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80041618);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80041658);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800416A0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800416D0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800416F4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800419A4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80041C04);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80041D54);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80041E90);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80041EC4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80042008);

INCLUDE_ASM("asm/jp/nonmatchings/main", LoadImage2);

INCLUDE_ASM("asm/jp/nonmatchings/main", StoreImage2);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80042280);

INCLUDE_ASM("asm/jp/nonmatchings/main", DrawOTag2);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800424C0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800424E8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80042514);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80042524);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80042534);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80042544);

INCLUDE_ASM("asm/jp/nonmatchings/main", OpenTMD);

INCLUDE_ASM("asm/jp/nonmatchings/main", ReadTMD);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80042890);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800429A8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80042B1C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80043DB4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80043DF4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80043E14);

INCLUDE_ASM("asm/jp/nonmatchings/main", TermPrim);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetPrimitiveSemiTrans);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetShadeTexFlag);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetPolyFT4);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetPolyG4);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetSprt8);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetSprt16);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetSpritePrimitive);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetTilePrimitive);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetLineF2);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80043FB4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80043FD4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80044004);

INCLUDE_ASM("asm/jp/nonmatchings/main", PCclose);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80044034);

INCLUDE_ASM("asm/jp/nonmatchings/main", Start);

INCLUDE_ASM("asm/jp/nonmatchings/main", __main);

INCLUDE_ASM("asm/jp/nonmatchings/main", __do_global_dtors);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800441D4);

INCLUDE_ASM("asm/jp/nonmatchings/main", PCinit);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800441F0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800442B0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800442C8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80044328);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80044338);

INCLUDE_ASM("asm/jp/nonmatchings/main", StartMemoryCardSystem);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800443EC);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetInitPadFlag);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80044424);

INCLUDE_ASM("asm/jp/nonmatchings/main", PAD_init);

INCLUDE_ASM("asm/jp/nonmatchings/main", InitPAD);

INCLUDE_ASM("asm/jp/nonmatchings/main", StartPAD);

INCLUDE_ASM("asm/jp/nonmatchings/main", StopPAD);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800445BC);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80044634);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8004466C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800446D4);

INCLUDE_ASM("asm/jp/nonmatchings/main", InitPAD2);

INCLUDE_ASM("asm/jp/nonmatchings/main", StartPAD2);

INCLUDE_ASM("asm/jp/nonmatchings/main", StopPAD2);

INCLUDE_ASM("asm/jp/nonmatchings/main", PAD_init2);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80044758);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80044768);

INCLUDE_ASM("asm/jp/nonmatchings/main", EnablePAD);

INCLUDE_ASM("asm/jp/nonmatchings/main", DisablePAD);

INCLUDE_ASM("asm/jp/nonmatchings/main", _patch_pad);

INCLUDE_ASM("asm/jp/nonmatchings/main", _remove_ChgclrPAD);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80044888);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80044898);

INCLUDE_ASM("asm/jp/nonmatchings/main", StopCARD2);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800448E4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80044928);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80044950);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800449E4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80044A54);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80044A88);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80044B08);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80044BF0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80044C68);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80044EE8);

INCLUDE_ASM("asm/jp/nonmatchings/main", _spu_FiDMA);

INCLUDE_ASM("asm/jp/nonmatchings/main", _spu_Fr_);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8004520C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8004548C);

INCLUDE_ASM("asm/jp/nonmatchings/main", _spu_Fr);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80045574);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800455B8);

INCLUDE_ASM("asm/jp/nonmatchings/main", _spu_FgetRXXa);

INCLUDE_ASM("asm/jp/nonmatchings/main", _spu_FsetPCR);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800456F0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80045718);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80045740);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetSpuDmaCallback);

INCLUDE_ASM("asm/jp/nonmatchings/main", SsUtReverbOff);

INCLUDE_ASM("asm/jp/nonmatchings/main", QuitSpu);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80045878);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800458D8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80045928);

INCLUDE_ASM("asm/jp/nonmatchings/main", _SpuIsInAllocateArea);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80045A78);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80045B08);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80045C48);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80045C68);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80045CA8);

INCLUDE_ASM("asm/jp/nonmatchings/main", _SpuCallback);

INCLUDE_ASM("asm/jp/nonmatchings/main", SpuRead);

INCLUDE_ASM("asm/jp/nonmatchings/main", SpuWriteWithCallbackCheck);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80045DD8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80045E38);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetSpuTransferCallback);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80045E98);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80045EB8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80046088);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80046558);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800466F8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80046708);

INCLUDE_ASM("asm/jp/nonmatchings/main", GetCurrentReverbMode);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80046748);

INCLUDE_ASM("asm/jp/nonmatchings/main", GsResetInterruptHandlers);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80046788);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800467A8);

INCLUDE_ASM("asm/jp/nonmatchings/main", GetVibrationDeviceType);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800468C0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800469B8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80046A8C);

INCLUDE_ASM("asm/jp/nonmatchings/main", QueueVibrationPlayback);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80046B6C);

INCLUDE_ASM("asm/jp/nonmatchings/main", SendVibrationCommand);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80046C08);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetupMovieIRQHandlers);

INCLUDE_ASM("asm/jp/nonmatchings/main", CheckAndHandleMovieInterrupt);

INCLUDE_ASM("asm/jp/nonmatchings/main", HandleMovieFrameInterrupt);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80046F44);

INCLUDE_ASM("asm/jp/nonmatchings/main", ResetInterruptHandlersAndTimers);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80047024);

INCLUDE_ASM("asm/jp/nonmatchings/main", BeginMovieFrameTransfer);

INCLUDE_ASM("asm/jp/nonmatchings/main", StepMovieFrameDecodePhase);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8004748C);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8004769C);

INCLUDE_ASM("asm/jp/nonmatchings/main", WaitForControllerReady);

INCLUDE_ASM("asm/jp/nonmatchings/main", WaitForControllerAckBit);

INCLUDE_ASM("asm/jp/nonmatchings/main", WriteVibrationData);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800479E4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800479F4);

INCLUDE_ASM("asm/jp/nonmatchings/main", ProcessMovieCommandState);

INCLUDE_ASM("asm/jp/nonmatchings/main", CalculateTotalMovieChunkSize);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetupMovieFrameProcessing);

INCLUDE_ASM("asm/jp/nonmatchings/main", HandleMovieFrameCommand);

INCLUDE_ASM("asm/jp/nonmatchings/main", ProcessMovieFrameStep);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetVibrationPlaybackState);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800482FC);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80048318);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800483E0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80048478);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800484CC);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetupMovieCommandGeneric);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_8004854C);

INCLUDE_ASM("asm/jp/nonmatchings/main", MovieCmd_SetupType3);

INCLUDE_ASM("asm/jp/nonmatchings/main", MovieCmd_SetupType2);

INCLUDE_ASM("asm/jp/nonmatchings/main", MovieCmd_SetupType4);

INCLUDE_ASM("asm/jp/nonmatchings/main", MovieCmd_Abort);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800485D8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80048620);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800486F8);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800487A4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80048830);

INCLUDE_ASM("asm/jp/nonmatchings/main", InitMovieIRQSystem);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80048D48);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80048DB0);

INCLUDE_ASM("asm/jp/nonmatchings/main", SaveAndClearMovieCommandCode);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80048EB4);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80048F70);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800491EC);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80049224);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80049248);

INCLUDE_ASM("asm/jp/nonmatchings/main", SetupMovieIRQFunctionPointers);

INCLUDE_ASM("asm/jp/nonmatchings/main", UpdateMoviePlaybackControlState);

INCLUDE_ASM("asm/jp/nonmatchings/main", HandleMoviePacketState);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80049600);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_800496E0);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80049718);

INCLUDE_ASM("asm/jp/nonmatchings/main", func_80049738);
