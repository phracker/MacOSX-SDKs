//
//  UNUserNotificationCenter.h
//  UserNotifications
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class UNNotification;
@class UNNotificationAttachment;
@class UNNotificationCategory;
@class UNNotificationContent;
@class UNNotificationRequest;
@class UNNotificationResponse;
@class UNNotificationSettings;

@protocol UNUserNotificationCenterDelegate;

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSUInteger, UNAuthorizationOptions) {
    UNAuthorizationOptionBadge   = (1 << 0),
    UNAuthorizationOptionSound   = (1 << 1),
    UNAuthorizationOptionAlert   = (1 << 2),
    UNAuthorizationOptionCarPlay = (1 << 3),
    UNAuthorizationOptionCriticalAlert __API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0)) = (1 << 4),
    UNAuthorizationOptionProvidesAppNotificationSettings __API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0)) = (1 << 5),
    UNAuthorizationOptionProvisional __API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0)) = (1 << 6),
    UNAuthorizationOptionAnnouncement __API_AVAILABLE(ios(13.0), watchos(6.0)) __API_UNAVAILABLE(macos, tvos) = (1 << 7),
} __API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0), tvos(10.0));

static const UNAuthorizationOptions UNAuthorizationOptionNone NS_SWIFT_UNAVAILABLE("Use [] instead.") __API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0), tvos(10.0)) = 0;

// UNNotificationRequests can be scheduled using UNUserNotificationCenter. They can also be sent to the device from a server using Apple Push Notification Service. If the application is authorized then the UNNotificationRequest will be used to create a UNNotification and it will be used to notify the user. If the user acts on the UNNotification then a UNNotificationResponse will be sent to the application.

__API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0), tvos(10.0))
@interface UNUserNotificationCenter : NSObject

// The delegate can only be set from an application
@property (NS_NONATOMIC_IOSONLY, nullable, weak) id <UNUserNotificationCenterDelegate> delegate;

// Returns YES if the current device supports content extensions
@property (NS_NONATOMIC_IOSONLY, readonly) BOOL supportsContentExtensions;

// The UNUserNotificationCenter for the current application
+ (UNUserNotificationCenter *)currentNotificationCenter;

- (instancetype)init NS_UNAVAILABLE;

// User authorization is required for applications to notify the user using UNUserNotificationCenter via both local and remote notifications.
- (void)requestAuthorizationWithOptions:(UNAuthorizationOptions)options completionHandler:(void (^)(BOOL granted, NSError *__nullable error))completionHandler;

// Notification categories can be used to choose which actions will be displayed on which notifications.
- (void)setNotificationCategories:(NSSet<UNNotificationCategory *> *)categories __API_UNAVAILABLE(tvos);
- (void)getNotificationCategoriesWithCompletionHandler:(void(^)(NSSet<UNNotificationCategory *> *categories))completionHandler __API_UNAVAILABLE(tvos);

// The application's user notification settings
- (void)getNotificationSettingsWithCompletionHandler:(void(^)(UNNotificationSettings *settings))completionHandler;

// Notification requests can be scheduled to notify the user via time and location. See UNNotificationTrigger for more information. Calling -addNotificationRequest: will replace an existing notification request with the same identifier. A notification request with the identifier as an existing delivered notifications will alert for the new notification request and replace the existing delivered notification when it is triggered. The number of pending notification requests that may be scheduled by an application at any one time is limited by the system.
- (void)addNotificationRequest:(UNNotificationRequest *)request withCompletionHandler:(nullable void(^)(NSError *__nullable error))completionHandler;

// Notification requests that are waiting for their trigger to fire
- (void)getPendingNotificationRequestsWithCompletionHandler:(void(^)(NSArray<UNNotificationRequest *> *requests))completionHandler;
- (void)removePendingNotificationRequestsWithIdentifiers:(NSArray<NSString *> *)identifiers;
- (void)removeAllPendingNotificationRequests;

// Notifications that have been delivered and remain in Notification Center. Notifications triggered by location cannot be retrieved, but can be removed.
- (void)getDeliveredNotificationsWithCompletionHandler:(void(^)(NSArray<UNNotification *> *notifications))completionHandler __API_UNAVAILABLE(tvos);
- (void)removeDeliveredNotificationsWithIdentifiers:(NSArray<NSString *> *)identifiers __API_UNAVAILABLE(tvos);
- (void)removeAllDeliveredNotifications __API_UNAVAILABLE(tvos);

@end

typedef NS_OPTIONS(NSUInteger, UNNotificationPresentationOptions) {
    UNNotificationPresentationOptionBadge   = (1 << 0),
    UNNotificationPresentationOptionSound   = (1 << 1),
    UNNotificationPresentationOptionAlert   = (1 << 2),
} __API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0), tvos(10.0));

static const UNNotificationPresentationOptions UNNotificationPresentationOptionNone NS_SWIFT_UNAVAILABLE("Use [] instead.") __API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0), tvos(10.0)) = 0;

__API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0), tvos(10.0))
@protocol UNUserNotificationCenterDelegate <NSObject>

@optional

// The method will be called on the delegate only if the application is in the foreground. If the method is not implemented or the handler is not called in a timely manner then the notification will not be presented. The application can choose to have the notification presented as a sound, badge, alert and/or in the notification list. This decision should be based on whether the information in the notification is otherwise visible to the user.
- (void)userNotificationCenter:(UNUserNotificationCenter *)center willPresentNotification:(UNNotification *)notification withCompletionHandler:(void (^)(UNNotificationPresentationOptions options))completionHandler __API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0), tvos(10.0));

// The method will be called on the delegate when the user responded to the notification by opening the application, dismissing the notification or choosing a UNNotificationAction. The delegate must be set before the application returns from application:didFinishLaunchingWithOptions:.
- (void)userNotificationCenter:(UNUserNotificationCenter *)center didReceiveNotificationResponse:(UNNotificationResponse *)response withCompletionHandler:(void(^)(void))completionHandler __API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0)) __API_UNAVAILABLE(tvos);

// The method will be called on the delegate when the application is launched in response to the user's request to view in-app notification settings. Add UNAuthorizationOptionProvidesAppNotificationSettings as an option in requestAuthorizationWithOptions:completionHandler: to add a button to inline notification settings view and the notification settings view in Settings. The notification will be nil when opened from Settings.
- (void)userNotificationCenter:(UNUserNotificationCenter *)center openSettingsForNotification:(nullable UNNotification *)notification __API_AVAILABLE(macos(10.14), ios(12.0)) __API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END
