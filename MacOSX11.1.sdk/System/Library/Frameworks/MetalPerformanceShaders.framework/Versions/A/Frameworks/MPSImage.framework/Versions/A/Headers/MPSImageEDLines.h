//
//  MPSImageEDLinesPrivate.h
//  MPSImage
//
//  Created by Christopher Bayley on 11/22/19.
//  Copyright © 2019 Apple. All rights reserved.
//

#ifndef MPSImageEDLinesPrivate_h
#define MPSImageEDLinesPrivate_h

/*!
 *  @class      MPSImageEDLines
 *  @discussion The MPSImageEDLInes class implements the EDLines line segmenting algorithm using edge-drawing (ED)
 *              described here
 *              https://ieeexplore.ieee.org/document/6116138
 *
 *              The EDLInes algorithm consists of 5 steps, the first 4 of which describe the ED algorithm:
 *              1. Blur the source image using a Gaussian blur with a sigma parameter
 *              2. Use horizontal and vertical Sobel filters to find a gradient magnitude and
 *                direction.
 *                  G = sqrt(Sx^2 + Sy^2)
 *                  G_ang = arctan(Sy / Sx)
 *              3. Compute anchor points, points with a high probability of being edge pixels.
 *                Anchor points are local maxima, in the gradient image that lie on row and column
 *                multiples of the detailRatio. This parameter effectively downsamples the gradient
 *                image, and directly influences the density of anchor points. A larger detailRatio results
 *                in fewer fine grained details, leaving long, main lines.
 *              4. Anchor points are traced in a forward and backward direction along the gradient direction, until
 *                the gradient falls below some gradientThreshold parameter or the edge of the image is reached.
 *                The paths traced become an edge map of the image.
 *              5. Points in the edges are fit to a line), and extended along the edge until the line error crosses a
 *                lineErrorThreshold. Lines which are beyond a minimum length are labelled line segments and
 *                will be outputs of the algorithm.
 */

MPS_CLASS_AVAILABLE_STARTING( macos(10.15.4), ios(13.4), macCatalyst(13.4), tvos(13.4))
@interface  MPSImageEDLines : MPSKernel

/*! @abstract   Initialize an EDLines kernel on a given device with specified parameters.
 *  @param      device             The device the filter will run on
 *  @param      gaussianSigma     The standard deviation of gaussian blur filter.
 *                          Gaussian weight, centered at 0, at integer grid i is given as
 *                @code
 *                          w(i) = 1/sqrt(2*pi*sigma) * exp(-i^2/2*sigma^2)
 *                @endcode
 *                          If we take cut off at 1% of w(0) (max weight) beyond which weights
 *                          are considered 0, we have
 *                @code
 *                          ceil (sqrt(-log(0.01)*2)*sigma) ~ ceil(3.7*sigma)
 *                @endcode
 *                          as rough estimate of filter width
 *  @param      minLineLength           The minimum length of output line segments.
 *  @param      maxLines                      The maximum amount of lines for the EDLines algorithm to output. The size of the
 *                                endpointBuffer supplied at encode must be >= maxLines * 4 * sizeof(unsigned short) + sizeof(uint32_t).
 *  @param      detailRatio                The detailRatio to use in the EDLines algorithm, which
 *                                inversely effects the number of anchor points
 *  @param      gradientThreshold   Any pixel with a gradient below the gradientThreshold will
 *                                not be considerd an edge
 *  @param      lineErrorThreshold  The limit of how much error a line segment can have relative
 *                                to the edge it represents
 *  @param      mergeLocalityThreshold  Determines how many pixels apart two lines can deviate spatially and still be merged.
 *                                     This value is normalized to the diagonal length of the image.
 *  @return     A valid object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                         gaussianSigma: (const float) gaussianSigma
                         minLineLength: (const unsigned short) minLineLength
                              maxLines: (const NSUInteger) maxLines
                           detailRatio: (const unsigned short) detailRatio
                     gradientThreshold: (const float) gradientThreshold
                    lineErrorThreshold: (const float) lineErrorThreshold
                mergeLocalityThreshold: (const float) mergeLocalityThreshold NS_DESIGNATED_INITIALIZER;


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


/*!
 * @abstract Encode the filter to a command buffer using a MTLComputeCommandEncoder.
 * @discussion The filter will not begin to execute until after the command
 *    buffer has been enqueued and committed.
 *
 * @param  commandBuffer           A valid MTLCommandBuffer.
 * @param  source                  A valid MTLTexture containing the source image for the filter
 * @param  dest              A valid MTLTexture containing the destination image for the filter. If not nil, the output will be the edges
 *                   found through the Edge Drawing algorithm.
 * @param  endpointBuffer         A valid MTLBuffer to receive the line segment count and endpoint results.
 * @param  endpointOffset         Byte offset into endpoint buffer at which to write the  line segment endpoint results. Must be a multiple of 32 bytes.
 *                                The total line segment count and the line segment endpoints are written to the endpoint buffer. The count
 *                                is written as a uint32_t at the start of the buffer. The line segments are written to the endpoint buffer as
 *                                start and end pixel coordinates of the segment. Coordinates are stored as unsigned short pairs, and a
 *                                single line segment will consist of two pairs, or four total unsigned shorts. The endpoint buffer size must
 *                                be >= 4 * maxLines * sizeof(unsigned short) + sizeof(uint32_t).
*/
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                sourceTexture: (nonnull id <MTLTexture>) source
           destinationTexture: (nullable id <MTLTexture>) dest
               endpointBuffer: (nonnull id <MTLBuffer>) endpointBuffer
               endpointOffset: (NSUInteger) endpointOffset;

/*! @property   clipRectSource
 *  @abstract   The source rectangle to use when reading data.
 *  @discussion A MTLRegion that indicates which part of the source to read. If the clipRectSource does not lie
 *              completely within the source image, the intersection of the image bounds and clipRectSource will
 *              be used. The clipRectSource replaces the MPSUnaryImageKernel offset parameter for this filter.
 *              The latter is ignored.   Default: MPSRectNoClip, use the entire source texture.
 */
@property (readwrite, nonatomic) MTLRegion clipRectSource;

/*! @property sigma
 *  @abstract Read-only sigma value used in performing Gaussian blur of the image.
 *            Default is 2.0
 */
@property (readonly, nonatomic) float gaussianSigma;

/*! @property minLineLength
 *  @abstract Read-write value used to set the minimum length of a line segment.
 *            Default is 32
 */
@property (readwrite, nonatomic) unsigned short minLineLength;

/*! @property maxLines
 *  @abstract Read-write value used to set the max number of line segments to be written out.
 *            The endpointBuffer at encode must be >= maxLines * 4 * sizeof(unsigned short) + sizeof(uint32_t).
 *            Default is 256
 */
@property (readwrite, nonatomic) NSUInteger maxLines;

/*! @property detailRatio
 *  @abstract Read-write value used to set the detailRatio to use in the EDLines algorithm
 *            Default is 32
 */
@property (readwrite, nonatomic) unsigned short detailRatio;

/*! @property gradientThreshold
 *  @abstract Read-write value used to set the threshold for a pixel to be considered an edge
 *            Default is 0.2
 */
@property (readwrite, nonatomic) float gradientThreshold;

/*! @property lineErrorThreshold
 *  @abstract Read-write value used to set the limit on error for a line segment relative to the edge it fits
 *            Default is 0.05
 */
@property (readwrite, nonatomic) float lineErrorThreshold;

/*! @property mergeLocalityThreshold
 *  @abstract Read-write value used to set how many pixels apart two lines can deviate spatially and still be merged.
 *            Default is 0.0025
 */
@property (readwrite, nonatomic) float mergeLocalityThreshold;

@end  /* MPSImageEDLines */

#endif /* MPSImageEDLinesPrivate_h */
