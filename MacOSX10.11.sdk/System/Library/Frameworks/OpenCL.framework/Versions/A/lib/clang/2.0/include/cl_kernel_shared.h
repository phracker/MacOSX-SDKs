/*******************************************************************************
 * Copyright:  (c) 2008-2012 by Apple, Inc., All Rights Reserved.
 ******************************************************************************/


#ifndef __CL_KERNEL_SHARED_H__
#define __CL_KERNEL_SHARED_H__

#ifndef __OPENCL_TYPES_DEFINED__
    #include <stddef.h>
    #include <stdint.h>

    typedef char            char16      __attribute__ ((__vector_size__(16)));
    typedef unsigned char   uchar16     __attribute__ ((__vector_size__(16)));
    typedef short           short8      __attribute__ ((__vector_size__(16)));
    typedef unsigned short  ushort8     __attribute__ ((__vector_size__(16)));
    typedef float           float4      __attribute__ ((__vector_size__(16)));
    typedef int             int4        __attribute__ ((__vector_size__(16)));
    typedef unsigned int    uint4       __attribute__ ((__vector_size__(16)));
    typedef long long       long2       __attribute__ ((__vector_size__(16)));
    typedef unsigned long long  ulong2  __attribute__ ((__vector_size__(16)));
    typedef double          double2     __attribute__ ((__vector_size__(16)));
    typedef size_t          event_t;
    typedef unsigned char   uchar;
    typedef unsigned short  ushort;
    typedef unsigned int    uint;

    typedef struct short16{ short8 lo, hi;  }short16;
    typedef struct ushort16{ ushort8 lo, hi;  }ushort16;

    typedef struct int8{ int4 lo,hi; }int8;
    typedef struct int16{ int8 lo,hi; }int16;

    typedef struct uint8{ uint4 lo,hi; }uint8;
    typedef struct uint16{ uint8 lo,hi; }uint16;

    typedef struct float8{ float4 lo,hi; }float8;
    typedef struct float16{ float8 lo,hi; }float16;
    typedef struct float32{ float16 lo,hi; }float32;

    #define __OPENCL_TYPES_DEFINED__
#endif /* __OPENCL_TYPES_DEFINED__ */

// Channel order; MUST be kept in sync with cld_internal.h in the drivers.
enum {
  CLK_R,
  CLK_A,
  CLK_RG,
  CLK_RA,
  CLK_RGB,
  CLK_RGBA,
  CLK_ARGB,
  CLK_BGRA,
  CLK_INTENSITY,
  CLK_LUMINANCE,
  CLK_Rx,
  CLK_RGx,
  CLK_RGBx,
  CLK_1RGB_APPLE,
  CLK_BGR1_APPLE,
  CLK_422_YCbYCr_APPLE,
  CLK_422_CbYCrY_APPLE,
  CLK_DEPTH_STENCIL,
  CLK_DEPTH,
  CLK_ABGR_APPLE
};

// Extension: cl_APPLE_yuv
// YUV color conversion matrices
enum {
    CLK_ITU_601_APPLE = 0x1000000A,
    CLK_ITU_709_APPLE = 0x1000000B
};

// Extension: cl_APPLE_yuv
// YUV chroma siting
enum {
    CLK_CHROMA_CENTERED_APPLE = 0x1000000C,
    CLK_CHROMA_COSITED_APPLE = 0x1000000D
};

typedef enum clk_channel_type{
  // valid formats for float return types
  CLK_SNORM_INT8,            // four channel RGBA unorm8
  CLK_UNORM_INT8,            // four channel RGBA unorm8
  CLK_SNORM_INT16,           // four channel RGBA unorm16
  CLK_UNORM_INT16,           // four channel RGBA unorm16
  CLK_HALF_FLOAT,            // four channel RGBA half
  CLK_FLOAT,                 // four channel RGBA float

  // valid only for integer return types
  CLK_SIGNED_INT8,
  CLK_SIGNED_INT16,
  CLK_SIGNED_INT32,
  CLK_UNSIGNED_INT8,
  CLK_UNSIGNED_INT16,
  CLK_UNSIGNED_INT32,

  // CI SPI for CPU
  __CLK_UNORM_INT8888,         // four channel ARGB unorm8
  __CLK_UNORM_INT8888R,        // four channel BGRA unorm8
  __CLK_UNORM_INT8A,           // single channel CL_A unorm8
  __CLK_UNORM_INT8I,           // single channel CL_INTENSITY unorm8

  CLK_UNORM_SHORT_565,
  CLK_UNORM_SHORT_555,
  CLK_UNORM_INT_101010,
  
  CLK_UNORM_INT8_ITU_601_APPLE,
  CLK_UNORM_INT8_ITU_709_APPLE,
  CLK_SFIXED14_APPLE,
  CLK_BIASED_HALF_APPLE,
  
  __CLK_VALID_IMAGE_TYPE_COUNT,
  __CLK_INVALID_IMAGE_TYPE = __CLK_VALID_IMAGE_TYPE_COUNT,
  __CLK_VALID_IMAGE_TYPE_MASK_BITS = 5,         // number of bits required to represent any image type
  __CLK_VALID_IMAGE_TYPE_MASK = ( 1 << __CLK_VALID_IMAGE_TYPE_MASK_BITS ) - 1
}clk_channel_type;

typedef enum clk_sampler_type
{
    __CLK_ADDRESS_BASE             = 0,
    CLK_ADDRESS_NONE               = 0 << __CLK_ADDRESS_BASE,
    CLK_ADDRESS_CLAMP              = 1 << __CLK_ADDRESS_BASE,
    CLK_ADDRESS_CLAMP_TO_EDGE      = 2 << __CLK_ADDRESS_BASE,
    CLK_ADDRESS_REPEAT             = 3 << __CLK_ADDRESS_BASE,
    CLK_ADDRESS_MIRRORED_REPEAT    = 4 << __CLK_ADDRESS_BASE,
    __CLK_ADDRESS_MASK             = CLK_ADDRESS_NONE | CLK_ADDRESS_CLAMP | CLK_ADDRESS_CLAMP_TO_EDGE | CLK_ADDRESS_REPEAT | CLK_ADDRESS_MIRRORED_REPEAT,
    __CLK_ADDRESS_BITS             = 3,        // number of bits required to represent address info

    __CLK_NORMALIZED_BASE          = __CLK_ADDRESS_BITS,
    CLK_NORMALIZED_COORDS_FALSE    = 0,
    CLK_NORMALIZED_COORDS_TRUE     = 1 << __CLK_NORMALIZED_BASE,
    __CLK_NORMALIZED_MASK          = CLK_NORMALIZED_COORDS_FALSE | CLK_NORMALIZED_COORDS_TRUE,
    __CLK_NORMALIZED_BITS          = 1,        // number of bits required to represent normalization 

    __CLK_FILTER_BASE              = __CLK_NORMALIZED_BASE + __CLK_NORMALIZED_BITS,
    CLK_FILTER_NEAREST             = 0 << __CLK_FILTER_BASE,
    CLK_FILTER_LINEAR              = 1 << __CLK_FILTER_BASE,
    CLK_FILTER_ANISOTROPIC         = 2 << __CLK_FILTER_BASE,
    __CLK_FILTER_MASK              = CLK_FILTER_NEAREST | CLK_FILTER_LINEAR | CLK_FILTER_ANISOTROPIC,
    __CLK_FILTER_BITS              = 2,        // number of bits required to represent address info

    __CLK_MIP_BASE                 = __CLK_FILTER_BASE + __CLK_FILTER_BITS,
    CLK_MIP_NEAREST                = 0 << __CLK_MIP_BASE,
    CLK_MIP_LINEAR                 = 1 << __CLK_MIP_BASE,
    CLK_MIP_ANISOTROPIC            = 2 << __CLK_MIP_BASE,
    __CLK_MIP_MASK                 = CLK_MIP_NEAREST | CLK_MIP_LINEAR | CLK_MIP_ANISOTROPIC,
    __CLK_MIP_BITS                 = 2,
  
    __CLK_SAMPLER_BITS             = __CLK_MIP_BASE + __CLK_MIP_BITS,
    __CLK_SAMPLER_MASK             = __CLK_MIP_MASK | __CLK_FILTER_MASK | __CLK_NORMALIZED_MASK | __CLK_ADDRESS_MASK,
    
    __CLK_ANISOTROPIC_RATIO_BITS   = 5,
    __CLK_ANISOTROPIC_RATIO_MASK   = (int) 0x80000000 >> (__CLK_ANISOTROPIC_RATIO_BITS-1)
}clk_sampler_type;


#if defined( __clang__ )
    //FIXME: commented out per <rdar://problem/6307429> ABI bustage in read_image
    #define __FAST_CALL           /* __attribute__ ((fastcall)) */
    #define __ALWAYS_INLINE       __attribute__ ((__always_inline__))
    #define INLINE                  inline
#else
    // compiling GCC version for debugging
    #define __FAST_CALL
    #define __ALWAYS_INLINE      __attribute__ (( __noinline__))
    #define INLINE
#endif

#endif /* __CL_KERNEL_SHARED_H__ */

