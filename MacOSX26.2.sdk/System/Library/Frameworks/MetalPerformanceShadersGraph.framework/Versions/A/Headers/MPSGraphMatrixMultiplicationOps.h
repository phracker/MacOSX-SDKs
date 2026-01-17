//
//  MPSGraphMatrixMultiplicationOps.h
//  MetalPerformanceShadersGraph
//
//  Created on 12/8/19.
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#ifndef MPSGraphMatrixMultiplicationOps_h
#define MPSGraphMatrixMultiplicationOps_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(MPSGraphMatrixMultiplicationOps)

/// Computes the matrix multiplication of 2 input tensors with support for broadcasting.
///
/// - Parameters:
///   - primaryTensor: The left-hand side tensor.
///   - secondaryTensor: The right-hand side tensor.
///   - name: The name for the operation.
/// - Returns: A valid tensor containing the product of the input matrices.
-(MPSGraphTensor *) matrixMultiplicationWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                                          secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                                     name:(NSString * _Nullable) name
MPS_SWIFT_NAME( matrixMultiplication(primary:secondary:name:) );

/// Computes the hamming distance of two input tensors with support for broadcasting.
///
/// The hamming distance is computed between 2 sets of vectors and the last dimension(s) of each 
/// input tensor is considered a vector.
///
/// - Parameters:
///   - primaryTensor: The first input tensor.
///   - secondaryTensor: The second input tensor.
///   - resultDataType: The datatype of the return MPSGraphTensor. Must be either ``MPSDataTypeUInt32`` or ``MPSDataTypeUInt16``.
///   - name: The name for the operation.
/// - Returns: A valid tensor containing the hamming distance between the input tensors.
-(MPSGraphTensor *) HammingDistanceWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                                     secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                      resultDataType:(MPSDataType) resultDataType
                                                name:(NSString * _Nullable) name
MPS_SWIFT_NAME( HammingDistance(primary:secondary:resultDataType:name:) )
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/// Creates a scaled dot product attention (SDPA) operation and returns the result tensor.
///
/// SDPA Op computes attention by computing softmax(scale * QK^T + M)V.
/// queryTensor Q with shape [B, Hq, Nq, F] and keyTensor K with shape [B, Hq, Nkv, F],
/// with Q's H dimension expandable to satisfy matmul QK^T. maskTensor M's shape
/// should be broadcast compatible to satisfy (QK^T + M). valueTensor V with shape
/// [B, Hv, Nkv, F] should satisfy the matmul (QK^T + M)V.
///
/// - Parameters:
///   - queryTensor: A tensor that represents the query projection.
///   - keyTensor: A tensor that represents the key projection.
///   - valueTensor: A tensor that represents the value projection.
///   - maskTensor: An optional tensor that contains a mask that is applied to the scaled, matrix
///   multiplied query and value matrices. If mask tensor is nil, the QK^T is not element-wise masked.
///   - scale: A scale that is applied to the result of query and value matrix multiply.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
- (MPSGraphTensor *)scaledDotProductAttentionWithQueryTensor:(MPSGraphTensor *)queryTensor
                                                   keyTensor:(MPSGraphTensor *)keyTensor
                                                 valueTensor:(MPSGraphTensor *)valueTensor
                                                  maskTensor:(MPSGraphTensor *_Nullable)maskTensor
                                                       scale:(float)scale
                                                        name:(NSString *_Nullable)name
    MPS_SWIFT_NAME(scaledDotProductAttention(query:key:value:mask:scale:name:) )
MPS_AVAILABLE_STARTING(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0));

/// Creates a scaled dot product attention (SDPA) operation (without a mask) and returns the result tensor.
///
/// - Parameters:
///   - queryTensor: A tensor that represents the query projection.
///   - keyTensor: A tensor that represents the key projection.
///   - valueTensor: A tensor that represents the value projection.
///   - scale: A scale that is applied on the result of query and value matrix multiply.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
- (MPSGraphTensor *)scaledDotProductAttentionWithQueryTensor:(MPSGraphTensor *)queryTensor
                                                   keyTensor:(MPSGraphTensor *)keyTensor
                                                 valueTensor:(MPSGraphTensor *)valueTensor
                                                       scale:(float)scale
                                                        name:(NSString *_Nullable)name
    MPS_SWIFT_NAME(scaledDotProductAttention(query:key:value:scale:name:) )
MPS_AVAILABLE_STARTING(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0));
@end


NS_ASSUME_NONNULL_END

#endif /* MPSGraphMatrixMultiplicationOps_h */
