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

/*!
 *  @property   ceilMode
 *  @discussion If set then the output size is computed by rounding up instead of down when
 *              dividing by stride.
 *              Default value: @code NO @endcode
 */
@property (readwrite, nonatomic) BOOL ceilMode MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/*!
 *  @property   includeZeroPadToAverage
 *  @discussion For average pooling use a mode where samples outside the input tensor count as
 *              zeroes in the average computation. Otherwise the result is sum over samples divided by
 *              number of samples that didn't come from padding.
 *              Default value: @code NO @endcode
 */
@property (readwrite, nonatomic) BOOL includeZeroPadToAverage MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));


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

/*!
 *  @class      MPSGraphPooling4DOpDescriptor
 *  @abstract   Defines a 4d pooling operation
 */
MPS_CLASS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
@interface MPSGraphPooling4DOpDescriptor : NSObject<NSCopying>

/*!
 *  @property   kernelSizes
 *  @discussion Defines the pooling window size.
 *              Must be four numbers, one for each spatial dimension, fastest running index last.
 */
@property (readwrite, nonatomic, copy) NSArray<NSNumber *> * _Nonnull   kernelSizes;

/*!
 *  @property   strides
 *  @discussion Must be four numbers, one for each spatial dimension, fastest running index last.
 *              Default value: @code @[ @1, @1, @1, @1 ] @endcode
 */
@property (readwrite, nonatomic, copy) NSArray<NSNumber *> * _Nonnull   strides;

/*!
 *  @property   dilationRates
 *  @discussion Must be four numbers, one for each spatial dimension, fastest running index last.
 *              Default value: @code @[ @1, @1, @1, @1 ] @endcode
 */
@property (readwrite, nonatomic, copy) NSArray<NSNumber *> * _Nonnull   dilationRates;

/*!
 *  @property   paddingValues
 *  @discussion Must be eight numbers, two for each spatial dimension. `paddingValues[0]` defines the explicit padding
 *              amount before the first spatial dimension (slowest running index of spatial dimensions),
 *              `paddingValues[1]` defines the padding amount after the first spatial dimension etc.
 *              Used only when `paddingStyle = MPSGraphPaddingStyleExplicit`.
 *              Default value: @code @[ @0, @0, @0, @0, @0, @0, @0, @0 ] @endcode
 */
@property (readwrite, nonatomic, copy) NSArray<NSNumber *> * _Nonnull   paddingValues;

/*!
 *  @property   paddingStyle
 *  @discussion Defines what kind of padding to apply to operation.
 *              Default value: @code MPSGraphPaddingStyleExplicit @endcode
 */
@property (readwrite, nonatomic) MPSGraphPaddingStyle paddingStyle;

/*!
 *  @property   ceilMode
 *  @discussion If set then the output size is computed by rounding up instead of down when
 *              dividing by stride.
 *              Default value: @code NO @endcode
 */
@property (readwrite, nonatomic) BOOL ceilMode;

/*!
 *  @property   includeZeroPadToAverage
 *  @discussion For average pooling use a mode where samples outside the input tensor count as
 *              zeroes in the average computation. Otherwise the result is sum over samples divided by
 *              number of samples that didn't come from padding.
 *              Default value: @code NO @endcode
 */
@property (readwrite, nonatomic) BOOL includeZeroPadToAverage;


/*!
 *  @abstract   Creates a 4d pooling descriptor with given values.
 *  @param      kernelSizes        See corresponding property above.
 *  @param      strides                 See corresponding property above.
 *  @param      dilationRates    See corresponding property above.
 *  @param      paddingValues    See corresponding property above.
 *  @param      paddingStyle      See corresponding property above.
 *  @return     The descriptor on autoreleasepool.
 */
+(nullable instancetype) descriptorWithKernelSizes:(NSArray<NSNumber *> * _Nonnull) kernelSizes
                                           strides:(NSArray<NSNumber *> * _Nonnull) strides
                                     dilationRates:(NSArray<NSNumber *> * _Nonnull) dilationRates
                                     paddingValues:(NSArray<NSNumber *> * _Nonnull) paddingValues
                                      paddingStyle:(MPSGraphPaddingStyle) paddingStyle;

/*!
 *  @abstract   Creates a 4d pooling descriptor with default values.
 *  @param      kernelSizes        See corresponding property above.
 *  @param      paddingStyle      See corresponding property above.
 *  @return     The descriptor on autoreleasepool.
 */
+(nullable instancetype) descriptorWithKernelSizes:(NSArray<NSNumber *> * _Nonnull) kernelSizes
                                      paddingStyle:(MPSGraphPaddingStyle) paddingStyle;

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


-(MPSGraphTensor *) maxPooling4DWithSourceTensor:(MPSGraphTensor *) source
                                      descriptor:(MPSGraphPooling4DOpDescriptor *) descriptor
                                            name:(NSString * _Nullable) name
MPS_SWIFT_NAME( maxPooling4D(_:descriptor:name:))
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

-(MPSGraphTensor *) maxPooling4DGradientWithGradientTensor:(MPSGraphTensor *) gradient
                                              sourceTensor:(MPSGraphTensor *) source
                                                descriptor:(MPSGraphPooling4DOpDescriptor *) descriptor
                                                      name:(NSString * _Nullable) name
MPS_SWIFT_NAME( maxPooling4DGradient(_:source:descriptor:name:))
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

-(MPSGraphTensor *) avgPooling4DWithSourceTensor:(MPSGraphTensor *) source
                                      descriptor:(MPSGraphPooling4DOpDescriptor *) descriptor
                                            name:(NSString * _Nullable) name
MPS_SWIFT_NAME( avgPooling4D(_:descriptor:name:))
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));


-(MPSGraphTensor *) avgPooling4DGradientWithGradientTensor:(MPSGraphTensor *) gradient
                                              sourceTensor:(MPSGraphTensor *) source
                                                descriptor:(MPSGraphPooling4DOpDescriptor *) descriptor
                                                      name:(NSString * _Nullable) name
MPS_SWIFT_NAME( avgPooling4DGradient(_:source:descriptor:name:))
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));


-(MPSGraphTensor *) L2NormPooling4DWithSourceTensor:(MPSGraphTensor *) source
                                         descriptor:(MPSGraphPooling4DOpDescriptor *) descriptor
                                               name:(NSString * _Nullable) name
MPS_SWIFT_NAME( L2NormPooling4D(_:descriptor:name:))
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));


-(MPSGraphTensor *) L2NormPooling4DGradientWithGradientTensor:(MPSGraphTensor *) gradient
                                                 sourceTensor:(MPSGraphTensor *) source
                                                   descriptor:(MPSGraphPooling4DOpDescriptor *) descriptor
                                                         name:(NSString * _Nullable) name
MPS_SWIFT_NAME( L2NormPooling4DGradient(_:source:descriptor:name:))
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

@end

NS_ASSUME_NONNULL_END


#endif /* MPSGraphPoolingOps_h */
