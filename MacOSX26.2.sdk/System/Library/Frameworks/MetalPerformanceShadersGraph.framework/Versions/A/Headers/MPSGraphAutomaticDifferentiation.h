//
//  MPSGraphAutomaticDifferentiation.h
//  MPSGraph
//
//  Created on 3/28/20.
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#ifndef MPSGraphGradientOps_h
#define MPSGraphGradientOps_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(MPSGraphGradientOps)

/// Calculates a partial derivative of primaryTensor with respect to the tensors.
///
/// - Parameters:
///   - primaryTensor: Tensor to be differentiated (numerator).
///   - tensors: Tensors to do the differentiation with (denominator).
///   - name: Name for the gradient operation.
/// - Returns: A valid MPSGraphTensor dictionary object containing partial derivative d(primaryTensor)/d(secondaryTensor) for each tensor as key.
-(NSDictionary<MPSGraphTensor *, MPSGraphTensor *> *) gradientForPrimaryTensor:(MPSGraphTensor *) primaryTensor
                                                                   withTensors:(NSArray<MPSGraphTensor *> *) tensors
                                                                          name:(NSString * _Nullable) name
MPS_SWIFT_NAME( gradients(of:with:name:) );

@end

NS_ASSUME_NONNULL_END


#endif /* MPSGraphGradientOps_h */
