//
//  CKShareMetadata.h
//  CloudKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDefines.h>
#import <CloudKit/CKShareParticipant.h>

@class CKShare, CKRecord, CKRecordID;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))
CK_SUBCLASSING_DEPRECATED // should not be subclassed, or Sendable may no longer apply
// NS_SWIFT_SENDABLE on macos(14.0), ios(17.0), tvos(17.0), watchos(10.0)
@interface CKShareMetadata : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init CK_UNAVAILABLE("Obtain `CKShareMetadata` from ``CKFetchShareMetadataOperation`` or platform-specific scene / app delegate callbacks.");
+ (instancetype)new CK_UNAVAILABLE("Obtain `CKShareMetadata` from ``CKFetchShareMetadataOperation`` or platform-specific scene / app delegate callbacks.");

@property (readonly, copy) NSString *containerIdentifier;
@property (readonly, copy) CKShare *share;
@property (nullable, readonly, copy) CKRecordID *hierarchicalRootRecordID API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));

/*! These properties reflect the participant properties of the user invoking CKFetchShareMetadataOperation */
@property (readonly, assign) CKShareParticipantRole participantRole API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0), watchos(5.0));
@property (readonly, assign) CKShareParticipantAcceptanceStatus participantStatus;
@property (readonly, assign) CKShareParticipantPermission participantPermission;

@property (readonly, copy) CKUserIdentity *ownerIdentity;

/*! This is only present if the share metadata was returned from a CKFetchShareMetadataOperation with shouldFetchRootRecord set to YES */  
@property (nullable, readonly, copy) CKRecord *rootRecord;

@property (readonly, assign) CKShareParticipantType participantType API_OBSOLETED_WITH_REPLACEMENT("role", macos(10.12, 10.14, 16.0), ios(10.0, 12.0, 19.0), tvos(10.0, 12.0, 19.0), watchos(3.0, 5.0, 12.0));
@property (readonly, copy) CKRecordID *rootRecordID API_DEPRECATED_WITH_REPLACEMENT("hierarchicalRootRecordID", macos(10.12, 13.0), ios(10.0, 16.0), tvos(10.0, 16.0), watchos(3.0, 9.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
