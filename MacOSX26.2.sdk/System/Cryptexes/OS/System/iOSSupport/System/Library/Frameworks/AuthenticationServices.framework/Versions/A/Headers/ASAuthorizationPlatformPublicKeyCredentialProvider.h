// Copyright © 2020 Apple Inc. All rights reserved.

#import <AuthenticationServices/ASAuthorizationPlatformPublicKeyCredentialRegistrationRequest.h>
#import <AuthenticationServices/ASAuthorizationProvider.h>
#import <AuthenticationServices/ASAuthorizationWebBrowserPlatformPublicKeyCredentialProvider.h>
#import <AuthenticationServices/ASFoundation.h>

@class ASAuthorizationPlatformPublicKeyCredentialAssertionRequest;
@class ASAuthorizationPlatformPublicKeyCredentialRegistrationRequest;

AS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_AVAILABLE(macos(12.0), ios(15.0), tvos(16.0)) API_UNAVAILABLE(watchos)
@interface ASAuthorizationPlatformPublicKeyCredentialProvider : NSObject <ASAuthorizationProvider>

- (instancetype)initWithRelyingPartyIdentifier:(NSString *)relyingPartyIdentifier NS_DESIGNATED_INITIALIZER;

/*! @abstract Create a request to register a new platform credential.
    @param challenge The challenge to sign.
    @param name The user name for the new credential.
    @param userID An identifier to be stored alongside the credential, which will be returned with the credential when it is used to authenticate.
 */
- (ASAuthorizationPlatformPublicKeyCredentialRegistrationRequest *)createCredentialRegistrationRequestWithChallenge:(NSData *)challenge name:(NSString *)name userID:(NSData *)userID NS_SWIFT_NAME(createCredentialRegistrationRequest(challenge:name:userID:));

/*! @abstract Create a request to register a new platform credential.
    @param challenge The challenge to sign.
    @param name The user name for the new credential.
    @param userID An identifier to be stored alongside the credential, which will be returned with the credential when it is used to authenticate.
    @param requestStyle The style for this request.
 */
- (ASAuthorizationPlatformPublicKeyCredentialRegistrationRequest *)createCredentialRegistrationRequestWithChallenge:(NSData *)challenge name:(NSString *)name userID:(NSData *)userID requestStyle:(ASAuthorizationPlatformPublicKeyCredentialRegistrationRequestStyle)requestStyle NS_SWIFT_NAME(createCredentialRegistrationRequest(challenge:name:userID:requestStyle:)) API_AVAILABLE(macos(15.0), ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos, watchos);

/*! @abstract Create a request to authenticate using an existing credential.
    @param challenge The challenge to sign.
 */
- (ASAuthorizationPlatformPublicKeyCredentialAssertionRequest *)createCredentialAssertionRequestWithChallenge:(NSData *)challenge NS_SWIFT_NAME(createCredentialAssertionRequest(challenge:));

/*! @abstract The Relying Party identifier used for all requests created by this object.
 */
@property (nonatomic, readonly, copy) NSString *relyingPartyIdentifier;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
API_AVAILABLE(macos(13.5), macCatalyst(16.6), ios(17.4)) API_UNAVAILABLE(tvos, watchos, visionos)
#else
API_AVAILABLE(macos(13.5), macCatalyst(16.6), ios(17.4)) API_UNAVAILABLE(tvos, watchos)
#endif
@interface ASAuthorizationPlatformPublicKeyCredentialProvider () <ASAuthorizationWebBrowserPlatformPublicKeyCredentialProvider>
@end

AS_HEADER_AUDIT_END(nullability, sendability)
