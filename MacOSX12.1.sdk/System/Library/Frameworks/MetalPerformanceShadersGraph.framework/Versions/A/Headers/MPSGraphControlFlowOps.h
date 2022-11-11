//
//  MPSGraphControlFlow.h
//  MPSGraph
//
//  Created by Dhruv Saksena on 12/27/20.
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#ifndef MPSGraphControlFlowOps_h
#define MPSGraphControlFlowOps_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

MPS_CLASS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
@interface MPSGraph(MPSGraphControlFlowOps)

/*!
 *  @abstract   Defines a scope where all the ops defined in this block get controlDependency operations
 *  @return     A valid MPSGraphTensor array with results forwarded to return of controlDependency call
 */
typedef NSArray<MPSGraphTensor *> * _Nonnull(^MPSGraphControlFlowDependencyBlock)();

/*!
 *  @abstract   Runs the graph for given feeds to return targetTensor values, ensuring all target operations also executed. This call blocks till execution has completed.
 *
 *  @param      operations                        Operations maked as control dependency for all ops created inside the dependent block
 *  @param      dependentBlock               MPSGraphControlFlowDependencyBlock which is provided by caller to create dependent ops
 *  @param      name                                      name of scope
 *
 *  @return     A valid MPSGraphTensor array with results returned from dependentBlock forwarded
 */
-(NSArray<MPSGraphTensor *> *) controlDependencyWithOperations:(NSArray<MPSGraphOperation *> *) operations
                                                dependentBlock:(MPSGraphControlFlowDependencyBlock) dependentBlock
                                                          name:(NSString * _Nullable) name;

/*! @abstract   A block to have if/else condition in it
 *  @return     results  If no error, the tensors returned by user. If not empty, user must define both then/else block,
 *              both should have same number of arguments and each corresponding argument should have same elementTypes.
 */
typedef NSArray<MPSGraphTensor *> * _Nonnull(^MPSGraphIfThenElseBlock)();

/*!
 *  @abstract   Add an if/then/else op to the graph
 *
 *  @param      predicateTensor             Tensor must have a single scalar value, used to decide between then/else branches
 *  @param      thenBlock                          If predicate is true operations in this block are executed
 *  @param      elseBlock                          If predicate is false operations in this block are executed
 *  @param      name                                     name of operation
 *
 *  @return     results  If no error, the tensors returned by user. If not empty, user must define both then/else block,
 *              both should have same number of arguments and each corresponding argument should have same elementTypes.
 */
-(NSArray<MPSGraphTensor *> *) ifWithPredicateTensor:(MPSGraphTensor *) predicateTensor
                                           thenBlock:(MPSGraphIfThenElseBlock) thenBlock
                                           elseBlock:(MPSGraphIfThenElseBlock _Nullable) elseBlock
                                                name:(NSString * _Nullable) name
MPS_SWIFT_NAME( if(_:then:else:name:) );

/*!
 *  @abstract   While loop before block, this block executes before the condition is evaluated for each iteration
 *
 *  @param      inputTensors                                     inputTensors to the whileConditionBlock, for the 1st iteration will be same as initialInputs passed to the whileLoop
 *  @param      resultTensors                                   A valid MPSGraphTensor array with results forwarded to after block or returned from the whileLoop depending on the predicateTensor.
 *                                           It will be empty and the caller block should fill it up before returning.
 *
 *  @return     Tensor MUST be set and have a single scalar value, used to decide between executing the bodyBlock or returning from the whileLoop
 */
typedef MPSGraphTensor *_Nonnull(^MPSGraphWhileBeforeBlock)(NSArray<MPSGraphTensor *> *inputTensors,
                                                            NSMutableArray<MPSGraphTensor *> *_Nonnull resultTensors);

/*!
 *  @abstract   While loop after block, this block executes after the condition is evaluated for each iteration
 *
 *  @param      bodyBlockArguments                             inputs to the body of the whileLoop passed by the conditionBlock return, should be the same element types as the return of the whileLoop
 *
 *  @return     A valid MPSGraphTensor array with results forwarded to condition block
 */
typedef NSArray<MPSGraphTensor *> * _Nonnull(^MPSGraphWhileAfterBlock)(NSArray<MPSGraphTensor *> *bodyBlockArguments);

/*!
 *  @abstract   Adds a whileLoop operation
 *
 *  @param      initialInputs                                         inputTensors to the whileBeforeBlock, for the 1st iteration will be same as initialInputs passed to the whileLoop
 *  @param      before                                                         beforeBlock, this will be run first and then call the afterBlock with results or return results from the loop
 *  @param      after                                                           afterBlock, this will execute after the condition evaluation
 *  @param      name                                                             name of operation
 *
 *  @return     A valid MPSGraphTensor array with results returned from the conditionBlock depending on the predicateTensor
 */
-(NSArray<MPSGraphTensor *> *) whileWithInitialInputs:(NSArray<MPSGraphTensor *> *) initialInputs
                                               before:(MPSGraphWhileBeforeBlock) before
                                                after:(MPSGraphWhileAfterBlock) after
                                                 name:(NSString * _Nullable) name
MPS_SWIFT_NAME( while(initialInputs:before:after:name:) );


/*!
 *  @abstract   A block for the body in the for loop
 *
 *  @param      index                                                       loopIndex per iteration, it is a scalar tensor
 *  @param      iterationArguments                          arguments for this iteration, same count and corresponding elementTypes as initialIterationArguments and return types of the forLoop
 *
 *  @return     A valid MPSGraphTensor array with same count and corresponding elementTypes as initialIterationArguments and return types of the forLoop
 */
typedef NSArray<MPSGraphTensor *> * _Nonnull(^MPSGraphForLoopBodyBlock)(MPSGraphTensor *index,
                                                                        NSArray<MPSGraphTensor *> *iterationArguments);

/*!
 *  @abstract   Adds a forLoop operation, The lower and upper bounds specify a half-open range: the range includes the lower bound but does not include the upper bound.
 *
 *  @param      lowerBound                                                   lowerBound value of the loop, this is a scalar tensor, this is the index the loop will start with
 *  @param      upperBound                                                   upperBound value of the loop, this is a scalar tensor
 *  @param      step                                                                step value of the loop, this is a scalar tensor and must be positive
 *  @param      initialBodyArguments                             initial set of iteration arguments passed to the bodyBlock of the for loop
 *  @param      body                                                                bodyBlock, this will execute the body of the forLoop
 *  @param      name                                                                name of operation
 *
 *  @return     A valid MPSGraphTensor array with same count and corresponding elementTypes as initialIterationArguments and return types of the forLoop
 */
-(NSArray<MPSGraphTensor *> *) forLoopWithLowerBound:(MPSGraphTensor *) lowerBound
                                          upperBound:(MPSGraphTensor *) upperBound
                                                step:(MPSGraphTensor *) step
                                initialBodyArguments:(NSArray<MPSGraphTensor *> *)initialBodyArguments
                                                body:(MPSGraphForLoopBodyBlock) body
                                                name:(NSString * _Nullable) name
MPS_SWIFT_NAME( for(lowerBound:upperBound:step:initialBodyArguments:body:name:) );

/*!
 *  @abstract   Adds a forLoop operation, with a specific number of iterations
 *
 *  @param      numberOfIterations                                tensor with number of iterations the loop will execute
 *  @param      initialBodyArguments                            initial set of iteration arguments passed to the bodyBlock of the for loop
 *  @param      body                                                                bodyBlock, this will execute the body of the forLoop, index will go from 0 to numberOfIterations-1
 *  @param      name                                                                name of operation
 *
 *  @return     A valid MPSGraphTensor array with same count and corresponding elementTypes as initialIterationArguments and return types of the forLoop
 */
-(NSArray<MPSGraphTensor *> *) forLoopWithNumberOfIterations:(MPSGraphTensor *) numberOfIterations
                                        initialBodyArguments:(NSArray<MPSGraphTensor *> *)initialBodyArguments
                                                        body:(MPSGraphForLoopBodyBlock) body
                                                        name:(NSString * _Nullable) name
MPS_SWIFT_NAME( for(numberOfIterations:initialBodyArguments:body:name:) );

@end

NS_ASSUME_NONNULL_END

#endif /* MPSGraphControlFlowOps_h */
