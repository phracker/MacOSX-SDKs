//
//  MPSCNNNormalizationWeights.h
//  MPSNeuralNetwork
//
//  Created by Justin Voo on 2/4/18.
//  Copyright © 2018 Apple. All rights reserved.
//

#ifndef MPSCNNNormalizationWeights_h
#define MPSCNNNormalizationWeights_h

#include <MPSNeuralNetwork/MPSCNNKernel.h>

#ifdef __cplusplus
extern "C" {
#endif
    
/*!
 *  @class  MPSCNNNormalizationGammaAndBetaState
 *  @description A state which contains gamma and beta terms used to apply a scale
 *               and bias in either an MPSCNNInstanceNormalization or MPSCNNBatchNormalization
 *               operation.
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
@interface MPSCNNNormalizationGammaAndBetaState : MPSState

/*! @property   gamma
 *  @abstract   A MTLBuffer containing the gamma terms.
 */
@property (readonly, nonatomic) __nonnull id<MTLBuffer> gamma;

/*! @property   beta
 *  @abstract   A MTLBuffer containing the beta terms.
 */
@property (readonly, nonatomic) __nonnull id<MTLBuffer> beta;

/*!
 *  @abstract   Initialize a MPSCNNNormalizationGammaAndBetaState object using values
 *              contained in MTLBuffers.
 *
 *  @param      gamma       The MTLBuffer containing gamma terms.
 *
 *  @param      beta        The MTLBuffer containing beta terms.
 */
- (nonnull instancetype) initWithGamma: (__nonnull id<MTLBuffer>) gamma
                                  beta: (__nonnull id<MTLBuffer>) beta;

/*!
 *  @abstract   Create a temporary MPSCNNNormalizationGammaAndBetaState suitable
 *              for a normalization operation on images containing no more than
 *              the specified number of feature channels.
 *
 *  @param      commandBuffer           The command buffer on which the temporary state will
 *                                      be used.
 *
 *  @param      numberOfFeatureChannels The number of feature channels used to size the
 *                                      state.
 */
+ (nonnull instancetype) temporaryStateWithCommandBuffer: (__nonnull id<MTLCommandBuffer>) commandBuffer
                                 numberOfFeatureChannels: (NSUInteger) numberOfFeatureChannels;

@end    // MPSCNNNormalizationGammaAndBetaState
    
#ifdef __cplusplus
}
#endif
#endif /* MPSCNNNormalizationWeights_h */
