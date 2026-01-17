// Copyright © 2023 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>

AS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NS_ENUM(NSInteger, ASAuthorizationPublicKeyCredentialLargeBlobSupportRequirement) {
    ASAuthorizationPublicKeyCredentialLargeBlobSupportRequirementRequired,
    ASAuthorizationPublicKeyCredentialLargeBlobSupportRequirementPreferred,
} API_AVAILABLE(macos(14.0), ios(17.0)) API_UNAVAILABLE(tvos, watchos) NS_REFINED_FOR_SWIFT;

NS_REFINED_FOR_SWIFT
API_AVAILABLE(macos(14.0), ios(17.0)) API_UNAVAILABLE(tvos, watchos)
@interface ASAuthorizationPublicKeyCredentialLargeBlobRegistrationInput : NSObject

- (instancetype)initWithSupportRequirement:(ASAuthorizationPublicKeyCredentialLargeBlobSupportRequirement)requirement;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@property (nonatomic) ASAuthorizationPublicKeyCredentialLargeBlobSupportRequirement supportRequirement;

@end

AS_HEADER_AUDIT_END(nullability, sendability)
