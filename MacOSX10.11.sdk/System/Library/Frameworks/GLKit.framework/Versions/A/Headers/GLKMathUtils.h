//
//  GLKMathUtils.h
//  GLKit
//
//  Copyright (c) 2011-2012, Apple Inc. All rights reserved.
//

#ifndef __GLK_MATH_UTILS_H
#define __GLK_MATH_UTILS_H

#include <math.h>
#include <stdbool.h>

#include <GLKit/GLKMathTypes.h>

#ifdef __OBJC__
#import <Foundation/Foundation.h>
NS_ASSUME_NONNULL_BEGIN
#endif

#ifdef __cplusplus
extern "C" {
#endif

GLK_INLINE float GLKMathDegreesToRadians(float degrees) { return degrees * (M_PI / 180); };
GLK_INLINE float GLKMathRadiansToDegrees(float radians) { return radians * (180 / M_PI); };
    
GLKVector3 GLKMathProject(GLKVector3 object, GLKMatrix4 model, GLKMatrix4 projection, int *viewport);
GLKVector3 GLKMathUnproject(GLKVector3 window, GLKMatrix4 model, GLKMatrix4 projection, int *viewport, bool *success);

#ifdef __OBJC__
NSString * NSStringFromGLKMatrix2(GLKMatrix2 matrix);
NSString * NSStringFromGLKMatrix3(GLKMatrix3 matrix);
NSString * NSStringFromGLKMatrix4(GLKMatrix4 matrix);
    
NSString * NSStringFromGLKVector2(GLKVector2 vector);
NSString * NSStringFromGLKVector3(GLKVector3 vector);
NSString * NSStringFromGLKVector4(GLKVector4 vector);
    
NSString * NSStringFromGLKQuaternion(GLKQuaternion quaternion);
NS_ASSUME_NONNULL_END
#endif
    
#ifdef __cplusplus
}
#endif

#endif /* __GLK_MATH_UTILS_H */
