// Copyright © 2023 Apple Inc. All rights reserved.

#import <AuthenticationServices/ASFoundation.h>

@class ASAuthorizationPlatformPublicKeyCredentialDescriptor;
@class ASPublicKeyCredentialClientData;

AS_HEADER_AUDIT_BEGIN(nullability, sendability)

#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
API_AVAILABLE(macos(13.5), macCatalyst(16.6), ios(17.4)) API_UNAVAILABLE(tvos, watchos, visionos)
#else
API_AVAILABLE(macos(13.5), macCatalyst(16.6), ios(17.4)) API_UNAVAILABLE(tvos, watchos)
#endif
@protocol ASAuthorizationWebBrowserPlatformPublicKeyCredentialRegistrationRequest

@property (nonatomic, readonly, nullable) ASPublicKeyCredentialClientData *clientData NS_REFINED_FOR_SWIFT;

@property (nonatomic, nullable, copy) NSArray<ASAuthorizationPlatformPublicKeyCredentialDescriptor *> *excludedCredentials;

@property (nonatomic) BOOL shouldShowHybridTransport API_AVAILABLE(macos(13.5), macCatalyst(16.6)) API_UNAVAILABLE(ios, tvos, watchos);

@end

AS_HEADER_AUDIT_END(nullability, sendability)
