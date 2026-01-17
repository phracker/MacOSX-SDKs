#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIHoverEffectLayer.h>)
//
//  UIHoverEffectLayer.h
//  UIKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <UIKit/UIHoverStyle.h>
#import <UIKit/UIView.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A layer type that can be used to apply a hover effect to its sublayers.
///
/// This layer type is useful for adding hover effects to an existing
/// ``CALayer`` hierarchy. Where possible, use ``UIView.hoverStyle`` instead.
///
/// A ``UIHoverEffectLayer`` is configured with:
///
/// 1. A container ``UIView``, which is used to infer some properties of the
///    hover effect from its trait collection and to allow some aspects of the
///    hover effect to behave correctly. This view's layer should be an ancestor
///    layer of the ``UIHoverEffectLayer``.
/// 2. A ``UIHoverStyle``, which describes the effect to use and the shape of
///    that effect. You then add your content layers that should receive a hover
///    effect as sublayers of this layer.
///
/// ``UIHoverEffectLayer`` may add its own internal sublayers as background or
/// overlay layers relative to your content sublayers. To preserve the correct
/// appearance of the effect, these internal sublayers are automatically sorted
/// accordingly within the layer's layout pass. As such, do not assume that the
/// indices of your content sublayers will remain stable throughout the lifetime
/// of the layer.
///
/// - Note: Not all ``UIHoverStyle``s may be supported by
///   ``UIHoverEffectLayer``. If the provided style is not supported, a fallback
///   style will be selected instead.
UIKIT_EXTERN API_AVAILABLE(visionos(1.0)) API_UNAVAILABLE(ios) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@interface UIHoverEffectLayer: CALayer

/// The hover style to apply to the sublayers of this layer when this layer
/// is hovered (e.g., when the user looks at this layer). Defaults to the
/// automatic style.
///
/// - Note: Not all ``UIHoverStyle``s may be supported by
///   ``UIHoverEffectLayer``. If the provided style is not supported, a fallback
///   style will be selected instead.
@property (nonatomic, copy) UIHoverStyle *hoverStyle;

/// The ``UIView`` in which this layer is contained. This view is used to
/// derive traits and other properties for applying the correct hover effect
/// to the layer. It may also be used to assist with applying some kinds of
/// hover effects to the layer.
///
/// The ``containerView`` should be an ancestor of this layer (once it has
/// been added to a layer hierarchy) to behave correctly, but does not need
/// to be the immediate parent of this layer. If the ``containerView`` is
/// set to nil or is deallocated, some aspects of this layer's hover effect
/// may no longer work correctly.
@property (nonatomic, weak, nullable) UIView *containerView;

/// Creates a ``UIHoverEffectLayer`` with the provided `containerView`
/// and `style`. If a `nil` `style` is provided, the automatic style will
/// be used instead.
- (instancetype)initWithContainerView:(UIView *)containerView style:(nullable UIHoverStyle *)style;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIHoverEffectLayer.h>
#endif
