//
//  ASAuthorizationSingleSignOnCredential.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASAuthorization.h>
#import <AuthenticationServices/ASAuthorizationCredential.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

AS_EXTERN API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(tvos, watchos)
@interface ASAuthorizationSingleSignOnCredential : NSObject <ASAuthorizationCredential>

/*! @abstract A state returned from the AuthenticationServices extension.
 */
@property (nonatomic, readonly, copy, nullable) NSString *state;

/*! @abstract An access token used to access other systems with the authorized scopes.
 */
@property (nonatomic, readonly, copy, nullable) NSData *accessToken;

/*! @abstract A JSON Web Token (JWT) used to communicate information about the identity of the user in a secure way to the app.
 */
@property (nonatomic, readonly, copy, nullable) NSData *identityToken;

/*! @abstract This value will contain a list of scopes for which the user provided authorization.  These may contain a subset of the requested scopes on @see ASAuthorizationOpenIDRequest.  The application should query this value to identify which scopes were returned as it maybe different from ones requested.
 */
@property (nonatomic, readonly, copy) NSArray<ASAuthorizationScope> *authorizedScopes;

/*! @abstract The complete AuthenticationServices extension response with the additional outputs used by the specific technology used by the Authorization Server instance and AuthenticationServices Extension.
 @note for some operations all properties can be null and the response will indicate just successful result of the operation.
 */
@property (nonatomic, copy, readonly, nullable) NSHTTPURLResponse *authenticatedResponse;

/*! @abstract Private SecKeys returned from the AuthenticationServices extension.
 */
@property (nonatomic, readonly) NSArray *privateKeys API_AVAILABLE(ios(15.0), macos(12.0)) API_UNAVAILABLE(tvos, watchos) NS_REFINED_FOR_SWIFT;

+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
