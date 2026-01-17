/* CoreGraphics - CGBitmapContext.h
   Copyright (c) 2000-2025 Apple Inc.
   All rights reserved. */

#ifndef CGBITMAPCONTEXT_H_
#define CGBITMAPCONTEXT_H_

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGContext.h>
#include <CoreGraphics/CGRenderingBufferProvider.h>
#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFAvailability.h>
#include <stdint.h>

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

/* The callback for releasing the data supplied to
   `CGBitmapContextCreateWithData'. */

typedef void (*CGBitmapContextReleaseDataCallback)(void * __nullable releaseInfo,
    void * __nullable data);

/* Create a bitmap context. The context draws into a bitmap which is `width'
   pixels wide and `height' pixels high. The number of components for each
   pixel is specified by `space', which may also specify a destination color
   profile. Note that the only legal case when `space' can be NULL is when
   alpha is specified as kCGImageAlphaOnly. The number of bits for each
   component of a pixel is specified by `bitsPerComponent'. The number of bytes
   per pixel is equal to `(bitsPerComponent * number of components + 7)/8'.
   Each row of the bitmap consists of `bytesPerRow' bytes, which must be at
   least `width * bytes per pixel' bytes; in addition, `bytesPerRow' must be
   an integer multiple of the number of bytes per pixel. `data', if non-NULL,
   points to a block of memory at least `bytesPerRow * height' bytes. If `data'
   is NULL, the context will allocate the data itself; this data will be freed
   when the context is deallocated. `bitmapInfo' specifies whether the bitmap
   should contain an alpha channel and how it's to be generated, along with
   whether the components are floating-point or integer. If `releaseCallback' is
   non-NULL, it is called when the context is freed with `releaseInfo' and
   `data' as arguments. */

CG_EXTERN CGContextRef __nullable CGBitmapContextCreateWithData(
    void * __nullable data, size_t width, size_t height, size_t bitsPerComponent,
    size_t bytesPerRow, CGColorSpaceRef __nullable space, CGBitmapInfo bitmapInfo,
    CGBitmapContextReleaseDataCallback __nullable releaseCallback,
    void * __nullable releaseInfo)
    API_AVAILABLE(macos(10.6), ios(4.0));

#ifdef __swift__
API_DEPRECATED("update space parameter to CGColorSpace?, bitmapInfo parameter to CGBitmapInfo", macos(10.6, API_TO_BE_DEPRECATED), ios(4.0, API_TO_BE_DEPRECATED))
CG_INLINE CGContextRef __nullable __CGBitmapContextCreateWithData(
    void * __nullable data, size_t width, size_t height, size_t bitsPerComponent,
    size_t bytesPerRow, CGColorSpaceRef cg_nullable space, uint32_t bitmapInfo,
    CGBitmapContextReleaseDataCallback __nullable releaseCallback,
    void * __nullable releaseInfo) {
    return CGBitmapContextCreateWithData(data, width, height, bitsPerComponent, bytesPerRow, space, bitmapInfo, releaseCallback, releaseInfo);
}
#endif

/* Create a bitmap context. The context draws into a bitmap which is `width'
   pixels wide and `height' pixels high. The number of components for each
   pixel is specified by `space', which may also specify a destination color
   profile.  Note that the only legal case when `space' can be NULL is when
   alpha is specified as kCGImageAlphaOnly.The number of bits for each component
   of a pixel is specified by `bitsPerComponent'. The number of bytes per pixel
   is equal to `(bitsPerComponent * number of components + 7)/8'. Each row of
   the bitmap consists of `bytesPerRow' bytes, which must be at least
   `width * bytes per pixel' bytes; in addition, `bytesPerRow' must be an
   integer multiple of the number of bytes per pixel. `data', if non-NULL,
   points to a block of memory at least `bytesPerRow * height' bytes.
   If `data' is NULL, the data for context is allocated automatically and freed
   when the context is deallocated. `bitmapInfo' specifies whether the bitmap
   should contain an alpha channel and how it's to be generated, along with
   whether the components are floating-point or integer. */

CG_EXTERN CGContextRef __nullable CGBitmapContextCreate(void * __nullable data,
    size_t width, size_t height, size_t bitsPerComponent, size_t bytesPerRow,
    CGColorSpaceRef __nullable space, CGBitmapInfo bitmapInfo)
    API_AVAILABLE(macos(10.0), ios(2.0));

#ifdef __swift__
API_DEPRECATED("update space parameter to CGColorSpace?, bitmapInfo parameter to CGBitmapInfo", macos(10.0, API_TO_BE_DEPRECATED), ios(2.0, API_TO_BE_DEPRECATED))
CG_INLINE CGContextRef __nullable __CGBitmapContextCreate(void * __nullable data,
    size_t width, size_t height, size_t bitsPerComponent, size_t bytesPerRow,
    CGColorSpaceRef cg_nullable space, uint32_t bitmapInfo) {
    return CGBitmapContextCreate(data, width, height, bitsPerComponent, bytesPerRow, space, bitmapInfo);
}
#endif

/* Bitmap Context typedefs */
 
typedef CF_OPTIONS (uint32_t, CGColorModel) {
    kCGColorModelNoColorant               = 0 << 0,
    kCGColorModelGray                     = 1 << 0,
    kCGColorModelRGB CF_SWIFT_NAME(rgb)   = 1 << 1,
    kCGColorModelCMYK CF_SWIFT_NAME(cmyk) = 1 << 2,
    kCGColorModelLab                      = 1 << 3,
    kCGColorModelDeviceN                  = 1 << 4
};

typedef CF_ENUM(uint32_t, CGComponent) {
    kCGComponentUnknown      = 0,
    kCGComponentInteger8Bit  = 1,
    kCGComponentInteger10Bit = 6,
    kCGComponentInteger16Bit = 2,
    kCGComponentInteger32Bit = 3,
    kCGComponentFloat16Bit   = 5,
    kCGComponentFloat32Bit   = 4
};

typedef struct {
    CGComponent  deepestImageComponent;  /* deepest image component */
    CGColorModel contentColorModels;     /* sum of all color models drawn */
    bool         hasWideGamut;           /* there is content in wide gamut color space */
    bool         hasTransparency;        /* there is transparent content */
    float        largestContentHeadroom;
} CGContentInfo;

typedef CF_ENUM (uint32_t, CGBitmapLayout) {
    kCGBitmapLayoutAlphaOnly CF_SWIFT_NAME(alphaOnly),
    kCGBitmapLayoutGray      CF_SWIFT_NAME(gray),
    kCGBitmapLayoutGrayAlpha CF_SWIFT_NAME(grayAlpha),
    kCGBitmapLayoutRGBA      CF_SWIFT_NAME(rgba),
    kCGBitmapLayoutARGB      CF_SWIFT_NAME(argb),
    kCGBitmapLayoutRGBX      CF_SWIFT_NAME(rgbx), // alpha skipped
    kCGBitmapLayoutXRGB      CF_SWIFT_NAME(xrgb), // alpha skipped; 16-bit float excluded
    kCGBitmapLayoutBGRA      CF_SWIFT_NAME(bgra), // 8-bit only
    kCGBitmapLayoutBGRX      CF_SWIFT_NAME(bgrx), // alpha skipped; 8-bit only
    kCGBitmapLayoutABGR      CF_SWIFT_NAME(abgr), // 8-bit only
    kCGBitmapLayoutXBGR      CF_SWIFT_NAME(xbgr), // alpha skipped; 8-bit only
    kCGBitmapLayoutCMYK      CF_SWIFT_NAME(cmyk)
};

typedef struct {
    const size_t             width;
    const size_t             height;
    size_t                   bytesPerPixel;
    size_t                   alignedBytesPerRow; /* Rounded up to an appropriate value for bitmap data */
    CGComponent              component;
    CGBitmapLayout           layout;
    CGImagePixelFormatInfo   format;
    CGColorSpaceRef          colorSpace;
    bool                     hasPremultipliedAlpha;
    CFByteOrder              byteOrder;
    float                    edrTargetHeadroom;
} CGBitmapParameters CF_REFINED_FOR_SWIFT;

/* CGBitmapContextCreateAdaptive creates a bitmap context which is designed to choose
 * optimal bit depth, color space and EDR target headroom based on the drawn content.
 * Client has an option to override the calculated settings in 'onResolve' callback,
 * however the image creation from the context will fail if the selected options
 * are not legal options for creating a CG bitmap content.
 * The 'onResolve' callback takes a pointer to CGBitmapParameters so the client can modify CGBitmapParameters.
 * The client returns true from 'onResolve' if CGBitmapParameters object is accepted as is, or false if it's modified.
 * If 'onResolve' is NULL, system will determine CGBitmapParameters based on the content drawn to the context.
 * If 'onAllocate' is NULL, system will allocate memory based on chosen CGBitmapParameters.
 * If 'onFree' is NULL, the allocated memory will be released using C 'free' when the context is released.
 * The 'onError' callback gives the client an option to receive a CFErrorRef describing a reason of failure,
 * should the creation of the bitmap failed.
 */

CG_EXTERN CGContextRef __nullable
CGBitmapContextCreateAdaptive(
    size_t width, size_t height,
    CFDictionaryRef                           __nullable auxiliaryInfo,
    bool                                    (^__nullable onResolve)(const CGContentInfo* __nonnull, CGBitmapParameters* __nonnull),
    CGRenderingBufferProviderRef __nullable (^__nullable onAllocate)(const CGContentInfo* __nonnull, const CGBitmapParameters* __nonnull),
    void                                    (^__nullable onFree)(CGRenderingBufferProviderRef __nonnull, const CGContentInfo* __nonnull, const CGBitmapParameters* __nonnull),
    void                                    (^__nullable onError)(CFErrorRef __nonnull, const CGContentInfo* __nonnull, const CGBitmapParameters* __nonnull))
    CF_REFINED_FOR_SWIFT
    API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

/* kCGAdaptiveMaximumBitDepth passed in auxiliaryInfo provides a hint about maximum bit depth of the
 * adaptive context which should be considered by the system. The value should be a CFNumberRef of
 * kCFNumberIntType created from CGComponent enum type.
 * Currently kCGAdaptiveMaximumBitDepth is the only valid key to be used in auxiliaryInfo.
 */

CG_EXTERN const CFStringRef kCGAdaptiveMaximumBitDepth CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(10.13), ios(11.0));

/* Return the data associated with the bitmap context `context', or NULL if
   `context' is not a bitmap context. */

CG_EXTERN void * __nullable CGBitmapContextGetData(CGContextRef cg_nullable context)
    API_AVAILABLE(macos(10.2), ios(2.0));

/* Return the width of the bitmap context `context', or 0 if `context' is
   not a bitmap context. */

CG_EXTERN size_t CGBitmapContextGetWidth(CGContextRef cg_nullable context)
    API_AVAILABLE(macos(10.2), ios(2.0));

/* Return the height of the bitmap context `context', or 0 if `context' is
   not a bitmap context. */

CG_EXTERN size_t CGBitmapContextGetHeight(CGContextRef cg_nullable context)
    API_AVAILABLE(macos(10.2), ios(2.0));

/* Return the bits per component of the bitmap context `context', or 0 if
   `context' is not a bitmap context. */

CG_EXTERN size_t CGBitmapContextGetBitsPerComponent(CGContextRef cg_nullable context)
    API_AVAILABLE(macos(10.2), ios(2.0));

/* Return the bits per pixel of the bitmap context `context', or 0 if
   `context' is not a bitmap context. */

CG_EXTERN size_t CGBitmapContextGetBitsPerPixel(CGContextRef cg_nullable context)
    API_AVAILABLE(macos(10.2), ios(2.0));

/* Return the bytes per row of the bitmap context `context', or 0 if
   `context' is not a bitmap context. */

CG_EXTERN size_t CGBitmapContextGetBytesPerRow(CGContextRef cg_nullable context)
    API_AVAILABLE(macos(10.2), ios(2.0));

/* Return the color space of the bitmap context `context', or NULL if
   `context' is not a bitmap context. */

CG_EXTERN CGColorSpaceRef __nullable CGBitmapContextGetColorSpace(
    CGContextRef cg_nullable context)
    API_AVAILABLE(macos(10.2), ios(2.0));

/* Return the alpha info of the bitmap context `context', or
   "kCGImageAlphaNone" if `context' is not a bitmap context. */

CG_EXTERN CGImageAlphaInfo CGBitmapContextGetAlphaInfo(
    CGContextRef cg_nullable context)
    API_AVAILABLE(macos(10.2), ios(2.0));

/* Return the bitmap info of the bitmap context `context', or 0 if `context'
   is not a bitmap context. */

CG_EXTERN CGBitmapInfo CGBitmapContextGetBitmapInfo(
    CGContextRef cg_nullable context)
    API_AVAILABLE(macos(10.4), ios(2.0));

/* Return an image containing a snapshot of the bitmap context `context'. If
   context is not a bitmap context, or if the image cannot be created for
   any reason, this function returns NULL. This is a "copy" operation ---
   subsequent changes to context will not affect the contents of the
   returned image.

   Note that in some cases the copy will actually follow "copy-on-write"
   semantics, so that the actual physical copy of the bits will only occur
   if the underlying data in the bitmap context is modified. As a
   consequence, you may wish to use the resulting image and release it
   before performing more drawing into the bitmap context; in this way, the
   actual physical copy of the data may be avoided. */

CG_EXTERN CGImageRef __nullable CGBitmapContextCreateImage(
    CGContextRef cg_nullable context)
    API_AVAILABLE(macos(10.4), ios(2.0));

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGBITMAPCONTEXT_H_ */
