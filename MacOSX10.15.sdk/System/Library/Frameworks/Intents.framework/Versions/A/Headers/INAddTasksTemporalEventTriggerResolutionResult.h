//
//  INAddTasksTemporalEventTriggerResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2019 Apple Inc. All rights reserved.
//

#import <Intents/INTemporalEventTriggerResolutionResult.h>

typedef NS_ENUM(NSInteger, INAddTasksTemporalEventTriggerUnsupportedReason) {
    INAddTasksTemporalEventTriggerUnsupportedReasonTimeInPast = 1,
    INAddTasksTemporalEventTriggerUnsupportedReasonInvalidRecurrence,
} API_AVAILABLE(ios(13.0), watchos(6.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), watchos(6.0))
API_UNAVAILABLE(macosx)
@interface INAddTasksTemporalEventTriggerResolutionResult : INTemporalEventTriggerResolutionResult

+ (instancetype)unsupportedForReason:(INAddTasksTemporalEventTriggerUnsupportedReason)reason NS_SWIFT_NAME(unsupported(forReason:));

- (instancetype)initWithTemporalEventTriggerResolutionResult:(INTemporalEventTriggerResolutionResult *)temporalEventTriggerResolutionResult;

@end

NS_ASSUME_NONNULL_END
