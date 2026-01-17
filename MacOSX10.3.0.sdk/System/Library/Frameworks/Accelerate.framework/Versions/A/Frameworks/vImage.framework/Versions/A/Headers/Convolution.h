/*
 *  Convolution.h
 *  vImage_Framework
 *
 *  Copyright (c) 2002 Apple Computer. All rights reserved.
 *
 */

/*
 *  For 8 bit integer calculations, kernel values may not sum in any combination
 *  to be greater than 2**23 or less than or equal to -2**23, to avoid exceeding the 32 bit
 *  internal precision of the calculation. 
 *
 *  For floating point calculations, the kernel must be normalized properly (sum to 1.0). 
 *  Otherwise lightening or darkening of the image will occur.  
 */

#ifndef VIMAGE_CONVOLUTION_H
#define VIMAGE_CONVOLUTION_H


#ifdef __cplusplus
extern "C" {
#endif

#include <vImage/vImage_Types.h>

enum		
{
	dataIs8Bits	= 1,
	dataIs1Channel	= 2,
	printImageData	= 4
};


/*  8 bit planar data  */
vImage_Error vImageConvolve_Planar8( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, unsigned int srcOffsetToROI_X, unsigned int srcOffsetToROI_Y,  const short *kernel, unsigned int kernel_height, unsigned int kernel_width, int divisor, Pixel_8 backgroundColor, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*  32 bit floating point planar data  */
vImage_Error vImageConvolve_PlanarF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, unsigned int srcOffsetToROI_X, unsigned int srcOffsetToROI_Y,  const float *kernel, unsigned int kernel_height, unsigned int kernel_width, Pixel_F backgroundColor, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*  ARGB (8 bits per channel) interleaved data 	*/
vImage_Error vImageConvolve_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, unsigned int srcOffsetToROI_X, unsigned int srcOffsetToROI_Y,  const short *kernel, unsigned int kernel_height, unsigned int kernel_width, int divisor, Pixel_8888 backgroundColor, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*  ARGB (32 bit float per channel) interleaved data  */
vImage_Error vImageConvolve_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, unsigned int srcOffsetToROI_X, unsigned int srcOffsetToROI_Y,  const float *kernel, unsigned int kernel_height, unsigned int kernel_width, Pixel_FFFF backgroundColor, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*	Temporary buffer size  */
size_t	vImageGetMinimumTempBufferSizeForConvolution( const vImage_Buffer *src, const vImage_Buffer *dest, unsigned int kernel_height, unsigned int kernel_width, vImage_Flags flags, size_t bytesPerPixel )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

#ifdef __cplusplus
}
#endif

#endif
