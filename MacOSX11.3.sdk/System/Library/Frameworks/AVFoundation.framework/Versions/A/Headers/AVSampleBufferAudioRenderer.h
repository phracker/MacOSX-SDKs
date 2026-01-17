#if !__has_include(<AVFCore/AVSampleBufferAudioRenderer.h>)
/*
	File:  AVSampleBufferAudioRenderer.h

	Framework:  AVFoundation
 
	Copyright 2016-2017 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVQueuedSampleBufferRendering.h>
#import <AVFoundation/AVAudioProcessingSettings.h>

NS_ASSUME_NONNULL_BEGIN

@class AVSampleBufferAudioRendererInternal;

/*
	@class			AVSampleBufferAudioRenderer
	@abstract		AVSampleBufferAudioRenderer can decompress and play compressed or uncompressed audio.
	@discussion
		An instance of AVSampleBufferAudioRenderer must be added to an AVSampleBufferRenderSynchronizer before the first sample buffer is enqueued.
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0))
@interface AVSampleBufferAudioRenderer : NSObject <AVQueuedSampleBufferRendering>
{
@private
	AVSampleBufferAudioRendererInternal *_audioRendererInternal;
}

/*
	@property		status
	@abstract		Indicates the status of the audio renderer.
	@discussion
		A renderer begins with status AVQueuedSampleBufferRenderingStatusUnknown.

		As sample buffers are enqueued for rendering using -enqueueSampleBuffer:, the renderer will transition to either AVQueuedSampleBufferRenderingStatusRendering or AVQueuedSampleBufferRenderingStatusFailed.
					
		If the status is AVQueuedSampleBufferRenderingStatusFailed, check the value of the renderer's error property for information on the error encountered.  This is terminal status from which recovery is not always possible.
		
		This property is key value observable.
*/
@property (nonatomic, readonly) AVQueuedSampleBufferRenderingStatus status;

/*
	@property		error
	@abstract		If the renderer's status is AVQueuedSampleBufferRenderingStatusFailed, this describes the error that caused the failure.
	@discussion
		The value of this property is an NSError that describes what caused the renderer to no longer be able to render sample buffers.  The value of this property is nil unless the value of status is AVQueuedSampleBufferRenderingStatusFailed.
*/
@property (nonatomic, readonly, nullable) NSError *error;

/*!
	@property		audioOutputDeviceUniqueID
	@abstract		Specifies the unique ID of the Core Audio output device used to play audio.
	@discussion
		By default, the value of this property is nil, indicating that the default audio output device is used. Otherwise the value of this property is an NSString containing the unique ID of the Core Audio output device to be used for audio output.

		Core Audio's kAudioDevicePropertyDeviceUID is a suitable source of audio output device unique IDs.
	
		Modifying this property while the timebase's rate is not 0.0 may cause the rate to briefly change to 0.0.
					
		On macOS, the audio device clock may be used as the AVSampleBufferRenderSynchronizer's and all attached AVQueuedSampleBufferRendering's timebase's clocks.  If the audioOutputDeviceUniqueID is modified, the clocks of all these timebases may also change.
 
		If multiple AVSampleBufferAudioRenderers with different values for audioOutputDeviceUniqueID are attached to the same AVSampleBufferRenderSynchronizer, audio may not stay in sync during playback.  To avoid this, ensure that all synchronized AVSampleBufferAudioRenderers are using the same audio output device.
*/
@property (nonatomic, copy, nullable) NSString *audioOutputDeviceUniqueID API_AVAILABLE(macos(10.13)) API_UNAVAILABLE(ios, tvos, watchos);

/*!
	@property		audioTimePitchAlgorithm
	@abstract		Indicates the processing algorithm used to manage audio pitch at varying rates.
	@discussion
		Constants for various time pitch algorithms, e.g. AVAudioTimePitchSpectral, are defined in AVAudioProcessingSettings.h.
	
		The default value on iOS is AVAudioTimePitchAlgorithmLowQualityZeroLatency and on macOS is AVAudioTimePitchAlgorithmTimeDomain.

		If the timebase's rate is not supported by the audioTimePitchAlgorithm, audio will be muted.

		Modifying this property while the timebase's rate is not 0.0 may cause the rate to briefly change to 0.0.
*/
@property (nonatomic, copy) AVAudioTimePitchAlgorithm audioTimePitchAlgorithm;

@end

@interface AVSampleBufferAudioRenderer (AVSampleBufferAudioRendererVolumeControl)

/* 
	@property		volume
	@abstract		Indicates the current audio volume of the AVSampleBufferAudioRenderer.
	@discussion
		A value of 0.0 means "silence all audio", while 1.0 means "play at the full volume of the audio media".
	
		This property should be used for frequent volume changes, for example via a volume knob or fader.
		
		This property is most useful on iOS to control the volume of the AVSampleBufferAudioRenderer relative to other audio output, not for setting absolute volume.
*/
@property (nonatomic) float volume;

/*
	@property		muted
	@abstract		Indicates whether or not audio output of the AVSampleBufferAudioRenderer is muted.
	@discussion
		Setting this property only affects audio muting for the renderer instance and not for the device.
 */
@property (nonatomic, getter=isMuted) BOOL muted;

@end

@interface AVSampleBufferAudioRenderer (AVSampleBufferAudioRendererQueueManagement)

/*!
	@method			flushFromSourceTime:completionHandler:
	@abstract		Flushes enqueued sample buffers with presentation time stamps later than or equal to the specified time.
	@param			completionHandler
		A block that is invoked, possibly asynchronously, after the flush operation completes or fails.
	@discussion
		This method can be used to replace media data scheduled to be rendered in the future, without interrupting playback.  One example of this is when the data that has already been enqueued is from a sequence of two songs and the second song is swapped for a new song.  In this case, this method would be called with the time stamp of the first sample buffer from the second song.  After the completion handler is executed with a YES parameter, media data may again be enqueued with timestamps at the specified time.
 
		If NO is provided to the completion handler, the flush did not succeed and the set of enqueued sample buffers remains unchanged.  A flush can fail becuse the source time was too close to (or earlier than) the current time or because the current configuration of the receiver does not support flushing at a particular time.  In these cases, the caller can choose to flush all enqueued media data by invoking the -flush method.
 */
- (void)flushFromSourceTime:(CMTime)time completionHandler:(void (^)(BOOL flushSucceeded))completionHandler;

/*!
	@constant		AVSampleBufferAudioRendererWasFlushedAutomaticallyNotification
	@abstract		A notification that fires whenever the receiver's enqueued media data has been flushed for a reason other than a call to the -flush method.
	@discussion
		The renderer may flush enqueued media data when the user routes playback to a new destination.  The renderer may also flush enqueued media data when the playback rate of the attached AVSampleBufferRenderSynchronizer is changed (e.g. 1.0 -> 2.0 or 1.0 -> 0.0 -> 2.0), however no flush will occur for normal pauses (non-zero -> 0.0) and resumes (0.0 -> same non-zero rate as before).
 
		When an automatic flush occurs, the attached render synchronizer's timebase will remain running at its current rate.  It is typically best to respond to this notification by enqueueing media data with timestamps starting at the timebase's current time.  To the listener, this will sound similar to muting the audio for a short period of time.  If it is more desirable to ensure that all audio is played than to keep the timeline moving, you may also stop the synchronizer, set the synchronizer's current time to the value of AVSampleBufferAudioRendererFlushTimeKey, start reenqueueing sample buffers with timestamps starting at that time, and restart the synchronizer.  To the listener, this will sound similar to pausing the audio for a short period of time.
 
		This notification is delivered on an arbitrary thread.  If sample buffers are being enqueued with the renderer concurrently with the receipt of this notification, it is possible that one or more sample buffers will remain enqueued in the renderer.  This is generally undesirable, because the sample buffers that remain will likely have timestamps far ahead of the timebase's current time and so won't be rendered for some time.  The best practice is to invoke the -flush method, in a manner that is serialized with enqueueing sample buffers, after receiving this notification and before resuming the enqueueing of sample buffers.
 */
AVF_EXPORT NSNotificationName const AVSampleBufferAudioRendererWasFlushedAutomaticallyNotification API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

	/*!
		@constant		AVSampleBufferAudioRendererFlushTimeKey
		@abstract		The presentation timestamp of the first enqueued sample that was flushed.
		@discussion
			The value of this key is an NSValue wrapping a CMTime.
	 */
	AVF_EXPORT NSString * const AVSampleBufferAudioRendererFlushTimeKey API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVSampleBufferAudioRenderer.h>
#endif
