//
//  SFTranscription.h
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SFTranscriptionSegment;

/**
 A textual representation of the specified speech in its entirety, as recognized by the speech recognizer.

 Use `SFTranscription` to obtain all the recognized utterances from your audio content. An _utterance_ is a vocalized word or group of words that represent a single meaning to the speech recognizer (``SFSpeechRecognizer``).

 Use the ``formattedString`` property to retrieve the entire transcription of utterances, or use the ``segments`` property to retrieve an individual utterance (``SFTranscriptionSegment``).

 You don't create an `SFTranscription` directly. Instead, you retrieve it from an ``SFSpeechRecognitionResult`` instance. The speech recognizer sends a speech recognition result to your app in one of two ways, depending on how your app started a speech recognition task.

 You can start a speech recognition task by using the speech recognizer's ``SFSpeechRecognizer/recognitionTask(with:resultHandler:)`` method. When the task is complete, the speech recognizer sends an ``SFSpeechRecognitionResult`` instance to your `resultHandler` closure. Alternatively, you can use the speech recognizer's ``SFSpeechRecognizer/recognitionTask(with:delegate:)`` method to start a speech recognition task. When the task is complete, the speech recognizer uses your ``SFSpeechRecognitionTaskDelegate`` to send an ``SFSpeechRecognitionResult`` by using the delegate's ``SFSpeechRecognitionTaskDelegate/speechRecognitionTask(_:didFinishRecognition:)`` method.

 An `SFTranscription` represents only a potential version of the speech. It might not be an accurate representation of the utterances.
 */
API_AVAILABLE(ios(10.0), macos(10.15), tvos(18))
@interface SFTranscription : NSObject <NSCopying, NSSecureCoding>

/**
 The entire transcription of utterances, formatted into a single, user-displayable string.
 */
@property (nonatomic, readonly, copy) NSString *formattedString;

/**
 An array of transcription segments that represent the parts of the transcription, as identified by the speech recognizer.

 The order of the segments in the array matches the order in which the corresponding utterances occur in the spoken content.
 */
@property (nonatomic, readonly, copy) NSArray<SFTranscriptionSegment *> *segments;

/**
 The number of words spoken per minute.
 */
@property (nonatomic, readonly) double speakingRate NS_DEPRECATED(10_15, 11_3, 13_0, 14_5, "speakingRate is moved to SFSpeechRecognitionMetadata");

/**
 The average pause duration between words, measured in seconds.
 */
@property (nonatomic, readonly) NSTimeInterval averagePauseDuration NS_DEPRECATED(10_15, 11_3, 13_0, 14_5, "averagePauseDuration is moved to SFSpeechRecognitionMetadata");

@end

NS_ASSUME_NONNULL_END
