// Copyright © 2024 Apple Inc. All rights reserved.

@class ASAuthorizationPublicKeyCredentialPRFAssertionInputValues;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(15.0), ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos, watchos)
NS_REFINED_FOR_SWIFT
@interface ASAuthorizationPublicKeyCredentialPRFRegistrationInput: NSObject

+ (instancetype)checkForSupport;

- (instancetype)initWithInputValues:(nullable ASAuthorizationPublicKeyCredentialPRFAssertionInputValues *)inputValues;

@property (nonatomic, readonly) BOOL shouldCheckForSupport;

@property (nonatomic, nullable, readonly) ASAuthorizationPublicKeyCredentialPRFAssertionInputValues *inputValues;

@end

NS_ASSUME_NONNULL_END
