//
//  INSpatialEventTriggerResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class INSpatialEventTrigger;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INSpatialEventTriggerResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INSpatialEventTrigger. The resolvedSpatialEventTrigger can be different than the original INSpatialEventTrigger. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedSpatialEventTrigger:(INSpatialEventTrigger *)resolvedSpatialEventTrigger NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided INSpatialEventTrigger.
+ (instancetype)disambiguationWithSpatialEventTriggersToDisambiguate:(NSArray<INSpatialEventTrigger *> *)spatialEventTriggersToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the spatialEventTrigger with which the user wants to continue.
+ (instancetype)confirmationRequiredWithSpatialEventTriggerToConfirm:(nullable INSpatialEventTrigger *)spatialEventTriggerToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
