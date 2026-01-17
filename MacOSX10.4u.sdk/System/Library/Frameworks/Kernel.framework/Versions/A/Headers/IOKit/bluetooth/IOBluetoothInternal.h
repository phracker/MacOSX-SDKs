/*
	File:		BluetoothInternal.h
	Contains:	Internal types and macros needed by public kernel APIs.
	Copyright:	© 2003 by Apple Computer, Inc. All rights reserved.
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
	kIOBluetoothHCIControllerPowerOptionWakeFromNewConnectionSupported		= 0x00000004
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
