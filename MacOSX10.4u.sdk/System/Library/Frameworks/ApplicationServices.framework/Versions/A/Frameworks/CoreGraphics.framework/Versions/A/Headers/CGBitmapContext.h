/* CoreGraphics - CGBitmapContext.h
 * Copyright (c) 2000 Apple Computer, Inc.
 * All rights reserved.
 */

#ifndef CGBITMAPCONTEXT_H_
#define CGBITMAPCONTEXT_H_

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGContext.h>

CG_EXTERN_C_BEGIN

/* Create a bitmap context.  The context draws into a bitmap which is
 * `width' pixels wide and `height' pixels high.  The number of components
 * for each pixel is specified by `colorspace', which also may specify a
 * destination color profile. The number of bits for each component of a
 * pixel is specified by `bitsPerComponent', which currently must be 5, 8 or 32.
 * Each row of the bitmap consists of `bytesPerRow' bytes, which must be at
 * least `(width * bitsPerComponent * number of components + 7)/8' bytes.
 * `data' points a block of memory at least `bytesPerRow * height' bytes.
 * `bitmapInfo' specifies whether the bitmap should contain an alpha
 * channel and how it's to be generated, along with whether the components
 * are floating-point or integer. */

CG_EXTERN CGContextRef CGBitmapContextCreate(void *data, size_t width, size_t height, size_t bitsPerComponent, size_t bytesPerRow, CGColorSpaceRef colorspace, CGBitmapInfo bitmapInfo);

/* Return the data associated with the bitmap context `c', or NULL if `c'
 * is not a bitmap context. */

CG_EXTERN void *CGBitmapContextGetData(CGContextRef c) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/* Return the width of the bitmap context `c', or 0 if `c' is not a bitmap
 * context. */

CG_EXTERN size_t CGBitmapContextGetWidth(CGContextRef c) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/* Return the height of the bitmap context `c', or 0 if `c' is not a bitmap
 * context. */

CG_EXTERN size_t CGBitmapContextGetHeight(CGContextRef c) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/* Return the bits per component of the bitmap context `c', or 0 if `c' is
 * not a bitmap context. */

CG_EXTERN size_t CGBitmapContextGetBitsPerComponent(CGContextRef c) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/* Return the bits per pixel of the bitmap context `c', or 0 if `c' is not
 * a bitmap context. */

CG_EXTERN size_t CGBitmapContextGetBitsPerPixel(CGContextRef c) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/* Return the bytes per row of the bitmap context `c', or 0 if `c' is not a
 * bitmap context. */

CG_EXTERN size_t CGBitmapContextGetBytesPerRow(CGContextRef c) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/* Return the colorspace of the bitmap context `c', or NULL if `c' is not a
 * bitmap context. */

CG_EXTERN CGColorSpaceRef CGBitmapContextGetColorSpace(CGContextRef c) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/* Return the alpha info of the bitmap context `c', or kCGImageAlphaNone if
 * `c' is not a bitmap context. */

CG_EXTERN CGImageAlphaInfo CGBitmapContextGetAlphaInfo(CGContextRef c) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/* Return the bitmap info of the bitmap context `c', or 0 if `c' is not a
 * bitmap context. */

CG_EXTERN CGBitmapInfo CGBitmapContextGetBitmapInfo(CGContextRef c) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Return an image containing a snapshot of the bitmap context `c'.  If
 * context is not a bitmap context, or if the image cannot be created for
 * any reason, this function returns NULL.  This is a "copy" operation ---
 * subsequent changes to context will not affect the contents of the
 * returned image.
 *
 * Note that in some cases the copy will actually follow "copy-on-write"
 * semantics, so that the actual physical copy of the bits will only occur
 * if the underlying data in the bitmap context is modified.  As a
 * consequence, you may wish to use the resulting image and release it
 * before performing more drawing into the bitmap context; in this way, the
 * actual physical copy of the data may be avoided. */

CG_EXTERN CGImageRef CGBitmapContextCreateImage(CGContextRef c) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CG_EXTERN_C_END

#endif	/* CGBITMAPCONTEXT_H_ */
