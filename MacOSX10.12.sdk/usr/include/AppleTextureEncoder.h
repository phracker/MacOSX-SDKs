/*!
 *  @header     AppleTextureEncoder.h
 *  @library    /usr/lib/libate.dylib
 *  @dependency -stdlib=libc++ -lobjc
 *  @copyright  Copyright (c) 2016 Apple Inc. All rights reserved.
 *  @discussion Fast run time texture compression on the CPU.
 *
 *      Created by Ian Ollmann on 1/13/16.      Skål
 */

#ifndef _AppleTextureEncoder_h_
#define _AppleTextureEncoder_h_     1

/*  ************************************************
 *  ***  SAVE YOURSELF SOME TIME -- Please Read  ***
 *  ************************************************
 *
 *  This is a low level interface into a software ASTC encoder / decoder.
 *  The same code is also usable through ImageIO.framework and the 
 *  CGImageSource / CGImageDestination APIs on iOS/tvOS 10.0 and macOS 12.0 and 
 *  later. In some cases, particularly for CGImageRef interoperability, 
 *  that framework can do some things you can not, such as read/write the 
 *  CGImageRef data directly without making a copy, and defer decoding until 
 *  needed and then only decode the regions that are needed by the CoreGraphics
 *  compositor. It also saves a lot of complexity managing alpha information,
 *  channel order, color spaces an the like and may allow for fast path
 *  conversion to MTLTexture behind the scenes, without decompression if the 
 *  hardware supports it.  
 *
 *  When possible, you should use the higher level APIs. You may use the MIME
 *  types CFSTR("org.khronos.astc") or CFSTR("org.khronos.ktx") for ASTC data.
 *  The latter encodes a richer set of metadata to go with the image such as 
 *  orientation, alpha and colorspace to help make sure that it is drawn
 *  correctly. The .astc file format is very basic and should only be used
 *  when this other information is implicitly assumed and the readers of the
 *  file are known to handle it correctly.
 */

#include <os/object.h>
#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>
#include <Availability.h>

#ifndef AT_LINK_STATIC
/*
 *  Availability information for AppleTextureEncoder.
 *  Release info:
 *      version 1 (v1): MacOS X.12, iOS 10, tvOS 10
 *          ASTC compression for 4x4 and 8x8 block sizes
 *          ASTC decompression of all LDR (not HDR, not 3D) textures
 *          unorm8, unorm16 and fp16 texel support for l, la, and rgba color models.
 *          sRGB->linear conversions for ASTC decode.
 *          various alpha operations.
 *
 *  The major field of the at_encoder_get_version build version corresponds with
 *  the availability version (e.g. AT_AVAILABILITY_v1) here.
 */
#   ifdef __IPHONE_OS_VERSION_MIN_REQUIRED
#       define  AT_AVAILABILITY_v1      __IOS_AVAILABLE(__IPHONE_10_0)
#   elif defined __MAC_OS_X_VERSION_MIN_REQUIRED
#       define  AT_AVAILABILITY_v1      __OSX_AVAILABLE(__MAC_10_12)
#   elif __has_feature(attribute_availability_tvos)
#       define  AT_AVAILABILITY_v1      __TVOS_AVAILABLE(__TVOS_10_0)
#   elif __has_feature(attribute_availability_watchos)
#       define  AT_AVAILABILITY_v1      __WATCHOS_UNAVAILABLE
#   else
#       define  AT_AVAILABILITY_v1
#   endif

#   if __has_extension(enumerator_attributes)
#       ifdef __IPHONE_OS_VERSION_MIN_REQUIRED
#           define  AT_ENUM_AVAILABILITY_v1      __IOS_AVAILABLE(__IPHONE_10_0)
#       elif defined __MAC_OS_X_VERSION_MIN_REQUIRED
#           define  AT_ENUM_AVAILABILITY_v1      __OSX_AVAILABLE(__MAC_10_12)
#       elif __has_feature(attribute_availability_tvos)
#           define  AT_ENUM_AVAILABILITY_v1      __TVOS_AVAILABLE(__TVOS_10_0)
#       elif __has_feature(attribute_availability_watchos)
#           define  AT_ENUM_AVAILABILITY_v1      __WATCHOS_UNAVAILABLE
#       else
#           define  AT_ENUM_AVAILABILITY_v1
#       endif
#   else
#       define      AT_ENUM_AVAILABILITY_v1
#   endif

#else   /* AT_LINK_STATIC */
#   define      AT_ENUM_AVAILABILITY_v1
#   define      AT_AVAILABILITY_v1
#endif  /* AT_LINK_STATIC */


#ifdef __cplusplus
    extern "C" {
#endif

/*! @enum       at_alpha_t
 *  @abstract   Describes how the alpha channel is encoded in the image
 *  @discussion The at_alpha_t tells the Apple texture encoder how to treat the encoded
 *              color and alpha values in the image:
 *
 *              at_alpha_not_premultiplied:
 *                  The color and alpha values are used as is.
 *
 *              at_alpha_premultiplied:
 *                  The color channels are interpreted as if they are multiplied by the alpha channel.
 *                  If color > alpha, it will be clamped to alpha (LDR only).
 *
 *              at_alpha_opaque:
 *                  On input, the content of the alpha channel is ignored. 1.0 is used instead.
 *                  On output, alpha is encoded as 1.0. Because alpha=1.0 does allows encoding to
 *                  be skipped for alpha, more bits are available to other channels. Using this
 *                  setting for the output alpha type can improve image quality.
 *
 *              If the image type does not have alpha (e.g. MTLPixelFormatR8Unorm),
 *              at_alpha_opaque must be used. If the input image has alpha, and the
 *              output image is at_alpha_opaque, the input image will be composited
 *              against the background color to make it opaque. If the image contains color data
 *              where the alpha channel "should be" (e.g. CMYK in a RGBA image type), use
 *              at_alpha_not_premultiplied.
 *
 *              The following table shows what happens in each combination:
 *              @code
 *                  output alpha -------->  not_premultiplied       premultiplied           opaque
 *                  input alpha:            ================================================================  
 *                      not_premultiplied       <no change>         premultiply             composite against background color
 *                      premultiplied           unpremultiply       clamp to alpha (LDR)    composite against background color
 *                      opaque                  set alpha to 1      set alpha to 1          set alpha to 1
 *              @endcode
 *
 *              Assets consumed by CoreAnimation are assumed to be premultiplied. In such cases, when encoding
 *              assets for use by CA, set the block type to at_alpha_premultiplied and match the texel alpha type
 *              to the encoding of the image data to be compressed. For example:
 *
 *                      kCGImageAlphaLast               ->  at_alpha_not_premultiplied
 *                      kCGImageAlphaPremultipliedLast  ->  at_alpha_premultiplied
 *                      kCGImageAlphaNoneSkipLast       ->  at_alpha_opaque
 *                      kCGImageAlphaNone               ->  at_alpha_opaque
 *
 *              Caution: ASTC encoded images that are encoded to be premultiplied should generally not
 *                       be converted back to non-premultiplied. Especially where values are small (e.g 
 *                       both alpha and color < 0.25) the quantization error from ASTC can become a 
 *                       relatively large fraction of the small value.  When one later unpremultiplies 
 *                       the values the operation results in:
 *                       @code
 *                          new color = (color ± color_quant_error) / (alpha ± alpha_quant_error)
 *                       @endcode
 *                       When the errors are a large fraction of the corresponding color or alpha, the 
 *                       unpremultiplied color value results can become inaccurate.  This is a standard 
 *                       problem for any unpremultiplication operation on relatively transparent content, 
 *                       but can be more visible in ASTC due to relatively high quantization error on 
 *                       some blocks and the fact that the quantization error can vary considerably from 
 *                       block to block.
 *
 *
 *  @memberof   at_encoder_t
 */
#if defined(DOXYGEN)
typedef enum at_alpha_t{
    at_alpha_not_premultiplied      AT_ENUM_AVAILABILITY_v1 = 0,        /**< the image is not premultiplied by alpha */
    at_alpha_opaque                 AT_ENUM_AVAILABILITY_v1 = 1,        /**< the image is always opaque or has no alpha channel. alpha=1, even if it isn't. */
    at_alpha_premultiplied          AT_ENUM_AVAILABILITY_v1 = 2,        /**< The color channels in each texel have been scaled by the texel's alpha */
    
    at_alpha_count                  AT_ENUM_AVAILABILITY_v1             /* CAUTION: value subject to change! */
};
#else
OS_ENUM(at_alpha, uint32_t,
        at_alpha_not_premultiplied  AT_ENUM_AVAILABILITY_v1 = 0,        /**< the image is not premultiplied by alpha */
        at_alpha_opaque             AT_ENUM_AVAILABILITY_v1 = 1,        /**< the image is always opaque or has no alpha channel.  */
        at_alpha_premultiplied      AT_ENUM_AVAILABILITY_v1 = 2,        /**< The color channels in each texel have been scaled by the texel's alpha */
        
        at_alpha_count              AT_ENUM_AVAILABILITY_v1             /* CAUTION: value subject to change! */
);
#endif

/*! @enum       at_texel_format_t
 *  @abstract   A texel format
 *
 *  @discussion Some of these have MTLPixelFormat counterparts which are documented below
 *
 *  @memberof   at_encoder_t
 */
#if defined(DOXYGEN)
typedef enum at_texel_format_t{
    at_texel_format_invalid         AT_ENUM_AVAILABILITY_v1 = 0,    ///< MTLPixelFormatInvalid
    
    at_texel_format_l8_unorm        AT_ENUM_AVAILABILITY_v1,        ///< MTLPixelFormatR8Unorm,   R is luminance (grayscale)
    at_texel_format_l16_unorm       AT_ENUM_AVAILABILITY_v1,        ///< MTLPixelFormatR16Unorm,  R is luminance (grayscale)
    at_texel_format_la8_unorm       AT_ENUM_AVAILABILITY_v1,        ///< Two channels, luminance then alpha  8 bpc
    at_texel_format_la16_unorm      AT_ENUM_AVAILABILITY_v1,        ///< Two channels, luminance then alpha  16 bpc
    at_texel_format_rgba8_unorm     AT_ENUM_AVAILABILITY_v1,        ///< MTLPixelFormatRGBA8Unorm
    at_texel_format_bgra8_unorm     AT_ENUM_AVAILABILITY_v1,        ///< MTLPixelFormatBGRA8Unorm
    at_texel_format_rgba16_unorm    AT_ENUM_AVAILABILITY_v1,        ///< MTLPixelFormatRGBA16Unorm

    at_texel_format_l16_float       AT_ENUM_AVAILABILITY_v1,        ///< MTLPixelFormatR16Float,  R is luminance (grayscale)
    at_texel_format_la16_float      AT_ENUM_AVAILABILITY_v1,        ///< Two channels, luminance then alpha  16 bpc float
    at_texel_format_rgba16_float    AT_ENUM_AVAILABILITY_v1,        ///< MTLPixelFormatRGBA16Float

    
    // always last
    at_texel_format_count           AT_ENUM_AVAILABILITY_v1,        /* CAUTION: value subject to change! */
};
#else
OS_ENUM( at_texel_format, unsigned long,
    at_texel_format_invalid         AT_ENUM_AVAILABILITY_v1 = 0,    ///< MTLPixelFormatInvalid
    
    at_texel_format_l8_unorm        AT_ENUM_AVAILABILITY_v1,        ///< MTLPixelFormatR8Unorm,   R is luminance (grayscale)
    at_texel_format_l16_unorm       AT_ENUM_AVAILABILITY_v1,        ///< MTLPixelFormatR16Unorm,  R is luminance (grayscale)
    at_texel_format_la8_unorm       AT_ENUM_AVAILABILITY_v1,        ///< Two channels, luminance then alpha  8 bpc
    at_texel_format_la16_unorm      AT_ENUM_AVAILABILITY_v1,        ///< Two channels, luminance then alpha  16 bpc
    at_texel_format_rgba8_unorm     AT_ENUM_AVAILABILITY_v1,        ///< MTLPixelFormatRGBA8Unorm
    at_texel_format_bgra8_unorm     AT_ENUM_AVAILABILITY_v1,        ///< MTLPixelFormatBGRA8Unorm
    at_texel_format_rgba16_unorm    AT_ENUM_AVAILABILITY_v1,        ///< MTLPixelFormatRGBA16Unorm
    
    at_texel_format_l16_float       AT_ENUM_AVAILABILITY_v1,        ///< MTLPixelFormatR16Float,  R is luminance (grayscale)
    at_texel_format_la16_float      AT_ENUM_AVAILABILITY_v1,        ///< Two channels, luminance then alpha  16 bpc float
    at_texel_format_rgba16_float    AT_ENUM_AVAILABILITY_v1,        ///< MTLPixelFormatRGBA16Float
    
    
    // always last
    at_texel_format_count           AT_ENUM_AVAILABILITY_v1,        /* CAUTION: value subject to change! */
);
#endif
        
/*!
 *  @abstract Convert a at_texel_format_t to a MTLPixelFormat
 *  @return  A MTLPixelFormat as a unsigned int
 *           Some at_texel_format_ts do not have a corresponding MTLPixelFormat
 *           in which case MTLPixelFormatInvalid will be returned.
 */
uint32_t at_texel_format_to_MTLPixelFormat(at_texel_format_t);


/*! @enum       at_block_format_t
 *  @abstract A compressed block format
 *
 *  @memberof   at_encoder_t
 */
#if defined(DOXYGEN)
typedef enum at_block_format_t{
    at_block_format_invalid         AT_ENUM_AVAILABILITY_v1 = 0,     ///< MTLPixelFormatInvalid
    
    at_block_format_astc_4x4_ldr    AT_ENUM_AVAILABILITY_v1,         ///< MTLPixelFormatASTC_4x4_LDR
    at_block_format_astc_5x4_ldr    AT_ENUM_AVAILABILITY_v1,         ///< MTLPixelFormatASTC_5x4_LDR, decode only
    at_block_format_astc_5x5_ldr    AT_ENUM_AVAILABILITY_v1,         ///< MTLPixelFormatASTC_5x5_LDR, decode only
    at_block_format_astc_6x5_ldr    AT_ENUM_AVAILABILITY_v1,         ///< MTLPixelFormatASTC_6x5_LDR, decode only
    at_block_format_astc_6x6_ldr    AT_ENUM_AVAILABILITY_v1,         ///< MTLPixelFormatASTC_6x6_LDR, decode only
    at_block_format_astc_8x5_ldr    AT_ENUM_AVAILABILITY_v1,         ///< MTLPixelFormatASTC_8x5_LDR, decode only
    at_block_format_astc_8x6_ldr    AT_ENUM_AVAILABILITY_v1,         ///< MTLPixelFormatASTC_8x6_LDR, decode only
    at_block_format_astc_8x8_ldr    AT_ENUM_AVAILABILITY_v1,         ///< MTLPixelFormatASTC_8x8_LDR
    at_block_format_astc_10x5_ldr   AT_ENUM_AVAILABILITY_v1,         ///< MTLPixelFormatASTC_10x5_LDR, decode only
    at_block_format_astc_10x6_ldr   AT_ENUM_AVAILABILITY_v1,         ///< MTLPixelFormatASTC_10x6_LDR, decode only
    at_block_format_astc_10x8_ldr   AT_ENUM_AVAILABILITY_v1,         ///< MTLPixelFormatASTC_10x5_LDR, decode only
    at_block_format_astc_10x10_ldr  AT_ENUM_AVAILABILITY_v1,         ///< MTLPixelFormatASTC_10x10_LDR, decode only
    at_block_format_astc_12x10_ldr  AT_ENUM_AVAILABILITY_v1,         ///< MTLPixelFormatASTC_12x10_LDR, decode only
    at_block_format_astc_12x12_ldr  AT_ENUM_AVAILABILITY_v1,         ///< MTLPixelFormatASTC_12x12_LDR, decode only
    
    // always last
    at_block_format_count                                           /* CAUTION: value subject to change! */
};
#else
OS_ENUM( at_block_format, unsigned long,
    at_block_format_invalid         AT_ENUM_AVAILABILITY_v1 = 0,           ///< MTLPixelFormatInvalid

    at_block_format_astc_4x4_ldr    AT_ENUM_AVAILABILITY_v1,       ///< MTLPixelFormatASTC_4x4_LDR
    at_block_format_astc_5x4_ldr    AT_ENUM_AVAILABILITY_v1,       ///< MTLPixelFormatASTC_5x4_LDR, decode only
    at_block_format_astc_5x5_ldr    AT_ENUM_AVAILABILITY_v1,       ///< MTLPixelFormatASTC_5x5_LDR, decode only
    at_block_format_astc_6x5_ldr    AT_ENUM_AVAILABILITY_v1,       ///< MTLPixelFormatASTC_6x5_LDR, decode only
    at_block_format_astc_6x6_ldr    AT_ENUM_AVAILABILITY_v1,       ///< MTLPixelFormatASTC_6x6_LDR, decode only
    at_block_format_astc_8x5_ldr    AT_ENUM_AVAILABILITY_v1,       ///< MTLPixelFormatASTC_8x5_LDR, decode only
    at_block_format_astc_8x6_ldr    AT_ENUM_AVAILABILITY_v1,       ///< MTLPixelFormatASTC_8x6_LDR, decode only
    at_block_format_astc_8x8_ldr    AT_ENUM_AVAILABILITY_v1,       ///< MTLPixelFormatASTC_8x8_LDR
    at_block_format_astc_10x5_ldr   AT_ENUM_AVAILABILITY_v1,       ///< MTLPixelFormatASTC_10x5_LDR, decode only
    at_block_format_astc_10x6_ldr   AT_ENUM_AVAILABILITY_v1,       ///< MTLPixelFormatASTC_10x6_LDR, decode only
    at_block_format_astc_10x8_ldr   AT_ENUM_AVAILABILITY_v1,       ///< MTLPixelFormatASTC_10x5_LDR, decode only
    at_block_format_astc_10x10_ldr  AT_ENUM_AVAILABILITY_v1,       ///< MTLPixelFormatASTC_10x10_LDR, decode only
    at_block_format_astc_12x10_ldr  AT_ENUM_AVAILABILITY_v1,       ///< MTLPixelFormatASTC_12x10_LDR, decode only
    at_block_format_astc_12x12_ldr  AT_ENUM_AVAILABILITY_v1,       ///< MTLPixelFormatASTC_12x12_LDR, decode only

    // always last
    at_block_format_count                                          /* CAUTION: value subject to change! */
);
#endif

/*!
 *  @abstract Convert a at_block_format to a MTLPixelFormat
 *  @return  A MTLPixelFormat as a unsigned int
 */
uint32_t at_block_format_to_MTLPixelFormat(at_block_format_t);
        
/*! @enum       at_flags_t
 *  @abstract   Flags to influence the operation of the ASTC encoder
 *  @constant   at_flags_default  Default operation
 *  @constant   at_flags_skip_parameter_checking  Assume parameters are sane and proceed blindly forward withput parameter error checking.
 *  @constant   at_flags_print_debug_info Print additional debug info to stderr in case of error
 *  @constant   at_flags_disable_multithreading  Run entirely in this thread
 *  @constant   at_flags_skip_error_calculation   Skip work to calculate mean square error per texel. Return 0 instead on no error.
 *  @constant   at_flags_flip_texel_region_vertically Read/write the texel region from bottom to top instead of top to bottom.
 *  @constant   at_flags_srgb_linear_texels  Apply the sRGB->linear gamma curve to texel results on decode.  Same effect as SRGB variants of LDR ASTC MTLPixelFormats. Decode only.
 *
 *  @memberof   at_encoder_t
 */
#if defined(DOXYGEN)
typedef enum at_flags_t
{
    at_flags_default                       AT_ENUM_AVAILABILITY_v1  =   0,
    at_flags_skip_parameter_checking       AT_ENUM_AVAILABILITY_v1  =   1U << 0,    //*<  Do not spend time checking input parameters */
    at_flags_print_debug_info              AT_ENUM_AVAILABILITY_v1  =   1U << 1,    //*<  Print additional debug info to stderr */
    at_flags_disable_multithreading        AT_ENUM_AVAILABILITY_v1  =   1U << 2,    //*<  Run entirely in this thread */
    at_flags_skip_error_calculation        AT_ENUM_AVAILABILITY_v1  =   1U << 3,    //*<  Skip work and memory usage associated with calculating aggregate mean square error. Return 0 instead. */
    at_flags_flip_texel_region_vertically  AT_ENUM_AVAILABILITY_v1  =   1U << 4,    //*<  Read/write the texel region from bottom to top instead of top to bottom.
    at_flags_srgb_linear_texels            AT_ENUM_AVAILABILITY_v1  =   1U << 5,    //*<  Contents of at_texel_region_t use linear gamma (decode only)*/
    at_flags_weight_channels_equally       AT_ENUM_AVAILABILITY_v1  =   1U << 6,    //*<  By default, RGB values are assumed to actually be red, green and blue and will be treated as such when calculating luminance and evaluating error. This flag cuases the chanels to be weighted equally, instead of the usual RGB->luminance formula. Encode only.*/
    
    /* other bits are reserved */
};
#else
OS_ENUM( at_flags, uint64_t,
    at_flags_default                       AT_ENUM_AVAILABILITY_v1  =   0,
    at_flags_skip_parameter_checking       AT_ENUM_AVAILABILITY_v1  =   1U << 0,    //*<  Do not spend time checking input parameters */
    at_flags_print_debug_info              AT_ENUM_AVAILABILITY_v1  =   1U << 1,    //*<  Print additional debug info to stderr */
    at_flags_disable_multithreading        AT_ENUM_AVAILABILITY_v1  =   1U << 2,    //*<  Run entirely in this thread */
    at_flags_skip_error_calculation        AT_ENUM_AVAILABILITY_v1  =   1U << 3,    //*<  Skip work and memory usage associated with calculating aggregate mean square error. Return 0 instead. */
    at_flags_flip_texel_region_vertically  AT_ENUM_AVAILABILITY_v1  =   1U << 4,    //*<  Read/write the texel region from bottom to top instead of top to bottom.
    at_flags_srgb_linear_texels            AT_ENUM_AVAILABILITY_v1  =   1U << 5,    //*<  Contents of at_texel_region_t use linear gamma (decode only)*/
    at_flags_weight_channels_equally       AT_ENUM_AVAILABILITY_v1  =   1U << 6,    //*<  By default, RGB values are assumed to actually be red, green and blue and will be treated as such when calculating luminance and evaluating error. This flag cuases the chanels to be weighted equally, instead of the usual RGB->luminance formula. Encode only.*/

    /* other bits are reserved */
);
#endif
        
/*! @enum       at_error_t
 *  @abstract   Error codes for at_encoder_t
 *  @constant   at_error_success                    The operation completed successfully
 *  @constant   at_error_invalid_parameter          One of the parameters was incorrect. Try 
 *                                                  at_flags_print_debug_info for more info.
 *  @constant   at_error_operation_unsupported      The operation is unsupported. Sometimes only decoding or
 *                                                  encoding might be supported for a particular encoder.
 *  @constant   at_error_invalid_source_data        Something in the source data was invalid. Typically,
 *                                                  a reserved block encoding was encountered during decoding.
 *  @constant   at_error_invalid_flag               The option requested by the flag is unsupported for this
 *                                                  at_encoder_t encode or decode operation. Retry with at_flags_default.
 */
#if defined(DOXYGEN)
typedef enum at_error_t
{
    at_error_success                       AT_ENUM_AVAILABILITY_v1  =   0,
    
    /* All failures are negative */
    at_error_invalid_parameter             AT_ENUM_AVAILABILITY_v1  =   -1,
    at_error_operation_unsupported         AT_ENUM_AVAILABILITY_v1  =   -2,
    at_error_invalid_source_data           AT_ENUM_AVAILABILITY_v1  =   -3,
    at_error_invalid_flag                  AT_ENUM_AVAILABILITY_v1  =   -4,
};
#else
OS_ENUM( at_error, long,
    at_error_success                       AT_ENUM_AVAILABILITY_v1  =   0,
    
    /* All failures are negative */
    at_error_invalid_parameter             AT_ENUM_AVAILABILITY_v1  =   -1,
    at_error_operation_unsupported         AT_ENUM_AVAILABILITY_v1  =   -2,
    at_error_invalid_source_data           AT_ENUM_AVAILABILITY_v1  =   -3,
    at_error_invalid_flag                  AT_ENUM_AVAILABILITY_v1  =   -4,
);
#endif
        
        
        
/*! @struct     at_size_t
 *  @abstract   Structure to describe the size of an image or offset into an image
 */
typedef struct at_size_t
{
    uint32_t    x;      /**< Size of image in horizontal and most quickly varying dimension. */
    uint32_t    y;      /**< Size of image in vertical and second most quickly varying dimension */
    uint32_t    z;      /**< Size of image in 3rd and least most quickly varying dimension */
}at_size_t;


/*! @struct     at_texel_region_t
 *  @abstract   A rectangular region of input texels in a texel buffer
 */
typedef struct at_texel_region_t
{
    void * __nonnull        texels;     /**< A pointer to the top left corner of the region of input data to be encoded. */
    at_size_t               validSize;  /**< The size (in texels) of the source region to encode. Does not need to be a multiple of a block size. */
    size_t                  rowBytes;   /**< The number of bytes from the start of one row to the next. */
    size_t                  sliceBytes; /**< The number of bytes from the start of one slice to the next. */
}at_texel_region_t;

/*! @struct     at_block_buffer_t
 *  @abstract   A rectangular region of input texels in a texel buffer. The Asize is inferred from the size of the corresponding at_texel_region_t, from which the data is taken.
 */
typedef struct at_block_buffer_t
{
    void * __nonnull        blocks;     /**< A pointer to the top left corner of the region of block data to write after encoding. Must be 16-byte aligned. */
    size_t                  rowBytes;   /**< The number of bytes from the start of one row to the next. Must be a multiple of the block size.*/
    size_t                  sliceBytes; /**< The number of bytes from the start of one slice to the next. Must be a multiple of the block size. */
}at_block_buffer_t;


/*!
 *  @class      at_encoder_t
 *  @abstract   An encoder for compressing and decompressing textures into formats such as ASTC.
 *  @discussion The at_encoder_t defines an interface for an opaque object that can
 *              both compress and decompress common texture formats, such as ASTC.
 *              These formats generally comsume texels (pixels) in a small rectangular
 *              region and produce a single block of compressed data. For example,
 *              for the at_texel_format_astc_4x4_ldr (MTLPixelFormatASTC_4x4_LDR) 
 *              compressed texture type, the image is segmented in 4x4 rectangles.
 *              Each of these is encoded by a variety of means to a 128-bit block.
 *              When compressing an image texels are consumed and blocks are produced.
 *              When decompressing an image blocks are consumed and texels are produced.
 *              Not all encoder types are capable of both encoding and decoding.
 *
 *              When working with such formats, it is important to know the block
 *              size, since you generally need to stride through the image in multiples
 *              of the block size to avoid encoding artifacts at the block seams.
 *              For texel coordinates, this is given by at_encoder_get_block_dimensions(). 
 *              For block coordinates, this is given by at_encoder_get_block_size().
 *
 *              In some cases, the at_encoder_t can work with subregions of an image.
 *              In these cases, it is said to be not monolithic. In other cases, the
 *              entire image is needed to get the right answer. Such at_encoder_ts 
 *              will be tagged as monolithic. Please check at_encoder_is_compression_monolithic
 *              or at_encoder_is_decompression_monolithic as appropriate before attempting
 *              to encode or decode subregions of an image.
 *
 *              The at_encoder_t is an os_object.  It should be released with os_release
 *              when you are done using it.
 */
#if OS_OBJECT_USE_OBJC && ! defined(DOXYGEN)
OS_OBJECT_DECL(at_encoder);
#else
typedef struct at_encoder *  at_encoder_t;
#endif

/*!
 *  @abstract Create an at_encoder_t
 *  @discussion An at_encoder_t can produce convert between compressed texture blocks and raw texel data. 
 *              An at_encoder_t is thread safe. A single at_encoder_t may be used from multiple threads 
 *              concurrently. Use os_retain / os_release to manage the lifetime of the encoder. The
 *              at_encoder_t type supports automatic reference counting (ARC). While most operation is
 *              through its C interface, it also implements some common NSObject methods:
 *
 *                  -debugDescription       (lldb po)
 *                  -isEqual:
 *                  -copy
 *                  -hash
 *
 *              The encoder can do basic transformations to image alpha as part of the operation.
 *              In some cases, this can help prevent another pass on the data. In other cases,
 *              knowledge of the alpha in the image, particularly if it is at_alpha_opaque,
 *              can help improve compression speed and image fidelity.
 *
 *  @param    texelType         The encoding of the uncompressed texel data, described by a at_texel_region_t.
 *                              See description for supported types.
 *  @param    texelAlphaType    The encoding of the alpha infomation in the uncompressed texel data
 *  @param    blockType         The format of the compressed blocks. Indicates block size. See description for supported types.
 *  @param    blockAlphaType    The encoding of the alpha in the compressed blocks.
 *  @param    backgroundColor   If the input image is not opaque and the output image is opaque
 *                              (outAlpha = at_alpha_opaque), then the image will
 *                              be made opaque by compositing it against a opaque background color
 *                              prior to encoding. If NULL, then {0} is used. Memory pointed
 *                              to by backgroundColor is copied by the function and may be released
 *                              immediately after the function returns. The length of the background
 *                              color array is the number of color (not alpha) channels in the input
 *                              image. The order of the colors matches the color space.  So for
 *                              BGRA data, the order is R,G,B.
 *
 *  @result A valid at_encoder_t or NULL if an error occurred.  Retain/release with os_retain / os_release
 *  @memberof   at_encoder_t
 */
at_encoder_t __nullable OS_OBJECT_RETURNS_RETAINED at_encoder_create(
                                                                     at_texel_format_t           texelType,
                                                                     at_alpha_t                  texelAlphaType,
                                                                     at_block_format_t           blockType,
                                                                     at_alpha_t                  blockAlphaType,
                                                                     const float * __nullable    backgroundColor
                                                                     )  AT_AVAILABILITY_v1;

/*! @function   at_encoder_compress_texels
 *  @abstract   Encode raw texel data to a rectangular region of a block based compressed texture
 *  @discussion Some compressed texture formats such as ASTC are encoded as a grid of fixed-sized block, each
 *              encoding for a region of {MxNxO} texels. The number of texels in the block is given by the output
 *              at_texel_format used when creating the at_encoder_t.
 *
 *              The blocks are ordered with the x dimension increasing most rapidly, then y dimension,
 *              then z dimension.  There is no padding between rows of  blocks in any dimension. The position
 *              of the texel in the region of interest of the input image corresponding to the top,left corner of
 *              each block is given by:
 *
 *                  texel_position.x = block_position.x * block_size_in_texels.x
 *                  texel_position.y = block_position.y * block_size_in_texels.y
 *                  texel_position.z = block_position.z * block_size_in_texels.z
 *
 *              Each block is encoded using one of a large variety of encoding methods. Some methods are more
 *              likely to work than others. These are tried first. If the accuracy of the encoding is not good
 *              enough, as determined by comparing its mean square error per normalized texel against the
 *              errorThreshold, then additional methods are tried. Some blocks may not meet the errorThreshold
 *              by any encoding method, in which case the encoding method that produced the best results is used.
 *
 *              If the src->validSize is not a multiple of the block size, some texels are undefined. For such texels,
 *              the nearest texel is used instead. All blocks must contain at least one valid texel or
 *              else behavior is undefined.
 *
 *              This function may be called from multiple threads on the same encoder concurrently.
 *
 *              Currently supported input formats are:
 *              @code
 *                  all
 *              @endcode
 *
 *              Currently supported output formats are:
 *              @code
 *                  at_texel_format_astc_4x4_ldr
 *                  at_texel_format_astc_8x8_ldr
 *              @endcode
 *
 *              Per the LDR subset of the ASTC specification, only 2D textures are supported.
 *              sRGB textures (e.g. MTLPixelFormatASTC_4x4_sRGB) should be encoded using the LDR
 *              formats, and decoded with the at_flags_srgb_linear_texels flag.  There is 
 *              currently no support for reading linear gamma textures with at_flags_srgb_linear_texels
 *              during encode.
 *
 *  @param      encoder             A valid at_encoder_t
 *  @param      src                 Pointer to a valid at_texel_region_t describing which texels to encode
 *  @param      dest                Pointer to a valid at_block_buffer_t describing which ASTC blocks to overwrite
 *  @param      errorThreshold      Mean square error per normalized texel (range [0,1]) below which to skip additional
 *                                  encoding attempts. Since it is square error, the minimum sensible value is 0.
 *                                  A value of 0 will cause the encoder to attempt all the available encodings
 *                                  it knows about unless one succeeds in encoding the block without loss of precision.
 *
 *                                  Common error thresholds are in the 2**-10 (fast) to 2**-15 (best quality) range.
 *
 *  @param      flags               Options to control operation of the encode filter.
 *
 *  @return     If >= 0, Success. The mean square error per normalized texel (range [0,1]) in the encode region
 *              is returned. Peak signal to noise ratio can be calculated from this number as PSNR = -10 * log10(result).
 *
 *              If < 0, then an error occurred and no encoding was done.
 *              All error codes are negative and have integer value. Please see at_error_t for
 *              a description of negative error codes.
 *
 *  @memberof   at_encoder_t
 */
float at_encoder_compress_texels(
                                 const at_encoder_t __nonnull encoder,
                                 const at_texel_region_t * __nonnull src,
                                 const at_block_buffer_t * __nonnull dest,
                                 float errorThreshold,
                                 at_flags_t flags
                                 )  AT_AVAILABILITY_v1;

/*! @function   at_encoder_decompress_texels
 *  @abstract   Decompress a sequence of iamge blocks to texel data
 *  @discussion Some compressed texture formats such as ASTC are encoded as a grid of fixed-sized block, each
 *              encoding for a region of {MxNxO} texels. The number of texels in the block is given by the output
 *              at_texel_format used when creating the at_encoder_t.
 *
 *              The blocks are ordered with the x dimension increasing most rapidly, then y dimension,
 *              then z dimension.  There is no padding between rows of blocks in any dimension. The position
 *              of the texel in the region of interest of the input image corresponding to the top,left corner of
 *              each block is given by:
 *
 *                  texel_position.x = block_position.x * block_size_in_texels.x
 *                  texel_position.y = block_position.y * block_size_in_texels.y
 *                  texel_position.z = block_position.z * block_size_in_texels.z
 *
 *              If dest->validSize is not a multiple of the block size, Only the region covered by the 
 *              dest->validSize will be overwritten.
 *
 *              This function may be called from multiple threads on the same encoder concurrently.
 *
 *              Currently supported input formats are:
 *              @code
 *                  all ASTC
 *              @endcode
 *
 *              Currently supported output formats are:
 *              @code
 *                  all
 *              @endcode
 *
 *              Per the LDR subset of the ASTC specification, only 2D textures are supported.
 *              sRGB textures (e.g. MTLPixelFormatASTC_4x4_sRGB) should be decoded using the LDR
 *              formats in conjunction with the at_flags_srgb_linear_texels flag.
 *
 *  @param      encoder             A valid at_encoder_t
 *  @param      src                 Pointer to a valid at_block_buffer_t describing which blocks to read
 *  @param      dest                Pointer to a valid at_texel_region_t describing which texels to overwrite
 *
 *  @param      flags               Options to control operation of the decode filter.
 *
 *  @return     If >= 0, Success. The mean square error per normalized texel (range [0,1]) in the encode region
 *              is returned. Peak signal to noise ratio can be calculated from this number as PSNR = -10 * log10(result).
 *
 *              If < 0, then an error occurred and no encoding was done.
 *              All error codes are negative and have integer value. Please see at_error_t for
 *              a description of each negative error code.
 *
 *  @memberof   at_encoder_t
 */
at_error_t at_encoder_decompress_texels(
                                   const at_encoder_t __nonnull encoder,
                                   const at_block_buffer_t * __nonnull src,
                                   const at_texel_region_t * __nonnull dest,
                                   at_flags_t flags
                                 )  AT_AVAILABILITY_v1;

/*! @function   at_encoder_get_block_counts
 *  @abstract   Return the number of blocks needed to hold the encoded image size.
 *  @param      encoder     The at_encoder_t
 *  @param      imageSize   A pointer to a valid at_size_t giving the size of the input image in texels
 *  @return     The size of the raw encoded ASTC image data in ATEASTCBlocks in each dimension.
 *              In a ASTC file, there is no padding between consecutive rows or slices.
 *
 *  @memberof   at_encoder_t
 */
at_size_t  at_encoder_get_block_counts( at_encoder_t __nonnull  encoder,
                                        at_size_t imageSize )   AT_AVAILABILITY_v1;


/*! @function   at_encoder_get_block_dimensions
 *  @abstract   Get the size of block in the encoded image
 *  @param      encoder     The at_encoder_t
 *  @return     The size {x,y,z} in texels of each block in the encoded image.
 *
 *  @memberof   at_encoder_t
 */
at_size_t  at_encoder_get_block_dimensions( const at_encoder_t __nonnull encoder)   AT_AVAILABILITY_v1;

/*! @function   at_encoder_get_block_size
 *  @abstract   Get the size of block in the encoded image in bytes
 *  @param      encoder     The at_encoder_t
 *  @return     The size in bytes of each block in the encoded image.
 *
 *  @memberof   at_encoder_t
 */
size_t  at_encoder_get_block_size( const at_encoder_t __nonnull encoder)    AT_AVAILABILITY_v1;

/*! @function   at_encoder_get_texel_format
 *  @abstract   Get the image type of the uncompressed texels
 *  @param      encoder     The at_encoder_t
 *  @return     The image type of the texels.  See also: at_texel_format_to_MTLPixelFormat
 */
at_texel_format_t  at_encoder_get_texel_format( const at_encoder_t __nonnull encoder)   AT_AVAILABILITY_v1;

/*! @function   at_encoder_get_block_format
 *  @abstract   Get the image type of the encoded blocks
 *  @param      encoder     The at_encoder_t
 *  @return     The image type of the output image.   See also: at_block_format_to_MTLPixelFormat
 *
 *  @memberof   at_encoder_t
 */
at_block_format_t  at_encoder_get_block_format( const at_encoder_t __nonnull encoder)   AT_AVAILABILITY_v1;

/*! @function   at_encoder_get_texel_alpha
 *  @abstract   Get the alpha type of the uncompressed texels
 *  @param      encoder     The at_encoder_t
 *  @return     The alpha type of the uncompressed texels
 */
at_alpha_t at_encoder_get_texel_alpha( const at_encoder_t __nonnull encoder)    AT_AVAILABILITY_v1;

/*! @function   at_encoder_get_block_alpha
 *  @abstract   Get the alpha type of the compressed blocks
 *  @param      encoder     The at_encoder_t
 *  @return     The alpha type of the compressed blocks
 *
 *  @memberof   at_encoder_t
 */
at_alpha_t at_encoder_get_block_alpha( const at_encoder_t __nonnull encoder)    AT_AVAILABILITY_v1;

        
/*! @function   at_encoder_compression_is_monolithic
 *  @abstract   Returns true if the encoder requires monolithic operation when compressing texels
 *  @discussion Some compressed texture formats require information from adjacent blocks
 *              in order to correctly encode / decode the current block. These formats
 *              are said to be monolithic. In such cases, even though
 *              at_encoder_compress_texels in principle allows you to call it
 *              with only part of an image, doing so will result in incorrect
 *              results.
 *  @param      encoder          The at_encoder_t
 *  @param      flags            The flags parameter to used with at_encoder_compress_texels
 *  @return     true if monolithic
 *              false if processing subregions of the image separately is allowed.
 */
bool at_encoder_is_compression_monolithic( const at_encoder_t __nonnull encoder, at_flags_t flags )   AT_AVAILABILITY_v1;


/*! @function   at_encoder_decompression_is_monolithic
 *  @abstract   Returns true if the encoder requires monolithic operation when decompressing texels
 *  @discussion Some compressed texture formats require information from adjacent blocks
 *              in order to correctly encode / decode the current block. These formats
 *              are said to be monolithic. In such cases, even though
 *              at_encoder_compress_texels in principle allows you to call it
 *              with only part of an image, doing so will result in incorrect
 *              results.
 *  @param      encoder          The at_encoder_t
 *  @param      flags            The flags parameter to used with at_encoder_decompress_texels
 *  @return     true if monolithic
 *              false if processing subregions of the image separately is allowed.
 */
bool at_encoder_is_decompression_monolithic( const at_encoder_t __nonnull encoder, at_flags_t flags ) AT_AVAILABILITY_v1;
        
/*!
 *  @abstract   Convenience method to find the position of an encoded block based on texel position
 *  @param      encoder          The at_encoder_t
 *  @param      texelPosition    An offset into the source image, in texels. If offset is not a
 *                               multiple of the block size, it will be rounded down.
 *  @param      imageSize        The size of the image in texels
 *  @param      blockInfo        A valid pointer to the storage where the ASTC blocks are kept
 *  @return     A pointer to the block containing the texel.
 *
 *  @memberof   at_encoder_t
 */
void * __nullable at_encoder_get_block_address(const at_encoder_t __nonnull encoder,
                                               at_size_t texelPosition,
                                               at_size_t imageSize,
                                               const at_block_buffer_t * __nonnull blockInfo )  AT_AVAILABILITY_v1;

#ifndef AT_LINK_STATIC
/*!
 *  @abstract   Get AppleTextureEncoder dylib.current_version
 *  @return     A uint32_t encoding library version as major.minor.bugfix  (16.8.8)
 *              The major field of the build version corresponds with the compatability
 *              version (e.g. AT_AVAILABILITY_v1)
 */
uint32_t  at_encoder_get_version(void)  AT_AVAILABILITY_v1;
#endif /* AT_LINK_STATIC */

#ifdef __cplusplus
    }  /* extern "C" */
#endif

#endif /* _AppleTextureEncoder_h_ */

