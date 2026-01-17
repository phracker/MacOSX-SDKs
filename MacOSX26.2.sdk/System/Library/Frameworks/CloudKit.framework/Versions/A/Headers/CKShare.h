//
//  CKShare.h
//  CloudKit
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CloudKit/CKRecord.h>
#import <CloudKit/CKShareParticipant.h>


#define CKSHARE_REQUEST_ACCESS_INTERFACES_AVAILABILITY API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0))


@class CKShareAccessRequester, CKShareBlockedIdentity, CKUserIdentityLookupInfo;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

CK_EXTERN CKRecordType const CKRecordTypeShare API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

/*! A zone-wide CKShare always uses the record name @c CKRecordNameZoneWideShare.
 *  You can use this to fetch the @c CKShare record for the zone with a @c CKFetchRecordsOperation.
 */
CK_EXTERN NSString * const CKRecordNameZoneWideShare API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));

/*! Predefined keys in the @c CKRecordTypeShare schema.  They're used by the out of process UI flow to send a share, and as part of the share acceptance flow.  These are optional */

/*! Value is a string.  Example for a recipe sharing app: "Pot Roast" */
CK_EXTERN CKRecordFieldKey const CKShareTitleKey API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));
/*! Value is a data blob suitable to pass into @code -[NSImage imageWithData:] or -[UIImage imageWithData:] @endcode */
CK_EXTERN CKRecordFieldKey const CKShareThumbnailImageDataKey API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));
/*! Value is a string representing a UTI.  Example for a recipe sharing app: "com.mycompany.recipe" */
CK_EXTERN CKRecordFieldKey const CKShareTypeKey API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

/*! @class CKShare
 *
 *  @discussion Like CKRecords, CKShares can store arbitrary key-value pairs.  They are modified and fetched in the same manner.
 *  A share, its root record, and its root record's children records will only appear in a participant's CKFetchRecordChangesOperation's results after the share has been accepted by that participant.
 *  Clients have access to the share (and optionally the root record) before accepting a share, via the CKShareMetadata object.  Note that in order to access a root record before accepting a share, you must run a CKFetchShareMetadataOperation requesting the root record.
 *  A CKShare will appear in a CKFetchRecordChangesOperation's results set whenever the participant list is updated.  For that reason, you shouldn't place heavy key-value pairs in it.
 */

API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))
// This class should not be subclassed. If it is, Sendable may no longer apply.
// NS_SWIFT_SENDABLE on macos(14.0), ios(17.0), tvos(17.0), watchos(10.0)
@interface CKShare : CKRecord <NSSecureCoding, NSCopying>

/*! When saving a newly created CKShare, you must save the share and its rootRecord in the same CKModifyRecordsOperation batch. */
- (instancetype)initWithRootRecord:(CKRecord *)rootRecord;
- (instancetype)initWithRootRecord:(CKRecord *)rootRecord shareID:(CKRecordID *)shareID NS_DESIGNATED_INITIALIZER;

/*! Creates a zone-wide @c CKShare.  A zone-wide @c CKShare can only exist in a zone with sharing capability @c CKRecordZoneCapabilityZoneWideSharing.
 * Only one such share can exist in a zone at a time.
 *
 * All records in this zone will appear in a participant's @c CKFetchRecordZoneChangesOperation results in the shared database after the
 * share has been accepted by the participant.
 *
 * Since these shares do not have an associated root record, @c shouldFetchRootRecord and @c rootRecordDesiredKeys are always ignored when
 * running a @c CKFetchShareMetadataOperation on a zone-wide share URL. Additionally, @c rootRecordID on the resulting @c CKShareMetadata is
 * always absent.
 */
- (instancetype)initWithRecordZoneID:(CKRecordZoneID *)recordZoneID NS_DESIGNATED_INITIALIZER API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));

- (instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

/*! @abstract Defines what permission a user has when not explicitly added to the share.
 *
 *  @discussion Shares with @c publicPermission more permissive than @c CKShareParticipantPermissionNone can be joined by any user with access to the share's shareURL.
 *  By default, public permission is @c CKShareParticipantPermissionNone.
 *  Changing the public permission to @c CKShareParticipantPermissionReadOnly or @c CKShareParticipantPermissionReadWrite will result in all pending participants being removed.  Already-accepted participants will remain on the share.
 *  Changing the public permission to @c CKShareParticipantPermissionNone will result in all participants being removed from the share.  You may subsequently choose to call @c addParticipant: before saving the share, those participants will be added to the share.
 */
@property (assign) CKShareParticipantPermission publicPermission;

/*! @abstract A URL that can be used to invite participants to this share.
 *
 *  @discussion Only available after share record has been saved to the server.  This url is stable, and is tied to the rootRecord.  That is, if you share a rootRecord, delete the share, and re-share the same rootRecord via a newly created share, that newly created share's url will be identical to the prior share's url
 */
@property (nullable, readonly, copy) NSURL *URL;

/*! @abstract All participants on the share that the current user has permissions to see.
 *
 *  @discussion At the minimum that will include the owner and the current user.
 */
@property (readonly, copy) NSArray<CKShareParticipant *> *participants;

/*! Convenience methods for fetching special users from the participant array */
@property (readonly, copy) CKShareParticipant *owner;
@property (nullable, readonly, copy) CKShareParticipant *currentUserParticipant;

/*! @discussion If a participant with a matching userIdentity already exists, then that existing participant's properties will be updated; no new participant will be added.
 *  A ``CKShareParticipant`` instance that has already been added to one ``CKShare`` cannot be added to another, unless it is removed from the first ``CKShare`` through `removeParticipant`.
 *  In order to modify the list of participants, a share must have publicPermission set to @c CKShareParticipantPermissionNone.  That is, you cannot mix-and-match private users and public users in the same share.
 *  @see CKShareParticipantRole
 */
- (void)addParticipant:(CKShareParticipant *)participant;

/*! @discussion It's not allowed to call `removeParticipant` on a ``CKShare`` with a ``CKShareParticipant`` that has never been added to that share through `addParticipant`.
 */
- (void)removeParticipant:(CKShareParticipant *)participant;

/// Invitation URLs that can be used by any receiver to claim the associated participantID and join the share.
///
/// Only available after a share record has been saved to the server for participants created via ``CKShareParticipant/oneTimeURLParticipant``.
/// One-time URLs are stable, and tied to the associated participantIDs as long as the participant is part of the share.
/// Typically, a recipient user invited via their handle is provided a ``URL`` directly by the share's owner.
/// However, any user can also use a one-time URL in the same manner to fetch share metadata and accept the share.
/// After share acceptance, the one-time URL becomes functionally equivalent to the regular ``URL``.
///
/// - Parameters:
///   - participantID: The ``CKShareParticipant/participantID`` corresponding to the ``CKShareParticipant/oneTimeURLParticipant`` added to the share.
- (nullable NSURL *)oneTimeURLForParticipantID:(NSString *)participantID API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0)) NS_REFINED_FOR_SWIFT;

/*! These superclass-provided initializers are not allowed for CKShare */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)initWithRecordType:(CKRecordType)recordType NS_UNAVAILABLE;
- (instancetype)initWithRecordType:(CKRecordType)recordType recordID:(CKRecordID *)recordID NS_UNAVAILABLE;
- (instancetype)initWithRecordType:(CKRecordType)recordType zoneID:(CKRecordZoneID *)zoneID NS_UNAVAILABLE;

/// A list of all uninvited users who have requested access to this share.
///
/// When share access requests are allowed, uninvited users can request to join the share.
/// All pending access requests appear in this array. Each requester is returned with name components
/// and either an email or phone number.
///
/// Either share owners or administrators can respond to these access requests.
///
/// ### Responding to Access Requests:
///
/// - **Approve Requesters:**
///     - Fetch the participant information by running ``CKFetchShareParticipantsOperation`` with
///       the requester's ``CKShareAccessRequester/participantLookupInfo``.
///     - Add the resulting participant to the share.
///
/// - **Deny Requesters:**
///     - Use ``CloudKit/CKShare/denyRequesters:`` to remove the requester from the requesters list.
///
/// - **Block Requesters:**
///     - Use ``CloudKit/CKShare/blockRequesters:`` to block requesters.
///     - Blocking a requester prevents them from sending future access requests to the share.
@property (readonly, copy) NSArray<CKShareAccessRequester *> *requesters CKSHARE_REQUEST_ACCESS_INTERFACES_AVAILABILITY;

/// A list of users blocked from requesting access to this share.
///
/// Identities remain in this list until an owner or administrator calls ``CloudKit/CKShare/unblockIdentities:``.
@property (readonly, copy) NSArray<CKShareBlockedIdentity *> *blockedIdentities CKSHARE_REQUEST_ACCESS_INTERFACES_AVAILABILITY;

/// Indicates whether uninvited users can request access to this share.
///
/// By default, this property is set to `NO`. When set to `YES`, uninvited users can request
/// access to the share if they discover the share URL. When set to `NO`, the server prevents uninvited users
/// from requesting access and does not indicate whether the share exists.
///
/// Only the share owner or an administrator can modify this property. Attempts by other participants
/// to modify this property result in an exception.
@property (readwrite, assign) BOOL allowsAccessRequests CKSHARE_REQUEST_ACCESS_INTERFACES_AVAILABILITY;

/// Denies access requests from specified users.
///
/// Use this method to deny pending access requests from uninvited users. Denied requesters are removed
/// from the ``CloudKit/CKShare/requesters`` array. To persist the changes, save the share to the server
/// after calling this method.
///
/// After denial, requesters can still submit new access requests unless explicitly blocked using
/// ``CloudKit/CKShare/blockRequesters:``.
///
/// Only the share owner or an administrator can invoke this method. Attempts by other participants
/// result in an exception.
///
/// - Parameter requesters: An array of ``CKShareAccessRequester`` objects to deny.
- (void)denyRequesters:(NSArray<CKShareAccessRequester *> *)requesters CKSHARE_REQUEST_ACCESS_INTERFACES_AVAILABILITY;

/// Blocks specified users from requesting access to this share.
///
/// Blocking prevents users from submitting future access requests and removes existing participants from the share.
/// Blocked requesters appear in the ``CloudKit/CKShare/blockedIdentities`` array.
///
/// To persist this change, save the share to the server after calling this method.
///
/// Only the share owner or an administrator can invoke this method. Attempts by other participants
/// result in an exception.
///
/// - Parameter requesters: An array of ``CKShareAccessRequester`` objects to block.
- (void)blockRequesters:(NSArray<CKShareAccessRequester *> *)requesters CKSHARE_REQUEST_ACCESS_INTERFACES_AVAILABILITY;

/// Unblocks previously blocked users, allowing them to request access again.
///
/// Use this method to remove specified identities from the ``CloudKit/CKShare/blockedIdentities`` array.
/// Unblocked identities can request access again if access requests are enabled.
///
/// To persist this change, save the share to the server after calling this method.
///
/// Only the share owner or an administrator can invoke this method. Attempts by other participants
/// result in an exception.
///
/// - Parameter blockedIdentities: An array of ``CKShareBlockedIdentity`` objects to unblock.
- (void)unblockIdentities:(NSArray<CKShareBlockedIdentity *> *)blockedIdentities CKSHARE_REQUEST_ACCESS_INTERFACES_AVAILABILITY;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
