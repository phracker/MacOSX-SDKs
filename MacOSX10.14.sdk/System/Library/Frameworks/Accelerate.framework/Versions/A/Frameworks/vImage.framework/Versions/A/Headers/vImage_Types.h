/*!
 *  @header vImage_Types.h
 *  vImage_Framework
 *
 *  See vImage/vImage.h for more on how to view the headerdoc documentation for types declared herein.
 *
 *  @copyright Copyright (c) 2002-2016 by Apple Inc. All rights reserved.
 *
 *  @discussion     Defines various types and constants common to vImage.
 */

#ifndef VIMAGE_TYPES_H
#define VIMAGE_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include <os/availability.h>

/*!
 *  @define     __has_attribute
 *  @abstract   Compiler attribute detection
 *  @discussion A macro for testing whether your compiler supports a particular clang attribute.
 *  @noParse
 */

#ifndef __has_attribute          /* clang will define this. Other compilers maybe not. */
    #define __has_attribute(a)   0
#endif
    
/*!
 *  @define     VIMAGE_NON_NULL
 *  @abstract   Enumerates which parameters may not be NULL.
 *  @discussion Macro to use to decorate API for sanity checking. Many vImage pointer operands may not be NULL.
 *  @noParse
 *  @ignorefuncmacro VIMAGE_NON_NULL
 */
#if __has_attribute(nonnull)
#   define VIMAGE_NON_NULL(...)         __attribute__ ((nonnull(__VA_ARGS__)))
#else
#   define VIMAGE_NON_NULL(...)         
#endif

/*!
 *  @define     __has_feature
 *  @abstract   Compiler feature detection
 *  @discussion A macro for testing whether your compiler supports a particular clang feature.
 *  @noParse
 */

#ifndef __has_feature           /* clang will define this. Other compilers maybe not. */
#   define __has_feature(f)     0
#endif
#ifndef __has_extension         /* clang will define this. Other compilers maybe not. */
#   define __has_extension(e)   0
#endif

/*!
 *  @define     CF_BRIDGED_TYPE
 *  @abstract   CoreFoundation definition detection and aliasing.
 *  @discussion A macro for annotating structs bridging to CoreFoundation types.
 *  @noParse
 */
#ifndef CF_BRIDGED_TYPE
#   if __has_feature(objc_bridge_id)
#       define CF_BRIDGED_TYPE(...) __attribute__((objc_bridge(__VA_ARGS__)))
#   else
#       define CF_BRIDGED_TYPE(...)
#   endif
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

/*!
 *  @availabilitymacro VIMAGE_ENUM_AVAILABLE_STARTING
 */
    
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

/*
 *  @vImage function prototype prefix - Currently only set for visibility
 */
    
#ifndef VIMAGE_PF
#define VIMAGE_PF __attribute__ ((visibility ("default")))
#endif
    
/* Please see vImage.h and vImage documentation for the meaning of these types. */

/*!
    @typedef vImagePixelCount
    @discussion A number of pixels.  Typically, this is the height or width of an image.
 */

typedef unsigned long   vImagePixelCount;       /* Pedantic: A number of pixels. For LP64 (arm64/x86_64) this is a 64-bit quantity.  */

    
/*!
    @typedef vImage_Buffer
    @field  data        A pointer to the top left corner of the buffer contain image pixels.
    @field  height      The number of pixels in a column of the image. 
    @field  width       The number of visible pixels in a row of an image (excluding padding at the ends of rows)
    @field  rowBytes    The number of bytes from a pixel to the next pixel down in the same column.
    @discussion The vImage_Buffer describes a rectangular region within a regular array of pixels. It may describe
                the entire image, or just a sub rectangle of it.  The vImage_Buffer struct is not a complete description
                of an image. Other aspects like pixel format, color space, channel ordering, etc. are generally given
                by the names of functions that operate on the vImage_Buffer or by parameters passed to those functions.
                A vImage_Buffer may contain multiple color channels interleaved with one another, or a single color channel
                (or alpha) as a planar buffer.  vImage_Buffers are often initialized directly by you, by setting fields
                to appropriate values to point to image data you already own. Convenience methods are also available as
                vImageBuffer_Init, vImageBuffer_InitWithCGImage and vImageBuffer_InitWithCVPixelBuffer
 */
    

typedef struct vImage_Buffer
{
    void                *data;        /* Pointer to the top left pixel of the buffer.    */
    vImagePixelCount    height;       /* The height (in pixels) of the buffer        */
    vImagePixelCount    width;        /* The width (in pixels) of the buffer         */
    size_t              rowBytes;     /* The number of bytes in a pixel row, including any unused space between one row and the next. */
}vImage_Buffer;



/*!
    @typedef vImage_AffineTransform
    @field  a        top left cell in 3x2 transform matrix
    @field  b        top right cell in 3x2 transform matrix
    @field  c        middle left cell in 3x2 transform matrix
    @field  d        middle right cell in 3x2 transform matrix
    @field  tx       The x coordinate translation
    @field  ty       The y coordinate translation
    @discussion      This 3x2 matrix generally operates the same as the CGAffineTransform, except that the fields
                     are all float, not CGFloat. If you are looking for CGAffineTransform compatibility, it is 
                     recommended that you use vImage_CGAffineTransform and associated APIs instead.
 */
 
typedef struct vImage_AffineTransform
{
    float         a, b, c, d;
    float         tx, ty;
}vImage_AffineTransform;

/*!
  @typedef vImage_AffineTransform_Double
  @field  a        top left cell in 3x2 transform matrix
  @field  b        top right cell in 3x2 transform matrix
  @field  c        middle left cell in 3x2 transform matrix
  @field  d        middle right cell in 3x2 transform matrix
  @field  tx       The x coordinate translation
  @field  ty       The y coordinate translation
  @discussion      This 3x2 matrix generally operates the same as the CGAffineTransform, except that the fields
                    are all double precision, not CGFloat. If you are looking for CGAffineTransform compatibility, it is
                    recommended that you use vImage_CGAffineTransform and associated APIs instead.
*/

     
#ifndef VIMAGE_AFFINETRANSFORM_DOUBLE_IS_AVAILABLE
    #define VIMAGE_AFFINETRANSFORM_DOUBLE_IS_AVAILABLE      1     /* defined if vImage_AffineTransform_Double type is available. undefined otherwise */
    typedef struct vImage_AffineTransform_Double 
    {
        double         a, b, c, d;
        double         tx, ty;
    }vImage_AffineTransform_Double;
#endif

 /*!
  @typedef vImage_CGAffineTransform
  @field  a        top left cell in 3x2 transform matrix
  @field  b        top right cell in 3x2 transform matrix
  @field  c        middle left cell in 3x2 transform matrix
  @field  d        middle right cell in 3x2 transform matrix
  @field  tx       The x coordinate translation
  @field  ty       The y coordinate translation
  @discussion      This type mirrors the CGAffineTransform type, and may be used interchangeably with it.
  @seealso         CGAffineTransform utilities in CoreGraphics/CGAffineTransform.h
  */
#if VIMAGE_AFFINETRANSFORM_DOUBLE_IS_AVAILABLE       /* Interfaces that use this are only available on MacOS X.6 and later */
    #define VIMAGE_CGAFFINETRANSFORM_IS_AVAILABLE			1
    #if defined( __LP64__ )
        typedef    vImage_AffineTransform_Double    vImage_CGAffineTransform;
    #else
        typedef    vImage_AffineTransform           vImage_CGAffineTransform;    
    #endif
#endif

/*!
 @typedef   Pixel_8
 @abstract   An 8-bit per component unsigned planar pixel value.
*/
typedef uint8_t     Pixel_8;            /* 8 bit planar pixel value */

/*!
 @typedef   Pixel_F
 @abstract   A single precision floating-point planar pixel value.
 @discussion Typically, these have range [0,1] though other values are generally allowed.
*/
typedef float       Pixel_F;            /* floating point planar pixel value */

/*!
 @typedef   Pixel_88
 @abstract  A two channel, 8-bit per channel pixel.
 @discussion The channel order is generally given by the function that consumes the value.
 */
typedef uint8_t     Pixel_88[2];      /* CbCr interleaved (8 bit/channel) pixel value. uint8_t[2] = { Cb, Cr } */

/*!
 @typedef   Pixel_8888
 @abstract  A four channel, 8-bit per channel pixel.
 @discussion The channel order is generally given by the function that consumes the value.
 */
typedef uint8_t     Pixel_8888[4];      /* ARGB interleaved (8 bit/channel) pixel value. uint8_t[4] = { alpha, red, green, blue } */
 
/*!
 @typedef   Pixel_FFFF
 @abstract  A four channel, single precision floating-point per channel pixel. 
 @discussion The channel order is generally given by the function that consumes the value.
 */
typedef float       Pixel_FFFF[4];      /* ARGB interleaved (floating point) pixel value. float[4] = { alpha, red, green, blue } */
 
/*!
 @typedef   Pixel_16U
 @abstract  A 16-bit per channel unsigned pixel.  
 @discussion Typical range is [0,USHRT_MAX] meaning [0.0, 1.0], though most functions tolerate other ranges.
*/
typedef uint16_t    Pixel_16U;          /* 16 bit unsigned pixel */

/*!
 @typedef   Pixel_16S
 @abstract  A 16-bit per channel signed pixel.  
 @discussion Typical range is [SHRT_MIN,SHRT_MAX] meaning [-1.0, 1.0], though most functions tolerate other ranges.
*/
typedef int16_t     Pixel_16S;          /* 16 bit signed pixel */

/*!
 @typedef   Pixel_16Q12
 @abstract  A signed 16 bit fixed point number with 12 bits of fractional precision.
 @discussion Normal range is [-4096,4096] meaning [-1.0, 1.0]. Values in the range [-8.0, 8.0) are representable.
 */
typedef int16_t     Pixel_16Q12;		/* 16 bit signed pixel */

/*!
 @typedef   Pixel_16U16U
 @abstract  A two channel, 16-bit per channel pixel.
 @discussion The channel order is generally given by the function that consumes the value.
 */
typedef uint16_t     Pixel_16U16U[2];	/* CbCr interleaved (16 bit/channel) pixel value. uint16_t[2] = { Cb, Cr } */

/*!
 @typedef   Pixel_32U
 @abstract  Type used for XRGB2101010 format.
 @discussion Typical range for RGB channels is [0,1023] meaning [0.0, 1.0], though most functions tolerate other ranges.
*/
typedef uint32_t    Pixel_32U;          /* 32 bit unsigned pixel */

/*!
 @typedef   Pixel_ARGB_16U
 @abstract  A four channel, 16-bit unsigned per channel pixel.  
 @discussion The channel order is generally given by the function that consumes the value. It is not necessarily ARGB.
 */
typedef uint16_t    Pixel_ARGB_16U[4];  /* four-channel 16-bit unsigned pixel */

/*!
 @typedef   Pixel_ARGB_16S
 @abstract  A four channel, 16-bit signed per channel pixel.  
 @discussion The channel order is generally given by the function that consumes the value. It is not necessarily ARGB.
*/
typedef int16_t     Pixel_ARGB_16S[4];  /* four-channel 16-bit signed pixel */

/*!
 @typedef ResamplingFilter
 @abstract A ResamplingFilter is an opaque structure used by vImage to hold precalculated filter coefficients for a resampling filter,
             such as a Lanczos or Gaussian resampling filter. 
 @discussion It is created with vImageNewResamplingFilter or vImageNewResamplingFilterUsingBuffer and is consumed by various vertical 
             and horizontal shear functions in vImage/Geometry.h. When possible, for better performance, reuse ResamplingFilters over 
             multiple vImage calls, instead of allocating a new one each time.
*/
    
typedef void*       ResamplingFilter;   /* Used by certain Geometry functions.  */

    
/*!
 @typedef GammaFunction
 @discussion A GammaFunction is an opaque structure used by vImage to represent an approximation of a non-linear curve. It is created with
             vImageCreateGammaFunction, and destroyed with vImageDestroyGammaFunction. When possible, for better performance,
             reuse GammaFunctions over multiple vImage function calls, instead of creating a new one each time.
 */
    
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
/*!
     @typedef   vImage_Error 
     @abstract  An error code returned by a vImage function.
     @discussion    All negative values are errors.
                    Positive return values are likely to be the result of kvImageGetTempBufferSize.
                    Zero indicates no error, or quasi-ambiguously a zero temp buffer size, if that
                    flag was passed. Please see the documentation for the function that returned the
                    error code for additional information about the error.
 
    @constant   kvImageNoError      Success.  If kvImageGetTempBufferSize is set in flags, then
                                    it indicates the temp buffer size is 0 and the function did
                                    nothing else.
    @constant   kvImageRoiLargerThanInputBuffer     The size or positioning of the result buffer 
                                    was such that pixels were needed in the source buffer, were
                                    found to be missing and could not be discovered using an edging
                                    process like kvImageEdgeExtend. Typically, this means that the
                                    source image was smaller than the destination image. 
    @constant   kvImageInvalidKernelSize    The size of a kernel was invalid. Typically, kernels have
                                    have an odd number of rows and columns. The kernel might also have
                                    been too large or of zero dimension. Typically only returned by
                                    convolutions and morphological operations.
 
    @constant   kvImageInvalidEdgeStyle   The edging style {kvImageBackgroundColorFill, kvImageCopyInPlace, kvImageEdgeExtend, kvImageTruncateKernel}
                                    was invalid. Typically, the edging style is either missing or the edging style 
                                    is not supported by this function.
 
    @constant   kvImageInvalidOffset_X   Some functions take an integer offset in the horizontal dimension. This indicates
                                    how far from the left edge of the vImage_Buffer we shoud consider the origin to be.
                                    The offset allows real pixel data to be used where an edging method like kvImageEdgeExtend
                                    might otherwise have to be used to generate missing pixels. An X offset is essential to
                                    obtaining correct results for tiled image processing when the tile is not at the left
                                    edge of the (whole) image and the function has a kernel or ResamplingFilter.
                                    Typically, this can happen when the offset is negative or larger than the source vImage_Buffer.width.
 
    @constant   kvImageInvalidOffset_Y   Some functions take an integer offset in the vertical dimension. This indicates
                                    how far from the top edge of the vImage_Buffer we shoud consider the origin to be.
                                    The offset allows real pixel data to be used where an edging method like kvImageEdgeExtend
                                    might otherwise have to be used to generate missing pixels. A Y offset is essential to
                                    obtaining correct results for tiled image processing when the tile is not at the top
                                    edge of the (whole) image and the function has a kernel or ResamplingFilter.
                                    Typically, this can happen when the offset is negative or larger than the source vImage_Buffer.height.
 
    @constant   kvImageMemoryAllocationError    vImage attempted to allocate memory and the allocator failed, returning NULL.
 
    @constant   kvImageNullPointerArgument      One or more arguments to the function are NULL, which are not allowed to be NULL.
                                    Typically, arguments that are not allowed to be NULL are listed in the VIMAGE_NON_NULL() attribute
                                    that follows the function declaration.
 
    @constant   kvImageInvalidParameter         A function parameter has an invalid value. This is the fallback error code when there is not
                                    an error code that more precisely describes the invalid parameter value such as kvImageNullPointerArgument,
                                    kvImageInvalidEdgeStyle, kvImageInvalidRowBytes, etc.
 
    @constant   kvImageBufferSizeMismatch       This most often occurs when a set of planar buffers are not the same size.  Most often
                                    this occurs when the destination image is planar and the destination planes are not the same size.
                                    It may also occur in rare cases when chunk sizes mismatch for some high level conversions.
 
    @constant   kvImageUnknownFlagsBit      A bit in the flags field is set, which the function does not understand or currently support.
                                    Please check flags enum availability info to make sure the flag is supported on the target OS revision.
 
    @constant   kvImageInternalError    A serious error occured inside vImage, which prevented vImage from continuing. This error is
                                    probably a problem with vImage itself, and not how it is being used. Please file a bug with a
                                    reproducible test case attached, if possible!
 
    @constant   kvImageInvalidRowBytes  The vImage_Buffer.rowBytes field is invalid. In some circumstances, rowBytes of 0 is not supported, 
                                    particularly with destination images or when vImage is asked to initialize a vImage_Buffer and the
                                    rowBytes is too small to hold a row of image data.
 
    @constant   kvImageInvalidImageFormat  Usually a vImage_CGImageFormat or vImageCVImageFormatRef contains an invalid format. It might be a
                                    NULL pointer, a description which is not allowed according to rules of CG or CV image format encodings.
 
    @constant   kvImageColorSyncIsAbsent    ColorSync.framework is completely missing. Certain operations will not work.
 
    @constant   kvImageOutOfPlaceOperationRequired   The source images and destination images may not alias the same image data. This will
                                    be returned by vImageCGConverter_MustOperateOutOfPlace(). However, there are many functions in vImage
                                    that do not work in place which do not check to see if the buffers overlap. Please inspect the documentation
                                    of each function for notes on in-place usage before using them that way.
 
    @constant   kvImageInvalidImageObject   An invalid CGImageRef or CVPixelBufferRef was passed to the function.  Typically, the object was NULL.
                                    A non-NULL invalid CGImageRef or CVPixelBufferRef will result in undefined behavior.
 
    @constant   kvImageInvalidCVImageFormat A vImageCVImageFormatRef contains an invalid format. It might be a NULL pointer, or an image format
                                    which is not allowed according to rules of CV image format encodings.
 
    @constant   kvImageUnsupportedConversion    Some lower level conversion APIs only support conversion among a sparse matrix of image formats.
 */
typedef VIMAGE_CHOICE_ENUM(vImage_Error, ssize_t)
{
    kvImageNoError                     VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 ) =    0,
    kvImageRoiLargerThanInputBuffer    VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 ) =    -21766,
    kvImageInvalidKernelSize           VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 ) =    -21767,
    kvImageInvalidEdgeStyle            VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 ) =    -21768,
    kvImageInvalidOffset_X             VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 ) =    -21769,
    kvImageInvalidOffset_Y             VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 ) =    -21770,
    kvImageMemoryAllocationError       VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 ) =    -21771,
    kvImageNullPointerArgument         VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 ) =    -21772,
    kvImageInvalidParameter            VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 ) =    -21773,
    kvImageBufferSizeMismatch          VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 ) =    -21774,
    kvImageUnknownFlagsBit             VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 ) =    -21775,
    kvImageInternalError               VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 ) =    -21776,    /* Should never see this. File a bug! */
    kvImageInvalidRowBytes             VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 ) =    -21777,
    kvImageInvalidImageFormat          VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 ) =    -21778,
    kvImageColorSyncIsAbsent           VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 ) =    -21779,
    kvImageOutOfPlaceOperationRequired VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 ) =    -21780,
    kvImageInvalidImageObject          VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 ) =    -21781,
    kvImageInvalidCVImageFormat        VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 ) =    -21782,
    kvImageUnsupportedConversion       VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 ) =    -21783,
    kvImageCoreVideoIsAbsent           VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 ) =    -21784,
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
/*!
 @typedef   vImage_Flags
 @abstract      vImage_Flags is a 32-bit bitfield of options of general use to vImage functions.
 @discussion    Multiple bits may be set concurrently. kvImageUnknownFlagsBit may be returned by
                a function if a flag bit is set (1) but the function does not know what the flag
                bit means (e.g. your new code on an older version of vImage) or if the flag should
                cause a behavior that is unsupported by the function, for example, kvImageHighQualityResampling
                to a function that does not do image resampling.
 @constant  kvImageNoFlags   Use the default behavior. Internal multithreading is enabled. Debug 
                messages are generally not printed to the console. No edging method is specified. 
                Normal quality resampling methods are used (Lanczos3, probably). Do the function,
                instead of returning a temp buffer size. Allocate memory as needed.
 
 @constant  kvImageLeaveAlphaUnchanged   Some functions that operate on ARGB data in place allow
                you to operate on just the RGB components and leave the alpha channel unmodified.
                These are typically histogram and gamma functions.
 
 @constant  kvImageCopyInPlace  One of four edging modes. This one tells vImage to do nothing for
                destination pixels that need source pixels that are missing. The corresponding source
                pixel is copied to the destination image. This is only used for image filters that take a
                kernel, such as convolutions. It is not allowed for Morphology filters.
 
 @constant kvImageBackgroundColorFill  One of four edging modes. This one tells vImage to use the
                backgroundColor parameter of the function as the color of any missing pixels in
                a source image. Missing pixels occur when a filter needs to read off the edge of
                a source image. 
 
 @constant kvImageEdgeExtend    One of four edging modes.  This one tells vImage to use the nearest
                existing source image pixel when it needs source data but finds it needs a non-existant
                pixel off the edge of the provided source image. 
 
 @constant kvImageDoNotTile     Do not internally subdivide the image for processing on multiple CPUs
                or other compute devices. If this flag is set, the function will run single threaded
                on the current thread. Usually this flag may be expected to cause a significant increase
                in the execution time of a vImage function. However, if you are calling the function
                from a heavily multithreaded context (such as your own tiling engine) and CPU occupancy
                is high, this may lead to small performance improvements due to reduced CPU contention.
 
 @constant kvImageHighQualityResampling  Use a more expensive image resampling method than what is available
                by default. Typically this is Lanczos5. Note that as vImage resampling already leans towards
                quality over performance -- the GPU texture unit is your friend if you just want raw performance
                -- the additional quality from kvImageHighQualityResampling may be difficult to see in some images. 
                It is best suited to background rendering tasks.
 
 @constant kvImageTruncateKernel    One of four edging modes. This one tells vImage to use only the pixels it 
                has and reweight the kernel accordingly. The reweighting process can be expensive.  It can 
                also lead to difficulties if a contiguous sub-rectangle of the kernel sums to zero. In this
                case, the area of the kernel is zero and you have formally asked vImage to do division by zero,
                in which case vImage behavior is undefined.
 
 @constant kvImageGetTempBufferSize  Instead of performing the function requested, return (as a vImage_Error)
                the size of the temp buffer requried by the function for this set of parameters. The image pixels
                are not touched. If the function does not take a temp buffer, then 0 will be returned and the 
                function will do nothing. Some functions may return a 0 sized temp buffer for some sets of parameters 
                an not others. The size of the temporary buffer may change for different parameters, and for
                different OS revisions.
 
 @constant kvImagePrintDiagnosticsToConsole Some of the high level functions in vImage_Utilities.h and 
                vImage_CVUtilities.h have complex failure modes that could prove baffling with just a 
                error code return.  This flag instructions these functions to also print a human readable
                diagnostic message to the Apple System Logger when an error is encountered. The output 
                should be visible in Console.app.
 
 @constant kvImageNoAllocate    Some vImage functions may allocate memory, possibly returning it to you.
                This flag instructs the function to use the memory provided instead. For example, instead of
                overwriting vImage_Buffer.data with a newly allocated pointer to memory, use the memory
                pointed to by vImage_Buffer.data directly. In other cases, it may cause the function to
                assume ownership of a buffer, rather than allocating a copy. You are responsible for making
                sure the buffer that you allocate instead of vImage is large enough to hold the image. Most 
                vImage functions do not allocate memory and assume that vImage_Buffer.data is already allocated, 
                and in the case of source image buffers, contain valid pixel data.
 
 @constant kvImageHDRContent    The pixels described in the input image may contain high dymanic range content.
                HDR pixels may have value outside of [-2,2.0]. This flag is generally only applicable to 
                floating-point images. Most 8- and 16-bit pixels can not represent values outside [0,1] and
                functions that operate on 16Q12 formats are designed to operate over the full range of [-8,8).
                Most floating-point functions in vImage are linear in behavior and so work equally well 
                on any float.  Some non-linear functions like polynomials (or by extension colorspace conversion)
                are only valid over a limited range (typically [-2,2]) and will return incorrect answers 
                for values outside that range.  In addition, certain IIR or FFT algorithms in convolution may
                encounter precision issues with HDR content.  For these cases, if you know you have HDR content,
                pass kvImageHDRContent and a (typically slower) alternative method will be used for these
                sources.
 */
typedef VIMAGE_OPTIONS_ENUM(vImage_Flags, uint32_t)
{
    kvImageNoFlags                   VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 )     =    0,
    
     /* Operate on red, green and blue channels only. Alpha is copied from source 
        to destination. For Interleaved formats only. */
    kvImageLeaveAlphaUnchanged       VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 )     =    1,    
    
     /* Copy edge pixels. Convolution Only. */
    kvImageCopyInPlace               VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 )     =    2,
    
    /* Use the background color for missing pixels. */
    kvImageBackgroundColorFill       VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 )     =    4,
    
    /* Use the nearest pixel for missing pixels. */
    kvImageEdgeExtend                VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 )     =    8,
    
    /* Pass to turn off internal tiling and disable internal multithreading. Use this if 
       you want to do your own tiling, or to use the Min/Max filters in place. */
    kvImageDoNotTile                 VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 )     =   16,
    
    /* Use a higher quality, slower resampling filter for Geometry operations 
       (shear, scale, rotate, affine transform, etc.) */
    kvImageHighQualityResampling     VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 )     =   32,
    
     /* Use only the part of the kernel that overlaps the image. For integer kernels, 
        real_divisor = divisor * (sum of used kernel elements) / (sum of kernel elements). 
        This should preserve image brightness at the edges. Convolution only. */
    kvImageTruncateKernel            VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 )     =   64,
    
    /* The function will return the number of bytes required for the temp buffer. 
       If this value is negative, it is an error, per standard usage. */
    kvImageGetTempBufferSize         VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 )     =  128,
    
    /* Some functions such as vImageConverter_CreateWithCGImageFormat have so many possible error conditions 
       that developers may need more help than a simple error code to diagnose problems. When this 
       flag is set and an error is encountered, an informative error message will be logged to the Apple 
       System Logger (ASL).  The output should be visible in Console.app. */
    kvImagePrintDiagnosticsToConsole VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 )     =  256,
    
    /* Pass this flag to prevent vImage from allocating additional storage. */
    kvImageNoAllocate                VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 )     =  512,

    /* Use methods that are HDR-aware, capable of providing correct results for input images with pixel values
       outside the otherwise limited (typically [-2,2]) range. This may be slower. */
    kvImageHDRContent                VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_11, __IPHONE_9_0 )    =  1024,

    /* Pass to disable clamping is some conversions to floating point formats. Use this if the input data
       may describe values outside [0,1] which should be preserved.. */
    kvImageDoNotClamp                 VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_12, __IPHONE_9_3 )     =   2048
};
    
/*!
    @class vImageConverterRef
    @abstract   An opaque type which contains a decription of a conversion from one CoreGraphics image format to another.
 
    @discussion The vImageConverter is an opaque type which contains information needed to do a rapid conversion from
    one image type to another. Sometimes, it can take a significant amount of time to figure out how to convert
    from one format to another. It wouldn't be good to do that redundantly for a bunch of small images. The
    vImageConversionSetup allows us to set up the conversion once and reuse the information many times, to
    keep net latencies low.
 
    Note that creating a vImageConverter can at times take a while. While usually it is quick, it might have
    to do things like load other frameworks in the system (e.g. Colorsync) if they are not loaded already,
    or build a lookup table. It is a good idea to setup your conversions in advance and reuse the conversion
    objects.  The objects are thread safe. You can use the same object in multiple threads concurrently. They
    follow standard retain / release semantics and can be used as CFTypeRefs.
 
    @superclass CFTypeRef
 
    @seealso Please see vImage_Utilities.h for interfaces that operate on the vImageConverterRef
 */

typedef struct CF_BRIDGED_TYPE(id) vImageConverter * vImageConverterRef;

    
/*!
    @class vImageCVImageFormatRef
    @abstract   An opaque type which contains a decription of a conversion from a CoreGraphics image format to a CVPixelBuffer, or the reverse.
 
    @superclass CFTypeRef
    @discussion The vImageCVImageFormatRef describes how the image is encoded in a CVPixelBufferRef. vImage uses this information to construct converters that
    are capable of converting to and from this image encoding.  The format stores a description of the pixels in the image (planar/color representation/
    bit depth/number of channels, etc.) but not the image size, location of the base pointer or rowbytes. It is intended for the vImageCVImageFormatRef
    to be reused for other CVPixelBufferRefs of the same format, such as other frames from the same movie.
 
    vImageCVImageFormatRefs are capable of holding an incomplete encoding representation. You may be required to provide addition information such
    as colorspace and (YCbCr only) chroma siting or conversion matrix before the vImageCVImageFormatRef can be used for image conversion to other
    formats.
 
    The vImageCVImageFormatRef is a CFTypeRef. CFEqual does not test for equivalence of the userData field. You should use vImageCVImageFormat_Retain/Release
    when working with vImageCVImageFormatRef to manage ownership of the object.

        <pre>
        @textblock
        Thread Safety:

            The vImageCVImageFormatRef may be safely read from multiple threads concurrently.  However,
            it makes no attempt to keep its internal state coherent when multiple threads write to it,
            or when one thread writes to it while one or more threads are reading from it at the same
            time. This can be trivially handled by keeping the knowledge of the vImageCVImageFormatRef
            limited to a single thread while it is being created / configured and then treat it as
            immutable thereafter.  If necessary, you can also use a read/write lock to limit reentrant
            access.
        @/textblock
        </pre>
 
 
    Information tracked by vImageCVImageFormatRef:
 
 <pre>
 @textblock
    imageFormatType     A CVPixelFormatType such as '2vuy'. See CVPixelBuffer.h for the complete list.
 
    number_of_channels  How many  color + alpha channels are encoded in the image. An alpha channel is included in this count
                        if it takes up space in the image, even if its value is described always 1.0, for example by /Last
                        kCGImageAlphaNoneSkipFirst or kCVImageBufferAlphaChannelIsOpaque.  This field is automatically initialized
                        based on the imageFormatType (see above) and is never missing.
 
    channel_names       A list of vImageBufferTypeCodes corresponding to the channels in the image. Unlike what happens for
                        vImageConverterRefs, the type codes used here always encode a single color channel.  vImageConverterRefs
                        use the channel names to encode what is in each vImage_Buffer. Here it is used to describe each channel.
                        So, an ARGB buffer might be described as kvImageBufferTypeCode_CGFormat but will be described as
                        { kvImageBufferTypeCode_RGB_Red, kvImageBufferTypeCode_RGB_Green, kvImageBufferTypeCode_RGB_Blue,
                        kvImageBufferTypeCode_Alpha, kvImageBufferTypeCode_EndOfList }. The order of the channels in the list
                        may not match the order of the channels in the buffer.  This field is automatically initialized based on
                        the imageFormatType (see above) and is never missing.
 
   matrix               (YpCbCr only.)  A YpCbCr image has an associated 3x3 matrix that encodes how it was converted to YpCbCr from
                        a reference RGB colorspace (see colorspace below). The matrix is encoded as a NULL pointer when missing.
                        This field is ignored for non-YpCbCr formats.
 
 
   chroma_siting        Some YpCbCr formats store their chroma components as a smaller image than the luminance component.
                        This describes where the subsampled chroma samples are positioned relative to the luminance component.
                        This field is encoded as a NULL CFStringRef when missing. The field is ignored for RGB, monochrome,
                        indexed and 4:4:4 YpCbCr image formats.
 
   colorspace           For RGB, indexed and grayscale images, this is the colorspace that describes the image encoding.
                        For YpCbCr images, this is the colorspace of the RGB image that you get once the matrix (see above)
                        is unapplied. Thus, the colorspace encodes for the underlying primaries and transfer function of the
                        YpCbCr image. See also vImageCreateRGBColorSpaceWithPrimariesAndTransferFunction.  This field is required
                        for all image formats. A colorspace of NULL indicates a missing colorspace. (This is inconsistent with
                        the shorthand used in vImage_Utilities.h where NULL maps to sRGB.)  Since vImage has no concept of
                        a current graphics device, deviceRGB maps to sRGB and device gray maps to gray 2.2. If you wish to
                        ensure no color correction / conversion, you should match this colorspace with the one in the
                        vImage_CGImageFormat to / from which you are converting.
 
   channel_description  Some CVPixelBuffer formats do not use the entire representable range of the format to encode image data.
                        For example, a 'yuvs' "video range" buffer only uses the range [16,235] for luminance and [16,240] for
                        chroma. Values outside that range are considered to have value equal to the nearest in-range value. In
                        addition, we add additionional fields to leave open the possibility that some formats can encode information
                        outside of the traditional [0,1.0] range ([-1.0,1.0] for chroma) so reference values for the encoding for 0
                        and 1.0 are also described. (See vImageChannelDescription below.) The zero/one fields are analogous in function
                        to the decode arrays provided by CG. It is possible to use the channel description to create formats that are
                        not correctly understood by CoreVideo. These are provided to allow for interoperation with custom video formats.
                        The channel description is initialized automatically for known image format types (see imageFormatType above)
                        and probably only very rarely needs to be changed. It is never missing.
 
  alpha_is_one_hint     Some images are encoded with an alpha channel. However, you may have additional information that the image is
                        really completely opaque. The "alpha is one hint" tells vImage that the alpha channel is always 1.0 (opaque)
                        across the entire image. Setting the hint to 1 may allow vImage to avoid work and run faster in some cases.
                        There is no vImageCVImageFormatRef representation for premultiplied alpha, currently. Since it is a hint,
                        the hint may never be missing from a vImageCVImageFormatRef.  The hint is ignored for image formats that do
                        not contain an alpha channel.
 
  user_data             The vImageCVImageFormatRef has a userData field to allow you to easily reference your data starting from
                        a handle to the object. vImage does  not attempt to interact with the memory pointed to by the userData
                        pointer. It simply holds on to the pointer for you and will call a destructor callback function when the
                        vImageCVImageFormatRef to allow you to free that memory, and do any other post processing needed when the
                        vImageCVImageFormatRef is destroyed. Since there is only one userData pointer, by convention its use is
                        considered private to the application/library/framework that created the vImageCVImageFormatRef, including
                        cases where the creator does not set the userData field. If you need to attach your own data to a
                        vImageCVImageFormatRef created by someone else, you can make  a copy of it or wrap it with your own object.
 @/textblock
 </pre>
 
    @seealso Please see vImage_CVUtilities.h for interfaces that operate on the vImageCVImageFormatRef
 */
typedef struct CF_BRIDGED_TYPE(id) vImageCVImageFormat * vImageCVImageFormatRef;
typedef const struct CF_BRIDGED_TYPE(id) vImageCVImageFormat * vImageConstCVImageFormatRef;



/*!
    @typedef    vImageARGBType
    @abstract   An encoding of an image format type to be used with RGB <-> Y'CbCr conversions in vImage/Conversions.h
    @discussion These formats enumerate different vImage ARGB pixel formats.
 */
typedef enum
{
        kvImageARGB8888   VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_0, __IPHONE_8_0 )        = 0,   /* Any 8-bit four channel interleaved buffer [0,255]=[0,1.0]. Does not specify channel order. */
        kvImageARGB16U    VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_0, __IPHONE_8_0 )        = 1,   /* Any 16-bit unsigned four channel interleaved buffer [0,65535]=[0,1.0]. Does not specify channel order. */
        kvImageARGB16Q12  VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_0, __IPHONE_8_0 )        = 2    /* Any 16-bit signed fixedpoint four channel interleaved buffer [0,4096]=[0,1.0]. Does not specify channel order.  */
}vImageARGBType;
    
/*!
    @typedef    vImageYpCbCrType
    @abstract   An encoding of an image format type to be used with RGB <-> Y'CbCr conversions in vImage/Conversions.h
    @discussion These formats enumerate different vImage/CoreVideo Y'CbCr pixel formats.
    @seealso    CVPixelBuffer OSTypes in CVPixelBuffer.h
 */
typedef enum
{
        kvImage422CbYpCrYp8                  VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_0, __IPHONE_8_0 ) = 0,   /* 2vuy        */
        kvImage422YpCbYpCr8                  VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_0, __IPHONE_8_0 ) = 1,   /* yuvs / yuvf */
        kvImage422CbYpCrYp8_AA8              VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_0, __IPHONE_8_0 ) = 2,   /* a2vy        */
        kvImage420Yp8_Cb8_Cr8                VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_0, __IPHONE_8_0 ) = 3,   /* y420 / f420 */
        kvImage420Yp8_CbCr8                  VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_0, __IPHONE_8_0 ) = 4,   /* 420v / 420f */
        kvImage444AYpCbCr8                   VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_0, __IPHONE_8_0 ) = 5,   /* r408 / y408 */
        kvImage444CrYpCb8                    VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_0, __IPHONE_8_0 ) = 6,   /* v308        */
        kvImage444CbYpCrA8                   VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_0, __IPHONE_8_0 ) = 7,   /* v408        */
        kvImage444CrYpCb10                   VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_0, __IPHONE_8_0 ) = 8,   /* v410        */
        kvImage422CrYpCbYpCbYpCbYpCrYpCrYp10 VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_0, __IPHONE_8_0 ) = 9,   /* v210        */
        kvImage422CbYpCrYp16                 VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_0, __IPHONE_8_0 ) = 13,  /* v216 16-bit */
        kvImage444AYpCbCr16                  VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_0, __IPHONE_8_0 ) = 14   /* y416        */
}vImageYpCbCrType;
    

/*!
 @struct    vImage_YpCbCrToARGBMatrix
 
 @field Yp      matrix[0][0].  Typically 1.
 @field Cr_R    matrix[0][2].
 @field Cb_G    matrix[1][1].
 @field Cr_G    matrix[1][2].
 @field Cb_B    matrix[2][1]
 
 @abstract   A 3x3 converson matrix for converting Y'CbCr signals to RGB
 @discussion The matrix is sparse. The 3x3 matrix is given by:
 
            <pre>
            @textblock
                    | R |   | Yp    0     Cr_R |   | Y' |
                    | G | = | Yp   Cb_G   Cr_G | * | Cb |
                    | B |   | Yp   Cb_B     0  |   | Cr |
            @/textblock
            </pre>
 
            Limits on the range of the fields in the matrix may apply.
 
 @seealso    vImage_ARGBToYpCbCrMatrix, which is the inverse matrix
 */

/* Input information into vImageConvert_YpCbCrToARGB_GenerateConversion() */
typedef struct vImage_YpCbCrToARGBMatrix
{
        float                      Yp;
        float                      Cr_R;
        float                      Cr_G;
        float                      Cb_G;
        float                      Cb_B;
}vImage_YpCbCrToARGBMatrix;
 
/*! @const      kvImage_YpCbCrToARGBMatrix_ITU_R_601_4
 @abstract   Y'CbCr->RGB conversion matrix for ITU-Recommendation BT.601-4 */
extern VIMAGE_PF const vImage_YpCbCrToARGBMatrix *kvImage_YpCbCrToARGBMatrix_ITU_R_601_4 API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*! @const      kvImage_YpCbCrToARGBMatrix_ITU_R_709_2
 @abstract   Y'CbCr->RGB conversion matrix for ITU-Recommendation BT.709-2 */
extern VIMAGE_PF const vImage_YpCbCrToARGBMatrix *kvImage_YpCbCrToARGBMatrix_ITU_R_709_2 API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

    
    
    
/*!
 @typedef    vImage_YpCbCrToARGB
 @abstract   An opaque representation of a 3x3 converson matrix for converting Y'CbCr signals to RGB.
             It is used to do the actual conversions. Please attempt to reuse these rather than making
             new ones each time.
 @discussion The representation also includes the range of the input and output pixels from the matrix and
             clamping information.
 
 @seealso    vImage_ARGBToYpCbCr, which is the inverse matrix
 */

typedef struct vImage_YpCbCrToARGB
{
        uint8_t __attribute__ ((__aligned__(16))) opaque[128];
}vImage_YpCbCrToARGB;
    
/*!
 @typedef    vImage_ARGBToYpCbCrMatrix
 @abstract   A 3x3 converson matrix for converting RGB signals to Y'CbCr
 @discussion The matrix has one repeating parameter. The 3x3 matrix is given by:
 
 @textblock
        | Y' |   | R_Yp        G_Yp  B_Yp      |   | R |
        | Cb | = | R_Cb        G_Cb  B_Cb_R_Cr | * | G |
        | Cr |   | B_Cb_R_Cr   G_Cr  B_Cr      |   | B |
 @/textblock
 
 Typically, these matrix coefficients come from a conversion of form:
 
 @textblock
    Y' = R_Yp * R + G_Yp * G + B_Yp * B         0 <= Y' <= 1
    Cb = k0 * (B - Y')                          -0.5 <= Cb <= 0.5
    Cr = k1 * (R - Y')                          -0.5 <= Cr <= 0.5
 @/textblock
 
 {R_Yp, G_Yp, B_Yp} are typically derived from the perceived brightness for red, green and blue.
 k0 and k1 are typically scaled so that Cb and Cr have the indicated range. Because of these
 relationships, {R_Yp, G_Yp, B_Yp} are usually positive, and B_Cb_R_Cr is usually 0.5.
 Limits on the range of the fields in the matrix may apply.
 @field R_Yp    matrix[0][0]
 @field G_Yp    matrix[0][1]
 @field B_Yp    matrix[0][2]
 @field R_Cb    matrix[1][0]
 @field G_Cb    matrix[1][1]
 @field B_Cb_R_Cr matrix[1][2] and matrix[2][0]
 @field G_Cr    matrix[2][1]
 @field B_Cr    matrix[2][2]
 @seealso    vImage_YpCbCrToARGBMatrix, which is the inverse matrix
 
 */
/* Input information into vImageConvert_ARGBToYpCbCr_GenerateConversion() */
typedef struct vImage_ARGBToYpCbCrMatrix
{
        float                      R_Yp;
        float                      G_Yp;
        float                      B_Yp;
        float                      R_Cb;
        float                      G_Cb;
        float                      B_Cb_R_Cr;
        float                      G_Cr;
        float                      B_Cr;
}vImage_ARGBToYpCbCrMatrix;

/*! @const      kvImage_ARGBToYpCbCrMatrix_ITU_R_601_4
 @abstract   RGB->Y'CbCr conversion matrix for ITU-Recommendation BT.601-4 */
extern VIMAGE_PF const vImage_ARGBToYpCbCrMatrix *kvImage_ARGBToYpCbCrMatrix_ITU_R_601_4 API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*! @const      kvImage_ARGBToYpCbCrMatrix_ITU_R_709_2
 @abstract   RGB->Y'CbCr conversion matrix for ITU-Recommendation BT.709-2 */
extern VIMAGE_PF const vImage_ARGBToYpCbCrMatrix *kvImage_ARGBToYpCbCrMatrix_ITU_R_709_2 API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));
    
/*!
 @typedef    vImage_ARGBToYpCbCr
 @abstract   An opaque representation of a 3x3 converson matrix for converting RGB signals to Y'CbCr.
 It is used to do the actual conversions. Please attempt to reuse these rather than making
 new ones each time.
 @discussion The representation also includes the range of the input and output pixels from the matrix and
 clamping information.
 
 @seealso    vImage_ARGBToYpCbCr, which is the inverse matrix
 */
typedef struct vImage_ARGBToYpCbCr
{
        uint8_t __attribute__ ((__aligned__(16))) opaque[128];
}vImage_ARGBToYpCbCr;
    
/*! 
 @typedef vImage_YpCbCrPixelRange
 @abstract  Range and clamping information for Y'CbCr pixel formats
 @discussion Y'CbCr formats frequently don't use the entire representable range available to 
             them to represent image data. While a "full range" video format does use the
             entire range, a "video range" format often leaves the extrema unused, except perhaps
             to represent values outside of the standard Y'=[0,1] CbCr = [-0.5, 0.5] range. 
             For example, a 8-bit video range format typically uses the range [16,235] for
             Y' and [16, 240] for Cb and Cr. 
 
 
             Some examples:
    
 @textblock
                (vImage_YpCbCrPixelRange){ 16, 128, 235, 240, 255, 0, 255, 1 }      // video range 8-bit, unclamped
                (vImage_YpCbCrPixelRange){ 16, 128, 235, 240, 235, 16, 240, 16 }    // video range 8-bit, clamped to video range
                (vImage_YpCbCrPixelRange){ 0, 128, 255, 255, 255, 1, 255, 0 }       // full range 8-bit, clamped to full range
 @/textblock
 
            The bias will be the prebias for YUV -> RGB and postbias for RGB -> YUV.
 
 @field Yp_bias The encoding for Y' = 0.0 for this video format (varies by bitdepth)
 @field CbCr_bias The encoding for {Cb,Cr} = 0.0 for this video format. This is usually the MIDDLE of the range of CbCr, not the low end. 
 @field YpRangeMax The encoding for Y' = 1.0 for this video format. For video range, this is typically less than the maximum representable value.
 @field CbCrRangeMax The encoding for {Cb,Cr} = 0.5 for this video format. This is usually near the high end of the encodable range (e.g. 0xf0), if not the maximum encodable value (e.g. 0xff)
 @field YpMax  The encoding for the maximum allowed Y' value. All values larger than this will be clamped to this value.
 @field YpMin   The encoding of the minimum allowed Y' value. All values less than this will be clamped to this value.
 @field CbCrMax The encoding of the maximum allowed {Cb, Cr} value. All chroma values greater than this value will be clamped to this value.
 @field CbCrMin The encoding of the minimum allowed {Cb, Cr} value. All chroma values less than this value will be clamped to this value.
 @seealso vImageChannelDescription
*/
typedef struct vImage_YpCbCrPixelRange
{
        int32_t                    Yp_bias;
        int32_t                    CbCr_bias;
        int32_t                    YpRangeMax;
        int32_t                    CbCrRangeMax;
        int32_t                    YpMax;
        int32_t                    YpMin;
        int32_t                    CbCrMax;
        int32_t                    CbCrMin;
}vImage_YpCbCrPixelRange;

    
#ifdef __cplusplus
}
#endif


#endif /* vImage_TYPES_H */
