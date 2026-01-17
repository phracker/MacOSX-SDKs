//
//  MPSNDArrayIdentity.h
//  MPS
//
//  Created by Dhruv Saksena on 8/3/19.
//  Copyright © 2019 Apple. All rights reserved.
//

#ifndef MPSNDArrayIdentity_h
#define MPSNDArrayIdentity_h

#import <MPSNDArray/MPSNDArrayKernel.h>

#pragma mark - Base class Identity Kernels

/*!
 *  @class      MPSNDArrayIdentityKernel
 *
 *  @dependency This depends on Metal.framework.
 *  @abstract   An efficient kernel to handle copies, transposed-copies and reshapes.
 *
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0), visionos(2.0) )
@interface MPSNDArrayIdentity : MPSNDArrayUnaryKernel

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

/*! @abstract   Do a reshape operation, either by trying to alias the array, returning an arrayview, or by copying.
 *  @param      cmdBuf          The command buffer into which to encode the kernel, or to create a temporary array alias.
 *  @param      sourceArray    Source array. If this function returns a non-nil result, then the readCount of `sourceArray` is decremented.
 *  @param      shape       The new shape, given in TF dimension ordering (as always with MPSShape).
 *  @param      destinationArray    If not nil, then the result of reshape will be copied to this. Shape of `destinationArray` must match `shape`.
 *  @result     If `destinationArray` is not nil, then `destinationArray`. Otherwise aliasing is tried, and if aliasing is not possible
 *              due to existing slices or transposes nil is returned. If aliasing is successful, then a new arrayview of `sourceArray`
 *              is returned; If `sourceArray` is a `MPSTemporaryArray` then a `MPSTemporaryArray` is returned referencing the same data,
 *              otherwise a `MPSNDArray` type result is returned.
 *   */
-(MPSNDArray * __nullable) reshapeWithCommandBuffer: (__nullable id <MTLCommandBuffer>) cmdBuf
                                        sourceArray: (MPSNDArray * __nonnull) sourceArray
                                              shape: (MPSShape * __nonnull) shape
                                   destinationArray: (MPSNDArray * __nullable) destinationArray;
// Variant with MPS dimension-ordering
-(MPSNDArray * __nullable) reshapeWithCommandBuffer: (__nullable id <MTLCommandBuffer>) cmdBuf
                                        sourceArray: (MPSNDArray * __nonnull) sourceArray
                                     dimensionCount: (NSUInteger) numberOfDimensions
                                     dimensionSizes: (NSUInteger*__nonnull) dimensionSizes
                                   destinationArray: (MPSNDArray * __nullable) destinationArray;

-(MPSNDArray * __nullable) reshapeWithCommandEncoder: (__nullable id <MTLComputeCommandEncoder>) encoder
                                       commandBuffer: (__nullable id <MTLCommandBuffer>) cmdBuf
                                        sourceArray: (MPSNDArray * __nonnull) sourceArray
                                              shape: (MPSShape * __nonnull) shape
                                   destinationArray: (MPSNDArray * __nullable) destinationArray;
// Variant with MPS dimension-ordering
-(MPSNDArray * __nullable) reshapeWithCommandEncoder: (__nullable id <MTLComputeCommandEncoder>) encoder
                                       commandBuffer: (__nullable id <MTLCommandBuffer>) cmdBuf
                                        sourceArray: (MPSNDArray * __nonnull) sourceArray
                                     dimensionCount: (NSUInteger) numberOfDimensions
                                     dimensionSizes: (NSUInteger*__nonnull) dimensionSizes
                                   destinationArray: (MPSNDArray * __nullable) destinationArray;

@end    // MPSNDArrayIdentity

#endif /* MPSNDArrayIdentity_h */
