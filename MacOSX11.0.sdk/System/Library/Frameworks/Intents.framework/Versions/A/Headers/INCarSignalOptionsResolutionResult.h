//
//  INCarSignalOptionsResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INCarSignalOptions.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macos, tvos)
@interface INCarSignalOptionsResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INCarSignalOptions. The resolvedValue can be different than the original INCarSignalOptions. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedCarSignalOptions:(INCarSignalOptions)resolvedCarSignalOptions NS_SWIFT_NAME(success(with:));

+ (instancetype)successWithResolvedValue:(INCarSignalOptions)resolvedValue NS_SWIFT_UNAVAILABLE("Please use 'success(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+successWithResolvedCarSignalOptions:", ios(10.3, 11.0), watchos(3.2, 4.0));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithCarSignalOptionsToConfirm:(INCarSignalOptions)carSignalOptionsToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

+ (instancetype)confirmationRequiredWithValueToConfirm:(INCarSignalOptions)valueToConfirm NS_SWIFT_UNAVAILABLE("Please use 'confirmationRequired(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+confirmationRequiredWithCarSignalOptionsToConfirm:", ios(10.3, 11.0), watchos(3.2, 4.0));

@end

NS_ASSUME_NONNULL_END
