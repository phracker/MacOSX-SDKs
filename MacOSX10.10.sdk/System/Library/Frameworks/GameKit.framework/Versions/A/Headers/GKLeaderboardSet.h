//
//  GKLeaderboardSet.h
//  Game Center
//
//  Copyright 2012-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameKit/GKDefines.h>


// GKLeaderboardSet represents the sets that leaderboards can be broken out into. 
NS_CLASS_AVAILABLE(10_10, 7_0)
@interface GKLeaderboardSet : NSObject <NSCoding, NSSecureCoding>

@property(readonly, copy, NS_NONATOMIC_IOSONLY)    NSString                    *title;               // Localized set title.

@property(nonatomic, readonly, retain)             NSString                    *groupIdentifier;       // set when leaderboardSets have been designated a game group; set when loadLeaderboardSetsWithCompletionHandler has been called for leaderboards that support game groups
@property(copy, NS_NONATOMIC_IOSONLY)              NSString                    *identifier;          // leaderboard set.

// Loads array with all sets for game
// Possible reasons for error:
// 1. Communications problem
// 2. Unauthenticated player
// 3. Set not present
+ (void)loadLeaderboardSetsWithCompletionHandler:(void(^)(NSArray *leaderboardSets, NSError *error))completionHandler NS_AVAILABLE(10_10, 7_0);

// Loads array with all leaderboards for the leaderboardSet
// Possible reasons for error:
// 1. Communications problem
// 2. Unauthenticated player
- (void)loadLeaderboardsWithCompletionHandler:(void(^)(NSArray *leaderboards, NSError *error))completionHandler NS_AVAILABLE(10_10, 7_0);

@end


@interface GKLeaderboardSet (UI)

// Asynchronously load the image. Error will be nil on success.
#if TARGET_OS_IPHONE
- (void)loadImageWithCompletionHandler:(void(^)(UIImage *image, NSError *error))completionHandler;
#else
- (void)loadImageWithCompletionHandler:(void(^)(NSImage *image, NSError *error))completionHandler;
#endif

@end



