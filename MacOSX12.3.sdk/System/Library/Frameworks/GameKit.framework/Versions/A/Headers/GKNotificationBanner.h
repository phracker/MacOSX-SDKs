//
//  GKNotificationBanner.h
//  Game Center
//
//  Copyright 2012-2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/// Asynchronously shows a notification banner like the one used for Game Center’s “Welcome Back” message.
/// If a banner is already being displayed, additional banners will be shown in sequence. Use this to notify the user of game events, high scores, completed achievements, etc.

NS_CLASS_AVAILABLE(10_8, 5_0)
@interface GKNotificationBanner : NSObject

+ (void)showBannerWithTitle:(nullable NSString *)title message:(nullable NSString *)message completionHandler:(void(^__nullable)(void))completionHandler NS_AVAILABLE(10_8, 5_0);

+ (void)showBannerWithTitle:(nullable NSString *)title message:(nullable NSString *)message duration:(NSTimeInterval)duration completionHandler:(void(^__nullable)(void))completionHandler NS_AVAILABLE(10_8, 6_0);

@end
