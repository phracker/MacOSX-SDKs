#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UICornerRadius.h>)
//
//  UICornerRadius.h
//  UIKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Represents a radius used to round a corner.
UIKIT_EXTERN UIKIT_FINAL NS_REFINED_FOR_SWIFT
API_AVAILABLE(ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos)
@interface UICornerRadius : NSObject <NSCopying>

/// A fixed corner radius in points.
+ (instancetype)fixedRadius:(CGFloat)radius;

/// A dynamic corner radius calculated using the geometry of the view and its container.
+ (instancetype)containerConcentricRadius;

/// A dynamic corner radius calculated using the geometry of the view and its container limited to a minimum radius.
+ (instancetype)containerConcentricRadiusWithMinimum:(CGFloat)minimum;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UICornerRadius.h>
#endif
