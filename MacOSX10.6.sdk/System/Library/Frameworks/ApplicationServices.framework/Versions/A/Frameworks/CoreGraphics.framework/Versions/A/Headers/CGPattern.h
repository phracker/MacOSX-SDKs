/* CoreGraphics - CGPattern.h
 * Copyright (c) 2000-2008 Apple Inc.
 * All rights reserved. */

#ifndef CGPATTERN_H_
#define CGPATTERN_H_

typedef struct CGPattern *CGPatternRef;

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGContext.h>
#include <CoreFoundation/CFBase.h>

/* kCGPatternTilingNoDistortion: The pattern cell is not distorted when
   painted, however the spacing between pattern cells may vary by as much as
   1 device pixel.

   kCGPatternTilingConstantSpacingMinimalDistortion: Pattern cells are
   spaced consistently, however the pattern cell may be distorted by as much
   as 1 device pixel when the pattern is painted.

   kCGPatternTilingConstantSpacing: Pattern cells are spaced consistently as
   with kCGPatternTilingConstantSpacingMinimalDistortion, however the
   pattern cell may be distorted additionally to permit a more efficient
   implementation. */

enum CGPatternTiling {
    kCGPatternTilingNoDistortion,
    kCGPatternTilingConstantSpacingMinimalDistortion,
    kCGPatternTilingConstantSpacing
};
typedef enum CGPatternTiling CGPatternTiling;

/* The drawing of the pattern is delegated to the callbacks. The callbacks
   may be called one or many times to draw the pattern.
    `version' is the version number of the structure passed in as a
      parameter to the CGPattern creation functions. The structure defined
      below is version 0.
    `drawPattern' should draw the pattern in the context `c'. `info' is the
      parameter originally passed to the CGPattern creation functions.
    `releaseInfo' is called when the pattern is deallocated. */

typedef void (*CGPatternDrawPatternCallback)(void *info, CGContextRef c);
typedef void (*CGPatternReleaseInfoCallback)(void *info);

struct CGPatternCallbacks {
    unsigned int version;
    CGPatternDrawPatternCallback drawPattern;
    CGPatternReleaseInfoCallback releaseInfo;
};
typedef struct CGPatternCallbacks CGPatternCallbacks;

/* Return the CFTypeID for CGPatternRefs. */

CG_EXTERN CFTypeID CGPatternGetTypeID(void)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Create a pattern. */

CG_EXTERN CGPatternRef CGPatternCreate(void *info, CGRect bounds,
    CGAffineTransform matrix, CGFloat xStep, CGFloat yStep,
    CGPatternTiling tiling, bool isColored,
    const CGPatternCallbacks *callbacks)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);


/* Equivalent to `CFRetain(pattern)', except it doesn't crash (as CF does)
   if `pattern' is NULL. */

CG_EXTERN CGPatternRef CGPatternRetain(CGPatternRef pattern)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Equivalent to `CFRelease(pattern)', except it doesn't crash (as CF does)
   if `pattern' is NULL. */

CG_EXTERN void CGPatternRelease(CGPatternRef pattern)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

#endif	/* CGPATTERN_H_ */
