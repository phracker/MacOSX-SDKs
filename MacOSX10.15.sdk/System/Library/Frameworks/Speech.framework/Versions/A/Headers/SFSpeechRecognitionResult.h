//
//  SFSpeechRecognitionResult.h
//
//  Copyright (c) 2016 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SFTranscription;

// A recognized utterance, corresponding to a segment of recorded audio with speech and containing one or more transcriptions hypotheses
API_AVAILABLE(ios(10.0), macos(10.15))
@interface SFSpeechRecognitionResult : NSObject <NSCopying, NSSecureCoding>

@property (nonatomic, readonly, copy) SFTranscription *bestTranscription;

// Hypotheses for possible transcriptions, sorted in decending order of confidence (more likely first)
@property (nonatomic, readonly, copy) NSArray<SFTranscription *> *transcriptions;

// True if the hypotheses will not change; speech processing is complete.
@property (nonatomic, readonly, getter=isFinal) BOOL final;

@end

NS_ASSUME_NONNULL_END
