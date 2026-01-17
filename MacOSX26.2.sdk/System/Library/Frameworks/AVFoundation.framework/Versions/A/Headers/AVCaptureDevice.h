#if !__has_include(<AVFCapture/AVCaptureDevice.h>)
/*
    File:  AVCaptureDevice.h
 
    Framework:  AVFoundation
 
    Copyright 2010-2023 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVCaptureSessionPreset.h>
#import <AVFoundation/AVCaptureReactions.h>
#import <AVFoundation/AVMediaFormat.h>
#import <Foundation/Foundation.h>
#import <CoreMedia/CMFormatDescription.h>
#import <CoreGraphics/CGBase.h>
#import <CoreGraphics/CGGeometry.h>

@class CALayer;

NS_ASSUME_NONNULL_BEGIN

/*!
 @constant AVCaptureDeviceWasConnectedNotification
 @abstract
    Posted when a device becomes available on the system.
 
 @discussion
    The notification object is an AVCaptureDevice instance representing the device that became available.
 */
AVF_EXPORT NSNotificationName const AVCaptureDeviceWasConnectedNotification NS_SWIFT_NAME(AVCaptureDevice.wasConnectedNotification) API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0), tvos(17.0), visionos(2.1)) API_UNAVAILABLE(watchos);

/*!
 @constant AVCaptureDeviceWasDisconnectedNotification
 @abstract
    Posted when a device becomes unavailable on the system.
 
 @discussion
    The notification object is an AVCaptureDevice instance representing the device that became unavailable.
 */
AVF_EXPORT NSNotificationName const AVCaptureDeviceWasDisconnectedNotification NS_SWIFT_NAME(AVCaptureDevice.wasDisconnectedNotification) API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0), tvos(17.0), visionos(2.1)) API_UNAVAILABLE(watchos);

/*!
 @constant AVCaptureDeviceSubjectAreaDidChangeNotification
 @abstract
    Posted when the instance of AVCaptureDevice has detected a substantial change to the video subject area.
 
 @discussion
    Clients may observe the AVCaptureDeviceSubjectAreaDidChangeNotification to know when an instance of AVCaptureDevice has detected a substantial change to the video subject area. This notification is only sent if you first set subjectAreaChangeMonitoringEnabled to YES.
  */
AVF_EXPORT NSNotificationName const AVCaptureDeviceSubjectAreaDidChangeNotification NS_SWIFT_NAME(AVCaptureDevice.subjectAreaDidChangeNotification) API_AVAILABLE(ios(5.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);


#pragma mark - AVCaptureDevice

@class AVCaptureDeviceFormat;
@class AVCaptureDeviceInputSource;
@class AVCaptureSystemPressureState;
@class AVCaptureDeviceInternal;
@class AVZoomRange;

/*!
 @class AVCaptureDevice
 @abstract
    An AVCaptureDevice represents a physical device that provides realtime input media data, such as video and audio.
 
 @discussion
    Each instance of AVCaptureDevice corresponds to a device, such as a camera or microphone. Instances of AVCaptureDevice cannot be created directly. An array of all currently available devices can also be obtained using the AVCaptureDeviceDiscoverySession. Devices can provide one or more streams of a given media type. Applications can search for devices matching desired criteria by using AVCaptureDeviceDiscoverySession, or may obtain a reference to the default device matching desired criteria by using +[AVCaptureDevice defaultDeviceWithDeviceType:mediaType:position:].
 
    Instances of AVCaptureDevice can be used to provide media data to an AVCaptureSession by creating an AVCaptureDeviceInput with the device and adding that to the capture session.
 */
API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0), tvos(17.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface AVCaptureDevice : NSObject
{
@private
    AVCaptureDeviceInternal *_internal;
}

AV_INIT_UNAVAILABLE

/*!
 @method devices
 @abstract
    Returns an array of devices currently available for use as media input sources.
 
 @result
    An NSArray of AVCaptureDevice instances for each available device.
 
 @discussion
    This method returns an array of AVCaptureDevice instances for input devices currently connected and available for capture. The returned array contains all devices that are available at the time the method is called. Applications should observe AVCaptureDeviceWasConnectedNotification and AVCaptureDeviceWasDisconnectedNotification to be notified when the list of available devices has changed.
 */
+ (NSArray<AVCaptureDevice *> *)devices API_DEPRECATED("Use AVCaptureDeviceDiscoverySession instead.", ios(4.0, 10.0), macos(10.7, 10.15)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(tvos);

/*!
 @method devicesWithMediaType:
 @abstract
    Returns an array of devices currently available for use as sources of media with the given media type.
 
 @param mediaType
    The media type, such as AVMediaTypeVideo, AVMediaTypeAudio, or AVMediaTypeMuxed, supported by each returned device.
 @result
    An NSArray of AVCaptureDevice instances for each available device.
 
 @discussion
    This method returns an array of AVCaptureDevice instances for input devices currently connected and available for capture that provide media of the given type. Media type constants are defined in AVMediaFormat.h. The returned array contains all devices that are available at the time the method is called. Applications should observe AVCaptureDeviceWasConnectedNotification and AVCaptureDeviceWasDisconnectedNotification to be notified when the list of available devices has changed.
 */
+ (NSArray<AVCaptureDevice *> *)devicesWithMediaType:(AVMediaType)mediaType API_DEPRECATED("Use AVCaptureDeviceDiscoverySession instead.", ios(4.0, 10.0), macos(10.7, 10.15)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(tvos);

/*!
 @method defaultDeviceWithMediaType:
 @abstract
    Returns an AVCaptureDevice instance for the default device of the given media type.
 
 @param mediaType
    The media type, such as AVMediaTypeVideo, AVMediaTypeAudio, or AVMediaTypeMuxed, supported by the returned device.
 @result
    The default device with the given media type, or nil if no device with that media type exists.
 
 @discussion
    This method returns the default device of the given media type currently available on the system. For example, for AVMediaTypeVideo, this method will return the built in camera that is primarily used for capture and recording. Media type constants are defined in AVMediaFormat.h.
 */
+ (nullable AVCaptureDevice *)defaultDeviceWithMediaType:(AVMediaType)mediaType API_AVAILABLE(visionos(2.1));

/*!
 @method deviceWithUniqueID:
 @abstract
    Returns an AVCaptureDevice instance with the given unique ID.
 
 @param deviceUniqueID
    The unique ID of the device instance to be returned.
 @result
    An AVCaptureDevice instance with the given unique ID, or nil if no device with that unique ID is available.
 
 @discussion
    Every available capture device has a unique ID that persists on one system across device connections and disconnections, application restarts, and reboots of the system itself. This method can be used to recall or track the status of a specific device whose unique ID has previously been saved.
 */
+ (nullable AVCaptureDevice *)deviceWithUniqueID:(NSString *)deviceUniqueID API_AVAILABLE(visionos(2.1));

/*!
 @property uniqueID
 @abstract
    An ID unique to the model of device corresponding to the receiver.
 
 @discussion
    Every available capture device has a unique ID that persists on one system across device connections and disconnections, application restarts, and reboots of the system itself. Applications can store the value returned by this property to recall or track the status of a specific device in the future.
 */
@property(nonatomic, readonly) NSString *uniqueID;

/*!
 @property modelID
 @abstract
    The model ID of the receiver.
 
 @discussion
    The value of this property is an identifier unique to all devices of the same model. The value is persistent across device connections and disconnections, and across different systems. For example, the model ID of the camera built in to two identical iPhone models will be the same even though they are different physical devices.
 */
@property(nonatomic, readonly) NSString *modelID API_AVAILABLE(visionos(2.1));

/*!
 @property localizedName
 @abstract
    A localized human-readable name for the receiver.
 
 @discussion
    This property can be used for displaying the name of a capture device in a user interface.
 */
@property(nonatomic, readonly) NSString *localizedName;

/*!
 @property manufacturer
 @abstract
    The human-readable manufacturer name for the receiver.
 
 @discussion
    This property can be used to identify capture devices from a particular manufacturer. All Apple devices return "Apple Inc.". Devices from third party manufacturers may return an empty string.
 */
@property(nonatomic, readonly) NSString *manufacturer API_AVAILABLE(macos(10.9), ios(14.0), macCatalyst(14.0), tvos(17.0), visionos(2.1)) API_UNAVAILABLE(watchos);

/*!
 @property transportType
 @abstract
    The transport type of the receiver (e.g. USB, PCI, etc).
 
 @discussion
    This property can be used to discover the transport type of a capture device. Transport types are defined in <IOKit/audio/IOAudioTypes.h> as kIOAudioDeviceTransportType*.
 */
@property(nonatomic, readonly) int32_t transportType API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(ios, watchos, tvos, visionos);

/*!
 @method hasMediaType:
 @abstract
    Returns whether the receiver provides media with the given media type.
 
 @param mediaType
    A media type, such as AVMediaTypeVideo, AVMediaTypeAudio, or AVMediaTypeMuxed.
 @result
    YES if the device outputs the given media type, NO otherwise.
 
 @discussion
    Media type constants are defined in AVMediaFormat.h.
 */
- (BOOL)hasMediaType:(AVMediaType)mediaType;

/*!
 @method lockForConfiguration:
 @abstract
    Requests exclusive access to configure device hardware properties.
 
 @param outError
    On return, if the device could not be locked, points to an NSError describing why the failure occurred.
 @result
    A BOOL indicating whether the device was successfully locked for configuration.
 
 @discussion
    In order to set hardware properties on an AVCaptureDevice, such as focusMode and exposureMode, clients must first acquire a lock on the device. Clients should only hold the device lock if they require settable device properties to remain unchanged. Holding the device lock unnecessarily may degrade capture quality in other applications sharing the device.
 */
- (BOOL)lockForConfiguration:(NSError * _Nullable * _Nullable)outError;

/*!
 @method unlockForConfiguration
 @abstract
    Release exclusive control over device hardware properties.
 
 @discussion
    This method should be called to match an invocation of lockForConfiguration: when an application no longer needs to keep device hardware properties from changing automatically.
 */
- (void)unlockForConfiguration;

/*!
 @method supportsAVCaptureSessionPreset:
 @abstract
    Returns whether the receiver can be used in an AVCaptureSession configured with the given preset.
 
 @param preset
    An AVCaptureSession preset.
 @result
    YES if the receiver can be used with the given preset, NO otherwise.
 
 @discussion
    An AVCaptureSession instance can be associated with a preset that configures its inputs and outputs to fulfill common use cases. This method can be used to determine if the receiver can be used in a capture session with the given preset. Presets are defined in AVCaptureSession.h.
 */
- (BOOL)supportsAVCaptureSessionPreset:(AVCaptureSessionPreset)preset API_UNAVAILABLE(visionos);

/*!
 @property connected
 @abstract
    Indicates whether the device is connected and available to the system.
 
 @discussion
    The value of this property is a BOOL indicating whether the device represented by the receiver is connected and available for use as a capture device. Clients can key value observe the value of this property to be notified when a device is no longer available. When the value of this property becomes NO for a given instance, it will not become YES again. If the same physical device again becomes available to the system, it will be represented using a new instance of AVCaptureDevice.
 */
@property(nonatomic, readonly, getter=isConnected) BOOL connected API_AVAILABLE(visionos(2.1));

/*!
 @property inUseByAnotherApplication
 @abstract
    Indicates whether the device is in use by another application.
 
 @discussion
    The value of this property is a BOOL indicating whether the device represented by the receiver is in use by another application. Clients can key value observe the value of this property to be notified when another app starts or stops using this device.
 */
@property(nonatomic, readonly, getter=isInUseByAnotherApplication) BOOL inUseByAnotherApplication API_AVAILABLE(macCatalyst(14.0)) API_UNAVAILABLE(ios, watchos, tvos, visionos);

/*!
 @property suspended
 @abstract
    Indicates whether the device is suspended.
 
 @discussion
    The value of this property is a BOOL indicating whether the device represented by the receiver is currently suspended. Some devices disallow data capture due to a feature on the device. For example, isSuspended returns YES for the external iSight when its privacy iris is closed, or for the internal iSight on a notebook when the notebook's display is closed. Clients can key value observe the value of this property to be notified when the device becomes suspended or unsuspended.
 */
@property(nonatomic, readonly, getter=isSuspended) BOOL suspended API_AVAILABLE(ios(14.0), macCatalyst(14.0), tvos(17.0), visionos(2.1)) API_UNAVAILABLE(watchos);

/*!
 @property linkedDevices
 @abstract
    An array of AVCaptureDevice objects physically linked to the receiver.
 
 @discussion
    The value of this property is an array of AVCaptureDevice objects that are a part of the same physical device as the receiver. For example, for the external iSight camera, linkedDevices returns an array containing an AVCaptureDevice for the external iSight microphone.
 */
@property(nonatomic, readonly) NSArray<AVCaptureDevice *> *linkedDevices API_UNAVAILABLE(ios, macCatalyst, watchos, tvos, visionos);

/*!
 @property formats
 @abstract
    An array of AVCaptureDeviceFormat objects supported by the receiver.
 
 @discussion
    This property can be used to enumerate the formats natively supported by the receiver. The capture device's activeFormat property may be set to one of the formats in this array. Clients can observe automatic changes to the receiver's formats by key value observing this property.
 */
@property(nonatomic, readonly) NSArray<AVCaptureDeviceFormat *> *formats API_AVAILABLE(ios(7.0), macCatalyst(14.0), tvos(17.0), visionos(1.0));

/*!
 @property activeFormat
 @abstract
    The currently active format of the receiver.
 
 @discussion
    This property can be used to get or set the currently active device format.
 
    -setActiveFormat: throws an NSInvalidArgumentException if set to a format not present in the formats array.
 
    -setActiveFormat: throws an NSGenericException if called without first obtaining exclusive access to the receiver using lockForConfiguration:.
 
    Clients can observe automatic changes to the receiver's activeFormat by key value observing this property.
 
    On iOS, use of AVCaptureDevice's setActiveFormat: and AVCaptureSession's setSessionPreset: are mutually exclusive. If you set a capture device's active format, the session to which it is attached changes its preset to AVCaptureSessionPresetInputPriority. Likewise if you set the AVCaptureSession's sessionPreset property, the session assumes control of its input devices, and configures their activeFormat appropriately. Note that audio devices do not expose any user-configurable formats on iOS. To configure audio input on iOS, you should use the AVAudioSession APIs instead (see AVAudioSession.h).
 
    The activeFormat, activeVideoMinFrameDuration, and activeVideoMaxFrameDuration properties may be set simultaneously by using AVCaptureSession's begin/commitConfiguration methods:
 
    [session beginConfiguration]; // the session to which the receiver's AVCaptureDeviceInput is added.
    if ( [device lockForConfiguration:&error] ) {
        [device setActiveFormat:newFormat];
        [device setActiveVideoMinFrameDuration:newMinDuration];
        [device setActiveVideoMaxFrameDuration:newMaxDuration];
        [device unlockForConfiguration];
    }
    [session commitConfiguration]; // The new format and frame rates are applied together in commitConfiguration
 
    Note that when configuring a session to use an active format intended for high resolution still photography and applying one or more of the following operations to an AVCaptureVideoDataOutput, the system may not meet the target framerate: zoom, orientation changes, format conversion.
 */
@property(nonatomic, retain) AVCaptureDeviceFormat *activeFormat API_AVAILABLE(ios(7.0), macCatalyst(14.0), tvos(17.0), visionos(1.0));

/*!
 @property activeVideoMinFrameDuration
 @abstract
    A property indicating the receiver's current active minimum frame duration (the reciprocal of its max frame rate).
 
 @discussion
    An AVCaptureDevice's activeVideoMinFrameDuration property is the reciprocal of its active maximum frame rate. To limit the max frame rate of the capture device, clients may set this property to a value supported by the receiver's activeFormat (see AVCaptureDeviceFormat's videoSupportedFrameRateRanges property). Clients may set this property's value to kCMTimeInvalid to return activeVideoMinFrameDuration to its default value for the given activeFormat.
 
    -setActiveVideoMinFrameDuration: throws an NSInvalidArgumentException if set to an unsupported value.
 
    -setActiveVideoMinFrameDuration: throws an NSGenericException if called without first obtaining exclusive access to the receiver using lockForConfiguration:.
 
    Clients can observe automatic changes to the receiver's activeVideoMinFrameDuration by key value observing this property.
 
    On iOS, the receiver's activeVideoMinFrameDuration resets to its default value under the following conditions:
        - The receiver's activeFormat changes
        - The receiver's AVCaptureDeviceInput's session's sessionPreset changes
        - The receiver's AVCaptureDeviceInput is added to a session
 
    When exposureMode is AVCaptureExposureModeCustom, setting the activeVideoMinFrameDuration affects max frame rate, but not exposureDuration. You may use setExposureModeCustomWithDuration:ISO:completionHandler: to set a shorter exposureDuration than your activeVideoMinFrameDuration, if desired.

    When autoVideoFrameRateEnabled is true, setting activeVideoMinFrameDuration throws an NSInvalidArgumentException.
 */
@property(nonatomic) CMTime activeVideoMinFrameDuration API_AVAILABLE(ios(7.0), macCatalyst(14.0), tvos(17.0), visionos(1.0));

/*!
 @property activeVideoMaxFrameDuration
 @abstract
    A property indicating the receiver's current active maximum frame duration (the reciprocal of its min frame rate).
 
 @discussion
    An AVCaptureDevice's activeVideoMaxFrameDuration property is the reciprocal of its active minimum frame rate. To limit the min frame rate of the capture device, clients may set this property to a value supported by the receiver's activeFormat (see AVCaptureDeviceFormat's videoSupportedFrameRateRanges property). Clients may set this property's value to kCMTimeInvalid to return activeVideoMaxFrameDuration to its default value for the given activeFormat.
 
    -setActiveVideoMaxFrameDuration: throws an NSInvalidArgumentException if set to an unsupported value.
 
    -setActiveVideoMaxFrameDuration: throws an NSGenericException if called without first obtaining exclusive access to the receiver using lockForConfiguration:.
 
    Clients can observe automatic changes to the receiver's activeVideoMaxFrameDuration by key value observing this property.
 
    On iOS, the receiver's activeVideoMaxFrameDuration resets to its default value under the following conditions:
        - The receiver's activeFormat changes
        - The receiver's AVCaptureDeviceInput's session's sessionPreset changes
        - The receiver's AVCaptureDeviceInput is added to a session
 
    When exposureMode is AVCaptureExposureModeCustom, frame rate and exposure duration are interrelated. If you call setExposureModeCustomWithDuration:ISO:completionHandler: with an exposureDuration longer than the current activeVideoMaxFrameDuration, the activeVideoMaxFrameDuration will be lengthened to accommodate the longer exposure time. Setting a shorter exposure duration does not automatically change the activeVideoMinFrameDuration or activeVideoMaxFrameDuration. To explicitly increase the frame rate in custom exposure mode, you must set the activeVideoMaxFrameDuration to a shorter value. If your new max frame duration is shorter than the current exposureDuration, the exposureDuration will shorten as well to accommodate the new frame rate.

    When autoVideoFrameRateEnabled is true, setting activeVideoMaxFrameDuration throws an NSInvalidArgumentException.
 */
@property(nonatomic) CMTime activeVideoMaxFrameDuration API_AVAILABLE(macos(10.9), ios(7.0), macCatalyst(14.0), tvos(17.0), visionos(1.0));

/// Whether the device's video frame rate (expressed as a duration) is currently locked.
///
/// Returns `true` when an ``AVCaptureDeviceInput`` associated with the device has its ``AVCaptureDeviceInput/activeLockedVideoFrameDuration`` property set to something other than `kCMTimeInvalid`. See ``AVCaptureDeviceInput/activeLockedVideoFrameDuration`` for more information on video frame duration locking.
@property(nonatomic, readonly, getter=isVideoFrameDurationLocked) BOOL videoFrameDurationLocked API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// The maximum frame rate (expressed as a minimum duration) that can be set on an input associated with this device.
///
/// `kCMTimeInvalid` is returned when the device or its current configuration does not support locked frame rate. Use ``AVCaptureDeviceInput/activeLockedVideoFrameDuration`` to set the locked frame rate on the input.
@property(nonatomic, readonly) CMTime minSupportedLockedVideoFrameDuration API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// Whether the device is following an external sync device.
///
/// See ``AVCaptureDeviceInput/followExternalSyncDevice:videoFrameDuration:delegate:`` for more information on external sync.
@property(nonatomic, readonly, getter=isFollowingExternalSyncDevice) BOOL followingExternalSyncDevice API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// The minimum frame duration that can be passed as the `videoFrameDuration` when directing your device input to follow an external sync device.
///
/// Use this property as the minimum allowable frame duration to pass to ``AVCaptureDeviceInput/follow:externalSyncDevice:videoFrameDuration:delegate:`` when you want to follow an external sync device. This property returns `kCMTimeInvalid` when the device's' current configuration does not support external sync device following.
@property(nonatomic, readonly) CMTime minSupportedExternalSyncFrameDuration API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// Indicates whether the receiver should enable auto video frame rate.
///
/// When you enable this property, the device automatically adjusts the active frame rate, depending on light level. Under low light conditions, it decreases the frame rate to properly expose the scene. For formats with a maximum frame rate of 30 fps, the device switches the frame rate between 30 - 24. For formats with a maximum frame rate of 60 fps, the device switches the frame rate between 60 - 30 - 24.
///
/// Setting this property throws an `NSInvalidArgumentException` if the active format's ``AVCaptureDeviceFormat/autoVideoFrameRateSupported`` returns `false`. When you change the device's active format, this property resets to its default value of `false`.
///
/// If you set this property to `true`, frame rate is under device control, and you may not set ``activeVideoMinFrameDuration`` or ``activeVideoMaxFrameDuration``. Doing so throws an `NSInvalidArgumentException`.
///
/// - Note: Setting this property to `true` throws an `NSInvalidArgumentException` if ``videoFrameDurationLocked`` or ``followingExternalSyncDevice`` are `true`.
@property(nonatomic, getter=isAutoVideoFrameRateEnabled) BOOL autoVideoFrameRateEnabled API_AVAILABLE(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @property inputSources
 @abstract
    An array of AVCaptureDeviceInputSource objects supported by the receiver.
 
 @discussion
    Some devices can capture data from one of multiple data sources (different input jacks on the same audio device, for example). For devices with multiple possible data sources, inputSources can be used to enumerate the possible choices. Clients can observe automatic changes to the receiver's inputSources by key value observing this property.
 */
@property(nonatomic, readonly) NSArray<AVCaptureDeviceInputSource *> *inputSources API_UNAVAILABLE(ios, macCatalyst, watchos, tvos, visionos);

/*!
 @property activeInputSource
 @abstract
    The currently active input source of the receiver.
 
 @discussion
    This property can be used to get or set the currently active device input source. -setActiveInputSource: throws an NSInvalidArgumentException if set to a value not present in the inputSources array. -setActiveInputSource: throws an NSGenericException if called without first obtaining exclusive access to the receiver using lockForConfiguration:. Clients can observe automatic changes to the receiver's activeInputSource by key value observing this property.
 */
@property(nonatomic, retain, nullable) AVCaptureDeviceInputSource *activeInputSource API_UNAVAILABLE(ios, macCatalyst, watchos, tvos, visionos);

@end


/*!
 @enum AVCaptureDevicePosition
 @abstract
    Constants indicating the physical position of an AVCaptureDevice's hardware on the system.
 
 @constant AVCaptureDevicePositionUnspecified
    Indicates that the device's position relative to the system hardware is unspecified.
 @constant AVCaptureDevicePositionBack
    Indicates that the device is physically located on the back of the system hardware.
 @constant AVCaptureDevicePositionFront
    Indicates that the device is physically located on the front of the system hardware.
 */
typedef NS_ENUM(NSInteger, AVCaptureDevicePosition) {
    AVCaptureDevicePositionUnspecified = 0,
    AVCaptureDevicePositionBack        = 1,
    AVCaptureDevicePositionFront       = 2,
} API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0), tvos(17.0), visionos(1.0)) API_UNAVAILABLE(watchos);


API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0), tvos(17.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface AVCaptureDevice (AVCaptureDevicePosition)

/*!
 @property position
 @abstract
    Indicates the physical position of an AVCaptureDevice's hardware on the system.
 
 @discussion
    The value of this property is an AVCaptureDevicePosition indicating where the receiver's device is physically located on the system hardware.
 */
@property(nonatomic, readonly) AVCaptureDevicePosition position;

@end


/*!
 @group AVCaptureDeviceType string constants
 
 @discussion
    The AVCaptureDeviceType string constants are intended to be used in combination with the AVCaptureDeviceDiscoverySession class to obtain a list of devices matching certain search criteria.
 */
typedef NSString *AVCaptureDeviceType NS_TYPED_ENUM API_AVAILABLE(macos(10.15), ios(10.0), macCatalyst(14.0), tvos(17.0), visionos(2.1)) API_UNAVAILABLE(watchos);

/*!
 @constant AVCaptureDeviceTypeExternal
    An external device type. On iPad, external devices are those that conform to the UVC (USB Video Class) specification.
 
 @discussion
    Starting in Mac Catalyst 17.0, apps may opt in for using AVCaptureDeviceTypeExternal by adding the following key to their Info.plist:
        <key>NSCameraUseExternalDeviceType</key>
        <true/>
    Otherwise, external cameras on Mac Catalyst report that their device type is AVCaptureDeviceTypeBuiltInWideAngleCamera.
 
    Prior to visionOS 3.0, your app must have the `com.apple.developer.avfoundation.uvc-device-access` entitlement in order to discover and use devices of type `AVCaptureDeviceTypeExternal` on visionOS.
 */
AVF_EXPORT AVCaptureDeviceType const AVCaptureDeviceTypeExternal API_AVAILABLE(macos(14.0), ios(17.0), macCatalyst(17.0), tvos(17.0), visionos(2.1)) API_UNAVAILABLE(watchos);

/*!
 @constant AVCaptureDeviceTypeMicrophone
    A microphone. On iOS and tvOS, only one AVCaptureDevice of type AVCaptureDeviceTypeMicrophone is exposed to the system. The audio routing subsystem decides which physical microphone to use, be it a built in microphone, a wired headset, an external microphone, etc. The microphone device's `localizedName` will change as the audio subsystem switches to a different physical device.
 */
AVF_EXPORT AVCaptureDeviceType const AVCaptureDeviceTypeMicrophone API_AVAILABLE(macos(14.0), ios(17.0), macCatalyst(17.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos) ;

/*!
 @constant AVCaptureDeviceTypeBuiltInWideAngleCamera
    A built-in wide angle camera device. These devices are suitable for general purpose use.
 */
AVF_EXPORT AVCaptureDeviceType const AVCaptureDeviceTypeBuiltInWideAngleCamera API_AVAILABLE(macos(10.15), ios(10.0), macCatalyst(14.0), tvos(17.0), visionos(2.1)) API_UNAVAILABLE(watchos);

/*!
 @constant AVCaptureDeviceTypeBuiltInTelephotoCamera
    A built-in camera device with a longer focal length than a wide angle camera. Note that devices of this type may only be discovered using an AVCaptureDeviceDiscoverySession.
 */
AVF_EXPORT AVCaptureDeviceType const AVCaptureDeviceTypeBuiltInTelephotoCamera API_AVAILABLE(ios(10.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

/*!
 @constant AVCaptureDeviceTypeBuiltInUltraWideCamera
    A built-in camera device with a shorter focal length than a wide angle camera. Note that devices of this type may only be discovered using an AVCaptureDeviceDiscoverySession.
 */
AVF_EXPORT AVCaptureDeviceType const AVCaptureDeviceTypeBuiltInUltraWideCamera API_AVAILABLE(ios(13.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

/*!
 @constant AVCaptureDeviceTypeBuiltInDualCamera
    A device that consists of two fixed focal length cameras, one wide and one telephoto. Note that devices of this type may only be discovered using an AVCaptureDeviceDiscoverySession or -[AVCaptureDevice defaultDeviceWithDeviceType:mediaType:position:].
 
    A device of this device type supports the following features:
    - Auto switching from one camera to the other when zoom factor, light level, and focus position allow this.
    - Higher quality zoom for still captures by fusing images from both cameras.
    - Depth data delivery by measuring the disparity of matched features between the wide and telephoto cameras.
    - Delivery of photos from constituent devices (wide and telephoto cameras) via a single photo capture request.
 
    A device of this device type does not support the following features:
    - AVCaptureExposureModeCustom and manual exposure bracketing.
    - Locking focus with a lens position other than AVCaptureLensPositionCurrent.
    - Locking auto white balance with device white balance gains other than AVCaptureWhiteBalanceGainsCurrent.
 
    Even when locked, exposure duration, ISO, aperture, white balance gains, or lens position may change when the device switches from one camera to the other. The overall exposure, white balance, and focus position however should be consistent.
 */
AVF_EXPORT AVCaptureDeviceType const AVCaptureDeviceTypeBuiltInDualCamera API_AVAILABLE(ios(10.2), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

/*!
 @constant AVCaptureDeviceTypeBuiltInDualWideCamera
    A device that consists of two fixed focal length cameras, one ultra wide and one wide angle. Note that devices of this type may only be discovered using an AVCaptureDeviceDiscoverySession or -[AVCaptureDevice defaultDeviceWithDeviceType:mediaType:position:].

    A device of this device type supports the following features:
    - Auto switching from one camera to the other when zoom factor, light level, and focus position allow this.
    - Depth data delivery by measuring the disparity of matched features between the ultra wide and wide cameras.
    - Delivery of photos from constituent devices (ultra wide and wide) via a single photo capture request.

    A device of this device type does not support the following features:
    - AVCaptureExposureModeCustom and manual exposure bracketing.
    - Locking focus with a lens position other than AVCaptureLensPositionCurrent.
    - Locking auto white balance with device white balance gains other than AVCaptureWhiteBalanceGainsCurrent.

    Even when locked, exposure duration, ISO, aperture, white balance gains, or lens position may change when the device switches from one camera to the other. The overall exposure, white balance, and focus position however should be consistent.
 */
AVF_EXPORT AVCaptureDeviceType const AVCaptureDeviceTypeBuiltInDualWideCamera API_AVAILABLE(ios(13.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

/*!
 @constant AVCaptureDeviceTypeBuiltInTripleCamera
    A device that consists of three fixed focal length cameras, one ultra wide, one wide angle, and one telephoto. Note that devices of this type may only be discovered using an AVCaptureDeviceDiscoverySession or -[AVCaptureDevice defaultDeviceWithDeviceType:mediaType:position:].

    A device of this device type supports the following features:
    - Auto switching from one camera to the other when zoom factor, light level, and focus position allow this.
    - Delivery of photos from constituent devices (ultra wide, wide and telephoto cameras) via a single photo capture request.

    A device of this device type does not support the following features:
    - AVCaptureExposureModeCustom and manual exposure bracketing.
    - Locking focus with a lens position other than AVCaptureLensPositionCurrent.
    - Locking auto white balance with device white balance gains other than AVCaptureWhiteBalanceGainsCurrent.

    Even when locked, exposure duration, ISO, aperture, white balance gains, or lens position may change when the device switches from one camera to the other. The overall exposure, white balance, and focus position however should be consistent.
 */
AVF_EXPORT AVCaptureDeviceType const AVCaptureDeviceTypeBuiltInTripleCamera API_AVAILABLE(ios(13.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

/*!
 @constant AVCaptureDeviceTypeBuiltInTrueDepthCamera
    A device that consists of two cameras, one YUV and one Infrared. The infrared camera provides high quality depth information that is synchronized and perspective corrected to frames produced by the YUV camera. While the resolution of the depth data and YUV frames may differ, their field of view and aspect ratio always match. Note that devices of this type may only be discovered using an AVCaptureDeviceDiscoverySession or -[AVCaptureDevice defaultDeviceWithDeviceType:mediaType:position:].
 */
AVF_EXPORT AVCaptureDeviceType const AVCaptureDeviceTypeBuiltInTrueDepthCamera API_AVAILABLE(ios(11.1), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

/*!
 @constant AVCaptureDeviceTypeBuiltInLiDARDepthCamera
    A device that consists of two cameras, one YUV and one LiDAR. The LiDAR camera provides high quality, high accuracy depth information by measuring the round trip of an artificial light signal emitted by a laser. The depth is synchronized and perspective corrected to frames produced by the paired YUV camera. While the resolution of the depth data and YUV frames may differ, their field of view and aspect ratio always match. Note that devices of this type may only be discovered using an AVCaptureDeviceDiscoverySession or -[AVCaptureDevice defaultDeviceWithDeviceType:mediaType:position:].
 */
AVF_EXPORT AVCaptureDeviceType const AVCaptureDeviceTypeBuiltInLiDARDepthCamera API_AVAILABLE(ios(15.4), macCatalyst(15.4), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

/*!
 @constant AVCaptureDeviceTypeContinuityCamera
    A continuity camera device. These devices are suitable for general purpose use. Note that devices of this type may only be discovered using an AVCaptureDeviceDiscoverySession or -[AVCaptureDevice defaultDeviceWithDeviceType:mediaType:position:].
 
 @discussion
    Starting in macOS 14.0 and Mac Catalyst 17.0, apps may opt in for using AVCaptureDeviceTypeContinuityCamera by adding the following key to their Info.plist:
        <key>NSCameraUseContinuityCameraDeviceType</key>
        <true/>

	Otherwise, continuity cameras on macOS and Mac Catalyst report that their device type is AVCaptureDeviceTypeBuiltInWideAngleCamera.
 */
AVF_EXPORT AVCaptureDeviceType const AVCaptureDeviceTypeContinuityCamera API_AVAILABLE(macos(14.0), ios(17.0), macCatalyst(17.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @constant AVCaptureDeviceTypeDeskViewCamera
    A distortion corrected cut out from an ultra wide camera, made to approximate an overhead camera pointing at a desk. Supports multicam operation.
 */
AVF_EXPORT AVCaptureDeviceType const AVCaptureDeviceTypeDeskViewCamera API_AVAILABLE(macos(13.0)) API_UNAVAILABLE(ios, macCatalyst, tvos, visionos) API_UNAVAILABLE(watchos);

/*!
 @constant AVCaptureDeviceTypeExternalUnknown
    A deprecated synonym for AVCaptureDeviceTypeExternal. Please use AVCaptureDeviceTypeExternal instead.
 */
AVF_EXPORT AVCaptureDeviceType const AVCaptureDeviceTypeExternalUnknown API_DEPRECATED_WITH_REPLACEMENT("AVCaptureDeviceTypeExternal", macos(10.15, 14.0)) API_UNAVAILABLE(ios, macCatalyst, tvos, visionos) API_UNAVAILABLE(watchos);

/*!
 @constant AVCaptureDeviceTypeBuiltInDuoCamera
    A deprecated synonym for AVCaptureDeviceTypeBuiltInDualCamera. Please use AVCaptureDeviceTypeBuiltInDualCamera instead.
 */
AVF_EXPORT AVCaptureDeviceType const AVCaptureDeviceTypeBuiltInDuoCamera API_DEPRECATED("Use AVCaptureDeviceTypeBuiltInDualCamera instead.", ios(10.0, 10.2)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(tvos, watchos);

/*!
 @constant AVCaptureDeviceTypeBuiltInMicrophone
    A deprecated synonym for AVCaptureDeviceTypeMicrophone. Please use AVCaptureDeviceTypeMicrophone instead.
 */
AVF_EXPORT AVCaptureDeviceType const AVCaptureDeviceTypeBuiltInMicrophone API_DEPRECATED_WITH_REPLACEMENT("AVCaptureDeviceTypeMicrophone", macos(10.15, 14.0), ios(10.0, 17.0), macCatalyst(14.0, 17.0)) API_UNAVAILABLE(tvos, visionos) API_UNAVAILABLE(watchos);


API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDevice (AVCaptureDeviceType)

/*!
 @property deviceType
 @abstract
    The type of the capture device.
 
 @discussion
    A capture device's type never changes.
 */
@property(nonatomic, readonly) AVCaptureDeviceType deviceType API_AVAILABLE(macos(10.15), ios(10.0), macCatalyst(14.0), tvos(17.0), visionos(2.1));

@end


API_AVAILABLE(macos(10.15), ios(10.0), macCatalyst(14.0), tvos(17.0), visionos(2.1)) API_UNAVAILABLE(watchos)
@interface AVCaptureDevice (AVCaptureDefaultDevice)

/*!
 @method defaultDeviceWithDeviceType:mediaType:position:
 @abstract
    Returns an AVCaptureDevice instance for the default device of the given device type, media type, and position.
 
 @param deviceType
    The device type supported by the returned device. It must be a valid AVCaptureDeviceType.
 @param mediaType
    The media type, such as AVMediaTypeVideo, AVMediaTypeAudio, or AVMediaTypeMuxed, supported by the returned device. Pass nil to consider devices with any media type.
 @param position
    The position supported by the returned device. Pass AVCaptureDevicePositionUnspecified to consider devices with any position.
 @result
    The default device with the given device type, media type and position or nil if no device with that media type exists and nil otherwise.
 
 @discussion
    This method returns the default device of the given combination of device type, media type, and position currently available on the system.
 */
+ (nullable AVCaptureDevice *)defaultDeviceWithDeviceType:(AVCaptureDeviceType)deviceType mediaType:(nullable AVMediaType)mediaType position:(AVCaptureDevicePosition)position API_AVAILABLE(macos(10.15), ios(10.0), macCatalyst(14.0), tvos(17.0), visionos(2.1));

@end


API_AVAILABLE(macos(13.0), ios(17.0), macCatalyst(16.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDevice (AVCaptureDevicePreferredCamera)

/*!
 @property userPreferredCamera
 @abstract
    Settable property that specifies a user preferred camera.
 
 @discussion
    Setting this property allows an application to persist its user’s preferred camera across app launches and reboots. The property internally maintains a short history, so if your user’s most recent preferred camera is not currently connected, it still reports the next best choice. This property always returns a device that is present. If no camera is available nil is returned. Setting the property to nil has no effect.
*/
@property(class, readwrite, nullable) AVCaptureDevice *userPreferredCamera API_AVAILABLE(macos(13.0), ios(17.0), macCatalyst(16.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @property systemPreferredCamera
 @abstract
    Specifies the best camera to use as determined by the system.
 
 @discussion
    Apple chooses the default value. This property incorporates userPreferredCamera as well as other factors, such as camera suspension and Apple cameras appearing that should be automatically chosen. The property may change spontaneously, such as when the preferred camera goes away. This property always returns a device that is present. If no camera is available nil is returned.

    Applications that adopt this API should always key-value observe this property and update their AVCaptureSession’s input device to reflect changes to the systemPreferredCamera. The application can still offer users the ability to pick a camera by setting userPreferredCamera, which will cause the systemPreferredCamera API to put the user’s choice first until either another Apple-preferred device becomes available or the machine is rebooted (after which it reverts to its original behavior of returning the internally determined best camera to use).

    If the application wishes to offer users a fully manual camera selection mode in addition to automatic camera selection, it is recommended to call setUserPreferredCamera: each time the user makes a camera selection, but ignore key-value observer updates to systemPreferredCamera while in manual selection mode.
*/
@property(class, readonly, nullable) AVCaptureDevice *systemPreferredCamera API_AVAILABLE(macos(13.0), ios(17.0), macCatalyst(16.0), tvos(17.0), visionos(1.0)) API_UNAVAILABLE(watchos);

@end


API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDevice (AVCaptureDeviceSystemPressure)

/*!
 @property systemPressureState
 @abstract
    A key-value observable property indicating the capture device's current system pressure state.
 
 @discussion
    This property indicates whether the capture device is currently subject to an elevated system pressure condition. When system pressure reaches AVCaptureSystemPressureLevelShutdown, the capture device cannot continue to provide input, so the AVCaptureSession becomes interrupted until the pressured state abates. System pressure can be effectively mitigated by lowering the device's activeVideoMinFrameDuration in response to changes in the systemPressureState. Clients are encouraged to implement frame rate throttling to bring system pressure down if their capture use case can tolerate a reduced frame rate.
 */
@property(nonatomic, readonly) AVCaptureSystemPressureState *systemPressureState API_AVAILABLE(ios(11.1), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

@end

/*!
 @enum AVCapturePrimaryConstituentDeviceSwitchingBehavior
 @abstract
    These constants can be used to control when the virtual device is allowed to switch the active primary constituent device.
 
 @constant AVCapturePrimaryConstituentDeviceSwitchingBehaviorUnsupported
    Indicates that the device does not support constituent device switching. This is reported for cameras that do not have more than one constituent device.
 @constant AVCapturePrimaryConstituentDeviceSwitchingBehaviorAuto
    Automatically select the best camera for the current scene. In this mode there are no restrictions on when a camera switch can occur.
 @constant AVCapturePrimaryConstituentDeviceSwitchingBehaviorRestricted
    Restrict fallback camera selection to certain conditions (see AVCapturePrimaryConstituentDeviceRestrictedSwitchingBehaviorConditions). Camera switches necessary to satisfy the requested video zoom factor are still allowed without restriction.
 @constant AVCapturePrimaryConstituentDeviceSwitchingBehaviorLocked
    Lock camera switching to the active primary constituent device. Note that this restricts the minAvailableVideoZoomFactor to the switch-over zoom factor of the activePrimaryConstituentDevice (as reported in AVCaptureDevice.virtualDeviceSwitchOverVideoZoomFactors).
 
 @discussion
    Virtual devices with multiple constituent video devices (such as the Dual Camera, Dual Wide Camera, or Triple Camera), consist of cameras that each have different properties such as focal length, maximum light sensitivity, and minimum focus distance. One of the constituent video devices is selected as the primary constituent device. For an AVCaptureSession, the primary constituent device produces for all outputs. For an AVCaptureMultiCamSession, the primary constituent device produces for all outputs connected to the virtual device's native AVCaptureDeviceInputPort (where its sourceDeviceType is equal to the virtual device's deviceType).

    When the requested zoom factor can be achieved by multiple constituent cameras (see -virtualDeviceSwitchOverVideoZoomFactors), the virtual device chooses the best camera for the scene. The primary condition for this is the focal length; the camera with the longest focal length requires the least amount of digital upscaling and therefore normally provides the highest image quality. Secondary conditions are focus and exposure; when the scene requires focus or exposure to go beyond the limits of the active primary constituent device, a camera with a shorter focal length may be able to deliver a better quality image. Such a device is called a fallback primary constituent device. For example, a telephoto camera with a minimum focus distance of 40cm is not able to deliver a sharp image when the subject in the scene is closer than 40cm. For such a scene, the virtual device will switch to the wide-angle camera which typically has a smaller minimum focus distance and is able to achieve accurate focus on the subject. In this case the wide-angle camera is the fallback primary constitute device.
 */
typedef NS_ENUM(NSInteger, AVCapturePrimaryConstituentDeviceSwitchingBehavior) {
    AVCapturePrimaryConstituentDeviceSwitchingBehaviorUnsupported  = 0,
    AVCapturePrimaryConstituentDeviceSwitchingBehaviorAuto         = 1,
    AVCapturePrimaryConstituentDeviceSwitchingBehaviorRestricted   = 2,
    AVCapturePrimaryConstituentDeviceSwitchingBehaviorLocked       = 3,
} NS_SWIFT_NAME(AVCaptureDevice.PrimaryConstituentDeviceSwitchingBehavior) API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @enum AVCapturePrimaryConstituentDeviceRestrictedSwitchingBehaviorConditions
 @abstract
    These constants can be used and combined to control the conditions that allow fallback camera selection when the primaryConstituentDeviceSelectionBehavior is set to AVCapturePrimaryConstituentDeviceSwitchingBehaviorRestricted. Note that camera switching necessary to satisfy the requested zoom factor is still allowed.
 
 @constant AVCapturePrimaryConstituentDeviceRestrictedSwitchingBehaviorConditionNone
    Disallow fallback switching.
 @constant AVCapturePrimaryConstituentDeviceRestrictedSwitchingBehaviorConditionVideoZoomChanged
    Restrict fallback camera switching to when the video zoom factor changes, either through AVCaptureDevice.videoZoomFactor or -[AVCaptureDevice rampToVideoZoomFactor:withRate:]. Note that any change in video zoom factor will allow a switch to a fallback camera, not just changes across switch-over zoom factors.
 @constant AVCapturePrimaryConstituentDeviceRestrictedSwitchingBehaviorConditionFocusModeChanged
    Restrict fallback camera switches to when AVCaptureDevice.focusMode is set.
 @constant AVCapturePrimaryConstituentDeviceRestrictedSwitchingBehaviorConditionExposureModeChanged
    Restrict fallback camera switches to when AVCaptureDevice.exposureMode is set.
 
 @discussion
    Whenever triggered by one or more of the enabled conditions, the fallback camera switching waits for exposure and focus to stabilize before deciding which camera to use as the primary constituent device.
 
    Whenever AVCapturePrimaryConstituentDeviceRestrictedSwitchingBehaviorConditionVideoZoomChanged is not included in the restricted switching behavior conditions, AVCapturePrimaryConstituentDeviceSwitchingBehaviorRestricted still allows camera selection when a change in video zoom factor makes a camera eligible or ineligible to be selected as the activePrimaryConstituentDevice. When the video zoom factor decreases to below the switch-over zoom factor of the activePrimaryConstituentDevice, a different camera will be selected to satisfy the requested zoom factor. When the video zoom factor increases and crosses a camera's switch-over zoom factor, this camera becomes eligible to be selected as the activePrimaryConstituentDevice. If exposure and focus allow, this camera then becomes the new activePrimaryConstituentDevice. Similar to the AVCapturePrimaryConstituentDeviceRestrictedSwitchingBehaviorConditionVideoZoomChanged this also waits for exposure and focus to stabilize. Otherwise the activePrimaryConstituentDevice remains unchanged.
 */
typedef NS_OPTIONS(NSUInteger, AVCapturePrimaryConstituentDeviceRestrictedSwitchingBehaviorConditions) {
    AVCapturePrimaryConstituentDeviceRestrictedSwitchingBehaviorConditionNone                = 0,
    AVCapturePrimaryConstituentDeviceRestrictedSwitchingBehaviorConditionVideoZoomChanged    = 1 << 0,
    AVCapturePrimaryConstituentDeviceRestrictedSwitchingBehaviorConditionFocusModeChanged    = 1 << 1,
    AVCapturePrimaryConstituentDeviceRestrictedSwitchingBehaviorConditionExposureModeChanged = 1 << 2,
} NS_SWIFT_NAME(AVCaptureDevice.PrimaryConstituentDeviceRestrictedSwitchingBehaviorConditions) API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDevice (AVCaptureDeviceVirtual)

/*!
 @property virtualDevice
 @abstract
    A property indicating whether the receiver is a virtual device consisting of constituent physical devices.
 
 @discussion
    Two examples of virtual devices are:
        The Dual Camera, which supports seamlessly switching between a wide and telephoto camera while zooming and generating depth data from the disparities between the different points of view of the physical cameras.
        The TrueDepth Camera, which generates depth data from disparities between a YUV camera and an Infrared camera pointed in the same direction.
 */
@property(nonatomic, readonly, getter=isVirtualDevice) BOOL virtualDevice API_AVAILABLE(ios(13.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

/*!
 @property constituentDevices
 @abstract
    An array of constituent physical devices comprising a virtual device.
 
 @discussion
    When called on a device for which virtualDevice == NO, an empty array is returned.
 */
@property(nonatomic, readonly) NSArray<AVCaptureDevice *> *constituentDevices API_AVAILABLE(ios(13.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

/*!
 @property virtualDeviceSwitchOverVideoZoomFactors
 @abstract
    An array of video zoom factors at or above which a virtual device (such as the Dual Camera) may switch to its next constituent device.
 
 @discussion
    This array contains zoom factors at which one of the constituent device's field of view matches the next constituent device's full field of view. The number of switch over video zoom factors is always one less than the count of the constituentDevices property, and the factors progress in the same order as the devices listed in that property. On non-virtual devices this property returns an empty array.
 */
@property(nonatomic, readonly) NSArray<NSNumber *> *virtualDeviceSwitchOverVideoZoomFactors API_AVAILABLE(ios(13.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

/*!
 @method setPrimaryConstituentDeviceSwitchingBehavior:restrictedSwitchingBehaviorConditions:
 @abstract
    The switching behavior and conditions, unless overwritten via -[AVCaptureMovieFileOutput setPrimaryConstituentDeviceSwitchingBehavior:restrictedSwitchingBehaviorConditions].
 @param switchingBehavior
    The desired switching behavior.
 @param restrictedSwitchingBehaviorConditions
    The desired conditions for restricting camera switching. This must be set to AVCapturePrimaryConstituentDeviceRestrictedSwitchingBehaviorConditionNone whenever switchingBehavior is not equal to AVCapturePrimaryConstituentDeviceSwitchingBehaviorRestricted.
 
 @discussion
    The switching behavior may be overridden on the AVCaptureMovieFileOutput while recording (see -[AVCaptureMovieFileOutput setPrimaryConstituentDeviceSwitchingBehavior:restrictedSwitchingBehaviorConditions]). This method throws an NSInvalidArgumentException if constituent device switching is not supported by the receiver or if restrictedSwitchingBehaviorConditions is not equal to AVCapturePrimaryConstituentDeviceRestrictedSwitchingBehaviorConditionNone and switchingBehavior is not equal to AVCapturePrimaryConstituentDeviceSwitchingBehaviorRestricted.
 */
- (void)setPrimaryConstituentDeviceSwitchingBehavior:(AVCapturePrimaryConstituentDeviceSwitchingBehavior)switchingBehavior restrictedSwitchingBehaviorConditions:(AVCapturePrimaryConstituentDeviceRestrictedSwitchingBehaviorConditions)restrictedSwitchingBehaviorConditions API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @property primaryConstituentDeviceSwitchingBehavior
 @abstract
    The primaryConstituentDeviceSwitchingBehavior as set by -[AVCaptureDevice setPrimaryConstituentDeviceSwitchingBehavior:restrictedSwitchingBehaviorConditions:].
 
 @discussion
    By default, this property is set to AVCapturePrimaryConstituentDeviceSwitchingBehaviorAuto for AVCaptureDevices that support it.  This property is key-value observable.
 */
@property(nonatomic, readonly) AVCapturePrimaryConstituentDeviceSwitchingBehavior primaryConstituentDeviceSwitchingBehavior API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @property primaryConstituentDeviceRestrictedSwitchingBehaviorConditions
 @abstract
    The primaryConstituentDeviceRestrictedSwitchingBehaviorConditions as set by -[AVCaptureDevice setPrimaryConstituentDeviceSwitchingBehavior:restrictedSwitchingBehaviorConditions:].
 
 @discussion
    By default, this propety is set to AVCapturePrimaryConstituentDeviceRestrictedSwitchingBehaviorConditionNone. This property is key-value observable.
 */
@property(nonatomic, readonly) AVCapturePrimaryConstituentDeviceRestrictedSwitchingBehaviorConditions primaryConstituentDeviceRestrictedSwitchingBehaviorConditions API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @property activePrimaryConstituentDeviceSwitchingBehavior
 @abstract
    The active constituent device switching behavior.
 
 @discussion
    For virtual devices with multiple constituent devices, this property returns the active switching behavior. This is equal to primaryConstituentDeviceSwitchingBehavior except while recording using an AVCaptureMovieFileOutput configured with a different switching behavior (see -[AVCaptureMovieFileOutput setPrimaryConstituentDeviceSwitchingBehavior:restrictedSwitchingBehaviorConditions]). Devices that do not support constituent device switching return AVCapturePrimaryConstituentDeviceSwitchingBehaviorUnsupported. This property is key-value observable.
 */
@property(nonatomic, readonly) AVCapturePrimaryConstituentDeviceSwitchingBehavior activePrimaryConstituentDeviceSwitchingBehavior API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @property activePrimaryConstituentDeviceRestrictedSwitchingBehaviorConditions
 @abstract
    The active constituent device restricted  switching behavior.
 
 @discussion
    For virtual devices with multiple constituent devices, this property returns the active restricted switching behavior conditions. This is equal to primaryConstituentDeviceRestrictedSwitchingBehaviorConditions except while recording using an AVCaptureMovieFileOutput configured with different restricted switching behavior conditions (see -[AVCaptureMovieFileOutput setPrimaryConstituentDeviceSwitchingBehaviorForRecording:restrictedSwitchingBehaviorConditions]). Devices that do not support constituent device switching return AVCapturePrimaryConstituentDeviceRestrictedSwitchingBehaviorConditionNone. This property is key-value observable.
 */
@property(nonatomic, readonly) AVCapturePrimaryConstituentDeviceRestrictedSwitchingBehaviorConditions activePrimaryConstituentDeviceRestrictedSwitchingBehaviorConditions API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @property activePrimaryConstituentDevice
 @abstract
    For virtual devices, this property indicates which constituent device is currently the primary constituent device. The primary constituent device may change when zoom, exposure, or focus changes.
 
 @discussion
    This property returns nil for non-virtual devices. On virtual devices this property returns nil until the device is used in a running AVCaptureSession. This property is key-value observable.
 */
@property(nonatomic, readonly, nullable) AVCaptureDevice *activePrimaryConstituentDevice API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @property supportedFallbackPrimaryConstituentDevices
 @abstract
    The constituent devices that may be selected as a fallback for a longer focal length primary constituent device.
 
 @discussion
    This property returns an empty array for non-virtual devices. This property never changes for a given virtual device.
 */
@property(nonatomic, readonly) NSArray<AVCaptureDevice *> *supportedFallbackPrimaryConstituentDevices API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @property fallbackPrimaryConstituentDevices
 @abstract
    The constituent devices that may be used as a fallback device when a constituent device with a longer focal length becomes limited by its light sensitivity or minimum focus distance.
 
 @discussion
    This may only be set to the supportedFallbackPrimaryConstituentDevices or a subset thereof. By default this is set to all supportedFallbackPrimaryConstituentDevices. This property will throw an NSInvalidArgumentException if the array includes any device not reported in supportedFallbackPrimaryConstituentDevices. This property is key-value observable.
 */
@property(nonatomic) NSArray<AVCaptureDevice *> *fallbackPrimaryConstituentDevices API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

@end


/*!
 @enum AVCaptureFlashMode
 @abstract
    Constants indicating the mode of the flash on the receiver's device, if it has one.
 
 @constant AVCaptureFlashModeOff
    Indicates that the flash should always be off.
 @constant AVCaptureFlashModeOn
    Indicates that the flash should always be on.
 @constant AVCaptureFlashModeAuto
    Indicates that the flash should be used automatically depending on ambient light conditions.
 */
typedef NS_ENUM(NSInteger, AVCaptureFlashMode) {
    AVCaptureFlashModeOff  = 0,
    AVCaptureFlashModeOn   = 1,
    AVCaptureFlashModeAuto = 2,
} API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);


API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDevice (AVCaptureDeviceFlash)

/*!
 @property hasFlash
 @abstract
    Indicates whether the receiver has a flash.
 
 @discussion
    The value of this property is a BOOL indicating whether the receiver has a flash. The receiver's flashMode property can only be set when this property returns YES.
 */
@property(nonatomic, readonly) BOOL hasFlash;

/*!
 @property flashAvailable
 @abstract
    Indicates whether the receiver's flash is currently available for use.
 
 @discussion
    The value of this property is a BOOL indicating whether the receiver's flash is currently available. The flash may become unavailable if, for example, the device overheats and needs to cool off. This property is key-value observable.
 */
@property(nonatomic, readonly, getter=isFlashAvailable) BOOL flashAvailable API_AVAILABLE(macos(10.15), ios(5.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos);

/*!
 @property flashActive
 @abstract
    Indicates whether the receiver's flash is currently active.
 
 @discussion
    The value of this property is a BOOL indicating whether the receiver's flash is currently active. When the flash is active, it will flash if a still image is captured. When a still image is captured with the flash active, exposure and white balance settings are overridden for the still. This is true even when using AVCaptureExposureModeCustom and/or AVCaptureWhiteBalanceModeLocked. This property is key-value observable.
 */
@property(nonatomic, readonly, getter=isFlashActive) BOOL flashActive API_DEPRECATED("Use AVCapturePhotoOutput's -isFlashScene instead.", ios(5.0, 10.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(tvos);

/*!
 @method isFlashModeSupported:
 @abstract
    Returns whether the receiver supports the given flash mode.
 
 @param flashMode
    An AVCaptureFlashMode to be checked.
 @result
    YES if the receiver supports the given flash mode, NO otherwise.
 
 @discussion
    The receiver's flashMode property can only be set to a certain mode if this method returns YES for that mode.
 */
- (BOOL)isFlashModeSupported:(AVCaptureFlashMode)flashMode API_DEPRECATED("Use AVCapturePhotoOutput's -supportedFlashModes instead.", ios(4.0, 10.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(tvos);

/*!
 @property flashMode
 @abstract
    Indicates current mode of the receiver's flash, if it has one.
 
 @discussion
    The value of this property is an AVCaptureFlashMode that determines the mode of the receiver's flash, if it has one. -setFlashMode: throws an NSInvalidArgumentException if set to an unsupported value (see -isFlashModeSupported:). -setFlashMode: throws an NSGenericException if called without first obtaining exclusive access to the receiver using lockForConfiguration:. Clients can observe automatic changes to the receiver's flashMode by key value observing this property.
 
    When using AVCapturePhotoOutput, AVCaptureDevice's flashMode property is ignored. You specify flashMode on a per photo basis by setting the AVCapturePhotoSettings.flashMode property.
 */
@property(nonatomic) AVCaptureFlashMode flashMode API_DEPRECATED("Use AVCapturePhotoSettings.flashMode instead.", ios(4.0, 10.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(tvos);

@end


/*!
 @enum AVCaptureTorchMode
 @abstract
    Constants indicating the mode of the torch on the receiver's device, if it has one.
 
 @constant AVCaptureTorchModeOff
    Indicates that the torch should always be off.
 @constant AVCaptureTorchModeOn
    Indicates that the torch should always be on.
 @constant AVCaptureTorchModeAuto
    Indicates that the torch should be used automatically depending on ambient light conditions.
 */
typedef NS_ENUM(NSInteger, AVCaptureTorchMode) {
    AVCaptureTorchModeOff  = 0,
    AVCaptureTorchModeOn   = 1,
    AVCaptureTorchModeAuto = 2,
} API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);


/*!
 @constant AVCaptureMaxAvailableTorchLevel
    A special value that may be passed to -setTorchModeWithLevel:error: to set the torch to the maximum level currently available. Under thermal duress, the maximum available torch level may be less than 1.0.
 */
AVF_EXPORT const float AVCaptureMaxAvailableTorchLevel API_AVAILABLE(macos(10.15), ios(6.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);


API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDevice (AVCaptureDeviceTorch)

/*!
 @property hasTorch
 @abstract
    Indicates whether the receiver has a torch.
 
 @discussion
    The value of this property is a BOOL indicating whether the receiver has a torch. The receiver's torchMode property can only be set when this property returns YES.
 */
@property(nonatomic, readonly) BOOL hasTorch;

/*!
 @property torchAvailable
 @abstract
    Indicates whether the receiver's torch is currently available for use.
 
 @discussion
    The value of this property is a BOOL indicating whether the receiver's torch is currently available. The torch may become unavailable if, for example, the device overheats and needs to cool off. This property is key-value observable.
 */
@property(nonatomic, readonly, getter=isTorchAvailable) BOOL torchAvailable API_AVAILABLE(macos(10.15), ios(5.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos);

/*!
 @property torchActive
 @abstract
    Indicates whether the receiver's torch is currently active.
 
 @discussion
    The value of this property is a BOOL indicating whether the receiver's torch is currently active. If the current torchMode is AVCaptureTorchModeAuto and isTorchActive is YES, the torch will illuminate once a recording starts (see AVCaptureOutput.h -startRecordingToOutputFileURL:recordingDelegate:). This property is key-value observable.
 */
@property(nonatomic, readonly, getter=isTorchActive) BOOL torchActive API_AVAILABLE(macos(10.15), ios(6.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos);

/*!
 @property torchLevel
 @abstract
    Indicates the receiver's current torch brightness level as a floating point value.
 
 @discussion
    The value of this property is a float indicating the receiver's torch level from 0.0 (off) -> 1.0 (full). This property is key-value observable.
 */
@property(nonatomic, readonly) float torchLevel API_AVAILABLE(macos(10.15), ios(5.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos);

/*!
 @method isTorchModeSupported:
 @abstract
    Returns whether the receiver supports the given torch mode.
 
 @param torchMode
    An AVCaptureTorchMode to be checked.
 @result
    YES if the receiver supports the given torch mode, NO otherwise.
 
 @discussion
    The receiver's torchMode property can only be set to a certain mode if this method returns YES for that mode.
 */
- (BOOL)isTorchModeSupported:(AVCaptureTorchMode)torchMode;

/*!
 @property torchMode
 @abstract
    Indicates current mode of the receiver's torch, if it has one.
 
 @discussion
    The value of this property is an AVCaptureTorchMode that determines the mode of the receiver's torch, if it has one. -setTorchMode: throws an NSInvalidArgumentException if set to an unsupported value (see -isTorchModeSupported:). -setTorchMode: throws an NSGenericException if called without first obtaining exclusive access to the receiver using lockForConfiguration:. Clients can observe automatic changes to the receiver's torchMode by key value observing this property.
 */
@property(nonatomic) AVCaptureTorchMode torchMode;

/*!
 @method setTorchModeOnWithLevel:error:
 @abstract
    Sets the current mode of the receiver's torch to AVCaptureTorchModeOn at the specified level.
 
 @discussion
    This method sets the torch mode to AVCaptureTorchModeOn at a specified level. torchLevel must be a value between 0 and 1, or the special value AVCaptureMaxAvailableTorchLevel. The specified value may not be available if the iOS device is too hot. This method throws an NSInvalidArgumentException if set to an unsupported level. If the specified level is valid, but unavailable, the method returns NO with AVErrorTorchLevelUnavailable. -setTorchModeOnWithLevel:error: throws an NSGenericException if called without first obtaining exclusive access to the receiver using lockForConfiguration:. Clients can observe automatic changes to the receiver's torchMode by key value observing the torchMode property.
 */
- (BOOL)setTorchModeOnWithLevel:(float)torchLevel error:(NSError * _Nullable * _Nullable)outError API_AVAILABLE(macos(10.15), ios(6.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos);

@end


/*!
 @enum AVCaptureFocusMode
 @abstract
    Constants indicating the mode of the focus on the receiver's device, if it has one.
 
 @constant AVCaptureFocusModeLocked
    Indicates that the focus should be locked at the lens' current position.
 @constant AVCaptureFocusModeAutoFocus
    Indicates that the device should autofocus once and then change the focus mode to AVCaptureFocusModeLocked.
 @constant AVCaptureFocusModeContinuousAutoFocus
    Indicates that the device should automatically focus when needed.
 */
typedef NS_ENUM(NSInteger, AVCaptureFocusMode) {
    AVCaptureFocusModeLocked              = 0,
    AVCaptureFocusModeAutoFocus           = 1,
    AVCaptureFocusModeContinuousAutoFocus = 2,
} API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);


/*!
 @enum AVCaptureAutoFocusRangeRestriction
 @abstract
    Constants indicating the restriction of the receiver's autofocus system to a particular range of focus scan, if it supports range restrictions.
 
 @constant AVCaptureAutoFocusRangeRestrictionNone
    Indicates that the autofocus system should not restrict the focus range.
 @constant AVCaptureAutoFocusRangeRestrictionNear
    Indicates that the autofocus system should restrict the focus range for subject matter that is near to the camera.
 @constant AVCaptureAutoFocusRangeRestrictionFar
    Indicates that the autofocus system should restrict the focus range for subject matter that is far from the camera.
 */
typedef NS_ENUM(NSInteger, AVCaptureAutoFocusRangeRestriction) {
    AVCaptureAutoFocusRangeRestrictionNone = 0,
    AVCaptureAutoFocusRangeRestrictionNear = 1,
    AVCaptureAutoFocusRangeRestrictionFar  = 2,
} API_AVAILABLE(ios(7.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);


API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDevice (AVCaptureDeviceFocus)

/*!
 @method isFocusModeSupported:
 @abstract
    Returns whether the receiver supports the given focus mode.
 
 @param focusMode
    An AVCaptureFocusMode to be checked.
 @result
    YES if the receiver supports the given focus mode, NO otherwise.
 
 @discussion
    The receiver's focusMode property can only be set to a certain mode if this method returns YES for that mode.
 */
- (BOOL)isFocusModeSupported:(AVCaptureFocusMode)focusMode;

/*!
 @property lockingFocusWithCustomLensPositionSupported
 @abstract
    Indicates whether the receiver supports a lens position other than AVCaptureLensPositionCurrent.
 
 @discussion
    If lockingFocusWithCustomLensPositionSupported returns NO, setFocusModeLockedWithLensPosition: may only be called with AVCaptureLensPositionCurrent. Passing any other lens position will result in an exception.
 */
@property(nonatomic, readonly, getter=isLockingFocusWithCustomLensPositionSupported) BOOL lockingFocusWithCustomLensPositionSupported API_AVAILABLE(ios(10.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @property focusMode
 @abstract
    Indicates current focus mode of the receiver, if it has one.
 
 @discussion
    The value of this property is an AVCaptureFocusMode that determines the receiver's focus mode, if it has one. -setFocusMode: throws an NSInvalidArgumentException if set to an unsupported value (see -isFocusModeSupported:). -setFocusMode: throws an NSGenericException if called without first obtaining exclusive access to the receiver using lockForConfiguration:. Clients can observe automatic changes to the receiver's focusMode by key value observing this property.
 */
@property(nonatomic) AVCaptureFocusMode focusMode;

/*!
 @property focusPointOfInterestSupported
 @abstract
    Indicates whether the receiver supports focus points of interest.
 
 @discussion
    The receiver's focusPointOfInterest property can only be set if this property returns YES.
 */
@property(nonatomic, readonly, getter=isFocusPointOfInterestSupported) BOOL focusPointOfInterestSupported;

/*!
 @property focusPointOfInterest
 @abstract
    Indicates current focus point of interest of the receiver, if it has one.
 
 @discussion
    The value of this property is a CGPoint that determines the receiver's focus point of interest, if it has one. A value of (0,0) indicates that the camera should focus on the top left corner of the image, while a value of (1,1) indicates that it should focus on the bottom right. The default value is (0.5,0.5). -setFocusPointOfInterest: throws an NSInvalidArgumentException if isFocusPointOfInterestSupported returns NO. -setFocusPointOfInterest: throws an NSGenericException if called without first obtaining exclusive access to the receiver using lockForConfiguration:. Clients can observe automatic changes to the receiver's focusPointOfInterest by key value observing this property. Note that setting focusPointOfInterest alone does not initiate a focus operation. After setting focusPointOfInterest, call -setFocusMode: to apply the new point of interest.
 */
@property(nonatomic) CGPoint focusPointOfInterest;

/// Whether the receiver supports focus rectangles of interest.
///
/// You may only set the device's ``focusRectOfInterest`` property if this property returns `true`.
@property(nonatomic, readonly, getter=isFocusRectOfInterestSupported) BOOL focusRectOfInterestSupported API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// The minimum size you may use when specifying a rectangle of interest.
///
/// The size returned is in normalized coordinates, and depends on the current ``AVCaptureDevice/activeFormat``. If ``focusRectOfInterestSupported`` returns `false`, this property returns { 0, 0 }.
@property(nonatomic, readonly) CGSize minFocusRectOfInterestSize API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// The device's current focus rectangle of interest, if it has one.
///
/// The value of this property is a ``CGRect`` determining the device's focus rectangle of interest. Use this as an alternative to setting ``focusPointOfInterest``, as it allows you to specify both a location and size. For example, a value of `CGRectMake(0, 0, 1, 1)` tells the device to use the entire field of view when determining the focus, while `CGRectMake(0, 0, 0.25, 0.25)` indicates the top left sixteenth, and `CGRectMake(0.75, 0.75, 0.25, 0.25)` indicates the bottom right sixteenth. Setting ``focusRectOfInterest`` throws an `NSInvalidArgumentException` if ``focusRectOfInterestSupported`` returns `false`. Setting ``focusRectOfInterest`` throws an `NSInvalidArgumentException` if your provided rectangle's size is smaller than the ``minFocusRectOfInterestSize``. Setting ``focusRectOfInterest`` throws an `NSGenericException` if you call it without first obtaining exclusive access to the device using ``AVCaptureDevice/lockForConfiguration:``. Setting ``focusRectOfInterest`` updates the device's ``focusPointOfInterest`` to the center of your provided rectangle of interest. If you later set the device's ``focusPointOfInterest``, the ``focusRectOfInterest`` resets to the default sized rectangle of interest for the new focus point of interest. If you change your ``AVCaptureDevice/activeFormat``, the point of interest and rectangle of interest both revert to their default values. You can observe automatic changes to the device's ``focusRectOfInterest`` by key-value observing this property.
///
/// - Note: Setting ``focusRectOfInterest`` alone does not initiate a focus operation. After setting ``focusRectOfInterest``, set ``focusMode`` to apply the new rectangle of interest.
@property(nonatomic) CGRect focusRectOfInterest API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// The default rectangle of interest used for a given focus point of interest.
///
/// - Parameter pointOfInterest: The point of interest for which you want the default rectangle of interest.
///
/// For example, pass `(0.5, 0.5)` to get the focus rectangle of interest used for the default focus point of interest at `(0.5, 0.5)`.
///
/// - Note: The particular default rectangle returned depends on the current focus mode.
///
/// This method returns `CGRectNull` if ``focusRectOfInterestSupported`` returns `false`.
- (CGRect)defaultRectForFocusPointOfInterest:(CGPoint)pointOfInterest API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @property adjustingFocus
 @abstract
    Indicates whether the receiver is currently performing a focus scan to adjust focus.
 
 @discussion
    The value of this property is a BOOL indicating whether the receiver's camera focus is being automatically adjusted by means of a focus scan, because its focus mode is AVCaptureFocusModeAutoFocus or AVCaptureFocusModeContinuousAutoFocus. Clients can observe the value of this property to determine whether the camera's focus is stable.
 @seealso lensPosition
 @seealso AVCaptureAutoFocusSystem
 */
@property(nonatomic, readonly, getter=isAdjustingFocus) BOOL adjustingFocus;

/*!
 @property autoFocusRangeRestrictionSupported
 @abstract
    Indicates whether the receiver supports autofocus range restrictions.
 
 @discussion
    The receiver's autoFocusRangeRestriction property can only be set if this property returns YES.
 */
@property(nonatomic, readonly, getter=isAutoFocusRangeRestrictionSupported) BOOL autoFocusRangeRestrictionSupported API_AVAILABLE(ios(7.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @property autoFocusRangeRestriction
 @abstract
    Indicates current restriction of the receiver's autofocus system to a particular range of focus scan, if it supports range restrictions.
 
 @discussion
    The value of this property is an AVCaptureAutoFocusRangeRestriction indicating how the autofocus system should limit its focus scan. The default value is AVCaptureAutoFocusRangeRestrictionNone. -setAutoFocusRangeRestriction: throws an NSInvalidArgumentException if isAutoFocusRangeRestrictionSupported returns NO. -setAutoFocusRangeRestriction: throws an NSGenericException if called without first obtaining exclusive access to the receiver using lockForConfiguration:. This property only has an effect when the focusMode property is set to AVCaptureFocusModeAutoFocus or AVCaptureFocusModeContinuousAutoFocus. Note that setting autoFocusRangeRestriction alone does not initiate a focus operation. After setting autoFocusRangeRestriction, call -setFocusMode: to apply the new restriction.
 */
@property(nonatomic) AVCaptureAutoFocusRangeRestriction autoFocusRangeRestriction API_AVAILABLE(ios(7.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @property smoothAutoFocusSupported
 @abstract
    Indicates whether the receiver supports smooth autofocus.
 
 @discussion
    The receiver's smoothAutoFocusEnabled property can only be set if this property returns YES.
 */
@property(nonatomic, readonly, getter=isSmoothAutoFocusSupported) BOOL smoothAutoFocusSupported API_AVAILABLE(ios(7.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @property smoothAutoFocusEnabled
 @abstract
    Indicates whether the receiver should use smooth autofocus.
 
 @discussion
    On a receiver where -isSmoothAutoFocusSupported returns YES and smoothAutoFocusEnabled is set to YES, a smooth autofocus will be engaged when the focus mode is set to AVCaptureFocusModeAutoFocus or AVCaptureFocusModeContinuousAutoFocus. Enabling smooth autofocus is appropriate for movie recording. Smooth autofocus is slower and less visually invasive. Disabling smooth autofocus is more appropriate for video processing where a fast autofocus is necessary. The default value is NO. Setting this property throws an NSInvalidArgumentException if -isSmoothAutoFocusSupported returns NO. The receiver must be locked for configuration using lockForConfiguration: before clients can set this method, otherwise an NSGenericException is thrown. Note that setting smoothAutoFocusEnabled alone does not initiate a focus operation. After setting smoothAutoFocusEnabled, call -setFocusMode: to apply the new smooth autofocus mode.
 */
@property(nonatomic, getter=isSmoothAutoFocusEnabled) BOOL smoothAutoFocusEnabled API_AVAILABLE(ios(7.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @property automaticallyAdjustsFaceDrivenAutoFocusEnabled
 @abstract
    Indicates whether the receiver should automatically adjust face-driven autofocus.
 
 @discussion
    The value of this property is a BOOL that determines the receiver's automatic adjustment of face-driven autofocus. Default is YES on all platforms, if the receiver supports autofocus. This property must be set to NO before manually setting faceDrivenAutoFocusEnabled to YES/NO. -setAutomaticallyAdjustsFaceDrivenAutoFocusEnabled: throws an NSInvalidArgumentException if the receiver doesn't support autofocus. -setAutomaticallyAdjustsFaceDrivenAutoFocusEnabled: throws an NSGenericException if called without first obtaining exclusive access to the receiver using -lockForConfiguration:. After setting automaticallyAdjustsFaceDrivenAutoFocusEnabled, call -setFocusMode: to apply the change.
 */
@property(nonatomic) BOOL automaticallyAdjustsFaceDrivenAutoFocusEnabled API_AVAILABLE(ios(15.4), macCatalyst(15.4), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

/*!
 @property faceDrivenAutoFocusEnabled
 @abstract
    Indicates whether face-driven autofocus is enabled on the receiver.
 
 @discussion
    Default is YES for all apps linked on or after iOS 15.4 when the receiver supports autofocus. -setFaceDrivenAutoFocusEnabled: throws an NSInvalidArgumentException if automaticallyAdjustsFaceDrivenAutoFocusEnabled returns YES.  -setFaceDrivenAutoFocusEnabled: throws an NSInvalidArgumentException if the receiver doesn't support autofocus. -setFaceDrivenAutoFocusEnabled: throws an NSGenericException if called without first obtaining exclusive access to the receiver using -lockForConfiguration:. Note that setting faceDrivenAutoFocusEnabled alone does not initiate this focus change operation. After setting faceDrivenAutoFocusEnabled, call -setFocusMode: to apply the change.
 */
@property(nonatomic, getter=isFaceDrivenAutoFocusEnabled) BOOL faceDrivenAutoFocusEnabled API_AVAILABLE(ios(15.4), macCatalyst(15.4), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

/*!
 @property lensPosition
 @abstract
    Indicates the focus position of the lens.
 
 @discussion
    The range of possible positions is 0.0 to 1.0, with 0.0 being the shortest distance at which the lens can focus and 1.0 the furthest. Note that 1.0 does not represent focus at infinity. The default value is 1.0. Note that a given lens position value does not correspond to an exact physical distance, nor does it represent a consistent focus distance from device to device. This property is key-value observable. It can be read at any time, regardless of focus mode, but can only be set via setFocusModeLockedWithLensPosition:completionHandler:.
 */
@property(nonatomic, readonly) float lensPosition API_AVAILABLE(ios(8.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @constant AVCaptureLensPositionCurrent
    A special value that may be passed as the lensPosition parameter of setFocusModeLockedWithLensPosition:completionHandler: to indicate that the caller does not wish to specify a value for the lensPosition property, and that it should instead be set to its current value. Note that the device may be adjusting lensPosition at the time of the call, in which case the value at which lensPosition is locked may differ from the value obtained by querying the lensPosition property.
 */
AVF_EXPORT const float AVCaptureLensPositionCurrent API_AVAILABLE(ios(8.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

/*!
 @method setFocusModeLockedWithLensPosition:completionHandler:
 @abstract
    Sets focusMode to AVCaptureFocusModeLocked and locks lensPosition at an explicit value.
 
 @param lensPosition
    The lens position, as described in the documentation for the lensPosition property. A value of AVCaptureLensPositionCurrent can be used to indicate that the caller does not wish to specify a value for lensPosition.
 @param handler
    A block to be called when lensPosition has been set to the value specified and focusMode is set to AVCaptureFocusModeLocked. If setFocusModeLockedWithLensPosition:completionHandler: is called multiple times, the completion handlers will be called in FIFO order. The block receives a timestamp which matches that of the first buffer to which all settings have been applied. Note that the timestamp is synchronized to the device clock, and thus must be converted to the `AVCaptureSession/synchronizationClock` prior to comparison with the timestamps of buffers delivered via an AVCaptureVideoDataOutput. The client may pass nil for the handler parameter if knowledge of the operation's completion is not required.
 
 @discussion
    This is the only way of setting lensPosition. This method throws an NSRangeException if lensPosition is set to an unsupported level. This method throws an NSGenericException if called without first obtaining exclusive access to the receiver using lockForConfiguration:.
 */
- (void)setFocusModeLockedWithLensPosition:(float)lensPosition completionHandler:(nullable void (^)(CMTime syncTime))handler API_AVAILABLE(ios(8.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @property minimumFocusDistance
 @abstract
    A property indicating the minimum focus distance.
 
 @discussion
    The minimum focus distance is given in millimeters, -1 if unknown. For virtual cameras (AVCaptureDeviceTypeBuiltInDualCamera, AVCaptureDeviceTypeBuiltInTripleCamera, etc.), the value reported is the smallest minimum focus distance of the auto-focus-capable cameras that it sources.
 */
@property(nonatomic, readonly) NSInteger minimumFocusDistance API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// Constants indicating the focus behavior when recording a Cinematic Video.
typedef NS_ENUM(NSInteger, AVCaptureCinematicVideoFocusMode) {
    /// Indicates that no focus mode is specified, in which case weak focus is used as default.
    AVCaptureCinematicVideoFocusModeNone   = 0,
    /// Indicates that the subject should remain in focus until it exits the scene.
    AVCaptureCinematicVideoFocusModeStrong = 1,
    /// Indicates that the Cinematic Video algorithm should automatically adjust focus according to the prominence of the subjects in the scene.
    AVCaptureCinematicVideoFocusModeWeak   = 2,
} NS_SWIFT_NAME(AVCaptureDevice.CinematicVideoFocusMode) API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// Focus on and start tracking a detected object.
///
/// - Parameter detectedObjectID: The ID of the detected object.
/// - Parameter focusMode: Specify whether to focus strongly or weakly.
- (void)setCinematicVideoTrackingFocusWithDetectedObjectID:(NSInteger)detectedObjectID focusMode:(AVCaptureCinematicVideoFocusMode)focusMode NS_SWIFT_NAME(setCinematicVideoTrackingFocus(detectedObjectID:focusMode:)) API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// Focus on and start tracking an object if it can be detected at the region specified by the point.
///
/// - Parameter point: A normalized point of interest (i.e., [0,1]) in the coordinate space of the device.
/// - Parameter focusMode: Specify whether to focus strongly or weakly.
- (void)setCinematicVideoTrackingFocusAtPoint:(CGPoint)point focusMode:(AVCaptureCinematicVideoFocusMode)focusMode NS_SWIFT_NAME(setCinematicVideoTrackingFocus(at:focusMode:)) API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// Fix focus at a distance.
///
/// - Parameter point: A normalized point of interest (i.e., [0,1]) in the coordinate space of the device.
/// - Parameter focusMode: Specify whether to focus strongly or weakly.
///
/// The distance at which focus is set is determined internally using signals such as depth data.
- (void)setCinematicVideoFixedFocusAtPoint:(CGPoint)point focusMode:(AVCaptureCinematicVideoFocusMode)focusMode NS_SWIFT_NAME(setCinematicVideoFixedFocus(at:focusMode:)) API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

@end


/*!
 @enum AVCaptureExposureMode
 @abstract
    Constants indicating the mode of the exposure on the receiver's device, if it has adjustable exposure.
 
 @constant AVCaptureExposureModeLocked
    Indicates that the exposure should be locked at its current value.
 @constant AVCaptureExposureModeAutoExpose
    Indicates that the device should automatically adjust exposure once and then change the exposure mode to AVCaptureExposureModeLocked.
 @constant AVCaptureExposureModeContinuousAutoExposure
    Indicates that the device should automatically adjust exposure when needed.
 @constant AVCaptureExposureModeCustom
    Indicates that the device should only adjust exposure according to user provided ISO, exposureDuration values.
 */
typedef NS_ENUM(NSInteger, AVCaptureExposureMode) {
    AVCaptureExposureModeLocked                            = 0,
    AVCaptureExposureModeAutoExpose                        = 1,
    AVCaptureExposureModeContinuousAutoExposure            = 2,
    AVCaptureExposureModeCustom API_AVAILABLE(macos(10.15), ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(visionos) = 3,
} API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);


API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDevice (AVCaptureDeviceExposure)

/*!
 @method isExposureModeSupported:
 @abstract
    Returns whether the receiver supports the given exposure mode.
 
 @param exposureMode
    An AVCaptureExposureMode to be checked.
 @result
    YES if the receiver supports the given exposure mode, NO otherwise.
 
 @discussion
    The receiver's exposureMode property can only be set to a certain mode if this method returns YES for that mode.
 */
- (BOOL)isExposureModeSupported:(AVCaptureExposureMode)exposureMode;

/*!
 @property exposureMode
 @abstract
    Indicates current exposure mode of the receiver, if it has adjustable exposure.
 
 @discussion
    The value of this property is an AVCaptureExposureMode that determines the receiver's exposure mode, if it has adjustable exposure. -setExposureMode: throws an NSInvalidArgumentException if set to an unsupported value (see -isExposureModeSupported:). -setExposureMode: throws an NSGenericException if called without first obtaining exclusive access to the receiver using lockForConfiguration:. When using AVCapturePhotoOutput and capturing photos with AVCapturePhotoSettings' photoQualityPrioritization property set to AVCapturePhotoQualityPrioritizationBalanced or higher, the receiver's ISO and exposureDuration values may be overridden when exposing the photo if the scene is dark enough to warrant some form of multi-image fusion to improve quality. To ensure that the receiver's ISO and exposureDuration values are honored while in AVCaptureExposureModeCustom or AVCaptureExposureModeLocked, you must set your AVCapturePhotoSettings.photoQualityPrioritization property to AVCapturePhotoQualityPrioritizationSpeed. The same rule applies if you are using the deprecated AVCapturePhotoSettings.autoStillImageStabilizationEnabled property; you must set it to NO to preserve your custom exposure values in the photo capture. Likewise if you're using AVCaptureStillImageOutput, automaticallyEnablesStillImageStabilizationWhenAvailable must be set to NO to preserve your custom exposure values in a still image capture. Clients can observe automatic changes to the receiver's exposureMode by key value observing this property.
 */
@property(nonatomic) AVCaptureExposureMode exposureMode;

/*!
 @property exposurePointOfInterestSupported:
 @abstract
    Indicates whether the receiver supports exposure points of interest.
 
 @discussion
    The receiver's exposurePointOfInterest property can only be set if this property returns YES.
 */
@property(nonatomic, readonly, getter=isExposurePointOfInterestSupported) BOOL exposurePointOfInterestSupported;

/*!
 @property exposurePointOfInterest
 @abstract
    Indicates current exposure point of interest of the receiver, if it has one.
 
 @discussion
    The value of this property is a CGPoint that determines the receiver's exposure point of interest, if it has adjustable exposure. A value of (0,0) indicates that the camera should adjust exposure based on the top left corner of the image, while a value of (1,1) indicates that it should adjust exposure based on the bottom right corner. The default value is (0.5,0.5). -setExposurePointOfInterest: throws an NSInvalidArgumentException if isExposurePointOfInterestSupported returns NO. -setExposurePointOfInterest: throws an NSGenericException if called without first obtaining exclusive access to the receiver using lockForConfiguration:. Note that setting exposurePointOfInterest alone does not initiate an exposure operation. After setting exposurePointOfInterest, call -setExposureMode: to apply the new point of interest.
 */
@property(nonatomic) CGPoint exposurePointOfInterest;

/// Whether the device supports exposure rectangles of interest.
///
/// You may only set the device's ``exposureRectOfInterest`` property if this property returns `true`.
@property(nonatomic, readonly, getter=isExposureRectOfInterestSupported) BOOL exposureRectOfInterestSupported API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// The minimum size you may use when specifying a rectangle of interest.
///
/// The size returned is in normalized coordinates, and depends on the current ``AVCaptureDevice/activeFormat``. If ``exposureRectOfInterestSupported`` returns `false`, this property returns { 0, 0 }.
@property(nonatomic, readonly) CGSize minExposureRectOfInterestSize API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// The device's current exposure rectangle of interest, if it has one.
///
/// The value of this property is a ``CGRect`` determining the device's exposure rectangle of interest. Use this as an alternative to setting ``exposurePointOfInterest``, as it allows you to specify both a location and size. For example, a value of `CGRectMake(0, 0, 1, 1)` tells the device to use the entire field of view when determining the exposure, while `CGRectMake(0, 0, 0.25, 0.25)` indicates the top left sixteenth, and `CGRectMake(0.75, 0.75, 0.25, 0.25)` indicates the bottom right sixteenth. Setting ``exposureRectOfInterest`` throws an `NSInvalidArgumentException` if ``exposureRectOfInterestSupported`` returns `false`. Setting ``exposureRectOfInterest`` throws an `NSInvalidArgumentException` if your provided rectangle's size is smaller than the ``minExposureRectOfInterestSize``. Setting ``exposureRectOfInterest`` throws an `NSGenericException` if you call it without first obtaining exclusive access to the device using ``AVCaptureDevice/lockForConfiguration:``. Setting ``exposureRectOfInterest`` updates the device's ``exposurePointOfInterest`` to the center of your provided rectangle of interest. If you later set the device's ``exposurePointOfInterest``, the ``exposureRectOfInterest`` resets to the default sized rectangle of interest for the new exposure point of interest. If you change your ``AVCaptureDevice/activeFormat``, the point of interest and rectangle of interest both revert to their default values. You can observe automatic changes to the device's ``exposureRectOfInterest`` by key-value observing this property.
///
/// - Note: Setting ``exposureRectOfInterest`` alone does not initiate an exposure operation. After setting ``exposureRectOfInterest``, set ``exposureMode`` to apply the new rectangle of interest.
@property(nonatomic) CGRect exposureRectOfInterest API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// The default rectangle of interest used for a given exposure point of interest.
///
/// - Parameter pointOfInterest: The point of interest for which you want the default rectangle of interest.
///
/// For example, pass `(0.5, 0.5)` to get the exposure rectangle of interest used for the default exposure point of interest at `(0.5, 0.5)`.
///
/// This method returns `CGRectNull` if ``exposureRectOfInterestSupported`` returns `false`.
- (CGRect)defaultRectForExposurePointOfInterest:(CGPoint)pointOfInterest API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @property automaticallyAdjustsFaceDrivenAutoExposureEnabled
 @abstract
    Indicates whether the receiver should automatically adjust face-driven auto exposure.
 
 @discussion
    The value of this property is a BOOL that determines the receiver's automatic adjustment of face-driven auto exposure. Default is YES on all platforms, if the receiver supports auto exposure. This property must be set to NO before manually setting faceDrivenAutoExposureEnabled to YES/NO. -setAutomaticallyAdjustsFaceDrivenAutoExposureEnabled: throws an NSInvalidArgumentException if the receiver doesn't support auto exposure. -setAutomaticallyAdjustsFaceDrivenAutoExposureEnabled: throws an NSGenericException if called without first obtaining exclusive access to the receiver using -lockForConfiguration:. After setting automaticallyAdjustsFaceDrivenAutoExposureEnabled, call -setExposureMode: to apply the change.
 */
@property(nonatomic) BOOL automaticallyAdjustsFaceDrivenAutoExposureEnabled API_AVAILABLE(ios(15.4), macCatalyst(15.4), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

/*!
 @property faceDrivenAutoExposureEnabled
 @abstract
    Indicates whether face-driven auto exposure is enabled on the receiver.
 
 @discussion
    Default is YES for all apps linked on or after iOS 15.4 when the receiver supports auto exposure. -setFaceDrivenAutoExposureEnabled: throws an NSInvalidArgumentException if automaticallyAdjustsFaceDrivenAutoExposureEnabled returns YES. -setFaceDrivenAutoExposureEnabled: throws an NSInvalidArgumentException if the receiver doesn't support auto exposure. -setFaceDrivenAutoExposureEnabled: throws an NSGenericException if called without first obtaining exclusive access to the receiver using -lockForConfiguration:. Note that setting faceDrivenAutoExposureEnabled alone does not initiate this exposure change operation. After setting faceDrivenAutoExposureEnabled, call -setExposureMode: to apply the change.
 */
@property(nonatomic, getter=isFaceDrivenAutoExposureEnabled) BOOL faceDrivenAutoExposureEnabled API_AVAILABLE(ios(15.4), macCatalyst(15.4), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

/*!
 @constant activeMaxExposureDuration
 @abstract
    The maximum exposure (integration) time that may be used by the auto exposure algorithm.
 
 @discussion
    When an AVCaptureDevice's exposureMode is set to AVCaptureExposureModeAutoExpose or AVCaptureExposureModeContinuousAutoExposure, the auto exposure algorithm picks a default max exposure duration that is tuned for the current configuration, balancing low light image quality with motion preservation. By querying or key-value observing this property, you may find out the current max exposure duration in use. You may also override the default value by setting this property to a value between activeFormat.maxExposureDuration and activeFormat.minExposureDuration. An NSRangeException is thrown if you pass an out-of-bounds exposure duration. Setting the property to the special value of kCMTimeInvalid resets the auto exposure max duration to the device's default for your current configuration. When the device's activeFormat or the AVCaptureSession's sessionPreset changes, this property resets to the default max exposure duration for the new format or session preset.
 
    On some devices, the auto exposure algorithm picks a different max exposure duration for a given format depending whether you used the -[AVCaptureSession setSessionPreset:] API or the -[AVCaptureDevice setActiveFormat:] API to set the format. To ensure uniform default handling of max exposure duration, you can set your AVCaptureDeviceInput's unifiedAutoExposureDefaultsEnabled property to YES.
 */
@property(nonatomic) CMTime activeMaxExposureDuration API_AVAILABLE(ios(12.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

/*!
 @property adjustingExposure
 @abstract
    Indicates whether the receiver is currently adjusting camera exposure.
 
 @discussion
    The value of this property is a BOOL indicating whether the receiver's camera exposure is being automatically adjusted because its exposure mode is AVCaptureExposureModeAutoExpose or AVCaptureExposureModeContinuousAutoExposure. Clients can observe the value of this property to determine whether the camera exposure is stable or is being automatically adjusted.
 */
@property(nonatomic, readonly, getter=isAdjustingExposure) BOOL adjustingExposure;

/*!
 @property lensAperture
 @abstract
    The size of the lens diaphragm.
 
 @discussion
    The value of this property is a float indicating the size (f number) of the lens diaphragm. This property does not change.
 */
@property(nonatomic, readonly) float lensAperture API_AVAILABLE(ios(8.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @property exposureDuration
 @abstract
    The length of time over which exposure takes place.
 
 @discussion
    Only exposure duration values between activeFormat.minExposureDuration and activeFormat.maxExposureDuration are supported. This property is key-value observable. It can be read at any time, regardless of exposure mode, but can only be set via setExposureModeCustomWithDuration:ISO:completionHandler:.
 */
@property(nonatomic, readonly) CMTime exposureDuration API_AVAILABLE(ios(8.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @property ISO
 @abstract
    The current exposure ISO value.
 
 @discussion
    This property controls the sensor's sensitivity to light by means of a gain value applied to the signal. Only ISO values between activeFormat.minISO and activeFormat.maxISO are supported. Higher values will result in noisier images. This property is key-value observable. It can be read at any time, regardless of exposure mode, but can only be set via setExposureModeCustomWithDuration:ISO:completionHandler:.
 */
@property(nonatomic, readonly) float ISO API_AVAILABLE(ios(8.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @constant AVCaptureExposureDurationCurrent
    A special value that may be passed as the duration parameter of setExposureModeCustomWithDuration:ISO:completionHandler: to indicate that the caller does not wish to specify a value for the exposureDuration property, and that it should instead be set to its current value. Note that the device may be adjusting exposureDuration at the time of the call, in which case the value to which exposureDuration is set may differ from the value obtained by querying the exposureDuration property.
 */
AVF_EXPORT const CMTime AVCaptureExposureDurationCurrent API_AVAILABLE(ios(8.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

/*!
 @constant AVCaptureISOCurrent
    A special value that may be passed as the ISO parameter of setExposureModeCustomWithDuration:ISO:completionHandler: to indicate that the caller does not wish to specify a value for the ISO property, and that it should instead be set to its current value. Note that the device may be adjusting ISO at the time of the call, in which case the value to which ISO is set may differ from the value obtained by querying the ISO property.
 */
AVF_EXPORT const float AVCaptureISOCurrent API_AVAILABLE(ios(8.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

/*!
 @method setExposureModeCustomWithDuration:ISO:completionHandler:
 @abstract
    Sets exposureMode to AVCaptureExposureModeCustom and locks exposureDuration and ISO at explicit values.
 
 @param duration
    The exposure duration, as described in the documentation for the exposureDuration property. A value of AVCaptureExposureDurationCurrent can be used to indicate that the caller does not wish to specify a value for exposureDuration. Note that changes to this property may result in changes to activeVideoMinFrameDuration and/or activeVideoMaxFrameDuration.
 @param ISO
    The exposure ISO value, as described in the documentation for the ISO property. A value of AVCaptureISOCurrent can be used to indicate that the caller does not wish to specify a value for ISO.
 @param handler
    A block to be called when both exposureDuration and ISO have been set to the values specified and exposureMode is set to AVCaptureExposureModeCustom. If setExposureModeCustomWithDuration:ISO:completionHandler: is called multiple times, the completion handlers will be called in FIFO order. The block receives a timestamp which matches that of the first buffer to which all settings have been applied. Note that the timestamp is synchronized to the device clock, and thus must be converted to the `AVCaptureSession/synchronizationClock` prior to comparison with the timestamps of buffers delivered via an AVCaptureVideoDataOutput. The client may pass nil for the handler parameter if knowledge of the operation's completion is not required.
 
 @discussion
    This is the only way of setting exposureDuration and ISO. This method throws an NSRangeException if either exposureDuration or ISO is set to an unsupported level. This method throws an NSGenericException if called without first obtaining exclusive access to the receiver using lockForConfiguration:. When using AVCapturePhotoOutput to capture photos, note that the photoQualityPrioritization property of AVCapturePhotoSettings defaults to AVCapturePhotoQualityPrioritizationBalanced, which allows photo capture to temporarily override the capture device's ISO and exposureDuration values if the scene is dark enough to warrant some form of multi-image fusion to improve quality. To ensure that the receiver's ISO and exposureDuration values are honored while in AVCaptureExposureModeCustom or AVCaptureExposureModeLocked, you must set your AVCapturePhotoSettings.photoQualityPrioritization property to AVCapturePhotoQualityPrioritizationSpeed. The same rule applies if you use the deprecated AVCapturePhotoSettings.autoStillImageStabilizationEnabled property or AVCaptureStillImageOutput.automaticallyEnablesStillImageStabilizationWhenAvailable property. You must set them to NO to preserve your custom or locked exposure settings.
 */
- (void)setExposureModeCustomWithDuration:(CMTime)duration ISO:(float)ISO completionHandler:(nullable void (^)(CMTime syncTime))handler API_AVAILABLE(ios(8.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @property exposureTargetOffset
 @abstract
    Indicates the metered exposure level's offset from the target exposure value, in EV units.
 
 @discussion
    The value of this read-only property indicates the difference between the metered exposure level of the current scene and the target exposure value. This property is key-value observable.
 */
@property(nonatomic, readonly) float exposureTargetOffset API_AVAILABLE(ios(8.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @property exposureTargetBias
 @abstract
    Bias applied to the target exposure value, in EV units.
 
 @discussion
    When exposureMode is AVCaptureExposureModeContinuousAutoExposure or AVCaptureExposureModeLocked, the bias will affect both metering (exposureTargetOffset), and the actual exposure level (exposureDuration and ISO). When the exposure mode is AVCaptureExposureModeCustom, it will only affect metering. This property is key-value observable. It can be read at any time, but can only be set via setExposureTargetBias:completionHandler:.
 */
@property(nonatomic, readonly) float exposureTargetBias API_AVAILABLE(ios(8.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @property minExposureTargetBias
 @abstract
    A float indicating the minimum supported exposure bias, in EV units.
 
 @discussion
    This read-only property indicates the minimum supported exposure bias.
 */
@property(nonatomic, readonly) float minExposureTargetBias API_AVAILABLE(ios(8.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @property maxExposureTargetBias
 @abstract
    A float indicating the maximum supported exposure bias, in EV units.
 
 @discussion
    This read-only property indicates the maximum supported exposure bias.
 */
@property(nonatomic, readonly) float maxExposureTargetBias API_AVAILABLE(ios(8.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @constant AVCaptureExposureTargetBiasCurrent
    A special value that may be passed as the bias parameter of setExposureTargetBias:completionHandler: to indicate that the caller does not wish to specify a value for the exposureTargetBias property, and that it should instead be set to its current value.
 */
AVF_EXPORT const float AVCaptureExposureTargetBiasCurrent API_AVAILABLE(ios(8.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

/*!
 @method setExposureTargetBias:completionHandler:
 @abstract
    Sets the bias to be applied to the target exposure value.
 
 @param bias
    The bias to be applied to the exposure target value, as described in the documentation for the exposureTargetBias property.
 @param handler
    A block to be called when exposureTargetBias has been set to the value specified. If setExposureTargetBias:completionHandler: is called multiple times, the completion handlers will be called in FIFO order. The block receives a timestamp which matches that of the first buffer to which the setting has been applied. Note that the timestamp is synchronized to the device clock, and thus must be converted to the `AVCaptureSession/synchronizationClock` prior to comparison with the timestamps of buffers delivered via an AVCaptureVideoDataOutput. The client may pass nil for the handler parameter if knowledge of the operation's completion is not required.
 
 @discussion
    This is the only way of setting exposureTargetBias. This method throws an NSRangeException if exposureTargetBias is set to an unsupported level. This method throws an NSGenericException if called without first obtaining exclusive access to the receiver using lockForConfiguration:.
 */
- (void)setExposureTargetBias:(float)bias completionHandler:(nullable void (^)(CMTime syncTime))handler API_AVAILABLE(ios(8.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

@end


API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDevice (AVCaptureDeviceToneMapping)

/*!
 @property globalToneMappingEnabled
 @abstract
    Indicates whether the receiver should use global tone mapping.
 
 @discussion
    Tone mapping is a technique used by the device to map the pixel levels in high dynamic range images to a more limited dynamic range (such as 16 bit to 8 bit), while still retaining as close an appearance as possible. Normally the device employs adaptive, local tone curves to preserve highest image quality and adapt quickly to changing lighting conditions.
 
    This property indicates to the receiver to use a global tone map. If set to YES, the tone map is adjusted dynamically depending on the current scene and the same tone map is applied to all pixels in an image. If set to its default value of NO, different tone maps may be applied to different pixels in an image.
 
    globalToneMappingEnabled may only be set to YES if the receiver's activeFormat.isGlobalToneMappingSupported property returns YES, otherwise an NSGenericException is thrown. Setting globalToneMappingEnabled throws an NSGenericException if called without first obtaining exclusive access to the receiver using lockForConfiguration:.
 
    When global tone mapping is enabled, an AVCapturePhotoOutput connected to the AVCaptureDeviceInput’s session disables all forms of still image fusion, resulting in still images with no automatic stabilization applied.
 
    The receiver’s globalToneMappingEnabled resets to its default value of NO under the following conditions:
     - The receiver’s activeFormat changes
     - The receiver’s AVCaptureDeviceInput’s session’s sessionPreset changes
     - The receiver’s AVCaptureDeviceInput is added to a session
 
    Clients can observe automatic changes to the receiver's globalToneMappingEnabled by key value observing this property.
 */
@property(nonatomic, getter=isGlobalToneMappingEnabled) BOOL globalToneMappingEnabled API_AVAILABLE(ios(13.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

@end


/*!
 @enum AVCaptureWhiteBalanceMode
 @abstract
    Constants indicating the mode of the white balance on the receiver's device, if it has adjustable white balance.
 
 @constant AVCaptureWhiteBalanceModeLocked
    Indicates that the white balance should be locked at its current value.
 @constant AVCaptureWhiteBalanceModeAutoWhiteBalance
    Indicates that the device should automatically adjust white balance once and then change the white balance mode to AVCaptureWhiteBalanceModeLocked.
 @constant AVCaptureWhiteBalanceModeContinuousAutoWhiteBalance
    Indicates that the device should automatically adjust white balance when needed.
 */
typedef NS_ENUM(NSInteger, AVCaptureWhiteBalanceMode) {
    AVCaptureWhiteBalanceModeLocked                     = 0,
    AVCaptureWhiteBalanceModeAutoWhiteBalance           = 1,
    AVCaptureWhiteBalanceModeContinuousAutoWhiteBalance = 2,
} API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);


/*!
 @typedef AVCaptureWhiteBalanceGains
 @abstract
    Structure containing RGB white balance gain values.
 */
typedef struct {
    float redGain;
    float greenGain;
    float blueGain;
} AVCaptureWhiteBalanceGains API_AVAILABLE(ios(8.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);


/*!
 @typedef AVCaptureWhiteBalanceChromaticityValues
 @abstract
    Structure containing CIE 1931 xy chromaticity values.
 */
typedef struct {
    float x;
    float y;
} AVCaptureWhiteBalanceChromaticityValues API_AVAILABLE(ios(8.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);


/*!
 @typedef AVCaptureWhiteBalanceTemperatureAndTintValues
 @abstract
    Structure containing a white balance color correlated temperature in kelvin, plus a tint value in the range of [-150 - +150].
 */
typedef struct {
    float temperature;
    float tint;
} AVCaptureWhiteBalanceTemperatureAndTintValues API_AVAILABLE(ios(8.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

/// Temperature and tint values ideal for scenes illuminated with a tungsten light source.
AVF_EXPORT AVCaptureWhiteBalanceTemperatureAndTintValues const AVCaptureWhiteBalanceTemperatureAndTintValuesTungsten NS_SWIFT_NAME(AVCaptureWhiteBalanceTemperatureAndTintValues.tungsten) API_AVAILABLE(ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

/// Temperature and tint values ideal for scenes illuminated with a fluorescent light source.
AVF_EXPORT AVCaptureWhiteBalanceTemperatureAndTintValues const AVCaptureWhiteBalanceTemperatureAndTintValuesFluorescent NS_SWIFT_NAME(AVCaptureWhiteBalanceTemperatureAndTintValues.fluorescent) API_AVAILABLE(ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

/// Temperature and tint values ideal for scenes illuminated with natural daylight.
AVF_EXPORT AVCaptureWhiteBalanceTemperatureAndTintValues const AVCaptureWhiteBalanceTemperatureAndTintValuesDaylight NS_SWIFT_NAME(AVCaptureWhiteBalanceTemperatureAndTintValues.daylight) API_AVAILABLE(ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

/// Temperature and tint values ideal for scenes illuminated with natural cloudy daylight.
AVF_EXPORT AVCaptureWhiteBalanceTemperatureAndTintValues const AVCaptureWhiteBalanceTemperatureAndTintValuesCloudy NS_SWIFT_NAME(AVCaptureWhiteBalanceTemperatureAndTintValues.cloudy) API_AVAILABLE(ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

/// Temperature and tint values ideal for scenes illuminated with daylight but in heavy shade.
AVF_EXPORT AVCaptureWhiteBalanceTemperatureAndTintValues const AVCaptureWhiteBalanceTemperatureAndTintValuesShadow NS_SWIFT_NAME(AVCaptureWhiteBalanceTemperatureAndTintValues.shadow) API_AVAILABLE(ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);


API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDevice (AVCaptureDeviceWhiteBalance)

/*!
 @method isWhiteBalanceModeSupported:
 @abstract
    Returns whether the receiver supports the given white balance mode.
 
 @param whiteBalanceMode
    An AVCaptureWhiteBalanceMode to be checked.
 @result
    YES if the receiver supports the given white balance mode, NO otherwise.
 
 @discussion
    The receiver's whiteBalanceMode property can only be set to a certain mode if this method returns YES for that mode.
 */
- (BOOL)isWhiteBalanceModeSupported:(AVCaptureWhiteBalanceMode)whiteBalanceMode;

/*!
 @property lockingWhiteBalanceWithCustomDeviceGainsSupported
 @abstract
    Indicates whether the receiver supports white balance gains other than AVCaptureWhiteBalanceGainsCurrent.
 
 @discussion
    If lockingWhiteBalanceWithCustomDeviceGainsSupported returns NO, setWhiteBalanceModeLockedWithDeviceWhiteBalanceGains: may only be called with AVCaptureWhiteBalanceGainsCurrent. Passing any other white balance gains will result in an exception.
 */
@property(nonatomic, readonly, getter=isLockingWhiteBalanceWithCustomDeviceGainsSupported) BOOL lockingWhiteBalanceWithCustomDeviceGainsSupported API_AVAILABLE(ios(10.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @property whiteBalanceMode
 @abstract
    Indicates current white balance mode of the receiver, if it has adjustable white balance.
 
 @discussion
    The value of this property is an AVCaptureWhiteBalanceMode that determines the receiver's white balance mode, if it has adjustable white balance. -setWhiteBalanceMode: throws an NSInvalidArgumentException if set to an unsupported value (see -isWhiteBalanceModeSupported:). -setWhiteBalanceMode: throws an NSGenericException if called without first obtaining exclusive access to the receiver using lockForConfiguration:. Clients can observe automatic changes to the receiver's whiteBalanceMode by key value observing this property.
 */
@property(nonatomic) AVCaptureWhiteBalanceMode whiteBalanceMode;

/*!
 @property adjustingWhiteBalance
 @abstract
    Indicates whether the receiver is currently adjusting camera white balance.
 
 @discussion
    The value of this property is a BOOL indicating whether the receiver's camera white balance is being automatically adjusted because its white balance mode is AVCaptureWhiteBalanceModeAutoWhiteBalance or AVCaptureWhiteBalanceModeContinuousAutoWhiteBalance. Clients can observe the value of this property to determine whether the camera white balance is stable or is being automatically adjusted.
 */
@property(nonatomic, readonly, getter=isAdjustingWhiteBalance) BOOL adjustingWhiteBalance;

/*!
 @property deviceWhiteBalanceGains
 @abstract
    Indicates the current device-specific RGB white balance gain values in use.
 
 @discussion
    This property specifies the current red, green, and blue gain values used for white balance. The values can be used to adjust color casts for a given scene. For each channel, only values between 1.0 and -maxWhiteBalanceGain are supported. This property is key-value observable. It can be read at any time, regardless of white balance mode, but can only be set via setWhiteBalanceModeLockedWithDeviceWhiteBalanceGains:completionHandler:.
 */
@property(nonatomic, readonly) AVCaptureWhiteBalanceGains deviceWhiteBalanceGains API_AVAILABLE(ios(8.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @property grayWorldDeviceWhiteBalanceGains
 @abstract
    Indicates the current device-specific Gray World RGB white balance gain values in use.
 
 @discussion
    This property specifies the current red, green, and blue gain values derived from the current scene to deliver a neutral (or "Gray World") white point for white balance. Gray World values assume a neutral subject (e.g. a gray card) has been placed in the middle of the subject area and fills the center 50% of the frame. Clients can read these values and apply them to the device using setWhiteBalanceModeLockedWithDeviceWhiteBalanceGains:completionHandler:. For each channel, only values between 1.0 and -maxWhiteBalanceGain are supported. This property is key-value observable. It can be read at any time, regardless of white balance mode.
 */
@property(nonatomic, readonly) AVCaptureWhiteBalanceGains grayWorldDeviceWhiteBalanceGains API_AVAILABLE(ios(8.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @property maxWhiteBalanceGain
 @abstract
    Indicates the maximum supported value to which a channel in the AVCaptureWhiteBalanceGains may be set.
 
 @discussion
    This property does not change for the life of the receiver.
 */
@property(nonatomic, readonly) float maxWhiteBalanceGain API_AVAILABLE(ios(8.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @constant AVCaptureWhiteBalanceGainsCurrent
    A special value that may be passed as a parameter of setWhiteBalanceModeLockedWithDeviceWhiteBalanceGains:completionHandler: to indicate that the caller does not wish to specify a value for deviceWhiteBalanceGains, and that gains should instead be locked at their value at the moment that white balance is locked.
 */
AVF_EXPORT const AVCaptureWhiteBalanceGains AVCaptureWhiteBalanceGainsCurrent API_AVAILABLE(ios(8.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

/// Sets white balance to locked mode with explicit temperature and tint values.
///
/// - Parameter whiteBalanceTemperatureAndTintValues: The white balance temperature and tint values, as computed from ``temperatureAndTintValuesForDeviceWhiteBalanceGains:`` method, ``AVCaptureWhiteBalanceTemperatureAndTintValues`` presets or manual input.
///
/// - Parameter handler: A block to be called when white balance values have been set to the values specified and ``whiteBalanceMode`` is set to ``AVCaptureWhiteBalanceModeLocked``. If ``setWhiteBalanceModeLockedWithDeviceWhiteBalanceTemperatureAndTintValues:completionHandler:`` is called multiple times, the completion handlers are called in FIFO order. The block receives a timestamp which matches that of the first buffer to which all settings have been applied. Note that the timestamp is synchronized to the device clock, and thus must be converted to the ``AVCaptureSession/synchronizationClock`` prior to comparison with the timestamps of buffers delivered via an ``AVCaptureVideoDataOutput``. This parameter may be `nil` if synchronization is not required.
///
/// This method takes a ``AVCaptureWhiteBalanceTemperatureAndTintValues`` struct and applies the appropriate ``AVCaptureWhiteBalanceGains``. This method throws an `NSRangeException` if any of the values are set to an unsupported level. This method throws an `NSGenericException` if called without first obtaining exclusive access to the device using ``AVCaptureDevice/lockForConfiguration:``.
- (void)setWhiteBalanceModeLockedWithDeviceWhiteBalanceTemperatureAndTintValues:(AVCaptureWhiteBalanceTemperatureAndTintValues)whiteBalanceTemperatureAndTintValues completionHandler:(nullable void (^)(CMTime syncTime))handler NS_SWIFT_NAME(setWhiteBalanceModeLocked(whiteBalanceTemperatureAndTintValues:handler:)) API_AVAILABLE(ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

/*!
 @method setWhiteBalanceModeLockedWithDeviceWhiteBalanceGains:completionHandler:
 @abstract
    Sets white balance to locked mode with explicit deviceWhiteBalanceGains values.
 
 @param whiteBalanceGains
    The white balance gain values, as described in the documentation for the deviceWhiteBalanceGains property. A value of AVCaptureWhiteBalanceGainsCurrent can be used to indicate that the caller does not wish to specify a value for deviceWhiteBalanceGains.
 @param handler
    A block to be called when white balance gains have been set to the values specified and whiteBalanceMode is set to AVCaptureWhiteBalanceModeLocked. If setWhiteBalanceModeLockedWithDeviceWhiteBalanceGains:completionHandler: is called multiple times, the completion handlers will be called in FIFO order. The block receives a timestamp which matches that of the first buffer to which all settings have been applied. Note that the timestamp is synchronized to the device clock, and thus must be converted to the `AVCaptureSession/synchronizationClock` prior to comparison with the timestamps of buffers delivered via an AVCaptureVideoDataOutput. This parameter may be nil if synchronization is not required.
 
 @discussion
    Gain values are normalized to the minimum channel value to avoid brightness changes (e.g. R:2 G:2 B:4 will be normalized to R:1 G:1 B:2). For each channel in the whiteBalanceGains struct, only values between 1.0 and maxWhiteBalanceGain after nomalization are supported.  This method throws an NSRangeException if any of the whiteBalanceGains are set to an unsupported level. This method throws an NSGenericException if called without first obtaining exclusive access to the receiver using lockForConfiguration:.
 */
- (void)setWhiteBalanceModeLockedWithDeviceWhiteBalanceGains:(AVCaptureWhiteBalanceGains)whiteBalanceGains completionHandler:(nullable void (^)(CMTime syncTime))handler API_AVAILABLE(ios(8.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @method chromaticityValuesForDeviceWhiteBalanceGains:
 @abstract
    Converts device-specific white balance RGB gain values to device-independent chromaticity values.
 
 @param whiteBalanceGains
    White balance gain values, as described in the documentation for the deviceWhiteBalanceGains property. A value of AVCaptureWhiteBalanceGainsCurrent may not be used in this function.
 @result
    A fully populated AVCaptureWhiteBalanceChromaticityValues structure containing device-independent values.
 
 @discussion
    This method may be called on the receiver to convert device-specific white balance RGB gain values to device-independent chromaticity (little x, little y) values. For each channel in the whiteBalanceGains struct, only values between 1.0 and -maxWhiteBalanceGain are supported. This method throws an NSRangeException if any of the whiteBalanceGains are set to unsupported values.
 */
- (AVCaptureWhiteBalanceChromaticityValues)chromaticityValuesForDeviceWhiteBalanceGains:(AVCaptureWhiteBalanceGains)whiteBalanceGains API_AVAILABLE(ios(8.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @method deviceWhiteBalanceGainsForChromaticityValues:
 @abstract
    Converts device-independent chromaticity values to device-specific white balance RGB gain values.
 
 @param chromaticityValues
    Little x, little y chromaticity values as described in the documentation for AVCaptureWhiteBalanceChromaticityValues.
 @result
    A fully populated AVCaptureWhiteBalanceGains structure containing device-specific RGB gain values.
 
 @discussion
    This method may be called on the receiver to convert device-independent chromaticity values to device-specific RGB white balance gain values. This method throws an NSRangeException if any of the chromaticityValues are set outside the range [0,1]. Note that some x,y combinations yield out-of-range device RGB values that will cause an exception to be thrown if passed directly to -setWhiteBalanceModeLockedWithDeviceWhiteBalanceGains:completionHandler:. Be sure to check that red, green, and blue gain values are within the range of [1.0 - maxWhiteBalanceGain].
 */
- (AVCaptureWhiteBalanceGains)deviceWhiteBalanceGainsForChromaticityValues:(AVCaptureWhiteBalanceChromaticityValues)chromaticityValues API_AVAILABLE(ios(8.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @method temperatureAndTintValuesForDeviceWhiteBalanceGains:
 @abstract
    Converts device-specific white balance RGB gain values to device-independent temperature and tint values.
 
 @param whiteBalanceGains
    White balance gain values, as described in the documentation for the deviceWhiteBalanceGains property. A value of AVCaptureWhiteBalanceGainsCurrent may not be used in this function.
 @result
    A fully populated AVCaptureWhiteBalanceTemperatureAndTintValues structure containing device-independent values.
 
 @discussion
    This method may be called on the receiver to convert device-specific white balance RGB gain values to device-independent temperature (in kelvin) and tint values. For each channel in the whiteBalanceGains struct, only values between 1.0 and -maxWhiteBalanceGain are supported. This method throws an NSRangeException if any of the whiteBalanceGains are set to unsupported values.
 */
- (AVCaptureWhiteBalanceTemperatureAndTintValues)temperatureAndTintValuesForDeviceWhiteBalanceGains:(AVCaptureWhiteBalanceGains)whiteBalanceGains API_AVAILABLE(ios(8.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @method deviceWhiteBalanceGainsForTemperatureAndTintValues:
 @abstract
    Converts device-independent temperature and tint values to device-specific white balance RGB gain values.
 
 @param tempAndTintValues
    Temperature and tint values as described in the documentation for AVCaptureWhiteBalanceTemperatureAndTintValues.
 @result
    A fully populated AVCaptureWhiteBalanceGains structure containing device-specific RGB gain values.
 
 @discussion
    This method may be called on the receiver to convert device-independent temperature and tint values to device-specific RGB white balance gain values. You may pass any temperature and tint values and corresponding white balance gains will be produced. Note though that some temperature and tint combinations yield out-of-range device RGB values that will cause an exception to be thrown if passed directly to -setWhiteBalanceModeLockedWithDeviceWhiteBalanceGains:completionHandler:. Be sure to check that red, green, and blue gain values are within the range of [1.0 - maxWhiteBalanceGain].
 */
- (AVCaptureWhiteBalanceGains)deviceWhiteBalanceGainsForTemperatureAndTintValues:(AVCaptureWhiteBalanceTemperatureAndTintValues)tempAndTintValues API_AVAILABLE(ios(8.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

@end


API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDevice (AVCaptureDeviceSubjectAreaChangeMonitoring)

/*!
 @property subjectAreaChangeMonitoringEnabled
 @abstract
    Indicates whether the receiver should monitor the subject area for changes.
 
 @discussion
    The value of this property is a BOOL indicating whether the receiver should monitor the video subject area for changes, such as lighting changes, substantial movement, etc. If subject area change monitoring is enabled, the receiver sends an AVCaptureDeviceSubjectAreaDidChangeNotification whenever it detects a change to the subject area, at which time an interested client may wish to re-focus, adjust exposure, white balance, etc. The receiver must be locked for configuration using lockForConfiguration: before clients can set the value of this property.
 */
@property(nonatomic, getter=isSubjectAreaChangeMonitoringEnabled) BOOL subjectAreaChangeMonitoringEnabled API_AVAILABLE(ios(5.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

@end


API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDevice (AVCaptureDeviceLowLightBoost)

/*!
 @property lowLightBoostSupported
 @abstract
    Indicates whether the receiver supports boosting images in low light conditions.
 
 @discussion
    The receiver's automaticallyEnablesLowLightBoostWhenAvailable property can only be set if this property returns YES.
 */
@property(nonatomic, readonly, getter=isLowLightBoostSupported) BOOL lowLightBoostSupported API_AVAILABLE(ios(6.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @property lowLightBoostEnabled
 @abstract
    Indicates whether the receiver's low light boost feature is enabled.
 
 @discussion
    The value of this property is a BOOL indicating whether the receiver is currently enhancing images to improve quality due to low light conditions. When -isLowLightBoostEnabled returns YES, the receiver has switched into a special mode in which more light can be perceived in images. This property is key-value observable.
 */
@property(nonatomic, readonly, getter=isLowLightBoostEnabled) BOOL lowLightBoostEnabled API_AVAILABLE(ios(6.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @property automaticallyEnablesLowLightBoostWhenAvailable
 @abstract
    Indicates whether the receiver should automatically switch to low light boost mode when necessary.
 
 @discussion
    On a receiver where -isLowLightBoostSupported returns YES, a special low light boost mode may be engaged to improve image quality. When the automaticallyEnablesLowLightBoostWhenAvailable property is set to YES, the receiver switches at its discretion to a special boost mode under low light, and back to normal operation when the scene becomes sufficiently lit. An AVCaptureDevice that supports this feature may only engage boost mode for certain source formats or resolutions. Clients may observe changes to the lowLightBoostEnabled property to know when the mode has engaged. The switch between normal operation and low light boost mode may drop one or more video frames. The default value is NO. Setting this property throws an NSInvalidArgumentException if -isLowLightBoostSupported returns NO. The receiver must be locked for configuration using lockForConfiguration: before clients can set this method, otherwise an NSGenericException is thrown.
 */
@property(nonatomic) BOOL automaticallyEnablesLowLightBoostWhenAvailable API_AVAILABLE(ios(6.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

@end


API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDevice (AVCaptureDeviceVideoZoom)

/*!
 @property videoZoomFactor
 @abstract
    Controls zoom level of image outputs
 
 @discussion
    Applies a centered crop for all image outputs, scaling as necessary to maintain output dimensions. Minimum value of 1.0 yields full field of view, increasing values will increase magnification, up to a maximum value specified in the activeFormat's videoMaxZoomFactor property. Modifying the zoom factor will cancel any active rampToVideoZoomFactor:withRate:, and snap directly to the assigned value. Assigning values outside the acceptable range will generate an NSRangeException. Clients can key value observe the value of this property. When depth data delivery is enabled, changing the zoom factor sets the videoZoomFactor to the nearest supportedVideoZoomFactor from -[AVCaptureDeviceFormat supportedVideoZoomFactorsForDepthDataDelivery] with a disruptive reconfiguration of the capture render pipeline.
 
    -setVideoZoomFactor: throws an NSGenericException if called without first obtaining exclusive access to the receiver using lockForConfiguration:.
 
 @seealso -[AVCaptureDeviceFormat videoMaxZoomFactor], -[AVCaptureDeviceFormat videoZoomFactorUpscaleThreshold], -[AVCaptureDevice minAvailableVideoZoomFactor], -[AVCaptureDevice maxAvailableVideoZoomFactor],  -[AVCaptureDeviceFormat supportedVideoZoomFactorsForDepthDataDelivery], -[AVCaptureDeviceFormat videoMinZoomFactorForCenterStage] and -[AVCaptureDeviceFormat videoMaxZoomFactorForCenterStage]
 */
@property(nonatomic) CGFloat videoZoomFactor API_AVAILABLE(ios(7.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @method rampToVideoZoomFactor:withRate:
 @abstract
    Provides smooth changes in zoom factor.
 
 @discussion
    This method provides a change in zoom by compounding magnification at the specified rate over time. Although the zoom factor will grow exponentially, this yields a visually linear zoom in the image over time.
 
    The zoom transition will stop at the specified factor, which must be in the valid range for videoZoomFactor. Assignments to videoZoomFactor while a ramp is in progress will cancel the ramp and snap to the assigned value.
 
    The zoom factor is continuously scaled by pow(2,rate * time). A rate of 0 causes no change in zoom factor, equivalent to calling cancelVideoZoomRamp. A rate of 1 will cause the magnification to double every second (or halve every second if zooming out), and similarly larger or smaller values will zoom faster or slower respectively. Only the absolute value of the rate is significant--sign is corrected for the direction of the target. Changes in rate will be smoothed by an internal acceleration limit.
 
    When depth data delivery is enabled, -rampToVideoZoomFactor:withRate: sets the videoZoomFactor to the nearest supportedVideoZoomFactor from -[AVCaptureDeviceFormat supportedVideoZoomFactorsForDepthDataDelivery] with a disruptive reconfiguration of the capture render pipeline.
 
    -rampToVideoZoomFactor:withRate: throws an NSGenericException if called without first obtaining exclusive access to the receiver using lockForConfiguration:.
 */
- (void)rampToVideoZoomFactor:(CGFloat)factor withRate:(float)rate API_AVAILABLE(ios(7.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @property rampingVideoZoom
 @abstract
    Indicates if the zoom factor is transitioning to a value set by rampToVideoZoomFactor:withRate:
 
 @discussion
    Clients can observe this value to determine when a ramp begins or completes.
 */
@property(nonatomic, readonly, getter=isRampingVideoZoom) BOOL rampingVideoZoom API_AVAILABLE(ios(7.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @method cancelVideoZoomRamp
 @abstract
    Eases out of any video zoom transitions initiated by rampToVideoZoomFactor:withRate:
 
 @discussion
    This method is equivalent to calling rampToVideoZoomFactor:withRate: using the current zoom factor target and a rate of 0. This allows a smooth stop to any changes in zoom which were in progress.
 
    -cancelVideoZoomRamp: throws an NSGenericException if called without first obtaining exclusive access to the receiver using lockForConfiguration:.
 */
- (void)cancelVideoZoomRamp API_AVAILABLE(ios(7.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @property dualCameraSwitchOverVideoZoomFactor
 @abstract
    The video zoom factor at or above which a DualCamera can select between its wide angle camera and its telephoto camera.
 
 @discussion
    This is the zoom factor at which the wide angle camera's field of view matches telephoto camera's full field of view. On non-DualCamera devices this will return 1.0. As of iOS 13.0, this API has been deprecated in favor of virtualDeviceSwitchOverVideoZoomFactors.
 */
@property(atomic, readonly) CGFloat dualCameraSwitchOverVideoZoomFactor API_DEPRECATED_WITH_REPLACEMENT("virtualDeviceSwitchOverVideoZoomFactors", ios(11.0, 13.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(tvos);

/*!
 @property displayVideoZoomFactorMultiplier
 @abstract
    A multiplier that can be used with the receiver's videoZoomFactor property for displaying a video zoom factor in a user interface.
 
 @discussion
    In some system user interfaces, like the macOS Video Effects Menu, the video zoom factor value is displayed in a way most appropriate for visual representation and might differ from the videoZoomFactor property value on the receiver by a fixed ratio. For example, if the videoZoomFactor property value is 1.0 and the displayVideoZoomFactorMultiplier property value is 0.5, then multiplying 1.0 and 0.5 produces 0.5 which can be displayed in the UI. Client applications can key value observe this property to update the display video zoom factor values in their UI to stay consistent with Apple's system UIs.
  */
@property(nonatomic, readonly) CGFloat displayVideoZoomFactorMultiplier API_AVAILABLE(macos(14.0), ios(18.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(watchos, visionos);

@end


/*!
 @enum AVAuthorizationStatus
 @abstract
    Constants indicating the client's authorization to the underlying hardware supporting a media type.
 
 @constant AVAuthorizationStatusNotDetermined
    Indicates that the user has not yet made a choice regarding whether the client can access the hardware.
 @constant AVAuthorizationStatusRestricted
    The client is not authorized to access the hardware for the media type. The user cannot change the client's status, possibly due to active restrictions such as parental controls being in place.
 @constant AVAuthorizationStatusDenied
    The user explicitly denied access to the hardware supporting a media type for the client.
 @constant AVAuthorizationStatusAuthorized
    The client is authorized to access the hardware supporting a media type.
 */
typedef NS_ENUM(NSInteger, AVAuthorizationStatus) {
    AVAuthorizationStatusNotDetermined = 0,
    AVAuthorizationStatusRestricted    = 1,
    AVAuthorizationStatusDenied        = 2,
    AVAuthorizationStatusAuthorized    = 3,
} API_AVAILABLE(macos(10.14), ios(7.0), macCatalyst(14.0), tvos(17.0), visionos(1.0)) API_UNAVAILABLE(watchos);


API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0), tvos(17.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface AVCaptureDevice (AVCaptureDeviceAuthorization)

/*!
 @method authorizationStatusForMediaType:
 @abstract
    Returns the client's authorization status for accessing the underlying hardware that supports a given media type.
 
 @param mediaType
    The media type, either AVMediaTypeVideo or AVMediaTypeAudio
 @result
    The authorization status of the client
 
 @discussion
    This method returns the AVAuthorizationStatus of the client for accessing the underlying hardware supporting the media type. Media type constants are defined in AVMediaFormat.h. If any media type other than AVMediaTypeVideo or AVMediaTypeAudio is supplied, an NSInvalidArgumentException will be thrown. If the status is AVAuthorizationStatusNotDetermined, you may use the +requestAccessForMediaType:completionHandler: method to request access by prompting the user.
 */
+ (AVAuthorizationStatus)authorizationStatusForMediaType:(AVMediaType)mediaType API_AVAILABLE(macos(10.14), ios(7.0), macCatalyst(14.0), tvos(17.0), visionos(1.0));

/*!
 @method requestAccessForMediaType:completionHandler:
 @abstract
    Requests access to the underlying hardware for the media type, showing a dialog to the user if necessary.
 
 @param mediaType
    The media type, either AVMediaTypeVideo or AVMediaTypeAudio
 @param handler
    A block called with the result of requesting access
 
 @discussion
    Use this function to request access to the hardware for a given media type. Media type constants are defined in AVMediaFormat.h. If any media type other than AVMediaTypeVideo or AVMediaTypeAudio is supplied, an NSInvalidArgumentException will be thrown.
 
    This call will not block while the user is being asked for access, allowing the client to continue running. Until access has been granted, any AVCaptureDevices for the media type will vend silent audio samples or black video frames. The user is only asked for permission the first time the client requests access. Later calls use the permission granted by the user.
 
    Note that the authorization dialog will automatically be shown if the status is AVAuthorizationStatusNotDetermined when creating an AVCaptureDeviceInput.
 
    Invoking this method with AVMediaTypeAudio is equivalent to calling -[AVAudioSession requestRecordPermission:].

    The completion handler is called on an arbitrary dispatch queue. It is the client's responsibility to ensure that any UIKit-related updates are called on the main queue or main thread as a result.
 */
+ (void)requestAccessForMediaType:(AVMediaType)mediaType completionHandler:(void (^)(BOOL granted))handler API_AVAILABLE(macos(10.14), ios(7.0), macCatalyst(14.0), tvos(17.0), visionos(1.0));

@end


/*!
 @typedef
 @abstract
    A constant that is used to specify the transport controls' speed.
 */
typedef float AVCaptureDeviceTransportControlsSpeed API_AVAILABLE(macos(10.7)) API_UNAVAILABLE(ios, macCatalyst, watchos, tvos, visionos);


/*!
 @enum AVCaptureDeviceTransportControlsPlaybackMode
 @abstract
    Constants indicating the transport controls' current mode of play back, if it has one.
 
 @constant AVCaptureDeviceTransportControlsNotPlayingMode
    Indicates that the tape transport is not threaded through the play head.
 @constant AVCaptureDeviceTransportControlsPlayingMode
    Indicates that the tape transport is threaded through the play head.
 */
typedef NS_ENUM(NSInteger, AVCaptureDeviceTransportControlsPlaybackMode) {
    AVCaptureDeviceTransportControlsNotPlayingMode = 0,
    AVCaptureDeviceTransportControlsPlayingMode    = 1,
} API_AVAILABLE(macos(10.7)) API_UNAVAILABLE(ios, macCatalyst, watchos, tvos, visionos);


API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDevice (AVCaptureDeviceTransportControls)

/*!
 @property transportControlsSupported
 @abstract
    Returns whether the receiver supports transport control commands.
 
 @discussion
    For devices with transport controls, such as AVC tape-based camcorders or pro capture devices with RS422 deck control, the value of this property is YES. If transport controls are not supported, none of the associated transport control methods and properties are available on the receiver.
 */
@property(nonatomic, readonly) BOOL transportControlsSupported API_UNAVAILABLE(ios, macCatalyst, watchos, tvos, visionos);

/*!
 @property transportControlsPlaybackMode
 @abstract
    Returns the receiver's current playback mode.
 
 @discussion
    For devices that support transport control, this property may be queried to discover the current playback mode.
 */
@property(nonatomic, readonly) AVCaptureDeviceTransportControlsPlaybackMode transportControlsPlaybackMode API_UNAVAILABLE(ios, macCatalyst, watchos, tvos, visionos);

/*!
 @property transportControlsSpeed
 @abstract
    Returns the receiver's current playback speed as a floating point value.
 
 @discussion
    For devices that support transport control, this property may be queried to discover the current playback speed of the deck.
    0.0 -> stopped.
    1.0 -> forward at normal speed.
    -1.0-> reverse at normal speed.
    2.0 -> forward at 2x normal speed.
    etc.
 */
@property(nonatomic, readonly) AVCaptureDeviceTransportControlsSpeed transportControlsSpeed API_UNAVAILABLE(ios, macCatalyst, watchos, tvos, visionos);

/*!
 @method setTransportControlsPlaybackMode:speed:
 @abstract
    Sets both the transport controls playback mode and speed in a single method.
 
 @param mode
    A AVCaptureDeviceTransportControlsPlaybackMode indicating whether the deck should be put into play mode.
 @param speed
    A AVCaptureDeviceTransportControlsSpeed indicating the speed at which to wind or play the tape.
 
 @discussion
    A method for setting the receiver's transport controls playback mode and speed. The receiver must be locked for configuration using lockForConfiguration: before clients can set this method, otherwise an NSGenericException is thrown.
 */
- (void)setTransportControlsPlaybackMode:(AVCaptureDeviceTransportControlsPlaybackMode)mode speed:(AVCaptureDeviceTransportControlsSpeed)speed API_UNAVAILABLE(ios, macCatalyst, watchos, tvos, visionos);

@end


API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDevice (AVCaptureDeviceHighDynamicRangeSupport)

/*!
 @property automaticallyAdjustsVideoHDREnabled
 @abstract
    Indicates whether the receiver is allowed to turn high dynamic range streaming on or off.
 
 @discussion
    The value of this property is a BOOL indicating whether the receiver is free to turn high dynamic range streaming on or off. This property defaults to YES. When automaticallyAdjustsVideoHDREnabled, the AVCaptureDevice turns videoHDR on automatically if it's a good fit for the activeFormat. -setAutomaticallyAdjustsVideoHDREnabled: throws an NSGenericException if called without first obtaining exclusive access to the receiver using -lockForConfiguration:. Clients can key-value observe videoHDREnabled to know when the receiver has automatically changed the value.
 */
@property(nonatomic) BOOL automaticallyAdjustsVideoHDREnabled API_AVAILABLE(ios(8.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @property videoHDREnabled
 @abstract
    Indicates whether the receiver's streaming high dynamic range feature is enabled. See AVCaptureDeviceFormat.isVideoHDRSupported.
 
 @discussion
    The value of this property is a BOOL indicating whether the receiver is currently streaming high dynamic range video buffers, also known as Extended Dynamic Range (EDR). The value of this property is ignored when device.activeColorSpace is HLG BT2020 color space since HDR is effectively always on and can't be disabled. The property may only be set if you first set automaticallyAdjustsVideoHDREnabled to NO, otherwise an NSGenericException is thrown. videoHDREnabled may only be set to YES if the receiver's activeFormat.isVideoHDRSupported property returns YES, otherwise an NSGenericException is thrown. This property may be key-value observed.
 
    Note that setting this property may cause a lengthy reconfiguration of the receiver, similar to setting a new active format or AVCaptureSession sessionPreset. If you are setting either the active format or the AVCaptureSession's sessionPreset AND this property, you should bracket these operations with [session beginConfiguration] and [session commitConfiguration] to minimize reconfiguration time.
 */
@property(nonatomic, getter=isVideoHDREnabled) BOOL videoHDREnabled API_AVAILABLE(ios(8.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

@end

/// Constants indicating active or supported video color space.
typedef NS_ENUM(NSInteger, AVCaptureColorSpace) {
    /// The sRGB color space ( https://www.w3.org/Graphics/Color/srgb ).
    AVCaptureColorSpace_sRGB       = 0,
    /// The P3 D65 wide color space which uses Illuminant D65 as the white point.
    AVCaptureColorSpace_P3_D65     = 1,
    /// The BT2020 wide color space which uses Illuminant D65 as the white point and Hybrid Log-Gamma as the transfer function.
    AVCaptureColorSpace_HLG_BT2020 API_AVAILABLE(ios(14.1), macCatalyst(14.1), tvos(17.0)) API_UNAVAILABLE(macos, visionos) = 2,
    /// The Apple Log Color space, which uses BT2020 as the color primaries, and an Apple defined Log curve as a transfer function. When you set this as the active color space on an ``AVCaptureDevice``, any ``AVCapturePhotoOutput`` or ``AVCaptureStillImageOutput`` connected to the same ``AVCaptureDevice`` is made inactive (its ``AVCaptureConnection/active`` property returns `false`).
    AVCaptureColorSpace_AppleLog API_AVAILABLE(ios(17.0), macCatalyst(17.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) = 3,
    /// The Apple Log 2 Color space, which uses Apple Gamut as the color primaries, and an Apple defined Log curve as a transfer function. When you set this as the active color space on an ``AVCaptureDevice``, any ``AVCapturePhotoOutput`` or ``AVCaptureStillImageOutput`` connected to the same ``AVCaptureDevice`` is made inactive (its ``AVCaptureConnection/active`` property returns `false`).
    AVCaptureColorSpace_AppleLog2 API_AVAILABLE(ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(macos, visionos) = 4,
} API_AVAILABLE(macos(10.15), ios(10.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDevice (AVCaptureDeviceColorSpaceSupport)

/*!
 @property activeColorSpace
 @abstract
    Indicates the receiver's current active color space.
 
 @discussion
    By default, an AVCaptureDevice attached to an AVCaptureSession is automatically configured for wide color by the AVCaptureSession (see AVCaptureSession automaticallyConfiguresCaptureDeviceForWideColor). You may also set the activeColorSpace manually. To prevent the AVCaptureSession from undoing your work, remember to set AVCaptureSession's automaticallyConfiguresCaptureDeviceForWideColor property to NO. Changing the receiver's activeColorSpace while the session is running requires a disruptive reconfiguration of the capture render pipeline. Movie captures in progress will be ended immediately; unfulfilled photo requests will be aborted; video preview will temporarily freeze. -setActiveColorSpace: throws an NSGenericException if called without first obtaining exclusive access to the receiver using -lockForConfiguration:.
 */
@property(nonatomic) AVCaptureColorSpace activeColorSpace API_AVAILABLE(macos(10.15), ios(10.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos);

@end


API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDevice (AVCaptureDeviceDepthSupport)

/*!
 @property activeDepthDataFormat
 @abstract
    The currently active depth data format of the receiver.

 @discussion
    This property can be used to get or set the device's currently active depth data format. -setActiveDepthDataFormat: throws an NSInvalidArgumentException if set to a format not present in the activeFormat's -supportedDepthDataFormats array. -setActiveDepthDataFormat: throws an NSGenericException if called without first obtaining exclusive access to the receiver using lockForConfiguration:. Clients can observe automatic changes to the receiver's activeDepthDataFormat by key value observing this property. On devices where depth data is not supported, this property returns nil.
 
    The frame rate of depth data may not be set directly. Depth data frame rate is synchronized to the device's activeMin/MaxFrameDurations. It may match the device's current frame rate, or lower, if depth data cannot be produced fast enough for the active video frame rate.
 
    Delivery of depth data to a AVCaptureDepthDataOutput may increase the system load, resulting in a reduced video frame rate for thermal sustainability.
 */
@property(nonatomic, retain, nullable) AVCaptureDeviceFormat *activeDepthDataFormat API_AVAILABLE(ios(11.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @property activeDepthDataMinFrameDuration
 @abstract
    A property indicating the receiver's current active minimum depth data frame duration (the reciprocal of its maximum depth data frame rate).

 @discussion
    This property may be used to set an upper limit to the frame rate at which depth data is produced. Lowering the depth data frame rate typically lowers power consumption which will increase the time the camera can run before an elevated system pressure state is reached.

    Setting this property to kCMTimeInvalid resets it to the active depth data format's default min frame duration. Setting this property to kCMTimePositiveInfinity results in a depth data frame rate of 0.

    The activeDepthDataMinFrameDuration gets reset whenever either the active video format or the active depth data format changes.

    -setActiveDepthDataMinFrameDuration: throws an NSRangeException if set to a value that is outside of the active depth data format's supported frame rate range.
    -setActiveDepthDataMinFrameDuration: throws an NSGenericException if called without first obtaining exclusive access to the receiver using lockForConfiguration:.
 */
@property(nonatomic) CMTime activeDepthDataMinFrameDuration API_AVAILABLE(ios(12.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @property minAvailableVideoZoomFactor
 @abstract
    Indicates the minimum zoom factor available for the AVCaptureDevice's videoZoomFactor property.
 
 @discussion
    On non-virtual devices the minAvailableVideoZoomFactor is always 1.0. If the device's videoZoomFactor property is assigned a value smaller than 1.0, an NSRangeException is thrown.
    On a virtual device the minAvailableVideoZoomFactor can change when the device is delivering depth data to one or more outputs (see -[AVCaptureDeviceFormat supportedVideoZoomFactorsForDepthDataDelivery]). When depth data delivery is enabled, allowed zoom factor values are governed by -[AVCaptureDeviceFormat supportedVideoZoomFactorsForDepthDataDelivery] and this contains the absolute minimum zoom of all allowed zoom factors.
    Setting the videoZoomFactor to a value greater than or equal to 1.0, but lower than minAvailableVideoZoomFactor results in the value being clamped to the minAvailableVideoZoomFactor. Clients can key value observe the value of this property.
 */
@property(nonatomic, readonly) CGFloat minAvailableVideoZoomFactor API_AVAILABLE(ios(11.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @property maxAvailableVideoZoomFactor
 @abstract
    Indicates the maximum zoom factor available for the AVCaptureDevice's videoZoomFactor property.
 
 @discussion
    On non-virtual devices the maxAvailableVideoZoomFactor is always equal to the activeFormat.videoMaxZoomFactor. If the device's videoZoomFactor property is assigned a value greater than activeFormat.videoMaxZoomFactor, an NSRangeException is thrown.
    On a virtual device the maxAvailableVideoZoomFactor can change when the device is delivering depth data to one or more outputs (see -[AVCaptureDeviceFormat supportedVideoZoomFactorsForDepthDataDelivery]). When depth data delivery is enabled, allowed zoom factor values are governed by -[AVCaptureDeviceFormat supportedVideoZoomFactorsForDepthDataDelivery] and this contains the absolute maximum zoom of all allowed zoom factors.
    Setting the videoZoomFactor to a value less than or equal to activeFormat.videoMaxZoomFactor, but greater than maxAvailableVideoZoomFactor results in the value being clamped to the maxAvailableVideoZoomFactor. Clients can key value observe the value of this property.
 */
@property(nonatomic, readonly) CGFloat maxAvailableVideoZoomFactor API_AVAILABLE(ios(11.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

@end


API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDevice (AVCaptureDeviceGeometricDistortionCorrection)

/*!
 @property geometricDistortionCorrectionSupported
 @abstract
    Indicates that geometric distortion correction is supported by the receiver.

 @discussion
    Some AVCaptureDevices benefit from geometric distortion correction (GDC), such as devices with a very wide field of view. GDC lessens the fisheye effect at the outer edge of the frame at the cost of losing a small amount of vertical and horizontal field of view. When GDC is enabled on the AVCaptureDevice (see geometricDistortionCorrectionEnabled), the corrected image is upscaled to the original image size when needed.  With respect to the AVCaptureDevice.videoZoomFactor API, the full viewable field of view is always represented with a videoZoomFactor of 1.0. Thus, when GDC is enabled, the AVCaptureDevice.activeFormat's field of view at videoZoomFactor = 1.0 will be different than when GDC is disabled. The smaller field of view is reported through the activeFormat's geometricDistortionCorrectedVideoFieldOfView property. Beware though that RAW photo captures never have GDC applied, regardless of the value of AVCaptureDevice.geometricDistortionCorrectionEnabled.
 */
@property(nonatomic, readonly, getter=isGeometricDistortionCorrectionSupported) BOOL geometricDistortionCorrectionSupported API_AVAILABLE(ios(13.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

/*!
 @property geometricDistortionCorrectionEnabled
 @abstract
    Indicates whether geometric distortion correction is enabled by the receiver.

 @discussion
    Where supported, the default value is YES. The receiver must be locked for configuration using lockForConfiguration: before clients can set this method, otherwise an NSGenericException is thrown.

    In the case of ProRes RAW, when geometricDistortionCorrectionEnabled is YES, GDC is applied to your outputs in different ways:
    - It is always applied to AVCaptureVideoPreviewLayer.
    - It is applied to AVCaptureVideoDataOutput only if deliversPreviewSizedOutputBuffers is set to YES.
    - It is never applied to AVCaptureMovieFileOutput.

    When GDC is enabled, AVCaptureVideoDataOutput buffers contain GDC metadata attachments, and AVCaptureMovieFileOutput movies contain GDC metadata which an application supporting ProRes RAW can optionally apply at playback time using the ProRes RAW SDK. To learn more about the ProRes RAW SDK, refer to the Apple ProRes and ProRes RAW Authorized Products article at https://support.apple.com/en-us/118584.
 */
@property(nonatomic, getter=isGeometricDistortionCorrectionEnabled) BOOL geometricDistortionCorrectionEnabled API_AVAILABLE(ios(13.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

@end


API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDevice (AVCaptureDeviceCalibration)

/*!
 @method extrinsicMatrixFromDevice:toDevice:
 @abstract
    An NSData containing the relative extrinsic matrix from one AVCaptureDevice to another.
 @param fromDevice
    The AVCaptureDevice to use as the source. Must be non nil or an NSInvalidArgumentException is thrown.
 @param toDevice
    The AVCaptureDevice to use as the destination. Must be non nil or an NSInvalidArgumentException is thrown.
 
 @discussion
    The extrinsic matrix consists of a unitless 3x3 rotation matrix (R) on the left and a translation (t) 3x1 column vector on the right. The translation vector's units are millimeters. The extrinsics of the "toDevice" camera are expressed with respect to a reference camera "fromDevice". If X_from is a 3D point in "fromCamera"'s coordinate system, then it can be projected into "toCamera"'s coordinate system with X_to = [R | t] * X_from. Note that a matrix_float4x3 matrix is column major with 3 rows and 4 columns. The extrinsicMatrix is only provided for physical cameras for which factory calibrations exist. Virtual device cameras return nil.
               /                       \
       /   \   | r1,1  r1,2  r1,3 | t1 |
       |R|t| = | r2,1  r2,2  r2,3 | t2 |
       \   /   | r3,1  r3,2  r3,3 | t3 |
               \                       /

    Note that if you enable video stabilization (see AVCaptureConnection.preferredVideoStabilizationMode), the pixels in stabilized video frames no longer match the relative extrinsicMatrix from one device to another due to warping. The extrinsicMatrix and camera intrinsics should only be used when video stabilization is disabled.
 */
+ (nullable NSData *)extrinsicMatrixFromDevice:(AVCaptureDevice *)fromDevice toDevice:(AVCaptureDevice *)toDevice API_AVAILABLE(ios(13.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

@end


API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDevice (AVCaptureDeviceCenterStage)

/*!
 @enum AVCaptureCenterStageControlMode
 @abstract
    Constants indicating the current Center Stage control mode.
 
 @constant AVCaptureCenterStageControlModeUser
    Indicates that the application is unaware of the Center Stage feature. Its enablement is entirely under user control in Control Center.
 @constant AVCaptureCenterStageControlModeApp
    Indicates that the application controls the Center Stage feature, disallowing input from the user in Control Center.
 @constant AVCaptureCenterStageControlModeCooperative
    Indicates that both the user and application cooperatively share control of the Center Stage feature.
 */
typedef NS_ENUM(NSInteger, AVCaptureCenterStageControlMode) {
    AVCaptureCenterStageControlModeUser          = 0,
    AVCaptureCenterStageControlModeApp           = 1,
    AVCaptureCenterStageControlModeCooperative   = 2,
} API_AVAILABLE(macos(12.3), ios(14.5), macCatalyst(14.5), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @property centerStageControlMode
 @abstract
    A class property indicating the current mode of Center Stage control (user, app, or cooperative).
 
 @discussion
    This class property determines how the Center Stage feature is controlled. When set to the default value of AVCaptureCenterStageControlModeUser, centerStageEnabled may not be set programmatically and throws an NSInvalidArgumentException. In User mode, the feature may only be set by the user in Control Center. If you wish to take Center Stage control away from the user and exclusively enable / disable it programmatically, set this property to AVCaptureCenterStageControlModeApp. When under exclusive app control, Center Stage user control is disallowed (for instance, the toggle is grayed out in Control Center). If you wish to take control of Center Stage, but also cooperate with the user by listening for and appropriately reacting to their changes to the centerStageEnabled property, set this property to AVCaptureCenterStageControlModeCooperative. Note that in this mode, the onus is on you, the app developer, to honor user intent and conform your AVCaptureSession configuration to make Center Stage active (see the AVCaptureDevice instance property centerStageActive). In cooperative mode, the centerStageEnabled property may change at any time (such as when the user enables / disables the feature in Control Center).
 */
@property(class) AVCaptureCenterStageControlMode centerStageControlMode API_AVAILABLE(macos(12.3), ios(14.5), macCatalyst(14.5), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @property centerStageEnabled
 @abstract
    A class property indicating whether the Center Stage feature is currently enabled or disabled (such as in Control Center or programmatically via your app).
 
 @discussion
    This property may only be set if centerStageControlMode is AVCaptureCenterStageControlModeApp or AVCaptureCenterStageControlModeCooperative, and otherwise throws an NSInvalidArgumentException. When centerStageControlMode is AVCaptureCenterStageControlModeUser or AVCaptureCenterStageControlModeCooperative, this property may change according to user desire (such as enabling / disabling the feature in Control Center), so you should key-value observe it.
 */
@property(class, getter=isCenterStageEnabled) BOOL centerStageEnabled API_AVAILABLE(macos(12.3), ios(14.5), macCatalyst(14.5), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @property centerStageActive
 @abstract
    Indicates whether Center Stage is currently active on a particular AVCaptureDevice.
 
 @discussion
    This readonly property returns YES when Center Stage is currently active on the receiver. When active, the camera automatically adjusts to keep people optimally framed within the field of view. The field of view may pan, tighten or widen as needed. Certain restrictions come into play when Center Stage is active:
        - The device's minAvailableVideoZoomFactor and maxAvailableVideoZoomFactor become restricted (see AVCaptureDeviceFormat's videoMinZoomFactorForCenterStage and videoMaxZoomFactorForCenterStage).
        - The device's activeVideoMinFrameDuration and activeVideoMaxFrameDuration are limited (see AVCaptureDeviceFormat's videoFrameRateRangeForCenterStage).
    Center Stage may be enabled via user control or application control, depending on the current +AVCaptureDevice.centerStageControlMode. When +AVCaptureDevice.centerStageEnabled is YES, a particular AVCaptureDevice instance may return YES for this property, depending whether it supports the feature in its current configuration. Some device features are mutually exclusive to Center Stage:
        - If depth data delivery is enabled on any output, such as AVCaptureDepthDataOutput, or -AVCapturePhotoOutput.depthDataDeliveryEnabled, Center Stage is deactivated.
        - If geometricDistortionCorrectionSupported is YES, geometricDistortionCorrectionEnabled must also be YES, or Center Stage is deactivated.
    This property is key-value observable.
 */
@property(nonatomic, readonly, getter=isCenterStageActive) BOOL centerStageActive API_AVAILABLE(macos(12.3), ios(14.5), macCatalyst(14.5), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @property centerStageRectOfInterestSupported
 @abstract
    Indicates whether the device supports the Center Stage Rect of Interest feature.
 
 @discussion
    This property returns YES if the device supports Center Stage Rect of Interest.
 */
@property(nonatomic, readonly, getter=isCenterStageRectOfInterestSupported) BOOL centerStageRectOfInterestSupported API_UNAVAILABLE(macos, ios, macCatalyst) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

/*!
 @property centerStageRectOfInterest
 @abstract
    Specifies the effective region within the output pixel buffer that will be used to perform Center Stage framing.
 
 @discussion
    Applications that wish to apply additional processing (such as cropping) on top of Center Stage's output can use this property to guide Center Stage's framing.
 
    The rectangle's origin is top left and is relative to the coordinate space of the output pixel buffer. The default value of this property is the value CGRectMake(0, 0, 1, 1), where {0,0} represents the top left of the picture area, and {1,1} represents the bottom right on an unrotated picture. This rectangle of interest is applied prior to rotation, mirroring or scaling.
 
    Pixels outside of this rectangle of interest will be blackened out.
 
    Setting this property has no impact on objects specified in the metadata output.
 
    -setCenterStageRectOfInterest: throws an NSGenericException if called without first obtaining exclusive access to the receiver using -lockForConfiguration:. -setCenterStageRectOfInterest: throws an NSInvalidArgumentException if none of the AVCaptureDeviceFormats supported by the receiver support CenterStage. -setCenterStageRectOfInterest: throws an NSInvalidArgumentException if +centerStageEnabled is NO on the AVCaptureDevice class. -setCenterStageRectOfInterest: throws an NSInvalidArgumentException if the provided rectOfInterest goes outside the normalized (0-1) coordinate space.
 */
@property(nonatomic) CGRect centerStageRectOfInterest API_AVAILABLE(macos(13.3), ios(16.4), macCatalyst(16.4)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

@end


API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDevice (AVCaptureDevicePortraitEffect)

/*!
 @property portraitEffectEnabled
 @abstract
    A class property indicating whether the Portrait Effect feature is currently enabled in Control Center.
 
 @discussion
    This property changes to reflect the Portrait Effect state in Control Center. It is key-value observable. On iOS, Portrait Effect only applies to video conferencing apps by default (apps that use "voip" as one of their UIBackgroundModes). Non video conferencing apps may opt in for the Portrait Effect by adding the following key to their Info.plist:
        <key>NSCameraPortraitEffectEnabled</key>
        <true/>
 */
@property(class, readonly, getter=isPortraitEffectEnabled) BOOL portraitEffectEnabled API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @property portraitEffectActive
 @abstract
    Indicates whether Portrait Effect is currently active for a particular AVCaptureDevice.
 
 @discussion
    This readonly property returns YES when Portrait Effect is currently active on the receiver. When active, the device blurs the background, simulating a shallow depth of field effect. Certain restrictions come into play when Portrait Effect is active:
        - The device's activeVideoMinFrameDuration and activeVideoMaxFrameDuration are limited (see AVCaptureDeviceFormat's videoFrameRateRangeForPortraitEffect).
    Note that when +AVCaptureDevice.portraitEffectEnabled is YES, a particular AVCaptureDevice instance may return YES for this property, depending whether it supports the feature in its current configuration.
    This property is key-value observable.
 */
@property(nonatomic, readonly, getter=isPortraitEffectActive) BOOL portraitEffectActive API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

@end


API_AVAILABLE(macos(14.0), ios(17.0), macCatalyst(17.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDevice (AVCaptureDeviceReactionEffects)

/*!
 @property reactionEffectsEnabled
 @abstract
    A class property indicating whether the application is suitable for reaction effects, either by automatic gesture detection, or by calls to -[AVCaptureDevice performEffectForReaction:]. Reactions are only rendered when the device's activeFormat.reactionEffectsSupported is also YES, which will be reflected by canPerformReactionEffects when the feature is both enabled and supported.
 
 @discussion
    On macOS, Reaction Effects are enabled by default for all applications. On iOS, Reaction Effects are enabled by default for video conferencing applications (apps that use "voip" as one of their UIBackgroundModes). Non video conferencing applications may opt in for Reaction Effects by adding the following key to their Info.plist:
        <key>NSCameraReactionEffectsEnabled</key>
        <true/>
 */
@property(class, readonly) BOOL reactionEffectsEnabled API_AVAILABLE(macos(14.0), ios(17.0), macCatalyst(17.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @property reactionEffectGesturesEnabled
 @abstract
    A class property indicating whether gesture detection will trigger reaction effects on the video stream. Gesture detection will only run when the device's activeFormat.reactionEffectsSupported is also YES, which will be reflected by canPerformReactionEffects.
 
 @discussion
    This property changes to reflect the Gestures state in Control Center. It is key-value observable. Clients can call performEffectForReaction: independently of whether gesture detection is enabled, reaction effects from either source will be intermixed.
    By default, gesture detection is enabled.  As of iOS 17.4 and macOS 14.4, applications can control the default value of this property by adding the following key to their Info.plist:
        <key>NSCameraReactionEffectGesturesEnabledDefault</key>
    A value of true enables gesture detection and a value of false disables it, until such time that the user makes their own selection in Control Center.
 */
@property(class, readonly) BOOL reactionEffectGesturesEnabled API_AVAILABLE(macos(14.0), ios(17.0), macCatalyst(17.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @property canPerformReactionEffects
 @abstract
    Indicates whether reactions can be performed on a particular AVCaptureDevice. This requires reactionEffectsEnabled to be YES, as well as using a AVCaptureDeviceFormat with reactionEffectsSupported.
 
 @discussion
    This readonly property returns YES when resources for reactions are available on the device instance. When YES, calls to performEffectForReaction: will render on the video feed, otherwise those calls are ignored. It is key-value observable.
 */
@property(nonatomic, readonly) BOOL canPerformReactionEffects API_AVAILABLE(macos(14.0), ios(17.0), macCatalyst(17.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @property availableReactionTypes
 @abstract
    Returns a list of reaction types which can be passed to performEffectForReaction.
 
 @discussion
    The list may differ between devices, or be affected by changes to active format, and can be key-value observed.
 */
@property(nonatomic, readonly) NSSet<AVCaptureReactionType> *availableReactionTypes API_AVAILABLE(macos(14.0), ios(17.0), macCatalyst(17.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @method performEffectForReaction:
 @abstract
    Triggers a specified reaction on the video stream.
 
 @param reactionType
    Indicates which reaction to perform.
 
 @discussion
    The entries in reactionEffectsInProgress may not reflect one-to-one against calls to this method. Depending on reaction style or resource limits, triggering multiple overlapping reactions of the same type may be coalesced into extending an existing reaction rather than overlaying a new one.
    
    The reactionType requested must be one of those listed in availableReactionTypes or an exception will be thrown. Performing a reaction when canPerformReactionEffects is NO is ignored, and VoIP applications are encouraged to transmit and display such reactions outside of the video feed.
 */
- (void)performEffectForReaction:(AVCaptureReactionType)reactionType NS_SWIFT_NAME(performEffect(for:)) API_AVAILABLE(macos(14.0), ios(17.0), macCatalyst(17.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @property reactionEffectsInProgress
 @abstract
    Contains an array of reaction effects that are currently being performed by the device, sorted by timestamp. If observing old and new values in the KVO callback, the reaction effects which are still running in the new array will have kCMTimeInvalid as their endTime property. Reaction effects which have ended will only be in the old array, and will have their endTime property set to the presentation time of the first frame where the reaction effect was no longer present.
 
 @discussion
    Reaction effects which are triggered by either a call to performEffectForReaction: or by the automatic gesture detection will be reflected in this array. It is key-value observable to be notified when reaction effects begin or end.
 */
@property(nonatomic, readonly) NSArray<AVCaptureReactionEffectState *> *reactionEffectsInProgress API_AVAILABLE(macos(14.0), ios(17.0), macCatalyst(17.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

@end


API_AVAILABLE(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDevice (AVCaptureDeviceBackgroundReplacement)

/*!
 @property backgroundReplacementEnabled
 @abstract
    A class property indicating whether the user has enabled the Background Replacement feature for this application.
 */
@property(class, readonly, getter=isBackgroundReplacementEnabled) BOOL backgroundReplacementEnabled API_AVAILABLE(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @property backgroundReplacementActive
 @abstract
    Indicates whether Background Replacement is currently active on a particular AVCaptureDevice.
 
 @discussion
    This property is key-value observable.
 */
@property(nonatomic, readonly, getter=isBackgroundReplacementActive) BOOL backgroundReplacementActive API_AVAILABLE(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

@end


API_AVAILABLE(macos(13.0), ios(16.0), macCatalyst(16.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDevice (AVCaptureDeviceContinuityCamera)

/*!
 @property continuityCamera
 @abstract
    A property that reports YES if the receiver is a Continuity Camera.
 
 @discussion
    Access this property to discover if the receiver is a Continuity Camera (external iPhone webcam).
*/
@property(nonatomic, readonly, getter=isContinuityCamera) BOOL continuityCamera API_AVAILABLE(macos(13.0), ios(16.0), macCatalyst(16.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

@end


API_AVAILABLE(macos(13.0), ios(16.0), macCatalyst(16.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDevice (AVCaptureDeviceDeskViewCamera)

/*!
 @property companionDeskViewCamera
 @abstract
    A reference to the Desk View Camera that is associated with and derived from this camera.
 
 @discussion
    The companionDeskViewCamera property allows you to discover if the receiver has a paired Desk View Camera which derives its desk framing from the receiver's ultra wide frame. In the presence of multiple Continuity Cameras, this property allows you to pair a particular Continuity Camera with its associated Desk View Camera.
*/
@property(nonatomic, readonly, nullable) AVCaptureDevice *companionDeskViewCamera API_AVAILABLE(macos(13.0), ios(16.0), macCatalyst(16.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

@end


API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDevice (AVCaptureMicrophoneMode)

/*!
 @enum AVCaptureMicrophoneMode
 @abstract
    Constants describing microphone filtering modes.

 @constant AVCaptureMicrophoneModeStandard
    Indicates that microphone audio is being processed with standard voice DSP.
 @constant AVCaptureMicrophoneModeWideSpectrum
    Indicates that microphone audio processing is minimized to capture all sounds in the room.
 @constant AVCaptureMicrophoneModeVoiceIsolation
    Indicates that microphone audio is being processed to isolate the voice and attenuate other signals.
 */
typedef NS_ENUM(NSInteger, AVCaptureMicrophoneMode) {
	AVCaptureMicrophoneModeStandard       = 0,
	AVCaptureMicrophoneModeWideSpectrum   = 1,
	AVCaptureMicrophoneModeVoiceIsolation = 2,
} NS_SWIFT_NAME(AVCaptureDevice.MicrophoneMode) API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @property preferredMicrophoneMode
 @abstract
    Indicates the microphone mode that has been selected by the user in Control Center.

 @discussion
    This readonly property returns the microphone mode selected by the user in Control Center. It is key-value observable.
 */
@property(class, readonly) AVCaptureMicrophoneMode preferredMicrophoneMode API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @property activeMicrophoneMode
 @abstract
    Indicates the currently active microphone mode.

 @discussion
    This readonly property returns the currently active microphone mode, which may differ from the preferredMicrophoneMode if the application's active audio route does not support the preferred microphone mode. This property is key-value observable.
 */
@property(class, readonly) AVCaptureMicrophoneMode activeMicrophoneMode API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

@end


API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDevice (AVCaptureSystemUserInterface)

/*!
 @enum AVCaptureSystemUserInterface
 @abstract
    Constants describing the system user interfaces available to +showSystemUserInterface:.
 
 @constant AVCaptureSystemUserInterfaceVideoEffects
    Indicates the system UI for enabling / disabling video effects.
 @constant AVCaptureSystemUserInterfaceMicrophoneModes
    Indicates the system UI for selecting microphone modes.
 */
typedef NS_ENUM(NSInteger, AVCaptureSystemUserInterface) {
    AVCaptureSystemUserInterfaceVideoEffects    = 1,
    AVCaptureSystemUserInterfaceMicrophoneModes = 2,
} NS_SWIFT_NAME(AVCaptureDevice.SystemUserInterface) API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @method showSystemUserInterface:
 @abstract
    Displays the system's user interface for video effects or microphone modes.
 
 @param systemUserInterface
    The system UI to show.
 
 @discussion
    This method allows the calling application to prompt the user to make changes to Video Effects (such as Center Stage or the Portrait Effect) or Microphone Modes. It brings up the system user interface and deep links to the appropriate module. This method is non-blocking. After presenting the desired system user interface, control returns immediately to the application.
 */
+ (void)showSystemUserInterface:(AVCaptureSystemUserInterface)systemUserInterface NS_SWIFT_NAME(showSystemUserInterface(_:)) API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

@end


/*!
 @group AVSpatialCaptureDiscomfortReason string constants

 @discussion
    The AVSpatialCaptureDiscomfortReason string constants are used to report the applicability of the current scene to create a comfortable viewing experience.
 */
typedef NSString *AVSpatialCaptureDiscomfortReason NS_TYPED_ENUM API_AVAILABLE(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @constant AVSpatialCaptureDiscomfortReasonNotEnoughLight
    The lighting of the current scene is not bright enough; the playback experience will likely be uncomfortable due to noise differences between the two cameras.
 */
AVF_EXPORT AVSpatialCaptureDiscomfortReason const AVSpatialCaptureDiscomfortReasonNotEnoughLight API_AVAILABLE(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @constant AVSpatialCaptureDiscomfortReasonSubjectTooClose
    The focus point of the current scene is too close; the playback experience will likely be uncomfortable due to the subject being closer than the minimum focus distance of one or both of the lenses.
 */
AVF_EXPORT AVSpatialCaptureDiscomfortReason const AVSpatialCaptureDiscomfortReasonSubjectTooClose API_AVAILABLE(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);


@interface AVCaptureDevice (AVCaptureDeviceSpatialCapture)

/*!
 @property spatialCaptureDiscomfortReasons
 @abstract
    Indicates whether or not the current environmental conditions are amenable to a spatial capture that is comfortable to view.
 
 @discussion
    This property can be monitored in order to determine the presentation of UI elements to inform the user that they should reframe their scene for a more pleasing spatial capture ("subject is too close", "scene is too dark").
 */
@property(nonatomic, readonly) NSSet<AVSpatialCaptureDiscomfortReason> *spatialCaptureDiscomfortReasons API_AVAILABLE(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);
@end

/// An informative status about the scene observed by the device.
///
/// Some features have certain requirements on the scene (lighting condition for Cinematic Video, for example) to produce optimal results; these ``AVCaptureSceneMonitoringStatus`` string constants are used to represent such scene statuses for a given feature.
typedef NSString *AVCaptureSceneMonitoringStatus NS_TYPED_ENUM API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// The light level of the current scene is insufficient for the current set of features to function optimally.
AVF_EXPORT AVCaptureSceneMonitoringStatus const AVCaptureSceneMonitoringStatusNotEnoughLight API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDevice (AVCaptureDeviceCinematicVideoCapture)

/// The current scene monitoring statuses related to Cinematic Video capture.
///
/// Monitor this property via key-value observation to present a UI informing the user that they should reframe their scene for a better Cinematic Video experience ("scene is too dark").
@property(nonatomic, readonly) NSSet<AVCaptureSceneMonitoringStatus> *cinematicVideoCaptureSceneMonitoringStatuses;

@end

/// String constants describing the different video aspect ratios you can configure for a particular device.
typedef NSString *AVCaptureAspectRatio NS_TYPED_ENUM NS_SWIFT_NAME(AVCaptureDevice.AspectRatio) API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, macCatalyst, tvos, visionos) API_UNAVAILABLE(watchos);

/// An aspect ratio of 1x1.
AVF_EXPORT AVCaptureAspectRatio const AVCaptureAspectRatio1x1 API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, macCatalyst, tvos, visionos) API_UNAVAILABLE(watchos);

/// An aspect ratio of 16x9.
AVF_EXPORT AVCaptureAspectRatio const AVCaptureAspectRatio16x9 API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, macCatalyst, tvos, visionos) API_UNAVAILABLE(watchos);

/// An aspect ratio of 9x16.
AVF_EXPORT AVCaptureAspectRatio const AVCaptureAspectRatio9x16 API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, macCatalyst, tvos, visionos) API_UNAVAILABLE(watchos);

/// An aspect ratio of 4x3.
AVF_EXPORT AVCaptureAspectRatio const AVCaptureAspectRatio4x3 API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, macCatalyst, tvos, visionos) API_UNAVAILABLE(watchos);

/// An aspect ratio of 3x4.
AVF_EXPORT AVCaptureAspectRatio const AVCaptureAspectRatio3x4 API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, macCatalyst, tvos, visionos) API_UNAVAILABLE(watchos);


API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, macCatalyst, tvos, visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDevice (DynamicAspectRatio)

/// A key-value observable property indicating the current aspect ratio for a device.
///
/// This property is initialized to the first ``AVCaptureAspectRatio`` listed in the device's activeFormat's ``AVCaptureDeviceFormat/supportedDynamicAspectRatios`` property. If the activeFormat's ``AVCaptureDeviceFormat/supportedDynamicAspectRatios`` is an empty array, this property returns nil.
@property(readonly, nullable) AVCaptureAspectRatio dynamicAspectRatio;

/// A key-value observable property describing the output dimensions of the video buffer based on the device's dynamic aspect ratio.
///
/// If the device's activeFormat's ``AVCaptureDeviceFormat/supportedDynamicAspectRatios`` is an empty array, this property returns {0,0}.
@property(readonly) CMVideoDimensions dynamicDimensions;

/// Updates the dynamic aspect ratio of the device.
///
/// - Parameter dynamicAspectRatio: The new ``AVCaptureAspectRatio`` the device should output.
/// - Parameter handler: A block called by the device when `dynamicAspectRatio` is set to the value specified. If you call ``setDynamicAspectRatio:completionHandler:`` multiple times, the completion handlers are called in FIFO order. The block receives a timestamp which matches that of the first buffer to which all settings have been applied. Note that the timestamp is synchronized to the device clock, and thus must be converted to the ``AVCaptureSession/synchronizationClock`` prior to comparison with the timestamps of buffers delivered via an ``AVCaptureVideoDataOutput``. You may pass `nil` for the `handler` parameter if you do not need to know when the operation completes.
///
/// This is the only way of setting ``dynamicAspectRatio``. This method throws an `NSInvalidArgumentException` if `dynamicAspectRatio` is not a supported aspect ratio found in the device's activeFormat's ``AVCaptureDeviceFormat/supportedDynamicAspectRatios``. This method throws an `NSGenericException` if you call it without first obtaining exclusive access to the device using ``AVCaptureDevice/lockForConfiguration:``.
- (void)setDynamicAspectRatio:(AVCaptureAspectRatio)dynamicAspectRatio completionHandler:(nullable void (^)(CMTime syncTime, NSError * _Nullable error))handler;

@end

@class AVCaptureSmartFramingMonitor;

API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, macCatalyst, tvos, visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDevice (AVCaptureDeviceSmartFraming)

/// A monitor owned by the device that recommends an optimal framing based on the content in the scene.
///
/// An ultra wide camera device that supports dynamic aspect ratio configuration may also support "smart framing monitoring". If this property returns non `nil`, you may use it to listen for framing recommendations by configuring its ``AVCaptureSmartFramingMonitor/enabledFramings`` and calling ``AVCaptureSmartFramingMonitor/startMonitoringWithError:``. The smart framing monitor only makes recommendations when the current ``AVCaptureDevice/activeFormat`` supports smart framing (see ``AVCaptureDeviceFormat/smartFramingSupported``).
@property(nonatomic, readonly, nullable) AVCaptureSmartFramingMonitor *smartFramingMonitor;

@end

@class AVCaptureFraming;

/// An object associated with a capture device that monitors the scene and suggests an optimal framing.
///
/// A smart framing monitor observes its associated device for objects of interest entering and exiting the camera's field of view and recommends an optimal framing for good photographic composition. This framing recommendation consists of an aspect ratio and zoom factor. You may respond to the device's framing recommendation by calling ``AVCaptureDevice/setDynamicAspectRatio:completionHandler:`` and setting ``AVCaptureDevice/videoZoomFactor`` on the associated device in whatever order best matches your animation between old and new framings.
API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, macCatalyst, tvos, visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureSmartFramingMonitor : NSObject

AV_INIT_UNAVAILABLE

/// An array of framings supported by the monitor in its current configuration.
///
/// The monitor is capable of recommending any of the framings in this array. This property is key-value observable and may change as the target capture device's ``AVCaptureDevice/activeFormat`` property changes. This array contains the full set of framings supported by the monitor in the device's current configuration. You must tell the monitor which smart framings you are interested in having recommended to you by setting the ``enabledFramings`` property.
@property(nonatomic, readonly) NSArray<AVCaptureFraming *> *supportedFramings;

/// An array of framings that the monitor is allowed to suggest.
///
/// The monitor is capable of recommending any of the framings in the ``supportedFramings`` array. This property contains the subset of ``supportedFramings`` you would like to have recommended to you. You may set this property at any time while running your ``AVCaptureSession``. This property's default value is the empty array.
@property(nonatomic, copy) NSArray<AVCaptureFraming *> *enabledFramings;

/// The latest recommended framing from the monitor.
///
/// While your ``AVCaptureSession`` is running, the monitor continuously observes its device's scene to recommend the best framing. This recommended framing is always one of the values in ``enabledFramings``. This property may return `nil` if smart framing isn't supported for the device in its current configuration. Its default value is `nil`. This property is key-value observable, and when you observe a change, you may respond to the new recommendation by calling ``AVCaptureDevice/setDynamicAspectRatio:completionHandler:`` and setting ``AVCaptureDevice/videoZoomFactor`` on the associated device in whatever order best matches your animation between old and new framings.
@property(nonatomic, readonly, nullable) AVCaptureFraming *recommendedFraming;

/// Begins monitoring the device's active scene and making framing recommendations.
///
/// - Parameter outError: A pointer to an ``NSError`` indicating why ``startMonitoringWithError:`` failed, or to a `nil` ``NSError`` on success.
/// - Returns: `true` if successful, `false` if monitoring could not be started.
///
/// The monitor's ``recommendedFraming`` is `nil` when it is not actively running. Call this method to start monitoring. You may start monitoring before or after calling ``AVCaptureSession/startRunning``,  and you may stop active monitoring without stopping the capture session by calling ``stopMonitoring`` at any time, but you must set ``enabledFramings`` before running your capture session so that the monitor is prepared for your desired framing recommendations. While the monitor is running, you may set ``enabledFramings`` at any time to change the framing choices the monitor should consider in its recommendations.
- (BOOL)startMonitoringWithError:(NSError **)outError;

/// Stops monitoring the device's active scene and making framing recommendations.
///
/// The monitor's ``recommendedFraming`` is `nil` when it is not actively running. Call this method to stop actively monitoring the scene and making framing recommendations. You may start monitoring before or after calling ``AVCaptureSession/startRunning``, and may stop active monitoring without stopping the capture session by calling ``stopMonitoring`` at any time.
- (void)stopMonitoring;

/// Yes when the receiver is actively monitoring.
///
/// See ``startMonitoringWithError:`` and ``stopMonitoring``.
@property(nonatomic, readonly, getter=isMonitoring) BOOL monitoring;

@end

/// A framing, consisting of an aspect ratio and a zoom factor.
///
/// An ``AVCaptureSmartFramingMonitor`` provides framing recommendations using this object.
API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, macCatalyst, tvos, visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureFraming : NSObject

AV_INIT_UNAVAILABLE

/// An aspect ratio.
///
/// One of the enumerated aspect ratios  suitable for use with the ``AVCaptureDevice`` dynamic aspect ratio APIs.
@property(atomic, readonly) AVCaptureAspectRatio aspectRatio;

/// A zoom factor.
///
/// Suitable for use with the ``AVCaptureDevice/videoZoomFactor`` property or ``AVCaptureDevice/rampToVideoZoomFactor:withRate:``.
@property(atomic, readonly) float zoomFactor;

@end

@interface AVCaptureDevice (AVCaptureDeviceNominalFocalLengthIn35mmFilm)

/// The nominal 35mm equivalent focal length of the capture device's lens.
///
/// This value represents a nominal measurement of the device's field of view, expressed as a 35mm equivalent focal length, measured diagonally. The value is similar to the `FocalLengthIn35mmFormat` EXIF entry (see <doc://com.apple.documentation/documentation/imageio/kcgimagepropertyexiffocallenin35mmfilm>) for a photo captured using the device's format where ``AVCaptureDeviceFormat/highestPhotoQualitySupported`` is `true` or when you've configured the session with the ``AVCaptureSessionPresetPhoto`` preset.
///
/// This property value is `0` for virtual devices and external cameras.
@property(nonatomic, readonly) float nominalFocalLengthIn35mmFilm API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, macCatalyst, tvos, visionos) API_UNAVAILABLE(watchos);
@end


#pragma mark - AVCaptureDeviceDiscoverySession

/*!
 @class AVCaptureDeviceDiscoverySession
 @abstract
    The AVCaptureDeviceDiscoverySession allows clients to search for devices by certain criteria.
 
 @discussion
    This class allows clients to discover devices by providing certain search criteria. The objective of this class is to help find devices by device type and optionally by media type or position and allow you to key-value observe changes to the returned devices list.
 */
API_AVAILABLE(macos(10.15), ios(10.0), macCatalyst(14.0), tvos(17.0), visionos(2.1)) API_UNAVAILABLE(watchos)
@interface AVCaptureDeviceDiscoverySession : NSObject

AV_INIT_UNAVAILABLE

/*!
 @method discoverySessionWithDeviceTypes:
 @abstract
    Returns an AVCaptureDeviceDiscoverySession instance for the given device types, media type, and position.
 
 @param deviceTypes
    An array specifying the device types to include in the list of discovered devices.
 @param mediaType
    The media type, such as AVMediaTypeVideo, AVMediaTypeAudio, or AVMediaTypeMuxed, to include in the list of discovered devices. Pass nil to search for devices with any media type.
 @param position
    The position to include in the list of discovered devices. Pass AVCaptureDevicePositionUnspecified to search for devices with any position.
 @result
    The AVCaptureDeviceDiscoverySession from which the list of devices can be obtained.
 
 @discussion
    The list of device types is mandatory. This is used to make sure that clients only get access to devices of types they expect. This prevents new device types from automatically being included in the list of devices.
 */
+ (instancetype)discoverySessionWithDeviceTypes:(NSArray<AVCaptureDeviceType> *)deviceTypes mediaType:(nullable AVMediaType)mediaType position:(AVCaptureDevicePosition)position;

/*!
 @property devices
 @abstract
    The list of devices that comply to the search criteria specified on the discovery session.
 
 @discussion
    The returned array contains only devices that are available at the time the method is called. Applications can key-value observe this property to be notified when the list of available devices has changed. For apps linked against iOS 10, the devices returned are unsorted. For apps linked against iOS 11 or later, the devices are sorted by AVCaptureDeviceType, matching the order specified in the deviceTypes parameter of +[AVCaptureDeviceDiscoverySession discoverySessionWithDeviceTypes:mediaType:position:]. If a position of AVCaptureDevicePositionUnspecified is specified, the results are further ordered by position in the AVCaptureDevicePosition enum. Starting in Mac Catalyst 14.0, clients can key value observe the value of this property to be notified when the devices change.
 */
@property(nonatomic, readonly) NSArray<AVCaptureDevice *> *devices;

/*!
 @property supportedMultiCamDeviceSets
 @abstract
    An array of sets of AVCaptureDevices that are allowed to be used simultaneously in an AVCaptureMultiCamSession.
 
 @discussion
    When using an AVCaptureMultiCamSession, multiple cameras may be used as device inputs to the session, so long as they are included in one of the supportedMultiCamDeviceSets. Starting in Mac Catalyst 14.0, clients can key value observe the value of this property to be notified when the device sets change.
 */
@property(nonatomic, readonly) NSArray<NSSet<AVCaptureDevice *> *> *supportedMultiCamDeviceSets API_AVAILABLE(ios(13.0), visionos(2.1)) API_UNAVAILABLE(macos);

@end


#pragma mark - AVCaptureDeviceRotationCoordinator

/*!
 @class AVCaptureDeviceRotationCoordinator
 @abstract
    The AVCaptureDeviceRotationCoordinator allows clients to monitor rotations of a given AVCaptureDevice instance and be provided the video rotation angle that should be applied for horizon-level preview and capture relative to gravity.
 
 @discussion
    Each instance of AVCaptureDeviceRotationCoordinator allows a client to coordinate with changes to the rotation of an AVCaptureDevice to ensure the camera's video preview and captured output are horizon-level. The coordinator delivers key-value updates on the main queue.
 */
API_AVAILABLE(macos(14.0), ios(17.0), macCatalyst(17.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
NS_SWIFT_NAME(AVCaptureDevice.RotationCoordinator)
@interface AVCaptureDeviceRotationCoordinator : NSObject

AV_INIT_UNAVAILABLE

/*!
 @method initWithDevice:previewLayer:
 @abstract
    Returns an AVCaptureDeviceRotationCoordinator instance that provides updates to the amount of rotation that should be applied for horizon-level preview and capture relative to gravity.
 
 @param device
    The device for which to monitor rotation.
 @param previewLayer
    A layer displaying the camera's video preview. If nil, the coordinator will return 0 degrees of rotation for horizon-level preview.
 @result
    An AVCaptureDeviceRotationCoordinator from which rotation angles for preview and capture can be obtained.
 
 @discussion
    An AVCaptureDeviceRotationCoordinator is only applicable to video devices. The given device and layer determine the amount of rotation that should be applied for horizon-level preview and capture.
 */
- (instancetype)initWithDevice:(AVCaptureDevice *)device previewLayer:(nullable CALayer *)previewLayer;

/*!
 @property device
 @abstract
    The the device for which the coordinator provides video rotation angles.
 
 @discussion
    The value of this property is the AVCaptureDevice instance that was used to create the coordinator. The coordinator holds a weak reference to the device.
 */
@property(nonatomic, readonly, nullable, weak) AVCaptureDevice *device;

/*!
 @property previewLayer
 @abstract
    The CALayer for which the coordinator calculates video rotation angles for horizon-level preview.
 
 @discussion
    The value of this property is the CALayer instance that was used to create the coordinator. Clients may specify an AVCaptureVideoPreviewLayer or other CALayer instance that displays a camera's video preview. The coordinator holds a weak reference to the layer. The coordinator will return 0 degrees of rotation from -videoRotationAngleForHorizonLevelPreview if a layer was not specified at initialization, the layer is not in a view hierarchy, or the layer has been deallocated.
 */
@property(nonatomic, readonly, nullable, weak) CALayer *previewLayer;

/*!
 @property videoRotationAngleForHorizonLevelPreview
 @abstract
    Returns a video rotation angle in degrees for displaying the camera's video preview in the given CALayer.
 
 @discussion
    The video rotation angle represents by how much the camera's video preview should be rotated for display in the CALayer to be horizon-level relative to gravity. An angle of 0 degrees means that video will be output in the camera's unrotated, native sensor orientation. The video rotation angle for preview may differ between cameras at different positions. For example when an iOS device is held in portrait orientation, the video preview for built-in cameras may need to be rotated by 90 degrees while the video preview for an external camera should not be rotated. External cameras return 0 degrees of rotation even if they physically rotate when their position in physical space is unknown. This property is key-value observable and delivers updates on the main queue.
 */
@property(nonatomic, readonly) CGFloat videoRotationAngleForHorizonLevelPreview;

/*!
 @property videoRotationAngleForHorizonLevelCapture
 @abstract
    Returns a video rotation angle in degrees for horizon-level capture from this camera.
 
 @discussion
    The video rotation angle represents by how much the photos or movies captured from the camera should be rotated to be horizon-level relative to gravity. A video rotation angle of 0 degrees means that the output will be in the camera's unrotated, native sensor orientation. The video rotation angle for capture may differ between cameras. For example when an iOS device is held in portrait orientation, photos and movies captured from built-in cameras may need to be rotated by 90 degrees while the photos and movies from an external camera should not be rotated. External cameras return 0 degrees of rotation even if they physically rotate when their position in physical space is unknown. The video rotation angle returned from this property is distinct from the angle returned by -videoRotationAngleForHorizonLevelPreview because in certain combinations of device and interface orientations, the video rotation angle needed for horizon-level preview may not match the amount of rotation needed for horizon-level capture. This property is key-value observable and delivers updates on the main queue.
 */
@property(nonatomic, readonly) CGFloat videoRotationAngleForHorizonLevelCapture;

@end

#pragma mark - AVExposureBiasRange

/*!
 @class AVExposureBiasRange
 @abstract
    An AVExposureBiasRange expresses an inclusive range of supported exposure bias values, in EV units.
 
 @discussion
    This is used by AVCaptureSystemExposureBiasSlider for the range the slider uses.
 */
API_AVAILABLE(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos) NS_REFINED_FOR_SWIFT
@interface AVExposureBiasRange : NSObject

AV_INIT_UNAVAILABLE

/*!
 @property minExposureBias
 @abstract
    A float indicating the minimum exposure bias in EV units supported by this range.
 */
@property(nonatomic, readonly) float minExposureBias;

/*!
 @property maxExposureBias
 @abstract
    A float indicating the maximum exposure bias in EV units supported by this range.
 */
@property(nonatomic, readonly) float maxExposureBias;

/*!
 @method containsExposureBias:
 @abstract
    Tests if a given exposure bias in EV units is within the exposure bias range.
 
 @param exposureBias
    The exposure bias to test.
 @result
    Returns YES if the given exposure bias is within the exposure bias, NO otherwise.
 
 @discussion
    Note that the exposure bias ranges are inclusive.
 */
- (BOOL)containsExposureBias:(float)exposureBias;

@end


#pragma mark - AVFrameRateRange

@class AVFrameRateRangeInternal;

/*!
 @class AVFrameRateRange
 @abstract
    An AVFrameRateRange expresses a range of valid frame rates as min and max rate and min and max duration.
 
 @discussion
    An AVCaptureDevice exposes an array of formats, and its current activeFormat may be queried. The payload for the formats property is an array of AVCaptureDeviceFormat objects and the activeFormat property payload is an AVCaptureDeviceFormat. AVCaptureDeviceFormat wraps a CMFormatDescription and expresses a range of valid video frame rates as an NSArray of AVFrameRateRange objects. AVFrameRateRange expresses min and max frame rate as a rate in frames per second and duration (CMTime). An AVFrameRateRange object is immutable. Its values do not change for the life of the object.
 */
API_AVAILABLE(macos(10.7), ios(7.0), macCatalyst(14.0), tvos(17.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface AVFrameRateRange : NSObject
{
@private
    AVFrameRateRangeInternal *_internal;
}

AV_INIT_UNAVAILABLE

/*!
 @property minFrameRate
 @abstract
    A Float64 indicating the minimum frame rate supported by this range.
 
 @discussion
    This read-only property indicates the minimum frame rate supported by this range in frames per second.
 */
@property(readonly) Float64 minFrameRate;

/*!
 @property maxFrameRate
 @abstract
    A Float64 indicating the maximum frame rate supported by this range.
 
 @discussion
    This read-only property indicates the maximum frame rate supported by this range in frames per second.
 */
@property(readonly) Float64 maxFrameRate;

/*!
 @property maxFrameDuration
 @abstract
    A CMTime indicating the maximum frame duration supported by this range.
 
 @discussion
    This read-only property indicates the maximum frame duration supported by this range. It is the reciprocal of minFrameRate, and expresses minFrameRate as a duration.
 */
@property(readonly) CMTime maxFrameDuration;

/*!
 @property minFrameDuration
 @abstract
    A CMTime indicating the minimum frame duration supported by this range.
 
 @discussion
    This read-only property indicates the minimum frame duration supported by this range. It is the reciprocal of maxFrameRate, and expresses maxFrameRate as a duration.
 */
@property(readonly) CMTime minFrameDuration;

@end


#pragma mark - AVZoomRange

/*!
 @class AVZoomRange
 @abstract
    An AVZoomRange expresses an inclusive range of supported zoom factors.
 
 @discussion
    This is used by features that have requirements on zoom factors falling within certain ranges.
 */
API_AVAILABLE(macos(14.2), ios(17.2), macCatalyst(17.2), tvos(17.2)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos) NS_REFINED_FOR_SWIFT
@interface AVZoomRange : NSObject

AV_INIT_UNAVAILABLE

/*!
@property minZoomFactor
@abstract
    A CGFloat indicating the minimum zoom factor supported by this range.
*/
@property(nonatomic, readonly) CGFloat minZoomFactor;

/*!
@property maxZoomFactor
@abstract
    A CGFloat indicating the maximum zoom factor supported by this range.
 */
@property(nonatomic, readonly) CGFloat maxZoomFactor;

/*!
@method containsZoomFactor:
@abstract
    Tests if a given zoom factor is within the zoom range.
 
@param zoomFactor
    The zoom factor to test.
@result
    Returns YES if the given zoom factor is within the zoom range, NO otherwise.
 
@discussion
     Note that the zoom ranges are inclusive.
 */
- (BOOL)containsZoomFactor:(CGFloat)zoomFactor;

@end

/// Constants indicating the modes of video stabilization supported by the device's format.
typedef NS_ENUM(NSInteger, AVCaptureVideoStabilizationMode) {
    /// Indicates that video should not be stabilized.
    AVCaptureVideoStabilizationModeOff       = 0,
    /// Indicates that video should be stabilized using the standard video stabilization algorithm introduced with iOS 5.0. Standard video stabilization has a reduced field of view. Enabling video stabilization may introduce additional latency into the video capture pipeline.
    AVCaptureVideoStabilizationModeStandard  = 1,
    /// Indicates that video should be stabilized using the cinematic stabilization algorithm for more dramatic results. Cinematic video stabilization has a reduced field of view compared to standard video stabilization. Enabling cinematic video stabilization introduces much more latency into the video capture pipeline than standard video stabilization and consumes significantly more system memory. Use narrow or identical min and max frame durations in conjunction with this mode.
    AVCaptureVideoStabilizationModeCinematic = 2,
    /// Indicates that the video should be stabilized using the extended cinematic stabilization algorithm. Enabling extended cinematic stabilization introduces longer latency into the video capture pipeline compared to the ``AVCaptureVideoStabilizationModeCinematic`` and consumes more memory, but yields improved stability. It is recommended to use identical or similar min and max frame durations in conjunction with this mode. Cinematic extended mode is face aware when enabled on a front-facing ultra wide camera on iPhone, and prioritizes stabilization of the subject of the frame rather than the background.
    AVCaptureVideoStabilizationModeCinematicExtended API_AVAILABLE(ios(13.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos) = 3,
    /// Indicates that video should be stabilized using the preview optimized stabilization algorithm. Preview stabilization is a low latency and low power algorithm which is supported only on connections which either have an associated preview layer or have a preview-sized ``AVCaptureVideoDataOutput``.
    AVCaptureVideoStabilizationModePreviewOptimized API_AVAILABLE(ios(17.0), macCatalyst(17.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) = 4,
    /// Indicates that the video should be stabilized using the enhanced extended cinematic stabilization algorithm. Enhanced extended cinematic has a reduced field of view compared to extended cinematic, without any noticeable increase in latency, and it yields improved stability. It is recommended to use identical or similar min and max frame durations in conjunction with this mode. Cinematic extended enhanced mode is face aware when enabled on a front-facing ultra wide camera on iPhone, and prioritizes stabilization of the subject of the frame rather than the background.
    AVCaptureVideoStabilizationModeCinematicExtendedEnhanced API_AVAILABLE(ios(18.0), macCatalyst(18.0), tvos(18.0)) API_UNAVAILABLE(macos, visionos) = 5,
    /// Indicates that video should be stabilized using the low latency stabilization algorithm. Low Latency stabilization has a reduced field of view. Enabling low latency stabilization introduces no additional latency into the video capture pipeline.
    AVCaptureVideoStabilizationModeLowLatency API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, macCatalyst, tvos, visionos) = 6,
    /// Indicates that the most appropriate video stabilization mode for the device and format should be chosen.
    AVCaptureVideoStabilizationModeAuto      = -1,
} API_AVAILABLE(ios(8.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

/*!
 @enum AVCaptureAutoFocusSystem
 @abstract
    Constants indicating the autofocus system.
 
 @constant AVCaptureAutoFocusSystemNone
    Indicates that autofocus is not available.
 @constant AVCaptureAutoFocusSystemContrastDetection
    Indicates that autofocus is achieved by contrast detection. Contrast detection performs a focus scan to find the optimal position.
 @constant AVCaptureAutoFocusSystemPhaseDetection
    Indicates that autofocus is achieved by phase detection. Phase detection has the ability to achieve focus in many cases without a focus scan. Phase detection autofocus is typically less visually intrusive than contrast detection autofocus.
 */
typedef NS_ENUM(NSInteger, AVCaptureAutoFocusSystem) {
    AVCaptureAutoFocusSystemNone              = 0,
    AVCaptureAutoFocusSystemContrastDetection = 1,
    AVCaptureAutoFocusSystemPhaseDetection    = 2,
} API_AVAILABLE(macos(10.15), ios(8.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);


#pragma mark - AVCaptureDeviceFormat

@class AVCaptureOutput;
@class AVCaptureDeviceFormatInternal;

/*!
 @class AVCaptureDeviceFormat
 @abstract
    An AVCaptureDeviceFormat wraps a CMFormatDescription and other format-related information, such as min and max framerate.
 
 @discussion
    An AVCaptureDevice exposes an array of formats, and its current activeFormat may be queried. The payload for the formats property is an array of AVCaptureDeviceFormat objects and the activeFormat property payload is an AVCaptureDeviceFormat. AVCaptureDeviceFormat is a thin wrapper around a CMFormatDescription, and can carry associated device format information that doesn't go in a CMFormatDescription, such as min and max frame rate. An AVCaptureDeviceFormat object is immutable. Its values do not change for the life of the object.
 */
API_AVAILABLE(macos(10.7), ios(7.0), macCatalyst(14.0), tvos(17.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface AVCaptureDeviceFormat : NSObject
{
@private
    AVCaptureDeviceFormatInternal *_internal;
}

AV_INIT_UNAVAILABLE

/*!
 @property mediaType
 @abstract
    An NSString describing the media type of an AVCaptureDevice active or supported format.
 
 @discussion
    Supported mediaTypes are listed in AVMediaFormat.h. This is a read-only property. The caller assumes no ownership of the returned value and should not CFRelease it.
 */
@property(nonatomic, readonly) AVMediaType mediaType;

/*!
 @property formatDescription
 @abstract
    A CMFormatDescription describing an AVCaptureDevice active or supported format.
 
 @discussion
    A CMFormatDescription describing an AVCaptureDevice active or supported format. This is a read-only property. The caller assumes no ownership of the returned value and should not CFRelease it.
 */
@property(nonatomic, readonly) CMFormatDescriptionRef formatDescription;

/*!
 @property videoSupportedFrameRateRanges
 @abstract
    A property indicating the format's supported frame rate ranges.
 
 @discussion
    videoSupportedFrameRateRanges is an array of AVFrameRateRange objects, one for each of the format's supported video frame rate ranges.
 */
@property(nonatomic, readonly) NSArray<AVFrameRateRange *> *videoSupportedFrameRateRanges;

/*!
 @property videoFieldOfView
 @abstract
    A property indicating the format's horizontal field of view.
 
 @discussion
    videoFieldOfView is a float value indicating the receiver's field of view in degrees. If field of view is unknown, a value of 0 is returned.
 */
@property(nonatomic, readonly) float videoFieldOfView API_UNAVAILABLE(macos, visionos);

/*!
 @property videoBinned
 @abstract
    A property indicating whether the format is binned.
 
 @discussion
    videoBinned is a BOOL indicating whether the format is a binned format. Binning is a pixel-combining process which can result in greater low light sensitivity at the cost of reduced resolution.
 */
@property(nonatomic, readonly, getter=isVideoBinned) BOOL videoBinned API_UNAVAILABLE(macos, visionos);

/*!
 @method isVideoStabilizationModeSupported
 @abstract
    Returns whether the format supports the given video stabilization mode.
 
 @param videoStabilizationMode
    An AVCaptureVideoStabilizationMode to be checked.

 @discussion
    isVideoStabilizationModeSupported: returns a boolean value indicating whether the format can be stabilized using the given mode with -[AVCaptureConnection setPreferredVideoStabilizationMode:]. In the case of ProRes RAW formats, video stabilization metadata is attached to the unstabilized video buffers instead.
 */
- (BOOL)isVideoStabilizationModeSupported:(AVCaptureVideoStabilizationMode)videoStabilizationMode API_AVAILABLE(ios(8.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @property videoStabilizationSupported
 @abstract
    A property indicating whether the format supports video stabilization.
 
 @discussion
    videoStabilizationSupported is a BOOL indicating whether the format can be stabilized using AVCaptureConnection -setEnablesVideoStabilizationWhenAvailable. This property is deprecated. Use isVideoStabilizationModeSupported: instead.
 */
@property(nonatomic, readonly, getter=isVideoStabilizationSupported) BOOL videoStabilizationSupported API_DEPRECATED("Use isVideoStabilizationModeSupported: instead.", ios(7.0, 8.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(tvos);

/*!
 @property videoMaxZoomFactor
 @abstract
    Indicates the maximum zoom factor available for the AVCaptureDevice's videoZoomFactor property.
 
 @discussion
    If the device's videoZoomFactor property is assigned a larger value, an NSRangeException will be thrown. A maximum zoom factor of 1 indicates no zoom is available.
 */
@property(nonatomic, readonly) CGFloat videoMaxZoomFactor API_UNAVAILABLE(macos, visionos);

/*!
 @property videoZoomFactorUpscaleThreshold
 @abstract
    Indicates the value of AVCaptureDevice's videoZoomFactor property at which the image output begins to require upscaling.
 
 @discussion
    In some cases the image sensor's dimensions are larger than the dimensions reported by the video AVCaptureDeviceFormat. As long as the sensor crop is larger than the reported dimensions of the AVCaptureDeviceFormat, the image will be downscaled. Setting videoZoomFactor to the value of videoZoomFactorUpscalingThreshold will provide a center crop of the sensor image data without any scaling. If a greater zoom factor is used, then the sensor data will be upscaled to the device format's dimensions.
 */
@property(nonatomic, readonly) CGFloat videoZoomFactorUpscaleThreshold API_UNAVAILABLE(macos, visionos);

/*!
 @property systemRecommendedVideoZoomRange
 @abstract
    Indicates the system's recommended zoom range for this device format.
 
 @discussion
    This property can be used to create a slider in your app's user interface to control the device's zoom with a system-recommended video zoom range. When a recommendation is not available, this property returns nil. Clients can key value observe AVCaptureDevice's minAvailableVideoZoomFactor and maxAvailableVideoZoomFactor properties to know when a device's supported zoom is restricted within the recommended zoom range.
 
    The value of this property is also used for the AVCaptureSystemZoomSlider's range.
 */
@property(nonatomic, readonly, nullable) AVZoomRange *systemRecommendedVideoZoomRange API_AVAILABLE(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0)) API_UNAVAILABLE(visionos) NS_REFINED_FOR_SWIFT;

/*!
 @property minExposureDuration
 @abstract
    A CMTime indicating the minimum supported exposure duration.
 
 @discussion
    This read-only property indicates the minimum supported exposure duration.
 */
@property(nonatomic, readonly) CMTime minExposureDuration API_AVAILABLE(ios(8.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @property maxExposureDuration
 @abstract
    A CMTime indicating the maximum supported exposure duration.
 
 @discussion
    This read-only property indicates the maximum supported exposure duration.
 */
@property(nonatomic, readonly) CMTime maxExposureDuration API_AVAILABLE(ios(8.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @property systemRecommendedExposureBiasRange
 @abstract
    Indicates the system's recommended exposure bias range for this device format.
 
 @discussion
    This property can be used to create a slider in your app's user interface to control the device's exposure bias with a system-recommended exposure bias range. When a recommendation is not available, this property returns nil.
 
    The value of this property is also used for the AVCaptureSystemExposureBiasSlider's range.
 */
@property(nonatomic, readonly, nullable) AVExposureBiasRange *systemRecommendedExposureBiasRange API_AVAILABLE(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0)) API_UNAVAILABLE(visionos) NS_REFINED_FOR_SWIFT;

/*!
 @property minISO
 @abstract
    A float indicating the minimum supported exposure ISO value.
 
 @discussion
    This read-only property indicates the minimum supported exposure ISO value.
 */
@property(nonatomic, readonly) float minISO API_AVAILABLE(ios(8.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @property maxISO
 @abstract
    An float indicating the maximum supported exposure ISO value.
 
 @discussion
    This read-only property indicates the maximum supported exposure ISO value.
 */
@property(nonatomic, readonly) float maxISO API_AVAILABLE(ios(8.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @property globalToneMappingSupported
 @abstract
    A property indicating whether the format supports global tone mapping.
 
 @discussion
    globalToneMappingSupported is a BOOL indicating whether the format supports global tone mapping. See AVCaptureDevice's globalToneMappingEnabled property.
 */
@property(nonatomic, readonly, getter=isGlobalToneMappingSupported) BOOL globalToneMappingSupported API_AVAILABLE(ios(13.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

/*!
 @property videoHDRSupported
 @abstract
    A property indicating whether the format supports high dynamic range streaming.
 
 @discussion
    videoHDRSupported is a BOOL indicating whether the format supports high dynamic range streaming, also known as Extended Dynamic Range (EDR). When enabled, the device streams at twice the published frame rate, capturing an under-exposed frame and correctly exposed frame for each frame time at the published rate. Portions of the under-exposed frame are combined with the correctly exposed frame to recover detail in darker areas of the scene. EDR is a separate and distinct feature from 10-bit HDR video (first seen in 2020 iPhones). 10-bit formats with HLG BT2020 color space have greater dynamic range by virtue of their expanded bit depth and HLG transfer function, and when captured in movies, contain Dolby Vision metadata. They are, in effect, "always on" HDR. And thus the videoHDRSupported property is always NO for 10-bit formats only supporting HLG BT2020 colorspace, since HDR cannot be enabled or disabled. To enable videoHDR (EDR), set the AVCaptureDevice.videoHDREnabled property.
 */
@property(nonatomic, readonly, getter=isVideoHDRSupported) BOOL videoHDRSupported API_AVAILABLE(ios(8.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @property highResolutionStillImageDimensions
 @abstract
    CMVideoDimensions indicating the highest resolution still image that can be produced by this format.
 
 @discussion
    By default, AVCapturePhotoOutput and AVCaptureStillImageOutput emit images with the same dimensions as their source AVCaptureDevice's activeFormat.formatDescription property. Some device formats support high resolution photo output. That is, they can stream video to an AVCaptureVideoDataOutput or AVCaptureMovieFileOutput at one resolution while outputting photos to AVCapturePhotoOutput at a higher resolution. You may query this property to discover a video format's supported high resolution still image dimensions. See -[AVCapturePhotoOutput highResolutionPhotoEnabled], -[AVCapturePhotoSettings highResolutionPhotoEnabled], and -[AVCaptureStillImageOutput highResolutionStillImageOutputEnabled].
 
    AVCaptureDeviceFormats of type AVMediaTypeDepthData may also support the delivery of a higher resolution depth data map to an AVCapturePhotoOutput. Chief differences are:
       - Depth data accompanying still images is not supported by AVCaptureStillImageOutput. You must use AVCapturePhotoOutput.
       - By opting in for depth data ( -[AVCapturePhotoSettings setDepthDataDeliveryEnabled:YES] ), you implicitly opt in for high resolution depth data if it's available. You may query the -[AVCaptureDevice activeDepthDataFormat]'s highResolutionStillImageDimensions to discover the depth data resolution that will be delivered with captured photos.
 */
@property(nonatomic, readonly) CMVideoDimensions highResolutionStillImageDimensions API_DEPRECATED("Use supportedMaxPhotoDimensions instead.", ios(8.0, 16.0), macCatalyst(14.0, 16.0)) API_UNAVAILABLE(macos, tvos, visionos);

/*!
 @property highPhotoQualitySupported
 @abstract
    A boolean value specifying whether this format supports high photo quality when selecting an AVCapturePhotoQualityPrioritization of .balanced or .quality.
 
 @discussion
    If an AVCaptureDeviceFormat's highPhotoQualitySupported property is YES, the format produces higher image quality when selecting .balanced or .quality AVCapturePhotoQualityPrioritization compared to .speed. Such formats adhere to the following rules:
        - Photo requests with a prioritization of .speed produce the fastest image result (suitable for burst captures).
        - Photo requests with a prioritization of .balanced produce higher image quality without dropping frames if a video recording is underway.
        - Photo requests with a prioritization of .quality produce high image quality and may cause frame drops if a video recording is underway. For maximum backward compatibility, photo requests on high photo quality formats set to .quality only cause video frame drops if your app is linked on or after iOS 15.
    Formats that don't support high photo quality produce the same image quality whether you select .speed, .balanced, or .quality. Note that high photo quality is only attainable when using the AVCapturePhotoOutput with these supported formats.
 */
@property(nonatomic, readonly, getter=isHighPhotoQualitySupported) BOOL highPhotoQualitySupported API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @property highestPhotoQualitySupported
 @abstract
    A boolean value specifying whether this format supports the highest possible photo quality that can be delivered on the current platform.
 
 @discussion
    Of the many formats supported by an AVCaptureDevice, only a few of them are designated as "photo" formats which can produce the highest possible quality, such as still image stabilization and Live Photos. If you intend to connect an AVCaptureDeviceInput to an AVCapturePhotoOutput and receive the best possible images, you should ensure that you are either using the AVCaptureSessionPresetPhoto as your preset, or if using the parallel AVCaptureDevice activeFormat API, select as your activeFormat one for which this property is YES.
 */
@property(nonatomic, readonly, getter=isHighestPhotoQualitySupported) BOOL highestPhotoQualitySupported API_AVAILABLE(ios(13.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

/*!
 @property autoFocusSystem
 @abstract
    A property indicating the autofocus system.
 
 @discussion
    This read-only property indicates the autofocus system.
 */
@property(nonatomic, readonly) AVCaptureAutoFocusSystem autoFocusSystem API_AVAILABLE(macos(10.15), ios(8.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos);

/*!
 @property supportedColorSpaces
 @abstract
    A property indicating the receiver's supported color spaces.
 
 @discussion
    This read-only property indicates the receiver's supported color spaces as an array of AVCaptureColorSpace constants sorted from narrow to wide color.
 */
@property(nonatomic, readonly) NSArray<NSNumber *> *supportedColorSpaces API_AVAILABLE(macos(10.15), ios(10.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos);

/*!
 @property videoMinZoomFactorForDepthDataDelivery
 @abstract
    A deprecated property. Please use supportedVideoZoomFactorsForDepthDataDelivery instead
 */
@property(nonatomic, readonly) CGFloat videoMinZoomFactorForDepthDataDelivery API_DEPRECATED_WITH_REPLACEMENT("supportedVideoZoomFactorsForDepthDataDelivery", ios(11.0,16.0), macCatalyst(14.0,16.0)) API_UNAVAILABLE(macos, tvos, visionos);

/*!
 @property videoMaxZoomFactorForDepthDataDelivery
 @abstract
    A deprecated property. Please use supportedVideoZoomFactorsForDepthDataDelivery instead
 */
@property(nonatomic, readonly) CGFloat videoMaxZoomFactorForDepthDataDelivery API_DEPRECATED_WITH_REPLACEMENT("supportedVideoZoomFactorsForDepthDataDelivery", ios(11.0,16.0), macCatalyst(14.0,16.0)) API_UNAVAILABLE(macos, tvos, visionos);

/*!
 @property supportedVideoZoomFactorsForDepthDataDelivery
 @abstract
    A deprecated property. Please use supportedVideoZoomRangesForDepthDataDelivery
 */
@property(nonatomic, readonly) NSArray<NSNumber *> *supportedVideoZoomFactorsForDepthDataDelivery API_DEPRECATED_WITH_REPLACEMENT("supportedVideoZoomRangesForDepthDataDelivery", ios(16.0, 17.2), macCatalyst(16.0, 17.2), tvos(17.0, 17.2)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos) NS_REFINED_FOR_SWIFT;

/*!
@property supportedVideoZoomRangesForDepthDataDelivery
@abstract
    This property returns the zoom ranges within which depth data can be delivered.

@discussion
    Virtual devices support limited zoom ranges when delivering depth data to any output. If this device format has no -supportedDepthDataFormats, this property returns an empty array.
    The presence of one or more ranges where the min and max zoom factors are not equal means that "continuous zoom" with depth is supported.
    For example:
    a) ranges: @[ [2..2], [4..4] ]
        only zoom factors 2 and 4 are allowed to be set when depthDataDelivery is enabled. Any other zoom factor results in an exception.
    b) ranges: @[ [2..5] ]
        depthDataDelivery is supported with zoom factors [2..5]. Zoom factors outside of this range may be set, but will result in loss of depthDataDeliery. Whenever zoom is set back to a value within the range of [2..5], depthDataDelivery will resume.
 
    When depth data delivery is enabled, the effective videoZoomFactorUpscaleThreshold will be 1.0, meaning that all zoom factors that are not native zoom factors (see AVCaptureDevice.virtualDeviceSwitchOverVideoZoomFactors and AVCaptureDevice.secondaryNativeResolutionZoomFactors) result in digital upscaling.
 */
@property(nonatomic, readonly) NSArray<AVZoomRange *> *supportedVideoZoomRangesForDepthDataDelivery API_AVAILABLE(macos(14.2), ios(17.2), macCatalyst(17.2), tvos(17.2)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos) NS_REFINED_FOR_SWIFT;

/*!
@property zoomFactorsOutsideOfVideoZoomRangesForDepthDeliverySupported
@abstract
    This property returns whether the format supports zoom factors outside of the supportedVideoZoomFactorRangesForDepthDataDelivery.

@discussion
    When a zoom factor outside of the supportedVideoZoomFactorRangesForDepthDataDelivery is set, depth data delivery will be suspended until a zoom factor within the supportedVideoZoomFactorRangesForDepthDataDelivery is set.
 */
@property(nonatomic, readonly) BOOL zoomFactorsOutsideOfVideoZoomRangesForDepthDeliverySupported API_AVAILABLE(macos(14.2), ios(17.2), macCatalyst(17.2), tvos(17.2)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @property supportedDepthDataFormats
 @abstract
    Indicates this format's companion depth data formats.
 
 @discussion
    If no depth data formats are supported by the receiver, an empty array is returned. On virtual devices, the supportedDepthDataFormats list items always match the aspect ratio of their paired video format. When the receiver is set as the device's activeFormat, you may set the device's activeDepthDataFormat to one of these supported depth data formats.
 */
@property(nonatomic, readonly) NSArray<AVCaptureDeviceFormat *> *supportedDepthDataFormats API_AVAILABLE(ios(11.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
 @property unsupportedCaptureOutputClasses
 @abstract
    A property indicating AVCaptureOutput subclasses the receiver does not support.
 
 @discussion
    As a rule, AVCaptureDeviceFormats of a given mediaType are available for use with all AVCaptureOutputs that accept that media type, but there are exceptions. For instance, on apps linked against iOS versions earlier than 12.0, the photo resolution video formats may not be used as sources for AVCaptureMovieFileOutput due to bandwidth limitations. On DualCamera devices, AVCaptureDepthDataOutput is not supported when outputting full resolution (i.e. 12 MP) video due to bandwidth limitations. In order to stream depth data plus video data from a photo format, ensure that your AVCaptureVideoDataOutput's deliversPreviewSizedOutputBuffers property is set to YES. Likewise, to stream depth data while capturing video to a movie file using AVCaptureMovieFileOutput, call -[AVCaptureSession setSessionPreset:AVCaptureSessionPresetPhoto]. When using the photo preset, video is captured at preview resolution rather than the full sensor resolution.
 */
@property(nonatomic, readonly) NSArray<Class> *unsupportedCaptureOutputClasses API_AVAILABLE(ios(11.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos);

/*!
@property supportedMaxPhotoDimensions
@abstract
    This property lists all of the supported maximum photo dimensions for this format. The array contains CMVideoDimensions structs encoded as NSValues.

@discussion
    Enumerate all supported resolution settings for which this format may be configured to capture photos. Use these values to set AVCapturePhotoOutput.maxPhotoDimensions and AVCapturePhotoSettings.maxPhotoDimensions.
 */
@property(nonatomic, readonly) NSArray<NSValue *> *supportedMaxPhotoDimensions API_AVAILABLE(ios(16.0), macos(13.0), macCatalyst(16.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos) NS_REFINED_FOR_SWIFT;

/*!
@property secondaryNativeResolutionZoomFactors
@abstract
    Indicates zoom factors at which this device transitions to secondary native resolution modes.

@discussion
    Devices with this property have the means to switch their pixel sampling mode on the fly to produce a high-fidelity, non-upsampled images at a fixed zoom factor beyond 1.0x.
 */
@property(nonatomic, readonly) NSArray<NSNumber *> *secondaryNativeResolutionZoomFactors API_AVAILABLE(ios(16.0), macos(13.0), macCatalyst(16.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos) NS_REFINED_FOR_SWIFT;

/*!
 @property autoVideoFrameRateSupported
 @abstract
    Indicates whether the device format supports auto video frame rate.

 @discussion
    See -[AVCaptureDevice autoVideoFrameRateEnabled] (above) for a detailed description of the feature.
 */
@property(nonatomic, readonly, getter=isAutoVideoFrameRateSupported) BOOL autoVideoFrameRateSupported API_AVAILABLE(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

@end


API_AVAILABLE(macos(10.7), ios(7.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDeviceFormat (AVCaptureDeviceFormatDepthDataAdditions)

/*
 @property portraitEffectsMatteStillImageDeliverySupported
 @abstract
    Indicates whether this depth format supports the delivery of a portrait effects matte.
 
 @discussion
    Some depth formats are capable of producing an auxiliary matting image (similar to an auxiliary depth image) tuned for high quality portrait effects rendering (see AVPortraitEffectsMatte.h). If this property's value is YES, you may request portrait effects matte delivery in your photos using the AVCapturePhotoOutput, provided this format is selected as the activeDepthDataFormat.
 */
@property(nonatomic, readonly, getter=isPortraitEffectsMatteStillImageDeliverySupported) BOOL portraitEffectsMatteStillImageDeliverySupported API_AVAILABLE(ios(12.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

@end


API_AVAILABLE(macos(10.7), ios(7.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDeviceFormat (AVCaptureDeviceFormatMultiCamAdditions)

/*!
 @property multiCamSupported
 @abstract
    A property indicating whether this format is supported in an AVCaptureMultiCamSession.
 
 @discussion
   When using an AVCaptureSession (single camera capture), any of the formats in the device's -formats array may be set as the -activeFormat. However, when used with an AVCaptureMultiCamSession, the device's -activeFormat may only be set to one of the formats for which multiCamSupported answers YES. This limited subset of capture formats are known to run sustainably in a multi camera capture scenario.
 */
@property(nonatomic, readonly, getter=isMultiCamSupported) BOOL multiCamSupported API_AVAILABLE(ios(13.0), macCatalyst(14.0), tvos(17.0), visionos(2.1)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos);

@end


API_AVAILABLE(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDeviceFormat (AVCaptureDeviceFormatSpatialVideoCapture)

/*!
 @property spatialVideoCaptureSupported
 @abstract
    Returns whether or not the format supports capturing spatial video to a file.
 */
@property(nonatomic, readonly, getter=isSpatialVideoCaptureSupported) BOOL spatialVideoCaptureSupported;

@end


API_AVAILABLE(macos(10.7), ios(7.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDeviceFormat (AVCaptureDeviceFormatGeometricDistortionCorrection)

/*!
 @property geometricDistortionCorrectedVideoFieldOfView
 @abstract
    A property indicating the format's horizontal field of view post geometric distortion correction.
 
 @discussion
    If the receiver's AVCaptureDevice does not support GDC, geometricDistortionCorrectedVideoFieldOfView matches the videoFieldOfView property.
 */
@property(nonatomic, readonly) float geometricDistortionCorrectedVideoFieldOfView API_AVAILABLE(ios(13.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

@end


API_AVAILABLE(macos(10.7), ios(7.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDeviceFormat (AVCaptureDeviceFormatCenterStage)

/*!
 @property centerStageSupported
 @abstract
    Indicates whether the format supports the Center Stage feature.
 
 @discussion
    This property returns YES if the format supports "Center Stage", which automatically adjusts the camera to keep people optimally framed within the field of view. See +AVCaptureDevice.centerStageEnabled for a detailed discussion.
 */
@property(nonatomic, readonly, getter=isCenterStageSupported) BOOL centerStageSupported API_AVAILABLE(macos(12.3), ios(14.5), macCatalyst(14.5), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @property videoMinZoomFactorForCenterStage
 @abstract
    Indicates the minimum zoom factor available for the AVCaptureDevice's videoZoomFactor property when centerStageActive is YES.
 
 @discussion
    Devices support a limited zoom range when Center Stage is active. If this device format does not support Center Stage, this property returns 1.0.
 */
@property(nonatomic, readonly) CGFloat videoMinZoomFactorForCenterStage API_AVAILABLE(macos(12.3), ios(14.5), macCatalyst(14.5), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @property videoMaxZoomFactorForCenterStage
 @abstract
    Indicates the maximum zoom factor available for the AVCaptureDevice's videoZoomFactor property when centerStageActive is YES.
 
 @discussion
    Devices support a limited zoom range when Center Stage is active. If this device format does not support Center Stage, this property returns videoMaxZoomFactor.
 */
@property(nonatomic, readonly) CGFloat videoMaxZoomFactorForCenterStage API_AVAILABLE(macos(12.3), ios(14.5), macCatalyst(14.5), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @property videoFrameRateRangeForCenterStage
 @abstract
    Indicates the minimum / maximum frame rates available when centerStageActive is YES.
 
 @discussion
    Devices may support a limited frame rate range when Center Stage is active. If this device format does not support Center Stage, this property returns nil.
 */
@property(nonatomic, readonly, nullable) AVFrameRateRange *videoFrameRateRangeForCenterStage API_AVAILABLE(macos(12.3), ios(14.5), macCatalyst(14.5), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

@end


API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDeviceFormat (AVCaptureDeviceFormatPortraitEffect)

/*!
 @property portraitEffectSupported
 @abstract
    Indicates whether the format supports the Portrait Effect feature.
 
 @discussion
    This property returns YES if the format supports Portrait Effect, the application of a shallow depth of field effect to objects in the background. See +AVCaptureDevice.portraitEffectEnabled for a detailed discussion.
 */
@property(nonatomic, readonly, getter=isPortraitEffectSupported) BOOL portraitEffectSupported API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @property videoFrameRateRangeForPortraitEffect
 @abstract
    Indicates the minimum / maximum frame rates available when portraitEffectActive is YES.
 
 @discussion
    Devices may support a limited frame rate range when Portrait Effect is active. If this device format does not support Portrait Effect, this property returns nil.
 */
@property(nonatomic, readonly, nullable) AVFrameRateRange *videoFrameRateRangeForPortraitEffect API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

@end


API_AVAILABLE(macos(13.0), ios(16.0), macCatalyst(16.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDevice (AVCaptureDeviceStudioLight)

/*!
 @property studioLightEnabled
 @abstract
    A class property indicating whether the Studio Light feature is currently enabled in Control Center.
 
 @discussion
    This property changes to reflect the Studio Light state in Control Center. It is key-value observable.  On iOS, Studio Light only applies to video conferencing apps by default (apps that use "voip" as one of their UIBackgroundModes). Non video conferencing apps may opt in for Studio Light by adding the following key to their Info.plist:
        <key>NSCameraStudioLightEnabled</key>
        <true/>
 */
@property(class, readonly, getter=isStudioLightEnabled) BOOL studioLightEnabled API_AVAILABLE(macos(13.0), ios(16.0), macCatalyst(16.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @property studioLightActive
 @abstract
    Indicates whether Studio Light is currently active on a particular AVCaptureDevice.
 
 @discussion
    This readonly property returns YES when Studio Light is currently active on the receiver. When active, the subject's face is artificially lit to simulate the presence of a studio light near the camera.
 */
@property(nonatomic, readonly, getter=isStudioLightActive) BOOL studioLightActive API_AVAILABLE(macos(13.0), ios(16.0), macCatalyst(16.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

@end

API_AVAILABLE(macos(13.0), ios(16.0), macCatalyst(16.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDeviceFormat (AVCaptureDeviceFormatStudioLight)

/*!
 @property studioLightSupported
 @abstract
    Indicates whether the format supports the Studio Light feature.
 
 @discussion
    This property returns YES if the format supports Studio Light (artificial re-lighting of the subject's face). See +AVCaptureDevice.studioLightEnabled.
 */
@property(nonatomic, readonly, getter=isStudioLightSupported) BOOL studioLightSupported API_AVAILABLE(macos(13.0), ios(16.0), macCatalyst(16.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @property videoFrameRateRangeForStudioLight
 @abstract
    Indicates the minimum / maximum frame rates available when studioLight is YES.
 
 @discussion
    Devices may support a limited frame rate range when Studio Light is active. If this device format does not support Studio Light, this property returns nil.
 */
@property(nonatomic, readonly, nullable) AVFrameRateRange *videoFrameRateRangeForStudioLight API_AVAILABLE(macos(13.0), ios(16.0), macCatalyst(16.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

@end


API_AVAILABLE(macos(14.0), ios(17.0), macCatalyst(17.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDeviceFormat (AVCaptureDeviceFormatReactionEffects)

/*!
 @property reactionEffectsSupported
 @abstract
    Indicates whether the format supports the Reaction Effects feature.
 
 @discussion
    This property returns YES if the format supports Reaction Effects. See +AVCaptureDevice.reactionEffectsEnabled.
 */
@property(nonatomic, readonly) BOOL reactionEffectsSupported API_AVAILABLE(macos(14.0), ios(17.0), macCatalyst(17.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @property videoFrameRateRangeForReactionEffectsInProgress
 @abstract
    Indicates the minimum / maximum frame rates available when a reaction effect is running.
 
 @discussion
    Unlike the other video effects, enabling reaction effects does not limit the stream's frame rate because most of the time no rendering is being performed. The frame rate will only ramp down when a reaction is actually being rendered on the stream (see AVCaptureDevice.reactionEffectsInProgress)
 */
@property(nonatomic, readonly, nullable) AVFrameRateRange *videoFrameRateRangeForReactionEffectsInProgress API_AVAILABLE(macos(14.0), ios(17.0), macCatalyst(17.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

@end


API_AVAILABLE(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDeviceFormat (AVCaptureDeviceFormatBackgroundReplacement)

/*!
 @property backgroundReplacementSupported
 @abstract
    Indicates whether the format supports the Background Replacement feature.
 
 @discussion
    This property returns YES if the format supports Background Replacement background replacement. See +AVCaptureDevice.backgroundReplacementEnabled.
 */
@property(nonatomic, readonly, getter=isBackgroundReplacementSupported) BOOL backgroundReplacementSupported API_AVAILABLE(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @property videoFrameRateRangeForBackgroundReplacement
 @abstract
    Indicates the minimum / maximum frame rates available when background replacement is active.
 
 @discussion
    Devices may support a limited frame rate range when Background Replacement is active. If this device format does not support Background Replacement, this property returns nil.
 */
@property(nonatomic, readonly, nullable) AVFrameRateRange *videoFrameRateRangeForBackgroundReplacement API_AVAILABLE(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

@end


API_AVAILABLE(macos(26.2), ios(26.2), macCatalyst(26.2), tvos(26.2)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDevice (AVCaptureDeviceEdgeLight)

/// A class property indicating whether the Edge Light feature is currently enabled in Control Center.
///
/// This readonly property changes to reflect the Edge Light state in Control Center. It is key-value observable.
@property(class, readonly, getter=isEdgeLightEnabled) BOOL edgeLightEnabled API_AVAILABLE(macos(26.2), ios(26.2), macCatalyst(26.2), tvos(26.2)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// A class property indicating whether the edge light UI is actively being shown on a screen.
///
/// This readonly property reflects whether the edge light UI is actively being shown on a screen. It is key-value observable.
@property(class, readonly, getter=isEdgeLightActive) BOOL edgeLightActive API_AVAILABLE(macos(26.2), ios(26.2), macCatalyst(26.2), tvos(26.2)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

@end


API_AVAILABLE(macos(26.2), ios(26.2), macCatalyst(26.2), tvos(26.2)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDeviceFormat (AVCaptureDeviceFormatEdgeLight)

/// Indicates whether the format supports the Edge Light feature.
///
/// This property returns YES if the device supports the Edge Light feature. See +AVCaptureDevice.edgeLightEnabled.
@property(nonatomic, readonly, getter=isEdgeLightSupported) BOOL edgeLightSupported API_AVAILABLE(macos(26.2), ios(26.2), macCatalyst(26.2), tvos(26.2)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

@end


API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDeviceFormat (AVCaptureDeviceFormatCinematicVideoSupport)

/// Indicates whether the format supports Cinematic Video capture.
///
///This property returns `true` if the format supports Cinematic Video that produces a controllable, simulated depth of field and adds beautiful focus transitions for a cinema-grade look.
@property(nonatomic, readonly, getter=isCinematicVideoCaptureSupported) BOOL cinematicVideoCaptureSupported API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// Default shallow depth of field simulated aperture.
///
/// This property return a non-zero value on devices that support the shallow depth of field effect.
@property(nonatomic, readonly) float defaultSimulatedAperture API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// Minimum supported shallow depth of field simulated aperture.
///
/// On devices that do not support changing the simulated aperture value, this returns a value of `0`.
@property(nonatomic, readonly) float minSimulatedAperture API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// Maximum supported shallow depth of field simulated aperture.
///
/// On devices that do not support changing the simulated aperture value, this returns a value of `0`.
@property(nonatomic, readonly) float maxSimulatedAperture API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// Indicates the minimum zoom factor available for the ``AVCaptureDevice/videoZoomFactor`` property when Cinematic Video capture is enabled on the device input.
///
/// Devices support a limited zoom range when Cinematic Video capture is active. If this device format does not support Cinematic Video capture, this property returns `1.0`.
@property(nonatomic, readonly) CGFloat videoMinZoomFactorForCinematicVideo API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// Indicates the maximum zoom factor available for the ``AVCaptureDevice/videoZoomFactor`` property when Cinematic Video capture is enabled on the device input.
///
/// Devices support a limited zoom range when Cinematic Video capture is active. If this device format does not support Cinematic Video capture, this property returns `1.0`.
@property(nonatomic, readonly) CGFloat videoMaxZoomFactorForCinematicVideo API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// Indicates the minimum / maximum frame rates available when Cinematic Video capture is enabled on the device input.
///
/// Devices may support a limited frame rate range when Cinematic Video capture is active. If this device format does not support Cinematic Video capture, this property returns `nil`.
@property(nonatomic, readonly, nullable) AVFrameRateRange *videoFrameRateRangeForCinematicVideo API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

@end

API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, macCatalyst, tvos, visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDeviceFormat (DynamicAspectRatio)

/// Indicates the supported aspect ratios for the device format.
///
/// An array that describes the aspect ratios that are supported for this format. If this device format does not support dynamic aspect ratio, this property returns an empty array.
@property(readonly, copy) NSArray<AVCaptureAspectRatio> *supportedDynamicAspectRatios;

/// Indicates the horizontal field of view for an aspect ratio, either uncorrected or corrected for geometric distortion.
///
/// A float indicating the field of view for the corresponding ``AVCaptureAspectRatio``. Set ``AVCaptureDevice/geometricDistortionCorrected`` to `true` to receive the field of view corrected for geometric distortion. If this device format does not support dynamic aspect ratio, this function returns `0`.
- (float)videoFieldOfViewForAspectRatio:(AVCaptureAspectRatio)aspectRatio geometricDistortionCorrected:(BOOL)geometricDistortionCorrected NS_SWIFT_NAME(videoFieldOfView(for:geometricDistortionCorrected:));

@end

API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, macCatalyst, tvos, visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDeviceFormat (AVCaptureDeviceFormatSmartFraming)

/// Returns `true` if smart framing is supported by the current format.
///
/// An ultra wide camera device that supports dynamic aspect ratio configuration may also support "smart framing monitoring" on particular formats.
@property(nonatomic, readonly, getter=isSmartFramingSupported) BOOL smartFramingSupported;

@end

API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDeviceFormat (CameraLensSmudgeDetection)

/// Whether camera lens smudge detection is supported.
///
/// This property returns `true` if the session's current configuration supports lens smudge detection. When switching cameras or formats, this property may change. When this property changes from `true` to `false`, ``AVCaptureDevice/cameraLensSmudgeDetectionEnabled`` also reverts to `false`. If you opt in for lens smudge detection and then change configurations, you should set ``AVCaptureDevice/cameraLensSmudgeDetectionEnabled`` to `true` again.
@property(nonatomic, readonly, getter=isCameraLensSmudgeDetectionSupported) BOOL cameraLensSmudgeDetectionSupported API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

@end

API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureDevice (CameraLensSmudgeDetection)

/// Specify whether to enable camera lens smudge detection, and the interval time between each run of detections.
///
/// - Parameter cameraLensSmudgeDetectionEnabled: Specify whether camera lens smudge detection should be enabled.
/// - Parameter detectionInterval: The detection running interval if detection is enabled.
///
/// Each run of detection processes frames over a short period, and produces one detection result. Use `detectionInterval` to specify the interval time between each run of detections. For example, when ``cameraLensSmudgeDetectionEnabled`` is set to `true` and `detectionInterval` is set to 1 minute, detection runs once per minute, and updates ``AVCaptureCameraLensSmudgeDetectionStatus``. If `detectionInterval` is set to ``kCMTimeInvalid``, detection runs only once after the session starts. If `detectionInterval` is set to ``kCMTimeZero``, detection runs continuously.
///
/// ``AVCaptureDevice`` throws an `NSInvalidArgumentException` if the ``AVCaptureDeviceFormat/cameraLensSmudgeDetectionSupported`` property on the current active format returns `false`. Enabling detection requires a lengthy reconfiguration of the capture render pipeline, so you should enable detection before calling ``AVCaptureSession/startRunning`` or within ``AVCaptureSession/beginConfiguration`` and ``AVCaptureSession/commitConfiguration`` while running.
- (void)setCameraLensSmudgeDetectionEnabled:(BOOL)cameraLensSmudgeDetectionEnabled detectionInterval:(CMTime)detectionInterval API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// Whether camera lens smudge detection is enabled.
///
/// You enable lens smudge detection by calling ``setCameraLensSmudgeDetectionEnabled:detectionInterval:``. By default, this property is returns `false`.
@property(nonatomic, readonly, getter=isCameraLensSmudgeDetectionEnabled) BOOL cameraLensSmudgeDetectionEnabled API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// The camera lens smudge detection interval.
///
/// ``cameraLensSmudgeDetectionInterval`` is set by calling ``setCameraLensSmudgeDetectionEnabled:detectionInterval:``. By default, this property returns `kCMTimeInvalid`.
@property(nonatomic, readonly) CMTime cameraLensSmudgeDetectionInterval API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// Constants indicating the current camera lens smudge detection status.
typedef NS_ENUM(NSInteger, AVCaptureCameraLensSmudgeDetectionStatus) {
    /// Indicates that the detection is not enabled.
    AVCaptureCameraLensSmudgeDetectionStatusDisabled            = 0,
    /// Indicates that the most recent detection found no smudge on the camera lens.
    AVCaptureCameraLensSmudgeDetectionStatusSmudgeNotDetected   = 1,
    /// Indicates that the most recent detection found the camera lens to be smudged.
    AVCaptureCameraLensSmudgeDetectionStatusSmudged             = 2,
    /// Indicates that the detection result has not settled, commonly caused by excessive camera movement or the content of the scene.
    AVCaptureCameraLensSmudgeDetectionStatusUnknown             = 3,
} API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// A value specifying the status of camera lens smudge detection.
///
/// During initial detection execution, ``cameraLensSmudgeDetectionStatus`` returns ``AVCaptureCameraLensSmudgeDetectionStatusUnknown`` until the detection result settles. Once a detection result is produced, ``cameraLensSmudgeDetectionStatus`` returns the most recent detection result. This property can be key-value observed.
@property(nonatomic, readonly) AVCaptureCameraLensSmudgeDetectionStatus cameraLensSmudgeDetectionStatus API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

@end

#pragma mark - AVCaptureDeviceInputSource

@class AVCaptureDeviceInputSourceInternal;

/*!
 @class AVCaptureDeviceInputSource
 @abstract
    An AVCaptureDeviceInputSource represents a distinct input source on an AVCaptureDevice object.
 
 @discussion
    An AVCaptureDevice may optionally present an array of inputSources, representing distinct mutually exclusive inputs to the device, for example, an audio AVCaptureDevice might have ADAT optical and analog input sources. A video AVCaptureDevice might have an HDMI input source, or a component input source.
 */
API_AVAILABLE(macos(10.7)) API_UNAVAILABLE(ios, macCatalyst, watchos, tvos, visionos)
@interface AVCaptureDeviceInputSource : NSObject
{
@private
    AVCaptureDeviceInputSourceInternal *_internal;
}

AV_INIT_UNAVAILABLE

/*!
 @property inputSourceID
 @abstract
    An ID unique among the inputSources exposed by a given AVCaptureDevice.
 
 @discussion
    An AVCaptureDevice's inputSources array must contain AVCaptureInputSource objects with unique inputSourceIDs.
 */
@property(nonatomic, readonly) NSString *inputSourceID;

/*!
 @property localizedName
 @abstract
    A localized human-readable name for the receiver.
 
 @discussion
    This property can be used for displaying the name of the capture device input source in a user interface.
 */
@property(nonatomic, readonly) NSString *localizedName;

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCapture/AVCaptureDevice.h>
#endif
