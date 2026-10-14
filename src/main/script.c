#include "common.h"
#include "game.h"

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

#define MUSIC_BUFFER_SIZE 0x7000
#define SOUND_EFFECT_BUFFFER_SIZE 0x2000
#define AUDIO_STREAM_BUFFER_SIZE 0x10000

extern s8 g_NeedToResetFaceSlots;
extern s8 g_FaceSlotResetState[];
extern u8 g_SoundEffectBuffer[SOUND_EFFECT_BUFFFER_SIZE];
extern u8 g_MusicBuffer[MUSIC_BUFFER_SIZE];
extern u8 g_AudioStreamBuffer[AUDIO_STREAM_BUFFER_SIZE];

typedef struct {
    /* 0x00 */ u8 compilerMonth;
    /* 0x01 */ u8 compilerDay;
    /* 0x02 */ u8 compilerHour;
    /* 0x03 */ u8 compilerMin;
    /* 0x04 */ u16 flags;
    /* 0x06 */ u16 totalFileSize;
    /* 0x08 */ u16 labelCount;
} ZzsHeader; /* size = 0x0A */

typedef struct {
    /* 0x00 */ char wordStr[17];
    /* 0x11 */ u8 pos;
    /* 0x12 */ u16 semanticIds[2][10];
    /* 0x3A */ u8 semanticWts[2][10];
    /* 0x4E */ u8 flags4e[2];
    /* 0x50 */ u8 tailFlags[3];
    /* 0x53 */ u8 pad53;
    /* 0x54 */ u16 pad54;
} JDictEntry; /* size = 0x56 */

typedef struct {
    /* 0x00 */ char prefixStr[17];
    /* 0x11 */ u8 attr;
    /* 0x12 */ u16 nextNodes[10];
} MDictNode; /* size = 0x26 */

typedef struct {
    /* 0x00 */ char nameStr[10];
    /* 0x0A */ u16 entityIds[3][5];
    /* 0x28 */ u8 slotCounts[3];
    /* 0x2B */ u8 pad2B;
} NameEntity; /* size = 0x2C */

typedef struct {
    /* 0x00 */ char formRenyou[15];
    /* 0x0F */ char formMizen[15];
    /* 0x1E */ char formKatei[15];
    /* 0x2D */ char formMeirei[15];
} KatsuyouRule; /* size = 0x3C */

extern JDictEntry g_JDictEntries[];
extern MDictNode g_MDictNodes[];
extern NameEntity g_NameEntities[];
extern KatsuyouRule g_KatsuyouRules[];

typedef struct {
    /* 0x00 */ u16 dialogueScriptOffset;
    /* 0x02 */ u8 characterDialogueLineIndex;
    /* 0x03 */ u8 unk03;
} ScriptDialogueLine;

typedef struct {
    /* 0x00 */ u8* ptr;
    /* 0x04 */ u8* start;
    /* 0x08 */ u8* end;
    /* 0x0C */ u8 isExecuting;
    /* 0x0D */ u8 pad0D[3];
    /* 0x10 */ s32 memoryLimitEnd;
    /* 0x14 */ u8 command;
    /* 0x15 */ u8 pad15;
    /* 0x16 */ ScriptDialogueLine dialogueLines[20];
    /* 0x66 */ u16 activeTaiwaCharacterIds[3];
    /* 0x6C */ u8 taiwaCharacterCount;
    /* 0x6D */ u8 faceSlotResetState;
    /* 0x6E */ u16 pad6E;
    /* 0x70 */ u8* returnStack[10];
} ScriptYPre; /* size = 0x98 */

extern ScriptYPre g_ScriptYprePtr;

typedef struct {
    /* 0x00 */ u8 faceSlotId;
    /* 0x01 */ u8 pad01;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 msgBoxPosX;
    /* 0x06 */ s16 msgBoxPosY;
    /* 0x08 */ s16 msgBoxWidth;
    /* 0x0A */ s16 msgBoxHeight;
    /* 0x0C */ s16 poseId;
    /* 0x0E */ s16 poseVariant;
    /* 0x10 */ s16 faceId;
    /* 0x12 */ u8 facingDirection;
    /* 0x13 */ u8 blendMode;
    /* 0x14 */ u8 faceNeedsRedraw;
    /* 0x15 */ u8 windowWidth;
} ScriptCharacterSlot; /* size = 0x16 */

extern ScriptCharacterSlot g_CharacterSlotTable[];

typedef struct {
    /* 0x00 */ s32 characterId;
    /* 0x04 */ s16 speed;
    /* 0x06 */ s16 faceSlotId;
    /* 0x08 */ s32 startX;
    /* 0x0C */ s32 startY;
    /* 0x10 */ s32 targetX;
    /* 0x14 */ s32 targetY;
    /* 0x18 */ s32 xAccum;
    /* 0x1C */ s32 yAccum;
    /* 0x20 */ s32 stepX;
    /* 0x24 */ s32 stepY;
    /* 0x28 */ s32 currentX;
    /* 0x2C */ s32 currentY;
    /* 0x30 */ s32 waitCounter;
} ScriptPmoveState; /* size = 0x34 */

extern ScriptPmoveState g_PmoveState;

typedef struct {
    /* 0x00 */ u8 active;
    /* 0x01 */ u8 wasActive;
    /* 0x02 */ u8* entryPointer;
    /* 0x06 */ u8* currentPointer;
    /* 0x0A */ u8 canRun;
    /* 0x0B */ u8 backupJumpOpcodeTemp;
    /* 0x0C */ u8 needsInit;
    /* 0x0D */ u8 timer;
    /* 0x0E */ u8 waitCounter;
    /* 0x0F */ u8 backupPortraitStateTemp;
} ScriptThread; /* size = 0x10 */

typedef struct {
    /* 0x00 */ u8* instructionPtr;
    /* 0x04 */ u8 canAdvance;
    /* 0x05 */ u8 jumpOpcode;
    /* 0x06 */ u8 waitMovieFlag;
    /* 0x07 */ u8 portraitWait;
    /* 0x08 */ u8 autoAdvance;
    /* 0x09 */ u8 portraitState;
} ScriptSavedContext; /* size = 0x0A */

void ExecuteUnaryOpcode(s32 opcode);
void ExecuteEquationOpcode(s32 opcode);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", InitOpcodeHandlerTable);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", InitializeScriptInterpreter);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", ResetFullGameRuntimeState_8001CA18);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", LoadPortraitLoopCutData);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", LoadPortraitTextGridData);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", SaveScriptGameState);

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

INCLUDE_ASM("asm/jp/nonmatchings/main/script", ResetPortraitSlotFade);

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

void LoadMusic(s32 MusicId) { LoadByFileIdGroupId(MusicId, FILE_AUDIO, g_MusicBuffer, MUSIC_BUFFER_SIZE); }

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

void LoadSoundEffect(s32 SfxId) {
    LoadByFileIdGroupId(SfxId, FILE_AUDIO, g_SoundEffectBuffer, SOUND_EFFECT_BUFFFER_SIZE);
}

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_loadwaveSE);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", LoadAudioId);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_loadwaveStream);

void LoadAudioStream(s32 audioId) {
    LoadByFileIdGroupId(audioId, FILE_AUDIO, g_AudioStreamBuffer, AUDIO_STREAM_BUFFER_SIZE);
}

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

void Cmd_preDinXX(void) {
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

INCLUDE_ASM("asm/jp/nonmatchings/main/script", Cmd_tagoff);

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

INCLUDE_ASM("asm/jp/nonmatchings/main/script", LogHexNumber);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", LogCommand);

extern char g_LogBuffer[];
extern char* strcat(char*, const char*);

void LogArgumentString(char* argumentString) { strcat(g_LogBuffer, argumentString); }

extern char g_ActiveScriptLabel[];
extern char* strcpy(char*, const char*);

void SetActiveScriptLabel(const char* label) { strcpy(g_ActiveScriptLabel, label); }

INCLUDE_ASM("asm/jp/nonmatchings/main/script", RecordCallLabel);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", ConvertIntToAscii);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", LookupTaiwaGrammarRule);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", MatchTaiwaVocabularyEntry);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", ParseTaiwaSentenceStructure);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", ValidateTaiwaPhraseLength);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", CheckTaiwaModifierFlags);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", IsTaiwaNounValid);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", LookupVerbConjugation);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", GetDictionaryByteField);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", ResetDialogueTrackingState);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", PreprocessScriptBlock);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", AdvanceScriptOperandPtr);

INCLUDE_ASM("asm/jp/nonmatchings/main/script", ReadLE16FromScript);

void SkipNext8ScriptBytes(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        g_ScriptYprePtr.ptr++;
    }
}
