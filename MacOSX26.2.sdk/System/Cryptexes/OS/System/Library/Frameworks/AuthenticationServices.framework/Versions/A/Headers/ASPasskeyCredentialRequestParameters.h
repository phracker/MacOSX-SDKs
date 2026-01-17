// Copyright © 2023 Apple Inc. All rights reserved.

#import <AuthenticationServices/ASFoundation.h>
#import <AuthenticationServices/ASAuthorizationPublicKeyCredentialConstants.h>
#import <Foundation/Foundation.h>

AS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class ASPasskeyAssertionCredentialExtensionInput;

/// A class that holds various parameters related to a passkey credential request.
///  This class is provided by the system to the credential provider extension when there is an active passkey request as part of
///  -[ASCredentialProviderViewController prepareCredentialListForServiceIdentifiers:requestParameters:] and should be used
///  to construct a passkey credential response using the item selected by the user from the extension's UI.
AS_EXTERN API_AVAILABLE(ios(17.0), macos(14.0)) API_UNAVAILABLE(tvos, watchos)
AS_SWIFT_SENDABLE
@interface ASPasskeyCredentialRequestParameters : NSObject <NSSecureCoding, NSCopying>

- (instancetype)init NS_UNAVAILABLE;

/// The relying party identifier for this request.
@property (nonatomic, readonly, copy) NSString *relyingPartyIdentifier;

/// Hash of client data for credential provider to sign as part of the operation.
@property (nonatomic, readonly, copy) NSData *clientDataHash;

/// A preference for whether the authenticator should attempt to verify that it is being used by its owner, such as through a PIN or biometrics.
@property (nonatomic, readonly, copy) ASAuthorizationPublicKeyCredentialUserVerificationPreference userVerificationPreference;

/// A list of allowed credential IDs for this request. An empty list means all credentials are allowed.
@property (nonatomic, readonly, copy) NSArray<NSData *> *allowedCredentials;

/// Inputs for WebAuthn extensions used for passkey assertion.
@property (nonatomic, readonly, nullable) ASPasskeyAssertionCredentialExtensionInput *extensionInput NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(18.0), macos(15.0), visionos(2.0)) API_UNAVAILABLE(watchos, tvos);

@end

AS_HEADER_AUDIT_END(nullability, sendability)
