//
//  SFSpeechRecognitionMetadata.h
//
//  Copyright © 2020 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SFVoiceAnalytics;

/**
 The metadata of speech in the audio of a speech recognition request.
 */
API_AVAILABLE(ios(14.5), macos(11.3), tvos(18))
@interface SFSpeechRecognitionMetadata : NSObject <NSCopying, NSSecureCoding>

/**
 The number of words spoken per minute.
 */
@property (nonatomic, readonly) double speakingRate;

/**
 The average pause duration between words, measured in seconds.
 */
@property (nonatomic, readonly) NSTimeInterval averagePauseDuration;

/**
 The start timestamp of speech in the audio.
 */
@property (nonatomic, readonly) NSTimeInterval speechStartTimestamp;

/**
 The duration in seconds of speech in the audio.
 */
@property (nonatomic, readonly) NSTimeInterval speechDuration;

/**
 An analysis of the transcription segment's vocal properties.
 */
@property (nonatomic, nullable, readonly) SFVoiceAnalytics *voiceAnalytics;

@end

NS_ASSUME_NONNULL_END
