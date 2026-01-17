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

/// The flattening mode for returned indices with max-pooling.
MPS_ENUM_AVAILABLE_STARTING(macos(12.2), ios(15.3), tvos(15.3))
typedef NS_ENUM(NSUInteger, MPSGraphPoolingReturnIndicesMode)
{
    /// No indices returned.
    MPSGraphPoolingReturnIndicesNone,
    /// Returns indices flattened in inner most (last) dimension.
    MPSGraphPoolingReturnIndicesGlobalFlatten1D,
    /// Returns indices flattened in 2 innermost dimensions. eg: HW in NCHW.
    MPSGraphPoolingReturnIndicesGlobalFlatten2D,
    /// Returns indices flattened in 3 innernost dimensions. eg: HWC in NHWC.
    MPSGraphPoolingReturnIndicesGlobalFlatten3D,
    /// Returns indices flattened in 4 innermost dimensions.
    MPSGraphPoolingReturnIndicesGlobalFlatten4D,
    /// Returns indices within pooling window, flattened in inner most dimension.
    MPSGraphPoolingReturnIndicesLocalFlatten1D,
    /// Returns indices within pooling window, flattened in 2 innermost dimensions. eg: HW in NCHW.
    MPSGraphPoolingReturnIndicesLocalFlatten2D,
    /// Returns indices within pooling window, flattened in 3 innernost dimensions. eg: HWC in NHWC.
    MPSGraphPoolingReturnIndicesLocalFlatten3D,
    /// Returns indices within pooling window, flattened in 4 innermost dimensions.
    MPSGraphPoolingReturnIndicesLocalFlatten4D,
};

/// The class that defines the parameters for a 2D pooling operation.
///
/// Use this descriptor with the following methods:
/// - ``MPSGraph/maxPooling2DWithSourceTensor:descriptor:name:``
/// - ``MPSGraph/maxPooling2DReturnIndicesWithSourceTensor:descriptor:name:``
/// - ``MPSGraph/maxPooling2DGradientWithGradientTensor:sourceTensor:descriptor:name:``
/// - ``MPSGraph/maxPooling2DGradientWithGradientTensor:indicesTensor:outputShape:descriptor:name:``
/// - ``MPSGraph/maxPooling2DGradientWithGradientTensor:indicesTensor:outputShapeTensor:descriptor:name:``
/// - ``MPSGraph/avgPooling2DWithSourceTensor:descriptor:name:``
/// - ``MPSGraph/avgPooling2DGradientWithGradientTensor:sourceTensor:descriptor:name:``
MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraphPooling2DOpDescriptor : MPSGraphObject<NSCopying>

/// Defines the pooling window size for the width dimension.
@property (readwrite, nonatomic) NSUInteger kernelWidth;
/// Defines the pooling window size for the height dimension.
@property (readwrite, nonatomic) NSUInteger kernelHeight;

/// Defines the stride for the width dimension. 
///
/// Default value: 1.
@property (readwrite, nonatomic) NSUInteger strideInX;
/// Defines the stride for the height dimension. 
///
/// Default value: 1.
@property (readwrite, nonatomic) NSUInteger strideInY;
/// Defines the dilation rate for the width dimension. 
///
/// Default value: 1.
@property (readwrite, nonatomic) NSUInteger dilationRateInX;
/// Defines the dilation rate for the height dimension. 
///
/// Default value: 1.
@property (readwrite, nonatomic) NSUInteger dilationRateInY;

/// Defines the explicit padding value for the width dimension to add before the data. 
///
/// Default value: 0.
@property (readwrite, nonatomic) NSUInteger paddingLeft;
/// Defines the explicit padding value for the width dimension to add after the data. 
///
/// Default value: 0.
@property (readwrite, nonatomic) NSUInteger paddingRight;
/// Defines the explicit padding value for the height dimension to add before the data. 
///
/// Default value: 0.
@property (readwrite, nonatomic) NSUInteger paddingTop;
/// Defines the explicit padding value for the height dimension to add after the data. 
///
/// Default value: 0.
@property (readwrite, nonatomic) NSUInteger paddingBottom;

/// Defines what kind of padding graph applies to the operation.
///
/// Default value: `MPSGraphPaddingStyleExplicit`.
@property (readwrite, nonatomic) MPSGraphPaddingStyle paddingStyle;
/// Defines the data layout of the input data in the forward pass. See: ``MPSGraphTensorNamedDataLayout``.
@property (readwrite, nonatomic) MPSGraphTensorNamedDataLayout dataLayout;

/// Defines the mode for returned indices of maximum values within each pooling window.
/// Use this in conjunction with ``MPSGraph/maxPooling2DReturnIndicesWithSourceTensor:descriptor:name:`` API.
/// If `returnIndicesMode = MPSGraphPoolingReturnIndicesNone` then only the first result
/// MPSGraph returns from ``MPSGraph/maxPooling2DReturnIndicesWithSourceTensor:descriptor:name:``
/// will be valid and using the second result will assert.
/// Default value: `MPSGraphPoolingReturnIndicesNone`.
@property (readwrite, nonatomic) MPSGraphPoolingReturnIndicesMode returnIndicesMode
MPS_AVAILABLE_STARTING(macos(12.2), ios(15.3), tvos(15.3));

/// Defines the data type for returned indices.
/// Use this in conjunction with ``MPSGraph/maxPooling2DReturnIndicesWithSourceTensor:descriptor:name:`` API.
/// Currently MPSGraph supports the following datatypes: `MPSDataTypeInt32`.
/// Default value: `MPSDataTypeInt32`.
@property (readwrite, nonatomic) MPSDataType returnIndicesDataType
MPS_AVAILABLE_STARTING(macos(12.2), ios(15.3), tvos(15.3));

/// Affects how the graph computes the output size.
///
/// if set to `YES` then output size is computed by rounding up instead of down when dividing input size by stride.
/// Default value: `NO`.
@property (readwrite, nonatomic) BOOL ceilMode MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/// Defines a mode for average pooling, where samples outside the input tensor count as zeroes in the average computation.
///
/// Otherwise the result is sum over samples divided by number of samples that didn't come from padding.
/// Default value: `NO`.
@property (readwrite, nonatomic) BOOL includeZeroPadToAverage MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/// Creates a 2D pooling descriptor with given values.
///
/// - Parameters:
///   - kernelWidth: See `kernelWidth` property.
///   - kernelHeight: See `kernelHeight` property.
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
/// - Returns: The descriptor on autoreleasepool.
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

/// Creates a 2D pooling descriptor with given values.
///
/// - Parameters:
///   - kernelWidth: See `kernelWidth` property.
///   - kernelHeight: See `kernelHeight`` property.
///   - strideInX: See `strideInX` property.
///   - strideInY: See `strideInY` property.
///   - paddingStyle: See `paddingStyle` property.
///   - dataLayout: See `dataLayout` property.
/// - Returns: The descriptor on autoreleasepool.
+(nullable instancetype) descriptorWithKernelWidth:(NSUInteger) kernelWidth
                                      kernelHeight:(NSUInteger) kernelHeight
                                         strideInX:(NSUInteger) strideInX
                                         strideInY:(NSUInteger) strideInY
                                      paddingStyle:(MPSGraphPaddingStyle) paddingStyle
                                        dataLayout:(MPSGraphTensorNamedDataLayout) dataLayout;

/// Sets the explicit padding values and sets padding style to explicit.
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

/// The class that defines the parameters for a 4D pooling operation.
///
/// Use this descriptor with the following methods:
/// - ``MPSGraph/maxPooling4DWithSourceTensor:descriptor:name:``
/// - ``MPSGraph/maxPooling4DReturnIndicesWithSourceTensor:descriptor:name:``
/// - ``MPSGraph/maxPooling4DGradientWithGradientTensor:sourceTensor:descriptor:name:``
/// - ``MPSGraph/maxPooling4DGradientWithGradientTensor:indicesTensor:outputShape:descriptor:name:``
/// - ``MPSGraph/maxPooling4DGradientWithGradientTensor:indicesTensor:outputShapeTensor:descriptor:name:``
/// - ``MPSGraph/avgPooling4DWithSourceTensor:descriptor:name:``
/// - ``MPSGraph/avgPooling4DGradientWithGradientTensor:sourceTensor:descriptor:name:``
/// - ``MPSGraph/L2NormPooling4DWithSourceTensor:descriptor:name:``
/// - ``MPSGraph/L2NormPooling4DGradientWithGradientTensor:sourceTensor:descriptor:name:``
MPS_CLASS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
@interface MPSGraphPooling4DOpDescriptor : MPSGraphObject<NSCopying>

/// Defines the pooling window size. 
/// 
/// Must be four numbers, one for each spatial dimension, fastest running index last.
@property (readwrite, nonatomic, copy) NSArray<NSNumber *> * _Nonnull   kernelSizes;

/// Defines strides for spatial dimensions. Must be four numbers, one for each spatial dimension, fastest running index last.
///
/// Default value: `@[ @1, @1, @1, @1 ]`
@property (readwrite, nonatomic, copy) NSArray<NSNumber *> * _Nonnull   strides;

/// Defines dilation rates for spatial dimensions. Must be four numbers, one for each spatial dimension, fastest running index last.
/// 
/// Default value: `@[ @1, @1, @1, @1 ]`
@property (readwrite, nonatomic, copy) NSArray<NSNumber *> * _Nonnull   dilationRates;

/// Defines padding values for spatial dimensions which must be eight numbers, two for each spatial dimension.
///
/// For example `paddingValues[0]` defines the explicit padding
/// amount before the first spatial dimension (slowest running index of spatial dimensions),
/// `paddingValues[1]` defines the padding amount after the first spatial dimension etc.
/// Used only when `paddingStyle = MPSGraphPaddingStyleExplicit`.
/// Default value: `@[ @0, @0, @0, @0, @0, @0, @0, @0 ]`
@property (readwrite, nonatomic, copy) NSArray<NSNumber *> * _Nonnull   paddingValues;

/// Defines what kind of padding graph applies to the operation.
///
/// Default value: `MPSGraphPaddingStyleExplicit`.
@property (readwrite, nonatomic) MPSGraphPaddingStyle paddingStyle;

/// Affects how MPSGraph computes the output size: if set to `YES` then output size is
/// computed by rounding up instead of down when dividing input size by stride.
/// 
/// Default value: `NO`.
@property (readwrite, nonatomic) BOOL ceilMode;

/// Defines a mode for average pooling, where samples outside the input tensor count as
/// zeroes in the average computation.
///
/// Otherwise the result is sum over samples divided by
/// number of samples that didn't come from padding.
/// Default value: `NO`.
@property (readwrite, nonatomic) BOOL includeZeroPadToAverage;

/// Defines the mode for returned indices of maximum values within each pooling window.
/// 
/// Use this in conjunction with ``MPSGraph/maxPooling4DReturnIndicesWithSourceTensor:descriptor:name:`` API.
/// If `returnIndicesMode = MPSGraphPoolingReturnIndicesNone` then only the first result
/// MPSGraph returns from ``MPSGraph/maxPooling4DReturnIndicesWithSourceTensor:descriptor:name:``
/// will be valid and using the second result will assert.
/// Default value: `MPSGraphPoolingReturnIndicesNone`.
@property (readwrite, nonatomic) MPSGraphPoolingReturnIndicesMode returnIndicesMode
MPS_AVAILABLE_STARTING(macos(12.2), ios(15.3), tvos(15.3));

/// Defines the data type for returned indices.
/// 
/// Use this in conjunction with ``MPSGraph/maxPooling4DReturnIndicesWithSourceTensor:descriptor:name:`` API.
/// Currently MPSGraph supports the following datatypes: `MPSDataTypeInt32`.
/// Default value: `MPSDataTypeInt32`.
@property (readwrite, nonatomic) MPSDataType returnIndicesDataType
MPS_AVAILABLE_STARTING(macos(12.2), ios(15.3), tvos(15.3));

/// Creates a 4D pooling descriptor with given values.
///
/// - Parameters:
///   - kernelSizes: See `kernelSizes` property.
///   - strides: See `strides` property.
///   - dilationRates: See `dilationRates` property.
///   - paddingValues: See `paddingValues` property.
///   - paddingStyle: See `paddingStyle` property.
/// - Returns: The descriptor on autoreleasepool.
+(nullable instancetype) descriptorWithKernelSizes:(NSArray<NSNumber *> * _Nonnull) kernelSizes
                                           strides:(NSArray<NSNumber *> * _Nonnull) strides
                                     dilationRates:(NSArray<NSNumber *> * _Nonnull) dilationRates
                                     paddingValues:(NSArray<NSNumber *> * _Nonnull) paddingValues
                                      paddingStyle:(MPSGraphPaddingStyle) paddingStyle;

/// Creates a 4D pooling descriptor with default values.
///
/// - Parameters:
///   - kernelSizes: See `kernelSizes` property.
///   - paddingStyle: See `paddingStyle` property.
/// - Returns: The descriptor on autoreleasepool.
+(nullable instancetype) descriptorWithKernelSizes:(NSArray<NSNumber *> * _Nonnull) kernelSizes
                                      paddingStyle:(MPSGraphPaddingStyle) paddingStyle;

@end

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(MPSGraphPoolingOps)

/// Creates a 2D max-pooling operation and returns the result tensor.
///
/// - Parameters:
///   - source: A 2D Image source as tensor - must be of rank=4. The layout is defined by `descriptor.dataLayout`.
///   - descriptor: A pooling operation descriptor that specifies pooling window sizes, strides, dilation rates, paddings and layouts.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) maxPooling2DWithSourceTensor:(MPSGraphTensor *) source
                                      descriptor:(MPSGraphPooling2DOpDescriptor *) descriptor
                                            name:(NSString * _Nullable) name;

/// Creates a 2D max-pooling operation and returns the result tensor and the corresponding indices tensor.
///
/// In order to Computes the indices, `returnIndicesMode` of the descriptor must be set. The datatype of indices tensor can be set
/// using `returnIndicesDataType`.
/// If `returnIndicesMode = MPSGraphPoolingReturnIndicesNone` then only the first result
/// MPSGraph returns will be valid and using the second result will assert.
///
/// - Parameters:
///   - source: A 2D Image source as tensor - must be of rank=4. The layout is defined by `descriptor.dataLayout`.
///   - descriptor: A pooling operation descriptor that specifies pooling window sizes, strides, dilation rates, paddings and layouts.
///   - name: The name for the operation.
/// - Returns: An array of two MPSGraphTensors. The first tensor holds the result of max pool and the second tensor holds the corresponding indices
-(NSArray<MPSGraphTensor *> *) maxPooling2DReturnIndicesWithSourceTensor:(MPSGraphTensor *) source
                                                              descriptor:(MPSGraphPooling2DOpDescriptor *) descriptor
                                                                    name:(NSString * _Nullable) name
MPS_SWIFT_NAME( maxPooling2DReturnIndices(_:descriptor:name:))
MPS_AVAILABLE_STARTING(macos(12.2), ios(15.3), tvos(15.3));

/// Creates a max-pooling gradient operation and returns the result tensor.
///
/// - Parameters:
///   - gradient: A 2D input gradient tensor - must be of rank=4. The layout is defined by `descriptor.dataLayout`.
///   - source: The input tensor for the forward pass.
///   - descriptor: A pooling operation descriptor that specifies pooling window sizes, strides, dilation rates, paddings and layouts.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) maxPooling2DGradientWithGradientTensor:(MPSGraphTensor *) gradient
                                              sourceTensor:(MPSGraphTensor *) source
                                                descriptor:(MPSGraphPooling2DOpDescriptor *) descriptor
                                                      name:(NSString * _Nullable) name;

/// Creates a max-pooling gradient operation and returns the result tensor.
///
/// With this API MPSGraph computes the max-pooling gradient efficiently by reusing the indices from the forward API instead of recomputing them.
/// The descriptor must set `returnIndicesMode` and `returnIndicesDataType` to the same value as that set by the forward pass.
///
/// - Parameters:
///   - gradient: A 2D input gradient tensor - must be of rank=4. The layout is defined by `descriptor.dataLayout`.
///   - indices: The indices tensor returned from ``MPSGraph/maxPooling2DReturnIndicesWithSourceTensor:descriptor:name:``.
///   - outputShape: The shape of the destination gradient.
///   - descriptor: A pooling operation descriptor that specifies pooling window sizes, strides, dilation rates, paddings and layouts.
///   - name: The name for the operation.
/// - Returns: Destination gradient tensor.
-(MPSGraphTensor *) maxPooling2DGradientWithGradientTensor:(MPSGraphTensor *) gradient
                                             indicesTensor:(MPSGraphTensor *) indices
                                               outputShape:(MPSShape*) outputShape
                                               descriptor:(MPSGraphPooling2DOpDescriptor *) descriptor
                                                     name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/// Creates a max-pooling gradient operation and returns the result tensor.
///
/// With this API MPSGraph computes the max-pooling gradient efficiently by reusing the indices from the forward API instead of recomputing them.
/// The descriptor must set `returnIndicesMode` and `returnIndicesDataType` to the same value as that set by the forward pass.
///
/// - Parameters:
///   - gradient: A 2D input gradient tensor - must be of rank=4. The layout is defined by `descriptor.dataLayout`.
///   - indices: The indices tensor returned from ``MPSGraph/maxPooling2DReturnIndicesWithSourceTensor:descriptor:name:``.
///   - outputShape: A tensor containing the shape of the destination gradient.
///   - descriptor: A pooling operation descriptor that specifies pooling window sizes, strides, dilation rates, paddings and layouts.
///   - name: The name for the operation.
/// - Returns: Destination gradient tensor.
-(MPSGraphTensor *) maxPooling2DGradientWithGradientTensor:(MPSGraphTensor *) gradient
                                             indicesTensor:(MPSGraphTensor *) indices
                                         outputShapeTensor:(MPSGraphTensor*) outputShape
                                               descriptor:(MPSGraphPooling2DOpDescriptor *) descriptor
                                                     name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/// Creates a 2D average-pooling operation and returns the result tensor.
///
/// - Parameters:
///   - source: A 2D Image source as tensor - must be of rank=4. The layout is defined by `descriptor.dataLayout`.
///   - descriptor: A pooling operation descriptor that specifies pooling window sizes, strides, dilation rates, paddings and layouts.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) avgPooling2DWithSourceTensor:(MPSGraphTensor *) source
                                      descriptor:(MPSGraphPooling2DOpDescriptor *) descriptor
                                            name:(NSString * _Nullable) name;

/// Creates a 2D average pooling gradient operation and returns the result tensor.
///
/// - Parameters:
///   - gradient: A 2D input gradient tensor - must be of rank=4. The layout is defined by `descriptor.dataLayout`.
///   - source: The input tensor for the forward pass.
///   - descriptor: A pooling operation descriptor that specifies pooling window sizes, strides, dilation rates, paddings and layouts.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) avgPooling2DGradientWithGradientTensor:(MPSGraphTensor *) gradient
                                              sourceTensor:(MPSGraphTensor *) source
                                                descriptor:(MPSGraphPooling2DOpDescriptor *) descriptor
                                                      name:(NSString * _Nullable) name;

/// Creates a 4D max-pooling operation and returns the result tensor.
///
/// - Parameters:
///   - source: A source tensor.
///   - descriptor: A pooling operation descriptor that specifies pooling window sizes, strides, dilation rates and paddings.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) maxPooling4DWithSourceTensor:(MPSGraphTensor *) source
                                      descriptor:(MPSGraphPooling4DOpDescriptor *) descriptor
                                            name:(NSString * _Nullable) name
MPS_SWIFT_NAME( maxPooling4D(_:descriptor:name:))
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/// Creates a 4D max-pooling operation and returns the result tensor and the corresponding indices tensor.
///
/// In order to Computes the indices, `returnIndicesMode` of the descriptor must be set. The datatype of indices tensor can be set
/// using `returnIndicesDataType`.
/// If `returnIndicesMode = MPSGraphPoolingReturnIndicesNone` then only the first result
/// MPSGraph returns will be valid and using the second result will assert.
///
/// - Parameters:
///   - source: The source tensor on which pooling will be performed.
///   - descriptor: A pooling operation descriptor that specifies pooling window sizes, strides, dilation rates and paddings.
///   - name: The name for the operation.
/// - Returns: An array of two MPSGraphTensors. The first tensor holds the result of max pool and the second tensor holds the corresponding indices.
-(NSArray<MPSGraphTensor *> *) maxPooling4DReturnIndicesWithSourceTensor:(MPSGraphTensor *) source
                                                              descriptor:(MPSGraphPooling4DOpDescriptor *) descriptor
                                                                    name:(NSString * _Nullable) name
MPS_SWIFT_NAME( maxPooling4DReturnIndices(_:descriptor:name:))
MPS_AVAILABLE_STARTING(macos(12.2), ios(15.3), tvos(15.3));

/// Creates a max-pooling gradient operation and returns the result tensor.
///
/// - Parameters:
///   - gradient: An input gradient tensor.
///   - source: The input tensor for the forward pass.
///   - descriptor: A pooling operation descriptor that specifies pooling window sizes, strides, dilation rates and paddings.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) maxPooling4DGradientWithGradientTensor:(MPSGraphTensor *) gradient
                                              sourceTensor:(MPSGraphTensor *) source
                                                descriptor:(MPSGraphPooling4DOpDescriptor *) descriptor
                                                      name:(NSString * _Nullable) name
MPS_SWIFT_NAME( maxPooling4DGradient(_:source:descriptor:name:))
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/// Creates a max-pooling gradient operation and returns the result tensor.
///
/// With this API MPSGraph computes the max-pooling gradient efficiently by reusing the indices from the forward API instead of recomputing them.
/// The descriptor must set `returnIndicesMode` and `returnIndicesDataType` to the same value as that set by the forward pass.
///
/// - Parameters:
///   - gradient: An input gradient tensor.
///   - indices: Indices tensor returned from ``MPSGraph/maxPooling4DReturnIndicesWithSourceTensor:descriptor:name:``.
///   - outputShape: The shape of the destination gradient.
///   - descriptor: A pooling operation descriptor that specifies pooling window sizes, strides, dilation rates, paddings and layouts.
///   - name: The name for the operation.
/// - Returns: Destination gradient tensor.
-(MPSGraphTensor *) maxPooling4DGradientWithGradientTensor:(MPSGraphTensor *) gradient
                                             indicesTensor:(MPSGraphTensor *) indices
                                               outputShape:(MPSShape*) outputShape
                                               descriptor:(MPSGraphPooling4DOpDescriptor *) descriptor
                                                     name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/// Creates a max-pooling gradient operation and returns the result tensor.
///
/// With this API MPSGraph computes the max-pooling gradient efficiently by reusing the indices from the forward API instead of recomputing them.
/// The descriptor must set `returnIndicesMode` and `returnIndicesDataType` to the same value as that set by the forward pass.
///
/// - Parameters:
///   - gradient: An input gradient tensor.
///   - indices: The indices tensor returned from ``MPSGraph/maxPooling4DReturnIndicesWithSourceTensor:descriptor:name:``.
///   - outputShape: A tensor containing the shape of the destination gradient.
///   - descriptor: A pooling operation descriptor that specifies pooling window sizes, strides, dilation rates, paddings and layouts.
///   - name: The name for the operation.
/// - Returns: Destination gradient tensor.
-(MPSGraphTensor *) maxPooling4DGradientWithGradientTensor:(MPSGraphTensor *) gradient
                                             indicesTensor:(MPSGraphTensor *) indices
                                         outputShapeTensor:(MPSGraphTensor*) outputShape
                                               descriptor:(MPSGraphPooling4DOpDescriptor *) descriptor
                                                     name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/// Creates a 4D average pooling operation and returns the result tensor.
///
/// - Parameters:
///   - source: A source tensor.
///   - descriptor: A pooling operation descriptor that specifies pooling window sizes, strides, dilation rates and paddings.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) avgPooling4DWithSourceTensor:(MPSGraphTensor *) source
                                      descriptor:(MPSGraphPooling4DOpDescriptor *) descriptor
                                            name:(NSString * _Nullable) name
MPS_SWIFT_NAME( avgPooling4D(_:descriptor:name:))
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/// Creates an average pooling gradient operation and returns the result tensor.
///
/// - Parameters:
///   - gradient: An input gradient tensor.
///   - source: The input tensor for the forward pass.
///   - descriptor: A pooling operation descriptor that specifies pooling window sizes, strides, dilation rates and paddings.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) avgPooling4DGradientWithGradientTensor:(MPSGraphTensor *) gradient
                                              sourceTensor:(MPSGraphTensor *) source
                                                descriptor:(MPSGraphPooling4DOpDescriptor *) descriptor
                                                      name:(NSString * _Nullable) name
MPS_SWIFT_NAME( avgPooling4DGradient(_:source:descriptor:name:))
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/// Creates a 4D L2-norm pooling operation and returns the result tensor.
///
/// - Parameters:
///   - source: A source tensor.
///   - descriptor: A pooling operation descriptor that specifies pooling window sizes, strides, dilation rates and paddings.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) L2NormPooling4DWithSourceTensor:(MPSGraphTensor *) source
                                         descriptor:(MPSGraphPooling4DOpDescriptor *) descriptor
                                               name:(NSString * _Nullable) name
MPS_SWIFT_NAME( L2NormPooling4D(_:descriptor:name:))
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/// Creates a L2-Norm pooling gradient operation and returns the result tensor.
///
/// - Parameters:
///   - gradient: An input gradient tensor.
///   - source: The input tensor for the forward pass.
///   - descriptor: A pooling operation descriptor that specifies pooling window sizes, strides, dilation rates and paddings.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) L2NormPooling4DGradientWithGradientTensor:(MPSGraphTensor *) gradient
                                                 sourceTensor:(MPSGraphTensor *) source
                                                   descriptor:(MPSGraphPooling4DOpDescriptor *) descriptor
                                                         name:(NSString * _Nullable) name
MPS_SWIFT_NAME( L2NormPooling4DGradient(_:source:descriptor:name:))
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

@end

NS_ASSUME_NONNULL_END


#endif /* MPSGraphPoolingOps_h */
