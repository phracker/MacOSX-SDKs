//
//  MPSGraphInverseOps.h
//  MPSGraph
//
//  Created on 8/2/22.
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#ifndef MPSGraphInverseOps_h
#define MPSGraphInverseOps_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

@interface MPSGraph(MPSGraphMatrixInverseOps)

/// Computes the inverse of an input tensor.
///
/// The framework computes the inverse of a square matrix by calling LU decomposition and LU solver.
/// All dimensions after the first 2 are treated as batch dimensions and the inverse for each batch is computed.
/// Results are undefined for ill conditioned matrices.
///
/// - Parameters:
///   - inputTensor: The input tensor.
///   - name: The name for the operation.
/// - Returns: A valid ``MPSGraphTensor`` object containing the inverse of the input tensor.
///
-(MPSGraphTensor *) inverseOfTensor:(MPSGraphTensor *) inputTensor
                               name:(NSString * _Nullable) name
MPS_SWIFT_NAME( inverse(input:name:) )
MPS_CLASS_AVAILABLE_STARTING(macos(13.0), ios(16.1), tvos(16.1));

@end


NS_ASSUME_NONNULL_END


#endif /* MPSGraphInverseOps_h */
