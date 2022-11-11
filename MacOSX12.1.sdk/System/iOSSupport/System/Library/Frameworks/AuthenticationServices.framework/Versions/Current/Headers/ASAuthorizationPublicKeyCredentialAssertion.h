// Copyright © 2020 Apple Inc. All rights reserved.

#import <AuthenticationServices/ASPublicKeyCredential.h>
#import <Foundation/Foundation.h>

API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos)
@protocol ASAuthorizationPublicKeyCredentialAssertion <ASPublicKeyCredential>

/*! @abstract A byte sequence containing the encoded authenticatorData blob returned by the authenticator.
 */
@property (nonatomic, readonly, copy) NSData *rawAuthenticatorData;

/*! @abstract The userID provided when creating this credential.
 */
@property (nonatomic, readonly, copy) NSData *userID;

/*! @abstract The signature provided by the authenticator using the credential's private key.
 */
@property (nonatomic, readonly, copy) NSData *signature;

@end
