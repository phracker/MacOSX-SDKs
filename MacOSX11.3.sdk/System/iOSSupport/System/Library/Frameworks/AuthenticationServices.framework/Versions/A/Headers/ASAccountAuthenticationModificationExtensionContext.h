//
//  ASAccountAuthenticationModificationExtensionContext.h
//  AuthenticationServices Framework
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASExtensionErrors.h>
#import <AuthenticationServices/ASFoundation.h>
#import <Foundation/Foundation.h>

@class ASAuthorizationAppleIDCredential;
@class ASPasswordCredential;

NS_ASSUME_NONNULL_BEGIN

AS_EXTERN API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface ASAccountAuthenticationModificationExtensionContext : NSExtensionContext

/*! @abstract Retrieves a Sign in with Apple credential from the system.
 @param state Can be specified to enhance security. State is returned in the ASAuthorizationAppleIDCredential.
 @param nonce Can be specified to enhance security. The returned identityToken on the ASAuthorizationAppleIDCredential can be exchanged with the server for the nonce.
 @discussion Calling this method will cause the system Sign in with Apple upgrade sheet
 to appear. If extension UI is showing when this method is called, the extension UI will be
 dismissed before the sheet is presented.
*/
- (void)getSignInWithAppleUpgradeAuthorizationWithState:(nullable NSString *)state nonce:(nullable NSString *)nonce completionHandler:(void(^)(ASAuthorizationAppleIDCredential * _Nullable authorization, NSError * _Nullable error))completionHandler NS_SWIFT_NAME(getSignInWithAppleUpgradeAuthorization(state:nonce:completionHandler:));

/*! @abstract Confirms successful completion of a Sign in with Apple upgrade.
 @param userInfo For upgrades invoked within the extension's containing app, any
 information the extension wants to pass back to the app.
 @discussion Once a Sign in with Apple upgrade is completed, the system will delete
 the password-based credential from the Keychain, if it is saved there.
*/
- (void)completeUpgradeToSignInWithAppleWithUserInfo:(nullable NSDictionary *)userInfo NS_SWIFT_NAME(completeUpgradeToSignInWithApple(userInfo:));

/*! @abstract Confirms successful completion of a strong password upgrade.
 @param updatedCredential contains the account username and new password.
 @param userInfo For upgrades invoked within the extension's containing app, any
 information the extension wants to pass back to the app.
*/
- (void)completeChangePasswordRequestWithUpdatedCredential:(ASPasswordCredential *)updatedCredential userInfo:(nullable NSDictionary *)userInfo NS_SWIFT_NAME(completeChangePasswordRequest(updatedCredential:userInfo:));

/*! @abstract Used to either ask for user interaction in a request or to fail a request.
*/
- (void)cancelRequestWithError:(NSError *)error;

@end

NS_ASSUME_NONNULL_END
