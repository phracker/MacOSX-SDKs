#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UNNotificationResponse+UIKitAdditions.h>)
//
//  UNNotificationResponse+UIKitAdditions.h
//  UIKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <UIKit/UIKitDefines.h>
#import <UserNotifications/UNNotificationResponse.h>

@class UIScene;

NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN @interface UNNotificationResponse (UIKitAdditions)
// used to identify which UIScene UI to reflect the user's response to a notification on
@property (nullable, nonatomic, readonly) UIScene *targetScene NS_AVAILABLE_IOS(13_0); //  default nil
@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UNNotificationResponse+UIKitAdditions.h>
#endif
