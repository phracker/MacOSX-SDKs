//
//  MPSGraphRandomOps.h
//  MPSGraph
//
//  Created on 6/1/20.
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#ifndef MPSGraphRandomOps_h
#define MPSGraphRandomOps_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

/// The distributions supported by random operations.
typedef NS_ENUM(uint64_t, MPSGraphRandomDistribution)
{
    /// The uniform distribution, with samples drawn uniformly from [min, max) for float types, and [min, max] for integer types.
    MPSGraphRandomDistributionUniform            MPS_ENUM_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4)) MPS_SWIFT_NAME(uniform) =   0,
    /// The normal distribution defined by mean and standard deviation.
    MPSGraphRandomDistributionNormal         MPS_ENUM_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4))                        =   1L,
    /// The normal distribution defined by mean and standard deviation, truncated to the range [min, max)
    MPSGraphRandomDistributionTruncatedNormal         MPS_ENUM_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4))                        =   2L,
};

/// The sampling method to use when generating values in the normal distribution.
typedef NS_ENUM(uint64_t, MPSGraphRandomNormalSamplingMethod)
{
    /// Use inverse erf to convert uniform values to values in the normal distribution
    MPSGraphRandomNormalSamplingInvCDF            MPS_ENUM_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4)) MPS_SWIFT_NAME(invCDF) =   0,
    /// Use Box Muller transform to convert uniform values to values in the normal distribution. For bounded distributions this is a rejection sampling method.
    MPSGraphRandomNormalSamplingBoxMuller         MPS_ENUM_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4))                        =   1L,
};

/// A class that describes the random operation.
@interface MPSGraphRandomOpDescriptor : MPSGraphObject<NSCopying>

/// The type of distribution to draw samples from. See MPSGraphRandomDistribution. 
///
@property (readwrite, nonatomic) MPSGraphRandomDistribution distribution;

/// The data type of the generated result values. 
/// 
/// When sampling from the uniform distribution, valid types are MPSDataTypeFloat16,
/// MPSDataTypeFloat32, and MPSDataTypeInt32.
/// When sampling from the normal or truncated normal distribution, valid types are 
/// MPSDataTypeFloat16 and MPSDataTypeFloat32. 
///
@property (readwrite, nonatomic) MPSDataType dataType;

/// The lower range of the distribution. 
///
/// This value is used for Uniform distributions with float data types and Truncated Normal disributions.
/// Defaults to 0 for uniform distributions and -2 for normal distributions.
///
@property (readwrite, nonatomic) float min;

/// The upper range of the distribution. 
///
/// This value is used for Uniform distributions with float data types and Truncated Normal disributions.
/// Defaults to 1 for uniform distributions and 2 for normal distributions.
///
@property (readwrite, nonatomic) float max;

/// The lower range of the distribution. 
///
/// This value is used for Uniform with integer data types
/// Defaults to 0.
///
@property (readwrite, nonatomic) NSInteger minInteger;

/// The upper range of the distribution. 
///
/// This value is used for Uniform with integer data types
/// Defaults to INT32_MAX for uniform distributions and 0 for normal distributions.
///
@property (readwrite, nonatomic) NSInteger maxInteger;

/// The mean of the distribution. 
///
/// This value is used for Normal and Truncated Normal disributions.
/// Defaults to 0.
///
@property (readwrite, nonatomic) float mean;

/// The standard deviation of the distribution.
///
/// This value is used for Normal and Truncated Normal disributions.
/// For Truncated Normal distribution this defines the standard deviation parameter of the underlying Normal distribution, that is the width
/// of the Gaussian, not the true standard deviation of the truncated distribution which typically differs from the standard deviation of the 
/// original Normal distribution. 
/// Defaults to 0 for uniform distributions and 1 for normal distributions. 
///
@property (readwrite, nonatomic) float standardDeviation;

/// The sampling method of the distribution. 
///
/// This value is used for Normal and Truncated Normal disributions. See MPSGraphRandomNormalSamplingMethod.
/// Defaults to MPSGraphRandomNormalSamplingInvCDF.
///
@property (readwrite, nonatomic) MPSGraphRandomNormalSamplingMethod samplingMethod;

/// Class method to initialize a distribution descriptor.
+(nullable instancetype) descriptorWithDistribution:(MPSGraphRandomDistribution) distribution
                                           dataType:(MPSDataType) dataType;

@end // MPSGraphRandomOpDescriptor

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(MPSGraphRandomOps)

/// Creates a tensor representing state using the Philox algorithm with given counter and key values.
///
/// Generates random numbers using the Philox counter-based algorithm, for further details see: 
/// John K. Salmon, Mark A. Moraes, Ron O. Dror, and David E. Shaw. Parallel Random Numbers: As Easy as 1, 2, 3. 
/// A stateTensor generated with this API can be used in MPSGraph Random APIs which accept a stateTensor. The 
/// updated stateTensor is returned alongside the random values, and can be fed to the following random layer. In 
/// most use cases, a stateTensor should only need to be initialized once at the start of the graph. A stateTensor can 
/// be set as a target tensor of an MPSGraph execution to obtain a stateTensor serialized as an NDArray. This can be 
/// used as input to a placeholder in the graph to avoid ever needing to have a state intilization layer in an MPSGraph. 
/// This can allow for a continued stream through multiple executions of a single MPSGraph by having the final 
/// stateTensor as a target tensor passed into the following MPSGraph execution as a placeholder input. This may be 
/// helpful for training graphs in particular. 
/// ```md 
/// MPSGraph *graph = [MPSGraph new]; 
/// MPSGraphTensor *stateTensor = [graph randomPhiloxStateTensorWithSeed: seed name: nil]; 
/// NSArray<MPSGraphTensor*> *resultTensors0 = [graph randomUniformTensorWithShape:
///
/// - Parameters:
///   - seed: Initial counter and key values will be generated using seed.
///   - name: Name for the operation
/// - Returns: An MPSGraphTensor representing a random state, to be passed as an input to a random op.
- (MPSGraphTensor *) randomPhiloxStateTensorWithSeed:(NSUInteger) seed
                                                name:(NSString * _Nullable) name;

/// Creates a tensor representing state using the Philox algorithm with given counter and key values.
///
/// See randomPhiloxStateTensorWithSeed.
///
/// - Parameters:
///   - counterLow: The value to initilaize lower 64 bits of counter to. Philox utilizes a 128 bit counter
///   - counterHigh: The value to initilaize upper 64 bits of counter to. Philox utilizes a 128 bit counter
///   - key: The value to initialize the key to in Philox algorithm.
///   - name: Name for the operation
/// - Returns: An MPSGraphTensor representing a random state, to be passed as an input to a random op.
- (MPSGraphTensor *) randomPhiloxStateTensorWithCounterLow:(NSUInteger) counterLow
                                               counterHigh:(NSUInteger) counterHigh
                                                       key:(NSUInteger) key
                                                      name:(NSString * _Nullable) name;

/// Creates a Random op of type matching distribution in descriptor and returns random values.
///
/// Returns a tensor of provided shape of random values in the distribution specified. Uses a random seed value
/// to initalize state. No state is preserved, and subsequent calls are not guaranteed to result in a unique stream of 
/// random values.
///
/// - Parameters:
///   - shape: The shape of the tensor generated
///   - descriptor: The descriptor of the distribution. See MPSGraphRandomOpDescriptor.
///   - name: The name for the operation.
/// - Returns: An MPSGraphTensor of shape containing random values in the defined range.
- (MPSGraphTensor *) randomTensorWithShape:(MPSShape *) shape
                                descriptor:(MPSGraphRandomOpDescriptor *) descriptor
                                      name:(NSString * _Nullable) name;

/// Creates a Random op of type matching distribution in descriptor and returns random values.
///
/// Returns a tensor of provided shape of random values in the distribution specified. Uses a random seed value
/// to initalize state. No state is preserved, and subsequent calls are not guaranteed to result in a unique stream of
/// random values.
///
/// - Parameters:
///   - shapeTensor: 1D Int32 or Int64 tensor. The shape of the tensor generated
///   - descriptor: The descriptor of the distribution. See MPSGraphRandomOpDescriptor.
///   - name: The name for the operation.
/// - Returns: An MPSGraphTensor of shape containing random values in the defined range.
- (MPSGraphTensor *) randomTensorWithShapeTensor:(MPSGraphTensor *) shapeTensor
                                      descriptor:(MPSGraphRandomOpDescriptor *) descriptor
                                            name:(NSString * _Nullable) name;

/// Creates a Random op of type matching distribution in descriptor and returns random values.
///
/// Returns a tensor of provided shape of random values in the distribution specified. Uses the provided seed value
/// to initalize state. No state is preserved, and all calls with equal seed yield an identical stream of random values.
///
/// - Parameters:
///   - shape: The shape of the tensor generated
///   - descriptor: The descriptor of the distribution. See MPSGraphRandomOpDescriptor.
///   - seed: The seed to use to initialize state. All calls with equal seed yield an identical stream of random values.
///   - name: The name for the operation.
/// - Returns: An MPSGraphTensor of shape containing random values in the defined range.
- (MPSGraphTensor *) randomTensorWithShape:(MPSShape *) shape
                                descriptor:(MPSGraphRandomOpDescriptor *) descriptor
                                      seed:(NSUInteger) seed
                                      name:(NSString * _Nullable) name;

/// Creates a Random op of type matching distribution in descriptor and returns random values.
///
/// Returns a tensor of provided shape of random values in the distribution specified. Uses the provided seed value
/// to initalize state. No state is preserved, and all calls with equal seed yield an identical stream of random values.
///
/// - Parameters:
///   - shapeTensor: 1D Int32 or Int64 tensor. The shape of the tensor generated
///   - descriptor: The descriptor of the distribution. See MPSGraphRandomOpDescriptor.
///   - seed: The seed to use to initialize state. All calls with equal seed yield an identical stream of random values.
///   - name: The name for the operation.
/// - Returns: An MPSGraphTensor of shape containing random values in the defined range.
- (MPSGraphTensor *) randomTensorWithShapeTensor:(MPSGraphTensor *) shapeTensor
                                      descriptor:(MPSGraphRandomOpDescriptor *) descriptor
                                            seed:(NSUInteger) seed
                                            name:(NSString * _Nullable) name;

/// Creates a Random op of type matching distribution in descriptor, and returns random values and updated state.
///
/// Returns an array of 2 tensors, where the first is of provided shape of random values in the distribution specified,
/// and the second is the updated state tensor.
/// Uses the provided state to define a stream of random values. No state is preserved, and all calls with equal state
/// yield an identical stream of random values. The initial stateTensor provided should be created using the MPSGraph 
/// randomPhiloxStateTensor APIs. The resulting stateTensor from this op can be passed as an argument to the following 
/// random calls to continue sampling from the stream.
///
/// - Parameters:
///   - shape: The shape of the tensor generated
///   - descriptor: The descriptor of the distribution. See MPSGraphRandomOpDescriptor.
///   - state: The state to define a stream of random values. All calls with equal state yield an identical stream of random values.
///   - name: The name for the operation.
/// - Returns: An array of MPSGraphTensor of size 2. The first MPSGraphTensor is of shape containing random values in the defined range. 
/// The second MPSGraphTensor is the updated state tensor.
- (NSArray<MPSGraphTensor *> *) randomTensorWithShape:(MPSShape *) shape
                                           descriptor:(MPSGraphRandomOpDescriptor *) descriptor
                                          stateTensor:(MPSGraphTensor *) state
                                                 name:(NSString * _Nullable) name;
/// Creates a Random op of type matching distribution in descriptor, and returns random values and updated state.
///
/// Returns an array of 2 tensors, where the first is of provided shape of random values in the distribution specified,
/// and the second is the updated state tensor.
/// Uses the provided state to define a stream of random values. No state is preserved, and all calls with equal state
/// yield an identical stream of random values. The initial stateTensor provided should be created using the MPSGraph
/// randomPhiloxStateTensor APIs. The resulting stateTensor from this op can be passed as an argument to the following
/// random calls to continue sampling from the stream.
///
/// - Parameters:
///   - shapeTensor: 1D Int32 or Int64 tensor. The shape of the tensor generated.
///   - descriptor: The descriptor of the distribution. See MPSGraphRandomOpDescriptor.
///   - state: The state to define a stream of random values. All calls with equal state yield an identical stream of random values.
///   - name: The name for the operation.
/// - Returns: An array of MPSGraphTensor of size 2. The first MPSGraphTensor is of shape containing random values in the defined range.
/// The second MPSGraphTensor is the updated state tensor.
- (NSArray<MPSGraphTensor *> *) randomTensorWithShapeTensor:(MPSGraphTensor *) shapeTensor
                                                 descriptor:(MPSGraphRandomOpDescriptor *) descriptor
                                                stateTensor:(MPSGraphTensor *) state
                                                       name:(NSString * _Nullable) name;

/// Creates a RandomUniform operation and returns random uniform values
///
/// Returns a tensor of provided shape of random uniform values in the range [0.0, 1.0). Uses a random seed value
/// to initalize state. No state is preserved, and subsequent calls are not guaranteed to result in a unique stream of 
/// random values.
///
/// - Parameters:
///   - shape: The shape of the tensor generated
///   - name: The name for the operation.
/// - Returns: An MPSGraphTensor of shape containing random values in the defined range.
- (MPSGraphTensor *) randomUniformTensorWithShape:(MPSShape *) shape
                                             name:(NSString * _Nullable) name;
/// Creates a RandomUniform operation and returns random uniform values
///
/// Returns a tensor of provided shape of random uniform values in the range [0.0, 1.0). Uses a random seed value
/// to initalize state. No state is preserved, and subsequent calls are not guaranteed to result in a unique stream of
/// random values.
///
/// - Parameters:
///   - shapeTensor: 1D Int32 or Int64 tensor. The shape of the tensor generated
///   - name: The name for the operation.
/// - Returns: An MPSGraphTensor of shape containing random values in the defined range.
- (MPSGraphTensor *) randomUniformTensorWithShapeTensor:(MPSGraphTensor *) shapeTensor
                                                   name:(NSString * _Nullable) name;

/// Creates a RandomUniform operation and returns random uniform values
///
/// Returns a tensor of provided shape of random uniform values in the range [0.0, 1.0). Uses the provided seed value
/// to initalize state. No state is preserved, and all calls with equal seed yield an identical stream of random values.
///
/// - Parameters:
///   - shape: The shape of the tensor generated
///   - seed: The seed to use to initialize state. All calls with equal seed yield an identical stream of random values.
///   - name: The name for the operation.
/// - Returns: An MPSGraphTensor of shape containing random values in the defined range.
- (MPSGraphTensor *) randomUniformTensorWithShape:(MPSShape *) shape
                                             seed:(NSUInteger) seed
                                             name:(NSString * _Nullable) name;
/// Creates a RandomUniform operation and returns random uniform values
///
/// Returns a tensor of provided shape of random uniform values in the range [0.0, 1.0). Uses the provided seed value
/// to initalize state. No state is preserved, and all calls with equal seed yield an identical stream of random values.
///
/// - Parameters:
///   - shapeTensor: 1D Int32 or Int64 tensor. The shape of the tensor generated
///   - seed: The seed to use to initialize state. All calls with equal seed yield an identical stream of random values.
///   - name: The name for the operation.
/// - Returns: An MPSGraphTensor of shape containing random values in the defined range.
- (MPSGraphTensor *) randomUniformTensorWithShapeTensor:(MPSGraphTensor *) shapeTensor
                                                   seed:(NSUInteger) seed
                                                   name:(NSString * _Nullable) name;

/// Creates a RandomUniform operation and returns random uniform values and updated state
///
/// Returns an array of 2 tensors, where the first is a tensor of provided shape of random uniform values in the range 
/// [0.0, 1.0), and the second is the updated state tensor.
/// The provided state is used to define a stream of random values. No state is preserved, and all calls with equal state 
/// yield an identical stream of random values. The initial stateTensor provided should be created using the MPSGraph 
/// randomPhiloxStateTensor APIs. The resulting stateTensor from this op can be passed as an argument to the following 
/// random calls to continue sampling from the stream.
///
/// - Parameters:
///   - shape: The shape of the tensor generated
///   - state: The state to define a stream of random values. All calls with equal state yield an identical stream of random values.
///   - name: The name for the operation.
/// - Returns: An array of MPSGraphTensor of size 2. The first MPSGraphTensor is of shape containing random values in the defined range. 
/// The second MPSGraphTensor is the updated state tensor.
- (NSArray<MPSGraphTensor *> *) randomUniformTensorWithShape:(MPSShape *) shape
                                                 stateTensor:(MPSGraphTensor *) state
                                                        name:(NSString * _Nullable) name;
/// Creates a RandomUniform operation and returns random uniform values and updated state
///
/// Returns an array of 2 tensors, where the first is a tensor of provided shape of random uniform values in the range
/// [0.0, 1.0), and the second is the updated state tensor.
/// The provided state is used to define a stream of random values. No state is preserved, and all calls with equal state
/// yield an identical stream of random values. The initial stateTensor provided should be created using the MPSGraph
/// randomPhiloxStateTensor APIs. The resulting stateTensor from this op can be passed as an argument to the following
/// random calls to continue sampling from the stream.
///
/// - Parameters:
///   - shapeTensor: 1D Int32 or Int64 tensor. The shape of the tensor generated
///   - state: The state to define a stream of random values. All calls with equal state yield an identical stream of random values.
///   - name: The name for the operation.
/// - Returns: An array of MPSGraphTensor of size 2. The first MPSGraphTensor is of shape containing random values in the defined range.
/// The second MPSGraphTensor is the updated state tensor.
- (NSArray<MPSGraphTensor *> *) randomUniformTensorWithShapeTensor:(MPSGraphTensor *) shapeTensor
                                                       stateTensor:(MPSGraphTensor *) state
                                                              name:(NSString * _Nullable) name;

/// Creates a dropout operation and returns the result
///
/// Removes values in the `tensor` with a percentage chance equal to `rate`. Removed values are set to 0
///
/// - Parameters:
///   - tensor: Input tensor
///   - rate: The rate of values to be set to 0
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
- (MPSGraphTensor *) dropoutTensor:(MPSGraphTensor *) tensor
                              rate:(double) rate
                              name:(NSString * _Nullable) name
MPS_SWIFT_NAME( dropout(_:rate:name:) );

/// Creates a dropout operation and returns the result
///
/// Removes values in the `tensor` with a percentage chance equal to `rate`. Removed values are set to 0
///
/// - Parameters:
///   - tensor: Input tensor
///   - rate: The rate of values to be set to 0
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
- (MPSGraphTensor *) dropoutTensor:(MPSGraphTensor *) tensor
                        rateTensor:(MPSGraphTensor *) rate
                              name:(NSString * _Nullable) name
MPS_SWIFT_NAME( dropout(_:rate:name:) );

@end

NS_ASSUME_NONNULL_END

#endif /* MPSGraphRandomOps_h */
