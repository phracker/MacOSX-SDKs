//
//  CKShare.h
//  CloudKit
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CloudKit/CKRecord.h>
#import <CloudKit/CKShareParticipant.h>

NS_ASSUME_NONNULL_BEGIN

CK_EXTERN NSString * const CKRecordTypeShare API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

/* Predefined keys in the CKRecordTypeShare schema.  They're used by the out of process UI flow to send a share, and as part of the share acceptance flow.  These are optional */

/* Value is a string.  Example for a recipe sharing app: "Pot Roast" */
CK_EXTERN NSString * const CKShareTitleKey API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));
/* Value is a data blob suitable to pass into -[NSImage imageWithData:] or -[UIImage imageWithData:] */
CK_EXTERN NSString * const CKShareThumbnailImageDataKey API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));
/* Value is a string representing a UTI.  Example for a recipe sharing app: "com.mycompany.recipe" */
CK_EXTERN NSString * const CKShareTypeKey API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

/*
 Like CKRecords, CKShares can store arbitrary key-value pairs.  They are modified and fetched in the same manner.
 A share, its root record (and its root record's children records), will only appear in a participant's CKFetchRecordChangesOperation's results after the share has been accepted by that participant.
 Clients have access to the share (and optionally the root record) before accepting a share, via the CKShareMetadata object.  Note that in order to access a root record before accepting a share, a third party must run a CKFetchShareMetadataOperation requesting the root record.
 A CKShare will appear in a CKFetchRecordChangesOperation's results set whenever the participant list is updated.  For that reason, you shouldn't place heavy key-value pairs in it.
 */

API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))
@interface CKShare : CKRecord

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithRecordType:(NSString *)recordType NS_UNAVAILABLE;
- (instancetype)initWithRecordType:(NSString *)recordType recordID:(CKRecordID *)recordID NS_UNAVAILABLE;
- (instancetype)initWithRecordType:(NSString *)recordType zoneID:(CKRecordZoneID *)zoneID NS_UNAVAILABLE;

/* When saving a newly created CKShare, you must save the share and its rootRecord in the same CKModifyRecordsOperation batch. */
- (instancetype)initWithRootRecord:(CKRecord *)rootRecord;
- (instancetype)initWithRootRecord:(CKRecord *)rootRecord shareID:(CKRecordID *)shareID NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

/*
 Shares with publicPermission more permissive than CKShareParticipantPermissionNone can be joined by any user with access to the share's shareURL.
 This property defines what permission those users will have.
 By default, public permission is CKShareParticipantPermissionNone.
 Changing the public permission to CKShareParticipantPermissionReadOnly or CKShareParticipantPermissionReadWrite will result in all pending participants being removed.  Already-accepted participants will remain on the share.
 Changing the public permission to CKShareParticipantPermissionNone will result in all participants being removed from the share.  You may subsequently choose to call addParticipant: before saving the share, those participants will be added to the share. */
@property (nonatomic, assign) CKShareParticipantPermission publicPermission;

/* A URL that can be used to invite participants to this share. Only available after share record has been saved to the server.  This url is stable, and is tied to the rootRecord.  That is, if you share a rootRecord, delete the share, and re-share the same rootRecord via a newly created share, that newly created share's url will be identical to the prior share's url */
@property (nonatomic, readonly, copy, nullable) NSURL *URL;

/* The participants array will contain all participants on the share that the current user has permissions to see. 
   At the minimum that will include the owner and the current user. */
@property (nonatomic, readonly, strong) NSArray<CKShareParticipant *> *participants;

/* Convenience methods for fetching special users from the participant array */
@property (nonatomic, readonly, strong) CKShareParticipant *owner;
@property (nonatomic, readonly, strong, nullable) CKShareParticipant *currentUserParticipant;

/*
 If a participant with a matching userIdentity already exists, then that existing participant's properties will be updated; no new participant will be added.
 In order to modify the list of participants, a share must have publicPermission set to CKShareParticipantPermissionNone.  That is, you cannot mix-and-match private users and public users in the same share.
 Only certain participant types may be added via this API, see the comments around CKShareParticipantType
*/
- (void)addParticipant:(CKShareParticipant *)participant;
- (void)removeParticipant:(CKShareParticipant *)participant;

@end
NS_ASSUME_NONNULL_END
