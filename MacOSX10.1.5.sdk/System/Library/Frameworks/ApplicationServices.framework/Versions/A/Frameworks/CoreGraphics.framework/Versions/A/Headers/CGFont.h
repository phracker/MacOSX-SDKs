/* CoreGraphics - CGFont.h
 * Copyright (c) 1999-2001 Apple Computer, Inc.
 * All rights reserved.
 */

#ifndef CGFONT_H_
#define CGFONT_H_

typedef struct CGFont *CGFontRef;
typedef unsigned short CGFontIndex;
typedef CGFontIndex CGGlyph;

#include <CoreGraphics/CGBase.h>
#include <limits.h>

enum {
    kCGFontIndexMax = USHRT_MAX - 1,
    kCGFontIndexInvalid = USHRT_MAX,
    kCGGlyphMax = kCGFontIndexMax
};

CG_EXTERN_C_BEGIN

/*** Font creation. ***/

/* Create a CGFont using `platformFontReference', a pointer to a
 * platform-specific font reference.  For MacOS X, `platformFontReference'
 * should be a pointer to an ATSFontRef. */

CG_EXTERN CGFontRef CGFontCreateWithPlatformFont(void *platformFontReference);

/*** Retain & release. ***/

/* Increment the retain count of `font' and return it.  All fonts are
 * created with an initial retain count of 1. */

CG_EXTERN CGFontRef CGFontRetain(CGFontRef font);

/* Decrement the retain count of `font'.  If the retain count reaches 0,
 * then release it and any associated resources. */

CG_EXTERN void CGFontRelease(CGFontRef font);

CG_EXTERN_C_END

/* Obsolete; don't use these. */

enum {
    CGGlyphMin = 0,
    CGGlyphMax = kCGGlyphMax
};

#endif	/* CGFONT_H_ */
