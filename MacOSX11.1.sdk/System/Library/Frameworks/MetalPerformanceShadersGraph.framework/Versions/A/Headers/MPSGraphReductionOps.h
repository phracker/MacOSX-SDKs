//
//  MPSGraphReductionOps.h
//  MetalPerformanceShadersGraph
//
//  Created on 12/13/19.
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#ifndef MPSGraphReductionOps_h
#define MPSGraphReductionOps_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(MPSGraphReductionOps)

-(MPSGraphTensor *) reductionSumWithTensor:(MPSGraphTensor *) tensor
                                      axis:(NSInteger) axis
                                      name:(NSString * _Nullable) name;

-(MPSGraphTensor *) reductionSumWithTensor:(MPSGraphTensor *) tensor
                                      axes:(NSArray<NSNumber *> *)axes
                                      name:(NSString * _Nullable) name;

-(MPSGraphTensor *) reductionMaximumWithTensor:(MPSGraphTensor *) tensor
                                          axis:(NSInteger) axis
                                          name:(NSString * _Nullable) name;

-(MPSGraphTensor *) reductionMaximumWithTensor:(MPSGraphTensor *) tensor
                                          axes:(NSArray<NSNumber *> *)axes
                                          name:(NSString * _Nullable) name;

-(MPSGraphTensor *) reductionMinimumWithTensor:(MPSGraphTensor *) tensor
                                          axis:(NSInteger) axis
                                          name:(NSString * _Nullable) name;

-(MPSGraphTensor *) reductionMinimumWithTensor:(MPSGraphTensor *) tensor
                                          axes:(NSArray<NSNumber *> *)axes
                                          name:(NSString * _Nullable) name;

-(MPSGraphTensor *) reductionProductWithTensor:(MPSGraphTensor *) tensor
                                          axis:(NSInteger) axis
                                          name:(NSString * _Nullable) name;

-(MPSGraphTensor *) reductionProductWithTensor:(MPSGraphTensor *) tensor
                                          axes:(NSArray<NSNumber *> *)axes
                                          name:(NSString * _Nullable) name;

@end

NS_ASSUME_NONNULL_END

#endif /* MPSGraphReductionOps_h */
