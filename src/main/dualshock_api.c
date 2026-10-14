#include "common.h"

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", GsGetAndClearControllerReadyFlag);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", GsResetInterruptHandlers);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", GsRemoveInterruptHandlers);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", Controller_GetReverbMode);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", GetVibrationDeviceType);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", CheckVibrationPortMode);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", InitVibrationPlaybackPacket);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", SendVibrationDataPacket);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", QueueVibrationPlayback);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", SetupControllerVibrationIRQHandlers);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", SendVibrationCommand);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", CheckAndHandleControllerAuxInterrupt);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", SetupControllerIRQHandlers);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", CheckAndHandleControllerInterrupt);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", HandleControllerFrameInterrupt);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", GetAndClearControllerReadyFlag);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", ResetInterruptHandlersAndTimers);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", RemoveInterruptHandlersAndTimers);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", BeginControllerTransfer);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", StepControllerTransferPhase);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", PollControllerTransferStatus);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", WaitControllerAckPulse);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", WaitForControllerReady);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", WaitForControllerAckBit);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", WriteVibrationData);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", SetControllerConfig);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", ProcessControllerCommandState);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", ProcessControllerPacketState);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", CalculateControllerPacketLength);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", SetupControllerPacketHandlers);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", HandleControllerPacketCommand);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", ProcessControllerPacketStep);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", SetVibrationPlaybackState);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", SetControllerRumbleMap);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", ProcessControllerFrameStep);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", SetVibrationMotorState);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", SetupControllerCommandGeneric);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", ControllerCmd_SetupType1);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", SetControllerConfigMode);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", SetControllerQueryStatus);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", SetControllerQueryMap);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", SetControllerQueryActuator);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", SetControllerQueryParam);

INCLUDE_ASM("asm/jp/nonmatchings/main/dualshock_api", SetControllerAbort);
