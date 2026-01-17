/* CoreGraphics - CGAffineTransform.h
 * Copyright (c) 1998-2005 Apple Computer, Inc.
 * All rights reserved.
 */

#ifndef CGAFFINETRANSFORM_H_
#define CGAFFINETRANSFORM_H_

typedef struct CGAffineTransform CGAffineTransform;

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGGeometry.h>

CG_EXTERN_C_BEGIN

struct CGAffineTransform {
    CGFloat a, b, c, d;
    CGFloat tx, ty;
};

/* The identity transform: [ 1 0 0 1 0 0 ]. */

CG_EXTERN const CGAffineTransform CGAffineTransformIdentity;

/* Return the transform [ a b c d tx ty ]. */

CG_EXTERN CGAffineTransform CGAffineTransformMake(CGFloat a, CGFloat b, CGFloat c, CGFloat d, CGFloat tx, CGFloat ty);

/* Return a transform which translates by `(tx, ty)':
 *   t' = [ 1 0 0 1 tx ty ] */

CG_EXTERN CGAffineTransform CGAffineTransformMakeTranslation(CGFloat tx, CGFloat ty);

/* Return a transform which scales by `(sx, sy)':
 *   t' = [ sx 0 0 sy 0 0 ] */

CG_EXTERN CGAffineTransform CGAffineTransformMakeScale(CGFloat sx, CGFloat sy);

/* Return a transform which rotates by `angle' radians:
 *   t' = [ cos(angle) sin(angle) -sin(angle) cos(angle) 0 0 ] */

CG_EXTERN CGAffineTransform CGAffineTransformMakeRotation(CGFloat angle);

/* Return true if `t' is the identity transform, false otherwise. */

CG_EXTERN bool CGAffineTransformIsIdentity(CGAffineTransform t) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Translate `t' by `(tx, ty)' and return the result:
 *   t' = [ 1 0 0 1 tx ty ] * t */

CG_EXTERN CGAffineTransform CGAffineTransformTranslate(CGAffineTransform t, CGFloat tx, CGFloat ty);

/* Scale `t' by `(sx, sy)' and return the result:
 *   t' = [ sx 0 0 sy 0 0 ] * t */

CG_EXTERN CGAffineTransform CGAffineTransformScale(CGAffineTransform t, CGFloat sx, CGFloat sy);

/* Rotate `t' by `angle' radians and return the result:
 *   t' =  [ cos(angle) sin(angle) -sin(angle) cos(angle) 0 0 ] * t */

CG_EXTERN CGAffineTransform CGAffineTransformRotate(CGAffineTransform t, CGFloat angle);

/* Invert `t' and return the result. If `t' has zero determinant, then `t'
 * is returned unchanged. */

CG_EXTERN CGAffineTransform CGAffineTransformInvert(CGAffineTransform t);

/* Concatenate `t2' to `t1' and return the result:
 *   t' = t1 * t2 */

CG_EXTERN CGAffineTransform CGAffineTransformConcat(CGAffineTransform t1, CGAffineTransform t2);

/* Return true if `t1' and `t2' are equal, false otherwise. */

CG_EXTERN bool CGAffineTransformEqualToTransform(CGAffineTransform t1, CGAffineTransform t2) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Transform `point' by `t' and return the result:
 *   p' = p * t
 * where p = [ x y 1 ]. */

CG_EXTERN CGPoint CGPointApplyAffineTransform(CGPoint point, CGAffineTransform t);

/* Transform `size' by `t' and return the result:
 *   s' = s * t
 * where s = [ width height 0 ]. */

CG_EXTERN CGSize CGSizeApplyAffineTransform(CGSize size, CGAffineTransform t);

/* Transform `rect' by `t' and return the result. Since affine transforms
 * do not preserve rectangles in general, this function returns the
 * smallest rectangle which contains the transformed corner points of
 * `rect'. If `t' consists solely of scales, flips and translations, then
 * the returned rectangle coincides with the rectangle constructed from the
 * four transformed corners. */

CG_EXTERN CGRect CGRectApplyAffineTransform(CGRect rect, CGAffineTransform t) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*** Definitions of inline functions. ***/

CG_INLINE CGAffineTransform
__CGAffineTransformMake(CGFloat a, CGFloat b, CGFloat c, CGFloat d,
    CGFloat tx, CGFloat ty)
{
    CGAffineTransform t;

    t.a = a; t.b = b; t.c = c; t.d = d; t.tx = tx; t.ty = ty;
    return t;
}

#define CGAffineTransformMake __CGAffineTransformMake

CG_INLINE CGPoint
__CGPointApplyAffineTransform(CGPoint point, CGAffineTransform t)
{
    CGPoint p;

    p.x = (CGFloat)((double)t.a * point.x + (double)t.c * point.y + t.tx);
    p.y = (CGFloat)((double)t.b * point.x + (double)t.d * point.y + t.ty);
    return p;
}

#define CGPointApplyAffineTransform __CGPointApplyAffineTransform

CG_INLINE CGSize
__CGSizeApplyAffineTransform(CGSize size, CGAffineTransform t)
{
    CGSize s;

    s.width = (CGFloat)((double)t.a * size.width + (double)t.c * size.height);
    s.height = (CGFloat)((double)t.b * size.width + (double)t.d * size.height);
    return s;
}

#define CGSizeApplyAffineTransform __CGSizeApplyAffineTransform

CG_EXTERN_C_END

#endif	/* CGAFFINETRANSFORM_H_ */
