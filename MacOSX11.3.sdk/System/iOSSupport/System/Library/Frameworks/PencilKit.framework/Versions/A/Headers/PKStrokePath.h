//
//  PKStrokePath.h
//  PencilKit
//
//  Copyright © 2020 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>


NS_ASSUME_NONNULL_BEGIN

@class PKStrokePoint;

/// A uniform cubic B-spline representing the point data of a `PKStroke`.
NS_REFINED_FOR_SWIFT
API_AVAILABLE(ios(14.0), macos(11.0))
@interface PKStrokePath : NSObject <NSCopying>

/// Create a stroke path value with the given cubic B-spline control points.
///
/// @param controlPoints An array of control points for a cubic B-spline.
/// @param creationDate The start time of this path.
- (instancetype)initWithControlPoints:(NSArray<PKStrokePoint *> *)controlPoints creationDate:(NSDate *)creationDate NS_DESIGNATED_INITIALIZER;

/// The number of control points in this stroke path.
@property (nonatomic, readonly) NSUInteger count;

/// The time at which this stroke path was started.
/// The `timeOffset` of contained PKStrokePoints is relative to this date.
@property (nonatomic, readonly) NSDate *creationDate;

/// Returns B-spline control point at index `i`.
- (PKStrokePoint *)pointAtIndex:(NSUInteger)i;

/// Returns B-spline control point at index `i`.
- (PKStrokePoint *)objectAtIndexedSubscript:(NSUInteger)i;

/// The on-curve location for the floating point [0, count-1] `parametricValue` parameter.
///
/// This has better performance than `[self interpolatedPointAt: parametricValue].location`
/// for when only the location is required.
- (CGPoint)interpolatedLocationAt:(CGFloat)parametricValue;

/// The on-curve point for the floating point [0, count-1] `parametricValue` parameter.
- (PKStrokePoint *)interpolatedPointAt:(CGFloat)parametricValue;

/// Executes a given block using each point in a range with a distance step.
///
/// @param range The parametric range to enumerate points in.
/// @param distanceStep The distance to step between points.
/// @param block The block to execute for each point. This block takes two parameters
///        point The interpolated point on the spline.
///        stop A reference to a Boolean value. Setting the value to YES within the block stops further enumeration of the array. If a block stops further enumeration, that block continues to run until it’s finished.
- (void)enumerateInterpolatedPointsInRange:(PKFloatRange *)range strideByDistance:(CGFloat)distanceStep usingBlock:(void (^)(PKStrokePoint *point, BOOL *stop))block;

/// Executes a given block using each point in a range with a time step.
///
/// @param range The parametric range to enumerate points in.
/// @param timeStep The time interval to step between points.
/// @param block The block to execute for each point. This block takes two parameters
///        point The interpolated point on the spline.
///        stop A reference to a Boolean value. Setting the value to YES within the block stops further enumeration of the array. If a block stops further enumeration, that block continues to run until it’s finished.
- (void)enumerateInterpolatedPointsInRange:(PKFloatRange *)range strideByTime:(NSTimeInterval)timeStep usingBlock:(void (^)(PKStrokePoint *point, BOOL *stop))block;

/// Executes a given block using each point in a range with a parametric step.
///
/// @param range The parametric range to enumerate points in.
/// @param parametricStep The parametric step between points.
/// @param block The block to execute for each point. This block takes two parameters
///        point The interpolated point on the spline.
///        stop A reference to a Boolean value. Setting the value to YES within the block stops further enumeration of the array. If a block stops further enumeration, that block continues to run until it’s finished.
- (void)enumerateInterpolatedPointsInRange:(PKFloatRange *)range strideByParametricStep:(CGFloat)parametricStep usingBlock:(void (^)(PKStrokePoint *point, BOOL *stop))block;

/// Returns a parametric value on the B-spline that is a specified distance from the given parametric value.
///
/// @param parametricValue The floating point [0, count-1] parametric value.
/// @param distanceStep The distance to offset `parametricValue`. `distanceStep` can be positive or negative.
/// @return A parametric value offset by `distanceStep` from `parametricValue`.
- (CGFloat)parametricValue:(CGFloat)parametricValue offsetByDistance:(CGFloat)distanceStep;

/// Returns a parametric value on the B-spline that is a specified time from the given parametric value.
///
/// @param parametricValue The floating point [0, count-1] parametric value.
/// @param timeStep The time to offset `parametricValue`. `timeStep` can be positive or negative.
/// @return A parametric value offset by `timeStep` from `parametricValue`.
- (CGFloat)parametricValue:(CGFloat)parametricValue offsetByTime:(NSTimeInterval)timeStep;

@end

NS_ASSUME_NONNULL_END
