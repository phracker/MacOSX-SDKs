//
//  MPSCNNUpsampling.h
//  MPS
//
//  Created on 9/1/16.
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
MPS_CLASS_AVAILABLE_STARTING(macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0))
@interface MPSCNNUpsampling : MPSCNNKernel

/*! @property   scaleFactorX
 *  @abstract   The upsampling scale factor for the x dimension. The default value is 1.
 */
@property(readonly, nonatomic) double      scaleFactorX;

/*! @property   scaleFactorY
 *  @abstract   The upsampling scale factor for the y dimension. The default value is 1.
 */
@property(readonly, nonatomic) double      scaleFactorY;

/*! @property   alignCorners
 *  @abstract   If YES, the centers of the 4 corner pixels of the input and output regions are aligned,
 *              preserving the values at the corner pixels.
 *              The default is NO.
 */
@property(readonly, nonatomic) BOOL      alignCorners;

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
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0))
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
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0))
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
                   integerScaleFactorY: (NSUInteger) integerScaleFactorY;

/*!
 *  @abstract  Initialize the bilinear spatial upsampling filter.
 *  @param     device                   The device the filter will run on.
 *  @param     integerScaleFactorX      The upsampling factor for the x dimension.
 *  @param     integerScaleFactorY      The upsampling factor for the y dimension.
 *  @param     alignCorners             Specifier whether the centers of the 4 corner pixels of the input and output regions are aligned,
 *                                      preserving the values at the corner pixels.
 *  @return    A valid MPSCNNUpsamplingBilinear object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                   integerScaleFactorX: (NSUInteger) integerScaleFactorX
                   integerScaleFactorY: (NSUInteger) integerScaleFactorY
                          alignCorners: (BOOL) alignCorners NS_DESIGNATED_INITIALIZER;

@end    /* MPSCNNUpsamplingBilinear */


#pragma mark -
#pragma mark MPSCNNUpsamplingGradient
    
/*!
 *  @class      MPSCNNUpsamplingGradient
 *  @dependency This depends on Metal.framework
 *  @discussion The MPSCNNUpsamplingGradient filter is used for training. It is the backward
 *              filter for the MPSCNNUpsampling filter. It operates on the gradient input,
 *              specifically, it reduces the size of the gradient input in the x and y dimensions.
 *
 *              The number of output feature channels remains the same as the number of input feature
 *              channels.
 *
 *              The scaleFactor must be an integer value >= 1. The default value is 1.
 *              If scaleFactor == 1, the filter acts as a copy kernel.
 *
 *              Nearest and bilinear variants are supported.
 *
 *              For example, for the nearest variant with scaleFactorX = scaleFactorY = 2, the
 *              forward pass produced the following output:
 *
 *              Input:	    Output:
 *                          a a b b
 *              a b         a a b b
 *              c d         c c d d
 *                          c c d d
 *
 *              To upsample the image, the input data is replicated.
 *
 *              And, the backward pass for the above froward pass is computed in the following
 *              way:
 *
 *              Input:		    Output:
 *              a1 a2 b1 b2
 *              a2 a3 b3 b4	    x y
 *              c1 c2 d1 d2	    z w
 *              c3 c4 d3 d4
 *
 *              where	x = a1 + a2 + a3 + a4
 *                      y = b1 + b2 + b3 + b4
 *                      z = c1 + c2 + c3 + c4
 *                      w = d1 + d2 + d3 + d4
 *
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
@interface MPSCNNUpsamplingGradient : MPSCNNGradientKernel

/*! @property   scaleFactorX
 *  @abstract   The downsampling scale factor for the x dimension. The default value is 1.
 */
@property(readonly, nonatomic) double      scaleFactorX;

/*! @property   scaleFactorY
 *  @abstract   The downsampling scale factor for the y dimension. The default value is 1.
 */
@property(readonly, nonatomic) double      scaleFactorY;

/*
 * You must use initWithDevice:scaleFactorX:scaleFactorY instead.
 * You must use one of the sub-classes of MPSCNNUpsamplingGradient.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;


@end /* MPSCNNUpsamplingGradient */
    
    
#pragma mark -
#pragma mark MPSCNNUpsamplingNearestGradient
    
/*!
 *  @class      MPSCNNUpsamplingNearestGradient
 *  @dependency This depends on Metal.framework.
 *  @discussion Specifies the nearest spatial downsampling filter.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
@interface MPSCNNUpsamplingNearestGradient : MPSCNNUpsamplingGradient

/*!
 *  @abstract  Initialize the nearest spatial upsampling filter.
 *  @param     device                   The device the filter will run on.
 *  @param     integerScaleFactorX      The downsampling factor for the x dimension.
 *  @param     integerScaleFactorY      The downsampling factor for the y dimension.
 *  @return    A valid MPSCNNUpsamplingNearestGradient object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                   integerScaleFactorX: (NSUInteger) integerScaleFactorX
                   integerScaleFactorY: (NSUInteger) integerScaleFactorY NS_DESIGNATED_INITIALIZER;

@end /* MPSCNNUpsamplingNearestGradient */
    
    
#pragma mark -
#pragma mark MPSCNNUpsamplingBilinearGradient
    
/*!
 *  @class      MPSCNNUpsamplingBilinearGradient
 *  @dependency This depends on Metal.framework.
 *  @discussion Specifies the bilinear spatial downsampling filter.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
@interface MPSCNNUpsamplingBilinearGradient : MPSCNNUpsamplingGradient

/*!
 *  @abstract  Initialize the bilinear spatial downsampling filter.
 *  @param     device                   The device the filter will run on.
 *  @param     integerScaleFactorX      The downsampling factor for the x dimension.
 *  @param     integerScaleFactorY      The downsampling factor for the y dimension.
 *  @return    A valid MPSCNNUpsamplingBilinearGradient object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                   integerScaleFactorX: (NSUInteger) integerScaleFactorX
                   integerScaleFactorY: (NSUInteger) integerScaleFactorY NS_DESIGNATED_INITIALIZER;

@end    /* MPSCNNUpsamplingBilinearGradient */


#ifdef __cplusplus
}
#endif

#endif /* MPSCNNUpsampling_h */
