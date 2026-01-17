// Copyright © 2020 Apple Inc. All rights reserved.

#import <AuthenticationServices/ASAuthorizationPublicKeyCredentialParameters.h>
#import <AuthenticationServices/ASAuthorizationPublicKeyCredentialRegistrationRequest.h>
#import <AuthenticationServices/ASAuthorizationRequest.h>
#import <AuthenticationServices/ASAuthorizationSecurityKeyPublicKeyCredentialDescriptor.h>
#import <AuthenticationServices/ASAuthorizationWebBrowserSecurityKeyPublicKeyCredentialRegistrationRequest.h>
#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos, tvos)
@interface ASAuthorizationSecurityKeyPublicKeyCredentialRegistrationRequest : ASAuthorizationRequest <ASAuthorizationPublicKeyCredentialRegistrationRequest>

/*! @abstract A list of parameters for the new credential which are supported by the Relying Party. The authenticator should choose from these parameters when creating the credential.
 */
@property (nonatomic, copy) NSArray<ASAuthorizationPublicKeyCredentialParameters *> *credentialParameters;

/*! @abstract A list of descriptors indicating credentials which must not already exist on the authenticator. If a credential already exists on the authenticator which matches one or more of these descriptors, a new credential will not be created and authentication will fail.
 */
@property (nonatomic, copy) NSArray<ASAuthorizationSecurityKeyPublicKeyCredentialDescriptor *> *excludedCredentials;

/*! @abstract A preference whether the authenticator should store the private key of the newly created credential.
 */
@property (nonatomic) ASAuthorizationPublicKeyCredentialResidentKeyPreference residentKeyPreference;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
API_AVAILABLE(macos(14.4), ios(17.4)) API_UNAVAILABLE(tvos, watchos, visionos)
#else
API_AVAILABLE(macos(14.4), ios(17.4)) API_UNAVAILABLE(tvos, watchos)
#endif
@interface ASAuthorizationSecurityKeyPublicKeyCredentialRegistrationRequest () <ASAuthorizationWebBrowserSecurityKeyPublicKeyCredentialRegistrationRequest>
@end

NS_HEADER_AUDIT_END(nullability, sendability)
