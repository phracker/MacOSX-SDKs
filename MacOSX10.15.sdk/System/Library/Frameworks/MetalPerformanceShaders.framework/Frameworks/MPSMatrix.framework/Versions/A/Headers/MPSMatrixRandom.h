//
//  MPSMatrixRandom.h
//  MPS
//
//  Created by Justin Voo on 5/1/19.
//  Copyright © 2019 Apple. All rights reserved.
//

#ifndef MPSMatrixRandom_h
#define MPSMatrixRandom_h

#import <MPSCore/MPSKernel.h>
#import <MPSMatrix/MPSMatrixTypes.h>

/*! @enum       MPSMatrixRandomDistribution
 *  @abstract   Type of distribution from which to generate values.
 */
#if defined(DOXYGEN)
    typedef enum MPSMatrixRandomDistribution
#else
    typedef NS_OPTIONS(NSUInteger, MPSMatrixRandomDistribution)
#endif
{
    // Generate random bits according to the distribution of the underlying generator.
    MPSMatrixRandomDistributionDefault    MPS_ENUM_AVAILABLE_STARTING( macos(10.15), ios(13), macCatalyst(13), tvos(13)) MPS_SWIFT_NAME(default) = 1U,
    
    // Generate uniformly distributed random floating point values in the interval [0, 1).
    MPSMatrixRandomDistributionUniform    MPS_ENUM_AVAILABLE_STARTING( macos(10.15), ios(13), macCatalyst(13), tvos(13)) MPS_SWIFT_NAME(uniform) = 2U
};

/*!
 *  @class      MPSMatrixRandomDistributionDescriptor
 *  @dependency This depends on Metal.framework
 *  @discussion Decribes properties of a distribution of random values.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.15), ios(13), macCatalyst(13), tvos(13))
@interface MPSMatrixRandomDistributionDescriptor : NSObject <NSCopying>

/*! @property   distributionType
 *  @abstract   The type of distribution.
 */
@property (readwrite, nonatomic) MPSMatrixRandomDistribution distributionType;

/*! @property   minimum
 *  @abstract   For distributions of values bounded below, this value describes the minimum.
 */
@property (readwrite, nonatomic) float minimum;

/*! @property   maximum
 *  @abstract   For distributions of values bounded above, this value describes the maximum.
 */
@property (readwrite, nonatomic) float maximum;

/*! @property   mean
 *  @abstract   The value to use for distributions described by their mean.
 */
@property (readwrite, nonatomic) float mean;

/*! @property   standardDeviation
 *  @abstract   The value to use for distributions described by their standardDeviation.
 */
@property (readwrite, nonatomic) float standardDeviation;

/*!
 *  @abstract  Make a descriptor for a uniform distribution of floating point values in
 *              the range [minimum, maximum).
 *  @param     minimum  The lower bound of the range.
 *  @param     maximum  The upper bound of the range.
 *  @return    A valid MPSMatrixRandomDistribution object or nil, if failure.
 */
+(nonnull MPSMatrixRandomDistributionDescriptor*) uniformDistributionDescriptorWithMinimum: (float) minimum
                                                                                   maximum: (float) maximum;

/*!
 *  @abstract  Make a descriptor for a default distribution.
 *  @return    A valid MPSMatrixRandomDistribution object or nil, if failure.
 */
+(nonnull MPSMatrixRandomDistributionDescriptor*) defaultDistributionDescriptor;

@end    /* MPSMatrixRandomDistributionDescriptor */

/*!
 *  @class      MPSMatrixRandom
 *  @discussion Kernels that implement random number generation.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.15), ios(13), macCatalyst(13), tvos(13))
@interface  MPSMatrixRandom : MPSKernel

/*! @property   destinationDataType
 *  @discussion The type of the data which makes up the values of the result.
 *              Supported values are:
 *                  MPSDataTypeUInt32
 *                  MPSDataTypeFloat32
 *
 *              Default is MPSDataTypeUInt32
 */
@property (readonly, nonatomic) MPSDataType destinationDataType;

/*! @property   distributionType
 *  @discussion The distribution from which to generate random values.
 *
 *              Default is MPSMatrixRandomDistributionDefault
 */
@property (readonly, nonatomic) MPSMatrixRandomDistribution distributionType;

/*! @property   batchStart
 *
 *  @discussion The starting index in the destination batch.
 */
@property (readwrite, nonatomic) NSUInteger batchStart;

/*! @property   batchSize
 *
 *  @discussion The size of the batch to process.
 */
@property (readwrite, nonatomic) NSUInteger batchSize;

/*
 * You must use one of the sub-classes of MPSMatrixRandom.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

/*!
 *  @abstract   Encode a MPSMatrixRandom kernel into a command Buffer.
 *  @param      commandBuffer       A valid MTLCommandBuffer to receive the encoded filter
 *  @param      destinationVector   A valid MPSVector to contain the result.
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
            destinationVector: (MPSVector* __nonnull) destinationVector
MPS_SWIFT_NAME(encode(commandBuffer:destinationVector:));

/*!
 *  @abstract   Encode a MPSMatrixRandom kernel into a command Buffer.
 *  @param      commandBuffer       A valid MTLCommandBuffer to receive the encoded filter
 *  @param      destinationMatrix   A valid MPSMatrix to contain the result.
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
            destinationMatrix: (MPSMatrix* __nonnull) destinationMatrix
MPS_SWIFT_NAME(encode(commandBuffer:destinationMatrix:));

@end  /* MPSMatrixRandom */

/*!
 *  @class      MPSMatrixRandomMTGP32
 *  @discussion Generates random numbers using a Mersenne Twister algorithm
 *              suitable for GPU execution.  It uses a period of 2**11214.
 *              For further details see:
 *          Mutsuo Saito. A Variant of Mersenne Twister Suitable for Graphic Processors. arXiv:1005.4973
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.15), ios(13), macCatalyst(13), tvos(13))
@interface  MPSMatrixRandomMTGP32 : MPSMatrixRandom

/*!
 *  @abstract   initialize a MPSMatrixRandomMTGP32 filter to generate 32-bit unsigned
 *              integer values with an initial seed of 0.
 *  @param      device          The device the filter will run on
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device;

/*!
 *  @abstract   initialize a MPSMatrixRandomMTGP32 filter
 *  @param      device                  The device the filter will run on
 *  @param      destinationDataType     The data type of the result.
 *  @param      seed                    The seed to initialize the random number generators with.
 *  @param      distributionDescriptor  A descriptor containing information about the distribution.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                   destinationDataType: (MPSDataType) destinationDataType
                                  seed: (NSUInteger) seed
                distributionDescriptor: (MPSMatrixRandomDistributionDescriptor* __nonnull) distributionDescriptor NS_DESIGNATED_INITIALIZER;

/*!
 *  @abstract   Synchronize internal MTGP32 state between GPU and CPU.
 *  @param      commandBuffer       The command buffer on which to encode the synchronization.
 */
-(void) synchronizeStateOnCommandBuffer: (__nonnull id <MTLCommandBuffer>) commandBuffer;

/*!
 *  @abstract   initialize a MPSMatrixRandomMTGP32 filter using a default distribution.
 *  @param      device                  The device the filter will run on
 *  @param      destinationDataType     The data type of the result.
 *  @param      seed                    The seed to initialize the random number generators with.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                   destinationDataType: (MPSDataType) destinationDataType
                                  seed: (NSUInteger) seed;

-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

@end  /* MPSMatrixRandomMTGP32 */

/*!
 *  @class      MPSMatrixRandomPhilox
 *  @discussion Generates random numbers using a counter based algorithm.
 *              For further details see:
 *          John K. Salmon, Mark A. Moraes, Ron O. Dror, and David E. Shaw. Parallel Random Numbers: As Easy as 1, 2, 3.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.15), ios(13), macCatalyst(13), tvos(13))
@interface  MPSMatrixRandomPhilox : MPSMatrixRandom

/*!
 *  @abstract   initialize a MPSMatrixRandomPhilox filter to generate 32-bit unsigned
 *              integer values with an initial seed of 0.
 *  @param      device          The device the filter will run on
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device;

/*!
 *  @abstract   initialize a MPSMatrixRandomPhilox filter
 *  @param      device                  The device the filter will run on
 *  @param      destinationDataType     The data type of the result.
 *  @param      seed                    The seed to initialize the random number generators with.
 *  @param      distributionDescriptor  A descriptor containing information about the distribution.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                   destinationDataType: (MPSDataType) destinationDataType
                                  seed: (NSUInteger) seed
                distributionDescriptor: (MPSMatrixRandomDistributionDescriptor* __nonnull) distributionDescriptor NS_DESIGNATED_INITIALIZER;

/*!
 *  @abstract   initialize a MPSMatrixRandomPhilox filter using a default distribution.
 *  @param      device                  The device the filter will run on
 *  @param      destinationDataType     The data type of the result.
 *  @param      seed                    The seed to initialize the random number generators with.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                   destinationDataType: (MPSDataType) destinationDataType
                                  seed: (NSUInteger) seed;

-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

@end  /* MPSMatrixRandomPhilox */

#endif /* MPSMatrixRandom_h */
