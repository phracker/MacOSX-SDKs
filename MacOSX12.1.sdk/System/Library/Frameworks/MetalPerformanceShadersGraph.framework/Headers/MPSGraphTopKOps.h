//
//  MPSGraphTopKOps.h
//  MPSGraph
//
//  Created by Chris Bayley on 9/21/20.
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#ifndef MPSGraphTopKOps_h
#define MPSGraphTopKOps_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

MPS_CLASS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
@interface MPSGraph(MPSGraphTopKOps)

/*!
 *  @abstract   Create TopK op and return the value and indices tensors
 *  @discussion Finds the k largest values along the minor dimension of the input. The source must have
 *              at least k elements along its minor dimension.
 *              The first element of the result array corresponds to the top values, and the second
 *              array corresponds to the indices of the top values.
 *              To perform a vertical TopK a transpose can be inserted at the minor dimension of the
 *              incoming tensor.
 *
 *  @param      source   Tensor containing source data
 *  @param      k              The number of largest values to return
 *  @param      name        The name for the operation
 *
 *  @return     A valid MPSGraphTensor array of size 2
 */
-(NSArray<MPSGraphTensor *> *) topKWithSourceTensor:(MPSGraphTensor *) source
                                                  k:(NSUInteger) k
                                               name:(NSString * _Nullable) name
MPS_SWIFT_NAME( topK(_:k:name:) );

/*!
 *  @abstract   Create TopK op and return the result tensor
 *  @discussion Finds the k largest values along the minor dimension of the input. The source must have
 *              at least k elements along its minor dimension.
 *              The first element of the result array corresponds to the top values, and the second
 *              array corresponds to the indices of the top values.
 *              To perform a vertical TopK a transpose can be inserted at the minor dimension of the
 *              incoming tensor.
 *
 *  @param      source     Tensor containing source data
 *  @param      kTensor   Tensor of the number of largest values to return
 *  @param      name          The name for the operation
 *
 *  @return     A valid MPSGraphTensor array of size 2
 */
-(NSArray<MPSGraphTensor *> *) topKWithSourceTensor:(MPSGraphTensor *) source
                                            kTensor:(MPSGraphTensor *) kTensor
                                               name:(NSString * _Nullable) name
MPS_SWIFT_NAME( topK(_:kTensor:name:) );

@end

@interface MPSGraph(MPSGraphTopKGradientOps)

/*!
 *  @abstract   Create TopKGradient op and return the result tensor
 *  @discussion Finds the K largest values along the minor dimension of the input. The input must have
 *              at least K elements along its minor dimension.
 *              To perform a vertical TopK a transpose can be inserted at the minor dimension of the
 *              incoming tensor.
 *
 *  @param      gradient   Tensor containing the incoming gradient
 *  @param      source        Tensor containing source data
 *  @param      k                   The number of largest values to return
 *  @param      name            The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) topKWithGradientTensor:(MPSGraphTensor *) gradient
                                    source:(MPSGraphTensor *) source
                                         k:(NSUInteger) k
                                      name:(NSString * _Nullable) name
MPS_SWIFT_NAME( topKGradient(_:input:k:name:) );

/*!
 *  @abstract   Create TopKGradient op and return the result tensor
 *  @discussion Finds the K largest values along the minor dimension of the input. The input must have
 *              at least K elements along its minor dimension.
 *              To perform a vertical TopK a transpose can be inserted at the minor dimension of the
 *              incoming tensor.
 *
 *  @param      gradient   Tensor containing the incoming gradient
 *  @param      source        Tensor containing source data
 *  @param      kTensor     Tensor of the number of largest values to return
 *  @param      name            The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) topKWithGradientTensor:(MPSGraphTensor *) gradient
                                    source:(MPSGraphTensor *) source
                                   kTensor:(MPSGraphTensor *) kTensor
                                      name:(NSString * _Nullable) name
MPS_SWIFT_NAME( topKGradient(_:input:kTensor:name:) );

@end

NS_ASSUME_NONNULL_END

#endif /* MPSGraphTopKOps_h */
