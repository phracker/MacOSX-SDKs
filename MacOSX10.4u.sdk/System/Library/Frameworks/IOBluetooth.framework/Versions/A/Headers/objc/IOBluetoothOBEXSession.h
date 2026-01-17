/*
	File:		IOBluetoothOBEXSession.h
	Contains:	Bluetooth Transport subclass of the OBEXSession object. 
    Copyright:	© 2002-2003 by Apple Computer, Inc. All rights reserved.
	Writers:	Jason Giles
*/

#import <IOKit/IOKitLib.h>

#import <IOBluetooth/objc/IOBluetoothRFCOMMChannel.h>
#import <IOBluetooth/objc/IOBluetoothSDPServiceRecord.h>
#import <IOBluetooth/IOBluetoothUserLib.h>

#import <IOBluetooth/OBEX.h>
#import <IOBluetooth/OBEXBluetooth.h>
#import <IOBluetooth/objc/OBEXSession.h>

//--------------------------------------------------------------------------------------------------------------------------
/*!	@class		IOBluetoothOBEXSession
	@abstract	An OBEX Session with a Bluetooth RFCOMM channel as the transport.
*/

	
//===========================================================================================================================
//	IOBluetoothOBEXSession Class
//===========================================================================================================================

#pragma mark === IOBluetoothOBEXSession ===

@interface IOBluetoothOBEXSession : OBEXSession
{
	/* All instance variables are protected. Use accessors to get to them if you need to. */
	
	IOBluetoothDevice *				mDevice;					// Bluetooth device we are conversing with.
	BluetoothRFCOMMChannelID		mRFCOMMChannelID;			// RFCOMM channel ID we're talking to.
	IOBluetoothRFCOMMChannel *		mRFCOMMChannel;				// RFCOMM channel we're talking to.
	
	// Buffer to write and varaibles to manage it:
	UInt8	*						outBuffer;
	size_t							bufferSize;
	size_t							currentOffsetInBuffer;
	BOOL							waitingForRfcommSpace;
	
	// Async Open Connection stuff.

	uint32_t										mOpenConnectionTimeout;
	SEL												mOpenConnectionSelector;
	id												mOpenConnectionSelectorTarget;
	void*											mOpenConnectionRefCon;
	IOBluetoothOBEXSessionOpenConnectionCallback	mOpenConnectionCallback;		// C API
	void*											mOpenConnectionCallbackRefCon;	// C API
}


//--------------------------------------------------------------------------------------------------------------------------
/*!	@method		withSDPServiceRecord
	@abstract	Creates a Bluetooth-based OBEX Session using an SDP service record, typically obtained from a device/service
				browser window controller.
	@param		inSDPServiceRecord		A valid SDP service record describing the service (and RFCOMM channel) you want to
										connect to with Bluetooth/OBEX.
	@result		An OBEX session representing the device/rfcomm channel found in the service record. nil if we failed.
	@discussion	Note that this does NOT mean the transport connection was open. It will be opened when OBEXConnect is
				invoked on the session object.
				
				*IMPORTANT NOTE*	In Bluetooth framework version 1.0.0, the session returned will NOT be autoreleased as it
									should be according to objc convention. This has been changed starting in Bluetooth version
									1.0.1 and later, so it WILL be autoreleased upon return, so you will need to retain
									it if you want to reference it later.
*/

+(IOBluetoothOBEXSession*) withSDPServiceRecord:(IOBluetoothSDPServiceRecord*)inSDPServiceRecord;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@method	withDevice
	@abstract	Creates a Bluetooth-based OBEX Session using a Bluetooth device and a Bluetooth RFCOMM channel ID.
	@param		inDevice				A valid Bluetooth device describing which device you want to connect to
										with Bluetooth/OBEX.
	@param		inRFCOMMChannelID		An RFCOMM Channel ID numbe that is available on the remote device. This channel will
										be used when the transport connection is attempted.
	@result		An OBEX session representing the device/rfcomm channel found in the service record. nil if we failed.
	@discussion	Note that this does NOT mean the transport connection was open. It will be opened when OBEXConnect is
				invoked on the session object.

				*IMPORTANT NOTE*	In Bluetooth framework version 1.0.0, the session returned will NOT be autoreleased as it
									should be according to objc convention. This has been changed starting in Bluetooth version
									1.0.1 and later, so it WILL be autoreleased upon return, so you will need to retain
									it if you want to reference it later.
*/
		
+(IOBluetoothOBEXSession*)withDevice:(IOBluetoothDevice*)inDevice
		channelID:(BluetoothRFCOMMChannelID)inRFCOMMChannelID;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@method		withIncomingRFCOMMChannel
	@abstract	Creates a Bluetooth-based OBEX Session using an incoming RFCOMM channel.
	@param		inChannel				The channel to use to create a connection to a device.
	@param		inEventSelector			The selector that gets called when an event occurs on the OBEX Session.
	@param		inEventSelectorTarget	The object that is used to call the above selector.
	@param		inUserRefCon			The reference constant. Pass whatever you wish - it will be returned to you in the selector.
	@result		
	@discussion	

				*IMPORTANT NOTE*	In Bluetooth framework version 1.0.0, the session returned will NOT be autoreleased as it
									should be according to objc convention. This has been changed starting in Bluetooth version
									1.0.1 and later, so it WILL be autoreleased upon return, so you will need to retain
									it if you want to reference it later.
*/
	
+(IOBluetoothOBEXSession*)withIncomingRFCOMMChannel:(IOBluetoothRFCOMMChannel*)inChannel
		eventSelector:(SEL)inEventSelector
		selectorTarget:(id)inEventSelectorTarget
		refCon:(void *)inUserRefCon;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@method		initWithSDPServiceRecord
	@abstract	Initializes a Bluetooth-based OBEX Session using an SDP service record.
	@param		inSDPServiceRecord		
	@result		
	@discussion	
*/
	
-(id) initWithSDPServiceRecord:(IOBluetoothSDPServiceRecord*)inSDPServiceRecord;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@method		initWithDevice
	@abstract	Initializes a Bluetooth-based OBEX Session using a Bluetooth device.
	@param		inDevice		The bluetooth device on which to open the OBEXSession.
	@param		inChannelID		The RFCOMM channel ID to use when opening the connection.
	@result		
	@discussion	
*/
		
-(id) initWithDevice:(IOBluetoothDevice*)inDevice
		channelID:(BluetoothRFCOMMChannelID)inChannelID;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@method		initWithIncomingRFCOMMChannel
	@abstract	Initializes a Bluetooth-based OBEX Session using an incoming RFCOMM channel.
	@param		inChannelID				RFCOMM channel ID of the desired channel to be used.
	@param		inEventSelector			The selector to be called when an event is received.
	@param		inEventSelectorTarget	The target object that get the selector message.
	@param		refCon					caller reference constant, pass whatever you want, it will be returned to you in the selector.		
	@result		
	@discussion	
*/
	
-(id) initWithIncomingRFCOMMChannel:(IOBluetoothRFCOMMChannel*)inChannel
		eventSelector:(SEL)inEventSelector
		selectorTarget:(id)inEventSelectorTarget
		refCon:(void *)inUserRefCon;
		
//--------------------------------------------------------------------------------------------------------------------------
/*!	@method		getRFCOMMChannel
	@abstract	Get the Bluetooth RFCOMM channel being used by the session object.
	@result		A IOBluetoothRFCOMMChannel object.
	@discussion	This could potentially be nil even though you have a valid OBEX session, because the RFCOMM channel is
				only valid when the session is connected.
*/
	
-(IOBluetoothRFCOMMChannel*)getRFCOMMChannel;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@method		getDevice
	@abstract	Get the Bluetooth Device being used by the session object.
	@result		An IOBluetoothDevice object.
	@discussion	
*/

-(IOBluetoothDevice*)getDevice;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@method		sendBufferTroughChannel
	@abstract	Sends the next block of data trough the rfcomm channel.
	@result
	@discussion	Since a send in the rfcomm channel is broken in multiple write calls (this actually is true only if the size is grater
	than the rfcomm MTU). Each write call is performed by sendBufferTroughChannel. This should never need to be overwritten.
*/
- (IOReturn)sendBufferTroughChannel;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@method		restartTransmission
	@abstract	If the transmission was stopeed due to the lack of buffers this call restarts it.
	@result
	@discussion	If the transmission was stopeed due to the lack of buffers this call restarts it.
*/
- (void)restartTransmission;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@method		isSessionTargetAMac
	@abstract	Tells whether the target device is a Mac by checking its service record.
	@result		TRUE only if device service record has Mac entry, FALSE for all else.
	@discussion	Tells whether the target device is a Mac by checking its service record.
*/
- (BOOL)isSessionTargetAMac;




/* OBEXSession overrides */

#pragma mark -
#pragma mark === OBEXSession overrides ===


//--------------------------------------------------------------------------------------------------------------------------
/*!	@method		openTransportConnection
	@abstract	An OBEXSession override. When this is called by the session baseclass, we will attempt to open the
				transport connection. In our case, this would be an RFCOMM channel to another Bluetooth device.
	@result		Success or failure code.
	@discussion	Your selector should have the following signature:
	
					-(void)transportConnectionSelector:(id)refcon		status:(OBEXError)status;
				
				Thus you could use it with openTransportConnection like this:
				
					OBEXError	error = [anOBEXSession	openTransportConnection:@selector( transportConnectionSelector:status: )
														selectorTarget:self
														refCon:anOBEXSession];	// or whatever you want to pass as a refCon...
				
				Be sure to check the status code! Assume the connection was not opened unless status is kOBEXSuccess.
				
*/

-(OBEXError)openTransportConnection:(SEL)inSelector
				selectorTarget:(id)inTarget
				refCon:(void *)inUserRefCon;
				
//--------------------------------------------------------------------------------------------------------------------------
/*!	@method		hasOpenTransportConnection
	@abstract	An OBEXSession override. When this is called by the session baseclass, we will return whether or not we
				have a transport connection established to another OBEX server/client. In our case we will tell whether
				or not the RFCOMM channel to a remote device is still open.
	@result		True or false, whether there is already an open transport connection for this OBEX session.
	@discussion	
*/

-(BOOL)hasOpenTransportConnection;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@method		closeTransportConnection
	@abstract	An OBEXSession override. When this is called by the session baseclass, we will close the transport
				connection if it is opened. In our case, it will be the RFCOMM channel that needs closing.
	@result		Success or failure code, describing whether the call succeeded in closing the transport connection successfully.
	@discussion	
*/

-(OBEXError)closeTransportConnection;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@method		sendDataToTransport
	@abstract	An OBEXSession override. When this is called by the session baseclass, we will send the data we are given
				over our transport connection. If none is open, we could try to open it, or just return an error. In our
				case, it will be sent over the RFCOMM channel.
	@result		Success or failure code, describing whether the call succeeded in writing the data to the transport.
	@discussion	
*/

-(OBEXError)sendDataToTransport:(void *)inDataToSend
			dataLength:(size_t)inDataLength;
			

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		setOpenTransportConnectionAsyncSelector
	@abstract	Allows you to set the selector to be used when a transport connection is opened, or fails to open.
	@param		inEventSelector				Selector to call on the target.
	@param		inEventSelectorTarget		Target to be called with the selector.
	@param		inUserRefCon				User's refCon that will get passed to them when their selector is invoked.
	@discussion	You do not need to call this on the session typically, unless you have subclassed the OBEXSession to
				implement a new transport and that transport supports async opening of connections. If it does not support
				async open, then using this is pointless.
*/

-(void)setOpenTransportConnectionAsyncSelector:(SEL)inSelector
			target:(id)inSelectorTarget
			refCon:(id)inUserRefCon;
			
//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		setOBEXSessionOpenConnectionCallback
	@abstract	For C API support. Allows you to set the callback to be invoked when the OBEX connection is actually opened.
	@param		inCallback			function to call on the target.
	@param		inUserRefCon		user's reference constant, will be returned on the callback.
*/

-(void)setOBEXSessionOpenConnectionCallback:(IOBluetoothOBEXSessionOpenConnectionCallback)inCallback
			refCon:(void*)inUserRefCon;
			
			
@end
