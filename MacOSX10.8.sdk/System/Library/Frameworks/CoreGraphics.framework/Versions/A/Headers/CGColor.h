/* CoreGraphics - CGColor.h
 * Copyright (c) 2003-2008 Apple Inc.
 * All rights reserved. */

#ifndef CGCOLOR_H_
#define CGCOLOR_H_

typedef struct CGColor *CGColorRef;

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGColorSpace.h>
#include <CoreGraphics/CGPattern.h>

/* Create a color in the color space `space' with color components
   (including alpha) specified by `components'. `space' may be any color
   space except a pattern color space. */

CG_EXTERN CGColorRef CGColorCreate(CGColorSpaceRef space,
  const CGFloat components[]) CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Create a color in the "Generic" gray color space. */

CG_EXTERN CGColorRef CGColorCreateGenericGray(CGFloat gray, CGFloat alpha)
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);

/* Create a color in the "Generic" RGB color space. */

CG_EXTERN CGColorRef CGColorCreateGenericRGB(CGFloat red, CGFloat green,
  CGFloat blue, CGFloat alpha) CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);

/* Create a color in the "Generic" CMYK color space. */

CG_EXTERN CGColorRef CGColorCreateGenericCMYK(CGFloat cyan, CGFloat magenta,
  CGFloat yellow, CGFloat black, CGFloat alpha)
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);

/* Return a constant color. As `CGColorGetConstantColor' is not a "Copy" or
   "Create" function, it does not necessarily return a new reference each
   time it's called. As a consequence, you should not release the returned
   value. However, colors returned from `CGColorGetConstantColor' can be
   retained and released in a properly nested fashion, just like any other
   CF type. */

CG_EXTERN CGColorRef CGColorGetConstantColor(CFStringRef colorName)
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);

/* Create a color in color space `space' with pattern `pattern' and
   components `components'. `space' must be a pattern color space. */

CG_EXTERN CGColorRef CGColorCreateWithPattern(CGColorSpaceRef space,
  CGPatternRef pattern, const CGFloat components[])
  CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Create a copy of `color'. */

CG_EXTERN CGColorRef CGColorCreateCopy(CGColorRef color)
  CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Create a copy of `color' with alpha set to `alpha'. */

CG_EXTERN CGColorRef CGColorCreateCopyWithAlpha(CGColorRef color,
  CGFloat alpha) CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Equivalent to `CFRetain(color)', except it doesn't crash (as CFRetain
   does) if `color' is NULL. */

CG_EXTERN CGColorRef CGColorRetain(CGColorRef color)
  CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Equivalent to `CFRelease(color)', except it doesn't crash (as CFRelease
   does) if `color' is NULL. */

CG_EXTERN void CGColorRelease(CGColorRef color)
  CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Return true if `color1' is equal to `color2'; false otherwise. */

CG_EXTERN bool CGColorEqualToColor(CGColorRef color1, CGColorRef color2)
  CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Return the number of color components (including alpha) associated with
   `color'. */

CG_EXTERN size_t CGColorGetNumberOfComponents(CGColorRef color)
  CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Return the color components (including alpha) associated with `color'. */

CG_EXTERN const CGFloat *CGColorGetComponents(CGColorRef color)
  CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Return the alpha component associated with `color'. */

CG_EXTERN CGFloat CGColorGetAlpha(CGColorRef color)
  CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Return the color space associated with `color'. */

CG_EXTERN CGColorSpaceRef CGColorGetColorSpace(CGColorRef color)
  CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Return the pattern associated with `color', if it's a color in a pattern
   color space; NULL otherwise. */

CG_EXTERN CGPatternRef CGColorGetPattern(CGColorRef color)
  CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Return the CFTypeID for CGColors. */

CG_EXTERN CFTypeID CGColorGetTypeID(void)
  CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/*** Names of colors for use with `CGColorGetConstantColor'. ***/

/* Colors in the "Generic" gray color space. */

CG_EXTERN const CFStringRef kCGColorWhite
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);

CG_EXTERN const CFStringRef kCGColorBlack
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);

CG_EXTERN const CFStringRef kCGColorClear
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);

#endif /* CGCOLOR_H_ */
