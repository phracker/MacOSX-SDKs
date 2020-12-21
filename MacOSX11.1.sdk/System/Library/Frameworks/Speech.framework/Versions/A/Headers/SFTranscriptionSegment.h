//
//  SFTranscriptionSegment.h
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SFVoiceAnalytics;

// Substrings of a hypothesized transcription
API_AVAILABLE(ios(10.0), macos(10.15))
@interface SFTranscriptionSegment : NSObject <NSCopying, NSSecureCoding>

@property (nonatomic, readonly, copy) NSString *substring;
@property (nonatomic, readonly) NSRange substringRange;

// Relative to start of utterance
@property (nonatomic, readonly) NSTimeInterval timestamp;
@property (nonatomic, readonly) NSTimeInterval duration;

// Confidence in the accuracy of transcription. Scale is 0 (least confident) to 1.0 (most confident)
@property (nonatomic, readonly) float confidence;

// Other possible interpretations of this segment
@property (nonatomic, readonly) NSArray<NSString *> *alternativeSubstrings;

@property (nonatomic, nullable, readonly) SFVoiceAnalytics *voiceAnalytics API_AVAILABLE(ios(13.0), macos(10.15));

@end

NS_ASSUME_NONNULL_END
