//
//  GKLeaderboard.h
//  Game Center
//
//  Copyright 2010-2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <os/lock.h>

typedef NS_ENUM(NSInteger, GKLeaderboardTimeScope) {
    GKLeaderboardTimeScopeToday = 0,
    GKLeaderboardTimeScopeWeek,
    GKLeaderboardTimeScopeAllTime
};

typedef NS_ENUM(NSInteger, GKLeaderboardPlayerScope) {
    GKLeaderboardPlayerScopeGlobal = 0,
    GKLeaderboardPlayerScopeFriendsOnly
};

@class GKPlayer;
@class GKScore;

NS_ASSUME_NONNULL_BEGIN

// GKLeaderboard represents the set of high scores for the current game, always including the local player's best score.
NS_CLASS_AVAILABLE(10_8, 4_1) __WATCHOS_AVAILABLE(3_0)
@interface GKLeaderboard : NSObject

@property(assign, NS_NONATOMIC_IOSONLY)            GKLeaderboardTimeScope      timeScope;
@property(assign, NS_NONATOMIC_IOSONLY)            GKLeaderboardPlayerScope    playerScope;        // Filter on friends. Does not apply to leaderboard initialized with players.

@property(copy, nullable, NS_NONATOMIC_IOSONLY)              NSString          *identifier NS_AVAILABLE(10_10, 7_0);         // leaderboardID. If nil, fetch the aggregate leaderboard.
 
@property(readonly, copy, nullable, NS_NONATOMIC_IOSONLY)    NSString          *title;             // Localized category title. Defaults to nil until loaded.
@property(assign, NS_NONATOMIC_IOSONLY)            NSRange                     range;              // Leaderboards start at index 1 and the length should be less than 100. Does not apply to leaderboards initialized with players.  Exception will be thrown if developer tries to set an invalid range

@property(readonly, retain, nullable, NS_NONATOMIC_IOSONLY)  NSArray<GKScore *> *scores;            // Scores are not valid until loadScores: has completed.
@property(readonly, assign, NS_NONATOMIC_IOSONLY)  NSUInteger                  maxRange;           // The maxRange which represents the size of the leaderboard is not valid until loadScores: has completed.
@property(readonly, retain, nullable, NS_NONATOMIC_IOSONLY)  GKScore           *localPlayerScore;  // The local player's score
@property(readonly, getter=isLoading)              BOOL                        loading;            // true if the leaderboard is currently loading

@property(nonatomic, readonly, nullable, retain)   NSString                    *groupIdentifier    NS_AVAILABLE(10_9, 6_0);       // set when leaderboards have been designated a game group; set when loadLeaderboardsWithCompletionHandler has been called for leaderboards that support game groups

// Default is the range 1-10 with Global/AllTime scopes
// if you want to change the scopes or range, set the properites before loading the scores.
- (instancetype)init;

// Specify an array of GKPlayers. For example, the players who are in a match together
// Defaults to AllTime score, if you want to change the timeScope, set the property before loading the scores. Range and playerScope are not applicable. players may not be nil.
- (instancetype)initWithPlayers:(NSArray<GKPlayer *> *)players NS_AVAILABLE(10_10, 8_0);

// Load the scores for this leader board asynchronously.  Error will be nil on success.
// Possible reasons for error:
// 1. Communications problem
// 2. Unauthenticated player
- (void)loadScoresWithCompletionHandler:(void(^__nullable)(NSArray<GKScore *> * __nullable scores, NSError * __nullable error))completionHandler;

// Loads the array of GKLeaderboard for your app
// Possible reasons for error:
// 1. Communications problem
// 2. Unauthenticated player
// 3. Leaderboard not present
+ (void)loadLeaderboardsWithCompletionHandler:(void(^__nullable)(NSArray<GKLeaderboard *> * __nullable leaderboards, NSError * __nullable error))completionHandler NS_AVAILABLE(10_8, 6_0);

@end

@interface GKLeaderboard (Deprecated)

@property(copy, nullable, NS_NONATOMIC_IOSONLY)              NSString                    *category NS_DEPRECATED(10_8, 10_10, 4_1, 7_0, "Use identifier instead") ;         // Deprecated. Use identifier instead.

- (nullable instancetype)initWithPlayerIDs:(nullable NSArray<NSString *> *)playerIDs NS_DEPRECATED(10_8, 10_10, 4_1, 8_0, "Use initWithPlayers: instead") ;

+ (void)loadCategoriesWithCompletionHandler:(void(^__nullable)(NSArray<NSString *> * __nullable categories, NSArray<NSString *> * __nullable titles, NSError * __nullable error))completionHandler NS_DEPRECATED(10_8, 10_9, 4_1, 6_0, "Use loadLeaderboardsWithCompletionHandler: instead") ;

+ (void)setDefaultLeaderboard:(nullable NSString *)leaderboardIdentifier withCompletionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler NS_DEPRECATED(10_8, 10_10, 5_0, 7_0,"Use setDefaultLeaderboardIdentifier:completionHandler: on GKLocalPlayer instead") ;

@end
NS_ASSUME_NONNULL_END


@interface GKLeaderboard (UI)
 
 // Asynchronously load the image. Error will be nil on success.
#if TARGET_OS_IPHONE
- (void)loadImageWithCompletionHandler:(void(^__nullable)(UIImage * __nullable image, NSError * __nullable error))completionHandler NS_AVAILABLE(10_8, 7_0) __TVOS_UNAVAILABLE;
#else
- (void)loadImageWithCompletionHandler:(void(^__nullable)(NSImage * __nullable image, NSError * __nullable error))completionHandler NS_AVAILABLE(10_8, 7_0);
#endif

@end
 

