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

-(MPSGraphTensor *) reshapeTensor:(MPSGraphTensor *) tensor
                        withShape:(MPSShape *) shape
                             name:(NSString * _Nullable) name
MPS_SWIFT_NAME( reshape(_:shape:name:) );

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


-(MPSGraphTensor *) concatTensor:(MPSGraphTensor *) tensor
                      withTensor:(MPSGraphTensor *) tensor2
                       dimension:(NSUInteger) dimensionIndex
                            name:(NSString * _Nullable) name;

-(MPSGraphTensor *) concatTensors:(NSArray<MPSGraphTensor *> *) tensors
                       dimension:(NSUInteger) dimensionIndex
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

@end

NS_ASSUME_NONNULL_END

#endif /* MPSGraphTensorShapeOps_h */
