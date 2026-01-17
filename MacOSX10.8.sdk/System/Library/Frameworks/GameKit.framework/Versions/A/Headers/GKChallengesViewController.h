/*
 *  GKChallengesViewController.h
 *  GameKit
 *
 *  Copyright 2010 Apple Inc. All rights reserved.
 */

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#import <GameKit/GKGameCenterViewController.h>
#else
#import <AppKit/AppKit.h>
#endif

@protocol GKChallengesViewControllerDelegate;

// View controller that provides the standard user interface for challenges. Present modally from the top view controller.
#if TARGET_OS_IPHONE
NS_CLASS_AVAILABLE(NA, 4_1)
@interface GKChallengesViewController : GKGameCenterViewController
@end
#else
#include <GameKit/GKDialogController.h>
NS_CLASS_AVAILABLE(10_8, NA)
@interface GKChallengesViewController : NSViewController <GKViewController> {
	id _internal1,_internal2,_internal3,_internal4;
}
@end
#endif

@interface GKChallengesViewController ()
@property (assign, NS_NONATOMIC_IOSONLY) id<GKChallengesViewControllerDelegate> challengeDelegate;
@end

// Optional delegate
@protocol GKChallengesViewControllerDelegate
@required
// The challenge view has finished
- (void)challengesViewControllerDidFinish:(GKChallengesViewController *)viewController;
@end
