/*
    File:		IOBluetoothL2CAPChannel.h
    Copyright:	(c) 2012 by Apple, Inc. All rights reserved.
*/
 
#import <Foundation/Foundation.h>
#import <IOKit/IOKitLib.h>
#import <IOKit/IODataQueueShared.h>

#import <IOBluetooth/Bluetooth.h>
#import <IOBluetooth/IOBluetoothUserLib.h>
#import <IOBluetooth/objc/IOBluetoothDevice.h>
#import <IOBluetooth/objc/IOBluetoothObject.h>


#if 0
#pragma mark -
#pragma mark === L2CAP ===
#endif

//===========================================================================================================================
// The following is left in for legacy reasons only. Please ignore.
//===========================================================================================================================

typedef enum IOBluetoothL2CAPChannelEventType {
	kIOBluetoothL2CAPChannelEventTypeData					=	0x0001,
	kIOBluetoothL2CAPChannelEventTypeOpenComplete			=	0x0002,
	kIOBluetoothL2CAPChannelEventTypeClosed					=	0x0003,
	kIOBluetoothL2CAPChannelEventTypeReconfigured			=	0x0004,
	kIOBluetoothL2CAPChannelEventTypeWriteComplete			=	0x0005,
	kIOBluetoothL2CAPChannelEventTypeQueueSpaceAvailable	=	0x0006
} IOBluetoothL2CAPChannelEventType;

typedef struct IOBluetoothL2CAPChannelDataBlock
{
	void 	*dataPtr;
	size_t	dataSize;
} IOBluetoothL2CAPChannelDataBlock;

typedef struct IOBluetoothL2CAPChannelEvent {
	IOBluetoothL2CAPChannelEventType	eventType;
	union
	{
		IOBluetoothL2CAPChannelDataBlock	data;
		void*								writeRefCon;
		UInt8								padding[32];
	} u;
	IOReturn							status;
} IOBluetoothL2CAPChannelEvent;

typedef void (*IOBluetoothL2CAPChannelIncomingDataListener)(IOBluetoothL2CAPChannelRef l2capChannel, void *data, UInt16 length, void *refCon);
typedef void (*IOBluetoothL2CAPChannelIncomingEventListener)(IOBluetoothL2CAPChannelRef l2capChannel, void *refCon, IOBluetoothL2CAPChannelEvent *event);


//--------------------------------------------------------------------------------------------------------------------------
/*!
 	@class IOBluetoothL2CAPChannel
	@abstract An instance of IOBluetoothL2CAPChannel represents a single open L2CAP channel.
	@discussion	A client won't create IOBluetoothL2CAPChannel objects directly.  Instead, the IOBluetoothDevice's 
                L2CAP channel open API is responsible for opening a new L2CAP channel and returning an
                IOBluetoothL2CAPChannel instance representing that newly opened channel.  Additionally, the IOBluetooth
                notification system will send notifications when new L2CAP channels are open (if requested).
                
                After a new L2CAP channel is opened, the L2CAP configuration process will not be completed until an
                incoming data listener is registered with the IOBluetoothL2CAPChannel object.  The reason for this is
                to due to the limited buffering done of incoming L2CAP data.  This way, we avoid the situation where 
                incoming data is received before the client is ready for it.  Once a client is done with an
                IOBluetoothL2CAPChannel that it opened, it should call -closeChannel.  Additionally, if the client
                does not intend to use the connection to the remote device any further, it should call -closeConnection
                on the IOBluetoothDevice object.
*/

@interface IOBluetoothL2CAPChannel : IOBluetoothObject <NSPortDelegate>
{
    NSPort										*mDataAvailablePort;
    IODataQueueMemory							*mIncomingDataQueue;
    IOBluetoothDevice							*mDevice;
    
	BOOL										mIncomingChannel;
	
	id											mL2CAPChannelConnectionHandler;

    IOBluetoothL2CAPChannelIncomingDataListener	mIncomingDataListener;
    void										*mIncomingDataListenerRefCon;

    IOBluetoothL2CAPChannelIncomingEventListener	mEventDataListener;
    void											*mEventDataListenerRefCon;
	
    BluetoothL2CAPPSM							mChannelPSM;
    
	BluetoothL2CAPChannelID						mLocalChannelID;
    BluetoothL2CAPChannelID						mRemoteChannelID;
    
	BOOL										mIsClosed;
    IOBluetoothObjectID							mObjectID;
    
    id                                          _mReserved;
}

/*!
    @method	registerForChannelOpenNotifications:selector:
	@abstract	Allows a client to register for L2CAP channel open notifications for any L2CAP channel.
	@discussion	The given selector will be called on the target object whenever any L2CAP channel is opened.
				The selector should accept two arguments.  The first is the user notification object.  The second
				is the IOBluetoothL2CAPChannel that was opened.
	@param		object		Target object
	@param		selector	Selector to be called on the target object when a new L2CAP channel is opened.
	@result		Returns an IOBluetoothUserNotification representing the outstanding L2CAP channel notification.
				To unregister the notification, call -unregister on the resulting IOBluetoothUserNotification 
				object.  If an error is encountered creating the notification, nil is returned.  The returned
				IOBluetoothUserNotification will be valid for as long as the notification is registered.  It is
				not necessary to retain the result.  Once -unregister is called on it, it will no longer be valid.
*/

+ (IOBluetoothUserNotification *)registerForChannelOpenNotifications:(id)object selector:(SEL)selector;

/*!
    @method	registerForChannelOpenNotifications:selector:withPSM:direction:
	@abstract	Allows a client to register for L2CAP channel open notifications for certain types of
				L2CAP channels.
	@discussion	The given selector will be called on the target object whenever an L2CAP channel with the given
				attributes is opened.  The selector should accept two arguments.  The first is the user 
				notification object.  The second is the IOBluetoothL2CAPChannel that was opened.
	@param		object		Target object
	@param		selector	Selector to be called on the target object when a new L2CAP channel is opened.
	@param		psm			PSM to match a new L2CAP channel.  If the PSM doesn't matter, 0 may be passed in.
	@param		inDirection	The desired direction of the L2CAP channel - kIOBluetoothUserNotificationChannelDirectionAny
				if the direction doesn't matter.
	@result		Returns an IOBluetoothUserNotification representing the outstanding L2CAP channel notification.
				To unregister the notification, call -unregister on the resulting IOBluetoothUserNotification 
				object.  If an error is encountered creating the notification, nil is returned.  The returned
				IOBluetoothUserNotification will be valid for as long as the notification is registered.  It is
				not necessary to retain the result.  Once -unregister is called on it, it will no longer be valid.
*/

+ (IOBluetoothUserNotification *)registerForChannelOpenNotifications:(id)object selector:(SEL)selector withPSM:(BluetoothL2CAPPSM)psm direction:(IOBluetoothUserNotificationChannelDirection)inDirection;

/*!
    @method	withObjectID:
	@abstract	Returns the IObluetoothL2CAPChannel with the given IOBluetoothObjectID.
	@discussion	The IOBluetoothObjectID can be used as a global reference for a given IOBluetoothL2CAPChannel.  It allows
				two separate applications to refer to the same IOBluetoothL2CAPChannel object.
	@param		objectID	IOBluetoothObjectID of the desired IOBluetoothL2CAPChannel.
	@result		Returns the IOBluetoothL2CAPChannel that matches the given IOBluetoothObjectID if one exists.
				If no matching L2CAP channel exists, nil is returned.
*/

+ (instancetype)withObjectID:(IOBluetoothObjectID)objectID;

/*!
    @method		closeChannel
	@abstract	Initiates the close process on an open L2CAP channel.
    @discussion	This method may only be called by the client that opened the channel in the first place.  In the future
                asynchronous and synchronous versions will be provided that let the client know when the close process
                has been finished.
	@result		Returns kIOReturnSuccess on success.
*/

- (IOReturn)closeChannel;

/*!
    @method		getOutgoingMTU
	@abstract	Returns the current outgoing MTU for the L2CAP channel.
    @discussion	The outgoing MTU represents the maximum L2CAP packet size for packets being sent to the remote device.
	@result		Returns the current outgoing MTU for the L2CAP channel.
*/

@property(readonly) BluetoothL2CAPMTU outgoingMTU;
- (BluetoothL2CAPMTU)getOutgoingMTU DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @method		getIncomingMTU
	@abstract	Returns the current incoming MTU for the L2CAP channel.
    @discussion	The incoming MTU represents the maximum L2CAP packet size for packets being sent by the remote device.
	@result		Returns the current incoming MTU for the L2CAP channel.
*/

@property(readonly) BluetoothL2CAPMTU incomingMTU;
- (BluetoothL2CAPMTU)getIncomingMTU DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @method		requestRemoteMTU:
	@abstract	Initiates the process to reconfigure the L2CAP channel with a new outgoing MTU.
    @discussion	Currently, this API does not give an indication that the re-config process has completed.  In
                the future additional API will be available to provide that information both synchronously and
                asynchronously.
    @param		remoteMTU	The desired outgoing MTU. 
	@result		Returns kIOReturnSuccess if the channel re-configure process was successfully initiated.
*/

- (IOReturn)requestRemoteMTU:(BluetoothL2CAPMTU)remoteMTU;

/*!
    @method		writeAsync:length:refcon:
	@abstract	Writes the given data over the target L2CAP channel asynchronously to the remote device.
    @discussion	The length of the data may not exceed the L2CAP channel's ougoing MTU.  When the data has 
				been successfully passed to the hardware to be transmitted, the delegate method 
				-l2capChannelWriteComplete:refcon:status: will be called with the refcon passed 
				into this method.

				NOTE: This method is only available in Mac OS X 10.2.5 (Bluetooth v1.2) or later.
    @param		data	Pointer to the buffer containing the data to send.
    @param		length 	The length of the given data buffer.
	@param		refcon	User supplied value that gets passed to the write callback.
	@result		Returns kIOReturnSuccess if the data was buffered successfully.
*/

- (IOReturn)writeAsync:(void *)data length:(UInt16)length refcon:(void*)refcon;

/*!
    @method		writeSync:length:
	@abstract	Writes the given data synchronously over the target L2CAP channel to the remote device.
    @discussion	The length of the data may not exceed the L2CAP channel's ougoing MTU.  This method will
				block until the data has been successfully sent to the hardware for transmission (or an error
				occurs).

				NOTE: This method is only available in Mac OS X 10.2.5 (Bluetooth v1.2) or later.
    @param		data	Pointer to the buffer containing the data to send.
    @param		length 	The length of the given data buffer.
	@result		Returns kIOReturnSuccess if the data was written successfully.
*/

- (IOReturn)writeSync:(void *)data length:(UInt16)length;

/*!
    @method		setDelegate:
	@abstract	Allows an object to register itself as client of the L2CAP channel.
    @discussion A channel delegate is the object the L2CAP channel uses as target for data and events. The
				developer will implement only the the methods he/she is interested in. A list of the
				possible methods is at the end of this file in the definition of the informal protocol
				IOBluetoothL2CAPChannelDelegate.
                A newly opened L2CAP channel will not complete its configuration process until the client
                that opened it registers a connectionHandler.  This prevents that case where incoming
                data is received before the client is ready. 

				NOTE: This method is only available in Mac OS X 10.2.5 (Bluetooth v1.2) or later.
	@param		channelDelegate	the object that will play the role of channel delegate [NOTE the l2cap channel will retain the delegate].
	@result		Returns kIOReturnSuccess if the delegate is successfully registered.
*/

- (IOReturn)setDelegate:(id)channelDelegate;

/*!
    @method		setDelegate:withConfiguration:
	@abstract	Allows an object to register itself as client of the L2CAP channel.
    @discussion A channel delegate is the object the L2CAP channel uses as target for data and events. The
				developer will implement only the the methods he/she is interested in. A list of the
				possible methods is at the end of this file in the definition of the informal protocol
				IOBluetoothL2CAPChannelDelegate.
                A newly opened L2CAP channel will not complete its configuration process until the client
                that opened it registers a connectionHandler.  This prevents that case where incoming
                data is received before the client is ready. 

				NOTE: This method is only available in Mac OS X 10.5 (Bluetooth v2.0) or later.
	@param		channelDelegate	the object that will play the role of channel delegate.
	@param		channelConfiguration the dictionary that describes the initial configuration for
				the channel.
	@result		Returns kIOReturnSuccess if the delegate is successfully registered.
*/

- (IOReturn)setDelegate:(id)channelDelegate withConfiguration:(NSDictionary*)channelConfiguration;

/*!
 @method		delegate
 @abstract		Returns the currently assigned delegate
 @discussion	An incoming channel is one that was initiated by a remote device.
 @result		Returns the current delegate, or nil if one is not set.
 */
- (id) delegate;

/*!
    @method		getDevice
	@abstract	Returns the IOBluetoothDevice to which the target L2CAP channel is open.
	@result		Returns the IOBluetoothDevice to which the target L2CAP channel is open.
*/

@property(readonly, retain) IOBluetoothDevice *device;
- (IOBluetoothDevice *)getDevice DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @method		getObjectID
	@abstract	Returns the IOBluetoothObjectID of the given IOBluetoothL2CAPChannel.
    @discussion	The IOBluetoothObjectID can be used as a global reference for a given IOBluetoothL2CAPChannel.  It allows
				two separate applications to refer to the same IOBluetoothL2CAPChannel.
	@result		Returns the IOBluetoothObjectID of the given IOBluetoothL2CAPChannel.
*/

@property(readonly, assign) IOBluetoothObjectID objectID;
- (IOBluetoothObjectID)getObjectID DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @method		getPSM
	@abstract	Returns the PSM for the target L2CAP channel.
	@result		Returns the PSM for the target L2CAP channel.
*/

@property(readonly, assign) BluetoothL2CAPPSM PSM;
- (BluetoothL2CAPPSM)getPSM DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @method		getLocalChannelID
	@abstract	Returns the local L2CAP channel ID for the target L2CAP channel.
	@result		Returns the local L2CAP channel ID for the target L2CAP channel.
*/

@property(readonly, assign) BluetoothL2CAPChannelID localChannelID;
- (BluetoothL2CAPChannelID)getLocalChannelID DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @method		getRemoteChannelID
	@abstract	Returns the remote L2CAP channel ID for the target L2CAP channel.
	@result		Returns the remote L2CAP channel ID for the target L2CAP channel.
*/

@property(readonly, assign) BluetoothL2CAPChannelID remoteChannelID;
- (BluetoothL2CAPChannelID)getRemoteChannelID DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @method		isIncoming
	@abstract	Returns TRUE if the channel is an incoming channel.
    @discussion	An incoming channel is one that was initiated by a remote device.
	@result		Returns TRUE if the channel is an incoming channel.
*/

- (BOOL)isIncoming;

/*!
    @method		registerForChannelCloseNotification:selector:
	@abstract	Allows a client to register for a channel close notification.
    @discussion	The given selector will be called on the target observer when the L2CAP channel is closed.
				The selector should contain two arguments.  The first is the user notification object. The second
				is the IOBluetoothL2CAPChannel that was closed.
	@param		observer	Target observer object
	@param		inSelector	Selector to be sent to the observer when the L2CAP channel is closed.
	@result		Returns an IOBluetoothUserNotification representing the outstanding L2CAP channel close notification.
				To unregister the notification, call -unregister of the returned IOBluetoothUserNotification 
				object.  If an error is encountered creating the notification, nil is returned.
*/

- (IOBluetoothUserNotification *)registerForChannelCloseNotification:(id)observer selector:(SEL)inSelector;
@end

// Informal protocol to describe the L2CAP channel delegate methods:
// If the developer wishes to take advantage of the asynchronous API in Objective C
// these are the methods that may be implemented:

@protocol IOBluetoothL2CAPChannelDelegate
@optional
- (void)l2capChannelData:(IOBluetoothL2CAPChannel*)l2capChannel data:(void *)dataPointer length:(size_t)dataLength;
- (void)l2capChannelOpenComplete:(IOBluetoothL2CAPChannel*)l2capChannel status:(IOReturn)error;
- (void)l2capChannelClosed:(IOBluetoothL2CAPChannel*)l2capChannel;
- (void)l2capChannelReconfigured:(IOBluetoothL2CAPChannel*)l2capChannel;
- (void)l2capChannelWriteComplete:(IOBluetoothL2CAPChannel*)l2capChannel refcon:(void*)refcon status:(IOReturn)error;
- (void)l2capChannelQueueSpaceAvailable:(IOBluetoothL2CAPChannel*)l2capChannel;
@end

extern NSString * const IOBluetoothL2CAPChannelPublishedNotification;
extern NSString * const IOBluetoothL2CAPChannelTerminatedNotification;

/* Deprecated API */

@interface NSObject( IOBluetoothL2CAPChannelDeprecated )

- (IOReturn)registerIncomingDataListener:(IOBluetoothL2CAPChannelIncomingDataListener)listener refCon:(void *)refCon DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (IOReturn)write:(void *)data length:(UInt16)length DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
+ (IOBluetoothL2CAPChannel *)withL2CAPChannelRef:(IOBluetoothL2CAPChannelRef)l2capChannelRef DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;
- (IOBluetoothL2CAPChannelRef)getL2CAPChannelRef DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

@end
