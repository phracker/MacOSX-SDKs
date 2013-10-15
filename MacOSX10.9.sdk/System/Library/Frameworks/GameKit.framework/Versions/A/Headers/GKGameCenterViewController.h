//
//  GKGameCenterViewController.h
//  GameKit
//
//  Copyright 2012 Apple Inc. All rights reserved.
//

#import <GameKit/GKLeaderboard.h>

@class GKMatch, GKMatchRequest, GKInvite;
@protocol GKGameCenterControllerDelegate;

typedef enum /*: NSInteger */ {
    GKGameCenterViewControllerStateDefault = -1,
    GKGameCenterViewControllerStateLeaderboards ,
    GKGameCenterViewControllerStateAchievements,
    GKGameCenterViewControllerStateChallenges,
} GKGameCenterViewControllerState;

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
NS_CLASS_AVAILABLE(10_9, 6_0)
@interface GKGameCenterViewController : UINavigationController
@end
#else
#import <Cocoa/Cocoa.h>
#import <GameKit/GKDialogController.h>
NS_CLASS_AVAILABLE(10_9, 6_0)
@interface GKGameCenterViewController : NSViewController  <GKViewController> {
	id _internal1,_internal2,_internal3;
    NSInteger _internal4;
}
@end
#endif

@interface GKGameCenterViewController ()
@property (assign, NS_NONATOMIC_IOSONLY)   id<GKGameCenterControllerDelegate>      gameCenterDelegate;
@property (assign, NS_NONATOMIC_IOSONLY)   GKGameCenterViewControllerState         viewState;

@end

@interface GKGameCenterViewController (Leaderboards)

@property (assign, NS_NONATOMIC_IOSONLY)   GKLeaderboardTimeScope                  leaderboardTimeScope;   // Implies showing leaderboards
@property (copy, NS_NONATOMIC_IOSONLY)   NSString                                *leaderboardCategory;   // Implies showing leaderboards

@end

@protocol GKGameCenterControllerDelegate <NSObject>

- (void)gameCenterViewControllerDidFinish:(GKGameCenterViewController *)gameCenterViewController;

@end
