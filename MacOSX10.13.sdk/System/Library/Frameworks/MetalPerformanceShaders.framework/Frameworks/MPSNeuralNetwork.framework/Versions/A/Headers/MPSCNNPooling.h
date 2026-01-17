//
//  MPSCNNPooling.h
//  MPS
//
//  Created by Ian Ollmann on 8/21/16.
//  Copyright © 2016 Apple. All rights reserved.
//

#ifndef MPSCNNPooling_h
#define MPSCNNPooling_h

#import <MPSNeuralNetwork/MPSCNNKernel.h>
#import <MPSCore/MPSCore.h>

#ifdef __cplusplus
extern "C" {
#endif



/*!
 *  @class      MPSCNNPooling
 *  @dependency This depends on Metal.framework
 *  @discussion Pooling is a form of non-linear sub-sampling. Pooling partitions the input image into a set of
 *              rectangles (overlapping or non-overlapping) and, for each such sub-region, outputs a value.
 *              The pooling operation is used in computer vision to reduce the dimensionality of intermediate representations.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(10.0), tvos(10.0))
@interface  MPSCNNPooling : MPSCNNKernel


/*!
 *  @abstract  Initialize a pooling filter
 *  @param      device              The device the filter will run on
 *  @param      kernelWidth         The width of the kernel.  Can be an odd or even value.
 *  @param      kernelHeight        The height of the kernel.  Can be an odd or even value.
 *  @return     A valid MPSCNNPooling object or nil, if failure.
 *
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                           kernelWidth: (NSUInteger) kernelWidth
                          kernelHeight: (NSUInteger) kernelHeight;

/*!
 *  @abstract  Initialize a pooling filter
 *  @param      device              The device the filter will run on
 *  @param      kernelWidth         The width of the kernel.  Can be an odd or even value.
 *  @param      kernelHeight        The height of the kernel.  Can be an odd or even value.
 *  @param      strideInPixelsX     The output stride (downsampling factor) in the x dimension.
 *  @param      strideInPixelsY     The output stride (downsampling factor) in the y dimension.
 *  @return     A valid MPSCNNPooling object or nil, if failure.
 *
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                           kernelWidth: (NSUInteger) kernelWidth
                          kernelHeight: (NSUInteger) kernelHeight
                       strideInPixelsX: (NSUInteger) strideInPixelsX
                       strideInPixelsY: (NSUInteger) strideInPixelsY NS_DESIGNATED_INITIALIZER;



/*! @abstract NSSecureCoding compatability
 *  @discussion See @ref MPSKernel#initWithCoder.
 *  @param      aDecoder    The NSCoder subclass with your serialized MPSCNNPooling
 *  @param      device      The MTLDevice on which to make the MPSCNNPooling
 *  @return     A new MPSCNNPooling object, or nil if failure.
 */
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER
MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0));



/*
 * Use initWithDevice:kernelWidth:kernelHeight:strideInPixelsX:strideInPixelsY: instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;


/*!
 *          Pooling window notes
 *          ====================
 *          The encodeToCommandBuffer API in MPSCNNKernel can be used to encode a MPSCNNPooling kernel
 *          to a MTLCommandBuffer. The exact location of the pooling window for each output value is determined
 *          as follows: The pooling window center for the first (top left) output pixel of the clipping
 *          rectangle is at spatial coordinates (offset.x, offset.y) in the input image. From this
 *          the top left corner of the pooling window is at
 *              (offset.x - floor(kernelWidth/2), offset.y - floor(kernelHeight/2)) and
 *          extends of course (kernelWidth, kernelHeight) pixels to the right and down direction, which means
 *          that the last pixel to be included into the pooling window is at:
 *              (offset.x + floor((kernelWidth-1)/2), offset.y + floor((kernelHeight-1)/2)),
 *          so that for even kernel sizes the pooling window is extends one pixel more into the left and up
 *          directions.
 *          The following pooling windows can be then easily deduced from the first one by simple shifting
 *          the source coordinates according to values of @ref strideInPixelsX and @ref strideInPixelsY.
 *          For example the pooling window center w(x,y) for the output value at coordinate (x,y) of the
 *          destination clip rectangle ((x,y) computed wrt. clipping rectangle origin) is at:
 *              w(x,y) = ( offset.x + strideInPixelsX * x , offset.y + strideInPixelsY * y ).
 *
 *          Quite often it is desirable to distribute the pooling windows as evenly as possible in the
 *          input image. As explained above, if offset is zero, then the center of the first pooling
 *          window is at the top left corner of the input image, which means that the left and top stripes
 *          of the pooling window are read from outside the input image boundaries (when filter size is
 *          larger than unity). Also it may mean that some values from the bottom and right stripes are
 *          not included at all in the pooling resulting in loss of valuable information. The different
 *          padding styles and padding sizes, or alternatively @ref offset and @edgeMode, can be used
 *          to control pooling window placement and boundary handling.
 *
 *
 *          For @ref MPSCNNPoolingMax the way the input image borders are handled (see @ref edgeMode)
 *          can become important: if there are negative values in the source image near the borders of the
 *          image and the pooling window crosses the borders, then using @ref MPSImageEdgeModeZero may
 *          cause the maximum pooling operation to override the negative input data values with zeros
 *          coming from outside the source image borders, resulting in large boundary effects. A simple
 *          way to avoid this is to use @ref MPSImageEdgeModeClamp for @ref edgeMode, which for
 *          @ref MPSCNNPoolingMax effectively causes all pooling windows to remain within the source image.
 *
 *
 *          Below are a couple of examples that can be used to visualize the effects of different
 *          offset values for pooling. The illustrations show the pooling window placements inside a
 *          single feature channel of a source image. In the first examples we use strides that are
 *          larger than the pooling window sizes in order to clarify the placement of each
 *          individual pooling window.
 *@code
 *              Source image: width = 8, height = 5
 *              Destination cliprect: width = 3, height = 2
 *              o - source pixel center, one for each destination cliprect pixel
 *              x - filter taps in the pooling windows
 *@endcode
 *          1) Filter size = 2x2, stride = 3x3, offset = (0,0)
 *@code
 *              x  x     x  x     x  x
 *                |-----------------------|
 *              x |xo|  |x |xo|  |x |xo|  |
 *                |-----------------------|
 *                |  |  |  |  |  |  |  |  |
 *                |-----------------------|
 *              x |x |  |x |x |  |x |x |  |
 *                |-----------------------|
 *              x |xo|  |x |xo|  |x |xo|  |
 *                |-----------------------|
 *                |  |  |  |  |  |  |  |  |
 *                |-----------------------|
 *@endcode
 *          One can use @ref offset to move the pooling windows within the source image:
 *          Using the formula offset.xy += (int)floor( ((L.xy - 1) % s.xy) / 2 ) + 1 from above
 *          for even filter sizes gives:
 *@code
 *              offset.x = floor( (7 % 3) / 2) + 1 = 0 + 1 = 1 and
 *              offset.y = floor( (4 % 3) / 2) + 1 = 0 + 1 = 1.
 *@endcode
 *          2) Filter size = 2x2, stride = 3x3, offset = (1,1)
 *@code
 *                |-----------------------|
 *                |x |x |  |x |x |  |x |x |
 *                |-----------------------|
 *                |x |xo|  |x |xo|  |x |xo|
 *                |-----------------------|
 *                |  |  |  |  |  |  |  |  |
 *                |-----------------------|
 *                |x |x |  |x |x |  |x |x |
 *                |-----------------------|
 *                |x |xo|  |x |xo|  |x |xo|
 *                |-----------------------|
 *@endcode
 *
 *          Our third example shows the placement of additional taps when we increase
 *          the size of the pooling window to 3x3.
 *          In this case the recommended formula for offsets with odd filter sizes gives:
 *@code
 *              offset.x = ceil( (7 % 3) / 2) = 1 and
 *              offset.y = ceil( (4 % 3) / 2) = 1.
 *@endcode
 *          3) Filter size = 3x3, stride = 3x3, offset = (1,1)
 *@code
 *                |-----------------------|
 *                |x |x |x |x |x |x |x |x |x
 *                |-----------------------|
 *                |x |xo|x |x |xo|x |x |xo|x
 *                |-----------------------|
 *                |x |x |x |x |x |x |x |x |x
 *                |-----------------------|
 *                |x |x |x |x |x |x |x |x |x
 *                |-----------------------|
 *                |x |xo|x |x |xo|x |x |xo|x
 *                |-----------------------|
 *                 x  x  x  x  x  x  x  x  x
 *@endcode
 *          In order to avoid large boundary effects with max pooling in examples 1) and 3) the user can use
 *          @ref MPSImageEdgeModeClamp for @ref edgeMode, which has the same effect as constraining the pooling
 *          windows to be confined completely within the source image.
 *
 */

@end    /* MPSCNNPooling */


/*!
 *  @class MPSCNNPoolingMax
 *  @dependency This depends on Metal.framework
 *  @discussion Specifies the max pooling filter.  For each pixel, returns the maximum value of pixels
 *              in the kernelWidth x kernelHeight filter region.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(10.0), tvos(10.0))
@interface  MPSCNNPoolingMax : MPSCNNPooling

/*!
 *  @abstract   Initialize a MPSCNNPoolingMax pooling filter
 *  @param      device              The device the filter will run on
 *  @param      kernelWidth         The width of the kernel.  Can be an odd or even value.
 *  @param      kernelHeight        The height of the kernel.  Can be an odd or even value.
 *  @param      strideInPixelsX     The output stride (downsampling factor) in the x dimension.
 *  @param      strideInPixelsY     The output stride (downsampling factor) in the y dimension.
 *  @return     A valid MPSCNNPooling object or nil, if failure.
 *
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                           kernelWidth: (NSUInteger) kernelWidth
                          kernelHeight: (NSUInteger) kernelHeight
                       strideInPixelsX: (NSUInteger) strideInPixelsX
                       strideInPixelsY: (NSUInteger) strideInPixelsY NS_DESIGNATED_INITIALIZER;


/*! @abstract NSSecureCoding compatability
 *  @discussion See @ref MPSKernel#initWithCoder.
 *  @param      aDecoder    The NSCoder subclass with your serialized MPSCNNPooling
 *  @param      device      The MTLDevice on which to make the MPSCNNPooling
 *  @return     A new MPSCNNPooling object, or nil if failure.
 */
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER
MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0));

@end    /* MPSCNNPoolingMax */


/*!
 *  @class MPSCNNPoolingAverage
 *  @dependency This depends on Metal.framework
 *  @discussion Specifies the average pooling filter.  For each pixel, returns the mean value of pixels
 *              in the kernelWidth x kernelHeight filter region.
 *              When @ref edgeMode is @ref MPSImageEdgeModeClamp the filtering window is shrunk to remain
 #              within the source image borders. What this means is that close to image borders the filtering window
 *              will be smaller in order to fit inside the source image and less values will be used to compute the
 *              average. In case the filtering window is entirely outside the source image border the
 *              outputted value will be zero.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(10.0), tvos(10.0))
@interface  MPSCNNPoolingAverage : MPSCNNPooling



/*! @property   zeroPadSizeX
 *  @abstract   How much zero padding to apply to both left and right borders of the input image for average pooling,
 *              when using @see edgeMode MPSImageEdgeModeClamp. For @see edgeMode MPSImageEdgeModeZero this property is
 *              ignored and the area outside the image is interpreted to contain zeros.
 *              The zero padding size is used to shrink the pooling window to fit inside the area bound by the source image
 *              and its padding region, but the effect is that the normalization factor of the average computation is computed
 *              also for the zeros in the padding region.
 */
@property(readwrite, nonatomic) NSUInteger zeroPadSizeX;

/*! @property   zeroPadSizeY
 *  @abstract   How much zero padding to apply to both top and bottom borders of the input image for average pooling,
 *              when using @see edgeMode MPSImageEdgeModeClamp. For @see edgeMode MPSImageEdgeModeZero this property is
 *              ignored and the area outside the image is interpreted to contain zeros.
 *              The zero padding size is used to shrink the pooling window to fit inside the area bound by the source image
 *              and its padding region, but the effect is that the normalization factor of the average computation is computed
 *              also for the zeros in the padding region.
 */
@property(readwrite, nonatomic) NSUInteger zeroPadSizeY;





/*!
 *  @abstract   Initialize a MPSCNNPoolingAverage pooling filter
 *  @param      device              The device the filter will run on
 *  @param      kernelWidth         The width of the kernel.  Can be an odd or even value.
 *  @param      kernelHeight        The height of the kernel.  Can be an odd or even value.
 *  @param      strideInPixelsX     The output stride (downsampling factor) in the x dimension.
 *  @param      strideInPixelsY     The output stride (downsampling factor) in the y dimension.
 *  @return     A valid MPSCNNPooling object or nil, if failure.
 *
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                           kernelWidth: (NSUInteger) kernelWidth
                          kernelHeight: (NSUInteger) kernelHeight
                       strideInPixelsX: (NSUInteger) strideInPixelsX
                       strideInPixelsY: (NSUInteger) strideInPixelsY NS_DESIGNATED_INITIALIZER;

/*! @abstract NSSecureCoding compatability
 *  @discussion See @ref MPSKernel#initWithCoder.
 *  @param      aDecoder    The NSCoder subclass with your serialized MPSCNNPooling
 *  @param      device      The MTLDevice on which to make the MPSCNNPooling
 *  @return     A new MPSCNNPooling object, or nil if failure.
 */
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER
MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0));

@end    /* MPSCNNPoolingAverage */


/*!
 *  @class MPSCNNPoolingL2Norm
 *  @dependency This depends on Metal.framework
 *  @discussion Specifies the L2-norm pooling filter.  For each pixel, returns L2-Norm of pixels
 *              in the kernelWidth x kernelHeight filter region.
 *                  out[c,x,y] = sqrt ( sum_{dx,dy} in[c,x+dx,y+dy] * in[c,x+dx,y+dy] ).
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface  MPSCNNPoolingL2Norm : MPSCNNPooling

/*!
 *  @abstract   Initialize a MPSCNNPoolingL2Norm pooling filter
 *  @param      device              The device the filter will run on
 *  @param      kernelWidth         The width of the kernel.  Can be an odd or even value.
 *  @param      kernelHeight        The height of the kernel.  Can be an odd or even value.
 *  @param      strideInPixelsX     The output stride (downsampling factor) in the x dimension.
 *  @param      strideInPixelsY     The output stride (downsampling factor) in the y dimension.
 *  @return     A valid MPSCNNPooling object or nil, if failure.
 *
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                           kernelWidth: (NSUInteger) kernelWidth
                          kernelHeight: (NSUInteger) kernelHeight
                       strideInPixelsX: (NSUInteger) strideInPixelsX
                       strideInPixelsY: (NSUInteger) strideInPixelsY NS_DESIGNATED_INITIALIZER;

/*! @abstract NSSecureCoding compatability
 *  @discussion See @ref MPSKernel#initWithCoder.
 *  @param      aDecoder    The NSCoder subclass with your serialized MPSCNNPooling
 *  @param      device      The MTLDevice on which to make the MPSCNNPooling
 *  @return     A new MPSCNNPooling object, or nil if failure.
 */
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

@end    /* MPSCNNPoolingL2Norm */


/*!
 *  @class MPSCNNDilatedPoolingMax
 *  @dependency This depends on Metal.framework
 *  @discussion Specifies the dilated max pooling filter.  For each pixel, returns the maximum value of pixels
 *              in the kernelWidth x kernelHeight filter region by step size dilationFactorX x dilationFactorY.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface  MPSCNNDilatedPoolingMax : MPSCNNPooling

/*! @property   dilationRateX
 *  @abstract   dilationRateX for accessing the image passed in as source
 */
@property(readonly, nonatomic) NSUInteger dilationRateX;

/*! @property   dilationRateY
 *  @abstract   dilationRateY for accessing the image passed in as source
 */
@property(readonly, nonatomic) NSUInteger dilationRateY;




/*!
 *  @abstract   Initialize a MPSCNNDilatedPoolingMax pooling filter
 *  @param      device              The device the filter will run on
 *  @param      kernelWidth         The width of the kernel.  Can be an odd or even value.
 *  @param      kernelHeight        The height of the kernel.  Can be an odd or even value.
 *  @param      dilationRateX       The dilation rate in the x dimension.
 *  @param      dilationRateY       The dilation rate in the y dimension.
 *  @param      strideInPixelsX     The output stride (downsampling factor) in the x dimension.
 *  @param      strideInPixelsY     The output stride (downsampling factor) in the y dimension.
 *  @return     A valid MPSCNNDilatedPoolingMax object or nil, if failure.
 *
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                           kernelWidth: (NSUInteger) kernelWidth
                          kernelHeight: (NSUInteger) kernelHeight
                         dilationRateX: (NSUInteger) dilationRateX
                         dilationRateY: (NSUInteger) dilationRateY
                       strideInPixelsX: (NSUInteger) strideInPixelsX
                       strideInPixelsY: (NSUInteger) strideInPixelsY NS_DESIGNATED_INITIALIZER;



/*! @abstract NSSecureCoding compatability
 *  @discussion See @ref MPSKernel.h initWithCoder.
 *  @param      aDecoder    The NSCoder subclass with your serialized MPSCNNDilatedPoolingMax
 *  @param      device      The MTLDevice on which to make the MPSCNNDilatedPoolingMax
 *  @return     A new MPSCNNDilatedPoolingMax object, or nil if failure.
 */
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

@end    /* MPSCNNDilatedPoolingMax */


#ifdef __cplusplus
}
#endif


#endif /* MPSCNNPooling_h */
