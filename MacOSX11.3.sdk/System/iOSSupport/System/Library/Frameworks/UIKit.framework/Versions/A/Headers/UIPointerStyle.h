#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIPointerStyle.h>)
//
//  UIPointerStyle.h
//  UIKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIGeometry.h>
#import <CoreGraphics/CGGeometry.h>

@class UITargetedPreview, UIBezierPath, UIPointerEffect, UIPointerShape;

NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN API_AVAILABLE(ios(13.4)) API_UNAVAILABLE(watchos, tvos) @interface UIPointerStyle : NSObject <NSCopying>

/*!
 * @abstract Applies the provided content effect and pointer shape within the current region.
 *
 * @param effect  The desired pointer effect.
 * @param shape   The desired pointer shape. If omitted, a pointer will be generated automatically from the effect's preview view.
 */
+ (instancetype)styleWithEffect:(UIPointerEffect *)effect shape:(nullable UIPointerShape *)shape NS_REFINED_FOR_SWIFT;

/*!
 * @abstract Morphs the pointer into the provided shape when hovering over the current region.
 *
 * @param shape  The desired pointer shape.
 * @param axes   Axes along which to recenter the pointer on touch up.
 */
+ (instancetype)styleWithShape:(UIPointerShape *)shape constrainedAxes:(UIAxis)axes NS_REFINED_FOR_SWIFT;

/*!
 * @abstract Hides the pointer when hovering over the current region.
 */
+ (instancetype)hiddenPointerStyle;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end


UIKIT_EXTERN API_AVAILABLE(ios(13.4)) API_UNAVAILABLE(watchos, tvos) NS_REFINED_FOR_SWIFT @interface UIPointerEffect : NSObject <NSCopying>

@property (nonatomic, copy, readonly) UITargetedPreview *preview;

/*!
 * @abstract Creates a pointer content effect with the given preview's view.
 *
 * @param preview  A UITargetedPreview object describing a view with which to construct the effect.
 *
 * @discussion UIPointerEffect attempts to determine the appropriate effect for the given preview automatically.
 *             Use one of its subclasses to request a specific system-provided effect.
 */
+ (instancetype)effectWithPreview:(UITargetedPreview *)preview;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

/// Pointer slides under the given view and morphs into the view's shape
UIKIT_EXTERN API_AVAILABLE(ios(13.4)) API_UNAVAILABLE(watchos, tvos) NS_REFINED_FOR_SWIFT @interface UIPointerHighlightEffect : UIPointerEffect
@end

/// Pointer slides under the given view and disappears as the view scales up and gains a shadow.
UIKIT_EXTERN API_AVAILABLE(ios(13.4)) API_UNAVAILABLE(watchos, tvos) NS_REFINED_FOR_SWIFT @interface UIPointerLiftEffect : UIPointerEffect
@end

typedef NS_ENUM(NSInteger, UIPointerEffectTintMode) {
    UIPointerEffectTintModeNone = 0,    // Indicates that no tint should be applied to the view.
    UIPointerEffectTintModeOverlay,     // Indicates that a tint overlay should be placed above the view.
    UIPointerEffectTintModeUnderlay,    // Indicates that a tint underlay should be placed below the view.
} API_AVAILABLE(ios(13.4)) API_UNAVAILABLE(watchos, tvos) NS_REFINED_FOR_SWIFT;


/// Pointer retains the system shape while over the given view. Visual changes applied to the view are dictated by the effect's properties.
UIKIT_EXTERN API_AVAILABLE(ios(13.4)) API_UNAVAILABLE(watchos, tvos) NS_REFINED_FOR_SWIFT @interface UIPointerHoverEffect : UIPointerEffect

@property (nonatomic) UIPointerEffectTintMode preferredTintMode;        // Defaults to UIPointerEffectTintModeOverlay
@property (nonatomic) BOOL prefersShadow;                               // Defaults to NO
@property (nonatomic) BOOL prefersScaledContent;                        // Defaults to YES

@end


UIKIT_EXTERN API_AVAILABLE(ios(13.4)) API_UNAVAILABLE(watchos, tvos) NS_REFINED_FOR_SWIFT @interface UIPointerShape : NSObject <NSCopying>

/*!
 * @abstract Morphs the pointer to the given path.
 */
+ (instancetype)shapeWithPath:(UIBezierPath *)path;

/*!
 * @abstract Morphs the pointer to a rounded rectangle with the provided rect and the standard system corner radius.
 *
 * @param rect  CGRect describing the pointer's frame. If used alongside a content effect, this rect must be in the effect's
 *              preview's container view's coordinate space. Otherwise, it is centered about the pointer's current location
 *              and the rect's origin is interpreted as an offset.
 */
+ (instancetype)shapeWithRoundedRect:(CGRect)rect;

/*!
 * @abstract Morphs the pointer to a rounded rectangle with the provided rect and cornerRadius.
 *
 * @param rect          CGRect describing the pointer's frame. If used alongside a content effect, this rect must be in
 *                      the effect's preview's container view's coordinate space. Otherwise, it is centered about the
 *                      pointer's current location and the rect's origin is interpreted as an offset.
 * @param cornerRadius  Corner radius to apply to the pointer.
 */
+ (instancetype)shapeWithRoundedRect:(CGRect)rect cornerRadius:(CGFloat)cornerRadius;

/*!
 * @abstract Morphs the pointer to a beam with the given length and axis.
 *
 * @param length  The beam's length. Limited to the region's width or height, depending on the beam's axis.
 * @param axis    The axis along which to draw the beam. Axis must be either UIAxisVertical or UIAxisHorizontal.
 */
+ (instancetype)beamWithPreferredLength:(CGFloat)length axis:(UIAxis)axis;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIPointerStyle.h>
#endif
