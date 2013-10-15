/*
	File:		IOBluetoothUIUserLib.h
	Contains:	Library to allow user-side clients to use Bluetooth UI C API's.
	Copyright:	(c) 2002-2006 by Apple Computer, Inc. All rights reserved.
*/

#pragma once

#include <IOBluetooth/IOBluetoothUserLib.h>

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

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothServiceBrowserControllerCreate
	@abstract	
	@param						
	@result		
	@discussion	
*/

IOBluetoothServiceBrowserControllerRef	IOBluetoothServiceBrowserControllerCreate(IOBluetoothServiceBrowserControllerOptions inOptions);

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothServiceBrowserControllerBrowseDevices
	@abstract	
	@param						
	@result		
	@discussion	
*/

IOReturn IOBluetoothServiceBrowserControllerBrowseDevices(IOBluetoothSDPServiceRecordRef *outRecord,  IOBluetoothServiceBrowserControllerOptions inOptions);

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothServiceBrowserControllerSetOptions
	@abstract	
	@param						
	@result		
	@discussion	
*/

void IOBluetoothServiceBrowserControllerSetOptions(IOBluetoothServiceBrowserControllerRef controller, IOBluetoothServiceBrowserControllerOptions inOptions);

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothServiceBrowserControllerDiscover
	@abstract	
	@param						
	@result		
	@discussion	
*/

IOReturn IOBluetoothServiceBrowserControllerDiscover(IOBluetoothServiceBrowserControllerRef controller, IOBluetoothSDPServiceRecordRef *outRecord);

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothServiceBrowserControllerDiscoverWithDeviceAttributes
	@abstract	
	@param						
	@result		
	@discussion	
*/

IOReturn IOBluetoothServiceBrowserControllerDiscoverWithDeviceAttributes(IOBluetoothServiceBrowserControllerRef controller, IOBluetoothSDPServiceRecordRef *outRecord, IOBluetoothDeviceSearchAttributes *deviceAttributes, CFArrayRef serviceArray);


#if 0
#pragma mark -
#pragma mark === Bluetooth Pairing Controller ===
#endif

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothGetPairingController
	@abstract	
	@param						
	@result		
	@discussion	
*/

IOBluetoothPairingControllerRef	IOBluetoothGetPairingController();

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothPairingControllerRunPanelWithAttributes
	@abstract	
	@param						
	@result		
	@discussion	
*/

void	IOBluetoothPairingControllerRunPanelWithAttributes(IOBluetoothPairingControllerRef pairingController, IOBluetoothDeviceSearchAttributes *attributes);

#if 0
#pragma mark -
#pragma mark === Bluetooth Device Selector Controller ===
#endif


//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothGetDeviceSelectorController
	@abstract	
	@param						
	@result		
	@discussion	
*/

IOBluetoothDeviceSelectorControllerRef	IOBluetoothGetDeviceSelectorController();


//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothDeviceSelectorRunPanelWithAttributes
	@abstract	
	@param						
	@result		
	@discussion	
*/

CFArrayRef	IOBluetoothDeviceSelectorRunPanelWithAttributes(IOBluetoothDeviceSelectorControllerRef deviceSelector, IOBluetoothDeviceSearchAttributes *attributes);

#if 0
#pragma mark -
#pragma mark === Other functions ===
#endif


IOReturn IOBluetoothValidateHardware( CFStringRef cancelButtonTitle ) AVAILABLE_BLUETOOTH_VERSION_1_1_AND_LATER;

#ifdef	__cplusplus
	}
#endif
