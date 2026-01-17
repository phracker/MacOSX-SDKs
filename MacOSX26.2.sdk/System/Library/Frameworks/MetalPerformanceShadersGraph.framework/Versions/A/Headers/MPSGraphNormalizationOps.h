//
//  MPSGraphNormalizationOps.h
//  MetalPerformanceShadersGraph
//
//  Created on 2/7/20.
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#ifndef MPSGraphNormalizationOps_h
#define MPSGraphNormalizationOps_h

#import <MetalPerformanceShadersGraph/MetalPerformanceShadersGraph.h>

NS_ASSUME_NONNULL_BEGIN

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(MPSGraphNormalizationOps)

/// Returns the mean of the first input along the specified axes.
///
/// - Parameters:
///   - axes: A list of axes over which to perform the reduction. The order of dimensions goes from the slowest moving at axis=0 to the fastest moving dimension.
///   - name: An optional name for the operation.
/// - Returns: A valid `MPSGraphTensor` object.
-(MPSGraphTensor *) meanOfTensor:(MPSGraphTensor *) tensor
                            axes:(NSArray<NSNumber *> *) axes
                            name:(NSString * _Nullable) name;

/// Returns the variance of the first input along the specified axes when the mean has been precomputed.
///
/// - Parameters:
///   - axes: A list of axes over which to perform the reduction such that the order of dimensions goes from the slowest moving at axis=0 to the fastest moving dimension.
///   - name: An optional name for the operation.
/// - Returns: A valid `MPSGraphTensor` object.
-(MPSGraphTensor *) varianceOfTensor:(MPSGraphTensor *) tensor
                          meanTensor:(MPSGraphTensor *) meanTensor
                                axes:(NSArray<NSNumber *> *) axes
                                name:(NSString * _Nullable) name;

/// Returns the variance of the first input along the specified axes.
///
/// - Parameters:
///   - axes: A list of axes over which to perform the reduction. Tthe order of dimensions goes from the slowest moving at axis=0 to the fastest moving dimension.
///   - name: An optional name for the operation.
/// - Returns: A valid `MPSGraphTensor` object.
-(MPSGraphTensor *) varianceOfTensor:(MPSGraphTensor *) tensor
                                axes:(NSArray<NSNumber *> *) axes
                                name:(NSString * _Nullable) name;

/// Creates a batch normalization operation and returns the result tensor.
///
/// The mean and variance tensors should be outputs of `meanWithTensor:axes:name` and `varianceWithTensor:meanTensor:axes:name`. 
/// Use the axes parameter to achieve different types of normalizations. 
/// For example (assuming your data is in NxHxWxC format) 
/// Batch normalization: axes = [0, 1, 2] 
/// Instance normalization: axes = [1, 2] 
/// Shapes for gamma and beta must match the input data along at least one dimension and will be broadcast along the rest. 
/// For batch normalization, gamma and beta would typically be 1x1x1xC i.e. one value per channel.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - mean: The mean tensor.
///   - variance: The variance tensor.
///   - gamma: The tensor used to scale the normalized result.
///   - beta: The tensor used to bias the normalized result.
///   - epsilon: A small value to add to the variance when normalizing the inputs.
///   - name: An optional name for the operation.
/// - Returns: A valid `MPSGraphTensor` object. 
///
-(MPSGraphTensor *) normalizationWithTensor:(MPSGraphTensor *) tensor
                                 meanTensor:(MPSGraphTensor *) mean
                             varianceTensor:(MPSGraphTensor *) variance
                                gammaTensor:(MPSGraphTensor * _Nullable) gamma
                                 betaTensor:(MPSGraphTensor * _Nullable) beta
                                    epsilon:(float) epsilon
                                       name:(NSString * _Nullable) name
MPS_SWIFT_NAME( normalize(_:mean:variance:gamma:beta:epsilon:name:) );

/// Creates a normalization gamma-gradient operation and returns the result tensor.
///
/// The mean and variance tensors should be outputs of ``meanWithTensor:axes:name`` and ``varianceWithTensor:meanTensor:axes:name``.
/// Use the axes parameter to achieve different types of normalizations.
/// For example (assuming your data is in `NxHxWxC` format)
/// Batch normalization: axes = [0, 1, 2]
/// Instance normalization: axes = [1, 2]
///
/// - Parameters:
///   - incomingGradientTensor: The incoming original `resultTensor` gradient.
///   - sourceTensor: The original input source in forward direction.
///   - meanTensor: The mean tensor.
///   - varianceTensor: The variance tensor.
///   - axes: The axes of normalization.
///   - epsilon: A small value to add to the variance when normalizing the inputs.
///   - name: An optional name for the operation.
/// - Returns: A valid `MPSGraphTensor` object.
///
-(MPSGraphTensor *) normalizationGammaGradientWithIncomingGradientTensor:(MPSGraphTensor *) incomingGradientTensor
                                                            sourceTensor:(MPSGraphTensor *) sourceTensor
                                                              meanTensor:(MPSGraphTensor *) meanTensor
                                                          varianceTensor:(MPSGraphTensor *) varianceTensor
                                                           reductionAxes:(NSArray<NSNumber *> *) axes
                                                                 epsilon:(float) epsilon
                                                                    name:(NSString * _Nullable) name;

/// Creates a normalization beta-gradient operation and returns the result tensor.
///
/// The mean and variance tensors should be outputs of ``meanWithTensor:axes:name`` and ``varianceWithTensor:meanTensor:axes:name``.
/// Use the axes parameter to achieve different types of normalizations.
/// For example (assuming your data is in `NxHxWxC` format)
/// Batch normalization: axes = [0, 1, 2]
/// Instance normalization: axes = [1, 2]
///
/// - Parameters:
///   - incomingGradientTensor: The incoming original `resultTensor` gradient.
///   - sourceTensor: The original input source in forward direction.
///   - axes: The axes of normalization.
///   - name: An optional name for the operation.
/// - Returns: A valid `MPSGraphTensor` object.
///
-(MPSGraphTensor *) normalizationBetaGradientWithIncomingGradientTensor:(MPSGraphTensor *) incomingGradientTensor
                                                           sourceTensor:(MPSGraphTensor *) sourceTensor
                                                          reductionAxes:(NSArray<NSNumber *> *) axes
                                                                   name:(NSString * _Nullable) name;
/// Creates a normalization input gradient operation and returns the result tensor.
///
/// The mean and variance tensors should be outputs of ``meanWithTensor:axes:name`` and ``varianceWithTensor:meanTensor:axes:name``.
/// Use the axes parameter to achieve different types of normalizations.
/// For example (assuming your data is in `NxHxWxC` format)
/// Batch normalization: axes = [0, 1, 2]
/// Instance normalization: axes = [1, 2]
///
/// - Parameters:
///   - incomingGradientTensor: The incoming original `resultTensor` gradient.
///   - sourceTensor: The original input source in forward direction.
///   - meanTensor: The mean tensor.
///   - varianceTensor: The variance tensor.
///   - gamma: The gamma tensor.
///   - gammaGradient: The `gammaGradient` tensor.
///   - betaGradient: The `betaGradient` tensor
///   - axes: The axes of normalization.
///   - epsilon: A small value to add to the variance when normalizing the inputs.
///   - name: An optional name for the operation.
///
-(MPSGraphTensor *) normalizationGradientWithIncomingGradientTensor:(MPSGraphTensor *) incomingGradientTensor
                                                       sourceTensor:(MPSGraphTensor *) sourceTensor
                                                         meanTensor:(MPSGraphTensor *) meanTensor
                                                     varianceTensor:(MPSGraphTensor *) varianceTensor
                                                        gammaTensor:(MPSGraphTensor * _Nullable) gamma
                                                gammaGradientTensor:(MPSGraphTensor * _Nullable) gammaGradient
                                                 betaGradientTensor:(MPSGraphTensor * _Nullable) betaGradient
                                                      reductionAxes:(NSArray<NSNumber *> *) axes
                                                            epsilon:(float) epsilon
                                                               name:(NSString * _Nullable) name;

@end

NS_ASSUME_NONNULL_END


#endif /* MPSGraphNormalizationOps_h */

