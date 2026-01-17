//
//  SFTranscriptionSegment.h
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SFVoiceAnalytics;

/**
 A discrete part of an entire transcription, as identified by the speech recognizer.

 Use ``SFTranscriptionSegment`` to get details about a part of an overall ``SFTranscription``. An ``SFTranscriptionSegment`` represents an utterance, which is a vocalized word or group of words that represent a single meaning to the speech recognizer (``SFSpeechRecognizer``).

 You don't create transcription object segments directly. Instead, you access them from a transcription's ``SFTranscription/segments`` property.

 A transcription segment includes the following information:

 - The text of the utterance, plus any alternative interpretations of the spoken word.
 - The character range of the segment within the ``SFTranscription/formattedString`` of its parent ``SFTranscription``.
 - A ``confidence`` value, indicating how likely it is that the specified string matches the audible speech.
 - A ``timestamp`` and ``duration`` value, indicating the position of the segment within the provided audio stream.
 */
API_AVAILABLE(ios(10.0), macos(10.15), tvos(18))
@interface SFTranscriptionSegment : NSObject <NSCopying, NSSecureCoding>

/**
 The string representation of the utterance in the transcription segment.
 */
@property (nonatomic, readonly, copy) NSString *substring;

/**
 The range information for the transcription segment's substring, relative to the overall transcription.

 Use the range information to find the position of the segment within the ``SFTranscription/formattedString`` property of the ``SFTranscription`` object containing this segment.
 */
@property (nonatomic, readonly) NSRange substringRange;

/**
 The start time of the segment in the processed audio stream.

 The ``timestamp`` is the number of seconds between the beginning of the audio content and when the user spoke the word represented by the segment. For example, if the user said the word "time" one second into the transcription "What time is it", the timestamp would be equal to `1.0`.
 */
@property (nonatomic, readonly) NSTimeInterval timestamp;

/**
 The number of seconds it took for the user to speak the utterance represented by the segment.

 The ``duration`` contains the number of seconds it took for the user to speak the one or more words (utterance) represented by the segment. For example, the ``SFSpeechRecognizer`` sets ``duration`` to `0.6` if the user took `0.6` seconds to say `“time”` in the transcription of `“What time is it?"`.
 */
@property (nonatomic, readonly) NSTimeInterval duration;

/**
 The level of confidence the speech recognizer has in its recognition of the speech transcribed for the segment.

 This property reflects the overall confidence in the recognition of the entire phrase. The value is `0` if there was no recognition, and it is closer to `1` when there is a high certainty that a transcription matches the user's speech exactly. For example, a confidence value of `0.94` represents a very high confidence level, and is more likely to be correct than a transcription with a confidence value of `0.72`.
 */
@property (nonatomic, readonly) float confidence;

/**
 An array of alternate interpretations of the utterance in the transcription segment.
*/
@property (nonatomic, readonly) NSArray<NSString *> *alternativeSubstrings;

/**
 An analysis of the transcription segment's vocal properties.
 */
@property (nonatomic, nullable, readonly) SFVoiceAnalytics *voiceAnalytics NS_DEPRECATED(10_15, 11_3, 13_0, 14_5, "voiceAnalytics is moved to SFSpeechRecognitionMetadata");

@end

NS_ASSUME_NONNULL_END
