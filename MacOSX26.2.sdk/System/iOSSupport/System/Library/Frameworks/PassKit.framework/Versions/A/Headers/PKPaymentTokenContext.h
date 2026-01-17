#if !__has_include(<PassKitCore/PKPaymentTokenContext.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKPaymentTokenContext.h
//    PassKit
//
//  Copyright © 2021 Apple, Inc. All rights reserved.
//


#ifndef PKPaymentTokenContext_h
#define PKPaymentTokenContext_h

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

// Defines the context for a single payment token in a request for multiple payment tokens.
API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos)
@interface PKPaymentTokenContext : NSObject

// An identifier for the merchant, as previously agreed with Apple. If you request a payment token
// for another merchant, use their merchant identifier, if available. Otherwise, use your own.
@property (nonatomic, copy) NSString *merchantIdentifier;

// An external identifier for the merchant, provided by the developer. If you request a payment
// token for another merchant, try to always use the same external identifier for that merchant,
// if possible.
@property (nonatomic, copy) NSString *externalIdentifier;

// The name of the merchant this payment token is intended for; will be displayed to the user.
@property (nonatomic, copy) NSString *merchantName;

// The main top-level domain of the merchant this payment token is intended for, optional.
@property (nonatomic, copy, nullable) NSString *merchantDomain;

// The amount this particular payment token should be authorized for. It has the same currency as
// the enclosing payment request. Must be less than or equal to the total amount of the enclosing
// payment request.
@property (nonatomic, copy) NSDecimalNumber *amount;

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithMerchantIdentifier:(NSString *)merchantIdentifier
                        externalIdentifier:(NSString *)externalIdentifier
                              merchantName:(NSString *)merchantName
                            merchantDomain:(nullable NSString *)merchantDomain
                                    amount:(NSDecimalNumber *)amount NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END

#endif /* PKPaymentTokenContext_h */


#else
#import <TargetConditionals.h>
#import <PassKitCore/PKPaymentTokenContext.h>
#endif