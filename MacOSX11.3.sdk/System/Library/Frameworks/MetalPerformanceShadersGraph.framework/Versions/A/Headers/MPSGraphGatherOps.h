//
//  MPSGatherOps.h
//  MPSGraph
//
//  Created on 3/10/20.
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#ifndef MPSGatherOps_h
#define MPSGatherOps_h

NS_ASSUME_NONNULL_BEGIN

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(GatherNDOps)
/*!
 *  @abstract   Create GatherND op and return the result tensor
 *  @discussion Gathers the slices in updatesTensor to the result tensor along the indices in indicesTensor.
 *              The gather is defined as
 *              @code
 *              B = batchDims
 *              U = updates.rank - B
 *              P = res.rank - B
 *              Q = inds.rank - B
 *              K = inds.shape[-1]
 *              index_slice = indices[i_{b0},...,i_{bB},i_{0},..,i_{Q-1}]
 *              res[i_{b0},...,i_{bB},i_{0},...,i_{Q-1}] = updates[i_{b0},...,i_{bB},index_slice[0],...,index_slice[K-1]]
 *              @endcode
 *              The tensors have the following shape requirements
 *              @code
 *              U > 0; P > 0; Q > 0
 *              K <= U
 *              P = (U-K) + Q-1
 *              indices.shape[0:Q-1] = res.shape[0:Q-1]
 *              res.shape[Q:P] = updates.shape[K:U]
 *              @endcode
 *
 *  @param      updatesTensor       Tensor containing slices to be inserted into the result tensor
 *  @param      indicesTensor       Tensor containg the updates indices to read slices from
 *  @param      batchDimensions  The number of batch dimensions
 *  @param      name                           The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
*/
-(MPSGraphTensor *) gatherNDWithUpdatesTensor:(MPSGraphTensor *) updatesTensor
                                indicesTensor:(MPSGraphTensor *) indicesTensor
                              batchDimensions:(NSUInteger) batchDimensions
                                         name:(NSString * _Nullable) name;

@end

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(GatherOps)

/*!
 *  @abstract   Create Gather op and return the result tensor
 *  @discussion Gathers the values in updatesTensor to the result tensor along the indices in indicesTensor.
 *              The gather is defined as
 *              @code
 *              B = batchDims
 *              U = updates.rank
 *              P = res.rank
 *              Q = inds.rank
 *
 *              res[p_{0},...p_{axis-1},                               i_{B},...,i_{Q}, ...,p_{axis+1},...,p{U-1}] =
 *              updates[p_{0},...p_{axis-1}, indices[p_{0},...,p_{B-1},i_{B},...,i_{Q}, ...,p_{axis+1},...,p{U-1}]
 *
 *              @endcode
 *              The tensors have the following shape requirements
 *              @code
 *              P = Q-B + U-1
 *              indices.shape[0:B] = updates.shape[0:B] = res.shape[0:B]
 *              res.shape[0:axis] = updates.shape[0:axis]
 *              res.shape[axis:axis+Q-B] = indices.shape[B:]
 *              res.shape[axis+1+Q-B:] = updates.shape[axis+1:]
 *              @endcode
 *
 *  @param      updatesTensor      Tensor containing slices to be inserted into the result tensor
 *  @param      indicesTensor      Tensor containg the updates indices to read slices from
 *  @param      axis                          The dimension on which to perform the gather
 *  @param      batchDimensions  The number of batch dimensions
 *  @param      name                          The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
*/
-(MPSGraphTensor *) gatherWithUpdatesTensor:(MPSGraphTensor *) updatesTensor
                              indicesTensor:(MPSGraphTensor *) indicesTensor
                                       axis:(NSUInteger) axis
                            batchDimensions:(NSUInteger) batchDimensions
                                       name:(NSString * _Nullable) name;

@end

NS_ASSUME_NONNULL_END

#endif /* MPSGatherOps_h */
