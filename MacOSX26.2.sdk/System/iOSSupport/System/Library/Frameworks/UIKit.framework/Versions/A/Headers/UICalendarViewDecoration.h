#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UICalendarViewDecoration.h>)
//
//  UICalendarViewDecoration.h
//  UIKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <UIKit/UIView.h>

@class UIImage, UIColor;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NS_ENUM(NSInteger, UICalendarViewDecorationSize) {
    UICalendarViewDecorationSizeSmall   = 0,
    UICalendarViewDecorationSizeMedium  = 1,
    UICalendarViewDecorationSizeLarge   = 2,
} API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos, tvos);

UIKIT_EXTERN API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@interface UICalendarViewDecoration : NSObject

/// Creates a default decoration with a circle image.
- (instancetype)init;

/**
 * @abstract Creates a new image-based decoration with the specified image, color, and size.
 *
 * @param image The image of the decoration, defaults to @c circ lebadge.fill if nil.
 * @param color The color of the the decoration. defaults to @c UIColor.systemFillColor if nil.
 * @param size  The preferred size of the decoration. The default is UICalendarViewDecorationSizeMedium
 */
- (instancetype)initWithImage:(nullable UIImage *)image color:(nullable UIColor *)color size:(UICalendarViewDecorationSize)size;

/**
 * Creates a new custom view decoration using the provided view provider. The provider will
 * be called once when the decoration view is first loaded. The decoration will be clipped to
 * its parent's bounds, and cannot have interaction.
 */
- (instancetype)initWithCustomViewProvider:(UIView *(^)(void))customViewProvider;

#pragma mark - Image

/// Creates a default image accessory with a circle image, and the specified color and size.
+ (instancetype)decorationWithColor:(nullable UIColor *)color size:(UICalendarViewDecorationSize)size;

/// Creates an accessory with the specified image, and default color, and size.
+ (instancetype)decorationWithImage:(nullable UIImage *)image;

/// Creates an accessory with the specified image, color, and size.
+ (instancetype)decorationWithImage:(nullable UIImage *)image color:(nullable UIColor *)color size:(UICalendarViewDecorationSize)size;

#pragma mark - Custom View

/// Creates a new custom view decoration using the specified custom view provider. The provider will be called once
/// when the decoration view is first loaded. The decoration will be clipped to its parent's bounds, and cannot have
/// user interaction.
+ (instancetype)decorationWithCustomViewProvider:(UIView *(^)(void))customViewProvider;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UICalendarViewDecoration.h>
#endif
