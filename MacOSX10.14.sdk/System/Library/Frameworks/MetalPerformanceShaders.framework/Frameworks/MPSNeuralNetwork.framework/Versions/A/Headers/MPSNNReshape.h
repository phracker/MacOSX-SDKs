//
//  MPSNNReshape.h
//  MPSNeuralNetwork
//
//  Created by Aaftab Munshi on 12/11/17.
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef MPSNNReshape_h
#define MPSNNReshape_h

#include <MPSNeuralNetwork/MPSCNNKernel.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  @class      MPSNNReshape
 *  @dependency This depends on Metal.framework
 *  @abstract   Describes a reshape operation
 *  @discussion This functions copies data from source MPSImage intot the new shape in the destination MPSImage
 *
 */

MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3))
@interface MPSNNReshape : MPSCNNKernel

/*!
 *  @abstract Initialize a MPSNNReshape kernel
 *  @param    device    The device the filter will run on
 *  @return   A valid MPSNNReshape object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device     NS_DESIGNATED_INITIALIZER;


-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(__nonnull id<MTLDevice>)device    NS_DESIGNATED_INITIALIZER;

@end  /* MPSNNReshape_h */

/*!
 *  @class      MPSNNReshapeGradient
 *  @dependency This depends on Metal.framework
 *  @discussion The reshape gradient filter reshapes the incoming gradient into the dimensions
 *              of the forward reshape kernel's source image.
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.14.1), ios(12.1), tvos(12.1))
@interface MPSNNReshapeGradient : MPSCNNGradientKernel

/*!
 *  @abstract   Initializes a MPSNNReshapeGradient function
 *  @param      device  The MTLDevice on which this filter will be used
 *
 *  @return     A valid MPSNNReshapeGradient object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

/*! @abstract NSSecureCoding compatability
 *  @discussion While the standard NSSecureCoding/NSCoding method
 *              -initWithCoder: should work, since the file can't
 *              know which device your data is allocated on, we
 *              have to guess and may guess incorrectly.  To avoid
 *              that problem, use initWithCoder:device instead.
 *  @param      aDecoder    The NSCoder subclass with your serialized MPSKernel
 *  @param      device      The MTLDevice on which to make the MPSKernel
 *  @return     A new MPSKernel object, or nil if failure.
 */
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

@end    /* MPSNNReshapeGradient */





/*
 *  @class      MPSNNPad
 *  @dependency This depends on Metal.framework
 *  @abstract   Describes a padding operation
 *  @discussion You should not use this filter to zero pad your data in the XY-plane.
 *              This filter achieves padding by copying the input image and therefore should only be used in
 *              special circumstances where the normal padding operation, defined for most filters through
 *              @ref MPSNNPadding, cannot achieve the necessary padding. Therefore use this filter only when
 *              you need one of the special edge modes: @ref MPSImageEdgeModeConstant,
 *              @ref MPSImageEdgeModeMirror, @ref MPSImageEdgeModeMirrorWithEdge or, if you need padding in the
 *              feature-channel dimesion.  In other cases use to @ref MPSNNPadding for best performance.
 *              This kernel copies data from source MPSImage into the destination MPSImage allowing special padding
 *              modes to be applied. It also enables easy to use arbitrary padding area sizes when used in conjuction
 *              with @ref destinationImageDescriptorForSourceImages:sourceStates: function.
 *              There are two main ways to control the amount of padding to be added in 'x' and 'y' image dimensions:
 *                  - The first one involves passing in an existing MPSImage as the destination image
 *              to the @ref MPSCNNKernel encode call, in which case the padding size in (x,y) plane
 *              is defined by the user-specified @ref clipRect and @ref offset properties of the kernel.
 *                  - In the second one the destination image size and @ref clipRect and @ref offset
 *              properties of the kernel are automatically computed by calling
 *              @ref destinationImageDescriptorForSourceImages:sourceStates: or the -encode calls that return the
 *              resulting image from the left hand side of the call. In this case, the properties
 *              @ref paddingSizeBefore and @ref paddingSizeAfter together with the source image
 *              dimensions define the size of the destination image and set the correct @ref offset
 *              and @ref clipRect properties to the filter.
 *              Padding in the feature channel dimension is handled a bit differently: the amount of
 *              padding is always determined by @ref paddingSizeBefore.channel and
 *              @ref paddingSizeAfter.channel for this direction and the amount of feature channels
 *              filled in the destination is determined by the number of active feature channels
 *              determined by @ref sourceFeatureChannelOffset and @ref sourceFeatureChannelMaxCount and
 *              the amount of padding to be added on each side of the source.
 *
 *              Example for feature channel indices:
 *  @code
 *                  paddingSizeBefore.channel = 2, paddingSizeAfter.channel = 3,
 *                  sourceFeatureChannelOffset = 1, sourceFeatureChannelMaxCount = 3,
 *                  destinationFeatureChannelOffset = 4.
 *                  We get the following padding operation:
 *
 *              Source:
 *                |-----------------------------|
 *                | x0 | x1 | x2 | x3 | x4 | x5 |
 *                |-----------------------------|
 *              Destination:
 *                |----------------------------------------------------------------|
 *                | -  | -  | -  | -  | 0  | 0  | x1 | x2 | x3 | 0  | 0  | 0  | -  |
 *                |----------------------------------------------------------------|
 *
 *              And with @ref edgeMode = MPSImageEdgeModeMirrorWithEdge:
 *
 *              Source:
 *                |-----------------------------|
 *                | x0 | x1 | x2 | x3 | x4 | x5 |
 *                |-----------------------------|
 *              Destination:
 *                |----------------------------------------------------------------|
 *                | -  | -  | -  | -  | x2 | x1 | x1 | x2 | x3 | x3 | x2 | x1 | -  |
 *                |----------------------------------------------------------------|
 *
 *              Here the symbols '-' denote pixels not written by the kernel.
 *
 *              NOTE:   The 'channel' coordinate and size in sourceRegion can be
 *                      set to other values than those with multiple of four channels,
 *                      but the @ref destinationFeatureChannelOffset property must be multiple of
 *                      four, which means that there are some limitations to what can be achieved
 *                      with this filter alone.
 *
 *  @endcode
 *              @NOTE:  MPSNNPad is currently the only filter that supports
 *                      @ref MPSImageEdgeModeMirror, @ref MPSImageEdgeModeMirrorWithEdge and
 *                      @ref MPSImageEdgeModeConstant.
 *
 */

MPS_CLASS_AVAILABLE_STARTING(macos(10.14.1), ios(12.1), tvos(12.1))
@interface MPSNNPad : MPSCNNKernel

/*! @property   paddingSizeBefore
 *  @abstract   This property is used for automatically sizing the destination image
 *              for the function @ref destinationImageDescriptorForSourceImages:sourceStates:. Defines
 *              how much padding to assign on the left, top and smaller feature channel indices
 *              of the image. NOTE: the x and y coordinates of this property are only
 *              used through @ref destinationImageDescriptorForSourceImages:sourceStates:, since
 *              the clipRect and offset together define the padding sizes in those directions, but
 *              the 'channel' size defines the amount of padding to be applied in the feature
 *              channel dimension, before the feature channels starting from feature channel
 *              index @ref sourceFeatureChannelOffset.
 *              Default: { 0, 0, 0 }
 */
@property(readwrite, nonatomic) MPSImageCoordinate  paddingSizeBefore;

/*! @property   paddingSizeAfter
 *  @abstract   This property is used for automatically sizing the destination image
 *              for the function @ref destinationImageDescriptorForSourceImages:sourceStates:. Defines
 *              how much padding to assign on the right, bottom and higher feature channel indices
 *              of the image. NOTE: the x and y coordinates of this property are only
 *              used through @ref destinationImageDescriptorForSourceImages:sourceStates:, since
 *              the clipRect and offset together define the padding sizes in those directions, but
 *              the 'channel' size defines the amount of padding to be applied in the feature
 *              channel dimension after source feature channel index determined by the sum of
 *              @ref sourceFeatureChannelOffset and @ref sourceFeatureChannelMaxCount, naturally
 *              clipped to fit the feature channels in the provided source image.
 *              Default: { 0, 0, 0 }
 */
@property(readwrite, nonatomic) MPSImageCoordinate  paddingSizeAfter;


/*! @property   fillValue
 *  @abstract   Determines the constant value to apply when using @ref MPSImageEdgeModeConstant. Default: 0.0f.
 *              NOTE: this value is ignored if the filter is initialized with a per-channel fill value
 *              using @ref initWithDevice:paddingSizeBefore:paddingSizeAfter:fillValueArray:.
 */
@property(readwrite, nonatomic) float               fillValue;

/*!
 *  @abstract Initialize a MPSNNPad kernel
 *  @param      device      The device the filter will run on.
 *  @return     A valid MPSNNPad object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device;

/*!
 *  @abstract Initialize a MPSNNPad kernel
 *  @param      device              The device the filter will run on
 *  @param      paddingSizeBefore   The amount of padding to add before the source image - see details above.
 *  @param      paddingSizeAfter    The amount of padding to add after the source image - see details above.
 *  @return     A valid MPSNNPad object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                     paddingSizeBefore: (MPSImageCoordinate) paddingSizeBefore
                      paddingSizeAfter: (MPSImageCoordinate) paddingSizeAfter;
/*!
 *  @abstract Initialize a MPSNNPad kernel
 *  @param      device              The device the filter will run on
 *  @param      paddingSizeBefore   The amount of padding to add before the source image - see details above.
 *  @param      paddingSizeAfter    The amount of padding to add after the source image - see details above.
 *  @param      fillValueArray      A NSData containing a float array to use with @ref MPSImageEdgeModeConstant.
 *                                  The first value of the array will correspond to the first feature channel
 *                                  written out to the destination image and the number of float values in the
 *                                  data must be at least as large as the number of feature channels written onto
 *                                  the destination by the filter. Failing to pass a large enough array will
 *                                  result in undefined behavior. Passing in nil is fine.
 *  @return     A valid MPSNNPad object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                     paddingSizeBefore: (MPSImageCoordinate) paddingSizeBefore
                      paddingSizeAfter: (MPSImageCoordinate) paddingSizeAfter
                        fillValueArray: (NSData* __nullable) fillValueArray
NS_DESIGNATED_INITIALIZER;


/*! @abstract   NSSecureCoding compatability
 *  @discussion See @ref MPSKernel#initWithCoder.
 *  @param      aDecoder    The NSCoder subclass with your serialized MPSNNPad
 *  @param      device      The MTLDevice on which to make the MPSNNPad
 *  @return     A new MPSNNPad object, or nil if failure.
 */

-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(__nonnull id<MTLDevice>)device    NS_DESIGNATED_INITIALIZER;


@end  /* MPSNNPad */


/*!
 *  @class      MPSNNPadGradient
 *  @dependency This depends on Metal.framework
 *  @discussion Computes the gradient for the @ref MPSNNPad layer.
 *              Since the padding forward operation typically increases the size of the image, the gradient operation
 *              decreases it. In case of zero or constant padding forward operation the gradient operation slices the
 *              input gradient and in other edge modes the padded values copied in the forward operation are
 *              summed together in the gradient operation.
 *              For Example for the @ref MPSImageEdgeModeClamp the forward operation with offset = -2, destSize = 8
 *              or @ref paddingSizeBefore = 2, @ref paddingSizeAfter = 3, sourceSize = 3:
 *  @code
 *              Source Image:
 *                |--------------|
 *                | x0 | x1 | x2 |
 *                |--------------|
 *              Destination Image:
 *                |---------------------------------------|
 *                | x0 | x0 | x0 | x1 | x2 | x2 | x2 | x2 |
 *                |---------------------------------------|
 *  @endcode
 *              Then the gradient operation becomes:
 *  @code
 *              Source Gradient Image:
 *                |---------------------------------------|
 *                | d0 | d1 | d2 | d3 | d4 | d5 | d6 | d7 |
 *                |---------------------------------------|
 *              Destination Gradient Image:
 *                |-----------------------------|
 *                | d0+d1+d2 | d3 | d4+d5+d6+d7 |
 *                |-----------------------------|
 *  @endcode
 *              Another example with @ref MPSImageEdgeModeMirror, the forward operation with offset = -4, destSize = 8
 *              or @ref paddingSizeBefore = 4, @ref paddingSizeAfter = 1, sourceSize = 3:
 *  @code
 *              Source Image:
 *                |--------------|
 *                | x0 | x1 | x2 |
 *                |--------------|
 *              Destination Image:
 *                |---------------------------------------|
 *                | x0 | x1 | x2 | x1 | x0 | x1 | x2 | x1 |
 *                |---------------------------------------|
 *  @endcode
 *              Then the gradient operation becomes:
 *  @code
 *              Source Gradient Image:
 *                |---------------------------------------|
 *                | d0 | d1 | d2 | d3 | d4 | d5 | d6 | d7 |
 *                |---------------------------------------|
 *              Destination Gradient Image:
 *                |-----------------------------|
 *                | d0+d4 | d1+d3+d5+d7 | d2+d6 |
 *                |-----------------------------|
 *  @endcode
 *
 *              NOTE: There are no channel fill-values to use with @ref MPSImageEdgeModeConstant
 *              since the gradient values are independent of the constant of the forward pass.
 *              NOTE: In case the forward pass defined a slice operation in feature channels then
 *              the channels not read in the forward pass will be filled with zeros in the gradient pass.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.14.1), ios(12.1), tvos(12.1))
@interface MPSNNPadGradient : MPSCNNGradientKernel


/*!
 *  @abstract   Initializes a MPSNNPadGradient filter
 *  @param      device  The MTLDevice on which this filter will be used
 *
 *  @return     A valid MPSNNPadGradient object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

/*! @abstract   NSSecureCoding compatability
 *  @discussion See @ref MPSKernel#initWithCoder.
 *  @param      aDecoder    The NSCoder subclass with your serialized MPSNNPadGradient.
 *  @param      device      The MTLDevice on which to make the MPSNNPadGradient.
 *  @return     A new MPSNNPadGradient object, or nil if failure.
 */
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

@end    /* MPSNNPadGradient */



#ifdef __cplusplus
}
#endif

#endif /* MPSNNReshape_h */
