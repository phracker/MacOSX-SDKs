/*!
 *  @header Alpha.h
 *  vImage Framework
 *
 *  @copyright Copyright (c) 2003-2015 by Apple Inc. All rights reserved.
 *
 *  See vImage/vImage.h for more on how to better view the headerdoc documentation for functions declared herein.
 *
 *  @discussion
 *  Alpha compositing is the practice of blending one image into another using a coverage component, commonly called
 *  alpha, to indicate how opaque each pixel is.  A value of 1.0 (or 255 if an 8-bit image) indicates the
 *  pixel is fully opaque. A value of 0 indicates that it is fully transparent. Values in beetween establish a linear scale
 *  of partial opacity. Alpha can be used to slowly fade one image into another. Some images such as icons, have opqaue
 *  portions and transparent portions. A blending operation based on alpha is required to draw these over a background 
 *  image.
 *
 *  In its simplest form, an alpha blend is a linear interpolation between pixel of two images:
 * <pre>@textblock
 *      float: new color =  top color * alpha + (1-alpha) * bottom color
 *      8-bit: new color =  (top color * alpha + (255-alpha) * bottom color + 127) / 255
 * @/textblock </pre>
 *  However, these formulations are a bit too simplistic because they do not account for the possibility that
 *  the bottom layer may have some transparency to it too. One subtlety of adding transparency to the bottom image
 *  is that the result image has an alpha component to it too that should be divided out:
 * <pre>@textblock
 *      float: new alpha =  top alpha + (1-top alpha) * bottom alpha
 *      float: new color =  (top color * top alpha + (1- top alpha) * bottom color * bottom alpha ) / new alpha
 *
 *      8-bit: new alpha =  top alpha + ((255-top alpha) * bottom alpha + 127)/255
 *      8-bit: new color =  (255 * top color * top alpha + (255- top alpha) * bottom color * bottom alpha + (255*255)/2) / (255 * 255 * new alpha)
 * @/textblock </pre>
 * As might be imagined, this extra complication may become costly.  At the cost of a small amount of accuracy in non-opaque regions
 * of the image, it is common to leave the alpha multiplied into the image. This avoids the division at the end. In addition,
 * if the result is used in another blend, we don't have to multiply the alpha back in at that stage, which simplifies things
 * all around. Such images with the alpha channel multiplied into the other channels are called pre-multiplied images.
 *
 * This gives us the following for premultiplied alpha blends:
 * <pre>@textblock
 *      float: new alpha               = top alpha +               (1 - top alpha) * bottom alpha
 *      float: new premultiplied color = top premultiplied color + (1 - top alpha) * bottom premultiplied color
 *
 *      8-bit: new alpha               =  top alpha +               ((255 - top alpha) * bottom alpha + 127)/255
 *      8-bit: new premultiplied color =  top premultiplied color + ((255 - top alpha) * bottom premultiplied color + 127)/255
 * @/textblock </pre>
 *
 * Some images are known to be fully opaque. For such images, alpha is 1.0 (or 255) for all the pixels, and consequently
 * do not require any computation to be done to interconvert between premultiplied and non-premultiplied states. That is,
 * since x/1 = x  and x*1 = x, they are non-premultiplied and premultiplied at the same time, and can serve in either 
 * capacity as needed.  Because of this special status, CoreGraphics labels them kCGImageAlphaNoneSkipFirst/Last. vImage
 * does similar things in vImage_Utilities.h. Labelling opaque buffers as such enables cheaper alpha blending and will frequently
 * will let us avoid blending all-together as a simple copy operation will do.
 *
 * This header provides compositing (blending) operations for both premultiplied and non-premultiplied images, functions 
 * to premultiply or unpremultiply images, and some functions to make sure that the color channel values do not exceed
 * the alpha value, which sometimes can happen after a convolution, morphological or resampling operation.
 *
 *	These alpha compositing functions assume that the floating point range is 0.0 (black) to 1.0 (full intensity color).
 *	While values outside these ranges do function correctly (you can have 110% intensity color or -50% color, for example),
 *	the calculation is done assuming 1.0 represents full intensity color, and 0.0 represents the absence of color. If these
 *	assumptions are not correct, then the calculation will produce incorrect results. Apple does not currently provide
 *	alpha compositing functions that work with any floating point range in vImage.
 *
 *	8 bit functionality assumes that 0 is no color, and 255 is full color. 8 bit functions do saturated clipping before
 *	converting from internal precision back to 8 bits to make sure that modulo overflow does not occur. The internal 
 *  calculation is done with higher precision.
 *
 *  @ignorefuncmacro VIMAGE_NON_NULL
 */

#ifndef VIMAGE_ALPHA_H
#define VIMAGE_ALPHA_H	

#include <vImage/vImage_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @functiongroup Alpha Blend
 * @discussion The Alpha Blend functions composite two non-premultiplied images together to produce a non-premultiplied result.
 *             They are in general more expensive than their premultiplied counterparts, because the alpha has to be 
 *             divided out of the result at the end.
 */
    
/*!
 * @function vImageAlphaBlend_Planar8
 * @abstract Composite two non-premultiplied planar 8-bit images, to produce a non-premultiplied result.
 * @discussion
 *
 *      For each color channel:
 * <pre>@textblock
 *          float destColor = (  srcTopColor * srcTopAlpha + (1.0 - srcTopAlpha) * srcBottomAlpha * srcBottomColor ) / alpha
 * @/textblock </pre>
 *      alpha (the new alpha value for that pixel) is calculated as:
 * <pre>@textblock
 *          float alpha =  srcTopAlpha + (1.0 - srcTopAlpha) * srcBottomAlpha
 * @/textblock </pre>
 *      For planar data, you need to calculate alpha yourself ahead of time and provide that as an argument to this function.
 *      This can be done using: 
 * <pre>@textblock
 *          vImagePremultipliedAlphaBlend_Planar8( srcTopAlpha, srcTopAlpha, srcBottomAlpha, alpha, kvImageNoFlags );
 * @/textblock </pre>
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 *      The ARGB versions work for all 4 channel 8-bit / channel image formats with alpha first in memory.
 *
 * @param srcTop        The color image that is composited on top of the bottom image
 * @param srcTopAlpha   The alpha channel corresponding to the srcTop image
 * @param srcBottom     The color image that is below the srcTop image, into which it is blended
 * @param srcBottomAlpha The alpha channel corresponding to the srcBottom image
 * @param alpha         The alpha channel for the destination image. You need to calculate this ahead of time as:
 * <pre>@textblock
 *          vImagePremultipliedAlphaBlend_Planar8( srcTopAlpha, srcTopAlpha, srcBottomAlpha, alpha, kvImageNoFlags );
 * @/textblock </pre>
 * @oaram dest          The non-premultiplied result will be written here.
 *
 * @param flags         The following flags are allowed:
 *  <pre>@textblock
 *          kvImageNoFlags          Default operation
 *
 *          kvImageDoNotTile        Disables internal multithreading. This may be useful if you are writing your own multithreaded tiling engine.
 *  @/textblock</pre>
 * @result              The following result codes may be returned:
 *  <pre>@textblock
 *          kvImageNoError                      Success!
 *          
 *          kvImageRoiLargerThanInputBuffer     The destination buffer must be no larger than srcTop, srcBottom, srcTopAlpha, srcBottomAlpha and alpha.
 *  @/textblock</pre>
 */
vImage_Error	vImageAlphaBlend_Planar8( const vImage_Buffer *srcTop, const vImage_Buffer *srcTopAlpha, const vImage_Buffer *srcBottom, const vImage_Buffer *srcBottomAlpha, const vImage_Buffer *alpha, const vImage_Buffer *dest, vImage_Flags flags )  VIMAGE_NON_NULL(1,2,3,4,5,6)  __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*!
 * @function vImageAlphaBlend_PlanarF
 * @abstract Composite two non-premultiplied planar floating-point images, to produce a non-premultiplied result.
 * @discussion
 *
 *      For each color channel:
 * <pre>@textblock
 *          float destColor = (  srcTopColor * srcTopAlpha + (1.0 - srcTopAlpha) * srcBottomAlpha * srcBottomColor ) / alpha
 * @/textblock </pre>
 *      alpha (the new alpha value for that pixel) is calculated as:
 * <pre>@textblock
 *          float alpha =  srcTopAlpha + (1.0 - srcTopAlpha) * srcBottomAlpha
 * @/textblock </pre>
 *      For planar data, you need to calculate alpha yourself ahead of time and provide that as an argument to this function.
 *      This can be done using:
 * <pre>@textblock
 *          vImagePremultipliedAlphaBlend_PlanarF( srcTopAlpha, srcTopAlpha, srcBottomAlpha, alpha, kvImageNoFlags );
 * @/textblock </pre>
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 *      The ARGB versions work for all 4 channel 8-bit / channel image formats with alpha first in memory.
 *
 * @param srcTop        The color image that is composited on top of the bottom image
 * @param srcTopAlpha   The alpha channel corresponding to the srcTop image
 * @param srcBottom     The color image that is below the srcTop image, into which it is blended
 * @param srcBottomAlpha The alpha channel corresponding to the srcBottom image
 * @param alpha         The alpha channel for the destination image. You need to calculate this ahead of time as:
 * <pre>@textblock
 *                          vImagePremultipliedAlphaBlend_PlanarF( srcTopAlpha, srcTopAlpha, srcBottomAlpha, alpha, kvImageNoFlags );
 * @/textblock </pre>
 * @oaram dest          The non-premultiplied result will be written here.
 *
 * @param flags         The following flags are allowed:
 *  <pre>@textblock
 *          kvImageNoFlags          Default operation
 *
 *          kvImageDoNotTile        Disables internal multithreading. This may be useful if you are writing your own multithreaded tiling engine.
 *  @/textblock</pre>
 * @result              The following result codes may be returned:
 *  <pre>@textblock
 *          kvImageNoError                      Success!
 *
 *          kvImageRoiLargerThanInputBuffer     The destination buffer must be no larger than srcTop, srcBottom, srcTopAlpha, srcBottomAlpha and alpha.
 *  @/textblock</pre>
 */
    
vImage_Error	vImageAlphaBlend_PlanarF( const vImage_Buffer *srcTop, const vImage_Buffer *srcTopAlpha, const vImage_Buffer *srcBottom, const vImage_Buffer *srcBottomAlpha, const vImage_Buffer *alpha, const vImage_Buffer *dest, vImage_Flags flags )  VIMAGE_NON_NULL(1,2,3,4,5,6)  __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*!
 * @function vImageAlphaBlend_ARGB8888
 * @abstract Composite two non-premultiplied ARGB8888 images, to produce a non-premultiplied result.
 * @discussion
 *
 *      For each color channel:
 * <pre>@textblock
 *          float destColor = (  srcTopColor * srcTopAlpha + (1.0 - srcTopAlpha) * srcBottomAlpha * srcBottomColor ) / alpha
 * @/textblock </pre>
 *      alpha (the new alpha value for that pixel) is calculated as:
 * <pre>@textblock
 *          float alpha =  srcTopAlpha + (1.0 - srcTopAlpha) * srcBottomAlpha
 * @/textblock </pre>
 *
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 *      The ARGB versions work for all 4 channel 8-bit / channel image formats with alpha first in memory.
 *
 * @param srcTop        The image that is composited on top of the bottom image. The alpha channel must appear first.
 * @param srcBottom     The image that is below the srcTop image, into which it is blended. The alpha channel must appear first.
 * @oaram dest          The non-premultiplied result will be written here.
 *
 * @param flags         The following flags are allowed:
 *  <pre>@textblock
 *          kvImageNoFlags          Default operation
 *
 *          kvImageDoNotTile        Disables internal multithreading. This may be useful if you are writing your own multithreaded tiling engine.
 *  @/textblock</pre>
 * @result              The following result codes may be returned:
 *  <pre>@textblock
 *          kvImageNoError                      Success!
 *
 *          kvImageRoiLargerThanInputBuffer     The destination buffer must be no larger than srcTop, srcBottom, srcTopAlpha, srcBottomAlpha and alpha.
 *  @/textblock</pre>
 */
vImage_Error	vImageAlphaBlend_ARGB8888( const vImage_Buffer *srcTop, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3)   __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*!
 * @function vImageAlphaBlend_ARGBFFFF
 * @abstract Composite two non-premultiplied ARGBFFFF images, to produce a non-premultiplied result.
 * @discussion
 *
 *      For each color channel:
 * <pre>@textblock
 *          float destColor = (  srcTopColor * srcTopAlpha + (1.0 - srcTopAlpha) * srcBottomAlpha * srcBottomColor ) / alpha
 * @/textblock </pre>
 *      alpha (the new alpha value for that pixel) is calculated as:
 * <pre>@textblock
 *          float alpha =  srcTopAlpha + (1.0 - srcTopAlpha) * srcBottomAlpha
 * @/textblock </pre>
 *
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 *      The ARGB versions work for all 4 channel float / channel image formats with alpha first in memory.
 *
 * @param srcTop        The image that is composited on top of the bottom image. The alpha channel must appear first.
 * @param srcBottom     The image that is below the srcTop image, into which it is blended. The alpha channel must appear first.
 * @oaram dest          The non-premultiplied result will be written here.
 *
 * @param flags         The following flags are allowed:
 *  <pre>@textblock
 *          kvImageNoFlags          Default operation
 *
 *          kvImageDoNotTile        Disables internal multithreading. This may be useful if you are writing your own multithreaded tiling engine.
 *  @/textblock</pre>
 * @result              The following result codes may be returned:
 *  <pre>@textblock
 *          kvImageNoError                      Success!
 *
 *          kvImageRoiLargerThanInputBuffer     The destination buffer must be no larger than srcTop, srcBottom, srcTopAlpha, srcBottomAlpha and alpha.
 *  @/textblock</pre>
 */
vImage_Error	vImageAlphaBlend_ARGBFFFF( const vImage_Buffer *srcTop, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3)  __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*!
 * @functiongroup Alpha Blend (Premultiplied)
 * @discussion  Premultiplied alpha blends composite two premultiplied images to produce a premultiplied result.
 */
    
/*!
 * @function vImagePremultipliedAlphaBlend_Planar8
 * @abstract blend two premultiplied Planar8 images to produce a premultiplied Planar8 result.
 * @discussion
 *      For each color channel:
 * <pre>@textblock
 *          uint8_t destColor = srcTopColor  + ((255 - srcTopAlpha) * srcBottomColor + 127)/255;
 * @/textblock</pre>
 *      Similarly, the output alpha channel (the new alpha value for that pixel) can be calculated as:
 * <pre>@textblock
 *          uint8_t alpha =  srcTopAlpha + ((255 - srcTopAlpha) * srcBottomAlpha + 127)/255;
 * @/textblock</pre>
 *      The alpha values are presumed to be normalized over the range [0, 255].
 *
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 * @param srcTop            The top image
 * @param srcTopAlpha       The coverage component for the top image (alpha)
 * @param srcBottom         The bottom image
 * @param dest              The result image is written here. This buffer must be preallocated before the function is called.
 * <pre>@textblock
 *      kvImageNoFlags      Default operation
 *
 *      kvImageDoNotTile    Disable internal multithreading. You might want to do that if you are calling
 *                          this in the context of your own multithreaded tiling engine.
 * @/textblock </pre>
 *
 * @result  The following error codes may occur:
 * <pre>@textblock
 *          kvImageNoError                      Success.
 *
 *          kvImageRoiLargerThanInputBuffer     The height and width of the result must be less than or equal to each of the input buffers.
 * @/textblock</pre>
 *
 */
vImage_Error	vImagePremultipliedAlphaBlend_Planar8( const vImage_Buffer *srcTop,
                                                      const vImage_Buffer *srcTopAlpha,
                                                      const vImage_Buffer *srcBottom,
                                                      const vImage_Buffer *dest,
                                                      vImage_Flags flags )
                                                      VIMAGE_NON_NULL(1,2,3,4)
                                                      __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*!
 * @function vImagePremultipliedAlphaBlend_PlanarF
 * @abstract blend two premultiplied PlanarF images to produce a premultiplied PlanarF result.
 * @discussion
 *      For each color channel:
 * <pre>@textblock
 *          float destColor = srcTopColor  + (1.0 - srcTopAlpha) * srcBottomColor;
 * @/textblock</pre>
 *      Similarly, the output alpha channel (the new alpha value for that pixel) can be calculated as:
 * <pre>@textblock
 *          float alpha =  srcTopAlpha + (1.0 - srcTopAlpha) * srcBottomAlpha
 * @/textblock</pre>
 *      The alpha values are presumed to be normalized over the range [0.0f, 1.0f].
 *
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 * @param srcTop            The top image
 * @param srcTopAlpha       The coverage component for the top image (alpha)
 * @param srcBottom         The bottom image
 * @param dest              The result image is written here. This buffer must be preallocated before the function is called.
 * <pre>@textblock
 *      kvImageNoFlags      Default operation
 *
 *      kvImageDoNotTile    Disable internal multithreading. You might want to do that if you are calling
 *                          this in the context of your own multithreaded tiling engine.
 * @/textblock </pre>
 *
 * @result  The following error codes may occur:
 * <pre>@textblock
 *          kvImageNoError                      Success.
 *
 *          kvImageRoiLargerThanInputBuffer     The height and width of the result must be less than or equal to each of the input buffers.
 * @/textblock</pre>
 *
 */

vImage_Error	vImagePremultipliedAlphaBlend_PlanarF( const vImage_Buffer *srcTop,
                                                      const vImage_Buffer *srcTopAlpha,
                                                      const vImage_Buffer *srcBottom,
                                                      const vImage_Buffer *dest,
                                                      vImage_Flags flags )
                                                      VIMAGE_NON_NULL(1,2,3,4)
                                                      __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*!
 * @function vImagePremultipliedAlphaBlend_ARGB8888
 * @abstract blend two premultiplied ARGB8888 images to produce a premultiplied ARGB8888 result.
 * @discussion
 *      For each color channel:
 * <pre>@textblock
 *          uint8_t destColor = srcTopColor  + ((255 - srcTopAlpha) * srcBottomColor + 127)/255;
 * @/textblock</pre>
 *      Similarly, the output alpha channel (the new alpha value for that pixel) can be calculated as:
 * <pre>@textblock
 *          uint8_t alpha =  srcTopAlpha + ((255 - srcTopAlpha) * srcBottomAlpha + 127)/255;
 * @/textblock</pre>
 *      The alpha values are presumed to be normalized over the range [0, 255].
 *
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 *      The function will work for all 4 channel 8-bit / channel image formats with alpha first in memory, not just ARGB.
 *
 * @param srcTop            The top image
 * @param srcBottom         The bottom image
 * @param dest              The result image is written here. This buffer must be preallocated before the function is called.
 * @param flags             The following flags may be used:
 * <pre>@textblock
 *      kvImageNoFlags      Default operation
 *
 *      kvImageDoNotTile    Disable internal multithreading. You might want to do that if you are calling 
 *                          this in the context of your own multithreaded tiling engine.
 * @/textblock </pre>
 *
 * @result  The following error codes may occur:
 * <pre>@textblock
 *          kvImageNoError                      Success.
 *
 *          kvImageRoiLargerThanInputBuffer     The height and width of the result must be less than or equal to each of the input buffers.
 * @/textblock</pre>
 *
 */
vImage_Error	vImagePremultipliedAlphaBlend_ARGB8888( const vImage_Buffer *srcTop, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3)   __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*!
 * @function vImagePremultipliedAlphaBlend_BGRA8888
 * @abstract blend two premultiplied BGRA8888 images to produce a premultiplied BGRA8888 result.
 * @discussion
 *      For each color channel:
 * <pre>@textblock
 *          uint8_t destColor = srcTopColor  + ((255 - srcTopAlpha) * srcBottomColor + 127)/255;
 * @/textblock</pre>
 *      Similarly, the output alpha channel (the new alpha value for that pixel) can be calculated as:
 * <pre>@textblock
 *          uint8_t alpha =  srcTopAlpha + ((255 - srcTopAlpha) * srcBottomAlpha + 127)/255;
 * @/textblock</pre>
 *      The alpha values are presumed to be normalized over the range [0, 255].
 *
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 *      The function will work for all 4 channel 8-bit / channel image formats with alpha last in memory, not just BGRA.
 *      Also available as vImagePremultipliedAlphaBlend_RGBA8888().
 *
 * @param srcTop            The top image
 * @param srcBottom         The bottom image
 * @param dest              The result image is written here. This buffer must be preallocated before the function is called.
 * @param flags             The following flags may be used:
 * <pre>@textblock
 *      kvImageNoFlags      Default operation
 *
 *      kvImageDoNotTile    Disable internal multithreading. You might want to do that if you are calling
 *                          this in the context of your own multithreaded tiling engine.
 * @/textblock </pre>
 *
 * @result  The following error codes may occur:
 * <pre>@textblock
 *          kvImageNoError                      Success.
 *
 *          kvImageRoiLargerThanInputBuffer     The height and width of the result must be less than or equal to each of the input buffers.
 * @/textblock</pre>
 *
 */
vImage_Error	vImagePremultipliedAlphaBlend_BGRA8888( const vImage_Buffer *srcTop, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3)   __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_5_0 );
#define         vImagePremultipliedAlphaBlend_RGBA8888( _srcTop, _srcBottom, _dest, _flags )    vImagePremultipliedAlphaBlend_BGRA8888((_srcTop), (_srcBottom), (_dest), (_flags))
    
/*!
 * @function vImagePremultipliedAlphaBlend_ARGBFFFF
 * @abstract blend two premultiplied ARGBFFFF images to produce a premultiplied ARGBFFFF result.
 * @discussion
 * <pre>@textblock
 *          float destColor = srcTopColor  + (1.0 - srcTopAlpha) * srcBottomColor;
 * @/textblock</pre>
 *      Similarly, the output alpha channel (the new alpha value for that pixel) can be calculated as:
 * <pre>@textblock
 *          float alpha =  srcTopAlpha + (1.0 - srcTopAlpha) * srcBottomAlpha
 * @/textblock</pre>
 *      The alpha values are presumed to be normalized over the range [0.0f, 1.0f].
 *
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 *      The function will work for all 4 channel float / channel image formats with alpha first in memory, not just ARGB.
 *
 * @param srcTop            The top image
 * @param srcBottom         The bottom image
 * @param dest              The result image is written here. This buffer must be preallocated before the function is called.
 * @param flags             The following flags may be used:
 * <pre>@textblock
 *      kvImageNoFlags      Default operation
 *
 *      kvImageDoNotTile    Disable internal multithreading. You might want to do that if you are calling
 *                          this in the context of your own multithreaded tiling engine.
 * @/textblock </pre>
 *
 * @result  The following error codes may occur:
 * <pre>@textblock
 *          kvImageNoError                      Success.
 *
 *          kvImageRoiLargerThanInputBuffer     The height and width of the result must be less than or equal to each of the input buffers.
 * @/textblock</pre>
 *
 */
vImage_Error	vImagePremultipliedAlphaBlend_ARGBFFFF( const vImage_Buffer *srcTop, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3)   __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*!
 * @function vImagePremultipliedAlphaBlend_BGRAFFFF
 * @abstract blend two premultiplied ARGBFFFF images to produce a premultiplied BGRAFFFF result.
 * @discussion
 * <pre>@textblock
 *          float destColor = srcTopColor  + (1.0 - srcTopAlpha) * srcBottomColor;
 * @/textblock</pre>
 *      Similarly, the output alpha channel (the new alpha value for that pixel) can be calculated as:
 * <pre>@textblock
 *          float alpha =  srcTopAlpha + (1.0 - srcTopAlpha) * srcBottomAlpha
 * @/textblock</pre>
 *      The alpha values are presumed to be normalized over the range [0.0f, 1.0f].
 *
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 *      The function will work for all 4 channel float / channel image formats with alpha first in memory, not just BGRA.
 *      Also available as vImagePremultipliedAlphaBlend_RGBAFFFF.
 *
 * @param srcTop            The top image
 * @param srcBottom         The bottom image
 * @param dest              The result image is written here. This buffer must be preallocated before the function is called.
 * @param flags             The following flags may be used:
 * <pre>@textblock
 *      kvImageNoFlags      Default operation
 *
 *      kvImageDoNotTile    Disable internal multithreading. You might want to do that if you are calling
 *                          this in the context of your own multithreaded tiling engine.
 * @/textblock </pre>
 *
 * @result  The following error codes may occur:
 * <pre>@textblock
 *          kvImageNoError                      Success.
 *
 *          kvImageRoiLargerThanInputBuffer     The height and width of the result must be less than or equal to each of the input buffers.
 * @/textblock</pre>
 *
 */
vImage_Error	vImagePremultipliedAlphaBlend_BGRAFFFF( const vImage_Buffer *srcTop, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3)   __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_5_0 );
#define         vImagePremultipliedAlphaBlend_RGBAFFFF( _srcTop, _srcBottom, _dest, _flags )    vImagePremultipliedAlphaBlend_BGRAFFFF((_srcTop), (_srcBottom), (_dest), (_flags))

/*!
 * @function vImagePremultipliedAlphaBlendWithPermute_ARGB8888
 * @abstract Reorder the channels of the top 8-bit 4 channel premultiplied image, blend into a bottom premultiplied ARGB8888 image.
 * @discussion
 *  This function does 3 things.
 * <pre>@textblock
 *      1. Changes the order of channels of srcTop according to permuteMap.
 *      2. A premultiplied alpha compositing.
 *      3. Set destA to 0xFF when makeDestAlphaOpaque is true.
 *
 *      permuteMap[i] = 0, 1, 2, or 3 to specify how we permute each channel in srcTop.
 *
 *      permuteMap[0] tells which channel in srcTop XXXX8888 will be used as A.
 *      permuteMap[1] tells which channel in srcTop XXXX8888 will be used as R.
 *      permuteMap[2] tells which channel in srcTop XXXX8888 will be used as G.
 *      permuteMap[3] tells which channel in srcTop XXXX8888 will be used as B.
 * @/textblock</pre>
 *
 *  This permuteMap lets us to cover any channel order for the top and bottom images.
 *  For example,
 * <pre>@textblock
 *      PremultipliedAlphaBlend(srcTop_ARGB8888, srcBottom_ARGB8888) -> dest_ARGB8888
 *                     will be covered by permuteMap[4] = {0, 1, 2, 3}
 *
 *      PremultipliedAlphaBlend(srcTop_RGBA8888, srcBottom_ARGB8888) -> dest_ARGB8888
 *                     will be covered by permuteMap[4] = {3, 0, 1, 2}
 *
 *      PremultipliedAlphaBlend(srcTop_ABGR8888, srcBottom_ARGB8888) -> dest_ARGB8888
 *                     will be covered by permuteMap[4] = {0, 3, 2, 1}
 *
 *      PremultipliedAlphaBlend(srcTop_BGRA8888, srcBottom_ARGB8888) -> dest_ARGB8888
 *                     will be covered by permuteMap[4] = {3, 2, 1, 0}
 * @/textblock</pre>
 *
 *  srcBottom will have the same pixel format (ARGB8888) as dest.
 *
 *
 *  The per-pixel operation is:
 *
 * <pre>@textblock
 *  uint8_t *srcTop, *srcBottom, *dest;
 *  uint8_t srcTopA, srcTopR, srcTopG, srcTopB;
 *  uint8_t srcBottomA, srcBottomR, srcBottomG, srcBottomB;
 *  uint8_t destA, destR, destG, destB;
 *
 *  srcTopA = srcTop[ permuteMap[0] ];
 *  srcTopR = srcTop[ permuteMap[1] ];
 *  srcTopG = srcTop[ permuteMap[2] ];
 *  srcTopB = srcTop[ permuteMap[3] ];
 *
 *  srcBottomA = srcBottom[ 0 ];
 *  srcBottomR = srcBottom[ 1 ];
 *  srcBottomG = srcBottom[ 2 ];
 *  srcBottomB = srcBottom[ 3 ];
 *
 *  destR = (srcTopR * 255 + (255 - srcTopA) * srcBottomR + 127) / 255;
 *  destG = (srcTopG * 255 + (255 - srcTopA) * srcBottomG + 127) / 255;
 *  destB = (srcTopB * 255 + (255 - srcTopA) * srcBottomB + 127) / 255;
 *
 *  if(makeDestAlphaOpaque)
 *  {
 *
 *      dest[0] = 0xFF;
 *      dest[1] = destR;
 *      dest[2] = destG;
 *      dest[3] = destB;
 *  }
 *  else
 *  {
 *      destA = (srcTopA * 255 + (255 - srcTopA) * srcBottomA + 127) / 255;
 *
 *      dest[0] = destA;
 *      dest[1] = destR;
 *      dest[2] = destG;
 *      dest[3] = destB;
 *  }
 * @/textblock</pre>
 *
 *  This function can work in place.
 *
 *  @param srcTop       A pointer to vImage_Buffer that references 8-bit XXXX interleaved source top image.
 *  @param srcBottom    A pointer to vImage_Buffer that references 8-bit ARGB interleaved source bottom image.
 *  @param dest         A pointer to vImage_Buffer that references 8-bit ARGB interleaved destination image.
 *  @param permuteMap   Values that can be used to switch the channel order of the source top image.
 *  @param makeDestAlphaOpaque  A boolean to set destA into 0xFF when it's true.
 *  @param flags        The following flags are allowed:
 * <pre>@textblock
 *      kvImageGetTempBufferSize    Returns 0. Does no work.
 *      kvImageDoNotTile            Disables internal multithreading, if any.
 * @/textblock</pre>
 * @return The following error codes may be returned:
 * <pre>@textblock
 *      kvImageNoError                  Is returned when there was no error.
 *      kvImageRoiLargerThanInputBuffer The destination buffers are larger than the source buffer.
 *      kvImageBufferSizeMismatch       Is returned when there is a mismatch in width & height of srcTop and srcBottom.
 *      kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 *      kvImageInvalidParameter         Is returned when the values in permuteMap[i] is not one of 0, 1, 2, or 3.
 * @/textblock</pre>
 *
 */
vImage_Error vImagePremultipliedAlphaBlendWithPermute_ARGB8888(const vImage_Buffer *srcTop,
                                                               const vImage_Buffer *srcBottom,
                                                               const vImage_Buffer *dest,
                                                               const uint8_t permuteMap[4],
                                                               bool makeDestAlphaOpaque,
                                                               vImage_Flags flags )
                                                               VIMAGE_NON_NULL(1,2,3,4)
                                                               __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );



/*!
 * @function vImagePremultipliedAlphaBlendWithPermute_RGBA8888
 * @abstract Reorder the channels of the top 8-bit 4 channel premultiplied image, blend into a bottom premultiplied RGBA8888 image.
 * @discussion
 *  This function does 3 things.
 * <pre>@textblock
 *      1. Changes the order of channels of srcTop according to permuteMap.
 *      2. A premultiplied alpha compositing.
 *      3. Set destA to 0xFF when makeDestAlphaOpaque is true.
 *
 *      permuteMap[i] = 0, 1, 2, or 3 to specify how we permute each channel in srcTop.
 *
 *      permuteMap[0] tells which channel in srcTop XXXX8888 will be used as A.
 *      permuteMap[1] tells which channel in srcTop XXXX8888 will be used as R.
 *      permuteMap[2] tells which channel in srcTop XXXX8888 will be used as G.
 *      permuteMap[3] tells which channel in srcTop XXXX8888 will be used as B.
 * @/textblock</pre>
 *
 *  This permuteMap lets us to cover any channel order for the top and bottom images.
 *  For example,
 * <pre>@textblock
 *      PremultipliedAlphaBlend(srcTop_RGBA8888, srcBottom_RGBA8888) -> dest_RGBA8888
 *                     will be covered by permuteMap[4] = {0, 1, 2, 3}
 *
 *      PremultipliedAlphaBlend(srcTop_ARGB8888, srcBottom_RGBA8888) -> dest_RGBA8888
 *                     will be covered by permuteMap[4] = {1, 2, 3, 0}
 *
 *      PremultipliedAlphaBlend(srcTop_ABGR8888, srcBottom_RGBA8888) -> dest_RGBA8888
 *                     will be covered by permuteMap[4] = {3, 2, 1, 0}
 *
 *      PremultipliedAlphaBlend(srcTop_BGRA8888, srcBottom_RGBA8888) -> dest_RGBA8888
 *                     will be covered by permuteMap[4] = {2, 1, 0, 3}
 * @/textblock</pre>
 *
 *  srcBottom will have the same pixel format (RGBA8888) as dest.
 *
 *
 *  The per-pixel operation is:
 *
 * <pre>@textblock
 *  uint8_t *srcTop, *srcBottom, *dest;
 *  uint8_t srcTopA, srcTopR, srcTopG, srcTopB;
 *  uint8_t srcBottomA, srcBottomR, srcBottomG, srcBottomB;
 *  uint8_t destA, destR, destG, destB;
 *
 *  srcTopR = srcTop[ permuteMap[0] ];
 *  srcTopG = srcTop[ permuteMap[1] ];
 *  srcTopB = srcTop[ permuteMap[2] ];
 *  srcTopA = srcTop[ permuteMap[3] ];
 *
 *  srcBottomR = srcBottom[ 0 ];
 *  srcBottomG = srcBottom[ 1 ];
 *  srcBottomB = srcBottom[ 2 ];
 *  srcBottomA = srcBottom[ 3 ];
 *
 *  destR = (srcTopR * 255 + (255 - srcTopA) * srcBottomR + 127) / 255;
 *  destG = (srcTopG * 255 + (255 - srcTopA) * srcBottomG + 127) / 255;
 *  destB = (srcTopB * 255 + (255 - srcTopA) * srcBottomB + 127) / 255;
 *
 *  if(makeDestAlphaOpaque)
 *  {
 *
 *      dest[0] = 0xFF;
 *      dest[1] = destR;
 *      dest[2] = destG;
 *      dest[3] = destB;
 *  }
 *  else
 *  {
 *      destA = (srcTopA * 255 + (255 - srcTopA) * srcBottomA + 127) / 255;
 *
 *      dest[0] = destA;
 *      dest[1] = destR;
 *      dest[2] = destG;
 *      dest[3] = destB;
 *  }
 * @/textblock</pre>
 *
 *  This function can work in place.
 *
 *  @param srcTop       A pointer to vImage_Buffer that references 8-bit XXXX interleaved source top image.
 *  @param srcBottom    A pointer to vImage_Buffer that references 8-bit RGBA interleaved source bottom image.
 *  @param dest         A pointer to vImage_Buffer that references 8-bit RGBA interleaved destination image.
 *  @param permuteMap   Values that can be used to switch the channel order of the source top image.
 *  @param makeDestAlphaOpaque  A boolean to set destA into 0xFF when it's true.
 *  @param flags        The following flags are allowed:
 * <pre>@textblock
 *      kvImageGetTempBufferSize    Returns 0. Does no work.
 *      kvImageDoNotTile            Disables internal multithreading, if any.
 * @/textblock</pre>
 * @return The following error codes may be returned:
 * <pre>@textblock
 *      kvImageNoError                  Is returned when there was no error.
 *      kvImageRoiLargerThanInputBuffer The destination buffers are larger than the source buffer.
 *      kvImageBufferSizeMismatch       Is returned when there is a mismatch in width & height of srcTop and srcBottom.
 *      kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 *      kvImageInvalidParameter         Is returned when the values in permuteMap[i] is not one of 0, 1, 2, or 3.
 * @/textblock</pre>
 *
 */
vImage_Error vImagePremultipliedAlphaBlendWithPermute_RGBA8888(const vImage_Buffer *srcTop, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, const uint8_t permuteMap[4], bool makeDestAlphaOpaque, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,4) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );

    
/*!
 *  @functiongroup Alpha Blend (Premultiplied, other blend modes)
 *  @discussion These alternative blend modes correspond to the blend modes required for SVG 
 *              (http://www.w3.org/TR/SVG/filters.html, see feBlend)
 */
    
/*!
 * @function vImagePremultipliedAlphaBlendMultiply_RGBA8888
 * @abstract blend two premultiplied RGBA8888 images using the Multiply blend mode to produce a premultiplied RGBA8888 result.
 * @discussion
 *      For each color channel:
 * <pre>@textblock
 *          uint8_t destColor =((255 -    srcTopAlpha) * srcBottomColor +
 *                              (255 - srcBottomAlpha) * srcTopColor + 
 *                               srcTopColor * srcBottomColor + 127)/255;
 * @/textblock</pre>
 *      The output alpha channel (the new alpha value for that pixel) can be calculated as:
 * <pre>@textblock
 *          uint8_t alpha =  srcTopAlpha + ((255 - srcTopAlpha) * srcBottomAlpha + 127)/255;
 * @/textblock</pre>
 *      The alpha values are presumed to be normalized over the range [0, 255].
 *
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 *      The function will work for all 4 channel 8-bit / channel image formats with alpha last in memory, not just RGBA.
 *      This function corresponds to the multiply blend mode in feBlend in the SVG standard. http://www.w3.org/TR/SVG/filters.html)
 *
 * @param srcTop            The top image
 * @param srcBottom         The bottom image
 * @param dest              The result image is written here. This buffer must be preallocated before the function is called.
 * @param flags             The following flags may be used:
 * <pre>@textblock
 *      kvImageNoFlags      Default operation
 *
 *      kvImageDoNotTile    Disable internal multithreading. You might want to do that if you are calling
 *                          this in the context of your own multithreaded tiling engine.
 * @/textblock </pre>
 *
 * @result  The following error codes may occur:
 * <pre>@textblock
 *          kvImageNoError                      Success.
 *
 *          kvImageRoiLargerThanInputBuffer     The height and width of the result must be less than or equal to each of the input buffers.
 * @/textblock</pre>
 *
 */
vImage_Error	vImagePremultipliedAlphaBlendMultiply_RGBA8888( const vImage_Buffer *srcTop, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3) __OSX_AVAILABLE_STARTING( __MAC_10_11, __IPHONE_9_0 );

/*!
 * @function vImagePremultipliedAlphaBlendScreen_RGBA8888
 * @abstract blend two premultiplied RGBA8888 images using the Screen blend mode to produce a premultiplied RGBA8888 result.
 * @discussion
 *      For each color channel:
 * <pre>@textblock
 *          uint8_t destColor = CLAMP( srcTopColor + srcBottomcolor - (srcTopColor * srcBottomColor + 127)/255, 0, 255);
 * @/textblock</pre>
 *      The output alpha channel (the new alpha value for that pixel) can be calculated as:
 * <pre>@textblock
 *          uint8_t alpha =  srcTopAlpha + ((255 - srcTopAlpha) * srcBottomAlpha + 127)/255;
 * @/textblock</pre>
 *      The alpha values are presumed to be normalized over the range [0, 255].
 *
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 *      The function will work for all 4 channel 8-bit / channel image formats with alpha last in memory, not just RGBA.
 *      This function corresponds to the screen blend mode in feBlend in the SVG standard. http://www.w3.org/TR/SVG/filters.html)
 *
 * @param srcTop            The top image
 * @param srcBottom         The bottom image
 * @param dest              The result image is written here. This buffer must be preallocated before the function is called.
 * @param flags             The following flags may be used:
 * <pre>@textblock
 *      kvImageNoFlags      Default operation
 *
 *      kvImageDoNotTile    Disable internal multithreading. You might want to do that if you are calling
 *                          this in the context of your own multithreaded tiling engine.
 * @/textblock </pre>
 *
 * @result  The following error codes may occur:
 * <pre>@textblock
 *          kvImageNoError                      Success.
 *
 *          kvImageRoiLargerThanInputBuffer     The height and width of the result must be less than or equal to each of the input buffers.
 * @/textblock</pre>
 *
 */
vImage_Error	vImagePremultipliedAlphaBlendScreen_RGBA8888( const vImage_Buffer *srcTop, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3) __OSX_AVAILABLE_STARTING( __MAC_10_11, __IPHONE_9_0 );

/*!
 * @function vImagePremultipliedAlphaBlendDarken_RGBA8888
 * @abstract blend two premultiplied RGBA8888 images using the Darken blend mode to produce a premultiplied RGBA8888 result.
 * @discussion
 *      For each color channel:
 * <pre>@textblock
 *          uint8_t destColor = MIN( topColor +    ((255 - srcTopAlpha) *  srcBotomColor + 127) / 255,
 *                                   bottomColor + ((255 - srcBottomAlpha) * srcTopColor + 127) / 255);
 * @/textblock</pre>
 *      The output alpha channel (the new alpha value for that pixel) can be calculated as:
 * <pre>@textblock
 *          uint8_t alpha =  srcTopAlpha + ((255 - srcTopAlpha) * srcBottomAlpha + 127)/255;
 * @/textblock</pre>
 *      The alpha values are presumed to be normalized over the range [0, 255].
 *
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 *      The function will work for all 4 channel 8-bit / channel image formats with alpha last in memory, not just RGBA.
 *      This function corresponds to the darken blend mode in feBlend in the SVG standard. http://www.w3.org/TR/SVG/filters.html)
 *
 * @param srcTop            The top image
 * @param srcBottom         The bottom image
 * @param dest              The result image is written here. This buffer must be preallocated before the function is called.
 * @param flags             The following flags may be used:
 * <pre>@textblock
 *      kvImageNoFlags      Default operation
 *
 *      kvImageDoNotTile    Disable internal multithreading. You might want to do that if you are calling
 *                          this in the context of your own multithreaded tiling engine.
 * @/textblock </pre>
 *
 * @result  The following error codes may occur:
 * <pre>@textblock
 *          kvImageNoError                      Success.
 *
 *          kvImageRoiLargerThanInputBuffer     The height and width of the result must be less than or equal to each of the input buffers.
 * @/textblock</pre>
 *
 */
vImage_Error	vImagePremultipliedAlphaBlendDarken_RGBA8888( const vImage_Buffer *srcTop, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3) __OSX_AVAILABLE_STARTING( __MAC_10_11, __IPHONE_9_0 );

/*!
 * @function vImagePremultipliedAlphaBlendLighten_RGBA8888
 * @abstract blend two premultiplied RGBA8888 images using the Lighten blend mode to produce a premultiplied RGBA8888 result.
 * @discussion
 *      For each color channel:
 * <pre>@textblock
 *          uint8_t destColor = MAX( topColor +    ((255 - srcTopAlpha) *  srcBotomColor + 127) / 255,
 *                                   bottomColor + ((255 - srcBottomAlpha) * srcTopColor + 127) / 255);
 * @/textblock</pre>
 *      The output alpha channel (the new alpha value for that pixel) can be calculated as:
 * <pre>@textblock
 *          uint8_t alpha =  srcTopAlpha + ((255 - srcTopAlpha) * srcBottomAlpha + 127)/255;
 * @/textblock</pre>
 *      The alpha values are presumed to be normalized over the range [0, 255].
 *
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 *      The function will work for all 4 channel 8-bit / channel image formats with alpha last in memory, not just RGBA.
 *      This function corresponds to the lighten blend mode in feBlend in the SVG standard. http://www.w3.org/TR/SVG/filters.html)
 *
 * @param srcTop            The top image
 * @param srcBottom         The bottom image
 * @param dest              The result image is written here. This buffer must be preallocated before the function is called.
 * @param flags             The following flags may be used:
 * <pre>@textblock
 *      kvImageNoFlags      Default operation
 *
 *      kvImageDoNotTile    Disable internal multithreading. You might want to do that if you are calling
 *                          this in the context of your own multithreaded tiling engine.
 * @/textblock </pre>
 *
 * @result  The following error codes may occur:
 * <pre>@textblock
 *          kvImageNoError                      Success.
 *
 *          kvImageRoiLargerThanInputBuffer     The height and width of the result must be less than or equal to each of the input buffers.
 * @/textblock</pre>
 */
vImage_Error	vImagePremultipliedAlphaBlendLighten_RGBA8888( const vImage_Buffer *srcTop, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3) __OSX_AVAILABLE_STARTING( __MAC_10_11, __IPHONE_9_0 );


    
    
/*!
 *  @functiongroup Premultiply Data
 *  @discussion  Multiply a non-premultiplied (normal) image with its
 *               alpha channel to produce a premultiplied image.
 */
    
/*!
 *  @function vImagePremultiplyData_Planar8
 *  @abstract Multiply a Planar8 color channel by its corresponding alpha
 *  @discussion
 *  This function multiplies color channels by the alpha channel.  
 *  <pre>@textblock
 *      For each color channel:
 *
 *          uint8_t destColor = (src * alpha + 127) / 255;
 *
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *  @/textblock </pre>
 *
 *  @param src      The color data to multiply with alpha
 *  @param alpha    The alpha data to multiply against src
 *  @param dest     A preallocated vImage_Buffer where the results are written
 *  @param flags    The following flags are allowed:
 *  <pre>@textblock
 *          kvImageNoFlags                      Default operation
 *
 *          kvImageDoNotTile                    Turn off internal multithreading. This might be useful if you are already  multithreading
 *                                              the work in your own tiling engine.
 *  @/textblock </pre>
 *  @result         The following result codes may occur:
 *  <pre>@textblock
 *          kvImageNoError                      Success.
 *
 *          kvImageRoiLargerThanInputBuffer     dest->width and dest->height must be less than or equal to corresponding 
 *                                              dimensions in src and alpha
 *  @/textblock</pre>
 */
vImage_Error	vImagePremultiplyData_Planar8( const vImage_Buffer *src, const vImage_Buffer *alpha, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3)   __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*!
 *  @function vImagePremultiplyData_PlanarF
 *  @abstract Multiply a PlanarF color channel by its corresponding alpha
 *  @discussion
 *  This function multiplies color channels by the alpha channel.
 *  <pre>@textblock
 *      For each color channel:
 *
 *          float destColor = src * alpha;
 *
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *  @/textblock </pre>
 *
 *  @param src      The color data to multiply with alpha
 *  @param alpha    The alpha data to multiply against src
 *  @param dest     A preallocated vImage_Buffer where the results are written
 *  @param flags    The following flags are allowed:
 *  <pre>@textblock
 *          kvImageNoFlags                      Default operation
 *
 *          kvImageDoNotTile                    Turn off internal multithreading. This might be useful if you are already  multithreading
 *                                              the work in your own tiling engine.
 *  @/textblock </pre>
 *  @result         The following result codes may occur:
 *  <pre>@textblock
 *          kvImageNoError                      Success.
 *
 *          kvImageRoiLargerThanInputBuffer     dest->width and dest->height must be less than or equal to corresponding
 *                                              dimensions in src and alpha
 *  @/textblock</pre>
 */
vImage_Error	vImagePremultiplyData_PlanarF( const vImage_Buffer *src, const vImage_Buffer *alpha, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3)   __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*!
 *  @function vImagePremultiplyData_ARGB8888
 *  @abstract Multiply a ARGB8888 color channel by its corresponding alpha
 *  @discussion
 *  This function multiplies color channels by the alpha channel.
 *  <pre>@textblock
 *      For each color channel:
 *
 *          uint8_t destColor = (src * alpha + 127) / 255;
 *          uint8_t destAlpha = alpha;
 *
 *      This function can work in place provided the following are true:
 *          If src overlaps with dest, src->data must be equal to dest->data
 *          If src also has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *                  (It is not necessary to pass kvImageDoNotTile if src and dest do not overlap.)
 *  @/textblock </pre>
 *
 *      This function will for all 4 channel 8-bit / channel image formats with alpha first in memory.
 *      It does not have to be ARGB.
 *
 *  @param src      The color data to multiply with alpha
 *  @param dest     A preallocated vImage_Buffer where the results are written
 *  @param flags    The following flags are allowed:
 *  <pre>@textblock
 *          kvImageNoFlags                      Default operation
 *
 *          kvImageDoNotTile                    Turn off internal multithreading. This might be useful if you are already multithreading
 *                                              the work in your own tiling engine.
 *  @/textblock </pre>
 *  @result         The following result codes may occur:
 *  <pre>@textblock
 *          kvImageNoError                      Success.
 *
 *          kvImageRoiLargerThanInputBuffer     dest->width and dest->height must be less than or equal to corresponding
 *                                              dimensions in src and alpha
 *  @/textblock</pre>
 */
vImage_Error	vImagePremultiplyData_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)   __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*!
 *  @function vImagePremultiplyData_ARGBFFFF
 *  @abstract Multiply a ARGBFFFF color channel by its corresponding alpha
 *  @discussion
 *  This function multiplies color channels by the alpha channel.
 *  <pre>@textblock
 *      For each color channel:
 *
 *          float destColor = src * alpha;
 *          float destAlpha = alpha;
 *
 *      This function can work in place provided the following are true:
 *          If src overlaps with dest, src->data must be equal to dest->data
 *          If src also has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *                  (It is not necessary to pass kvImageDoNotTile if src and dest do not overlap.)
 *  @/textblock </pre>
 *
 *      This function will for all 4 channel float / channel image formats with alpha first in memory.
 *      It does not have to be ARGB.
 *
 *  @param src      The color data to multiply with alpha
 *  @param dest     A preallocated vImage_Buffer where the results are written
 *  @param flags    The following flags are allowed:
 *  <pre>@textblock
 *          kvImageNoFlags                      Default operation
 *
 *          kvImageDoNotTile                    Turn off internal multithreading. This might be useful if you are already multithreading
 *                                              the work in your own tiling engine.
 *  @/textblock </pre>
 *  @result         The following result codes may occur:
 *  <pre>@textblock
 *          kvImageNoError                      Success.
 *
 *          kvImageRoiLargerThanInputBuffer     dest->width and dest->height must be less than or equal to corresponding
 *                                              dimensions in src and alpha
 *  @/textblock</pre>
 */
vImage_Error	vImagePremultiplyData_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)   __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*!
 *  @function vImagePremultiplyData_RGBA8888
 *  @abstract Multiply a RGBA8888 color channel by its corresponding alpha
 *  @discussion
 *  This function multiplies color channels by the alpha channel.
 *  <pre>@textblock
 *      For each color channel:
 *
 *          uint8_t destColor = (src * alpha + 127) / 255;
 *          uint8_t destAlpha = alpha;
 *
 *      This function can work in place provided the following are true:
 *          If src overlaps with dest, src->data must be equal to dest->data
 *          If src also has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *                  (It is not necessary to pass kvImageDoNotTile if src and dest do not overlap.)
 *  @/textblock </pre>
 *
 *      This function will for all 4 channel 8-bit / channel image formats with alpha last in memory.
 *      It does not have to be RGBA. Also available as vImagePremultiplyData_BGRA8888().
 *
 *  @param src      The color data to multiply with alpha
 *  @param dest     A preallocated vImage_Buffer where the results are written
 *  @param flags    The following flags are allowed:
 *  <pre>@textblock
 *          kvImageNoFlags                      Default operation
 *
 *          kvImageDoNotTile                    Turn off internal multithreading. This might be useful if you are already multithreading
 *                                              the work in your own tiling engine.
 *  @/textblock </pre>
 *  @result         The following result codes may occur:
 *  <pre>@textblock
 *          kvImageNoError                      Success.
 *
 *          kvImageRoiLargerThanInputBuffer     dest->width and dest->height must be less than or equal to corresponding
 *                                              dimensions in src and alpha
 *  @/textblock</pre>
 */
vImage_Error	vImagePremultiplyData_RGBA8888( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)   __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
#define         vImagePremultiplyData_BGRA8888( _src, _dest, _flags )           vImagePremultiplyData_RGBA8888((_src), (_dest), (_flags))

/*!
 *  @function vImagePremultiplyData_RGBAFFFF
 *  @abstract Multiply a RGBAFFFF color channel by its corresponding alpha
 *  @discussion
 *  This function multiplies color channels by the alpha channel.
 *  <pre>@textblock
 *      For each color channel:
 *
 *          float destColor = src * alpha;
 *          float destAlpha = alpha;
 *
 *      This function can work in place provided the following are true:
 *          If src overlaps with dest, src->data must be equal to dest->data
 *          If src also has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *                  (It is not necessary to pass kvImageDoNotTile if src and dest do not overlap.)
 *  @/textblock </pre>
 *
 *      This function will for all 4 channel float / channel image formats with alpha first in memory.
 *      It does not have to be RGBA. Also available as vImagePremultiplyData_BGRAFFFF().
 *
 *  @param src      The color data to multiply with alpha
 *  @param dest     A preallocated vImage_Buffer where the results are written
 *  @param flags    The following flags are allowed:
 *  <pre>@textblock
 *          kvImageNoFlags                      Default operation
 *
 *          kvImageDoNotTile                    Turn off internal multithreading. This might be useful if you are already multithreading
 *                                              the work in your own tiling engine.
 *  @/textblock </pre>
 *  @result         The following result codes may occur:
 *  <pre>@textblock
 *          kvImageNoError                      Success.
 *
 *          kvImageRoiLargerThanInputBuffer     dest->width and dest->height must be less than or equal to corresponding
 *                                              dimensions in src and alpha
 *  @/textblock</pre>
 */
vImage_Error	vImagePremultiplyData_RGBAFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)   __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
#define         vImagePremultiplyData_BGRAFFFF( _src, _dest, _flags )           vImagePremultiplyData_RGBAFFFF((_src), (_dest), (_flags))

/*!
 *  @function vImagePremultiplyData_ARGB16U
 *  @abstract Multiply a unsigned 16-bit ARGB color channel by its corresponding alpha
 *  @discussion
 *  This function multiplies color channels by the alpha channel.
 *  <pre>@textblock
 *      For each color channel:
 *
 *          uint16_t destColor = (src * alpha + 32767) / 65535;
 *          uint16_t destAlpha = alpha;
 *
 *      This function can work in place provided the following are true:
 *          If src overlaps with dest, src->data must be equal to dest->data
 *          If src also has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *                  (It is not necessary to pass kvImageDoNotTile if src and dest do not overlap.)
 *  @/textblock </pre>
 *
 *      This function will for all 4 channel uint16_t / channel image formats with alpha first in memory.
 *      It does not have to be ARGB.
 *
 *  @param src      The color data to multiply with alpha
 *  @param dest     A preallocated vImage_Buffer where the results are written
 *  @param flags    The following flags are allowed:
 *  <pre>@textblock
 *          kvImageNoFlags                      Default operation
 *
 *          kvImageDoNotTile                    Turn off internal multithreading. This might be useful if you are already multithreading
 *                                              the work in your own tiling engine.
 *  @/textblock </pre>
 *  @result         The following result codes may occur:
 *  <pre>@textblock
 *          kvImageNoError                      Success.
 *
 *          kvImageRoiLargerThanInputBuffer     dest->width and dest->height must be less than or equal to corresponding
 *                                              dimensions in src and alpha
 *  @/textblock</pre>
 */
vImage_Error	vImagePremultiplyData_ARGB16U( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_6_0 );

/*!
 *  @function vImagePremultiplyData_RGBA16U
 *  @abstract Multiply a unsigned 16-bit RGBA color channel by its corresponding alpha
 *  @discussion
 *  This function multiplies color channels by the alpha channel.
 *  <pre>@textblock
 *      For each color channel:
 *
 *          uint16_t destColor = (src * alpha + 32767) / 65535;
 *          uint16_t destAlpha = alpha;
 *
 *      This function can work in place provided the following are true:
 *          If src overlaps with dest, src->data must be equal to dest->data
 *          If src also has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *                  (It is not necessary to pass kvImageDoNotTile if src and dest do not overlap.)
 *  @/textblock </pre>
 *
 *      This function will for all 4 channel uint16_t / channel image formats with alpha last in memory.
 *      It does not have to be RGBA. Also available as vImagePremultiplyData_BGRA16U().
 *
 *  @param src      The color data to multiply with alpha
 *  @param dest     A preallocated vImage_Buffer where the results are written
 *  @param flags    The following flags are allowed:
 *  <pre>@textblock
 *          kvImageNoFlags                      Default operation
 *
 *          kvImageDoNotTile                    Turn off internal multithreading. This might be useful if you are already multithreading
 *                                              the work in your own tiling engine.
 *  @/textblock </pre>
 *  @result         The following result codes may occur:
 *  <pre>@textblock
 *          kvImageNoError                      Success.
 *
 *          kvImageRoiLargerThanInputBuffer     dest->width and dest->height must be less than or equal to corresponding
 *                                              dimensions in src and alpha
 *  @/textblock</pre>
 */
vImage_Error	vImagePremultiplyData_RGBA16U( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_6_0 );
#define         vImagePremultiplyData_BGRA16U( _src, _dest, _flags )           vImagePremultiplyData_RGBA16U((_src), (_dest), (_flags))


/*!
 *  @function vImagePremultiplyData_ARGB16Q12
 *  @abstract Multiply a signed 16Q12 fixed-point ARGB color channel by its corresponding alpha
 *  @discussion
 *  This function multiplies color channels by the alpha channel.
 *      For each color in each pixel:
 *  <pre>@textblock
 *          int16_t destColor = CLAMP((src * alpha + 2048) / 4096, INT16_MIN, INT16_MAX);
 *          int16_t destAlpha = alpha;
 *  @/textblock </pre>
 *      This function can work in place provided the following are true:
 *          If src overlaps with dest, src->data must be equal to dest->data
 *          If src also has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *                  (It is not necessary to pass kvImageDoNotTile if src and dest do not overlap.)
 *
 *      This function will for other 4 channel 16Q12 / channel image formats with alpha first in memory.
 *      It does not have to be ARGB.
 *
 *  @param src      The color data to multiply with alpha
 *  @param dest     A preallocated vImage_Buffer where the results are written
 *  @param flags    The following flags are allowed:
 *  <pre>@textblock
 *          kvImageNoFlags                      Default operation
 *
 *          kvImageDoNotTile                    Turn off internal multithreading. This might be useful if you are already multithreading
 *                                              the work in your own tiling engine.
 *  @/textblock </pre>
 *  @result         The following result codes may occur:
 *  <pre>@textblock
 *          kvImageNoError                      Success.
 *
 *          kvImageRoiLargerThanInputBuffer     dest->width and dest->height must be less than or equal to corresponding
 *                                              dimensions in src and alpha
 *  @/textblock</pre>
 */
vImage_Error    vImagePremultiplyData_ARGB16Q12( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );

/*!
 *  @function vImagePremultiplyData_RGBA16Q12
 *  @abstract Multiply a signed 16Q12 RGBA color channel by its corresponding alpha
 *  @discussion
 *  This function multiplies color channels by the alpha channel.
 *      For each color in each pixel:
 *  <pre>@textblock
 *          int16_t destColor = CLAMP((src * alpha + 2048) / 4096, INT16_MIN, INT16_MAX);
 *          int16_t destAlpha = alpha;
 *  @/textblock </pre>
 *      This function can work in place provided the following are true:
 *          If src overlaps with dest, src->data must be equal to dest->data
 *          If src also has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *                  (It is not necessary to pass kvImageDoNotTile if src and dest do not overlap.)
 *
 *      This function will for all 4 channel 16Q12 / channel image formats with alpha last in memory.
 *      It does not have to be RGBA.
 *
 *  @param src      The color data to multiply with alpha
 *  @param dest     A preallocated vImage_Buffer where the results are written
 *  @param flags    The following flags are allowed:
 *  <pre>@textblock
 *          kvImageNoFlags                      Default operation
 *
 *          kvImageDoNotTile                    Turn off internal multithreading. This might be useful if you are already multithreading
 *                                              the work in your own tiling engine.
 *  @/textblock </pre>
 *  @result         The following result codes may occur:
 *  <pre>@textblock
 *          kvImageNoError                      Success.
 *
 *          kvImageRoiLargerThanInputBuffer     dest->width and dest->height must be less than or equal to corresponding
 *                                              dimensions in src and alpha
 *  @/textblock</pre>
 */
vImage_Error    vImagePremultiplyData_RGBA16Q12( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
    
/*!
 *  @functiongroup Unpremultiply Data
 *  @discussion Divide a premultiplied image by its alpha channel to produce a non-premultiplied image.
 */
    
/*!
 *  @function vImageUnpremultiplyData_Planar8
 *  @abstract Divide alpha from a premultiplied Planar8 images
 *
 *  @discussion This function divides color channels by the alpha channel.
 *      For each color channel:
 *  <pre>@textblock
 *          uint8_t destColor = ( MIN(src_color, alpha) * 255 + alpha/2) / alpha;
 *  @/textblock </pre>
 *      ...which is the nearest unpremultiplied result, with clamping to ensure no modulo overflow in cases where srcColor > srcAlpha.
 *      In the division by zero case, the returned color value is 0.  
 *
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data.
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 *  @param src          The planar8 input color channel
 *  @param alpha        The planar8 input alpha channel
 *  @param dest         A preallocated planar8 destination buffer into which the result will be written.'
 *  @param flags        The following flags are allowed:
 *      <pre>@textblock
 *                      kvImageNoFlags          Default operation
 *
 *                      kvImageDoNotTile        Disable internal multithreading.
 *      @/textblock </pre>
 *
 *  @result The following error codes may be returned:
 *      <pre>@textblock
 *                      kvImageNoError                      Success
 *
 *                      kvImageRoiLargerThanInputBuffer     dest->height or width is larger than the corresponding src or alpha dimension
 *      @/textblock </pre>
 */
vImage_Error	vImageUnpremultiplyData_Planar8( const vImage_Buffer *src, const vImage_Buffer *alpha, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3)   __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

    
/*!
 *  @function vImageUnpremultiplyData_PlanarF
 *  @abstract Divide alpha from a premultiplied PlanarF images
 *
 *  @discussion This function divides color channels by the alpha channel.
 *      For each color channel:
 *  <pre>@textblock
 *          float destColor = destColor / alpha;   // according to current rounding mode
 *  @/textblock </pre>
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data.
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 *  @param src          The planarF input color channel
 *  @param alpha        The planarF input alpha channel
 *  @param dest         A preallocated planar8 destination buffer into which the result will be written.'
 *  @param flags        The following flags are allowed:
 *      <pre>@textblock
 *                      kvImageNoFlags          Default operation
 *
 *                      kvImageDoNotTile        Disable internal multithreading.
 *      @/textblock </pre>
 *
 *  @result The following error codes may be returned:
 *      <pre>@textblock
 *                      kvImageNoError                      Success
 *
 *                      kvImageRoiLargerThanInputBuffer     dest->height or width is larger than the corresponding src or alpha dimension
 *      @/textblock </pre>
 */
vImage_Error	vImageUnpremultiplyData_PlanarF( const vImage_Buffer *src, const vImage_Buffer *alpha, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3)    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*!
 *  @function vImageUnpremultiplyData_ARGB8888
 *  @abstract Divide the alpha channel from the color channels in a ARGB8888 image
 *  @discussion
 *  This function divides color channels by the alpha channel.
 *      For each color channel:
 *      <pre>@textblock
 *          uint8_t destColor = ( MIN(src_color, alpha) * 255 + alpha/2) / alpha;
 *          uint8_t destAlpha = alpha;
 *      @/textblock </pre>
 *
 *      ...which is the nearest unpremultiplied result, with clamping to ensure no modulo overflow in cases where srcColor > srcAlpha.
 *      In the division by zero case, the returned color value is 0.  
 *
 *      The positioning of only the alpha channel is important for interleaved formats for these functions.
 *      This function will work with other channel orders that have alpha first.
 *
 *      This function can work in place provided the following are true:
 *          src->data must be equal to dest->data
 *          src->rowBytes must be equal to dest->rowBytes
 *
 *  @param src          The input inmage
 *  @param dest         A preallocated planar8 destination buffer into which the result will be written.'
 *  @param flags        The following flags are allowed:
 *      <pre>@textblock
 *                      kvImageNoFlags          Default operation
 *
 *                      kvImageDoNotTile        Disable internal multithreading.
 *      @/textblock </pre>
 *
 *  @result The following error codes may be returned:
 *      <pre>@textblock
 *                      kvImageNoError                      Success
 *
 *                      kvImageRoiLargerThanInputBuffer     dest->height or width is larger than the corresponding src or alpha dimension
 *      @/textblock </pre>
 */
vImage_Error	vImageUnpremultiplyData_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*!
 *  @function vImageUnpremultiplyData_RGBA8888
 *  @abstract Divide the alpha channel from the color channels in a RGBA8888 image
 *  @discussion
 *  This function divides color channels by the alpha channel.
 *      For each color channel:
 *      <pre>@textblock
 *          uint8_t destColor = ( MIN(src_color, alpha) * 255 + alpha/2) / alpha;
 *          uint8_t destAlpha = alpha;
 *      @/textblock </pre>
 *
 *      ...which is the nearest unpremultiplied result, with clamping to ensure no modulo overflow in cases where srcColor > srcAlpha.
 *      In the division by zero case, the returned color value is 0.
 *
 *      The positioning of only the alpha channel is important for interleaved formats for these functions.
 *      This function will work with other channel orders that have alpha last. The function is also available as vImageUnpremultiplyData_BGRA8888.
 *
 *      This function can work in place provided the following are true:
 *          src->data must be equal to dest->data
 *          src->rowBytes must be equal to dest->rowBytes
 *
 *  @param src          The input inmage
 *  @param dest         A preallocated planar8 destination buffer into which the result will be written.'
 *  @param flags        The following flags are allowed:
 *      <pre>@textblock
 *                      kvImageNoFlags          Default operation
 *
 *                      kvImageDoNotTile        Disable internal multithreading.
 *      @/textblock </pre>
 *
 *  @result The following error codes may be returned:
 *      <pre>@textblock
 *                      kvImageNoError                      Success
 *
 *                      kvImageRoiLargerThanInputBuffer     dest->height or width is larger than the corresponding src or alpha dimension
 *      @/textblock </pre>
 */
vImage_Error	vImageUnpremultiplyData_RGBA8888( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
#define         vImageUnpremultiplyData_BGRA8888( _src, _dest, _flags )             vImageUnpremultiplyData_RGBA8888((_src), (_dest), (_flags))

/*!
 *  @function vImageUnpremultiplyData_ARGBFFFF
 *  @abstract Divide the alpha channel from the color channels in a ARGBFFFF image
 *  @discussion
 *  This function divides color channels by the alpha channel.
 *      For each color channel:
 *      <pre>@textblock
 *          float destColor = destColor / alpha;
 *          float destAlpha = alpha;
 *      @/textblock </pre>
 *
 *      The positioning of only the alpha channel is important for interleaved formats for these functions.
 *      This function will work with other channel orders that have alpha first.
 *
 *      This function can work in place provided the following are true:
 *          src->data must be equal to dest->data
 *          src->rowBytes must be equal to dest->rowBytes
 *
 *  @param src          The input inmage
 *  @param dest         A preallocated planar8 destination buffer into which the result will be written.'
 *  @param flags        The following flags are allowed:
 *      <pre>@textblock
 *                      kvImageNoFlags          Default operation
 *
 *                      kvImageDoNotTile        Disable internal multithreading.
 *      @/textblock </pre>
 *
 *  @result The following error codes may be returned:
 *      <pre>@textblock
 *                      kvImageNoError                      Success
 *
 *                      kvImageRoiLargerThanInputBuffer     dest->height or width is larger than the corresponding src or alpha dimension
 *      @/textblock </pre>
 */
vImage_Error	vImageUnpremultiplyData_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

    
/*!
 *  @function vImageUnpremultiplyData_RGBAFFFF
 *  @abstract Divide the alpha channel from the color channels in a RGBAFFFF image
 *  @discussion
 *  This function divides color channels by the alpha channel.
 *      For each color channel:
 *      <pre>@textblock
 *          float destColor = destColor / alpha;
 *          float destAlpha = alpha;
 *      @/textblock </pre>
 *
 *      The positioning of only the alpha channel is important for interleaved formats for these functions.
 *      This function will work with other channel orders that have alpha last. It is also available as vImageUnpremultiplyData_BGRAFFFF().
 *
 *      This function can work in place provided the following are true:
 *          src->data must be equal to dest->data
 *          src->rowBytes must be equal to dest->rowBytes
 *
 *  @param src          The input inmage
 *  @param dest         A preallocated planar8 destination buffer into which the result will be written.'
 *  @param flags        The following flags are allowed:
 *      <pre>@textblock
 *                      kvImageNoFlags          Default operation
 *
 *                      kvImageDoNotTile        Disable internal multithreading.
 *      @/textblock </pre>
 *
 *  @result The following error codes may be returned:
 *      <pre>@textblock
 *                      kvImageNoError                      Success
 *
 *                      kvImageRoiLargerThanInputBuffer     dest->height or width is larger than the corresponding src or alpha dimension
 *      @/textblock </pre>
 */
vImage_Error	vImageUnpremultiplyData_RGBAFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
#define         vImageUnpremultiplyData_BGRAFFFF( _src, _dest, _flags )             vImageUnpremultiplyData_RGBAFFFF((_src), (_dest), (_flags))

    
/*!
 *  @function vImageUnpremultiplyData_ARGB16U
 *  @abstract Divide the alpha channel from the color channels in a ARGB16U image
 *  @discussion
 *  This function divides color channels by the alpha channel.
 *      For each color channel:
 *      <pre>@textblock
 *          uint16_t destColor = ( MIN(src_color, alpha) * 65535 + alpha/2) / alpha;
 *          uint16_t destAlpha = alpha;
 *      @/textblock </pre>
 *
 *      ...which is the nearest unpremultiplied result, with clamping to ensure no modulo overflow in cases where srcColor > srcAlpha.
 *      In the division by zero case, the returned color value is 0.
 *
 *      The positioning of only the alpha channel is important for interleaved formats for these functions.
 *      This function will work with other channel orders that have alpha first.
 *
 *      This function can work in place provided the following are true:
 *          src->data must be equal to dest->data
 *          src->rowBytes must be equal to dest->rowBytes
 *
 *  @param src          The input inmage
 *  @param dest         A preallocated planar8 destination buffer into which the result will be written.'
 *  @param flags        The following flags are allowed:
 *      <pre>@textblock
 *                      kvImageNoFlags          Default operation
 *
 *                      kvImageDoNotTile        Disable internal multithreading.
 *      @/textblock </pre>
 *
 *  @result The following error codes may be returned:
 *      <pre>@textblock
 *                      kvImageNoError                      Success
 *
 *                      kvImageRoiLargerThanInputBuffer     dest->height or width is larger than the corresponding src or alpha dimension
 *      @/textblock </pre>
 */
vImage_Error	vImageUnpremultiplyData_ARGB16U( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_6_0 );

    
/*!
 *  @function vImageUnpremultiplyData_RGBA16U
 *  @abstract Divide the alpha channel from the color channels in a RGBA16U image
 *  @discussion
 *  This function divides color channels by the alpha channel.
 *      For each color channel:
 *      <pre>@textblock
 *          uint16_t destColor = ( MIN(src_color, alpha) * 65535 + alpha/2) / alpha;
 *          uint16_t destAlpha = alpha;
 *      @/textblock </pre>
 *
 *      ...which is the nearest unpremultiplied result, with clamping to ensure no modulo overflow in cases where srcColor > srcAlpha.
 *      In the division by zero case, the returned color value is 0.
 *
 *      The positioning of only the alpha channel is important for interleaved formats for these functions.
 *      This function will work with other channel orders that have alpha last. The function is also available as vImageUnpremultiplyData_BGRA16U.
 *
 *      This function can work in place provided the following are true:
 *          src->data must be equal to dest->data
 *          src->rowBytes must be equal to dest->rowBytes
 *
 *  @param src          The input inmage
 *  @param dest         A preallocated planar8 destination buffer into which the result will be written.'
 *  @param flags        The following flags are allowed:
 *      <pre>@textblock
 *                      kvImageNoFlags          Default operation
 *
 *                      kvImageDoNotTile        Disable internal multithreading.
 *      @/textblock </pre>
 *
 *  @result The following error codes may be returned:
 *      <pre>@textblock
 *                      kvImageNoError                      Success
 *
 *                      kvImageRoiLargerThanInputBuffer     dest->height or width is larger than the corresponding src or alpha dimension
 *      @/textblock </pre>
 */
vImage_Error	vImageUnpremultiplyData_RGBA16U( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_6_0 );
#define         vImageUnpremultiplyData_BGRA16U( _src, _dest, _flags )             vImageUnpremultiplyData_RGBA16U((_src), (_dest), (_flags))

/*!
 *  @function vImageUnpremultiplyData_ARGB16Q12
 *  @abstract Divide the alpha channel from the color channels in a ARGB16Q12 image
 *  @discussion
 *  This function divides color channels by the alpha channel.
 *      For each color channel:
 *      <pre>@textblock
 *          int16_t destColor = ( MIN(src_color, alpha) * 4096 + alpha/2) / alpha;
 *          int16_t destAlpha = alpha;
 *      @/textblock </pre>
 *
 *      ...which is the nearest unpremultiplied result, with clamping to ensure no modulo overflow in cases where srcColor > srcAlpha.
 *      In the division by zero case, the returned color value is 0.
 *
 *      The positioning of only the alpha channel is important for interleaved formats for these functions.
 *      This function will work with other channel orders that have alpha first.
 *
 *      This function can work in place provided the following are true:
 *          src->data must be equal to dest->data
 *          src->rowBytes must be equal to dest->rowBytes
 *
 *  @param src          The input inmage
 *  @param dest         A preallocated planar8 destination buffer into which the result will be written.'
 *  @param flags        The following flags are allowed:
 *      <pre>@textblock
 *                      kvImageNoFlags          Default operation
 *
 *                      kvImageDoNotTile        Disable internal multithreading.
 *      @/textblock </pre>
 *
 *  @result The following error codes may be returned:
 *      <pre>@textblock
 *                      kvImageNoError                      Success
 *
 *                      kvImageRoiLargerThanInputBuffer     dest->height or width is larger than the corresponding src or alpha dimension
 *      @/textblock </pre>
 */
vImage_Error    vImageUnpremultiplyData_ARGB16Q12( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );

    
/*!
 *  @function vImageUnpremultiplyData_RGBA16Q12
 *  @abstract Divide the alpha channel from the color channels in a RGBA16Q12 image
 *  @discussion
 *  This function divides color channels by the alpha channel.
 *      For each color channel:
 *      <pre>@textblock
 *          int16_t destColor = ( MIN(src_color, alpha) * 4096 + alpha/2) / alpha;
 *          int16_t destAlpha = alpha;
 *      @/textblock </pre>
 *
 *      ...which is the nearest unpremultiplied result, with clamping to ensure no modulo overflow in cases where srcColor > srcAlpha.
 *      In the division by zero case, the returned color value is 0.
 *
 *      The positioning of only the alpha channel is important for interleaved formats for these functions.
 *      This function will work with other channel orders that have alpha last. 
 *
 *      This function can work in place provided the following are true:
 *          src->data must be equal to dest->data
 *          src->rowBytes must be equal to dest->rowBytes
 *
 *  @param src          The input inmage
 *  @param dest         A preallocated planar8 destination buffer into which the result will be written.'
 *  @param flags        The following flags are allowed:
 *      <pre>@textblock
 *                      kvImageNoFlags          Default operation
 *
 *                      kvImageDoNotTile        Disable internal multithreading.
 *      @/textblock </pre>
 *
 *  @result The following error codes may be returned:
 *      <pre>@textblock
 *                      kvImageNoError                      Success
 *
 *                      kvImageRoiLargerThanInputBuffer     dest->height or width is larger than the corresponding src or alpha dimension
 *      @/textblock </pre>
 */
vImage_Error    vImageUnpremultiplyData_RGBA16Q12( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );

/*!
 * @functiongroup Alpha Blend (Premultiplied with additional constant alpha)
 * @discussion  A premultiplied alpha blend with an extra constant alpha applied to the top image to allow
 *              it to be faded in our out.
 */
    
/*!
 * @function vImagePremultipliedConstAlphaBlend_Planar8
 * @abstract Blend two Planar8 premultiplied images with an extra image-wide alpha for the top image
 * @discussion  This is a premultiplied alpha compositing function using a constant for alpha over the whole image.
 *  Color data from both images is presumed to be already premultiplied by its own per-pixel alpha.
 *      For calculations involving 8-bit integer data, the calculation is done with an additional rounding step
 *      followed by division by 255:
 * <pre>@textblock
 *          uint8_t destColor = (srcTopColor * constAlpha * 255  + (255*255 - srcTopAlpha * constAlpha) * srcBottomColor + 127*255) / (255*255);
 *          uint8_t destAlpha =  (srcTopAlpha * constAlpha * 255 + (255*255 - srcTopAlpha * constAlpha) * srcBottomAlpha + 127*255 ) / (255*255);
 * @/textblock</pre>
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 * @param srcTop        The top image
 * @param constAlpha    An extra alpha to apply to the entire top image
 * @param srcTopAlpha   The alpha channel for the top image
 * @param srcBottom     The bottom image
 * @param dest          A preallocate vImage_Buffer where the result will be written
 * @param flags         The following flags are allowed:
 * <pre>@textblock
 *          kvImageNoFlags          Default operation
 *
 *          kvImageDoNotTile        Turn off internal multithreading
 * @/textblock</pre>
 * @return The following error codes may be returned:
 * <pre>@textblock
 *          kvImageNoError                      Success
 *
 *          kvImageRoiLargerThanInputBuffer     The destination buffer height or width is larger than the corresponding dimension in
 *                                              srcTop, srcTopAlpha or srcBottom
 * @/textblock</pre>
 */
vImage_Error	vImagePremultipliedConstAlphaBlend_Planar8( const vImage_Buffer *srcTop, Pixel_8 constAlpha, const vImage_Buffer *srcTopAlpha, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,3,4,5)    __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

/*!
 * @function vImagePremultipliedConstAlphaBlend_PlanarF
 * @abstract Blend two PlanarF premultiplied images with an extra image-wide alpha for the top image
 * @discussion  This is a premultiplied alpha compositing function using a constant for alpha over the whole image.
 *  Color data from both images is presumed to be already premultiplied by its own per-pixel alpha.
 * <pre>@textblock
 *          float destColor = srcTopColor * constAlpha  + (1.0 - srcTopAlpha  * constAlpha) * srcBottomColor;
 *          float alpha =  srcTopAlpha * constAlpha + (1.0 - srcTopAlpha * constAlpha) * srcBottomAlpha
 * @/textblock </pre>
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 * @param srcTop        The top image
 * @param constAlpha    An extra alpha to apply to the entire top image
 * @param srcTopAlpha   The alpha channel for the top image
 * @param srcBottom     The bottom image
 * @param dest          A preallocate vImage_Buffer where the result will be written
 * @param flags         The following flags are allowed:
 * <pre>@textblock
 *          kvImageNoFlags          Default operation
 *
 *          kvImageDoNotTile        Turn off internal multithreading
 * @/textblock</pre>
 * @return The following error codes may be returned:
 * <pre>@textblock
 *          kvImageNoError                      Success
 *
 *          kvImageRoiLargerThanInputBuffer     The destination buffer height or width is larger than the corresponding dimension in
 *                                              srcTop, srcTopAlpha or srcBottom
 * @/textblock</pre>
 */
vImage_Error	vImagePremultipliedConstAlphaBlend_PlanarF( const vImage_Buffer *srcTop, Pixel_F constAlpha, const vImage_Buffer *srcTopAlpha, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,3,4,5)    __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

/*!
 * @function vImagePremultipliedConstAlphaBlend_ARGB8888
 * @abstract Blend two ARGB8888 premultiplied images with an extra image-wide alpha for the top image
 * @discussion  This is a premultiplied alpha compositing function using a constant for alpha over the whole image.
 *  Color data from both images is presumed to be already premultiplied by its own per-pixel alpha.
 *      For calculations involving 8-bit integer data, the calculation is done with an additional rounding step
 *      followed by division by 255:
 * <pre>@textblock
 *          uint8_t destColor = (srcTopColor * constAlpha * 255  + (255*255 - srcTopAlpha * constAlpha) * srcBottomColor + 127*255) / (255*255);
 *          uint8_t destAlpha =  (srcTopAlpha * constAlpha * 255 + (255*255 - srcTopAlpha * constAlpha) * srcBottomAlpha + 127*255 ) / (255*255);
 * @/textblock</pre>
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 *      The  function will work for all 4 channel 8-bit / channel image formats with alpha first in memory, not just ARGB.
 * @param srcTop        The top image
 * @param constAlpha    An extra alpha to apply to the entire top image
 * @param srcBottom     The bottom image
 * @param dest          A preallocate vImage_Buffer where the result will be written
 * @param flags         The following flags are allowed:
 * <pre>@textblock
 *          kvImageNoFlags          Default operation
 *
 *          kvImageDoNotTile        Turn off internal multithreading
 * @/textblock</pre>
 * @return The following error codes may be returned:
 * <pre>@textblock
 *          kvImageNoError                      Success
 *
 *          kvImageRoiLargerThanInputBuffer     The destination buffer height or width is larger than the corresponding dimension in
 *                                              srcTop, srcTopAlpha or srcBottom
 * @/textblock</pre>
 */
vImage_Error	vImagePremultipliedConstAlphaBlend_ARGB8888( const vImage_Buffer *srcTop, Pixel_8 constAlpha, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,3,4)    __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

/*!
 * @function vImagePremultipliedConstAlphaBlend_ARGBFFFF
 * @abstract Blend two ARGBFFFF premultiplied images with an extra image-wide alpha for the top image
 * @discussion  This is a premultiplied alpha compositing function using a constant for alpha over the whole image.
 *  Color data from both images is presumed to be already premultiplied by its own per-pixel alpha.
 *      For calculations involving 8-bit integer data, the calculation is done with an additional rounding step
 *      followed by division by 255:
 * <pre>@textblock
 *          float destColor = srcTopColor * constAlpha  + (1.0 - srcTopAlpha  * constAlpha) * srcBottomColor;
 *          float alpha =  srcTopAlpha * constAlpha + (1.0 - srcTopAlpha * constAlpha) * srcBottomAlpha
 * @/textblock</pre>
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 *      The function will work for all 4 channel float / channel image formats with alpha first in memory, not just ARGB.
 * @param srcTop        The top image
 * @param constAlpha    An extra alpha to apply to the entire top image
 * @param srcBottom     The bottom image
 * @param dest          A preallocate vImage_Buffer where the result will be written
 * @param flags         The following flags are allowed:
 * <pre>@textblock
 *          kvImageNoFlags          Default operation
 *
 *          kvImageDoNotTile        Turn off internal multithreading
 * @/textblock</pre>
 * @return The following error codes may be returned:
 * <pre>@textblock
 *          kvImageNoError                      Success
 *
 *          kvImageRoiLargerThanInputBuffer     The destination buffer height or width is larger than the corresponding dimension in
 *                                              srcTop, srcTopAlpha or srcBottom
 * @/textblock</pre>
 */
vImage_Error	vImagePremultipliedConstAlphaBlend_ARGBFFFF( const vImage_Buffer *srcTop, Pixel_F constAlpha, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,3,4)    __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

/*!
 *  @functiongroup Alpha Blend (Non-premultiplied to premultiplied)
 *  @discussion    These functions blend a non-premultiplied top image into a premultiplied bottom image 
 *                 to produce a premultiplied result.
 */
    
/*!
 * @function vImageAlphaBlend_NonpremultipliedToPremultiplied_Planar8
 * @abstract Blend a non-premultiplied top Planar8 image into a premultiplied Planar8 bottom image and return a premultiplied Planar8 result.
 * @discussion Top buffer is non-premultiplied. Bottom buffer is premultiplied. Dest buffer is premultiplied. Works in place.
 * <pre>@textblock
 *      result = (srcTop * srctopAlpha + (255 - srcTopAlpha) * bottomAlpha + 127 ) / 255;
 * @/textblock </pre>
 * This function will work in place as long as the src and dest buffer overlap exactly. 
 * The src buffers must be at least as large as the dest buffer in each dimension. (src.height >= dest.height && src.width >= dest.width)
 *
 *  To calculate the alpha result for the Planar cases, use 
 * <pre>@textblock
 *      vImagePremultipliedAlphaBlend_Planar8( srcTopAlpha, srcTopAlpha, srcBottomAlpha, dest, flags );
 * @/textblock </pre>
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 * @param srcTop        Planar8 non-premultiplied color channel for top image
 * @param srcTopAlpha   Planar8 alpha channel for top image
 * @param srcBottom     Planar8 premultiplied color channel for bottom image
 * @param dest          Planar8 premultiplied result. Must be preallocated before the call is made.
 * @param flags         The following flags are allowed:
 *      <pre> @textblock
 *          kvImageNoFlags          Default operation.
 *
 *          kvImageDoNotTile        Disable internal multithreading. 
 *      @/textblock </pre>
 *  @result     The following error codes may occur:
 *      <pre> @textblock
 *          kvImageNoError                      Success.
 *
 *          kvImageRoiLargerThanInputBuffer     dest->height and dest->width must be less than or equal to corresponding
 *                                              dimensions in srcTop, srcTopAlpha and srcBottom.
 *      @/textblock </pre>
 */
vImage_Error	vImageAlphaBlend_NonpremultipliedToPremultiplied_Planar8( const vImage_Buffer *srcTop, const vImage_Buffer *srcTopAlpha, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,4)    __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

/*!
 * @function vImageAlphaBlend_NonpremultipliedToPremultiplied_PlanarF
 * @abstract Blend a non-premultiplied top PlanarF image into a premultiplied PlanarF bottom image and return a premultiplied PlanarF result.
 * @discussion Top buffer is non-premultiplied. Bottom buffer is premultiplied. Dest buffer is premultiplied. Works in place.
 * <pre>@textblock
 *      result = srcTop * srcTopAlpha + (1 - srcTopAlpha) * srcBottom
 * @/textblock </pre>
 * This function will work in place as long as the src and dest buffer overlap exactly.
 * The src buffers must be at least as large as the dest buffer in each dimension. (src.height >= dest.height && src.width >= dest.width)
 *
 *  To calculate the alpha result for the Planar cases, use
 * <pre>@textblock
 *      vImagePremultipliedAlphaBlend_PlanarF( srcTopAlpha, srcTopAlpha, srcBottomAlpha, dest, flags );
 * @/textblock </pre>
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 * @param srcTop        Planar8 non-premultiplied color channel for top image
 * @param srcTopAlpha   Planar8 alpha channel for top image
 * @param srcBottom     Planar8 premultiplied color channel for bottom image
 * @param dest          Planar8 premultiplied result. Must be preallocated before the call is made.
 * @param flags         The following flags are allowed:
 *      <pre> @textblock
 *          kvImageNoFlags          Default operation.
 *
 *          kvImageDoNotTile        Disable internal multithreading.
 *      @/textblock </pre>
 *  @result     The following error codes may occur:
 *      <pre> @textblock
 *          kvImageNoError                      Success.
 *
 *          kvImageRoiLargerThanInputBuffer     dest->height and dest->width must be less than or equal to corresponding
 *                                              dimensions in srcTop, srcTopAlpha and srcBottom.
 *      @/textblock </pre>
 */
vImage_Error	vImageAlphaBlend_NonpremultipliedToPremultiplied_PlanarF( const vImage_Buffer *srcTop, const vImage_Buffer *srcTopAlpha, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,4)    __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
    
/*!
 * @function vImageAlphaBlend_NonpremultipliedToPremultiplied_ARGB8888
 * @abstract Blend a non-premultiplied top ARGB8888 image into a premultiplied ARGB8888 bottom image and return a premultiplied ARGB8888 result.
 * @discussion Top buffer is non-premultiplied. Bottom buffer is premultiplied. Dest buffer is premultiplied. Works in place.
 * <pre>@textblock
 *      result = (srcTop * srctopAlpha + (255 - srcTopAlpha) * bottomAlpha + 127 ) / 255;
 * @/textblock </pre>
 * This function will work in place as long as the src and dest buffer overlap exactly.
 * The src buffers must be at least as large as the dest buffer in each dimension. (src.height >= dest.height && src.width >= dest.width)
 *
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 *  This function will work with any channel order with alpha first, not just ARGB.
 *
 * @param srcTop        Planar8 non-premultiplied color channel for top image
 * @param srcBottom     Planar8 premultiplied color channel for bottom image
 * @param dest          Planar8 premultiplied result. Must be preallocated before the call is made.
 * @param flags         The following flags are allowed:
 *      <pre> @textblock
 *          kvImageNoFlags          Default operation.
 *
 *          kvImageDoNotTile        Disable internal multithreading.
 *      @/textblock </pre>
 *  @result     The following error codes may occur:
 *      <pre> @textblock
 *          kvImageNoError                      Success.
 *
 *          kvImageRoiLargerThanInputBuffer     dest->height and dest->width must be less than or equal to corresponding
 *                                              dimensions in srcTop, srcTopAlpha and srcBottom.
 *      @/textblock </pre>
 */
vImage_Error	vImageAlphaBlend_NonpremultipliedToPremultiplied_ARGB8888( const vImage_Buffer *srcTop, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3)    __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

/*!
 * @function vImageAlphaBlend_NonpremultipliedToPremultiplied_ARGBFFFF
 * @abstract Blend a non-premultiplied top ARGBFFFF image into a premultiplied ARGBFFFF bottom image and return a premultiplied ARGBFFFF result.
 * @discussion Top buffer is non-premultiplied. Bottom buffer is premultiplied. Dest buffer is premultiplied. Works in place.
 * <pre>@textblock
 *      result = srcTop * srcTopAlpha + (1 - srcTopAlpha) * srcBottom
 * @/textblock </pre>
 * This function will work in place as long as the src and dest buffer overlap exactly.
 * The src buffers must be at least as large as the dest buffer in each dimension. (src.height >= dest.height && src.width >= dest.width)
 *
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 *  This function will work with any channel order with alpha first, not just ARGB.
 *
 * @param srcTop        Planar8 non-premultiplied color channel for top image
 * @param srcBottom     Planar8 premultiplied color channel for bottom image
 * @param dest          Planar8 premultiplied result. Must be preallocated before the call is made.
 * @param flags         The following flags are allowed:
 *      <pre> @textblock
 *          kvImageNoFlags          Default operation.
 *
 *          kvImageDoNotTile        Disable internal multithreading.
 *      @/textblock </pre>
 *  @result     The following error codes may occur:
 *      <pre> @textblock
 *          kvImageNoError                      Success.
 *
 *          kvImageRoiLargerThanInputBuffer     dest->height and dest->width must be less than or equal to corresponding
 *                                              dimensions in srcTop, srcTopAlpha and srcBottom.
 *      @/textblock </pre>
 */
vImage_Error	vImageAlphaBlend_NonpremultipliedToPremultiplied_ARGBFFFF( const vImage_Buffer *srcTop, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3)    __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

/*!
 * @functiongroup Clip To Alpha
 * @discusssion  If a premultiplied image color channel has a value greater than alpha it is super-opaque.  This may
 *               cause problems later in compositing operations. Alpha > color can happen normally as a result of
 *               convolutions, resampling, and morphological operations. While such operations should generally be done
 *               on non-premultiplied content, sometimes premultiplied content slips through. vImage provides a clamping
 *               function vImageClipToAlpha which identify color channels that are greater than alpha and clamp them to be
 *               equal to alpha.
 */
    
/*!
 *  @function vImageClipToAlpha_Planar8
 *  @abstract Clamp a Planar8 color buffer to be less than or equal to alpha
 *  @discussion
 *  For each pixel, each color channel shall be set to the smaller of the color channel or alpha value for that pixel. 
 *  <pre>@textblock
 *          color_result = MIN( color, alpha )
 *  @/textblock </pre>
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *  @param src      The color image to clip
 *  @param alpha    The alpha channel
 *  @param dest     A preallocated buffer to receive the results.
 *  @param flags    The following flags are allowed:
 *      <pre> @textblock
 *          kvImageNoFlags          Default operation.
 *
 *          kvImageDoNotTile        Disable internal multithreading.
 *      @/textblock </pre>
 *  @result     The following error codes may occur:
 *      <pre> @textblock
 *          kvImageNoError                      Success.
 *
 *          kvImageRoiLargerThanInputBuffer     dest->height and dest->width must be less than or equal to corresponding
 *                                              dimensions in srcTop, srcTopAlpha and srcBottom.
 *      @/textblock </pre>
 */
vImage_Error vImageClipToAlpha_Planar8( const vImage_Buffer *src, const vImage_Buffer *alpha, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

/*!
 *  @function vImageClipToAlpha_PlanarF
 *  @abstract Clamp a PlanarF color buffer to be less than or equal to alpha
 *  @discussion
 *  For each pixel, each color channel shall be set to the smaller of the color channel or alpha value for that pixel.
 *  <pre>@textblock
 *          color_result = MIN( color, alpha )
 *  @/textblock </pre>
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *  @param src      The color image to clip
 *  @param alpha    The alpha channel
 *  @param dest     A preallocated buffer to receive the results.
 *  @param flags    The following flags are allowed:
 *      <pre> @textblock
 *          kvImageNoFlags          Default operation.
 *
 *          kvImageDoNotTile        Disable internal multithreading.
 *      @/textblock </pre>
 *  @result     The following error codes may occur:
 *      <pre> @textblock
 *          kvImageNoError                      Success.
 *
 *          kvImageRoiLargerThanInputBuffer     dest->height and dest->width must be less than or equal to corresponding
 *                                              dimensions in srcTop, srcTopAlpha and srcBottom.
 *      @/textblock </pre>
 */
vImage_Error vImageClipToAlpha_PlanarF( const vImage_Buffer *src,  const vImage_Buffer *alpha,  const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
 
/*!
 *  @function vImageClipToAlpha_ARGB8888
 *  @abstract Clamp a ARGB8888 color buffer to be less than or equal to alpha
 *  @discussion
 *  For each pixel, each color channel shall be set to the smaller of the color channel or alpha value for that pixel.
 *  <pre>@textblock
 *          alpha_result = alpha
 *          color_result = MIN( color, alpha )
 *  @/textblock </pre>
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 *      This function will work for any channel order with alpha first, not just ARGB.
 *
 *  @param src      The color image to clip
 *  @param dest     A preallocated buffer to receive the results.
 *  @param flags    The following flags are allowed:
 *      <pre> @textblock
 *          kvImageNoFlags          Default operation.
 *
 *          kvImageDoNotTile        Disable internal multithreading.
 *      @/textblock </pre>
 *  @result     The following error codes may occur:
 *      <pre> @textblock
 *          kvImageNoError                      Success.
 *
 *          kvImageRoiLargerThanInputBuffer     dest->height and dest->width must be less than or equal to corresponding
 *                                              dimensions in srcTop, srcTopAlpha and srcBottom.
 *      @/textblock </pre>
 */
vImage_Error vImageClipToAlpha_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

/*!
 *  @function vImageClipToAlpha_ARGBFFFF
 *  @abstract Clamp a ARGBFFFF color buffer to be less than or equal to alpha
 *  @discussion
 *  For each pixel, each color channel shall be set to the smaller of the color channel or alpha value for that pixel.
 *  <pre>@textblock
 *          alpha_result = alpha
 *          color_result = MIN( color, alpha )
 *  @/textblock </pre>
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 *      This function will work for any channel order with alpha first, not just ARGB.
 *
 *  @param src      The color image to clip
 *  @param dest     A preallocated buffer to receive the results.
 *  @param flags    The following flags are allowed:
 *      <pre> @textblock
 *          kvImageNoFlags          Default operation.
 *
 *          kvImageDoNotTile        Disable internal multithreading.
 *      @/textblock </pre>
 *  @result     The following error codes may occur:
 *      <pre> @textblock
 *          kvImageNoError                      Success.
 *
 *          kvImageRoiLargerThanInputBuffer     dest->height and dest->width must be less than or equal to corresponding
 *                                              dimensions in srcTop, srcTopAlpha and srcBottom.
 *      @/textblock </pre>
 */
vImage_Error vImageClipToAlpha_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

/*!
 *  @function vImageClipToAlpha_RGBA8888
 *  @abstract Clamp a RGBA8888 color buffer to be less than or equal to alpha
 *  @discussion
 *  For each pixel, each color channel shall be set to the smaller of the color channel or alpha value for that pixel.
 *  <pre>@textblock
 *          alpha_result = alpha
 *          color_result = MIN( color, alpha )
 *  @/textblock </pre>
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 *      This function will work for any channel order with alpha last, not just RGBA. Also available as vImageClipToAlpha_BGRA8888().
 *
 *  @param src      The color image to clip
 *  @param dest     A preallocated buffer to receive the results.
 *  @param flags    The following flags are allowed:
 *      <pre> @textblock
 *          kvImageNoFlags          Default operation.
 *
 *          kvImageDoNotTile        Disable internal multithreading.
 *      @/textblock </pre>
 *  @result     The following error codes may occur:
 *      <pre> @textblock
 *          kvImageNoError                      Success.
 *
 *          kvImageRoiLargerThanInputBuffer     dest->height and dest->width must be less than or equal to corresponding
 *                                              dimensions in srcTop, srcTopAlpha and srcBottom.
 *      @/textblock </pre>
 */
vImage_Error vImageClipToAlpha_RGBA8888( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_6_0 );
#define vImageClipToAlpha_BGRA8888(_src, _dest, _flags)   vImageClipToAlpha_RGBA8888((_src), (_dest), (_flags))

/*!
 *  @function vImageClipToAlpha_RGBAFFFF
 *  @abstract Clamp a RGBAFFFF color buffer to be less than or equal to alpha
 *  @discussion
 *  For each pixel, each color channel shall be set to the smaller of the color channel or alpha value for that pixel.
 *  <pre>@textblock
 *          alpha_result = alpha
 *          color_result = MIN( color, alpha )
 *  @/textblock </pre>
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 *      This function will work for any channel order with alpha last, not just RGBA. Also available as vImageClipToAlpha_BGRAFFFF().
 *
 *  @param src      The color image to clip
 *  @param dest     A preallocated buffer to receive the results.
 *  @param flags    The following flags are allowed:
 *      <pre> @textblock
 *          kvImageNoFlags          Default operation.
 *
 *          kvImageDoNotTile        Disable internal multithreading.
 *      @/textblock </pre>
 *  @result     The following error codes may occur:
 *      <pre> @textblock
 *          kvImageNoError                      Success.
 *
 *          kvImageRoiLargerThanInputBuffer     dest->height and dest->width must be less than or equal to corresponding
 *                                              dimensions in srcTop, srcTopAlpha and srcBottom.
 *      @/textblock </pre>
 */
vImage_Error vImageClipToAlpha_RGBAFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_6_0 );
#define vImageClipToAlpha_BGRAFFFF(_src, _dest, _flags)   vImageClipToAlpha_RGBAFFFF((_src), (_dest), (_flags))

/*
 * See also the vImageFlatten APIs in Conversion.h for compositing an image against a constant color opaque background.
 */

#ifdef __cplusplus
}
#endif

#endif /* vImage_ALPHA_H */


