#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIApplication.h>)
//
//  UIApplication.h
//  UIKit
//
//  Copyright (c) 2005-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIResponder.h>
#import <UIKit/UIInterface.h>
#import <UIKit/UIDevice.h>
#import <UIKit/UIAlert.h>
#import <UIKit/UIContentSizeCategory.h>
#import <UIKit/UIOrientation.h>
#import <UIKit/UISceneDefinitions.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NS_ENUM(NSInteger, UIStatusBarStyle) {
    UIStatusBarStyleDefault                                  = 0, // Automatically chooses light or dark content based on the user interface style
    UIStatusBarStyleLightContent     API_AVAILABLE(ios(7.0)) = 1, // Light content, for use on dark backgrounds
    UIStatusBarStyleDarkContent     API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos) = 3, // Dark content, for use on light backgrounds
    
    UIStatusBarStyleBlackTranslucent API_DEPRECATED_WITH_REPLACEMENT("UIStatusBarStyleLightContent", ios(2.0, 7.0)) API_UNAVAILABLE(visionos, watchos) = 1,
    UIStatusBarStyleBlackOpaque      API_DEPRECATED_WITH_REPLACEMENT("UIStatusBarStyleLightContent", ios(2.0, 7.0)) API_UNAVAILABLE(visionos, watchos) = 2,
} API_UNAVAILABLE(tvos, watchos);

typedef NS_ENUM(NSInteger, UIStatusBarAnimation) {
    UIStatusBarAnimationNone,
    UIStatusBarAnimationFade API_AVAILABLE(ios(3.2)),
    UIStatusBarAnimationSlide API_AVAILABLE(ios(3.2)),
} API_UNAVAILABLE(tvos, watchos);

/* This exception is raised if supportedInterfaceOrientations returns 0, or if preferredInterfaceOrientationForPresentation
   returns an orientation that is not supported.
*/
UIKIT_EXTERN NSExceptionName const UIApplicationInvalidInterfaceOrientationException API_AVAILABLE(ios(6.0)) API_UNAVAILABLE(tvos, watchos);

typedef NS_OPTIONS(NSUInteger, UIRemoteNotificationType) {
    UIRemoteNotificationTypeNone    = 0,
    UIRemoteNotificationTypeBadge   = 1 << 0,
    UIRemoteNotificationTypeSound   = 1 << 1,
    UIRemoteNotificationTypeAlert   = 1 << 2,
    UIRemoteNotificationTypeNewsstandContentAvailability = 1 << 3,
} API_DEPRECATED("Use UserNotifications Framework's UNAuthorizationOptions for user notifications and registerForRemoteNotifications for receiving remote notifications instead.", ios(3.0, 8.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos);

typedef NS_ENUM(NSUInteger, UIBackgroundFetchResult) {
    UIBackgroundFetchResultNewData,
    UIBackgroundFetchResultNoData,
    UIBackgroundFetchResultFailed
} API_AVAILABLE(ios(7.0)) API_UNAVAILABLE(watchos);

typedef NS_ENUM(NSInteger, UIBackgroundRefreshStatus) {
    UIBackgroundRefreshStatusRestricted, // unavailable on this system due to device configuration; the user cannot enable the feature
    UIBackgroundRefreshStatusDenied,     // explicitly disabled by the user for this application
    UIBackgroundRefreshStatusAvailable   // enabled for this application
} API_AVAILABLE(ios(7.0), tvos(11.0)) API_UNAVAILABLE(watchos);
    
typedef NS_ENUM(NSInteger, UIApplicationState) {
    UIApplicationStateActive,
    UIApplicationStateInactive,
    UIApplicationStateBackground
} API_AVAILABLE(ios(4.0)) API_UNAVAILABLE(watchos);

typedef NSUInteger UIBackgroundTaskIdentifier NS_TYPED_ENUM API_UNAVAILABLE(watchos);
UIKIT_EXTERN const UIBackgroundTaskIdentifier UIBackgroundTaskInvalid  API_AVAILABLE(ios(4.0)) API_UNAVAILABLE(watchos);
UIKIT_EXTERN const NSTimeInterval UIMinimumKeepAliveTimeout API_DEPRECATED("Please use PushKit for VoIP applications.", ios(4.0, 13.0), tvos(9.0, 13.0)) API_UNAVAILABLE(visionos, watchos);
UIKIT_EXTERN const NSTimeInterval UIApplicationBackgroundFetchIntervalMinimum API_AVAILABLE(ios(7.0), tvos(11.0)) API_UNAVAILABLE(watchos);
UIKIT_EXTERN const NSTimeInterval UIApplicationBackgroundFetchIntervalNever API_AVAILABLE(ios(7.0), tvos(11.0)) API_UNAVAILABLE(watchos);

typedef NSString * UIApplicationOpenExternalURLOptionsKey NS_TYPED_ENUM API_UNAVAILABLE(watchos);

@class CKShareMetadata;
@class UIView, UIWindow;
@class UILocalNotification;
@protocol UIApplicationDelegate;
@class INIntent;
@class INIntentResponse;
@class UIScene, UIWindowScene, UISceneSession, UISceneSessionActivationRequest, UISceneConfiguration, UISceneConnectionOptions, UISceneActivationRequestOptions, UISceneDestructionRequestOptions;

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIApplication : UIResponder

@property(class, nonatomic, readonly) UIApplication *sharedApplication NS_EXTENSION_UNAVAILABLE_IOS("Use view controller based solutions where appropriate instead.");

@property(nullable, nonatomic, assign) id<UIApplicationDelegate> delegate;

- (void)beginIgnoringInteractionEvents API_DEPRECATED("Use UIView's userInteractionEnabled property instead", ios(2.0, 13.0)) API_UNAVAILABLE(visionos, watchos);               // nested. set should be set during animations & transitions to ignore touch and other events
- (void)endIgnoringInteractionEvents API_DEPRECATED("Use UIView's userInteractionEnabled property instead", ios(2.0, 13.0)) API_UNAVAILABLE(watchos);
@property(nonatomic, readonly, getter=isIgnoringInteractionEvents) BOOL ignoringInteractionEvents API_DEPRECATED("Use UIView's userInteractionEnabled property instead", ios(2.0, 13.0)) API_UNAVAILABLE(visionos, watchos);                  // returns YES if we are at least one deep in ignoring events

@property(nonatomic,getter=isIdleTimerDisabled)       BOOL idleTimerDisabled;	  // default is NO

- (BOOL)openURL:(NSURL*)url API_DEPRECATED_WITH_REPLACEMENT("openURL:options:completionHandler:", ios(2.0, 10.0)) API_UNAVAILABLE(visionos, watchos);
- (BOOL)canOpenURL:(NSURL *)url API_AVAILABLE(ios(3.0)) NS_SWIFT_NONISOLATED;

// Options are specified in the section below for openURL options. An empty options dictionary will result in the same
// behavior as the older openURL call, aside from the fact that this is asynchronous and calls the completion handler rather
// than returning a result.
// The completion handler is called on the main queue.
- (void)openURL:(NSURL*)url options:(NSDictionary<UIApplicationOpenExternalURLOptionsKey, id> *)options completionHandler:(void (^ __nullable NS_SWIFT_UI_ACTOR)(BOOL success))completion API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos);

- (void)sendEvent:(UIEvent *)event;

@property(nullable, nonatomic,readonly) UIWindow *keyWindow API_DEPRECATED("Should not be used for applications that support multiple scenes as it returns a key window across all connected scenes", ios(2.0, 13.0)) API_UNAVAILABLE(visionos, watchos);
@property(nonatomic,readonly) NSArray<__kindof UIWindow *>  *windows API_DEPRECATED("Use UIWindowScene.windows on a relevant window scene instead", ios(2.0, 15.0), visionos(1.0, 1.0)) API_UNAVAILABLE(watchos);

- (BOOL)sendAction:(SEL)action to:(nullable id)target from:(nullable id)sender forEvent:(nullable UIEvent *)event;

@property(nonatomic,getter=isNetworkActivityIndicatorVisible) BOOL networkActivityIndicatorVisible API_DEPRECATED("Provide a custom network activity UI in your app if desired.", ios(2.0, 13.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos);

@property(readonly, nonatomic) UIStatusBarStyle statusBarStyle API_UNAVAILABLE(tvos) API_DEPRECATED("Use the statusBarManager property of the window scene instead.", ios(2.0, 13.0)) API_UNAVAILABLE(visionos); // default is UIStatusBarStyleDefault

@property(readonly, nonatomic,getter=isStatusBarHidden) BOOL statusBarHidden API_UNAVAILABLE(tvos) API_DEPRECATED("Use the statusBarManager property of the window scene instead.", ios(2.0, 13.0)) API_UNAVAILABLE(visionos);

@property(readonly, nonatomic) UIInterfaceOrientation statusBarOrientation API_UNAVAILABLE(tvos) API_DEPRECATED("Use the interfaceOrientation property of the window scene instead.", ios(2.0, 13.0)) API_UNAVAILABLE(visionos);

// The system only calls this method if the application delegate has not
// implemented the delegate equivalent. It returns the orientations specified by
// the application's info.plist. If no supported interface orientations were
// specified it will return UIInterfaceOrientationMaskAll on an iPad and
// UIInterfaceOrientationMaskAllButUpsideDown on a phone.  The return value
// should be one of the UIInterfaceOrientationMask values which indicates the
// orientations supported by this application.
- (UIInterfaceOrientationMask)supportedInterfaceOrientationsForWindow:(nullable UIWindow *)window API_AVAILABLE(ios(6.0)) API_UNAVAILABLE(tvos);

@property(nonatomic,readonly) NSTimeInterval statusBarOrientationAnimationDuration API_DEPRECATED("Use viewWillTransitionToSize:withTransitionCoordinator: instead.", ios(2.0, 13.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos); // Returns the animation duration for the status bar during a 90 degree orientation change.  It should be doubled for a 180 degree orientation change.
@property(nonatomic,readonly) CGRect statusBarFrame API_DEPRECATED("Use the statusBarManager property of the window scene instead.", ios(2.0, 13.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos); // returns CGRectZero if the status bar is hidden

@property(nonatomic) NSInteger applicationIconBadgeNumber API_DEPRECATED("Use -[UNUserNotificationCenter setBadgeCount:withCompletionHandler:] instead.", ios(2.0, 17.0)) API_UNAVAILABLE(watchos);

@property(nonatomic) BOOL applicationSupportsShakeToEdit API_AVAILABLE(ios(3.0)) API_UNAVAILABLE(tvos);

@property(nonatomic,readonly) UIApplicationState applicationState API_AVAILABLE(ios(4.0));

@property(nonatomic,readonly) NSTimeInterval backgroundTimeRemaining API_AVAILABLE(ios(4.0)) NS_SWIFT_NONISOLATED;

- (UIBackgroundTaskIdentifier)beginBackgroundTaskWithExpirationHandler:(void(^ __nullable NS_SWIFT_UI_ACTOR)(void))handler  API_AVAILABLE(ios(4.0)) NS_REQUIRES_SUPER NS_SWIFT_NONISOLATED;
- (UIBackgroundTaskIdentifier)beginBackgroundTaskWithName:(nullable NSString *)taskName expirationHandler:(void(^ __nullable NS_SWIFT_UI_ACTOR)(void))handler API_AVAILABLE(ios(7.0)) NS_REQUIRES_SUPER NS_SWIFT_NONISOLATED;
- (void)endBackgroundTask:(UIBackgroundTaskIdentifier)identifier API_AVAILABLE(ios(4.0)) NS_REQUIRES_SUPER NS_SWIFT_NONISOLATED;

/*! The system guarantees that it will not wake up your application for a background fetch more
    frequently than the interval provided. Set to UIApplicationBackgroundFetchIntervalMinimum to be
    woken as frequently as the system desires, or to UIApplicationBackgroundFetchIntervalNever (the
    default) to never be woken for a background fetch.
 
    This setter will have no effect unless your application has the "fetch" 
    UIBackgroundMode. See the UIApplicationDelegate method
    `application:performFetchWithCompletionHandler:` for more. */
- (void)setMinimumBackgroundFetchInterval:(NSTimeInterval)minimumBackgroundFetchInterval API_DEPRECATED("Use a BGAppRefreshTask in the BackgroundTasks framework instead", ios(7.0, 13.0), tvos(11.0, 13.0)) API_UNAVAILABLE(visionos, watchos);
;

/*! When background refresh is available for an application, it may launched or resumed in the background to handle significant
    location changes, remote notifications, background fetches, etc. Observe UIApplicationBackgroundRefreshStatusDidChangeNotification to
    be notified of changes. */
@property (nonatomic, readonly) UIBackgroundRefreshStatus backgroundRefreshStatus API_AVAILABLE(ios(7.0), tvos(11.0));

@property(nonatomic,readonly,getter=isProtectedDataAvailable) BOOL protectedDataAvailable API_AVAILABLE(ios(4.0)) NS_SWIFT_NONISOLATED;

@property(nonatomic,readonly) UIUserInterfaceLayoutDirection userInterfaceLayoutDirection API_AVAILABLE(ios(5.0));

// Return the size category
@property(nonatomic,readonly) UIContentSizeCategory preferredContentSizeCategory API_AVAILABLE(ios(7.0));

#pragma mark -- UIScene --
// All of the currently connected UIScene instances
@property(nonatomic, readonly) NSSet<UIScene *> *connectedScenes API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

// All of the representations that currently have connected UIScene instances or had their sessions persisted by the system (ex: visible in iOS' switcher)
@property(nonatomic, readonly) NSSet<UISceneSession *> *openSessions API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

// returns YES if the application both declares multiple scene support in its info.plist and the executing environment allows multiple scenes for at least one system type. NO otherwise.
@property(nonatomic, readonly) BOOL supportsMultipleScenes API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Asks the system to activate an existing scene, or create a new scene and associate it with your app.
/// - Parameters:
///   - request: The activation request.
///   - errorHandler: A handler to be called if the request fails.
- (void)activateSceneSessionForRequest:(UISceneSessionActivationRequest *)request
                          errorHandler:(nullable void (^)(NSError * error))errorHandler API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);

- (void)requestSceneSessionActivation:(nullable UISceneSession *)sceneSession
                         userActivity:(nullable NSUserActivity *)userActivity
                              options:(nullable UISceneActivationRequestOptions *)options
                         errorHandler:(nullable void (^)(NSError * error))errorHandler API_DEPRECATED("Please use activateSceneSessionForRequest:errorHandler:", ios(13.0, API_TO_BE_DEPRECATED), visionos(1.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(watchos);

// requests that a given session be closed, disconnecting the currently connected scene if present, and calling the -application:didDiscardSceneSessions: method on the application's delegate
- (void)requestSceneSessionDestruction:(UISceneSession *)sceneSession options:(nullable UISceneDestructionRequestOptions *)options errorHandler:(nullable void (^)(NSError * error))errorHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

// requests that any system UI representing a scene be updated due to background updates or any other relevant model/state update.
- (void)requestSceneSessionRefresh:(UISceneSession *)sceneSession API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

@end

@interface UIApplication (UIRemoteNotifications)

// Calling this will result in either application:didRegisterForRemoteNotificationsWithDeviceToken: or application:didFailToRegisterForRemoteNotificationsWithError: to be called on the application delegate. Note: these callbacks will be made only if the application has successfully registered for user notifications with registerUserNotificationSettings:, or if it is enabled for Background App Refresh.
- (void)registerForRemoteNotifications API_AVAILABLE(ios(8.0));

- (void)unregisterForRemoteNotifications API_AVAILABLE(ios(3.0));

// Returns YES if the application is currently registered for remote notifications, taking into account any systemwide settings; doesn't relate to connectivity.
@property(nonatomic, readonly, getter=isRegisteredForRemoteNotifications) BOOL registeredForRemoteNotifications API_AVAILABLE(ios(8.0));

- (void)registerForRemoteNotificationTypes:(UIRemoteNotificationType)types API_DEPRECATED("Use -[UIApplication registerForRemoteNotifications] and UserNotifications Framework's -[UNUserNotificationCenter requestAuthorizationWithOptions:completionHandler:]", ios(3.0, 8.0)) API_UNAVAILABLE(visionos, tvos, watchos);

// Returns the enabled types, also taking into account any systemwide settings; doesn't relate to connectivity.
- (UIRemoteNotificationType)enabledRemoteNotificationTypes API_DEPRECATED("Use -[UIApplication isRegisteredForRemoteNotifications] and UserNotifications Framework's -[UNUserNotificationCenter getNotificationSettingsWithCompletionHandler:] to retrieve user-enabled remote notification and user notification settings", ios(3.0, 8.0)) API_UNAVAILABLE(visionos, tvos, watchos);

@end

// In iOS 8.0 and later, your application must register for user notifications using -[UIApplication registerUserNotificationSettings:] before being able to schedule and present UILocalNotifications
@interface UIApplication (UILocalNotifications)

- (void)presentLocalNotificationNow:(UILocalNotification *)notification API_DEPRECATED("Use UserNotifications Framework's -[UNUserNotificationCenter addNotificationRequest:withCompletionHandler:]", ios(4.0, 10.0)) API_UNAVAILABLE(visionos, tvos, watchos);

- (void)scheduleLocalNotification:(UILocalNotification *)notification API_DEPRECATED("Use UserNotifications Framework's -[UNUserNotificationCenter addNotificationRequest:withCompletionHandler:]", ios(4.0, 10.0)) API_UNAVAILABLE(visionos, tvos, watchos);  // copies notification
- (void)cancelLocalNotification:(UILocalNotification *)notification API_DEPRECATED("Use UserNotifications Framework's -[UNUserNotificationCenter removePendingNotificationRequestsWithIdentifiers:]", ios(4.0, 10.0)) API_UNAVAILABLE(visionos, tvos, watchos);
- (void)cancelAllLocalNotifications API_DEPRECATED("Use UserNotifications Framework's -[UNUserNotificationCenter removeAllPendingNotificationRequests]", ios(4.0, 10.0)) API_UNAVAILABLE(visionos, tvos, watchos);

@property(nullable,nonatomic,copy) NSArray<UILocalNotification *> *scheduledLocalNotifications API_DEPRECATED("Use UserNotifications Framework's -[UNUserNotificationCenter getPendingNotificationRequestsWithCompletionHandler:]", ios(4.0, 10.0)) API_UNAVAILABLE(visionos, tvos, watchos);

@end

@class UIUserNotificationSettings;
@interface UIApplication (UIUserNotificationSettings)

// Registering UIUserNotificationSettings more than once results in previous settings being overwritten.
- (void)registerUserNotificationSettings:(UIUserNotificationSettings *)notificationSettings API_DEPRECATED("Use UserNotifications Framework's -[UNUserNotificationCenter requestAuthorizationWithOptions:completionHandler:] and -[UNUserNotificationCenter setNotificationCategories:]", ios(8.0, 10.0)) API_UNAVAILABLE(visionos, tvos, watchos);

// Returns the enabled user notification settings, also taking into account any systemwide settings.
@property(nonatomic, readonly, nullable) UIUserNotificationSettings *currentUserNotificationSettings API_DEPRECATED("Use UserNotifications Framework's -[UNUserNotificationCenter getNotificationSettingsWithCompletionHandler:] and -[UNUserNotificationCenter getNotificationCategoriesWithCompletionHandler:]", ios(8.0, 10.0)) API_UNAVAILABLE(visionos, tvos, watchos);

@end

@interface UIApplication (UIRemoteControlEvents)

- (void)beginReceivingRemoteControlEvents API_AVAILABLE(ios(4.0));
- (void)endReceivingRemoteControlEvents API_AVAILABLE(ios(4.0));

@end

@interface UIApplication (UINewsstand)
- (void)setNewsstandIconImage:(nullable UIImage *)image API_DEPRECATED("Newsstand apps now behave like normal apps on SpringBoard", ios(5.0, 9.0)) API_UNAVAILABLE(visionos, tvos, watchos);
@end

@class UIApplicationShortcutItem;
@interface UIApplication (UIShortcutItems)
// Register shortcuts to display on the home screen, or retrieve currently registered shortcuts.
@property (nullable, nonatomic, copy) NSArray<UIApplicationShortcutItem *> *shortcutItems API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(tvos);
@end

@interface UIApplication (UIAlternateApplicationIcons)
// If false, alternate icons are not supported for the current process.
@property (readonly, nonatomic) BOOL supportsAlternateIcons NS_EXTENSION_UNAVAILABLE("Extensions may not have alternate icons") API_AVAILABLE(ios(10.3), tvos(10.2)) API_UNAVAILABLE(watchos);

// Pass `nil` to use the primary application icon. The completion handler will be invoked asynchronously on an arbitrary background queue; be sure to dispatch back to the main queue before doing any further UI work.
- (void)setAlternateIconName:(nullable NSString *)alternateIconName completionHandler:(nullable void (^)(NSError *_Nullable error))completionHandler NS_EXTENSION_UNAVAILABLE("Extensions may not have alternate icons") API_AVAILABLE(ios(10.3), tvos(10.2)) API_UNAVAILABLE(watchos);

// If `nil`, the primary application icon is being used.
@property (nullable, readonly, nonatomic) NSString *alternateIconName NS_EXTENSION_UNAVAILABLE("Extensions may not have alternate icons") API_AVAILABLE(ios(10.3), tvos(10.2)) API_UNAVAILABLE(watchos);
@end

@protocol UIStateRestoring;
@interface UIApplication (UIStateRestoration)
// These methods are used to inform the system that state restoration is occurring asynchronously after the application
// has processed its restoration archive on launch. In the even of a crash, the system will be able to detect that it may
// have been caused by a bad restoration archive and arrange to ignore it on a subsequent application launch.
- (void)extendStateRestoration  API_AVAILABLE(ios(6.0));
- (void)completeStateRestoration  API_AVAILABLE(ios(6.0));

// Indicate the application should not use the snapshot on next launch, even if there is a valid state restoration archive.
// This should only be called from methods invoked from State Preservation, else it is ignored.
- (void)ignoreSnapshotOnNextApplicationLaunch API_AVAILABLE(ios(7.0));

// Register non-View/ViewController objects for state restoration so other objects can reference them within state restoration archives.
// If the object implements encode/decode, those methods will be called during save/restore.
// Obj and identifier must not be nil, or will raise UIRestorationObjectRegistrationException.
// Objects do not need to be unregistered when they are deleted, the State Restoration system will notice and stop tracking the object.
+ (void)registerObjectForStateRestoration:(id<UIStateRestoring>)object restorationIdentifier:(NSString *)restorationIdentifier API_AVAILABLE(ios(7.0));
@end


typedef NS_ENUM(NSInteger, UIApplicationCategory) {
    UIApplicationCategoryWebBrowser = 1
}
API_AVAILABLE(ios(18.2)) API_UNAVAILABLE(visionos, macCatalyst) API_UNAVAILABLE(watchos, tvos)
NS_SWIFT_NAME(UIApplication.Category);

/// The default status of an application for some category.
typedef NS_ENUM(NSInteger, UIApplicationCategoryDefaultStatus) {
    /// The status was not available. This is an error condition and the returned error object has more information.
    UIApplicationCategoryDefaultStatusUnavailable,

    /// The application is the default for the category.
    UIApplicationCategoryDefaultStatusIsDefault,

    /// The application is not the default for the category.
    UIApplicationCategoryDefaultStatusNotDefault
} API_AVAILABLE(ios(18.2)) API_UNAVAILABLE(visionos, macCatalyst) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UNAVAILABLE("Use UIApplication.isDefault(_:)");

UIKIT_EXTERN NSErrorDomain const UIApplicationCategoryDefaultErrorDomain
API_AVAILABLE(ios(18.2)) API_UNAVAILABLE(visionos, macCatalyst) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_NONISOLATED NS_SWIFT_UNAVAILABLE("Use UIApplication.CategoryDefaultError.domain");

typedef NS_ERROR_ENUM(UIApplicationCategoryDefaultErrorDomain, UIApplicationCategoryDefaultErrorCode) {
    /// The application is rate-limited.
    UIApplicationCategoryDefaultErrorRateLimited = 1,
}
API_AVAILABLE(ios(18.2)) API_UNAVAILABLE(visionos, macCatalyst) API_UNAVAILABLE(watchos, tvos)
NS_SWIFT_NAME(UIApplication.CategoryDefaultError);

/// Supplied in userInfo when the application is rate-limited: the last date on which data was
/// retrieved.
UIKIT_EXTERN NSErrorUserInfoKey const UIApplicationCategoryDefaultStatusLastProvidedDateErrorKey
API_AVAILABLE(ios(18.2)) API_UNAVAILABLE(visionos, macCatalyst) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_NONISOLATED NS_REFINED_FOR_SWIFT;

/// Supplied in userInfo when the application is rate-limited: the date after which the app will no
/// longer be rate-limited
UIKIT_EXTERN NSErrorUserInfoKey const UIApplicationCategoryDefaultRetryAvailabilityDateErrorKey
API_AVAILABLE(ios(18.2)) API_UNAVAILABLE(visionos, macCatalyst) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_NONISOLATED NS_REFINED_FOR_SWIFT;

@interface UIApplication (DefaultApplication)

/// Determine whether the application is the current default app for some category of application.
///
/// When this method returns `UIApplicationCategoryDefaultStatusIsDefault`, the application
/// is the default for the provided category.
///
/// When this method returns `UIApplicationCategoryDefaultStatusNotDefault`, the application is
/// not the default for the provide category.
///
/// Otherwise, this method returns `UIApplicationCategoryDefaultStatusUnavailable`, which is an error
/// condition (e.g., the application was rate-limited); the `NSError` object returned in the error
/// out-parameter has more information.
///
/// The system reserves the right to aggressively rate-limit its response. If the application is
/// rate-limited, the method will fail, the error will be `UIApplicationCategoryDefaultErrorRateLimited`
/// in the `UIApplicationCategoryDefaultErrorDomain` domain, and two keys will be in the error userInfo
/// dictionary: `UIApplicationCategoryDefaultStatusLastProvidedDateErrorKey`, which is the date when
/// an answer was last provided to the app, and `UIApplicationCategoryDefaultRetryAvailabilityDateErrorKey`,
/// which is the date after which the application can expect to ask again (i.e., will not be
/// rate-limited any more).
- (UIApplicationCategoryDefaultStatus)defaultStatusForCategory:(UIApplicationCategory)category error:(NSError **)error
API_AVAILABLE(ios(18.2)) API_UNAVAILABLE(visionos, macCatalyst) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_NONISOLATED NS_REFINED_FOR_SWIFT;

@end


typedef NSString * UIApplicationLaunchOptionsKey NS_TYPED_ENUM API_UNAVAILABLE(watchos);

API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UIApplicationDelegate<NSObject>

@optional

- (void)applicationDidFinishLaunching:(UIApplication *)application;
- (BOOL)application:(UIApplication *)application willFinishLaunchingWithOptions:(nullable NSDictionary<UIApplicationLaunchOptionsKey, id> *)launchOptions API_AVAILABLE(ios(6.0));
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(nullable NSDictionary<UIApplicationLaunchOptionsKey, id> *)launchOptions API_AVAILABLE(ios(3.0));

/// Tells the delegate that the application has become active
/// - Note: This method is not called if `UIScene` lifecycle has been adopted.
- (void)applicationDidBecomeActive:(UIApplication *)application API_DEPRECATED("Use UIScene lifecycle and sceneDidBecomeActive(_:) from UISceneDelegate or the UIApplication.didBecomeActiveNotification instead.", ios(2.0, 26.0), tvos(9.0, 26.0), visionos(1.0, 26.0)) API_UNAVAILABLE(watchos);

/// Tells the delegate that the application is about to become inactive
/// - Note: This method is not called if `UIScene` lifecycle has been adopted.
- (void)applicationWillResignActive:(UIApplication *)application API_DEPRECATED("Use UIScene lifecycle and sceneWillResignActive(_:) from UISceneDelegate or the UIApplication.willResignActiveNotification instead.", ios(2.0, 26.0), tvos(9.0, 26.0), visionos(1.0, 26.0)) API_UNAVAILABLE(watchos);

/// Tells the delegate that the application is now in the background
/// - Note: This method is not called if `UIScene` lifecycle has been adopted.
- (void)applicationDidEnterBackground:(UIApplication *)application API_AVAILABLE(ios(4.0)) API_DEPRECATED("Use UIScene lifecycle and sceneDidEnterBackground(_:) from UISceneDelegate or the UIApplication.didEnterBackgroundNotification instead.", ios(4.0, 26.0), tvos(9.0, 26.0), visionos(1.0, 26.0)) API_UNAVAILABLE(watchos);

/// Tells the delegate that the application is about to enter the foreground
/// - Note: This method is not called if `UIScene` lifecycle has been adopted.
- (void)applicationWillEnterForeground:(UIApplication *)application API_DEPRECATED("Use UIScene lifecycle and sceneWillEnterForeground(_:) from UISceneDelegate or the UIApplication.willEnterForegroundNotification instead.", ios(4.0, 26.0), tvos(9.0, 26.0), visionos(1.0, 26.0)) API_UNAVAILABLE(watchos);

- (BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)url API_DEPRECATED_WITH_REPLACEMENT("application:openURL:options:", ios(2.0, 9.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos);

- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(nullable NSString *)sourceApplication annotation:(id)annotation API_DEPRECATED_WITH_REPLACEMENT("application:openURL:options:", ios(4.2, 9.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos);


typedef NSString * UIApplicationOpenURLOptionsKey NS_TYPED_ENUM API_DEPRECATED("Use UIScene lifecycle and equivalent properties on UISceneOpenURLOptions from a UIOpenURLContext in UIScene.ConnectionOptions.URLContexts instead.", ios(9.0, 26.0), tvos(9.0, 26.0), visionos(1.0, 26.0)) API_UNAVAILABLE(watchos);

/// Return NO if the application can't open the `url` for some reason
- (BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey, id> *)options API_DEPRECATED("Use UIScene lifecycle and scene(_:openURLContexts:) from UISceneDelegate instead.", ios(9.0, 26.0), tvos(9.0, 26.0), visionos(1.0, 26.0)) API_UNAVAILABLE(watchos);

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application;      // try to clean up as much memory as possible. next step is to terminate app
- (void)applicationWillTerminate:(UIApplication *)application;
- (void)applicationSignificantTimeChange:(UIApplication *)application;        // midnight, carrier time update, daylight savings time change

- (void)application:(UIApplication *)application willChangeStatusBarOrientation:(UIInterfaceOrientation)newStatusBarOrientation duration:(NSTimeInterval)duration API_DEPRECATED("Use viewWillTransitionToSize:withTransitionCoordinator: instead.", ios(2.0, 13.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos);
- (void)application:(UIApplication *)application didChangeStatusBarOrientation:(UIInterfaceOrientation)oldStatusBarOrientation API_DEPRECATED("Use viewWillTransitionToSize:withTransitionCoordinator: instead.", ios(2.0, 13.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos);

- (void)application:(UIApplication *)application willChangeStatusBarFrame:(CGRect)newStatusBarFrame API_DEPRECATED("Use viewWillTransitionToSize:withTransitionCoordinator: instead.", ios(2.0, 13.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos);   // in screen coordinates
- (void)application:(UIApplication *)application didChangeStatusBarFrame:(CGRect)oldStatusBarFrame API_DEPRECATED("Use viewWillTransitionToSize:withTransitionCoordinator: instead.", ios(2.0, 13.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos);

// This callback will be made upon calling -[UIApplication registerUserNotificationSettings:]. The settings the user has granted to the application will be passed in as the second argument.
- (void)application:(UIApplication *)application didRegisterUserNotificationSettings:(UIUserNotificationSettings *)notificationSettings API_DEPRECATED("Use UserNotifications Framework's -[UNUserNotificationCenter requestAuthorizationWithOptions:completionHandler:]", ios(8.0, 10.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos);

- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken API_AVAILABLE(ios(3.0));

- (void)application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error API_AVAILABLE(ios(3.0));

- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo API_DEPRECATED("Use UserNotifications Framework's -[UNUserNotificationCenterDelegate willPresentNotification:withCompletionHandler:] or -[UNUserNotificationCenterDelegate didReceiveNotificationResponse:withCompletionHandler:] for user visible notifications and -[UIApplicationDelegate application:didReceiveRemoteNotification:fetchCompletionHandler:] for silent remote notifications", ios(3.0, 10.0)) API_UNAVAILABLE(visionos, watchos);

- (void)application:(UIApplication *)application didReceiveLocalNotification:(UILocalNotification *)notification API_DEPRECATED("Use UserNotifications Framework's -[UNUserNotificationCenterDelegate willPresentNotification:withCompletionHandler:] or -[UNUserNotificationCenterDelegate didReceiveNotificationResponse:withCompletionHandler:]", ios(4.0, 10.0)) API_UNAVAILABLE(visionos, tvos, watchos);

// Called when your app has been activated by the user selecting an action from a local notification.
// A nil action identifier indicates the default action.
// You should call the completion handler as soon as you've finished handling the action.
- (void)application:(UIApplication *)application handleActionWithIdentifier:(nullable NSString *)identifier forLocalNotification:(UILocalNotification *)notification completionHandler:(void (^)(void))completionHandler API_DEPRECATED("Use UserNotifications Framework's -[UNUserNotificationCenterDelegate didReceiveNotificationResponse:withCompletionHandler:]", ios(8.0, 10.0)) API_UNAVAILABLE(visionos, tvos, watchos);

- (void)application:(UIApplication *)application handleActionWithIdentifier:(nullable NSString *)identifier forRemoteNotification:(NSDictionary *)userInfo withResponseInfo:(NSDictionary *)responseInfo completionHandler:(void (^)(void))completionHandler API_DEPRECATED("Use UserNotifications Framework's -[UNUserNotificationCenterDelegate didReceiveNotificationResponse:withCompletionHandler:]", ios(9.0, 10.0)) API_UNAVAILABLE(visionos, tvos, watchos);

// Called when your app has been activated by the user selecting an action from a remote notification.
// A nil action identifier indicates the default action.
// You should call the completion handler as soon as you've finished handling the action.
- (void)application:(UIApplication *)application handleActionWithIdentifier:(nullable NSString *)identifier forRemoteNotification:(NSDictionary *)userInfo completionHandler:(void (^)(void))completionHandler API_DEPRECATED("Use UserNotifications Framework's -[UNUserNotificationCenterDelegate didReceiveNotificationResponse:withCompletionHandler:]", ios(8.0, 10.0)) API_UNAVAILABLE(visionos, tvos, watchos);

- (void)application:(UIApplication *)application handleActionWithIdentifier:(nullable NSString *)identifier forLocalNotification:(UILocalNotification *)notification withResponseInfo:(NSDictionary *)responseInfo completionHandler:(void (^)(void))completionHandler API_DEPRECATED("Use UserNotifications Framework's -[UNUserNotificationCenterDelegate didReceiveNotificationResponse:withCompletionHandler:]", ios(9.0, 10.0)) API_UNAVAILABLE(visionos, tvos, watchos);

/*! This delegate method offers an opportunity for applications with the "remote-notification" background mode to fetch appropriate new data in response to an incoming remote notification. You should call the fetchCompletionHandler as soon as you're finished performing that operation, so the system can accurately estimate its power and data cost.
 
 This method will be invoked even if the application was launched or resumed because of the remote notification. The respective delegate methods will be invoked first. Note that this behavior is in contrast to application:didReceiveRemoteNotification:, which is not called in those cases, and which will not be invoked if this method is implemented. !*/
- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo fetchCompletionHandler:(void (^)(UIBackgroundFetchResult result))completionHandler API_AVAILABLE(ios(7.0));

/// Applications with the "fetch" background mode may be given opportunities to fetch updated content in the background or when it is convenient for the system. This method will be called in these situations. You should call the fetchCompletionHandler as soon as you're finished performing that operation, so the system can accurately estimate its power and data cost.
- (void)application:(UIApplication *)application performFetchWithCompletionHandler:(void (^)(UIBackgroundFetchResult result))completionHandler NS_SWIFT_DISABLE_ASYNC API_DEPRECATED("Use a BGAppRefreshTask in the BackgroundTasks framework instead", ios(7.0, 13.0), tvos(11.0, 13.0)) API_UNAVAILABLE(visionos, watchos);

/// Called when the user activates your application by selecting a shortcut on the home screen, except when `application(_:willFinishLaunchingWithOptions:)`
/// or `application(_:didFinishLaunchingWithOptions:)` returns `false`.
- (void)application:(UIApplication *)application performActionForShortcutItem:(UIApplicationShortcutItem *)shortcutItem completionHandler:(void(^)(BOOL succeeded))completionHandler API_DEPRECATED("Use UIScene lifecycle and windowScene(_:performActionFor:completionHandler:) from UIWindowSceneDelegate instead.", ios(9.0, 26.0), visionos(1.0, 26.0)) API_UNAVAILABLE(tvos, watchos);

// Applications using an NSURLSession with a background configuration may be launched or resumed in the background in order to handle the
// completion of tasks in that session, or to handle authentication. This method will be called with the identifier of the session needing
// attention. Once a session has been created from a configuration object with that identifier, the session's delegate will begin receiving
// callbacks. If such a session has already been created (if the app is being resumed, for instance), then the delegate will start receiving
// callbacks without any action by the application. You should call the completionHandler as soon as you're finished handling the callbacks.
- (void)application:(UIApplication *)application handleEventsForBackgroundURLSession:(NSString *)identifier completionHandler:(void (^)(void))completionHandler API_AVAILABLE(ios(7.0));

- (void)application:(UIApplication *)application handleWatchKitExtensionRequest:(nullable NSDictionary *)userInfo reply:(void(^)(NSDictionary * __nullable replyInfo))reply API_AVAILABLE(ios(8.2));

- (void)applicationShouldRequestHealthAuthorization:(UIApplication *)application API_AVAILABLE(ios(9.0));

- (nullable id)application:(UIApplication *)application handlerForIntent:(INIntent *)intent API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos);

- (void)application:(UIApplication *)application handleIntent:(INIntent *)intent completionHandler:(void(^)(INIntentResponse *intentResponse))completionHandler API_DEPRECATED("Use application:handlerForIntent: instead", ios(11.0, 14.0), visionos(1.0, 1.0)) API_UNAVAILABLE(watchos);

- (void)applicationProtectedDataWillBecomeUnavailable:(UIApplication *)application API_AVAILABLE(ios(4.0));
- (void)applicationProtectedDataDidBecomeAvailable:(UIApplication *)application    API_AVAILABLE(ios(4.0));

@property (nullable, nonatomic, strong) UIWindow *window API_AVAILABLE(ios(5.0));

- (UIInterfaceOrientationMask)application:(UIApplication *)application supportedInterfaceOrientationsForWindow:(nullable UIWindow *)window  API_AVAILABLE(ios(6.0)) API_UNAVAILABLE(tvos);

typedef NSString * UIApplicationExtensionPointIdentifier NS_TYPED_ENUM API_UNAVAILABLE(watchos);

// Applications may reject specific types of extensions based on the extension point identifier.
// Constants representing common extension point identifiers are provided further down.
// If unimplemented, the default behavior is to allow the extension point identifier.
- (BOOL)application:(UIApplication *)application shouldAllowExtensionPointIdentifier:(UIApplicationExtensionPointIdentifier)extensionPointIdentifier API_AVAILABLE(ios(8.0));

#pragma mark -- State Restoration protocol adopted by UIApplication delegate --

- (nullable UIViewController *) application:(UIApplication *)application viewControllerWithRestorationIdentifierPath:(NSArray<NSString *> *)identifierComponents coder:(NSCoder *)coder API_AVAILABLE(ios(6.0));
- (BOOL)application:(UIApplication *)application shouldSaveSecureApplicationState:(NSCoder *)coder API_AVAILABLE(ios(13.2)) API_UNAVAILABLE(watchos);
- (BOOL)application:(UIApplication *)application shouldRestoreSecureApplicationState:(NSCoder *)coder API_AVAILABLE(ios(13.2)) API_UNAVAILABLE(watchos);
- (void)application:(UIApplication *)application willEncodeRestorableStateWithCoder:(NSCoder *)coder API_AVAILABLE(ios(6.0));
- (void)application:(UIApplication *)application didDecodeRestorableStateWithCoder:(NSCoder *)coder API_AVAILABLE(ios(6.0));

// Deprecated State Restoration opt-in methods:
- (BOOL)application:(UIApplication *)application shouldSaveApplicationState:(NSCoder *)coder API_DEPRECATED("Use application:shouldSaveSecureApplicationState: instead", ios(6.0, 13.2)) API_UNAVAILABLE(visionos, watchos);
- (BOOL)application:(UIApplication *)application shouldRestoreApplicationState:(NSCoder *)coder API_DEPRECATED("Use application:shouldRestoreSecureApplicationState: instead", ios(6.0, 13.2)) API_UNAVAILABLE(visionos, watchos);

#pragma mark -- User Activity Continuation protocol adopted by UIApplication delegate --

/// Called on the main thread as soon as the user indicates they want to continue an activity in your application. The ``NSUserActivity`` object may not be available
/// instantly, so use this as an opportunity to show the user that an activity will be continued shortly.
///
/// For each `application(_:willContinueUserActivityWithType:)` invocation, you are guaranteed to get exactly one invocation of `application(_:continue:restorationHandler:)`
/// on success, or `application(_:didFailToContinueUserActivityWithType:error:)` if an error was encountered.
- (BOOL)application:(UIApplication *)application willContinueUserActivityWithType:(NSString *)userActivityType API_DEPRECATED("Use UIScene lifecycle and scene(_:willContinueUserActivityWithType:) from UISceneDelegate instead.", ios(8.0, 26.0), tvos(9.0, 26.0), visionos(1.0, 26.0)) API_UNAVAILABLE(watchos);

/// Called on the main thread after the ``NSUserActivity`` object is available. Use the data you stored in the ``NSUserActivity`` object to re-create what the user
/// was doing. You can create/fetch any restorable objects associated with the user activity, and pass them to the `restorationHandler`. They will then have the
/// `UIResponder` `restoreUserActivityState:` method invoked with the user activity. Invoking the `restorationHandler` is optional. It may be copied and
/// invoked later, and it will bounce to the main thread to complete its work and call `restoreUserActivityState` on all objects.
- (BOOL)application:(UIApplication *)application continueUserActivity:(NSUserActivity *)userActivity restorationHandler:(void(^)(NSArray<id<UIUserActivityRestoring>> * __nullable restorableObjects))restorationHandler API_DEPRECATED("Use UIScene lifecycle and scene(_:continue:) from UISceneDelegate instead.", ios(8.0, 26.0), tvos(9.0, 26.0), visionos(1.0, 26.0)) API_UNAVAILABLE(watchos);

/// If the user activity cannot be fetched after `application(_:willContinueUserActivityWithType:)` is called, this will be called on the main thread when implemented.
- (void)application:(UIApplication *)application didFailToContinueUserActivityWithType:(NSString *)userActivityType error:(NSError *)error API_DEPRECATED("Use UIScene lifecycle and scene(_:didFailToContinueUserActivityWithType:error:) from UISceneDelegate instead.", ios(8.0, 26.0), tvos(9.0, 26.0), visionos(1.0, 26.0)) API_UNAVAILABLE(watchos);

/// This is called on the main thread when a user activity managed by UIKit has been updated. You can use this as a last chance to add additional data to the userActivity.
- (void)application:(UIApplication *)application didUpdateUserActivity:(NSUserActivity *)userActivity API_DEPRECATED("Use UIScene lifecycle and scene(_:didUpdate) from UISceneDelegate instead.", ios(8.0, 26.0), tvos(9.0, 26.0), visionos(1.0, 26.0)) API_UNAVAILABLE(watchos);

#pragma mark -- CloudKit Sharing Invitation Handling --
/// This will be called on the main thread after the user indicates they want to accept a CloudKit sharing invitation in your application.
/// You should use the `CKShareMetadata` object's `shareURL` and `containerIdentifier` to schedule a `CKAcceptSharesOperation`, then start using
/// the resulting `CKShare` and its associated record(s), which will appear in the `CKContainer`'s shared database in a zone matching that of the record's owner.
- (void)application:(UIApplication *)application userDidAcceptCloudKitShareWithMetadata:(CKShareMetadata *)cloudKitShareMetadata API_DEPRECATED("Use UIScene lifecycle and windowScene(_:userDidAcceptCloudKitShareWith:) from UIWindowSceneDelegate instead.", ios(10.0, 26.0), tvos(10.0, 26.0), visionos(1.0, 26.0)) API_UNAVAILABLE(watchos);

#pragma mark -- UIScene Support --
// Called when the UIKit is about to create & vend a new UIScene instance to the application.
// The application delegate may modify the provided UISceneConfiguration within this method.
// If the UISceneConfiguration instance returned from this method does not have a systemType which matches the connectingSession's, UIKit will assert
- (UISceneConfiguration *)application:(UIApplication *)application configurationForConnectingSceneSession:(UISceneSession *)connectingSceneSession options:(UISceneConnectionOptions *)options API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

// Called when the system, due to a user interaction or a request from the application itself, removes one or more representation from the -[UIApplication openSessions] set
// If sessions are discarded while the application is not running, this method is called shortly after the application's next launch.
- (void)application:(UIApplication *)application didDiscardSceneSessions:(NSSet<UISceneSession *> *)sceneSessions API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

#pragma mark -- UIKeyCommand Support --
// UIKeyCommand system-wide keyboard shortcut localization support
// This method will be called during application launch.
// Return NO if the receiving delegate object wishes to opt-out of system-wide keyboard shortcut localization for all application-supplied UIKeyCommands. Return YES by default for apps linked against 15.0 and later SDK.
- (BOOL)applicationShouldAutomaticallyLocalizeKeyCommands:(UIApplication *)application API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos);

@end

@interface UIApplication(UIApplicationDeprecated)

@property(nonatomic,getter=isProximitySensingEnabled) BOOL proximitySensingEnabled API_DEPRECATED("", ios(2.0, 3.0)) API_UNAVAILABLE(visionos, tvos, watchos); // default is NO. see UIDevice for replacement
- (void)setStatusBarHidden:(BOOL)hidden animated:(BOOL)animated API_DEPRECATED("Use -[UIViewController prefersStatusBarHidden]", ios(2.0, 3.2)) API_UNAVAILABLE(visionos, tvos, watchos);

// Explicit setting of the status bar orientation is more limited in iOS 6.0 and later.
@property(readwrite, nonatomic) UIInterfaceOrientation statusBarOrientation API_DEPRECATED("Explicit setting of the status bar orientation is more limited in iOS 6.0 and later", ios(2.0, 9.0)) API_UNAVAILABLE(visionos, tvos, watchos);
- (void)setStatusBarOrientation:(UIInterfaceOrientation)interfaceOrientation animated:(BOOL)animated API_DEPRECATED("Explicit setting of the status bar orientation is more limited in iOS 6.0 and later", ios(2.0, 9.0)) API_UNAVAILABLE(visionos, tvos, watchos);

// Setting the statusBarStyle does nothing if your application is using the default UIViewController-based status bar system.
@property(readwrite, nonatomic) UIStatusBarStyle statusBarStyle API_DEPRECATED("Use -[UIViewController preferredStatusBarStyle]", ios(2.0, 9.0)) API_UNAVAILABLE(visionos, tvos, watchos);
- (void)setStatusBarStyle:(UIStatusBarStyle)statusBarStyle animated:(BOOL)animated API_DEPRECATED("Use -[UIViewController preferredStatusBarStyle]", ios(2.0, 9.0)) API_UNAVAILABLE(visionos, tvos, watchos);

// Setting statusBarHidden does nothing if your application is using the default UIViewController-based status bar system.
@property(readwrite, nonatomic,getter=isStatusBarHidden) BOOL statusBarHidden API_DEPRECATED("Use -[UIViewController prefersStatusBarHidden]", ios(2.0, 9.0)) API_UNAVAILABLE(visionos, tvos, watchos);
- (void)setStatusBarHidden:(BOOL)hidden withAnimation:(UIStatusBarAnimation)animation API_DEPRECATED("Use -[UIViewController prefersStatusBarHidden]", ios(3.2, 9.0)) API_UNAVAILABLE(visionos, tvos, watchos);

- (BOOL)setKeepAliveTimeout:(NSTimeInterval)timeout handler:(void(^ __nullable)(void))keepAliveHandler API_DEPRECATED("Please use PushKit for VoIP applications instead of calling this method", ios(4.0, 9.0)) API_UNAVAILABLE(visionos, tvos, watchos);
- (void)clearKeepAliveTimeout API_DEPRECATED("Please use PushKit for VoIP applications instead of calling this method", ios(4.0, 9.0)) API_UNAVAILABLE(visionos, tvos, watchos);

@end

// If nil is specified for principalClassName, the value for NSPrincipalClass from the Info.plist is used. If there is no
// NSPrincipalClass key specified, the UIApplication class is used. The delegate class will be instantiated using init.
UIKIT_EXTERN int UIApplicationMain(int argc, char * _Nullable argv[_Nonnull], NSString * _Nullable principalClassName, NSString * _Nullable delegateClassName) API_UNAVAILABLE(watchos);

UIKIT_EXTERN NSRunLoopMode const UITrackingRunLoopMode API_UNAVAILABLE(watchos);

// These notifications are sent out after the equivalent delegate message is called
UIKIT_EXTERN NSNotificationName const UIApplicationDidEnterBackgroundNotification       API_AVAILABLE(ios(4.0)) API_UNAVAILABLE(watchos) NS_SWIFT_NONISOLATED;
UIKIT_EXTERN NSNotificationName const UIApplicationWillEnterForegroundNotification      API_AVAILABLE(ios(4.0)) API_UNAVAILABLE(watchos) NS_SWIFT_NONISOLATED;
UIKIT_EXTERN NSNotificationName const UIApplicationDidFinishLaunchingNotification API_UNAVAILABLE(watchos) NS_SWIFT_NONISOLATED;
UIKIT_EXTERN NSNotificationName const UIApplicationDidBecomeActiveNotification API_UNAVAILABLE(watchos) NS_SWIFT_NONISOLATED;
UIKIT_EXTERN NSNotificationName const UIApplicationWillResignActiveNotification API_UNAVAILABLE(watchos) NS_SWIFT_NONISOLATED;
UIKIT_EXTERN NSNotificationName const UIApplicationDidReceiveMemoryWarningNotification API_UNAVAILABLE(watchos) NS_SWIFT_NONISOLATED;
UIKIT_EXTERN NSNotificationName const UIApplicationWillTerminateNotification API_UNAVAILABLE(watchos) NS_SWIFT_NONISOLATED;
UIKIT_EXTERN NSNotificationName const UIApplicationSignificantTimeChangeNotification API_UNAVAILABLE(watchos) NS_SWIFT_NONISOLATED;
UIKIT_EXTERN NSNotificationName const UIApplicationWillChangeStatusBarOrientationNotification API_DEPRECATED("Use viewWillTransitionToSize:withTransitionCoordinator: instead.", ios(2.0, 13.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos) NS_SWIFT_NONISOLATED; // userInfo contains NSNumber with new orientation
UIKIT_EXTERN NSNotificationName const UIApplicationDidChangeStatusBarOrientationNotification API_DEPRECATED("Use viewWillTransitionToSize:withTransitionCoordinator: instead.", ios(2.0, 13.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos) NS_SWIFT_NONISOLATED;  // userInfo contains NSNumber with old orientation
UIKIT_EXTERN NSString *const UIApplicationStatusBarOrientationUserInfoKey API_DEPRECATED("Use viewWillTransitionToSize:withTransitionCoordinator: instead.", ios(2.0, 13.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos) NS_SWIFT_NONISOLATED;            // userInfo dictionary key for status bar orientation
UIKIT_EXTERN NSNotificationName const UIApplicationWillChangeStatusBarFrameNotification API_DEPRECATED("Use viewWillTransitionToSize:withTransitionCoordinator: instead.", ios(2.0, 13.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos) NS_SWIFT_NONISOLATED;       // userInfo contains NSValue with new frame
UIKIT_EXTERN NSNotificationName const UIApplicationDidChangeStatusBarFrameNotification API_DEPRECATED("Use viewWillTransitionToSize:withTransitionCoordinator: instead.", ios(2.0, 13.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos) NS_SWIFT_NONISOLATED;        // userInfo contains NSValue with old frame
UIKIT_EXTERN NSString *const UIApplicationStatusBarFrameUserInfoKey API_DEPRECATED("Use viewWillTransitionToSize:withTransitionCoordinator: instead.", ios(2.0, 13.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos) NS_SWIFT_NONISOLATED;                  // userInfo dictionary key for status bar frame
UIKIT_EXTERN NSNotificationName const UIApplicationBackgroundRefreshStatusDidChangeNotification API_AVAILABLE(ios(7.0), tvos(11.0)) API_UNAVAILABLE(watchos) NS_SWIFT_NONISOLATED;

UIKIT_EXTERN NSNotificationName const UIApplicationProtectedDataWillBecomeUnavailable    API_AVAILABLE(ios(4.0)) API_UNAVAILABLE(watchos) NS_SWIFT_NONISOLATED;
UIKIT_EXTERN NSNotificationName const UIApplicationProtectedDataDidBecomeAvailable       API_AVAILABLE(ios(4.0)) API_UNAVAILABLE(watchos) NS_SWIFT_NONISOLATED;

/// UserInfo contains a ``NSURL`` with launch URL to open
UIKIT_EXTERN UIApplicationLaunchOptionsKey const UIApplicationLaunchOptionsURLKey NS_SWIFT_NAME(url) API_DEPRECATED("Use UIScene lifecycle and UIScene.ConnectionOptions.URLContexts instead.", ios(3.0, 26.0), tvos(9.0, 26.0), visionos(1.0, 26.0)) API_UNAVAILABLE(watchos);

/// UserInfo contains a ``NSString`` with the bundle ID of the originating application; non-nil if the originating application and this application share the same team identifier
UIKIT_EXTERN UIApplicationLaunchOptionsKey const UIApplicationLaunchOptionsSourceApplicationKey NS_SWIFT_NAME(sourceApplication) API_DEPRECATED("Use UIScene lifecycle and UIScene.ConnectionOptions.sourceApplication instead.", ios(3.0, 26.0), tvos(9.0, 26.0), visionos(1.0, 26.0)) API_UNAVAILABLE(watchos);

/// UserInfo contains a ``NSDictionary`` notification payload with property-list objects plus ``NSNull``
UIKIT_EXTERN UIApplicationLaunchOptionsKey const UIApplicationLaunchOptionsRemoteNotificationKey NS_SWIFT_NAME(remoteNotification) API_DEPRECATED("Continue using UIApplicationDelegate's application(_:didReceiveRemoteNotification:fetchCompletionHandler:) to process silent remote notifications after scene connection.", ios(3.0, 26.0), visionos(1.0, 26.0)) API_UNAVAILABLE(tvos, watchos);

/// UserInfo contains a ``UILocalNotification``
UIKIT_EXTERN UIApplicationLaunchOptionsKey const UIApplicationLaunchOptionsLocalNotificationKey NS_SWIFT_NAME(localNotification) API_DEPRECATED("Use UserNotifications Framework's -[UNUserNotificationCenterDelegate didReceiveNotificationResponse:withCompletionHandler:]", ios(4.0, 10.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos) ;

/// UserInfo contains a property list annotation object
UIKIT_EXTERN UIApplicationLaunchOptionsKey const UIApplicationLaunchOptionsAnnotationKey NS_SWIFT_NAME(annotation) API_DEPRECATED("This dictionary key is no longer used.", ios(3.2, 16.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// The app was launched in response to a CoreLocation event
UIKIT_EXTERN UIApplicationLaunchOptionsKey const UIApplicationLaunchOptionsLocationKey NS_SWIFT_NAME(location) API_DEPRECATED("Adopt CLLocationUpdate or CLMonitor, or use CLLocationManagerDelegate from CoreLocation to handle expected location events after scene connection.", ios(4.0, 26.0), tvos(9.0, 26.0), visionos(1.0, 26.0)) API_UNAVAILABLE(watchos);

/// UserInfo contains an ``NSArray`` of ``NKAssetDownload`` identifiers
UIKIT_EXTERN UIApplicationLaunchOptionsKey const UIApplicationLaunchOptionsNewsstandDownloadsKey NS_SWIFT_NAME(newsstandDownloads) API_DEPRECATED("This dictionary key is no longer used.", ios(5.0, 26.0), visionos(1.0, 26.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

/// UserInfo contains an ``NSArray`` of ``CBCentralManager`` restore identifiers
UIKIT_EXTERN UIApplicationLaunchOptionsKey const UIApplicationLaunchOptionsBluetoothCentralsKey NS_SWIFT_NAME(bluetoothCentrals) API_DEPRECATED("Store restoration identifiers and reinstantiate central managers with those identifiers on app launch to resume previous functionality.", ios(7.0, 26.0), tvos(9.0, 26.0), visionos(1.0, 26.0)) API_UNAVAILABLE(watchos);

/// UserInfo contains an ``NSArray`` of ``CBPeripheralManager`` restore identifiers
UIKIT_EXTERN UIApplicationLaunchOptionsKey const UIApplicationLaunchOptionsBluetoothPeripheralsKey NS_SWIFT_NAME(bluetoothPeripherals) API_DEPRECATED("Store restoration identifiers and reinstantiate peripheral managers with those identifiers on app launch to resume previous functionality.", ios(7.0, 26.0), tvos(9.0, 26.0), visionos(1.0, 26.0)) API_UNAVAILABLE(watchos);

/// UserInfo contains the ``UIApplicationShortcutItem`` used to launch the app
UIKIT_EXTERN UIApplicationLaunchOptionsKey const UIApplicationLaunchOptionsShortcutItemKey NS_SWIFT_NAME(shortcutItem) API_DEPRECATED("Use UIScene lifecycle and UIScene.ConnectionOptions.shortcutItem instead.", ios(3.0, 26.0), visionos(1.0, 26.0)) API_UNAVAILABLE(tvos, watchos);

/// UserInfo contains a ``UIEventAttribution`` to go along with a URL open on launch
UIKIT_EXTERN UIApplicationLaunchOptionsKey const UIApplicationLaunchOptionsEventAttributionKey NS_SWIFT_NAME(eventAttribution) API_DEPRECATED("Use UIScene lifecycle and UIScene.ConnectionOptions.eventAttribution instead.", ios(14.5, 26.0), visionos(1.0, 26.0)) API_UNAVAILABLE(watchos, tvos);

/// Key in options dictionary passed to `application(_:willFinishLaunchingWithOptions:)` and `application(_:didFinishLaunchingWithOptions:)`
/// and info for `UIApplication.didFinishLaunchingNotification`. Sub-Dictionary present in launch options when user activity is present.
UIKIT_EXTERN UIApplicationLaunchOptionsKey const UIApplicationLaunchOptionsUserActivityDictionaryKey NS_SWIFT_NAME(userActivityDictionary) API_DEPRECATED("Use UIScene lifecycle and UIScene.ConnectionOptions.userActivities instead.", ios(8.0, 26.0), tvos(9.0, 26.0), visionos(1.0, 26.0)) API_UNAVAILABLE(watchos);

/// Key in user activity dictionary for the activity type
UIKIT_EXTERN UIApplicationLaunchOptionsKey const UIApplicationLaunchOptionsUserActivityTypeKey NS_SWIFT_NAME(userActivityType) API_DEPRECATED("Use UIScene lifecycle and UIScene.ConnectionOptions.handoffUserActivityType instead.", ios(8.0, 26.0), tvos(9.0, 26.0), visionos(1.0, 26.0)) API_UNAVAILABLE(watchos);

/// The presence of this key indicates that the app was launched in order to handle a CloudKit sharing invitation. The value of this key is a ``CKShareMetadata`` object.
UIKIT_EXTERN UIApplicationLaunchOptionsKey const UIApplicationLaunchOptionsCloudKitShareMetadataKey NS_SWIFT_NAME(cloudKitShareMetadata) API_DEPRECATED("Use UIScene lifecycle and UIScene.ConnectionOptions.cloudKitShareMetadata instead.", ios(10.0, 26.0), visionos(1.0, 26.0)) API_UNAVAILABLE(tvos, watchos);

UIKIT_EXTERN NSString *const UIApplicationOpenSettingsURLString API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(watchos) NS_SWIFT_NONISOLATED;

/// The URL string you use to deep link to settings for default app selection in the Settings app.
UIKIT_EXTERN NSString *const UIApplicationOpenDefaultApplicationsSettingsURLString API_AVAILABLE(ios(18.3)) API_UNAVAILABLE(watchos) NS_SWIFT_NONISOLATED;

#if __swift__
UIKIT_EXTERN NSString *const UIApplicationOpenNotificationSettingsURLString API_DEPRECATED_WITH_REPLACEMENT("UIApplication.openNotificationSettingsURLString", ios(15.4, 16.0), visionos(1.0, 1.0)) NS_SWIFT_NONISOLATED;
#else
UIKIT_EXTERN NSString *const UIApplicationOpenNotificationSettingsURLString API_AVAILABLE(ios(15.4)) API_UNAVAILABLE(watchos) NS_SWIFT_NONISOLATED;
#endif

/// An options key for `application(_:open:options:)`. The value is an ``NSString`` containing the bundle ID of the originating application; non-nil if the originating
/// application and this application share the same team identifier.
UIKIT_EXTERN UIApplicationOpenURLOptionsKey const UIApplicationOpenURLOptionsSourceApplicationKey NS_SWIFT_NAME(sourceApplication) API_DEPRECATED("Use UIScene lifecycle and UISceneOpenURLOptions.sourceApplication from a UIOpenURLContext in UIScene.ConnectionOptions.URLContexts instead.", ios(9.0, 26.0), tvos(9.0, 26.0), visionos(1.0, 26.0)) API_UNAVAILABLE(watchos);

/// An options key for `application(_:open:options:)`. The value is a property-list typed object corresponding to what the originating application passed in
/// `UIDocumentInteractionController`'s annotation property.
UIKIT_EXTERN UIApplicationOpenURLOptionsKey const UIApplicationOpenURLOptionsAnnotationKey NS_SWIFT_NAME(annotation) API_DEPRECATED("Use UIScene lifecycle and UISceneOpenURLOptions.annotation from a UIOpenURLContext in UIScene.ConnectionOptions.URLContexts instead.", ios(9.0, 26.0), tvos(9.0, 26.0), visionos(1.0, 26.0)) API_UNAVAILABLE(watchos) ;

/// An options key for `application(_:open:options:)`. The value is a bool `NSNumber`. Copy the file before use if this value is NO, or is not present.
UIKIT_EXTERN UIApplicationOpenURLOptionsKey const UIApplicationOpenURLOptionsOpenInPlaceKey NS_SWIFT_NAME(openInPlace) API_DEPRECATED("Use UIScene lifecycle and UISceneOpenURLOptions.openInPlace from a UIOpenURLContext in UIScene.ConnectionOptions.URLContexts instead.", ios(9.0, 26.0), tvos(9.0, 26.0), visionos(1.0, 26.0)) API_UNAVAILABLE(watchos);

/// An options key for `application(_:open:options:)`. The value is a `UIEventAttribution` to go along with the URL to open.
UIKIT_EXTERN UIApplicationOpenURLOptionsKey const UIApplicationOpenURLOptionsEventAttributionKey NS_SWIFT_NAME(eventAttribution) API_DEPRECATED("Use UIScene lifecycle and UISceneOpenURLOptions.eventAttribution from a UIOpenURLContext in UIScene.ConnectionOptions.URLContexts instead.", ios(14.5, 26.0), visionos(1.0, 26.0)) API_UNAVAILABLE(watchos, tvos);

// This notification is posted after the user takes a screenshot (for example by pressing both the home and lock screen buttons)
UIKIT_EXTERN NSNotificationName const UIApplicationUserDidTakeScreenshotNotification API_AVAILABLE(ios(7.0)) API_UNAVAILABLE(watchos) NS_SWIFT_NONISOLATED;

// Extension point identifier constants
UIKIT_EXTERN UIApplicationExtensionPointIdentifier const UIApplicationKeyboardExtensionPointIdentifier API_UNAVAILABLE(watchos) NS_SWIFT_NAME(keyboard) API_AVAILABLE(ios(8.0));

#pragma mark -- openURL options --

// Option for openURL:options:CompletionHandler: only open URL if it is a valid universal link with an application configured to open it
// If there is no application configured, or the user disabled using it to open the link, completion handler called with NO
UIKIT_EXTERN UIApplicationOpenExternalURLOptionsKey const UIApplicationOpenURLOptionUniversalLinksOnly API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos);

// Option for openURL:options:CompletionHandler: to provide an event attribution to go along with the openURL call.
UIKIT_EXTERN UIApplicationOpenExternalURLOptionsKey const UIApplicationOpenExternalURLOptionsEventAttributionKey NS_SWIFT_NAME(eventAttribution) API_AVAILABLE(ios(14.5)) API_UNAVAILABLE(watchos, tvos); // value is a UIEventAttribution

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIApplication.h>
#endif
