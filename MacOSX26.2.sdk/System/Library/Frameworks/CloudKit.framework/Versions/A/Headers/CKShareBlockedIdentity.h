//
//  CKShareBlockedIdentity.h
//  CloudKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>


#define CK_SHARE_BLOCKED_IDENTITY_AVAILABILITY API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0))


@class CKUserIdentity, CNContact;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

CK_SHARE_BLOCKED_IDENTITY_AVAILABILITY
NS_SWIFT_NAME(CKShare.BlockedIdentity)
CK_SUBCLASSING_EXTERNALLY_RESTRICTED // should not be subclassed, or Sendable may no longer apply
NS_SWIFT_SENDABLE
@interface CKShareBlockedIdentity : NSObject <NSSecureCoding, NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// The identity of the user who has been blocked from requesting access to the share.
@property (readonly, copy, nonatomic) CKUserIdentity *userIdentity;

#if !TARGET_OS_TV

/// A displayable `CNContact` representing the blocked user.
///
/// If the blocked identity does not exist in the user's contacts or is not accessible, returns a newly created `CNContact`.
/// This provides formatted blocked identity information suitable for display in the application's UI.
@property (nonatomic, readonly, copy) CNContact *contact;

#endif

@end

NS_HEADER_AUDIT_END(nullability, sendability)
