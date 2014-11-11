/*
 *  Geometry.h
 *  vImage_Framework
 *
 *  Copyright (c) 2002 Apple Computer. All rights reserved.
 *
 */


/*
 *
 *	This suite of functions allows the caller to rotate, resize and distort images. Resampling
 *	is currently done with a Lanczos kernel.
 *
 *	The 90 degree rotate function requires that the corresponding destination axes share the 
 *	same even/odd parity for size as the source buffer. Otherwise, the image may become uncentered
 *	by a half a pixel. For example if the input buffer has a width of 3 and a height of 4, and you rotate
 *	90 degrees, the destination buffer should have a even width (4 is even) and a odd height (3 is odd). 
 *	For a 180 degree rotate, the width would have to be odd and the height even. 
 *
 *	Set the vImageEdgeExtend flag if you wish to use the edge pixels of the image as the color of regions
 *	outside the input vImage_Buffer. In general, this is not a good idea, however if you are just resizing, 
 *	it will prevent the background color from bleeding into the edges of the image. 	
 *
 *	The kvImageLeaveAlphaUnchanged flag is ignored for this set of functions, since most of these 
 *	functions involve a high degree of resampling. It is not clear in most cases what the
 *	appropriate "unchanged" value would be to use.
 *
 */
 

#ifndef VIMAGE_GEOMETRY_H
#define VIMAGE_GEOMETRY_H

#include <vImage/vImage_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

//Rotation constants for use with Rotate_90_*
enum
{
    kRotate0DegreesClockwise = 0,
    kRotate90DegreesClockwise = 3,
    kRotate180DegreesClockwise = 2,
    kRotate270DegreesClockwise = 1,

    kRotate0DegreesCounterClockwise = 0,
    kRotate90DegreesCounterClockwise = 1,
    kRotate180DegreesCounterClockwise = 2,
    kRotate270DegreesCounterClockwise = 3
};


/*
 * High Level Geometry Functions
 * ----------------------------
 * vImage provides a set of high level geometry functions to do simple geometric transforms on an image. 
 * These are:
 *
 *	Rotate -- rotate the input image around a center point by any amount and write to a destination buffer.
 *	Scale  -- resize the input image to the size of the destination buffer
 *	Affine Transform -- Apply an affine transform to an image
 *
 * When calling the Rotate and Affine Transform functions, it is possible that some part of the output 
 * image may come from regions of the input image that are outside the original input image. In these cases,
 * the "revealed" pixels will be of the color provided in the backgroundColor parameter passed to the function,
 * unless kvImageEdgeExtend is passed, in which case it will be taken from the nearest edge pixel. 
 *
 * The Scaling function may need to read outside the edges of the input buffer to service the resampling kernel.
 * In this case the values of the edge pixels a replicated outward infinitely. This allows us to avoid having
 * the background color bleed into the edges of the image. If you wish to rescale part of an image and have the rest
 * of the image considered for this operation, use the Affine Transform for scaling. 
 *
 * Temporary Buffers
 * -----------------
 * The high level geometry functions cannot operate in place and cannot operate simply within the confines of the 
 * source and destination buffers. This is because they employ multipass algorithms that need to save 
 * intermediate pixel values between passes. The destination buffer may not be large enough to hold that
 * information or later passes may not operate correctly in place, meaning that additional storage is 
 * required. Temporary storage is required by the higher level Geometry operations: Rotate, Scale, 
 * and Affine Transform. 
 * 
 * Even though temporary storage is required by these functions, you may pass NULL for the pointer to
 * a temporary buffer. This may cause vImage to call malloc to allocate a buffer for you. It will 
 * be destroyed before the function returns to prevent a memory leak. This is a perfectly sensible thing
 * to do when the function is not called often and possibly blocking on a lock for a short period of time
 * is not a problem. (Malloc may block on a lock.)
 *
 * If you plan to call the function frequently over a relatively short period of time, or you need real time 
 * performance guarantees (which make locks a problem) then you should preallocate your own temporary 
 * working buffer for vImage to use and reuse that. This will avoid the per-call malloc overhead, helping 
 * to guarantee top performance. In addition, it avoids a problem caused by the fact that large 
 * (i.e. image sized) buffers allocated by malloc are usually allocated by the OS in a paged-out state. 
 * (They are not on disk. They do not physically exist until you touch the page, at which point they are 
 * allocated and zero filled on demand.) This means that as we touch each new 4k page we take an interrupt to zero fill 
 * the page, which would be nice to avoid. If you call the vImage function rarely, this is not worth worrying 
 * about, since whatever buffer you preallocate is likely to be paged out to disk by the VM system anyway. 
 * It is just on the 2nd and later calls in quick succession that this is a performance win, since we can 
 * avoid the paging activity.
 *
 * You may allocate the temporary buffer anywhere you like -- heap, global, stack, etc. The buffer should 
 * be at least the size returned by vImageGetMinimumGeometryTempBufferSize() for the source and destination buffers.
 * Be aware that the stack size limit is user configurable and in many cases may not be large enough.
 * The buffer should not be shared reentrantly between different threads in a multithreaded app, unless you
 * protect it with a mutual exclusion device such as a lock/mutex/etc. Otherwise two vImage functions may
 * overwrite each other and produce garbled image data. No information is kept in the temporary buffer 
 * between function calls. 
 *
 *  All four channel geometry functions (i.e. those that support ARGB8888, ARGB16U, ARGB16S or ARGBFFFF images) work equally 
 *  well on four channel images with other channel orderings such as RGBA or BGRA.  
 */

/*
 * vImageRotate_<fmt>
 * =================
 * vImageRotate_<fmt> is a convenience function to provide facile rotation of images about their center point. The operation can also be done with vImageWarp_<fmt>, or 
 * by using appropriate low level vImageHorizontal/VerticalShear_<fmt> interfaces. vImageWarp_<fmt> may be appropriate if you wish to rotate around a non-center point in
 * the image. vImageHorizontal/VerticalShear_<fmt> will provide the greatest detail in control, since it allows for alternative sampling methods, and also the opportunity to
 * control how tiling is done. This might allow for better cache utilization in cases where a format conversion (or other fast filter) is required either before or after
 * the scaling operation and you wish to incorporate it into your tiling design.
 *
 * To avoid artifacts in high frequency regions of the image, the data should be non-premultiplied, or at minimum have the same alpha over the entire image. For integer
 * formats with constant alpha < PIXEL_MAX, it is possible for result color values to be greater than alpha.  vImageClipToAlpha_<fmt> can be used to correct that problem.
 * Some other functions like vImageUnpremultiplyData_<fmt> will correct the problem as part of their operation, if they appear later in your image pipeline.
 * Otherwise, integer formats are clamped in the range [0,255] and can not experience modulo overflow problems. For floating-point formats, it is always possible to
 * produce out-of-gamut or greater than alpha results, most often in high-frequency regions of the image. Out-of-gamut results are often resolved when the floating-point
 * format is converted to an integer format in a later vImage call -- all conversions to integer format are clamped to the representable range. However, color values
 * greater than alpha will persist if the alpha is less than fully opaque, and can be fixed by vImageClipToAlpha_<fmt> as with the integer formats.
 * vImageUnpremultiplyData_<fmt> and vImagePremultiplyData_<fmt> are much, much faster than vImageRotate_<fmt> and typically only add a few percent to the overall cost 
 * of the filter.
 *
 * vImageRotate_<fmt>() does not work in place
 * The ARGB8888, ARGB16U, ARGB16S and ARGBFFFF functions work equally well on other channel orderings of 4-channel images, such as RGBA or BGRA.
 *
 * Acceptable flags are kvImageEdgeExtend, kvImageBackgroundColorFill, kvImageDoNotTile, kvImageHighQualityResampling, kvImageNoFlags. If no edging mode is passed, 
 * the edging mode is undefined. You may not pass both kvImageEdgeExtend and kvImageBackgroundColorFill. kvImageEdgeExtend will leave odd stripes in areas for which  
 * no corresponding source image pixel exists, corresponding to the value of the nearest edge pixel, for some value of "nearest". kvImageBackgroundColorFill is most 
 * commonly used. 
 */                                                                                                                                                                          

vImage_Error	vImageRotate_Planar8( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, float angleInRadians, Pixel_8 backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error	vImageRotate_PlanarF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, float angleInRadians, Pixel_F backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error	vImageRotate_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, float angleInRadians, Pixel_8888 backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error	vImageRotate_ARGB16U( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, float angleInRadians, Pixel_ARGB_16U backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
vImage_Error	vImageRotate_ARGB16S( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, float angleInRadians, Pixel_ARGB_16S backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
vImage_Error	vImageRotate_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, float angleInRadians, Pixel_FFFF backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*
 * vImageScale_<fmt>
 * =================
 * vImageScale_<fmt> is a convenience function to provide facile resizing of images. The operation can also be done with vImageWarp_<fmt>, or by using appropriate
 * low level vImageHorizontal/VerticalShear_<fmt> interfaces. vImageWarp_<fmt> may be appropriate if you wish to use an edging mode other than kvImageEdgeExtend.
 * vImageHorizontal/VerticalShear_<fmt> will provide the greatest detail in control, since it allows for alternative sampling methods, and also the opportunity to
 * control how tiling is done. This might allow for better cache utilization in cases where a format conversion (or other fast filter) is required either before or after
 * the scaling operation and you wish to incorporate it into your tiling design.
 *
 * To avoid artifacts in high frequency regions of the image, the data should be non-premultiplied, or at minimum have the same alpha over the entire image. For integer
 * formats with constant alpha < PIXEL_MAX, it is possible for result color values to be greater than alpha.  vImageClipToAlpha_<fmt> can be used to correct that problem.
 * Some other functions like vImageUnpremultiplyData_<fmt> will correct the problem as part of their operation, if they appear later in your image pipeline.
 * Otherwise, integer formats are clamped in the range [PIXEL_MIN,PIXEL_MAX] and can not experience modulo overflow problems. For floating-point formats, it is always possible to
 * produce out-of-gamut or greater than alpha results, most often in high-frequency regions of the image. Out-of-gamut results are often resolved when the floating-point
 * format is converted to an integer format in a later vImage call -- all conversions to integer format are clamped to the representable range. However, color values
 * greater than alpha will persist if the alpha is less than fully opaque, and can be fixed by vImageClipToAlpha_<fmt> as with the integer formats.
 * vImageUnpremultiplyData_<fmt> and vImagePremultiplyData_<fmt> are much, much faster than vImageScale_<fmt> and typically only add a few percent to the overall cost 
 * of the filter.
 *
 * vImageScale_<fmt>() does not work in place
 * The ARGB8888, ARGB16U, ARGB16S and ARGBFFFF functions work equally well on other channel orderings of 4-channel images, such as RGBA or BGRA.
 *
 * Acceptable flags are kvImageEdgeExtend, kvImageDoNotTile, kvImageHighQualityResampling, kvImageNoFlags. If no edging mode is passed, kvImageEdgeExtend is used.
 * Developers using vImageScale_<fmt> on MacOS X.3 should pass kvImageEdgeExtend in the flags field to avoid ringing artifacts at the edges of images
 */                                                                                                                                                                          
vImage_Error	vImageScale_Planar8( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error	vImageScale_Planar16S( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 );
vImage_Error	vImageScale_Planar16U( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 );
vImage_Error	vImageScale_PlanarF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error	vImageScale_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error	vImageScale_ARGB16U( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
vImage_Error	vImageScale_ARGB16S( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
vImage_Error	vImageScale_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*
 * vImageAffineWarp_<fmt>
 * ======================
 * vImageAffineWarp_<fmt> is a convenience function to provide facile affine transformation of images. The operation can also be done by using appropriate low level 
 * vImageHorizontal/VerticalShear_<fmt> interfaces. vImageHorizontal/VerticalShear_<fmt> will provide the greatest detail in control, since it allows for alternative 
 * sampling methods, and also the opportunity to control how tiling is done, possibly allowing for better cache utilization in cases where a format conversion (or 
 * other fast filter) is required either before or after the scaling operation and you wish to incorporate it into your tiling design. 
 *
 * To avoid artifacts in high frequency regions of the image, the data should be non-premultiplied, or at minimum have the same alpha over the entire image. For integer
 * formats with constant alpha < 255, it is possible for result color values to be greater than alpha.  vImageClipToAlpha_<fmt> can be used to correct that problem.
 * Some other functions like vImageUnpremultiplyData_<fmt> will correct the problem as part of their operation, if they appear later in your image pipeline.
 * Otherwise, integer formats are clamped in the range [PIXEL_MIN, PIXEL_MAX] and can not experience modulo overflow problems. For floating-point formats, it is always possible to
 * produce out-of-gamut or greater than alpha results, most often in high-frequency regions of the image. Out-of-gamut results are often resolved when the floating-point
 * format is converted to an integer format in a later vImage call -- all conversions to integer format are clamped to the representable range. However, color values
 * greater than alpha will persist if the alpha is less than fully opaque, and can be fixed by vImageClipToAlpha_<fmt> as with the integer formats.
 * vImageUnpremultiplyData_<fmt> and vImagePremultiplyData_<fmt> are much, much faster than vImageAffineWarp_<fmt> and typically only add a few percent to the overall cost 
 * of the filter.
 *
 * For the Affine Transform function, the coordinate space places the origin at the bottom left corner of the image. Positive movement in the X and Y direction moves you
 * right and up. Both source and destination images are assumed to place their bottom left hand corner at the origin.
 *	
 * vImageAffineWarp_<fmt>() does not work in place
 * The ARGB8888, ARGB16U, ARGB16S and ARGBFFFF functions work equally well on other channel orderings of 4-channel images, such as RGBA or BGRA.
 *
 * Acceptable flags are kvImageEdgeExtend, kvImageBackgroundColorFill, kvImageDoNotTile, kvImageHighQualityResampling, kvImageNoFlags. If no edging mode is passed, the edging 
 * mode is undefined. You may not pass both kvImageEdgeExtend and kvImageBackgroundColorFill. kvImageEdgeExtend will leave odd stripes in areas for which no corresponding source  
 * image pixel exists, corresponding to the value of the nearest edge pixel, for some value of "nearest". kvImageBackgroundColorFill is most commonly used, except when the result 
 * will be cropped to cover only regions present in the original image and no background color leakage into the edges of the result image are desired. 
 *
 * Versions of the API that use alternative formulations of the affine transform matrix follow immediately afterward. 
 */                                                                                                                                                                          
vImage_Error	vImageAffineWarp_Planar8( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, const vImage_AffineTransform *transform, Pixel_8 backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,4) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error	vImageAffineWarp_PlanarF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, const vImage_AffineTransform *transform, Pixel_F backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,4) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error	vImageAffineWarp_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, const vImage_AffineTransform *transform, Pixel_8888 backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,4) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error	vImageAffineWarp_ARGB16U( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, const vImage_AffineTransform *transform, Pixel_ARGB_16U backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,4) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
vImage_Error	vImageAffineWarp_ARGB16S( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, const vImage_AffineTransform *transform, Pixel_ARGB_16S backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,4) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
vImage_Error	vImageAffineWarp_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, const vImage_AffineTransform *transform, Pixel_FFFF backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,4) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

#if VIMAGE_AFFINETRANSFORM_DOUBLE_IS_AVAILABLE
    /* A single precision transformation matrix is often not enough. This one uses double precision. */
    vImage_Error	vImageAffineWarpD_Planar8( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, const vImage_AffineTransform_Double *transform, Pixel_8 backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,4) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_6_0 );
    vImage_Error	vImageAffineWarpD_PlanarF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, const vImage_AffineTransform_Double *transform, Pixel_F backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,4) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_6_0 );
    vImage_Error	vImageAffineWarpD_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, const vImage_AffineTransform_Double *transform, Pixel_8888 backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,4) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_6_0 );
    vImage_Error	vImageAffineWarpD_ARGB16U( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, const vImage_AffineTransform_Double *transform, Pixel_ARGB_16U backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,4) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
    vImage_Error	vImageAffineWarpD_ARGB16S( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, const vImage_AffineTransform_Double *transform, Pixel_ARGB_16S backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,4) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
    vImage_Error	vImageAffineWarpD_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, const vImage_AffineTransform_Double *transform, Pixel_FFFF backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,4) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_6_0 );
#endif

#if VIMAGE_CGAFFINETRANSFORM_IS_AVAILABLE
    /* Convenience Interfaces for working directly with CGAffineTransform, which changes size depending on whether we are LP64 or not. */
    vImage_Error	vImageAffineWarpCG_Planar8( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, const vImage_CGAffineTransform *transform, Pixel_8 backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,4) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_6_0 );
    vImage_Error	vImageAffineWarpCG_PlanarF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, const vImage_CGAffineTransform *transform, Pixel_F backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,4) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_6_0 );
    vImage_Error	vImageAffineWarpCG_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, const vImage_CGAffineTransform *transform, Pixel_8888 backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,4) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_6_0 );
    vImage_Error	vImageAffineWarpCG_ARGB16U( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, const vImage_CGAffineTransform *transform, Pixel_ARGB_16U backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,4) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
    vImage_Error	vImageAffineWarpCG_ARGB16S( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, const vImage_CGAffineTransform *transform, Pixel_ARGB_16S backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,4) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
    vImage_Error	vImageAffineWarpCG_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, const vImage_CGAffineTransform *transform, Pixel_FFFF backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,4) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_6_0 );
#endif


/* 
 * vImageGetMinimumGeometryTempBufferSize() returns the minimum size of a temporary buffer passed to any of the Rotate, Scale
 * or Affine Transform functions. The size is only dependent on the height and width of the two buffers, and the
 * number of bytes per pixel (the data format). The rowbytes and data fields are ignored. As long as the size
 * of the buffers doesn't change, the size returned by  GetMinimumTempBufferSize() will not change. 
 */
 
/* THIS FUNCTION IS DEPRECATED.
 * Use the kvImageGetTempBufferSize flag with the appropriate function, instead of using this API 
 * Simply pass the kvImageGetTempBufferSize flag in addition to all the regular parameters. The size will be returned in the  
 * vImage_Error result.  kvImageGetTempBufferSize is for MacOS X.4 and later. 
 */
size_t		vImageGetMinimumGeometryTempBufferSize( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags, size_t bytesPerPixel ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_BUT_DEPRECATED( __MAC_10_3, __MAC_10_4, __IPHONE_NA, __IPHONE_NA );

/*
 *	Low Level Geometry Functions
 *	----------------------------
 *
 *	vImage also provides a series of low level geometry functions that do simple, often 1-D transforms on images. 
 *	They are:
 *
 *		Reflect -- reflect an image across a  mirror plane at the center of the image in the x or y direction
 *		Shear --  shear and rescale an image in the x or y direction
 *		Rotate90 -- rotate an image by 0, 90, 180 or 270 degrees
 *
 *	The Reflect functions simply reflect images horizontally or vertically. Horizontal reflection inverts the image
 *	left to right as if seen from behind. Vertical reflection causes the image to appear upside down.
 *
 *  Acceptable flags are kvImageDoNotTile, kvImageNoFlags.
 *
 *  These functions do not work in place.
 *
 *  All four channel geometry functions (i.e. those that support ARGB8888, ARGB16U, ARGB16S or ARGBFFFF images) work equally well on four channel images 
 *  with other channel orderings such as RGBA or BGRA.  
 */

vImage_Error	vImageHorizontalReflect_Planar8( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error	vImageHorizontalReflect_Planar16U( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_6_0 );    
vImage_Error	vImageHorizontalReflect_PlanarF( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error	vImageHorizontalReflect_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error	vImageHorizontalReflect_ARGB16U( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
vImage_Error	vImageHorizontalReflect_ARGB16S( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
vImage_Error	vImageHorizontalReflect_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

vImage_Error	vImageVerticalReflect_Planar8( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error	vImageVerticalReflect_Planar16U( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_6_0 );
vImage_Error	vImageVerticalReflect_PlanarF( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error	vImageVerticalReflect_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error	vImageVerticalReflect_ARGB16U( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
vImage_Error	vImageVerticalReflect_ARGB16S( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
vImage_Error	vImageVerticalReflect_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*
 * 	The Rotate90 function does simple 0, 90, 180 or 270 degree rotation according to the value of a rotation constant
 *	passed to it. The images are rotated about their center. If the source and destination sizes do not match, parts 
 *	of the image may be cut off. Other parts may have no image, in which case the background color will be drawn there.
 *
 *	CAUTION: 90 and 270 degree rotation does not rotate about the true center of the image if the height of the source image  
 *	is an odd number of pixels and the width of the destination image an even number of pixels, or vice versa. This is also 
 *	true of the source width and destination height. In this case, you should use the High level rotate function for 90 or 
 *	270 rotates so that the resampling can be done to shift the image a half pixel for proper centering. It may be somewhat 
 *	faster to widen the destination image by 1 and use the low level shearing functions to resample the image at a a half pixel offset.
 *	For 0 and 180 degree rotates, if the source and destination buffers are a different size, the two heights must have matching
 *	even/oddness and the two widths must have matching even/oddness. Otherwise the image will be rotated and shifted a half pixel 
 *	away from the center. 
 *
 *	rotationConstant:	0 -- rotate 0 degrees (simply copy the data from src to dest)
 *				1 -- rotate 90 degrees counterclockwise
 *				2 -- rotate 180 degress
 *				3 -- rotate 270 degrees counterclockwise
 *
 *	backColor:	The color of the background. This color will be copied to any place where pixels are revealed because
 *			the input image does not completely cover the output image. 
 *
 *  Acceptable flags are kvImageDoNotTile, kvImageNoFlags.
 *
 *  These functions do not work in place.
 *
 *  All four channel geometry functions (i.e. those that support ARGB8888, ARGB16U, ARGB16S or ARGBFFFF images) work equally well on 
 *  four channel images with other channel orderings such as RGBA or BGRA.  
 */

vImage_Error	vImageRotate90_Planar8( const vImage_Buffer *src, const vImage_Buffer *dest, uint8_t rotationConstant, Pixel_8 backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error	vImageRotate90_Planar16U( const vImage_Buffer *src, const vImage_Buffer *dest, uint8_t rotationConstant, Pixel_16U backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_6_0 );
vImage_Error	vImageRotate90_PlanarF( const vImage_Buffer *src, const vImage_Buffer *dest, uint8_t rotationConstant, Pixel_F backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error	vImageRotate90_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, uint8_t rotationConstant, const Pixel_8888 backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,4) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error	vImageRotate90_ARGB16U( const vImage_Buffer *src, const vImage_Buffer *dest, uint8_t rotationConstant, const Pixel_ARGB_16U backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,4) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
vImage_Error	vImageRotate90_ARGB16S( const vImage_Buffer *src, const vImage_Buffer *dest, uint8_t rotationConstant, const Pixel_ARGB_16S backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,4) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
vImage_Error	vImageRotate90_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, uint8_t rotationConstant, const Pixel_FFFF backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,4) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
 
/*
 *	The Shearing functions use resampling to rescale a image and offset it to fractional pixel offsets. 
 *	The functions actually shear, resize in one dimension and translate. All of it is done with fractional
 *	pixel precision. The shear slope is set using the shearSlope parameter. They are intended to be identical
 *      to the off diagonal components of the AffineWarp matrix for the same shear (i.e. at 1,0 or 0,1). The 
 *      xTranslate or yTranslate variable may be used to adjust the position of the destination image in the x and 
 *      y directions. Scaling (making the image larger or smaller in one dimension) is done by adjusting the resampling kernel.
 *
 *  All four channel geometry functions (i.e. those that support ARGB8888, ARGB16U, ARGB16S or ARGBFFFF images) work equally well on
 *  four channel images with other channel orderings such as RGBA or BGRA.
 *
 *  These functions do not work in place.
 *
 *  Acceptable flags are kvImageEdgeExtend, kvImageBackgroundColor, kvImageDoNotTile, kvImageNoFlags.
 *  Only one of kvImageEdgeExtend or kvImageBackgroundColor may be used. If none is used then the edging mode is undefined and results may be unpredictable.
 *
 *  The ResamplingFilter is created using vImageNewResamplingFilter or vImageNewResamplingFilterForFunctionUsingBuffer. The latter
 *  gives more precise control over where the memory is allocated and which filter function is used, at the expense of having to 
 *  define / setup the same.
 */

vImage_Error	vImageHorizontalShear_Planar8( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, float xTranslate, float shearSlope, ResamplingFilter filter, Pixel_8 backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error	vImageHorizontalShear_Planar16S( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, float xTranslate, float shearSlope, ResamplingFilter filter, Pixel_16S backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 );
vImage_Error	vImageHorizontalShear_Planar16U( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, float xTranslate, float shearSlope, ResamplingFilter filter, Pixel_16U backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 );
vImage_Error	vImageHorizontalShear_PlanarF( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, float xTranslate, float shearSlope, ResamplingFilter filter, Pixel_F backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error	vImageHorizontalShear_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, float xTranslate, float shearSlope, ResamplingFilter filter, Pixel_8888 backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error	vImageHorizontalShear_ARGB16U( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, float xTranslate, float shearSlope, ResamplingFilter filter, Pixel_ARGB_16U backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
vImage_Error	vImageHorizontalShear_ARGB16S( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, float xTranslate, float shearSlope, ResamplingFilter filter, Pixel_ARGB_16S backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
vImage_Error	vImageHorizontalShear_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, float xTranslate, float shearSlope, ResamplingFilter filter, Pixel_FFFF backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

vImage_Error	vImageVerticalShear_Planar8( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, float yTranslate, float shearSlope, ResamplingFilter filter, Pixel_8 backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error	vImageVerticalShear_Planar16S( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, float yTranslate, float shearSlope, ResamplingFilter filter, Pixel_16S backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 );
vImage_Error	vImageVerticalShear_Planar16U( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, float yTranslate, float shearSlope, ResamplingFilter filter, Pixel_16U backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 );
vImage_Error	vImageVerticalShear_PlanarF( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, float yTranslate, float shearSlope, ResamplingFilter filter, Pixel_F backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error	vImageVerticalShear_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, float yTranslate, float shearSlope, ResamplingFilter filter,  Pixel_8888 backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error	vImageVerticalShear_ARGB16U( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, float yTranslate, float shearSlope, ResamplingFilter filter,  Pixel_ARGB_16U backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
vImage_Error	vImageVerticalShear_ARGB16S( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, float yTranslate, float shearSlope, ResamplingFilter filter,  Pixel_ARGB_16S backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
vImage_Error	vImageVerticalShear_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, float yTranslate, float shearSlope, ResamplingFilter filter, Pixel_FFFF backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/* Versions of shear functions that take coordinates in double precision */
vImage_Error	vImageHorizontalShearD_Planar8( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, double xTranslate, double shearSlope, ResamplingFilter filter, Pixel_8 backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_6_0 );
vImage_Error	vImageHorizontalShearD_PlanarF( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, double xTranslate, double shearSlope, ResamplingFilter filter, Pixel_F backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_6_0 );
vImage_Error	vImageHorizontalShearD_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, double xTranslate, double shearSlope, ResamplingFilter filter, Pixel_8888 backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_6_0 );
vImage_Error	vImageHorizontalShearD_ARGB16U( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, double xTranslate, double shearSlope, ResamplingFilter filter, Pixel_ARGB_16U backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
vImage_Error	vImageHorizontalShearD_ARGB16S( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, double xTranslate, double shearSlope, ResamplingFilter filter, Pixel_ARGB_16S backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
vImage_Error	vImageHorizontalShearD_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, double xTranslate, double shearSlope, ResamplingFilter filter, Pixel_FFFF backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_6_0 );

vImage_Error	vImageVerticalShearD_Planar8( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, double yTranslate, double shearSlope, ResamplingFilter filter, Pixel_8 backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_6_0 );
vImage_Error	vImageVerticalShearD_PlanarF( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, double yTranslate, double shearSlope, ResamplingFilter filter, Pixel_F backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_6_0 );
vImage_Error	vImageVerticalShearD_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, double yTranslate, double shearSlope, ResamplingFilter filter,  Pixel_8888 backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_6_0 );
vImage_Error	vImageVerticalShearD_ARGB16U( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, double yTranslate, double shearSlope, ResamplingFilter filter,  Pixel_ARGB_16U backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
vImage_Error	vImageVerticalShearD_ARGB16S( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, double yTranslate, double shearSlope, ResamplingFilter filter,  Pixel_ARGB_16S backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
vImage_Error	vImageVerticalShearD_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, double yTranslate, double shearSlope, ResamplingFilter filter, Pixel_FFFF backColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_6_0 );

 
/*
 *	The shearing functions use a resampling filter for their work. Before you call these functions you must 
 *	create a new filter. The filter must be remade for different scaling factors, but may be reused in different
 *	function calls if the scaling factor is the same. 
 *
 * 	For general purpose work, use NewResamplingFilter() to create a resampling filter. It currently uses 
 *	either Lanczos3 or Lanczos5 filter, depending on whether the kvImageHighQualityResampling bit is set in the flags field. 
 *	What filter is used is subject to change. 
 *
 *		ResamplingFilter kernel = NewResamplingFilter( theScale, kvImageHighQualityResampling );
 *
 *	Use DestroyResamplingFilter() when you are done with the filter to return the memory it uses to the heap.
 *
 *	The scale parameter sets the level of rescaling to be done. A value of 1.0f leaves the image at its 
 *	original size. 2.0f will magnify in one direction to make the image twice as wide / tall. 0.5f will 
 *	make it half as wide / tall. Any float is allowed, including negative values, which will have the effect
 *	of flipping the image along that axis. Scaling will happen relative to the left or bottom edge of the image. 
 *
 *	Set the kvImageEdgeExtend bit in the flags field if you would like the image buffer edges extended infinitely
 *	rather than use the backColor value. This is useful when you do not wish a background color to bleed into
 *	the edges of your image. This is generally only useful when the shear angle is 0.
 *
 */

ResamplingFilter	vImageNewResamplingFilter( float scale, vImage_Flags flags )    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
void			vImageDestroyResamplingFilter( ResamplingFilter filter )    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*
 *	vImageNewResamplingFilter and vImageDestroyResamplingFilter are merely convenience functions to make
 *	the common case of the default resampling filter into a heap allocated buffer easier for you.
 *
 *	If you would like to use your own special purpose resampling filter or need to restrict your use of malloc, 
 *	you may instead call NewResamplingFilterForFunctionUsingBuffer(), which creates a filter for a specific 
 *	resampling filter function that you provide in the form of a simple y = f(x) function, and writes it into a buffer
 *	that you provide. This function writes the kernel values into a preallocated kernel buffer that you provide. The 
 *	kernel buffer should be at least the size of the kernel data, which is given by vImageGetResamplingKernelSize.
 *
 */
 
vImage_Error	vImageNewResamplingFilterForFunctionUsingBuffer( ResamplingFilter filter, 
                                                        float scale, 
                                                        void (*kernelFunc)( const float *xArray, float *yArray, unsigned long count, void *userData ), 
                                                        float kernelWidth, 
                                                        void *userData,
                                                        vImage_Flags flags ) VIMAGE_NON_NULL(1) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

size_t		vImageGetResamplingFilterSize(  float scale, 
                                                void (*kernelFunc)( const float *xArray, float *yArray, unsigned long count, void *userData ),
                                                float kernelWidth, 
                                                vImage_Flags flags ) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*
 *	The scale parameter is the amount to enlarge or reduce the output image. It is the same meaning
 *	as for the generic resampling kernel.
 *
 *	The kernelFunc defines the shape of the resampling kernel. Here is a sample kernelFunc that does 
 *	linear interpolation:
 *
 *		void MyLinearInterpolationFilterFunc( const float *xArray, float *yArray, int count, void *userData )
 *		{
 *			int i;
 *			float sum = 0.0f;
 *
 *			//Calculate kernel values
 *			for( i = 0; i < count; i++ )
 *			{
 *				float unscaledResult = 1.0f - fabs( xArray[i] );	//LERP
 *				yArray[i] = unscaledResult;
 *				sum += unscaledResult;		
 *			}
 *
 *			//Make sure the kernel values sum to 1.0. You can use some other value here. 
 *			//Values other than 1.0 will cause the image to lighten or darken.
 *			sum = 1.0f / sum;
 *			for( i = 0; i < count; i++ )
 *				yArray[i] *= sum;
 *			
 *		}
 *
 *	This specifies the tent line shape centered around 0.0f that defines a linear interpolation kernel. 
 *	The array of values you will be asked to provide are the entire resampling window for a single pixel.
 *	The x values are pixel positions relative to the result, and the y values are where you should put
 *	the kernel values for those positions. The x values will range from -kernelWidth to kernelWidth.
 *
 *	The array format is used for efficiency, and also to give you the opportunity to make sure the kernel 
 *	adds up to 1.0 or some other desired value. Making sure that the kernel values add up to 1.0 will
 *	prevent interference patterns from emerging in the image. Since the sampling kernel function itself is 
 *	sampled during the process of pairing kernel values against sampled pixel data, the sampled kernel data 
 *	does not always integrate to the same value that the parent function does, so usually we must normalize 
 *	it to prevent interference/moiree patterns from to emerging in the image as the pixels in the input buffer 
 *	drift in and out of phase with those in the output buffer. Sums less than 1.0f will cause the image to 
 *	darken. Gain values greater than 1.0 may cause significant clipping for integer pixel data. Kernel values 
 *	are clipped at approximately +- 2.0 for all integer data. If your filter function values exceed +- 2.0, then
 *	you will need to use the floating point data format to avoid overflow. 
 *
 *	If you pass NULL for the kernelFunc, vImage will use its default resampling kernel. You can control 
 *	whether the high quality resampling kernel is used or not by setting the kvImageHighQualityResampling 
 *	bit in the flags field. This allows you to use the default resampling kernel in your own buffer. If you do
 *	not pass NULL for the kernelFunc, the kernelFunc and your userData parameter must be valid for the lifetime
 *	of the ResamplingKernel. 
 *
 *	The kernelWidth parameter controls the limiting values of x, when creating the new kernel. A kernelWidth 
 *	of 1.0 would allow input samples between -1.0 and 1.0 pixels away from the destination pixel to influence 
 *	the result. For Lanczos3, we would use a kernelWidth of 3.0f, because the Lanczos3 function is defined 
 *	over the range -3.0f to 3.0f. If your function is only defined over part of the range -x...x, then have 
 *	your function return zero for the rest of the function. The computational cost of the shearing functions 
 *	is proportional to the kernelWidth. 
 *
 *	The userData field is passed back unchanged to your kernelFunc when it is called. 
 *
 *	The only flag honored by this function in this release is kvImageHighQualityResampling, which is only
 *	used if NULL is passed for the kernelFunc to decide whether to use the normal or high quality default
 *	resampling filter. Except in this case, you should in general pass kvImageNoFlags in the flags field 
 * 	to avoid conflicting with future implementations where flags may be used. 
 *
 *	Do not use DestroyResamplingKernel() to free the memory used by kernels created with NewResamplingKernelForFunction().
 *	Since you are responsible for allocating that buffer, you are also responsible for destroying it, using the matching
 *	free function. 
 *
 *	Do not call vImageNewResamplingKernelForFunctionUsingBuffer() on a buffer created with vImageNewResamplingKernel().
 *	The buffer sizes may be different. You must use vImageGetResamplingKernelSize() to find out the new buffer size,
 *	allocate a buffer yourself using something like malloc(), then call vImageNewResamplingKernelForFunctionUsingBuffer().
 */


/*
 *  vImageGetSamplingFilterExtent
 *
 *  returns the maximum sampling radius for the resampling filter.  This is the maximum distance from any pixel 
 *  that the filter will look either horizontally or vertically, depending on whether vImageHorizontalShear or 
 *  vImageVerticalShear is used.  It is analogous to kernelWidth in vImageNewResamplingFilterForFunctionUsingBuffer,
 *  but might be slightly larger to allow for extra slop when dealing with sub-pixel coordinates during resampling.
 *
 *      filter      a valid ResamplingFilter
 *      flags       the flags you intend to pass to vImage{Horizontal/Vertical}Shear_<fmt>.  
 */
vImagePixelCount    vImageGetResamplingFilterExtent( ResamplingFilter filter, vImage_Flags flags )  VIMAGE_NON_NULL(1)  __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
    
#ifdef __cplusplus
}
#endif

#endif
