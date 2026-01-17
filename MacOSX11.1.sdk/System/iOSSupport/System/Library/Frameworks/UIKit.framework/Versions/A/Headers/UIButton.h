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

NS_ASSUME_NONNULL_BEGIN

@class UIImage, UIFont, UIColor, UIImageView, UILabel, UIImageSymbolConfiguration;

typedef NS_ENUM(NSInteger, UIButtonType) {
    UIButtonTypeCustom = 0,                         // no button type
    UIButtonTypeSystem API_AVAILABLE(ios(7.0)),  // standard system button

    UIButtonTypeDetailDisclosure,
    UIButtonTypeInfoLight,
    UIButtonTypeInfoDark,
    UIButtonTypeContactAdd,
    
    UIButtonTypePlain API_AVAILABLE(tvos(11.0)) API_UNAVAILABLE(ios, watchos), // standard system button without the blurred background view
    
    UIButtonTypeClose API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos),
    
    UIButtonTypeRoundedRect = UIButtonTypeSystem   // Deprecated, use UIButtonTypeSystem instead
};

typedef NS_ENUM(NSInteger, UIButtonRole) {
    UIButtonRoleNormal,
    UIButtonRolePrimary,
    UIButtonRoleCancel,
    UIButtonRoleDestructive
} API_AVAILABLE(ios(14.0));

@class UIButton, UIPointerStyle, UIPointerEffect, UIPointerShape;
typedef UIPointerStyle *_Nullable(^UIButtonPointerStyleProvider)(UIButton *button, UIPointerEffect *proposedEffect, UIPointerShape *proposedShape) API_AVAILABLE(ios(13.4)) API_UNAVAILABLE(watchos, tvos);

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) @interface UIButton : UIControl <NSCoding>

- (instancetype)initWithFrame:(CGRect)frame NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

/// Initializes a custom button, registers primaryAction for the UIControlEventPrimaryActionTriggered control event, and uses primaryAction's title & image as the button's title & image.
- (instancetype)initWithFrame:(CGRect)frame primaryAction:(nullable UIAction *)primaryAction API_AVAILABLE(ios(14.0));

+ (instancetype)buttonWithType:(UIButtonType)buttonType;
+ (instancetype)systemButtonWithImage:(UIImage *)image target:(nullable id)target action:(nullable SEL)action API_AVAILABLE(ios(13.0), tvos(13.0), watchos(6.0));
/// Creates a system button, registers primaryAction for the UIControlEventPrimaryActionTriggered control event, and uses primaryAction's title & image as the button's title & image.
+ (instancetype)systemButtonWithPrimaryAction:(nullable UIAction *)primaryAction API_AVAILABLE(ios(14.0));
/// Creates a button of the given type, registers primaryAction for the UIControlEventPrimaryActionTriggered control event, and if appropriate uses primaryAction's title & image as the button's title & image.
+ (instancetype)buttonWithType:(UIButtonType)buttonType primaryAction:(nullable UIAction *)primaryAction API_AVAILABLE(ios(14.0));

@property(nonatomic)          UIEdgeInsets contentEdgeInsets UI_APPEARANCE_SELECTOR; // default is UIEdgeInsetsZero. On tvOS 10 or later, default is nonzero except for custom buttons.
@property(nonatomic)          UIEdgeInsets titleEdgeInsets;                // default is UIEdgeInsetsZero
@property(nonatomic)          BOOL         reversesTitleShadowWhenHighlighted; // default is NO. if YES, shadow reverses to shift between engrave and emboss appearance
@property(nonatomic)          UIEdgeInsets imageEdgeInsets;                // default is UIEdgeInsetsZero
@property(nonatomic)          BOOL         adjustsImageWhenHighlighted;    // default is YES. if YES, image is drawn darker when highlighted(pressed)
@property(nonatomic)          BOOL         adjustsImageWhenDisabled;       // default is YES. if YES, image is drawn lighter when disabled
@property(nonatomic)          BOOL         showsTouchWhenHighlighted API_UNAVAILABLE(tvos);      // default is NO. if YES, show a simple feedback (currently a glow) while highlighted
@property(null_resettable, nonatomic,strong)   UIColor     *tintColor API_AVAILABLE(ios(5.0)); // The tintColor is inherited through the superview hierarchy. See UIView for more information.
@property(nonatomic,readonly) UIButtonType buttonType;

@property (nonatomic) UIButtonRole role API_AVAILABLE(ios(14.0));   // default is UIButtonRoleNormal. 

/// Enables this button's built-in pointer interaction.
@property (nonatomic, readwrite, assign, getter = isPointerInteractionEnabled) BOOL pointerInteractionEnabled API_AVAILABLE(ios(13.4)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @abstract Called when the system pointer hovers over this button if its pointer interaction is enabled. The
 *           system calls this block with a proposed UIPointerEffect and UIPointerShape. You may use them to construct
 *           a customized version of the system provided style or return an entirely custom one.
 */
@property (nonatomic, readwrite, copy, nullable) UIButtonPointerStyleProvider pointerStyleProvider API_AVAILABLE(ios(13.4)) API_UNAVAILABLE(watchos, tvos) NS_REFINED_FOR_SWIFT;

/// An optional menu for the button to display. The button will automatically enable or disable its contextMenuInteraction when a non-nil or nil menu is set. Defaults to nil.
@property (nonatomic, readwrite, copy, nullable) UIMenu *menu API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, tvos);

// you can set the image, title color, title shadow color, and background image to use for each state. you can specify data
// for a combined state by using the flags added together. in general, you should specify a value for the normal state to be used
// by other states which don't have a custom value set

- (void)setTitle:(nullable NSString *)title forState:(UIControlState)state;                     // default is nil. title is assumed to be single line
- (void)setTitleColor:(nullable UIColor *)color forState:(UIControlState)state UI_APPEARANCE_SELECTOR; // default is nil. use opaque white
- (void)setTitleShadowColor:(nullable UIColor *)color forState:(UIControlState)state UI_APPEARANCE_SELECTOR; // default is nil. use 50% black
- (void)setImage:(nullable UIImage *)image forState:(UIControlState)state;                      // default is nil. should be same size if different for different states
- (void)setBackgroundImage:(nullable UIImage *)image forState:(UIControlState)state UI_APPEARANCE_SELECTOR; // default is nil
- (void)setPreferredSymbolConfiguration:(nullable UIImageSymbolConfiguration *)configuration forImageInState:(UIControlState)state UI_APPEARANCE_SELECTOR API_AVAILABLE(ios(13.0), tvos(13.0), watchos(6.0));
- (void)setAttributedTitle:(nullable NSAttributedString *)title forState:(UIControlState)state API_AVAILABLE(ios(6.0)); // default is nil. title is assumed to be single line

- (nullable NSString *)titleForState:(UIControlState)state;          // these getters only take a single state value
- (nullable UIColor *)titleColorForState:(UIControlState)state;
- (nullable UIColor *)titleShadowColorForState:(UIControlState)state;
- (nullable UIImage *)imageForState:(UIControlState)state;
- (nullable UIImage *)backgroundImageForState:(UIControlState)state;
- (nullable UIImageSymbolConfiguration *)preferredSymbolConfigurationForImageInState:(UIControlState)state API_AVAILABLE(ios(13.0), tvos(13.0), watchos(6.0));
- (nullable NSAttributedString *)attributedTitleForState:(UIControlState)state API_AVAILABLE(ios(6.0));

// these are the values that will be used for the current state. you can also use these for overrides. a heuristic will be used to
// determine what image to choose based on the explicit states set. For example, the 'normal' state value will be used for all states
// that don't have their own image defined.

@property(nullable, nonatomic,readonly,strong) NSString *currentTitle;             // normal/highlighted/selected/disabled. can return nil
@property(nonatomic,readonly,strong) UIColor  *currentTitleColor;        // normal/highlighted/selected/disabled. always returns non-nil. default is white(1,1)
@property(nullable, nonatomic,readonly,strong) UIColor  *currentTitleShadowColor;  // normal/highlighted/selected/disabled.
@property(nullable, nonatomic,readonly,strong) UIImage  *currentImage;             // normal/highlighted/selected/disabled. can return nil
@property(nullable, nonatomic,readonly,strong) UIImage  *currentBackgroundImage;   // normal/highlighted/selected/disabled. can return nil
@property(nullable, nonatomic,readonly,strong) UIImageSymbolConfiguration *currentPreferredSymbolConfiguration API_AVAILABLE(ios(13.0), tvos(13.0), watchos(6.0)); // normal/highlighted/selected/disabled. can return nil
@property(nullable, nonatomic,readonly,strong) NSAttributedString *currentAttributedTitle API_AVAILABLE(ios(6.0));  // normal/highlighted/selected/disabled. can return nil

// return title and image views. will always create them if necessary. always returns nil for system buttons
@property(nullable, nonatomic,readonly,strong) UILabel     *titleLabel API_AVAILABLE(ios(3.0));
@property(nullable, nonatomic,readonly,strong) UIImageView *imageView  API_AVAILABLE(ios(3.0));

// these return the rectangle for the background (assumes bounds), the content (image + title) and for the image and title separately. the content rect is calculated based
// on the title and image size and padding and then adjusted based on the control content alignment. there are no draw methods since the contents
// are rendered in separate subviews (UIImageView, UILabel)

- (CGRect)backgroundRectForBounds:(CGRect)bounds;
- (CGRect)contentRectForBounds:(CGRect)bounds;
- (CGRect)titleRectForContentRect:(CGRect)contentRect;
- (CGRect)imageRectForContentRect:(CGRect)contentRect;
@end

@interface UIButton(UIButtonDeprecated)

@property(nonatomic,strong) UIFont         *font              API_DEPRECATED("", ios(2.0, 3.0)) API_UNAVAILABLE(tvos);
@property(nonatomic)        NSLineBreakMode lineBreakMode     API_DEPRECATED("", ios(2.0, 3.0)) API_UNAVAILABLE(tvos);
@property(nonatomic)        CGSize          titleShadowOffset API_DEPRECATED("", ios(2.0, 3.0)) API_UNAVAILABLE(tvos);

@end

#if TARGET_OS_IOS
@interface UIButton (SpringLoading) <UISpringLoadedInteractionSupporting>
@end
#endif

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIButton.h>
#endif
