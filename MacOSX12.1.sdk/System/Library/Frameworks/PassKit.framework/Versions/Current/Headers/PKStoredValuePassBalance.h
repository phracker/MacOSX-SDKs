//
//  PKStoredValuePassBalance.h
//  PassKit
//
//  Copyright © 2020 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSString * PKStoredValuePassBalanceType NS_TYPED_ENUM NS_SWIFT_NAME(PKStoredValuePassBalance.BalanceType);
extern PKStoredValuePassBalanceType const PKStoredValuePassBalanceTypeCash API_AVAILABLE(ios(15.0), watchos(8.0));
extern PKStoredValuePassBalanceType const PKStoredValuePassBalanceTypeLoyaltyPoints API_AVAILABLE(ios(15.0), watchos(8.0));

API_AVAILABLE(ios(15.0), watchos(8.0))
@interface PKStoredValuePassBalance : NSObject

@property (nonatomic, strong, readonly) NSDecimalNumber *amount NS_REFINED_FOR_SWIFT;
@property (nonatomic, copy, readonly, nullable) NSString *currencyCode;
@property (nonatomic, copy, readonly) PKStoredValuePassBalanceType balanceType;
@property (nonatomic, strong, readonly, nullable) NSDate *expiryDate;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

- (BOOL)isEqualToBalance:(PKStoredValuePassBalance *)balance NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
