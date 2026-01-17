// Copyright © Apple Inc. All rights reserved.

#import <TargetConditionals.h>

#import <GameKit/GKLeaderboard.h>
#import <GameKit/GKGameCenterViewController.h>

@protocol GKLeaderboardViewControllerDelegate;

/// View controller that provides the standard user interface for leaderboards.  Present modally from the top view controller.
API_DEPRECATED_WITH_REPLACEMENT("Use ``GKGameCenterViewController`` instead.", ios(4.1,7.0), macos(10.8,10.10)) API_UNAVAILABLE(tvos, watchos)
@interface GKLeaderboardViewController : GKGameCenterViewController
#if !TARGET_OS_IPHONE
{
    NSString *_category;
    GKLeaderboardTimeScope _timeScope;
}
#endif
@end

@interface GKLeaderboardViewController ()
@property (assign, NS_NONATOMIC_IOSONLY) GKLeaderboardTimeScope timeScope;
@property (copy, NS_NONATOMIC_IOSONLY)   NSString *category;
@property (weak, NS_NONATOMIC_IOSONLY) id <GKLeaderboardViewControllerDelegate> leaderboardDelegate;

@end

API_DEPRECATED_WITH_REPLACEMENT("Use ``GKGameCenterViewController`` instead.", ios(4.1,7.0), macos(10.8,10.10)) API_UNAVAILABLE(tvos, watchos)
@protocol GKLeaderboardViewControllerDelegate <NSObject>
@required
/// The leaderboard view has finished
- (void)leaderboardViewControllerDidFinish:(GKLeaderboardViewController *)viewController;
@end

