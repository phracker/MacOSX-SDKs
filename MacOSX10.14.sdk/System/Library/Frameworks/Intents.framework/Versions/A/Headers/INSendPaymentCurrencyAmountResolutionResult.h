//
//  INSendPaymentCurrencyAmountResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INCurrencyAmountResolutionResult.h>

typedef NS_ENUM(NSInteger, INSendPaymentCurrencyAmountUnsupportedReason) {
    INSendPaymentCurrencyAmountUnsupportedReasonPaymentsAmountBelowMinimum = 1,
    INSendPaymentCurrencyAmountUnsupportedReasonPaymentsAmountAboveMaximum,
    INSendPaymentCurrencyAmountUnsupportedReasonPaymentsCurrencyUnsupported,
} API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INSendPaymentCurrencyAmountResolutionResult : INCurrencyAmountResolutionResult

+ (instancetype)unsupportedForReason:(INSendPaymentCurrencyAmountUnsupportedReason)reason NS_SWIFT_NAME(unsupported(forReason:));

- (instancetype)initWithCurrencyAmountResolutionResult:(INCurrencyAmountResolutionResult *)currencyAmountResolutionResult;

@end

NS_ASSUME_NONNULL_END
