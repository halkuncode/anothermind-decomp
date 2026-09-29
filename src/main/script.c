#include "common.h"

INCLUDE_ASM("asm/jp/nonmatchings/main/script", InitOpcodeHandlerTable);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", InitializeScriptInterpreter);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", ResetFullGameRuntimeState_8001CA18);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", LoadPortraitLoopCutData);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", LoadPortraitTextGridData);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", func_8001D48C);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", ApplySaveGameState);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", UpdateScriptStateAndDebugInput);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_interpreterStep);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_handleScriptBlock);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_print_a);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", DecodePortraitAnimBlock);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_call);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_thread);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_bg2);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_kbg2);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_movie2);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_movieflash2);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_movieFstate);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_movieFframe);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_allmuisc);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_seloop);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_allSE);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_oneSE);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_allStream);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_setVariableByType);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", ExecuteUnaryOpcode);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", ExecuteEquationOpcode);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_ifv);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_ifs);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_ifs2);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_ifo);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_ifo2);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_ifc);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_ifc2);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_ifvar);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_face_a);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_facer_a);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_pset_a);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_mset_a);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_mwin);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_exec);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_enter);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_exit);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_pmove_a);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_facelight);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_faceEffect);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_din);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_dout);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_sjump);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_jsel);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_mdel_s);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_vardel_j);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_loaddict);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", LoadDictionaryData);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_watch);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_watch16);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_watchflag);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_getRandom);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", MatchNameExpression);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_newsel);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_getnews_80025CCC);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", ValidateScriptHeader);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", DecodeScriptOperand);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", GetTaiwaNoun);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", ReportSystemError);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", CopyScriptToRuntimeBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", InitTitleScreenAudio);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", ForceStopMusic);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", LoadStoryScript);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", SetupDebugOptionMenu);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", PlaySingleSoundeffect);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", PlayConditionalSoundEffect);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", func_80026CB0);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", MaybeStartTaiwaVibration);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", DispatchScriptOpcode);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", JumpOpcodeFuncViaTable);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_errorUnknownOpcode);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_wait);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", ResetPortraitState);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_mspeed);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_loadkanji);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_return);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_threadret);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_threadstop);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_bg);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_kbg);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_movie);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_movieflash);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_vibrateflash);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_movieF);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_movieF2);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_movieFstop);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_movieFblock);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_movieFloop);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_soundmode);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_music);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_musiccut);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_loadmusic);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", LoadMusic);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_loadwavemusic);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", LoadWaveMusic);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_channelMute);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_finale);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_se);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_sse);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_ve);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_vestop);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_seStop);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_secut);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_loadse);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", LoadSoundEffect);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_loadwaveSE);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", LoadAudioId);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_loadwaveStream);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", LoadAudioStream);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_cdplay);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_if);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", ComputeMovementStep);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_effectB);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_seekF);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_seekB);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_backF);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_talk);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_ltalk);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_tset);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_byuu);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_preDinXX);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_dinbrainoff);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_doutWithFaceSlotXX);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_nin);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_ninjump);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_nincall);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_ninwait);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_nout);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_end);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_bp);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_present);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_tagon);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", func_80028FA4);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_brainon);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_brainoff);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_aurthor);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_place);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_date);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_time);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_chapter);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_chapterTitle);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_endTitle);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_scene);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_inputName);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_vibrateMode);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_menuMode);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_menuOpen);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_getnews_80029820);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_newsput);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_newsquit);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_logicalAnd);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_logicalOr);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_bitwiseAnd);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_bitwiseOr);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_bitwiseXor);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_logicalNot);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_negate);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_add);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_subtract);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_multiply);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_divide);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_modulo);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_setVariable);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_shiftLeft);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_shiftRight);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_equal);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_notEqual);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_lessThan);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_lessThanOrEqual);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_greaterThan);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Func_graterThanOrEqualTo);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", ReadScript16bitBE);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", ReportError);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", DoDebugOptionMenu);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", DrawGlobalInspectorList);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", PrintScriptSystemDebug);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", DrawWatchedScriptFlags);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", PrintScriptBasicDebug);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", ShowTaiwaDebugData);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", DrawFlagInspectorList);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", DbgPrintCallandJump);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", DrawScriptExecutionLog);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", DrawWatchDebugValues);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", DrawWatch16ValuesHex);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", DrawWatch16ValuesBinary);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", DbgScreenPrintBinary);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", PrintDebugBinaryGroupString);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", LogDecimalNumber);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", func_8002B494);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", LogCommand);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", LogArgumentString);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", SetActiveScriptLabel);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", RecordCallLabel);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", ConvertIntToAscii);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", func_8002B680);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", func_8002BA98);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", func_8002BEF8);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", func_8002C3CC);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", func_8002C5D8);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", func_8002C6BC);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", func_8002C70C);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", func_8002C7FC);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", ResetDialogueTrackingState);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", PreprocessScriptBlock);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", AdvanceScriptOperandPtr);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", ReadLE16FromScript);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", SkipNext8ScriptBytes);
