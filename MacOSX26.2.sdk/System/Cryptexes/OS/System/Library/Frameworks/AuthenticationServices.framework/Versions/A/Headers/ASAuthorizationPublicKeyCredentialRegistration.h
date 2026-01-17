// Copyright © 2020 Apple Inc. All rights reserved.

#import <AuthenticationServices/ASFoundation.h>
#import <AuthenticationServices/ASPublicKeyCredential.h>
#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_AVAILABLE(macos(12.0), ios(15.0), tvos(16.0)) API_UNAVAILABLE(watchos)
@protocol ASAuthorizationPublicKeyCredentialRegistration <ASPublicKeyCredential>

/*! @abstract The raw data containing the authenticator's attestation statement, if one was provided.
 */
@property (nonatomic, readonly, nullable, copy) NSData *rawAttestationObject;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
