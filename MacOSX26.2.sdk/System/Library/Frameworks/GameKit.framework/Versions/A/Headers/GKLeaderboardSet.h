// Copyright © Apple Inc. All rights reserved.

#import <TargetConditionals.h>
#import <GameKit/GKDefines.h>

@class GKLeaderboard;
@class UIImage;

NS_ASSUME_NONNULL_BEGIN
/// GKLeaderboardSet represents the sets that leaderboards can be broken out into.
API_AVAILABLE(ios(7.0), macos(10.10), tvos(9.0), visionos(1.0), watchos(3.0))
@interface GKLeaderboardSet : NSObject <NSCoding, NSSecureCoding>

/// Localized set title.
@property(readonly, copy, NS_NONATOMIC_IOSONLY) NSString *title;

/// set when leaderboardSets have been designated a game group; set when loadLeaderboardSetsWithCompletionHandler has been called for leaderboards that support game groups
@property(nonatomic, readonly, nullable, strong) NSString *groupIdentifier;

/// leaderboard set.
@property(copy, nullable, NS_NONATOMIC_IOSONLY) NSString *identifier;


/// Loads array with all sets for game
/// Possible reasons for error:
/// 1. Communications problem
/// 2. Unauthenticated player
/// 3. Set not present
+ (void)loadLeaderboardSetsWithCompletionHandler:(void(^__nullable)(NSArray<GKLeaderboardSet *> * __nullable leaderboardSets, NSError * __nullable error))completionHandler;

/// Loads array with all classic leaderboards and current instances of recurring leaderboards for this leaderboardSet
/// Possible reasons for error:
/// 1. Communications problem
/// 2. Unauthenticated player
- (void)loadLeaderboardsWithHandler:(void(^)(NSArray<GKLeaderboard *> * __nullable leaderboards, NSError * __nullable error))handler API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0), watchos(7.0));

@end

@interface GKLeaderboardSet (Deprecated)

/// Loads array with all leaderboards for the leaderboardSet
/// Possible reasons for error:
/// 1. Communications problem
/// 2. Unauthenticated player
- (void)loadLeaderboardsWithCompletionHandler:(void(^__nullable)(NSArray<GKLeaderboard *> * __nullable leaderboards, NSError * __nullable error))completionHandler API_DEPRECATED_WITH_REPLACEMENT("Use the ``GKLeaderboardSet/loadLeaderboards(handler:)`` method instead.", ios(7.0, 14.0), tvos(9.0, 14.0), macos(10.10, 11.0), watchos(3.0, 7.0));

@end
NS_ASSUME_NONNULL_END

#if !TARGET_OS_WATCH

@interface GKLeaderboardSet (UI)

#if TARGET_OS_IPHONE
/// Asynchronously load the image. Error will be nil on success.
- (void)loadImageWithCompletionHandler:(void(^__nullable)(UIImage * __nullable image, NSError * __nullable error))completionHandler API_AVAILABLE(ios(7.0), macos(10.10), visionos(1.0)) API_UNAVAILABLE(tvos, watchos);
#else
/// Asynchronously load the image. Error will be nil on success.
- (void)loadImageWithCompletionHandler:(void(^__nullable)(NSImage * __nullable image, NSError * __nullable error))completionHandler API_AVAILABLE(ios(7.0), macos(10.10), visionos(1.0)) API_UNAVAILABLE(tvos, watchos);
#endif

@end

#endif
