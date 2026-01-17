//
//  CKDiscoverUserInfosOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CloudKit/CKOperation.h>

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKDiscoverUserInfosOperation : CKOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithEmailAddresses:(NSArray /* NSString */ *)emailAddresses userRecordIDs:(NSArray /* CKRecordID */ *)userRecordIDs;

@property (nonatomic, copy) NSArray /* NSString */ *emailAddresses;
@property (nonatomic, copy) NSArray /* CKRecordID */ *userRecordIDs;

/*  This block is called when the operation completes.
    The [NSOperation completionBlock] will also be called if both are set. */
@property (nonatomic, copy) void (^discoverUserInfosCompletionBlock)(NSDictionary /* NSString -> CKDiscoveredUserInfo */ *emailsToUserInfos, NSDictionary /* CKRecordID -> CKDiscoveredUserInfo */ *userRecordIDsToUserInfos, NSError *operationError);

@end
