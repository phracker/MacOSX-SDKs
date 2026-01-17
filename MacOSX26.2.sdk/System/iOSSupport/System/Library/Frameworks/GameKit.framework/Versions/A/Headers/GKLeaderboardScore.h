// Copyright © Apple Inc. All rights reserved.

NS_ASSUME_NONNULL_BEGIN

@class GKPlayer;

/// A `GKLeaderboardScore` object represents a score on a leaderboard for scores you report for challenges or turn-based games.
API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0), watchos(7.0))
@interface GKLeaderboardScore : NSObject

/// The player who earns the score.
@property (strong, nonatomic) GKPlayer *player;

/// The score that the player earns.
@property (assign, nonatomic) NSInteger value;

/// An integer value that your game uses.
@property (assign, nonatomic) NSUInteger context;

/// The ID that Game Center uses for the leaderboard.
@property (strong, nonatomic) NSString *leaderboardID;

@end

NS_ASSUME_NONNULL_END
