/*!
 *  @header MPSImageGuidedFilter.h
 *  @framework MetalPerformanceShaders
 *
 *  @copyright Copyright (c) 2018 Apple Inc. All rights reserved.
 *  @abstract MetalPerformanceShaders guided filter
 */

#ifndef MPS_MPSImageGuidedFilter_h
#define MPS_MPSImageGuidedFilter_h

#include <MPSImage/MPSImageKernel.h>
#include <simd/simd.h>


/*!
 *  @class      MPSImageGuidedFilter
 *  @discussion Perform Guided Filter to produce a coefficients image
 *              The filter is broken into two stages:
 *                  - Regression
 *                  - Reconstruction
 *
 *              The regression stage learns a 4-channel "coefficient" texture (typically at a very low resolution),
 *              and represents the per-pixel linear regression of the source texture to the guidance texture.
 *
 *              The reconstruction stage upsamples the coefficeints to the same size as the final output and
 *              then at each pixel computes the inner product to produce the output.
 *
 *              The filter is broken into two stages to allow coefficients to be filtered (such as for example - temporally filtering for video to prevent flicker).
 *
 *              There is also support for an optional weight texture that can be used to discard values in the source data.
 *
 *              Guided Filter is described at https://arxiv.org/pdf/1505.00996.pdf.
 *
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
@interface  MPSImageGuidedFilter : MPSKernel

/*! @property   kernelDiameter
 *  @abstract   The local window size
 *  @discussion The local window size.
 */
@property (readonly, nonatomic) NSUInteger kernelDiameter;

/*! @property   epsilon
 *  @abstract   The regularization parameter
 *  @discussion The parameter used when computing the linear coefficients a and b.
 */
@property (readwrite, nonatomic) float epsilon;

/*! @property   reconstructScale
 *  @abstract   The scale parameter
 *  @discussion The parameter used to scale the result of the reconstruction operation.
 *              The default value is 1.0f.
 */
@property (readwrite, nonatomic) float reconstructScale;

/*! @property   reconstructOffset
 *  @abstract   The offset parameter
 *  @discussion The offset parameter added to the result of the scaled reconstructed value.
 *              The default value is 0.0f.
 */
@property (readwrite, nonatomic) float reconstructOffset;

/*!
 *  @abstract Specifies information to apply the guided filter regression.
 *  @param    device            The device the filter will run on
 *  @param    kernelDiameter    The local window size
 *  @return     A valid MPSImageGuidedFilterRegression object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                        kernelDiameter: (NSUInteger) kernelDiameter NS_DESIGNATED_INITIALIZER;

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

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
-(nullable instancetype) initWithCoder: (NSCoder * __nonnull)aDecoder
                                device: (nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

/*!
 * @abstract Perform Guided Filter Regression (correlation) to produce a coefficients texture
 * @discussion The filter will not begin to execute until after the command buffer has been enqueued and committed.
 *
 * @param  commandBuffer           A valid MTLCommandBuffer.
 * @param  sourceTexture           Input source texture to be filtered (typically a mask).  This should be a single channel image.
 * @param  guidanceTexture         Input guidance texture.  This should be a color (RGB) image.
 * @param  weightsTexture          Optional input confidence texture.  This should also a single channel image.
 * @param  destinationCoefficientsTexture  Output texture with four coefficients that minimize the mean squared error between
 *                                         the source and an affine function of guidance R, G, B.
 * Note: The destinationCoefficientsTexture computes the linear cofficients "a" and "b".  The "a" coefficient is
 *       stored in the RGB channels of destinationCoefficientsTexture and the "b" coefficient in the alpha chnanel.
 *
 *       Set the MPSKernelOptionsAllowReducedPrecision in the "options" property for this kernel to peform the
 *       computations using half-precision arithmetic.  This can potentially improve performance and/or power usage.
 */
- (void)encodeRegressionToCommandBuffer: (nonnull id <MTLCommandBuffer>)commandBuffer
                          sourceTexture: (nonnull id <MTLTexture>)sourceTexture
                        guidanceTexture: (nonnull id <MTLTexture>)guidanceTexture
                         weightsTexture: (nullable id <MTLTexture>)weightsTexture
         destinationCoefficientsTexture: (nonnull id <MTLTexture>)destinationCoefficientsTexture;

/*!
 * @abstract Perform Guided Filter Reconstruction (inference) to produce the filtered output
 * @discussion The filter will not begin to execute until after the command buffer has been enqueued and committed.
 *
 * @pparam sourceGuidanceTexture Input guidance pixel buffer.  This should be a color (RGB) image.
 * @pparam coefficientsTexture   Input coefficients texture generated generated by a previous encodeRegressionToCommandBuffer
 * @param destinationTexture     Output texture
 *
 * Note: The coefficients are upsampled at the reconstruction of the filtered data.
 *       Reconstruct(guidance RGB) = a.r * R + a.g * G + a.b * B + b, where a and b
 *       are the coefficients learnt using encodeRegressionToCommandBuffer.
 *
 *       Final reconstructed value = value * reconstructScale + reconstructOffset
 */
- (void)encodeReconstructionToCommandBuffer: (nonnull id <MTLCommandBuffer>)commandBuffer
                            guidanceTexture: (nonnull id <MTLTexture>)guidanceTexture
                        coefficientsTexture: (nonnull id <MTLTexture>)coefficientsTexture
                         destinationTexture: (nonnull id <MTLTexture>)destinationTexture;



/*!
 * @abstract Perform per-channel (non-color correlated) Guided Filter Regression (correlation) to produce a coefficients texture
 * @discussion The filter will not begin to execute until after the command buffer has been enqueued and committed.
 *              This encode call differs from the one above in that the correlations are not computed across channels
 *              and therefore this filter computes two coefficient textures: ai and bi.
 * @param  commandBuffer           A valid MTLCommandBuffer.
 * @param  sourceTexture           Input source texture to be filtered.
 * @param  guidanceTexture       Input guidance texture.  This should be a color (RGB) image.
 * @param  weightsTexture          Optional input confidence texture.  This should be a single channel image.
 * @param  destinationCoefficientsTextureA  Output texture with four coefficients A that minimize the mean squared error between
 *                                         the source channels and an affine function of guidance channels.
 * @param  destinationCoefficientsTextureB  Output texture with four coefficients B that minimize the mean squared error between
 *                                         the source channels and an affine function of guidance channels.
 *
 *       Set the MPSKernelOptionsAllowReducedPrecision in the "options" property for this kernel to peform the
 *       computations using half-precision arithmetic.  This can potentially improve performance and/or power usage.
 */
- (void)encodeRegressionToCommandBuffer: (nonnull id <MTLCommandBuffer>)commandBuffer
                          sourceTexture: (nonnull id <MTLTexture>)sourceTexture
                        guidanceTexture: (nonnull id <MTLTexture>)guidanceTexture
                         weightsTexture: (nullable id <MTLTexture>)weightsTexture
        destinationCoefficientsTextureA: (nonnull id <MTLTexture>)destinationCoefficientsTextureA
        destinationCoefficientsTextureB: (nonnull id <MTLTexture>)destinationCoefficientsTextureB

MPS_SWIFT_NAME(encodeRegression(commandBuffer:source:guidance:weights:destinationCoefficientsA:destinationCoefficientsB:))
MPS_AVAILABLE_STARTING(macos(10.15.4), ios(13.2), macCatalyst(13.2), tvos(13.2));

/*!
 * @abstract Perform Guided Filter Reconstruction (inference) to produce the filtered output
 * @discussion The filter will not begin to execute until after the command buffer has been enqueued and committed.
 *
 * @param commandBuffer                  A valid MTLCommandBuffer.
 * @param guidanceTexture              Input guidance pixel buffer.
 * @param coefficientsTextureA   Input coefficients A texture generated generated by a previous encodeRegressionToCommandBuffer.
 * @param coefficientsTextureB   Input coefficients B texture generated generated by a previous encodeRegressionToCommandBuffer.
 * @param destinationTexture       Output texture
 */
- (void)encodeReconstructionToCommandBuffer: (nonnull id <MTLCommandBuffer>)commandBuffer
                            guidanceTexture: (nonnull id <MTLTexture>)guidanceTexture
                       coefficientsTextureA: (nonnull id <MTLTexture>)coefficientsTextureA
                       coefficientsTextureB: (nonnull id <MTLTexture>)coefficientsTextureB
                         destinationTexture: (nonnull id <MTLTexture>)destinationTexture

MPS_SWIFT_NAME(encodeReconstruction(commandBuffer:guidance:coefficientsA:coefficientsB:destination:))
MPS_AVAILABLE_STARTING(macos(10.15.4), ios(13.2), macCatalyst(13.2), tvos(13.2));

@end  /* MPSImageGuidedFilter */


#endif  /* MPS_MPSImageGuidedFilter_h */

