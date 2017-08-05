/*!
 *  @header MPSImageHistogram.h
 *  @framework MetalPerformanceShaders.framework
 *
 *  @copyright Copyright (c) 2015 Apple Inc. All rights reserved.
 *  @abstract MetalPerformanceShaders histogram filters
 */

#ifndef MPS_MPSImageHistogram_h
#define MPS_MPSImageHistogram_h

#include <MPSImage/MPSImageKernel.h>
#include <simd/simd.h>

/*!
 *  @brief      Specifies information to compute the histogram for channels of an image.
 */
typedef struct
{
    NSUInteger      numberOfHistogramEntries;   /**<  Specifies the number of histogram entries, or "bins" for each channel.  For example, if you want 256 histogram bins then numberOfHistogramEntries must be set to 256.  The value stored in each histogram bin is a 32-bit unsigned integer.  The size of the histogram buffer in which these bins will be stored should be >= numberOfHistogramEntries * sizeof(uint32_t) * number of channels in the image. numberOfHistogramEntries must be a power of 2 and is a minimum of 256 bins.   */
    BOOL            histogramForAlpha;          /**<  Specifies whether the histogram for the alpha channel should be computed or not. */
    vector_float4   minPixelValue;              /**<  Specifies the minimum pixel value.  Any pixel value less than this will be clipped to this value (for the purposes of histogram calculation), and assigned to the first histogram entry. This minimum value is applied to each of the four channels separately. */
    vector_float4   maxPixelValue;              /**<  Specifies the maximum pixel value.  Any pixel value greater than this will be clipped to this value (for the purposes of histogram calculation), and assigned to the first histogram entry. This maximum value is applied to each of the four channels separately. */
} MPSImageHistogramInfo;


/*!
 *  @class      MPSImageHistogram
 *  @discussion The MPSImageHistogram computes the histogram of an image.
 *              
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(9.0), tvos(9.0))
@interface  MPSImageHistogram : MPSKernel

/*! @property   clipRectSource
 *  @abstract   The source rectangle to use when reading data.
 *  @discussion A MTLRegion that indicates which part of the source to read. If the clipRectSource does not lie
 *              completely within the source image, the intersection of the image bounds and clipRectSource will
 *              be used. The clipRectSource replaces the MPSUnaryImageKernel offset parameter for this filter.
 *              The latter is ignored.   Default: MPSRectNoClip, use the entire source texture.
 */
@property (readwrite, nonatomic) MTLRegion clipRectSource;

/*! @property   zeroHistogram
 *  @abstract   Zero-initalize the histogram results
 *  @discussion Indicates that the memory region in which the histogram results are to be written in the
 *              histogram buffer are to be zero-initialized or not. Default: YES.
 */
@property (readwrite, nonatomic) BOOL zeroHistogram;

/*! @property   minPixelThresholdValue
 *  @abstract   The minimum pixel threshold value
 *  @discussion The histogram entries will be incremented only if pixel value is >= minPixelThresholdValue.
 *              The minPixelThresholdValue is a floating-point value.  For unsigned normalized textures, the 
 *              minPixelThresholdValue should be a value between 0.0f and 1.0f (for eg. MTLPixelFormatRGBA8Unorm).
 *              For signed normalized textures, the minPixelThresholdValue should be a value between -1.0f and 1.0f
 *              (for eg. MTLPixelFormatRGBA8Snorm).  Default: vector_float4(0.0f).
 */
@property (readwrite, nonatomic) vector_float4 minPixelThresholdValue;

/*! @property   histogramInfo
 *  @abstract   Return a structure describing the histogram content
 *  @discussion Returns a MPSImageHistogramInfo structure describing the format of the
 *              histogram.
 */
@property (readonly, nonatomic)  MPSImageHistogramInfo histogramInfo;

/*!
 *  @abstract Specifies information to compute the histogram for channels of an image.
 *  @param    device            The device the filter will run on
 *  @param    histogramInfo     Pointer to the MPSHistogramInfo struct
 *  @return     A valid MPSImageHistogram object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                         histogramInfo: (const MPSImageHistogramInfo * __nonnull) histogramInfo     NS_DESIGNATED_INITIALIZER;


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
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER
                        MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0));

/*!
 *  @abstract Encode the filter to a command buffer using a MTLComputeCommandEncoder.
 *  @discussion The filter will not begin to execute until after the command
 *  buffer has been enqueued and committed.
 *
 *
 *  @param  commandBuffer           A valid MTLCommandBuffer.
 *  @param  source                  A valid MTLTexture containing the source image for the filter
 *  @param  histogram               A valid MTLBuffer to receive the histogram results.
 *  @param  histogramOffset         Byte offset into histogram buffer at which to write the histogram results. Must be a multiple of 32 bytes.
 *                                  The histogram results / channel are stored together.  The number of channels for which
 *                                  histogram results are stored is determined by the number of channels in the image.
 *                                  If histogramInfo.histogramForAlpha is false and the source image is RGBA then only histogram
 *                                  results for RGB channels are stored.
 *
 *                                  The histogram results are stored in the histogram buffer as follows:
 *                                      - histogram results for the R channel for all bins followed by
 *                                      - histogram results for the G channel for all bins followed by
 *                                      - histogram results for the B channel for all bins followed by
 *                                      - histogram results for the A channel for all bins
 *
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                sourceTexture: (nonnull id <MTLTexture>) source
                    histogram: (nonnull id <MTLBuffer>) histogram
              histogramOffset: (NSUInteger) histogramOffset;


/*!
 *  @abstract   The amount of space in the output MTLBuffer the histogram will take up.
 *  @discussion This convenience function calculates the minimum amount of space
 *              needed in the output histogram for the results.  The MTLBuffer should
 *              be at least this length, longer if histogramOffset is non-zero.
 *  @param      sourceFormat      The MTLPixelFormat of the source image. This is
 *                                the source parameter of -encodeToCommandBuffer:
 *                                sourceTexture:histogram:histogramOffset
 *  @return     The number of bytes needed to store the result histograms.
 */
-(size_t) histogramSizeForSourceFormat: (MTLPixelFormat) sourceFormat;


@end  /* MPSImageHistogram */

/*!
 *  @class      MPSImageHistogramEqualization
 *  @discussion The MPSImageHistogramEqualization performs equalizes the histogram of an image.
 *              The process is divided into three steps. 
 *
 *              -# Call -initWithDevice:histogramInfo:   This creates a MPSImageHistogramEqualization
 *              object.   It is done when the method returns.
 *  
 *              -# Call -encodeTransform:sourceTexture:histogram:histogramOffset:  This creates a privately held
 *              image transform (i.e. a cumulative distribution function of the histogram) which will be used to 
 *              equalize the distribution of the histogram of the source image. This process runs on a MTLCommandBuffer
 *              when it is committed to a MTLCommandQueue. It must complete before the next step can be run.
 *              It may be performed on the same MTLCommandBuffer.  The histogram argument specifies the histogram
 *              buffer which contains the histogram values for sourceTexture.  The sourceTexture argument is used by
 *              encodeTransform to determine the number of channels and therefore which histogram data in histogram 
 *              buffer to use. The histogram for sourceTexture must have been computed either on the CPU or using 
 *              the MPSImageHistogram kernel
 *
 *              -# Call -encodeToCommandBuffer:sourceTexture:destinationTexture: to read data from
 *              sourceTexture, apply the equalization transform to it and write to destination texture.
 *              This step is also done on the GPU on a MTLCommandQueue.
 *
 *              You can reuse the same equalization transform on other images to perform the
 *              same transform on those images. (Since their distribution is probably different,
 *              they will probably not be equalized by it.) This filter usually will not be able 
 *              to work in place.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(9.0), tvos(9.0))
@interface  MPSImageHistogramEqualization : MPSUnaryImageKernel

/*! @property   histogramInfo
 *  @abstract   Return a structure describing the histogram content
 *  @discussion Returns a MPSImageHistogramInfo structure describing the format of the
 *              histogram.
 */
@property (readonly, nonatomic)  MPSImageHistogramInfo histogramInfo;

/*!
 *  @abstract Specifies information about the histogram for the channels of an image.
 *  @param    device            The device the filter will run on
 *  @param    histogramInfo     Pointer to the MPSHistogramInfo struct
 *  @return     A valid MPSImageHistogramEqualization object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                         histogramInfo: (const MPSImageHistogramInfo * __nonnull) histogramInfo     NS_DESIGNATED_INITIALIZER;

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
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER
                            MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0));

/*!
 *  @abstract Encode the transform function to a command buffer using a MTLComputeCommandEncoder.
 *            The transform function computes the equalization lookup table.
 *  @discussion The transform function will not begin to execute until after the command
 *              buffer has been enqueued and committed.  This step will need to be repeated
 *              with the new MPSKernel if -copyWithZone:device or -copyWithZone: is called.
 *              The transform is stored as internal state to the object. You still need to 
 *              call -encodeToCommandBuffer:sourceTexture:destinationTexture: afterward
 *              to apply the transform to produce a result texture.
 *
 *  @param  commandBuffer   A valid MTLCommandBuffer.
 *  @param  source          A valid MTLTexture containing the source image for the filter.
 *  @param  histogram       A valid MTLBuffer containing the histogram results for an image.  This filter
 *                          will use these histogram results to generate the cumulative histogram for equalizing
 *                          the image.  The histogram results / channel are stored together.  The number of channels
 *                          for which histogram results are stored is determined by the number of channels in the image.
 *                          If histogramInfo.histogramForAlpha is false and the source image is RGBA then only histogram
 *                          results for RGB channels are stored.
 *  @param  histogramOffset A byte offset into the histogram MTLBuffer where the histogram starts. Must conform to
 *                          alignment requirements for [MTLComputeCommandEncoder setBuffer:offset:atIndex:] offset
 *                          parameter.
 */
 -(void) encodeTransformToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                          sourceTexture: (nonnull id <MTLTexture>) source
                              histogram: (nonnull id <MTLBuffer>) histogram
                        histogramOffset: (NSUInteger) histogramOffset;



@end  /* MPSImageHistogramEqualization */

/*!
 *  @class      MPSImageHistogramSpecification
 *  @discussion The MPSImageHistogramSpecification performs a histogram specification operation on an image.
 *              It is a generalized version of histogram equalization operation.  The histogram specificaiton filter
 *              converts the image so that its histogram matches the desired histogram.
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(9.0), tvos(9.0))
@interface  MPSImageHistogramSpecification : MPSUnaryImageKernel

/*! @property   histogramInfo
 *  @abstract   Return a structure describing the histogram content
 *  @discussion Returns a MPSImageHistogramInfo structure describing the format of the
 *              histogram.
 */
@property (readonly, nonatomic)  MPSImageHistogramInfo histogramInfo;

/*!
 *  @abstract Specifies information about the histogram for the channels of an image.
 *  @discussion The MPSImageHistogramSpecification applies a transfor to convert the histogram 
 *              to a specified histogram. The process is divided into three steps:
 *
 *              -# Call -initWithDevice:histogramInfo:   This creates a MPSImageHistogramSpecification
 *              object.  It is done when the method returns.
 *
 *              -# Call -encodeTransform:sourceTexture:sourceHistogram:sourceHistogramOffset:desiredHistogram:
 *              desiredHistogramOffset: This creates a privately held image transform which will convert the
 *              the distribution of the source histogram to the desired histogram. This process runs on a 
 *              MTLCommandBuffer when it is committed to a MTLCommandQueue. It must complete before the next 
 *              step can be run. It may be performed on the same MTLCommandBuffer.  The sourceTexture argument 
 *              is used by encodeTransform to determine the number of channels and therefore which histogram data 
 *              in sourceHistogram buffer to use. The sourceHistogram and desiredHistogram must have been computed 
 *              either on the CPU or using the MPSImageHistogram kernel
 *
 *              -# Call -encodeToCommandBuffer:sourceTexture:destinationTexture: to read data from
 *              sourceTexture, apply the transform to it and write to destination texture.
 *              This step is also done on the GPU on a MTLCommandQueue.
 *
 *              You can reuse the same specification transform on other images to perform the
 *              same transform on those images. (Since their starting distribution is probably
 *              different, they will probably not arrive at the same distribution as the desired
 *              histogram.) This filter usually will not be able to work in place.
 *
 *  @param    device            The device the filter will run on
 *  @param    histogramInfo     Pointer to the MPSHistogramInfo struct
 *  @return     A valid MPSImageHistogramSpecification object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                         histogramInfo: (const MPSImageHistogramInfo * __nonnull) histogramInfo     NS_DESIGNATED_INITIALIZER;


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
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER
                            MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0));

/*!
 *  @abstract Encode the transform function to a command buffer using a MTLComputeCommandEncoder.
 *            The transform function computes the specification lookup table.
 *  @discussion The transform function will not begin to execute until after the command
 *              buffer has been enqueued and committed. This step will need to be repeated
 *              with the new MPSKernel if -copyWithZone:device or -copyWithZone: is called.
 *
 *  @param  commandBuffer   A valid MTLCommandBuffer.
 *  @param  source          A valid MTLTexture containing the source image for the filter.
 *  @param  sourceHistogram A valid MTLBuffer containing the histogram results for the source image.  This filter
 *                          will use these histogram results to generate the cumulative histogram for equalizing
 *                          the image.  The histogram results / channel are stored together.  The number of channels
 *                          for which histogram results are stored is determined by the number of channels in the image.
 *                          If histogramInfo.histogramForAlpha is false and the source image is RGBA then only histogram
 *                          results for RGB channels are stored.
 *  @param  sourceHistogramOffset   A byte offset into the sourceHistogram MTLBuffer where the histogram starts. Must conform to
 *                                  alignment requirements for [MTLComputeCommandEncoder setBuffer:offset:atIndex:] offset
 *                                  parameter.
 *  @param  desiredHistogram    A valid MTLBuffer containing the desired histogram results for the source image.
 *                          The histogram results / channel are stored together.  The number of channels
 *                          for which histogram results are stored is determined by the number of channels in the image.
 *                          If histogramInfo.histogramForAlpha is false and the source image is RGBA then only histogram
 *                          results for RGB channels are stored.
 *  @param  desiredHistogramOffset  A byte offset into the desiredHistogram MTLBuffer where the histogram starts. Must conform to
 *                                  alignment requirements for [MTLComputeCommandEncoder setBuffer:offset:atIndex:] offset
 *                                  parameter.
 */
-(void) encodeTransformToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                         sourceTexture: (nonnull id <MTLTexture>) source
                       sourceHistogram: (nonnull id <MTLBuffer>) sourceHistogram
                 sourceHistogramOffset: (NSUInteger) sourceHistogramOffset
                      desiredHistogram: (nonnull id <MTLBuffer>) desiredHistogram
                desiredHistogramOffset: (NSUInteger) desiredHistogramOffset;



@end  /* MPSImageHistogramSpecification */

#endif  /* MPS_MSImageHistogram_h */

