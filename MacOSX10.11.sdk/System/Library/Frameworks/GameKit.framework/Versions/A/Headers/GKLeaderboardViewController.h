//
//  GKLeaderboardViewController.h
//  Game Center
//
//  Copyright 2010-2015 Apple Inc. All rights reserved.
//

#import <GameKit/GKLeaderboard.h>
#import <GameKit/GKGameCenterViewController.h>

@protocol GKLeaderboardViewControllerDelegate;

// View controller that provides the standard user interface for leaderboards.  Present modally from the top view controller.
NS_CLASS_DEPRECATED(10_8, 10_10, 4_1, 7_0, "Use GKGameCenterViewController instead") 
@interface GKLeaderboardViewController : GKGameCenterViewController
#if !TARGET_OS_IPHONE
{
    id<GKLeaderboardViewControllerDelegate> _leaderboardDelegate;
    NSString *_category;
    GKLeaderboardTimeScope _timeScope;
}
#endif
@end

@interface GKLeaderboardViewController ()
@property (assign, NS_NONATOMIC_IOSONLY) GKLeaderboardTimeScope timeScope;
@property (copy, NS_NONATOMIC_IOSONLY)   NSString *category;
@property (assign, NS_NONATOMIC_IOSONLY) id <GKLeaderboardViewControllerDelegate> leaderboardDelegate;

@end

NS_DEPRECATED(10_8, 10_10, 4_1, 7_0, "Use GKGameCenterViewController instead") 
@protocol GKLeaderboardViewControllerDelegate <NSObject>
@required
// The leaderboard view has finished
- (void)leaderboardViewControllerDidFinish:(GKLeaderboardViewController *)viewController;
@end
