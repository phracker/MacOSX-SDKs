/*!
 *  @header MPSImageTranspose.h
 *  @framework MetalPerformanceShaders.framework
 *
 *  @copyright Copyright (c) 2015 Apple Inc. All rights reserved.
 *  @abstract MetalPerformanceShaders transpose filters
 */

#ifndef MPS_MPSImageTranspose_h
#define MPS_MPSImageTranspose_h

#include <MPSImage/MPSImageKernel.h>

/*!
 *  @class      MPSImageTranspose
 *  @discussion The MPSImageTranspose transposes an image
 *
 *              This kernel accepts uint and int textures in addition to unorm and floating-point textures.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(9.0), tvos(9.0))
@interface  MPSImageTranspose : MPSUnaryImageKernel

@end    /* MPSImageTranspose */


#endif  /* MPS_MSImageTranspose_h */

