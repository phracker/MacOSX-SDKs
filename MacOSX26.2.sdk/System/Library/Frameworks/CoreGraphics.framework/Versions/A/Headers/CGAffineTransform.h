/* CoreGraphics - CGAffineTransform.h
   Copyright (c) 1998-2011 Apple Inc.
   All rights reserved. */

#ifndef CGAFFINETRANSFORM_H_
#define CGAFFINETRANSFORM_H_

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGGeometry.h>
#include <CoreFoundation/CFBase.h>

CF_IMPLICIT_BRIDGING_ENABLED

#ifndef CF_DEFINES_CG_TYPES
typedef struct CGAffineTransform CGAffineTransform;

struct CGAffineTransform {
  CGFloat a, b, c, d;
  CGFloat tx, ty;
};

#endif /* CF_DEFINES_CG_TYPES */

#ifndef CF_DEFINES_CGAFFINETRANSFORMCOMPONENTS
/*                      |------------------ CGAffineTransformComponents ----------------|
 *
 *      | a  b  0 |     | sx  0  0 |   |  1  0  0 |   | cos(t)  sin(t)  0 |   | 1  0  0 |
 *      | c  d  0 |  =  |  0 sy  0 | * | sh  1  0 | * |-sin(t)  cos(t)  0 | * | 0  1  0 |
 *      | tx ty 1 |     |  0  0  1 |   |  0  0  1 |   |   0       0     1 |   | tx ty 1 |
 *  CGAffineTransform      scale           shear            rotation          translation
 */

typedef struct CGAffineTransformComponents
{
    /* initial scaling in X and Y dimensions. {sx,sy} */
    /* Negative values indicate the image has been flipped in this dimension. */
    CGSize      scale;
    
    /* shear distortion (sh). Turns rectangles to parallelograms. 0 for no shear. Typically 0. */
    CGFloat     horizontalShear;
    
    /* Rotation angle in radians about the origin. (t) Sign convention for clockwise rotation */
    /* may differ between various Apple frameworks based on origin placement. Please see discussion. */
    CGFloat     rotation;

    /* Displacement from the origin (ty, ty) */
    CGVector    translation;
} CGAffineTransformComponents;

#endif /* CF_DEFINES_CGAFFINETRANSFORMCOMPONENTS */


/* The identity transform: [ 1 0 0 1 0 0 ]. */

CG_EXTERN const CGAffineTransform CGAffineTransformIdentity
  API_AVAILABLE(macos(10.0), ios(2.0));

/* Return the transform [ a b c d tx ty ]. */

CG_EXTERN CGAffineTransform CG_PURE CGAffineTransformMake(CGFloat a, CGFloat b,
  CGFloat c, CGFloat d, CGFloat tx, CGFloat ty)
  API_AVAILABLE(macos(10.0), ios(2.0));

/* Return a transform which translates by `(tx, ty)':
     t' = [ 1 0 0 1 tx ty ] */

CG_EXTERN CGAffineTransform CG_PURE CGAffineTransformMakeTranslation(CGFloat tx,
  CGFloat ty) API_AVAILABLE(macos(10.0), ios(2.0));

/* Return a transform which scales by `(sx, sy)':
     t' = [ sx 0 0 sy 0 0 ] */

CG_EXTERN CGAffineTransform CG_PURE CGAffineTransformMakeScale(CGFloat sx, CGFloat sy)
  API_AVAILABLE(macos(10.0), ios(2.0));

/* Return a transform which rotates by `angle' radians:
     t' = [ cos(angle) sin(angle) -sin(angle) cos(angle) 0 0 ] */

CG_EXTERN CGAffineTransform CG_PURE CGAffineTransformMakeRotation(CGFloat angle)
  API_AVAILABLE(macos(10.0), ios(2.0));

/* Return true if `t' is the identity transform, false otherwise. */

CG_EXTERN bool CG_PURE CGAffineTransformIsIdentity(CGAffineTransform t)
  API_AVAILABLE(macos(10.4), ios(2.0));

/* Translate `t' by `(tx, ty)' and return the result:
     t' = [ 1 0 0 1 tx ty ] * t */

CG_EXTERN CGAffineTransform CG_PURE CGAffineTransformTranslate(CGAffineTransform t,
  CGFloat tx, CGFloat ty) API_AVAILABLE(macos(10.0), ios(2.0));

/* Scale `t' by `(sx, sy)' and return the result:
     t' = [ sx 0 0 sy 0 0 ] * t */

CG_EXTERN CGAffineTransform CG_PURE CGAffineTransformScale(CGAffineTransform t,
  CGFloat sx, CGFloat sy) API_AVAILABLE(macos(10.0), ios(2.0));

/* Rotate `t' by `angle' radians and return the result:
     t' =  [ cos(angle) sin(angle) -sin(angle) cos(angle) 0 0 ] * t */

CG_EXTERN CGAffineTransform CG_PURE CGAffineTransformRotate(CGAffineTransform t,
  CGFloat angle) API_AVAILABLE(macos(10.0), ios(2.0));

/* Invert `t' and return the result. If `t' has zero determinant, then `t'
   is returned unchanged. */

CG_EXTERN CGAffineTransform CG_PURE CGAffineTransformInvert(CGAffineTransform t)
  API_AVAILABLE(macos(10.0), ios(2.0));

/* Concatenate `t2' to `t1' and return the result:
     t' = t1 * t2 */

CG_EXTERN CGAffineTransform CG_PURE CGAffineTransformConcat(CGAffineTransform t1,
  CGAffineTransform t2) API_AVAILABLE(macos(10.0), ios(2.0));

/* Return true if `t1' and `t2' are equal, false otherwise. */

CG_EXTERN bool CG_PURE CGAffineTransformEqualToTransform(CGAffineTransform t1,
  CGAffineTransform t2) API_AVAILABLE(macos(10.4), ios(2.0));

/* Transform `point' by `t' and return the result:
     p' = p * t
   where p = [ x y 1 ]. */

CG_EXTERN CGPoint CG_PURE CGPointApplyAffineTransform(CGPoint point,
  CGAffineTransform t) API_AVAILABLE(macos(10.0), ios(2.0));

/* Transform `size' by `t' and return the result:
     s' = s * t
   where s = [ width height 0 ]. */

CG_EXTERN CGSize CG_PURE CGSizeApplyAffineTransform(CGSize size, CGAffineTransform t)
  API_AVAILABLE(macos(10.0), ios(2.0));

/* Transform `rect' by `t' and return the result. Since affine transforms do
   not preserve rectangles in general, this function returns the smallest
   rectangle which contains the transformed corner points of `rect'. If `t'
   consists solely of scales, flips and translations, then the returned
   rectangle coincides with the rectangle constructed from the four
   transformed corners. */

CG_EXTERN CGRect CG_PURE CGRectApplyAffineTransform(CGRect rect, CGAffineTransform t)
  API_AVAILABLE(macos(10.4), ios(2.0));

/*! @abstract Decompose a CGAffineTransform into a scale * shear * rotation * translation
 *  @discussion This decomposition method may be used to provide insight into what a
 *              arbitrary CGAffineTransform does. This may be necessary, for example, because
 *              an algorithm would like to know what the scaling portion of a transform is before rotation,
 *              or perhaps because some part of a transform is undesired and your application would like
 *              to replace a portion of it with a different transformation.
 *
 *              Since there are many ways to make a affine transform out of other affine transforms
 *              this method can not tell us the ordering of geometric steps used to create the original
 *              CGAffineTransform. It tells us what the transform does, not how it was made.
 *
 *  @param transform        The CGAffineTransform to decompose
 *  @return A decomposed set of geometric operations, the product of which is the CGAffineTransform.  */
CG_EXTERN
 CGAffineTransformComponents CG_PURE CGAffineTransformDecompose( CGAffineTransform transform )
CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(13.0), ios(16.0));

/*! @abstract Create CGAffineTransform from scale * shear * rotation * translation CGAffineTransformComponents
 *  @param components        The set of CGAffineTransformComponents to use to create a new CGAffineTransform
 *  @return A new CGAffineTransform built from the provided components  */
CG_EXTERN
 CGAffineTransform CG_PURE CGAffineTransformMakeWithComponents( CGAffineTransformComponents components )
CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(13.0), ios(16.0));

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

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGAFFINETRANSFORM_H_ */
