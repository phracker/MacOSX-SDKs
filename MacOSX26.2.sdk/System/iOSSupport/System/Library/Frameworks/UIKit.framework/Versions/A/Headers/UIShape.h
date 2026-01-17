#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIShape.h>)
//
//  UIShape.h
//  UIKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIGeometry.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// The corner curve to apply to a view.
API_AVAILABLE(ios(17.0), visionos(1.0)) API_UNAVAILABLE(tvos, watchos)
typedef NS_ENUM(NSInteger, UICornerCurve) {
    /// Select the corner style automatically.
    UICornerCurveAutomatic,
    /// Always use a circular corner style.
    UICornerCurveCircular,
    /// Always use a continuous corner style.
    UICornerCurveContinuous,
} API_UNAVAILABLE(watchos);

@class UIShapeResolutionContext, UIResolvedShape, UIBezierPath;

/// A type that can provide a custom `UIShape`, resolved dynamically based on
/// context.
UIKIT_EXTERN API_AVAILABLE(ios(17.0), visionos(1.0)) API_UNAVAILABLE(tvos, watchos)
NS_REFINED_FOR_SWIFT
@protocol UIShapeProvider <NSObject>

/// Resolves this shape in the provided `context`.
- (UIResolvedShape *)resolvedShapeInContext:(UIShapeResolutionContext *)context;

@end

/// An abstract representation of a shape.
///
/// A `UIShape` can represent a simple shape such as a rectangle or circle that
/// are later "resolved" into a concrete shape based on context like a size and
/// position for the shape. A `UIShape` can also represent more complex shapes
/// like paths and even "dynamic" shapes that are resolved using a custom
/// closure.
///
/// You typically use a `UIShape` with APIs like `UIHoverStyle` to represent the
/// shape of an effect.
UIKIT_EXTERN API_AVAILABLE(ios(17.0), visionos(1.0)) API_UNAVAILABLE(tvos, watchos)
NS_REFINED_FOR_SWIFT
@interface UIShape : NSObject <UIShapeProvider, NSCopying>

/// A rectangular shape.
@property (class, nonatomic, readonly) UIShape *rectShape;

/// A capsule shape, equivalent to a rounded rectangle where the corner
/// radius is chosen as half the length of the rectangle’s smallest edge.
@property (class, nonatomic, readonly) UIShape *capsuleShape;

/// A circular shape, with a radius equals half the length of the frame
/// rectangle’s smallest edge.
@property (class, nonatomic, readonly) UIShape *circleShape;

/// A rectangular shape with rounded corners, aligned inside the frame of
/// in which it is contained.
+ (instancetype)rectShapeWithCornerRadius:(CGFloat)cornerRadius;

/// A rectangular shape with rounded corners, aligned inside the frame of
/// in which it is contained.
+ (instancetype)rectShapeWithCornerRadius:(CGFloat)cornerRadius cornerCurve:(UICornerCurve)cornerCurve;

/// A rectangular shape with rounded corners, aligned inside the frame of
/// in which it is contained.
+ (instancetype)rectShapeWithCornerRadius:(CGFloat)cornerRadius cornerCurve:(UICornerCurve)cornerCurve maskedCorners:(UIRectCorner)maskedCorners;

/// A fixed rectangle shape using `rect` as its shape, regardless of the
/// frame in which it is contained.
+ (instancetype)fixedRectShapeWithRect:(CGRect)rect;

/// A fixed rectangle shape using `rect` as its shape, regardless of the
/// frame in which it is contained, with rounded corners using `cornerRadius`.
+ (instancetype)fixedRectShapeWithRect:(CGRect)rect cornerRadius:(CGFloat)cornerRadius;

/// A fixed rectangle shape using `rect` as its shape, regardless of the
/// frame in which it is contained, with rounded corners using `cornerRadius`.
+ (instancetype)fixedRectShapeWithRect:(CGRect)rect cornerRadius:(CGFloat)cornerRadius cornerCurve:(UICornerCurve)cornerCurve maskedCorners:(UIRectCorner)maskedCorners;

/// A shape with a custom bezier path.
+ (instancetype)shapeWithBezierPath:(UIBezierPath *)path;

/// Creates a dynamic shape that can be resolved using the provided
/// `UIShapeProvider` based on context like its containing rect.
+ (instancetype)shapeWithProvider:(id<UIShapeProvider>)provider;

/// Insets this shape by the provided `insets`, returning a new modified
/// shape.
///
/// Negative values can be used to add inner padding to a shape. If this
/// shape is not insettable (e.g., if it is a custom path), this has no
/// effect. For some shapes like rounded rectangles, this can also modify
/// the corner radii of the shape to ensure the resulting corners are
/// concentric.
- (UIShape *)shapeByApplyingInsets:(UIEdgeInsets)insets;

/// Insets this shape by the provided `inset`, returning a new modified
/// shape.
///
/// Negative values can be used to add inner padding to a shape. If this
/// shape is not insettable (e.g., if it is a custom path), this has no
/// effect. For some shapes like rounded rectangles, this can also modify
/// the corner radii of the shape to ensure the resulting corners are
/// concentric.
- (UIShape *)shapeByApplyingInset:(CGFloat)inset;

/// Resolves this shape in the provided `context`.
- (UIResolvedShape *)resolvedShapeInContext:(UIShapeResolutionContext *)context;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

/// A shape that has been resolved based on a `ResolutionContext`.
UIKIT_EXTERN API_AVAILABLE(ios(17.0), visionos(1.0)) API_UNAVAILABLE(tvos, watchos)
NS_REFINED_FOR_SWIFT
@interface UIResolvedShape : NSObject <NSCopying>

/// The abstract shape that produced this resolved shape.
@property (nonatomic, readonly) UIShape *shape;

/// The bounding rect in which the shape is framed.
@property (nonatomic, readonly) CGRect boundingRect;

/// The bezier path representing this shape.
@property (nonatomic, readonly) UIBezierPath *path;

/// Insets this shape by the provided `insets`, returning a new modified
/// shape.
///
/// Negative values can be used to add inner padding to a shape. If this
/// shape is not insettable (e.g., if it is a custom path), this has no
/// effect. For some shapes like rounded rectangles, this can also modify
/// the corner radii of the shape to ensure the resulting corners are
/// concentric.
- (UIResolvedShape *)shapeByApplyingInsets:(UIEdgeInsets)insets;

/// Insets this shape by the provided `inset`, returning a new modified
/// shape.
///
/// Negative values can be used to add inner padding to a shape. If this
/// shape is not insettable (e.g., if it is a custom path), this has no
/// effect. For some shapes like rounded rectangles, this can also modify
/// the corner radii of the shape to ensure the resulting corners are
/// concentric.
- (UIResolvedShape *)shapeByApplyingInset:(CGFloat)inset;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

/// The context used for resolving a `dynamic` `UIShape`.
UIKIT_EXTERN API_AVAILABLE(ios(17.0), visionos(1.0)) API_UNAVAILABLE(tvos, watchos)
NS_REFINED_FOR_SWIFT
@interface UIShapeResolutionContext : NSObject

/// The resolved shape of the content to which this shape may be
/// applied. For example, if this shape will be used to apply an effect
/// to a button, the `contentShape` could represent the bounding shape
/// of that button's background. You should typically size a dynamic
/// shape relative to the bounding `rect` of the `contentShape`.
@property (nonatomic, readonly) UIResolvedShape *contentShape;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIShape.h>
#endif
