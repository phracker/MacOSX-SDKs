/*
    File:  AVCapturePhotoOutput.h
 
    Framework:  AVFoundation
 
    Copyright 2016-2018 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVCaptureOutputBase.h>
#import <AVFoundation/AVVideoSettings.h>
#import <CoreMedia/CMSampleBuffer.h>

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
 
    Some AVCapturePhotoSettings properties are "Auto", such as autoStillImageStabilizationEnabled. When set to YES, the photo output decides at capture time whether the current scene and lighting conditions require still image stabilization. Thus the client doesn't know with certainty which features are enabled when making the capture request. With the first and each subsequent delegate callback, the client is provided an AVCaptureResolvedPhotoSettings instance that indicates the settings that were applied to the capture. All "Auto" features have now been resolved to on or off. The AVCaptureResolvedPhotoSettings object passed in the client's delegate callbacks has a uniqueID identical to the AVCapturePhotoSettings request. This uniqueID allows clients to pair unresolved and resolved settings objects. See AVCapturePhotoCaptureDelegate below for a detailed discussion of the delegate callbacks.
 
    Enabling certain photo features (Live Photo capture and high resolution capture) requires a reconfiguration of the capture render pipeline. Clients wishing to opt in for these features should call -setLivePhotoCaptureEnabled: and/or -setHighResolutionCaptureEnabled: before calling -startRunning on the AVCaptureSession. Changing any of these properties while the session is running requires a disruptive reconfiguration of the capture render pipeline. Live Photo captures in progress will be ended immediately; unfulfilled photo requests will be aborted; video preview will temporarily freeze. If you wish to capture Live Photos containing sound, you must add an audio AVCaptureDeviceInput to your AVCaptureSession.

    Simultaneous Live Photo capture and MovieFileOutput capture is not supported. If an AVCaptureMovieFileOutput is added to your session, AVCapturePhotoOutput's livePhotoCaptureSupported property returns NO. Note that simultaneous Live Photo capture and AVCaptureVideoDataOutput is supported.
 
    AVCaptureStillImageOutput and AVCapturePhotoOutput may not both be added to a capture session. You must use one or the other. If you add both to a session, a NSInvalidArgumentException is thrown.
 
    AVCapturePhotoOutput implicitly supports wide color photo capture, following the activeColorSpace of the source AVCaptureDevice. If the source device's activeColorSpace is AVCaptureColorSpace_P3_D65, photos are encoded with wide color information, unless you've specified an output format of '420v', which does not support wide color.
 */
API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED
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
        - If rawPhotoPixelFormatType is non-zero, it must be present in the receiver's -availableRawPhotoPixelFormatTypes array.
        - If rawPhotoPixelFormatType is non-zero, autoStillImageStabilizationEnabled must be set to NO.
        - If rawPhotoPixelFormatType is non-zero, your delegate must respond to -captureOutput:didFinishProcessingRawPhotoSampleBuffer:previewPhotoSampleBuffer:resolvedSettings:bracketSettings:error:.
        - If rawPhotoPixelFormatType is non-zero, highResolutionPhotoEnabled may be YES or NO, but the setting only applies to the processed image, if you've specified one.
        - If rawPhotoPixelFormatType is non-zero, the videoZoomFactor of the source device and the videoScaleAndCropFactor of the photo output's video connection must both be 1.0. Ensure no zoom is applied before requesting a RAW capture, and don't change the zoom during RAW capture.
        - If rawFileType is specified, it must be present in -availableRawPhotoFileTypes and must support the rawPhotoPixelFormatType specified using -supportedRawPhotoPixelFormatTypesForFileType:.
    Processed Format rules:
        - If format is non-nil, a kCVPixelBufferPixelFormatTypeKey or AVVideoCodecKey must be present, and both may not be present.
        - If format has a kCVPixelBufferPixelFormatTypeKey, its value must be present in the receiver's -availablePhotoPixelFormatTypes array.
        - If format has a AVVideoCodecKey, its value must be present in the receiver's -availablePhotoCodecTypes array.
        - If format is non-nil, your delegate must respond to -captureOutput:didFinishProcessingPhotoSampleBuffer:previewPhotoSampleBuffer:resolvedSettings:bracketSettings:error:.
        - If processedFileType is specified, it must be present in -availablePhotoFileTypes and must support the format's specified kCVPixelBufferPixelFormatTypeKey (using -supportedPhotoPixelFormatTypesForFileType:) or AVVideoCodecKey (using -supportedPhotoCodecTypesForFileType:).
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
    @seealso setPreparedPhotoSettingsArray:completionHandler:
    Some types of photo capture, such as bracketed captures and RAW captures, require the receiver to allocate additional buffers or prepare other resources. To prevent photo capture requests from executing slowly due to lazy resource allocation, you may call -setPreparedPhotoSettingsArray:completionHandler: with an array of settings objects representative of the types of capture you will be performing (e.g., settings for a bracketed capture, RAW capture, and/or still image stabilization capture). By default, the receiver prepares sufficient resources to capture photos with default settings, +[AVCapturePhotoSettings photoSettings].
 */
@property(nonatomic, readonly) NSArray<AVCapturePhotoSettings *> *preparedPhotoSettingsArray;

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
- (void)setPreparedPhotoSettingsArray:(NSArray<AVCapturePhotoSettings *> *)preparedPhotoSettingsArray completionHandler:(nullable void (^)(BOOL prepared, NSError * _Nullable error))completionHandler;

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
 @property availableRawPhotoPixelFormatTypes
 @abstract
    An array of Bayer RAW CVPixelBufferPixelFormatTypeKey values that are currently supported by the receiver.

 @discussion
    If you wish to capture a RAW photo, you must ensure that the Bayer RAW format you want is present in the receiver's availableRawPhotoPixelFormatTypes array. If you've not yet added your receiver to an AVCaptureSession with a video source, no RAW formats are available. This property is key-value observable. RAW capture is not supported on all platforms.
 */
@property(nonatomic, readonly) NSArray<NSNumber *> *availableRawPhotoPixelFormatTypes;

/*!
 @property availablePhotoFileTypes
 @abstract
    An array of AVFileType values that are currently supported by the receiver.

 @discussion
    If you wish to capture a photo that is formatted for a particular file container, such as HEIF, you must ensure that the fileType you desire is present in the receiver's availablePhotoFileTypes array. If you've not yet added your receiver to an AVCaptureSession with a video source, no file types are available. This property is key-value observable.
 */
@property(nonatomic, readonly) NSArray<AVFileType> *availablePhotoFileTypes API_AVAILABLE(ios(11.0));

/*!
 @property availableRawPhotoFileTypes
 @abstract
    An array of AVFileType values that are currently supported by the receiver for RAW capture.

 @discussion
    If you wish to capture a RAW photo that is formatted for a particular file container, such as DNG, you must ensure that the fileType you desire is present in the receiver's availableRawPhotoFileTypes array. If you've not yet added your receiver to an AVCaptureSession with a video source, no file types are available. This property is key-value observable.
 */
@property(nonatomic, readonly) NSArray<AVFileType> *availableRawPhotoFileTypes API_AVAILABLE(ios(11.0));

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
- (NSArray<NSNumber *> *)supportedPhotoPixelFormatTypesForFileType:(AVFileType)fileType API_AVAILABLE(ios(11.0));

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
- (NSArray<AVVideoCodecType> *)supportedPhotoCodecTypesForFileType:(AVFileType)fileType API_AVAILABLE(ios(11.0));

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
- (NSArray<NSNumber *> *)supportedRawPhotoPixelFormatTypesForFileType:(AVFileType)fileType API_AVAILABLE(ios(11.0));

/*!
 @property stillImageStabilizationSupported
 @abstract
    Indicates whether the still image stabilization feature is supported by the receiver.

 @discussion
    This property may change as the session's -sessionPreset or source device's -activeFormat change. When still image stabilization is not supported, your capture requests always resolve stillImageStabilizationEnabled to NO. This property is key-value observable.
 */
@property(nonatomic, readonly, getter=isStillImageStabilizationSupported) BOOL stillImageStabilizationSupported;

/*!
 @property isStillImageStabilizationScene
 @abstract
    Indicates whether the current scene is dark enough to warrant use of still image stabilization.

 @discussion
    This property reports whether the current scene being previewed by the camera is dark enough to benefit from still image stabilization. You can influence this property's answers by setting the photoSettingsForSceneMonitoring property, indicating whether autoStillImageStabilization monitoring should be on or off. If you set autoStillImageStabilization to NO, isStillImageStabilizationScene always reports NO. If you set it to YES, this property returns YES or NO depending on the current scene's lighting conditions. Note that some very dark scenes do not benefit from still image stabilization, but do benefit from flash. By default, this property always returns NO unless you set photoSettingsForSceneMonitoring to a non-nil value. This property may be key-value observed.
 */
@property(nonatomic, readonly) BOOL isStillImageStabilizationScene;

/*!
 @property dualCameraFusionSupported
 @abstract
    Indicates whether the DualCamera image fusion feature is supported by the receiver.

 @discussion
    This property may change as the session's -sessionPreset or source device's -activeFormat change. When using the AVCaptureDevice with deviceType AVCaptureDeviceTypeBuiltInDualCamera, the wide-angle and telephoto camera images can be fused together to improve image quality in some configurations. When DualCamera image fusion is not supported by the current configuration, your capture requests always resolve dualCameraFusionEnabled to NO. This property is key-value observable.
 */
@property(nonatomic, readonly, getter=isDualCameraFusionSupported) BOOL dualCameraFusionSupported API_AVAILABLE(ios(10.2));

/*!
 @property dualCameraDualPhotoDeliverySupported
 @abstract
    Specifies whether the photo output's current configuration supports delivery of both telephoto and wide images from the DualCamera.

 @discussion
    DualCamera dual photo delivery is only supported for certain AVCaptureSession sessionPresets and AVCaptureDevice activeFormats. When switching cameras or formats this property may change. When this property changes from YES to NO, dualCameraDualPhotoDeliveryEnabled also reverts to NO. If you've previously opted in for DualCamera dual photo delivery and then change configurations, you may need to set dualCameraDualPhotoDeliveryEnabled = YES again. This property is key-value observable.
 */
@property(nonatomic, readonly, getter=isDualCameraDualPhotoDeliverySupported) BOOL dualCameraDualPhotoDeliverySupported API_AVAILABLE(ios(11.0));

/*!
 @property dualCameraDualPhotoDeliveryEnabled
 @abstract
    Indicates whether the photo output is configured for delivery of both the telephoto and wide images from the DualCamera.

 @discussion
    Default value is NO. This property may only be set to YES if dualCameraDualPhotoDeliverySupported is YES. DualCamera dual photo delivery requires a lengthy reconfiguration of the capture render pipeline, so if you intend to do any dual photo delivery captures, you should set this property to YES before calling -[AVCaptureSession startRunning]. See also -[AVCapturePhotoSettings dualCameraDualPhotoDeliveryEnabled].
 */
@property(nonatomic, getter=isDualCameraDualPhotoDeliveryEnabled) BOOL dualCameraDualPhotoDeliveryEnabled API_AVAILABLE(ios(11.0));

/*!
 @property cameraCalibrationDataDeliverySupported
 @abstract
    Specifies whether the photo output's current configuration supports delivery of AVCameraCalibrationData in the resultant AVCapturePhoto.

 @discussion
    Camera calibration data delivery (intrinsics, extrinsics, lens distortion characteristics, etc.) is only supported in certain configurations. In iOS 11, its value is only YES if dualCameraDualPhotoDeliveryEnabled is YES. This property is key-value observable.
 */
@property(nonatomic, readonly, getter=isCameraCalibrationDataDeliverySupported) BOOL cameraCalibrationDataDeliverySupported API_AVAILABLE(ios(11.0));

/*!
 @property supportedFlashModes
 @abstract
    An array of AVCaptureFlashMode constants for the current capture session configuration.

 @discussion
    This property supersedes AVCaptureDevice's isFlashModeSupported: It returns an array of AVCaptureFlashMode constants. To test whether a particular flash mode is supported, use NSArray's containsObject API: [photoOutput.supportedFlashModes containsObject:@(AVCaptureFlashModeAuto)]. This property is key-value observable.
 */
@property(nonatomic, readonly) NSArray<NSNumber *> *supportedFlashModes;


/*!
 @property autoRedEyeReductionSupported
 @abstract
    Indicates whether the receiver supports automatic red-eye reduction for flash captures.

 @discussion
    Flash images may cause subjects' eyes to appear red, golden, or white. Automatic red-eye reduction detects and corrects for reflected light in eyes, at the cost of additional processing time per image. This property may change as the session's -sessionPreset or source device's -activeFormat change. When red-eye reduction is not supported, your capture requests always resolve redEyeReductionEnabled to NO. This property is key-value observable.
 */
@property(nonatomic, readonly, getter=isAutoRedEyeReductionSupported) BOOL autoRedEyeReductionSupported API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 @property isFlashScene
 @abstract
    Indicates whether the current scene is dark enough to warrant use of the flash.

 @discussion
    This property reports whether the current scene being previewed by the camera is dark enough to need the flash. If -supportedFlashModes only contains AVCaptureFlashModeOff, isFlashScene always reports NO. You can influence this property's answers by setting the photoSettingsForSceneMonitoring property, indicating the flashMode you wish to monitor. If you set flashMode to AVCaptureFlashModeOff, isFlashScene always reports NO. If you set it to AVCaptureFlashModeAuto or AVCaptureFlashModeOn, isFlashScene answers YES or NO based on the current scene's lighting conditions. By default, this property always returns NO unless you set photoSettingsForSceneMonitoring to a non-nil value. Note that there is some overlap in the light level ranges that benefit from still image stabilization and flash. If your photoSettingsForSceneMonitoring indicate that both still image stabilization and flash scenes should be monitored, still image stabilization takes precedence, and isFlashScene becomes YES at lower overall light levels. This property may be key-value observed.
 */
@property(nonatomic, readonly) BOOL isFlashScene;

/*!
 @property photoSettingsForSceneMonitoring
 @abstract
    Settings that govern the behavior of isFlashScene and isStillImageStabilizationScene.

 @discussion
    You can influence the return values of isFlashScene and isStillImageStabilizationScene by setting this property, indicating the flashMode and autoStillImageStabilizationEnabled values that should be considered for scene monitoring. For instance, if you set flashMode to AVCaptureFlashModeOff, isFlashScene always reports NO. If you set it to AVCaptureFlashModeAuto or AVCaptureFlashModeOn, isFlashScene answers YES or NO based on the current scene's lighting conditions. Note that there is some overlap in the light level ranges that benefit from still image stabilization and flash. If your photoSettingsForSceneMonitoring indicate that both still image stabilization and flash scenes should be monitored, still image stabilization takes precedence, and isFlashScene becomes YES at lower overall light levels. The default value for this property is nil. See isStillImageStabilizationScene and isFlashScene for further discussion.
 */
@property(nonatomic, copy, nullable) AVCapturePhotoSettings *photoSettingsForSceneMonitoring;

/*!
 @property highResolutionCaptureEnabled
 @abstract
    Indicates whether the photo render pipeline should be configured to deliver high resolution still images.

 @discussion
    Some AVCaptureDeviceFormats support outputting higher resolution stills than their streaming resolution (See AVCaptureDeviceFormat.highResolutionStillImageDimensions). Under some conditions, AVCaptureSession needs to set up the photo render pipeline differently to support high resolution still image capture. If you intend to take high resolution still images at all, you should set this property to YES before calling -[AVCaptureSession startRunning]. Once you've opted in for high resolution capture, you are free to issue photo capture requests with or without highResolutionCaptureEnabled in the AVCapturePhotoSettings. If you have not set this property to YES and call capturePhotoWithSettings:delegate: with settings.highResolutionCaptureEnabled set to YES, an NSInvalidArgumentException will be thrown.
 */
@property(nonatomic, getter=isHighResolutionCaptureEnabled) BOOL highResolutionCaptureEnabled;

/*!
 @property maxBracketedCapturePhotoCount
 @abstract
    Specifies the maximum number of photos that may be taken in a single bracket.

 @discussion
     AVCapturePhotoOutput can only satisfy a limited number of image requests in a single bracket without exhausting system resources. The maximum number of photos that may be taken in a single bracket depends on the size and format of the images being captured, and consequently may vary with AVCaptureSession -sessionPreset and AVCaptureDevice -activeFormat. Some formats do not support bracketed capture at all, and thus this property may return a value of 0. This read-only property is key-value observable. If you call -capturePhotoWithSettings:delegate: with a bracketedSettings whose count exceeds -maxBracketedCapturePhotoCount, an NSInvalidArgumentException is thrown.
 */
@property(nonatomic, readonly) NSUInteger maxBracketedCapturePhotoCount;

/*!
 @property lensStabilizationDuringBracketedCaptureSupported
 @abstract
    Indicates whether the receiver supports lens stabilization during bracketed captures.

 @discussion
    The AVCapturePhotoBracketSettings lensStabilizationEnabled property may only be set if this property returns YES. Its value may change as the session's -sessionPreset or input device's -activeFormat changes. This read-only property is key-value observable.
 */
@property(nonatomic, readonly, getter=isLensStabilizationDuringBracketedCaptureSupported) BOOL lensStabilizationDuringBracketedCaptureSupported;

/*!
 @property livePhotoCaptureSupported
 @abstract
    Indicates whether the receiver supports Live Photo capture.

 @discussion
    Live Photo capture is only supported for certain AVCaptureSession sessionPresets and AVCaptureDevice activeFormats. When switching cameras or formats this property may change. When this property changes from YES to NO, livePhotoCaptureEnabled also reverts to NO. If you've previously opted in for Live Photo capture and then change configurations, you may need to set livePhotoCaptureEnabled = YES again. 
 */
@property(nonatomic, readonly, getter=isLivePhotoCaptureSupported) BOOL livePhotoCaptureSupported;

/*!
 @property livePhotoCaptureEnabled
 @abstract
    Indicates whether the receiver is configured for Live Photo capture

 @discussion
    Default value is NO. This property may only be set to YES if livePhotoCaptureSupported is YES. Live Photo capture requires a lengthy reconfiguration of the capture render pipeline, so if you intend to do any Live Photo captures at all, you should set livePhotoCaptureEnabled to YES before calling -[AVCaptureSession startRunning].
 */
@property(nonatomic, getter=isLivePhotoCaptureEnabled) BOOL livePhotoCaptureEnabled;

/*!
 @property livePhotoCaptureSuspended
 @abstract
    Indicates whether Live Photo capture is enabled, but currently suspended.

 @discussion
    This property allows you to cut current Live Photo movie captures short (for instance, if you suddenly need to do something that you don't want to show up in the Live Photo movie, such as take a non Live Photo capture that makes a shutter sound). By default, livePhotoCaptureSuspended is NO. When you set livePhotoCaptureSuspended = YES, any Live Photo movie captures in progress are trimmed to the current time. Likewise, when you toggle livePhotoCaptureSuspended from YES to NO, subsequent Live Photo movie captures will not contain any samples earlier than the time you un-suspended Live Photo capture. Setting this property to YES throws an NSInvalidArgumentException if livePhotoCaptureEnabled is NO. This property may only be set while the session is running. Setting this property to YES when the session is not running will fail resulting in livePhotoCaptureSuspended being reverted to NO.
 */
@property(nonatomic, getter=isLivePhotoCaptureSuspended) BOOL livePhotoCaptureSuspended;

/*!
 @property livePhotoAutoTrimmingEnabled
 @abstract
    Indicates whether Live Photo movies are trimmed in real time to avoid excessive movement.

 @discussion
    This property defaults to YES when livePhotoCaptureSupported is YES. Changing this property's value while your session is running will cause a lengthy reconfiguration of the session. You should set livePhotoAutoTrimmingEnabled to YES or NO before calling -[AVCaptureSession startRunning]. When set to YES, Live Photo movies are analyzed in real time and trimmed if there's excessive movement before or after the photo is taken. Nominally, Live Photos are approximately 3 seconds long. With trimming enabled, they may be shorter, depending on movement. This feature prevents common problems such as Live Photo movies containing shoe or pocket shots.
 */
@property(nonatomic, getter=isLivePhotoAutoTrimmingEnabled) BOOL livePhotoAutoTrimmingEnabled;

/*!
 @property availableLivePhotoVideoCodecTypes
 @abstract
    An array of AVVideoCodecKey values that are currently supported by the receiver for use in the movie complement of a Live Photo.

 @discussion
    Prior to iOS 11, all Live Photo movie video tracks are compressed using H.264. Beginning in iOS 11, you can select the Live Photo movie video compression format using one of the AVVideoCodecKey strings presented in this property. The system's default (preferred) video codec is always presented first in the list. If you've not yet added your receiver to an AVCaptureSession with a video source, no codecs are available. This property is key-value observable.
 */
@property(nonatomic, readonly) NSArray<AVVideoCodecType> *availableLivePhotoVideoCodecTypes API_AVAILABLE(ios(11.0));

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
+ (nullable NSData *)JPEGPhotoDataRepresentationForJPEGSampleBuffer:(CMSampleBufferRef)JPEGSampleBuffer previewPhotoSampleBuffer:(nullable CMSampleBufferRef)previewPhotoSampleBuffer API_DEPRECATED("Use -[AVCapturePhoto fileDataRepresentation] instead.", ios(10.0, 11.0));

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
+ (nullable NSData *)DNGPhotoDataRepresentationForRawSampleBuffer:(CMSampleBufferRef)rawSampleBuffer previewPhotoSampleBuffer:(nullable CMSampleBufferRef)previewPhotoSampleBuffer API_DEPRECATED("Use -[AVCapturePhoto fileDataRepresentation] instead.", ios(10.0, 11.0));

@end


@class AVCapturePhoto;

@interface AVCapturePhotoOutput (AVCapturePhotoOutputDepthDataDeliverySupport)

/*!
 @property depthDataDeliverySupported
 @abstract
    A BOOL value specifying whether depth data delivery is supported.

 @discussion
    Some cameras and configurations support the delivery of depth data (e.g. disparity maps) along with the photo. This property returns YES if the session's current configuration allows photos to be captured with depth data, from which depth-related filters may be applied. When switching cameras or formats this property may change. When this property changes from YES to NO, depthDataDeliveryEnabled also reverts to NO. If you've previously opted in for depth data delivery and then change configurations, you may need to set depthDataDeliveryEnabled = YES again.This property is key-value observable.
 */
@property(nonatomic, readonly, getter=isDepthDataDeliverySupported) BOOL depthDataDeliverySupported API_AVAILABLE(ios(11.0));

/*!
 @property depthDataDeliveryEnabled
 @abstract
    A BOOL specifying whether the photo render pipeline is prepared for depth data delivery.

 @discussion
    Default is NO. Set to YES if you wish depth data to be delivered with your AVCapturePhotos. This property may only be set to YES if depthDataDeliverySupported is YES. Enabling depth data delivery requires a lengthy reconfiguration of the capture render pipeline, so if you intend to capture depth data, you should set this property to YES before calling -[AVCaptureSession startRunning].
 */
@property(nonatomic, getter=isDepthDataDeliveryEnabled) BOOL depthDataDeliveryEnabled API_AVAILABLE(ios(11.0));

/*!
 @property portraitEffectsMatteDeliverySupported
 @abstract
    A BOOL value specifying whether portrait effects matte delivery is supported.

 @discussion
    Some cameras and configurations support the delivery of a matting image to augment depth data and aid in high quality portrait effect rendering (see AVPortraitEffectsMatte.h). This property returns YES if the session's current configuration allows photos to be captured with a portrait effects matte. When switching cameras or formats this property may change. When this property changes from YES to NO, portraitEffectsMatteDeliveryEnabled also reverts to NO. If you've previously opted in for portrait effects matte delivery and then change configurations, you may need to set portraitEffectsMatteDeliveryEnabled = YES again.This property is key-value observable.
 */
@property(nonatomic, readonly, getter=isPortraitEffectsMatteDeliverySupported) BOOL portraitEffectsMatteDeliverySupported API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, tvos, watchos);

/*!
 @property portraitEffectsMatteDeliveryEnabled
 @abstract
    A BOOL specifying whether the photo render pipeline is prepared for portrait effects matte delivery.

 @discussion
    Default is NO. Set to YES if you wish portrait effects mattes to be delivered with your AVCapturePhotos. This property may only be set to YES if portraitEffectsMatteDeliverySupported is YES. Portrait effects matte generation requires depth to be present, so when enabling portrait effects matte delivery, you must also set depthDataDeliveryEnabled to YES. Enabling portrait effects matte delivery requires a lengthy reconfiguration of the capture render pipeline, so if you intend to capture portrait effects mattes, you should set this property to YES before calling -[AVCaptureSession startRunning].
 */
@property(nonatomic, getter=isPortraitEffectsMatteDeliveryEnabled) BOOL portraitEffectsMatteDeliveryEnabled API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, tvos, watchos);

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
API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED
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
- (void)captureOutput:(AVCapturePhotoOutput *)output didFinishProcessingPhoto:(AVCapturePhoto *)photo error:(nullable NSError *)error API_AVAILABLE(ios(11.0));

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
- (void)captureOutput:(AVCapturePhotoOutput *)output didFinishProcessingPhotoSampleBuffer:(nullable CMSampleBufferRef)photoSampleBuffer previewPhotoSampleBuffer:(nullable CMSampleBufferRef)previewPhotoSampleBuffer resolvedSettings:(AVCaptureResolvedPhotoSettings *)resolvedSettings bracketSettings:(nullable AVCaptureBracketedStillImageSettings *)bracketSettings error:(nullable NSError *)error API_DEPRECATED("Use -captureOutput:didFinishProcessingPhoto:error: instead.", ios(10.0, 11.0));

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
- (void)captureOutput:(AVCapturePhotoOutput *)output didFinishProcessingRawPhotoSampleBuffer:(nullable CMSampleBufferRef)rawSampleBuffer previewPhotoSampleBuffer:(nullable CMSampleBufferRef)previewPhotoSampleBuffer resolvedSettings:(AVCaptureResolvedPhotoSettings *)resolvedSettings bracketSettings:(nullable AVCaptureBracketedStillImageSettings *)bracketSettings error:(nullable NSError *)error API_DEPRECATED("Use -captureOutput:didFinishProcessingPhoto:error: instead.", ios(10.0, 11.0));

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
- (void)captureOutput:(AVCapturePhotoOutput *)output didFinishRecordingLivePhotoMovieForEventualFileAtURL:(NSURL *)outputFileURL resolvedSettings:(AVCaptureResolvedPhotoSettings *)resolvedSettings;

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
- (void)captureOutput:(AVCapturePhotoOutput *)output didFinishProcessingLivePhotoToMovieFileAtURL:(NSURL *)outputFileURL duration:(CMTime)duration photoDisplayTime:(CMTime)photoDisplayTime resolvedSettings:(AVCaptureResolvedPhotoSettings *)resolvedSettings error:(nullable NSError *)error;

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
API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED
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
    A default AVCapturePhotoSettings object has a format of AVVideoCodecTypeJPEG, a fileType of AVFileTypeJPEG, and autoStillImageStabilizationEnabled set to YES.
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
    A Bayer RAW pixel format OSType (defined in CVPixelBuffer.h).
 @result
    An instance of AVCapturePhotoSettings.

 @discussion
    rawPixelFormatType must be one of the OSTypes contained in AVCapturePhotoOutput's -availableRawPhotoPixelFormatTypes array. See AVCapturePhotoOutput's -capturePhotoWithSettings:delegate: inline documentation for a discussion of restrictions on AVCapturePhotoSettings when requesting RAW capture.
 */
+ (instancetype)photoSettingsWithRawPixelFormatType:(OSType)rawPixelFormatType;

/*!
 @method photoSettingsWithRawPixelFormatType:processedFormat:
 @abstract
    Creates an instance of AVCapturePhotoSettings specifying RAW + a processed format (such as JPEG).
 
 @param rawPixelFormatType
    A Bayer RAW pixel format OSType (defined in CVPixelBuffer.h).
 @param processedFormat
    A dictionary of Core Video pixel buffer attributes or AVVideoSettings, analogous to AVCaptureStillImageOutput's outputSettings property.
 @result
    An instance of AVCapturePhotoSettings.
 
 @discussion
    rawPixelFormatType must be one of the OSTypes contained in AVCapturePhotoOutput's -availableRawPhotoPixelFormatTypes array. If you wish an uncompressed processedFormat, your dictionary must contain kCVPixelBufferPixelFormatTypeKey, and the processedFormat specified must be present in AVCapturePhotoOutput's -availablePhotoPixelFormatTypes array. kCVPixelBufferPixelFormatTypeKey is the only supported key when expressing uncompressed processedFormat. If you wish a compressed format, your dictionary must contain AVVideoCodecKey and the codec specified must be present in AVCapturePhotoOutput's -availablePhotoCodecTypes array. If you are specifying a compressed format, the AVVideoCompressionPropertiesKey is also supported, with a payload dictionary containing a single AVVideoQualityKey. Passing a nil processedFormat dictionary is analogous to calling +photoSettingsWithRawPixelFormatType:. See AVCapturePhotoOutput's -capturePhotoWithSettings:delegate: inline documentation for a discussion of restrictions on AVCapturePhotoSettings when requesting RAW capture.
 */
+ (instancetype)photoSettingsWithRawPixelFormatType:(OSType)rawPixelFormatType processedFormat:(nullable NSDictionary<NSString *, id> *)processedFormat;

/*!
 @method photoSettingsWithRawPixelFormatType:processedFormat:fileType:
 @abstract
    Creates an instance of AVCapturePhotoSettings specifying RAW + a processed format (such as JPEG) and a file container to which it will be written.
 
 @param rawPixelFormatType
    A Bayer RAW pixel format OSType (defined in CVPixelBuffer.h). Pass 0 if you do not desire a RAW photo callback.
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
+ (instancetype)photoSettingsWithRawPixelFormatType:(OSType)rawPixelFormatType rawFileType:(nullable AVFileType)rawFileType processedFormat:(nullable NSDictionary<NSString *, id> *)processedFormat processedFileType:(nullable AVFileType)processedFileType API_AVAILABLE(ios(11.0));

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
    The formatting of data within a photo buffer is often dependent on the file format intended for storage. For instance, a JPEG encoded photo buffer intended for storage in a JPEG (JPEG File Interchange Format) file differs from JPEG to be stored in HEIF. The HEIF-containerized JPEG buffer is tiled for readback efficiency and partitioned into the box structure dictated by the HEIF file format. Some codecs are only supported by AVCapturePhotoOutput if containerized. For instance, the AVVideoCodecTypeHEVC is only supported with AVFileTypeHEIF formatting. To discover which photo pixel format types and video codecs are supported for a given file type, you may query AVCapturePhotoOutput's -supportedPhotoPixelFormatTypesForFileType:, or -supportedPhotoCodecTypesForFileType: respectively.
 */
@property(nullable, readonly) AVFileType processedFileType API_AVAILABLE(ios(11.0));

/*!
 @property rawPhotoPixelFormatType
 @abstract
    A Bayer RAW pixel format OSType (defined in CVPixelBuffer.h).

 @discussion
    The rawPixelFormatType you specified in one of the creation methods. Returns 0 if you did not specify RAW capture. See AVCapturePhotoOutput's -capturePhotoWithSettings:delegate: inline documentation for a discussion of restrictions on AVCapturePhotoSettings when requesting RAW capture.
 */
@property(readonly) OSType rawPhotoPixelFormatType;

/*!
 @property rawFileType
 @abstract
    The file container for which the RAW photo is formatted to be stored.

 @discussion
    The formatting of data within a RAW photo buffer may be dependent on the file format intended for storage. To discover which RAW photo pixel format types are supported for a given file type, you may query AVCapturePhotoOutput's -supportedRawPhotoPixelFormatTypesForFileType:.
 */
@property(nullable, readonly) AVFileType rawFileType API_AVAILABLE(ios(11.0));

/*!
 @property flashMode
 @abstract
    Specifies whether the flash should be on, off, or chosen automatically by AVCapturePhotoOutput.

 @discussion
    flashMode takes the place of the deprecated AVCaptureDevice -flashMode API. Setting AVCaptureDevice.flashMode has no effect on AVCapturePhotoOutput, which only pays attention to the flashMode specified in your AVCapturePhotoSettings. The default value is AVCaptureFlashModeOff. Flash modes are defined in AVCaptureDevice.h. If you specify a flashMode of AVCaptureFlashModeOn, it wins over autoStillImageStabilizationEnabled=YES. When the device becomes very hot, the flash becomes temporarily unavailable until the device cools down (see AVCaptureDevice's -flashAvailable). While the flash is unavailable, AVCapturePhotoOutput's -supportedFlashModes property still reports AVCaptureFlashModeOn and AVCaptureFlashModeAuto as being available, thus allowing you to specify a flashMode of AVCaptureModeOn. You should always check the AVCaptureResolvedPhotoSettings provided to you in the AVCapturePhotoCaptureDelegate callbacks, as the resolved flashEnabled property will tell you definitively if the flash is being used.
 */
@property(nonatomic) AVCaptureFlashMode flashMode;


/*!
 @property autoRedEyeReductionEnabled
 @abstract
    Specifies whether red-eye reduction should be applied automatically on flash captures.
 
 @discussion
    Default is YES on platforms that support automatic red-eye reduction unless you are capturing a bracket using AVCapturePhotoBracketSettings or a RAW photo without a processed photo.  For RAW photos with a processed photo the red-eye reduction will be applied to the processed photo only (RAW photos by definition are not processed). When set to YES, red-eye reduction is applied as needed for flash captures if the photo output's autoRedEyeReductionSupported property returns YES.
 */
@property(nonatomic, getter=isAutoRedEyeReductionEnabled) BOOL autoRedEyeReductionEnabled API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 @property autoStillImageStabilizationEnabled
 @abstract
    Specifies whether still image stabilization should be used automatically.

 @discussion
    Default is YES unless you are capturing a RAW photo (RAW photos may not be processed by definition) or a bracket using AVCapturePhotoBracketSettings. When set to YES, still image stabilization is applied automatically in low light to counteract hand shake. If the device has optical image stabilization, autoStillImageStabilizationEnabled makes use of lens stabilization as well.
 */
@property(nonatomic, getter=isAutoStillImageStabilizationEnabled) BOOL autoStillImageStabilizationEnabled;

/*!
 @property autoDualCameraFusionEnabled
 @abstract
    Specifies whether DualCamera image fusion should be used automatically.

 @discussion
    Default is YES unless you are capturing a RAW photo (RAW photos may not be processed by definition) or a bracket using AVCapturePhotoBracketSettings. When set to YES, and -[AVCapturePhotoOutput isDualCameraFusionSupported] is also YES, wide-angle and telephoto images may be fused to improve still image quality, depending on the current zoom factor, light levels, and focus position. You may determine whether DualCamera fusion is enabled for a particular capture request by inspecting the dualCameraFusionEnabled property of the AVCaptureResolvedPhotoSettings. Note that when using the deprecated AVCaptureStillImageOutput interface with the DualCamera, auto DualCamera fusion is always enabled and may not be turned off.
 */
@property(nonatomic, getter=isAutoDualCameraFusionEnabled) BOOL autoDualCameraFusionEnabled API_AVAILABLE(ios(10.2));

/*!
 @property dualCameraDualPhotoDeliveryEnabled
 @abstract
    Specifies whether the DualCamera should return both the telephoto and wide image.

 @discussion
    Default is NO. When set to YES, your captureOutput:didFinishProcessingPhoto:error: callback will receive twice the number of callbacks, as both the telephoto image(s) and wide-angle image(s) are delivered. You may only set this property to YES if you've set your AVCapturePhotoOutput's dualCameraDualPhotoDeliveryEnabled property to YES, and your delegate responds to the captureOutput:didFinishProcessingPhoto:error: selector.
 */
@property(nonatomic, getter=isDualCameraDualPhotoDeliveryEnabled) BOOL dualCameraDualPhotoDeliveryEnabled API_AVAILABLE(ios(11.0));

/*!
 @property highResolutionPhotoEnabled
 @abstract
    Specifies whether photos should be captured at the highest resolution supported by the source AVCaptureDevice's activeFormat.

 @discussion
    Default is NO. By default, AVCapturePhotoOutput emits images with the same dimensions as its source AVCaptureDevice's activeFormat.formatDescription. However, if you set this property to YES, the AVCapturePhotoOutput emits images at its source AVCaptureDevice's activeFormat.highResolutionStillImageDimensions. Note that if you enable video stabilization (see AVCaptureConnection's preferredVideoStabilizationMode) for any output, the high resolution photos emitted by AVCapturePhotoOutput may be smaller by 10 or more percent. You may inspect your AVCaptureResolvedPhotoSettings in the delegate callbacks to discover the exact dimensions of the capture photo(s).
 */
@property(nonatomic, getter=isHighResolutionPhotoEnabled) BOOL highResolutionPhotoEnabled;

/*!
 @property depthDataDeliveryEnabled
 @abstract
    Specifies whether AVDepthData should be captured along with the photo.

 @discussion
    Default is NO. Set to YES if you wish to receive depth data with your photo. Throws an exception if -[AVCapturePhotoOutput depthDataDeliveryEnabled] is not set to YES or your delegate does not respond to the captureOutput:didFinishProcessingPhoto:error: selector. Note that setting this property to YES may add significant processing time to the delivery of your didFinishProcessingPhoto: callback.
 
    For best rendering results in Apple's Photos.app, portrait photos should be captured with both embedded depth data and a portrait effects matte (see portraitEffectsMatteDeliveryEnabled). When supported, it is recommended to opt in for both of these auxiliary images in your photo captures involving depth.
 */
@property(nonatomic, getter=isDepthDataDeliveryEnabled) BOOL depthDataDeliveryEnabled API_AVAILABLE(ios(11.0));

/*!
 @property embedsDepthDataInPhoto
 @abstract
    Specifies whether depth data included with this photo should be written to the photo's file structure.

 @discussion
    Default is YES. When depthDataDeliveryEnabled is set to YES, this property specifies whether the included depth data should be written to the resulting photo's internal file structure. Depth data is currently only supported in HEIF and JPEG. This property is ignored if depthDataDeliveryEnabled is set to NO.
 */
@property(nonatomic) BOOL embedsDepthDataInPhoto API_AVAILABLE(ios(11.0));

/*!
 @property depthDataFiltered
 @abstract
    Specifies whether the depth data delivered with the photo should be filtered to fill invalid values.

 @discussion
    Default is YES. This property is ignored unless depthDataDeliveryEnabled is set to YES. Depth data maps may contain invalid pixel values due to a variety of factors including occlusions and low light. When depthDataFiltered is set to YES, the photo output interpolates missing data, filling in all holes.
 */
@property(nonatomic, getter=isDepthDataFiltered) BOOL depthDataFiltered API_AVAILABLE(ios(11.0));

/*!
 @property cameraCalibrationDataDeliveryEnabled
 @abstract
    Specifies whether AVCameraCalibrationData should be captured and delivered along with this photo.

 @discussion
    Default is NO. Set to YES if you wish to receive camera calibration data with your photo. Camera calibration data is delivered as a property of an AVCapturePhoto, so if you are using the CMSampleBuffer delegate callbacks rather than -captureOutput:didFinishProcessingPhoto:error:, an exception is thrown. Also, you may only set this property to YES if your AVCapturePhotoOutput's cameraCalibrationDataDeliverySupported property is YES. When requesting dual camera dual photo delivery plus camera calibration data, the wide and tele photos each contain camera calibration data for their respective camera. Note that AVCameraCalibrationData can be delivered as a property of an AVCapturePhoto or an AVDepthData, thus your delegate must respond to the captureOutput:didFinishProcessingPhoto:error: selector.
 */
@property(nonatomic, getter=isCameraCalibrationDataDeliveryEnabled) BOOL cameraCalibrationDataDeliveryEnabled API_AVAILABLE(ios(11.0));

/*!
 @property portraitEffectsMatteDeliveryEnabled
 @abstract
    Specifies whether an AVPortraitEffectsMatte should be captured along with the photo.

 @discussion
    Default is NO. Set to YES if you wish to receive a portrait effects matte with your photo. Throws an exception if -[AVCapturePhotoOutput portraitEffectsMatteDeliveryEnabled] is not set to YES or your delegate does not respond to the captureOutput:didFinishProcessingPhoto:error: selector. Portrait effects matte generation requires depth to be present, so if you wish to enable portrait effects matte delivery, you must set depthDataDeliveryEnabled to YES. Setting this property to YES does not guarantee that a portrait effects matte will be present in the resulting AVCapturePhoto. As the property name implies, the matte is primarily used to improve the rendering quality of portrait effects on the image. If the photo's content lacks a clear foreground subject, no portrait effects matte is generated, and the -[AVCapturePhoto portraitEffectsMatte] property returns nil. Note that setting this property to YES may add significant processing time to the delivery of your didFinishProcessingPhoto: callback.
 
    For best rendering results in Apple's Photos.app, portrait photos should be captured with both embedded depth data (see depthDataDeliveryEnabled) and a portrait effects matte. When supported, it is recommended to opt in for both of these auxiliary images in your photo captures involving depth.
 */
@property(nonatomic, getter=isPortraitEffectsMatteDeliveryEnabled) BOOL portraitEffectsMatteDeliveryEnabled API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, tvos, watchos);

/*!
 @property embedsPortraitEffectsMatteInPhoto
 @abstract
    Specifies whether the portrait effects matte captured with this photo should be written to the photo's file structure.

 @discussion
    Default is YES. When portraitEffectsMatteDeliveryEnabled is set to YES, this property specifies whether the included portrait effects matte should be written to the resulting photo's internal file structure. Portrait effects mattes are currently only supported in HEIF and JPEG. This property is ignored if portraitEffectsMatteDeliveryEnabled is set to NO.
 */
@property(nonatomic) BOOL embedsPortraitEffectsMatteInPhoto API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, tvos, watchos);

/*!
 @property metadata
 @abstract
    A dictionary of metadata key/value pairs you'd like to have written to each photo in the capture request.

 @discussion
    Valid metadata keys are found in <ImageIO/CGImageProperties.h>. AVCapturePhotoOutput inserts a base set of metadata into each photo it captures, such as kCGImagePropertyOrientation, kCGImagePropertyExifDictionary, and kCGImagePropertyMakerAppleDictionary. You may specify metadata keys and values that should be written to each photo in the capture request. If you've specified metadata that also appears in AVCapturePhotoOutput's base set, your value replaces the base value. An NSInvalidArgumentException is thrown if you specify keys other than those found in <ImageIO/CGImageProperties.h>.
 */
@property(nonatomic, copy) NSDictionary<NSString *, id> *metadata API_AVAILABLE(ios(11.0));

/*!
 @property livePhotoMovieFileURL
 @abstract
    Specifies that a Live Photo movie be captured to complement the still photo.

 @discussion
    A Live Photo movie is a short movie (with audio, if you've added an audio input to your session) containing the moments right before and after the still photo. A QuickTime movie file will be written to disk at the URL specified if it is a valid file URL accessible to your app's sandbox. You may only set this property if AVCapturePhotoOutput's livePhotoCaptureSupported property is YES. When you specify a Live Photo, your AVCapturePhotoCaptureDelegate object must implement -captureOutput:didFinishProcessingLivePhotoToMovieFileAtURL:duration:photoDisplayTime:resolvedSettings:error:.
 */
@property(nonatomic, copy, nullable) NSURL *livePhotoMovieFileURL;

/*!
 @property livePhotoVideoCodecType
 @abstract
    Specifies the video codec type to use when compressing video for the Live Photo movie complement.

 @discussion
    Prior to iOS 11, all Live Photo movie video tracks are compressed using H.264. Beginning in iOS 11, you can select the Live Photo movie video compression format by specifying one of the strings present in AVCapturePhotoOutput's availableLivePhotoVideoCodecTypes array.
 */
@property(nonatomic, copy) AVVideoCodecType livePhotoVideoCodecType API_AVAILABLE(ios(11.0));

/*!
 @property livePhotoMovieMetadata
 @abstract
    Movie-level metadata to be written to the Live Photo movie.

 @discussion
    An array of AVMetadataItems to be inserted into the top level of the Live Photo movie. The receiver makes immutable copies of the AVMetadataItems in the array. Live Photo movies always contain a AVMetadataQuickTimeMetadataKeyContentIdentifier which allow them to be paired with a similar identifier in the MakerNote of the photo complement. AVCapturePhotoSettings generates a unique content identifier for you. If you provide a metadata array containing an AVMetadataItem with keyspace = AVMetadataKeySpaceQuickTimeMetadata and key = AVMetadataQuickTimeMetadataKeyContentIdentifier, an NSInvalidArgumentException is thrown.
 */
@property(nonatomic, copy, null_resettable) NSArray<AVMetadataItem *> *livePhotoMovieMetadata;

/*!
 @property availablePreviewPhotoPixelFormatTypes
 @abstract
    An array of available kCVPixelBufferPixelFormatTypeKeys that may be used when specifying a previewPhotoFormat.
 
 @discussion
    The array is sorted such that the preview format requiring the fewest conversions is presented first.
 */
@property(nonatomic, readonly) NSArray<NSNumber *> *availablePreviewPhotoPixelFormatTypes;

/*!
 @property previewPhotoFormat
 @abstract
    A dictionary of Core Video pixel buffer attributes specifying the preview photo format to be delivered along with the RAW or processed photo.

 @discussion
    A dictionary of pixel buffer attributes specifying a smaller version of the RAW or processed photo for preview purposes. The kCVPixelBufferPixelFormatTypeKey is required and must be present in the receiver's -availablePreviewPhotoPixelFormatTypes array. Optional keys are { kCVPixelBufferWidthKey | kCVPixelBufferHeightKey }. If you wish to specify dimensions, you must add both width and height. Width and height are only honored up to the display dimensions. If you specify a width and height whose aspect ratio differs from the RAW or processed photo, the larger of the two dimensions is honored and aspect ratio of the RAW or processed photo is always preserved.
 */
@property(nonatomic, copy, nullable) NSDictionary<NSString *, id> *previewPhotoFormat;

/*!
 @property availableEmbeddedThumbnailPhotoCodecTypes
 @abstract
    An array of available AVVideoCodecKeys that may be used when specifying an embeddedThumbnailPhotoFormat.
 
 @discussion
    The array is sorted such that the thumbnail codec type that is most backward compatible is listed first.
 */
@property(nonatomic, readonly) NSArray<AVVideoCodecType> *availableEmbeddedThumbnailPhotoCodecTypes API_AVAILABLE(ios(11.0));

/*!
 @property embeddedThumbnailPhotoFormat
 @abstract
    A dictionary of AVVideoSettings keys specifying the thumbnail format to be written to the processed or RAW photo.

 @discussion
    A dictionary of AVVideoSettings keys specifying a thumbnail (usually smaller) version of the processed photo to be embedded in that image before calling the AVCapturePhotoCaptureDelegate. This image is sometimes referred to as a "thumbnail image". The AVVideoCodecKey is required and must be present in the receiver's -availableEmbeddedThumbnailPhotoCodecTypes array. Optional keys are { AVVideoWidthKey | AVVideoHeightKey }. If you wish to specify dimensions, you must specify both width and height. If you specify a width and height whose aspect ratio differs from the processed photo, the larger of the two dimensions is honored and aspect ratio of the RAW or processed photo is always preserved. For RAW captures, use -rawEmbeddedThumbnailPhotoFormat to specify the thumbnail format you'd like to capture in the RAW image. For apps linked on or after iOS 12, the raw thumbnail format must be specified using the -rawEmbeddedThumbnailPhotoFormat API rather than -embeddedThumbnailPhotoFormat. Beginning in iOS 12, HEIC files may contain thumbnails up to the full resolution of the main image.
 */
@property(nonatomic, copy, nullable) NSDictionary<NSString *, id> *embeddedThumbnailPhotoFormat API_AVAILABLE(ios(11.0));

/*!
 @property availableRawEmbeddedThumbnailPhotoCodecTypes
 @abstract
    An array of available AVVideoCodecKeys that may be used when specifying a rawEmbeddedThumbnailPhotoFormat.
 
 @discussion
    The array is sorted such that the thumbnail codec type that is most backward compatible is listed first.
 */
@property(nonatomic, readonly) NSArray<AVVideoCodecType> *availableRawEmbeddedThumbnailPhotoCodecTypes API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, tvos, watchos);

/*!
 @property rawEmbeddedThumbnailPhotoFormat
 @abstract
    A dictionary of AVVideoSettings keys specifying the thumbnail format to be written to the RAW photo in a RAW photo request.

 @discussion
    A dictionary of AVVideoSettings keys specifying a thumbnail (usually smaller) version of the RAW photo to be embedded in that image's DNG before calling back the AVCapturePhotoCaptureDelegate. The AVVideoCodecKey is required and must be present in the receiver's -availableRawEmbeddedThumbnailPhotoCodecTypes array. Optional keys are { AVVideoWidthKey | AVVideoHeightKey }. If you wish to specify dimensions, you must specify both width and height. If you specify a width and height whose aspect ratio differs from the RAW or processed photo, the larger of the two dimensions is honored and aspect ratio of the RAW or processed photo is always preserved. For apps linked on or after iOS 12, the raw thumbnail format must be specified using the -rawEmbeddedThumbnailPhotoFormat API rather than -embeddedThumbnailPhotoFormat. Beginning in iOS 12, DNG files may contain thumbnails up to the full resolution of the RAW image.
 */
@property(nonatomic, copy, nullable) NSDictionary<NSString *, id> *rawEmbeddedThumbnailPhotoFormat API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, tvos, watchos);

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
API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED
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
+ (instancetype)photoBracketSettingsWithRawPixelFormatType:(OSType)rawPixelFormatType rawFileType:(nullable AVFileType)rawFileType processedFormat:(nullable NSDictionary<NSString *, id> *)processedFormat processedFileType:(nullable AVFileType)processedFileType bracketedSettings:(NSArray<AVCaptureBracketedStillImageSettings *> *)bracketedSettings API_AVAILABLE(ios(11.0));

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
API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED
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
@property(readonly) CMVideoDimensions rawPhotoDimensions;

/*!
 @property previewDimensions
 @abstract
    The resolved dimensions of the preview photo buffer that will be delivered to the -captureOutput:didFinishProcessing{Photo | RawPhoto}... AVCapturePhotoCaptureDelegate callbacks.

 @discussion
    If you don't request a preview image, previewDimensions resolve to { 0, 0 }.
 */
@property(readonly) CMVideoDimensions previewDimensions;

/*!
 @property embeddedThumbnailDimensions
 @abstract
    The resolved dimensions of the embedded thumbnail that will be written to the processed photo delivered to the -captureOutput:didFinishProcessingPhoto:error: AVCapturePhotoCaptureDelegate callback.

 @discussion
    If you don't request an embedded thumbnail image, embeddedThumbnailDimensions resolve to { 0, 0 }.
 */
@property(readonly) CMVideoDimensions embeddedThumbnailDimensions API_AVAILABLE(ios(11.0));

/*!
 @property rawEmbeddedThumbnailDimensions
 @abstract
    The resolved dimensions of the embedded thumbnail that will be written to the RAW photo delivered to the -captureOutput:didFinishProcessingPhoto:error: AVCapturePhotoCaptureDelegate callback.

 @discussion
    If you don't request a raw embedded thumbnail image, rawEmbeddedThumbnailDimensions resolve to { 0, 0 }.
 */
@property(readonly) CMVideoDimensions rawEmbeddedThumbnailDimensions API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, tvos, watchos);

/*!
 @property portraitEffectsMatteDimensions
 @abstract
    The resolved dimensions of the portrait effects matte that will be delivered to the AVCapturePhoto in the -captureOutput:didFinishProcessingPhoto:error: AVCapturePhotoCaptureDelegate callback.

 @discussion
    If you request a portrait effects matte by calling -[AVCapturePhotoSettings setPortraitEffectsMatteDeliveryEnabled:YES], portraitEffectsMatteDimensions resolve to the expected dimensions of the portrait effects matte, assuming one is generated (see -[AVCapturePhotoSettings portraitEffectsMatteDeliveryEnabled] for a discussion of why a portrait effects matte might not be delivered). If you don't request a portrait effects matte, portraitEffectsMatteDimensions always resolve to { 0, 0 }.
 */
@property(readonly) CMVideoDimensions portraitEffectsMatteDimensions API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 @property livePhotoMovieDimensions
 @abstract
    The resolved dimensions of the video track in the movie that will be delivered to the -captureOutput:didFinishProcessingLivePhotoToMovieFileAtURL:duration:photoDisplayTime:resolvedSettings:error: callback.
 
 @discussion
    If you don't request Live Photo capture, livePhotoMovieDimensions resolve to { 0, 0 }.
 */
@property(readonly) CMVideoDimensions livePhotoMovieDimensions;

/*!
 @property flashEnabled
 @abstract
    Indicates whether the flash will fire when capturing the photo.

 @discussion
    When you specify AVCaptureFlashModeAuto as you AVCapturePhotoSettings.flashMode, you don't know if flash capture will be chosen until you inspect the AVCaptureResolvedPhotoSettings flashEnabled property. If the device becomes too hot, the flash becomes temporarily unavailable. You can key-value observe AVCaptureDevice's flashAvailable property to know when this occurs. If the flash is unavailable due to thermal issues, and you specify a flashMode of AVCaptureFlashModeOn, flashEnabled still resolves to NO until the device has sufficiently cooled off.
 */
@property(readonly, getter=isFlashEnabled) BOOL flashEnabled;


/*!
 @property redEyeReductionEnabled
 @abstract
    Indicates whether red-eye reduction will be applied as necessary when capturing the photo if flashEnabled is YES.
 */
@property(readonly, getter=isRedEyeReductionEnabled) BOOL redEyeReductionEnabled API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 @property stillImageStabilizationEnabled
 @abstract
    Indicates whether still image stabilization will be employed when capturing the photo.
 */
@property(readonly, getter=isStillImageStabilizationEnabled) BOOL stillImageStabilizationEnabled;

/*!
 @property dualCameraFusionEnabled
 @abstract
    Indicates whether DualCamera wide-angle and telephoto image fusion will be employed when capturing the photo.
 */
@property(readonly, getter=isDualCameraFusionEnabled) BOOL dualCameraFusionEnabled API_AVAILABLE(ios(10.2));

/*!
 @property expectedPhotoCount
 @abstract
    Indicates the number of times your -captureOutput:didFinishProcessingPhoto:error: callback will be called. For instance, if you've requested an auto exposure bracket of 3 with JPEG and RAW, the expectedPhotoCount is 6.
 */
@property(readonly) NSUInteger expectedPhotoCount API_AVAILABLE(ios(11.0));

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
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED
@interface AVCapturePhoto : NSObject
{
@private
    AVCapturePhotoInternal *_internal;
}

AV_INIT_UNAVAILABLE

/*!
 @property timestamp
 @abstract
    The time at which this image was captured, synchronized to the masterClock of the AVCaptureSession

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
@property(readonly, getter=isRawPhoto) BOOL rawPhoto;

/*!
 @property pixelBuffer
 @abstract
    For uncompressed or RAW captures, this property offers access to the pixel data.

 @discussion
    Uncompressed captures, such as '420f' or 'BGRA', or RAW captures, such as 'bgg4', present pixel data as a CVPixelBuffer. This property is analogous to CMSampleBufferGetImageBuffer(). The pixel buffer contains only the minimal attachments required for correct display. Compressed captures, such as 'jpeg', return nil.
 */
@property(nullable, readonly) CVPixelBufferRef pixelBuffer NS_RETURNS_INNER_POINTER;

/*!
 @property previewPixelBuffer
 @abstract
    This property offers access to the preview image pixel data if you've requested it.

 @discussion
    If you requested a preview image by calling -[AVCapturePhotoSettings setPreviewPhotoFormat:] with a non-nil value, this property offers access to the resulting preview image pixel data, and is analogous to CMSampleBufferGetImageBuffer(). The pixel buffer contains only the minimal attachments required for correct display. Nil is returned if you did not request a preview image.
 */
@property(nullable, readonly) CVPixelBufferRef previewPixelBuffer NS_RETURNS_INNER_POINTER;

/*!
 @property embeddedThumbnailPhotoFormat
 @abstract
    The format of the embedded thumbnail contained in this AVCapturePhoto.

 @discussion
    If you requested an embedded thumbnail image by calling -[AVCapturePhotoSettings setEmbeddedThumbnailPhotoFormat:] with a non-nil value, this property offers access to the resolved embedded thumbnail AVVideoSettings dictionary. Nil is returned if you did not request an embedded thumbnail image.
 */
@property(nullable, readonly) NSDictionary<NSString *, id> *embeddedThumbnailPhotoFormat;

/*!
 @property depthData
 @abstract
    An AVDepthData object wrapping a disparity/depth map associated with this photo.

 @discussion
    If you requested depth data delivery by calling -[AVCapturePhotoSettings setDepthDataDeliveryEnabled:YES], this property offers access to the resulting AVDepthData object. Nil is returned if you did not request depth data delivery. Note that the depth data is only embedded in the photo's internal file format container if you set -[AVCapturePhotoSettings setEmbedsDepthDataInPhoto:YES].
 */
@property(nullable, readonly) AVDepthData *depthData;

/*!
 @property portraitEffectsMatte
 @abstract
    An AVPortraitEffectsMatte object wrapping a matte associated with this photo.

 @discussion
    If you requested portrait effects matte delivery by calling -[AVCapturePhotoSettings setPortraitEffectsMatteDeliveryEnabled:YES], this property offers access to the resulting AVPortraitEffectsMatte object. Nil is returned if you did not request portrait effects matte delivery. Note that the portrait effects matte is only embedded in the photo's internal file format container if you set -[AVCapturePhotoSettings setEmbedsPortraitEffectsMatteInPhoto:YES].
 */
@property(nullable, readonly) AVPortraitEffectsMatte *portraitEffectsMatte API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, tvos, watchos);

/*!
 @property metadata
 @abstract
    An ImageIO property style dictionary of metadata associated with this photo.

 @discussion
    Valid metadata keys are found in <ImageIO/CGImageProperties.h>, such as kCGImagePropertyOrientation, kCGImagePropertyExifDictionary, kCGImagePropertyMakerAppleDictionary, etc.
 */
@property(readonly) NSDictionary<NSString *, id> *metadata;

/*!
 @property cameraCalibrationData
 @abstract
    An AVCameraCalibrationData object representing the calibration information for the camera providing the photo.

 @discussion
    Camera calibration data is only present if you call -[AVCapturePhotoSettings setCameraCalibrationDataDeliveryEnabled:YES]. When requesting dualCameraDualPhotoDeliveryEnabled plus cameraCalibrationDataDeliveryEnabled, camera calibration information is delivered with both photos. Telephoto camera calibration data is presented with the telephoto AVCapturePhoto, and wide-angle camera calibration data is presented with the wide AVCapturePhoto.
 */
@property(nullable, readonly) AVCameraCalibrationData *cameraCalibrationData;

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
    When taking a dual photo capture from the DualCamera, you may query this property to find out the source of the photo: AVCaptureDeviceTypeBuiltInWideCamera, or AVCaptureDeviceTypeBuiltInTelephotoCamera. For all other types of capture, the source device type is equal to the -[AVCaptureDevice deviceType] of the AVCaptureDevice to which the AVCapturePhotoOutput is connected. May return nil if the source of the photo is not an AVCaptureDevice.
 */
@property(nullable, readonly) AVCaptureDeviceType sourceDeviceType;

@end

@protocol AVCapturePhotoFileDataRepresentationCustomizer;

@interface AVCapturePhoto (AVCapturePhotoConversions)

/*!
 @method fileDataRepresentation
 @abstract
    Flattens the AVCapturePhoto to an NSData using the file container format (processedFileType or rawFileType) specified in the AVCapturePhotoSettings (e.g. JFIF, HEIF, DNG).
 
 @result
    An NSData containing bits in the file container's format, or nil if the flattening process fails.
 */
- (nullable NSData *)fileDataRepresentation API_AVAILABLE(ios(11.0));

/*!
 @method fileDataRepresentationWithCustomizer:
 @abstract
    Flattens the AVCapturePhoto to an NSData using the file container format (processedFileType or rawFileType) specified in the AVCapturePhotoSettings (e.g. JFIF, HEIF, DNG), and allows you to strip or replace various pieces of metadata in the process.
 
 @param customizer
    An object conforming to the AVCapturePhotoFileDataRepresentationCustomizer protocol that will be called synchronously to provide customization of metadata written to the container format. An NSInvalidArgumentException is thrown if you pass nil.
 @result
    An NSData containing bits in the file container's format, or nil if the flattening process fails.
 */
- (nullable NSData *)fileDataRepresentationWithCustomizer:(id<AVCapturePhotoFileDataRepresentationCustomizer>)customizer API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, tvos, watchos);

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
- (nullable NSData *)fileDataRepresentationWithReplacementMetadata:(nullable NSDictionary<NSString *, id> *)replacementMetadata replacementEmbeddedThumbnailPhotoFormat:(nullable NSDictionary<NSString *, id> *)replacementEmbeddedThumbnailPhotoFormat replacementEmbeddedThumbnailPixelBuffer:(nullable CVPixelBufferRef)replacementEmbeddedThumbnailPixelBuffer replacementDepthData:(nullable AVDepthData *)replacementDepthData API_DEPRECATED("Use fileDataRepresentationWithCustomizer: instead", ios(11.0, 12.0));

/*!
 @method CGImageRepresentation
 @abstract
    Utility method that converts the AVCapturePhoto's primary photo to a CGImage.
 
 @result
    A CGImageRef, or nil if the conversion process fails.
 
 @discussion
    Each time you access this method, AVCapturePhoto generates a new CGImageRef. When backed by a compressed container (such as HEIC), the CGImageRepresentation is decoded lazily as needed. When backed by an uncompressed format such as BGRA, it is copied into a separate backing buffer whose lifetime is not tied to that of the AVCapturePhoto. For a 12 megapixel image, a BGRA CGImage represents ~48 megabytes per call. If you only intend to use the CGImage for on-screen rendering, use the previewCGImageRepresentation instead. Note that the physical rotation of the CGImageRef matches that of the main image. Exif orientation has not been applied. If you wish to apply rotation when working with UIImage, you can do so by querying the photo's metadata[kCGImagePropertyOrientation] value, and passing it as the orientation parameter to +[UIImage imageWithCGImage:scale:orientation:]. RAW images always return a CGImageRepresentation of nil. If you wish to make a CGImageRef from a RAW image, use CIRAWFilter in the CoreImage framework.
 */
- (nullable CGImageRef)CGImageRepresentation API_AVAILABLE(ios(11.0));

/*!
 @method CGImageRepresentation
 @abstract
    Utility method that converts the AVCapturePhoto's preview photo to a CGImage.
 
 @result
    A CGImageRef, or nil if the conversion process fails, or if you did not request a preview photo.
 
 @discussion
    Each time you access this method, AVCapturePhoto generates a new CGImageRef. This CGImageRepresentation is a RGB rendering of the previewPixelBuffer property. If you did not request a preview photo by setting the -[AVCapturePhotoSettings previewPhotoFormat] property, this method returns nil. Note that the physical rotation of the CGImageRef matches that of the main image. Exif orientation has not been applied. If you wish to apply rotation when working with UIImage, you can do so by querying the photo's metadata[kCGImagePropertyOrientation] value, and passing it as the orientation parameter to +[UIImage imageWithCGImage:scale:orientation:].
 */
- (nullable CGImageRef)previewCGImageRepresentation API_AVAILABLE(ios(11.0));

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
} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;

@interface AVCapturePhoto (AVCapturePhotoBracketedCapture)

/*!
 @property bracketSettings
 @abstract
    The AVCaptureBracketedStillImageSettings associated with this photo.

 @discussion
    When specifying a bracketed capture using AVCapturePhotoBracketSettings, you specify an array of AVCaptureBracketedStillImageSettings -- one per image in the bracket. This property indicates the AVCaptureBracketedStillImageSettings associated with this particular photo, or nil if this photo is not part of a bracketed capture.
 */
@property(nullable, readonly) AVCaptureBracketedStillImageSettings *bracketSettings API_AVAILABLE(ios(11.0));

/*!
 @property sequenceCount
 @abstract
    1-based sequence count of the photo.

 @discussion
    If this photo is part of a bracketed capture (invoked using AVCapturePhotoBracketSettings), this property indicates the current result's count in the sequence, starting with 1 for the first result, or 0 if this photo is not part of a bracketed capture.
 */
@property(readonly) NSInteger sequenceCount API_AVAILABLE(ios(11.0));

/*!
 @property lensStabilizationStatus
 @abstract
    The status of the lens stabilization module during capture of this photo.

 @discussion
    In configurations where lens stabilization (OIS) is unsupported, AVCaptureLensStabilizationStatusUnsupported is returned. If lens stabilization is supported, but this photo is not part of a bracketed capture in which -[AVCapturePhotoBracketSettings setLensStabilizationEnabled:YES] was called, AVCaptureLensStabilizationStatusOff is returned. Otherwise a lens stabilization status is returned indicating how lens stabilization was applied during the capture.
 */
@property(readonly) AVCaptureLensStabilizationStatus lensStabilizationStatus API_AVAILABLE(ios(11.0));

@end


/*!
 @protocol AVCapturePhotoFileDataRepresentationCustomizer
 @abstract
    A set of delegate callbacks to be implemented by a client who calls AVCapturePhoto's -fileDataRepresentationWithCustomizer:.
 
 @discussion
    AVCapturePhoto is a wrapper representing a file-containerized photo in memory. If you simply wish to flatten the photo to an NSData to be written to a file, you may call -[AVCapturePhoto fileDataRepresentation]. For more complex flattening operations in which you wish to replace or strip metadata, you should call -[AVCapturePhoto fileDataRepresentationWithCustomizer:] instead, providing a delegate for customized stripping / replacing behavior. This delegate's methods are called synchronously before the flattening process commences.
 */
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, tvos, watchos) 
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

@end

NS_ASSUME_NONNULL_END
