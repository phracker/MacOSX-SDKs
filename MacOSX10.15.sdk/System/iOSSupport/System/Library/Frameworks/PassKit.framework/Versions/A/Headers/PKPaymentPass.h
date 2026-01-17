//
//  PKPaymentPass.h
//  PassKit
//
//  Copyright (c) 2014 Apple, Inc. All rights reserved.
//

#ifndef __PKPAYMENTPASS_H
#define __PKPAYMENTPASS_H

#import <PassKit/PKPass.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, PKPaymentPassActivationState) {
    PKPaymentPassActivationStateActivated,
    PKPaymentPassActivationStateRequiresActivation,
    PKPaymentPassActivationStateActivating,
    PKPaymentPassActivationStateSuspended,
    PKPaymentPassActivationStateDeactivated
} API_AVAILABLE(ios(8.0), watchos(3.0));


API_AVAILABLE(ios(8.0), watchos(3.0))
@interface PKPaymentPass : PKPass

@property (nonatomic, copy, readonly) NSString *primaryAccountIdentifier;
@property (nonatomic, copy, readonly) NSString *primaryAccountNumberSuffix;
@property (weak, readonly) NSString *deviceAccountIdentifier;
@property (weak, readonly) NSString *deviceAccountNumberSuffix;
@property (nonatomic, readonly) PKPaymentPassActivationState activationState;

@end
NS_ASSUME_NONNULL_END

#endif // End __PKPAYMENTPASS_H
