//
//  INTemporalEventTriggerTypeOptionsResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INTemporalEventTriggerTypeOptions.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), watchos(6.0))
API_UNAVAILABLE(macos, tvos)
@interface INTemporalEventTriggerTypeOptionsResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INTemporalEventTriggerTypeOptions. The resolvedValue can be different than the original INTemporalEventTriggerTypeOptions. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedTemporalEventTriggerTypeOptions:(INTemporalEventTriggerTypeOptions)resolvedTemporalEventTriggerTypeOptions NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithTemporalEventTriggerTypeOptionsToConfirm:(INTemporalEventTriggerTypeOptions)temporalEventTriggerTypeOptionsToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
