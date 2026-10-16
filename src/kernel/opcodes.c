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
extern u8* g_ScriptInstructionPointer;
extern char g_LogBuffer[];
extern char g_ActiveScriptLabel[];

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

void Cmd_setVariableByType(s32 type);
void ExecuteUnaryOpcode(s32 opcode);
void ExecuteEquationOpcode(s32 opcode);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", InitOpcodeHandlerTable);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", InitializeScriptInterpreter);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", ResetScriptInterpreterState);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", LoadPortraitLoopCutData);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", LoadPortraitTextGridData);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", SaveScriptGameState);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", ApplySaveGameState);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", UpdateScriptStateAndDebugInput);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_interpreterStep);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_handleScriptBlock);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_print_a);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", DecodePortraitAnimBlock);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_call);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_thread);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_bg2);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_kbg2);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_movie2);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_movieflash2);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_movieFstate);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_movieFframe);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_allmuisc);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_seloop);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_allSE);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_oneSE);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_allStream);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_setVariableByType);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", ExecuteUnaryOpcode);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", ExecuteEquationOpcode);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_ifv);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_ifs);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_ifs2);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_ifo);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_ifo2);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_ifc);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_ifc2);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_ifvar);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_face_a);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_facer_a);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_pset_a);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_mset_a);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_mwin);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_exec);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_enter);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_exit);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_pmove_a);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_facelight);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_faceEffect);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_din);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_dout);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_sjump);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_jsel);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_mdel_s);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_vardel_j);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_loaddict);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", LoadDictionaryData);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_watch);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_watch16);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_watchflag);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_getRandom);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", MatchNameExpression);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_newsel);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_getnews);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", ValidateScriptHeader);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", DecodeScriptOperand);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", GetTaiwaNoun);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", ReportSystemError);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", CopyScriptToRuntimeBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", InitTitleScreenAudio);

void ForceStopMusic(void) { AkaoSendCmd_F0_StopMusic(); }

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", LoadStoryScript);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", SetupDebugOptionMenu);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", PlaySingleSoundeffect);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", PlayConditionalSoundEffect);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", ResetPortraitSlotFade);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", MaybeStartTaiwaVibration);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", DispatchScriptOpcode);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", JumpOpcodeFuncViaTable);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_errorUnknownOpcode);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_wait);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", ResetPortraitState);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_mspeed);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_loadkanji);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_return);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_threadret);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_threadstop);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_bg);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_kbg);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_movie);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_movieflash);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_vibrateflash);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_movieF);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_movieF2);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_movieFstop);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_movieFblock);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_movieFloop);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_soundmode);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_music);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_musiccut);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_loadmusic);

void LoadMusic(s32 MusicId) { LoadByFileIdGroupId(MusicId, FILE_AUDIO, g_MusicBuffer, MUSIC_BUFFER_SIZE); }

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_loadwavemusic);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", LoadWaveMusic);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_channelMute);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_finale);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_se);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_sse);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_ve);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_vestop);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_seStop);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_secut);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_loadse);

void LoadSoundEffect(s32 SfxId) {
    LoadByFileIdGroupId(SfxId, FILE_AUDIO, g_SoundEffectBuffer, SOUND_EFFECT_BUFFFER_SIZE);
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_loadwaveSE);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", LoadAudioId);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_loadwaveStream);

void LoadAudioStream(s32 audioId) {
    LoadByFileIdGroupId(audioId, FILE_AUDIO, g_AudioStreamBuffer, AUDIO_STREAM_BUFFER_SIZE);
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_cdplay);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_if);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", ComputeMovementStep);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_effectB);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_seekF);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_seekB);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_backF);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_talk);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_ltalk);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_tset);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_byuu);

void Cmd_preDinXX(void) {
    g_NeedToResetFaceSlots = 1;
    g_FaceSlotResetState[0] = 1;
    Cmd_din();
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_dinbrainoff);

void Cmd_doutWithFaceSlotXX(void) {
    g_NeedToResetFaceSlots = 1;
    Cmd_dout();
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_nin);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_ninjump);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_nincall);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_ninwait);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_nout);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_end);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_bp);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_present);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_tagon);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_tagoff);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_brainon);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_brainoff);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_aurthor);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_place);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_date);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_time);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_chapter);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_chapterTitle);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_endTitle);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_scene);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_inputName);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_vibrateMode);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_menuMode);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_menuOpen);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_news);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_newsput);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", Cmd_newsquit);

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

void Cmd_setVariable(void) { Cmd_setVariableByType(*g_ScriptInstructionPointer++); }

void Cmd_shiftLeft(void) { ExecuteEquationOpcode(EQ_OP_SHIF_L); }

void Cmd_shiftRight(void) { ExecuteEquationOpcode(EQ_OP_SHIF_R); }

void Cmd_equal(void) { ExecuteEquationOpcode(EQ_OP_EQU); }

void Cmd_notEqual(void) { ExecuteEquationOpcode(EQ_OP_NOT_EUQ); }

void Cmd_lessThan(void) { ExecuteEquationOpcode(EQ_OP_LT); }

void Cmd_lessThanOrEqual(void) { ExecuteEquationOpcode(EQ_OP_LTEQ); }

void Cmd_greaterThan(void) { ExecuteEquationOpcode(EQ_OP_GT); }

void Cmd_graterThanOrEqualTo(void) { ExecuteEquationOpcode(EQ_OP_GTEQ); }

s32 ReadScript16bitBE(void) {
    u32 b1 = *g_ScriptInstructionPointer++;
    u32 b2 = *g_ScriptInstructionPointer++;
    return b2 | (b1 << 8);
}

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", ReportError);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", DoDebugOptionMenu);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", DrawGlobalInspectorList);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", PrintScriptSystemDebug);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", DrawWatchedScriptFlags);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", PrintScriptBasicDebug);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", ShowTaiwaDebugData);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", DrawFlagInspectorList);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", DbgPrintCallandJump);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", DrawScriptExecutionLog);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", DrawWatchDebugValues);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", DrawWatch16ValuesHex);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", DrawWatch16ValuesBinary);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", DbgScreenPrintBinary);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", PrintDebugBinaryGroupString);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", LogDecimalNumber);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", LogHexNumber);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", LogCommand);

extern char* strcat(char*, const char*);

void LogArgumentString(char* argumentString) { strcat(g_LogBuffer, argumentString); }

extern char* strcpy(char*, const char*);

void SetActiveScriptLabel(const char* label) { strcpy(g_ActiveScriptLabel, label); }

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", RecordCallLabel);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", ConvertIntToAscii);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", LookupTaiwaGrammarRule);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", MatchTaiwaVocabularyEntry);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", ParseTaiwaSentenceStructure);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", ValidateTaiwaPhraseLength);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", CheckTaiwaModifierFlags);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", IsTaiwaNounValid);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", LookupVerbConjugation);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", GetDictionaryByteField);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", ResetDialogueTrackingState);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", PreprocessScriptBlock);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", AdvanceScriptOperandPtr);

INCLUDE_ASM("asm/jp/nonmatchings/kernel/opcodes", ReadLE16FromScript);

void SkipNext8ScriptBytes(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        g_ScriptYprePtr.ptr++;
    }
}
