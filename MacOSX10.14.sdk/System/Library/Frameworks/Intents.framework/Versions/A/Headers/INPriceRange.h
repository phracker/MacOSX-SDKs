//
//  INPriceRange.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx)
@interface INPriceRange : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

// "(min amount) to (max amount)"
- (instancetype)initWithRangeBetweenPrice:(NSDecimalNumber *)firstPrice andPrice:(NSDecimalNumber *)secondPrice currencyCode:(NSString *)currencyCode NS_SWIFT_NAME(init(firstPrice:secondPrice:currencyCode:)) NS_DESIGNATED_INITIALIZER;

// "Up to (amount)."
- (instancetype)initWithMaximumPrice:(NSDecimalNumber *)maximumPrice currencyCode:(NSString *)currencyCode NS_SWIFT_NAME(init(maximumPrice:currencyCode:)) NS_DESIGNATED_INITIALIZER;

// "Starting from (amount)."
- (instancetype)initWithMinimumPrice:(NSDecimalNumber *)minimumPrice currencyCode:(NSString *)currencyCode NS_SWIFT_NAME(init(minimumPrice:currencyCode:)) NS_DESIGNATED_INITIALIZER;

// "(amount)". Convenience initializer.
- (instancetype)initWithPrice:(NSDecimalNumber *)price currencyCode:(NSString *)currencyCode NS_SWIFT_NAME(init(price:currencyCode:));

// If a value is nil, the interval is open in that direction. Only one of these properties may be nil.
@property (readonly, nullable, NS_NONATOMIC_IOSONLY) NSDecimalNumber *minimumPrice; // The lowest of the two prices used to construct this range.

@property (readonly, nullable, NS_NONATOMIC_IOSONLY) NSDecimalNumber *maximumPrice; // The highest of the two prices used to construct this range.

@property (readonly, NS_NONATOMIC_IOSONLY) NSString *currencyCode; // A ISO 4217 currency code. For a list of currency codes, see +[NSLocale ISOCurrencyCodes].

@end

NS_ASSUME_NONNULL_END
