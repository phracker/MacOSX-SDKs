//
//  CKDiscoverUserInfosOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CloudKit/CKOperation.h>

@class CKRecordID, CKDiscoveredUserInfo;

NS_ASSUME_NONNULL_BEGIN
API_DEPRECATED_WITH_REPLACEMENT("CKDiscoverUserIdentitiesOperation", macos(10.10, 10.12), ios(8.0, 10.0), tvos(9.0, 10.0), watchos(3.0, 3.0))
@interface CKDiscoverUserInfosOperation : CKOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithEmailAddresses:(nullable NSArray<NSString *> *)emailAddresses userRecordIDs:(nullable NSArray<CKRecordID *> *)userRecordIDs;

@property (nonatomic, copy, nullable) NSArray<NSString *> *emailAddresses;
@property (nonatomic, copy, nullable) NSArray<CKRecordID *> *userRecordIDs;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

/*! @abstract This block is called when the operation completes.
 *
 *  @discussion The [NSOperation completionBlock] will also be called if both are set.
 */
@property (nonatomic, copy, nullable) void (^discoverUserInfosCompletionBlock)(NSDictionary<NSString *, CKDiscoveredUserInfo *> * _Nullable emailsToUserInfos, NSDictionary<CKRecordID *, CKDiscoveredUserInfo *> * _Nullable userRecordIDsToUserInfos, NSError * _Nullable operationError);

#pragma clang diagnostic pop

@end
NS_ASSUME_NONNULL_END
