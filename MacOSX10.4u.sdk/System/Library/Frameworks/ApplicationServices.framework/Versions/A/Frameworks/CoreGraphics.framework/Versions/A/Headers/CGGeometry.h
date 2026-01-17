/* CoreGraphics - CGGeometry.h
 * Copyright (c) 1998-2003 Apple Computer, Inc.
 * All rights reserved.
 */

#ifndef CGGEOMETRY_H_
#define CGGEOMETRY_H_

#include <CoreGraphics/CGBase.h>
#include <CoreFoundation/CFByteOrder.h>

CG_EXTERN_C_BEGIN

/* Points. */

struct CGPoint {
    float x;
    float y;
};
typedef struct CGPoint CGPoint;

/* Sizes. */

struct CGSize {
    float width;
    float height;
};
typedef struct CGSize CGSize;

/* Rectangles. */

struct CGRect {
    CGPoint origin;
    CGSize size;
};
typedef struct CGRect CGRect;

/* Rectangle edges. */

enum CGRectEdge {
    CGRectMinXEdge, CGRectMinYEdge, CGRectMaxXEdge, CGRectMaxYEdge
};
typedef enum CGRectEdge CGRectEdge;

/* The "zero" point -- equivalent to CGPointMake(0, 0). */ 

CG_EXTERN const CGPoint CGPointZero;

/* The "zero" size -- equivalent to CGSizeMake(0, 0). */ 

CG_EXTERN const CGSize CGSizeZero;

/* The "zero" rectangle -- equivalent to CGRectMake(0, 0, 0, 0). */ 

CG_EXTERN const CGRect CGRectZero;

/* The "empty" rect.  This is the rectangle returned when, for example, we
 * intersect two disjoint rectangles.  Note that the null rect is not the
 * same as the zero rect. */

CG_EXTERN const CGRect CGRectNull;

/* The infinite rectangle. */

CG_EXTERN const CGRect CGRectInfinite AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Make a point from `(x, y)'. */

CG_INLINE CGPoint CGPointMake(float x, float y);

/* Make a size from `(width, height)'. */

CG_INLINE CGSize CGSizeMake(float width, float height);

/* Make a rect from `(x, y; width, height)'. */

CG_INLINE CGRect CGRectMake(float x, float y, float width, float height);

/* Return the leftmost x-value of `rect'. */

CG_EXTERN float CGRectGetMinX(CGRect rect);

/* Return the midpoint x-value of `rect'. */

CG_EXTERN float CGRectGetMidX(CGRect rect);

/* Return the rightmost x-value of `rect'. */

CG_EXTERN float CGRectGetMaxX(CGRect rect);

/* Return the bottommost y-value of `rect'. */

CG_EXTERN float CGRectGetMinY(CGRect rect);

/* Return the midpoint y-value of `rect'. */

CG_EXTERN float CGRectGetMidY(CGRect rect);

/* Return the topmost y-value of `rect'. */

CG_EXTERN float CGRectGetMaxY(CGRect rect);

/* Return the width of `rect'. */

CG_EXTERN float CGRectGetWidth(CGRect rect);

/* Return the height of `rect'. */

CG_EXTERN float CGRectGetHeight(CGRect rect);

/* Return 1 if `point1' and `point2' are the same, 0 otherwise. */

CG_EXTERN int CGPointEqualToPoint(CGPoint point1, CGPoint point2);

/* Return 1 if `size1' and `size2' are the same, 0 otherwise. */

CG_EXTERN int CGSizeEqualToSize(CGSize size1, CGSize size2);

/* Return 1 if `rect1' and `rect2' are the same, 0 otherwise. */

CG_EXTERN int CGRectEqualToRect(CGRect rect1, CGRect rect2);

/* Standardize `rect' -- i.e., convert it to an equivalent rect which has
 * positive width and height. */

CG_EXTERN CGRect CGRectStandardize(CGRect rect);

/* Return 1 if `rect' is empty -- i.e., if it has zero width or height.  A
 * null rect is defined to be empty. */

CG_EXTERN int CGRectIsEmpty(CGRect rect);

/* Return 1 if `rect' is null -- e.g., the result of intersecting two
 * disjoint rectangles is a null rect. */

CG_EXTERN int CGRectIsNull(CGRect rect);

/* Return true if `rect' is the infinite rectangle, false otherwise. */

CG_EXTERN bool CGRectIsInfinite(CGRect rect) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Inset `rect' by `(dx, dy)' -- i.e., offset its origin by `(dx, dy)', and
 * decrease its size by `(2*dx, 2*dy)'. */

CG_EXTERN CGRect CGRectInset(CGRect rect, float dx, float dy);

/* Expand `rect' to the smallest rect containing it with integral origin
 * and size. */

CG_EXTERN CGRect CGRectIntegral(CGRect rect);

/* Return the union of `r1' and `r2'. */

CG_EXTERN CGRect CGRectUnion(CGRect r1, CGRect r2);

/* Return the intersection of `r1' and `r2'.  This may return a null
 * rect. */

CG_EXTERN CGRect CGRectIntersection(CGRect r1, CGRect r2);

/* Offset `rect' by `(dx, dy)'. */

CG_EXTERN CGRect CGRectOffset(CGRect rect, float dx, float dy);

/* Make two new rectangles, `slice' and `remainder', by dividing `rect'
 * with a line that's parallel to one of its sides, specified by `edge' --
 * either `CGRectMinXEdge', `CGRectMinYEdge', `CGRectMaxXEdge', or
 * `CGRectMaxYEdge'.  The size of `slice' is determined by `amount', which
 * measures the distance from the specified edge. */

CG_EXTERN void CGRectDivide(CGRect rect, CGRect *slice, CGRect *remainder, float amount, CGRectEdge edge);

/* Return 1 if `point' is contained in `rect', 0 otherwise. */

CG_EXTERN int CGRectContainsPoint(CGRect rect, CGPoint point);

/* Return 1 if `rect2' is contained in `rect1', 0 otherwise.  `rect2' is
 * contained in `rect1' if the union of `rect1' and `rect2' is equal to
 * `rect1'. */

CG_EXTERN int CGRectContainsRect(CGRect rect1, CGRect rect2);

/* Return 1 if `rect1' intersects `rect2', 0 otherwise.  `rect1' intersects
 * `rect2' if the intersection of `rect1' and `rect2' is not the null
 * rect. */

CG_EXTERN int CGRectIntersectsRect(CGRect rect1, CGRect rect2);

/*** Definitions of inline functions. ***/

CG_INLINE CGPoint CGPointMake(float x, float y)
{
    CGPoint p; p.x = x; p.y = y; return p;
}

CG_INLINE CGSize CGSizeMake(float width, float height)
{
    CGSize size; size.width = width; size.height = height; return size;
}

CG_INLINE CGRect CGRectMake(float x, float y, float width, float height)
{
    CGRect rect;
    rect.origin.x = x; rect.origin.y = y;
    rect.size.width = width; rect.size.height = height;
    return rect;
}

CG_EXTERN_C_END

#endif	/* CGGEOMETRY_H_ */
