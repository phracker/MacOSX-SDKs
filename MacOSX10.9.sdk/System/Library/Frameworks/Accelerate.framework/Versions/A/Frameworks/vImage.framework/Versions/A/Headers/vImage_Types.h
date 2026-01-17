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
    
/* Macro to use to decorate API for sanity checking. Many vImage pointer operands may not be NULL */
#ifndef __has_attribute          /* clang will define this. Other compilers maybe not. */
    #define __has_attribute(a)   0
#endif
#if __has_attribute(nonnull)
#   define VIMAGE_NON_NULL(...)         __attribute__ ((nonnull(__VA_ARGS__)))
#else
#   define VIMAGE_NON_NULL(...)
#endif

#ifndef __has_feature           /* clang will define this. Other compilers maybe not. */
#   define __has_feature(f)     0
#endif
#ifndef __has_extension         /* clang will define this. Other compilers maybe not. */
#   define __has_extension(e)   0
#endif
    /* The C++'11 strongly typed enum feature turns out to be not exactly what we want because it precludes doing things like kvImageLeaveAlphaUnchanged | kvImageCopyInPlace */
    /* We are still exploring options to deliver something better than what we have today for enums. */
#if 0 /*(__cplusplus && __cplusplus >= 201103L && (__has_extension(cxx_strong_enums) || __has_feature(objc_fixed_enum))) || (!__cplusplus && __has_feature(objc_fixed_enum))*/
#   define VIMAGE_CHOICE_ENUM( _name, _type)        enum _name : _type _name; enum _name : _type
#   define VIMAGE_OPTIONS_ENUM(_name, _type)        enum _name : _type _name; enum _name : _type
#else
#   define VIMAGE_CHOICE_ENUM( _name, _type)        _type _name; enum
#   define VIMAGE_OPTIONS_ENUM( _name, _type)       _type _name; enum      
#endif
    
#if __has_extension(enumerator_attributes)
#   ifdef __IPHONE_OS_VERSION_MIN_REQUIRED
#       define VIMAGE_ENUM_AVAILABLE_STARTING(_osx, _ios) __AVAILABILITY_INTERNAL##_ios
#   elif defined(__MAC_OS_X_VERSION_MIN_REQUIRED)
#       define VIMAGE_ENUM_AVAILABLE_STARTING(_osx, _ios) __AVAILABILITY_INTERNAL##_osx
#   else
#       define VIMAGE_ENUM_AVAILABLE_STARTING(_osx, _ios)
#   endif
#else
#   define VIMAGE_ENUM_AVAILABLE_STARTING( _a, _b )
#endif

/* Please see vImage.h and vImage documentation for the meaning of these types. */

typedef unsigned long   vImagePixelCount;       /* Pedantic: A number of pixels. For LP64 (ppc64/x86_64) this is a 64-bit quantity.  */

typedef struct vImage_Buffer
{
    void                *data;        /* Pointer to the top left pixel of the buffer.    */
    vImagePixelCount    height;       /* The height (in pixels) of the buffer        */
    vImagePixelCount    width;        /* The width (in pixels) of the buffer         */
    size_t              rowBytes;     /* The number of bytes in a pixel row, including any unused space between one row and the next. */
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

    
/* Pixel data types */
typedef uint8_t     Pixel_8;            /* 8 bit planar pixel value                                                                     */
typedef float       Pixel_F;            /* floating point planar pixel value                                                            */
typedef uint8_t     Pixel_8888[4];      /* ARGB interleaved (8 bit/channel) pixel value. uint8_t[4] = { alpha, red, green, blue }       */
typedef float       Pixel_FFFF[4];      /* ARGB interleaved (floating point) pixel value. float[4] = { alpha, red, green, blue }        */
typedef uint16_t    Pixel_16U;          /* 16 bit unsigned pixel                                                                        */
typedef int16_t     Pixel_16S;          /* 16 bit signed pixel                                                                          */
typedef uint16_t    Pixel_ARGB_16U[4];  /* four-channel 16-bit unsigned pixel                                                           */
typedef int16_t     Pixel_ARGB_16S[4];  /* four-channel 16-bit signed pixel                                                             */

/* The following are opaque data types used by vImage to hold expensive to compute data structures needed for specific computations.    */
/* When possible, for better performance you should reuse these things over multiple vImage calls, instead of allocating a new one for  */
/* each vImage call.                                                                                                                    */
typedef void*       ResamplingFilter;   /* Used by certain Geometry functions.  */
typedef void*       GammaFunction;      /* Used by vImageGamma                  */

/* vImage Errors                                                                                */
/* ============                                                                                 */
/*   All return values < 0 indicate failure. In this case, the results in the destination       */
/*   buffer are undefined. The list of error codes may grow in the future.                      */
/*                                                                                              */
/*   Note: It is also possible for positive non-zero numbers to be returned out the LHS of a    */
/*   vImage function. This happens when the kvImageGetTempBufferSize bit is set in the flags.   */
/*   In this case, no work is done by the vImage function.  The value returned is the size of   */
/*   the temp buffer needed by the function.                                                    */
typedef VIMAGE_CHOICE_ENUM(vImage_Error, ssize_t)
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
    kvImageUnknownFlagsBit              =    -21775,
    kvImageInternalError                =    -21776,    /* Should never see this. File a bug! */
    kvImageInvalidRowBytes              =    -21777,
    kvImageInvalidImageFormat           =    -21778,
    kvImageColorSyncIsAbsent            =    -21779,
    kvImageOutOfPlaceOperationRequired  =    -21780
};
    
/* vImage Flags                                                                                 */
/* ============                                                                                 */
/* The values here indicate bits in a vImage_Flags bit field.                                   */
/* Other bits are reserved for future use.                                                      */
/* Some flags are mutually exclusive. You can not have more                                     */
/* than one bit from this set set at the same time:                                             */
/* { kvImageCopyInPlace, kvImageBackgroundColorFill, kvImageEdgeExtend, kvImageTruncateKernel } */
/* all unused flags bits must be set to 0                                                       */
/* Not all flags are allowed by all functions.                                                  */
typedef VIMAGE_OPTIONS_ENUM(vImage_Flags, uint32_t)
{
    kvImageNoFlags                                                                                  =    0,
    
     /* Operate on red, green and blue channels only. Alpha is copied from source 
        to destination. For Interleaved formats only. */
    kvImageLeaveAlphaUnchanged       VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 )     =    1,    
    
     /* Copy edge pixels. Convolution Only. */
    kvImageCopyInPlace               VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 )     =    2,
    
    /* Use the background color for missing pixels. */
    kvImageBackgroundColorFill       VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 )     =    4,
    
    /* Use the nearst pixel for missing pixels. */
    kvImageEdgeExtend                VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 )     =    8,
    
    /* Pass to turn off internal tiling and disable internal multithreading. Use this if 
       you want to do your own tiling, or to use the Min/Max filters in place. */
    kvImageDoNotTile                 VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 )     =   16,
    
    /* Use a higher quality, slower resampling filter for Geometry operations 
       (shear, scale, rotate, affine transform, etc.) */
    kvImageHighQualityResampling     VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 )     =   32,
    
     /* Use only the part of the kernel that overlaps the image. For integer kernels, 
        real_divisor = divisor * (sum of used kernel elements) / (sum of kernel elements). 
        This should preserve image brightness at the edges. Convolution only.               */
    kvImageTruncateKernel            VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 )     =   64,
    
    /* The function will return the number of bytes required for the temp buffer. 
       If this value is negative, it is an error, per standard usage. */
    kvImageGetTempBufferSize         VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 )     =  128,
    
    /* Some functions such as vImageConverter_CreateWithCGImageFormat have so many possible error conditions 
       that developers may need more help than a simple error code to diagnose problems. When this 
       flag is set and an error is encountered, an informative error message will be logged to the Apple 
       System Logger (ASL).  The output should be visible in Console.app.  */
    kvImagePrintDiagnosticsToConsole VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 )     =  256,
    
    /* Pass this flag to prevent vImage from allocating additional storage. */
    kvImageNoAllocate                VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 )     =  512
};


#ifdef __cplusplus
}
#endif


#endif /* vImage_TYPES_H */
