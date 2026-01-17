//
//  SceneKit_simd.h
//
//  Copyright (c) 2012-2014 Apple Inc. All rights reserved.
//

#import <simd/simd.h>

/*! @header SceneKit_simd.h
    @abstract Bridge with the SIMD math library
 */

/* vector_ext bridge */
NS_INLINE vector_float3 SCNVector3ToFloat3(SCNVector3 v) {
    vector_float3 vec = {(float)v.x, (float)v.y, (float)v.z};
    return vec;
}

NS_INLINE vector_float4 SCNVector4ToFloat4(SCNVector4 v) {
    vector_float4 vec = {(float)v.x, (float)v.y, (float)v.z, (float)v.w};
    return vec;
}

NS_INLINE matrix_float4x4 SCNMatrix4ToMat4(SCNMatrix4 m) {
    matrix_float4x4 mat;
    mat.columns[0] = (vector_float4){(float)m.m11, (float)m.m12, (float)m.m13, (float)m.m14};
    mat.columns[1] = (vector_float4){(float)m.m21, (float)m.m22, (float)m.m23, (float)m.m24};
    mat.columns[2] = (vector_float4){(float)m.m31, (float)m.m32, (float)m.m33, (float)m.m34};
    mat.columns[3] = (vector_float4){(float)m.m41, (float)m.m42, (float)m.m43, (float)m.m44};
    return mat;
}
    
NS_INLINE SCNVector3 SCNVector3FromFloat3(vector_float3 v) {
    SCNVector3 vec = {v.x, v.y, v.z } ;
    return vec;
}

NS_INLINE SCNVector4 SCNVector4FromFloat4(vector_float4 v) {
    SCNVector4 vec = {v.x, v.y, v.z, v.z } ;
    return vec;
}

NS_INLINE SCNMatrix4 SCNMatrix4FromMat4(matrix_float4x4 m) {
    SCNMatrix4 mat;
    mat.m11 = m.columns[0].x; mat.m12 = m.columns[0].y; mat.m13 = m.columns[0].z; mat.m14 = m.columns[0].w;
    mat.m21 = m.columns[1].x; mat.m22 = m.columns[1].y; mat.m23 = m.columns[1].z; mat.m24 = m.columns[1].w;
    mat.m31 = m.columns[2].x; mat.m32 = m.columns[2].y; mat.m33 = m.columns[2].z; mat.m34 = m.columns[2].w;
    mat.m41 = m.columns[3].x; mat.m42 = m.columns[3].y; mat.m43 = m.columns[3].z; mat.m44 = m.columns[3].w;
    return mat;
}

