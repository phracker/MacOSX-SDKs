//------------------------------------------------------------------------------------------------------------------------------
//
//  ICDevice.h
//  ImageCaptureCore
//
//  Copyright (c) 2008-2019 Apple Inc., all rights reserved.
//
//  Best viewed with the following settings: Tab width 4, Indent width 2, Wrap lines, Indent wrapped lines by 3, Page guide 128.
//
//------------------------------------------------------------------------------------------------------------------------------

#pragma once

#import <ImageCaptureCore/ImageCapturePlatform.h>
#import <CoreGraphics/CGImage.h>

@protocol ICDeviceDelegate;

//------------------------------------------------------------------------------------------------------------------------------
/*!
 @const ICDeviceType
 @abstract Image Capture Device Types
 @constant ICDeviceTypeCamera Camera device.
 @constant ICDeviceTypeScanner Scanner device.
 */

typedef NS_ENUM(NSUInteger, ICDeviceType)
{
    ICDeviceTypeCamera  = 0x00000001,
    ICDeviceTypeScanner = 0x00000002
} IC_AVAILABLE(macos(10.4),ios(13.0));

/*!
 @const ICDeviceLocationType
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
}  IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @const ICDeviceTypeMask
 @abstract Image Capture Device Type Mask
 @constant ICDeviceTypeMaskCamera Mask to detect a camera device.
 @constant ICDeviceTypeMaskScanner Mask to detect a scanner device.
 */
typedef NS_ENUM(NSUInteger, ICDeviceTypeMask)
{
    ICDeviceTypeMaskCamera  = 0x00000001,
    ICDeviceTypeMaskScanner = 0x00000002
} IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @const ICDeviceLocationTypeMask
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
} IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

@class ICDevice,ICCameraDevice,NSError, NSDictionary, NSData, NSMutableDictionary;

CF_ASSUME_NONNULL_BEGIN

typedef NSString* ICDeviceTransport NS_TYPED_ENUM IC_AVAILABLE(macos(10.4), ios(13.0));

//------------------------------------------------------------------------------------------------------------------------------
// Constants used to identify the transport type used by a device.

/*!
 @const      ICTransportTypeUSB
 @abstract   Indicates that the device uses USB transport.
 */
IMAGECAPTURE_EXTERN ICDeviceTransport const ICTransportTypeUSB IC_AVAILABLE(macos(10.4),ios(13.0));

/*!
 @const      ICTransportTypeFireWire
 @abstract   Indicates that the device uses FireWire transport.
 */
IMAGECAPTURE_EXTERN ICDeviceTransport const ICTransportTypeFireWire IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @const      ICTransportTypeBluetooth
 @abstract   Indicates that the device uses Bluetooth transport.
 */
IMAGECAPTURE_EXTERN ICDeviceTransport const ICTransportTypeBluetooth IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @const      ICTransportTypeMassStorage
 @abstract   Indicates that the device use mounts as a mass-storage volume.
 */
IMAGECAPTURE_EXTERN ICDeviceTransport const ICTransportTypeMassStorage IC_AVAILABLE(macos(10.4),ios(13.0));

/*!
 @const      ICTransportTypeExFAT
 @abstract   Indicates that the device use mounts as a exFat storage volume.
 */
IMAGECAPTURE_EXTERN ICDeviceTransport const ICTransportTypeExFAT IC_AVAILABLE(ios(10.0)) IC_UNAVAILABLE(macos);

/*!
 @const      ICTransportTypeTCPIP
 @abstract   Indicates that the device uses TCP/IP transport. These devices are discovered using Bonjour.
 */
IMAGECAPTURE_EXTERN ICDeviceTransport const ICTransportTypeTCPIP IC_AVAILABLE(macos(10.4),ios(13.0));

typedef NSString* ICDeviceStatus NS_TYPED_ENUM;

//------------------------------------------------------------------------------------------------------------------------------
// Constants used for device status notifications.
/*!
 @const      ICStatusNotificationKey
 @abstract   Key for a non-localized notification string.
 */
IMAGECAPTURE_EXTERN ICDeviceStatus const ICStatusNotificationKey IC_AVAILABLE(macos(10.4),ios(13.0));

/*!
 @const      ICStatusCodeKey
 @abstract   One of values defined in ICReturnCode.
 */
IMAGECAPTURE_EXTERN ICDeviceStatus const ICStatusCodeKey IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @const      ICLocalizedStatusNotificationKey
 @abstract   Key for a localized notification string.
 */
IMAGECAPTURE_EXTERN ICDeviceStatus const ICLocalizedStatusNotificationKey IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

typedef NSString* ICDeviceCapability NS_TYPED_ENUM;

//------------------------------------------------------------------------------------------------------------------------------
// Constants used to describe capabilities of a device
/*!
 @const      ICDeviceCanEjectOrDisconnect
 @abstract   Indicates either the device is mounted as a mass-storage volume and can be ejected or the it is a remote device with an active connection that can be disconnected.
 */
IMAGECAPTURE_EXTERN ICDeviceCapability const ICDeviceCanEjectOrDisconnect IC_AVAILABLE(macos(10.4), ios(13.0));

typedef NSString* ICSessionOptions NS_TYPED_ENUM IC_AVAILABLE(macos(10.15),ios(13.0));

IMAGECAPTURE_EXTERN ICSessionOptions const ICEnumerationChronologicalOrder IC_AVAILABLE(macos(10.15),ios(13.0));

typedef NSString* ICDeviceLocationOptions NS_TYPED_ENUM;

//------------------------------------------------------------------------------------------------------------------------------
// Constants used for device location description.
/*!
 @const      ICDeviceLocationDescriptionUSB
 @abstract   This description is returned for locationDescription property of a device connected to a USB port.
 */
IMAGECAPTURE_EXTERN ICDeviceLocationOptions const ICDeviceLocationDescriptionUSB IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);
/*!
 @const      ICDeviceLocationDescriptionFireWire
 @abstract   This description is returned for locationDescription property of a device connected to a FireWire port.
 */
IMAGECAPTURE_EXTERN ICDeviceLocationOptions const ICDeviceLocationDescriptionFireWire IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);
/*!
 @const      ICDeviceLocationDescriptionBluetooth
 @abstract   This description is returned for locationDescription property of a device connected via Bluetooth.
 */
IMAGECAPTURE_EXTERN ICDeviceLocationOptions const ICDeviceLocationDescriptionBluetooth IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);
/*!
 @const      ICDeviceLocationDescriptionMassStorage
 @abstract   This description is returned for locationDescription property of a device that is mounted as a mass-storage volume.
 */
IMAGECAPTURE_EXTERN ICDeviceLocationOptions const ICDeviceLocationDescriptionMassStorage IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

//--------------------------------------------------------------------------------------------------------------------- ICDevice
/*!
 @class ICDevice
 @abstract ICDevice is an abstract class that represents a device supported by Image Capture facility. ImageCaptureCore defines two concrete subclasses of ICDevice, ICCameraDevice and ICScannerDevice. ICDeviceBrowser creates instances of these two subclasses to represent cameras and scanners it finds.
 */
IC_AVAILABLE(macos(10.4), ios(13.0))
@interface ICDevice : NSObject

/*!
 @property delegate
 @abstract The delegate to receive messages once a session is opened on the device.
 @discussion The delegate must conform ICDeviceDelegate protocol. In addition it should respond to selectors defined in ICCameraDeviceDelegate protocol in order to effectively interact with the device object. The messages this delegate can expect to receive are described by these protocols.
 */
@property (nonatomic, readwrite, assign, nullable) id <ICDeviceDelegate> delegate IC_AVAILABLE(macos(10.4),ios(13.0));

/*!
 @property type
 @abstract ￼The type of the device as defined by ICDeviceType OR'd with its ICDeviceLocationType.
 @note The type of this device can be obtained by AND'ing the value retuned by this property with an appropriate ICDeviceTypeMask.
 @note The location type of this device can be obtained by AND'ing the value retuned by this property with an appropriate ICDeviceLocationTypeMask.
 */
@property (nonatomic, readonly) ICDeviceType type IC_AVAILABLE(macos(10.4),ios(13.0));

/*!
 @property capabilities
 @abstract ￼The capabilities of the device as reported by the device module.
 */
@property (nonatomic, readonly) NSArray<NSString*>* capabilities IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property name
 @abstract ￼Name of the device as reported by the device module or by the device transport when a device module is not in control of this device.
 @note This name may change if the device module overrides the default name of the device reported by the device's transport, or if the name of the filesystem volume mounted by the device is changed by the user.
 */
@property (nonatomic, readonly, copy, nullable) NSString* name IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property productKind
 @abstract ￼Type of the device. Possible values are: @"iPhone", @"iPod", @"iPad", @"Camera", @"Scanner"
 */
@property (nonatomic, readonly, copy, nullable) NSString* productKind IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property icon
 @abstract ￼Icon image for the device class.  If there is no custom icon present from a device manufacturer, this will be a rendered version of the system symbol for the device class.  Using a rendered system symbol instead of the systemSymbolName is discouraged.
 */
@property (nonatomic, readonly, nullable) CGImageRef icon IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
@property systemSymbolName
@abstract ￼Standard system symbol used to represent the device class.  Using the symbol to render an appropriate device icon will ensure proper scaling for high resolution devices.
*/
@property (nonatomic, readonly, copy, nullable) NSString* systemSymbolName IC_AVAILABLE(macos(11.0)) IC_UNAVAILABLE(ios);

/*!
 @property transportType
 @abstract ￼The transport type used by the device. The possible values are: ICTransportTypeUSB or ICTransportTypeMassStorage.
 */
@property (nonatomic, readonly, copy, nullable) NSString* transportType IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property UUIDString
 @abstract ￼A string representation of the Universally Unique ID of the device.
 */
@property (nonatomic, readonly, copy, nullable) NSString* UUIDString IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property locationDescription
 @abstract ￼A non-localized location description string for the device.
 @discussion The value returned in one of the location description strings defined above, or location obtained from the Bonjour TXT record of a network device.
 */
@property (nonatomic, readonly, nullable) NSString* locationDescription IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property hasOpenSession
 @abstract ￼Indicates whether the device has an open session.
 */
@property (nonatomic, readonly) BOOL hasOpenSession IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property userData
 @abstract ￼Client convenience bookkeeping object retained by the framework.
 */
@property (nonatomic, readonly, nullable) NSMutableDictionary* userData IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property modulePath
 @abstract ￼Filesystem path of the device module that is associated with this device. Camera-specific capabilities are defined in ICCameraDevice.h and scanner-specific capabilities are defined in ICScannerDevice.h.
 */
@property (nonatomic, readonly ) NSString* modulePath IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property moduleVersion
 @abstract ￼The bundle version of the device module associated with this device.
 @note This may change if an existing device module associated with this device is updated or a new device module for this device is installed.
 */
@property (nonatomic, readonly, nullable) NSString* moduleVersion IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property serialNumberString
 @abstract ￼The serial number of the device. This will be NULL if the device does not provide a serial number.
 */
@property (nonatomic, readonly, nullable) NSString* serialNumberString IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property usbLocationID
 @abstract ￼The USB location of which the device is occupying.
 */
@property (nonatomic, readonly) int usbLocationID IC_AVAILABLE(macos(10.4),ios(13.0));

/*!
 @property usbProductID
 @abstract ￼The USB PID associated with the device attached.
 */
@property (nonatomic, readonly) int usbProductID IC_AVAILABLE(macos(10.4),ios(13.0));

/*!
 @property usbVendorID
 @abstract ￼The USB VID associated with the device attached.
 */
@property (nonatomic, readonly) int usbVendorID IC_AVAILABLE(macos(10.4),ios(13.0));

#pragma mark - Delegate API

/*!
 @method requestOpenSession
 @abstract This message requests to open a session on the device.
 @discussion Make sure the receiver's delegate is set prior to sending this message; otherwise this message will be ignored. This request is completed when the delegate receives a "device:didOpenSessionWithError:" message.
 @note Execution of the delegate callback will occur on the main thread.
 */
- (void)requestOpenSession IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @method requestCloseSession
 @abstract This message requests to close a previously opened session on this device.
 @discussion This request is completed when the delegate receives a "device:didCloseSessionWithError:" message.
 @note Execution of the delegate callback will occur on the main thread.
 */
- (void)requestCloseSession IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @method requestEject
 @abstract Eject the media if permitted by the device, or disconnect from a remote device.
 */
- (void)requestEject IC_AVAILABLE(macos(10.4), ios(13.0));


//------------------------------------------------------------------------------------------------------------- ICDeviceDelegate
/*!
 @protocol ICDeviceDelegate <NSObject>
 @abstract A delegate of ICDevice must conform to ICDeviceDelegate protocol.
 @note Unless otherwise noted, all completion blocks will execute on the thread initially called from.
 */
#pragma mark - Block API

/*!
 @method requestOpenSessionWithOptions:completion
 @abstract This message requests to open a session on the device.
 @discussion This request will execute the completion handler provided upon return.
 @note The completion block will execute on an any available queue, often this will not be the main queue.
 */
- (void)requestOpenSessionWithOptions:(NSDictionary<ICSessionOptions, id>* _Nullable)options
                           completion:(void (^)(NSError* _Nullable error))completion IC_AVAILABLE(macos(10.15), ios(13.0));

/*!
 @method requestCloseSessionWithOptions:completion
 @abstract This message requests to close a previously opened session on this device.
 @discussion This request will execute the completion handler provided upon return.
 @note The completion block will execute on an any available queue, often this will not be the main queue.
 */
- (void)requestCloseSessionWithOptions:(NSDictionary<ICSessionOptions, id>* _Nullable)options
                            completion:(void (^)(NSError* _Nullable error))completion IC_AVAILABLE(macos(10.15), ios(13.0));

/*!
 @method requestEjectWithCompletion:
 @abstract Eject the media, or disconnect the device - if permitted by the device.
 @discussion This request will execute the completion handler provided upon return.
 @note The completion block will execute on an any available queue, often this will not be the main queue.
 */
- (void)requestEjectWithCompletion:(void (^)(NSError* _Nullable error))completion IC_AVAILABLE(macos(10.15), ios(13.0));

#pragma mark - macOS only

/*!
 @property autolaunchApplicationPath
 @abstract ￼Filesystem path of an application that is to be automatically launched when this device is added.
 */
@property (nonatomic, readwrite, copy, nullable) NSString* autolaunchApplicationPath IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property remote
 @abstract ￼Indicates whether the device is a remote device published by Image Capture device sharing facility.
 @property name
 @discussion ￼Name of the device as reported by the device module or by the device transport when a device module is not in control of this device.
 @note This name may change if the device module overrides the default name of the device reported by the device's transport, or if the name of the filesystem volume mounted by the device is changed by the user.
 */
@property (readonly, getter=isRemote) BOOL remote IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property persistentIDString
 @abstract ￼A string representation of the persistent ID of the device.
 */
@property (nonatomic, readonly, nullable) NSString* persistentIDString IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @method requestSendMessage:outData:maxReturnDataSize:sendMessageDelegate:didSendMessageSelector:contextInfo:
 @abstract This method asynchronously sends an arbitrary message with optional data to a device.
 @discussion This method allows developers to send a private message from a client application to a device module.
 
 The response to this command will be delivered using didSendMessageSelector of sendMessageDelegate.
 The didSendMessageSelector should have the same signature as: - (void)didSendMessage:(UInt32)messageCode inData:(NSData*)data error:(NSError*)error contextInfo:(void*)contextInfo.
 
 The content of error returned should be examined to determine if the request completed successfully.
 @note This method should not be used to send PTP pass-through commands to a PTP camera.
 Please refer to 'requestSendPTPCommand:outData:sendCommandDelegate:sendCommandDelegate:contextInfo:' defined in ICCameraDevice.h for sending PTP pass-through commands.
 @note Execution of the delegate callback will occur on the main thread.
 */
- (void)requestSendMessage:(unsigned int)messageCode outData:(NSData*)data maxReturnedDataSize:(unsigned int)maxReturnedDataSize sendMessageDelegate:(id)sendMessageDelegate didSendMessageSelector:(SEL)selector contextInfo:(void* _Nullable)contextInfo IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

#pragma mark - Deprecated

/*!
 @method requestEjectOrDisconnect
 @abstract Eject the media if permitted by the device, or disconnect from a remote device.
 */
- (void)requestEjectOrDisconnect IC_DEPRECATED_WITH_REPLACEMENT("Use requestEject, or requestEjectWithCompletion:", macos(10.4,10.15)) IC_UNAVAILABLE(ios);

/*!
 @method requestYield
 @abstract This message requests the device module in control of this device to yield control.
 @discussion This message should be used only if the client is planning on communicating with the device directly. The device module may not yield control of the device if it has an open session.
 */
- (void)requestYield IC_DEPRECATED("Requesting a device yield is no longer avaialble", macos(10.4,10.15)) IC_UNAVAILABLE(ios);

/*!
 @property moduleExecutableArchitecture
 @abstract Reports the device module servicing the requests executable architecture.
 */
@property (readonly) int moduleExecutableArchitecture IC_DEPRECATED("Module executable architecture is no longer available",macos(10.4,10.15)) IC_UNAVAILABLE(ios);

@end

//------------------------------------------------------------------------------------------------------------- ICDeviceDelegate
/*!
 @protocol ICDeviceDelegate <NSObject>
 @abstract A delegate of ICDevice must conform to ICDeviceDelegate protocol.
 @note Unless otherwise noted, all delegate callbacks will occur on the main thread.
 */

@protocol ICDeviceDelegate <NSObject>

@required

/*!
 @method device:didCloseSessionWithError:
 @abstract This message is sent when a session is closed on a device.
 @discussion This message completes the process initiated by the message "requestCloseSession" sent to the device object. This message is also sent if the device module in control of the device ceases to control the device.
 @note Execution of the delegate callback will occur on the main thread.
 */
- (void)device:(ICDevice*)device didCloseSessionWithError:(NSError* _Nullable)error IC_AVAILABLE(macos(10.4),ios(13.0));

/*!
 @method didRemoveDevice:
 @abstract This message is sent to the delegate to inform that a device has been removed.
 */
- (void)didRemoveDevice:(ICDevice*)device IC_AVAILABLE(macos(10.4),ios(13.0));

/*!
 @method device:didOpenSessionWithError:
 @abstract This message is sent when a session is opened on a device.
 @discussion This message completes the process initiated by the message "requestOpenSession" sent to the device object.
 @note Execution of the delegate callback will occur on the main thread.
 */
- (void)device:(ICDevice*)device didOpenSessionWithError:(NSError* _Nullable) error IC_AVAILABLE(macos(10.4),ios(13.0));

@optional

/*!
 @method deviceDidBecomeReady:
 @abstract This message is sent when the device is ready to receive requests.
 @note Execution of the delegate callback will occur on the main thread.
 */
- (void)deviceDidBecomeReady:(ICDevice*)device IC_AVAILABLE(macos(10.4),ios(13.0));


/*!
 @method deviceDidChangeName:
 @abstract This message is sent if the name of a device changes.
 @discussion This happens if the device module overrides the default name of the device reported by the device's transport layer, or if the name of the filesystem volume mounted by the device is changed by the user.
 @note Execution of the delegate callback will occur on the main thread.
 */
- (void)deviceDidChangeName:(ICDevice*)device IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @method device:didReceiveStatusInformation:
 @abstract This message is sent to the device delegate when status information is received from a device.
 @discussion The 'status' dictionary contains two keys, ICStatusNotificationKey and ICLocalizedStatusNotificationKey, which are defined above.  Status information keys are located in their respective ICDevice type class header.
 @note Execution of the delegate callback will occur on the main thread.
 */
- (void)device:(ICDevice*)device didReceiveStatusInformation:( NSDictionary<ICDeviceStatus,id>*)status IC_AVAILABLE(macos(10.4),ios(13.0));

/*!
 @method device:didEncounterError:
 @abstract This message is sent to the device delegate a device encounters an error.
 @note Execution of the delegate callback will occur on the main thread.
 */
- (void)device:(ICDevice*)device didEncounterError:(NSError* _Nullable) error IC_AVAILABLE(macos(10.4),ios(13.0));

/*!
 @method device:didEjectWithError:
 @abstract This message is sent to the device delegate when the eject has completed.
 @note Execution of the delegate callback will occur on the main thread.
 */
- (void)device:(ICDevice*)device didEjectWithError:(NSError* _Nullable) error IC_AVAILABLE(macos(10.4),ios(13.0));

#pragma mark - ICDeviceDelegate Deprecated

/*!
 @method deviceDidChangeSharingState:
 @abstract This message is sent when the sharing state of a device has changes.
 @discusson Any Image Capture client application can choose to share the device over the network using the sharing or webSharing facility in Image Capture.
 @note Execution of the delegate callback will occur on the main thread.
 */
- (void)deviceDidChangeSharingState:(ICDevice*)device IC_DEPRECATED("Device sharing is no longer available",macos(10.4,10.15)) IC_UNAVAILABLE(ios);

@end



CF_ASSUME_NONNULL_END

