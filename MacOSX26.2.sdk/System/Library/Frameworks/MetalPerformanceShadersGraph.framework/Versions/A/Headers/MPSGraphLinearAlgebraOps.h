//
//  MPSGraphLinearAlgebraOps.h
//  MPSGraph
//
//  Created on 1/21/22.
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#ifndef MPSGraphLinearAlgebraOps_h
#define MPSGraphLinearAlgebraOps_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN


MPS_CLASS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4))
@interface MPSGraph(MPSGraphLinearAlgebraOps)

/// Computes the band part of an input tensor.
///
/// This operation copies a diagonal band of values from input tensor to a result tensor of the same size.
/// A coordinate `[..., i, j]` is in the band if 
/// ```md 
/// (numLower < 0 || (i-j) <= numLower) && (numUpper < 0 || (j-i) <= numUpper) 
/// ``` 
/// The values outside of the band are set to 0.
///
/// - Parameters:
///   - inputTensor: input tensor
///   - numLower: the number of diagonals in the lower triangle to keep. If -1, the framework returns all sub diagnols.
///   - numUpper: the number of diagonals in the upper triangle to keep. If -1,  the framework returns all super diagnols.
///   - name: name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) bandPartWithTensor:(MPSGraphTensor *) inputTensor
                              numLower:(NSInteger) numLower
                              numUpper:(NSInteger) numUpper
                                  name:(NSString * _Nullable) name
MPS_SWIFT_NAME( bandPart(_:numLower:numUpper:name:) );

/// Creates the band part operation and returns the result.
///
/// See above discussion of bandPartWithTensor: numLower: numUpper: name:
///
/// - Parameters:
///   - inputTensor: The source tensor to copy.
///   - numLowerTensor: Scalar Int32 tensor. The number of diagonals in the lower triangle to keep. If -1, keep all.
///   - numUpperTensor: Scalar Int32 tensor. The number of diagonals in the upper triangle to keep. If -1, keep all.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) bandPartWithTensor:(MPSGraphTensor *) inputTensor
                        numLowerTensor:(MPSGraphTensor *) numLowerTensor
                        numUpperTensor:(MPSGraphTensor *) numUpperTensor
                                  name:(NSString * _Nullable) name
MPS_SWIFT_NAME( bandPart(_:numLowerTensor:numUpperTensor:name:) );

@end

NS_ASSUME_NONNULL_END


#endif /* MPSGraphLinearAlgebraOps_h */
