/*
    File:		IOBluetoothDevice.h
    Copyright:	(c) 2008 by Apple Computer, Inc. All rights reserved.
*/
 
#import <IOKit/IOKitLib.h>

#import <IOBluetooth/Bluetooth.h>
#import <IOBluetooth/IOBluetoothUserLib.h>
#import <IOBluetooth/objc/IOBluetoothObject.h>
#import <IOBluetooth/objc/IOBluetoothUserNotification.h>

/*!	@header		IOBluetoothDevice.h
	@abstract	An instance of IOBluetoothDevice represents a single remote Bluetooth device.
	@discussion	An IOBluetoothDevice object may exist independent of the existence of a baseband connection
                with the target device.  Through this object you can request baseband connections to be made, 
                request opening and closing of L2CAP and RFCOMM channels.
*/

//====================================================================================================================
//	Defines
//====================================================================================================================

// These are the names of the notifications the device sends using NSNotificationCenter when it is connected
// and disconnected

#define	kIOBluetoothDeviceNotificationNameConnected			@"IOBluetoothDeviceConnected"
#define	kIOBluetoothDeviceNotificationNameDisconnected		@"IOBluetoothDeviceDisconnected"
#define kIOBluetoothDeviceNameChangedNotification			@"IOBluetoothDeviceNameChanged"
#define kIOBluetoothDeviceInquiryInfoChangedNotification	@"IOBluetoothDeviceInquiryInfoChanged"
#define kIOBluetoothDeviceServicesChangedNotification		@"IOBluetoothDeviceServicesChanged"

// These are for the configuration of L2CAP Channels:
#define kIOBluetoothL2CAPChannelMaxAllowedIncomingMTU		@"MaxAllowedIncomingMTU"
#define kIOBluetoothL2CAPChannelDesiredOutgoingMTU			@"DesiredOutgoingMTU"

//====================================================================================================================
//	Forward declarations
//====================================================================================================================

@class IOBluetoothDevice;
@class IOBluetoothL2CAPChannel;
@class IOBluetoothRFCOMMConnection;
@class IOBluetoothRFCOMMChannel;
@class IOBluetoothSDPServiceRecord;
@class IOBluetoothSDPUUID;

//====================================================================================================================
//	Async callbacks informal protocol
//====================================================================================================================

@protocol IOBluetoothDeviceAsyncCallbacks

- (void)remoteNameRequestComplete:(IOBluetoothDevice *)device status:(IOReturn)status;
- (void)connectionComplete:(IOBluetoothDevice *)device status:(IOReturn)status;
- (void)sdpQueryComplete:(IOBluetoothDevice *)device status:(IOReturn)status;

@end

//--------------------------------------------------------------------------------------------------------------------------
/*!
 	@class IOBluetoothDevice
	@abstract An instance of IOBluetoothDevice represents a single remote Bluetooth device.
	@discussion	An IOBluetoothDevice object may exist independent of the existence of a baseband connection
                with the target device.  Using this object, a client can request creation and destruction of baseband
                connections, and request the opening of L2CAP and RFCOMM channels on the remote device.  Many of the other
                APIs in the IOBluetooth framework will return this object, or it's C counterpart (IOBluetoothDeviceRef).
*/

//====================================================================================================================
//	IOBluetoothDevice
//====================================================================================================================

@interface IOBluetoothDevice : IOBluetoothObject <NSCoding, NSSecureCoding>
{
    id									mServerDevice;
    
    io_iterator_t						mDeviceConnectNotification;
    
	// Device info.
	
	BluetoothDeviceAddress				mAddress;				// 00 08 22 44 AB 56, etc.
    
	NSString							*mName;					// "Terry Bozzio's Phone", etc.
	NSDate								*mLastNameUpdate;		// The date/time of the last read name
    
    BluetoothClassOfDevice				mClassOfDevice;
	
	// Stuff for connecting to the device.
	
	BluetoothPageScanRepetitionMode		mPageScanRepetitionMode;
	BluetoothHCIPageScanPeriodMode		mPageScanPeriodMode;
	BluetoothHCIPageScanMode			mPageScanMode;
	BluetoothClockOffset				mClockOffset;
    
    NSDate								*mLastInquiryUpdate;	// Time/date of the last inquiry result
                                                                // including the above 5 attributes
	
	// Stuff for maintaining a connection to the device.
	
	BluetoothConnectionHandle			mConnectionHandle;		// HCI handle
	BluetoothLinkType					mLinkType;				// SCO or ACL
	BluetoothHCIEncryptionMode			mEncryptionMode;		// Disabled, only P2P, P2P and Broadcast.
    
    NSArray								*mServiceArray;
    NSDate								*mLastServicesUpdate;
    
    // RFCOMM support
    
    IOBluetoothRFCOMMConnection			*mRFCOMMConnection;
    
    id                                  _mReserved;
}

// Creation/deletion.

/*!
    @property	registerForConnectNotifications:selector:
	@abstract	Allows a client to register for device connect notifications for any connection.
	@discussion	The given selector will be called on the target observer whenever any device connection is made.
				The selector should accept two arguments.  The first is the user notification object.  The second
				is the device that was connected.
	@param		observer	Target observer object
	@param		inSelector	Selector to be sent to the observer when a new connection is made
	@result		Returns an IOBluetoothUserNotification representing the outstanding device connect notification.
				To unregister the notification, call -unregister on the returned IOBluetoothUserNotification 
				object.  If an error is encountered creating the notification, nil is returned.  The returned
				IOBluetoothUserNotification object will be valid for as long as the notification is registered.
				It is not necessary to retain the result.  Once -unregister is called on it, it will no longer
				be valid.
*/

+ (IOBluetoothUserNotification *)registerForConnectNotifications:(id)observer selector:(SEL)inSelector;

/*!
    @property	registerForDisconnectNotification:selector:
	@abstract	Allows a client to register for device disconnect notification.
	@discussion	The given selector will be called on the target observer when the target device's connection is 
				closed.  The selector should contain two arguments.  The first is the user notification object.  The second
				is the IOBluetoothDevice that was disconnected.
	@param		observer	Target observer object
	@param		inSelector	Selector to be sent to the observer when the connection is destroyed
	@result		Returns an IOBluetoothUserNotification representing the outstanding device disconnect notification.
				To unregister the notification, call -unregister of the returned IOBluetoothUserNotification 
				object.  If an error is encountered creating the notification, nil is returned.
*/

- (IOBluetoothUserNotification *)registerForDisconnectNotification:(id)observer selector:(SEL)inSelector;

/*!
    @property	deviceWithAddress:
	@abstract	Returns the IOBluetoothDevice object for the given BluetoothDeviceAddress
	@discussion	Within a single application, there will be only one instance of IOBluetoothDevice for a
                given remote device address.
	@param		address	Pointer to a BluetoothDeviceAddress for which an IOBluetoothDevice instance is desired
	@result		Returns the IOBluetoothDevice object for the given BluetoothDeviceAddress
*/

+ (instancetype)deviceWithAddress:(const BluetoothDeviceAddress *)address;
+ (instancetype)withAddress:(const BluetoothDeviceAddress *)address DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
 @property	deviceWithAddressString:
 @abstract	Returns the IOBluetoothDevice object for the given BluetoothDeviceAddress
 @discussion	Within a single application, there will be only one instance of IOBluetoothDevice for a
 given remote device address.
 @param		address	Pointer to an NSString containing the BD_ADDR for which an IOBluetoothDevice instance is desired.  The string should be of the form xx:xx:xx:xx:xx:xx
 @result		Returns the IOBluetoothDevice object for the given BluetoothDeviceAddress
 */

+ (instancetype)deviceWithAddressString:(NSString *)address ;

/*!
    @property	withDeviceRef:
	@abstract	Method call to convert an IOBluetoothDeviceRef into an IOBluetoothDevice *.
	@discussion	IOBluetoothDeviceRef and it's API are deprecated.  An IOBluetoothDeviceRef can be cast to a IOBluetoothDevice *
	@param		deviceRef IOBluetoothDeviceRef for which an IOBluetoothDevice * is desired.
	@result		Returns the IOBluetoothDevice * for the given IOBluetoothDeviceRef.
*/

+ (instancetype)withDeviceRef:(IOBluetoothDeviceRef)deviceRef DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @property	getDeviceRef
	@abstract	Returns an IOBluetoothDeviceRef representation of the target IOBluetoothDevice object.
	@discussion	IOBluetoothDeviceRef and it's API are deprecated.  An IOBluetoothDeviceRef can be cast to a IOBluetoothDevice *
	@result		Returns an IOBluetoothDeviceRef representation of the target IOBluetoothDevice object.
*/

- (IOBluetoothDeviceRef)getDeviceRef DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

// L2CAP channel.

/*!
    @property	openL2CAPChannelSync:withPSM:delegate:
	@abstract	Opens a new L2CAP channel to the target device. Returns only after the channel is opened.
	@discussion	This method will begin the process of opening a new L2CAP channel to the target device.  
                The baseband connection to the device will be opened if it is not open already.  The L2CAP
                channel open process will not complete until the client has registered an incoming data 
                listener on the new channel.  This prevents a situation where the channel succeeds
                in being configured and opened and receives data before the client is listening and
                is ready for it.

				NOTE: This method is only available in Mac OS X 10.2.5 (Bluetooth v1.2) or later.
	@param		newChannel		A pointer to an IOBluetoothL2CAPChannel object to receive the L2CAP channel 
                                requested to be opened.  The newChannel pointer will only be set if 
                                kIOReturnSuccess is returned.
	@param		withPSM			The L2CAP PSM value for the new channel.
	@param		channelDelegate the object that will play the role of delegate for the channel.
				A channel delegate is the object the l2cap uses as target for  data and events. The
				developer will implement only the the methods he/she is interested in. A list of the
				possible methods is at the end of the file "IOBluetoothL2CAPChannel.h" in the definition
				of the protocol IOBluetoothL2CAPChannelDelegate.
				
	@result		Returns kIOReturnSuccess if the open process was successfully started (or if an existing
                L2CAP channel was found). 
*/

- (IOReturn)openL2CAPChannelSync:(IOBluetoothL2CAPChannel **)newChannel withPSM:(BluetoothL2CAPPSM)psm delegate:(id)channelDelegate;

/*!
    @property	openL2CAPChannelAsync:withPSM:delegate:
	@abstract	Opens a new L2CAP channel to the target device. Returns immediately after starting the opening process.
	@discussion	This method will begin the process of opening a new L2CAP channel to the target device.  
                The baseband connection to the device will be opened if it is not open already.  The L2CAP
                channel open process will not complete until the client has registered an incoming data 
                listener on the new channel.  This prevents a situation where the channel succeeds
                in being configured and opened and receives data before the client is listening and
                is ready for it.

				NOTE: This method is only available in Mac OS X 10.2.5 (Bluetooth v1.2) or later.
	@param		newChannel		A pointer to an IOBluetoothL2CAPChannel object to receive the L2CAP channel 
                                requested to be opened.  The newChannel pointer will only be set if 
                                kIOReturnSuccess is returned.
	@param		psm				The L2CAP PSM value for the new channel.
	@param		channelDelegate the object that will play the role of delegate for the channel.
				A channel delegate is the object the l2cap uses as target for  data and events. The
				developer will implement only the the methods he/she is interested in. A list of the
				possible methods is at the end of the file "IOBluetoothL2CAPChannel.h" in the definition
				of the protocol IOBluetoothL2CAPChannelDelegate.
				
	@result		Returns kIOReturnSuccess if the open process was successfully started (or if an existing
                L2CAP channel was found). 
*/

- (IOReturn)openL2CAPChannelAsync:(IOBluetoothL2CAPChannel **)newChannel withPSM:(BluetoothL2CAPPSM)psm delegate:(id)channelDelegate;

/*!
    @property	openL2CAPChannel:findExisting:newChannel:
	@abstract	Opens a new L2CAP channel to the target device. Returns immedialty after starting the opening process.
	@discussion	This method will begin the process of opening a new L2CAP channel to the target device.  
                The baseband connection to the device will be opened if it is not open already.  The L2CAP
                channel open process will not complete until the client has registered an incoming data 
                listener on the new channel.  This prevents a situation where the channel succeeds
                in being configured and opened and receives data before the client is listening and
                is ready for it.
	@param		psm				The L2CAP PSM value for the new channel.
	@param		findExisting	This value should be set to TRUE if it should look for an existing channel 
                                with the PSM.  Typically this value will be FALSE.  It should be TRUE only
                                in the case where a single channel is allowed by the spec for the given PSM.
	@param		newChannel		A pointer to an IOBluetoothL2CAPChannel object to receive the L2CAP channel 
                                requested to be opened.  The newChannel pointer will only be set if 
                                kIOReturnSuccess is returned.
	@result		Returns kIOReturnSuccess if the open process was successfully started (or if an existing
                L2CAP channel was found). 
*/

- (IOReturn)openL2CAPChannel:(BluetoothL2CAPPSM)psm findExisting:(BOOL)findExisting newChannel:(IOBluetoothL2CAPChannel **)newChannel DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
    @property	sendL2CAPEchoRequest:length:
	@abstract	Send an echo request over the L2CAP connection to a remote device.
	@discussion	The current implementation returns when the request has been sent, but does not indicate when
                a response is received.  Also, the baseband connection must be up for the echo request to be sent.
                In the future, this method will also open the connection if necessary.  The API will be updated
                to allow the client to be informed when the echo response has been received (both synchronously
                and asynchronously).
	@param		data	(void *) - Pointer to buffer to send.
	@param		length	(UInt16) - Length of the buffer to send
	@result		Returns kIOReturnSuccess if the echo request was able to be sent.
*/

- (IOReturn)sendL2CAPEchoRequest:(void *)data length:(UInt16)length;

/*!
    @property	openRFCOMMChannel:channel:
	@abstract	Opens a new RFCOMM channel to the target device. Returns only once the channel is open or failed to open.
	@discussion	This method will begin the process of opening a new RFCOMM channel to the target device.  
                The baseband connection to the device will be opened if it is not open already.  The RFCOMM
                channel open process will not complete until the client has registered an incoming data 
                listener on the new channel.
	@param		channelID		The RFCOMM channel ID for the new channel.
	@param		rfcommChannel	A pointer to an IOBluetoothRFCOMMChannel object to receive the RFCOMM channel 
                                requested to be opened.  The rfcommChannel pointer will only be set if 
                                kIOReturnSuccess is returned.
	@result		Returns kIOReturnSuccess if the open process was successfully started (or if an existing
                RFCOMM channel was found). 
*/

- (IOReturn)openRFCOMMChannel:(BluetoothRFCOMMChannelID)channelID channel:(IOBluetoothRFCOMMChannel **)rfcommChannel DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
    @property	openRFCOMMChannelSync:withChannelID:delegate:
	@abstract	Opens a new RFCOMM channel to the target device.  Returns only once the channel is open or failed to open.
	@discussion	This method will begin the process of opening a new RFCOMM channel to the target device.  
                The baseband connection to the device will be opened if it is not open already.  The RFCOMM
                channel open process will not complete until the client has registered an incoming data 
                listener on the new channel. The RFCOMM channel object is already retained when this function returns success;
				the channel must be released when the caller is done with it.

				You should verify that the channel you wish to open exists on the remote device before attempting to open it,
				by performing an SDP query. This is recommended because the service might have been removed from the,
				remote device or the channel assignments for the service could have changed (this is rare, but it does happen
				frequently on some devices). This also works around a bug that existed in early Leopard versions in certain
				situations where the method would return an error; in these instances, the desired RFCOMM channel could not
				be opened again until the calling app was restarted.

				NOTE:	This method is only available in Mac OS X 10.2.5 (Bluetooth v1.2) or later.
						
	@param		rfcommChannel	A pointer to an IOBluetoothRFCOMMChannel object to receive the RFCOMM channel 
                                requested to be opened.  The rfcommChannel pointer will only be set if 
                                kIOReturnSuccess is returned.

	@param		channelID		The RFCOMM channel ID for the new channel.
								
	@param		channelDelegate the object that will play the role of delegate for the channel.
				A channel delegate is the object the rfcomm uses as target for  data and events. The
				developer will implement only the the methods he/she is interested in. A list of the
				possible methods is at the end of the file "IOBluetoothRFCOMMChannel.h" in the definition
				of the protocol IOBluetoothRFCOMMChannelDelegate.

	@result		Returns kIOReturnSuccess if the open process was successfully started (or if an existing
                RFCOMM channel was found). The channel must be released when the caller is done with it.
*/

- (IOReturn)openRFCOMMChannelSync:(IOBluetoothRFCOMMChannel **)rfcommChannel withChannelID:(BluetoothRFCOMMChannelID)channelID delegate:(id)channelDelegate;

/*!
    @property	openRFCOMMChannelAsync:withChannelID:delegate:
	@abstract	Opens a new RFCOMM channel to the target device. Returns immediately.
	@discussion	This method will begin the process of opening a new RFCOMM channel to the target device.  
                The baseband connection to the device will be opened if it is not open already.  The RFCOMM
                channel open process will not complete until the client has registered an incoming data 
                listener on the new channel. The RFCOMM channel object is already retained when this function returns success;
				the channel must be released when the caller is done with it.
					
				You should verify that the channel you wish to open exists on the remote device before attempting to open it,
				by performing an SDP query. This is recommended because the service might have been removed from the,
				remote device or the channel assignments for the service could have changed (this is rare, but it does happen
				frequently on some devices). This also works around a bug that existed in early Leopard versions in certain
				situations where the method would return an error; in these instances, the desired RFCOMM channel could not
				be opened again until the calling app was restarted.

				NOTE: This method is only available in Mac OS X 10.2.5 (Bluetooth v1.2) or later.
				
	@param		rfcommChannel	A pointer to an IOBluetoothRFCOMMChannel object to receive the RFCOMM channel 
                                requested to be opened.  The rfcommChannel pointer will only be set if 
                                kIOReturnSuccess is returned.

	@param		channelID		The RFCOMM channel ID for the new channel.
								
	@param		channelDelegate the object that will play the role of delegate for the channel.
				A channel delegate is the object the rfcomm uses as target for  data and events. The
				developer will implement only the the methods he/she is interested in. A list of the
				possible methods is at the end of the file "IOBluetoothRFCOMMChannel.h" in the definition
				of the protocol IOBluetoothRFCOMMChannelDelegate.

	@result		Returns kIOReturnSuccess if the open process was successfully started (or if an existing
                RFCOMM channel was found). The channel must be released when the caller is done with it.
*/

- (IOReturn)openRFCOMMChannelAsync:(IOBluetoothRFCOMMChannel **)rfcommChannel withChannelID:(BluetoothRFCOMMChannelID)channelID delegate:(id)channelDelegate;

// Setting/getting device info.

/*!
    @property	getClassOfDevice
	@abstract	Gets the full class of device value for the remote device.
	@discussion	This value is only meaningful if the target device has been seen during an inquiry.  This can be
                by checking the result of -getLastInquiryUpdate.  If nil is returned, then the device hasn't been
                seen.
	@result		Returns the class of device for the remote device.
*/

@property(readonly) BluetoothClassOfDevice classOfDevice;
- (BluetoothClassOfDevice)getClassOfDevice DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @property	getServiceClassMajor
	@abstract	Get the major service class of the device.
	@discussion	This value is only meaningful if the target device has been seen during an inquiry.  This can be
                by checking the result of -getLastInquiryUpdate.  If nil is returned, then the device hasn't been
                seen.
	@result		Returns the major service class of the device.
*/

@property(readonly) BluetoothServiceClassMajor serviceClassMajor;
- (BluetoothServiceClassMajor)getServiceClassMajor DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @property	getDeviceClassMajor
	@abstract	Get the major device class of the device.
	@discussion	This value is only meaningful if the target device has been seen during an inquiry.  This can be
                by checking the result of -getLastInquiryUpdate.  If nil is returned, then the device hasn't been
                seen.
	@result		Returns the major device class of the remote device.
*/

@property(readonly) BluetoothDeviceClassMajor deviceClassMajor;
- (BluetoothDeviceClassMajor)getDeviceClassMajor DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @property	getDeviceClassMinor
	@abstract	Get the minor service class of the device.
	@discussion	This value is only meaningful if the target device has been seen during an inquiry.  This can be
                by checking the result of -getLastInquiryUpdate.  If nil is returned, then the device hasn't been
                seen.
	@result		Returns the minor device class of the remote device.
*/

@property(readonly) BluetoothDeviceClassMinor deviceClassMinor;
- (BluetoothDeviceClassMinor)getDeviceClassMinor DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @property	getName
	@abstract	Get the human readable name of the remote device.
	@discussion	This only returns a value if a remote name request has been performed on the target device.  If a
                successful remote name request has not been completed, nil is returned.  To perform a remote
                name request, call -remoteNameRequest.  If a remote name request has been successfully completed, 
                the method -getLastNameUpdate will return the date/time of the last successful request.
	@result		Returns the name of the remote device name.  This value is an NSString generated from the UTF-8
                format of the most recent remote name request.
*/

@property(readonly, copy) NSString *name;
- (NSString *)getName DEPRECATED_IN_MAC_OS_X_VERSION_10_6_AND_LATER;

/*!
    @property	getNameOrAddress
	@abstract	Get the human readable name of the remote device.  If the name is not present, it will return a string
                containing the device's address.
	@discussion	If a remote name request has been successfully completed, the device name will be returned.  If not,
                a string containg the device address in the format of "XX-XX-XX-XX-XX-XX" will be returned.
    @result		Returns the device's name or a string containing the device's address.
*/

@property(readonly) NSString *nameOrAddress;
- (NSString *)getNameOrAddress DEPRECATED_IN_MAC_OS_X_VERSION_10_6_AND_LATER;

/*!
    @property	getLastNameUpdate
	@abstract	Get the date/time of the last successful remote name request.
	@result		Returns the date/time of the last successful remote name request.  If no remote name request has been
                completed on the target device, nil is returned.
*/

@property(readonly, retain) NSDate *lastNameUpdate;
- (NSDate *)getLastNameUpdate DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @property	getAddress
	@abstract	Get the Bluetooth device address for the target device.
	@result		Returns a pointer to the Bluetooth device address of the target device.
*/

- (const BluetoothDeviceAddress *)getAddress;

/*!
    @property	getAddressString
	@abstract	Get a string representation of the Bluetooth device address for the target device.  The
				format of the string is the same as returned by IOBluetoothNSStringFromDeviceAddress().
	@discussion	NOTE: This method is only available in Mac OS X 10.2.4 (Bluetooth v1.1) or later.
	@result		Returns an NSString containing the Bluetooth device address of the target device.
*/

@property(readonly) NSString *addressString;
- (NSString *)getAddressString DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

// Connecting to the device.

/*!
    @property	getPageScanRepetitionMode
	@abstract	Get the value of the page scan repetition mode for the device.
	@discussion	This value is only meaningful if the target device has been seen during an inquiry.  This can be
                by checking the result of -getLastInquiryUpdate.  If nil is returned, then the device hasn't been
                seen.
	@result		Returns the page scan repetition mode value for this device.
*/

- (BluetoothPageScanRepetitionMode)getPageScanRepetitionMode;

/*!
    @property	getPageScanPeriodMode
	@abstract	Get the value of the page scan period mode for the device.
	@discussion	This value is only meaningful if the target device has been seen during an inquiry.  This can be
                by checking the result of -getLastInquiryUpdate.  If nil is returned, then the device hasn't been
                seen.
	@result		Returns page scan period mode value for the device.
*/

- (BluetoothPageScanPeriodMode)getPageScanPeriodMode;

/*!
    @property	getPageScanMode
	@abstract	Get the page scan mode for the device.
	@discussion	This value is only meaningful if the target device has been seen during an inquiry.  This can be
                by checking the result of -getLastInquiryUpdate.  If nil is returned, then the device hasn't been
                seen.
	@result		Returns the value for the page scan mode for the device.
*/

- (BluetoothPageScanMode)getPageScanMode;

/*!
    @property	getClockOffset
	@abstract	Get the clock offset value of the device.
	@discussion	This value is only meaningful if the target device has been seen during an inquiry.  This can be
                by checking the result of -getLastInquiryUpdate.  If nil is returned, then the device hasn't been
                seen.
	@result		Returns the clock offset value for the device.
*/

- (BluetoothClockOffset)getClockOffset;

/*!
    @property	getLastInquiryUpdate
	@abstract	Get the date/time of the last time the device was returned during an inquiry.
	@result		Returns the date/time of the last time the device was seen during an inquiry.
                If the device has never been seen during an inquiry, nil is returned.
*/

- (NSDate *)getLastInquiryUpdate;

/*!
    @property	RSSI
	@abstract	Get the RSSI device (if connected), above or below the golden range. If the RSSI is within the golden
				range, a value of 0 is returned. For the actual RSSI value, use getRawRSSI. For more information, see
				the Bluetooth 4.0 Core Specification.
	@result		Returns the RSSI of the device. If the value cannot be read (e.g. the device is disconnected), a value 
				of +127 will be returned.
*/

- (BluetoothHCIRSSIValue)RSSI AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @property	rawRSSI
	@abstract	Get the raw RSSI device (if connected).
	@result		Returns the raw RSSI of the device.
	@discussion	This value is the perceived RSSI value, not relative the the golden range (see getRSSI for that value).
				This value will not available on all Bluetooth modules. If the value cannot be read (e.g. the device
				is disconnected) or is not available on a module, a value of +127 will be returned.
*/

- (BluetoothHCIRSSIValue)rawRSSI AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @property	isConnected
	@abstract	Indicates whether a baseband connection to the device exists.
	@result		Returns YES if a baseband connection to the device exists.
*/

- (BOOL)isConnected;

/*!
    @property	openConnection
	@abstract	Create a baseband connection to the device.
	@discussion	This method is synchronous and will not return until either a connection has been established
                or the create connection has failed (perhaps timed out).  This method does the same thing as
				calling -openConnection: with a nil target.	 This call with proceed without authentication required, and
				using the default page timeout value.  If authentication or a non-default page timeout is required the method
				-openConnection:withPageTimeout:authenticationRequired: should be used instead.	
				
				As of Mac OS X 10.7, this method will no longer mask out "Connection Exists" 'errors' with a success result code;
				your code must account for the cases where the baseband connection is already open.
										
	@result		Returns kIOReturnSuccess if the connection was successfully created.
*/

- (IOReturn)openConnection;

/*!
    @property	openConnection:
	@abstract	Create a baseband connection to the device.
	@discussion	If a target is specified, the open connection call is asynchronous and on completion of the 
				CREATE_CONNECTION command, the method -connectionComplete:status: will be called on the specified target.  
				If no target is specified, the call is synchronous and will not return until the connection is open
				or the CREATE_CONNECTION call has failed.  This call with proceed without authentication required, and
				using the default page timeout value.  If authentication or a non-default page timeout is required the method
				-openConnection:withPageTimeout:authenticationRequired: should be used instead.

				As of Mac OS X 10.7, this method will no longer mask out "Connection Exists" 'errors' with a success result code;
				your code must account for the cases where the baseband connection is already open.

	@result		Returns kIOReturnSuccess if the connection was successfully created (or if asynchronous, if the
				CREATE_CONNECTION command was successfully issued).
*/

- (IOReturn)openConnection:(id)target;

/*!
    @property	openConnection:withPageTimeout:authenticationRequired:
	@abstract	Create a baseband connection to the device.
	@discussion	If a target is specified, the open connection call is asynchronous and on completion of the 
				CREATE_CONNECTION command, the method -connectionComplete:status: will be called on the specified target.  
				If no target is specified, the call is synchronous and will not return until the connection is open
				or the CREATE_CONNECTION call has failed.

				NOTE: This method is only available in Mac OS X 10.2.7 (Bluetooth v1.3) or later.

				As of Mac OS X 10.7, this method will no longer mask out "Connection Exists" 'errors' with a success result code;
				your code must account for the cases where the baseband connection is already open.

	@param		target The target to message when the create connection call is complete
	@param		pageTimeoutValue The page timeout value to use for this call
	@param		authenticationRequired BOOL value to indicate whether authentication should be required for the connection
	@result		Returns kIOReturnSuccess if the connection was successfully created (or if asynchronous, if the
				CREATE_CONNECTION command was successfully issued).
*/
- (IOReturn)openConnection:(id)target withPageTimeout:(BluetoothHCIPageTimeout)pageTimeoutValue authenticationRequired:(BOOL)authenticationRequired;

/*!
    @property	closeConnection
	@abstract	Close down the baseband connection to the device.
	@discussion	This method is synchronous and will not return until the connection has been closed (or the 
                command failed).  In the future this API will be changed to allow asynchronous operation.
    @result		Returns kIOReturnSuccess if the connection has successfully been closed.
*/

- (IOReturn)closeConnection;

/*!
    @property	remoteNameRequest:
	@abstract	Issues a remote name request to the target device.
	@discussion	If a target is specified, the request is asynchronous and on completion of the request, the method
 
				- (void)remoteNameRequestComplete:(IOBluetoothDevice *)device status:(IOReturn)status;

                will be called on the specified target. If no target is specified, the request is made synchronously
 				and won't return until the request is complete.  This call with operate with the default page
 				timeout value. If a different page timeout value is desired, the method -remoteNameRequest:withPageTimeout:
 				should be used instead.
	@param		target The target to message when the remote name request is complete
    @result		Returns kIOReturnSuccess if the remote name request was successfully issued (and if synchronous, if
                the request completed successfully).
*/

- (IOReturn)remoteNameRequest:(id)target;

/*!
    @property	remoteNameRequest:withPageTimeout:
	@abstract	Issues a remote name request to the target device.
	@discussion	If a target is specified, the request is asynchronous and on completion of the REMOTE_NAME_REQUEST
                command, the method -remoteNameRequestComplete:status:name: will be called on the specified target.
                If no target is specified, the request is made synchronously and won't return until the request is 
                complete.

				NOTE: This method is only available in Mac OS X 10.2.7 (Bluetooth v1.3) or later.
	@param		target The target to message when the remote name request is complete
	@param		pageTimeoutValue The page timeout value to use for this call
    @result		Returns kIOReturnSuccess if the remote name request was successfully issued (and if synchronous, if
                the request completed successfully).
*/

- (IOReturn)remoteNameRequest:(id)target withPageTimeout:(BluetoothHCIPageTimeout)pageTimeoutValue;

/*!
    @property	requestAuthentication
	@abstract	Requests that the existing baseband connection be authenticated.
	@discussion	In order to authenticate a baseband connection, a link key needs to be generated as a result of 
                the pairing process.  This call will synchronously initiate the pairing process with the target device
                and not return until the authentication process is complete.  This API will be updated to allow
                for asynchronous operation.
    @result		Returns kIOReturnSuccess if the connection has been successfully been authenticated.  Returns an error
                if authentication fails or no baseband connection exists.
*/

- (IOReturn)requestAuthentication;

/*!
    @property	getConnectionHandle
	@abstract	Get the connection handle for the baseband connection.
	@discussion	This method only returns a valid result if a baseband connection is present (-isConnected returns TRUE).
	@result		Returns the connection handle for the baseband connection.  If no baseband connection is present,
                kBluetoothConnectionHandleNone is returned.
*/

@property(readonly, assign) BluetoothConnectionHandle connectionHandle;
- (BluetoothConnectionHandle)getConnectionHandle DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @property	isIncoming
	@abstract	Returns TRUE if the device connection was generated by the remote host.
    @discussion	Returns TRUE if the device connection was generated by the remote host. False if the connection was generated by some other device that connected to the local host.

				NOTE: This method is only available in Mac OS X 10.2.7 (Bluetooth v1.3) or later.
	@result		Returns TRUE if the device connection was generated by the remote host.
*/

- (BOOL)isIncoming;

/*!
    @property	getLinkType
	@abstract	Get the link type for the baseband connection.
	@discussion	This method only returns a valid result if a baseband connection is present (-isConnected returns TRUE).
	@result		Returns the link type for the baseband connection.  If no baseband connection is present,
                kBluetoothLinkTypeNone is returned.
*/

- (BluetoothLinkType)getLinkType;

/*!
    @property	getEncryptionMode
	@abstract	Get the encryption mode for the baseband connection.
	@discussion	This method only returns a valid result if a baseband connection is present (-isConnected returns TRUE).
	@result		Returns the encryption mode for the baseband connection.  If no baseband connection is present,
                kEncryptionDisabled is returned.
*/

- (BluetoothHCIEncryptionMode)getEncryptionMode;

/*!
    @property	performSDPQuery:
	@abstract	Performs an SDP query on the target device.
	@discussion	As a result of this call, a baseband connection will be built to the device (if not already connected).
				Then, an L2CAP channel will be opened to the SDP server on the device.  At that point, a Service
				Search Attribute request will be issued with a UUID of 0x0100 (L2CAP) and an attribute range of
				0x0000 - 0xffff specified.  This will cause the SDP server to return all attributes of all L2CAP-derived 
				services on the device.  The results essentially encompass all services on the device.
				This function is always asynchronous.  If a target is specified, when the SDP query is complete (or
				an error is encountered), the method -sdpQueryComplete:status: will be called on the given target.  If no target 
				is specified, the request is still asynchronous, but no callback will be made.  That can be useful if the client 
				has	registered for SDP service changed notifications.
	@param		target The target to message when the SDP query is complete
    @result		Returns kIOReturnSuccess if the SDP query was successfully started.
*/

- (IOReturn)performSDPQuery:(id)target;

/*!
 @property	performSDPQuery:uuids:
 @abstract	Performs an SDP query on the target device with the specified service UUIDs.
 @discussion	As a result of this call, a baseband connection will be built to the device (if not already connected).
 Then, an L2CAP channel will be opened to the SDP server on the device.  At that point, a Service
 Search Attribute request will be issued for each service UUID specified in the UUID array.
 
 This function is always asynchronous.  If a target is specified, when the SDP query is complete (or
 an error is encountered), the method -sdpQueryComplete:status: will be called on the given target.  If no target 
 is specified, the request is still asynchronous, but no callback will be made.  That can be useful if the client 
 has	registered for SDP service changed notifications.
 @param		target The target to message when the SDP query is complete
 @param		uuidArray An array of IOBluetoothSDPUUID objects for each service the caller is interested in
 
 @result		Returns kIOReturnSuccess if the SDP query was successfully started.
 */

- (IOReturn)performSDPQuery:(id)target uuids:(NSArray *)uuidArray AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @property	services
	@abstract	Gets an array of service records for the device.
	@discussion	The resulting array contains IOBluetoothSDPServiceRecord objects.  The service records are only
                present if an SDP query has been done on the target object.  This can be determined by calling
                -getLastServicesUpdate.  It will return the last date/time of the SDP query. To initiate an
				SDP query on a device, use -performSDPQuery: as defined above.
                
                Instead of allowing individual clients to query for different services and service attributes,
                the system request all of the device's services and service attributes.
	@result		Returns an array of service records for the device if an SDP query has been performed.  If no
                SDP query has been performed, nil is returned.
*/

@property(readonly, retain) NSArray *services;
- (NSArray *)getServices DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @property	getLastServicesUpdate
	@abstract	Get the date/time of the last SDP query.
	@result		Returns the date/time of the last SDP query.  If an SDP query has never been performed on the
                device, nil is returned.
*/

- (NSDate *)getLastServicesUpdate;

/*!
    @property	getServiceRecordForUUID
	@abstract	Search for a service record containing the given UUID.
	@discussion	This method searches through the device's services to find a service that contains the given
                UUID.  Only the first service record will be returned.  This method only operates on services
                that have already been queried.  It will not initiate a new query.  This method should probably 
                be updated to return an array of service records if more than one contains the UUID.  
    @param		sdpUUID UUID value to search for.  
	@result		Returns the first service record that contains the given uuid.  If no service record is found,
                nil is returned.
*/

- (IOBluetoothSDPServiceRecord *)getServiceRecordForUUID:(IOBluetoothSDPUUID *)sdpUUID;

/*!
    @property	favoriteDevices
	@abstract	Gets an array of the user's favorite devices.
	@discussion	The resulting array contains IOBluetoothDevice objects.

				NOTE: This method is only available in Mac OS X 10.2.4 (Bluetooth v1.1) or later.
	@result		Returns an array of device objects representing the user's favorite devices.  If the
				user has no favorites, nil is returned.
*/

+ (NSArray *)favoriteDevices;

/*!
    @property	isFavorite
	@abstract	Reports whether the target device is a favorite for the user.
	@discussion	NOTE: This method is only available in Mac OS X 10.2.4 (Bluetooth v1.1) or later.
	@result		Returns TRUE if the target device is a favorite for the user, FALSE if not.
*/

- (BOOL)isFavorite;

/*!
    @property	addToFavorites
	@abstract	Adds the target device to the user's favorite devices list.
	@discussion	NOTE: This method is only available in Mac OS X 10.2.4 (Bluetooth v1.1) or later.
	@result		Returns kIOReturnSuccess if the device was successfully added to the user's
				list of favorite devices.
*/

- (IOReturn)addToFavorites;

/*!
    @property	removeFromFavorites
	@abstract	Removes the target device from the user's favorite devices list.
	@discussion	NOTE: This method is only available in Mac OS X 10.2.4 (Bluetooth v1.1) or later.
	@result		Returns kIOReturnSuccess if the device was successfully removed from the user's
				list of favorite devices.
*/

- (IOReturn)removeFromFavorites;

/*!
    @property	recentDevices
	@abstract	Gets an array of recently used Bluetooth devices.
	@discussion	The resulting array contains IOBluetoothDevice objects sorted in reverse chronological order.
				The most recently accessed devices are first.  If the numDevices parameter is 0, all devices 
				accessed by the system are returned.  If numDevices is non-zero, only the most recent devices
				are returned.

				NOTE: This method is only available in Mac OS X 10.2.4 (Bluetooth v1.1) or later.
    @param		numDevices The number of devices to return.
	@result		Returns an array of device objects recently used by the system.  If no devices have been accessed,
				nil is returned.
*/

+ (NSArray *)recentDevices:(unsigned long)numDevices;

/*!
    @property	recentAccessDate
	@abstract	Returns the date/time of the most recent access of the target device.
	@discussion	This is the date that -recentDevices uses to sort its list of the most recently accessed
				devices.

				NOTE: This method is only available in Mac OS X 10.2.4 (Bluetooth v1.1) or later.
	@result		Returns the date/time of the most recent access of the target device.  If the device
				has not been accessed, nil is returned.
*/

- (NSDate *)recentAccessDate;

/*!
    @property	pairedDevices
	@abstract	Gets an array of all of the paired devices on the system.
	@discussion	The resulting array contains IOBluetoothDevice objects.  The paired devices are currently NOT stored
				per user, so this is all devices paired by any user.

				NOTE: This method is only available in Mac OS X 10.2.5 (Bluetooth v1.2) or later.
	@result		Returns an array of device objects for all of the paired devices on the system.  If there are
				no paired devices, nil is returned.
*/

+ (NSArray *)pairedDevices;

/*!
    @property	isPaired
	@abstract	Returns whether the target device is paired.
	@discussion	NOTE: This method is only available in Mac OS X 10.2.5 (Bluetooth v1.2) or later.
	@result		Returns TRUE if the target device is paired, FALSE if not.
*/

- (BOOL)isPaired;

/*!
    @property	setSupervisionTimeout
	@abstract	Sets the connection supervision timeout.
	@discussion	NOTE: This method is only available in Mac OS X 10.5 (Bluetooth v2.0) or later.
	@param		timeout A client-supplied link supervision timeout value to use to monitor the connection. The timeout
				value should be specified in slots, so you can use the BluetoothGetSlotsFromSeconds macro to get the proper
				value. e.g. BluetoothGetSlotsFromSeconds( 5.0 ) will give yield the proper number of slots (8000) for 5 seconds.
	@result		Returns kIOReturnSuccess if it was possible to set the connection supervision timeout.
*/

- (IOReturn)setSupervisionTimeout:(UInt16)timeout;

/*!
    @property	openL2CAPChannelSync:withPSM:withConfiguration:delegate:
	@abstract	Opens a new L2CAP channel to the target device. Returns only after the channel is opened.
	@discussion	This method will begin the process of opening a new L2CAP channel to the target device.  
                The baseband connection to the device will be opened if it is not open already.  The L2CAP
                channel open process will not complete until the client has registered an incoming data 
                listener on the new channel.  This prevents a situation where the channel succeeds
                in being configured and opened and receives data before the client is listening and
                is ready for it. The L2CAP channel object is already retained when this function returns success;
				the channel must be released when the caller is done with it.

				NOTE: This method is only available in Mac OS X 10.5 (Bluetooth v2.0) or later.
	@param		newChannel		A pointer to an IOBluetoothL2CAPChannel object to receive the L2CAP channel 
                                requested to be opened.  The newChannel pointer will only be set if 
                                kIOReturnSuccess is returned.
	@param		withPSM			The L2CAP PSM value for the new channel.
	@param		channelConfiguration the dictionary that describes the initial configuration for
				the channel.
	@param		channelDelegate the object that will play the role of delegate for the channel.
				A channel delegate is the object the l2cap uses as target for  data and events. The
				developer will implement only the the methods he/she is interested in. A list of the
				possible methods is at the end of the file "IOBluetoothL2CAPChannel.h" in the definition
				of the protocol IOBluetoothL2CAPChannelDelegate.
			
	@result		Returns kIOReturnSuccess if the open process was successfully started (or if an existing
                L2CAP channel was found). The channel must be released when the caller is done with it.
*/

- (IOReturn)openL2CAPChannelSync:(IOBluetoothL2CAPChannel **)newChannel withPSM:(BluetoothL2CAPPSM)psm withConfiguration:(NSDictionary*)channelConfiguration delegate:(id)channelDelegate;

/*!
    @property	openL2CAPChannelAsync:withPSM:withConfiguration:delegate:
	@abstract	Opens a new L2CAP channel to the target device. Returns immediately after starting the opening process.
	@discussion	This method will begin the process of opening a new L2CAP channel to the target device.  
                The baseband connection to the device will be opened if it is not open already.  The L2CAP
                channel open process will not complete until the client has registered an incoming data 
                listener on the new channel.  This prevents a situation where the channel succeeds
                in being configured and opened and receives data before the client is listening and
                is ready for it. The L2CAP channel object is already retained when this function returns success;
				the channel must be released when the caller is done with it.

				NOTE: This method is only available in Mac OS X 10.5 (Bluetooth v2.0) or later.
	@param		newChannel		A pointer to an IOBluetoothL2CAPChannel object to receive the L2CAP channel 
                                requested to be opened.  The newChannel pointer will only be set if 
                                kIOReturnSuccess is returned.
	@param		psm				The L2CAP PSM value for the new channel.
	@param		channelConfiguration the dictionary that describes the initial configuration for
				the channel.
	@param		channelDelegate the object that will play the role of delegate for the channel.
				A channel delegate is the object the l2cap uses as target for  data and events. The
				developer will implement only the the methods he/she is interested in. A list of the
				possible methods is at the end of the file "IOBluetoothL2CAPChannel.h" in the definition
				of the protocol IOBluetoothL2CAPChannelDelegate.
				
	@result		Returns kIOReturnSuccess if the open process was successfully started (or if an existing
                L2CAP channel was found). The channel must be released when the caller is done with it.
*/

- (IOReturn)openL2CAPChannelAsync:(IOBluetoothL2CAPChannel **)newChannel withPSM:(BluetoothL2CAPPSM)psm withConfiguration:(NSDictionary*)channelConfiguration delegate:(id)channelDelegate;

- (id)awakeAfterUsingCoder:(NSCoder *)coder;

@end


