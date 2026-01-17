// Copyright © 2022 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

NS_REFINED_FOR_SWIFT
AS_EXTERN API_AVAILABLE(macos(13.3), macCatalyst(16.4), ios(17.4)) API_UNAVAILABLE(tvos, watchos)
@interface ASAuthorizationWebBrowserPlatformPublicKeyCredential : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// The user name of the saved credential.
@property (nonatomic, readonly) NSString *name;

/// A user-specified title for the credential.
@property (nonatomic, nullable, readonly) NSString *customTitle AS_API_AVAILABLE(macos(14.0), macCatalyst(17.0), ios(17.4));

/// The "relying party" (generally website) the credential was saved for.
@property (nonatomic, readonly) NSString *relyingParty;

/// A unique identifier for this credential.
@property (nonatomic, readonly) NSData *credentialID;

/// A unique identifier for the user account associated with this credential. One account may have multiple associated credentials.
@property (nonatomic, readonly) NSData *userHandle;

/// The localized name of the credential provider that provided this passkey.
@property (nonatomic, readonly) NSString *providerName API_AVAILABLE(macos(14.0), macCatalyst(17.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
