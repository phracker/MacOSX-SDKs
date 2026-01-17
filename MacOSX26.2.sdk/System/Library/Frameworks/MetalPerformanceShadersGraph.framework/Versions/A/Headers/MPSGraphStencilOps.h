//
//  MPSGraphStencilOps.h
//  MetalPerformanceShadersGraph
//
//  Created on 12/16/20.
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#ifndef MPSGraphStencilOps_h
#define MPSGraphStencilOps_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

/// The class that defines the parameters for a stencil operation.
///
/// Use this descriptor with the following ``MPSGraph`` method:
/// - ``MPSGraph/stencilWithSourceTensor:weightsTensor:descriptor:name:``
MPS_CLASS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
@interface MPSGraphStencilOpDescriptor : MPSGraphObject<NSCopying>

/// The reduction mode to use within the stencil window.
///
/// Default value: `MPSGraphReductionModeSum`.
@property (readwrite, nonatomic) MPSGraphReductionMode reductionMode;

/// An array of length four that determines from which offset to start reading the input tensor.
///
/// Only used when `paddingStyle` is `MPSGraphPaddingStyleExplicitOffset`.
/// For example zero offset means that the first stencil window will align its top-left corner (in 4 dimensions) to the top-left corner of the input tensor.
/// Default value: `@[ @0, @0, @0, @0 ]`
@property (readwrite, nonatomic, copy) MPSShape * offsets;

/// The property that defines strides for spatial dimensions.
///
/// Must be four numbers, one for each spatial dimension, fastest running index last.
/// Default value: `@[ @1, @1, @1, @1 ]`
@property (readwrite, nonatomic, copy) MPSShape * strides;

/// The property that defines dilation rates for spatial dimensions.
///
/// Must be four numbers, one for each spatial dimension, fastest running index last.
/// Default value: `@[ @1, @1, @1, @1 ]`
@property (readwrite, nonatomic, copy) MPSShape * dilationRates;

/// The property that defines padding values for spatial dimensions.
///
/// Must be eight numbers, two for each spatial dimension.
/// For example `paddingValues[0]` defines the explicit padding
/// amount before the first spatial dimension (slowest running index of spatial dimensions),
/// `paddingValues[1]` defines the padding amount after the first spatial dimension etc.
/// Used only when `paddingStyle = MPSGraphPaddingStyleExplicit`.
/// Default value: `@[ @0, @0, @0, @0, @0, @0, @0, @0 ]`
@property (readwrite, nonatomic, copy) MPSShape * explicitPadding;

/// The property that determines which values to use for padding the input tensor.
/// 
/// Default value: `MPSGraphPaddingModeZero`.
@property (readwrite, nonatomic) MPSGraphPaddingMode boundaryMode;

/// The property that defines what kind of padding to apply to the stencil operation.
/// 
/// Default value: `MPSGraphPaddingStyleExplicit`.
@property (readwrite, nonatomic) MPSGraphPaddingStyle paddingStyle;

/// The padding value for `boundaryMode = MPSGraphPaddingModeConstant`.
/// 
/// Default value: 0.
@property (readwrite, nonatomic) float paddingConstant;

/// Creates a stencil operation descriptor with given values.
///
/// - Parameters:
///   - reductionMode: See `reductionMode` property.
///   - offsets: See `offsets` property.
///   - strides: See `strides` property.
///   - dilationRates: See `dilationRates` property.
///   - explicitPadding: See `explicitPadding` property.
///   - boundaryMode: See `boundaryMode` property.
///   - paddingStyle: See `paddingStyle` property.
///   - paddingConstant: See `paddingConstant` property.
/// - Returns: A valid MPSGraphStencilOpDescriptor object
+(nullable instancetype) descriptorWithReductionMode:(MPSGraphReductionMode) reductionMode
                                             offsets:(MPSShape *) offsets
                                             strides:(MPSShape *) strides
                                       dilationRates:(MPSShape *) dilationRates
                                     explicitPadding:(MPSShape *) explicitPadding
                                        boundaryMode:(MPSGraphPaddingMode) boundaryMode
                                        paddingStyle:(MPSGraphPaddingStyle) paddingStyle
                                     paddingConstant:(float) paddingConstant;

/// Creates a stencil operation descriptor with default values.
///
/// - Parameters:
///   - offsets: See `offsets` property.
///   - explicitPadding: See `explicitPadding` property.
/// - Returns: A valid MPSGraphStencilOpDescriptor object
+(nullable instancetype) descriptorWithOffsets:(MPSShape *) offsets
                               explicitPadding:(MPSShape *) explicitPadding;

/// Creates a stencil operation descriptor with default values.
///
/// - Parameters:
///   - explicitPadding: See `explicitPadding` property.
/// - Returns: A valid MPSGraphStencilOpDescriptor object
+(nullable instancetype) descriptorWithExplicitPadding:(MPSShape *) explicitPadding;

/// Creates a stencil operation descriptor with default values.
///
/// - Parameters:
///   - paddingStyle: See `paddingStyle` property.
/// - Returns: A valid MPSGraphStencilOpDescriptor object
+(nullable instancetype) descriptorWithPaddingStyle:(MPSGraphPaddingStyle) paddingStyle;

@end

MPS_CLASS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
@interface MPSGraph(MPSGraphStencilOps)

/// Creates a stencil operation and returns the result tensor.
///
/// Performs a weighted reduction operation (See ``MPSGraphStencilOpDescriptor/reductionMode``) on the last 4 dimensions of the `source`
/// over the window determined by `weights`, according to the value defined in `descriptor`.
///  ```md
///     y[i] = reduction{j \in w} ( x[ i + j ]w[j] )
/// ```
///
/// - Parameters:
///   - source: The tensor containing the source data. Must be of rank 4 or greater.
///   - weights: A 4-D tensor containing the weights data.
///   - descriptor: The descriptor object that specifies the parameters for the stencil operation.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) stencilWithSourceTensor:(MPSGraphTensor *) source
                              weightsTensor:(MPSGraphTensor *) weights
                                 descriptor:(MPSGraphStencilOpDescriptor *) descriptor
                                       name:(NSString * _Nullable) name;

@end

NS_ASSUME_NONNULL_END

#endif /* MPSGraphStencilOps_h */
