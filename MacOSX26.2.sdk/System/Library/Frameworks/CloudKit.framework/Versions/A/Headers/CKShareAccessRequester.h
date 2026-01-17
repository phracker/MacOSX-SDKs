//
//  CKShareAccessRequester.h
//  CloudKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>


#define CK_SHARE_ACCESS_REQUESTER_AVAILABILITY API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0))


@class CKUserIdentity, CKUserIdentityLookupInfo, CNContact;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

CK_SHARE_ACCESS_REQUESTER_AVAILABILITY
NS_SWIFT_NAME(CKShare.AccessRequester)
CK_SUBCLASSING_RESTRICTED // should not be subclassed, or Sendable may no longer apply
NS_SWIFT_SENDABLE
@interface CKShareAccessRequester : NSObject <NSSecureCoding, NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// The identity of the user requesting access to the share.
@property (readonly, copy) CKUserIdentity *userIdentity;

/// Lookup information for the requester.
///
/// Use this lookup info with ``CKFetchShareParticipantsOperation`` to fetch the corresponding participant.
/// Once fetched, add the participant to the share to approve the requester.
@property (nonatomic, readonly, copy) CKUserIdentityLookupInfo *participantLookupInfo;

#if !TARGET_OS_TV

/// A displayable `CNContact` representing the requester.
///
/// If the requester doesn't exist in the user's contacts or is not accessible, returns a newly created `CNContact`.
/// This provides formatted requester information suitable for display in the application's UI.
@property (nonatomic, readonly, copy) CNContact *contact;

#endif

@end

NS_HEADER_AUDIT_END(nullability, sendability)
