//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0), visionos(2.0))
NS_SWIFT_NAME(LAEnvironment.Mechanism)
NS_SWIFT_SENDABLE
@interface LAEnvironmentMechanism : NSObject

/// Clients should only consume environment mechanisms..
+ (instancetype)new NS_UNAVAILABLE;

/// The Clients should only consume environment mechanisms..
- (instancetype)init NS_UNAVAILABLE;

/// @brief Whether the mechanism is available for use, i.e. whether the relevant preflight call of @c canEvaluatePolicy would succeed.
/// @warning If @c isUsable reads @c NO, do not assume that it's because of some particular reason. You should check
/// properties of the subclass to determine why mechanism can't be used.
@property (nonatomic, readonly) BOOL isUsable;

/// The localized name of the authentication mechanism, e.g. "Touch ID", "Face ID" etc.
@property (nonatomic, readonly) NSString *localizedName;

/// Name of the SF Symbol representing this authentication mechanism.
@property (nonatomic, readonly) NSString *iconSystemName;

@end

NS_ASSUME_NONNULL_END
