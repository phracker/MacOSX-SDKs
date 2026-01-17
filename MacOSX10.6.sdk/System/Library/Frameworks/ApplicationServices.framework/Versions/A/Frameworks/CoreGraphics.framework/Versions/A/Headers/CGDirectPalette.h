/* CoreGraphics - CGDirectPalette.h
   Copyright (c) 2000-2008 Apple Inc.
   All rights reserved. */

#ifndef CGDIRECTPALETTE_H_
#define CGDIRECTPALETTE_H_

#include <CoreGraphics/CGDirectDisplay.h>

/* A value in the interval [0, 1]. */
typedef float CGPaletteBlendFraction;

/* A color in a display palette. Values should be in the interval [0, 1]
   where 0 is no color and 1 is full intensity. */

struct CGDeviceColor {
  float red;
  float green;
  float blue;
};
typedef struct CGDeviceColor CGDeviceColor;

/* A color in a display palette, using 8-bit integer components. Values
   should be in the interval [0, 255] where 0 is no color and 255 is full
   intensity. */

struct CGDeviceByteColor {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
};
typedef struct CGDeviceByteColor CGDeviceByteColor;

/* Create a new display palette representing the default 8-bit color
   palette. */

CG_EXTERN CGDirectPaletteRef CGPaletteCreateDefaultColorPalette(void)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Return a copy of the current palette of `display', or NULL if the current
   display mode does not support a palette. */

CG_EXTERN CGDirectPaletteRef CGPaletteCreateWithDisplay(CGDirectDisplayID
  display) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Create a new display palette with the specified capacity. The new palette
   is initialized from the default color palette. */

CG_EXTERN CGDirectPaletteRef CGPaletteCreateWithCapacity(uint32_t capacity)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Create a new palette with the specified capacity and contents. */

CG_EXTERN CGDirectPaletteRef CGPaletteCreateWithSamples(CGDeviceColor *samples,
  uint32_t count) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Create a new palette with the specified capacity and contents. */

CG_EXTERN CGDirectPaletteRef CGPaletteCreateWithByteSamples(CGDeviceByteColor
  *samples, uint32_t count) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Release a palette. */

CG_EXTERN void CGPaletteRelease(CGDirectPaletteRef palette)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Return the color value at `index' in `palette'. */

CG_EXTERN CGDeviceColor CGPaletteGetColorAtIndex(CGDirectPaletteRef palette,
  uint32_t index) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Return the index of the color in `palette' which most closely matches the
   specified color value `color'. */

CG_EXTERN uint32_t CGPaletteGetIndexForColor(CGDirectPaletteRef palette,
  CGDeviceColor color) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Return the number of samples in `palette'. */

CG_EXTERN uint32_t CGPaletteGetNumberOfSamples(CGDirectPaletteRef palette)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Set the color value of `palette' at `index' to `color'. */

CG_EXTERN void CGPaletteSetColorAtIndex(CGDirectPaletteRef palette,
  CGDeviceColor color, uint32_t index)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Create a copy of `palette'. */

CG_EXTERN CGDirectPaletteRef CGPaletteCreateCopy(CGDirectPaletteRef palette)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Return true if `palette1' is equal to `palette2', false otherwise. */

CG_EXTERN bool CGPaletteIsEqualToPalette(CGDirectPaletteRef palette1,
  CGDirectPaletteRef palette2) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Return a new tinted display palette, derived from `palette' blended with
   `color' with blend intensity specified by `fraction'. */
  
CG_EXTERN CGDirectPaletteRef CGPaletteCreateFromPaletteBlendedWithColor(
  CGDirectPaletteRef palette, CGPaletteBlendFraction fraction,
  CGDeviceColor color) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

#endif /* CGDIRECTPALETTE_H_ */
