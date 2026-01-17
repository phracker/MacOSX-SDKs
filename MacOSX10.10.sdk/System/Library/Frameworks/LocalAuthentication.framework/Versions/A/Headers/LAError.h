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
} NS_ENUM_AVAILABLE(10_10, 8_0);

/// LocalAuthentication error domain.
extern NSString *const LAErrorDomain NS_AVAILABLE(10_10, 8_0);
