//
//  INTemporalEventTriggerResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class INTemporalEventTrigger;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macos, tvos)
@interface INTemporalEventTriggerResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INTemporalEventTrigger. The resolvedTemporalEventTrigger can be different than the original INTemporalEventTrigger. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedTemporalEventTrigger:(INTemporalEventTrigger *)resolvedTemporalEventTrigger NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided INTemporalEventTrigger.
+ (instancetype)disambiguationWithTemporalEventTriggersToDisambiguate:(NSArray<INTemporalEventTrigger *> *)temporalEventTriggersToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the temporalEventTrigger with which the user wants to continue.
+ (instancetype)confirmationRequiredWithTemporalEventTriggerToConfirm:(nullable INTemporalEventTrigger *)temporalEventTriggerToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
