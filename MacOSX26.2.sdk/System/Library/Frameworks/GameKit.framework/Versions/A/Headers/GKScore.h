// Copyright © Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>

#import <GameKit/GKLeaderboard.h>

@class GKPlayer;

NS_ASSUME_NONNULL_BEGIN

/// GKScore represents a score in the leaderboards.
API_DEPRECATED_WITH_REPLACEMENT("Use the ``GKLeaderboard/Entry`` class instead.", ios(4.1, 14.0), tvos(9.0, 14.0), macos(10.8, 11.0), visionos(1.0,1.0), watchos(3.0, 7.0))
@interface GKScore : NSObject <NSCoding, NSSecureCoding>

/// Initialize the score with the local player and current date.
- (instancetype)initWithLeaderboardIdentifier:(NSString *)identifier;

/// Initialize the achievement for a specific player. Use to submit participant scores when ending a turn-based match.
- (instancetype)initWithLeaderboardIdentifier:(NSString *)identifier player:(GKPlayer *)player API_DEPRECATED_WITH_REPLACEMENT("Use ``GKLeaderboardScore`` instead.", ios(8.0,14.0), macos(10.10,11.0), tvos(9.0,14.0), visionos(1.0,1.0), watchos(3.0,7.0));

/// The score value as a 64bit integer.
@property(assign, NS_NONATOMIC_IOSONLY)                     int64_t     value;

/// The score formatted as a string, localized with a label
@property(readonly, copy, nullable, NS_NONATOMIC_IOSONLY)   NSString    *formattedValue;

/// leaderboard identifier (required)
@property(copy, NS_NONATOMIC_IOSONLY)               NSString    *leaderboardIdentifier API_DEPRECATED_WITH_REPLACEMENT("Use ``GKLeaderboardScore`` instead.", ios(7.0,14.0), macos(10.10,11.0), tvos(9.0,14.0), visionos(1.0,1.0), watchos(3.0,7.0));

/// optional additional context that allows a game to store and retrieve additional data associated with the store.  Default value of zero is returned if no value is set.
@property(assign, NS_NONATOMIC_IOSONLY)                        uint64_t    context API_DEPRECATED_WITH_REPLACEMENT("Use ``GKLeaderboardScore`` instead.", ios(5.0,14.0), macos(10.8,11.0), tvos(9.0,14.0), visionos(1.0,1.0), watchos(3.0,7.0));

/// The date this score was recorded. A newly initialized, unsubmitted GKScore records the current date at init time.
@property(readonly, retain, NS_NONATOMIC_IOSONLY)   NSDate      *date;

/// The player that recorded the score.
@property(readonly, retain, nullable, NS_NONATOMIC_IOSONLY)   GKPlayer    *player API_DEPRECATED_WITH_REPLACEMENT("Use ``GKLeaderboardScore`` instead.", ios(8.0,14.0), macos(10.10,11.0), tvos(9.0,14.0), visionos(1.0,1.0), watchos(3.0,7.0));


/// The rank of the player within the leaderboard, only valid when returned from GKLeaderboard
@property(readonly, assign, NS_NONATOMIC_IOSONLY)   NSInteger   rank;

/// Convenience property to make the leaderboard associated with this GKScore, the default leaderboard for this player. Default value is false.
/// If true, reporting that score will make the category this score belongs to, the default leaderboard for this user
@property(nonatomic, assign)                        BOOL        shouldSetDefaultLeaderboard     API_DEPRECATED_WITH_REPLACEMENT("Use ``GKLeaderboardScore`` instead.", ios(5.0,14.0), macos(10.8,11.0), tvos(9.0,14.0), visionos(1.0,1.0), watchos(3.0,7.0));

/// Report scores to the server. The value must be set, and date may be changed.
/// Possible reasons for error:
/// 1. Value not set
/// 2. Local player not authenticated
/// 3. Communications problem
+ (void)reportScores:(NSArray<GKScore *> *)scores withCompletionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler API_DEPRECATED_WITH_REPLACEMENT("Use ``GKLeaderboardScore`` instead.", ios(6.0,14.0), macos(10.8,11.0), tvos(9.0,14.0), visionos(1.0,1.0), watchos(3.0,7.0));

@end

@interface GKScore (Deprecated)

- (void)reportScoreWithCompletionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler API_DEPRECATED_WITH_REPLACEMENT("Use ``GKLeaderboardScore`` instead.", ios(4.1,7.0), macos(10.8,10.10), visionos(1.0,1.0), watchos(3.0,3.0)) API_UNAVAILABLE(tvos);
- (instancetype)initWithCategory:(nullable NSString *)category API_DEPRECATED_WITH_REPLACEMENT("Use ``GKLeaderboardScore`` instead.", ios(4.1,7.0), macos(10.8,10.10), visionos(1.0,1.0), watchos(3.0,3.0)) API_UNAVAILABLE(tvos);

@property(copy, nullable, NS_NONATOMIC_IOSONLY) NSString *category API_DEPRECATED_WITH_REPLACEMENT("Use ``GKLeaderboardScore`` instead.", ios(4.1,7.0), macos(10.8,10.10), visionos(1.0,1.0), watchos(3.0,3.0)) API_UNAVAILABLE(tvos);
@end

API_UNAVAILABLE(tvos)
@interface GKScore (Obsoleted)
/*** This method is obsolete. Calling this initialiser does nothing and will return nil ***/
- (nullable instancetype)initWithLeaderboardIdentifier:(NSString *)identifier forPlayer:(NSString *)playerID API_DEPRECATED_WITH_REPLACEMENT("Use ``GKLeaderboardScore`` instead.", ios(7.0,8.0), macos(10.9,10.10), visionos(1.0,1.0), watchos(3.0,3.0)) API_UNAVAILABLE(tvos);

/*** This property is obsolete. ***/
@property(readonly, nullable, retain, NS_NONATOMIC_IOSONLY)   NSString    *playerID API_DEPRECATED_WITH_REPLACEMENT("Use ``GKLeaderboardScore`` instead.", ios(4.1,8.0), macos(10.8,10.10), visionos(1.0,1.0), watchos(3.0,3.0)) API_UNAVAILABLE(tvos);          // The identifier of the player that recorded the score.
@end

NS_ASSUME_NONNULL_END
