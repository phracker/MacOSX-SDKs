//
//  ASGeneratedPassword.h
//  AuthenticationServices Framework
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//


#import <AuthenticationServices/ASFoundation.h>
#import <AuthenticationServices/ASGeneratedPasswordKind.h>

AS_HEADER_AUDIT_BEGIN(nullability, sendability)

AS_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(26.2), visionos(26.2))
API_UNAVAILABLE(macos, tvos, watchos)
@interface ASGeneratedPassword : NSObject <NSCopying, NSSecureCoding>

/// The kind of password that this represents.
@property (nonatomic, readonly) ASGeneratedPasswordKind kind;

/// The user-visible description of this password, derived from the kind.
///
/// This may be shown to help with selecting the desired password.
@property (nonatomic, readonly) NSString *localizedName;

/// The value of the password.
@property (nonatomic, readonly) NSString *value;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)initWithKind:(ASGeneratedPasswordKind)kind value:(NSString *)value;

@end

AS_HEADER_AUDIT_END(nullability, sendability)

