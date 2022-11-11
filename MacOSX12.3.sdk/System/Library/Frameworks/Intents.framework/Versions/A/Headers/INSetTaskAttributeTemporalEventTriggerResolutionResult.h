//
//  INSetTaskAttributeTemporalEventTriggerResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Intents/INTemporalEventTriggerResolutionResult.h>

typedef NS_ENUM(NSInteger, INSetTaskAttributeTemporalEventTriggerUnsupportedReason) {
    INSetTaskAttributeTemporalEventTriggerUnsupportedReasonTimeInPast = 1,
    INSetTaskAttributeTemporalEventTriggerUnsupportedReasonInvalidRecurrence,
} API_AVAILABLE(ios(13.0), watchos(6.0)) API_UNAVAILABLE(macos, tvos);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), watchos(6.0))
API_UNAVAILABLE(macos, tvos)
@interface INSetTaskAttributeTemporalEventTriggerResolutionResult : INTemporalEventTriggerResolutionResult

+ (instancetype)unsupportedForReason:(INSetTaskAttributeTemporalEventTriggerUnsupportedReason)reason NS_SWIFT_NAME(unsupported(forReason:));

- (instancetype)initWithTemporalEventTriggerResolutionResult:(INTemporalEventTriggerResolutionResult *)temporalEventTriggerResolutionResult;

@end

NS_ASSUME_NONNULL_END
