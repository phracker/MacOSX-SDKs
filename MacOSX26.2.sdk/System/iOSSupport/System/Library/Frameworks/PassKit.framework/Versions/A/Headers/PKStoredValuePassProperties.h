#if !__has_include(<PassKitCore/PKStoredValuePassProperties.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKStoredValuePassProperties.h
//    PassKit
//
//  Copyright © 2020 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class PKPass;
@class PKStoredValuePassBalance;

API_AVAILABLE(ios(15.0), watchos(8.0))
@interface PKStoredValuePassProperties : NSObject

+ (nullable instancetype)passPropertiesForPass:(PKPass *)pass;

@property (nonatomic, assign, readonly, getter=isBlacklisted) BOOL blacklisted API_DEPRECATED_WITH_REPLACEMENT("isBlocked", ios(15.0, 15.0), watchos(8.0, 8.0), macos(12.0, 12.0));

@property (nonatomic, assign, readonly, getter=isBlocked) BOOL blocked API_AVAILABLE(ios(15.0), watchos(8.0), macos(12.0)) NS_REFINED_FOR_SWIFT;

@property (nonatomic, nullable, copy, readonly) NSDate *expirationDate; // nil if pass does not expire

@property (nonatomic, copy, readonly) NSArray<PKStoredValuePassBalance*> *balances;

@end

NS_ASSUME_NONNULL_END

#else
#import <TargetConditionals.h>
#import <PassKitCore/PKStoredValuePassProperties.h>
#endif