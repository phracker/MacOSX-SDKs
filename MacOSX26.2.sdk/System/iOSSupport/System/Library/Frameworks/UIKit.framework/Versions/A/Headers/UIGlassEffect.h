#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIGlassEffect.h>)
//
//  UIGlassEffect.h
//  UIKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <UIKit/UIVisualEffect.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIColor.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NS_ENUM(NSInteger, UIGlassEffectStyle) {
    /// Standard glass effect style.
    UIGlassEffectStyleRegular,
    /// Clear glass effect style.
    UIGlassEffectStyleClear
} API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(visionos, watchos) NS_SWIFT_NAME(UIGlassEffect.Style);

/// A visual effect that renders a glass material.
UIKIT_EXTERN NS_SWIFT_UI_ACTOR
API_AVAILABLE(ios(26.0))
API_UNAVAILABLE(visionos, watchos)
@interface UIGlassEffect : UIVisualEffect

/// Enables interactive behavior for the glass effect.
@property (nonatomic, getter=isInteractive) BOOL interactive;

/// A tint color applied to the glass.
@property (nonatomic, copy, nullable) UIColor *tintColor;

/// Creates a glass effect with the specified style.
+ (UIGlassEffect *)effectWithStyle:(UIGlassEffectStyle)style NS_SWIFT_NAME(init(style:));

@end

/// A `UIGlassContainerEffect` renders multiple glass elements into a combined effect.
///
/// When using `UIGlassContainerEffect` with a `UIVisualEffectView` you can
/// add individual glass elements to the visual effect view's contentView by nesting `UIVisualEffectView`'s
/// configured with `UIGlassEffect`. In that configuration, the glass container will render all glass elements
/// in one combined view, behind the visual effect view's `contentView`.
UIKIT_EXTERN NS_SWIFT_UI_ACTOR
API_AVAILABLE(ios(26.0))
API_UNAVAILABLE(visionos, watchos)
@interface UIGlassContainerEffect : UIVisualEffect

/// The spacing specifies the distance between elements at which they begin to merge.
@property (nonatomic) CGFloat spacing;
@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIGlassEffect.h>
#endif
