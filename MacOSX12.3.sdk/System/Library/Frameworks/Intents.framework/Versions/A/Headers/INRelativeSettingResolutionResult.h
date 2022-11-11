//
//  INRelativeSettingResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INRelativeSetting.h>

NS_ASSUME_NONNULL_BEGIN

API_DEPRECATED("INRelativeSettingResolutionResult is deprecated. There is no replacement.", ios(10.0, 15.0))
API_UNAVAILABLE(macos, watchos, tvos)
@interface INRelativeSettingResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INRelativeSetting. The resolvedValue can be different than the original INRelativeSetting. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedRelativeSetting:(INRelativeSetting)resolvedRelativeSetting NS_SWIFT_NAME(success(with:));

+ (instancetype)successWithResolvedValue:(INRelativeSetting)resolvedValue NS_SWIFT_UNAVAILABLE("Please use 'success(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+successWithResolvedRelativeSetting:", ios(10.0, 11.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(macos, tvos);

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithRelativeSettingToConfirm:(INRelativeSetting)relativeSettingToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

+ (instancetype)confirmationRequiredWithValueToConfirm:(INRelativeSetting)valueToConfirm NS_SWIFT_UNAVAILABLE("Please use 'confirmationRequired(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+confirmationRequiredWithRelativeSettingToConfirm:", ios(10.0, 11.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(macos, tvos);

@end

NS_ASSUME_NONNULL_END
