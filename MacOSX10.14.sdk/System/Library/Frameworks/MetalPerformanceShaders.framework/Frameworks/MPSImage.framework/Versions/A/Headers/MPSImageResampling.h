/*!
 *  @header MPSImageResampling.h
 *  @framework MetalPerformanceShaders
 *
 *  @copyright Copyright (c) 2015 Apple Inc. All rights reserved.
 *  @abstract  Resampling filters for MetalPerformanceShaders
 */

#ifndef MPS_MPSImageResampling_h
#define MPS_MPSImageResampling_h

#include <MPSImage/MPSImageKernel.h>


/*!
 *  @class      MPSImageScale
 *  @abstract   Resize an image and / or change its aspect ratio
 *  @discussion The MPSImageScale filter can be used to resample an existing image
 *              using a different sampling frequency in each dimension. This can be
 *              used to enlarge or reduce the size of an image, or change the aspect
 *              ratio of an image.  
 *
 *              The resample methods supported are:
 *                    Bilinear
 *                    Bicubcic
 *                    Lanczos
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface  MPSImageScale : MPSUnaryImageKernel

/*
 * You must use one of the sub-classes of MPSImageScale
 */
-(nonnull instancetype) initWithDevice: (nonnull id<MTLDevice>)device NS_DESIGNATED_INITIALIZER;

/*! @property   scaleTransform
 *  @abstract   An optional transform that describes how to scale and translate the source image
 *  @discussion If the scaleTransform is NULL, then the MPSImageLanczosScale filter will
 *              rescale the image so that the source image fits exactly into the destination
 *              texture.  If the transform is not NULL, then the transform is used for determining
 *              how to map the source image to the destination. Default: NULL
 *
 *              When the scaleTransform is set to non-NULL, the values pointed to by the new
 *              scaleTransform are copied to object storage, and the pointer is updated to point
 *              to internal storage. Do not attempt to free it.  You may free your copy of
 *              the MPSScaleTransform as soon as the property set operation is complete.
 *
 *              When calculating a scaleTransform, use the limits of the bounding box for the intended
 *              source region of interest and the destination clipRect. Adjustments for pixel center
 *              coordinates are handled internally to the function.  For example,
 *              the scale transform to convert the entire source image to the entire destination image
 *              size (clipRect = MPSRectNoClip) would be:
 *
 *              @code
 *                  scaleTransform.scaleX = (double) dest.width / source.width;
 *                  scaleTransform.scaleY = (double) dest.height / source.height;
 *                  scaleTransform.translateX = scaleTransform.translateY = 0.0;
 *              @endcode
 *
 *              The translation parameters allow you to adjust the region of the source image used
 *              to create the destination image. They are in destination coordinates. To place the
 *              top left corner of the destination clipRect to represent the position {x,y} in source
 *              coordinates, we solve for the translation based on the standard scale matrix operation
 *              for each axis:
 *
 *              @code
 *                  dest_position = source_position * scale + translation;
 *                  translation = dest_position - source_position * scale;
 *              @endcode
 *
 *              For the top left corner of the clipRect, the dest_position is considered to be {0,0}.
 *              This gives us a translation of:
 *
 *              @code
 *                  scaleTransform.translateX = -source_origin.x * scaleTransform.scaleX;
 *                  scaleTransform.translateY = -source_origin.y * scaleTransform.scaleY;
 *              @endcode
 *
 *              One would typically use non-zero translations to do tiling, or provide a resized
 *              view into a internal segment of an image.
 *
 *              Changing the Lanczos scale factor may trigger recalculation of signficant state internal
 *              to the object when the filter is encoded to the command buffer. The scale factor is
 *              scaleTransform->scaleX,Y, or the ratio of source and destination image sizes if
 *              scaleTransform is NULL. Reuse a MPSImageLanczosScale object for frequently used scalings
 *              to avoid redundantly recreating expensive resampling state.
 */
@property (readwrite, nonatomic, nullable) const MPSScaleTransform *scaleTransform;


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

@end


/*!
 *  @class      MPSImageLanczosScale
 *  @abstract   Resize an image and / or change its aspect ratio
 *  @discussion The MPSImageLanczosScale filter can be used to resample an existing image
 *              using a different sampling frequency in each dimension. This can be
 *              used to enlarge or reduce the size of an image, or change the aspect
 *              ratio of an image.  The filter uses a Lanczos resampling algorithm
 *              which typically produces better quality for photographs, but is slower
 *              than linear sampling using the GPU texture units. Lanczos downsampling 
 *              does not require a low pass filter to be applied before it is used. 
 *              Because the resampling function has negative lobes, Lanczos can result 
 *              in ringing near sharp edges, making it less suitable for vector art.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(9.0), tvos(9.0))
@interface  MPSImageLanczosScale : MPSImageScale

-(nonnull instancetype) initWithDevice: (nonnull id<MTLDevice>)device NS_DESIGNATED_INITIALIZER;

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

@end


/*!
 *  @class      MPSImageBilinearScale
 *  @abstract   Resize an image and / or change its aspect ratio
 *  @discussion The MPSImageBilinearScale filter can be used to resample an existing image
 *              using a bilinear filter. This is typically used to reduce the size of an image.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface  MPSImageBilinearScale : MPSImageScale

-(nonnull instancetype) initWithDevice: (nonnull id<MTLDevice>)device NS_DESIGNATED_INITIALIZER;

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

@end


#endif /* MPS_MSImageResampling_h */
