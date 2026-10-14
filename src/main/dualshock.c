#include "common.h"

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", GsGetAndClearControllerReadyFlag);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", GsResetInterruptHandlers);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", GsRemoveInterruptHandlers);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", Controller_GetReverbMode);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", GetVibrationDeviceType);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", CheckVibrationPortMode);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", InitVibrationPlaybackPacket);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", SendVibrationDataPacket);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", QueueVibrationPlayback);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", SetupControllerVibrationIRQHandlers);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", SendVibrationCommand);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", CheckAndHandleControllerAuxInterrupt);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", SetupControllerIRQHandlers);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", CheckAndHandleControllerInterrupt);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", HandleControllerFrameInterrupt);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", GetAndClearControllerReadyFlag);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", ResetInterruptHandlersAndTimers);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", RemoveInterruptHandlersAndTimers);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", BeginControllerTransfer);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", StepControllerTransferPhase);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", PollControllerTransferStatus);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", WaitControllerAckPulse);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", WaitForControllerReady);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", WaitForControllerAckBit);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", WriteVibrationData);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", SetControllerConfig);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", ProcessControllerCommandState);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", ProcessControllerPacketState);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", CalculateControllerPacketLength);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", SetupControllerPacketHandlers);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", HandleControllerPacketCommand);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", ProcessControllerPacketStep);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", SetVibrationPlaybackState);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", SetControllerRumbleMap);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", ProcessControllerFrameStep);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", SetVibrationMotorState);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", SetupControllerCommandGeneric);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", ControllerCmd_SetupType1);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", SetControllerConfigMode);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", SetControllerQueryStatus);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", SetControllerQueryMap);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", SetControllerQueryActuator);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", SetControllerQueryParam);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", SetControllerAbort);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", ControllerCmd_SetupType3);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", ControllerCmd_SetupType2);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", ControllerCmd_SetupType4);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", ControllerCmd_Abort);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", InitControllerPacketIRQSystem);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", InitControllerIRQSystem);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", FlushControllerPacketBuffer);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", HandleControllerPacketProcessed);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", SaveAndClearControllerCommandCode);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", HandleControllerBufferFilled);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", HandleControllerPacketReady);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", HandleControllerTransferComplete);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", QueryControllerState);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", BIOS_bzero);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", SetupControllerIRQFunctionPointers);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", UpdateControllerState);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", HandleControllerPacketState);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", StepControllerPacketTimeout);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", CheckVibrationBusyStat);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", StartControllerTimeout);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock", WaitRC2Ready);
