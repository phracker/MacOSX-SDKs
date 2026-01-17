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
API_DEPRECATED_WITH_REPLACEMENT("CKDiscoverAllUserIdentitiesOperation", macos(10.10, 10.12), ios(8.0, 10.0), watchos(3.0, 3.0))
API_UNAVAILABLE(tvos)
@interface CKDiscoverAllContactsOperation : CKOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

@property (nonatomic, copy, nullable) void (^discoverAllContactsCompletionBlock)(NSArray<CKDiscoveredUserInfo *> * _Nullable userInfos, NSError * _Nullable operationError);

#pragma clang diagnostic pop

@end
NS_ASSUME_NONNULL_END
