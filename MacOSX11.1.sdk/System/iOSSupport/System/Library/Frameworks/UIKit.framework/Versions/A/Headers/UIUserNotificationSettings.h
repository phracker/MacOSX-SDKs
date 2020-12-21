#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIUserNotificationSettings.h>)
//
//  UIUserNotificationSettings.h
//  UIKit
//
//  Copyright (c) 2007-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class UIUserNotificationCategory;
@class UIUserNotificationAction;

typedef NS_OPTIONS(NSUInteger, UIUserNotificationType) {
    UIUserNotificationTypeNone    = 0,      // the application may not present any UI upon a notification being received
    UIUserNotificationTypeBadge   = 1 << 0, // the application may badge its icon upon a notification being received
    UIUserNotificationTypeSound   = 1 << 1, // the application may play a sound upon a notification being received
    UIUserNotificationTypeAlert   = 1 << 2, // the application may display an alert upon a notification being received
} NS_ENUM_DEPRECATED_IOS(8_0, 10_0, "Use UserNotifications Framework's UNAuthorizationOptions") API_UNAVAILABLE(tvos);

typedef NS_ENUM(NSUInteger, UIUserNotificationActionBehavior) {
    UIUserNotificationActionBehaviorDefault,        // the default action behavior
    UIUserNotificationActionBehaviorTextInput       // system provided action behavior, allows text input from the user
} NS_ENUM_DEPRECATED_IOS(9_0, 10_0, "Use UserNotifications Framework's UNNotificationAction or UNTextInputNotificationAction") API_UNAVAILABLE(tvos);

typedef NS_ENUM(NSUInteger, UIUserNotificationActivationMode) {
    UIUserNotificationActivationModeForeground, // activates the application in the foreground
    UIUserNotificationActivationModeBackground  // activates the application in the background, unless it's already in the foreground
} NS_ENUM_DEPRECATED_IOS(8_0, 10_0, "Use UserNotifications Framework's UNNotificationActionOptions") API_UNAVAILABLE(tvos);

typedef NS_ENUM(NSUInteger, UIUserNotificationActionContext) {
    UIUserNotificationActionContextDefault,  // the default context of a notification action
    UIUserNotificationActionContextMinimal   // the context of a notification action when space is limited
} NS_ENUM_DEPRECATED_IOS(8_0, 10_0, "Use UserNotifications Framework's -[UNNotificationCategory actions] or -[UNNotificationCategory minimalActions]") API_UNAVAILABLE(tvos);

UIKIT_EXTERN NSString *const UIUserNotificationTextInputActionButtonTitleKey API_DEPRECATED("Use UserNotifications Framework's -[UNTextInputNotificationAction textInputButtonTitle]", ios(9.0, 10.0)) API_UNAVAILABLE(tvos);

UIKIT_EXTERN NSString *const UIUserNotificationActionResponseTypedTextKey API_DEPRECATED("Use UserNotifications Framework's -[UNTextInputNotificationResponse userText]", ios(9.0, 10.0)) API_UNAVAILABLE(tvos);

UIKIT_EXTERN API_DEPRECATED("Use UserNotifications Framework's UNNotificationSettings", ios(8.0, 10.0)) API_UNAVAILABLE(tvos)
@interface UIUserNotificationSettings : NSObject

// categories may be nil or an empty set if custom user notification actions will not be used
+ (instancetype)settingsForTypes:(UIUserNotificationType)types
                      categories:(nullable NSSet<UIUserNotificationCategory *> *)categories; // instances of UIUserNotificationCategory

@property (nonatomic, readonly) UIUserNotificationType types;

// The set of UIUserNotificationCategory objects that describe the actions to show when a user notification is presented
@property (nullable, nonatomic, copy, readonly) NSSet<UIUserNotificationCategory *> *categories;

@end

UIKIT_EXTERN API_DEPRECATED("Use UserNotifications Framework's UNNotificationCategory", ios(8.0, 10.0)) API_UNAVAILABLE(tvos)
@interface UIUserNotificationCategory : NSObject <NSCopying, NSMutableCopying, NSSecureCoding>

- (instancetype)init NS_DESIGNATED_INITIALIZER API_UNAVAILABLE(tvos);
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER API_UNAVAILABLE(tvos);

// The category identifier passed in a UILocalNotification or a remote notification payload
@property (nullable, nonatomic, copy, readonly) NSString *identifier API_UNAVAILABLE(tvos);

// UIUserNotificationActions in the order to be displayed for the specified context
- (nullable NSArray<UIUserNotificationAction *> *)actionsForContext:(UIUserNotificationActionContext)context API_UNAVAILABLE(tvos);

@end

UIKIT_EXTERN API_DEPRECATED("Use UserNotifications Framework's UNNotificationCategory", ios(8.0, 10.0)) API_UNAVAILABLE(tvos)
@interface UIMutableUserNotificationCategory : UIUserNotificationCategory

// The category identifier passed in a UILocalNotification or a remote notification payload
@property (nullable, nonatomic, copy) NSString *identifier;

// Sets the UIUserNotificationActions in the order to be displayed for the specified context
- (void)setActions:(nullable NSArray<UIUserNotificationAction *> *)actions forContext:(UIUserNotificationActionContext)context;

@end

UIKIT_EXTERN API_DEPRECATED("Use UserNotifications Framework's UNNotificationAction", ios(8.0, 10.0)) API_UNAVAILABLE(tvos)
@interface UIUserNotificationAction : NSObject <NSCopying, NSMutableCopying, NSSecureCoding>

- (instancetype)init NS_DESIGNATED_INITIALIZER API_UNAVAILABLE(tvos);
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER API_UNAVAILABLE(tvos);

// The unique identifier for this action.
@property (nullable, nonatomic, copy, readonly) NSString *identifier API_UNAVAILABLE(tvos);

// The localized title to display for this action.
@property (nullable, nonatomic, copy, readonly) NSString *title API_UNAVAILABLE(tvos);

// The behavior of this action when the user activates it.
@property (nonatomic, assign, readonly) UIUserNotificationActionBehavior behavior API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(tvos);

// Parameters that can be used by some types of actions.
@property (nonatomic, copy, readonly) NSDictionary *parameters API_AVAILABLE(ios(9.0))API_UNAVAILABLE(tvos);

// How the application should be activated in response to the action.
@property (nonatomic, assign, readonly) UIUserNotificationActivationMode activationMode API_UNAVAILABLE(tvos);

// Whether this action is secure and should require unlocking before being performed. If the activation mode is UIUserNotificationActivationModeForeground, then the action is considered secure and this property is ignored.
@property (nonatomic, assign, readonly, getter=isAuthenticationRequired) BOOL authenticationRequired API_UNAVAILABLE(tvos);

// Whether this action should be indicated as destructive when displayed.
@property (nonatomic, assign, readonly, getter=isDestructive) BOOL destructive API_UNAVAILABLE(tvos);

@end

UIKIT_EXTERN API_DEPRECATED("Use UserNotifications Framework's UNNotificationAction", ios(8.0, 10.0)) API_UNAVAILABLE(tvos)
@interface UIMutableUserNotificationAction : UIUserNotificationAction

// The unique identifier for this action.
@property (nullable, nonatomic, copy) NSString *identifier;

// The localized title to display for this action.
@property (nullable, nonatomic, copy) NSString *title;

// The behavior of this action when the user activates it.
@property (nonatomic, assign) UIUserNotificationActionBehavior behavior API_AVAILABLE(ios(9.0));

// Parameters that can be used by some types of actions.
@property (nonatomic, copy) NSDictionary *parameters API_AVAILABLE(ios(9.0));

// How the application should be activated in response to the action.
@property (nonatomic, assign) UIUserNotificationActivationMode activationMode;

// Whether this action is secure and should require unlocking before being performed. If the activation mode is UIUserNotificationActivationModeForeground, then the action is considered secure and this property is ignored.
@property (nonatomic, assign, getter=isAuthenticationRequired) BOOL authenticationRequired;

// Whether this action should be indicated as destructive when displayed.
@property (nonatomic, assign, getter=isDestructive) BOOL destructive;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIUserNotificationSettings.h>
#endif
