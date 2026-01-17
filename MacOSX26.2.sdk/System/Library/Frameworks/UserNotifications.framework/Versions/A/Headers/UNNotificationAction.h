//
//  UNNotificationAction.h
//  UserNotifications
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class UNNotificationActionIcon;

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSUInteger, UNNotificationActionOptions) {
    
    // Whether this action should require unlocking before being performed.
    UNNotificationActionOptionAuthenticationRequired = (1 << 0),
    
    // Whether this action should be indicated as destructive.
    UNNotificationActionOptionDestructive = (1 << 1),

    // Whether this action should cause the application to launch in the foreground.
    UNNotificationActionOptionForeground = (1 << 2),
} API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0)) API_UNAVAILABLE(tvos);

static const UNNotificationActionOptions UNNotificationActionOptionNone NS_SWIFT_UNAVAILABLE("Use [] instead.") API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0)) API_UNAVAILABLE(tvos) = 0;

API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0)) API_UNAVAILABLE(tvos)
@interface UNNotificationAction : NSObject <NSCopying, NSSecureCoding>

// The unique identifier for this action.
@property (NS_NONATOMIC_IOSONLY, copy, readonly) NSString *identifier;

// The title to display for this action.
@property (NS_NONATOMIC_IOSONLY, copy, readonly) NSString *title;

// The options configured for this action.
@property (NS_NONATOMIC_IOSONLY, readonly) UNNotificationActionOptions options;

// The icon configured for this action.
@property (NS_NONATOMIC_IOSONLY, readonly, copy, nullable) UNNotificationActionIcon *icon API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

// Use -[NSString localizedUserNotificationStringForKey:arguments:] to provide a string that will be localized at the time that the notification is presented.
+ (instancetype)actionWithIdentifier:(NSString *)identifier title:(NSString *)title options:(UNNotificationActionOptions)options;

+ (instancetype)actionWithIdentifier:(NSString *)identifier title:(NSString *)title options:(UNNotificationActionOptions)options icon:(nullable UNNotificationActionIcon *)icon API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));


- (instancetype)init NS_UNAVAILABLE;

@end

API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0)) API_UNAVAILABLE(tvos)
@interface UNTextInputNotificationAction : UNNotificationAction

// Use -[NSString localizedUserNotificationStringForKey:arguments:] to provide a string that will be localized at the time that the notification is presented.
+ (instancetype)actionWithIdentifier:(NSString *)identifier title:(NSString *)title options:(UNNotificationActionOptions)options textInputButtonTitle:(NSString *)textInputButtonTitle textInputPlaceholder:(NSString *)textInputPlaceholder;

+ (instancetype)actionWithIdentifier:(NSString *)identifier title:(NSString *)title options:(UNNotificationActionOptions)options icon:(nullable UNNotificationActionIcon *)icon textInputButtonTitle:(NSString *)textInputButtonTitle textInputPlaceholder:(NSString *)textInputPlaceholder API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

// The text input button title displayed for this action.
@property (NS_NONATOMIC_IOSONLY, copy, readonly) NSString *textInputButtonTitle;

// The placeholder text displayed in the text input field for this action.
@property (NS_NONATOMIC_IOSONLY, copy, readonly) NSString *textInputPlaceholder;

@end

NS_ASSUME_NONNULL_END
