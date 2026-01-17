//
//  PKStroke.h
//  PencilKit
//
//  Copyright © 2020 Apple. All rights reserved.
//

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <Cocoa/Cocoa.h>
#endif

@class PKInk, PKStrokePath, PKFloatRange;

NS_ASSUME_NONNULL_BEGIN

/// The data model value representing a stroke in a `PKDrawing`.
NS_REFINED_FOR_SWIFT
API_AVAILABLE(ios(14.0), macos(11.0))
@interface PKStroke : NSObject <NSCopying>

/// Create a new stroke.
///
/// @param ink The ink for the stroke.
/// @param strokePath The B-spine stroke path for the stroke.
/// @param transform The affine transform of the stroke. Defaults to `.identity`.
/// @param mask The mask for the stroke.
#if TARGET_OS_IPHONE
- (instancetype)initWithInk:(PKInk *)ink strokePath:(PKStrokePath *)strokePath transform:(CGAffineTransform)transform mask:(nullable UIBezierPath *)mask;
#else
- (instancetype)initWithInk:(PKInk *)ink strokePath:(PKStrokePath *)strokePath transform:(CGAffineTransform)transform mask:(nullable NSBezierPath *)mask;
#endif

/// The ink used to render this stroke.
@property (nonatomic, readonly) PKInk *ink;

/// The affine transform of the stroke when rendered.
@property (nonatomic, readonly) CGAffineTransform transform;

/// The B-spline path that describes this stroke.
@property (nonatomic, readonly) PKStrokePath *path;

/// The mask pre-transform that is used to clip the
/// rendering of the stroke.
#if TARGET_OS_IPHONE
@property (nonatomic, readonly, nullable) UIBezierPath *mask;
#else
@property (nonatomic, readonly, nullable) NSBezierPath *mask;
#endif

/// The bounds of the rendered stroke.
/// This includes the width & ink of the stroke after the transform
/// is applied.
@property (nonatomic, readonly) CGRect renderBounds;

/// These are the parametric parameter ranges of points in `strokePath`
/// that intersect the stroke's mask.
@property (nonatomic, readonly) NSArray<PKFloatRange *> *maskedPathRanges;

@end

NS_ASSUME_NONNULL_END
