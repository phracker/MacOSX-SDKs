/*
	File:		AVAudioPlayerNode.h
	Framework:	AVFoundation
	
	Copyright (c) 2014 Apple Inc. All Rights Reserved.
*/

#import <AVFoundation/AVAudioNode.h>
#import <AVFoundation/AVAudioFile.h>
#import <AVFoundation/AVAudioMixing.h>

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
*/
typedef NS_OPTIONS(NSUInteger, AVAudioPlayerNodeBufferOptions) {
    AVAudioPlayerNodeBufferLoops			= 1UL << 0,		// 0x01
	AVAudioPlayerNodeBufferInterrupts		= 1UL << 1,		// 0x02
	AVAudioPlayerNodeBufferInterruptsAtLoop	= 1UL << 2		// 0x04
} NS_AVAILABLE(10_10, 8_0);

/*!
	@class AVAudioPlayerNode
	@abstract Play buffers or segments of audio files.
	@discussion
		AVAudioPlayerNode supports scheduling the playback of @link AVAudioBuffer @/link instances,
		or segments of audio files opened via @link AVAudioFile @/link. Buffers and segments may be
		scheduled at specific points in time, or to play immediately following preceding segments.
	
		FORMATS
		
		Normally, you will want to configure the node's output format with the same number of
		channels as are in the files and buffers to be played. Otherwise, channels will be dropped
		or added as required. It is usually better to use an @link AVAudioMixerNode @/link to
		do this.
	
		Similarly, when playing file segments, the node will sample rate convert if necessary, but
		it is often preferable to configure the node's output sample rate to match that of the file(s)
		and use a mixer to perform the rate conversion.
		
		When playing buffers, there is an implicit assumption that the buffers are at the same
		sample rate as the node's output format.
		
		TIMELINES
	
		The usual @link AVAudioNode @/link sample times (as observed by @link lastRenderTime @/link)
		have an arbitrary zero point. AVAudioPlayerNode superimposes a second "player timeline" on
		top of this, to reflect when the player was started, and intervals during which it was
		paused. The methods @link nodeTimeForPlayerTime: @/link and @link playerTimeForNodeTime: @/link
		convert between the two.

		This class' @link stop @/link method unschedules all previously scheduled buffers and 
		file segments, and returns the player timeline to sample time 0.

		TIMESTAMPS
		
		The "schedule" methods all take an @link AVAudioTime @/link "when" parameter. This is
		interpreted as follows:
		
		1. nil:
			- if there have been previous commands, the new one is played immediately following the
				last one.
			- otherwise, if the node is playing, the event is played in the very near future.
			- otherwise, the command is played at sample time 0.
		2. sample time:
			- relative to the node's start time (which begins at 0 when the node is started).
		3. host time:
			- ignored unless sample time not valid.
		
		ERRORS
		
		The "schedule" methods can fail if:
		
		1. a buffer's channel count does not match that of the node's output format.
		2. a file can't be accessed.
		3. an AVAudioTime specifies neither a valid sample time or host time.
		4. a segment's start frame or frame count is negative.
*/
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface AVAudioPlayerNode : AVAudioNode <AVAudioMixing>

/*! @method scheduleBuffer:error:completionHandler:
	@abstract Schedule playing samples from an AVAudioBuffer.
	@param buffer
		the buffer to play
	@param completionHandler
		called after the buffer has completely played or the player is stopped. may be nil.
	@discussion
		Schedules the buffer to be played following any previously scheduled commands.
*/
- (void)scheduleBuffer:(AVAudioPCMBuffer *)buffer completionHandler:(AVAudioNodeCompletionHandler)completionHandler;

/*! @method scheduleBuffer:atTime:options:error:completionHandler:
	@abstract Schedule playing samples from an AVAudioBuffer.
	@param buffer
		the buffer to play
	@param when 
		the time at which to play the buffer. see the discussion of timestamps, above.
	@param options
		options for looping, interrupting other buffers, etc.
	@param completionHandler
		called after the buffer has completely played or the player is stopped. may be nil.
	@discussion
*/
- (void)scheduleBuffer:(AVAudioPCMBuffer *)buffer atTime:(AVAudioTime *)when options:(AVAudioPlayerNodeBufferOptions)options completionHandler:(AVAudioNodeCompletionHandler)completionHandler;

/*! @method scheduleFile:atTime:error:completionHandler:
	@abstract Schedule playing of an entire audio file.
	@param file
		the file to play
	@param when 
		the time at which to play the file. see the discussion of timestamps, above.
	@param completionHandler
		called after the file has completely played or the player is stopped. may be nil.
*/
- (void)scheduleFile:(AVAudioFile *)file atTime:(AVAudioTime *)when completionHandler:(AVAudioNodeCompletionHandler)completionHandler;

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
		called after the segment has completely played or the player is stopped. may be nil.
*/
- (void)scheduleSegment:(AVAudioFile *)file startingFrame:(AVAudioFramePosition)startFrame frameCount:(AVAudioFrameCount)numberFrames atTime:(AVAudioTime *)when completionHandler:(AVAudioNodeCompletionHandler)completionHandler;

/*!	@method stop
	@abstract Clear all of the node's previously scheduled events and stop playback.
	@discussion
		All of the node's previously scheduled events are cleared, including any that are in the
		middle of playing. The node's sample time (and therefore the times to which new events are 
		to be scheduled) is reset to 0, and will not proceed until the node is started again (via
		play or playAtTime).
*/
- (void)stop;

/*! @method prepareWithFrameCount:
	@abstract Prepares previously scheduled file regions or buffers for playback.
	@param numberFrames
		The number of sample frames of data to be prepared before returning.
	@discussion
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
- (void)playAtTime:(AVAudioTime *)when;

/*! @method pause
	@abstract Pause playback.
	@discussion
		The player's sample time does not advance while the node is paused.
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
		This method and its inverse @link playerTimeForNodeTime: @/link are discussed in the
		introduction to this class.
	
		If the player is not playing when this method is called, nil is returned.
*/
- (AVAudioTime *)nodeTimeForPlayerTime:(AVAudioTime *)playerTime;

/*!	@method playerTimeForNodeTime:
	@abstract
		Convert from node time to player time.
	@param nodeTime
		a node time
	@return
		a time relative to the player's start time
	@discussion
		This method and its inverse @link nodeTimeForPlayerTime: @/link are discussed in the
		introduction to this class.
	
		If the player is not playing when this method is called, nil is returned.
*/
- (AVAudioTime *)playerTimeForNodeTime:(AVAudioTime *)nodeTime;

/*!	@property playing
	@abstract Indicates whether or not the player is playing.
*/
@property(nonatomic, readonly, getter=isPlaying) BOOL playing;


@end

