/*
	File:  AVAudioRecorder.h
	
	Framework:  AVFoundation

	Copyright 2008-2012 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVBase.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>  /* for NSTimeInterval */
#import <AVFoundation/AVAudioSettings.h>
#import <Availability.h>

@protocol AVAudioRecorderDelegate;
@class NSDictionary, NSURL, NSError;

NS_CLASS_AVAILABLE(10_7, 3_0)
@interface AVAudioRecorder : NSObject {
@private
    __strong void *_impl;
}


/* The file type to record is inferred from the file extension. Will overwrite a file at the specified url if a file exists */
- (id)initWithURL:(NSURL *)url settings:(NSDictionary *)settings error:(NSError **)outError;

/* transport control */
/* methods that return BOOL return YES on success and NO on failure. */
- (BOOL)prepareToRecord; /* creates the file and gets ready to record. happens automatically on record. */
- (BOOL)record; /* start or resume recording to file. */
- (BOOL)recordForDuration: (NSTimeInterval) duration; /* record a file of a specified duration. the recorder will stop when it has recorded this length of audio */
- (void)pause; /* pause recording */
- (void)stop; /* stops recording. closes the file. */

- (BOOL)deleteRecording; /* delete the recorded file. recorder must be stopped. returns NO on failure. */

/* properties */

@property(readonly, getter=isRecording) BOOL recording; /* is it recording or not? */

@property(readonly) NSURL *url; /* URL of the recorded file */

/* these settings are fully valid only when prepareToRecord has been called */
@property(readonly) NSDictionary *settings;

/* the delegate will be sent messages from the AVAudioRecorderDelegate protocol */ 
@property(assign) id<AVAudioRecorderDelegate> delegate;  

/* get the current time of the recording - only valid while recording */
@property(readonly) NSTimeInterval currentTime;

/* metering */

@property(getter=isMeteringEnabled) BOOL meteringEnabled; /* turns level metering on or off. default is off. */

- (void)updateMeters; /* call to refresh meter values */

- (float)peakPowerForChannel:(NSUInteger)channelNumber; /* returns peak power in decibels for a given channel */
- (float)averagePowerForChannel:(NSUInteger)channelNumber; /* returns average power in decibels for a given channel */

@end


/* A protocol for delegates of AVAudioRecorder */
@protocol AVAudioRecorderDelegate <NSObject>
@optional 

/* audioRecorderDidFinishRecording:successfully: is called when a recording has been finished or stopped. This method is NOT called if the recorder is stopped due to an interruption. */
- (void)audioRecorderDidFinishRecording:(AVAudioRecorder *)recorder successfully:(BOOL)flag;

/* if an error occurs while encoding it will be reported to the delegate. */
- (void)audioRecorderEncodeErrorDidOccur:(AVAudioRecorder *)recorder error:(NSError *)error;

#if TARGET_OS_IPHONE

/* audioRecorderBeginInterruption: is called when the audio session has been interrupted while the recorder was recording. The recorder will have been paused. */
- (void)audioRecorderBeginInterruption:(AVAudioRecorder *)recorder;

/* audioRecorderEndInterruption:withFlags: is called when the audio session interruption has ended and this recorder had been interrupted while recording. */
/* Currently the only flag is AVAudioSessionInterruptionFlags_ShouldResume. */
- (void)audioRecorderEndInterruption:(AVAudioRecorder *)recorder withFlags:(NSUInteger)flags NS_AVAILABLE_IOS(4_0);

/* audioRecorderEndInterruption: is called when the preferred method, audioRecorderEndInterruption:withFlags:, is not implemented. */
- (void)audioRecorderEndInterruption:(AVAudioRecorder *)recorder;

#endif // TARGET_OS_IPHONE

@end

