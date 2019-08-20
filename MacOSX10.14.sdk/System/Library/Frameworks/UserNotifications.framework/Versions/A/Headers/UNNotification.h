//
//  UNNotification.h
//  UserNotifications
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class UNNotificationRequest;

NS_ASSUME_NONNULL_BEGIN

__IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0) __OSX_AVAILABLE(10.14)
@interface UNNotification : NSObject <NSCopying, NSSecureCoding>

// The date displayed on the notification.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSDate *date;

// The notification request that caused the notification to be delivered.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) UNNotificationRequest *request;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
