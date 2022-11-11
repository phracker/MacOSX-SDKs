//
//  LAError.h
//  LocalAuthentication
//
//  Copyright (c) 2013 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <LocalAuthentication/LAPublicDefines.h>

/// LocalAuthentication error domain.
extern NSString *const __nonnull LAErrorDomain
API_AVAILABLE(macos(10.11), ios(8.3), watchos(3.0), tvos(10.0));

typedef NS_ENUM(NSInteger, LAError)
{
    /// Authentication was not successful because user failed to provide valid credentials.
    LAErrorAuthenticationFailed = kLAErrorAuthenticationFailed,
    
    /// Authentication was canceled by user (e.g. tapped Cancel button).
    LAErrorUserCancel = kLAErrorUserCancel,
    
    /// Authentication was canceled because the user tapped the fallback button (Enter Password).
    LAErrorUserFallback = kLAErrorUserFallback,
    
    /// Authentication was canceled by system (e.g. another application went to foreground).
    LAErrorSystemCancel = kLAErrorSystemCancel,
    
    /// Authentication could not start because passcode is not set on the device.
    LAErrorPasscodeNotSet = kLAErrorPasscodeNotSet,

    /// Authentication could not start because Touch ID is not available on the device.
    LAErrorTouchIDNotAvailable NS_ENUM_DEPRECATED(10_10, 10_13, 8_0, 11_0, "use LAErrorBiometryNotAvailable") = kLAErrorTouchIDNotAvailable,

    /// Authentication could not start because Touch ID has no enrolled fingers.
    LAErrorTouchIDNotEnrolled NS_ENUM_DEPRECATED(10_10, 10_13, 8_0, 11_0, "use LAErrorBiometryNotEnrolled") = kLAErrorTouchIDNotEnrolled,

    /// Authentication was not successful because there were too many failed Touch ID attempts and
    /// Touch ID is now locked. Passcode is required to unlock Touch ID, e.g. evaluating
    /// LAPolicyDeviceOwnerAuthenticationWithBiometrics will ask for passcode as a prerequisite.
    LAErrorTouchIDLockout NS_ENUM_DEPRECATED(10_11, 10_13, 9_0, 11_0, "use LAErrorBiometryLockout")
        __WATCHOS_DEPRECATED(3.0, 4.0, "use LAErrorBiometryLockout") __TVOS_DEPRECATED(10.0, 11.0, "use LAErrorBiometryLockout") = kLAErrorTouchIDLockout,

    /// Authentication was canceled by application (e.g. invalidate was called while
    /// authentication was in progress).
    LAErrorAppCancel API_AVAILABLE(macos(10.11), ios(9.0)) = kLAErrorAppCancel,

    /// LAContext passed to this call has been previously invalidated.
    LAErrorInvalidContext API_AVAILABLE(macos(10.11), ios(9.0)) = kLAErrorInvalidContext,

    /// Authentication could not start because biometry is not available on the device.
    LAErrorBiometryNotAvailable API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0)) = kLAErrorBiometryNotAvailable,

    /// Authentication could not start because biometry has no enrolled identities.
    LAErrorBiometryNotEnrolled API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0)) = kLAErrorBiometryNotEnrolled,
    
    /// Authentication was not successful because there were too many failed biometry attempts and
    /// biometry is now locked. Passcode is required to unlock biometry, e.g. evaluating
    /// LAPolicyDeviceOwnerAuthenticationWithBiometrics will ask for passcode as a prerequisite.
    LAErrorBiometryLockout API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0)) = kLAErrorBiometryLockout,
    
    /// Authentication failed because it would require showing UI which has been forbidden
    /// by using interactionNotAllowed property.
    LAErrorNotInteractive API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0), tvos(10.0)) = kLAErrorNotInteractive,
    
    /// Authentication could not start because there was no paired watch device nearby.
    LAErrorWatchNotAvailable API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos) = kLAErrorWatchNotAvailable,
    
    /// Authentication could not start because this device supports biometry only via removable accessories and no accessory has been paired.
    LAErrorBiometryNotPaired API_AVAILABLE(macos(11.2)) API_UNAVAILABLE(ios, watchos, tvos) = kLAErrorBiometryNotPaired,

    /// Authentication could not start because this device supports biometry only via removable accessories and the paired accessory is not connected.
    LAErrorBiometryDisconnected API_AVAILABLE(macos(11.2)) API_UNAVAILABLE(ios, watchos, tvos) = kLAErrorBiometryDisconnected,

    /// Authentication could not start because dimensions of embedded UI are invalid.
    LAErrorInvalidDimensions
    API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, tvos) = kLAErrorInvalidDimensions,

} API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0), tvos(10.0));

