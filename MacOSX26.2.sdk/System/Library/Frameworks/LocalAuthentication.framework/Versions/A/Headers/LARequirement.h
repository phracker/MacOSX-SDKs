//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class LABiometryFallbackRequirement, LAExtendedRequirement;

#pragma mark -

API_AVAILABLE(macos(13.0), ios(16.0)) API_UNAVAILABLE(watchos, tvos)
/// @brief Builds requirements that can be used for protecting a @c LARight
@interface LAAuthenticationRequirement: NSObject

/// @brief Requires user authentication
/// @return @c LAAuthenticationRequirement instance
@property (class, readonly) LAAuthenticationRequirement *defaultRequirement;

/// @brief Requires biometric authentication
/// @discussion The authorization will fail if:
/// @li • Biometry is not available in the current device
/// @li • There are no biometric enrollments
/// @return @c LAAuthenticationRequirement instance
@property (class, readonly) LAAuthenticationRequirement *biometryRequirement;

/// @brief Requires user authentication with the current biometric set
/// @discussion The authorization will fail if:
/// @li • Biometry is not available in the current device
/// @li • There are no biometric enrollments
/// @li • There is a change in the enrollment database -e.g a new TouchID finger is enrolled.
/// @return @c LAAuthenticationRequirement instance
@property (class, readonly) LAAuthenticationRequirement *biometryCurrentSetRequirement;

/// @brief Requires biometric authentication or the given fallback method.
/// @param fallback Fallback used in case biometry authentication fails, is not available or
/// not preferred by the user.
/// @return @c LAAuthenticationRequirement instance
+ (instancetype)biometryRequirementWithFallback:(LABiometryFallbackRequirement *)fallback NS_SWIFT_NAME(biometry(fallback:));
@end

#pragma mark -

API_AVAILABLE(macos(13.0), ios(16.0)) API_UNAVAILABLE(watchos, tvos)
/// @brief Builds authentication requirements that can be used as fallbacks for  biometric authentication
@interface LABiometryFallbackRequirement: NSObject

/// @brief Use default biometric fallback
/// @return @c LABiometryFallbackRequirement instance
@property (class, readonly) LABiometryFallbackRequirement *defaultRequirement;

/// @brief Requires authorization using the device passcode
/// @return @c LABiometryFallbackRequirement instance
@property (class, readonly) LABiometryFallbackRequirement *devicePasscodeRequirement;
@end

NS_ASSUME_NONNULL_END
