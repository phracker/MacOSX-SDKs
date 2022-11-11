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
    GLKVector2 v = {{ x, y }};
    return v;
}
    
GLK_INLINE GLKVector2 GLKVector2MakeWithArray(float values[2])
{
#if   defined(GLK_SSE3_INTRINSICS)
    __m128 v;
    v = _mm_loadl_pi(v, (__m64 *)values);
    return *(GLKVector2 *)&v;
#else
    GLKVector2 v = {{ values[0], values[1] }};
    return v;
#endif
}
    
GLK_INLINE GLKVector2 GLKVector2Negate(GLKVector2 vector)
{
#if   defined(GLK_SSE3_INTRINSICS)
    __m128 v;
    v = _mm_sub_ps(_mm_setzero_ps(), _mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vector));
    return *(GLKVector2 *)&v;
#else
    GLKVector2 v = {{ -vector.v[0] , -vector.v[1] }};
    return v;
#endif
}
 
GLK_INLINE GLKVector2 GLKVector2Add(GLKVector2 vectorLeft, GLKVector2 vectorRight)
{
#if   defined(GLK_SSE3_INTRINSICS)
    __m128 v;
    v = _mm_add_ps(_mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vectorLeft), _mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vectorRight));
    return *(GLKVector2 *)&v;
#else
    GLKVector2 v = {{ vectorLeft.v[0] + vectorRight.v[0],
                      vectorLeft.v[1] + vectorRight.v[1] }};
    return v;
#endif
}
  
GLK_INLINE GLKVector2 GLKVector2Subtract(GLKVector2 vectorLeft, GLKVector2 vectorRight)
{
#if   defined(GLK_SSE3_INTRINSICS)
    __m128 v;
    v = _mm_sub_ps(_mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vectorLeft), _mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vectorRight));
    return *(GLKVector2 *)&v;
#else
    GLKVector2 v = {{ vectorLeft.v[0] - vectorRight.v[0],
                      vectorLeft.v[1] - vectorRight.v[1] }};
    return v;
#endif
}
    
GLK_INLINE GLKVector2 GLKVector2Multiply(GLKVector2 vectorLeft, GLKVector2 vectorRight)
{
#if   defined(GLK_SSE3_INTRINSICS)
    __m128 v;
    v = _mm_mul_ps(_mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vectorLeft), _mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vectorRight));
    return *(GLKVector2 *)&v;
#else
    GLKVector2 v = {{ vectorLeft.v[0] * vectorRight.v[0],
                      vectorLeft.v[1] * vectorRight.v[1] }};
    return v;
#endif
}
    
GLK_INLINE GLKVector2 GLKVector2Divide(GLKVector2 vectorLeft, GLKVector2 vectorRight)
{
#if   defined(GLK_SSE3_INTRINSICS)
    __m128 v;
    v = _mm_div_ps(_mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vectorLeft), _mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vectorRight));
    return *(GLKVector2 *)&v;
#else
    GLKVector2 v = {{ vectorLeft.v[0] / vectorRight.v[0],
                      vectorLeft.v[1] / vectorRight.v[1] }};
    return v;
#endif
}

GLK_INLINE GLKVector2 GLKVector2AddScalar(GLKVector2 vector, float value)
{
#if   defined(GLK_SSE3_INTRINSICS)
    __m128 v;
    v = _mm_add_ps(_mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vector), _mm_set1_ps(value));
    return *(GLKVector2 *)&v;
#else
    GLKVector2 v = {{ vector.v[0] + value,
                      vector.v[1] + value }};
    return v;
#endif
}
    
GLK_INLINE GLKVector2 GLKVector2SubtractScalar(GLKVector2 vector, float value)
{
#if   defined(GLK_SSE3_INTRINSICS)
    __m128 v;
    v = _mm_sub_ps(_mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vector), _mm_set1_ps(value));
    return *(GLKVector2 *)&v;
#else    
    GLKVector2 v = {{ vector.v[0] - value,
                      vector.v[1] - value }};
    return v;
#endif
}
    
GLK_INLINE GLKVector2 GLKVector2MultiplyScalar(GLKVector2 vector, float value)
{
#if   defined(GLK_SSE3_INTRINSICS)
    __m128 v;
    v = _mm_mul_ps(_mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vector), _mm_set1_ps(value));
    return *(GLKVector2 *)&v;
#else
    GLKVector2 v = {{ vector.v[0] * value,
                      vector.v[1] * value }};
    return v;
#endif
}
    
GLK_INLINE GLKVector2 GLKVector2DivideScalar(GLKVector2 vector, float value)
{
#if   defined(GLK_SSE3_INTRINSICS)
    __m128 v;
    v = _mm_div_ps(_mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vector), _mm_set1_ps(value));
    return *(GLKVector2 *)&v;
#else
    GLKVector2 v = {{ vector.v[0] / value,
                      vector.v[1] / value }};
    return v;
#endif
}
    
GLK_INLINE GLKVector2 GLKVector2Maximum(GLKVector2 vectorLeft, GLKVector2 vectorRight)
{
#if   defined(GLK_SSE3_INTRINSICS)
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
#if   defined(GLK_SSE3_INTRINSICS)
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
    bool compare = false;
    if (vectorLeft.v[0] == vectorRight.v[0] &&
        vectorLeft.v[1] == vectorRight.v[1])
        compare = true;
    return compare;
}

GLK_INLINE bool GLKVector2AllEqualToScalar(GLKVector2 vector, float value)
{
    bool compare = false;
    if (vector.v[0] == value &&
        vector.v[1] == value)
        compare = true;
    return compare;
}

GLK_INLINE bool GLKVector2AllGreaterThanVector2(GLKVector2 vectorLeft, GLKVector2 vectorRight)
{
    bool compare = false;
    if (vectorLeft.v[0] > vectorRight.v[0] &&
        vectorLeft.v[1] > vectorRight.v[1])
        compare = true;
    return compare;
}

GLK_INLINE bool GLKVector2AllGreaterThanScalar(GLKVector2 vector, float value)
{
    bool compare = false;
    if (vector.v[0] > value &&
        vector.v[1] > value)
        compare = true;
    return compare;
}

GLK_INLINE bool GLKVector2AllGreaterThanOrEqualToVector2(GLKVector2 vectorLeft, GLKVector2 vectorRight)
{
    bool compare = false;
    if (vectorLeft.v[0] >= vectorRight.v[0] &&
        vectorLeft.v[1] >= vectorRight.v[1])
        compare = true;
    return compare;
}

GLK_INLINE bool GLKVector2AllGreaterThanOrEqualToScalar(GLKVector2 vector, float value)
{
    bool compare = false;
    if (vector.v[0] >= value &&
        vector.v[1] >= value)
        compare = true;
    return compare;
}
    
GLK_INLINE GLKVector2 GLKVector2Normalize(GLKVector2 vector)
{
    float scale = 1.0f / GLKVector2Length(vector);
    GLKVector2 v = GLKVector2MultiplyScalar(vector, scale);
    return v;
}

GLK_INLINE float GLKVector2DotProduct(GLKVector2 vectorLeft, GLKVector2 vectorRight)
{
    return vectorLeft.v[0] * vectorRight.v[0] + vectorLeft.v[1] * vectorRight.v[1];
}

GLK_INLINE float GLKVector2Length(GLKVector2 vector)
{
    return sqrt(vector.v[0] * vector.v[0] + vector.v[1] * vector.v[1]);
}

GLK_INLINE float GLKVector2Distance(GLKVector2 vectorStart, GLKVector2 vectorEnd)
{
    return GLKVector2Length(GLKVector2Subtract(vectorEnd, vectorStart));
}
    
GLK_INLINE GLKVector2 GLKVector2Lerp(GLKVector2 vectorStart, GLKVector2 vectorEnd, float t)
{
    GLKVector2 v = {{ vectorStart.v[0] + ((vectorEnd.v[0] - vectorStart.v[0]) * t),
                      vectorStart.v[1] + ((vectorEnd.v[1] - vectorStart.v[1]) * t) }};
    return v;
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
