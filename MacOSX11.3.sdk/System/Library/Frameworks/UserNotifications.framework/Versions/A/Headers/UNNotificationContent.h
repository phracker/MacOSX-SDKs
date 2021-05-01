//
//  UNNotificationContent.h
//  UserNotifications
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class UNNotificationAttachment;
@class UNNotificationSound;

NS_ASSUME_NONNULL_BEGIN

__API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0), tvos(10.0))
@interface UNNotificationContent : NSObject <NSCopying, NSMutableCopying, NSSecureCoding>

// Optional array of attachments.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSArray <UNNotificationAttachment *> *attachments __API_UNAVAILABLE(tvos);

// The application badge number.
@property (NS_NONATOMIC_IOSONLY, readonly, copy, nullable) NSNumber *badge;

// The body of the notification.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *body __API_UNAVAILABLE(tvos);

// The identifier for a registered UNNotificationCategory that will be used to determine the appropriate actions to display for the notification.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *categoryIdentifier __API_UNAVAILABLE(tvos);

// The launch image that will be used when the app is opened from the notification.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *launchImageName __API_UNAVAILABLE(macos, tvos);

// The sound that will be played for the notification.
@property (NS_NONATOMIC_IOSONLY, readonly, copy, nullable) UNNotificationSound *sound __API_UNAVAILABLE(tvos);

// The subtitle of the notification.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *subtitle __API_UNAVAILABLE(tvos);

// The unique identifier for the thread or conversation related to this notification request. It will be used to visually group notifications together.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *threadIdentifier __API_UNAVAILABLE(tvos);

// The title of the notification.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *title __API_UNAVAILABLE(tvos);

// Apps can set the userInfo for locally scheduled notification requests. The contents of the push payload will be set as the userInfo for remote notifications.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSDictionary *userInfo __API_UNAVAILABLE(tvos);

/// The argument to be inserted in the summary for this notification.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *summaryArgument __API_AVAILABLE(ios(12.0)) __API_UNAVAILABLE(watchos, tvos);

/// A number that indicates how many items in the summary are represented in the summary.
/// For example if a podcast app sends one notification for 3 new episodes in a show,
/// the argument should be the name of the show and the count should be 3.
/// Default is 1 and cannot be 0.
@property (NS_NONATOMIC_IOSONLY, readonly, assign) NSUInteger summaryArgumentCount __API_AVAILABLE(ios(12.0)) __API_UNAVAILABLE(watchos, tvos);

// An identifier for the content of the notification used by the system to customize the scene to be activated when tapping on a notification.
@property (NS_NONATOMIC_IOSONLY, readonly, copy, nullable) NSString *targetContentIdentifier __API_AVAILABLE(ios(13.0)); // default nil

@end

__API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0), tvos(10.0))
@interface UNMutableNotificationContent : UNNotificationContent

// Optional array of attachments.
@property (NS_NONATOMIC_IOSONLY, copy) NSArray <UNNotificationAttachment *> *attachments __API_UNAVAILABLE(tvos);

// The application badge number. nil means no change. 0 to hide.
@property (NS_NONATOMIC_IOSONLY, copy, nullable) NSNumber *badge;

// The body of the notification. Use -[NSString localizedUserNotificationStringForKey:arguments:] to provide a string that will be localized at the time that the notification is presented.
@property (NS_NONATOMIC_IOSONLY, copy) NSString *body __API_UNAVAILABLE(tvos);

// The identifier for a registered UNNotificationCategory that will be used to determine the appropriate actions to display for the notification.
@property (NS_NONATOMIC_IOSONLY, copy) NSString *categoryIdentifier __API_UNAVAILABLE(tvos);

// The launch image that will be used when the app is opened from the notification.
@property (NS_NONATOMIC_IOSONLY, copy) NSString *launchImageName __API_UNAVAILABLE(macos, tvos);

// The sound that will be played for the notification.
@property (NS_NONATOMIC_IOSONLY, copy, nullable) UNNotificationSound *sound __API_UNAVAILABLE(tvos);

// The subtitle of the notification. Use -[NSString localizedUserNotificationStringForKey:arguments:] to provide a string that will be localized at the time that the notification is presented.
@property (NS_NONATOMIC_IOSONLY, copy) NSString *subtitle __API_UNAVAILABLE(tvos);

// The unique identifier for the thread or conversation related to this notification request. It will be used to visually group notifications together.
@property (NS_NONATOMIC_IOSONLY, copy) NSString *threadIdentifier __API_UNAVAILABLE(tvos);

// The title of the notification. Use -[NSString localizedUserNotificationStringForKey:arguments:] to provide a string that will be localized at the time that the notification is presented.
@property (NS_NONATOMIC_IOSONLY, copy) NSString *title __API_UNAVAILABLE(tvos);

// Apps can set the userInfo for locally scheduled notification requests. The contents of the push payload will be set as the userInfo for remote notifications.
@property (NS_NONATOMIC_IOSONLY, copy) NSDictionary *userInfo __API_UNAVAILABLE(tvos);

/// The argument to be inserted in the summary for this notification.
@property (NS_NONATOMIC_IOSONLY, copy) NSString *summaryArgument __API_AVAILABLE(ios(12.0)) __API_UNAVAILABLE(watchos, tvos);

/// A number that indicates how many items in the summary are represented in the summary.
/// For example if a podcast app sends one notification for 3 new episodes in a show,
/// the argument should be the name of the show and the count should be 3.
/// Default is 1 and cannot be 0.
@property (NS_NONATOMIC_IOSONLY, assign) NSUInteger summaryArgumentCount __API_AVAILABLE(ios(12.0)) __API_UNAVAILABLE(watchos, tvos);

// An identifier for the content of the notification used by the system to customize the scene to be activated when tapping on a notification.
@property (NS_NONATOMIC_IOSONLY, copy, nullable) NSString *targetContentIdentifier __API_AVAILABLE(ios(13.0)); // default nil

@end

NS_ASSUME_NONNULL_END
