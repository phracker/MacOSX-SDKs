/*
 *  CGDirectPalette.h
 *  CoreGraphics
 *
 *  Copyright (c) 2000 Apple Computer, Inc. All rights reserved.
 *
 */

#ifndef __CGDIRECT_PALETTE_H__
#define __CGDIRECT_PALETTE_H__ 1

#include <CoreGraphics/CGDirectDisplay.h>

CG_EXTERN_C_BEGIN

typedef float CGPaletteBlendFraction; /* A value between 0.0 and 1.0 */

/*
 * Convenient device color representation
 *
 * Values should be in the range from 0.0 to 1.0, where 0.0 is black, and 1.0
 * is full on for each channel.
 */
struct _CGDeviceColor
{
    float red;
    float green;
    float blue;
};
typedef struct _CGDeviceColor CGDeviceColor;

struct _CGDeviceByteColor
{
    CGByteValue red;
    CGByteValue green;
    CGByteValue blue;
};
typedef struct _CGDeviceByteColor CGDeviceByteColor;

/*
 * Create a new palette object representing the default 8 bit color palette.
 * Release the palette using CGPaletteRelease().
 */
CGDirectPaletteRef CGPaletteCreateDefaultColorPalette(void);

/*
 * Create a copy of the display's current palette, if any.
 * Returns NULL if the current display mode does not support a palette.
 * Release the palette using CGPaletteRelease().
 */
CGDirectPaletteRef CGPaletteCreateWithDisplay(CGDirectDisplayID display);

/*
 * Create a new palette with a capacity as specified.  Entries are initialized from
 * the default color palette.  Release the palette using CGPaletteRelease().
 */
CGDirectPaletteRef CGPaletteCreateWithCapacity( CGTableCount capacity );

/*
 * Create a new palette with a capacity and contents as specified.
 * Release the palette using CGPaletteRelease().
 */
CGDirectPaletteRef CGPaletteCreateWithSamples(CGDeviceColor * sampleTable, CGTableCount sampleCount);

/*
 * Convenience function:
 * Create a new palette with a capacity and contents as specified.
 * Release the palette using CGPaletteRelease().
 */
CGDirectPaletteRef CGPaletteCreateWithByteSamples(CGDeviceByteColor * sampleTable, CGTableCount sampleCount);

/*
 * Release a palette
 */
void CGPaletteRelease( CGDirectPaletteRef palette );

/*
 * Get the color value at the specified index
 */
CGDeviceColor CGPaletteGetColorAtIndex(CGDirectPaletteRef palette, CGTableCount index);

/*
 * Get the index for the specified color value
 * The index returned is for a palette color with the
 * lowest RMS error to the specified color.
 */
CGTableCount CGPaletteGetIndexForColor(CGDirectPaletteRef palette, CGDeviceColor color);

/*
 * Get the number of samples in the palette
 */
CGTableCount CGPaletteGetNumberOfSamples(CGDirectPaletteRef palette);


/*
 * Set the color value at the specified index
 */
void CGPaletteSetColorAtIndex(CGDirectPaletteRef palette, CGDeviceColor color, CGTableCount index);

/*
 * Copy a palette
 */
CGDirectPaletteRef CGPaletteCreateCopy(CGDirectPaletteRef palette);

/*
 * Compare two palettes
 */
Boolean CGPaletteIsEqualToPalette(CGDirectPaletteRef palette1, CGDirectPaletteRef palette2);

/*
 * Create a new palette blended with a fraction of a device color.
 * Free the resulting palette with CGPaletteRelease()
 */
CGDirectPaletteRef CGPaletteCreateFromPaletteBlendedWithColor(
                                          CGDirectPaletteRef palette,
                                          CGPaletteBlendFraction fraction,
                                          CGDeviceColor color);

CG_EXTERN_C_END

#endif /* __CGDIRECT_PALETTE_H__ */

