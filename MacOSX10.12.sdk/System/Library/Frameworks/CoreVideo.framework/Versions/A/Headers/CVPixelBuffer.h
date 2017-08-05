/*
 *  CVPixelBuffer.h
 *  CoreVideo
 *
 *  Copyright (c) 2004-2015 Apple Inc. All rights reserved.
 *
 */
 
  /*! @header CVPixelBuffer.h
	@copyright 2004-2015 Apple Inc. All rights reserved.
	@availability Mac OS X 10.4 or later, and iOS 4.0 or later
    @discussion CVPixelBuffers are CVImageBuffers that hold the pixels in main memory
		   
*/

#if !defined(__COREVIDEO_CVPIXELBUFFER_H__)
#define __COREVIDEO_CVPIXELBUFFER_H__ 1

#include <TargetConditionals.h>
#include <Availability.h>
#include <AvailabilityMacros.h>

#include <CoreVideo/CVImageBuffer.h>
#include <CoreFoundation/CFArray.h>

#if defined(__cplusplus)
extern "C" {
#endif

/*
CoreVideo pixel format type constants.
CoreVideo does not provide support for all of these formats; this list just defines their names.
*/
#if COREVIDEO_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : OSType
#else
enum
#endif
{
  kCVPixelFormatType_1Monochrome    = 0x00000001, /* 1 bit indexed */
  kCVPixelFormatType_2Indexed       = 0x00000002, /* 2 bit indexed */
  kCVPixelFormatType_4Indexed       = 0x00000004, /* 4 bit indexed */
  kCVPixelFormatType_8Indexed       = 0x00000008, /* 8 bit indexed */
  kCVPixelFormatType_1IndexedGray_WhiteIsZero = 0x00000021, /* 1 bit indexed gray, white is zero */
  kCVPixelFormatType_2IndexedGray_WhiteIsZero = 0x00000022, /* 2 bit indexed gray, white is zero */
  kCVPixelFormatType_4IndexedGray_WhiteIsZero = 0x00000024, /* 4 bit indexed gray, white is zero */
  kCVPixelFormatType_8IndexedGray_WhiteIsZero = 0x00000028, /* 8 bit indexed gray, white is zero */
  kCVPixelFormatType_16BE555        = 0x00000010, /* 16 bit BE RGB 555 */
  kCVPixelFormatType_16LE555        = 'L555',     /* 16 bit LE RGB 555 */
  kCVPixelFormatType_16LE5551       = '5551',     /* 16 bit LE RGB 5551 */
  kCVPixelFormatType_16BE565        = 'B565',     /* 16 bit BE RGB 565 */
  kCVPixelFormatType_16LE565        = 'L565',     /* 16 bit LE RGB 565 */
  kCVPixelFormatType_24RGB          = 0x00000018, /* 24 bit RGB */
  kCVPixelFormatType_24BGR          = '24BG',     /* 24 bit BGR */
  kCVPixelFormatType_32ARGB         = 0x00000020, /* 32 bit ARGB */
  kCVPixelFormatType_32BGRA         = 'BGRA',     /* 32 bit BGRA */
  kCVPixelFormatType_32ABGR         = 'ABGR',     /* 32 bit ABGR */
  kCVPixelFormatType_32RGBA         = 'RGBA',     /* 32 bit RGBA */
  kCVPixelFormatType_64ARGB         = 'b64a',     /* 64 bit ARGB, 16-bit big-endian samples */
  kCVPixelFormatType_48RGB          = 'b48r',     /* 48 bit RGB, 16-bit big-endian samples */
  kCVPixelFormatType_32AlphaGray    = 'b32a',     /* 32 bit AlphaGray, 16-bit big-endian samples, black is zero */
  kCVPixelFormatType_16Gray         = 'b16g',     /* 16 bit Grayscale, 16-bit big-endian samples, black is zero */
  kCVPixelFormatType_30RGB          = 'R10k',     /* 30 bit RGB, 10-bit big-endian samples, 2 unused padding bits (at least significant end). */
  kCVPixelFormatType_422YpCbCr8     = '2vuy',     /* Component Y'CbCr 8-bit 4:2:2, ordered Cb Y'0 Cr Y'1 */
  kCVPixelFormatType_4444YpCbCrA8   = 'v408',     /* Component Y'CbCrA 8-bit 4:4:4:4, ordered Cb Y' Cr A */
  kCVPixelFormatType_4444YpCbCrA8R  = 'r408',     /* Component Y'CbCrA 8-bit 4:4:4:4, rendering format. full range alpha, zero biased YUV, ordered A Y' Cb Cr */
  kCVPixelFormatType_4444AYpCbCr8   = 'y408',     /* Component Y'CbCrA 8-bit 4:4:4:4, ordered A Y' Cb Cr, full range alpha, video range Y'CbCr. */
  kCVPixelFormatType_4444AYpCbCr16  = 'y416',     /* Component Y'CbCrA 16-bit 4:4:4:4, ordered A Y' Cb Cr, full range alpha, video range Y'CbCr, 16-bit little-endian samples. */
  kCVPixelFormatType_444YpCbCr8     = 'v308',     /* Component Y'CbCr 8-bit 4:4:4 */
  kCVPixelFormatType_422YpCbCr16    = 'v216',     /* Component Y'CbCr 10,12,14,16-bit 4:2:2 */
  kCVPixelFormatType_422YpCbCr10    = 'v210',     /* Component Y'CbCr 10-bit 4:2:2 */
  kCVPixelFormatType_444YpCbCr10    = 'v410',     /* Component Y'CbCr 10-bit 4:4:4 */
  kCVPixelFormatType_420YpCbCr8Planar = 'y420',   /* Planar Component Y'CbCr 8-bit 4:2:0.  baseAddr points to a big-endian CVPlanarPixelBufferInfo_YCbCrPlanar struct */
  kCVPixelFormatType_420YpCbCr8PlanarFullRange    = 'f420',   /* Planar Component Y'CbCr 8-bit 4:2:0, full range.  baseAddr points to a big-endian CVPlanarPixelBufferInfo_YCbCrPlanar struct */
  kCVPixelFormatType_422YpCbCr_4A_8BiPlanar = 'a2vy', /* First plane: Video-range Component Y'CbCr 8-bit 4:2:2, ordered Cb Y'0 Cr Y'1; second plane: alpha 8-bit 0-255 */
  kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange = '420v', /* Bi-Planar Component Y'CbCr 8-bit 4:2:0, video-range (luma=[16,235] chroma=[16,240]).  baseAddr points to a big-endian CVPlanarPixelBufferInfo_YCbCrBiPlanar struct */
  kCVPixelFormatType_420YpCbCr8BiPlanarFullRange  = '420f', /* Bi-Planar Component Y'CbCr 8-bit 4:2:0, full-range (luma=[0,255] chroma=[1,255]).  baseAddr points to a big-endian CVPlanarPixelBufferInfo_YCbCrBiPlanar struct */ 
  kCVPixelFormatType_422YpCbCr8_yuvs = 'yuvs',     /* Component Y'CbCr 8-bit 4:2:2, ordered Y'0 Cb Y'1 Cr */
  kCVPixelFormatType_422YpCbCr8FullRange = 'yuvf', /* Component Y'CbCr 8-bit 4:2:2, full range, ordered Y'0 Cb Y'1 Cr */
  kCVPixelFormatType_OneComponent8  = 'L008',     /* 8 bit one component, black is zero */
  kCVPixelFormatType_TwoComponent8  = '2C08',     /* 8 bit two component, black is zero */
  kCVPixelFormatType_30RGBLEPackedWideGamut = 'w30r', /* little-endian RGB101010, 2 MSB are zero, wide-gamut (384-895) */
  kCVPixelFormatType_OneComponent16Half  = 'L00h',     /* 16 bit one component IEEE half-precision float, 16-bit little-endian samples */
  kCVPixelFormatType_OneComponent32Float = 'L00f',     /* 32 bit one component IEEE float, 32-bit little-endian samples */
  kCVPixelFormatType_TwoComponent16Half  = '2C0h',     /* 16 bit two component IEEE half-precision float, 16-bit little-endian samples */
  kCVPixelFormatType_TwoComponent32Float = '2C0f',     /* 32 bit two component IEEE float, 32-bit little-endian samples */
  kCVPixelFormatType_64RGBAHalf          = 'RGhA',     /* 64 bit RGBA IEEE half-precision float, 16-bit little-endian samples */
  kCVPixelFormatType_128RGBAFloat        = 'RGfA',     /* 128 bit RGBA IEEE float, 32-bit little-endian samples */
  kCVPixelFormatType_14Bayer_GRBG        = 'grb4',     /* Bayer 14-bit Little-Endian, packed in 16-bits, ordered G R G R... alternating with B G B G... */
  kCVPixelFormatType_14Bayer_RGGB        = 'rgg4',     /* Bayer 14-bit Little-Endian, packed in 16-bits, ordered R G R G... alternating with G B G B... */
  kCVPixelFormatType_14Bayer_BGGR        = 'bgg4',     /* Bayer 14-bit Little-Endian, packed in 16-bits, ordered B G B G... alternating with G R G R... */
  kCVPixelFormatType_14Bayer_GBRG        = 'gbr4',     /* Bayer 14-bit Little-Endian, packed in 16-bits, ordered G B G B... alternating with R G R G... */
};

	
/*!
	@enum Pixel Buffer Locking Flags
	@discussion Flags to pass to CVPixelBufferLockBaseAddress() / CVPixelBufferUnlockBaseAddress()
	@constant kCVPixelBufferLock_ReadOnly
		If you are not going to modify the data while you hold the lock, you should set this flag
		to avoid potentially invalidating any existing caches of the buffer contents.  This flag
		should be passed both to the lock and unlock functions.  Non-symmetrical usage of this
		flag will result in undefined behavior.
*/
typedef CF_OPTIONS(CVOptionFlags, CVPixelBufferLockFlags)
{
	kCVPixelBufferLock_ReadOnly = 0x00000001,
};

/*
Planar pixel buffers have the following descriptor at their base address.  
Clients should generally use CVPixelBufferGetBaseAddressOfPlane, 
CVPixelBufferGetBytesPerRowOfPlane, etc. instead of accessing it directly.
*/
struct CVPlanarComponentInfo {
  int32_t             offset;    /* offset from main base address to base address of this plane, big-endian */
  uint32_t            rowBytes;  /* bytes per row of this plane, big-endian */
};
typedef struct CVPlanarComponentInfo      CVPlanarComponentInfo;
struct CVPlanarPixelBufferInfo {
  CVPlanarComponentInfo  componentInfo[1];
};
typedef struct CVPlanarPixelBufferInfo         CVPlanarPixelBufferInfo;
struct CVPlanarPixelBufferInfo_YCbCrPlanar {
  CVPlanarComponentInfo  componentInfoY;
  CVPlanarComponentInfo  componentInfoCb;
  CVPlanarComponentInfo  componentInfoCr;
};
typedef struct CVPlanarPixelBufferInfo_YCbCrPlanar   CVPlanarPixelBufferInfo_YCbCrPlanar;
struct CVPlanarPixelBufferInfo_YCbCrBiPlanar {
  CVPlanarComponentInfo  componentInfoY;
  CVPlanarComponentInfo  componentInfoCbCr;
};
typedef struct CVPlanarPixelBufferInfo_YCbCrBiPlanar   CVPlanarPixelBufferInfo_YCbCrBiPlanar;

#pragma mark BufferAttributeKeys
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferPixelFormatTypeKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);		    // A single CFNumber or a CFArray of CFNumbers (OSTypes)
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferMemoryAllocatorKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);		    // CFAllocatorRef
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferWidthKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);			    // CFNumber
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferHeightKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);			    // CFNumber
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferExtendedPixelsLeftKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);	    // CFNumber
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferExtendedPixelsTopKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);		    // CFNumber
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferExtendedPixelsRightKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);	    // CFNumber
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferExtendedPixelsBottomKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);	    // CFNumber
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferBytesPerRowAlignmentKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);	    // CFNumber
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferCGBitmapContextCompatibilityKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);  // CFBoolean
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferCGImageCompatibilityKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);	    // CFBoolean
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferOpenGLCompatibilityKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);	    // CFBoolean
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferPlaneAlignmentKey __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_4_0);		    // CFNumber
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferIOSurfacePropertiesKey __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_4_0);     // CFDictionary; presence requests buffer allocation via IOSurface
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferOpenGLESCompatibilityKey __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0);	    // CFBoolean
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferMetalCompatibilityKey __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_8_0);	    // CFBoolean
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferOpenGLTextureCacheCompatibilityKey __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_NA);
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferOpenGLESTextureCacheCompatibilityKey __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_9_0);    

/*!
    @typedef	CVPixelBufferRef
    @abstract   Based on the image buffer type. The pixel buffer implements the memory storage for an image buffer.

*/
typedef CVImageBufferRef CVPixelBufferRef;

CV_EXPORT CFTypeID CVPixelBufferGetTypeID(void) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVPixelBufferRetain
    @abstract   Retains a CVPixelBuffer object
    @discussion Equivalent to CFRetain, but NULL safe
    @param      buffer A CVPixelBuffer object that you want to retain.
    @result     A CVPixelBuffer object that is the same as the passed in buffer.
*/
CV_EXPORT CVPixelBufferRef CV_NULLABLE CVPixelBufferRetain( CVPixelBufferRef CV_NULLABLE texture ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVPixelBufferRelease
    @abstract   Releases a CVPixelBuffer object
    @discussion Equivalent to CFRelease, but NULL safe
    @param      buffer A CVPixelBuffer object that you want to release.
*/
CV_EXPORT void CVPixelBufferRelease( CV_RELEASES_ARGUMENT CVPixelBufferRef CV_NULLABLE texture ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVPixelBufferCreateResolvedAttributesDictionary
    @abstract   Takes a CFArray of CFDictionary objects describing various pixel buffer attributes and tries to resolve them into a
                single dictionary.
    @discussion This is useful when you need to resolve multiple requirements between different potential clients of a buffer.
    @param      attributes CFArray of CFDictionaries containing kCVPixelBuffer key/value pairs.
    @param      resolvedDictionaryOut The resulting dictionary will be placed here.
    @result     Return value that may be useful in discovering why resolution failed.
*/
CV_EXPORT CVReturn CVPixelBufferCreateResolvedAttributesDictionary(
    CFAllocatorRef CV_NULLABLE allocator,
    CFArrayRef CV_NULLABLE attributes,
    CV_RETURNS_RETAINED_PARAMETER CFDictionaryRef CV_NULLABLE * CV_NONNULL resolvedDictionaryOut) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);


/*!
    @function   CVPixelBufferCreate
    @abstract   Call to create a single PixelBuffer for a given size and pixelFormatType.
    @discussion Creates a single PixelBuffer for a given size and pixelFormatType. It allocates the necessary memory based on the pixel dimensions, pixelFormatType and extended pixels described in the pixelBufferAttributes. Not all parameters of the pixelBufferAttributes will be used here.
    @param      width   Width of the PixelBuffer in pixels.
    @param      height  Height of the PixelBuffer in pixels.
    @param	pixelFormatType		Pixel format indentified by its respective OSType.
    @param	pixelBufferAttributes      A dictionary with additional attributes for a pixel buffer. This parameter is optional. See BufferAttributeKeys for more details.
    @param      pixelBufferOut          The new pixel buffer will be returned here
    @result	returns kCVReturnSuccess on success.
*/    
CV_EXPORT CVReturn CVPixelBufferCreate(
    CFAllocatorRef CV_NULLABLE allocator,
    size_t width,
    size_t height,
    OSType pixelFormatType,
    CFDictionaryRef CV_NULLABLE pixelBufferAttributes,
    CV_RETURNS_RETAINED_PARAMETER CVPixelBufferRef CV_NULLABLE * CV_NONNULL pixelBufferOut) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

typedef void (*CVPixelBufferReleaseBytesCallback)( void * CV_NULLABLE releaseRefCon, const void * CV_NULLABLE baseAddress );

/*!
    @function   CVPixelBufferCreateWithBytes
    @abstract   Call to create a single PixelBuffer for a given size and pixelFormatType based on a passed in piece of memory.
    @discussion Creates a single PixelBuffer for a given size and pixelFormatType. Not all parameters of the pixelBufferAttributes will be used here. It requires a release callback function that will be called, when the PixelBuffer gets destroyed so that the owner of the pixels can free the memory.
    @param      width   Width of the PixelBuffer in pixels
    @param      height  Height of the PixelBuffer in pixels
    @param      pixelFormatType		Pixel format indentified by its respective OSType.
    @param      baseAddress		Address of the memory storing the pixels.
    @param      bytesPerRow		Row bytes of the pixel storage memory.
    @param      releaseCallback         CVPixelBufferReleaseBytePointerCallback function that gets called when the PixelBuffer gets destroyed.
    @param      releaseRefCon           User data identifying the PixelBuffer for the release callback.
    @param      pixelBufferAttributes      A dictionary with additional attributes for a a pixel buffer. This parameter is optional. See PixelBufferAttributes for more details.
    @param      pixelBufferOut          The new pixel buffer will be returned here
    @result	returns kCVReturnSuccess on success.
*/
CV_EXPORT CVReturn CVPixelBufferCreateWithBytes(
    CFAllocatorRef CV_NULLABLE allocator,
    size_t width,
    size_t height,
    OSType pixelFormatType,
    void * CV_NONNULL baseAddress,
    size_t bytesPerRow,
    CVPixelBufferReleaseBytesCallback CV_NULLABLE releaseCallback,
    void * CV_NULLABLE releaseRefCon,
    CFDictionaryRef CV_NULLABLE pixelBufferAttributes,
    CV_RETURNS_RETAINED_PARAMETER CVPixelBufferRef CV_NULLABLE * CV_NONNULL pixelBufferOut) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

typedef void (*CVPixelBufferReleasePlanarBytesCallback)( void * CV_NULLABLE releaseRefCon, const void * CV_NULLABLE dataPtr, size_t dataSize, size_t numberOfPlanes, const void * CV_NULLABLE planeAddresses[] );

/*!
    @function   CVPixelBufferCreateWithPlanarBytes
    @abstract   Call to create a single PixelBuffer in planar format for a given size and pixelFormatType based on a passed in piece of memory.
    @discussion Creates a single PixelBuffer for a given size and pixelFormatType. Not all parameters of the pixelBufferAttributes will be used here. It requires a release callback function that will be called, when the PixelBuffer gets destroyed so that the owner of the pixels can free the memory.
    @param      width			Width of the PixelBuffer in pixels
    @param      height			Height of the PixelBuffer in pixels
    @param      pixelFormatType		Pixel format indentified by its respective OSType.
    @param	dataPtr			Pass a pointer to a plane descriptor block, or NULL.
    @param	dataSize		pass size if planes are contiguous, NULL if not.
    @param	numberOfPlanes		Number of planes.
    @param	planeBaseAddress	Array of base addresses for the planes.
    @param	planeWidth		Array of plane widths.
    @param	planeHeight		Array of plane heights.
    @param	planeBytesPerRow	Array of plane bytesPerRow values.
    @param	releaseCallback		CVPixelBufferReleaseBytePointerCallback function that gets called when the PixelBuffer gets destroyed.
    @param	releaseRefCon		User data identifying the PixelBuffer for the release callback.
    @param	pixelBufferAttributes      A dictionary with additional attributes for a a pixel buffer. This parameter is optional. See PixelBufferAttributes for more details.
    @param      pixelBufferOut          The new pixel buffer will be returned here
    @result	returns kCVReturnSuccess on success.
*/
CV_EXPORT CVReturn CVPixelBufferCreateWithPlanarBytes(
    CFAllocatorRef CV_NULLABLE allocator,
    size_t width,
    size_t height,
    OSType pixelFormatType,
    void * CV_NULLABLE dataPtr, // pass a pointer to a plane descriptor block, or NULL
    size_t dataSize, // pass size if planes are contiguous, NULL if not
    size_t numberOfPlanes,
    void * CV_NULLABLE planeBaseAddress[],
    size_t planeWidth[],
    size_t planeHeight[],
    size_t planeBytesPerRow[],
    CVPixelBufferReleasePlanarBytesCallback CV_NULLABLE releaseCallback,
    void * CV_NULLABLE releaseRefCon,
    CFDictionaryRef CV_NULLABLE pixelBufferAttributes,
    CV_RETURNS_RETAINED_PARAMETER CVPixelBufferRef CV_NULLABLE * CV_NONNULL pixelBufferOut) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);


/*!
	@function   CVPixelBufferLockBaseAddress
	@abstract   Description Locks the BaseAddress of the PixelBuffer to ensure that the memory is accessible.
	@discussion This API ensures that the CVPixelBuffer is accessible in system memory. This should only be called if the base address is going to be used and the pixel data will be accessed by the CPU.
	@param      pixelBuffer Target PixelBuffer.
	@param      lockFlags See CVPixelBufferLockFlags.
	@result     kCVReturnSuccess if the lock succeeded, or error code on failure
*/
CV_EXPORT CVReturn CVPixelBufferLockBaseAddress( CVPixelBufferRef CV_NONNULL pixelBuffer, CVPixelBufferLockFlags lockFlags ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
	@function   CVPixelBufferUnlockBaseAddress
	@abstract   Description Unlocks the BaseAddress of the PixelBuffer.
	@param      pixelBuffer Target PixelBuffer.
	@param      unlockFlags See CVPixelBufferLockFlags.
	@result     kCVReturnSuccess if the unlock succeeded, or error code on failure
*/
CV_EXPORT CVReturn CVPixelBufferUnlockBaseAddress( CVPixelBufferRef CV_NONNULL pixelBuffer, CVPixelBufferLockFlags unlockFlags ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVPixelBufferGetWidth
    @abstract   Returns the width of the PixelBuffer.
    @param      pixelBuffer Target PixelBuffer.
    @result     Width in pixels.
*/
CV_EXPORT size_t CVPixelBufferGetWidth( CVPixelBufferRef CV_NONNULL pixelBuffer ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVPixelBufferGetHeight
    @abstract   Returns the height of the PixelBuffer.
    @param      pixelBuffer Target PixelBuffer.
    @result     Height in pixels.
*/
CV_EXPORT size_t CVPixelBufferGetHeight( CVPixelBufferRef CV_NONNULL pixelBuffer ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVPixelBufferGetPixelFormatType
    @abstract   Returns the PixelFormatType of the PixelBuffer.
    @param      pixelBuffer Target PixelBuffer.
    @result     OSType identifying the pixel format by its type.
*/
CV_EXPORT OSType CVPixelBufferGetPixelFormatType( CVPixelBufferRef CV_NONNULL pixelBuffer ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVPixelBufferGetBaseAddress
    @abstract   Returns the base address of the PixelBuffer.
    @discussion Retrieving the base address for a PixelBuffer requires that the buffer base address be locked
                via a successful call to CVPixelBufferLockBaseAddress.
    @param      pixelBuffer Target PixelBuffer.
    @result     Base address of the pixels.
		For chunky buffers, this will return a pointer to the pixel at 0,0 in the buffer
		For planar buffers this will return a pointer to a PlanarComponentInfo struct (defined in QuickTime).
*/
CV_EXPORT void * CV_NULLABLE CVPixelBufferGetBaseAddress( CVPixelBufferRef CV_NONNULL pixelBuffer ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVPixelBufferGetBytesPerRow
    @abstract   Returns the rowBytes of the PixelBuffer.
    @param      pixelBuffer Target PixelBuffer.
    @result     Bytes per row of the image data.   For planar buffers this will return a rowBytes value such that bytesPerRow * height
                will cover the entire image including all planes.
*/
CV_EXPORT size_t CVPixelBufferGetBytesPerRow( CVPixelBufferRef CV_NONNULL pixelBuffer ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVPixelBufferGetDataSize
    @abstract   Returns the data size for contigous planes of the PixelBuffer.
    @param      pixelBuffer Target PixelBuffer.
    @result     Data size used in CVPixelBufferCreateWithPlanarBytes.
*/
CV_EXPORT size_t CVPixelBufferGetDataSize( CVPixelBufferRef CV_NONNULL pixelBuffer ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVPixelBufferIsPlanar
    @abstract   Returns if the PixelBuffer is planar.
    @param      pixelBuffer Target PixelBuffer.
    @result     True if the PixelBuffer was created using CVPixelBufferCreateWithPlanarBytes.
*/
CV_EXPORT Boolean CVPixelBufferIsPlanar( CVPixelBufferRef CV_NONNULL pixelBuffer ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVPixelBufferGetPlaneCount
    @abstract   Returns number of planes of the PixelBuffer.
    @param      pixelBuffer Target PixelBuffer.
    @result     Number of planes.  Returns 0 for non-planar CVPixelBufferRefs.
*/
CV_EXPORT size_t CVPixelBufferGetPlaneCount( CVPixelBufferRef CV_NONNULL pixelBuffer ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVPixelBufferGetWidthOfPlane
    @abstract   Returns the width of the plane at planeIndex in the PixelBuffer.
    @discussion On OSX 10.10 and earlier, or iOS 8 and earlier, calling this 
                function with a non-planar buffer will have undefined behavior.
    @param      pixelBuffer Target PixelBuffer.
    @param      planeIndex  Identifying the plane.
    @result     Width in pixels, or 0 for non-planar CVPixelBufferRefs.
*/
CV_EXPORT size_t CVPixelBufferGetWidthOfPlane( CVPixelBufferRef CV_NONNULL pixelBuffer, size_t planeIndex ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVPixelBufferGetHeightOfPlane
    @abstract   Returns the height of the plane at planeIndex in the PixelBuffer.
    @discussion On OSX 10.10 and earlier, or iOS 8 and earlier, calling this
                function with a non-planar buffer will have undefined behavior.
    @param      pixelBuffer Target PixelBuffer.
    @param      planeIndex  Identifying the plane.
    @result     Height in pixels, or 0 for non-planar CVPixelBufferRefs.
*/
CV_EXPORT size_t CVPixelBufferGetHeightOfPlane( CVPixelBufferRef CV_NONNULL pixelBuffer, size_t planeIndex ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVPixelBufferGetBaseAddressOfPlane
    @abstract   Returns the base address of the plane at planeIndex in the PixelBuffer.
    @discussion Retrieving the base address for a PixelBuffer requires that the buffer base address be locked
                via a successful call to CVPixelBufferLockBaseAddress. On OSX 10.10 and earlier, or iOS 8 and
                earlier, calling this function with a non-planar buffer will have undefined behavior.
    @param      pixelBuffer Target PixelBuffer.
    @param      planeIndex  Identifying the plane.
    @result     Base address of the plane, or NULL for non-planar CVPixelBufferRefs.
*/
CV_EXPORT void * CV_NULLABLE CVPixelBufferGetBaseAddressOfPlane( CVPixelBufferRef CV_NONNULL pixelBuffer, size_t planeIndex ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVPixelBufferGetBytesPerRowOfPlane
    @abstract   Returns the row bytes of the plane at planeIndex in the PixelBuffer.
    @discussion On OSX 10.10 and earlier, or iOS 8 and earlier, calling this
                function with a non-planar buffer will have undefined behavior.
    @param      pixelBuffer Target PixelBuffer.
    @param      planeIndex  Identifying the plane.
    @result     Row bytes of the plane, or NULL for non-planar CVPixelBufferRefs.
*/
CV_EXPORT size_t CVPixelBufferGetBytesPerRowOfPlane( CVPixelBufferRef CV_NONNULL pixelBuffer, size_t planeIndex ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVPixelBufferGetExtendedPixels
    @abstract   Returns the size of extended pixels of the PixelBuffer.
    @discussion On OSX 10.10 and earlier, or iOS 8 and earlier, calling this
                function with a non-planar buffer will have undefined behavior.
    @param      pixelBuffer Target PixelBuffer.
    @param      extraColumnsOnLeft Returns the pixel row padding to the left.  May be NULL.
    @param      extraRowsOnTop Returns the pixel row padding to the top.  May be NULL. 
    @param      extraColumnsOnRight Returns the pixel row padding to the right. May be NULL.
    @param      extraRowsOnBottom Returns the pixel row padding to the bottom. May be NULL.
*/
CV_EXPORT void CVPixelBufferGetExtendedPixels(
						  CVPixelBufferRef CV_NONNULL pixelBuffer,
						  size_t * CV_NULLABLE extraColumnsOnLeft,
						  size_t * CV_NULLABLE extraColumnsOnRight,
						  size_t * CV_NULLABLE extraRowsOnTop,
						  size_t * CV_NULLABLE extraRowsOnBottom ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVPixelBufferFillExtendedPixels
    @abstract   Fills the extended pixels of the PixelBuffer.   This function replicates edge pixels to fill the entire extended region of the image.
    @param      pixelBuffer Target PixelBuffer.
*/
CV_EXPORT CVReturn CVPixelBufferFillExtendedPixels( CVPixelBufferRef CV_NONNULL pixelBuffer ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);


#if defined(__cplusplus)
}
#endif

#if (COREVIDEO_SUPPORTS_IOSURFACE && ! TARGET_OS_IPHONE && ! TARGET_OS_EMBEDDED)
#include <CoreVideo/CVPixelBufferIOSurface.h>
#endif

#endif
