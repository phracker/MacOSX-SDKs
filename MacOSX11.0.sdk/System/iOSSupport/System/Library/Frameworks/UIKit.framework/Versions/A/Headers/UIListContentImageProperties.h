#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIListContentImageProperties.h>)
//
//  UIListContentImageProperties.h
//  UIKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>
#import <UIKit/UIConfigurationColorTransformer.h>

NS_ASSUME_NONNULL_BEGIN

@class UIImage;
@class UIImageSymbolConfiguration;
@class UIColor;

UIKIT_EXTERN API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0))
@interface UIListContentImageProperties : NSObject <NSCopying, NSSecureCoding>

/// The symbol configuration to use.
@property (nonatomic, copy, nullable) UIImageSymbolConfiguration *preferredSymbolConfiguration;

/// The tintColor to apply to the image view. Nil will use the image view's normal inherited tintColor.
@property (nonatomic, strong, nullable) UIColor *tintColor;
/// Optional color transformer that is used to resolve the tint color. A nil value means the `tintColor` is used as-is.
@property (nonatomic, copy, nullable) UIConfigurationColorTransformer tintColorTransformer;
/// Returns the resolved image tint color for the specified tint color of the view, based on the `tintColor` and `tintColorTransformer`.
- (UIColor *)resolvedTintColorForTintColor:(UIColor *)tintColor;

/// The preferred corner radius (using a continuous corner curve) for the image.
/// Default is 0. If the image is too small to fit the requested radius, the corner curve
/// and radius will be adjusted to fit.
@property (nonatomic) CGFloat cornerRadius;

/// Enforces a maximum size for the image. The default value is CGSizeZero. A zero width or
/// height means the size is unconstrained on that dimension. If the image exceeds this size
/// on either dimension, its size will be reduced proportionately (maintaining aspect ratio).
@property (nonatomic) CGSize maximumSize;

/// The layout size that is reserved for the image, inside which the image will be centered.
/// The default value is CGSizeZero. The reservedLayoutSize width & height only affect the
/// space reserved for the image and its positioning; they do not affect the image's size.
/// A zero width or height means the default behavior is used for that dimension:
///     * Symbol images will be centered inside a standard width/height that is scaled
///       with the content size category.
///     * Non-symbol images will use a reservedLayoutSize equal to the actual size of the
///       displayed image.
/// Use the UIListContentImageStandardDimension constant for the width and/or height to force
/// the standard symbol image value to be used for that dimension, regardless of the image.
/// This property is used to horizontally align images across adjacent content views (even
/// when the actual image widths may vary slightly), and/or to ensure a consistent height is
/// reserved for different images across different content views (so that the content view
/// heights are consistent even when the actual image heights may vary slightly). The
/// reservedLayoutSize.width is ignored by content views at Accessibility Dynamic Type
/// sizes, and the reservedLayoutSize.height is ignored when using the special Accessibility
/// Dynamic Type layout where text wraps around the image.
@property (nonatomic) CGSize reservedLayoutSize;

/// Prevents the image from inverting its colors when the accessibility setting is enabled.
@property (nonatomic) BOOL accessibilityIgnoresInvertColors;

@end

/// A special constant that can be set to the `reservedLayoutSize` width or height. This
/// forces the system standard value that a symbol image would use for that dimension,
/// even when the image is not a symbol image.
UIKIT_EXTERN const CGFloat UIListContentImageStandardDimension API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0));

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIListContentImageProperties.h>
#endif
