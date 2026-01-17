#if !__has_include(<AVFCapture/AVCaptureInput.h>)
/*
    File:  AVCaptureInput.h
 
    Framework:  AVFoundation
 
    Copyright 2010-2024 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVMediaFormat.h>
#import <AVFoundation/AVCaptureDevice.h>
#import <AVFoundation/AVExternalSyncDevice.h>
#import <Foundation/Foundation.h>
#import <CoreMedia/CMFormatDescription.h>
#import <CoreMedia/CMSync.h>
#if TARGET_OS_OSX
#import <CoreGraphics/CGDirectDisplay.h>
#endif

NS_ASSUME_NONNULL_BEGIN

#pragma mark AVCaptureInput

@class AVCaptureInputPort;
@class AVCaptureInputInternal;
@class AVTimedMetadataGroup;

/*!
 @class AVCaptureInput
 @abstract
    AVCaptureInput is an abstract class that provides an interface for connecting capture input sources to an AVCaptureSession.
 
 @discussion
    Concrete instances of AVCaptureInput representing input sources such as cameras can be added to instances of AVCaptureSession using the -[AVCaptureSession addInput:] method. An AVCaptureInput vends one or more streams of media data. For example, input devices can provide both audio and video data. Each media stream provided by an input is represented by an AVCaptureInputPort object. Within a capture session, connections are made between AVCaptureInput instances and AVCaptureOutput instances via AVCaptureConnection objects that define the mapping between a set of AVCaptureInputPort objects and a single AVCaptureOutput.
 */
API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0), tvos(17.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface AVCaptureInput : NSObject
{
@private
    AVCaptureInputInternal *_inputInternal;
}

AV_INIT_UNAVAILABLE

/*!
 @property ports
 @abstract
    The ports owned by the receiver.
 
 @discussion
    The value of this property is an array of AVCaptureInputPort objects, each exposing an interface to a single stream of media data provided by an input.
 */
@property(nonatomic, readonly) NSArray<AVCaptureInputPort *> *ports API_UNAVAILABLE(visionos);

@end


/*!
 @constant AVCaptureInputPortFormatDescriptionDidChangeNotification
 @abstract
    This notification is posted when the value of an AVCaptureInputPort instance's formatDescription property changes.
 
 @discussion
    The notification object is the AVCaptureInputPort instance whose format description changed.
 */
AVF_EXPORT NSNotificationName const AVCaptureInputPortFormatDescriptionDidChangeNotification NS_SWIFT_NAME(AVCaptureInputPort.formatDescriptionDidChangeNotification) API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);


#pragma mark - AVCaptureInputPort

@class AVCaptureInputPortInternal;

/*!
 @class AVCaptureInputPort
 @abstract
    An AVCaptureInputPort describes a single stream of media data provided by an AVCaptureInput and provides an interface for connecting that stream to AVCaptureOutput instances via AVCaptureConnection.
 
 @discussion
    Instances of AVCaptureInputPort cannot be created directly. An AVCaptureInput exposes its input ports via its ports property. Input ports provide information about the format of their media data via the mediaType and formatDescription properties, and allow clients to control the flow of data via the enabled property. Input ports are used by an AVCaptureConnection to define the mapping between inputs and outputs in an AVCaptureSession.
 */
API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureInputPort : NSObject
{
@private
    AVCaptureInputPortInternal *_internal;
}

AV_INIT_UNAVAILABLE

/*!
 @property input
 @abstract
    The input that owns the receiver.
 
 @discussion
    The value of this property is an AVCaptureInput instance that owns the receiver.
 */
@property(nonatomic, readonly) AVCaptureInput *input;

/*!
 @property mediaType
 @abstract
    The media type of the data provided by the receiver.
 
 @discussion
    The value of this property is a constant describing the type of media, such as AVMediaTypeVideo or AVMediaTypeAudio, provided by the receiver. Media type constants are defined in AVMediaFormat.h.
 */
@property(nonatomic, readonly) AVMediaType mediaType;

/*!
 @property formatDescription
 @abstract
    The format of the data provided by the receiver.
 
 @discussion
    The value of this property is a CMFormatDescription that describes the format of the media data currently provided by the receiver. Clients can be notified of changes to the format by observing the AVCaptureInputPortFormatDescriptionDidChangeNotification.
 */
@property(nonatomic, readonly, nullable) __attribute__((NSObject)) CMFormatDescriptionRef formatDescription;

/*!
 @property enabled
 @abstract
    Whether the receiver should provide data.
 
 @discussion
    The value of this property is a BOOL that determines whether the receiver should provide data to outputs when a session is running. Clients can set this property to fine tune which media streams from a given input will be used during capture. The default value is YES.
 */
@property(nonatomic, getter=isEnabled) BOOL enabled;

/*!
 @property clock
 @abstract
    Provides access to the "native" clock used by the input port.
 
 @discussion
    The clock is read-only.
 */
@property(nonatomic, readonly, nullable) __attribute__((NSObject)) CMClockRef clock API_AVAILABLE(macos(10.9), ios(7.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos);

/*!
 @property sourceDeviceType
 @abstract
    The AVCaptureDeviceType of the source device providing input through this port.
 
 @discussion
    All AVCaptureInputPorts contained in an AVCaptureDeviceInput's ports array have the same sourceDeviceType, which is equal to deviceInput.device.deviceType. All of these ports are legal for use in an AVCaptureSession. When working with virtual devices such as the DualCamera in an AVCaptureMultiCamSession, it is possible to stream media from the virtual device's constituent device streams by discovering and connecting hidden ports. In the case of the DualCamera, its constituent devices are the WideAngle camera and the Telephoto camera. By calling -[AVCaptureDeviceInput portsWithMediaType:sourceDeviceType:sourceDevicePosition:], you may discover ports originating from one or more of the virtual device's constituent devices and then make connections using those ports. Constituent device ports are never present in their owning virtual device input's ports array. As an example, to find the video port originating from the DualCamera's Telephoto camera constituent device, you call [dualCameraDeviceInput portsWithMediaType:AVMediaTypeVideo sourceDeviceType:AVCaptureDeviceTypeBuiltInTelephotoCamera sourceDevicePosition:dualCamera.position] and use the first port in the resulting array.
 */
@property(nonatomic, readonly, nullable) AVCaptureDeviceType sourceDeviceType API_AVAILABLE(ios(13.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

/*!
 @property sourceDevicePosition
 @abstract
    The AVCaptureDevicePosition of the source device providing input through this port.
 
 @discussion
    All AVCaptureInputPorts contained in an AVCaptureDeviceInput's ports array have the same sourceDevicePosition, which is deviceInput.device.position. When working with microphone input in an AVCaptureMultiCamSession, it is possible to record multiple microphone directions simultaneously, for instance, to record front-facing microphone input to pair with video from the front facing camera, and back-facing microphone input to pair with the video from the back-facing camera. By calling -[AVCaptureDeviceInput portsWithMediaType:sourceDeviceType:sourceDevicePosition:], you may discover additional hidden ports originating from the source audio device. These ports represent individual microphones positioned to pick up audio from one particular direction. Examples follow.
 
        To discover the audio port that captures omnidirectional audio, use [microphoneDeviceInput portsWithMediaType:AVMediaTypeAudio sourceDeviceType:AVCaptureDeviceTypeMicrophone sourceDevicePosition:AVCaptureDevicePositionUnspecified].firstObject.
        To discover the audio port that captures front-facing audio, use [microphoneDeviceInput portsWithMediaType:AVMediaTypeAudio sourceDeviceType:AVCaptureDeviceTypeMicrophone sourceDevicePosition:AVCaptureDevicePositionFront].firstObject.
        To discover the audio port that captures back-facing audio, use [microphoneDeviceInput portsWithMediaType:AVMediaTypeAudio sourceDeviceType:AVCaptureDeviceTypeMicrophone sourceDevicePosition:AVCaptureDevicePositionBack].firstObject.
 */
@property(nonatomic, readonly) AVCaptureDevicePosition sourceDevicePosition API_AVAILABLE(ios(13.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

@end


#pragma mark - AVCaptureDeviceInput

@class AVCaptureDevice;
@class AVCaptureDeviceInputInternal;

/*!
 @class AVCaptureDeviceInput
 @abstract
    AVCaptureDeviceInput is a concrete subclass of AVCaptureInput that provides an interface for capturing media from an AVCaptureDevice.
 
 @discussion
    Instances of AVCaptureDeviceInput are input sources for AVCaptureSession that provide media data from devices connected to the system, represented by instances of AVCaptureDevice.
 */
API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0), tvos(17.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface AVCaptureDeviceInput : AVCaptureInput
{
@private
    AVCaptureDeviceInputInternal *_internal;
}

/*!
 @method deviceInputWithDevice:error:
 @abstract
    Returns an AVCaptureDeviceInput instance that provides media data from the given device.
 
 @param device
    An AVCaptureDevice instance to be used for capture.
 @param outError
    On return, if the given device cannot be used for capture, points to an NSError describing the problem.
 @result
    An AVCaptureDeviceInput instance that provides data from the given device, or nil, if the device could not be used for capture.
 
 @discussion
    This method returns an instance of AVCaptureDeviceInput that can be used to capture data from an AVCaptureDevice in an AVCaptureSession. This method attempts to open the device for capture, taking exclusive control of it if necessary. If the device cannot be opened because it is no longer available or because it is in use, for example, this method returns nil, and the optional outError parameter points to an NSError describing the problem.
 */
+ (nullable instancetype)deviceInputWithDevice:(AVCaptureDevice *)device error:(NSError * _Nullable * _Nullable)outError API_UNAVAILABLE(visionos);

/*!
 @method initWithDevice:error:
 @abstract
    Creates an AVCaptureDeviceInput instance that provides media data from the given device.
 
 @param device
    An AVCaptureDevice instance to be used for capture.
 @param outError
    On return, if the given device cannot be used for capture, points to an NSError describing the problem.
 @result
    An AVCaptureDeviceInput instance that provides data from the given device, or nil, if the device could not be used for capture.
 
 @discussion
    This method creates an instance of AVCaptureDeviceInput that can be used to capture data from an AVCaptureDevice in an AVCaptureSession. This method attempts to open the device for capture, taking exclusive control of it if necessary. If the device cannot be opened because it is no longer available or because it is in use, for example, this method returns nil, and the optional outError parameter points to an NSError describing the problem.
 */
- (nullable instancetype)initWithDevice:(AVCaptureDevice *)device error:(NSError * _Nullable * _Nullable)outError;

/*!
 @property device
 @abstract
    The device from which the receiver provides data.
 
 @discussion
    The value of this property is the AVCaptureDevice instance that was used to create the receiver.
 */
@property(nonatomic, readonly) AVCaptureDevice *device;

/*!
 @property unifiedAutoExposureDefaultsEnabled
 @abstract
    Specifies whether the source device should use the same default auto exposure behaviors for -[AVCaptureSession setSessionPreset:] and -[AVCaptureDevice setActiveFormat:].
 
 @discussion
    AVCaptureDevice's activeFormat property may be set two different ways. 1) You set it directly using one of the formats in the device's -formats array, or 2) the AVCaptureSession sets it on your behalf when you set the AVCaptureSession's sessionPreset property. Depending on the device and format, the default auto exposure behavior may be configured differently when you use one method or the other, resulting in non-uniform auto exposure behavior. Auto exposure defaults include min frame rate, max frame rate, and max exposure duration. If you wish to ensure that consistent default behaviors are applied to the device regardless of the API you use to configure the activeFormat, you may set the device input's unifiedAutoExposureDefaultsEnabled property to YES. Default value for this property is NO.
 
    Note that if you manually set the device's min frame rate, max frame rate, or max exposure duration, your custom values will override the device defaults regardless of whether you've set this property to YES.
 */
@property(nonatomic) BOOL unifiedAutoExposureDefaultsEnabled API_AVAILABLE(ios(12.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

/*!
 @method portsWithMediaType:sourceDeviceType:sourceDevicePosition:
 @abstract
    An accessor method used to retrieve a virtual device's constituent device ports for use in an AVCaptureMultiCamSession.
 
 @param mediaType
    The AVMediaType of the port for which you're searching, or nil if all media types should be considered.
 @param sourceDeviceType
    The AVCaptureDeviceType of the port for which you're searching, or nil if source device type is irrelevant.
 @param sourceDevicePosition
    The AVCaptureDevicePosition of the port for which you're searching. AVCaptureDevicePositionUnspecified is germane to audio devices, indicating omnidirectional audio. For other types of capture devices (e.g. cameras), AVCaptureDevicePositionUnspecified means all positions should be considered in the search.
 
 @result
    An array of AVCaptureInputPorts satisfying the search criteria, or an empty array could be found.
 
 @discussion
    When using AVCaptureMultiCamSession, multiple devices may be run simultaneously. You may also run simultaneous streams from a virtual device such as the Dual Camera. By inspecting a virtual device's constituentDevices property, you can find its underlying physical devices and, using this method, search for ports originating from one of those constituent devices. Note that the AVCaptureInput.ports array does not include constituent device ports for virtual devices. You must use this accessor method to discover the ports for which you're specifically looking. These constituent device ports may be used to make connections to outputs for use with an AVCaptureMultiCamSession. Using the Dual Camera as an example, the AVCaptureInput.ports property exposes only those ports supported by the virtual device (it switches automatically between wide and telephoto cameras according to the zoom factor). You may use this method to find the video ports for the constituentDevices.
 
         AVCaptureInputPort *wideVideoPort = [dualCameraInput portsWithMediaType:AVMediaTypeVideo sourceDeviceType:AVCaptureDeviceTypeBuiltInWideAngleCamera sourceDevicePosition:AVCaptureDevicePositionBack].firstObject;
         AVCaptureInputPort *teleVideoPort = [dualCameraInput portsWithMediaType:AVMediaTypeVideo sourceDeviceType:AVCaptureDeviceTypeBuiltInTelephotoCamera sourceDevicePosition:AVCaptureDevicePositionBack].firstObject;

    These ports may be used to create connections, say, to two AVCaptureVideoDataOutput instances, allowing for synchronized full frame rate delivery of both wide and telephoto streams.
 
    As of iOS 13, constituent device ports may not be connected to AVCapturePhotoOutput instances. Clients who wish to capture multiple photos from a virtual device should use AVCapturePhotoOutput's virtualDeviceConstituentPhotoDeliveryEnabled feature.
 
    When used in conjunction with an audio device, this method allows you to discover microphones in different AVCaptureDevicePositions. When you intend to work with an AVCaptureMultiCamSession, you may use these ports to make connections and simultaneously capture both front facing and back facing audio simultaneously to two different outputs. When used with an AVCaptureMultiCamSession, the audio device port whose sourceDevicePosition is AVCaptureDevicePositionUnspecified produces omnidirectional sound.
 */
- (NSArray<AVCaptureInputPort *> *)portsWithMediaType:(nullable AVMediaType)mediaType sourceDeviceType:(nullable AVCaptureDeviceType)sourceDeviceType sourceDevicePosition:(AVCaptureDevicePosition)sourceDevicePosition API_AVAILABLE(ios(13.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

/*!
 @property videoMinFrameDurationOverride
 @abstract
    A property that acts as a modifier to the AVCaptureDevice's activeVideoMinFrameDuration property. Default value is kCMTimeInvalid.
 
 @discussion
    An AVCaptureDevice's activeVideoMinFrameDuration property is the reciprocal of its active maximum frame rate. To limit the max frame rate of the capture device, clients may set the device's activeVideoMinFrameDuration to a value supported by the receiver's activeFormat (see AVCaptureDeviceFormat's videoSupportedFrameRateRanges property). Changes you make to the device's activeVideoMinFrameDuration property take effect immediately without disrupting preview. Therefore, the AVCaptureSession must always allocate sufficient resources to allow the device to run at its activeFormat's max allowable frame rate. If you wish to use a particular device format but only ever run it at lower frame rates (for instance, only run a 1080p240 fps format at a max frame rate of 60), you can set the AVCaptureDeviceInput's videoMinFrameDurationOverride property to the reciprocal of the max frame rate you intend to use before starting the session (or within a beginConfiguration / commitConfiguration block while running the session).
 
    When a device input is added to a session, this property reverts back to the default of kCMTimeInvalid (no override).
 */
@property(nonatomic) CMTime videoMinFrameDurationOverride API_AVAILABLE(ios(13.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

/// Indicates whether the device input supports locked frame durations.
///
/// See ``AVCaptureDeviceInput/activeLockedVideoFrameDuration`` for more information on video frame duration locking.
@property(nonatomic, readonly, getter=isLockedVideoFrameDurationSupported) BOOL lockedVideoFrameDurationSupported API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// The receiver's locked frame duration (the reciprocal of its frame rate). Setting this property guarantees the intra-frame duration delivered by the device input is precisely the frame duration you request.
///
/// Set this property to run the receiver's associated ``AVCaptureDevice`` at precisely your provided frame rate (expressed as a duration). Query ``AVCaptureDevice/minSupportedLockedVideoFrameDuration`` to find the minimum value supported by this ``AVCaptureDeviceInput``. In order to disable locked video frame duration, set this property to `kCMTimeInvalid`. This property resets itself to `kCMTimeInvalid` when the receiver's attached ``AVCaptureDevice/activeFormat`` changes. When you set this property, its value is also reflected in the receiver's ``AVCaptureDevice/activeVideoMinFrameDuration`` and ``AVCaptureDevice/activeVideoMaxFrameDuration``.
///
/// - Note: Locked frame duration availability may change depending on the device configuration. For example, locked frame duration is unsupported when ``AVCaptureDevice/autoVideoFrameRateEnabled`` or ``AVCaptureMovieFileOutput/spatialVideoCaptureEnabled`` is set to `true`.
///
/// - Note: Only one ``AVCaptureDeviceInput`` added to an ``AVCaptureMultiCamSession`` can follow an external sync device or run at a locked frame duration.
///
/// - Note: Setting this property may cause a lengthy reconfiguration of the receiver, similar to setting ``AVCaptureDevice/activeFormat`` or ``AVCaptureSession/sessionPreset``.
///
/// - Important: If you set this property to a valid value while the receiver's ``AVCaptureDevice/minSupportedLockedVideoFrameDuration`` is `kCMTimeInvalid`, it throws an `NSInvalidArgumentException`.
///
/// - Important: If you set this property while the receiver's  ``lockedVideoFrameDurationSupported`` property returns `false`, it throws an `NSInvalidArgumentException`.
@property(nonatomic) CMTime activeLockedVideoFrameDuration API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);


/// Indicates whether the device input supports being configured to follow an external sync device.
///
/// See ``AVCaptureDeviceInput/followExternalSyncDevice:videoFrameDuration:delegate:`` for more information on external sync.
@property(nonatomic, readonly, getter=isExternalSyncSupported) BOOL externalSyncSupported API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// Configures the the device input to follow an external sync device at the given frame duration.
///
/// - Parameter externalSyncDevice: The ``AVExternalSyncDevice`` hardware to follow.
/// - Parameter videoFrameDuration: The frame duration to which the ``AVExternalSyncDevice`` is calibrated.
/// - Parameter delegate: The delegate to notify when the connection status changes, or an error occurs.
///
/// Call this method to direct your ``AVCaptureDeviceInput`` to follow the external sync pulse from a sync device at the given frame duration.
///
/// Your provided `videoFrameDuration` value must match the sync pulse duration of the external sync device. If it does not, the request times out, the external sync device's status returns to ``AVExternalSyncDeviceStatusReady``, and your session stops running, posting a ``AVCaptureSessionRuntimeErrorNotification`` with ``AVErrorFollowExternalSyncDeviceTimedOut``.
///
/// The ability to follow an external sync device may change depending on the device configuration. For example, ``followExternalSyncDevice:videoFrameDuration:delegate:`` cannot be used when ``AVCaptureDevice/autoVideoFrameRateEnabled`` is `true`.
///
/// To stop following an external pulse, call ``unfollowExternalSyncDevice``. External sync device following is also disabled when your device's ``AVCaptureDeviceFormat`` changes.
///
/// Your provided delegate's ``AVExternalSyncDeviceDelegate/externalSyncDeviceStatusDidChange:`` method is called with a status of ``AVExternalSyncDeviceStatusReady`` if the external pulse signal is not close enough to the provided `videoFrameDuration` for successful calibration.
///
/// Once your ``AVExternalSyncDevice/status`` changes to ``AVExternalSyncDeviceStatusActiveSync``, your input's  ``AVCaptureInput/activeExternalSyncVideoFrameDuration`` property reports the up-to-date frame duration. ``AVCaptureInput/activeExternalSyncVideoFrameDuration`` is also reflected in the ``AVCaptureDevice/activeVideoMinFrameDuration`` and ``AVCaptureDevice/activeVideoMaxFrameDuration`` of your input's associated device.
///
/// - Note: Calling this method may cause a lengthy reconfiguration of the receiver, similar to setting a new active format or ``AVCaptureSession/sessionPreset``.
///
/// - Important: Calling this method throws an `NSInvalidArgumentException` if ``AVCaptureDeviceInput/externalSyncSupported`` returns `false`.
/// 
/// - Important: The provided external sync device's ``status`` must be ``AVExternalSyncDeviceStatusReady`` when you call this method, otherwise an `NSInvalidArgumentException` is thrown.
- (void)followExternalSyncDevice:(AVExternalSyncDevice *)externalSyncDevice videoFrameDuration:(CMTime)frameDuration delegate:(id <AVExternalSyncDeviceDelegate> _Nullable)delegate NS_SWIFT_NAME(follow(_:videoFrameDuration:delegate:)) API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// The receiver's external sync frame duration (the reciprocal of its frame rate) when being driven by an external sync device.
///
/// Set up your input to follow an external sync device by calling ``followExternalSyncDevice:videoFrameDuration:delegate:``.
/// - Note: The value of this readonly property is `kCMTimeInvalid` unless the ``AVExternalSyncDevice`` is actively driving the ``AVCaptureDeviceInput``. This is reflected by the ``AVExternalSyncDevice/status`` being either ``AVExternalSyncDeviceStatusActiveSync`` or ``AVExternalSyncDeviceStatusFreeRunSync``.
@property(nonatomic, readonly) CMTime activeExternalSyncVideoFrameDuration API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// The external sync device currently being followed by this input.
///
/// This readonly property returns the ``AVExternalSyncDevice`` instance you provided in ``followExternalSyncDevice:videoFrameDuration:delegate:``. This property returns `nil` when an external sync device is disconnected or fails to calibrate.
@property(nonatomic, readonly, nullable) AVExternalSyncDevice *externalSyncDevice API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// Discontinues external sync.
///
/// This method stops your input from syncing to the external sync device you specified in ``followExternalSyncDevice:videoFrameDuration:delegate:``.
- (void)unfollowExternalSyncDevice API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @enum AVCaptureMultichannelAudioMode
 @abstract
    Constants indicating the modes of multichannel audio.
 
 @constant AVCaptureMultichannelAudioModeNone
    Indicates that no multichannel audio should be used.
 @constant AVCaptureMultichannelAudioModeStereo
    Indicates that the audio should be recorded using stereo.
 @constant AVCaptureMultichannelAudioModeFirstOrderAmbisonics
    Indicates that the audio should be recorded using first-order ambisonics. When recording a QuickTime movie file, a stereo audio track will be recorded alongside the FOA track for backward playback compatibility.
 */
typedef NS_ENUM(NSInteger, AVCaptureMultichannelAudioMode) {
    AVCaptureMultichannelAudioModeNone                 = 0,
    AVCaptureMultichannelAudioModeStereo               = 1,
    AVCaptureMultichannelAudioModeFirstOrderAmbisonics = 2,
} API_AVAILABLE(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0)) API_UNAVAILABLE(watchos, visionos);

/*!
 @method isMultichannelAudioModeSupported:
 @abstract
    Returns whether the receiver supports the given multichannel audio mode.
 
 @param multichannelAudioMode
    An AVCaptureMultichannelAudioMode to be checked.
 @result
    YES if the receiver supports the given multichannel audio mode, NO otherwise.
 
 @discussion
    The receiver's multichannelAudioMode property can only be set to a certain mode if this method returns YES for that mode.
 
    Multichannel audio modes are not supported when used in conjunction with AVCaptureMultiCamSession.
 */
- (BOOL)isMultichannelAudioModeSupported:(AVCaptureMultichannelAudioMode)multichannelAudioMode API_AVAILABLE(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0)) API_UNAVAILABLE(watchos, visionos);

/*!
 @property multichannelAudioMode
 @abstract
    Indicates the multichannel audio mode to apply when recording audio.
 
 @discussion
    This property only takes effect when audio is being routed through the built-in microphone, and is ignored if an external microphone is in use.
    
    The default value is AVCaptureMultichannelAudioModeNone, in which case the default single channel audio recording is used.
 */
@property(nonatomic) AVCaptureMultichannelAudioMode multichannelAudioMode API_AVAILABLE(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0)) API_UNAVAILABLE(watchos, visionos);

/*!
 @property windNoiseRemovalSupported
 @abstract
    Returns whether or not the device supports wind noise removal during audio capture.
 
 @discussion
    YES if the device supports wind noise removal, NO otherwise.
 */
@property(nonatomic, readonly, getter=isWindNoiseRemovalSupported) BOOL windNoiseRemovalSupported API_AVAILABLE(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @property windNoiseRemovalEnabled
 @abstract
    Specifies whether or not wind noise is removed during audio capture.
 
 @discussion
    Wind noise removal is available when the AVCaptureDeviceInput multichannelAudioMode property is set to any value other than AVCaptureMultichannelAudioModeNone.
 */
@property(nonatomic, getter=isWindNoiseRemovalEnabled) BOOL windNoiseRemovalEnabled API_AVAILABLE(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// A BOOL value specifying whether Cinematic Video capture is supported.
///
/// With Cinematic Video capture, you get a simulated depth-of-field effect that keeps your subjects (people, pets, and more) in sharp focus while applying a pleasing blur to the background (or foreground). Depending on the focus mode (see ``AVCaptureCinematicVideoFocusMode`` for detail), the camera either uses machine learning to automatically detect and focus on subjects in the scene, or it fixes focus on a subject until it exits the scene. Cinematic Videos can be played back and edited using the Cinematic framework.
///
/// You can adjust the video's simulated aperture before starting a recording using the ``simulatedAperture`` property. With Cinematic Video specific focus methods on ``AVCaptureDevice``, you can dynamically control focus transitions.
///
/// Movie files captured with Cinematic Video enabled can be played back and edited with the [Cinematic framework] (https://developer.apple.com/documentation/cinematic/playing-and-editing-cinematic-mode-video?language=objc).
///
/// This property returns `true` if the session's current configuration allows Cinematic Video capture. When switching cameras or formats, this property may change. When this property changes from `true` to `false`, ``cinematicVideoCaptureEnabled`` also reverts to `false`. If you've previously opted in for Cinematic Video capture and then change configuration, you may need to set ``cinematicVideoCaptureEnabled`` to `true` again. This property is key-value observable.
///
/// - Note: ``AVCaptureDepthDataOutput`` is not supported when ``cinematicVideoCaptureEnabled`` is set to `true`. Running an ``AVCaptureSession`` with both of these features throws an `NSInvalidArgumentException`.
@property(nonatomic, readonly, getter=isCinematicVideoCaptureSupported) BOOL cinematicVideoCaptureSupported API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// A BOOL value specifying whether the Cinematic Video effect is being applied to any movie file output, video data output, metadata output, or video preview layer added to the capture session.
///
/// Default is `false`. Set to `true` to enable support for Cinematic Video capture.
///
/// When you set this property to `true`, your input's associated ``AVCaptureDevice/focusMode`` changes to ``AVCaptureFocusModeContinuousAutoFocus``. While Cinematic Video capture is enabled, you are not permitted to change your device's focus mode, and any attempt to do so results in an `NSInvalidArgumentException`. You may only set this property to `true` if ``cinematicVideoCaptureSupported`` is `true`.
///
/// - Note: Enabling Cinematic Video capture requires a lengthy reconfiguration of the capture render pipeline, so if you intend to capture Cinematic Video, you should set this property to `true` before calling ``AVCaptureSession/startRunning`` or within ``AVCaptureSession/beginConfiguration`` and ``AVCaptureSession/commitConfiguration`` while running.
@property(nonatomic, getter=isCinematicVideoCaptureEnabled) BOOL cinematicVideoCaptureEnabled API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// Shallow depth of field simulated aperture.
///
/// When capturing a Cinematic Video, use this property to control the amount of blur in the simulated depth of field effect.
///
/// This property only takes effect when ``cinematicVideoCaptureEnabled`` is set to `true`.
///
/// - Important: Setting this property to a value less than the ``AVCaptureDevice/activeFormat/minSimulatedAperture`` or greater than the ``AVCaptureDevice/activeFormat/maxSimulatedAperture`` throws an `NSRangeException`. you may only set this property if ``AVCaptureDevice/activeFormat/minSimulatedAperture`` returns a non-zero value, otherwise an `NSInvalidArgumentException` is thrown. You must set this property before starting a Cinematic Video capture. If you attempt to set it while a recording is in progress, an `NSInvalidArgumentException` is thrown.
///
/// This property is initialized to the associated ``AVCaptureDevice/activeFormat/defaultSimulatedAperture``.
///
/// This property is key-value observable.
@property(nonatomic) float simulatedAperture API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

@end


#pragma mark - AVCaptureScreenInput

@class AVCaptureScreenInputInternal;

/*!
 @class AVCaptureScreenInput
 @abstract
    AVCaptureScreenInput is a concrete subclass of AVCaptureInput that provides an interface for capturing media from a screen or portion thereof.
 
 @discussion
    Instances of AVCaptureScreenInput are input sources for AVCaptureSession that provide media data from one of the screens connected to the system, represented by CGDirectDisplayIDs.
 */
API_AVAILABLE(macos(10.7)) API_UNAVAILABLE(ios, macCatalyst, watchos, tvos, visionos)
@interface AVCaptureScreenInput : AVCaptureInput
{
@private
    AVCaptureScreenInputInternal *_internal;
}

/*!
 @method init
 @abstract
    Creates an AVCaptureScreenInput instance that provides media data from the main display.
 
 @discussion
    This method creates an instance of AVCaptureScreenInput using the main display whose id is returned from CGMainDisplayID().
 */
- (instancetype)init;

+ (instancetype)new;

#if TARGET_OS_OSX

/*!
 @method initWithDisplayID:
 @abstract
    Creates an AVCaptureScreenInput instance that provides media data from the given display.
 
 @param displayID
    The id of the display from which to capture video. CGDirectDisplayID is defined in <CoreGraphics/CGDirectDisplay.h>
 @result
    An AVCaptureScreenInput instance that provides data from the given screen, or nil, if the screen could not be used for capture.
 
 @discussion
    This method creates an instance of AVCaptureScreenInput that can be used to capture data from a display in an AVCaptureSession. This method validates the displayID. If the display cannot be used because it is not available on the system, for example, this method returns nil.
 */
- (nullable instancetype)initWithDisplayID:(CGDirectDisplayID)displayID;

#endif // TARGET_OS_OSX

/*!
 @property minFrameDuration
 @abstract
    A property indicating the screen input's minimum frame duration.
 
 @discussion
    An AVCaptureScreenInput's minFrameDuration is the reciprocal of its maximum frame rate. This property may be used to request a maximum frame rate at which the input produces video frames. The requested rate may not be achievable due to overall bandwidth, so actual frame rates may be lower.
 */
@property(nonatomic) CMTime minFrameDuration;

/*!
 @property cropRect
 @abstract
    A property indicating the bounding rectangle of the screen area to be captured in points.
 
 @discussion
    By default, AVCaptureScreenInput captures the entire area of the displayID with which it is associated. To limit the capture rectangle to a subsection of the screen, set the cropRect property, which defines a smaller section of the screen in the screen's coordinate system. The origin (0,0) is the bottom-left corner of the screen.
 */
@property(nonatomic) CGRect cropRect;

/*!
 @property scaleFactor
 @abstract
    A property indicating the factor by which video buffers captured from the screen are to be scaled.
 
 @discussion
    By default, AVCaptureScreenInput captures the video buffers from the display at a scale factor of 1.0 (no scaling). Set this property to scale the buffers by a given factor. For instance, a 320x240 capture area with a scaleFactor of 2.0f produces video buffers at 640x480.
 */
@property(nonatomic) CGFloat scaleFactor;

/*!
 @property capturesMouseClicks
 @abstract
    A property indicating whether mouse clicks should be highlighted in the captured output.
 
 @discussion
    By default, AVCaptureScreenInput does not highlight mouse clicks in its captured output. If this property is set to YES, mouse clicks are highlighted (a circle is drawn around the mouse for the duration of the click) in the captured output.
 */
@property(nonatomic) BOOL capturesMouseClicks;

/*!
 @property capturesCursor
 @abstract
    A property indicating whether the cursor should be rendered to the captured output.
 
 @discussion
    By default, AVCaptureScreenInput draws the cursor in its captured output. If this property is set to NO, the captured output contains only the windows on the screen. Cursor is omitted. Note that cursor position and mouse button state at the time of capture is preserved in CMSampleBuffers emitted from AVCaptureScreenInput. See the inline documentation for kCMIOSampleBufferAttachmentKey_MouseAndKeyboardModifiers in <CoreMediaIO/CMIOSampleBuffer.h>
 */
@property(nonatomic) BOOL capturesCursor API_AVAILABLE(macos(10.8));

/*!
 @property removesDuplicateFrames
 @abstract
    A property indicating whether duplicate frames should be removed by the input.
 
 @discussion
    If this property is set to YES, AVCaptureScreenInput performs frame differencing and when it detects duplicate frames, it drops them. If set to NO, the captured output receives all frames from the input. Prior to 10.9 this value defaulted to YES. In 10.9 and later, it defaults to NO, as modern platforms support frame differencing in hardware-based encoders.
 
    As of 10.10, this property has been deprecated and is ignored. Clients wishing to re-create this functionality can use an AVCaptureVideoDataOutput and compare frame contents in their own code. If they wish to write a movie file, they can then pass the unique frames to an AVAssetWriterInput.
 */
@property(nonatomic) BOOL removesDuplicateFrames API_DEPRECATED("No longer supported.", macos(10.8, 10.10));

@end


#pragma mark - AVCaptureMetadataInput

@class AVCaptureMetadataInputInternal;

/*!
 @class AVCaptureMetadataInput
 @abstract
    AVCaptureMetadataInput is a concrete subclass of AVCaptureInput that provides a way for clients to supply AVMetadataItems to an AVCaptureSession.
 
 @discussion
    Instances of AVCaptureMetadataInput are input sources for AVCaptureSession that provide AVMetadataItems to an AVCaptureSession. AVCaptureMetadataInputs present one and only one AVCaptureInputPort, which currently may only be connected to an AVCaptureMovieFileOutput. The metadata supplied over the input port is provided by the client, and must conform to a client-supplied CMFormatDescription. The AVMetadataItems are supplied in an AVTimedMetadataGroup.
 */
API_AVAILABLE(ios(9.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureMetadataInput : AVCaptureInput
{
@private
    AVCaptureMetadataInputInternal *_internal;
}

/*!
 @method metadataInputWithFormatDescription:clock:
 @abstract
    Returns an AVCaptureMetadataInput instance that allows a client to provide AVTimedMetadataGroups to an AVCaptureSession.
 
 @param desc
    A CMFormatDescription that defines the metadata to be supplied by the client. Throws an NSInvalidArgumentException if NULL is passed.
 @param clock
    A CMClock that provided the timebase for the supplied samples. Throws an NSInvalidArgumentException if NULL is passed.
 @result
    An AVCaptureMetadataInput instance.
 
 @discussion
    This method returns an instance of AVCaptureMetadataInput that can be used to capture AVTimedMetadataGroups supplied by the client to an AVCaptureSession.
 */
+ (instancetype)metadataInputWithFormatDescription:(CMMetadataFormatDescriptionRef)desc clock:(CMClockRef)clock;

/*!
 @method initWithFormatDescription:clock:
 @abstract
    Creates an AVCaptureMetadataInput instance that allows a client to provide AVTimedMetadataGroups to an AVCaptureSession.
 
 @param desc
    A CMFormatDescription that defines the metadata to be supplied by the client. Throws NSInvalidArgumentException if NULL is passed.
 @param clock
    A CMClock that provided the timebase for the supplied samples. Throws NSInvalidArgumentException if NULL is passed.
 @result
    An AVCaptureMetadataInput instance, or nil, if the device could not be used for capture.
 
 @discussion
    This method creates an instance of AVCaptureMetadataInput that can be used to capture AVTimedMetadataGroups supplied by the client to an AVCaptureSession.
 */
- (instancetype)initWithFormatDescription:(CMMetadataFormatDescriptionRef)desc clock:(CMClockRef)clock;

/*!
 @method appendTimedMetadataGroup:
 @abstract
    Provides metadata to the AVCaptureSession.
 
 @param metadata
    An AVTimedMetadataGroup of metadata. Will throw an exception if nil. In order to denote a period of no metadata, an empty AVTimedMetadataGroup should be passed.
 
 @discussion
    The provided AVTimedMetadataGroup will be provided to the AVCaptureSession. The group's presentation timestamp is expressed in the context of the clock supplied to the initializer. It is not required that the AVTimedMetadataGroup have a duration; an empty AVTimedMetadataGroup can be supplied to denote a period of no metadata.
 */
- (BOOL)appendTimedMetadataGroup:(AVTimedMetadataGroup *)metadata error:(NSError * _Nullable * _Nullable)outError;

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCapture/AVCaptureInput.h>
#endif
