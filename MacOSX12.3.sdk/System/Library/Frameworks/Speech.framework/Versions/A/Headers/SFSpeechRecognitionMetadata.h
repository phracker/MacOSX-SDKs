//
//  SFSpeechRecognitionMetadata.h
//
//  Copyright © 2020 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SFVoiceAnalytics;

API_AVAILABLE(ios(14.5), macos(11.3))
@interface SFSpeechRecognitionMetadata : NSObject <NSCopying, NSSecureCoding>

// Measures the number of words spoken per minute
@property (nonatomic, readonly) double speakingRate;

// Measures average pause between words (in seconds)
@property (nonatomic, readonly) NSTimeInterval averagePauseDuration;

// Timestamp of start of speech in audio
@property (nonatomic, readonly) NSTimeInterval speechStartTimestamp;

// Duration of speech in audio
@property (nonatomic, readonly) NSTimeInterval speechDuration;

@property (nonatomic, nullable, readonly) SFVoiceAnalytics *voiceAnalytics;

@end

NS_ASSUME_NONNULL_END
