#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIBackgroundConfiguration.h>)
//
//  UIBackgroundConfiguration.h
//  UIKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <UIKit/UIGeometry.h>
#import <UIKit/UIConfigurationColorTransformer.h>
#import <UIKit/UIView.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@protocol UIConfigurationState;
@class UIVisualEffect;
@class UIImage;
@class UIShadowProperties;

UIKIT_EXTERN API_AVAILABLE(ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIBackgroundConfiguration : NSObject <NSCopying, NSSecureCoding>

/// Returns a clear configuration, with no default styling.
+ (instancetype)clearConfiguration;

/// Represents a generic cell background configuration that automatically adopts the style of a containing list when updated for a
/// new configuration state, by reading the `listEnvironment` trait from the state's trait collection.
/// Defaults to the background configuration for a cell in a plain-style list.
+ (instancetype)listCellConfiguration API_AVAILABLE(ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos);

/// Represents a generic header background configuration that automatically adopts the style of a containing list when updated for a
/// new configuration state, by reading the `listEnvironment` trait from the state's trait collection.
/// Defaults to the background configuration for a header in a plain-style list.
+ (instancetype)listHeaderConfiguration API_AVAILABLE(ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos);

/// Represents a generic footer background configuration that automatically adopts the style of a containing list when updated for a
/// new configuration state, by reading the `listEnvironment` trait from the state's trait collection.
/// Defaults to the background configuration for a footer in a plain-style list.
+ (instancetype)listFooterConfiguration API_AVAILABLE(ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos);

/// Returns the default configuration for an accompanied sidebar list cell.
+ (instancetype)listAccompaniedSidebarCellConfiguration API_UNAVAILABLE(tvos, watchos);

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// Returns a copy of the configuration updated for the specified state, by applying the configuration's default values for that state to any properties that have not been customized.
- (instancetype)updatedConfigurationForState:(id<UIConfigurationState>)state;


/// A custom view for the background. The custom view must have translatesAutoresizingMaskIntoConstraints
/// enabled, but may use auto layout constraints internally for layout of subviews.
@property (nonatomic, strong, nullable) UIView *customView;

/// The preferred corner radius (using a continuous corner curve) for the background and stroke. This is also applied to the custom view. Default is 0.
/// If the view is too small to fit the requested radius, the corner curve and radius will be adjusted to fit.
@property (nonatomic) CGFloat cornerRadius;

/// Insets (or outsets, if negative) for the background and stroke, relative to the edges of the containing view. These also apply to the custom view. Default is NSDirectionalEdgeInsetsZero.
@property (nonatomic) NSDirectionalEdgeInsets backgroundInsets;
/// The edges on which the containing view's layout margins are added to the `backgroundInsets`, effectively making the `backgroundInsets` values relative
/// to the containing view's layout margins for these edges. Default is NSDirectionalRectEdgeNone.
@property (nonatomic) NSDirectionalRectEdge edgesAddingLayoutMarginsToBackgroundInsets;

// Background (Fill)

/// Configures the color of the background. A nil value uses the view's tint color; use `clearColor` for no color (transparent).
@property (nonatomic, strong, nullable) UIColor *backgroundColor;
/// Optional color transformer that is used to resolve the background color. A nil value means the `backgroundColor` is used as-is.
@property (nonatomic, copy, nullable) UIConfigurationColorTransformer backgroundColorTransformer;
/// Returns the resolved background color for the specified tint color, based on the `backgroundColor` and `backgroundColorTransformer`.
- (UIColor *)resolvedBackgroundColorForTintColor:(UIColor *)tintColor;

/// The visual effect to apply to the background. Default is nil.
@property (nonatomic, copy, nullable) UIVisualEffect *visualEffect;

/// The image to use. Default is nil.
@property (nonatomic, strong, nullable) UIImage *image API_AVAILABLE(ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos);
/// The content mode to use when rendering the image. Default is UIViewContentModeScaleToFill.
@property (nonatomic) UIViewContentMode imageContentMode API_AVAILABLE(ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos);

// Stroke

/// Configures the color of the stroke. A nil value uses the view's tint color; use `clearColor` for no color (transparent).
@property (nonatomic, strong, nullable) UIColor *strokeColor;
/// Optional color transformer that is used to resolve the stroke color. A nil value means the `strokeColor` is used as-is.
@property (nonatomic, copy, nullable) UIConfigurationColorTransformer strokeColorTransformer;
/// Returns the resolved stroke color for the specified tint color, based on the `strokeColor` and `strokeColorTransformer`.
- (UIColor *)resolvedStrokeColorForTintColor:(UIColor *)tintColor;

/// The width of the stroke. Default is 0.
@property (nonatomic) CGFloat strokeWidth;

/// Outset (or inset, if negative) for the stroke, relative to the background (including any backgroundInsets). Default is 0.
/// The corner radius of the stroke is adjusted for any outset to remain concentric with the background.
@property (nonatomic) CGFloat strokeOutset;

/// Describes a shadow applied by the background.
/// Defaults to no shadow (i.e. a shadow with an opacity of 0.0).
@property (nonatomic, readonly) UIShadowProperties *shadowProperties API_AVAILABLE(ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos);


// Deprecated

/// Returns the default configuration for a plain list cell.
+ (instancetype)listPlainCellConfiguration API_DEPRECATED_WITH_REPLACEMENT("listCellConfiguration", ios(14.0, 18.0)) API_UNAVAILABLE(watchos);

/// Returns the default configuration for a grouped list cell.
+ (instancetype)listGroupedCellConfiguration API_DEPRECATED_WITH_REPLACEMENT("listCellConfiguration", ios(14.0, 18.0)) API_UNAVAILABLE(watchos);

/// Returns the default configuration for a sidebar list cell.
+ (instancetype)listSidebarCellConfiguration API_DEPRECATED_WITH_REPLACEMENT("listCellConfiguration", ios(14.0, 18.0)) API_UNAVAILABLE(watchos, tvos);

/// Returns the default configuration for a plain list header or footer.
+ (instancetype)listPlainHeaderFooterConfiguration API_DEPRECATED("Use +listHeaderConfiguration or +listFooterConfiguration", ios(14.0, 18.0)) API_UNAVAILABLE(watchos);

/// Returns the default configuration for a grouped list header or footer.
+ (instancetype)listGroupedHeaderFooterConfiguration API_DEPRECATED("Use +listHeaderConfiguration or +listFooterConfiguration", ios(14.0, 18.0)) API_UNAVAILABLE(watchos);

/// Returns the default configuration for a sidebar list header.
+ (instancetype)listSidebarHeaderConfiguration API_DEPRECATED("Use +listHeaderConfiguration or +listFooterConfiguration", ios(14.0, 18.0)) API_UNAVAILABLE(tvos, watchos);

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIBackgroundConfiguration.h>
#endif
