/*
 *  GKAchievementViewController.h
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

@protocol GKAchievementViewControllerDelegate;

// View controller that provides the standard user interface for achievements. Present modally from the top view controller.
#if TARGET_OS_IPHONE
NS_CLASS_AVAILABLE(NA, 4_1)
@interface GKAchievementViewController : GKGameCenterViewController
@end
#else
#include <GameKit/GKDialogController.h>
NS_CLASS_AVAILABLE(10_8, NA)
@interface GKAchievementViewController : NSViewController <GKViewController> {
	id _internal1,_internal2,_internal3,_internal4;
}
@end
#endif

@interface GKAchievementViewController ()
@property (assign, NS_NONATOMIC_IOSONLY) id<GKAchievementViewControllerDelegate> achievementDelegate;
@end

// Optional delegate
@protocol GKAchievementViewControllerDelegate
@required
// The achievement view has finished
- (void)achievementViewControllerDidFinish:(GKAchievementViewController *)viewController;
@end


