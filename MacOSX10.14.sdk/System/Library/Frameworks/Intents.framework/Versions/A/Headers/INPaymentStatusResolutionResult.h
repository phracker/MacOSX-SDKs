//
//  INPaymentStatusResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INPaymentStatus.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INPaymentStatusResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INPaymentStatus. The resolvedValue can be different than the original INPaymentStatus. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedPaymentStatus:(INPaymentStatus)resolvedPaymentStatus NS_SWIFT_NAME(success(with:));

+ (instancetype)successWithResolvedValue:(INPaymentStatus)resolvedValue NS_SWIFT_UNAVAILABLE("Please use 'success(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+successWithResolvedPaymentStatus:", ios(10.0, 11.0), watchos(3.2, 4.0));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithPaymentStatusToConfirm:(INPaymentStatus)paymentStatusToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

+ (instancetype)confirmationRequiredWithValueToConfirm:(INPaymentStatus)valueToConfirm NS_SWIFT_UNAVAILABLE("Please use 'confirmationRequired(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+confirmationRequiredWithPaymentStatusToConfirm:", ios(10.0, 11.0), watchos(3.2, 4.0));

@end

NS_ASSUME_NONNULL_END
