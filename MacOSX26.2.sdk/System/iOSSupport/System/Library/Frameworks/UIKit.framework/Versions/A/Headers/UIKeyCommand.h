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

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunguarded-availability"
UIKIT_EXTERN API_AVAILABLE(ios(7.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIKeyCommand : UICommand
#pragma clang diagnostic pop

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

/// Short display title.
@property (nonatomic, copy) NSString *title API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Image that can appear next to this command.
@property (nullable, nonatomic, copy) UIImage *image API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Elaborated title, if any.
@property (nullable, nonatomic, copy) NSString *discoverabilityTitle API_AVAILABLE(ios(9.0));

/// Action to take on choosing this command.
@property (nullable, nonatomic, readonly) SEL action;

@property (nullable, nonatomic, readonly) NSString *input;
@property (nonatomic, readonly) UIKeyModifierFlags modifierFlags;

/// Property list object to distinguish commands, if needed.
@property (nullable, nonatomic, readonly) id propertyList API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Command attributes.
@property (nonatomic) UIMenuElementAttributes attributes API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// State that can appear next to this command.
@property (nonatomic) UIMenuElementState state API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Alternates that differ in modifier flags, if any.
@property (nonatomic, readonly) NSArray<UICommandAlternate *> *alternates API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Indicates whether the key command should execute if it conflicts with focus or text-editing system commands, defaults to @c NO
@property (nonatomic) BOOL wantsPriorityOverSystemBehavior API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos);

/// Suppose the system detects a given key command that is not reachable in the current keyboard layout; it will localize the key command to something reachable. By setting this property to NO, you will opt-out this menu item from the system-provided localization. YES by default for apps linked against 15.0 and later SDK. 
@property (nonatomic) BOOL allowsAutomaticLocalization API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos);

/// Suppose the system detects a given key command with the following input string [ ] { } ( ) < > ← → in a right-to-left user interface environment (UIUserInterfaceLayoutDirectionRightToLeft); in that case, the system will automatically mirror the key command. For example, a pair of key commands with input { and } will be localized to } and { in a right-to-left user interface. By setting this property to NO, you will opt-out this key command of automatically mirroring in RTL. It would be best only to do this if your action will result in some sort of directional change in the UI, e.g. a segmented control for text alignment or a D-pad in a game. YES by default for apps linked against 15.0 and later SDK.
@property (nonatomic) BOOL allowsAutomaticMirroring API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos);

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
    NS_SWIFT_UNAVAILABLE("Use init(title:image:action:input:modifierFlags:propertyList:alternates:discoverabilityTitle:attributes:state:) instead.") API_UNAVAILABLE(watchos);

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
    NS_SWIFT_UNAVAILABLE("Use init(title:image:action:input:modifierFlags:propertyList:alternates:discoverabilityTitle:attributes:state:) instead.") API_UNAVAILABLE(watchos);

// The action for UIKeyCommands should accept a single (id)sender, as do the UIResponderStandardEditActions above

// Creates an key command that will _not_ be discoverable in the UI.
+ (instancetype)keyCommandWithInput:(NSString *)input modifierFlags:(UIKeyModifierFlags)modifierFlags action:(SEL)action;

// Key Commands with a discoverabilityTitle _will_ be discoverable in the UI.
+ (instancetype)keyCommandWithInput:(NSString *)input modifierFlags:(UIKeyModifierFlags)modifierFlags action:(SEL)action discoverabilityTitle:(NSString *)discoverabilityTitle API_DEPRECATED_WITH_REPLACEMENT("keyCommandWithInput:modifierFlags:action:", ios(9.0, 13.0)) API_UNAVAILABLE(visionos, watchos);

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

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIKeyCommand.h>
#endif
