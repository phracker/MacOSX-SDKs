/*
	File:  VTFrameProcessor_SuperResolutionScaler.h
 
	Framework:  VideoToolbox
 
	Copyright 2023-2024 Apple Inc. All rights reserved.
 
*/

#ifndef VTFRAMEPROCESSOR_SUPERRESOLUTION_H
#define VTFRAMEPROCESSOR_SUPERRESOLUTION_H

#include <CoreMedia/CMBase.h>

#if ! TARGET_OS_SIMULATOR
#ifdef __OBJC__

#import <VideoToolbox/VTFrameProcessorConfiguration.h>
#import <VideoToolbox/VTFrameProcessorParameters.h>
#import <VideoToolbox/VTFrameProcessorFrame.h>


/// Configuration value you set to prioritize quality or performance.
API_AVAILABLE(macos(26.0), ios(26.0)) API_UNAVAILABLE(tvos, visionos, watchos)
typedef NS_ENUM(NSInteger, VTSuperResolutionScalerConfigurationQualityPrioritization) {
	VTSuperResolutionScalerConfigurationQualityPrioritizationNormal = 1,
} NS_SWIFT_NAME(VTSuperResolutionScalerConfiguration.QualityPrioritization);

/// Available algorithm revisions.
///
/// A new enum case with a higher revision number is added when the processing algorithm is updated.
/// The ``VTSuperResolutionScalerConfiguration/defaultRevision`` property provides the default algorithm revision.
API_AVAILABLE(macos(26.0), ios(26.0)) API_UNAVAILABLE(tvos, visionos, watchos)
typedef NS_ENUM(NSInteger, VTSuperResolutionScalerConfigurationRevision) {
	VTSuperResolutionScalerConfigurationRevision1           = 1,    // revision 1
} NS_SWIFT_NAME(VTSuperResolutionScalerConfiguration.Revision);

/// Available super-resolution processor input types.
API_AVAILABLE(macos(26.0), ios(26.0)) API_UNAVAILABLE(tvos, visionos, watchos)
typedef NS_ENUM(NSInteger, VTSuperResolutionScalerConfigurationInputType) {
	VTSuperResolutionScalerConfigurationInputTypeVideo		= 1,
	VTSuperResolutionScalerConfigurationInputTypeImage		= 2,
} NS_SWIFT_NAME(VTSuperResolutionScalerConfiguration.InputType);

/// Available super-resolution processor model status types.
API_AVAILABLE(macos(26.0), ios(26.0)) API_UNAVAILABLE(tvos, visionos, watchos)
typedef NS_ENUM(NSInteger, VTSuperResolutionScalerConfigurationModelStatus) {
	VTSuperResolutionScalerConfigurationModelStatusDownloadRequired	= 0,
	VTSuperResolutionScalerConfigurationModelStatusDownloading		= 1,
	VTSuperResolutionScalerConfigurationModelStatusReady			= 2,
} NS_SWIFT_NAME(VTSuperResolutionScalerConfiguration.ModelStatus);

/// Indicates the order of input frames.
///
/// When submitting ``VTSuperResolutionScalerParameters`` to the processor, you need to provide one of these values based on
/// how the input frames are related to each other.
///
/// Use ``VTSuperResolutionScalerParametersSubmissionModeSequential`` to indicate that the current submission follows
/// presentation time order without jumps or skips, when compared to previous submissions. This value provides better
/// processor performance than other values.
///
/// Use ``VTSuperResolutionScalerParametersSubmissionModeRandom`` to indicate that the current submission has no relation
/// to the previous submission. Typically, this indicates a jump or skip in the frame sequence. The processor clears
/// internal caches when it receives this value in ``VTFrameProcessor/processWithParameters`` function call.
API_AVAILABLE(macos(26.0), ios(26.0)) API_UNAVAILABLE(tvos, visionos, watchos)
typedef NS_ENUM(NSInteger, VTSuperResolutionScalerParametersSubmissionMode) {
	VTSuperResolutionScalerParametersSubmissionModeRandom             = 1,    // You are submitting frames in non-sequential order.
	VTSuperResolutionScalerParametersSubmissionModeSequential         = 2,    // You are submitting frames sequentially following presentation time order.
} NS_SWIFT_NAME(VTSuperResolutionScalerParameters.SubmissionMode);


NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Configuration that you use to set up the super-resolution processor.
///
/// This configuration enables the super-resolution processor on a `VTFrameProcessor` session.
///
/// > Important: The super-resolution processor may require ML models which the framework needs to download in order to
/// operate. Before calling ``VTFrameProcessor/startSessionWithConfiguration:error:`` with an instance of this class,
/// it is important that you verify that the necessary models are present by checking ``configurationModelStatus``.
/// If models are not available, you can trigger model download using the ``downloadConfigurationModelWithCompletionHandler:``
/// method. Best practice is to confirm availability of models and drive download with user awareness and interaction
/// before engaging workflows that need this processor.
API_AVAILABLE(macos(26.0), ios(26.0)) API_UNAVAILABLE(tvos, visionos, watchos)
NS_SWIFT_SENDABLE
@interface VTSuperResolutionScalerConfiguration : NSObject <VTFrameProcessorConfiguration>

#pragma mark --- init function(s).

/// Creates a new super-resolution scaler processor configuration.
///
/// This processor increases resolution of an image or video.
/// Returns `nil` if dimensions are out of range or revision is unsupported.
///
/// - Parameters:
///   - frameWidth: Width of source frame in pixels. With ``VTSuperResolutionScalerConfigurationInputTypeVideo``,
///   maximum width is 1920 on macOS and 1440 on iOS. With ``VTSuperResolutionScalerConfigurationInputTypeImage``,
///   maximum width is 1920.
///   - frameHeight: Height of source frame in pixels. With ``VTSuperResolutionScalerConfigurationInputTypeVideo``,
///   maximum height is 1080. With ``VTSuperResolutionScalerConfigurationInputTypeImage``, maximum height is 1920 on
///   macOS and 1080 on iOS.
///   - scaleFactor: Indicates the scale factor between input and output.
///   - inputType: Indicates the type of input, either video or image.
///   - usePrecomputedFlow: Boolean value to indicate that you provide optical flow; if false, this configuration
///   computes the optical flow on the fly.
///   - qualityPrioritization: A level you use to prioritize quality or performance; for more information about
///   supported levels, see ``VTSuperResolutionScalerConfigurationQualityPrioritization``.
///   - revision: The specific algorithm or configuration revision you use to perform the request.
- (nullable instancetype)initWithFrameWidth:(NSInteger)frameWidth
								frameHeight:(NSInteger)frameHeight
								scaleFactor:(NSInteger)scaleFactor
								  inputType:(VTSuperResolutionScalerConfigurationInputType)inputType
						 usePrecomputedFlow:(BOOL)usePrecomputedFlow
					  qualityPrioritization:(VTSuperResolutionScalerConfigurationQualityPrioritization)qualityPrioritization
								   revision:(VTSuperResolutionScalerConfigurationRevision)revision;

- (instancetype) init NS_UNAVAILABLE;
+ (instancetype) new NS_UNAVAILABLE;

/// Width of source frame in pixels.
@property (nonatomic, readonly) NSInteger frameWidth;

/// Height of source frame in pixels.
@property (nonatomic, readonly) NSInteger frameHeight;

/// Indicates the type of input.
@property (nonatomic, readonly) VTSuperResolutionScalerConfigurationInputType inputType;

/// Indicates that you provide optical flow.
@property (nonatomic, readonly, getter=usesPrecomputedFlow) BOOL precomputedFlow;

/// Indicates the scale factor between input and output.
@property (nonatomic, readonly) NSInteger scaleFactor;

/// A parameter to control quality and performance levels.
///
/// For more information about supported levels, see ``VTSuperResolutionScalerConfigurationQualityPrioritization``.
@property (nonatomic, readonly) VTSuperResolutionScalerConfigurationQualityPrioritization qualityPrioritization;

/// The specific algorithm or configuration revision you use to perform the request.
@property (nonatomic, readonly) VTSuperResolutionScalerConfigurationRevision revision;

/// Provides the collection of currently supported algorithms or configuration revisions for the class of configuration.
///
/// A property you use to introspect at runtime which revisions are available for each configuration.
@property (class, nonatomic, readonly) NSIndexSet* supportedRevisions;

/// Provides the default revision of a specific algorithm or configuration.
@property (class, nonatomic, readonly) VTSuperResolutionScalerConfigurationRevision defaultRevision;

/// Available supported pixel formats for source frames for current configuration.
@property (nonatomic, readonly) NSArray<NSNumber *> * frameSupportedPixelFormats NS_REFINED_FOR_SWIFT;

/// Pixel buffer attributes dictionary that describes requirements for pixel buffers which represent source frames and reference frames.
///
/// Use ``CVPixelBufferCreateResolvedAttributesDictionary`` to combine this dictionary with your pixel buffer attributes dictionary.
@property (nonatomic, readonly) NSDictionary<NSString *, id> * NS_SWIFT_SENDABLE sourcePixelBufferAttributes;

/// Pixel buffer attributes dictionary that describes requirements for pixel buffers which represent destination frames.
///
/// Use ``CVPixelBufferCreateResolvedAttributesDictionary`` to combine this dictionary with your pixel buffer attributes dictionary.
@property (nonatomic, readonly) NSDictionary<NSString *, id> * NS_SWIFT_SENDABLE destinationPixelBufferAttributes;

/// Reports the download status of models that the system needs for the current configuration.
@property (nonatomic, readonly) VTSuperResolutionScalerConfigurationModelStatus configurationModelStatus;

/// Downloads models that the system needs for the current configuration.
///
/// This method downloads model assets required for the current configuration in background. You should call this method
/// if ``configurationModelStatus`` is ``VTSuperResolutionScalerConfigurationModelStatusDownloadRequired``. After this
/// method is called, you can query ``configurationModelPercentageAvailable`` to determine progress of model asset
/// download process. If the download fails, the completion handler is invoked with an `NSError`, and the
/// ``configurationModelStatus`` goes back to ``VTSuperResolutionScalerConfigurationModelStatusDownloadRequired``. If
/// the download succeeds, the completion handler is invoked with `nil` NSError.
- (void)downloadConfigurationModelWithCompletionHandler:(void (^)(NSError * _Nullable error))completionHandler;

/// Returns a floating point value between 0.0 and 1.0 indicating the percentage of required model assets that have been downloaded.
@property (nonatomic, readonly) float configurationModelPercentageAvailable;

/// Reports whether the system supports this processor.
@property (class, nonatomic, readonly, getter=isSupported) BOOL supported;

/// Reports the set of supported scale factors to use when initializing a super-resolution scaler configuration.
@property (class, nonatomic, readonly) NSArray<NSNumber*> * supportedScaleFactors NS_REFINED_FOR_SWIFT;

@end

/// An object that contains both input and output parameters that the super-resolution processor needs to run on a frame.
///
/// Use this object in the `processWithParameters` call of the `VTFrameProcessor` class. The output parameter for this class is `destinationFrame`, where the processor returns the output frame (as `VTFrameProcessorFrame`) back to you once `processWithParameters` completes.
///
/// `VTSuperResolutionScalerParameters` are frame-level parameters.
API_AVAILABLE(macos(26.0), ios(26.0)) API_UNAVAILABLE(tvos, visionos, watchos)
@interface VTSuperResolutionScalerParameters : NSObject <VTFrameProcessorParameters>

/// Creates a new super-resolution scaler parameters instance.
///
/// Returns `nil` if `sourceFrame` or `destinationFrame` is `nil`, or if `sourceFrame` and reference frames have different pixel formats.
///
/// - Parameters:
///   - sourceFrame: Current source frame; must be non `nil`.
///   - previousFrame: The previous source frame in presentation time order. For the first frame you can set this to `nil`.
///   - previousOutputFrame: The previous output frame in presentation time order. For the first frame you can set this to `nil`.
///   - opticalFlow: Optional `VTFrameProcessorOpticalFlow` object that contains forward and backward optical flow between the `sourceFrame` and `previousFrame`. You only need this if optical flow is pre-computed.
///   - submissionMode: Provides a hint to let the processor know whether you are submitting frames in presentation
///   sequence. For more information about supported modes see ``VTSuperResolutionScalerParametersSubmissionMode``.
///   - destinationFrame: User-allocated pixel buffer that receives the results.
- (nullable instancetype) initWithSourceFrame:(VTFrameProcessorFrame *)sourceFrame
								previousFrame:(VTFrameProcessorFrame * _Nullable)previousFrame
						  previousOutputFrame:(VTFrameProcessorFrame * _Nullable)previousOutputFrame
								  opticalFlow:(VTFrameProcessorOpticalFlow * _Nullable)opticalFlow
							   submissionMode:(VTSuperResolutionScalerParametersSubmissionMode)submissionMode
							 destinationFrame:(VTFrameProcessorFrame *)destinationFrame;

- (instancetype) init NS_UNAVAILABLE;
+ (instancetype) new NS_UNAVAILABLE;

/// Current source frame, which must be non `nil`.
@property(nonatomic, readonly) VTFrameProcessorFrame * sourceFrame;

/// Previous source frame in presentation time order, which is `nil` for the first frame.
@property(nonatomic, readonly, nullable) VTFrameProcessorFrame * previousFrame;

/// Previous output frame in presentation time order, which is `nil` for the first frame.
@property(nonatomic, readonly, nullable) VTFrameProcessorFrame * previousOutputFrame;

/// Optional object that contains forward and backward optical flow with the previous frame.
///
/// You only need this if optical flow is pre-computed. For the first frame this is `nil`.
@property(nonatomic, readonly, nullable) VTFrameProcessorOpticalFlow * opticalFlow;

/// Ordering of the input frames in this submission relative to the previous submission.
@property (nonatomic, readonly) VTSuperResolutionScalerParametersSubmissionMode submissionMode;

/// Destination frame that contains user-allocated pixel buffer that receives the results.
@property(nonatomic, readonly) VTFrameProcessorFrame * destinationFrame;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#endif // __OBJC__
#endif // ! TARGET_OS_SIMULATOR

#endif // VTFRAMEPROCESSOR_SUPERRESOLUTION_H
