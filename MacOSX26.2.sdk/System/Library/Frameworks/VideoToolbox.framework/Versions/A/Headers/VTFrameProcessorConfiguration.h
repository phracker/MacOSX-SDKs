/*
	File:  VTFrameProcessorConfiguration.h
 
	Framework:  VideoToolbox
 
	Copyright © 2023-2024 Apple Inc. All rights reserved.
 
*/

#ifndef VTFRAMEPROCESSORCONFIGURATION_H
#define VTFRAMEPROCESSORCONFIGURATION_H

#ifdef __OBJC__

#import <CoreMedia/CMBase.h>
#import <Foundation/Foundation.h>
#import <CoreMedia/CMFormatDescription.h>

NS_HEADER_AUDIT_BEGIN(nullability)


/// The protocol that describes the configuration of a processor for a video frame processing session.
///
/// Use `VTFrameProcessorConfiguration` protocol conformance to start a frame processing session. You can query these
/// properties on an implementation conforming to `VTFrameProcessorConfiguration` without starting a session.
API_AVAILABLE(macos(15.4), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos)
NS_SWIFT_SENDABLE
@protocol VTFrameProcessorConfiguration <NSObject>

@required

/// Returns a Boolean indicating whether the system supports this processor on the current configuration.
@property (class, nonatomic, readonly, getter=isSupported) BOOL supported;

/// List of supported pixel formats for source frames for the current configuration.
@property (nonatomic, readonly) NSArray<NSNumber *> * frameSupportedPixelFormats NS_REFINED_FOR_SWIFT;

/// Pixel buffer attributes dictionary that describes requirements for pixel buffers which represent source frames and reference frames.
///
/// Use ``CVPixelBufferCreateResolvedAttributesDictionary`` to combine this dictionary with your pixel buffer attributes dictionary.
@property (nonatomic, readonly) NSDictionary<NSString *, id> * NS_SWIFT_SENDABLE sourcePixelBufferAttributes;

/// Pixel buffer attributes dictionary that describes requirements for pixel buffers which represent destination frames.
///
/// Use ``CVPixelBufferCreateResolvedAttributesDictionary`` to combine this dictionary with your pixel buffer attributes dictionary.
@property (nonatomic, readonly) NSDictionary<NSString *, id> * NS_SWIFT_SENDABLE destinationPixelBufferAttributes;

@optional // WARNING: Optional properties must be refined for swift

/// Returns the number of "next" frames that this processor requires for processing.
@property (nonatomic, readonly) NSInteger nextFrameCount NS_REFINED_FOR_SWIFT;

/// Returns the number of "previous" frames that this processor requires for processing.
@property (nonatomic, readonly) NSInteger previousFrameCount NS_REFINED_FOR_SWIFT;

/// Returns the maximum dimensions for a `sourceFrame` for the processor.
@property (class, nonatomic, readonly) CMVideoDimensions maximumDimensions NS_REFINED_FOR_SWIFT;

/// Returns the minimum dimensions for a `sourceFrame` for the processor.
@property (class, nonatomic, readonly) CMVideoDimensions minimumDimensions NS_REFINED_FOR_SWIFT;

@end

NS_HEADER_AUDIT_END(nullability)

#endif // __OBJC__

#endif // VTFRAMEPROCESSORCONFIGURATION_H
