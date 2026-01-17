#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIButtonConfiguration.h>)
//
//  UIButtonConfiguration.h
//  UIKit
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIBackgroundConfiguration.h>
#import <UIKit/NSParagraphStyle.h>

@class UIImageSymbolConfiguration;
@class UIButton;
@class UIImage;
@class UISymbolContentTransition;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NSDictionary<NSAttributedStringKey, id> *_Nonnull (^/*NS_SWIFT_SENDABLE*/ UIConfigurationTextAttributesTransformer)(NSDictionary<NSAttributedStringKey, id> *textAttributes) API_AVAILABLE(ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos);

typedef NS_ENUM(NSInteger, UIButtonConfigurationSize) {
    UIButtonConfigurationSizeMedium,
    UIButtonConfigurationSizeSmall,
    UIButtonConfigurationSizeMini,
    UIButtonConfigurationSizeLarge,
} API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos);

typedef NS_ENUM(NSInteger, UIButtonConfigurationTitleAlignment) {
    /// Align title & subtitle automatically
    UIButtonConfigurationTitleAlignmentAutomatic,
    /// Align title & subtitle along their leading edges
    UIButtonConfigurationTitleAlignmentLeading,
    /// Align title & subtitle to be centered with respect to each other
    UIButtonConfigurationTitleAlignmentCenter,
    /// Align title & subtitle along their trailing edges
    UIButtonConfigurationTitleAlignmentTrailing,
} API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos);

typedef NS_ENUM(NSInteger, UIButtonConfigurationCornerStyle) {
    /// The corner radius provided by the background style will be used as is, without adjusting for dynamic type
    UIButtonConfigurationCornerStyleFixed = -1,
    /// The corner radius provided by the background style is adjusted based on dynamic type
    UIButtonConfigurationCornerStyleDynamic,
    /// Ignore the corner radius provided by the background style and substitute a small system defined corner radius.
    UIButtonConfigurationCornerStyleSmall,
    /// Ignore the corner radius provided by the background style and substitute a medium system defined corner radius.
    UIButtonConfigurationCornerStyleMedium,
    /// Ignore the corner radius provided by the background style and substitute a large system defined corner radius.
    UIButtonConfigurationCornerStyleLarge,
    /// Ignore the corner radius provided by the background style and always set the corner radius to generate a capsule.
    UIButtonConfigurationCornerStyleCapsule,
} API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos);

typedef NS_ENUM(NSInteger, UIButtonConfigurationMacIdiomStyle) {
    /// Automatically select the style to use
    UIButtonConfigurationMacIdiomStyleAutomatic,
    /// Always use a bordered style button
    UIButtonConfigurationMacIdiomStyleBordered,
    /// Always use a borderless style button
    UIButtonConfigurationMacIdiomStyleBorderless,
    /// Always use a tinted, borderless style button
    UIButtonConfigurationMacIdiomStyleBorderlessTinted,
} API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos);

typedef NS_ENUM(NSInteger, UIButtonConfigurationIndicator) {
    /// Automatically determine an indicator based on the button's properties.
    UIButtonConfigurationIndicatorAutomatic,
    /// Don't show any indicator
    UIButtonConfigurationIndicatorNone,
    /// Show an indicator appropriate for a popup-style button
    UIButtonConfigurationIndicatorPopup,
} API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos);

UIKIT_EXTERN API_AVAILABLE(ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIButtonConfiguration : NSObject <NSCopying, NSSecureCoding>

+ (instancetype)plainButtonConfiguration;
+ (instancetype)tintedButtonConfiguration;
+ (instancetype)grayButtonConfiguration;
+ (instancetype)filledButtonConfiguration;

+ (instancetype)borderlessButtonConfiguration;
+ (instancetype)borderedButtonConfiguration;
+ (instancetype)borderedTintedButtonConfiguration;
+ (instancetype)borderedProminentButtonConfiguration;

+ (instancetype)glassButtonConfiguration API_AVAILABLE(ios(26.0), tvos(26.0)) API_UNAVAILABLE(watchos, visionos);
+ (instancetype)prominentGlassButtonConfiguration API_AVAILABLE(ios(26.0), tvos(26.0)) API_UNAVAILABLE(watchos, visionos);
+ (instancetype)clearGlassButtonConfiguration API_AVAILABLE(ios(26.0), tvos(26.0)) API_UNAVAILABLE(watchos, visionos);
+ (instancetype)prominentClearGlassButtonConfiguration API_AVAILABLE(ios(26.0), tvos(26.0)) API_UNAVAILABLE(watchos, visionos);

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// Returns a copy of the configuration updated based on the given button, by applying the configuration's default values for that button's state to any properties that have not been customized.
- (instancetype)updatedConfigurationForButton:(UIButton *)button;

/// A UIBackgroundConfiguration describing the button's background. UIKit provides a value by default with values appropriate for a UIButton.
@property (nonatomic, readwrite, strong) UIBackgroundConfiguration *background;

/// The corner style controls how background.cornerRadius is interpreted by the button. Defaults to `Dynamic`.
@property (nonatomic, readwrite, assign) UIButtonConfigurationCornerStyle cornerStyle;

/// Determines the metrics and ideal size of the button. Clients may resize the button arbitrarily regardless of this value.
@property (nonatomic, readwrite, assign) UIButtonConfigurationSize buttonSize;

// Button style to use when running under the Mac idiom.
@property (nonatomic, readwrite, assign) UIButtonConfigurationMacIdiomStyle macIdiomStyle;

/// The base color to use for foreground elements. This color may be modified before being passed to a transformer, and finally applied to specific elements. Setting nil will cede full control to the configuration to select a color appropriate to the style.
@property (nonatomic, readwrite, strong, nullable) UIColor *baseForegroundColor;

/// The base color to use for background elements. This color may be modified before being passed to a transformer, and finally applied to specific elements. Setting nil will cede full control to the configuration to select a color appropriate to the style.
@property (nonatomic, readwrite, strong, nullable) UIColor *baseBackgroundColor;

@property (nonatomic, readwrite, strong, nullable) UIImage *image;
@property (nonatomic, readwrite, copy, nullable) UIConfigurationColorTransformer imageColorTransformer;
@property (nonatomic, readwrite, copy, nullable) UIImageSymbolConfiguration *preferredSymbolConfigurationForImage;

/// The symbol content transition to use when transitioning across symbol images.
/// Defaults to `nil`, meaning no symbol content transition should occur.
@property (nonatomic, readwrite, strong, nullable) UISymbolContentTransition *symbolContentTransition API_AVAILABLE(ios(26.0), tvos(26.0)) API_UNAVAILABLE(watchos);

/// Shows an activity indicator in place of an image. Its placement is controlled by the imagePlacement property.
@property (nonatomic, readwrite, assign) BOOL showsActivityIndicator;
@property (nonatomic, readwrite, copy, nullable) UIConfigurationColorTransformer activityIndicatorColorTransformer;

@property (nonatomic, readwrite, copy, nullable) NSString *title;
@property (nonatomic, readwrite, copy, nullable) NSAttributedString *attributedTitle;
@property (nonatomic, readwrite, copy, nullable) UIConfigurationTextAttributesTransformer titleTextAttributesTransformer;
/// Default is WordWrapping. WordWrapping and CharWrapping both allow for multi-line text, other modes will restrict the title to a single line of text.
@property (nonatomic, readwrite, assign) NSLineBreakMode titleLineBreakMode;

@property (nonatomic, readwrite, copy, nullable) NSString *subtitle;
@property (nonatomic, readwrite, copy, nullable) NSAttributedString *attributedSubtitle;
@property (nonatomic, readwrite, copy, nullable) UIConfigurationTextAttributesTransformer subtitleTextAttributesTransformer;
/// Default is WordWrapping. WordWrapping and CharWrapping both allow for multi-line text, other modes will restrict the subtitle to a single line of text.
@property (nonatomic, readwrite, assign) NSLineBreakMode subtitleLineBreakMode;

/// What kind of indicator should the button show. Default value is .automatic.
@property (nonatomic, readwrite, assign) UIButtonConfigurationIndicator indicator API_AVAILABLE(ios(16.0));
@property (nonatomic, readwrite, copy, nullable) UIConfigurationColorTransformer indicatorColorTransformer API_AVAILABLE(ios(16.0));

/// Insets from the bounds of the button to create the content region. Defaults styles provide insets based on the button size.
@property (nonatomic, readwrite, assign) NSDirectionalEdgeInsets contentInsets;
/// Restore the default content insets.
- (void)setDefaultContentInsets;
/// Defaults to Leading, only single edge values (top/leading/bottom/trailing) are supported.
@property (nonatomic, readwrite, assign) NSDirectionalRectEdge imagePlacement;
/// When a button has both image and text content, this value is the padding between the image and the text.
@property (nonatomic, readwrite, assign) CGFloat imagePadding;
/// When a button has both a title & subtitle, this value is the padding between those titles.
@property (nonatomic, readwrite, assign) CGFloat titlePadding;
/// The alignment to use for relative layout between title & subtitle.
@property (nonatomic, readwrite, assign) UIButtonConfigurationTitleAlignment titleAlignment;
/// If the style should automatically update when the button is selected. Default varies by style. Disable to customize selection behavior.
@property (nonatomic, readwrite, assign) BOOL automaticallyUpdateForSelection;

@end



NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIButtonConfiguration.h>
#endif
