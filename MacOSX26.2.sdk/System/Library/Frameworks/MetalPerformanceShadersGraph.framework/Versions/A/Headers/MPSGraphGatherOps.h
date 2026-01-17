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
/// Creates a GatherND operation and returns the result tensor.
///
/// Gathers the slices in updatesTensor to the result tensor along the indices in indicesTensor. 
/// The gather is defined as 
/// ```md 
/// B = batchDims 
/// U = updates.rank - B 
/// P = res.rank - B 
/// Q = inds.rank - B 
/// K = inds.shape[-1] 
/// index_slice = indices[i_{b0},...,i_{bB},i_{0},..,i_{Q-1}] 
/// res[i_{b0},...,i_{bB},i_{0},...,i_{Q-1}] = updates[i_{b0},...,i_{bB},index_slice[0],...,index_slice[K-1]] 
/// ``` 
/// The tensors have the following shape requirements 
/// ```md 
/// U > 0; P > 0; Q > 0 
/// K <= U 
/// P = (U-K) + Q-1 
/// indices.shape[0:Q-1] = res.shape[0:Q-1] 
/// res.shape[Q:P] = updates.shape[K:U] 
/// ```
///
/// - Parameters:
///   - updatesTensor: Tensor containing slices to be inserted into the result tensor.
///   - indicesTensor: Tensor containg the updates indices to read slices from
///   - batchDimensions: The number of batch dimensions
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object 
///
- (MPSGraphTensor *) gatherNDWithUpdatesTensor:(MPSGraphTensor *) updatesTensor
                                 indicesTensor:(MPSGraphTensor *) indicesTensor
                               batchDimensions:(NSUInteger) batchDimensions
                                          name:(NSString * _Nullable) name;

@end

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(GatherOps)

/// Creates a Gather operation and returns the result tensor.
///
/// Gathers the values in updatesTensor to the result tensor along the indices in indicesTensor. 
/// The gather is defined as 
/// ```md 
/// B = batchDims 
/// U = updates.rank 
/// P = res.rank 
/// Q = inds.rank 
/// res[p_{0},...p_{axis-1}, i_{B},...,i_{Q}, ...,p_{axis+1},...,p{U-1}] = 
/// updates[p_{0},...p_{axis-1}, indices[p_{0},...,p_{B-1},i_{B},...,i_{Q}, ...,p_{axis+1},...,p{U-1}] 
/// ``` 
/// The tensors have the following shape requirements 
/// ```md 
/// P = Q-B + U-1 
/// indices.shape[0:B] = updates.shape[0:B] = res.shape[0:B] 
/// res.shape[0:axis] = updates.shape[0:axis] 
/// res.shape[axis:axis+Q-B] = indices.shape[B:] 
/// res.shape[axis+1+Q-B:] = updates.shape[axis+1:] 
/// ```
///
/// - Parameters:
///   - updatesTensor: Tensor containing slices to be inserted into the result tensor.
///   - indicesTensor: Tensor containg the updates indices to read slices from
///   - axis: The dimension on which to perform the gather
///   - batchDimensions: The number of batch dimensions
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object 
///
- (MPSGraphTensor *) gatherWithUpdatesTensor:(MPSGraphTensor *) updatesTensor
                               indicesTensor:(MPSGraphTensor *) indicesTensor
                                        axis:(NSUInteger) axis
                             batchDimensions:(NSUInteger) batchDimensions
                                        name:(NSString * _Nullable) name;

@end

@interface MPSGraph(MPSGraphGatherAlongAxisOps)

/// Creates a GatherAlongAxis operation and returns the result tensor.
///
/// Gather values from `updatesTensor` along the specified `axis` at indices in `indicesTensor`. 
/// The shape of `updatesTensor` and `indicesTensor` must match except at `axis`. 
/// The shape of the result tensor is equal to the shape of `indicesTensor`. 
/// If an index is out of bounds of the `updatesTensor` along `axis` a 0 is inserted.
///
/// - Parameters:
///   - axis: The axis to gather from. Negative values wrap around
///   - updatesTensor: The input tensor to gather values from
///   - indicesTensor: Int32 or Int64 tensor used to index `updatesTensor`
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object 
///

- (MPSGraphTensor *) gatherAlongAxis:(NSInteger) axis
                   withUpdatesTensor:(MPSGraphTensor *) updatesTensor
                       indicesTensor:(MPSGraphTensor *) indicesTensor
                                name:(NSString * _Nullable) name
MPS_SWIFT_NAME( gatherAlongAxis(_:updates:indices:name:) )
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

/// Creates a GatherAlongAxis operation and returns the result tensor.
///
/// Gather values from `updatesTensor` along the specified `axis` at indices in `indicesTensor`.
/// The shape of `updatesTensor` and `indicesTensor` must match except at `axis`.
/// The shape of the result tensor is equal to the shape of `indicesTensor`.
/// If an index is out of bounds of the `updatesTensor` along `axis` a 0 is inserted.
/// 
/// - Parameters:
///   - axisTensor: Scalar Int32 tensor. The axis to gather from. Negative values wrap around
///   - updatesTensor: The input tensor to gather values from
///   - indicesTensor: Int32 or Int64 tensor used to index `updatesTensor`
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object 
///
- (MPSGraphTensor *) gatherAlongAxisTensor:(MPSGraphTensor *) axisTensor
                         withUpdatesTensor:(MPSGraphTensor *) updatesTensor
                             indicesTensor:(MPSGraphTensor *) indicesTensor
                                      name:(NSString * _Nullable) name
MPS_SWIFT_NAME( gatherAlongAxisTensor(_:updates:indices:name:) )
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

@end

NS_ASSUME_NONNULL_END

#endif /* MPSGatherOps_h */
