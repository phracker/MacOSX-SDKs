/* CoreGraphics - CGImage.h
 * Copyright (c) 2000-2008 Apple Inc.
 * All rights reserved. */

#ifndef CGIMAGE_H_
#define CGIMAGE_H_

typedef struct CGImage *CGImageRef;

#include <CoreGraphics/CGColorSpace.h>
#include <CoreGraphics/CGDataProvider.h>
#include <CoreGraphics/CGGeometry.h>

CF_IMPLICIT_BRIDGING_ENABLED

typedef CF_ENUM(uint32_t, CGImageAlphaInfo) {
  kCGImageAlphaNone,               /* For example, RGB. */
  kCGImageAlphaPremultipliedLast,  /* For example, premultiplied RGBA */
  kCGImageAlphaPremultipliedFirst, /* For example, premultiplied ARGB */
  kCGImageAlphaLast,               /* For example, non-premultiplied RGBA */
  kCGImageAlphaFirst,              /* For example, non-premultiplied ARGB */
  kCGImageAlphaNoneSkipLast,       /* For example, RBGX. */
  kCGImageAlphaNoneSkipFirst,      /* For example, XRGB. */
  kCGImageAlphaOnly                /* No color data, alpha data only */
};

typedef CF_OPTIONS(uint32_t, CGBitmapInfo) {
  kCGBitmapAlphaInfoMask = 0x1F,
  kCGBitmapFloatComponents = (1 << 8),
    
  kCGBitmapByteOrderMask = 0x7000,
  kCGBitmapByteOrderDefault = (0 << 12),
  kCGBitmapByteOrder16Little = (1 << 12),
  kCGBitmapByteOrder32Little = (2 << 12),
  kCGBitmapByteOrder16Big = (3 << 12),
  kCGBitmapByteOrder32Big = (4 << 12)
} CF_ENUM_AVAILABLE(10_4, 2_0);

#ifdef __BIG_ENDIAN__
# define kCGBitmapByteOrder16Host kCGBitmapByteOrder16Big
# define kCGBitmapByteOrder32Host kCGBitmapByteOrder32Big
#else    /* Little endian. */
# define kCGBitmapByteOrder16Host kCGBitmapByteOrder16Little
# define kCGBitmapByteOrder32Host kCGBitmapByteOrder32Little
#endif

/* Return the CFTypeID for CGImageRefs. */

CG_EXTERN CFTypeID CGImageGetTypeID(void)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Create an image. */

CG_EXTERN CGImageRef CGImageCreate(size_t width, size_t height,
    size_t bitsPerComponent, size_t bitsPerPixel, size_t bytesPerRow,
    CGColorSpaceRef space, CGBitmapInfo bitmapInfo, CGDataProviderRef provider,
    const CGFloat decode[], bool shouldInterpolate,
    CGColorRenderingIntent intent)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Create an image mask. */

CG_EXTERN CGImageRef CGImageMaskCreate(size_t width, size_t height,
    size_t bitsPerComponent, size_t bitsPerPixel, size_t bytesPerRow,
    CGDataProviderRef provider, const CGFloat decode[], bool shouldInterpolate)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return a copy of `image'. Only the image structure itself is copied; the
   underlying data is not. */

CG_EXTERN CGImageRef CGImageCreateCopy(CGImageRef image)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Create an image from `source', a data provider of JPEG-encoded data. */

CG_EXTERN CGImageRef CGImageCreateWithJPEGDataProvider(CGDataProviderRef
    source, const CGFloat decode[], bool shouldInterpolate,
    CGColorRenderingIntent intent)
    CG_AVAILABLE_STARTING(__MAC_10_1, __IPHONE_2_0);

/* Create an image using `source', a data provider for PNG-encoded data. */

CG_EXTERN CGImageRef CGImageCreateWithPNGDataProvider(CGDataProviderRef source,
    const CGFloat decode[], bool shouldInterpolate,
    CGColorRenderingIntent intent)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Create an image using the data contained within the subrectangle `rect'
   of `image'.

   The new image is created by
     1) adjusting `rect' to integral bounds by calling "CGRectIntegral";
     2) intersecting the result with a rectangle with origin (0, 0) and size
        equal to the size of `image';
     3) referencing the pixels within the resulting rectangle, treating the
        first pixel of the image data as the origin of the image.
   If the resulting rectangle is the null rectangle, this function returns
   NULL.

   If W and H are the width and height of image, respectively, then the
   point (0,0) corresponds to the first pixel of the image data; the point
   (W-1, 0) is the last pixel of the first row of the image data; (0, H-1)
   is the first pixel of the last row of the image data; and (W-1, H-1) is
   the last pixel of the last row of the image data.

   The resulting image retains a reference to the original image, so you may
   release the original image after calling this function. */

CG_EXTERN CGImageRef CGImageCreateWithImageInRect(CGImageRef image,
    CGRect rect) CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Create a new image from `image' masked by `mask', which may be an image
   mask or an image.

   If `mask' is an image mask, then it indicates which parts of the context
   are to be painted with the image when drawn in a context, and which are
   to be masked out (left unchanged). The source samples of the image mask
   determine which areas are painted, acting as an "inverse alpha": if the
   value of a source sample in the image mask is S, then the corresponding
   region in `image' is blended with the destination using an alpha of
   (1-S). (For example, if S is 1, then the region is not painted, while if
   S is 0, the region is fully painted.)

   If `mask' is an image, then it serves as alpha mask for blending the
   image onto the destination. The source samples of `mask' determine which
   areas are painted: if the value of the source sample in mask is S, then
   the corresponding region in image is blended with the destination with an
   alpha of S. (For example, if S is 0, then the region is not painted,
   while if S is 1, the region is fully painted.)

   The parameter `image' may not be an image mask and may not have an image
   mask or masking color associated with it.
  
   If `mask' is an image, then it must be in the DeviceGray color space, may
   not have alpha, and may not itself be masked by an image mask or a
   masking color. */

CG_EXTERN CGImageRef CGImageCreateWithMask(CGImageRef image, CGImageRef mask)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Create a new image from `image' masked by `components', an array of 2N
   values { min[1], max[1], ... min[N], max[N] } where N is the number of
   components in color space of `image'. Any image sample with color value
   {c[1], ... c[N]} where min[i] <= c[i] <= max[i] for 1 <= i <= N is masked
   out (that is, not painted).

   Each value in `components' must be a valid image sample value: if `image'
   has integral pixel components, then each value of must be in the range
   [0..2**bitsPerComponent - 1] (where `bitsPerComponent' is the number of
   bits/component of `image'); if `image' has floating-point pixel
   components, then each value may be any floating-point number which is a
   valid color component.

   The parameter `image' may not be an image mask, and may not already have
   an image mask or masking color associated with it. */

CG_EXTERN CGImageRef CGImageCreateWithMaskingColors(CGImageRef image,
    const CGFloat components[])
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Create a copy of `image', replacing the image's color space with `space'.
   Returns NULL if `image' is an image mask, or if the number of components
   of `space' isn't the same as the number of components of the color space
   of `image'. */

CG_EXTERN CGImageRef CGImageCreateCopyWithColorSpace(CGImageRef image,
    CGColorSpaceRef space) CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Equivalent to `CFRetain(image)'. */

CG_EXTERN CGImageRef CGImageRetain(CGImageRef image)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Equivalent to `CFRelease(image)'. */

CG_EXTERN void CGImageRelease(CGImageRef image)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return true if `image' is an image mask, false otherwise. */

CG_EXTERN bool CGImageIsMask(CGImageRef image)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the width of `image'. */

CG_EXTERN size_t CGImageGetWidth(CGImageRef image)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the height of `image'. */

CG_EXTERN size_t CGImageGetHeight(CGImageRef image)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the number of bits/component of `image'. */

CG_EXTERN size_t CGImageGetBitsPerComponent(CGImageRef image)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the number of bits/pixel of `image'. */

CG_EXTERN size_t CGImageGetBitsPerPixel(CGImageRef image)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the number of bytes/row of `image'. */

CG_EXTERN size_t CGImageGetBytesPerRow(CGImageRef image)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the color space of `image', or NULL if `image' is an image
   mask. */

CG_EXTERN CGColorSpaceRef CGImageGetColorSpace(CGImageRef image)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the alpha info of `image'. */

CG_EXTERN CGImageAlphaInfo CGImageGetAlphaInfo(CGImageRef image)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the data provider of `image'. */

CG_EXTERN CGDataProviderRef CGImageGetDataProvider(CGImageRef image)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the decode array of `image'. */

CG_EXTERN const CGFloat *CGImageGetDecode(CGImageRef image)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the interpolation parameter of `image'. */

CG_EXTERN bool CGImageGetShouldInterpolate(CGImageRef image)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the rendering intent of `image'. */

CG_EXTERN CGColorRenderingIntent CGImageGetRenderingIntent(CGImageRef image)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the bitmap info of `image'. */

CG_EXTERN CGBitmapInfo CGImageGetBitmapInfo(CGImageRef image)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

CF_IMPLICIT_BRIDGING_DISABLED

#endif	/* CGIMAGE_H_ */
