#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIContentUnavailableImageProperties.h>)
//
//  UIContentUnavailableImageProperties.h
//  UIKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UIImage;
@class UIImageSymbolConfiguration;
@class UIColor;

UIKIT_EXTERN API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIContentUnavailableImageProperties : NSObject <NSCopying, NSSecureCoding>

/// The symbol configuration to use.
@property (nonatomic, copy, nullable) UIImageSymbolConfiguration *preferredSymbolConfiguration;

/// The tint color to apply to the image view. Nil will use the image view's normal inherited tint color.
@property (nonatomic, strong, nullable) UIColor *tintColor;

/// The preferred corner radius (using a continuous corner curve) for the image.
/// Default is 0. If the image is too small to fit the requested radius, the corner curve
/// and radius will be adjusted to fit.
@property (nonatomic) CGFloat cornerRadius;

/// Enforces a maximum size for the image. The default value is CGSizeZero. A zero width or
/// height means the size is unconstrained on that dimension. If the image exceeds this size
/// on either dimension, its size will be reduced proportionately (maintaining aspect ratio).
@property (nonatomic) CGSize maximumSize;

/// Prevents the image from inverting its colors when the accessibility setting is enabled.
@property (nonatomic) BOOL accessibilityIgnoresInvertColors;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIContentUnavailableImageProperties.h>
#endif
