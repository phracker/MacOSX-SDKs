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
@property (nonatomic, readonly) double speakingRate API_AVAILABLE(ios(13.0), macos(10.15));

// Measures average pause between words (in seconds)
@property (nonatomic, readonly) NSTimeInterval averagePauseDuration API_AVAILABLE(ios(13.0), macos(10.15));

@end

NS_ASSUME_NONNULL_END
