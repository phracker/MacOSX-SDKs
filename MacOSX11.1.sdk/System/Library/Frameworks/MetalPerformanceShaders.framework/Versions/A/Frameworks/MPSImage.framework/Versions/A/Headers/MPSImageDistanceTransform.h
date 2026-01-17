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
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
@interface  MPSImageEuclideanDistanceTransform : MPSUnaryImageKernel

/*! @property   searchLimitRadius
 *  @abstract   Defines a search scope size around output pixel to limit closest non-zero pixel search. Optional variable.
 *  @discussion When the non-zeroes in the input image are on average very far away from each other (ie. the distances are large),
 *              the distance calculation algorithm has to work harder to find the closest pixel. If you don't care about getting exact
 *              results beyond a certain distance you can use this property to limit the search space and speed up the kernels.
 *              In case there are no non-zero pixels within this search scope around the output pixel, then the output value will
 *              be some number that is larger than this search limit. Normally you should be fine with the default value of FLT_MAX,
 *              which results in the exact EDT, so use this only if you need additional performance.
 *              Typical good values are: 32, 64, 96, 128.
 *              Default: FLT_MAX
 */
@property (readwrite, nonatomic) float searchLimitRadius MPS_AVAILABLE_STARTING(macos(11.0), ios(14.0), macCatalyst(14.0), tvos(14.0));


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
