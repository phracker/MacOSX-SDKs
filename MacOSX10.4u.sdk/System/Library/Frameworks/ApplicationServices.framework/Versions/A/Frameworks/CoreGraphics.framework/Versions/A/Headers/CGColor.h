/* CoreGraphics - CGColor.h
 * Copyright (c) 2003 Apple Computer, Inc.
 * All rights reserved.
 */

#ifndef CGCOLOR_H_
#define CGCOLOR_H_

typedef struct CGColor *CGColorRef;

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGColorSpace.h>
#include <CoreGraphics/CGPattern.h>

CG_EXTERN_C_BEGIN

/* Return the CFTypeID for CGColors. */

CG_EXTERN CFTypeID CGColorGetTypeID(void) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Create a color in colorspace `colorspace' with color components
 * (including alpha) specified by `components'.  `colorspace' may be any
 * colorspace except a pattern colorspace. */

CG_EXTERN CGColorRef CGColorCreate(CGColorSpaceRef colorspace, const float components[]) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Create a color in colorspace `colorspace' with pattern `pattern' and
 * components `components'.  `colorspace' must be a pattern colorspace. */

CG_EXTERN CGColorRef CGColorCreateWithPattern(CGColorSpaceRef colorspace, CGPatternRef pattern, const float components[]) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Create a copy of `color'. */

CG_EXTERN CGColorRef CGColorCreateCopy(CGColorRef color) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Create a copy of `color' with alpha set to `alpha'. */

CG_EXTERN CGColorRef CGColorCreateCopyWithAlpha(CGColorRef color, float alpha) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

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

CG_EXTERN const float *CGColorGetComponents(CGColorRef color) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Return the alpha component associated with `color'. */

CG_EXTERN float CGColorGetAlpha(CGColorRef color) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Return the colorspace associated with `color'. */

CG_EXTERN CGColorSpaceRef CGColorGetColorSpace(CGColorRef color) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Return the pattern associated with `color', if it's a color in a pattern
 * colorspace; NULL otherwise. */

CG_EXTERN CGPatternRef CGColorGetPattern(CGColorRef color) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

CG_EXTERN_C_END

#endif	/* CGCOLOR_H_ */
