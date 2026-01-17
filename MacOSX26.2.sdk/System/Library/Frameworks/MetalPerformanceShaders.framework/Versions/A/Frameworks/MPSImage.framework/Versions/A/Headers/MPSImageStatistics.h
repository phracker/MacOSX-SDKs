/*!
 *  @header MPSImageStatistics.h
 *  @framework MetalPerformanceShaders.framework
 *
 *  @copyright Copyright (c) 2016 Apple Inc. All rights reserved.
 *  @abstract MetalPerformanceShaders image statistics filters
 */

#ifndef MPS_MPSImageStatistics_h
#define MPS_MPSImageStatistics_h

#include <MPSImage/MPSImageKernel.h>
#include <simd/simd.h>


/*!
 *  @class      MPSImageStatisticsMinAndMax
 *  @discussion The MPSImageStatisticsMinAndMax computes the minimum and maximum pixel values for a given region of an image.
 *              The min and max values are written to the destination image at the following pixel locations:
 *                  - min value is written at pixel location (0, 0)
 *                  - max value is written at pixel location (1, 0)
 *              
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0))
@interface  MPSImageStatisticsMinAndMax : MPSUnaryImageKernel

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

/*!
 *  @abstract Specifies information to apply the statistics min-max operation on an image.
 *  @param    device            The device the filter will run on
 *  @return     A valid MPSImageStatisticsMinAndMax object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device     NS_DESIGNATED_INITIALIZER;

/*! @abstract NSSecureCoding compatability
 *  @discussion While the standard NSSecureCoding/NSCoding method
 *              -initWithCoder: should work, since the file can't
 *              know which device your data is allocated on, we
 *              have to guess and may guess incorrectly.  To avoid
 *              that problem, use initWithCoder:device instead.
 *  @param      aDecoder    The NSCoder subclass with your serialized MPSKernel
 *  @param      device      The MTLDevice on which to make the MPSKernel
 *  @return     A new MPSKernel object, or nil if failure.
 */
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

@end  /* MPSImageStatisticsMinAndMax */


/*!
 *  @class      MPSImageStatisticsMeanAndVariance
 *  @discussion The MPSImageStatisticsMeanAndVariance computes the mean and variance for a given region of an image.
 *              The mean and variance values are written to the destination image at the following pixel locations:
 *                  - mean value is written at pixel location (0, 0)
 *                  - variance value is written at pixel location (1, 0)
 *
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0))
@interface  MPSImageStatisticsMeanAndVariance : MPSUnaryImageKernel

/*! @property   clipRectSource
 *  @abstract   The source rectangle to use when reading data.
 *  @discussion A MTLRegion that indicates which part of the source to read. If the clipRectSource does not lie
 *              completely within the source image, the intersection of the image bounds and clipRectSource will
 *              be used. The clipRectSource replaces the MPSUnaryImageKernel offset parameter for this filter.
 *              The latter is ignored.   Default: MPSRectNoClip, use the entire source texture.
 *
 *              The clipRect specified in MPSUnaryImageKernel is used to control the origin in the destination texture
 *              where the mean value is written.
 *
 */
@property (readwrite, nonatomic) MTLRegion clipRectSource;

/*!
 *  @abstract Specifies information to apply the statistics mean operation on an image.
 *  @param    device            The device the filter will run on
 *  @return     A valid MPSImageStatisticsMeanAndVariance object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device     NS_DESIGNATED_INITIALIZER;

/*! @abstract NSSecureCoding compatability
 *  @discussion While the standard NSSecureCoding/NSCoding method
 *              -initWithCoder: should work, since the file can't
 *              know which device your data is allocated on, we
 *              have to guess and may guess incorrectly.  To avoid
 *              that problem, use initWithCoder:device instead.
 *  @param      aDecoder    The NSCoder subclass with your serialized MPSKernel
 *  @param      device      The MTLDevice on which to make the MPSKernel
 *  @return     A new MPSKernel object, or nil if failure.
 */
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

@end  /* MPSImageStatisticsMeanAndVariance */


/*!
 *  @class      MPSImageStatisticsMean
 *  @discussion The MPSImageStatisticsMean computes the mean for a given region of an image.
 *
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0))
@interface  MPSImageStatisticsMean : MPSUnaryImageKernel

/*! @property   clipRectSource
 *  @abstract   The source rectangle to use when reading data.
 *  @discussion A MTLRegion that indicates which part of the source to read. If the clipRectSource does not lie
 *              completely within the source image, the intersection of the image bounds and clipRectSource will
 *              be used. The clipRectSource replaces the MPSUnaryImageKernel offset parameter for this filter.
 *              The latter is ignored.   Default: MPSRectNoClip, use the entire source texture.
 *
 *              The clipRect specified in MPSUnaryImageKernel is used to control the origin in the destination texture
 *              where the mean value is written.
 *
 */
@property (readwrite, nonatomic) MTLRegion clipRectSource;

/*!
 *  @abstract Specifies information to apply the statistics mean operation on an image.
 *  @param    device            The device the filter will run on
 *  @return     A valid MPSImageStatisticsMean object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device     NS_DESIGNATED_INITIALIZER;

/*! @abstract NSSecureCoding compatability
 *  @discussion While the standard NSSecureCoding/NSCoding method
 *              -initWithCoder: should work, since the file can't
 *              know which device your data is allocated on, we
 *              have to guess and may guess incorrectly.  To avoid
 *              that problem, use initWithCoder:device instead.
 *  @param      aDecoder    The NSCoder subclass with your serialized MPSKernel
 *  @param      device      The MTLDevice on which to make the MPSKernel
 *  @return     A new MPSKernel object, or nil if failure.
 */
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

@end  /* MPSImageStatisticsMean */


#endif  /* MPS_MSImageStatistics_h */

