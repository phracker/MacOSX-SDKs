/*
	File:  VTFrameProcessor_LowLatencyFrameInterpolation.h
 
	Framework:  VideoToolbox
 
	Copyright © 2024-2025 Apple Inc. All rights reserved.
 
*/

#ifndef VTFRAMEPROCESSOR_LOWLATENCYFRAMEINTERPOLATION_H
#define VTFRAMEPROCESSOR_LOWLATENCYFRAMEINTERPOLATION_H

#include <CoreMedia/CMBase.h>

#if ! TARGET_OS_SIMULATOR
#ifdef __OBJC__

#import <VideoToolbox/VTFrameProcessorConfiguration.h>
#import <VideoToolbox/VTFrameProcessorParameters.h>
#import <VideoToolbox/VTFrameProcessorFrame.h>


NS_HEADER_AUDIT_BEGIN(nullability, sendability)


/// Configuration that you use to program Video Toolbox frame processor for low-latency frame interpolation.
///
/// This configuration can do either purely temporal interpolation (frame-rate conversion) or temporal and spatial
/// interpolation (scaling and frame-rate conversion). This processor requires a source frame and a previous frame. It
/// does temporal scaling, which interpolates frames between the previous frame and the source frame. When performing
/// both temporal and spatial interpolation, the processor can only perform 2x upscaling, and a single frame of temporal
/// interpolation. When performing spatial scaling, the processor produces upscaled intermediate frames and an upscaled
/// `sourceFrame`, but it does not upscale the previous reference frame you provided.
///
/// > Important: When calling ``VTFrameProcessor/startSessionWithConfiguration:error:`` to create a `VTLowLatencyFrameInterpolation`
/// session, ML model loading may take longer than a frame time. Avoid blocking the UI thread or stalling frame rendering
/// pipelines during this call.
API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos)
NS_SWIFT_SENDABLE
@interface VTLowLatencyFrameInterpolationConfiguration : NSObject <VTFrameProcessorConfiguration>

#pragma mark --- init function(s).

/// Creates a new low-latency frame interpolation configuration for frame-rate conversion.
///
/// The available interpolation points are the equal to the value of (2^x - 1), where x is equal to `numberOfInterpolatedFrames`.
/// For example,
/// - If you request 1 interpolated frame, 1 interpolation point at 0.5 is available.
/// - If you request 2 interpolated frames, 3 interpolation points at 0.25, 0.5 and 0.75 are available.
/// You don't need to use all available interpolation points. Setting a higher `numberOfInterpolatedFrames` increases
/// the resolution of interpolation in some cases, but also increases latency.
///
/// - Parameters:
///   - frameWidth: Width of source frame in pixels.
///   - frameHeight: Height of source frame in pixels.
///   - numberOfInterpolatedFrames: The number of uniformly spaced frames that you want to be used for interpolation.
- (nullable instancetype)initWithFrameWidth:(NSInteger)frameWidth
								frameHeight:(NSInteger)frameHeight
				 numberOfInterpolatedFrames:(NSInteger)numberOfInterpolatedFrames;

/// Creates a new low-latency frame interpolation configuration for spatial scaling and temporal scaling.
///
/// When you configure the processor for spatial scaling, the low-latency frame interpolation processor only supports 2x
/// spatial upscaling and a single frame of temporal interpolation at a 0.5 interpolation phase.
///
/// - Parameters:
///   - frameWidth: Width of source frame in pixels.
///   - frameHeight: Height of source frame in pixels.
///   - spatialScaleFactor: The requested spatial scale factor as an integer. Currently, the processor supports only 2x spatial scaling.
- (nullable instancetype)initWithFrameWidth:(NSInteger)frameWidth
								frameHeight:(NSInteger)frameHeight
						 spatialScaleFactor:(NSInteger)spatialScaleFactor;

- (instancetype) init NS_UNAVAILABLE;
+ (instancetype) new NS_UNAVAILABLE;

/// Width of source frames in pixels.
@property (nonatomic, readonly) NSInteger frameWidth;

/// Height of source frames in pixels.
@property (nonatomic, readonly) NSInteger frameHeight;

/// Configured spatial scale factor as an integer.
@property (nonatomic, readonly) NSInteger spatialScaleFactor;

/// Number of uniformly spaced frames for which you configured the processor.
@property (nonatomic, readonly) NSInteger numberOfInterpolatedFrames;

/// Available supported pixel formats for current configuration.
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

@end

/// An object that contains both input and output parameters that the low-latency frame interpolation processor needs.
///
/// Use this object in the `processWithParameters` call of `VTFrameProcessor` class.
///
/// `VTLowLatencyFrameInterpolationParameters` are frame-level parameters.
API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos)
@interface VTLowLatencyFrameInterpolationParameters : NSObject <VTFrameProcessorParameters>

/// Creates a new low-latency frame interpolation parameters object.
///
/// - Parameters:
///   - sourceFrame: Current frame to use for interpolation; must be non `nil`.
///   - previousFrame: Previous frame used for interpolation; must be non `nil`.
///   - interpolationPhase: Array of float numbers that indicate interpolation phase locations at which the processor
///   interpolates the frames. Must be greater than 0 and less than 1.0; for example 0.5 is midway between the previous
///   frame and the source frame. If you enable spatial scaling, the only supported interpolation phase is 0.5.
///   - destinationFrames: Caller-allocated array of `VTFrameProcessorFrame` to receive the interpolated frames. This
///   must have the same number of elements as the the `interpolationPhase`. If you enable spatial scaling, it must also
///   contain an element to hold the scaled version of sourceFrame.
- (nullable instancetype) initWithSourceFrame:(VTFrameProcessorFrame *)sourceFrame
					   previousFrame:(VTFrameProcessorFrame *)previousFrame
				  interpolationPhase:(NSArray<NSNumber *> *) interpolationPhase
				   destinationFrames:(NSArray<VTFrameProcessorFrame *> *)destinationFrames NS_REFINED_FOR_SWIFT;

- (instancetype) init NS_UNAVAILABLE;
+ (instancetype) new NS_UNAVAILABLE;

/// Source frame that you provided when creating the low-latency frame interpolation parameters object.
@property(nonatomic, readonly) VTFrameProcessorFrame * sourceFrame;

/// Previous frame that you provided when creating the low-latency frame interpolation parameters object.
@property(nonatomic, readonly) VTFrameProcessorFrame * previousFrame;

/// Array of interpolation phases that you provided when creating the low-latency frame interpolation parameters object.
@property (nonatomic, readonly) NSArray<NSNumber *> * interpolationPhase NS_REFINED_FOR_SWIFT;

/// Array of destination frames that you provided when creating the low-latency frame interpolation parameters object.
@property(nonatomic, readonly) NSArray<VTFrameProcessorFrame *> * destinationFrames;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#endif // __OBJC__
#endif // ! TARGET_OS_SIMULATOR

#endif // VTFRAMEPROCESSOR_LOWLATENCYFRAMEINTERPOLATION_H
