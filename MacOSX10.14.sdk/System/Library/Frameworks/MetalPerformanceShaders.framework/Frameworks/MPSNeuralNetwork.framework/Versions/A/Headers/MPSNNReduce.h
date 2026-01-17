//
//  MPSNNReduce.h
//  MPSNeuralNetwork
//
//  Created by Dhruv Saksena on 10/31/17.
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef MPSNNReduce_h
#define MPSNNReduce_h

#include <MPSNeuralNetwork/MPSCNNKernel.h>

#ifdef __cplusplus
extern "C" {
#endif


/*!
 *  @class      MPSNNReduceUnary
 *  @discussion The MPSNNReduce performs a reduction operation
 *              The reduction operations supported are:
 *                   - Reduce row min
 *                   - Reduce column min
 *                   - Reduce feature channels min
 *                   - Reduce row max
 *                   - Reduce column max
 *                   - Reduce feature channels max
 *                   - Reduce row mean
 *                   - Reduce column mean
 *                   - Reduce feature channels mean
 *                   - Reduce row sum
 *                   - Reduce column sum
 *                   - Reduce feature channels sum
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3))
@interface  MPSNNReduceUnary : MPSCNNKernel

/*! @property   clipRectSource
 *  @abstract   The source rectangle to use when reading data.
 *  @discussion A MTLRegion that indicates which part of the source to read. If the clipRectSource does not lie
 *              completely within the source image, the intersection of the image bounds and clipRectSource will
 *              be used. The clipRectSource replaces the MPSCNNKernel offset parameter for this filter.
 *              The latter is ignored.   Default: MPSRectNoClip, use the entire source texture.
 *
 */
@property (readwrite, nonatomic) MTLRegion clipRectSource;

/*
 * You must use one of the sub-classes of MPSNNReduceUnary.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device     NS_UNAVAILABLE;

@end  /* MPSNNReduceUnary */


/*!
 *  @class      MPSNNReduceRowMin
 *  @discussion The MPSNNReduceRowMin performs a reduction operation returning the mininmum value for each row of an image
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3))
@interface  MPSNNReduceRowMin : MPSNNReduceUnary

/*!
 *  @abstract Specifies information to apply the reduction operation on an image.
 *  @param    device            The device the filter will run on
 *  @return     A valid MPSNNReduceRowMin object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device     NS_DESIGNATED_INITIALIZER;

@end  /* MPSNNReduceRowMin */


/*!
 *  @class      MPSNNReduceColumnMin
 *  @discussion The MPSNNReduceColumnMin performs a reduction operation returning the mininmum value for each column of an image
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3))
@interface  MPSNNReduceColumnMin : MPSNNReduceUnary

/*!
 *  @abstract Specifies information to apply the reduction operation on an image.
 *  @param    device            The device the filter will run on
 *  @return     A valid MPSNNReduceColumnMin object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device     NS_DESIGNATED_INITIALIZER;

@end  /* MPSNNReduceColumnMin */

/*!
 *  @class      MPSNNReduceFeatureChannelsMin
 *  @discussion The MPSNNReduceFeatureChannelsMin performs a reduction operation returning the mininmum value for feature channels of an image
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3))
@interface  MPSNNReduceFeatureChannelsMin : MPSNNReduceUnary

/*!
 *  @abstract Specifies information to apply the reduction operation on an image.
 *  @param    device            The device the filter will run on
 *  @return     A valid MPSNNReduceFeatureChannelsMin object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device     NS_DESIGNATED_INITIALIZER;

@end  /* MPSNNReduceFeatureChannelsMin */

/*!
 *  @class      MPSNNReduceFeatureChannelsArgumentMin
 *  @discussion The MPSNNReduceFeatureChannelsArgumentMin returns the argument index that is the
 *              location of the minimum value for feature channels of an image
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.14), ios(12.0), tvos(12.0))
@interface  MPSNNReduceFeatureChannelsArgumentMin : MPSNNReduceUnary

/*!
*  @abstract Specifies information to apply the reduction operation on an image.
*  @param    device            The device the filter will run on
*  @return     A valid MPSNNReduceFeatureChannelsArgumentMin object or nil, if failure.
*/

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device     NS_DESIGNATED_INITIALIZER;

@end  /* MPSNNReduceFeatureChannelsArgumentMin */


/*!
 *  @class      MPSNNReduceRowMax
 *  @discussion The MPSNNReduceRowMax performs a reduction operation returning the maximum value for each row of an image
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3))
@interface  MPSNNReduceRowMax : MPSNNReduceUnary

/*!
 *  @abstract Specifies information to apply the reduction operation on an image.
 *  @param    device            The device the filter will run on
 *  @return     A valid MPSNNReduceRowMax object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device     NS_DESIGNATED_INITIALIZER;

@end  /* MPSNNReducenRowMax */

/*!
 *  @class      MPSNNReduceColumnMax
 *  @discussion The MPSNNReduceColumnMax performs a reduction operation returning the maximum value for each column of an image
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3))
@interface  MPSNNReduceColumnMax : MPSNNReduceUnary

/*!
 *  @abstract Specifies information to apply the reduction operation on an image.
 *  @param    device            The device the filter will run on
 *  @return     A valid MPSNNReduceColumnMax object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device     NS_DESIGNATED_INITIALIZER;

@end  /* MPSNNReduceColumnMax */

/*!
 *  @class      MPSNNReduceFeatureChannelsMax
 *  @discussion The MPSNNReduceFeatureChannelsMax performs a reduction operation returning the maximum value for feature channels of an image
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3))
@interface  MPSNNReduceFeatureChannelsMax : MPSNNReduceUnary

/*!
 *  @abstract Specifies information to apply the reduction operation on an image.
 *  @param    device            The device the filter will run on
 *  @return     A valid MPSNNReduceFeatureChannelsMax object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device     NS_DESIGNATED_INITIALIZER;

@end  /* MPSNNReduceFeatureChannelsMax */

/*!
 *  @class      MPSNNReduceFeatureChannelsArgumentMax
 *  @discussion The MPSNNReduceFeatureChannelsArgumentMax performs returns the argument index that is the
 *              location of the maximum value for feature channels of an image
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.14), ios(12.0), tvos(12.0))
@interface  MPSNNReduceFeatureChannelsArgumentMax : MPSNNReduceUnary

/*!
*  @abstract Specifies information to apply the reduction operation on an image.
*  @param    device            The device the filter will run on
*  @return     A valid MPSNNReduceFeatureChannelsArgumentMax object or nil, if failure.
*/

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device     NS_DESIGNATED_INITIALIZER;

@end  /* MPSNNReduceFeatureChannelsArgumentMax */
    

/*!
 *  @class      MPSNNReduceRowMean
 *  @discussion The MPSNNReduceRowMean performs a reduction operation returning the mean value for each row of an image
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3))
@interface  MPSNNReduceRowMean : MPSNNReduceUnary

/*!
 *  @abstract Specifies information to apply the reduction operation on an image.
 *  @param    device            The device the filter will run on
 *  @return     A valid MPSNNReduceRowMean object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device     NS_DESIGNATED_INITIALIZER;

@end  /* MPSNNReduceRowMean */

/*!
 *  @class      MPSNNReduceColumnMean
 *  @discussion The MPSNNReduceColumnMean performs a reduction operation returning the mean value for each column of an image
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3))
@interface  MPSNNReduceColumnMean : MPSNNReduceUnary

/*!
 *  @abstract Specifies information to apply the reduction operation on an image.
 *  @param    device            The device the filter will run on
 *  @return     A valid MPSNNReduceColumnMean object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device     NS_DESIGNATED_INITIALIZER;

@end  /* MPSNNReduceColumnMean */

/*!
 *  @class      MPSNNReduceFeatureChannelsMean
 *  @discussion The MPSNNReduceFeatureChannelsMean performs a reduction operation returning the mean value for each column of an image
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3))
@interface  MPSNNReduceFeatureChannelsMean : MPSNNReduceUnary

/*!
 *  @abstract Specifies information to apply the reduction operation on an image.
 *  @param    device            The device the filter will run on
 *  @return     A valid MPSNNReduceFeatureChannelsMean object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device     NS_DESIGNATED_INITIALIZER;

@end  /* MPSNNReduceFeatureChannelsMean */

/*!
 *  @class      MPSNNReduceRowSum
 *  @discussion The MPSNNReduceRowSum performs a reduction operation returning the sum for each row of an image
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3))
@interface  MPSNNReduceRowSum : MPSNNReduceUnary

/*!
 *  @abstract Specifies information to apply the reduction operation on an image.
 *  @param    device            The device the filter will run on
 *  @return     A valid MPSNNReduceRowSum object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device     NS_DESIGNATED_INITIALIZER;

@end  /* MPSNNReduceRowSum */

/*!
 *  @class      MPSNNReduceColumnSum
 *  @discussion The MPSNNReduceColumnSum performs a reduction operation returning the sum for each column of an image
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3))
@interface  MPSNNReduceColumnSum : MPSNNReduceUnary

/*!
 *  @abstract Specifies information to apply the reduction operation on an image.
 *  @param    device            The device the filter will run on
 *  @return     A valid MPSNNReduceColumnSum object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device     NS_DESIGNATED_INITIALIZER;

@end  /* MPSNNReduceColumnSum */


/*!
 *  @class      MPSNNReduceFeatureChannelsSum
 *  @discussion The MPSNNReduceFeatureChannelsSum performs a reduction operation returning the sum for each column of an image
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3))
@interface  MPSNNReduceFeatureChannelsSum : MPSNNReduceUnary

/*! @property   weight
 *  @abstract   The scale factor to apply to each feature channel value
 *  @discussion Each feature channel is multiplied by the weight value to compute a weighted sum or mean across feature channels
 *              The default value is 1.0.
 */
@property (readwrite, nonatomic) float weight;

/*!
 *  @abstract Specifies information to apply the reduction operation on an image.
 *  @param    device            The device the filter will run on
 *  @return     A valid MPSNNReduceFeatureChannelsSum object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device     NS_DESIGNATED_INITIALIZER;

@end  /* MPSNNReduceFeatureChannelsSum */


#pragma mark -
#pragma mark MPSNNReduceBinary

/*!
 *  @class      MPSNNReduceBinary
 *  @discussion The MPSNNReduce performs a reduction operation
 *              The reduction operations supported are:
 *                   - Reduce feature channels mean
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3))
@interface  MPSNNReduceBinary : MPSCNNBinaryKernel

/*!
 *  @abstract   The source rectangle to use when reading data from primary source
 *  @discussion A MTLRegion that indicates which part of the primary source to read. If the clipRectPrimarySource does not lie
 *              completely within the primary source image, the intersection of the image bounds and clipRectPrimarySource will
 *              be used. The primarySourceClipRect replaces the MPSBinaryImageKernel primaryOffset parameter for this filter.
 *              The latter is ignored.   Default: MPSRectNoClip, use the entire source texture.
 *
 *              The clipRect specified in MPSBinaryImageKernel is used to control the origin in the destination texture
 *              where the min, max values are written.  The clipRect.width must be >=2.  The clipRect.height must be >= 1.
 *
 */
@property (readwrite, nonatomic) MTLRegion primarySourceClipRect;

/*!
 *  @abstract   The source rectangle to use when reading data from secondary source
 *  @discussion A MTLRegion that indicates which part of the secondary source to read. If the clipRectSecondarySource does not lie
 *              completely within the secondary source image, the intersection of the image bounds and clipRectSecondarySource will
 *              be used. The secondarySourceClipRect replaces the MPSBinaryImageKernel secondaryOffset parameter for this filter.
 *              The latter is ignored.   Default: MPSRectNoClip, use the entire source texture.
 *
 *              The clipRect specified in MPSBinaryImageKernel is used to control the origin in the destination texture
 *              where the min, max values are written.  The clipRect.width must be >=2.  The clipRect.height must be >= 1.
 *
 */
@property (readwrite, nonatomic) MTLRegion secondarySourceClipRect;

/*
 * You must use one of the sub-classes of MPSNNReduceBinary.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device     NS_UNAVAILABLE;

@end  /* MPSNNReduceBinary */


MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3))
@interface  MPSNNReduceFeatureChannelsAndWeightsMean : MPSNNReduceBinary

/*!
 *  @abstract Specifies information to apply the reduction operation on an image.
 *  @param    device            The device the filter will run on
 *  @return   A valid MPSNNReduceFeatureChannelsAndWeightsMean object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device     NS_DESIGNATED_INITIALIZER;

@end  /* MPSNNReduceFeatureChannelsAndWeightsMean */

MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3))
@interface  MPSNNReduceFeatureChannelsAndWeightsSum : MPSNNReduceBinary

/*!
 *  @abstract   A boolean to indicate whether the reduction should perform a weighted sum of feature channels with non-zero weights
 *  @discussion If false, computes a dot product of the feature channels and weights.
 *              If true, computes a dot product of the feature channels and weights divided by the number of non-zero weights
 */
@property (readonly, nonatomic) bool doWeightedSumByNonZeroWeights;

/*!
 *  @abstract Specifies information to apply the reduction operation on an image.
 *  @param    device            The device the filter will run on
 *  @return   A valid MPSNNReduceFeatureChannelsAndWeightsMean object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device ;

/*!
 *  @abstract Specifies information to apply the reduction operation on an image.
 *  @param    device                         The device the filter will run on
 *  @param    doWeightedSumByNonZeroWeights  A boolean to indicate whether to compute a weighted sum or
 *                                           weighted sum divided by the number of non-zero weights
 *  @return   A valid MPSNNReduceFeatureChannelsAndWeightsSum object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                  doWeightedSumByNonZeroWeights: (bool)doWeightedSumByNonZeroWeights NS_DESIGNATED_INITIALIZER;

@end  /* MPSNNReduceFeatureChannelsAndWeightsSum */

#ifdef __cplusplus
}
#endif

#endif /* MPSNNReduce_h */
