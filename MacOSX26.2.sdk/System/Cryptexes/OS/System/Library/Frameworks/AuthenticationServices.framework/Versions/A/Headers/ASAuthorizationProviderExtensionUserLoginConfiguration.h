//
//  ASAuthorizationProviderExtensionUserLoginConfiguration.h
//  AuthenticationServices Framework
//
//  Copyright © 2023 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

@class ASAuthorizationProviderExtensionLoginManager;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, watchos, tvos)
@interface ASAuthorizationProviderExtensionUserLoginConfiguration : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// @abstract The user name to use when authenticating with the identity provider.
@property (nonatomic, copy) NSString *loginUserName;

/// @abstract Creates an instance with the required values.
/// @param loginUserName The login user name to use.

- (instancetype)initWithLoginUserName:(NSString *)loginUserName;

#pragma mark - Embedded Assertions

/*!
 @abstract Sets custom claims to be added to the embedded assertion request header.
 @param claims The claims to be added. It must serialize as valid JSON to be accepted.
 @param error Nil or an NSError indicating why the claims were rejected.
 @returns YES when successful and NO when claims are rejected.
 */
- (BOOL)setCustomAssertionRequestHeaderClaims:(NSDictionary<NSString *, id> *)claims returningError:(NSError * _Nullable * _Nullable) error;

/*!
 @abstract Sets custom claims to be added to the embedded assertion request body.
 @param claims The claims to be added. It must serialize as valid JSON to be accepted.
 @param error Nil or an NSError indicating why the claims were rejected.
 @returns YES when successful and NO when claims are rejected.
 */
- (BOOL)setCustomAssertionRequestBodyClaims:(NSDictionary<NSString *, id> *)claims returningError:(NSError * _Nullable * _Nullable) error;

#pragma mark - Login Request

/*!
 @abstract Sets custom claims to be added to the login request header.
 @param claims The claims to be added. It must serialize as valid JSON to be accepted.
 @param error Nil or an NSError indicating why the claims were rejected.
 @returns YES when successful and NO when claims are rejected.
 */
- (BOOL)setCustomLoginRequestHeaderClaims:(NSDictionary<NSString *, id> *)claims returningError:(NSError * _Nullable * _Nullable) error;

/*!
 @abstract Sets custom claims to be added to the login request body.
 @param claims The claims to be added. It must serialize as valid JSON to be accepted.
 @param error Nil or an NSError indicating why the claims were rejected.
 @returns YES when successful and NO when claims are rejected.
 */
- (BOOL)setCustomLoginRequestBodyClaims:(NSDictionary<NSString *, id> *)claims returningError:(NSError * _Nullable * _Nullable) error;

@end

NS_ASSUME_NONNULL_END
