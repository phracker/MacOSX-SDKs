// Copyright © 2020 Apple Inc. All rights reserved.

#import <AuthenticationServices/ASAuthorizationPublicKeyCredentialAssertionRequest.h>
#import <AuthenticationServices/ASAuthorizationRequest.h>
#import <AuthenticationServices/ASAuthorizationSecurityKeyPublicKeyCredentialDescriptor.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos)
@interface ASAuthorizationSecurityKeyPublicKeyCredentialAssertionRequest : ASAuthorizationRequest <ASAuthorizationPublicKeyCredentialAssertionRequest>

/*! A list of descriptors indicating credentials that may be used to sign in. If this is non-empty, only credentials matching the provided descriptors can be used when authenticating.
 */
@property (nonatomic, copy) NSArray<ASAuthorizationSecurityKeyPublicKeyCredentialDescriptor *> *allowedCredentials;

@end

NS_ASSUME_NONNULL_END
