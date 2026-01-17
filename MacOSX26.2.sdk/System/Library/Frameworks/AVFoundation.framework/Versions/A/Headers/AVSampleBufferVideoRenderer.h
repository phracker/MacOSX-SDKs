#if !__has_include(<AVFCore/AVSampleBufferVideoRenderer.h>)
/*
	File:  AVSampleBufferVideoRenderer.h

	Framework:  AVFoundation
 
	Copyright 2023 Apple Inc. All rights reserved.

*/

/*!
	@class			AVSampleBufferVideoRenderer

	@abstract		AVSampleBufferVideoRenderer provides a mechanism to enqueue sample buffers for rendering.
*/

#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVQueuedSampleBufferRendering.h>

@class AVVideoPerformanceMetrics;

NS_ASSUME_NONNULL_BEGIN

AVF_EXPORT NSNotificationName const AVSampleBufferVideoRendererDidFailToDecodeNotification API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), visionos(1.0)) API_UNAVAILABLE(watchos); // decode failed, see NSError in notification payload
AVF_EXPORT NSString *const AVSampleBufferVideoRendererDidFailToDecodeNotificationErrorKey API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), visionos(1.0)) API_UNAVAILABLE(watchos); // NSError

AVF_EXPORT NSNotificationName const AVSampleBufferVideoRendererRequiresFlushToResumeDecodingDidChangeNotification API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), visionos(1.0)) API_UNAVAILABLE(watchos); // see requiresFlushToResumeDecoding property

API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface AVSampleBufferVideoRenderer : NSObject <AVQueuedSampleBufferRendering>

/*!
	@property		status
	@abstract		The ability of the video renderer to be used for enqueueing sample buffers.
	@discussion		The value of this property is an AVQueuedSampleBufferRenderingStatus that indicates whether the receiver can be used for enqueueing and rendering sample buffers. When the value of this property is AVQueuedSampleBufferRenderingStatusFailed, clients can check the value of the error property to determine the failure. To resume rendering sample buffers using the video renderer after a failure, clients must first reset the status to AVQueuedSampleBufferRenderingStatusUnknown. This can be achieved by invoking -flush on the video renderer.
					This property is key value observable.
*/
@property (readonly) AVQueuedSampleBufferRenderingStatus status;

/*!
	@property		error
	@abstract		If the video renderer's status is AVQueuedSampleBufferRenderingStatusFailed, this describes the error that caused the failure.
	@discussion		The value of this property is an NSError that describes what caused the video renderer to no longer be able to enqueue sample buffers. If the status is not AVQueuedSampleBufferRenderingStatusFailed, the value of this property is nil.
*/
@property (readonly, nullable) NSError *error;

/*!
	@property		requiresFlushToResumeDecoding
	@abstract		Indicates that the receiver is in a state where it requires a call to -flush to continue decoding frames.
	@discussion		When the application enters a state where use of video decoder resources is not permissible, the value of this property changes to YES along with the video renderer's status changing to AVQueuedSampleBufferRenderingStatusFailed.
					To resume rendering sample buffers using the video renderer after this property's value is YES, clients must first reset the video renderer by calling flush or flushWithRemovalOfDisplayedImage:completionHandler:.
					Clients can track changes to this property via AVSampleBufferVideoRendererRequiresFlushToResumeDecodingDidChangeNotification.
					This property is not key value observable.
*/
@property (readonly) BOOL requiresFlushToResumeDecoding;

/*!
	@method			flushWithRemovalOfDisplayedImage:completionHandler:
	@abstract		Instructs the video renderer to discard pending enqueued sample buffers and call the provided block when complete.
	@param			removeDisplayedImage
					Set YES to remove any currently displayed image, NO to preserve any current image.
	@param			handler
					The handler to invoke when flush operation is complete. May be nil.
	@discussion		A flush resets decoder state. The next frame passed to enqueueSampleBuffer: should be an IDR frame (also known as a key frame or sync sample).
*/

- (void)flushWithRemovalOfDisplayedImage:(BOOL)removeDisplayedImage completionHandler:(nullable void (^ NS_SWIFT_SENDABLE)(void))handler;

@end

API_AVAILABLE(macos(14.4), ios(17.4), tvos(17.4), visionos(1.1)) API_UNAVAILABLE(watchos)
@interface AVSampleBufferVideoRenderer (AVSampleBufferVideoRendererPixelBufferOutput)
/*!
	@method			copyDisplayedPixelBuffer
	@abstract		Returns a retained reference to the pixel buffer currently displayed in the AVSampleBufferVideoRenderer's target. This will return NULL if the displayed pixel buffer is protected, no image is currently being displayed, or if the image is unavailable.
	@discussion		This will return NULL if the rate is non-zero.  Clients must release the pixel buffer after use.
			
					Do not write to the returned CVPixelBuffer's attachments or pixel data.
 */
- (nullable CVPixelBufferRef)copyDisplayedPixelBuffer CF_RETURNS_RETAINED API_AVAILABLE(macos(14.4), ios(17.4), tvos(17.4), visionos(1.1)) API_UNAVAILABLE(watchos);

@end

API_AVAILABLE(macos(14.4), ios(17.4), tvos(17.4), visionos(1.1)) API_UNAVAILABLE(watchos)
@interface AVSampleBufferVideoRenderer (AVSampleBufferVideoRendererPowerOptimization)

/*!
	@method			expectMinimumUpcomingSampleBufferPresentationTime:
	@abstract		Promises, for the purpose of enabling power optimizations, that future sample buffers will have PTS values no less than a specified lower-bound PTS.
	@discussion		Only applicable for forward playback.
					Sending this message and later calling -enqueueSampleBuffer: with a buffer with a lower PTS has the potential to lead to dropping that later buffer.
					For best results, call -expectMinimumUpcomingSampleBufferPresentationTime: regularly, in between calls to -enqueueSampleBuffer:, to advance the lower-bound PTS.
					Messaging -flush resets such expectations.
					(For example, it's OK to make this expectation, then in response to a seek back, flush and then enqueue buffers with lower PTS values.)
	@param			minimumUpcomingPresentationTime
					A lower bound on PTS values for buffers that will be passed to -enqueueSampleBuffer: in the future.
*/
- (void)expectMinimumUpcomingSampleBufferPresentationTime:(CMTime)minimumUpcomingPresentationTime NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.4), ios(17.4), tvos(17.4), visionos(1.1)) API_UNAVAILABLE(watchos);


/*!
	@method			expectMonotonicallyIncreasingUpcomingSampleBufferPresentationTimes
	@abstract		Promises, for the purpose of enabling power optimizations, that future sample buffers will have monotonically increasing PTS values.
	@discussion		Only applicable for forward playback.
					Sending this message and later calling -enqueueSampleBuffer: with a buffer with a lower PTS than any previously enqueued PTS has the potential to lead to dropped buffers.
					Messaging -flush resets such expectations.
*/
- (void)expectMonotonicallyIncreasingUpcomingSampleBufferPresentationTimes NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.4), ios(17.4), tvos(17.4), visionos(1.1)) API_UNAVAILABLE(watchos);

/*!
	@method			resetUpcomingSampleBufferPresentationTimeExpectations:
	@abstract		Resets previously-promised expectations about upcoming sample buffer PTSs.
	@discussion		This undoes the state set by messaging -expectMinimumUpcomingSampleBufferPresentationTime: or -expectMonotonicallyIncreasingUpcomingSampleBufferPresentationTimes.
					If you didn't use either of those, you don't have to use this.
*/
- (void)resetUpcomingSampleBufferPresentationTimeExpectations NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.4), ios(17.4), tvos(17.4), visionos(1.1)) API_UNAVAILABLE(watchos);

/*!
	@property		recommendedPixelBufferAttributes
	@abstract		Recommended pixel buffer attributes for optimal performance when using CMSampleBuffers containing CVPixelBuffers.
	@discussion		The returned dictionary does not contain all of the attributes needed for creating pixel buffers.
					Use ``CVPixelBufferCreateResolvedAttributesDictionary()`` to reconcile these attributes with the pixel buffer creation attributes.
*/
@property (readonly, nonnull) NSDictionary<NSString*, NS_SWIFT_SENDABLE id> *recommendedPixelBufferAttributes NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);

@end

API_AVAILABLE(macos(14.4), ios(17.4), tvos(17.4), visionos(1.1)) API_UNAVAILABLE(watchos)
@interface AVSampleBufferVideoRenderer (AVSampleBufferVideoRendererVideoPerformanceMetrics)

/*!
	@method			loadVideoPerformanceMetricsWithCompletionHandler:
	@abstract		Gathers a snapshot of the video performance metrics and calls the completion handler with the results.
	@param			completionHandler
					The handler to invoke with the video performance metrics.
	@discussion		If there are no performance metrics available, the completion handler will be called with nil videoPerformanceMetrics.
*/
- (void)loadVideoPerformanceMetricsWithCompletionHandler:(void (^ NS_SWIFT_SENDABLE)(AVVideoPerformanceMetrics * _Nullable_result videoPerformanceMetrics))completionHandler NS_SWIFT_ASYNC_NAME(getter:videoPerformanceMetrics()) API_AVAILABLE(macos(14.4), ios(17.4), tvos(17.4), visionos(1.1)) API_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVSampleBufferVideoRenderer.h>
#endif
