/*!
 *  @header MPSImageMath.h
 *  @framework MetalPerformanceShaders.framework
 *
 *  @copyright Copyright (c) 2016 Apple Inc. All rights reserved.
 *  @abstract MetalPerformanceShaders math filters
 */

#ifndef MPS_MPSImageMath_h
#define MPS_MPSImageMath_h

#include <MPSImage/MPSImageKernel.h>
#include <simd/simd.h>


/*!
 *  @class      MPSImageArithmetic
 *  @dependency This depends on Metal.framework.
 *  @discussion This filter takes two source images, a primary source image and a secondary source image,
 *              and outputs a single destination image. It applies an element-wise arithmetic operator to
 *              each pixel in a primary source image and a corresponding pixel in a secondary source image
 *              over a specified region.
 *              
 *              The supported arithmetic operators are the following:
 *              - Addition
 *              - Subtraction
 *              - Multiplication
 *              - Division
 *
 *              This filter takes additional parameters: primaryScale, secondaryScale, and bias. The default
 *              value for primaryScale and secondaryScale is 1.0f. The default value for bias is 0.0f. This
 *              filter applies primaryScale, secondaryScale, and bias to the primary source pixel (x) and
 *              secondary source pixel (y) in the following way:
 *              - Addition:         result = ((primaryScale * x) + (secondaryScale * y)) + bias
 *              - Subtraction:      result = ((primaryScale * x) - (secondaryScale * y)) + bias
 *              - Multiplicaton:    result = ((primaryScale * x) * (secondaryScale * y)) + bias
 *              - Division:         result = ((primaryScale * x) / (secondaryScale * y)) + bias
 *
 *              This filter also takes the following additional parameters:
 *              - primaryStrideInPixels
 *              - secondaryStrideInPixels
 *              These parameters can be used to control broadcasting for the data stored in the primary and
 *              secondary source images. For example, setting all strides for the primary source image to 0
 *              will result in the primarySource image being treated as a scalar value. The default value of
 *              these parameters is 1.
 *
 *              This filter accepts uint and int data in addition to unorm and floating-point data.
 *              
 *              You must use one of the sub-classes of MPSImageArithmetic.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface  MPSImageArithmetic : MPSBinaryImageKernel

@property (readwrite, nonatomic) float primaryScale;
@property (readwrite, nonatomic) float secondaryScale;
@property (readwrite, nonatomic) float bias;


/*! @property   primaryStrideInPixels
 *  @abstract   The secondarySource stride in the x, y, and z dimensions. The default value for each dimension is 1.
 */
@property(readwrite, nonatomic) MTLSize         primaryStrideInPixels;

/*! @property   secondaryStrideInPixels
 *  @abstract   The secondarySource stride in the x, y, and z dimensions. The default value for each dimension is 1.
 */
@property(readwrite, nonatomic) MTLSize         secondaryStrideInPixels;

/*
 * You must use one of the sub-classes of MPSImageArithmetic.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

@end    /* MPSImageArithmetic */


/*!
 *  @class      MPSImageAdd
 *  @dependency This depends on Metal.framework.
 *  @discussion Specifies the addition operator.
 *              For each pixel in the primary source image (x) and each pixel in a secondary source image (y),
 *              it applies the following function: result = ((primaryScale * x) + (secondaryScale * y)) + bias.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface  MPSImageAdd : MPSImageArithmetic

/*!
 *  @abstract  Initialize the addition operator
 *  @param     device           The device the filter will run on.
 *  @return    A valid MPSImageAdd object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

@end    /* MPSImageAdd */


/*!
 *  @class      MPSImageSubtract
 *  @dependency This depends on Metal.framework.
 *  @discussion Specifies the subtraction operator.
 *              For each pixel in the primary source image (x) and each pixel in a secondary source image (y),
 *              it applies the following function: result = ((primaryScale * x) - (secondaryScale * y)) + bias.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface  MPSImageSubtract : MPSImageArithmetic

/*!
 *  @abstract  Initialize the subtraction operator
 *  @param     device           The device the filter will run on.
 *  @return    A valid MPSImageSubtract object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

@end    /* MPSImageSubtract */


/*!
 *  @class      MPSImageMultiply
 *  @dependency This depends on Metal.framework.
 *  @discussion Specifies the multiplication operator.
 *              For each pixel in the primary source image (x) and each pixel in a secondary source image (y),
 *              it applies the following function: result = ((primaryScale * x) * (secondaryScale * y)) + bias.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface  MPSImageMultiply : MPSImageArithmetic

/*!
 *  @abstract  Initialize the multiplication operator
 *  @param     device           The device the filter will run on.
 *  @return    A valid MPSImageMultiply object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

@end    /* MPSImageMultiply */


/*!
 *  @class      MPSImageDivide
 *  @dependency This depends on Metal.framework.
 *  @discussion Specifies the division operator.
 *              For each pixel in the primary source image (x) and each pixel in a secondary source image (y),
 *              it applies the following function: result = ((primaryScale * x) / (secondaryScale * y)) + bias.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface  MPSImageDivide : MPSImageArithmetic

/*!
 *  @abstract  Initialize the division operator
 *  @param     device           The device the filter will run on.
 *  @return    A valid MPSImageDivide object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

@end    /* MPSImageDivide */


#endif  /* MPSImageMath_h */

