/*!
 *  @header MPSSVGF.h
 *  @framework MPSRayIntersector
 *  @description  MPS noise reduction filter interface.
 *
 *  @copyright Copyright (c) 2018 Apple Inc. All rights reserved.
 */

#ifndef MPSSVGF_h
#define MPSSVGF_h

#import <MPSCore/MPSCoreTypes.h>
#import <MPSCore/MPSKernel.h>

/**
 * @brief Controls how samples are weighted over time
 */
typedef NS_ENUM(NSUInteger, MPSTemporalWeighting) {
    /**
     * @brief Compute an average of all samples. This will fully utilize all samples but may lead
     * to excessive ghosting artifacts under motion. Therefore, this is best for static images.
     */
    MPSTemporalWeightingAverage = 0,

    /**
     * @brief Compute an exponential moving average by blending linearly between the previous
     * accumulated samples and the current sample according to the temporalReprojectionBlendFactor
     * property. This will cause older samples to lose their contribution over time, which will
     * prevent ghosting artifacts but will also never converge to a stable value. Therefore, this
     * is best for images with motion.
     */
    MPSTemporalWeightingExponentialMovingAverage = 1,
} MPS_ENUM_AVAILABLE_STARTING(macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0));

/**
 * @brief Reduces noise in images rendered with Monte Carlo ray tracing methods
 *
 * @discussion This filter uses temporal reprojection to accumulate samples over time, followed by
 * an edge-avoiding blur to smooth out the noise. It uses depth and surface normal textures to
 * detect edges in the image(s) to be denoised. The filter also computes an estimate of the
 * luminance variance of the accumulated samples for each pixel to reject neighboring pixels whose
 * luminance is too dissimilar while blurring.
 *
 * This filter requires noise-free depth and normal textures, so it is not compatible with
 * stochastic visibility effects such as depth of field, motion blur, or pixel subsampling. These
 * effects need to be applied as a post-process instead. Furthermore, because the depth and normal
 * textures can only represent directly visible geometry, the filter may over-blur reflections.
 * The use of temporal reprojection may introduce artifacts such as ghosting or streaking, as well
 * as a temporal lag for changes in luminance such as moving shadows. However, the filter is
 * relatively fast as it is intended for realtime use. Slower but higher quality filters are
 * available in the literature.
 * 
 * This filter can process up to two images simultaneously assuming they share the same depth and
 * normal textures. This is typically faster than processing the two images independently because
 * memory bandwidth spent fetching depth and normal values and ALU time spent computing various
 * weighting functions can be shared by both images. This is useful if e.g. you want to denoise
 * direct and indirect lighting terms separately to avoid mixing the two terms. The filter is also
 * optimized for processing single-channel images for effects such as shadows and ambient
 * occlusion. Denoising these images can be much faster than denoising a full RGB image, so it may
 * be useful to separate out these terms and denoise them specifically.
 *
 * This filter operates in three stages: temporal reprojection, variance estimation, and finally a
 * series of edge-avoiding bilateral blurs. The temporal reprojection stage accepts the image to
 * be denoised for the current frame and the denoised image from the previous frame, the depth and
 * normal textures from the current and previous frame and, finally, a motion vector texture. It
 * uses the motion vector texture to look up the accumulated samples from the previous frame. It
 * then compares the depth and normals to determine if those samples are consistent with the
 * current frame. If so, the previous frame is blended with the current frame. This stage also
 * accumulates the first and second moments of the sample luminance which is used to compute the
 * luminance variance in the next stage.
 *
 * The variance estimation stage computes an estimate of the variance of the luminance of the
 * accumulated samples for each pixel. This stage may fall back to a spatial estimate if not enough
 * samples have been accumulated. The luminance variance is used in the final stage to reject
 * outlying neighboring pixels while blurring to avoid blurring across luminance discontinuities
 * such as shadow boundaries.
 *
 * The final stage performs consecutive edge-avoiding bilateral blurs to smooth out noise in the
 * image. The blurs are dilated with increasing power of two step distances starting from 1,
 * which cheaply approximates a very large radius bilateral blur. Each iteration blurs both the
 * input image and the variance image as variance is reduced after each iteration. It is
 * recommended that the output of the first iteration be used as the input to the next frame's
 * reprojection stage to further reduce noise.
 *
 * Tips:
 *
 * - It may be helpful to further divide out texture details such as surface albedo before
 *   denoising to avoid blurring texture detail and to preserve any careful texture filtering that
 *   may have been performed. The albedo can be reapplied after denoising.
 * - High frequency geometry and normal maps may cause excessive disocclusions during reprojection
 *   manifesting as noise.
 * - Jittering sample positions from frame to frame for temporal antialiasing may also cause
 *   disocclusions. However, this can be partially hidden by the temporal antialiasing algorithm
 *   itself.
 * - This kernel, like many convolutions, requires quite a bit of bandwidth. Use the texture pixel
 *   formats with the smallest number of bits-per-pixel and the lowest resolution possible for the
 *   required quality level. Lower resolution images can be combined with a bilateral upsampling
 *   filter, especially if the image being denoised is mostly low frequency lighting or ambient
 *   occlusion.
 * - The increasing dilation during the bilateral blurring stage can introduce ringing artifacts
 *   around geometric discontinuities. These can be partially hidden at the cost of potentially
 *   increased noise by reducing the bilateral blur's sigma value slightly after each iteration.
 * - Use lower precision pixel formats if possible to reduce memory bandwidth.
 *
 * Refer to "Spatiotemporal Variance-Guided Filtering: Real-Time Reconstruction for Path-Traced
 * Global Illumination" for more information.
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0))
@interface MPSSVGF : MPSKernel <NSSecureCoding, NSCopying>

/**
 * @brief Controls how samples' depths are compared during reprojection, variance estimation, and
 * bilateral filtering. The final weight is given by exp(-abs(Z1 - Z2) / depthWeight). Must be
 * greater than zero. Defaults to 1.0.
 */
@property (nonatomic) float depthWeight;

/**
 * @brief Controls how samples' normals are compared during reprojection, variance estimation, and
 * bilateral filtering. The final weight is given by pow(max(dot(N1, N2)), normalWeight). Must be
 * greater than or equal to zero. Defaults to 128.
 */
@property (nonatomic) float normalWeight;

/**
 * @brief Controls how samples' luminance values are compared during bilateral filtering. The final
 * weight is given by exp(-abs(L1 - L2) / (luminanceWeight * luminanceVariance + EPSILON)). Must be
 * greater than or equal to zero. Defaults to 4.
 */
@property (nonatomic) float luminanceWeight;

/**
 * @brief How to weight samples during temporal reprojection. Defaults to
 * MPSTemporalWeightingAverage.
 */
@property (nonatomic) MPSTemporalWeighting temporalWeighting;

/**
 * @brief When using MPSTemporalWeightingExponentialMovingAverage, how much to blend
 * the current frame with the previous frame during reprojection. The final value is given by
 * current * temporalReprojectionBlendFactor + previous * (1 - temporalReprojectionBlendFactor).
 * Must be between zero and one, inclusive. Defaults to 0.2.
 */
@property (nonatomic) float temporalReprojectionBlendFactor;

/**
 * @brief During reprojection, minimum combined depth and normal weight needed to consider a pixel
 * from the previous frame consistent with a pixel from the current frame. Must be greater than or
 * equal to zero. Defaults to 0.01.
 */
@property (nonatomic) float reprojectionThreshold;

/**
 * @brief The minimum number of frames which must be accumulated before variance can be computed
 * directly from the accumulated luminance moments. If enough frames have not been accumulated,
 * variance will be estimated with a spatial filter instead. Defaults to 4.
 */
@property (nonatomic) NSUInteger minimumFramesForVarianceEstimation;

/**
 * @brief The radius of the spatial filter used when not enough frames have been accumulated to
 * compute variance from accumulated luminance moments. Defaults to 3 resulting in a 7x7 filter.
 */
@property (nonatomic) NSUInteger varianceEstimationRadius;

/**
 * @brief The sigma value of the Gaussian function used by the spatial filter used when not enough
 * frames have been accumulated to compute variance from accumulated luminance moments. Must be
 * greater than zero. Defaults to 2.0.
 */
@property (nonatomic) float varianceEstimationSigma;

/**
 * @brief The sigma value of the Gaussian function used by the variance pre-filter of the
 * bilateral filter. Must be greater than zero. Defaults to 1.33.
 */
@property (nonatomic) float variancePrefilterSigma;

/**
 * @brief The radius of the variance pre-filter of the bilateral filter. Defaults to 1 resulting in
 * a 3x3 filter.
 */
@property (nonatomic) NSUInteger variancePrefilterRadius;

/**
 * @brief The sigma value of the Gaussian function used by the bilateral filter. Must be greater
 * than zero. Defaults to 1.2.
 */
@property (nonatomic) float bilateralFilterSigma;

/**
 * @brief The radius of the bilateral filter. Defaults to 2 resulting in a 5x5 filter.
 */
@property (nonatomic) NSUInteger bilateralFilterRadius;

/**
 * @brief The number of channels to filter in the source image. Must be at least one and at most
 * three. Defaults to 3.
 */
@property (nonatomic) NSUInteger channelCount;

/**
 * @brief The number of channels to filter in the second source image. Must be at least one and at
 * most three. Defaults to 3.
 */
@property (nonatomic) NSUInteger channelCount2;

- (nonnull instancetype)initWithDevice:(nonnull id <MTLDevice>)device NS_DESIGNATED_INITIALIZER;

- (nullable instancetype)initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>)device NS_DESIGNATED_INITIALIZER;

- (nonnull instancetype)copyWithZone:(nullable NSZone *)zone
                              device:(nullable id <MTLDevice>)device;

- (void)encodeWithCoder:(NSCoder * __nonnull)coder;

/**
 * @brief Encode reprojection into a command buffer
 *
 * @discussion Normal and depth values from the previous frame will be compared with normal and
 * depth values from the current frame to determine if they are similar enough to reproject into
 * the current frame. These values are weighted by the depthWeight and normalWeight properties.
 * If the combined weight exceeds the reprojectionThreshold property's value, the previous frame
 * will be blended with the current frame according to the temporalWeighting and
 * temporalReprojectionBlendFactor properties.
 *
 * The reprojection kernel can operate on two sets of source and destination textures
 * simultaneously to share costs such as loading depth and normal values from memory, computing
 * various weights, etc. The second set of textures may be nil. The two images are assumed to share
 * the same depth and normal values.
 *
 * The number of channels in the source image(s), previous frame's image(s), and destination
 * image(s) are given by the channelCount and channelCount2 properties. These images must have at
 * least as many channels as given by these properties. Channels beyond the required number are
 * ignored when reading from source images and set to zero when writing to the destination images,
 * except the alpha channel which will be set to one if present. The previous frame's image will
 * be ignored on the first frame.
 *
 * The source and destination luminance moments textures must be at least two-channel textures,
 * which will be set to the accumulated first and second moments of luminance. Channels beyond the
 * first two will be ignored when reading from the previous frame's texture and set to zero when
 * writing to the destination texture. The previous frame's luminance moments will be ignored on
 * the first frame.
 *
 * The frame count textures track the number of accumulated frames and must be at least R32Uint
 * textures. The remaining channels will be ignored when reading from the source texture and set to
 * zero when writing to the destination texture, if present. The previous frame count texture must
 * be cleared to zero on the first frame or to reset the accumulated images to the current frame's
 * image.
 *
 * The motion vector texture must be at least a two channel texture representing how many texels
 * each texel in the source image(s) have moved since the previous frame. The remaining channels
 * will be ignored if present. This texture may be nil, in which case the motion vector is assumed
 * to be zero, which is suitable for static images.
 *
 * The depth/normal texture must contain the depth and normal values for directly visible geometry
 * for the current frame for each pixel. These values are packed into a four channel texture to
 * reduce the number of texture sampling instructions required to load them. The first channel must
 * store the depth value from zero to infinity. The normals must be stored in the last three
 * channels as the three signed X, Y, and z components each between negative one and one. 
 * The depth and normal values are not required if the motion vector texture is nil.
 *
 * The destination texture, destination luminance moments texture, and destination frame count
 * texture are used by subsequent stages of the denoising filter. The destination frame count
 * texture is also used as the source frame count texture the reprojection kernel in the next
 * frame.
 *
 * @param commandBuffer                       Command buffer to encode into
 * @param sourceTexture                       Current frame to denoise
 * @param previousTexture                     Previous denoised frame to reproject into current
 *                                            frame
 * @param destinationTexture                  Output blended image
 * @param previousLuminanceMomentsTexture     Previous accumulated luminance moments image
 * @param destinationLuminanceMomentsTexture  Output accumulated luminance moments image
 * @param previousFrameCountTexture           The number of frames accumulated in the previous
 *                                            source image
 * @param destinationFrameCountTexture        The number of frames accumulated in the destination
 *                                            texture(s) including the current frame
 * @param motionVectorTexture                 Motion vector texture
 * @param depthNormalTexture                  The depth and normal values for the current frame
 * @param previousDepthNormalTexture          The depth and normal values for the previous frame
 */
- (void)encodeReprojectionToCommandBuffer:(nonnull id <MTLCommandBuffer>)commandBuffer
                            sourceTexture:(nonnull id <MTLTexture>)sourceTexture
                          previousTexture:(nonnull id <MTLTexture>)previousTexture
                       destinationTexture:(nonnull id <MTLTexture>)destinationTexture
          previousLuminanceMomentsTexture:(nonnull id <MTLTexture>)previousLuminanceMomentsTexture
       destinationLuminanceMomentsTexture:(nonnull id <MTLTexture>)destinationLuminanceMomentsTexture
                previousFrameCountTexture:(nonnull id <MTLTexture>)previousFrameCountTexture
             destinationFrameCountTexture:(nonnull id <MTLTexture>)destinationFrameCountTexture
                      motionVectorTexture:(nullable id <MTLTexture>)motionVectorTexture
                       depthNormalTexture:(nullable id <MTLTexture>)depthNormalTexture
               previousDepthNormalTexture:(nullable id <MTLTexture>)previousDepthNormalTexture;

/**
 * @brief Encode reprojection into a command buffer
 *
 * @discussion Normal and depth values from the previous frame will be compared with normal and
 * depth values from the current frame to determine if they are similar enough to reproject into
 * the current frame. These values are weighted by the depthWeight and normalWeight properties.
 * If the combined weight exceeds the reprojectionThreshold property's value, the previous frame
 * will be blended with the current frame according to the temporalWeighting and
 * temporalReprojectionBlendFactor properties.
 *
 * The reprojection kernel can operate on two sets of source and destination textures
 * simultaneously to share costs such as loading depth and normal values from memory, computing
 * various weights, etc. The second set of textures may be nil. The two images are assumed to share
 * the same depth and normal values.
 *
 * The number of channels in the source image(s), previous frame's image(s), and destination
 * image(s) are given by the channelCount and channelCount2 properties. These images must have at
 * least as many channels as given by these properties. Channels beyond the required number are
 * ignored when reading from source images and set to zero when writing to the destination images,
 * except the alpha channel which will be set to one if present. The previous frame's image will
 * be ignored on the first frame.
 *
 * The source and destination luminance moments textures must be at least two-channel textures,
 * which will be set to the accumulated first and second moments of luminance. Channels beyond the
 * first two will be ignored when reading from the previous frame's texture and set to zero when
 * writing to the destination texture. The previous frame's luminance moments will be ignored on
 * the first frame.
 *
 * The frame count textures track the number of accumulated frames and must be at least R32Uint
 * textures. The remaining channels will be ignored when reading from the source texture and set to
 * zero when writing to the destination texture, if present. The previous frame count texture must
 * be cleared to zero on the first frame or to reset the accumulated images to the current frame's
 * image.
 *
 * The motion vector texture must be at least a two channel texture representing how many texels
 * each texel in the source image(s) have moved since the previous frame. The remaining channels
 * will be ignored if present. This texture may be nil, in which case the motion vector is assumed
 * to be zero, which is suitable for static images.
 *
 * The depth/normal texture must contain the depth and normal values for directly visible geometry
 * for the current frame for each pixel. These values are packed into a four channel texture to
 * reduce the number of texture sampling instructions required to load them. The first channel must
 * store the depth value from zero to infinity. The normals must be stored in the last three
 * channels as the three signed X, Y, and z components each between negative one and one. 
 * The depth and normal values are not required if the motion vector texture is nil.
 *
 * The destination texture, destination luminance moments texture, and destination frame count
 * texture are used by subsequent stages of the denoising filter. The destination frame count
 * texture is also used as the source frame count texture the reprojection kernel in the next
 * frame.
 *
 * @param commandBuffer                       Command buffer to encode into
 * @param sourceTexture                       Current frame to denoise
 * @param previousTexture                     Previous denoised frame to reproject into current
 *                                            frame
 * @param destinationTexture                  Output blended image
 * @param previousLuminanceMomentsTexture     Previous accumulated luminance moments image
 * @param destinationLuminanceMomentsTexture  Output accumulated luminance moments image
 * @param sourceTexture2                      Second source image
 * @param previousTexture2                    Second previous image
 * @param destinationTexture2                 Second destination image
 * @param previousLuminanceMomentsTexture2    Second previous luminance moments texture
 * @param destinationLuminanceMomentsTexture2 Second destination luminance moments texture
 * @param previousFrameCountTexture           The number of frames accumulated in the previous
 *                                            source image
 * @param destinationFrameCountTexture        The number of frames accumulated in the destination
 *                                            texture(s) including the current frame
 * @param motionVectorTexture                 Motion vector texture
 * @param depthNormalTexture                  The depth and normal values for the current frame
 * @param previousDepthNormalTexture          The depth and normal values for the previous frame
 */
- (void)encodeReprojectionToCommandBuffer:(nonnull id <MTLCommandBuffer>)commandBuffer
                            sourceTexture:(nonnull id <MTLTexture>)sourceTexture
                          previousTexture:(nonnull id <MTLTexture>)previousTexture
                       destinationTexture:(nonnull id <MTLTexture>)destinationTexture
          previousLuminanceMomentsTexture:(nonnull id <MTLTexture>)previousLuminanceMomentsTexture
       destinationLuminanceMomentsTexture:(nonnull id <MTLTexture>)destinationLuminanceMomentsTexture
                           sourceTexture2:(nullable id <MTLTexture>)sourceTexture2
                         previousTexture2:(nullable id <MTLTexture>)previousTexture2
                      destinationTexture2:(nullable id <MTLTexture>)destinationTexture2
         previousLuminanceMomentsTexture2:(nullable id <MTLTexture>)previousLuminanceMomentsTexture2
      destinationLuminanceMomentsTexture2:(nullable id <MTLTexture>)destinationLuminanceMomentsTexture2
                previousFrameCountTexture:(nonnull id <MTLTexture>)previousFrameCountTexture
             destinationFrameCountTexture:(nonnull id <MTLTexture>)destinationFrameCountTexture
                      motionVectorTexture:(nullable id <MTLTexture>)motionVectorTexture
                       depthNormalTexture:(nullable id <MTLTexture>)depthNormalTexture
               previousDepthNormalTexture:(nullable id <MTLTexture>)previousDepthNormalTexture;

/**
 * @brief Encode variance estimation into a command buffer
 *
 * @discussion Variance is computed from the accumulated first and second luminance moments. If the
 * number of accumulated frames is below the minimumFramesForVarianceEstimation property, the
 * luminance variance will be computed using a spatial estimate instead. The spatial estimate is
 * computed using a bilateral filter with radius given by the varianceEstimationRadius property.
 * Neighboring samples will be weighted according to a gaussian function with sigma given by the
 * varianceEstimationSigma property. Normal and depth values from neighboring pixels will be
 * compared with depth and normal values of the center pixel to determine if they are similar
 * enough to include in the spatial blur. These values are weighted by the depthWeight and
 * normalWeight properties.
 *
 * The variance kernel can operate on two sets of source and destination textures
 * simultaneously to share costs such as loading depth and normal values from memory, computing
 * various weights, etc. The second set of textures may be nil. The two images are assumed to share
 * the same depth and normal values.
 *
 * The reprojected source texture, luminance moments texture and frame count texture are computed
 * by the reprojection kernel.
 *
 * The computed variance will be stored in the last channel of the destination image, while the
 * source image will be copied into the previous channels, to reduce the number of texture sample
 * instructured required by the bilateral filter in the final stage of the denoising kernel. The
 * number of channels in the source image(s) are given by the channelCount and channelCount2
 * properties. Therefore, the destination image(s) must have at least channelCount + 1 and
 * channelCount2 + 1 channels and the source image(s) must have at least channelCount and
 * channelCount2 channels. Channels beyond the required number are ignored when reading from
 * source textures and set to zero when writing to destination textures.
 *
 * The depth/normal texture must contain the depth and normal values for directly visible geometry
 * for the current frame for each pixel. These values are packed into a four channel texture to
 * reduce the number of texture sampling instructions required to load them. The first channel must
 * store the depth value from zero to infinity. The normals must be stored in the last three
 * channels as the three signed X, Y, and z components each between negative one and one.
 * If the minimumFramesForVarianceEstimation property is less than or equal to one, variance will
 * be estimated directly from the accumulated luminance moments so the depth/normal texture may be
 * nil.
 *
 * @param commandBuffer            Command buffer to encode into
 * @param sourceTexture            Current reprojected frame to denoise
 * @param luminanceMomentsTexture  Luminance moments texture
 * @param destinationTexture       Output packed color and variance image
 * @param frameCountTexture        Number of frames accumulated into the source image
 * @param depthNormalTexture       The depth and normal values for the current frame
 */
- (void)encodeVarianceEstimationToCommandBuffer:(nonnull id <MTLCommandBuffer>)commandBuffer
                                  sourceTexture:(nonnull id <MTLTexture>)sourceTexture
                        luminanceMomentsTexture:(nonnull id <MTLTexture>)luminanceMomentsTexture
                             destinationTexture:(nonnull id <MTLTexture>)destinationTexture
                              frameCountTexture:(nonnull id <MTLTexture>)frameCountTexture
                             depthNormalTexture:(nullable id <MTLTexture>)depthNormalTexture;

/**
 * @brief Encode variance estimation into a command buffer
 *
 * @discussion Variance is computed from the accumulated first and second luminance moments. If the
 * number of accumulated frames is below the minimumFramesForVarianceEstimation property, the
 * luminance variance will be computed using a spatial estimate instead. The spatial estimate is
 * computed using a bilateral filter with radius given by the varianceEstimationRadius property.
 * Neighboring samples will be weighted according to a gaussian function with sigma given by the
 * varianceEstimationSigma property. Normal and depth values from neighboring pixels will be
 * compared with depth and normal values of the center pixel to determine if they are similar
 * enough to include in the spatial blur. These values are weighted by the depthWeight and
 * normalWeight properties.
 *
 * The variance kernel can operate on two sets of source and destination textures
 * simultaneously to share costs such as loading depth and normal values from memory, computing
 * various weights, etc. The second set of textures may be nil. The two images are assumed to share
 * the same depth and normal values.
 *
 * The reprojected source texture, luminance moments texture and frame count texture are computed
 * by the reprojection kernel.
 *
 * The computed variance will be stored in the last channel of the destination image, while the
 * source image will be copied into the previous channels, to reduce the number of texture sample
 * instructured required by the bilateral filter in the final stage of the denoising kernel. The
 * number of channels in the source image(s) are given by the channelCount and channelCount2
 * properties. Therefore, the destination image(s) must have at least channelCount + 1 and
 * channelCount2 + 1 channels and the source image(s) must have at least channelCount and
 * channelCount2 channels. Channels beyond the required number are ignored when reading from
 * source textures and set to zero when writing to destination textures.
 *
 * The depth/normal texture must contain the depth and normal values for directly visible geometry
 * for the current frame for each pixel. These values are packed into a four channel texture to
 * reduce the number of texture sampling instructions required to load them. The first channel must
 * store the depth value from zero to infinity. The normals must be stored in the last three
 * channels as the three signed X, Y, and z components each between negative one and one.
 * If the minimumFramesForVarianceEstimation property is less than or equal to one, variance will
 * be estimated directly from the accumulated luminance moments so the depth/normal texture may be
 * nil.
 *
 * @param commandBuffer            Command buffer to encode into
 * @param sourceTexture            Current reprojected frame to denoise
 * @param luminanceMomentsTexture  Luminance moments texture
 * @param destinationTexture       Output packed color and variance image
 * @param sourceTexture2           Second source image
 * @param luminanceMomentsTexture2 Second luminance moments image
 * @param destinationTexture2      Second destination image
 * @param frameCountTexture        Number of frames accumulated into the source image
 * @param depthNormalTexture       The depth and normal values for the current frame
 */
- (void)encodeVarianceEstimationToCommandBuffer:(nonnull id <MTLCommandBuffer>)commandBuffer
                                  sourceTexture:(nonnull id <MTLTexture>)sourceTexture
                        luminanceMomentsTexture:(nonnull id <MTLTexture>)luminanceMomentsTexture
                             destinationTexture:(nonnull id <MTLTexture>)destinationTexture
                                 sourceTexture2:(nullable id <MTLTexture>)sourceTexture2
                       luminanceMomentsTexture2:(nullable id <MTLTexture>)luminanceMomentsTexture2
                            destinationTexture2:(nullable id <MTLTexture>)destinationTexture2
                              frameCountTexture:(nonnull id <MTLTexture>)frameCountTexture
                             depthNormalTexture:(nullable id <MTLTexture>)depthNormalTexture;

/**
 * @brief Encode bilateral filter into a command buffer
 *
 * @discussion Performs an edge avoiding blur with radius given by the bilateraFilterRadius
 * property with sampling weighted by a Gaussian filter with sigma given by the bilteralFilterSigma
 * property. Normal and depth values from neighboring pixels will be compared with depth and normal
 * values of the center pixel to determine if they are similar enough to include in the blur. These
 * values are weighted by the depthWeight, normalWeight, and luminanceWeight properties.
 *
 * Before the variance values are used for luminance weighting, the variance is prefiltered with a
 * small Gaussian blur with radius given by the variancePrefilterRadius property and sigma given by
 * the variancePrefilterSigma property.
 *
 * This kernel should be run multiple times with a step distance of pow(2, i), starting with i = 0.
 * It is recommended that the output of the first iteration be used as the image to be reprojected
 * in the next frame. Then several more iterations should be run to compute the denoised image for
 * the current frame. 5 total iterations is reasonable.
 *
 * The bilateral filter can operate on two sets of source and destination textures simultaneously
 * to share costs such as loading depth and normal values from memory, computing various weights,
 * etc. The second set of textures may be nil. The two images are assumed to share the same normal
 * and depth values.
 *
 * The number of channels to filter in the source image(s) are given by the channelCount and
 * channelCount2 properties. Furthermore, the luminance variance is packed into the final channel
 * of the source image(s) to reduce the number of texture sample instructions required. The
 * filtered color and variance values are packed the same way in the destination image(s).
 * Therefore, the source and destination images must have at least channelCount + 1 and
 * channelCount2 + 1 channels. Channels beyond the required number are ignored when reading from
 * source images and set to zero when writing to destination images. The source image should be
 * produced by either the variance estimation kernel or a previous iteration of the bilateral
 * filter.
 *
 * The depth/normal texture must contain the depth and normal values for directly visible geometry
 * for the current frame for each pixel. These values are packed into a four channel texture to
 * reduce the number of texture sampling instructions required to load them. The first channel must
 * store the depth value from zero to infinity. The normals must be stored in the last three
 * channels as the three signed X, Y, and z components each between negative one and one. 
 *
 * @param commandBuffer       Command buffer to encode into
 * @param stepDistance        Number of pixels to skip between samples
 * @param sourceTexture       Source packed color and variance texture
 * @param destinationTexture  Destination packed color and variance texture
 * @param depthNormalTexture  The depth and normal values for the current frame
 */
- (void)encodeBilateralFilterToCommandBuffer:(nonnull id <MTLCommandBuffer>)commandBuffer
                                stepDistance:(NSUInteger)stepDistance
                               sourceTexture:(nonnull id <MTLTexture>)sourceTexture
                          destinationTexture:(nonnull id <MTLTexture>)destinationTexture
                          depthNormalTexture:(nonnull id <MTLTexture>)depthNormalTexture;

/**
 * @brief Encode bilateral filter into a command buffer
 *
 * @discussion Performs an edge avoiding blur with radius given by the bilateraFilterRadius
 * property with sampling weighted by a Gaussian filter with sigma given by the bilteralFilterSigma
 * property. Normal and depth values from neighboring pixels will be compared with depth and normal
 * values of the center pixel to determine if they are similar enough to include in the blur. These
 * values are weighted by the depthWeight, normalWeight, and luminanceWeight properties.
 *
 * Before the variance values are used for luminance weighting, the variance is prefiltered with a
 * small Gaussian blur with radius given by the variancePrefilterRadius property and sigma given by
 * the variancePrefilterSigma property.
 *
 * This kernel should be run multiple times with a step distance of pow(2, i), starting with i = 0.
 * It is recommended that the output of the first iteration be used as the image to be reprojected
 * in the next frame. Then several more iterations should be run to compute the denoised image for
 * the current frame. 5 total iterations is reasonable.
 *
 * The bilateral filter can operate on two sets of source and destination textures simultaneously
 * to share costs such as loading depth and normal values from memory, computing various weights,
 * etc. The second set of textures may be nil. The two images are assumed to share the same normal
 * and depth values.
 *
 * The number of channels to filter in the source image(s) are given by the channelCount and
 * channelCount2 properties. Furthermore, the luminance variance is packed into the final channel
 * of the source image(s) to reduce the number of texture sample instructions required. The
 * filtered color and variance values are packed the same way in the destination image(s).
 * Therefore, the source and destination images must have at least channelCount + 1 and
 * channelCount2 + 1 channels. Channels beyond the required number are ignored when reading from
 * source images and set to zero when writing to destination images. The source image should be
 * produced by either the variance estimation kernel or a previous iteration of the bilateral
 * filter.
 *
 * The depth/normal texture must contain the depth and normal values for directly visible geometry
 * for the current frame for each pixel. These values are packed into a four channel texture to
 * reduce the number of texture sampling instructions required to load them. The first channel must
 * store the depth value from zero to infinity. The normals must be stored in the last three
 * channels as the three signed X, Y, and z components each between negative one and one. 
 *
 * @param commandBuffer       Command buffer to encode into
 * @param stepDistance        Number of pixels to skip between samples
 * @param sourceTexture       Source packed color and variance texture
 * @param destinationTexture  Destination packed color and variance texture
 * @param sourceTexture2      Second source image
 * @param destinationTexture2 Second destination image
 * @param depthNormalTexture  The depth and normal values for the current frame
 */
- (void)encodeBilateralFilterToCommandBuffer:(nonnull id <MTLCommandBuffer>)commandBuffer
                                stepDistance:(NSUInteger)stepDistance
                               sourceTexture:(nonnull id <MTLTexture>)sourceTexture
                          destinationTexture:(nonnull id <MTLTexture>)destinationTexture
                              sourceTexture2:(nullable id <MTLTexture>)sourceTexture2
                         destinationTexture2:(nullable id <MTLTexture>)destinationTexture2
                          depthNormalTexture:(nonnull id <MTLTexture>)depthNormalTexture;

@end

/**
 * @brief Protocol dictating how texture allocator objects should operate so that they can be used
 * by an MPSSVGFDenoiser object to allocate and reuse intermediate and output textures during the
 * denoising process.
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0))
@protocol MPSSVGFTextureAllocator <NSObject>

/**
 * @brief Returns an autoreleased Metal 2D texture with a matching pixel format, width, and height.
 */
- (nullable id <MTLTexture>)textureWithPixelFormat:(MTLPixelFormat)pixelFormat
                                             width:(NSUInteger)width
                                            height:(NSUInteger)height;

/**
 * @brief Return a texture to the allocator. The allocator operate in such a way as to reduce the
 * allocation cost should another texture be requested with the same width, height, and pixel
 * format.
 */
- (void)returnTexture:(nonnull id <MTLTexture>)texture;

@end

/**
 * @brief A default implementation of the MPSSVGFTextureAllocator protocol. Maintains a cache of
 * textures which is checked first when a texture is requested. If there is no suitable texture in
 * the cache, allocates a texture directly from the Metal device.
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0))
@interface MPSSVGFDefaultTextureAllocator : NSObject <MPSSVGFTextureAllocator>

/**
 * @brief Metal device this object was allocated from
 */
@property (nonatomic, readonly) id <MTLDevice> _Nonnull device;

/**
 * @brief The number of textures which have been allocated from this allocator
 */
@property (nonatomic, readonly) NSUInteger allocatedTextureCount;

/**
 * @brief Initialize the MPSSVGFDefaultTextureAllocator with a Metal device
 */
- (nonnull instancetype)initWithDevice:(nonnull id <MTLDevice>)device;

- (nullable id <MTLTexture>)textureWithPixelFormat:(MTLPixelFormat)pixelFormat
                                             width:(NSUInteger)width
                                            height:(NSUInteger)height;

- (void)returnTexture:(nonnull id <MTLTexture>)texture;

/**
 * @brief Remove all textures from the cache
 */
- (void)reset;

@end

/**
 * @brief A convenience object which uses an MPSSVGF object to manage the denoising process
 *
 * @discussion The MPSSVGF object can also be used directly to customize the denoising process.
 * This object keeps track of auxilary textures used by the MPSSVGF object, manages a temporal
 * history, and encodes the entire denoising process into a command buffer.
 *
 * To use this class, first create and customize an MPSSVGF object. This object allows you to tweak
 * various aspect of the denoising process such as temporal reprojection and bilateral blur settings.
 * Then create a texture allocator object which will allocate temporary textures during denoising.
 * This can either be an object conforming to the MPSSVGFTextureAllocator protocol or an instance of
 * the MPSSVGFDefaultTextureAllocator class. Next, create an MPSSVGFDenoiser object. To perform
 * denoising, assign inputs textures to the denoiser object's properties and call
 * encodeToCommandBuffer:. Finally, read the output from the destinationTexture property. Note that
 * this class can denoise up to two independent textures simultaneously, e.g. specular and diffuse,
 * direct and indirect lighting, shadows and AO, etc.
 *
 *     @code
 *     MPSSVGF *svgf = [[MPSSVGF alloc] initWithDevice:device];
 *
 *     // configure svgf properties
 *
 *     MPSSVGFDefaultTextureAllocator *allocator =
 *         [[MPSSVGFDefaultTextureAllocator alloc] initWithDevice:device];
 *
 *     MPSSVGFDenoiser *denoiser = [[MPSSVGFDenoiser alloc] initWithSVGF:svgf
 *                                                      textureAllocator:allocator];
 *
 *     // configure denoiser properties
 *
 *     denoiser.sourceTexture = noisyTexture;
 *     denoiser.depthNormalTexture = depthNormalTexture;
 *     denoiser.previousDepthNormalTexture = depthNormalTextureFromPreviousFrame;
 *     denoiser.motionVectorTexture = motionVectorTexture;
 *
 *     [denoiser encodeToCommandBuffer:commandBuffer];
 *
 *     id <MTLTexture> cleanTexture = denoiser.destinationTexture;
 *     @endcode
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0))
@interface MPSSVGFDenoiser : NSObject

/**
 * @brief The underlying MPSSVGF kernels object which will be used for denoising. Use this object
 * to customize the denoising process.
 */
@property (nonatomic, readonly) MPSSVGF * _Nonnull svgf;

/**
 * @brief The object which will be used to allocate intermediate and output textures.
 */
@property (nonatomic, readonly) id <MPSSVGFTextureAllocator> _Nonnull textureAllocator;

/**
 * @brief The number of bilateral filter iterations to run. More iterations will improve quality at
 * the cost of performance. Defaults to 5. Must be at least 1.
 */
@property (nonatomic) NSUInteger bilateralFilterIterations;

/**
 * @brief Initialize the MPSSVGFDenoiser object
 *
 * @parameter device The Metal device to use for denoising
 */
- (nonnull instancetype)initWithDevice:(nonnull id <MTLDevice>)device
    MPS_SWIFT_NAME(init(device:));

/**
 * @brief Initialize the MPSSVGFDenoiser object
 *
 * @parameter svgf             MPSSVGF kernels to use for denoising. This object can be used to
 *                             configure temporal reprojection, bilateral blur settings, etc.
 * @parameter textureAllocator An object conforming to the MPSSVGFTextureAllocator protocol. This
 *                             object will be used to allocate temporary intermediate and output
 *                             textures. This can be a custom object or an instance of the
 *                             MPSSVGFDefaultTextureAllocator class.
 */
- (nonnull instancetype)initWithSVGF:(nonnull MPSSVGF *)svgf
                    textureAllocator:(nonnull id <MPSSVGFTextureAllocator>)textureAllocator
    MPS_SWIFT_NAME(init(SVGF:textureAllocator:));

/**
 * @brief Clear the temporal history. Reprojection and temporal accumulation will restart on the
 * next call to encodeToCommandBuffer:
 */
- (void)clearTemporalHistory;

/**
 * @brief Return any temporary textures to the texture allocator. Also clears the temporal history.
 * This should be called before resizing the source texture(s).
 */
- (void)releaseTemporaryTextures;

/**
 * @brief Encode denoising kernels to a command buffer
 *
 * @discussion Removes noise from the source texture, using the additional data in the motion vector,
 * depth/normal, and previous depth/normal textures. Returns the resulting texture. The depth/normal
 * texture should be provided as the previous depth/normal texture for the next call to this method.
 * This method will also update an internally managed temporal history to aid the denoising process.
 * To reset this history, call the clearTemporalHistory method. This method will allocate and return
 * several textures from and to the texture allocator the MPSSVGFDenoiser was initialized with. The
 * number of iterations of the bilateral filter is controlled by the bilateralFilterIterations property.
 * Larger numbers of iterations will improve the quality but reduce performance. To configure other
 * parameters of the denoising process, modify the properties of the MPSSVGF object the
 * MPSSVGFDenoiser was initialized with.
 *
 * @parameter commandBuffer              Command buffer to encode into
 * @parameter sourceTexture              Source image to denoiser
 * @parameter motionVectorTexture        Motion vector texture describing how much each texel has moved,
 *                                       in texels, since the previous frame. See the MPSSVGF object for
 *                                       more details.
 * @parameter depthNormalTexture         Texture containing linear depth in the X component and signed
 *                                       normals in the YZW components. See the MPSSVGF object for more
 *                                       details.
 * @parameter previousDepthNormalTexture Depth/normal texture from the previous frame. See the MPSSVGF
 *                                       object for more details.
 */
- (id <MTLTexture> _Nonnull)encodeToCommandBuffer:(nonnull id <MTLCommandBuffer>)commandBuffer
                                    sourceTexture:(id <MTLTexture> _Nonnull)sourceTexture
                              motionVectorTexture:(id <MTLTexture> _Nullable)motionVectorTexture
                               depthNormalTexture:(id <MTLTexture> _Nonnull)depthNormalTexture
                       previousDepthNormalTexture:(id <MTLTexture> _Nullable)previousDepthNormalTexture
    MPS_SWIFT_NAME(encode(commandBuffer:sourceTexture:motionVectorTexture:depthNormalTexture:previousDepthNormalTexture:));

/**
 * @brief Encode denoising kernels to a command buffer
 *
 * @discussion Simultaneously removes noise from the source texture and optional second source texture,
 * using the additional data in the motion vector, depth/normal, and previous depth/normal textures.
 * Returns the result through the destination texture pointers. The depth/normal texture should be
 * provided as the previous depth/normal texture for the next call to this method. This method will
 * also update an internally managed temporal history to aid the denoising process. To reset this
 * history, call the clearTemporalHistory method. This method will allocate and return several
 * textures from and to the texture allocator the MPSSVGFDenoiser was initialized with. The number
 * of iterations of the bilateral filter is controlled by the bilateralFilterIterations property.
 * Larger numbers of iterations will improve the quality but reduce performance. To configure other
 * parameters of the denoising process, modify the properties of the MPSSVGF object the
 * MPSSVGFDenoiser was initialized with.
 *
 * @parameter commandBuffer              Command buffer to encode into
 * @parameter sourceTexture              Source image to denoiser
 * @parameter destinationTexture         Denoised output image
 * @parameter sourceTexture2             Optional second source image to denoise
 * @parameter destinationTexture2        Denoised second output image, if there is a second source image
 * @parameter motionVectorTexture        Motion vector texture describing how much each texel has moved,
 *                                       in texels, since the previous frame. See the MPSSVGF object for
 *                                       more details.
 * @parameter depthNormalTexture         Texture containing linear depth in the X component and signed
 *                                       normals in the YZW components. See the MPSSVGF object for more
 *                                       details.
 * @parameter previousDepthNormalTexture Depth/normal texture from the previous frame. See the MPSSVGF
 *                                       object for more details.
 */
- (void)encodeToCommandBuffer:(nonnull id <MTLCommandBuffer>)commandBuffer
                sourceTexture:(id <MTLTexture> _Nonnull)sourceTexture
           destinationTexture:(id <MTLTexture> _Nonnull * _Nonnull)destinationTexture
               sourceTexture2:(id <MTLTexture> _Nullable)sourceTexture2
          destinationTexture2:(id <MTLTexture> _Nonnull * _Nullable)destinationTexture2
          motionVectorTexture:(id <MTLTexture> _Nullable)motionVectorTexture
           depthNormalTexture:(id <MTLTexture> _Nonnull)depthNormalTexture
   previousDepthNormalTexture:(id <MTLTexture> _Nullable)previousDepthNormalTexture
    MPS_SWIFT_NAME(encode(commandBuffer:sourceTexture:destinationTexture:sourceTexture2:destinationTexture2:motionVectorTexture:depthNormalTexture:previousDepthNormalTexture:));

@end

#endif
