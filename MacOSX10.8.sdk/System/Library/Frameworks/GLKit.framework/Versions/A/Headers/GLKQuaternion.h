//
//  GLKQuaternion.h
//  GLKit
//
//  Copyright (c) 2011-2012, Apple Inc. All rights reserved.
//

#ifndef __GLK_QUATERNION_H
#define __GLK_QUATERNION_H

#include <stddef.h>
#include <math.h>

#include <GLKit/GLKMathTypes.h>

#include <GLKit/GLKVector3.h>
#include <GLKit/GLKVector4.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma mark -
#pragma mark Prototypes
#pragma mark -
    
extern const GLKQuaternion GLKQuaternionIdentity; 
	
/*
 x, y, and z represent the imaginary values.
 */
GLK_INLINE GLKQuaternion GLKQuaternionMake(float x, float y, float z, float w);
    
/*
 vector represents the imaginary values.
 */
GLK_INLINE GLKQuaternion GLKQuaternionMakeWithVector3(GLKVector3 vector, float scalar);

/*
 values[0], values[1], and values[2] represent the imaginary values.
 */
GLK_INLINE GLKQuaternion GLKQuaternionMakeWithArray(float values[4]);
    
/*
 Assumes the axis is already normalized.
 */
GLK_INLINE GLKQuaternion GLKQuaternionMakeWithAngleAndAxis(float radians, float x, float y, float z);
/*
 Assumes the axis is already normalized.
 */
GLK_INLINE GLKQuaternion GLKQuaternionMakeWithAngleAndVector3Axis(float radians, GLKVector3 axisVector);
    
GLKQuaternion GLKQuaternionMakeWithMatrix3(GLKMatrix3 matrix);
GLKQuaternion GLKQuaternionMakeWithMatrix4(GLKMatrix4 matrix);

/*
 Calculate and return the angle component of the angle and axis form.
 */
float GLKQuaternionAngle(GLKQuaternion quaternion);

/*
 Calculate and return the axis component of the angle and axis form.
 */
GLKVector3 GLKQuaternionAxis(GLKQuaternion quaternion);
    
GLK_INLINE GLKQuaternion GLKQuaternionAdd(GLKQuaternion quaternionLeft, GLKQuaternion quaternionRight);
GLK_INLINE GLKQuaternion GLKQuaternionSubtract(GLKQuaternion quaternionLeft, GLKQuaternion quaternionRight);
GLK_INLINE GLKQuaternion GLKQuaternionMultiply(GLKQuaternion quaternionLeft, GLKQuaternion quaternionRight);
	
GLKQuaternion GLKQuaternionSlerp(GLKQuaternion quaternionStart, GLKQuaternion quaternionEnd, float t);

GLK_INLINE float GLKQuaternionLength(GLKQuaternion quaternion);

GLK_INLINE GLKQuaternion GLKQuaternionConjugate(GLKQuaternion quaternion);
GLK_INLINE GLKQuaternion GLKQuaternionInvert(GLKQuaternion quaternion);
GLK_INLINE GLKQuaternion GLKQuaternionNormalize(GLKQuaternion quaternion);

GLK_INLINE GLKVector3 GLKQuaternionRotateVector3(GLKQuaternion quaternion, GLKVector3 vector);
void GLKQuaternionRotateVector3Array(GLKQuaternion quaternion, GLKVector3 *vectors, size_t vectorCount);
    
/*
 The fourth component of the vector is ignored when calculating the rotation.
 */
GLK_INLINE GLKVector4 GLKQuaternionRotateVector4(GLKQuaternion quaternion, GLKVector4 vector);
void GLKQuaternionRotateVector4Array(GLKQuaternion quaternion, GLKVector4 *vectors, size_t vectorCount);
    
#pragma mark -
#pragma mark Implementations
#pragma mark -
    
GLK_INLINE GLKQuaternion GLKQuaternionMake(float x, float y, float z, float w)
{
    GLKQuaternion q = { x, y, z, w };
    return q;
}

GLK_INLINE GLKQuaternion GLKQuaternionMakeWithVector3(GLKVector3 vector, float scalar)
{
    GLKQuaternion q = { vector.v[0], vector.v[1], vector.v[2], scalar };
    return q;
}
    
GLK_INLINE GLKQuaternion GLKQuaternionMakeWithArray(float values[4])
{
#if defined(GLK_SSE3_INTRINSICS)
    __m128 v = _mm_load_ps(values);
    return *(GLKQuaternion *)&v;
#else
    GLKQuaternion q = { values[0], values[1], values[2], values[3] };
    return q;
#endif
}
    
GLK_INLINE GLKQuaternion GLKQuaternionMakeWithAngleAndAxis(float radians, float x, float y, float z)
{
    float halfAngle = radians * 0.5f;
    float scale = sinf(halfAngle);
    GLKQuaternion q = { scale * x, scale * y, scale * z, cosf(halfAngle) };
    return q;
}
    
GLK_INLINE GLKQuaternion GLKQuaternionMakeWithAngleAndVector3Axis(float radians, GLKVector3 axisVector)
{
    return GLKQuaternionMakeWithAngleAndAxis(radians, axisVector.v[0], axisVector.v[1], axisVector.v[2]);
}
    
GLK_INLINE GLKQuaternion GLKQuaternionAdd(GLKQuaternion quaternionLeft, GLKQuaternion quaternionRight)
{
#if defined(__ARM_NEON__)
    float32x4_t v = vaddq_f32(*(float32x4_t *)&quaternionLeft,
                              *(float32x4_t *)&quaternionRight);
    return *(GLKQuaternion *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v = _mm_load_ps(&quaternionLeft.q[0]) + _mm_load_ps(&quaternionRight.q[0]);
    return *(GLKQuaternion *)&v;
#else
    GLKQuaternion q = { quaternionLeft.q[0] + quaternionRight.q[0],
                        quaternionLeft.q[1] + quaternionRight.q[1],
                        quaternionLeft.q[2] + quaternionRight.q[2],
                        quaternionLeft.q[3] + quaternionRight.q[3] };
    return q;
#endif
}

GLK_INLINE GLKQuaternion GLKQuaternionSubtract(GLKQuaternion quaternionLeft, GLKQuaternion quaternionRight)
{
#if defined(__ARM_NEON__)
    float32x4_t v = vsubq_f32(*(float32x4_t *)&quaternionLeft,
                              *(float32x4_t *)&quaternionRight);
    return *(GLKQuaternion *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v = _mm_load_ps(&quaternionLeft.q[0]) - _mm_load_ps(&quaternionRight.q[0]);
    return *(GLKQuaternion *)&v;
#else
    GLKQuaternion q = { quaternionLeft.q[0] - quaternionRight.q[0],
                        quaternionLeft.q[1] - quaternionRight.q[1],
                        quaternionLeft.q[2] - quaternionRight.q[2],
                        quaternionLeft.q[3] - quaternionRight.q[3] };
    return q;
#endif
}

GLK_INLINE GLKQuaternion GLKQuaternionMultiply(GLKQuaternion quaternionLeft, GLKQuaternion quaternionRight)
{
#if defined(GLK_SSE3_INTRINSICS)
	const __m128 ql = _mm_load_ps(&quaternionLeft.q[0]);
	const __m128 qr = _mm_load_ps(&quaternionRight.q[0]);

	const __m128 ql3012 = _mm_shuffle_ps(ql, ql, _MM_SHUFFLE(2, 1, 0, 3));
	const __m128 ql3120 = _mm_shuffle_ps(ql, ql, _MM_SHUFFLE(0, 2, 1, 3));
	const __m128 ql3201 = _mm_shuffle_ps(ql, ql, _MM_SHUFFLE(1, 0, 2, 3));

	const __m128 qr0321 = _mm_shuffle_ps(qr, qr, _MM_SHUFFLE(1, 2, 3, 0));
	const __m128 qr1302 = _mm_shuffle_ps(qr, qr, _MM_SHUFFLE(2, 0, 3, 1));
	const __m128 qr2310 = _mm_shuffle_ps(qr, qr, _MM_SHUFFLE(0, 1, 3, 2));
	const __m128 qr3012 = _mm_shuffle_ps(qr, qr, _MM_SHUFFLE(2, 1, 0, 3));

    uint32_t signBit = 0x80000000;
    uint32_t zeroBit = 0x0;
    uint32_t __attribute__((aligned(16))) mask0001[4] = {zeroBit, zeroBit, zeroBit, signBit};
    uint32_t __attribute__((aligned(16))) mask0111[4] = {zeroBit, signBit, signBit, signBit};
    const __m128 m0001 = _mm_load_ps((float *)mask0001);
    const __m128 m0111 = _mm_load_ps((float *)mask0111);

	const __m128 aline = ql3012 * _mm_xor_ps(qr0321, m0001);
	const __m128 bline = ql3120 * _mm_xor_ps(qr1302, m0001);
	const __m128 cline = ql3201 * _mm_xor_ps(qr2310, m0001);
	const __m128 dline = ql3012 * _mm_xor_ps(qr3012, m0111);
	const __m128 r = _mm_hadd_ps(_mm_hadd_ps(aline, bline), _mm_hadd_ps(cline, dline));
				   
    return *(GLKQuaternion *)&r;
#else

    GLKQuaternion q = { quaternionLeft.q[3] * quaternionRight.q[0] +
                        quaternionLeft.q[0] * quaternionRight.q[3] +
                        quaternionLeft.q[1] * quaternionRight.q[2] -
                        quaternionLeft.q[2] * quaternionRight.q[1],
        
                        quaternionLeft.q[3] * quaternionRight.q[1] +
                        quaternionLeft.q[1] * quaternionRight.q[3] +
                        quaternionLeft.q[2] * quaternionRight.q[0] -
                        quaternionLeft.q[0] * quaternionRight.q[2],
        
                        quaternionLeft.q[3] * quaternionRight.q[2] +
                        quaternionLeft.q[2] * quaternionRight.q[3] +
                        quaternionLeft.q[0] * quaternionRight.q[1] -
                        quaternionLeft.q[1] * quaternionRight.q[0],
        
                        quaternionLeft.q[3] * quaternionRight.q[3] -
                        quaternionLeft.q[0] * quaternionRight.q[0] -
                        quaternionLeft.q[1] * quaternionRight.q[1] -
                        quaternionLeft.q[2] * quaternionRight.q[2] };
    return q;
#endif
}
 
GLK_INLINE float GLKQuaternionLength(GLKQuaternion quaternion)
{
#if defined(__ARM_NEON__)
    float32x4_t v = vmulq_f32(*(float32x4_t *)&quaternion,
                              *(float32x4_t *)&quaternion);
    float32x2_t v2 = vpadd_f32(vget_low_f32(v), vget_high_f32(v));
    v2 = vpadd_f32(v2, v2);
    return sqrt(vget_lane_f32(v2, 0)); 
#elif defined(GLK_SSE3_INTRINSICS)
	const __m128 q = _mm_load_ps(&quaternion.q[0]);
	const __m128 product = q * q;
	const __m128 halfsum = _mm_hadd_ps(product, product);
	return _mm_cvtss_f32(_mm_sqrt_ss(_mm_hadd_ps(halfsum, halfsum)));
#else
    return sqrt(quaternion.q[0] * quaternion.q[0] +
                quaternion.q[1] * quaternion.q[1] +
                quaternion.q[2] * quaternion.q[2] +
                quaternion.q[3] * quaternion.q[3]);
#endif
}
    
GLK_INLINE GLKQuaternion GLKQuaternionConjugate(GLKQuaternion quaternion)
{
#if defined(__ARM_NEON__)
    float32x4_t *q = (float32x4_t *)&quaternion;
    
    uint32_t signBit = 0x80000000;
    uint32_t zeroBit = 0x0;
    uint32x4_t mask = vdupq_n_u32(signBit);
    mask = vsetq_lane_u32(zeroBit, mask, 3);
    *q = vreinterpretq_f32_u32(veorq_u32(vreinterpretq_u32_f32(*q), mask));
    
    return *(GLKQuaternion *)q;
#elif defined(GLK_SSE3_INTRINSICS)
    // Multiply first three elements by -1
    const uint32_t signBit = 0x80000000;
    const uint32_t zeroBit = 0x0;
    const uint32_t __attribute__((aligned(16))) mask[4] = {signBit, signBit, signBit, zeroBit};
    __m128 v_mask = _mm_load_ps((float *)mask);
	const __m128 q = _mm_load_ps(&quaternion.q[0]);
    __m128 v = _mm_xor_ps(q, v_mask);
    
    return *(GLKQuaternion *)&v;
#else
    GLKQuaternion q = { -quaternion.q[0], -quaternion.q[1], -quaternion.q[2], quaternion.q[3] };
    return q;
#endif
}
    
GLK_INLINE GLKQuaternion GLKQuaternionInvert(GLKQuaternion quaternion)
{
#if defined(__ARM_NEON__)
    float32x4_t *q = (float32x4_t *)&quaternion;
    float32x4_t v = vmulq_f32(*q, *q);
    float32x2_t v2 = vpadd_f32(vget_low_f32(v), vget_high_f32(v));
    v2 = vpadd_f32(v2, v2);
    float32_t scale = 1.0f / vget_lane_f32(v2, 0);
    v = vmulq_f32(*q, vdupq_n_f32(scale));
    
    uint32_t signBit = 0x80000000;
    uint32_t zeroBit = 0x0;
    uint32x4_t mask = vdupq_n_u32(signBit);
    mask = vsetq_lane_u32(zeroBit, mask, 3);
    v = vreinterpretq_f32_u32(veorq_u32(vreinterpretq_u32_f32(v), mask));
    
    return *(GLKQuaternion *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
	const __m128 q = _mm_load_ps(&quaternion.q[0]);
    const uint32_t signBit = 0x80000000;
    const uint32_t zeroBit = 0x0;
    const uint32_t __attribute__((aligned(16))) mask[4] = {signBit, signBit, signBit, zeroBit};
    const __m128 v_mask = _mm_load_ps((float *)mask);
	const __m128 product = q * q;
	const __m128 halfsum = _mm_hadd_ps(product, product);
	const __m128 v = _mm_xor_ps(q, v_mask) / _mm_hadd_ps(halfsum, halfsum);
    return *(GLKQuaternion *)&v;
#else
    float scale = 1.0f / (quaternion.q[0] * quaternion.q[0] + 
                          quaternion.q[1] * quaternion.q[1] +
                          quaternion.q[2] * quaternion.q[2] +
                          quaternion.q[3] * quaternion.q[3]);
    GLKQuaternion q = { -quaternion.q[0] * scale, -quaternion.q[1] * scale, -quaternion.q[2] * scale, quaternion.q[3] * scale };
    return q;
#endif
}
    
GLK_INLINE GLKQuaternion GLKQuaternionNormalize(GLKQuaternion quaternion)
{
    float scale = 1.0f / GLKQuaternionLength(quaternion);
#if defined(__ARM_NEON__)
    float32x4_t v = vmulq_f32(*(float32x4_t *)&quaternion,
                              vdupq_n_f32((float32_t)scale));
    return *(GLKQuaternion *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
	const __m128 q = _mm_load_ps(&quaternion.q[0]);
    __m128 v = q * _mm_set1_ps(scale);
    return *(GLKQuaternion *)&v;
#else
    GLKQuaternion q = { quaternion.q[0] * scale, quaternion.q[1] * scale, quaternion.q[2] * scale, quaternion.q[3] * scale };
    return q;
#endif
}
    
GLK_INLINE GLKVector3 GLKQuaternionRotateVector3(GLKQuaternion quaternion, GLKVector3 vector)
{
    GLKQuaternion rotatedQuaternion = GLKQuaternionMake(vector.v[0], vector.v[1], vector.v[2], 0.0f);
    rotatedQuaternion = GLKQuaternionMultiply(GLKQuaternionMultiply(quaternion, rotatedQuaternion), GLKQuaternionInvert(quaternion));
    
    return GLKVector3Make(rotatedQuaternion.q[0], rotatedQuaternion.q[1], rotatedQuaternion.q[2]);
}
    
GLK_INLINE GLKVector4 GLKQuaternionRotateVector4(GLKQuaternion quaternion, GLKVector4 vector)
{
    GLKQuaternion rotatedQuaternion = GLKQuaternionMake(vector.v[0], vector.v[1], vector.v[2], 0.0f);
    rotatedQuaternion = GLKQuaternionMultiply(GLKQuaternionMultiply(quaternion, rotatedQuaternion), GLKQuaternionInvert(quaternion));
    
    return GLKVector4Make(rotatedQuaternion.q[0], rotatedQuaternion.q[1], rotatedQuaternion.q[2], vector.v[3]);
}
    
#ifdef __cplusplus
}
#endif

#endif /* __GLK_QUATERNION_H */
