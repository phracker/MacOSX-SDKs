//
//  MPSGraphOptimizerOps.h
//  MetalPerformanceShadersGraph
//
//  Created on 2/4/20.
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#ifndef MPSGraphOptimizerOps_h
#define MPSGraphOptimizerOps_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(MPSGraphOptimizerOps)

/// The Stochastic gradient descent performs a gradient descent.
///
/// `variable = variable - (learningRate * g)`
/// where, 
/// `g` is gradient of error wrt variable
///
/// - Parameters:
///   - learningRateTensor: scalar tensor which indicates the learning rate to use with the optimizer
///   - valuesTensor: values tensor, usually representing the trainable parameters
///   - gradientTensor: partial gradient of the trainable parameters with respect to loss
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) stochasticGradientDescentWithLearningRateTensor:(MPSGraphTensor *) learningRateTensor
                                                       valuesTensor:(MPSGraphTensor *) valuesTensor
                                                     gradientTensor:(MPSGraphTensor *) gradientTensor
                                                               name:(NSString * _Nullable) name
MPS_SWIFT_NAME( stochasticGradientDescent(learningRate:values:gradient:name:) );

/// The Stochastic gradient descent performs a gradient descent
/// `variable = variable - (learningRate * g)`
/// where,
/// `g` is gradient of error wrt variable
/// this op directly writes to the variable
///
/// - Parameters:
///   - learningRateTensor: scalar tensor which indicates the learning rate to use with the optimizer
///   - variable: variable operation with trainable parameters
///   - gradientTensor: partial gradient of the trainable parameters with respect to loss
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphOperation *) applyStochasticGradientDescentWithLearningRateTensor:(MPSGraphTensor *) learningRateTensor
                                                                   variable:(MPSGraphVariableOp *) variable
                                                             gradientTensor:(MPSGraphTensor *) gradientTensor
                                                                       name:(NSString * _Nullable) name
MPS_SWIFT_NAME( applyStochasticGradientDescent(learningRate:variable:gradient:name:) );

/// Creates operations to apply Adam optimization.
///
/// The adam update ops are added 
/// current learning rate:
/// ```md
/// lr[t] = learningRate * sqrt(1 - beta2^t) / (1 - beta1^t)
/// m[t] = beta1 * m[t-1] + (1 - beta1) * g
/// v[t] = beta2 * v[t-1] + (1 - beta2) * (g ^ 2)
/// maxVel[t] = max(maxVel[t-1], v[t])
/// variable = variable - lr[t] * m[t] / (sqrt(maxVel) + epsilon)
/// ```
/// - Parameters:
///   - learningRateTensor: scalar tensor which indicates the learning rate to use with the optimizer
///   - beta1Tensor: beta1Tensor
///   - beta2Tensor: beta2Tensor
///   - beta1PowerTensor: `beta1^t` beta1 power tensor
///   - beta2PowerTensor: `beta2^t` beta2 power tensor
///   - valuesTensor: values to update with optimization
///   - momentumTensor: momentum tensor
///   - velocityTensor: velocity tensor
///   - maximumVelocityTensor: optional maximum velocity tensor
///   - gradientTensor: partial gradient of the trainable parameters with respect to loss
///   - name: name for the operation
/// - Returns: if maximumVelocity is nil array of 3 tensors (update, newMomentum, newVelocity) else array of 4 tensors (update, newMomentum, newVelocity, newMaximumVelocity)
-(NSArray<MPSGraphTensor *> *) adamWithLearningRateTensor:(MPSGraphTensor *) learningRateTensor
                                              beta1Tensor:(MPSGraphTensor *) beta1Tensor
                                              beta2Tensor:(MPSGraphTensor *) beta2Tensor
                                            epsilonTensor:(MPSGraphTensor *) epsilonTensor
                                         beta1PowerTensor:(MPSGraphTensor *) beta1PowerTensor
                                         beta2PowerTensor:(MPSGraphTensor *) beta2PowerTensor
                                             valuesTensor:(MPSGraphTensor *) valuesTensor
                                           momentumTensor:(MPSGraphTensor *) momentumTensor
                                           velocityTensor:(MPSGraphTensor *) velocityTensor
                                    maximumVelocityTensor:(MPSGraphTensor * _Nullable) maximumVelocityTensor
                                           gradientTensor:(MPSGraphTensor *) gradientTensor
                                                     name:(NSString * _Nullable) name
MPS_SWIFT_NAME( adam(learningRate:beta1:beta2:epsilon:beta1Power:beta2Power:values:momentum:velocity:maximumVelocity:gradient:name:) );


/// Creates operations to apply Adam optimization.
///
/// The adam update ops are added
/// ```md
/// m[t] = beta1m[t-1] + (1 - beta1) * g
/// v[t] = beta2v[t-1] + (1 - beta2) * (g ^ 2)
/// maxVel[t] = max(maxVel[t-1],v[t]) 
/// variable = variable - lr[t] * m[t] / (sqrt(maxVel) + epsilon)
/// ```
/// - Parameters:
///   - learningRateTensor: scalar tensor which indicates the learning rate to use with the optimizer
///   - beta1Tensor: beta1Tensor
///   - beta2Tensor: beta2Tensor
///   - epsilonTensor: epsilon tensor
///   - valuesTensor: values to update with optimization
///   - momentumTensor: momentum tensor
///   - velocityTensor: velocity tensor
///   - maximumVelocityTensor: optional maximum velocity tensor
///   - gradientTensor: partial gradient of the trainable parameters with respect to loss
///   - name: name for the operation
/// - Returns: if maximumVelocity is nil array of 3 tensors (update, newMomentum, newVelocity) else array of 4 tensors (update, newMomentum, newVelocity, newMaximumVelocity)
-(NSArray<MPSGraphTensor *> *) adamWithCurrentLearningRateTensor:(MPSGraphTensor *) currentLearningRateTensor
                                                     beta1Tensor:(MPSGraphTensor *) beta1Tensor
                                                     beta2Tensor:(MPSGraphTensor *) beta2Tensor
                                                   epsilonTensor:(MPSGraphTensor *) epsilonTensor
                                                    valuesTensor:(MPSGraphTensor *) valuesTensor
                                                  momentumTensor:(MPSGraphTensor *) momentumTensor
                                                  velocityTensor:(MPSGraphTensor *) velocityTensor
                                           maximumVelocityTensor:(MPSGraphTensor * _Nullable) maximumVelocityTensor
                                                  gradientTensor:(MPSGraphTensor *) gradientTensor
                                                            name:(NSString * _Nullable) name
MPS_SWIFT_NAME( adam(currentLearningRate:beta1:beta2:epsilon:values:momentum:velocity:maximumVelocity:gradient:name:) );

@end

NS_ASSUME_NONNULL_END


#endif /* MPSGraphOptimizerOps_h */
