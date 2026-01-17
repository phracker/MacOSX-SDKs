#if !__has_include(<PassKitCore/PKSuicaPassProperties.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKSuicaPassProperties.h
//    PassKit
//
//  Copyright (c) 2016 Apple, Inc. All rights reserved.
//
//

#import <PassKit/PKTransitPassProperties.h>

@class PKPass;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.1), watchos(3.1))
@interface PKSuicaPassProperties : PKTransitPassProperties

/// Properties for a given pass, or nil if the pass doesn’t support the set of properties being requested
+ (nullable instancetype)passPropertiesForPass:(PKPass *)pass;

@property (nonatomic, copy, readonly) NSDecimalNumber *transitBalance;
@property (nonatomic, copy, readonly) NSString *transitBalanceCurrencyCode;

@property (nonatomic, assign, readonly, getter=isInStation) BOOL inStation;
/// Note: isInShinkansenStation is not a subset of isInStation.
@property (nonatomic, assign, readonly, getter=isInShinkansenStation) BOOL inShinkansenStation;

@property (nonatomic, assign, getter=isBalanceAllowedForCommute, readonly) BOOL balanceAllowedForCommute API_AVAILABLE(ios(11.3), watchos(4.3));
@property (nonatomic, assign, getter=isLowBalanceGateNotificationEnabled, readonly) BOOL lowBalanceGateNotificationEnabled API_AVAILABLE(ios(11.3), watchos(4.3));

@property (nonatomic, assign, readonly, getter=isGreenCarTicketUsed) BOOL greenCarTicketUsed;

@property (nonatomic, assign, readonly, getter=isBlacklisted) BOOL blacklisted API_DEPRECATED_WITH_REPLACEMENT("isBlocked", ios(10.1, 15.0), watchos(3.1, 8.0));

@end

NS_ASSUME_NONNULL_END

#else
#import <TargetConditionals.h>
#import <PassKitCore/PKSuicaPassProperties.h>
#endif