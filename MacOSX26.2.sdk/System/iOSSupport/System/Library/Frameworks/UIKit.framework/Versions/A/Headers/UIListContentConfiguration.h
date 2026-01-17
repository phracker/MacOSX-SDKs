#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIListContentConfiguration.h>)
//
//  UIListContentConfiguration.h
//  UIKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <UIKit/UIContentConfiguration.h>
#import <UIKit/UIListContentImageProperties.h>
#import <UIKit/UIListContentTextProperties.h>
#import <UIKit/UIGeometry.h>
#import <UIKit/UIView.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN API_AVAILABLE(ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIListContentConfiguration : NSObject <UIContentConfiguration, NSSecureCoding>

/// Returns the default configuration for a list cell.
/// From iOS 18 onwards, the configuration will automatically adopt the appropriate style for a list when updating for a
/// new configuration state, by reading the `listEnvironment` trait from the state's trait collection.
/// Defaults to a cell in a plain-style list.
+ (instancetype)cellConfiguration;

/// Returns the default configuration for a list cell with subtitle text.
/// From iOS 18 onwards, the configuration will automatically adopt the appropriate style for a list when updating for a
/// new configuration state, by reading the `listEnvironment` trait from the state's trait collection.
/// Defaults to a subtitle cell in a plain-style list.
+ (instancetype)subtitleCellConfiguration;

/// Returns the default configuration for a list cell with side-by-side value text.
/// From iOS 18 onwards, the configuration will automatically adopt the appropriate style for a list when updating for a
/// new configuration state, by reading the `listEnvironment` trait from the state's trait collection.
/// Defaults to the appearance of a value cell in a plain-style list.
+ (instancetype)valueCellConfiguration;

/// Represents a generic header configuration that automatically adopts the style of a containing list when updating for a
/// new configuration state, by reading the `listEnvironment` trait from the state's trait collection.
/// Defaults to the header configuration for a plain-style list.
+ (instancetype)headerConfiguration API_AVAILABLE(ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos);

/// Represents a generic footer configuration that automatically adopts the style of a containing list when updating for a
/// new configuration state, by reading the `listEnvironment` trait from the state's trait collection.
/// Defaults to the footer configuration for a plain-style list.
+ (instancetype)footerConfiguration API_AVAILABLE(ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos);


/// Returns the default configuration for a prominent inset grouped list header.
+ (instancetype)prominentInsetGroupedHeaderConfiguration API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(tvos, watchos);
/// Returns the default configuration for an extra prominent inset grouped list header.
+ (instancetype)extraProminentInsetGroupedHeaderConfiguration API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(tvos, watchos);

/// Returns the default configuration for an accompanied sidebar list cell.
+ (instancetype)accompaniedSidebarCellConfiguration API_UNAVAILABLE(tvos, watchos);
/// Returns the default configuration for an accompanied sidebar list cell with subtitle text.
+ (instancetype)accompaniedSidebarSubtitleCellConfiguration API_UNAVAILABLE(tvos, watchos);

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// The image to display.
@property (nonatomic, strong, nullable) UIImage *image;
/// Additional properties to configure the image.
@property (nonatomic, readonly) UIListContentImageProperties *imageProperties;

/// The primary text.
@property (nonatomic, copy, nullable) NSString *text;
/// An attributed variant of the primary text, which supersedes the `text` and some properties of the `textProperties` if set.
@property (nonatomic, copy, nullable) NSAttributedString *attributedText;
/// Additional properties to configure the primary text.
@property (nonatomic, readonly) UIListContentTextProperties *textProperties;

/// The secondary text.
@property (nonatomic, copy, nullable) NSString *secondaryText;
/// An attributed variant of the secondary text, which supersedes the `secondaryText` and some properties of the `secondaryTextProperties` if set.
@property (nonatomic, copy, nullable) NSAttributedString *secondaryAttributedText;
/// Additional properties to configure the secondary text.
@property (nonatomic, readonly) UIListContentTextProperties *secondaryTextProperties;

/// Whether the content view will preserve inherited layout margins from its superview on the horizontal and/or vertical axes.
@property (nonatomic) UIAxis axesPreservingSuperviewLayoutMargins;
/// The margins for the content to the edges of the content view. (When preserving superview layout margins on one or both axes, these are just minimum margins, as inherited margins may be larger.)
@property (nonatomic) NSDirectionalEdgeInsets directionalLayoutMargins;

/// When YES, the text and secondary text will be positioned side-by-side if there is sufficient space. Otherwise, the text will be stacked in a vertical layout.
@property (nonatomic) BOOL prefersSideBySideTextAndSecondaryText;

/// Padding between the image and text. Only applies when there is both an image and text.
@property (nonatomic) CGFloat imageToTextPadding;
/// Horizontal (minimum) padding between the text and secondary text. Only applies when there is both text and secondary text, and they are in a side-by-side layout.
@property (nonatomic) CGFloat textToSecondaryTextHorizontalPadding;
/// Vertical padding between the text and secondary text. Only applies when there is both text and secondary text, and they are in a stacked layout.
@property (nonatomic) CGFloat textToSecondaryTextVerticalPadding;

/// The alpha to apply to the entire content view. Defaults to 1.0.
@property (nonatomic) CGFloat alpha API_AVAILABLE(ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos);

// Deprecated declarations

/// Returns the default configuration for a sidebar list cell.
+ (instancetype)sidebarCellConfiguration API_DEPRECATED_WITH_REPLACEMENT("cellConfiguration", ios(14.0, 18.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);
/// Returns the default configuration for a sidebar list cell with subtitle text.
+ (instancetype)sidebarSubtitleCellConfiguration API_DEPRECATED_WITH_REPLACEMENT("subtitleCellConfiguration", ios(14.0, 18.0)) API_UNAVAILABLE(tvos, watchos);
/// Returns the default configuration for a plain list header.
+ (instancetype)plainHeaderConfiguration API_DEPRECATED_WITH_REPLACEMENT("headerConfiguration", ios(14.0, 18.0), tvos(14.0, 18.0)) API_UNAVAILABLE(watchos);
/// Returns the default configuration for a plain list footer.
+ (instancetype)plainFooterConfiguration API_DEPRECATED_WITH_REPLACEMENT("footerConfiguration", ios(14.0, 18.0), tvos(14.0, 18.0)) API_UNAVAILABLE(watchos);
/// Returns the default configuration for a grouped list header.
+ (instancetype)groupedHeaderConfiguration API_DEPRECATED_WITH_REPLACEMENT("headerConfiguration", ios(14.0, 18.0), tvos(14.0, 18.0)) API_UNAVAILABLE(watchos);
/// Returns the default configuration for a grouped list footer.
+ (instancetype)groupedFooterConfiguration API_DEPRECATED_WITH_REPLACEMENT("footerConfiguration", ios(14.0, 18.0), tvos(14.0, 18.0)) API_UNAVAILABLE(watchos);
/// Returns the default configuration for a sidebar list header.
+ (instancetype)sidebarHeaderConfiguration API_DEPRECATED_WITH_REPLACEMENT("headerConfiguration", ios(14.0, 18.0)) API_UNAVAILABLE(tvos, watchos);

@end

UIKIT_EXTERN API_AVAILABLE(ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIListContentView : UIView <UIContentView>

- (instancetype)initWithConfiguration:(UIListContentConfiguration *)configuration NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithFrame:(CGRect)frame NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic, copy) UIListContentConfiguration *configuration;

/// This guide reflects the positioning of the primary text rendered by this content view, if specified by the configuration.
///
/// Returns nil if there is no primary text. If a new configuration is applied that does not contain primary text, then this layout
/// guide is removed from the view, and any constraints associated with it will be deactivated.
@property (nonatomic, strong, readonly, nullable) UILayoutGuide *textLayoutGuide;

/// This guide reflects the positioning of the secondary text rendered by this content view, if specified by the configuration.
///
/// Returns nil if there is no secondary text. If a new configuration is applied that does not contain secondary text, then this layout
/// guide is removed from the view, and any constraints associated with it will be deactivated.
@property (nonatomic, strong, readonly, nullable) UILayoutGuide *secondaryTextLayoutGuide;

/// This guide reflects the positioning of the image rendered by this content view, if specified by the configuration.
/// 
/// Returns nil if there is no image. If a new configuration is applied that does contain an image, then this layout
/// guide is removed from the view, and any constraints associated with it will be deactivated.
@property (nonatomic, strong, readonly, nullable) UILayoutGuide *imageLayoutGuide;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIListContentConfiguration.h>
#endif
