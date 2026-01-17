//
//  ASCredentialRequest.h
//  AuthenticationServices Framework
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol ASCredentialIdentity;

/*! @enum ASCredentialRequestType
 @constant ASCredentialRequestTypePassword Password credential type.
 @constant ASCredentialRequestTypePasskeyAssertion Passkey assertion credential type.
 @constant ASCredentialRequestTypePasskeyRegistration Passkey registration credential type.
 @constant ASCredentialRequestTypeOneTimeCode One Time Code credential type.
 */
typedef NS_ENUM(NSInteger, ASCredentialRequestType) {
    ASCredentialRequestTypePassword = 0,
    ASCredentialRequestTypePasskeyAssertion,
    ASCredentialRequestTypePasskeyRegistration API_AVAILABLE(ios(18.0), macos(15.0), visionos(2.0)) API_UNAVAILABLE(tvos, watchos),
    ASCredentialRequestTypeOneTimeCode API_AVAILABLE(ios(18.0), macos(15.0), visionos(2.0)) API_UNAVAILABLE(tvos, watchos),
} API_AVAILABLE(ios(17.0), macos(14.0)) API_UNAVAILABLE(tvos, watchos);

/*! @protocol ASCredentialRequest
 ASCredentialRequest is used by Credential Provider Extensions to identify a credential to use
 for an authorization request. For passkey requests it also carries the assertion challenge to
 be used by the extension to create the assertion response.
 */
AS_EXTERN API_AVAILABLE(ios(17.0), macos(14.0)) API_UNAVAILABLE(tvos, watchos)
@protocol ASCredentialRequest <NSObject, NSSecureCoding, NSCopying>

/*! @abstract The type of credential used for this request.
 */
@property (nonatomic, readonly) ASCredentialRequestType type;

/*! @abstract The credential identity selected by the user to authenticate.
 */
@property (nonatomic, readonly) id<ASCredentialIdentity> credentialIdentity;

@end

NS_ASSUME_NONNULL_END
