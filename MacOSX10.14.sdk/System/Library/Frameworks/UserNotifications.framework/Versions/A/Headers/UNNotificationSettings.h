//
//  UNNotificationSettings.h
//  UserNotifications
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, UNAuthorizationStatus) {
    // The user has not yet made a choice regarding whether the application may post user notifications.
    UNAuthorizationStatusNotDetermined = 0,
    
    // The application is not authorized to post user notifications.
    UNAuthorizationStatusDenied,
    
    // The application is authorized to post user notifications.
    UNAuthorizationStatusAuthorized,
    
    // The application is authorized to post non-interruptive user notifications.
    UNAuthorizationStatusProvisional __IOS_AVAILABLE(12.0) __TVOS_AVAILABLE(12.0) __WATCHOS_AVAILABLE(5.0) __OSX_AVAILABLE(10.14)
} __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0) __OSX_AVAILABLE(10.14);

typedef NS_ENUM(NSInteger, UNShowPreviewsSetting) {
    // Notification previews are always shown.
    UNShowPreviewsSettingAlways,
    
    // Notifications previews are only shown when authenticated.
    UNShowPreviewsSettingWhenAuthenticated,
    
    // Notifications previews are never shown.
    UNShowPreviewsSettingNever
} __IOS_AVAILABLE(11.0) __OSX_AVAILABLE(10.14) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;

typedef NS_ENUM(NSInteger, UNNotificationSetting) {
    // The application does not support this notification type
    UNNotificationSettingNotSupported  = 0,
    
    // The notification setting is turned off.
    UNNotificationSettingDisabled,
    
    // The notification setting is turned on.
    UNNotificationSettingEnabled,
} __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0) __OSX_AVAILABLE(10.14);

typedef NS_ENUM(NSInteger, UNAlertStyle) {
    UNAlertStyleNone = 0,
    UNAlertStyleBanner,
    UNAlertStyleAlert,
} __IOS_AVAILABLE(10.0) __OSX_AVAILABLE(10.14) __TVOS_PROHIBITED __WATCHOS_PROHIBITED;

__IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0) __OSX_AVAILABLE(10.14)
@interface UNNotificationSettings : NSObject <NSCopying, NSSecureCoding>

@property (NS_NONATOMIC_IOSONLY, readonly) UNAuthorizationStatus authorizationStatus;

@property (NS_NONATOMIC_IOSONLY, readonly) UNNotificationSetting soundSetting __TVOS_PROHIBITED;
@property (NS_NONATOMIC_IOSONLY, readonly) UNNotificationSetting badgeSetting __WATCHOS_PROHIBITED;
@property (NS_NONATOMIC_IOSONLY, readonly) UNNotificationSetting alertSetting __TVOS_PROHIBITED;

@property (NS_NONATOMIC_IOSONLY, readonly) UNNotificationSetting notificationCenterSetting __TVOS_PROHIBITED;
@property (NS_NONATOMIC_IOSONLY, readonly) UNNotificationSetting lockScreenSetting __TVOS_PROHIBITED __WATCHOS_PROHIBITED;
@property (NS_NONATOMIC_IOSONLY, readonly) UNNotificationSetting carPlaySetting __API_UNAVAILABLE(macos, tvos, watchos);

@property (NS_NONATOMIC_IOSONLY, readonly) UNAlertStyle alertStyle __TVOS_PROHIBITED __WATCHOS_PROHIBITED;

@property (NS_NONATOMIC_IOSONLY, readonly) UNShowPreviewsSetting showPreviewsSetting  __IOS_AVAILABLE(11.0) __OSX_AVAILABLE(10.14) __TVOS_PROHIBITED __WATCHOS_PROHIBITED;

@property (NS_NONATOMIC_IOSONLY, readonly) UNNotificationSetting criticalAlertSetting __IOS_AVAILABLE(12.0) __OSX_AVAILABLE(10.14) __WATCHOS_AVAILABLE(5.0) __TVOS_PROHIBITED;

@property (NS_NONATOMIC_IOSONLY, readonly) BOOL providesAppNotificationSettings __IOS_AVAILABLE(12.0) __OSX_AVAILABLE(10.14) __WATCHOS_AVAILABLE(5.0) __TVOS_PROHIBITED;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
