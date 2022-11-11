/*
	File:  AVAudioPlayer.h
	
	Framework:  AVFoundation

	Copyright 2008-2016 Apple Inc. All rights reserved.
*/

#import <AVFAudio/AVAudioFormat.h>
#import <AVFAudio/AVAudioSettings.h>
#if __has_include(<AVFAudio/AVAudioSession.h>)
#import <AVFAudio/AVAudioSession.h>
#endif

NS_ASSUME_NONNULL_BEGIN

@class NSData, NSURL, NSError;
@class AVAudioSessionChannelDescription;
@protocol AVAudioPlayerDelegate;

API_AVAILABLE(macos(10.7), ios(2.2), watchos(3.0), tvos(9.0))
@interface AVAudioPlayer : NSObject {
@private
	id _impl;
}

/* For all of these init calls, if a return value of nil is given you can check outError to see what the problem was.
 If not nil, then the object is usable for playing
*/

/* all data must be in the form of an audio file understood by CoreAudio */
- (nullable instancetype)initWithContentsOfURL:(NSURL *)url error:(NSError **)outError;
- (nullable instancetype)initWithData:(NSData *)data error:(NSError **)outError;

/* The file type hint is a constant defined in AVMediaFormat.h whose value is a UTI for a file format. e.g. AVFileTypeAIFF. */
/* Sometimes the type of a file cannot be determined from the data, or it is actually corrupt. The file type hint tells the parser what kind of data to look for so that files which are not self identifying or possibly even corrupt can be successfully parsed. */
- (nullable instancetype)initWithContentsOfURL:(NSURL *)url fileTypeHint:(NSString * __nullable)utiString error:(NSError **)outError API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));
- (nullable instancetype)initWithData:(NSData *)data fileTypeHint:(NSString * __nullable)utiString error:(NSError **)outError API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));

/* Transport control */
/* Methods that return BOOL return YES on success and NO on failure. */
/* Get ready to play the sound. This happens automatically on play. */
- (BOOL)prepareToPlay;

/* This method starts the audio hardware synchronously (if not already running), and triggers the sound playback which is streamed asynchronously. */
- (BOOL)play;

/* This method starts the audio hardware synchronously (if not already running), and triggers the sound playback which is streamed asynchronously at the specified time in the future.
 Time is an absolute time based on and greater than deviceCurrentTime. */
- (BOOL)playAtTime:(NSTimeInterval)time API_AVAILABLE(macos(10.7), ios(4.0), watchos(2.0), tvos(9.0));

/* Pauses playback, but remains ready to play. */
- (void)pause;

/* Synchronously stops playback, no longer ready to play.
 NOTE: - This will block while releasing the audio hardware that was acquired upon calling play() or prepareToPlay() */
- (void)stop;

/* properties */

@property(readonly, getter=isPlaying) BOOL playing; /* is it playing or not? */

@property(readonly) NSUInteger numberOfChannels;
@property(readonly) NSTimeInterval duration; /* the duration of the sound. */

/* the UID of the current audio device (as a string) */
@property(copy, nullable) NSString *currentDevice API_AVAILABLE(macos(10.13)) API_UNAVAILABLE(ios, watchos, tvos);

/* the delegate will be sent messages from the AVAudioPlayerDelegate protocol */ 
@property(weak, nullable) id<AVAudioPlayerDelegate> delegate;

/* one of these properties will be non-nil based on the init... method used */
@property(readonly, nullable) NSURL *url; /* returns nil if object was not created with a URL */
@property(readonly, nullable) NSData *data; /* returns nil if object was not created with a data object */

@property float pan API_AVAILABLE(macos(10.7), ios(4.0), watchos(2.0), tvos(9.0)); /* set panning. -1.0 is left, 0.0 is center, 1.0 is right. */
@property float volume; /* The volume for the sound. The nominal range is from 0.0 to 1.0. */
- (void)setVolume:(float)volume fadeDuration:(NSTimeInterval)duration API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0)); /* fade to a new volume over a duration */

@property BOOL enableRate API_AVAILABLE(macos(10.8), ios(5.0), watchos(2.0), tvos(9.0)); /* You must set enableRate to YES for the rate property to take effect. You must set this before calling prepareToPlay. */
@property float rate API_AVAILABLE(macos(10.8), ios(5.0), watchos(2.0), tvos(9.0)); /* See enableRate. The playback rate for the sound. 1.0 is normal, 0.5 is half speed, 2.0 is double speed. */


/*  If the sound is playing, currentTime is the offset into the sound of the current playback position.  
If the sound is not playing, currentTime is the offset into the sound where playing would start. */
@property NSTimeInterval currentTime;

/* returns the current time associated with the output device */
@property(readonly) NSTimeInterval deviceCurrentTime API_AVAILABLE(macos(10.7), ios(4.0), watchos(2.0), tvos(9.0));

/* "numberOfLoops" is the number of times that the sound will return to the beginning upon reaching the end. 
A value of zero means to play the sound just once.
A value of one will result in playing the sound twice, and so on..
Any negative number will loop indefinitely until stopped.
*/
@property NSInteger numberOfLoops;

/* settings */
@property(readonly) NSDictionary<NSString *, id> *settings API_AVAILABLE(macos(10.7), ios(4.0), watchos(2.0), tvos(9.0)); /* returns a settings dictionary with keys as described in AVAudioSettings.h */

/* returns the format of the audio data */
@property(readonly) AVAudioFormat *format API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/* metering */

@property(getter=isMeteringEnabled) BOOL meteringEnabled; /* turns level metering on or off. default is off. */

- (void)updateMeters; /* call to refresh meter values */

- (float)peakPowerForChannel:(NSUInteger)channelNumber; /* returns peak power in decibels for a given channel */
- (float)averagePowerForChannel:(NSUInteger)channelNumber; /* returns average power in decibels for a given channel */

/* The channels property lets you assign the output to play to specific channels as described by AVAudioSession's channels property */
/* This property is nil valued until set. */
/* The array must have the same number of channels as returned by the numberOfChannels property. */
@property(nonatomic, copy, nullable) NSArray<AVAudioSessionChannelDescription *> *channelAssignments API_AVAILABLE(ios(7.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos) ; /* Array of AVAudioSessionChannelDescription objects */

@end

/* A protocol for delegates of AVAudioPlayer */
__WATCHOS_AVAILABLE(3_0)
@protocol AVAudioPlayerDelegate <NSObject>
@optional 
/* audioPlayerDidFinishPlaying:successfully: is called when a sound has finished playing. This method is NOT called if the player is stopped due to an interruption. */
- (void)audioPlayerDidFinishPlaying:(AVAudioPlayer *)player successfully:(BOOL)flag;

/* if an error occurs while decoding it will be reported to the delegate. */
- (void)audioPlayerDecodeErrorDidOccur:(AVAudioPlayer *)player error:(NSError * __nullable)error;

#if TARGET_OS_IPHONE

/* AVAudioPlayer INTERRUPTION NOTIFICATIONS ARE DEPRECATED - Use AVAudioSession instead. */

/* audioPlayerBeginInterruption: is called when the audio session has been interrupted while the player was playing. The player will have been paused. */
- (void)audioPlayerBeginInterruption:(AVAudioPlayer *)player NS_DEPRECATED_IOS(2_2, 8_0);

/* audioPlayerEndInterruption:withOptions: is called when the audio session interruption has ended and this player had been interrupted while playing. */
/* Currently the only flag is AVAudioSessionInterruptionFlags_ShouldResume. */
- (void)audioPlayerEndInterruption:(AVAudioPlayer *)player withOptions:(NSUInteger)flags NS_DEPRECATED_IOS(6_0, 8_0);

- (void)audioPlayerEndInterruption:(AVAudioPlayer *)player withFlags:(NSUInteger)flags NS_DEPRECATED_IOS(4_0, 6_0);

/* audioPlayerEndInterruption: is called when the preferred method, audioPlayerEndInterruption:withFlags:, is not implemented. */
- (void)audioPlayerEndInterruption:(AVAudioPlayer *)player NS_DEPRECATED_IOS(2_2, 6_0);

#endif // TARGET_OS_IPHONE

@end

NS_ASSUME_NONNULL_END
