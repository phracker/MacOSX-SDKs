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
 *      This function can work in place provided the following are true:
 *          if src overlaps with dest,
 *                  src->data must be equal to dest->data and src->rowBytes >= dest->rowBytes
 *          If an overlapping src has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 *  This function may be used for multichannel image formats, such as ARGBFFFF. Just scale the vImage_Buffer.width to compensate for the extra channels.
 */
vImage_Error vImageClip_PlanarF(const vImage_Buffer* src, const vImage_Buffer* dest, Pixel_F maxFloat, Pixel_F minFloat, vImage_Flags flags)  VIMAGE_NON_NULL(1,2)   __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

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
vImage_Error vImageConvert_Planar8toPlanarF(const vImage_Buffer *src, const vImage_Buffer *dest, Pixel_F maxFloat, Pixel_F minFloat, vImage_Flags flags) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*
 *  vImageConvert_PlanarFtoPlanar8:  
 *         Convert an array of floating point data to 8 bit integer data. For each pixel, do the following:
 *
 *         uint8_t result = SATURATED_CLIP_0_to_255( 255.0f * ( srcPixel - minFloat ) / (maxFloat - minFloat) + 0.5f );
 *
 *         You can use this for ARGBFFFF -> ARGB8888 conversions by simply multiplying the width of the vImage_Buffer by 4 (for 4 channels)
 *
 *      This function can work in place provided the following are true:
 *          if src overlaps with dest,
 *                  src->data must be equal to dest->data and src->rowBytes >= dest->rowBytes
 *          If an overlapping src has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 */
vImage_Error vImageConvert_PlanarFtoPlanar8(const vImage_Buffer *src, const vImage_Buffer *dest, Pixel_F maxFloat, Pixel_F minFloat, vImage_Flags flags) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );


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
vImage_Error vImageConvert_Planar8toARGB8888(const vImage_Buffer *srcA, const vImage_Buffer *srcR, const vImage_Buffer *srcG, const vImage_Buffer *srcB, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3,4,5)    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

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
vImage_Error vImageConvert_PlanarFtoARGBFFFF(const vImage_Buffer *srcA, const vImage_Buffer *srcR, const vImage_Buffer *srcG, const vImage_Buffer *srcB, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3,4,5)    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

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
vImage_Error vImageConvert_ARGB8888toPlanar8(const vImage_Buffer *srcARGB, const vImage_Buffer *destA, const vImage_Buffer *destR, const vImage_Buffer *destG, const vImage_Buffer *destB, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3,4,5)   __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
#define vImageConvert_RGBA8888toPlanar8(_src, _red, _green, _blue, _alpha, _flags) \
    vImageConvert_ARGB8888toPlanar8((_src), (_red), (_green), (_blue), (_alpha), (_flags))
#define vImageConvert_BGRA8888toPlanar8(_src, _blue, _green, _red, _alpha, _flags) \
    vImageConvert_ARGB8888toPlanar8((_src), (_blue), (_green), (_red), (_alpha), (_flags))

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
vImage_Error vImageConvert_ARGBFFFFtoPlanarF(const vImage_Buffer *srcARGB, const vImage_Buffer *destA, const vImage_Buffer *destR, const vImage_Buffer *destG, const vImage_Buffer *destB, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3,4,5) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
#define vImageConvert_RGBAFFFFtoPlanarF(_src, _red, _green, _blue, _alpha, _flags) \
    vImageConvert_ARGBFFFFtoPlanarF((_src), (_red), (_green), (_blue), (_alpha), (_flags))
#define vImageConvert_BGRAFFFFtoPlanarF(_src, _blue, _green, _red, _alpha, _flags) \
    vImageConvert_ARGBFFFFtoPlanarF((_src), (_blue), (_green), (_red), (_alpha), (_flags))

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
 *  will not work in place
 *
 *  Performance advisory:
 *  =====================
 *  These functions are too flexible to vectorize every case. When appropriate, it is suggested you use the other 
 *  special purpose conversion functions. If you know what your data formats are ahead of time, it is
 *  likely you can write your own special purpose conversion function that is faster, even in scalar code.  
 *  These functions are provided as a convenience. 
 */
vImage_Error vImageConvert_ChunkyToPlanar8( const void *srcChannels[], const vImage_Buffer *destPlanarBuffers[], unsigned int channelCount, size_t srcStrideBytes, vImagePixelCount srcWidth, vImagePixelCount srcHeight, size_t srcRowBytes, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error vImageConvert_PlanarToChunky8( const vImage_Buffer *srcPlanarBuffers[], void *destChannels[], unsigned int channelCount, size_t destStrideBytes, vImagePixelCount destWidth, vImagePixelCount destHeight, size_t destRowBytes, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error vImageConvert_ChunkyToPlanarF( const void *srcChannels[], const vImage_Buffer *destPlanarBuffers[], unsigned int channelCount, size_t srcStrideBytes, vImagePixelCount srcWidth, vImagePixelCount srcHeight, size_t srcRowBytes, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error vImageConvert_PlanarToChunkyF( const vImage_Buffer *srcPlanarBuffers[], void *destChannels[], unsigned int channelCount, size_t destStrideBytes, vImagePixelCount destWidth, vImagePixelCount destHeight, size_t destRowBytes, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

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
vImage_Error vImageConvert_16SToF( const vImage_Buffer *src, const vImage_Buffer *dest, float offset, float scale, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

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
vImage_Error vImageConvert_16UToF( const vImage_Buffer *src, const vImage_Buffer *dest, float offset, float scale, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

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
vImage_Error vImageConvert_FTo16S( const vImage_Buffer *src, const vImage_Buffer *dest, float offset, float scale, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

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
vImage_Error vImageConvert_FTo16U( const vImage_Buffer *src, const vImage_Buffer *dest, float offset, float scale, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );


/*
 *  vImageConvert_16Uto16F
 *
 *  Convert from 16 bit unsigned integer to 16 bit float format.
 *
 *      destPixel[x] = ConvertToPlanar16F(srcPixel[x]);
 *
 *  The 16 bit floating point format is half-precision floating point 
 *  (a.k.a.  IEEE-754 binary16, OpenCL half, GL_ARB_half_float_pixel, OpenEXR half).
 *  It has a layout as follows:
 *
 *      16 bits:  seeeeemmmmmmmmmm
 *
 *      1-bit sign | 5 bits of exponent, with a bias of 15 | 10 bits of significand 
 *      (with 11 bits of significance due to the implicit 1 bit)
 *
 *  NaNs, Infinities and denormals are supported.
 *  Per IEEE-754, all signaling NaNs are quieted during the conversion. (OpenEXR-1.2.1 converts SNaNs to SNaNs.)
 *  To set/inspect the current IEEE-754 rounding mode, please see appropriate utilities in fenv.h
 *
 *  Operands:
 *  ---------
 *      src             A pointer to a vImage_Buffer that references the source pixels
 *
 *      dest            A pointer to a vImage_Buffer that references the destination pixels
 *
 *      flags           The following flags are allowed:
 *
 *          kvImageDoNotTile            Turns off internal multithreading. You may
 *                                      wish to do this if you have your own
 *                                      multithreading scheme to avoid having the
 *                                      two interfere with one another.
 *
 *  Return Value:
 *  -------------
 *      kvImageNoError                  Success!
 *      kvImageBufferSizeMismatch		The source buffer must have a height and 
 *										width at least as large as the destination buffer.
 *      kvImageNullPointerArgument      src or dest pointer is NULL.
 *		kvImageUnknownFlagsBit			Unknown flag was passed.
 *
 *  This routine will work in place provided that src.data == dest.data 
 *  and src.rowBytes >= dest.rowBytes, however when src.rowBytes > dest.rowBytes
 *  inplace will only work if you pass kvImageDoNotTile.
 *
 *  To use this with interleaved data, multiply vImage_Buffer.width by 4
 *
 */
vImage_Error
vImageConvert_16Uto16F( const vImage_Buffer *src, const vImage_Buffer *dest,
                       vImage_Flags flags )
    VIMAGE_NON_NULL(1,2)  __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );

/*
 *  vImageConvert_16Fto16U
 *
 *  Convert from 16 bit float to 16 bit unsigned integer format.
 *
 *      destPixel[x] = ConvertToPlanar16U(srcPixel[x]);
 *
 *  The 16 bit floating point format is half-precision floating point 
 *  (a.k.a.  IEEE-754 binary16, OpenCL half, GL_ARB_half_float_pixel, OpenEXR half).
 *  It has a layout as follows:
 *
 *      16 bits:  seeeeemmmmmmmmmm
 *
 *      1-bit sign | 5 bits of exponent, with a bias of 15 | 10 bits of significand 
 *      (with 11 bits of significance due to the implicit 1 bit)
 *
 *  NaNs, Infinities and denormals are supported.
 *  Per IEEE-754, all signaling NaNs are quieted during the conversion. (OpenEXR-1.2.1 converts SNaNs to SNaNs.)
 *  To set/inspect the current IEEE-754 rounding mode, please see appropriate utilities in fenv.h
 *
 *  Operands:
 *  ---------
 *      src             A pointer to a vImage_Buffer that references the source pixels
 *
 *      dest            A pointer to a vImage_Buffer that references the destination pixels
 *
 *      flags           The following flags are allowed:
 *
 *          kvImageDoNotTile            Turns off internal multithreading. You may
 *                                      wish to do this if you have your own
 *                                      multithreading scheme to avoid having the
 *                                      two interfere with one another.
 *
 *  Return Value:
 *  -------------
 *      kvImageNoError                  Success!
 *      kvImageBufferSizeMismatch		The source buffer must have a height and
 *										width at least as large as the destination buffer.
 *      kvImageNullPointerArgument      src or dest pointer is NULL.
 *		kvImageUnknownFlagsBit			Unknown flag was passed.
 *
 *  This routine will work in place provided that src.data == dest.data
 *  and src.rowBytes >= dest.rowBytes, however when src.rowBytes > dest.rowBytes
 *  inplace will only work if you pass kvImageDoNotTile.
 *
 *  To use this with interleaved data, multiply vImage_Buffer.width by 4
 */
vImage_Error
vImageConvert_16Fto16U( const vImage_Buffer *src, const vImage_Buffer *dest,
                       vImage_Flags flags )
    VIMAGE_NON_NULL(1,2)  __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
    
/*
 *  vImageTableLookUp_ARGB8888:
 *      Use a lookup table to remap 0...255 values in the source image to a different set of 0...255 values in the destination.
 *      A different lookup table is used for each channel in the ARGB image
 *
 *      This function can work in place provided the following are true:
 *          if src overlaps with dest,
 *                  src->data must be equal to dest->data and src->rowBytes >= dest->rowBytes
 *          If an overlapping src has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 *  This function may be used to do table lookups on other 4 channel 8-bit/channel formats (e.g. RGBA8888) by adjusting the order of the tables
 *  passed into the function accordingly.
 *
 *	Performance Advisory:  For 8-bit monochrome -> ARGB8888  or 8-bit indexed -> ARGB8888 conversions, it is probably significantly faster
 *							to use vImageLookupTable_Planar8toPlanarF. Use the desired ARGB8888 (32 bits/pixel) pixels in place of the planar 
 *							32-bit floats in the lookup table. See vImage/Tiger.h.
 */
vImage_Error vImageTableLookUp_ARGB8888(const vImage_Buffer *src, const vImage_Buffer *dest, const Pixel_8 alphaTable[256], const Pixel_8 redTable[256], const  Pixel_8 greenTable[256], const  Pixel_8 blueTable[256], vImage_Flags flags) VIMAGE_NON_NULL(1,2,3,4,5,6)    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*
 *  vImageTableLookUp_Planar8:
 *      Use a lookup table to remap 0...255 values in the source image to a different set of 0...255 values in the destination.
 *
 *      This function can work in place provided the following are true:
 *          if src overlaps with dest,
 *                  src->data must be equal to dest->data and src->rowBytes >= dest->rowBytes
 *          If an overlapping src has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 */
vImage_Error vImageTableLookUp_Planar8(const vImage_Buffer *src, const vImage_Buffer *dest, const Pixel_8 table[256], vImage_Flags flags)  VIMAGE_NON_NULL(1,2,3)   __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*
 *  Additional Lookup table functions are available in Transform.h :
 *      vImageLookupTable_Planar8toPlanar16,
 *      vImageLookupTable_Planar8toPlanarF,
 *      vImageLookupTable_8to64U,
 *      vImageLookupTable_PlanarFtoPlanar8
 */

/*
 * origSrc and dest may overlap, if they share the same origin. 
 * origSrc should be at least as big as dest
 *
 * origSrc and dest can be the same buffer
 * This function may be used with other channel orderings (e.g. origSrc -> a RGBA8888 buffer) by adjusting the order of the bits in the copyMask.
 *
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 */
vImage_Error vImageOverwriteChannels_ARGB8888(	const vImage_Buffer *newSrc,       /* A planar buffer */
                                                const vImage_Buffer *origSrc,      /* A ARGB interleaved buffer */
                                                const vImage_Buffer *dest,      /* A ARGB interleaved buffer */
                                                uint8_t copyMask,               /* Copy plane into  0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue */ 
                                                vImage_Flags    flags ) VIMAGE_NON_NULL(1,2,3)		__OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

/*
 * origSrc and dest may overlap, if they share the same origin. 
 * origSrc should be at least as big as dest
 *
 *      This function can work in place provided the following are true:
 *          origSrc->data must be equal to dest->data and origSrc->rowBytes >= dest->rowBytes
 *          If overlapping origSrc has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 * This function may be used with other channel orderings (e.g. origSrc -> a RGBA8888 buffer) by adjusting the order of the bits in the copyMask.
 */
vImage_Error vImageOverwriteChannels_ARGBFFFF(	const vImage_Buffer *newSrc,       /* A planar buffer */
                                                const vImage_Buffer *origSrc,      /* A ARGB interleaved buffer */
                                                const vImage_Buffer *dest,      /* A ARGB interleaved buffer */
                                                uint8_t copyMask,               /* Copy plane into  0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue */ 
                                                vImage_Flags    flags ) VIMAGE_NON_NULL(1,2,3)		__OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

/*
 *  Fill the dest buffer with the scalar value
 */
vImage_Error vImageOverwriteChannelsWithScalar_Planar8(	Pixel_8     scalar,
                                                        const vImage_Buffer *dest,      /* A planar buffer */
                                                        vImage_Flags    flags ) VIMAGE_NON_NULL(2)		__OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

/*
 *  Fill the dest buffer with the scalar value
 */
vImage_Error vImageOverwriteChannelsWithScalar_PlanarF( Pixel_F     scalar,
                                                        const vImage_Buffer *dest,      /* A planar buffer */
                                                        vImage_Flags    flags ) VIMAGE_NON_NULL(2)		__OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );



/*
 * Fill a buffer with a color. Use vImageOverwriteChannelsWithScalar_* to fill planar buffers with a color.
 * These functions work for any 4-channel 8-bit/channel, 16-bit/channel or floating-point format, such as RGBAFFFF or BGRA8888.
 */
vImage_Error vImageBufferFill_ARGB8888( const vImage_Buffer *dest, const Pixel_8888 color, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
vImage_Error vImageBufferFill_ARGB16U( const vImage_Buffer *dest, const Pixel_ARGB_16U color, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
vImage_Error vImageBufferFill_ARGB16S( const vImage_Buffer *dest, const Pixel_ARGB_16S color, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
vImage_Error vImageBufferFill_ARGBFFFF( const vImage_Buffer *dest, const Pixel_FFFF color, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

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
 *      This function can work in place provided the following are true:
 *          src->data must be equal to dest->data and src->rowBytes >= dest->rowBytes
 *          If overlapping src has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 * These functions may be used for images with other channel orderings such as RGBA8888 by adjusting the ordering of the bits in copyMask.
 * See also vImageOverwriteChannelsWithPixel_ARGB8888 to cover the case where a different value is needed for each channel.
 */
vImage_Error vImageOverwriteChannelsWithScalar_ARGB8888(	Pixel_8     scalar,
                                                                const vImage_Buffer *src,      /* A ARGB interleaved buffer */
                                                                const vImage_Buffer *dest,      /* A ARGB interleaved buffer */
                                                                uint8_t copyMask,               /* Copy plane into  0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue */ 
                                                                vImage_Flags    flags ) VIMAGE_NON_NULL(2,3)		__OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );



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
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest,
 *                  buf->data must be equal to dest->data and buf->rowBytes >= dest->rowBytes
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 * These functions may be used for images with other channel orderings such as RGBAFFFF by adjusting the ordering of the bits in copyMask.
 * See also vImageOverwriteChannelsWithPixel_ARGBFFFF to cover the case where a different value is needed for each channel.
 */
vImage_Error vImageOverwriteChannelsWithScalar_ARGBFFFF(	Pixel_F     scalar,
                                                                const vImage_Buffer *src,      /* A ARGB interleaved buffer */
                                                                const vImage_Buffer *dest,      /* A ARGB interleaved buffer */
                                                                uint8_t copyMask,               /* Copy plane into  0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue */ 
                                                                vImage_Flags    flags ) VIMAGE_NON_NULL(2,3)		__OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

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
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest,
 *                  buf->data must be equal to dest->data and buf->rowBytes >= dest->rowBytes
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 * This function may be used with any 4 channel 8-bit/channel format, such as RGBA8888, BGRA8888 or AYUV8888.
 */
vImage_Error vImagePermuteChannels_ARGB8888(    const vImage_Buffer *src,
                                                const vImage_Buffer *dest,
                                                const uint8_t       permuteMap[4],
                                                vImage_Flags        flags )	VIMAGE_NON_NULL(1,2,3)	__OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

/*
 * vImagePermuteChannels_ARGB16U
 *
 * Reorders the channels of a 4-channel 16-bit/channel image format according 
 * to a permute map.
 *
 * For each pixel in src:
 *
 *	Pixel_ARGB_16U srcPixel, destPixel;
 *	for( int i = 0; i < 4; i++ )
 *		destPixel[i] = srcPixel[ permuteMap[i] ];
 *
 * Operands:
 * ---------
 * src				A pointer to a vImage_Buffer that references the source
 *					pixels.  Unchanged on exit.
 *
 * dest				A pointer to a vImage_Buffer that references where to
 *                  write the permuted result. This pointer is const to indicate 
 *					the vImage_Buffer object is not modified; only the image
 *                  data pointed to by dest->data is changed.
 *					
 *					The dest buffer must have a width and height greater than 
 *					or equal to the src buffer else kvImageBufferSizeMismatch 
 *					is returned.
 *
 * permuteMap		The map describing the permutation of the 4 color channels.
 *					Each value in the map must be 0,1,2, or 3.  A map of 0,1,2,3
 *					is a copy from src->dest while a map of 3,2,1,0 is permutes
 *					ARGB -> BGRA.  Providing a map value greater than 3 will 
 *					result in the return of error kvImageInvalidParameter.
 *
 * flags			The following flags are allowed:
 *
 *		kvImageDoNotTile			Turn off internal multithreading. You may 
 *									wish to do this if you have your own 
 *									multithreading scheme to avoid having the 
 *									two interfere with one another.
 *
 *		kvImageGetTempBufferSize 	Returns 0, if no error. No work is done.
 *
 * Return Value:
 * -------------
 * >= 0                        		Minimum temp buffer size, if 
 *									kvImageGetTempBufferSize was specified.
 *
 * kvImageNoError              		Success!
 *
 * kvImageInvalidParameter   		Parameter permuteMap contained a value
 *									other than 0,1,2, or 3.
 *
 * kvImageBufferSizeMismatch 		The destination buffer must have a height 
 *									and width at least as large as the source 
 *									buffer.
 *
 * kvImageNullPointerArgument		Any of src, dest, permuteMap were NULL.
 *
 * kvImageUnknownFlagsBit			Unexpected flag was passed.
 *
 *
 * This routine will work in place provided that src.data == dest.data and 
 * src.rowBytes >= dest.rowBytes. If src.rowBytes > dest.rowBytes and 
 * src.data == dest.data, the function will only work if you pass 
 * kvImageDoNotTile.
 *
 * This ARGB function can also be used for other channel orders such as RGBA, 
 * BGRA, etc. Additionally the 16U pixel format will work for other 16 bit 
 * pixel formats, such as 16S and 16F. 
 */
    
vImage_Error vImagePermuteChannels_ARGB16U(     const vImage_Buffer *src,
                                                const vImage_Buffer *dest,
                                                const uint8_t       permuteMap[4],
                                                vImage_Flags        flags )
    											VIMAGE_NON_NULL(1,2,3)
    											__OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );

    
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
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest,
 *                  buf->data must be equal to dest->data and buf->rowBytes >= dest->rowBytes
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 * This function may be used with any 4 channel floating-point format, such as RGBAFFFF, BGRAFFFF or AYUVFFF.
 */
vImage_Error vImagePermuteChannels_ARGBFFFF(    const vImage_Buffer *src,
                                                const vImage_Buffer *dest,
                                                const uint8_t       permuteMap[4],
                                                vImage_Flags        flags )	VIMAGE_NON_NULL(1,2,3)		__OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
                                                

    
/*
 * vImagePermuteChannelsWithMaskedInsert_ARGB8888
 *
 * This is in principle vImagePermuteChannels_ARGB8888, followed by vImageOverwriteChannelsWithScalar_ARGB8888.  The fused operation is 
 * provided because it allows you to set different channels to different values (a weakness in vImageOverwriteChannelsWithScalar_ARGB8888)
 * and because neither the Permute or Overwrite functions alone saturate the vector ALU on most architectures, so we think we can get
 * the extra work done in the compound operation for free.  The per-pixel operation is:
 *
 *  Pixel_8888 srcPixel,  destPixel;
 *  uint8_t mask = 0x8;
 *
 *  for( int i = 0; i < 4; i++ )
 *  {
 *      result[i] = srcPixel[ permuteMap[i] ];
 *      if( mask & copyMask )
 *          result[i] = backgroundColor[i];
 *      mask = mask >> 1;
 *  }
 * 
 *  If you intend to just set the entire image to just the backgroundColor, we will detect this case and reroute to vImageBufferFill_ARGB8888.
 *  If it isn't obvious, this will of course work with other non-ARGB channel orderings. You'll need to adjust copyMask accordingly.  The 
 *  backgroundColor should be in the output format.
 *
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest,
 *                  buf->data must be equal to dest->data and buf->rowBytes >= dest->rowBytes
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 *  Flags honored:  kvImageNoFlags, kvImageDoNotTile, kvImageGetTempBufferSize
 */
vImage_Error vImagePermuteChannelsWithMaskedInsert_ARGB8888(    const vImage_Buffer *src,
                                                                const vImage_Buffer *dest,
                                                                const uint8_t permuteMap[4],
                                                                uint8_t copyMask, /* Copy backgroundColor into  0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue */
                                                                const Pixel_8888 backgroundColor,
                                                                vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,5) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0);
    
/*
 * vImagePermuteChannelsWithMaskedInsert_ARGBFFFF
 *
 * This is in principle vImagePermuteChannels_ARGBFFFF, followed by vImageOverwriteChannelsWithScalar_ARGBFFFF.  The fused operation is 
 * provided because it allows you to set different channels to different values (a weakness in vImageOverwriteChannelsWithScalar_ARGBFFFF)
 * and because neither the Permute or Overwrite functions alone saturate the vector ALU on most architectures, so we think we can get
 * the extra work done in the compound operation for free.  The per-pixel operation is:
 *
 *  Pixel_FFFF srcPixel,  destPixel;
 *  uint8_t mask = 0x8;
 *
 *  for( int i = 0; i < 4; i++ )
 *  {
 *      result[i] = srcPixel[ permuteMap[i] ];
 *      if( mask & copyMask )
 *          result[i] = backgroundColor[i];
 *      mask = mask >> 1;
 *  }
 * 
 *  If you intend to just set the entire image to just the backgroundColor, we will detect this case and reroute to vImageBufferFill_ARGBFFFF.
 *  If it isn't obvious, this will of course work with other non-ARGB channel orderings. You'll need to adjust copyMask accordingly. The 
 *  backgroundColor should be in the output format.
 *
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest,
 *                  buf->data must be equal to dest->data and buf->rowBytes >= dest->rowBytes
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 *  Flags honored:  kvImageNoFlags, kvImageDoNotTile, kvImageGetTempBufferSize
 */
vImage_Error vImagePermuteChannelsWithMaskedInsert_ARGBFFFF(    const vImage_Buffer *src,
                                                                const vImage_Buffer *dest,
                                                                const uint8_t permuteMap[4],
                                                                uint8_t copyMask, /* Copy backgroundColor into  0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue */
                                                                const Pixel_FFFF backgroundColor,
                                                                vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,5) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0);


/*
 * vImageConvert_ARGB8888toPlanarF
 *
 *     convert a packed (interleaved) 4-channel 8-bit unsigned buffer to planar float buffers.
 *
 *    For each pixel in src,
 *
 *      float  alpha = (maxFloat[0] - minFloat[0]) * (float) src[0] / 255.0  + minFloat[0];
 *      float    red = (maxFloat[1] - minFloat[1]) * (float) src[1] / 255.0  + minFloat[1];
 *      float  green = (maxFloat[2] - minFloat[2]) * (float) src[2] / 255.0  + minFloat[2];
 *      float   blue = (maxFloat[3] - minFloat[3]) * (float) src[3] / 255.0  + minFloat[3];
 * This routine will not work in place.
 */

vImage_Error    vImageConvert_ARGB8888toPlanarF(
    const vImage_Buffer *src,
    const vImage_Buffer *alpha,
    const vImage_Buffer *red,
    const vImage_Buffer *green,
    const vImage_Buffer *blue,
    const Pixel_FFFF maxFloat,
    const Pixel_FFFF minFloat,
    vImage_Flags flags ) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );

/*
 * vImageConvert_ARGBFFFFtoPlanar8
 *
 *   convert a packed (interleaved) 4-channel float buffer to planar 8 bit unsigned format buffers.
 *
 *      For each pixel in src,
 *
 *      uint8_t alpha = ROUND_TO_INTEGER( CLAMP(0, 255.0f * ( src[0] - minFloat[0], 255 ) / (maxFloat[0] - minFloat[0]) ));
 *      uint8_t   red = ROUND_TO_INTEGER( CLAMP(0, 255.0f * ( src[1] - minFloat[1], 255 ) / (maxFloat[1] - minFloat[1]) ));
 *      uint8_t green = ROUND_TO_INTEGER( CLAMP(0, 255.0f * ( src[2] - minFloat[2], 255 ) / (maxFloat[2] - minFloat[2]) ));
 *      uint8_t  blue = ROUND_TO_INTEGER( CLAMP(0, 255.0f * ( src[3] - minFloat[3], 255 ) / (maxFloat[3] - minFloat[3]) ));
 *
 * This routine will not work in place.
 */

vImage_Error    vImageConvert_ARGBFFFFtoPlanar8(
    const vImage_Buffer *src,
    const vImage_Buffer *alpha,
    const vImage_Buffer *red,
    const vImage_Buffer *green,
    const vImage_Buffer *blue,
    const Pixel_FFFF maxFloat,
    const Pixel_FFFF minFloat,
    vImage_Flags flags ) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );

/*
 * vImageConvert_ARGBFFFFtoRGBFFF
 *
 *     Convert 4-channel ARGB buffer to a 3-channel RGB one, by removing the alpha (1st) channel.
 *
 * This routine will work in place.
 */

vImage_Error    vImageConvert_ARGBFFFFtoRGBFFF(
    const vImage_Buffer *src,
    const vImage_Buffer *dest,
    vImage_Flags flags ) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );

/*
 * vImageConvert_RGBAFFFFtoRGBFFF
 *
 *     Convert 4-channel RGBA buffer to a 3-channel RGB one, by removing the alpha (4th) channel.
 *
 * This routine will work in place.
 */

vImage_Error    vImageConvert_RGBAFFFFtoRGBFFF(
    const vImage_Buffer *src,
    const vImage_Buffer *dest,
    vImage_Flags flags ) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );

/*
 * vImageConvert_BGRAFFFFtoRGBFFF
 *
 *     Convert 4-channel BGRA buffer to a 3-channel RGB one, by removing the alpha (4th) channel, and reordering the other three.
 *
 * This routine will work in place.
 */

vImage_Error    vImageConvert_BGRAFFFFtoRGBFFF(
    const vImage_Buffer *src,
    const vImage_Buffer *dest,
    vImage_Flags flags ) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );



/*
 *  vImageConvert_RGBFFFtoARGBFFFF
 *
 *  Convert/pack a float RGB buffer with a corresponding alpha channel buffer or an alpha factor into a ARGB buffer.
 *
 *      a = a corresponding pixel from the alpha channel buffer, if it exists, or a fixed factor
 *
 *      for each pixel (r,g,b) in src with alpha a,
 *          if (premultiply!=0) dest = (a,r*a,g*a,b*a);
 *          else dest = (a,r,g,b);
 *
 *  Operands:
 *  ---------
 *      rgbSrc      A pointer to a vImage_Buffer that references the source RGB pixels.  Unchanged on exit.
 *      aSrc        A pointer to a vImage_Buffer that references the source alpha channel. Unchanged on exit.
 *      alpha       If aSrc is non-NULL, this parameter is ignored.
 *                  If aSrc is NULL, the value is used for the alpha channel of every pixel.
 *      argbDest    A pointer to a vImage_Buffer that references where to write the converted RGBA data.
 *      flags       The following flags are allowed:
 *
 *          kvImageDoNotTile            Turns off internal multithreading. You may
 *                                      wish to do this if you have your own
 *                                      multithreading scheme to avoid having the
 *                                      two interfere with one another.
 *
 *  Return Value:
 *  -------------
 *      kvImageNoError                      Success!
 *      kvImageNullPointerArgument          rgbSrc or rgbaDest is NULL.
 *      kvImageUnknownFlagsBit              Unknown flag was passed to the function.
 *      kvImageRoiLargerThanInputBuffer     The source buffer must have a size (in both height and width)
 *                                          no less than the destination buffers.
 *
 *  This routine will not work in place.
 */
vImage_Error
vImageConvert_RGBFFFtoARGBFFFF(
                               const vImage_Buffer* /* rgbSrc      */,
                               const vImage_Buffer* /* aSrc        */,
                               Pixel_F              /* alpha       */,
                               const vImage_Buffer* /* argbDest    */,
                               bool                 /* premultiply */,  /* Boolean 1 or 0 */
                               vImage_Flags flags ) VIMAGE_NON_NULL(1,4) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
    
/*
 *  vImageConvert_RGBFFFtoRGBAFFFF
 *
 *  Convert/pack a float RGB buffer with a corresponding alpha channel buffer or an alpha factor into a RGBA buffer.
 *
 *      a = a corresponding pixel from the alpha channel buffer, if it exists, or a fixed factor
 *
 *      for each pixel (r,g,b) in src with alpha a,
 *          if (premultiply!=0) dest = (r*a,g*a,b*a,a);
 *          else dest = (r,g,b,a);
 *
 *  Operands:
 *  ---------
 *      rgbSrc      A pointer to a vImage_Buffer that references the source RGB pixels.  Unchanged on exit.
 *      aSrc        A pointer to a vImage_Buffer that references the source alpha channel. Unchanged on exit.
 *      alpha       If aSrc is non-NULL, this parameter is ignored.
 *                  If aSrc is NULL, the value is used for the alpha channel of every pixel.
 *      rgbaDest    A pointer to a vImage_Buffer that references where to write the converted RGBA data.
 *      flags       The following flags are allowed:
 *
 *          kvImageDoNotTile            Turns off internal multithreading. You may
 *                                      wish to do this if you have your own
 *                                      multithreading scheme to avoid having the
 *                                      two interfere with one another.
 *
 *  Return Value:
 *  -------------
 *      kvImageNoError                      Success!
 *      kvImageNullPointerArgument          rgbSrc or rgbaDest is NULL.
 *      kvImageUnknownFlagsBit              Unknown flag was passed to the function.
 *      kvImageRoiLargerThanInputBuffer     The source buffer must have a size (in both height and width)
 *                                          no less than the destination buffers.
 *
 *  This routine will not work in place.
 */
vImage_Error
vImageConvert_RGBFFFtoRGBAFFFF(
                               const vImage_Buffer* /* rgbSrc      */,
                               const vImage_Buffer* /* aSrc        */,
                               Pixel_F              /* alpha       */,
                               const vImage_Buffer* /* rgbaDest    */,
                               bool                 /* premultiply */,  /* Boolean 1 or 0 */
                               vImage_Flags flags ) VIMAGE_NON_NULL(1,4) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
    
/*
 *  vImageConvert_RGBFFFtoBGRAFFFF
 *
 *  Convert/pack a float RGB buffer with a corresponding alpha channel buffer or an alpha factor into a BGRA buffer.
 *
 *      a = a corresponding pixel from the alpha channel buffer, if it exists, or a fixed factor
 *
 *      for each pixel (r,g,b) in src with alpha a,
 *          if (premultiply!=0) dest = (b*a,g*a,r*a,a);
 *          else dest = (b,g,r,a);
 *
 *  Operands:
 *  ---------
 *      rgbSrc      A pointer to a vImage_Buffer that references the source RGB pixels.  Unchanged on exit.
 *      aSrc        A pointer to a vImage_Buffer that references the source alpha channel. Unchanged on exit.
 *      alpha       If aSrc is non-NULL, this parameter is ignored.  
 *                  If aSrc is NULL, the value is used for the alpha channel of every pixel.
 *      bgraDest    A pointer to a vImage_Buffer that references where to write the converted BGRA data.
 *      flags       The following flags are allowed:
 *
 *          kvImageDoNotTile            Turns off internal multithreading. You may
 *                                      wish to do this if you have your own
 *                                      multithreading scheme to avoid having the
 *                                      two interfere with one another.
 *
 *  Return Value:
 *  -------------
 *      kvImageNoError                      Success!
 *      kvImageNullPointerArgument          rgbSrc or bgraDest is NULL.
 *      kvImageUnknownFlagsBit              Unknown flag was passed to the function.
 *      kvImageRoiLargerThanInputBuffer     The source buffer must have a size (in both height and width)
 *                                          no less than the destination buffers.
 *
 *  This routine will not work in place.
 */
vImage_Error 
vImageConvert_RGBFFFtoBGRAFFFF(
    const vImage_Buffer* /* rgbSrc      */, 
    const vImage_Buffer* /* aSrc        */,
    Pixel_F              /* alpha       */,
    const vImage_Buffer* /* bgraDest    */,
    bool                 /* premultiply */,  /* Boolean 1 or 0 */
    vImage_Flags flags ) VIMAGE_NON_NULL(1,4) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );

#define vImageConvert_BGRFFFtoBGRAFFFF( _bgrSrc, _aSrc, _alpha, _bgraDest, _premultiply, _flags )   \
    vImageConvert_RGBFFFtoRGBAFFFF((_bgrSrc), (_aSrc), (_alpha), (_bgraDest), (_premultiply), (_flags) )
#define vImageConvert_BGRFFFtoRGBAFFFF( _bgrSrc, _aSrc, _alpha, _rgbaDest, _premultiply, _flags )   \
    vImageConvert_RGBFFFtoBGRAFFFF((_bgrSrc), (_aSrc), (_alpha), (_rgbaDest), (_premultiply), (_flags) )


    
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
 *      This function can work in place provided the following are true:
 *          For each buffer "buf" that overlaps with dest,
 *                  buf->data must be equal to dest->data and buf->rowBytes >= dest->rowBytes
 *          If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 */
vImage_Error    vImageConvert_ARGB1555toPlanar8( const vImage_Buffer *src, const vImage_Buffer *destA, const vImage_Buffer *destR, const vImage_Buffer *destG, const vImage_Buffer *destB, vImage_Flags flags )	VIMAGE_NON_NULL(1,2,3,4,5)  __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
vImage_Error    vImageConvert_ARGB1555toARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)  __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
vImage_Error    vImageConvert_Planar8toARGB1555( const vImage_Buffer *srcA, const vImage_Buffer *srcR, const vImage_Buffer *srcG, const vImage_Buffer *srcB, const vImage_Buffer *dest, vImage_Flags flags )	VIMAGE_NON_NULL(1,2,3,4,5)  __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
vImage_Error    vImageConvert_ARGB8888toARGB1555( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)  __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

/*  Convert from 16 bit/pixel RGB565 to 32 bit/pixel ARGB8888 or RGBA8888 or
 *  BGRA8888 formats.  For each pixel:
 *
 *      Pixel8 alpha = alpha;
 *      Pixel8 red   = (5bitRedChannel   * 255 + 15) / 31;
 *      Pixel8 green = (6bitGreenChannel * 255 + 31) / 63;
 *      Pixel8 blue  = (5bitBlueChannel  * 255 + 15) / 31;
 *
 *  The following flags are allowed:
 *
 *      kvImageDoNotTile            Disables internal threading.  You may want
 *                                  to use this if you have your own threading
 *                                  scheme and need to avoid interference.
 *
 *      kvImageGetTempBufferSize    Does no work and returns zero, as this
 *                                  function does not use a temp buffer.
 *
 *  Return values:
 *
 *      kvImageNoError              Success
 *      kvImageUnknownFlagsBit      No work was done because an unknown bit was
 *                                  set in the flags parameter.
 *      kvImageBufferSizeMismatch   No work was done because the source
 *                                  image isn't large enough to cover the
 *                                  destination image.
 *
 *
 *  These functions do not operate in place.
 */

vImage_Error vImageConvert_RGB565toARGB8888(Pixel_8 alpha, const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(2,3) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);
vImage_Error vImageConvert_RGB565toRGBA8888(Pixel_8 alpha, const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(2,3) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
vImage_Error vImageConvert_RGB565toBGRA8888(Pixel_8 alpha, const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(2,3) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
    
/*  Convert from 32 bit/pixel ARGB8888 or RGBA8888 or BGRA8888 formats
 *  to 16 bit/pixel RGB565. for each pixel:
 *
 *      uint32_t red   = (8bitRedChannel   * 31 + 127) / 255;
 *      uint32_t green = (8bitGreenChannel * 63 + 127) / 255;
 *      uint32_t blue  = (8bitBlueChannel  * 31 + 127) / 255;
 *      uint16_t RGB565pixel =  (red << 11) | (green << 5) | blue;
 *
 *  The following flags are allowed:
 *
 *      kvImageDoNotTile            Disables internal threading.  You may want
 *                                  to use this if you have your own threading
 *                                  scheme and need to avoid interference.
 *
 *      kvImageGetTempBufferSize    Does no work and returns zero, as this
 *                                  function does not use a temp buffer.
 *
 *  Return values:
 *
 *      kvImageNoError              Success
 *      kvImageUnknownFlagsBit      No work was done because an unknown bit was
 *                                  set in the flags parameter.
 *      kvImageBufferSizeMismatch   No work was done because the source
 *                                  image isn't large enough to cover the
 *                                  destination image.
 *
 *  These functions operate in place, provided that src->data == dest->data,
 *  src->rowBytes >= dest->rowBytes, and the kvImageDoNotTile flag is used
 *  if src->rowBytes > dest->rowBytes.
 */

vImage_Error vImageConvert_ARGB8888toRGB565(const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);
vImage_Error vImageConvert_RGBA8888toRGB565(const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
vImage_Error vImageConvert_BGRA8888toRGB565(const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
    
/*  Convert between 16 bit/pixel RGB565 and Planar8 formats.  For the forward
 *  conversion, for each pixel:
 *
 *      Pixel8 red   = (5bitRedChannel   * 255 + 15) / 31;
 *      Pixel8 green = (6bitGreenChannel * 255 + 31) / 63;
 *      Pixel8 blue  = (5bitBlueChannel  * 255 + 15) / 31;
 *
 *  For the reverse conversion, for each pixel:
 *
 *      uint32_t red   = (8bitRedChannel   * 31 + 127) / 255;
 *      uint32_t green = (8bitGreenChannel * 63 + 127) / 255;
 *      uint32_t blue  = (8bitBlueChannel  * 31 + 127) / 255;
 *      uint16_t RGB565pixel =  (red << 11) | (green << 5) | blue;
 *
 *  The following flags are allowed:
 *
 *      kvImageDoNotTile            Disables internal threading.  You may want
 *                                  to use this if you have your own threading
 *                                  scheme and need to avoid interference.
 *
 *      kvImageGetTempBufferSize    Does no work and returns zero, as this
 *                                  function does not use a temp buffer.
 *
 *  Return values:
 *
 *      kvImageNoError              Success
 *      kvImageUnknownFlagsBit      No work was done because an unknown bit was
 *                                  set in the flags parameter.
 *      kvImageBufferSizeMismatch   No work was done because the source
 *                                  image isn't large enough to cover the
 *                                  destination image.
 *
 *  These functions do not operate in place.
 */
 
vImage_Error vImageConvert_RGB565toPlanar8(const vImage_Buffer *src, const vImage_Buffer *destR, const vImage_Buffer *destG, const vImage_Buffer *destB, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3,4) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);
vImage_Error vImageConvert_Planar8toRGB565(const vImage_Buffer *srcR, const vImage_Buffer *srcG, const vImage_Buffer *srcB, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3,4) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);

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
 *      In which case:
 *          src->data must be equal to dest->data  and src->rowBytes >= dest->rowBytes
 *          If src has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 *  These functions may also be used with multichannel images formats, such as RGBAFFFF by scaling the width by the number of channels.
 */
vImage_Error    vImageConvert_Planar16FtoPlanarF( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)  __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
vImage_Error    vImageConvert_PlanarFtoPlanar16F( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)  __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );


/*
 *  vImageConvert_Planar8toPlanar16F
 *
 *  Convert from 8 bit integer to 16 bit float format.
 *
 *      destPixel[x] = ConvertToPlanar16F(srcPixel[x]);
 *
 *  The range for conversion is [0,255] -> (half) [0.0, 1.0]
 *
 *  The 16 bit floating point format is half-precision floating point 
 *  (a.k.a.  IEEE-754 binary16, OpenCL half, GL_ARB_half_float_pixel, OpenEXR half).
 *  It has a layout as follows:
 *
 *      16 bits:  seeeeemmmmmmmmmm
 *
 *      1-bit sign | 5 bits of exponent, with a bias of 15 | 10 bits of significand 
 *      (with 11 bits of significance due to the implicit 1 bit)
 *
 *  Operands:
 *  ---------
 *      src             A pointer to a vImage_Buffer that references the source pixels
 *
 *      dest            A pointer to a vImage_Buffer that references the destination pixels
 *
 *      flags           The following flags are allowed:
 *
 *          kvImageDoNotTile            Turns off internal multithreading. You may
 *                                      wish to do this if you have your own
 *                                      multithreading scheme to avoid having the
 *                                      two interfere with one another.
 *
 *  Return Value:
 *  -------------
 *      kvImageNoError                  Success!
 *      kvImageBufferSizeMismatch       Mismatch in width & height of source and destination.
 *      kvImageNullPointerArgument      src or dest pointer is NULL.
 *      kvImageUnknownFlagsBit			Unexpected flag was passed.
 *
 *  This routine will work in place as long as the scan lines overlap exactly.
 *
 *  You can use this for ARGB8888 -> ARGB16F conversions by simply multiplying 
 *  the width of the vImage_Buffer by 4 (for 4 channels)
 */
vImage_Error
vImageConvert_Planar8toPlanar16F(
    const vImage_Buffer *src,
    const vImage_Buffer *dest,
    vImage_Flags flags ) VIMAGE_NON_NULL(1,2)  __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );

/*
 *  vImageConvert_Planar16FtoPlanar8
 *
 *  Convert from 16 bit float to 8 bit integer format.
 *
 *      destPixel[x] = ROUND_TO_INTEGER( SATURATED_CLAMP_0_to_255( 255.0f * (srcPixel[x])));
 *
 *  The ROUND_TO_INTEGER function is round to nearest integer (ties go to the even result).
 *
 *  The 16 bit floating point format is half-precision floating point 
 *  (a.k.a.  IEEE-754 binary16, OpenCL half, GL_ARB_half_float_pixel, OpenEXR half).
 *  It has a layout as follows:
 *
 *      16 bits:  seeeeemmmmmmmmmm
 *
 *      1-bit sign | 5 bits of exponent, with a bias of 15 | 10 bits of significand 
 *      (with 11 bits of significance due to the implicit 1 bit)
 *
 *  All NaNs are converted to 0.
 *  To set/inspect the current IEEE-754 rounding mode, please see appropriate utilities in fenv.h
 *
 *  Operands:
 *  ---------
 *      src             A pointer to a vImage_Buffer that references the source pixels
 *
 *      dest            A pointer to a vImage_Buffer that references the destination pixels
 *
 *      flags           The following flags are allowed:
 *
 *          kvImageDoNotTile            Turns off internal multithreading. You may
 *                                      wish to do this if you have your own
 *                                      multithreading scheme to avoid having the
 *                                      two interfere with one another.
 *
 *  Return Value:
 *  -------------
 *      kvImageNoError                  Success!
 *      kvImageBufferSizeMismatch       Mismatch in width & height of source and destination.
 *      kvImageNullPointerArgument      src or dest pointer is NULL.
 *      kvImageUnknownFlagsBit			Unexpected flag was passed.
 *
 *  This routine will work in place as long as the scan lines overlap exactly.
 *
 *  You can use this for ARGB16F -> ARGB8888 conversions by simply multiplying 
 *  the width of the vImage_Buffer by 4 (for 4 channels)
 */
vImage_Error
vImageConvert_Planar16FtoPlanar8(
    const vImage_Buffer *src,
    const vImage_Buffer *dest,
    vImage_Flags flags ) VIMAGE_NON_NULL(1,2)  __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );


/*
 * vImageConvert_16UToPlanar8
 *      Convert a planar (or interleaved -- multiply vImage_Buffer.width by 4) vImage_Buffer of 16 bit unsigned shorts to a buffer containing 8 bit integer values.
 *      For each 16 bit pixel in src:
 *
 *          uint8_t result = (srcPixel * 255 + 32767) / 65535;
 *
 *      To convert 4 channel interleaved unsigned 16 bit data to ARGB_8888, simply multiply the vImage_Buffer.width by 4.
 *
 *  This can work in place, though the contents of the unused half of the buffer are undefined
 *      In which case:
 *          src->data must be equal to dest->data  and src->rowBytes >= dest->rowBytes
 *          If src has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 *
 *  This function may also be used with multichannel images formats, such as RGBA16U -> RGBA8888 by scaling the width by the number of channels.
 */
vImage_Error vImageConvert_16UToPlanar8( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

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
vImage_Error vImageConvert_Planar8To16U( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

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
 *  Pass NULL for aSrc to use alpha instead.
 */
 vImage_Error vImageConvert_RGB888toARGB8888(   const vImage_Buffer* /* rgbSrc */, 
                                                const vImage_Buffer* /* aSrc */, 
                                                Pixel_8 /* alpha */, 
                                                const vImage_Buffer* /*argbDest*/, 
                                                bool /* premultiply */,  /* Boolean 1 or 0 */ 
                                                vImage_Flags /* flags */ ) VIMAGE_NON_NULL(1,4) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
vImage_Error vImageConvert_RGB888toRGBA8888(    const vImage_Buffer * /* rgbSrc */, 
                                                const vImage_Buffer * /* aSrc */, 
                                                Pixel_8 /* alpha */, 
                                                const vImage_Buffer * /* rgbaDest */, 
                                                bool /* premultiply */,  /* Boolean 1 or 0 */ 
                                                vImage_Flags /* flags */ ) VIMAGE_NON_NULL(1,4) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_6_0 );
vImage_Error vImageConvert_RGB888toBGRA8888(    const vImage_Buffer * /* rgbSrc, */,
                                                const vImage_Buffer * /* aSrc */, 
                                                Pixel_8 /* alpha */, 
                                                const vImage_Buffer * /* bgraDest */, 
                                                bool /* premultiply */,  /* Boolean 1 or 0 */ 
                                                vImage_Flags /* flags */ ) VIMAGE_NON_NULL(1,4) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_6_0 );
#define vImageConvert_BGR888toBGRA8888( _bgrSrc, _aSrc, _alpha, _bgraDest, _premultiply, _flags )   vImageConvert_RGB888toRGBA8888((_bgrSrc), (_aSrc), (_alpha), (_bgraDest), (_premultiply), (_flags) ) 
#define vImageConvert_BGR888toRGBA8888( _bgrSrc, _aSrc, _alpha, _rgbaDest, _premultiply, _flags )   vImageConvert_RGB888toBGRA8888((_bgrSrc), (_aSrc), (_alpha), (_rgbaDest), (_premultiply), (_flags) ) 
    
/*
 *  Convert 4 channel buffer to a 3 channel one, by removing the 1st channel.
 *  The R,G and B channels are simply copied into the new buffer.
 *
 *  This can work in place, though the contents of the unused half of the buffer are undefined
 *      In which case:
 *          src->data must be equal to dest->data  and src->rowBytes >= dest->rowBytes
 *          If src has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 */
vImage_Error vImageConvert_ARGB8888toRGB888(    const vImage_Buffer * /*argbSrc*/, 
                                                const vImage_Buffer * /*rgbDest*/, 
                                                vImage_Flags /* flags */ ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
vImage_Error vImageConvert_RGBA8888toRGB888(    const vImage_Buffer * /*rgbaSrc*/, 
                                                const vImage_Buffer * /*rgbDest*/, 
                                                vImage_Flags /* flags */ ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_6_0 );
vImage_Error vImageConvert_BGRA8888toRGB888(    const vImage_Buffer * /* bgraSrc */,
                                                const vImage_Buffer * /* rgbDest */, 
                                                vImage_Flags /* flags */ ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_6_0 );
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
 *
 *  Note: that regardless of the value of isImagePremultiplied, the result image is premultiplied by alpha. If the backgroundColor 
 *  was not opaque and you want a non-premultiplied image, you will still need to unpremultiply the result. 
 */
vImage_Error  vImageFlatten_ARGB8888ToRGB888( 
                                                const vImage_Buffer * /* argb8888Src */, 
                                                const vImage_Buffer * /* rgb888dest */, 
                                                const Pixel_8888   /* backgroundColor */,    /* background color is assumed to have a 255 alpha channel */
                                                bool      /* isImagePremultiplied */,
                                                vImage_Flags     /* flags */
                                            ) VIMAGE_NON_NULL(1,2,3) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
vImage_Error  vImageFlatten_ARGBFFFFToRGBFFF( 
                                                const vImage_Buffer * /* argbFFFFSrc */, 
                                                const vImage_Buffer * /* rgbFFFdest */, 
                                                const Pixel_FFFF   /* backgroundColor */,    /* background color is assumed to have a 1.0f alpha channel */
                                                bool      /* isImagePremultiplied */,
                                                vImage_Flags     /* flags */
                                            ) VIMAGE_NON_NULL(1,2,3) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
vImage_Error  vImageFlatten_RGBA8888ToRGB888( 
                                             const vImage_Buffer * /* rgba8888Src */, 
                                             const vImage_Buffer * /* rgb888dest */, 
                                             const Pixel_8888   /* backgroundColor */,    /* background color is assumed to have a 255 alpha channel */
                                             bool      /* isImagePremultiplied */,
                                             vImage_Flags     /* flags */
                                             ) VIMAGE_NON_NULL(1,2,3) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_6_0 );
vImage_Error  vImageFlatten_RGBAFFFFToRGBFFF( 
                                             const vImage_Buffer * /* rgbaFFFFSrc */, 
                                             const vImage_Buffer * /* rgbFFFdest */, 
                                             const Pixel_FFFF   /* backgroundColor */,    /* background color is assumed to have a 1.0f alpha channel */
                                             bool      /* isImagePremultiplied */,
                                             vImage_Flags     /* flags */
                                             ) VIMAGE_NON_NULL(1,2,3) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_6_0 );
vImage_Error  vImageFlatten_BGRA8888ToRGB888( 
                                             const vImage_Buffer * /* bgra8888Src */, 
                                             const vImage_Buffer * /* rgb888dest */, 
                                             const Pixel_8888   /* backgroundColor */,    /* background color is assumed to have a 255 alpha channel */
                                             bool      /* isImagePremultiplied */,
                                             vImage_Flags     /* flags */
                                             ) VIMAGE_NON_NULL(1,2,3) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_6_0 );
vImage_Error  vImageFlatten_BGRAFFFFToRGBFFF( 
                                             const vImage_Buffer * /* bgraFFFFSrc */, 
                                             const vImage_Buffer * /* rgbFFFdest */, 
                                             const Pixel_FFFF   /* backgroundColor */,    /* background color is assumed to have a 1.0f alpha channel */
                                             bool      /* isImagePremultiplied */,
                                             vImage_Flags     /* flags */
                                             ) VIMAGE_NON_NULL(1,2,3) __OSX_AVAILABLE_STARTING( __MAC_10_8, __IPHONE_6_0 );
#define vImageFlatten_BGRA8888ToBGR888( _bgra8888Src, _bgr888Dest, _backgroundColor, _isImagePremultiplied, _flags )        \
        vImageFlatten_RGBA8888ToRGB888( (_bgra8888Src), (_bgr888Dest), (_backgroundColor), (_isImagePremultiplied), (_flags) )
#define vImageFlatten_RGBA8888ToBGR888( _rgba8888Src, _bgr888Dest, _backgroundColor, _isImagePremultiplied, _flags )        \
        vImageFlatten_BGRA8888ToRGB888( (_rgba8888Src), (_bgr888Dest), (_backgroundColor), (_isImagePremultiplied), (_flags) )
#define vImageFlatten_BGRAFFFFToBGRFFF( _bgraFFFFSrc, _bgrFFFDest, _backgroundColor, _isImagePremultiplied, _flags )        \
        vImageFlatten_RGBAFFFFToRGBFFF( (_bgraFFFFSrc), (_bgrFFFDest), (_backgroundColor), (_isImagePremultiplied), (_flags) )
#define vImageFlatten_RGBAFFFFToBGRFFF( _rgbaFFFFSrc, _bgrFFFDest, _backgroundColor, _isImagePremultiplied, _flags )        \
        vImageFlatten_BGRAFFFFToRGBFFF( (_rgbaFFFFSrc), (_bgrFFFDest), (_backgroundColor), (_isImagePremultiplied), (_flags) )

    
/*
 *  Convert 3 planar buffers to a 3 channel interleave buffer.
 *
 *  Does not work in place
 *  This may be used to produce other channel orderings by changing the order of the planar buffers passed into the function.
 */
vImage_Error vImageConvert_Planar8toRGB888( const vImage_Buffer *planarRed, const vImage_Buffer *planarGreen, const vImage_Buffer *planarBlue, const vImage_Buffer *rgbDest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,4) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
vImage_Error vImageConvert_PlanarFtoRGBFFF( const vImage_Buffer *planarRed, const vImage_Buffer *planarGreen, const vImage_Buffer *planarBlue, const vImage_Buffer *rgbDest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,4) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

/*
 *  Convert a 3 channel interleave buffer to 3 planar buffers.
 *
 *  Does not work in place
 *  This may be used to consume other channel orderings by changing the order of the planar buffers passed into the function.
 */
vImage_Error vImageConvert_RGB888toPlanar8( const vImage_Buffer *rgbSrc, const vImage_Buffer *redDest, const vImage_Buffer *greenDest, const vImage_Buffer *blueDest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,4) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
vImage_Error vImageConvert_RGBFFFtoPlanarF( const vImage_Buffer *rgbSrc, const vImage_Buffer *redDest, const vImage_Buffer *greenDest, const vImage_Buffer *blueDest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,4) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 ); 


/*
 *  Does the same thing as vImageOverwriteChannels_ARGB8888 except that the newSrc buffer is formatted as ARGB8888
 *  If the appropriate copyMask bit is set, then the color channel from newSrc is used. Otherwise the color channel from origSrc is used.
 *  We note that functions of this kind only exist for interleaved buffers. If you had been using planar data, this would just be a pointer swap.
 *  This will work for other channel orderings, such as RGBA8888.  You need to adjust the ordering of the bits in copyMask to compensate.
 *  This can work in place provided that for each buffer "buf" that overlaps with dest:
 *          buf->data must be equal to dest->data and buf->rowBytes >= dest->rowBytes
 *          If buf has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
*/
vImage_Error	vImageSelectChannels_ARGB8888( const vImage_Buffer *newSrc,       /* A ARGB interleaved buffer */
                                                const vImage_Buffer *origSrc,      /* A ARGB interleaved buffer */
                                                const vImage_Buffer *dest,      /* A ARGB interleaved buffer */
                                                uint8_t copyMask,               /* Copy plane into  0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue */ 
                                                vImage_Flags    flags ) VIMAGE_NON_NULL(1,2,3) __OSX_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_5_0 );

vImage_Error	vImageSelectChannels_ARGBFFFF( const vImage_Buffer *newSrc,       /* A ARGB interleaved buffer */
                                                const vImage_Buffer *origSrc,      /* A ARGB interleaved buffer */
                                                const vImage_Buffer *dest,      /* A ARGB interleaved buffer */
                                                uint8_t copyMask,               /* Copy plane into  0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue */ 
                                                vImage_Flags    flags ) VIMAGE_NON_NULL(1,2,3) __OSX_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_5_0 );

/*
 *  The following are like vImageOverwriteChannelsWithScalar_ARGB*, except that they take a ARGB input pixel, instead of a planar one. 
 *  This will work for other channel orderings, such as RGBA8888. You will need to adjust the ordering of bits in copyMask to compensate.
 *  This can work in place provided that for each buffer "buf" that overlaps with dest:
 *          buf->data must be equal to dest->data and buf->rowBytes >= dest->rowBytes
 *          If buf has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 */
vImage_Error vImageOverwriteChannelsWithPixel_ARGB8888( const Pixel_8888     the_pixel,
                                                        const vImage_Buffer *src,      /* A ARGB interleaved buffer */
                                                        const vImage_Buffer *dest,      /* A ARGB interleaved buffer */
                                                        uint8_t copyMask,               /* Copy plane into  0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue */ 
                                                        vImage_Flags    flags ) VIMAGE_NON_NULL(2,3) __OSX_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_5_0 );

vImage_Error vImageOverwriteChannelsWithPixel_ARGB16U( const Pixel_ARGB_16U     the_pixel,
                                                       const vImage_Buffer *src,      /* A ARGB interleaved buffer */
                                                       const vImage_Buffer *dest,      /* A ARGB interleaved buffer */
                                                       uint8_t copyMask,               /* Copy plane into  0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue */
                                                       vImage_Flags    flags ) VIMAGE_NON_NULL(2,3) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );

vImage_Error vImageOverwriteChannelsWithPixel_ARGBFFFF( const Pixel_FFFF     the_pixel,
                                                        const vImage_Buffer *src,      /* A ARGB interleaved buffer */
                                                        const vImage_Buffer *dest,      /* A ARGB interleaved buffer */
                                                        uint8_t copyMask,               /* Copy plane into  0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue */ 
                                                        vImage_Flags    flags ) VIMAGE_NON_NULL(2,3) __OSX_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_5_0 );


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
vImage_Error    vImageConvert_Planar8ToXRGB8888( Pixel_8 alpha, const vImage_Buffer *red, const vImage_Buffer *green, const vImage_Buffer *blue, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(2,3,4,5)    __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_5_0 );
vImage_Error    vImageConvert_Planar8ToBGRX8888( const vImage_Buffer *blue, const vImage_Buffer *green, const vImage_Buffer *red, Pixel_8 alpha, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,5)    __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_5_0 );
#define         vImageConvert_Planar8ToRGBX8888( _red, _green, _blue, _alpha, _dest, _flags )   vImageConvert_Planar8ToBGRX8888((_red), (_green), (_blue), (_alpha), (_dest), (_flags))
vImage_Error    vImageConvert_PlanarFToXRGBFFFF( Pixel_F alpha, const vImage_Buffer *red, const vImage_Buffer *green, const vImage_Buffer *blue, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(2,3,4,5)    __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_5_0 );
vImage_Error    vImageConvert_PlanarFToBGRXFFFF( const vImage_Buffer *blue, const vImage_Buffer *green, const vImage_Buffer *red, Pixel_F alpha, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,5)    __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_5_0 );
#define         vImageConvert_PlanarFToRGBXFFFF( _red, _green, _blue, _alpha, _dest, _flags )   vImageConvert_PlanarFToBGRXFFFF( (_red), (_green), (_blue), (_alpha), (_dest), (_flags))
    
/*
 *  The following functions de-interleave a XRGB, BGRX, or RGBX four-channel
 *  buffer to create three planar buffers red, green, and blue, discarding
 *  the fourth channel.  These functions do not work in place.  As with all
 *  vImage functions, channel order is memory order.
 *
 *  Flags:
 *      kvImageGetTempBufferSize    Returns 0, does nothing.
 *      kvImageDoNotTile            Disables internal multithreading.
 *
 *      Other flags cause the function to return kvImageUnknownFlagsBit.
 */

vImage_Error vImageConvert_XRGB8888ToPlanar8(const vImage_Buffer *src,
                                             const vImage_Buffer *red,
                                             const vImage_Buffer *green,
                                             const vImage_Buffer *blue,
                                             vImage_Flags flags)
    VIMAGE_NON_NULL(1,2,3,4)
    __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
    
vImage_Error vImageConvert_BGRX8888ToPlanar8(const vImage_Buffer *src,
                                             const vImage_Buffer *blue,
                                             const vImage_Buffer *green,
                                             const vImage_Buffer *red,
                                             vImage_Flags flags)
    VIMAGE_NON_NULL(1,2,3,4)
    __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
    
#define vImageConvert_RGBX8888ToPlanar8(_src, _red, _green, _blue, _flags) \
    vImageConvert_BGRX8888ToPlanar8((_src), (_red), (_green), (_blue), (_flags))
    
vImage_Error vImageConvert_XRGBFFFFToPlanarF(const vImage_Buffer *src,
                                             const vImage_Buffer *red,
                                             const vImage_Buffer *green,
                                             const vImage_Buffer *blue,
                                             vImage_Flags flags)
    VIMAGE_NON_NULL(1,2,3,4)
    __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
    
vImage_Error vImageConvert_BGRXFFFFToPlanarF(const vImage_Buffer *src,
                                             const vImage_Buffer *blue,
                                             const vImage_Buffer *green,
                                             const vImage_Buffer *red,
                                             vImage_Flags flags)
    VIMAGE_NON_NULL(1,2,3,4)
    __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
    
#define vImageConvert_RGBXFFFFToPlanarF(_src, _red, _green, _blue, _flags) \
    vImageConvert_BGRXFFFFToPlanarF((_src), (_red), (_green), (_blue), (_flags))
    
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
vImage_Error    vImageConvert_Planar8ToARGBFFFF( const vImage_Buffer *alpha, const vImage_Buffer *red, const vImage_Buffer *green, const vImage_Buffer *blue, const vImage_Buffer *dest, const Pixel_FFFF maxFloat, const Pixel_FFFF minFloat, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,4,5) __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_5_0 );
vImage_Error    vImageConvert_Planar8ToXRGBFFFF( Pixel_F alpha, const vImage_Buffer *red, const vImage_Buffer *green, const vImage_Buffer *blue, const vImage_Buffer *dest, const Pixel_FFFF maxFloat, const Pixel_FFFF minFloat, vImage_Flags flags ) VIMAGE_NON_NULL(2,3,4,5) __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_5_0 );
vImage_Error    vImageConvert_Planar8ToBGRXFFFF(const vImage_Buffer *blue, const vImage_Buffer *green, const vImage_Buffer *red, Pixel_F alpha, const vImage_Buffer *dest, const Pixel_FFFF maxFloat, const Pixel_FFFF minFloat, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,5) __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_5_0 );
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
 *  These can work in place provided that for each buffer "buf" that overlaps with dest:
 *          buf->data must be equal to dest->data and buf->rowBytes >= dest->rowBytes
 *          If buf has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 */
vImage_Error    vImageConvert_PlanarFToARGB8888( const vImage_Buffer *alpha, const vImage_Buffer *red, const vImage_Buffer *green, const vImage_Buffer *blue, const vImage_Buffer *dest, const Pixel_FFFF maxFloat, const Pixel_FFFF minFloat, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,4,5,6,7) __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_5_0 );
vImage_Error    vImageConvert_PlanarFToXRGB8888( Pixel_8 alpha, const vImage_Buffer *red, const vImage_Buffer *green, const vImage_Buffer *blue, const vImage_Buffer *dest, const Pixel_FFFF maxFloat, const Pixel_FFFF minFloat, vImage_Flags flags ) VIMAGE_NON_NULL(2,3,4,5,6,7) __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_5_0 );
vImage_Error    vImageConvert_PlanarFToBGRX8888( const vImage_Buffer *blue, const vImage_Buffer *green, const vImage_Buffer *red, Pixel_8 alpha, const vImage_Buffer *dest, const Pixel_FFFF maxFloat, const Pixel_FFFF minFloat, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,5,6,7) __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_5_0 );
#define         vImageConvert_PlanarFToRGBX8888( _red, _green, _blue, _alpha, _dest, _maxFloat, _minFloat, _flags )     vImageConvert_PlanarFToBGRX8888((_red), (_green), (_blue), (_alpha), (_dest), (_maxFloat), (_minFloat), (_flags))

/*
 *  vImageConvert_RGB16UtoARGB16U
 *
 *  Convert RGB16U -> ARGB16U
 *
 *
 *  vImageConvert_RGB16UtoRGBA16U
 *
 *  Convert RGB16U -> RGBA16U
 *
 *
 *  vImageConvert_RGB16UtoBGRA16U
 *
 *  Convert RGB16U -> BGRA16U
 *
 *
 *  Each channel is 16 bit unsigned.
 *  3-channel interleaved pixel buffers that contains RGB and 1 planar pixel buffer for A or
 *  'alpha' value are combined to create 4-channel interleaved pixel buffer.
 *  'premultiply' determines if this function will premultiply alpha value(s) to RGB values.
 *
 *  if (aSrc != NULL)
 *  {
 *     if (premultiply)
 *     {
 *         r = (aSrc[i] * rgb[i*3+0] + 32767) / 65535
 *         g = (aSrc[i] * rgb[i*3+1] + 32767) / 65535
 *         b = (aSrc[i] * rgb[i*3+2] + 32767) / 65535
 *
 *         argbDest[i*4+0] = aSrc[i];
 *         argbDest[i*4+1] = r;
 *         argbDest[i*4+2] = g;
 *         argbDest[i*4+3] = b;
 *     }
 *     else
 *     {
 *         argbDest[i*4+0] = aSrc[i];
 *         argbDest[i*4+1] = rgb[i*3+0];
 *         argbDest[i*4+2] = rgb[i*3+1];
 *         argbDest[i*4+3] = rgb[i*3+2];
 *     }
 *  }
 *  else
 *  {
 *     if (premultiply)
 *     {
 *         r = (alpha * rgb[i*3+0] + 32767) / 65535
 *         g = (alpha * rgb[i*3+1] + 32767) / 65535
 *         b = (alpha * rgb[i*3+2] + 32767) / 65535
 *
 *         argbDest[i*4+0] = alpha;
 *         argbDest[i*4+1] = r;
 *         argbDest[i*4+2] = g;
 *         argbDest[i*4+3] = b;
 *     }
 *     else
 *     {
 *         argbDest[i*4+0] = alpha;
 *         argbDest[i*4+1] = rgb[i*3+0];
 *         argbDest[i*4+2] = rgb[i*3+1];
 *         argbDest[i*4+3] = rgb[i*3+2];
 *     }
 *  }
 *
 *  Operands:
 *  ---------
 *  rgbSrc : A pointer to vImage_Buffer that references RGB interleaved source pixels
 *
 *  aSrc : A pointer to vImage_Buffer that references A planar source pixels
 *
 *  alpha : A single alpha value
 *
 *  argbDest / rgbaDest / bgraDest : A pointer to vImage_Buffer that references ARGB / RGBA / BGRA interleaved destination pixels
 *
 *  Flags:
 *  ------
 *      kvImageGetTempBufferSize    Returns 0. Does no work.
 *      kvImageDoNotTile            Disables internal multithreading, if any.
 *
 *  Return Value:
 *  -------------
 *      kvImageNoError              Is returned when there was no error.
 *      kvImageBufferSizeMismatch   Is returned when there is a mismatch in width & height of source and destination.
 *      kvImageUnknownFlagsBit      Is returned when there is a unknown flag.
 *
 *  This function will not work in place.
 *
 */
vImage_Error vImageConvert_RGB16UtoARGB16U( const vImage_Buffer *rgbSrc, const vImage_Buffer *aSrc, Pixel_16U alpha, const vImage_Buffer *argbDest, bool premultiply, vImage_Flags flags ) VIMAGE_NON_NULL(1,4) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
vImage_Error vImageConvert_RGB16UtoRGBA16U( const vImage_Buffer *rgbSrc, const vImage_Buffer *aSrc, Pixel_16U alpha, const vImage_Buffer *rgbaDest, bool premultiply, vImage_Flags flags ) VIMAGE_NON_NULL(1,4) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
vImage_Error vImageConvert_RGB16UtoBGRA16U( const vImage_Buffer *rgbSrc, const vImage_Buffer *aSrc, Pixel_16U alpha, const vImage_Buffer *bgraDest, bool premultiply, vImage_Flags flags ) VIMAGE_NON_NULL(1,4) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );

/*
 *
 *  vImageConvert_ARGB16UtoRGB16U
 *
 *  Convert ARGB16U -> RGB16U
 *
 *
 *  vImageConvert_RGBA16UtoRGB16U
 *
 *  Convert RGBA16U -> RGB16U
 *
 *
 *  vImageConvert_BGRA16UtoRGB16U
 *
 *  Convert BGRA16U -> RGB16U
 *
 *
 *  Each channel is 16-bit unsigned
 *  4-channel interleaved pixel buffer becomes 3-channel interleaved pixel buffer by skipping to copy
 *  the first channel in 4-channel interleaved pixel buffer.
 *
 *  rgbDest[i*3+0] = argbSrc[i*4+1];
 *  rgbDest[i*3+1] = argbSrc[i*4+2];
 *  rgbDest[i*3+2] = argbSrc[i*4+3];
 *
 *  Operands:
 *  ---------
 *  argbSrc / rgbaSrc / bgraSrc : A pointer to vImage_Buffer that references ARGB / RGBA / BGRA interleaved source pixels
 *
 *  rgbDest : A pointer to vImage_Buffer that references RGB interleaved destination pixels
 *
 *  Flags:
 *  ------
 *      kvImageGetTempBufferSize    Returns 0. Does no work.
 *      kvImageDoNotTile            Disables internal multithreading, if any.
 *
 *  Return Value:
 *  -------------
 *      kvImageNoError              Is returned when there was no error.
 *      kvImageBufferSizeMismatch   Is returned when there is a mismatch in width & height of source and destination.
 *      kvImageUnknownFlagsBit      Is returned when there is a unknown flag.
 *
 *  vImageConvert_RGBA16UtoRGB16U() can work in place if (argbSrc.data == rgbDest.data) && (argbSrc.rowBytes == rgbDest.rowBytes)
 *  Rest of cases in these 3 functions will not work in place.
 *
 */
vImage_Error vImageConvert_ARGB16UtoRGB16U( const vImage_Buffer *argbSrc, const vImage_Buffer *rgbDest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
vImage_Error vImageConvert_RGBA16UtoRGB16U( const vImage_Buffer *rgbaSrc, const vImage_Buffer *rgbDest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
vImage_Error vImageConvert_BGRA16UtoRGB16U( const vImage_Buffer *bgraSrc, const vImage_Buffer *rgbDest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );

/*
 *  vImageConvert_Planar16UtoARGB16U
 *
 *  Convert Planar16U -> ARGB16U
 *
 *
 *  Each channel is 16-bit unsigned
 *  4 planar pixel buffers are combined to create 4-channel interleaved pixel buffers.
 *
 *  argbDest[i*4+0] = aSrc[i];
 *  argbDest[i*4+1] = rSrc[i];
 *  argbDest[i*4+2] = gSrc[i];
 *  argbDest[i*4+3] = bSrc[i];
 *
 *  This function can be used to create any channel order from 4 planar pixel buffers to interleaved
 *  pixel buffers.
 *
 *  Operands:
 *  ---------
 *  aSrc : A pointer to vImage_Buffer that references A planar source pixels
 *
 *  rSrc : A pointer to vImage_Buffer that references R planar source pixels
 *
 *  gSrc : A pointer to vImage_Buffer that references G planar source pixels
 *
 *  bSrc : A pointer to vImage_Buffer that references B planar source pixels
 *
 *  argbDest : A pointer to vImage_Buffer that references ARGB interleaved destination pixels
 *
 *  Flags:
 *  ------
 *      kvImageGetTempBufferSize    Returns 0. Does no work.
 *      kvImageDoNotTile            Disables internal multithreading, if any.
 *
 *  Return Value:
 *  -------------
 *      kvImageNoError              Is returned when there was no error.
 *      kvImageBufferSizeMismatch   Is returned when there is a mismatch in width & height of source and destination.
 *      kvImageUnknownFlagsBit      Is returned when there is a unknown flag.
 *
 *  This function will not work in place.
 *
 */
vImage_Error vImageConvert_Planar16UtoARGB16U(const vImage_Buffer *aSrc, const vImage_Buffer *rSrc, const vImage_Buffer *gSrc, const vImage_Buffer *bSrc, const vImage_Buffer *argbDest, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3,4,5) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );

/*
 *  vImageConvert_ARGB16UtoPlanar16U
 *
 *  Convert ARGB16U -> Planar16U
 *
 *
 *  Each channel is 16-bit unsigned
 *  Each channel of 4-channel interleaved pixel buffer are copied into its planar pixel buffer.
 *
 *  aDest[i] = argbSrc[i*4+0];
 *  rDest[i] = argbSrc[i*4+1];
 *  gDest[i] = argbSrc[i*4+2];
 *  bDest[i] = argbSrc[i*4+3];
 *
 *  This function can be used to create any channel order from interleaved pixel buffers to 4 planar
 *  pixel buffers.
 *
 *  Operands:
 *  ---------
 *  argbSrc : A pointer to vImage_Buffer that references ARGB interleaved source pixels
 *
 *  aDest : A pointer to vImage_Buffer that references A planar destination pixels
 *
 *  rDest : A pointer to vImage_Buffer that references R planar destination pixels
 *
 *  gDest : A pointer to vImage_Buffer that references G planar destination pixels
 *
 *  bDest : A pointer to vImage_Buffer that references B planar destination pixels
 *
 *  Flags:
 *  ------
 *      kvImageGetTempBufferSize    Returns 0. Does no work.
 *      kvImageDoNotTile            Disables internal multithreading, if any.
 *
 *  Return Value:
 *  -------------
 *      kvImageNoError              Is returned when there was no error.
 *      kvImageBufferSizeMismatch   Is returned when there is a mismatch in width & height of source and destination.
 *      kvImageUnknownFlagsBit      Is returned when there is a unknown flag.
 *
 *  This function will not work in place.
 *
 */
vImage_Error vImageConvert_ARGB16UtoPlanar16U(const vImage_Buffer *argbSrc, const vImage_Buffer *aDest, const vImage_Buffer *rDest, const vImage_Buffer *gDest, const vImage_Buffer *bDest, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3,4,5) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );


/*
 *  vImageConvert_Planar16UtoRGB16U
 *
 *  Planar16U -> RGB16U
 *
 *
 *  Each channel is 16-bit unsigned
 *  3 planar pixel buffers are combined to create 3-channel interleaved pixel buffer.
 *
 *  rgbDest[i*3+0] = rSrc[i];
 *  rgbDest[i*3+1] = gSrc[i];
 *  rgbDest[i*3+2] = bSrc[i];
 *
 *  This function can be used to create any channel order from 3 planar pixel buffers to interleaved
 *  pixel buffers.
 *
 *  Operands:
 *  ---------
 *  rSrc : A pointer to vImage_Buffer that references R planar source pixels
 *
 *  gSrc : A pointer to vImage_Buffer that references G planar source pixels
 *
 *  bSrc : A pointer to vImage_Buffer that references B planar source pixels
 *
 *  rgbDest : A pointer to vImage_Buffer that references RGB interleaved destination pixels
 *
 *  Flags:
 *  ------
 *      kvImageGetTempBufferSize    Returns 0. Does no work.
 *      kvImageDoNotTile            Disables internal multithreading, if any.
 *
 *  Return Value:
 *  -------------
 *      kvImageNoError              Is returned when there was no error.
 *      kvImageBufferSizeMismatch   Is returned when there is a mismatch in width & height of source and destination.
 *      kvImageUnknownFlagsBit      Is returned when there is a unknown flag.
 *
 *  This function will not work in place.
 *
 */
vImage_Error vImageConvert_Planar16UtoRGB16U( const vImage_Buffer *rSrc, const vImage_Buffer *gSrc, const vImage_Buffer *bSrc, const vImage_Buffer *rgbDest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,4) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );

/*
 *  vImageConvert_RGB16UtoPlanar16U
 *
 *  Planar16U <- RGB16U
 *
 *  Each channel is 16-bit unsigned
 *  Each channel of 3-channel interleaved pixel buffer are copied into its planar pixel buffer.
 *
 *  rDest[i] = rgbSrc[i*3+0];
 *  gDest[i] = rgbSrc[i*3+1];
 *  bDest[i] = rgbSrc[i*3+2];
 *
 *  This function can be used to create any channel order from interleaved pixel buffers to 3 planar
 *  pixel buffers.
 *
 *  Operands:
 *  ---------
 *  rgbSrc : A pointer to vImage_Buffer that references RGB interleaved source pixels
 *
 *  rDest : A pointer to vImage_Buffer that references R planar destination pixels
 *
 *  gDest : A pointer to vImage_Buffer that references G planar destination pixels
 *
 *  bDest : A pointer to vImage_Buffer that references B planar destination pixels
 *
 *  Flags:
 *  ------
 *      kvImageGetTempBufferSize    Returns 0. Does no work.
 *      kvImageDoNotTile            Disables internal multithreading, if any.
 *
 *  Return Value:
 *  -------------
 *      kvImageNoError              Is returned when there was no error.
 *      kvImageBufferSizeMismatch   Is returned when there is a mismatch in width & height of source and destination.
 *      kvImageUnknownFlagsBit      Is returned when there is a unknown flag.
 *
 *  This function will not work in place.
 *
 */
vImage_Error vImageConvert_RGB16UtoPlanar16U( const vImage_Buffer *rgbSrc, const vImage_Buffer *rDest, const vImage_Buffer *gDest, const vImage_Buffer *bDest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,4) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
    
/*
 *  vImageConvert_ARGB16UToARGB8888
 *
 *  This function does 3 things.
 *  1. Converts 16-bit unsigned ARGB interleaved pixels into 8-bit unsigned ARGB interleaved pixels.
 *  2. Changes the order of channels according to permuteMap
 *  3. Selects between the result pixel and the backgroundColor according to the bits in copyMask.
 *
 *  permuteMap[i] = 0, 1, 2, or 3 to specify how we permute each channel.
 *
 *  permuteMap[0] tells which channel in ARGB16U will be used as the 1st channel (A) in the result ARGB8888.
 *  permuteMap[1] tells which channel in ARGB16U will be used as the 2nd channel (R) in the result ARGB8888.
 *  permuteMap[2] tells which channel in ARGB16U will be used as the 3rd channel (G) in the result ARGB8888.
 *  permuteMap[3] tells which channel in ARGB16U will be used as the 4th channel (B) in the result ARGB8888.
 *
 *  copyMask = _ _ _ _  ; 4 digit binary
 *  1000 tells if we want to use 1st channel in backgroundColor as the value of channel A in the result.
 *  0100 tells if we want to use 2nd channel in backgroundColor as the value of channel R in the result.
 *  0010 tells if we want to use 3rd channel in backgroundColor as the value of channel G in the result.
 *  0001 tells if we want to use 4th channel in backgroundColor as the value of channel B in the result.
 *
 *  The per-pixel operation is:
 *
 *      Pixel_16U *srcPixel;
 *      Pixel_8888 *destPixel;
 *      uint16_t result16;
 *      uint8_t result[4];
 *      uint8_t mask = 0x8;
 *
 *      for( int i = 0; i < 4; i++ )
 *      {
 *          result16 = srcPixel[ permuteMap[i] ];
 *          result[i] = (result16 * 255U + 32767U) / 65535U;
 *          if( mask & copyMask )
 *              result[i] = backgroundColor[i];
 *          mask = mask >> 1;
 *      }
 *      srcPixel += 4;
 *
 *      destPixel[0] = result[0];
 *      destPixel[1] = result[1];
 *      destPixel[2] = result[2];
 *      destPixel[3] = result[3];
 *      destPixel += 4;
 *
 *  Operands:
 *  ---------
 *  src : A pointer to vImage_Buffer that references 16-bit ARGB interleaved source pixels.
 *  dest : A pointer to vImage_Buffer that references 8-bit ARGB interleaved destination pixels.
 *  permuteMap : Values that can be used to switch the channel order as the above example.
 *  copyMask : A mask to choose between the result and backgroundColor.
 *  backgroudColor : A pointer to Pixel_8888 that references 8-bit ARGB values which can replace the result pixels with. Pixel_8888 backgroundColor = {alpha, red, green, blue};
 *
 *  Flags:
 *  ------
 *      kvImageGetTempBufferSize    Returns 0. Does no work.
 *      kvImageDoNotTile            Disables internal multithreading, if any.
 *
 *  Return Value:
 *  -------------
 *      kvImageNoError              Is returned when there was no error.
 *      kvImageBufferSizeMismatch   Is returned when there is a mismatch in width & height of source and destination.
 *      kvImageUnknownFlagsBit      Is returned when there is a unknown flag.
 *      kvImageInvalidParameter     Is returned when the values in permuteMap[i] is not one of 0, 1, 2, or 3.
 *      kvImageNullPointerArgument  Is returned when backgroundColorPtr is NULL.
 *
 *  This function can work in place.
 *
 */
vImage_Error vImageConvert_ARGB16UToARGB8888(const vImage_Buffer *src, const vImage_Buffer *dest, const uint8_t permuteMap[4], uint8_t copyMask, const Pixel_8888 backgroundColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,5) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );


/*
 *  vImageConvert_ARGB8888ToARGB16U
 *
 *  This function does 3 things.
 *  1. Converts 8-bit unsigned ARGB interleaved pixels into 16-bit unsigned ARGB interleaved pixels.
 *  2. Changes the order of channels according to permuteMap
 *  3. Selects between the result pixel and the backgroundColor according to the bits in copyMask.
 *
 *  permuteMap[i] = 0, 1, 2, or 3 to specify how we permute each channel.
 *
 *  permuteMap[0] tells which channel in ARGB8888 will be used as the 1st channel (A) in the result ARGB16U.
 *  permuteMap[1] tells which channel in ARGB8888 will be used as the 2nd channel (R) in the result ARGB16U.
 *  permuteMap[2] tells which channel in ARGB8888 will be used as the 3rd channel (G) in the result ARGB16U.
 *  permuteMap[3] tells which channel in ARGB8888 will be used as the 4th channel (B) in the result ARGB16U.
 *
 *  copyMask = _ _ _ _  ; 4 digit binary
 *  1000 tells if we want to use 1st channel in backgroundColor as the value of channel A in the result.
 *  0100 tells if we want to use 2nd channel in backgroundColor as the value of channel R in the result.
 *  0010 tells if we want to use 3rd channel in backgroundColor as the value of channel G in the result.
 *  0001 tells if we want to use 4th channel in backgroundColor as the value of channel B in the result.
 *
 *  The per-pixel operation is:
 *
 *      Pixel_8888 *srcPixel;
 *      Pixel_16U *destPixel;
 *      uint8_t result8;
 *      uint16_t result[4];
 *      uint8_t mask = 0x8;
 *
 *      for( int i = 0; i < 4; i++ )
 *      {
 *          result8 = srcPixel[ permuteMap[i] ];
 *          result[i] = (result8 * 65535U + 127U) / 255U;
 *          if( mask & copyMask )
 *              result[i] = backgroundColor[i];
 *          mask = mask >> 1;
 *      }
 *      srcPixel += 4;
 *
 *      destPixel[0] = result[0];
 *      destPixel[1] = result[1];
 *      destPixel[2] = result[2];
 *      destPixel[3] = result[3];
 *      destPixel += 4;
 *
 *  Operands:
 *  ---------
 *  src : A pointer to vImage_Buffer that references 8-bit ARGB interleaved source pixels.
 *  dest : A pointer to vImage_Buffer that references 16-bit ARGB interleaved destination pixels.
 *  permuteMap : Values that can be used to switch the channel order as the above example.
 *  copyMask : A mask to choose between the result and backgroundColor.
 *  backgroundColor : A pointer to Pixel_ARGB_16U that references 16-bit ARGB values which can replace the result pixels with. Pixel_ARGB_16U backgroundColor = {alpha, red, green, blue};
 *
 *  Flags:
 *  ------
 *      kvImageGetTempBufferSize    Returns 0. Does no work.
 *      kvImageDoNotTile            Disables internal multithreading, if any.
 *
 *  Return Value:
 *  -------------
 *      kvImageNoError              Is returned when there was no error.
 *      kvImageBufferSizeMismatch   Is returned when there is a mismatch in width & height of source and destination.
 *      kvImageUnknownFlagsBit      Is returned when there is a unknown flag.
 *      kvImageInvalidParameter     Is returned when the values in permuteMap[i] is not one of 0, 1, 2, or 3.
 *      kvImageNullPointerArgument  Is returned when backgroundColorPtr is NULL.
 *
 *  This function doesn't work in place.
 *
 */
vImage_Error vImageConvert_ARGB8888ToARGB16U(const vImage_Buffer *src, const vImage_Buffer *dest, const uint8_t permuteMap[4], uint8_t copyMask, const Pixel_ARGB_16U backgroundColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,5) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );


/*
 *  vImageConvert_RGB16UToARGB8888
 *
 *  This function does 3 things.
 *  1. Converts 16-bit unsigned RGB interleaved pixels into 8-bit unsigned ARGB interleaved pixels. (255 or A from backgroundColor will be used as A.)
 *  2. Changes the order of channels according to permuteMap.
 *  3. Selects between the result pixel and the backgroundColor according to the bits in copyMask.
 *
 * permuteMap[x] = 0, 1, or 2 to specify how we permute each channel.
 *
 * 255 will be used as a default alpha value.
 * permuteMap[0] tells which channel in 255RGB16U will be used as the 1st channel (A) in the result ARGB8888.
 * permuteMap[1] tells which channel in 255RGB16U will be used as the 2nd channel (R) in the result ARGB8888.
 * permuteMap[2] tells which channel in 255RGB16U will be used as the 3rd channel (G) in the result ARGB8888.
 * permuteMap[3] tells which channel in 255RGB16U will be used as the 4th channel (B) in the result ARGB8888.
 *
 * copyMask = _ _ _ _  ; 4 digit binary
 * 1000 tells if we want to use 1st channel in backgroundColor which can be A in this function.
 * 0100 tells if we want to use 2nd channel in backgroundColor which can be R in this function.
 * 0010 tells if we want to use 3rd channel in backgroundColor which can be G in this function.
 * 0001 tells if we want to use 4th channel in backgroundColor which can be B in this function.
 *
 *  The per-pixel operation is:
 *
 *      Pixel_16U  *srcPixel;
 *      Pixel_8888 *destPixel;
 *      uint16_t   r16, g16, b16;
 *      uint8_t    result[4], a, r, g, b;
 *      uint8_t    mask = 0x8;
 *
 *      r16 = srcPixel[0];
 *      g16 = srcPixel[1];
 *      b16 = srcPixel[2];
 *      srcPixel += 3;
 *
 *      //Convert
 *      result[0] = 255;
 *      result[1] = (r16 * 255U + 32767U) / 65535U;
 *      result[2] = (g16 * 255U + 32767U) / 65535U;
 *      result[3] = (b16 * 255U + 32767U) / 65535U;
 *
 *      //Permute
 *      a = result[permuteMap[0]];
 *      r = result[permuteMap[1]];
 *      g = result[permuteMap[2]];
 *      b = result[permuteMap[3]];
 *
 *      //Select
 *      if( mask & copyMask )
 *          a = backgroundColor[0];
 *      mask = mask >> 1;
 *      if( mask & copyMask )
 *          r = backgroundColor[1];
 *      mask = mask >> 1;
 *      if( mask & copyMask )
 *          g = backgroundColor[2];
 *      mask = mask >> 1;
 *      if( mask & copyMask )
 *          b = backgroundColor[3];
 *
 *      destPixel[0] = a;
 *      destPixel[1] = r;
 *      destPixel[2] = g;
 *      destPixel[3] = b;
 *      destPixel += 4;
 *
 *  Operands:
 *  ---------
 *  src : A pointer to vImage_Buffer that references 16-bit RGB interleaved source pixels.
 *  dest : A pointer to vImage_Buffer that references 8-bit ARGB interleaved destination pixels.
 *  permuteMap : Values that can be used to switch the channel order as the above example. permuteMap[0] is for A in the dest ARGB8888, permuteMap[1] is for R in the dest ARGB8888,  permuteMap[2] is for G in the dest ARGB8888, and  permuteMap[3] is for B in the dest ARGB8888. 
 *  copyMask : A mask to choose between the result and backgroundColor.
 *  backgroudColor : A pointer to Pixel_8888 that references 8-bit ARGB values which can replace the result pixels with. Pixel_8888 backgroundColor = {alpha, red, green, blue};
 *
 *  Flags:
 *  ------
 *      kvImageGetTempBufferSize    Returns 0. Does no work.
 *      kvImageDoNotTile            Disables internal multithreading, if any.
 *
 *  Return Value:
 *  -------------
 *      kvImageNoError              Is returned when there was no error.
 *      kvImageBufferSizeMismatch   Is returned when there is a mismatch in width & height of source and destination.
 *      kvImageUnknownFlagsBit      Is returned when there is a unknown flag.
 *      kvImageInvalidParameter     Is returned when the values in permuteMap[i] is not one of 0, 1, 2, or 3.
 *      kvImageNullPointerArgument  Is returned when backgroundColorPtr is NULL.
 *
 *  This function can work in place.
 *
 */
vImage_Error vImageConvert_RGB16UToARGB8888(const vImage_Buffer *src, const vImage_Buffer *dest, const uint8_t permuteMap[4], uint8_t copyMask, const Pixel_8888 backgroundColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,5) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );


/*
 *  vImageConvert_ARGB8888ToRGB16U
 *
 *  This function does 3 things.
 *  1. Converts 8-bit unsigned ARGB interleaved pixels into 16-bit unsigned RGB interleaved pixels.
 *  2. Changes the order of channels according to permuteMap.
 *  3. Selects between the result pixel and the backgroundColor according to the bits in copyMask.
 *
 *  permuteMap[i] = 0, 1, 2, or 3 to specify how we permute each channel.
 *
 *  permuteMap[0] tells which channel in ARGB8888 will be used as the 1st channel (R) in the result RGB16U.
 *  permuteMap[1] tells which channel in ARGB8888 will be used as the 2nd channel (G) in the result RGB16U.
 *  permuteMap[2] tells which channel in ARGB8888 will be used as the 3rd channel (B) in the result RGB16U.
 *
 *  copyMask = _ _ _ _  ; 3 digit binary
 *  100 tells if we want to use 1st channel in backgroundColor as the value of channel R in the result.
 *  010 tells if we want to use 2nd channel in backgroundColor as the value of channel G in the result.
 *  001 tells if we want to use 3rd channel in backgroundColor as the value of channel B in the result.
 *
 *  The per-pixel operation is:
 *
 *      Pixel_8888 *srcPixel;
 *      Pixel_16U *destPixel;
 *      uint8_t result8, r8, g8, b8;
 *      uint16_t result[3];
 *      uint8_t mask = 0x4;
 *
 *      //Permute
 *      r8 = srcPixel[permuteMap[0]];
 *      g8 = srcPixel[permuteMap[1]];
 *      b8 = srcPixel[permuteMap[2]];
 *      srcPixel += 4;
 *
 *      //Convert
 *      result[0] = (r8 * 65535U + 127U) / 255U;
 *      result[1] = (g8 * 65535U + 127U) / 255U;
 *      result[2] = (b8 * 65535U + 127U) / 255U;
 *
 *      //Select
 *      if( mask & copyMask )
 *          result[0] = backgroundColor[0];
 *      mask = mask >> 1;
 *      if( mask & copyMask )
 *          result[1] = backgroundColor[1];
 *      mask = mask >> 1;
 *      if( mask & copyMask )
 *          result[2] = backgroundColor[2];
 *
 *      destPixel[0] = result[0];
 *      destPixel[1] = result[1];
 *      destPixel[2] = result[2];
 *      destPixel += 3;
 *
 *  Operands:
 *  ---------
 *  src : A pointer to vImage_Buffer that references 8-bit ARGB interleaved source pixels.
 *  dest : A pointer to vImage_Buffer that references 16-bit RGB interleaved destination pixels.
 *  permuteMap : Values that can be used to switch the channel order as the above example. permuteMap[0] is for R in the dest ARGB8888,  permuteMap[1] is for G in the dest ARGB8888, and  permuteMap[2] is for B in the dest ARGB8888. 
 *  copyMask : A mask to choose between the result and backgroundColor.
 *  backgroudColor : A pointer to Pixel_16U that references 16-bit ARGB values which can replace the result pixels with. Pixel_16U backgroundColor[3] = {red, green, blue};
 *
 *  Flags:
 *  ------
 *      kvImageGetTempBufferSize    Returns 0. Does no work.
 *      kvImageDoNotTile            Disables internal multithreading, if any.
 *
 *  Return Value:
 *  -------------
 *      kvImageNoError              Is returned when there was no error.
 *      kvImageBufferSizeMismatch   Is returned when there is a mismatch in width & height of source and destination.
 *      kvImageUnknownFlagsBit      Is returned when there is a unknown flag.
 *      kvImageInvalidParameter     Is returned when the values in permuteMap[i] is not one of 0, 1, 2, or 3.
 *      kvImageNullPointerArgument  Is returned when backgroundColorPtr is NULL.
 *
 *  This function doesn't work in place.
 *
 */
vImage_Error vImageConvert_ARGB8888ToRGB16U(const vImage_Buffer *src, const vImage_Buffer *dest, const uint8_t permuteMap[3], uint8_t copyMask, const Pixel_16U backgroundColor[3], vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,5) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );


/*
 *  vImageByteSwap_Planar16U
 *
 *  This function does byteswap 16-bit pixel.
 *
 *  Operands:
 *  ---------
 *  src  : A pointer to vImage_Buffer that references 16-bit ARGB interleaved source pixels.
 *  dest : A pointer to vImage_Buffer that references 16-bit ARGB interleaved destination pixels.
 *
 *  Flags:
 *  ------
 *      kvImageGetTempBufferSize    Returns 0. Does no work.
 *      kvImageDoNotTile            Disables internal multithreading, if any.
 *
 *  Return Value:
 *  -------------
 *      kvImageNoError              Is returned when there was no error.
 *      kvImageBufferSizeMismatch   Is returned when there is a mismatch in width & height of source and destination.
 *      kvImageUnknownFlagsBit      Is returned when there is a unknown flag.
 *
 *  This function can work in place.
 *
 */

vImage_Error vImageByteSwap_Planar16U(const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );



/*
 *  vImageFlatten_ARGB8888
 *
 *  This function does a flattening operation on ARGB8888.
 *  A flattening operation is an alpha composite against a solid background color.
 *
 *  The per-pixel operation is:
 *
 *  resultAlpha = (pixelAlpha * 255 + (255 - pixelAlpha) * backgroundAlpha + 127) / 255
 *  if(isImagePremultiplied)
 *  {
 *      resultColor = (pixelColor * 255 + (255 - pixelAlpha) * backgroundColor + 127) / 255
 *  }
 *  else
 *  {
 *      resultColor = (pixelColor * pixelAlpha + (255 - pixelAlpha) * backgroundColor + 127) / 255
 *  }
 *
 *  Operands:
 *  ---------
 *  src  : A pointer to vImage_Buffer that references 8-bit ARGB interleaved source pixels.
 *  dest : A pointer to vImage_Buffer that references 8-bit ARGB interleaved destination pixels.
 *  backgroudColorPtr : A pointer to Pixel_8888 that references 8-bit premultiplied ARGB background color.
 *  isImagePremultiplied : True means input colors are premultiplied. False means input colors are not premultiplied.
 *
 *  Flags:
 *  ------
 *      kvImageGetTempBufferSize    Returns 0. Does no work.
 *      kvImageDoNotTile            Disables internal multithreading, if any.
 *
 *  Return Value:
 *  -------------
 *      kvImageNoError              Is returned when there was no error.
 *      kvImageBufferSizeMismatch   Is returned when there is a mismatch in width & height of source and destination.
 *      kvImageUnknownFlagsBit      Is returned when there is a unknown flag.
 *      kvImageNullPointerArgument  Is returned when argbBackgroundColorPtr is NULL.
 *
 *  This function can work in place.
 *
 */

vImage_Error  vImageFlatten_ARGB8888(const vImage_Buffer *argbSrc, const vImage_Buffer *argbDst, const Pixel_8888 argbBackgroundColorPtr, bool isImagePremultiplied, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );

/*
 *  vImageFlatten_RGBA8888
 *
 *  This function does flattening operation on RGBA8888.
 *  A flattening operation is an alpha composite against a solid background color.
 *
 *  The per-pixel operation is:
 *
 *  resultAlpha = (pixelAlpha * 255 + (255 - pixelAlpha) * backgroundAlpha + 127) / 255
 *  if(isImagePremultiplied)
 *  {
 *      resultColor = (pixelColor * 255 + (255 - pixelAlpha) * backgroundColor + 127) / 255
 *  }
 *  else
 *  {
 *      resultColor = (pixelColor * pixelAlpha + (255 - pixelAlpha) * backgroundColor + 127) / 255
 *  }
 *
 *  Operands:
 *  ---------
 *  src  : A pointer to vImage_Buffer that references 8-bit RGBA interleaved source pixels.
 *  dest : A pointer to vImage_Buffer that references 8-bit RGBA interleaved destination pixels.
 *  backgroudColorPtr : A pointer to Pixel_8888 that references 8-bit premultiplied RGBA background color.
 *  isImagePremultiplied : True means input colors are premultiplied. False means input colors are not premultiplied.
 *
 *  Flags:
 *  ------
 *      kvImageGetTempBufferSize    Returns 0. Does no work.
 *      kvImageDoNotTile            Disables internal multithreading, if any.
 *
 *  Return Value:
 *  -------------
 *      kvImageNoError              Is returned when there was no error.
 *      kvImageBufferSizeMismatch   Is returned when there is a mismatch in width & height of source and destination.
 *      kvImageUnknownFlagsBit      Is returned when there is a unknown flag.
 *      kvImageNullPointerArgument  Is returned when rgbaBackgroundColorPtr is NULL.
 *
 *  This function can work in place.
 *  BGRA format can be used as well.
 *
 */

vImage_Error  vImageFlatten_RGBA8888(const vImage_Buffer *rgbaSrc, const vImage_Buffer *rgbaDst, const Pixel_8888 rgbaBackgroundColorPtr, bool isImagePremultiplied, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );

/*
 *  vImageFlatten_ARGB16U
 *
 *  This function does flattening operation on ARGB16U.
 *  A flattening operation is an alpha composite against a solid background color.
 *
 *  The per-pixel operation is:
 *
 *  resultAlpha = (pixelAlpha * 65535 + (65535 - pixelAlpha) * backgroundAlpha + 32767) / 65535
 *  if(isImagePremultiplied)
 *  {
 *      resultColor = (pixelColor * 65535 + (65535 - pixelAlpha) * backgroundColor + 32767) / 65535
 *  }
 *  else
 *  {
 *      resultColor = (pixelColor * pixelAlpha + (65535 - pixelAlpha) * backgroundColor + 32767) / 65535
 *  }
 *
 *  Operands:
 *  ---------
 *  src  : A pointer to vImage_Buffer that references 16-bit ARGB interleaved source pixels.
 *  dest : A pointer to vImage_Buffer that references 16-bit ARGB interleaved destination pixels.
 *  backgroudColorPtr : A pointer to Pixel_ARGB_16U that references 16-bit ARGB premultiplied background color.
 *  isImagePremultiplied : True means input colors are premultiplied. False means input colors are not premultiplied.
 *
 *  Flags:
 *  ------
 *      kvImageGetTempBufferSize    Returns 0. Does no work.
 *      kvImageDoNotTile            Disables internal multithreading, if any.
 *
 *  Return Value:
 *  -------------
 *      kvImageNoError              Is returned when there was no error.
 *      kvImageBufferSizeMismatch   Is returned when there is a mismatch in width & height of source and destination.
 *      kvImageUnknownFlagsBit      Is returned when there is a unknown flag.
 *      kvImageNullPointerArgument  Is returned when argbBackgroundColorPtr is NULL.
 *
 *  This function can work in place.
 *
 */

vImage_Error  vImageFlatten_ARGB16U(const vImage_Buffer *argbSrc, const vImage_Buffer *argbDst, const Pixel_ARGB_16U argbBackgroundColorPtr, bool isImagePremultiplied, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );

/*
 *  vImageFlatten_RGBA16U
 *
 *  This function does flattening operation on RGBA16U.
 *  A flattening operation is an alpha composite against a solid background color.
 *
 *  The per-pixel operation is:
 *
 *  resultAlpha = (pixelAlpha * 65535 + (65535 - pixelAlpha) * backgroundAlpha + 32767) / 65535
 *  if(isImagePremultiplied)
 *  {
 *      resultColor = (pixelColor * 65535 + (65535 - pixelAlpha) * backgroundColor + 32767) / 65535
 *  }
 *  else
 *  {
 *      resultColor = (pixelColor * pixelAlpha + (65535 - pixelAlpha) * backgroundColor + 32767) / 65535
 *  }
 *
 *  Operands:
 *  ---------
 *  src  : A pointer to vImage_Buffer that references 16-bit RGBA interleaved source pixels.
 *  dest : A pointer to vImage_Buffer that references 16-bit RGBA interleaved destination pixels.
 *  backgroudColorPtr : A pointer to Pixel_ARGB_16U that references 16-bit RGBA premultiplied background color.
 *  isImagePremultiplied : True means input colors are premultiplied. False means input colors are not premultiplied.
 *
 *  Flags:
 *  ------
 *      kvImageGetTempBufferSize    Returns 0. Does no work.
 *      kvImageDoNotTile            Disables internal multithreading, if any.
 *
 *  Return Value:
 *  -------------
 *      kvImageNoError              Is returned when there was no error.
 *      kvImageBufferSizeMismatch   Is returned when there is a mismatch in width & height of source and destination.
 *      kvImageUnknownFlagsBit      Is returned when there is a unknown flag.
 *      kvImageNullPointerArgument  Is returned when rgbaBackgroundColorPtr is NULL.
 *
 *  This function can work in place.
 *  BGRA format can be used as well.
 *
 */

vImage_Error  vImageFlatten_RGBA16U(const vImage_Buffer *rgbaSrc, const vImage_Buffer *rgbaDst, const Pixel_ARGB_16U rgbaBackgroundColorPtr, bool isImagePremultiplied, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );

    
    
/*
 *  vImageFlatten_ARGB16Q12
 *
 *  This function does flattening operation on ARGB16Q12.
 *  A flattening operation is an alpha composite against a solid background color.
 *
 *  The per-pixel operation is:
 *
 *  pixelAlpha = CLAMP( 0, pixelAlpha, 4096);
 *  resultAlpha = (pixelAlpha * 4096 + (4096 - pixelAlpha) * backgroundAlpha + 2048) >> 12;
 *  if(isImagePremultiplied)
 *  {
 *      resultColor = (pixelColor * 4096 + (4096 - pixelAlpha) * backgroundColor + 2048) >> 12
 *  }
 *  else
 *  {
 *      resultColor = (pixelColor * pixelAlpha + (4096 - pixelAlpha) * backgroundColor + 2048) >> 12
 *  }
 *
 *  Whether the function attempts to clamp the case when the |resultColor| >= 8.0 is undefined.
 *
 *  Operands:
 *  ---------
 *  src  : A pointer to vImage_Buffer that references 16Q12 ARGB interleaved source pixels.
 *  dest : A pointer to vImage_Buffer that references 16Q12 ARGB interleaved destination pixels.
 *  backgroudColorPtr : A pointer to Pixel_ARGB_16S that references 16-bit ARGB16Q12 premultiplied background color.
 *  isImagePremultiplied : True means input colors are premultiplied. False means input colors are not premultiplied.
 *
 *  Flags:
 *  ------
 *      kvImageGetTempBufferSize    Returns 0. Does no work.
 *      kvImageDoNotTile            Disables internal multithreading, if any.
 *
 *  Return Value:
 *  -------------
 *      kvImageNoError              Is returned when there was no error.
 *      kvImageBufferSizeMismatch   Is returned when there is a mismatch in width & height of source and destination.
 *      kvImageUnknownFlagsBit      Is returned when there is a unknown flag.
 *      kvImageNullPointerArgument  Is returned when argbBackgroundColorPtr is NULL.
 *
 *  This function can work in place. Pixels are assumed to be in native-endian byte order. 
 *
 */
vImage_Error  vImageFlatten_ARGB16Q12(const vImage_Buffer *argbSrc, const vImage_Buffer *argbDst, const Pixel_ARGB_16S argbBackgroundColorPtr, bool isImagePremultiplied, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
vImage_Error  vImageFlatten_RGBA16Q12(const vImage_Buffer *argbSrc, const vImage_Buffer *argbDst, const Pixel_ARGB_16S argbBackgroundColorPtr, bool isImagePremultiplied, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );

    
    
/*
 *  vImageFlatten_ARGBFFFF
 *
 *  This function does flattening operation on ARGBFFFF.
 *  A flattening operation is an alpha composite against a solid background color.
 *
 *  The per-pixel operation is:
 *
 *  resultAlpha = pixelAlpha + (1 - pixelAlpha) * backgroundAlpha
 *  if(isImagePremultiplied)
 *  {
 *      resultColor = pixelColor + (1 - pixelAlpha) * backgroundColor
 *  }
 *  else
 *  {
 *      resultColor = pixelColor * pixelAlpha + (1 - pixelAlpha) * backgroundColor
 *  }
 *
 *  Operands:
 *  ---------
 *  src  : A pointer to vImage_Buffer that references float ARGB interleaved source pixels.
 *  dest : A pointer to vImage_Buffer that references float ARGB interleaved destination pixels.
 *  backgroudColorPtr : A pointer to Pixel_FFFF that references float premultiplied ARGB background color.
 *  isImagePremultiplied : True means input colors are premultiplied. False means input colors are not premultiplied.
 *
 *  Flags:
 *  ------
 *      kvImageGetTempBufferSize    Returns 0. Does no work.
 *      kvImageDoNotTile            Disables internal multithreading, if any.
 *
 *  Return Value:
 *  -------------
 *      kvImageNoError              Is returned when there was no error.
 *      kvImageBufferSizeMismatch   Is returned when there is a mismatch in width & height of source and destination.
 *      kvImageUnknownFlagsBit      Is returned when there is a unknown flag.
 *      kvImageNullPointerArgument  Is returned when argbBackgroundColorPtr is NULL.
 *
 *  This function can work in place.
 *
 */

vImage_Error  vImageFlatten_ARGBFFFF(const vImage_Buffer *argbSrc, const vImage_Buffer *argbDst, const Pixel_FFFF argbBackgroundColorPtr, bool isImagePremultiplied, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );

/*
 *  vImageFlatten_RGBAFFFF
 *
 *  This function does flattening operation on RGBAFFFF.
 *  A flattening operation is an alpha composite against a solid background color.
 *
 *  The per-pixel operation is:
 *
 *  resultAlpha = pixelAlpha + (1 - pixelAlpha) * backgroundAlpha
 *  if(isImagePremultiplied)
 *  {
 *      resultColor = pixelColor + (1 - pixelAlpha) * backgroundColor
 *  }
 *  else
 *  {
 *      resultColor = pixelColor * pixelAlpha + (1 - pixelAlpha) * backgroundColor
 *  }
 *
 *  Operands:
 *  ---------
 *  src  : A pointer to vImage_Buffer that references float RGBA interleaved source pixels.
 *  dest : A pointer to vImage_Buffer that references float RGBA interleaved destination pixels.
 *  backgroudColorPtr : A pointer to Pixel_FFFF that references float RGBA premultiplied background color.
 *  isImagePremultiplied : True means input colors are premultiplied. False means input colors are not premultiplied.
 *
 *  Flags:
 *  ------
 *      kvImageGetTempBufferSize    Returns 0. Does no work.
 *      kvImageDoNotTile            Disables internal multithreading, if any.
 *
 *  Return Value:
 *  -------------
 *      kvImageNoError              Is returned when there was no error.
 *      kvImageBufferSizeMismatch   Is returned when there is a mismatch in width & height of source and destination.
 *      kvImageUnknownFlagsBit      Is returned when there is a unknown flag.
 *      kvImageNullPointerArgument  Is returned when rgbaBackgroundColorPtr is NULL.
 *
 *  This function can work in place.
 *  BGRA format can be used as well.
 *
 */

vImage_Error  vImageFlatten_RGBAFFFF(const vImage_Buffer *rgbaSrc, const vImage_Buffer *rgbaDst, const Pixel_FFFF rgbaBackgroundColorPtr, bool isImagePremultiplied, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
    
/*
 *  vImageConvert_Planar1toPlanar8
 *  vImageConvert_Planar2toPlanar8
 *  vImageConvert_Planar4toPlanar8
 *
 *  These functions convert from 1-, 2-, or 4-bit per pixel to 8-bit per pixel
 *  planar formats.
 *
 *  Function Arguments:
 *  -------------------
 *      src         Pointer to the source vImage_Buffer object.  Because the
 *                  source pixel format is smaller than a byte, there are
 *                  multiple pixels in each byte of the data buffer.  These
 *                  pixels are interpreted as being in big endian order (i.e.
 *                  the low-indexed pixel is in the high-order bits of the
 *                  byte).
 *
 *                  Sub-byte indexing of scanlines is unsupported, because the
 *                  data and rowBytes fields of the buffer are specified in
 *                  whole bytes.
 *
 *                  Widths, however, are measured in pixels, so a scanline may
 *                  end in the middle of a byte.  If this occurs, the contents
 *                  of any unused bits of the final byte are ignored.
 *
 *      dest        Pointer to the destination vImage_Buffer object.
 *
 *      flags       The following flags are allowed:
 *
 *                  kvImageDoNotTile - disables internal threading.  You may
 *                      want to specify this if you have your own threading
 *                      scheme and need to avoid interference.
 *
 *                  kvImageGetTempBufferSize - does no work and returns zero,
 *                      as these functions do not use temp buffers.
 *
 *  Operation:
 *  ----------
 *      For each pixel in the destination image, the resulting value is the
 *      corresponding pixel value from the source image multiplied by 255, 85,
 *      or 17 (for Planar1, Planar2, or Planar4, respectively).
 *
 *
 *  Return values:
 *  --------------
 *      kvImageNoError              Success
 *      kvImageUnknownFlagsBit      No work was done because an unknown bit was
 *                                  set in the flags parameter.
 *      kvImageBufferSizeMismatch   No work was done because the source
 *                                  image isn't large enough to cover the
 *                                  destination image.
 *
 *  These functions do not work in place.
 */

vImage_Error vImageConvert_Planar1toPlanar8(const vImage_Buffer *src, const vImage_Buffer *dest, const vImage_Flags flags) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
vImage_Error vImageConvert_Planar2toPlanar8(const vImage_Buffer *src, const vImage_Buffer *dest, const vImage_Flags flags) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
vImage_Error vImageConvert_Planar4toPlanar8(const vImage_Buffer *src, const vImage_Buffer *dest, const vImage_Flags flags) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);

/*
 *  vImageConvert_Indexed1toPlanar8
 *  vImageConvert_Indexed2toPlanar8
 *  vImageConvert_Indexed4toPlanar8
 *
 *  These functions convert from 1-, 2-, or 4-bit per pixel indexed to 8-bit
 *  per pixel planar format.
 *
 *  Function Arguments:
 *  -------------------
 *      src         Pointer to the source vImage_Buffer object.  Because the
 *                  source pixel format is smaller than a byte, there are
 *                  multiple pixels in each byte of the data buffer.  These
 *                  pixels are interpreted as being in big endian order (i.e.
 *                  the low-indexed pixel is in the high-order bits of the
 *                  byte).
 *
 *                  Sub-byte indexing of scanlines is unsupported, because the
 *                  data and rowBytes fields of the buffer are specified in
 *                  whole bytes.
 *
 *                  Widths, however, are measured in pixels, so a scanline may
 *                  end in the middle of a byte.  If this occurs, the contents
 *                  of any unused bits of the final byte are ignored.
 *
 *      dest        Pointer to the destination vImage_Buffer object.
 *
 *      colors      Color table in which to lookup pixel values for destination
 *                  image.
 *
 *      flags       The following flags are allowed:
 *
 *                  kvImageDoNotTile - disables internal threading.  You may
 *                      want to specify this if you have your own threading
 *                      scheme and need to avoid interference.
 *
 *                  kvImageGetTempBufferSize - does no work and returns zero,
 *                      as these functions do not use temp buffers.
 *
 *  Operation:
 *  ----------
 *      For each pixel in the destination image, the value is looked up in the
 *      color table using the corresponding pixel value from the source image
 *      as an index.
 *
 *  Return values:
 *  --------------
 *      kvImageNoError              Success
 *      kvImageUnknownFlagsBit      No work was done because an unknown bit was
 *                                  set in the flags parameter.
 *      kvImageBufferSizeMismatch   No work was done because the source
 *                                  image isn't large enough to cover the
 *                                  destination image.
 *
 *  These functions do not work in place.
 */

 
vImage_Error vImageConvert_Indexed1toPlanar8(const vImage_Buffer *src, const vImage_Buffer *dest, const Pixel_8 colors[2], const vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
vImage_Error vImageConvert_Indexed2toPlanar8(const vImage_Buffer *src, const vImage_Buffer *dest, const Pixel_8 colors[4], const vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
vImage_Error vImageConvert_Indexed4toPlanar8(const vImage_Buffer *src, const vImage_Buffer *dest, const Pixel_8 colors[16], const vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
    
/*
 *  vImageConvert_Planar8toPlanar1
 *  vImageConvert_Planar8toPlanar2
 *  vImageConvert_Planar8toPlanar4
 *
 *  These functions convert from 8-bit per pixel to 1-, 2-, or 4-bit per pixel
 *  planar formats.
 *
 *  Function Arguments:
 *  -------------------
 *      src         Pointer to the source vImage_Buffer object
 *
 *      dest        Pointer to the destination vImage_Buffer object.  Because
 *                  the destination pixel format is smaller than a byte, there
 *                  are multiple pixels in each byte of the data buffer.  These
 *                  pixels are interpreted as being in big endian order (i.e.
 *                  the low-indexed pixel is in the high-order bits of the
 *                  byte).
 *
 *                  Sub-byte indexing of scanlines is unsupported, because the
 *                  data and rowBytes fields of the buffer are specified in
 *                  whole bytes.
 *
 *                  Widths, however, are measured in pixels, so a scanline may
 *                  end in the middle of a byte.  If this occurs, the contents
 *                  of any unused bits of the final byte are unspecified.
 *
 *      tempBuffer  Pointer to temporary buffer for the routine to use for
 *                  scratch space.  If non-NULL, the buffer must be at least
 *                  as large as the value returned by calling this function
 *                  with the kvImageGetTempBufferSize flag.  If NULL, this
 *                  function will still work, but may allocate and free a
 *                  scratch buffer internally.
 *
 *      dither      Type of dithering to apply to the image, if any.  Options:
 *
 *                  kvImageConvert_DitherNone - apply no dithering; input values
 *                      are rounded to the nearest value representable in the
 *                      destination format.
 *                  kvImageConvert_DitherOrdered - pre-computed blue noise is
 *                      added to the image before rounding to the values in
 *                      the destination format.  The offset into this blue
 *                      noise is randomized per-call to avoid visible artifacts
 *                      if you do your own tiling or call the function on
 *                      sequential frames of video.
 *                  kvImageConvert_DitherOrderedReproducible - pre-computed
 *                      blue noise is added to the image before rounding to the
 *                      values in the destination format.  The offset into the
 *                      blue noise is the same for every call to allow users
 *                      to get reproducible results.
 *                  kvImageConvert_DitherFloydSteinberg - Floyd-Steinberg
 *                      dithering is applied to the image.
 *                  kvImageConvert_DitherAtkinson - Atkinson dithering is
 *                      applied to the image, for the old timers.
 *
 *                  The ordered dither methods may be further influenced by shaping the
 *                  distribution of the noise using the gaussian and uniform options below. 
 *                  These options are OR-ed with kvImageConvert_DitherOrdered / kvImageCon-
 *                  vert_DitherOrderedReproducible:
 *
 *                  kvImageConvert_DitherGaussianBlue - when using an ordered dither
 *                      pattern, distribute the noise according to a gaussian
 *                      distribution. This generally gives more pleasing images --
 *                      less noisy and perhaps a little more saturated -- but color 
 *                      fidelity can suffer. Its effect is between kvImageConvert_DitherNone
 *                      and kvImageConvert_DitherOrdered | kvImageConvert_DitherUniform.
 *                      This is the default for kvImageConvert_DitherOrdered and 
 *                      kvImageConvert_DitherOrderedReproducible.
 *
 *                  kvImageConvert_DitherUniformBlue - when using an ordered dither
 *                      pattern, distribute the noise uniformly. This generally gives 
 *                      best color fidelity, but the resulting image is noisier and more
 *                      obviously dithered. This is usually the best choice when low 
 *                      bitdepth content is drawn next to high bitdepth content and in other
 *                      circumstances where subtle changes to color arising from the conversion 
 *                      could be easily noticed. It may be a poor choice when the image 
 *                      is likely to be enlarged -- this would cause the noise to become 
 *                      more evident-- and for very flat / synthetic content with little 
 *                      inherent noise. The enlargement problem may be avoided by enlarging 
 *                      first at high bitdepth, then convert to lower bitdepth. 
 *
 *                  To clarify: "Blue" noise is not blue, nor does it operate solely on the blue 
 *                  color channel. Blue noise is monochrome noise that is added to all color 
 *                  channels equally. The name arises from blue light, which has a higher frequency 
 *                  than other colors of visible light. Thus, blue noise is noise which is
 *                  weighted heavily towards high frequencies. Low frequency noise tends to have 
 *                  visible shapes in it that would become apparent in an image if it was added in,
 *                  so it is excluded from the dither pattern.
 *
 *      flags       The following flags are allowed:
 *
 *                  kvImageDoNotTile - disables internal threading.  You may
 *                      want to specify this if you have your own threading
 *                      scheme and need to avoid interference.
 *
 *                  kvImageGetTempBufferSize - does no work, but returns the
 *                      required size of tempBuffer for this routine.
 *
 *  Operation:
 *  ----------
 *      For a brief description of each dither method, see dither above.
 *
 *      Notes:
 *      The results for Floyd-Steinberg and Atkinson dithering methods depend on the results 
 *      of pixels around each result pixel. Consequently, these methods do not tile well. (Tiling  
 *      can cause visible artifacts at tile boundaries because residuals are not propagated to the 
 *      next tile in a manner consistent with how it is propagated within a tile.) You should pass
 *      the entire image in a single call for good results with Atkinson and Floyd-Steinberg.
 *
 *      The ordered dithering method is suitable for tiled / multithreaded / scanline-at-a-time 
 *      execution. In addition to being spatially random, the ordered dithering pattern is also
 *      temporally random. This is necessary to prevent stripes when it is invoked scanline-at-a-time.
 *      Temporal randomness also prevents visible walking of the dither pattern across the image 
 *      when used for video. Because it is temporally random, results from this filter are not 
 *      reproducible.
 *
 *      To get reproducible results with ordered dithering, use the OrderedReproducible
 *      dithering attribute.
 *      
 *      The dither none option will produce reproducible results in all calling contexts, but 
 *      is prone to obvious banding in images, especially in regions of an image with a smooth 
 *      gradient.
 *
 *  Return values:
 *  --------------
 *      kvImageNoError              Success
 *      kvImageUnknownFlagsBit      No work was done because an unknown bit was
 *                                  set in the flags parameter.
 *      kvImageBufferSizeMismatch   No work was done because the source
 *                                  image isn't large enough to cover the
 *                                  destination image.
 *      kvImageInvalidParameter     An unrecognized or unsupported value was
 *                                  specified for dither.
 *
 *  These functions do not work in place.
 */
    
/* See description above for the meaning of these contants */ 
enum {
    kvImageConvert_DitherNone                   = 0,         /* __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0) */
    kvImageConvert_DitherOrdered                = 1,         /* __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0) */
    kvImageConvert_DitherOrderedReproducible    = 2,         /* __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0) */
    kvImageConvert_DitherFloydSteinberg         = 3,         /* __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0) */
    kvImageConvert_DitherAtkinson               = 4,         /* __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0) */
    
    /* Gaussian vs. uniform distribution for ordered dithering patterns. By default ordered dithering uses gaussian blue noise. */
    kvImageConvert_OrderedGaussianBlue          = 0,         /* __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0) */
    kvImageConvert_OrderedUniformBlue           = (1<<28),   /* __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0) */
    kvImageConvert_OrderedNoiseShapeMask        = (0xfU<<28) /* __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0) */
};
    
vImage_Error vImageConvert_Planar8toPlanar1(const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, int dither, const vImage_Flags flags) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
vImage_Error vImageConvert_Planar8toPlanar2(const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, int dither, const vImage_Flags flags) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
vImage_Error vImageConvert_Planar8toPlanar4(const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, int dither, const vImage_Flags flags) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
    
/*
 *  vImageConvert_Planar8toIndexed1
 *  vImageConvert_Planar8toIndexed2
 *  vImageConvert_Planar8toIndexed4
 *
 *  These functions convert from 8-bit per pixel planar to 1-, 2-, or 4-bit
 *  per pixel indexed formats.
 *
 *  Function Arguments:
 *  -------------------
 *      src         Pointer to the source vImage_Buffer object
 *
 *      dest        Pointer to the destination vImage_Buffer object.  Because
 *                  the destination pixel format is smaller than a byte, there
 *                  are multiple pixels in each byte of the data buffer.  These
 *                  pixels are interpreted as being in big endian order (i.e.
 *                  the low-indexed pixel is in the high-order bits of the
 *                  byte).
 *
 *                  Sub-byte indexing of scanlines is unsupported, because the
 *                  data and rowBytes fields of the buffer are specified in
 *                  whole bytes.
 *
 *                  Widths, however, are measured in pixels, so a scanline may
 *                  end in the middle of a byte.  If this occurs, the contents
 *                  of any unused bits of the final byte are unspecified.
 *
 *      tempBuffer  Pointer to temporary buffer for the routine to use for
 *                  scratch space.  If non-NULL, the buffer must be at least
 *                  as large as the value returned by calling this function
 *                  with the kvImageGetTempBufferSize flag.  If NULL, this
 *                  function will still work, but may allocate and free a
 *                  scratch buffer internally.
 * 
 *      colors      Color table to use for the destination.
 *
 *                  If you want us to compute a color table for you, initialize
 *                  the table to all zeros:
 *
 *                      Pixel_8 colors[4] = { 0 };
 *                      vImageConvert_Planar8toIndexed2(src, dest, colors, dither, flags);
 *
 *                  We will then compute an appropriate color table for the
 *                  image before performing the conversion.
 *
 *      dither      Type of dithering to apply to the image, if any.  See the
 *                  discussion for vImageConvert_Planar8toPlanar1 for more
 *                  details.
 *
 *      flags       The following flags are allowed:
 *
 *                  kvImageDoNotTile - disables internal threading.  You may
 *                      want to specify this if you have your own threading
 *                      scheme and need to avoid interference.
 *
 *                  kvImageGetTempBufferSize - does no work, but returns the
 *                      required size of tempBuffer for this routine.
 *
 *  Operation:
 *  ----------
 *      See dither above.
 *
 *  Return values:
 *  --------------
 *      kvImageNoError              Success
 *      kvImageUnknownFlagsBit      No work was done because an unknown bit was
 *                                  set in the flags parameter.
 *      kvImageBufferSizeMismatch   No work was done because the source
 *                                  image isn't large enough to cover the
 *                                  destination image.
 *      kvImageInvalidParameter     A non-zero color table was not ordered
 *                                  correctly, or an unrecognized or
 *                                  unsupported value was specified for dither.
 *
 *  These functions do not work in place.
 */
    
vImage_Error vImageConvert_Planar8toIndexed1(const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, Pixel_8 colors[2], int dither, const vImage_Flags flags) VIMAGE_NON_NULL(1,2,4) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
vImage_Error vImageConvert_Planar8toIndexed2(const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, Pixel_8 colors[4], int dither, const vImage_Flags flags) VIMAGE_NON_NULL(1,2,4) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
vImage_Error vImageConvert_Planar8toIndexed4(const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, Pixel_8 colors[16], int dither, const vImage_Flags flags) VIMAGE_NON_NULL(1,2,4) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
    
/*  vImageConvert_8to16Q12
 *  vImageConvert_RGB888toPlanar16Q12
 *  vImageConvert_ARGB8888toPlanar16Q12
 *
 *  All three functions convert 8-bit pixel format to 16-bit format with 12
 *  fractional bits.  The conversion is performed as follows:
 *
 *      uint16_t dest = ((src << 12) + 127)/255;
 *
 *  Source pixel values of 0 are mapped to 0, and source pixel values of 255
 *  are mapped to 0x1000 (4096).  No larger values are produced by this
 *  conversion, which provides some headroom to help subsequent operations
 *  avoid overflow or clipping.
 *
 *  vImageConvert_8to16Q12 takes a single source buffer and a single 
 *  destination buffer and simply does the conversion.
 *
 *  vImageConvert_RGB888toPlanar16Q12 has three destination buffers, and
 *  de-interleaves while it converts.
 *
 *  vImageConvert_ARGB8888toPlanar16Q12 takes four destination buffers, and
 *  also de-interleaves.  Any channel order may be handled by the latter two
 *  functions by permuting the order in which the destination buffers are
 *  passed as arguments.
 *
 *  
 *
 *  The only supported flags are:
 *
 *      kvImageDoNotTile            Turns off internal multithreading. You may
 *                                  wish to do this if you have your own
 *                                  multithreading scheme to avoid having the
 *                                  two interfere with one another.
 *  
 *      kvImageGetTempBufferSize    Returns zero, as the routine does not use
 *                                  a temp buffer.
 *
 *  Passing any other flag will result in no work being done and an error
 *  code being returned.
 *
 *  Return Value:
 *  -------------
 *  kvImageNoError                  is returned when there was no error.
 *  kvImageBufferSizeMismatch       the destination buffers do not have the
 *                                  same size as each other
 *  kvImageRoiLargerThanInputBuffer The destination buffers are larger than the
 *                                  source buffer.
 *  kvImageUnknownFlagsBit          is returned when there is a unknown flag.
 *  
 *  This function will not operate in place.
 */
    
vImage_Error vImageConvert_8to16Q12(const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
vImage_Error vImageConvert_RGB888toPlanar16Q12(const vImage_Buffer *src, const vImage_Buffer *red, const vImage_Buffer *green, const vImage_Buffer *blue, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3,4) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
vImage_Error vImageConvert_ARGB8888toPlanar16Q12(const vImage_Buffer *src, const vImage_Buffer *alpha, const vImage_Buffer *red, const vImage_Buffer *green, const vImage_Buffer *blue, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3,4,5) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
    
/*  vImageConvert_16Q12to8
 *  vImageConvert_Planar16Q12toRGB888
 *  vImageConvert_Planar16Q12toARGB8888
 *
 *  All three functions convert 16-bit format with 12 fractional bits to 8-bit.
 *  The conversion is performed as follows:
 *
 *      uint8_t dest = clamp(src, 0, 4096)*255 + 2048 >> 12
 *
 *  Source pixel values of 0 are mapped to 0, and source pixel values of 4088
 *  or greater are mapped to 255.
 *
 *  vImageConvert_Planar16Q12toRGB888 and vImageConvert_Planar16Q12toARGB8888
 *  interleave data from three or four buffers respectively while performing
 *  the conversion.
 *
 *  The only supported flags are:
 *
 *      kvImageDoNotTile            Turns off internal multithreading. You may
 *                                  wish to do this if you have your own
 *                                  multithreading scheme to avoid having the
 *                                  two interfere with one another.
 *
 *      kvImageGetTempBufferSize    Returns zero, as the routine does not use
 *                                  a temp buffer.
 *
 *  Passing any other flag will result in no work being done and an error
 *  code being returned.
 *
 *  Return Value:
 *  -------------
 *  kvImageNoError                  is returned when there was no error.
 *  kvImageBufferSizeMismatch       the destination buffers do not have the
 *                                  same size as each other
 *  kvImageRoiLargerThanInputBuffer The destination buffers are larger than the
 *                                  source buffer.
 *  kvImageUnknownFlagsBit          is returned when there is a unknown flag.
 *
 *  This function will not operate in place.
 */
    
vImage_Error vImageConvert_16Q12to8(const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
vImage_Error vImageConvert_Planar16Q12toRGB888(const vImage_Buffer *red, const vImage_Buffer *green, const vImage_Buffer *blue, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3,4) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
vImage_Error vImageConvert_Planar16Q12toARGB8888(const vImage_Buffer *alpha, const vImage_Buffer *red, const vImage_Buffer *green, const vImage_Buffer *blue, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3,4,5) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);

/*  
 *  vImageConvert_16Q12toF
 *  vImageConvert_Fto16Q12
 *
 *  Convert 16-bit format with 12 fractional bits to floating-point.
 *  The conversion is performed as follows:
 *
 *      float vImageConvert_16Q12toF_result = sample_16Q12 / 4096.0f
 *      Pixel_16Q12 vImageConvert_Fto16Q12_result = CLAMP( -32768, lrintf(sample_float * 4096.0f), 32767)
 *
 *  Source pixel values of 0 are mapped to 0, and source pixel values of (Pixel_16Q12) 4096
 *  is mapped to (Pixel_F) 1.0f.
 *
 *  The only supported flags are:
 *
 *      kvImageDoNotTile            Turns off internal multithreading. You may
 *                                  wish to do this if you have your own
 *                                  multithreading scheme to avoid having the
 *                                  two interfere with one another.
 *
 *      kvImageGetTempBufferSize    Returns zero, as the routine does not use
 *                                  a temp buffer. Does no work
 *
 *  Passing any other flag will result in no work being done and an error
 *  code being returned.
 *
 *  Return Value:
 *  -------------
 *  kvImageNoError                  is returned when there was no error.
 *  kvImageRoiLargerThanInputBuffer one or more source buffers is smaller than the destination buffer.
 *  kvImageUnknownFlagsBit          is returned when there is a unknown flag.
 *
 *  These functions will operate in place provided that src->data == dest->data && src->rowBytes == dest->rowBytes.
 *
 */

vImage_Error vImageConvert_16Q12toF(const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
vImage_Error vImageConvert_Fto16Q12(const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
    
/*
 *  vImageConvert_16Q12to16U
 *  vImageConvert_16Uto16Q12
 *
 *  Convert 16-bit format with 12 fractional bits to floating-point.
 *  The conversion is performed as follows:
 *
 *      Pixel_16U vImageConvert_16Q12to16U_result = CLAMP( 0, (sample_16Q12 * 65535 + 2048) >> 12, 65535 )
 *      Pixel_16Q12 vImageConvert_16Uto16Q12_result = (sample_16U * 4096 + 32767) / 65535;
 *
 *  Source pixel values of 0 are mapped to 0, and source pixel values of (Pixel_16Q12) 4096
 *  is mapped to (Pixel_16U) 65535.
 *
 *  The only supported flags are:
 *
 *      kvImageDoNotTile            Turns off internal multithreading. You may
 *                                  wish to do this if you have your own
 *                                  multithreading scheme to avoid having the
 *                                  two interfere with one another.
 *
 *      kvImageGetTempBufferSize    Returns zero, as the routine does not use
 *                                  a temp buffer. Does no work
 *
 *  Passing any other flag will result in no work being done and an error
 *  code being returned.
 *
 *  Return Value:
 *  -------------
 *  kvImageNoError                  is returned when there was no error.
 *  kvImageRoiLargerThanInputBuffer one or more source buffers is smaller than the destination buffer.
 *  kvImageUnknownFlagsBit          is returned when there is a unknown flag.
 *
 *  These functions will operate in place provided that src->data == dest->data && src->rowBytes == dest->rowBytes.
 *
 */

vImage_Error vImageConvert_16Q12to16U(const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
vImage_Error vImageConvert_16Uto16Q12(const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);


    
#ifdef __cplusplus
}
#endif

#endif
