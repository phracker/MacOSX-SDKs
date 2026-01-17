/*
	File:  AVQueuedSampleBufferRendering.h

	Framework:  AVFoundation
 
	Copyright 2013-2017 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <CoreMedia/CMSampleBuffer.h>
#import <CoreMedia/CMSync.h>

NS_ASSUME_NONNULL_BEGIN

/*!
	@enum		 AVQueuedSampleBufferRenderingStatus
	@abstract	 These constants are the possible status values for queued sample buffer renderers.
	@constant	 AVQueuedSampleBufferRenderingStatusUnknown
		Indicates that the receiver is in a fresh state without any sample buffers enqueued on it.
	@constant	 AVQueuedSampleBufferRenderingStatusRendering
		Indicates at least one sample buffer has been enqueued on the receiver.
	@constant	 AVQueuedSampleBufferRenderingStatusFailed
		Indicates that the receiver cannot currently enqueue or render sample buffers because of an error.
 */
typedef NS_ENUM(NSInteger, AVQueuedSampleBufferRenderingStatus) {
	AVQueuedSampleBufferRenderingStatusUnknown,
	AVQueuedSampleBufferRenderingStatusRendering,
	AVQueuedSampleBufferRenderingStatusFailed
} API_AVAILABLE(macos(10.10), ios(8.0), tvos(10.2)) __WATCHOS_PROHIBITED;

/*
	@protocol		AVQueuedSampleBufferRendering
	@abstract		Defines methods for enqueueing CMSampleBuffers for presentation.
	@discussion
		AVSampleBufferDisplayLayer and AVSampleBufferAudioRenderer conform to this protocol.  When used in conjunction with an AVSampleBufferRenderSynchronizer, an object conforming to AVQueuedSampleBufferRendering can only be attached to a single synchronizer.
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0)) __WATCHOS_PROHIBITED
@protocol AVQueuedSampleBufferRendering <NSObject>

/*!
	@property		timebase
	@abstract		The renderer's timebase, which governs how time stamps are interpreted.
	@discussion
		The timebase is used to interpret time stamps.
 
		The timebase is read-only.  Use the AVSampleBufferRenderSynchronizer to set the rate or time.
*/
@property (retain, readonly) __attribute__((NSObject)) CMTimebaseRef timebase;

/*!
	@method			enqueueSampleBuffer:
	@abstract		Sends a sample buffer in order to render its contents.
	@discussion
		Video-specific notes:
	
		If sampleBuffer has the kCMSampleAttachmentKey_DoNotDisplay attachment set to kCFBooleanTrue, the frame will be decoded but not displayed.  Otherwise, if sampleBuffer has the kCMSampleAttachmentKey_DisplayImmediately attachment set to kCFBooleanTrue, the decoded image will be displayed as soon as possible, replacing all previously enqueued images regardless of their timestamps.  Otherwise, the decoded image will be displayed at sampleBuffer's output presentation timestamp, as interpreted by the timebase.
					
		To schedule the removal of previous images at a specific timestamp, enqueue a marker sample buffer containing no samples, with the kCMSampleBufferAttachmentKey_EmptyMedia attachment set to kCFBooleanTrue.
					
		IMPORTANT NOTE: attachments with the kCMSampleAttachmentKey_ prefix must be set via CMSampleBufferGetSampleAttachmentsArray and CFDictionarySetValue.  Attachments with the kCMSampleBufferAttachmentKey_ prefix must be set via CMSetAttachment.
*/
- (void)enqueueSampleBuffer:(CMSampleBufferRef)sampleBuffer;

/*!
	@method			flush
	@abstract		Instructs the receiver to discard pending enqueued sample buffers.
	@discussion
		Additional sample buffers can be appended after -flush.
	
		Video-specific notes:
					
		It is not possible to determine which sample buffers have been decoded, so the next frame passed to enqueueSampleBuffer: should be an IDR frame (also known as a key frame or sync sample).
*/
- (void)flush;

/*!
	@property		readyForMoreMediaData
	@abstract		Indicates the readiness of the receiver to accept more sample buffers.
	@discussion
		An object conforming to AVQueuedSampleBufferRendering keeps track of the occupancy levels of its internal queues for the benefit of clients that enqueue sample buffers from non-real-time sources -- i.e., clients that can supply sample buffers faster than they are consumed, and so need to decide when to hold back.
					
		Clients enqueueing sample buffers from non-real-time sources may hold off from generating or obtaining more sample buffers to enqueue when the value of readyForMoreMediaData is NO.
					
		It is safe to call enqueueSampleBuffer: when readyForMoreMediaData is NO, but it is a bad idea to enqueue sample buffers without bound.
					
		To help with control of the non-real-time supply of sample buffers, such clients can use -requestMediaDataWhenReadyOnQueue:usingBlock in order to specify a block that the receiver should invoke whenever it's ready for sample buffers to be appended.
 
		The value of readyForMoreMediaData will often change from NO to YES asynchronously, as previously supplied sample buffers are decoded and rendered.
	
		This property is not key value observable.
*/
@property (readonly, getter=isReadyForMoreMediaData) BOOL readyForMoreMediaData;

/*!
	@method			requestMediaDataWhenReadyOnQueue:usingBlock:
	@abstract		Instructs the target to invoke a client-supplied block repeatedly, at its convenience, in order to gather sample buffers for playback.
	@discussion
		The block should enqueue sample buffers to the receiver either until the receiver's readyForMoreMediaData property becomes NO or until there is no more data to supply. When the receiver has decoded enough of the media data it has received that it becomes ready for more media data again, it will invoke the block again in order to obtain more.

		If this method is called multiple times, only the last call is effective. Call stopRequestingMediaData to cancel this request.

		Each call to requestMediaDataWhenReadyOnQueue:usingBlock: should be paired with a corresponding call to stopRequestingMediaData:. Releasing the AVQueuedSampleBufferRendering object without a call to stopRequestingMediaData will result in undefined behavior.
*/
- (void)requestMediaDataWhenReadyOnQueue:(dispatch_queue_t)queue usingBlock:(void (^)(void))block;

/*!
	@method			stopRequestingMediaData
	@abstract		Cancels any current requestMediaDataWhenReadyOnQueue:usingBlock: call.
	@discussion
		This method may be called from outside the block or from within the block.
*/
- (void)stopRequestingMediaData;

@end

NS_ASSUME_NONNULL_END
