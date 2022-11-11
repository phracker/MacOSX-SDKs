/* CoreAnimation - CATransform3D.h

   Copyright (c) 2006-2021, Apple Inc.
   All rights reserved. */

#ifndef CATRANSFORM_H
#define CATRANSFORM_H

#include <QuartzCore/CABase.h>

#ifdef __OBJC__
#import <Foundation/NSValue.h>
#endif

/* Homogeneous three-dimensional transforms. */

struct CATransform3D
{
  CGFloat m11, m12, m13, m14;
  CGFloat m21, m22, m23, m24;
  CGFloat m31, m32, m33, m34;
  CGFloat m41, m42, m43, m44;
};

typedef struct CA_BOXABLE CATransform3D CATransform3D;

CA_EXTERN_C_BEGIN

/* The identity transform: [1 0 0 0; 0 1 0 0; 0 0 1 0; 0 0 0 1]. */

CA_EXTERN const CATransform3D CATransform3DIdentity
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/* Returns true if 't' is the identity transform. */

CA_EXTERN bool CATransform3DIsIdentity (CATransform3D t)
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/* Returns true if 'a' is exactly equal to 'b'. */

CA_EXTERN bool CATransform3DEqualToTransform (CATransform3D a,
    CATransform3D b)
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/* Returns a transform that translates by '(tx, ty, tz)':
 * t' =  [1 0 0 0; 0 1 0 0; 0 0 1 0; tx ty tz 1]. */

CA_EXTERN CATransform3D CATransform3DMakeTranslation (CGFloat tx,
    CGFloat ty, CGFloat tz)
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/* Returns a transform that scales by `(sx, sy, sz)':
 * t' = [sx 0 0 0; 0 sy 0 0; 0 0 sz 0; 0 0 0 1]. */

CA_EXTERN CATransform3D CATransform3DMakeScale (CGFloat sx, CGFloat sy,
    CGFloat sz)
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/* Returns a transform that rotates by 'angle' radians about the vector
 * '(x, y, z)'. If the vector has length zero the identity transform is
 * returned. */

CA_EXTERN CATransform3D CATransform3DMakeRotation (CGFloat angle, CGFloat x,
    CGFloat y, CGFloat z)
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/* Translate 't' by '(tx, ty, tz)' and return the result:
 * t' = translate(tx, ty, tz) * t. */

CA_EXTERN CATransform3D CATransform3DTranslate (CATransform3D t, CGFloat tx,
    CGFloat ty, CGFloat tz)
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/* Scale 't' by '(sx, sy, sz)' and return the result:
 * t' = scale(sx, sy, sz) * t. */

CA_EXTERN CATransform3D CATransform3DScale (CATransform3D t, CGFloat sx,
    CGFloat sy, CGFloat sz)
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/* Rotate 't' by 'angle' radians about the vector '(x, y, z)' and return
 * the result. If the vector has zero length the behavior is undefined:
 * t' = rotation(angle, x, y, z) * t. */

CA_EXTERN CATransform3D CATransform3DRotate (CATransform3D t, CGFloat angle,
    CGFloat x, CGFloat y, CGFloat z)
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/* Concatenate 'b' to 'a' and return the result: t' = a * b. */

CA_EXTERN CATransform3D CATransform3DConcat (CATransform3D a, CATransform3D b)
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/* Invert 't' and return the result. Returns the original matrix if 't'
 * has no inverse. */

CA_EXTERN CATransform3D CATransform3DInvert (CATransform3D t)
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/* Return a transform with the same effect as affine transform 'm'. */

CA_EXTERN CATransform3D CATransform3DMakeAffineTransform (CGAffineTransform m)
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/* Returns true if 't' can be represented exactly by an affine transform. */

CA_EXTERN bool CATransform3DIsAffine (CATransform3D t)
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/* Returns the affine transform represented by 't'. If 't' can not be
 * represented exactly by an affine transform the returned value is
 * undefined. */

CA_EXTERN CGAffineTransform CATransform3DGetAffineTransform (CATransform3D t)
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

CA_EXTERN_C_END

/** NSValue support. **/

#ifdef __OBJC__

NS_ASSUME_NONNULL_BEGIN

@interface NSValue (CATransform3DAdditions)

+ (NSValue *)valueWithCATransform3D:(CATransform3D)t;

@property(readonly) CATransform3D CATransform3DValue;

@end

NS_ASSUME_NONNULL_END

#endif /* __OBJC__ */

#endif /* CATRANSFORM_H */
