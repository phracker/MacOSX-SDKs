//
//  SRSpeechMetrics.h
//  SensorKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SensorKit/SRDefines.h>
#import <Speech/Speech.h>
#import <SoundAnalysis/SoundAnalysis.h>
#import <CoreMedia/CoreMedia.h>

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_SENDABLE
SR_EXTERN API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos, macos)
@interface SRSpeechExpression : NSObject <NSCopying, NSSecureCoding>
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
 * @property version
 * @brief Version of the algorithm used to generate \c SRSpeechExpression
 */
@property (nonatomic, readonly, copy) NSString *version;

/*!
 * @property version
 * @brief The time range in the client-provided audio stream to which this classification
 * result corresponds
 */
@property (nonatomic, readonly, assign) CMTimeRange timeRange;

/*!
 * @property confidence
 * @brief The level of confidence normalized to [0, 1], where 1 is most confident
 */
@property (nonatomic, readonly, assign) double confidence;

/*!
 * @property mood
 * @brief Indicator of how slurry/tired/exhausted the speaker sounds as opposed to normal.
 *
 * @discussion
 * on a scale from -1 to 1, where negative scores indicate 'negative'
 * sentiment, and positive scores indicate 'positive' sentiment.
 */
@property (nonatomic, readonly, assign) double mood;

/*!
 * @property valence
 * @brief Degree of (perceived) positive or negative emotion/sentiment from voice
 *
 * @discussion
 * on a scale from -1 to 1, where negative scores indicate 'negative'
 * sentiment, and positive scores indicate 'positive' sentiment.
 * */
@property (nonatomic, readonly, assign) double valence;

/*!
 * @property activation
 * @brief Level of energy or activation (perceived) in voice
 *
 * @discussion
 * on a scale from -1 to 1, where negative scores indicate 'negative'
 * sentiment, and positive scores indicate 'positive' sentiment.
 */
@property (nonatomic, readonly, assign) double activation;

/*!
 * @property dominance
 * @brief Degree of how strong or meek a person sounds (perceptually)
 *
 * @discussion
 * on a scale from -1 to 1, where negative scores indicate 'negative'
 * sentiment, and positive scores indicate 'positive' sentiment. 
 */
@property (nonatomic, readonly, assign) double dominance;
@end

NS_SWIFT_SENDABLE
SR_EXTERN API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos, macos)
@interface SRAudioLevel : NSObject <NSCopying, NSSecureCoding>
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
 * @property version
 * @brief The time range in the client-provided audio stream to which this classification
 * result corresponds
 */
@property (nonatomic, readonly, assign) CMTimeRange timeRange;

/*!
 * @property loudness
 * @brief Measure of the audio level in decibels
 */
@property (nonatomic, readonly, assign) double loudness;
@end

/*!
 * @typedef SRSpeechMetricsSessionFlags
 * @brief Flags indicating more information about how audio processing was done
 *  on the audio stream
 *
 * @const SRSpeechMetricsSessionFlagsDefault
 * @brief Audio stream went through the system voice processor
 *
 * @const SRSpeechMetricsSessionFlagsBypassVoiceProcessing
 * @brief Audio stream bypassed the system voice processor.
 *
 */
typedef NS_OPTIONS(NSUInteger, SRSpeechMetricsSessionFlags) {
    SRSpeechMetricsSessionFlagsDefault = 0,
    SRSpeechMetricsSessionFlagsBypassVoiceProcessing = (1U << 0),
} API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos, macos);

NS_SWIFT_SENDABLE
SR_EXTERN API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos, macos)
@interface SRSpeechMetrics : NSObject <NSCopying, NSSecureCoding>
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
 * @property sessionIdentifier
 * @brief Identifier of an audio session e.g., a Phone call or Siri utterance
 */
@property (nonatomic, readonly, copy) NSString *sessionIdentifier;


@property (nonatomic, readonly, assign) SRSpeechMetricsSessionFlags sessionFlags;

/*!
 * @property timestamp
 * @brief The wall time when this sample was generated
 */
@property (nonatomic, readonly, strong) NSDate *timestamp;

/*!
 * @property timeSinceAudioStart
 * @brief The number of seconds since the start of the audio stream
 *
 * @discussion
 * When an audio stream like a phone call starts, \c SRSpeechMetrics samples are collected
 * periodically. This field can be used to determine where each sample falls in the audio stream
 */
@property (nonatomic, readonly, assign) NSTimeInterval timeSinceAudioStart API_AVAILABLE(ios(17.2)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos, macos);

@property (nonatomic, nullable, readonly, strong) SRAudioLevel *audioLevel;
@property (nonatomic, nullable, readonly, strong) SFSpeechRecognitionResult *speechRecognition;
@property (nonatomic, nullable, readonly, strong) SNClassificationResult *soundClassification;
@property (nonatomic, nullable, readonly, strong) SRSpeechExpression *speechExpression;
@end

NS_ASSUME_NONNULL_END
