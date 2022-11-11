//
//  GKGameCenterViewController.h
//  Game Center
//
//  Copyright 2012-2021 Apple Inc. All rights reserved.
//

#import <GameKit/GKLeaderboard.h>
#import <GameKit/GKAchievement.h>

@protocol GKGameCenterControllerDelegate;

typedef NS_ENUM(NSInteger, GKGameCenterViewControllerState) {
    GKGameCenterViewControllerStateDefault = -1,
    GKGameCenterViewControllerStateLeaderboards,
    GKGameCenterViewControllerStateAchievements,
    GKGameCenterViewControllerStateChallenges,
    GKGameCenterViewControllerStateLocalPlayerProfile,
    GKGameCenterViewControllerStateDashboard,
    GKGameCenterViewControllerStateLocalPlayerFriendsList
};

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <Cocoa/Cocoa.h>
#import <GameKit/GKDialogController.h>
#endif

NS_ASSUME_NONNULL_BEGIN
/// View controller that provides the standard user interface for leaderboards, achievements, and challenges. Present modally from the top view controller.
#if TARGET_OS_IPHONE
NS_CLASS_AVAILABLE(10_9, 6_0)
@interface GKGameCenterViewController : UINavigationController
@end
#else
NS_CLASS_AVAILABLE(10_9, 6_0)
@interface GKGameCenterViewController : NSViewController  <GKViewController>
@end
#endif

@interface GKGameCenterViewController ()

@property (weak, nullable, NS_NONATOMIC_IOSONLY) id<GKGameCenterControllerDelegate> gameCenterDelegate;

/**
 Use this to display content associated with the specified state. For example setting the state to GKGameCenterViewControllerStateLeaderboards will display a list of leaderboard sets or leaderboards (if no sets). Setting state to GKGameCenterViewControllerStateAchievements will display a list of achievements.
 */
- (instancetype)initWithState:(GKGameCenterViewControllerState)state API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0)) API_UNAVAILABLE(watchos);

/**
 Use this to display the scores for the specified leaderboardID, player scope and time scope. The time scope is only applicable to classic leaderboards. Recurring leaderboards will always be displayed initially with the results (scores) associated with the current instance of the leaderboard.
 */
- (instancetype)initWithLeaderboardID:(NSString *)leaderboardID playerScope:(GKLeaderboardPlayerScope)playerScope timeScope:(GKLeaderboardTimeScope)timeScope API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0)) API_UNAVAILABLE(watchos);

/**
 Use this to display the scores for the specified leaderboard and player scope. Both classic and recurring leaderboards can use this method to initialize the view with their scores.
 */
- (instancetype)initWithLeaderboard:(GKLeaderboard *)leaderboard playerScope:(GKLeaderboardPlayerScope)playerScope API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0)) API_UNAVAILABLE(watchos);

/**
 Use this to display the details associated with the specified achievementID
 */
- (instancetype)initWithAchievementID:(NSString *)achievementID API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0)) API_UNAVAILABLE(watchos);

@end

@interface GKGameCenterViewController (Deprecated)

@property (assign, NS_NONATOMIC_IOSONLY) GKGameCenterViewControllerState viewState API_DEPRECATED("Use -initWithState: instead", ios(6.0, 14.0), tvos(9.0, 14.0), macosx(10.9, 11.0)) ;
@property (nonatomic, assign) GKLeaderboardTimeScope leaderboardTimeScope API_DEPRECATED("Use -initWithLeaderboard: instead", ios(4.1, 14.0), macosx(10.8, 11.0))  ;
@property (nonatomic, nullable, strong) NSString *leaderboardIdentifier API_DEPRECATED("Use -initWithLeaderboard: instead", ios(7.0, 14.0), tvos(9.0, 14.0), macosx(10.10, 11.0)) ;
@property (nonatomic, nullable, strong) NSString *leaderboardCategory    NS_DEPRECATED(10_8, 10_10, 4_1, 7_0, "GKGameCenterViewController's leaderboardCategory property is deprecated. Use -initWithLeaderboard: instead") ;

@end

@protocol GKGameCenterControllerDelegate <NSObject>

- (void)gameCenterViewControllerDidFinish:(GKGameCenterViewController *)gameCenterViewController NS_AVAILABLE(10_9, 6_0);

@end

NS_ASSUME_NONNULL_END
