// Copyright © 2020 Apple Inc. All rights reserved.

#import <AuthenticationServices/ASAuthorizationPlatformPublicKeyCredentialDescriptor.h>
#import <AuthenticationServices/ASAuthorizationPublicKeyCredentialAssertionRequest.h>
#import <AuthenticationServices/ASAuthorizationPublicKeyCredentialLargeBlobAssertionInput.h>
#import <AuthenticationServices/ASAuthorizationRequest.h>
#import <AuthenticationServices/ASAuthorizationWebBrowserExternallyAuthenticatableRequest.h>
#import <AuthenticationServices/ASAuthorizationWebBrowserPlatformPublicKeyCredentialAssertionRequest.h>
#import <Foundation/Foundation.h>

@class ASAuthorizationPublicKeyCredentialPRFAssertionInput;

AS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_AVAILABLE(macos(12.0), ios(15.0), tvos(16.0)) API_UNAVAILABLE(watchos)
@interface ASAuthorizationPlatformPublicKeyCredentialAssertionRequest : ASAuthorizationRequest<ASAuthorizationPublicKeyCredentialAssertionRequest>

/*! @abstract A list of credentials to allow for this request. If this ilist is nonempty, only credentials matching the provided descriptors can be used to sign in.
 */
@property (nonatomic, copy) NSArray<ASAuthorizationPlatformPublicKeyCredentialDescriptor *> *allowedCredentials;

@property (nonatomic, nullable) ASAuthorizationPublicKeyCredentialLargeBlobAssertionInput *largeBlob NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0)) API_UNAVAILABLE(tvos, watchos);

@property (nonatomic, nullable) ASAuthorizationPublicKeyCredentialPRFAssertionInput *prf API_AVAILABLE(macos(15.0), ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos, watchos);

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

API_AVAILABLE(macos(13.3)) API_UNAVAILABLE(ios, watchos, tvos)
@interface ASAuthorizationPlatformPublicKeyCredentialAssertionRequest () <ASAuthorizationWebBrowserExternallyAuthenticatableRequest>
@end

#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
API_AVAILABLE(macos(13.5), macCatalyst(16.6), ios(17.4)) API_UNAVAILABLE(tvos, watchos, visionos)
#else
API_AVAILABLE(macos(13.5), macCatalyst(16.6), ios(17.4)) API_UNAVAILABLE(tvos, watchos)
#endif
@interface ASAuthorizationPlatformPublicKeyCredentialAssertionRequest () <ASAuthorizationWebBrowserPlatformPublicKeyCredentialAssertionRequest>
@end

AS_HEADER_AUDIT_END(nullability, sendability)
