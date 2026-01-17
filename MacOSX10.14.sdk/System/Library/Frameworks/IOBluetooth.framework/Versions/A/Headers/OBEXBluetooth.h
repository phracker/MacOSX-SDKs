/*
	File:		OBEXBluetooth.h
	Contains:	Technology interfaces for OBEX over Bluetooth. See OBEX.h for more details about OBEX.
	Copyright:	(c) 2010 by Apple, Inc. All rights reserved.
*/

#pragma once

#import <IOBluetooth/OBEX.h>
#import <IOBluetooth/IOBluetoothUserLib.h>

//---------------------------------------------------------------------------------------------------------------------------
/*!	@header		OBEXBluetooth
	Object Exchange over Bluetooth.
*/


#ifdef	__cplusplus
	extern "C" {
#endif


#if 0
#pragma mark ======= Bluetooth Session Creators =======
#endif


//---------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothOBEXSessionCreateWithIOBluetoothSDPServiceRecordRef
	@abstract	Create an OBEX session with a service ref, usually obtained from the device browser.
	@param		inSDPServiceRecordRef	A valid service reference.
	@param		outSessionRef			A valid ptr to an IOBluetoothOBEXSessionRef; will contain the newly created session if
										return value is kOBEXSuccess.
	@result		An error code value. 0 if successful.
	@discussion	You will use a session reference to do all OBEX interaction to a specific device. This method DOES NOT
				create a connection to the device of any kind.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

OBEXError	IOBluetoothOBEXSessionCreateWithIOBluetoothSDPServiceRecordRef(	IOBluetoothSDPServiceRecordRef	inSDPServiceRef,
																			OBEXSessionRef *				outSessionRef )	DEPRECATED_IN_MAC_OS_X_VERSION_10_6_AND_LATER;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothOBEXSessionCreateWithIOBluetoothDeviceRefAndChannelNumber
	@abstract	Create an OBEX session with a device ref and an RFCOMM channel ID. This allows you to bypass the browser
				if you already know the SDP information.
	@param		inDeviceRef		A valid IOBluetoothDeviceRef reference.
	@param		inChannelID		A valid RFCOMM channel ID on the target device.
	@param		outSessionRef	A valid ptr to an IOBluetoothOBEXSessionRef; will contain the newly created session
								if return value is kOBEXSuccess.
	@result		An error code value. 0 if successful.
	@discussion	You will use a session reference to do all OBEX interaction to a specific device. This method DOES NOT
				create a connection to the device of any kind.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

OBEXError	IOBluetoothOBEXSessionCreateWithIOBluetoothDeviceRefAndChannelNumber(	IOBluetoothDeviceRef 		inDeviceRef,
																					BluetoothRFCOMMChannelID	inChannelID,
																					OBEXSessionRef *			outSessionRef )	DEPRECATED_IN_MAC_OS_X_VERSION_10_6_AND_LATER;


//---------------------------------------------------------------------------------------------------------------------------
/*!	@function	OBEXSessionCreateWithIncomingIOBluetoothRFCOMMChannel
	@abstract	Create an OBEX session with an IOBluetoothRFCOMMchannel. This implies you are creating a OBEX SERVER
				session that will dole out info to remote Bluetooth clients.
	@param		inRFCOMMChannel			A valid IOBluetoothRFCOMMChannel reference.
	@param		inGetResponseCallback	A callback for Get requests sent to your session by a remote device. Must be a
										valid function ptr, otherwise why even call this?
	@param		outSessionRef			A valid ptr to an IOBluetoothOBEXSessionRef; will contain the newly created
										session if return value is kOBEXSuccess.
	@result		An error code value. 0 if successful.
	@discussion	This assumes that the RFCOMM channel you have passed it is already open and ready to transmit data
				to the session.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

OBEXError	IOBluetoothOBEXSessionCreateWithIncomingIOBluetoothRFCOMMChannel(	IOBluetoothRFCOMMChannelRef		inRFCOMMChannelRef,
																				OBEXSessionEventCallback		inCallback,
																				void *							inUserRefCon,
																				OBEXSessionRef *				outSessionRef )	DEPRECATED_IN_MAC_OS_X_VERSION_10_6_AND_LATER;


typedef	void	(*IOBluetoothOBEXSessionOpenConnectionCallback) ( OBEXSessionRef session, OBEXError status, void * refCon );


//---------------------------------------------------------------------------------------------------------------------------
/*!	@function	OBEXSessionOpenTransportConnection
	@param		inSessionRef			A valid session reference.
	@param		inCallback				A valid callback.
	@param		inUserRefCon			Optional parameter; can contain anything you wish. Will be returned in your
										callback just as you passed it.
	@result		An error code value. 0 if successful.
	@discussion	Opens a transport-level connection to a remote target. For example, if you are using a Bluetooth transport,
				this will establish the baseband/L2CAP/RFCOMM connection to a device. Once the callback is called, the
				connection will either be opened or have failed with a status code. That status code will most likely have
				originated from the transport layer being used, so you may receive a Bluetooth error, an IOKit error, etc,
				but a 0 status should indicate success in all cases.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/ 

OBEXError	IOBluetoothOBEXSessionOpenTransportConnection(	OBEXSessionRef									inSessionRef,
															IOBluetoothOBEXSessionOpenConnectionCallback	inCallback,
															void *											inUserRefCon	)	DEPRECATED_IN_MAC_OS_X_VERSION_10_6_AND_LATER;

#ifdef	__cplusplus
	}
#endif

