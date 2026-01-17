// Copyright © 2020 Apple Inc. All rights reserved.

#import <AuthenticationServices/ASAuthorizationProvider.h>
#import <AuthenticationServices/ASAuthorizationWebBrowserSecurityKeyPublicKeyCredentialProvider.h>
#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class ASAuthorizationSecurityKeyPublicKeyCredentialAssertionRequest;
@class ASAuthorizationSecurityKeyPublicKeyCredentialRegistrationRequest;

API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos, tvos)
@interface ASAuthorizationSecurityKeyPublicKeyCredentialProvider : NSObject <ASAuthorizationProvider>

- (instancetype)initWithRelyingPartyIdentifier:(NSString *)relyingPartyIdentifier NS_DESIGNATED_INITIALIZER;

/*! @abstract Create a request to register a new security key credential.
    @param challenge The challenge to sign.
    @param displayName The display name for the new credential.
    @param name The name for the new credential.
    @param userID An identifier to be stored alongside the credential, which will be returned with the credential when it is used to authenticate.
 */
- (ASAuthorizationSecurityKeyPublicKeyCredentialRegistrationRequest *)createCredentialRegistrationRequestWithChallenge:(NSData *)challenge displayName:(NSString *)displayName name:(NSString *)name userID:(NSData *)userID NS_SWIFT_NAME(createCredentialRegistrationRequest(challenge:displayName:name:userID:));

/*! @abstract Create a request to authenticate using an existing credential.
    @param challenge The challenge to sign.
 */
- (ASAuthorizationSecurityKeyPublicKeyCredentialAssertionRequest *)createCredentialAssertionRequestWithChallenge:(NSData *)challenge NS_SWIFT_NAME(createCredentialAssertionRequest(challenge:));

/*! @abstract The Relying Party identifier used for all requests created by this object.
 */
@property (nonatomic, readonly, copy) NSString *relyingPartyIdentifier;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
API_AVAILABLE(macos(14.4), ios(17.4)) API_UNAVAILABLE(tvos, watchos, visionos)
#else
API_AVAILABLE(macos(14.4), ios(17.4)) API_UNAVAILABLE(tvos, watchos)
#endif
@interface ASAuthorizationSecurityKeyPublicKeyCredentialProvider () <ASAuthorizationWebBrowserSecurityKeyPublicKeyCredentialProvider>
@end

NS_HEADER_AUDIT_END(nullability, sendability)
