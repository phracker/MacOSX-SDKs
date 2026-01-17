//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <LocalAuthentication/LAPublicDefines.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, LABiometryType)
{
    /// The device does not support biometry.
    LABiometryTypeNone API_AVAILABLE(macos(10.13.2), ios(11.2)) = kLABiometryTypeNone,
    LABiometryNone API_DEPRECATED_WITH_REPLACEMENT("LABiometryTypeNone", macos(10.13, 10.13.2), ios(11.0, 11.2)) = LABiometryTypeNone,
    
    /// The device supports Touch ID.
    LABiometryTypeTouchID = kLABiometryTypeTouchID,

    /// The device supports Face ID.
    LABiometryTypeFaceID API_AVAILABLE(macos(10.15)) = kLABiometryTypeFaceID,

    /// The device supports Optic ID
    LABiometryTypeOpticID API_AVAILABLE(visionos(1.0), ios(17.0), macos(14.0)) = kLABiometryTypeOpticID,
} API_AVAILABLE(macos(10.13.2), ios(11.0), watchos(11.0), tvos(18.0), visionos(1.0));

NS_ASSUME_NONNULL_END
