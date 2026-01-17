#if !__has_include(<PassKitCore/PKPaymentPass.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKPaymentPass.h
//    PassKit
//
//  Copyright (c) 2014 Apple, Inc. All rights reserved.
//

#ifndef __PKPAYMENTPASS_H
#define __PKPAYMENTPASS_H

#import <PassKit/PKSecureElementPass.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, PKPaymentPassActivationState) {
    PKPaymentPassActivationStateActivated,
    PKPaymentPassActivationStateRequiresActivation,
    PKPaymentPassActivationStateActivating,
    PKPaymentPassActivationStateSuspended,
    PKPaymentPassActivationStateDeactivated
} API_DEPRECATED("Use PKSecureElementPassActivationState instead", macos(11.0, API_TO_BE_DEPRECATED), ios(8.0, API_TO_BE_DEPRECATED), watchos(3.0, API_TO_BE_DEPRECATED));

API_AVAILABLE(macos(11.0), ios(8.0), watchos(3.0))
@interface PKPaymentPass : PKSecureElementPass

@property (nonatomic, readonly) PKPaymentPassActivationState activationState API_DEPRECATED("Use [PKSecureElementPass passActivationState] instead", macos(11.0, API_TO_BE_DEPRECATED), ios(8.0, API_TO_BE_DEPRECATED), watchos(3.0, API_TO_BE_DEPRECATED));

@end
NS_ASSUME_NONNULL_END

#endif // End __PKPAYMENTPASS_H

#else
#import <TargetConditionals.h>
#import <PassKitCore/PKPaymentPass.h>
#endif