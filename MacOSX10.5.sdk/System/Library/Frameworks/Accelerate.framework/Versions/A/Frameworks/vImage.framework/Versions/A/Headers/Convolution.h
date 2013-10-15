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

/*  8 bit planar data  */
vImage_Error vImageConvolve_Planar8( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  const int16_t *kernel, uint32_t kernel_height, uint32_t kernel_width, int32_t divisor, Pixel_8 backgroundColor, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*  32 bit floating point planar data  */
vImage_Error vImageConvolve_PlanarF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  const float *kernel, uint32_t kernel_height, uint32_t kernel_width, Pixel_F backgroundColor, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*  ARGB (8 bits per channel) interleaved data 	*/
vImage_Error vImageConvolve_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  const int16_t *kernel, uint32_t kernel_height, uint32_t kernel_width, int32_t divisor, Pixel_8888 backgroundColor, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*  ARGB (32 bit float per channel) interleaved data  */
vImage_Error vImageConvolve_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  const float *kernel, uint32_t kernel_height, uint32_t kernel_width, Pixel_FFFF backgroundColor, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 * Convolve with bias. 
 * These functions are the same as those immediately above, except that a provided bias is added to the convolution
 * result. It is added before the divisor is applied or any clipping is done.
 */
vImage_Error vImageConvolveWithBias_Planar8( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  const int16_t *kernel, uint32_t kernel_height, uint32_t kernel_width, int32_t divisor, int32_t bias, Pixel_8 backgroundColor, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
vImage_Error vImageConvolveWithBias_PlanarF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  const float *kernel, uint32_t kernel_height, uint32_t kernel_width, float bias, Pixel_F backgroundColor, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
vImage_Error vImageConvolveWithBias_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  const int16_t *kernel, uint32_t kernel_height, uint32_t kernel_width, int32_t divisor, int32_t bias, Pixel_8888 backgroundColor, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
vImage_Error vImageConvolveWithBias_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  const float *kernel, uint32_t kernel_height, uint32_t kernel_width, float bias,  Pixel_FFFF backgroundColor, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*
 *	Apply a convolution operation to the src buffer, using a different kernel for each channel.
 *	The kernel is an array of pointers to MxN matrices:
 *
 *		int16_t *kernelData = malloc( M * N * 4  * sizeof( int16_t ) );		//4 channels
 *		int16_t	*kernel[4];
 *
 *			kernel[0] = kernelData;		//First (alpha) channel
 *			kernel[1] = kernel[0] + M*N;	//Second (red) channel
 *			kernel[2] = kernel[1] + M*N;	//Third (green) channel
 *			kernel[3] = kernel[2] + M*N;	//Fourth (blue) channel
 *
 *	Each kernel must be a contiguous array of M*N*sizeof(int16_t) bytes. The different kernels do not need to be contiguous with each other.
 *	Standard edging modes are available.
 *
 *	Does not work in place (src = dest). 
 *
 *  In order to determine the amount of memory needed for tempBuffer, call vImageConvolveMultiKernel_ARGB8888 exactly as you would 
 *  to execute it, but with the kvImageGetTempBufferSize flag set in flags. The return value will be the size needed in bytes.
 *  DO NOT use vImageGetMinimumTempBufferSizeForConvolution for this purpose - it has been deprecated.
 *  Alternatively, set tempBuffer to NULL to have vImage allocate the memory.
 */
vImage_Error vImageConvolveMultiKernel_ARGB8888(    const vImage_Buffer *src, 
                                                    const vImage_Buffer *dest, 
                                                    void *tempBuffer, 
                                                    vImagePixelCount srcOffsetToROI_X, 
                                                    vImagePixelCount srcOffsetToROI_Y,  
                                                    const int16_t *kernels[4], 		
                                                    uint32_t kernel_height, 
                                                    uint32_t kernel_width, 
                                                    const int32_t divisors[4], 
													const int32_t biases[4], 
                                                    Pixel_8888 backgroundColor, 
                                                    vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*
 *	Apply a convolution operation to the src buffer, using a different kernel for each channel.
 *	The kernel is an array of pointers to MxN matrices:
 *
 *		float *kernelData = malloc( M * N * 4  * sizeof( float ) );		//4 channels
 *		float *kernel[4];
 *
 *			kernel[0] = kernelData;		//First (alpha) channel
 *			kernel[1] = kernel[0] + M*N;	//Second (red) channel
 *			kernel[2] = kernel[1] + M*N;	//Third (green) channel
 *			kernel[3] = kernel[2] + M*N;	//Fourth (blue) channel
 *
 *	Each kernel must be a contiguous array of M*N*sizeof(float) bytes. The different kernels do not need to be contiguous with each other.
 *	Standard edging modes are available.
 *
 *	Does not work in place (src = dest). 
 *
 *  In order to determine the amount of memory needed for tempBuffer, call vImageConvolveMultiKernel_ARGBFFFF exactly as you would 
 *  to execute it, but with the kvImageGetTempBufferSize flag set in flags. The return value will be the size needed in bytes.
 *  DO NOT use vImageGetMinimumTempBufferSizeForConvolution for this purpose - it has been deprecated.
 *  Alternatively, set tempBuffer to NULL to have vImage allocate the memory.
 */
vImage_Error vImageConvolveMultiKernel_ARGBFFFF(    const vImage_Buffer *src, 
                                                    const vImage_Buffer *dest, 
                                                    void *tempBuffer, 
                                                    vImagePixelCount srcOffsetToROI_X, 
                                                    vImagePixelCount srcOffsetToROI_Y,  
                                                    const float *kernels[4], 
                                                    uint32_t kernel_height, 
                                                    uint32_t kernel_width, 
													const float biases[4], 
                                                    Pixel_FFFF backgroundColor, 
                                                    vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 * It is recommended that you use the kvImageGetTempBufferSize flag with the appropriate function, instead of using this API 
 * Simply pass the kvImageGetTempBufferSize flag in addition to all the regular parameters. The size will be returned in the  
 * vImage_Error result.  kvImageGetTempBufferSize is for MacOS X.4 and later. 
 */
size_t	vImageGetMinimumTempBufferSizeForConvolution( const vImage_Buffer *src, const vImage_Buffer *dest, uint32_t kernel_height, uint32_t kernel_width, vImage_Flags flags, size_t bytesPerPixel )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  Richardson-Lucy algorithm for deconvolution.
 *
 *  This routine iteratively uses the following formula:
 *
 *		e[i+1] = e[i] x (psf0 * ( e[0] / (psf1 * e[i]) ) )
 *
 *		where   e[0] = the observed image (src parameter)
 *              e[n] = the result of the nth iteration
 *              psf  = point spread function (kernel for call to convolution)
 *				x    = multiply operator
 *              *    = convolution operator
 *
 *  In order to determine the amount of memory needed for tempBuffer, call vImageRichardsonLucyDeConvolve_xxxx exactly as you would 
 *  to execute it, but with the kvImageGetTempBufferSize flag set in flags. The return value will be the size needed in bytes.
 *  DO NOT use vImageGetMinimumTempBufferSizeForConvolution for this purpose - it has been deprecated.
 *  Alternatively, set tempBuffer to NULL to have vImage allocate the memory.
 */
vImage_Error vImageRichardsonLucyDeConvolve_Planar8( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, const int16_t *kernel, const int16_t *kernel2, uint32_t kernel_height, uint32_t kernel_width, uint32_t kernel_height2, uint32_t kernel_width2, int32_t divisor, int32_t divisor2, Pixel_8 backgroundColor, uint32_t iterationCount, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
vImage_Error vImageRichardsonLucyDeConvolve_PlanarF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, const float *kernel, const float *kernel2, uint32_t kernel_height, uint32_t kernel_width, uint32_t kernel_height2, uint32_t kernel_width2, Pixel_F backgroundColor,  uint32_t iterationCount, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
vImage_Error vImageRichardsonLucyDeConvolve_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, const int16_t *kernel, const int16_t *kernel2, uint32_t kernel_height, uint32_t kernel_width, uint32_t kernel_height2, uint32_t kernel_width2, int32_t divisor, int32_t divisor2, Pixel_8888 backgroundColor,  uint32_t iterationCount, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
vImage_Error vImageRichardsonLucyDeConvolve_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, const float *kernel, const float *kernel2, uint32_t kernel_height, uint32_t kernel_width, uint32_t kernel_height2, uint32_t kernel_width2, Pixel_FFFF backgroundColor,  uint32_t iterationCount, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*
 *  Box
 *
 *  Apply a mean filter to the image. Each result pixel is the mean of the pixels around it as defined by the kernel height and width.
 *  This is the same as doing a regular convolution with a kernel full of all 1's (integer) or all 1.0/(kernel_height*kernel_width)
 *  (floating point). The divisor for the integer case is kernel_height * kernel_width. This is a special high speed algorithm for
 *  finding a box convolve. For large kernels, it may be orders of magnitude faster. 
 *
 *  Do *NOT* use vImageGetMinimumTempBufferSizeForConvolution to set up the temp buffer for this function. It will return incorrect
 *  results. Please use the kvImageGetTempBufferSize flag.
 */
vImage_Error vImageBoxConvolve_Planar8( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, uint32_t kernel_height, uint32_t kernel_width, Pixel_8 backgroundColor, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
vImage_Error vImageBoxConvolve_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, uint32_t kernel_height, uint32_t kernel_width, Pixel_8888 backgroundColor, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*
 *  Tent
 *
 *  Apply a tent filter to the image. Tent filters are separable filters. In the integer world, they increase by 1 for each position
 *  away from the edge (e.g. 1,2,3,2,1). It provides an inexpensive blurring effect. This is a special high speed algorithm for
 *  finding a convolve using these kernels. For large kernels, it may be orders of magnitude faster than the standard convolve. 
 *
 *  Do *NOT* use vImageGetMinimumTempBufferSizeForConvolution to set up the temp buffer for this function. It will return incorrect
 *  results. Please use the kvImageGetTempBufferSize flag.
 */
vImage_Error vImageTentConvolve_Planar8( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, uint32_t kernel_height, uint32_t kernel_width, Pixel_8 backgroundColor, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
vImage_Error vImageTentConvolve_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, uint32_t kernel_height, uint32_t kernel_width, Pixel_8888 backgroundColor, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


#ifdef __cplusplus
}
#endif

#endif
