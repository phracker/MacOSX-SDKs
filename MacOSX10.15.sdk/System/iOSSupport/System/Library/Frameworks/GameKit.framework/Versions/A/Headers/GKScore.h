//
//  GKScore.h
//  Game Center
//
//  Copyright 2010-2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <GameKit/GKLeaderboard.h>


@class GKPlayer;

NS_ASSUME_NONNULL_BEGIN

// GKScore represents a score in the leaderboards.
NS_CLASS_AVAILABLE(10_8, 4_1) __WATCHOS_AVAILABLE(3_0)
@interface GKScore : NSObject <NSCoding, NSSecureCoding>

// Initialize the score with the local player and current date.
- (instancetype)initWithLeaderboardIdentifier:(NSString *)identifier;

// Initialize the achievement for a specific player. Use to submit participant scores when ending a turn-based match.
- (instancetype)initWithLeaderboardIdentifier:(NSString *)identifier player:(GKPlayer *)player NS_AVAILABLE(10_10, 8_0) __WATCHOS_AVAILABLE(3_0);

@property(assign, NS_NONATOMIC_IOSONLY)                     int64_t     value;              // The score value as a 64bit integer.
@property(readonly, copy, nullable, NS_NONATOMIC_IOSONLY)   NSString    *formattedValue;    // The score formatted as a string, localized with a label

// leaderboard identifier (required)
@property(copy, NS_NONATOMIC_IOSONLY)               NSString    *leaderboardIdentifier NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);

// optional additional context that allows a game to store and retrieve additional data associated with the store.  Default value of zero is returned if no value is set.
@property(assign, NS_NONATOMIC_IOSONLY)                        uint64_t    context NS_AVAILABLE(10_8, 5_0) __WATCHOS_AVAILABLE(3_0);

@property(readonly, retain, NS_NONATOMIC_IOSONLY)   NSDate      *date;              // The date this score was recorded. A newly initialized, unsubmitted GKScore records the current date at init time.
@property(readonly, retain, nullable, NS_NONATOMIC_IOSONLY)   GKPlayer    *player NS_AVAILABLE(10_10, 8_0) __WATCHOS_AVAILABLE(3_0);          // The player that recorded the score.
@property(readonly, assign, NS_NONATOMIC_IOSONLY)   NSInteger   rank;               // The rank of the player within the leaderboard, only valid when returned from GKLeaderboard

// Convenience property to make the leaderboard associated with this GKScore, the default leaderboard for this player. Default value is false.
// If true, reporting that score will make the category this score belongs to, the default leaderboard for this user
@property(nonatomic, assign)                        BOOL        shouldSetDefaultLeaderboard     NS_AVAILABLE(10_8, 5_0) __WATCHOS_AVAILABLE(3_0);

// Report scores to the server. The value must be set, and date may be changed.
// Possible reasons for error:
// 1. Value not set
// 2. Local player not authenticated
// 3. Communications problem
+ (void)reportScores:(NSArray<GKScore *> *)scores withCompletionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_8, 6_0) __WATCHOS_AVAILABLE(3_0);

@end

@interface GKScore (Deprecated)

- (instancetype)initWithLeaderboardIdentifier:(NSString *)identifier forPlayer:(NSString *)playerID NS_DEPRECATED_IOS(7_0, 8_0, "use initWithLeaderboardIdentifier:player:") ;
- (void)reportScoreWithCompletionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler NS_DEPRECATED(10_8, 10_10, 4_1, 7_0, "Use +reportScores:withCompletionhandler: instead") ;
- (instancetype)initWithCategory:(nullable NSString *)category NS_DEPRECATED(10_8, 10_10, 4_1, 7_0, "Use initWithLeaderboardIdentifier: instead") ;

@property(readonly, retain, NS_NONATOMIC_IOSONLY)   NSString    *playerID NS_DEPRECATED(10_8, 10_10, 4_1, 8_0, "use player") ;          // The identifier of the player that recorded the score.
@property(copy, nullable, NS_NONATOMIC_IOSONLY) NSString *category NS_DEPRECATED(10_8, 10_10, 4_1, 7_0, "Use leaderboardIdentifier instead") ;

@end

NS_ASSUME_NONNULL_END
