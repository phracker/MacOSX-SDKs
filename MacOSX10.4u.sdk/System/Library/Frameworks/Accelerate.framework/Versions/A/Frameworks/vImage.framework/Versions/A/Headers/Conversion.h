/*
 *  Conversion.h
 *  vImage_Framework
 *
 *  Copyright (c) 2003 Apple Computer. All rights reserved.
 *
 */

#ifndef VIMAGE_CONVERSION_H
#define VIMAGE_CONVERSION_H

#include <vImage/vImage_Types.h>




#ifdef __cplusplus
extern "C" {
#endif

/*
 * vImageClip_PlanarF: 
 *         Read floating point pixels in the source buffer. For each pixel, do the following:
 *
 *         if( pixel > maxFloat )
 *             pixel = maxFloat;
 *         if( pixel < minFloat )
 *             pixel = minFloat;
 *
 *  will work in place.
 */
vImage_Error vImageClip_PlanarF(const vImage_Buffer* src, const vImage_Buffer* dest, Pixel_F maxFloat, Pixel_F minFloat, vImage_Flags flags)    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*
 *  vImageConvert_Planar8toPlanarF:  
 *         Convert an array of 8 bit integer data to floating point data. For each pixel, do the following:
 *
 *         float result = (maxFloat - minFloat) * (float) srcPixel / 255.0  + minFloat
 *
 *         You can use this for ARGB8888 -> ARGBFFFF conversions by simply multiplying the width of the vImage_Buffer by 4 (for 4 channels)
 *
 *  will not work in place.
 */
vImage_Error vImageConvert_Planar8toPlanarF(const vImage_Buffer *src, const vImage_Buffer *dest, Pixel_F maxFloat, Pixel_F minFloat, vImage_Flags flags)    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*
 *  vImageConvert_PlanarFtoPlanar8:  
 *         Convert an array of floating point data to 8 bit integer data. For each pixel, do the following:
 *
 *         uint8_t result = SATURATED_CLIP_0_to_255( 255.0f * ( srcPixel - minFloat ) / (maxFloat - minFloat) + 0.5f );
 *
 *         You can use this for ARGBFFFF -> ARGB8888 conversions by simply multiplying the width of the vImage_Buffer by 4 (for 4 channels)
 *
 *  will work in place.
 */
vImage_Error vImageConvert_PlanarFtoPlanar8(const vImage_Buffer *src, const vImage_Buffer *dest, Pixel_F maxFloat, Pixel_F minFloat, vImage_Flags flags)    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*  
 *  vImageConvert_Planar8toARGB8888:
 *      Interleave 4 planar 8 bit integer buffers to make a Interleaved 4 channel ARGB8888 buffer
 *      For each pixel in {srcA, srcR, srcG, srcB }:
 *
 *          Pixel_88888 result = { pixelFromSrcA, pixelFromSrcR, pixelFromSrcG, pixelFromSrcB } 
 *
 *  will not work in place.
 */
vImage_Error vImageConvert_Planar8toARGB8888(const vImage_Buffer *srcA, const vImage_Buffer *srcR, const vImage_Buffer *srcG, const vImage_Buffer *srcB, const vImage_Buffer *dest, vImage_Flags flags)    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*  
 *  vImageConvert_PlanarFtoARGBFFFF:
 *      Interleave 4 planar floating point buffers to make a Interleaved 4 channel ARGBFFFF buffer
 *      For each pixel in {srcA, srcR, srcG, srcB }:
 *
 *          Pixel_FFFF result = { pixelFromSrcA, pixelFromSrcR, pixelFromSrcG, pixelFromSrcB } 
 *
 *  will not work in place.
 */
vImage_Error vImageConvert_PlanarFtoARGBFFFF(const vImage_Buffer *srcA, const vImage_Buffer *srcR, const vImage_Buffer *srcG, const vImage_Buffer *srcB, const vImage_Buffer *dest, vImage_Flags flags)    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*
 *  vImageConvert_ARGB8888toPlanar8:
 *      Deinterleave a ARGB interleaved vImage_Buffer to form 4 planar 8-bit integer buffers. 
 *      For each pixel in srcARGB:
 *
 *          Pixel_8 destAResult = srcARGBPixel[0];
 *          Pixel_8 destRResult = srcARGBPixel[1];
 *          Pixel_8 destGResult = srcARGBPixel[2];
 *          Pixel_8 destBResult = srcARGBPixel[3];
 *
 *  will not work in place.
 */
vImage_Error vImageConvert_ARGB8888toPlanar8(const vImage_Buffer *srcARGB, const vImage_Buffer *destA, const vImage_Buffer *destR, const vImage_Buffer *destG, const vImage_Buffer *destB, vImage_Flags flags)    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*
 *  vImageConvert_ARGBFFFFtoPlanarF:
 *      Deinterleave a ARGB interleaved vImage_Buffer to form 4 planar floating point buffers. 
 *      For each pixel in srcARGB:
 *
 *          Pixel_F destAResult = srcARGBPixel[0];
 *          Pixel_F destRResult = srcARGBPixel[1];
 *          Pixel_F destGResult = srcARGBPixel[2];
 *          Pixel_F destBResult = srcARGBPixel[3];
 *
 *  will not work in place.
 */
vImage_Error vImageConvert_ARGBFFFFtoPlanarF(const vImage_Buffer *srcARGB, const vImage_Buffer *destA, const vImage_Buffer *destR, const vImage_Buffer *destG, const vImage_Buffer *destB, vImage_Flags flags)    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*
 * vImageConvert_ChunkyToPlanar8 
 * vImageConvert_PlanarToChunky8 
 * vImageConvert_ChunkyToPlanarF
 * vImageConvert_PlanarToChunkyF
 *
 *  These functions convert between nearly arbitrary interleaved data formats that vImage doesn't support to/from planar data formats that it 
 *  does support. N planar arrays are interleaved to make (or are made made by deinterleaving) a N channel packed interleaved buffer with pixels
 *  that are {srcStrideBytes, destStrideBytes} bytes in size. Valid data channels are assumed to be at the front of each interleaved pixel.
 *
 *  Performance advisory:
 *  =====================
 *  These functions are too flexible to vectorize every case. When appropriate, it is suggested you use the other 
 *  special purpose conversion functions. If you know what your data formats are ahead of time, it is
 *  likely you can write your own special purpose conversion function that is faster, even in scalar code.  
 *  These functions are provided as a convenience. 
 */
vImage_Error vImageConvert_ChunkyToPlanar8( const void *srcChannels[], const vImage_Buffer *destPlanarBuffers[], unsigned int channelCount, size_t srcStrideBytes, vImagePixelCount srcWidth, vImagePixelCount srcHeight, size_t srcRowBytes, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
vImage_Error vImageConvert_PlanarToChunky8( const vImage_Buffer *srcPlanarBuffers[], void *destChannels[], unsigned int channelCount, size_t destStrideBytes, vImagePixelCount destWidth, vImagePixelCount destHeight, size_t destRowBytes, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
vImage_Error vImageConvert_ChunkyToPlanarF( const void *srcChannels[], const vImage_Buffer *destPlanarBuffers[], unsigned int channelCount, size_t srcStrideBytes, vImagePixelCount srcWidth, vImagePixelCount srcHeight, size_t srcRowBytes, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
vImage_Error vImageConvert_PlanarToChunkyF( const vImage_Buffer *srcPlanarBuffers[], void *destChannels[], unsigned int channelCount, size_t destStrideBytes, vImagePixelCount destWidth, vImagePixelCount destHeight, size_t destRowBytes, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*
 * vImageConvert_16SToF
 *      Convert a planar (or interleaved -- multiply vImage_Buffer.width by 4) vImage_Buffer of 16 bit signed ints to a buffer containing floating point values.
 *      For each 16 bit pixel in src:
 *
 *          float result = (float) srcPixel * scale + offset
 *
 *      To convert 4 channel interleaved signed 16 bit data to ARGB_FFFF, simply multiply the vImage_Buffer.width by 4.
 *
 *  will not work in place.
 */
vImage_Error vImageConvert_16SToF( const vImage_Buffer *src, const vImage_Buffer *dest, float offset, float scale, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*
 * vImageConvert_16UToF
 *      Convert a planar (or interleaved -- multiply vImage_Buffer.width by 4) vImage_Buffer of 16 bit unsigned ints to a buffer containing floating point values.
 *      For each 16 bit pixel in src:
 *
 *          float result = (float) srcPixel * scale + offset
 *
 *      To convert 4 channel interleaved signed 16 bit data to ARGB_FFFF, simply multiply the vImage_Buffer.width by 4.
 *
 *  will not work in place.
 */
vImage_Error vImageConvert_16UToF( const vImage_Buffer *src, const vImage_Buffer *dest, float offset, float scale, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*
 *  vImageConvert_FTo16S:
 *      Convert a planar (or interleaved -- multiply vImage_Buffer.width by 4) vImage_Buffer of floating point values to a buffer of 16 bit signed ints.
 *      For each floating point pixel in src:
 *
 *          int16_t result = SATURATED_CLIP_SHRT_MIN_to_SHRT_MAX( (srcPixel - offset) / scale  + 0.5f);      
 *
 *  Programmer's note:
 *      The scale and offset here are designed to be the same offset and scale used for the vImageConvert_16SToF conversion.
 *      For a lossless round trip (within the limits of floating point precision), use the same scale and offset values 
 *      in both directions:
 *
 *              vImageConvert_16SToF( int16_buffer, float_buffer, myOffset, myScale, kvImageNoFlags );   //Convert to float
 *              vImageConvert_FTo16S( float_buffer, int16_buffer, myOffset, myScale, kvImageNoFlags );   //Convert back to int16_t
 *
 *  will not work in place.
 */
vImage_Error vImageConvert_FTo16S( const vImage_Buffer *src, const vImage_Buffer *dest, float offset, float scale, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*
 *  vImageConvert_FTo16U:
 *      Convert a planar (or interleaved -- multiply vImage_Buffer.width by 4) vImage_Buffer of floating point values to a buffer of 16 bit unsigned ints.
 *      For each floating point pixel in src:
 *
 *          uint16_t result = SATURATED_CLIP_0_to_USHRT_MAX( (srcPixel - offset) / scale  + 0.5f);      
 *
 *  Programmer's note:
 *      The scale and offset here are designed to be the same offset and scale used for the vImageConvert_16UToF conversion.
 *      For a lossless round trip (within the limits of floating point precision), use the same scale and offset values 
 *      in both directions:
 *
 *              vImageConvert_16UToF( uint16_buffer, float_buffer, myOffset, myScale, kvImageNoFlags );   //Convert to float
 *              vImageConvert_FTo16U( float_buffer, uint16_buffer, myOffset, myScale, kvImageNoFlags );   //Convert back to uint16_t
 *
 *  will not work in place.
 */
vImage_Error vImageConvert_FTo16U( const vImage_Buffer *src, const vImage_Buffer *dest, float offset, float scale, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;



/*
 *  vImageTableLookUp_ARGB8888:
 *      Use a lookup table to remap 0...255 values in the source image to a different set of 0...255 values in the destination.
 *      A different lookup table is used for each channel in the ARGB image
 *
 *  will work in place.
 *
 *	Performance Advisory:  For 8-bit monochrome -> ARGB8888  or 8-bit indexed -> ARGB8888 conversions, it is probably significantly faster
 *							to use vImageLookupTable_Planar8toPlanarF. Use the desired ARGB8888 (32 bits/pixel) pixels in place of the planar 
 *							32-bit floats in the lookup table. See vImage/Tiger.h.
 */
vImage_Error vImageTableLookUp_ARGB8888(const vImage_Buffer *src, const vImage_Buffer *dest, const Pixel_8 alphaTable[256], const Pixel_8 redTable[256], const  Pixel_8 greenTable[256], const  Pixel_8 blueTable[256], vImage_Flags flags)    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*
 *  vImageTableLookUp_Planar8:
 *      Use a lookup table to remap 0...255 values in the source image to a different set of 0...255 values in the destination.
 *
 *  will work in place.
 */
vImage_Error vImageTableLookUp_Planar8(const vImage_Buffer *src, const vImage_Buffer *dest, const Pixel_8 table[256], vImage_Flags flags)    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


//origSrc and dest may overlap, if they share the same origin. 
//origSrc should be at least as big as dest
//
// origSrc and dest can be the same buffer
vImage_Error vImageOverwriteChannels_ARGB8888(	const vImage_Buffer *newSrc,       /* A planar buffer */
                                                const vImage_Buffer *origSrc,      /* A ARGB interleaved buffer */
                                                const vImage_Buffer *dest,      /* A ARGB interleaved buffer */
                                                uint8_t copyMask,               /* Copy plane into  0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue */ 
                                                vImage_Flags    flags )		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

//origSrc and dest may overlap, if they share the same origin. 
//origSrc should be at least as big as dest
//
// origSrc and dest can be the same buffer
vImage_Error vImageOverwriteChannels_ARGBFFFF(	const vImage_Buffer *newSrc,       /* A planar buffer */
                                                const vImage_Buffer *origSrc,      /* A ARGB interleaved buffer */
                                                const vImage_Buffer *dest,      /* A ARGB interleaved buffer */
                                                uint8_t copyMask,               /* Copy plane into  0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue */ 
                                                vImage_Flags    flags )		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*
 *  Fill the dest buffer with the scalar value
 */
vImage_Error vImageOverwriteChannelsWithScalar_Planar8(	Pixel_8     scalar,
                                                        const vImage_Buffer *dest,      /* A planar buffer */
                                                        vImage_Flags    flags )		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*
 *  Fill the dest buffer with the scalar value
 */
vImage_Error vImageOverwriteChannelsWithScalar_PlanarF( Pixel_F     scalar,
                                                        const vImage_Buffer *dest,      /* A planar buffer */
                                                        vImage_Flags    flags )		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



//
// Fill a buffer with a color. Use vImageOverwriteChannelsWithScalar_* to fill planar buffers with a color.
//
vImage_Error vImageBufferFill_ARGB8888( const vImage_Buffer *dest, const Pixel_8888 color, vImage_Flags flags ) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
vImage_Error vImageBufferFill_ARGBFFFF( const vImage_Buffer *dest, const Pixel_FFFF color, vImage_Flags flags ) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* vImageOverwriteChannelsWithScalar_ARGB8888
 *
 * 	Fill the color channels (as indicated by copyMask) with the scalar value.
 *	For each pixel in src:
 *
 *		Pixel_8888 srcPixel, destPixel;
 *		int mask;
 *		int i;
 *		
 *		mask = 0x8;
 *		for( i = 0; i < 4; i++ )
 *		{
 *			if( copyMask & mask )
 *				destPixel[i] = scalar;
 *			else
 *				destPixel[i] = srcPixel[i]
 *			
 *			mask = mask >> 1;
 *		}
 *
 *	Bits 0-27 of copyMask must be 0.
 *	The src and dest buffers may overlap, so long as they share the same origin. 
 *	The src buffer must be at least as large as the dest buffer. (src.height >= dest.height && src.width >= dest.width)
 *
 * Will work in place. 
 */
vImage_Error vImageOverwriteChannelsWithScalar_ARGB8888(	Pixel_8     scalar,
                                                                const vImage_Buffer *src,      /* A ARGB interleaved buffer */
                                                                const vImage_Buffer *dest,      /* A ARGB interleaved buffer */
                                                                uint8_t copyMask,               /* Copy plane into  0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue */ 
                                                                vImage_Flags    flags )		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* vImageOverwriteChannelsWithScalar_ARGBFFFF
 *
 * 	Fill the color channels (as indicated by copyMask) with the scalar value.
 *	For each pixel in src:
 *
 *		Pixel_FFFF srcPixel, destPixel;
 *		int mask;
 *		int i;
 *		
 *		mask = 0x8;
 *		for( i = 0; i < 4; i++ )
 *		{
 *			if( copyMask & mask )
 *				destPixel[i] = scalar;
 *			else
 *				destPixel[i] = srcPixel[i]
 *			
 *			mask = mask >> 1;
 *		}
 *
 *	Bits 0-27 of copyMask must be 0.
 *	The src and dest buffers may overlap, so long as they share the same origin. 
 *	The src buffer must be at least as large as the dest buffer. (src.height >= dest.height && src.width >= dest.width)
 *
 * Will work in place. 
 */
vImage_Error vImageOverwriteChannelsWithScalar_ARGBFFFF(	Pixel_F     scalar,
                                                                const vImage_Buffer *src,      /* A ARGB interleaved buffer */
                                                                const vImage_Buffer *dest,      /* A ARGB interleaved buffer */
                                                                uint8_t copyMask,               /* Copy plane into  0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue */ 
                                                                vImage_Flags    flags )		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*
 * Reorder color channels within the buffer according to the permute map.
 * For each pixel in src:
 *
 *	Pixel_8888 srcPixel, result;
 *	for( int i = 0; i < 4; i++ )
 *		result[i] = srcPixel[ permuteMap[i] ];
 *
 * This function will work in place as long as the src and dest buffer overlap exactly. 
 * The src buffer must be at least as large as the dest buffer in each dimension. (src.height >= dest.height && src.width >= dest.width)
 *
 * Will work in place. 
 */
vImage_Error vImagePermuteChannels_ARGB8888(    const vImage_Buffer *src,
                                                const vImage_Buffer *dest,
                                                const uint8_t       permuteMap[4],
                                                vImage_Flags        flags )		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*
 * Reorder color channels within the buffer according to the permute map.
 * For each pixel in src:
 *
 *	Pixel_FFFF srcPixel, result;
 *	for( int i = 0; i < 4; i++ )
 *		result[i] = srcPixel[ permuteMap[i] ];
 *
 * This function will work in place as long as the src and dest buffer overlap exactly. 
 * The src buffer must be at least as large as the dest buffer in each dimension. (src.height >= dest.height && src.width >= dest.width)
 *
 * Will work in place. 
 */
vImage_Error vImagePermuteChannels_ARGBFFFF(    const vImage_Buffer *src,
                                                const vImage_Buffer *dest,
                                                const uint8_t       permuteMap[4],
                                                vImage_Flags        flags )		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
                                                

/*
 *  Convert between 16 bit/pixel ARGB1555 to 32 bit/pixel ARGB8888 format
 *  In the forward direction (ARGB1555->ARGB8888), for each pixel:
 *
 *      Pixel8 alpha =  1bitAlphaChannel * 255;
 *      Pixel8 red   = (5bitRedChannel   * 255 + 15) / 31;
 *      Pixel8 green = (5bitGreenChannel * 255 + 15) / 31;
 *      Pixel8 blue  = (5bitBlueChannel  * 255 + 15) / 31;
 *
 *  Does not work in place
 *
 *  In the reverse direction (ARGB8888->ARGB1555), for each pixel:
 *
 *      uint32_t alpha = (8bitAlphaChannel      + 127) / 255;
 *      uint32_t red   = (8bitRedChannel   * 31 + 127) / 255;
 *      uint32_t green = (8bitGreenChannel * 31 + 127) / 255;
 *      uint32_t blue  = (8bitBlueChannel  * 31 + 127) / 255;
 *      uint16_t ARGB1555pixel =  (alpha << 15) | (red << 10) | (green << 5) | blue;
 *
 *  Does work in place
 */
vImage_Error    vImageConvert_ARGB1555toPlanar8( const vImage_Buffer *src, const vImage_Buffer *destA, const vImage_Buffer *destR, const vImage_Buffer *destG, const vImage_Buffer *destB, vImage_Flags flags )  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
vImage_Error    vImageConvert_ARGB1555toARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags )  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
vImage_Error    vImageConvert_Planar8toARGB1555( const vImage_Buffer *srcA, const vImage_Buffer *srcR, const vImage_Buffer *srcG, const vImage_Buffer *srcB, const vImage_Buffer *dest, vImage_Flags flags )  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
vImage_Error    vImageConvert_ARGB8888toARGB1555( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags )  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
    
/*
 *  Convert between 16 bit/pixel RGB565 to 32 bit/pixel ARGB8888 format
 *  In the forward direction (RGB565->ARGB8888), for each pixel:
 *
 *      Pixel8 alpha = alpha;
 *      Pixel8 red   = (5bitRedChannel   * 255 + 15) / 31;
 *      Pixel8 green = (6bitGreenChannel * 255 + 31) / 63;
 *      Pixel8 blue  = (5bitBlueChannel  * 255 + 15) / 31;
 *
 *  Does not work in place
 *
 *  In the reverse direction (ARGB8888->RGB565), for each pixel:
 *
 *      uint32_t red   = (8bitRedChannel   * 31 + 127) / 255;
 *      uint32_t green = (8bitGreenChannel * 63 + 127) / 255;
 *      uint32_t blue  = (8bitBlueChannel  * 31 + 127) / 255;
 *      uint16_t RGB565pixel =  (red << 11) | (green << 5) | blue;
 *
 *  Does work in place
 */
vImage_Error    vImageConvert_RGB565toPlanar8( const vImage_Buffer *src, const vImage_Buffer *destR, const vImage_Buffer *destG, const vImage_Buffer *destB, vImage_Flags flags )  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
vImage_Error    vImageConvert_RGB565toARGB8888( Pixel_8 alpha, const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags )  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
vImage_Error    vImageConvert_Planar8toRGB565( const vImage_Buffer *srcR, const vImage_Buffer *srcG, const vImage_Buffer *srcB, const vImage_Buffer *dest, vImage_Flags flags )  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
vImage_Error    vImageConvert_ARGB8888toRGB565( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags )  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
    
/*
 *  Convert between 16 bit floats to 32 bit float format.
 *  The 16 bit floating point format is identical to OpenEXR. It has a layout as follows:
 *
 *    16 bits:  seeeeemmmmmmmmmm
 *
 *      1-bit sign | 5 bits of exponent, with a bias of 15 | 10 bits of significand (with 11 bits of significance due to the implicit 1 bit)
 *
 *  NaNs, Infinities and denormals are supported, even on AlitVec.
 *  Per IEEE-754, all signaling NaNs are quieted during the conversion. (OpenEXR-1.2.1 converts SNaNs to SNaNs.)
 *  In the float->16 bit float direction, rounding occurs according to the IEEE-754 standard and current IEEE-754 rounding mode, even in AltiVec.
 *  To set/inspect the current IEEE-754 rounding mode, please see appropriate utilities in fenv.h
 *
 *  vImageConvert_Planar16FtoPlanarF does not work in place. 
 *  vImageConvert_PlanarFtoPlanar16F does work in place, though the contents of the unused half of the buffer are undefined 
 */
vImage_Error    vImageConvert_Planar16FtoPlanarF( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags )  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
vImage_Error    vImageConvert_PlanarFtoPlanar16F( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags )  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
    
/*
 * vImageConvert_16UToPlanar8
 *      Convert a planar (or interleaved -- multiply vImage_Buffer.width by 4) vImage_Buffer of 16 bit unsigned shorts to a buffer containing 8 bit integer values.
 *      For each 16 bit pixel in src:
 *
 *          uint8_t result = (srcPixel * 255 + 32767) / 65535;
 *
 *      To convert 4 channel interleaved unsigned 16 bit data to ARGB_8888, simply multiply the vImage_Buffer.width by 4.
 *
 *  Will work in place, though the contents of the unused half of the source buffer are undefined after conversion.
 */
vImage_Error vImageConvert_16UToPlanar8( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*
 *  vImageConvert_Planar8To16U:
 *      Convert a planar (or interleaved -- multiply vImage_Buffer.width by 4) vImage_Buffer of 8-bit integer values to a buffer of 16 bit unsigned ints.
 *      For each 8-bit pixel in src:
 *
 *          uint16_t result = (srcPixel * 65535 + 127 ) / 255;      
 *
 *  will not work in place.
 */
vImage_Error vImageConvert_Planar8To16U( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*
 *  Convert RGB to ARGB
 *
 *  If premultiply != 0, then 
 *
 *      r = (a * r + 127) / 255
 *      g = (a * g + 127) / 255
 *      b = (a * b + 127) / 255
 *
 *  will not work in place.
 */
 vImage_Error vImageConvert_RGB888toARGB8888(   const vImage_Buffer *rgbSrc, 
                                                const vImage_Buffer *aSrc, 
                                                Pixel_8 alpha, 
                                                const vImage_Buffer *argbDest, 
                                                bool premultiply,  /* Boolean 1 or 0 */ 
                                                vImage_Flags flags ) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*
 *  Convert 4 channel buffer to a 3 channel one, by removing the 1st channel.
 *  The R,G and B channels are simply copied into the new buffer.
 *
 *  Will work in place
 */
 vImage_Error vImageConvert_ARGB8888toRGB888(   const vImage_Buffer *argbSrc, 
                                                const vImage_Buffer *rgbDest, 
                                                vImage_Flags flags ) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 * Flatten a ARGB8888 image to a RGB888 image against an opaque background of a certain color. 
 * The calculation for each {R,G,B} channel is done as:
 * 
 *   8-bit:
 *       if( isImagePremultiplied )
 *           color = (color * 255 + (255 - alpha) * backgroundColor + 127) / 255
 *       else
 *           color = (color * alpha + (255 - alpha) * backgroundColor + 127) / 255
 * 
 *   floating point:
 *       if( isImagePremultiplied )
 *           color = color + (1.0f - alpha) * backgroundColor
 *       else
 *           color = color * alpha + (1.0f - alpha) * backgroundColor
 */
vImage_Error  vImageFlatten_ARGB8888ToRGB888( 
                                                const vImage_Buffer *argb8888Src, 
                                                const vImage_Buffer *rgb888dest, 
                                                Pixel_8888  backgroundColor,    /* background color is assumed to have a 255 alpha channel */
                                                bool     isImagePremultiplied,
                                                vImage_Flags    flags
                                            ) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
vImage_Error  vImageFlatten_ARGBFFFFToRGBFFF( 
                                                const vImage_Buffer *argbFFFFSrc, 
                                                const vImage_Buffer *rgbFFFdest, 
                                                Pixel_FFFF  backgroundColor,    /* background color is assumed to have a 1.0f alpha channel */
                                                bool     isImagePremultiplied,
                                                vImage_Flags    flags
                                            ) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*
 *  Convert 3 planar buffers to a 3 channel interleave buffer.
 *
 *  Does not work in place
 */
vImage_Error vImageConvert_Planar8toRGB888( const vImage_Buffer *planarRed, const vImage_Buffer *planarGreen, const vImage_Buffer *planarBlue, const vImage_Buffer *rgbDest, vImage_Flags flags ) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; 
vImage_Error vImageConvert_PlanarFtoRGBFFF( const vImage_Buffer *planarRed, const vImage_Buffer *planarGreen, const vImage_Buffer *planarBlue, const vImage_Buffer *rgbDest, vImage_Flags flags ) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; 

/*
 *  Convert a 3 channel interleave buffer to 3 planar buffers.
 *
 *  Does not work in place
 */
vImage_Error vImageConvert_RGB888toPlanar8( const vImage_Buffer *rgbSrc, const vImage_Buffer *redDest, const vImage_Buffer *greenDest, const vImage_Buffer *blueDest, vImage_Flags flags ) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; 
vImage_Error vImageConvert_RGBFFFtoPlanarF( const vImage_Buffer *rgbSrc, const vImage_Buffer *redDest, const vImage_Buffer *greenDest, const vImage_Buffer *blueDest, vImage_Flags flags ) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; 


#ifdef __cplusplus
}
#endif

#endif
