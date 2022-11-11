//
//  MPSGraphConvolutionOps.h
//  MetalPerformanceShadersGraph
//
//  Created on 12/20/19.
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#ifndef MPSGraphConvolutionOps_h
#define MPSGraphConvolutionOps_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraphConvolution2DOpDescriptor : NSObject<NSCopying>


@property (readwrite, nonatomic) NSUInteger strideInX;
@property (readwrite, nonatomic) NSUInteger strideInY;
@property (readwrite, nonatomic) NSUInteger dilationRateInX;
@property (readwrite, nonatomic) NSUInteger dilationRateInY;

@property (readwrite, nonatomic) NSUInteger paddingLeft;
@property (readwrite, nonatomic) NSUInteger paddingRight;
@property (readwrite, nonatomic) NSUInteger paddingTop;
@property (readwrite, nonatomic) NSUInteger paddingBottom;

@property (readwrite, nonatomic) MPSGraphPaddingStyle paddingStyle;
@property (readwrite, nonatomic) MPSGraphTensorNamedDataLayout dataLayout;
@property (readwrite, nonatomic) MPSGraphTensorNamedDataLayout weightsLayout;

/*! @property   groups
 *  @discussion groups of the operation
 */
@property (readwrite, nonatomic) NSUInteger groups;


+(nullable instancetype) descriptorWithStrideInX:(NSUInteger) strideInX
                                       strideInY:(NSUInteger) strideInY
                                 dilationRateInX:(NSUInteger) dilationRateInX
                                 dilationRateInY:(NSUInteger) dilationRateInY
                                          groups:(NSUInteger) groups
                                     paddingLeft:(NSUInteger) paddingLeft
                                    paddingRight:(NSUInteger) paddingRight
                                      paddingTop:(NSUInteger) paddingTop
                                   paddingBottom:(NSUInteger) paddingBottom
                                    paddingStyle:(MPSGraphPaddingStyle) paddingStyle
                                      dataLayout:(MPSGraphTensorNamedDataLayout) dataLayout
                                   weightsLayout:(MPSGraphTensorNamedDataLayout) weightsLayout;

+(nullable instancetype) descriptorWithStrideInX:(NSUInteger) strideInX
                                       strideInY:(NSUInteger) strideInY
                                 dilationRateInX:(NSUInteger) dilationRateInX
                                 dilationRateInY:(NSUInteger) dilationRateInY
                                          groups:(NSUInteger) groups
                                    paddingStyle:(MPSGraphPaddingStyle) paddingStyle
                                      dataLayout:(MPSGraphTensorNamedDataLayout) dataLayout
                                   weightsLayout:(MPSGraphTensorNamedDataLayout) weightsLayout;


-(void) setExplicitPaddingWithPaddingLeft:(NSUInteger) paddingLeft
                             paddingRight:(NSUInteger) paddingRight
                               paddingTop:(NSUInteger) paddingTop
                            paddingBottom:(NSUInteger) paddingBottom;


@end

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(MPSGraphConvolutionOps)



-(MPSGraphTensor *) convolution2DWithSourceTensor:(MPSGraphTensor *) source
                                    weightsTensor:(MPSGraphTensor *) weights
                                       descriptor:(MPSGraphConvolution2DOpDescriptor *) descriptor
                                             name:(NSString * _Nullable) name
MPS_SWIFT_NAME( convolution2D(_:weights:descriptor:name:) );

/*!
 *  @abstract   Create Convolution gradient op and return the result tensor
 *  @discussion Computes the gradient of source input for the forward pass Convolution op with identical parameters.
 *              See discussion of convolution2DWithSourceTensor for more in depth description of  paramters.
 *
 *  @param      incomingGradient                              Incoming gradient tensor
 *  @param      weights                                                  Forward pass weights tensor
 *  @param      outputShape                                         Shape of the forward pass source tensor
 *  @param      forwardConvolutionDescriptor   Forward pass op descriptor
 *  @param      name                                                        The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) convolution2DDataGradientWithIncomingGradientTensor:(MPSGraphTensor *) incomingGradient
                                                          weightsTensor:(MPSGraphTensor *) weights
                                                            outputShape:(MPSShape *) outputShape
                                           forwardConvolutionDescriptor:(MPSGraphConvolution2DOpDescriptor *) forwardConvolutionDescriptor
                                                                   name:(NSString * _Nullable) name
MPS_SWIFT_NAME( convolution2DDataGradient(_:weights:outputShape:forwardConvolutionDescriptor:name:) );

/*!
 *  @abstract   Create Convolution gradient op and return the result tensor
 *  @discussion Computes the gradient of source input for the forward pass Convolution op with identical parameters.
 *              See discussion of convolution2DWithSourceTensor for more in depth description of  paramters.
 *
 *  @param      gradient                                                Incoming gradient tensor
 *  @param      weights                                                  Forward pass weights tensor
 *  @param      outputShapeTensor                           1D Int32 or Int64 Tensor. Shape of the forward pass source tensor
 *  @param      forwardConvolutionDescriptor   Forward pass op descriptor
 *  @param      name                                                        The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) convolution2DDataGradientWithIncomingGradientTensor:(MPSGraphTensor *) gradient
                                                          weightsTensor:(MPSGraphTensor *) weights
                                                      outputShapeTensor:(MPSGraphTensor *) outputShapeTensor
                                           forwardConvolutionDescriptor:(MPSGraphConvolution2DOpDescriptor *) forwardConvolutionDescriptor
                                                                   name:(NSString * _Nullable) name
MPS_CLASS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
MPS_SWIFT_NAME( convolution2DDataGradient(_:weights:outputShapeTensor:forwardConvolutionDescriptor:name:) );

/*!
 *  @abstract   Create Convolution gradient op and return the result tensor
 *  @discussion Computes the gradient of weights input for the forward pass Convolution op with identical parameters.
 *              See discussion of convolution2DWithSourceTensor for more in depth description of  paramters.
 *
 *  @param      incomingGradient                              Incoming gradient tensor
 *  @param      source                                                    Forward pass source tensor
 *  @param      outputShape                                         Shape of the forward pass weights tensor
 *  @param      forwardConvolutionDescriptor   Forward pass op descriptor
 *  @param      name                                                        The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) convolution2DWeightsGradientWithIncomingGradientTensor:(MPSGraphTensor *) incomingGradient
                                                              sourceTensor:(MPSGraphTensor *) source
                                                               outputShape:(MPSShape *) outputShape
                                              forwardConvolutionDescriptor:(MPSGraphConvolution2DOpDescriptor *) forwardConvolutionDescriptor
                                                                      name:(NSString * _Nullable) name
MPS_SWIFT_NAME( convolution2DWeightsGradient(_:source:outputShape:forwardConvolutionDescriptor:name:) );

/*!
 *  @abstract   Create Convolution gradient op and return the result tensor
 *  @discussion Computes the gradient of weights input for the forward pass Convolution op with identical parameters.
 *              See discussion of convolution2DWithSourceTensor for more in depth description of  paramters.
 *
 *  @param      gradient                                                Incoming gradient tensor
 *  @param      source                                                    Forward pass source tensor
 *  @param      outputShapeTensor                           1D int32 or Int64 Tensor. Shape of the forward pass weights tensor
 *  @param      forwardConvolutionDescriptor   Forward pass op descriptor
 *  @param      name                                                        The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) convolution2DWeightsGradientWithIncomingGradientTensor:(MPSGraphTensor *) gradient
                                                              sourceTensor:(MPSGraphTensor *) source
                                                         outputShapeTensor:(MPSGraphTensor *) outputShapeTensor
                                              forwardConvolutionDescriptor:(MPSGraphConvolution2DOpDescriptor *) forwardConvolutionDescriptor
                                                                      name:(NSString * _Nullable) name
MPS_CLASS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
MPS_SWIFT_NAME( convolution2DWeightsGradient(_:source:outputShapeTensor:forwardConvolutionDescriptor:name:) );

@end

NS_ASSUME_NONNULL_END

#endif /* MPSGraphConvolutionOps_h */
