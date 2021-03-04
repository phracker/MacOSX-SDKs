
#pragma once

#import	<IOKit/IOKitLib.h>
#import 	<CoreFoundation/CFMachPort.h>

#import	<IOBluetooth/Bluetooth.h>

#ifdef __OBJC__
#import		<Foundation/Foundation.h>
#endif

#ifdef	__cplusplus
	extern "C" {
#endif

//--------------------------------------------------------------------------------------------------------------------------
/*!	@header		IOBluetoothUserLib.h
	@abstract	Public Interfaces for Apple's implementation of Bluetooth technology.
	@discussion	There is an accompanying header to this, "Bluetooth.h", which contains all technology-specific typedefs and information. This header relies heavily on it.
*/

//===========================================================================================================================
// General
//===========================================================================================================================
 
#if 0
#pragma mark -
#pragma mark === General ===
#endif


typedef struct OpaqueIOBluetoothObjectRef *			IOBluetoothObjectRef;
typedef struct OpaqueIOBluetoothObjectRef *			IOBluetoothDeviceRef;
typedef struct OpaqueIOBluetoothObjectRef *			IOBluetoothL2CAPChannelRef;
typedef struct OpaqueIOBluetoothObjectRef *			IOBluetoothRFCOMMChannelRef;
typedef struct OpaqueIOBluetoothObjectRef *			IOBluetoothSDPServiceRecordRef;
typedef struct OpaqueIOBluetoothObjectRef *			IOBluetoothSDPUUIDRef;
typedef struct OpaqueIOBluetoothObjectRef *			IOBluetoothSDPDataElementRef;
typedef struct OpaqueIOBluetoothObjectRef *			IOBluetoothUserNotificationRef;

typedef unsigned long								IOBluetoothObjectID;

#define kIOBluetoothObjectIDNULL	((IOBluetoothObjectID)0)

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothGetObjectIDFromArguments
	@abstract	Returns the BluetoothObjectID passed as an argument to an auto-launched app.
	@discussion	When an application gets auto-launched by the bluetoothd process (as a result of an incoming connection
				to an appropriately configured service), it has a BluetoothObjectID passed to it on the command
				line.  To get the BluetoothObjectID, simply pass the argc and argv parameters received in main(void)
				to this function.  The returned BluetoothObjectID can then be used to find the appropriate
				IOBluetoothL2CAPChannel or IOBluetoothRFCOMMChannel depending on the type of service (using 
				IOBluetoothL2CAPChannelCreateFromObjectID(void) or IOBluetoothRFCOMMChannelCreateFromObjectID.)

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param        argc The argc parameter passed to main()
	@param        argv The argv parameter passed to main()
	@result		Returns the BluetoothObjectID passed in the given arguments.  If no ID is present,
				kIOBluetoothObjectIDNULL is returned.
*/

extern IOBluetoothObjectID IOBluetoothGetObjectIDFromArguments( int argc, const char *argv[] )	DEPRECATED_IN_MAC_OS_X_VERSION_10_6_AND_LATER;

//===========================================================================================================================
// Device searching.
//===========================================================================================================================
 
#if 0
#pragma mark -
#pragma mark === Device Inquiry ===
#endif

//--------------------------------------------------------------------------------------------------------------------------
// As promised, the IOBluetoothDeviceInquiry C API has been removed. Please use obj-c equivalents.
//--------------------------------------------------------------------------------------------------------------------------
		
/*!	@typedef	IOBluetoothDeviceSearchOptions
*/
typedef	UInt32	IOBluetoothDeviceSearchOptions;

enum IOBluetoothDeviceSearchOptionsBits
{
	kSearchOptionsNone							= 0L,
	kSearchOptionsAlwaysStartInquiry			= (1L << 0),
	kSearchOptionsDiscardCachedResults			= (1L << 1),
};

//--------------------------------------------------------------------------------------------------------------------------
/*!	@typedef	IOBluetoothDeviceSearchDeviceAttributes
	@abstract	Structure used to search for particular devices.
	@discussion Make sure you specify all fields! If you do not set deviceClassMajor for example, and the value is
				0, that is mapped to kBluetoothDeviceClassMajorMiscellaneous, which is probably not what you want. To
				search for all device types, you must pass kBluetoothDeviceClassMajorAny and its relatives. 
*/

struct 	IOBluetoothDeviceSearchDeviceAttributes
{
	BluetoothDeviceAddress				address;				// 00 08 22 44 AB 56, etc.
	BluetoothDeviceName					name;					// "Al Yankovic's Phone", etc.
	BluetoothServiceClassMajor			serviceClassMajor;		// Networking, Rendering, etc.
	BluetoothDeviceClassMajor			deviceClassMajor;		// Computer, Phone, Audio, etc.
	BluetoothDeviceClassMinor			deviceClassMinor;		// Desktop, cordless, headset, etc.
};
typedef	struct	IOBluetoothDeviceSearchDeviceAttributes	IOBluetoothDeviceSearchDeviceAttributes;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@struct		IOBluetoothDeviceSearchAttributes
	@discussion You can search for general device classes and service classes, or you can search for a 
				specific device address or name. If you pass NULL as the attribute structure,
				you will get ALL devices in the vicinity found during a search. Note that passing a zeroed
				out block of attributes is NOT equivalent to passing in NULL!	
*/ 

struct 	IOBluetoothDeviceSearchAttributes
{
	IOBluetoothDeviceSearchOptions	options;				// Options.
	IOItemCount						maxResults;				// Maximum number of results you desire. 0 means infinite.
	IOItemCount						deviceAttributeCount;

	IOBluetoothDeviceSearchDeviceAttributes	*attributeList;	
};
typedef	struct	IOBluetoothDeviceSearchAttributes	IOBluetoothDeviceSearchAttributes;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@typedef		IOBluetoothDeviceSearchTypes
 */

typedef UInt32	IOBluetoothDeviceSearchTypes;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@enum		IOBluetoothDeviceSearchTypesBits
	@abstract	Bits to determine what Bluetooth devices to search for
 */

enum IOBluetoothDeviceSearchTypesBits
{
    kIOBluetoothDeviceSearchClassic = 1,
    kIOBluetoothDeviceSearchLE = 2
};

//===========================================================================================================================
// Local Device Interaction
//===========================================================================================================================

#if 0
#pragma mark -
#pragma mark ===  Local Device Interaction ===
#endif

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothIgnoreHIDDevice
	@abstract	Hints that the Mac OS X Bluetooth software should ignore a HID device that connects up.
	@param		device	A Bluetooth Device to ignore.
*/

API_UNAVAILABLE(ios, watchos, tvos)
extern	void	IOBluetoothIgnoreHIDDevice( IOBluetoothDeviceRef	device );

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothRemoveIgnoredHIDDevice
	@abstract    The counterpart to the above IOBluetoothIgnoreHIDDevice() API.
	@param		device	A Bluetooth Device to "un"ignore.
*/

API_UNAVAILABLE(ios, watchos, tvos)
extern	void	IOBluetoothRemoveIgnoredHIDDevice( IOBluetoothDeviceRef	device );

#if 0
#pragma mark -
#pragma mark === Notifications ===
#endif

typedef enum IOBluetoothUserNotificationChannelDirection
{
    kIOBluetoothUserNotificationChannelDirectionAny						= 0,
    kIOBluetoothUserNotificationChannelDirectionIncoming				= 1,
    kIOBluetoothUserNotificationChannelDirectionOutgoing				= 2,
} IOBluetoothUserNotificationChannelDirection;

/*!
    @typedef IOBluetoothUserNotificationCallback
    @abstract Callback function definition for user notifications.
    @discussion This callback will be invoked when the notification for which it was registered is sent.
    @param userRefCon	(void *) This user defined parameter was provided during the original call to register
						the notification.
    @param inRef		(IOBluetoothUserNotificationRef) The notification responsible for sending the notification.
    @param objectRef	(IOBluetoothObjectRef) The object that originated the notification.
*/

typedef void (*IOBluetoothUserNotificationCallback)( 	void * userRefCon,
                                                        IOBluetoothUserNotificationRef inRef,
                                                        IOBluetoothObjectRef objectRef );

/*!
    @function IOBluetoothUserNotificationUnregister
    @abstract Unregisters the target notification.
    @discussion This function will unregister the notification.  Once the notification has been unregistered,
				it will no longer call the callback.  Additionally, once this function has been called the
				target IOBluetoothUserNotificationRef is no longer valid.
    @param	notificationRef The target IOBluetoothUserNotificationRef to be unregistered
*/

API_UNAVAILABLE(ios, watchos, tvos)
void IOBluetoothUserNotificationUnregister( IOBluetoothUserNotificationRef notificationRef );

/*!
    @function	IOBluetoothRegisterForDeviceConnectNotifications
	@abstract	Allows a client to register for device connect notifications for any connection.
	@discussion	The given callback will be called whenever any device connection is made.
	@param		callback	The callback to be called when a new connection is made
	@param		inRefCon	Client-supplied refCon to be passed to the callback.
	@result		Returns an IOBluetoothUserNotificationRef representing the outstanding device connect notification.
				To unregister the notification, call IOBluetoothUserNotificationUnregister(void) with the returned
				IOBluetoothUserNotificationRef.  If an error is encountered creating the notification, NULL is returned.  
				The returned IOBluetoothUserNotificationRef will be valid for as long as the notification is registered.
				It is not necessary to retain the result.  Once the notification is unregistered, it will no longer
				be valid.
*/

API_UNAVAILABLE(ios, watchos, tvos)
IOBluetoothUserNotificationRef IOBluetoothRegisterForDeviceConnectNotifications(	IOBluetoothUserNotificationCallback callback,
                                                                                    void * inRefCon );

/*!
    @function	IOBluetoothDeviceRegisterForDisconnectNotification
	@abstract	Allows a client to register for device disconnect notification.
	@discussion	The given callback will be called when the target device's connection is closed..
	@param		callback	The callback to be called when the target's connection is destroyed
	@param		inRefCon	Client-supplied refCon to be passed to the callback.
	@result		Returns an IOBluetoothUserNotificationRef representing the outstanding device disconnect notification.
				To unregister the notification, call IOBluetoothUserNotificationUnregister(void) with the returned
				IOBluetoothUserNotificationRef.  If an error is encountered creating the notification, NULL is returned.  
				The returned IOBluetoothUserNotificationRef will be valid for as long as the notification is registered.
				It is not necessary to retain the result.  Once the notification is unregistered, it will no longer
				be valid.
*/

API_UNAVAILABLE(ios, watchos, tvos)
IOBluetoothUserNotificationRef IOBluetoothDeviceRegisterForDisconnectNotification(	IOBluetoothDeviceRef inDevice,
                                                                                    IOBluetoothUserNotificationCallback callback,
                                                                                    void * inRefCon );

/*!
    @function	IOBluetoothRegisterForL2CAPChannelOpenNotifications
	@abstract	Allows a client to register for L2CAP channel open notifications for any L2CAP channel.
	@discussion	The given callback will be called whenever any L2CAP channel is opened.
	@param		callback	The callback to be called when a new L2CAP channel is opened.
	@param		inRefCon	Client-supplied refCon to be passed to the callback.
	@result		Returns an IOBluetoothUserNotificationRef representing the outstanding L2CAP channel notification.
				To unregister the notification, call IOBluetoothUserNotificationUnregister(void) with the returned
				IOBluetoothUserNotificationRef.  If an error is encountered creating the notification, NULL is returned.  
				The returned IOBluetoothUserNotificationRef will be valid for as long as the notification is registered.
				It is not necessary to retain the result.  Once the notification is unregistered, it will no longer
				be valid.
*/

API_UNAVAILABLE(ios, watchos, tvos)
IOBluetoothUserNotificationRef IOBluetoothRegisterForL2CAPChannelOpenNotifications(	IOBluetoothUserNotificationCallback callback,
                                                                                    void *inRefCon );

/*!
    @function	IOBluetoothRegisterForFilteredL2CAPChannelOpenNotifications
	@abstract	Allows a client to register for L2CAP channel open notifications for certain types of
				L2CAP channels.
	@discussion	The given callback will be called whenever any L2CAP channel is opened.
	@param		callback	The callback to be called when a new L2CAP channel is opened.
	@param		inRefCon	Client-supplied refCon to be passed to the callback.
	@param		inPSM		PSM to match a new L2CAP channel.  If the PSM doesn't matter, 0 may be passed in.
	@param		inDirection	The desired direction of the L2CAP channel - kIOBluetoothUserNotificationChannelDirectionAny
				if the direction doesn't matter.
	@result		Returns an IOBluetoothUserNotificationRef representing the outstanding L2CAP channel notification.
				To unregister the notification, call IOBluetoothUserNotificationUnregister(void) with the returned
				IOBluetoothUserNotificationRef.  If an error is encountered creating the notification, NULL is returned.  
				The returned IOBluetoothUserNotificationRef will be valid for as long as the notification is registered.
				It is not necessary to retain the result.  Once the notification is unregistered, it will no longer
				be valid.
*/

API_UNAVAILABLE(ios, watchos, tvos)
IOBluetoothUserNotificationRef IOBluetoothRegisterForFilteredL2CAPChannelOpenNotifications(	IOBluetoothUserNotificationCallback callback,
                                                                                            void * inRefCon,
                                                                                            BluetoothL2CAPPSM inPSM,
                                                                                            IOBluetoothUserNotificationChannelDirection inDirection );

/*!
    @function	IOBluetoothL2CAPChannelRegisterForChannelCloseNotification
	@abstract	Allows a client to register for a channel close notification.
    @discussion	The given callback will be called when the L2CAP channel is closed.
	@param		channel		The target L2CAP channel
	@param		callback	Callback to be called when the L2CAP channel is closed.
	@param		inRefCon	Client-supplied refCon to be passed to the callback.
	@result		Returns an IOBluetoothUserNotificationRef representing the outstanding L2CAP channel close notification.
				To unregister the notification, call IOBluetoothUserNotificationUnregister(void) with the returned
				IOBluetoothUserNotificationRef.  If an error is encountered creating the notification, NULL is returned.  
				The returned IOBluetoothUserNotificationRef will be valid for as long as the notification is registered.
				It is not necessary to retain the result.  Once the notification is unregistered, it will no longer
				be valid.
*/

API_UNAVAILABLE(ios, watchos, tvos)
IOBluetoothUserNotificationRef IOBluetoothL2CAPChannelRegisterForChannelCloseNotification(	IOBluetoothL2CAPChannelRef channel,
                                                                                            IOBluetoothUserNotificationCallback callback,
                                                                                            void *inRefCon );

/*!
    @function	IOBluetoothRegisterForRFCOMMChannelOpenNotifications
	@abstract	Allows a client to register for RFCOMM channel open notifications for any RFCOMM channel.
	@discussion	The given callback will be called whenever any RFCOMM channel is opened.
	@param		callback	The callback to be called when a new RFCOMM channel is opened.
	@param		inRefCon	Client-supplied refCon to be passed to the callback.
	@result		Returns an IOBluetoothUserNotificationRef representing the outstanding RFCOMM channel notification.
				To unregister the notification, call IOBluetoothUserNotificationUnregister(void) with the returned
				IOBluetoothUserNotificationRef.  If an error is encountered creating the notification, NULL is returned.  
				The returned IOBluetoothUserNotificationRef will be valid for as long as the notification is registered.
				It is not necessary to retain the result.  Once the notification is unregistered, it will no longer
				be valid.
*/

API_UNAVAILABLE(ios, watchos, tvos)
IOBluetoothUserNotificationRef IOBluetoothRegisterForRFCOMMChannelOpenNotifications(	IOBluetoothUserNotificationCallback callback,
                                                                                        void * inRefCon );

/*!
    @function	IOBluetoothRegisterForFilteredRFCOMMChannelOpenNotifications
	@abstract	Allows a client to register for RFCOMM channel open notifications for certain types of
				RFCOMM channels.
	@discussion	The given callback will be called whenever any RFCOMM channel is opened.
	@param		callback	The callback to be called when a new RFCOMM channel is opened.
	@param		inRefCon	Client-supplied refCon to be passed to the callback.
	@param		channelID	RFCOMM channel ID to match a new RFCOMM channel.  If the channel ID doesn't matter, 0 may be passed in.
	@param		inDirection	The desired direction of the RFCOMM channel - kIOBluetoothUserNotificationChannelDirectionAny
				if the direction doesn't matter.
	@result		Returns an IOBluetoothUserNotificationRef representing the outstanding RFCOMM channel notification.
				To unregister the notification, call IOBluetoothUserNotificationUnregister(void) with the returned
				IOBluetoothUserNotificationRef.  If an error is encountered creating the notification, NULL is returned.  
				The returned IOBluetoothUserNotificationRef will be valid for as long as the notification is registered.
				It is not necessary to retain the result.  Once the notification is unregistered, it will no longer
				be valid.
*/

API_UNAVAILABLE(ios, watchos, tvos)
IOBluetoothUserNotificationRef IOBluetoothRegisterForFilteredRFCOMMChannelOpenNotifications(	IOBluetoothUserNotificationCallback callback,
                                                                                                void * inRefCon,
                                                                                                BluetoothRFCOMMChannelID channelID,
                                                                                                IOBluetoothUserNotificationChannelDirection inDirection );

/*!
    @function	IOBluetoothRFCOMMChannelRegisterForChannelCloseNotification
	@abstract	Allows a client to register for a channel close notification.
    @discussion	The given callback will be called when the RFCOMM channel is closed.
	@param		inChannel	The target RFCOMM channel
	@param		callback	Callback to be called when the RFCOMM channel is closed.
	@param		inRefCon	Client-supplied refCon to be passed to the callback.
	@result		Returns an IOBluetoothUserNotificationRef representing the outstanding RFCOMM channel close notification.
				To unregister the notification, call IOBluetoothUserNotificationUnregister(void) with the returned
				IOBluetoothUserNotificationRef.  If an error is encountered creating the notification, NULL is returned.  
				The returned IOBluetoothUserNotificationRef will be valid for as long as the notification is registered.
				It is not necessary to retain the result.  Once the notification is unregistered, it will no longer
				be valid.
*/

API_UNAVAILABLE(ios, watchos, tvos)
IOBluetoothUserNotificationRef IOBluetoothRFCOMMChannelRegisterForChannelCloseNotification(	IOBluetoothRFCOMMChannelRef inChannel,
                                                                                            IOBluetoothUserNotificationCallback callback,
                                                                                            void * inRefCon );


#ifdef	__cplusplus
	}
#endif

