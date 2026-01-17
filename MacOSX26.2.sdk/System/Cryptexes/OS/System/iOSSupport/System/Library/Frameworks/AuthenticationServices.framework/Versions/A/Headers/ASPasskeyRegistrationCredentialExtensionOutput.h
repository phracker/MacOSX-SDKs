// Copyright © 2024 Apple Inc. All rights reserved.

NS_ASSUME_NONNULL_BEGIN

@class ASAuthorizationPublicKeyCredentialLargeBlobRegistrationOutput;

/// This class encapsulates output for various WebAuthn extensions used during passkey registration.
NS_REFINED_FOR_SWIFT
API_AVAILABLE(ios(18.0), macos(15.0), visionos(2.0)) API_UNAVAILABLE(tvos, watchos)
@interface ASPasskeyRegistrationCredentialExtensionOutput : NSObject <NSCopying, NSSecureCoding>

- (instancetype)initWithLargeBlobOutput:(nullable ASAuthorizationPublicKeyCredentialLargeBlobRegistrationOutput *)largeBlob;

/// Output for `largeBlob` operation during passkey registration.
@property (nonatomic, readonly, nullable, copy) ASAuthorizationPublicKeyCredentialLargeBlobRegistrationOutput *largeBlobRegistrationOutput;

@end

NS_ASSUME_NONNULL_END
