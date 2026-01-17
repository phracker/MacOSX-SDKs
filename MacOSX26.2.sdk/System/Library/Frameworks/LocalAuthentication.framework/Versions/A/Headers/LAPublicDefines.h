//
//  LAPublicDefines.h
//  LocalAuthentication
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#ifndef LocalAuthentication_LAPublicDefines_h
#define LocalAuthentication_LAPublicDefines_h

// Policies
#define kLAPolicyDeviceOwnerAuthenticationWithBiometrics        1
#define kLAPolicyDeviceOwnerAuthentication                      2
#define kLAPolicyDeviceOwnerAuthenticationWithWatch             3
#define kLAPolicyDeviceOwnerAuthenticationWithBiometricsOrWatch 4
#define kLAPolicyDeviceOwnerAuthenticationWithWristDetection    5
#define kLAPolicyDeviceOwnerAuthenticationWithCompanion         kLAPolicyDeviceOwnerAuthenticationWithWatch
#define kLAPolicyDeviceOwnerAuthenticationWithBiometricsOrCompanion kLAPolicyDeviceOwnerAuthenticationWithBiometricsOrWatch

// ACL operations
#define kLAAccessControlOperationCreateItem         0
#define kLAAccessControlOperationUseItem            1
#define kLAAccessControlOperationCreateKey          2
#define kLAAccessControlOperationUseKeySign         3
#define kLAAccessControlOperationUseKeyDecrypt      4
#define kLAAccessControlOperationUseKeyKeyExchange  5

// Biometry types
#define kLABiometryTypeNone           0
#define kLABiometryTypeTouchID        1 << 0
#define kLABiometryTypeFaceID         1 << 1
#define kLABiometryTypeOpticID        1 << 2

// Credential types
#define kLACredentialTypeApplicationPassword                0
#define kLACredentialSmartCardPIN                          -3

// Error codes
#define kLAErrorAuthenticationFailed                       -1
#define kLAErrorUserCancel                                 -2
#define kLAErrorUserFallback                               -3
#define kLAErrorSystemCancel                               -4
#define kLAErrorPasscodeNotSet                             -5
#define kLAErrorTouchIDNotAvailable                        -6
#define kLAErrorTouchIDNotEnrolled                         -7
#define kLAErrorTouchIDLockout                             -8
#define kLAErrorAppCancel                                  -9
#define kLAErrorInvalidContext                            -10
#define kLAErrorWatchNotAvailable                         -11
#define kLAErrorNotInteractive                          -1004
#define kLAErrorBiometryNotAvailable                        kLAErrorTouchIDNotAvailable
#define kLAErrorBiometryNotEnrolled                         kLAErrorTouchIDNotEnrolled
#define kLAErrorBiometryLockout                             kLAErrorTouchIDLockout
#define kLAErrorBiometryNotPaired                         -12
#define kLAErrorBiometryDisconnected                      -13
#define kLAErrorInvalidDimensions                         -14
#define kLAErrorCompanionNotAvailable                       kLAErrorWatchNotAvailable

// Error domain
#define kLAErrorDomain        "com.apple.LocalAuthentication"

// Companion types
#define kLACompanionTypeNone            0
#define kLACompanionTypeWatch           1 << 0
#define kLACompanionTypeMac             1 << 1
#define kLACompanionTypeVision          1 << 2

#endif
