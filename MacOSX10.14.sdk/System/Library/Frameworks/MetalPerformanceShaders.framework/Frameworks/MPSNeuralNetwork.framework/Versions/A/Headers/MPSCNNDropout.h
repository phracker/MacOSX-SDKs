//
//  MPSCNNDropout.h
//  MPS
//
//  Created by Anna Tikhonova on 9/7/17.
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef MPSCNNDropout_h
#define MPSCNNDropout_h

#import <MPSNeuralNetwork/MPSCNNKernel.h>

#ifdef __cplusplus
extern "C" {
#endif


#pragma mark -
#pragma mark MPSCNNDropoutGradientState

/*!
 *  @class      MPSCNNDropoutGradientState
 *  @dependency This depends on Metal.framework.
 *  @discussion The MPSCNNDropoutGradientState is used to hold the mask used by both
 *              MPSCNNDropout forward filter and MPSCNNDropoutGradient backward filter.
 *              The MPSCNNDropout forward filter populates the MPSCNNDropoutGradientState
 *              object and the MPSCNNDropoutGradient backward filter consumes the state
 *              object.
 *
 *              While the mask is stored internally, the mask data is accessible by the
 *              user for debugging purposes via an accessor method.
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3))
@interface MPSCNNDropoutGradientState : MPSNNGradientState

/*
 * Use [MPSCNNDropout resultStateForSourceImage:...] or other variants instead
 */
-(nonnull instancetype) init NS_UNAVAILABLE;

/*!
 *  @abstract   Mask data accessor method.
 *  @return     An autoreleased NSData object, containing the mask data.
 *              The mask data is populated in the -encode call, thus the contents
 *              are undefined until you -encode the filter.
 *              Use for debugging purposes only.
 *
 *              In order to gaurantee that the mask data is correctly synchronized for CPU side access,
 *              it is the application's responsibility to call the [gradientState synchronizeOnCommandBuffer:]
 *              method before accessing the mask data.
 */
-(nonnull NSData*) maskData;

@end

#pragma mark -
#pragma mark MPSCNNDropoutGradientStateBatch

typedef NSArray<MPSCNNDropoutGradientState*> MPSCNNDropoutGradientStateBatch
    MPS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3));

#pragma mark -
#pragma mark MPSCNNDropout

/*!
 *  @class      MPSCNNDropout
 *  @dependency This depends on Metal.framework
 *  @discussion Dropout is a regularization technique used to prevent neural networks from
 *              overfitting during training. With probability keepProbability, this filter
 *              outputs the input element scaled by 1 / keepProbability. Otherwise, it
 *              outputs 0. Each input element is kept or dropped independently. The scaling
 *              is performed to keep the energy of the output unchanged.
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3))
@interface MPSCNNDropout : MPSCNNKernel

/*! @property   keepProbability
 *  @abstract   The probability that each element in the input is kept.
 *              The valid range is (0.0f, 1.0f).
 */
@property (readonly, nonatomic) float keepProbability;

/*! @property   seed
 *  @abstract   The seed used to generate random numbers.
 */
@property (readonly, nonatomic) NSUInteger seed;

/*! @property   maskStrideInPixels
 *  @abstract   The mask stride in the x, y, and x dimensions, which
 *              allows for the broadcasting the mask data.
 *  @discussion The only valid values are 0 and 1 for each dimension.
 *              For no broadcasting, set the values for each dimension
 *              to 1. For broadcasting, set desired values to 0.
 */
@property (readonly, nonatomic) MTLSize maskStrideInPixels;

/*
 * You must use initWithDevice:keepProbability:seed:maskStrideInPixels: instead.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

/*! @abstract <NSSecureCoding> support */
-(nullable instancetype) initWithCoder: (NSCoder * __nonnull) aDecoder
                                device: (nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

/*! @abstract   Standard init with default properties per filter type.
 *  @param      device              The device that the filter will be used on.
 *  @param      keepProbability     The probability that each element in the input is kept.
 *                                  The valid range is (0.0f, 1.0f).
 *  @param      seed                The seed used to generate random numbers.
 *  @param      maskStrideInPixels  The mask stride in the x, y, and z dimensions, which
 *                                  allows for the broadcasting of mask data. The only valid
 *                                  values are 0 and 1 for each dimension. For no
 *                                  broadcasting, set the values for each dimension to 1.
 *                                  For broadcasting, set desired values to 0.
 *  @result     A valid MPSCNNDropout object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                       keepProbability: (float) keepProbability
                                  seed: (NSUInteger) seed
                    maskStrideInPixels: (MTLSize) maskStrideInPixels NS_DESIGNATED_INITIALIZER;

-(MPSCNNDropoutGradientState * __nullable) temporaryResultStateForCommandBuffer: (__nonnull id <MTLCommandBuffer>) commandBuffer
                                                                    sourceImage: (MPSImage *__nonnull) sourceImage
                                                                   sourceStates: (NSArray <MPSState *> *__nullable) sourceStates
                                                               destinationImage: (MPSImage * __nonnull) dest NS_UNAVAILABLE;

-(MPSCNNDropoutGradientStateBatch * __nullable) temporaryResultStateBatchForCommandBuffer: (__nonnull id <MTLCommandBuffer>) commandBuffer NS_UNAVAILABLE;

@end /* MPSCNNDroput */


#pragma mark -
#pragma mark MPSCNNDropoutGradient
    
/*!
 *  @class      MPSCNNDropoutGradient
 *  @dependency This depends on Metal.framework
 *  @discussion This filter is the backward filter for the MPSCNNDropout forward filter.
 *              It requires the mask data, along with all the associated parameters used
 *              to generate the mask, from the forward pass. The mask is associated with
 *              a MPSCNNDropoutGradientState object.
 *
 *              In this kernel, use the secondaryOffset to apply an offset to the mask data.
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3))
@interface MPSCNNDropoutGradient : MPSCNNGradientKernel

/*! @property   keepProbability
 *  @abstract   The probability that each element in the input is kept.
 *              The valid range is (0.0f, 1.0f).
 */
@property (readonly, nonatomic) float keepProbability;

/*! @property   seed
 *  @abstract   The seed used to generate random numbers.
 */
@property (readonly, nonatomic) NSUInteger seed;

/*! @property   maskStrideInPixels
 *  @abstract   The mask stride in the x, y, and x dimensions, which
 *              allows for the broadcasting the mask data.
 *  @discussion The only valid values are 0 and 1 for each dimension.
 *              For no broadcasting, set the values for each dimension
 *              to 1. For broadcasting, set desired values to 0.
 */
@property (readonly, nonatomic) MTLSize maskStrideInPixels;

/*
 * You must use initWithDevice:keepProbability:seed:maskStrideInPixels: instead.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

/*! @abstract <NSSecureCoding> support */
-(nullable instancetype) initWithCoder: (NSCoder * __nonnull) aDecoder
                                device: (nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

/*! @abstract   Standard init with default properties per filter type.
 *  @param      device              The device that the filter will be used on.
 *  @param      keepProbability     The probability that each element in the input is kept.
 *                                  The valid range is (0.0f, 1.0f).
 *  @param      seed                The seed used to generate random numbers.
 *  @param      maskStrideInPixels  The mask stride in the x, y, and z dimensions, which
 *                                  allows for the broadcasting of mask data. The only valid
 *                                  values are 0 and 1 for each dimension. For no
 *                                  broadcasting, set the values for each dimension to 1.
 *                                  For broadcasting, set desired values to 0.
 *  @result     A valid MPSCNNDropoutGradient object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                       keepProbability: (float) keepProbability
                                  seed: (NSUInteger) seed
                    maskStrideInPixels: (MTLSize) maskStrideInPixels NS_DESIGNATED_INITIALIZER;


@end /* MPSCNNDroputGradient */


#ifdef __cplusplus
}
#endif

#endif /* MPSCNNDropout_h */
