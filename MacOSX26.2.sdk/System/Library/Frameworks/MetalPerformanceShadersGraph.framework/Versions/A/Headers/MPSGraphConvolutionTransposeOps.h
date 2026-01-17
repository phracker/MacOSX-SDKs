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

/// This is a category that defines the methods which can be used to add 2D-convolution transpose operator to the graph with properties described by an instance of `MPSGraphConvolution2DOpDescriptor`.

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(MPSGraphConvolutionTransposeOps)

/// Creates a convolution transpose operation and returns the result tensor.
///
/// Convolution Tranpose operation is exactly the same as convolution gradint with respect to input image `convolution2DDataGradientWithIncomingGradient`.
/// Weights tensor and source tensors are interpreted as they are in `convolution2DDataGradientWithIncomingGradient`.
/// Convolution with stride `s` downsamples source tensor by factor `s` in spatial dimensions whereas convolution tranpose with stride `s` upsamples
/// source tensor by factor `s`. Convolution transpose can map the same source size to multiple destination sizes. The relationship between the width of the
/// source and the width of the destination is `(sourceWidth - 1)stride + 1 + (kernelWidth - 1)dilationRate <= destinationWidth + paddingLeft + paddingRight`
/// so there are stride -1 values of the width of the destination that give same width of the source. In order to disambiguate, outputShape parameter is used.
///
/// - Parameters:
///   - source: input tensor
///   - weights: weights tensor
///   - outputShape: shape of the result tensor.
///   - descriptor: descriptor for the corresponding forward 2D-convolution operation
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) convolutionTranspose2DWithSourceTensor:(MPSGraphTensor *) source
                                             weightsTensor:(MPSGraphTensor *) weights
                                               outputShape:(MPSShape*) outputShape
                                                descriptor:(MPSGraphConvolution2DOpDescriptor *) descriptor
                                                      name:(NSString * _Nullable) name
MPS_SWIFT_NAME( convolutionTranspose2D(_:weights:outputShape:descriptor:name:) );

/// Creates a convolution transpose operation and returns the result tensor.
///
/// - Parameters:
///   - source: input tensor
///   - weights: weights tensor
///   - outputShape: 1D Int32 or Int64 tensor. shape of the result tensor.
///   - descriptor: descriptor for the corresponding forward Conv2D operation
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) convolutionTranspose2DWithSourceTensor:(MPSGraphTensor *) source
                                             weightsTensor:(MPSGraphTensor *) weights
                                         outputShapeTensor:(MPSGraphTensor*) outputShape
                                                descriptor:(MPSGraphConvolution2DOpDescriptor *) descriptor
                                                      name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
MPS_SWIFT_NAME( convolutionTranspose2D(_:weights:outputShapeTensor:descriptor:name:) );

/// Creates a convolution transpose gradient operation with respect to the source tensor of convolution transpose operation and returns the result tensor.
///
/// Inserts an operation in graph to compute gradient of convolution transpose with respect to source tensor of the corresponding
/// convolution transpose operation.
///
/// - Parameters:
///   - incomingGradient: Incoming gradient tensor
///   - weights: Forward pass weights tensor
///   - outputShape: Shape of the forward pass source tensor
///   - forwardConvolutionDescriptor: Forward pass op descriptor
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) convolutionTranspose2DDataGradientWithIncomingGradientTensor:(MPSGraphTensor *) incomingGradient
                                                                   weightsTensor:(MPSGraphTensor *) weights
                                                                     outputShape:(MPSShape *) outputShape
                                                    forwardConvolutionDescriptor:(MPSGraphConvolution2DOpDescriptor *) forwardConvolutionDescriptor
                                                                            name:(NSString * _Nullable) name
MPS_SWIFT_NAME( convolutionTranspose2DDataGradient(_:weights:outputShape:forwardConvolutionDescriptor:name:) );

/// Creates a convolution transpose gradient operation with respect to the source tensor of convolution transpose operation and returns the result tensor.
///
/// Inserts an operation in graph to compute gradient of convolution transpose with respect to source tensor of the corresponding
/// convolution transpose operation.
///
/// - Parameters:
///   - incomingGradient: Incoming gradient tensor
///   - weights: Forward pass weights tensor
///   - outputShape: 1D Int32 or Int64 Tensor. Shape of the forward pass source tensor
///   - forwardConvolutionDescriptor: Forward pass op descriptor
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) convolutionTranspose2DDataGradientWithIncomingGradientTensor:(MPSGraphTensor *) incomingGradient
                                                                   weightsTensor:(MPSGraphTensor *) weights
                                                               outputShapeTensor:(MPSGraphTensor *) outputShape
                                                    forwardConvolutionDescriptor:(MPSGraphConvolution2DOpDescriptor *) forwardConvolutionDescriptor
                                                                            name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
MPS_SWIFT_NAME( convolutionTranspose2DDataGradient(_:weights:outputShapeTensor:forwardConvolutionDescriptor:name:) );

/// Creates a convolution transpose gradient operation with respect to the weights tensor of the convolution transpose operation and returns the result tensor.
///
/// Inserts an operation in graph to compute gradient of convolution transpose with respect to the weights tensor of the corresponding
/// convolution transpose operation.
///
/// - Parameters:
///   - incomingGradientTensor: Incoming gradient tensor
///   - source: Forward pass source tensor
///   - outputShape: Shape of the forward pass source weights tensor
///   - forwardConvolutionDescriptor: Forward pass op descriptor
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) convolutionTranspose2DWeightsGradientWithIncomingGradientTensor:(MPSGraphTensor *) incomingGradientTensor
                                                                       sourceTensor:(MPSGraphTensor *) source
                                                                        outputShape:(MPSShape *) outputShape
                                                       forwardConvolutionDescriptor:(MPSGraphConvolution2DOpDescriptor *) forwardConvolutionDescriptor
                                                                               name:(NSString * _Nullable) name
MPS_SWIFT_NAME( convolutionTranspose2DWeightsGradient(_:weights:outputShape:forwardConvolutionDescriptor:name:) );

/// Creates a convolution transpose gradient operation with respect to the weights tensor of the convolution transpose operation and returns the result tensor.
///
/// Inserts an operation in graph to compute gradient of convolution transpose with respect to the weights tensor of the corresponding
/// convolution transpose operation.
///
/// - Parameters:
///   - incomingGradientTensor: Incoming gradient tensor
///   - source: Forward pass source tensor
///   - outputShape: 1D Int32 or Int64 Tensor. Shape of the forward pass source weights tensor
///   - forwardConvolutionDescriptor: Forward pass op descriptor
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) convolutionTranspose2DWeightsGradientWithIncomingGradientTensor:(MPSGraphTensor *) incomingGradientTensor
                                                                       sourceTensor:(MPSGraphTensor *) source
                                                                  outputShapeTensor:(MPSGraphTensor *) outputShape
                                                       forwardConvolutionDescriptor:(MPSGraphConvolution2DOpDescriptor *) forwardConvolutionDescriptor
                                                                               name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
MPS_SWIFT_NAME( convolutionTranspose2DWeightsGradient(_:weights:outputShapeTensor:forwardConvolutionDescriptor:name:) );

@end

NS_ASSUME_NONNULL_END

#endif /* Header_h */
