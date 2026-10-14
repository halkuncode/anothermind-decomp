#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "common.h"

// Note 'volatile' is allowed here as a deviation from
// STYLE.md due to the high degree of timing needed
// for the root counter.
#define RCNT_REG(addr) (*(volatile u16*)(addr))
#define RCNT2_COUNT 0x1F801120
#define RCNT2_MODE 0x1F801124
#define RCNT2_TARGET 0x1F801128

typedef enum ControllerCommand {
    CONTROLLER_POLL = 0x42,
    CONTROLLER_CONFIG_MODE = 0x43,
    CONTROLLER_MODE_SELECT = 0x44,
    CONTROLLER_QUERY_STATUS = 0x45,
    CONTROLLER_QUERY_ACTUATOR = 0x46,
    CONTROLLER_QUERY_PARAM = 0x47,
    CONTROLLER_ABORT = 0x4B,
    CONTROLLER_QUERY_MAP = 0x4C,
    CONTROLLER_RUMBLE_MAP = 0x4D,
} ControllerCommand;

typedef struct ControllerState {
    /* 0x00 */ u8 pad0[0x20];
    /* 0x20 */ u8* rumbleMap;
    /* 0x24 */ u8 configParam;
    /* 0x25 */ u8 pad25[3];
    /* 0x28 */ u8* vibrationBuffer;
    /* 0x2C */ u8* configBuffer;
    /* 0x30 */ u8 pad30[4];
    /* 0x34 */ u8 vibrationBufferLength;
    /* 0x35 */ u8 pad35;
    /* 0x36 */ u8 configBufferLength;
    /* 0x37 */ u8 configMode;
    /* 0x38 */ u8 pad38[0xF0 - 0x38];
} ControllerState;

typedef struct ControllerAttribute {
    /* 0x00 */ u8 pad0[0x37];
    /* 0x37 */ u8 currCmdType;
    /* 0x38 */ u8 savedCmdType;
} ControllerAttribute;

extern s32 g_ControllerTimeoutStartTime;
extern s32 g_ControllerTimeoutDuration;
extern s32 g_ControllerReadyFlag;
extern ControllerState g_Controllers[];

void BIOS_bzero(void* ptr, s32 size);
#define bzero(ptr, size) BIOS_bzero((ptr), (size))

// Assembly trampoline stub for BIOS bzero syscall (A0 table function 0x28)
#define DEFINE_BIOS_BZERO()                                                                                            \
    void __maspsx_include_asm_hack_BIOS_bzero() {                                                                      \
        __asm__(".text # maspsx-keep\n"                                                                                \
                "\t.align\t2 # maspsx-keep\n"                                                                          \
                "\t.globl\tBIOS_bzero # maspsx-keep\n"                                                                 \
                "BIOS_bzero: # maspsx-keep\n"                                                                          \
                "\t.set\tnoreorder # maspsx-keep\n"                                                                    \
                "\t.set\tnoat # maspsx-keep\n"                                                                         \
                "\taddiu\t$10,$0,0xA0 # maspsx-keep\n"                                                                 \
                "\tjr\t$10 # maspsx-keep\n"                                                                            \
                "\taddiu\t$9,$0,0x28 # maspsx-keep\n"                                                                  \
                "\tnop # maspsx-keep\n"                                                                                \
                "\t.set\treorder # maspsx-keep\n"                                                                      \
                "\t.set\tat # maspsx-keep\n");                                                                         \
    }

#endif // CONTROLLER_H


