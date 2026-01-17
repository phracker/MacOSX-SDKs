//
//  INPaymentAmountResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class INPaymentAmount;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macos, tvos)
@interface INPaymentAmountResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INPaymentAmount. The resolvedPaymentAmount can be different than the original INPaymentAmount. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedPaymentAmount:(INPaymentAmount *)resolvedPaymentAmount NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided INPaymentAmount.
+ (instancetype)disambiguationWithPaymentAmountsToDisambiguate:(NSArray<INPaymentAmount *> *)paymentAmountsToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the paymentAmount with which the user wants to continue.
+ (instancetype)confirmationRequiredWithPaymentAmountToConfirm:(nullable INPaymentAmount *)paymentAmountToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
