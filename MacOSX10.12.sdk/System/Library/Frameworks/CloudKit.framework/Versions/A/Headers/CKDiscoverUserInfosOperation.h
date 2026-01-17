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
NS_CLASS_DEPRECATED(10_10, 10_12, 8_0, 10_0, "Use CKDiscoverUserIdentitiesOperation instead")
@interface CKDiscoverUserInfosOperation : CKOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithEmailAddresses:(nullable NSArray<NSString *> *)emailAddresses userRecordIDs:(nullable NSArray<CKRecordID *> *)userRecordIDs;

@property (nonatomic, copy, nullable) NSArray<NSString *> *emailAddresses;
@property (nonatomic, copy, nullable) NSArray<CKRecordID *> *userRecordIDs;

/*  This block is called when the operation completes.
    The [NSOperation completionBlock] will also be called if both are set. */
@property (nonatomic, copy, nullable) void (^discoverUserInfosCompletionBlock)(NSDictionary<NSString *, CKDiscoveredUserInfo *> * _Nullable emailsToUserInfos, NSDictionary<CKRecordID *, CKDiscoveredUserInfo *> * _Nullable userRecordIDsToUserInfos, NSError * _Nullable operationError);

@end
NS_ASSUME_NONNULL_END
