/*
	File:  VTFrameProcessor_OpticalFlow.h
 
	Framework:  VideoToolbox
 
	Copyright 2023-2024 Apple Inc. All rights reserved.
 
*/

#ifndef VTFRAMEPROCESSOR_OPTICALFLOW_H
#define VTFRAMEPROCESSOR_OPTICALFLOW_H

#include <CoreMedia/CMBase.h>

#if ! TARGET_OS_SIMULATOR
#ifdef __OBJC__

#import <VideoToolbox/VTFrameProcessorConfiguration.h>
#import <VideoToolbox/VTFrameProcessorParameters.h>
#import <VideoToolbox/VTFrameProcessorFrame.h>


/// Configuration value you set to prioritize quality or performance.
API_AVAILABLE(macos(15.4), ios(26.0)) API_UNAVAILABLE(tvos, visionos, watchos)
typedef NS_ENUM(NSInteger, VTOpticalFlowConfigurationQualityPrioritization) {
	VTOpticalFlowConfigurationQualityPrioritizationNormal = 1,
	VTOpticalFlowConfigurationQualityPrioritizationQuality = 2,
} NS_SWIFT_NAME(VTOpticalFlowConfiguration.QualityPrioritization);

/// Available algorithm revisions.
///
/// A new enum case with higher revision number is added when the processing algorithm is updated.
/// The ``VTOpticalFlowConfiguration/defaultRevision`` property provides the default algorithm revision.
API_AVAILABLE(macos(15.4), ios(26.0)) API_UNAVAILABLE(tvos, visionos, watchos)
typedef NS_ENUM(NSInteger, VTOpticalFlowConfigurationRevision) {
	VTOpticalFlowConfigurationRevision1           = 1,    // revision 1
} NS_SWIFT_NAME(VTOpticalFlowConfiguration.Revision);

/// Indicates the order of input frames.
///
/// When submitting ``VTOpticalFlowParameters`` to the processor, you need to provide one of these values based on how
/// the input frames are related to each other.
///
/// Use ``VTOpticalFlowParametersSubmissionModeSequential`` to indicate that the current submission follows presentation
/// time order without jump or skip, when compared to previous submissions. This value provides better processor
/// performance than other values.
///
/// Use ``VTOpticalFlowParametersSubmissionModeRandom`` to indicate that the current submission has no relation to the
/// previous submission. Typically, this indicates a jump or a skip in the frame sequence. The processor clears internal
/// caches when it receives this value in ``VTFrameProcessor/processWithParameters`` function call.
API_AVAILABLE(macos(15.4), ios(26.0)) API_UNAVAILABLE(tvos, visionos, watchos)
typedef NS_ENUM(NSInteger, VTOpticalFlowParametersSubmissionMode) {
	VTOpticalFlowParametersSubmissionModeRandom             = 1,    // You are submitting frames in non-sequential order.
	VTOpticalFlowParametersSubmissionModeSequential         = 2,    // You are submitting frames sequentially following presentation time order.
} NS_SWIFT_NAME(VTOpticalFlowParameters.SubmissionMode);

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Configuration that you use to set up an optical flow processor
///
/// This configuration enables the optical flow on a `VTFrameProcessor` session.
API_AVAILABLE(macos(15.4), ios(26.0)) API_UNAVAILABLE(tvos, visionos, watchos)
NS_SWIFT_SENDABLE
@interface VTOpticalFlowConfiguration : NSObject <VTFrameProcessorConfiguration>

#pragma mark --- init function(s).

/// Creates a new optical flow configuration.
///
/// Returns ``nil`` if dimensions are out of range or revision is unsupported.
///
/// - Parameters:
///   - frameWidth: Width of source frame in pixels; the maximum value is 8192 for macOS, and 4096 for iOS.
///   - frameHeight: Height of source frame in pixels; the maximum value is 4320 for macOS, and 2160 for iOS.
///   - qualityPrioritization: A level you use to prioritize quality or performance; for more information about supported
///   levels, see ``VTOpticalFlowConfigurationQualityPrioritization``.
///   - revision: The specific algorithm or configuration revision you use to perform the request.
- (nullable instancetype)initWithFrameWidth:(NSInteger)frameWidth
								frameHeight:(NSInteger)frameHeight
					  qualityPrioritization:(VTOpticalFlowConfigurationQualityPrioritization)qualityPrioritization
								   revision:(VTOpticalFlowConfigurationRevision)revision;

- (instancetype) init NS_UNAVAILABLE;
+ (instancetype) new NS_UNAVAILABLE;

/// Width of source frame in pixels.
@property (nonatomic, readonly) NSInteger frameWidth;

/// Height of source frame in pixels.
@property (nonatomic, readonly) NSInteger frameHeight;

/// A parameter you use to control quality and performance levels.
///
/// For more information about supported levels, see ``VTOpticalFlowConfigurationQualityPrioritization``.
@property (nonatomic, readonly) VTOpticalFlowConfigurationQualityPrioritization qualityPrioritization;

/// The specific algorithm or configuration revision you use to perform the request.
@property (nonatomic, readonly) VTOpticalFlowConfigurationRevision revision;

/// Provides the collection of currently supported algorithms or configuration revisions for the class of configuration.
///
/// A property you use to introspect at runtime which revisions are available for each configuration.
@property (class, nonatomic, readonly) NSIndexSet* supportedRevisions;

/// Provides the default revision of a specific algorithm or configuration.
@property (class, nonatomic, readonly) VTOpticalFlowConfigurationRevision defaultRevision;

/// Supported pixel formats for source frames for current configuration.
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

/// An object that contains both input and output parameters the frame processor needs to generate optical flow between two frames.
///
/// Use this object in the `processWithParameters` call of `VTFrameProcessor` class. The output parameter for this class is `destinationOpticalFlow` where the processor returns the output flow (as mutable `VTFrameProcessorOpticalFlow`) back to you once the `processWithParameters` completes.
///
/// `VTOpticalFlowParameters` are frame-level parameters.
API_AVAILABLE(macos(15.4), ios(26.0)) API_UNAVAILABLE(tvos, visionos, watchos)
@interface VTOpticalFlowParameters : NSObject <VTFrameProcessorParameters>

/// Creates a new optical flow parameters object.
///
/// Returns `nil` if `sourceFrame` or `nextFrame` is `nil`, or if `sourceFrame` and `nextFrame` have different pixel formats.
///
/// - Parameters:
///   - sourceFrame: Current source frame; must be non `nil`.
///   - nextFrame: Next source frame in presentation time order.
///   - submissionMode: Provides a hint to let the processor know whether you are submitting frames in presentation
///   sequence. For more information about supported modes see ``VTOpticalFlowParametersSubmissionMode``.
///   - destinationOpticalFlow: User allocated `VTFrameProcessorOpticalFlow` that receives the results.
- (nullable instancetype) initWithSourceFrame:(VTFrameProcessorFrame *)sourceFrame
									nextFrame:(VTFrameProcessorFrame *)nextFrame
							   submissionMode:(VTOpticalFlowParametersSubmissionMode)submissionMode
					   destinationOpticalFlow:(VTFrameProcessorOpticalFlow *) destinationOpticalFlow;

- (instancetype) init NS_UNAVAILABLE;
+ (instancetype) new NS_UNAVAILABLE;

/// Current source frame, which must be non `nil`.
@property(nonatomic, readonly) VTFrameProcessorFrame * sourceFrame;

/// The next source frame in presentation time order.
@property(nonatomic, readonly) VTFrameProcessorFrame * nextFrame;

/// Ordering of the input frames in this submission relative to the previous submission.
@property (nonatomic, readonly) VTOpticalFlowParametersSubmissionMode submissionMode;

/// Output optical flow calculated by the processor.
@property(nonatomic, readonly) VTFrameProcessorOpticalFlow * destinationOpticalFlow;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#endif // __OBJC__
#endif // ! TARGET_OS_SIMULATOR

#endif // VTFRAMEPROCESSOR_OPTICALFLOW_H
