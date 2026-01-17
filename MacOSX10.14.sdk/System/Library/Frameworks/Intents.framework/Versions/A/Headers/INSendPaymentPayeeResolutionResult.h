//
//  INSendPaymentPayeeResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INPersonResolutionResult.h>

typedef NS_ENUM(NSInteger, INSendPaymentPayeeUnsupportedReason) {
    INSendPaymentPayeeUnsupportedReasonCredentialsUnverified = 1,
    INSendPaymentPayeeUnsupportedReasonInsufficientFunds,
    INSendPaymentPayeeUnsupportedReasonNoAccount,
    INSendPaymentPayeeUnsupportedReasonNoValidHandle API_AVAILABLE(ios(11.1), watchos(4.1)),
} API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INSendPaymentPayeeResolutionResult : INPersonResolutionResult

+ (instancetype)unsupportedForReason:(INSendPaymentPayeeUnsupportedReason)reason NS_SWIFT_NAME(unsupported(forReason:));

- (instancetype)initWithPersonResolutionResult:(INPersonResolutionResult *)personResolutionResult;

@end

NS_ASSUME_NONNULL_END
