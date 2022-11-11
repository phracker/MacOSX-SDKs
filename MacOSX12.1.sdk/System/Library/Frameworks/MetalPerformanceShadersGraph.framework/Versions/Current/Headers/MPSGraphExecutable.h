//
//  MPSGraphExecutable.h
//  MPSGraph
//
//  Created by Dhruv Saksena on 4/11/21.
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#ifndef MPSGraphExecutable_h
#define MPSGraphExecutable_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

/*! @abstract   A notification when graph executable execution: has finished
 *  @param      results  If no error, the results produced by the graph operation.
 *  @param      error   If an error occurs, more information might be found here.
 */
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
typedef void (^MPSGraphExecutableCompletionHandler)(NSArray<MPSGraphTensorData *> * results,
                                                    NSError * _Nullable error);

/*! @abstract   A notification when graph executable execution: has finished
 *  @param      results  If no error, the results produced by the graph operation.
 *  @param      error   If an error occurs, more information might be found here.
 */
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
typedef void (^MPSGraphExecutableScheduledHandler)(NSArray<MPSGraphTensorData *> * results,
                                                   NSError * _Nullable error);

MPS_CLASS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
@interface MPSGraphExecutableExecutionDescriptor : NSObject

/*! @property   scheduledHandler
 *  @discussion scheduledHandler for the graph executable, default value is nil
 */
@property (readwrite, atomic) MPSGraphExecutableScheduledHandler scheduledHandler;

/*! @property   completionHandler
 *  @discussion completionHandler for the graph executable, default value is nil
 */
@property (readwrite, atomic) MPSGraphExecutableCompletionHandler completionHandler;

/*! @property   waitUntilCompleted
 *  @discussion waitUntilCompleted for the graph executable, default value is false
 */
@property (readwrite, atomic) BOOL waitUntilCompleted;

@end

/*! @class      MPSGraphExecutable
 *  @abstract   Compiled representation of a compute graph executable
 *  @discussion An MPSGraphExecutable is a compiled graph for specific feeds for  specific targetTensors and targetOperations
 *
 */
MPS_CLASS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
@interface MPSGraphExecutable : NSObject

/*! @property   options
 *  @discussion options for the graph, default value is MPSGraphOptionsDefault
 */
@property (readwrite, atomic) MPSGraphOptions options;

/*! @property   feedTensors
 *  @discussion feedTensors for the graph, can be used to order the inputs when executable was created with an MPSGraph
 */
@property (readonly, atomic, nullable) NSArray<MPSGraphTensor *> *feedTensors;

/*! @property   targetTensors
 *  @discussion targetTensors for the graph, can be used to order the outputs when executable was created with an MPSGraph
 */
@property (readonly, atomic, nullable) NSArray<MPSGraphTensor *> *targetTensors;

/*!
 *  @abstract   Specialize MLIR module and optimize it
 *
 *  @param      device                                   optional MPSGraph device to compile with
 *  @param      inputTypes                          input types
 *
 */
-(void) specializeWithDevice:(MPSGraphDevice * _Nullable) device
                  inputTypes:(NSArray<MPSGraphType *> *) inputTypes
       compilationDescriptor:(MPSGraphCompilationDescriptor * _Nullable) compilationDescriptor;

/*!
 *  @abstract   Runs the graph for given feeds to return targetTensor values, ensuring all target operations also executed.
 *              This call  is synchronous and will return on completion of execution
 *
 *  @param      commandQueue                                       CommandQueue passed to exectute the graph on
 *  @param      inputsArray                                         Feeds tensorData for the placeholder tensors, same order as arguments of main function
 *  @param      resultsArray                                       Results tensorData for which the caller wishes MPSGraphTensorData to be returned
 *
 *  @return     A valid MPSGraphTensorData array with results synchronized to the CPU memory if MPSGraphOptionsSynchronizeResults set.
 */
-(NSArray<MPSGraphTensorData *> *) runWithMTLCommandQueue:(id<MTLCommandQueue>) commandQueue
                                              inputsArray:(NSArray<MPSGraphTensorData *> *) inputsArray
                                             resultsArray:(NSArray<MPSGraphTensorData *> * _Nullable) resultsArray
                                      executionDescriptor:(MPSGraphExecutableExecutionDescriptor * _Nullable) executionDescriptor
MPS_SWIFT_NAME( run(with:inputs:results:executionDescriptor:) );

/*!
 *  @abstract   Runs the graph for given feeds to return targetTensor values, ensuring all target operations also executed.
 *              This call  is asynchronous and will return immediately if a completionHandler is set.
 *
 *  @param      commandQueue                                      CommandQueue passed to exectute the graph on
 *  @param      inputsArray                                         Feeds tensorData for the placeholder tensors, same order as arguments of main function
 *  @param      resultsArray                                      Tensors for which the caller wishes MPSGraphTensorData to be returned
 *  @param      executionDescriptor                       ExecutionDescriptor to be passed in and used,
 *
 *  @return     A valid MPSGraphTensorData array with results synchronized to the CPU memory if MPSGraphOptionsSynchronizeResults set.
 */
-(NSArray<MPSGraphTensorData *> *) runAsyncWithMTLCommandQueue:(id<MTLCommandQueue>) commandQueue
                                                   inputsArray:(NSArray<MPSGraphTensorData *> *) inputsArray
                                                  resultsArray:(NSArray<MPSGraphTensorData *> * _Nullable) resultsArray
                                           executionDescriptor:(MPSGraphExecutableExecutionDescriptor * _Nullable) executionDescriptor
MPS_SWIFT_NAME( runAsync(with:inputs:results:executionDescriptor:) );

/*!
 *  @abstract   Runs the graph for given feeds to return targetTensor values, ensuring all target operations also executed.
 *              This call  is asynchronous and will return immediately if a completionHandler is set.
 *
 *  @param      commandBuffer                                     commandBuffer passed to exectute the graph on, commitAndContinue might be called, please don't rely on underlying MTLCommandBuffer to remain uncommitted
 *  @param      inputsArray                                         Feeds tensorData for the placeholder tensors, same order as arguments of main function
 *  @param      resultsArray                                      Tensors for which the caller wishes MPSGraphTensorData to be returned
 *  @param      executionDescriptor                       ExecutionDescriptor to be passed in and used,
 *
 *  @return     A valid MPSGraphTensorData array with results synchronized to the CPU memory if MPSGraphOptionsSynchronizeResults set.
 */
-(NSArray<MPSGraphTensorData *> *) encodeToCommandBuffer:(MPSCommandBuffer *) commandBuffer
                                             inputsArray:(NSArray<MPSGraphTensorData *> *) inputsArray
                                            resultsArray:(NSArray<MPSGraphTensorData *> * _Nullable) resultsArray
                                     executionDescriptor:(MPSGraphExecutableExecutionDescriptor * _Nullable) executionDescriptor
MPS_SWIFT_NAME( encode(to:inputs:results:executionDescriptor:) );

@end


NS_ASSUME_NONNULL_END

#endif /* MPSGraphExecutable_h */
