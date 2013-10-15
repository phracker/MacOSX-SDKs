//
//  GKNotificationBanner.h
//  GameKit
//
//  Copyright 2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameKit/GKDefines.h>

// Asynchronously shows a notification banner like the one used for Game Center’s “Welcome Back” message.
// If a banner is already being displayed, additional banners will be shown in sequence. Use this to notify the user of game events, high scores, completed achievements, etc.

NS_CLASS_AVAILABLE(10_8, 5_0)
@interface GKNotificationBanner : NSObject
+ (void)showBannerWithTitle:(NSString *)title message:(NSString *)message completionHandler:(void(^)(void))completionHandler __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_5_0);

+ (void)showBannerWithTitle:(NSString *)title message:(NSString *)message duration:(NSTimeInterval)duration completionHandler:(void(^)(void))completionHandler __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_6_0);
@end

