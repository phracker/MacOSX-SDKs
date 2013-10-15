/* CoreGraphics - CGColorSpace.h
 * Copyright (c) 1999-2004 Apple Computer, Inc.
 * All rights reserved.
 */

#ifndef CGCOLORSPACE_H_
#define CGCOLORSPACE_H_

typedef struct CGColorSpace *CGColorSpaceRef;

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGDataProvider.h>
#include <stddef.h>

enum CGColorRenderingIntent {
    kCGRenderingIntentDefault,
    kCGRenderingIntentAbsoluteColorimetric,
    kCGRenderingIntentRelativeColorimetric,
    kCGRenderingIntentPerceptual,
    kCGRenderingIntentSaturation
};
typedef enum CGColorRenderingIntent CGColorRenderingIntent;

CG_EXTERN CFStringRef kCGColorSpaceGenericGray AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CG_EXTERN CFStringRef kCGColorSpaceGenericRGB AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CG_EXTERN CFStringRef kCGColorSpaceGenericCMYK AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CG_EXTERN_C_BEGIN

/* Return the CFTypeID for CGColorSpaces. */

CG_EXTERN CFTypeID CGColorSpaceGetTypeID(void) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/** Device-dependent color spaces.  **/

/* Create a DeviceGray colorspace. */

CG_EXTERN CGColorSpaceRef CGColorSpaceCreateDeviceGray(void);

/* Create a DeviceRGB colorspace. */

CG_EXTERN CGColorSpaceRef CGColorSpaceCreateDeviceRGB(void);

/* Create a DeviceCMYK colorspace. */

CG_EXTERN CGColorSpaceRef CGColorSpaceCreateDeviceCMYK(void);

/** Device-independent color spaces. **/

/* Create a calibrated gray colorspace.  `whitePoint' is an array of 3
 * numbers specifying the tristimulus value, in the CIE 1931 XYZ-space, of
 * the diffuse white point.  `blackPoint' is an array of 3 numbers
 * specifying the tristimulus value, in CIE 1931 XYZ-space, of the diffuse
 * black point. `gamma' defines the gamma for the gray component. */

CG_EXTERN CGColorSpaceRef CGColorSpaceCreateCalibratedGray(const float whitePoint[3], const float blackPoint[3], float gamma);

/* Create a calibrated RGB colorspace.  `whitePoint' is an array of 3
 * numbers specifying the tristimulus value, in the CIE 1931 XYZ-space, of
 * the diffuse white point.  `blackPoint' is an array of 3 numbers
 * specifying the tristimulus value, in CIE 1931 XYZ-space, of the diffuse
 * black point. `gamma' is an array of 3 numbers specifying the gamma for
 * the red, green, and blue components of the color space. `matrix' is an
 * array of 9 numbers specifying the linear interpretation of the
 * gamma-modified RGB values of the colorspace with respect to the final
 * XYZ representation. */

CG_EXTERN CGColorSpaceRef CGColorSpaceCreateCalibratedRGB(const float whitePoint[3], const float blackPoint[3], const float gamma[3], const float matrix[9]);

/* Create an L*a*b* colorspace.  `whitePoint' is an array of 3 numbers
 * specifying the tristimulus value, in the CIE 1931 XYZ-space, of the
 * diffuse white point.  `blackPoint' is an array of 3 numbers specifying
 * the tristimulus value, in CIE 1931 XYZ-space, of the diffuse black
 * point. `range' is an array of four numbers specifying the range of valid
 * values for the a* and b* components of the color space. */

CG_EXTERN CGColorSpaceRef CGColorSpaceCreateLab(const float whitePoint[3], const float blackPoint[3], const float range[4]);

/* Create an ICC-based colorspace.  `nComponents' specifies the number of
 * color components in the color space defined by the ICC profile data.
 * This must match the number of components actually in the ICC profile,
 * and must be 1, 3, or 4.  `range' is an array of 2*nComponents numbers
 * specifying the minimum and maximum valid values of the corresponding
 * color components, so that for color component k, range[2*k] <= c[k] <=
 * range[2*k+1], where c[k] is the k'th color component.  `profile' is a
 * data provider specifying the ICC profile.  `alternate' specifies an
 * alternate colorspace to be used in case the ICC profile is not
 * supported.  It must have `nComponents' color components. If `alternate'
 * is NULL, then the color space used will be DeviceGray, DeviceRGB, or
 * DeviceCMYK, depending on whether `nComponents' is 1, 3, or 4,
 * respectively. */

CG_EXTERN CGColorSpaceRef CGColorSpaceCreateICCBased(size_t nComponents, const float *range, CGDataProviderRef profile, CGColorSpaceRef alternate);

/** Special colorspaces. **/

/* Create an indexed colorspace.  A sample value in an indexed color space
 * is treated as an index into the color table of the color space.  `base'
 * specifies the base color space in which the values in the color table
 * are to be interpreted. `lastIndex' is an integer which specifies the
 * maximum valid index value; it must be less than or equal to 255.
 * `colorTable' is an array of m * (lastIndex + 1) bytes, where m is
 * the number of color components in the base color space.  Each byte
 * is an unsigned integer in the range 0 to 255 that is scaled to the
 * range of the corresponding color component in the base color space. */

CG_EXTERN CGColorSpaceRef CGColorSpaceCreateIndexed(CGColorSpaceRef baseSpace, size_t lastIndex, const unsigned char *colorTable);

/* Create a pattern colorspace. `baseSpace' is the underlying colorspace of
 * the pattern colorspace.  For colored patterns, `baseSpace' should be
 * NULL; for uncolored patterns, `baseSpace' specifies the colorspace of
 * colors which will be painted through the pattern. */

CG_EXTERN CGColorSpaceRef CGColorSpaceCreatePattern(CGColorSpaceRef baseSpace);

/* Create a CGColorSpace using `platformColorSpaceReference', a
 * platform-specific color space reference. For MacOS X,
 * `platformColorSpaceReference' should be a CMProfileRef. */

CG_EXTERN CGColorSpaceRef CGColorSpaceCreateWithPlatformColorSpace(void *platformColorSpaceReference);

/* Create a colorspace using `name' as the identifier for the colorspace. */

CG_EXTERN CGColorSpaceRef CGColorSpaceCreateWithName(CFStringRef name) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/** Colorspace information. **/

/* Return the number of color components in the colorspace `cs'. */

CG_EXTERN size_t CGColorSpaceGetNumberOfComponents(const CGColorSpaceRef cs);

/** Retaining & releasing colorspaces. **/

/* Equivalent to `CFRetain(cs)'. */

CG_EXTERN CGColorSpaceRef CGColorSpaceRetain(CGColorSpaceRef cs);

/* Equivalent to `CFRelease(cs)'. */

CG_EXTERN void CGColorSpaceRelease(CGColorSpaceRef cs);

CG_EXTERN_C_END

/** Deprecated APIs. **/

/* Use "kCGColorSpaceGenericGray" instead. */
#define kCGColorSpaceUserGray CFSTR("kCGColorSpaceUserGray")

/* Use "kCGColorSpaceGenericRGB" instead. */
#define kCGColorSpaceUserRGB  CFSTR("kCGColorSpaceUserRGB")

/* Use "kCGColorSpaceGenericCMYK" instead. */
#define kCGColorSpaceUserCMYK CFSTR("kCGColorSpaceUserCMYK")

#endif	/* CGCOLORSPACE_H_ */
