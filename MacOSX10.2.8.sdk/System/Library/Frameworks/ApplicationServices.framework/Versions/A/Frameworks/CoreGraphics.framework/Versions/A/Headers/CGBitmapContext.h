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
 * pixel is specified by `bitsPerComponent', which must be 1, 2, 4, or 8.
 * Each row of the bitmap consists of `bytesPerRow' bytes, which must be at
 * least `(width * bitsPerComponent * number of components + 7)/8' bytes.
 * `data' points a block of memory at least `bytesPerRow * height' bytes.
 * `alphaInfo' specifies whether the bitmap should contain an alpha
 * channel, and how it's to be generated. */

CG_EXTERN CGContextRef CGBitmapContextCreate(void *data, size_t width, size_t height, size_t bitsPerComponent, size_t bytesPerRow, CGColorSpaceRef colorspace, CGImageAlphaInfo alphaInfo);

/* Return the data associated with the bitmap context `c', or NULL if `c'
 * is not a bitmap context. */

CG_EXTERN void *CGBitmapContextGetData(CGContextRef c);

/* Return the width of the bitmap context `c', or 0 if `c' is not a bitmap
 * context. */

CG_EXTERN size_t CGBitmapContextGetWidth(CGContextRef c);

/* Return the height of the bitmap context `c', or 0 if `c' is not a bitmap
 * context. */

CG_EXTERN size_t CGBitmapContextGetHeight(CGContextRef c);

/* Return the bits per component of the bitmap context `c', or 0 if `c' is
 * not a bitmap context. */

CG_EXTERN size_t CGBitmapContextGetBitsPerComponent(CGContextRef c);

/* Return the bits per pixel of the bitmap context `c', or 0 if `c' is not
 * a bitmap context. */

CG_EXTERN size_t CGBitmapContextGetBitsPerPixel(CGContextRef c);

/* Return the bytes per row of the bitmap context `c', or 0 if `c' is not a
 * bitmap context. */

CG_EXTERN size_t CGBitmapContextGetBytesPerRow(CGContextRef c);

/* Return the colorspace of the bitmap context `c', or NULL if `c' is not a
 * bitmap context. */

CG_EXTERN CGColorSpaceRef CGBitmapContextGetColorSpace(CGContextRef c);

/* Return the alpha info of the bitmap context `c', or kCGImageAlphaNone if
 * `c' is not a bitmap context. */

CG_EXTERN CGImageAlphaInfo CGBitmapContextGetAlphaInfo(CGContextRef c);

CG_EXTERN_C_END

#endif	/* CGBITMAPCONTEXT_H_ */
