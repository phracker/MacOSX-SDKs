//
//  LAAuthenticationView.h
//  LocalAuthenticationEmbeddedUI
//
//  Copyright © 2021 Apple. All rights reserved.
//

#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>

@class LAContext;

NS_ASSUME_NONNULL_BEGIN

/// @brief Compact authentication view providing authentication similar to @c LAContext
/// evaluatePolicy API.
/// @discussion This view is non-textual, it displays only a compact icon hinting
/// users to use Touch ID or Watch to authenticate. The reason for the
/// authentication must be apparent from the surrounding UI to avoid confusion and
/// security risks.
API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, tvos)
@interface LAAuthenticationView : NSView

- (instancetype)initWithFrame:(NSRect)frameRect NS_UNAVAILABLE;
- (instancetype)initWithCoder:(NSCoder *)coder NS_UNAVAILABLE;

/// @brief Creates a new view and pairs it with the specified authentication context.
/// @discussion The authentication is controlled using the provided authentication
/// context. When `evaluatePolicy` or `evaluateAccessControl` is called on this
/// context, the UI will be presented using this view rather than using the standard
/// authentication alert.
/// Since the view is designed for authentication with Touch ID or Watch
/// the only supported policies for calling `evaluatePolicy` on the context are
/// - `LAPolicyDeviceOwnerAuthenticationWithBiometrics`
/// - `LAPolicyDeviceOwnerAuthenticationWithCompanion`
/// - `LAPolicyDeviceOwnerAuthenticationWitchBiometricsOrCompanion`
/// - `LAPolicyDeviceOwnerAuthentication` (This one is supported just for convenience. If neither biometric nor watch authentication is available, the evaluation of the policy fails)
/// @param context  @c LAContext instance to control the authentication.
- (instancetype)initWithContext:(LAContext *)context
API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, tvos);

/// @brief Creates a new view and pairs it with the specified authentication context.
/// @discussion The authentication is controlled using the provided authentication
/// context. When `evaluatePolicy` or `evaluateAccessControl` is called on this
/// context, the UI will be presented using this view rather than using the standard
/// authentication alert.
/// Since the view is designed for authentication with Touch ID or Watch
/// the only supported policies for calling `evaluatePolicy` on the context are
/// - `LAPolicyDeviceOwnerAuthenticationWithBiometrics`
/// - `LAPolicyDeviceOwnerAuthenticationWithCompanion`
/// - `LAPolicyDeviceOwnerAuthenticationWitchBiometricsOrCompanion`
/// - `LAPolicyDeviceOwnerAuthentication` (This one is supported just for convenience. If neither biometric nor watch authentication is available, the evaluation of the policy fails)
/// @param context  @c LAContext instance to control the authentication.
/// @param controlSize Preferred size of @c LAAuthenticationView provided using @c NSControlSize
- (instancetype)initWithContext:(LAContext *)context controlSize:(NSControlSize)controlSize
API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, tvos);

/// @brief @c LAContext instance passed to the initializer.
@property (nonatomic, readonly) LAContext *context
API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, tvos);

/// @brief @c NSControlSize instance passed to the initializer.
@property (nonatomic, readonly) NSControlSize controlSize
API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, tvos);

@end
NS_ASSUME_NONNULL_END
