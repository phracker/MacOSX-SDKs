//
//  CKShareMetadata.h
//  CloudKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <CloudKit/CKShareParticipant.h>

@class CKShare, CKRecord, CKRecordID;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))
@interface CKShareMetadata : NSObject <NSCopying, NSSecureCoding>

@property (nonatomic, readonly, copy) NSString *containerIdentifier;
@property (nonatomic, readonly, copy) CKShare *share;
@property (nonatomic, readonly, copy) CKRecordID *rootRecordID;

/*! These properties reflect the participant properties of the user invoking CKFetchShareMetadataOperation */
@property (nonatomic, readonly, assign) CKShareParticipantRole participantRole API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0), watchos(5.0));
@property (nonatomic, readonly, assign) CKShareParticipantType participantType API_DEPRECATED_WITH_REPLACEMENT("participantRole", macos(10.12, 10.14), ios(10.0, 12.0), tvos(10.0, 12.0), watchos(3.0, 5.0));
@property (nonatomic, readonly, assign) CKShareParticipantAcceptanceStatus participantStatus;
@property (nonatomic, readonly, assign) CKShareParticipantPermission participantPermission;

@property (nonatomic, readonly, copy) CKUserIdentity *ownerIdentity;

/*! This is only present if the share metadata was returned from a CKFetchShareMetadataOperation with shouldFetchRootRecord set to YES */  
@property (nonatomic, readonly, copy, nullable) CKRecord *rootRecord;

@end

NS_ASSUME_NONNULL_END
