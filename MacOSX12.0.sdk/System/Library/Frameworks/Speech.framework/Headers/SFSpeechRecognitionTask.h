//
//  SFSpeechRecognitionTask.h
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SFVoiceAnalytics;
@class SFSpeechRecognitionResult;
@class SFTranscription;

typedef NS_ENUM(NSInteger, SFSpeechRecognitionTaskState) {
    SFSpeechRecognitionTaskStateStarting = 0,       // Speech processing (potentially including recording) has not yet begun
    SFSpeechRecognitionTaskStateRunning = 1,        // Speech processing (potentially including recording) is running
    SFSpeechRecognitionTaskStateFinishing = 2,      // No more audio is being recorded, but more recognition results may arrive
    SFSpeechRecognitionTaskStateCanceling = 3,      // No more recognition results will arrive, but recording may not have stopped yet
    SFSpeechRecognitionTaskStateCompleted = 4,      // No more results will arrive, and recording is stopped.
} API_AVAILABLE(ios(10.0), macos(10.15));

API_AVAILABLE(ios(10.0), macos(10.15))
@interface SFSpeechRecognitionTask : NSObject

@property (nonatomic, readonly) SFSpeechRecognitionTaskState state;

// True if recognition audio input has stopped
@property (nonatomic, readonly, getter=isFinishing) BOOL finishing;
// Instructs the task to stop accepting new audio (e.g. stop recording) but complete processing on audio already buffered.
// This has no effect on URL-based recognition requests, which effectively buffer the entire file immediately.
- (void)finish;

// True if recognition has been cancelled
@property (nonatomic, readonly, getter=isCancelled) BOOL cancelled;
- (void)cancel;

// Reports error that occurred during recognition, if applicable
@property (nonatomic, readonly, copy, nullable) NSError *error;

@end

// Recognition result receiver, to be used for complex or multi-utterance speech recognition requests
API_AVAILABLE(ios(10.0), macos(10.15))
@protocol SFSpeechRecognitionTaskDelegate <NSObject>

@optional

// Called when the task first detects speech in the source audio
- (void)speechRecognitionDidDetectSpeech:(SFSpeechRecognitionTask *)task;

// Called for all recognitions, including non-final hypothesis
- (void)speechRecognitionTask:(SFSpeechRecognitionTask *)task didHypothesizeTranscription:(SFTranscription *)transcription;

// Called only for final recognitions of utterances. No more about the utterance will be reported
- (void)speechRecognitionTask:(SFSpeechRecognitionTask *)task didFinishRecognition:(SFSpeechRecognitionResult *)recognitionResult;

// Called when the task is no longer accepting new audio but may be finishing final processing
- (void)speechRecognitionTaskFinishedReadingAudio:(SFSpeechRecognitionTask *)task;

// Called when the task has been cancelled, either by client app, the user, or the system
- (void)speechRecognitionTaskWasCancelled:(SFSpeechRecognitionTask *)task;

// Called when recognition of all requested utterances is finished.
// If successfully is false, the error property of the task will contain error information
- (void)speechRecognitionTask:(SFSpeechRecognitionTask *)task didFinishSuccessfully:(BOOL)successfully;

@end

NS_ASSUME_NONNULL_END
