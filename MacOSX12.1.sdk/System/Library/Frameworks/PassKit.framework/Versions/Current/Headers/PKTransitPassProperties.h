//
//  PKTransitPassProperties.h
//  PassKit
//
//  Copyright © 2017 Apple, Inc. All rights reserved.
//

#import <PassKit/PKStoredValuePassProperties.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.3), watchos(4.3))
@interface PKTransitPassProperties : PKStoredValuePassProperties

@property (nonatomic, copy, readonly) NSDecimalNumber *transitBalance API_DEPRECATED_WITH_REPLACEMENT("balances", ios(11.3, 15.0), watchos(4.3, 8.0), macos(11.0, 12.0));
@property (nonatomic, copy, readonly) NSString *transitBalanceCurrencyCode API_DEPRECATED_WITH_REPLACEMENT("balances", ios(11.3, 15.0), watchos(4.3, 8.0), macos(11.0, 12.0));

@property (nonatomic, assign, readonly, getter=isBlacklisted) BOOL blacklisted API_DEPRECATED_WITH_REPLACEMENT("isBlocked", ios(11.3, 15.0), watchos(4.3, 8.0), macos(11.0, 12.0));

@property (nonatomic, nullable, copy, readonly) NSDate *expirationDate API_AVAILABLE(ios(11.3), watchos(4.3), macos(11.0)); // nil if pass does not expire

@property (nonatomic, assign, readonly, getter=isBlocked) BOOL blocked API_AVAILABLE(ios(14.5), watchos(7.5), macos(11.3));

@property (nonatomic, assign, readonly, getter=isInStation) BOOL inStation;

@end

NS_ASSUME_NONNULL_END
