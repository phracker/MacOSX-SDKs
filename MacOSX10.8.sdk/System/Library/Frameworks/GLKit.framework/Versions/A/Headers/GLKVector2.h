//
//  GLKVector2.h
//  GLKit
//
//  Copyright (c) 2011-2012, Apple Inc. All rights reserved.
//

#ifndef __GLK_VECTOR_2_H
#define __GLK_VECTOR_2_H

#include <stdbool.h>
#include <math.h>

#if defined(__ARM_NEON__)
#include <arm_neon.h>
#endif

#include <GLKit/GLKMathTypes.h>

#ifdef __cplusplus
extern "C" {
#endif
    
#pragma mark -
#pragma mark Prototypes
#pragma mark -

GLK_INLINE GLKVector2 GLKVector2Make(float x, float y);
GLK_INLINE GLKVector2 GLKVector2MakeWithArray(float values[2]);

GLK_INLINE GLKVector2 GLKVector2Negate(GLKVector2 vector);

GLK_INLINE GLKVector2 GLKVector2Add(GLKVector2 vectorLeft, GLKVector2 vectorRight);
GLK_INLINE GLKVector2 GLKVector2Subtract(GLKVector2 vectorLeft, GLKVector2 vectorRight);
GLK_INLINE GLKVector2 GLKVector2Multiply(GLKVector2 vectorLeft, GLKVector2 vectorRight);
GLK_INLINE GLKVector2 GLKVector2Divide(GLKVector2 vectorLeft, GLKVector2 vectorRight);
        
GLK_INLINE GLKVector2 GLKVector2AddScalar(GLKVector2 vector, float value);
GLK_INLINE GLKVector2 GLKVector2SubtractScalar(GLKVector2 vector, float value);
GLK_INLINE GLKVector2 GLKVector2MultiplyScalar(GLKVector2 vector, float value);
GLK_INLINE GLKVector2 GLKVector2DivideScalar(GLKVector2 vector, float value);
        
/*
 Returns a vector whose elements are the larger of the corresponding elements of the vector arguments.
 */
GLK_INLINE GLKVector2 GLKVector2Maximum(GLKVector2 vectorLeft, GLKVector2 vectorRight);
/*
 Returns a vector whose elements are the smaller of the corresponding elements of the vector arguments.
 */
GLK_INLINE GLKVector2 GLKVector2Minimum(GLKVector2 vectorLeft, GLKVector2 vectorRight);
    
/*
 Returns true if all of the first vector's elements are equal to all of the second vector's arguments.
 */
GLK_INLINE bool GLKVector2AllEqualToVector2(GLKVector2 vectorLeft, GLKVector2 vectorRight);
/*
 Returns true if all of the vector's elements are equal to the provided value.
 */
GLK_INLINE bool GLKVector2AllEqualToScalar(GLKVector2 vector, float value);
/*
 Returns true if all of the first vector's elements are greater than all of the second vector's arguments.
 */
GLK_INLINE bool GLKVector2AllGreaterThanVector2(GLKVector2 vectorLeft, GLKVector2 vectorRight);
/*
 Returns true if all of the vector's elements are greater than the provided value.
 */
GLK_INLINE bool GLKVector2AllGreaterThanScalar(GLKVector2 vector, float value);
/*
 Returns true if all of the first vector's elements are greater than or equal to all of the second vector's arguments.
 */
GLK_INLINE bool GLKVector2AllGreaterThanOrEqualToVector2(GLKVector2 vectorLeft, GLKVector2 vectorRight);
/*
 Returns true if all of the vector's elements are greater than or equal to the provided value.
 */
GLK_INLINE bool GLKVector2AllGreaterThanOrEqualToScalar(GLKVector2 vector, float value);
    
GLK_INLINE GLKVector2 GLKVector2Normalize(GLKVector2 vector);

GLK_INLINE float GLKVector2DotProduct(GLKVector2 vectorLeft, GLKVector2 vectorRight);
GLK_INLINE float GLKVector2Length(GLKVector2 vector);
GLK_INLINE float GLKVector2Distance(GLKVector2 vectorStart, GLKVector2 vectorEnd);

GLK_INLINE GLKVector2 GLKVector2Lerp(GLKVector2 vectorStart, GLKVector2 vectorEnd, float t);

/*
 Project the vector, vectorToProject, onto the vector, projectionVector.
 */
GLK_INLINE GLKVector2 GLKVector2Project(GLKVector2 vectorToProject, GLKVector2 projectionVector);

#pragma mark -
#pragma mark Implementations
#pragma mark -
    
GLK_INLINE GLKVector2 GLKVector2Make(float x, float y)
{
    GLKVector2 v = { x, y };
    return v;
}
    
GLK_INLINE GLKVector2 GLKVector2MakeWithArray(float values[2])
{
#if defined(__ARM_NEON__)
    float32x2_t v = vld1_f32(values);
    return *(GLKVector2 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v;
    v = _mm_loadl_pi(v, (__m64 *)values);
    return *(GLKVector2 *)&v;
#else
    GLKVector2 v = { values[0], values[1] };
    return v;
#endif
}
    
GLK_INLINE GLKVector2 GLKVector2Negate(GLKVector2 vector)
{
#if defined(__ARM_NEON__)
    float32x2_t v = vneg_f32(*(float32x2_t *)&vector);
    return *(GLKVector2 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v;
    v = _mm_sub_ps(_mm_setzero_ps(), _mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vector));
    return *(GLKVector2 *)&v;
#else
    GLKVector2 v = { -vector.v[0] , -vector.v[1] };
    return v;
#endif
}
 
GLK_INLINE GLKVector2 GLKVector2Add(GLKVector2 vectorLeft, GLKVector2 vectorRight)
{
#if defined(__ARM_NEON__)
    float32x2_t v = vadd_f32(*(float32x2_t *)&vectorLeft,
                             *(float32x2_t *)&vectorRight);
    return *(GLKVector2 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v;
    v = _mm_add_ps(_mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vectorLeft), _mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vectorRight));
    return *(GLKVector2 *)&v;
#else
    GLKVector2 v = { vectorLeft.v[0] + vectorRight.v[0],
                     vectorLeft.v[1] + vectorRight.v[1] };
    return v;
#endif
}
  
GLK_INLINE GLKVector2 GLKVector2Subtract(GLKVector2 vectorLeft, GLKVector2 vectorRight)
{
#if defined(__ARM_NEON__)
    float32x2_t v = vsub_f32(*(float32x2_t *)&vectorLeft,
                             *(float32x2_t *)&vectorRight);
    return *(GLKVector2 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v;
    v = _mm_sub_ps(_mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vectorLeft), _mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vectorRight));
    return *(GLKVector2 *)&v;
#else
    GLKVector2 v = { vectorLeft.v[0] - vectorRight.v[0],
                     vectorLeft.v[1] - vectorRight.v[1] };
    return v;
#endif
}
    
GLK_INLINE GLKVector2 GLKVector2Multiply(GLKVector2 vectorLeft, GLKVector2 vectorRight)
{
#if defined(__ARM_NEON__)
    float32x2_t v = vmul_f32(*(float32x2_t *)&vectorLeft,
                             *(float32x2_t *)&vectorRight);
    return *(GLKVector2 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v;
    v = _mm_mul_ps(_mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vectorLeft), _mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vectorRight));
    return *(GLKVector2 *)&v;
#else
    GLKVector2 v = { vectorLeft.v[0] * vectorRight.v[0],
                     vectorLeft.v[1] * vectorRight.v[1] };
    return v;
#endif
}
    
GLK_INLINE GLKVector2 GLKVector2Divide(GLKVector2 vectorLeft, GLKVector2 vectorRight)
{
#if defined(__ARM_NEON__)
    float32x2_t *vLeft = (float32x2_t *)&vectorLeft;
    float32x2_t *vRight = (float32x2_t *)&vectorRight;
    float32x2_t estimate = vrecpe_f32(*vRight);    
    estimate = vmul_f32(vrecps_f32(*vRight, estimate), estimate);
    estimate = vmul_f32(vrecps_f32(*vRight, estimate), estimate);
    float32x2_t v = vmul_f32(*vLeft, estimate);
    return *(GLKVector2 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v;
    v = _mm_div_ps(_mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vectorLeft), _mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vectorRight));
    return *(GLKVector2 *)&v;
#else
    GLKVector2 v = { vectorLeft.v[0] / vectorRight.v[0],
                     vectorLeft.v[1] / vectorRight.v[1] };
    return v;
#endif
}

GLK_INLINE GLKVector2 GLKVector2AddScalar(GLKVector2 vector, float value)
{
#if defined(__ARM_NEON__)
    float32x2_t v = vadd_f32(*(float32x2_t *)&vector,
                             vdup_n_f32((float32_t)value));
    return *(GLKVector2 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v;
    v = _mm_add_ps(_mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vector), _mm_set1_ps(value));
    return *(GLKVector2 *)&v;
#else
    GLKVector2 v = { vector.v[0] + value,
                     vector.v[1] + value };
    return v;
#endif
}
    
GLK_INLINE GLKVector2 GLKVector2SubtractScalar(GLKVector2 vector, float value)
{
#if defined(__ARM_NEON__)
    float32x2_t v = vsub_f32(*(float32x2_t *)&vector,
                             vdup_n_f32((float32_t)value));
    return *(GLKVector2 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v;
    v = _mm_sub_ps(_mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vector), _mm_set1_ps(value));
    return *(GLKVector2 *)&v;
#else    
    GLKVector2 v = { vector.v[0] - value,
                     vector.v[1] - value };
    return v;
#endif
}
    
GLK_INLINE GLKVector2 GLKVector2MultiplyScalar(GLKVector2 vector, float value)
{
#if defined(__ARM_NEON__)
    float32x2_t v = vmul_f32(*(float32x2_t *)&vector,
                             vdup_n_f32((float32_t)value));
    return *(GLKVector2 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v;
    v = _mm_mul_ps(_mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vector), _mm_set1_ps(value));
    return *(GLKVector2 *)&v;
#else
    GLKVector2 v = { vector.v[0] * value,
                     vector.v[1] * value };
    return v;
#endif
}
    
GLK_INLINE GLKVector2 GLKVector2DivideScalar(GLKVector2 vector, float value)
{
#if defined(__ARM_NEON__)
    float32x2_t values = vdup_n_f32((float32_t)value);
    float32x2_t estimate = vrecpe_f32(values);    
    estimate = vmul_f32(vrecps_f32(values, estimate), estimate);
    estimate = vmul_f32(vrecps_f32(values, estimate), estimate);
    float32x2_t v = vmul_f32(*(float32x2_t *)&vector, estimate);
    return *(GLKVector2 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v;
    v = _mm_div_ps(_mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vector), _mm_set1_ps(value));
    return *(GLKVector2 *)&v;
#else
    GLKVector2 v = { vector.v[0] / value,
                     vector.v[1] / value };
    return v;
#endif
}
    
GLK_INLINE GLKVector2 GLKVector2Maximum(GLKVector2 vectorLeft, GLKVector2 vectorRight)
{
#if defined(__ARM_NEON__)
    float32x2_t v = vmax_f32(*(float32x2_t *)&vectorLeft,
                             *(float32x2_t *)&vectorRight);
    return *(GLKVector2 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v;
    v = _mm_max_ps(_mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vectorLeft), _mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vectorRight));
    return *(GLKVector2 *)&v;
#else
    GLKVector2 max = vectorLeft;
    if (vectorRight.v[0] > vectorLeft.v[0])
        max.v[0] = vectorRight.v[0];
    if (vectorRight.v[1] > vectorLeft.v[1])
        max.v[1] = vectorRight.v[1];
    return max;
#endif
}

GLK_INLINE GLKVector2 GLKVector2Minimum(GLKVector2 vectorLeft, GLKVector2 vectorRight)
{
#if defined(__ARM_NEON__)
    float32x2_t v = vmin_f32(*(float32x2_t *)&vectorLeft,
                             *(float32x2_t *)&vectorRight);
    return *(GLKVector2 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v;
    v = _mm_min_ps(_mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vectorLeft), _mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vectorRight));
    return *(GLKVector2 *)&v;
#else
    GLKVector2 min = vectorLeft;
    if (vectorRight.v[0] < vectorLeft.v[0])
        min.v[0] = vectorRight.v[0];
    if (vectorRight.v[1] < vectorLeft.v[1])
        min.v[1] = vectorRight.v[1];
    return min;
#endif
}
   
GLK_INLINE bool GLKVector2AllEqualToVector2(GLKVector2 vectorLeft, GLKVector2 vectorRight)
{
#if defined(__ARM_NEON_)
    float32x2_t v1 = *(float32x2_t *)&vectorLeft;
    float32x2_t v2 = *(float32x2_t *)&vectorRight;
    uint32x2_t vCmp = vceq_f32(v1, v2);
    uint32x2_t vAnd = vand_u32(vCmp, vext_u32(vCmp, vCmp, 1));
    vAnd = vand_u32(vAnd, vdup_n_u32(1));
    return (bool)vget_lane_u32(vAnd, 0);
#else
    bool compare = false;
    if (vectorLeft.v[0] == vectorRight.v[0] &&
        vectorLeft.v[1] == vectorRight.v[1])
        compare = true;
    return compare;
#endif
}

GLK_INLINE bool GLKVector2AllEqualToScalar(GLKVector2 vector, float value)
{
#if defined(__ARM_NEON_)
    float32x2_t v1 = *(float32x2_t *)&vector;
    float32x2_t v2 = vdup_n_f32(value);
    uint32x2_t vCmp = vceq_f32(v1, v2);
    uint32x2_t vAnd = vand_u32(vCmp, vext_u32(vCmp, vCmp, 1));
    vAnd = vand_u32(vAnd, vdup_n_u32(1));
    return (bool)vget_lane_u32(vAnd, 0);
#else
    bool compare = false;
    if (vector.v[0] == value &&
        vector.v[1] == value)
        compare = true;
    return compare;
#endif
}

GLK_INLINE bool GLKVector2AllGreaterThanVector2(GLKVector2 vectorLeft, GLKVector2 vectorRight)
{
#if defined(__ARM_NEON_)
    float32x2_t v1 = *(float32x2_t *)&vectorLeft;
    float32x2_t v2 = *(float32x2_t *)&vectorRight;
    uint32x2_t vCmp = vcgt_f32(v1, v2);
    uint32x2_t vAnd = vand_u32(vCmp, vext_u32(vCmp, vCmp, 1));
    vAnd = vand_u32(vAnd, vdup_n_u32(1));
    return (bool)vget_lane_u32(vAnd, 0);
#else
    bool compare = false;
    if (vectorLeft.v[0] > vectorRight.v[0] &&
        vectorLeft.v[1] > vectorRight.v[1])
        compare = true;
    return compare;
#endif
}

GLK_INLINE bool GLKVector2AllGreaterThanScalar(GLKVector2 vector, float value)
{
#if defined(__ARM_NEON_)
    float32x2_t v1 = *(float32x2_t *)&vector;
    float32x2_t v2 = vdup_n_f32(value);
    uint32x2_t vCmp = vcgt_f32(v1, v2);
    uint32x2_t vAnd = vand_u32(vCmp, vext_u32(vCmp, vCmp, 1));
    vAnd = vand_u32(vAnd, vdup_n_u32(1));
    return (bool)vget_lane_u32(vAnd, 0);
#else
    bool compare = false;
    if (vector.v[0] > value &&
        vector.v[1] > value)
        compare = true;
    return compare;
#endif
}

GLK_INLINE bool GLKVector2AllGreaterThanOrEqualToVector2(GLKVector2 vectorLeft, GLKVector2 vectorRight)
{
#if defined(__ARM_NEON_)
    float32x2_t v1 = *(float32x2_t *)&vectorLeft;
    float32x2_t v2 = *(float32x2_t *)&vectorRight;
    uint32x2_t vCmp = vcge_f32(v1, v2);
    uint32x2_t vAnd = vand_u32(vCmp, vext_u32(vCmp, vCmp, 1));
    vAnd = vand_u32(vAnd, vdup_n_u32(1));
    return (bool)vget_lane_u32(vAnd, 0);
#else
    bool compare = false;
    if (vectorLeft.v[0] >= vectorRight.v[0] &&
        vectorLeft.v[1] >= vectorRight.v[1])
        compare = true;
    return compare;
#endif
}

GLK_INLINE bool GLKVector2AllGreaterThanOrEqualToScalar(GLKVector2 vector, float value)
{
#if defined(__ARM_NEON_)
    float32x2_t v1 = *(float32x2_t *)&vector;
    float32x2_t v2 = vdup_n_f32(value);
    uint32x2_t vCmp = vcge_f32(v1, v2);
    uint32x2_t vAnd = vand_u32(vCmp, vext_u32(vCmp, vCmp, 1));
    vAnd = vand_u32(vAnd, vdup_n_u32(1));
    return (bool)vget_lane_u32(vAnd, 0);
#else
    bool compare = false;
    if (vector.v[0] >= value &&
        vector.v[1] >= value)
        compare = true;
    return compare;
#endif
}
    
GLK_INLINE GLKVector2 GLKVector2Normalize(GLKVector2 vector)
{
    float scale = 1.0f / GLKVector2Length(vector);
    GLKVector2 v = GLKVector2MultiplyScalar(vector, scale);
    return v;
}

GLK_INLINE float GLKVector2DotProduct(GLKVector2 vectorLeft, GLKVector2 vectorRight)
{
#if defined(__ARM_NEON__)
    float32x2_t v = vmul_f32(*(float32x2_t *)&vectorLeft,
                             *(float32x2_t *)&vectorRight);
    v = vpadd_f32(v, v);
    return vget_lane_f32(v, 0);
#else
    return vectorLeft.v[0] * vectorRight.v[0] + vectorLeft.v[1] * vectorRight.v[1];
#endif
}

GLK_INLINE float GLKVector2Length(GLKVector2 vector)
{
#if defined(__ARM_NEON__)
    float32x2_t v = vmul_f32(*(float32x2_t *)&vector,
                             *(float32x2_t *)&vector);
    v = vpadd_f32(v, v);
    return sqrt(vget_lane_f32(v, 0)); 
#else
    return sqrt(vector.v[0] * vector.v[0] + vector.v[1] * vector.v[1]);
#endif
}

GLK_INLINE float GLKVector2Distance(GLKVector2 vectorStart, GLKVector2 vectorEnd)
{
    return GLKVector2Length(GLKVector2Subtract(vectorEnd, vectorStart));
}
    
GLK_INLINE GLKVector2 GLKVector2Lerp(GLKVector2 vectorStart, GLKVector2 vectorEnd, float t)
{
#if defined(__ARM_NEON__)
    float32x2_t vDiff = vsub_f32(*(float32x2_t *)&vectorEnd,
                                 *(float32x2_t *)&vectorStart);
    vDiff = vmul_f32(vDiff, vdup_n_f32((float32_t)t));
    float32x2_t v = vadd_f32(*(float32x2_t *)&vectorStart, vDiff);
    return *(GLKVector2 *)&v;
#else
    GLKVector2 v = { vectorStart.v[0] + ((vectorEnd.v[0] - vectorStart.v[0]) * t),
                     vectorStart.v[1] + ((vectorEnd.v[1] - vectorStart.v[1]) * t) };
    return v;
#endif
}

GLK_INLINE GLKVector2 GLKVector2Project(GLKVector2 vectorToProject, GLKVector2 projectionVector)
{
    float scale = GLKVector2DotProduct(projectionVector, vectorToProject) / GLKVector2DotProduct(projectionVector, projectionVector);
    GLKVector2 v = GLKVector2MultiplyScalar(projectionVector, scale);
    return v;
}

#ifdef __cplusplus
}
#endif

#endif /* __GLK_VECTOR_2_H */
