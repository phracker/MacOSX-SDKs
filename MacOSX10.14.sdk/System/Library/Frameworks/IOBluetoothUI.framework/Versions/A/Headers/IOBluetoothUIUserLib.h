/*
	File:		IOBluetoothUIUserLib.h
	Copyright:	(c) 2010 by Apple, Inc. All rights reserved.
*/

#pragma once

#import <IOBluetooth/IOBluetoothUserLib.h>

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

IOReturn IOBluetoothValidateHardware( CFStringRef cancelButtonTitle ) DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;
		
IOReturn IOBluetoothValidateHardwareWithDescription( CFStringRef cancelButtonTitle,  CFStringRef descriptionText) AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;
		
		
// Deprecated API; use obj-c equivalents.

IOBluetoothServiceBrowserControllerRef	IOBluetoothServiceBrowserControllerCreate(IOBluetoothServiceBrowserControllerOptions inOptions) DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;
IOReturn IOBluetoothServiceBrowserControllerBrowseDevices(IOBluetoothSDPServiceRecordRef *outRecord,  IOBluetoothServiceBrowserControllerOptions inOptions)  DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;
void IOBluetoothServiceBrowserControllerSetOptions(IOBluetoothServiceBrowserControllerRef controller, IOBluetoothServiceBrowserControllerOptions inOptions)  DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;
IOReturn IOBluetoothServiceBrowserControllerDiscover(IOBluetoothServiceBrowserControllerRef controller, IOBluetoothSDPServiceRecordRef *outRecord)  DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;
IOReturn IOBluetoothServiceBrowserControllerDiscoverWithDeviceAttributes(IOBluetoothServiceBrowserControllerRef controller, IOBluetoothSDPServiceRecordRef *outRecord, IOBluetoothDeviceSearchAttributes *deviceAttributes, CFArrayRef serviceArray)  DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;
IOBluetoothPairingControllerRef	IOBluetoothGetPairingController();
void	IOBluetoothPairingControllerRunPanelWithAttributes(IOBluetoothPairingControllerRef pairingController, IOBluetoothDeviceSearchAttributes *attributes)  DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;
IOBluetoothDeviceSelectorControllerRef	IOBluetoothGetDeviceSelectorController();
CFArrayRef	IOBluetoothDeviceSelectorRunPanelWithAttributes(IOBluetoothDeviceSelectorControllerRef deviceSelector, IOBluetoothDeviceSearchAttributes *attributes)  DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

#ifdef	__cplusplus
	}
#endif
