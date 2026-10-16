#include "common.h"

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", GsGetAndClearControllerReadyFlag);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", GsResetInterruptHandlers);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", GsRemoveInterruptHandlers);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", Controller_GetReverbMode);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", GetVibrationDeviceType);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", CheckVibrationPortMode);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", InitVibrationPlaybackPacket);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", SendVibrationDataPacket);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", QueueVibrationPlayback);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", SetupControllerVibrationIRQHandlers);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", SendVibrationCommand);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", CheckAndHandleControllerAuxInterrupt);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", SetupControllerIRQHandlers);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", CheckAndHandleControllerInterrupt);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", HandleControllerFrameInterrupt);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", GetAndClearControllerReadyFlag);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", ResetInterruptHandlersAndTimers);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", RemoveInterruptHandlersAndTimers);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", BeginControllerTransfer);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", StepControllerTransferPhase);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", PollControllerTransferStatus);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", WaitControllerAckPulse);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", WaitForControllerReady);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", WaitForControllerAckBit);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", WriteVibrationData);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", SetControllerConfig);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", ProcessControllerCommandState);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", ProcessControllerPacketState);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", CalculateControllerPacketLength);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", SetupControllerPacketHandlers);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", HandleControllerPacketCommand);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", ProcessControllerPacketStep);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", SetVibrationPlaybackState);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", SetControllerRumbleMap);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", ProcessControllerFrameStep);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", SetVibrationMotorState);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", SetupControllerCommandGeneric);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", ControllerCmd_SetupType1);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", SetControllerConfigMode);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", SetControllerQueryStatus);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", SetControllerQueryMap);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", SetControllerQueryActuator);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", SetControllerQueryParam);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", SetControllerAbort);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", ControllerCmd_SetupType3);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", ControllerCmd_SetupType2);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", ControllerCmd_SetupType4);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", ControllerCmd_Abort);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", InitControllerPacketIRQSystem);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", InitControllerIRQSystem);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", FlushControllerPacketBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", HandleControllerPacketProcessed);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", SaveAndClearControllerCommandCode);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", HandleControllerBufferFilled);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", HandleControllerPacketReady);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", HandleControllerTransferComplete);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", QueryControllerState);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", BIOS_bzero);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", SetupControllerIRQFunctionPointers);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", UpdateControllerState);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", HandleControllerPacketState);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", StepControllerPacketTimeout);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", CheckVibrationBusyStat);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", StartControllerTimeout);

INCLUDE_ASM("asm/jp/nonmatchings/lib/dualshock", WaitRC2Ready);
