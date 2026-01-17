/*
	File:		AVAudioPlayerNode.h
	Framework:	AVFoundation
	
	Copyright (c) 2014-2015 Apple Inc. All Rights Reserved.
*/

#import <AVFAudio/AVAudioNode.h>
#import <AVFAudio/AVAudioFile.h>
#import <AVFAudio/AVAudioMixing.h>

NS_ASSUME_NONNULL_BEGIN

@class AVAudioTime;

/*!
	@enum AVAudioPlayerNodeBufferOptions
	@abstract	Options controlling buffer scheduling.
	
	@constant	AVAudioPlayerNodeBufferLoops
					The buffer loops indefinitely.
	@constant	AVAudioPlayerNodeBufferInterrupts
					The buffer interrupts any buffer already playing.
	@constant	AVAudioPlayerNodeBufferInterruptsAtLoop
					The buffer interrupts any buffer already playing, at its loop point.

	API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0))
*/
typedef NS_OPTIONS(NSUInteger, AVAudioPlayerNodeBufferOptions) {
    AVAudioPlayerNodeBufferLoops			= 1UL << 0,		// 0x01
	AVAudioPlayerNodeBufferInterrupts		= 1UL << 1,		// 0x02
	AVAudioPlayerNodeBufferInterruptsAtLoop	= 1UL << 2		// 0x04
};

/*!
	@enum AVAudioPlayerNodeCompletionCallbackType
	@abstract	Specifies when the completion handler must be invoked.

	@constant	AVAudioPlayerNodeCompletionDataConsumed
					The buffer or file data has been consumed by the player.
  	@constant	AVAudioPlayerNodeCompletionDataRendered
					The buffer or file data has been rendered (i.e. output) by the player. This
					does not account for any signal processing latencies downstream of the player 
					in the engine (see `AVAudioNode(outputPresentationLatency)`).
	@constant	AVAudioPlayerNodeCompletionDataPlayedBack
					Applicable only when the engine is rendering to/from an audio device.
					The buffer or file has finished playing. This accounts for both (small) signal 
					processing latencies downstream of the player in the engine, as well as
					(possibly significant) latency in the audio playback device.

 	API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));
 */
typedef NS_ENUM(NSInteger, AVAudioPlayerNodeCompletionCallbackType) {
	AVAudioPlayerNodeCompletionDataConsumed		= 0,
	AVAudioPlayerNodeCompletionDataRendered		= 1,
	AVAudioPlayerNodeCompletionDataPlayedBack	= 2,
};

/*! @typedef AVAudioPlayerNodeCompletionHandler
	@abstract Buffer or file completion callback handler.
	@param callbackType
		Indicates the type of buffer or file completion when the callback is invoked.
	@discussion
		AVAudioPlayerNode issues this callback to inform the client about the specific type of
		buffer or file completion. See `AVAudioPlayerNodeCompletionCallbackType` for more details.
 
		Note that the `AVAudioNodeCompletionHandler` callback from some of the player's scheduling
		methods (e.g. `scheduleBuffer:completionHandler:`) is equivalent to the
		AVAudioPlayerNodeCompletionHandler callback for `AVAudioPlayerNodeCompletionDataConsumed`.
 
		In general the callbacks arrive on a non-main thread and it is the client's responsibility
		to handle them in a thread-safe manner.
*/
typedef void (^AVAudioPlayerNodeCompletionHandler)(AVAudioPlayerNodeCompletionCallbackType callbackType) API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/*!
	@class AVAudioPlayerNode
	@abstract Play buffers or segments of audio files.
	@discussion
		AVAudioPlayerNode supports scheduling the playback of `AVAudioBuffer` instances,
		or segments of audio files opened via `AVAudioFile`. Buffers and segments may be
		scheduled at specific points in time, or to play immediately following preceding segments.
	
		FORMATS
		
		Normally, you will want to configure the node's output format with the same number of
		channels as are in the files and buffers to be played. Otherwise, channels will be dropped
		or added as required. It is usually better to use an `AVAudioMixerNode` to
		do this.
	
		Similarly, when playing file segments, the node will sample rate convert if necessary, but
		it is often preferable to configure the node's output sample rate to match that of the file(s)
		and use a mixer to perform the rate conversion.
		
		When playing buffers, there is an implicit assumption that the buffers are at the same
		sample rate as the node's output format.
		
		TIMELINES
	
		The usual `AVAudioNode` sample times (as observed by `lastRenderTime`)
		have an arbitrary zero point. AVAudioPlayerNode superimposes a second "player timeline" on
		top of this, to reflect when the player was started, and intervals during which it was
		paused. The methods `nodeTimeForPlayerTime:` and `playerTimeForNodeTime:`
		convert between the two.

		This class' `stop` method unschedules all previously scheduled buffers and
		file segments, and returns the player timeline to sample time 0.

		TIMESTAMPS
		
		The "schedule" methods all take an `AVAudioTime` "when" parameter. This is
		interpreted as follows:
		
		1. nil:
			- if there have been previous commands, the new one is played immediately following the
				last one.
			- otherwise, if the node is playing, the event is played in the very near future.
			- otherwise, the command is played at sample time 0.
		2. sample time:
			- relative to the node's start time (which begins at 0 when the node is started).
		3. host time:
			- ignored unless the sample time is invalid when the engine is rendering to an audio 
			  device.
			- ignored in manual rendering mode.
		
		ERRORS
		
		The "schedule" methods can fail if:
		
		1. a buffer's channel count does not match that of the node's output format.
		2. a file can't be accessed.
		3. an AVAudioTime specifies neither a valid sample time or host time.
		4. a segment's start frame or frame count is negative.
 
		BUFFER/FILE COMPLETION HANDLERS
 
		The buffer or file completion handlers (see scheduling methods) are a means to schedule 
		more data if available on the player node. See `AVAudioPlayerNodeCompletionCallbackType` 
		for details on the different buffer/file completion callback types.
		
		Note that a player should not be stopped from within a completion handler callback because
		it can deadlock while trying to unschedule previously scheduled buffers.
 
		OFFLINE RENDERING
	
		When a player node is used with the engine operating in the manual rendering mode, the
		buffer/file completion handlers, `lastRenderTime` and the latencies (`latency` and
		`outputPresentationLatency`) can be used to track how much data the player has rendered and
		how much more data is left to render.
*/
API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0))
@interface AVAudioPlayerNode : AVAudioNode <AVAudioMixing>

- (instancetype)init NS_DESIGNATED_INITIALIZER;

/*! @method scheduleBuffer:completionHandler:
	@abstract Schedule playing samples from an AVAudioBuffer.
	@param buffer
		the buffer to play
	@param completionHandler
		called after the buffer has been consumed by the player or the player is stopped. may be nil.
	@discussion
		Schedules the buffer to be played following any previously scheduled commands.
		
		It is possible for the completionHandler to be called before rendering begins
		or before the buffer is played completely.
*/
- (void)scheduleBuffer:(AVAudioPCMBuffer *)buffer completionHandler:(AVAudioNodeCompletionHandler __nullable)completionHandler;

/*! @method scheduleBuffer:completionCallbackType:completionHandler:
	@abstract Schedule playing samples from an AVAudioBuffer.
	@param buffer
		the buffer to play
	@param callbackType
		option to specify when the completion handler must be called
	@param completionHandler
		called after the buffer has been consumed by the player or has finished playing back or 
		the player is stopped. may be nil.
	@discussion
		Schedules the buffer to be played following any previously scheduled commands.
*/
- (void)scheduleBuffer:(AVAudioPCMBuffer *)buffer completionCallbackType:(AVAudioPlayerNodeCompletionCallbackType)callbackType completionHandler:(AVAudioPlayerNodeCompletionHandler __nullable)completionHandler API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/*! @method scheduleBuffer:atTime:options:completionHandler:
	@abstract Schedule playing samples from an AVAudioBuffer.
	@param buffer
		the buffer to play
	@param when 
		the time at which to play the buffer. see the discussion of timestamps, above.
	@param options
		options for looping, interrupting other buffers, etc.
	@param completionHandler
		called after the buffer has been consumed by the player or the player is stopped. may be nil.
	@discussion
		It is possible for the completionHandler to be called before rendering begins
		or before the buffer is played completely.
*/
- (void)scheduleBuffer:(AVAudioPCMBuffer *)buffer atTime:(AVAudioTime * __nullable)when options:(AVAudioPlayerNodeBufferOptions)options completionHandler:(AVAudioNodeCompletionHandler __nullable)completionHandler;

/*! @method scheduleBuffer:atTime:options:completionCallbackType:completionHandler:
	@abstract Schedule playing samples from an AVAudioBuffer.
	@param buffer
		the buffer to play
	@param when
		the time at which to play the buffer. see the discussion of timestamps, above.
	@param options
		options for looping, interrupting other buffers, etc.
	@param callbackType
		option to specify when the completion handler must be called
	@param completionHandler
		called after the buffer has been consumed by the player or has finished playing back or 
		the player is stopped. may be nil.
*/
- (void)scheduleBuffer:(AVAudioPCMBuffer *)buffer atTime:(AVAudioTime * __nullable)when options:(AVAudioPlayerNodeBufferOptions)options
	 completionCallbackType:(AVAudioPlayerNodeCompletionCallbackType)callbackType completionHandler:(AVAudioPlayerNodeCompletionHandler __nullable)completionHandler API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/*! @method scheduleFile:atTime:completionHandler:
	@abstract Schedule playing of an entire audio file.
	@param file
		the file to play
	@param when 
		the time at which to play the file. see the discussion of timestamps, above.
	@param completionHandler
		called after the file has been consumed by the player or the player is stopped. may be nil.
	@discussion
		It is possible for the completionHandler to be called before rendering begins
		or before the file is played completely.
*/
- (void)scheduleFile:(AVAudioFile *)file atTime:(AVAudioTime * __nullable)when completionHandler:(AVAudioNodeCompletionHandler __nullable)completionHandler;

/*! @method scheduleFile:atTime:completionCallbackType:completionHandler:
	@abstract Schedule playing of an entire audio file.
	@param file
		the file to play
	@param when
		the time at which to play the file. see the discussion of timestamps, above.
	@param callbackType
		option to specify when the completion handler must be called
	@param completionHandler
		called after the file has been consumed by the player or has finished playing back or 
		the player is stopped. may be nil.
*/
- (void)scheduleFile:(AVAudioFile *)file atTime:(AVAudioTime * __nullable)when completionCallbackType:(AVAudioPlayerNodeCompletionCallbackType)callbackType completionHandler:(AVAudioPlayerNodeCompletionHandler __nullable)completionHandler API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/*! @method scheduleSegment:startingFrame:frameCount:atTime:completionHandler:
	@abstract Schedule playing a segment of an audio file.
	@param file
		the file to play
	@param startFrame
		the starting frame position in the stream
	@param numberFrames
		the number of frames to play
	@param when
		the time at which to play the region. see the discussion of timestamps, above.
	@param completionHandler
		called after the segment has been consumed by the player or the player is stopped. may be nil.
	@discussion
		It is possible for the completionHandler to be called before rendering begins
		or before the segment is played completely.
*/
- (void)scheduleSegment:(AVAudioFile *)file startingFrame:(AVAudioFramePosition)startFrame frameCount:(AVAudioFrameCount)numberFrames atTime:(AVAudioTime * __nullable)when completionHandler:(AVAudioNodeCompletionHandler __nullable)completionHandler;

/*! @method scheduleSegment:startingFrame:frameCount:atTime:completionCallbackType:completionHandler:
	@abstract Schedule playing a segment of an audio file.
	@param file
		the file to play
	@param startFrame
		the starting frame position in the stream
	@param numberFrames
		the number of frames to play
	@param when
		the time at which to play the region. see the discussion of timestamps, above.
	@param callbackType
		option to specify when the completion handler must be called
	@param completionHandler
		called after the segment has been consumed by the player or has finished playing back or 
		the player is stopped. may be nil.
*/
- (void)scheduleSegment:(AVAudioFile *)file startingFrame:(AVAudioFramePosition)startFrame frameCount:(AVAudioFrameCount)numberFrames atTime:(AVAudioTime * __nullable)when
	completionCallbackType:(AVAudioPlayerNodeCompletionCallbackType)callbackType completionHandler:(AVAudioPlayerNodeCompletionHandler __nullable)completionHandler API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/*!	@method stop
	@abstract Clear all of the node's previously scheduled events and stop playback.
	@discussion
		All of the node's previously scheduled events are cleared, including any that are in the
		middle of playing. The node's sample time (and therefore the times to which new events are 
		to be scheduled) is reset to 0, and will not proceed until the node is started again (via
		play or playAtTime).
 
		Note that pausing or stopping all the players connected to an engine does not pause or stop
		the engine or the underlying hardware. The engine must be explicitly paused or stopped for
		the hardware to stop.
*/
- (void)stop;

/*! @method prepareWithFrameCount:
	@abstract Prepares previously scheduled file regions or buffers for playback.
	@param frameCount
		The number of sample frames of data to be prepared before returning.
*/		
- (void)prepareWithFrameCount:(AVAudioFrameCount)frameCount;

/*!	@method play
	@abstract Start or resume playback immediately.
	@discussion
		equivalent to playAtTime:nil
*/
- (void)play;

/*!	@method playAtTime:
	@abstract Start or resume playback at a specific time.
	@param when
		the node time at which to start or resume playback. nil signifies "now".
	@discussion
		This node is initially paused. Requests to play buffers or file segments are enqueued, and
		any necessary decoding begins immediately. Playback does not begin, however, until the player
		has started playing, via this method.

 		Note that providing an AVAudioTime which is past (before lastRenderTime) will cause the
 		player to begin playback immediately.

		E.g. To start a player X seconds in future:
<pre>
// start engine and player
NSError *nsErr = nil;
[_engine startAndReturnError:&nsErr];
if (!nsErr) {
	const float kStartDelayTime = 0.5; // sec
	AVAudioFormat *outputFormat = [_player outputFormatForBus:0];
	AVAudioFramePosition startSampleTime = _player.lastRenderTime.sampleTime + kStartDelayTime * outputFormat.sampleRate;
	AVAudioTime *startTime = [AVAudioTime timeWithSampleTime:startSampleTime atRate:outputFormat.sampleRate];
	[_player playAtTime:startTime];
}
</pre>
*/
- (void)playAtTime:(AVAudioTime * __nullable)when;

/*! @method pause
	@abstract Pause playback.
	@discussion
		The player's sample time does not advance while the node is paused.
 
		Note that pausing or stopping all the players connected to an engine does not pause or stop
		the engine or the underlying hardware. The engine must be explicitly paused or stopped for
		the hardware to stop.
*/
- (void)pause;

/*!	@method nodeTimeForPlayerTime:
	@abstract
		Convert from player time to node time.
	@param playerTime
		a time relative to the player's start time
	@return
		a node time
	@discussion
		This method and its inverse `playerTimeForNodeTime:` are discussed in the
		introduction to this class.
	
		If the player is not playing when this method is called, nil is returned.
*/
- (AVAudioTime * __nullable)nodeTimeForPlayerTime:(AVAudioTime *)playerTime;

/*!	@method playerTimeForNodeTime:
	@abstract
		Convert from node time to player time.
	@param nodeTime
		a node time
	@return
		a time relative to the player's start time
	@discussion
		This method and its inverse `nodeTimeForPlayerTime:` are discussed in the
		introduction to this class.
	
		If the player is not playing when this method is called, nil is returned.
*/
- (AVAudioTime * __nullable)playerTimeForNodeTime:(AVAudioTime *)nodeTime;

/*!	@property playing
	@abstract Indicates whether or not the player is playing.
*/
@property(nonatomic, readonly, getter=isPlaying) BOOL playing;


@end

NS_ASSUME_NONNULL_END
