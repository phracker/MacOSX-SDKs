//
//  PHASEEnvelope.h
//  PHASE
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#ifndef PHASEEnvelope_h
#define PHASEEnvelope_h

#import <PHASE/PHASETypes.h>

#import <simd/types.h>

NS_ASSUME_NONNULL_BEGIN

/****************************************************************************************************/
/*!
    @interface PHASENumericPair
    @abstract A numeric pair.
*/
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASENumericPair : NSObject

/*!
    @method initWithFirstValue:secondValue
    @abstract Initialize a numeric pair with a first and second value.
    @param first
        The first value in the pair.
    @param second
        The second value in the pair.
    @return
        A new pair.
 */
- (instancetype)initWithFirstValue:(double)first secondValue:(double)second;

/*!
    @property first
    @abstract The first value in the numeric pair.
    @discussion
        The default value is 0.0.
 */
@property(nonatomic, assign) double first;

/*! @property second
    @abstract The second value in the numeric pair.
    @discussion
        The default value is 0.0.
 */
@property(nonatomic, assign) double second;

@end

#pragma mark - PHASEEnvelopeSegment

/****************************************************************************************************/
/*!
    @class PHASEEnvelopeSegment
    @abstract An envelope segment defined by an end point and a curve type.
    @discussion
        Envelope segments do 'not' contain a start point.
        We do this so we can connect envelope segments together end to end and gaurantee continuity along the x and y axes.
*/
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASEEnvelopeSegment : NSObject

/*!
    @method initWithEndPoint:curveType
    @abstract Initialize an envelope segment with an endPoint and a curveType.
    @param endPoint
        The end point of the segment.
    @param curveType
        The curve type.
    @return
        A new envelope.
 */
- (instancetype)initWithEndPoint:(simd_double2)endPoint curveType:(PHASECurveType)curveType;

/*!
    @property endPoint
    @abstract The end point of the envelope segment.
    @discussion
        The default value is [0.0, 0.0].
 */
@property(nonatomic, assign) simd_double2 endPoint;

/*!
    @property curveType
    @abstract The curve type of the envelope segment.
    @discussion
        The default value is PHASECurveTypeLinear.
 */
@property(nonatomic, assign) PHASECurveType curveType;

@end

#pragma mark - PHASEEnvelope

/****************************************************************************************************/
/*!
    @interface PHASEEnvelope
    @abstract A segmented envelope.
*/
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASEEnvelope : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @method initWithStartPoint:segments
    @abstract Initialize an envelope from a start point and an array of segments.
    @discussion
        If the segment array is empty (i.e., count == 0), the envelope will internally create a single segment with an end point matching the start point.
        If the segment array has more than one segment, segments will be sorted internally in ascending order of x value.
        Note that the startPoint.x value must be <= the segment with the lowest x value provided in segments.
        Failure to do so will cause this function to return nil.
    @param startPoint
        The start point of the envelope.
    @param segments
        An array of segments.
    @return
        A new envelope.
 */
- (nullable instancetype)initWithStartPoint:(simd_double2)startPoint
                                   segments:(NSArray<PHASEEnvelopeSegment*>*)segments NS_DESIGNATED_INITIALIZER;

/*!
    @method evaluateForValue
    @abstract Evaluates the envelope.
    @discussion
        If required, x will be clamped to the envelope's domain.
    @param x
        The input along the x-axis.
    @return
        The output along the y-axis.
 */
- (double)evaluateForValue:(double)x
NS_SWIFT_NAME(evaluate(x:));

/*!
    @property startPoint
    @abstract The start point of the envelope.
 */
@property(nonatomic, readonly) simd_double2 startPoint;

/*!
    @property segments
    @abstract The segments of the envelope.
 */
@property(nonatomic, readonly, copy) NSArray<PHASEEnvelopeSegment*>* segments;

/*!
    @property domain
    @abstract The domain (along the x-axis).
    @discussion
        The first value in the pair is the minimum value of the domain.
        The second value in the pair is the maximum value of the domain.
 */
@property(nonatomic, strong, readonly) PHASENumericPair* domain;

/*!
    @property range
    @abstract The range (along the y-axis).
    @discussion
        The first value in the pair is the minimum value of the range.
        The second value in the pair is the maximum value of the range.
 */
@property(nonatomic, strong, readonly) PHASENumericPair* range;

@end

NS_ASSUME_NONNULL_END

#endif /* PHASEEnvelope_h */
