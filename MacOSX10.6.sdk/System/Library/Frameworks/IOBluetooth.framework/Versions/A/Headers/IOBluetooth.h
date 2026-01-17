//
//  IOBluetooth.h
//  IOBluetooth Framework
//
//  Copyright (c) 2007 Apple Inc. All rights reserved.
//

#if __OBJC__

	// Objective C API

	#if defined(__cplusplus)
	extern "C" {
	#endif
		
		// Core - General & Support

		#import	<IOBluetooth/Bluetooth.h>
		#import	<IOBluetooth/BluetoothAssignedNumbers.h>
		#import	<IOBluetooth/IOBluetoothTypes.h>
		#import	<IOBluetooth/IOBluetoothUtilities.h>
		#import <IOBluetooth/objc/IOBluetoothDeviceInquiry.h>
		#import <IOBluetooth/objc/IOBluetoothDevice.h>
		
		// Core - Host Controller (HCI)

		#import <IOBluetooth/objc/IOBluetoothHostController.h>
		#import <IOBluetooth/objc/IOBluetoothDeviceInquiry.h>

		// Core - L2CAP

		#import <IOBluetooth/objc/IOBluetoothL2CAPChannel.h>

		// Core - RFCOMM

		#import <IOBluetooth/objc/IOBluetoothRFCOMMChannel.h>

		// Core - SDP

		#import <IOBluetooth/objc/IOBluetoothSDPDataElement.h>
		#import <IOBluetooth/objc/IOBluetoothSDPServiceAttribute.h>
		#import <IOBluetooth/objc/IOBluetoothSDPServiceRecord.h>
		#import <IOBluetooth/objc/IOBluetoothSDPUUID.h>

		// Profiles - OBEX

		#import <IOBluetooth/OBEX.h>
		#import <IOBluetooth/objc/OBEXSession.h>
		#import <IOBluetooth/objc/IOBluetoothOBEXSession.h>
		#import <IOBluetooth/objc/OBEXFileTransferServices.h>

		// Profiles - Audio, etc.

		#import <IOBluetooth/objc/IOBluetoothRFCOMMAudioController.h>
		#import <IOBluetooth/objc/IOBluetoothHandsFreeGateway.h>
		#import <IOBluetooth/objc/IOBluetoothHeadsetDevice.h>

	#if defined(__cplusplus)
	}
	#endif
	
#endif

