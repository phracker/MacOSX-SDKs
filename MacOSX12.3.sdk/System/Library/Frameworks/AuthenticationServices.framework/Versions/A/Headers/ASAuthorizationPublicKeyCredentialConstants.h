// Copyright © 2020 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>

/*! @abstract A string indicating a preference for whether the authenticator should attempt to verify the user, such as through a PIN or biometrics.
 */
API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos, tvos)
typedef NSString *ASAuthorizationPublicKeyCredentialUserVerificationPreference NS_TYPED_EXTENSIBLE_ENUM;

/*! @abstract Indicates that the authenticator should try to verify the user if possible, but authentication should proceed even if user verification is not currently available.
 */
API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos, tvos)
extern ASAuthorizationPublicKeyCredentialUserVerificationPreference const ASAuthorizationPublicKeyCredentialUserVerificationPreferencePreferred;

/*! @abstract Indicates that the authenticator must attempt to verify the user. If the authenticator is not currently capable of verifying the user, authentication will fail.
 */
API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos, tvos)
extern ASAuthorizationPublicKeyCredentialUserVerificationPreference const ASAuthorizationPublicKeyCredentialUserVerificationPreferenceRequired;

/*! @abstract Indicates that the authenticator should prefer _not_ verifying the user, if possible. This may be used to streamline an authentication process where the user has already been verified.
 */
API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos, tvos)
extern ASAuthorizationPublicKeyCredentialUserVerificationPreference const ASAuthorizationPublicKeyCredentialUserVerificationPreferenceDiscouraged;

/*! @abstract A string indicating the type of attestation the authenticator should attempt to perform.
 */
API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos, tvos)
typedef NSString *ASAuthorizationPublicKeyCredentialAttestationKind NS_TYPED_EXTENSIBLE_ENUM;

/*! @abstract Indicates that the authenticator should not perform attestation.
 */
API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos, tvos)
extern ASAuthorizationPublicKeyCredentialAttestationKind const ASAuthorizationPublicKeyCredentialAttestationKindNone;

/*! @abstract Indicates that the authenticator should perform attestation itself.
 */
API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos, tvos)
extern ASAuthorizationPublicKeyCredentialAttestationKind const ASAuthorizationPublicKeyCredentialAttestationKindDirect;

/*! @abstract Indicates that the authenticator may use an external service to perform attestation.
 */
API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos, tvos)
extern ASAuthorizationPublicKeyCredentialAttestationKind const ASAuthorizationPublicKeyCredentialAttestationKindIndirect;

/*! @abstract Indicates that the authenticator should perform an attestation which may include information that uniquely identifies that authenticator. Authenticators should only allow enterprise attestation if they have been previously enrolled in enterprise management, and should restrict it to managed Relying Parties.
 */
API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos, tvos)
extern ASAuthorizationPublicKeyCredentialAttestationKind const ASAuthorizationPublicKeyCredentialAttestationKindEnterprise;

/*! @abstract A string used to indicate a preference for whether the authenticator should itself store the private key for a credential.
 */
API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos, tvos)
typedef NSString *ASAuthorizationPublicKeyCredentialResidentKeyPreference NS_TYPED_EXTENSIBLE_ENUM;

/*! @abstract Indicates that the authenticator should not store the private key, if possible.
 */
API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos, tvos)
extern ASAuthorizationPublicKeyCredentialResidentKeyPreference const ASAuthorizationPublicKeyCredentialResidentKeyPreferenceDiscouraged;

/*! @abstract Indicates that the authenticator should store the private key, if possible.
 */
API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos, tvos)
extern ASAuthorizationPublicKeyCredentialResidentKeyPreference const ASAuthorizationPublicKeyCredentialResidentKeyPreferencePreferred;

/*! @abstract Indicates that the authenticator must store the private key, and that key creation should fail if the authenticator is not currently capable of storing the key.
 */
API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos, tvos)
extern ASAuthorizationPublicKeyCredentialResidentKeyPreference const ASAuthorizationPublicKeyCredentialResidentKeyPreferenceRequired;
