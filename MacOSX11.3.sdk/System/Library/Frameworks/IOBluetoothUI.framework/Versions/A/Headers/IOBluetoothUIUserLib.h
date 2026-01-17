/*
	File:		IOBluetoothUIUserLib.h
	Copyright:	(c) 2010 by Apple, Inc. All rights reserved.
*/

#pragma once

#import <IOBluetooth/IOBluetoothUserLib.h>
#import <Availability.h>

API_UNAVAILABLE_BEGIN(ios)
#ifdef	__cplusplus
	extern "C" {
#endif

typedef struct OpaqueIOBluetoothObjectRef *			IOBluetoothDeviceSelectorControllerRef;
typedef struct OpaqueIOBluetoothObjectRef *			IOBluetoothPairingControllerRef;
typedef struct OpaqueIOBluetoothObjectRef *			IOBluetoothServiceBrowserControllerRef;

// Common UI functions

#if 0
#pragma mark -
#pragma mark === Bluetooth Service Browser Controller ===
#endif

/*!
  @enum IOBluetoothServiceBrowserControllerOptions
  @discussion Option values to customize the behavior of an IOBluetoothServiceBrowserController object.
  @constant kIOBluetoothServiceBrowserControllerOptionsNone - no options set.
  @constant kIOBluetoothServiceBrowserControllerOptionsAutoStartInquiry - automatically start an inquiry when the panel is displayed.  This has been deprecated in 10.5
  @constant kIOBluetoothServiceBrowserControllerOptionsDisconnectWhenDone - disconnect from the device when UI operations are finished.
  
*/
typedef uint32_t IOBluetoothServiceBrowserControllerOptions;

enum
{
	kIOBluetoothServiceBrowserControllerOptionsNone					= 0L,
	kIOBluetoothServiceBrowserControllerOptionsAutoStartInquiry		= (1L << 0), // this has been deprecated in 10.5, all panels will AutoStart
    kIOBluetoothServiceBrowserControllerOptionsDisconnectWhenDone	= (1L << 1)
};

enum
{
	kIOBluetoothUISuccess			= (-1000),	// Same as NSRunStoppedResponse
	kIOBluetoothUIUserCanceledErr	= (-1001)	// Same as NSRunAbortedResponse
};
		
IOReturn IOBluetoothValidateHardwareWithDescription( CFStringRef cancelButtonTitle,  CFStringRef descriptionText) AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;
		
// Deprecated API; use obj-c equivalents.
IOBluetoothPairingControllerRef	IOBluetoothGetPairingController(void);
IOBluetoothDeviceSelectorControllerRef	IOBluetoothGetDeviceSelectorController(void);

#ifdef	__cplusplus
	}
#endif
API_UNAVAILABLE_END
