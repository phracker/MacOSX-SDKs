/*!
 *  @header MPSImageReduce.h
 *  @framework MetalPerformanceShaders
 *
 *  @copyright Copyright (c) 2017 Apple Inc. All rights reserved.
 *  @abstract  Reduction filters for MetalPerformanceShaders
 */

#ifndef MPS_MPSImageReduce_h
#define MPS_MPSImageReduce_h

#include <MPSImage/MPSImageKernel.h>


/*!
 *  @class      MPSImageReduceUnary
 *  @discussion The MPSImageReduce performs a reduction operation
 *              The reduction operations supported are:
 *                   - Reduce row min
 *                   - Reduce column min
 *                   - Reduce row max
 *                   - Reduce column max
 *                   - Reduce row mean
 *                   - Reduce column mean
 *                   - Reduce row sum
 *                   - Reduce column sum
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
@interface  MPSImageReduceUnary : MPSUnaryImageKernel

/*! @property   clipRectSource
 *  @abstract   The source rectangle to use when reading data.
 *  @discussion A MTLRegion that indicates which part of the source to read. If the clipRectSource does not lie
 *              completely within the source image, the intersection of the image bounds and clipRectSource will
 *              be used. The clipRectSource replaces the MPSUnaryImageKernel offset parameter for this filter.
 *              The latter is ignored.   Default: MPSRectNoClip, use the entire source texture.
 *
 *              The clipRect specified in MPSUnaryImageKernel is used to control the origin in the destination texture
 *              where the min, max values are written.  The clipRect.width must be >=2.  The clipRect.height must be >= 1.
 *
 */
@property (readwrite, nonatomic) MTLRegion clipRectSource;

/*
 * You must use one of the sub-classes of MPSImageReduceUnary.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device     NS_UNAVAILABLE;

@end  /* MPSImageReduceUnary */

/*!
 *  @class      MPSImageReduceRowMin
 *  @discussion The MPSImageReduceRowMin performs a reduction operation returning the mininmum value for each row of an image
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
@interface  MPSImageReduceRowMin : MPSImageReduceUnary

/*!
 *  @abstract Specifies information to apply the reduction operation on an image.
 *  @param    device            The device the filter will run on
 *  @return     A valid MPSImageReduce object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device     NS_DESIGNATED_INITIALIZER;

@end  /* MPSImageReduceRowMin */


/*!
 *  @class      MPSImageReduceColumnMin
 *  @discussion The MPSImageReduceColumnMin performs a reduction operation returning the mininmum value for each column of an image
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
@interface  MPSImageReduceColumnMin : MPSImageReduceUnary

/*!
 *  @abstract Specifies information to apply the reduction operation on an image.
 *  @param    device            The device the filter will run on
 *  @return     A valid MPSImageReduce object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device     NS_DESIGNATED_INITIALIZER;

@end  /* MPSImageReduceColumnMin */

/*!
 *  @class      MPSImageReduceRowMax
 *  @discussion The MPSImageReduceRowMax performs a reduction operation returning the maximum value for each row of an image
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
@interface  MPSImageReduceRowMax : MPSImageReduceUnary

/*!
 *  @abstract Specifies information to apply the reduction operation on an image.
 *  @param    device            The device the filter will run on
 *  @return     A valid MPSImageReduce object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device     NS_DESIGNATED_INITIALIZER;

@end  /* MPSImageReducenRowMax */

/*!
 *  @class      MPSImageReduceColumnMax
 *  @discussion The MPSImageReduceColumnMax performs a reduction operation returning the maximum value for each column of an image
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
@interface  MPSImageReduceColumnMax : MPSImageReduceUnary

/*!
 *  @abstract Specifies information to apply the reduction operation on an image.
 *  @param    device            The device the filter will run on
 *  @return     A valid MPSImageReduce object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device     NS_DESIGNATED_INITIALIZER;

@end  /* MPSImageReduceColumnMax */

/*!
 *  @class      MPSImageReduceRowMean
 *  @discussion The MPSImageReduceRowMean performs a reduction operation returning the mean value for each row of an image
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
@interface  MPSImageReduceRowMean : MPSImageReduceUnary

/*!
 *  @abstract Specifies information to apply the reduction operation on an image.
 *  @param    device            The device the filter will run on
 *  @return     A valid MPSImageReduce object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device     NS_DESIGNATED_INITIALIZER;

@end  /* MPSImageReduceRowMean */

/*!
 *  @class      MPSImageReduceColumnMean
 *  @discussion The MPSImageReduceColumnMean performs a reduction operation returning the mean value for each column of an image
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
@interface  MPSImageReduceColumnMean : MPSImageReduceUnary

/*!
 *  @abstract Specifies information to apply the reduction operation on an image.
 *  @param    device            The device the filter will run on
 *  @return     A valid MPSImageReduce object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device     NS_DESIGNATED_INITIALIZER;

@end  /* MPSImageReduceColumnMean */

/*!
 *  @class      MPSImageReduceRowSum
 *  @discussion The MPSImageReduceRowSum performs a reduction operation returning the sum for each row of an image
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
@interface  MPSImageReduceRowSum : MPSImageReduceUnary

/*!
 *  @abstract Specifies information to apply the reduction operation on an image.
 *  @param    device            The device the filter will run on
 *  @return     A valid MPSImageReduce object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device     NS_DESIGNATED_INITIALIZER;

@end  /* MPSImageReduceRowSum */

/*!
 *  @class      MPSImageReduceColumnSum
 *  @discussion The MPSImageReduceColumnSum performs a reduction operation returning the sum for each column of an image
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
@interface  MPSImageReduceColumnSum : MPSImageReduceUnary

/*!
 *  @abstract Specifies information to apply the reduction operation on an image.
 *  @param    device            The device the filter will run on
 *  @return     A valid MPSImageReduce object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device     NS_DESIGNATED_INITIALIZER;

@end  /* MPSImageReduceColumnSum */

#endif  /* MPS_MSImageReduce_h */

