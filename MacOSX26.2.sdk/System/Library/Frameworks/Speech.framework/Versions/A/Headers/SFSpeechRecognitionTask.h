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

/**
 The state of the task associated with the recognition request.
 */
typedef NS_ENUM(NSInteger, SFSpeechRecognitionTaskState) {
    /// Speech recognition (potentially including audio recording) has not yet started.
    SFSpeechRecognitionTaskStateStarting = 0,

    /// Speech recognition (potentially including audio recording) is in progress.
    SFSpeechRecognitionTaskStateRunning = 1,

    /// Audio recording has stopped, but delivery of recognition results may continue.
    SFSpeechRecognitionTaskStateFinishing = 2,

    /// Delivery of recognition results has finished, but audio recording may be ongoing.
    SFSpeechRecognitionTaskStateCanceling = 3,
    
    /// Delivery of recognition requests has finished and audio recording has stopped.
    SFSpeechRecognitionTaskStateCompleted = 4,
} API_AVAILABLE(ios(10.0), macos(10.15), tvos(18));

/**
 A task object for monitoring the speech recognition progress.

 Use an `SFSpeechRecognitionTask` object to determine the state of a speech recognition task, to cancel an ongoing task, or to signal the end of the task.

 You don't create speech recognition task objects directly. Instead, you receive one of these objects after calling ``SFSpeechRecognizer/recognitionTask(with:resultHandler:)`` or ``SFSpeechRecognizer/recognitionTask(with:delegate:)`` on your ``SFSpeechRecognizer`` object.
 */
API_AVAILABLE(ios(10.0), macos(10.15), tvos(18))
@interface SFSpeechRecognitionTask : NSObject

/**
 The current state of the speech recognition task.

 Check the value of this property to get the state of the in-progress speech recognition session. For valid values, see ``SFSpeechRecognitionTaskState``.
 */
@property (nonatomic, readonly) SFSpeechRecognitionTaskState state;

/**
 A Boolean value that indicates whether audio input has stopped.

 By default, the value of this property is `false`.
 */
@property (nonatomic, readonly, getter=isFinishing) BOOL finishing;

/**
 Stops accepting new audio and finishes processing on the audio input that has already been accepted.

 For audio buffer–based recognition, recognition does not finish until this method is called, so be sure to call it when the audio source is exhausted.
 */
// This has no effect on URL-based recognition requests, which effectively buffer the entire file immediately.
- (void)finish;

/**
 A Boolean value that indicates whether the speech recognition task was canceled.

 By default, the value of this property is `false`.
 */
@property (nonatomic, readonly, getter=isCancelled) BOOL cancelled;

/**
 Cancels the current speech recognition task.

 You can cancel recognition tasks for both prerecorded and live audio input. For example, you might cancel a task in response to a user action or because the recording was interrupted.

 When canceling a task, be sure to release any resources associated with the task, such as the audio input resources you are using to capture audio samples.
 */
- (void)cancel;

/**
 An error object that specifies the error that occurred during a speech recognition task.

 The system may return one of the errors listed in the table below.

 | Error Code | Error Domain | Description |
 |---|---|---|
 | `102` | `kLSRErrorDomain` | Assets are not installed. |
 | `201` | `kLSRErrorDomain` | Siri or Dictation is disabled. |
 | `300` | `kLSRErrorDomain` | Failed to initialize recognizer. |
 | `301` | `kLSRErrorDomain` | Request was canceled. |
 | `203` | `kAFAssistantErrorDomain` | Failure occurred during speech recognition. |
 | `1100` | `kAFAssistantErrorDomain` | Trying to start recognition while an earlier instance is still active. |
 | `1101` | `kAFAssistantErrorDomain` | Connection to speech process was invalidated. |
 | `1107` | `kAFAssistantErrorDomain` | Connection to speech process was interrupted. |
 | `1110` | `kAFAssistantErrorDomain` | Failed to recognize any speech. |
 | `1700` | `kAFAssistantErrorDomain` | Request is not authorized. |
 */
@property (nonatomic, readonly, copy, nullable) NSError *error;

@end

/**
 A protocol with methods for managing multi-utterance speech recognition requests.

 The methods of this protocol give you fine-grained control over the speech recognition process. Specifically, you use this protocol when you want to know the following:

 - When the first utterances of speech occur in the audio.
 - When the speech recognizer stops accepting audio.
 - When the speech recognition process finishes or is canceled.
 - When the speech recognizer generates a potential transcription.

 Adopt the methods of this protocol in an object and pass that object in to the `delegate` parameter of ``SFSpeechRecognizer/recognitionTask(with:delegate:)`` when starting your speech recognition task.
 */
API_AVAILABLE(ios(10.0), macos(10.15), tvos(18))
@protocol SFSpeechRecognitionTaskDelegate <NSObject>

@optional

/**
 Tells the delegate when the task first detects speech in the source audio.

 - Parameters:
   - task: The speech recognition task (an ``SFSpeechRecognitionTask`` object) that represents the request.
 */
- (void)speechRecognitionDidDetectSpeech:(SFSpeechRecognitionTask *)task;

/**
 Tells the delegate that a hypothesized transcription is available.

 This method is called for all recognitions, including partial recognitions.
 
 - Parameters:
   - task: The speech recognition task (an ``SFSpeechRecognitionTask`` object) that represents the request.
   - transcription: The hypothesized transcription in an ``SFTranscription`` object.
 */
- (void)speechRecognitionTask:(SFSpeechRecognitionTask *)task didHypothesizeTranscription:(SFTranscription *)transcription;

/**
 Tells the delegate when the final utterance is recognized.

 When this method is called, the delegate should expect no further information about the utterance to be reported.

 - Parameters:
   - task: The speech recognition task (an ``SFSpeechRecognitionTask`` object) that represents the request.
   - recognitionResult: A recognized utterance that contains one or more transcription hypotheses in an ``SFSpeechRecognitionResult`` object.
 */
- (void)speechRecognitionTask:(SFSpeechRecognitionTask *)task didFinishRecognition:(SFSpeechRecognitionResult *)recognitionResult;

/**
 Tells the delegate when the task is no longer accepting new audio input, even if final processing is in progress.

 - Parameters:
   - task: The speech recognition task (an ``SFSpeechRecognitionTask`` object) that represents the request.
 */
- (void)speechRecognitionTaskFinishedReadingAudio:(SFSpeechRecognitionTask *)task;

/**
 Tells the delegate that the task has been canceled.

 A speech recognition task can be canceled by the user, by your app, or by the system.

 - Parameters:
   - task: The speech recognition task (an ``SFSpeechRecognitionTask`` object) that represents the request.
 */
- (void)speechRecognitionTaskWasCancelled:(SFSpeechRecognitionTask *)task;

/**
 Tells the delegate when the recognition of all requested utterances is finished.

 - Parameters:
   - task: The speech recognition task (an ``SFSpeechRecognitionTask`` object) that represents the request.
   - successfully: A Boolean value that indicates whether the task was successful. When this parameter is `false`, use the ``SFSpeechRecognitionTask/error`` property of the task to get information about why the task was unsuccessful.
 */
- (void)speechRecognitionTask:(SFSpeechRecognitionTask *)task didFinishSuccessfully:(BOOL)successfully;

/**
 Tells the delegate how much audio has been processed by the task.
 
 - Parameters:
   - task: The speech recognition task (an ``SFSpeechRecognitionTask`` object) that represents the request.
   - duration: The seconds of audio input that the recognizer has processed.
 */
- (void)speechRecognitionTask:(SFSpeechRecognitionTask *)task didProcessAudioDuration:(NSTimeInterval)duration API_AVAILABLE(ios(10.0), macos(10.15), tvos(18));

@end

NS_ASSUME_NONNULL_END
