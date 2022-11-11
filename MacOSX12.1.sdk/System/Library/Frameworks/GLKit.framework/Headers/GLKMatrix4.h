//
//  GLKMatrix4.h
//  GLKit
//
//  Copyright (c) 2011-2012, Apple Inc. All rights reserved.
//

#ifndef __GLK_MATRIX_4_H
#define __GLK_MATRIX_4_H

#include <stddef.h>
#include <stdbool.h>
#include <math.h>



#include <GLKit/GLKMathTypes.h>
#include <GLKit/GLKVector3.h>
#include <GLKit/GLKVector4.h>
#include <GLKit/GLKQuaternion.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma mark -
#pragma mark Prototypes
#pragma mark -
    
extern const GLKMatrix4 GLKMatrix4Identity;

/*
 m30, m31, and m32 correspond to the translation values tx, ty, tz, respectively.
 */
GLK_INLINE GLKMatrix4 GLKMatrix4Make(float m00, float m01, float m02, float m03,
                                            float m10, float m11, float m12, float m13,
                                            float m20, float m21, float m22, float m23,
                                            float m30, float m31, float m32, float m33);
    
/*
 m03, m13, and m23 correspond to the translation values tx, ty, tz, respectively.
 */
GLK_INLINE GLKMatrix4 GLKMatrix4MakeAndTranspose(float m00, float m01, float m02, float m03,
                                                        float m10, float m11, float m12, float m13,
                                                        float m20, float m21, float m22, float m23,
                                                        float m30, float m31, float m32, float m33);

/*
 m[12], m[13], and m[14] correspond to the translation values tx, ty, and tz, respectively.
 */
GLK_INLINE GLKMatrix4 GLKMatrix4MakeWithArray(float values[16]);

/*
 m[3], m[7], and m[11] correspond to the translation values tx, ty, and tz, respectively.
 */
GLK_INLINE GLKMatrix4 GLKMatrix4MakeWithArrayAndTranspose(float values[16]);
    
/*
 row0, row1, and row2's last component should correspond to the translation values tx, ty, and tz, respectively.
 */
GLK_INLINE GLKMatrix4 GLKMatrix4MakeWithRows(GLKVector4 row0,
                                                    GLKVector4 row1, 
                                                    GLKVector4 row2,
                                                    GLKVector4 row3);
    
/*
 column3's first three components should correspond to the translation values tx, ty, and tz.
 */
GLK_INLINE GLKMatrix4 GLKMatrix4MakeWithColumns(GLKVector4 column0,
                                                       GLKVector4 column1, 
                                                       GLKVector4 column2,
                                                       GLKVector4 column3);
    
/*
 The quaternion will be normalized before conversion.
 */
GLK_INLINE GLKMatrix4 GLKMatrix4MakeWithQuaternion(GLKQuaternion quaternion);
	
GLK_INLINE GLKMatrix4 GLKMatrix4MakeTranslation(float tx, float ty, float tz);
GLK_INLINE GLKMatrix4 GLKMatrix4MakeScale(float sx, float sy, float sz);	
GLK_INLINE GLKMatrix4 GLKMatrix4MakeRotation(float radians, float x, float y, float z);

GLK_INLINE GLKMatrix4 GLKMatrix4MakeXRotation(float radians);
GLK_INLINE GLKMatrix4 GLKMatrix4MakeYRotation(float radians);
GLK_INLINE GLKMatrix4 GLKMatrix4MakeZRotation(float radians);

/*
 Equivalent to gluPerspective.
 */
GLK_INLINE GLKMatrix4 GLKMatrix4MakePerspective(float fovyRadians, float aspect, float nearZ, float farZ);

/*
 Equivalent to glFrustum.
 */
GLK_INLINE GLKMatrix4 GLKMatrix4MakeFrustum(float left, float right,
                                                   float bottom, float top,
                                                   float nearZ, float farZ);

/*
 Equivalent to glOrtho.
 */
GLK_INLINE GLKMatrix4 GLKMatrix4MakeOrtho(float left, float right,
                                                 float bottom, float top,
                                                 float nearZ, float farZ);

/*
 Equivalent to gluLookAt.
 */
GLK_INLINE GLKMatrix4 GLKMatrix4MakeLookAt(float eyeX, float eyeY, float eyeZ,
                                                  float centerX, float centerY, float centerZ,
                                                  float upX, float upY, float upZ);
	
/*
 Returns the upper left 3x3 portion of the 4x4 matrix.
 */
GLK_INLINE GLKMatrix3 GLKMatrix4GetMatrix3(GLKMatrix4 matrix);
/*
 Returns the upper left 2x2 portion of the 4x4 matrix.
 */
GLK_INLINE GLKMatrix2 GLKMatrix4GetMatrix2(GLKMatrix4 matrix);
	
/*
 GLKMatrix4GetRow returns vectors for rows 0, 1, and 2 whose last component will be the translation value tx, ty, and tz, respectively.
 Valid row values range from 0 to 3, inclusive.
 */
GLK_INLINE GLKVector4 GLKMatrix4GetRow(GLKMatrix4 matrix, int row);
/*
 GLKMatrix4GetColumn returns a vector for column 3 whose first three components will be the translation values tx, ty, and tz.
 Valid column values range from 0 to 3, inclusive.
 */
GLK_INLINE GLKVector4 GLKMatrix4GetColumn(GLKMatrix4 matrix, int column);
    
/*
 GLKMatrix4SetRow expects that the vector for row 0, 1, and 2 will have a translation value as its last component.
 Valid row values range from 0 to 3, inclusive.
 */
GLK_INLINE GLKMatrix4 GLKMatrix4SetRow(GLKMatrix4 matrix, int row, GLKVector4 vector);
/*
 GLKMatrix4SetColumn expects that the vector for column 3 will contain the translation values tx, ty, and tz as its first three components, respectively.
 Valid column values range from 0 to 3, inclusive.
 */
GLK_INLINE GLKMatrix4 GLKMatrix4SetColumn(GLKMatrix4 matrix, int column, GLKVector4 vector);
    
GLK_INLINE GLKMatrix4 GLKMatrix4Transpose(GLKMatrix4 matrix);
    
GLKMatrix4 GLKMatrix4Invert(GLKMatrix4 matrix, bool * __nullable isInvertible);
GLKMatrix4 GLKMatrix4InvertAndTranspose(GLKMatrix4 matrix, bool * __nullable isInvertible);

GLK_INLINE GLKMatrix4 GLKMatrix4Multiply(GLKMatrix4 matrixLeft, GLKMatrix4 matrixRight);

GLK_INLINE GLKMatrix4 GLKMatrix4Add(GLKMatrix4 matrixLeft, GLKMatrix4 matrixRight);
GLK_INLINE GLKMatrix4 GLKMatrix4Subtract(GLKMatrix4 matrixLeft, GLKMatrix4 matrixRight);
    
GLK_INLINE GLKMatrix4 GLKMatrix4Translate(GLKMatrix4 matrix, float tx, float ty, float tz);
GLK_INLINE GLKMatrix4 GLKMatrix4TranslateWithVector3(GLKMatrix4 matrix, GLKVector3 translationVector);
/*
 The last component of the GLKVector4, translationVector, is ignored.
 */
GLK_INLINE GLKMatrix4 GLKMatrix4TranslateWithVector4(GLKMatrix4 matrix, GLKVector4 translationVector);

GLK_INLINE GLKMatrix4 GLKMatrix4Scale(GLKMatrix4 matrix, float sx, float sy, float sz);
GLK_INLINE GLKMatrix4 GLKMatrix4ScaleWithVector3(GLKMatrix4 matrix, GLKVector3 scaleVector);
/*
 The last component of the GLKVector4, scaleVector, is ignored.
 */
GLK_INLINE GLKMatrix4 GLKMatrix4ScaleWithVector4(GLKMatrix4 matrix, GLKVector4 scaleVector);
    
GLK_INLINE GLKMatrix4 GLKMatrix4Rotate(GLKMatrix4 matrix, float radians, float x, float y, float z);
GLK_INLINE GLKMatrix4 GLKMatrix4RotateWithVector3(GLKMatrix4 matrix, float radians, GLKVector3 axisVector);
/*
 The last component of the GLKVector4, axisVector, is ignored.
 */
GLK_INLINE GLKMatrix4 GLKMatrix4RotateWithVector4(GLKMatrix4 matrix, float radians, GLKVector4 axisVector);
        
GLK_INLINE GLKMatrix4 GLKMatrix4RotateX(GLKMatrix4 matrix, float radians);
GLK_INLINE GLKMatrix4 GLKMatrix4RotateY(GLKMatrix4 matrix, float radians);
GLK_INLINE GLKMatrix4 GLKMatrix4RotateZ(GLKMatrix4 matrix, float radians);

/*
 Assumes 0 in the w component.
 */
GLK_INLINE GLKVector3 GLKMatrix4MultiplyVector3(GLKMatrix4 matrixLeft, GLKVector3 vectorRight);
/*
 Assumes 1 in the w component.
 */
GLK_INLINE GLKVector3 GLKMatrix4MultiplyVector3WithTranslation(GLKMatrix4 matrixLeft, GLKVector3 vectorRight);
/*
 Assumes 1 in the w component and divides the resulting vector by w before returning.
 */
GLK_INLINE GLKVector3 GLKMatrix4MultiplyAndProjectVector3(GLKMatrix4 matrixLeft, GLKVector3 vectorRight);

/*
 Assumes 0 in the w component.
 */
GLK_INLINE void GLKMatrix4MultiplyVector3Array(GLKMatrix4 matrix, GLKVector3 *__nonnull vectors, size_t vectorCount);
/*
 Assumes 1 in the w component.
 */
GLK_INLINE void GLKMatrix4MultiplyVector3ArrayWithTranslation(GLKMatrix4 matrix, GLKVector3 *__nonnull vectors, size_t vectorCount);
/*
 Assumes 1 in the w component and divides the resulting vector by w before returning.
 */
GLK_INLINE void GLKMatrix4MultiplyAndProjectVector3Array(GLKMatrix4 matrix, GLKVector3 *__nonnull vectors, size_t vectorCount);
    
GLK_INLINE GLKVector4 GLKMatrix4MultiplyVector4(GLKMatrix4 matrixLeft, GLKVector4 vectorRight);

GLK_INLINE void GLKMatrix4MultiplyVector4Array(GLKMatrix4 matrix, GLKVector4 *__nonnull vectors, size_t vectorCount);

#pragma mark -
#pragma mark Implementations
#pragma mark -
    
GLK_INLINE GLKMatrix4 GLKMatrix4Make(float m00, float m01, float m02, float m03,
                                            float m10, float m11, float m12, float m13,
                                            float m20, float m21, float m22, float m23,
                                            float m30, float m31, float m32, float m33)
{
    GLKMatrix4 m = {{ m00, m01, m02, m03,
                      m10, m11, m12, m13,
                      m20, m21, m22, m23,
                      m30, m31, m32, m33 }};
    return m;
}

GLK_INLINE GLKMatrix4 GLKMatrix4MakeAndTranspose(float m00, float m01, float m02, float m03,
                                                        float m10, float m11, float m12, float m13,
                                                        float m20, float m21, float m22, float m23,
                                                        float m30, float m31, float m32, float m33)
{
    GLKMatrix4 m = {{ m00, m10, m20, m30,
                      m01, m11, m21, m31,
                      m02, m12, m22, m32,
                      m03, m13, m23, m33 }};
    return m;
}
    
GLK_INLINE GLKMatrix4 GLKMatrix4MakeWithArray(float values[16])
{
    GLKMatrix4 m = {{ values[0], values[1], values[2], values[3],
                      values[4], values[5], values[6], values[7],
                      values[8], values[9], values[10], values[11],
                      values[12], values[13], values[14], values[15] }};
    return m;
}
 
GLK_INLINE GLKMatrix4 GLKMatrix4MakeWithArrayAndTranspose(float values[16])
{
    GLKMatrix4 m = {{ values[0], values[4], values[8], values[12],
                      values[1], values[5], values[9], values[13],
                      values[2], values[6], values[10], values[14],
                      values[3], values[7], values[11], values[15] }};
    return m;
}

GLK_INLINE GLKMatrix4 GLKMatrix4MakeWithRows(GLKVector4 row0,
                                                    GLKVector4 row1, 
                                                    GLKVector4 row2,
                                                    GLKVector4 row3)
{
    GLKMatrix4 m = {{ row0.v[0], row1.v[0], row2.v[0], row3.v[0],
                      row0.v[1], row1.v[1], row2.v[1], row3.v[1],
                      row0.v[2], row1.v[2], row2.v[2], row3.v[2],
                      row0.v[3], row1.v[3], row2.v[3], row3.v[3] }};
    return m;
}

GLK_INLINE GLKMatrix4 GLKMatrix4MakeWithColumns(GLKVector4 column0,
                                                       GLKVector4 column1, 
                                                       GLKVector4 column2,
                                                       GLKVector4 column3)
{
#if   defined(GLK_SSE3_INTRINSICS)
    GLKMatrix4 m;
    *((__m128*)&m.m[0])  = *(__m128*)&column0;
    *((__m128*)&m.m[4])  = *(__m128*)&column1;
    *((__m128*)&m.m[8])  = *(__m128*)&column2;
    *((__m128*)&m.m[12]) = *(__m128*)&column3;
    return m;
#else
    GLKMatrix4 m = {{ column0.v[0], column0.v[1], column0.v[2], column0.v[3],
                      column1.v[0], column1.v[1], column1.v[2], column1.v[3],
                      column2.v[0], column2.v[1], column2.v[2], column2.v[3],
                      column3.v[0], column3.v[1], column3.v[2], column3.v[3] }};
    return m;
#endif
}
    
GLK_INLINE GLKMatrix4 GLKMatrix4MakeWithQuaternion(GLKQuaternion quaternion)
{
    quaternion = GLKQuaternionNormalize(quaternion);
    
    float x = quaternion.q[0];
    float y = quaternion.q[1];
    float z = quaternion.q[2];
    float w = quaternion.q[3];
    
    float _2x = x + x;
    float _2y = y + y;
    float _2z = z + z;
    float _2w = w + w;
    
    GLKMatrix4 m = {{ 1.0f - _2y * y - _2z * z,
                      _2x * y + _2w * z,
                      _2x * z - _2w * y,
                      0.0f,
                      _2x * y - _2w * z,
                      1.0f - _2x * x - _2z * z,
                      _2y * z + _2w * x,
                      0.0f,
                      _2x * z + _2w * y,
                      _2y * z - _2w * x,
                      1.0f - _2x * x - _2y * y,
                      0.0f,
                      0.0f,
                      0.0f,
                      0.0f,
                      1.0f }};
    
    return m;
}
    
GLK_INLINE GLKMatrix4 GLKMatrix4MakeTranslation(float tx, float ty, float tz)
{
    GLKMatrix4 m = GLKMatrix4Identity;
    m.m[12] = tx;
    m.m[13] = ty;
    m.m[14] = tz;
    return m;
}

GLK_INLINE GLKMatrix4 GLKMatrix4MakeScale(float sx, float sy, float sz)
{
    GLKMatrix4 m = GLKMatrix4Identity;
    m.m[0] = sx;
    m.m[5] = sy;
    m.m[10] = sz;
    return m;
}

GLK_INLINE GLKMatrix4 GLKMatrix4MakeRotation(float radians, float x, float y, float z)
{
    GLKVector3 v = GLKVector3Normalize(GLKVector3Make(x, y, z));
    float cos = cosf(radians);
    float cosp = 1.0f - cos;
    float sin = sinf(radians);
    
    GLKMatrix4 m = {{ cos + cosp * v.v[0] * v.v[0],
                      cosp * v.v[0] * v.v[1] + v.v[2] * sin,
                      cosp * v.v[0] * v.v[2] - v.v[1] * sin,
                      0.0f,
                      cosp * v.v[0] * v.v[1] - v.v[2] * sin,
                      cos + cosp * v.v[1] * v.v[1],
                      cosp * v.v[1] * v.v[2] + v.v[0] * sin,
                      0.0f,
                      cosp * v.v[0] * v.v[2] + v.v[1] * sin,
                      cosp * v.v[1] * v.v[2] - v.v[0] * sin,
                      cos + cosp * v.v[2] * v.v[2],
                      0.0f,
                      0.0f,
                      0.0f,
                      0.0f,
                      1.0f }};

    return m;
}
   
GLK_INLINE GLKMatrix4 GLKMatrix4MakeXRotation(float radians)
{
    float cos = cosf(radians);
    float sin = sinf(radians);
    
    GLKMatrix4 m = {{ 1.0f, 0.0f, 0.0f, 0.0f,
                      0.0f, cos, sin, 0.0f,
                      0.0f, -sin, cos, 0.0f,
                      0.0f, 0.0f, 0.0f, 1.0f }};
    
    return m;
}

GLK_INLINE GLKMatrix4 GLKMatrix4MakeYRotation(float radians)
{
    float cos = cosf(radians);
    float sin = sinf(radians);
    
    GLKMatrix4 m = {{ cos, 0.0f, -sin, 0.0f,
                      0.0f, 1.0f, 0.0f, 0.0f,
                      sin, 0.0f, cos, 0.0f,
                      0.0f, 0.0f, 0.0f, 1.0f }};
    
    return m;
}

GLK_INLINE GLKMatrix4 GLKMatrix4MakeZRotation(float radians)
{
    float cos = cosf(radians);
    float sin = sinf(radians);
    
    GLKMatrix4 m = {{ cos, sin, 0.0f, 0.0f,
                      -sin, cos, 0.0f, 0.0f,
                      0.0f, 0.0f, 1.0f, 0.0f,
                      0.0f, 0.0f, 0.0f, 1.0f }};
    
    return m;
}
 
GLK_INLINE GLKMatrix4 GLKMatrix4MakePerspective(float fovyRadians, float aspect, float nearZ, float farZ)
{
    float cotan = 1.0f / tanf(fovyRadians / 2.0f);
    
    GLKMatrix4 m = {{ cotan / aspect, 0.0f, 0.0f, 0.0f,
                      0.0f, cotan, 0.0f, 0.0f,
                      0.0f, 0.0f, (farZ + nearZ) / (nearZ - farZ), -1.0f,
                      0.0f, 0.0f, (2.0f * farZ * nearZ) / (nearZ - farZ), 0.0f }};
    
    return m;
}
    
GLK_INLINE GLKMatrix4 GLKMatrix4MakeFrustum(float left, float right,
                                                   float bottom, float top,
                                                   float nearZ, float farZ)
{
    float ral = right + left;
    float rsl = right - left;
    float tsb = top - bottom;
    float tab = top + bottom;
    float fan = farZ + nearZ;
    float fsn = farZ - nearZ;
    
    GLKMatrix4 m = {{ 2.0f * nearZ / rsl, 0.0f, 0.0f, 0.0f,
                      0.0f, 2.0f * nearZ / tsb, 0.0f, 0.0f,
                      ral / rsl, tab / tsb, -fan / fsn, -1.0f,
                      0.0f, 0.0f, (-2.0f * farZ * nearZ) / fsn, 0.0f }};
    
    return m;
}
    
GLK_INLINE GLKMatrix4 GLKMatrix4MakeOrtho(float left, float right,
                                                 float bottom, float top,
                                                 float nearZ, float farZ)
{
    float ral = right + left;
    float rsl = right - left;
    float tab = top + bottom;
    float tsb = top - bottom;
    float fan = farZ + nearZ;
    float fsn = farZ - nearZ;
    
    GLKMatrix4 m = {{ 2.0f / rsl, 0.0f, 0.0f, 0.0f,
                      0.0f, 2.0f / tsb, 0.0f, 0.0f,
                      0.0f, 0.0f, -2.0f / fsn, 0.0f,
                      -ral / rsl, -tab / tsb, -fan / fsn, 1.0f }};
                     
    return m;
}
   
GLK_INLINE GLKMatrix4 GLKMatrix4MakeLookAt(float eyeX, float eyeY, float eyeZ,
                                                  float centerX, float centerY, float centerZ,
                                                  float upX, float upY, float upZ)
{
    GLKVector3 ev = {{ eyeX, eyeY, eyeZ }};
    GLKVector3 cv = {{ centerX, centerY, centerZ }};
    GLKVector3 uv = {{ upX, upY, upZ }};
    GLKVector3 n = GLKVector3Normalize(GLKVector3Add(ev, GLKVector3Negate(cv)));
    GLKVector3 u = GLKVector3Normalize(GLKVector3CrossProduct(uv, n));
    GLKVector3 v = GLKVector3CrossProduct(n, u);
    
    GLKMatrix4 m = {{ u.v[0], v.v[0], n.v[0], 0.0f,
                      u.v[1], v.v[1], n.v[1], 0.0f,
                      u.v[2], v.v[2], n.v[2], 0.0f,
                      GLKVector3DotProduct(GLKVector3Negate(u), ev),
                      GLKVector3DotProduct(GLKVector3Negate(v), ev),
                      GLKVector3DotProduct(GLKVector3Negate(n), ev),
                      1.0f }};
    
    return m;
}
  
GLK_INLINE GLKMatrix3 GLKMatrix4GetMatrix3(GLKMatrix4 matrix)
{
    GLKMatrix3 m = {{ matrix.m[0], matrix.m[1], matrix.m[2],
                      matrix.m[4], matrix.m[5], matrix.m[6],
                      matrix.m[8], matrix.m[9], matrix.m[10] }};
    return m;
}

GLK_INLINE GLKMatrix2 GLKMatrix4GetMatrix2(GLKMatrix4 matrix)
{
    GLKMatrix2 m = {{ matrix.m[0], matrix.m[1],
                      matrix.m[4], matrix.m[5] }};
    return m;
}

GLK_INLINE GLKVector4 GLKMatrix4GetRow(GLKMatrix4 matrix, int row)
{
    GLKVector4 v = {{ matrix.m[row], matrix.m[4 + row], matrix.m[8 + row], matrix.m[12 + row] }};
    return v;
}

GLK_INLINE GLKVector4 GLKMatrix4GetColumn(GLKMatrix4 matrix, int column)
{
#if   defined(GLK_SSE3_INTRINSICS)
    __m128 v = _mm_load_ps(&matrix.m[column * 4]);
    return *(GLKVector4 *)&v;
#else
    GLKVector4 v = {{ matrix.m[column * 4 + 0], matrix.m[column * 4 + 1], matrix.m[column * 4 + 2], matrix.m[column * 4 + 3] }};
    return v;
#endif
}

GLK_INLINE GLKMatrix4 GLKMatrix4SetRow(GLKMatrix4 matrix, int row, GLKVector4 vector)
{
    matrix.m[row] = vector.v[0];
    matrix.m[row + 4] = vector.v[1];
    matrix.m[row + 8] = vector.v[2];
    matrix.m[row + 12] = vector.v[3];
    
    return matrix;
}

GLK_INLINE GLKMatrix4 GLKMatrix4SetColumn(GLKMatrix4 matrix, int column, GLKVector4 vector)
{
#if   defined(GLK_SSE3_INTRINSICS)
    *((__m128*)&matrix.m[column*4]) = *(__m128*)&vector;
    return matrix;
#else
    matrix.m[column * 4 + 0] = vector.v[0];
    matrix.m[column * 4 + 1] = vector.v[1];
    matrix.m[column * 4 + 2] = vector.v[2];
    matrix.m[column * 4 + 3] = vector.v[3];
    
    return matrix;
#endif
}
    
GLK_INLINE GLKMatrix4 GLKMatrix4Transpose(GLKMatrix4 matrix)
{
    GLKMatrix4 m = {{ matrix.m[0], matrix.m[4], matrix.m[8], matrix.m[12],
                      matrix.m[1], matrix.m[5], matrix.m[9], matrix.m[13],
                      matrix.m[2], matrix.m[6], matrix.m[10], matrix.m[14],
                      matrix.m[3], matrix.m[7], matrix.m[11], matrix.m[15] }};
    return m;
}

GLK_INLINE GLKMatrix4 GLKMatrix4Multiply(GLKMatrix4 matrixLeft, GLKMatrix4 matrixRight)
{
#if   defined(GLK_SSE3_INTRINSICS)
    
	const __m128 l0 = _mm_load_ps(&matrixLeft.m[0]);
	const __m128 l1 = _mm_load_ps(&matrixLeft.m[4]);
	const __m128 l2 = _mm_load_ps(&matrixLeft.m[8]);
	const __m128 l3 = _mm_load_ps(&matrixLeft.m[12]);

	const __m128 r0 = _mm_load_ps(&matrixRight.m[0]);
	const __m128 r1 = _mm_load_ps(&matrixRight.m[4]);
	const __m128 r2 = _mm_load_ps(&matrixRight.m[8]);
	const __m128 r3 = _mm_load_ps(&matrixRight.m[12]);
	
	const __m128 m0 = l0 * _mm_shuffle_ps(r0, r0, _MM_SHUFFLE(0, 0, 0, 0))
					+ l1 * _mm_shuffle_ps(r0, r0, _MM_SHUFFLE(1, 1, 1, 1))
					+ l2 * _mm_shuffle_ps(r0, r0, _MM_SHUFFLE(2, 2, 2, 2))
					+ l3 * _mm_shuffle_ps(r0, r0, _MM_SHUFFLE(3, 3, 3, 3));

	const __m128 m1 = l0 * _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(0, 0, 0, 0))
					+ l1 * _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(1, 1, 1, 1))
					+ l2 * _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(2, 2, 2, 2))
					+ l3 * _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(3, 3, 3, 3));

	const __m128 m2 = l0 * _mm_shuffle_ps(r2, r2, _MM_SHUFFLE(0, 0, 0, 0))
					+ l1 * _mm_shuffle_ps(r2, r2, _MM_SHUFFLE(1, 1, 1, 1))
					+ l2 * _mm_shuffle_ps(r2, r2, _MM_SHUFFLE(2, 2, 2, 2))
					+ l3 * _mm_shuffle_ps(r2, r2, _MM_SHUFFLE(3, 3, 3, 3));

	const __m128 m3 = l0 * _mm_shuffle_ps(r3, r3, _MM_SHUFFLE(0, 0, 0, 0))
					+ l1 * _mm_shuffle_ps(r3, r3, _MM_SHUFFLE(1, 1, 1, 1))
					+ l2 * _mm_shuffle_ps(r3, r3, _MM_SHUFFLE(2, 2, 2, 2))
					+ l3 * _mm_shuffle_ps(r3, r3, _MM_SHUFFLE(3, 3, 3, 3));
				
	GLKMatrix4 m;
	_mm_store_ps(&m.m[0], m0);
	_mm_store_ps(&m.m[4], m1);
	_mm_store_ps(&m.m[8], m2);
	_mm_store_ps(&m.m[12], m3);
    return m;

#else
    GLKMatrix4 m;
    
    m.m[0]  = matrixLeft.m[0] * matrixRight.m[0]  + matrixLeft.m[4] * matrixRight.m[1]  + matrixLeft.m[8] * matrixRight.m[2]   + matrixLeft.m[12] * matrixRight.m[3];
	m.m[4]  = matrixLeft.m[0] * matrixRight.m[4]  + matrixLeft.m[4] * matrixRight.m[5]  + matrixLeft.m[8] * matrixRight.m[6]   + matrixLeft.m[12] * matrixRight.m[7];
	m.m[8]  = matrixLeft.m[0] * matrixRight.m[8]  + matrixLeft.m[4] * matrixRight.m[9]  + matrixLeft.m[8] * matrixRight.m[10]  + matrixLeft.m[12] * matrixRight.m[11];
	m.m[12] = matrixLeft.m[0] * matrixRight.m[12] + matrixLeft.m[4] * matrixRight.m[13] + matrixLeft.m[8] * matrixRight.m[14]  + matrixLeft.m[12] * matrixRight.m[15];
    
	m.m[1]  = matrixLeft.m[1] * matrixRight.m[0]  + matrixLeft.m[5] * matrixRight.m[1]  + matrixLeft.m[9] * matrixRight.m[2]   + matrixLeft.m[13] * matrixRight.m[3];
	m.m[5]  = matrixLeft.m[1] * matrixRight.m[4]  + matrixLeft.m[5] * matrixRight.m[5]  + matrixLeft.m[9] * matrixRight.m[6]   + matrixLeft.m[13] * matrixRight.m[7];
	m.m[9]  = matrixLeft.m[1] * matrixRight.m[8]  + matrixLeft.m[5] * matrixRight.m[9]  + matrixLeft.m[9] * matrixRight.m[10]  + matrixLeft.m[13] * matrixRight.m[11];
	m.m[13] = matrixLeft.m[1] * matrixRight.m[12] + matrixLeft.m[5] * matrixRight.m[13] + matrixLeft.m[9] * matrixRight.m[14]  + matrixLeft.m[13] * matrixRight.m[15];
    
	m.m[2]  = matrixLeft.m[2] * matrixRight.m[0]  + matrixLeft.m[6] * matrixRight.m[1]  + matrixLeft.m[10] * matrixRight.m[2]  + matrixLeft.m[14] * matrixRight.m[3];
	m.m[6]  = matrixLeft.m[2] * matrixRight.m[4]  + matrixLeft.m[6] * matrixRight.m[5]  + matrixLeft.m[10] * matrixRight.m[6]  + matrixLeft.m[14] * matrixRight.m[7];
	m.m[10] = matrixLeft.m[2] * matrixRight.m[8]  + matrixLeft.m[6] * matrixRight.m[9]  + matrixLeft.m[10] * matrixRight.m[10] + matrixLeft.m[14] * matrixRight.m[11];
	m.m[14] = matrixLeft.m[2] * matrixRight.m[12] + matrixLeft.m[6] * matrixRight.m[13] + matrixLeft.m[10] * matrixRight.m[14] + matrixLeft.m[14] * matrixRight.m[15];
    
	m.m[3]  = matrixLeft.m[3] * matrixRight.m[0]  + matrixLeft.m[7] * matrixRight.m[1]  + matrixLeft.m[11] * matrixRight.m[2]  + matrixLeft.m[15] * matrixRight.m[3];
	m.m[7]  = matrixLeft.m[3] * matrixRight.m[4]  + matrixLeft.m[7] * matrixRight.m[5]  + matrixLeft.m[11] * matrixRight.m[6]  + matrixLeft.m[15] * matrixRight.m[7];
	m.m[11] = matrixLeft.m[3] * matrixRight.m[8]  + matrixLeft.m[7] * matrixRight.m[9]  + matrixLeft.m[11] * matrixRight.m[10] + matrixLeft.m[15] * matrixRight.m[11];
	m.m[15] = matrixLeft.m[3] * matrixRight.m[12] + matrixLeft.m[7] * matrixRight.m[13] + matrixLeft.m[11] * matrixRight.m[14] + matrixLeft.m[15] * matrixRight.m[15];
    
    return m;
#endif
}
 
GLK_INLINE GLKMatrix4 GLKMatrix4Add(GLKMatrix4 matrixLeft, GLKMatrix4 matrixRight)
{
#if   defined(GLK_SSE3_INTRINSICS)
    GLKMatrix4 m;
    
    _mm_store_ps(&m.m[0],  _mm_load_ps(&matrixLeft.m[0])  + _mm_load_ps(&matrixRight.m[0]));
    _mm_store_ps(&m.m[4],  _mm_load_ps(&matrixLeft.m[4])  + _mm_load_ps(&matrixRight.m[4]));
    _mm_store_ps(&m.m[8],  _mm_load_ps(&matrixLeft.m[8])  + _mm_load_ps(&matrixRight.m[8]));
    _mm_store_ps(&m.m[12], _mm_load_ps(&matrixLeft.m[12]) + _mm_load_ps(&matrixRight.m[12]));
	    
    return m;
#else
    GLKMatrix4 m;
    
    m.m[0] = matrixLeft.m[0] + matrixRight.m[0];
    m.m[1] = matrixLeft.m[1] + matrixRight.m[1];
    m.m[2] = matrixLeft.m[2] + matrixRight.m[2];
    m.m[3] = matrixLeft.m[3] + matrixRight.m[3];
    
    m.m[4] = matrixLeft.m[4] + matrixRight.m[4];
    m.m[5] = matrixLeft.m[5] + matrixRight.m[5];
    m.m[6] = matrixLeft.m[6] + matrixRight.m[6];
    m.m[7] = matrixLeft.m[7] + matrixRight.m[7];
    
    m.m[8] = matrixLeft.m[8] + matrixRight.m[8];
    m.m[9] = matrixLeft.m[9] + matrixRight.m[9];
    m.m[10] = matrixLeft.m[10] + matrixRight.m[10];
    m.m[11] = matrixLeft.m[11] + matrixRight.m[11];
    
    m.m[12] = matrixLeft.m[12] + matrixRight.m[12];
    m.m[13] = matrixLeft.m[13] + matrixRight.m[13];
    m.m[14] = matrixLeft.m[14] + matrixRight.m[14];
    m.m[15] = matrixLeft.m[15] + matrixRight.m[15];
    
    return m;
#endif
}

GLK_INLINE GLKMatrix4 GLKMatrix4Subtract(GLKMatrix4 matrixLeft, GLKMatrix4 matrixRight)
{
#if   defined(GLK_SSE3_INTRINSICS)
    GLKMatrix4 m;
    
    _mm_store_ps(&m.m[0],  _mm_load_ps(&matrixLeft.m[0])  - _mm_load_ps(&matrixRight.m[0]));
    _mm_store_ps(&m.m[4],  _mm_load_ps(&matrixLeft.m[4])  - _mm_load_ps(&matrixRight.m[4]));
    _mm_store_ps(&m.m[8],  _mm_load_ps(&matrixLeft.m[8])  - _mm_load_ps(&matrixRight.m[8]));
    _mm_store_ps(&m.m[12], _mm_load_ps(&matrixLeft.m[12]) - _mm_load_ps(&matrixRight.m[12]));
	    
    return m;
#else
    GLKMatrix4 m;
    
    m.m[0] = matrixLeft.m[0] - matrixRight.m[0];
    m.m[1] = matrixLeft.m[1] - matrixRight.m[1];
    m.m[2] = matrixLeft.m[2] - matrixRight.m[2];
    m.m[3] = matrixLeft.m[3] - matrixRight.m[3];
    
    m.m[4] = matrixLeft.m[4] - matrixRight.m[4];
    m.m[5] = matrixLeft.m[5] - matrixRight.m[5];
    m.m[6] = matrixLeft.m[6] - matrixRight.m[6];
    m.m[7] = matrixLeft.m[7] - matrixRight.m[7];
    
    m.m[8] = matrixLeft.m[8] - matrixRight.m[8];
    m.m[9] = matrixLeft.m[9] - matrixRight.m[9];
    m.m[10] = matrixLeft.m[10] - matrixRight.m[10];
    m.m[11] = matrixLeft.m[11] - matrixRight.m[11];
    
    m.m[12] = matrixLeft.m[12] - matrixRight.m[12];
    m.m[13] = matrixLeft.m[13] - matrixRight.m[13];
    m.m[14] = matrixLeft.m[14] - matrixRight.m[14];
    m.m[15] = matrixLeft.m[15] - matrixRight.m[15];
    
    return m;
#endif
}
    
GLK_INLINE GLKMatrix4 GLKMatrix4Translate(GLKMatrix4 matrix, float tx, float ty, float tz)
{
    GLKMatrix4 m = {{ matrix.m[0], matrix.m[1], matrix.m[2], matrix.m[3],
                      matrix.m[4], matrix.m[5], matrix.m[6], matrix.m[7],
                      matrix.m[8], matrix.m[9], matrix.m[10], matrix.m[11],
                      matrix.m[0] * tx + matrix.m[4] * ty + matrix.m[8] * tz + matrix.m[12],
                      matrix.m[1] * tx + matrix.m[5] * ty + matrix.m[9] * tz + matrix.m[13],
                      matrix.m[2] * tx + matrix.m[6] * ty + matrix.m[10] * tz + matrix.m[14],
                      matrix.m[3] * tx + matrix.m[7] * ty + matrix.m[11] * tz + matrix.m[15] }};
    return m;
}
 
GLK_INLINE GLKMatrix4 GLKMatrix4TranslateWithVector3(GLKMatrix4 matrix, GLKVector3 translationVector)
{
    GLKMatrix4 m = {{ matrix.m[0], matrix.m[1], matrix.m[2], matrix.m[3],
                      matrix.m[4], matrix.m[5], matrix.m[6], matrix.m[7],
                      matrix.m[8], matrix.m[9], matrix.m[10], matrix.m[11],
                      matrix.m[0] * translationVector.v[0] + matrix.m[4] * translationVector.v[1] + matrix.m[8] * translationVector.v[2] + matrix.m[12],
                      matrix.m[1] * translationVector.v[0] + matrix.m[5] * translationVector.v[1] + matrix.m[9] * translationVector.v[2] + matrix.m[13],
                      matrix.m[2] * translationVector.v[0] + matrix.m[6] * translationVector.v[1] + matrix.m[10] * translationVector.v[2] + matrix.m[14],
                      matrix.m[3] * translationVector.v[0] + matrix.m[7] * translationVector.v[1] + matrix.m[11] * translationVector.v[2] + matrix.m[15] }};
    return m;
}
    
GLK_INLINE GLKMatrix4 GLKMatrix4TranslateWithVector4(GLKMatrix4 matrix, GLKVector4 translationVector)
{
    GLKMatrix4 m = {{ matrix.m[0], matrix.m[1], matrix.m[2], matrix.m[3],
                      matrix.m[4], matrix.m[5], matrix.m[6], matrix.m[7],
                      matrix.m[8], matrix.m[9], matrix.m[10], matrix.m[11],
                      matrix.m[0] * translationVector.v[0] + matrix.m[4] * translationVector.v[1] + matrix.m[8] * translationVector.v[2] + matrix.m[12],
                      matrix.m[1] * translationVector.v[0] + matrix.m[5] * translationVector.v[1] + matrix.m[9] * translationVector.v[2] + matrix.m[13],
                      matrix.m[2] * translationVector.v[0] + matrix.m[6] * translationVector.v[1] + matrix.m[10] * translationVector.v[2] + matrix.m[14],
                      matrix.m[3] * translationVector.v[0] + matrix.m[7] * translationVector.v[1] + matrix.m[11] * translationVector.v[2] + matrix.m[15] }};
    return m;
}
    
GLK_INLINE GLKMatrix4 GLKMatrix4Scale(GLKMatrix4 matrix, float sx, float sy, float sz)
{
#if   defined(GLK_SSE3_INTRINSICS)
    GLKMatrix4 m;
    
    _mm_store_ps(&m.m[0],  _mm_load_ps(&matrix.m[0])  * _mm_load1_ps(&sx));
    _mm_store_ps(&m.m[4],  _mm_load_ps(&matrix.m[4])  * _mm_load1_ps(&sy));
    _mm_store_ps(&m.m[8],  _mm_load_ps(&matrix.m[8])  * _mm_load1_ps(&sz));
    _mm_store_ps(&m.m[12], _mm_load_ps(&matrix.m[12]));
	    
    return m;
#else
    GLKMatrix4 m = {{ matrix.m[0] * sx, matrix.m[1] * sx, matrix.m[2] * sx, matrix.m[3] * sx,
                      matrix.m[4] * sy, matrix.m[5] * sy, matrix.m[6] * sy, matrix.m[7] * sy,
                      matrix.m[8] * sz, matrix.m[9] * sz, matrix.m[10] * sz, matrix.m[11] * sz,
                      matrix.m[12], matrix.m[13], matrix.m[14], matrix.m[15] }};
    return m;
#endif
}

GLK_INLINE GLKMatrix4 GLKMatrix4ScaleWithVector3(GLKMatrix4 matrix, GLKVector3 scaleVector)
{
#if   defined(GLK_SSE3_INTRINSICS)
    GLKMatrix4 m;
    
    _mm_store_ps(&m.m[0],  _mm_load_ps(&matrix.m[0])  * _mm_load1_ps(&scaleVector.v[0]));
    _mm_store_ps(&m.m[4],  _mm_load_ps(&matrix.m[4])  * _mm_load1_ps(&scaleVector.v[1]));
    _mm_store_ps(&m.m[8],  _mm_load_ps(&matrix.m[8])  * _mm_load1_ps(&scaleVector.v[2]));
    _mm_store_ps(&m.m[12], _mm_load_ps(&matrix.m[12]));
	    
    return m;
#else
    GLKMatrix4 m = {{ matrix.m[0] * scaleVector.v[0], matrix.m[1] * scaleVector.v[0], matrix.m[2] * scaleVector.v[0], matrix.m[3] * scaleVector.v[0],
                      matrix.m[4] * scaleVector.v[1], matrix.m[5] * scaleVector.v[1], matrix.m[6] * scaleVector.v[1], matrix.m[7] * scaleVector.v[1],
                      matrix.m[8] * scaleVector.v[2], matrix.m[9] * scaleVector.v[2], matrix.m[10] * scaleVector.v[2], matrix.m[11] * scaleVector.v[2],
                      matrix.m[12], matrix.m[13], matrix.m[14], matrix.m[15] }};
    return m;
#endif
}

GLK_INLINE GLKMatrix4 GLKMatrix4ScaleWithVector4(GLKMatrix4 matrix, GLKVector4 scaleVector)
{
#if   defined(GLK_SSE3_INTRINSICS)
    GLKMatrix4 m;
    
    _mm_store_ps(&m.m[0],  _mm_load_ps(&matrix.m[0])  * _mm_load1_ps(&scaleVector.v[0]));
    _mm_store_ps(&m.m[4],  _mm_load_ps(&matrix.m[4])  * _mm_load1_ps(&scaleVector.v[1]));
    _mm_store_ps(&m.m[8],  _mm_load_ps(&matrix.m[8])  * _mm_load1_ps(&scaleVector.v[2]));
    _mm_store_ps(&m.m[12], _mm_load_ps(&matrix.m[12]));
	    
    return m;
#else
    GLKMatrix4 m = {{ matrix.m[0] * scaleVector.v[0], matrix.m[1] * scaleVector.v[0], matrix.m[2] * scaleVector.v[0], matrix.m[3] * scaleVector.v[0],
                      matrix.m[4] * scaleVector.v[1], matrix.m[5] * scaleVector.v[1], matrix.m[6] * scaleVector.v[1], matrix.m[7] * scaleVector.v[1],
                      matrix.m[8] * scaleVector.v[2], matrix.m[9] * scaleVector.v[2], matrix.m[10] * scaleVector.v[2], matrix.m[11] * scaleVector.v[2],
                      matrix.m[12], matrix.m[13], matrix.m[14], matrix.m[15] }};
    return m;
#endif
}

GLK_INLINE GLKMatrix4 GLKMatrix4Rotate(GLKMatrix4 matrix, float radians, float x, float y, float z)
{
    GLKMatrix4 rm = GLKMatrix4MakeRotation(radians, x, y, z);
    return GLKMatrix4Multiply(matrix, rm);
}

GLK_INLINE GLKMatrix4 GLKMatrix4RotateWithVector3(GLKMatrix4 matrix, float radians, GLKVector3 axisVector)
{
    GLKMatrix4 rm = GLKMatrix4MakeRotation(radians, axisVector.v[0], axisVector.v[1], axisVector.v[2]);
    return GLKMatrix4Multiply(matrix, rm);
}

GLK_INLINE GLKMatrix4 GLKMatrix4RotateWithVector4(GLKMatrix4 matrix, float radians, GLKVector4 axisVector)
{
    GLKMatrix4 rm = GLKMatrix4MakeRotation(radians, axisVector.v[0], axisVector.v[1], axisVector.v[2]);
    return GLKMatrix4Multiply(matrix, rm);    
}
    
GLK_INLINE GLKMatrix4 GLKMatrix4RotateX(GLKMatrix4 matrix, float radians)
{
    GLKMatrix4 rm = GLKMatrix4MakeXRotation(radians);
    return GLKMatrix4Multiply(matrix, rm);
}

GLK_INLINE GLKMatrix4 GLKMatrix4RotateY(GLKMatrix4 matrix, float radians)
{
    GLKMatrix4 rm = GLKMatrix4MakeYRotation(radians);
    return GLKMatrix4Multiply(matrix, rm);
}

GLK_INLINE GLKMatrix4 GLKMatrix4RotateZ(GLKMatrix4 matrix, float radians)
{
    GLKMatrix4 rm = GLKMatrix4MakeZRotation(radians);
    return GLKMatrix4Multiply(matrix, rm);
}
    
GLK_INLINE GLKVector3 GLKMatrix4MultiplyVector3(GLKMatrix4 matrixLeft, GLKVector3 vectorRight)
{
    GLKVector4 v4 = GLKMatrix4MultiplyVector4(matrixLeft, GLKVector4Make(vectorRight.v[0], vectorRight.v[1], vectorRight.v[2], 0.0f));
    return GLKVector3Make(v4.v[0], v4.v[1], v4.v[2]);
}

GLK_INLINE GLKVector3 GLKMatrix4MultiplyVector3WithTranslation(GLKMatrix4 matrixLeft, GLKVector3 vectorRight)
{
    GLKVector4 v4 = GLKMatrix4MultiplyVector4(matrixLeft, GLKVector4Make(vectorRight.v[0], vectorRight.v[1], vectorRight.v[2], 1.0f));
    return GLKVector3Make(v4.v[0], v4.v[1], v4.v[2]);
}
    
GLK_INLINE GLKVector3 GLKMatrix4MultiplyAndProjectVector3(GLKMatrix4 matrixLeft, GLKVector3 vectorRight)
{
    GLKVector4 v4 = GLKMatrix4MultiplyVector4(matrixLeft, GLKVector4Make(vectorRight.v[0], vectorRight.v[1], vectorRight.v[2], 1.0f));
    return GLKVector3MultiplyScalar(GLKVector3Make(v4.v[0], v4.v[1], v4.v[2]), 1.0f / v4.v[3]);
}

GLK_INLINE void GLKMatrix4MultiplyVector3Array(GLKMatrix4 matrix, GLKVector3 *__nonnull vectors, size_t vectorCount)
{
    int i;
    for (i=0; i < vectorCount; i++)
        vectors[i] = GLKMatrix4MultiplyVector3(matrix, vectors[i]);
}

GLK_INLINE void GLKMatrix4MultiplyVector3ArrayWithTranslation(GLKMatrix4 matrix, GLKVector3 *__nonnull vectors, size_t vectorCount)
{
    int i;
    for (i=0; i < vectorCount; i++)
        vectors[i] = GLKMatrix4MultiplyVector3WithTranslation(matrix, vectors[i]);
}
    
GLK_INLINE void GLKMatrix4MultiplyAndProjectVector3Array(GLKMatrix4 matrix, GLKVector3 *__nonnull vectors, size_t vectorCount)
{
    int i;
    for (i=0; i < vectorCount; i++)
        vectors[i] = GLKMatrix4MultiplyAndProjectVector3(matrix, vectors[i]);
}

GLK_INLINE GLKVector4 GLKMatrix4MultiplyVector4(GLKMatrix4 matrixLeft, GLKVector4 vectorRight)
{
#if   defined(GLK_SSE3_INTRINSICS)
	const __m128 v = _mm_load_ps(&vectorRight.v[0]);

	const __m128 r = _mm_load_ps(&matrixLeft.m[0])  * _mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 0, 0, 0))
	               + _mm_load_ps(&matrixLeft.m[4])  * _mm_shuffle_ps(v, v, _MM_SHUFFLE(1, 1, 1, 1))
	               + _mm_load_ps(&matrixLeft.m[8])  * _mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 2, 2, 2))
	               + _mm_load_ps(&matrixLeft.m[12]) * _mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 3, 3, 3));
    
	GLKVector4 ret;
	*(__m128*)&ret = r;
    return ret;
#else
    GLKVector4 v = {{ matrixLeft.m[0] * vectorRight.v[0] + matrixLeft.m[4] * vectorRight.v[1] + matrixLeft.m[8] * vectorRight.v[2] + matrixLeft.m[12] * vectorRight.v[3],
                      matrixLeft.m[1] * vectorRight.v[0] + matrixLeft.m[5] * vectorRight.v[1] + matrixLeft.m[9] * vectorRight.v[2] + matrixLeft.m[13] * vectorRight.v[3],
                      matrixLeft.m[2] * vectorRight.v[0] + matrixLeft.m[6] * vectorRight.v[1] + matrixLeft.m[10] * vectorRight.v[2] + matrixLeft.m[14] * vectorRight.v[3],
                      matrixLeft.m[3] * vectorRight.v[0] + matrixLeft.m[7] * vectorRight.v[1] + matrixLeft.m[11] * vectorRight.v[2] + matrixLeft.m[15] * vectorRight.v[3] }};
    return v;
#endif
}

GLK_INLINE void GLKMatrix4MultiplyVector4Array(GLKMatrix4 matrix, GLKVector4 *__nonnull vectors, size_t vectorCount)
{
    int i;
    for (i=0; i < vectorCount; i++)
        vectors[i] = GLKMatrix4MultiplyVector4(matrix, vectors[i]);
}
    
#ifdef __cplusplus
}
#endif

#endif /* __GLK_MATRIX_4_H */
