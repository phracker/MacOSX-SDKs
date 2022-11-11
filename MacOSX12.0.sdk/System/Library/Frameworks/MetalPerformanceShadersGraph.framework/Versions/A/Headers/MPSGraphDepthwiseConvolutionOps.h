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

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraphDepthwiseConvolution2DOpDescriptor : NSObject<NSCopying>

@property (readwrite, nonatomic) NSUInteger strideInX;          //!< Default = 1
@property (readwrite, nonatomic) NSUInteger strideInY;          //!< Default = 1
@property (readwrite, nonatomic) NSUInteger dilationRateInX;    //!< Default = 1
@property (readwrite, nonatomic) NSUInteger dilationRateInY;    //!< Default = 1

@property (readwrite, nonatomic) NSUInteger paddingLeft;        //!< Default = 0 - ignored if paddingStyle != explicit
@property (readwrite, nonatomic) NSUInteger paddingRight;       //!< Default = 0 - ignored if paddingStyle != explicit
@property (readwrite, nonatomic) NSUInteger paddingTop;         //!< Default = 0 - ignored if paddingStyle != explicit
@property (readwrite, nonatomic) NSUInteger paddingBottom;      //!< Default = 0 - ignored if paddingStyle != explicit

@property (readwrite, nonatomic) MPSGraphPaddingStyle paddingStyle; //!< Default = MPSGraphPaddingStyleExplicit
@property (readwrite, nonatomic) MPSGraphTensorNamedDataLayout dataLayout;
@property (readwrite, nonatomic) MPSGraphTensorNamedDataLayout weightsLayout; //!< NOTE: 'O' index is channel multiplier index


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

+(nullable instancetype) descriptorWithDataLayout:(MPSGraphTensorNamedDataLayout) dataLayout
                                    weightsLayout:(MPSGraphTensorNamedDataLayout) weightsLayout;

-(void) setExplicitPaddingWithPaddingLeft:(NSUInteger) paddingLeft
                             paddingRight:(NSUInteger) paddingRight
                               paddingTop:(NSUInteger) paddingTop
                            paddingBottom:(NSUInteger) paddingBottom;
@end


/*!
 *  @class      MPSGraphDepthwiseConvolution3DOpDescriptor
 *  @abstract   Defines a 3d depthwise convolution operation
 */
MPS_CLASS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
@interface MPSGraphDepthwiseConvolution3DOpDescriptor : NSObject<NSCopying>

/*!
 *  @property   strides
 *  @discussion Must be three numbers, one for each spatial dimension, fastest running index last.
 *              Default value: @code @[ @1, @1, @1 ] @endcode
 */
@property (readwrite, nonatomic, copy) NSArray<NSNumber *> * _Nonnull   strides;

/*!
 *  @property   dilationRates
 *  @discussion Must be three numbers, one for each spatial dimension, fastest running index last.
 *              Default value: @code @[ @1, @1, @1 ] @endcode
 */
@property (readwrite, nonatomic, copy) NSArray<NSNumber *> * _Nonnull   dilationRates;

/*!
 *  @property   paddingValues
 *  @discussion Must be six numbers, two for each spatial dimension. `paddingValues[0]` defines the explicit padding
 *              amount before the first spatial dimension (slowest running index of spatial dimensions),
 *              `paddingValues[1]` defines the padding amount after the first spatial dimension etc.
 *              Used only when `paddingStyle = MPSGraphPaddingStyleExplicit`.
 *              Default value: @code @[ @0, @0, @0, @0, @0, @0 ] @endcode
 */
@property (readwrite, nonatomic, copy) NSArray<NSNumber *> * _Nonnull   paddingValues;

/*!
 *  @property   paddingStyle
 *  @discussion Defines what kind of padding to apply to operation.
 *              Default value: @code MPSGraphPaddingStyleExplicit @endcode
 */
@property (readwrite, nonatomic) MPSGraphPaddingStyle paddingStyle;

/*!
 *  @property   channelDimensionIndex
 *  @discussion Defines which axis contains the channels in the input and the weights, within
 *              the 4d tile of the last dimensions. For example the value of @code -1 @endcode
 *              corresponds to @code NDHWC, NHWC @endcode layouts. This allows the placement
 *              of the channel index anywhere within the last 4 dimensions of the tensor. In case the
 *              weights are in a different layout it is recommended to bring them to the same layout
 *              as inputs using transposes or permutations.
 *              Default value: @code -4 @endcode, corresponds to @code NCDHW @endcode
 *              and @code CDHW @endcode layouts.
 */
@property (readwrite, nonatomic) NSInteger channelDimensionIndex;
/*!
 *  @abstract   Creates a 3d depthwise convolution descriptor with given values.
 *  @param      strides                 See corresponding property above.
 *  @param      dilationRates    See corresponding property above.
 *  @param      paddingValues    See corresponding property above.
 *  @param      paddingStyle      See corresponding property above.
 *  @return     The descriptor on autoreleasepool.
 */
+(nullable instancetype) descriptorWithStrides:(NSArray<NSNumber *> * _Nonnull) strides
                                 dilationRates:(NSArray<NSNumber *> * _Nonnull) dilationRates
                                 paddingValues:(NSArray<NSNumber *> * _Nonnull) paddingValues
                                  paddingStyle:(MPSGraphPaddingStyle) paddingStyle;

/*!
 *  @abstract   Creates a 3d depthwise convolution descriptor with default values.
 *  @param      paddingStyle      See corresponding property above.
 *  @return     The descriptor on autoreleasepool.
 */
+(nullable instancetype) descriptorWithPaddingStyle:(MPSGraphPaddingStyle) paddingStyle;

@end

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(MPSGraphDepthwiseConvolutionOps)


-(MPSGraphTensor *) depthwiseConvolution2DWithSourceTensor:(MPSGraphTensor *) source
                                             weightsTensor:(MPSGraphTensor *) weights
                                                descriptor:(MPSGraphDepthwiseConvolution2DOpDescriptor *) descriptor
                                                      name:(NSString * _Nullable) name
MPS_SWIFT_NAME( depthwiseConvolution2D(_:weights:descriptor:name:) );

-(MPSGraphTensor *) depthwiseConvolution2DDataGradientWithIncomingGradientTensor:(MPSGraphTensor *) incomingGradient
                                                                   weightsTensor:(MPSGraphTensor *) weights
                                                                     outputShape:(MPSShape *) outputShape
                                                                      descriptor:(MPSGraphDepthwiseConvolution2DOpDescriptor *) descriptor
                                                                            name:(NSString * _Nullable) name
MPS_SWIFT_NAME( depthwiseConvolution2DDataGradient(_:weights:outputShape:descriptor:name:) );

-(MPSGraphTensor *) depthwiseConvolution2DWeightsGradientWithIncomingGradientTensor:(MPSGraphTensor *) incomingGradient
                                                                       sourceTensor:(MPSGraphTensor *) source
                                                                        outputShape:(MPSShape *) outputShape
                                                                         descriptor:(MPSGraphDepthwiseConvolution2DOpDescriptor *) descriptor
                                                                               name:(NSString * _Nullable) name
MPS_SWIFT_NAME( depthwiseConvolution2DWeightsGradient(_:source:outputShape:descriptor:name:));

#pragma mark - 3D Depthwise convolution

/*!
 *  @abstract   Create 3d depthwise convolution operation and return the result tensor.
 *  @discussion Just like depthwise convolution2d, but in three dimensions. Different layouts are supported by using
 *              the @code channelDimensionIndex @endcode property. If your weights need a different layout
 *              add a permute operation on them before this operation.

 *  @param      source              3d Image source as tensor - must be at least rank=4 (CDHW when channelDimensionIndex = -4).
 *  @param      weights             Weights tensor, must be rank=4 - axes are interpreted as CDHW when channelDimensionIndex = -4 .
 *  @param      descriptor      Specifies strides, dilation rates and paddings.
 *  @param      name                    The name for the operation.
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) depthwiseConvolution3DWithSourceTensor:(MPSGraphTensor *) source
                                             weightsTensor:(MPSGraphTensor *) weights
                                                descriptor:(MPSGraphDepthwiseConvolution3DOpDescriptor* _Nonnull) descriptor
                                                      name:(NSString * _Nullable) name
MPS_SWIFT_NAME( depthwiseConvolution3D(_:weights:descriptor:name:))
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/*!
 *  @abstract   Create 3d depthwise convolution gradient for data operation and return the result tensor.

 *  @param      incomingGradient        3d input gradient tensor - must be at least rank=4 (CDHW).
 *  @param      weights                 Weights tenstor, must be rank=4 - axes are interpreted as CDHW.
 *  @param      outputShape             Shape of the οutput tensor (and therefore input tensor of forward pass).
 *  @param      descriptor                  Specifies strides, dilation rates and paddings.
 *  @param      name                    The name for the operation (NCDHW).
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) depthwiseConvolution3DDataGradientWithIncomingGradientTensor:(MPSGraphTensor *) incomingGradient
                                                                   weightsTensor:(MPSGraphTensor *) weights
                                                                     outputShape:(MPSShape * _Nullable) outputShape
                                                                      descriptor:(MPSGraphDepthwiseConvolution3DOpDescriptor* _Nonnull) descriptor
                                                                            name:(NSString * _Nullable) name
MPS_SWIFT_NAME( depthwiseConvolution3DDataGradient(_:weights:outputShape:descriptor:name:))
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/*!
 *  @abstract   Create 3d depthwise convolution gradient for weights operation and return the result tensor.

 *  @param      incomingGradient              3d input gradient tensor - must be at least rank=4 (NCDHW).
 *  @param      source             Forward pass 3d Image source as tensor - must be at least rank=4 (NCDHW).
 *  @param      outputShape    Shape of the οutput tensor (and therefore weight tensor of forward pass).
 *  @param      descriptor      Specifies strides, dilation rates and paddings.
 *  @param      name                    The name for the operation (NCDHW).
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) depthwiseConvolution3DWeightsGradientWithIncomingGradientTensor:(MPSGraphTensor *) incomingGradient
                                                                       sourceTensor:(MPSGraphTensor *) source
                                                                        outputShape:(MPSShape *) outputShape
                                                                         descriptor:(MPSGraphDepthwiseConvolution3DOpDescriptor *) descriptor
                                                                               name:(NSString * _Nullable) name
MPS_SWIFT_NAME( depthwiseConvolution3DWeightsGradient(_:source:outputShape:descriptor:name:));

@end

NS_ASSUME_NONNULL_END


#endif /* MPSGraphDepthwiseConvolutionOps_h */
