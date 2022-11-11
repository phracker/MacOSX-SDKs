//
//  MPSGraphStencilOps.h
//  MetalPerformanceShadersGraph
//
//  Created by Riya Savla on 12/16/20.
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#ifndef MPSGraphStencilOps_h
#define MPSGraphStencilOps_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

MPS_CLASS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
@interface MPSGraphStencilOpDescriptor : NSObject<NSCopying>

@property (readwrite, nonatomic) MPSGraphReductionMode reductionMode;
@property (readwrite, nonatomic, copy) MPSShape * offsets;
@property (readwrite, nonatomic, copy) MPSShape * strides;
@property (readwrite, nonatomic, copy) MPSShape * dilationRates;
@property (readwrite, nonatomic, copy) MPSShape * explicitPadding;
@property (readwrite, nonatomic) MPSGraphPaddingMode boundaryMode;
@property (readwrite, nonatomic) MPSGraphPaddingStyle paddingStyle;
@property (readwrite, nonatomic) float paddingConstant;

/*!
 *  @abstract   stencil operation descriptor
 *
 *  @param      reductionMode               Reduction operation used to combine the source with weights. Defaults to Sum.
 *  @param      offsets                             Array of length 4 that determines where to start reading the `input` from.
 *                                  Only used when paddingStyle is MPSGraphPaddingStylExplicitOffset. Defaults to 0.
 *  @param      strides                             Array of length 4 that determines strides for the window of the weights Tensor. Defaults to 1.
 *  @param      dilationRates                Array of length 4 that determines dilation rates for the weights Tensor. Defaults to 1.
 *  @param      explicitPadding           Array of length 8 that determines paddings for the input Tensor's last 4 dimensions.
 *                                  explicitPadding[2*i] and explicitPadding[2*i + 1] for dimension i of the input.
 *                                  Only used when paddingSTyle is MPSGraphPaddingStyleExplicit or ExplicitOffset.
 *  @param      boundaryMode                  Determines what values to pad the input Tensor with. Defaults to MPSGraphPaddingModeZero.
 *  @param      paddingStyle                  Determines how many values to pad the inpur Tensor with.
 *  @param      paddingConstant           Specifies the value to pad the inputTensor with when using boundaryMode = constant. Defaults to 0.
 *
 *  @return     A valid MPSGraphStencilOpDescriptor object
 */

+(nullable instancetype) descriptorWithReductionMode:(MPSGraphReductionMode) reductionMode
                                             offsets:(MPSShape *) offsets
                                             strides:(MPSShape *) strides
                                       dilationRates:(MPSShape *) dilationRates
                                     explicitPadding:(MPSShape *) explicitPadding
                                        boundaryMode:(MPSGraphPaddingMode) boundaryMode
                                        paddingStyle:(MPSGraphPaddingStyle) paddingStyle
                                     paddingConstant:(float) paddingConstant;

/*!
 *  @abstract   stencil operation descriptor
 *  @discussion Stencil operation descriptor for paddingStyle MPSGraphPaddingStyleExplicitOffset.
 *              Default values for everything else.
 *
 *  @param      offsets                             Array of length 4 that determines where to start reading the `input` from.
 *  @param      explicitPadding           Array of length 8 that determines paddings for the input Tensor's last 4 dimensions.
 *                                  explicitPadding[2*i] and explicitPadding[2*i + 1] for dimension i of the input.
 *
 *  @return     A valid MPSGraphStencilOpDescriptor object
 */

+(nullable instancetype) descriptorWithOffsets:(MPSShape *) offsets
                               explicitPadding:(MPSShape *) explicitPadding;

/*!
 *  @abstract   stencil operation descriptor
 *  @discussion Stencil operation descriptor for paddingStyle MPSGraphPaddingStyleExplicit
 *              Default values for everything else.
 *
 *  @param      explicitPadding           Array of length 8 that determines paddings for the input Tensor's last 4 dimensions.
 *                                  explicitPadding[2*i] and explicitPadding[2*i + 1] for dimension i of the input.
 *
 *  @return     A valid MPSGraphStencilOpDescriptor object
 */

+(nullable instancetype) descriptorWithExplicitPadding:(MPSShape *) explicitPadding;

/*!
 *  @abstract   stencil operation descriptor
 *  @discussion Stencil operation descriptor with a user specified paddingStyle.
 *              Default values for everything else.
 *
 *  @param      paddingStyle                  Determines how many values to pad the inpur Tensor with.
 *
 *  @return     A valid MPSGraphStencilOpDescriptor object
 */

+(nullable instancetype) descriptorWithPaddingStyle:(MPSGraphPaddingStyle) paddingStyle;

@end

MPS_CLASS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
@interface MPSGraph(MPSGraphStencilOps)

/*!
 *  @abstract   stencil operation
 *  @discussion Performs a weighted reduction operation (`reductionMode`) on the last 4 dimensions of the `source`
 *  over the window determined by `weights`, acc. to the given `strides` and `dilationRates` and `paddingStyle`.
 *  `boundaryMode` determines what values to pad the `input` with. `offsets` are used to determine where
 *  to start reading the `input` from. `explicitPadding` can also be provided when using relevant paddingStyles.
 *
 *  y[i] = reduction { x[ i + j ] * w[j] }
 *
 *  @param      source                Tensor containing source data. Must be of rank 4 or greater.
 *  @param      weights              4-D Tensor containing the weights data.
 *  @param      descriptor       Descriptor object that specifies strides, dilationRates etc.
 *  @param      name                     The name for the operation.
 *
 *  @return     A valid MPSGraphTensor object
 */

-(MPSGraphTensor *) stencilWithSourceTensor:(MPSGraphTensor *) source
                              weightsTensor:(MPSGraphTensor *) weights
                                 descriptor:(MPSGraphStencilOpDescriptor *) descriptor
                                       name:(NSString * _Nullable) name;

@end

NS_ASSUME_NONNULL_END

#endif /* MPSGraphStencilOps_h */
