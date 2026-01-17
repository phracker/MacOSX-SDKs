//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <LocalAuthentication/LAContext.h>
#import <LocalAuthentication/LAEnvironmentMechanism.h>

NS_ASSUME_NONNULL_BEGIN


API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0), visionos(2.0))
NS_SWIFT_NAME(LAEnvironment.MechanismBiometry)
NS_SWIFT_SENDABLE
@interface LAEnvironmentMechanismBiometry : LAEnvironmentMechanism

/// @brief Type of biometry supported by the device.
/// @discussion This property does not indicate whether biometry is available or not. It always reads the type of biometry
///             supported by device hardware. You should check @c isUsable property to see if it is available for use.
@property (nonatomic, readonly) LABiometryType biometryType;

/// @brief Whether the user has enrolled this biometry.
/// @discussion Even if biometry is enrolled, it does not necessarily mean that it can be used. You should check @c isUsable
///             property to see if it is available for use.
@property (nonatomic, readonly) BOOL isEnrolled;

/// @brief Whether biometry is locked out.
/// @discussion The system might lock the user out of biometry for various reasons. For example, with Face ID, the user is
///             locked out after 5 failed match attempts in row. To recover from bio lockout, users need to enter their passcode
///             (e.g. during device ulock).
@property (nonatomic, readonly) BOOL isLockedOut;

/// @brief The application specific state of the biometric enrollment as returned by @c LAContext.domainState.biometry.stateHash
/// @discussion This value represents the state of the enrollment and changes whenever the biometric enrollment is changed.
///             It does not directly map to the enrolled templates, e.g. if a finger is added to Touch ID enrollement and then
///             removed, the final state would be different.
///             It also returns different values to different apps to prevent tracking of user identity.
@property (nonatomic, readonly) NSData *stateHash;

/// @brief Whether the built in biometric sensor is inaccessible in the current configuration, preventing the use of biometry.
/// @discussion Currently, the only example of this is a Clamshell Mode on macOS. The user will be not able to use Touch ID
///             if the MacBook lid is closed while connected to external monitor and keyboard, unless the external keyboard
///             has Touch ID.
@property (nonatomic, readonly) BOOL builtInSensorInaccessible;

@end

NS_ASSUME_NONNULL_END
