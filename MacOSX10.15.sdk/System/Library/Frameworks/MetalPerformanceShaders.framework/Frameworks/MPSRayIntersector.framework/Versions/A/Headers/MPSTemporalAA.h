/*!
 *  @header MPSTemporalAA.h
 *  @framework MPSRayIntersector
 *  @description  MPS noise reduction filter interface.
 *
 *  @copyright Copyright (c) 2018 Apple Inc. All rights reserved.
 */

#ifndef MPSTemporalAA_h
#define MPSTemporalAA_h

#import <MPSCore/MPSCoreTypes.h>
#import <MPSCore/MPSKernel.h>

/**
 * @brief Reduces aliasing in an image by accumulating samples over multiple frames
 *
 * @discussion The color for the previous frame will be sampled using the provided motion vector
 * texture and blended with the current frame according to the blendFactor property. The colors
 * from the previous frame will be clamped to the color-space bounding box formed by the center
 * pixel's neighbors to avoid reprojection artifacts, and the motion vector texture will be
 * dilated to avoid aliased silhouette edges under motion.
 *
 * For the best result, the sample positions produced by the renderer should be jittered every
 * frame, ideally using a low discrepency sequence. This will ensure that different sample
 * positions along edges will be visited over time even if the camera is not moving. This will
 * also reduce aliasing due to textures and high-frequency shading.
 *
 * For reference, see "High-Quality Temporal Supersampling" by Karis.
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0))
@interface MPSTemporalAA : MPSKernel <NSSecureCoding, NSCopying>

/**
 * @brief How much to blend the current frame with the previous frame during temporal antialiasing.
 * The final value is given by
 * current * blendFactor + previous * (1 - blendFactor). Must be between zero
 * and one, inclusive. Defaults to 0.1.
 */
@property (nonatomic) float blendFactor;

- (nonnull instancetype)initWithDevice:(nonnull id <MTLDevice>)device NS_DESIGNATED_INITIALIZER;

- (nullable instancetype)initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>)device NS_DESIGNATED_INITIALIZER;

- (nonnull instancetype)copyWithZone:(nullable NSZone *)zone
                              device:(nullable id <MTLDevice>)device;

- (void)encodeWithCoder:(NSCoder * __nonnull)coder;

/**
 * @brief Encode temporal antialiasing a command buffer
 *
 * @discussion The motion vector texture must be at least a two channel texture representing how
 * many texels each texel in the source image(s) have moved since the previous frame. The remaining
 * channels will be ignored if present. This texture may be nil, in which case the motion vector is
 * assumed to be zero, which is suitable for static images.
 *
 * The depth texture must contain the depth values for directly visible geometry for the current
 * frame for each pixel. The first channel must store the depth value from zero to infinity.
 * The depth texture may be nil, but this will prevent motion vectors from being dilated and
 * may introduce aliasing along silhouette edges.
 *
 * The destination texture should be used as the previous texture in the next frame.
 *
 * @param commandBuffer       Command buffer to encode into
 * @param sourceTexture       Current frame to denoise
 * @param previousTexture     Previous denoised frame to reproject into current
 *                            frame
 * @param destinationTexture  Output blended image
 * @param motionVectorTexture Motion vector texture
 * @param depthTexture        The depth values for the current frame
 */
- (void)encodeToCommandBuffer:(nonnull id <MTLCommandBuffer>)commandBuffer
                sourceTexture:(nonnull id <MTLTexture>)sourceTexture
              previousTexture:(nonnull id <MTLTexture>)previousTexture
           destinationTexture:(nonnull id <MTLTexture>)destinationTexture
          motionVectorTexture:(nullable id <MTLTexture>)motionVectorTexture
                 depthTexture:(nullable id <MTLTexture>)depthTexture;

@end

#endif
