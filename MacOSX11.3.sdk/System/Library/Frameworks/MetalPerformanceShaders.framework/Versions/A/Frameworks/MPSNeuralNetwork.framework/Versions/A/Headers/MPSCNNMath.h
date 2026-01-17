//
//  MPSCNNMath.h
//  MPS
//
//  Created on 11/17/17.
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef MPSCNNMath_h
#define MPSCNNMath_h

#import <MPSNeuralNetwork/MPSCNNKernel.h>

#ifdef __cplusplus
extern "C" {
#endif

    
#pragma mark -
#pragma mark MPSCNNArithmeticGradientState

/*!
 *  @class      MPSCNNArithmeticGradientState
 *  @dependency This depends on Metal.framework.
 *  @discussion The MPSCNNArithmeticGradientState is used to hold the clamp mask used by both
 *              MPSCNNArithmetic forward filter and MPSCNNArithmeticGradient backward filter.
 *              The MPSCNNArithmetic forward filter populates the MPSCNNArithmeticGradientState
 *              object and the MPSCNNArithmeticGradient backward filter consumes the state
 *              object.
 *
 *              The clamp mask is stored internally and is not accessible by the user.
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
@interface MPSCNNArithmeticGradientState : MPSNNBinaryGradientState

/*
 * Use [MPSCNNDropout resultStateForSourceImage:...] or other variants instead
 */
-(nonnull instancetype) init NS_UNAVAILABLE;

@end


#pragma mark -
#pragma mark MPSCNNArithmeticGradientStateBatch

typedef NSArray<MPSCNNArithmeticGradientState*> MPSCNNArithmeticGradientStateBatch
MPS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3));


#pragma mark -
#pragma mark MPSCNNArithmetic

/*!
 *  @class      MPSCNNArithmetic
 *  @dependency This depends on Metal.framework
 *  @discussion The MPSCNNArithmetic filter takes two source images, a primary source image and a
 *              secondary source image, and outputs a single destination image. It applies an
 *              element-wise arithmetic operator to each pixel in a primary source image and a
 *              corresponding pixel in a secondary source image over a specified region.
 *
 *              The supported arithmetic operators are the following:
 *              - Addition
 *              - Subtraction
 *              - Multiplication
 *              - Division
 *              - Comparison
 *
 *              This filter takes additional parameters: primaryScale, secondaryScale, and bias. The default
 *              value for primaryScale and secondaryScale is 1.0f. The default value for bias is 0.0f. This
 *              filter applies primaryScale, secondaryScale, and bias to the primary source pixel (x) and
 *              secondary source pixel (y) in the following way:
 *              - Addition:         result = ((primaryScale * x) + (secondaryScale * y)) + bias
 *              - Subtraction:      result = ((primaryScale * x) - (secondaryScale * y)) + bias
 *              - Multiplicaton:    result = ((primaryScale * x) * (secondaryScale * y)) + bias
 *              - Division:         result = ((primaryScale * x) / (secondaryScale * y)) + bias
 *              - Comparison:       Unused.
 *
 *              To clamp the result of an arithmetic operation, where
 *              result = clamp(result, minimumValue, maximumValue),
 *              set the minimumValue and maximumValue appropriately. The default value of minimumValue
 *              is -FLT_MAX. The default value of maximumValue is FLT_MAX.
 *
 *              This filter also takes the following additional parameters:
 *              - primaryStrideInPixelsX, primaryStrideInPixelsY, primaryStrideInFeatureChannels
 *              - secondaryStrideInPixelsX, secondaryStrideInPixelsY, secondaryStrideInFeatureChannels
 *              These parameters can be used to control broadcasting for the data stored in the primary and
 *              secondary source images. For example, setting all strides for the primary source image to 0
 *              will result in the primarySource image being treated as a scalar value. The only supported
 *              values are 0 or 1. The default value of these parameters is 1.
 *
 *              The number of output feature channels remains the same as the number of input feature
 *              channels.
 *
 *              You must use one of the sub-classes of MPSImageArithmetic.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
@interface MPSCNNArithmetic : MPSCNNBinaryKernel

@property (readwrite, nonatomic) float primaryScale;
@property (readwrite, nonatomic) float secondaryScale;
@property (readwrite, nonatomic) float bias;

/*! @property   primaryStrideInPixels
 *  @abstract   The primarySource stride in the feature channel dimension. The only supported values are 0 or 1.
 *              The default value for each dimension is 1.
 */
@property(readwrite, nonatomic) NSUInteger      primaryStrideInFeatureChannels;

/*! @property   secondaryStrideInPixels
 *  @abstract   The secondarySource stride in the feature channel dimension. The only supported values are 0 or 1.
 *              The default value for each dimension is 1.
 */
@property(readwrite, nonatomic) NSUInteger      secondaryStrideInFeatureChannels;

/*! @property   minimumValue
 *  @abstract   minimumValue is to clamp the result of an arithmetic operation:
 *              result = clamp(result, minimumValue, maximumValue).
 *              The default value of minimumValue is -FLT_MAX.
 */
@property (readwrite, nonatomic) float          minimumValue;

/*! @property   maximumValue
 *  @abstract   maximumValue is used to clamp the result of an arithmetic operation:
 *              result = clamp(result, minimumValue, maximumValue).
 *              The default value of maximumValue is FLT_MAX.
 */
@property (readwrite, nonatomic) float          maximumValue;

/*
 * You must use one of the sub-classes of MPSCNNArithmetic.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;


/*! @abstract       Encode call that operates on a state for later consumption by a gradient kernel in training
 *  @discussion     This is the older style of encode which reads the offset, doesn't change it,
 *                  and ignores the padding method.
 *  @param          commandBuffer       The command buffer
 *  @param          primaryImage        A MPSImage to use as the source images for the filter.
 *  @param          secondaryImage      A MPSImage to use as the source images for the filter.
 *  @param          destinationState    MPSCNNArithmeticGradientState to be consumed by the gradient layer
 *  @param          destinationImage    A valid MPSImage to be overwritten by result image. destinationImage
 *                                      may not alias primarySourceImage or secondarySourceImage.
 */
-(void) encodeToCommandBuffer: (__nonnull id <MTLCommandBuffer>) commandBuffer
                 primaryImage: (MPSImage * __nonnull) primaryImage
               secondaryImage: (MPSImage * __nonnull) secondaryImage
             destinationState: (MPSCNNArithmeticGradientState * __nonnull) destinationState
             destinationImage: (MPSImage * __nonnull) destinationImage
MPS_SWIFT_NAME( encode(commandBuffer:primaryImage:secondaryImage:destinationState:destinationImage:));


/*!
 *  @abstract   Encode call that operates on a state for later consumption by a gradient kernel in training
 *  @discussion This is the older style of encode which reads the offset, doesn't change it,
 *              and ignores the padding method. Multiple images are processed concurrently.
 *              All images must have MPSImage.numberOfImages = 1.
 *  @param      commandBuffer         A valid MTLCommandBuffer to receive the encoded filter
 *  @param      primaryImages         An array of MPSImage objects containing the primary source images.
 *  @param      secondaryImages       An array MPSImage objects containing the secondary source images.
 *  @param      destinationStates     An array of MPSCNNArithmeticGradientStateBatch to be consumed by the gradient layer
 *  @param      destinationImages     An array of MPSImage objects to contain the result images.
 *                                    destinationImages may not alias primarySourceImages or secondarySourceImages
 *                                    in any manner.
 */
-(void) encodeBatchToCommandBuffer: (__nonnull id <MTLCommandBuffer>) commandBuffer
                     primaryImages: (MPSImageBatch * __nonnull) primaryImages
                   secondaryImages: (MPSImageBatch * __nonnull) secondaryImages
                 destinationStates: (MPSCNNArithmeticGradientStateBatch * __nonnull) destinationStates
                 destinationImages: (MPSImageBatch * __nonnull) destinationImages
MPS_SWIFT_NAME( encodeBatch(commandBuffer:primaryImages:secondaryImages:destinationStates:destinationImages:));



@end /* MPSCNNArithmetic */


#pragma mark -
#pragma mark MPSCNNAdd
    
/*!
 *  @class      MPSCNNAdd
 *  @dependency This depends on Metal.framework.
 *  @discussion Specifies the addition operator.
 *              For each pixel in the primary source image (x) and each pixel in a secondary source image (y),
 *              it applies the following function: result = ((primaryScale * x) + (secondaryScale * y)) + bias.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
@interface  MPSCNNAdd : MPSCNNArithmetic

/*!
 *  @abstract  Initialize the addition operator.
 *  @param     device           The device the filter will run on.
 *  @return    A valid MPSCNNAdd object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

@end    /* MPSCNNAdd */


#pragma mark -
#pragma mark MPSCNNSubtract

/*!
 *  @class      MPSCNNSubtract
 *  @dependency This depends on Metal.framework.
 *  @discussion Specifies the subtraction operator.
 *              For each pixel in the primary source image (x) and each pixel in a secondary source image (y),
 *              it applies the following function: result = ((primaryScale * x) - (secondaryScale * y)) + bias.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
@interface  MPSCNNSubtract : MPSCNNArithmetic

/*!
 *  @abstract  Initialize the subtraction operator
 *  @param     device           The device the filter will run on.
 *  @return    A valid MPSCNNSubtract object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

@end    /* MPSCNNSubtract */


#pragma mark -
#pragma mark MPSCNNMultiply

/*!
 *  @class      MPSCNNMultiply
 *  @dependency This depends on Metal.framework.
 *  @discussion Specifies the multiplication operator.
 *              For each pixel in the primary source image (x) and each pixel in a secondary source image (y),
 *              it applies the following function: result = ((primaryScale * x) * (secondaryScale * y)) + bias.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
@interface  MPSCNNMultiply : MPSCNNArithmetic

/*!
 *  @abstract  Initialize the multiplication operator
 *  @param     device           The device the filter will run on.
 *  @return    A valid MPSCNNMultiply object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

@end    /* MPSCNNMultiply */
    

#pragma mark -
#pragma mark MPSCNNDivide

/*!
 *  @class      MPSCNNDivide
 *  @dependency This depends on Metal.framework.
 *  @discussion Specifies the division operator.
 *              For each pixel in the primary source image (x) and each pixel in a secondary source image (y),
 *              it applies the following function: result = ((primaryScale * x) / (secondaryScale * y)) + bias.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
@interface  MPSCNNDivide : MPSCNNArithmetic

/*!
 *  @abstract  Initialize the division operator
 *  @param     device           The device the filter will run on.
 *  @return    A valid MPSCNNDivide object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

@end    /* MPSCNNDivide */

#pragma mark -
#pragma mark MPSNNCompare

/*! @enum       MPSNNComparisonType
 *  @abstract   The type of comparison an MPSNNCompare kernel should perform.
 */
#if defined(DOXYGEN)
    typedef enum MPSNNComparisonType
#else
    typedef NS_OPTIONS(NSUInteger, MPSNNComparisonType)
#endif
{
    MPSNNComparisonTypeEqual       MPS_ENUM_AVAILABLE_STARTING( macos(10.14.1), ios(12.1), macCatalyst(13.0), tvos(12.1))   MPS_SWIFT_NAME(equal),
    MPSNNComparisonTypeNotEqual    MPS_ENUM_AVAILABLE_STARTING( macos(10.14.1), ios(12.1), macCatalyst(13.0), tvos(12.1))   MPS_SWIFT_NAME(notEqual),
    MPSNNComparisonTypeLess        MPS_ENUM_AVAILABLE_STARTING( macos(10.14.1), ios(12.1), macCatalyst(13.0), tvos(12.1))   MPS_SWIFT_NAME(less),
    MPSNNComparisonTypeLessOrEqual MPS_ENUM_AVAILABLE_STARTING( macos(10.14.1), ios(12.1), macCatalyst(13.0), tvos(12.1))   MPS_SWIFT_NAME(lessOrEqual),
    MPSNNComparisonTypeGreater     MPS_ENUM_AVAILABLE_STARTING( macos(10.14.1), ios(12.1), macCatalyst(13.0), tvos(12.1))   MPS_SWIFT_NAME(greater),
    MPSNNComparisonTypeGreaterOrEqual  MPS_ENUM_AVAILABLE_STARTING( macos(10.14.1), ios(12.1), macCatalyst(13.0), tvos(12.1))   MPS_SWIFT_NAME(greaterOrEqual)
};
    
/*!
 *  @class      MPSNNCompare
 *  @dependency This depends on Metal.framework.
 *  @discussion Specifies the elementwise comparison operator.
 *              For each pixel in the primary source image (x) and each pixel in a secondary source image (y),
 *              it applies the following function: result = (abs(x-y)) <= threshold
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.14.1), ios(12.1), macCatalyst(13.0), tvos(12.1))
@interface  MPSNNCompare : MPSCNNArithmetic
/*! @property   comparisonType
 *  @abstract   The comparison type to use
 */
@property (readwrite, nonatomic) MPSNNComparisonType   comparisonType;

/*! @property   threshold
 *  @abstract   The threshold to use when comparing for equality.  Two values will
 *              be considered to be equal if the absolute value of their difference
 *              is less than, or equal, to the specified threshold:
 *                  result = |b - a| <= threshold
 */
@property (readwrite, nonatomic) float          threshold;

/*!
 *  @abstract  Initialize the comparison operator
 *  @param     device           The device the filter will run on.
 *  @return    A valid MPSNNCompare object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

@end    /* MPSNNCompare */

#pragma mark -
#pragma mark MPSCNNArithmeticGradient

/*!
 *  @class      MPSCNNArithmeticGradient
 *  @dependency This depends on Metal.framework
 *  @discussion The MPSCNNArithmeticGradient filter is the backward filter for the MPSCNNArithmetic
 *              forward filter.
 *
 *              The forward filter takes two inputs, primary and secondary source images, and produces
 *              a single output image. Thus, going backwards requires two separate filters (one for
 *              the primary source image and one for the secondary source image) that take multiple
 *              inputs and produce a single output. The secondarySourceFilter property is used to
 *              indicate whether the filter is operating on the primary or secondary source image from
 *              the forward pass.
 *
 *              All the arithmetic gradient filters require the following inputs: gradient image from
 *              the previous layer (going backwards) and all the applicable input source images from
 *              the forward pass.
 *
 *              The forward filter takes the following additional parameters:
 *              - primaryStrideInPixelsX, primaryStrideInPixelsY, primaryStrideInFeatureChannels
 *              - secondaryStrideInPixelsX, secondaryStrideInPixelsY, secondaryStrideInFeatureChannels
 *              These parameters can be used in the forward filter to control broadcasting for the data
 *              stored in the primary and secondary source images. For example, setting all strides for
 *              the primary source image to 0 will result in the primarySource image being treated as a
 *              single pixel. The only supported values are 0 or 1. The default value of these parameters
 *              is 1.
 *
 *              The first input to the backward filter is the gradient image from the previous layer
 *              (going backwards), so there are no broadcasting parameters for this input. For the
 *              backward filter, the broadcasting parameters for the second input must match the
 *              broadcasting parameters set for the same image in the forward filter.
 *
 *              In the backward pass, broadcasting results in a reduction operation (sum) across all of the
 *              applicable broadcasting dimensions (rows, columns, feature channels, or any combination
 *              thereof) to produce the destination image of the size that matches the primary/secondary
 *              input images used in the forward pass.
 *
 *              In the case of no broadcasting, the following arithmetic gradient operations are copy
 *              operations (that can be optimized away by the graph interface):
 *              - Add (primarySource, secondarySource)
 *              - Subtract (primarySource)
 *
 *              Similarly to the forward filter, this backward filter takes additional parameters:
 *              primaryScale, secondaryScale, and bias. The default value for primaryScale and secondaryScale
 *              is 1.0f. The default value for bias is 0.0f. This filter applies primaryScale to the primary
 *              source image, applies the secondaryScale to the secondary source image, where appropriate,
 *              and applies bias to the result, i.e.:
 *              result = ((primaryScale * x) [insert operation] (secondaryScale * y)) + bias.
 *
 *              The subtraction gradient filter for the secondary source image requires that the primaryScale
 *              property is set to -1.0f (for x - y, d/dy(x - y) = -1).
 *
 *              In the forward filter, there is support for clamping the result of the available operations,
 *              where result = clamp(result, minimumValue, maximumValue). The clamp backward operation is
 *              not supported in the arithmetic gradient filters. If you require this functionality, it can
 *              be implemented by performing a clamp backward operation before calling the arithmetic gradient
 *              filters. You would need to apply the following function on the incomping gradient input image:
 *              f(x) = ((minimumValue < x) && (x < maximumValue)) ? 1 : 0, where x is the original result
 *              (before clamping) of the forward arithmetic filter.
 *
 *              The number of output feature channels remains the same as the number of input feature
 *              channels.
 *
 *              You must use one of the sub-classes of MPSImageArithmeticGradient.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
@interface MPSCNNArithmeticGradient : MPSCNNGradientKernel

@property (readwrite, nonatomic) float primaryScale;
@property (readwrite, nonatomic) float secondaryScale;
@property (readwrite, nonatomic) float bias; /* bias is ignored in the backward pass */

/*! @property   secondaryStrideInPixels
 *  @abstract   The secondarySource stride in the feature channel dimension. The only supported values are 0 or 1.
 *              The default value for each dimension is 1.
 */
@property(readwrite, nonatomic) NSUInteger      secondaryStrideInFeatureChannels;

/*! @property   minimumValue
 *  @abstract   minimumValue is to clamp the result of an arithmetic operation:
 *              result = clamp(result, minimumValue, maximumValue).
 *              The default value of minimumValue is -FLT_MAX.
 */
@property (readwrite, nonatomic) float          minimumValue;

/*! @property   maximumValue
 *  @abstract   maximumValue is used to clamp the result of an arithmetic operation:
 *              result = clamp(result, minimumValue, maximumValue).
 *              The default value of maximumValue is FLT_MAX.
 */
@property (readwrite, nonatomic) float          maximumValue;

/*! @property   isSecondarySourceFilter
 *  @abstract   The isSecondarySourceFilter property is used to indicate whether the arithmetic gradient
 *              filter is operating on the primary or secondary source image from the forward pass.
 */
@property (readonly, nonatomic) BOOL            isSecondarySourceFilter;

/*
 * You must use one of the sub-classes of MPSCNNArithmetic.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

/*
 * You must use one of the sub-classes of MPSCNNArithmetic.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
               isSecondarySourceFilter: (BOOL) isSecondarySourceFilter NS_UNAVAILABLE;

@end /* MPSCNNArithmetic */


#pragma mark -
#pragma mark MPSCNNAddGradient

/*!
 *  @class      MPSCNNAddGradient
 *  @dependency This depends on Metal.framework.
 *  @discussion Specifies the addition gradient operator.
 *              This arithmetic gradient filter requires the following inputs: gradient image from
 *              the previous layer (going backwards) and either the primary or the secondary source
 *              image from the forward pass. You will need a separate filter for the primary and
 *              secondary source images.
 *
 *              Without broadcasting, the arithmetic add gradient operation is a copy operation on
 *              the input gradient image. It is the same operation for both the primary and secondary
 *              source images (for x + y, d/dx(x + y) = 1, d/dy(x + y) = 1). This copy operation can
 *              be optimized away by the graph interface.
 *
 *              Setting the broadcasting parameters results in a reduction operation (sum) across all
 *              of the applicable broadcasting dimensions (rows, columns, feature channels, or any
 *              combination thereof) to produce the destination image of the size that matches the
 *              primary/secondary input images used in the forward pass.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
@interface  MPSCNNAddGradient : MPSCNNArithmeticGradient

/*!
 *  @abstract  Initialize the addition gradient operator.
 *  @param     device                   The device the filter will run on.
 *  @param     isSecondarySourceFilter  A boolean indicating whether the arithmetic gradient
 *             filter is operating on the primary or secondary source image from the forward pass.
 *  @return    A valid MPSCNNAddGradient object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
               isSecondarySourceFilter: (BOOL) isSecondarySourceFilter NS_DESIGNATED_INITIALIZER;

@end    /* MPSCNNAddGradient */
    
    
#pragma mark -
#pragma mark MPSCNNSubtractGradient

/*!
 *  @class      MPSCNNSubtractGradient
 *  @dependency This depends on Metal.framework.
 *  @discussion Specifies the subtraction gradient operator.
 *              This arithmetic gradient filter requires the following inputs: gradient image from
 *              the previous layer (going backwards) and either the primary or the secondary source
 *              image from the forward pass. You will need a separate filter for the primary and
 *              secondary source images.
 *
 *              Without broadcasting, the arithmetic subtract gradient operation for the primary
 *              source image is a copy operation on the input gradient image (for x - y, d/dx(x - y) = 1).
 *              This copy operation can be optimized away by the graph interface.
 *
 *              For the secondary source image, the result is a negation of the gradient image from
 *              the previous layer (for x - y, d/dy(x - y) = -1).
 *
 *              Setting the broadcasting parameters results in a reduction operation (sum) across all
 *              of the applicable broadcasting dimensions (rows, columns, feature channels, or any
 *              combination thereof) to produce the destination image of the size that matches the
 *              primary/secondary input images used in the forward pass.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
@interface  MPSCNNSubtractGradient : MPSCNNArithmeticGradient

/*!
 *  @abstract  Initialize the subtraction gradient operator.
 *  @param     device                   The device the filter will run on.
 *  @param     isSecondarySourceFilter  A boolean indicating whether the arithmetic gradient
 *             filter is operating on the primary or secondary source image from the forward pass.
 *  @return    A valid MPSCNNSubtractGradient object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
               isSecondarySourceFilter: (BOOL) isSecondarySourceFilter NS_DESIGNATED_INITIALIZER;

@end    /* MPSCNNSubtractGradient */


#pragma mark -
#pragma mark MPSCNNMultiplyGradient

/*!
 *  @class      MPSCNNMultiplyGradient
 *  @dependency This depends on Metal.framework.
 *  @discussion Specifies the multiplication gradient operator.
 *              This arithmetic gradient filter requires the following inputs: gradient image from
 *              the previous layer (going backwards) and either the primary or the secondary source
 *              image from the forward pass. You will need a separate filter for the primary and
 *              secondary source images.
 *
 *              Without broadcasting, the arithmetic multiply gradient operation is an element-wise
 *              multiplication operation between the gradient image from the previous layer (going
 *              backwards) and:
 *              - The secondary source image from the forward pass for the primary source filter
 *                (for x * y, d/dx(x * y) = y).
 *              - The primary source image from the forward pass for the secondary source filter
 *                (for x * y, d/dy(x * y) = x).
 *
 *              Setting the broadcasting parameters results in a reduction operation (sum) across all
 *              of the applicable broadcasting dimensions (rows, columns, feature channels, or any
 *              combination thereof) to produce the destination image of the size that matches the
 *              primary/secondary input images used in the forward pass.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
@interface  MPSCNNMultiplyGradient : MPSCNNArithmeticGradient

/*!
 *  @abstract  Initialize the multiplication gradient operator.
 *  @param     device                   The device the filter will run on.
 *  @param     isSecondarySourceFilter  A boolean indicating whether the arithmetic gradient
 *             filter is operating on the primary or secondary source image from the forward pass.
 *  @return    A valid MPSCNNMultiplyGradient object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
               isSecondarySourceFilter: (BOOL) isSecondarySourceFilter NS_DESIGNATED_INITIALIZER;

@end    /* MPSCNNMultiplyGradient */


#ifdef __cplusplus
}
#endif

#endif /* MPSCNNMath_h */
