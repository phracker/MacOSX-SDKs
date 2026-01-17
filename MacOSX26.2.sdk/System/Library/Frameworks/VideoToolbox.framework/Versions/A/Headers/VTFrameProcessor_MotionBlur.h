/*
	File:  VTFrameProcessor_MotionBlur.h
 
	Framework:  VideoToolbox
 
	Copyright 2023-2024 Apple Inc. All rights reserved.
 
*/

#ifndef VTFRAMEPROCESSOR_MOTIONBLUR_H
#define VTFRAMEPROCESSOR_MOTIONBLUR_H

#include <CoreMedia/CMBase.h>

#if ! TARGET_OS_SIMULATOR
#ifdef __OBJC__

#import <VideoToolbox/VTFrameProcessorConfiguration.h>
#import <VideoToolbox/VTFrameProcessorParameters.h>
#import <VideoToolbox/VTFrameProcessorFrame.h>


/// Configuration value you set to prioritize quality or performance.
API_AVAILABLE(macos(15.4), ios(26.0)) API_UNAVAILABLE(tvos, visionos, watchos)
typedef NS_ENUM(NSInteger, VTMotionBlurConfigurationQualityPrioritization) {
	VTMotionBlurConfigurationQualityPrioritizationNormal = 1,
	VTMotionBlurConfigurationQualityPrioritizationQuality = 2,
} NS_SWIFT_NAME(VTMotionBlurConfiguration.QualityPrioritization);

/// Available algorithm revisions.
///
/// A new enum case with higher revision number is added when the processing algorithm is updated.
/// The ``VTMotionBlurConfiguration/defaultRevision`` property provides the default algorithm revision.
API_AVAILABLE(macos(15.4), ios(26.0)) API_UNAVAILABLE(tvos, visionos, watchos)
typedef NS_ENUM(NSInteger, VTMotionBlurConfigurationRevision) {
	VTMotionBlurConfigurationRevision1           = 1,    // revision 1
} NS_SWIFT_NAME(VTMotionBlurConfiguration.Revision);

/// Indicates the order of input frames.
///
/// When submitting ``VTMotionBlurParameters`` to the processor, you need to provide one of these values based on how
/// the input frames are related to each other.
///
/// Use ``VTMotionBlurParametersSubmissionModeSequential`` to indicate that the current submission follows presentation
/// time order without jump or skip, when compared to previous submissions. This value provides better processor
/// performance than other values.
///
/// Use ``VTMotionBlurParametersSubmissionModeRandom`` to indicate that the current submission has no relation to the
/// previous submission. Typically, this indicates a jump or a skip in the frame sequence. The processor clears internal
/// caches when it receives this value in ``VTFrameProcessor/processWithParameters`` function call.
API_AVAILABLE(macos(15.4), ios(26.0)) API_UNAVAILABLE(tvos, visionos, watchos)
typedef NS_ENUM(NSInteger, VTMotionBlurParametersSubmissionMode) {
	VTMotionBlurParametersSubmissionModeRandom             = 1,    // You are submitting frames in non-sequential order.
	VTMotionBlurParametersSubmissionModeSequential         = 2,    // You are submitting frames sequentially following presentation time order.
} NS_SWIFT_NAME(VTMotionBlurParameters.SubmissionMode);

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Configuration that you use to set up the motion blur processor.
///
/// This configuration enables the motion blur on a `VTFrameProcessor` session.
API_AVAILABLE(macos(15.4), ios(26.0)) API_UNAVAILABLE(tvos, visionos, watchos)
NS_SWIFT_SENDABLE
@interface VTMotionBlurConfiguration : NSObject <VTFrameProcessorConfiguration>

#pragma mark --- init function(s).

/// Creates a new motion blur configuration.
///
/// Returns `nil` if dimensions are out of range or revision is unsupported.
///
/// - Parameters:
///   - frameWidth: Width of source frame in pixels; the maximum value is 8192 for macOS, and 4096 for iOS.
///   - frameHeight: Height of source frame in pixels; the maximum value is 4320 for macOS, and 2160 for iOS.
///   - usePrecomputedFlow: Boolean value that indicates whether you will provide optical flow; if false, this
///    configuration computes the optical flow on the fly.
///   - qualityPrioritization: A level you use to prioritize quality or performance; for more information about supported
///    levels, see ``VTMotionBlurConfigurationQualityPrioritization``.
///   - revision: The specific algorithm or configuration revision you use to perform the request.
- (nullable instancetype)initWithFrameWidth:(NSInteger)frameWidth
								frameHeight:(NSInteger)frameHeight
						 usePrecomputedFlow:(BOOL)usePrecomputedFlow
					  qualityPrioritization:(VTMotionBlurConfigurationQualityPrioritization)qualityPrioritization
								   revision:(VTMotionBlurConfigurationRevision)revision;

- (instancetype) init NS_UNAVAILABLE;
+ (instancetype) new NS_UNAVAILABLE;

/// Width of source frame in pixels.
@property (nonatomic, readonly) NSInteger frameWidth;

/// Height of source frame in pixels.
@property (nonatomic, readonly) NSInteger frameHeight;

/// Indicates that you provide optical flow.
@property (nonatomic, readonly) BOOL usePrecomputedFlow;

/// A parameter you use to control quality and performance levels.
///
/// For more information about supported levels, see ``VTMotionBlurConfigurationQualityPrioritization``.
@property (nonatomic, readonly) VTMotionBlurConfigurationQualityPrioritization qualityPrioritization;

/// The specific algorithm or configuration revision you use to perform the request.
@property (nonatomic, readonly) VTMotionBlurConfigurationRevision revision;

/// Provides the collection of currently supported algorithms or configuration revisions for the class of configuration.
///
/// A property you use to introspect at runtime which revisions are available for each configuration.
@property (class, nonatomic, readonly) NSIndexSet* supportedRevisions;

/// Provides the default revision of a specific algorithm or configuration.
@property (class, nonatomic, readonly) VTMotionBlurConfigurationRevision defaultRevision;

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

/// Reports whether the system supports this processor.
@property (class, nonatomic, readonly, getter=isSupported) BOOL supported;
@property (class, nonatomic, readonly) Boolean processorSupported API_DEPRECATED_WITH_REPLACEMENT("isSupported", macos(15.4, 26.0)) API_UNAVAILABLE(ios) API_UNAVAILABLE(tvos, watchos, visionos);

@end

/// An object that contains both input and output parameters that the motion blur processor needs to run on a frame.
///
/// Use this object in the `processWithParameters` call of `VTFrameProcessor` class. The output parameter for this class is `destinationFrame` where the processor returns the output frame (as `VTFrameProcessorFrame`) back to you once the `processWithParameters` completes.
///
/// `VTMotionBlurParameters` are frame-level parameters.
API_AVAILABLE(macos(15.4), ios(26.0)) API_UNAVAILABLE(tvos, visionos, watchos)
@interface VTMotionBlurParameters : NSObject <VTFrameProcessorParameters>

/// Creates a new motion blur parameters object.
///
/// Returns `nil` if `sourceFrame` or `destinationFrame` is `nil`, `sourceFrame` and reference frames are different pixel
/// formats, or `motionBlurStrength` is out of range.
///
/// - Parameters:
///   - sourceFrame: Current source frame; must be non `nil`.
///   - nextFrame: Next source frame in presentation time order; for the last frame you can set this to `nil`.
///   - previousFrame: Previous source frame in presentation time order; for the first frame you can set this to `nil`.
///   - nextOpticalFlow: Optional `VTFrameProcessorOpticalFlow` object that contains forward and backward optical flow
///   with `nextFrame`. You only need this object if optical flow is pre-computed. For the last frame this is always `nil`.
///   - previousOpticalFlow: Optional VTFrameProcessorOpticalFlow object that contains forward and backward optical flow
///   with `previousFrame`. You only need to use this if the optical flow is pre-computed. For the first frame this is always `nil`.
///   - motionBlurStrength: Number that indicates the strength of blur applied by the processor. Range is from 1 to 100. Default value is 50.
///   - submissionMode: Provides a hint to let the processor know whether you are submitting frames in presenatation
///   sequence. For more information about supported modes see ``VTMotionBlurParametersSubmissionMode``.
///   - destinationFrame: User-allocated pixel buffer that receives a frame with motion blur applied by the processor.
- (nullable instancetype) initWithSourceFrame:(VTFrameProcessorFrame *)sourceFrame
									nextFrame:(VTFrameProcessorFrame * _Nullable)nextFrame
								previousFrame:(VTFrameProcessorFrame * _Nullable)previousFrame
							  nextOpticalFlow:(VTFrameProcessorOpticalFlow * _Nullable)nextOpticalFlow
						  previousOpticalFlow:(VTFrameProcessorOpticalFlow * _Nullable)previousOpticalFlow
						   motionBlurStrength:(NSInteger)motionBlurStrength
							   submissionMode:(VTMotionBlurParametersSubmissionMode)submissionMode
							 destinationFrame:(VTFrameProcessorFrame *)destinationFrame;

- (instancetype) init NS_UNAVAILABLE;
+ (instancetype) new NS_UNAVAILABLE;

/// Current source frame, which must be non `nil`.
@property(nonatomic, readonly) VTFrameProcessorFrame * sourceFrame;

/// The next source frame in presentation time order, which is `nil` for the last frame.
@property(nonatomic, readonly, nullable) VTFrameProcessorFrame * nextFrame;

/// Previous source frame in presentation time order, which is `nil` for the first frame.
@property(nonatomic, readonly, nullable) VTFrameProcessorFrame * previousFrame;

/// Optional frame processor optical flow object that contains forward and backward optical flow with next frame.
///
/// You only need to use this object if the optical flow is pre-computed. For the last frame this is `nil`.
@property(nonatomic, readonly, nullable) VTFrameProcessorOpticalFlow * nextOpticalFlow;

/// Optional frame processor optical flow object that contains forward and backward optical flow with previous frame.
///
/// You only need to use this object if the optical flow is pre-computed. For the first frame this is `nil`.
@property(nonatomic, readonly, nullable) VTFrameProcessorOpticalFlow * previousOpticalFlow;

/// Number that indicates the strength of motion blur.
///
/// The range is from 1 to 100; the default value is 50.
@property (nonatomic, readonly) NSInteger motionBlurStrength;

/// Ordering of the input frames this submission related to the previous submission.
@property (nonatomic, readonly) VTMotionBlurParametersSubmissionMode submissionMode;

/// Destination frame that contains user-allocated pixel buffer that receive a frame with motion blur applied by the processor.
@property(nonatomic, readonly) VTFrameProcessorFrame * destinationFrame;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#endif // __OBJC__
#endif // ! TARGET_OS_SIMULATOR

#endif // VTFRAMEPROCESSOR_MOTIONBLUR_H
