// Copyright © 2020 Apple Inc. All rights reserved.

#import <AuthenticationServices/ASAuthorizationCredential.h>
#import <AuthenticationServices/ASCOSEConstants.h>
#import <AuthenticationServices/ASFoundation.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*! @abstract The base protocol for all PublicKeyCredential credential types.
 */
API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos)
@protocol ASPublicKeyCredential <ASAuthorizationCredential>

/*! @abstract A byte sequence containing the serialized clientDataJSON blob returned by the authenticator.
 */
@property (nonatomic, readonly, copy) NSData *rawClientDataJSON;

/*! @abstract An identifier that uniquely identifies this credential.
 */
@property (nonatomic, readonly, copy) NSData *credentialID;


@end

NS_ASSUME_NONNULL_END
