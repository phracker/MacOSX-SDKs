//
//  SFTranscription.h
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SFTranscriptionSegment;

// A hypothesized text form of a speech recording
API_AVAILABLE(ios(10.0), macos(10.15))
@interface SFTranscription : NSObject <NSCopying, NSSecureCoding>

// Contains the entire recognition, formatted into a single user-displayable string
@property (nonatomic, readonly, copy) NSString *formattedString;

@property (nonatomic, readonly, copy) NSArray<SFTranscriptionSegment *> *segments;

// Measures the number of words spoken per minute
@property (nonatomic, readonly) double speakingRate NS_DEPRECATED(10_15, 11_3, 13_0, 14_5, "speakingRate is moved to SFSpeechRecognitionMetadata");

// Measures average pause between words (in seconds)
@property (nonatomic, readonly) NSTimeInterval averagePauseDuration NS_DEPRECATED(10_15, 11_3, 13_0, 14_5, "averagePauseDuration is moved to SFSpeechRecognitionMetadata");

@end

NS_ASSUME_NONNULL_END
