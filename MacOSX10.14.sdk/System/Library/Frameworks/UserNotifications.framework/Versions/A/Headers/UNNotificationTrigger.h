//
//  UNNotificationTrigger.h
//  UserNotifications
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CLRegion;

NS_ASSUME_NONNULL_BEGIN

__IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0) __OSX_AVAILABLE(10.14)
@interface UNNotificationTrigger : NSObject <NSCopying, NSSecureCoding>

@property (NS_NONATOMIC_IOSONLY, readonly) BOOL repeats;

- (instancetype)init NS_UNAVAILABLE;

@end

// UNPushNotificationTrigger can be sent from a server using Apple Push Notification Service.
__IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0) __OSX_AVAILABLE(10.14)
@interface UNPushNotificationTrigger : UNNotificationTrigger

@end

// UNTimeIntervalNotificationTrigger can be scheduled on the device to notify after the time interval, and optionally repeat.
__IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0) __OSX_AVAILABLE(10.14)
@interface UNTimeIntervalNotificationTrigger : UNNotificationTrigger

@property (NS_NONATOMIC_IOSONLY, readonly) NSTimeInterval timeInterval;

+ (instancetype)triggerWithTimeInterval:(NSTimeInterval)timeInterval repeats:(BOOL)repeats;

- (nullable NSDate *)nextTriggerDate;

@end

// UNCalendarNotificationTrigger can be scheduled on the device to notify based on date and time values, and optionally repeat. For example, if a notification should be delivered at the next 8:00 AM then set the 'hour' property of dateComponents to 8. If the notification should be delivered every day at 8:00 AM then set repeats to YES.
__IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0) __OSX_AVAILABLE(10.14)
@interface UNCalendarNotificationTrigger : UNNotificationTrigger

@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSDateComponents *dateComponents;

// The next date is calculated using matching date components.
+ (instancetype)triggerWithDateMatchingComponents:(NSDateComponents *)dateComponents repeats:(BOOL)repeats;

- (nullable NSDate *)nextTriggerDate;

@end

// UNLocationNotificationTrigger can be scheduled on the device to notify when the user enters or leaves a geographic region. The identifier on CLRegion must be unique. Scheduling multiple UNNotificationRequests with different regions containing the same identifier will result in undefined behavior. The number of UNLocationNotificationTriggers that may be scheduled by an application at any one time is limited by the system. Applications must have "when-in-use" authorization through CoreLocation. See the CoreLocation documentation for more information.
__IOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0) __API_UNAVAILABLE(macos, tvos)
@interface UNLocationNotificationTrigger : UNNotificationTrigger

@property (NS_NONATOMIC_IOSONLY, readonly, copy) CLRegion *region;

+ (instancetype)triggerWithRegion:(CLRegion *)region repeats:(BOOL)repeats __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END
