/*
	File:  VTFrameProcessorFrame.h
 
	Framework:  VideoToolbox
 
	Copyright © 2023-2024 Apple Inc. All rights reserved.
 
*/

#ifndef VTFRAMEPROCESSORFRAME_H
#define VTFRAMEPROCESSORFRAME_H

#ifdef __OBJC__

#import <CoreMedia/CMBase.h>
#import <CoreVideo/CoreVideo.h>
#import <CoreMedia/CMTime.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)


/// Helper class to wrap pixel buffers as video frames.
///
/// You can use the frames as source frames, reference frames, or output frames of a processor. Frame instances retain
/// the backing pixel buffer.
API_AVAILABLE(macos(15.4), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos)
@interface VTFrameProcessorFrame : NSObject
/// Creates a new instance of frame with a pixel buffer and presentation timestamp.
///
/// The `CVPixelBuffer` is retained in this object.
/// Returns `nil` if the ``CVPixelBuffer`` you provided is NULL or the ``CVPixelBuffer`` is not backed by ``IOSurface``.
///
/// - Parameters:
///   - buffer: The ``CVPixelBuffer`` that this frame wraps; it must not be `nil` and must be ``IOSurface`` backed.
///   - presentationTimeStamp: The presentation timestamp of the buffer.
- (nullable instancetype)initWithBuffer:(CVPixelBufferRef)buffer
         presentationTimeStamp:(CMTime)presentationTimeStamp;

- (instancetype) init NS_UNAVAILABLE;
+ (instancetype) new NS_UNAVAILABLE;

/// Pixel buffer that you provided when you initialized the object.
@property(nonatomic,readonly) CVPixelBufferRef buffer;

/// Presentation timestamp that you provided when you initialized the object.
@property(nonatomic,readonly) CMTime presentationTimeStamp;

@end

/// Helper class to wrap optical flow.
///
/// Instances retain the backing pixel buffers that you provide.
API_AVAILABLE(macos(15.4), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos)
@interface VTFrameProcessorOpticalFlow : NSObject
/// Creates a new instance of forward and backward optical flow with pixel buffers.
///
/// Create a new instance with forward and backward optical flow ``CVPixelBuffer``s. Instances retain the pixel buffers
/// you provide to this method. Returns `nil` if either `CVPixelBuffer` is NULL or the `CVPixelBuffer`s are not `IOSurface` backed.
///
/// - Parameters:
///   - forwardFlow: `CVPixelBuffer` that contains forward optical flow; it must not be `nil` and must be `IOSurface` backed.
///   - backwardFlow: `CVPixelBuffer` that contains backward optical flow; it must not be `nil` and must be `IOSurface` backed.
- (nullable instancetype)initWithForwardFlow:(CVPixelBufferRef)forwardFlow
                       backwardFlow:(CVPixelBufferRef)backwardFlow;

- (instancetype) init NS_UNAVAILABLE;
+ (instancetype) new NS_UNAVAILABLE;

/// Returns the forward optical flow `CVPixelBuffer` that you provided when you initialized the object.
@property(nonatomic, readonly) CVPixelBufferRef forwardFlow;

/// Returns the backward optical flow `CVPixelBuffer` that you provided when you initialized the object.
@property(nonatomic, readonly) CVPixelBufferRef backwardFlow;

@end


NS_HEADER_AUDIT_END(nullability, sendability)

#endif // __OBJC__

#endif // VTFRAMEPROCESSORFRAME_H
