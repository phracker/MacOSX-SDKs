/* CoreGraphics - CGPattern.h
 * Copyright (c) 2000-2001 Apple Computer, Inc.
 * All rights reserved.
 */

#ifndef CGPATTERN_H_
#define CGPATTERN_H_

typedef struct CGPattern *CGPatternRef;

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGContext.h>

/* kCGPatternTilingNoDistortion: The pattern cell is not distorted when
 * painted, however the spacing between pattern cells may vary by as much
 * as 1 device pixel.
 *
 * kCGPatternTilingConstantSpacingMinimalDistortion: Pattern cells are
 * spaced consistently, however the pattern cell may be distorted by as
 * much as 1 device pixel when the pattern is painted.
 *
 * kCGPatternTilingConstantSpacing: Pattern cells are spaced consistently
 * as with kCGPatternTilingConstantSpacingMinimalDistortion, however the
 * pattern cell may be distorted additionally to permit a more efficient
 * implementation. */

enum CGPatternTiling {
    kCGPatternTilingNoDistortion,
    kCGPatternTilingConstantSpacingMinimalDistortion,
    kCGPatternTilingConstantSpacing
};
typedef enum CGPatternTiling CGPatternTiling;

CG_EXTERN_C_BEGIN

/* The drawing of the pattern is delegated to the callbacks.  The callbacks
 * may be called one or many times to draw the pattern.
 *
 * `version' is the version number of the structure passed in as a
 * parameter to the CGPattern creation functions. The structure defined
 * below is version 0.
 *
 * `drawPattern' should draw the pattern in the context `c'. `info' is the
 * parameter originally passed to the CGPattern creation functions.
 *
 * `releaseInfo' is called when the pattern is deallocated. */

struct CGPatternCallbacks {
    unsigned int version;
    void (*drawPattern)(void *info, CGContextRef c);
    void (*releaseInfo)(void *info);
};
typedef struct CGPatternCallbacks CGPatternCallbacks;

/* Create a pattern. */

CG_EXTERN CGPatternRef CGPatternCreate(void *info, CGRect bounds, CGAffineTransform matrix, float xStep, float yStep, CGPatternTiling tiling, int isColored, const CGPatternCallbacks *callbacks);

/* Increment the retain count of `pattern' and return it.  All patterns are
 * created with an initial retain count of 1. */

CG_EXTERN CGPatternRef CGPatternRetain(CGPatternRef pattern);

/* Decrement the retain count of `pattern'.  If the retain count reaches 0,
 * then free it and release any associated resources. */

CG_EXTERN void CGPatternRelease(CGPatternRef pattern);

CG_EXTERN_C_END

#endif	/* CGPATTERN_H_ */
