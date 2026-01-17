//------------------------------------------------------------------------------------------------------------------------------
//
//  ICDevice.h
//  ImageCaptureCore
//
//  Copyright (c) 2008 Apple, Inc., all rights reserved.
//
//  Best viewed with the following settings: Tab width 4, Indent width 2, Wrap lines, Indent wrapped lines by 3, Page guide 128.
//
//------------------------------------------------------------------------------------------------------------------------------

#pragma once

/*!
    @header ICDevice
    ICDevice is an abstract class that represents a device supported by Image Capture. ImageCaptureCore defines two concrete subclasses of ICDevice, ICCameraDevice and ICScannerDevice. ICDeviceBrowser creates instances of these two subclasses to represent cameras and scanners it finds.
*/

//------------------------------------------------------------------------------------------------------------------------------

@class  ICDevice;

//------------------------------------------------------------------------------------------------------------------------------
/*!
  @ICDeviceType
  @abstract Image Capture Device Types
  @constant ICDeviceTypeCamera Camera device.
  @constant ICDeviceTypeScanner Scanner device.
*/

typedef NS_ENUM(NSUInteger, ICDeviceType)
{
    ICDeviceTypeCamera  = 0x00000001,
    ICDeviceTypeScanner = 0x00000002
};

/*!
  @ICDeviceLocationType
  @abstract Image Capture Device Location Types
  @constant ICDeviceLocationTypeLocal Device found directly attached to the Macintosh via its USB or FireWire port.
  @constant ICDeviceLocationTypeShared Device found over the network by searching for devices shared by other Macintosh hosts.
  @constant ICDeviceLocationTypeBonjour Device found over the network by searching for Bonjour services supported by Image Capture.
  @constant ICDeviceLocationTypeBluetooth Device found as a paired Bluetooth device.
*/

typedef NS_ENUM(NSUInteger, ICDeviceLocationType)
{
    ICDeviceLocationTypeLocal     = 0x00000100,
    ICDeviceLocationTypeShared    = 0x00000200,
    ICDeviceLocationTypeBonjour   = 0x00000400,
    ICDeviceLocationTypeBluetooth = 0x00000800
};

/*!
  @ICDeviceTypeMask
  @abstract Image Capture Device Type Mask
  @constant ICDeviceTypeMaskCamera Mask to detect a camera device.
  @constant ICDeviceTypeMaskScanner Mask to detect a scanner device.
*/

typedef NS_ENUM(NSUInteger, ICDeviceTypeMask)
{
    ICDeviceTypeMaskCamera  = 0x00000001,
    ICDeviceTypeMaskScanner = 0x00000002
};

/*!
  @ICDeviceLocationTypeMask
  @abstract Image Capture Device Location Type Mask
  @constant ICDeviceLocationTypeMaskLocal Mask to detect a local (e.g., USB or FireWire) device.
  @constant ICDeviceLocationTypeMaskShared Mask to detect a device by another Macintosh host.
  @constant ICDeviceLocationTypeMaskBonjour Mask to detect a network device that publishes a Bonjour service.
  @constant ICDeviceLocationTypeMaskBluetooth Mask to detect paired Bluetooth device.
  @constant ICDeviceLocationTypeMaskRemote Mask to detect a remote (shared, Bonjour, Bluetooth) device.
*/

typedef NS_ENUM( NSUInteger, ICDeviceLocationTypeMask )
{
    ICDeviceLocationTypeMaskLocal     = 0x00000100,
    ICDeviceLocationTypeMaskShared    = 0x00000200,
    ICDeviceLocationTypeMaskBonjour   = 0x00000400,
    ICDeviceLocationTypeMaskBluetooth = 0x00000800,
    ICDeviceLocationTypeMaskRemote    = 0x0000FE00
};

NS_ASSUME_NONNULL_BEGIN

//------------------------------------------------------------------------------------------------------------------------------
// Constants used to identify the transport type used by a device.
/*!
    @const      ICTransportTypeUSB
    @abstract   ICTransportTypeUSB
    @discussion Indicates that the device uses USB transport.
*/
extern NSString* const ICTransportTypeUSB;

/*!
    @const      ICTransportTypeFireWire
    @abstract   ICTransportTypeFireWire
    @discussion Indicates that the device uses FireWire transport.
*/
extern NSString *const ICTransportTypeFireWire;

/*!
    @const      ICTransportTypeBluetooth
    @abstract   ICTransportTypeBluetooth
    @discussion Indicates that the device uses Bluetooth transport.
*/
extern NSString *const ICTransportTypeBluetooth;

/*!
    @const      ICTransportTypeTCPIP
    @abstract   ICTransportTypeTCPIP
    @discussion Indicates that the device uses TCP/IP transport. These devices are discovered using Bonjour.
*/
extern NSString *const ICTransportTypeTCPIP;

/*!
    @const      ICTransportTypeMassStorage
    @abstract   ICTransportTypeMassStorage
    @discussion Indicates that the device use mounts as a mass-storage volume.
*/
extern NSString *const ICTransportTypeMassStorage;

//------------------------------------------------------------------------------------------------------------------------------
// Constants used for device location description.
/*!
    @const      ICDeviceLocationDescriptionUSB
    @abstract   ICDeviceLocationDescriptionUSB
    @discussion This description is returned for locationDescription property of a device connected to a USB port.
*/
extern NSString *const ICDeviceLocationDescriptionUSB;

/*!
    @const      ICDeviceLocationDescriptionFireWire
    @abstract   ICDeviceLocationDescriptionFireWire
    @discussion This description is returned for locationDescription property of a device connected to a FireWire port.
*/
extern NSString *const ICDeviceLocationDescriptionFireWire;

/*!
    @const      ICDeviceLocationDescriptionBluetooth
    @abstract   ICDeviceLocationDescriptionBluetooth
    @discussion This description is returned for locationDescription property of a device connected via Bluetooth.
*/
extern NSString *const ICDeviceLocationDescriptionBluetooth;

/*!
    @const      ICDeviceLocationDescriptionMassStorage
    @abstract   ICDeviceLocationDescriptionMassStorage
    @discussion This description is returned for locationDescription property of a device that is mounted as a mass-storage volume.
*/
extern NSString *const ICDeviceLocationDescriptionMassStorage;

//------------------------------------------------------------------------------------------------------------------------------
// Constants used to identify button-press on a device.
/*!
    @const      ICButtonTypeScan
    @abstract   ICButtonTypeScan
    @discussion Indicates that the "Scan" button on the device was pressed.
*/
extern NSString *const ICButtonTypeScan;

/*!
    @const      ICButtonTypeMail
    @abstract   ICButtonTypeMail
    @discussion Indicates that the "Mail" button on the device was pressed.
*/
extern NSString *const ICButtonTypeMail;

/*!
    @const      ICButtonTypeCopy
    @abstract   ICButtonTypeCopy
    @discussion Indicates that the "Copy" button on the device was pressed.
*/
extern NSString *const ICButtonTypeCopy;

/*!
    @const      ICButtonTypeWeb
    @abstract   ICButtonTypeWeb
    @discussion Indicates that the "Web" button on the device was pressed.
*/
extern NSString *const ICButtonTypeWeb;

/*!
    @const      ICButtonTypePrint
    @abstract   ICButtonTypePrint
    @discussion Indicates that the "Print" button on the device was pressed.
*/
extern NSString *const ICButtonTypePrint;

/*!
    @const      ICButtonTypeTransfer
    @abstract   ICButtonTypeTransfer
    @discussion Indicates that the "Transfer" button on the device was pressed.
*/
extern NSString *const ICButtonTypeTransfer;

//------------------------------------------------------------------------------------------------------------------------------
// Constants used for device status notifications.
/*!
    @const      ICStatusNotificationKey
    @abstract   ICStatusNotificationKey
    @discussion Key for a non-localized notification string.
*/
extern NSString *const ICStatusNotificationKey;

/*!
    @const      ICStatusCodeKey
    @abstract   ICStatusCodeKey
    @discussion One of values defined in ICReturnCode.
*/
extern NSString *const ICStatusCodeKey;

/*!
    @const      ICLocalizedStatusNotificationKey
    @abstract   ICLocalizedStatusNotificationKey
    @discussion Key for a localized notification string.
*/
extern NSString *const ICLocalizedStatusNotificationKey;

//------------------------------------------------------------------------------------------------------------------------------
// Constants used to describe capabilities of a device
/*!
    @const      ICDeviceCanEjectOrDisconnect
    @abstract   ICDeviceCanEjectOrDisconnect
    @discussion Indicates either the device is mounted as a mass-storage volume and can be ejected or the it is a remote device with an active connection that can be disconnected.
*/
extern NSString *const ICDeviceCanEjectOrDisconnect;


//------------------------------------------------------------------------------------------------------------- ICDeviceDelegate
/*! 
  @protocol ICDeviceDelegate <NSObject>
  @abstract A delegate of ICDevice must conform to ICDeviceDelegate protocol.
*/

@protocol ICDeviceDelegate <NSObject>

@required

/*! 
  @method didRemoveDevice:
  @abstract This message is sent to the delegate to inform that a device has been removed.
*/
- (void)didRemoveDevice:(ICDevice*)device;

@optional

/*! 
  @method device:didOpenSessionWithError:
  @abstract This message is sent when a session is opened on a device.
  @discussion This message completes the process initiated by the message "requestOpenSession" sent to the device object.
*/
- (void)device:(ICDevice*)device didOpenSessionWithError:(nullable NSError*)error;

/*! 
  @method deviceDidBecomeReady:
  @abstract This message is sent when the device is ready to receive requests.
  @discusson A camera device is ready, when it is ready to receive requests. A scanner device is ready when its functional units are found and the default functional unit is selected for use and is ready to receive requests. The device will become ready to receive requests only after a session is opened.
*/
- (void)deviceDidBecomeReady:(ICDevice*)device;

/*! 
  @method device:didCloseSessionWithError:
  @abstract This message is sent when a session is closed on a device.
  @discussion This message completes the process initiated by the message "requestCloseSession" sent to the device object. This message is also sent if the device module in control of the device ceases to control the device.
*/
- (void)device:(ICDevice*)device didCloseSessionWithError:(nullable NSError*)error;

/*! 
  @method deviceDidChangeName:
  @abstract This message is sent if the name of a device changes.
  @discussion This happens if the device module overrides the default name of the device reported by the device's transport layer, or if the name of the filesystem volume mounted by the device is changed by the user.
*/
- (void)deviceDidChangeName:(ICDevice*)device;

/*! 
  @method deviceDidChangeSharingState:
  @abstract This message is sent when the sharing state of a device has changes.
  @discusson Any Image Capture client application can choose to share the device over the network using the sharing or webSharing facility in Image Capture.
*/
- (void)deviceDidChangeSharingState:(ICDevice*)device;

/*! 
  @method device:didReceiveStatusInformation:
  @abstract This message is sent to the device delegate when status information is received from a camera or a scanner. In Mac OS X 10.6 this delegate is not called for camera devices. This may change in the future releases of Mac OS X.
  @discussion The 'status' dictionary contains two keys, ICStatusNotificationKey and ICLocalizedStatusNotificationKey, which are defined above. If type of 'device' is ICDeviceTypeScanner, the value of ICStatusNotificationKey will be one of the values defined in ICScannerDevice.h (e.g., ICScannerStatusWarmingUp, ICScannerStatusWarmUpDone, or ICScannerStatusRequestsOverviewScan); the value of ICLocalizedStatusNotificationKey will be a localized status information string suitable for displaying to the user. */
- (void)device:(ICDevice*)device didReceiveStatusInformation:( NSDictionary<NSString*,id>*)status;

/*! 
  @method device:didEncounterError:
  @abstract This message is sent to the device delegate when a camera or scanner device encounters an error.
*/
- (void)device:(ICDevice*)device didEncounterError:(nullable NSError*)error;

/*! 
  @method device:didReceiveButtonPress:
  @abstract This message is sent to the device delegate if a button is pressed on the device.
  @discussion This message is sent only if a session is open on the device. The value of 'buttonType' argument is one of the ICButtonType* values defined above.
*/
- (void)device:(ICDevice*)device didReceiveButtonPress:( NSString*)buttonType;

/*! 
  @method device:didReceiveCustomNotification:data:
  @abstract This message is sent to the device delegate the device sends a custom notification 'notification' with an arbitrary byte buffer 'data'.
  @discussion This message is sent only if a session is open on the device.
*/
- (void)device:(ICDevice*)device didReceiveCustomNotification:(NSDictionary<NSString*,id>*)notification data:(NSData*)data;

@end

//--------------------------------------------------------------------------------------------------------------------- ICDevice
/*! 
  @class ICDevice
  @abstract ICDevice is an abstract class that represents a device supported by Image Capture facility. ImageCaptureCore defines two concrete subclasses of ICDevice, ICCameraDevice and ICScannerDevice. ICDeviceBrowser creates instances of these two subclasses to represent cameras and scanners it finds.
*/

@interface ICDevice : NSObject
{
@private
    id _deviceProperties;
}

/*! 
  @property delegate
  @abstract The delegate to receive messages once a session is opened on the device.
  @discussion The delegate must conform to ICDeviceDelegate protocol. In addition it should respond to selectors defined in ICCameraDeviceDelegate or ICScannerDeviceDelegate protocols in order to effectively interact with the device object. The messages this delegate can expect to receive are described by these protocols. NOTES: (1) The delegate is not retain by the ICDevice instance. Therefore the delegate property of the ICDevice instance must be set to NULL before the delegate is released. (2) Since communication with the device object is done asynchronously, changing the delegate after opening a session may result in unexpected behavior; e.g., expected delegate method(s) may not be invoked.
*/
@property(assign,nullable)               id <ICDeviceDelegate> delegate;

/*!
    @property type
    @abstract ￼The type of the device as defined by ICDeviceType OR'd with its ICDeviceLocationType. The type of this device can be obtained by AND'ing the value retuned by this property with an appropriate ICDeviceTypeMask. The location type of this device can be obtained by AND'ing the value retuned by this property with an appropriate ICDeviceLocationTypeMask.

*/
@property(readonly)                     ICDeviceType          type;

/*!
    @property name
    @abstract ￼Name of the device as reported by the device module or by the device transport when a device module is not in control of this device. This name may change if the device module overrides the default name of the device reported by the device's transport, or if the name of the filesystem volume mounted by the device is changed by the user.

*/
@property(readonly,nullable)            NSString*             name;

/*!
    @property icon
    @abstract ￼Icon image for the device.

*/
@property(readonly,nullable)            CGImageRef            icon;

/*!
    @property capabilities
    @abstract ￼The capabilities of the device as reported by the device module.

*/
@property(readonly, nonnull)            NSArray<NSString*>*   capabilities;

/*!
    @property modulePath
    @abstract ￼Filesystem path of the device module that is associated with this device. Camera-specific capabilities are defined in ICCameraDevice.h and scanner-specific capabilities are defined in ICScannerDevice.h.

*/
@property(readonly, nonnull)            NSString*             modulePath;

/*!
    @property moduleVersion
    @abstract ￼The bundle version of the device module associated with this device. This may change if an existing device module associated with this device is updated or a new device module for this device is installed.

*/
@property(readonly)             NSString*             moduleVersion;

/*!
    @property moduleExecutableArchitecture
    @abstract ￼Executable Architecture of the device module in control of this device. This is equal to a value as defined in NSBundle.h or CFBundle.h.

*/
@property(readonly)                     int                   moduleExecutableArchitecture; 

/*!
    @property remote
    @abstract ￼Indicates whether the device is a remote device published by Image Capture device sharing facility.

*/
@property(readonly, getter=isRemote)    BOOL                  remote;

/*!
    @property shared
    @abstract ￼Indicates whether the device is shared using the Image Capture device sharing facility. This value will change when sharing of this device is enabled or disabled.

*/
@property(readonly, getter=isShared)    BOOL                  shared;

/*!
    @property hasConfigurableWiFiInterface
    @abstract ￼Indicates whether the device can be configured for use on a WiFi network.

*/
@property(readonly)                     BOOL                  hasConfigurableWiFiInterface;

/*!
    @property transportType
    @abstract ￼The transport type used by the device. The possible values are: ICTransportTypeUSB, ICTransportTypeFireWire, ICTransportTypeBluetooth, ICTransportTypeTCPIP, or ICTransportTypeMassStorage.

*/
@property(readonly)             NSString*             transportType;

/*!
    @property usbLocationID
    @abstract ￼The USB location ID of a USB device in the IOKit registry. This will be 0 for non-USB devices.

*/
@property(readonly)                     int                   usbLocationID;

/*!
    @property usbProductID
    @abstract ￼The USB product ID of a USB device in the IOKit registry. This will be 0 for non-USB devices.

*/
@property(readonly)                     int                   usbProductID;

/*!
    @property usbVendorID
    @abstract ￼The USB vendor ID of a USB device in the IOKit registry. This will be 0 for non-USB devices.

*/
@property(readonly)                     int                   usbVendorID;

/*!
    @property fwGUID
    @abstract ￼The FireWire GUID of a FireWire device in the IOKit registry. This will be 0 for non-FireWire devices.

*/
@property(readonly)                     long long             fwGUID;

/*!
    @property serialNumberString
    @abstract ￼The serial number of the device. This will be NULL if the device does not provide a serial number.

*/
@property(readonly,nullable)            NSString*             serialNumberString;

/*!
    @property locationDescription
    @abstract ￼A non-localized location description string for the device.
    @discussion The value returned in one of the location description strings defined above, or location obtained from the Bonjour TXT record of a network device.

*/
@property(readonly,nullable)            NSString*             locationDescription;

/*!
    @property hasOpenSession
    @abstract ￼Indicates whether the device has an open session.

*/
@property(readonly)                     BOOL                  hasOpenSession;

/*!
    @property UUIDString
    @abstract ￼A string representation of the Universally Unique ID of the device.

*/
@property(readonly,nullable)            NSString*             UUIDString;

/*!
    @property persistentIDString
    @abstract ￼A string representation of the persistent ID of the device.

*/
@property(readonly,nullable)            NSString*             persistentIDString;

/*!
    @property buttonPressed
    @abstract ￼A string object with one of the ICButtonType* values defined above.

*/
@property(readonly)             NSString*             buttonPressed;

/*!
    @property autolaunchApplicationPath
    @abstract ￼Filesystem path of an application that is to be automatically launched when this device is added.

*/
@property(readwrite,copy,nullable)      NSString*             autolaunchApplicationPath;

/*!
    @property userData
    @abstract ￼A mutable dictionary to store arbitrary key-value pairs associated with a device object. This can be used by view objects that bind to this object to store "house-keeping" information.

*/
@property(readonly,nullable)            NSMutableDictionary*  userData;

/*! 
  @method requestOpenSession:
  @abstract This message requests to open a session on the device. A client MUST open a session on a device in order to use the device.
  @discussion Make sure the receiver's delegate is set prior to sending this message; otherwise this message will be ignored. This request is completed when the delegate receives a "device:didOpenSessionWithError:" message. No more messages will be sent to the delegate if this request fails.
*/
- (void)requestOpenSession;

/*! 
  @method requestCloseSession
  @abstract This message requests to close a previously opened session on this device.
  @discussion This request is completed when the delegate receives a "device:didCloseSessionWithError:" message. This will be the last message sent to the delegate.
*/
- (void)requestCloseSession;

/*! 
  @method requestYield
  @abstract This message requests the device module in control of this device to yield control.
  @discussion This message should be used only if the client is planning on communiting with the device directly. The device module may not yield control of the device if it has an open session.
*/
- (void)requestYield;

/*! 
  @method requestSendMessage:outData:maxReturnDataSize:sendMessageDelegate:didSendMessageSelector:contextInfo:
  @abstract This method asynchronously sends an arbitrary message with optional data to a device.
  @discussion This method allows developers to send a private message from a client application to a device module. This method is the functional equivalent of calling ICAObjectSendMessage() found in ImageCapture.framework, which has been deprecated in Mac OS X 10.6. The response to this command will be delivered using didSendMessageSelector of sendMessageDelegate. The didSendMessageSelector should have the same signature as: - (void)didSendMessage:(UInt32)messageCode inData:(NSData*)data error:(NSError*)error contextInfo:(void*)contextInfo. The content of error returned should be examined to determine if the request completed successfully. NOTE: This method SHOULD NOT BE USED to send PTP pass-through commands to a PTP camera. Please refer to 'requestSendPTPCommand:outData:sendCommandDelegate:sendCommandDelegate:contextInfo:' defined in ICCameraDevice.h for sending PTP pass-through commands.
*/
- (void)requestSendMessage:(unsigned int)messageCode outData:(NSData*)data maxReturnedDataSize:(unsigned int)maxReturnedDataSize sendMessageDelegate:(id)sendMessageDelegate didSendMessageSelector:(SEL)selector contextInfo:(nullable void*)contextInfo;

/*! 
  @method requestEjectOrDisconnect
  @abstract Eject the media if permitted by the device, or disconnect from a remote device.
*/
- (void)requestEjectOrDisconnect;

NS_ASSUME_NONNULL_END

@end

//------------------------------------------------------------------------------------------------------------------------------
