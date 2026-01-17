#if !__has_include(<AVFCapture/AVExternalStorageDevice.h>)
/*
    File:  AVExternalStorageDevice.h
 
    Framework:  AVFoundation
 
    Copyright 2022-2023 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVFCapture.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark - AVExternalStorageDevice

/*!
 @class AVExternalStorageDevice
 @abstract
	An AVExternalStorageDevice represents a physical external storage device connected to the device that can be used to store captured media assets.

 @discussion
	Each instance of AVExternalStorageDevice corresponds to a physical external storage device where captured media assets can be stored. Instances of AVExternalStorageDevice cannot be created directly. An array of all currently available external storage devices can be obtained using AVExternalStorageDeviceDiscoverySession.

	Instances of AVExternalStorageDevice can be used with AVCaptureFileOutput subclasses for writing media files.
 */
API_AVAILABLE(macos(14.0), ios(17.0), macCatalyst(17.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVExternalStorageDevice : NSObject

AV_INIT_UNAVAILABLE

/*!
 @property displayName
 @abstract
	Display name of the external storage device.

 @discussion
	This property can be used for displaying the name of an external storage device in a user interface. Will return nil if we fail to extract information from external storage device.
 */
@property(nullable, nonatomic, readonly) NSString *displayName;

/*!
 @property freeSize
 @abstract
	Current free size in bytes.

 @discussion
	This property represents the free size available on the external storage device. Will return -1 if we fail to extract information from external storage device.

 */
@property(nonatomic, readonly) NSInteger freeSize;

/*!
 @property totalSize
 @abstract
	Total storage size in bytes.

 @discussion
	This property represents the total storage size available on the external storage device. Will return -1 if we fail to extract information from external storage device.

 */
@property(nonatomic, readonly) NSInteger totalSize;

/*!
 @property connected
 @abstract
	Indicates whether the external storage device is connected and available to the system.

 @discussion
	The property gives the current connection status of the external storage device.

 */
@property(nonatomic, readonly, getter=isConnected) BOOL connected;

/*!
 @property uuid
 @abstract
	A unique identifier for external storage device.

 @discussion
	This property can be used to select a specific external storage device with ImageCapture framework APIs to read media assets. Will return nil if we fail to extract information from external storage device.
	For example the string value of this property will match the value from [ICDevice UUIDString].
 */
@property(nullable, nonatomic, readonly) NSUUID *uuid;

/*!
 @property notRecommendedForCaptureUse
 @abstract
    Indicates whether the external storage device is not recommended for capture use.

 @discussion
    This property is used to let the client know if the external storage device is not suitable for camera capture.
 */
@property(nonatomic, readonly, getter=isNotRecommendedForCaptureUse) BOOL notRecommendedForCaptureUse;

/*!
 @method nextAvailableURLsWithPathExtensions:error:
 @abstract
	Next available security-scoped, DCF compliant URL array with different path extensions.

 @param extensionArray
	An array of path extensions for the next available URL requested.
 @param outError
	An out parameter with error information indicating why the URL could not be provided. If this method is successful, error will be nil.
 @result
	An array of DCF compliant security-scoped URL with all the path extensions requested.

 @discussion
	Configures the folder structure (create a DCIM folder if there isn't one already) on the external storage device to provide the next available unique DCF compliant security-scoped URL array with different path extensions.

	Security-scoped URL requires the use of startAccessingSecurityScopedResource, and stopAccessingSecurityScopedResource for access.
	[nextAvailableURL startAccessingSecurityScopedResource];
	. . .
	// your code to capture image / video
	. . .
	[nextAvailableURL stopAccessingSecurityScopedResource];

	Use the +requestAccessWithCompletionHandler: method to request access to external storage device before getting the next available URL array else an error will be thrown.
 */
- (nullable NSArray<NSURL *> *)nextAvailableURLsWithPathExtensions:(nonnull NSArray<NSString *> *)extensionArray error:(NSError * _Nullable * _Nullable)outError;

@end

API_AVAILABLE(macos(14.0), ios(17.0), macCatalyst(17.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVExternalStorageDevice (AVExternalStorageDeviceAuthorization)

/*!
 @property authorizationStatus
 @abstract
	Returns the client's authorization status for capturing onto an external storage device connected to this device.

 @discussion
	This method returns the AVAuthorizationStatus of the client for capturing onto an external storage device connected to this device. If the status is AVAuthorizationStatusNotDetermined, you may use the +requestAccessWithCompletionHandler: method to request access by prompting the user.
 */
@property(class, readonly) AVAuthorizationStatus authorizationStatus;

/*!
 @method requestAccessWithCompletionHandler:
 @abstract
	Requests access to capture onto an external storage device connected to this device, showing a dialog to the user if necessary.

 @param handler
	A completion handler block called with the result of requesting access to capture onto an external storage device.

 @discussion
	Use this method to request access to capture onto an external storage device connected to this device.

	This call will not block while the user is being asked for access, allowing the client to continue running. Until access has been granted, trying to capture into detected external storage devices will result in an error. The user is only asked for permission the first time the client requests access, later calls use the authorization status selected by the user.

	The completion handler is called on an arbitrary dispatch queue. It is the client's responsibility to ensure that any UIKit-related updates are called on the main queue or main thread as a result.
 */
+ (void)requestAccessWithCompletionHandler:(void (^)(BOOL granted))handler;

@end

#pragma mark - AVExternalStorageDeviceDiscoverySession

/*!
 @class AVExternalStorageDeviceDiscoverySession
 @abstract
	AVExternalStorageDeviceDiscoverySession is used to monitor connection / disconnection of external storage devices to the device.

 @discussion
	AVExternalStorageDeviceDiscoverySession is a singleton that lists the external storage devices connected to this device. The client is expected to key-value observe the externalStorageDevices property for changes to the external storage devices list.
 */
API_AVAILABLE(macos(14.0), ios(17.0), macCatalyst(17.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVExternalStorageDeviceDiscoverySession : NSObject

AV_INIT_UNAVAILABLE

/*!
 @@property sharedSession
 @abstract
	Returns the singleton instance of the external storage device discovery session.

 @discussion
	There is only one external storage device discovery session for each host device which can be accessed using this method. Will return nil if the device doesn't support external storage devices.
 */
@property(class, readonly, nullable) AVExternalStorageDeviceDiscoverySession *sharedSession;

/*!
 @property externalStorageDevices
 @abstract
	An array of external storage devices connected to this device. Read only. Key-value observable.

 @discussion
	An array of AVExternalStorageDevice objects connected to this device. The list is updated when the external storage device detected status changes.
 */
@property(readonly) NSArray<AVExternalStorageDevice *> *externalStorageDevices;

/*!
 @property supported
 @abstract
	Whether the external storage devices are supported by this device.

 @discussion
	A value of YES indicates that external storage devices are supported while NO indicates it is not.
 */
@property(class, readonly, getter=isSupported) BOOL supported;

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCapture/AVExternalStorageDevice.h>
#endif
