//
//  UNNotification.h
//  UserNotifications
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class UNNotificationRequest;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0), tvos(10.0))
@interface UNNotification : NSObject <NSCopying, NSSecureCoding>

// The date displayed on the notification.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSDate *date;

// The notification request that caused the notification to be delivered.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) UNNotificationRequest *request;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
