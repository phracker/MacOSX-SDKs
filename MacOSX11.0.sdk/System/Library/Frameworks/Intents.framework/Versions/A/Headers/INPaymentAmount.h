//
//  INPaymentAmount.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INAmountType.h>

@class INCurrencyAmount;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macos, tvos)
@interface INPaymentAmount : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithAmountType:(INAmountType)amountType
                            amount:(INCurrencyAmount *)amount NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INCurrencyAmount *amount;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INAmountType amountType;

@end

NS_ASSUME_NONNULL_END
