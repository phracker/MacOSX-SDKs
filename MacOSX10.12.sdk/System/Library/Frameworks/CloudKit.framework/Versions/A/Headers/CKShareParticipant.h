//
//  CKShareParticipant.h
//  CloudKit
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CKUserIdentity;

NS_ASSUME_NONNULL_BEGIN
typedef NS_ENUM(NSInteger, CKShareParticipantAcceptanceStatus) {
    CKShareParticipantAcceptanceStatusUnknown,
    CKShareParticipantAcceptanceStatusPending,
    CKShareParticipantAcceptanceStatusAccepted,
    CKShareParticipantAcceptanceStatusRemoved,
} NS_ENUM_AVAILABLE(10_12, 10_0);

/* These permissions determine what share participants can do with records inside that share */
typedef NS_ENUM(NSInteger, CKShareParticipantPermission) {
    CKShareParticipantPermissionUnknown,
    CKShareParticipantPermissionNone,
    CKShareParticipantPermissionReadOnly,
    CKShareParticipantPermissionReadWrite,
} NS_ENUM_AVAILABLE(10_12, 10_0);

/* The participant type determines whether a participant can modify the list of participants on a share.
    - Owners can add private users
    - Private users can access the share
    - Public users are "self-added" when the participant accesses the shareURL.  Owners cannot add public users.
 */
typedef NS_ENUM(NSInteger, CKShareParticipantType) {
    CKShareParticipantTypeUnknown = 0,
    CKShareParticipantTypeOwner = 1,
    CKShareParticipantTypePrivateUser = 3,
    CKShareParticipantTypePublicUser = 4,
} NS_ENUM_AVAILABLE(10_12, 10_0);


NS_CLASS_AVAILABLE(10_12, 10_0)
@interface CKShareParticipant : NSObject <NSSecureCoding, NSCopying>

/* Use CKFetchShareParticipantsOperation to create a CKShareParticipant object */
- (instancetype)init NS_UNAVAILABLE;

@property (nonatomic, readonly, strong) CKUserIdentity *userIdentity;

/* The default participant type is CKShareParticipantTypePrivateUser. */
@property (nonatomic, assign) CKShareParticipantType type;

@property (nonatomic, readonly, assign) CKShareParticipantAcceptanceStatus acceptanceStatus;

/* The default permission for a new participant is CKShareParticipantPermissionReadOnly. */
@property (nonatomic, assign) CKShareParticipantPermission permission;

@end
NS_ASSUME_NONNULL_END
