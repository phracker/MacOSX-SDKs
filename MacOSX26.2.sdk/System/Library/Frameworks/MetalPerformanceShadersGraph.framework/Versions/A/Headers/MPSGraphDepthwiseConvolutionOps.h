//
//  MPSGraphDepthwiseConvolutionOps.h
//  MPSGraph
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#ifndef MPSGraphDepthwiseConvolutionOps_h
#define MPSGraphDepthwiseConvolutionOps_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

/// A class that defines the parameters for  a 2D-depthwise convolution operation.
///
/// An `MPSGraphDepthwiseConvolution2DOpDescriptor` defines constant parameters for 2D-depthwise convolutions.
/// Use this class with ``MPSGraph/depthwiseConvolution2DWithSourceTensor:weightsTensor:descriptor:name:``,
/// ``MPSGraph/depthwiseConvolution2DDataGradientWithIncomingGradientTensor:weightsTensor:outputShape:descriptor:name:``,
/// and ``MPSGraph/depthwiseConvolution2DWeightsGradientWithIncomingGradientTensor:sourceTensor:outputShape:descriptor:name:``
/// methods.
MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraphDepthwiseConvolution2DOpDescriptor : MPSGraphObject<NSCopying>

/// The stride for the x dimension. 
///
/// Default value: 1.
@property (readwrite, nonatomic) NSUInteger strideInX;
/// The stride for the y dimension. 
///
/// Default value: 1.
@property (readwrite, nonatomic) NSUInteger strideInY;
/// The dilation rate for the x dimension. 
///
/// Default value: 1.
@property (readwrite, nonatomic) NSUInteger dilationRateInX;
/// The dilation rate for the y dimension. 
///
/// Default value: 1.
@property (readwrite, nonatomic) NSUInteger dilationRateInY;


/// The explicit padding value for the x dimension the operation adds before the data. 
///
/// Default value: 0.
@property (readwrite, nonatomic) NSUInteger paddingLeft;
/// The explicit padding value for the x dimension operation adds after the data. 
///
/// Default value: 0.
@property (readwrite, nonatomic) NSUInteger paddingRight;
/// The explicit padding value for the y dimension operation adds before the data. 
///
/// Default value: 0.
@property (readwrite, nonatomic) NSUInteger paddingTop;
/// The explicit padding value for the y dimension operation adds after the data. 
///
/// Default value: 0.
@property (readwrite, nonatomic) NSUInteger paddingBottom;

/// The padding style for the operation. 
///
/// Default value is `MPSGraphPaddingStyleExplicit`.
@property (readwrite, nonatomic) MPSGraphPaddingStyle paddingStyle;
/// The data layout of the input data in the forward pass.
///
/// See: ``MPSGraphTensorNamedDataLayout``.
@property (readwrite, nonatomic) MPSGraphTensorNamedDataLayout dataLayout;
/// The data layout of the weights.
///
/// NOTE: 'O' index is channel multiplier index. See: ``MPSGraphTensorNamedDataLayout``.
@property (readwrite, nonatomic) MPSGraphTensorNamedDataLayout weightsLayout;

/// Creates a 2D-depthwise convolution descriptor with given values.
///
/// - Parameters:
///   - strideInX: See `strideInX` property.
///   - strideInY: See `strideInY` property.
///   - dilationRateInX: See `dilationRateInX` property.
///   - dilationRateInY: See `dilationRateInY` property.
///   - paddingLeft: See `paddingLeft` property.
///   - paddingRight: See `paddingRight` property.
///   - paddingTop: See `paddingTop` property.
///   - paddingBottom: See `paddingBottom` property.
///   - paddingStyle: See `paddingStyle` property.
///   - dataLayout: See `dataLayout` property.
///   - weightsLayout: See `weightsLayout` property.
/// - Returns: The descriptor on autoreleasepool.
+(nullable instancetype) descriptorWithStrideInX:(NSUInteger) strideInX
                                       strideInY:(NSUInteger) strideInY
                                 dilationRateInX:(NSUInteger) dilationRateInX
                                 dilationRateInY:(NSUInteger) dilationRateInY
                                     paddingLeft:(NSUInteger) paddingLeft
                                    paddingRight:(NSUInteger) paddingRight
                                      paddingTop:(NSUInteger) paddingTop
                                   paddingBottom:(NSUInteger) paddingBottom
                                    paddingStyle:(MPSGraphPaddingStyle) paddingStyle
                                      dataLayout:(MPSGraphTensorNamedDataLayout) dataLayout
                                   weightsLayout:(MPSGraphTensorNamedDataLayout) weightsLayout;

/// Creates a 2D-depthwise convolution descriptor with given properties and default values.
///
/// - Parameters:
///   - dataLayout: See `dataLayout` property.
///   - weightsLayout: See `weightsLayout` property.
/// - Returns: The descriptor on autoreleasepool.
+(nullable instancetype) descriptorWithDataLayout:(MPSGraphTensorNamedDataLayout) dataLayout
                                    weightsLayout:(MPSGraphTensorNamedDataLayout) weightsLayout;

/// Sets the explicit padding values.
///
/// Note: this method also sets `paddingStyle` to `MPSGraphPaddingStyleExplicit` (see ``MPSGraphPaddingStyle``).
///
/// - Parameters:
///   - paddingLeft: See `paddingLeft` property.
///   - paddingRight: See `paddingRight` property.
///   - paddingTop: See `paddingTop` property.
///   - paddingBottom: See `paddingBottom` property.
-(void) setExplicitPaddingWithPaddingLeft:(NSUInteger) paddingLeft
                             paddingRight:(NSUInteger) paddingRight
                               paddingTop:(NSUInteger) paddingTop
                            paddingBottom:(NSUInteger) paddingBottom;
@end


/// The class that defines the parameters for a 3D-depthwise convolution operation.
///
/// A `MPSGraphDepthwiseConvolution3DOpDescriptor` defines constant parameters for 3D depthwise convolutions.
/// Use this class with ``MPSGraph/depthwiseConvolution3DWithSourceTensor:weightsTensor:descriptor:name:``,
/// ``MPSGraph/depthwiseConvolution3DDataGradientWithIncomingGradientTensor:weightsTensor:outputShape:descriptor:name:``
/// and ``MPSGraph/depthwiseConvolution3DWeightsGradientWithIncomingGradientTensor:sourceTensor:outputShape:descriptor:name:``
/// methods.
MPS_CLASS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
@interface MPSGraphDepthwiseConvolution3DOpDescriptor : MPSGraphObject<NSCopying>

/// The strides for spatial dimensions.
///
/// Must be three numbers, one for each spatial dimension, fastest running index last.
/// Default value: `@[ @1, @1, @1 ]`
@property (readwrite, nonatomic, copy) NSArray<NSNumber *> * _Nonnull   strides;

/// The dilation rates for spatial dimensions.
///
/// Must be three numbers, one for each spatial dimension, fastest running index last.
/// Default value: `@[ @1, @1, @1 ]`
@property (readwrite, nonatomic, copy) NSArray<NSNumber *> * _Nonnull   dilationRates;

/// The padding values for spatial dimensions.
///
/// Must be six numbers, two for each spatial dimension.
/// For example `paddingValues[0]` defines the explicit padding
/// amount before the first spatial dimension (slowest running index of spatial dimensions), 
/// `paddingValues[1]` defines the padding amount after the first spatial dimension etc.
/// Use only with `paddingStyle = MPSGraphPaddingStyleExplicit`.
/// Default value: `@[ @0, @0, @0, @0, @0, @0 ]`
@property (readwrite, nonatomic, copy) NSArray<NSNumber *> * _Nonnull   paddingValues;

/// The padding style for the operation. 
///
/// Default value: `MPSGraphPaddingStyleExplicit`.
@property (readwrite, nonatomic) MPSGraphPaddingStyle paddingStyle;

/// The axis that contains the channels in the input and the weights, within
/// the 4D tile of the last dimensions.
///
/// For example the value of `-1` corresponds to `NDHWC`, `NHWC` layouts. This allows the placement
/// of the channel index anywhere within the last 4 dimensions of the tensor. In case your
/// weights are in a different layout you can bring them to the same layout
/// as inputs using transposes or permutations.
/// Default value: `-4`, corresponds to `NCDHW` and `CDHW` layouts.
@property (readwrite, nonatomic) NSInteger channelDimensionIndex;

/// Creates a 3D depthwise convolution descriptor with given values.
///
/// - Parameters:
///   - strides: See `strides` property.
///   - dilationRates: See `dilationRates` property.
///   - paddingValues: See `paddingValues` property.
///   - paddingStyle: See `paddingStyle` property.
/// - Returns: The descriptor on autoreleasepool.
+(nullable instancetype) descriptorWithStrides:(NSArray<NSNumber *> * _Nonnull) strides
                                 dilationRates:(NSArray<NSNumber *> * _Nonnull) dilationRates
                                 paddingValues:(NSArray<NSNumber *> * _Nonnull) paddingValues
                                  paddingStyle:(MPSGraphPaddingStyle) paddingStyle;

/// Creates a 3D depthwise convolution descriptor with default values.
///
/// - Parameters:
///   - paddingStyle: See `paddingStyle` property.
/// - Returns: The descriptor on autoreleasepool.
+(nullable instancetype) descriptorWithPaddingStyle:(MPSGraphPaddingStyle) paddingStyle;

@end

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(MPSGraphDepthwiseConvolutionOps)

/// Creates a 2D-depthwise convolution operation and returns the result tensor.
///
/// - Parameters:
///   - source: A 2D Image source as tensor - must be of rank=4. The layout is defined by `descriptor.dataLayout`.
///   - weights: The weights tensor, must be rank=4. The layout is defined by `descriptor.weightsLayout`.
///   - descriptor: The descriptor object that specifies strides, dilation rates, paddings and layouts.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) depthwiseConvolution2DWithSourceTensor:(MPSGraphTensor *) source
                                             weightsTensor:(MPSGraphTensor *) weights
                                                descriptor:(MPSGraphDepthwiseConvolution2DOpDescriptor *) descriptor
                                                      name:(NSString * _Nullable) name
MPS_SWIFT_NAME( depthwiseConvolution2D(_:weights:descriptor:name:) );

/// Creates a 2D-depthwise convolution gradient for data operation and returns the result tensor.
///
/// - Parameters:
///   - incomingGradient: A 2D input gradient tensor - must be of rank=4. The layout is defined by `descriptor.dataLayout`.
///   - weights: The weights tensor, must be rank=4. The layout is defined by `descriptor.weightsLayout`.
///   - outputShape: The shape of the οutput tensor (and therefore input tensor of forward pass).
///   - descriptor: The descriptor object that specifies strides, dilation rates, paddings and layouts.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) depthwiseConvolution2DDataGradientWithIncomingGradientTensor:(MPSGraphTensor *) incomingGradient
                                                                   weightsTensor:(MPSGraphTensor *) weights
                                                                     outputShape:(MPSShape *) outputShape
                                                                      descriptor:(MPSGraphDepthwiseConvolution2DOpDescriptor *) descriptor
                                                                            name:(NSString * _Nullable) name
MPS_SWIFT_NAME( depthwiseConvolution2DDataGradient(_:weights:outputShape:descriptor:name:) );

/// Creates a 2D-depthwise convolution gradient for weights operation and returns the result tensor.
///
/// - Parameters:
///   - incomingGradient: A 2D input gradient tensor - must be of rank=4. The layout is defined by `descriptor.dataLayout`.
///   - source: A 2D Image source as tensor - must be of rank=4. The layout is defined by `descriptor.dataLayout`.
///   - outputShape: The shape of the οutput tensor (and therefore weight tensor of forward pass).
///   - descriptor: The descriptor object that specifies strides, dilation rates, paddings and layouts.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) depthwiseConvolution2DWeightsGradientWithIncomingGradientTensor:(MPSGraphTensor *) incomingGradient
                                                                       sourceTensor:(MPSGraphTensor *) source
                                                                        outputShape:(MPSShape *) outputShape
                                                                         descriptor:(MPSGraphDepthwiseConvolution2DOpDescriptor *) descriptor
                                                                               name:(NSString * _Nullable) name
MPS_SWIFT_NAME( depthwiseConvolution2DWeightsGradient(_:source:outputShape:descriptor:name:));

#pragma mark - 3D Depthwise convolution

/// Creates a 3D depthwise convolution operation and returns the result tensor.
///
/// Works exactly like depthwise convolution2D, but in three dimensions. Supports different layouts with
/// the ``MPSGraphDepthwiseConvolution3DOpDescriptor/channelDimensionIndex`` property.
/// If your weights need a different layout add a permute operation on them before this operation.
///
/// - Parameters:
///   - source: A 3D Image source as tensor - must be at least rank=4 (CDHW when channelDimensionIndex = -4).
///   - weights: The weights tensor, must be rank=4 - axes are interpreted as CDHW when channelDimensionIndex = -4 .
///   - descriptor: The descriptor object that specifies strides, dilation rates and paddings.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) depthwiseConvolution3DWithSourceTensor:(MPSGraphTensor *) source
                                             weightsTensor:(MPSGraphTensor *) weights
                                                descriptor:(MPSGraphDepthwiseConvolution3DOpDescriptor* _Nonnull) descriptor
                                                      name:(NSString * _Nullable) name
MPS_SWIFT_NAME( depthwiseConvolution3D(_:weights:descriptor:name:))
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/// Creates a 3D depthwise convolution gradient for data operation and returns the result tensor.
///
/// - Parameters:
///   - incomingGradient: A 3D input gradient tensor - must be at least rank=4 (CDHW).
///   - weights: The weights tensor, must be rank=4 - axes are interpreted as CDHW.
///   - outputShape: The shape of the οutput tensor (and therefore input tensor of forward pass).
///   - descriptor: The descriptor object that  specifies strides, dilation rates and paddings.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) depthwiseConvolution3DDataGradientWithIncomingGradientTensor:(MPSGraphTensor *) incomingGradient
                                                                   weightsTensor:(MPSGraphTensor *) weights
                                                                     outputShape:(MPSShape * _Nullable) outputShape
                                                                      descriptor:(MPSGraphDepthwiseConvolution3DOpDescriptor* _Nonnull) descriptor
                                                                            name:(NSString * _Nullable) name
MPS_SWIFT_NAME( depthwiseConvolution3DDataGradient(_:weights:outputShape:descriptor:name:))
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/// Creates a 3D depthwise convolution gradient for weights operation and returns the result tensor.
///
/// - Parameters:
///   - incomingGradient: A 3D input gradient tensor - must be at least rank=4 (NCDHW).
///   - source: The forward pass 3D Image source as tensor - must be at least rank=4 (NCDHW).
///   - outputShape: The shape of the οutput tensor (and therefore weight tensor of forward pass).
///   - descriptor: The descriptor object that specifies strides, dilation rates and paddings.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) depthwiseConvolution3DWeightsGradientWithIncomingGradientTensor:(MPSGraphTensor *) incomingGradient
                                                                       sourceTensor:(MPSGraphTensor *) source
                                                                        outputShape:(MPSShape *) outputShape
                                                                         descriptor:(MPSGraphDepthwiseConvolution3DOpDescriptor *) descriptor
                                                                               name:(NSString * _Nullable) name
MPS_SWIFT_NAME( depthwiseConvolution3DWeightsGradient(_:source:outputShape:descriptor:name:));

@end

NS_ASSUME_NONNULL_END


#endif /* MPSGraphDepthwiseConvolutionOps_h */
