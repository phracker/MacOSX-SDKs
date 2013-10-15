/*
	File:		IOBluetoothUIUserLib.h
	Contains:	Library to allow user-side clients to use Bluetooth UI C API's.
	Copyright:	й 2002 by Apple Computer, Inc. All rights reserved.
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
#pragma mark ее Bluetooth Service Browser Controller ее
#endif

/*!
  @enum IOBluetoothServiceBrowserControllerOptions
  @discussion Option values to customize the behavior of an IOBluetoothServiceBrowserController object.
  @constant kIOBluetoothServiceBrowserControllerOptionsNone - no options set.
  @constant kIOBluetoothServiceBrowserControllerOptionsAutoStartInquiry - automatically start an inquiry when the panel is displayed.
  @constant kIOBluetoothServiceBrowserControllerOptionsDisconnectWhenDone - disconnect from the device when UI operations are finished.
  
*/
typedef uint32_t IOBluetoothServiceBrowserControllerOptions;

enum
{
	kIOBluetoothServiceBrowserControllerOptionsNone					= (0 << 0L),
	kIOBluetoothServiceBrowserControllerOptionsAutoStartInquiry		= (1 << 0L),
    kIOBluetoothServiceBrowserControllerOptionsDisconnectWhenDone	= (2 << 0L)
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
#pragma mark ее Bluetooth Pairing Controller ее
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
#pragma mark ее Bluetooth Device Selector Controller ее
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
#pragma mark ее Other functions ее
#endif


IOReturn IOBluetoothValidateHardware( CFStringRef cancelButtonTitle ) AVAILABLE_BLUETOOTH_VERSION_1_1_AND_LATER;

#ifdef	__cplusplus
	}
#endif
