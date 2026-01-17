/*!
 *  @header MPSImageMorphology.h
 *  @framework MetalPerformanceShaders
 *
 *  @copyright Copyright (c) 2015 Apple Inc. All rights reserved.
 *  @abstract MetalPerformanceShaders morphological operators
 */

#ifndef MPS_MPSImageMorphology_h
#define MPS_MPSImageMorphology_h

#include <MPSImage/MPSImageKernel.h>


/*!
 *  @class      MPSImageAreaMax
 *  @discussion The MPSImageAreaMax kernel finds the maximum pixel value in a rectangular region centered around each pixel
 *              in the source image. If there are multiple channels in the source image, each channel is processed independently.
 *              The edgeMode property is assumed to always be MPSImageEdgeModeClamp for this filter.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(9.0), macCatalyst(13.0), tvos(9.0))
@interface  MPSImageAreaMax : MPSUnaryImageKernel

/*! @property kernelHeight
 *  @abstract  The height of the filter window. Must be an odd number.
 */
@property (readonly, nonatomic)   NSUInteger  kernelHeight;

/*! @property kernelWidth
 *  @abstract  The width of the filter window. Must be an odd number.
 */
@property (readonly, nonatomic)   NSUInteger  kernelWidth;

/*!
 *  @abstract Set the kernel height and width
 *  @param      device              The device the filter will run on
 *  @param      kernelWidth         The width of the kernel. Must be an odd number.
 *  @param      kernelHeight        The height of the kernel. Must be an odd number.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                           kernelWidth: (NSUInteger)kernelWidth
                          kernelHeight: (NSUInteger)kernelHeight            NS_DESIGNATED_INITIALIZER;


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
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER
                    MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0));

/* You must use initWithDevice:kernelWidth:kernelHeight: instead. */
-(nonnull instancetype) initWithDevice:(nonnull id<MTLDevice>)device        NS_UNAVAILABLE;

@end  /* MPSImageAreaMax */

/*!
 *  @class      MPSImageAreaMin
 *  @discussion The MPSImageAreaMin finds the minimum pixel value in a rectangular region centered around each pixel in the
 *               source image. If there are multiple channels in the source image, each channel is processed independently.
 *               It has the same methods as MPSImageAreaMax
 *               The edgeMode property is assumed to always be MPSImageEdgeModeClamp for this filter.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(9.0), macCatalyst(13.0), tvos(9.0))
@interface  MPSImageAreaMin : MPSImageAreaMax

@end  /* MPSImageAreaMin */

/*!
 *  @class      MPSImageDilate
 *  @discussion The MPSImageDilate finds the maximum pixel value in a rectangular region centered around each pixel in the
 *              source image. It is like the MPSImageAreaMax, except that the intensity at each position is calculated relative
 *              to a different value before determining which is the maximum pixel value, allowing for shaped, non-rectangular
 *              morphological probes.
 *  @code
 *          for each pixel in the filter window:
 *              value =  pixel[filterY][filterX] - filter[filterY*filter_width+filterX]
 *              if( value > bestValue ){
 *                   result = value
 *                   bestValue = value;
 *              }
 *  @endcode
 *              A filter that contains all zeros and is identical to a MPSImageAreaMax filter.  The center filter element
 *              is assumed to be 0 to avoid causing a general darkening of the image.
 *
 *              The edgeMode property is assumed to always be MPSImageEdgeModeClamp for this filter.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(9.0), macCatalyst(13.0), tvos(9.0))
@interface  MPSImageDilate : MPSUnaryImageKernel
/*! @property kernelHeight
 *  @abstract  The height of the filter window. Must be an odd number.
 */
@property (readonly, nonatomic)   NSUInteger  kernelHeight;

/*! @property kernelWidth
 *  @abstract  The width of the filter window. Must be an odd number.
 */
@property (readonly, nonatomic)   NSUInteger  kernelWidth;


/*!
 *  @abstract   Init a object with kernel height, width and weight values.
 *  @discussion Each dilate shape probe defines a 3D surface of values.
 *              These are arranged in order left to right, then top to bottom
 *              in a 1D array. (values[kernelWidth*y+x] = probe[y][x])
 *              Values should be generally be in the range [0,1] with the center 
 *              pixel tending towards 0 and edges towards 1. However, any numerical
 *              value is allowed. Calculations are subject to the usual floating-point
 *              rounding error.
 *
 *  @param      device              The device the filter will run on
 *  @param      kernelWidth         The width of the kernel. Must be an odd number.
 *  @param      kernelHeight        The height of the kernel. Must be an odd number.
 *  @param      values              The set of values to use as the dilate probe.
 *                                  The values are copied into the filter. To avoid 
 *                                  image ligthening or darkening, the center value should
 *                                  be 0.0f.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                           kernelWidth: (NSUInteger)kernelWidth
                          kernelHeight: (NSUInteger)kernelHeight
                                values: (const float* __nonnull) values       NS_DESIGNATED_INITIALIZER;

/* You must use initWithDevice:kernelWidth:kernelHeight:values: instead. */
-(nonnull instancetype) initWithDevice:(nonnull id<MTLDevice>)device        NS_UNAVAILABLE;

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
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER
                        MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0));


@end  /* MPSImageDilate */


/*!
 *  @class      MPSImageErode
 *  @discussion The MPSImageErode filter finds the minimum pixel value in a rectangular region centered around each pixel in the
 *              source image. It is like the MPSImageAreaMin, except that the intensity at each position is calculated relative
 *              to a different value before determining which is the maximum pixel value, allowing for shaped, non-rectangular
 *              morphological probes.
 *  @code
 *          for each pixel in the filter window:
 *              value =  pixel[filterY][filterX] + filter[filterY*filter_width+filterX]
 *              if( value < bestValue ){
 *                   result = value
 *                   bestValue = value;
 *              }
 *  @endcode
 *              A filter that contains all zeros is identical to a MPSImageAreaMin filter. The center filter element
 *              is assumed to be 0, to avoid causing a general lightening of the image.
 *
 *              The definition of the filter for MPSImageErode is different from vImage. (MPSErode_filter_value = 1.0f-vImageErode_filter_value.)
 *              This allows MPSImageDilate and MPSImageErode to use the same filter, making open and close operators easier to write.
 *              The edgeMode property is assumed to always be MPSImageEdgeModeClamp for this filter.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(9.0), macCatalyst(13.0), tvos(9.0))
@interface  MPSImageErode : MPSImageDilate
@end

#endif  /* MPS_MSImageMorphology_h */
