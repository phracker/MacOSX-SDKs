//
//  SceneKitTypes.h
//
//  Copyright (c) 2012-2013 Apple Inc. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>
#import <GLKit/GLKMathTypes.h>

/*! @header SceneKitTypes
    @abstract Various types and utility functions used throughout Scene Kit
 */

typedef struct {
	CGFloat x, y, z;
} SCNVector3;

typedef struct {
	CGFloat x, y, z, w;
} SCNVector4;

/*! Returns true if 'a' is exactly equal to 'b'. */
SCN_EXTERN bool SCNVector3EqualToVector3 (SCNVector3 a, SCNVector3 b);

/*! Returns true if 'a' is exactly equal to 'b'. */
SCN_EXTERN bool SCNVector4EqualToVector4 (SCNVector4 a, SCNVector4 b);

/*! Returns an initialized SCNVector3 */
NS_INLINE SCNVector3 SCNVector3Make(CGFloat x, CGFloat y, CGFloat z) {
    SCNVector3 v = {x, y, z};
    return v;
}

/*! Returns an initialized SCNVector4 */
NS_INLINE SCNVector4 SCNVector4Make(CGFloat x, CGFloat y, CGFloat z, CGFloat w) {
    SCNVector4 v = {x, y, z, w};
    return v;
}

NS_INLINE SCNVector3 SCNVector3FromGLKVector3(GLKVector3 vector) {
#if CGFLOAT_IS_DOUBLE
    SCNVector3 v = {vector.x, vector.y, vector.z};
    return v;
#else
    return *(SCNVector3 *)&vector;
#endif
}

NS_INLINE GLKVector3 SCNVector3ToGLKVector3(SCNVector3 vector) {
#if CGFLOAT_IS_DOUBLE
    GLKVector3 v = {{(float)vector.x, (float)vector.y, (float)vector.z}};
    return v;
#else
    return *(GLKVector3 *)&vector;
#endif
}

NS_INLINE SCNVector4 SCNVector4FromGLKVector4(GLKVector4 vector) {
#if CGFLOAT_IS_DOUBLE
    SCNVector4 v = {vector.x, vector.y, vector.z, vector.w};
    return v;
#else
    return *(SCNVector4 *)&vector;
#endif
}

NS_INLINE GLKVector4 SCNVector4ToGLKVector4(SCNVector4 vector) {
#if CGFLOAT_IS_DOUBLE
    GLKVector4 v = {{(float)vector.x, (float)vector.y, (float)vector.z, (float)vector.w}};
    return v;
#else
    return *(GLKVector4 *)&vector;
#endif
}

NS_INLINE GLKMatrix4 _SCNGLKMatrix4FromCATransform3D(CATransform3D transform) {
#if CGFLOAT_IS_DOUBLE
    GLKMatrix4 m = {{(float)transform.m11, (float)transform.m12, (float)transform.m13, (float)transform.m14,
        (float)transform.m21, (float)transform.m22, (float)transform.m23, (float)transform.m24,
        (float)transform.m31, (float)transform.m32, (float)transform.m33, (float)transform.m34,
        (float)transform.m41, (float)transform.m42, (float)transform.m43, (float)transform.m44}};
    return m;
#else
    return *(GLKMatrix4 *)&transform;
#endif
}

NS_INLINE CATransform3D _SCNGLKMatrix4ToCATransform3D(GLKMatrix4 matrix) {
#if CGFLOAT_IS_DOUBLE
    CATransform3D transform = {matrix.m00, matrix.m01, matrix.m02, matrix.m03,
        matrix.m10, matrix.m11, matrix.m12, matrix.m13,
        matrix.m20, matrix.m21, matrix.m22, matrix.m23,
        matrix.m30, matrix.m31, matrix.m32, matrix.m33};
    return transform;
#else
    return *(CATransform3D *)&matrix;
#endif
}

#define GLKMatrix4FromCATransform3D(X) _SCNGLKMatrix4FromCATransform3D(X)
#define GLKMatrix4ToCATransform3D(X)   _SCNGLKMatrix4ToCATransform3D(X)

#ifdef __OBJC__

/*! @category NSValue(SceneKitAdditions)
 @abstract Adds methods to wrap vectors in NSValue objects.
 */

@interface NSValue (SceneKitAdditions)

+ (NSValue *)valueWithSCNVector3:(SCNVector3)v;
+ (NSValue *)valueWithSCNVector4:(SCNVector4)v;

- (SCNVector3)SCNVector3Value;
- (SCNVector4)SCNVector4Value;

@end

//domain for errors from SceneKit API.
SCN_EXTERN NSString * const SCNErrorDomain;

// NSError codes in SCNErrorDomain.
enum {
	SCNProgramCompilationError = 1
};

#endif /* __OBJC__ */

