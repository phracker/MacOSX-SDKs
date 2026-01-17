/* CoreGraphics - CGDirectPalette.h
   Copyright (c) 2000-2011 Apple Inc.
   All rights reserved. */

#ifndef CGDIRECTPALETTE_H_
#define CGDIRECTPALETTE_H_

#include <CoreGraphics/CGDirectDisplay.h>

/* These types are deprecated; don't use them. */

typedef float CGPaletteBlendFraction;

struct CGDeviceColor {
  float red;
  float green;
  float blue;
};
typedef struct CGDeviceColor CGDeviceColor;

struct CGDeviceByteColor {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
};
typedef struct CGDeviceByteColor CGDeviceByteColor;

/* These functions are deprecated; do not use them. */

CG_EXTERN CGDirectPaletteRef CGPaletteCreateDefaultColorPalette(void)
  CG_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);

CG_EXTERN CGDirectPaletteRef CGPaletteCreateWithDisplay(CGDirectDisplayID
  display)
  CG_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);

CG_EXTERN CGDirectPaletteRef CGPaletteCreateWithCapacity(uint32_t capacity)
  CG_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);

CG_EXTERN CGDirectPaletteRef CGPaletteCreateWithSamples(CGDeviceColor *samples,
  uint32_t count)
  CG_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);

CG_EXTERN CGDirectPaletteRef CGPaletteCreateWithByteSamples(CGDeviceByteColor
  *samples, uint32_t count)
  CG_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);

CG_EXTERN void CGPaletteRelease(CGDirectPaletteRef palette)
  CG_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);

CG_EXTERN CGDeviceColor CGPaletteGetColorAtIndex(CGDirectPaletteRef palette,
  uint32_t index)
  CG_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);

CG_EXTERN uint32_t CGPaletteGetIndexForColor(CGDirectPaletteRef palette,
  CGDeviceColor color)
  CG_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);

CG_EXTERN uint32_t CGPaletteGetNumberOfSamples(CGDirectPaletteRef palette)
  CG_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);

CG_EXTERN void CGPaletteSetColorAtIndex(CGDirectPaletteRef palette,
  CGDeviceColor color, uint32_t index)
  CG_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);

CG_EXTERN CGDirectPaletteRef CGPaletteCreateCopy(CGDirectPaletteRef palette)
  CG_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);

CG_EXTERN bool CGPaletteIsEqualToPalette(CGDirectPaletteRef palette1,
  CGDirectPaletteRef palette2)
  CG_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);

CG_EXTERN CGDirectPaletteRef CGPaletteCreateFromPaletteBlendedWithColor(
  CGDirectPaletteRef palette, CGPaletteBlendFraction fraction,
  CGDeviceColor color)
  CG_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);

#endif /* CGDIRECTPALETTE_H_ */
