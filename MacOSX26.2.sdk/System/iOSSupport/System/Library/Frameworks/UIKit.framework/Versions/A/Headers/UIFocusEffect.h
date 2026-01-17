#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIFocusEffect.h>)
//
//  UIFocusEffect.h
//  UIKit
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <QuartzCore/CALayer.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UIView, UIBezierPath;

UIKIT_EXTERN API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos)
@interface UIFocusEffect : NSObject <NSCopying>

/// Creates a default system effect using metrics inferred from the focus item.
+ (instancetype)effect;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end


typedef NS_ENUM(NSInteger, UIFocusHaloEffectPosition) {
    /// Automatically detects the best position depending on the the focus item and its containing view hierarchy.
    UIFocusHaloEffectPositionAutomatic = 0,
    /// Draws the halo around the given shape.
    UIFocusHaloEffectPositionOutside,
    /// Draws the halo inside the given shape.
    UIFocusHaloEffectPositionInside,
} API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos);


UIKIT_EXTERN API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos)
@interface UIFocusHaloEffect : UIFocusEffect

/// Creates a rectangular halo.
+ (instancetype)effectWithRect:(CGRect)rect;

/// Creates a rounded rect halo using the specified corner radius and corner curve.
+ (instancetype)effectWithRoundedRect:(CGRect)rect cornerRadius:(CGFloat)cornerRadius curve:(CALayerCornerCurve)curve;

/// Creates a halo with the given bezier path.
+ (instancetype)effectWithPath:(UIBezierPath *)bezierPath;

/// Container view in which to place the effect. When not set, the container is determined automatically
/// from the focus item that provided this effect and the @c referenceView (if present).
@property (nonatomic, weak, nullable) UIView *containerView;

/// When set, the halo is placed above this view. If a @c containerView is also set, the @c referenceView must be a descendant
/// of the @c containerView. The system will ensure that the halo is in the container but visually above the @c referenceView.
@property (nonatomic, weak, nullable) UIView *referenceView;

/// Position of the halo relative to the specified shape. Defaults to @c UIFocusHaloEffectPositionAutomatic.
@property (nonatomic) UIFocusHaloEffectPosition position;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIFocusEffect.h>
#endif
