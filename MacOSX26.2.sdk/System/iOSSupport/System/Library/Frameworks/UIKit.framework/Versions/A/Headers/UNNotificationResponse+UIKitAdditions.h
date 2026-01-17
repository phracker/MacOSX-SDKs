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

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN @interface UNNotificationResponse (UIKitAdditions)
// used to identify which UIScene UI to reflect the user's response to a notification on
@property (nullable, nonatomic, readonly) UIScene *targetScene API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos, watchos); //  default nil
@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UNNotificationResponse+UIKitAdditions.h>
#endif
