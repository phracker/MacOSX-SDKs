//
//  MPSGraphTensorShapeOps.h
//  MetalPerformanceShadersGraph
//
//  Created on 12/16/19.
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#ifndef MPSGraphTensorShapeOps_h
#define MPSGraphTensorShapeOps_h


#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(MPSGraphTensorShapeOps)

/// Creates a reshape operation and returns the result tensor.
///
/// This operation reshapes the input tensor to the target shape.
/// The shape must be compatible with the input tensor shape, specifically the volume of the input tensor has to match the volume defined by the shape.
/// The shape is allowed to contain dynamic dimensions (-1) when the result type can be inferred unambiguously.
///
/// - Parameters:
///   - tensor: The tensor to be reshaped.
///   - shape: The result tensor shape.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) reshapeTensor:(MPSGraphTensor *) tensor
                        withShape:(MPSShape *) shape
                             name:(NSString * _Nullable) name
MPS_SWIFT_NAME( reshape(_:shape:name:) );

/// Creates a reshape operation and returns the result tensor.
///
/// This operation reshapes the input tensor to the target shape.
/// The shape tensor must be compatible with the input tensor shape, specifically the volume of the input tensor has to match the volume defined by the shape tensor.
/// The shape tensor is allowed to contain dynamic dimensions (-1) when the result type can be inferred unambiguously.
///
/// - Parameters:
///   - tensor: The tensor to be reshaped.
///   - shapeTensor: A 1D tensor of type `MPSDataTypeInt32` or `MPSDataTypeInt64`, that contains the target shape values.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) reshapeTensor:(MPSGraphTensor *) tensor
                  withShapeTensor:(MPSGraphTensor *) shapeTensor
                             name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
MPS_SWIFT_NAME( reshape(_:shapeTensor:name:) );

/// Creates a transpose operation and returns the result tensor.
///
/// Transposes the dimensions `dimensionIndex` and `dimensionIndex2` of the input tensor.
///
/// - Parameters:
///   - tensor: The tensor to be transposed.
///   - dimensionIndex: The first dimension index to be transposed.
///   - dimensionIndex2: The second dimension index to be transposed.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) transposeTensor:(MPSGraphTensor *) tensor
                          dimension:(NSUInteger) dimensionIndex
                      withDimension:(NSUInteger) dimensionIndex2
                               name:(NSString * _Nullable) name;

/// Creates a permutation operation and returns the result tensor.
///
/// Permutes the dimensions of the input tensor according to values in `permutation`.
///
/// - Parameters:
///   - tensor: The tensor to be permuted.
///   - permutation: An array of numbers defining the permutation, must be of length `rank(tensor)` and define a valid permutation.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) transposeTensor:(MPSGraphTensor *) tensor
                        permutation:(NSArray<NSNumber *> *) permutation
                               name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0))
MPS_SWIFT_NAME( transpose(_:permutation:name:) );

/// Creates a slice operation and returns the result tensor.
///
/// - Parameters:
///   - tensor: The tensor to be sliced.
///   - dimensionIndex: The dimension to slice.
///   - start: The starting index of the slice, can be negative to count from the end of the tensor dimension.
///   - length: The length of the slice.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) sliceTensor:(MPSGraphTensor *) tensor
                      dimension:(NSUInteger) dimensionIndex
                          start:(NSInteger) start
                         length:(NSInteger) length
                           name:(NSString * _Nullable) name;

/// Creates a strided-slice operation and returns the result tensor.
///
/// Slices a tensor starting from `starts`, stopping short before `ends` stepping
/// `strides` paces between each value. Semantics based on
/// [TensorFlow Strided Slice Op](https://www.tensorflow.org/api_docs/python/tf/strided_slice).
///
/// - Parameters:
///   - tensor: The tensor to be sliced.
///   - starts: An array of numbers that specify the starting points for each dimension.
///   - ends: An array of numbers that specify the ending points for each dimension.
///   - strides: An array of numbers that specify the strides for each dimension.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) sliceTensor:(MPSGraphTensor *) tensor
                         starts:(NSArray<NSNumber *> *) starts
                           ends:(NSArray<NSNumber *> *) ends
                        strides:(NSArray<NSNumber *> *) strides
                           name:(NSString * _Nullable) name;

/// Creates a strided-slice operation and returns the result tensor.
///
/// Slices a tensor starting from `starts`, stopping short before `ends` stepping
/// `strides` paces between each value. Semantics based on
/// [TensorFlow Strided Slice Op](https://www.tensorflow.org/api_docs/python/tf/strided_slice).
///
/// - Parameters:
///   - tensor: The Tensor to be sliced.
///   - starts: An array of numbers that specify the starting points for each dimension.
///   - ends: An array of numbers that specify the ending points for each dimension.
///   - strides: An array of numbers that specify the strides for each dimension.
///   - startMask: A bitmask that indicates dimensions whose `starts` values the operation should ignore.
///   - endMask: A bitmask that indicates dimensions whose `ends` values the operation should ignore.
///   - squeezeMask: A bitmask that indicates dimensions the operation will squeeze out from the result.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) sliceTensor:(MPSGraphTensor *) tensor
                         starts:(NSArray<NSNumber *> *) starts
                           ends:(NSArray<NSNumber *> *) ends
                        strides:(NSArray<NSNumber *> *) strides
                      startMask:(uint32_t) startMask
                        endMask:(uint32_t) endMask
                    squeezeMask:(uint32_t) squeezeMask
                           name:(NSString * _Nullable) name;

/// Creates a strided-slice operation and returns the result tensor.
///
/// Slices a tensor starting from `startTensor`, stopping short before `endTensor` stepping
/// `strideTensor` paces between each value. Semantics based on
/// [TensorFlow Strided Slice Op](https://www.tensorflow.org/api_docs/python/tf/strided_slice).
///
/// - Parameters:
///   - tensor: The Tensor to be sliced.
///   - startTensor: The tensor that specifies the starting points for each dimension.
///   - endTensor: The tensor that specifies the ending points for each dimension.
///   - strideTensor: The tensor that specifies the strides for each dimension.
///   - startMask: A bitmask that indicates dimensions whose `starts` values the operation should ignore.
///   - endMask: A bitmask that indicates dimensions whose `ends` values the operation should ignore.
///   - squeezeMask: A bitmask that indicates dimensions the operation will squeeze out from the result.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) sliceTensor:(MPSGraphTensor *) tensor
                    startTensor:(MPSGraphTensor *) startTensor
                      endTensor:(MPSGraphTensor *) endTensor
                   strideTensor:(MPSGraphTensor *) strideTensor
                      startMask:(uint32_t) startMask
                        endMask:(uint32_t) endMask
                    squeezeMask:(uint32_t) squeezeMask
                           name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(15.2), ios(18.2), macCatalyst(18.2), tvos(18.2));

/// Creates a slice operation and returns the result tensor.
///
/// Slices a tensor starting from `startTensor`, stopping short before `startTensor + endTensor` stepping
/// a single pace between each value. Semantics based on
/// [TensorFlow Strided Slice Op](https://www.tensorflow.org/api_docs/python/tf/strided_slice).
///
/// - Parameters:
///   - tensor: The Tensor to be sliced.
///   - startTensor: The tensor that specifies the starting points for each dimension.
///   - sizeTensor: The tensor that specifies the size of the result for each dimension.
///   - squeezeMask: A bitmask that indicates dimensions the operation will squeeze out from the result.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) sliceTensor:(MPSGraphTensor *) tensor
                    startTensor:(MPSGraphTensor *) startTensor
                     sizeTensor:(MPSGraphTensor *) sizeTensor
                    squeezeMask:(uint32_t) squeezeMask
                           name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(15.2), ios(18.2), macCatalyst(18.2), tvos(18.2));

/// Creates a strided-slice gradient operation and returns the result tensor.
///
/// - Parameters:
///   - inputGradientTensor: The input gradient.
///   - fwdInShapeTensor: The shape of the forward pass input, that is the shape of the gradient output.
///   - starts: An array of numbers that specify the starting points for each dimension.
///   - ends: An array of numbers that specify the ending points for each dimension.
///   - strides: An array of numbers that specify the strides for each dimension.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) sliceGradientTensor:(MPSGraphTensor *) inputGradientTensor
                       fwdInShapeTensor:(MPSGraphTensor *) fwdInShapeTensor
                                 starts:(NSArray<NSNumber *> *) starts
                                   ends:(NSArray<NSNumber *> *) ends
                                strides:(NSArray<NSNumber *> *) strides
                                   name:(NSString * _Nullable) name;

/// Creates a strided-slice gradient operation and returns the result tensor.
///
/// - Parameters:
///   - inputGradientTensor: The input gradient.
///   - fwdInShapeTensor: The shape of the forward pass input, that is the shape of the gradient output.
///   - startTensor: The tensor that specifies the starting points for each dimension.
///   - endTensor: The tensor that specifies the ending points for each dimension.
///   - strideTensor: The tensor that specifies the strides for each dimension.
///   - startMask: A bitmask that indicates dimensions whose `starts` values the operation should ignore.
///   - endMask: A bitmask that indicates dimensions whose `ends` values the operation should ignore.
///   - squeezeMask: A bitmask that indicates dimensions the operation will squeeze out from the result.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) sliceGradientTensor:(MPSGraphTensor *) inputGradientTensor
                       fwdInShapeTensor:(MPSGraphTensor *) fwdInShapeTensor
                            startTensor:(MPSGraphTensor *) startTensor
                              endTensor:(MPSGraphTensor *) endTensor
                           strideTensor:(MPSGraphTensor *) strideTensor
                              startMask:(uint32_t) startMask
                                endMask:(uint32_t) endMask
                            squeezeMask:(uint32_t) squeezeMask
                                   name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(15.2), ios(18.2), macCatalyst(18.2), tvos(18.2));

/// Creates a slice gradient operation and returns the result tensor.
///
/// - Parameters:
///   - inputGradientTensor: The input gradient.
///   - fwdInShapeTensor: The shape of the forward pass input, that is the shape of the gradient output.
///   - startTensor: The tensor that specifies the starting points for each dimension.
///   - sizeTensor: The tensor that specifies the size of the forward result for each dimension.
///   - squeezeMask: A bitmask that indicates dimensions the operation will squeeze out from the result.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) sliceGradientTensor:(MPSGraphTensor *) inputGradientTensor
                       fwdInShapeTensor:(MPSGraphTensor *) fwdInShapeTensor
                            startTensor:(MPSGraphTensor *) startTensor
                             sizeTensor:(MPSGraphTensor *) sizeTensor
                            squeezeMask:(uint32_t) squeezeMask
                                   name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(15.2), ios(18.2), macCatalyst(18.2), tvos(18.2));

/// Creates a strided-slice gradient operation and returns the result tensor.
///
/// - Parameters:
///   - inputGradientTensor: The input gradient.
///   - fwdInShapeTensor: The shape of the forward pass input, that is the shape of the gradient output.
///   - starts: An array of numbers that specify the starting points for each dimension.
///   - ends: An array of numbers that specify the ending points for each dimension.
///   - strides: An array of numbers that specify the strides for each dimension.
///   - startMask: A bitmask that indicates dimensions whose `starts` values the operation should ignore.
///   - endMask: A bitmask that indicates dimensions whose `ends` values the operation should ignore.
///   - squeezeMask: A bitmask that indicates dimensions the operation will squeeze out from the result.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) sliceGradientTensor:(MPSGraphTensor *) inputGradientTensor
                       fwdInShapeTensor:(MPSGraphTensor *) fwdInShapeTensor
                                 starts:(NSArray<NSNumber *> *) starts
                                   ends:(NSArray<NSNumber *> *) ends
                                strides:(NSArray<NSNumber *> *) strides
                              startMask:(uint32_t) startMask
                                endMask:(uint32_t) endMask
                            squeezeMask:(uint32_t) squeezeMask
                                   name:(NSString * _Nullable) name;

/// Creates a strided-slice update operation and returns the result tensor.
///
/// - Parameters:
///   - dataTensor: The large tensor that will receive the update.
///   - updateTensor: The tensor with the new values that will replace values in the dataTensor.
///   - startsTensor: A Tensor that contains an array of numbers that specify the starting points for each dimension.
///   - endsTensor: A Tensor that contains an array of numbers that specify the ending points for each dimension.
///   - stridesTensor: A Tensor that contains an array of numbers that specify the strides for each dimension.
///   - startMask: A bitmask that indicates dimensions whose `starts` values the operation should ignore.
///   - endMask: A bitmask that indicates dimensions whose `ends` values the operation should ignore.
///   - squeezeMask: A bitmask that indicates dimensions the operation will squeeze out from the result.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) sliceUpdateDataTensor:(MPSGraphTensor *) dataTensor
                             updateTensor:(MPSGraphTensor *) updateTensor
                             startsTensor:(MPSGraphTensor *) startsTensor
                               endsTensor:(MPSGraphTensor *) endsTensor
                            stridesTensor:(MPSGraphTensor *) stridesTensor
                                startMask:(uint32_t) startMask
                                  endMask:(uint32_t) endMask
                              squeezeMask:(uint32_t) squeezeMask
                                     name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(14.4), ios(17.4), tvos(17.4));

/// Creates a strided-slice update operation and returns the result tensor.
///
/// - Parameters:
///   - dataTensor: The large tensor that will receive the update.
///   - updateTensor: The tensor with the new values that will replace values in the dataTensor.
///   - starts: An array of numbers that specify the starting points for each dimension.
///   - ends: An array of numbers that specify the ending points for each dimension.
///   - strides: An array of numbers that specify the strides for each dimension.
///   - startMask: A bitmask that indicates dimensions whose `starts` values the operation should ignore.
///   - endMask: A bitmask that indicates dimensions whose `ends` values the operation should ignore.
///   - squeezeMask: A bitmask that indicates dimensions the operation will squeeze out from the result.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) sliceUpdateDataTensor:(MPSGraphTensor *) dataTensor
                             updateTensor:(MPSGraphTensor *) updateTensor
                                   starts:(NSArray<NSNumber *> *) starts
                                     ends:(NSArray<NSNumber *> *) ends
                                  strides:(NSArray<NSNumber *> *) strides
                                startMask:(uint32_t) startMask
                                  endMask:(uint32_t) endMask
                              squeezeMask:(uint32_t) squeezeMask
                                     name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(14.4), ios(17.4), tvos(17.4));

/// Creates a strided-slice update operation with zero masks and returns the result tensor.
///
/// - Parameters:
///   - dataTensor: The large tensor that will receive the update.
///   - updateTensor: The tensor with the new values that will replace values in the dataTensor.
///   - startsTensor: A Tensor that contains an array of numbers that specify the starting points for each dimension.
///   - endsTensor: A Tensor that contains an array of numbers that specify the ending points for each dimension.
///   - stridesTensor: A Tensor that contains an array of numbers that specify the strides for each dimension.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) sliceUpdateDataTensor:(MPSGraphTensor *) dataTensor
                             updateTensor:(MPSGraphTensor *) updateTensor
                             startsTensor:(MPSGraphTensor *) startsTensor
                               endsTensor:(MPSGraphTensor *) endsTensor
                            stridesTensor:(MPSGraphTensor *) stridesTensor
                                     name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0));

/// Creates a strided-slice update operation with zero masks and returns the result tensor.
///
/// - Parameters:
///   - dataTensor: The large tensor that will receive the update.
///   - updateTensor: The tensor with the new values that will replace values in the dataTensor.
///   - starts: An array of numbers that specify the starting points for each dimension.
///   - ends: An array of numbers that specify the ending points for each dimension.
///   - strides: An array of numbers that specify the strides for each dimension.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) sliceUpdateDataTensor:(MPSGraphTensor *) dataTensor
                             updateTensor:(MPSGraphTensor *) updateTensor
                                   starts:(NSArray<NSNumber *> *) starts
                                     ends:(NSArray<NSNumber *> *) ends
                                  strides:(NSArray<NSNumber *> *) strides
                                     name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0));


/// Creates a concatenation operation and returns the result tensor.
///
/// Concatenates two input tensors along the specified dimension. Tensors must be broadcast
/// compatible along all other dimensions, and have the same datatype.
///
/// - Parameters:
///   - tensor: The first tensor to concatenate.
///   - tensor2: The second tensor to concatenate.
///   - dimensionIndex: The dimension to concatenate across, must be in range: `-rank <= dimension < rank`.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) concatTensor:(MPSGraphTensor *) tensor
                      withTensor:(MPSGraphTensor *) tensor2
                       dimension:(NSInteger) dimensionIndex
                            name:(NSString * _Nullable) name;

/// Creates a concatenation operation and returns the result tensor.
///
/// Concatenates all input tensors along the specified dimension. All inputs must be broadcast
/// compatible along all other dimensions, and have the same datatype.
///
/// - Parameters:
///   - tensors: The tensors to concatenate.
///   - dimensionIndex: The dimension to concatenate across, must be in range: `-rank <= dimension < rank`.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) concatTensors:(NSArray<MPSGraphTensor *> *) tensors
                        dimension:(NSInteger) dimensionIndex
                             name:(NSString * _Nullable) name;

/// Creates a concatenation operation and returns the result tensor.
///
/// Concatenates all input tensors along specified dimension. All inputs must be broadcast
/// compatible along all other dimensions, and have the same type. 
/// When interleave is specified, all tensors will be interleaved. To interleave, make sure to provide broadcast
/// compatible inputs along the specified dimension as well.
/// For example:
/// ```md 
///   operand0 = [1, 2, 3]
///   operand1 = [4, 5, 6]
///   concat([operand0, operand1], axis = 0, interleave = YES) = [1, 4, 2, 5, 3, 6]
/// ```
///
/// - Parameters:
///   - tensors: The tensors to concatenate.
///   - dimensionIndex: The dimension to concatenate across, must be in range: `-rank <= dimension < rank`.
///   - interleave: A boolean value that specifies whether the operation interleaves input tensors.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) concatTensors:(NSArray<MPSGraphTensor *> *) tensors
                        dimension:(NSInteger) dimensionIndex
                       interleave:(BOOL) interleave
                             name:(NSString * _Nullable) name;

/// Creates a tile operation and returns the result tensor.
///
/// Creates a tensor which contains multiple copies of the input tensor along each dimension of the tensor.
///
/// - Parameters:
///   - tensor: The input tensor
///   - multiplier: An array of numbers that specifies how many copies per dimension MPSGraph produces.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) tileTensor:(MPSGraphTensor *) tensor
                withMultiplier:(MPSShape *) multiplier
                          name:(NSString * _Nullable) name;

/// Creates a tile gradient operation and returns the result tensor.
///
/// - Parameters:
///   - incomingGradientTensor: The input gradient tensor.
///   - sourceTensor: The input tensor of the forward pass.
///   - multiplier: An array of numbers that specifies how many copies per dimension MPSGraph produced in the forward pass.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) tileGradientWithIncomingGradientTensor:(MPSGraphTensor *) incomingGradientTensor
                                              sourceTensor:(MPSGraphTensor *) sourceTensor
                                            withMultiplier:(MPSShape *) multiplier
                                                      name:(NSString * _Nullable) name;

/// Creates a padding operation and returns the result tensor.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - paddingMode: The parameter that defines the padding mode.
///   - leftPadding: The parameter that defines how much padding the operation applies to the input tensor before each dimension - must be of size `rank(tensor)`.
///   - rightPadding: The parameter that defines how much padding the operation applies to the input tensor after each dimension - must be of size `rank(tensor)`.
///   - constantValue: The constant value the operation uses when `paddingMode = MPSGraphPaddingModeConstant`.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *)padTensor:(MPSGraphTensor *) tensor
             withPaddingMode:(MPSGraphPaddingMode)paddingMode
                 leftPadding:(MPSShape *) leftPadding
                rightPadding:(MPSShape *) rightPadding
               constantValue:(double)constantValue
                        name:(NSString * _Nullable) name;

/// Creates a padding gradient operation and returns the result tensor.
///
/// - Parameters:
///   - incomingGradientTensor: The input gradient tensor.
///   - sourceTensor: The input tensor of the forward pass.
///   - paddingMode: The parameter that defines the padding mode.
///   - leftPadding: The parameter that defines how much padding the operation applies to the input tensor before each dimension - must be of size `rank(tensor)`.
///   - rightPadding: The parameter that defines how much padding the operation applies to the input tensor after each dimension - must be of size `rank(tensor)`.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *)padGradientWithIncomingGradientTensor:(MPSGraphTensor *) incomingGradientTensor
                                            sourceTensor:(MPSGraphTensor *) sourceTensor
                                             paddingMode:(MPSGraphPaddingMode)paddingMode
                                             leftPadding:(MPSShape *) leftPadding
                                            rightPadding:(MPSShape *) rightPadding
                                                    name:(NSString * _Nullable) name;

/// Creates a space-to-depth2D operation and returns the result tensor.
///
/// This operation outputs a copy of the `input` tensor, where values from the
/// `widthAxis` and `heightAxis` dimensions are moved in spatial blocks of size
/// `blockSize` to the `depthAxis` dimension. Use the `usePixelShuffleOrder` parameter
/// to control how the data within spatial blocks is ordered in the
/// `depthAxis` dimension: with `usePixelShuffleOrder=YES` MPSGraph stores the
/// values of the spatial blocks  contiguosly within the `depthAxis` dimension, whereas
/// otherwise they are stored interleaved with existing values in the `depthAxis` dimension.
/// This operation is the inverse of `MPSGraph/depthToSpace2DTensor:widthAxis:heightAxis:depthAxis:blockSize:usePixelShuffleOrder:name:`.
/// - Parameters:
///   - tensor: The input tensor.
///   - widthAxis: The axis that defines the fastest running dimension within the block.
///   - heightAxis: The axis that defines the 2nd fastest running dimension within the block.
///   - depthAxis: The axis that defines the destination dimension, where to copy the blocks.
///   - blockSize: The size of the square spatial sub-block.
///   - usePixelShuffleOrder: A parameter that controls the layout of the sub-blocks within the depth dimension.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *)spaceToDepth2DTensor:(MPSGraphTensor *) tensor
                              widthAxis:(NSUInteger) widthAxis
                             heightAxis:(NSUInteger) heightAxis
                              depthAxis:(NSUInteger) depthAxis
                              blockSize:(NSUInteger) blockSize
                   usePixelShuffleOrder:(BOOL)usePixelShuffleOrder
                                   name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/// Creates a space-to-depth2D operation and returns the result tensor.
///
/// This operation outputs a copy of the `input` tensor, where values from the
/// `widthAxisTensor` and `heightAxisTensor` dimensions are moved in spatial blocks of size
/// `blockSize` to the `depthAxisTensor` dimension. Use the `usePixelShuffleOrder` parameter
/// to control how the data within spatial blocks is ordered in the
/// `depthAxisTensor` dimension: with `usePixelShuffleOrder=YES` MPSGraph stores the
/// values of the spatial blocks  contiguosly within the `depthAxisTensor` dimension, whereas
/// otherwise they are stored interleaved with existing values in the `depthAxisTensor` dimension.
/// This operation is the inverse of ``MPSGraph/depthToSpace2DTensor:widthAxisTensor:heightAxisTensor:depthAxisTensor:blockSize:usePixelShuffleOrder:name:``.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - widthAxisTensor: A scalar tensor that contains the axis that defines the fastest running dimension within the block.
///   - heightAxisTensor: A scalar tensor that contains the axis that defines the 2nd fastest running dimension within the block.
///   - depthAxisTensor: A scalar tensor that contains the axis that defines the destination dimension, where to copy the blocks.
///   - blockSize: The size of the square spatial sub-block.
///   - usePixelShuffleOrder: A parameter that controls the layout of the sub-blocks within the depth dimension.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *)spaceToDepth2DTensor:(MPSGraphTensor *) tensor
                        widthAxisTensor:(MPSGraphTensor *) widthAxisTensor
                       heightAxisTensor:(MPSGraphTensor *) heightAxisTensor
                        depthAxisTensor:(MPSGraphTensor *) depthAxisTensor
                              blockSize:(NSUInteger)blockSize
                   usePixelShuffleOrder:(BOOL)usePixelShuffleOrder
                                   name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/// Creates a depth-to-space2D operation and returns the result tensor.
///
/// This operation outputs a copy of the input tensor, where values from the 
/// `depthAxis` dimension are moved in spatial blocks of size `blockSize` to the
/// `heightAxis` and `widthAxis` dimensions.  Use the `usePixelShuffleOrder` parameter
/// to control how the data within spatial blocks is ordered in the
/// `depthAxis` dimension: with `usePixelShuffleOrder = YES` MPSGraph stores the values
/// of the spatial block contiguosly within the `depthAxis` dimension, whereas
/// without it they are stored interleaved with existing values in the `depthAxisTensor` dimension.
/// This operation is the inverse of
/// ``MPSGraph/spaceToDepth2DTensor:widthAxis:heightAxis:depthAxis:blockSize:usePixelShuffleOrder:name:``.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - widthAxis: The axis that defines the fastest running dimension within the block.
///   - heightAxis: The axis that defines the 2nd fastest running dimension within the block.
///   - depthAxis: The axis that defines the destination dimension, where to copy the blocks.
///   - blockSize: The size of the square spatial sub-block.
///   - usePixelShuffleOrder: A parameter that controls the layout of the sub-blocks within the depth dimension.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *)depthToSpace2DTensor:(MPSGraphTensor *) tensor
                              widthAxis:(NSUInteger) widthAxis
                             heightAxis:(NSUInteger) heightAxis
                              depthAxis:(NSUInteger) depthAxis
                              blockSize:(NSUInteger)blockSize
                   usePixelShuffleOrder:(BOOL)usePixelShuffleOrder
                                   name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/// Creates a depth-to-space2D operation and returns the result tensor.
///
/// This operation outputs a copy of the input tensor, where values from the
/// `depthAxisTensor` dimension are moved in spatial blocks of size `blockSize` to the
/// `heightAxisTensor` and `widthAxisTensor` dimensions.  Use the `usePixelShuffleOrder` parameter
/// to control how the data within spatial blocks is ordered in the
/// `depthAxisTensor` dimension: with `usePixelShuffleOrder = YES` MPSGraph stores the values
/// of the spatial block contiguosly within the `depthAxisTensor` dimension, whereas
/// without it they are stored interleaved with existing values in the `depthAxisTensor` dimension.
/// This operation is the inverse of ``MPSGraph/spaceToDepth2DTensor:widthAxisTensor:heightAxisTensor:depthAxisTensor:blockSize:usePixelShuffleOrder:name:``.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - widthAxisTensor: A scalar tensor that contains the axis that defines the fastest running dimension within the block.
///   - heightAxisTensor: A scalar tensor that contains the axis that defines the 2nd fastest running dimension within the block.
///   - depthAxisTensor: A scalar tensor that contains the axis that defines the destination dimension, where to copy the blocks.
///   - blockSize: The size of the square spatial sub-block.
///   - usePixelShuffleOrder: A parameter that controls the layout of the sub-blocks within the depth dimension.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *)depthToSpace2DTensor:(MPSGraphTensor *) tensor
                        widthAxisTensor:(MPSGraphTensor *) widthAxisTensor
                       heightAxisTensor:(MPSGraphTensor *) heightAxisTensor
                        depthAxisTensor:(MPSGraphTensor *) depthAxisTensor
                              blockSize:(NSUInteger)blockSize
                   usePixelShuffleOrder:(BOOL)usePixelShuffleOrder
                                   name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/// Creates a space-to-batch operation and returns the result tensor.
///
/// This operation outputs a copy of the `input` tensor, where values from the
/// `spatialAxes` (for `usePixelShuffleOrder=YES` 1,2 or 3 axes supported, otherwise
/// limited only by `MPSNDArray` rank limitations) dimensions are moved in spatial blocks with
/// rectangular size defined by `blockDimensions` to the `batchAxis` dimension.
/// Use the `usePixelShuffleOrder` parameter  to control how the data within spatial blocks is ordered
/// in the `batchAxis` dimension: with `usePixelShuffleOrder=YES` MPSGraph stores
/// the values of the spatial blocks contiguosly within the `batchAxis` dimension, whereas
/// otherwise they are stored interleaved with existing values in the `batchAxis` dimension.
/// Note: This operation is the inverse of
///     ``MPSGraph/batchToSpaceTensor:spatialAxes:batchAxis:blockDimensions:usePixelShuffleOrder:name:``.
/// Note: This operation is a generalization of
///     ``MPSGraph/spaceToDepth2DTensor:widthAxis:heightAxis:depthAxis:blockSize:usePixelShuffleOrder:name:``.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - spatialAxes: The axes that define the dimensions containing the spatial blocks.
///   - batchAxis: The axis that defines the destination dimension, where to copy the blocks.
///   - blockDimensions: An array of numbers that defines the size of the rectangular spatial sub-block.
///   - usePixelShuffleOrder: A parameter that controls layout of the sub-blocks within the batch dimension.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *)spaceToBatchTensor:(MPSGraphTensor *) tensor
                          spatialAxes:(NSArray<NSNumber *> *) spatialAxes
                            batchAxis:(NSInteger) batchAxis
                      blockDimensions:(NSArray<NSNumber *> *) blockDimensions
                 usePixelShuffleOrder:(BOOL)usePixelShuffleOrder
                                 name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.1), tvos(16.1))
MPS_SWIFT_NAME( spaceToBatch(_:spatialAxes:batchAxis:blockDimensions:usePixelShuffleOrder:name:));

/// Creates a space-to-batch operation and returns the result tensor.
///
/// This operation outputs a copy of the `input` tensor, where values from the
/// `spatialAxesTensor` (for `usePixelShuffleOrder=YES` 1,2 or 3 axes supported, otherwise
/// limited only by `MPSNDArray` rank limitations) dimensions are moved in spatial blocks with
/// rectangular size defined by `blockDimensionsTensor` to the `batchAxisTensor` dimension.
/// Use the `usePixelShuffleOrder` parameter  to control how the data within spatial blocks is ordered
/// in the `batchAxisTensor` dimension: with `usePixelShuffleOrder=YES` MPSGraph stores
/// the values of the spatial blocks contiguosly within the `batchAxisTensor` dimension, whereas
/// otherwise they are stored interleaved with existing values in the `batchAxisTensor` dimension.
/// Note: This operation is the inverse of
///     ``MPSGraph/batchToSpaceTensor:spatialAxesTensor:batchAxisTensor:blockDimensionsTensor:usePixelShuffleOrder:name:``.
/// Note: This operation is a generalization of
///     ``MPSGraph/spaceToDepth2DTensor:widthAxisTensor:heightAxisTensor:depthAxisTensor:blockSize:usePixelShuffleOrder:name:``.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - spatialAxesTensor: A tensor that contains the axes that define the dimensions containing the spatial blocks.
///   - batchAxisTensor: A tensor that contains the axis that defines the destination dimension, where to copy the blocks.
///   - blockDimensionsTensor: A tensor that defines the size of the rectangular spatial sub-block.
///   - usePixelShuffleOrder: A parameter that controls layout of the sub-blocks within the batch dimension.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *)spaceToBatchTensor:(MPSGraphTensor *) tensor
                    spatialAxesTensor:(MPSGraphTensor *) spatialAxesTensor
                      batchAxisTensor:(MPSGraphTensor *) batchAxisTensor
                blockDimensionsTensor:(MPSGraphTensor *) blockDimensionsTensor
                 usePixelShuffleOrder:(BOOL)usePixelShuffleOrder
                                 name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.1), tvos(16.1))
MPS_SWIFT_NAME( spaceToBatch(_:spatialAxesTensor:batchAxisTensor:blockDimensionsTensor:usePixelShuffleOrder:name:));

/// Creates a batch-to-space operation and returns the result tensor.
///
/// This operation outputs a copy of the input tensor, where values from the 
/// `batchAxis` dimension are moved in spatial blocks of size `blockDimensions` to the
/// `spatialAxes` dimensions (for `usePixelShuffleOrder=YES` 1,2 or 3 axes supported,
/// otherwise limited only by `MPSNDArray` rank limitations).  Use the `usePixelShuffleOrder` parameter
/// to control how the data within spatial blocks is ordered in the
/// `batchAxis` dimension: with `usePixelShuffleOrder = YES` MPSGraph stores
/// the values of the spatial block contiguosly within the `batchAxis` dimension whereas
/// without it they are stored interleaved with existing values in the `batchAxis` dimension.
/// Note: This operation is the inverse of
///     ``MPSGraph/spaceToBatchTensor:spatialAxes:batchAxis:blockDimensions:usePixelShuffleOrder:name:``.
/// Note: This operation is a generalization of
///     ``MPSGraph/depthToSpace2DTensor:widthAxis:heightAxis:depthAxis:blockSize:usePixelShuffleOrder:name:``.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - spatialAxes: The axes that define the dimensions containing the spatial blocks.
///   - batchAxis: The axis that defines the destination dimension, where to copy the blocks.
///   - blockDimensions: An array of numbers that defines the size of the rectangular spatial sub-block.
///   - usePixelShuffleOrder: A parameter that controls layout of the sub-blocks within the batch dimension.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *)batchToSpaceTensor:(MPSGraphTensor *) tensor
                          spatialAxes:(NSArray<NSNumber *> *) spatialAxes
                            batchAxis:(NSInteger) batchAxis
                      blockDimensions:(NSArray<NSNumber *> *) blockDimensions
                 usePixelShuffleOrder:(BOOL)usePixelShuffleOrder
                                 name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.1), tvos(16.1))
MPS_SWIFT_NAME( batchToSpace(_:spatialAxes:batchAxis:blockDimensions:usePixelShuffleOrder:name:));

/// Creates a batch-to-space operation and returns the result tensor.
///
/// This operation outputs a copy of the input tensor, where values from the
/// `batchAxisTensor` dimension are moved in spatial blocks of size `blockDimensionsTensor` to the
/// `spatialAxesTensor` dimensions (for `usePixelShuffleOrder=YES` 1,2 or 3 axes supported,
/// otherwise limited only by `MPSNDArray` rank limitations).  Use the `usePixelShuffleOrder` parameter
/// to control how the data within spatial blocks is ordered in the
/// `batchAxisTensor` dimension: with `usePixelShuffleOrder = YES` MPSGraph stores
/// the values of the spatial block contiguosly within the `batchAxisTensor` dimension whereas
/// without it they are stored interleaved with existing values in the `batchAxisTensor` dimension.
/// Note: This operation is the inverse of
/// ``MPSGraph/spaceToBatchTensor:spatialAxesTensor:batchAxisTensor:blockDimensionsTensor:usePixelShuffleOrder:name:``.
/// Note: This operation is a generalization of
/// ``MPSGraph/depthToSpace2DTensor:widthAxisTensor:heightAxisTensor:depthAxisTensor:blockSize:usePixelShuffleOrder:name:``.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - spatialAxesTensor: A tensor that contains the axes that define the dimensions containing the spatial blocks.
///   - batchAxisTensor: A tensor that contains the axis that defines the destination dimension, where to copy the blocks.
///   - blockDimensionsTensor: A tensor that defines the size of the rectangular spatial sub-block.
///   - usePixelShuffleOrder: A parameter that controls layout of the sub-blocks within the batch dimension.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.

-(MPSGraphTensor *)batchToSpaceTensor:(MPSGraphTensor *) tensor
                    spatialAxesTensor:(MPSGraphTensor *) spatialAxesTensor
                      batchAxisTensor:(MPSGraphTensor *) batchAxisTensor
                blockDimensionsTensor:(MPSGraphTensor *) blockDimensionsTensor
                 usePixelShuffleOrder:(BOOL)usePixelShuffleOrder
                                 name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.1), tvos(16.1))
MPS_SWIFT_NAME( batchToSpace(_:spatialAxesTensor:batchAxisTensor:blockDimensionsTensor:usePixelShuffleOrder:name:));

/// Creates a reverse operation and returns the result tensor.
///
/// Reverses a tensor on given axes.
/// Semantics based on [TensorFlow reverse op](https://www.tensorflow.org/api_docs/python/tf/reverse).
///
/// - Parameters:
///   - tensor: The tensor to be reversed.
///   - axesTensor: A tensor that specifies axes to be reversed (Axes must be unique and within normal axis range).
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) reverseTensor:(MPSGraphTensor *) tensor
                       axesTensor:(MPSGraphTensor *) axesTensor
                             name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/// Creates a reverse operation and returns the result tensor.
///
/// Reverses a tensor on given axes.
/// Semantics based on [TensorFlow reverse op](https://www.tensorflow.org/api_docs/python/tf/reverse).
///
/// - Parameters:
///   - tensor: The tensor to be reversed.
///   - axes: A tensor that specifies axes to be reversed (Axes must be unique and within normal axis range).
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) reverseTensor:(MPSGraphTensor *) tensor
                             axes:(NSArray<NSNumber *> *) axes
                             name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/// Creates a reverse operation and returns the result tensor.
///
/// Reverses a tensor on all axes.
/// Semantics based on [TensorFlow reverse op](https://www.tensorflow.org/api_docs/python/tf/reverse).
///
/// - Parameters:
///   - tensor: The tensor to be reversed.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.

-(MPSGraphTensor *) reverseTensor:(MPSGraphTensor *) tensor
                             name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));


/// Creates a flatten2D operation and returns the result tensor.
///
/// Flattens dimensions before `axis` to `result[0]` and dimensions starting
/// from `axis` to `result[1]` and returns a rank-2 tensor as result.
///
/// - Parameters:
///   - tensor: The tensor to be flattened.
///   - axis: The axis around which to flatten.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) flatten2DTensor:(MPSGraphTensor *) tensor
                               axis:(NSInteger) axis
                               name:(NSString * _Nullable) name
MPS_SWIFT_NAME( flatten2D(_:axis:name:) )
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/// Creates a flatten2D operation and returns the result tensor.
///
/// Flattens dimensions before `axis` to `result[0]` and dimensions starting
/// from `axis` to `result[1]` and returns a rank-2 tensor as result.
///
/// - Parameters:
///   - tensor: The tensor to be flattened.
///   - axisTensor: A scalar tensor that contains the axis around which to flatten.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) flatten2DTensor:(MPSGraphTensor *) tensor
                         axisTensor:(MPSGraphTensor *) axisTensor
                               name:(NSString * _Nullable) name
MPS_SWIFT_NAME( flatten2D(_:axisTensor:name:) )
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/// Creates a broadcast operation and returns the result tensor.
///
/// Broadcasts values inside the tensor, starting from the trailing dimensions, to give it the correct shape.
/// This is equivalent to the broadcasting for arithmetic operations when operands have different shapes.
///
/// - Parameters:
///   - tensor: The tensor to be broadcasted
///   - shape: The shape of the result tensor.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) broadcastTensor:(MPSGraphTensor *) tensor
                            toShape:(MPSShape *) shape
                               name:(NSString * _Nullable) name
MPS_SWIFT_NAME( broadcast(_:shape:name:) )
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/// Creates a broadcast operation and returns the result tensor.
///
/// Broadcasts values inside the tensor, starting from the trailing dimensions, to give it the correct shape.
/// This is equivalent to the broadcasting for arithmetic operations when operands have different shapes.
///
/// - Parameters:
///   - tensor: The Tensor to be broadcasted.
///   - shapeTensor: A rank-1 tensor of type `MPSDataTypeInt32` or `MPSDataTypeInt64` that defines the shape of the result tensor.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) broadcastTensor:(MPSGraphTensor *) tensor
                      toShapeTensor:(MPSGraphTensor *) shapeTensor
                               name:(NSString * _Nullable) name
MPS_SWIFT_NAME( broadcast(_:shapeTensor:name:) )
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/// Creates a shape-of operation and returns the result tensor.
///
/// Returns a rank-1 tensor of type `MPSDataTypeInt32` with the values of the static shape of the input tensor.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) shapeOfTensor:(MPSGraphTensor *) tensor
                             name:(NSString * _Nullable) name
MPS_SWIFT_NAME( shapeOf(_:name:) )
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/// Creates a cast operation and returns the result tensor.
///
/// Returns the input tensor casted to the specied data type.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - type: The datatype to which MPSGraph casts the input.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *)castTensor:(MPSGraphTensor *)tensor
                       toType:(MPSDataType)type
                         name:(NSString * _Nullable)name
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/// Creates a reinterpret cast operation and returns the result tensor.
///
/// Returns input tensor (with element type `tensor_type`) reinterpreted to element type
/// passed in with the last dimension scaled by `sizeof(tensor_type) / sizeof(type)`. 
/// This operation is endianness agnostic and MPSGraph reinterprets the data with the endianness of the
/// system.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - type: The element type of the returned tensor.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
- (MPSGraphTensor *)reinterpretCastTensor:(MPSGraphTensor *)tensor
                                   toType:(MPSDataType)type
                                     name:(NSString *_Nullable)name
MPS_AVAILABLE_STARTING(macos(13.2), ios(16.3), tvos(16.3));

/// Creates a stack operation and returns the result tensor.
///
/// Stacks all input tensors along `axis` into a result tensor of `rank + 1`. Tensors must be broadcast
/// compatible along all dimensions except `axis`, and have the same type.
///
/// - Parameters:
///   - inputTensors: The input tensors.
///   - axis: The dimension to stack tensors into result. Must be in range: `-rank + 1 <= dimension < rank + 1`.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) stackTensors:(NSArray<MPSGraphTensor *> *) inputTensors
                            axis:(NSInteger) axis
                            name:(NSString * _Nullable) name
MPS_SWIFT_NAME( stack(_:axis:name:) )
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

/// Creates a split operation and returns the result tensor.
///
/// Splits the input tensor along `axis` into multiple result tensors of size determined by `splitSizes`.
/// Requires that the sum of `splitSizes` is equal to the lenth of the input along `axis`.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - splitSizes: The lengths of the result tensors along the split axis.
///   - axis: The dimension along which MPSGraph splits the input tensor.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(NSArray<MPSGraphTensor *> *) splitTensor:(MPSGraphTensor *) tensor
                                splitSizes:(NSArray<NSNumber *> *) splitSizes
                                      axis:(NSInteger) axis
                                      name:(NSString * _Nullable) name
MPS_SWIFT_NAME( split(_:splitSizes:axis:name:) )
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

/// Creates a split operation and returns the result tensor.
///
/// Splits the input tensor along `axis` into multiple result tensors of size determined by `splitSizesTensor`.
/// Requires that the sum of the elements of `splitSizesTensor` is equal to the lenth of the input along `axis`.
///
/// - Parameters:
///   - tensor: The input tensor
///   - splitSizesTensor: The lengths of the result tensors along the split axis.
///   - axis: The dimension along which MPSGraph splits the input tensor.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(NSArray<MPSGraphTensor *> *) splitTensor:(MPSGraphTensor *) tensor
                          splitSizesTensor:(MPSGraphTensor *) splitSizesTensor
                                      axis:(NSInteger) axis
                                      name:(NSString * _Nullable) name
MPS_SWIFT_NAME( split(_:splitSizesTensor:axis:name:) )
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

/// Creates a split operation and returns the result tensor.
///
/// Splits the input tensor along `axis` into `numsplits` result tensors of equal size.
/// Requires that the lenth of the input along `axis` is divisible by `numSplits`.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - numSplits: The number of result tensors to split to.
///   - axis: The dimension along which MPSGraph splits the input tensor.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(NSArray<MPSGraphTensor *> *) splitTensor:(MPSGraphTensor *) tensor
                                 numSplits:(NSUInteger) numSplits
                                      axis:(NSInteger) axis
                                      name:(NSString * _Nullable) name
MPS_SWIFT_NAME( split(_:numSplits:axis:name:) )
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

/// Creates a squeeze operation and returns the result tensor.
///
/// Squeezes the tensor, removing all dimensions with size 1.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) squeezeTensor:(MPSGraphTensor *) tensor
                             name:(NSString * _Nullable) name
MPS_SWIFT_NAME( squeeze(_:name:) )
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

/// Creates a squeeze operation and returns the result tensor.
///
/// Squeezes the tensor, removing a dimension with size 1 at the specified axis.
/// The size of the input tensor must be 1 at the specified axis.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - axis: The axis to squeeze.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) squeezeTensor:(MPSGraphTensor *) tensor
                             axis:(NSInteger) axis
                             name:(NSString * _Nullable) name
MPS_SWIFT_NAME( squeeze(_:axis:name:) )
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

/// Creates a squeeze operation and returns the result tensor.
///
/// Squeezes the tensor, removing dimensions with size 1 at specified axes. 
/// The size of the input tensor must be 1 at all specified axes.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - axes: The axes to squeeze.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) squeezeTensor:(MPSGraphTensor *) tensor
                             axes:(NSArray<NSNumber *> *) axes
                             name:(NSString * _Nullable) name
MPS_SWIFT_NAME( squeeze(_:axes:name:) )
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

/// Creates a squeeze operation and returns the result tensor.
///
/// Squeezes the tensor, removing dimensions with size 1 at specified axes.
/// The size of the input tensor must be 1 at all specified axes.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - axesTensor: The tensor containing the axes to squeeze.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) squeezeTensor:(MPSGraphTensor *) tensor
                       axesTensor:(MPSGraphTensor *) axesTensor
                             name:(NSString * _Nullable) name
MPS_SWIFT_NAME( squeeze(_:axesTensor:name:) )
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

/// Creates an expand-dimensions operation and returns the result tensor.
///
/// Expands the tensor, inserting a dimension with size 1 at the specified axis.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - axis: The axis to expand.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) expandDimsOfTensor:(MPSGraphTensor *) tensor
                                  axis:(NSInteger) axis
                                  name:(NSString * _Nullable) name
MPS_SWIFT_NAME( expandDims(_:axis:name:) )
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

/// Creates an expand-dimensions operation and returns the result tensor.
///
/// Expands the tensor, inserting dimensions with size 1 at specified axes.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - axes: The axes to expand.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) expandDimsOfTensor:(MPSGraphTensor *) tensor
                                  axes:(NSArray<NSNumber *> *) axes
                                  name:(NSString * _Nullable) name
MPS_SWIFT_NAME( expandDims(_:axes:name:) )
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

/// Creates an expand-dimensions operation and returns the result tensor.
///
/// Expands the tensor, inserting dimensions with size 1 at specified axes.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - axesTensor: The tensor containing the axes to expand.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.

-(MPSGraphTensor *) expandDimsOfTensor:(MPSGraphTensor *) tensor
                            axesTensor:(MPSGraphTensor *) axesTensor
                                  name:(NSString * _Nullable) name
MPS_SWIFT_NAME( expandDims(_:axesTensor:name:) )
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

/// Creates a get-coordindate operation and returns the result tensor.
///
/// Creates a tensor of specified shape with value at index `[i_0, i_1, ... , i_N] = i_axis`
/// For example, 
/// ```md 
/// coordinateAlongAxis(0, withShape=[5]) = [0, 1, 2, 3, 4] 
/// coordinateAlongAxis(0, withShape=[3,2]) = [[0, 0],
///                                            [1, 1],
///                                            [2, 2]]
/// ```
///
/// - Parameters:
///   - axis: The coordinate axis an element's value is set to. Negative values wrap around.
///   - shape: The shape of the result tensor.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) coordinateAlongAxis:(NSInteger) axis
                              withShape:(MPSShape *) shape
                                   name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

/// Creates a get-coordindate operation and returns the result tensor.
///
/// See ``MPSGraph/coordinateAlongAxis:withShape:name:``.
///
/// - Parameters:
///   - axisTensor: A Scalar tensor of type `MPSDataTypeInt32`, that specifies the coordinate axis an element's value is set to. Negative values wrap around.
///   - shape: The shape of the result tensor.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) coordinateAlongAxisTensor:(MPSGraphTensor *) axisTensor
                                    withShape:(MPSShape *) shape
                                         name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

/// Creates a get-coordindate operation and returns the result tensor.
///
/// See ``coordinateAlongAxis:withShape:name:``.
///
/// - Parameters:
///   - axis: The coordinate axis an element's value is set to. Negative values wrap around.
///   - shapeTensor: A rank-1 tensor of type `MPSDataTypeInt32` or `MPSDataTypeInt64` that defines the shape of the result tensor.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) coordinateAlongAxis:(NSInteger) axis
                        withShapeTensor:(MPSGraphTensor *) shapeTensor
                                   name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

/// Creates a get-coordindate operation and returns the result tensor.
///
/// See ``coordinateAlongAxis:withShape:name:``.
///
/// - Parameters:
///   - axisTensor: A Scalar tensor of type `MPSDataTypeInt32`, that specifies the coordinate axis an element's value is set to. Negative values wrap around.
///   - shapeTensor: A rank-1 tensor of type `MPSDataTypeInt32` or `MPSDataTypeInt64` that defines the shape of the result tensor.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) coordinateAlongAxisTensor:(MPSGraphTensor *) axisTensor
                              withShapeTensor:(MPSGraphTensor *) shapeTensor
                                         name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

@end

NS_ASSUME_NONNULL_END

#endif /* MPSGraphTensorShapeOps_h */
