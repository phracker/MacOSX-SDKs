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
 *  This function may be used for multichannel image formats, such as ARGBFFFF. Just scale the vImage_Buffer.width to compensate for the extra channels.
 */
vImage_Error vImageClip_PlanarF(const vImage_Buffer* src, const vImage_Buffer* dest, Pixel_F maxFloat, Pixel_F minFloat, vImage_Flags flags)    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

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
vImage_Error vImageConvert_Planar8toPlanarF(const vImage_Buffer *src, const vImage_Buffer *dest, Pixel_F maxFloat, Pixel_F minFloat, vImage_Flags flags)    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

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
vImage_Error vImageConvert_PlanarFtoPlanar8(const vImage_Buffer *src, const vImage_Buffer *dest, Pixel_F maxFloat, Pixel_F minFloat, vImage_Flags flags)    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );


/*  
 *  vImageConvert_Planar8toARGB8888:
 *      Interleave 4 planar 8 bit integer buffers to make a Interleaved 4 channel ARGB8888 buffer
 *      For each pixel in {srcA, srcR, srcG, srcB }:
 *
 *          Pixel_88888 result = { pixelFromSrcA, pixelFromSrcR, pixelFromSrcG, pixelFromSrcB } 
 *
 *  will not work in place.
 *  This function may be used to create other channel orderings such as RGBA8888 by passing in the planar8 images in the alternate order.
 */
vImage_Error vImageConvert_Planar8toARGB8888(const vImage_Buffer *srcA, const vImage_Buffer *srcR, const vImage_Buffer *srcG, const vImage_Buffer *srcB, const vImage_Buffer *dest, vImage_Flags flags)    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*  
 *  vImageConvert_PlanarFtoARGBFFFF:
 *      Interleave 4 planar floating point buffers to make a Interleaved 4 channel ARGBFFFF buffer
 *      For each pixel in {srcA, srcR, srcG, srcB }:
 *
 *          Pixel_FFFF result = { pixelFromSrcA, pixelFromSrcR, pixelFromSrcG, pixelFromSrcB } 
 *
 *  will not work in place.
 *  This function may be used to create other channel orderings such as RGBAFFFF by passing in the planar8 images in the alternate order.
 */
vImage_Error vImageConvert_PlanarFtoARGBFFFF(const vImage_Buffer *srcA, const vImage_Buffer *srcR, const vImage_Buffer *srcG, const vImage_Buffer *srcB, const vImage_Buffer *dest, vImage_Flags flags)    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

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
 *  This function may be used to deinterleave other channel orderings such as RGBA8888 by passing in the planar8 images in the alternate order.
 */
vImage_Error vImageConvert_ARGB8888toPlanar8(const vImage_Buffer *srcARGB, const vImage_Buffer *destA, const vImage_Buffer *destR, const vImage_Buffer *destG, const vImage_Buffer *destB, vImage_Flags flags)    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

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
 *  This function may be used to deinterleave other channel orderings such as RGBAFFFF by passing in the planar8 images in the alternate order.
 */
vImage_Error vImageConvert_ARGBFFFFtoPlanarF(const vImage_Buffer *srcARGB, const vImage_Buffer *destA, const vImage_Buffer *destR, const vImage_Buffer *destG, const vImage_Buffer *destB, vImage_Flags flags)    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

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
vImage_Error vImageConvert_ChunkyToPlanar8( const void *srcChannels[], const vImage_Buffer *destPlanarBuffers[], unsigned int channelCount, size_t srcStrideBytes, vImagePixelCount srcWidth, vImagePixelCount srcHeight, size_t srcRowBytes, vImage_Flags flags )    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error vImageConvert_PlanarToChunky8( const vImage_Buffer *srcPlanarBuffers[], void *destChannels[], unsigned int channelCount, size_t destStrideBytes, vImagePixelCount destWidth, vImagePixelCount destHeight, size_t destRowBytes, vImage_Flags flags )    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error vImageConvert_ChunkyToPlanarF( const void *srcChannels[], const vImage_Buffer *destPlanarBuffers[], unsigned int channelCount, size_t srcStrideBytes, vImagePixelCount srcWidth, vImagePixelCount srcHeight, size_t srcRowBytes, vImage_Flags flags )    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error vImageConvert_PlanarToChunkyF( const vImage_Buffer *srcPlanarBuffers[], void *destChannels[], unsigned int channelCount, size_t destStrideBytes, vImagePixelCount destWidth, vImagePixelCount destHeight, size_t destRowBytes, vImage_Flags flags )    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

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
vImage_Error vImageConvert_16SToF( const vImage_Buffer *src, const vImage_Buffer *dest, float offset, float scale, vImage_Flags flags )    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

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
vImage_Error vImageConvert_16UToF( const vImage_Buffer *src, const vImage_Buffer *dest, float offset, float scale, vImage_Flags flags )    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

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
 *  To convert multichannel interleaved floating point formats (e.g. ARGB_FFFF) to a multichannel 16-bit image format with the same channel ordering, 
 *  simply multiply the vImage_Buffer.width by the number of channels.
 */
vImage_Error vImageConvert_FTo16S( const vImage_Buffer *src, const vImage_Buffer *dest, float offset, float scale, vImage_Flags flags )    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

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
 *  To convert multichannel interleaved floating point formats (e.g. ARGB_FFFF) to a multichannel 16-bit image format with the same channel ordering, 
 *  simply multiply the vImage_Buffer.width by the number of channels.
 */
vImage_Error vImageConvert_FTo16U( const vImage_Buffer *src, const vImage_Buffer *dest, float offset, float scale, vImage_Flags flags )    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );



/*
 *  vImageTableLookUp_ARGB8888:
 *      Use a lookup table to remap 0...255 values in the source image to a different set of 0...255 values in the destination.
 *      A different lookup table is used for each channel in the ARGB image
 *
 *  will work in place.
 *  This function may be used to do table lookups on other 4 channel 8-bit/channel formats (e.g. RGBA8888) by adjusting the order of the tables
 *  passed into the function accordingly.
 *
 *	Performance Advisory:  For 8-bit monochrome -> ARGB8888  or 8-bit indexed -> ARGB8888 conversions, it is probably significantly faster
 *							to use vImageLookupTable_Planar8toPlanarF. Use the desired ARGB8888 (32 bits/pixel) pixels in place of the planar 
 *							32-bit floats in the lookup table. See vImage/Tiger.h.
 */
vImage_Error vImageTableLookUp_ARGB8888(const vImage_Buffer *src, const vImage_Buffer *dest, const Pixel_8 alphaTable[256], const Pixel_8 redTable[256], const  Pixel_8 greenTable[256], const  Pixel_8 blueTable[256], vImage_Flags flags)    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*
 *  vImageTableLookUp_Planar8:
 *      Use a lookup table to remap 0...255 values in the source image to a different set of 0...255 values in the destination.
 *
 *  will work in place.
 */
vImage_Error vImageTableLookUp_Planar8(const vImage_Buffer *src, const vImage_Buffer *dest, const Pixel_8 table[256], vImage_Flags flags)    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );


/*
 * origSrc and dest may overlap, if they share the same origin. 
 * origSrc should be at least as big as dest
 *
 * origSrc and dest can be the same buffer
 * This function may be used with other channel orderings (e.g. origSrc -> a RGBA8888 buffer) by adjusting the order of the bits in the copyMask.
 */
vImage_Error vImageOverwriteChannels_ARGB8888(	const vImage_Buffer *newSrc,       /* A planar buffer */
                                                const vImage_Buffer *origSrc,      /* A ARGB interleaved buffer */
                                                const vImage_Buffer *dest,      /* A ARGB interleaved buffer */
                                                uint8_t copyMask,               /* Copy plane into  0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue */ 
                                                vImage_Flags    flags )		__OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

/*
 * origSrc and dest may overlap, if they share the same origin. 
 * origSrc should be at least as big as dest
 *
 * origSrc and dest can be the same buffer
 * This function may be used with other channel orderings (e.g. origSrc -> a RGBA8888 buffer) by adjusting the order of the bits in the copyMask.
 */
vImage_Error vImageOverwriteChannels_ARGBFFFF(	const vImage_Buffer *newSrc,       /* A planar buffer */
                                                const vImage_Buffer *origSrc,      /* A ARGB interleaved buffer */
                                                const vImage_Buffer *dest,      /* A ARGB interleaved buffer */
                                                uint8_t copyMask,               /* Copy plane into  0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue */ 
                                                vImage_Flags    flags )		__OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

/*
 *  Fill the dest buffer with the scalar value
 */
vImage_Error vImageOverwriteChannelsWithScalar_Planar8(	Pixel_8     scalar,
                                                        const vImage_Buffer *dest,      /* A planar buffer */
                                                        vImage_Flags    flags )		__OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

/*
 *  Fill the dest buffer with the scalar value
 */
vImage_Error vImageOverwriteChannelsWithScalar_PlanarF( Pixel_F     scalar,
                                                        const vImage_Buffer *dest,      /* A planar buffer */
                                                        vImage_Flags    flags )		__OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );



/*
 * Fill a buffer with a color. Use vImageOverwriteChannelsWithScalar_* to fill planar buffers with a color.
 * These functions work for any 4-channel 8-bit/channel or floating-point format, such as RGBAFFFF or BGRA8888.
 */
vImage_Error vImageBufferFill_ARGB8888( const vImage_Buffer *dest, const Pixel_8888 color, vImage_Flags flags ) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
vImage_Error vImageBufferFill_ARGBFFFF( const vImage_Buffer *dest, const Pixel_FFFF color, vImage_Flags flags ) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

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
 * These functions may be used for images with other channel orderings such as RGBA8888 by adjusting the ordering of the bits in copyMask.
 */
vImage_Error vImageOverwriteChannelsWithScalar_ARGB8888(	Pixel_8     scalar,
                                                                const vImage_Buffer *src,      /* A ARGB interleaved buffer */
                                                                const vImage_Buffer *dest,      /* A ARGB interleaved buffer */
                                                                uint8_t copyMask,               /* Copy plane into  0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue */ 
                                                                vImage_Flags    flags )		__OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );


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
 * These functions may be used for images with other channel orderings such as RGBAFFFF by adjusting the ordering of the bits in copyMask.
 */
vImage_Error vImageOverwriteChannelsWithScalar_ARGBFFFF(	Pixel_F     scalar,
                                                                const vImage_Buffer *src,      /* A ARGB interleaved buffer */
                                                                const vImage_Buffer *dest,      /* A ARGB interleaved buffer */
                                                                uint8_t copyMask,               /* Copy plane into  0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue */ 
                                                                vImage_Flags    flags )		__OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

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
 * This function may be used with any 4 channel 8-bit/channel format, such as RGBA8888, BGRA8888 or AYUV8888.
 */
vImage_Error vImagePermuteChannels_ARGB8888(    const vImage_Buffer *src,
                                                const vImage_Buffer *dest,
                                                const uint8_t       permuteMap[4],
                                                vImage_Flags        flags )		__OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

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
 * This function may be used with any 4 channel floating-point format, such as RGBAFFFF, BGRAFFFF or AYUVFFF.
 */
vImage_Error vImagePermuteChannels_ARGBFFFF(    const vImage_Buffer *src,
                                                const vImage_Buffer *dest,
                                                const uint8_t       permuteMap[4],
                                                vImage_Flags        flags )		__OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
                                                

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
 *  Does work in place.
 */
vImage_Error    vImageConvert_ARGB1555toPlanar8( const vImage_Buffer *src, const vImage_Buffer *destA, const vImage_Buffer *destR, const vImage_Buffer *destG, const vImage_Buffer *destB, vImage_Flags flags )  __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
vImage_Error    vImageConvert_ARGB1555toARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags )  __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
vImage_Error    vImageConvert_Planar8toARGB1555( const vImage_Buffer *srcA, const vImage_Buffer *srcR, const vImage_Buffer *srcG, const vImage_Buffer *srcB, const vImage_Buffer *dest, vImage_Flags flags )  __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
vImage_Error    vImageConvert_ARGB8888toARGB1555( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags )  __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
    
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
vImage_Error    vImageConvert_RGB565toPlanar8( const vImage_Buffer *src, const vImage_Buffer *destR, const vImage_Buffer *destG, const vImage_Buffer *destB, vImage_Flags flags )  __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
vImage_Error    vImageConvert_RGB565toARGB8888( Pixel_8 alpha, const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags )  __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
vImage_Error    vImageConvert_Planar8toRGB565( const vImage_Buffer *srcR, const vImage_Buffer *srcG, const vImage_Buffer *srcB, const vImage_Buffer *dest, vImage_Flags flags )  __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
vImage_Error    vImageConvert_ARGB8888toRGB565( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags )  __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
    
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
 *  These functions may also be used with multichannel images formats, such as RGBAFFFF by scaling the width by the number of channels.
 */
vImage_Error    vImageConvert_Planar16FtoPlanarF( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags )  __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
vImage_Error    vImageConvert_PlanarFtoPlanar16F( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags )  __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
    
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
 *  This function may also be used with multichannel images formats, such as RGBA16U -> RGBA8888 by scaling the width by the number of channels.
 */
vImage_Error vImageConvert_16UToPlanar8( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags )    __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

/*
 *  vImageConvert_Planar8To16U:
 *      Convert a planar (or interleaved -- multiply vImage_Buffer.width by 4) vImage_Buffer of 8-bit integer values to a buffer of 16 bit unsigned ints.
 *      For each 8-bit pixel in src:
 *
 *          uint16_t result = (srcPixel * 65535 + 127 ) / 255;      
 *
 *  will not work in place.
 *  This function may also be used with multichannel images formats, such as RGBA8888 -> RGBA16U  by scaling the width by the number of channels.
 */
vImage_Error vImageConvert_Planar8To16U( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags )    __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

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
 vImage_Error vImageConvert_RGB888toARGB8888(   const vImage_Buffer* /* rgbSrc */, 
                                                const vImage_Buffer* /* aSrc */, 
                                                Pixel_8 /* alpha */, 
                                                const vImage_Buffer* /*argbDest*/, 
                                                bool /* premultiply */,  /* Boolean 1 or 0 */ 
                                                vImage_Flags /* flags */ ) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
vImage_Error vImageConvert_RGB888toRGBA8888(    const vImage_Buffer * /* rgbSrc */, 
                                                const vImage_Buffer * /* aSrc */, 
                                                Pixel_8 /* alpha */, 
                                                const vImage_Buffer * /* rgbaDest */, 
                                                bool /* premultiply */,  /* Boolean 1 or 0 */ 
                                                vImage_Flags /* flags */ ) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_NA );
vImage_Error vImageConvert_RGB888toBGRA8888(    const vImage_Buffer * /* rgbSrc, */,
                                                const vImage_Buffer * /* aSrc */, 
                                                Pixel_8 /* alpha */, 
                                                const vImage_Buffer * /* bgraDest */, 
                                                bool /* premultiply */,  /* Boolean 1 or 0 */ 
                                                vImage_Flags /* flags */ ) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_NA );
#define vImageConvert_BGR888toBGRA8888( _bgrSrc, _aSrc, _alpha, _bgraDest, _premultiply, _flags )   vImageConvert_RGB888toRGBA8888((_bgrSrc), (_aSrc), (_alpha), (_bgraDest), (_premultiply), (_flags) ) 
#define vImageConvert_BGR888toRGBA8888( _bgrSrc, _aSrc, _alpha, _rgbaDest, _premultiply, _flags )   vImageConvert_RGB888toBGRA8888((_bgrSrc), (_aSrc), (_alpha), (_rgbaDest), (_premultiply), (_flags) ) 
    
/*
 *  Convert 4 channel buffer to a 3 channel one, by removing the 1st channel.
 *  The R,G and B channels are simply copied into the new buffer.
 *
 *  Will work in place
 */
vImage_Error vImageConvert_ARGB8888toRGB888(    const vImage_Buffer * /*argbSrc*/, 
                                                const vImage_Buffer * /*rgbDest*/, 
                                                vImage_Flags /* flags */ ) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
vImage_Error vImageConvert_RGBA8888toRGB888(    const vImage_Buffer * /*rgbaSrc*/, 
                                                const vImage_Buffer * /*rgbDest*/, 
                                                vImage_Flags /* flags */ ) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_NA );
vImage_Error vImageConvert_BGRA8888toRGB888(    const vImage_Buffer * /* bgraSrc */, 
                                                const vImage_Buffer * /* rgbDest */, 
                                                vImage_Flags /* flags */ ) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_NA );
#define vImageConvert_RGBA8888toBGR888( _rgbaSrc, _bgrDest, _flags )    vImageConvert_BGRA8888toRGB888((_rgbaSrc), (_bgrDest), (_flags))
#define vImageConvert_BGRA8888toBGR888( _bgraSrc, _bgrDest, _flags )    vImageConvert_RGBA8888toRGB888((_bgraSrc), (_bgrDest), (_flags))

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
 *
 *  backgroundColor.alpha is ignored.
 *  These functions will work in place provided that rowBytes and the position of row starts is the same between src and dest images.
 */
vImage_Error  vImageFlatten_ARGB8888ToRGB888( 
                                                const vImage_Buffer * /* argb8888Src */, 
                                                const vImage_Buffer * /* rgb888dest */, 
                                                Pixel_8888   /* backgroundColor */,    /* background color is assumed to have a 255 alpha channel */
                                                bool      /* isImagePremultiplied */,
                                                vImage_Flags     /* flags */
                                            ) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
vImage_Error  vImageFlatten_ARGBFFFFToRGBFFF( 
                                                const vImage_Buffer * /* argbFFFFSrc */, 
                                                const vImage_Buffer * /* rgbFFFdest */, 
                                                Pixel_FFFF   /* backgroundColor */,    /* background color is assumed to have a 1.0f alpha channel */
                                                bool      /* isImagePremultiplied */,
                                                vImage_Flags     /* flags */
                                            ) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
vImage_Error  vImageFlatten_RGBA8888ToRGB888( 
                                             const vImage_Buffer * /* rgba8888Src */, 
                                             const vImage_Buffer * /* rgb888dest */, 
                                             Pixel_8888   /* backgroundColor */,    /* background color is assumed to have a 255 alpha channel */
                                             bool      /* isImagePremultiplied */,
                                             vImage_Flags     /* flags */
                                             ) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_NA );
vImage_Error  vImageFlatten_RGBAFFFFToRGBFFF( 
                                             const vImage_Buffer * /* rgbaFFFFSrc */, 
                                             const vImage_Buffer * /* rgbFFFdest */, 
                                             Pixel_FFFF   /* backgroundColor */,    /* background color is assumed to have a 1.0f alpha channel */
                                             bool      /* isImagePremultiplied */,
                                             vImage_Flags     /* flags */
                                             ) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_NA );
vImage_Error  vImageFlatten_BGRA8888ToRGB888( 
                                             const vImage_Buffer * /* bgra8888Src */, 
                                             const vImage_Buffer * /* rgb888dest */, 
                                             Pixel_8888   /* backgroundColor */,    /* background color is assumed to have a 255 alpha channel */
                                             bool      /* isImagePremultiplied */,
                                             vImage_Flags     /* flags */
                                             ) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_NA );
vImage_Error  vImageFlatten_BGRAFFFFToRGBFFF( 
                                             const vImage_Buffer * /* bgraFFFFSrc */, 
                                             const vImage_Buffer * /* rgbFFFdest */, 
                                             Pixel_FFFF   /* backgroundColor */,    /* background color is assumed to have a 1.0f alpha channel */
                                             bool      /* isImagePremultiplied */,
                                             vImage_Flags     /* flags */
                                             ) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_NA );
#define vImageFlatten_BGRA8888ToBGR888( _bgra8888Src, _bgr888Dest, _backgroundColor, _isImagePremultiplied, _flags )        \
        vImageFlatten_RGBA8888ToRGB888( (_bgra8888Src), (_bgr888Dest), (_backgroundColor), (_isImagePremultiplied), (_flags) )
#define vImageFlatten_RGBA8888ToBGR888( _rgba8888Src, _bgr888Dest, _backgroundColor, _isImagePremultiplied, _flags )        \
        vImageFlatten_BGRA8888ToRGB888( (_rgba8888Src), (_bgr888Dest), (_backgroundColor), (_isImagePremultiplied), (_flags) )

    
/*
 *  Convert 3 planar buffers to a 3 channel interleave buffer.
 *
 *  Does not work in place
 *  This may be used to produce other channel orderings by changing the order of the planar buffers passed into the function.
 */
vImage_Error vImageConvert_Planar8toRGB888( const vImage_Buffer *planarRed, const vImage_Buffer *planarGreen, const vImage_Buffer *planarBlue, const vImage_Buffer *rgbDest, vImage_Flags flags ) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 ); 
vImage_Error vImageConvert_PlanarFtoRGBFFF( const vImage_Buffer *planarRed, const vImage_Buffer *planarGreen, const vImage_Buffer *planarBlue, const vImage_Buffer *rgbDest, vImage_Flags flags ) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 ); 

/*
 *  Convert a 3 channel interleave buffer to 3 planar buffers.
 *
 *  Does not work in place
 *  This may be used to consume other channel orderings by changing the order of the planar buffers passed into the function.
 */
vImage_Error vImageConvert_RGB888toPlanar8( const vImage_Buffer *rgbSrc, const vImage_Buffer *redDest, const vImage_Buffer *greenDest, const vImage_Buffer *blueDest, vImage_Flags flags ) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 ); 
vImage_Error vImageConvert_RGBFFFtoPlanarF( const vImage_Buffer *rgbSrc, const vImage_Buffer *redDest, const vImage_Buffer *greenDest, const vImage_Buffer *blueDest, vImage_Flags flags ) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 ); 


/*
 *  Does the same thing as vImageOverwriteChannels_ARGB8888 except that the newSrc buffer is formatted as ARGB8888
 *  If the appropriate copyMask bit is set, then the color channel from newSrc is used. Otherwise the color channel from origSrc is used.
 *  We note that functions of this kind only exist for interleaved buffers. If you had been using planar data, this would just be a pointer swap.
 *  This will work for other channel orderings, such as RGBA8888.  You need to adjust the ordering of the bits in copyMask to compensate.
 */
vImage_Error	vImageSelectChannels_ARGB8888( const vImage_Buffer *newSrc,       /* A ARGB interleaved buffer */
                                                const vImage_Buffer *origSrc,      /* A ARGB interleaved buffer */
                                                const vImage_Buffer *dest,      /* A ARGB interleaved buffer */
                                                uint8_t copyMask,               /* Copy plane into  0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue */ 
                                                vImage_Flags    flags )     __OSX_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_5_0 );

vImage_Error	vImageSelectChannels_ARGBFFFF( const vImage_Buffer *newSrc,       /* A ARGB interleaved buffer */
                                                const vImage_Buffer *origSrc,      /* A ARGB interleaved buffer */
                                                const vImage_Buffer *dest,      /* A ARGB interleaved buffer */
                                                uint8_t copyMask,               /* Copy plane into  0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue */ 
                                                vImage_Flags    flags )     __OSX_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_5_0 );

/*
 *  The following are like vImageOverwriteChannelsWithScalar_ARGB*, except that they take a ARGB input pixel, instead of a planar one. 
 *  This will work for other channel orderings, such as RGBA8888. You will need to adjust the ordering of bits in copyMask to compensate.
 */
vImage_Error vImageOverwriteChannelsWithPixel_ARGB8888( const Pixel_8888     the_pixel,
                                                        const vImage_Buffer *src,      /* A ARGB interleaved buffer */
                                                        const vImage_Buffer *dest,      /* A ARGB interleaved buffer */
                                                        uint8_t copyMask,               /* Copy plane into  0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue */ 
                                                        vImage_Flags    flags )     __OSX_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_5_0 );

vImage_Error vImageOverwriteChannelsWithPixel_ARGBFFFF( const Pixel_FFFF     the_pixel,
                                                        const vImage_Buffer *src,      /* A ARGB interleaved buffer */
                                                        const vImage_Buffer *dest,      /* A ARGB interleaved buffer */
                                                        uint8_t copyMask,               /* Copy plane into  0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue */ 
                                                        vImage_Flags    flags )     __OSX_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_5_0 );


/*
 *  The following functions interleave the planar buffers pointed to by red, green and blue, with the scalar value in alpha, to 
 *  create a ARGB, BGRA or RGBA  four channel interleaved buffer.  These functions do not work in place.  Per all vImage functions
 *  channel order is defined as memory order.
 *
 *  Flags: 
 *      kvImageGetTempBufferSize    returns 0. Does no work.
 *      kvImageDoNotTile            Disables internal multithreading, if any.
 *
 *      Other flags cause the function to return kvImageUnknownFlagsBit.
 */
vImage_Error    vImageConvert_Planar8ToXRGB8888( Pixel_8 alpha, const vImage_Buffer *red, const vImage_Buffer *green, const vImage_Buffer *blue, const vImage_Buffer *dest, vImage_Flags flags )    __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_5_0 );
vImage_Error    vImageConvert_Planar8ToBGRX8888( const vImage_Buffer *blue, const vImage_Buffer *green, const vImage_Buffer *red, Pixel_8 alpha, const vImage_Buffer *dest, vImage_Flags flags )    __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_5_0 );
#define         vImageConvert_Planar8ToRGBX8888( _red, _green, _blue, _alpha, _dest, _flags )   vImageConvert_Planar8ToBGRX8888((_red), (_green), (_blue), (_alpha), (_dest), (_flags))
vImage_Error    vImageConvert_PlanarFToXRGBFFFF( Pixel_F alpha, const vImage_Buffer *red, const vImage_Buffer *green, const vImage_Buffer *blue, const vImage_Buffer *dest, vImage_Flags flags )    __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_5_0 );
vImage_Error    vImageConvert_PlanarFToBGRXFFFF( const vImage_Buffer *blue, const vImage_Buffer *green, const vImage_Buffer *red, Pixel_F alpha, const vImage_Buffer *dest, vImage_Flags flags )    __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_5_0 );
#define         vImageConvert_PlanarFToRGBXFFFF( _red, _green, _blue, _alpha, _dest, _flags )   vImageConvert_PlanarFToBGRXFFFF( (_red), (_green), (_blue), (_alpha), (_dest), (_flags))
    
/*
 *  vImageConvert_Planar8ToARGBFFFF
 *
 *  Conversion routines to convert planar 8-bit buffers to packed (interleaved) 4 channel floating point format.
 *
 *  The meaning of maxFloat and minFloat here is substatially the same as for vImageConvert_Planar8toPlanarF. The difference is that since this is a four channel
 *  image, we use four channel min and max values so that different mins and maxes can be used for each channel. The channels in minFloat and maxFloat are in the 
 *  same order as the output pixels. MaxFloat is allowed to be less than MinFloat, in which case the image will come out looking like a photographic negative.
 *  (That is, you get a free contrast + brightness adjustment as part of this conversion.)
 *
 *  The vImageConvert_Planar8ToARGBFFFF function is the workhorse of this family. The other three are provided as a convenience. You can actually substitute
 *  any of the channels with a constant by replacing the vImage_Buffer passed in for that channel with one from another color channel, and set 
 *  maxFloat.color = minFloat.color = desired color for that channel. (In the particular case where you want all four channels to be constant, please call 
 *  vImageBufferFill_ARGBFFFF instead.) Likewise, though these API names appear to correspond to particular color channel orders, vImage has no way of knowing what 
 *  is actually red or green or cyan, so you can use them for other color spaces and other packing orders. Thus, vImageConvert_Planar8ToARGBFFFF should be 
 *  properly considered a somewhat color space agnostic <=4 planar 8-bit channel to 4 channel packed float conversion function. 
 *
 *  Performance data on Intel Core2 and G5 suggest that like most simple conversion functions, these functions only perform well if the data is already in the cache. 
 *  Optimum tile sizes are between ~200 pixels and somewhere in the 50000 to 200000 pixel range, depending on cache size. If the image is larger than that, this 
 *  function is limited by the throughput of the machine's front side bus and will run anywhere from 3 to 10 times slower. For well sized images / times, we observe 
 *  that the vector code is 3-12x faster than scalar code. For images that don't fit in cache or that are not in cache, the vector code is perhaps only 10% faster 
 *  than scalar.
 *
 *  Flags: 
 *      kvImageGetTempBufferSize    returns 0. Does no work.
 *      kvImageDoNotTile            Disables internal multithreading, if any.
 *
 *      Other flags cause the function to return kvImageUnknownFlagsBit.
 *
 *  These routines do not work in place.
 */
vImage_Error    vImageConvert_Planar8ToARGBFFFF( const vImage_Buffer *alpha, const vImage_Buffer *red, const vImage_Buffer *green, const vImage_Buffer *blue, const vImage_Buffer *dest, const Pixel_FFFF maxFloat, const Pixel_FFFF minFloat, vImage_Flags flags ) __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_5_0 );
vImage_Error    vImageConvert_Planar8ToXRGBFFFF( Pixel_F alpha, const vImage_Buffer *red, const vImage_Buffer *green, const vImage_Buffer *blue, const vImage_Buffer *dest, const Pixel_FFFF maxFloat, const Pixel_FFFF minFloat, vImage_Flags flags ) __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_5_0 );
vImage_Error    vImageConvert_Planar8ToBGRXFFFF(const vImage_Buffer *blue, const vImage_Buffer *green, const vImage_Buffer *red, Pixel_F alpha, const vImage_Buffer *dest, const Pixel_FFFF maxFloat, const Pixel_FFFF minFloat, vImage_Flags flags ) __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_5_0 );
#define         vImageConvert_Planar8ToRGBXFFFF(_red, _green, _blue, _alpha, _dest, _maxFloat, _minFloat, _flags)  vImageConvert_Planar8ToBGRXFFFF((_red), (_green), (_blue), (_alpha), (_dest), (_maxFloat), (_minFloat), (_flags))
    
/*
 *  vImageConvert_PlanarFToARGB8888
 *
 *  Conversion routines to convert planar float buffers to packed (interleaved) 4 channel 8-bit unsigned format.
 *
 *  The meaning of maxFloat and minFloat here is similar to vImageConvert_PlanarFtoPlanar8. That is, the max and min define the pixel values for
 *  100% and 0% light saturation respectively. (Pixel values outside that range are clamped into that range before we do arithmetic.) Since this function works on
 *  multichannel data, we pass in multichannel maxes and mins. The channel order in maxFloat and minFloat is the same as for the desired result pixel. The calculation
 *  is as follows for each channel:
 *
 *      uint8_t result = ROUND_TO_INTEGER( SATURATED_CLAMP_0_to_255( 255.0f * ( srcPixel[channel] - minFloat[channel] ) / (maxFloat[channel] - minFloat[channel]) ));
 *
 *  The ROUND_TO_INTEGER function here behaves identically to the C99 lrintf() function. It rounds to integer using the prevailing floating point rounding mode.
 *  By default, that is round to nearest integer (ties go to the even result).  You can change the rounding mode using interfaces in fenv.h, specfically fesetround() 
 *  and fegetround(), if you prefer that the calculation round up, or down.
 *
 *  It is allowed that maxFloat[channel] < minFloat[channel], in which case you'll get an image that appears a bit like a photgraphic negative. The astute reader will
 *  note that these routines provide a free per-channel brightness and contrast adjustment.
 *
 *  In the special case that maxFloat[channel] == minFloat[channel], then the calculation is instead as follows:
 *
 *      uint8_t result = ROUND_TO_INTEGER( SATURATED_CLIP_0_to_255( 255.0f * maxFloat[channel] ) );
 *
 *  This serves two purposes. It guarantees we can't get a division by zero. It also provides a way to set certain channels to a constant, rather than use
 *  a source buffer. You'll still need to pass in a source buffer for that channel, the data also needs to be valid, but it wont actually affect the result. It should
 *  be sufficient to substitute one of the other source buffers in for the color channel that you wish to be constant. If you intend to produce a buffer full of a 
 *  solid color, please use vImageBufferFill_ARGB8888 instead. Two special purpose routines are provided for constant alpha in either the first or last position 
 *  in the pixel, vImageConvert_PlanarFToXRGB8888, vImageConvert_PlanarFToBGRX8888. On some platforms, these may be a little bit faster.   
 *
 *  Numerics note: We don't actually do the full caculation described above. The constant terms are precalculated. We are really doing the following:
 *
 *      float a = 255.0f / (maxFloat[channel] - minFloat[channel]);
 *      float b = minFloat[channel] * -a;
 *
 *      uint8_t result = ROUND_TO_INTEGER( SATURATED_CLAMP( srcPixel[channel], minFloat[channel], maxFloat[channel]) * a  + b ));
 *
 *  This may cause slightly different rounding when scaling the pixel to the 0..255 range. In very rare cases, that may produce a result pixel that differs from the 
 *  true calculation by 1. NaNs produce 0.  
 *
 *  Flags: 
 *      kvImageGetTempBufferSize    returns 0. Does no work.
 *      kvImageDoNotTile            Disables internal multithreading, if any.
 *
 *      Other flags cause the function to return kvImageUnknownFlagsBit.
 *
 *  These routines will work in place.
 */
vImage_Error    vImageConvert_PlanarFToARGB8888( const vImage_Buffer *alpha, const vImage_Buffer *red, const vImage_Buffer *green, const vImage_Buffer *blue, const vImage_Buffer *dest, const Pixel_FFFF maxFloat, const Pixel_FFFF minFloat, vImage_Flags flags ) __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_5_0 );
vImage_Error    vImageConvert_PlanarFToXRGB8888( Pixel_8 alpha, const vImage_Buffer *red, const vImage_Buffer *green, const vImage_Buffer *blue, const vImage_Buffer *dest, const Pixel_FFFF maxFloat, const Pixel_FFFF minFloat, vImage_Flags flags ) __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_5_0 );
vImage_Error    vImageConvert_PlanarFToBGRX8888( const vImage_Buffer *blue, const vImage_Buffer *green, const vImage_Buffer *red, Pixel_8 alpha, const vImage_Buffer *dest, const Pixel_FFFF maxFloat, const Pixel_FFFF minFloat, vImage_Flags flags ) __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_5_0 );
#define         vImageConvert_PlanarFToRGBX8888( _red, _green, _blue, _alpha, _dest, _maxFloat, _minFloat, _flags )     vImageConvert_PlanarFToBGRX8888((_red), (_green), (_blue), (_alpha), (_dest), (_maxFloat), (_minFloat), (_flags))

#ifdef __cplusplus
}
#endif

#endif
