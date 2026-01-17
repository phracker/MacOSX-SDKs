//
//  UNNotificationSound.h
//  UserNotifications
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSString *UNNotificationSoundName NS_EXTENSIBLE_STRING_ENUM;

__IOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0) __OSX_AVAILABLE(10.14) __TVOS_PROHIBITED
@interface UNNotificationSound : NSObject <NSCopying, NSSecureCoding>

// The default sound used for notifications.
@property(class, NS_NONATOMIC_IOSONLY, copy, readonly) UNNotificationSound *defaultSound;

// The default sound used for critical alerts. Critical alerts will bypass the mute switch and Do Not Disturb.
@property(class, NS_NONATOMIC_IOSONLY, copy, readonly) UNNotificationSound *defaultCriticalSound __IOS_AVAILABLE(12.0) __WATCHOS_AVAILABLE(5.0);

// The default sound used for critical alerts with a custom audio volume level. Critical alerts will bypass the mute switch and Do Not Disturb. The audio volume is expected to be between 0.0f and 1.0f.
+ (instancetype)defaultCriticalSoundWithAudioVolume:(float)volume __IOS_AVAILABLE(12.0) __WATCHOS_AVAILABLE(5.0);

// The name of a sound file to be played for the notification. The sound file must be contained in the app’s bundle or in the Library/Sounds folder of the app’s data container. If files exist in both locations then the file in the app’s data container will be preferred.
+ (instancetype)soundNamed:(UNNotificationSoundName)name __WATCHOS_PROHIBITED;

// The name of a sound file to be played for an critical alert. Critical alerts will bypass the mute switch and Do Not Disturb. The sound file must be contained in the app’s bundle or in the Library/Sounds folder of the app’s data container. If files exist in both locations then the file in the app’s data container will be preferred.
+ (instancetype)criticalSoundNamed:(UNNotificationSoundName)name __IOS_AVAILABLE(12.0) __WATCHOS_PROHIBITED;

// The name of a sound file to be played for an critical alert with a custom audio volume level. Critical alerts will bypass the mute switch and Do Not Disturb. The sound file must be contained in the app’s bundle or in the Library/Sounds folder of the app’s data container. If files exist in both locations then the file in the app’s data container will be preferred. The audio volume is expected to be between 0.0f and 1.0f.
+ (instancetype)criticalSoundNamed:(UNNotificationSoundName)name withAudioVolume:(float)volume __IOS_AVAILABLE(12.0) __WATCHOS_PROHIBITED;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
