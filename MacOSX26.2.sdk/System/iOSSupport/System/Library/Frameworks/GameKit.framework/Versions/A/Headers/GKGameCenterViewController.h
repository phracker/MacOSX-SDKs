// Copyright © Apple Inc. All rights reserved.

#import <TargetConditionals.h>

#import <GameKit/GKLeaderboard.h>
#import <GameKit/GKAchievement.h>

API_UNAVAILABLE_BEGIN(watchos)

API_DEPRECATED_WITH_REPLACEMENT("Replaced by ``GKAccessPoint``", ios(6.0,26.0), macos(10.8,26.0), tvos(9.0,26.0), visionos(1.0,26.0))
@protocol GKGameCenterControllerDelegate;

typedef NS_ENUM(NSInteger, GKGameCenterViewControllerState) {
    GKGameCenterViewControllerStateDefault = -1,
    GKGameCenterViewControllerStateLeaderboards,
    GKGameCenterViewControllerStateAchievements,
    GKGameCenterViewControllerStateChallenges               API_DEPRECATED_WITH_REPLACEMENT("Replaced by developer defined challenges, see ``GKChallengeDefinition``", ios(6.0,26.0), macos(10.8,26.0), tvos(9.0,26.0), visionos(1.0,26.0)),
    GKGameCenterViewControllerStateLocalPlayerProfile       API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0), visionos(1.0)),
    GKGameCenterViewControllerStateDashboard                API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0), visionos(1.0)),
    GKGameCenterViewControllerStateLocalPlayerFriendsList   API_AVAILABLE(ios(15.0), macos(12.0), tvos(15.0), visionos(1.0))
} API_AVAILABLE(ios(6.0), macos(10.8), tvos(9.0), visionos(1.0));

#if TARGET_OS_WATCH
#elif TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <Cocoa/Cocoa.h>
#import <GameKit/GKDialogController.h>
#endif

NS_ASSUME_NONNULL_BEGIN
#if TARGET_OS_WATCH
/// View controller that provides the standard user interface for leaderboards, achievements, and challenges. Present modally from the top view controller.
API_DEPRECATED_WITH_REPLACEMENT("Replaced by ``GKAccessPoint``", ios(6.0,26.0), macos(10.9,26.0), tvos(9.0,26.0), visionos(1.0,26.0))
@interface GKGameCenterViewController
@end
#elif TARGET_OS_IPHONE
/// View controller that provides the standard user interface for leaderboards, achievements, and challenges. Present modally from the top view controller.
API_DEPRECATED_WITH_REPLACEMENT("Replaced by ``GKAccessPoint``", ios(6.0,26.0), macos(10.9,26.0), tvos(9.0,26.0), visionos(1.0,26.0))
@interface GKGameCenterViewController : UINavigationController
@end
#else
/// View controller that provides the standard user interface for leaderboards, achievements, and challenges. Present modally from the top view controller.
API_DEPRECATED_WITH_REPLACEMENT("Replaced by ``GKAccessPoint``", ios(6.0,26.0), macos(10.9,26.0), tvos(9.0,26.0), visionos(1.0,26.0))
@interface GKGameCenterViewController : NSViewController  <GKViewController>
@end
#endif

@interface GKGameCenterViewController ()

@property (weak, nullable, NS_NONATOMIC_IOSONLY) id<GKGameCenterControllerDelegate> gameCenterDelegate;

/**
 Use this to display content associated with the specified state. For example setting the state to GKGameCenterViewControllerStateLeaderboards will display a list of leaderboard sets or leaderboards (if no sets). Setting state to GKGameCenterViewControllerStateAchievements will display a list of achievements.
 */
- (instancetype)initWithState:(GKGameCenterViewControllerState)state API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0));

/**
 Use this to display the scores for the specified leaderboardID, player scope and time scope. The time scope is only applicable to classic leaderboards. Recurring leaderboards will always be displayed initially with the results (scores) associated with the current instance of the leaderboard.
 */
- (instancetype)initWithLeaderboardID:(NSString *)leaderboardID playerScope:(GKLeaderboardPlayerScope)playerScope timeScope:(GKLeaderboardTimeScope)timeScope API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0));

/**
 Use this to display the scores for the specified leaderboard and player scope. Both classic and recurring leaderboards can use this method to initialize the view with their scores.
 */
- (instancetype)initWithLeaderboard:(GKLeaderboard *)leaderboard playerScope:(GKLeaderboardPlayerScope)playerScope API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0));

/**
 Use this to display the leaderboard sets for the specified leaderboardSetID.
 */
- (instancetype)initWithLeaderboardSetID:(NSString *)leaderboardSetID API_AVAILABLE(ios(18.0), macos(15.0), tvos(18.0), visionos(2.0));

/**
 Use this to display the details associated with the specified achievementID
 */
- (instancetype)initWithAchievementID:(NSString *)achievementID API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0));

/**
 Use this to display the profile page associated with the specified player.
 */
- (instancetype)initWithPlayer:(GKPlayer *)player API_AVAILABLE(ios(18.0), macos(15.0), tvos(18.0), visionos(2.0));

@end

@interface GKGameCenterViewController (Deprecated)

@property (assign, NS_NONATOMIC_IOSONLY) GKGameCenterViewControllerState viewState API_DEPRECATED_WITH_REPLACEMENT("Use ``GKGameCenterViewController/init(state:)`` instead.", ios(6.0, 14.0), tvos(9.0, 14.0), macos(10.9, 11.0));
@property (nonatomic, assign) GKLeaderboardTimeScope leaderboardTimeScope API_DEPRECATED_WITH_REPLACEMENT("Use ``GKGameCenterViewController/init(leaderboardID:playerScope:timeScope:)`` instead.", ios(4.1, 14.0), macos(10.8, 11.0)) API_UNAVAILABLE(tvos);
@property (nonatomic, nullable, strong) NSString *leaderboardIdentifier API_DEPRECATED_WITH_REPLACEMENT("Use ``GKGameCenterViewController/init(leaderboard:playerScope:)`` instead.", ios(7.0, 14.0), tvos(9.0, 14.0), macos(10.10, 11.0));
@property (nonatomic, nullable, strong) NSString *leaderboardCategory API_DEPRECATED_WITH_REPLACEMENT("Use ``GKGameCenterViewController/init(leaderboard:playerScope:)`` instead.", ios(4.1,7.0), macos(10.8,10.10)) API_UNAVAILABLE(tvos);

@end

@protocol GKGameCenterControllerDelegate <NSObject>

- (void)gameCenterViewControllerDidFinish:(GKGameCenterViewController *)gameCenterViewController API_AVAILABLE(ios(6.0), macos(10.9), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END

API_UNAVAILABLE_END // watchos
