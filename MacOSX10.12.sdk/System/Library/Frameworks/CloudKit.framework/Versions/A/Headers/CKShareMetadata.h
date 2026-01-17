//
//  CKShareMetadata.h
//  CloudKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <CloudKit/CKShareParticipant.h>

@class CKShare, CKRecord, CKRecordID;

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_12, 10_0)
@interface CKShareMetadata : NSObject <NSCopying, NSSecureCoding>

@property (nonatomic, readonly, copy) NSString *containerIdentifier;
@property (nonatomic, readonly, strong) CKShare *share;
@property (nonatomic, readonly, copy) CKRecordID *rootRecordID;

/* These properties reflect the participant properties of the user invoking CKFetchShareMetadataOperation */
@property (nonatomic, readonly, assign) CKShareParticipantType participantType;
@property (nonatomic, readonly, assign) CKShareParticipantAcceptanceStatus participantStatus;
@property (nonatomic, readonly, assign) CKShareParticipantPermission participantPermission;

@property (nonatomic, readonly, strong) CKUserIdentity *ownerIdentity;

/* This is only present if the share metadata was returned from a CKFetchShareMetadataOperation with shouldFetchRootRecord set to YES */  
@property (nonatomic, readonly, strong, nullable) CKRecord *rootRecord;

@end
NS_ASSUME_NONNULL_END
