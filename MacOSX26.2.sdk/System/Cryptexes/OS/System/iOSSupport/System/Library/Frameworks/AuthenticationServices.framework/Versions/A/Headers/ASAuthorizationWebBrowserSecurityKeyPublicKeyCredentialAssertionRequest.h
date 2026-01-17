// Copyright © 2024 Apple Inc. All rights reserved.

#import <AuthenticationServices/ASFoundation.h>

@class ASPublicKeyCredentialClientData;

AS_HEADER_AUDIT_BEGIN(nullability, sendability)

#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
API_AVAILABLE(macos(14.4), ios(17.4)) API_UNAVAILABLE(tvos, watchos, visionos)
#else
API_AVAILABLE(macos(14.4), ios(17.4)) API_UNAVAILABLE(tvos, watchos)
#endif
@protocol ASAuthorizationWebBrowserSecurityKeyPublicKeyCredentialAssertionRequest

@property (nonatomic, readonly, nullable) ASPublicKeyCredentialClientData *clientData NS_REFINED_FOR_SWIFT;

@end

AS_HEADER_AUDIT_END(nullability, sendability)
