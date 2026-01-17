#if !__has_include(<AVFCapture/AVCaptureStillImageOutput.h>)
/*
    File:  AVCaptureStillImageOutput.h
 
    Framework:  AVFoundation
 
    Copyright 2010-2017 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVCaptureOutputBase.h>
#import <AVFoundation/AVVideoSettings.h>
#import <CoreMedia/CMSampleBuffer.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark AVCaptureStillImageOutput

@class AVCaptureStillImageOutputInternal;

/*!
 @class AVCaptureStillImageOutput
 @abstract
    AVCaptureStillImageOutput is a concrete subclass of AVCaptureOutput that can be used to capture high-quality still images with accompanying metadata.
 
 @discussion
    Instances of AVCaptureStillImageOutput can be used to capture, on demand, high quality snapshots from a realtime capture source. Clients can request a still image for the current time using the captureStillImageAsynchronouslyFromConnection:completionHandler: method. Clients can also configure still image outputs to produce still images in specific image formats.
 */
API_DEPRECATED("Use AVCapturePhotoOutput instead.", macos(10.7, 10.15), ios(4.0, 10.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface AVCaptureStillImageOutput : AVCaptureOutput
{
@private
    AVCaptureStillImageOutputInternal *_internal;
}

- (instancetype)init;

+ (instancetype)new;

/*!
 @property outputSettings
 @abstract
    Specifies the options the receiver uses to encode still images before they are delivered.
 
 @discussion
    See AVVideoSettings.h for more information on how to construct an output settings dictionary.
 
    On iOS, the only currently supported keys are AVVideoCodecKey and kCVPixelBufferPixelFormatTypeKey. Use -availableImageDataCVPixelFormatTypes and -availableImageDataCodecTypes to determine what codec keys and pixel formats are supported. AVVideoQualityKey is supported on iOS 6.0 and later and may only be used when AVVideoCodecKey is set to AVVideoCodecTypeJPEG.
 */
@property(nonatomic, copy) NSDictionary<NSString *, id> *outputSettings;

/*!
 @property availableImageDataCVPixelFormatTypes
 @abstract
    Indicates the supported image pixel formats that can be specified in outputSettings.
 
 @discussion
    The value of this property is an NSArray of NSNumbers that can be used as values for the kCVPixelBufferPixelFormatTypeKey in the receiver's outputSettings property. The first format in the returned list is the most efficient output format.
 */
@property(nonatomic, readonly) NSArray<NSNumber *> *availableImageDataCVPixelFormatTypes;

/*!
 @property availableImageDataCodecTypes
 @abstract
    Indicates the supported image codec formats that can be specified in outputSettings.
 
 @discussion
    The value of this property is an NSArray of AVVideoCodecTypes that can be used as values for the AVVideoCodecKey in the receiver's outputSettings property.
 */
@property(nonatomic, readonly) NSArray<AVVideoCodecType> *availableImageDataCodecTypes;

/*!
 @property stillImageStabilizationSupported
 @abstract
    Indicates whether the receiver supports still image stabilization.
 
 @discussion
    The receiver's automaticallyEnablesStillImageStabilizationWhenAvailable property can only be set if this property returns YES. Its value may change as the session's -sessionPreset or input device's -activeFormat changes.
 */
@property(nonatomic, readonly, getter=isStillImageStabilizationSupported) BOOL stillImageStabilizationSupported API_AVAILABLE(ios(7.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 @property automaticallyEnablesStillImageStabilizationWhenAvailable
 @abstract
    Indicates whether the receiver should automatically use still image stabilization when necessary.
 
 @discussion
    On a receiver where -isStillImageStabilizationSupported returns YES, image stabilization may be applied to reduce blur commonly found in low light photos. When stabilization is enabled, still image captures incur additional latency. The default value is YES when supported, NO otherwise. Setting this property throws an NSInvalidArgumentException if -isStillImageStabilizationSupported returns NO.
 */
@property(nonatomic) BOOL automaticallyEnablesStillImageStabilizationWhenAvailable API_AVAILABLE(ios(7.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 @property stillImageStabilizationActive
 @abstract
    Indicates whether still image stabilization is in use for the current capture.
 
 @discussion
    On a receiver where -isStillImageStabilizationSupported returns YES, and automaticallyEnablesStillImageStabilizationWhenAvailable is set to YES, this property may be key-value observed, or queried from inside your key-value observation callback for the @"capturingStillImage" property, to find out if still image stabilization is being applied to the current capture.
 */
@property(nonatomic, readonly, getter=isStillImageStabilizationActive) BOOL stillImageStabilizationActive API_AVAILABLE(ios(7.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 @property highResolutionStillImageOutputEnabled
 @abstract
    Indicates whether the receiver should emit still images at the highest resolution supported by its source AVCaptureDevice's activeFormat.
 
 @discussion
    By default, AVCaptureStillImageOutput emits images with the same dimensions as its source AVCaptureDevice's activeFormat.formatDescription. However, if you set this property to YES, the receiver emits still images at its source AVCaptureDevice's activeFormat.highResolutionStillImageDimensions. Note that if you enable video stabilization (see AVCaptureConnection's preferredVideoStabilizationMode) for any output, the high resolution still images emitted by AVCaptureStillImageOutput may be smaller by 10 or more percent.
 */
@property(nonatomic, getter=isHighResolutionStillImageOutputEnabled) BOOL highResolutionStillImageOutputEnabled API_AVAILABLE(macos(10.14), ios(8.0), macCatalyst(14.0));

/*!
 @property capturingStillImage
 @abstract
    A boolean value that becomes true when a still image is being captured.
 
 @discussion
    The value of this property is a BOOL that becomes true when a still image is being captured, and false when no still image capture is underway. This property is key-value observable.
 */
@property(readonly, getter=isCapturingStillImage) BOOL capturingStillImage API_AVAILABLE(macos(10.8), ios(5.0), macCatalyst(14.0));

/*!
 @method captureStillImageAsynchronouslyFromConnection:completionHandler:
 @abstract
    Initiates an asynchronous still image capture, returning the result to a completion handler.
 
 @param connection
    The AVCaptureConnection object from which to capture the still image.
 @param handler
    A block that will be called when the still image capture is complete. The block will be passed a CMSampleBuffer object containing the image data or an NSError object if an image could not be captured.
 
 @discussion
    This method will return immediately after it is invoked, later calling the provided completion handler block when image data is ready. If the request could not be completed, the error parameter will contain an NSError object describing the failure.
 
    Attachments to the image data sample buffer may contain metadata appropriate to the image data format. For instance, a sample buffer containing JPEG data may carry a kCGImagePropertyExifDictionary as an attachment. See <ImageIO/CGImageProperties.h> for a list of keys and value types.
 
    Clients should not assume that the completion handler will be called on a specific thread.
 
    Calls to captureStillImageAsynchronouslyFromConnection:completionHandler: are not synchronized with AVCaptureDevice manual control completion handlers. Setting a device manual control, waiting for its completion, then calling captureStillImageAsynchronouslyFromConnection:completionHandler: DOES NOT ensure that the still image returned reflects your manual control change. It may be from an earlier time. You can compare your manual control completion handler sync time to the returned still image's presentation time. You can retrieve the sample buffer's pts using CMSampleBufferGetPresentationTimestamp(). If the still image has an earlier timestamp, your manual control command does not apply to it.
 */
- (void)captureStillImageAsynchronouslyFromConnection:(AVCaptureConnection *)connection completionHandler:(void (^)(CMSampleBufferRef _Nullable imageDataSampleBuffer, NSError * _Nullable error))handler;

/*!
 @method jpegStillImageNSDataRepresentation:
 @abstract
    Converts the still image data and metadata attachments in a JPEG sample buffer to an NSData representation.
 
 @param jpegSampleBuffer
    The sample buffer carrying JPEG image data, optionally with Exif metadata sample buffer attachments. This method throws an NSInvalidArgumentException if jpegSampleBuffer is NULL or not in the JPEG format.
 
 @discussion
    This method returns an NSData representation of a JPEG still image sample buffer, merging the image data and Exif metadata sample buffer attachments without recompressing the image. The returned NSData is suitable for writing to disk.
 */
+ (nullable NSData *)jpegStillImageNSDataRepresentation:(CMSampleBufferRef)jpegSampleBuffer;

@end


#pragma mark - AVCaptureBracketedStillImageSettings

/*!
 @class AVCaptureBracketedStillImageSettings
 @abstract
    AVCaptureBracketedStillImageSettings is an abstract base class that defines an interface for settings pertaining to a bracketed capture.
 
 @discussion
    AVCaptureBracketedStillImageSettings may not be instantiated directly.
 */
API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED
@interface AVCaptureBracketedStillImageSettings : NSObject

AV_INIT_UNAVAILABLE

@end


#pragma mark - AVCaptureManualExposureBracketedStillImageSettings

/*!
 @class AVCaptureManualExposureBracketedStillImageSettings
 @abstract
    AVCaptureManualExposureBracketedStillImageSettings is a concrete subclass of AVCaptureBracketedStillImageSettings to be used when bracketing exposure duration and ISO.
 
 @discussion
    An AVCaptureManualExposureBracketedStillImageSettings instance defines the exposure duration and ISO settings that should be applied to one image in a bracket. An array of settings objects is passed to -[AVCaptureStillImageOutput captureStillImageBracketAsynchronouslyFromConnection:withSettingsArray:completionHandler:]. Min and max duration and ISO values are queryable properties of the AVCaptureDevice supplying data to an AVCaptureStillImageOutput instance. If you wish to leave exposureDuration unchanged for this bracketed still image, you may pass the special value AVCaptureExposureDurationCurrent. To keep ISO unchanged, you may pass AVCaptureISOCurrent (see AVCaptureDevice.h).
 */
API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED
@interface AVCaptureManualExposureBracketedStillImageSettings : AVCaptureBracketedStillImageSettings

/*!
 @method manualExposureSettingsWithExposureDuration:ISO:
 @abstract
    Creates an AVCaptureManualExposureBracketedStillImageSettings using the specified exposure duration and ISO.
 
 @param duration
    The exposure duration in seconds. Pass AVCaptureExposureDurationCurrent to leave the duration unchanged for this bracketed image.
 @param ISO
    The ISO. Pass AVCaptureISOCurrent to leave the ISO unchanged for this bracketed image.
 @result
    An initialized AVCaptureManualExposureBracketedStillImageSettings instance.
 */
+ (instancetype)manualExposureSettingsWithExposureDuration:(CMTime)duration ISO:(float)ISO;

/*!
 @property exposureDuration
 @abstract
    The exposure duration for the still image.
 */
@property(readonly) CMTime exposureDuration;

/*!
 @property ISO
 @abstract
    The ISO for the still image.
 */
@property(readonly) float ISO;

@end


#pragma mark - AVCaptureAutoExposureBracketedStillImageSettings

/*!
 @class AVCaptureAutoExposureBracketedStillImageSettings
 @abstract
    AVCaptureAutoExposureBracketedStillImageSettings is a concrete subclass of AVCaptureBracketedStillImageSettings to be used when bracketing exposure target bias.
 
 @discussion
    An AVCaptureAutoExposureBracketedStillImageSettings instance defines the exposure target bias setting that should be applied to one image in a bracket. An array of settings objects is passed to -[AVCaptureStillImageOutput captureStillImageBracketAsynchronouslyFromConnection:withSettingsArray:completionHandler:]. Min and max exposure target bias are queryable properties of the AVCaptureDevice supplying data to an AVCaptureStillImageOutput instance. If you wish to leave exposureTargetBias unchanged for this bracketed still image, you may pass the special value AVCaptureExposureTargetBiasCurrent (see AVCaptureDevice.h).
 */
API_AVAILABLE(ios(8.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED
@interface AVCaptureAutoExposureBracketedStillImageSettings : AVCaptureBracketedStillImageSettings

/*!
 @method autoExposureSettingsWithExposureTargetBias
 @abstract
     Creates an AVCaptureAutoExposureBracketedStillImageSettings using the specified exposure target bias.
 
 @param exposureTargetBias
     The exposure target bias. Pass AVCaptureExposureTargetBiasCurrent to leave the exposureTargetBias unchanged for this image.
 @result
     An initialized AVCaptureAutoExposureBracketedStillImageSettings instance.
 */
+ (instancetype)autoExposureSettingsWithExposureTargetBias:(float)exposureTargetBias;

/*!
 @property exposureTargetBias
 @abstract
     The exposure bias for the auto exposure bracketed settings
 */
@property(readonly) float exposureTargetBias;

@end


/*!
 @category AVCaptureStillImageOutput (AVCaptureStillImageOutputBracketedCapture)
 @abstract
    A category of methods for bracketed still image capture.
 
 @discussion
    A "still image bracket" is a batch of images taken as quickly as possible in succession, optionally with different settings from picture to picture.
 
    In a bracketed capture, AVCaptureDevice flashMode property is ignored (flash is forced off), as is AVCaptureStillImageOutput's automaticallyEnablesStillImageStabilizationWhenAvailable property (stabilization is forced off).
 */
@interface AVCaptureStillImageOutput (AVCaptureStillImageOutputBracketedCapture)

/*!
 @property maxBracketedCaptureStillImageCount
 @abstract
    Specifies the maximum number of still images that may be taken in a single bracket.
 
 @discussion
    AVCaptureStillImageOutput can only satisfy a limited number of image requests in a single bracket without exhausting system resources. The maximum number of still images that may be taken in a single bracket depends on the size of the images being captured, and consequently may vary with AVCaptureSession -sessionPreset and AVCaptureDevice -activeFormat. Some formats do not support bracketed capture and return a maxBracketedCaptureStillImageCount of 0. This read-only property is key-value observable. If you exceed -maxBracketedCaptureStillImageCount, then -captureStillImageBracketAsynchronouslyFromConnection:withSettingsArray:completionHandler: fails and the completionHandler is called [settings count] times with a NULL sample buffer and AVErrorMaximumStillImageCaptureRequestsExceeded.
 */
@property(nonatomic, readonly) NSUInteger maxBracketedCaptureStillImageCount API_DEPRECATED("Use AVCapturePhotoOutput maxBracketedCapturePhotoCount instead.", ios(8.0, 10.0)) API_UNAVAILABLE(macos);

/*!
 @property lensStabilizationDuringBracketedCaptureSupported
 @abstract
    Indicates whether the receiver supports lens stabilization during bracketed captures.
 
 @discussion
    The receiver's lensStabilizationDuringBracketedCaptureEnabled property can only be set if this property returns YES. Its value may change as the session's -sessionPreset or input device's -activeFormat changes. This read-only property is key-value observable.
 */
@property(nonatomic, readonly, getter=isLensStabilizationDuringBracketedCaptureSupported) BOOL lensStabilizationDuringBracketedCaptureSupported API_DEPRECATED("Use AVCapturePhotoOutput lensStabilizationDuringBracketedCaptureSupported instead.", ios(9.0, 10.0)) API_UNAVAILABLE(macos);

/*!
 @property lensStabilizationDuringBracketedCaptureEnabled
 @abstract
    Indicates whether the receiver should use lens stabilization during bracketed captures.
 
 @discussion
    On a receiver where -isLensStabilizationDuringBracketedCaptureSupported returns YES, lens stabilization may be applied to the bracket to reduce blur commonly found in low light photos. When lens stabilization is enabled, bracketed still image captures incur additional latency. Lens stabilization is more effective with longer-exposure captures, and offers limited or no benefit for exposure durations shorter than 1/30 of a second. It is possible that during the bracket, the lens stabilization module may run out of correction range and therefore will not be active for every frame in the bracket. Each emitted CMSampleBuffer from the bracket will have an attachment of kCMSampleBufferAttachmentKey_StillImageLensStabilizationInfo indicating additional information about stabilization was applied to the buffer, if any. The default value of -isLensStabilizationDuringBracketedCaptureEnabled is NO. This value will be set to NO when -isLensStabilizationDuringBracketedCaptureSupported changes to NO. Setting this property throws an NSInvalidArgumentException if -isLensStabilizationDuringBracketedCaptureSupported returns NO. This property is key-value observable.
 */
@property(nonatomic, getter=isLensStabilizationDuringBracketedCaptureEnabled) BOOL lensStabilizationDuringBracketedCaptureEnabled API_DEPRECATED("Use AVCapturePhotoOutput with AVCapturePhotoBracketSettings instead.", ios(9.0, 10.0)) API_UNAVAILABLE(macos);

/*!
 @method prepareToCaptureStillImageBracketFromConnection:withSettingsArray:completionHandler:
 @abstract
    Allows the receiver to prepare resources in advance of capturing a still image bracket.
 
 @param connection
    The connection through which the still image bracket should be captured.
 @param settings
    An array of AVCaptureBracketedStillImageSettings objects. All must be of the same kind of AVCaptureBracketedStillImageSettings subclass, or an NSInvalidArgumentException is thrown.
 @param handler
    A user provided block that will be called asynchronously once resources have successfully been allocated for the specified bracketed capture operation. If sufficient resources could not be allocated, the "prepared" parameter contains NO, and "error" parameter contains a non-nil error value. If [settings count] exceeds -maxBracketedCaptureStillImageCount, then AVErrorMaximumStillImageCaptureRequestsExceeded is returned. You should not assume that the completion handler will be called on a specific thread.
 
 @discussion
    -maxBracketedCaptureStillImageCount tells you the maximum number of images that may be taken in a single bracket given the current AVCaptureDevice/AVCaptureSession/AVCaptureStillImageOutput configuration. But before taking a still image bracket, additional resources may need to be allocated. By calling -prepareToCaptureStillImageBracketFromConnection:withSettingsArray:completionHandler: first, you are able to deterministically know when the receiver is ready to capture the bracket with the specified settings array.
 */
- (void)prepareToCaptureStillImageBracketFromConnection:(AVCaptureConnection *)connection withSettingsArray:(NSArray<__kindof AVCaptureBracketedStillImageSettings *> *)settings completionHandler:(void (^)(BOOL prepared, NSError * _Nullable error))handler API_DEPRECATED("Use AVCapturePhotoOutput setPreparedPhotoSettingsArray:completionHandler: instead.", ios(8.0, 10.0)) API_UNAVAILABLE(macos);

/*!
 @method captureStillImageBracketAsynchronouslyFromConnection:withSettingsArray:completionHandler:
 @abstract
    Captures a still image bracket.
 
 @param connection
    The connection through which the still image bracket should be captured.
 @param settings
    An array of AVCaptureBracketedStillImageSettings objects. All must be of the same kind of AVCaptureBracketedStillImageSettings subclass, or an NSInvalidArgumentException is thrown.
 @param handler
    A user provided block that will be called asynchronously as each still image in the bracket is captured. If the capture request is successful, the "sampleBuffer" parameter contains a valid CMSampleBuffer, the "stillImageSettings" parameter contains the settings object corresponding to this still image, and a nil "error" parameter. If the bracketed capture fails, sample buffer is NULL and error is non-nil. If [settings count] exceeds -maxBracketedCaptureStillImageCount, then AVErrorMaximumStillImageCaptureRequestsExceeded is returned. You should not assume that the completion handler will be called on a specific thread.
 
 @discussion
    If you have not called -prepareToCaptureStillImageBracketFromConnection:withSettingsArray:completionHandler: for this still image bracket request, the bracket may not be taken immediately, as the receiver may internally need to prepare resources.
 */
- (void)captureStillImageBracketAsynchronouslyFromConnection:(AVCaptureConnection *)connection withSettingsArray:(NSArray<__kindof AVCaptureBracketedStillImageSettings *> *)settings completionHandler:(void (^)(CMSampleBufferRef _Nullable sampleBuffer, AVCaptureBracketedStillImageSettings * _Nullable stillImageSettings, NSError * _Nullable error))handler API_DEPRECATED("Use AVCapturePhotoOutput capturePhotoWithSettings:delegate: instead.", ios(8.0, 10.0)) API_UNAVAILABLE(macos);

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCapture/AVCaptureStillImageOutput.h>
#endif
