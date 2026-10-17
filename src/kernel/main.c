#include "common.h"
#include <libetc.h>
#include <libgpu.h>
#include <libsnd.h>

typedef struct {
    /* 0x00 */ DRAWENV draw;
    /* 0x5C */ DISPENV disp;
} IssueDB; // size:0x70

const char s_BuildupDatePrefix[] = "Buildup:  199";
const char s_PushSelectPrompt[] = "\n\n\n\n\n\n\n           Push Select";
const char s_UnpackErrNoAmpackData[] = "Unpack Err:  no Ampack data";
const char s_UnpackDebugHeader[] = "-----Unpack Debug -------\n";
const char s_DebugDummyStringA[76] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
const char s_ManoNameCount[] = "mano name cnt= ";
const char s_HitomiNameCount[] = "\nhitomi name cnt= ";
const char s_UnpackResultLabel[] = "unpack =";
extern char g_StrBuildupUndefine[];
extern u32 g_ScriptBuildTimestamp;
extern char g_AsciiConversionTemp1[];
extern char g_StrSlash[];
extern char g_StrSpace[];
extern char g_StrColon[];
extern char g_StrNewline[];
extern char g_StrFourNewlines[];
extern char g_StrDataEquals[];
extern char g_StrDebugNewline[];
extern char g_StrEndNewline[];
extern s32 g_RawControllerInputHigh[];
extern s32 g_InputTransitionMask2P[];
extern s32 g_DebugLockState; //!< Global debug lockout state flag.
extern char g_DebugStringBuf[];
extern u8 g_LzssWindow[];

extern void DoGame(void);
extern void InitNameEntryScreen(s32);
extern s32 GetHeroEnteredNameLength(s32);
extern s32 GetRawControllerInput(s32);
extern void ResetVibrationSystem(void);
extern void UpdateVibrationAndInput(void);
extern void DisplayPadDebugPanel(void);
extern void DisplayChapterTitle(s32);
extern void ShowSquaresoftLogo(void);
extern void LoadCdPosTablefromCd(void);
extern s32 LoadByFileIdGroupId(s32, s32, void*, s32);
extern s32 IsDebugDisabled(void);
extern void UpdateCdTransferState(void);
extern void UpdateMoviePlaybackFrame(void);
extern void DisplayCdFileDebugStatus(void);
extern void DisplayMovieDebugPanel(void);
extern void ResetMovieDecoderState(void);
extern void ResetCdTransferReadyFlag(void);
extern void DisplayCdControlStatusToDebugScreen(void);
extern char* strcat(char*, const char*);
extern void DbgScreenPrintInt(s32);
extern void Load8x8DebugFont(void);
extern void DbgScreenPrintString(const char*);

void LockoutDebug(s32);
s32 IntToAscii(s32 value, char* buffer, s32 radix);
void ReportIssue(const char* msg0, const char* msg1, const char* msg2, const char* msg3, const char* msg4);
void DecompressLZSS(u8* source, u8* destination);
s32 ReadLittleEndian32(u8* data);

/**
 * @brief Aborts program execution immediately.
 *
 * Triggers a hardware breakpoint (MIPS break instruction) to halt execution
 * and signal an unrecoverable abnormal termination.
 */
void abort(void) { M2C_BREAK(1); }

int main(void) {
    StopCallback();
    ResetCallback();
    ResetGraph(0);
    SsUtReverbOff();
    DoGame();
    while (1)
        ;
}

void ResetToReleaseMode(void) {
    LockoutDebug(0);
    ResetCdTransferReadyFlag();
    LoadCdPosTablefromCd();
    if (IsDebugDisabled() == -1) {
        ShowSquaresoftLogo();
        LockoutDebug(1);
    }
    ResetMovieDecoderState();
    ResetVibrationSystem();
}

void UpdateSystemPerFrame(void) {
    UpdateCdTransferState();
    UpdateMoviePlaybackFrame();
    UpdateVibrationAndInput();
}

void DisplaySystemDebugPanel(void) {
    DisplayCdControlStatusToDebugScreen();
    DisplayCdFileDebugStatus();
    DisplayMovieDebugPanel();
    DisplayPadDebugPanel();
}

s32 GetDebugLockState(void) { return g_DebugLockState; }

void LockoutDebug(s32 state) { g_DebugLockState = state; }

char* GetDebugScriptBuildDateString(void) {
    char tempBuffer[8];
    char* result;
    u32 timestampShifted;
    u32 year;
    u32 month;
    u32 day;
    u32 hour;
    u32 minute;
    u32 second;

    __builtin_memcpy(tempBuffer, g_AsciiConversionTemp1, 8);
    if (!IsDebugDisabled()) {
        result = g_StrBuildupUndefine;
    } else {
        second = g_ScriptBuildTimestamp;
        timestampShifted = (second >> 5) & 0x07FFFFFF;
        year = (timestampShifted >> 20) % 10;
        __builtin_memcpy(g_DebugStringBuf, s_BuildupDatePrefix, 14);
        second &= 0xF;
        minute = timestampShifted & 0x3F;
        hour = (timestampShifted >> 6) & 0x1F;
        day = (timestampShifted >> 11) & 0x1F;
        month = (timestampShifted >> 16) & 0xF;

        IntToAscii(year, tempBuffer, 16);
        strcat(g_DebugStringBuf, tempBuffer);
        strcat(g_DebugStringBuf, g_StrSlash);
        IntToAscii(month, tempBuffer, 10);
        strcat(g_DebugStringBuf, tempBuffer);
        strcat(g_DebugStringBuf, g_StrSlash);
        IntToAscii(day, tempBuffer, 10);
        strcat(g_DebugStringBuf, tempBuffer);
        strcat(g_DebugStringBuf, g_StrSpace);
        IntToAscii(hour, tempBuffer, 10);
        strcat(g_DebugStringBuf, tempBuffer);
        strcat(g_DebugStringBuf, g_StrColon);
        IntToAscii(minute, tempBuffer, 10);
        strcat(g_DebugStringBuf, tempBuffer);
        strcat(g_DebugStringBuf, g_StrColon);
        IntToAscii(second, tempBuffer, 10);
        strcat(g_DebugStringBuf, tempBuffer);
        strcat(g_DebugStringBuf, g_StrNewline);
        result = g_DebugStringBuf;
    }
    return result;
}

s32 IntToAscii(s32 value, char* buffer, s32 radix) {
    u8 digits[20];
    s32 count;
    s32 length;

    if (value < 0) {
        value = -value;
        *buffer++ = '-';
    }
    count = 0;
    length = 0;
    while (value) {
        digits[count++] = value % radix;
        value /= radix;
        length++;
    }
    if (!count) {
        digits[0] = 0;
        count = 1;
    }
    buffer[count] = '\0';
    while (count > 0) {
        if (digits[count - 1] < 10) {
            *buffer = digits[count - 1] + '0';
        } else {
            *buffer = digits[count - 1] + '7';
        }
        count--;
        buffer++;
    }
    return length;
}

void ReportIssue(const char* msg0, const char* msg1, const char* msg2, const char* msg3, const char* msg4) {
    IssueDB issueBuffers[2];
    s32 unusedPad[2];
    IssueDB* currentBuffer;
    s32 selectReleased = 0;

    SetDefDrawEnv(&issueBuffers[0].draw, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    SetDefDrawEnv(&issueBuffers[1].draw, 0, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
    SetDefDispEnv(&issueBuffers[0].disp, 0, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
    SetDefDispEnv(&issueBuffers[1].disp, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    FntLoad(960, 0);
    SetDumpFnt(FntOpen(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 1, 512));
    SetDispMask(1);

    while (1) {
        if (!(GetRawControllerInput(1) & PADselect)) {
            selectReleased = 1;
        }
        if (selectReleased && (GetRawControllerInput(1) & PADselect)) {
            Load8x8DebugFont();
            break;
        }
        currentBuffer = (currentBuffer == issueBuffers) ? &issueBuffers[1] : &issueBuffers[0];
        FntPrint(g_StrFourNewlines);
        if (msg0) {
            FntPrint(msg0);
        }
        if (msg1) {
            FntPrint(msg1);
        }
        if (msg2) {
            FntPrint(msg2);
        }
        if (msg3) {
            FntPrint(msg3);
        }
        if (msg4) {
            FntPrint(msg4);
        }
        if (!(VSync(-1) & 0x20)) {
            FntPrint(s_PushSelectPrompt);
        }
        FntFlush(-1);
        PutDispEnv(&currentBuffer->disp);
        PutDrawEnv(&currentBuffer->draw);
        DrawSync(0);
        VSync(0);
    }
}

void UnpackAmpackArchiveData(u8* src, u8* dst) {
    char tempBuffer[64];
    s32 unpackedSize;
    u8* bitstreamPtr;
    s32 bitPos;
    s32 outIdx;
    u8 codeLen;
    s32 tableBitPos;
    s32 symbol;
    u8 bitIdx;
    s32 maxSym;

    unpackedSize = ReadLittleEndian32(src + 1);
    bitstreamPtr = src + ReadLittleEndian32(src + 5);
    bitPos = 0;
    for (outIdx = 0; unpackedSize != outIdx; outIdx++) {
        for (codeLen = 1;; codeLen++) {
            tableBitPos = 0;
            IntToAscii(codeLen, tempBuffer, 10);
            for (symbol = 0; symbol != (maxSym = 0x100); symbol++) {
                if (codeLen == src[symbol + 9]) {
                    for (bitIdx = 0; bitIdx != codeLen; bitIdx++) {
                        if (((src[((tableBitPos + bitIdx) / 8) + 0x109] << ((tableBitPos + bitIdx) & 7)) & 0x80) !=
                            ((bitstreamPtr[(bitPos + bitIdx) / 8] << ((bitPos + bitIdx) & 7)) & 0x80)) {
                            goto next_sym;
                        }
                    }
                    dst[outIdx] = symbol;
                    bitPos += codeLen;
                    goto next_byte;
                }
            next_sym:
                tableBitPos += (maxSym = src[symbol + 9]);
            }
        }
    next_byte:;
    }
}

void DecompressLZSS(u8* source, u8* destination) {
    s32 i;
    s32 j;
    s32 k;
    s32 windowIndex;
    u32 byteValue;
    u32 flags;
    s32 size;
    s32 bytesRead;

    bytesRead = 0;
    source += 2;
    size = ReadLittleEndian32(source) - 6;
    source += 4;
    for (i = 0; i < LZSS_WINDOW_INIT_INDEX; i++) {
        g_LzssWindow[i] = 0;
    }
    windowIndex = LZSS_WINDOW_INIT_INDEX;
    flags = 0;
    for (;;) {
        if (!((flags >>= 1) & 0x100)) {
            byteValue = *source++;
            if (++bytesRead == size + 1) {
                break;
            }
            flags = byteValue | 0xFF00;
        }
        if (flags & 1) {
            byteValue = *source++;
            if (++bytesRead == size + 1) {
                break;
            }
            *destination++ = byteValue;
            g_LzssWindow[windowIndex++] = byteValue;
            windowIndex &= LZSS_WINDOW_MASK;
        } else {
            i = *source++;
            if (++bytesRead == size + 1) {
                break;
            }
            j = *source++;
            if (++bytesRead == size + 1) {
                break;
            }
            i |= (j & 0xF0) << 4;
            j = (j & 0x0F) + 2;
            for (k = 0; k <= j; k++) {
                byteValue = g_LzssWindow[(i + k) & LZSS_WINDOW_MASK];
                *destination++ = byteValue;
                g_LzssWindow[windowIndex++] = byteValue;
                windowIndex &= LZSS_WINDOW_MASK;
            }
        }
    }
}

void DebugUnpackAmpack(void) {
    s32 buffer1[250];
    s32 buffer2[250];

    DbgScreenPrintString(s_UnpackDebugHeader);
    if (g_RawControllerInputHigh[0] & 0x80) {
        InitNameEntryScreen(1);
    }
    SCHEDULE_BARRIER();
    if (g_InputTransitionMask2P[0] & 0x10) {
        if (DEBUG_UNPACK_SRC_ADDR[0] == AMPACK_MAGIC_0) {
            if (DEBUG_UNPACK_SRC_ADDR[1] == AMPACK_MAGIC_1) {
                DecompressLZSS(DEBUG_UNPACK_SRC_ADDR, PROGDATA_LOAD_ADDR);
            } else {
                ReportIssue(s_UnpackErrNoAmpackData, g_StrDataEquals, 0, 0, 0);
            }
        } else {
            ReportIssue(s_UnpackErrNoAmpackData, 0, 0, 0, 0);
        }
    }
    SCHEDULE_BARRIER();
    if (g_InputTransitionMask2P[0] & 0x40) {
        __builtin_memcpy(buffer2, s_DebugDummyStringA, 73);
    }
    if (g_InputTransitionMask2P[0] & 0x8) {
        DisplayChapterTitle(2);
    }
    DbgScreenPrintString(s_ManoNameCount);
    DbgScreenPrintInt(GetHeroEnteredNameLength(2));
    DbgScreenPrintString(s_HitomiNameCount);
    DbgScreenPrintInt(GetHeroEnteredNameLength(4));
    DbgScreenPrintString(g_StrDebugNewline);
    DbgScreenPrintString(s_UnpackResultLabel);
    DbgScreenPrintString((char*)buffer2);
    DbgScreenPrintString(g_StrEndNewline);
    DbgScreenPrintString(g_StrDebugNewline);
}

void CheckAndUnpackAmpack(u8* source, u8* destination) {
    if (source[0] == AMPACK_MAGIC_0) {
        if (source[1] == AMPACK_MAGIC_1) {
            DecompressLZSS(source, destination);
        } else {
            ReportIssue(s_UnpackErrNoAmpackData, g_StrDataEquals, 0, 0, 0);
        }
    } else {
        ReportIssue(s_UnpackErrNoAmpackData, 0, 0, 0, 0);
    }
}

s32 ReadLittleEndian32(u8* data) {
    u32 result = data[0];
    result += data[1] << 8;
    result += data[2] << 16;
    result += data[3] << 24;
    return result;
}

void LoadProgdata(s32 fileId, s32 groupId) {
    LoadByFileIdGroupId(fileId, groupId, PROGDATA_LOAD_ADDR, PROGDATA_LOAD_MAX_SIZE);
    if (PROGDATA_LOAD_ADDR[0] == AMPACK_MAGIC_0) {
        if (PROGDATA_LOAD_ADDR[1] == AMPACK_MAGIC_1) {
            DecompressLZSS(PROGDATA_LOAD_ADDR, PROGDATA_UNPACK_ADDR);
        } else {
            ReportIssue(s_UnpackErrNoAmpackData, g_StrDataEquals, 0, 0, 0);
        }
    } else {
        ReportIssue(s_UnpackErrNoAmpackData, 0, 0, 0, 0);
    }
}
