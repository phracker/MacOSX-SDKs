//
//  UNNotificationAttributedMessageContext.h
//  UserNotifications
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UserNotifications/UNNotificationContent.h>

@class INSendMessageIntent;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0)) API_UNAVAILABLE(tvos)
@interface UNNotificationAttributedMessageContext : NSObject <UNNotificationContentProviding>

+ (instancetype)contextWithSendMessageIntent:(INSendMessageIntent *)sendMessageIntent attributedContent:(NSAttributedString *)attributedContent;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
