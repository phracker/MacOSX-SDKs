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
 *      For ARGB interleaved data, this is done for you while the other calculations are taking place. Somewhat better alpha 
 *      precision is available for ARGB8888 data compared to Planar_8 data, because the result alpha channel can be represented
 *      with fractional precision.
 *
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 *      The ARGB versions work for all 4 channel 8-bit / channel image formats with alpha first in memory.
 */
vImage_Error	vImageAlphaBlend_Planar8( const vImage_Buffer *srcTop, const vImage_Buffer *srcTopAlpha, const vImage_Buffer *srcBottom, const vImage_Buffer *srcBottomAlpha, const vImage_Buffer *alpha, const vImage_Buffer *dest, vImage_Flags flags )  VIMAGE_NON_NULL(1,2,3,4,5,6)  __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error	vImageAlphaBlend_PlanarF( const vImage_Buffer *srcTop, const vImage_Buffer *srcTopAlpha, const vImage_Buffer *srcBottom, const vImage_Buffer *srcBottomAlpha, const vImage_Buffer *alpha, const vImage_Buffer *dest, vImage_Flags flags )  VIMAGE_NON_NULL(1,2,3,4,5,6)  __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error	vImageAlphaBlend_ARGB8888( const vImage_Buffer *srcTop, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3)   __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error	vImageAlphaBlend_ARGBFFFF( const vImage_Buffer *srcTop, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3)  __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

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
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 *      The ARGB versions work for all 4 channel 8-bit / channel image formats with alpha first in memory.
 *      The BGRA versions work for all 4 channel 8-bit / channel image formats with alpha last in memory.
 */
vImage_Error	vImagePremultipliedAlphaBlend_Planar8( const vImage_Buffer *srcTop, const vImage_Buffer *srcTopAlpha, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags )  VIMAGE_NON_NULL(1,2,3,4)  __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error	vImagePremultipliedAlphaBlend_PlanarF( const vImage_Buffer *srcTop, const vImage_Buffer *srcTopAlpha, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags )  VIMAGE_NON_NULL(1,2,3,4)  __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error	vImagePremultipliedAlphaBlend_ARGB8888( const vImage_Buffer *srcTop, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3)   __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error	vImagePremultipliedAlphaBlend_ARGBFFFF( const vImage_Buffer *srcTop, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3)   __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error	vImagePremultipliedAlphaBlend_BGRA8888( const vImage_Buffer *srcTop, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3)   __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_5_0 );
vImage_Error	vImagePremultipliedAlphaBlend_BGRAFFFF( const vImage_Buffer *srcTop, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3)   __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_5_0 );
#define         vImagePremultipliedAlphaBlend_RGBA8888( _srcTop, _srcBottom, _dest, _flags )    vImagePremultipliedAlphaBlend_BGRA8888((_srcTop), (_srcBottom), (_dest), (_flags))
#define         vImagePremultipliedAlphaBlend_RGBAFFFF( _srcTop, _srcBottom, _dest, _flags )    vImagePremultipliedAlphaBlend_BGRAFFFF((_srcTop), (_srcBottom), (_dest), (_flags))

/*
 *  vImagePremultipliedAlphaBlendWithPermute_ARGB8888
 *
 *  This function does 3 things.
 *  1. Changes the order of channels of srcTop according to permuteMap.
 *  2. A premultiplied alpha compositing.
 *  3. Set destA to 0xFF when makeDestAlphaOpaque is true.
 *
 *  permuteMap[i] = 0, 1, 2, or 3 to specify how we permute each channel in srcTop.
 *
 *  permuteMap[0] tells which channel in srcTop XXXX8888 will be used as A.
 *  permuteMap[1] tells which channel in srcTop XXXX8888 will be used as R.
 *  permuteMap[2] tells which channel in srcTop XXXX8888 will be used as G.
 *  permuteMap[3] tells which channel in srcTop XXXX8888 will be used as B.
 *
 *  This permuteMap lets us to cover any channel order for the top and bottom images.
 *  For example,
 *
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
 *
 *
 *  srcBottom will have the same pixel format (ARGB8888) as dest.
 *
 *
 *  The per-pixel operation is:
 *
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
 *
 *  Operands:
 *  ---------
 *  srcTop     : A pointer to vImage_Buffer that references 8-bit XXXX interleaved source top image.
 *  srcBottom  : A pointer to vImage_Buffer that references 8-bit ARGB interleaved source bottom image.
 *  dest       : A pointer to vImage_Buffer that references 8-bit ARGB interleaved destination image.
 *  permuteMap : Values that can be used to switch the channel order of the source top image.
 *  makeDestAlphaOpaque  : A boolean to set destA into 0xFF when it's true.
 *
 *  Flags:
 *  ------
 *      kvImageGetTempBufferSize    Returns 0. Does no work.
 *      kvImageDoNotTile            Disables internal multithreading, if any.
 *
 *  Return Value:
 *  -------------
 *      kvImageNoError                  Is returned when there was no error.
 *      kvImageRoiLargerThanInputBuffer The destination buffers are larger than the source buffer.
 *      kvImageBufferSizeMismatch       Is returned when there is a mismatch in width & height of srcTop and srcBottom.
 *      kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 *      kvImageInvalidParameter         Is returned when the values in permuteMap[i] is not one of 0, 1, 2, or 3.
 *
 *  This function can work in place.
 *
 */

vImage_Error vImagePremultipliedAlphaBlendWithPermute_ARGB8888(const vImage_Buffer *srcTop, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, const uint8_t permuteMap[4], bool makeDestAlphaOpaque, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,4) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );



/*
 *  vImagePremultipliedAlphaBlendWithPermute_RGBA8888
 *
 *  This function does 3 things.
 *  1. Changes the order of channels of srcTop according to permuteMap.
 *  2. A premultiplied alpha compositing.
 *  3. Set destA to 0xFF when makeDestAlphaOpaque is true.
 *
 *  permuteMap[i] = 0, 1, 2, or 3 to specify how we permute each channel in srcTop.
 *
 *  permuteMap[0] tells which channel in srcTop XXXX8888 will be used as A.
 *  permuteMap[1] tells which channel in srcTop XXXX8888 will be used as R.
 *  permuteMap[2] tells which channel in srcTop XXXX8888 will be used as G.
 *  permuteMap[3] tells which channel in srcTop XXXX8888 will be used as B.
 *
 *  This permuteMap lets us to cover any channel order for the top and bottom images.
 *  For example,
 *
 *      PremultipliedAlphaBlend(srcTop_ARGB8888, srcBottom_RGBA8888) -> dest_RGBA8888
 *                     will be covered by permuteMap[4] = {0, 1, 2, 3}
 *
 *      PremultipliedAlphaBlend(srcTop_RGBA8888, srcBottom_RGBA8888) -> dest_RGBA8888
 *                     will be covered by permuteMap[4] = {3, 0, 1, 2}
 *
 *      PremultipliedAlphaBlend(srcTop_ABGR8888, srcBottom_RGBA8888) -> dest_RGBA8888
 *                     will be covered by permuteMap[4] = {0, 3, 2, 1}
 *
 *      PremultipliedAlphaBlend(srcTop_BGRA8888, srcBottom_RGBA8888) -> dest_RGBA8888
 *                     will be covered by permuteMap[4] = {3, 2, 1, 0}
 *
 *
 *  srcBottom will have the same pixel format (RGBA8888) as dest.
 *
 *
 *  The per-pixel operation is:
 *
 *  uint8_t *srcTop, *srcBottom, *dest;
 *  uint8_t srcTopA, srcTopR, srcTopG, srcTopB;
 *  uint8_t srcBottomA, srcBottomR, srcBottomG, srcBottomB;
 *  uint8_t destA, destR, destG, destB;
 *
 *  srcTopA = srcTop[ permuteMapTop[0] ];
 *  srcTopR = srcTop[ permuteMapTop[1] ];
 *  srcTopG = srcTop[ permuteMapTop[2] ];
 *  srcTopB = srcTop[ permuteMapTop[3] ];
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
 *      dest[0] = destR;
 *      dest[1] = destG;
 *      dest[2] = destB;
 *      dest[3] = 0xFF;
 *  }
 *  else
 *  {
 *      destA = (srcTopA * 255 + (255 - srcTopA) * srcBottomA + 127) / 255;
 *
 *      dest[0] = destR;
 *      dest[1] = destG;
 *      dest[2] = destB;
 *      dest[3] = destA;
 *  }
 *
 *
 *  Operands:
 *  ---------
 *  srcTop               : A pointer to vImage_Buffer that references 8-bit XXXX interleaved source top image.
 *  srcBottom            : A pointer to vImage_Buffer that references 8-bit RGBA interleaved source bottom image.
 *  dest                 : A pointer to vImage_Buffer that references 8-bit RGBA interleaved destination image.
 *  permuteMap           : Values that can be used to switch the channel order of the source top image.
 *  makeDestAlphaOpaque  : A boolean to set destA into 0xFF when it's true.
 *
 *  Flags:
 *  ------
 *      kvImageGetTempBufferSize    Returns 0. Does no work.
 *      kvImageDoNotTile            Disables internal multithreading, if any.
 *
 *  Return Value:
 *  -------------
 *      kvImageNoError                  Is returned when there was no error.
 *      kvImageRoiLargerThanInputBuffer The destination buffers are larger than the source buffer.
 *      kvImageBufferSizeMismatch       Is returned when there is a mismatch in width & height of srcTop and srcBottom.
 *      kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 *      kvImageInvalidParameter         Is returned when the values in permuteMap[i] is not one of 0, 1, 2, or 3.
 *
 *  This function can work in place.
 *
 */

vImage_Error vImagePremultipliedAlphaBlendWithPermute_RGBA8888(const vImage_Buffer *srcTop, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, const uint8_t permuteMap[4], bool makeDestAlphaOpaque, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,4) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );

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
 *      numbers internally to make sure that -1.0 is representable where needed.  Values are rounded up by 1/2 ulp before truncation. e.g.:
 *
 *          premul_8( a, c ) =  (a * c + 127) / 255
 *          premul_16U( a, c ) =  (a * c + 32767) / 65535
 *
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 *      Pass kvImageDoNotTile to prevent multithreading.
 *      The ARGB versions work for all 4 channel 8-bit / channel image formats with alpha first in memory.
 *      The RGBA versions work for all 4 channel 8-bit / channel image formats with alpha last in memory.
 */
vImage_Error	vImagePremultiplyData_Planar8( const vImage_Buffer *src, const vImage_Buffer *alpha, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3)   __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error	vImagePremultiplyData_PlanarF( const vImage_Buffer *src, const vImage_Buffer *alpha, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3)   __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error	vImagePremultiplyData_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)   __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error	vImagePremultiplyData_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)   __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error	vImagePremultiplyData_RGBA8888( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)   __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
vImage_Error	vImagePremultiplyData_RGBAFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)   __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
#define         vImagePremultiplyData_BGRA8888( _src, _dest, _flags )           vImagePremultiplyData_RGBA8888((_src), (_dest), (_flags))
#define         vImagePremultiplyData_BGRAFFFF( _src, _dest, _flags )           vImagePremultiplyData_RGBAFFFF((_src), (_dest), (_flags)) 

// The ARGB16U type is alpha, red, green, blue (memory order).  Each channel in the pixel is a uint16_t fixed point value 
// in the range [0, 65536], which map to the pixel intensities [0.0, 1.0]. 
vImage_Error	vImagePremultiplyData_ARGB16U( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_6_0 );  
vImage_Error	vImagePremultiplyData_RGBA16U( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_6_0 );
vImage_Error    vImagePremultiplyData_ARGB16Q12( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
vImage_Error    vImagePremultiplyData_RGBA16Q12( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
#define         vImagePremultiplyData_BGRA16U( _src, _dest, _flags )           vImagePremultiplyData_RGBA16U((_src), (_dest), (_flags))
    
/*
 *  vImageUnpremultiplyData_*
 *
 *  This function multiplies color channels by the alpha channel.  
 *      For each color channel:
 *
 *          float destColor = src / srcAlpha;   // according to current rounding mode
 *          float destAlpha = alpha;            //For interleaved formats only
 *
 *      For calculations involving Planar8 and interleaved 8888 formats, the results will be in accordance with the following formula:
 *
 *          uint8_t srcColor, srcAlpha;     // input color data
 *          uint8_t destColor = srcAlpha == 0 ? 0 : ( 2 * 255 * MIN( srcColor, srcAlpha) + srcAlpha ) / (2 * srcAlpha);
 *          uint8_t destAlpha = srcAlpha;
 *
 *      ...which is the nearest unpremultiplied result, with clamping to ensure no modulo overflow in cases where srcColor > srcAlpha.
 *      In the division by zero case, the returned color value is 0.  The accuracy and speed of these functions were improved for X.6.6.
 *      Before that, the Planar8 and 8888 functions were a bit slower (~2/3) and in about 1% of cases (all near the halfway point), 
 *      rounded down where it now rounds up. 
 *
 *      It should be self-evident that only the positioning of the alpha channel is important for interleaved formats for these functions. 
 *      So, for example, vImageUnpremultiplyData_RGBA8888 will work for BGRA data too, because the alpha channel is in the same place.
 *
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 *      Pass kvImageDoNotTile to prevent multithreading.
 *      The ARGB versions work for all 4 channel 8-bit / channel image formats with alpha first in memory.
 *      The RGBA versions work for all 4 channel 8-bit / channel image formats with alpha last in memory.
 */
vImage_Error	vImageUnpremultiplyData_Planar8( const vImage_Buffer *src, const vImage_Buffer *alpha, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3)   __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error	vImageUnpremultiplyData_PlanarF( const vImage_Buffer *src, const vImage_Buffer *alpha, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3)    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error	vImageUnpremultiplyData_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error	vImageUnpremultiplyData_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error	vImageUnpremultiplyData_RGBA8888( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
vImage_Error	vImageUnpremultiplyData_RGBAFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
#define         vImageUnpremultiplyData_BGRA8888( _src, _dest, _flags )             vImageUnpremultiplyData_RGBA8888((_src), (_dest), (_flags))
#define         vImageUnpremultiplyData_BGRAFFFF( _src, _dest, _flags )             vImageUnpremultiplyData_RGBAFFFF((_src), (_dest), (_flags))

vImage_Error	vImageUnpremultiplyData_ARGB16U( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_6_0 );
vImage_Error	vImageUnpremultiplyData_RGBA16U( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_6_0 );
vImage_Error    vImageUnpremultiplyData_ARGB16Q12( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
vImage_Error    vImageUnpremultiplyData_RGBA16Q12( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
#define         vImageUnpremultiplyData_BGRA16U( _src, _dest, _flags )             vImageUnpremultiplyData_RGBA16U((_src), (_dest), (_flags))

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
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 *      The ARGB versions work for all 4 channel 8-bit / channel image formats with alpha first in memory.
 */
vImage_Error	vImagePremultipliedConstAlphaBlend_Planar8( const vImage_Buffer *srcTop, Pixel_8 constAlpha, const vImage_Buffer *srcTopAlpha, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,3,4,5)    __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
vImage_Error	vImagePremultipliedConstAlphaBlend_PlanarF( const vImage_Buffer *srcTop, Pixel_F constAlpha, const vImage_Buffer *srcTopAlpha, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,3,4,5)    __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
vImage_Error	vImagePremultipliedConstAlphaBlend_ARGB8888( const vImage_Buffer *srcTop, Pixel_8 constAlpha, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,3,4)    __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
vImage_Error	vImagePremultipliedConstAlphaBlend_ARGBFFFF( const vImage_Buffer *srcTop, Pixel_F constAlpha, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,3,4)    __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );


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
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 *  The ARGB versions work for all 4 channel 8-bit / channel image formats with alpha first in memory.
 */
vImage_Error	vImageAlphaBlend_NonpremultipliedToPremultiplied_Planar8( const vImage_Buffer *srcTop, const vImage_Buffer *srcTopAlpha, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,4)    __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
vImage_Error	vImageAlphaBlend_NonpremultipliedToPremultiplied_PlanarF( const vImage_Buffer *srcTop, const vImage_Buffer *srcTopAlpha, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,4)    __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
vImage_Error	vImageAlphaBlend_NonpremultipliedToPremultiplied_ARGB8888( const vImage_Buffer *srcTop, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3)    __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
vImage_Error	vImageAlphaBlend_NonpremultipliedToPremultiplied_ARGBFFFF( const vImage_Buffer *srcTop, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3)    __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

/*
 *  ClipToAlpha
 *  
 *  For each pixel, each color channel shall be set to the smaller of the color channel or alpha value for that pixel. 
 *
 *          alpha_result = alpha
 *          color_result = MIN( color, alpha )
 *
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 *  The ARGB versions work for all 4 channel 8-bit / channel image formats with alpha first in memory.
 *  The RGBA versions work for all 4 channel 8-bit / channel image formats with alpha last in memory.
 */
vImage_Error vImageClipToAlpha_Planar8( const vImage_Buffer *src, const vImage_Buffer *alpha, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
vImage_Error vImageClipToAlpha_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
vImage_Error vImageClipToAlpha_PlanarF( const vImage_Buffer *src,  const vImage_Buffer *alpha,  const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
vImage_Error vImageClipToAlpha_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
vImage_Error vImageClipToAlpha_RGBA8888( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_6_0 );
vImage_Error vImageClipToAlpha_RGBAFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_6_0 );
#define vImageClipToAlpha_BGRA8888(_src, _dest, _flags)   vImageClipToAlpha_RGBA8888((_src), (_dest), (_flags)) 
#define vImageClipToAlpha_BGRAFFFF(_src, _dest, _flags)   vImageClipToAlpha_RGBAFFFF((_src), (_dest), (_flags)) 

/*
 * See also the vImageFlatten APIs in Conversion.h for compositing an image against a constant color opaque background.
 */

#ifdef __cplusplus
}
#endif

#endif /* vImage_ALPHA_H */


