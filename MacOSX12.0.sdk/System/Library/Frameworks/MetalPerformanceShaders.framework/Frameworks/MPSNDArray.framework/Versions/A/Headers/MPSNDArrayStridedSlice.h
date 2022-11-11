//
//  MPSNDArrayStridedSlice.h
//  MPS
//
//  Created on 1/10/19.
//  Copyright © 2019 Apple. All rights reserved.
//

#ifndef MPSNDArrayStridedSlice_h
#define MPSNDArrayStridedSlice_h

#import <MPSNDArray/MPSNDArrayKernel.h>

/*!
 *  @class      MPSNDStridedSlice
 *
 *  @dependency This depends on Metal.framework.
 *
 *  @abstract   Extracts a subset of the source array using the specified slice strides.
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.15), ios(13), macCatalyst(13), tvos(13))
@interface MPSNDArrayStridedSlice : MPSNDArrayUnaryKernel

/*! @property  strides
 *  @abstract  The strides to use when slicing the input array.
 */
@property (readwrite, nonatomic)  MPSNDArrayOffsets strides;

@end    // MPSNDArrayStridedSlice

/*!
 *  @class      MPSNDStridedSliceGradient
 *
 *  @dependency This depends on Metal.framework.
 *
 *  @abstract   Perform the gradient operation corresponding to a strided slice.
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.15), ios(13), macCatalyst(13), tvos(13))
@interface MPSNDArrayStridedSliceGradient : MPSNDArrayUnaryGradientKernel

@end    // MPSNDArrayStridedSliceGradient

#endif /* MPSNDArrayStridedSlice_h */
