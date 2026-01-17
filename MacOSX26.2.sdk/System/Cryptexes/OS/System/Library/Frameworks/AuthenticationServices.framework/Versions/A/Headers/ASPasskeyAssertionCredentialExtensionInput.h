// Copyright © 2024 Apple Inc. All rights reserved.

NS_ASSUME_NONNULL_BEGIN

@class ASAuthorizationPublicKeyCredentialLargeBlobAssertionInput;

/// This class encapsulates input for various WebAuthn extensions during passkey assertion.
NS_REFINED_FOR_SWIFT
API_AVAILABLE(ios(18.0), macos(15.0), visionos(2.0)) API_UNAVAILABLE(watchos, tvos)
@interface ASPasskeyAssertionCredentialExtensionInput : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Input for the `largeBlob` extension in passkey assertion requests.
@property (nonatomic, readonly, nullable) ASAuthorizationPublicKeyCredentialLargeBlobAssertionInput *largeBlob;

@end

NS_ASSUME_NONNULL_END
