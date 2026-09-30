#ifndef AKAO_H
#define AKAO_H

#include "common.h"

#define AKAO_SFX_LEGATO 0x1

typedef struct AkaoChannel {
    /* 0x00 */ u8* akaoSequencePointer;
    /* 0x04 */ u8 pad04[0x98 - 0x04];
    /* 0x98 */ u16 portamentoSteps;
    /* 0x9A */ u16 sfxMask;
    /* 0x9C */ u8 pad9C[0x124 - 0x9C];
} AkaoChannel;

#endif
