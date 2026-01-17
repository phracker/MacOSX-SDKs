// Copyright © Apple Inc. All rights reserved.

#import <TargetConditionals.h>
#import <Foundation/Foundation.h>

#if !TARGET_OS_WATCH

/// Asynchronously shows a notification banner like the one used for Game Center’s “Welcome Back” message.
/// If a banner is already being displayed, additional banners will be shown in sequence. Use this to notify the user of game events, high scores, completed achievements, etc.

API_DEPRECATED("Use UNNotificationRequest or provide custom UI instead. This method will become a no-op in a future version of GameKit.", ios(5.0, 17.0), tvos(9.0, 16.1), macos(10.8, 14.0))
@interface GKNotificationBanner : NSObject

+ (void)showBannerWithTitle:(nullable NSString *)title message:(nullable NSString *)message completionHandler:(void(^__nullable)(void))completionHandler API_DEPRECATED("Use UNNotificationRequest or provide custom UI instead. This method will become a no-op in a future version of GameKit.", ios(5.0, 16.1), tvos(9.0, 16.1), macos(10.8, 13.0));

+ (void)showBannerWithTitle:(nullable NSString *)title message:(nullable NSString *)message duration:(NSTimeInterval)duration completionHandler:(void(^__nullable)(void))completionHandler API_DEPRECATED("Use UNNotificationRequest or provide custom UI instead. This method will become a no-op in a future version of GameKit.", ios(5.0, 16.1), tvos(9.0, 16.1), macos(10.8, 13.0));

@end

#endif
