/*!
 *  @header MPSImageDistanceTransform.h
 *  @framework MetalPerformanceShaders
 *
 *  @copyright Copyright (c) 2018 Apple Inc. All rights reserved.
 *  @abstract MetalPerformanceShaders distance transform filters
 */

#ifndef MPS_MPSImageDistanceTransform_h
#define MPS_MPSImageDistanceTransform_h

#include <MPSImage/MPSImageKernel.h>
#include <simd/simd.h>

/*!
 *  @class      MPSImageEuclideanDistanceTransform
 *  @discussion Perform a Euclidean Distance Transform
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3))
@interface  MPSImageEuclideanDistanceTransform : MPSUnaryImageKernel

/*!
 *  @abstract Specifies information to apply the statistics min-max operation on an image.
 *  @param    device            The device the filter will run on
 *  @return     A valid MPSImageEuclideanDistanceTransform object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

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

@end  /* MPSImageEuclideanDistanceTransform */

#endif  /* MPS_MPSImageDistanceTransform_h */
