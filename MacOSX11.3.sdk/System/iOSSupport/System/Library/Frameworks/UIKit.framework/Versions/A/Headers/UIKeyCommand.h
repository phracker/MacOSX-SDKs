#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIKeyCommand.h>)
//
//  UIKeyCommand.h
//  UIKit
//
//  Copyright (c) 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UICommand.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunguarded-availability"
UIKIT_EXTERN API_AVAILABLE(ios(7.0)) @interface UIKeyCommand : UICommand
#pragma clang diagnostic pop

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

/// Short display title.
@property (nonatomic, copy) NSString *title API_AVAILABLE(ios(13.0));

/// Image that can appear next to this command.
@property (nullable, nonatomic, copy) UIImage *image API_AVAILABLE(ios(13.0));

/// Elaborated title, if any.
@property (nullable, nonatomic, copy) NSString *discoverabilityTitle API_AVAILABLE(ios(9.0));

/// Action to take on choosing this command.
@property (nullable, nonatomic, readonly) SEL action;

@property (nullable, nonatomic, readonly) NSString *input;
@property (nonatomic, readonly) UIKeyModifierFlags modifierFlags;

/// Property list object to distinguish commands, if needed.
@property (nullable, nonatomic, readonly) id propertyList API_AVAILABLE(ios(13.0));

/// Command attributes.
@property (nonatomic) UIMenuElementAttributes attributes API_AVAILABLE(ios(13.0));

/// State that can appear next to this command.
@property (nonatomic) UIMenuElementState state API_AVAILABLE(ios(13.0));

/// Alternates that differ in modifier flags, if any.
@property (nonatomic, readonly) NSArray<UICommandAlternate *> *alternates API_AVAILABLE(ios(13.0));

/// Initializes a key command.
///
/// @param title Short display title. This should be localized.
/// @param image Image that can appear next to this command, if needed.
/// @param action Action to take on choosing this command.
/// @param input Keys that must be pressed to choose this command.
/// @param modifierFlags Bit mask of key modifier flags to choose this command.
/// @param propertyList Property list object to distinguish commands, if needed.
/// @return A new key command.
+ (instancetype)commandWithTitle:(NSString *)title
                           image:(nullable UIImage *)image
                          action:(SEL)action
                           input:(NSString *)input
                   modifierFlags:(UIKeyModifierFlags)modifierFlags
                    propertyList:(nullable id)propertyList
    NS_SWIFT_UNAVAILABLE("Use init(title:image:action:input:modifierFlags:propertyList:alternates:discoverabilityTitle:attributes:state:) instead.");

/// Initializes a key command with alternates.
///
/// @param title Short display title. This should be localized.
/// @param image Image that can appear next to this command, if needed.
/// @param action Action to take on choosing this command.
/// @param input Keys that must be pressed to choose this command.
/// @param modifierFlags Bit mask of key modifier flags to choose this command.
/// @param propertyList Property list object to distinguish commands, if needed.
/// @param alternates Alternates that differ in modifier flags.
/// @return A new key command.
+ (instancetype)commandWithTitle:(NSString *)title
                           image:(nullable UIImage *)image
                          action:(SEL)action
                           input:(NSString *)input
                   modifierFlags:(UIKeyModifierFlags)modifierFlags
                    propertyList:(nullable id)propertyList
                      alternates:(NSArray<UICommandAlternate *> *)alternates
    NS_SWIFT_UNAVAILABLE("Use init(title:image:action:input:modifierFlags:propertyList:alternates:discoverabilityTitle:attributes:state:) instead.");

// The action for UIKeyCommands should accept a single (id)sender, as do the UIResponderStandardEditActions above

// Creates an key command that will _not_ be discoverable in the UI.
+ (instancetype)keyCommandWithInput:(NSString *)input modifierFlags:(UIKeyModifierFlags)modifierFlags action:(SEL)action;

// Key Commands with a discoverabilityTitle _will_ be discoverable in the UI.
+ (instancetype)keyCommandWithInput:(NSString *)input modifierFlags:(UIKeyModifierFlags)modifierFlags action:(SEL)action discoverabilityTitle:(NSString *)discoverabilityTitle API_DEPRECATED_WITH_REPLACEMENT("keyCommandWithInput:modifierFlags:action:", ios(9.0, 13.0));

// UICommand initializers are unavailable
+ (instancetype)commandWithTitle:(NSString *)title
                           image:(nullable UIImage *)image
                          action:(SEL)action
                    propertyList:(nullable id)propertyList NS_UNAVAILABLE;
+ (instancetype)commandWithTitle:(NSString *)title
                           image:(nullable UIImage *)image
                          action:(SEL)action
                    propertyList:(nullable id)propertyList
                      alternates:(NSArray<UICommandAlternate *> *)alternates NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIKeyCommand.h>
#endif
