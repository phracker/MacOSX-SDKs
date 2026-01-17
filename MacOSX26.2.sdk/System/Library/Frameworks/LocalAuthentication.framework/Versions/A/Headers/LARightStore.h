//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class LAPersistedRight, LARight, LASecret;

/// @brief Persistent storage for @c LARight instances.
API_AVAILABLE(macos(13.0), ios(16.0)) API_UNAVAILABLE(watchos, tvos)
@interface LARightStore: NSObject

/// @brief Shared instance of @c LARightStore.
@property (class, readonly) LARightStore *sharedStore;

/// @brief Fetches a right stored under the given identifier.
/// @param identifier Identifier associated with a previously stored right.
/// @param handler Completion handler with the fetched right or an error on failure.
- (void)rightForIdentifier:(NSString *)identifier completion:(void (NS_SWIFT_SENDABLE ^)(LAPersistedRight *_Nullable, NSError *_Nullable))handler;

/// @brief Persists a right for later usage.
/// @param right @c LARight instance to store.
/// @param identifier Identifier to be associated with the right. Useful for later retrieval.
/// @param handler Completion handler with the persisted right or an error on failure.
- (void)saveRight:(LARight *)right identifier:(NSString *)identifier completion:(void (NS_SWIFT_SENDABLE ^)(LAPersistedRight *_Nullable, NSError *_Nullable))handler NS_SWIFT_NAME(saveRight(_:identifier:completion:));

/// @brief Persists a right for later usage.
/// @param right @c LARight instance to store.
/// @param identifier Identifier to be associated with the right. Useful for later retrieval.
/// @param secret Secret data to be associated with the provided right.
/// @param handler Completion handler with the persisted right or an error on failure.
- (void)saveRight:(LARight *)right identifier:(NSString *)identifier secret:(NSData *)secret completion:(void (NS_SWIFT_SENDABLE ^)(LAPersistedRight *_Nullable, NSError *_Nullable))handler NS_SWIFT_NAME(saveRight(_:identifier:secret:completion:));

/// @brief Removes a right from the persistent storage along with its associated resources.
/// @param right @c LAPersistedRight instance to remove.
/// @param handler Completion handler with an error on failure.
- (void)removeRight:(LAPersistedRight *)right completion:(void (NS_SWIFT_SENDABLE ^)(NSError *_Nullable error))handler NS_SWIFT_NAME(removeRight(_:completion:));

/// @brief Removes right with provided identifier from persistant storage.
/// @param identifier Identifier of @c LAPersistedRight instance to remove.
/// @param handler Completion handler with an error on failure.
- (void)removeRightForIdentifier:(NSString *)identifier completion:(void (NS_SWIFT_SENDABLE ^)(NSError *_Nullable error))handler NS_SWIFT_NAME(removeRight(forIdentifier:completion:));

/// @brief Removes all rights stored by the client
/// @param handler Completion handler with an error on failure.
- (void)removeAllRightsWithCompletion:(void (NS_SWIFT_SENDABLE ^)(NSError *_Nullable error))handler;

/// @brief Clients should rely on the @c shared instance instead
+ (instancetype)new NS_UNAVAILABLE;

/// @brief Clients should rely on the @c shared instance instead
- (instancetype)init NS_UNAVAILABLE;
@end

NS_ASSUME_NONNULL_END
