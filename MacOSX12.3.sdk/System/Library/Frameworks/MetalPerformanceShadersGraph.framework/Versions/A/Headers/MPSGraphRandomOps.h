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

/*!
 *  @typedef    MPSGraphRandomDistribution
 *  @abstract   The distributions supported by MPSGraphRandom ops.
 *
 *  @constant   MPSGraphRandomDistributionUniform                    The uniform distribution, with samples drawn uniformly from [min, max) for float types, and [min, max] for integer types.
 *  @constant   MPSGraphRandomDistributionNormal                     The normal distribution defined by mean and standardDeviation.
 *  @constant   MPSGraphRandomDistributionTruncatedNormal                     The normal distribution defined by mean and standardDeviation, truncated to the range [min, max)
 */
typedef NS_ENUM(uint64_t, MPSGraphRandomDistribution)
{
    MPSGraphRandomDistributionUniform            MPS_ENUM_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4)) MPS_SWIFT_NAME(uniform) =   0,
    MPSGraphRandomDistributionNormal         MPS_ENUM_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4))                        =   1L,
    MPSGraphRandomDistributionTruncatedNormal         MPS_ENUM_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4))                        =   2L,
};

/*!
 *  @typedef    MPSGraphRandomNormalSamplingMethod
 *  @abstract   Specify what sampling method to use when generating values in the normal distribution.
 *
 *  @constant   MPSGraphRandomNormalSamplingInvCDF                    Use inverse erf to convert uniform values to values in the normal distribution
 *  @constant   MPSGraphRandomNormalSamplingBoxMuller                     Use Box Muller transform to convert uniform values to values in the normal distribution. For bounded distributions this is a rejection sampling method.
 */
typedef NS_ENUM(uint64_t, MPSGraphRandomNormalSamplingMethod)
{
    MPSGraphRandomNormalSamplingInvCDF            MPS_ENUM_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4)) MPS_SWIFT_NAME(invCDF) =   0,
    MPSGraphRandomNormalSamplingBoxMuller         MPS_ENUM_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4))                        =   1L,
};

@interface MPSGraphRandomOpDescriptor : NSObject<NSCopying>

/*! @property   distribution
 *  @discussion The type of distribution to draw samples from. See MPSGraphRandomDistribution.
*/
@property (readwrite, nonatomic) MPSGraphRandomDistribution distribution;

/*! @property   dataType
 *  @discussion The data type of the generated result values.
 *              When sampling from the uniform distribution, valid types are MPSDataTypeFloat16,
 *              MPSDataTypeFloat32, and MPSDataTypeInt32.
 *              When sampling from the normal or truncated normal distribution, valid types are
 *              MPSDataTypeFloat16 and MPSDataTypeFloat32.
*/
@property (readwrite, nonatomic) MPSDataType dataType;

/*! @property   min
 *  @discussion The lower range of the distribution. This value is used for Uniform distributions with float data types and Truncated Normal disributions.
 *              Defaults to 0 for uniform distributions and -2 for normal distributions.
*/
@property (readwrite, nonatomic) float min;

/*! @property   max
 *  @discussion The upper range of the distribution. This value is used for Uniform distributions with float data types and Truncated Normal disributions.
 *              Defaults to 1 for uniform distributions and 2 for normal distributions.
*/
@property (readwrite, nonatomic) float max;

/*! @property   minInteger
 *  @discussion The lower range of the distribution. This value is used for Uniform with integer data types
 *              Defaults to 0.
*/
@property (readwrite, nonatomic) NSInteger minInteger;

/*! @property   maxInteger
 *  @discussion The upper range of the distribution. This value is used for Uniform with integer data types
 *              Defaults to INT32_MAX for uniform distributions and 0 for normal distributions.
*/
@property (readwrite, nonatomic) NSInteger maxInteger;

/*! @property   mean
 *  @discussion The mean of the distribution. This value is used for Normal and Truncated Normal disributions.
 *              Defaults to 0.
*/
@property (readwrite, nonatomic) float mean;

/*! @property   standardDeviation
 *  @discussion The standardDeviation of the distribution. This value is used for Normal and Truncated Normal disributions.
 *              For Truncated Normal distribution this defines the standard deviation parameter of the underlying Normal distribution, that is the width
 *              of the Gaussian, not the true standard deviation of the truncated distribution which typically differs from the standard deviation of the
 *              original Normal distribution.
 *              Defaults to 0 for uniform distributions and 1 for normal distributions.
*/
@property (readwrite, nonatomic) float standardDeviation;

/*! @property   samplingMethod
 *  @discussion The sampling method of the distribution. This value is used for Normal and Truncated Normal disributions. See MPSGraphRandomNormalSamplingMethod.
 *              Defaults to MPSGraphRandomNormalSamplingInvCDF.
*/
@property (readwrite, nonatomic) MPSGraphRandomNormalSamplingMethod samplingMethod;

+(nullable instancetype) descriptorWithDistribution:(MPSGraphRandomDistribution) distribution
                                           dataType:(MPSDataType) dataType;

@end // MPSGraphRandomOpDescriptor

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(MPSGraphRandomOps)

/*!
 *  @abstract   Creates an MPSGraphTensor representing state using the Philox algorithm with given counter and key values.
 *  @discussion Generates random numbers using the Philox counter-based algorithm, for further details see:
 *              John K. Salmon, Mark A. Moraes, Ron O. Dror, and David E. Shaw. Parallel Random Numbers: As Easy as 1, 2, 3.
 *
 *              A stateTensor generated with this API can be used in MPSGraph Random APIs which accept a stateTensor. The
 *              updated stateTensor is returned alongside the random values, and can be fed to the following random layer. In
 *              most use cases, a stateTensor should only need to be initialized once at the start of the graph. A stateTensor can
 *              be set as a target tensor of an MPSGraph execution to obtain a stateTensor serialized as an NDArray. This can be
 *              used as input to a placeholder in the graph to avoid ever needing to have a state intilization layer in an MPSGraph.
 *              This can allow for a continued stream through multiple executions of a single MPSGraph by having the final
 *              stateTensor as a target tensor passed into the following MPSGraph execution as a placeholder input. This may be
 *              helpful for training graphs in particular.
 *
 *              @code
 *                  MPSGraph *graph = [MPSGraph new];
 *                  MPSGraphTensor *stateTensor = [graph randomPhiloxStateTensorWithSeed: seed name: nil];
 *                  NSArray<MPSGraphTensor*> *resultTensors0 = [graph randomUniformTensorWithShape:@[@10, @10]
 *                                                                                     stateTensor:stateTensor
 *                                                                                            name:nil];
 *                  NSArray<MPSGraphTensor*> *resultTensors1 = [graph randomUniformTensorWithShape:@[@10, @10]
 *                                                                                     stateTensor:resultTensors0[1]
 *                                                                                            name:nil];
 *
 *              @endcode
 *
 *  @param      seed    Initial counter and key values will be generated using seed.
 *
 *  @return     An MPSGraphTensor representing a random state, to be passed as an input to a random op.
 */
-(MPSGraphTensor *) randomPhiloxStateTensorWithSeed:(NSUInteger) seed
                                               name:(NSString * _Nullable) name;

/*!
 *  @abstract   Creates an MPSGraphTensor representing state using the Philox algorithm with given counter and key values.
 *  @discussion See randomPhiloxStateTensorWithSeed.
 *
 *  @param      counterLow     The value to initilaize lower 64 bits of counter to. Philox utilizes a 128 bit counter
 *  @param      counterHigh    The value to initilaize upper 64 bits of counter to. Philox utilizes a 128 bit counter
 *  @param      key  The value to initialize the key to in Philox algorithm.
 *
 *  @return     An MPSGraphTensor representing a random state, to be passed as an input to a random op.
 */
-(MPSGraphTensor *) randomPhiloxStateTensorWithCounterLow:(NSUInteger) counterLow
                                              counterHigh:(NSUInteger) counterHigh
                                                      key:(NSUInteger) key
                                                     name:(NSString * _Nullable) name;

/*!
 *  @abstract   Create Random op of type matching distribution in descriptor and return random values
 *  @discussion Returns a tensor of provided shape of random values in the distribution specified. A random seed value is used
 *              to initalize state. No state is preserved, and subsequent calls are not guaranteed to result in a unique stream of
 *              random values.
 *
 *  @param      shape   The shape of the tensor generated
 *  @param      descriptor   The descriptor of the distribution. See MPSGraphRandomOpDescriptor.
 *  @param      name        The name for the operation
 *
 *  @return     An MPSGraphTensor of shape containing random values in the defined range.
 */
-(MPSGraphTensor *) randomTensorWithShape:(MPSShape *) shape
                               descriptor:(MPSGraphRandomOpDescriptor *) descriptor
                                     name:(NSString * _Nullable) name;
-(MPSGraphTensor *) randomTensorWithShapeTensor:(MPSGraphTensor *) shapeTensor
                                     descriptor:(MPSGraphRandomOpDescriptor *) descriptor
                                           name:(NSString * _Nullable) name;

/*!
 *  @abstract   Create Random op of type matching distribution in descriptor and return random values
 *  @discussion Returns a tensor of provided shape of random values in the distribution specified. The provided seed value is
 *              used to initalize state. No state is preserved, and all calls with equal seed yield an identical stream of random values.
 *
 *  @param      shape   The shape of the tensor generated
 *  @param      descriptor   The descriptor of the distribution. See MPSGraphRandomOpDescriptor.
 *  @param      seed   The seed to use to initialize state. All calls with equal seed yield an identical stream of random values.
 *  @param      name        The name for the operation
 *
 *  @return     An MPSGraphTensor of shape containing random values in the defined range.
 */
-(MPSGraphTensor *) randomTensorWithShape:(MPSShape *) shape
                               descriptor:(MPSGraphRandomOpDescriptor *) descriptor
                                     seed:(NSUInteger) seed
                                     name:(NSString * _Nullable) name;
-(MPSGraphTensor *) randomTensorWithShapeTensor:(MPSGraphTensor *) shapeTensor
                                     descriptor:(MPSGraphRandomOpDescriptor *) descriptor
                                           seed:(NSUInteger) seed
                                           name:(NSString * _Nullable) name;

/*!
 *  @abstract   Create Random op of type matching distribution in descriptor, and return random values and updated state
 *  @discussion Returns an array of 2 tensors, where the first is of provided shape of random values in the distribution specified.
 *              The updated state tensor is returned as the second result tensor.
 *
 *              The provided state is used to define a stream of random values. No state is preserved, and all calls with equal state
 *              yield an identical stream of random values. The initial stateTensor provided should be created using the MPSGraph
 *              randomPhiloxStateTensor APIs. The resulting stateTensor from this op can be passed as an argument to the following
 *              random calls to continue sampling from the stream.
 *
 *  @param      shape   The shape of the tensor generated
 *  @param      descriptor   The descriptor of the distribution. See MPSGraphRandomOpDescriptor.
 *  @param      state   The state to define a stream of random values. All calls with equal state yield an identical stream of random values.
 *  @param      name        The name for the operation
 *
 *  @return     An array of MPSGraphTensor of size 2. The first MPSGraphTensor is of shape containing random values in the defined range.
 *              The second MPSGraphTensor is the updated state tensor.
 */
-(NSArray<MPSGraphTensor *> *) randomTensorWithShape:(MPSShape *) shape
                                          descriptor:(MPSGraphRandomOpDescriptor *) descriptor
                                         stateTensor:(MPSGraphTensor *) state
                                                name:(NSString * _Nullable) name;
-(NSArray<MPSGraphTensor *> *) randomTensorWithShapeTensor:(MPSGraphTensor *) shapeTensor
                                                descriptor:(MPSGraphRandomOpDescriptor *) descriptor
                                               stateTensor:(MPSGraphTensor *) state
                                                      name:(NSString * _Nullable) name;

/*!
 *  @abstract   Create RandomUniform op and return random uniform values
 *  @discussion Returns a tensor of provided shape of random uniform values in the range [0.0, 1.0). A random seed value is used
 *              to initalize state. No state is preserved, and subsequent calls are not guaranteed to result in a unique stream of
 *              random values.
 *
 *  @param      shape   The shape of the tensor generated
 *  @param      name        The name for the operation
 *
 *  @return     An MPSGraphTensor of shape containing random values in the defined range.
 */
-(MPSGraphTensor *) randomUniformTensorWithShape:(MPSShape *) shape
                                            name:(NSString * _Nullable) name;

-(MPSGraphTensor *) randomUniformTensorWithShapeTensor:(MPSGraphTensor *) shapeTensor
                                                  name:(NSString * _Nullable) name;

/*!
 *  @abstract   Create RandomUniform op and return random uniform values
 *  @discussion Returns a tensor of provided shape of random uniform values in the range [0.0, 1.0). The provided seed value is
 *              used to initalize state. No state is preserved, and all calls with equal seed yield an identical stream of random values.
 *
 *  @param      shape   The shape of the tensor generated
 *  @param      seed   The seed to use to initialize state. All calls with equal seed yield an identical stream of random values.
 *  @param      name        The name for the operation
 *
 *  @return     An MPSGraphTensor of shape containing random values in the defined range.
 */
-(MPSGraphTensor *) randomUniformTensorWithShape:(MPSShape *) shape
                                            seed:(NSUInteger) seed
                                            name:(NSString * _Nullable) name;

-(MPSGraphTensor *) randomUniformTensorWithShapeTensor:(MPSGraphTensor *) shapeTensor
                                                  seed:(NSUInteger) seed
                                                  name:(NSString * _Nullable) name;

/*!
 *  @abstract   Create RandomUniform op and return random uniform values and updated state
 *  @discussion Returns an array of 2 tensors, where the first is a tensor of provided shape of random uniform values in the range
 *              [0.0, 1.0). The updated state tensor is returned as the second result tensor.
 *
 *              The provided state is used to define a stream of random values. No state is preserved, and all calls with equal state
 *              yield an identical stream of random values. The initial stateTensor provided should be created using the MPSGraph
 *              randomPhiloxStateTensor APIs. The resulting stateTensor from this op can be passed as an argument to the following
 *              random calls to continue sampling from the stream.
 *
 *  @param      shape   The shape of the tensor generated
 *  @param      state   The state to define a stream of random values. All calls with equal state yield an identical stream of random values.
 *  @param      name        The name for the operation
 *
 *  @return     An array of MPSGraphTensor of size 2. The first MPSGraphTensor is of shape containing random values in the defined range.
 *              The second MPSGraphTensor is the updated state tensor.
 */
-(NSArray<MPSGraphTensor *> *) randomUniformTensorWithShape:(MPSShape *) shape
                                                stateTensor:(MPSGraphTensor *) state
                                                       name:(NSString * _Nullable) name;

-(NSArray<MPSGraphTensor *> *) randomUniformTensorWithShapeTensor:(MPSGraphTensor *) shapeTensor
                                                      stateTensor:(MPSGraphTensor *) state
                                                             name:(NSString * _Nullable) name;


-(MPSGraphTensor *) dropoutTensor:(MPSGraphTensor *) tensor
                             rate:(double) rate
                             name:(NSString * _Nullable) name
MPS_SWIFT_NAME( dropout(_:rate:name:) );

-(MPSGraphTensor *) dropoutTensor:(MPSGraphTensor *) tensor
                       rateTensor:(MPSGraphTensor *) rate
                             name:(NSString * _Nullable) name
MPS_SWIFT_NAME( dropout(_:rate:name:) );

@end

NS_ASSUME_NONNULL_END

#endif /* MPSGraphRandomOps_h */
