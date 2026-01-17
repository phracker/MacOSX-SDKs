// Copyright © 2023 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>

AS_HEADER_AUDIT_BEGIN(nullability, sendability)

NS_REFINED_FOR_SWIFT
API_AVAILABLE(macos(14.0), ios(17.0)) API_UNAVAILABLE(tvos, watchos)
@interface ASAuthorizationPublicKeyCredentialLargeBlobRegistrationOutput : NSObject <NSCopying, NSSecureCoding>

@property (nonatomic, readonly) BOOL isSupported;

@end

AS_HEADER_AUDIT_END(nullability, sendability)
