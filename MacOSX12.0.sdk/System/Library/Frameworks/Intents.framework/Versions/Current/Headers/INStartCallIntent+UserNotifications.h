//
//  INStartCallIntent+UserNotifications.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Intents/INStartCallIntent.h>
#import <UserNotifications/UNNotificationContent.h>

 NS_ASSUME_NONNULL_BEGIN

 API_AVAILABLE(ios(15.0), macos(12.0), watchos(8.0)) API_UNAVAILABLE(tvos)
 @interface INStartCallIntent (UserNotifications) <UNNotificationContentProviding>
 @end

 NS_ASSUME_NONNULL_END
