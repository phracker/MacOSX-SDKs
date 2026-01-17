#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIShadowProperties.h>)
//
//  UIShadowProperties.h
//  UIKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

@class UIColor, UIBezierPath;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN NS_SWIFT_UI_ACTOR NS_REFINED_FOR_SWIFT
API_AVAILABLE(ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos)
@interface UIShadowProperties : NSObject <NSCopying, NSSecureCoding>

/// The color to use when rendering the shadow. Defaults to `UIColor.blackColor`.
@property (nonatomic, strong) UIColor *color;

/// The shadow's opacity. Defaults to `0.0`.
@property (nonatomic, assign) CGFloat opacity;

/// The blur radius, in points, used to render the shadow. Defaults to `0.0`.
@property (nonatomic, assign) CGFloat radius;

/// The offset, in points, of the layer's shadow. Defaults to `CGSizeZero`.
@property (nonatomic, assign) CGSize offset;

/// The path that is used to create the shadow. When `nil`, the shadow will be rendered to match
/// the bounds of the view that it is applied to.
/// Defaults to `nil`.
@property (nonatomic, copy, nullable) UIBezierPath *path;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIShadowProperties.h>
#endif
