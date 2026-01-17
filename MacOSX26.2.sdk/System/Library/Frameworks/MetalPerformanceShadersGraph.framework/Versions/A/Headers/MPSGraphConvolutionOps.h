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

/// A class that describes the properties of a 2D-convolution operator.
///
/// Use an instance of this class is to add a 2D-convolution operator with the desired properties to the graph.
MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraphConvolution2DOpDescriptor : MPSGraphObject<NSCopying>

/// The scale that maps `x`-coordinate of the destination to `x`-coordinate of the source.
///
/// Source `x`-coordinate, `sx` is computed from destination `x`-coordinate, `dx` as `sx = strideInX*dx`.
/// Default value is 1.
@property (readwrite, nonatomic) NSUInteger strideInX;
/// The scale that maps `y`-coordinate of the destination to `y`-coordinate of the source.
///
/// Source `y`-coordinate, `sy` is computed from destination `y`-coordinate, `dy` as `sy = strideInY*dy`.
/// Default value is 1.
@property (readwrite, nonatomic) NSUInteger strideInY;
/// The amount by which the weights tensor expands in the `x`-direction.
///
/// The weights tensor is dilated by inserting `dilationRateInX-1` zeros between consecutive values in `x`-dimension.
/// Dilated weights tensor width is `(dilationRateInX-1)*kernelWidth+1`.
/// Default value is 1.
@property (readwrite, nonatomic) NSUInteger dilationRateInX;
/// The amount by which the weights tensor expands in the `y`-direction.
///
/// The weights tensor is dilated by inserting `dilationRateInY-1` zeros between consecutive values in `y`-dimension.
/// Dilated weights tensor width is `(dilationRateInY-1)*kernelHeight+1`.
/// Default value is 1.
@property (readwrite, nonatomic) NSUInteger dilationRateInY;
/// The number of zeros added on the left side of the source tensor.
@property (readwrite, nonatomic) NSUInteger paddingLeft;
/// The number of zeros added on the right side of the source tensor.
@property (readwrite, nonatomic) NSUInteger paddingRight;
/// The number of zeros added at the top of the source tensor.
@property (readwrite, nonatomic) NSUInteger paddingTop;
/// The number of zeros added at the bottom of the source tensor.
@property (readwrite, nonatomic) NSUInteger paddingBottom;
/// The type of padding applied to the source tensor.
///
/// If paddingStyle is `MPSGraphPaddingStyleExplicit`, `paddingLeft`, `laddingRight`, `paddingTop`,
/// and `paddingBottom` must to be specified. For all other padding styles, framework compute these values so you dont need to provide these values.
@property (readwrite, nonatomic) MPSGraphPaddingStyle paddingStyle;
/// The named layout of data in the source tensor.
///
/// It defines the order of named dimensions (Batch, Channel, Height, Width). The convolution operation uses this to interpret data in the source tensor.
/// For example, if `dataLayout` is `MPSGraphTensorNamedDataLayoutNCHW`, frameork interprets data in source tensor as `batch x channels x height x width`
/// with `width` as fastest moving dimension.
@property (readwrite, nonatomic) MPSGraphTensorNamedDataLayout dataLayout;
/// The named layout of data in the weights tensor.
///
/// It defines the order of named dimensions (Output channels, Input channels, Kernel height, Kernel width). The convolution operation uses this to interpret data in the weights tensor.
/// For example, if `weightsLayout` is `MPSGraphTensorNamedDataLayoutOIHW`, frameork interprets data in weights tensor as `outputChannels x inputChannels x kernelHeight x kernelWidth`
/// with `kernelWidth` as fastest moving dimension.
@property (readwrite, nonatomic) MPSGraphTensorNamedDataLayout weightsLayout;
/// The number of partitions of the input and output channels.
///
/// The convolution operation divides input and output channels in `groups` partitions.
/// input channels in a group or partition are only connected to output channels in corresponding group.
/// Number of weights the convolution needs is `outputFeatureChannels x inputFeatureChannels/groups x kernelWidth x kernelHeight`
@property (readwrite, nonatomic) NSUInteger groups;

/// Creates a convolution descriptor with given values for parameters.
/// - Parameters:
///   - strideInX: See ``strideInX`` property.
///   - strideInY: See ``strideInY`` property.
///   - dilationRateInX: See ``dilationRateInX`` property.
///   - dilationRateInY: See ``dilationRateInY`` property.
///   - groups: See ``groups`` property.
///   - paddingLeft: See ``paddingLeft`` property.
///   - paddingRight: See ``paddingRight`` property.
///   - paddingTop: See ``paddingTop`` property.
///   - paddingBottom: See ``paddingBottom`` property.
///   - paddingStyle: See ``paddingStyle`` property.
///   - dataLayout: See ``dataLayout`` property.
///   - weightsLayout: See ``weightsLayout`` property.
/// - Returns: The `MPSGraphConvolution2DOpDescriptor` on autoreleasepool.
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

/// Creates a convolution descriptor with given values for parameters.
/// - Parameters:
///   - strideInX: See ``strideInX`` property.
///   - strideInY: See ``strideInY`` property.
///   - dilationRateInX: See ``dilationRateInX`` property.
///   - dilationRateInY: See ``dilationRateInY`` property.
///   - groups: See ``groups`` property.
///   - paddingStyle: See ``paddingStyle`` property.
///   - dataLayout: See ``dataLayout`` property.
///   - weightsLayout: See ``weightsLayout`` property.
/// - Returns: The `MPSGraphConvolution2DOpDescriptor` on autoreleasepool.
+(nullable instancetype) descriptorWithStrideInX:(NSUInteger) strideInX
                                       strideInY:(NSUInteger) strideInY
                                 dilationRateInX:(NSUInteger) dilationRateInX
                                 dilationRateInY:(NSUInteger) dilationRateInY
                                          groups:(NSUInteger) groups
                                    paddingStyle:(MPSGraphPaddingStyle) paddingStyle
                                      dataLayout:(MPSGraphTensorNamedDataLayout) dataLayout
                                   weightsLayout:(MPSGraphTensorNamedDataLayout) weightsLayout;

/// Sets the left, right, top, and bottom padding values.
/// - Parameters:
///   - paddingLeft: See ``paddingLeft`` property.
///   - paddingRight: See ``paddingRight`` property.
///   - paddingTop: See ``paddingTop`` property.
///   - paddingBottom: See ``paddingBottom`` property.
-(void) setExplicitPaddingWithPaddingLeft:(NSUInteger) paddingLeft
                             paddingRight:(NSUInteger) paddingRight
                               paddingTop:(NSUInteger) paddingTop
                            paddingBottom:(NSUInteger) paddingBottom;


@end

/// A class that describes the properties of a 3D-convolution operator.
///
/// Use an instance of this class is to add a 3D-convolution operator with desired properties to the graph.
MPS_CLASS_AVAILABLE_STARTING(macos(13.2), ios(16.3), tvos(16.3))
@interface MPSGraphConvolution3DOpDescriptor : MPSGraphObject<NSCopying>

/// The scale that maps`x`-coordinate of destination to `x`-coordinate of source.
///
/// Source `x`-coordinate, `sx` is computed from destination `x`-coordinate, `dx` as `sx = strideInX*dx`.
/// Default value is 1.
@property (readwrite, nonatomic) NSUInteger strideInX;
/// The scale that maps`y`-coordinate of destination to `y`-coordinate of source.
///
/// Source `y`-coordinate, `sy` is computed from destination `y`-coordinate, `dy` as `sy = strideInY*dy`.
/// Default value is 1.
@property (readwrite, nonatomic) NSUInteger strideInY;
/// The scale that maps`z`-coordinate of destination to `z`-coordinate of source.
///
/// Source `z`-coordinate, `sz` is computed from destination `z`-coordinate, `dz` as `sz = strideInZ*dz`.
/// Default value is 1.
@property (readwrite, nonatomic) NSUInteger strideInZ;
/// The amount by which weights tensor expands in the `x`-direction.
///
/// The weights tensor is dilated by inserting `dilationRateInX-1` zeros between consecutive values in `x`-dimension.
/// Dilated weights tensor width is `(dilationRateInX-1)*kernelWidth+1`.
/// Default value is 1.
@property (readwrite, nonatomic) NSUInteger dilationRateInX;
/// The amount by which weights tensor expands in the `y`-direction.
///
/// The weights tensor is dilated by inserting `dilationRateInY-1` zeros between consecutive values in `y`-dimension.
/// Dilated weights tensor width is `(dilationRateInY-1)*kernelHeight+1`.
/// Default value is 1.
@property (readwrite, nonatomic) NSUInteger dilationRateInY;
/// The amount by which weights tensor expands in the `z`-direction.
///
/// The weights tensor is dilated by inserting `dilationRateInZ-1` zeros between consecutive values in `z`-dimension.
/// Dilated weights tensor depth is `(dilationRateInZ-1)*kernelDepth+1`.
/// Default value is 1.
@property (readwrite, nonatomic) NSUInteger dilationRateInZ;
/// The number of zeros added on the left side of the source tensor.
@property (readwrite, nonatomic) NSUInteger paddingLeft;
/// The number of zeros added on the right side of the source tensor.
@property (readwrite, nonatomic) NSUInteger paddingRight;
/// The number of zeros added at the top of the source tensor.
@property (readwrite, nonatomic) NSUInteger paddingTop;
/// The number of zeros added at the bottom of the source tensor.
@property (readwrite, nonatomic) NSUInteger paddingBottom;
/// The number of zeros added at the front of the source tensor.
@property (readwrite, nonatomic) NSUInteger paddingFront;
/// The number of zeros added at the back of the source tensor.
@property (readwrite, nonatomic) NSUInteger paddingBack;
/// The type of padding that is applied to the source tensor.
///
/// If paddingStyle is `MPSGraphPaddingStyleExplicit`, `paddingLeft`, `laddingRight`, `paddingTop`,
/// `paddingBottom`,   `paddingFront` and `paddingBack` must to be specified. For all other padding styles, framework compute these values so you dont need to provide these values.
@property (readwrite, nonatomic) MPSGraphPaddingStyle paddingStyle;
/// The named layout of data in the source tensor.
///
/// It defines the order of named dimensions (Batch, Channel, Depth, Height, Width). The convolution operation uses this to interpret data in the source tensor.
/// For example, if `dataLayout` is `MPSGraphTensorNamedDataLayoutNCDHW`, frameork interprets data in source tensor as `batch x channels x depth x height x width`
/// with `width` as fastest moving dimension.
@property (readwrite, nonatomic) MPSGraphTensorNamedDataLayout dataLayout;
/// The named layout of data in the weights tensor.
///
/// It defines the order of named dimensions (Output channels, Input channels, Kernel depth, Kernel height, Kernel width). The convolution operation uses this to interpret data in the weights tensor.
/// For example, if `weightsLayout` is `MPSGraphTensorNamedDataLayoutOIDHW`, frameork interprets data in weights tensor as `outputChannels x inputChannels x kernelDepth x kernelHeight x kernelWidth`
/// with `kernelWidth` as fastest moving dimension.
@property (readwrite, nonatomic) MPSGraphTensorNamedDataLayout weightsLayout;
/// The number of partitions of the input and output channels.
///
/// The convolution operation divides input and output channels in `groups` partitions.
/// input channels in a group or partition are only connected to output channels in corresponding group.
/// Number of weights the convolution needs is `outputFeatureChannels x inputFeatureChannels/groups x kernelDepth x kernelWidth x kernelHeight`
@property (readwrite, nonatomic) NSUInteger groups;

/// Creates a convolution descriptor with given values for parameters.
/// - Parameters:
///   - strideInX: See ``strideInX`` property.
///   - strideInY: See ``strideInY`` property.
///   - strideInZ: See ``strideInZ`` property.
///   - dilationRateInX: See ``dilationRateInX`` property.
///   - dilationRateInY: See ``dilationRateInY`` property.
///   - dilationRateInZ: See ``dilationRateInZ`` property.
///   - groups: See ``groups`` property.
///   - paddingLeft: See ``paddingLeft`` property.
///   - paddingRight: See ``paddingRight`` property.
///   - paddingTop: See ``paddingTop`` property.
///   - paddingBottom: See ``paddingBottom`` property.
///   - paddingFront: See ``paddingFront`` property.
///   - paddingBack: See ``paddingBack`` property.
///   - paddingStyle: See ``paddingStyle`` property.
///   - dataLayout: See ``dataLayout`` property.
///   - weightsLayout: See ``weightsLayout`` property.
/// - Returns: The `MPSGraphConvolution3DOpDescriptor` on autoreleasepool.
+(nullable instancetype) descriptorWithStrideInX:(NSUInteger) strideInX
                                       strideInY:(NSUInteger) strideInY
                                       strideInZ:(NSUInteger) strideInZ
                                 dilationRateInX:(NSUInteger) dilationRateInX
                                 dilationRateInY:(NSUInteger) dilationRateInY
                                 dilationRateInZ:(NSUInteger) dilationRateInZ
                                          groups:(NSUInteger) groups
                                     paddingLeft:(NSUInteger) paddingLeft
                                    paddingRight:(NSUInteger) paddingRight
                                      paddingTop:(NSUInteger) paddingTop
                                   paddingBottom:(NSUInteger) paddingBottom
                                    paddingFront:(NSUInteger) paddingFront
                                     paddingBack:(NSUInteger) paddingBack
                                    paddingStyle:(MPSGraphPaddingStyle) paddingStyle
                                      dataLayout:(MPSGraphTensorNamedDataLayout) dataLayout
                                   weightsLayout:(MPSGraphTensorNamedDataLayout) weightsLayout;

/// Creates a convolution descriptor with given values for parameters.
/// - Parameters:
///   - strideInX: See ``strideInX`` property.
///   - strideInY: See ``strideInY`` property.
///   - strideInZ: See ``strideInZ`` property.
///   - dilationRateInX: See ``dilationRateInX`` property.
///   - dilationRateInY: See ``dilationRateInY`` property.
///   - dilationRateInZ: See ``dilationRateInZ`` property.
///   - groups: See ``groups`` property.
///   - paddingStyle: See ``paddingStyle`` property.
///   - dataLayout: See ``dataLayout`` property.
///   - weightsLayout: See ``weightsLayout`` property.
/// - Returns: The `MPSGraphConvolution3DOpDescriptor` on autoreleasepool.
+(nullable instancetype) descriptorWithStrideInX:(NSUInteger) strideInX
                                       strideInY:(NSUInteger) strideInY
                                       strideInZ:(NSUInteger) strideInZ
                                 dilationRateInX:(NSUInteger) dilationRateInX
                                 dilationRateInY:(NSUInteger) dilationRateInY
                                 dilationRateInZ:(NSUInteger) dilationRateInZ
                                          groups:(NSUInteger) groups
                                    paddingStyle:(MPSGraphPaddingStyle) paddingStyle
                                      dataLayout:(MPSGraphTensorNamedDataLayout) dataLayout
                                   weightsLayout:(MPSGraphTensorNamedDataLayout) weightsLayout;

/// Sets the left, right, top, bottom, front, and back padding values.
/// - Parameters:
///   - paddingLeft: See ``paddingLeft`` property.
///   - paddingRight: See ``paddingRight`` property.
///   - paddingTop: See ``paddingTop`` property.
///   - paddingBottom: See ``paddingBottom`` property.
///   - paddingFront: See ``paddingFront`` property.
///   - paddingBottom: See ``paddingBottom`` property.
-(void) setExplicitPaddingWithPaddingLeft:(NSUInteger) paddingLeft
                             paddingRight:(NSUInteger) paddingRight
                               paddingTop:(NSUInteger) paddingTop
                            paddingBottom:(NSUInteger) paddingBottom
                             paddingFront:(NSUInteger) paddingFront
                              paddingBack:(NSUInteger) paddingBack;
@end

/// This is a category that defines the methods which can be used to add 2D-convolution operator to the graph with properties described by an instance of `MPSGraphConvolution2DOpDescriptor`.
MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(MPSGraphConvolutionOps)

/// Creates a 2D (forward) convolution operation and returns the result tensor.
///
/// - Parameters:
///   - source: source tensor - must be a rank 4 tensor. The layout is defined by ``descriptor.dataLayout``.
///   - weights: weights tensor, must be rank 4. The layout is defined by ``descriptor.weightsLayout``.
///   - descriptor: Specifies strides, dilation rates, paddings and layouts.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) convolution2DWithSourceTensor:(MPSGraphTensor *) source
                                    weightsTensor:(MPSGraphTensor *) weights
                                       descriptor:(MPSGraphConvolution2DOpDescriptor *) descriptor
                                             name:(NSString * _Nullable) name
MPS_SWIFT_NAME( convolution2D(_:weights:descriptor:name:) );

/// Creates a 2D convolution gradient operation with respect to the source tensor of the forward convolution.
///
/// If `S` is source tensor to forward convolution, `R` is the result/returned tensor from forward convolution,
/// and `L` is the loss function, `convolution2DDataGradientWithIncomingGradientTensor` returns tensor `dL/dS = dL/dR * dR/dS`,
/// where `dL/dR` is the incomingGradient parameter.
///
/// - Parameters:
///   - incomingGradient: Incoming loss gradient tensor
///   - weights: Forward pass weights tensor
///   - outputShape: Shape of the forward pass source tensor
///   - forwardConvolutionDescriptor: Forward convolution 2D op ``descriptor``
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) convolution2DDataGradientWithIncomingGradientTensor:(MPSGraphTensor *) incomingGradient
                                                          weightsTensor:(MPSGraphTensor *) weights
                                                            outputShape:(MPSShape *) outputShape
                                           forwardConvolutionDescriptor:(MPSGraphConvolution2DOpDescriptor *) forwardConvolutionDescriptor
                                                                   name:(NSString * _Nullable) name
MPS_SWIFT_NAME( convolution2DDataGradient(_:weights:outputShape:forwardConvolutionDescriptor:name:) );

/// Creates a 2D convolution gradient operation with respect to the source tensor of the forward convolution.
///
/// If `S` is source tensor to forward convolution, `R` is the result/returned tensor of forward convolution,
/// and `L` is the loss function, convolution2DDataGradientWithIncomingGradientTensor returns tensor `dL/dS = dL/dR * dR/dS`,
/// where `dL/dR` is the incomingGradient parameter.
///
/// - Parameters:
///   - incomingGradient: Incoming loss gradient tensor
///   - weights: Forward pass weights tensor
///   - outputShapeTensor: 4D Int32 or Int64 tensor. Shape of the forward pass source tensor
///   - forwardConvolutionDescriptor: Forward convolution 2D op ``descriptor``
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) convolution2DDataGradientWithIncomingGradientTensor:(MPSGraphTensor *) gradient
                                                          weightsTensor:(MPSGraphTensor *) weights
                                                      outputShapeTensor:(MPSGraphTensor *) outputShapeTensor
                                           forwardConvolutionDescriptor:(MPSGraphConvolution2DOpDescriptor *) forwardConvolutionDescriptor
                                                                   name:(NSString * _Nullable) name
MPS_CLASS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
MPS_SWIFT_NAME( convolution2DDataGradient(_:weights:outputShapeTensor:forwardConvolutionDescriptor:name:) );

/// Creates a 2D convolution gradient operation with respect to the weights tensor of the forward convolution.
///
/// If `W` is weights tensor to forward convolution, `R` is the result/returned tensor of forward convolution,
/// and `L` is the loss function, convolution2DWeightsGradientWithIncomingGradientTensor returns tensor `dL/dW = dL/dR * dR/dW`,
/// where `dL/dR` is the incomingGradient parameter.
///
/// - Parameters:
///   - incomingGradient: Incoming loss gradient tensor
///   - weights: Forward pass weights tensor
///   - outputShape: Shape of the forward pass source tensor
///   - forwardConvolutionDescriptor: Forward convolution 2D op ``descriptor``
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) convolution2DWeightsGradientWithIncomingGradientTensor:(MPSGraphTensor *) incomingGradient
                                                              sourceTensor:(MPSGraphTensor *) source
                                                               outputShape:(MPSShape *) outputShape
                                              forwardConvolutionDescriptor:(MPSGraphConvolution2DOpDescriptor *) forwardConvolutionDescriptor
                                                                      name:(NSString * _Nullable) name
MPS_SWIFT_NAME( convolution2DWeightsGradient(_:source:outputShape:forwardConvolutionDescriptor:name:) );


/// Creates a 2D convolution gradient operation with respect to weights tensor of forward convolution.
///
/// If `W` is weights tensor to forward convolution, `R` is the result/returned tensor of forward convolution,
/// and `L` is the loss function, convolution2DWeightsGradientWithIncomingGradientTensor returns tensor `dL/dW = dL/dR * dR/dW`,
/// where `dL/dR` is the incomingGradient parameter.
///
/// - Parameters:
///   - incomingGradient: Incoming loss gradient tensor
///   - weights: Forward pass weights tensor
///   - outputShapeTensor: 4D int32 or Int64 Tensor. Shape of the forward pass source tensor
///   - forwardConvolutionDescriptor: Forward convolution 2D op ``descriptor``
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) convolution2DWeightsGradientWithIncomingGradientTensor:(MPSGraphTensor *) gradient
                                                              sourceTensor:(MPSGraphTensor *) source
                                                         outputShapeTensor:(MPSGraphTensor *) outputShapeTensor
                                              forwardConvolutionDescriptor:(MPSGraphConvolution2DOpDescriptor *) forwardConvolutionDescriptor
                                                                      name:(NSString * _Nullable) name
MPS_CLASS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
MPS_SWIFT_NAME( convolution2DWeightsGradient(_:source:outputShapeTensor:forwardConvolutionDescriptor:name:) );


/// Creates a 3D forward convolution operation and returns the result tensor.
///
/// - Parameters:
///   - source: source tensor - must be of rank 5. The layout is defined by ``descriptor.dataLayout``.
///   - weights: weights tensor, must be rank 5. The layout is defined by ``descriptor.weightsLayout``.
///   - descriptor: Specifies strides, dilation rates, paddings and layouts.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) convolution3DWithSourceTensor:(MPSGraphTensor *) source
                                    weightsTensor:(MPSGraphTensor *) weights
                                       descriptor:(MPSGraphConvolution3DOpDescriptor *) descriptor
                                             name:(NSString * _Nullable) name
MPS_CLASS_AVAILABLE_STARTING(macos(13.2), ios(16.3), tvos(16.3))
MPS_SWIFT_NAME( convolution3D(_:weights:descriptor:name:) );

/// Creates a 3D convolution gradient operation with respect to the source tensor of the forward convolution.
///
/// If `S` is source tensor to forward convolution, `R` is the result/returned tensor of forward convolution,
/// and `L` is the loss function, convolution3DDataGradientWithIncomingGradientTensor returns tensor `dL/dS = dL/dR * dR/dS`,
/// where `dL/dR` is the incomingGradient parameter.
///
/// - Parameters:
///   - incomingGradient: Incoming loss gradient tensor
///   - weights: Forward pass weights tensor
///   - outputShape: Shape of the forward pass source tensor
///   - forwardConvolutionDescriptor: Forward convolution 2D op ``descriptor``
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) convolution3DDataGradientWithIncomingGradientTensor:(MPSGraphTensor *) incomingGradient
                                                          weightsTensor:(MPSGraphTensor *) weights
                                                            outputShape:(MPSShape *) outputShape
                                           forwardConvolutionDescriptor:(MPSGraphConvolution3DOpDescriptor *) forwardConvolutionDescriptor
                                                                   name:(NSString * _Nullable) name
MPS_CLASS_AVAILABLE_STARTING(macos(13.2), ios(16.3), tvos(16.3))
MPS_SWIFT_NAME( convolution3DDataGradient(_:weights:outputShape:forwardConvolutionDescriptor:name:) );

/// Creates a 3D convolution gradient operation with respect to the source tensor of the forward convolution.
///
/// If `S` is source tensor to forward convolution, `R` is the result/returned tensor of forward convolution,
/// and `L` is the loss function, convolution3DDataGradientWithIncomingGradientTensor returns tensor `dL/dS = dL/dR * dR/dS`,
/// where `dL/dR` is the incomingGradient parameter.
///
/// - Parameters:
///   - incomingGradient: Incoming loss gradient tensor
///   - weights: Forward pass weights tensor
///   - outputShapeTensor: 4D Int32 or Int64 tensor. Shape of the forward pass source tensor
///   - forwardConvolutionDescriptor: Forward convolution 2D op ``descriptor``
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) convolution3DDataGradientWithIncomingGradientTensor:(MPSGraphTensor *) gradient
                                                          weightsTensor:(MPSGraphTensor *) weights
                                                      outputShapeTensor:(MPSGraphTensor *) outputShapeTensor
                                           forwardConvolutionDescriptor:(MPSGraphConvolution3DOpDescriptor *) forwardConvolutionDescriptor
                                                                   name:(NSString * _Nullable) name
MPS_CLASS_AVAILABLE_STARTING(macos(13.2), ios(16.3), tvos(16.3))
MPS_SWIFT_NAME( convolution3DDataGradient(_:weights:outputShapeTensor:forwardConvolutionDescriptor:name:) );

/// Creates a 3D convolution gradient operation with respect to the weights tensor of the forward convolution.
///
/// If `W` is weights tensor to forward convolution, `R` is the result/returned tensor of forward convolution,
/// and `L` is the loss function, convolution3DWeightsGradientWithIncomingGradientTensor returns tensor `dL/dW = dL/dR * dR/dW`,
/// where `dL/dR` is the incomingGradient parameter.
///
/// - Parameters:
///   - incomingGradient: Incoming loss gradient tensor
///   - weights: Forward pass weights tensor
///   - outputShape: Shape of the forward pass source tensor
///   - forwardConvolutionDescriptor: Forward convolution 2D op ``descriptor``
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) convolution3DWeightsGradientWithIncomingGradientTensor:(MPSGraphTensor *) incomingGradient
                                                              sourceTensor:(MPSGraphTensor *) source
                                                               outputShape:(MPSShape *) outputShape
                                              forwardConvolutionDescriptor:(MPSGraphConvolution3DOpDescriptor *) forwardConvolutionDescriptor
                                                                      name:(NSString * _Nullable) name
MPS_CLASS_AVAILABLE_STARTING(macos(13.2), ios(16.3), tvos(16.3))
MPS_SWIFT_NAME( convolution3DWeightsGradient(_:source:outputShape:forwardConvolutionDescriptor:name:) );

/// Creates a 3D convolution gradient operation with respect to the weights tensor of the forward convolution.
/// 
/// If `W` is weights tensor to forward convolution, `R` is the result/returned tensor of forward convolution,
/// and `L` is the loss function, convolution3DWeightsGradientWithIncomingGradientTensor returns tensor `dL/dW = dL/dR * dR/dW`,
/// where `dL/dR` is the incomingGradient parameter.
///
/// - Parameters:
///   - incomingGradient: Incoming loss gradient tensor
///   - weights: Forward pass weights tensor
///   - outputShapeTensor: 4D int32 or Int64 Tensor. Shape of the forward pass source tensor
///   - forwardConvolutionDescriptor: Forward convolution 2D op ``descriptor``
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) convolution3DWeightsGradientWithIncomingGradientTensor:(MPSGraphTensor *) gradient
                                                              sourceTensor:(MPSGraphTensor *) source
                                                         outputShapeTensor:(MPSGraphTensor *) outputShapeTensor
                                              forwardConvolutionDescriptor:(MPSGraphConvolution3DOpDescriptor *) forwardConvolutionDescriptor
                                                                      name:(NSString * _Nullable) name
MPS_CLASS_AVAILABLE_STARTING(macos(13.2), ios(16.3), tvos(16.3))
MPS_SWIFT_NAME( convolution3DWeightsGradient(_:source:outputShapeTensor:forwardConvolutionDescriptor:name:) );

@end

NS_ASSUME_NONNULL_END

#endif /* MPSGraphConvolutionOps_h */
