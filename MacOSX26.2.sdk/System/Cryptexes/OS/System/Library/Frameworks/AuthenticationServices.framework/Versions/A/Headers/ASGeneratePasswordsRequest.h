//
//  ASGeneratePasswordsRequest
//  AuthenticationServices Framework
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//


#import <AuthenticationServices/ASFoundation.h>
#import <AuthenticationServices/ASCredentialServiceIdentifier.h>

AS_HEADER_AUDIT_BEGIN(nullability, sendability)

AS_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(26.2), visionos(26.2))
API_UNAVAILABLE(macos, tvos, watchos)
@interface ASGeneratePasswordsRequest : NSObject <NSCopying, NSSecureCoding>

/// The identifier of the service for which the the credential would be associated.
@property (nonatomic, readonly) ASCredentialServiceIdentifier *serviceIdentifier;

/// Developer provided password rules.
@property (nonatomic, nullable, readonly) NSString *passwordFieldPasswordRules;

/// Developer provided password rules for a "confirm password" field.
///
/// This is only relevant in an HTML context.
@property (nonatomic, nullable, readonly) NSString *confirmPasswordFieldPasswordRules;

/// Password rules from https://github.com/apple/password-manager-resources
@property (nonatomic, nullable, readonly) NSString *passwordRulesFromQuirks;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)initWithServiceIdentifier:(ASCredentialServiceIdentifier *)serviceIdentifier
    passwordFieldPasswordRules:(nullable NSString *)passwordFieldPasswordRules
    confirmPasswordFieldPasswordRules:(nullable NSString *)confirmPasswordFieldPasswordRules
    passwordRulesFromQuirks:(nullable NSString *)passwordRulesFromQuirks;

@end

AS_HEADER_AUDIT_END(nullability, sendability)

