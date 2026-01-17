/* CoreGraphics - CGPath.h
 * Copyright (c) 2001-2002 Apple Computer, Inc.
 * All rights reserved.
 */

#ifndef CGPATH_H_
#define CGPATH_H_

typedef struct CGPath *CGMutablePathRef;
typedef const struct CGPath *CGPathRef;

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGAffineTransform.h>
#include <CoreFoundation/CFBase.h>

CG_EXTERN_C_BEGIN

/* Return the CFTypeID for CGPathRefs. */

CG_EXTERN CFTypeID CGPathGetTypeID(void);

/* Create a mutable path. */

CG_EXTERN CGMutablePathRef CGPathCreateMutable(void);

/* Create a copy of `path'. */

CG_EXTERN CGPathRef CGPathCreateCopy(CGPathRef path);

/* Create a mutable copy of `path'. */

CG_EXTERN CGMutablePathRef CGPathCreateMutableCopy(CGPathRef path);

/* Equivalent to `CFRetain(path)', except it doesn't crash (as CFRetain
 * does) if `path' is NULL. */

CG_EXTERN CGPathRef CGPathRetain(CGPathRef path);

/* Equivalent to `CFRelease(path)', except it doesn't crash (as CFRelease
 * does) if `path' is NULL. */

CG_EXTERN void CGPathRelease(CGPathRef path);

/* Return true if `path1' is equal to `path2'; false otherwise. */

CG_EXTERN bool CGPathEqualToPath(CGPathRef path1, CGPathRef path2);

/*** Path construction functions. ***/

/* Move the current point to `(x, y)' in `path' and begin a new subpath.
 * If `m' is non-NULL, then transform `(x, y)' by `m' first. */

CG_EXTERN void CGPathMoveToPoint(CGMutablePathRef path, const CGAffineTransform *m, float x, float y);

/* Append a straight line segment from the current point to `(x, y)' in
 * `path' and move the current point to `(x, y)'.  If `m' is non-NULL, then
 * transform `(x, y)' by `m' first. */

CG_EXTERN void CGPathAddLineToPoint(CGMutablePathRef path, const CGAffineTransform *m, float x, float y);

/* Append a quadratic curve from the current point to `(x, y)' with control
 * point `(cpx, cpy)' in `path' and move the current point to `(x, y)'.  If
 * `m' is non-NULL, then transform all points by `m' first. */

CG_EXTERN void CGPathAddQuadCurveToPoint(CGMutablePathRef path, const CGAffineTransform *m, float cpx, float cpy, float x, float y);

/* Append a cubic Bezier curve from the current point to `(x,y)' with
 * control points `(cp1x, cp1y)' and `(cp2x, cp2y)' in `path' and move the
 * current point to `(x, y)'. If `m' is non-NULL, then transform all points
 * by `m' first. */

CG_EXTERN void CGPathAddCurveToPoint(CGMutablePathRef path, const CGAffineTransform *m, float cp1x, float cp1y, float cp2x, float cp2y, float x, float y);

/* Append a line from the current point to the starting point of the
 * current subpath of `path' and end the subpath. */

CG_EXTERN void CGPathCloseSubpath(CGMutablePathRef path);

/*** Path construction convenience functions. ***/

/* Add `rect' to `path'. If `m' is non-NULL, then first transform `rect' by
 * `m' before adding it to `path'. */

CG_EXTERN void CGPathAddRect(CGMutablePathRef path, const CGAffineTransform *m, CGRect rect);

/* Add each rectangle specified by `rects', an array of `count' CGRects, to
 * `path'. If `m' is non-NULL, then first transform each rectangle by `m'
 * before adding it to `path'. */

CG_EXTERN void CGPathAddRects(CGMutablePathRef path, const CGAffineTransform *m, const CGRect rects[], size_t count);

/* Move to the first element of `points', an array of `count' CGPoints, and
 * append a line from each point to the next point in `points'.  If `m' is
 * non-NULL, then first transform each point by `m'. */

CG_EXTERN void CGPathAddLines(CGMutablePathRef path, const CGAffineTransform *m, const CGPoint points[], size_t count);

/* Add an arc of a circle to `path', possibly preceded by a straight line
 * segment. The arc is approximated by a sequence of cubic Bezier
 * curves. `(x, y)' is the center of the arc; `radius' is its radius;
 * `startAngle' is the angle to the first endpoint of the arc; `endAngle'
 * is the angle to the second endpoint of the arc; and `clockwise' is true
 * if the arc is to be drawn clockwise, false otherwise.  `startAngle' and
 * `endAngle' are measured in radians.  If `m' is non-NULL, then the
 * constructed Bezier curves representing the arc will be transformed by
 * `m' before they are added to `path'. */

CG_EXTERN void CGPathAddArc(CGMutablePathRef path, const CGAffineTransform *m, float x, float y, float radius, float startAngle, float endAngle, bool clockwise);

/* Add an arc of a circle to `path', possibly preceded by a straight line
 * segment.  The arc is approximated by a sequence of cubic Bezier curves.
 * `radius' is the radius of the arc.  The resulting arc is tangent to the
 * line from the current point of `path' to `(x1, y1)', and the line from
 * `(x1, y1)' to `(x2, y2)'.  If `m' is non-NULL, then the constructed
 * Bezier curves representing the arc will be transformed by `m' before
 * they are added to `path'. */

CG_EXTERN void CGPathAddArcToPoint(CGMutablePathRef path, const CGAffineTransform *m, float x1, float y1, float x2, float y2, float radius);

/* Add `path2' to `path1'. If `m' is non-NULL, then the points in `path2'
* will be transformed by `m' before they are added to `path1'.*/

CG_EXTERN void CGPathAddPath(CGMutablePathRef path1, const CGAffineTransform *m, CGPathRef path2);

/*** Path information functions. ***/

/* Return true if `path' contains no elements, false otherwise. */

CG_EXTERN bool CGPathIsEmpty(CGPathRef path);

/* Return true if `path' represents a rectangle, false otherwise. */

CG_EXTERN bool CGPathIsRect(CGPathRef path, CGRect *rect);

/* Return the current point of the current subpath of `path'.  If there is
 * no current point, then return CGPointZero. */

CG_EXTERN CGPoint CGPathGetCurrentPoint(CGPathRef path);

/* Return the bounding box of `path'.  The bounding box is the smallest
 * rectangle completely enclosing all points in the path, including control
 * points for Bezier and quadratic curves. If the path is empty, then
 * return CGRectNull. */

CG_EXTERN CGRect CGPathGetBoundingBox(CGPathRef path);

enum CGPathElementType {
    kCGPathElementMoveToPoint,
    kCGPathElementAddLineToPoint,
    kCGPathElementAddQuadCurveToPoint,
    kCGPathElementAddCurveToPoint,
    kCGPathElementCloseSubpath
};
typedef enum CGPathElementType CGPathElementType;

struct CGPathElement {
    CGPathElementType type;
    CGPoint *points;
};
typedef struct CGPathElement CGPathElement;

typedef void (*CGPathApplierFunction)(void *info, const CGPathElement *element);

CG_EXTERN void CGPathApply(CGPathRef path, void *info, CGPathApplierFunction function);

CG_EXTERN_C_END

#endif	/* CGPATH_H_ */
