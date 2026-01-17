/*
 *  Alpha.h
 *  vImage Framework
 *
 *  Copyright (c) 2003 Apple Computer. All rights reserved.
 *
 */

#ifndef VIMAGE_ALPHA_H
#define VIMAGE_ALPHA_H	

#include <vImage/vImage_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *
 *	These alpha compositing functions assume that the floating point range is 0.0 (black) to 1.0 (full intensity color).
 *	While values outside these ranges do function correctly (you can have 110% intensity color or -50% color, for example), 
 *	the calculation is done assuming 1.0 represents full intensity color, and 0.0 represents the absence of color. If these 
 *	assumptions are not correct, then the calculation will produce incorrect results. Apple does not currently provide 
 *	alpha compositing functions that work with any floating point range in vImage.  
 *
 *	8 bit functionality assumes that 0 is no color, and 255 is full color. 8 bit functions do saturated clipping before
 *	converting from internal precision back to 8 bits. The internal calculation is done with higher precision.
 *
 */

/*
 *  vImageAlphaBlend_*
 *
 *  This is a non-premultiplied alpha compositing function.  
 *      For each color channel:
 *
 *          float destColor = (  srcTopColor * srcTopAlpha + (1.0 - srcTopAlpha) * srcBottomAlpha * srcBottomColor ) / alpha
 *
 *      alpha (the new alpha value for that pixel) is calculated as:
 *
 *          float alpha =  srcTopAlpha + (1.0 - srcTopAlpha) * srcBottomAlpha
 *
 *      For planar data, you need to calculate alpha yourself ahead of time and provide that as an argument to this function. 
 *      This can be done using: 
 *
 *          vImagePremultipliedAlphaBlend_Planar(8/F)( srcTopAlpha, srcTopAlpha, srcBottomAlpha, alpha, kvImageNoFlags );
 *
 *      For ARGB interleaved data, this is done for you while the other calculations are taking place. Somewhat better alpha precision
 *      is available for ARGB8888 data compared to Planar_8 data, because the result alpha channel can be represented with fractional precision.
 *
 *      For calculations involving 8-bit integer data, the calculation is done in a fixed point representation using signed 0.15 fixed point
 *      internal representation with saturated clipping, to prevent results > 1.0 and results < 0. The calculation is actually done with negative
 *      numbers internally to make sure that -1.0 is representable where needed.  Values are rounded up by 1/2 ulp before truncation.
 *
 *      This function will work in place.
 */
vImage_Error	vImageAlphaBlend_Planar8( const vImage_Buffer *srcTop, const vImage_Buffer *srcTopAlpha, const vImage_Buffer *srcBottom, const vImage_Buffer *srcBottomAlpha, const vImage_Buffer *alpha, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
vImage_Error	vImageAlphaBlend_PlanarF( const vImage_Buffer *srcTop, const vImage_Buffer *srcTopAlpha, const vImage_Buffer *srcBottom, const vImage_Buffer *srcBottomAlpha, const vImage_Buffer *alpha, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
vImage_Error	vImageAlphaBlend_ARGB8888( const vImage_Buffer *srcTop, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
vImage_Error	vImageAlphaBlend_ARGBFFFF( const vImage_Buffer *srcTop, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*
 *  vImagePremultipliedAlphaBlend_*
 *
 *  This is a premultiplied alpha compositing function.  
 *      For each color channel:
 *
 *          float destColor = srcTopColor  + (1.0 - srcTopAlpha) * srcBottomColor;
 *
 *      Similarly, the output alpha channel (the new alpha value for that pixel) can be calculated as:
 *
 *          float alpha =  srcTopAlpha + (1.0 - srcTopAlpha) * srcBottomAlpha
 *
 *      The alpha values are presumed to be normalized over the range 0.0f ... 1.0f. 
 *
 *      For calculations involving 8-bit integer data, the calculation is done with an additional rounding step 
 *      followed by division by 255:
 *
 *          uint8_t destColor = (srcTopColor * 255  + (255 - srcTopAlpha) * srcBottomColor + 127) / 255;
 *
 *      Similarly, the output alpha channel (the new alpha value for that pixel) can be calculated as:
 *
 *          uint8_t destAlpha =  (srcTopAlpha * 255 + (255 - srcTopAlpha) * srcBottomAlpha + 127 ) / 255;
 *
 *      This function will work in place.
 */
vImage_Error	vImagePremultipliedAlphaBlend_Planar8( const vImage_Buffer *srcTop, const vImage_Buffer *srcTopAlpha, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
vImage_Error	vImagePremultipliedAlphaBlend_PlanarF( const vImage_Buffer *srcTop, const vImage_Buffer *srcTopAlpha, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
vImage_Error	vImagePremultipliedAlphaBlend_ARGB8888( const vImage_Buffer *srcTop, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
vImage_Error	vImagePremultipliedAlphaBlend_ARGBFFFF( const vImage_Buffer *srcTop, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*
 *  vImagePremultiplyData_*
 *
 *  This function multiplies color channels by the alpha channel.  
 *      For each color channel:
 *
 *          float destColor = src * alpha;
 *          float destAlpha = alpha;            //For interleaved formats only. 
 *
 *      For calculations involving 8-bit integer data, the calculation is done in a fixed point representation using signed 0.15 fixed point
 *      internal representation with saturated clipping, to prevent results > 1.0 and results < 0. The calculation is actually done with negative
 *      numbers internally to make sure that -1.0 is representable where needed.  Values are rounded up by 1/2 ulp before truncation.
 *
 *      This function will work in place.
 */
vImage_Error	vImagePremultiplyData_Planar8( const vImage_Buffer *src, const vImage_Buffer *alpha, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
vImage_Error	vImagePremultiplyData_PlanarF( const vImage_Buffer *src, const vImage_Buffer *alpha, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
vImage_Error	vImagePremultiplyData_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
vImage_Error	vImagePremultiplyData_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
vImage_Error	vImagePremultiplyData_RGBA8888( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
vImage_Error	vImagePremultiplyData_RGBAFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*
 *  vImageUnpremultiplyData_*
 *
 *  This function multiplies color channels by the alpha channel.  
 *      For each color channel:
 *
 *          float destColor = src / srcAlpha;
 *          float destAlpha = alpha;            //For interleaved formats only
 *
 *      For calculations involving 8-bit integer data, the calculation is done in a fixed point representation using signed 0.15 fixed point
 *      internal representation with saturated clipping, to prevent results > 1.0 and results < 0. The calculation is actually done with negative
 *      numbers internally to make sure that -1.0 is representable where needed.  Values are rounded up by 1/2 ulp before truncation.
 *
 *      This function will work in place.
 */
vImage_Error	vImageUnpremultiplyData_Planar8( const vImage_Buffer *src, const vImage_Buffer *alpha, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
vImage_Error	vImageUnpremultiplyData_PlanarF( const vImage_Buffer *src, const vImage_Buffer *alpha, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
vImage_Error	vImageUnpremultiplyData_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
vImage_Error	vImageUnpremultiplyData_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
vImage_Error	vImageUnpremultiplyData_RGBA8888( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
vImage_Error	vImageUnpremultiplyData_RGBAFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*
 *  vImageConstPremultipliedAlphaBlend_*
 *
 *  This is a premultiplied alpha compositing function using a constant for alpha over the whole image.
 *  Color data from both images is presumed to be already premultiplied by its own per-pixel alpha.
 *
 *      For each color channel:
 *
 *          float destColor = srcTopColor * constAlpha  + (1.0 - srcTopAlpha  * constAlpha) * srcBottomColor;
 *
 *      Similarly, the output alpha channel (the new alpha value for that pixel) can be calculated as:
 *
 *          float alpha =  srcTopAlpha * constAlpha + (1.0 - srcTopAlpha * constAlpha) * srcBottomAlpha
 *
 *      The alpha values are presumed to be normalized over the range 0.0f ... 1.0f. 
 *
 *      For calculations involving 8-bit integer data, the calculation is done with an additional rounding step 
 *      followed by division by 255:
 *
 *          uint8_t destColor = (srcTopColor * constAlpha * 255  + (255*255 - srcTopAlpha * constAlpha) * srcBottomColor + 127*255) / (255*255);
 *
 *      Similarly, the output alpha channel (the new alpha value for that pixel) can be calculated as:
 *
 *          uint8_t destAlpha =  (srcTopAlpha * constAlpha * 255 + (255*255 - srcTopAlpha * constAlpha) * srcBottomAlpha + 127*255 ) / (255*255);
 *
 *      This function will work in place.
 */
vImage_Error	vImagePremultipliedConstAlphaBlend_Planar8( const vImage_Buffer *srcTop, Pixel_8 constAlpha, const vImage_Buffer *srcTopAlpha, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
vImage_Error	vImagePremultipliedConstAlphaBlend_PlanarF( const vImage_Buffer *srcTop, Pixel_F constAlpha, const vImage_Buffer *srcTopAlpha, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
vImage_Error	vImagePremultipliedConstAlphaBlend_ARGB8888( const vImage_Buffer *srcTop, Pixel_8 constAlpha, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
vImage_Error	vImagePremultipliedConstAlphaBlend_ARGBFFFF( const vImage_Buffer *srcTop, Pixel_F constAlpha, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 * Mixed non-premultiplied and premultiplied alpha blend
 * Top buffer is non-premultiplied. Bottom buffer is premultiplied. Dest buffer is premultiplied. Works in place.
 *
 *      result = srcTop * srcTopAlpha + (1 - srcTopAlpha) * srcBottom
 *
 * For integer results, it is calculated as 
 *
 *      result = (srcTop * srctopAlpha + (255 - srcTopAlpha) * bottomAlpha + 127 ) / 255;
 *
 * This function will work in place as long as the src and dest buffer overlap exactly. 
 * The src buffers must be at least as large as the dest buffer in each dimension. (src.height >= dest.height && src.width >= dest.width)
 *
 *  To calculate the alpha result for the Planar cases, use 
 *
 *      vImagePremultipliedAlphaBlend_Planar8( srcTopAlpha, srcTopAlpha, srcBottomAlpha, dest, flags );
 *
 *  Will work in place. 
 */
vImage_Error	vImageAlphaBlend_NonpremultipliedToPremultiplied_Planar8( const vImage_Buffer *srcTop, const vImage_Buffer *srcTopAlpha, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
vImage_Error	vImageAlphaBlend_NonpremultipliedToPremultiplied_PlanarF( const vImage_Buffer *srcTop, const vImage_Buffer *srcTopAlpha, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
vImage_Error	vImageAlphaBlend_NonpremultipliedToPremultiplied_ARGB8888( const vImage_Buffer *srcTop, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
vImage_Error	vImageAlphaBlend_NonpremultipliedToPremultiplied_ARGBFFFF( const vImage_Buffer *srcTop, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*
 *  ClipToAlpha
 *  
 *  For each pixel, each color channel shall be set to the smaller of the color channel or alpha value for that pixel. 
 *
 *          alpha_result = alpha
 *          color_result = MIN( color, alpha )
 *
 *  This function will work in place.
 */
vImage_Error vImageClipToAlpha_Planar8( const vImage_Buffer *src, const vImage_Buffer *alpha, const vImage_Buffer *dest, vImage_Flags flags ) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
vImage_Error vImageClipToAlpha_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
vImage_Error vImageClipToAlpha_PlanarF( const vImage_Buffer *src,  const vImage_Buffer *alpha,  const vImage_Buffer *dest, vImage_Flags flags ) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
vImage_Error vImageClipToAlpha_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



#ifdef __cplusplus
}
#endif

#endif /* vImage_ALPHA_H */


