// Copyright © 2020 Apple Inc. All rights reserved.

#import <AuthenticationServices/ASAuthorizationPublicKeyCredentialRegistration.h>
#import <AuthenticationServices/ASAuthorizationSecurityKeyPublicKeyCredentialDescriptor.h>
#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos, tvos)
@interface ASAuthorizationSecurityKeyPublicKeyCredentialRegistration : NSObject <ASAuthorizationPublicKeyCredentialRegistration>

/*! @abstract A list of transports that the authenticator is believed to support, if this could be determined.
 */
@property (nonatomic, readonly) NSArray<ASAuthorizationSecurityKeyPublicKeyCredentialDescriptorTransport> *transports API_AVAILABLE(macos(14.5), ios(17.5));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
