//
//  ASAuthorizationOpenIDRequest.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASAuthorization.h>
#import <AuthenticationServices/ASAuthorizationRequest.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/*! @enum Operation which should be executed.
 */
typedef NSString * ASAuthorizationOpenIDOperation API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0))
NS_SWIFT_NAME(ASAuthorization.OpenIDOperation) NS_TYPED_EXTENSIBLE_ENUM;
AS_EXTERN ASAuthorizationOpenIDOperation const ASAuthorizationOperationImplicit API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0));
AS_EXTERN ASAuthorizationOpenIDOperation const ASAuthorizationOperationLogin API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0));
AS_EXTERN ASAuthorizationOpenIDOperation const ASAuthorizationOperationRefresh API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0));
AS_EXTERN ASAuthorizationOpenIDOperation const ASAuthorizationOperationLogout API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0));

AS_EXTERN API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0))
@interface ASAuthorizationOpenIDRequest : ASAuthorizationRequest

/*! @abstract The contact information to be requested from the user.  Only scopes for which this app was authorized for will be returned.
 */
@property (nonatomic, copy, nullable) NSArray<ASAuthorizationScope> *requestedScopes;

/*! @abstract State to be passed to the identity provider.  This value will be returned as a part of successful ASAuthorization response.
 @note The state size may depend on the actual technology used and an error might be returned by the request execution. 
 */
@property (nonatomic, copy, nullable) NSString *state;

/*! @abstract Nonce to be passed to the identity provider.  This value can be verified with the identity token provided as a part of successful ASAuthorization response.
 @note The nonce size may depend on the actual technology used and an error might be returned by the request execution.
 */
@property (nonatomic, copy, nullable) NSString *nonce;

/*! @abstract Operation to be executed by the request. The ASAuthorizationOperationImplicit operation interpretation depends on the credential provider implementation.
 */
@property (nonatomic, copy) ASAuthorizationOpenIDOperation requestedOperation;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

