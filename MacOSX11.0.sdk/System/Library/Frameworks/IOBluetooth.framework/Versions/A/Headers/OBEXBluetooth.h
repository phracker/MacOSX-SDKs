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

API_UNAVAILABLE(ios, watchos, tvos)
OBEXError	IOBluetoothOBEXSessionCreateWithIncomingIOBluetoothRFCOMMChannel(	IOBluetoothRFCOMMChannelRef		inRFCOMMChannelRef,
																				OBEXSessionEventCallback		inCallback,
																				void *							inUserRefCon,
																				OBEXSessionRef *				outSessionRef )	DEPRECATED_IN_MAC_OS_X_VERSION_10_6_AND_LATER;


typedef	void	(*IOBluetoothOBEXSessionOpenConnectionCallback) ( OBEXSessionRef session, OBEXError status, void * refCon );


#ifdef	__cplusplus
	}
#endif

