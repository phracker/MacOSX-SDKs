//
//  MPSGraphImToColOps.h
//  MetalPerformanceShadersGraph
//
//  Created on 4/26/23.
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#ifndef MPSGraphImToColOps_h
#define MPSGraphImToColOps_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

/// The class that defines the parameters for an image to column or column to image operation.
///
/// Use this descriptor with the following ``MPSGraph`` methods:
/// - ``MPSGraph/imToColWithSourceTensor:descriptor:name:``
/// - ``MPSGraph/colToImWithSourceTensor:outputShape:descriptor:name:``
MPS_CLASS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0))
@interface MPSGraphImToColOpDescriptor : MPSGraphObject<NSCopying>

/// The property that defines the kernel size in width dimension.
@property (readwrite, nonatomic) NSUInteger kernelWidth;
/// The property that defines the kernel size  in height dimension.
@property (readwrite, nonatomic) NSUInteger kernelHeight;
/// The property that defines the stride in width dimension.
@property (readwrite, nonatomic) NSUInteger strideInX;
/// The property that defines the stride in height dimension.
@property (readwrite, nonatomic) NSUInteger strideInY;
/// The property that defines the dilation in width dimension.
@property (readwrite, nonatomic) NSUInteger dilationRateInX;
/// The property that defines the dilation in height dimension.
@property (readwrite, nonatomic) NSUInteger dilationRateInY;
/// The property that defines the padding in width dimension on the left side.
@property (readwrite, nonatomic) NSUInteger paddingLeft;
/// The property that defines the padding in width dimension on the right side.
@property (readwrite, nonatomic) NSUInteger paddingRight;
/// The property that defines the padding in height dimension at the top.
@property (readwrite, nonatomic) NSUInteger paddingTop;
/// The property that defines the padding in height dimension at the bottom.
@property (readwrite, nonatomic) NSUInteger paddingBottom;
/// The property that defines the layout of source or output  tensor.
/// e.g. `batch x channels x width x height` for `NCHW` layout
@property (readwrite, nonatomic) MPSGraphTensorNamedDataLayout dataLayout;

/// Creates an image to column descriptor with given values for parameters.
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
///   - dataLayout: See `dataLayout` property.
/// - Returns: A valid MPSGraphImToColOpDescriptor on autoreleasepool.
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
                                        dataLayout:(MPSGraphTensorNamedDataLayout) dataLayout;

/// Creates column to image descriptor with given values for parameters.
/// - Parameters:
///   - kernelWidth: See `kernelWidth` property.
///   - kernelHeight: See `kernelHeight` property.
///   - strideInX: See `strideInX` property.
///   - strideInY: See `strideInY` property.
///   - dilationRateInX: See `dilationRateInX` property.
///   - dilationRateInY: See `dilationRateInY` property.
///   - dataLayout: See `dataLayout` property.
/// - Returns: A valid MPSGraphImToColOpDescriptor on autoreleasepool.
+(nullable instancetype) descriptorWithKernelWidth:(NSUInteger) kernelWidth
                                      kernelHeight:(NSUInteger) kernelHeight
                                         strideInX:(NSUInteger) strideInX
                                         strideInY:(NSUInteger) strideInY
                                   dilationRateInX:(NSUInteger) dilationRateInX
                                   dilationRateInY:(NSUInteger) dilationRateInY
                                        dataLayout:(MPSGraphTensorNamedDataLayout) dataLayout;

/// Sets the descriptor's padding to the given values.
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

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(MPSGraphImToColOps)

/// Creates an imToCol operation and returns the result tensor.
///
/// - Parameters:
///   - source: The tensor containing the source data. Must be of rank 4. The layout is defined by `descriptor.dataLayout`.
///   - descriptor: The descriptor object that specifies the parameters of the operation.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) imToColWithSourceTensor:(MPSGraphTensor *) source
                                       descriptor:(MPSGraphImToColOpDescriptor *) descriptor
                                             name:(NSString * _Nullable) name
MPS_SWIFT_NAME( imToCol(_:descriptor:name:) );
MPS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0));

/// Creates a column to image operation and returns the result tensor.
///
/// - Parameters:
///   - source: The tensor containing the source data. Must be of rank 4. The layout is defined by `descriptor.dataLayout`.
///   - outputShape: The result tensor shape.
///   - descriptor: The descriptor object that specifies the parameters of the operation.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) colToImWithSourceTensor:(MPSGraphTensor *) source
                                outputShape:(MPSShape *)outputShape
                                 descriptor:(MPSGraphImToColOpDescriptor *) descriptor
                                       name:(NSString * _Nullable) name
MPS_SWIFT_NAME( colToIm(_:outputShape:descriptor:name:) );
MPS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0));
@end

NS_ASSUME_NONNULL_END

#endif /* MPSGraphImToColOps_h */
