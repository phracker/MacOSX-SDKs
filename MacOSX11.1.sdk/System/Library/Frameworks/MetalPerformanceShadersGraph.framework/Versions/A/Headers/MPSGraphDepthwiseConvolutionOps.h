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
MPS_SWIFT_NAME( depthwiseConvolution2DWeightsGradient(_:source:outputShape:descriptor:name:) );

@end

NS_ASSUME_NONNULL_END


#endif /* MPSGraphDepthwiseConvolutionOps_h */
