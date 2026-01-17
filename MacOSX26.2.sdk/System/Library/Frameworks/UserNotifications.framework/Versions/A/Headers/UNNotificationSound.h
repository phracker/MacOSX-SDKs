//
//  UNNotificationSound.h
//  UserNotifications
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSString *UNNotificationSoundName NS_EXTENSIBLE_STRING_ENUM;

API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0)) API_UNAVAILABLE(tvos)
@interface UNNotificationSound : NSObject <NSCopying, NSSecureCoding>

// The default sound used for notifications.
@property(class, NS_NONATOMIC_IOSONLY, copy, readonly) UNNotificationSound *defaultSound;

// The default sound used for incoming call notifications. Plays the ringtone and haptics specified in Settings for a 30 second duration. The parent UNNotificationContent object must be created in the notification service extension via -[UNNotificationContent contentByUpdatingWithProvider:error:] where the provider is an INStartCallIntent with a destinationType of INCallDestinationTypeNormal. Please use CallKit instead of UserNotifications for this use case when available.
@property(class, NS_NONATOMIC_IOSONLY, copy, readonly) UNNotificationSound *defaultRingtoneSound API_AVAILABLE(ios(15.2)) API_UNAVAILABLE(macos, watchos, tvos, macCatalyst);

// The default sound used for critical alerts. Critical alerts will bypass the mute switch and Do Not Disturb.
@property(class, NS_NONATOMIC_IOSONLY, copy, readonly) UNNotificationSound *defaultCriticalSound API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(tvos);

// The default sound used for critical alerts with a custom audio volume level. Critical alerts will bypass the mute switch and Do Not Disturb. The audio volume is expected to be between 0.0f and 1.0f.
+ (instancetype)defaultCriticalSoundWithAudioVolume:(float)volume API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(tvos);

// The sound file to be played for the notification. The sound must be in the Library/Sounds folder of the app's data container or the Library/Sounds folder of an app group data container. If the file is not found in a container, the system will look in the app's bundle.
+ (instancetype)soundNamed:(UNNotificationSoundName)name API_UNAVAILABLE(watchos, tvos);

// The sound file to be played for an incoming call notification. The sound must be in the Library/Sounds folder of the app's data container or the Library/Sounds folder of an app group data container. If the file is not found in a container, the system will look in the app's bundle. The sound will repeat for a total duration of 30 seconds. The haptics specified in Settings will be played along with the sound. The parent UNNotificationContent object must be created in the notification service extension via -[UNNotificationContent contentByUpdatingWithProvider:error:] where the provider is an INStartCallIntent with a destinationType of INCallDestinationTypeNormal. Please use CallKit instead of UserNotifications for this use case when available.
+ (instancetype)ringtoneSoundNamed:(UNNotificationSoundName)name API_AVAILABLE(ios(15.2)) API_UNAVAILABLE(macos, watchos, tvos, macCatalyst);

// The name of a sound file to be played for an critical alert. Critical alerts will bypass the mute switch and Do Not Disturb. The sound file must be contained in the app’s bundle or in the Library/Sounds folder of the app’s data container. If files exist in both locations then the file in the app’s data container will be preferred.
+ (instancetype)criticalSoundNamed:(UNNotificationSoundName)name API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(watchos, tvos);

// The name of a sound file to be played for an critical alert with a custom audio volume level. Critical alerts will bypass the mute switch and Do Not Disturb. The sound file must be contained in the app’s bundle or in the Library/Sounds folder of the app’s data container. If files exist in both locations then the file in the app’s data container will be preferred. The audio volume is expected to be between 0.0f and 1.0f.
+ (instancetype)criticalSoundNamed:(UNNotificationSoundName)name withAudioVolume:(float)volume API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(watchos, tvos);

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
