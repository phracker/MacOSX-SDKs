//
//  CKDiscoverAllUserIdentitiesOperation.h
//  CloudKit
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CloudKit/CKOperation.h>

@class CKUserIdentity;

/* Finds all discoverable users in the device's address book. No Address Book access dialog will be displayed */
NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_12, 10_0)
__TVOS_UNAVAILABLE
@interface CKDiscoverAllUserIdentitiesOperation : CKOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;

@property (nonatomic, copy, nullable) void (^userIdentityDiscoveredBlock)(CKUserIdentity *identity);
@property (nonatomic, copy, nullable) void (^discoverAllUserIdentitiesCompletionBlock)(NSError * _Nullable operationError);

@end
NS_ASSUME_NONNULL_END
