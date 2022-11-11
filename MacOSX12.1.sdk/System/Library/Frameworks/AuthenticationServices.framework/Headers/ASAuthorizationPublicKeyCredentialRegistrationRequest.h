// Copyright © 2020 Apple Inc. All rights reserved.

#import <AuthenticationServices/ASAuthorizationPublicKeyCredentialConstants.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos)
@protocol ASAuthorizationPublicKeyCredentialRegistrationRequest <NSObject, NSSecureCoding, NSCopying>

/*! @abstract The Relying Party identifier used to scope this request.
 */
@property (nonatomic, readonly, copy) NSString *relyingPartyIdentifier;

/*! @abstract An arbitrary byte sequence which will be stored alongside the credential and will be returned with the credential when authenticating with it in the future. May be used by a relying party to identify the user account this credential is associated with.
 */
@property (nonatomic, copy) NSData *userID;

/*! @abstract A human readable name to associate with a credential, which a user should be able to use to identify the credential.
 */
@property (nonatomic, copy) NSString *name;

/*! @abstract A high level human readable name to associate with a credential, which should only be used for display.
 */
@property (nonatomic, nullable, copy) NSString *displayName;

/*! @abstract The challenge which can be used to verify the authenticator's attestation, if attestation is requested.
 */
@property (nonatomic, copy) NSData *challenge;

/*! @abstract A preference for whether the authenticator should attempt to verify that it is being used by its owner, such as through a PIN or biometrics.
 */
@property (nonatomic) ASAuthorizationPublicKeyCredentialUserVerificationPreference userVerificationPreference;

/*! @abstract A preference for the type of attestation that the authenticator should attempt to perform.
 */
@property (nonatomic) ASAuthorizationPublicKeyCredentialAttestationKind attestationPreference;

@end

NS_ASSUME_NONNULL_END
