/*
	File:  VTFrameProcessor_LowLatencySuperResolutionScaler.h

	Framework:  VideoToolbox

	Copyright © 2024-2025 Apple Inc. All rights reserved.

*/

#ifndef VTFRAMEPROCESSOR_LOWLATENCYSUPERRESOLUTIONSCALER_H
#define VTFRAMEPROCESSOR_LOWLATENCYSUPERRESOLUTIONSCALER_H

#include <CoreMedia/CMBase.h>

#if ! TARGET_OS_SIMULATOR
#ifdef __OBJC__

#import <VideoToolbox/VTFrameProcessorConfiguration.h>
#import <VideoToolbox/VTFrameProcessorParameters.h>
#import <VideoToolbox/VTFrameProcessorFrame.h>


NS_HEADER_AUDIT_BEGIN(nullability, sendability)


/// An object you use to configure frame processor for low-latency super-resolution scaler processing.
///
/// Use this object to configure a ``VTFrameProcessor``. Query this interface also for important operating details, like
/// the pixel buffer attributes required for frames you submit to the processor.
///
/// > Important: When calling ``VTFrameProcessor/startSessionWithConfiguration:error:`` to create a `VTLowLatencySuperResolutionScaler`
/// session, ML model loading may take longer than a frame time. Avoid blocking the UI thread or stalling frame rendering
/// pipelines during this call.
API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos)
NS_SWIFT_SENDABLE
@interface VTLowLatencySuperResolutionScalerConfiguration : NSObject <VTFrameProcessorConfiguration>

#pragma mark --- init function(s).

/// Creates a new low-latency super-resolution scaler configuration with specified frame width and height.
///
/// - Parameters:
///   - frameWidth: Width of source frame in pixels.
///   - frameHeight: Height of source frame in pixels.
///   - scaleFactor: The scale factor to apply. This must be a supported value that ``supportedScaleFactorsForFrameWidth:frameHeight:`` returns.
- (instancetype)initWithFrameWidth:(NSInteger)frameWidth
					   frameHeight:(NSInteger)frameHeight
					   scaleFactor:(float)scaleFactor;

- (instancetype) init NS_UNAVAILABLE;
+ (instancetype) new NS_UNAVAILABLE;

/// Width of source frame in pixels.
@property (nonatomic, readonly) NSInteger frameWidth;

/// Height of source frame in pixels.
@property (nonatomic, readonly) NSInteger frameHeight;

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

/// Scale factor with which you initialized the configuration.
@property (nonatomic, readonly) float scaleFactor;

/// Maximum dimensions for a source frame for the processor.
@property (class, nonatomic, readonly) CMVideoDimensions maximumDimensions;

/// Minimum dimensions for a source frame for the processor.
@property (class, nonatomic, readonly) CMVideoDimensions minimumDimensions;

/// Reports whether the system supports this processor on the current configuration.
@property (class, nonatomic, readonly, getter=isSupported) BOOL supported;

/// Returns an array of supported scale factors values, or an empty list if the processor doesn't support the dimensions.
+ (NSArray<NSNumber*>*) supportedScaleFactorsForFrameWidth:(NSInteger)frameWidth
											   frameHeight:(NSInteger)frameHeight NS_REFINED_FOR_SWIFT;

@end

/// An object that contains both input and output parameters that the low-latency super-resolution scaler frame processor needs.
///
/// Use this object in the `processWithParameters` call of `VTFrameProcessor` class.
///
/// `VTLowLatencySuperResolutionScalerParameters` are frame-level parameters.
API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos)

@interface VTLowLatencySuperResolutionScalerParameters : NSObject <VTFrameProcessorParameters>

/// Creates a new low-latency, super-resolution scaler parameters object.
///
/// - Parameters:
///   - sourceFrame: Current source frame; must be non `nil`.
///   - destinationFrame: User-allocated pixel buffer that receives the scaled processor output; must be non `nil`.
- (instancetype) initWithSourceFrame:(VTFrameProcessorFrame *)sourceFrame
					destinationFrame:(VTFrameProcessorFrame *)destinationFrame;

- (instancetype) init NS_UNAVAILABLE;
+ (instancetype) new NS_UNAVAILABLE;

/// Current source frame, which must be non `nil`.
@property(nonatomic, readonly) VTFrameProcessorFrame * sourceFrame;

/// Destination frame that contains user-allocated pixel buffer that receives the scaled processor output.
@property(nonatomic, readonly) VTFrameProcessorFrame * destinationFrame;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#endif // __OBJC__
#endif // ! TARGET_OS_SIMULATOR

#endif // VTFRAMEPROCESSOR_LOWLATENCYSUPERRESOLUTIONSCALER_H
