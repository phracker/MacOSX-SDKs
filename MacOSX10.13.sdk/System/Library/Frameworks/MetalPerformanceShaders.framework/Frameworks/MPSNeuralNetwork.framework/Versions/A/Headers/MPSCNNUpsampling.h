//
//  MPSCNNUpsampling.h
//  MPS
//
//  Created by Anna Tikhonova on 9/1/16.
//  Copyright © 2016 Apple. All rights reserved.
//

#ifndef MPSCNNUpsampling_h
#define MPSCNNUpsampling_h

#import <MPSNeuralNetwork/MPSCNNKernel.h>

#ifdef __cplusplus
extern "C" {
#endif


#pragma mark -
#pragma mark MPSCNNUpsampling

/*!
 *  @class      MPSCNNUpsampling
 *  @dependency This depends on Metal.framework
 *  @discussion The MPSCNNUpsampling filter can be used to resample an existing MPSImage
 *              using a different sampling frequency for the x and y dimensions with the purpose of
 *              enlarging the size of an image.
 *
 *              The number of output feature channels remains the same as the number of input feature
 *              channels.
 *
 *              The scaleFactor must be an integer value >= 1. The default value is 1.
 *              If scaleFactor == 1, the filter acts as a copy kernel.
 *              
 *              Nearest and bilinear variants are supported.
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0))
@interface MPSCNNUpsampling : MPSCNNKernel

/*! @property   scaleFactorX
 *  @abstract   The upsampling scale factor for the x dimension. The default value is 1.
 */
@property(readonly, nonatomic) double      scaleFactorX;

/*! @property   scaleFactorY
 *  @abstract   The upsampling scale factor for the y dimension. The default value is 1.
 */
@property(readonly, nonatomic) double      scaleFactorY;

/*
 * You must use initWithDevice:scaleFactorX:scaleFactorY instead.
 * You must use one of the sub-classes of MPSCNNUpsampling.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

@end /* MPSCNNUpsampling */


#pragma mark -
#pragma mark MPSCNNUpsamplingNearest
    
/*!
 *  @class      MPSCNNUpsamplingNearest
 *  @dependency This depends on Metal.framework.
 *  @discussion Specifies the nearest spatial upsampling filter.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface MPSCNNUpsamplingNearest : MPSCNNUpsampling

/*!
 *  @abstract  Initialize the nearest spatial upsampling filter.
 *  @param     device                   The device the filter will run on.
 *  @param     integerScaleFactorX      The upsampling factor for the x dimension.
 *  @param     integerScaleFactorY      The upsampling factor for the y dimension.
 *  @return    A valid MPSCNNUpsamplingNearest object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                   integerScaleFactorX: (NSUInteger) integerScaleFactorX
                   integerScaleFactorY: (NSUInteger) integerScaleFactorY NS_DESIGNATED_INITIALIZER;

@end /* MPSCNNUpsamplingNearest */


#pragma mark -
#pragma mark MPSCNNUpsamplingBilinear

/*!
 *  @class      MPSCNNUpsamplingBilinear
 *  @dependency This depends on Metal.framework.
 *  @discussion Specifies the bilinear spatial upsampling filter.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface MPSCNNUpsamplingBilinear : MPSCNNUpsampling

/*!
 *  @abstract  Initialize the bilinear spatial upsampling filter.
 *  @param     device                   The device the filter will run on.
 *  @param     integerScaleFactorX      The upsampling factor for the x dimension.
 *  @param     integerScaleFactorY      The upsampling factor for the y dimension.
 *  @return    A valid MPSCNNUpsamplingBilinear object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                   integerScaleFactorX: (NSUInteger) integerScaleFactorX
                   integerScaleFactorY: (NSUInteger) integerScaleFactorY NS_DESIGNATED_INITIALIZER;

@end    /* MPSCNNUpsamplingBilinear */


#ifdef __cplusplus
}
#endif

#endif /* MPSCNNUpsampling_h */

