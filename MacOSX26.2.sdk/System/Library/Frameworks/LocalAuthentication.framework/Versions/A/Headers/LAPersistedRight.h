//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <LocalAuthentication/LARight.h>

NS_ASSUME_NONNULL_BEGIN

@class LASecret, LAPrivateKey;

/// @brief A type of right that, when authorized, grants access to a key and secret
API_AVAILABLE(macos(13.0), ios(16.0)) API_UNAVAILABLE(watchos, tvos)
@interface LAPersistedRight: LARight

/// @brief Managed private key
@property (nonatomic, readonly) LAPrivateKey *key;

/// @brief Generic secret
/// @discussion This is the generic secret that would have been stored along with the right
@property (nonatomic, readonly) LASecret *secret;

/// @brief Clients cannot create @c LAPersistedRight instances directly. They can only obtain them from the @c LARightStore .
+ (instancetype)new NS_UNAVAILABLE;

/// @brief Clients cannot create @c LAPersistedRight instances directly. They can only obtain them from the @c LARightStore .
- (instancetype)init NS_UNAVAILABLE;
@end

NS_ASSUME_NONNULL_END
