/* CoreGraphics - CGColorSpace.h
   Copyright (c) 1999-2013 Apple Inc.
   All rights reserved. */

#ifndef CGCOLORSPACE_H_
#define CGCOLORSPACE_H_

typedef struct CGColorSpace *CGColorSpaceRef;

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGDataProvider.h>

CF_IMPLICIT_BRIDGING_ENABLED

/* Color rendering intents. */

enum CGColorRenderingIntent {
  kCGRenderingIntentDefault,
  kCGRenderingIntentAbsoluteColorimetric,
  kCGRenderingIntentRelativeColorimetric,
  kCGRenderingIntentPerceptual,
  kCGRenderingIntentSaturation
};
typedef enum CGColorRenderingIntent CGColorRenderingIntent;

/* The model of a color space. */

enum CGColorSpaceModel {
  kCGColorSpaceModelUnknown = -1,
  kCGColorSpaceModelMonochrome,
  kCGColorSpaceModelRGB,
  kCGColorSpaceModelCMYK,
  kCGColorSpaceModelLab,
  kCGColorSpaceModelDeviceN,
  kCGColorSpaceModelIndexed,
  kCGColorSpaceModelPattern
};
typedef enum CGColorSpaceModel CGColorSpaceModel;

/* The name of the "Generic" gray color space. */

CG_EXTERN const CFStringRef kCGColorSpaceGenericGray
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* The name of the "Generic" RGB color space. */

CG_EXTERN const CFStringRef kCGColorSpaceGenericRGB
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* The name of the "Generic" CMYK color space. */

CG_EXTERN const CFStringRef kCGColorSpaceGenericCMYK
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* The name of the "Generic" linear RGB color space. This is the same as
   `kCGColorSpaceGenericRGB' but with a 1.0 gamma. */

CG_EXTERN const CFStringRef kCGColorSpaceGenericRGBLinear
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);

/* The name of the Adobe RGB (1998) color space. For more information, see
  "Adobe RGB (1998) Color Image Encoding", Version 2005-05, Adobe Systems
  Inc. (http://www.adobe.com). */

CG_EXTERN const CFStringRef kCGColorSpaceAdobeRGB1998
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);

/* The name of the sRGB color space. The capitalization in the name, while
   strictly inaccurate, avoids interpretational ambiguity. For more
   information, see IEC 61966-2-1 (1999-10): "Multimedia systems and
   equipment - Colour measurement and management - Part 2-1: Colour
   management - Default RGB colour space - sRGB". */

CG_EXTERN const CFStringRef kCGColorSpaceSRGB
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);

/* The "Generic" gray color space with γ = 2.2. */

CG_EXTERN const CFStringRef kCGColorSpaceGenericGrayGamma2_2
  CG_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_NA);

/* Create a DeviceGray color space. */

CG_EXTERN CGColorSpaceRef CGColorSpaceCreateDeviceGray(void)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Create a DeviceRGB color space. */

CG_EXTERN CGColorSpaceRef CGColorSpaceCreateDeviceRGB(void)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Create a DeviceCMYK color space. */

CG_EXTERN CGColorSpaceRef CGColorSpaceCreateDeviceCMYK(void)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Create a calibrated gray color space. `whitePoint' is an array of 3
   numbers specifying the tristimulus value, in the CIE 1931 XYZ-space, of
   the diffuse white point. `blackPoint' is an array of 3 numbers specifying
   the tristimulus value, in CIE 1931 XYZ-space, of the diffuse black point.
   `gamma' defines the gamma for the gray component. */

CG_EXTERN CGColorSpaceRef CGColorSpaceCreateCalibratedGray(const CGFloat
  whitePoint[3], const CGFloat blackPoint[3], CGFloat gamma)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Create a calibrated RGB color space. `whitePoint' is an array of 3
   numbers specifying the tristimulus value, in the CIE 1931 XYZ-space, of
   the diffuse white point. `blackPoint' is an array of 3 numbers specifying
   the tristimulus value, in CIE 1931 XYZ-space, of the diffuse black point.
   `gamma' is an array of 3 numbers specifying the gamma for the red, green,
   and blue components of the color space. `matrix' is an array of 9 numbers
   specifying the linear interpretation of the gamma-modified RGB values of
   the color space with respect to the final XYZ representation. */

CG_EXTERN CGColorSpaceRef CGColorSpaceCreateCalibratedRGB(const CGFloat
  whitePoint[3], const CGFloat blackPoint[3], const CGFloat gamma[3],
  const CGFloat matrix[9]) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);
    
/* Create an L*a*b* color space. `whitePoint' is an array of 3 numbers
   specifying the tristimulus value, in the CIE 1931 XYZ-space, of the
   diffuse white point. `blackPoint' is an array of 3 numbers specifying the
   tristimulus value, in CIE 1931 XYZ-space, of the diffuse black point.
   `range' is an array of four numbers specifying the range of valid values
   for the a* and b* components of the color space. */

CG_EXTERN CGColorSpaceRef CGColorSpaceCreateLab(const CGFloat whitePoint[3],
  const CGFloat blackPoint[3], const CGFloat range[4])
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Create an ICC-based color space using the ICC profile specified by
   `data'. */

CG_EXTERN CGColorSpaceRef CGColorSpaceCreateWithICCProfile(CFDataRef data)
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Create an ICC-based color space. `nComponents' specifies the number of
   color components in the color space defined by the ICC profile data. This
   must match the number of components actually in the ICC profile, and must
   be 1, 3, or 4. `range' is an array of 2*nComponents numbers specifying
   the minimum and maximum valid values of the corresponding color
   components, so that for color component k, range[2*k] <= c[k] <=
   range[2*k+1], where c[k] is the k'th color component. `profile' is a data
   provider specifying the ICC profile. `alternate' specifies an alternate
   color space to be used in case the ICC profile is not supported. It must
   have `nComponents' color components. If `alternate' is NULL, then the
   color space used will be DeviceGray, DeviceRGB, or DeviceCMYK, depending
   on whether `nComponents' is 1, 3, or 4, respectively. */

CG_EXTERN CGColorSpaceRef CGColorSpaceCreateICCBased(size_t nComponents,
  const CGFloat *range, CGDataProviderRef profile, CGColorSpaceRef alternate)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Create an indexed color space. A sample value in an indexed color space
   is treated as an index into the color table of the color space. `base'
   specifies the base color space in which the values in the color table are
   to be interpreted. `lastIndex' is an integer which specifies the maximum
   valid index value; it must be less than or equal to 255. `colorTable' is
   an array of m * (lastIndex + 1) bytes, where m is the number of color
   components in the base color space. Each byte is an unsigned integer in
   the range 0 to 255 that is scaled to the range of the corresponding color
   component in the base color space. */

CG_EXTERN CGColorSpaceRef CGColorSpaceCreateIndexed(CGColorSpaceRef baseSpace,
  size_t lastIndex, const unsigned char *colorTable)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Create a pattern color space. `baseSpace' is the underlying color space
   of the pattern color space. For colored patterns, `baseSpace' should be
   NULL; for uncolored patterns, `baseSpace' specifies the color space of
   colors which will be painted through the pattern. */

CG_EXTERN CGColorSpaceRef CGColorSpaceCreatePattern(CGColorSpaceRef baseSpace)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Create a color space using `ref', a platform-specific color space
   reference. For MacOS X, `ref' should be a CMProfileRef. */

CG_EXTERN CGColorSpaceRef
  CGColorSpaceCreateWithPlatformColorSpace(const void *ref)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Create a color space using `name' as the identifier for the color
   space. */

CG_EXTERN CGColorSpaceRef CGColorSpaceCreateWithName(CFStringRef name)
  CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Equivalent to `CFRetain(space)', except it doesn't crash (as CFRetain
   does) if `space' is NULL. */

CG_EXTERN CGColorSpaceRef CGColorSpaceRetain(CGColorSpaceRef space)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Equivalent to `CFRelease(space)', except it doesn't crash (as CFRelease
   does) if `space' is NULL. */

CG_EXTERN void CGColorSpaceRelease(CGColorSpaceRef space)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the name used to create the color space `space', or NULL if the
   color space was not created using `CGColorSpaceCreateWithName'. */

CG_EXTERN CFStringRef CGColorSpaceCopyName(CGColorSpaceRef space)
  CG_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_NA);

/* Return the CFTypeID for CGColorSpaces. */

CG_EXTERN CFTypeID CGColorSpaceGetTypeID(void)
  CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Return the number of color components in the color space `space'. */

CG_EXTERN size_t CGColorSpaceGetNumberOfComponents(CGColorSpaceRef space)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the color space model of `space'. */

CG_EXTERN CGColorSpaceModel CGColorSpaceGetModel(CGColorSpaceRef space)
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Return the base color space of `space' if `space' is a pattern or indexed
   color space; otherwise, return NULL. To determine whether a color space
   is an indexed or pattern color space, use `CGColorSpaceGetModel'. */

CG_EXTERN CGColorSpaceRef CGColorSpaceGetBaseColorSpace(CGColorSpaceRef space)
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Return the number of entries in the color table of `space' if `space' is
   an indexed color space; otherwise, return 0. To determine whether a color
   space is an indexed color space, use `CGColorSpaceGetModel'. */

CG_EXTERN size_t CGColorSpaceGetColorTableCount(CGColorSpaceRef space)
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Copy the entries in the color table of `space' to `table' if `space' is
   an indexed color space; otherwise, do nothing. The array pointed to by
   `table' should be at least as large as the number of entries in the color
   table; the returned data is in the same format as that passed to
   `CGColorSpaceCreateIndexed'. To determine whether a color space is an
   indexed color space, use `CGColorSpaceGetModel'. */

CG_EXTERN void CGColorSpaceGetColorTable(CGColorSpaceRef space, uint8_t *table)
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Return a copy of the ICC profile of `space', or NULL if the color space
   doesn't have an ICC profile. */

CG_EXTERN CFDataRef CGColorSpaceCopyICCProfile(CGColorSpaceRef space)
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_6_0);

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGCOLORSPACE_H_ */
