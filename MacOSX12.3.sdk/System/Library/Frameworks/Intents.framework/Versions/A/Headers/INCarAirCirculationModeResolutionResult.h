//
//  INCarAirCirculationModeResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INCarAirCirculationMode.h>

NS_ASSUME_NONNULL_BEGIN

API_DEPRECATED("INCarAirCirculationModeResolutionResult is deprecated. There is no replacement.", ios(10.0, 15.0))
API_UNAVAILABLE(macos, watchos, tvos)
@interface INCarAirCirculationModeResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INCarAirCirculationMode. The resolvedValue can be different than the original INCarAirCirculationMode. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedCarAirCirculationMode:(INCarAirCirculationMode)resolvedCarAirCirculationMode NS_SWIFT_NAME(success(with:));

+ (instancetype)successWithResolvedValue:(INCarAirCirculationMode)resolvedValue NS_SWIFT_UNAVAILABLE("Please use 'success(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+successWithResolvedCarAirCirculationMode:", ios(10.0, 11.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(macos, tvos);

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithCarAirCirculationModeToConfirm:(INCarAirCirculationMode)carAirCirculationModeToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

+ (instancetype)confirmationRequiredWithValueToConfirm:(INCarAirCirculationMode)valueToConfirm NS_SWIFT_UNAVAILABLE("Please use 'confirmationRequired(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+confirmationRequiredWithCarAirCirculationModeToConfirm:", ios(10.0, 11.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(macos, tvos);

@end

NS_ASSUME_NONNULL_END
