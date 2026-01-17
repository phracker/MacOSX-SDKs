#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIHoverStyle.h>)
//
//  UIHoverStyle.h
//  UIKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIView.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@protocol UIHoverEffect;
@class UIShape, UIPointerStyle;

/// The hover style to apply to a view, including an effect and a shape to use
/// for displaying that effect.
UIKIT_EXTERN API_AVAILABLE(ios(17.0), visionos(1.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@interface UIHoverStyle : NSObject <NSCopying>

/// The effect to apply to the view with this style. Use `UIHoverAutomaticEffect`
/// to apply a system-default effect to the view.
@property (nonatomic, strong) id<UIHoverEffect> effect NS_REFINED_FOR_SWIFT;

/// The shape to use for the hover effect. If a `nil` shape is used, a
/// system-default shape will be chosen based on the view.
@property (nonatomic, strong, nullable) UIShape *shape NS_REFINED_FOR_SWIFT;

/// Whether the effect to apply to the view with this style is enabled.
/// Use this property to temporarily disable a view's hover effect without
/// removing it from the view entirely.
@property (nonatomic, getter=isEnabled) BOOL enabled;

/// Creates a hover style with the provided effect and shape.
+ (instancetype)styleWithEffect:(id<UIHoverEffect>)effect shape:(nullable UIShape *)shape NS_REFINED_FOR_SWIFT;

/// Creates a hover style with the provided shape and a `UIHoverAutomaticEffect`.
+ (instancetype)styleWithShape:(nullable UIShape *)shape NS_REFINED_FOR_SWIFT;

/// Creates a hover style with the default shape and a `UIHoverAutomaticEffect`.
+ (instancetype)automaticStyle NS_REFINED_FOR_SWIFT;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

UIKIT_EXTERN API_AVAILABLE(ios(17.0), visionos(1.0)) API_UNAVAILABLE(watchos, tvos)
@interface UIView (UIHoverStyle)

/// The hover style associated with this view. Defaults to `nil`,
/// indicating that this view should not have any hover effect.
/// Subclasses may configure this style to use a different default value.
@property (nonatomic, copy, nullable) UIHoverStyle *hoverStyle API_UNAVAILABLE(watchos);

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIHoverStyle.h>
#endif
