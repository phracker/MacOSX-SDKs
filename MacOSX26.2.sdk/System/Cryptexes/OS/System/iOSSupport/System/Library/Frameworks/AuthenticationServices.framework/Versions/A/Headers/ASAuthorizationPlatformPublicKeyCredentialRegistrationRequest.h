// Copyright © 2020 Apple Inc. All rights reserved.

#import <AuthenticationServices/ASAuthorizationPublicKeyCredentialRegistrationRequest.h>
#import <AuthenticationServices/ASAuthorizationPublicKeyCredentialLargeBlobRegistrationInput.h>
#import <AuthenticationServices/ASAuthorizationRequest.h>
#import <AuthenticationServices/ASAuthorizationWebBrowserPlatformPublicKeyCredentialRegistrationRequest.h>
#import <AuthenticationServices/ASFoundation.h>

@class ASAuthorizationPublicKeyCredentialPRFRegistrationInput;

typedef NS_ENUM(NSInteger, ASAuthorizationPlatformPublicKeyCredentialRegistrationRequestStyle) {
    /// Perform a request using the standard presentation style. This is the default style.
    ASAuthorizationPlatformPublicKeyCredentialRegistrationRequestStyleStandard,

    /// Perform a conditional request. This style of request is meant to opportunistically add passkeys to existing
    /// password-based accounts, at the discretion of the user's credential manager. It should be performed
    /// shortly after a user has signed in with a password. If the user is using a password and passkey manager,
    /// and certain internal conditions of that credential manager are met (e.g. the user signed in recently with a
    /// matching password-based account and does not yet have a passkey for this account), then this request
    /// may proceed automatically, without further user interaction. If any of the internal conditions are not met,
    /// this request will return an error without showing any UI to the user, and may be retried the next time they
    /// sign in.
    ASAuthorizationPlatformPublicKeyCredentialRegistrationRequestStyleConditional,
} NS_SWIFT_NAME(ASAuthorizationPlatformPublicKeyCredentialRegistrationRequest.RequestStyle) AS_API_AVAILABLE(macos(15.0), ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

AS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_AVAILABLE(macos(12.0), ios(15.0), tvos(16.0)) API_UNAVAILABLE(watchos)
@interface ASAuthorizationPlatformPublicKeyCredentialRegistrationRequest : ASAuthorizationRequest <ASAuthorizationPublicKeyCredentialRegistrationRequest>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@property (nonatomic, nullable) ASAuthorizationPublicKeyCredentialLargeBlobRegistrationInput *largeBlob NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0)) API_UNAVAILABLE(tvos, watchos);

@property (nonatomic, nullable) ASAuthorizationPublicKeyCredentialPRFRegistrationInput *prf NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0), ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos, watchos);

@property (nonatomic) ASAuthorizationPlatformPublicKeyCredentialRegistrationRequestStyle requestStyle AS_API_AVAILABLE(macos(15.0), ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos, watchos);

@end

#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
API_AVAILABLE(macos(13.5), macCatalyst(16.6), ios(17.4)) API_UNAVAILABLE(tvos, watchos, visionos)
#else
API_AVAILABLE(macos(13.5), macCatalyst(16.6), ios(17.4)) API_UNAVAILABLE(tvos, watchos)
#endif
@interface ASAuthorizationPlatformPublicKeyCredentialRegistrationRequest () <ASAuthorizationWebBrowserPlatformPublicKeyCredentialRegistrationRequest>
@end

AS_HEADER_AUDIT_END(nullability, sendability)
