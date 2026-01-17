//
//  MPSGraphControlFlow.h
//  MPSGraph
//
//  Created on 12/27/20.
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#ifndef MPSGraphControlFlowOps_h
#define MPSGraphControlFlowOps_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

MPS_CLASS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
@interface MPSGraph(MPSGraphControlFlowOps)

/// The scope where all the operations defined in this block get control-dependency operations.
///
/// - Returns: A valid tensor with the results forwarded to the return of `controlDependency` call.
typedef NSArray<MPSGraphTensor *> * _Nonnull(^MPSGraphControlFlowDependencyBlock)();

/// Runs the graph for the given feeds and returns the target tensor values, ensuring all target operations also executed. 
///
/// This call blocks until execution has completed.
///
/// - Parameters:
///   - operations: Operations maked as control dependency for all ops created inside the dependent block
///   - dependentBlock: MPSGraphControlFlowDependencyBlock which is provided by caller to create dependent ops
///   - name: name of scope
/// - Returns: A valid MPSGraphTensor array with results returned from dependentBlock forwarded
-(NSArray<MPSGraphTensor *> *) controlDependencyWithOperations:(NSArray<MPSGraphOperation *> *) operations
                                                dependentBlock:(MPSGraphControlFlowDependencyBlock) dependentBlock
                                                          name:(NSString * _Nullable) name;

/// A block of operations executed under either the if or else condition.
///
/// - Returns: Tensors returned by user. If not empty, the user must define both the then and else blocks,
/// both should have the same number of arguments, and each corresponding argument should have the same element types.
typedef NSArray<MPSGraphTensor *> * _Nonnull(^MPSGraphIfThenElseBlock)();

/// Adds an if-then-else operation to the graph.
///
/// - Parameters:
///   - predicateTensor: Tensor must have a single scalar value, used to decide between then/else branches
///   - thenBlock: If predicate is true operations in this block are executed
///   - elseBlock: If predicate is false operations in this block are executed
///   - name: name of operation
/// - Returns: results If no error, the tensors returned by user. If not empty, user must define both then/else block, 
/// both should have same number of arguments and each corresponding argument should have same elementTypes.
-(NSArray<MPSGraphTensor *> *) ifWithPredicateTensor:(MPSGraphTensor *) predicateTensor
                                           thenBlock:(MPSGraphIfThenElseBlock) thenBlock
                                           elseBlock:(MPSGraphIfThenElseBlock _Nullable) elseBlock
                                                name:(NSString * _Nullable) name
MPS_SWIFT_NAME( if(_:then:else:name:) );

/// The block that executes before the condition evaluates for each iteration.
///
/// - Parameters:
///   - inputTensors: Input tensors to the `whileConditionBlock`, for the first iteration will be same as initialInputs passed to the while loop.
///   - resultTensors: A valid `MPSGraphTensor` array with results forwarded to after block or returned from the while loop depending on the predicate tensor. It will be empty and the caller block should fill it up before returning.
/// - Returns: Tensor MUST be set and have a single scalar value, used to decide between executing the body block or returning from the while loop.
typedef MPSGraphTensor *_Nonnull(^MPSGraphWhileBeforeBlock)(NSArray<MPSGraphTensor *> *inputTensors,
                                                            NSMutableArray<MPSGraphTensor *> *_Nonnull resultTensors);

/// The block that executes after the condition evaluates for each iteration.
///
/// - Parameters:
///   - bodyBlockArguments: Inputs to the body of the while loop passed by the condition block return, and should be the same element types as the return of the while loop.
/// - Returns: A valid `MPSGraphTensor` array with results forwarded to the condition block.
typedef NSArray<MPSGraphTensor *> * _Nonnull(^MPSGraphWhileAfterBlock)(NSArray<MPSGraphTensor *> *bodyBlockArguments);

/// Adds a while loop operation.
///
/// - Parameters:
///   - initialInputs: inputTensors to the `beforeBlock`, for the 1st iteration will be same as initialInputs passed to the while loop.
///   - before: `beforeBlock`, this will be run first and then call the `afterBlock` with results or return results from the loop.
///   - after: `afterBlock`, this will execute after the condition evaluation.
///   - name: name of operation.
/// - Returns: A valid MPSGraphTensor array with results returned from the conditionBlock depending on the predicate tensor.
-(NSArray<MPSGraphTensor *> *) whileWithInitialInputs:(NSArray<MPSGraphTensor *> *) initialInputs
                                               before:(MPSGraphWhileBeforeBlock) before
                                                after:(MPSGraphWhileAfterBlock) after
                                                 name:(NSString * _Nullable) name
MPS_SWIFT_NAME( while(initialInputs:before:after:name:) );


/// A block for the body in the for loop.
///
/// - Parameters:
///   - index: The for loop index per iteration, it is a scalar tensor.
///   - iterationArguments: Arguments for this iteration, with the same count and corresponding element types as `initialIterationArguments` and return types of the `for` loop.
/// - Returns: A valid MPSGraphTensor array with same count and corresponding element types as `initialIterationArguments` and return types of the `for` loop.
typedef NSArray<MPSGraphTensor *> * _Nonnull(^MPSGraphForLoopBodyBlock)(MPSGraphTensor *index,
                                                                        NSArray<MPSGraphTensor *> *iterationArguments);

/// Adds a for loop operation, The lower and upper bounds specify a half-open range: the range includes the lower bound but does not include the upper bound.
///
/// - Parameters:
///   - lowerBound: Lower bound value of the loop, this is a scalar tensor, this is the index the loop will start with.
///   - upperBound: Upper bound value of the loop, this is a scalar tensor.
///   - step: Step value of the loop, this is a scalar tensor and must be positive.
///   - initialBodyArguments: initial set of iteration arguments passed to the bodyBlock of the for loop.
///   - body: This block will execute the body of the for loop.
///   - name: name of operation.
/// - Returns: A valid `MPSGraphTensor` array with same count and corresponding element types as `initialIterationArguments` and return types of the for loop.
-(NSArray<MPSGraphTensor *> *) forLoopWithLowerBound:(MPSGraphTensor *) lowerBound
                                          upperBound:(MPSGraphTensor *) upperBound
                                                step:(MPSGraphTensor *) step
                                initialBodyArguments:(NSArray<MPSGraphTensor *> *)initialBodyArguments
                                                body:(MPSGraphForLoopBodyBlock) body
                                                name:(NSString * _Nullable) name
MPS_SWIFT_NAME( for(lowerBound:upperBound:step:initialBodyArguments:body:name:) );

/// Adds a for loop operation, with a specific number of iterations.
///
/// - Parameters:
///   - numberOfIterations: tensor with number of iterations the loop will execute
///   - initialBodyArguments: initial set of iteration arguments passed to the bodyBlock of the for loop
///   - body: bodyBlock, this will execute the body of the for loop, index will go from 0 to numberOfIterations-1
///   - name: name of operation
/// - Returns: A valid MPSGraphTensor array with same count and corresponding elementTypes as initialIterationArguments and return types of the for loop
-(NSArray<MPSGraphTensor *> *) forLoopWithNumberOfIterations:(MPSGraphTensor *) numberOfIterations
                                        initialBodyArguments:(NSArray<MPSGraphTensor *> *)initialBodyArguments
                                                        body:(MPSGraphForLoopBodyBlock) body
                                                        name:(NSString * _Nullable) name
MPS_SWIFT_NAME( for(numberOfIterations:initialBodyArguments:body:name:) );

@end

NS_ASSUME_NONNULL_END

#endif /* MPSGraphControlFlowOps_h */
