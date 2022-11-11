// Copyright © 2020 Apple Inc. All rights reserved.

#import <AuthenticationServices/ASFoundation.h>
#import <AuthenticationServices/ASPublicKeyCredential.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos, tvos)
@protocol ASAuthorizationPublicKeyCredentialRegistration <ASPublicKeyCredential>

/*! @abstract The raw data containing the authenticator's attestation statement, if one was provided.
 */
@property (nonatomic, readonly, nullable, copy) NSData *rawAttestationObject;


@end

NS_ASSUME_NONNULL_END
