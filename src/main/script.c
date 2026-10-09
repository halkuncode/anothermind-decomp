//! CC1=2.8.0 G=8
#include "common.h"

typedef enum {
    EQ_OP_LOGIC_AND = 0x00,
    EQ_OP_LOGIC_OR = 0x01,
    EQ_OP_BIT_AND = 0x02,
    EQ_OP_BIT_OR = 0x03,
    EQ_OP_BIT_XOR = 0x04,
    EQ_OP_LOGIC_NOT = 0x05,
    EQ_OP_NEG = 0x06,
    EQ_OP_ADD = 0x07,
    EQ_OP_SUB = 0x08,
    EQ_OP_MUL = 0x09,
    EQ_OP_NOT_EUQ = 0x10,
    EQ_OP_DIV = 0x0A,
    EQ_OP_MOD = 0x0B,
    EQ_OP_SHIF_L = 0x0D,
    EQ_OP_SHIF_R = 0x0E,
    EQ_OP_EQU = 0x0F,
    EQ_OP_LT = 0x11,
    EQ_OP_LTEQ = 0x12,
    EQ_OP_GT = 0x13,
    EQ_OP_GTEQ = 0x14,

} EqOpcodes;

extern s8 g_NeedToResetFaceSlots;
extern s8 g_FaceSlotResetState[];

void ExecuteUnaryOpcode(s32 opcode);
void ExecuteEquationOpcode(s32 opcode);

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

void ForceStopMusic(void) { AkaoSendCmd_F0_StopMusic(); }

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

#ifndef INCLIDE_MAP
INCLUDE_ASM("asm/jp/nonmatchings/main/script", LoadAudioStream);
#else
extern s32 D_800A05B8;

void LoadAudioStream(void)
{
    LoadByFileIdGroupId(8, &D_800A05B8, 0x10000);
}
#endif
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




void Cmd_preDinXX(void)
{
    g_NeedToResetFaceSlots = 1;
    g_FaceSlotResetState[0] = 1;
    Cmd_din();
}

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_dinbrainoff);

void Cmd_doutWithFaceSlotXX(void) {
    g_NeedToResetFaceSlots = 1;
    Cmd_dout();
}

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

void Cmd_logicalAnd(void) { ExecuteEquationOpcode(EQ_OP_LOGIC_AND); }

void Cmd_logicalOr(void) { ExecuteEquationOpcode(EQ_OP_LOGIC_OR); }

void Cmd_bitwiseAnd(void) { ExecuteEquationOpcode(EQ_OP_BIT_AND); }

void Cmd_bitwiseOr(void) { ExecuteEquationOpcode(EQ_OP_BIT_OR); }

void Cmd_bitwiseXor(void) { ExecuteEquationOpcode(EQ_OP_BIT_XOR); }

void Cmd_logicalNot(void) { ExecuteUnaryOpcode(EQ_OP_LOGIC_NOT); }

void Cmd_negate(void) { ExecuteUnaryOpcode(EQ_OP_NEG); }

void Cmd_add(void) { ExecuteEquationOpcode(EQ_OP_ADD); }

void Cmd_subtract(void) { ExecuteEquationOpcode(EQ_OP_SUB); }

void Cmd_multiply(void) { ExecuteEquationOpcode(EQ_OP_MUL); }

void Cmd_divide(void) { ExecuteEquationOpcode(EQ_OP_DIV); }

void Cmd_modulo(void) { ExecuteEquationOpcode(EQ_OP_MOD); }

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_setVariable);

void Cmd_shiftLeft(void) { ExecuteEquationOpcode(EQ_OP_SHIF_L); }

void Cmd_shiftRight(void) { ExecuteEquationOpcode(EQ_OP_SHIF_R); }

void Cmd_equal(void) { ExecuteEquationOpcode(EQ_OP_EQU); }

void Cmd_notEqual(void) { ExecuteEquationOpcode(EQ_OP_NOT_EUQ); }

void Cmd_lessThan(void) { ExecuteEquationOpcode(EQ_OP_LT); }

void Cmd_lessThanOrEqual(void) { ExecuteEquationOpcode(EQ_OP_LTEQ); }

void Cmd_greaterThan(void) { ExecuteEquationOpcode(EQ_OP_GT); }

void Cmd_graterThanOrEqualTo(void) { ExecuteEquationOpcode(EQ_OP_GTEQ); }

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

extern char g_LogBuffer[];
extern char* strcat(char*, const char*);

void LogArgumentString(char* argumentString) { strcat(g_LogBuffer, argumentString); }

extern char g_ActiveScriptLabel[];
extern char* strcpy(char*, const char*);

void SetActiveScriptLabel(const char* label) { strcpy(g_ActiveScriptLabel, label); }

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
