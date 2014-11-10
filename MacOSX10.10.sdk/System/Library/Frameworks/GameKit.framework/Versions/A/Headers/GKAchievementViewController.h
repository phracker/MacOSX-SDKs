//
//  GKAchievementViewController.h
//  Game Center
//
//  Copyright 2010-2014 Apple Inc. All rights reserved.
//

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <AppKit/AppKit.h>
#endif
#import <GameKit/GKGameCenterViewController.h>

@protocol GKAchievementViewControllerDelegate;

// View controller that provides the standard user interface for achievements. Present modally from the top view controller.
#if TARGET_OS_IPHONE
// View controller that provides the standard user interface for achievements. Present modally from the top view controller.
NS_DEPRECATED(10_8, 10_10, 4_1, 7_0, "Use GKGameCenterViewController instead")
@interface GKAchievementViewController : GKGameCenterViewController
@end
#else
#import <GameKit/GKDialogController.h>
NS_CLASS_AVAILABLE(10_8, 10_10)
@interface GKAchievementViewController : GKGameCenterViewController
{
    id<GKAchievementViewControllerDelegate> _achievementDelegate;
}
@end
#endif

@interface GKAchievementViewController ()
@property (assign, NS_NONATOMIC_IOSONLY) id<GKAchievementViewControllerDelegate> achievementDelegate;
@end

// Optional delegate
NS_DEPRECATED(10_8, 10_10, 4_1, 7_0, "Use GKGameCenterViewController instead")
@protocol GKAchievementViewControllerDelegate <NSObject>
@required
// The achievement view has finished
- (void)achievementViewControllerDidFinish:(GKAchievementViewController *)viewController;
@end


