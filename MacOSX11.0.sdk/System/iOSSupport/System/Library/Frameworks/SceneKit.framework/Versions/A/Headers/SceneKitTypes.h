//
//  SceneKitTypes.h
//  SceneKit
//
//  Copyright © 2012-2020 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKitAvailability.h>
#import <CoreGraphics/CoreGraphics.h>
#import <simd/simd.h>

/*! @header SceneKitTypes
 @abstract Various types and utility functions used throughout SceneKit
 */

#define SCN_ENABLE_METAL 1
#define SCN_ENABLE_OPENGL 0

#ifdef SCN_SILENCE_GL_DEPRECATION
#define SCN_GL_DEPRECATED_MAC(from, to) NS_AVAILABLE_MAC(from)
#define SCN_GL_DEPRECATED_IOS(from, to) NS_AVAILABLE_IOS(from)
#define SCN_GL_DEPRECATED(fromM,toM, fromI,toI) NS_AVAILABLE(fromM,fromI)
#else
#define SCN_GL_DEPRECATED_MAC(from, to) NS_DEPRECATED_MAC(from, to, "OpenGL API deprecated, please use Metal instead. (Define SCN_SILENCE_GL_DEPRECATION to silence these warnings)")
#define SCN_GL_DEPRECATED_IOS(from, to) NS_DEPRECATED_IOS(from, to, "OpenGL API deprecated, please use Metal instead. (Define SCN_SILENCE_GL_DEPRECATION to silence these warnings)")
#define SCN_GL_DEPRECATED(fromM, toM, fromI, toI) NS_DEPRECATED(fromM, toM, fromI, toI, "OpenGL API deprecated, please use Metal instead. (Define SCN_SILENCE_GL_DEPRECATION to silence these warnings)")
#endif

#if SCN_ENABLE_METAL
#import <Metal/Metal.h>
#endif

#if SCN_ENABLE_OPENGL
#import <GLKit/GLKMathTypes.h>
#endif

#import <QuartzCore/QuartzCore.h>

// Color
#define SCNColor UIColor

/*! @enum SCNActionTimingMode
 @abstract The modes that an action can use to adjust the apparent timing of the action.
 */
typedef NS_ENUM(NSInteger, SCNActionTimingMode) {
    SCNActionTimingModeLinear,
    SCNActionTimingModeEaseIn,
    SCNActionTimingModeEaseOut,
    SCNActionTimingModeEaseInEaseOut
} API_AVAILABLE(macos(10.10), ios(8.0));

/*! @enum SCNColorComponent
 @abstract Color components
 */
typedef NS_OPTIONS(NSInteger, SCNColorMask) {
    SCNColorMaskNone   = 0,
    SCNColorMaskRed    = 0x1 << 3,
    SCNColorMaskGreen  = 0x1 << 2,
    SCNColorMaskBlue   = 0x1 << 1,
    SCNColorMaskAlpha  = 0x1 << 0,
    SCNColorMaskAll    = 0xf
} API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

#pragma mark - Vectors

typedef struct SCNVector3 {
    float x, y, z;
} SCNVector3;

typedef struct SCNVector4 {
    float x, y, z, w;
} SCNVector4;

/* The null vector: [0 0 0]. */
SCN_EXPORT const SCNVector3 SCNVector3Zero API_AVAILABLE(macos(10.10));

/* The null vector: [0 0 0 0]. */
SCN_EXPORT const SCNVector4 SCNVector4Zero API_AVAILABLE(macos(10.10));

/* Returns true if 'a' is exactly equal to 'b'. */
SCN_EXPORT bool SCNVector3EqualToVector3 (SCNVector3 a, SCNVector3 b);

/* Returns true if 'a' is exactly equal to 'b'. */
SCN_EXPORT bool SCNVector4EqualToVector4 (SCNVector4 a, SCNVector4 b);

/* Returns an initialized SCNVector3 */
NS_INLINE SCNVector3 SCNVector3Make(float x, float y, float z) {
    return (SCNVector3){x, y, z};
}

/* Returns an initialized SCNVector4 */
NS_INLINE SCNVector4 SCNVector4Make(float x, float y, float z, float w) {
    return (SCNVector4){x, y, z, w};
}


#pragma mark - Quaternions

typedef SCNVector4 SCNQuaternion;


#pragma mark - Matrices

typedef struct SCNMatrix4 {
    float m11, m12, m13, m14;
    float m21, m22, m23, m24;
    float m31, m32, m33, m34;
    float m41, m42, m43, m44;
} SCNMatrix4;

/* The identity matrix: [1 0 0 0; 0 1 0 0; 0 0 1 0; 0 0 0 1]. */
SCN_EXPORT const SCNMatrix4 SCNMatrix4Identity API_AVAILABLE(macos(10.10));

/* Returns true if 'm' is the identity matrix. */
SCN_EXPORT bool SCNMatrix4IsIdentity(SCNMatrix4 m) API_AVAILABLE(macos(10.10));

/* Returns true if 'a' is exactly equal to 'b'. */
SCN_EXPORT bool SCNMatrix4EqualToMatrix4(SCNMatrix4 a, SCNMatrix4 b) API_AVAILABLE(macos(10.10));

/* Returns a transform that translates by '(tx, ty, tz)':
 * m' =  [1 0 0 0; 0 1 0 0; 0 0 1 0; tx ty tz 1]. */
NS_INLINE SCNMatrix4 SCNMatrix4MakeTranslation(float tx, float ty, float tz) {
    return (SCNMatrix4){
        .m11 = 1.f, .m12 = 0.f, .m13 = 0.f, .m14 = 0.f,
        .m21 = 0.f, .m22 = 1.f, .m23 = 0.f, .m24 = 0.f,
        .m31 = 0.f, .m32 = 0.f, .m33 = 1.f, .m34 = 0.f,
        .m41 =  tx, .m42 =  ty, .m43 =  tz, .m44 = 1.f
    };
}

/* Returns a transform that scales by '(sx, sy, sz)':
 * m' = [sx 0 0 0; 0 sy 0 0; 0 0 sz 0; 0 0 0 1]. */
NS_INLINE SCNMatrix4 SCNMatrix4MakeScale(float sx, float sy, float sz) {
    return (SCNMatrix4){
        .m11 =  sx, .m12 = 0.f, .m13 = 0.f, .m14 = 0.f,
        .m21 = 0.f, .m22 =  sy, .m23 = 0.f, .m24 = 0.f,
        .m31 = 0.f, .m32 = 0.f, .m33 =  sz, .m34 = 0.f,
        .m41 = 0.f, .m42 = 0.f, .m43 = 0.f, .m44 = 1.f
    };
}

/* Returns a matrix that rotates by 'angle' radians about the vector '(x, y, z)'. */
SCN_EXPORT SCNMatrix4 SCNMatrix4MakeRotation(float angle, float x, float y, float z) API_AVAILABLE(macos(10.10));

/* Translate 'm' by '(tx, ty, tz)' and return the result:
 * m' = translate(tx, ty, tz) * m. */
NS_INLINE SCNMatrix4 SCNMatrix4Translate(SCNMatrix4 m, float tx, float ty, float tz) {
    m.m41 += tx;
    m.m42 += ty;
    m.m43 += tz;
    return m;
}

/* Scale 'm' by '(sx, sy, sz)' and return the result:
 * m' = scale(sx, sy, sz) * m. */
SCN_EXPORT SCNMatrix4 SCNMatrix4Scale(SCNMatrix4 m, float sx, float sy, float sz) API_AVAILABLE(macos(10.10));

/* Rotate 'm' by 'angle' radians about the vector '(x, y, z)' and return the result:
 * m' = rotation(angle, x, y, z) * m.
 Note: on iOS 10.12 or before, the matrix are combined in the wrong order: m' = m * rotation(angle, x, y, z) */
SCN_EXPORT SCNMatrix4 SCNMatrix4Rotate(SCNMatrix4 m, float angle, float x, float y, float z) API_AVAILABLE(macos(10.10));

/* Invert 'm' and return the result. */
SCN_EXPORT SCNMatrix4 SCNMatrix4Invert(SCNMatrix4 m) API_AVAILABLE(macos(10.10));

/* Concatenate 'b' to 'a' and return the result: m' = a * b. */
SCN_EXPORT SCNMatrix4 SCNMatrix4Mult(SCNMatrix4 a, SCNMatrix4 b) API_AVAILABLE(macos(10.10));


#pragma mark - GLKit Bridge

#if SCN_ENABLE_OPENGL
    
NS_INLINE SCNVector3 SCNVector3FromGLKVector3(GLKVector3 vector) {
    return (SCNVector3){vector.v[0], vector.v[1], vector.v[2]};
}

NS_INLINE GLKVector3 SCNVector3ToGLKVector3(SCNVector3 vector) {
    return *(GLKVector3 *)&vector;
}

NS_INLINE SCNVector4 SCNVector4FromGLKVector4(GLKVector4 vector) {
    return *(SCNVector4 *)&vector;
}

NS_INLINE GLKVector4 SCNVector4ToGLKVector4(SCNVector4 vector) {
    return *(GLKVector4 *)&vector;
}

SCN_EXPORT GLKMatrix4 SCNMatrix4ToGLKMatrix4(SCNMatrix4 mat) API_AVAILABLE(macos(10.10));
SCN_EXPORT SCNMatrix4 SCNMatrix4FromGLKMatrix4(GLKMatrix4 mat) API_AVAILABLE(macos(10.10));

#endif //SCN_ENABLE_OPENGL


#pragma mark - SIMD Bridge
    
NS_INLINE simd_float3 SCNVector3ToFloat3(SCNVector3 v) {
    return simd_make_float3(v.x, v.y, v.z);
}

NS_INLINE simd_float4 SCNVector4ToFloat4(SCNVector4 v) {
    return simd_make_float4(v.x, v.y, v.z, v.w);
}

NS_INLINE simd_float4x4 SCNMatrix4ToMat4(SCNMatrix4 m) {
    return (simd_float4x4){
        .columns[0] = simd_make_float4(m.m11, m.m12, m.m13, m.m14),
        .columns[1] = simd_make_float4(m.m21, m.m22, m.m23, m.m24),
        .columns[2] = simd_make_float4(m.m31, m.m32, m.m33, m.m34),
        .columns[3] = simd_make_float4(m.m41, m.m42, m.m43, m.m44)
    };
}

NS_INLINE SCNVector3 SCNVector3FromFloat3(simd_float3 v) {
    return (SCNVector3){v.x, v.y, v.z};
}

NS_INLINE SCNVector4 SCNVector4FromFloat4(simd_float4 v) {
    return (SCNVector4){v.x, v.y, v.z, v.w};
}

NS_INLINE SCNMatrix4 SCNMatrix4FromMat4(simd_float4x4 m) {
    return *(SCNMatrix4 *)&m;
}


#pragma mark - NSValue Additions
    
#ifdef __OBJC__
    
NS_ASSUME_NONNULL_BEGIN

/*! @category NSValue(SceneKitAdditions)
 @abstract Adds methods to wrap vectors in NSValue objects.
 */

SCN_EXPORT
@interface NSValue (SceneKitAdditions)

+ (NSValue *)valueWithSCNVector3:(SCNVector3)v;
+ (NSValue *)valueWithSCNVector4:(SCNVector4)v;
+ (NSValue *)valueWithSCNMatrix4:(SCNMatrix4)v API_AVAILABLE(macos(10.10));

@property(nonatomic, readonly) SCNVector3 SCNVector3Value;
@property(nonatomic, readonly) SCNVector4 SCNVector4Value;
@property(nonatomic, readonly) SCNMatrix4 SCNMatrix4Value API_AVAILABLE(macos(10.10));

@end


#pragma mark - Errors

//domain for errors from SceneKit API.
SCN_EXPORT NSString * const SCNErrorDomain;

// NSError codes in SCNErrorDomain.
enum {
	SCNProgramCompilationError = 1
};

NS_ASSUME_NONNULL_END
    
#endif /* __OBJC__ */
