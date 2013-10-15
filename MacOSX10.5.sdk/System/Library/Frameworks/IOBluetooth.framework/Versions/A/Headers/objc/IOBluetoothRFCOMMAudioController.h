
/*!
	@header
	@abstract	Baseclass of Headset and Handsfree objects.  Implements
				basic interface to the audio driver and remote device
	@copywrite	(C) 2006 by Apple Computer, Inc., all rights reserved.
 */


#if BLUETOOTH_VERSION_MAX_ALLOWED >= BLUETOOTH_VERSION_2_0

#import <Foundation/Foundation.h>
#import <IOBluetooth/Bluetooth.h>
#import <CoreAudio/AudioHardware.h>

@class IOBluetoothSCOAudioDevice;
@class IOBluetoothDevice;
@class IOBluetoothRFCOMMChannel;
@class IOBluetoothUserNotification;
@class IOBluetoothSDPServiceRecord;


//  These values are for apps that try to use our drivers through CoreAudio
//
enum IOBluetoothSCODriverPropertiesPublic
{
	//  regsiter for changes on this before before opening the device
	//
	kIOBluetoothSCOAudioDriverPropertyNotificationDeviceOpenResult		= 'scor',

	//  Set this property to true to suppress the UI brought up by the Bluetooth system
	// when errors occur
	//
	kIOBluetoothSCOAudioDriverPropertyUsesExternalErrorUI				= 'scoa',
};



//====================================================================================================================
//	IOBluetoothRFCOMMAudioController
//====================================================================================================================
/*!
	@class			IOBluetoothRFCOMMAudioController
	@abstract		Baseclass for various SCO profiles
	@discussion		
*/
@interface IOBluetoothRFCOMMAudioController : NSObject {
	
	IOBluetoothSCOAudioDevice *		mSCOAudioDevice;
	IOBluetoothDevice *				mBluetoothDevice;
	BluetoothRFCOMMChannelID		mIncomingRFCOMMChannelID;
	BluetoothRFCOMMChannelID		mOutgoingRFCOMMChannelID;
	IOBluetoothRFCOMMChannel *		mRFCOMMChannel;
	IOBluetoothUserNotification *	mRFCOMMChannelNotification;
	
	id								mDelegate;	

	BOOL							mIsInternalVolumeChange;
	
	void *							mReserved;
	
}

// ---------------------------------------------------
// Init's
//
/*!
	 @method		initWithIncomingDevice:incomingRFCOMMChannelID:delegate:
	 @abstract		Create a new IOBluetoothRFCOMMAudioController for a device that is trying to connect in
	 @discussion	Typically you won't be calling this method directly, instead you'll use
					methods provided by the subclasses.
	 @param			device A valid IOBluetoothDevice with baseband connection
	 @param			incomingRFCOMMChannelID The RFCOMM ID the device is trying to connect to
	 @param			inDelegate An object to act as delegate
	 @result		A newly created IOBluetoothRFCOMMAudioController object on success, nil on failure
*/
- (id) initWithIncomingDevice: (IOBluetoothDevice *)device 
	  incomingRFCOMMChannelID: (BluetoothRFCOMMChannelID)incomingRFCOMMChannelID
					 delegate: (id)inDelegate;

/*!
	 @method		initForConnectionToDevice:delegate:
	 @abstract		Create a new IOBluetoothRFCOMMAudioController for outgoing connect to a device
	 @discussion	Typically you won't be calling this method directly, instead you'll use
					methods provided by the subclasses.
	 @param			device A valid IOBluetoothDevice
	 @param			inDelegate An object to act as delegate
	 @result		A newly created IOBluetoothRFCOMMAudioController object on success, nil on failure
*/
- (id) initForConnectionToDevice: (IOBluetoothDevice *)device
						delegate: (id)inDelegate;

- (void) dealloc;
- (void) setDelegate:(id)delegate;


// ---------------------------------------------------
// CoreAudio stuff
//
/*!
	@method		getAudioDeviceID
	@abstract	Get the audio device ID this object is attached to
	@discussion	
	@result		The audio device ID this object is attached to, NULL if not attached
*/
- (AudioDeviceID) getAudioDeviceID;


// ---------------------------------------------------
// Device connection
//
/*!
	@method		getBluetoothDevice
	@abstract	Get the bluetooth device associated with this device
	@discussion	
	@result		The bluetooth device this object is using, otherwise NULL
*/
- (IOBluetoothDevice *) getBluetoothDevice;

/*!
	@method		isDeviceConnected
	@abstract	Get the connection state of the bluetooth device being used
	@discussion	
	@result		The connection state of the device, FALSE if no device or not connected
*/
- (BOOL) isDeviceConnected;

/*!
	@method		openDeviceConnection
	@abstract	Open the bluetooth device connection
	@discussion	Look for final result in the provided delegate method
	@result		The result of the first stage of connection, kIOReturnNoDevice if no device.
*/
- (IOReturn) openDeviceConnection;

/*!
	@method		closeDeviceConnection
	@abstract	Close the bluetooth device connection
	@discussion	Look for final result in the provided delegate method
	@result		The result of the first stage of disconnection, kIOReturnNoDevice if no device.
*/
- (IOReturn) closeDeviceConnection;



// ---------------------------------------------------
// RFCOMM connection
//
/*!
	@method		getIncomingRFCOMMChannelID
	@abstract	Access to the RFCOMM ID as specified on init for incoming device connections
	@discussion	
	@result		The RFCOMM channel ID of the remote device, 0 if none
*/
- (BluetoothRFCOMMChannelID) getIncomingRFCOMMChannelID;

/*!
	@method		getOutgoingRFCOMMChannelID
	@abstract	Access to the RFCOMM ID as specified in the SDP of the device for outgoing connections
	@discussion	
	@result		The RFCOMM channel ID of the remote device, 0 if none
*/
- (BluetoothRFCOMMChannelID) getOutgoingRFCOMMChannelID;

/*!
	@method		isRFCOMMChannelOpen
	@abstract	Check if the RFCOMM channel is open
	@discussion	
	@result		TRUE if open, FALSE if closed or device is nil
*/
- (BOOL) isRFCOMMChannelOpen;

/*!
	@method		setRFCOMMChannel
	@abstract	Set the RFCOMM channel to use
	@discussion	
	@param		rfcommChannel The channel to use or nil to release the current one
*/
- (void) setRFCOMMChannel:(IOBluetoothRFCOMMChannel *)rfcommChannel;

/*!
	@method		openRFCOMMChannel
	@abstract	Open rfcomm channel on current bluetooth device on the outgoing RFCOMM channel ID 
	@discussion	Look for final result in the provided delegate method
	@result		Result will be value returned from IOBluetoothDevice openRFCOMMChannelAsync if device is valid, kIOReturnError if no device is set
*/
- (IOReturn) openRFCOMMChannel;

/*!
	@method		closeRFCOMMChannel
	@abstract	Close the rfcomm channel
	@discussion	Look for final results in the provided delegate method
	@result		Result will be value returned from the channels' "closeChannel" method, kIOReturnNotAttached if no channel is set
*/
- (IOReturn) closeRFCOMMChannel;

/*!
	@method		sendRFCOMMData:length:
	@abstract	Send RFCOMM data to the device
	@discussion	
	@param		data Data to be sent to device
	@param		length Length of the data
	@result		Result will be value returned from the channels' "writeAsync" method, kIOReturnNotAttached if no channel is set
*/
- (IOReturn) sendRFCOMMData:(const void *)data length:(UInt16)length;

//
//  Various RFCOMM delegate methods.  Developers, you can override the rfcommChannelData method to 
// catch and deal with incoming commands from the remote device.  This object does nothing with the
// data it receives.
//
//	Its also suggested that you use the standard delegate method below and not touch these guys unless
// you absolutely have to.
//
- (void) handleIncomingRFCOMMChannelOpened:(IOBluetoothUserNotification *)notification channel:(IOBluetoothRFCOMMChannel *)channel;
- (void) rfcommChannelOpenComplete:(IOBluetoothRFCOMMChannel *)rfcommChannel status:(IOReturn)status;
- (void) rfcommChannelClosed:(IOBluetoothRFCOMMChannel *)rfcommChannel;
- (void) rfcommChannelData:(IOBluetoothRFCOMMChannel *)rfcommChannel data:(void *)data length:(size_t)length;


// ---------------------------------------------------
// SCO connection
//
/*!
	@method		isSCOConnected
	@abstract	Check if the SCO connection is open
	@discussion	
	@result		TRUE if open, FALSE if closed or device is nil
*/
- (BOOL) isSCOConnected;

/*!
	@method		openSCOConnection
	@abstract	Open the SCO connection
	@discussion	Look for final result in the provided delegate method
	@result		kIOReturnSuccess on success or if still open, various errors if failed
*/
- (IOReturn) openSCOConnection;

/*!
	@method		closeSCOConnection
	@abstract	Close the SCO connection
	@discussion	Look for final results in the provided delegate method
	@result		kIOReturnSuccess on success or if already closed, various errors if failed
*/
- (IOReturn) closeSCOConnection;

@end


//===============================================
//  Delegate Inteface
//===============================================
@interface NSObject( IOBluetoothRFCOMMAudioDelegate )

- (void) audioDevice:(id)device deviceConnectionOpened:(IOReturn)status;
- (void) audioDevice:(id)device deviceConnectionClosed:(IOReturn)status;

- (void) audioDevice:(id)device rfcommChannelOpened:(IOReturn)status;
- (void) audioDevice:(id)device rfcommChannelClosed:(IOReturn)status;

- (void) audioDevice:(id)device serviceLevelConnectionOpened:(IOReturn)status;
- (void) audioDevice:(id)device serviceLevelConnectionComplete:(IOReturn)status;
- (void) audioDevice:(id)device serviceLevelConnectionClosed:(IOReturn)status;

- (void) audioDevice:(id)device scoConnectionOpened:(IOReturn)status;
- (void) audioDevice:(id)device scoConnectionClosed:(IOReturn)status;

@end

#endif /* BLUETOOTH_VERSION_MAX_ALLOWED >= BLUETOOTH_VERSION_2_0 */

