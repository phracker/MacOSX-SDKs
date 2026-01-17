/* CoreGraphics - CGImage.h
 * Copyright (c) 2000 Apple Computer, Inc.
 * All rights reserved.
 */

#ifndef CGIMAGE_H_
#define CGIMAGE_H_

typedef struct CGImage *CGImageRef;

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGColorSpace.h>
#include <CoreGraphics/CGDataProvider.h>
#include <CoreFoundation/CFBase.h>

CG_EXTERN_C_BEGIN

enum CGImageAlphaInfo {
    kCGImageAlphaNone,
    kCGImageAlphaPremultipliedLast,  /* For example, premultiplied RGBA */
    kCGImageAlphaPremultipliedFirst, /* For example, premultiplied ARGB */
    kCGImageAlphaLast,               /* For example, non-premultiplied RGBA */
    kCGImageAlphaFirst,              /* For example, non-premultiplied ARGB */
    kCGImageAlphaNoneSkipLast,       /* Equivalent to kCGImageAlphaNone. */
    kCGImageAlphaNoneSkipFirst
};
typedef enum CGImageAlphaInfo CGImageAlphaInfo;

/* Return the CFTypeID for CGImageRefs. */

CG_EXTERN CFTypeID CGImageGetTypeID(void);

/* Create an image. */

CG_EXTERN CGImageRef CGImageCreate(size_t width, size_t height, size_t bitsPerComponent, size_t bitsPerPixel, size_t bytesPerRow, CGColorSpaceRef colorspace, CGImageAlphaInfo alphaInfo, CGDataProviderRef provider, const float decode[], bool shouldInterpolate, CGColorRenderingIntent intent);

/* Create an image mask. */

CG_EXTERN CGImageRef CGImageMaskCreate(size_t width, size_t height, size_t bitsPerComponent, size_t bitsPerPixel, size_t bytesPerRow, CGDataProviderRef provider, const float decode[], bool shouldInterpolate);

/* Create an image from `source', a data provider of JPEG-encoded data. */

CG_EXTERN CGImageRef CGImageCreateWithJPEGDataProvider(CGDataProviderRef source, const float decode[], bool shouldInterpolate, CGColorRenderingIntent intent);

/* Create an image using `source', a data provider for PNG-encoded data. */

CG_EXTERN CGImageRef CGImageCreateWithPNGDataProvider(CGDataProviderRef source, const float decode[], bool shouldInterpolate, CGColorRenderingIntent intent);

/* Equivalent to `CFRetain(image)'. */

CG_EXTERN CGImageRef CGImageRetain(CGImageRef image);

/* Equivalent to `CFRelease(image)'. */

CG_EXTERN void CGImageRelease(CGImageRef image);

/* Return true if `image' is an image mask, false otherwise. */

CG_EXTERN bool CGImageIsMask(CGImageRef image);

/* Return the width of `image'. */

CG_EXTERN size_t CGImageGetWidth(CGImageRef image);

/* Return the height of `image'. */

CG_EXTERN size_t CGImageGetHeight(CGImageRef image);

/* Return the number of bits/component of `image'. */

CG_EXTERN size_t CGImageGetBitsPerComponent(CGImageRef image);

/* Return the number of bits/pixel of `image'. */

CG_EXTERN size_t CGImageGetBitsPerPixel(CGImageRef image);

/* Return the number of bytes/row of `image'. */

CG_EXTERN size_t CGImageGetBytesPerRow(CGImageRef image);

/* Return the colorspace of `image', or NULL if `image' is an image
 * mask. */

CG_EXTERN CGColorSpaceRef CGImageGetColorSpace(CGImageRef image);

/* Return the alpha info of `image'. */

CG_EXTERN CGImageAlphaInfo CGImageGetAlphaInfo(CGImageRef image);

/* Return the data provider of `image'. */

CG_EXTERN CGDataProviderRef CGImageGetDataProvider(CGImageRef image);

/* Return the decode array of `image'. */

CG_EXTERN const float *CGImageGetDecode(CGImageRef image);

/* Return the interpolation parameter of `image'. */

CG_EXTERN bool CGImageGetShouldInterpolate(CGImageRef image);

/* Return the rendering intent of `image'. */

CG_EXTERN CGColorRenderingIntent CGImageGetRenderingIntent(CGImageRef image);

CG_EXTERN_C_END

#endif	/* CGIMAGE_H_ */
