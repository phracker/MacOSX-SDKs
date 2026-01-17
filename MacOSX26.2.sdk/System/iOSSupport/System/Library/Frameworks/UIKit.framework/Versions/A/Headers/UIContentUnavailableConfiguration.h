#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIContentUnavailableConfiguration.h>)
//
//  UIContentUnavailableConfiguration.h
//  UIKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <UIKit/UIContentConfiguration.h>
#import <UIKit/UIContentUnavailableImageProperties.h>
#import <UIKit/UIContentUnavailableTextProperties.h>
#import <UIKit/UIContentUnavailableButtonProperties.h>
#import <UIKit/UIBackgroundConfiguration.h>
#import <UIKit/UIGeometry.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NS_ENUM(NSInteger, UIContentUnavailableAlignment) {
    UIContentUnavailableAlignmentCenter,
    UIContentUnavailableAlignmentNatural
} API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);

UIKIT_EXTERN API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIContentUnavailableConfiguration : NSObject <UIContentConfiguration, NSSecureCoding>

/// Returns the default configuration for unavailable content.
+ (instancetype)emptyConfiguration;
/// Returns the default configuration for content which is loading.
+ (instancetype)loadingConfiguration;
/// Returns the default configuration for searches which return no results.
+ (instancetype)searchConfiguration;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// The image to display.
@property (nonatomic, strong, nullable) UIImage *image;
/// Additional properties to configure the image. When adopting the loading configuration, relevant properties are applied to the activity indicator.
@property (nonatomic, readonly) UIContentUnavailableImageProperties *imageProperties;

/// The primary text.
@property (nonatomic, copy, nullable) NSString *text;
/// An attributed variant of the primary text, which supersedes the `text` and some properties of the `textProperties` if set.
@property (nonatomic, copy, nullable) NSAttributedString *attributedText;
/// Additional properties to configure the primary text.
@property (nonatomic, readonly) UIContentUnavailableTextProperties *textProperties;

/// The secondary text.
@property (nonatomic, copy, nullable) NSString *secondaryText;
/// An attributed variant of the secondary text, which supersedes the `secondaryText` and some properties of the `secondaryTextProperties` if set.
@property (nonatomic, copy, nullable) NSAttributedString *secondaryAttributedText;
/// Additional properties to configure the secondary text.
@property (nonatomic, readonly) UIContentUnavailableTextProperties *secondaryTextProperties;

/// The primary button.
@property (nonatomic, strong) UIButtonConfiguration *button;
/// Additional properties to configure the primary button.
@property (nonatomic, readonly) UIContentUnavailableButtonProperties *buttonProperties;

/// The secondary button.
@property (nonatomic, strong) UIButtonConfiguration *secondaryButton;
/// Additional properties to configure the secondary button.
@property (nonatomic, readonly) UIContentUnavailableButtonProperties *secondaryButtonProperties;

/// The alignment of the image, text and buttons.
@property (nonatomic) UIContentUnavailableAlignment alignment;
/// Whether the content view will preserve inherited layout margins from its superview on the horizontal and/or vertical axes.
@property (nonatomic) UIAxis axesPreservingSuperviewLayoutMargins;
/// The margins for the content to the edges of the content view. (When preserving superview layout margins on one or both axes, these are just minimum margins, as inherited margins may be larger.)
@property (nonatomic) NSDirectionalEdgeInsets directionalLayoutMargins;

/// Padding between the image and text. Only applies when there is both an image and text.
@property (nonatomic) CGFloat imageToTextPadding;
/// Padding between the text and secondary text. Only applies when there is both text and secondary text.
@property (nonatomic) CGFloat textToSecondaryTextPadding;
/// Padding between the button and text. Only applies when there is both a button and text.
@property (nonatomic) CGFloat textToButtonPadding;
/// Padding between the button and secondary button. Only applies when there is both a button and a secondary button.
@property (nonatomic) CGFloat buttonToSecondaryButtonPadding;

/// The background configuration.
@property (nonatomic, strong) UIBackgroundConfiguration *background;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIContentUnavailableConfiguration.h>
#endif
