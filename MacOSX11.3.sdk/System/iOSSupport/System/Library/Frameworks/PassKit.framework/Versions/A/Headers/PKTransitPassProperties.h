//
//  PKTransitPassProperties.h
//  PassKit
//
//  Copyright © 2017 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class PKPass;

API_AVAILABLE(ios(11.3), watchos(4.3))
@interface PKTransitPassProperties : NSObject

+ (nullable instancetype)passPropertiesForPass:(PKPass *)pass;

@property (nonatomic, copy, readonly) NSDecimalNumber *transitBalance;
@property (nonatomic, copy, readonly) NSString *transitBalanceCurrencyCode;

@property (nonatomic, assign, readonly, getter=isBlacklisted) BOOL blacklisted API_DEPRECATED_WITH_REPLACEMENT("isBlocked", ios(11.3, 14.5), watchos(4.3, 6.4));

@property (nonatomic, assign, readonly, getter=isBlocked) BOOL blocked API_AVAILABLE(ios(14.5), watchos(6.4));

@property (nonatomic, assign, readonly, getter=isInStation) BOOL inStation;

@property (nonatomic, nullable, copy, readonly) NSDate *expirationDate; // nil if pass does not expire

@end

NS_ASSUME_NONNULL_END
