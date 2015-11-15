//
//  MTLPixelFormat.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>

NS_ASSUME_NONNULL_BEGIN
typedef NS_ENUM(NSUInteger, MTLPixelFormat)
{
    MTLPixelFormatInvalid = 0,

    /* Normal 8 bit formats */
    
    MTLPixelFormatA8Unorm      = 1,
    
    MTLPixelFormatR8Unorm      = 10,
#if TARGET_OS_EMBEDDED
    MTLPixelFormatR8Unorm_sRGB = 11,
#endif
    MTLPixelFormatR8Snorm      = 12,
    MTLPixelFormatR8Uint       = 13,
    MTLPixelFormatR8Sint       = 14,
    
    /* Normal 16 bit formats */

    MTLPixelFormatR16Unorm     = 20,
    MTLPixelFormatR16Snorm     = 22,
    MTLPixelFormatR16Uint      = 23,
    MTLPixelFormatR16Sint      = 24,
    MTLPixelFormatR16Float     = 25,

    MTLPixelFormatRG8Unorm      = 30,
#if TARGET_OS_EMBEDDED
    MTLPixelFormatRG8Unorm_sRGB = 31,
#endif
    MTLPixelFormatRG8Snorm      = 32,
    MTLPixelFormatRG8Uint       = 33,
    MTLPixelFormatRG8Sint       = 34,

    /* Packed 16 bit formats */

#if TARGET_OS_EMBEDDED
    MTLPixelFormatB5G6R5Unorm = 40,
    MTLPixelFormatA1BGR5Unorm = 41,
    MTLPixelFormatABGR4Unorm  = 42,
    MTLPixelFormatBGR5A1Unorm = 43,
#endif

    /* Normal 32 bit formats */

    MTLPixelFormatR32Uint  = 53,
    MTLPixelFormatR32Sint  = 54,
    MTLPixelFormatR32Float = 55,

    MTLPixelFormatRG16Unorm  = 60,
    MTLPixelFormatRG16Snorm  = 62,
    MTLPixelFormatRG16Uint   = 63,
    MTLPixelFormatRG16Sint   = 64,
    MTLPixelFormatRG16Float  = 65,

    MTLPixelFormatRGBA8Unorm      = 70,
    MTLPixelFormatRGBA8Unorm_sRGB = 71,
    MTLPixelFormatRGBA8Snorm      = 72,
    MTLPixelFormatRGBA8Uint       = 73,
    MTLPixelFormatRGBA8Sint       = 74,

    MTLPixelFormatBGRA8Unorm      = 80,
    MTLPixelFormatBGRA8Unorm_sRGB = 81,

    /* Packed 32 bit formats */

    MTLPixelFormatRGB10A2Unorm = 90,
    MTLPixelFormatRGB10A2Uint  = 91,

    MTLPixelFormatRG11B10Float = 92,
    MTLPixelFormatRGB9E5Float = 93,

    /* Normal 64 bit formats */

    MTLPixelFormatRG32Uint  = 103,
    MTLPixelFormatRG32Sint  = 104,
    MTLPixelFormatRG32Float = 105,

    MTLPixelFormatRGBA16Unorm  = 110,
    MTLPixelFormatRGBA16Snorm  = 112,
    MTLPixelFormatRGBA16Uint   = 113,
    MTLPixelFormatRGBA16Sint   = 114,
    MTLPixelFormatRGBA16Float  = 115,

    /* Normal 128 bit formats */

    MTLPixelFormatRGBA32Uint  = 123,
    MTLPixelFormatRGBA32Sint  = 124,
    MTLPixelFormatRGBA32Float = 125,

    /* Compressed formats. */

#if !TARGET_OS_EMBEDDED
    /* S3TC/DXT */
    MTLPixelFormatBC1_RGBA          = 130,
    MTLPixelFormatBC1_RGBA_sRGB     = 131,
    MTLPixelFormatBC2_RGBA          = 132,
    MTLPixelFormatBC2_RGBA_sRGB     = 133,
    MTLPixelFormatBC3_RGBA          = 134,
    MTLPixelFormatBC3_RGBA_sRGB     = 135,

    /* RGTC */
    MTLPixelFormatBC4_RUnorm        = 140,
    MTLPixelFormatBC4_RSnorm        = 141,
    MTLPixelFormatBC5_RGUnorm       = 142,
    MTLPixelFormatBC5_RGSnorm       = 143,

    /* BPTC */
    MTLPixelFormatBC6H_RGBFloat         = 150,
    MTLPixelFormatBC6H_RGBUfloat        = 151,
    MTLPixelFormatBC7_RGBAUnorm         = 152,
    MTLPixelFormatBC7_RGBAUnorm_sRGB    = 153,
#endif

#if TARGET_OS_EMBEDDED
    /* PVRTC */
    MTLPixelFormatPVRTC_RGB_2BPP       = 160,
    MTLPixelFormatPVRTC_RGB_2BPP_sRGB  = 161,
    MTLPixelFormatPVRTC_RGB_4BPP       = 162,
    MTLPixelFormatPVRTC_RGB_4BPP_sRGB  = 163,
    MTLPixelFormatPVRTC_RGBA_2BPP      = 164,
    MTLPixelFormatPVRTC_RGBA_2BPP_sRGB = 165,
    MTLPixelFormatPVRTC_RGBA_4BPP      = 166,
    MTLPixelFormatPVRTC_RGBA_4BPP_sRGB = 167,

    /* ETC2 */
    MTLPixelFormatEAC_R11Unorm        = 170,
    MTLPixelFormatEAC_R11Snorm        = 172,
    MTLPixelFormatEAC_RG11Unorm       = 174,
    MTLPixelFormatEAC_RG11Snorm       = 176,
    MTLPixelFormatEAC_RGBA8      = 178,
    MTLPixelFormatEAC_RGBA8_sRGB = 179,

    MTLPixelFormatETC2_RGB8        = 180,
    MTLPixelFormatETC2_RGB8_sRGB   = 181,
    MTLPixelFormatETC2_RGB8A1      = 182,
    MTLPixelFormatETC2_RGB8A1_sRGB = 183,
#endif

#if TARGET_OS_EMBEDDED
    /* ASTC */
    MTLPixelFormatASTC_4x4_sRGB           = 186,
    MTLPixelFormatASTC_5x4_sRGB           = 187,
    MTLPixelFormatASTC_5x5_sRGB           = 188,
    MTLPixelFormatASTC_6x5_sRGB           = 189,
    MTLPixelFormatASTC_6x6_sRGB           = 190,
    MTLPixelFormatASTC_8x5_sRGB           = 192,
    MTLPixelFormatASTC_8x6_sRGB           = 193,
    MTLPixelFormatASTC_8x8_sRGB           = 194,
    MTLPixelFormatASTC_10x5_sRGB          = 195,
    MTLPixelFormatASTC_10x6_sRGB          = 196,
    MTLPixelFormatASTC_10x8_sRGB          = 197,
    MTLPixelFormatASTC_10x10_sRGB         = 198,
    MTLPixelFormatASTC_12x10_sRGB         = 199,
    MTLPixelFormatASTC_12x12_sRGB         = 200,

    MTLPixelFormatASTC_4x4_LDR            = 204,
    MTLPixelFormatASTC_5x4_LDR            = 205,
    MTLPixelFormatASTC_5x5_LDR            = 206,
    MTLPixelFormatASTC_6x5_LDR            = 207,
    MTLPixelFormatASTC_6x6_LDR            = 208,
    MTLPixelFormatASTC_8x5_LDR            = 210,
    MTLPixelFormatASTC_8x6_LDR            = 211,
    MTLPixelFormatASTC_8x8_LDR            = 212,
    MTLPixelFormatASTC_10x5_LDR           = 213,
    MTLPixelFormatASTC_10x6_LDR           = 214,
    MTLPixelFormatASTC_10x8_LDR           = 215,
    MTLPixelFormatASTC_10x10_LDR          = 216,
    MTLPixelFormatASTC_12x10_LDR          = 217,
    MTLPixelFormatASTC_12x12_LDR          = 218,
#endif

    /*!
     @constant MTLPixelFormatGBGR422
     @abstract A pixel format where the red and green channels are subsampled horizontally.  Two pixels are stored in 32 bits, with shared red and blue values, and unique green values.
     @discussion This format is equivelent to YUY2, YUYV, yuvs, or GL_RGB_422_APPLE/GL_UNSIGNED_SHORT_8_8_REV_APPLE.   The component order, from lowest addressed byte to highest, is Y0, Cb, Y1, Cr.  There is no implicit colorspace conversion from YUV to RGB, the shader will receive (Cr, Y, Cb, 1).  422 textures must have a width that is a multiple of 2, and can only be used for 2D non-mipmap textures.  When sampling, ClampToEdge is the only usable wrap mode.
     */
    MTLPixelFormatGBGR422 = 240,

    /*!
     @constant MTLPixelFormatBGRG422
     @abstract A pixel format where the red and green channels are subsampled horizontally.  Two pixels are stored in 32 bits, with shared red and blue values, and unique green values.
     @discussion This format is equivelent to UYVY, 2vuy, or GL_RGB_422_APPLE/GL_UNSIGNED_SHORT_8_8_APPLE. The component order, from lowest addressed byte to highest, is Cb, Y0, Cr, Y1.  There is no implicit colorspace conversion from YUV to RGB, the shader will receive (Cr, Y, Cb, 1).  422 textures must have a width that is a multiple of 2, and can only be used for 2D non-mipmap textures.  When sampling, ClampToEdge is the only usable wrap mode.
     */
    MTLPixelFormatBGRG422 = 241,

    /* Depth */

    MTLPixelFormatDepth32Float  = 252,

    /* Stencil */

    MTLPixelFormatStencil8        = 253,

    /* Packed Depth Stencil */

    MTLPixelFormatDepth24Unorm_Stencil8 = 255,

    /* Depth Stencil */

    MTLPixelFormatDepth32Float_Stencil8  = 260,

} NS_ENUM_AVAILABLE(10_11, 8_0);
NS_ASSUME_NONNULL_END