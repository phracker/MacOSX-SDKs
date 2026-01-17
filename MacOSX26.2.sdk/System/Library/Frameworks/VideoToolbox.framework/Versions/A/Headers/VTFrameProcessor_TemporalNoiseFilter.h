/*
	File:  VTFrameProcessor_TemporalNoiseFilter.h
 
	Framework:  VideoToolbox
 
	Copyright © 2024-2025 Apple Inc. All rights reserved.
 
*/

#ifndef VTFRAMEPROCESSOR_TEMPORALNOISEFILTER_H
#define VTFRAMEPROCESSOR_TEMPORALNOISEFILTER_H

#include <CoreMedia/CMBase.h>

#if ! TARGET_OS_SIMULATOR
#ifdef __OBJC__

#import <VideoToolbox/VTFrameProcessorConfiguration.h>
#import <VideoToolbox/VTFrameProcessorParameters.h>
#import <VideoToolbox/VTFrameProcessorFrame.h>


NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A configuration object to initiate a frame processor and use temporal noise-filter processor.
///
/// The class properties of `VTTemporalNoiseFilterConfiguration` help to identify the capabilities of temporal noise
/// filter processor on the current platform, prior to initiating a session. You can confirm the availability of temporal
/// noise-filter processor in the current platform by checking the ``isSupported`` class property. Verify the processor's
/// capability to process source frames by ensuring that the dimensions are no less than ``minimumDimensions`` and no
/// greater than ``maximumDimensions``. Use the instance properties such as ``frameSupportedPixelFormats``,
/// ``sourcePixelBufferAttributes``, and ``destinationPixelBufferAttributes`` to ensure that the input and output pixel
/// buffer formats and attributes of the processor align with the client's specific requirements. The properties
/// ``previousFrameCount`` and ``nextFrameCount`` represent the maximum number of preceding and subsequent reference
/// frames, used in the processing of a source frame, to achieve optimum noise-reduction quality.
API_AVAILABLE(macos(26.0), ios(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(tvos, watchos)
NS_SWIFT_SENDABLE
VT_EXPORT @interface VTTemporalNoiseFilterConfiguration : NSObject <VTFrameProcessorConfiguration>

#pragma mark --- init function(s).

/// Creates a new temporal noise-processor configuration.
///
///	Returns nil if frameWidth, frameHeight, or sourcePixelFormat is unsupported.
///
/// - Parameters:
///   - frameWidth: Width of source frame in pixels.
///   - frameHeight: Height of source frame in pixels.
- (nullable instancetype)initWithFrameWidth:(NSInteger)frameWidth
								frameHeight:(NSInteger)frameHeight
						  sourcePixelFormat:(OSType)sourcePixelFormat;

- (instancetype) init NS_UNAVAILABLE;
+ (instancetype) new NS_UNAVAILABLE;

/// Width of source frame in pixels.
@property (nonatomic, readonly) NSInteger frameWidth;

/// Height of source frame in pixels.
@property (nonatomic, readonly) NSInteger frameHeight;

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

/// Maximum number of future reference frames that the processor can use to process a source frame.
@property (nonatomic, readonly) NSInteger nextFrameCount;

/// Maximum number of past reference frames that the processor can use to process a source frame.
@property (nonatomic, readonly) NSInteger previousFrameCount;

///	List of all supported pixel formats for source frames.
@property (class, nonatomic, readonly) NSArray<NSNumber *> *supportedSourcePixelFormats NS_REFINED_FOR_SWIFT;

/// The maximum dimensions of a source frame that the processor supports.
@property (class, nonatomic, readonly) CMVideoDimensions maximumDimensions;

/// The minimum dimensions of a source frame that the processor supports.
@property (class, nonatomic, readonly) CMVideoDimensions minimumDimensions;

/// Reports whether the system supports this processor.
@property (class, nonatomic, readonly, getter=isSupported) BOOL supported;

@end

/// Encapsulates the frame-level parameters necessary for processing a source frame using temporal noise-filter processor.
///
/// This object is intended for sending input parameters into the `processWithParameters` method of the `VTFrameProcessor`
/// class. Temporal noise-filter processor utilizes past and future reference frames, provided in presentation time order,
/// to reduce noise from the source frame. The `previousFrameCount` and `nextFrameCount` properties in
/// ``VTTemporalNoiseFilterConfiguration`` represent the maximum number of past and future reference frames that the
/// processor can use to achieve optimum noise reduction quality. The number of reference frames provided shall depend
/// on their availability, but at a minimum, you must provide one reference frame, either past or future. The parameter
/// `destinationFrame` stores the output frame that the processor returns to the caller upon the successful completion
/// of the `processWithParameters` operation.
API_AVAILABLE(macos(26.0), ios(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(tvos, watchos)
VT_EXPORT @interface VTTemporalNoiseFilterParameters : NSObject <VTFrameProcessorParameters>

/// Creates a new `VTTemporalNoiseFilterParameters` object.
///
/// - Parameters:
///   - sourceFrame: Current source frame; must be non `nil`.
///   - nextFrames: Future reference frames in presentation time order to use for processing the source frame. The number
///   of frames can vary from 0 to the number specified by ``VTTemporalNoiseFilterConfiguration/nextFrameCount`` property.
///   - previousFrames: Past reference frames in presentation time order to use for processing the source frame. The number
///   of frames can vary from 0 to the number specified by ``VTTemporalNoiseFilterConfiguration/previousFrameCount`` property.
///   - destinationFrame: User-allocated pixel buffer that receives the output frame. The pixel format of `destinationFrame`
///   must match with that of the `sourceFrame`.
///   - filterStrength: Strength of the noise-filtering to use. The value can range from the minimum strength of 0.0 to the
///   maximum strength of 1.0. Change in filter strength causes the processor to flush all frames in the queue prior to
///   processing the source frame.
///   - hasDiscontinuity: Marks sequence discontinuity, forcing the processor to reset prior to processing the source frame.
- (nullable instancetype) initWithSourceFrame:(VTFrameProcessorFrame *)sourceFrame
								   nextFrames:(NSArray<VTFrameProcessorFrame *> *)nextFrames
							   previousFrames:(NSArray<VTFrameProcessorFrame *> *)previousFrames
							 destinationFrame:(VTFrameProcessorFrame *)destinationFrame
							   filterStrength:(float)filterStrength
							 hasDiscontinuity:(Boolean)hasDiscontinuity;

- (instancetype) init NS_UNAVAILABLE;
+ (instancetype) new NS_UNAVAILABLE;

/// Current source frame; must be non `nil`.
@property(nonatomic, readonly) VTFrameProcessorFrame * sourceFrame;

/// Future reference frames in presentation time order that you use to process the source frame.
///
/// The number of frames can vary from 0 to the number specified by the `nextFrameCount` property in `VTTemporalNoiseFilterConfiguration`.
@property(nonatomic, readonly) NSArray<VTFrameProcessorFrame *> *nextFrames;

/// Past reference frames in presentation time order that you use to process the source frame.
///
/// The number of frames can vary from 0 to the number specified by the `previousFrameCount` property in `VTTemporalNoiseFilterConfiguration`.
@property(nonatomic, readonly) NSArray<VTFrameProcessorFrame *> *previousFrames;

/// A parameter to control the strength of noise-filtering. The value can range from the minimum strength of 0.0 to the maximum strength of 1.0. Change in filter strength causes the processor to flush all frames in the queue prior to processing the source frame.
@property (nonatomic) float filterStrength;

/// A Boolean that indicates sequence discontinuity, forcing the processor to reset prior to processing the source frame.
@property (nonatomic) BOOL hasDiscontinuity;

/// Destination frame that contains a user-allocated pixel buffer that receives the output frame.
@property(nonatomic, readonly) VTFrameProcessorFrame * destinationFrame;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#endif // __OBJC__
#endif // ! TARGET_OS_SIMULATOR

#endif // VTFRAMEPROCESSOR_TEMPORALNOISEFILTER_H
