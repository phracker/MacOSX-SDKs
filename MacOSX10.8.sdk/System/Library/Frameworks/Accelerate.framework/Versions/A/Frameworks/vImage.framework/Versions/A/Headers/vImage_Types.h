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
#include <Availability.h>


/* Please see vImage.h and vImage documentation for the meaning of these types. */

typedef unsigned long   vImagePixelCount;       /* Pedantic: A number of pixels. For LP64 (ppc64) this is a 64-bit quantity.  */

typedef struct vImage_Buffer
{
    void                *data;        /* Pointer to the top left pixel of the buffer.    */
    vImagePixelCount    height;       /* The height (in pixels) of the buffer        */
    vImagePixelCount    width;        /* The width (in pixels) of the buffer         */
    size_t              rowBytes;     /* The number of bytes in a pixel row        */
}vImage_Buffer;


/*
 * This 3x2 matrix was defined to be the same as the CGAffineTransform. Unfortunately, vImage went 64-bit in MacOS X.4.
 * CoreGraphics went 64-bit in MacOS X.5, and elected to change the definition to use doubles. vImage can't change existing APIs
 * to match CG due to binary compatibility guarantees, so we have a bit of a hacky workaround and added new APIs in MacOS X.6.
 *
 * Some handy functions for creating and manipulating that may be found in CoreGraphics/CGAffineTransform.h.
 */
typedef struct vImage_AffineTransform 
{
    float         a, b, c, d;
    float         tx, ty;
}vImage_AffineTransform;

#ifndef VIMAGE_AFFINETRANSFORM_DOUBLE_IS_AVAILABLE
    #define VIMAGE_AFFINETRANSFORM_DOUBLE_IS_AVAILABLE      1     /* defined if vImage_AffineTransform_Double type is available. undefined otherwise */
    typedef struct vImage_AffineTransform_Double 
    {
        double         a, b, c, d;
        double         tx, ty;
    }vImage_AffineTransform_Double;
#endif

/*
 *  vImage_CGAffineTransform is a convenience type to match CGAffineTransform 
 */
#if VIMAGE_AFFINETRANSFORM_DOUBLE_IS_AVAILABLE       /* Interfaces that use this are only available on MacOS X.6 and later */
    #define VIMAGE_CGAFFINETRANSFORM_IS_AVAILABLE			1
    #if defined( __LP64__ )
        typedef    vImage_AffineTransform_Double    vImage_CGAffineTransform;
    #else
        typedef    vImage_AffineTransform           vImage_CGAffineTransform;    
    #endif
#endif


typedef ssize_t     vImage_Error;       /* If positive, a size. If negative, a error.  */
typedef uint32_t    vImage_Flags;       /* You must set all undefined flags bits to 0 */

/* Pixel data types */
typedef uint8_t     Pixel_8;            /* 8 bit planar pixel value                                                                     */
typedef uint16_t    Pixel_16U;          /* 16 bit unsigned planar pixel value. Typical range [0,65535], but most functions are agnostic */
typedef float       Pixel_F;            /* floating point planar pixel value                                                            */
typedef uint8_t     Pixel_8888[4];      /* ARGB interleaved (8 bit/channel) pixel value. uint8_t[4] = { alpha, red, green, blue }       */
typedef float       Pixel_FFFF[4];      /* ARGB interleaved (floating point) pixel value. float[4] = { alpha, red, green, blue }        */
    
typedef void*       ResamplingFilter;
typedef void*       GammaFunction;

/* vImage Errors */
enum        
{
    kvImageNoError                      =    0,
    kvImageRoiLargerThanInputBuffer     =    -21766,
    kvImageInvalidKernelSize            =    -21767,
    kvImageInvalidEdgeStyle             =    -21768,
    kvImageInvalidOffset_X              =    -21769,
    kvImageInvalidOffset_Y              =    -21770,
    kvImageMemoryAllocationError        =    -21771,
    kvImageNullPointerArgument          =    -21772,
    kvImageInvalidParameter             =    -21773,
    kvImageBufferSizeMismatch           =    -21774,
    kvImageUnknownFlagsBit              =    -21775
};

/* vImage Flags */
enum
{
    kvImageNoFlags                      =    0,
    kvImageLeaveAlphaUnchanged          =    1,     /* Operate on red, green and blue channels only. Alpha is copied from source to destination. For Interleaved formats only. __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 )*/
    kvImageCopyInPlace                  =    2,     /* Copy edge pixels. Convolution Only. __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 )*/
    kvImageBackgroundColorFill          =    4,     /* Use the background color for missing pixels. __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 )*/
    kvImageEdgeExtend                   =    8,     /* Extend border data elements. (For 3D LUTs, extend the table.) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 )*/
    kvImageDoNotTile                    =   16,     /* Pass to turn off internal tiling. Use this if you want to do your own tiling, or to use the Min/Max filters in place. __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 )*/
    kvImageHighQualityResampling        =   32,     /* Use a higher quality, slower resampling filter for Geometry operations (shear, scale, rotate, affine transform, etc.) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 )*/
    kvImageTruncateKernel               =   64,     /* Use only the part of the kernel that overlaps the image. For integer kernels, real_divisor = divisor * (sum of used kernel elements) / (sum of kernel elements). This should preserve image brightness at the edges. Convolution only. __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 ) */
    kvImageGetTempBufferSize            =  128,     /* The function will return the number of bytes required for the temp buffer. If this value is negative, it is an error, per standard usage.  __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 ) */
};


#ifdef __cplusplus
}
#endif


#endif /* vImage_TYPES_H */
