//
//  CKUserIdentity.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CKRecordID, CKUserIdentityLookupInfo;

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_12, 10_0)
@interface CKUserIdentity : NSObject <NSSecureCoding, NSCopying>
// Use CKDiscoverUserIdentitiesOperation or CKFetchShareParticipantsOperation to create a CKUserIdentity
- (instancetype)init NS_UNAVAILABLE;

// This is the lookupInfo you passed in to CKDiscoverUserIdentitiesOperation or CKFetchShareParticipantsOperation
@property (nonatomic, readonly, copy, nullable) CKUserIdentityLookupInfo *lookupInfo;
@property (nonatomic, readonly, copy, nullable) NSPersonNameComponents *nameComponents;
@property (nonatomic, readonly, copy, nullable) CKRecordID *userRecordID;

@property (nonatomic, readonly, assign) BOOL hasiCloudAccount;

@end

NS_ASSUME_NONNULL_END
