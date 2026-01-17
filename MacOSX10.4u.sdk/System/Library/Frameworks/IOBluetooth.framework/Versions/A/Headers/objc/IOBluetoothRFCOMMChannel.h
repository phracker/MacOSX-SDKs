/*
    File:		IOBluetoothRFCOMMChannel.h
    Copyright:	© 2002 by Apple Computer, Inc. All rights reserved.
*/
 
#import <Foundation/Foundation.h>
#import <IOKit/IOKitLib.h>
#import <IOKit/IODataQueueShared.h>
#import <IOBluetooth/Bluetooth.h>
#import <IOBluetooth/IOBluetoothUserLib.h>
#import <IOBluetooth/objc/IOBluetoothObject.h>
#import <IOBluetooth/objc/IOBluetoothUserNotification.h>

@class IOBluetoothDevice;
@class IOBluetoothL2CAPChannel;
@class IOBluetoothRFCOMMConnection;


/*!
    @class IOBluetoothRFCOMMChannel
    @abstract An instance of this class represents an rfcomm channel as defined by the Bluetooth SDP spec..
    @discussion An RFCOMM channel object can be obtained by opening an rfcomm channel in a device, or
    by requesting a notification when a channel is created (this is commonly used to provide services).
*/

@interface IOBluetoothRFCOMMChannel : IOBluetoothObject
{
    BOOL											mChannelIsOpen;
    UInt16											mMTU;
    BOOL											mIsIncoming;

    IOBluetoothDevice								*mDevice;
    IOBluetoothL2CAPChannel							*mL2Channel;

    NSPort											*mDataAvailablePort;
    IODataQueueMemory								*mIncomingDataQueue;

	id												mRFCOMMChannelConnectionHandler;
	
    IOBluetoothRFCOMMChannelIncomingDataListener	mIncomingDataListener;
    void											*mIncomingDataListenerRefCon;

    IOBluetoothRFCOMMChannelIncomingEventListener	mEventDataListener;
    void											*mEventDataListenerRefCon;
    
    IOBluetoothObjectID								mObjectID;
    
    BluetoothRFCOMMChannelID                                                    mChannelID;
    
    void											*_mReserved;
}

/*!
	@method	registerForChannelOpenNotifications:selector:
	@abstract	Allows a client to register for RFCOMM channel open notifications for any RFCOMM channel.
	@discussion	The given selector will be called on the target object whenever any RFCOMM channel is opened.
				The selector should accept two arguments.  The first is the user notification object.  The second
				is the IOBluetoothRFCOMMChannel that was opened.
	@param		rfcommChannelRef IOBluetoothRFCOMMChannelRef for which an IOBluetoothRFCOMMChannel * is desired.
	@param		object		Target object
	@param		selector	Selector to be called on the target object when a new RFCOMM channel is opened.
				the format for the selector is: 
				-(void) selectorName:(IOBluetoothUserNotification *)inNotification channel:(IOBluetoothRFCOMMChannel *)newChannel
	@result		Returns an IOBluetoothUserNotification representing the outstanding RFCOMM channel notification.
				To unregister the notification, call -unregister on the resulting IOBluetoothUserNotification 
				object.  If an error is encountered creating the notification, nil is returned.  The returned
				IOBluetoothUserNotification will be valid for as long as the notification is registered.  It is
				not necessary to retain the result.  Once -unregister is called on it, it will no longer be valid.
*/

+ (IOBluetoothUserNotification *)registerForChannelOpenNotifications:(id)object selector:(SEL)selector;

/*!
    @method	registerForChannelOpenNotifications:selector:
	@abstract	Allows a client to register for RFCOMM channel open notifications for certain types of
				RFCOMM channels.
	@discussion	The given selector will be called on the target object whenever an RFCOMM channel with the given
				attributes is opened.  The selector should accept two arguments.  The first is the user 
				notification object.  The second is the IOBluetoothL2CAPChannel that was opened.
	@param		object		Target object
	@param		selector	Selector to be called on the target object when a new RFCOMM channel is opened.
				the format for the selector is: 
				-(void) selectorName:(IOBluetoothUserNotification *)inNotification channel:(IOBluetoothRFCOMMChannel *)newChannel
	@param		channeLID	RFCOMM channel ID to match a new RFCOMM channel.  If the channel ID doesn't matter, 0 may be passed in.
	@param		inDirection	The desired direction of the RFCOMM channel - kIOBluetoothUserNotificationChannelDirectionAny
				if the direction doesn't matter.
	@result		Returns an IOBluetoothUserNotification representing the outstanding RFCOMM channel notification.
				To unregister the notification, call -unregister on the resulting IOBluetoothUserNotification 
				object.  If an error is encountered creating the notification, nil is returned.  The returned
				IOBluetoothUserNotification will be valid for as long as the notification is registered.  It is
				not necessary to retain the result.  Once -unregister is called on it, it will no longer be valid.
*/

+ (IOBluetoothUserNotification *)registerForChannelOpenNotifications:(id)object selector:(SEL)selector withChannelID:(BluetoothRFCOMMChannelID)channelID direction:(IOBluetoothUserNotificationChannelDirection)inDirection;

/*!	@method	withRFCOMMChannelRef:
	@abstract	Method call to convert an IOBluetoothRFCOMMChannelRef into an IOBluetoothRFCOMMChannel *.
        @param	rfcommChannelRef IOBluetoothRFCOMMChannelRef for which an IOBluetoothRFCOMMChannel * is desired.
	@result		Returns the IOBluetoothRFCOMMChannel * for the given IOBluetoothRFCOMMChannelRef.
*/
+ (IOBluetoothRFCOMMChannel *)withRFCOMMChannelRef:(IOBluetoothRFCOMMChannelRef)rfcommChannelRef;

/*!
    @method	withObjectID:
	@abstract	Returns the IObluetoothRFCOMMChannel with the given IOBluetoothObjectID.
	@discussion	The IOBluetoothObjectID can be used as a global reference for a given IObluetoothRFCOMMChannel.  It allows
				two separate applications to refer to the same IObluetoothRFCOMMChannel object.
	@param		objectID	IOBluetoothObjectID of the desired IObluetoothRFCOMMChannel.
	@result		Returns the IObluetoothRFCOMMChannel that matches the given IOBluetoothObjectID if one exists.
				If no matching RFCOMM channel exists, nil is returned.
*/

+ (IOBluetoothRFCOMMChannel *)withObjectID:(IOBluetoothObjectID)objectID;

/*!	@method	getRFCOMMChannelRef
	@abstract	Returns an IOBluetoothRFCOMMChannelRef representation of the target IOBluetoothRFCOMMChannel object.
	@result		Returns an IOBluetoothRFCOMMChannelRef representation of the target IOBluetoothRFCOMMChannel object.
*/
- (IOBluetoothRFCOMMChannelRef)getRFCOMMChannelRef;

/*!
    @method closeChannel
    @abstract Close the channel.
    @result An error code value. 0 if successful.
*/

- (IOReturn)closeChannel;

/*!
    @method isOpen
    @abstract Returns the state of the channel. 
    @discussion	note that "not open" means closed, opening and closing.
    @result TRUE if the channel state is open,  FALSE otherwise.
*/

- (BOOL)isOpen;

/*!
    @method getMTU
    @abstract Returns the channel maximum transfer unit.
    @discussion Returns the length of the largest chunk of data that this channel can carry. If the
    caller wishes to use the write:length:sleep: api the length of the data can not be bigger than
    the channel MTU (maximum transfer unit). 
    @result Channel MTU size .
*/

- (BluetoothRFCOMMMTU)getMTU;

/*!
    @method isTransmissionPaused
    @abstract Returns TRUE if flow control is off.
    @discussion Returns true if the remote device flow control is stopping out transmission. This is
            useful because we do not buffer data, we stop the transmitting actor. With this method
            the transmitter can check if sending data is going to be successful or is going to block.
    @result TRUE if the action of sending data will block the current thread, FALSE otherwise.

*/

- (BOOL)isTransmissionPaused;

/*!
    @method  write:length:sleep:
    @abstract Sends a block of data in the channel syncronously.
    @discussion	***WARNING*** This method is being deprecated in favor of -writeSync:... and -writeAsync:...
				Sends data tough the channel. The number of bytes to be sent must not exceed the channel MTU. 
				If the return value is an error condition none of the data was sent.
    @param data is a pointer to the data buffer to be sent.
    @param length the length of the buffer to be sent (in bytes).
    @param sleep is a boolean if set to TRUE the call will wait until it is possible to send data.
    If set to FALSE and it is not possible to send data the method will return immediately with an
    error.
    @result An error code value. 0 if successful. 
*/

- (IOReturn)write:(void *)data length:(UInt16)length sleep:(BOOL)sleep;

#if BLUETOOTH_VERSION_MAX_ALLOWED >= BLUETOOTH_VERSION_1_2

/*!
    @method  writeAsync:length:refcon:
    @abstract Sends a block of data in the channel asynchronously.
    @discussion The number of bytes to be sent must not exceed the channel MTU. 
				If the return value is an error condition none of the data was sent.  Once the data
				has been successfully passed to the hardware to be transmitted, the delegate method
				-rfcommChannelWriteComplete:refcon:status: will be called with the refcon that was passed
				to this method.

				NOTE: This method is only available in Mac OS X 10.2.5 (Bluetooth v1.2) or later.
    @param		data A pointer to the data buffer to be sent.
    @param		length The length of the buffer to be sent (in bytes).
	@param		refcon User supplied value that gets passed to the write callback.
    @result		Returns kIOReturnSuccess if the data was buffered successfully. 
*/

- (IOReturn)writeAsync:(void *)data length:(UInt16)length refcon:(void*)refcon;

/*!
    @method  writeSync:length:refcon:
    @abstract Sends a block of data in the channel synchronously.
    @discussion	Sends data tough the channel. The number of bytes to be sent must not exceed the channel MTU. 
				If the return value is an error condition none of the data was sent.  This method will
				block until the data has been successfully sent to the hardware for transmission (or until
				an error occurs).

				NOTE: This method is only available in Mac OS X 10.2.5 (Bluetooth v1.2) or later.
    @param		data A pointer to the data buffer to be sent.
    @param		length The length of the buffer to be sent (in bytes).
	@result		Returns kIOReturnSuccess if the data was written successfully.
*/

- (IOReturn)writeSync:(void *)data length:(UInt16)length;

#endif /* BLUETOOTH_VERSION_MAX_ALLOWED >= BLUETOOTH_VERSION_1_2 */

/*!
    @method  writeSimple:length:sleep:
    @abstract Sends a block of data in the channel.
    @discussion ***WARNING*** This method is being deprecated in favor of -writeSync:... and -writeAsync:...
				Sends data tough the channel. The number of bytes to be sent is arbitrary. The caller
				does not have to worry about the MTU. 
    @param data a pointer to the data buffer to be sent.
    @param length the length of the buffer to be sent (in bytes).
    @param sleep a boolean if set to TRUE the call will wait until it is possible to send all the data.
    @param a UInt32 pointer in which the caller received the nuber of bytes sent.
    If set to FALSE and it is not possible to send part of the data the method will return immediately.
    @result An error code value. 0 if successful.
*/

- (IOReturn)writeSimple:(void *)data length:(UInt16)length sleep:(BOOL)sleep bytesSent:(UInt32 *)numBytesSent;

/*!
    @method  setSerialParameters:dataBits:parity:stopBits:
    @abstract Changes the parameters of the serial connection. 
    @param speed the baudrate.
    @param nBits number of data bits.
    @param parity the type of parity can be NoParity, OddParity, EvenParity or MaxParity.
    @param bitStop number of stop bits.
    @result An error code value. 0 if successful. 
*/

- (IOReturn)setSerialParameters:(UInt32)speed dataBits:(UInt8)nBits parity:(BluetoothRFCOMMParityType)parity stopBits:(UInt8)bitStop;

/*!
    @method  sendRemoteLineStatus:
    @abstract Sends an error to the remote side. 
    @param lineStatus the error type. The error code can be NoError, OverrunError, ParityError or FramingError.
    @result An error code value. 0 if successful. 
*/

- (IOReturn)sendRemoteLineStatus:(BluetoothRFCOMMLineStatus)lineStatus;

/*!
    @method  registerIncomingDataListener:refCon:refCon:
    @abstract Registers a callback for incoming data. 
    @discussion	***WARNING*** This method is being deprecated in favor of -setDelegate:
				Registers a callback for the incoming data. The form for the callback is:
    
    <br>void function(IOBluetoothRFCOMMChannelRef rfcommChannel, void *data, UInt16 length, void *refCon)<br>
    
    where rfcommChannel is the refernce to the channel that received data, data is a buffer with the received data, length is the buffer length
    (in bytes) and refCon is a user defined void* (maybe the reference to the object to call back ?).
    @param listener is the callback function.
    @param refCon is a void*, its meaning is up to the developer. This parameter will be passed back as last parameter of
    the callback function.
    @result An error code value. 0 if successful. 
*/

- (IOReturn)registerIncomingDataListener:(IOBluetoothRFCOMMChannelIncomingDataListener)listener refCon:(void *)refCon;

/*!
    @method  registerIncomingEventListener:refCon:refCon:
    @abstract Registers a callback for events. 
    @discussion ***WARNING*** This method is being deprecated in favor of -setDelegate:
		Registers a callback for events generated by the RFCOMM channel. The form for the callback is:
    
    <br>void function(IOBluetoothRFCOMMChannelRef rfcommChannel, void *refCon, IOBluetoothRFCOMMChannelEvent *event)<br>
    
    where rfcommChannel is the refernce to the channel that generated the event, refCon is a user defined void* (maybe the reference to the object to
    call back ?) and event is the generated event. There are three types of events available:

    <br>
    kIOBluetoothRFCOMMNewDataEvent when new data is received.<br>
    kIOBluetoothRFCOMMFlowControlChangedEvent change of flow control.<br>
    kIOBluetoothRFCOMMChannelTerminatedEvent when the rfcomm channel is no more valid.<br>
    <br>
    
    Note that the kIOBluetoothRFCOMMNewDataEvent provides the same functionality
    of the data listener callback. This means that if the developer has both an event callback and a datalistener callback both
    functions will be called when new data arrives. It is up to the developer to properly filter the events (or better to use only
    one callback). For a better descriptions of the events and the event structure see IOBluetoothUserLib.h.
    @param listener is the callback function.
    @param refCon is a void*, its meaning is up to the developer. This parameter will be passed back as second parameter of
    the callback function.
    @result An error code value. 0 if successful. 
*/

- (IOReturn)registerIncomingEventListener:(IOBluetoothRFCOMMChannelIncomingEventListener)listener refCon:(void *)refCon;

#if BLUETOOTH_VERSION_MAX_ALLOWED >= BLUETOOTH_VERSION_1_2

/*!
    @method		setDelegate:
	@abstract	Allows an object to register itself as a client of the RFCOMM channel.
    @discussion A channel delegate is the object the RFCOMM channel uses as target for data and events. The
				developer will implement only the the methods he/she is interested in. A list of the
				possible methods is at the end of this file in the definition of the informal protocol
				IOBluetoothRFCOMMChannelDelegate.

				NOTE: This method is only available in Mac OS X 10.2.5 (Bluetooth v1.2) or later.
	@param		delegate	The object that will play the role of channel delegate.
	@result		Returns kIOReturnSuccess if the delegate is successfully registered.
*/

- (IOReturn)setDelegate:(id)delegate;

#endif /* BLUETOOTH_VERSION_MAX_ALLOWED >= BLUETOOTH_VERSION_1_2 */

/*!
    @method channelNumber
    @abstract Returns the object rfcomm channel ID. 
    @result the RFCOMM channel number .
*/

- (BluetoothRFCOMMChannelID)getChannelID;

/*!
    @method isIncoming
    @abstract	Returns the direction of the channel.  An incoming channel is one that was opened by the remote
                device. 
    @result 	Returns TRUE if the channel was opened by the remote device, FALSE if the channel was opened by this object.
*/

- (BOOL)isIncoming;

/*!
    @method getDevice
    @abstract Returns the Bluetooth Device that carries the rfcomm data. 
    @result the IOBluetoothDevice object .
*/

- (IOBluetoothDevice *)getDevice;

/*!
    @method		getObjectID
	@abstract	Returns the IOBluetoothObjectID of the given IOBluetoothRFCOMMChannel.
    @discussion	The IOBluetoothObjectID can be used as a global reference for a given IOBluetoothRFCOMMChannel.  It allows
				two separate applications to refer to the same IOBluetoothRFCOMMChannel.
	@result		Returns the IOBluetoothObjectID of the given IOBluetoothRFCOMMChannel.
*/

- (IOBluetoothObjectID)getObjectID;

/*!
    @method		registerForChannelCloseNotification:selector:
	@abstract	Allows a client to register for a channel close notification.
    @discussion	The given selector will be called on the target observer when the RFCOMM channel is closed.
				The selector should contain two arguments.  The first is the user notification object. The second
				is the IOBluetoothRFCOMMChannel that was closed.
	@param		observer	Target observer object
	@param		inSelector	Selector to be sent to the observer when the RFCOMM channel is closed.
	@result		Returns an IOBluetoothUserNotification representing the outstanding RFCOMM channel close notification.
				To unregister the notification, call -unregister of the returned IOBluetoothUserNotification 
				object.  If an error is encountered creating the notification, nil is returned.
*/

- (IOBluetoothUserNotification *)registerForChannelCloseNotification:(id)observer selector:(SEL)inSelector;

@end

#if BLUETOOTH_VERSION_MAX_ALLOWED >= BLUETOOTH_VERSION_1_2

// Informal protocol to describe the RFCOMM channel delegate methods:
// If the developer wishes to take advantage of the asynchronous API in Objective C
// these are the methods that may be implemented:

@protocol IOBluetoothRFCOMMChannelDelegate
- (void)rfcommChannelData:(IOBluetoothRFCOMMChannel*)rfcommChannel data:(void *)dataPointer length:(size_t)dataLength;
- (void)rfcommChannelOpenComplete:(IOBluetoothRFCOMMChannel*)rfcommChannel status:(IOReturn)error;
- (void)rfcommChannelClosed:(IOBluetoothRFCOMMChannel*)rfcommChannel;
- (void)rfcommChannelControlSignalsChanged:(IOBluetoothRFCOMMChannel*)rfcommChannel;
- (void)rfcommChannelFlowControlChanged:(IOBluetoothRFCOMMChannel*)rfcommChannel;
- (void)rfcommChannelWriteComplete:(IOBluetoothRFCOMMChannel*)rfcommChannel refcon:(void*)refcon status:(IOReturn)error;
- (void)rfcommChannelQueueSpaceAvailable:(IOBluetoothRFCOMMChannel*)rfcommChannel;

@end

#endif /* BLUETOOTH_VERSION_MAX_ALLOWED >= BLUETOOTH_VERSION_1_2 */
