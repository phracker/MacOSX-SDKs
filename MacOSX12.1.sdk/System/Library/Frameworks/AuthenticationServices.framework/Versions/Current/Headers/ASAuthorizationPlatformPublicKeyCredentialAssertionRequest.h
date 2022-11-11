// Copyright © 2020 Apple Inc. All rights reserved.

#import <AuthenticationServices/ASAuthorizationPlatformPublicKeyCredentialDescriptor.h>
#import <AuthenticationServices/ASAuthorizationPublicKeyCredentialAssertionRequest.h>
#import <AuthenticationServices/ASAuthorizationRequest.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos)
@interface ASAuthorizationPlatformPublicKeyCredentialAssertionRequest : ASAuthorizationRequest<ASAuthorizationPublicKeyCredentialAssertionRequest>

/*! @abstract A list of credentials to allow for this request. If this ilist is nonempty, only credentials matching the provided descriptors can be used to sign in.
 */
@property (nonatomic, copy) NSArray<ASAuthorizationPlatformPublicKeyCredentialDescriptor *> *allowedCredentials;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
