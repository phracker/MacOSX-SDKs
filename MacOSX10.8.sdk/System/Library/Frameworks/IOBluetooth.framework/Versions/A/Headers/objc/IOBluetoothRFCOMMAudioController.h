
/*!
	@header
	@abstract	Baseclass of Headset and Handsfree objects.  Implements
				basic interface to the audio driver and remote device
	@copywrite	(C) 2006 by Apple Computer, Inc., all rights reserved.
 	@discussion
				 ***		DEPRECATED IN 10.7
				 ***		You should transition your code to IOBluetoothHandsFree class.
				 ***		This API may be removed any time in the future. 
 */

#import <Foundation/Foundation.h>
#import <IOBluetooth/Bluetooth.h>
#import <CoreAudio/AudioHardware.h>

@class IOBluetoothDevice;
@class IOBluetoothRFCOMMChannel;
@class IOBluetoothUserNotification;
@class IOBluetoothSCOAudioDevice;
@class IOBluetoothSDPServiceRecord;

@protocol IOBluetoothRFCOMMAudioDelegate;

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

// Notification when the button is pressed
#define kIOBluetoothRFCOMMAudioControllerButtonPressedNotification	@"IOBluetoothRFCOMMAudioControllerButtonPressed"

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

	BOOL							mIsInternalVolumeChange;
	
	void *							mReserved;
	
    id <IOBluetoothRFCOMMAudioDelegate> mDelegate;	
}

@property(assign) id delegate;

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
					 delegate: (id)inDelegate DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

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
						delegate: (id)inDelegate DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

// ---------------------------------------------------
// CoreAudio stuff
//

/*!
 @method		getDriverIDForDevice
 @abstract		Get the driver ID string used by the device
 @discussion	
 @result		The driver ID this object is attached to, nil if not attached
 */
+ (NSString *)getDriverIDForDevice:(IOBluetoothDevice*)inDevice DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
	@method		getAudioDeviceID
	@abstract	Get the audio device ID this object is attached to
	@discussion	
	@result		The audio device ID this object is attached to, NULL if not attached
*/
- (AudioDeviceID) getAudioDeviceID DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;


// ---------------------------------------------------
// Device connection
//
/*!
	@method		getBluetoothDevice
	@abstract	Get the bluetooth device associated with this device
	@discussion	
	@result		The bluetooth device this object is using, otherwise NULL
*/
- (IOBluetoothDevice *) getBluetoothDevice DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
	@method		isDeviceConnected
	@abstract	Get the connection state of the bluetooth device being used
	@discussion	
	@result		The connection state of the device, FALSE if no device or not connected
*/
- (BOOL) isDeviceConnected DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
	@method		openDeviceConnection
	@abstract	Open the bluetooth device connection
	@discussion	Look for final result in the provided delegate method
	@result		The result of the first stage of connection, kIOReturnNoDevice if no device.
*/
- (IOReturn) openDeviceConnection DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
	@method		closeDeviceConnection
	@abstract	Close the bluetooth device connection
	@discussion	Look for final result in the provided delegate method
	@result		The result of the first stage of disconnection, kIOReturnNoDevice if no device.
*/
- (IOReturn) closeDeviceConnection DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;



// ---------------------------------------------------
// RFCOMM connection
//
/*!
	@method		getIncomingRFCOMMChannelID
	@abstract	Access to the RFCOMM ID as specified on init for incoming device connections
	@discussion	
	@result		The RFCOMM channel ID of the remote device, 0 if none
*/
- (BluetoothRFCOMMChannelID) getIncomingRFCOMMChannelID DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
	@method		getOutgoingRFCOMMChannelID
	@abstract	Access to the RFCOMM ID as specified in the SDP of the device for outgoing connections
	@discussion	
	@result		The RFCOMM channel ID of the remote device, 0 if none
*/
- (BluetoothRFCOMMChannelID) getOutgoingRFCOMMChannelID DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
	@method		isRFCOMMChannelOpen
	@abstract	Check if the RFCOMM channel is open
	@discussion	
	@result		TRUE if open, FALSE if closed or device is nil
*/
- (BOOL) isRFCOMMChannelOpen DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
	@method		setRFCOMMChannel
	@abstract	Set the RFCOMM channel to use
	@discussion	
	@param		rfcommChannel The channel to use or nil to release the current one
*/
- (void) setRFCOMMChannel:(IOBluetoothRFCOMMChannel *)rfcommChannel DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
	@method		openRFCOMMChannel
	@abstract	Open rfcomm channel on current bluetooth device on the outgoing RFCOMM channel ID 
	@discussion	Look for final result in the provided delegate method
	@result		Result will be value returned from IOBluetoothDevice openRFCOMMChannelAsync if device is valid, kIOReturnError if no device is set
*/
- (IOReturn) openRFCOMMChannel DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
	@method		closeRFCOMMChannel
	@abstract	Close the rfcomm channel
	@discussion	Look for final results in the provided delegate method
	@result		Result will be value returned from the channels' "closeChannel" method, kIOReturnNotAttached if no channel is set
*/
- (IOReturn) closeRFCOMMChannel DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
	@method		sendRFCOMMData:length:
	@abstract	Send RFCOMM data to the device
	@discussion	
	@param		data Data to be sent to device
	@param		length Length of the data
	@result		Result will be value returned from the channels' "writeAsync" method, kIOReturnNotAttached if no channel is set
*/
- (IOReturn) sendRFCOMMData:(const void *)data length:(uint16_t)length DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

//
//  Various RFCOMM delegate methods.  Developers, you can override the rfcommChannelData method to 
// catch and deal with incoming commands from the remote device.  This object does nothing with the
// data it receives.
//
//	Its also suggested that you use the standard delegate method below and not touch these guys unless
// you absolutely have to.
//
- (void) handleIncomingRFCOMMChannelOpened:(IOBluetoothUserNotification *)notification channel:(IOBluetoothRFCOMMChannel *)channel DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;
- (void) rfcommChannelOpenComplete:(IOBluetoothRFCOMMChannel *)rfcommChannel status:(IOReturn)status DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;
- (void) rfcommChannelClosed:(IOBluetoothRFCOMMChannel *)rfcommChannel DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;
- (void) rfcommChannelData:(IOBluetoothRFCOMMChannel *)rfcommChannel data:(void *)data length:(size_t)length DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;


// ---------------------------------------------------
// SCO connection
//
/*!
	@method		isSCOConnected
	@abstract	Check if the SCO connection is open
	@discussion	
	@result		TRUE if open, FALSE if closed or device is nil
*/
- (BOOL) isSCOConnected DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
	@method		openSCOConnection
	@abstract	Open the SCO connection
	@discussion	Look for final result in the provided delegate method
	@result		kIOReturnSuccess on success or if still open, various errors if failed
*/
- (IOReturn) openSCOConnection DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
	@method		closeSCOConnection
	@abstract	Close the SCO connection
	@discussion	Look for final results in the provided delegate method
	@result		kIOReturnSuccess on success or if already closed, various errors if failed
*/
- (IOReturn) closeSCOConnection DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

@end


//===============================================
//  Delegate Inteface - DEPRECATED in 10.7
//===============================================
@protocol IOBluetoothRFCOMMAudioDelegate <NSObject>
@optional
- (void) audioDevice:(id)device deviceConnectionOpened:(IOReturn)status;
- (void) audioDevice:(id)device deviceConnectionClosed:(IOReturn)status;

- (void) audioDevice:(id)device rfcommChannelOpened:(IOReturn)status;
- (void) audioDevice:(id)device rfcommChannelClosed:(IOReturn)status;

- (void) audioDevice:(id)device serviceLevelConnectionOpened:(IOReturn)status;
- (void) audioDevice:(id)device serviceLevelConnectionClosed:(IOReturn)status;

- (void) audioDevice:(id)device scoConnectionOpening:(IOReturn)status;
- (void) audioDevice:(id)device scoConnectionOpened:(IOReturn)status;
- (void) audioDevice:(id)device scoConnectionClosed:(IOReturn)status;
- (void) audioDevice:(id)device scoDone:(IOReturn)status;

- (void) audioDevice:(id)device scoAudioDeviceActive:(IOReturn)status;
- (void) audioDevice:(id)device scoAudioDeviceInactive:(IOReturn)status;

- (void) audioDevice:(id)device disconnectedError:(IOReturn)status;

@end
