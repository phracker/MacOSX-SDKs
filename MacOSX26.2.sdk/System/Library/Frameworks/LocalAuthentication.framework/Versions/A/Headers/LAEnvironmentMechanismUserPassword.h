//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <LocalAuthentication/LAEnvironmentMechanism.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0), visionos(2.0)) 
NS_SWIFT_NAME(LAEnvironment.MechanismUserPassword)
NS_SWIFT_SENDABLE
@interface LAEnvironmentMechanismUserPassword : LAEnvironmentMechanism

/// @brief Whether the local user password or passcode is set on this device.
@property (nonatomic, readonly) BOOL isSet;

@end

NS_ASSUME_NONNULL_END
