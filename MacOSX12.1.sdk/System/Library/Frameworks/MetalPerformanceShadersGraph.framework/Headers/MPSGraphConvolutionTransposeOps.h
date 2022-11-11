//
//  Header.h
//  MetalPerformanceShadersGraph
//
//  Created on 5/15/20.
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#ifndef MPSGraphConvolutionTransposeOps_h
#define MPSGraphConvolutionTransposeOps_h

#import <MetalPerformanceShadersGraph/MPSGraphConvolutionOps.h>

NS_ASSUME_NONNULL_BEGIN

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(MPSGraphConvolutionTransposeOps)

/*!
 *  @abstract   Create ConvolutionTranspose op and return the result tensor
 *  @discussion Convolution Tranpose op is exactly the same as convolution gradint with respect to input image (convolution2DDataGradient)
 *              Weights tensor and source tensors are interpreted as they are in convolution2DDataGradientWithIncomingGradient. For example
 *              if weightsTensor layout is HWIO, inner most (fastest moving) dimension, denoted by O here should be equal to inputFeatureChannels
 *              i.e. number of channels in source tensor
 *              and next fasted moving dimension denoated by I is equal to number of channels in returns (destination) tensor outputFeatureChannels.
 *              TensorFlow interprets the weights tensor same way excpet that it states weights are in HWOI format. We dont define another weights format enum
 *              rather we reinterpret HWIO just like TensorFlow does for gradient with data.
 *              Normally in auto encoder, convoluton transpose is associated with regular convolution i.e. convolution downsamples by stride s
 *              and convolution tranpose upsamples by factor s.
 *              In that case, convolution transpose can map same source size to multiple destination sizes. The relationship between sourceWidth and destinationWidth is
 *              (sourceWidth - 1) * stride + 1 + (kernelWidth - 1) * dilationRate <= destinationWidth + paddingLeft + paddingRight
 *              so there are stride -1 destinationWidth that give same sourceWidth. In order to disambiguate, outputShape parameter is used.
 *              This is what TensorFlow does.
 *              PyTourch takes additional outputPadding that is applied to destination size.
 *
 * @param       source             input tensor
 * @param       weights           weights tensor
 * @param       outputShape  shape of the result tensor
 * @param       descriptor    descriptor for the corresponding forward Conv2d operation
 * @param       name                 name for the operation
 *
 * @return      A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) convolutionTranspose2DWithSourceTensor:(MPSGraphTensor *) source
                                             weightsTensor:(MPSGraphTensor *) weights
                                               outputShape:(MPSShape*) outputShape
                                                descriptor:(MPSGraphConvolution2DOpDescriptor *) descriptor
                                                      name:(NSString * _Nullable) name
MPS_SWIFT_NAME( convolutionTranspose2D(_:weights:outputShape:descriptor:name:) );

/*!
 *  @abstract   Create ConvolutionTranspose op and return the result tensor
 *  @discussion Convolution Tranpose op is exactly the same as convolution gradint with respect to input image (convolution2DDataGradient)
 *              Weights tensor and source tensors are interpreted as they are in convolution2DDataGradientWithIncomingGradient. For example
 *              if weightsTensor layout is HWIO, inner most (fastest moving) dimension, denoted by O here should be equal to inputFeatureChannels
 *              i.e. number of channels in source tensor
 *              and next fasted moving dimension denoated by I is equal to number of channels in returns (destination) tensor outputFeatureChannels.
 *              TensorFlow interprets the weights tensor same way excpet that it states weights are in HWOI format. We dont define another weights format enum
 *              rather we reinterpret HWIO just like TensorFlow does for gradient with data.
 *              Normally in auto encoder, convoluton transpose is associated with regular convolution i.e. convolution downsamples by stride s
 *              and convolution tranpose upsamples by factor s.
 *              In that case, convolution transpose can map same source size to multiple destination sizes. The relationship between sourceWidth and destinationWidth is
 *              (sourceWidth - 1) * stride + 1 + (kernelWidth - 1) * dilationRate <= destinationWidth + paddingLeft + paddingRight
 *              so there are stride -1 destinationWidth that give same sourceWidth. In order to disambiguate, outputShape parameter is used.
 *              This is what TensorFlow does.
 *              PyTourch takes additional outputPadding that is applied to destination size.
 *
 * @param       source             input tensor
 * @param       weights           weights tensor
 * @param       outputShape  1D Int32 or Int64 tensor. shape of the result tensor
 * @param       descriptor    descriptor for the corresponding forward Conv2d operation
 * @param       name                 name for the operation
 *
 * @return      A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) convolutionTranspose2DWithSourceTensor:(MPSGraphTensor *) source
                                             weightsTensor:(MPSGraphTensor *) weights
                                         outputShapeTensor:(MPSGraphTensor*) outputShape
                                                descriptor:(MPSGraphConvolution2DOpDescriptor *) descriptor
                                                      name:(NSString * _Nullable) name
MPS_CLASS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
MPS_SWIFT_NAME( convolutionTranspose2D(_:weights:outputShapeTensor:descriptor:name:) );

/*!
 *  @abstract   Create ConvolutionTranspose gradient op and return the result tensor
 *  @discussion Computes the gradient of source input for the forward pass ConvolutionTranspose op with identical parameters.
 *              See discussion of convolutionTranspose2DWithSourceTensor for more in depth description of  paramters.
 *
 *  @param      incomingGradient                              Incoming gradient tensor
 *  @param      weights                                                  Forward pass weights tensor
 *  @param      outputShape                                         Shape of the forward pass source tensor
 *  @param      forwardConvolutionDescriptor   Forward pass op descriptor
 *  @param      name                                                        The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) convolutionTranspose2DDataGradientWithIncomingGradientTensor:(MPSGraphTensor *) incomingGradient
                                                                   weightsTensor:(MPSGraphTensor *) weights
                                                                     outputShape:(MPSShape *) outputShape
                                                    forwardConvolutionDescriptor:(MPSGraphConvolution2DOpDescriptor *) forwardConvolutionDescriptor
                                                                            name:(NSString * _Nullable) name
MPS_SWIFT_NAME( convolutionTranspose2DDataGradient(_:weights:outputShape:forwardConvolutionDescriptor:name:) );

/*!
 *  @abstract   Create ConvolutionTranspose gradient op and return the result tensor
 *  @discussion Computes the gradient of source input for the forward pass ConvolutionTranspose op with identical parameters.
 *              See discussion of convolutionTranspose2DWithSourceTensor for more in depth description of  paramters.
 *
 *  @param      incomingGradient                              Incoming gradient tensor
 *  @param      weights                                                  Forward pass weights tensor
 *  @param      outputShape                                         1D Int32 or Int64 Tensor. Shape of the forward pass source tensor
 *  @param      forwardConvolutionDescriptor   Forward pass op descriptor
 *  @param      name                                                        The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) convolutionTranspose2DDataGradientWithIncomingGradientTensor:(MPSGraphTensor *) incomingGradient
                                                                   weightsTensor:(MPSGraphTensor *) weights
                                                               outputShapeTensor:(MPSGraphTensor *) outputShape
                                                    forwardConvolutionDescriptor:(MPSGraphConvolution2DOpDescriptor *) forwardConvolutionDescriptor
                                                                            name:(NSString * _Nullable) name
MPS_CLASS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
MPS_SWIFT_NAME( convolutionTranspose2DDataGradient(_:weights:outputShapeTensor:forwardConvolutionDescriptor:name:) );

/*!
 *  @abstract   Create ConvolutionTranspose gradient op and return the result tensor
 *  @discussion Computes the gradient of weights input for the forward pass ConvolutionTranspose op with identical parameters.
 *              See discussion of convolutionTranspose2DWithSourceTensor for more in depth description of  paramters.
 *
 *  @param      incomingGradientTensor                 Incoming gradient tensor
 *  @param      source                                                    Forward pass source tensor
 *  @param      outputShape                                         Shape of the forward pass source weights tensor
 *  @param      forwardConvolutionDescriptor   Forward pass op descriptor
 *  @param      name                                                        The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) convolutionTranspose2DWeightsGradientWithIncomingGradientTensor:(MPSGraphTensor *) incomingGradientTensor
                                                                       sourceTensor:(MPSGraphTensor *) source
                                                                        outputShape:(MPSShape *) outputShape
                                                       forwardConvolutionDescriptor:(MPSGraphConvolution2DOpDescriptor *) forwardConvolutionDescriptor
                                                                               name:(NSString * _Nullable) name
MPS_SWIFT_NAME( convolutionTranspose2DWeightsGradient(_:weights:outputShape:forwardConvolutionDescriptor:name:) );

/*!
 *  @abstract   Create ConvolutionTranspose gradient op and return the result tensor
 *  @discussion Computes the gradient of weights input for the forward pass ConvolutionTranspose op with identical parameters.
 *              See discussion of convolutionTranspose2DWithSourceTensor for more in depth description of  paramters.
 *
 *  @param      incomingGradientTensor                 Incoming gradient tensor
 *  @param      source                                                    Forward pass source tensor
 *  @param      outputShape                                         1D Int32 or Int64 Tensor. Shape of the forward pass source weights tensor
 *  @param      forwardConvolutionDescriptor   Forward pass op descriptor
 *  @param      name                                                        The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) convolutionTranspose2DWeightsGradientWithIncomingGradientTensor:(MPSGraphTensor *) incomingGradientTensor
                                                                       sourceTensor:(MPSGraphTensor *) source
                                                                  outputShapeTensor:(MPSGraphTensor *) outputShape
                                                       forwardConvolutionDescriptor:(MPSGraphConvolution2DOpDescriptor *) forwardConvolutionDescriptor
                                                                               name:(NSString * _Nullable) name
MPS_CLASS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
MPS_SWIFT_NAME( convolutionTranspose2DWeightsGradient(_:weights:outputShapeTensor:forwardConvolutionDescriptor:name:) );

@end

NS_ASSUME_NONNULL_END

#endif /* Header_h */
