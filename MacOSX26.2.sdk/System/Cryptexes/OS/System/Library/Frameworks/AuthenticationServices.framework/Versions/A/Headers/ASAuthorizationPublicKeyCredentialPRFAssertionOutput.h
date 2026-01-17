// Copyright © 2024 Apple Inc. All rights reserved.

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(15.0), ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos, watchos)
NS_REFINED_FOR_SWIFT
@interface ASAuthorizationPublicKeyCredentialPRFAssertionOutput: NSObject

@property (nonatomic, readonly) NSData *first;
@property (nonatomic, nullable, readonly) NSData *second;

@end
NS_ASSUME_NONNULL_END
