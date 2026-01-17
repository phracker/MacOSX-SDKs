//
//  CNObjectTracker.h
//  Cinematic
//
//  Copyright © 2022-2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreMedia/CoreMedia.h>
#import <Metal/Metal.h>

#import <Cinematic/CNDetectionTrack.h>

NS_ASSUME_NONNULL_BEGIN

NS_REFINED_FOR_SWIFT
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface CNBoundsPrediction : NSObject <NSCopying, NSMutableCopying>

/// bounds of the detected object in normalized coordinates where (0.0, 0.0) is the upper left corner, and (1.0, 1.0) is the lower right
@property CGRect normalizedBounds;

/// the probability that a well-defined object is within the bounds — a number between 0.0 and 1.0.
@property float confidence;

@end


NS_REFINED_FOR_SWIFT
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos)
/// Converts a normalized point or rectangle into a detection track that tracks an object over time.
@interface CNObjectTracker : NSObject

/// Indicates whether the current device supports object detection and tracking.
@property (class, readonly) BOOL isSupported;

/// Create a new detection track builder.
/// - Parameters:
///   - commandQueue: the command queue of a metal device to which commands should be submitted to perform work
- (instancetype)initWithCommandQueue:(id<MTLCommandQueue>)commandQueue;

/// Find the bounds of an object at the given point. Can be used to convert a normalized point in an image to a rectangle that can be used to start tracking.
/// - Parameters:
///   - point: location of object in image in normalized coordinates where (0.0, 0.0) is the upper left corner, and (1.0, 1.0) is the lower right
///   - sourceImage: pixel buffer containing the image
/// - Returns: A prediction, which includes bounds that can be used to start tracking, or `nil` if no discernible object is detected.
- (nullable CNBoundsPrediction *)findObjectAtPoint:(CGPoint)point sourceImage:(CVPixelBufferRef)sourceImage;

/// Start creating a detection track to track an object within the given bounds.
/// - Parameters:
///   - time: the presentation time of the first frame in the detection track
///   - normalizedBounds: the bounds of the object to track in normalized coordinates where (0.0, 0.0) is the upper left corner, and (1.0, 1.0) is the lower right
///   - sourceImage: image buffer containing the image
///   - sourceDisparity: disparity buffer containing depth information
/// - Returns: whether the object can be tracked
/// - Note: if the object can be tracked, a detection is added to the detection track being built
- (BOOL)startTrackingAt:(CMTime)time within:(CGRect)normalizedBounds sourceImage:(CVPixelBufferRef)sourceImage sourceDisparity:(CVPixelBufferRef)sourceDisparity;

/// Continue tracking an object for which tracking has started, and add a new detection to the detection track being built.
/// - Parameters:
///   - time: the presentation time of the frame to be added to the detection track
/// - Returns: a prediction of where the object is in the source image
- (nullable CNBoundsPrediction *)continueTrackingAt:(CMTime)time sourceImage:(CVPixelBufferRef)sourceImage sourceDisparity:(CVPixelBufferRef)sourceDisparity;

/// Finish constructing the detection track and return it.
/// - Returns: a detection track which tracks the object
- (CNDetectionTrack *)finishDetectionTrack;

/// Reset the builder to construct a new detection track.
- (void)resetDetectionTrack;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
