//
//  CPTemplateApplicationScene.h
//  CarPlay
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CarPlay/CPInterfaceController.h>
#import <CarPlay/CPWindow.h>

NS_ASSUME_NONNULL_BEGIN

@class CPTemplateApplicationScene;

API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, watchos, tvos)
@protocol CPTemplateApplicationSceneDelegate <UISceneDelegate>

@optional

/**
 The CarPlay screen has connected and is ready to present content.
 
 Your app should create its view controller and assign it to the @c rootViewController property
 of this window.
 
 @note The interfaceController object will be strongly retained by the CPTemplateApplicationScene, the delegate does not need to retain it.
 
 @note This method is provided only for navigation apps; other apps should use the variant that does not provide a window.
 */
- (void)templateApplicationScene:(CPTemplateApplicationScene *)templateApplicationScene
   didConnectInterfaceController:(CPInterfaceController *)interfaceController
                        toWindow:(CPWindow *)window;

/**
 The CarPlay screen has connected and is ready to present content.
 
 Your app should create its view controller and assign it to the @c rootViewController property
 of this window.
 
 @note The interfaceController object will be strongly retained by the CPTemplateApplicationScene, the delegate does not need to retain it.
  */
- (void)templateApplicationScene:(CPTemplateApplicationScene *)templateApplicationScene
   didConnectInterfaceController:(CPInterfaceController *)interfaceController API_AVAILABLE(ios(14.0));

/**
 The CarPlay screen has disconnected.
 
 @note This method is provided only for navigation apps; other apps should use the variant that does not provide a window.
 */
- (void)templateApplicationScene:(CPTemplateApplicationScene *)templateApplicationScene
didDisconnectInterfaceController:(CPInterfaceController *)interfaceController
                      fromWindow:(CPWindow *)window;

/**
 The CarPlay screen has disconnected.
 */
- (void)templateApplicationScene:(CPTemplateApplicationScene *)templateApplicationScene
didDisconnectInterfaceController:(CPInterfaceController *)interfaceController API_AVAILABLE(ios(14.0));

/**
 If your application posts a @c CPNavigationAlert while backgrounded, a notification banner may be presented to the user.
 If the user taps on that banner, your application will launch on the car screen and this method will be called
 with the alert the user tapped.
 */
- (void)templateApplicationScene:(CPTemplateApplicationScene *)templateApplicationScene didSelectNavigationAlert:(CPNavigationAlert *)navigationAlert;

/**
 If your application posts a @c CPManeuver while backgrounded, a notification banner may be presented to the user.
 If the user taps on that banner, your application will launch on the car screen and this method will be called
 with the maneuver the user tapped.
 */
- (void)templateApplicationScene:(CPTemplateApplicationScene *)templateApplicationScene didSelectManeuver:(CPManeuver *)maneuver;

@end


API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPTemplateApplicationScene : UIScene

/**
    The delegate for a CPTemplateApplicationScene must conform to the CPTemplateApplicationSceneDelegate protocol.
 */
@property (nullable, nonatomic, strong) id<CPTemplateApplicationSceneDelegate> delegate;

/**
    The interfaceController object for this scene.
 */
@property (nonnull, nonatomic, strong, readonly) CPInterfaceController *interfaceController;

/**
    The CPWindow created for this CPTemplateApplicationScene
 */
@property (nonnull, nonatomic, strong, readonly) CPWindow *carWindow;

@end

// A session role which defines a typical interactive application on the car display
extern UISceneSessionRole const CPTemplateApplicationSceneSessionRoleApplication API_AVAILABLE(ios(13.0));

NS_ASSUME_NONNULL_END
