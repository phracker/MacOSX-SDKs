//
//  INMediaAffinityTypeResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INMediaAffinityType.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), watchos(6.0), tvos(14.0))
API_UNAVAILABLE(macos)
@interface INMediaAffinityTypeResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INMediaAffinityType. The resolvedValue can be different than the original INMediaAffinityType. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedMediaAffinityType:(INMediaAffinityType)resolvedMediaAffinityType NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithMediaAffinityTypeToConfirm:(INMediaAffinityType)mediaAffinityTypeToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
