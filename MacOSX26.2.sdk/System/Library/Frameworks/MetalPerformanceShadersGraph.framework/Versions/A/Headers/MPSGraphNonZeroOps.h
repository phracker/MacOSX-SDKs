//
//  MPSGraphNonZeroOps.h
//  MPSGraph
//
//  Created on 2/27/23.
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#ifndef MPSGraphNonZeroOps_h
#define MPSGraphNonZeroOps_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(NonZeroOps)

/// Computes the indices of the non-zero elements of the input tensor. 
///
/// The indices are returned as a two-dimensional tensor of size `[number_of_nonzeros, input_rank]`.
/// Each row in the result contains indices of a nonzero elements in input.
/// For example:
/// ```md
/// tensor = [[ 1,  0, 3],
///           [ 0, 10, 0]]
/// indices = [[ 0, 0],
///            [ 0, 2],
///            [ 1, 1]]
/// ```
///
/// - Parameters:
///   - tensor: An MPSGraphTensor of which to compute the non-zero indices.
/// - Returns: A valid MPSGraphTensor containing indices in signed int32 data type.
-(MPSGraphTensor *) nonZeroIndicesOfTensor:(MPSGraphTensor *) tensor
                                      name:(NSString * _Nullable) name
MPS_SWIFT_NAME( nonZeroIndices(_:name:))
MPS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0));

@end

NS_ASSUME_NONNULL_END

#endif /* MPSGraphNonZeroOps_h */
