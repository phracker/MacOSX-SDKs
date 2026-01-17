// Copyright © 2024 Apple Inc. All rights reserved.

@class ASAuthorizationPublicKeyCredentialLargeBlobAssertionOutput;

NS_ASSUME_NONNULL_BEGIN

/// This class encapsulates output for various WebAuthn extensions used during passkey assertion.
NS_REFINED_FOR_SWIFT
API_AVAILABLE(ios(18.0), macos(15.0), visionos(2.0)) API_UNAVAILABLE(watchos, tvos)
@interface ASPasskeyAssertionCredentialExtensionOutput : NSObject <NSCopying, NSSecureCoding>

- (instancetype)initWithLargeBlobOutput:(nullable ASAuthorizationPublicKeyCredentialLargeBlobAssertionOutput *)largeBlob;

/// Output for `largeBlob` operation during passkey assertion.
@property (nonatomic, readonly, nullable, copy) ASAuthorizationPublicKeyCredentialLargeBlobAssertionOutput *largeBlobAssertionOutput;

@end

NS_ASSUME_NONNULL_END
