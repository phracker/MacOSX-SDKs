#if !__has_include(<AVFCapture/AVCaptureDevice.h>)
/*
    File:  AVCaptureDevice.h
 
    Framework:  AVFoundation
 
    Copyright 2010-2021 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVCaptureSessionPreset.h>
#import <AVFoundation/AVMediaFormat.h>
#import <Foundation/Foundation.h>
#import <CoreMedia/CMFormatDescription.h>
#import <CoreGraphics/CGBase.h>
#import <CoreGraphics/CGGeometry.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @constant AVCaptureDeviceWasConnectedNotification
 @abstract
    Posted when a device becomes available on the system.
 
 @discussion
    The notification object is an AVCaptureDevice instance representing the device that became available.
 */
AVF_EXPORT NSString *const AVCaptureDeviceWasConnectedNotification API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 @constant AVCaptureDeviceWasDisconnectedNotification
 @abstract
    Posted when a device becomes unavailable on the system.
 
 @discussion
    The notification object is an AVCaptureDevice instance representing the device that became unavailable.
 */
AVF_EXPORT NSString *const AVCaptureDeviceWasDisconnectedNotification API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 @constant AVCaptureDeviceSubjectAreaDidChangeNotification
 @abstract
    Posted when the instance of AVCaptureDevice has detected a substantial change to the video subject area.
 
 @discussion
    Clients may observe the AVCaptureDeviceSubjectAreaDidChangeNotification to know when an instance of AVCaptureDevice has detected a substantial change to the video subject area. This notification is only sent if you first set subjectAreaChangeMonitoringEnabled to YES.
  */
AVF_EXPORT NSString *const AVCaptureDeviceSubjectAreaDidChangeNotification API_AVAILABLE(ios(5.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;


#pragma mark - AVCaptureDevice

@class AVCaptureDeviceFormat;
@class AVCaptureDeviceInputSource;
@class AVCaptureSystemPressureState;
@class AVCaptureDeviceInternal;

/*!
 @class AVCaptureDevice
 @abstract
    An AVCaptureDevice represents a physical device that provides realtime input media data, such as video and audio.
 
 @discussion
    Each instance of AVCaptureDevice corresponds to a device, such as a camera or microphone. Instances of AVCaptureDevice cannot be created directly. An array of all currently available devices can also be obtained using the AVCaptureDeviceDiscoverySession. Devices can provide one or more streams of a given media type. Applications can search for devices matching desired criteria by using AVCaptureDeviceDiscoverySession, or may obtain a reference to the default device matching desired criteria by using +[AVCaptureDevice defaultDeviceWithDeviceType:mediaType:position:].
 
    Instances of AVCaptureDevice can be used to provide media data to an AVCaptureSession by creating an AVCaptureDeviceInput with the device and adding that to the capture session.
 */
API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
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
+ (NSArray<AVCaptureDevice *> *)devices API_DEPRECATED("Use AVCaptureDeviceDiscoverySession instead.", ios(4.0, 10.0), macos(10.7, 10.15)) API_UNAVAILABLE(tvos);

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
+ (NSArray<AVCaptureDevice *> *)devicesWithMediaType:(AVMediaType)mediaType API_DEPRECATED("Use AVCaptureDeviceDiscoverySession instead.", ios(4.0, 10.0), macos(10.7, 10.15)) API_UNAVAILABLE(tvos);

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
+ (nullable AVCaptureDevice *)defaultDeviceWithMediaType:(AVMediaType)mediaType;

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
+ (nullable AVCaptureDevice *)deviceWithUniqueID:(NSString *)deviceUniqueID;

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
@property(nonatomic, readonly) NSString *modelID;

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
@property(nonatomic, readonly) NSString *manufacturer API_AVAILABLE(macos(10.9), ios(14.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

/*!
 @property transportType
 @abstract
    The transport type of the receiver (e.g. USB, PCI, etc).
 
 @discussion
    This property can be used to discover the transport type of a capture device. Transport types are defined in <IOKit/audio/IOAudioTypes.h> as kIOAudioDeviceTransportType*.
 */
@property(nonatomic, readonly) int32_t transportType API_UNAVAILABLE(ios, macCatalyst, watchos, tvos);

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
- (BOOL)supportsAVCaptureSessionPreset:(AVCaptureSessionPreset)preset;

/*!
 @property connected
 @abstract
    Indicates whether the device is connected and available to the system.
 
 @discussion
    The value of this property is a BOOL indicating whether the device represented by the receiver is connected and available for use as a capture device. Clients can key value observe the value of this property to be notified when a device is no longer available. When the value of this property becomes NO for a given instance, it will not become YES again. If the same physical device again becomes available to the system, it will be represented using a new instance of AVCaptureDevice.
 */
@property(nonatomic, readonly, getter=isConnected) BOOL connected;

/*!
 @property inUseByAnotherApplication
 @abstract
    Indicates whether the device is in use by another application.
 
 @discussion
    The value of this property is a BOOL indicating whether the device represented by the receiver is in use by another application. Clients can key value observe the value of this property to be notified when another app starts or stops using this device.
 */
@property(nonatomic, readonly, getter=isInUseByAnotherApplication) BOOL inUseByAnotherApplication API_AVAILABLE(macCatalyst(14.0)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 @property suspended
 @abstract
    Indicates whether the device is suspended.
 
 @discussion
    The value of this property is a BOOL indicating whether the device represented by the receiver is currently suspended. Some devices disallow data capture due to a feature on the device. For example, isSuspended returns YES for the external iSight when its privacy iris is closed, or for the internal iSight on a notebook when the notebook's display is closed. Clients can key value observe the value of this property to be notified when the device becomes suspended or unsuspended.
 */
@property(nonatomic, readonly, getter=isSuspended) BOOL suspended API_AVAILABLE(ios(14.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

/*!
 @property linkedDevices
 @abstract
    An array of AVCaptureDevice objects physically linked to the receiver.
 
 @discussion
    The value of this property is an array of AVCaptureDevice objects that are a part of the same physical device as the receiver. For example, for the external iSight camera, linkedDevices returns an array containing an AVCaptureDevice for the external iSight microphone.
 */
@property(nonatomic, readonly) NSArray<AVCaptureDevice *> *linkedDevices API_UNAVAILABLE(ios, macCatalyst, watchos, tvos);

/*!
 @property formats
 @abstract
    An array of AVCaptureDeviceFormat objects supported by the receiver.
 
 @discussion
    This property can be used to enumerate the formats natively supported by the receiver. The capture device's activeFormat property may be set to one of the formats in this array. Clients can observe automatic changes to the receiver's formats by key value observing this property.
 */
@property(nonatomic, readonly) NSArray<AVCaptureDeviceFormat *> *formats API_AVAILABLE(ios(7.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos);

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
@property(nonatomic, retain) AVCaptureDeviceFormat *activeFormat API_AVAILABLE(ios(7.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos);

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
 */
@property(nonatomic) CMTime activeVideoMinFrameDuration API_AVAILABLE(ios(7.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos);

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
 */
@property(nonatomic) CMTime activeVideoMaxFrameDuration API_AVAILABLE(macos(10.9), ios(7.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos);

/*!
 @property inputSources
 @abstract
    An array of AVCaptureDeviceInputSource objects supported by the receiver.
 
 @discussion
    Some devices can capture data from one of multiple data sources (different input jacks on the same audio device, for example). For devices with multiple possible data sources, inputSources can be used to enumerate the possible choices. Clients can observe automatic changes to the receiver's inputSources by key value observing this property.
 */
@property(nonatomic, readonly) NSArray<AVCaptureDeviceInputSource *> *inputSources API_UNAVAILABLE(ios, macCatalyst, watchos, tvos);

/*!
 @property activeInputSource
 @abstract
    The currently active input source of the receiver.
 
 @discussion
    This property can be used to get or set the currently active device input source. -setActiveInputSource: throws an NSInvalidArgumentException if set to a value not present in the inputSources array. -setActiveInputSource: throws an NSGenericException if called without first obtaining exclusive access to the receiver using lockForConfiguration:. Clients can observe automatic changes to the receiver's activeInputSource by key value observing this property.
 */
@property(nonatomic, retain, nullable) AVCaptureDeviceInputSource *activeInputSource API_UNAVAILABLE(ios, macCatalyst, watchos, tvos);

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
} API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;


API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
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
typedef NSString *AVCaptureDeviceType NS_TYPED_ENUM API_AVAILABLE(macos(10.15), ios(10.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 @constant AVCaptureDeviceTypeExternalUnknown
    An unknown device type.
 */
AVF_EXPORT AVCaptureDeviceType const AVCaptureDeviceTypeExternalUnknown API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, macCatalyst, watchos, tvos);

/*!
 @constant AVCaptureDeviceTypeBuiltInMicrophone
    A built-in microphone.
 */
AVF_EXPORT AVCaptureDeviceType const AVCaptureDeviceTypeBuiltInMicrophone API_AVAILABLE(macos(10.15), ios(10.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 @constant AVCaptureDeviceTypeBuiltInWideAngleCamera
    A built-in wide angle camera device. These devices are suitable for general purpose use.
 */
AVF_EXPORT AVCaptureDeviceType const AVCaptureDeviceTypeBuiltInWideAngleCamera API_AVAILABLE(macos(10.15), ios(10.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 @constant AVCaptureDeviceTypeBuiltInTelephotoCamera
    A built-in camera device with a longer focal length than a wide angle camera. Note that devices of this type may only be discovered using an AVCaptureDeviceDiscoverySession.
 */
AVF_EXPORT AVCaptureDeviceType const AVCaptureDeviceTypeBuiltInTelephotoCamera API_AVAILABLE(ios(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 @constant AVCaptureDeviceTypeBuiltInUltraWideCamera
    A built-in camera device with a shorter focal length than a wide angle camera. Note that devices of this type may only be discovered using an AVCaptureDeviceDiscoverySession.
 */
AVF_EXPORT AVCaptureDeviceType const AVCaptureDeviceTypeBuiltInUltraWideCamera API_AVAILABLE(ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

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
AVF_EXPORT AVCaptureDeviceType const AVCaptureDeviceTypeBuiltInDualCamera API_AVAILABLE(ios(10.2), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

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
AVF_EXPORT AVCaptureDeviceType const AVCaptureDeviceTypeBuiltInDualWideCamera API_AVAILABLE(ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

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
AVF_EXPORT AVCaptureDeviceType const AVCaptureDeviceTypeBuiltInTripleCamera API_AVAILABLE(ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @constant AVCaptureDeviceTypeBuiltInTrueDepthCamera
    A device that consists of two cameras, one YUV and one Infrared. The infrared camera provides high quality depth information that is synchronized and perspective corrected to frames produced by the YUV camera. While the resolution of the depth data and YUV frames may differ, their field of view and aspect ratio always match. Note that devices of this type may only be discovered using an AVCaptureDeviceDiscoverySession or -[AVCaptureDevice defaultDeviceWithDeviceType:mediaType:position:].
 */
AVF_EXPORT AVCaptureDeviceType const AVCaptureDeviceTypeBuiltInTrueDepthCamera API_AVAILABLE(ios(11.1), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 @constant AVCaptureDeviceTypeBuiltInDuoCamera
    A deprecated synonym for AVCaptureDeviceTypeBuiltInDualCamera. Please use AVCaptureDeviceTypeBuiltInDualCamera instead.
 */
AVF_EXPORT AVCaptureDeviceType const AVCaptureDeviceTypeBuiltInDuoCamera API_DEPRECATED("Use AVCaptureDeviceTypeBuiltInDualCamera instead.", ios(10.0, 10.2)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;


API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface AVCaptureDevice (AVCaptureDeviceType)

/*!
 @property deviceType
 @abstract
    The type of the capture device.
 
 @discussion
    A capture device's type never changes.
 */
@property(nonatomic, readonly) AVCaptureDeviceType deviceType API_AVAILABLE(macos(10.15), ios(10.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos);

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
+ (nullable AVCaptureDevice *)defaultDeviceWithDeviceType:(AVCaptureDeviceType)deviceType mediaType:(nullable AVMediaType)mediaType position:(AVCaptureDevicePosition)position API_AVAILABLE(macos(10.15), ios(10.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos);

@end


API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface AVCaptureDevice (AVCaptureDeviceSystemPressure)

/*!
 @property systemPressureState
 @abstract
    A key-value observable property indicating the capture device's current system pressure state.
 
 @discussion
    This property indicates whether the capture device is currently subject to an elevated system pressure condition. When system pressure reaches AVCaptureSystemPressureLevelShutdown, the capture device cannot continue to provide input, so the AVCaptureSession becomes interrupted until the pressured state abates. System pressure can be effectively mitigated by lowering the device's activeVideoMinFrameDuration in response to changes in the systemPressureState. Clients are encouraged to implement frame rate throttling to bring system pressure down if their capture use case can tolerate a reduced frame rate.
 */
@property(nonatomic, readonly) AVCaptureSystemPressureState *systemPressureState API_AVAILABLE(ios(11.1), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

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
} NS_SWIFT_NAME(AVCaptureDevice.PrimaryConstituentDeviceSwitchingBehavior) API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

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
} NS_SWIFT_NAME(AVCaptureDevice.PrimaryConstituentDeviceRestrictedSwitchingBehaviorConditions) API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
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
@property(nonatomic, readonly, getter=isVirtualDevice) BOOL virtualDevice API_AVAILABLE(ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @property constituentDevices
 @abstract
    An array of constituent physical devices comprising a virtual device.
 
 @discussion
    When called on a device for which virtualDevice == NO, an empty array is returned.
 */
@property(nonatomic, readonly) NSArray<AVCaptureDevice *> *constituentDevices API_AVAILABLE(ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @property virtualDeviceSwitchOverVideoZoomFactors
 @abstract
    An array of video zoom factors at or above which a virtual device (such as the Dual Camera) may switch to its next constituent device.
 
 @discussion
    This array contains zoom factors at which one of the constituent device's field of view matches the next constituent device's full field of view. The number of switch over video zoom factors is always one less than the count of the constituentDevices property, and the factors progress in the same order as the devices listed in that property. On non-virtual devices this property returns an empty array.
 */
@property(nonatomic, readonly) NSArray<NSNumber *> *virtualDeviceSwitchOverVideoZoomFactors API_AVAILABLE(ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

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
- (void)setPrimaryConstituentDeviceSwitchingBehavior:(AVCapturePrimaryConstituentDeviceSwitchingBehavior)switchingBehavior restrictedSwitchingBehaviorConditions:(AVCapturePrimaryConstituentDeviceRestrictedSwitchingBehaviorConditions)restrictedSwitchingBehaviorConditions API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

/*!
 @property primaryConstituentDeviceSwitchingBehavior
 @abstract
    The primaryConstituentDeviceSwitchingBehavior as set by -[AVCaptureDevice setPrimaryConstituentDeviceSwitchingBehavior:restrictedSwitchingBehaviorConditions:].
 
 @discussion
    By default, this property is set to AVCapturePrimaryConstituentDeviceSwitchingBehaviorAuto for AVCaptureDevices that support it.  This property is key-value observable.
 */
@property(nonatomic, readonly) AVCapturePrimaryConstituentDeviceSwitchingBehavior primaryConstituentDeviceSwitchingBehavior API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

/*!
 @property primaryConstituentDeviceRestrictedSwitchingBehaviorConditions
 @abstract
    The primaryConstituentDeviceRestrictedSwitchingBehaviorConditions as set by -[AVCaptureDevice setPrimaryConstituentDeviceSwitchingBehavior:restrictedSwitchingBehaviorConditions:].
 
 @discussion
    By default, this propety is set to AVCapturePrimaryConstituentDeviceRestrictedSwitchingBehaviorConditionNone. This property is key-value observable.
 */
@property(nonatomic, readonly) AVCapturePrimaryConstituentDeviceRestrictedSwitchingBehaviorConditions primaryConstituentDeviceRestrictedSwitchingBehaviorConditions API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

/*!
 @property activePrimaryConstituentDeviceSwitchingBehavior
 @abstract
    The active constituent device switching behavior.
 
 @discussion
    For virtual devices with multiple constituent devices, this property returns the active switching behavior. This is equal to primaryConstituentDeviceSwitchingBehavior except while recording using an AVCaptureMovieFileOutput configured with a different switching behavior (see -[AVCaptureMovieFileOutput setPrimaryConstituentDeviceSwitchingBehavior:restrictedSwitchingBehaviorConditions]). Devices that do not support constituent device switching return AVCapturePrimaryConstituentDeviceSwitchingBehaviorUnsupported. This property is key-value observable.
 */
@property(nonatomic, readonly) AVCapturePrimaryConstituentDeviceSwitchingBehavior activePrimaryConstituentDeviceSwitchingBehavior API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

/*!
 @property activePrimaryConstituentDeviceRestrictedSwitchingBehaviorConditions
 @abstract
    The active constituent device restricted  switching behavior.
 
 @discussion
    For virtual devices with multiple constituent devices, this property returns the active restricted switching behavior conditions. This is equal to primaryConstituentDeviceRestrictedSwitchingBehaviorConditions except while recording using an AVCaptureMovieFileOutput configured with different retricted switching behavior conditions (see -[AVCaptureMovieFileOutput setPrimaryConstituentDeviceSwitchingBehaviorForRecording:restrictedSwitchingBehaviorConditions]). Devices that do not support constituent device switching return AVCapturePrimaryConstituentDeviceRestrictedSwitchingBehaviorConditionNone. This property is key-value observable.
 */
@property(nonatomic, readonly) AVCapturePrimaryConstituentDeviceRestrictedSwitchingBehaviorConditions activePrimaryConstituentDeviceRestrictedSwitchingBehaviorConditions API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

/*!
 @property activePrimaryConstituentDevice
 @abstract
    For virtual devices, this property indicates which constituent device is currently the primary constituent device. The primary constituent device may change when zoom, exposure, or focus changes.
 
 @discussion
    This property returns nil for non-virtual devices. This property is key-value observable.
 */
@property(nonatomic, readonly, nullable) AVCaptureDevice *activePrimaryConstituentDevice API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

/*!
 @property supportedFallbackPrimaryConstituentDevices
 @abstract
    The constituent devices that may be selected as a fallback for a longer focal length primary constituent device.
 
 @discussion
    This property returns an empty array for non-virtual devices. This property never changes for a given virtual device.
 */
@property(nonatomic, readonly) NSArray<AVCaptureDevice *> *supportedFallbackPrimaryConstituentDevices API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

/*!
 @property fallbackPrimaryConstituentDevices
 @abstract
    The constituent devices that may be used as a fallback device when a constituent device with a longer focal length becomes limited by its light sensitivity or minimum focus distance.
 
 @discussion
    This may only be set to the supportedFallbackPrimaryConstituentDevices or a subset thereof. By default this is set to all supportedFallbackPrimaryConstituentDevices. This property will throw an NSInvalidArgumentException if the array includes any device not reported in supportedFallbackPrimaryConstituentDevices. This property is key-value observable.
 */
@property(nonatomic) NSArray<AVCaptureDevice *> *fallbackPrimaryConstituentDevices API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

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
} API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;


API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
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
@property(nonatomic, readonly, getter=isFlashAvailable) BOOL flashAvailable API_AVAILABLE(macos(10.15), ios(5.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos);

/*!
 @property flashActive
 @abstract
    Indicates whether the receiver's flash is currently active.
 
 @discussion
    The value of this property is a BOOL indicating whether the receiver's flash is currently active. When the flash is active, it will flash if a still image is captured. When a still image is captured with the flash active, exposure and white balance settings are overridden for the still. This is true even when using AVCaptureExposureModeCustom and/or AVCaptureWhiteBalanceModeLocked. This property is key-value observable.
 */
@property(nonatomic, readonly, getter=isFlashActive) BOOL flashActive API_DEPRECATED("Use AVCapturePhotoOutput's -isFlashScene instead.", ios(5.0, 10.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos);

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
- (BOOL)isFlashModeSupported:(AVCaptureFlashMode)flashMode API_DEPRECATED("Use AVCapturePhotoOutput's -supportedFlashModes instead.", ios(4.0, 10.0)) API_UNAVAILABLE(tvos);

/*!
 @property flashMode
 @abstract
    Indicates current mode of the receiver's flash, if it has one.
 
 @discussion
    The value of this property is an AVCaptureFlashMode that determines the mode of the receiver's flash, if it has one. -setFlashMode: throws an NSInvalidArgumentException if set to an unsupported value (see -isFlashModeSupported:). -setFlashMode: throws an NSGenericException if called without first obtaining exclusive access to the receiver using lockForConfiguration:. Clients can observe automatic changes to the receiver's flashMode by key value observing this property.
 
    When using AVCapturePhotoOutput, AVCaptureDevice's flashMode property is ignored. You specify flashMode on a per photo basis by setting the AVCapturePhotoSettings.flashMode property.
 */
@property(nonatomic) AVCaptureFlashMode flashMode API_DEPRECATED("Use AVCapturePhotoSettings.flashMode instead.", ios(4.0, 10.0)) API_UNAVAILABLE(tvos);

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
} API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;


/*!
 @constant AVCaptureMaxAvailableTorchLevel
    A special value that may be passed to -setTorchModeWithLevel:error: to set the torch to the maximum level currently available. Under thermal duress, the maximum available torch level may be less than 1.0.
 */
AVF_EXPORT const float AVCaptureMaxAvailableTorchLevel API_AVAILABLE(macos(10.15), ios(6.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;


API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
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
@property(nonatomic, readonly, getter=isTorchAvailable) BOOL torchAvailable API_AVAILABLE(macos(10.15), ios(5.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos);

/*!
 @property torchActive
 @abstract
    Indicates whether the receiver's torch is currently active.
 
 @discussion
    The value of this property is a BOOL indicating whether the receiver's torch is currently active. If the current torchMode is AVCaptureTorchModeAuto and isTorchActive is YES, the torch will illuminate once a recording starts (see AVCaptureOutput.h -startRecordingToOutputFileURL:recordingDelegate:). This property is key-value observable.
 */
@property(nonatomic, readonly, getter=isTorchActive) BOOL torchActive API_AVAILABLE(macos(10.15), ios(6.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos);

/*!
 @property torchLevel
 @abstract
    Indicates the receiver's current torch brightness level as a floating point value.
 
 @discussion
    The value of this property is a float indicating the receiver's torch level from 0.0 (off) -> 1.0 (full). This property is key-value observable.
 */
@property(nonatomic, readonly) float torchLevel API_AVAILABLE(macos(10.15), ios(5.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos);

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
- (BOOL)setTorchModeOnWithLevel:(float)torchLevel error:(NSError * _Nullable * _Nullable)outError API_AVAILABLE(macos(10.15), ios(6.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos);

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
} API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;


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
} API_AVAILABLE(ios(7.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;


API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
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
@property(nonatomic, readonly, getter=isLockingFocusWithCustomLensPositionSupported) BOOL lockingFocusWithCustomLensPositionSupported API_AVAILABLE(ios(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

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
@property(nonatomic, readonly, getter=isAutoFocusRangeRestrictionSupported) BOOL autoFocusRangeRestrictionSupported API_AVAILABLE(ios(7.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property autoFocusRangeRestriction
 @abstract
    Indicates current restriction of the receiver's autofocus system to a particular range of focus scan, if it supports range restrictions.
 
 @discussion
    The value of this property is an AVCaptureAutoFocusRangeRestriction indicating how the autofocus system should limit its focus scan. The default value is AVCaptureAutoFocusRangeRestrictionNone. -setAutoFocusRangeRestriction: throws an NSInvalidArgumentException if isAutoFocusRangeRestrictionSupported returns NO. -setAutoFocusRangeRestriction: throws an NSGenericException if called without first obtaining exclusive access to the receiver using lockForConfiguration:. This property only has an effect when the focusMode property is set to AVCaptureFocusModeAutoFocus or AVCaptureFocusModeContinuousAutoFocus. Note that setting autoFocusRangeRestriction alone does not initiate a focus operation. After setting autoFocusRangeRestriction, call -setFocusMode: to apply the new restriction.
 */
@property(nonatomic) AVCaptureAutoFocusRangeRestriction autoFocusRangeRestriction API_AVAILABLE(ios(7.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property smoothAutoFocusSupported
 @abstract
    Indicates whether the receiver supports smooth autofocus.
 
 @discussion
    The receiver's smoothAutoFocusEnabled property can only be set if this property returns YES.
 */
@property(nonatomic, readonly, getter=isSmoothAutoFocusSupported) BOOL smoothAutoFocusSupported API_AVAILABLE(ios(7.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property smoothAutoFocusEnabled
 @abstract
    Indicates whether the receiver should use smooth autofocus.
 
 @discussion
    On a receiver where -isSmoothAutoFocusSupported returns YES and smoothAutoFocusEnabled is set to YES, a smooth autofocus will be engaged when the focus mode is set to AVCaptureFocusModeAutoFocus or AVCaptureFocusModeContinuousAutoFocus. Enabling smooth autofocus is appropriate for movie recording. Smooth autofocus is slower and less visually invasive. Disabling smooth autofocus is more appropriate for video processing where a fast autofocus is necessary. The default value is NO. Setting this property throws an NSInvalidArgumentException if -isSmoothAutoFocusSupported returns NO. The receiver must be locked for configuration using lockForConfiguration: before clients can set this method, otherwise an NSGenericException is thrown. Note that setting smoothAutoFocusEnabled alone does not initiate a focus operation. After setting smoothAutoFocusEnabled, call -setFocusMode: to apply the new smooth autofocus mode.
 */
@property(nonatomic, getter=isSmoothAutoFocusEnabled) BOOL smoothAutoFocusEnabled API_AVAILABLE(ios(7.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property lensPosition
 @abstract
    Indicates the focus position of the lens.
 
 @discussion
    The range of possible positions is 0.0 to 1.0, with 0.0 being the shortest distance at which the lens can focus and 1.0 the furthest. Note that 1.0 does not represent focus at infinity. The default value is 1.0. Note that a given lens position value does not correspond to an exact physical distance, nor does it represent a consistent focus distance from device to device. This property is key-value observable. It can be read at any time, regardless of focus mode, but can only be set via setFocusModeLockedWithLensPosition:completionHandler:.
 */
@property(nonatomic, readonly) float lensPosition API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @constant AVCaptureLensPositionCurrent
    A special value that may be passed as the lensPosition parameter of setFocusModeLockedWithLensPosition:completionHandler: to indicate that the caller does not wish to specify a value for the lensPosition property, and that it should instead be set to its current value. Note that the device may be adjusting lensPosition at the time of the call, in which case the value at which lensPosition is locked may differ from the value obtained by querying the lensPosition property.
 */
AVF_EXPORT const float AVCaptureLensPositionCurrent API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @method setFocusModeLockedWithLensPosition:completionHandler:
 @abstract
    Sets focusMode to AVCaptureFocusModeLocked and locks lensPosition at an explicit value.
 
 @param lensPosition
    The lens position, as described in the documentation for the lensPosition property. A value of AVCaptureLensPositionCurrent can be used to indicate that the caller does not wish to specify a value for lensPosition.
 @param handler
    A block to be called when lensPosition has been set to the value specified and focusMode is set to AVCaptureFocusModeLocked. If setFocusModeLockedWithLensPosition:completionHandler: is called multiple times, the completion handlers will be called in FIFO order. The block receives a timestamp which matches that of the first buffer to which all settings have been applied. Note that the timestamp is synchronized to the device clock, and thus must be converted to the master clock prior to comparison with the timestamps of buffers delivered via an AVCaptureVideoDataOutput. The client may pass nil for the handler parameter if knowledge of the operation's completion is not required.
 
 @discussion
    This is the only way of setting lensPosition. This method throws an NSRangeException if lensPosition is set to an unsupported level. This method throws an NSGenericException if called without first obtaining exclusive access to the receiver using lockForConfiguration:.
 */
- (void)setFocusModeLockedWithLensPosition:(float)lensPosition completionHandler:(nullable void (^)(CMTime syncTime))handler API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property minimumFocusDistance
 @abstract
    A property indicating the minimum focus distance.
 
 @discussion
    The minimum focus distance is given in millimeters, -1 if unknown. For virtual cameras (AVCaptureDeviceTypeBuiltInDualCamera, AVCaptureDeviceTypeBuiltInTripleCamera, etc.), the value reported is the smallest minimum focus distance of the auto-focus-capable cameras that it sources.
 */
@property(nonatomic, readonly) NSInteger minimumFocusDistance API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

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
    AVCaptureExposureModeCustom API_AVAILABLE(macos(10.15), ios(8.0), macCatalyst(14.0)) = 3,
} API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;


API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
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

/*!
 @constant activeMaxExposureDuration
 @abstract
    The maximum exposure (integration) time that may be used by the auto exposure algorithm.
 
 @discussion
    When an AVCaptureDevice's exposureMode is set to AVCaptureExposureModeAutoExpose or AVCaptureExposureModeContinuousAutoExposure, the auto exposure algorithm picks a default max exposure duration that is tuned for the current configuration, balancing low light image quality with motion preservation. By querying or key-value observing this property, you may find out the current max exposure duration in use. You may also override the default value by setting this property to a value between activeFormat.maxExposureDuration and activeFormat.minExposureDuration. An NSRangeException is thrown if you pass an out-of-bounds exposure duration. Setting the property to the special value of kCMTimeInvalid resets the auto exposure max duration to the device's default for your current configuration. When the device's activeFormat or the AVCaptureSession's sessionPreset changes, this property resets to the default max exposure duration for the new format or session preset.
 
    On some devices, the auto exposure algorithm picks a different max exposure duration for a given format depending whether you used the -[AVCaptureSession setSessionPreset:] API or the -[AVCaptureDevice setActiveFormat:] API to set the format. To ensure uniform default handling of max exposure duration, you can set your AVCaptureDeviceInput's unifiedAutoExposureDefaultsEnabled property to YES.
 */
@property(nonatomic) CMTime activeMaxExposureDuration API_AVAILABLE(ios(12.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

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
@property(nonatomic, readonly) float lensAperture API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property exposureDuration
 @abstract
    The length of time over which exposure takes place.
 
 @discussion
    Only exposure duration values between activeFormat.minExposureDuration and activeFormat.maxExposureDuration are supported. This property is key-value observable. It can be read at any time, regardless of exposure mode, but can only be set via setExposureModeCustomWithDuration:ISO:completionHandler:.
 */
@property(nonatomic, readonly) CMTime exposureDuration API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property ISO
 @abstract
    The current exposure ISO value.
 
 @discussion
    This property controls the sensor's sensitivity to light by means of a gain value applied to the signal. Only ISO values between activeFormat.minISO and activeFormat.maxISO are supported. Higher values will result in noisier images. This property is key-value observable. It can be read at any time, regardless of exposure mode, but can only be set via setExposureModeCustomWithDuration:ISO:completionHandler:.
 */
@property(nonatomic, readonly) float ISO API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @constant AVCaptureExposureDurationCurrent
    A special value that may be passed as the duration parameter of setExposureModeCustomWithDuration:ISO:completionHandler: to indicate that the caller does not wish to specify a value for the exposureDuration property, and that it should instead be set to its current value. Note that the device may be adjusting exposureDuration at the time of the call, in which case the value to which exposureDuration is set may differ from the value obtained by querying the exposureDuration property.
 */
AVF_EXPORT const CMTime AVCaptureExposureDurationCurrent API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 @constant AVCaptureISOCurrent
    A special value that may be passed as the ISO parameter of setExposureModeCustomWithDuration:ISO:completionHandler: to indicate that the caller does not wish to specify a value for the ISO property, and that it should instead be set to its current value. Note that the device may be adjusting ISO at the time of the call, in which case the value to which ISO is set may differ from the value obtained by querying the ISO property.
 */
AVF_EXPORT const float AVCaptureISOCurrent API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 @method setExposureModeCustomWithDuration:ISO:completionHandler:
 @abstract
    Sets exposureMode to AVCaptureExposureModeCustom and locks exposureDuration and ISO at explicit values.
 
 @param duration
    The exposure duration, as described in the documentation for the exposureDuration property. A value of AVCaptureExposureDurationCurrent can be used to indicate that the caller does not wish to specify a value for exposureDuration. Note that changes to this property may result in changes to activeVideoMinFrameDuration and/or activeVideoMaxFrameDuration.
 @param ISO
    The exposure ISO value, as described in the documentation for the ISO property. A value of AVCaptureISOCurrent can be used to indicate that the caller does not wish to specify a value for ISO.
 @param handler
    A block to be called when both exposureDuration and ISO have been set to the values specified and exposureMode is set to AVCaptureExposureModeCustom. If setExposureModeCustomWithDuration:ISO:completionHandler: is called multiple times, the completion handlers will be called in FIFO order. The block receives a timestamp which matches that of the first buffer to which all settings have been applied. Note that the timestamp is synchronized to the device clock, and thus must be converted to the master clock prior to comparison with the timestamps of buffers delivered via an AVCaptureVideoDataOutput. The client may pass nil for the handler parameter if knowledge of the operation's completion is not required.
 
 @discussion
    This is the only way of setting exposureDuration and ISO. This method throws an NSRangeException if either exposureDuration or ISO is set to an unsupported level. This method throws an NSGenericException if called without first obtaining exclusive access to the receiver using lockForConfiguration:. When using AVCapturePhotoOutput to capture photos, note that the photoQualityPrioritization property of AVCapturePhotoSettings defaults to AVCapturePhotoQualityPrioritizationBalanced, which allows photo capture to temporarily override the capture device's ISO and exposureDuration values if the scene is dark enough to warrant some form of multi-image fusion to improve quality. To ensure that the receiver's ISO and exposureDuration values are honored while in AVCaptureExposureModeCustom or AVCaptureExposureModeLocked, you must set your AVCapturePhotoSettings.photoQualityPrioritization property to AVCapturePhotoQualityPrioritizationSpeed. The same rule applies if you use the deprecated AVCapturePhotoSettings.autoStillImageStabilizationEnabled property or AVCaptureStillImageOutput.automaticallyEnablesStillImageStabilizationWhenAvailable property. You must set them to NO to preserve your custom or locked exposure settings.
 */
- (void)setExposureModeCustomWithDuration:(CMTime)duration ISO:(float)ISO completionHandler:(nullable void (^)(CMTime syncTime))handler API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property exposureTargetOffset
 @abstract
    Indicates the metered exposure level's offset from the target exposure value, in EV units.
 
 @discussion
    The value of this read-only property indicates the difference between the metered exposure level of the current scene and the target exposure value. This property is key-value observable.
 */
@property(nonatomic, readonly) float exposureTargetOffset API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property exposureTargetBias
 @abstract
    Bias applied to the target exposure value, in EV units.
 
 @discussion
    When exposureMode is AVCaptureExposureModeContinuousAutoExposure or AVCaptureExposureModeLocked, the bias will affect both metering (exposureTargetOffset), and the actual exposure level (exposureDuration and ISO). When the exposure mode is AVCaptureExposureModeCustom, it will only affect metering. This property is key-value observable. It can be read at any time, but can only be set via setExposureTargetBias:completionHandler:.
 */
@property(nonatomic, readonly) float exposureTargetBias API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property minExposureTargetBias
 @abstract
    A float indicating the minimum supported exposure bias, in EV units.
 
 @discussion
    This read-only property indicates the minimum supported exposure bias.
 */
@property(nonatomic, readonly) float minExposureTargetBias API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property maxExposureTargetBias
 @abstract
    A float indicating the maximum supported exposure bias, in EV units.
 
 @discussion
    This read-only property indicates the maximum supported exposure bias.
 */
@property(nonatomic, readonly) float maxExposureTargetBias API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @constant AVCaptureExposureTargetBiasCurrent
    A special value that may be passed as the bias parameter of setExposureTargetBias:completionHandler: to indicate that the caller does not wish to specify a value for the exposureTargetBias property, and that it should instead be set to its current value.
 */
AVF_EXPORT const float AVCaptureExposureTargetBiasCurrent API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 @method setExposureTargetBias:completionHandler:
 @abstract
    Sets the bias to be applied to the target exposure value.
 
 @param bias
    The bias to be applied to the exposure target value, as described in the documentation for the exposureTargetBias property.
 @param handler
    A block to be called when exposureTargetBias has been set to the value specified. If setExposureTargetBias:completionHandler: is called multiple times, the completion handlers will be called in FIFO order. The block receives a timestamp which matches that of the first buffer to which the setting has been applied. Note that the timestamp is synchronized to the device clock, and thus must be converted to the master clock prior to comparison with the timestamps of buffers delivered via an AVCaptureVideoDataOutput. The client may pass nil for the handler parameter if knowledge of the operation's completion is not required.
 
 @discussion
    This is the only way of setting exposureTargetBias. This method throws an NSRangeException if exposureTargetBias is set to an unsupported level. This method throws an NSGenericException if called without first obtaining exclusive access to the receiver using lockForConfiguration:.
 */
- (void)setExposureTargetBias:(float)bias completionHandler:(nullable void (^)(CMTime syncTime))handler API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

@end


API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
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
@property(nonatomic, getter=isGlobalToneMappingEnabled) BOOL globalToneMappingEnabled API_AVAILABLE(ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

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
} API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;


/*!
 @typedef AVCaptureWhiteBalanceGains
 @abstract
    Structure containing RGB white balance gain values.
 */
typedef struct {
    float redGain;
    float greenGain;
    float blueGain;
} AVCaptureWhiteBalanceGains API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;


/*!
 @typedef AVCaptureWhiteBalanceChromaticityValues
 @abstract
    Structure containing CIE 1931 xy chromaticity values.
 */
typedef struct {
    float x;
    float y;
} AVCaptureWhiteBalanceChromaticityValues API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;


/*!
 @typedef AVCaptureWhiteBalanceTemperatureAndTintValues
 @abstract
    Structure containing a white balance color correlated temperature in kelvin, plus a tint value in the range of [-150 - +150].
 */
typedef struct {
    float temperature;
    float tint;
} AVCaptureWhiteBalanceTemperatureAndTintValues API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;


API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
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
@property(nonatomic, readonly, getter=isLockingWhiteBalanceWithCustomDeviceGainsSupported) BOOL lockingWhiteBalanceWithCustomDeviceGainsSupported API_AVAILABLE(ios(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

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
@property(nonatomic, readonly) AVCaptureWhiteBalanceGains deviceWhiteBalanceGains API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property grayWorldDeviceWhiteBalanceGains
 @abstract
    Indicates the current device-specific Gray World RGB white balance gain values in use.
 
 @discussion
    This property specifies the current red, green, and blue gain values derived from the current scene to deliver a neutral (or "Gray World") white point for white balance. Gray World values assume a neutral subject (e.g. a gray card) has been placed in the middle of the subject area and fills the center 50% of the frame. Clients can read these values and apply them to the device using setWhiteBalanceModeLockedWithDeviceWhiteBalanceGains:completionHandler:. For each channel, only values between 1.0 and -maxWhiteBalanceGain are supported. This property is key-value observable. It can be read at any time, regardless of white balance mode.
 */
@property(nonatomic, readonly) AVCaptureWhiteBalanceGains grayWorldDeviceWhiteBalanceGains API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property maxWhiteBalanceGain
 @abstract
    Indicates the maximum supported value to which a channel in the AVCaptureWhiteBalanceGains may be set.
 
 @discussion
    This property does not change for the life of the receiver.
 */
@property(nonatomic, readonly) float maxWhiteBalanceGain API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @constant AVCaptureWhiteBalanceGainsCurrent
    A special value that may be passed as a parameter of setWhiteBalanceModeLockedWithDeviceWhiteBalanceGains:completionHandler: to indicate that the caller does not wish to specify a value for deviceWhiteBalanceGains, and that gains should instead be locked at their value at the moment that white balance is locked.
 */
AVF_EXPORT const AVCaptureWhiteBalanceGains AVCaptureWhiteBalanceGainsCurrent API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 @method setWhiteBalanceModeLockedWithDeviceWhiteBalanceGains:completionHandler:
 @abstract
    Sets white balance to locked mode with explicit deviceWhiteBalanceGains values.
 
 @param whiteBalanceGains
    The white balance gain values, as described in the documentation for the deviceWhiteBalanceGains property. A value of AVCaptureWhiteBalanceGainsCurrent can be used to indicate that the caller does not wish to specify a value for deviceWhiteBalanceGains.
 @param handler
    A block to be called when white balance gains have been set to the values specified and whiteBalanceMode is set to AVCaptureWhiteBalanceModeLocked. If setWhiteBalanceModeLockedWithDeviceWhiteBalanceGains:completionHandler: is called multiple times, the completion handlers will be called in FIFO order. The block receives a timestamp which matches that of the first buffer to which all settings have been applied. Note that the timestamp is synchronized to the device clock, and thus must be converted to the master clock prior to comparison with the timestamps of buffers delivered via an AVCaptureVideoDataOutput. This parameter may be nil if synchronization is not required.
 
 @discussion
    For each channel in the whiteBalanceGains struct, only values between 1.0 and -maxWhiteBalanceGain are supported. Gain values are normalized to the minimum channel value to avoid brightness changes (e.g. R:2 G:2 B:4 will be normalized to R:1 G:1 B:2). This method throws an NSRangeException if any of the whiteBalanceGains are set to an unsupported level. This method throws an NSGenericException if called without first obtaining exclusive access to the receiver using lockForConfiguration:.
 */
- (void)setWhiteBalanceModeLockedWithDeviceWhiteBalanceGains:(AVCaptureWhiteBalanceGains)whiteBalanceGains completionHandler:(nullable void (^)(CMTime syncTime))handler API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

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
- (AVCaptureWhiteBalanceChromaticityValues)chromaticityValuesForDeviceWhiteBalanceGains:(AVCaptureWhiteBalanceGains)whiteBalanceGains API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

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
- (AVCaptureWhiteBalanceGains)deviceWhiteBalanceGainsForChromaticityValues:(AVCaptureWhiteBalanceChromaticityValues)chromaticityValues API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

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
- (AVCaptureWhiteBalanceTemperatureAndTintValues)temperatureAndTintValuesForDeviceWhiteBalanceGains:(AVCaptureWhiteBalanceGains)whiteBalanceGains API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

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
- (AVCaptureWhiteBalanceGains)deviceWhiteBalanceGainsForTemperatureAndTintValues:(AVCaptureWhiteBalanceTemperatureAndTintValues)tempAndTintValues API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

@end


API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface AVCaptureDevice (AVCaptureDeviceSubjectAreaChangeMonitoring)

/*!
 @property subjectAreaChangeMonitoringEnabled
 @abstract
    Indicates whether the receiver should monitor the subject area for changes.
 
 @discussion
    The value of this property is a BOOL indicating whether the receiver should monitor the video subject area for changes, such as lighting changes, substantial movement, etc. If subject area change monitoring is enabled, the receiver sends an AVCaptureDeviceSubjectAreaDidChangeNotification whenever it detects a change to the subject area, at which time an interested client may wish to re-focus, adjust exposure, white balance, etc. The receiver must be locked for configuration using lockForConfiguration: before clients can set the value of this property.
 */
@property(nonatomic, getter=isSubjectAreaChangeMonitoringEnabled) BOOL subjectAreaChangeMonitoringEnabled API_AVAILABLE(ios(5.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

@end


API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface AVCaptureDevice (AVCaptureDeviceLowLightBoost)

/*!
 @property lowLightBoostSupported
 @abstract
    Indicates whether the receiver supports boosting images in low light conditions.
 
 @discussion
    The receiver's automaticallyEnablesLowLightBoostWhenAvailable property can only be set if this property returns YES.
 */
@property(nonatomic, readonly, getter=isLowLightBoostSupported) BOOL lowLightBoostSupported API_AVAILABLE(ios(6.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property lowLightBoostEnabled
 @abstract
    Indicates whether the receiver's low light boost feature is enabled.
 
 @discussion
    The value of this property is a BOOL indicating whether the receiver is currently enhancing images to improve quality due to low light conditions. When -isLowLightBoostEnabled returns YES, the receiver has switched into a special mode in which more light can be perceived in images. This property is key-value observable.
 */
@property(nonatomic, readonly, getter=isLowLightBoostEnabled) BOOL lowLightBoostEnabled API_AVAILABLE(ios(6.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property automaticallyEnablesLowLightBoostWhenAvailable
 @abstract
    Indicates whether the receiver should automatically switch to low light boost mode when necessary.
 
 @discussion
    On a receiver where -isLowLightBoostSupported returns YES, a special low light boost mode may be engaged to improve image quality. When the automaticallyEnablesLowLightBoostWhenAvailable property is set to YES, the receiver switches at its discretion to a special boost mode under low light, and back to normal operation when the scene becomes sufficiently lit. An AVCaptureDevice that supports this feature may only engage boost mode for certain source formats or resolutions. Clients may observe changes to the lowLightBoostEnabled property to know when the mode has engaged. The switch between normal operation and low light boost mode may drop one or more video frames. The default value is NO. Setting this property throws an NSInvalidArgumentException if -isLowLightBoostSupported returns NO. The receiver must be locked for configuration using lockForConfiguration: before clients can set this method, otherwise an NSGenericException is thrown.
 */
@property(nonatomic) BOOL automaticallyEnablesLowLightBoostWhenAvailable API_AVAILABLE(ios(6.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

@end


API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface AVCaptureDevice (AVCaptureDeviceVideoZoom)

/*!
 @property videoZoomFactor
 @abstract
    Controls zoom level of image outputs
 
 @discussion
    Applies a centered crop for all image outputs, scaling as necessary to maintain output dimensions. Minimum value of 1.0 yields full field of view, increasing values will increase magnification, up to a maximum value specified in the activeFormat's videoMaxZoomFactor property. Modifying the zoom factor will cancel any active rampToVideoZoomFactor:withRate:, and snap directly to the assigned value. Assigning values outside the acceptable range will generate an NSRangeException. Clients can key value observe the value of this property.
 
    -setVideoZoomFactor: throws an NSGenericException if called without first obtaining exclusive access to the receiver using lockForConfiguration:.
 
 @seealso -[AVCaptureDeviceFormat videoMaxZoomFactor] and -[AVCaptureDeviceFormat videoZoomFactorUpscaleThreshold]
 */
@property(nonatomic) CGFloat videoZoomFactor API_AVAILABLE(ios(7.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @method rampToVideoZoomFactor:withRate:
 @abstract
    Provides smooth changes in zoom factor.
 
 @discussion
    This method provides a change in zoom by compounding magnification at the specified rate over time. Although the zoom factor will grow exponentially, this yields a visually linear zoom in the image over time.
 
    The zoom transition will stop at the specified factor, which must be in the valid range for videoZoomFactor. Assignments to videoZoomFactor while a ramp is in progress will cancel the ramp and snap to the assigned value.
 
    The zoom factor is continuously scaled by pow(2,rate * time). A rate of 0 causes no change in zoom factor, equivalent to calling cancelVideoZoomRamp. A rate of 1 will cause the magnification to double every second (or halve every second if zooming out), and similarly larger or smaller values will zoom faster or slower respectively. Only the absolute value of the rate is significant--sign is corrected for the direction of the target. Changes in rate will be smoothed by an internal acceleration limit.
 
    -rampToVideoZoomFactor:withRate: throws an NSGenericException if called without first obtaining exclusive access to the receiver using lockForConfiguration:.
 */
- (void)rampToVideoZoomFactor:(CGFloat)factor withRate:(float)rate API_AVAILABLE(ios(7.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property rampingVideoZoom
 @abstract
    Indicates if the zoom factor is transitioning to a value set by rampToVideoZoomFactor:withRate:
 
 @discussion
    Clients can observe this value to determine when a ramp begins or completes.
 */
@property(nonatomic, readonly, getter=isRampingVideoZoom) BOOL rampingVideoZoom API_AVAILABLE(ios(7.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @method cancelVideoZoomRamp
 @abstract
    Eases out of any video zoom transitions initiated by rampToVideoZoomFactor:withRate:
 
 @discussion
    This method is equivalent to calling rampToVideoZoomFactor:withRate: using the current zoom factor target and a rate of 0. This allows a smooth stop to any changes in zoom which were in progress.
 
    -cancelVideoZoomRamp: throws an NSGenericException if called without first obtaining exclusive access to the receiver using lockForConfiguration:.
 */
- (void)cancelVideoZoomRamp API_AVAILABLE(ios(7.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 @property dualCameraSwitchOverVideoZoomFactor
 @abstract
    The video zoom factor at or above which a DualCamera can select between its wide angle camera and its telephoto camera.
 
 @discussion
    This is the zoom factor at which the wide angle camera's field of view matches telephoto camera's full field of view. On non-DualCamera devices this will return 1.0. As of iOS 13.0, this API has been deprecated in favor of virtualDeviceSwitchOverVideoZoomFactors.
 */
@property(atomic, readonly) CGFloat dualCameraSwitchOverVideoZoomFactor API_DEPRECATED_WITH_REPLACEMENT("virtualDeviceSwitchOverVideoZoomFactors", ios(11.0, 13.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos);

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
} API_AVAILABLE(macos(10.14), ios(7.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;


API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
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
+ (AVAuthorizationStatus)authorizationStatusForMediaType:(AVMediaType)mediaType API_AVAILABLE(macos(10.14), ios(7.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos);

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

    The completion handler is called on an arbitrary dispatch queue. Is it the client's responsibility to ensure that any UIKit-related updates are called on the main queue or main thread as a result.
 */
+ (void)requestAccessForMediaType:(AVMediaType)mediaType completionHandler:(void (^)(BOOL granted))handler API_AVAILABLE(macos(10.14), ios(7.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos);

@end


/*!
 @typedef
 @abstract
    A constant that is used to specify the transport controls' speed.
 */
typedef float AVCaptureDeviceTransportControlsSpeed API_AVAILABLE(macos(10.7)) API_UNAVAILABLE(ios, macCatalyst, watchos, tvos);


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
} API_AVAILABLE(macos(10.7)) API_UNAVAILABLE(ios, macCatalyst, watchos, tvos);


API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface AVCaptureDevice (AVCaptureDeviceTransportControls)

/*!
 @property transportControlsSupported
 @abstract
    Returns whether the receiver supports transport control commands.
 
 @discussion
    For devices with transport controls, such as AVC tape-based camcorders or pro capture devices with RS422 deck control, the value of this property is YES. If transport controls are not supported, none of the associated transport control methods and properties are available on the receiver.
 */
@property(nonatomic, readonly) BOOL transportControlsSupported API_UNAVAILABLE(ios, macCatalyst, watchos, tvos);

/*!
 @property transportControlsPlaybackMode
 @abstract
    Returns the receiver's current playback mode.
 
 @discussion
    For devices that support transport control, this property may be queried to discover the current playback mode.
 */
@property(nonatomic, readonly) AVCaptureDeviceTransportControlsPlaybackMode transportControlsPlaybackMode API_UNAVAILABLE(ios, macCatalyst, watchos, tvos);

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
@property(nonatomic, readonly) AVCaptureDeviceTransportControlsSpeed transportControlsSpeed API_UNAVAILABLE(ios, macCatalyst, watchos, tvos);

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
- (void)setTransportControlsPlaybackMode:(AVCaptureDeviceTransportControlsPlaybackMode)mode speed:(AVCaptureDeviceTransportControlsSpeed)speed API_UNAVAILABLE(ios, macCatalyst, watchos, tvos);

@end


API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface AVCaptureDevice (AVCaptureDeviceHighDynamicRangeSupport)

/*!
 @property automaticallyAdjustsVideoHDREnabled
 @abstract
    Indicates whether the receiver is allowed to turn high dynamic range streaming on or off.
 
 @discussion
    The value of this property is a BOOL indicating whether the receiver is free to turn high dynamic range streaming on or off. This property defaults to YES. When automaticallyAdjustsVideoHDREnabled, the AVCaptureDevice turns videoHDR on automatically if it's a good fit for the activeFormat. -setAutomaticallyAdjustsVideoHDREnabled: throws an NSGenericException if called without first obtaining exclusive access to the receiver using -lockForConfiguration:. Clients can key-value observe videoHDREnabled to know when the receiver has automatically changed the value.
 */
@property(nonatomic) BOOL automaticallyAdjustsVideoHDREnabled API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property videoHDREnabled
 @abstract
    Indicates whether the receiver's streaming high dynamic range feature is enabled. See AVCaptureDeviceFormat.isVideoHDRSupported.
 
 @discussion
    The value of this property is a BOOL indicating whether the receiver is currently streaming high dynamic range video buffers, also known as Extended Dynamic Range (EDR). The value of this property is ignored when device.activeColorSpace is HLG BT2020 color space since HDR is effectively always on and can't be disabled. The property may only be set if you first set automaticallyAdjustsVideoHDREnabled to NO, otherwise an NSGenericException is thrown. videoHDREnabled may only be set to YES if the receiver's activeFormat.isVideoHDRSupported property returns YES, otherwise an NSGenericException is thrown. This property may be key-value observed.
 
    Note that setting this property may cause a lengthy reconfiguration of the receiver, similar to setting a new active format or AVCaptureSession sessionPreset. If you are setting either the active format or the AVCaptureSession's sessionPreset AND this property, you should bracket these operations with [session beginConfiguration] and [session commitConfiguration] to minimize reconfiguration time.
 */
@property(nonatomic, getter=isVideoHDREnabled) BOOL videoHDREnabled API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

@end

/*!
 @enum AVCaptureColorSpace
 @abstract
    Constants indicating active or supported video color space.
 
 @constant AVCaptureColorSpace_sRGB
    The sGRB color space ( https://www.w3.org/Graphics/Color/srgb )
 @constant AVCaptureColorSpace_P3_D65
    The P3 D65 wide color space which uses Illuminant D65 as the white point.
 @constant AVCaptureColorSpace_HLG_BT2020
    The BT2020 wide color space which uses Illuminant D65 as the white point and Hybrid Log-Gamma as the transfer function.
 */
typedef NS_ENUM(NSInteger, AVCaptureColorSpace) {
    AVCaptureColorSpace_sRGB       = 0,
    AVCaptureColorSpace_P3_D65     = 1,
    AVCaptureColorSpace_HLG_BT2020 API_AVAILABLE(ios(14.1), macCatalyst(14.1)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos) = 2,
} API_AVAILABLE(macos(10.15), ios(10.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;


API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface AVCaptureDevice (AVCaptureDeviceColorSpaceSupport)

/*!
 @property activeColorSpace
 @abstract
    Indicates the receiver's current active color space.
 
 @discussion
    By default, an AVCaptureDevice attached to an AVCaptureSession is automatically configured for wide color by the AVCaptureSession (see AVCaptureSession automaticallyConfiguresCaptureDeviceForWideColor). You may also set the activeColorSpace manually. To prevent the AVCaptureSession from undoing your work, remember to set AVCaptureSession's automaticallyConfiguresCaptureDeviceForWideColor property to NO. Changing the receiver's activeColorSpace while the session is running requires a disruptive reconfiguration of the capture render pipeline. Movie captures in progress will be ended immediately; unfulfilled photo requests will be aborted; video preview will temporarily freeze. -setActiveColorSpace: throws an NSGenericException if called without first obtaining exclusive access to the receiver using -lockForConfiguration:.
 */
@property(nonatomic) AVCaptureColorSpace activeColorSpace API_AVAILABLE(macos(10.15), ios(10.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos);

@end


API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
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
@property(nonatomic, retain, nullable) AVCaptureDeviceFormat *activeDepthDataFormat API_AVAILABLE(ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

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
@property(nonatomic) CMTime activeDepthDataMinFrameDuration API_AVAILABLE(ios(12.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property minAvailableVideoZoomFactor
 @abstract
    Indicates the minimum zoom factor available for the AVCaptureDevice's videoZoomFactor property.
 
 @discussion
    On non-virtual devices the minAvailableVideoZoomFactor is always 1.0. On a virtual device the minAvailableVideoZoomFactor can change when the device is delivering depth data to one or more outputs (see -[AVCaptureDeviceFormat videoMinZoomFactorForDepthDataDelivery]). If the device's videoZoomFactor property is assigned a value smaller than 1.0, an NSRangeException is thrown. Setting the videoZoomFactor to a value greater than or equal to 1.0, but lower than minAvailableVideoZoomFactor results in the value being clamped to the minAvailableVideoZoomFactor. Clients can key value observe the value of this property.
 */
@property(nonatomic, readonly) CGFloat minAvailableVideoZoomFactor API_AVAILABLE(ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property maxAvailableVideoZoomFactor
 @abstract
    Indicates the maximum zoom factor available for the AVCaptureDevice's videoZoomFactor property.
 
 @discussion
    On non-virtual devices the maxAvailableVideoZoomFactor is always equal to the activeFormat.videoMaxZoomFactor. On a virtual device the maxAvailableVideoZoomFactor can change when the device is delivering depth data to one or more outputs (see -[AVCaptureDeviceFormat videoMaxZoomFactorForDepthDataDelivery]). If the device's videoZoomFactor property is assigned a value greater than activeFormat.videoMaxZoomFactor, an NSRangeException is thrown. Setting the videoZoomFactor to a value less than or equal to activeFormat.videoMaxZoomFactor, but greater than maxAvailableVideoZoomFactor results in the value being clamped to the maxAvailableVideoZoomFactor. Clients can key value observe the value of this property.
 */
@property(nonatomic, readonly) CGFloat maxAvailableVideoZoomFactor API_AVAILABLE(ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

@end


API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface AVCaptureDevice (AVCaptureDeviceGeometricDistortionCorrection)

/*!
 @property geometricDistortionCorrectionSupported
 @abstract
    Indicates that geometric distortion correction is supported by the receiver.
 
 @discussion
    Some AVCaptureDevices benefit from geometric distortion correction (GDC), such as devices with a very wide field of view. GDC lessens the fisheye effect at the outer edge of the frame at the cost of losing a small amount of vertical and horizontal field of view. When GDC is enabled on the AVCaptureDevice (see geometricDistortionEnabled), the corrected image is upscaled to the original image size when needed.  With respect to the AVCaptureDevice.videoZoomFactor API, the full viewable field of view is always represented with a videoZoomFactor of 1.0. Thus, when GDC is enabled, the AVCaptureDevice.activeFormat's field of view at videoZoomFactor = 1.0 will be different than when GDC is disabled. The smaller field of view is reported through the activeFormat's geometricDistortionCorrectedVideoFieldOfView property. Beware though that RAW photo captures never have GDC applied, regardless of the value of AVCaptureDevice.geometricDistortionCorrectionEnabled.
 */
@property(nonatomic, readonly, getter=isGeometricDistortionCorrectionSupported) BOOL geometricDistortionCorrectionSupported API_AVAILABLE(ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @property geometricDistortionCorrectionEnabled
 @abstract
    Indicates whether geometric distortion correction is enabled by the receiver.
 
 @discussion
    Where supported, the default value is YES. The receiver must be locked for configuration using lockForConfiguration: before clients can set this method, otherwise an NSGenericException is thrown.
 */
@property(nonatomic, getter=isGeometricDistortionCorrectionEnabled) BOOL geometricDistortionCorrectionEnabled API_AVAILABLE(ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

@end


API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
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
+ (nullable NSData *)extrinsicMatrixFromDevice:(AVCaptureDevice *)fromDevice toDevice:(AVCaptureDevice *)toDevice API_AVAILABLE(ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

@end


API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
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
} API_AVAILABLE(ios(14.5), macCatalyst(14.5)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @property centerStageControlMode
 @abstract
    A class property indicating the current mode of Center Stage control (user, app, or cooperative).
 
 @discussion
    This class property determines how the Center Stage feature is controlled. When set to the default value of AVCaptureCenterStageControlModeUser, centerStageEnabled may not be set programmatically and throws an NSInvalidArgumentException. In User mode, the feature may only be set by the user in Control Center. If you wish to take Center Stage control away from the user and exclusively enable / disable it programmatically, set this property to AVCaptureCenterStageControlModeApp. When under exclusive app control, Center Stage user control is disallowed (for instance, the toggle is grayed out in Control Center). If you wish to take control of Center Stage, but also cooperate with the user by listening for and appropriately reacting to their changes to the centerStageEnabled property, set this property to AVCaptureCenterStageControlModeCooperative. Note that in this mode, the onus is on you, the app developer, to honor user intent and conform your AVCaptureSession configuration to make Center Stage active (see the AVCaptureDevice instance property centerStageActive). In cooperative mode, the centerStageEnabled property may change at any time (such as when the user enables / disables the feature in Control Center).
 */
@property(class) AVCaptureCenterStageControlMode centerStageControlMode API_AVAILABLE(ios(14.5), macCatalyst(14.5)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @property centerStageEnabled
 @abstract
    A class property indicating whether the Center Stage feature is currently enabled or disabled (such as in Control Center or programmatically via your app).
 
 @discussion
    This property may only be set if centerStageControlMode is AVCaptureCenterStageControlModeApp or AVCaptureCenterStageControlModeCooperative, and otherwise throws an NSInvalidArgumentException. When centerStageControlMode is AVCaptureCenterStageControlModeUser or AVCaptureCenterStageControlModeCooperative, this property may change according to user desire (such as enabling / disabling the feature in Control Center), so you should key-value observe it.
 */
@property(class, getter=isCenterStageEnabled) BOOL centerStageEnabled API_AVAILABLE(ios(14.5), macCatalyst(14.5)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

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
@property(nonatomic, readonly, getter=isCenterStageActive) BOOL centerStageActive API_AVAILABLE(ios(14.5), macCatalyst(14.5)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

@end


API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos)
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
@property(class, readonly, getter=isPortraitEffectEnabled) BOOL portraitEffectEnabled API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

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
@property(nonatomic, readonly, getter=isPortraitEffectActive) BOOL portraitEffectActive API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

@end


API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos)
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
} NS_SWIFT_NAME(AVCaptureDevice.MicrophoneMode) API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

/*!
 @property preferredMicrophoneMode
 @abstract
    Indicates the microphone mode that has been selected by the user in Control Center.

 @discussion
    This readonly property returns the microphone mode selected by the user in Control Center. It is key-value observable.
 */
@property(class, readonly) AVCaptureMicrophoneMode preferredMicrophoneMode API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

/*!
 @property activeMicrophoneMode
 @abstract
    Indicates the currently active microphone mode.

 @discussion
    This readonly property returns the currently active microphone mode, which may differ from the preferredMicrophoneMode if the application's active audio route does not support the preferred microphone mode. This property is key-value observable.
 */
@property(class, readonly) AVCaptureMicrophoneMode activeMicrophoneMode API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

@end


API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos)
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
} NS_SWIFT_NAME(AVCaptureDevice.SystemUserInterface) API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

/*!
 @method showSystemUserInterface:
 @abstract
    Displays the system's user interface for video effects or microphone modes.
 
  @param systemUserInterface
     The system UI to show.
 
 @discussion
    This method allows the calling application to prompt the user to make changes to Video Effects (such as Center Stage or the Portrait Effect) or Microphone Modes. It brings up the system user interface and deep links to the appropriate module. This method is non-blocking. After presenting the desired system user interface, control returns immediately to the application.
 */
+ (void)showSystemUserInterface:(AVCaptureSystemUserInterface)systemUserInterface NS_SWIFT_NAME(showSystemUserInterface(_:)) API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

@end


#pragma mark - AVCaptureDeviceDiscoverySession

/*!
 @class AVCaptureDeviceDiscoverySession
 @abstract
    The AVCaptureDeviceDiscoverySession allows clients to search for devices by certain criteria.
 
 @discussion
    This class allows clients to discover devices by providing certain search criteria. The objective of this class is to help find devices by device type and optionally by media type or position and allow you to key-value observe changes to the returned devices list.
 */
API_AVAILABLE(macos(10.15), ios(10.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
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
@property(nonatomic, readonly) NSArray<NSSet<AVCaptureDevice *> *> *supportedMultiCamDeviceSets API_AVAILABLE(ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

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
API_AVAILABLE(macos(10.7), ios(7.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
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


/*!
 @enum AVCaptureVideoStabilizationMode
 @abstract
    Constants indicating the modes of video stabilization supported by the device's format.
 
 @constant AVCaptureVideoStabilizationModeOff
    Indicates that video should not be stabilized.
 @constant AVCaptureVideoStabilizationModeStandard
    Indicates that video should be stabilized using the standard video stabilization algorithm introduced with iOS 5.0. Standard video stabilization has a reduced field of view. Enabling video stabilization may introduce additional latency into the video capture pipeline.
 @constant AVCaptureVideoStabilizationModeCinematic
    Indicates that video should be stabilized using the cinematic stabilization algorithm for more dramatic results. Cinematic video stabilization has a reduced field of view compared to standard video stabilization. Enabling cinematic video stabilization introduces much more latency into the video capture pipeline than standard video stabilization and consumes significantly more system memory. Use narrow or identical min and max frame durations in conjunction with this mode.
 @constant AVCaptureVideoStabilizationModeCinematicExtended
    Indicates that the video should be stabilized using the extended cinematic stabilization algorithm. Enabling extended cinematic stabilization introduces longer latency into the video capture pipeline compared to the AVCaptureVideoStabilizationModeCinematic and consumes more memory, but yields improved stability. It is recommended to use identical or similar min and max frame durations in conjunction with this mode.
 @constant AVCaptureVideoStabilizationModeAuto
    Indicates that the most appropriate video stabilization mode for the device and format should be chosen.
 */
typedef NS_ENUM(NSInteger, AVCaptureVideoStabilizationMode) {
    AVCaptureVideoStabilizationModeOff       = 0,
    AVCaptureVideoStabilizationModeStandard  = 1,
    AVCaptureVideoStabilizationModeCinematic = 2,
    AVCaptureVideoStabilizationModeCinematicExtended API_AVAILABLE(ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos) = 3,
    AVCaptureVideoStabilizationModeAuto      = -1,
} API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;


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
} API_AVAILABLE(macos(10.15), ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;


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
API_AVAILABLE(macos(10.7), ios(7.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
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
@property(nonatomic, readonly) float videoFieldOfView API_UNAVAILABLE(macos);

/*!
 @property videoBinned
 @abstract
    A property indicating whether the format is binned.
 
 @discussion
    videoBinned is a BOOL indicating whether the format is a binned format. Binning is a pixel-combining process which can result in greater low light sensitivity at the cost of reduced resolution.
 */
@property(nonatomic, readonly, getter=isVideoBinned) BOOL videoBinned API_UNAVAILABLE(macos);

/*!
 @method isVideoStabilizationModeSupported
 @abstract
    Returns whether the format supports the given video stabilization mode.
 
 @param videoStabilizationMode
    An AVCaptureVideoStabilizationMode to be checked.
 
 @discussion
    isVideoStabilizationModeSupported: returns a boolean value indicating whether the format can be stabilized using the given mode with -[AVCaptureConnection setPreferredVideoStabilizationMode:].
 */
- (BOOL)isVideoStabilizationModeSupported:(AVCaptureVideoStabilizationMode)videoStabilizationMode API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property videoStabilizationSupported
 @abstract
    A property indicating whether the format supports video stabilization.
 
 @discussion
    videoStabilizationSupported is a BOOL indicating whether the format can be stabilized using AVCaptureConnection -setEnablesVideoStabilizationWhenAvailable. This property is deprecated. Use isVideoStabilizationModeSupported: instead.
 */
@property(nonatomic, readonly, getter=isVideoStabilizationSupported) BOOL videoStabilizationSupported API_DEPRECATED("Use isVideoStabilizationModeSupported: instead.", ios(7.0, 8.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos);

/*!
 @property videoMaxZoomFactor
 @abstract
    Indicates the maximum zoom factor available for the AVCaptureDevice's videoZoomFactor property.
 
 @discussion
    If the device's videoZoomFactor property is assigned a larger value, an NSRangeException will be thrown. A maximum zoom factor of 1 indicates no zoom is available.
 */
@property(nonatomic, readonly) CGFloat videoMaxZoomFactor API_UNAVAILABLE(macos);

/*!
 @property videoZoomFactorUpscaleThreshold
 @abstract
    Indicates the value of AVCaptureDevice's videoZoomFactor property at which the image output begins to require upscaling.
 
 @discussion
    In some cases the image sensor's dimensions are larger than the dimensions reported by the video AVCaptureDeviceFormat. As long as the sensor crop is larger than the reported dimensions of the AVCaptureDeviceFormat, the image will be downscaled. Setting videoZoomFactor to the value of videoZoomFactorUpscalingThreshold will provide a center crop of the sensor image data without any scaling. If a greater zoom factor is used, then the sensor data will be upscaled to the device format's dimensions.
 */
@property(nonatomic, readonly) CGFloat videoZoomFactorUpscaleThreshold API_UNAVAILABLE(macos);

/*!
 @property minExposureDuration
 @abstract
    A CMTime indicating the minimum supported exposure duration.
 
 @discussion
    This read-only property indicates the minimum supported exposure duration.
 */
@property(nonatomic, readonly) CMTime minExposureDuration API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property maxExposureDuration
 @abstract
    A CMTime indicating the maximum supported exposure duration.
 
 @discussion
    This read-only property indicates the maximum supported exposure duration.
 */
@property(nonatomic, readonly) CMTime maxExposureDuration API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property minISO
 @abstract
    A float indicating the minimum supported exposure ISO value.
 
 @discussion
    This read-only property indicates the minimum supported exposure ISO value.
 */
@property(nonatomic, readonly) float minISO API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property maxISO
 @abstract
    An float indicating the maximum supported exposure ISO value.
 
 @discussion
    This read-only property indicates the maximum supported exposure ISO value.
 */
@property(nonatomic, readonly) float maxISO API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property globalToneMappingSupported
 @abstract
    A property indicating whether the format supports global tone mapping.
 
 @discussion
    globalToneMappingSupported is a BOOL indicating whether the format supports global tone mapping. See AVCaptureDevice's globalToneMappingEnabled property.
 */
@property(nonatomic, readonly, getter=isGlobalToneMappingSupported) BOOL globalToneMappingSupported API_AVAILABLE(ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @property videoHDRSupported
 @abstract
    A property indicating whether the format supports high dynamic range streaming.
 
 @discussion
    videoHDRSupported is a BOOL indicating whether the format supports high dynamic range streaming, also known as Extended Dynamic Range (EDR). When enabled, the device streams at twice the published frame rate, capturing an under-exposed frame and correctly exposed frame for each frame time at the published rate. Portions of the under-exposed frame are combined with the correctly exposed frame to recover detail in darker areas of the scene. EDR is a separate and distinct feature from 10-bit HDR video (first seen in 2020 iPhones). 10-bit formats with HLG BT2020 color space have greater dynamic range by virtue of their expanded bit depth and HLG transfer function, and when captured in movies, contain Dolby Vision metadata. They are, in effect, "always on" HDR. And thus the videoHDRSupported property is always NO for 10-bit formats only supporting HLG BT2020 colorspace, since HDR cannot be enabled or disabled. To enable videoHDR (EDR), set the AVCaptureDevice.videoHDREnabled property.
 */
@property(nonatomic, readonly, getter=isVideoHDRSupported) BOOL videoHDRSupported API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

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
@property(nonatomic, readonly) CMVideoDimensions highResolutionStillImageDimensions API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

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
@property(nonatomic, readonly, getter=isHighPhotoQualitySupported) BOOL highPhotoQualitySupported API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

/*!
 @property highestPhotoQualitySupported
 @abstract
    A boolean value specifying whether this format supports the highest possible photo quality that can be delivered on the current platform.
 
 @discussion
    Of the many formats supported by an AVCaptureDevice, only a few of them are designated as "photo" formats which can produce the highest possible quality, such as still image stabilization and Live Photos. If you intend to connect an AVCaptureDeviceInput to an AVCapturePhotoOutput and receive the best possible images, you should ensure that you are either using the AVCaptureSessionPresetPhoto as your preset, or if using the parallel AVCaptureDevice activeFormat API, select as your activeFormat one for which this property is YES.
 */
@property(nonatomic, readonly, getter=isHighestPhotoQualitySupported) BOOL highestPhotoQualitySupported API_AVAILABLE(ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @property autoFocusSystem
 @abstract
    A property indicating the autofocus system.
 
 @discussion
    This read-only property indicates the autofocus system.
 */
@property(nonatomic, readonly) AVCaptureAutoFocusSystem autoFocusSystem API_AVAILABLE(macos(10.15), ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos);

/*!
 @property supportedColorSpaces
 @abstract
    A property indicating the receiver's supported color spaces.
 
 @discussion
    This read-only property indicates the receiver's supported color spaces as an array of AVCaptureColorSpace constants sorted from narrow to wide color.
 */
@property(nonatomic, readonly) NSArray<NSNumber *> *supportedColorSpaces API_AVAILABLE(macos(10.15), ios(10.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos);

/*!
 @property videoMinZoomFactorForDepthDataDelivery
 @abstract
    Indicates the minimum zoom factor available for the AVCaptureDevice's videoZoomFactor property when delivering depth data to one or more outputs.
 
 @discussion
    Virtual devices support a limited zoom range when delivering depth data to any output. If this device format has no -supportedDepthDataFormats, this property returns 1.0.
 */
@property(nonatomic, readonly) CGFloat videoMinZoomFactorForDepthDataDelivery API_AVAILABLE(ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property videoMaxZoomFactorForDepthDataDelivery
 @abstract
    Indicates the maximum zoom factor available for the AVCaptureDevice's videoZoomFactor property when delivering depth data to one or more outputs.
 
 @discussion
    Virtual devices support a limited zoom range when delivering depth data to any output. If this device format has no -supportedDepthDataFormats, this property returns videoMaxZoomFactor.
 */
@property(nonatomic, readonly) CGFloat videoMaxZoomFactorForDepthDataDelivery API_AVAILABLE(ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property supportedDepthDataFormats
 @abstract
    Indicates this format's companion depth data formats.
 
 @discussion
    If no depth data formats are supported by the receiver, an empty array is returned. On virtual devices, the supportedDepthDataFormats list items always match the aspect ratio of their paired video format. When the receiver is set as the device's activeFormat, you may set the device's activeDepthDataFormat to one of these supported depth data formats.
 */
@property(nonatomic, readonly) NSArray<AVCaptureDeviceFormat *> *supportedDepthDataFormats API_AVAILABLE(ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property unsupportedCaptureOutputClasses
 @abstract
    A property indicating AVCaptureOutput subclasses the receiver does not support.
 
 @discussion
    As a rule, AVCaptureDeviceFormats of a given mediaType are available for use with all AVCaptureOutputs that accept that media type, but there are exceptions. For instance, on apps linked against iOS versions earlier than 12.0, the photo resolution video formats may not be used as sources for AVCaptureMovieFileOutput due to bandwidth limitations. On DualCamera devices, AVCaptureDepthDataOutput is not supported when outputting full resolution (i.e. 12 MP) video due to bandwidth limitations. In order to stream depth data plus video data from a photo format, ensure that your AVCaptureVideoDataOutput's deliversPreviewSizedOutputBuffers property is set to YES. Likewise, to stream depth data while capturing video to a movie file using AVCaptureMovieFileOutput, call -[AVCaptureSession setSessionPreset:AVCaptureSessionPresetPhoto]. When using the photo preset, video is captured at preview resolution rather than the full sensor resolution.
 */
@property(nonatomic, readonly) NSArray<Class> *unsupportedCaptureOutputClasses API_AVAILABLE(ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

@end


API_AVAILABLE(macos(10.7), ios(7.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface AVCaptureDeviceFormat (AVCaptureDeviceFormatDepthDataAdditions)

/*
 @property portraitEffectsMatteStillImageDeliverySupported
 @abstract
    Indicates whether this depth format supports the delivery of a portrait effects matte.
 
 @discussion
    Some depth formats are capable of producing an auxiliary matting image (similar to an auxiliary depth image) tuned for high quality portrait effects rendering (see AVPortraitEffectsMatte.h). If this property's value is YES, you may request portrait effects matte delivery in your photos using the AVCapturePhotoOutput, provided this format is selected as the activeDepthDataFormat.
 */
@property(nonatomic, readonly, getter=isPortraitEffectsMatteStillImageDeliverySupported) BOOL portraitEffectsMatteStillImageDeliverySupported API_AVAILABLE(ios(12.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

@end


API_AVAILABLE(macos(10.7), ios(7.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface AVCaptureDeviceFormat (AVCaptureDeviceFormatMultiCamAdditions)

/*!
 @property multiCamSupported
 @abstract
    A property indicating whether this format is supported in an AVCaptureMultiCamSession.
 
 @discussion
   When using an AVCaptureSession (single camera capture), any of the formats in the device's -formats array may be set as the -activeFormat. However, when used with an AVCaptureMultiCamSession, the device's -activeFormat may only be set to one of the formats for which multiCamSupported answers YES. This limited subset of capture formats are known to run sustainably in a multi camera capture scenario.
 */
@property(nonatomic, readonly, getter=isMultiCamSupported) BOOL multiCamSupported API_AVAILABLE(ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

@end


API_AVAILABLE(macos(10.7), ios(7.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface AVCaptureDeviceFormat (AVCaptureDeviceFormatGeometricDistortionCorrection)

/*!
 @property geometricDistortionCorrectedVideoFieldOfView
 @abstract
    A property indicating the format's horizontal field of view post geometric distortion correction.
 
 @discussion
    If the receiver's AVCaptureDevice does not support GDC, geometricDistortionCorrectedVideoFieldOfView matches the videoFieldOfView property.
 */
@property(nonatomic, readonly) float geometricDistortionCorrectedVideoFieldOfView API_AVAILABLE(ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

@end


API_AVAILABLE(macos(10.7), ios(7.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface AVCaptureDeviceFormat (AVCaptureDeviceFormatCenterStage)

/*!
 @property centerStageSupported
 @abstract
    Indicates whether the format supports the Center Stage feature.
 
 @discussion
    This property returns YES if the format supports "Center Stage", which automatically adjusts the camera to keep people optimally framed within the field of view. See +AVCaptureDevice.centerStageEnabled for a detailed discussion.
 */
@property(nonatomic, readonly, getter=isCenterStageSupported) BOOL centerStageSupported API_AVAILABLE(ios(14.5), macCatalyst(14.5)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @property videoMinZoomFactorForCenterStage
 @abstract
    Indicates the minimum zoom factor available for the AVCaptureDevice's videoZoomFactor property when centerStageActive is YES.
 
 @discussion
    Devices support a limited zoom range when Center Stage is active. If this device format does not support Center Stage, this property returns 1.0.
 */
@property(nonatomic, readonly) CGFloat videoMinZoomFactorForCenterStage API_AVAILABLE(ios(14.5), macCatalyst(14.5)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @property videoMaxZoomFactorForCenterStage
 @abstract
    Indicates the maximum zoom factor available for the AVCaptureDevice's videoZoomFactor property when centerStageActive is YES.
 
 @discussion
    Devices support a limited zoom range when Center Stage is active. If this device format does not support Center Stage, this property returns videoMaxZoomFactor.
 */
@property(nonatomic, readonly) CGFloat videoMaxZoomFactorForCenterStage API_AVAILABLE(ios(14.5), macCatalyst(14.5)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @property videoFrameRateRangeForCenterStage
 @abstract
    Indicates the minimum / maximum frame rates available when centerStageActive is YES.
 
 @discussion
    Devices may support a limited frame rate range when Center Stage is active. If this device format does not support Center Stage, this property returns nil.
 */
@property(nonatomic, readonly, nullable) AVFrameRateRange *videoFrameRateRangeForCenterStage API_AVAILABLE(ios(14.5), macCatalyst(14.5)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

@end


API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos)
@interface AVCaptureDeviceFormat (AVCaptureDeviceFormatPortraitEffect)

/*!
 @property portraitEffectSupported
 @abstract
    Indicates whether the format supports the Portrait Effect feature.
 
 @discussion
    This property returns YES if the format supports Portrait Effect, the application of a shallow depth of field effect to objects in the background. See +AVCaptureDevice.portraitEffectEnabled for a detailed discussion.
 */
@property(nonatomic, readonly, getter=isPortraitEffectSupported) BOOL portraitEffectSupported API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

/*!
 @property videoFrameRateRangeForPortraitEffect
 @abstract
    Indicates the minimum / maximum frame rates available when portraitEffectActive is YES.
 
 @discussion
    Devices may support a limited frame rate range when Portrait Effect is active. If this device format does not support Portrait Effect, this property returns nil.
 */
@property(nonatomic, readonly, nullable) AVFrameRateRange *videoFrameRateRangeForPortraitEffect API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

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
API_AVAILABLE(macos(10.7)) API_UNAVAILABLE(ios, macCatalyst, watchos, tvos)
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
