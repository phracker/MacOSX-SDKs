#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIButton.h>)
//
//  UIButton.h
//  UIKit
//
//  Copyright (c) 2005-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIControl.h>
#import <UIKit/UIGeometry.h>
#import <UIKit/UIStringDrawing.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UISpringLoadedInteractionSupporting.h>
#import <UIKit/UIButtonConfiguration.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UIImage, UIFont, UIColor, UIImageView, UILabel, UIImageSymbolConfiguration;

typedef NS_ENUM(NSInteger, UIButtonType) {
    UIButtonTypeCustom = 0,                         // no button type
    UIButtonTypeSystem API_AVAILABLE(ios(7.0)),  // standard system button

    UIButtonTypeDetailDisclosure,
    UIButtonTypeInfoLight,
    UIButtonTypeInfoDark,
    UIButtonTypeContactAdd,
    
    UIButtonTypePlain API_AVAILABLE(tvos(11.0)) API_UNAVAILABLE(ios, watchos), // standard system button without the blurred background view
    
    UIButtonTypeClose API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos, watchos),
    
    UIButtonTypeRoundedRect = UIButtonTypeSystem   // Deprecated, use UIButtonTypeSystem instead
} API_UNAVAILABLE(watchos);

typedef NS_ENUM(NSInteger, UIButtonRole) {
    UIButtonRoleNormal,
    UIButtonRolePrimary,
    UIButtonRoleCancel,
    UIButtonRoleDestructive
} API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos);

@class UIButton, UIPointerStyle, UIPointerEffect, UIPointerShape;
typedef UIPointerStyle *_Nullable(^UIButtonPointerStyleProvider)(UIButton *button, UIPointerEffect *proposedEffect, UIPointerShape *proposedShape) API_AVAILABLE(ios(13.4)) API_UNAVAILABLE(watchos, tvos);
typedef void (^UIButtonConfigurationUpdateHandler)(__kindof UIButton *button) API_AVAILABLE(ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos);

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIButton : UIControl <NSCoding>

- (instancetype)initWithFrame:(CGRect)frame NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

/// Initializes a custom button, registers primaryAction for the UIControlEventPrimaryActionTriggered control event, and uses primaryAction's title & image as the button's title & image.
- (instancetype)initWithFrame:(CGRect)frame primaryAction:(nullable UIAction *)primaryAction API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos);

+ (instancetype)buttonWithType:(UIButtonType)buttonType;
+ (instancetype)systemButtonWithImage:(UIImage *)image target:(nullable id)target action:(nullable SEL)action API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);
/// Creates a system button, registers primaryAction for the UIControlEventPrimaryActionTriggered control event, and uses primaryAction's title & image as the button's title & image.
+ (instancetype)systemButtonWithPrimaryAction:(nullable UIAction *)primaryAction API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos);
/// Creates a button of the given type, registers primaryAction for the UIControlEventPrimaryActionTriggered control event, and if appropriate uses primaryAction's title & image as the button's title & image.
+ (instancetype)buttonWithType:(UIButtonType)buttonType primaryAction:(nullable UIAction *)primaryAction API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos);

/// Construct a new UIButton. `configuration` will be installed on the created button, and `primaryAction` added to handle the .primaryActionTriggered control event. If `primaryAction` has a title or image, they will be copied to `configuration`
+ (instancetype)buttonWithConfiguration:(UIButtonConfiguration *)configuration primaryAction:(nullable UIAction *)primaryAction API_AVAILABLE(ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos);

/// Setting a non-nil value for `configuration` will opt into configuration-based behavior on UIButton, update the button in a platform specific manner, and enable/disable some API.
@property (nonatomic, readwrite, copy, nullable) UIButtonConfiguration *configuration API_AVAILABLE(ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos);

/// Requests the view update its configuration for its current state. This method is called automatically when the button's state may have changed, as well as in other circumstances where an update may be required. Multiple requests may be coalesced into a single update at the appropriate time.
- (void)setNeedsUpdateConfiguration API_AVAILABLE(ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos);

/// Subclasses should override this method and update the button's `configuration`. This method should not be called directly, use `setNeedsUpdateConfiguration` to request an update.
- (void)updateConfiguration API_AVAILABLE(ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos);

/// Block-based equivalent to overriding -updateConfiguration in a subclass. Setting this handler will force the button into configuration-based behavior (see the `configuration` property). This block is called after `-updateConfiguration`
@property (nonatomic, readwrite, copy, nullable) UIButtonConfigurationUpdateHandler configurationUpdateHandler API_AVAILABLE(ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos);

/// When YES, the button will automatically call -updatedConfigurationForButton: on its `configuration ` when the button's state changes, and apply the updated configuration to the button. The default value is YES.
@property (nonatomic, readwrite, assign) BOOL automaticallyUpdatesConfiguration API_AVAILABLE(ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos);

@property(null_resettable, nonatomic,strong)   UIColor     *tintColor API_AVAILABLE(ios(5.0)); // The tintColor is inherited through the superview hierarchy. See UIView for more information.
@property(nonatomic,readonly) UIButtonType buttonType;

/// If pointer effects are enabled for the button, this will return true when an effect is active.
@property (nonatomic, assign, readonly, getter = isHovered) BOOL hovered API_AVAILABLE(ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos);

/// Returns true while the button is presenting a menu.
@property (nonatomic, assign, readonly, getter = isHeld) BOOL held API_AVAILABLE(ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos);

@property (nonatomic) UIButtonRole role API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos);   // default is UIButtonRoleNormal.

/// Enables this button's built-in pointer interaction.
@property (nonatomic, readwrite, assign, getter = isPointerInteractionEnabled) BOOL pointerInteractionEnabled API_AVAILABLE(ios(13.4)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @abstract Called when the system pointer hovers over this button if its pointer interaction is enabled. The
 *           system calls this block with a proposed UIPointerEffect and UIPointerShape. You may use them to construct
 *           a customized version of the system provided style or return an entirely custom one.
 *           Setting this property automatically enables the button's pointer interaction and sets @c pointerInteractionEnabled to true.
 */
@property (nonatomic, readwrite, copy, nullable) UIButtonPointerStyleProvider pointerStyleProvider API_AVAILABLE(ios(13.4)) API_UNAVAILABLE(watchos, tvos) NS_REFINED_FOR_SWIFT;

/// An optional menu for the button to display. The button will automatically enable or disable its contextMenuInteraction when a non-nil or nil menu is set. Defaults to nil.
@property (nonatomic, readwrite, copy, nullable) UIMenu *menu API_AVAILABLE(ios(14.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/// Preferred menu element ordering strategy for menus displayed by this button.
@property (nonatomic) UIContextMenuConfigurationElementOrder preferredMenuElementOrder API_AVAILABLE(ios(16.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/// Indicates if the button changes selection as its primary action.
/// This shows the menu as options for selection if a menu is populated and showsMenuAsPrimaryAction is enabled.
/// If no menu is provided or it is not the primary action, UIControlStateSelected is toggled on and off for the primary action.
@property (nonatomic, readwrite, assign) BOOL changesSelectionAsPrimaryAction API_AVAILABLE(ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos);

// you can set the image, title color, title shadow color, and background image to use for each state. you can specify data
// for a combined state by using the flags added together. in general, you should specify a value for the normal state to be used
// by other states which don't have a custom value set

- (void)setTitle:(nullable NSString *)title forState:(UIControlState)state;                     // default is nil. title is assumed to be single line
- (void)setTitleColor:(nullable UIColor *)color forState:(UIControlState)state UI_APPEARANCE_SELECTOR; // default is nil. use opaque white
- (void)setTitleShadowColor:(nullable UIColor *)color forState:(UIControlState)state UI_APPEARANCE_SELECTOR; // default is nil. use 50% black
- (void)setImage:(nullable UIImage *)image forState:(UIControlState)state;                      // default is nil. should be same size if different for different states
- (void)setBackgroundImage:(nullable UIImage *)image forState:(UIControlState)state UI_APPEARANCE_SELECTOR; // default is nil
- (void)setPreferredSymbolConfiguration:(nullable UIImageSymbolConfiguration *)configuration forImageInState:(UIControlState)state UI_APPEARANCE_SELECTOR API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);
- (void)setAttributedTitle:(nullable NSAttributedString *)title forState:(UIControlState)state API_AVAILABLE(ios(6.0)); // default is nil. title is assumed to be single line

- (nullable NSString *)titleForState:(UIControlState)state;          // these getters only take a single state value
- (nullable UIColor *)titleColorForState:(UIControlState)state;
- (nullable UIColor *)titleShadowColorForState:(UIControlState)state;
- (nullable UIImage *)imageForState:(UIControlState)state;
- (nullable UIImage *)backgroundImageForState:(UIControlState)state;
- (nullable UIImageSymbolConfiguration *)preferredSymbolConfigurationForImageInState:(UIControlState)state API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);
- (nullable NSAttributedString *)attributedTitleForState:(UIControlState)state API_AVAILABLE(ios(6.0));

// these are the values that will be used for the current state. you can also use these for overrides. a heuristic will be used to
// determine what image to choose based on the explicit states set. For example, the 'normal' state value will be used for all states
// that don't have their own image defined.

@property(nullable, nonatomic,readonly,strong) NSString *currentTitle;             // normal/highlighted/selected/disabled. can return nil
@property(nonatomic,readonly,strong) UIColor  *currentTitleColor;        // normal/highlighted/selected/disabled. always returns non-nil. default is white(1,1)
@property(nullable, nonatomic,readonly,strong) UIColor  *currentTitleShadowColor;  // normal/highlighted/selected/disabled.
@property(nullable, nonatomic,readonly,strong) UIImage  *currentImage;             // normal/highlighted/selected/disabled. can return nil
@property(nullable, nonatomic,readonly,strong) UIImage  *currentBackgroundImage;   // normal/highlighted/selected/disabled. can return nil
@property(nullable, nonatomic,readonly,strong) UIImageSymbolConfiguration *currentPreferredSymbolConfiguration API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos); // normal/highlighted/selected/disabled. can return nil
@property(nullable, nonatomic,readonly,strong) NSAttributedString *currentAttributedTitle API_AVAILABLE(ios(6.0));  // normal/highlighted/selected/disabled. can return nil

// return title and image views. will always create them if necessary. always returns nil for system buttons
@property(nullable, nonatomic,readonly,strong) UILabel     *titleLabel API_AVAILABLE(ios(3.0));
@property(nullable, nonatomic,readonly,strong) UIImageView *imageView  API_AVAILABLE(ios(3.0));
/// The label used to display the subtitle, when present.
@property(nonatomic, readonly, strong, nullable) UILabel *subtitleLabel API_AVAILABLE(ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos);

@end

@interface UIButton(/*UIButtonDeprecated*/)

@property(nonatomic,strong) UIFont         *font              API_DEPRECATED("Specify an attributed title with a custom font", ios(2.0, 3.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos);
@property(nonatomic)        NSLineBreakMode lineBreakMode     API_DEPRECATED("Specify an attributed title with a customized paragraph style", ios(2.0, 3.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos);
@property(nonatomic)        CGSize          titleShadowOffset API_DEPRECATED("Specify an attributed title with a customized shadow style", ios(2.0, 3.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos);

// The effect of these properties can be replicated via UIButtonConfiguration.contentInset and UIButtonConfiguration.imageToTitlePadding. They are ignored when a configuration is set.
@property(nonatomic) UIEdgeInsets contentEdgeInsets API_DEPRECATED("This property is ignored when using UIButtonConfiguration", ios(2.0,15.0), tvos(2.0,15.0), visionos(1.0, 1.0)) UI_APPEARANCE_SELECTOR API_UNAVAILABLE(watchos); // default is UIEdgeInsetsZero. On tvOS 10 or later, default is nonzero except for custom buttons.
@property(nonatomic) UIEdgeInsets titleEdgeInsets API_DEPRECATED("This property is ignored when using UIButtonConfiguration", ios(2.0, 15.0), tvos(2.0, 15.0), visionos(1.0, 1.0)) API_UNAVAILABLE(watchos);                // default is UIEdgeInsetsZero
@property(nonatomic) UIEdgeInsets imageEdgeInsets API_DEPRECATED("This property is ignored when using UIButtonConfiguration", ios(2.0, 15.0), tvos(2.0, 15.0), visionos(1.0, 1.0)) API_UNAVAILABLE(watchos);                // default is UIEdgeInsetsZero

// The effect of these properties can be replicated by providing an appropriate UIButtonConfiguration. They are ignored when a configuration set.
@property(nonatomic) BOOL reversesTitleShadowWhenHighlighted API_DEPRECATED("This property is ignored when using UIButtonConfiguration, you may customize to replicate this behavior via a configurationUpdateHandler", ios(2.0, 15.0), tvos(2.0, 15.0), visionos(1.0, 1.0)) API_UNAVAILABLE(watchos); // default is NO. if YES, shadow reverses to shift between engrave and emboss appearance
@property(nonatomic) BOOL adjustsImageWhenHighlighted API_DEPRECATED("This property is ignored when using UIButtonConfiguration, you may customize to replicate this behavior via a configurationUpdateHandler", ios(2.0, 15.0), tvos(2.0, 15.0), visionos(1.0, 1.0)) API_UNAVAILABLE(watchos);    // default is YES. if YES, image is drawn darker when highlighted(pressed)
@property(nonatomic) BOOL adjustsImageWhenDisabled API_DEPRECATED("This property is ignored when using UIButtonConfiguration, you may customize to replicate this behavior via a configurationUpdateHandler", ios(2.0, 15.0), tvos(2.0, 15.0), visionos(1.0, 1.0)) API_UNAVAILABLE(watchos);       // default is YES. if YES, image is drawn lighter when disabled

// These properties are ignored when a configuration is set and have no replacement.
@property(nonatomic) BOOL showsTouchWhenHighlighted  API_DEPRECATED("This property is ignored when using UIButtonConfiguration", ios(2.0, 15.0), visionos(1.0, 1.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

// These methods will not be called when using a configuration.
// To change the layout of button content, override -layoutSubviews, call super, and then position views as you see fit.
- (CGRect)backgroundRectForBounds:(CGRect)bounds API_DEPRECATED("Override layoutSubviews, call super, and position views as you desire.", ios(2.0, 15.0), tvos(2.0, 15.0), visionos(1.0, 1.0)) API_UNAVAILABLE(watchos);
- (CGRect)contentRectForBounds:(CGRect)bounds API_DEPRECATED("Override layoutSubviews, call super, and position views as you desire.", ios(2.0, 15.0), tvos(2.0, 15.0), visionos(1.0, 1.0)) API_UNAVAILABLE(watchos);
- (CGRect)titleRectForContentRect:(CGRect)contentRect API_DEPRECATED("Override layoutSubviews, call super, and position views as you desire.", ios(2.0, 15.0), tvos(2.0, 15.0), visionos(1.0, 1.0)) API_UNAVAILABLE(watchos);
- (CGRect)imageRectForContentRect:(CGRect)contentRect API_DEPRECATED("Override layoutSubviews, call super, and position views as you desire.", ios(2.0, 15.0), tvos(2.0, 15.0), visionos(1.0, 1.0)) API_UNAVAILABLE(watchos);

@end

#if TARGET_OS_IOS
@interface UIButton (SpringLoading) <UISpringLoadedInteractionSupporting>
@end
#endif

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIButton.h>
#endif
