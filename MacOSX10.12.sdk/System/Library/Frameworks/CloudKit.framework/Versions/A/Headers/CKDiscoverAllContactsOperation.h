//
//  CKDiscoverAllContactsOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CloudKit/CKOperation.h>

@class CKDiscoveredUserInfo;

/* Finds all discoverable users in the device's address book. No Address Book access dialog will be displayed */
NS_ASSUME_NONNULL_BEGIN
__TVOS_UNAVAILABLE
NS_CLASS_DEPRECATED(10_10, 10_12, 8_0, 10_0, "Use CKDiscoverAllUserIdentitiesOperation instead")
@interface CKDiscoverAllContactsOperation : CKOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;

@property (nonatomic, copy, nullable) void (^discoverAllContactsCompletionBlock)(NSArray<CKDiscoveredUserInfo *> * _Nullable userInfos, NSError * _Nullable operationError);

@end
NS_ASSUME_NONNULL_END
