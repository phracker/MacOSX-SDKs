#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UICornerConfiguration.h>)
//
//  UICornerConfiguration.h
//  UIKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <UIKit/UIKitDefines.h>
#import <UIKit/UICornerRadius.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Defines how corner radii are mapped to the corners of a rectangle.
UIKIT_EXTERN UIKIT_FINAL NS_REFINED_FOR_SWIFT
API_AVAILABLE(ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos)
@interface UICornerConfiguration : NSObject <NSCopying>

/// A configuration that applies the given radius independently to all corners.
///
/// When used with a container concentric radius, this allows each individual
/// corner to resolve to different radii.
+ (instancetype)configurationWithRadius:(UICornerRadius *)radius NS_SWIFT_NAME(corners(radius:));

/// A configuration with independent radii for each corner.
+ (instancetype)configurationWithTopLeftRadius:(nullable UICornerRadius *)topLeftRadius
                                topRightRadius:(nullable UICornerRadius *)topRightRadius
                              bottomLeftRadius:(nullable UICornerRadius *)bottomLeftRadius
                             bottomRightRadius:(nullable UICornerRadius *)bottomRightRadius NS_SWIFT_NAME(corners(topLeftRadius:topRightRadius:bottomLeftRadius:bottomRightRadius:));

/// A configuration that rounds the corners into a capsule shape, scaling with the view's size.
+ (instancetype)capsuleConfiguration NS_SWIFT_NAME(capsule());

/// A configuration that rounds the corners into a capsule shape, scaling with the view's size and clamped to the `maximumRadius`.
+ (instancetype)capsuleConfigurationWithMaximumRadius:(CGFloat)maximumRadius NS_SWIFT_NAME(capsule(maximumRadius:));

/// A configuration that applies the given radius uniformly to all corners.
+ (instancetype)configurationWithUniformRadius:(UICornerRadius *)radius NS_SWIFT_NAME(uniformCorners(radius:));

/// A configuration that applies the `topRadius` uniformly to the top-left and top-right corners, and the `bottomRadius` uniformly to the bottom-left and bottom-right corners.
+ (instancetype)configurationWithUniformTopRadius:(UICornerRadius *)topRadius
                              uniformBottomRadius:(UICornerRadius *)bottomRadius NS_SWIFT_NAME(uniformEdges(topRadius:bottomRadius:));

/// A configuration that applies the `leftRadius` uniformly to the top-left and bottom-left corners, and the `rightRadius` uniformly to the top-right and bottom-right corners.
+ (instancetype)configurationWithUniformLeftRadius:(UICornerRadius *)leftRadius
                                uniformRightRadius:(UICornerRadius *)rightRadius NS_SWIFT_NAME(uniformEdges(leftRadius:rightRadius:));

/// A configuration that applies the `topRadius` uniformly to the top-left and top-right corners, with optional independent radii for the bottom-left and bottom-right corners.
+ (instancetype)configurationWithUniformTopRadius:(UICornerRadius *)topRadius
                                 bottomLeftRadius:(nullable UICornerRadius *)bottomLeftRadius
                                bottomRightRadius:(nullable UICornerRadius *)bottomRightRadius NS_SWIFT_NAME(uniformTopRadius(_:bottomLeftRadius:bottomRightRadius:));

/// A configuration that applies the `bottomRadius` uniformly to the bottom-left and bottom-right corners, with optional independent radii for the top-left and top-right corners.
+ (instancetype)configurationWithUniformBottomRadius:(UICornerRadius *)bottomRadius
                                       topLeftRadius:(nullable UICornerRadius *)topLeftRadius
                                      topRightRadius:(nullable UICornerRadius *)topRightRadius NS_SWIFT_NAME(uniformBottomRadius(_:topLeftRadius:topRightRadius:));

/// A configuration that applies the `leftRadius` uniformly to the top-left and bottom-left corners, with optional independent radii for the top-right and bottom-right corners.
+ (instancetype)configurationWithUniformLeftRadius:(UICornerRadius *)leftRadius
                                    topRightRadius:(nullable UICornerRadius *)topRightRadius
                                 bottomRightRadius:(nullable UICornerRadius *)bottomRightRadius NS_SWIFT_NAME(uniformLeftRadius(_:topRightRadius:bottomRightRadius:));

/// A configuration that applies the `rightRadius` uniformly to the top-right and bottom-right corners, with optional independent radii for the top-left and bottom-left corners.
+ (instancetype)configurationWithUniformRightRadius:(UICornerRadius *)rightRadius
                                      topLeftRadius:(nullable UICornerRadius *)topLeftRadius
                                   bottomLeftRadius:(nullable UICornerRadius *)bottomLeftRadius NS_SWIFT_NAME(uniformRightRadius(_:topLeftRadius:bottomLeftRadius:));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UICornerConfiguration.h>
#endif
