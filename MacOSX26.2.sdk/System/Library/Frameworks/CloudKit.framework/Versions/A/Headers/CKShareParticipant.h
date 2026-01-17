//
//  CKShareParticipant.h
//  CloudKit
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CKUserIdentity;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NS_ENUM(NSInteger, CKShareParticipantAcceptanceStatus) {
    CKShareParticipantAcceptanceStatusUnknown,
    CKShareParticipantAcceptanceStatusPending,
    CKShareParticipantAcceptanceStatusAccepted,
    CKShareParticipantAcceptanceStatusRemoved,
} API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

/*! These permissions determine what share participants can do with records inside that share */
typedef NS_ENUM(NSInteger, CKShareParticipantPermission) {
    CKShareParticipantPermissionUnknown,
    CKShareParticipantPermissionNone,
    CKShareParticipantPermissionReadOnly,
    CKShareParticipantPermissionReadWrite,
} API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

/// Defines the participant role in a share:
/// - `owner`: Can add private users.
/// - `privateUser`: Can access the share.
/// - `publicUser`: Self-added when accessing the share URL (owners cannot add public users).
/// - `administrator`: Can add and remove participants and change their permissions.
///
/// Shares with ``CloudKit/CKShareParticipantRole/CKShareParticipantRoleAdministrator`` participants will be returned as read-only to devices running OS versions prior to this role being introduced.
/// Administrator participants on these read-only shares will be returned as ``CloudKit/CKShareParticipantRole/CKShareParticipantRolePrivateUser``.
typedef NS_ENUM(NSInteger, CKShareParticipantRole) {
    CKShareParticipantRoleUnknown = 0,
    CKShareParticipantRoleOwner = 1,
    CKShareParticipantRolePrivateUser = 3,
    CKShareParticipantRolePublicUser = 4,
    CKShareParticipantRoleAdministrator API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0)) = 2,
} API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0), watchos(5.0));

typedef NS_ENUM(NSInteger, CKShareParticipantType) {
    CKShareParticipantTypeUnknown = 0,
    CKShareParticipantTypeOwner = 1,
    CKShareParticipantTypePrivateUser = 3,
    CKShareParticipantTypePublicUser = 4,
} API_OBSOLETED_WITH_REPLACEMENT("CKShareParticipantRole", macos(10.12, 10.14, 16.0), ios(10.0, 12.0, 19.0), tvos(10.0, 12.0, 19.0), watchos(3.0, 5.0, 12.0));

API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))
// This class should not be subclassed. If it is, Sendable may no longer apply.
// NS_SWIFT_SENDABLE on macos(14.0), ios(17.0), tvos(17.0), watchos(10.0)
@interface CKShareParticipant : NSObject <NSSecureCoding, NSCopying>

/*! Use @c CKFetchShareParticipantsOperation to create a @c CKShareParticipant object */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (readonly, copy) CKUserIdentity *userIdentity;

/*! The default participant role is @c CKShareParticipantRolePrivateUser. */
@property (assign) CKShareParticipantRole role API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0), watchos(5.0));

/// The default participant type is ``CloudKit/CKShareParticipantType/CKShareParticipantTypePrivateUser``.
@property (assign) CKShareParticipantType type API_OBSOLETED_WITH_REPLACEMENT("role", macos(10.12, 10.14, 16.0), ios(10.0, 12.0, 19.0), tvos(10.0, 12.0, 19.0), watchos(3.0, 5.0, 12.0));

@property (readonly, assign) CKShareParticipantAcceptanceStatus acceptanceStatus;

/*! The default permission for a new participant is @c CKShareParticipantPermissionReadOnly. */
@property (assign) CKShareParticipantPermission permission;

/*! A unique identifier for this participant. */
@property (readonly, copy) NSString *participantID API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0)) NS_REFINED_FOR_SWIFT;

/// Indicates whether the participant was originally a requester who was approved to join the share.
@property (readonly, assign, nonatomic) BOOL isApprovedRequester API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

/// The date and time when the participant was added to the share.
///
/// This timestamp is set when the share is successfully saved to the server.
@property (nullable, readonly, copy, nonatomic) NSDate *dateAddedToShare API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

/// Generate a unique URL for inviting a participant without knowing their handle
///
/// When a participant's email address / phone number / userRecordID isn't known up-front, a ``CKShareParticipant/oneTimeURLParticipant`` can be added
/// to the share. Once the share is saved, a custom invitation link or one-time URL is available for the added participant via ``CKShare/oneTimeURLForParticipantID:``.
/// This custom link can be used by any recipient user to fetch share metadata and accept the share.
///
/// Note that a one-time URL participant in the ``ParticipantAcceptanceStatus/pending`` state has empty ``CKUserIdentity/nameComponents``
/// and a nil ``CKUserIdentity/lookupInfo``.
+ (instancetype)oneTimeURLParticipant NS_SWIFT_NAME(oneTimeURLParticipant()) API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
