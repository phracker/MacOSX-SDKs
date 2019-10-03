//
//  CKDiscoverAllUserIdentitiesOperation.h
//  CloudKit
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CloudKit/CKOperation.h>

@class CKUserIdentity;

NS_ASSUME_NONNULL_BEGIN

/*! @class CKDiscoverAllUserIdentitiesOperation
 *
 *  @abstract Finds all discoverable users in the device's contacts database. No Contacts access dialog will be displayed.
 *
 *  @discussion This operation scales linearly with the number of email addresses and phone numbers in the device's address book.  It may take some time to complete.
 */
API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0))
API_UNAVAILABLE(tvos)
@interface CKDiscoverAllUserIdentitiesOperation : CKOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;

@property (nonatomic, copy, nullable) void (^userIdentityDiscoveredBlock)(CKUserIdentity *identity);
@property (nonatomic, copy, nullable) void (^discoverAllUserIdentitiesCompletionBlock)(NSError * _Nullable operationError);

@end
NS_ASSUME_NONNULL_END
