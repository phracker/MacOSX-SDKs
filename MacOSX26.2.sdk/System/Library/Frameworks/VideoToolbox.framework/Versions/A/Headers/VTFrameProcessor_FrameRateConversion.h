/*
	File:  VTFrameProcessor_FrameRateConversion.h
 
	Framework:  VideoToolbox
 
	Copyright 2023-2024 Apple Inc. All rights reserved.
 
*/

#ifndef VTFRAMEPROCESSOR_FRAMERATECONVERSION_H
#define VTFRAMEPROCESSOR_FRAMERATECONVERSION_H

#include <CoreMedia/CMBase.h>

#if ! TARGET_OS_SIMULATOR
#ifdef __OBJC__

#import <VideoToolbox/VTFrameProcessorConfiguration.h>
#import <VideoToolbox/VTFrameProcessorParameters.h>
#import <VideoToolbox/VTFrameProcessorFrame.h>

/// Configuration value you set to prioritize quality or performance.
API_AVAILABLE(macos(15.4), ios(26.0)) API_UNAVAILABLE(tvos, visionos, watchos)
typedef NS_ENUM(NSInteger, VTFrameRateConversionConfigurationQualityPrioritization) {
	VTFrameRateConversionConfigurationQualityPrioritizationNormal = 1,
	VTFrameRateConversionConfigurationQualityPrioritizationQuality = 2,
} NS_SWIFT_NAME(VTFrameRateConversionConfiguration.QualityPrioritization);

/// Available algorithm revisions.
///
/// A new enum case with higher revision number is added when the processing algorithm is updated.
/// The ``VTFrameRateConversionConfiguration/defaultRevision`` property provides the default algorithm revision.
API_AVAILABLE(macos(15.4), ios(26.0)) API_UNAVAILABLE(tvos, visionos, watchos)
typedef NS_ENUM(NSInteger, VTFrameRateConversionConfigurationRevision) {
	VTFrameRateConversionConfigurationRevision1           = 1,    // revision 1
} NS_SWIFT_NAME(VTFrameRateConversionConfiguration.Revision);

/// Indicates the order of input frames.
///
/// When submitting ``VTFrameRateConversionParameters`` to the processor, you need to provide one of these values based on
/// how the input frames are related to each other.
///
/// Use ``VTFrameRateConversionParametersSubmissionModeSequential`` to indicate that the current submission follows
/// presentation time order without jump or skip, when compared to previous submissions. This value provides better
/// processor performance than other values.
///
/// Use ``VTFrameRateConversionParametersSubmissionModeRandom`` to indicate that the current submission has no relation
/// to the previous submission. Typically, this indicates a jump or a skip in the frame sequence. The processor clears
/// internal caches when it receives this value in ``VTFrameProcessor/processWithParameters`` function call.
///
/// Use ``VTFrameRateConversionParametersSubmissionModeSequentialReferencesUnchanged`` to indicate that the frames are
/// in sequential order however, the reference frames are unchanged.
API_AVAILABLE(macos(15.4), ios(26.0)) API_UNAVAILABLE(tvos, visionos, watchos)
typedef NS_ENUM(NSInteger, VTFrameRateConversionParametersSubmissionMode) {
	/// You are submitting frames in non-sequential order.
	VTFrameRateConversionParametersSubmissionModeRandom							= 1,
	/// You are submitting frames sequentially following presentation time order.
	VTFrameRateConversionParametersSubmissionModeSequential						= 2,
	/// You are submitting frames sequentially.
	///
	/// This processing request uses the same source and next reference frames as the previous submission.
	VTFrameRateConversionParametersSubmissionModeSequentialReferencesUnchanged	= 3,
} NS_SWIFT_NAME(VTFrameRateConversionParameters.SubmissionMode);


NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Configuration that you use to set up the frame rate conversion processor.
///
/// This configuration enables the frame-rate conversion on a `VTFrameProcessor` session.
API_AVAILABLE(macos(15.4), ios(26.0)) API_UNAVAILABLE(tvos, visionos, watchos)
NS_SWIFT_SENDABLE
@interface VTFrameRateConversionConfiguration : NSObject <VTFrameProcessorConfiguration>

#pragma mark --- init function(s).

/// Creates a new frame-rate conversion configuration.
///
/// Returns `nil` if dimensions are out of range or revision is unsupported.
///
/// - Parameters:
///   - frameWidth: Width of source frame in pixels; the maximum value is 8192 for macOS, and 4096 for iOS.
///   - frameHeight: Height of source frame in pixels; the maximum value is 4320 for macOS, and 2160 for iOS.
///   - usePrecomputedFlow: A Boolean value that indicates whether you are providing Optical Flow. If false, optical flow is computed on the fly.
///   - qualityPrioritization: A level you use to prioritize quality or performance; for more information about supported levels, see ``VTFrameRateConversionConfigurationQualityPrioritization``.
///   - revision: The specific algorithm or configuration revision you use to perform the request.
- (nullable instancetype)initWithFrameWidth:(NSInteger)frameWidth
								frameHeight:(NSInteger)frameHeight
						 usePrecomputedFlow:(BOOL)usePrecomputedFlow
					  qualityPrioritization:(VTFrameRateConversionConfigurationQualityPrioritization)qualityPrioritization
								   revision:(VTFrameRateConversionConfigurationRevision)revision;

- (instancetype) init NS_UNAVAILABLE;
+ (instancetype) new NS_UNAVAILABLE;

/// Width of source frame in pixels.
@property (nonatomic, readonly) NSInteger frameWidth;

/// Height of source frame in pixels.
@property (nonatomic, readonly) NSInteger frameHeight;

/// Indicates that caller provides optical flow.
@property (nonatomic, readonly) BOOL usePrecomputedFlow;

/// A parameter you use to control quality and performance levels.
///
/// For more information about supported levels, see ``VTFrameRateConversionConfigurationQualityPrioritization``.
@property (nonatomic, readonly) VTFrameRateConversionConfigurationQualityPrioritization qualityPrioritization;

/// The specific algorithm or configuration revision you use to perform the request.
@property (nonatomic, readonly) VTFrameRateConversionConfigurationRevision revision;

/// Provides the collection of currently supported algorithms or configuration revisions for the class of configuration.
///
/// A property you use to introspect at runtime which revisions are available for each configuration.
@property (class, nonatomic, readonly) NSIndexSet* supportedRevisions;

/// Provides the default revision of a specific algorithm or configuration.
@property (class, nonatomic, readonly) VTFrameRateConversionConfigurationRevision defaultRevision;

/// Supported pixel formats available for source frames for current configuration.
@property (nonatomic, readonly) NSArray<NSNumber *> * frameSupportedPixelFormats NS_REFINED_FOR_SWIFT;

/// Pixel buffer attributes dictionary that describes requirements for pixel buffers which represent source frames and reference frames.
///
/// Use ``CVPixelBufferCreateResolvedAttributesDictionary`` to combine this dictionary with your pixel buffer attributes dictionary.
@property (nonatomic, readonly) NSDictionary<NSString *, id> * NS_SWIFT_SENDABLE sourcePixelBufferAttributes;

/// Pixel buffer attributes dictionary that describes requirements for pixel buffers which represent destination frames.
///
/// Use ``CVPixelBufferCreateResolvedAttributesDictionary`` to combine this dictionary with your pixel buffer attributes dictionary.
@property (nonatomic, readonly) NSDictionary<NSString *, id> * NS_SWIFT_SENDABLE destinationPixelBufferAttributes;

/// Reports whether the system supports this processor.
@property (class, nonatomic, readonly, getter=isSupported) BOOL supported;
@property (class, nonatomic, readonly) Boolean processorSupported API_DEPRECATED_WITH_REPLACEMENT("isSupported", macos(15.4, 26.0)) API_UNAVAILABLE(ios) API_UNAVAILABLE(tvos, watchos, visionos);

@end

/// An object that contains both input and output parameters, which the frame-rate conversion processor needs to process a frame.
///
/// Use this object as a parameter to the ``VTFrameProcessor/processWithParameters`` method. The output parameter for
/// this class is ``destinationFrame`` where the processor returns output frame (as mutable ``VTFrameProcessorFrame``)
/// back to you once the `processWithParameters` completes.
///
/// `VTFrameRateConversionParameters` are frame-level parameters.
API_AVAILABLE(macos(15.4), ios(26.0)) API_UNAVAILABLE(tvos, visionos, watchos)
@interface VTFrameRateConversionParameters : NSObject <VTFrameProcessorParameters>

/// Creates new frame rate conversion parameters.
///
/// Returns `nil` if `sourceFrame` or `nextFrame` is `nil`, if `sourceFrame` and reference frames don't have the same pixel format, or if `interpolationPhase` array count does not match `destinationFrames` array count.
///
/// - Parameters:
///   - sourceFrame: Current source frame; must be non `nil`.
///   - nextFrame: Next source frame in presentation time order; must be non `nil`.
///   - opticalFlow: Optional ``VTFrameProcessorOpticalFlow`` object that contains forward and backward optical flow with
///   next frame. You only need to use this if the optical flow is pre-computed. For the first frame this is always `nil`.
///   - interpolationPhase: Array of float numbers that indicate intervals at which the processor inserts a frame between
///   current and next frame. The array size indicates how many frames to interpolate and this size must match
///   `destinationFrames` size, with one interval for each destination frame. Use float number values between 0 and 1,
///   for example, to insert one frame in the middle use a value of 0.5.
///   - submissionMode: Provides a hint to let the processor know whether you are submitting frames in presentation
///   sequence. For more information about supported modes see ``VTFrameRateConversionParametersSubmissionMode``.
///   - destinationFrames: Caller-allocated array of ``VTFrameProcessorFrame`` that contains pixel buffers to receive the results. Must contain the same number of elements as `interpolationPhase`.
- (nullable instancetype) initWithSourceFrame:(VTFrameProcessorFrame *)sourceFrame
									nextFrame:(VTFrameProcessorFrame *)nextFrame
								  opticalFlow:(VTFrameProcessorOpticalFlow * _Nullable)opticalFlow
						   interpolationPhase:(NSArray<NSNumber *> *) interpolationPhase
							   submissionMode:(VTFrameRateConversionParametersSubmissionMode)submissionMode
							destinationFrames:(NSArray<VTFrameProcessorFrame *> *)destinationFrame NS_REFINED_FOR_SWIFT;

- (instancetype) init NS_UNAVAILABLE;
+ (instancetype) new NS_UNAVAILABLE;

/// Current source frame, which must be non `nil`.
@property(nonatomic, readonly) VTFrameProcessorFrame * sourceFrame;

/// The next source frame in presentation time order, which is `nil` for the last frame.
@property(nonatomic, readonly, nullable) VTFrameProcessorFrame * nextFrame;

/// An optional object that contains forward and backward optical flow with next frame.
///
/// Only needed if optical flow is pre-computed. For the last frame this is `nil`.
@property(nonatomic, readonly, nullable) VTFrameProcessorOpticalFlow * opticalFlow;

/// Array of float numbers that indicate intervals at which the processor inserts a frame between the current and next frame.
///
/// Array size indicates how many frames to interpolate and must match `destinationFrames` size, one interval for each destination frame. Use float number values between 0 and 1, for example, to insert one frame in the middle use a value of 0.5.
@property (nonatomic, readonly) NSArray<NSNumber *> * interpolationPhase NS_REFINED_FOR_SWIFT;

/// Ordering of the input frames in this submission relative to the previous submission.
@property (nonatomic, readonly) VTFrameRateConversionParametersSubmissionMode submissionMode;

/// Caller-allocated array of video frame objects that contain pixel buffers to receive the results.
///
/// Must contain the same number of elements as `interpolationPhase` NSArray.
@property(nonatomic, readonly) NSArray<VTFrameProcessorFrame *> * destinationFrames;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#endif // __OBJC__
#endif // ! TARGET_OS_SIMULATOR

#endif // VTFRAMEPROCESSOR_FRAMERATECONVERSION_H
