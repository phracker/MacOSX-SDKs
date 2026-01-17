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

/// Creates a reduction sum operation and returns the result tensor.
///
/// - Parameters:
///   - tensor: input tensor
///   - axis: axis of reduction
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
- (MPSGraphTensor *) reductionSumWithTensor:(MPSGraphTensor *) tensor
                                       axis:(NSInteger) axis
                                       name:(NSString * _Nullable) name;

/// Creates a reduction sum operation and returns the result tensor.
///
/// - Parameters:
///   - tensor: input tensor
///   - axes: axes of reduction
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
- (MPSGraphTensor *) reductionSumWithTensor:(MPSGraphTensor *)tensor
                                       axes:(NSArray<NSNumber *> *_Nullable)axes
                                       name:(NSString *_Nullable)name;

/// Creates a reduction max operation and returns the result tensor.
///
/// - Parameters:
///   - tensor: input tensor
///   - axis: axis of reduction
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) reductionMaximumWithTensor:(MPSGraphTensor *) tensor
                                          axis:(NSInteger) axis
                                          name:(NSString * _Nullable) name;

/// Creates a reduction max operation and returns the result tensor.
///
/// - Parameters:
///   - tensor: input tensor
///   - axes: axes of reduction
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
- (MPSGraphTensor *) reductionMaximumWithTensor:(MPSGraphTensor *)tensor
                                           axes:(NSArray<NSNumber *> *_Nullable)axes
                                           name:(NSString *_Nullable)name;

/// Creates a reduction minimum operation and returns the result tensor.
///
/// - Parameters:
///   - tensor: input tensor
///   - axis: axis of reduction
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
- (MPSGraphTensor *) reductionMinimumWithTensor:(MPSGraphTensor *) tensor
                                           axis:(NSInteger) axis
                                           name:(NSString * _Nullable) name;

/// Creates a reduction min operation and returns the result tensor.
///
/// - Parameters:
///   - tensor: input tensor
///   - axes: axes of reduction
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) reductionMinimumWithTensor:(MPSGraphTensor *)tensor
                                          axes:(NSArray<NSNumber *> *_Nullable)axes
                                          name:(NSString *_Nullable)name;

/// Creates a reduction max propagate NaN operation and returns the result tensor.
///
/// - Parameters:
///   - tensor: input tensor
///   - axis: axis of reduction
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
- (MPSGraphTensor *) reductionMaximumPropagateNaNWithTensor:(MPSGraphTensor *) tensor
                                                       axis:(NSInteger) axis
                                                       name:(NSString * _Nullable) name;

/// Creates a reduction max propagate NaN operation and returns the result tensor.
///
/// - Parameters:
///   - tensor: input tensor
///   - axes: axes of reduction
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
- (MPSGraphTensor *) reductionMaximumPropagateNaNWithTensor:(MPSGraphTensor *)tensor
                                                       axes:(NSArray<NSNumber *> *_Nullable)axes
                                                       name:(NSString *_Nullable)name;

/// Creates a reduction min propagate NaN operation and returns the result tensor.
///
/// - Parameters:
///   - tensor: input tensor
///   - axis: axis of reduction
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
- (MPSGraphTensor *) reductionMinimumPropagateNaNWithTensor:(MPSGraphTensor *) tensor
                                                       axis:(NSInteger) axis
                                                       name:(NSString * _Nullable) name;

/// Creates a reduction min propagate NaN operation and returns the result tensor.
///
/// - Parameters:
///   - tensor: input tensor
///   - axes: axes of reduction
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
- (MPSGraphTensor *) reductionMinimumPropagateNaNWithTensor:(MPSGraphTensor *)tensor
                                                       axes:(NSArray<NSNumber *> *_Nullable)axes
                                                       name:(NSString *_Nullable)name;

/// Creates a reduction product operation and returns the result tensor.
///
/// - Parameters:
///   - tensor: input tensor
///   - axis: axis of reduction
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) reductionProductWithTensor:(MPSGraphTensor *) tensor
                                          axis:(NSInteger) axis
                                          name:(NSString * _Nullable) name;


/// Creates a reduction product operation and returns the result tensor.
///
/// - Parameters:
///   - tensor: input tensor
///   - axes: axes of reduction
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
- (MPSGraphTensor *) reductionProductWithTensor:(MPSGraphTensor *)tensor
                                           axes:(NSArray<NSNumber *> *_Nullable)axes
                                           name:(NSString *_Nullable)name;

/// Creates a reduction argMax operation and returns the result tensor.
///
/// - Parameters:
///   - tensor: input tensor
///   - axis: axis of reduction
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
- (MPSGraphTensor *) reductionArgMaximumWithTensor:(MPSGraphTensor *)tensor
                                              axis:(NSInteger)axis
                                              name:(NSString *_Nullable)name
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), macCatalyst(15.0), tvos(15.0));

/// Creates a reduction argMin operation and returns the result tensor.
///
/// - Parameters:
///   - tensor: input tensor
///   - axis: axis of reduction
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) reductionArgMinimumWithTensor:(MPSGraphTensor *)tensor
                                             axis:(NSInteger)axis
                                             name:(NSString *_Nullable)name
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), macCatalyst(15.0), tvos(15.0));

/// Creates a reduction and operation and returns the result tensor.
///
/// - Parameters:
///   - tensor: input tensor
///   - axis: axis of reduction
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
- (MPSGraphTensor *) reductionAndWithTensor:(MPSGraphTensor *) tensor
                                       axis:(NSInteger) axis
                                       name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.2), ios(15.3), macCatalyst(15.3), tvos(15.3));


/// Creates a reduction and operation and returns the result tensor.
///
/// - Parameters:
///   - tensor: input tensor
///   - axes: axes of reduction
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
- (MPSGraphTensor *) reductionAndWithTensor:(MPSGraphTensor *)tensor
                                       axes:(NSArray<NSNumber *> *_Nullable)axes
                                       name:(NSString *_Nullable)name
MPS_AVAILABLE_STARTING(macos(12.2), ios(15.3), macCatalyst(15.3), tvos(15.3));

/// Creates a reduction or operation and returns the result tensor.
///
/// - Parameters:
///   - tensor: input tensor
///   - axis: axis of reduction
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
- (MPSGraphTensor *) reductionOrWithTensor:(MPSGraphTensor *) tensor
                                      axis:(NSInteger) axis
                                      name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.2), ios(15.3), macCatalyst(15.3), tvos(15.3));


/// Creates a reduction or operation and returns the result tensor.
///
/// - Parameters:
///   - tensor: input tensor
///   - axes: axes of reduction
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
- (MPSGraphTensor *) reductionOrWithTensor:(MPSGraphTensor *)tensor
                                      axes:(NSArray<NSNumber *> *_Nullable)axes
                                      name:(NSString *_Nullable)name
MPS_AVAILABLE_STARTING(macos(12.2), ios(15.3), macCatalyst(15.3), tvos(15.3));

@end

NS_ASSUME_NONNULL_END

#endif /* MPSGraphReductionOps_h */
