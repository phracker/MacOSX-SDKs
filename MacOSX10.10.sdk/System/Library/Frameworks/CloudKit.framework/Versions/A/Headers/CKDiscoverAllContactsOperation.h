//
//  CKDiscoverAllContactsOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CloudKit/CKOperation.h>

/* Finds all discoverable users in the device's address book. No Address Book access dialog will be displayed */
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKDiscoverAllContactsOperation : CKOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;

@property (nonatomic, copy) void (^discoverAllContactsCompletionBlock)(NSArray /* CKDiscoveredUserInfo */ *userInfos, NSError *operationError);

@end
