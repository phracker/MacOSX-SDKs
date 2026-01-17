//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// @brief Generic secret
API_AVAILABLE(macos(13.0), ios(16.0)) API_UNAVAILABLE(watchos, tvos)
@interface LASecret: NSObject

/// @brief Fetch stored data if any
/// @param handler Completion handler invoked with a generic secret stored along with the right or an error if no secret is found or the fetch operation fails.
- (void)loadDataWithCompletion:(void (NS_SWIFT_SENDABLE ^)(NSData *_Nullable, NSError *_Nullable))handler NS_SWIFT_ASYNC_NAME(getter:rawData());

/// @brief Clients cannot create @c LASecret instances directly. They typically obtain them from a @c LAPersistedRight instance.
+ (instancetype)new NS_UNAVAILABLE;

/// @brief Clients cannot create @c LASecret instances directly. They typically obtain them from a @c LAPersistedRight instance.
- (instancetype)init NS_UNAVAILABLE;
@end

NS_ASSUME_NONNULL_END
