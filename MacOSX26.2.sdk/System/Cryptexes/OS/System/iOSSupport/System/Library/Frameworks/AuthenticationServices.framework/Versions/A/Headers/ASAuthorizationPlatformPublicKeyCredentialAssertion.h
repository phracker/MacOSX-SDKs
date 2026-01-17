// Copyright © 2020 Apple Inc. All rights reserved.

#import <AuthenticationServices/ASAuthorizationPublicKeyCredentialAssertion.h>
#import <AuthenticationServices/ASAuthorizationPublicKeyCredentialConstants.h>
#import <AuthenticationServices/ASAuthorizationPublicKeyCredentialLargeBlobAssertionOutput.h>
#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class ASAuthorizationPublicKeyCredentialPRFAssertionOutput;

API_AVAILABLE(macos(12.0), ios(15.0), tvos(16.0)) API_UNAVAILABLE(watchos)
@interface ASAuthorizationPlatformPublicKeyCredentialAssertion : NSObject<ASAuthorizationPublicKeyCredentialAssertion>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@property (nonatomic, readonly) ASAuthorizationPublicKeyCredentialAttachment attachment API_AVAILABLE(macos(13.5), ios(16.6)) API_UNAVAILABLE(tvos, watchos);

@property (nonatomic, readonly, nullable) ASAuthorizationPublicKeyCredentialLargeBlobAssertionOutput *largeBlob NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0)) API_UNAVAILABLE(tvos, watchos);

@property (nonatomic, readonly, nullable) ASAuthorizationPublicKeyCredentialPRFAssertionOutput *prf NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0), ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos, watchos);

@end

NS_HEADER_AUDIT_END(nullability, sendability)
