/*
	File:		IOBluetoothTypes.h
	Contains:	Public header with family provided types and defines - shared between user and kernel code.
	Version:	1.0
	Copyright:	© 2002 by Apple Computer, Inc. All rights reserved.
	Technology:	Bluetooth
*/

#pragma once

#include <IOKit/IOReturn.h>

// Error returns
#ifndef sub_iokit_bluetooth
#define sub_iokit_bluetooth				err_sub(8)
#endif

#define iokit_bluetooth_err(return)		(sys_iokit|sub_iokit_bluetooth|return)

#define kIOBluetoothDeviceResetError			iokit_bluetooth_err(1)	// Device reset interrupted pending operation
#define kIOBluetoothConnectionAlreadyExists		iokit_bluetooth_err(2)	// Attempting to open a connection that already exists
#define kIOBluetoothNoHCIController				iokit_bluetooth_err(3)	// No HCI controller is present
#define kIOBluetoothHCIPowerStatesNotSupported	iokit_bluetooth_err(4)	// HCI controller does not support changing power states


