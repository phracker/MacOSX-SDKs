//
//  LAError.h
//  LocalAuthentication
//
//  Copyright (c) 2013 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <LocalAuthentication/LAPublicDefines.h>

typedef NS_ENUM(NSInteger, LAError)
{
    /// Authentication was not successful, because user failed to provide valid credentials.
    LAErrorAuthenticationFailed = kLAErrorAuthenticationFailed,
    
    /// Authentication was canceled by user (e.g. tapped Cancel button).
    LAErrorUserCancel           = kLAErrorUserCancel,
    
    /// Authentication was canceled, because the user tapped the fallback button (Enter Password).
    LAErrorUserFallback         = kLAErrorUserFallback,
    
    /// Authentication was canceled by system (e.g. another application went to foreground).
    LAErrorSystemCancel         = kLAErrorSystemCancel,
    
    /// Authentication could not start, because passcode is not set on the device.
    LAErrorPasscodeNotSet       = kLAErrorPasscodeNotSet,

    /// Authentication could not start, because Touch ID is not available on the device.
    LAErrorTouchIDNotAvailable  = kLAErrorTouchIDNotAvailable,
    
    /// Authentication could not start, because Touch ID has no enrolled fingers.
    LAErrorTouchIDNotEnrolled   = kLAErrorTouchIDNotEnrolled,

    /// Authentication was not successful, because there were too many failed Touch ID attempts and
    /// Touch ID is now locked. Passcode is required to unlock Touch ID, e.g. evaluating
    /// LAPolicyDeviceOwnerAuthenticationWithBiometrics will ask for passcode as a prerequisite.
    LAErrorTouchIDLockout   NS_ENUM_AVAILABLE(10_11, 9_0) = kLAErrorTouchIDLockout,

    /// Authentication was canceled by application (e.g. invalidate was called while
    /// authentication was in progress).
    LAErrorAppCancel        NS_ENUM_AVAILABLE(10_11, 9_0) = kLAErrorAppCancel,

    /// LAContext passed to this call has been previously invalidated.
    LAErrorInvalidContext   NS_ENUM_AVAILABLE(10_11, 9_0) = kLAErrorInvalidContext
} NS_ENUM_AVAILABLE(10_10, 8_0);

/// LocalAuthentication error domain.
extern NSString *const __nonnull LAErrorDomain NS_AVAILABLE(10_10, 8_0);
