//
//  ASAuthorizationAppleIDCredential.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASAuthorization.h>
#import <AuthenticationServices/ASAuthorizationCredential.h>
#import <Foundation/Foundation.h>

/*! @enum ASUserDetectionStatus
 @constant ASUserDetectionStatusUnsupported Not supported on current platform, ignore the value
 @constant ASUserDetectionStatusUnknown We could not determine the value.  New users in the ecosystem will get this value as well, so you should not blacklist but instead treat these users as any new user through standard email sign up flows
 @constant ASUserDetectionStatusLikelyReal A hint that we have high confidence that the user is real.
 */
typedef NS_ENUM(NSInteger, ASUserDetectionStatus) {
    ASUserDetectionStatusUnsupported,
    ASUserDetectionStatusUnknown,
    ASUserDetectionStatusLikelyReal,
};

NS_ASSUME_NONNULL_BEGIN

AS_EXTERN API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0))
@interface ASAuthorizationAppleIDCredential : NSObject <ASAuthorizationCredential>

/*! @abstract An opaque user ID associated with the AppleID used for the sign in. This identifier will be stable across the 'developer team', it can later be used as an input to @see ASAuthorizationRequest to request user contact information.

 The identifier will remain stable as long as the user is connected with the requesting client.  The value may change upon user disconnecting from the identity provider.
 */
@property (nonatomic, readonly, copy) NSString *user;

/*! @abstract A copy of the state value that was passed to ASAuthorizationRequest.
 */
@property (nonatomic, readonly, copy, nullable) NSString *state;

/*! @abstract This value will contain a list of scopes for which the user provided authorization.  These may contain a subset of the requested scopes on @see ASAuthorizationAppleIDRequest.  The application should query this value to identify which scopes were returned as it maybe different from ones requested.
 */
@property (nonatomic, readonly, copy) NSArray<ASAuthorizationScope> *authorizedScopes;

/*! @abstract A short-lived, one-time valid token that provides proof of authorization to the server component of the app. The authorization code is bound to the specific transaction using the state attribute passed in the authorization request. The server component of the app can validate the code using Apple’s identity service endpoint provided for this purpose.
 */
@property (nonatomic, readonly, copy, nullable) NSData *authorizationCode;

/*! @abstract A JSON Web Token (JWT) used to communicate information about the identity of the user in a secure way to the app. The ID token will contain the following information: Issuer Identifier, Subject Identifier, Audience, Expiry Time and Issuance Time signed by Apple's identity service.
 */
@property (nonatomic, readonly, copy, nullable) NSData *identityToken;

/*! @abstract An optional email shared by the user.  This field is populated with a value that the user authorized.
 */
@property (nonatomic, readonly, copy, nullable) NSString *email;

/*! @abstract An optional full name shared by the user.  This field is populated with a value that the user authorized.
 */
@property (nonatomic, readonly, copy, nullable) NSPersonNameComponents *fullName;

/*! @abstract Check this property for a hint as to whether the current user is a "real user".  @see ASUserDetectionStatus for guidelines on handling each status
 */
@property (nonatomic, readonly) ASUserDetectionStatus realUserStatus;

+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
