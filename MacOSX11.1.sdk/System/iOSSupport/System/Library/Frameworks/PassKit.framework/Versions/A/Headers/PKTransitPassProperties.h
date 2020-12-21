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

@property (nonatomic, assign, readonly, getter=isInStation) BOOL inStation;
@property (nonatomic, assign, readonly, getter=isBlacklisted) BOOL blacklisted;

@property (nonatomic, nullable, copy, readonly) NSDate *expirationDate; // nil if pass does not expire

@end

NS_ASSUME_NONNULL_END
