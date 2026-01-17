/* CoreGraphics - CGColor.h
 * Copyright (c) 2003-2008 Apple Inc.
 * All rights reserved. */

#ifndef CGCOLOR_H_
#define CGCOLOR_H_

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFAvailability.h>
#include <stdint.h>

typedef struct CF_BRIDGED_TYPE(id) CGColor *CGColorRef; /* Swift Sendable */

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGColorSpace.h>
#include <CoreGraphics/CGPattern.h>

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

/* Create a color in the color space `space' with color components
   (including alpha) specified by `components'. `space' may be any color
   space except a pattern color space. */

CG_EXTERN CGColorRef __nullable CGColorCreate(CGColorSpaceRef cg_nullable space,
  const CGFloat * cg_nullable components)
  API_AVAILABLE(macos(10.3), ios(2.0));

/* Create a color in the "Generic" gray color space. */

CG_EXTERN CGColorRef  CGColorCreateGenericGray(CGFloat gray, CGFloat alpha)
  API_AVAILABLE(macos(10.5), ios(13.0));

/* Create a color in the "Generic" RGB color space. */

CG_EXTERN CGColorRef  CGColorCreateGenericRGB(CGFloat red, CGFloat green,
  CGFloat blue, CGFloat alpha) API_AVAILABLE(macos(10.5), ios(13.0));

/* Create a color in the "Generic" CMYK color space. */

CG_EXTERN CGColorRef  CGColorCreateGenericCMYK(CGFloat cyan, CGFloat magenta,
  CGFloat yellow, CGFloat black, CGFloat alpha) API_AVAILABLE(macos(10.5), ios(13.0));

/* Create a color in the "Generic Gray Gamma 2.2 color space. */

CG_EXTERN CGColorRef  CGColorCreateGenericGrayGamma2_2(CGFloat gray, CGFloat alpha) API_AVAILABLE(macos(10.15), ios(13.0));

/* Create a color in sRGB color space. */

CG_EXTERN CGColorRef  CGColorCreateSRGB(CGFloat red, CGFloat green,
                                        CGFloat blue, CGFloat alpha) API_AVAILABLE(macos(10.15), ios(13.0));

/* Create a color with a specified content headroom. Color space is required to be either HDR or extended range RGB.
   The content value of 0.0f means 'unknown headroom'. If the color space is HDR, passing a headroom of 0.0f
   is a request to use a default headroom implied by the color space. */

CG_EXTERN CGColorRef __nullable CGColorCreateWithContentHeadroom(float headroom, CGColorSpaceRef cg_nullable space, CGFloat red, CGFloat green,
                                                                 CGFloat blue, CGFloat alpha) API_AVAILABLE(macos(26.0), ios(26.0));

/* Return content headroom of the color. Returned value is 0.0f if the content headroom of the color is unknown */

CG_EXTERN float CGColorGetContentHeadroom(CGColorRef cg_nullable color) API_AVAILABLE(macos(26.0), ios(26.0));

/* Return a constant color. As `CGColorGetConstantColor' is not a "Copy" or
   "Create" function, it does not necessarily return a new reference each
   time it's called. As a consequence, you should not release the returned
   value. However, colors returned from `CGColorGetConstantColor' can be
   retained and released in a properly nested fashion, just like any other
   CF type. */

CG_EXTERN CGColorRef __nullable CGColorGetConstantColor(CFStringRef cg_nullable colorName)
  API_AVAILABLE(macos(10.5), ios(14.0));

/* Create a color in color space `space' with pattern `pattern' and
   components `components'. `space' must be a pattern color space. */

CG_EXTERN CGColorRef __nullable CGColorCreateWithPattern(CGColorSpaceRef cg_nullable space,
  CGPatternRef cg_nullable pattern, const CGFloat * cg_nullable components)
  API_AVAILABLE(macos(10.3), ios(2.0));

/* Create a copy of `color'. */

CG_EXTERN CGColorRef __nullable CGColorCreateCopy(CGColorRef cg_nullable color)
  API_AVAILABLE(macos(10.3), ios(2.0));

/* Create a copy of `color' with alpha set to `alpha'. */

CG_EXTERN CGColorRef __nullable CGColorCreateCopyWithAlpha(CGColorRef cg_nullable color,
  CGFloat alpha) API_AVAILABLE(macos(10.3), ios(2.0));

/* Create a copy of `color' by matching existing color to destination color space. */

CG_EXTERN CGColorRef __nullable CGColorCreateCopyByMatchingToColorSpace(cg_nullable CGColorSpaceRef,
  CGColorRenderingIntent intent, CGColorRef cg_nullable color, __nullable CFDictionaryRef options)
  API_AVAILABLE(macos(10.11), ios(9.0));

/* Equivalent to `CFRetain(color)', except it doesn't crash (as CFRetain
   does) if `color' is NULL. */

CG_EXTERN CGColorRef cg_nullable CGColorRetain(CGColorRef cg_nullable color)
  API_AVAILABLE(macos(10.3), ios(2.0));

/* Equivalent to `CFRelease(color)', except it doesn't crash (as CFRelease
   does) if `color' is NULL. */

CG_EXTERN void CGColorRelease(CGColorRef cg_nullable color)
  API_AVAILABLE(macos(10.3), ios(2.0));

/* Return true if `color1' is equal to `color2'; false otherwise. */

CG_EXTERN bool CGColorEqualToColor(CGColorRef cg_nullable color1, CGColorRef cg_nullable color2)
  API_AVAILABLE(macos(10.3), ios(2.0));

/* Return the number of color components (including alpha) associated with
   `color'. */

CG_EXTERN size_t CGColorGetNumberOfComponents(CGColorRef cg_nullable color)
  API_AVAILABLE(macos(10.3), ios(2.0));

/* Return the color components (including alpha) associated with `color'. */

CG_EXTERN const CGFloat * __nullable CGColorGetComponents(CGColorRef cg_nullable color)
  API_AVAILABLE(macos(10.3), ios(2.0));

/* Return the alpha component associated with `color'. */

CG_EXTERN CGFloat CGColorGetAlpha(CGColorRef cg_nullable color)
  API_AVAILABLE(macos(10.3), ios(2.0));

/* Return the color space associated with `color'. */

CG_EXTERN CGColorSpaceRef __nullable CGColorGetColorSpace(CGColorRef cg_nullable color)
  API_AVAILABLE(macos(10.3), ios(2.0));

/* Return the pattern associated with `color', if it's a color in a pattern
   color space; NULL otherwise. */

CG_EXTERN CGPatternRef __nullable CGColorGetPattern(CGColorRef cg_nullable color)
  API_AVAILABLE(macos(10.3), ios(2.0));

/* Return the CFTypeID for CGColors. */

CG_EXTERN CFTypeID CGColorGetTypeID(void)
  API_AVAILABLE(macos(10.3), ios(2.0));

/*** Names of colors for use with `CGColorGetConstantColor'. ***/

/* Colors in the "Generic" gray color space. */

CG_EXTERN const CFStringRef  kCGColorWhite
API_AVAILABLE(macos(10.5), ios(14.0));

CG_EXTERN const CFStringRef  kCGColorBlack
  API_AVAILABLE(macos(10.5), ios(14.0));

CG_EXTERN const CFStringRef  kCGColorClear
  API_AVAILABLE(macos(10.5), ios(14.0));

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGCOLOR_H_ */
