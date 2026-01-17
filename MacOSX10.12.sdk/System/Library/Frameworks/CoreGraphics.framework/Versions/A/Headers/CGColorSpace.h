/* CoreGraphics - CGColorSpace.h
   Copyright (c) 1999-2013 Apple Inc.
   All rights reserved. */

#ifndef CGCOLORSPACE_H_
#define CGCOLORSPACE_H_

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFAvailability.h>
#include <stdint.h>

typedef struct CGColorSpace *CGColorSpaceRef;

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGDataProvider.h>

CF_IMPLICIT_BRIDGING_ENABLED

/* Color rendering intents. */

typedef CF_ENUM (int32_t, CGColorRenderingIntent) {
    kCGRenderingIntentDefault,
    kCGRenderingIntentAbsoluteColorimetric,
    kCGRenderingIntentRelativeColorimetric,
    kCGRenderingIntentPerceptual,
    kCGRenderingIntentSaturation
};

/* The model of a color space. */

typedef CF_ENUM (int32_t,  CGColorSpaceModel) {
    kCGColorSpaceModelUnknown = -1,
    kCGColorSpaceModelMonochrome,
    kCGColorSpaceModelRGB,
    kCGColorSpaceModelCMYK,
    kCGColorSpaceModelLab,
    kCGColorSpaceModelDeviceN,
    kCGColorSpaceModelIndexed,
    kCGColorSpaceModelPattern
};

CF_ASSUME_NONNULL_BEGIN

/* The name of the "Generic" Gray color space. It is a legacy
   color space so use it only if you definitely know that you
   need it. If you need just a reasonable monochrome color space,
   please use Generic Gray Gamma 2.2, i.e. use
   kCGColorSpaceGenericGrayGamma2_2 name instead of
   kCGColorSpaceGenericGray. */

CG_EXTERN const CFStringRef kCGColorSpaceGenericGray
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_9_0);

/* The name of the "Generic" RGB color space. It is a legacy
   color space so use it only if you definitely know that you
   need it. If you need just a reasonable RGB color space,
   please use sRGB, i.e. use kCGColorSpaceSRGB name
   instead of kCGColorSpaceGenericRGB. */

CG_EXTERN const CFStringRef kCGColorSpaceGenericRGB
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_9_0);

/* The name of the "Generic" CMYK color space. */

CG_EXTERN const CFStringRef kCGColorSpaceGenericCMYK
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_9_0);
  
CG_EXTERN const CFStringRef kCGColorSpaceDisplayP3
  CG_AVAILABLE_STARTING(__MAC_10_11_2, __IPHONE_9_3);

/* The name of the "Generic" linear RGB color space. This is the same as
   `kCGColorSpaceGenericRGB' but with a 1.0 gamma. */

CG_EXTERN const CFStringRef kCGColorSpaceGenericRGBLinear
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_9_0);

/* The name of the Adobe RGB (1998) color space. For more information, see
  "Adobe RGB (1998) Color Image Encoding", Version 2005-05, Adobe Systems
  Inc. (http://www.adobe.com). */

CG_EXTERN const CFStringRef kCGColorSpaceAdobeRGB1998
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_9_0);

/* The name of the sRGB color space. The capitalization in the name, while
   strictly inaccurate, avoids interpretational ambiguity. For more
   information, see IEC 61966-2-1 (1999-10): "Multimedia systems and
   equipment - Colour measurement and management - Part 2-1: Colour
   management - Default RGB colour space - sRGB". */

CG_EXTERN const CFStringRef kCGColorSpaceSRGB
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_9_0);

/* The "Generic" gray color space with γ = 2.2. */

CG_EXTERN const CFStringRef kCGColorSpaceGenericGrayGamma2_2
  CG_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_9_0);

CG_EXTERN const CFStringRef kCGColorSpaceGenericXYZ
  CG_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_9_0);

CG_EXTERN const CFStringRef kCGColorSpaceACESCGLinear
CG_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_9_0);

CG_EXTERN const CFStringRef kCGColorSpaceITUR_709
CG_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_9_0);

CG_EXTERN const CFStringRef kCGColorSpaceITUR_2020
CG_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_9_0);

CG_EXTERN const CFStringRef kCGColorSpaceROMMRGB
CG_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_9_0);

CG_EXTERN const CFStringRef kCGColorSpaceDCIP3
CG_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_9_0);

/*  The name of the extended sRGB color space.
    The extended sRGB color space allows to specify colors beyond the range of [0.0, 1.0],
    while still preserving the colorimetry and encoding of sRGB (see above for more details).
    The negative values will be encoded as the signed reflection of original encoding functions,
    i.e. y(x) = sign(x)*f(abs(x)) where f(x) represents the encoding function. 
    The capitalization in the name is for avoiding interpretational ambiguity.  */

CG_EXTERN const CFStringRef kCGColorSpaceExtendedSRGB
CG_AVAILABLE_STARTING(__MAC_10_12, __IPHONE_10_0);

/*  The name of the sRGB color space variant with linear gamma */

CG_EXTERN const CFStringRef kCGColorSpaceLinearSRGB
CG_AVAILABLE_STARTING(__MAC_10_12, __IPHONE_10_0);

/*  The name of the extended sRGB color space variant with linear gamma */

CG_EXTERN const CFStringRef kCGColorSpaceExtendedLinearSRGB
CG_AVAILABLE_STARTING(__MAC_10_12, __IPHONE_10_0);

/*  The name of the extended Gray color space. This color space has the same colorimetry as Generic Gray 2.2.
    The negative values will be encoded as the signed reflection of original encoding functions,
    i.e. y(x) = sign(x)*f(abs(x)) where f(x) represents the encoding function. */

CG_EXTERN const CFStringRef kCGColorSpaceExtendedGray
CG_AVAILABLE_STARTING(__MAC_10_12, __IPHONE_10_0);

/*  The name of the Generic Gray 2.2 color space variant with linear gamma */

CG_EXTERN const CFStringRef kCGColorSpaceLinearGray
CG_AVAILABLE_STARTING(__MAC_10_12, __IPHONE_10_0);

/*  The name of the extended Generic Gray 2.2 color space variant with linear gamma */

CG_EXTERN const CFStringRef kCGColorSpaceExtendedLinearGray
CG_AVAILABLE_STARTING(__MAC_10_12, __IPHONE_10_0);

/* Create a DeviceGray color space. */

CG_EXTERN CGColorSpaceRef cg_nullable CGColorSpaceCreateDeviceGray(void)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Create a DeviceRGB color space. */

CG_EXTERN CGColorSpaceRef cg_nullable CGColorSpaceCreateDeviceRGB(void)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Create a DeviceCMYK color space. */

CG_EXTERN CGColorSpaceRef cg_nullable CGColorSpaceCreateDeviceCMYK(void)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Create a calibrated gray color space. `whitePoint' is an array of 3
   numbers specifying the tristimulus value, in the CIE 1931 XYZ-space, of
   the diffuse white point. `blackPoint' is an array of 3 numbers specifying
   the tristimulus value, in CIE 1931 XYZ-space, of the diffuse black point.
   `gamma' defines the gamma for the gray component. */

CG_EXTERN CGColorSpaceRef __nullable CGColorSpaceCreateCalibratedGray(const CGFloat
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

CG_EXTERN CGColorSpaceRef __nullable CGColorSpaceCreateCalibratedRGB(const CGFloat
  whitePoint[3], const CGFloat blackPoint[3], const CGFloat gamma[3],
  const CGFloat matrix[9]) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);
    
/* Create an L*a*b* color space. `whitePoint' is an array of 3 numbers
   specifying the tristimulus value, in the CIE 1931 XYZ-space, of the
   diffuse white point. `blackPoint' is an array of 3 numbers specifying the
   tristimulus value, in CIE 1931 XYZ-space, of the diffuse black point.
   `range' is an array of four numbers specifying the range of valid values
   for the a* and b* components of the color space. */

CG_EXTERN CGColorSpaceRef __nullable CGColorSpaceCreateLab(const CGFloat whitePoint[3],
  const CGFloat blackPoint[3], const CGFloat range[4])
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Create an ICC-based color space using the ICC profile specified by
   `data'. */

CG_EXTERN CGColorSpaceRef __nullable CGColorSpaceCreateWithICCProfile(CFDataRef cg_nullable data)
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

CG_EXTERN CGColorSpaceRef __nullable CGColorSpaceCreateICCBased(size_t nComponents,
  const CGFloat * __nullable range, CGDataProviderRef cg_nullable profile,
  CGColorSpaceRef __nullable alternate)
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

CG_EXTERN CGColorSpaceRef __nullable CGColorSpaceCreateIndexed(CGColorSpaceRef cg_nullable baseSpace,
  size_t lastIndex, const unsigned char * cg_nullable colorTable)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Create a pattern color space. `baseSpace' is the underlying color space
   of the pattern color space. For colored patterns, `baseSpace' should be
   NULL; for uncolored patterns, `baseSpace' specifies the color space of
   colors which will be painted through the pattern. */

CG_EXTERN CGColorSpaceRef __nullable CGColorSpaceCreatePattern(CGColorSpaceRef __nullable baseSpace)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Create a color space using `ref', a platform-specific color space
   reference. For MacOS X, `ref' should be a ColorSyncProfileRef. */

CG_EXTERN CGColorSpaceRef __nullable
  CGColorSpaceCreateWithPlatformColorSpace(const void * cg_nullable ref)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_9_0);

/* Create a color space using `name' as the identifier for the color
   space. */

CG_EXTERN CGColorSpaceRef __nullable CGColorSpaceCreateWithName(CFStringRef cg_nullable name)
  CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Equivalent to `CFRetain(space)', except it doesn't crash (as CFRetain
   does) if `space' is NULL. */

CG_EXTERN CGColorSpaceRef cg_nullable CGColorSpaceRetain(CGColorSpaceRef cg_nullable space)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Equivalent to `CFRelease(space)', except it doesn't crash (as CFRelease
   does) if `space' is NULL. */

CG_EXTERN void CGColorSpaceRelease(CGColorSpaceRef cg_nullable space)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the name used to create the color space `space', or NULL if the
   color space was not created using `CGColorSpaceCreateWithName'. */

CG_EXTERN CFStringRef __nullable CGColorSpaceCopyName(CGColorSpaceRef cg_nullable space)
  CG_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_10_0);

/* Return the CFTypeID for CGColorSpaces. */

CG_EXTERN CFTypeID CGColorSpaceGetTypeID(void)
  CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Return the number of color components in the color space `space'. */

CG_EXTERN size_t CGColorSpaceGetNumberOfComponents(CGColorSpaceRef cg_nullable space)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the color space model of `space'. */

CG_EXTERN CGColorSpaceModel CGColorSpaceGetModel(CGColorSpaceRef cg_nullable space)
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Return the base color space of `space' if `space' is a pattern or indexed
   color space; otherwise, return NULL. To determine whether a color space
   is an indexed or pattern color space, use `CGColorSpaceGetModel'. */

CG_EXTERN CGColorSpaceRef __nullable CGColorSpaceGetBaseColorSpace(CGColorSpaceRef cg_nullable space)
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Return the number of entries in the color table of `space' if `space' is
   an indexed color space; otherwise, return 0. To determine whether a color
   space is an indexed color space, use `CGColorSpaceGetModel'. */

CG_EXTERN size_t CGColorSpaceGetColorTableCount(CGColorSpaceRef cg_nullable space)
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Copy the entries in the color table of `space' to `table' if `space' is
   an indexed color space; otherwise, do nothing. The array pointed to by
   `table' should be at least as large as the number of entries in the color
   table; the returned data is in the same format as that passed to
   `CGColorSpaceCreateIndexed'. To determine whether a color space is an
   indexed color space, use `CGColorSpaceGetModel'. */

CG_EXTERN void CGColorSpaceGetColorTable(CGColorSpaceRef cg_nullable space,
  uint8_t * cg_nullable table) CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Return a copy of the ICC profile of `space', or NULL if the color space
   doesn't have an ICC profile. */

CG_EXTERN CFDataRef __nullable CGColorSpaceCopyICCProfile(CGColorSpaceRef cg_nullable space);
//__CG_DEPRECATED_WITH_MSG("Don't this function; call "
//                         "`CGColorSpaceCopyICCData' instead.");

CG_EXTERN CFDataRef __nullable CGColorSpaceCopyICCData(CGColorSpaceRef cg_nullable space)
CG_AVAILABLE_STARTING(__MAC_10_12, __IPHONE_10_0);

/* Return true if gamut of the RGB color space is greater than 85% of NTSC gamut */

CG_EXTERN bool CGColorSpaceIsWideGamutRGB(CGColorSpaceRef)
CG_AVAILABLE_STARTING(__MAC_10_12, __IPHONE_10_0);

/* Return true if `space' can be used as a destination color space; false
 otherwise. */

CG_EXTERN bool CGColorSpaceSupportsOutput(CGColorSpaceRef space)
CG_AVAILABLE_STARTING(__MAC_10_12, __IPHONE_10_0);

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGCOLORSPACE_H_ */
