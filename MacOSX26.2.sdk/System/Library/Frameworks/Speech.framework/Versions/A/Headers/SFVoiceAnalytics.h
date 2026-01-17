//  SFVoiceAnalytics.h
//  Copyright (c) 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The value of a voice analysis metric.
 */
API_AVAILABLE(ios(13), macos(10.15), tvos(18))
@interface SFAcousticFeature : NSObject <NSCopying, NSSecureCoding>

/**
 An array of feature values, one value per audio frame, corresponding to a transcript segment of recorded audio.
 */
@property (nonatomic, readonly, copy) NSArray<NSNumber *> *acousticFeatureValuePerFrame;

/**
 The duration of the audio frame.
 */
@property (nonatomic, readonly) NSTimeInterval frameDuration;

@end

/**
 A collection of vocal analysis metrics.

 Use an ``SFAcousticFeature`` object to access the `SFVoiceAnalytics` insights. Voice analytics include the following features:

 - Use ``jitter`` to measure how pitch varies in audio.
 - Use ``shimmer`` to measure how amplitude varies in audio.
 - Use ``pitch`` to measure the highness and lowness of the tone.
 - Use ``voicing`` to identify voiced regions in speech.

 These results are part of the ``SFTranscriptionSegment`` object and are available when the system sends the ``SFSpeechRecognitionResult/isFinal`` flag.
 */
API_AVAILABLE(ios(13), macos(10.15), tvos(18))
@interface SFVoiceAnalytics : NSObject <NSCopying, NSSecureCoding>

/**
 The variation in pitch in each frame of a transcription segment, expressed as a percentage of the frame's fundamental frequency.
 */
// Jitter measures vocal stability and is measured as an absolute difference between consecutive periods, divided by the average period. It is expressed as a percentage
@property (nonatomic, readonly, copy) SFAcousticFeature *jitter;

/**
 The variation in vocal volume stability (amplitude) in each frame of a transcription segment, expressed in decibels.
 */
@property (nonatomic, readonly, copy) SFAcousticFeature *shimmer;

/**
 The highness or lowness of the tone (fundamental frequency) in each frame of a transcription segment, expressed as a logarithm.

 The value is a logarithm (base `e`) of the normalized pitch estimate for each frame.
*/
@property (nonatomic, readonly, copy) SFAcousticFeature *pitch;

/**
 The likelihood of a voice in each frame of a transcription segment.

 The `voicing` value is expressed as a probability in the range `[0.0, 1.0]`.
 */
// Voicing measures the probability of whether a frame is voiced or not and is measured as a probability
@property (nonatomic, readonly, copy) SFAcousticFeature *voicing;

@end

NS_ASSUME_NONNULL_END
