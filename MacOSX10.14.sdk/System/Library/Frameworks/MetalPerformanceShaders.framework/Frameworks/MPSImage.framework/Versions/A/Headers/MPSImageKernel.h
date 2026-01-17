/*!
 *  @header MPSImageKernel.h
 *  @framework MetalPerformanceShaders.framework
 *
 *  @copyright Copyright (c) 2015 Apple Inc. All rights reserved.
 *  @abstract MetalPerformanceShaders filter base classes
 */

#ifndef _MPS_MPSImageKernel_
#define _MPS_MPSImageKernel_

#import <MPSCore/MPSKernel.h>
#import <MPSImage/MPSImageTypes.h>

/*!
 *  @typedef    MPSCopyAllocator
 *  @memberof   MPSKernel
 *  @abstract   A block to make a copy of sourceTexture for MPSKernels that can only execute out of place.
 *  @discussion Some MPSKernel objects may not be able to operate in place. When that occurs, and in-place
 *              operation is requested, MPS will call back to this block to get a new texture
 *              to return instead. To avoid spending long periods of time allocating pages to back the
 *              MTLTexture, the block should attempt to reuse textures. The texture returned from the
 *              MPSCopyAllocator will be returned instead of the sourceTexture from the MPSKernel method
 *              on return.
 *              @code
 *              // A MPSCopyAllocator to handle cases where in-place operation fails.
 *              MPSCopyAllocator myAllocator = ^id <MTLTexture>( MPSKernel * __nonnull filter,
 *                                                              __nonnull id <MTLCommandBuffer> cmdBuf,
 *                                                              __nonnull id <MTLTexture> sourceTexture)
 *              {
 *                  MTLPixelFormat format = sourceTexture.pixelFormat;  // FIXME: is this format writable?
 *                  MTLTextureDescriptor *d = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat: format
 *                                               width: sourceTexture.width
 *                                              height: sourceTexture.height
 *                                           mipmapped: NO];
 *                  d.usage = MTLTextureUsageShaderRead | MTLTextureUsageShaderWrite;
 *
 *                  //FIXME: Allocating a new texture each time is slow. They take up to 1 ms each.
 *                  //       There are not too many milliseconds in a video frame! You can recycle
 *                  //       old textures (or MTLBuffers and make textures from them) and reuse
 *                  //       the memory here.
 *                  id <MTLTexture> result = [cmdBuf.device newTextureWithDescriptor: d];
 *
 *                  // FIXME: If there is any metadata associated with sourceTexture such as colorspace
 *                  //        information, MTLResource.label, MTLResource.cpuCacheMode mode,
 *                  //        MTLResource.MTLPurgeableState, etc., it may need to be similarly associated
 *                  //        with the new texture to avoid losing your metadata.
 *
 *                  // FIXME: If filter.clipRect doesn't cover the entire image, you may need to copy
 *                  //        pixels from sourceTexture to the new texture or regions of the new texture
 *                  //        will be uninitialized. You can make a MTLCommandEncoder to encode work on
 *                  //        the MTLCommandBuffer here to do that work, if necessary. It will be
 *                  //        scheduled to run immediately before the MPSKernel work. Do not call
 *                  //        [MTLCommandBuffer enqueue/commit/waitUntilCompleted/waitUntilScheduled]
 *                  //        in the MPSCopyAllocator block. Make sure to call -endEncoding on the
 *                  //        MTLCommandEncoder so that the MTLCommandBuffer has no active encoder
 *                  //        before returning.
 *
 *                  // CAUTION: The next command placed on the MTLCommandBuffer after the MPSCopyAllocator
 *                  //          returns is almost assuredly going to be encoded with a MTLComputeCommandEncoder.
 *                  //          Creating any other type of encoder in the MPSCopyAllocator will probably cost
 *                  //          an additional 0.5 ms of both CPU _AND_ GPU time (or more!) due to a double
 *                  //          mode switch penalty.
 *
 *                  // CAUTION: If other objects (in addition to the caller of -encodeToCommandBuffer:inPlaceTexture:...)
 *                  //          own a reference to sourceTexture, they may need to be notified that
 *                  //          sourceTexture has been replaced so that they can release that resource
 *                  //          and adopt the new texture.
 *
 *                  //          The reference to sourceTexture owned by the caller of
 *                  //          -encodeToCommandBuffer:inPlaceTexture... will be released by
 *                  //          -encodeToCommandBuffer:inPlaceTexture:... after the kernel is encoded if
 *                  //          and only if the MPSCopyAllocator is called, and the operation is successfully
 *                  //          encoded out of place.
 *
 *                  return result;
 *                  // d is autoreleased
 *              };
 *              @endcode
 *              If nil is returned by the allocator, NO will be returned by the calling function.
 *
 *              When the MPSCopyAllocator is called, no MTLCommandEncoder is active on the commandBuffer.
 *              You may create a MTLCommandEncoder in the block to initialize the texture. Make sure
 *              to call -endEncoding on it before returning, if you do.
 *
 *  @param      filter          A valid pointer to the MPSKernel that is calling the MPSCopyAllocator. From
 *                              it you can get the clipRect of the intended operation.
 *  @param      commandBuffer   A valid MTLCommandBuffer. It can be used to obtain the device against
 *                              which to allocate the new texture. You may also enqueue operations on
 *                              the commandBuffer to initialize the texture on a encoder allocated in the
 *                              block. You may not submit, enqueue or wait for scheduling/completion of
 *                              the command buffer.
 *  @param      sourceTexture   The texture that is providing the source image for the filter. You may
 *                              wish to use its size and MTLPixelFormat for the new texture, but it is
 *                              not requred.
 *
 *  @return     A new valid MTLTexture to use as the destination for the MPSKernel. If the calling function
 *              succeeds, its texture parameter will be overwritten with a pointer to this texture. If the
 *              calling function fails (highly unlikely, except for user error) then the texture
 *              will be released before the calling function returns.
 */



#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wignored-attributes"
/* Squelch broken clan warning here for ns_returns_retained rdar://problem/20130079 */

typedef id <MTLTexture> __nonnull NS_RETURNS_RETAINED (^MPSCopyAllocator)(
      MPSKernel * __nonnull filter,
      id <MTLCommandBuffer> __nonnull commandBuffer,
      id <MTLTexture> __nonnull sourceTexture);


#pragma clang diagnostic pop




@class MPSImage;

/*!
 *  @class      MPSUnaryImageKernel
 *  @dependency This depends on Metal.framework
 *  @discussion A MPSUnaryImageKernel consumes one MTLTexture and produces one MTLTexture.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(9.0), tvos(9.0))
@interface MPSUnaryImageKernel : MPSKernel


/*! @property   offset
 *  @abstract   The position of the destination clip rectangle origin relative to the source buffer.
 *  @discussion The offset is defined to be the position of clipRect.origin in source coordinates.
 *              Default: {0,0,0}, indicating that the top left corners of the clipRect and source image align.
 *
 *              See Also: @ref MetalPerformanceShaders.h subsubsection_mpsoffset
 */
@property (readwrite, nonatomic) MPSOffset                offset;

/*! @property   clipRect
 *  @abstract   An optional clip rectangle to use when writing data. Only the pixels in the rectangle will be overwritten.
 *  @discussion A MTLRegion that indicates which part of the destination to overwrite. If the clipRect does not lie
 *              completely within the destination image, the intersection between clip rectangle and destination bounds is
 *              used.   Default: MPSRectNoClip (MPSKernel::MPSRectNoClip) indicating the entire image.
 *
 *              See Also: @ref MetalPerformanceShaders.h subsubsection_clipRect
 */
@property (readwrite, nonatomic) MTLRegion               clipRect;


/*! @property   edgeMode
 *  @abstract   The MPSImageEdgeMode to use when texture reads stray off the edge of an image
 *  @discussion Most MPSKernel objects can read off the edge of the source image. This can happen because of a
 *              negative offset property, because the offset + clipRect.size is larger than the
 *              source image or because the filter looks at neighboring pixels, such as a Convolution
 *              or morphology filter.   Default: usually MPSImageEdgeModeZero. (Some MPSKernel types default
 *              to MPSImageEdgeModeClamp, because MPSImageEdgeModeZero is either not supported or
 *              would produce unexpected results.)
 *
 *              See Also: @ref MetalPerformanceShaders.h subsubsection_edgemode
 */
@property (readwrite, nonatomic) MPSImageEdgeMode        edgeMode;

/*!
 *  @abstract   Standard init with default properties per filter type
 *  @param      device      The device that the filter will be used on. May not be NULL.
 *  @result     a pointer to the newly initialized object. This will fail, returning
 *              nil if the device is not supported. Devices must be
 *              MTLFeatureSet_iOS_GPUFamily2_v1 or later.
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
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER
                            MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0));

/*!
 *  This method attempts to apply the MPSKernel in place on a texture.
 *
 *          In-place operation means that the same texture is used both to hold the input
 *          image and the results. Operating in-place can be an excellent way to reduce
 *          resource utilization, and save time and energy. While simple Metal kernels can
 *          not operate in place because textures can not be readable and writable at the
 *          same time, some MPSKernels can operate in place because they use
 *          multi-pass algorithms. Whether a MPSKernel can operate in-place can
 *          depend on current hardware, operating system revision and the parameters
 *          and properties passed to it. You should never assume that a MPSKernel will
 *          continue to work in place, even if you have observed it doing so before.
 *
 *  If the operation succeeds in-place, YES is returned.  If the in-place operation
 *  fails and no copyAllocator is provided, then NO is returned. Without a fallback
 *  MPSCopyAllocator, in neither case is the pointer held at *texture modified.
 *
 *  Failure during in-place operation is very common and will occur inconsistently across
 *  different hardware platforms and OS releases. Without a fallback MPSCopyAllocator,
 *  operating in place may require significant error handling code to accompany each
 *  call to -encodeToCommandBuffer:..., complicating your code.
 *
 *  You may find it simplifies your code to provide a fallback MPSCopyAllocator so
 *  that the operation can proceed reliably even when it can not proceed in-place.
 *  When an in-place filter fails, the MPSCopyAllocator (if any) will be
 *  invoked to create a new texture in which to write the results, allowing the
 *  filter to proceed reliably out-of-place. The original texture will be released,
 *  replaced with a pointer to the new texture and YES will be returned. If the
 *  allocator returns an invalid texture, it is released, *texture remains unmodified
 *  and NO is returned.  Please see the MPSCopyAllocator definition for a sample allocator
 *  implementation.
 *
 *  Sample usage with a copy allocator:
 *  @code
 *  id <MTLTexture> inPlaceTex = ...;
 *  MPSImageSobel *sobelFiler = [[MPSImageSobel alloc] initWithDevice: my_device];
 *
 *  // With a fallback MPSCopyAllocator, failure should only occur in exceptional
 *  // conditions such as MTLTexture allocation failure or programmer error.
 *  // That is, the operation is roughly as robust as the MPSCopyAllocator.
 *  // Depending on the quality of that, we might decide we are justified here
 *  // in not checking the return value.
 *  [sobelFilter encodeToCommandBuffer: my_command_buffer
 *                      inPlaceTexture: &inPlaceTex  // may be replaced!
 *               fallbackCopyAllocator: myAllocator];
 *
 *  // If myAllocator was not called:
 *  //
 *  //      inPlaceTex holds the original texture with the result pixels in it
 *  //
 *  // else,
 *  //
 *  //      1) myAllocator creates a new texture.
 *  //      2) The new texture pixel data is overwritten by MPSUnaryImageKernel.
 *  //      3) The old texture passed in *inPlaceTex is released once.
 *  //      4) *inPlaceTex = the new texture
 *  //
 *  // In either case, the caller should now hold one reference to the texture now held in
 *  // inPlaceTex, whether it was replaced or not. Most of the time that means that nothing
 *  // further needs to be done here, and you can proceed to the next image encoding operation.
 *  // However, if other agents held references to the original texture, they still hold them
 *  // and may need to be alerted that the texture has been replaced so that they can retain
 *  // the new texture and release the old one.
 *
 *  [sobelFilter release];  // if not ARC, clean up the MPSImageSobel object
 *  @endcode
 *
 *  Note: Image filters that look at neighboring pixel values may actually consume more
 *        memory when operating in place than out of place. Many such operations are
 *        tiled internally to save intermediate texture storage, but can not tile when
 *        operating in place. The memory savings for tiling is however very short term,
 *        typically the lifetime of the MTLCommandBuffer.
 *
 *  @abstract   Attempt to apply a MPSKernel to a texture in place.
 *  @param      commandBuffer       A valid MTLCommandBuffer to receive the encoded filter
 *  @param      texture             A pointer to a valid MTLTexture containing source image.
 *                                  On success, the image contents and possibly texture itself
 *                                  will be replaced with the result image.
 *  @param      copyAllocator       An optional block to allocate a new texture to hold the
 *                                  results, in case in-place operation is not possible. The
 *                                  allocator may use a different MTLPixelFormat or size than
 *                                  the original texture. You may enqueue operations on the
 *                                  provided MTLCommandBuffer using the provided
 *                                  MTLComputeCommandEncoder to initialize the texture contents.
 *  @return     On success, YES is returned. The texture may have been replaced with a new
 *              texture if a copyAllocator was provided.  On failure, NO is returned. The
 *              texture is unmodified.
 */
-(BOOL)    encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>)commandBuffer
                  inPlaceTexture: (__nonnull id <MTLTexture> __strong * __nonnull) texture
           fallbackCopyAllocator: (nullable MPSCopyAllocator) copyAllocator
                MPS_SWIFT_NAME(encode(commandBuffer:inPlaceTexture:fallbackCopyAllocator:));


/*!
 *  @abstract   Encode a MPSKernel into a command Buffer.  The operation shall proceed out-of-place.
 *  @param      commandBuffer       A valid MTLCommandBuffer to receive the encoded filter
 *  @param      sourceTexture       A valid MTLTexture containing the source image.
 *  @param      destinationTexture  A valid MTLTexture to be overwritten by result image. DestinationTexture may not alias sourceTexture.
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                sourceTexture: (nonnull id <MTLTexture>) sourceTexture
           destinationTexture: (nonnull id <MTLTexture>) destinationTexture
            MPS_SWIFT_NAME(encode(commandBuffer:sourceTexture:destinationTexture:));


/*!
 *  @abstract   Encode a MPSKernel into a command Buffer.  The operation shall proceed out-of-place.
 *  @param      commandBuffer       A valid MTLCommandBuffer to receive the encoded filter
 *  @param      sourceImage         A valid MPSImage containing the source image.
 *  @param      destinationImage    A valid MPSImage to be overwritten by result image. DestinationImage may not alias sourceImage.
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                  sourceImage: (nonnull MPSImage *) sourceImage
             destinationImage: (nonnull MPSImage *) destinationImage
            MPS_SWIFT_NAME(encode(commandBuffer:sourceImage:destinationImage:))
            // FIXME: availability info missing
            ;

/*!
 *  sourceRegionForDestinationSize: is used to determine which region of the
 *  sourceTexture will be read by encodeToCommandBuffer:sourceTexture:destinationTexture
 *  (and similar) when the filter runs. This information may be needed if the
 *  source image is broken into multiple textures.  The size of the full
 *  (untiled) destination image is provided. The region of the full (untiled)
 *  source image that will be read is returned. You can then piece together an
 *  appropriate texture containing that information for use in your tiled context.
 *
 *  The function will consult the MPSUnaryImageKernel offset and clipRect parameters, 
 *  to determine the full region read by the function. Other parameters such as
 *  sourceClipRect, kernelHeight and kernelWidth will be consulted as necessary.
 *  All properties should be set to intended values prior to calling 
 *  sourceRegionForDestinationSize:.
 *
 *      Caution: This function operates using global image coordinates, but
 *      -encodeToCommandBuffer:... uses coordinates local to the source and
 *      destination image textures. Consequently, the offset and clipRect 
 *      attached to this object will need to be updated using a global to 
 *      local coordinate transform before -encodeToCommandBuffer:... is 
 *      called.
 *
 *  @abstract   Determine the region of the source texture that will be read for a encode operation 
 *  @param      destinationSize The size of the full virtual destination image.
 *  @return     The area in the virtual source image that will be read.
 */
-(MPSRegion) sourceRegionForDestinationSize: (MTLSize) destinationSize
            MPS_SWIFT_NAME(sourceRegion(destinationSize:));

@end



/*!
 *  @class      MPSBinaryImageKernel
 *  @dependency This depends on Metal.framework
 *  @discussion A MPSBinaryImageKernel consumes two MTLTextures and produces one MTLTexture.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(9.0), tvos(9.0))
@interface MPSBinaryImageKernel : MPSKernel

/*! @property   primaryOffset
 *  @abstract   The position of the destination clip rectangle origin relative to the primary source buffer.
 *  @discussion The offset is defined to be the position of clipRect.origin in source coordinates.
 *              Default: {0,0,0}, indicating that the top left corners of the clipRect and primary source image align.
 *
 *              See Also: @ref MetalPerformanceShaders.h  subsubsection_mpsoffset
 */
@property (readwrite, nonatomic) MPSOffset                primaryOffset;

/*! @property   secondaryOffset
 *  @abstract   The position of the destination clip rectangle origin relative to the secondary source buffer.
 *  @discussion The offset is defined to be the position of clipRect.origin in source coordinates.
 *              Default: {0,0,0}, indicating that the top left corners of the clipRect and secondary source image align.
 *
 *              See Also: @ref MetalPerformanceShaders.h  subsubsection_mpsoffset
 */
@property (readwrite, nonatomic) MPSOffset                secondaryOffset;


/*! @property   primaryEdgeMode
 *  @abstract   The MPSImageEdgeMode to use when texture reads stray off the edge of the primary source image
 *  @discussion Most MPSKernel objects can read off the edge of a source image. This can happen because of a
 *              negative offset property, because the offset + clipRect.size is larger than the
 *              source image or because the filter looks at neighboring pixels, such as a Convolution
 *              or morphology filter.   Default: usually MPSImageEdgeModeZero. (Some MPSKernel types default
 *              to MPSImageEdgeModeClamp, because MPSImageEdgeModeZero is either not supported or
 *              would produce unexpected results.)
 *
 *              See Also: @ref MetalPerformanceShaders.h  subsubsection_edgemode
 */
@property (readwrite, nonatomic) MPSImageEdgeMode        primaryEdgeMode;

/*! @property   secondaryEdgeMode
 *  @abstract   The MPSImageEdgeMode to use when texture reads stray off the edge of the secondary source image
 *  @discussion Most MPSKernel objects can read off the edge of a source image. This can happen because of a
 *              negative offset property, because the offset + clipRect.size is larger than the
 *              source image or because the filter looks at neighboring pixels, such as a Convolution
 *              or morphology filter.   Default: usually MPSImageEdgeModeZero. (Some MPSKernel types default
 *              to MPSImageEdgeModeClamp, because MPSImageEdgeModeZero is either not supported or
 *              would produce unexpected results.)
 *
 *              See Also: @ref MetalPerformanceShaders.h  subsubsection_edgemode
 */
@property (readwrite, nonatomic) MPSImageEdgeMode        secondaryEdgeMode;

/*! @property   clipRect
 *  @abstract   An optional clip rectangle to use when writing data. Only the pixels in the rectangle will be overwritten.
 *  @discussion A MTLRegion that indicates which part of the destination to overwrite. If the clipRect does not lie
 *              completely within the destination image, the intersection between clip rectangle and destination bounds is
 *              used.   Default: MPSRectNoClip (MPSKernel::MPSRectNoClip) indicating the entire image.
 *
 *              See Also: @ref MetalPerformanceShaders.h subsubsection_clipRect
 */
@property (readwrite, nonatomic) MTLRegion               clipRect;

/*!
 *  @abstract   Standard init with default properties per filter type
 *  @param      device      The device that the filter will be used on. May not be NULL.
 *  @result     a pointer to the newly initialized object. This will fail, returning
 *              nil if the device is not supported. Devices must be
 *              MTLFeatureSet_iOS_GPUFamily2_v1 or later.
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
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER
                MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0));


/*!
 *  This method attempts to apply the MPSKernel in place on a texture.
 *
 *          In-place operation means that the same texture is used both to hold the input
 *          image and the results. Operating in-place can be an excellent way to reduce
 *          resource utilization, and save time and energy. While simple Metal kernels can
 *          not operate in place because textures can not be readable and writable at the
 *          same time, some MPSKernels can operate in place because they use
 *          multi-pass algorithms. Whether a MPSKernel can operate in-place can
 *          depend on current hardware, operating system revision and the parameters
 *          and properties passed to it. You should never assume that a MPSKernel will
 *          continue to work in place, even if you have observed it doing so before.
 *
 *  If the operation succeeds in-place, YES is returned.  If the in-place operation
 *  fails and no copyAllocator is provided, then NO is returned. In neither
 *  case is the pointer held at *texture modified.
 *
 *  Failure during in-place operation is common. You may find it simplifies your
 *  code to provide a copyAllocator. When an in-place filter fails, your
 *  copyAllocator will be invoked to create a new texture in which to write
 *  the results, allowing the filter to proceed reliably out-of-place. The
 *  original texture will be released, replaced with a pointer to the new texture
 *  and YES will be returned. If the allocator returns an invalid texture, it is
 *  released, *texture remains unmodified and NO is returned.  Please see the
 *  MPSCopyAllocator definition for a sample allocator implementation.
 *
 *  Note: Image filters that look at neighboring pixel values may actually consume more
 *        memory when operating in place than out of place. Many such operations are
 *        tiled internally to save intermediate texture storage, but can not tile when
 *        operating in place. The memory savings for tiling is however very short term,
 *        typically the lifetime of the MTLCommandBuffer.
 *
 *  @abstract   Attempt to apply a MPSKernel to a texture in place.
 *  @param      commandBuffer           A valid MTLCommandBuffer to receive the encoded filter
 *  @param      primaryTexture          A pointer to a valid MTLTexture containing the
 *                                      primary source image. It will not be overwritten.
 *  @param      inPlaceSecondaryTexture A pointer to a valid MTLTexture containing secondary image.
 *                                      On success, the image contents and possibly texture itself
 *                                      will be replaced with the result image.
 *  @param      copyAllocator           An optional block to allocate a new texture to hold the
 *                                      results, in case in-place operation is not possible. The
 *                                      allocator may use a different MTLPixelFormat or size than
 *                                      the original texture. You may enqueue operations on the
 *                                      provided MTLCommandBuffer using the provided
 *                                      MTLComputeCommandEncoder to initialize the texture contents.
 *  @return     On success, YES is returned. The texture may have been replaced with a new
 *              texture if a copyAllocator was provided.  On failure, NO is returned. The
 *              texture is unmodified.
 */
-(BOOL)    encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>)commandBuffer
                  primaryTexture: (nonnull id <MTLTexture>) primaryTexture
         inPlaceSecondaryTexture: (__nonnull id <MTLTexture> __strong * __nonnull) inPlaceSecondaryTexture
           fallbackCopyAllocator: (nullable MPSCopyAllocator) copyAllocator
    MPS_SWIFT_NAME(encode(commandBuffer:primaryTexture:inPlaceSecondaryTexture:fallbackCopyAllocator:));

/*!
 *  @abstract   Attempt to apply a MPSKernel to a texture in place.
 *  @discussion This method attempts to apply the MPSKernel in place on a texture.
 *  @code
 *          In-place operation means that the same texture is used both to hold the input
 *          image and the results. Operating in-place can be an excellent way to reduce
 *          resource utilization, and save time and energy. While simple Metal kernels can
 *          not operate in place because textures can not be readable and writable at the
 *          same time, some MPSKernels can operate in place because they use
 *          multi-pass algorithms. Whether a MPSKernel can operate in-place can
 *          depend on current hardware, operating system revision and the parameters
 *          and properties passed to it. You should never assume that a MPSKernel will
 *          continue to work in place, even if you have observed it doing so before.
 *  @endcode
 *  If the operation succeeds in-place, YES is returned.  If the in-place operation
 *  fails and no copyAllocator is provided, then NO is returned. In neither
 *  case is the pointer held at *texture modified.
 *
 *  Failure during in-place operation is common. You may find it simplifies your
 *  code to provide a copyAllocator. When an in-place filter fails, your
 *  copyAllocator will be invoked to create a new texture in which to write
 *  the results, allowing the filter to proceed reliably out-of-place. The
 *  original texture will be released, replaced with a pointer to the new texture
 *  and YES will be returned. If the allocator returns an invalid texture, it is
 *  released, *texture remains unmodified and NO is returned.  Please see the
 *  MPSCopyAllocator definition for a sample allocator implementation.
 *
 *  Note: Image filters that look at neighboring pixel values may actually consume more
 *        memory when operating in place than out of place. Many such operations are
 *        tiled internally to save intermediate texture storage, but can not tile when
 *        operating in place. The memory savings for tiling is however very short term,
 *        typically the lifetime of the MTLCommandBuffer.
 *
 *  @param      commandBuffer           A valid MTLCommandBuffer to receive the encoded filter
 *  @param      inPlacePrimaryTexture   A pointer to a valid MTLTexture containing secondary image.
 *                                      On success, the image contents and possibly texture itself
 *                                      will be replaced with the result image.
 *  @param      secondaryTexture        A pointer to a valid MTLTexture containing the
 *                                      primary source image. It will not be overwritten.
 *  @param      copyAllocator           An optional block to allocate a new texture to hold the
 *                                      results, in case in-place operation is not possible. The
 *                                      allocator may use a different MTLPixelFormat or size than
 *                                      the original texture. You may enqueue operations on the
 *                                      provided MTLCommandBuffer using the provided
 *                                      MTLComputeCommandEncoder to initialize the texture contents.
 *  @return     On success, YES is returned. The texture may have been replaced with a new
 *              texture if a copyAllocator was provided.  On failure, NO is returned. The
 *              texture is unmodified.
 */
-(BOOL)    encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>)commandBuffer
           inPlacePrimaryTexture: (__nonnull id <MTLTexture> __strong * __nonnull) inPlacePrimaryTexture
                secondaryTexture: (nonnull id <MTLTexture>) secondaryTexture
           fallbackCopyAllocator: (nullable MPSCopyAllocator) copyAllocator
        MPS_SWIFT_NAME(encode(commandBuffer:inPlacePrimaryTexture:secondaryTexture:fallbackCopyAllocator:));



/*!
 *  @abstract   Encode a MPSKernel into a command Buffer.  The operation shall proceed out-of-place.
 *  @param      commandBuffer       A valid MTLCommandBuffer to receive the encoded filter
 *  @param      primaryTexture      A valid MTLTexture containing the primary source image.
 *  @param      secondaryTexture    A valid MTLTexture containing the secondary source image.
 *  @param      destinationTexture  A valid MTLTexture to be overwritten by result image. destinationTexture may not alias the source textures.
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
               primaryTexture: (nonnull id <MTLTexture>) primaryTexture
             secondaryTexture: (nonnull id <MTLTexture>) secondaryTexture
           destinationTexture: (nonnull id <MTLTexture>) destinationTexture
    MPS_SWIFT_NAME(encode(commandBuffer:primaryTexture:secondaryTexture:destinationTexture:));

/*! @abstract   Encode a MPSKernel into a command Buffer.  The operation shall proceed out-of-place.
 *  @param      commandBuffer       A valid MTLCommandBuffer to receive the encoded filter
 *  @param      primaryImage        A valid MPSImage containing the primary source image.
 *  @param      secondaryImage      A valid MPSImage containing the secondary source image.
 *  @param      destinationImage    A valid MPSImage to be overwritten by result image. destinationImage may not alias the source images.
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                 primaryImage: (MPSImage * __nonnull) primaryImage
               secondaryImage: (MPSImage * __nonnull) secondaryImage
             destinationImage: (MPSImage * __nonnull) destinationImage
    MPS_SWIFT_NAME(encode(commandBuffer:primaryImage:secondaryImage:destinationImage:))
    // FIXME: availability info missing
    ;

/*!
 *  primarySourceRegionForDestinationSize: is used to determine which region of the
 *  primaryTexture will be read by encodeToCommandBuffer:primaryTexture:secondaryTexture:destinationTexture
 *  (and in-place variants) when the filter runs. This information may be needed if the
 *  primary source image is broken into multiple textures.  The size of the full
 *  (untiled) destination image is provided. The region of the full (untiled)
 *  source image that will be read is returned. You can then piece together an
 *  appropriate texture containing that information for use in your tiled context.
 *
 *  The function will consult the MPSBinaryImageKernel primaryOffset and clipRect parameters,
 *  to determine the full region read by the function. Other parameters such as
 *  kernelHeight and kernelWidth will be consulted as necessary. All properties
 *  should be set to intended values prior to calling primarySourceRegionForDestinationSize:.
 *
 *      Caution: This function operates using global image coordinates, but
 *      -encodeToCommandBuffer:... uses coordinates local to the source and
 *      destination image textures. Consequently, the primaryOffset and clipRect
 *      attached to this object will need to be updated using a global to
 *      local coordinate transform before -encodeToCommandBuffer:... is
 *      called.
 *
 *  @abstract   Determine the region of the source texture that will be read for a encode operation
 *  @param      destinationSize     The size of the full virtual destination image.
 *  @return     The area in the virtual source image that will be read.
 */
-(MPSRegion) primarySourceRegionForDestinationSize: (MTLSize) destinationSize;

/*!
 *  secondarySourceRegionForDestinationSize: is used to determine which region of the
 *  sourceTexture will be read by encodeToCommandBuffer:primaryTexture:secondaryTexture:destinationTexture
 *  (and in-place variants) when the filter runs. This information may be needed if the
 *  secondary source image is broken into multiple textures.  The size of the full
 *  (untiled) destination image is provided. The region of the full (untiled)
 *  secondary source image that will be read is returned. You can then piece together an
 *  appropriate texture containing that information for use in your tiled context.
 *
 *  The function will consult the MPSBinaryImageKernel secondaryOffset and clipRect
 *  parameters, to determine the full region read by the function. Other parameters
 *  such as kernelHeight and kernelWidth will be consulted as necessary.  All properties
 *  should be set to intended values prior to calling secondarySourceRegionForDestinationSize:.
 *
 *      Caution: This function operates using global image coordinates, but
 *      -encodeToCommandBuffer:... uses coordinates local to the source and
 *      destination image textures. Consequently, the secondaryOffset and clipRect
 *      attached to this object will need to be updated using a global to
 *      local coordinate transform before -encodeToCommandBuffer:... is
 *      called.
 *
 *  @abstract   Determine the region of the source texture that will be read for a encode operation
 *  @param      destinationSize     The size of the full virtual destination image.
 *  @return     The area in the virtual source image that will be read.
 */
-(MPSRegion) secondarySourceRegionForDestinationSize: (MTLSize) destinationSize;



@end

#endif /* defined(_MetalPerformanceShaders_MSImageKernel_) */
