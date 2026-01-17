// Copyright © 2020 Apple Inc. All rights reserved.

#import <AuthenticationServices/ASAuthorizationPublicKeyCredentialAssertionRequest.h>
#import <AuthenticationServices/ASAuthorizationRequest.h>
#import <AuthenticationServices/ASAuthorizationSecurityKeyPublicKeyCredentialDescriptor.h>
#import <AuthenticationServices/ASAuthorizationWebBrowserSecurityKeyPublicKeyCredentialAssertionRequest.h>
#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos, tvos)
@interface ASAuthorizationSecurityKeyPublicKeyCredentialAssertionRequest : ASAuthorizationRequest <ASAuthorizationPublicKeyCredentialAssertionRequest>

/*! A list of descriptors indicating credentials that may be used to sign in. If this is non-empty, only credentials matching the provided descriptors can be used when authenticating.
 */
@property (nonatomic, copy) NSArray<ASAuthorizationSecurityKeyPublicKeyCredentialDescriptor *> *allowedCredentials;

/// Use this value to request the appid WebAuthn extension. This can only be requested by web browsers.
@property (nonatomic, nullable, copy) NSString *appID AS_API_AVAILABLE(macos(14.5), ios(17.5));

@end

#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
API_AVAILABLE(macos(14.4), ios(17.4)) API_UNAVAILABLE(tvos, watchos, visionos)
#else
API_AVAILABLE(macos(14.4), ios(17.4)) API_UNAVAILABLE(tvos, watchos)
#endif // defined(TARGET_OS_XR) && TARGET_OS_XR
@interface ASAuthorizationSecurityKeyPublicKeyCredentialAssertionRequest () <ASAuthorizationWebBrowserSecurityKeyPublicKeyCredentialAssertionRequest>
@end

NS_HEADER_AUDIT_END(nullability, sendability)
