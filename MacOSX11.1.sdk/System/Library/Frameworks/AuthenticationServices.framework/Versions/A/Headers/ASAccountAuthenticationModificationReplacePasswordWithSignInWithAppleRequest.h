//
//  ASAccountAuthenticationModificationReplacePasswordWithSignInWithAppleRequest.h
//  AuthenticationServices Framework
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASAccountAuthenticationModificationRequest.h>

NS_ASSUME_NONNULL_BEGIN

@class ASCredentialServiceIdentifier;

AS_EXTERN API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface ASAccountAuthenticationModificationReplacePasswordWithSignInWithAppleRequest : ASAccountAuthenticationModificationRequest

/*! @abstract Creates a request for a Sign in with Apple upgrade invoked within the extension's containing app.
 @param user The username for the account to upgrade.
 @param serviceIdentifier The service identifier of the credential the user wishes to upgrade.
 @param userInfo A dictionary the app can use to pass information to the extension, most likely to help with authorizing the upgrade.
 @discussion In this flow, when the extension is invoked from within the containing app, the extension
 will receive an empty password for the credential to upgrade. It should check that it is authorized to perform
 the upgrade. The authorization check should ideally be done with information in userInfo, but may involve
 communicating with a backend server or using a shared data container between the app and extension.
*/
- (instancetype)initWithUser:(NSString *)user serviceIdentifier:(ASCredentialServiceIdentifier *)serviceIdentifier userInfo:(nullable NSDictionary *)userInfo;

@property (nonatomic, readonly) NSString *user;
@property (nonatomic, readonly) ASCredentialServiceIdentifier *serviceIdentifier;
@property (nonatomic, nullable, readonly) NSDictionary *userInfo;

@end

NS_ASSUME_NONNULL_END
