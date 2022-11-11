#if !__has_include(<AVFCore/AVSampleBufferDisplayLayer.h>)
/*
	File:  AVSampleBufferDisplayLayer.h

	Framework:  AVFoundation
 
	Copyright 2011-2021 Apple Inc. All rights reserved.

*/

/*!
    @class			AVSampleBufferDisplayLayer

    @abstract		AVSampleBufferDisplayLayer is a subclass of CALayer that can decompress and display compressed or uncompressed video frames.
*/

#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVAnimation.h>
#import <AVFoundation/AVQueuedSampleBufferRendering.h>

#if __has_include(<QuartzCore/CoreAnimation.h>)
#import <QuartzCore/CoreAnimation.h>
#import <CoreMedia/CMSync.h>
#import <CoreMedia/CMSampleBuffer.h>

NS_ASSUME_NONNULL_BEGIN

@class AVSampleBufferDisplayLayerInternal;

AVF_EXPORT NSString *const AVSampleBufferDisplayLayerFailedToDecodeNotification API_AVAILABLE(macos(10.10), ios(8.0), tvos(10.2)) API_UNAVAILABLE(watchos); // decode failed, see NSError in notification payload
AVF_EXPORT NSString *const AVSampleBufferDisplayLayerFailedToDecodeNotificationErrorKey API_AVAILABLE(macos(10.10), ios(8.0), tvos(10.2)) API_UNAVAILABLE(watchos); // NSError

AVF_EXPORT NSNotificationName const AVSampleBufferDisplayLayerRequiresFlushToResumeDecodingDidChangeNotification API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos); // see requiresFlushToResumeDecoding property
AVF_EXPORT NSNotificationName const AVSampleBufferDisplayLayerOutputObscuredDueToInsufficientExternalProtectionDidChangeNotification API_AVAILABLE(macos(11.3), ios(14.5), tvos(14.5), watchos(7.4)); // see outputObscuredDueToInsufficientExternalProtection property

API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2)) API_UNAVAILABLE(watchos)
@interface AVSampleBufferDisplayLayer : CALayer

/*!
	@property		controlTimebase
	@abstract		The layer's control timebase, which governs how time stamps are interpreted.
	@discussion		By default, this property is NULL, in which case time stamps will be interpreted
					according to the host time clock (mach_absolute_time with the appropriate timescale
					conversion; this is the same as Core Animation's CACurrentMediaTime).  With no 
					control timebase, once frames are enqueued, it is not possible to adjust exactly 
					when they are displayed.
					
					If a non-NULL control timebase is set, it will be used to interpret time stamps.
					You can control the timing of frame display by setting the rate and time of the
					control timebase.  
					If you are synchronizing video to audio, you can use a timebase whose source clock
					is a CMAudioDeviceClock for the appropriate audio device to prevent drift.
					
					Note that prior to OSX 10.10 and iOS 8.0, the control timebase could not be changed after enqueueSampleBuffer: was called.  As of OSX 10.10 and iOS 8.0, the control timebase may be changed at any time.
*/
@property (retain, nullable) __attribute__((NSObject)) CMTimebaseRef controlTimebase;

/*!
	@property		videoGravity
	@abstract		A string defining how the video is displayed within an AVSampleBufferDisplayLayer bounds rect.
	@discusssion	Options are AVLayerVideoGravityResizeAspect, AVLayerVideoGravityResizeAspectFill 
 					and AVLayerVideoGravityResize. AVLayerVideoGravityResizeAspect is default. 
					See <AVFoundation/AVAnimation.h> for a description of these options.
 */
@property(copy) AVLayerVideoGravity videoGravity;

@end


@interface AVSampleBufferDisplayLayer (AVSampleBufferDisplayLayerQueueManagement) <AVQueuedSampleBufferRendering>

/*!
	@property		status
	@abstract		The ability of the display layer to be used for enqueuing sample buffers.
	@discussion		The value of this property is an AVQueuedSampleBufferRenderingStatus that indicates whether the receiver can be used for enqueuing and rendering sample buffers. When the value of this property is AVQueuedSampleBufferRenderingStatusFailed, clients can check the value of the error property to determine the failure. To resume rendering sample buffers using the display layer after a failure, clients must first reset the status to AVQueuedSampleBufferRenderingStatusUnknown. This can be achieved by invoking -flush on the display layer.
		
					This property is key value observable.
 */
@property (nonatomic, readonly) AVQueuedSampleBufferRenderingStatus status API_AVAILABLE(macos(10.10), ios(8.0), tvos(10.2)) API_UNAVAILABLE(watchos);

/*!
	@property		error
	@abstract		If the display layer's status is AVQueuedSampleBufferRenderingStatusFailed, this describes the error that caused the failure.
	@discussion		The value of this property is an NSError that describes what caused the display layer to no longer be able to enqueue sample buffers. If the status is not AVQueuedSampleBufferRenderingStatusFailed, the value of this property is nil.
 */
@property (nonatomic, readonly, nullable) NSError *error API_AVAILABLE(macos(10.10), ios(8.0), tvos(10.2)) API_UNAVAILABLE(watchos);

/*!
	@method			enqueueSampleBuffer:
	@abstract		Sends a sample buffer for display.
	@discussion		If sampleBuffer has the kCMSampleAttachmentKey_DoNotDisplay attachment set to
					kCFBooleanTrue, the frame will be decoded but not displayed.
					Otherwise, if sampleBuffer has the kCMSampleAttachmentKey_DisplayImmediately
					attachment set to kCFBooleanTrue, the decoded image will be displayed as soon 
					as possible, replacing all previously enqueued images regardless of their timestamps.
					Otherwise, the decoded image will be displayed at sampleBuffer's output presentation
					timestamp, as interpreted by the control timebase (or the mach_absolute_time timeline
					if there is no control timebase).
					
					To schedule the removal of previous images at a specific timestamp, enqueue 
					a marker sample buffer containing no samples, with the
					kCMSampleBufferAttachmentKey_EmptyMedia attachment set to kCFBooleanTrue.
					
					IMPORTANT NOTE: attachments with the kCMSampleAttachmentKey_ prefix must be set via
					CMSampleBufferGetSampleAttachmentsArray and CFDictionarySetValue. 
					Attachments with the kCMSampleBufferAttachmentKey_ prefix must be set via
					CMSetAttachment.
 
					IMPORTANT NOTE:  When using CMSampleBuffers that wrap CVPixelBuffer, it is important that such CVPixelBuffers be IOSurface-backed.
					CoreVideo allocates IOSurface-backed CVPixelBuffers when the pixel buffer attribute dictionary passed to CVPixelBufferPoolCreate contains
					an entry with key kCVPixelBufferIOSurfacePropertiesKey and value being a dictionary (which can be an empty dictionary).
 */
- (void)enqueueSampleBuffer:(CMSampleBufferRef)sampleBuffer;

/*!
	@method			flush
	@abstract		Instructs the layer to discard pending enqueued sample buffers.
	@discussion		It is not possible to determine which sample buffers have been decoded, 
					so the next frame passed to enqueueSampleBuffer: should be an IDR frame
					(also known as a key frame or sync sample).
*/
- (void)flush;

/*!
	@method			flushAndRemoveImage
	@abstract		Instructs the layer to discard pending enqueued sample buffers and remove any
					currently displayed image.
	@discussion		It is not possible to determine which sample buffers have been decoded, 
					so the next frame passed to enqueueSampleBuffer: should be an IDR frame
					(also known as a key frame or sync sample).
*/
- (void)flushAndRemoveImage;

/*!
	@property		requiresFlushToResumeDecoding
	@abstract		Indicates that the receiver is in a state where it requires a call to -flush to continue decoding frames.
	@discussion		When the application enters a state where use of video decoder resources is not permissible, the value of this property changes to YES along with the display layer's status changing to AVQueuedSampleBufferRenderingStatusFailed.
					To resume rendering sample buffers using the display layer after this property's value is YES, clients must first reset the display layer's status to AVQueuedSampleBufferRenderingStatusUnknown. This can be achieved by invoking -flush on the display layer.
					Clients can track changes to this property via AVSampleBufferDisplayLayerRequiresFlushToResumeDecodingDidChangeNotification.
					This property is not key value observable.
*/
@property (nonatomic, readonly) BOOL requiresFlushToResumeDecoding API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos);

/*!
	@property		readyForMoreMediaData
	@abstract		Indicates the readiness of the layer to accept more sample buffers.
	@discussion		AVSampleBufferDisplayLayer keeps track of the occupancy levels of its internal queues
					for the benefit of clients that enqueue sample buffers from non-real-time sources --
					i.e., clients that can supply sample buffers faster than they are consumed, and so
					need to decide when to hold back.
					
					Clients enqueueing sample buffers from non-real-time sources may hold off from
					generating or obtaining more sample buffers to enqueue when the value of
					readyForMoreMediaData is NO.  
					
					It is safe to call enqueueSampleBuffer: when readyForMoreMediaData is NO, but 
					it is a bad idea to enqueue sample buffers without bound.
					
					To help with control of the non-real-time supply of sample buffers, such clients can use
					-requestMediaDataWhenReadyOnQueue:usingBlock
					in order to specify a block that the layer should invoke whenever it's ready for 
					sample buffers to be appended.
 
					The value of readyForMoreMediaData will often change from NO to YES asynchronously, 
					as previously supplied sample buffers are decoded and displayed.
	
					This property is not key value observable.
*/
@property (readonly, getter=isReadyForMoreMediaData) BOOL readyForMoreMediaData;

/*!
	@method			requestMediaDataWhenReadyOnQueue:usingBlock:
	@abstract		Instructs the target to invoke a client-supplied block repeatedly, 
					at its convenience, in order to gather sample buffers for display.
	@discussion		The block should enqueue sample buffers to the layer either until the layer's
					readyForMoreMediaData property becomes NO or until there is no more data 
					to supply. When the layer has decoded enough of the media data it has received 
					that it becomes ready for more media data again, it will invoke the block again 
					in order to obtain more.
					If this function is called multiple times, only the last call is effective.
					Call stopRequestingMediaData to cancel this request.
					Each call to requestMediaDataWhenReadyOnQueue:usingBlock: should be paired
					with a corresponding call to stopRequestingMediaData:. Releasing the
					AVSampleBufferDisplayLayer without a call to stopRequestingMediaData will result
					in undefined behavior.
*/
- (void)requestMediaDataWhenReadyOnQueue:(dispatch_queue_t)queue usingBlock:(void (^)(void))block;

/*!
	@method			stopRequestingMediaData
	@abstract		Cancels any current requestMediaDataWhenReadyOnQueue:usingBlock: call.
	@discussion		This method may be called from outside the block or from within the block.
*/
- (void)stopRequestingMediaData;

@end

@interface AVSampleBufferDisplayLayer (AVSampleBufferDisplayLayerImageProtection)

/*!
 @property		preventsCapture
 @abstract		Indicates that image data should be protected from capture.
 */
@property (nonatomic) BOOL preventsCapture API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);

@end

@interface AVSampleBufferDisplayLayer (AVSampleBufferDisplayLayerVideoDisplaySleepPrevention)

/*!
 @property   preventsDisplaySleepDuringVideoPlayback
 @abstract   Indicates whether video playback prevents display and device sleep.
 @discussion
 Default is YES on iOS, tvOS and in Mac Catalyst apps.  Default is NO on macOS.
 Setting this property to NO does not force the display to sleep, it simply stops preventing display sleep.  Other apps or frameworks within your app may still be preventing display sleep for various reasons.
 Note: If sample buffers are being enqueued for playback at the user's request, you should ensure that the value of this property is set to YES. If video is not being displayed as part of the user's primary focus, you should ensure that the value of this property is set to NO.
 */
@property (nonatomic) BOOL preventsDisplaySleepDuringVideoPlayback API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);

@end

@interface AVSampleBufferDisplayLayer (ProtectedContent)

/*!
 @property      outputObscuredDueToInsufficientExternalProtection
 @abstract      Whether or not decoded output is being obscured due to insufficient external protection.
 
 @discussion
	 The value of this property indicates whether the layer is purposefully obscuring its visual output
	 because the requirement for an external protection mechanism is not met by the current device
	 configuration. The change of this property can be observed through AVSampleBufferDisplayLayerOutputObscuredDueToInsufficientExternalProtectionDidChangeNotification
	 
	 It is highly recommended that clients whose content requires external
	 protection observe this property and set the playback rate to zero and display an appropriate user
	 interface when the value changes to YES.
	 
	 Note that the value of this property is dependent on the external protection requirements of the
	 media being displayed by the layer. These requirements are inherent to the content itself and cannot
	 be externally specified. If the content does not require external protection, the value of this
	 property will be NO.
 */
@property (nonatomic, readonly) BOOL outputObscuredDueToInsufficientExternalProtection API_AVAILABLE(macos(11.3), ios(14.5), tvos(14.5)) API_UNAVAILABLE(watchos);
@end

NS_ASSUME_NONNULL_END

#endif  // __has_include(<QuartzCore/CoreAnimation.h>)

#else
#import <AVFCore/AVSampleBufferDisplayLayer.h>
#endif
