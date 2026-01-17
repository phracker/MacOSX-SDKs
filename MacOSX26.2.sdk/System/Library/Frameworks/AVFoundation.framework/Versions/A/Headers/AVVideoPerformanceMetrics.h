#if !__has_include(<AVFCore/AVVideoPerformanceMetrics.h>)
/*
 	File:  AVVideoPerformanceMetrics.h
 
 	Framework:  AVFoundation
 
 	Copyright 2014-2023 Apple Inc. All rights reserved.
 
 */

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class AVVideoPerformanceMetricsInternal;

/*!
 @class			AVVideoPerformanceMetrics
 @abstract		[SPI] An instance of AVVideoPerformanceMetrics provides current performance metrics.
 @discussion	An instance of AVVideoPerformanceMetrics provides named properties for accessing the video playback quality metrics.
				Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
 */

NS_SWIFT_SENDABLE
API_AVAILABLE(macos(14.4), ios(17.4), tvos(17.4), visionos(1.1)) API_UNAVAILABLE(watchos)
@interface AVVideoPerformanceMetrics : NSObject
{
@private
	AVVideoPerformanceMetricsInternal *_performanceMetricsInternal;
}
AV_INIT_UNAVAILABLE

/*!
 @property		totalNumberOfFrames
 @abstract		[SPI] The total number of frames that would have been displayed if no frames are dropped.
 */
@property (nonatomic, readonly) NSInteger totalNumberOfFrames;

/*!
 @property		numberOfDroppedFrames
 @abstract		[SPI] The total number of frames dropped prior to decoding or dropped because a frame missed its display deadline.
 */
@property (nonatomic, readonly) NSInteger numberOfDroppedFrames;

/*!
 @property		numberOfCorruptedFrames
 @abstract		[SPI] The total number of corrupted frames that have been detected.
 */
@property (nonatomic, readonly) NSInteger numberOfCorruptedFrames;

/*!
 @property		numberOfFramesDisplayedUsingOptimizedCompositing
 @abstract		[SPI] The total number of full screen frames that were rendered in a special power-efficient mode that didn't require the frame to be composited with other UI elements.
 */
@property (nonatomic, readonly) NSInteger numberOfFramesDisplayedUsingOptimizedCompositing;

/*!
 @property		totalAccumulatedFrameDelay
 @abstract		[SPI] The accumulated amount of time between the prescribed presentation times of displayed video frames and the actual time at which they were displayed.
 @discussion	This delay is always greater than or equal to zero since frames must never be displayed before their presentation time. Non-zero delays are a sign of playback jitter and possible loss of A/V sync.
 */
@property (nonatomic, readonly) NSTimeInterval totalAccumulatedFrameDelay;

/*!
 @property		totalNumberOfVideoFrames
 @abstract		[SPI] The total number of frames that would have been displayed if no frames are dropped. Same as totalNumberOfFrames.
 */
@property (nonatomic, readonly) unsigned long totalNumberOfVideoFrames API_UNAVAILABLE(macos, ios, tvos, visionos) API_UNAVAILABLE(watchos);

/*!
 @property		numberOfDroppedVideoFrames
 @abstract		[SPI] The total number of frames dropped prior to decoding or dropped because a frame missed its display deadline. Same as numberOfDroppedFrames.
 */
@property (nonatomic, readonly) unsigned long numberOfDroppedVideoFrames API_UNAVAILABLE(macos, ios, tvos, visionos) API_UNAVAILABLE(watchos);

/*!
 @property		numberOfCorruptedVideoFrames
 @abstract		[SPI] The total number of corrupted frames that have been detected. Same as numberOfCorruptedFrames.
 */
@property (nonatomic, readonly) unsigned long numberOfCorruptedVideoFrames API_UNAVAILABLE(macos, ios, tvos, visionos) API_UNAVAILABLE(watchos);

/*!
 @property		numberOfDisplayCompositedFrames
 @abstract		[SPI] The total number of frames that were composited in detached mode.  Same as numberOfFramesDisplayedUsingOptimizedCompositing.
 */
@property (nonatomic, readonly) unsigned long numberOfDisplayCompositedVideoFrames API_UNAVAILABLE(macos, ios, tvos, visionos) API_UNAVAILABLE(watchos);

/*!
 @property		numberOfNonDisplayCompositedFrames
 @abstract		[SPI] The total number of frames that were composited in undetached mode.
 */
@property (nonatomic, readonly) unsigned long numberOfNonDisplayCompositedVideoFrames API_UNAVAILABLE(macos, ios, tvos, visionos) API_UNAVAILABLE(watchos);

/*!
 @property		totalFrameDelay
 @abstract		[SPI] The accumulated amount of time, in microseconds, between the prescribed presentation times of displayed video frames and the actual time at which they were displayed.
 @discussion	This delay is always greater than or equal to zero since frames must never be displayed before their presentation time. Non-zero delays are a sign of playback jitter and possible loss of A/V sync. Same as totalAccumulatedFrameDelay.
 */
@property (nonatomic, readonly) double totalFrameDelay API_UNAVAILABLE(macos, ios, tvos, visionos) API_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVVideoPerformanceMetrics.h>
#endif
