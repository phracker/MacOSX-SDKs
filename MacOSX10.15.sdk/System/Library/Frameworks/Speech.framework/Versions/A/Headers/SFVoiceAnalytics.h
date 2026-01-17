//  SFVoiceAnalytics.h
//  Copyright (c) 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

// An acoustic feature
API_AVAILABLE(ios(13), macos(10.15))
@interface SFAcousticFeature : NSObject <NSCopying, NSSecureCoding>

// Array of feature values per audio frame, corresponding to a segment of recorded audio
@property (nonatomic, readonly, copy) NSArray<NSNumber *> *acousticFeatureValuePerFrame;

// Duration of an audio frame
@property (nonatomic, readonly) NSTimeInterval frameDuration;

@end

// Voice analytics corresponding to a segment of recorded audio
API_AVAILABLE(ios(13), macos(10.15))
@interface SFVoiceAnalytics : NSObject <NSCopying, NSSecureCoding>

// Jitter measures vocal stability and is measured as an absolute difference between consecutive periods, divided by the average period. It is expressed as a percentage
@property (nonatomic, readonly, copy) SFAcousticFeature *jitter;

// Shimmer measures vocal stability and is measured in decibels
@property (nonatomic, readonly, copy) SFAcousticFeature *shimmer;

// Pitch measures the highness and lowness of tone and is measured in logarithm of normalized pitch estimates
@property (nonatomic, readonly, copy) SFAcousticFeature *pitch;

// Voicing measures the probability of whether a frame is voiced or not and is measured as a probability
@property (nonatomic, readonly, copy) SFAcousticFeature *voicing;

@end

NS_ASSUME_NONNULL_END
