//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <LocalAuthentication/LAEnvironmentMechanism.h>
#import <LocalAuthentication/LAEnvironmentMechanismBiometry.h>
#import <LocalAuthentication/LAEnvironmentMechanismCompanion.h>
#import <LocalAuthentication/LAEnvironmentMechanismUserPassword.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0), visionos(2.0))
NS_SWIFT_NAME(LAEnvironment.State)
NS_SWIFT_SENDABLE
@interface LAEnvironmentState : NSObject<NSCopying>

/// Clients shall not create environment state.
- (instancetype)init NS_UNAVAILABLE;

/// Clients shall not create environment state.
+ (instancetype)new NS_UNAVAILABLE;

/// @brief Information about biometric authentication (Touch ID, Face ID or Optic ID).
/// @discussion @c nil if biometry is not supported by this device.
@property (nonatomic, readonly, nullable) LAEnvironmentMechanismBiometry *biometry;

/// @brief Information about local user password (on macOS) or passcode (on embedded platforms).
/// @discussion @c nil if user password or passcode is not supported by this device.
@property (nonatomic, readonly, nullable) LAEnvironmentMechanismUserPassword *userPassword;

/// @brief Companion authentication mechanisms.
/// @discussion Companion mechanisms such as Apple Watch can appear and disappear as they get in and out of reach, but
///             this property enumerates paired companions, even if they are not reachable at the moment. Check @c isUsable
///             property to determine if a particular companion type is available for use. 
///             Note that items in this array represent paired companion types, not individual devices. Therefore, even if the user
///             has paired multiple Apple Watch devices for companion authentication, the array will contain only one
///             @c LAEnvironmentMechanimsCompanion instance of type @c LACompanionTypeWatch.
@property (nonatomic, readonly) NSArray<LAEnvironmentMechanismCompanion *> *companions
API_AVAILABLE(macos(15.0), ios(18.0)) API_UNAVAILABLE(watchos, tvos, visionos);

/// @brief Information about all authentication mechanisms.
/// @discussion This property aggregates @c biometry, @c userPassword, @c companions and any future
///             authentication mechanisms.
@property (nonatomic, readonly) NSArray<LAEnvironmentMechanism *> *allMechanisms;

@end

NS_ASSUME_NONNULL_END
