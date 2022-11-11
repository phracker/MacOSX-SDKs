#if !__has_include(<AVFCapture/AVCapturePhotoOutput.h>)
/*
    File:  AVCapturePhotoOutput.h
 
    Framework:  AVFoundation
 
    Copyright 2016-2021 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVCaptureOutputBase.h>
#import <AVFoundation/AVVideoSettings.h>
#import <AVFoundation/AVSemanticSegmentationMatte.h>
#import <CoreMedia/CMSampleBuffer.h>
#import <CoreMedia/CMTimeRange.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark AVCapturePhotoOutput

@class AVCapturePhotoSettings;
@class AVCapturePhotoBracketSettings;
@class AVCaptureResolvedPhotoSettings;
@class AVCaptureBracketedStillImageSettings;
@class AVMetadataItem;
@class AVPortraitEffectsMatte;
@class AVCapturePhotoOutputInternal;


@protocol AVCapturePhotoCaptureDelegate;

/*!
 @class AVCapturePhotoOutput
 @abstract
    AVCapturePhotoOutput is a concrete subclass of AVCaptureOutput that supersedes AVCaptureStillImageOutput as the preferred interface for capturing photos. In addition to capturing all flavors of still image supported by AVCaptureStillImageOutput, it supports Live Photo capture, preview-sized image delivery, wide color, RAW, RAW+JPG and RAW+DNG formats.
 
 @discussion
    Taking a photo is multi-step process. Clients wishing to build a responsive UI need to know about the progress of a photo capture request as it advances from capture to processing to finished delivery. AVCapturePhotoOutput informs clients of photo capture progress through a delegate protocol. To take a picture, a client instantiates and configures an AVCapturePhotoSettings object, then calls AVCapturePhotoOutput's -capturePhotoWithSettings:delegate:, passing a delegate to be informed when events relating to the photo capture occur (e.g., the photo is about to be captured, the photo has been captured but not processed yet, the Live Photo movie is ready, etc.).
 
    Some AVCapturePhotoSettings properties can be set to "Auto", such as flashMode. When set to AVCaptureFlashModeAuto, the photo output decides at capture time whether the current scene and lighting conditions require use of the flash. Thus the client doesn't know with certainty which features will be enabled when making the capture request. With the first and each subsequent delegate callback, the client is provided an AVCaptureResolvedPhotoSettings instance that indicates the settings that were applied to the capture. All "Auto" features have now been resolved to on or off. The AVCaptureResolvedPhotoSettings object passed in the client's delegate callbacks has a uniqueID identical to the AVCapturePhotoSettings request. This uniqueID allows clients to pair unresolved and resolved settings objects. See AVCapturePhotoCaptureDelegate below for a detailed discussion of the delegate callbacks.
 
    Enabling certain photo features (Live Photo capture and high resolution capture) requires a reconfiguration of the capture render pipeline. Clients wishing to opt in for these features should call -setLivePhotoCaptureEnabled: and/or -setHighResolutionCaptureEnabled: before calling -startRunning on the AVCaptureSession. Changing any of these properties while the session is running requires a disruptive reconfiguration of the capture render pipeline. Live Photo captures in progress will be ended immediately; unfulfilled photo requests will be aborted; video preview will temporarily freeze. If you wish to capture Live Photos containing sound, you must add an audio AVCaptureDeviceInput to your AVCaptureSession.

    Simultaneous Live Photo capture and MovieFileOutput capture is not supported. If an AVCaptureMovieFileOutput is added to your session, AVCapturePhotoOutput's livePhotoCaptureSupported property returns NO. Note that simultaneous Live Photo capture and AVCaptureVideoDataOutput is supported.
 
    AVCaptureStillImageOutput and AVCapturePhotoOutput may not both be added to a capture session. You must use one or the other. If you add both to a session, a NSInvalidArgumentException is thrown.
 
    AVCapturePhotoOutput implicitly supports wide color photo capture, following the activeColorSpace of the source AVCaptureDevice. If the source device's activeColorSpace is AVCaptureColorSpace_P3_D65, photos are encoded with wide color information, unless you've specified an output format of '420v', which does not support wide color.
 */
API_AVAILABLE(macos(10.15), ios(10.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface AVCapturePhotoOutput : AVCaptureOutput
{
@private
    AVCapturePhotoOutputInternal *_internal;
}

- (instancetype)init;

+ (instancetype)new;

/*!
 @method capturePhotoWithSettings:delegate:
 @abstract
    Method for initiating a photo capture request with progress monitoring through the supplied delegate.
 
 @param settings
    An AVCapturePhotoSettings object you have configured. May not be nil.
 @param delegate
    An object conforming to the AVCapturePhotoCaptureDelegate protocol. This object's delegate methods are called back as the photo advances from capture to processing to finished delivery. May not be nil.
 
 @discussion
    This method initiates a photo capture. The receiver copies your provided settings to prevent unintentional mutation. It is illegal to re-use settings. The receiver throws a NSInvalidArgumentException if your settings.uniqueID matches that of any previously used settings. This method is used to initiate all flavors of photo capture: single photo, RAW capture with or without a processed image (such as a JPEG), bracketed capture, and Live Photo.
 
    Clients need not wait for a capture photo request to complete before issuing another request. This is true for single photo captures as well as Live Photos, where movie complements of adjacent photo captures are allowed to overlap.
 
    This method validates your settings and enforces the following rules in order to ensure deterministic behavior. If any of these rules are violated, a NSInvalidArgumentException is thrown.
    RAW rules:
        See +isBayerRAWPixelFormat: and +isAppleProRAWPixelFormat: on the difference between Bayer RAW and Apple ProRAW pixel formats.
        Common RAW rules:
        - If rawPhotoPixelFormatType is non-zero, it must be present in the receiver's -availableRawPhotoPixelFormatTypes array.
        - If rawPhotoPixelFormatType is non-zero, your delegate must respond to -captureOutput:didFinishProcessingRawPhotoSampleBuffer:previewPhotoSampleBuffer:resolvedSettings:bracketSettings:error:.
        - If rawPhotoPixelFormatType is non-zero, highResolutionPhotoEnabled may be YES or NO, but the setting only applies to the processed image, if you've specified one.
        - If rawFileType is specified, it must be present in -availableRawPhotoFileTypes and must support the rawPhotoPixelFormatType specified using -supportedRawPhotoPixelFormatTypesForFileType:.
        Bayer RAW rules (isBayerRAWPixelFormat: returns yes for rawPhotoPixelFormatType):
        - photoQualityPrioritization must be set to AVCapturePhotoQualityPrioritizationSpeed (deprecated autoStillImageStabilizationEnabled must be set to NO).
        - the videoZoomFactor of the source device and the videoScaleAndCropFactor of the photo output's video connection must both be 1.0. Ensure no zoom is applied before requesting a RAW capture, and don't change the zoom during RAW capture.
        Apple ProRAW rules (isAppleProRAWPixelFormat: returns yes for rawPhotoPixelFormatType):
        - livePhotoMovieFileURL must be nil in AVCapturePhotoSettings settings
        - autoContentAwareDistortionCorrectionEnabled will automatically be disabled in AVCapturePhotoSettings
        - autoRedEyeReductionEnabled will automatically be disabled in AVCapturePhotoSettings
        - portraitEffectsMatteDeliveryEnabled will automatically be disabled in AVCapturePhotoSettings
        - enabledSemanticSegmentationMatteTypes will automatically be cleared in AVCapturePhotoSettings
    Processed Format rules:
        - If format is non-nil, a kCVPixelBufferPixelFormatTypeKey or AVVideoCodecKey must be present, and both may not be present.
        - If format has a kCVPixelBufferPixelFormatTypeKey, its value must be present in the receiver's -availablePhotoPixelFormatTypes array.
        - If format has a AVVideoCodecKey, its value must be present in the receiver's -availablePhotoCodecTypes array.
        - If format is non-nil, your delegate must respond to -captureOutput:didFinishProcessingPhotoSampleBuffer:previewPhotoSampleBuffer:resolvedSettings:bracketSettings:error:.
        - If processedFileType is specified, it must be present in -availablePhotoFileTypes and must support the format's specified kCVPixelBufferPixelFormatTypeKey (using -supportedPhotoPixelFormatTypesForFileType:) or AVVideoCodecKey (using -supportedPhotoCodecTypesForFileType:).
        - The photoQualityPrioritization you specify may not be a greater number than the photo output's maxPhotoQualityPrioritization. You must set your AVCapturePhotoOutput maxPhotoQualityPrioritization up front.
    Flash rules:
        - The specified flashMode must be present in the receiver's -supportedFlashModes array.
    Live Photo rules:
        - The receiver's livePhotoCaptureEnabled must be YES if settings.livePhotoMovieURL is non-nil.
        - If settings.livePhotoMovieURL is non-nil, the receiver's livePhotoCaptureSuspended property must be set to NO.
        - If settings.livePhotoMovieURL is non-nil, it must be a file URL that's accessible to your app's sandbox.
        - If settings.livePhotoMovieURL is non-nil, your delegate must respond to -captureOutput:didFinishProcessingLivePhotoToMovieFileAtURL:duration:photoDisplayTime:resolvedSettings:error:.
    Bracketed capture rules:
        - bracketedSettings.count must be <= the receiver's maxBracketedCapturePhotoCount property.
        - For manual exposure brackets, ISO value must be within the source device activeFormat's minISO and maxISO values.
        - For manual exposure brackets, exposureDuration value must be within the source device activeFormat's minExposureDuration and maxExposureDuration values.
        - For auto exposure brackets, exposureTargetBias value must be within the source device's minExposureTargetBias and maxExposureTargetBias values.
 */
- (void)capturePhotoWithSettings:(AVCapturePhotoSettings *)settings delegate:(id<AVCapturePhotoCaptureDelegate>)delegate;

/*!
 @property preparedPhotoSettingsArray
 @abstract
    An array of AVCapturePhotoSettings instances for which the receiver is prepared to capture.

 @discussion
    See also setPreparedPhotoSettingsArray:completionHandler:
    Some types of photo capture, such as bracketed captures and RAW captures, require the receiver to allocate additional buffers or prepare other resources. To prevent photo capture requests from executing slowly due to lazy resource allocation, you may call -setPreparedPhotoSettingsArray:completionHandler: with an array of settings objects representative of the types of capture you will be performing (e.g., settings for a bracketed capture, RAW capture, and/or still image stabilization capture). By default, the receiver prepares sufficient resources to capture photos with default settings, +[AVCapturePhotoSettings photoSettings].
 */
@property(nonatomic, readonly) NSArray<AVCapturePhotoSettings *> *preparedPhotoSettingsArray API_UNAVAILABLE(macos);

/*!
 @method setPreparedPhotoSettingsArray:completionHandler:
 @abstract
    Method allowing the receiver to prepare resources in advance for future -capturePhotoWithSettings:delegate: requests.
 
 @param preparedPhotoSettingsArray
    An array of AVCapturePhotoSettings instances indicating the types of capture for which the receiver should prepare resources.
 @param completionHandler
    A completion block to be fired on a serial dispatch queue once the receiver has finished preparing. You may pass nil to indicate you do not wish to be called back when preparation is complete.
 
 @discussion
    Some types of photo capture, such as bracketed captures and RAW captures, require the receiver to allocate additional buffers or prepare other resources. To prevent photo capture requests from executing slowly due to lazy resource allocation, you may call this method with an array of settings objects representative of the types of capture you will be performing (e.g., settings for a bracketed capture, RAW capture, and/or still image stabilization capture). You may call this method even before calling -[AVCaptureSession startRunning] in order to hint the receiver up front which features you'll be utilizing. Each time you call this method with an array of settings, the receiver evaluates what additional resources it needs to allocate, as well as existing resources that can be reclaimed, and calls back your completionHandler when it has finished preparing (and possibly reclaiming) needed resources. By default, the receiver prepares sufficient resources to capture photos with default settings, +[AVCapturePhotoSettings photoSettings]. If you wish to reclaim all possible resources, you may call this method with an empty array.
 
    Preparation for photo capture is always optional. You may call -capturePhotoWithSettings:delegate: without first calling -setPreparedPhotoSettingsArray:completionHandler:, but be advised that some of your photo captures may execute slowly as additional resources are allocated just-in-time.
 
    If you call this method while your AVCaptureSession is not running, your completionHandler does not fire immediately. It only fires once you've called -[AVCaptureSession startRunning], and the needed resources have actually been prepared. If you call -setPreparedPhotoSettingsArray:completionHandler: with an array of settings, and then call it a second time, your first prepare call's completionHandler fires immediately with prepared == NO.
 
    Prepared settings persist across session starts/stops and committed configuration changes. This property participates in -[AVCaptureSession beginConfiguration] / -[AVCaptureSession commitConfiguration] deferred work behavior. That is, if you call -[AVCaptureSession beginConfiguration], change your session's input/output topology, and call this method, preparation is deferred until you call -[AVCaptureSession commitConfiguration], enabling you to atomically commit a new configuration as well as prepare to take photos in that new configuration.
 */
- (void)setPreparedPhotoSettingsArray:(NSArray<AVCapturePhotoSettings *> *)preparedPhotoSettingsArray completionHandler:(nullable void (^)(BOOL prepared, NSError * _Nullable error))completionHandler API_UNAVAILABLE(macos) NS_SWIFT_ASYNC_THROWS_ON_FALSE(1);

/*!
 @property availablePhotoPixelFormatTypes
 @abstract
    An array of kCVPixelBufferPixelFormatTypeKey values that are currently supported by the receiver.

 @discussion
    If you wish to capture a photo in an uncompressed format, such as 420f, 420v, or BGRA, you must ensure that the format you want is present in the receiver's availablePhotoPixelFormatTypes array. If you've not yet added your receiver to an AVCaptureSession with a video source, no pixel format types are available. This property is key-value observable.
 */
@property(nonatomic, readonly) NSArray<NSNumber *> *availablePhotoPixelFormatTypes;

/*!
 @property availablePhotoCodecTypes
 @abstract
    An array of AVVideoCodecKey values that are currently supported by the receiver.

 @discussion
    If you wish to capture a photo in a compressed format, such as JPEG, you must ensure that the format you want is present in the receiver's availablePhotoCodecTypes array. If you've not yet added your receiver to an AVCaptureSession with a video source, no codec types are available. This property is key-value observable.
 */
@property(nonatomic, readonly) NSArray<AVVideoCodecType> *availablePhotoCodecTypes;

/*!
 @property appleProRAWSupported
 @abstract
    Indicates whether the current configuration supports Apple ProRAW pixel formats.
 
 @discussion
	The AVCapturePhotoSettings appleProRAWEnabled property may only be set to YES if this property returns YES. This property is key-value observable.
 */
@property(nonatomic, readonly, getter=isAppleProRAWSupported) BOOL appleProRAWSupported API_AVAILABLE(ios(14.3), macCatalyst(14.3)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @property appleProRAWEnabled
 @abstract
    Indicates whether the photo output is configured for delivery of Apple ProRAW pixel formats as well as Bayer RAW formats.
 
 @discussion
    Setting this property to YES will enable support for taking photos in Apple ProRAW pixel formats. These formats will be added to -availableRawPhotoPixelFormatTypes after any existing Bayer RAW formats. Compared to photos taken with a Bayer RAW format, these photos will be demosaiced and partially processed. They are still scene-referred, and allow capturing RAW photos in modes where there is no traditional sensor/Bayer RAW available. Examples are any modes that rely on fusion of multiple captures. Use +isBayerRAWPixelFormat: to determine if a pixel format in -availableRawPhotoPixelFormatTypes is a Bayer RAW format, and +isAppleProRAWPixelFormat: to determine if it is an Apple ProRAW format. When writing an Apple ProRAW buffer to a DNG file, the resulting file is known as "Linear DNG". Apple ProRAW formats are not supported on all platforms and devices. This property may only be set to YES if appleProRAWSupported returns YES. This property is key-value observable.
 
    Enabling this property requires a lengthy reconfiguration of the capture render pipeline, so you should set this property to YES before calling -[AVCaptureSession startRunning].
 */
@property(nonatomic, getter=isAppleProRAWEnabled) BOOL appleProRAWEnabled API_AVAILABLE(ios(14.3), macCatalyst(14.3)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @method isBayerRAWPixelFormat:
 @abstract
    Returns YES if the given pixel format is a Bayer RAW format.
 
 @discussion
    May be used to distinguish Bayer RAW from Apple ProRAW pixel formats in -availableRawPhotoPixelFormatTypes once appleProRAWEnabled has been set to YES.
 */
+ (BOOL)isBayerRAWPixelFormat:(OSType)pixelFormat API_AVAILABLE(ios(14.3), macCatalyst(14.3)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @method isAppleProRAWPixelFormat:
 @abstract
    Returns YES if the given pixel format is an Apple ProRAW format.
 
 @discussion
    May be used to distinguish Bayer RAW from Apple ProRAW pixel formats in -availableRawPhotoPixelFormatTypes once appleProRAWEnabled has been set to YES.
 
    See appleProRAWEnabled for more information on Apple ProRAW.
 */
+ (BOOL)isAppleProRAWPixelFormat:(OSType)pixelFormat API_AVAILABLE(ios(14.3), macCatalyst(14.3)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @property availableRawPhotoPixelFormatTypes
 @abstract
    An array of RAW CVPixelBufferPixelFormatTypeKey values that are currently supported by the receiver.

 @discussion
    If you wish to capture a RAW photo, you must ensure that the RAW format you want is present in the receiver's availableRawPhotoPixelFormatTypes array. If you've not yet added your receiver to an AVCaptureSession with a video source, no RAW formats are available. See AVCapturePhotoOutput.appleProRAWEnabled on how to enable support for partially processed RAW formats. This property is key-value observable. RAW capture is not supported on all platforms.
 */
@property(nonatomic, readonly) NSArray<NSNumber *> *availableRawPhotoPixelFormatTypes API_UNAVAILABLE(macos);

/*!
 @property availablePhotoFileTypes
 @abstract
    An array of AVFileType values that are currently supported by the receiver.

 @discussion
    If you wish to capture a photo that is formatted for a particular file container, such as HEIF, you must ensure that the fileType you desire is present in the receiver's availablePhotoFileTypes array. If you've not yet added your receiver to an AVCaptureSession with a video source, no file types are available. This property is key-value observable.
 */
@property(nonatomic, readonly) NSArray<AVFileType> *availablePhotoFileTypes API_AVAILABLE(ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos);

/*!
 @property availableRawPhotoFileTypes
 @abstract
    An array of AVFileType values that are currently supported by the receiver for RAW capture.

 @discussion
    If you wish to capture a RAW photo that is formatted for a particular file container, such as DNG, you must ensure that the fileType you desire is present in the receiver's availableRawPhotoFileTypes array. If you've not yet added your receiver to an AVCaptureSession with a video source, no file types are available. This property is key-value observable.
 */
@property(nonatomic, readonly) NSArray<AVFileType> *availableRawPhotoFileTypes API_AVAILABLE(ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @method supportedPhotoPixelFormatTypesForFileType:
 @abstract
    An array of pixel format type values that are currently supported by the receiver for a particular file container.
 
 @param fileType
    The AVFileType container type intended for storage of a photo.
 @result
    An array of CVPixelBufferPixelFormatTypeKey values supported by the receiver for the file type in question.
 
 @discussion
    If you wish to capture a photo for storage in a particular file container, such as TIFF, you must ensure that the photo pixel format type you request is valid for that file type. If no pixel format types are supported for a given fileType, an empty array is returned. If you've not yet added your receiver to an AVCaptureSession with a video source, no pixel format types are supported.
 */
- (NSArray<NSNumber *> *)supportedPhotoPixelFormatTypesForFileType:(AVFileType)fileType API_AVAILABLE(ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos);

/*!
 @method supportedPhotoCodecTypesForFileType:
 @abstract
    An array of AVVideoCodecKey values that are currently supported by the receiver for a particular file container.
 
 @param fileType
    The AVFileType container type intended for storage of a photo.
 @result
    An array of AVVideoCodecKey values supported by the receiver for the file type in question.
 
 @discussion
    If you wish to capture a photo for storage in a particular file container, such as HEIF, you must ensure that the photo codec type you request is valid for that file type. If no codec types are supported for a given fileType, an empty array is returned. If you've not yet added your receiver to an AVCaptureSession with a video source, no codec types are supported.
 */
- (NSArray<AVVideoCodecType> *)supportedPhotoCodecTypesForFileType:(AVFileType)fileType API_AVAILABLE(ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos);

/*!
 @method supportedRawPhotoPixelFormatTypesForFileType:
 @abstract
    An array of CVPixelBufferPixelFormatType values that are currently supported by the receiver for a particular file container.
 
 @param fileType
    The AVFileType container type intended for storage of a photo.
 @result
    An array of CVPixelBufferPixelFormatType values supported by the receiver for the file type in question.
 
 @discussion
    If you wish to capture a photo for storage in a particular file container, such as DNG, you must ensure that the RAW pixel format type you request is valid for that file type. If no RAW pixel format types are supported for a given fileType, an empty array is returned. If you've not yet added your receiver to an AVCaptureSession with a video source, no pixel format types are supported.
 */
- (NSArray<NSNumber *> *)supportedRawPhotoPixelFormatTypesForFileType:(AVFileType)fileType API_AVAILABLE(ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @enum AVCapturePhotoQualityPrioritization
 @abstract
    Constants indicating how photo quality should be prioritized against speed.

 @constant AVCapturePhotoQualityPrioritizationSpeed
    Indicates that speed of photo delivery is most important, even at the expense of quality.
 @constant AVCapturePhotoQualityPrioritizationBalanced
    Indicates that photo quality and speed of delivery are balanced in priority.
 @constant AVCapturePhotoQualityPrioritizationQuality
    Indicates that photo quality is paramount, even at the expense of shot-to-shot time.
 */
typedef NS_ENUM(NSInteger, AVCapturePhotoQualityPrioritization) {
    AVCapturePhotoQualityPrioritizationSpeed    = 1,
	AVCapturePhotoQualityPrioritizationBalanced = 2,
	AVCapturePhotoQualityPrioritizationQuality  = 3,
} API_AVAILABLE(ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @property maxPhotoQualityPrioritization
 @abstract
    Indicates the highest quality the receiver should be prepared to output on a capture-by-capture basis.

 @discussion
    Default value is AVCapturePhotoQualityPrioritizationBalanced when attached to an AVCaptureSession, and AVCapturePhotoQualityPrioritizationSpeed when attached to an AVCaptureMultiCamSession. The AVCapturePhotoOutput is capable of applying a variety of techniques to improve photo quality (reduce noise, preserve detail in low light, freeze motion, etc). Some techniques improve image quality at the expense of speed (shot-to-shot time). Before starting your session, you may set this property to indicate the highest quality prioritization you intend to request when calling -capturePhotoWithSettings:delegate:. When configuring an AVCapturePhotoSettings object, you may not exceed this quality prioritization level, but you may select a lower (speedier) prioritization level.
 
    Changing the maxPhotoQualityPrioritization while the session is running can result in a lengthy rebuild of the session in which video preview is disrupted.
 
    Setting the maxPhotoQualityPrioritization to .quality will turn on optical image stabilization if the -isHighPhotoQualitySupported of the source device's -activeFormat is true.
 */
@property(nonatomic) AVCapturePhotoQualityPrioritization maxPhotoQualityPrioritization API_AVAILABLE(ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @property stillImageStabilizationSupported
 @abstract
    Indicates whether the still image stabilization feature is supported by the receiver.

 @discussion
    This property may change as the session's -sessionPreset or source device's -activeFormat change. When still image stabilization is not supported, your capture requests always resolve stillImageStabilizationEnabled to NO. This property is key-value observable.
 
    As of iOS 13 hardware, the AVCapturePhotoOutput is capable of applying a variety of multi-image fusion techniques to improve photo quality (reduce noise, preserve detail in low light, freeze motion, etc), all of which have been previously lumped under the stillImageStabilization moniker. This property should no longer be used as it no longer provides meaningful information about the techniques used to improve quality in a photo capture. Instead, you should use -maxPhotoQualityPrioritization to indicate the highest quality prioritization level you might request in a photo capture, understanding that the higher the quality, the longer the potential wait. You may also use AVCapturePhotoSettings' photoQualityPrioritization property to specify a prioritization level for a particular photo capture, and then query the AVCaptureResolvedPhotoSettings photoProcessingTimeRange property to find out how long it might take to receive the resulting photo in your delegate callback.
 */
@property(nonatomic, readonly, getter=isStillImageStabilizationSupported) BOOL stillImageStabilizationSupported API_DEPRECATED_WITH_REPLACEMENT("maxPhotoQualityPrioritization", ios(10.0, 13.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos);

/*!
 @property isStillImageStabilizationScene
 @abstract
    Indicates whether the current scene is dark enough to warrant use of still image stabilization.

 @discussion
    This property reports whether the current scene being previewed by the camera is dark enough to benefit from still image stabilization. You can influence this property's answers by setting the photoSettingsForSceneMonitoring property, indicating whether autoStillImageStabilization monitoring should be on or off. If you set autoStillImageStabilization to NO, isStillImageStabilizationScene always reports NO. If you set it to YES, this property returns YES or NO depending on the current scene's lighting conditions. Note that some very dark scenes do not benefit from still image stabilization, but do benefit from flash. By default, this property always returns NO unless you set photoSettingsForSceneMonitoring to a non-nil value. This property may be key-value observed.
 
    As of iOS 13 hardware, the AVCapturePhotoOutput is capable of applying a variety of multi-image fusion techniques to improve photo quality (reduce noise, preserve detail in low light, freeze motion, etc), all of which have been previously lumped under the stillImageStabilization moniker. This property should no longer be used as it no longer provides meaningful information about the techniques used to improve quality in a photo capture. Instead, you should use -maxPhotoQualityPrioritization to indicate the highest quality prioritization level you might request in a photo capture, understanding that the higher the quality, the longer the potential wait. You may also use AVCapturePhotoSettings' photoQualityPrioritization property to specify a prioritization level for a particular photo capture, and then query the AVCaptureResolvedPhotoSettings photoProcessingTimeRange property to find out how long it might take to receive the resulting photo in your delegate callback.
 */
@property(nonatomic, readonly) BOOL isStillImageStabilizationScene API_DEPRECATED_WITH_REPLACEMENT("maxPhotoQualityPrioritization", ios(10.0, 13.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos);

/*!
 @property virtualDeviceFusionSupported
 @abstract
    Indicates whether the virtual device image fusion feature is supported by the receiver.

 @discussion
    This property may change as the session's -sessionPreset or source device's -activeFormat change. When using a virtual AVCaptureDevice, its constituent camera images can be fused together to improve image quality when this property answers YES. When virtual device fusion is not supported by the current configuration, your capture requests always resolve virtualDeviceFusionEnabled to NO. This property is key-value observable.
 */
@property(nonatomic, readonly, getter=isVirtualDeviceFusionSupported) BOOL virtualDeviceFusionSupported API_AVAILABLE(ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @property dualCameraFusionSupported
 @abstract
    Indicates whether the DualCamera image fusion feature is supported by the receiver.

 @discussion
    This property may change as the session's -sessionPreset or source device's -activeFormat change. When using the AVCaptureDevice with deviceType AVCaptureDeviceTypeBuiltInDualCamera, the wide-angle and telephoto camera images can be fused together to improve image quality in some configurations. When DualCamera image fusion is not supported by the current configuration, your capture requests always resolve dualCameraFusionEnabled to NO. This property is key-value observable. As of iOS 13, this property is deprecated in favor of virtualDeviceFusionSupported.
 */
@property(nonatomic, readonly, getter=isDualCameraFusionSupported) BOOL dualCameraFusionSupported API_DEPRECATED_WITH_REPLACEMENT("virtualDeviceFusionSupported", ios(10.2, 13.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos);

/*!
 @property virtualDeviceConstituentPhotoDeliverySupported
 @abstract
    Specifies whether the photo output's current configuration supports delivery of photos from constituent cameras of a virtual device.

 @discussion
    Virtual device constituent photo delivery is only supported for certain AVCaptureSession sessionPresets and AVCaptureDevice activeFormats. When switching cameras or formats this property may change. When this property changes from YES to NO, virtualDeviceConstituentPhotoDeliveryEnabled also reverts to NO. If you've previously opted in for virtual device constituent photo delivery and then change configurations, you may need to set virtualDeviceConstituentPhotoDeliveryEnabled = YES again. This property is key-value observable.
 */
@property(nonatomic, readonly, getter=isVirtualDeviceConstituentPhotoDeliverySupported) BOOL virtualDeviceConstituentPhotoDeliverySupported API_AVAILABLE(ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @property dualCameraDualPhotoDeliverySupported
 @abstract
    Specifies whether the photo output's current configuration supports delivery of both telephoto and wide images from the DualCamera.

 @discussion
    DualCamera dual photo delivery is only supported for certain AVCaptureSession sessionPresets and AVCaptureDevice activeFormats. When switching cameras or formats this property may change. When this property changes from YES to NO, dualCameraDualPhotoDeliveryEnabled also reverts to NO. If you've previously opted in for DualCamera dual photo delivery and then change configurations, you may need to set dualCameraDualPhotoDeliveryEnabled = YES again. This property is key-value observable. As of iOS 13, this property is deprecated in favor of virtualDeviceConstituentPhotoDeliverySupported.
 */
@property(nonatomic, readonly, getter=isDualCameraDualPhotoDeliverySupported) BOOL dualCameraDualPhotoDeliverySupported API_DEPRECATED_WITH_REPLACEMENT("virtualDeviceConstituentPhotoDeliverySupported", ios(11.0, 13.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos);

/*!
 @property virtualDeviceConstituentPhotoDeliveryEnabled
 @abstract
    Indicates whether the photo output is configured for delivery of photos from constituent cameras of a virtual device.

 @discussion
    Default value is NO. This property may only be set to YES if virtualDeviceConstituentPhotoDeliverySupported is YES. Virtual device constituent photo delivery requires a lengthy reconfiguration of the capture render pipeline, so if you intend to do any constituent photo delivery captures, you should set this property to YES before calling -[AVCaptureSession startRunning]. See also -[AVCapturePhotoSettings virtualDeviceConstituentPhotoDeliveryEnabledDevices].
 */
@property(nonatomic, getter=isVirtualDeviceConstituentPhotoDeliveryEnabled) BOOL virtualDeviceConstituentPhotoDeliveryEnabled API_AVAILABLE(ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @property dualCameraDualPhotoDeliveryEnabled
 @abstract
    Indicates whether the photo output is configured for delivery of both the telephoto and wide images from the DualCamera.

 @discussion
    Default value is NO. This property may only be set to YES if dualCameraDualPhotoDeliverySupported is YES. DualCamera dual photo delivery requires a lengthy reconfiguration of the capture render pipeline, so if you intend to do any dual photo delivery captures, you should set this property to YES before calling -[AVCaptureSession startRunning]. See also -[AVCapturePhotoSettings dualCameraDualPhotoDeliveryEnabled]. As of iOS 13, this property is deprecated in favor of virtualDeviceConstituentPhotoDeliveryEnabled.
 */
@property(nonatomic, getter=isDualCameraDualPhotoDeliveryEnabled) BOOL dualCameraDualPhotoDeliveryEnabled API_DEPRECATED_WITH_REPLACEMENT("virtualDeviceConstituentPhotoDeliveryEnabled", ios(11.0, 13.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos);

/*!
 @property cameraCalibrationDataDeliverySupported
 @abstract
    Specifies whether the photo output's current configuration supports delivery of AVCameraCalibrationData in the resultant AVCapturePhoto.

 @discussion
    Camera calibration data delivery (intrinsics, extrinsics, lens distortion characteristics, etc.) is only supported if virtualDeviceConstituentPhotoDeliveryEnabled is YES and contentAwareDistortionCorrectionEnabled is NO and the source device's geometricDistortionCorrectionEnabled property is set to NO. This property is key-value observable.
 */
@property(nonatomic, readonly, getter=isCameraCalibrationDataDeliverySupported) BOOL cameraCalibrationDataDeliverySupported API_AVAILABLE(ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property supportedFlashModes
 @abstract
    An array of AVCaptureFlashMode constants for the current capture session configuration.

 @discussion
    This property supersedes AVCaptureDevice's isFlashModeSupported: It returns an array of AVCaptureFlashMode constants. To test whether a particular flash mode is supported, use NSArray's containsObject API: [photoOutput.supportedFlashModes containsObject:@(AVCaptureFlashModeAuto)]. This property is key-value observable.
 */
@property(nonatomic, readonly) NSArray<NSNumber *> *supportedFlashModes API_UNAVAILABLE(macos);

/*!
 @property autoRedEyeReductionSupported
 @abstract
    Indicates whether the receiver supports automatic red-eye reduction for flash captures.

 @discussion
    Flash images may cause subjects' eyes to appear red, golden, or white. Automatic red-eye reduction detects and corrects for reflected light in eyes, at the cost of additional processing time per image. This property may change as the session's -sessionPreset or source device's -activeFormat change. When red-eye reduction is not supported, your capture requests always resolve redEyeReductionEnabled to NO. This property is key-value observable.
 */
@property(nonatomic, readonly, getter=isAutoRedEyeReductionSupported) BOOL autoRedEyeReductionSupported API_AVAILABLE(ios(12.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @property isFlashScene
 @abstract
    Indicates whether the current scene is dark enough to warrant use of the flash.

 @discussion
    This property reports whether the current scene being previewed by the camera is dark enough to need the flash. If -supportedFlashModes only contains AVCaptureFlashModeOff, isFlashScene always reports NO. You can influence this property's answers by setting the photoSettingsForSceneMonitoring property, indicating the flashMode you wish to monitor. If you set flashMode to AVCaptureFlashModeOff, isFlashScene always reports NO. If you set it to AVCaptureFlashModeAuto or AVCaptureFlashModeOn, isFlashScene answers YES or NO based on the current scene's lighting conditions. By default, this property always returns NO unless you set photoSettingsForSceneMonitoring to a non-nil value. Note that there is some overlap in the light level ranges that benefit from still image stabilization and flash. If your photoSettingsForSceneMonitoring indicate that both still image stabilization and flash scenes should be monitored, still image stabilization takes precedence, and isFlashScene becomes YES at lower overall light levels. This property may be key-value observed.
 */
@property(nonatomic, readonly) BOOL isFlashScene API_UNAVAILABLE(macos);

/*!
 @property photoSettingsForSceneMonitoring
 @abstract
    Settings that govern the behavior of isFlashScene and isStillImageStabilizationScene.

 @discussion
    You can influence the return values of isFlashScene and isStillImageStabilizationScene by setting this property, indicating the flashMode and photoQualityPrioritization values that should be considered for scene monitoring. For instance, if you set flashMode to AVCaptureFlashModeOff, isFlashScene always reports NO. If you set it to AVCaptureFlashModeAuto or AVCaptureFlashModeOn, isFlashScene answers YES or NO based on the current scene's lighting conditions. Note that there is some overlap in the light level ranges that benefit from still image stabilization and flash. If your photoSettingsForSceneMonitoring indicate that both still image stabilization and flash scenes should be monitored, still image stabilization takes precedence, and isFlashScene becomes YES at lower overall light levels. The default value for this property is nil. See isStillImageStabilizationScene and isFlashScene for further discussion.
 */
@property(nonatomic, copy, nullable) AVCapturePhotoSettings *photoSettingsForSceneMonitoring API_UNAVAILABLE(macos);

/*!
 @property highResolutionCaptureEnabled
 @abstract
    Indicates whether the photo render pipeline should be configured to deliver high resolution still images.

 @discussion
    Some AVCaptureDeviceFormats support outputting higher resolution stills than their streaming resolution (See AVCaptureDeviceFormat.highResolutionStillImageDimensions). Under some conditions, AVCaptureSession needs to set up the photo render pipeline differently to support high resolution still image capture. If you intend to take high resolution still images at all, you should set this property to YES before calling -[AVCaptureSession startRunning]. Once you've opted in for high resolution capture, you are free to issue photo capture requests with or without highResolutionCaptureEnabled in the AVCapturePhotoSettings. If you have not set this property to YES and call capturePhotoWithSettings:delegate: with settings.highResolutionCaptureEnabled set to YES, an NSInvalidArgumentException will be thrown.
 */
@property(nonatomic, getter=isHighResolutionCaptureEnabled) BOOL highResolutionCaptureEnabled API_UNAVAILABLE(macos);

/*!
 @property maxBracketedCapturePhotoCount
 @abstract
    Specifies the maximum number of photos that may be taken in a single bracket.

 @discussion
     AVCapturePhotoOutput can only satisfy a limited number of image requests in a single bracket without exhausting system resources. The maximum number of photos that may be taken in a single bracket depends on the size and format of the images being captured, and consequently may vary with AVCaptureSession -sessionPreset and AVCaptureDevice -activeFormat. Some formats do not support bracketed capture at all, and thus this property may return a value of 0. This read-only property is key-value observable. If you call -capturePhotoWithSettings:delegate: with a bracketedSettings whose count exceeds -maxBracketedCapturePhotoCount, an NSInvalidArgumentException is thrown.
 */
@property(nonatomic, readonly) NSUInteger maxBracketedCapturePhotoCount API_UNAVAILABLE(macos);

/*!
 @property lensStabilizationDuringBracketedCaptureSupported
 @abstract
    Indicates whether the receiver supports lens stabilization during bracketed captures.

 @discussion
    The AVCapturePhotoBracketSettings lensStabilizationEnabled property may only be set if this property returns YES. Its value may change as the session's -sessionPreset or input device's -activeFormat changes. This read-only property is key-value observable.
 */
@property(nonatomic, readonly, getter=isLensStabilizationDuringBracketedCaptureSupported) BOOL lensStabilizationDuringBracketedCaptureSupported API_UNAVAILABLE(macos);

/*!
 @property livePhotoCaptureSupported
 @abstract
    Indicates whether the receiver supports Live Photo capture.

 @discussion
    Live Photo capture is only supported for certain AVCaptureSession sessionPresets and AVCaptureDevice activeFormats. When switching cameras or formats this property may change. When this property changes from YES to NO, livePhotoCaptureEnabled also reverts to NO. If you've previously opted in for Live Photo capture and then change configurations, you may need to set livePhotoCaptureEnabled = YES again. 
 */
@property(nonatomic, readonly, getter=isLivePhotoCaptureSupported) BOOL livePhotoCaptureSupported API_UNAVAILABLE(macos);

/*!
 @property livePhotoCaptureEnabled
 @abstract
    Indicates whether the receiver is configured for Live Photo capture.

 @discussion
    Default value is NO. This property may only be set to YES if livePhotoCaptureSupported is YES. Live Photo capture requires a lengthy reconfiguration of the capture render pipeline, so if you intend to do any Live Photo captures at all, you should set livePhotoCaptureEnabled to YES before calling -[AVCaptureSession startRunning].
 */
@property(nonatomic, getter=isLivePhotoCaptureEnabled) BOOL livePhotoCaptureEnabled API_UNAVAILABLE(macos);

/*!
 @property livePhotoCaptureSuspended
 @abstract
    Indicates whether Live Photo capture is enabled, but currently suspended.

 @discussion
    This property allows you to cut current Live Photo movie captures short (for instance, if you suddenly need to do something that you don't want to show up in the Live Photo movie, such as take a non Live Photo capture that makes a shutter sound). By default, livePhotoCaptureSuspended is NO. When you set livePhotoCaptureSuspended = YES, any Live Photo movie captures in progress are trimmed to the current time. Likewise, when you toggle livePhotoCaptureSuspended from YES to NO, subsequent Live Photo movie captures will not contain any samples earlier than the time you un-suspended Live Photo capture. Setting this property to YES throws an NSInvalidArgumentException if livePhotoCaptureEnabled is NO. This property may only be set while the session is running. Setting this property to YES when the session is not running will fail resulting in livePhotoCaptureSuspended being reverted to NO.
 */
@property(nonatomic, getter=isLivePhotoCaptureSuspended) BOOL livePhotoCaptureSuspended API_UNAVAILABLE(macos);

/*!
 @property livePhotoAutoTrimmingEnabled
 @abstract
    Indicates whether Live Photo movies are trimmed in real time to avoid excessive movement.

 @discussion
    This property defaults to YES when livePhotoCaptureSupported is YES. Changing this property's value while your session is running will cause a lengthy reconfiguration of the session. You should set livePhotoAutoTrimmingEnabled to YES or NO before calling -[AVCaptureSession startRunning]. When set to YES, Live Photo movies are analyzed in real time and trimmed if there's excessive movement before or after the photo is taken. Nominally, Live Photos are approximately 3 seconds long. With trimming enabled, they may be shorter, depending on movement. This feature prevents common problems such as Live Photo movies containing shoe or pocket shots.
 */
@property(nonatomic, getter=isLivePhotoAutoTrimmingEnabled) BOOL livePhotoAutoTrimmingEnabled API_UNAVAILABLE(macos);

/*!
 @property availableLivePhotoVideoCodecTypes
 @abstract
    An array of AVVideoCodecKey values that are currently supported by the receiver for use in the movie complement of a Live Photo.

 @discussion
    Prior to iOS 11, all Live Photo movie video tracks are compressed using H.264. Beginning in iOS 11, you can select the Live Photo movie video compression format using one of the AVVideoCodecKey strings presented in this property. The system's default (preferred) video codec is always presented first in the list. If you've not yet added your receiver to an AVCaptureSession with a video source, no codecs are available. This property is key-value observable.
 */
@property(nonatomic, readonly) NSArray<AVVideoCodecType> *availableLivePhotoVideoCodecTypes API_AVAILABLE(ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @method JPEGPhotoDataRepresentationForJPEGSampleBuffer:previewPhotoSampleBuffer:
 @abstract
    A class method that writes a JPEG sample buffer to an NSData in the JPEG file format.
 
 @param JPEGSampleBuffer
    A CMSampleBuffer containing JPEG compressed data.
 @param previewPhotoSampleBuffer
    An optional CMSampleBuffer containing pixel buffer image data to be written as a thumbnail image.
 @result
    An NSData containing bits in the JPEG file format. May return nil if the re-packaging process fails.

 @discussion
    AVCapturePhotoOutput's depecrated -captureOutput:didFinishProcessingPhotoSampleBuffer:previewPhotoSampleBuffer:resolvedSettings:bracketSettings:error: callback delivers JPEG photos to clients as CMSampleBuffers. To re-package these buffers in a data format suitable for writing to a JPEG file, you may call this class method, optionally inserting your own metadata into the JPEG CMSampleBuffer first, and optionally passing a preview image to be written to the JPEG file format as a thumbnail image.
 */
+ (nullable NSData *)JPEGPhotoDataRepresentationForJPEGSampleBuffer:(CMSampleBufferRef)JPEGSampleBuffer previewPhotoSampleBuffer:(nullable CMSampleBufferRef)previewPhotoSampleBuffer API_DEPRECATED_WITH_REPLACEMENT("-[AVCapturePhoto fileDataRepresentation]", ios(10.0, 11.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos);

/*!
 @method DNGPhotoDataRepresentationForRawSampleBuffer:previewPhotoSampleBuffer:
 @abstract
    A class method that writes a RAW sample buffer to an NSData containing bits in the DNG file format.
 
 @param rawSampleBuffer
    A CMSampleBuffer containing Bayer RAW data.
 @param previewPhotoSampleBuffer
    An optional CMSampleBuffer containing pixel buffer image data to be written as a thumbnail image.
 @result
    An NSData containing bits in the DNG file format. May return nil if the re-packaging process fails.

 @discussion
    AVCapturePhotoOutput's deprecated -captureOutput:didFinishProcessingRawPhotoSampleBuffer:previewPhotoSampleBuffer:resolvedSettings:bracketSettings:error: callback delivers RAW photos to clients as CMSampleBuffers. To re-package these buffers in a data format suitable for writing to a DNG file, you may call this class method, optionally inserting your own metadata into the RAW CMSampleBuffer first, and optionally passing a preview image to be written to the DNG file format as a thumbnail image. Only RAW images from Apple built-in cameras are supported.
 */
+ (nullable NSData *)DNGPhotoDataRepresentationForRawSampleBuffer:(CMSampleBufferRef)rawSampleBuffer previewPhotoSampleBuffer:(nullable CMSampleBufferRef)previewPhotoSampleBuffer API_DEPRECATED_WITH_REPLACEMENT("-[AVCapturePhoto fileDataRepresentation]", ios(10.0, 11.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos);

/*!
 @property contentAwareDistortionCorrectionSupported
 @abstract
    A BOOL value specifying whether content aware distortion correction is supported.

 @discussion
    The rectilinear model used in optical design and by geometric distortion correction only preserves lines but not area, angles, or distance. Thus the wider the field of view of a lens, the greater the areal distortion at the edges of images. Content aware distortion correction, when enabled, intelligently corrects distortions by taking content into consideration, such as faces near the edges of the image. This property returns YES if the session's current configuration allows photos to be captured with content aware distortion correction. When switching cameras or formats or enabling depth data delivery this property may change. When this property changes from YES to NO, contentAwareDistortionCorrectionEnabled also reverts to NO. This property is key-value observable.
 */
@property(nonatomic, readonly, getter=isContentAwareDistortionCorrectionSupported) BOOL contentAwareDistortionCorrectionSupported API_AVAILABLE(ios(14.1), macCatalyst(14.1)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @property contentAwareDistortionCorrectionEnabled
 @abstract
    A BOOL value specifying whether the photo render pipeline is set up to perform content aware distortion correction.

 @discussion
    Default is NO. Set to YES if you wish content aware distortion correction to be performed on your AVCapturePhotos. This property may only be set to YES if contentAwareDistortionCorrectionSupported is YES. Note that warping the photos to preserve more natural looking content may result in a small change in field of view compared to what you see in the AVCaptureVideoPreviewLayer. The amount of field of view lost or gained is content specific and may vary from photo to photo. Enabling this property requires a lengthy reconfiguration of the capture render pipeline, so you should set this property to YES before calling -[AVCaptureSession startRunning].
 */
@property(nonatomic, getter=isContentAwareDistortionCorrectionEnabled) BOOL contentAwareDistortionCorrectionEnabled API_AVAILABLE(ios(14.1), macCatalyst(14.1)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);
@end


@class AVCapturePhoto;

API_AVAILABLE(macos(10.15), ios(10.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface AVCapturePhotoOutput (AVCapturePhotoOutputDepthDataDeliverySupport)

/*!
 @property depthDataDeliverySupported
 @abstract
    A BOOL value specifying whether depth data delivery is supported.

 @discussion
    Some cameras and configurations support the delivery of depth data (e.g. disparity maps) along with the photo. This property returns YES if the session's current configuration allows photos to be captured with depth data, from which depth-related filters may be applied. When switching cameras or formats this property may change. When this property changes from YES to NO, depthDataDeliveryEnabled also reverts to NO. If you've previously opted in for depth data delivery and then change configurations, you may need to set depthDataDeliveryEnabled = YES again. This property is key-value observable.
 */
@property(nonatomic, readonly, getter=isDepthDataDeliverySupported) BOOL depthDataDeliverySupported API_AVAILABLE(ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property depthDataDeliveryEnabled
 @abstract
    A BOOL specifying whether the photo render pipeline is prepared for depth data delivery.

 @discussion
    Default is NO. Set to YES if you wish depth data to be delivered with your AVCapturePhotos. This property may only be set to YES if depthDataDeliverySupported is YES. Enabling depth data delivery requires a lengthy reconfiguration of the capture render pipeline, so if you intend to capture depth data, you should set this property to YES before calling -[AVCaptureSession startRunning].
 */
@property(nonatomic, getter=isDepthDataDeliveryEnabled) BOOL depthDataDeliveryEnabled API_AVAILABLE(ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property portraitEffectsMatteDeliverySupported
 @abstract
    A BOOL value specifying whether portrait effects matte delivery is supported.

 @discussion
    Some cameras and configurations support the delivery of a matting image to augment depth data and aid in high quality portrait effect rendering (see AVPortraitEffectsMatte.h). This property returns YES if the session's current configuration allows photos to be captured with a portrait effects matte. When switching cameras or formats this property may change. When this property changes from YES to NO, portraitEffectsMatteDeliveryEnabled also reverts to NO. If you've previously opted in for portrait effects matte delivery and then change configurations, you may need to set portraitEffectsMatteDeliveryEnabled = YES again. This property is key-value observable.
 */
@property(nonatomic, readonly, getter=isPortraitEffectsMatteDeliverySupported) BOOL portraitEffectsMatteDeliverySupported API_AVAILABLE(ios(12.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @property portraitEffectsMatteDeliveryEnabled
 @abstract
    A BOOL specifying whether the photo render pipeline is prepared for portrait effects matte delivery.

 @discussion
    Default is NO. Set to YES if you wish portrait effects mattes to be delivered with your AVCapturePhotos. This property may only be set to YES if portraitEffectsMatteDeliverySupported is YES. Portrait effects matte generation requires depth to be present, so when enabling portrait effects matte delivery, you must also set depthDataDeliveryEnabled to YES. Enabling portrait effects matte delivery requires a lengthy reconfiguration of the capture render pipeline, so if you intend to capture portrait effects mattes, you should set this property to YES before calling -[AVCaptureSession startRunning].
 */
@property(nonatomic, getter=isPortraitEffectsMatteDeliveryEnabled) BOOL portraitEffectsMatteDeliveryEnabled API_AVAILABLE(ios(12.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @property availableSemanticSegmentationMatteTypes
 @abstract
    An array of supported semantic segmentation matte types that may be captured and delivered along with your AVCapturePhotos.

 @discussion
    Some cameras and configurations support the delivery of semantic segmentation matting images (e.g. segmentations of the hair, skin, or teeth in the photo). This property returns an array of AVSemanticSegmentationMatteTypes available given the session's current configuration. When switching cameras or formats this property may change. When this property changes, enabledSemanticSegmentationMatteTypes reverts to an empty array. If you've previously opted in for delivery of one or more semantic segmentation mattes and then change configurations, you need to set up your enabledSemanticSegmentationMatteTypes again. This property is key-value observable.
 */
@property(nonatomic, readonly) NSArray<AVSemanticSegmentationMatteType> *availableSemanticSegmentationMatteTypes API_AVAILABLE(ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @property enabledSemanticSegmentationMatteTypes
 @abstract
    An array of semantic segmentation matte types which the photo render pipeline is prepared to deliver.

 @discussion
    Default is empty array. You may set this to the array of matte types you'd like to be delivered with your AVCapturePhotos. The array may only contain values present in availableSemanticSegmentationMatteTypes. Enabling semantic segmentation matte delivery requires a lengthy reconfiguration of the capture render pipeline, so if you intend to capture semantic segmentation mattes, you should set this property to YES before calling -[AVCaptureSession startRunning].
 */
@property(nonatomic) NSArray<AVSemanticSegmentationMatteType> *enabledSemanticSegmentationMatteTypes API_AVAILABLE(ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

@end


/*!
 @protocol AVCapturePhotoCaptureDelegate
 @abstract
    A set of delegate callbacks to be implemented by a client who calls AVCapturePhotoOutput's -capturePhotoWithSettings:delegate.
 
 @discussion
    AVCapturePhotoOutput invokes the AVCapturePhotoCaptureDelegate callbacks on a common dispatch queue — not necessarily the main queue. While the -captureOutput:willBeginCaptureForResolvedSettings: callback always comes first and the -captureOutput:didFinishCaptureForResolvedSettings: callback always comes last, none of the other callbacks can be assumed to come in any particular order. The AVCaptureResolvedPhotoSettings instance passed to the client with each callback has the same uniqueID as the AVCapturePhotoSettings instance passed in -capturePhotoWithSettings:delegate:. All callbacks are marked optional, but depending on the features you've specified in your AVCapturePhotoSettings, some callbacks become mandatory and are validated in -capturePhotoWithSettings:delegate:. If your delegate does not implement the mandatory callbacks, an NSInvalidArgumentException is thrown.

    - If you initialize your photo settings with a format dictionary, or use one of the default constructors (that is, if you're not requesting a RAW-only capture), your delegate must respond to either - captureOutput:didFinishProcessingPhoto:error: or the deprecated -captureOutput:didFinishProcessingPhotoSampleBuffer:previewPhotoSampleBuffer:resolvedSettings:bracketSettings:error:. If your delegate responds to both of these callbacks, only the undeprecated variant will be called.
    - If you initialize your photo settings with a rawPhotoPixelFormatType, your delegate must respond to either -captureOutput:didFinishProcessingPhoto:error: or the deprecated -captureOutput:didFinishProcessingRawPhotoSampleBuffer:previewPhotoSampleBuffer:resolvedSettings:bracketSettings:error:. If your delegate responds to both of these callbacks, only the undeprecated variant will be called.
    - If you set livePhotoMovieFileURL to non-nil, your delegate must respond to -captureOutput:didFinishProcessingLivePhotoToMovieFileAtURL:duration:photoDisplayTime:resolvedSettings:error:.
 
    In the event of an error, all expected callbacks are fired with an appropriate error.
 */
API_AVAILABLE(macos(10.15), ios(10.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@protocol AVCapturePhotoCaptureDelegate <NSObject>

@optional
/*!
 @method captureOutput:willBeginCaptureForResolvedSettings:
 @abstract
    A callback fired as soon as the capture settings have been resolved.
 
 @param output
    The calling instance of AVCapturePhotoOutput.
 @param resolvedSettings
    An instance of AVCaptureResolvedPhotoSettings indicating which capture features have been selected.

 @discussion
    This callback is always delivered first for a particular capture request. It is delivered as soon as possible after you call -capturePhotoWithSettings:delegate:, so you can know what to expect in the remainder of your callbacks.
 */
- (void)captureOutput:(AVCapturePhotoOutput *)output willBeginCaptureForResolvedSettings:(AVCaptureResolvedPhotoSettings *)resolvedSettings;

/*!
 @method captureOutput:willCapturePhotoForResolvedSettings:
 @abstract
    A callback fired just as the photo is being taken.
 
 @param output
    The calling instance of AVCapturePhotoOutput.
 @param resolvedSettings
    An instance of AVCaptureResolvedPhotoSettings indicating which capture features have been selected.
 
 @discussion
    The timing of this callback is analogous to AVCaptureStillImageOutput's capturingStillImage property changing from NO to YES. The callback is delivered right after the shutter sound is heard (note that shutter sounds are suppressed when Live Photos are being captured).
 */
- (void)captureOutput:(AVCapturePhotoOutput *)output willCapturePhotoForResolvedSettings:(AVCaptureResolvedPhotoSettings *)resolvedSettings;

/*!
 @method captureOutput:didCapturePhotoForResolvedSettings:
 @abstract
    A callback fired just after the photo is taken.
 
 @param output
    The calling instance of AVCapturePhotoOutput.
 @param resolvedSettings
    An instance of AVCaptureResolvedPhotoSettings indicating which capture features have been selected.
 
 @discussion
    The timing of this callback is analogous to AVCaptureStillImageOutput's capturingStillImage property changing from YES to NO.
 */
- (void)captureOutput:(AVCapturePhotoOutput *)output didCapturePhotoForResolvedSettings:(AVCaptureResolvedPhotoSettings *)resolvedSettings;

/*!
 @method captureOutput:didFinishProcessingPhoto:error:
 @abstract
    A callback fired when photos are ready to be delivered to you (RAW or processed).
 
 @param output
    The calling instance of AVCapturePhotoOutput.
 @param photo
    An instance of AVCapturePhoto.
 @param error
    An error indicating what went wrong. If the photo was processed successfully, nil is returned.
 
 @discussion
    This callback fires resolvedSettings.expectedPhotoCount number of times for a given capture request. Note that the photo parameter is always non nil, even if an error is returned. The delivered AVCapturePhoto's rawPhoto property can be queried to know if it's a RAW image or processed image.
 */
- (void)captureOutput:(AVCapturePhotoOutput *)output didFinishProcessingPhoto:(AVCapturePhoto *)photo error:(nullable NSError *)error API_AVAILABLE(ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos);

/*!
 @method captureOutput:didFinishProcessingPhotoSampleBuffer:previewPhotoSampleBuffer:resolvedSettings:bracketSettings:error:
 @abstract
    A callback fired when the primary processed photo or photos are done.
 
 @param output
    The calling instance of AVCapturePhotoOutput.
 @param photoSampleBuffer
    A CMSampleBuffer containing an uncompressed pixel buffer or compressed data, along with timing information and metadata. May be nil if there was an error.
 @param previewPhotoSampleBuffer
    An optional CMSampleBuffer containing an uncompressed, down-scaled preview pixel buffer. Note that the preview sample buffer contains no metadata. Refer to the photoSampleBuffer for metadata (e.g., the orientation). May be nil.
 @param resolvedSettings
    An instance of AVCaptureResolvedPhotoSettings indicating which capture features have been selected.
 @param bracketSettings
    If this image is being delivered as part of a bracketed capture, the bracketSettings corresponding to this image. Otherwise nil.
 @param error
    An error indicating what went wrong if photoSampleBuffer is nil.
 
 @discussion
    If you've requested a single processed image (uncompressed or compressed) capture, the photo is delivered here. If you've requested a bracketed capture, this callback is fired bracketedSettings.count times (once for each photo in the bracket).
 */
- (void)captureOutput:(AVCapturePhotoOutput *)output didFinishProcessingPhotoSampleBuffer:(nullable CMSampleBufferRef)photoSampleBuffer previewPhotoSampleBuffer:(nullable CMSampleBufferRef)previewPhotoSampleBuffer resolvedSettings:(AVCaptureResolvedPhotoSettings *)resolvedSettings bracketSettings:(nullable AVCaptureBracketedStillImageSettings *)bracketSettings error:(nullable NSError *)error API_DEPRECATED_WITH_REPLACEMENT("-captureOutput:didFinishProcessingPhoto:error:", ios(10.0, 11.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos);

/*!
 @method captureOutput:didFinishProcessingRawPhotoSampleBuffer:previewPhotoSampleBuffer:resolvedSettings:bracketSettings:error:
 @abstract
    A callback fired when the RAW photo or photos are done.
 
 @param output
    The calling instance of AVCapturePhotoOutput.
 @param rawSampleBuffer
    A CMSampleBuffer containing Bayer RAW pixel data, along with timing information and metadata. May be nil if there was an error.
 @param previewPhotoSampleBuffer
    An optional CMSampleBuffer containing an uncompressed, down-scaled preview pixel buffer. Note that the preview sample buffer contains no metadata. Refer to the rawSampleBuffer for metadata (e.g., the orientation). May be nil.
 @param resolvedSettings
    An instance of AVCaptureResolvedPhotoSettings indicating which capture features have been selected.
 @param bracketSettings
    If this image is being delivered as part of a bracketed capture, the bracketSettings corresponding to this image. Otherwise nil.
 @param error
    An error indicating what went wrong if rawSampleBuffer is nil.
 
 @discussion
    Single RAW image and bracketed RAW photos are delivered here. If you've requested a RAW bracketed capture, this callback is fired bracketedSettings.count times (once for each photo in the bracket).
 */
- (void)captureOutput:(AVCapturePhotoOutput *)output didFinishProcessingRawPhotoSampleBuffer:(nullable CMSampleBufferRef)rawSampleBuffer previewPhotoSampleBuffer:(nullable CMSampleBufferRef)previewPhotoSampleBuffer resolvedSettings:(AVCaptureResolvedPhotoSettings *)resolvedSettings bracketSettings:(nullable AVCaptureBracketedStillImageSettings *)bracketSettings error:(nullable NSError *)error API_DEPRECATED_WITH_REPLACEMENT("-captureOutput:didFinishProcessingPhoto:error:", ios(10.0, 11.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos);

/*!
 @method captureOutput:didFinishRecordingLivePhotoMovieForEventualFileAtURL:resolvedSettings:
 @abstract
    A callback fired when the Live Photo movie has captured all its media data, though all media has not yet been written to file.
 
 @param output
    The calling instance of AVCapturePhotoOutput.
 @param outputFileURL
    The URL to which the movie file will be written. This URL is equal to your AVCapturePhotoSettings.livePhotoMovieURL.
 @param resolvedSettings
    An instance of AVCaptureResolvedPhotoSettings indicating which capture features have been selected.
 
 @discussion
    When this callback fires, no new media is being written to the file. If you are displaying a "Live" badge, this is an appropriate time to dismiss it. The movie file itself is not done being written until the -captureOutput:didFinishProcessingLivePhotoToMovieFileAtURL:duration:photoDisplayTime:resolvedSettings:error: callback fires.
 */
- (void)captureOutput:(AVCapturePhotoOutput *)output didFinishRecordingLivePhotoMovieForEventualFileAtURL:(NSURL *)outputFileURL resolvedSettings:(AVCaptureResolvedPhotoSettings *)resolvedSettings API_UNAVAILABLE(macos);

/*!
 @method captureOutput:didFinishProcessingLivePhotoToMovieFileAtURL:duration:photoDisplayTime:resolvedSettings:error:
 @abstract
    A callback fired when the Live Photo movie is finished being written to disk.
 
 @param output
    The calling instance of AVCapturePhotoOutput.
 @param outputFileURL
    The URL where the movie file resides. This URL is equal to your AVCapturePhotoSettings.livePhotoMovieURL.
 @param duration
    A CMTime indicating the duration of the movie file.
 @param photoDisplayTime
    A CMTime indicating the time in the movie at which the still photo should be displayed.
 @param resolvedSettings
    An instance of AVCaptureResolvedPhotoSettings indicating which capture features have been selected.
 @param error
    An error indicating what went wrong if the outputFileURL is damaged.
 
 @discussion
    When this callback fires, the movie on disk is fully finished and ready for consumption.
 */
- (void)captureOutput:(AVCapturePhotoOutput *)output didFinishProcessingLivePhotoToMovieFileAtURL:(NSURL *)outputFileURL duration:(CMTime)duration photoDisplayTime:(CMTime)photoDisplayTime resolvedSettings:(AVCaptureResolvedPhotoSettings *)resolvedSettings error:(nullable NSError *)error API_UNAVAILABLE(macos);

/*!
 @method captureOutput:didFinishCaptureForResolvedSettings:error:
 @abstract
    A callback fired when the photo capture is completed and no more callbacks will be fired.
 
 @param output
    The calling instance of AVCapturePhotoOutput.
 @param resolvedSettings
    An instance of AVCaptureResolvedPhotoSettings indicating which capture features were selected.
 @param error
    An error indicating whether the capture was unsuccessful. Nil if there were no problems.
 
 @discussion
    This callback always fires last and when it does, you may clean up any state relating to this photo capture.
 */
- (void)captureOutput:(AVCapturePhotoOutput *)output didFinishCaptureForResolvedSettings:(AVCaptureResolvedPhotoSettings *)resolvedSettings error:(nullable NSError *)error;

@end


#pragma mark - AVCapturePhotoSettings

@class AVCapturePhotoSettingsInternal;

/*!
 @class AVCapturePhotoSettings
 @abstract
    A mutable settings object encapsulating all the desired properties of a photo capture.
 
 @discussion
    To take a picture, a client instantiates and configures an AVCapturePhotoSettings object, then calls AVCapturePhotoOutput's -capturePhotoWithSettings:delegate:, passing the settings and a delegate to be informed when events relating to the photo capture occur. Since AVCapturePhotoSettings has no reference to the AVCapturePhotoOutput instance with which it will be used, minimal validation occurs while you configure an AVCapturePhotoSettings instance. The bulk of the validation is executed when you call AVCapturePhotoOutput's -capturePhotoWithSettings:delegate:.
 */
API_AVAILABLE(macos(10.15), ios(10.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface AVCapturePhotoSettings : NSObject <NSCopying>
{
@private
    AVCapturePhotoSettingsInternal *_internal;
}

/*!
 @method photoSettings
 @abstract
    Creates a default instance of AVCapturePhotoSettings.
 
 @result
    An instance of AVCapturePhotoSettings.
 
 @discussion
    A default AVCapturePhotoSettings object has a format of AVVideoCodecTypeJPEG, a fileType of AVFileTypeJPEG, and photoQualityPrioritization set to AVCapturePhotoQualityPrioritizationBalanced.
 */
+ (instancetype)photoSettings;

/*!
 @method photoSettingsWithFormat:
 @abstract
    Creates an instance of AVCapturePhotoSettings with a user-specified output format.
 
 @param format
    A dictionary of Core Video pixel buffer attributes or AVVideoSettings, analogous to AVCaptureStillImageOutput's outputSettings property.
 @result
    An instance of AVCapturePhotoSettings.
 
 @discussion
    If you wish an uncompressed format, your dictionary must contain kCVPixelBufferPixelFormatTypeKey, and the format specified must be present in AVCapturePhotoOutput's -availablePhotoPixelFormatTypes array. kCVPixelBufferPixelFormatTypeKey is the only supported key when expressing uncompressed output. If you wish a compressed format, your dictionary must contain AVVideoCodecKey and the codec specified must be present in AVCapturePhotoOutput's -availablePhotoCodecTypes array. If you are specifying a compressed format, the AVVideoCompressionPropertiesKey is also supported, with a payload dictionary containing a single AVVideoQualityKey. Passing a nil format dictionary is analogous to calling +photoSettings.
 */
+ (instancetype)photoSettingsWithFormat:(nullable NSDictionary<NSString *, id> *)format;

/*!
 @method photoSettingsWithRawPixelFormatType:
 @abstract
    Creates an instance of AVCapturePhotoSettings specifying RAW only output.
 
 @param rawPixelFormatType
    A Bayer RAW or Apple ProRAW pixel format OSType (defined in CVPixelBuffer.h).
 @result
    An instance of AVCapturePhotoSettings.

 @discussion
    rawPixelFormatType must be one of the OSTypes contained in AVCapturePhotoOutput's -availableRawPhotoPixelFormatTypes array. See AVCapturePhotoOutput's -capturePhotoWithSettings:delegate: inline documentation for a discussion of restrictions on AVCapturePhotoSettings when requesting RAW capture.
 */
+ (instancetype)photoSettingsWithRawPixelFormatType:(OSType)rawPixelFormatType API_UNAVAILABLE(macos);

/*!
 @method photoSettingsWithRawPixelFormatType:processedFormat:
 @abstract
    Creates an instance of AVCapturePhotoSettings specifying RAW + a processed format (such as JPEG).
 
 @param rawPixelFormatType
    A Bayer RAW or Apple ProRAW pixel format OSType (defined in CVPixelBuffer.h).
 @param processedFormat
    A dictionary of Core Video pixel buffer attributes or AVVideoSettings, analogous to AVCaptureStillImageOutput's outputSettings property.
 @result
    An instance of AVCapturePhotoSettings.
 
 @discussion
    rawPixelFormatType must be one of the OSTypes contained in AVCapturePhotoOutput's -availableRawPhotoPixelFormatTypes array. If you wish an uncompressed processedFormat, your dictionary must contain kCVPixelBufferPixelFormatTypeKey, and the processedFormat specified must be present in AVCapturePhotoOutput's -availablePhotoPixelFormatTypes array. kCVPixelBufferPixelFormatTypeKey is the only supported key when expressing uncompressed processedFormat. If you wish a compressed format, your dictionary must contain AVVideoCodecKey and the codec specified must be present in AVCapturePhotoOutput's -availablePhotoCodecTypes array. If you are specifying a compressed format, the AVVideoCompressionPropertiesKey is also supported, with a payload dictionary containing a single AVVideoQualityKey. Passing a nil processedFormat dictionary is analogous to calling +photoSettingsWithRawPixelFormatType:. See AVCapturePhotoOutput's -capturePhotoWithSettings:delegate: inline documentation for a discussion of restrictions on AVCapturePhotoSettings when requesting RAW capture.
 */
+ (instancetype)photoSettingsWithRawPixelFormatType:(OSType)rawPixelFormatType processedFormat:(nullable NSDictionary<NSString *, id> *)processedFormat API_UNAVAILABLE(macos);

/*!
 @method photoSettingsWithRawPixelFormatType:processedFormat:fileType:
 @abstract
    Creates an instance of AVCapturePhotoSettings specifying RAW + a processed format (such as JPEG) and a file container to which it will be written.
 
 @param rawPixelFormatType
    A Bayer RAW or Apple ProRAW pixel format OSType (defined in CVPixelBuffer.h). Pass 0 if you do not desire a RAW photo callback.
 @param rawFileType
    The file container for which the RAW image should be formatted to be written. Pass nil if you have no preferred file container. A default container will be chosen for you.
 @param processedFormat
    A dictionary of Core Video pixel buffer attributes or AVVideoSettings, analogous to AVCaptureStillImageOutput's outputSettings property. Pass nil if you do not desire a processed photo callback.
 @param processedFileType
    The file container for which the processed image should be formatted to be written. Pass nil if you have no preferred file container. A default container will be chosen for you.
 @result
    An instance of AVCapturePhotoSettings.
 
 @discussion
    rawPixelFormatType must be one of the OSTypes contained in AVCapturePhotoOutput's -availableRawPhotoPixelFormatTypes array. Set rawPixelFormatType to 0 if you do not desire a RAW photo callback. If you are specifying a rawFileType, it must be present in AVCapturePhotoOutput's -availableRawPhotoFileTypes array. If you wish an uncompressed processedFormat, your dictionary must contain kCVPixelBufferPixelFormatTypeKey, and the processedFormat specified must be present in AVCapturePhotoOutput's -availablePhotoPixelFormatTypes array. kCVPixelBufferPixelFormatTypeKey is the only supported key when expressing uncompressed processedFormat. If you wish a compressed format, your dictionary must contain AVVideoCodecKey and the codec specified must be present in AVCapturePhotoOutput's -availablePhotoCodecTypes array. If you are specifying a compressed format, the AVVideoCompressionPropertiesKey is also supported, with a payload dictionary containing a single AVVideoQualityKey. If you are specifying a processedFileType, it must be present in AVCapturePhotoOutput's -availablePhotoFileTypes array. Pass a nil processedFormat dictionary if you only desire a RAW photo capture. See AVCapturePhotoOutput's -capturePhotoWithSettings:delegate: inline documentation for a discussion of restrictions on AVCapturePhotoSettings when requesting RAW capture.
 */
+ (instancetype)photoSettingsWithRawPixelFormatType:(OSType)rawPixelFormatType rawFileType:(nullable AVFileType)rawFileType processedFormat:(nullable NSDictionary<NSString *, id> *)processedFormat processedFileType:(nullable AVFileType)processedFileType API_AVAILABLE(ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @method photoSettingsFromPhotoSettings:
 @abstract
    Creates an instance of AVCapturePhotoSettings with a new uniqueID from an existing instance of AVCapturePhotoSettings.
 
 @param photoSettings
     An existing AVCapturePhotoSettings instance.
 @result
    An new instance of AVCapturePhotoSettings with new uniqueID.
 
 @discussion
    Use this factory method to create a clone of an existing photo settings instance, but with a new uniqueID that can safely be passed to AVCapturePhotoOutput -capturePhotoWithSettings:delegate:.
 */
+ (instancetype)photoSettingsFromPhotoSettings:(AVCapturePhotoSettings *)photoSettings;

/*!
 @property uniqueID
 @abstract
    A 64-bit number that uniquely identifies this instance.

 @discussion
    When you create an instance of AVCapturePhotoSettings, a uniqueID is generated automatically. This uniqueID is guaranteed to be unique for the life time of your process.
 */
@property(readonly) int64_t uniqueID;

/*!
 @property format
 @abstract
    A dictionary of Core Video pixel buffer attributes or AVVideoSettings, analogous to AVCaptureStillImageOutput's outputSettings property.

 @discussion
    The format dictionary you passed to one of the creation methods. May be nil if you've specified RAW-only capture.
 */
@property(readonly, copy, nullable) NSDictionary<NSString *, id> *format;

/*!
 @property processedFileType
 @abstract
    The file container for which the processed photo is formatted to be stored.

 @discussion
    The formatting of data within a photo buffer is often dependent on the file format intended for storage. For instance, a JPEG encoded photo buffer intended for storage in a JPEG (JPEG File Interchange Format) file differs from JPEG to be stored in HEIF. The HEIF-containerized JPEG buffer is tiled for readback efficiency and partitioned into the box structure dictated by the HEIF file format. Some codecs are only supported by AVCapturePhotoOutput if containerized. For instance, the AVVideoCodecTypeHEVC is only supported with AVFileTypeHEIF and AVFileTypeHEIC formatting. To discover which photo pixel format types and video codecs are supported for a given file type, you may query AVCapturePhotoOutput's -supportedPhotoPixelFormatTypesForFileType:, or -supportedPhotoCodecTypesForFileType: respectively.
 */
@property(nullable, readonly) AVFileType processedFileType API_AVAILABLE(ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos);

/*!
 @property rawPhotoPixelFormatType
 @abstract
    A Bayer RAW or Apple ProRAW pixel format OSType (defined in CVPixelBuffer.h).

 @discussion
    The rawPixelFormatType you specified in one of the creation methods. Returns 0 if you did not specify RAW capture. See AVCapturePhotoOutput's -capturePhotoWithSettings:delegate: inline documentation for a discussion of restrictions on AVCapturePhotoSettings when requesting RAW capture.
 */
@property(readonly) OSType rawPhotoPixelFormatType API_UNAVAILABLE(macos);

/*!
 @property rawFileType
 @abstract
    The file container for which the RAW photo is formatted to be stored.

 @discussion
    The formatting of data within a RAW photo buffer may be dependent on the file format intended for storage. To discover which RAW photo pixel format types are supported for a given file type, you may query AVCapturePhotoOutput's -supportedRawPhotoPixelFormatTypesForFileType:.
 */
@property(nullable, readonly) AVFileType rawFileType API_AVAILABLE(ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property flashMode
 @abstract
    Specifies whether the flash should be on, off, or chosen automatically by AVCapturePhotoOutput.

 @discussion
    flashMode takes the place of the deprecated AVCaptureDevice -flashMode API. Setting AVCaptureDevice.flashMode has no effect on AVCapturePhotoOutput, which only pays attention to the flashMode specified in your AVCapturePhotoSettings. The default value is AVCaptureFlashModeOff. Flash modes are defined in AVCaptureDevice.h. If you specify a flashMode of AVCaptureFlashModeOn, it wins over autoStillImageStabilizationEnabled=YES. When the device becomes very hot, the flash becomes temporarily unavailable until the device cools down (see AVCaptureDevice's -flashAvailable). While the flash is unavailable, AVCapturePhotoOutput's -supportedFlashModes property still reports AVCaptureFlashModeOn and AVCaptureFlashModeAuto as being available, thus allowing you to specify a flashMode of AVCaptureModeOn. You should always check the AVCaptureResolvedPhotoSettings provided to you in the AVCapturePhotoCaptureDelegate callbacks, as the resolved flashEnabled property will tell you definitively if the flash is being used.
 */
@property(nonatomic) AVCaptureFlashMode flashMode API_UNAVAILABLE(macos);

/*!
 @property autoRedEyeReductionEnabled
 @abstract
    Specifies whether red-eye reduction should be applied automatically on flash captures.
 
 @discussion
    Default is YES on platforms that support automatic red-eye reduction unless you are capturing a bracket using AVCapturePhotoBracketSettings or a RAW photo without a processed photo.  For RAW photos with a processed photo the red-eye reduction will be applied to the processed photo only (RAW photos by definition are not processed). When set to YES, red-eye reduction is applied as needed for flash captures if the photo output's autoRedEyeReductionSupported property returns YES.
 */
@property(nonatomic, getter=isAutoRedEyeReductionEnabled) BOOL autoRedEyeReductionEnabled API_AVAILABLE(ios(12.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @property photoQualityPrioritization
 @abstract
    Indicates how photo quality should be prioritized against speed of photo delivery.

 @discussion
    Default value is AVCapturePhotoQualityPrioritizationBalanced. The AVCapturePhotoOutput is capable of applying a variety of techniques to improve photo quality (reduce noise, preserve detail in low light, freeze motion, etc), depending on the source device's activeFormat. Some of these techniques can take significant processing time before the photo is returned to your delegate callback. The photoQualityPrioritization property allows you to specify your preferred quality vs speed of delivery. By default, speed and quality are considered to be of equal importance. When you specify AVCapturePhotoQualityPrioritizationSpeed, you indicate that speed should be prioritized at the expense of quality. Likewise, when you choose AVCapturePhotoQualityPrioritizationQuality, you signal your willingness to prioritize the very best quality at the expense of speed, and your readiness to wait (perhaps significantly) longer for the photo to be returned to your delegate.
 */
@property(nonatomic) AVCapturePhotoQualityPrioritization photoQualityPrioritization API_AVAILABLE(ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @property autoStillImageStabilizationEnabled
 @abstract
    Specifies whether still image stabilization should be used automatically.

 @discussion
    Default is YES unless you are capturing a Bayer RAW photo (Bayer RAW photos may not be processed by definition) or a bracket using AVCapturePhotoBracketSettings. When set to YES, still image stabilization is applied automatically in low light to counteract hand shake. If the device has optical image stabilization, autoStillImageStabilizationEnabled makes use of lens stabilization as well.
 
    As of iOS 13 hardware, the AVCapturePhotoOutput is capable of applying a variety of multi-image fusion techniques to improve photo quality (reduce noise, preserve detail in low light, freeze motion, etc), all of which have been previously lumped under the stillImageStabilization moniker. This property should no longer be used as it no longer provides meaningful information about the techniques used to improve quality in a photo capture. Instead, you should use -photoQualityPrioritization to indicate your preferred quality vs speed.
 */
@property(nonatomic, getter=isAutoStillImageStabilizationEnabled) BOOL autoStillImageStabilizationEnabled API_DEPRECATED_WITH_REPLACEMENT("photoQualityPrioritization", ios(10.0, 13.0)) API_UNAVAILABLE(macos)  API_UNAVAILABLE(tvos);

/*!
 @property autoVirtualDeviceFusionEnabled
 @abstract
    Specifies whether virtual device image fusion should be used automatically.

 @discussion
    Default is YES unless you are capturing a RAW photo (RAW photos may not be processed by definition) or a bracket using AVCapturePhotoBracketSettings. When set to YES, and -[AVCapturePhotoOutput isVirtualDeviceFusionSupported] is also YES, constituent camera images of a virtual device may be fused to improve still image quality, depending on the current zoom factor, light levels, and focus position. You may determine whether virtual device fusion is enabled for a particular capture request by inspecting the virtualDeviceFusionEnabled property of the AVCaptureResolvedPhotoSettings. Note that when using the deprecated AVCaptureStillImageOutput interface with a virtual device, autoVirtualDeviceFusionEnabled fusion is always enabled if supported, and may not be turned off.
 */
@property(nonatomic, getter=isAutoVirtualDeviceFusionEnabled) BOOL autoVirtualDeviceFusionEnabled API_AVAILABLE(ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @property autoDualCameraFusionEnabled
 @abstract
    Specifies whether DualCamera image fusion should be used automatically.

 @discussion
    Default is YES unless you are capturing a RAW photo (RAW photos may not be processed by definition) or a bracket using AVCapturePhotoBracketSettings. When set to YES, and -[AVCapturePhotoOutput isDualCameraFusionSupported] is also YES, wide-angle and telephoto images may be fused to improve still image quality, depending on the current zoom factor, light levels, and focus position. You may determine whether DualCamera fusion is enabled for a particular capture request by inspecting the dualCameraFusionEnabled property of the AVCaptureResolvedPhotoSettings. Note that when using the deprecated AVCaptureStillImageOutput interface with the DualCamera, auto DualCamera fusion is always enabled and may not be turned off. As of iOS 13, this property is deprecated in favor of autoVirtualDeviceFusionEnabled.
 */
@property(nonatomic, getter=isAutoDualCameraFusionEnabled) BOOL autoDualCameraFusionEnabled API_DEPRECATED_WITH_REPLACEMENT("autoVirtualDeviceFusionEnabled", ios(10.2, 13.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos);

/*!
 @property virtualDeviceConstituentPhotoDeliveryEnabledDevices
 @abstract
    Specifies the constituent devices for which the virtual device should deliver photos.

 @discussion
    Default is empty array. To opt in for constituent device photo delivery, you may set this property to any subset of 2 or more of the devices in virtualDevice.constituentDevices. Your captureOutput:didFinishProcessingPhoto:error: callback will be called n times -- one for each of the devices you include in the array. You may only set this property to a non-nil array if you've set your AVCapturePhotoOutput's virtualDeviceConstituentPhotoDeliveryEnabled property to YES, and your delegate responds to the captureOutput:didFinishProcessingPhoto:error: selector.
 */
@property(nonatomic, copy) NSArray<AVCaptureDevice *> *virtualDeviceConstituentPhotoDeliveryEnabledDevices API_AVAILABLE(ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @property dualCameraDualPhotoDeliveryEnabled
 @abstract
    Specifies whether the DualCamera should return both the telephoto and wide image.

 @discussion
    Default is NO. When set to YES, your captureOutput:didFinishProcessingPhoto:error: callback will receive twice the number of callbacks, as both the telephoto image(s) and wide-angle image(s) are delivered. You may only set this property to YES if you've set your AVCapturePhotoOutput's dualCameraDualPhotoDeliveryEnabled property to YES, and your delegate responds to the captureOutput:didFinishProcessingPhoto:error: selector. As of iOS 13, this property is deprecated in favor of virtualDeviceConstituentPhotoDeliveryEnabledDevices.
 */
@property(nonatomic, getter=isDualCameraDualPhotoDeliveryEnabled) BOOL dualCameraDualPhotoDeliveryEnabled API_DEPRECATED_WITH_REPLACEMENT("virtualDeviceConstituentPhotoDeliveryEnabledDevices", ios(11.0, 13.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos);

/*!
 @property highResolutionPhotoEnabled
 @abstract
    Specifies whether photos should be captured at the highest resolution supported by the source AVCaptureDevice's activeFormat.

 @discussion
    Default is NO. By default, AVCapturePhotoOutput emits images with the same dimensions as its source AVCaptureDevice's activeFormat.formatDescription. However, if you set this property to YES, the AVCapturePhotoOutput emits images at its source AVCaptureDevice's activeFormat.highResolutionStillImageDimensions. Note that if you enable video stabilization (see AVCaptureConnection's preferredVideoStabilizationMode) for any output, the high resolution photos emitted by AVCapturePhotoOutput may be smaller by 10 or more percent. You may inspect your AVCaptureResolvedPhotoSettings in the delegate callbacks to discover the exact dimensions of the capture photo(s).

    Starting in iOS 14.5 if you disable geometric distortion correction, the high resolution photo emitted by AVCapturePhotoOutput may be is smaller depending on the format.
 */
@property(nonatomic, getter=isHighResolutionPhotoEnabled) BOOL highResolutionPhotoEnabled API_UNAVAILABLE(macos);

/*!
 @property depthDataDeliveryEnabled
 @abstract
    Specifies whether AVDepthData should be captured along with the photo.

 @discussion
    Default is NO. Set to YES if you wish to receive depth data with your photo. Throws an exception if -[AVCapturePhotoOutput depthDataDeliveryEnabled] is not set to YES or your delegate does not respond to the captureOutput:didFinishProcessingPhoto:error: selector. Note that setting this property to YES may add significant processing time to the delivery of your didFinishProcessingPhoto: callback.
 
    For best rendering results in Apple's Photos.app, portrait photos should be captured with both embedded depth data and a portrait effects matte (see portraitEffectsMatteDeliveryEnabled). When supported, it is recommended to opt in for both of these auxiliary images in your photo captures involving depth.
 */
@property(nonatomic, getter=isDepthDataDeliveryEnabled) BOOL depthDataDeliveryEnabled API_AVAILABLE(ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property embedsDepthDataInPhoto
 @abstract
    Specifies whether depth data included with this photo should be written to the photo's file structure.

 @discussion
    Default is YES. When depthDataDeliveryEnabled is set to YES, this property specifies whether the included depth data should be written to the resulting photo's internal file structure. Depth data is currently only supported in HEIF and JPEG. This property is ignored if depthDataDeliveryEnabled is set to NO.
 */
@property(nonatomic) BOOL embedsDepthDataInPhoto API_AVAILABLE(ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property depthDataFiltered
 @abstract
    Specifies whether the depth data delivered with the photo should be filtered to fill invalid values.

 @discussion
    Default is YES. This property is ignored unless depthDataDeliveryEnabled is set to YES. Depth data maps may contain invalid pixel values due to a variety of factors including occlusions and low light. When depthDataFiltered is set to YES, the photo output interpolates missing data, filling in all holes.
 */
@property(nonatomic, getter=isDepthDataFiltered) BOOL depthDataFiltered API_AVAILABLE(ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property cameraCalibrationDataDeliveryEnabled
 @abstract
    Specifies whether AVCameraCalibrationData should be captured and delivered along with this photo.

 @discussion
    Default is NO. Set to YES if you wish to receive camera calibration data with your photo. Camera calibration data is delivered as a property of an AVCapturePhoto, so if you are using the CMSampleBuffer delegate callbacks rather than -captureOutput:didFinishProcessingPhoto:error:, an exception is thrown. Also, you may only set this property to YES if your AVCapturePhotoOutput's cameraCalibrationDataDeliverySupported property is YES and 2 or more devices are selected for virtual device constituent photo delivery. When requesting virtual device constituent photo delivery plus camera calibration data, the photos for each constituent device each contain camera calibration data. Note that AVCameraCalibrationData can be delivered as a property of an AVCapturePhoto or an AVDepthData, thus your delegate must respond to the captureOutput:didFinishProcessingPhoto:error: selector.
 */
@property(nonatomic, getter=isCameraCalibrationDataDeliveryEnabled) BOOL cameraCalibrationDataDeliveryEnabled API_AVAILABLE(ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property portraitEffectsMatteDeliveryEnabled
 @abstract
    Specifies whether an AVPortraitEffectsMatte should be captured along with the photo.

 @discussion
    Default is NO. Set to YES if you wish to receive a portrait effects matte with your photo. Throws an exception if -[AVCapturePhotoOutput portraitEffectsMatteDeliveryEnabled] is not set to YES or your delegate does not respond to the captureOutput:didFinishProcessingPhoto:error: selector. Portrait effects matte generation requires depth to be present, so if you wish to enable portrait effects matte delivery, you must set depthDataDeliveryEnabled to YES. Setting this property to YES does not guarantee that a portrait effects matte will be present in the resulting AVCapturePhoto. As the property name implies, the matte is primarily used to improve the rendering quality of portrait effects on the image. If the photo's content lacks a clear foreground subject, no portrait effects matte is generated, and the -[AVCapturePhoto portraitEffectsMatte] property returns nil. Note that setting this property to YES may add significant processing time to the delivery of your didFinishProcessingPhoto: callback.
 
    For best rendering results in Apple's Photos.app, portrait photos should be captured with both embedded depth data (see depthDataDeliveryEnabled) and a portrait effects matte. When supported, it is recommended to opt in for both of these auxiliary images in your photo captures involving depth.
 */
@property(nonatomic, getter=isPortraitEffectsMatteDeliveryEnabled) BOOL portraitEffectsMatteDeliveryEnabled API_AVAILABLE(ios(12.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @property embedsPortraitEffectsMatteInPhoto
 @abstract
    Specifies whether the portrait effects matte captured with this photo should be written to the photo's file structure.

 @discussion
    Default is YES. When portraitEffectsMatteDeliveryEnabled is set to YES, this property specifies whether the included portrait effects matte should be written to the resulting photo's internal file structure. Portrait effects mattes are currently only supported in HEIF and JPEG. This property is ignored if portraitEffectsMatteDeliveryEnabled is set to NO.
 */
@property(nonatomic) BOOL embedsPortraitEffectsMatteInPhoto API_AVAILABLE(ios(12.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @property enabledSemanticSegmentationMatteTypes
 @abstract
    Specifies which types of AVSemanticSegmentationMatte should be captured along with the photo.

 @discussion
    Default is empty array. You may set this property to an array of AVSemanticSegmentationMatteTypes you'd like to capture. Throws an exception if -[AVCapturePhotoOutput enabledSemanticSegmentationMatteTypes] does not contain any of the AVSemanticSegmentationMatteTypes specified. In other words, when setting up a capture session, you opt in for the superset of segmentation matte types you might like to receive, and then on a shot-by-shot basis, you may opt in to all or a subset of the previously specified types by setting this property. An exception is also thrown during -[AVCapturePhotoOutput capturePhotoWithSettings:delegate:] if your delegate does not respond to the captureOutput:didFinishProcessingPhoto:error: selector. Setting this property to YES does not guarantee that the specified mattes will be present in the resulting AVCapturePhoto. If the photo's content lacks any persons, for instance, no hair, skin, or teeth mattes are generated, and the -[AVCapturePhoto semanticSegmentationMatteForType:] property returns nil. Note that setting this property to YES may add significant processing time to the delivery of your didFinishProcessingPhoto: callback.
 */
@property(nonatomic, copy) NSArray<AVSemanticSegmentationMatteType> *enabledSemanticSegmentationMatteTypes API_AVAILABLE(ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @property embedsSemanticSegmentationMattesInPhoto
 @abstract
    Specifies whether enabledSemanticSegmentationMatteTypes captured with this photo should be written to the photo's file structure.

 @discussion
    Default is YES. This property specifies whether the captured semantic segmentation mattes should be written to the resulting photo's internal file structure. Semantic segmentation mattes are currently only supported in HEIF and JPEG. This property is ignored if enabledSemanticSegmentationMatteTypes is set to an empty array.
 */
@property(nonatomic) BOOL embedsSemanticSegmentationMattesInPhoto API_AVAILABLE(ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @property metadata
 @abstract
    A dictionary of metadata key/value pairs you'd like to have written to each photo in the capture request.

 @discussion
    Valid metadata keys are found in <ImageIO/CGImageProperties.h>. AVCapturePhotoOutput inserts a base set of metadata into each photo it captures, such as kCGImagePropertyOrientation, kCGImagePropertyExifDictionary, and kCGImagePropertyMakerAppleDictionary. You may specify metadata keys and values that should be written to each photo in the capture request. If you've specified metadata that also appears in AVCapturePhotoOutput's base set, your value replaces the base value. An NSInvalidArgumentException is thrown if you specify keys other than those found in <ImageIO/CGImageProperties.h>.
 */
@property(nonatomic, copy) NSDictionary<NSString *, id> *metadata API_AVAILABLE(ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property livePhotoMovieFileURL
 @abstract
    Specifies that a Live Photo movie be captured to complement the still photo.

 @discussion
    A Live Photo movie is a short movie (with audio, if you've added an audio input to your session) containing the moments right before and after the still photo. A QuickTime movie file will be written to disk at the URL specified if it is a valid file URL accessible to your app's sandbox. You may only set this property if AVCapturePhotoOutput's livePhotoCaptureSupported property is YES. When you specify a Live Photo, your AVCapturePhotoCaptureDelegate object must implement -captureOutput:didFinishProcessingLivePhotoToMovieFileAtURL:duration:photoDisplayTime:resolvedSettings:error:.
 */
@property(nonatomic, copy, nullable) NSURL *livePhotoMovieFileURL API_UNAVAILABLE(macos);

/*!
 @property livePhotoVideoCodecType
 @abstract
    Specifies the video codec type to use when compressing video for the Live Photo movie complement.

 @discussion
    Prior to iOS 11, all Live Photo movie video tracks are compressed using H.264. Beginning in iOS 11, you can select the Live Photo movie video compression format by specifying one of the strings present in AVCapturePhotoOutput's availableLivePhotoVideoCodecTypes array.
 */
@property(nonatomic, copy) AVVideoCodecType livePhotoVideoCodecType API_AVAILABLE(ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property livePhotoMovieMetadata
 @abstract
    Movie-level metadata to be written to the Live Photo movie.

 @discussion
    An array of AVMetadataItems to be inserted into the top level of the Live Photo movie. The receiver makes immutable copies of the AVMetadataItems in the array. Live Photo movies always contain a AVMetadataQuickTimeMetadataKeyContentIdentifier which allow them to be paired with a similar identifier in the MakerNote of the photo complement. AVCapturePhotoSettings generates a unique content identifier for you. If you provide a metadata array containing an AVMetadataItem with keyspace = AVMetadataKeySpaceQuickTimeMetadata and key = AVMetadataQuickTimeMetadataKeyContentIdentifier, an NSInvalidArgumentException is thrown.
 */
@property(nonatomic, copy, null_resettable) NSArray<AVMetadataItem *> *livePhotoMovieMetadata API_UNAVAILABLE(macos);

/*!
 @property availablePreviewPhotoPixelFormatTypes
 @abstract
    An array of available kCVPixelBufferPixelFormatTypeKeys that may be used when specifying a previewPhotoFormat.
 
 @discussion
    The array is sorted such that the preview format requiring the fewest conversions is presented first.
 */
@property(nonatomic, readonly) NSArray<NSNumber *> *availablePreviewPhotoPixelFormatTypes API_UNAVAILABLE(macos);

/*!
 @property previewPhotoFormat
 @abstract
    A dictionary of Core Video pixel buffer attributes specifying the preview photo format to be delivered along with the RAW or processed photo.

 @discussion
    A dictionary of pixel buffer attributes specifying a smaller version of the RAW or processed photo for preview purposes. The kCVPixelBufferPixelFormatTypeKey is required and must be present in the receiver's -availablePreviewPhotoPixelFormatTypes array. Optional keys are { kCVPixelBufferWidthKey | kCVPixelBufferHeightKey }. If you wish to specify dimensions, you must add both width and height. Width and height are only honored up to the display dimensions. If you specify a width and height whose aspect ratio differs from the RAW or processed photo, the larger of the two dimensions is honored and aspect ratio of the RAW or processed photo is always preserved.
 */
@property(nonatomic, copy, nullable) NSDictionary<NSString *, id> *previewPhotoFormat API_UNAVAILABLE(macos);

/*!
 @property availableEmbeddedThumbnailPhotoCodecTypes
 @abstract
    An array of available AVVideoCodecKeys that may be used when specifying an embeddedThumbnailPhotoFormat.
 
 @discussion
    The array is sorted such that the thumbnail codec type that is most backward compatible is listed first.
 */
@property(nonatomic, readonly) NSArray<AVVideoCodecType> *availableEmbeddedThumbnailPhotoCodecTypes API_AVAILABLE(ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property embeddedThumbnailPhotoFormat
 @abstract
    A dictionary of AVVideoSettings keys specifying the thumbnail format to be written to the processed or RAW photo.

 @discussion
    A dictionary of AVVideoSettings keys specifying a thumbnail (usually smaller) version of the processed photo to be embedded in that image before calling the AVCapturePhotoCaptureDelegate. This image is sometimes referred to as a "thumbnail image". The AVVideoCodecKey is required and must be present in the receiver's -availableEmbeddedThumbnailPhotoCodecTypes array. Optional keys are { AVVideoWidthKey | AVVideoHeightKey }. If you wish to specify dimensions, you must specify both width and height. If you specify a width and height whose aspect ratio differs from the processed photo, the larger of the two dimensions is honored and aspect ratio of the RAW or processed photo is always preserved. For RAW captures, use -rawEmbeddedThumbnailPhotoFormat to specify the thumbnail format you'd like to capture in the RAW image. For apps linked on or after iOS 12, the raw thumbnail format must be specified using the -rawEmbeddedThumbnailPhotoFormat API rather than -embeddedThumbnailPhotoFormat. Beginning in iOS 12, HEIC files may contain thumbnails up to the full resolution of the main image.
 */
@property(nonatomic, copy, nullable) NSDictionary<NSString *, id> *embeddedThumbnailPhotoFormat API_AVAILABLE(ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property availableRawEmbeddedThumbnailPhotoCodecTypes
 @abstract
    An array of available AVVideoCodecKeys that may be used when specifying a rawEmbeddedThumbnailPhotoFormat.
 
 @discussion
    The array is sorted such that the thumbnail codec type that is most backward compatible is listed first.
 */
@property(nonatomic, readonly) NSArray<AVVideoCodecType> *availableRawEmbeddedThumbnailPhotoCodecTypes API_AVAILABLE(ios(12.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @property rawEmbeddedThumbnailPhotoFormat
 @abstract
    A dictionary of AVVideoSettings keys specifying the thumbnail format to be written to the RAW photo in a RAW photo request.

 @discussion
    A dictionary of AVVideoSettings keys specifying a thumbnail (usually smaller) version of the RAW photo to be embedded in that image's DNG before calling back the AVCapturePhotoCaptureDelegate. The AVVideoCodecKey is required and must be present in the receiver's -availableRawEmbeddedThumbnailPhotoCodecTypes array. Optional keys are { AVVideoWidthKey | AVVideoHeightKey }. If you wish to specify dimensions, you must specify both width and height. If you specify a width and height whose aspect ratio differs from the RAW or processed photo, the larger of the two dimensions is honored and aspect ratio of the RAW or processed photo is always preserved. For apps linked on or after iOS 12, the raw thumbnail format must be specified using the -rawEmbeddedThumbnailPhotoFormat API rather than -embeddedThumbnailPhotoFormat. Beginning in iOS 12, DNG files may contain thumbnails up to the full resolution of the RAW image.
 */
@property(nonatomic, copy, nullable) NSDictionary<NSString *, id> *rawEmbeddedThumbnailPhotoFormat API_AVAILABLE(ios(12.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @property autoContentAwareDistortionCorrectionEnabled
 @abstract
    Specifies whether the photo output should use content aware distortion correction on this photo request (at its discretion).

 @discussion
    Default is NO. Set to YES if you wish content aware distortion correction to be performed on your AVCapturePhotos, when the photo output deems it necessary. Photos may or may not benefit from distortion correction. For instance, photos lacking faces may be left as is. Setting this property to YES does introduce a small additional amount of latency to the photo processing. You may check your AVCaptureResolvedPhotoSettings to see whether content aware distortion correction will be enabled for a given photo request. Throws an exception if -[AVCapturePhotoOutput contentAwareDistortionCorrectionEnabled] is not set to YES.
 */
@property(nonatomic, getter=isAutoContentAwareDistortionCorrectionEnabled) BOOL autoContentAwareDistortionCorrectionEnabled API_AVAILABLE(ios(14.1), macCatalyst(14.1)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);
@end


#pragma mark - AVCapturePhotoBracketSettings

@class AVCapturePhotoBracketSettingsInternal;

/*!
 @class AVCapturePhotoBracketSettings
 @abstract
    A concrete subclass of AVCapturePhotoSettings that describes a bracketed capture.
 
 @discussion
    In addition to the properties expressed in the base class, an AVCapturePhotoBracketSettings contains an array of AVCaptureBracketedStillImageSettings objects, where each describes one individual photo in the bracket. bracketedSettings.count must be <= AVCapturePhotoOutput's -maxBracketedCapturePhotoCount. Capturing a photo bracket may require the allocation of additional resources.

    When you request a bracketed capture, your AVCapturePhotoCaptureDelegate's -captureOutput:didFinishProcessing{Photo | RawPhoto}... callbacks are called back bracketSettings.count times and provided with the corresponding AVCaptureBracketedStillImageSettings object from your request.
 */
API_AVAILABLE(ios(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED
@interface AVCapturePhotoBracketSettings : AVCapturePhotoSettings
{
@private
    AVCapturePhotoBracketSettingsInternal *_bracketSettingsInternal;
}

/*!
 @method photoBracketSettingsWithRawPixelFormatType:processedFormat:bracketedSettings:
 @abstract
    Creates an instance of AVCapturePhotoBracketSettings.
 
 @param rawPixelFormatType
    One of the OSTypes contained in AVCapturePhotoOutput's -availableRawPhotoPixelFormatTypes array. May be set to 0 if you do not desire RAW capture.
 @param processedFormat
    A dictionary of Core Video pixel buffer attributes or AVVideoSettings, analogous to AVCaptureStillImageOutput's outputSettings property. If you wish an uncompressed format, your dictionary must contain kCVPixelBufferPixelFormatTypeKey, and the format specified must be present in AVCapturePhotoOutput's -availablePhotoPixelFormatTypes array. kCVPixelBufferPixelFormatTypeKey is the only supported key when expressing uncompressed output. If you wish a compressed format, your dictionary must contain AVVideoCodecKey and the codec specified must be present in AVCapturePhotoOutput's -availablePhotoCodecTypes array. If you are specifying a compressed format, the AVVideoCompressionPropertiesKey is also supported, with a payload dictionary containing a single AVVideoQualityKey. If you only wish to capture RAW, you may pass a non-zero rawPixelFormatType and a nil processedFormat dictionary. If you pass a rawPixelFormatType of 0 AND a nil processedFormat dictionary, the default output of AVVideoCodecTypeJPEG will be delivered.
 @param bracketedSettings
    An array of AVCaptureBracketedStillImageSettings objects (defined in AVCaptureStillImageOutput.h). All must be of the same type, either AVCaptureManualExposureBracketedStillImageSettings or AVCaptureAutoExposureBracketedStillImageSettings. bracketedSettings.count must be <= AVCapturePhotoOutput's -maxBracketedCapturePhotoCount.
 @result
    An instance of AVCapturePhotoBracketSettings.

 @discussion
    An NSInvalidArgumentException is thrown if bracketedSettings is nil, contains zero elements, or mixes and matches different subclasses of AVCaptureBracketedStillImageSettings.
 
    AVCapturePhotoBracketSettings do not support flashMode, autoStillImageStabilizationEnabled, livePhotoMovieFileURL or livePhotoMovieMetadata.
 */
+ (instancetype)photoBracketSettingsWithRawPixelFormatType:(OSType)rawPixelFormatType processedFormat:(nullable NSDictionary<NSString *, id> *)processedFormat bracketedSettings:(NSArray<__kindof AVCaptureBracketedStillImageSettings *> *)bracketedSettings;

/*!
 @method photoBracketSettingsWithRawPixelFormatType:rawFileType:processedFormat:processedFileType:bracketedSettings:
 @abstract
    Creates an instance of AVCapturePhotoBracketSettings.
 
 @param rawPixelFormatType
    One of the OSTypes contained in AVCapturePhotoOutput's -availableRawPhotoPixelFormatTypes array. May be set to 0 if you do not desire RAW capture.
 @param rawFileType
    The file container for which the RAW image should be formatted to be written. Pass nil if you have no preferred file container. A default container will be chosen for you.
 @param processedFormat
    A dictionary of Core Video pixel buffer attributes or AVVideoSettings, analogous to AVCaptureStillImageOutput's outputSettings property. If you wish an uncompressed format, your dictionary must contain kCVPixelBufferPixelFormatTypeKey, and the format specified must be present in AVCapturePhotoOutput's -availablePhotoPixelFormatTypes array. kCVPixelBufferPixelFormatTypeKey is the only supported key when expressing uncompressed output. If you wish a compressed format, your dictionary must contain AVVideoCodecKey and the codec specified must be present in AVCapturePhotoOutput's -availablePhotoCodecTypes array. If you are specifying a compressed format, the AVVideoCompressionPropertiesKey is also supported, with a payload dictionary containing a single AVVideoQualityKey. If you only wish to capture RAW, you may pass a non-zero rawPixelFormatType and a nil processedFormat dictionary. If you pass a rawPixelFormatType of 0 AND a nil processedFormat dictionary, the default output of AVVideoCodecTypeJPEG will be delivered.
 @param processedFileType
    The file container for which the processed image should be formatted to be written. Pass nil if you have no preferred file container. A default container will be chosen for you.
 @param bracketedSettings
    An array of AVCaptureBracketedStillImageSettings objects (defined in AVCaptureStillImageOutput.h). All must be of the same type, either AVCaptureManualExposureBracketedStillImageSettings or AVCaptureAutoExposureBracketedStillImageSettings. bracketedSettings.count must be <= AVCapturePhotoOutput's -maxBracketedCapturePhotoCount.
 @result
    An instance of AVCapturePhotoBracketSettings.
 
 @discussion
    An NSInvalidArgumentException is thrown if bracketedSettings is nil, contains zero elements, or mixes and matches different subclasses of AVCaptureBracketedStillImageSettings.
 
    AVCapturePhotoBracketSettings do not support flashMode, autoStillImageStabilizationEnabled, livePhotoMovieFileURL or livePhotoMovieMetadata.
 */
+ (instancetype)photoBracketSettingsWithRawPixelFormatType:(OSType)rawPixelFormatType rawFileType:(nullable AVFileType)rawFileType processedFormat:(nullable NSDictionary<NSString *, id> *)processedFormat processedFileType:(nullable AVFileType)processedFileType bracketedSettings:(NSArray<AVCaptureBracketedStillImageSettings *> *)bracketedSettings API_AVAILABLE(ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos);

/*!
 @property bracketedSettings
 @abstract
    An array of AVCaptureBracketedStillImageSettings objects you passed in -initWithFormat:rawPixelFormatType:bracketedSettings:

 @discussion
    This read-only property never returns nil.
 */
@property(nonatomic, readonly) NSArray<__kindof AVCaptureBracketedStillImageSettings *> *bracketedSettings;

/*!
 @property lensStabilizationEnabled
 @abstract
    Specifies whether lens (optical) stabilization should be employed during the bracketed capture.

 @discussion
    Default value is NO. This property may only be set to YES if AVCapturePhotoOutput's isLensStabilizationDuringBracketedCaptureSupported is YES. When set to YES, AVCapturePhotoOutput holds the lens steady for the duration of the bracket to counter hand shake and produce a sharper bracket of images.
 */
@property(nonatomic, getter=isLensStabilizationEnabled) BOOL lensStabilizationEnabled;

@end


#pragma mark - AVCaptureResolvedPhotoSettings

@class AVCaptureResolvedPhotoSettingsInternal;

/*!
 @class AVCaptureResolvedPhotoSettings
 @abstract
    An immutable object produced by callbacks in each and every AVCapturePhotoCaptureDelegate protocol method.
 
 @discussion
    When you initiate a photo capture request using -capturePhotoWithSettings:delegate:, some of your settings are not yet certain. For instance, auto flash and auto still image stabilization allow the AVCapturePhotoOutput to decide just in time whether to employ flash or still image stabilization, depending on the current scene. Once the request is issued, AVCapturePhotoOutput begins the capture, resolves the uncertain settings, and in its first callback informs you of its choices through an AVCaptureResolvedPhotoSettings object. This same object is presented to all the callbacks fired for a particular photo capture request. Its uniqueID property matches that of the AVCapturePhotoSettings instance you used to initiate the photo request.
 */
API_AVAILABLE(macos(10.15), ios(10.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface AVCaptureResolvedPhotoSettings : NSObject
{
@private
    AVCaptureResolvedPhotoSettingsInternal *_internal;
}

AV_INIT_UNAVAILABLE

/*!
 @property uniqueID
 @abstract
    uniqueID matches that of the AVCapturePhotoSettings instance you passed to -capturePhotoWithSettings:delegate:.
 */
@property(readonly) int64_t uniqueID;

/*!
 @property photoDimensions
 @abstract
    The resolved dimensions of the photo buffer that will be delivered to the -captureOutput:didFinishProcessingPhotoSampleBuffer:previewPhotoSampleBuffer:resolvedSettings:bracketSettings:error: callback.
 
 @discussion
    If you request a RAW capture with no processed companion image, photoDimensions resolve to { 0, 0 }.
 */
@property(readonly) CMVideoDimensions photoDimensions;

/*!
 @property rawPhotoDimensions
 @abstract
    The resolved dimensions of the RAW photo buffer that will be delivered to the -captureOutput:didFinishProcessingRawPhotoSampleBuffer:previewPhotoSampleBuffer:resolvedSettings:bracketSettings:error: callback.

 @discussion
    If you request a non-RAW capture, rawPhotoDimensions resolve to { 0, 0 }.
 */
@property(readonly) CMVideoDimensions rawPhotoDimensions API_UNAVAILABLE(macos);

/*!
 @property previewDimensions
 @abstract
    The resolved dimensions of the preview photo buffer that will be delivered to the -captureOutput:didFinishProcessing{Photo | RawPhoto}... AVCapturePhotoCaptureDelegate callbacks.

 @discussion
    If you don't request a preview image, previewDimensions resolve to { 0, 0 }.
 */
@property(readonly) CMVideoDimensions previewDimensions API_UNAVAILABLE(macos);

/*!
 @property embeddedThumbnailDimensions
 @abstract
    The resolved dimensions of the embedded thumbnail that will be written to the processed photo delivered to the -captureOutput:didFinishProcessingPhoto:error: AVCapturePhotoCaptureDelegate callback.

 @discussion
    If you don't request an embedded thumbnail image, embeddedThumbnailDimensions resolve to { 0, 0 }.
 */
@property(readonly) CMVideoDimensions embeddedThumbnailDimensions API_AVAILABLE(ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property rawEmbeddedThumbnailDimensions
 @abstract
    The resolved dimensions of the embedded thumbnail that will be written to the RAW photo delivered to the -captureOutput:didFinishProcessingPhoto:error: AVCapturePhotoCaptureDelegate callback.

 @discussion
    If you don't request a raw embedded thumbnail image, rawEmbeddedThumbnailDimensions resolve to { 0, 0 }.
 */
@property(readonly) CMVideoDimensions rawEmbeddedThumbnailDimensions API_AVAILABLE(ios(12.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @property portraitEffectsMatteDimensions
 @abstract
    The resolved dimensions of the portrait effects matte that will be delivered to the AVCapturePhoto in the -captureOutput:didFinishProcessingPhoto:error: AVCapturePhotoCaptureDelegate callback.

 @discussion
    If you request a portrait effects matte by calling -[AVCapturePhotoSettings setPortraitEffectsMatteDeliveryEnabled:YES], portraitEffectsMatteDimensions resolve to the expected dimensions of the portrait effects matte, assuming one is generated (see -[AVCapturePhotoSettings portraitEffectsMatteDeliveryEnabled] for a discussion of why a portrait effects matte might not be delivered). If you don't request a portrait effects matte, portraitEffectsMatteDimensions always resolve to { 0, 0 }.
 */
@property(readonly) CMVideoDimensions portraitEffectsMatteDimensions API_AVAILABLE(ios(12.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @method dimensionsForSemanticSegmentationMatteOfType:
 @abstract
    Queries the resolved dimensions of semantic segmentation mattes that will be delivered to the AVCapturePhoto in the -captureOutput:didFinishProcessingPhoto:error: AVCapturePhotoCaptureDelegate callback.

 @discussion
    If you request semantic segmentation mattes by calling -[AVCapturePhotoSettings setEnabledSemanticSegmentationMatteTypes:] with a non-empty array, the dimensions resolve to the expected dimensions for each of the mattes, assuming they are generated (see -[AVCapturePhotoSettings enabledSemanticSegmentationMatteTypes] for a discussion of why a particular matte might not be delivered). If you don't request any semantic segmentation mattes, the result will always be { 0, 0 }.
 */
- (CMVideoDimensions)dimensionsForSemanticSegmentationMatteOfType:(AVSemanticSegmentationMatteType)semanticSegmentationMatteType API_AVAILABLE(ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @property livePhotoMovieDimensions
 @abstract
    The resolved dimensions of the video track in the movie that will be delivered to the -captureOutput:didFinishProcessingLivePhotoToMovieFileAtURL:duration:photoDisplayTime:resolvedSettings:error: callback.
 
 @discussion
    If you don't request Live Photo capture, livePhotoMovieDimensions resolve to { 0, 0 }.
 */
@property(readonly) CMVideoDimensions livePhotoMovieDimensions API_UNAVAILABLE(macos);

/*!
 @property flashEnabled
 @abstract
    Indicates whether the flash will fire when capturing the photo.

 @discussion
    When you specify AVCaptureFlashModeAuto as you AVCapturePhotoSettings.flashMode, you don't know if flash capture will be chosen until you inspect the AVCaptureResolvedPhotoSettings flashEnabled property. If the device becomes too hot, the flash becomes temporarily unavailable. You can key-value observe AVCaptureDevice's flashAvailable property to know when this occurs. If the flash is unavailable due to thermal issues, and you specify a flashMode of AVCaptureFlashModeOn, flashEnabled still resolves to NO until the device has sufficiently cooled off.
 */
@property(readonly, getter=isFlashEnabled) BOOL flashEnabled API_UNAVAILABLE(macos);

/*!
 @property redEyeReductionEnabled
 @abstract
    Indicates whether red-eye reduction will be applied as necessary when capturing the photo if flashEnabled is YES.
 */
@property(readonly, getter=isRedEyeReductionEnabled) BOOL redEyeReductionEnabled API_AVAILABLE(ios(12.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @property stillImageStabilizationEnabled
 @abstract
    Indicates whether still image stabilization will be employed when capturing the photo.
 
	As of iOS 13 hardware, the AVCapturePhotoOutput is capable of applying a variety of multi-image fusion techniques to improve photo quality (reduce noise, preserve detail in low light, freeze motion, etc), all of which have been previously lumped under the stillImageStabilization moniker. This property should no longer be used as it no longer provides meaningful information about the techniques used to improve quality in a photo capture. Instead, you should use -photoQualityPrioritization to indicate your preferred quality vs speed when configuring your AVCapturePhotoSettings. You may query -photoProcessingTimeRange to get an indication of how long the photo will take to process before delivery to your delegate.
 */
@property(readonly, getter=isStillImageStabilizationEnabled) BOOL stillImageStabilizationEnabled API_DEPRECATED_WITH_REPLACEMENT("photoProcessingTimeRange", ios(10.0, 13.0)) API_UNAVAILABLE(macos);

/*!
 @property virtualDeviceFusionEnabled
 @abstract
    Indicates whether fusion of virtual device constituent camera images will be used when capturing the photo, such as the wide-angle and telephoto images on a DualCamera.
 */
@property(readonly, getter=isVirtualDeviceFusionEnabled) BOOL virtualDeviceFusionEnabled API_AVAILABLE(ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @property dualCameraFusionEnabled
 @abstract
    Indicates whether DualCamera wide-angle and telephoto image fusion will be employed when capturing the photo. As of iOS 13, this property is deprecated in favor of virtualDeviceFusionEnabled.
 */
@property(readonly, getter=isDualCameraFusionEnabled) BOOL dualCameraFusionEnabled API_DEPRECATED_WITH_REPLACEMENT("virtualDeviceFusionEnabled", ios(10.2, 13.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos);

/*!
 @property expectedPhotoCount
 @abstract
    Indicates the number of times your -captureOutput:didFinishProcessingPhoto:error: callback will be called. For instance, if you've requested an auto exposure bracket of 3 with JPEG and RAW, the expectedPhotoCount is 6.
 */
@property(readonly) NSUInteger expectedPhotoCount API_AVAILABLE(ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos);

/*!
 @property photoProcessingTimeRange
 @abstract
    Indicates the processing time range you can expect for this photo to be delivered to your delegate. the .start field of the CMTimeRange is zero-based. In other words, if photoProcessingTimeRange.start is equal to .5 seconds, then the minimum processing time for this photo is .5 seconds. The .start field plus the .duration field of the CMTimeRange indicate the max expected processing time for this photo. Consider implementing a UI affordance if the max processing time is uncomfortably long.
 */
@property(readonly) CMTimeRange photoProcessingTimeRange API_AVAILABLE(ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property contentAwareDistortionCorrectionEnabled
 @abstract
    Indicates whether content aware distortion correction will be employed when capturing the photo.
 */
@property(readonly, getter=isContentAwareDistortionCorrectionEnabled) BOOL contentAwareDistortionCorrectionEnabled API_AVAILABLE(ios(14.1), macCatalyst(14.1)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);
@end


#pragma mark - AVCapturePhoto

@class AVCapturePhotoInternal;
@class AVDepthData;
@class AVCameraCalibrationData;

/*!
 @class AVCapturePhoto
 @abstract
    An object representing a photo in memory, produced by the -captureOutput:didFinishingProcessingPhoto:error: in the AVCapturePhotoCaptureDelegate protocol method.
 
 @discussion
    Beginning in iOS 11, AVCapturePhotoOutput's AVCapturePhotoCaptureDelegate supports a simplified callback for delivering image data, namely -captureOutput:didFinishingProcessingPhoto:error:. This callback presents each image result for your capture request as an AVCapturePhoto object, an immutable wrapper from which various properties of the photo capture may be queried, such as the photo's preview pixel buffer, metadata, depth data, camera calibration data, and image bracket specific properties. AVCapturePhoto can wrap file-containerized photo results, such as HEVC encoded image data, containerized in the HEIC file format. CMSampleBufferRef, on the other hand, may only be used to express non file format containerized photo data. For this reason, the AVCapturePhotoCaptureDelegate protocol methods that return CMSampleBuffers have been deprecated in favor of -captureOutput:didFinishingProcessingPhoto:error:. A AVCapturePhoto wraps a single image result. For instance, if you've requested a bracketed capture of 3 images, your callback is called 3 times, each time delivering an AVCapturePhoto.
 */
API_AVAILABLE(macos(10.15), ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface AVCapturePhoto : NSObject
{
@private
    AVCapturePhotoInternal *_internal;
}

AV_INIT_UNAVAILABLE

/*!
 @property timestamp
 @abstract
    The time at which this image was captured, synchronized to the synchronizationClock of the AVCaptureSession

 @discussion
    The timestamp property indicates the time the image was captured, and is analogous to CMSampleBufferGetPresentationTimeStamp(). If an error was provided in the -captureOutput:didFinishingProcessingPhoto:error: callback, timestamp returns kCMTimeInvalid.
 */
@property(readonly) CMTime timestamp;

/*!
 @property rawPhoto
 @abstract
    This property returns YES if this photo is a RAW image.

 @discussion
    Your AVCapturePhotoCaptureDelegate's -captureOutput:didFinishingProcessingPhoto:error: method may be called one or more times with image results, including RAW or non-RAW images. This property distinguishes RAW from non-RAW image results, for instance, if you've requested a RAW + JPEG capture.
 */
@property(readonly, getter=isRawPhoto) BOOL rawPhoto API_UNAVAILABLE(macos);

/*!
 @property pixelBuffer
 @abstract
    For uncompressed or RAW captures, this property offers access to the pixel data.

 @discussion
    Uncompressed captures, such as '420f' or 'BGRA', Bayer RAW captures, such as 'bgg4', or Apple ProRAW captures, such as 'l64r', present pixel data as a CVPixelBuffer. See AVCapturePhotoOutput's -appleProRAWEnabled for a discussion on the differences between Bayer RAW and Apple ProRAW. This property is analogous to CMSampleBufferGetImageBuffer(). The pixel buffer contains only the minimal attachments required for correct display. Compressed captures, such as 'jpeg', return nil.
 */
@property(nullable, readonly) CVPixelBufferRef pixelBuffer NS_RETURNS_INNER_POINTER;

/*!
 @property previewPixelBuffer
 @abstract
    This property offers access to the preview image pixel data if you've requested it.

 @discussion
    If you requested a preview image by calling -[AVCapturePhotoSettings setPreviewPhotoFormat:] with a non-nil value, this property offers access to the resulting preview image pixel data, and is analogous to CMSampleBufferGetImageBuffer(). The pixel buffer contains only the minimal attachments required for correct display. Nil is returned if you did not request a preview image.
 */
@property(nullable, readonly) CVPixelBufferRef previewPixelBuffer NS_RETURNS_INNER_POINTER API_UNAVAILABLE(macos);

/*!
 @property embeddedThumbnailPhotoFormat
 @abstract
    The format of the embedded thumbnail contained in this AVCapturePhoto.

 @discussion
    If you requested an embedded thumbnail image by calling -[AVCapturePhotoSettings setEmbeddedThumbnailPhotoFormat:] with a non-nil value, this property offers access to the resolved embedded thumbnail AVVideoSettings dictionary. Nil is returned if you did not request an embedded thumbnail image.
 */
@property(nullable, readonly) NSDictionary<NSString *, id> *embeddedThumbnailPhotoFormat API_UNAVAILABLE(macos);

/*!
 @property depthData
 @abstract
    An AVDepthData object wrapping a disparity/depth map associated with this photo.

 @discussion
    If you requested depth data delivery by calling -[AVCapturePhotoSettings setDepthDataDeliveryEnabled:YES], this property offers access to the resulting AVDepthData object. Nil is returned if you did not request depth data delivery. Note that the depth data is only embedded in the photo's internal file format container if you set -[AVCapturePhotoSettings setEmbedsDepthDataInPhoto:YES].
 */
@property(nullable, readonly) AVDepthData *depthData API_UNAVAILABLE(macos);

/*!
 @property portraitEffectsMatte
 @abstract
    An AVPortraitEffectsMatte object wrapping a matte associated with this photo.

 @discussion
    If you requested portrait effects matte delivery by calling -[AVCapturePhotoSettings setPortraitEffectsMatteDeliveryEnabled:YES], this property offers access to the resulting AVPortraitEffectsMatte object. Nil is returned if you did not request portrait effects matte delivery. Note that the portrait effects matte is only embedded in the photo's internal file format container if you set -[AVCapturePhotoSettings setEmbedsPortraitEffectsMatteInPhoto:YES].
 */
@property(nullable, readonly) AVPortraitEffectsMatte *portraitEffectsMatte API_AVAILABLE(ios(12.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @method semanticSegmentationMatteForType:
 @abstract
    An accessor for semantic segmentation mattes associated with this photo.
 
 @param semanticSegmentationMatteType
    The matte type of interest (hair, skin, etc).
 @result
    An instance of AVSemanticSegmentationMatte, or nil if none could be found for the specified type.
 
 @discussion
    If you requested one or more semantic segmentation mattes by calling -[AVCapturePhotoSettings setEnabledSemanticSegmentationMatteTypes:] with a non-empty array of types, this property offers access to the resulting AVSemanticSegmentationMatte objects. Nil is returned if you did not request semantic segmentation matte delivery, or if no mattes of the specified type are available. Note that semantic segmentation mattes are only embedded in the photo's internal file format container if you call -[AVCapturePhotoSettings setEmbedsSemanticSegmentationMattesInPhoto:YES].
 */
- (nullable AVSemanticSegmentationMatte *)semanticSegmentationMatteForType:(AVSemanticSegmentationMatteType)semanticSegmentationMatteType API_AVAILABLE(ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @property metadata
 @abstract
    An ImageIO property style dictionary of metadata associated with this photo.

 @discussion
    Valid metadata keys are found in <ImageIO/CGImageProperties.h>, such as kCGImagePropertyOrientation, kCGImagePropertyExifDictionary, kCGImagePropertyMakerAppleDictionary, etc.
 */
@property(readonly) NSDictionary<NSString *, id> *metadata API_UNAVAILABLE(macos);

/*!
 @property cameraCalibrationData
 @abstract
    An AVCameraCalibrationData object representing the calibration information for the camera providing the photo.

 @discussion
    Camera calibration data is only present if you set AVCapturePhotoSettings.setCameraCalibrationDataDeliveryEnabled to YES. When requesting virtual device constituent photo delivery plus cameraCalibrationDataDeliveryEnabled, camera calibration information is delivered with all resultant photos and is specific to the constituent device producing that photo.
 */
@property(nullable, readonly) AVCameraCalibrationData *cameraCalibrationData API_UNAVAILABLE(macos);

/*!
 @property resolvedSettings
 @abstract
    The AVCaptureResolvedPhotoSettings associated with all photo results for a given -[AVCapturePhotoOutput capturePhotoWithSettings:delegate:] request.

 @discussion
    Even in the event of an error, the resolved settings are always non nil.
 */
@property(readonly) AVCaptureResolvedPhotoSettings *resolvedSettings;

/*!
 @property photoCount
 @abstract
    This photo's index (1-based) in the total expected photo count.

 @discussion
    The resolvedSettings.expectedPhotoCount property indicates the total number of images that will be returned for a given capture request. This property indicates this photo's index (1-based). When you receive a -captureOutput:didFinishProcessingPhoto:error: callback with a photo whose photoCount matches resolvedSettings.expectedPhotoCount, you know you've received the last one for the given capture request.
 */
@property(readonly) NSInteger photoCount;

/*!
 @property sourceDeviceType
 @abstract
    The device type of the source camera providing the photo.

 @discussion
    When taking a virtual device constituent photo capture, you may query this property to find out the source type of the photo. For instance, on a DualCamera, resulting photos will be of sourceDeviceType AVCaptureDeviceTypeBuiltInWideCamera, or AVCaptureDeviceTypeBuiltInTelephotoCamera. For all other types of capture, the source device type is equal to the -[AVCaptureDevice deviceType] of the AVCaptureDevice to which the AVCapturePhotoOutput is connected. Returns nil if the source of the photo is not an AVCaptureDevice.
 */
@property(nullable, readonly) AVCaptureDeviceType sourceDeviceType API_UNAVAILABLE(macos);

@end

@protocol AVCapturePhotoFileDataRepresentationCustomizer;

API_AVAILABLE(macos(10.15), ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface AVCapturePhoto (AVCapturePhotoConversions)

/*!
 @method fileDataRepresentation
 @abstract
    Flattens the AVCapturePhoto to an NSData using the file container format (processedFileType or rawFileType) specified in the AVCapturePhotoSettings (e.g. JFIF, HEIF, DNG).
 
 @result
    An NSData containing bits in the file container's format, or nil if the flattening process fails.
 */
- (nullable NSData *)fileDataRepresentation API_AVAILABLE(ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos);

/*!
 @method fileDataRepresentationWithCustomizer:
 @abstract
    Flattens the AVCapturePhoto to an NSData using the file container format (processedFileType or rawFileType) specified in the AVCapturePhotoSettings (e.g. JFIF, HEIF, DNG), and allows you to strip or replace various pieces of metadata in the process.
 
 @param customizer
    An object conforming to the AVCapturePhotoFileDataRepresentationCustomizer protocol that will be called synchronously to provide customization of metadata written to the container format. An NSInvalidArgumentException is thrown if you pass nil.
 @result
    An NSData containing bits in the file container's format, or nil if the flattening process fails.
 */
- (nullable NSData *)fileDataRepresentationWithCustomizer:(id<AVCapturePhotoFileDataRepresentationCustomizer>)customizer API_AVAILABLE(ios(12.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @method fileDataRepresentationWithReplacementMetadata:replacementEmbeddedThumbnailPhotoFormat:replacementEmbeddedThumbnailPixelBuffer:replacementDepthData:
 @abstract
    Flattens the AVCapturePhoto to an NSData using the file container format (processedFileType or rawFileType) specified in the AVCapturePhotoSettings (e.g. JFIF, HEIF, DNG), and allows you to replace metadata, thumbnail, and depth data in the process.
 
 @param replacementMetadata
    A dictionary of keys and values from <ImageIO/CGImageProperties.h>. To preserve existing metadata to the file, pass self.metadata. To strip existing metadata, pass nil. To replace metadata, pass a replacement dictionary.
 @param replacementEmbeddedThumbnailPhotoFormat
    A dictionary of keys and values from <AVFoundation/AVVideoSettings.h>. If you pass a non-nil dictionary, AVVideoCodecKey is required, with AVVideoWidthKey and AVVideoHeightKey being optional. To preserve the existing embedded thumbnail photo to the file, pass self.embeddedThumbnailPhotoFormat and pass nil as your replacementEmbeddedThumbnailPixelBuffer parameter. To strip the existing embedded thumbnail, pass nil for both replacementEmbeddedThumbnailPhotoFormat and replacementEmbeddedThumbnailPixelBuffer. To replace the existing embedded thumbnail photo, pass both a non-nil replacementThumbnailPixelBuffer and replacementEmbeddedThumbnailPhotoFormat dictionary.
 @param replacementEmbeddedThumbnailPixelBuffer
    A pixel buffer containing a source image to be encoded to the file as the replacement thumbnail image. To preserve the existing embedded thumbnail photo to the file, pass self.embeddedThumbnailPhotoFormat as your replacementEmbeddedThumbnailPhotoFormat parameter and nil as your replacementEmbeddedThumbnailPixelBuffer parameter. To strip the existing embedded thumbnail, pass nil for both replacementEmbeddedThumbnailPhotoFormat and replacementEmbeddedThumbnailPixelBuffer. To replace the existing embedded thumbnail photo, pass both a non-nil replacementThumbnailPixelBuffer and replacementEmbeddedThumbnailPhotoFormat dictionary.
 @param replacementDepthData
    Replacement depth data to be written to the flattened file container. To preserve existing depth data to the file, pass self.depthData. To strip it, pass nil. To replace it, pass a new AVDepthData instance.
 @result
    An NSData containing bits in the file container's format, or nil if the flattening process fails.
 */
- (nullable NSData *)fileDataRepresentationWithReplacementMetadata:(nullable NSDictionary<NSString *, id> *)replacementMetadata replacementEmbeddedThumbnailPhotoFormat:(nullable NSDictionary<NSString *, id> *)replacementEmbeddedThumbnailPhotoFormat replacementEmbeddedThumbnailPixelBuffer:(nullable CVPixelBufferRef)replacementEmbeddedThumbnailPixelBuffer replacementDepthData:(nullable AVDepthData *)replacementDepthData API_DEPRECATED_WITH_REPLACEMENT("fileDataRepresentationWithCustomizer:", ios(11.0, 12.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos);

/*!
 @method CGImageRepresentation
 @abstract
    Utility method that converts the AVCapturePhoto's primary photo to a CGImage.
 
 @result
    A CGImageRef, or nil if the conversion process fails.
 
 @discussion
    Each time you access this method, AVCapturePhoto generates a new CGImageRef. When backed by a compressed container (such as HEIC), the CGImageRepresentation is decoded lazily as needed. When backed by an uncompressed format such as BGRA, it is copied into a separate backing buffer whose lifetime is not tied to that of the AVCapturePhoto. For a 12 megapixel image, a BGRA CGImage represents ~48 megabytes per call. If you only intend to use the CGImage for on-screen rendering, use the previewCGImageRepresentation instead. Note that the physical rotation of the CGImageRef matches that of the main image. Exif orientation has not been applied. If you wish to apply rotation when working with UIImage, you can do so by querying the photo's metadata[kCGImagePropertyOrientation] value, and passing it as the orientation parameter to +[UIImage imageWithCGImage:scale:orientation:]. RAW images always return a CGImageRepresentation of nil. If you wish to make a CGImageRef from a RAW image, use CIRAWFilter in the CoreImage framework.
 */
- (nullable CGImageRef)CGImageRepresentation API_AVAILABLE(ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) CF_RETURNS_NOT_RETAINED;

/*!
 @method CGImageRepresentation
 @abstract
    Utility method that converts the AVCapturePhoto's preview photo to a CGImage.
 
 @result
    A CGImageRef, or nil if the conversion process fails, or if you did not request a preview photo.
 
 @discussion
    Each time you access this method, AVCapturePhoto generates a new CGImageRef. This CGImageRepresentation is a RGB rendering of the previewPixelBuffer property. If you did not request a preview photo by setting the -[AVCapturePhotoSettings previewPhotoFormat] property, this method returns nil. Note that the physical rotation of the CGImageRef matches that of the main image. Exif orientation has not been applied. If you wish to apply rotation when working with UIImage, you can do so by querying the photo's metadata[kCGImagePropertyOrientation] value, and passing it as the orientation parameter to +[UIImage imageWithCGImage:scale:orientation:].
 */
- (nullable CGImageRef)previewCGImageRepresentation API_AVAILABLE(ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) CF_RETURNS_NOT_RETAINED;

@end


/*!
 @enum AVCaptureLensStabilizationStatus
 @abstract
    Constants indicating the status of the lens stabilization module (aka OIS).

 @constant AVCaptureLensStabilizationStatusUnsupported
    Indicates that lens stabilization is unsupported.
 @constant AVCaptureLensStabilizationStatusOff
    Indicates that lens stabilization was not in use for this capture.
 @constant AVCaptureLensStabilizationStatusActive
    Indicates that the lens stabilization module was active for the duration of the capture.
 @constant AVCaptureLensStabilizationStatusOutOfRange
    Indicates that device motion or capture duration exceeded the stabilization module's correction limits.
 @constant AVCaptureLensStabilizationStatusUnavailable
    Indicates that the lens stabilization module was unavailable for use at the time of capture. The module may be available in subsequent captures.
 */
typedef NS_ENUM(NSInteger, AVCaptureLensStabilizationStatus) {
    AVCaptureLensStabilizationStatusUnsupported = 0,
    AVCaptureLensStabilizationStatusOff         = 1,
    AVCaptureLensStabilizationStatusActive      = 2,
    AVCaptureLensStabilizationStatusOutOfRange  = 3,
    AVCaptureLensStabilizationStatusUnavailable = 4,
} API_AVAILABLE(ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

API_AVAILABLE(macos(10.15), ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface AVCapturePhoto (AVCapturePhotoBracketedCapture)

/*!
 @property bracketSettings
 @abstract
    The AVCaptureBracketedStillImageSettings associated with this photo.

 @discussion
    When specifying a bracketed capture using AVCapturePhotoBracketSettings, you specify an array of AVCaptureBracketedStillImageSettings -- one per image in the bracket. This property indicates the AVCaptureBracketedStillImageSettings associated with this particular photo, or nil if this photo is not part of a bracketed capture.
 */
@property(nullable, readonly) AVCaptureBracketedStillImageSettings *bracketSettings API_AVAILABLE(ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property sequenceCount
 @abstract
    1-based sequence count of the photo.

 @discussion
    If this photo is part of a bracketed capture (invoked using AVCapturePhotoBracketSettings), this property indicates the current result's count in the sequence, starting with 1 for the first result, or 0 if this photo is not part of a bracketed capture.
 */
@property(readonly) NSInteger sequenceCount API_AVAILABLE(ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property lensStabilizationStatus
 @abstract
    The status of the lens stabilization module during capture of this photo.

 @discussion
    In configurations where lens stabilization (OIS) is unsupported, AVCaptureLensStabilizationStatusUnsupported is returned. If lens stabilization is supported, but this photo is not part of a bracketed capture in which -[AVCapturePhotoBracketSettings setLensStabilizationEnabled:YES] was called, AVCaptureLensStabilizationStatusOff is returned. Otherwise a lens stabilization status is returned indicating how lens stabilization was applied during the capture.
 */
@property(readonly) AVCaptureLensStabilizationStatus lensStabilizationStatus API_AVAILABLE(ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

@end


/*!
 @protocol AVCapturePhotoFileDataRepresentationCustomizer
 @abstract
    A set of delegate callbacks to be implemented by a client who calls AVCapturePhoto's -fileDataRepresentationWithCustomizer:.
 
 @discussion
    AVCapturePhoto is a wrapper representing a file-containerized photo in memory. If you simply wish to flatten the photo to an NSData to be written to a file, you may call -[AVCapturePhoto fileDataRepresentation]. For more complex flattening operations in which you wish to replace or strip metadata, you should call -[AVCapturePhoto fileDataRepresentationWithCustomizer:] instead, providing a delegate for customized stripping / replacing behavior. This delegate's methods are called synchronously before the flattening process commences.
 */
API_AVAILABLE(ios(12.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos)
@protocol AVCapturePhotoFileDataRepresentationCustomizer <NSObject>

@optional
/*!
 @method replacementMetadataForPhoto:
 @abstract
    A callback in which you may provide replacement metadata, or direct the AVCapturePhoto to strip existing metadata from the flattened file data representation.
 
 @param photo
    The calling instance of AVCapturePhoto.
 @return
    A dictionary of keys and values from <ImageIO/CGImageProperties.h>. To preserve existing metadata, return photo.metadata. To strip existing metadata, return nil. To replace metadata, pass a replacement dictionary.

 @discussion
    This callback is optional. If your delegate does not implement this callback, the existing metadata in the in-memory AVCapturePhoto container will be written to the file data representation.
 */
- (nullable NSDictionary<NSString *, id> *)replacementMetadataForPhoto:(AVCapturePhoto *)photo;

/*!
 @method replacementEmbeddedThumbnailPixelBufferWithPhotoFormat:forPhoto:
 @abstract
    A callback in which you may provide a replacement embedded thumbnail image with compression settings, or strip the existing embedded thumbnail image from the flattened file data representation.
 
 @param replacementEmbeddedThumbnailPhotoFormatOut
    On output, a pointer to a dictionary of keys and values from <AVFoundation/AVVideoSettings.h> If you pass a non-nil dictionary, AVVideoCodecKey is required, with AVVideoWidthKey and AVVideoHeightKey being optional. To preserve the existing embedded thumbnail photo to the flattened data, set *replacementEmbeddedThumbnailPhotoFormatOut to photo.embeddedThumbnailPhotoFormat and return nil. To strip the existing embedded thumbnail, set *replacementEmbeddedThumbnailPhotoFormatOut to nil and return nil. To replace the existing embedded thumbnail photo, pass a replacement photo format dictionary and return a non-nil replacement pixel buffer.
 @param photo
    The calling instance of AVCapturePhoto.
 @return
    A pixel buffer containing a source image to be encoded to the file as the replacement thumbnail image. To preserve the existing embedded thumbnail photo to the flattened data, set *replacementEmbeddedThumbnailPhotoFormatOut to photo.embeddedThumbnailPhotoFormat and return nil. To strip the existing embedded thumbnail, set *replacementEmbeddedThumbnailPhotoFormatOut to nil and return nil. To replace the existing embedded thumbnail photo, pass a replacement photo format dictionary and return a non-nil replacement pixel buffer.

 @discussion
    This callback is optional. If your delegate does not implement this callback, the existing embedded thumbnail photo in the in-memory AVCapturePhoto container will be written to the file data representation.
 */
- (nullable CVPixelBufferRef)replacementEmbeddedThumbnailPixelBufferWithPhotoFormat:(NSDictionary<NSString *, id> *_Nullable * _Nonnull)replacementEmbeddedThumbnailPhotoFormatOut forPhoto:(AVCapturePhoto *)photo;

/*!
 @method replacementDepthDataForPhoto:
 @abstract
    A callback in which you may provide replacement depth data, or strip the existing depth data from the flattened file data representation.
 
 @param photo
    The calling instance of AVCapturePhoto.
 @return
    An instance of AVDepthData. To preserve the existing depth data, return photo.depthData. To strip the existing one, return nil. To replace, provide a replacement AVDepthData instance.

 @discussion
    This callback is optional. If your delegate does not implement this callback, the existing depth data in the in-memory AVCapturePhoto container will be written to the file data representation.
 */
- (nullable AVDepthData *)replacementDepthDataForPhoto:(AVCapturePhoto *)photo;

/*!
 @method replacementPortraitEffectsMatteForPhoto:
 @abstract
    A callback in which you may provide a replacement portrait effects matte, or strip the existing portrait effects matte from the flattened file data representation.
 
 @param photo
    The calling instance of AVCapturePhoto.
 @return
    An instance of AVPortraitEffectsMatte. To preserve the existing portrait effects matte, return photo.portraitEffectsMatte. To strip the existing one, return nil. To replace, provide a replacement AVPortraitEffectsMatte instance.

 @discussion
    This callback is optional. If your delegate does not implement this callback, the existing portrait effects matte in the in-memory AVCapturePhoto container will be written to the file data representation.
 */
- (nullable AVPortraitEffectsMatte *)replacementPortraitEffectsMatteForPhoto:(AVCapturePhoto *)photo;

/*!
 @method replacementSemanticSegmentationMatteOfType:forPhoto:
 @abstract
    A callback in which you may provide a replacement semantic segmentation matte of the indicated type, or strip the existing one from the flattened file data representation.
 
 @param semanticSegmentationMatteType
    The type of semantic segmentation matte to be replaced or stripped.
 @param photo
    The calling instance of AVCapturePhoto.
 @return
    An instance of AVSemanticSegmentationMatte. To preserve the existing matte, return [photo semanticSegmentationMatteForType:semanticSegmentationMatteType]. To strip the existing one, return nil. To replace, provide a replacement AVPortraitEffectsMatte instance.

 @discussion
    This callback is optional. If your delegate does not implement this callback, the existing semantic segmentation matte of the specified type in the in-memory AVCapturePhoto container will be written to the file data representation.
 */
- (nullable AVSemanticSegmentationMatte *)replacementSemanticSegmentationMatteOfType:(AVSemanticSegmentationMatteType)semanticSegmentationMatteType forPhoto:(AVCapturePhoto *)photo API_AVAILABLE(ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos);

/*!
 @method replacementAppleProRAWCompressionSettingsForPhoto:defaultSettings:maximumBitDepth:
 @abstract
	A callback in which you may provide replacement compression settings for the DNG flattened file data representation of Apple ProRAW. This callback will only be invoked for Apple ProRAW captures written to DNG.
 
 @param photo
	The calling instance of AVCapturePhoto.
 @param defaultSettings
	The default settings that will be used if not overridden.
 @param maximumBitDepth
	The maximum bit depth that can be specified with AVVideoAppleProRAWBitDepthKey in the returned settings dictionary.
 @return
	An NSDictionary containing compression settings to be used when writing the DNG file representation. Currently accepted keys are:
		AVVideoQualityKey (NSNumber in range 0 to 1.0, inclusive)
		AVVideoAppleProRAWBitDepthKey (NSNumber in range 8 to maximumBitDepth, inclusive)
	Setting AVVideoQualityKey to 1.0 will use lossless compression. Any value between 0 and 1.0 will use lossy compression with that quality.
	Setting AVVideoAppleProRAWBitDepthKey to a value less than what is given in defaultSettings may result in quantization losses.
	Any keys not specified in the returned dictionary will use the values from defaultSettings. Return defaultSettings if no changes to the compression settings are desired.

 @discussion
	This callback is optional. If your delegate does not implement this callback, the default compression settings for the file type will be used.
 */
- (NSDictionary<NSString *, id> *)replacementAppleProRAWCompressionSettingsForPhoto:(AVCapturePhoto *)photo defaultSettings:(NSDictionary<NSString *, id> *)defaultSettings maximumBitDepth:(NSInteger)maximumBitDepth API_AVAILABLE(ios(14.3), macCatalyst(14.3)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCapture/AVCapturePhotoOutput.h>
#endif
