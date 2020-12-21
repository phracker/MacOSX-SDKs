//
//  MPSScatterNDOps.h
//  MPSGraph
//
//  Created on 3/6/20.
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#ifndef MPSScatterNDOps_h
#define MPSScatterNDOps_h

NS_ASSUME_NONNULL_BEGIN

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(ScatterNDOps)

/*!
 *  @abstract   Create ScatterND op and return the result tensor
 *  @discussion Scatters the slices in updatesTensor to the result tensor along the indices in indicesTensor.
 *              The scatter is defined as
 *              @code
 *              B = batchDims
 *              U = updates.rank - B
 *              P = res.rank - B
 *              Q = inds.rank - B
 *              K = inds.shape[-1]
 *              index_slice = indices[i_{b0},...,i_{bB},i_{0},..,i_{Q-1}]
 *              res[i_{b0},...,i_{bB},index_slice[0],...,index_slice[K-1]] = updates[i_{b0},...,i_{bB},i_{0},...,i_{Q-1}]
 *              @endcode
 *              Collsions will be summed, and slices not set by indices are set to 0. The tensors have the following shape requirements
 *              @code
 *              K <= P
 *              U = (P-K) + Q-1
 *              indices.shape[0:Q-1] = updates.shape[0:Q-1]
 *              updates.shape[Q:U] = res.shape[K:P]
 *              @endcode
 *
 *  @param      updatesTensor      Tensor containing slices to be inserted into the result tensor
 *  @param      indicesTensor      Tensor containg the result indices to insert slices at
 *  @param      shape                        The shape of the result tensor
 *  @param      batchDimensions  The number of batch dimensions
 *  @param      name                           The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) scatterNDWithUpdatesTensor:(MPSGraphTensor *) updatesTensor
                                 indicesTensor:(MPSGraphTensor *) indicesTensor
                                         shape:(MPSShape *) shape
                               batchDimensions:(NSUInteger) batchDimensions
                                          name:(NSString * _Nullable) name;

@end

NS_ASSUME_NONNULL_END

#endif /* MPSScatterNDOps_h */
