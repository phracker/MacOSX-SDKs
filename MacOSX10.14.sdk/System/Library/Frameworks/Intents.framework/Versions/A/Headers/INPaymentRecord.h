//
//  INPaymentRecord.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INPaymentStatus.h>

@class INCurrencyAmount;
@class INPaymentMethod;
@class INPerson;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INPaymentRecord : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (nullable instancetype)initWithPayee:(nullable INPerson *)payee
                                 payer:(nullable INPerson *)payer
                        currencyAmount:(nullable INCurrencyAmount *)currencyAmount
                         paymentMethod:(nullable INPaymentMethod *)paymentMethod
                                  note:(nullable NSString *)note
                                status:(INPaymentStatus)status
                             feeAmount:(nullable INCurrencyAmount *)feeAmount NS_DESIGNATED_INITIALIZER;

- (nullable instancetype)initWithPayee:(nullable INPerson *)payee
                                 payer:(nullable INPerson *)payer
                        currencyAmount:(nullable INCurrencyAmount *)currencyAmount
                         paymentMethod:(nullable INPaymentMethod *)paymentMethod
                                  note:(nullable NSString *)note
                                status:(INPaymentStatus)status;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPerson *payee;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPerson *payer;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INCurrencyAmount *currencyAmount;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *note;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INPaymentStatus status;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPaymentMethod *paymentMethod;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INCurrencyAmount *feeAmount;

@end

NS_ASSUME_NONNULL_END
