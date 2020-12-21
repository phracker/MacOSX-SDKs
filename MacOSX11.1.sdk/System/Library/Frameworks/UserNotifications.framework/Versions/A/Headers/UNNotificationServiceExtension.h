//
//  UNNotificationServiceExtension.h
//  UserNotifications
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#include <Foundation/Foundation.h>

@class UNNotificationRequest;
@class UNNotificationContent;

NS_ASSUME_NONNULL_BEGIN

__API_AVAILABLE(macos(10.14), ios(10.0), watchos(6.0)) __API_UNAVAILABLE(tvos)
@interface UNNotificationServiceExtension : NSObject

// Call contentHandler with the modified notification content to deliver. If the handler is not called before the service's time expires then the unmodified notification will be delivered.
// You are expected to override this method to implement push notification modification.
- (void)didReceiveNotificationRequest:(UNNotificationRequest *)request withContentHandler:(void (^)(UNNotificationContent *contentToDeliver))contentHandler;

// Will be called just before this extension is terminated by the system. You may choose whether to override this method.
- (void)serviceExtensionTimeWillExpire;

@end

NS_ASSUME_NONNULL_END
