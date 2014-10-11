/*
 *  vImage_Types.h
 *  vImage_Framework
 *
 *  Copyright (c) 2002 Apple Computer, Inc. All rights reserved.
 *
 */

#ifndef VIMAGE_TYPES_H
#define VIMAGE_TYPES_H


#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>
#include <stddef.h>
#include <AvailabilityMacros.h>


/* Please see vImage.h and vImage documentation for the meaning of these types. */

typedef struct vImage_Buffer
{
    void	*data;		/* Pointer to the top left pixel of the buffer.	*/
    u_int32_t	height;		/* The height (in pixels) of the buffer		*/
    u_int32_t	width;		/* The width (in pixels) of the buffer 		*/
    u_int32_t	rowBytes;	/* The number of bytes in a pixel row		*/
}vImage_Buffer;


/*
 * This 3x2 matrix is defined to be the same as the CGAffineTransform.
 * Some handy functions for creating and manipulating that may be found in CoreGraphics/CGAffineTransform.h.
 */
typedef struct vImage_AffineTransform 
{
    float 	a, b, c, d;
    float 	tx, ty;
}vImage_AffineTransform;

typedef int32_t		vImage_Error;
typedef u_int32_t 	vImage_Flags;		/* You must set all undefined flags bits to 0 */

/* Pixel data types */
typedef u_int8_t	Pixel_8;		/* 8 bit planar pixel value										*/
typedef float		Pixel_F;		/* floating point planar pixel value									*/
typedef u_int8_t	Pixel_8888[4];		/* ARGB interleaved (8 bit/channel) pixel value. u_int8_t[4] = { alpha, red, green, blue } 	*/
typedef float		Pixel_FFFF[4];		/* ARGB interleaved (floating point) pixel value. float[4] = { alpha, red, green, blue }		*/

typedef void*		ResamplingFilter;

/* vImage Errors */
enum		
{
    kvImageNoError			=	0,
    kvImageRoiLargerThanInputBuffer	=	-21766,
    kvImageInvalidKernelSize		=	-21767,
    kvImageInvalidEdgeStyle		=	-21768,
    kvImageInvalidOffset_X		=	-21769,
    kvImageInvalidOffset_Y		=	-21770,
    kvImageMemoryAllocationError	=	-21771,
    kvImageNullPointerArgument		=	-21772,
    kvImageInvalidParameter		=	-21773,
    kvImageBufferSizeMismatch		=	-21774,
    kvImageUnknownFlagsBit		=	-21775
};

/* vImage Flags */
enum
{
    kvImageNoFlags		=	0,
    kvImageLeaveAlphaUnchanged 	=	1,	/* Operate on red, green and blue channels only. Alpha is copied from source to destination. For Interleaved formats only. */
    kvImageCopyInPlace		=	2,	/* Copy edge pixels */
    kvImageBackgroundColorFill	=	4,	/* Use the background color for missing pixels */
    kvImageEdgeExtend		=	8,	/* Extend border data elements */
    kvImageDoNotTile		= 	16,	/* Pass to turn off internal tiling. Use this if you want to do your own tiling, or to use the Min/Max filters in place. */
    kvImageHighQualityResampling = 	32	/* Use a higher quality, slower resampling filter for Geometry operations (shear, scale, rotate, affine transform, etc.) */
};


#ifdef __cplusplus
}
#endif


#endif /* vImage_TYPES_H */