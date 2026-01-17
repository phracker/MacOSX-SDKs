//
//  UNNotificationActionIcon.h
//  UserNotifications
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
@interface UNNotificationActionIcon : NSObject <NSCopying, NSSecureCoding>

+ (instancetype)iconWithTemplateImageName:(NSString *)templateImageName;

+ (instancetype)iconWithSystemImageName:(NSString *)systemImageName;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
