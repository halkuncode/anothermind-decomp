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

typedef struct ControllerPacket {
    /* 0x00 */ u8 status;
    /* 0x01 */ u8 deviceId;
    /* 0x02 */ u8 buttonLo;
    /* 0x03 */ u8 buttonHi;
    /* 0x04 */ u8 rightX;
    /* 0x05 */ u8 rightY;
    /* 0x06 */ u8 leftX;
    /* 0x07 */ u8 leftY;
} ControllerPacket;

typedef struct ControllerState {
    /* 0x00 */ u8 pad0[0x0C];
    /* 0x0C */ s32 status;
    /* 0x10 */ struct ControllerState* self;
    /* 0x14 */ u8 pad14[0x0C];
    /* 0x20 */ u8* rumbleMap;
    /* 0x24 */ u8 configParam;
    /* 0x25 */ u8 pad25[3];
    /* 0x28 */ u8* vibrationBuffer;
    /* 0x2C */ u8* configBuffer;
    /* 0x30 */ u8* readBuffer;
    /* 0x34 */ u8 vibrationBufferLength;
    /* 0x35 */ u8 pad35;
    /* 0x36 */ u8 configBufferLength;
    /* 0x37 */ u8 configMode;
    /* 0x38 */ u8 savedCmdType;
    /* 0x39 */ u8 pad39[3];
    /* 0x3C */ u8* packetBuffer1;
    /* 0x40 */ u8* packetBuffer0;
    /* 0x44 */ u8 pad44[2];
    /* 0x46 */ u8 cmdState;
    /* 0x47 */ u8 pad47[0x53 - 0x47];
    /* 0x53 */ u8 cmdPhase;
    /* 0x54 */ u8 pad54[0x5D - 0x54];
    /* 0x5D */ u8 buttonData[6];
    /* 0x63 */ u8 pad63[0xF0 - 0x63];
} ControllerState;

typedef struct ControllerAttribute {
    /* 0x00 */ u8 pad0[0x37];
    /* 0x37 */ u8 currCmdType;
    /* 0x38 */ u8 savedCmdType;
} ControllerAttribute;

typedef struct ControllerIRQHandler {
    /* 0x00 */ struct ControllerIRQHandler* next;
    /* 0x04 */ void (*mainHandler)(void);
    /* 0x08 */ s32 (*edgeHandler)(void);
    /* 0x0C */ s32 status;
} ControllerIRQHandler;

typedef struct ControllerCallbacks {
    /* 0x00 */ void (*onPacketProcessed)(void);
    /* 0x04 */ void (*flushBuffer)(void);
    /* 0x08 */ void (*onBufferFilled)(void);
    /* 0x0C */ void (*onPacketReady)(void);
    /* 0x10 */ void (*onTransferComplete)(void);
    /* 0x14 */ ControllerState* (*getActiveState)(s32 port);
    /* 0x18 */ void (*controlHandler)(void);
    /* 0x1C */ s32 isVibrationBusy;
    /* 0x20 */ void (*packetHandler)(void);
    /* 0x24 */ void (*getPlaybackStatus)(void*);
    /* 0x28 */ void (*irqHandler)(void);
} ControllerCallbacks;

extern s32 g_ControllerTimeoutStartTime;
extern s32 g_ControllerTimeoutDuration;
extern s32 g_ControllerReadyFlag;
extern ControllerState g_Controllers[];
extern ControllerIRQHandler g_ControllerIRQHandlerStruct;
extern u8 g_ControllerPort1Buffer[];
extern u8 g_ControllerPort2Buffer[];
extern u8 g_ControllerPacketBuffer0[];
extern u8 g_ControllerPacketBuffer1[];

void BIOS_bzero(void* ptr, s32 size);
#define bzero(ptr, size) BIOS_bzero((ptr), (size))

#endif // CONTROLLER_H
