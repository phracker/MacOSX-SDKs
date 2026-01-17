//
//  GKLeaderboard.h
//  GameKit
//
//  Copyright 2010 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameKit/GKDefines.h>

enum {
    GKLeaderboardTimeScopeToday = 0,
    GKLeaderboardTimeScopeWeek,
    GKLeaderboardTimeScopeAllTime
};
typedef NSInteger GKLeaderboardTimeScope;

enum {
    GKLeaderboardPlayerScopeGlobal = 0,
    GKLeaderboardPlayerScopeFriendsOnly
};
typedef NSInteger GKLeaderboardPlayerScope;

@class GKScore;

// GKLeaderboard represents the set of high scores for the current game, always including the local player's best score.
NS_CLASS_AVAILABLE(10_8, 4_1)
@interface GKLeaderboard : NSObject {
}
@end

@interface GKLeaderboard (GKAdditions)
@property(assign, NS_NONATOMIC_IOSONLY)            GKLeaderboardTimeScope      timeScope;
@property(assign, NS_NONATOMIC_IOSONLY)            GKLeaderboardPlayerScope    playerScope;        // Filter on friends. Does not apply to leaderboard initialized with players.
@property(copy, NS_NONATOMIC_IOSONLY)              NSString                    *category;          // leaderboard category.  If nil, then it will fetch the aggregate leaderboard
@property(readonly, copy, NS_NONATOMIC_IOSONLY)    NSString                    *title;             // Localized category title. Defaults to nil until loaded.
@property(assign, NS_NONATOMIC_IOSONLY)            NSRange                     range;              // Leaderboards start at index 1 and the length should be less than 100. Does not apply to leaderboards initialized with players.  Exception will be thrown if developer tries to set an invalid range

@property(readonly, retain, NS_NONATOMIC_IOSONLY)  NSArray                     *scores;            // Scores are not valid until loadScores: has completed.
@property(readonly, assign, NS_NONATOMIC_IOSONLY)  NSUInteger                  maxRange;           // The maxRange which represents the size of the leaderboard is not valid until loadScores: has completed.
@property(readonly, retain, NS_NONATOMIC_IOSONLY)  GKScore                     *localPlayerScore;  // The local player's score
@property(readonly, getter=isLoading)   BOOL                        loading;            // true if the leaderboard is currently loading

@property(readonly, retain, NS_NONATOMIC_IOSONLY)  NSString                    *groupIdentifier    __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_6_0);       // set when leaderboards have been designated a game group; set when loadLeaderboardsWithCompletionHandler has been called for leaderboards that support game groups

// Designated initializer
// Default is the range 1-10 with Global/AllTime scopes
// if you want to change the scopes or range, set the properites before loading the scores.
- (id)init;

// Specify an array of players ids, for example, the players who are in a match together
// Defaults to AllTime score, if you want to change the timeScope, set the property before loading the scores. Range and playerScope are not applicable. playerIDs may not be nil.
- (id)initWithPlayerIDs:(NSArray *)playerIDs;

// Load the scores for this leader board asynchronously.  Error will be nil on success.
// Possible reasons for error:
// 1. Communications problem
// 2. Unauthenticated player
- (void)loadScoresWithCompletionHandler:(void(^)(NSArray *scores, NSError *error))completionHandler;

// Loads parallel arrays that maps categories to their title strings
// Possible reasons for error:
// 1. Communications problem
// 2. Unauthenticated player
// 3. Leaderboard not present
+ (void)loadCategoriesWithCompletionHandler:(void(^)(NSArray *categories, NSArray *titles, NSError *error))completionHandler __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_8, __MAC_10_9, __IPHONE_4_1, __IPHONE_6_0);

+ (void)loadLeaderboardsWithCompletionHandler:(void(^)(NSArray *leaderboards, NSError *error))completionHandler __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_6_0);

// Set the default leaderboard for the local player per game
// Possible reasons for error:
// 1. Communications problem
// 2. Unauthenticated player
// 3. Leaderboard not present
+ (void)setDefaultLeaderboard:(NSString *)categoryID withCompletionHandler:(void(^)(NSError *error))completionHandler __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_5_0);

#if TARGET_OS_IPHONE
// Asynchronously load the image. Error will be nil on success.
- (void)loadImageWithCompletionHandler:(void(^)(UIImage *image, NSError *error))completionHandler;
#else
// Asynchronously load the image. Error will be nil on success.
- (void)loadImageWithCompletionHandler:(void(^)(NSImage *image, NSError *error))completionHandler;
#endif

@end
