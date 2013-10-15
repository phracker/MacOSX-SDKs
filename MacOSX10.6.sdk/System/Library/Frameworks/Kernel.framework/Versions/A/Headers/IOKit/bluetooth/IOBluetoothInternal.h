/*
	File:		BluetoothInternal.h
	Contains:	Internal types and macros needed by public kernel APIs.
	Copyright:	2003-2007 by Apple, Inc. All rights reserved.
*/

#pragma once

typedef enum IOBluetoothHCIControllerConfigState
{
	kIOBluetoothHCIControllerConfigStateOnline							= 0,	// Controller is configured and ready for clients
	kIOBluetoothHCIControllerConfigStateKernelSetupPending				= 1,	// New controller - kernel setup in progress
	kIOBluetoothHCIControllerConfigStateDaemonSetupPending				= 2,	// New controller - daemon setup in progress
	kIOBluetoothHCIControllerConfigStateDaemonSetupComplete				= 3,	// New controller - daemon setup complete
	kIOBluetoothHCIControllerConfigStateResetPending					= 4,	// HCI reset has been issued
	kIOBluetoothHCIControllerConfigStateKernelPostResetSetupPending		= 5,	// HCI reset complete - kernel setup in progress
	kIOBluetoothHCIControllerConfigStateDaemonPostResetSetupPending		= 6,	// HCI reset complete - daemon setup in progress
	kIOBluetoothHCIControllerConfigStateDaemonPostResetSetupComplete	= 7,	// HCI reset complete - daemon setup complete
	kIOBluetoothHCIControllerConfigStateUninitialized					= 8
} IOBluetoothHCIControllerConfigState;

typedef UInt32 IOBluetoothHCIControllerPowerOptions;
enum
{
	kIOBluetoothHCIControllerPowerOptionPowerOffSupported					= 0x00000001,
	kIOBluetoothHCIControllerPowerOptionWakeFromExistingConnectionSupported	= 0x00000002,
	kIOBluetoothHCIControllerPowerOptionWakeFromNewConnectionSupported		= 0x00000004,
	kIOBluetoothHCIControllerPowerOptionIdleWithConnectionSupported			= 0x00000008,	
	kIOBluetoothHCIControllerPowerOptionIdleWhenInternalPower				= 0x00000010	
};

enum IOBluetoothHCIControllerSleepOptions
{
	kIOBluetoothHCIControllerAllowWakeFromExistingConnection				= 0x00000001,
	kIOBluetoothHCIControllerAllowWakeFromNewConnection						= 0x00000002,
	kIOBluetoothHCIControllerTemporaryOnFromIdle							= 0x00000004
};

#define HCI_CONTROLLER_POWER_OFF_SUPPORTED( _controllerPowerOptions )	( ( _controllerPowerOptions & kIOBluetoothHCIControllerPowerOptionPowerOffSupported ) == kIOBluetoothHCIControllerPowerOptionPowerOffSupported )
#define HCI_CONTROLLER_SLEEP_SUPPORTED( _controllerPowerOptions )	\
	( ( _controllerPowerOptions &	\
		( kIOBluetoothHCIControllerPowerOptionWakeFromExistingConnectionSupported |	\
		  kIOBluetoothHCIControllerPowerOptionWakeFromNewConnectionSupported ) ) != 0 )

typedef enum IOBluetoothHCIControllerInternalPowerState
{
	kIOBluetoothHCIControllerInternalPowerStateOff		= 0,
	kIOBluetoothHCIControllerInternalPowerStateOn		= 1,
	kIOBluetoothHCIControllerInternalPowerStateSleep	= 2,
	kIOBluetoothHCIControllerInternalPowerStateIdle		= 3
} IOBluetoothHCIControllerInternalPowerState;

enum IOBluetoothHCIControllerPowerStateOrdinal
{
	kIOBluetoothHCIControllerPowerStateOrdinalOff		= 0,
	kIOBluetoothHCIControllerPowerStateOrdinalIdle		= 1,
	kIOBluetoothHCIControllerPowerStateOrdinalOn		= 2
};

typedef UInt32 IOBluetoothHCIControllerFeatureFlags;

enum
{
	kIOBluetoothHCIControllerFeatureFlagVendorCommandFlowControl	= 0x00000001,
	kIOBluetoothHCIControllerFeatureFlagSCOSupported				= 0x00000002,
	kIOBluetoothHCIControllerFeatureFlagSerializeCommands			= 0x10000000
};

//===========================================================================================================================
//	Private_UnifiedInquiryResult
//===========================================================================================================================

typedef struct	IOBluetoothHCIUnifiedInquiryResult	IOBluetoothHCIUnifiedInquiryResult;
struct	IOBluetoothHCIUnifiedInquiryResult
{
	BluetoothHCIInquiryResult			originalInquiryResult;

	// event code will be either:
	// kBluetoothHCIEventInquiryResult, kBluetoothHCIEventInquiryResultWithRSSI, or kBluetoothHCIEventExtendedInquiryResult

	BluetoothHCIEventCode eventCode;

	// kBluetoothHCIEventExtendedInquiryResult only

	BluetoothHCIExtendedInquiryResponse	extendedInquiryResponse;

	// kBluetoothHCIEventExtendedInquiryResult or kBluetoothHCIEventInquiryResultWithRSSI only

	UInt8								reserved;
	BluetoothHCIRSSIValue				RSSIValue;
};

#if BLUETOOTH_VERSION_MAX_ALLOWED >= BLUETOOTH_VERSION_2_0

enum BluetoothHCIExtendedInquiryResponseDataTypesAppleSpecificInfo
{
	kBluetoothHCIExtendedInquiryResponseDataTypeAppleSpecificInfoReserved					=	0x00,
	kBluetoothHCIExtendedInquiryResponseDataTypeAppleSpecificInfoModelIdentifier			=	0x01,	/* UTF8String char data */
	kBluetoothHCIExtendedInquiryResponseDataTypeAppleSpecificInfoThirdPartyAdvertising		=	0x02,
};

#endif /* BLUETOOTH_VERSION_MAX_ALLOWED >= BLUETOOTH_VERSION_2_0 */

