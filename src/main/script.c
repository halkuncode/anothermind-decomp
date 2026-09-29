#include "common.h"

INCLUDE_ASM("asm/jp/nonmatchings/main/script", InitOpcodeHandlerTable);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", InitializeScriptInterpreter);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", ResetFullGameRuntimeState_8001CA18);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", LoadPortraitLoopCutData);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", LoadPortraitTextGridData);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", func_8001D48C);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", ApplySaveGameState);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", UpdateScriptStateAndDebugInput);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_interpreterStep);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_handleScriptBlock);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_print_a);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", DecodePortraitAnimBlock);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_call);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_thread);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_bg2);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_kbg2);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_movie2);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_movieflash2);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_movieFstate);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_movieFframe);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_allmuisc);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_seloop);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_allSE);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_oneSE);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_allStream);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_setVariableByType);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", ExecuteUnaryOpcode);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", ExecuteEquationOpcode);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_ifv);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_ifs);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_ifs2);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_ifo);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_ifo2);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_ifc);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_ifc2);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_ifvar);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_face_a);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_facer_a);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_pset_a);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_mset_a);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_mwin);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_exec);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_enter);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_exit);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_pmove_a);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_facelight);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_faceEffect);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_din);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_dout);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_sjump);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_jsel);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_mdel_s);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_vardel_j);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_loaddict);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", LoadDictionaryData);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_watch);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_watch16);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_watchflag);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_getRandom);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", MatchNameExpression);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_newsel);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_getnews_80025CCC);

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

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_errorUnknownOpcode);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_wait);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", ResetPortraitState);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_mspeed);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_loadkanji);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_return);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_threadret);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_threadstop);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_bg);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_kbg);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_movie);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_movieflash);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_vibrateflash);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_movieF);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_movieF2);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_movieFstop);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_movieFblock);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_movieFloop);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_soundmode);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_music);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_musiccut);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_loadmusic);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", LoadMusic);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_loadwavemusic);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", LoadWaveMusic);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_channelMute);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_finale);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_se);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_sse);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_ve);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_vestop);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_seStop);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_secut);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_loadse);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", LoadSoundEffect);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_loadwaveSE);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", LoadAudioId);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_loadwaveStream);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", LoadAudioStream);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_cdplay);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_if);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", ComputeMovementStep);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_effectB);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_seekF);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_seekB);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_backF);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_talk);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_ltalk);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_tset);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_byuu);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_preDinXX);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_dinbrainoff);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_doutWithFaceSlotXX);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_nin);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_ninjump);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_nincall);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_ninwait);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_nout);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_end);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_bp);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_present);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_tagon);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", func_80028FA4);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_brainon);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_brainoff);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_aurthor);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_place);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_date);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_time);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_chapter);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_chapterTitle);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_endTitle);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_scene);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_inputName);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_vibrateMode);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_menuMode);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_menuOpen);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_getnews_80029820);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_newsput);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_newsquit);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_logicalAnd);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_logicalOr);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_bitwiseAnd);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_bitwiseOr);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_bitwiseXor);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_logicalNot);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_negate);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_add);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_subtract);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_multiply);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_divide);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_modulo);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_setVariable);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_shiftLeft);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_shiftRight);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_equal);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_notEqual);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_lessThan);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_lessThanOrEqual);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_greaterThan);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_graterThanOrEqualTo);

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
