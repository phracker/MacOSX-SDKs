/* CoreGraphics - CGColor.h
 * Copyright (c) 2003-2006 Apple Computer, Inc.
 * All rights reserved.
 */

#ifndef CGCOLOR_H_
#define CGCOLOR_H_

typedef struct CGColor *CGColorRef;

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGColorSpace.h>
#include <CoreGraphics/CGPattern.h>

CG_EXTERN_C_BEGIN

/* Create a color in the color space `space' with color components
 * (including alpha) specified by `components'. `space' may be any color
 * space except a pattern color space. */

CG_EXTERN CGColorRef CGColorCreate(CGColorSpaceRef space, const CGFloat components[]) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Create a color in the "Generic" gray color space. */

CG_EXTERN CGColorRef CGColorCreateGenericGray(CGFloat gray, CGFloat alpha) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Create a color in the "Generic" RGB color space. */

CG_EXTERN CGColorRef CGColorCreateGenericRGB(CGFloat red, CGFloat green, CGFloat blue, CGFloat alpha) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Create a color in the "Generic" CMYK color space. */

CG_EXTERN CGColorRef CGColorCreateGenericCMYK(CGFloat cyan, CGFloat magenta, CGFloat yellow, CGFloat black, CGFloat alpha) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Return a constant color. As CGColorGetConstantColor is not a "Copy" or
 * "Create" function, it does not necessarily return a new reference each
 * time it's called. As a consequence, you should not release the returned
 * value. However, colors returned from CGColorGetConstantColor can be
 * retained and released in a properly nested fashion, just like any other
 * CF type. */

CG_EXTERN CGColorRef CGColorGetConstantColor(CFStringRef colorName) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Create a color in color space `space' with pattern `pattern' and
 * components `components'. `space' must be a pattern color space. */

CG_EXTERN CGColorRef CGColorCreateWithPattern(CGColorSpaceRef space, CGPatternRef pattern, const CGFloat components[]) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Create a copy of `color'. */

CG_EXTERN CGColorRef CGColorCreateCopy(CGColorRef color) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Create a copy of `color' with alpha set to `alpha'. */

CG_EXTERN CGColorRef CGColorCreateCopyWithAlpha(CGColorRef color, CGFloat alpha) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Equivalent to `CFRetain(color)', except it doesn't crash (as CFRetain
 * does) if `color' is NULL. */

CG_EXTERN CGColorRef CGColorRetain(CGColorRef color) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Equivalent to `CFRelease(color)', except it doesn't crash (as CFRelease
 * does) if `color' is NULL. */

CG_EXTERN void CGColorRelease(CGColorRef color) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Return true if `color1' is equal to `color2'; false otherwise. */

CG_EXTERN bool CGColorEqualToColor(CGColorRef color1, CGColorRef color2) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Return the number of color components (including alpha) associated with
 * `color'. */

CG_EXTERN size_t CGColorGetNumberOfComponents(CGColorRef color) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Return the color components (including alpha) associated with
 * `color'. */

CG_EXTERN const CGFloat *CGColorGetComponents(CGColorRef color) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Return the alpha component associated with `color'. */

CG_EXTERN CGFloat CGColorGetAlpha(CGColorRef color) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Return the color space associated with `color'. */

CG_EXTERN CGColorSpaceRef CGColorGetColorSpace(CGColorRef color) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Return the pattern associated with `color', if it's a color in a pattern
 * color space; NULL otherwise. */

CG_EXTERN CGPatternRef CGColorGetPattern(CGColorRef color) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Return the CFTypeID for CGColors. */

CG_EXTERN CFTypeID CGColorGetTypeID(void) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*** Names of colors for use with `CGColorGetConstantColor'. ***/

/* Colors in the "Generic" gray color space. */

CG_EXTERN const CFStringRef kCGColorWhite AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CG_EXTERN const CFStringRef kCGColorBlack AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CG_EXTERN const CFStringRef kCGColorClear AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

CG_EXTERN_C_END

#endif	/* CGCOLOR_H_ */
