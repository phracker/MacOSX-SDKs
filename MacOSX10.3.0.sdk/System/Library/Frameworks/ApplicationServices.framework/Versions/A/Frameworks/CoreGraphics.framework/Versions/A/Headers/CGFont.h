/* CoreGraphics - CGFont.h
 * Copyright (c) 1999-2002 Apple Computer, Inc.
 * All rights reserved.
 */

#ifndef CGFONT_H_
#define CGFONT_H_

typedef struct CGFont *CGFontRef;
typedef unsigned short CGFontIndex;
typedef CGFontIndex CGGlyph;

#include <CoreGraphics/CGBase.h>
#include <CoreFoundation/CFBase.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>

enum {
    kCGFontIndexMax = ((1 << 16) - 2),		/* Always <= USHRT_MAX - 1 */
    kCGFontIndexInvalid = ((1 << 16) - 1),	/* Always <= USHRT_MAX */
    kCGGlyphMax = kCGFontIndexMax
};

CG_EXTERN_C_BEGIN

/* Return the CFTypeID for CGFontRefs. */

CG_EXTERN CFTypeID CGFontGetTypeID(void);

/* Create a CGFont using `platformFontReference', a pointer to a
 * platform-specific font reference.  For MacOS X, `platformFontReference'
 * should be a pointer to an ATSFontRef. */

CG_EXTERN CGFontRef CGFontCreateWithPlatformFont(void *platformFontReference);

/* Equivalent to `CFRetain(font)'. */

CG_EXTERN CGFontRef CGFontRetain(CGFontRef font);

/* Equivalent to `CFRelease(font)'. */

CG_EXTERN void CGFontRelease(CGFontRef font);

CG_EXTERN_C_END

/* Obsolete; don't use these. */

enum {
    CGGlyphMin = 0,
    CGGlyphMax = kCGGlyphMax
};

#endif	/* CGFONT_H_ */
