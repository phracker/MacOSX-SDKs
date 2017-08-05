
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
	@discussion	When an application gets auto-launched by the blued process (as a result of an incoming connection
				to an appropriately configured service), it has a BluetoothObjectID passed to it on the command
				line.  To get the BluetoothObjectID, simply pass the argc and argv parameters received in main()
				to this function.  The returned BluetoothObjectID can then be used to find the appropriate
				IOBluetoothL2CAPChannel or IOBluetoothRFCOMMChannel depending on the type of service (using 
				IOBluetoothL2CAPChannelCreateFromObjectID() or IOBluetoothRFCOMMChannelCreateFromObjectID.)

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		argc The argc parameter passed to main()
	@param		argv The argv parameter passed to main()
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

extern	void	IOBluetoothIgnoreHIDDevice( IOBluetoothDeviceRef	device );

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothRemoveIgnoredHIDDevice
	@abstract	The counterpart to the above IOBluetoothIgnoreHIDDevice() API.
	@param		device	A Bluetooth Device to "un"ignore.
*/

extern	void	IOBluetoothRemoveIgnoredHIDDevice( IOBluetoothDeviceRef	device );


#if 0
#pragma mark -
#pragma mark === SDP ===
#endif

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothAddServiceDict
	@abstract	Adds a service to the local SDP server.
    @discussion	Each entry in the dictionary representing the service contains the individual attributes.  Each
                attribute in the dict is keyed by a string that must begin with a hex number representing the
                attribute ID.  The key string may contain additional characters if desired as long as they 
                follow a space after the ID hex string.  The attribute value must follow the dictionary format 
                described by IOBluetoothSDPDataElement.  This dictionary format allows a service dict to be
                created as a plist file and then loaded into the system rather than built up in code.  See the
                example code for an example of how can be done.
                
                If the service record handle, L2CAP PSM or RFCOMM channel ID specified in the dictionary are in
                use, an alternate one will be assigned.
                
                In addition to attributes that represent the service itself, additional attributes may be specified
				that control the local behavior of the service.  To specify these local attributes, an additional
				property titled "LocalAttributes" may be added to the root of the service dict.  The value of this 
				property must be a dictionary that contains the individual local attributes.
				
				Currently, only two local attributes are supported: "Persistent" and "TargetApplication".
				
				The "Persistent" local attribute must be either a boolean or number representing whether the service
				should be persistent.  A persistent service will be saved off and restored any time the Bluetooth
				hardware is present.  It will persist through reboots and can only be removed by calling 
				IOBluetoothRemoveServiceWithRecordHandle().  This attribute is optional.  By default, if no 
				"Persistent" local property is present,	the service will only exist temporarily.  It will 
				be removed either when IOBluetoothRemoveServiceWithRecordHandle() is called or when the client 
				application exits.
				
				The "TargetApplication" local attribute is used to specify an application to be launched when a 
				remote device attempts to connect to the service (by opening either an L2CAP or RFCOMM channel of
				the type specified in the service).  This value must be a string representing the absolute path to
				the target executable (not just the .app wrapper - i.e. 
				/System/Library/CoreServices/OBEXAgent.app/Contents/MacOS/OBEXAgent).  This attribute is optional.
				If no "TargetApplication" local attribute is specified, no special action will take place when an
				incoming connection to the service is created.  It is up to the client to be monitoring for the
				connection and to do the right thing when one appears.
				
				The "LocalAttributes" property is optional.  If it is not specified, by default the created service
				is transient and will be removed when the client exits.
                
                Additional local attributes to further control incoming services will be added in the future.
                
	@param		serviceDict	A dictionary containing the attributes for the new service
	@param		outServiceRecord A pointer to the newly created IOBluetoothSDPServiceRecordRef.  The assigned RFCOMM
				channel ID can be retrieved from the service record (as can other assigned parameters.)  This value 
				only gets set if kIOReturnSuccess is returned.  The caller is responsible for releasing the 
				IOBluetoothSDPServiceRecordRef when done.
	@result		Returns kIOReturnSuccess if successful.
 
 THIS CALL IS DEPRECATED IN 10.9.  PLEASE USE +[IOBluetoothSDPServiceRecord publishedServiceRecordWithDictionary:]

*/

extern IOReturn IOBluetoothAddServiceDict(CFDictionaryRef serviceDict, IOBluetoothSDPServiceRecordRef *outServiceRecord) DEPRECATED_IN_MAC_OS_X_VERSION_10_9_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothRemoveServiceWithRecordHandle
	@abstract	Removes the given service from the local SDP server.
	@discussion	The service record handle passed to this function must match the handle in the service record returned by 
                IOBluetoothAddServiceDict.
	@param		serviceRecordHandle The handle of the service to be removed.
	@result		Returns kIOReturnSuccess if successful.
 
    THIS CALL IS DEPRECATED IN 10.9.  PLEASE USE -[IOBluetoothSDPServiceRecord removeServiceRecord]

*/

extern IOReturn IOBluetoothRemoveServiceWithRecordHandle( BluetoothSDPServiceRecordHandle serviceRecordHandle ) DEPRECATED_IN_MAC_OS_X_VERSION_10_9_AND_LATER;


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
    @param status		(IOBluetoothObjectRef) The object that originated the notification.
    @result None.
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
    @result None.
*/

void IOBluetoothUserNotificationUnregister( IOBluetoothUserNotificationRef notificationRef );

/*!
    @function	IOBluetoothRegisterForDeviceConnectNotifications
	@abstract	Allows a client to register for device connect notifications for any connection.
	@discussion	The given callback will be called whenever any device connection is made.
	@param		callback	The callback to be called when a new connection is made
	@param		inRefCon	Client-supplied refCon to be passed to the callback.
	@result		Returns an IOBluetoothUserNotificationRef representing the outstanding device connect notification.
				To unregister the notification, call IOBluetoothUserNotificationUnregister() with the returned
				IOBluetoothUserNotificationRef.  If an error is encountered creating the notification, NULL is returned.  
				The returned IOBluetoothUserNotificationRef will be valid for as long as the notification is registered.
				It is not necessary to retain the result.  Once the notification is unregistered, it will no longer
				be valid.
*/

IOBluetoothUserNotificationRef IOBluetoothRegisterForDeviceConnectNotifications(	IOBluetoothUserNotificationCallback callback,
                                                                                    void * inRefCon );

/*!
    @function	IOBluetoothDeviceRegisterForDisconnectNotification
	@abstract	Allows a client to register for device disconnect notification.
	@discussion	The given callback will be called when the target device's connection is closed..
	@param		callback	The callback to be called when the target's connection is destroyed
	@param		inRefCon	Client-supplied refCon to be passed to the callback.
	@result		Returns an IOBluetoothUserNotificationRef representing the outstanding device disconnect notification.
				To unregister the notification, call IOBluetoothUserNotificationUnregister() with the returned
				IOBluetoothUserNotificationRef.  If an error is encountered creating the notification, NULL is returned.  
				The returned IOBluetoothUserNotificationRef will be valid for as long as the notification is registered.
				It is not necessary to retain the result.  Once the notification is unregistered, it will no longer
				be valid.
*/

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
				To unregister the notification, call IOBluetoothUserNotificationUnregister() with the returned
				IOBluetoothUserNotificationRef.  If an error is encountered creating the notification, NULL is returned.  
				The returned IOBluetoothUserNotificationRef will be valid for as long as the notification is registered.
				It is not necessary to retain the result.  Once the notification is unregistered, it will no longer
				be valid.
*/

IOBluetoothUserNotificationRef IOBluetoothRegisterForL2CAPChannelOpenNotifications(	IOBluetoothUserNotificationCallback callback,
                                                                                    void *inRefCon );

/*!
    @function	IOBluetoothRegisterForFilteredL2CAPChannelOpenNotifications
	@abstract	Allows a client to register for L2CAP channel open notifications for certain types of
				L2CAP channels.
	@discussion	The given callback will be called whenever any L2CAP channel is opened.
	@param		callback	The callback to be called when a new L2CAP channel is opened.
	@param		inRefCon	Client-supplied refCon to be passed to the callback.
	@param		psm			PSM to match a new L2CAP channel.  If the PSM doesn't matter, 0 may be passed in.
	@param		inDirection	The desired direction of the L2CAP channel - kIOBluetoothUserNotificationChannelDirectionAny
				if the direction doesn't matter.
	@result		Returns an IOBluetoothUserNotificationRef representing the outstanding L2CAP channel notification.
				To unregister the notification, call IOBluetoothUserNotificationUnregister() with the returned
				IOBluetoothUserNotificationRef.  If an error is encountered creating the notification, NULL is returned.  
				The returned IOBluetoothUserNotificationRef will be valid for as long as the notification is registered.
				It is not necessary to retain the result.  Once the notification is unregistered, it will no longer
				be valid.
*/

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
				To unregister the notification, call IOBluetoothUserNotificationUnregister() with the returned
				IOBluetoothUserNotificationRef.  If an error is encountered creating the notification, NULL is returned.  
				The returned IOBluetoothUserNotificationRef will be valid for as long as the notification is registered.
				It is not necessary to retain the result.  Once the notification is unregistered, it will no longer
				be valid.
*/

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
				To unregister the notification, call IOBluetoothUserNotificationUnregister() with the returned
				IOBluetoothUserNotificationRef.  If an error is encountered creating the notification, NULL is returned.  
				The returned IOBluetoothUserNotificationRef will be valid for as long as the notification is registered.
				It is not necessary to retain the result.  Once the notification is unregistered, it will no longer
				be valid.
*/

IOBluetoothUserNotificationRef IOBluetoothRegisterForRFCOMMChannelOpenNotifications(	IOBluetoothUserNotificationCallback callback,
                                                                                        void * inRefCon );

/*!
    @function	IOBluetoothRegisterForFilteredRFCOMMChannelOpenNotifications
	@abstract	Allows a client to register for RFCOMM channel open notifications for certain types of
				RFCOMM channels.
	@discussion	The given callback will be called whenever any RFCOMM channel is opened.
	@param		callback	The callback to be called when a new RFCOMM channel is opened.
	@param		inRefCon	Client-supplied refCon to be passed to the callback.
	@param		channeLID	RFCOMM channel ID to match a new RFCOMM channel.  If the channel ID doesn't matter, 0 may be passed in.
	@param		inDirection	The desired direction of the RFCOMM channel - kIOBluetoothUserNotificationChannelDirectionAny
				if the direction doesn't matter.
	@result		Returns an IOBluetoothUserNotificationRef representing the outstanding RFCOMM channel notification.
				To unregister the notification, call IOBluetoothUserNotificationUnregister() with the returned
				IOBluetoothUserNotificationRef.  If an error is encountered creating the notification, NULL is returned.  
				The returned IOBluetoothUserNotificationRef will be valid for as long as the notification is registered.
				It is not necessary to retain the result.  Once the notification is unregistered, it will no longer
				be valid.
*/

IOBluetoothUserNotificationRef IOBluetoothRegisterForFilteredRFCOMMChannelOpenNotifications(	IOBluetoothUserNotificationCallback callback,
                                                                                                void * inRefCon,
                                                                                                BluetoothRFCOMMChannelID channelID,
                                                                                                IOBluetoothUserNotificationChannelDirection inDirection );

/*!
    @function	IOBluetoothRFCOMMChannelRegisterForChannelCloseNotification
	@abstract	Allows a client to register for a channel close notification.
    @discussion	The given callback will be called when the RFCOMM channel is closed.
	@param		channel		The target RFCOMM channel
	@param		callback	Callback to be called when the RFCOMM channel is closed.
	@param		inRefCon	Client-supplied refCon to be passed to the callback.
	@result		Returns an IOBluetoothUserNotificationRef representing the outstanding RFCOMM channel close notification.
				To unregister the notification, call IOBluetoothUserNotificationUnregister() with the returned
				IOBluetoothUserNotificationRef.  If an error is encountered creating the notification, NULL is returned.  
				The returned IOBluetoothUserNotificationRef will be valid for as long as the notification is registered.
				It is not necessary to retain the result.  Once the notification is unregistered, it will no longer
				be valid.
*/

IOBluetoothUserNotificationRef IOBluetoothRFCOMMChannelRegisterForChannelCloseNotification(	IOBluetoothRFCOMMChannelRef inChannel,
                                                                                            IOBluetoothUserNotificationCallback callback,
                                                                                            void * inRefCon );
        
/*!
 @function	IOBluetoothAddSCOAudioDevice
 @abstract   Creates a persistent audio driver that will route audio data to/from the specified device.
 @discussion In 10.9 this is not needed and does nothing.
 @param		device	A paired Bluetooth audio device
 @param		configDict	Configuration dictionary containing a description of the audio controls to be attached to the driver.  Passing NULL will result in default controls
 @result		Returns kIOReturnSuccess if the audio driver was successfully created, error if hardware does not support SCO or device is not paired. On 10.9 it will always return kIOReturnSuccess.
 */
extern IOReturn IOBluetoothAddSCOAudioDevice( IOBluetoothDeviceRef device, CFDictionaryRef configDict ) DEPRECATED_IN_MAC_OS_X_VERSION_10_9_AND_LATER;

/*!
 @function	IOBluetoothRemoveSCOAudioDevice
 @abstract   Removes a persistent audio driver for a device that had already been added using IOBluetoothAddAudioDevice(). In 10.9 this is not needed and does nothing.
 @param		device	Bluetooth audio device to remove
 @result		Returns kIOReturnSuccess if the audio driver was successfully removed. On 10.9 it will always return kIOReturnSuccess
 */
extern IOReturn IOBluetoothRemoveSCOAudioDevice( IOBluetoothDeviceRef device ) DEPRECATED_IN_MAC_OS_X_VERSION_10_9_AND_LATER;


#ifdef	__cplusplus
	}
#endif

