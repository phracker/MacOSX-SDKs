//
//  GKLeaderboardViewController.h
//  GameKit
//
//  Copyright 2010 Apple Inc. All rights reserved.
//

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <AppKit/AppKit.h>
#endif

#import <GameKit/GKLeaderboard.h>
#import <GameKit/GKGameCenterViewController.h>

@protocol GKLeaderboardViewControllerDelegate;

// View controller that provides the standard user interface for leaderboards.  Present modally from the top view controller.

#if TARGET_OS_IPHONE
NS_CLASS_AVAILABLE(NA, 4_1)
@interface GKLeaderboardViewController : GKGameCenterViewController
@end
#else
#import <GameKit/GKDialogController.h>
NS_CLASS_AVAILABLE(10_8, NA)
@interface GKLeaderboardViewController : NSViewController <GKViewController> {
	id _internal1,_internal2,_internal3,_internal4;
}
@end
#endif

@interface GKLeaderboardViewController ()
@property (assign, ) GKLeaderboardTimeScope timeScope;
@property (copy, NS_NONATOMIC_IOSONLY)   NSString *category;
@property (assign, NS_NONATOMIC_IOSONLY) id <GKLeaderboardViewControllerDelegate> leaderboardDelegate;

@end

@protocol GKLeaderboardViewControllerDelegate
@required
// The leaderboard view has finished
- (void)leaderboardViewControllerDidFinish:(GKLeaderboardViewController *)viewController;
@end
