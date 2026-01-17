#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIScene.h>)
//
//  UIScene.h
//  UIKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UISceneDefinitions.h>
#import <UIKit/UIResponder.h>

NS_ASSUME_NONNULL_BEGIN

@class UISceneSession, UISceneConnectionOptions, UIOpenURLContext, UISceneOpenExternalURLOptions, UISceneActivationConditions;
@protocol UISceneDelegate;

UIKIT_EXTERN API_AVAILABLE(ios(13.0)) @interface UIScene : UIResponder
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

// An initializer for subclasses, will be called by UIKit and not intended to be called by applications.
- (instancetype)initWithSession:(UISceneSession *)session connectionOptions:(UISceneConnectionOptions *)connectionOptions NS_DESIGNATED_INITIALIZER;

#pragma mark - Session
// The existing representation which references this UIScene instance
@property (nonatomic, readonly) UISceneSession *session;

#pragma mark - Delegate
// UIScene is strongly retained by UIKit like UIApplication, however, unlike UIApplication, the delegate may not need to live for the whole lifetime of the process.
// A strong ref here relieves clients of the responsibility of managing the delegate lifetime directly.
@property (nullable, nonatomic, strong) id<UISceneDelegate> delegate;

#pragma mark - State
// the activation state of this scene
@property (nonatomic, readonly) UISceneActivationState activationState;

#pragma mark - System Integration
// Options are specified in the UIApplication.h section for openURL options.
// An empty options dictionary will result in the same behavior as the older openURL call,
// aside from the fact that this is asynchronous and calls the completion handler rather than returning a result.
// The completion handler is called on the main queue.
- (void)openURL:(NSURL*)url options:(nullable UISceneOpenExternalURLOptions *)options completionHandler:(void (^ __nullable)(BOOL success))completion;

// A title for the scene to allow the system to differentiate multiple scenes for the user.
// If set to nil or an empty string, the system will not display a title.
@property (null_resettable, nonatomic, copy) NSString *title;

// use the activation conditions to influence which scene is activated for banner taps, URLs, etc.
@property (nonatomic, strong) UISceneActivationConditions *activationConditions;

@end

API_AVAILABLE(ios(13.0)) @protocol UISceneDelegate <NSObject>
@optional
#pragma mark Lifecycle State Transitioning
- (void)scene:(UIScene *)scene willConnectToSession:(UISceneSession *)session options:(UISceneConnectionOptions *)connectionOptions;
- (void)sceneDidDisconnect:(UIScene *)scene;

- (void)sceneDidBecomeActive:(UIScene *)scene;
- (void)sceneWillResignActive:(UIScene *)scene;

- (void)sceneWillEnterForeground:(UIScene *)scene;
- (void)sceneDidEnterBackground:(UIScene *)scene;

#pragma mark - System Integration
- (void)scene:(UIScene *)scene openURLContexts:(NSSet<UIOpenURLContext *> *)URLContexts;

#pragma mark - State Restoration Integration
// This is the NSUserActivity that will be used to restore state when the Scene reconnects.
// It can be the same activity used for handoff or spotlight, or it can be a separate activity
// with a different activity type and/or userInfo.
// After this method is called, and before the activity is actually saved in the restoration file,
// if the returned NSUserActivity has a delegate (NSUserActivityDelegate), the method
// userActivityWillSave is called on the delegate. Additionally, if any UIResponders
// have the activity set as their userActivity property, the UIResponder updateUserActivityState
// method is called to update the activity. This is done synchronously and ensures the activity
// has all info filled in before it is saved.
- (nullable NSUserActivity *)stateRestorationActivityForScene:(UIScene *)scene;

#pragma mark - User Activity Integration
- (void)scene:(UIScene *)scene willContinueUserActivityWithType:(NSString *)userActivityType;
- (void)scene:(UIScene *)scene continueUserActivity:(NSUserActivity *)userActivity;
- (void)scene:(UIScene *)scene didFailToContinueUserActivityWithType:(NSString *)userActivityType error:(NSError *)error;
- (void)scene:(UIScene *)scene didUpdateUserActivity:(NSUserActivity *)userActivity;
@end

#pragma mark - Lifecycle Notification Names
UIKIT_EXTERN NSNotificationName const UISceneWillConnectNotification API_AVAILABLE(ios(13.0));
UIKIT_EXTERN NSNotificationName const UISceneDidDisconnectNotification API_AVAILABLE(ios(13.0));
UIKIT_EXTERN NSNotificationName const UISceneDidActivateNotification API_AVAILABLE(ios(13.0));
UIKIT_EXTERN NSNotificationName const UISceneWillDeactivateNotification API_AVAILABLE(ios(13.0));
UIKIT_EXTERN NSNotificationName const UISceneWillEnterForegroundNotification API_AVAILABLE(ios(13.0));
UIKIT_EXTERN NSNotificationName const UISceneDidEnterBackgroundNotification API_AVAILABLE(ios(13.0));

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIScene.h>
#endif
