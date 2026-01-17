//
//  INRequestPaymentCurrencyAmountResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Intents/INCurrencyAmountResolutionResult.h>

typedef NS_ENUM(NSInteger, INRequestPaymentCurrencyAmountUnsupportedReason) {
    INRequestPaymentCurrencyAmountUnsupportedReasonPaymentsAmountBelowMinimum = 1,
    INRequestPaymentCurrencyAmountUnsupportedReasonPaymentsAmountAboveMaximum,
    INRequestPaymentCurrencyAmountUnsupportedReasonPaymentsCurrencyUnsupported,
} API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macos, tvos);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macos, tvos)
@interface INRequestPaymentCurrencyAmountResolutionResult : INCurrencyAmountResolutionResult

+ (instancetype)unsupportedForReason:(INRequestPaymentCurrencyAmountUnsupportedReason)reason NS_SWIFT_NAME(unsupported(forReason:));

- (instancetype)initWithCurrencyAmountResolutionResult:(INCurrencyAmountResolutionResult *)currencyAmountResolutionResult;

@end

NS_ASSUME_NONNULL_END
