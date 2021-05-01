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

/*!
 *  @typedef    MPSGraphLossReductionType
 *  @abstract   Options to be utilized by the graph
 *
 *  @constant   MPSGraphLossReductionTypeAxis                                   No Reductions
 *  @constant   MPSGraphLossReductionTypeSum                                    ReduceSum down to a scalar
 */
typedef NS_ENUM(uint64_t, MPSGraphLossReductionType)
{
    MPSGraphLossReductionTypeAxis                                            MPS_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0)) MPS_SWIFT_NAME(none) =   0,
    MPSGraphLossReductionTypeSum                                             MPS_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))                      =   1L,
};

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(MPSGraphLossOps)

/*!
 * @abstract   Create a softmax cross entropy loss op and return the result tensor
 *
 *
 * @param      sourceTensor                 sourceTensor
 * @param      labelsTensor                 labelsTensor
 * @param      axis               axis over which loss reuction happens
 * @param      reductionType               reductionType which reduces across all other axes
 * @param      name                                   name for the operation
 *
 * @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) softMaxCrossEntropyWithSourceTensor:(MPSGraphTensor *) sourceTensor
                                           labelsTensor:(MPSGraphTensor *) labelsTensor
                                                   axis:(NSInteger) axis
                                          reductionType:(MPSGraphLossReductionType) reductionType
                                                   name:(NSString * _Nullable) name
MPS_SWIFT_NAME( softMaxCrossEntropy(_:labels:axis:reuctionType:name:) );

/*!
 * @abstract   Create a softmax cross entropy loss op and return the result tensor
 *
 * @param      gradientTensor            gradientTensor
 * @param      sourceTensor                 sourceTensor
 * @param      labelsTensor                 labelsTensor
 * @param      axis               axis over which loss reuction happens
 * @param      reductionType               reductionType which reduces across all other axes
 * @param      name                                   name for the operation
 *
 * @return     A valid MPSGraphTensor object.
 */
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
