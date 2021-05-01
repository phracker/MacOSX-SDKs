#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIBarAppearance.h>)
//
//  UIBarAppearance.h
//  UIKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIView.h>

NS_ASSUME_NONNULL_BEGIN

@class UIColor;
@class UIImage;
@class UIBlurEffect;

UIKIT_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0)) @interface UIBarAppearance : NSObject<NSCopying, NSSecureCoding>

/// Constructs a new bar appearance, configured with default values and targeting the device idiom.
- (instancetype)init;

/// Constructs a new bar appearance, targeting the passed-in idiom as a hint. Not all platforms support all available idioms. See the idiom property to determine the resolved idiom.
- (instancetype)initWithIdiom:(UIUserInterfaceIdiom)idiom NS_DESIGNATED_INITIALIZER;

/// The idiom that this appearance object targets.
@property (nonatomic, readonly, assign) UIUserInterfaceIdiom idiom;

/// Constructs a new bar appearance, copying all relevant properties from the given appearance object. This initializer is useful for migrating configuration between UIBarAppearance subclasses. For example, you can initialize a UINavigationBarAppearance with a UIToolbarAppearance instance, and shared attributes will be identical between the two.
- (instancetype)initWithBarAppearance:(UIBarAppearance *)barAppearance NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

- (instancetype)copy;

/// Reset background and shadow properties to their defaults.
- (void)configureWithDefaultBackground;

/// Reset background and shadow properties to display theme-appropriate opaque colors.
- (void)configureWithOpaqueBackground;

/// Reset background and shadow properties to be transparent.
- (void)configureWithTransparentBackground;

/// A specific blur effect to use for the bar background. This effect is composited first when constructing the bar's background.
@property (nonatomic, readwrite, copy, nullable) UIBlurEffect *backgroundEffect;
/// A color to use for the bar background. This color is composited over backgroundEffects.
@property (nonatomic, readwrite, copy, nullable) UIColor *backgroundColor;
/// An image to use for the bar background. This image is composited over the backgroundColor, and resized per the backgroundImageContentMode.
@property (nonatomic, readwrite, strong, nullable) UIImage *backgroundImage;
/// The content mode to use when rendering the backgroundImage. Defaults to UIViewContentModeScaleToFill. UIViewContentModeRedraw will be reinterpreted as UIViewContentModeScaleToFill.
@property (nonatomic, readwrite, assign) UIViewContentMode backgroundImageContentMode;

/// A color to use for the shadow. Its specific behavior depends on the value of shadowImage. If shadowImage is nil, then the shadowColor is used to color the bar's default shadow; a nil or clearColor shadowColor will result in no shadow. If shadowImage is a template image, then the shadowColor is used to tint the image; a nil or clearColor shadowColor will also result in no shadow. If the shadowImage is not a template image, then it will be rendered regardless of the value of shadowColor.
@property (nonatomic, readwrite, copy, nullable) UIColor *shadowColor;
/// Use an image for the shadow. See shadowColor for how they interact.
@property (nonatomic, readwrite, strong, nullable) UIImage *shadowImage;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIBarAppearance.h>
#endif
