/*
	File:  AVAudioRecorder.h
	
	Framework:  AVFoundation

	Copyright 2008-2016 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVAudioFormat.h>
#import <Foundation/Foundation.h>
#import <AVFAudio/AVAudioSettings.h>

#if TARGET_OS_IPHONE
#import <AVFAudio/AVAudioSession.h>
#endif // #if TARGET_OS_EMBEDDED

#import <Availability.h>

NS_ASSUME_NONNULL_BEGIN

@protocol AVAudioRecorderDelegate;
@class NSURL, NSError;


API_AVAILABLE(macos(10.7), ios(3.0), watchos(4.0)) API_UNAVAILABLE(tvos) 
@interface AVAudioRecorder : NSObject {
@private
    void *_impl;
}


/* The file type to create can be set through the corresponding settings key. If not set, it will be inferred from the file extension. Will overwrite a file at the specified url if a file exists. */
- (nullable instancetype)initWithURL:(NSURL *)url settings:(NSDictionary<NSString *, id> *)settings error:(NSError **)outError;

/* The file type to create can be set through the corresponding settings key. If not set, it will be inferred from the file extension. Will overwrite a file at the specified url if a file exists. */
- (nullable instancetype)initWithURL:(NSURL *)url format:(AVAudioFormat *)format error:(NSError **)outError API_AVAILABLE(macos(10.12), ios(10.0), watchos(4.0)) API_UNAVAILABLE(tvos);

/* transport control */
/* methods that return BOOL return YES on success and NO on failure. */
- (BOOL)prepareToRecord; /* creates the file and gets ready to record. happens automatically on record. */
- (BOOL)record; /* start or resume recording to file. */
- (BOOL)recordAtTime:(NSTimeInterval)time API_AVAILABLE(macos(10.9), ios(6.0), watchos(4.0)) API_UNAVAILABLE(tvos); /* start recording at specified time in the future. time is an absolute time based on and greater than deviceCurrentTime. */
- (BOOL)recordForDuration:(NSTimeInterval) duration; /* record a file of a specified duration. the recorder will stop when it has recorded this length of audio */
- (BOOL)recordAtTime:(NSTimeInterval)time forDuration:(NSTimeInterval) duration API_AVAILABLE(macos(10.9), ios(6.0), watchos(4.0)) API_UNAVAILABLE(tvos); /* record a file of a specified duration starting at specified time. time is an absolute time based on and greater than deviceCurrentTime. */
- (void)pause; /* pause recording */
- (void)stop; /* stops recording. closes the file. */

- (BOOL)deleteRecording; /* delete the recorded file. recorder must be stopped. returns NO on failure. */

/* properties */

@property(readonly, getter=isRecording) BOOL recording; /* is it recording or not? */

@property(readonly) NSURL *url; /* URL of the recorded file */

/* these settings are fully valid only when prepareToRecord has been called */
@property(readonly) NSDictionary<NSString *, id> *settings;

/* this object is fully valid only when prepareToRecord has been called */
@property(readonly) AVAudioFormat *format API_AVAILABLE(macos(10.12), ios(10.0), watchos(4.0)) API_UNAVAILABLE(tvos);

/* the delegate will be sent messages from the AVAudioRecorderDelegate protocol */ 
@property(assign, nullable) id<AVAudioRecorderDelegate> delegate;

/* get the current time of the recording - only valid while recording */
@property(readonly) NSTimeInterval currentTime;
/* get the device current time - always valid */
@property(readonly) NSTimeInterval deviceCurrentTime API_AVAILABLE(macos(10.9), ios(6.0), watchos(4.0)) API_UNAVAILABLE(tvos);

/* metering */

@property(getter=isMeteringEnabled) BOOL meteringEnabled; /* turns level metering on or off. default is off. */

- (void)updateMeters; /* call to refresh meter values */

- (float)peakPowerForChannel:(NSUInteger)channelNumber; /* returns peak power in decibels for a given channel */
- (float)averagePowerForChannel:(NSUInteger)channelNumber; /* returns average power in decibels for a given channel */

#if TARGET_OS_IPHONE
/* The channels property lets you assign the output to record specific channels as described by AVAudioSession's channels property */
/* This property is nil valued until set. */
/* The array must have the same number of channels as returned by the numberOfChannels property. */
@property(nonatomic, copy, nullable) NSArray<AVAudioSessionChannelDescription *> *channelAssignments API_AVAILABLE(macos(10.9), ios(7.0), watchos(4.0)) API_UNAVAILABLE(tvos); /* Array of AVAudioSessionChannelDescription objects */
#endif

@end


/* A protocol for delegates of AVAudioRecorder */
API_AVAILABLE(macos(10.7), ios(3.0), watchos(4.0)) API_UNAVAILABLE(tvos) 
@protocol AVAudioRecorderDelegate <NSObject>
@optional 

/* audioRecorderDidFinishRecording:successfully: is called when a recording has been finished or stopped. This method is NOT called if the recorder is stopped due to an interruption. */
- (void)audioRecorderDidFinishRecording:(AVAudioRecorder *)recorder successfully:(BOOL)flag;

/* if an error occurs while encoding it will be reported to the delegate. */
- (void)audioRecorderEncodeErrorDidOccur:(AVAudioRecorder *)recorder error:(NSError * __nullable)error;

#if TARGET_OS_IPHONE

/* AVAudioRecorder INTERRUPTION NOTIFICATIONS ARE DEPRECATED - Use AVAudioSession instead. */

/* audioRecorderBeginInterruption: is called when the audio session has been interrupted while the recorder was recording. The recorded file will be closed. */
- (void)audioRecorderBeginInterruption:(AVAudioRecorder *)recorder NS_DEPRECATED_IOS(2_2, 8_0);

/* audioRecorderEndInterruption:withOptions: is called when the audio session interruption has ended and this recorder had been interrupted while recording. */
/* Currently the only flag is AVAudioSessionInterruptionFlags_ShouldResume. */
- (void)audioRecorderEndInterruption:(AVAudioRecorder *)recorder withOptions:(NSUInteger)flags NS_DEPRECATED_IOS(6_0, 8_0);

- (void)audioRecorderEndInterruption:(AVAudioRecorder *)recorder withFlags:(NSUInteger)flags NS_DEPRECATED_IOS(4_0, 6_0);

/* audioRecorderEndInterruption: is called when the preferred method, audioRecorderEndInterruption:withFlags:, is not implemented. */
- (void)audioRecorderEndInterruption:(AVAudioRecorder *)recorder NS_DEPRECATED_IOS(2_2, 6_0);

#endif // TARGET_OS_IPHONE

@end

NS_ASSUME_NONNULL_END
