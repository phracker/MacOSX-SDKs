//
//  UNNotificationAction.h
//  UserNotifications
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSUInteger, UNNotificationActionOptions) {
    
    // Whether this action should require unlocking before being performed.
    UNNotificationActionOptionAuthenticationRequired = (1 << 0),
    
    // Whether this action should be indicated as destructive.
    UNNotificationActionOptionDestructive = (1 << 1),

    // Whether this action should cause the application to launch in the foreground.
    UNNotificationActionOptionForeground = (1 << 2),
} __IOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0) __OSX_AVAILABLE(10.14) __TVOS_PROHIBITED;

static const UNNotificationActionOptions UNNotificationActionOptionNone NS_SWIFT_UNAVAILABLE("Use [] instead.") __IOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0) __OSX_AVAILABLE(10.14) __TVOS_PROHIBITED = 0;

__IOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0) __OSX_AVAILABLE(10.14) __TVOS_PROHIBITED
@interface UNNotificationAction : NSObject <NSCopying, NSSecureCoding>

// The unique identifier for this action.
@property (NS_NONATOMIC_IOSONLY, copy, readonly) NSString *identifier;

// The title to display for this action.
@property (NS_NONATOMIC_IOSONLY, copy, readonly) NSString *title;

// The options configured for this action.
@property (NS_NONATOMIC_IOSONLY, readonly) UNNotificationActionOptions options;

// Use -[NSString localizedUserNotificationStringForKey:arguments:] to provide a string that will be localized at the time that the notification is presented.
+ (instancetype)actionWithIdentifier:(NSString *)identifier title:(NSString *)title options:(UNNotificationActionOptions)options;

- (instancetype)init NS_UNAVAILABLE;

@end

__IOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0) __OSX_AVAILABLE(10.14) __TVOS_PROHIBITED
@interface UNTextInputNotificationAction : UNNotificationAction

// Use -[NSString localizedUserNotificationStringForKey:arguments:] to provide a string that will be localized at the time that the notification is presented.
+ (instancetype)actionWithIdentifier:(NSString *)identifier title:(NSString *)title options:(UNNotificationActionOptions)options textInputButtonTitle:(NSString *)textInputButtonTitle textInputPlaceholder:(NSString *)textInputPlaceholder;

// The text input button title displayed for this action.
@property (NS_NONATOMIC_IOSONLY, copy, readonly) NSString *textInputButtonTitle;

// The placeholder text displayed in the text input field for this action.
@property (NS_NONATOMIC_IOSONLY, copy, readonly) NSString *textInputPlaceholder;

@end

NS_ASSUME_NONNULL_END
