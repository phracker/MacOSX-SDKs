//
//  MPSNDArrayGather.h
//  MPSNDArray
//
//  Created on 1/22/19.
//  Copyright © 2019 Apple. All rights reserved.
//

#ifndef MPSNDArrayGather_h
#define MPSNDArrayGather_h

#import <MPSNDArray/MPSNDArrayKernel.h>
#import <MPSNDArray/MPSNDArrayGradientState.h>

/*! @class  A state created to record a MPSNDArrayGather kernel properties
 *          at the time an -encode call was made.
 *
 *          Must be created with the appropriate MPSNDArray kernel method, for example:
 *
 *          MPSNDArrayGather* gather = [[MPSNDArrayGather alloc] initWithDevice: device];
 *          MPSNDArrayGatherGradientState* state = [gather resultStateForSourceArrays:...];
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0))
@interface MPSNDArrayGatherGradientState : MPSNDArrayGradientState
@end

/*!
 *  @class      MPSNDArrayGather
 *
 *  @dependency This depends on Metal.framework.
 *
 *  @abstract   Applies a gather operation along a given axis.  The encoded primary source array
 *              contains the data and the secondary array is a 1-D MPSNDArray containing the
 *              indices.
 *
 *                  For each dimension other than axis
 *                      result[i] = source[i]; 0 <= i < array slice length along dimension
 *                  Along the specified axis
 *                      result[i] = source[indices[i]]; 0 <= i < number of indices
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.15), ios(13), macCatalyst(13), tvos(13))
@interface MPSNDArrayGather : MPSNDArrayBinaryKernel

/*! @property  axis
 *  @abstract  The axis along which to apply the gather operation.
 *              Defaults to zero.
 */
@property (readwrite, nonatomic)  NSUInteger axis;

@end    // MPSNDArrayGather

/*!
 *  @class      MPSNDArrayGatherGradient
 *
 *  @dependency This depends on Metal.framework.
 *
 *  @abstract   Applies the gradient operation corresponding to a forward gather operation.
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.15), ios(13), macCatalyst(13), tvos(13))
@interface MPSNDArrayGatherGradient : MPSNDArrayBinaryPrimaryGradientKernel

@end    // MPSNDArrayGatherGradient

#endif /* MPSNDArrayGather_h */
