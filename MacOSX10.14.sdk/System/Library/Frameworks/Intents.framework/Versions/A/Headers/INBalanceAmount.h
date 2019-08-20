//
//  INBalanceAmount.h
//  Intents
//
//  Copyright (c) 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INBalanceType.h>


NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macosx)
@interface INBalanceAmount : NSObject <NSCopying, NSSecureCoding>

- (id)init NS_UNAVAILABLE;

- (nullable instancetype)initWithAmount:(NSDecimalNumber *)amount
                            balanceType:(INBalanceType)balanceType NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithAmount:(NSDecimalNumber *)amount
                           currencyCode:(NSString *)currencyCode NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSDecimalNumber *amount;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INBalanceType balanceType;

// The ISO 4217 currency code that applies to the monetary amount.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *currencyCode;

@end

NS_ASSUME_NONNULL_END
