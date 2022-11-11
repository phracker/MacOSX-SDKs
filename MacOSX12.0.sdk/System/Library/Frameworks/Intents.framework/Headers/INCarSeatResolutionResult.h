//
//  INCarSeatResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INCarSeat.h>

NS_ASSUME_NONNULL_BEGIN

API_DEPRECATED("INCarSeatResolutionResult is deprecated. There is no replacement.", ios(10.0, 15.0))
API_UNAVAILABLE(macos, watchos, tvos)
@interface INCarSeatResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INCarSeat. The resolvedValue can be different than the original INCarSeat. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedCarSeat:(INCarSeat)resolvedCarSeat NS_SWIFT_NAME(success(with:));

+ (instancetype)successWithResolvedValue:(INCarSeat)resolvedValue NS_SWIFT_UNAVAILABLE("Please use 'success(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+successWithResolvedCarSeat:", ios(10.0, 11.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(macos, tvos);

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithCarSeatToConfirm:(INCarSeat)carSeatToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

+ (instancetype)confirmationRequiredWithValueToConfirm:(INCarSeat)valueToConfirm NS_SWIFT_UNAVAILABLE("Please use 'confirmationRequired(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+confirmationRequiredWithCarSeatToConfirm:", ios(10.0, 11.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(macos, tvos);

@end

NS_ASSUME_NONNULL_END
