//
//  CPTemplateApplicationDashboardScene.h
//  CarPlay
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <CarPlay/CarPlay.h>
#import <CarPlay/CPDashboardController.h>

NS_ASSUME_NONNULL_BEGIN
@class CPTemplateApplicationDashboardScene;
@class CPDashboardController;

API_AVAILABLE(ios(13.4)) API_UNAVAILABLE(macos, watchos, tvos)
@protocol CPTemplateApplicationDashboardSceneDelegate <UISceneDelegate>

@optional

/**
The Dashboard navigation widget has connected and is ready to present content.

Your app should create its view controller and assign it to the @c rootViewController property
of this window.

@note The dashboardController object will be strongly retained by the CPTemplateApplicationDashboardScene, the delegate does not need to retain it.
*/
- (void)templateApplicationDashboardScene:(CPTemplateApplicationDashboardScene *)templateApplicationDashboardScene didConnectDashboardController:(CPDashboardController *)dashboardController toWindow:(UIWindow *)window;

/**
The Dashboard navigation widget has disconnected.
*/
- (void)templateApplicationDashboardScene:(CPTemplateApplicationDashboardScene *)templateApplicationDashboardScene didDisconnectDashboardController:(CPDashboardController *)dashboardController fromWindow:(UIWindow *)window;

@end

API_AVAILABLE(ios(13.4)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPTemplateApplicationDashboardScene : UIScene

/**
   The delegate for a CPTemplateApplicationDashboardScene must conform to the CPTemplateApplicationDashboardSceneDelegate protocol.
*/
@property (nullable, nonatomic, strong) id<CPTemplateApplicationDashboardSceneDelegate> delegate;

/**
   The dashboardController object for this scene.
*/
@property (nonnull, nonatomic, strong, readonly) CPDashboardController *dashboardController;

/**
   The UIWindow created for this CPTemplateApplicationDashboardScene
*/
@property (nonnull, nonatomic, strong, readonly) UIWindow *dashboardWindow;

@end

// A session role which defines a typical interactive application in the CarPlay dashboard
extern UISceneSessionRole const CPTemplateApplicationDashboardSceneSessionRoleApplication API_AVAILABLE(ios(13.4));

NS_ASSUME_NONNULL_END
