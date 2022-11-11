//
//  MPSGraph.h
//  MetalPerformanceShadersGraph
//
//  Created on 11/10/19.
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#ifndef MPSGraph_h
#define MPSGraph_h

#import <MetalPerformanceShadersGraph/MPSGraphCore.h>
#import <MetalPerformanceShadersGraph/MPSGraphDevice.h>
#import <MetalPerformanceShadersGraph/MPSGraphTensor.h>
#import <MetalPerformanceShadersGraph/MPSGraphTensorData.h>
#import <MetalPerformanceShadersGraph/MPSGraphOperation.h>

NS_ASSUME_NONNULL_BEGIN

@class MPSGraphExecutable;

/*!
 *  @typedef    MPSGraphOptions
 *  @abstract   Options to be utilized by the graph
 *
 *  @constant   MPSGraphOptionsNone                                   No Options
 *  @constant   MPSGraphOptionsSynchronizeResults            Synchronize results using a blit encoder if on a GPU
 *  @constant   MPSGraphOptionsVerbose                               Prints more logging info
 */
typedef NS_ENUM(uint64_t, MPSGraphOptions)
{
    MPSGraphOptionsNone                                            MPS_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0)) MPS_SWIFT_NAME(none) =   0,
    MPSGraphOptionsSynchronizeResults                              MPS_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))                      =   1L,
    MPSGraphOptionsVerbose                                         MPS_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))                      =   2L,
    
    MPSGraphOptionsDefault                                         MPS_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))                      =   MPSGraphOptionsSynchronizeResults,
};

/*!
 *  @typedef    MPSGraphOptimization
 *  @abstract   Optimization levels
 *
 *  @constant   MPSGraphOptimizationLevel0                               Default optimizations
 *  @constant   MPSGraphOptimizationLevel1                               Additional Optimizations
 */
typedef NS_ENUM(uint64_t, MPSGraphOptimization)
{
    MPSGraphOptimizationLevel0                        MPS_ENUM_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4)) MPS_SWIFT_NAME(level0) =   0,
    MPSGraphOptimizationLevel1                        MPS_ENUM_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4))                        =   1L,
};

/*!
 *  @typedef    MPSGraphOptimizationProfile
 *  @abstract   Optimization profile used as heuristic as graph compiler optimizes network
 *
 *  @constant   MPSGraphOptimizationProfilePerformance                               Default, optimize for performance
 *  @constant   MPSGraphOptimizationProfilePowerEfficiency                          optimize for power efficiency
 */
typedef NS_ENUM(uint64_t, MPSGraphOptimizationProfile)
{
    MPSGraphOptimizationProfilePerformance                        MPS_ENUM_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4)) MPS_SWIFT_NAME(performance) =   0,
    MPSGraphOptimizationProfilePowerEfficiency                    MPS_ENUM_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4))                             =   1L,
};

/*! @abstract   A dictionary of tensors and correspondiing tensorData for them
 */
MPS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
typedef NSDictionary<MPSGraphTensor*, MPSGraphTensorData *> MPSGraphTensorDataDictionary;

/*! @abstract   A dictionary of tensors and correspondiing shapes for them
 */
MPS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
typedef NSDictionary<MPSGraphTensor*, MPSGraphShapedType *> MPSGraphTensorShapedTypeDictionary;

/*! @abstract   A notification when graph execution: has finished
 *  @param      resultsDictionary  If no error, the image produced by the graph operation.
 *  @param      error   If an error occurs, more information might be found here.
 */
typedef void (^MPSGraphCompletionHandler)(MPSGraphTensorDataDictionary * resultsDictionary,
                                          NSError * _Nullable error);

/*! @abstract   A notification when graph execution: has finished
 *  @param      resultsDictionary  If no error, the image produced by the graph operation.
 *  @param      error   If an error occurs, more information might be found here.
 */
typedef void (^MPSGraphScheduledHandler)(MPSGraphTensorDataDictionary * resultsDictionary,
                                         NSError * _Nullable error);

/*! @class      MPSGraphCompilationDescriptor
 *  @abstract   A structure which consists of all the levers users can use to compile their graphs
 *
 */
MPS_CLASS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
@interface MPSGraphCompilationDescriptor : NSObject <NSCopying>

/*!
 *  @brief Turns off type inference and we rely on type inference during runtime
 */
-(void) disableTypeInference;

/*! @property   optimizationLevel
 *  @discussion optimization level for the graph execution, default is MPSGraphOptimizationLevel0
 */
@property (readwrite, nonatomic) MPSGraphOptimization optimizationLevel MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

/*! @property   optimizationProfile
 *  @discussion optimization profile for the graph optimization, default is MPSGraphOptimizationProfilePerformance
 */
@property (readwrite, nonatomic) MPSGraphOptimizationProfile optimizationProfile MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

@end

/*! @class      MPSGraphExecutionDescriptor
 *  @abstract   A structure which consists of all the levers users can use to synchronize and schedule their graph execution
 *
 */
MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraphExecutionDescriptor : NSObject

/*! @property   scheduledHandler
 *  @discussion scheduledHandler for the graph, default value is nil
 */
@property (readwrite, atomic) MPSGraphScheduledHandler scheduledHandler;

/*! @property   completionHandler
 *  @discussion completionHandler for the graph, default value is nil
 */
@property (readwrite, atomic) MPSGraphCompletionHandler completionHandler;

/*! @property   waitUntilCompleted
 *  @discussion waitUntilCompleted for the graph, default value is false
 */
@property (readwrite, atomic) BOOL waitUntilCompleted;

/*! @property   compilationDescriptor
 *  @discussion compilationDescriptor for the graph, default value is nil
 */
@property (readwrite, atomic, copy, nullable) MPSGraphCompilationDescriptor *compilationDescriptor
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

@end

/*! @class      MPSGraph
 *  @abstract   Optimized representation of a compute graph of MPSGraphOperations and MPSGraphTensors
 *  @discussion An MPSGraph is a symbolic representation of operations to be utilized to execute compute graphs on a device.
 *
 */
MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph : NSObject

/*! @property   options
 *  @discussion options for the graph, default value is MPSGraphOptionsDefault
 */
@property (readwrite, atomic) MPSGraphOptions options;

/*!
 *  @brief Create a new MPSGraph to insert nodes in
 */
+(instancetype) new;

/*!
 *  @brief Initialize an MPSGraph to insert nodes in
 */
-(instancetype) init;

/*! @property   placeholderTensors
 *  @discussion an array of all the placeholderTensors
 */
@property (readonly, nonnull, nonatomic) NSArray<MPSGraphTensor *> *placeholderTensors;

/*!
 *  @abstract   Compiles the graph for given feeds to return targetTensor values, ensuring all target operations would be executed. This call blocks till execution has completed.
 *
 *  @param      device                                                     MPSGraph device to optimize for
 *  @param      feeds                                                       Feeds dictionary for the placeholder tensors
 *  @param      targetTensors                                     Tensors for which the caller wishes MPSGraphTensorData to be returned
 *  @param      targetOperations                              Operations to be completed at the end of the run
 *  @param      compilationDescriptor                   compilation descriptor
 *
 *  @return     A valid MPSGraphExecutable object
 */
-(MPSGraphExecutable *) compileWithDevice:(MPSGraphDevice * _Nullable) device
                                    feeds:(MPSGraphTensorShapedTypeDictionary *) feeds
                            targetTensors:(NSArray<MPSGraphTensor *> *) targetTensors
                         targetOperations:(NSArray<MPSGraphOperation *> * _Nullable) targetOperations
                    compilationDescriptor:(MPSGraphCompilationDescriptor * _Nullable) compilationDescriptor MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/*!
 *  @abstract   Runs the graph for given feeds to return targetTensor values, ensuring all target operations also executed. This call blocks till execution has completed.
 *
 *  @param      feeds                                                       Feeds dictionary for the placeholder tensors
 *  @param      targetTensors                                     Tensors for which the caller wishes MPSGraphTensorData to be returned
 *  @param      targetOperations                              Operations to be completed at the end of the run
 *
 *  @return     A valid MPSGraphTensor : MPSGraphTensorData dictionary with results synchronized to the CPU memory.
 */
-(MPSGraphTensorDataDictionary *) runWithFeeds:(MPSGraphTensorDataDictionary *) feeds
                                 targetTensors:(NSArray<MPSGraphTensor *> *) targetTensors
                              targetOperations:(NSArray<MPSGraphOperation *> * _Nullable) targetOperations
MPS_SWIFT_NAME( run(feeds:targetTensors:targetOperations:) );

/*!
 *  @abstract   Runs the graph for given feeds to return targetTensor values, ensuring all target operations also executed. This call blocks till execution has completed.
 *
 *  @param      commandQueue                                       CommandQueue passed to exectute the graph on
 *  @param      feeds                                                       Feeds dictionary for the placeholder tensors
 *  @param      targetTensors                                     Tensors for which the caller wishes MPSGraphTensorData to be returned
 *  @param      targetOperations                              Operations to be completed at the end of the run
 *
 *  @return     A valid MPSGraphTensor : MPSGraphTensorData dictionary with results synchronized to the CPU memory.
 */
-(MPSGraphTensorDataDictionary *) runWithMTLCommandQueue:(id<MTLCommandQueue>) commandQueue
                                                   feeds:(MPSGraphTensorDataDictionary *) feeds
                                           targetTensors:(NSArray<MPSGraphTensor *> *) targetTensors
                                        targetOperations:(NSArray<MPSGraphOperation *> * _Nullable) targetOperations
MPS_SWIFT_NAME( run(with:feeds:targetTensors:targetOperations:) );

/*!
 *  @abstract   Runs the graph for given feeds to return targetTensor values in the resultsDictionary provided by the user,
 *              ensuring all target operations also executed. This call blocks till execution has completed.
 *
 *  @param      commandQueue                                       CommandQueue passed to exectute the graph on
 *  @param      feeds                                                       Feeds dictionary for the placeholder tensors
 *  @param      targetOperations                              Operations to be completed at the end of the run
 *  @param      resultsDictionary                            MPSGraphTensors dictionary passed by user, these will be filled with graph output data
 *
 */
-(void) runWithMTLCommandQueue:(id<MTLCommandQueue>) commandQueue
                         feeds:(MPSGraphTensorDataDictionary *) feeds
              targetOperations:(NSArray<MPSGraphOperation *> * _Nullable) targetOperations
             resultsDictionary:(MPSGraphTensorDataDictionary *) resultsDictionary
MPS_SWIFT_NAME( run(with:feeds:targetOperations:resultsDictionary:) );


// Async methods

/*!
 *  @abstract   Runs the graph for given feeds to return targetTensor values, ensuring all target operations also executed.
 *              This call  is asynchronous and will return immediately if a completionHandler is set.
 *
 *  @param      feeds                                                       Feeds dictionary for the placeholder tensors
 *  @param      targetTensors                                     Tensors for which the caller wishes MPSGraphTensorData to be returned
 *  @param      targetOperations                              Operations to be completed at the end of the run
 *  @param      executionDescriptor                       ExecutionDescriptor to be passed in and used,
 *
 *  @return     A valid MPSGraphTensor : MPSGraphTensorData dictionary with results synchronized to the CPU memory.
 */
-(MPSGraphTensorDataDictionary *) runAsyncWithFeeds:(MPSGraphTensorDataDictionary *) feeds
                                      targetTensors:(NSArray<MPSGraphTensor *> *) targetTensors
                                   targetOperations:(NSArray<MPSGraphOperation *> * _Nullable) targetOperations
                                executionDescriptor:(MPSGraphExecutionDescriptor * _Nullable) executionDescriptor
MPS_SWIFT_NAME( runAsync(feeds:targetTensors:targetOperations:executionDescriptor:) );


/*!
 *  @abstract   Runs the graph for given feeds to return targetTensor values, ensuring all target operations also executed.
 *              This call  is asynchronous and will return immediately if a completionHandler is set.
 *
 *  @param      commandQueue                                       CommandQueue passed to exectute the graph on
 *  @param      feeds                                                       Feeds dictionary for the placeholder tensors
 *  @param      targetTensors                                     Tensors for which the caller wishes MPSGraphTensorData to be returned
 *  @param      targetOperations                              Operations to be completed at the end of the run
 *  @param      executionDescriptor                       ExecutionDescriptor to be passed in and used,
 *
 *  @return     A valid MPSGraphTensor : MPSGraphTensorData dictionary with results synchronized to the CPU memory if MPSGraphOptionsSynchronizeResults set.
 */
-(MPSGraphTensorDataDictionary *) runAsyncWithMTLCommandQueue:(id<MTLCommandQueue>) commandQueue
                                                        feeds:(MPSGraphTensorDataDictionary *) feeds
                                                targetTensors:(NSArray<MPSGraphTensor *> *) targetTensors
                                             targetOperations:(NSArray<MPSGraphOperation *> * _Nullable) targetOperations
                                          executionDescriptor:(MPSGraphExecutionDescriptor * _Nullable) executionDescriptor
MPS_SWIFT_NAME( runAsync(with:feeds:targetTensors:targetOperations:executionDescriptor:) );

/*!
 *  @abstract   Runs the graph for given feeds to return targetTensor values in the resultsDictionary provided by the user,
 *              ensuring all target operations also executed. This call  is asynchronous and will return immediately if a completionHandler is set.
 *
 *  @param      commandQueue                                       CommandQueue passed to exectute the graph on
 *  @param      feeds                                                       Feeds dictionary for the placeholder tensors
 *  @param      targetOperations                              Operations to be completed at the end of the run
 *  @param      resultsDictionary                            MPSGraphTensors dictionary passed by user, these will be filled with graph output data
 *  @param      executionDescriptor                       ExecutionDescriptor to be passed in and used,
 *
 */
-(void) runAsyncWithMTLCommandQueue:(id<MTLCommandQueue>) commandQueue
                              feeds:(MPSGraphTensorDataDictionary *) feeds
                   targetOperations:(NSArray<MPSGraphOperation *> * _Nullable) targetOperations
                  resultsDictionary:(MPSGraphTensorDataDictionary *) resultsDictionary
                executionDescriptor:(MPSGraphExecutionDescriptor * _Nullable) executionDescriptor
MPS_SWIFT_NAME( runAsync(with:feeds:targetOperations:resultsDictionary:executionDescriptor:) );

/*!
 *  @abstract   Encodes graph for given feeds to return targetTensor values, ensuring all target operations also executed.
 *              This call  is asynchronous and will return immediately if a completionHandler is set.
 *
 *  @param      commandBuffer                                      commandBuffer passed to exectute the graph on, it is an MPSCommandBuffer, commitAndContinue might be called, please don't rely on underlying MTLCommandBuffer to remain uncommitted
 *  @param      feeds                                                       Feeds dictionary for the placeholder tensors
 *  @param      targetTensors                                     Tensors for which the caller wishes MPSGraphTensorData to be returned
 *  @param      targetOperations                              Operations to be completed at the end of the run
 *  @param      executionDescriptor                       ExecutionDescriptor to be passed in and used,
 *
 *  @return     A valid MPSGraphTensor : MPSGraphTensorData dictionary with results synchronized to the CPU memory if MPSGraphOptionsSynchronizeResults set.
 */
-(MPSGraphTensorDataDictionary *) encodeToCommandBuffer:(MPSCommandBuffer *) commandBuffer
                                                  feeds:(MPSGraphTensorDataDictionary *) feeds
                                          targetTensors:(NSArray<MPSGraphTensor *> *) targetTensors
                                       targetOperations:(NSArray<MPSGraphOperation *> * _Nullable) targetOperations
                                    executionDescriptor:(MPSGraphExecutionDescriptor * _Nullable) executionDescriptor
MPS_SWIFT_NAME( encode(to:feeds:targetTensors:targetOperations:executionDescriptor:) );

/*!
 *  @abstract   Encodes the graph for given feeds to return targetTensor values in the resultsDictionary provided by the user,
 *              ensuring all target operations also executed. This call  is asynchronous and will return immediately if a completionHandler is set.
 *
 *  @param      commandBuffer                                      commandBuffer passed to exectute the graph on, commitAndContinue might be called, please don't rely on underlying MTLCommandBuffer to remain uncommitted
 *  @param      feeds                                                       Feeds dictionary for the placeholder tensors
 *  @param      targetOperations                              Operations to be completed at the end of the run
 *  @param      resultsDictionary                            MPSGraphTensors dictionary passed by user, these will be filled with graph output data
 *  @param      executionDescriptor                       ExecutionDescriptor to be passed in and used,
 *
 */
-(void) encodeToCommandBuffer:(MPSCommandBuffer *) commandBuffer
                        feeds:(MPSGraphTensorDataDictionary *) feeds
             targetOperations:(NSArray<MPSGraphOperation *> * _Nullable) targetOperations
            resultsDictionary:(MPSGraphTensorDataDictionary *) resultsDictionary
          executionDescriptor:(MPSGraphExecutionDescriptor * _Nullable) executionDescriptor
MPS_SWIFT_NAME( encode(to:feeds:targetOperations:resultsDictionary:executionDescriptor:) );


@end

NS_ASSUME_NONNULL_END

#endif /* MPSGraph_h */
