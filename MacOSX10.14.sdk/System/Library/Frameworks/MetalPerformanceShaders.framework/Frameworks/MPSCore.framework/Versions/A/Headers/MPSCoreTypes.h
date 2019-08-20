/*!
 *  @header     MPSTypes.h
 *  @framework  MPSCore
 *  @copyright  Copyright (c) 2017 Apple Inc. All rights reserved.
 *  @discussion Types common to MetalPerformanceShaders.framework
 */

#ifndef MPSCoreTypes_h
#define MPSCoreTypes_h

#import <Foundation/NSObject.h>
#import <Metal/Metal.h>

#ifdef __cplusplus
extern "C" {
#endif
    
/*
 *  Identify compiler capabilities
 */
#ifndef __has_attribute          /* clang will define this. Other compilers maybe not. */
#    define __has_attribute(a)   0
#endif
#ifndef __has_feature           /* clang will define this. Other compilers maybe not. */
#    define __has_feature(f)     0
#endif
#ifndef __has_extension         /* clang will define this. Other compilers maybe not. */
#    define __has_extension(e)   0
#endif
    
#if defined(DOXYGEN)
#   define  MPS_HIDE_AVAILABILITY 1
#endif
    
/*
 *  Macros to describe MPS functionality availability by operating system revision.
 */
#ifdef MPS_HIDE_AVAILABILITY
#    define MPS_ENUM_AVAILABLE_STARTING(...)
#    define MPS_ENUM_AVAILABLE_STARTING_BUT_DEPRECATED(...)
#    define MPS_CLASS_AVAILABLE_STARTING(...)
#    define MPS_AVAILABLE_STARTING(...)
#    define MPS_AVAILABLE_STARTING_BUT_DEPRECATED(...)
#else
#    define MPS_ENUM_AVAILABLE_STARTING(...)                    __API_AVAILABLE(__VA_ARGS__)
#    define MPS_ENUM_AVAILABLE_STARTING_BUT_DEPRECATED(...)     __API_DEPRECATED_WITH_REPLACEMENT(__VA_ARGS__)
#    define MPS_CLASS_AVAILABLE_STARTING(...)                   __API_AVAILABLE(__VA_ARGS__)
#    define MPS_AVAILABLE_STARTING(...)                         __API_AVAILABLE(__VA_ARGS__)
#    define MPS_AVAILABLE_STARTING_BUT_DEPRECATED(...)          __API_DEPRECATED_WITH_REPLACEMENT(__VA_ARGS__)
#endif
    
/*
 *  Some MPS interfaces have a slightly different name in Swift to 
 *  enhance readability. MPS_SWIFT_NAME is used to rename the interface
 *  for Swift.
 */
#if DOXYGEN
#   define  MPS_SWIFT_NAME(...)
#elif __has_feature(objc_class_property)
#   define  MPS_SWIFT_NAME(_name)    CF_SWIFT_NAME(_name)
#else
#   define  MPS_SWIFT_NAME(_name)
#endif
    
/*! @enum       MPSKernelOptions
 *  @memberof   MPSKernel
 *  @abstract   Options used when creating MPSKernel objects
 */
#if defined(DOXYGEN)
    typedef enum MPSKernelOptions
#else
    typedef NS_OPTIONS(NSUInteger, MPSKernelOptions)
#endif
{
    /*! Use default options */
    MPSKernelOptionsNone                         MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(9.0), tvos(9.0)) MPS_SWIFT_NAME(none) = 0U,
    
    /*! Most MPS functions will sanity check their arguments. This has a small but
     *  non-zero CPU cost. Setting the MPSKernelOptionsSkipAPIValidation will skip these checks.
     *  MPSKernelOptionsSkipAPIValidation does not skip checks for memory allocation failure.
     *  Caution:  turning on MPSKernelOptionsSkipAPIValidation can result in undefined behavior
     *  if the requested operation can not be completed for some reason. Most error states
     *  will be passed through to Metal which may do nothing or abort the program if Metal
     *  API validation is turned on. */
    MPSKernelOptionsSkipAPIValidation            MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(9.0), tvos(9.0))  = 1U << 0,
    
    /*! When possible, MPSKernels use a higher precision data representation internally than
     *  the destination storage format to avoid excessive accumulation of computational
     *  rounding error in the result. MPSKernelOptionsAllowReducedPrecision advises the
     *  MPSKernel that the destination storage format already has too much precision for
     *  what is ultimately required downstream, and the MPSKernel may use reduced precision
     *  internally when it feels that a less precise result would yield better performance.
     *  The expected performance win is often small, perhaps 0-20%. When enabled, the
     *  precision of the result may vary by hardware and operating system. */
    MPSKernelOptionsAllowReducedPrecision        MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(9.0), tvos(9.0))  = 1U << 1,
    
    /*! Some MPSKernels may automatically split up the work internally into multiple tiles.
     *  This improves performance on larger textures and reduces the amount of memory needed by
     *  MPS for temporary storage. However, if you are using your own tiling scheme to achieve
     *  similar results, your tile sizes and MPS's choice of tile sizes may interfere with
     *  one another causing MPS to subdivide your tiles for its own use inefficiently. Pass
     *  MPSKernelOptionsDisableInternalTiling to force MPS to process your data tile as a
     *  single chunk.   */
    MPSKernelOptionsDisableInternalTiling        MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(10.0), tvos(10.0)) = 1U << 2,
    
    /*! Enabling this bit will cause various -encode... methods to call MTLCommandEncoder
     *  push/popDebugGroup.  The debug string will be drawn from MPSKernel.label, if any
     *  or the name of the class otherwise. */
    MPSKernelOptionsInsertDebugGroups            MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(10.0), tvos(10.0)) = 1U << 3,

    /*! Some parts of MPS can provide debug commentary and tuning advice when run.
     *  Setting this bit to 1 will cause the commentary to be emitted to stderr. Otherwise,
     *  the code is silent.  This is especially useful for debugging MPSNNGraph. This option
     *  is on by default when the MPS_LOG_INFO environment variable is defined.  For
     *  even more detailed output on a MPS object, you can use the po command in llvm
     *  with MPS objects:
     *  @code
     *    llvm>  po  <MPS object pointer>
     *  @endcode */
    MPSKernelOptionsVerbose                      MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0)) = 1U << 4,
    
};
    
/*! @enum       MPSImageEdgeMode
 *  @memberof   MPSKernel
 *  @abstract   Options used to control edge behaviour of filter when filter reads beyond boundary of src image
 */
#if defined(DOXYGEN)
typedef enum MPSImageEdgeMode
#else
typedef NS_ENUM(NSUInteger, MPSImageEdgeMode)
#endif
{
    /*! Out of bound pixels are (0,0,0,1) for image with pixel format without alpha channel
     *  and (0,0,0,0) for image with pixel format that has an alpha channel */
    MPSImageEdgeModeZero                MPS_ENUM_AVAILABLE_STARTING(macos(10.13), ios(9.0), tvos(9.0)) MPS_SWIFT_NAME(zero)  = 0,
    
    /*! Out of bound pixels are clamped to nearest edge pixel */
    MPSImageEdgeModeClamp               MPS_ENUM_AVAILABLE_STARTING(macos(10.13), ios(9.0), tvos(9.0))  = 1,

    /*! Out of bound pixels are mirrored wrt. the nearest edge pixel center - ie. the edge of the image is not repeated.
     *  NOTE: The only filter that currently supports this mode is @ref MPSNNPad - using this with other filters results in undefined behavior. */
    MPSImageEdgeModeMirror              MPS_ENUM_AVAILABLE_STARTING( macos(10.14.1), ios(12.1), tvos(12.1)),

    /*! Out of bound pixels are mirrored wrt. the nearest edge pixel nearest border - ie. the edge of the image is repeated.
     *  NOTE: The only filter that currently supports this mode is @ref MPSNNPad - using this with other filters results in undefined behavior. */
    MPSImageEdgeModeMirrorWithEdge      MPS_ENUM_AVAILABLE_STARTING( macos(10.14.1), ios(12.1), tvos(12.1)),

    /*! Out of bound pixels are filled with a constant value defined by the filter.
     *  NOTE: The only filter that currently supports this mode is @ref MPSNNPad - using this with other filters results in undefined behavior. */
    MPSImageEdgeModeConstant            MPS_ENUM_AVAILABLE_STARTING( macos(10.14.1), ios(12.1), tvos(12.1)),
}
#if defined(DOXYGEN)
    MPSImageEdgeMode
#endif
;

    
/*! @enum       MPSImageFeatureChannelFormat
 *  @memberof   MPSImage
 *  @abstract   Encodes the representation of a single channel within a MPSImage.
 *  @discussion A MPSImage pixel may have many channels in it, sometimes many more than 4, the
 *              limit of what MTLPixelFormats encode. The storage format for a single channel
 *              within a pixel can be given by the MPSImageFeatureChannelFormat. The number
 *              of channels is given by the featureChannels parameter of appropriate MPSImage
 *              APIs. The size of the pixel is size of the channel format multiplied by the
 *              number of feature channels. No padding is allowed, except to round out to a full
 *              byte.
 */
#if defined(DOXYGEN)
typedef enum MPSImageFeatureChannelFormat
#else
typedef NS_ENUM(NSUInteger, MPSImageFeatureChannelFormat)
#endif
{
    /*! No format. This can mean  according to context invalid format or any format.  In the
        latter case, it is an invitation to MPS to pick a format. */
    MPSImageFeatureChannelFormatNone        MPS_ENUM_AVAILABLE_STARTING(macos(10.13), ios(10.0), tvos(10.0)) MPS_SWIFT_NAME(none)  = 0,
    
    /*! uint8_t with value [0,255] encoding [0,1.0] */
    MPSImageFeatureChannelFormatUnorm8      MPS_ENUM_AVAILABLE_STARTING(macos(10.13), ios(10.0), tvos(10.0))   = 1,
    
    /*! uint16_t with value [0,65535] encoding [0,1.0] */
    MPSImageFeatureChannelFormatUnorm16     MPS_ENUM_AVAILABLE_STARTING(macos(10.13), ios(10.0), tvos(10.0))  = 2,
    
    /*! IEEE-754 16-bit floating-point value. "half precision" Representable normal range is +-[2**-14, 65504], 0, Infinity, NaN. 11 bits of precision + exponent. */
    MPSImageFeatureChannelFormatFloat16     MPS_ENUM_AVAILABLE_STARTING(macos(10.13), ios(10.0), tvos(10.0))  = 3,
    
    /*! IEEE-754 32-bit floating-point value.  "single precision" (standard float type in C) 24 bits of precision + exponent */
    MPSImageFeatureChannelFormatFloat32     MPS_ENUM_AVAILABLE_STARTING(macos(10.13), ios(10.0), tvos(10.0))  = 4,
    
    
    /* Always last */
    MPSImageFeatureChannelFormatCount        MPS_ENUM_AVAILABLE_STARTING(macos(10.14), ios(12.0), tvos(12.0))
}
#if defined(DOXYGEN)
    MPSImageFeatureChannelFormat
#endif
;

    
/*! @enum        MPSDataType
 *  @discussion A value to specify a type of data.
 *
 *  @constant   MPSDataTypeFloatBit         A common bit for all floating point data types.  Zero for integer types
 *  @constant   MPSDataTypeNormalizedBit    If set, the value of the shall be interpreted as value / UNORM_TYPE_MAX
 *                                          Normalized values have range [0, 1.0] if unsigned and [-1,1] if signed.
 *                                          SNORM_TYPE_MIN is interpreted as SNORM_TYPE_MIN+1 per standard Metal rules.
 *
 *  @constant   MSPDataTypeFloat32      32-bit floating point (single-precision).
 *  @constant   MSPDataTypeFloat16      16-bit floating point (half-precision).  (IEEE-754-2008 float16 exchange format)
 *  @constant   MPSDataTypeInt8         Signed 8-bit integer.
 *  @constant   MPSDataTypeInt16        Signed 16-bit integer.
 *  @constant   MPSDataTypeUInt8        Unsigned 8-bit integer. Not normalized
 *  @constant   MPSDataTypeUInt16       Unsigned 16-bit integer. Not normalized
 *  @constant   MPSDataTypeUInt32       Unsigned 32-bit integer. Not normalized
 *  @constant   MPSDataTypeUnorm1       Unsigned 1-bit normalized value.
 *  @constant   MPSDataTypeUnorm8       Unsigned 8-bit normalized value.
 */
#if defined(DOXYGEN)
    typedef enum MPSDataType
#else
    typedef NS_ENUM(uint32_t, MPSDataType)
#endif
{
    MPSDataTypeInvalid MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(10.0), tvos(10.0)) MPS_SWIFT_NAME(invalid) = 0,
    
    MPSDataTypeFloatBit MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(10.0), tvos(10.0)) = 0x10000000,
    MPSDataTypeFloat32  MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(10.0), tvos(10.0)) = MPSDataTypeFloatBit | 32,
    MPSDataTypeFloat16  MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0)) = MPSDataTypeFloatBit | 16,
    
    // signed integers
    MPSDataTypeSignedBit MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(10.0), tvos(10.0)) = 0x20000000,
    MPSDataTypeIntBit DEPRECATED_ATTRIBUTE = MPSDataTypeSignedBit,
    MPSDataTypeInt8   MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(10.0), tvos(10.0))   = MPSDataTypeSignedBit | 8,
    MPSDataTypeInt16  MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(10.0), tvos(10.0))   = MPSDataTypeSignedBit | 16,

    // unsigned integers. Range: [0, UTYPE_MAX]
    MPSDataTypeUInt8   MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(10.0), tvos(10.0))   = 8,
    MPSDataTypeUInt16  MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(10.0), tvos(10.0))   = 16,
    MPSDataTypeUInt32  MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(10.0), tvos(10.0))   = 32,

    // unsigned normalized  (see for example Metal's unorm8 and unorm16 pixel formats). Range: [0, 1.0]
    MPSDataTypeNormalizedBit MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))   = 0x40000000,
    MPSDataTypeUnorm1   MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0)) = MPSDataTypeNormalizedBit | 1,
    MPSDataTypeUnorm8   MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0)) = MPSDataTypeNormalizedBit | 8,
}
#if defined(DOXYGEN)
    MPSDataType
#endif
    ;


/*!
 *  @struct     MPSOffset
 *  @memberof   MPSKernel
 *  @abstract   A signed coordinate with x, y and z components
 */
typedef struct
{
    NSInteger x;    /**<    The horizontal component of the offset. Units: pixels   */
    NSInteger y;    /**<    The vertical component of the offset. Units: pixels     */
    NSInteger z;    /**<    The depth component of the offset. Units: pixels        */
}MPSOffset;

/*!
 *  @struct     MPSOrigin
 *  @memberof   MPSKernel
 *  @abstract   A position in an image
 */
typedef struct MPSOrigin
{
    double  x;  /**< The x coordinate of the position       */
    double  y;  /**< The y coordinate of the position       */
    double  z;  /**< The z coordinate of the position       */
}MPSOrigin;

/*!
 *  @struct     MPSSize
 *  @memberof   MPSKernel
 *  @abstract   A size of a region in an image
 */
typedef struct MPSSize
{
    double  width;      /**< The width of the region    */
    double  height;     /**< The height of the region   */
    double  depth;      /**< The depth of the region    */
}MPSSize;

/*!
 *  @struct     MPSRegion
 *  @memberof   MPSKernel
 *  @abstract   A region of an image
 */
typedef struct MPSRegion
{
    MPSOrigin       origin;     /**< The top left corner of the region.  Units: pixels  */
    MPSSize         size;       /**< The size of the region. Units: pixels              */
}MPSRegion;
    
/*!
 *  @struct         MPSScaleTransform
 *  @abstract       Transform matrix for explict control over resampling in MPSImageLanczosScale.
 *  @discussion     The MPSScaleTransform is equivalent to:
 *       @code
 *          (CGAffineTransform) {
 *               .a = scaleX,        .b = 0,
 *               .c = 0,             .d = scaleY,
 *               .tx = translateX,   .ty = translateY
 *           }
 *       @endcode
 *
 *  @memberof       MPSImageLanczosScale
 */
typedef struct MPSScaleTransform
{
    double  scaleX;                         /**< horizontal scaling factor */
    double  scaleY;                         /**< vertical scaling factor */
    double  translateX;                     /**< horizontal translation */
    double  translateY;                     /**< vertical translation */
}MPSScaleTransform;

/*!
 *  @struct     MPSImageCoordinate
 *  @memberof   MPSImage
 *  @abstract   A unsigned coordinate with x, y and channel components
 */
typedef struct MPSImageCoordinate
{
    NSUInteger x;           /**<    The horizontal component of the coordinate. Units: pixels      */
    NSUInteger y;           /**<    The vertical component of the coordinate. Units: pixels        */
    NSUInteger channel;     /**<    The index of the channel or feature channel within the pixel   */
}MPSImageCoordinate;

/*!
 *  @struct     MPSImageRegion
 *  @memberof   MPSImage
 *  @abstract   A rectangular subregion of a MPSImage
 */
typedef struct MPSImageRegion
{
    MPSImageCoordinate offset;      /**<    The position of the top left corner of the subregion */
    MPSImageCoordinate size;        /**<    The size {pixels, pixels, channels} of the subregion */
}MPSImageRegion;

    
/*!
 *  @memberof   MPSKernel
 *  @constant   MPSRectNoClip
 *  @discussion This is a special constant to indicate no clipping is to be done.
 *              The entire image will be used.
 *              This is the default clipping rectangle or the input extent for MPSKernels.
 */
extern const MTLRegion  MPSRectNoClip
    MPS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0));
    
/*! @abstract   A way of extending a NSCoder to enable the setting of MTLDevice for unarchived objects
 *  @discussion When a object is initialized by a NSCoder, it calls -initWithCoder:, which is 
 *              missing the necessary MTLDevice to correctly initialize the MPSKernel, or MPSNNGraph.
 *              If the coder does not conform to MPSDeviceProvider, the system default device
 *              will be used.  If you would like to specify which device to use, subclass the 
 *              NSCoder (NSKeyedUnarchiver, etc.) to conform to MPSDeviceProvider so that 
 *              the device can be gotten from the NSCoder.
 *
 *              See MPSKeyedUnarchiver for one implementation of this protocol. It reads files
 *              prepared with the NSKeyedArchiver and allows you to set the MTLDevice that the
 *              unarchived objects use.
 */
@protocol   MPSDeviceProvider
    /*! @abstract   Return the device to use when making MPSKernel subclasses from the NSCoder */
    -(id <MTLDevice>) mpsMTLDevice;
@end

#ifdef __cplusplus
}
#endif


#endif /* MPSCoreTypes_h */
