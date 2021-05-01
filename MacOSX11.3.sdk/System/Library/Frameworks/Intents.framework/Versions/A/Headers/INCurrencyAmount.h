//
//  INCurrencyAmount.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macos, tvos)
@interface INCurrencyAmount : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithAmount:(NSDecimalNumber *)amount
                  currencyCode:(NSString *)currencyCode NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSDecimalNumber *amount;

// The ISO 4217 currency code that applies to the monetary amount.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *currencyCode;

@end

NS_ASSUME_NONNULL_END
