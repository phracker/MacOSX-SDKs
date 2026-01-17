//
//  GKLeaderboardSet.h
//  Game Center
//
//  Copyright 2012-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameKit/GKDefines.h>


@class GKLeaderboard;

NS_ASSUME_NONNULL_BEGIN
// GKLeaderboardSet represents the sets that leaderboards can be broken out into. 
NS_CLASS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0)
@interface GKLeaderboardSet : NSObject <NSCoding, NSSecureCoding>

@property(readonly, copy, NS_NONATOMIC_IOSONLY)    NSString                    *title;               // Localized set title.

@property(nonatomic, readonly, nullable, retain)            NSString                    *groupIdentifier;       // set when leaderboardSets have been designated a game group; set when loadLeaderboardSetsWithCompletionHandler has been called for leaderboards that support game groups
@property(copy, nullable, NS_NONATOMIC_IOSONLY)             NSString                    *identifier;          // leaderboard set.

// Loads array with all sets for game
// Possible reasons for error:
// 1. Communications problem
// 2. Unauthenticated player
// 3. Set not present
+ (void)loadLeaderboardSetsWithCompletionHandler:(void(^__nullable)(NSArray<GKLeaderboardSet *> * __nullable leaderboardSets, NSError * __nullable error))completionHandler NS_AVAILABLE(10_10, 7_0);

// Loads array with all leaderboards for the leaderboardSet
// Possible reasons for error:
// 1. Communications problem
// 2. Unauthenticated player
- (void)loadLeaderboardsWithCompletionHandler:(void(^__nullable)(NSArray<GKLeaderboard *> * __nullable leaderboards, NSError * __nullable error))completionHandler NS_AVAILABLE(10_10, 7_0);

@end
NS_ASSUME_NONNULL_END


@interface GKLeaderboardSet (UI)

// Asynchronously load the image. Error will be nil on success.
#if TARGET_OS_IPHONE
- (void)loadImageWithCompletionHandler:(void(^__nullable)(UIImage * __nullable image, NSError * __nullable error))completionHandler __TVOS_UNAVAILABLE;
#else
- (void)loadImageWithCompletionHandler:(void(^__nullable)(NSImage * __nullable image, NSError * __nullable error))completionHandler;
#endif

@end



