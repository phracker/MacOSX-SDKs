//
//  ASAuthorizationAppleIDProvider.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASAuthorizationAppleIDRequest.h>
#import <AuthenticationServices/ASAuthorizationProvider.h>
#import <AuthenticationServices/ASFoundation.h>

NS_ASSUME_NONNULL_BEGIN

/*! @enum ASAuthorizationAppleIDProviderCredentialState
 @abstract Authorization state of an Apple ID credential.
 @constant ASAuthorizationAppleIDProviderCredentialAuthorized The Opaque user ID is in good state.
 @constant ASAuthorizationAppleIDProviderCredentialRevoked The Opaque user ID was revoked by the user.
 @constant ASAuthorizationAppleIDProviderCredentialNotFound The Opaque user ID was not found.
 */
typedef NS_ENUM(NSInteger, ASAuthorizationAppleIDProviderCredentialState) {
    ASAuthorizationAppleIDProviderCredentialRevoked,
    ASAuthorizationAppleIDProviderCredentialAuthorized,
    ASAuthorizationAppleIDProviderCredentialNotFound,
    ASAuthorizationAppleIDProviderCredentialTransferred,
} NS_SWIFT_NAME(ASAuthorizationAppleIDProvider.CredentialState) API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0));

AS_EXTERN NSNotificationName const ASAuthorizationAppleIDProviderCredentialRevokedNotification API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0));

AS_EXTERN API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0))
@interface ASAuthorizationAppleIDProvider : NSObject <ASAuthorizationProvider>

/*!
 @abstract This method initializes and returns an instance of @see ASAuthorizationAppleIDRequest to be serviced by @see ASAuthorizationController.
 */
- (ASAuthorizationAppleIDRequest *)createRequest;

/*!
 @abstract This method can be used to get the current state of an opaque user ID previously given.
 @param userID Opaque user identifier that will be checked for state.
 @param completion A completion block that will return one of 3 possible states @see ASAuthorizationAppleIDProviderCredentialState.
 
 @note If credentialState is @see ASAuthorizationAppleIDProviderCredentialNotFound, an error will also be passed in the completion block.
 */
- (void)getCredentialStateForUserID:(NSString *)userID completion:(void (^)(ASAuthorizationAppleIDProviderCredentialState credentialState, NSError * _Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
