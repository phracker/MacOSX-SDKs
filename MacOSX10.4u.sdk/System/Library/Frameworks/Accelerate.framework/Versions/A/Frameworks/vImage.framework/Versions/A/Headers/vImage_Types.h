/*
 *  vImage_Types.h
 *  vImage_Framework
 *
 *  Copyright (c) 2002-4 Apple Computer, Inc. All rights reserved.
 *
 */

#ifndef VIMAGE_TYPES_H
#define VIMAGE_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>  /* Header no longer needed -- left in for source compatibility for old code. Please use C99 types. */
#include <stdbool.h>   
#include <stdint.h>
#include <stddef.h>
#include <AvailabilityMacros.h>


/* Please see vImage.h and vImage documentation for the meaning of these types. */

typedef unsigned long   vImagePixelCount;       /* Pedantic: A number of pixels. For LP64 (ppc64) this is a 64-bit quantity.  */

typedef struct vImage_Buffer
{
    void                *data;		/* Pointer to the top left pixel of the buffer.	*/
    vImagePixelCount	height;		/* The height (in pixels) of the buffer		*/
    vImagePixelCount	width;		/* The width (in pixels) of the buffer 		*/
    size_t              rowBytes;	/* The number of bytes in a pixel row		*/
}vImage_Buffer;


/*
 * This 3x2 matrix is defined to be the same as the CGAffineTransform.
 * Some handy functions for creating and manipulating that may be found in CoreGraphics/CGAffineTransform.h.
 */
typedef struct vImage_AffineTransform 
{
    float 		a, b, c, d;
    float 		tx, ty;
}vImage_AffineTransform;

typedef ssize_t        vImage_Error;    /* If positive, a size. If negative, a error.  */
typedef uint32_t 	vImage_Flags;		/* You must set all undefined flags bits to 0 */

/* Pixel data types */
typedef uint8_t		Pixel_8;            /* 8 bit planar pixel value										*/
typedef float		Pixel_F;            /* floating point planar pixel value									*/
typedef uint8_t		Pixel_8888[4];		/* ARGB interleaved (8 bit/channel) pixel value. uint8_t[4] = { alpha, red, green, blue } 	*/
typedef float		Pixel_FFFF[4];		/* ARGB interleaved (floating point) pixel value. float[4] = { alpha, red, green, blue }		*/

typedef void*		ResamplingFilter;
typedef void*		GammaFunction;

/* vImage Errors */
enum		
{
    kvImageNoError                      =	0,
    kvImageRoiLargerThanInputBuffer		=	-21766,
    kvImageInvalidKernelSize			=	-21767,
    kvImageInvalidEdgeStyle             =	-21768,
    kvImageInvalidOffset_X              =	-21769,
    kvImageInvalidOffset_Y              =	-21770,
    kvImageMemoryAllocationError		=	-21771,
    kvImageNullPointerArgument			=	-21772,
    kvImageInvalidParameter             =	-21773,
    kvImageBufferSizeMismatch			=	-21774,
    kvImageUnknownFlagsBit              =	-21775
};

/* vImage Flags */
enum
{
    kvImageNoFlags                      =	0,
    kvImageLeaveAlphaUnchanged 			=	1,	/* Operate on red, green and blue channels only. Alpha is copied from source to destination. For Interleaved formats only. AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER*/
    kvImageCopyInPlace                  =	2,	/* Copy edge pixels. Convolution Only. AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER*/
    kvImageBackgroundColorFill			=	4,	/* Use the background color for missing pixels. AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER*/
    kvImageEdgeExtend                   =	8,	/* Extend border data elements. AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER*/
    kvImageDoNotTile                    = 	16,	/* Pass to turn off internal tiling. Use this if you want to do your own tiling, or to use the Min/Max filters in place. AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER*/
    kvImageHighQualityResampling		= 	32,	/* Use a higher quality, slower resampling filter for Geometry operations (shear, scale, rotate, affine transform, etc.) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER*/
    kvImageTruncateKernel               =   64, /* Use only the part of the kernel that overlaps the image. For integer kernels, real_divisor = divisor * (sum of used kernel elements) / (sum of kernel elements). This should preserve image brightness at the edges. Convolution only. AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER */
    kvImageGetTempBufferSize            =  128 /* The function will return the number of bytes required for the temp buffer. If this value is negative, it is an error, per standard usage.  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER */
};


#ifdef __cplusplus
}
#endif


#endif /* vImage_TYPES_H */
