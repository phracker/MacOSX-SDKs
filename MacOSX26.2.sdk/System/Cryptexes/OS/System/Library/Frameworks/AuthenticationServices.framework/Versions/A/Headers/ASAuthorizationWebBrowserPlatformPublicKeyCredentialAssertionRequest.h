// Copyright © 2023 Apple Inc. All rights reserved.

#import <AuthenticationServices/ASFoundation.h>

@class ASPublicKeyCredentialClientData;

AS_HEADER_AUDIT_BEGIN(nullability, sendability)

#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
API_AVAILABLE(macos(13.5), macCatalyst(16.6), ios(17.4)) API_UNAVAILABLE(tvos, watchos, visionos)
#else
API_AVAILABLE(macos(13.5), macCatalyst(16.6), ios(17.4)) API_UNAVAILABLE(tvos, watchos)
#endif
@protocol ASAuthorizationWebBrowserPlatformPublicKeyCredentialAssertionRequest

@property (nonatomic, readonly, nullable) ASPublicKeyCredentialClientData *clientData NS_REFINED_FOR_SWIFT;

@property (nonatomic) BOOL shouldShowHybridTransport;

@end

AS_HEADER_AUDIT_END(nullability, sendability)
