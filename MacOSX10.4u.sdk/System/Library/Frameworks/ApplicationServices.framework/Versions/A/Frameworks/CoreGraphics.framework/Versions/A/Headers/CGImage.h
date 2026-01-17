/* CoreGraphics - CGImage.h
 * Copyright (c) 2000-2004 Apple Computer, Inc.
 * All rights reserved.
 */

#ifndef CGIMAGE_H_
#define CGIMAGE_H_

typedef struct CGImage *CGImageRef;

#include <CoreGraphics/CGColorSpace.h>
#include <CoreGraphics/CGDataProvider.h>
#include <CoreGraphics/CGGeometry.h>

CG_EXTERN_C_BEGIN

enum CGImageAlphaInfo {
    kCGImageAlphaNone,               /* For example, RGB. */
    kCGImageAlphaPremultipliedLast,  /* For example, premultiplied RGBA */
    kCGImageAlphaPremultipliedFirst, /* For example, premultiplied ARGB */
    kCGImageAlphaLast,               /* For example, non-premultiplied RGBA */
    kCGImageAlphaFirst,              /* For example, non-premultiplied ARGB */
    kCGImageAlphaNoneSkipLast,       /* For example, RBGX. */
    kCGImageAlphaNoneSkipFirst,      /* For example, XRGB. */
    kCGImageAlphaOnly                /* No color data, alpha data only */
};
typedef enum CGImageAlphaInfo CGImageAlphaInfo;

enum {
    kCGBitmapAlphaInfoMask = 0x1F,
    kCGBitmapFloatComponents = (1 << 8),
    
    kCGBitmapByteOrderMask = 0x7000,
    kCGBitmapByteOrderDefault = (0 << 12),
    kCGBitmapByteOrder16Little = (1 << 12),
    kCGBitmapByteOrder32Little = (2 << 12),
    kCGBitmapByteOrder16Big = (3 << 12),
    kCGBitmapByteOrder32Big = (4 << 12)
};
typedef uint32_t CGBitmapInfo; /* Available in MAC OS X 10.4 & later. */

#ifdef __BIG_ENDIAN__
#define kCGBitmapByteOrder16Host kCGBitmapByteOrder16Big
#define kCGBitmapByteOrder32Host kCGBitmapByteOrder32Big
#else    /* Little endian. */
#define kCGBitmapByteOrder16Host kCGBitmapByteOrder16Little
#define kCGBitmapByteOrder32Host kCGBitmapByteOrder32Little
#endif

/* Return the CFTypeID for CGImageRefs. */

CG_EXTERN CFTypeID CGImageGetTypeID(void) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/* Create an image. */

CG_EXTERN CGImageRef CGImageCreate(size_t width, size_t height, size_t bitsPerComponent, size_t bitsPerPixel, size_t bytesPerRow, CGColorSpaceRef colorspace, CGBitmapInfo bitmapInfo, CGDataProviderRef provider, const float decode[], bool shouldInterpolate, CGColorRenderingIntent intent);

/* Create an image mask. */

CG_EXTERN CGImageRef CGImageMaskCreate(size_t width, size_t height, size_t bitsPerComponent, size_t bitsPerPixel, size_t bytesPerRow, CGDataProviderRef provider, const float decode[], bool shouldInterpolate);

/* Return a copy of `image'. Only the image structure itself is copied; the
 * underlying data is not. */

CG_EXTERN CGImageRef CGImageCreateCopy(CGImageRef image);

/* Create an image from `source', a data provider of JPEG-encoded data. */

CG_EXTERN CGImageRef CGImageCreateWithJPEGDataProvider(CGDataProviderRef source, const float decode[], bool shouldInterpolate, CGColorRenderingIntent intent) AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

/* Create an image using `source', a data provider for PNG-encoded data. */

CG_EXTERN CGImageRef CGImageCreateWithPNGDataProvider(CGDataProviderRef source, const float decode[], bool shouldInterpolate, CGColorRenderingIntent intent) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/* Create an image using the data contained within the subrectangle `rect'
 * of `image'.
 *
 * The new image is created by
 *   1) adjusting `rect' to integral bounds by calling "CGRectIntegral";
 *   2) intersecting the result with a rectangle with origin (0, 0) and
 *      size equal to the size of `image';
 *   3) referencing the pixels within the resulting rectangle, treating the
 *      first pixel of the image data as the origin of the image.
 * If the resulting rectangle is the null rectangle, this function returns
 * NULL.
 *
 * If W and H are the width and height of image, respectively, then the
 * point (0,0) corresponds to the first pixel of the image data; the point
 * (W-1, 0) is the last pixel of the first row of the image data; (0, H-1)
 * is the first pixel of the last row of the image data; and (W-1, H-1) is
 * the last pixel of the last row of the image data.
 *
 * The resulting image retains a reference to the original image, so you
 * may release the original image after calling this function. */

CG_EXTERN CGImageRef CGImageCreateWithImageInRect(CGImageRef image, CGRect rect) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Create a new image from `image' masked by `mask', which may be an image
 * mask or an image.
 *
 * If `mask' is an image mask, then it indicates which parts of the context
 * are to be painted with the image when drawn in a context, and which are
 * to be masked out (left unchanged). The source samples of the image mask
 * determine which areas are painted, acting as an "inverse alpha": if the
 * value of a source sample in the image mask is S, then the corresponding
 * region in `image' is blended with the destination using an alpha of
 * (1-S).  (For example, if S is 1, then the region is not painted, while
 * if S is 0, the region is fully painted.)
 *
 * If `mask' is an image, then it serves as alpha mask for blending the
 * image onto the destination.  The source samples of `mask' determine
 * which areas are painted: if the value of the source sample in mask is S,
 * then the corresponding region in image is blended with the destination
 * with an alpha of S.  (For example, if S is 0, then the region is not
 * painted, while if S is 1, the region is fully painted.)
 *
 * The parameter `image' may not be an image mask and may not have an image
 * mask or masking color associated with it.
 *
 * If `mask' is an image, then it must be in the DeviceGray color space,
 * may not have alpha, and may not itself be masked by an image mask
 * or a masking color. */

CG_EXTERN CGImageRef CGImageCreateWithMask(CGImageRef image, CGImageRef mask) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Create a new image from `image' masked by `components', an array of 2N
 * values { min[1], max[1], ... min[N], max[N] } where N is the number of
 * components in color space of `image'. Any image sample with color value
 * {c[1], ... c[N]} where min[i] <= c[i] <= max[i] for 1 <= i <= N is
 * masked out (that is, not painted).
 *
 * Each value in `components' must be a valid image sample value: if
 * `image' has integral pixel components, then each value of must be in the
 * range [0 .. 2**bitsPerComponent - 1] (where `bitsPerComponent' is the
 * number of bits/component of `image'); if `image' has floating-point
 * pixel components, then each value may be any floating-point number which
 * is a valid color component.
 *
 * The parameter `image' may not be an image mask, and may not already have
 * an image mask or masking color associated with it. */

CG_EXTERN CGImageRef CGImageCreateWithMaskingColors(CGImageRef image, const float components[]) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Create a copy of `image', replacing the image's colorspace with
 * `colorspace'.  Returns NULL if `image' is an image mask, or if the
 * number of components of `colorspace' isn't the same as the number of
 * components of the colorspace of `image'. */

CG_EXTERN CGImageRef CGImageCreateCopyWithColorSpace(CGImageRef image, CGColorSpaceRef colorspace) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

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

/* Return the bitmap info of `image'. */

CG_EXTERN CGBitmapInfo CGImageGetBitmapInfo(CGImageRef image) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CG_EXTERN_C_END

#endif	/* CGIMAGE_H_ */
