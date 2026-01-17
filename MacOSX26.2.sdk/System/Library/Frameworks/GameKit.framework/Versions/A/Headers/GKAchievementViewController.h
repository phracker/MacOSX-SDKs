// Copyright © Apple Inc. All rights reserved.

#import <TargetConditionals.h>

#if !TARGET_OS_TV && !TARGET_OS_WATCH

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <AppKit/AppKit.h>
#endif
#import <GameKit/GKGameCenterViewController.h>

@protocol GKAchievementViewControllerDelegate;

/// View controller that provides the standard user interface for achievements. Present modally from the top view controller.
API_DEPRECATED_WITH_REPLACEMENT("Use ``GKGameCenterViewController`` instead.", ios(4.1,7.0), macos(10.8,10.10)) API_UNAVAILABLE(tvos)
@interface GKAchievementViewController : GKGameCenterViewController
@property (weak, NS_NONATOMIC_IOSONLY) id<GKAchievementViewControllerDelegate> achievementDelegate;
@end

/// Optional delegate
API_DEPRECATED_WITH_REPLACEMENT("Use ``GKGameCenterViewController`` instead.", ios(4.1,7.0), macos(10.8,10.10)) API_UNAVAILABLE(tvos)
@protocol GKAchievementViewControllerDelegate <NSObject>
@required
/// The achievement view has finished
- (void)achievementViewControllerDidFinish:(GKAchievementViewController *)viewController;
@end

#endif
