#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UILocalNotification.h>)
//
//  UILocalNotification.h
//  UIKit
//
//  Copyright (c) 2007-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class CLRegion;

// In iOS 8.0 and later, your application must register for user notifications using -[UIApplication registerUserNotificationSettings:] before being able to schedule and present UILocalNotifications
UIKIT_EXTERN API_DEPRECATED("Use UserNotifications Framework's UNNotificationRequest", ios(4.0, 10.0)) API_UNAVAILABLE(tvos) NS_SWIFT_UI_ACTOR
@interface UILocalNotification : NSObject<NSCopying, NSCoding>

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

// timer-based scheduling
@property(nullable, nonatomic,copy) NSDate *fireDate;
// the time zone to interpret fireDate in. pass nil if fireDate is an absolute GMT time (e.g. for an egg timer).
// pass a time zone to interpret fireDate as a wall time to be adjusted automatically upon time zone changes (e.g. for an alarm clock).
@property(nullable, nonatomic,copy) NSTimeZone *timeZone;

@property(nonatomic) NSCalendarUnit repeatInterval;      // 0 means don't repeat
@property(nullable, nonatomic,copy) NSCalendar *repeatCalendar;

// location-based scheduling

// set a CLRegion object to trigger the notification when the user enters or leaves a geographic region, depending upon the properties set on the CLRegion object itself. registering multiple UILocalNotifications with different regions containing the same identifier will result in undefined behavior. the number of region-triggered UILocalNotifications that may be registered at any one time is internally limited. in order to use region-triggered notifications, applications must have "when-in-use" authorization through CoreLocation. see the CoreLocation documentation for more information.
@property(nullable, nonatomic,copy) CLRegion *region API_AVAILABLE(ios(8.0));

// when YES, the notification will only fire one time. when NO, the notification will fire every time the region is entered or exited (depending upon the CLRegion object's configuration). default is YES.
@property(nonatomic,assign) BOOL regionTriggersOnce API_AVAILABLE(ios(8.0));

// alerts
@property(nullable, nonatomic,copy) NSString *alertBody;      // defaults to nil. pass a string or localized string key to show an alert
@property(nonatomic) BOOL hasAction;                // defaults to YES. pass NO to hide launching button/slider
@property(nullable, nonatomic,copy) NSString *alertAction;    // used in UIAlert button or 'slide to unlock...' slider in place of unlock
@property(nullable, nonatomic,copy) NSString *alertLaunchImage;   // used as the launch image (UILaunchImageFile) when launch button is tapped
@property(nullable, nonatomic,copy) NSString *alertTitle API_AVAILABLE(ios(8.2));  // defaults to nil. pass a string or localized string key

// sound
@property(nullable, nonatomic,copy) NSString *soundName;      // name of resource in app's bundle to play or UILocalNotificationDefaultSoundName

// badge
@property(nonatomic) NSInteger applicationIconBadgeNumber;  // 0 means no change. defaults to 0

// user info
@property(nullable, nonatomic,copy) NSDictionary *userInfo;   // throws if contains non-property list types

// category identifier of the local notification, as set on a UIUserNotificationCategory and passed to +[UIUserNotificationSettings settingsForTypes:categories:]
@property (nullable, nonatomic, copy) NSString *category API_AVAILABLE(ios(8.0));

@end


UIKIT_EXTERN NSString *const UILocalNotificationDefaultSoundName API_DEPRECATED("Use UserNotifications Framework's +[UNNotificationSound defaultSound]", ios(4.0, 10.0)) API_UNAVAILABLE(tvos);

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UILocalNotification.h>
#endif
