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
    UNAuthorizationStatusProvisional __API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
} __API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0), tvos(10.0));

typedef NS_ENUM(NSInteger, UNShowPreviewsSetting) {
    // Notification previews are always shown.
    UNShowPreviewsSettingAlways,
    
    // Notifications previews are only shown when authenticated.
    UNShowPreviewsSettingWhenAuthenticated,
    
    // Notifications previews are never shown.
    UNShowPreviewsSettingNever
} __API_AVAILABLE(macos(10.14), ios(11.0)) __API_UNAVAILABLE(watchos, tvos);

typedef NS_ENUM(NSInteger, UNNotificationSetting) {
    // The application does not support this notification type
    UNNotificationSettingNotSupported  = 0,
    
    // The notification setting is turned off.
    UNNotificationSettingDisabled,
    
    // The notification setting is turned on.
    UNNotificationSettingEnabled,
} __API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0), tvos(10.0));

typedef NS_ENUM(NSInteger, UNAlertStyle) {
    UNAlertStyleNone = 0,
    UNAlertStyleBanner,
    UNAlertStyleAlert,
} __API_AVAILABLE(macos(10.14), ios(10.0)) __API_UNAVAILABLE(watchos, tvos);

__API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0), tvos(10.0))
@interface UNNotificationSettings : NSObject <NSCopying, NSSecureCoding>

@property (NS_NONATOMIC_IOSONLY, readonly) UNAuthorizationStatus authorizationStatus;

@property (NS_NONATOMIC_IOSONLY, readonly) UNNotificationSetting soundSetting __API_UNAVAILABLE(tvos);
@property (NS_NONATOMIC_IOSONLY, readonly) UNNotificationSetting badgeSetting __API_UNAVAILABLE(watchos);
@property (NS_NONATOMIC_IOSONLY, readonly) UNNotificationSetting alertSetting __API_UNAVAILABLE(tvos);

@property (NS_NONATOMIC_IOSONLY, readonly) UNNotificationSetting notificationCenterSetting __API_UNAVAILABLE(tvos);
@property (NS_NONATOMIC_IOSONLY, readonly) UNNotificationSetting lockScreenSetting __API_UNAVAILABLE(watchos, tvos);
@property (NS_NONATOMIC_IOSONLY, readonly) UNNotificationSetting carPlaySetting __API_UNAVAILABLE(macos, tvos, watchos);

@property (NS_NONATOMIC_IOSONLY, readonly) UNAlertStyle alertStyle __API_UNAVAILABLE(watchos, tvos);

@property (NS_NONATOMIC_IOSONLY, readonly) UNShowPreviewsSetting showPreviewsSetting  __API_AVAILABLE(macos(10.14), ios(11.0)) __API_UNAVAILABLE(watchos, tvos);

@property (NS_NONATOMIC_IOSONLY, readonly) UNNotificationSetting criticalAlertSetting __API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0)) __API_UNAVAILABLE(tvos);

@property (NS_NONATOMIC_IOSONLY, readonly) BOOL providesAppNotificationSettings __API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0)) __API_UNAVAILABLE(tvos);

@property (NS_NONATOMIC_IOSONLY, readonly) UNNotificationSetting announcementSetting __API_AVAILABLE(ios(13.0), watchos(6.0)) __API_UNAVAILABLE(macos, tvos);

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
