//
//  MPSGraphLossOps.h
//  MPSGraph
//
//  Created on 3/27/20.
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#ifndef MPSGraphLossOps_h
#define MPSGraphLossOps_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

/// The type of the reduction the graph applies in the loss operations.
typedef NS_ENUM(uint64_t, MPSGraphLossReductionType)
{
    /// Computes the loss without reduction.
    MPSGraphLossReductionTypeNone                                            MPS_ENUM_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0)) MPS_SWIFT_NAME(none) =   0L,
    /// Computes the loss without reduction.
    MPSGraphLossReductionTypeAxis                                            MPS_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0)) MPS_SWIFT_NAME(axis) =   MPSGraphLossReductionTypeNone,
    /// Reduces the loss down to a scalar with a sum operation.
    MPSGraphLossReductionTypeSum                                             MPS_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))                      =   1L,
    /// Reduces the loss down to a scalar with a mean operation.
    MPSGraphLossReductionTypeMean                                            MPS_ENUM_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))                      =   2L,
};

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(MPSGraphLossOps)

/// Creates a softmax cross-entropy loss operation and returns the result tensor.
///
/// The softmax cross-entropy operation computes:
/// ```md
///     loss = reduction( - labels*ln( softmax(source) )), where
///     sotfmax(source) = exp(source) / sum( exp(source) ), and
/// ```
/// the operation performs the reduction over the `axis` dimension.
///
/// - Parameters:
///   - sourceTensor: The source tensor.
///   - labelsTensor: The labels tensor.
///   - axis: The axis over which the operation computes the softmax reduction.
///   - reductionType: The type of reduction MPSGraph uses to reduce across all other axes than `axis`. See: ``MPSGraphLossReductionType``.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) softMaxCrossEntropyWithSourceTensor:(MPSGraphTensor *) sourceTensor
                                           labelsTensor:(MPSGraphTensor *) labelsTensor
                                                   axis:(NSInteger) axis
                                          reductionType:(MPSGraphLossReductionType) reductionType
                                                   name:(NSString * _Nullable) name
MPS_SWIFT_NAME( softMaxCrossEntropy(_:labels:axis:reuctionType:name:) );

/// Creates the gradient of a softmax cross-entropy loss operation and returns the result tensor.
///
/// - Parameters:
///   - gradientTensor: The input gradientTensor. Note: in most cases this is the initial gradient tensor, which is a constant tensor with value one.
///   - sourceTensor: The source tensor.
///   - labelsTensor: The labels tensor.
///   - axis: The axis over which the operation computes the softmax reduction.
///   - reductionType: The type of reduction MPSGraph uses to reduce across all other axes than `axis`. See: ``MPSGraphLossReductionType``.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) softMaxCrossEntropyGradientWithIncomingGradientTensor:(MPSGraphTensor *) gradientTensor
                                                             sourceTensor:(MPSGraphTensor *) sourceTensor
                                                             labelsTensor:(MPSGraphTensor *) labelsTensor
                                                                     axis:(NSInteger) axis
                                                            reductionType:(MPSGraphLossReductionType) reductionType
                                                                     name:(NSString * _Nullable) name
MPS_SWIFT_NAME( softMaxCrossEntropyGradient(_:source:labels:axis:reuctionType:name:) );

@end

NS_ASSUME_NONNULL_END

#endif /* MPSGraphLossOps_h */
