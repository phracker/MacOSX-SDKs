//
//  INPaymentMethodResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class INPaymentMethod;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), macos(11.0), watchos(6.0))
API_UNAVAILABLE(tvos)
@interface INPaymentMethodResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INPaymentMethod. The resolvedPaymentMethod can be different than the original INPaymentMethod. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedPaymentMethod:(INPaymentMethod *)resolvedPaymentMethod NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided INPaymentMethod.
+ (instancetype)disambiguationWithPaymentMethodsToDisambiguate:(NSArray<INPaymentMethod *> *)paymentMethodsToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the paymentMethod with which the user wants to continue.
+ (instancetype)confirmationRequiredWithPaymentMethodToConfirm:(nullable INPaymentMethod *)paymentMethodToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
