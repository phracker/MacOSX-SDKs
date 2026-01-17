//
//  MPSGraphOperation.h
//  MetalPerformanceShadersGraph
//
//  Created on 11/10/19.
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#ifndef MPSGraphOperation_h
#define MPSGraphOperation_h

#import <MetalPerformanceShadersGraph/MPSGraphCore.h>
#import <MetalPerformanceShadersGraph/MPSGraphTensor.h>

NS_ASSUME_NONNULL_BEGIN

@class MPSGraph;

/*! @class      MPSGraphOperation
 *  @abstract   Symbolic representation of a compute operation, all tensors are created, owned and destroyed by the MPSGraph
 *  @discussion NSCopy will cause a refrence to be taken, this is so NSDictionary can work with the tensor.
 *              All operations  are created, owned and destroyed by the MPSGraph
 */
MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraphOperation : NSObject <NSCopying>

/*! @property   inputTensors
 *  @discussion inputTensors of the operation
 */
@property (readonly, nonnull, nonatomic) NSArray<MPSGraphTensor *> *inputTensors;

/*! @property   outputTensors
 *  @discussion outputTensors of the operation
 */
@property (readonly, nonnull, nonatomic) NSArray<MPSGraphTensor *> *outputTensors;

/*! @property   controlDependencies
 *  @discussion operations guaranteed to execute before this operation
 */
@property (readonly, nonnull, nonatomic) NSArray<MPSGraphOperation *> *controlDependencies;

/*! @property   graph
 *  @discussion graph on which the operation is defined
 */
@property (readonly, nonatomic) MPSGraph *graph;

/*! @property   name
 *  @discussion name of the operation
 */
@property (readonly, nonnull, nonatomic) NSString *name;

/*!
 *  @brief Unvaiable, please utilize graph methods to create and initialize operations
 */
-(instancetype) init NS_UNAVAILABLE;


@end

NS_ASSUME_NONNULL_END

#endif /* MPSGraphOperation_h */
