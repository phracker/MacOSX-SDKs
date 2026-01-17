//
//  MPSGraphTensor.h
//  MetalPerformanceShadersGraph
//
//  Created on 11/10/19.
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#ifndef MPSGraphTensor_h
#define MPSGraphTensor_h

#import <MetalPerformanceShadersGraph/MPSGraphCore.h>

// Forward declaration
@class MPSGraphOperation;

NS_ASSUME_NONNULL_BEGIN

/// The symbolic representation of a compute data type.
///
/// `NSCopy` will take a refrence, this is so `NSDictionary` can work with the tensor.
/// All tensors are created, owned and destroyed by the MPSGraph
MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraphTensor : MPSGraphObject <NSCopying>

/// The shape of the tensor.
///
/// nil shape represents an unranked tensor.
/// -1 value for a dimension represents that it will be resolved via shape inference at runtime and it can be anything.
@property (nullable, readonly, copy, nonatomic) MPSShape *shape;

/// The data type of the tensor.
@property (readonly, nonatomic) MPSDataType dataType;

/// The operation responsible for creating this tensor.
@property (readonly, nonnull, nonatomic) MPSGraphOperation *operation;

/// Unavailable, please utilize graph methods to create and initialize tensors.
-(instancetype) init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END


#endif /* MPSGraphTensor_h */
