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

/*!
 *  @abstract   Create Reshape op and return the result tensor
 *  @discussion Reshape the input tensor to the target shape
 *              The shape must be compatible with the input tensor shape
 *              shape is allowed to contain dynamic dimensions (-1) when the result type can be inferred unambiguously
 *
 *  @param      tensor                  Tensor to be reshaped.
 *  @param      shape                    The result tensor shape
 *  @param      name                      The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) reshapeTensor:(MPSGraphTensor *) tensor
                        withShape:(MPSShape *) shape
                             name:(NSString * _Nullable) name
MPS_SWIFT_NAME( reshape(_:shape:name:) );

/*!
 *  @abstract   Create Reshape op and return the result tensor
 *  @discussion Reshape the input tensor to the target shapeTensor
 *              The shape must be compatible with the input tensor shape
 *              shapeTensor is allowed to contain dynamic dimensions (-1) when the result type can be inferred unambiguously
 *
 *  @param      tensor                  Tensor to be reshaped.
 *  @param      shapeTensor       1D Int32 or Int64 tensor. The result tensor shape
 *  @param      name                      The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) reshapeTensor:(MPSGraphTensor *) tensor
                  withShapeTensor:(MPSGraphTensor *) shapeTensor
                             name:(NSString * _Nullable) name
MPS_CLASS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
MPS_SWIFT_NAME( reshape(_:shapeTensor:name:) );

-(MPSGraphTensor *) transposeTensor:(MPSGraphTensor *) tensor
                          dimension:(NSUInteger) dimensionIndex
                      withDimension:(NSUInteger) dimensionIndex2
                               name:(NSString * _Nullable) name;

-(MPSGraphTensor *) sliceTensor:(MPSGraphTensor *) tensor
                      dimension:(NSUInteger) dimensionIndex
                          start:(NSInteger) start
                         length:(NSInteger) length
                           name:(NSString * _Nullable) name;

/*!
 *  @abstract   Create strided slice op and return the result tensor
 *  @discussion Slices a tensor starting from `starts`, stopping short before `ends` stepping
 *              `strides` paces between each value. Semantics based on
 *              https://www.tensorflow.org/api_docs/python/tf/strided_slice.
 *
 *  @param      tensor      Tensor to be sliced
 *  @param      starts      Array of numbers specifying starting point per dimension
 *  @param      ends          Array of numbers specifying ending point per dimension
 *  @param      strides   Array of numbers specifying strides per dimension
 *  @param      name           The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */

-(MPSGraphTensor *) sliceTensor:(MPSGraphTensor *) tensor
                         starts:(NSArray<NSNumber *> *) starts
                           ends:(NSArray<NSNumber *> *) ends
                        strides:(NSArray<NSNumber *> *) strides
                           name:(NSString * _Nullable) name;

/*!
 *  @abstract   Create strided slice op and return the result tensor
 *  @discussion Slices a tensor starting from `starts`, stopping short before `ends` stepping
 *              `strides` paces between each value. Semantics based on
 *              https://www.tensorflow.org/api_docs/python/tf/strided_slice.
 *
 *  @param      tensor              Tensor to be sliced
 *  @param      starts              Array of numbers specifying starting point per dimension
 *  @param      ends                  Array of numbers specifying ending point per dimension
 *  @param      strides           Array of numbers specifying strides per dimension
 *  @param      startMask       Bitmask indicating dimensions whose `starts` values should be ignored.
 *  @param      endMask           Bitmask indicating dimensions whose `ends` values should be ignored.
 *  @param      squeezeMask   Bitmask indicating dimensions that should be squeezed out from the result.
 *  @param      name                  The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */

-(MPSGraphTensor *) sliceTensor:(MPSGraphTensor *) tensor
                         starts:(NSArray<NSNumber *> *) starts
                           ends:(NSArray<NSNumber *> *) ends
                        strides:(NSArray<NSNumber *> *) strides
                      startMask:(uint32_t) startMask
                        endMask:(uint32_t) endMask
                    squeezeMask:(uint32_t) squeezeMask
                           name:(NSString * _Nullable) name;

/*!
 *  @abstract   Create strided slice gradient op and return the result tensor
 *
 *  @param      inputGradientTensor      Input gradient
 *  @param      fwdInShapeTensor    Shape of the forward pass input = shape of gradient output
 *  @param      starts      Array of numbers specifying starting point per dimension
 *  @param      ends          Array of numbers specifying ending point per dimension
 *  @param      strides   Array of numbers specifying strides per dimension
 *  @param      name           The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */

-(MPSGraphTensor *) sliceGradientTensor:(MPSGraphTensor *) inputGradientTensor
                       fwdInShapeTensor:(MPSGraphTensor *) fwdInShapeTensor
                                 starts:(NSArray<NSNumber *> *) starts
                                   ends:(NSArray<NSNumber *> *) ends
                                strides:(NSArray<NSNumber *> *) strides
                                   name:(NSString * _Nullable) name;

/*!
 *  @abstract   Create strided slice gradient op and return the result tensor
 *
 *  @param      inputGradientTensor      Input gradient
 *  @param      fwdInShapeTensor    Shape of the forward pass input = shape of gradient output
 *  @param      starts              Array of numbers specifying starting point per dimension
 *  @param      ends                  Array of numbers specifying ending point per dimension
 *  @param      strides           Array of numbers specifying strides per dimension
 *  @param      startMask       Bitmask indicating dimensions whose `starts` values should be ignored.
 *  @param      endMask           Bitmask indicating dimensions whose `ends` values should be ignored.
 *  @param      squeezeMask   Bitmask indicating dimensions that should be squeezed out from the result.
 *  @param      name                  The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */

-(MPSGraphTensor *) sliceGradientTensor:(MPSGraphTensor *) inputGradientTensor
                       fwdInShapeTensor:(MPSGraphTensor *) fwdInShapeTensor
                                 starts:(NSArray<NSNumber *> *) starts
                                   ends:(NSArray<NSNumber *> *) ends
                                strides:(NSArray<NSNumber *> *) strides
                              startMask:(uint32_t) startMask
                                endMask:(uint32_t) endMask
                            squeezeMask:(uint32_t) squeezeMask
                                   name:(NSString * _Nullable) name;

/*!
 *  @abstract   Create concat  op and return the result tensor
 *  @discussion Concatenate two input tensors along sepecified dimension. Tensors must be broadcast
 *              compatible along all other dimensions, and have the same type.
 *
 *  @param      tensor                         First tensor to concatenate
 *  @param      tensor2                       Second tensor to concatenate
 *  @param      dimensionIndex        The dimension to concatenate across, must be in range - rank <= dimension < rank
 *  @param      name                              The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */

-(MPSGraphTensor *) concatTensor:(MPSGraphTensor *) tensor
                      withTensor:(MPSGraphTensor *) tensor2
                       dimension:(NSInteger) dimensionIndex
                            name:(NSString * _Nullable) name;

/*!
 *  @abstract   Create concat op and return the result tensor
 *  @discussion Concatenate all input tensors along specified dimension. All inputs must be broadcast
 *              compatible along all other dimensions, and have the same type.
 *
 *  @param      tensors                      Tensors to concatenate
 *  @param      dimensionIndex       The dimension to concatenate across, must be in range - rank <= dimension < rank
 *  @param      name                             The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) concatTensors:(NSArray<MPSGraphTensor *> *) tensors
                        dimension:(NSInteger) dimensionIndex
                             name:(NSString * _Nullable) name;

/*!
 *  @abstract   Create concat op and return the result tensor
 *  @discussion Concatenate all input tensors along specified dimension. All inputs must be broadcast
 *              compatible along all other dimensions, and have the same type.
 *              When interleave is specified, all tensors will be interleaved. To interleave, all inputs must
 *              be broadcast compatible along the specified dimension as well.
 *              Example,
 *              @code
 *              operand0 = [1, 2, 3]
 *              operand1 = [4, 5, 6]
 *              concat([operand0, operand1], axis = 0, interleave = YES) = [1, 4, 2, 5, 3, 6]
 *              @endcode
 *
 *  @param      tensors                      Tensors to concatenate
 *  @param      dimensionIndex       The dimension to concatenate across, must be in range - rank <= dimension < rank
 *  @param      interleave                Interleave input tensors
 *  @param      name                             The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) concatTensors:(NSArray<MPSGraphTensor *> *) tensors
                        dimension:(NSInteger) dimensionIndex
                       interleave:(BOOL) interleave
                             name:(NSString * _Nullable) name;

-(MPSGraphTensor *) tileTensor:(MPSGraphTensor *) tensor
                withMultiplier:(MPSShape *) multiplier
                          name:(NSString * _Nullable) name;

-(MPSGraphTensor *) tileGradientWithIncomingGradientTensor:(MPSGraphTensor *) incomingGradientTensor
                                              sourceTensor:(MPSGraphTensor *) sourceTensor
                                            withMultiplier:(MPSShape *) multiplier
                                                      name:(NSString * _Nullable) name;


-(MPSGraphTensor *)padTensor:(MPSGraphTensor *) tensor
             withPaddingMode:(MPSGraphPaddingMode)paddingMode
                 leftPadding:(MPSShape *) leftPadding
                rightPadding:(MPSShape *) rightPadding
               constantValue:(double)constantValue
                        name:(NSString * _Nullable) name;
                        
-(MPSGraphTensor *)padGradientWithIncomingGradientTensor:(MPSGraphTensor *) incomingGradientTensor
                                            sourceTensor:(MPSGraphTensor *) sourceTensor
                                             paddingMode:(MPSGraphPaddingMode)paddingMode
                                             leftPadding:(MPSShape *) leftPadding
                                            rightPadding:(MPSShape *) rightPadding
                                                    name:(NSString * _Nullable) name;

-(MPSGraphTensor *)spaceToDepth2DTensor:(MPSGraphTensor *) tensor
                        widthAxisTensor:(MPSGraphTensor *) widthAxisTensor
                       heightAxisTensor:(MPSGraphTensor *) heightAxisTensor
                        depthAxisTensor:(MPSGraphTensor *) depthAxisTensor
                              blockSize:(NSUInteger)blockSize
                   usePixelShuffleOrder:(BOOL)usePixelShuffleOrder
                                   name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

-(MPSGraphTensor *)depthToSpace2DTensor:(MPSGraphTensor *) tensor
                        widthAxisTensor:(MPSGraphTensor *) widthAxisTensor
                       heightAxisTensor:(MPSGraphTensor *) heightAxisTensor
                        depthAxisTensor:(MPSGraphTensor *) depthAxisTensor
                              blockSize:(NSUInteger)blockSize
                   usePixelShuffleOrder:(BOOL)usePixelShuffleOrder
                                   name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

-(MPSGraphTensor *)spaceToDepth2DTensor:(MPSGraphTensor *) tensor
                              widthAxis:(NSUInteger) widthAxis
                             heightAxis:(NSUInteger) heightAxis
                              depthAxis:(NSUInteger) depthAxis
                              blockSize:(NSUInteger)blockSize
                   usePixelShuffleOrder:(BOOL)usePixelShuffleOrder
                                   name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

-(MPSGraphTensor *)depthToSpace2DTensor:(MPSGraphTensor *) tensor
                              widthAxis:(NSUInteger) widthAxis
                             heightAxis:(NSUInteger) heightAxis
                              depthAxis:(NSUInteger) depthAxis
                              blockSize:(NSUInteger)blockSize
                   usePixelShuffleOrder:(BOOL)usePixelShuffleOrder
                                   name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/*!
 *  @abstract   Create reverse op and return the result tensor
 *  @discussion Reverses a tensor on given axes
 *              https://www.tensorflow.org/api_docs/python/tf/reverse.
 *
 *  @param      tensor              Tensor to be reversed
 *  @param      axesTensor     Tensor that specifies axes to be reversed (Axes must be unique and within normal axis range).
 *  @param      name                  The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */

-(MPSGraphTensor *) reverseTensor:(MPSGraphTensor *) tensor
                       axesTensor:(MPSGraphTensor *) axesTensor
                             name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/*!
 *  @abstract   Create reverse op and return the result tensor
 *  @discussion Reverses a tensor on given axes
 *              https://www.tensorflow.org/api_docs/python/tf/reverse.
 *
 *  @param      tensor              Tensor to be reversed
 *  @param      axes                  Axes to be reversed (Axes must be unique and within normal axis range).
 *  @param      name                  The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */

-(MPSGraphTensor *) reverseTensor:(MPSGraphTensor *) tensor
                             axes:(NSArray<NSNumber *> *) axes
                             name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/*!
 *  @abstract   Create reverse op and return the result tensor
 *  @discussion Reverses a tensor on all axes
 *              https://www.tensorflow.org/api_docs/python/tf/reverse.
 *
 *  @param      tensor              Tensor to be reversed
 *  @param      name                  The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */

-(MPSGraphTensor *) reverseTensor:(MPSGraphTensor *) tensor
                             name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));


/*!
 *  @abstract   Create flatten2d op and return the result tensor
 *  @discussion Flattens dimensions before `axis` to `result[0]` and dimensions starting
 *              from `axis` to `result[1]` and returns a rank-2 tensor as result.
 *
 *  @param      tensor          Tensor to be flattened
 *  @param      axis            Axis around which to flatten
 *  @param      name            The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */

-(MPSGraphTensor *) flatten2DTensor:(MPSGraphTensor *) tensor
                               axis:(NSInteger) axis
                               name:(NSString * _Nullable) name
MPS_SWIFT_NAME( flatten2D(_:axis:name:) )
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/*!
 *  @abstract   Create flatten2d op and return the result tensor
 *  @discussion Flattens dimensions before `axis` to `result[0]` and dimensions starting
 *              from `axis` to `result[1]` and returns a rank-2 tensor as result.
 *
 *  @param      tensor              Tensor to be flattened
 *  @param      axisTensor          Axis around which to flatten
 *  @param      name                The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */

-(MPSGraphTensor *) flatten2DTensor:(MPSGraphTensor *) tensor
                         axisTensor:(MPSGraphTensor *) axisTensor
                               name:(NSString * _Nullable) name
MPS_SWIFT_NAME( flatten2D(_:axisTensor:name:) )
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/*!
 *  @abstract   Create broadcast op and return the result tensor
 *  @discussion Broadcast values inside the tensor, starting from the trailing dimensions, to give it the correct shape.
 *              This is equivalent to the broadcasting for arithmetic operations when operands have different shapes.
 *
 *  @param      tensor        Tensor to be broadcasted
 *  @param      shape          Shape of the result tensor
 *  @param      name            The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */

-(MPSGraphTensor *) broadcastTensor:(MPSGraphTensor *) tensor
                            toShape:(MPSShape *) shape
                               name:(NSString * _Nullable) name
MPS_SWIFT_NAME( broadcast(_:shape:name:) )
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/*!
 *  @abstract   Create broadcast op and return the result tensor
 *  @discussion Broadcast values inside the tensor, starting from the trailing dimensions, to give it the correct shape.
 *              This is equivalent to the broadcasting for arithmetic operations when operands have different shapes.
 *
 *  @param      tensor                Tensor to be broadcasted
 *  @param      shapeTensor     1D Int32 or Int64 tensor. Shape of the result tensor
 *  @param      name                     The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */

-(MPSGraphTensor *) broadcastTensor:(MPSGraphTensor *) tensor
                      toShapeTensor:(MPSGraphTensor *) shapeTensor
                               name:(NSString * _Nullable) name
MPS_SWIFT_NAME( broadcast(_:shapeTensor:name:) )
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/*!
 *  @abstract   Create shapeof op and return the result tensor
 *  @discussion Returns a 1D Int32 tensor with value the static shape of the input tensor
 *
 *  @param      tensor        Input tensor
 *  @param      name            The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */

-(MPSGraphTensor *) shapeOfTensor:(MPSGraphTensor *) tensor
                             name:(NSString * _Nullable) name
MPS_SWIFT_NAME( shapeOf(_:name:) )
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/*!
 *  @abstract   Create cast op and return the result tensor
 *  @discussion Returns input tensor casted to the dataType passed in
 *
 *  @param      tensor        Input tensor
 *  @param      type        Input tensor
 *  @param      name            The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *)castTensor:(MPSGraphTensor *)tensor
                       toType:(MPSDataType)type
                         name:(NSString *)name
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

@end

NS_ASSUME_NONNULL_END

#endif /* MPSGraphTensorShapeOps_h */
