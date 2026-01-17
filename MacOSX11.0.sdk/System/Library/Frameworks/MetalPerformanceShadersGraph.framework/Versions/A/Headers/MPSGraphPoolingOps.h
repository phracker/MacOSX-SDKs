//
//  MPSGraphPoolingOps.h
//  MetalPerformanceShadersGraph
//
//  Created on 2/4/20.
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#ifndef MPSGraphPoolingOps_h
#define MPSGraphPoolingOps_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraphPooling2DOpDescriptor : NSObject<NSCopying>

/*! @property   groups
 *  @discussion groups of the operation
 */
@property (readwrite, nonatomic) NSUInteger kernelWidth;
@property (readwrite, nonatomic) NSUInteger kernelHeight;

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


+(nullable instancetype) descriptorWithKernelWidth:(NSUInteger) kernelWidth
                                      kernelHeight:(NSUInteger) kernelHeight
                                         strideInX:(NSUInteger) strideInX
                                         strideInY:(NSUInteger) strideInY
                                   dilationRateInX:(NSUInteger) dilationRateInX
                                   dilationRateInY:(NSUInteger) dilationRateInY
                                       paddingLeft:(NSUInteger) paddingLeft
                                      paddingRight:(NSUInteger) paddingRight
                                        paddingTop:(NSUInteger) paddingTop
                                     paddingBottom:(NSUInteger) paddingBottom
                                      paddingStyle:(MPSGraphPaddingStyle) paddingStyle
                                        dataLayout:(MPSGraphTensorNamedDataLayout) dataLayout;

+(nullable instancetype) descriptorWithKernelWidth:(NSUInteger) kernelWidth
                                      kernelHeight:(NSUInteger) kernelHeight
                                         strideInX:(NSUInteger) strideInX
                                         strideInY:(NSUInteger) strideInY
                                      paddingStyle:(MPSGraphPaddingStyle) paddingStyle
                                        dataLayout:(MPSGraphTensorNamedDataLayout) dataLayout;


-(void) setExplicitPaddingWithPaddingLeft:(NSUInteger) paddingLeft
                             paddingRight:(NSUInteger) paddingRight
                               paddingTop:(NSUInteger) paddingTop
                            paddingBottom:(NSUInteger) paddingBottom;

@end

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(MPSGraphPoolingOps)

-(MPSGraphTensor *) maxPooling2DWithSourceTensor:(MPSGraphTensor *) source
                                      descriptor:(MPSGraphPooling2DOpDescriptor *) descriptor
                                            name:(NSString * _Nullable) name;

-(MPSGraphTensor *) maxPooling2DGradientWithGradientTensor:(MPSGraphTensor *) gradient
                                              sourceTensor:(MPSGraphTensor *) source
                                                descriptor:(MPSGraphPooling2DOpDescriptor *) descriptor
                                                      name:(NSString * _Nullable) name;

-(MPSGraphTensor *) avgPooling2DWithSourceTensor:(MPSGraphTensor *) source
                                      descriptor:(MPSGraphPooling2DOpDescriptor *) descriptor
                                            name:(NSString * _Nullable) name;

-(MPSGraphTensor *) avgPooling2DGradientWithGradientTensor:(MPSGraphTensor *) gradient
                                              sourceTensor:(MPSGraphTensor *) source
                                                descriptor:(MPSGraphPooling2DOpDescriptor *) descriptor
                                                      name:(NSString * _Nullable) name;

@end

NS_ASSUME_NONNULL_END


#endif /* MPSGraphPoolingOps_h */
