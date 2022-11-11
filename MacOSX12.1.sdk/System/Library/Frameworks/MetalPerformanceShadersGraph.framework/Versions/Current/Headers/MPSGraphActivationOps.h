//
//  MPSGraphActivationOps.h
//  MetalPerformanceShadersGraph
//
//  Created on 12/13/19.
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#ifndef MPSGraphActivationOps_h
#define MPSGraphActivationOps_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(MPSGraphActivationOps)


-(MPSGraphTensor *) reLUWithTensor:(MPSGraphTensor *) tensor
                              name:(NSString * _Nullable) name;


-(MPSGraphTensor *) reLUGradientWithIncomingGradient:(MPSGraphTensor *) gradient
                                        sourceTensor:(MPSGraphTensor *) source
                                                name:(NSString * _Nullable) name;


-(MPSGraphTensor *) sigmoidWithTensor:(MPSGraphTensor *) tensor
                                 name:(NSString * _Nullable) name;


-(MPSGraphTensor *) sigmoidGradientWithIncomingGradient:(MPSGraphTensor *) gradient
                                           sourceTensor:(MPSGraphTensor *) source
                                                   name:(NSString * _Nullable) name;


-(MPSGraphTensor *) softMaxWithTensor:(MPSGraphTensor *) tensor
                                 axis:(NSInteger) axis
                                 name:(NSString * _Nullable) name;

-(MPSGraphTensor *) softMaxGradientWithIncomingGradient:(MPSGraphTensor *) gradient
                                           sourceTensor:(MPSGraphTensor *) source
                                                   axis:(NSInteger) axis
                                                   name:(NSString * _Nullable) name;


/*!
 * @brief Leaky ReLU activation tensor
 * @discussion Specifies the leaky ReLU activation tensor.
 *             For each pixel, applies the following function: f(x) = max(x, alpha * x)
 */
-(MPSGraphTensor*)leakyReLUWithTensor:(MPSGraphTensor* _Nonnull)tensor
                                alpha:(double) alpha
                                 name:(NSString* _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

-(MPSGraphTensor*)leakyReLUWithTensor:(MPSGraphTensor* _Nonnull) tensor
                          alphaTensor:(MPSGraphTensor* _Nonnull) alphaTensor
                                 name:(NSString* _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

-(MPSGraphTensor*)leakyReLUGradientWithIncomingGradient:(MPSGraphTensor *) gradient
                                           sourceTensor:(MPSGraphTensor* _Nonnull) source
                                            alphaTensor:(MPSGraphTensor* _Nonnull) alphaTensor
                                                   name:(NSString* _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

@end

NS_ASSUME_NONNULL_END

#endif /* MPSGraphActivationOps_h */
