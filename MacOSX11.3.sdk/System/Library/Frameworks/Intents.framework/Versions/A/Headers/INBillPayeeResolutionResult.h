//
//  INBillPayeeResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class INBillPayee;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macos, tvos)
@interface INBillPayeeResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INBillPayee. The resolvedBillPayee can be different than the original INBillPayee. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedBillPayee:(INBillPayee *)resolvedBillPayee NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided INBillPayee.
+ (instancetype)disambiguationWithBillPayeesToDisambiguate:(NSArray<INBillPayee *> *)billPayeesToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the billPayee with which the user wants to continue.
+ (instancetype)confirmationRequiredWithBillPayeeToConfirm:(nullable INBillPayee *)billPayeeToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
