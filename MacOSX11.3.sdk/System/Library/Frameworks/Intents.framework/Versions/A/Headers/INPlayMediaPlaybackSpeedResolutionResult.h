//
//  INPlayMediaPlaybackSpeedResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Intents/INDoubleResolutionResult.h>

typedef NS_ENUM(NSInteger, INPlayMediaPlaybackSpeedUnsupportedReason) {
    INPlayMediaPlaybackSpeedUnsupportedReasonBelowMinimum = 1,
    INPlayMediaPlaybackSpeedUnsupportedReasonAboveMaximum,
} API_AVAILABLE(ios(13.0), watchos(6.0), tvos(14.0)) API_UNAVAILABLE(macos);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), watchos(6.0), tvos(14.0))
API_UNAVAILABLE(macos)
@interface INPlayMediaPlaybackSpeedResolutionResult : INDoubleResolutionResult

+ (instancetype)unsupportedForReason:(INPlayMediaPlaybackSpeedUnsupportedReason)reason NS_SWIFT_NAME(unsupported(forReason:));

- (instancetype)initWithDoubleResolutionResult:(INDoubleResolutionResult *)doubleResolutionResult;

@end

NS_ASSUME_NONNULL_END
