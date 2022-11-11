#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UICommand.h>)
//
//  UICommand.h
//  UIKit
//
//  Copyright (c) 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIMenuElement.h>
#import <UIKit/UIMenu.h>

typedef NS_OPTIONS(NSInteger, UIKeyModifierFlags) {
    UIKeyModifierAlphaShift     = 1 << 16,  // This bit indicates CapsLock
    UIKeyModifierShift          = 1 << 17,
    UIKeyModifierControl        = 1 << 18,
    UIKeyModifierAlternate      = 1 << 19,
    UIKeyModifierCommand        = 1 << 20,
    UIKeyModifierNumericPad     = 1 << 21,
} API_AVAILABLE(ios(7.0));

@class UICommand;
@class UIImage;

NS_ASSUME_NONNULL_BEGIN

/// Represents an alternate action to take for a command.
///
/// Two alternates are equal iff their modifierFlags are equal.
UIKIT_EXTERN API_AVAILABLE(ios(13.0)) NS_SWIFT_UI_ACTOR
@interface UICommandAlternate : NSObject <NSCopying, NSSecureCoding>

/// Short display title.
@property (nonatomic, readonly) NSString *title;

/// Action to take on choosing this command alternate.
@property (nonatomic, readonly) SEL action;

/// Bitmask of modifier flags to choose this command alternate.
@property (nonatomic, readonly) UIKeyModifierFlags modifierFlags;

/// Initialize an alternate action to take for a command.
///
/// @param title Short display title. This should be localized.
/// @param action Action to take on choosing this command alternate.
/// @param modifierFlags Bitmask of modifier flags to choose this command alternate.
/// @return A new command alternate.
+ (instancetype)alternateWithTitle:(NSString *)title
                            action:(SEL)action
                     modifierFlags:(UIKeyModifierFlags)modifierFlags;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

@end

/// Represents an action to take.
UIKIT_EXTERN API_AVAILABLE(ios(13.0)) NS_SWIFT_UI_ACTOR
@interface UICommand : UIMenuElement

/// Short display title.
@property (nonatomic, copy) NSString *title;

/// Image that can appear next to this command
@property (nullable, nonatomic, copy) UIImage *image;

/// Elaborated title, if any.
@property (nullable, nonatomic, copy) NSString *discoverabilityTitle;

/// Action to take on choosing this command.
@property (nonatomic, readonly) SEL action;

/// Property list object to distinguish commands, if needed.
@property (nullable, nonatomic, readonly) id propertyList;

/// Command attributes.
@property (nonatomic) UIMenuElementAttributes attributes;

/// State that can appear next to the command.
@property (nonatomic) UIMenuElementState state;

/// Alternates that differ in modifier flags, if any.
@property (nonatomic, readonly) NSArray<UICommandAlternate *> *alternates;

/// Initializes a keyless command.
///
/// @param title Short display title. This should be localized.
/// @param image Image that can appear next to this command, if needed.
/// @param action Action to take on choosing this command.
/// @param propertyList Property list object to distinguish commands, if needed.
/// @return A new keyless command.
+ (instancetype)commandWithTitle:(NSString *)title
                           image:(nullable UIImage *)image
                          action:(SEL)action
                    propertyList:(nullable id)propertyList
    NS_SWIFT_UNAVAILABLE("Use init(title:image:action:propertyList:alternates:discoverabilityTitle:attributes:state:) instead.");

/// Initializes a keyless command with alternates.
///
/// @param title Short display title. This should be localized.
/// @param image Image that can appear next to this command, if needed.
/// @param action Action to take on choosing this command.
/// @param propertyList Property list object to distinguish commands, if needed.
/// @param alternates Alternates that differ in modifier flags.
/// @return A new keyless command with alternates.
+ (instancetype)commandWithTitle:(NSString *)title
                           image:(nullable UIImage *)image
                          action:(SEL)action
                    propertyList:(nullable id)propertyList
                      alternates:(NSArray<UICommandAlternate *> *)alternates
    NS_SWIFT_UNAVAILABLE("Use init(title:image:action:propertyList:alternates:discoverabilityTitle:attributes:state:) instead.");

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

@end

// UICommand.propertyList value to indicate that a command is a Sharing menu item. Such an item automatically receives a standard Share submenu.
UIKIT_EXTERN NSString *const UICommandTagShare API_AVAILABLE(ios(13.0));

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UICommand.h>
#endif
