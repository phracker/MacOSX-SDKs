/*
	File:  AVAudioRecorder.h
	
	Framework:  AVFoundation

	Copyright 2008-2023 Apple Inc. All rights reserved.
*/

#import <AVFAudio/AVAudioFormat.h>
#import <AVFAudio/AVAudioSettings.h>
#import <AVFAudio/AVAudioSession.h>

NS_ASSUME_NONNULL_BEGIN

@protocol AVAudioRecorderDelegate;
@class NSURL, NSError;

/*!
    @class AVAudioRecorder
    @abstract An object that records audio data to a file.
 */
NS_SWIFT_SENDABLE 
API_AVAILABLE(macos(10.7), ios(3.0), watchos(4.0), tvos(17.0))
@interface AVAudioRecorder : NSObject {
@private
    void *_impl;
}

/*!
    @method initWithURL:settings:error:
    @abstract Init the AudioRecorder with a specified url and settings.
    @discussion The file type to create can be set through the corresponding settings key. If not set, it will be inferred from the file extension. Will overwrite a file at the specified url if a file exists.
 */
- (nullable instancetype)initWithURL:(NSURL *)url settings:(NSDictionary<NSString *, id> *)settings error:(NSError **)outError;

/*!
    @method initWithURL:format:error:
    @abstract Init the AudioRecorder with a specified url and format.
    @discussion The file type to create can be set through the corresponding settings key. If not set, it will be inferred from the file extension. Will overwrite a file at the specified url if a file exists.
 */
- (nullable instancetype)initWithURL:(NSURL *)url format:(AVAudioFormat *)format error:(NSError **)outError API_AVAILABLE(macos(10.12), ios(10.0), watchos(4.0), tvos(17.0));

/* transport control */
/* methods that return BOOL return YES on success and NO on failure. */

/*!
    @method prepareToRecord
    @abstract Creates the output file and gets ready to record.
    @discussion This method is called automatically on record. Returns YES on success and NO on failure.
 */
- (BOOL)prepareToRecord;

/*!
    @method record
    @abstract Start or resume recording to file.
    @discussion Returns YES on success and NO on failure.
 */
- (BOOL)record;

/*!
    @method recordAtTime:
    @abstract Start recording at specified time in the future.
    @discussion Time is an absolute time based on and greater than deviceCurrentTime. Returns YES on success and NO on failure.
 */
- (BOOL)recordAtTime:(NSTimeInterval)time API_AVAILABLE(macos(10.9), ios(6.0), watchos(4.0), tvos(17.0));

/*!
    @method recordForDuration:
    @abstract Record for a specified duration.
    @discussion The recorder will stop when it has recorded this length of audio. Returns YES on success and NO on failure.
 */
- (BOOL)recordForDuration:(NSTimeInterval) duration;

/*!
    @method recordAtTime:forDuration:
    @abstract Record for a specified duration at a specified time in the future.
    @discussion Time is an absolute time based on and greater than deviceCurrentTime. Returns YES on success and NO on failure.
 */
- (BOOL)recordAtTime:(NSTimeInterval)time forDuration:(NSTimeInterval) duration API_AVAILABLE(macos(10.9), ios(6.0), watchos(4.0), tvos(17.0));

/*!
    @method pause
    @abstract Pause recording.
 */
- (void)pause;

/*!
    @method stop
    @abstract Stop recording.
    @discussion This method also closes the output file.
 */
- (void)stop;

/*!
    @method deleteRecording
    @abstract Delete the recorded file.
    @discussion AudioRecorder must be stopped. Returns YES on success and NO on failure.
 */
- (BOOL)deleteRecording;

/* properties */

/*!
    @property recording
    @abstract Returns YES if the AudioRecorder is currently recording.
 */
@property(readonly, getter=isRecording) BOOL recording;

/*!
    @property url
    @abstract URL of the recorded file.
 */
@property(readonly) NSURL *url;

/*!
    @property settings
    @abstract A dictionary of settings for the AudioRecorder.
    @discussion These settings are fully valid only when prepareToRecord has been called. For supported key-value pairs, see https://developer.apple.com/documentation/avfaudio/avaudiorecorder/1388386-initwithurl?language=objc
 */
@property(readonly) NSDictionary<NSString *, id> *settings;

/*!
    @property format
    @abstract The audio format of the AudioRecorder.
    @discussion This property is fully valid only when prepareToRecord has been called.
 */
@property(readonly) AVAudioFormat *format API_AVAILABLE(macos(10.12), ios(10.0), watchos(4.0), tvos(17.0));

/*!
    @property delegate
    @abstract A delegate object to the AudioRecorder that conforms to the AVAudioRecorderDelegate protocol.
 */
@property(weak, nullable) id<AVAudioRecorderDelegate> delegate;

/*!
    @property currentTime
    @abstract Get the current time of the recording.
    @discussion This method is only vaild while recording.
 */
@property(readonly) NSTimeInterval currentTime;

/*!
    @property deviceCurrentTime
    @abstract Get the device current time.
    @discussion This method is always valid.
 */
@property(readonly) NSTimeInterval deviceCurrentTime API_AVAILABLE(macos(10.9), ios(6.0), watchos(4.0), tvos(17.0));

/* metering */

/*!
    @property meteringEnabled
    @abstract Turns level metering on or off.
    @discussion Default is off.
 */
@property(getter=isMeteringEnabled) BOOL meteringEnabled;

/*!
    @method updateMeters
    @abstract Call this method to refresh meter values.
 */
- (void)updateMeters;

/*!
    @method peakPowerForChannel:
    @abstract Returns peak power in decibels for a given channel.
 */
- (float)peakPowerForChannel:(NSUInteger)channelNumber;

/*!
    @method averagePowerForChannel:
    @abstract Returns average power in decibels for a given channel.
 */
- (float)averagePowerForChannel:(NSUInteger)channelNumber;

/*!
    @property channelAssignments
    @abstract Array of AVAudioSessionChannelDescription objects
    @discussion The channels property lets you assign the output to record specific channels as described by AVAudioSessionPortDescription's channels property. This property is nil valued until set. The array must have the same number of channels as returned by the numberOfChannels property.
 */
@property(nonatomic, copy, nullable) NSArray<AVAudioSessionChannelDescription *> *channelAssignments API_AVAILABLE(ios(7.0), watchos(4.0), tvos(17.0)) API_UNAVAILABLE(macos) ;

@end

/*!
    @protocol AVAudioRecorderDelegate
    @abstract A protocol for delegates of AVAudioRecorder.
 */
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.7), ios(3.0), watchos(4.0), tvos(17.0))
@protocol AVAudioRecorderDelegate <NSObject>
@optional 

/*!
    @method audioRecorderDidFinishRecording:successfully:
    @abstract This callback method is called when a recording has been finished or stopped.
    @discussion This method is NOT called if the recorder is stopped due to an interruption.
 */
- (void)audioRecorderDidFinishRecording:(AVAudioRecorder *)recorder successfully:(BOOL)flag;

/*!
    @method audioRecorderEncodeErrorDidOccur:error:
    @abstract This callback method is called when an error occurs while encoding.
    @discussion If an error occurs while encoding it will be reported to the delegate.
 */
- (void)audioRecorderEncodeErrorDidOccur:(AVAudioRecorder *)recorder error:(NSError * __nullable)error;

#if TARGET_OS_IPHONE

/* AVAudioRecorder INTERRUPTION NOTIFICATIONS ARE DEPRECATED - Use AVAudioSession instead. */

/*!
    @method audioRecorderBeginInterruption:
    @abstract audioRecorderBeginInterruption: is called when the audio session has been interrupted while the recorder was recording. The recorded file will be closed.
    @discussion Deprecated - use AVAudioSession instead.
 */
- (void)audioRecorderBeginInterruption:(AVAudioRecorder *)recorder API_UNAVAILABLE(tvos) API_DEPRECATED("Deprecated - use AVAudioSession instead", ios(2.2, 8.0));

/*!
    @method audioRecorderEndInterruption:withOptions:
    @abstract audioRecorderEndInterruption:withOptions: is called when the audio session interruption has ended and this recorder had been interrupted while recording.
    @discussion Currently the only flag is AVAudioSessionInterruptionFlags_ShouldResume.  Deprecated - use AVAudioSession instead.
 */
- (void)audioRecorderEndInterruption:(AVAudioRecorder *)recorder withOptions:(NSUInteger)flags API_UNAVAILABLE(tvos) API_DEPRECATED("Deprecated - use AVAudioSession instead", ios(6.0, 8.0));

/*!
    @method audioRecorderEndInterruption:withFlags:
    @abstract audioRecorderEndInterruption:withFlags: is called when the audio session interruption has ended and this recorder had been interrupted while recording.
    @discussion Deprecated - use AVAudioSession instead.
 */
- (void)audioRecorderEndInterruption:(AVAudioRecorder *)recorder withFlags:(NSUInteger)flags API_UNAVAILABLE(tvos) API_DEPRECATED("Deprecated - use AVAudioSession instead", ios(4.0, 6.0));

/*!
    @method audioRecorderEndInterruption:
    @abstract audioRecorderEndInterruption: is called when the preferred method, audioRecorderEndInterruption:withFlags:, is not implemented.
    @discussion Deprecated - use AVAudioSession instead.
 */
- (void)audioRecorderEndInterruption:(AVAudioRecorder *)recorder API_UNAVAILABLE(tvos) API_DEPRECATED("Deprecated - use AVAudioSession instead", ios(2.2, 6.0));

#endif // TARGET_OS_IPHONE

@end

NS_ASSUME_NONNULL_END
