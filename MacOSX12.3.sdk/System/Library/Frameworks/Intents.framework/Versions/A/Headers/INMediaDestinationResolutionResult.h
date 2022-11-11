//
//  INMediaDestinationResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class INMediaDestination;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), watchos(6.0), tvos(14.0))
API_UNAVAILABLE(macos)
@interface INMediaDestinationResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INMediaDestination. The resolvedMediaDestination can be different than the original INMediaDestination. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedMediaDestination:(INMediaDestination *)resolvedMediaDestination NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided INMediaDestination.
+ (instancetype)disambiguationWithMediaDestinationsToDisambiguate:(NSArray<INMediaDestination *> *)mediaDestinationsToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the mediaDestination with which the user wants to continue.
+ (instancetype)confirmationRequiredWithMediaDestinationToConfirm:(nullable INMediaDestination *)mediaDestinationToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
