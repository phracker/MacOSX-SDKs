#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIApplicationShortcutItem.h>)
//
//  UIApplicationShortcutItem.h
//  UIKit
//
//  Copyright © 2015-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class UIImage;

typedef NS_ENUM(NSInteger, UIApplicationShortcutIconType) {
    UIApplicationShortcutIconTypeCompose,
    UIApplicationShortcutIconTypePlay,
    UIApplicationShortcutIconTypePause,
    UIApplicationShortcutIconTypeAdd,
    UIApplicationShortcutIconTypeLocation,
    UIApplicationShortcutIconTypeSearch,
    UIApplicationShortcutIconTypeShare,
    UIApplicationShortcutIconTypeProhibit       API_AVAILABLE(ios(9.1)),
    UIApplicationShortcutIconTypeContact        API_AVAILABLE(ios(9.1)),
    UIApplicationShortcutIconTypeHome           API_AVAILABLE(ios(9.1)),
    UIApplicationShortcutIconTypeMarkLocation   API_AVAILABLE(ios(9.1)),
    UIApplicationShortcutIconTypeFavorite       API_AVAILABLE(ios(9.1)),
    UIApplicationShortcutIconTypeLove           API_AVAILABLE(ios(9.1)),
    UIApplicationShortcutIconTypeCloud          API_AVAILABLE(ios(9.1)),
    UIApplicationShortcutIconTypeInvitation     API_AVAILABLE(ios(9.1)),
    UIApplicationShortcutIconTypeConfirmation   API_AVAILABLE(ios(9.1)),
    UIApplicationShortcutIconTypeMail           API_AVAILABLE(ios(9.1)),
    UIApplicationShortcutIconTypeMessage        API_AVAILABLE(ios(9.1)),
    UIApplicationShortcutIconTypeDate           API_AVAILABLE(ios(9.1)),
    UIApplicationShortcutIconTypeTime           API_AVAILABLE(ios(9.1)),
    UIApplicationShortcutIconTypeCapturePhoto   API_AVAILABLE(ios(9.1)),
    UIApplicationShortcutIconTypeCaptureVideo   API_AVAILABLE(ios(9.1)),
    UIApplicationShortcutIconTypeTask           API_AVAILABLE(ios(9.1)),
    UIApplicationShortcutIconTypeTaskCompleted  API_AVAILABLE(ios(9.1)),
    UIApplicationShortcutIconTypeAlarm          API_AVAILABLE(ios(9.1)),
    UIApplicationShortcutIconTypeBookmark       API_AVAILABLE(ios(9.1)),
    UIApplicationShortcutIconTypeShuffle        API_AVAILABLE(ios(9.1)),
    UIApplicationShortcutIconTypeAudio          API_AVAILABLE(ios(9.1)),
    UIApplicationShortcutIconTypeUpdate         API_AVAILABLE(ios(9.1))
} API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(tvos);

UIKIT_EXTERN API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(tvos)
@interface UIApplicationShortcutIcon : NSObject <NSCopying>

// Create an icon using a system-defined image.
+ (instancetype)iconWithType:(UIApplicationShortcutIconType)type;

// Create an icon from a custom image.
// The provided image named will be loaded from the app's bundle
// and will be masked to conform to the system-defined icon style.
+ (instancetype)iconWithTemplateImageName:(NSString *)templateImageName;

// Create an icon using a system image.
// You can use any of the names here that are usable with -systemImageNamed:.
+ (instancetype)iconWithSystemImageName:(NSString *)systemImageName;

@end

UIKIT_EXTERN API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(tvos)
@interface UIApplicationShortcutItem : NSObject <NSCopying, NSMutableCopying>

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithType:(NSString *)type localizedTitle:(NSString *)localizedTitle localizedSubtitle:(nullable NSString *)localizedSubtitle icon:(nullable UIApplicationShortcutIcon *)icon userInfo:(nullable NSDictionary<NSString *, id <NSSecureCoding>> *)userInfo NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithType:(NSString *)type localizedTitle:(NSString *)localizedTitle;

// An application-specific string that identifies the type of action to perform.
@property (nonatomic, copy, readonly) NSString *type;

// Properties controlling how the item should be displayed on the home screen.
@property (nonatomic, copy, readonly) NSString *localizedTitle;
@property (nullable, nonatomic, copy, readonly) NSString *localizedSubtitle;
@property (nullable, nonatomic, copy, readonly) UIApplicationShortcutIcon *icon;

// Application-specific information needed to perform the action.
// Will throw an exception if the NSDictionary is not plist-encodable.
@property (nullable, nonatomic, copy, readonly) NSDictionary<NSString *, id <NSSecureCoding>> *userInfo;

// used with UISceneActivationConditions to customize what scene should be activated for a shortcut
@property (nullable, nonatomic, copy, readonly) id targetContentIdentifier;

@end

UIKIT_EXTERN API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(tvos)
@interface UIMutableApplicationShortcutItem : UIApplicationShortcutItem

// An application-specific string that identifies the type of action to perform.
@property (nonatomic, copy) NSString *type;

// Properties controlling how the item should be displayed on the home screen.
@property (nonatomic, copy) NSString *localizedTitle;
@property (nullable, nonatomic, copy) NSString *localizedSubtitle;
@property (nullable, nonatomic, copy) UIApplicationShortcutIcon *icon;

// Application-specific information needed to perform the action.
// Will throw an exception if the NSDictionary is not plist-encodable.
@property (nullable, nonatomic, copy) NSDictionary<NSString *, id <NSSecureCoding>> *userInfo;

// used with UISceneActivationConditions to customize what scene should be activated for a shortcut
@property (nullable, nonatomic, copy) id targetContentIdentifier;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIApplicationShortcutItem.h>
#endif
