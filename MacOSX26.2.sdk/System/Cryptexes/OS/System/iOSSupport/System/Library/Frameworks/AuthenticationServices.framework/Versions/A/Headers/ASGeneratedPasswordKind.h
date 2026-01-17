//
//  ASGeneratedPasswordKind.h
//  AuthenticationServices Framework
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//


#import <Foundation/Foundation.h>

AS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_AVAILABLE(ios(26.2), visionos(26.2))
API_UNAVAILABLE(macos, tvos, watchos)
typedef NSString *ASGeneratedPasswordKind NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(ASGeneratedPassword.Kind);

API_AVAILABLE(ios(26.2), visionos(26.2))
API_UNAVAILABLE(macos, tvos, watchos)
/// A password that contains alphanumeric characters and special characters.
extern ASGeneratedPasswordKind const ASGeneratedPasswordKindStrong;

API_AVAILABLE(ios(26.2), visionos(26.2))
API_UNAVAILABLE(macos, tvos, watchos)
/// A password that only contains alphanumeric characters.
///
/// This may be referred to as a password "without special characters".
extern ASGeneratedPasswordKind const ASGeneratedPasswordKindAlphanumeric;

API_AVAILABLE(ios(26.2), visionos(26.2))
API_UNAVAILABLE(macos, tvos, watchos)
/// A password that contains multiple words or phrases.
extern ASGeneratedPasswordKind const ASGeneratedPasswordKindPassphrase;

AS_HEADER_AUDIT_END(nullability, sendability)

