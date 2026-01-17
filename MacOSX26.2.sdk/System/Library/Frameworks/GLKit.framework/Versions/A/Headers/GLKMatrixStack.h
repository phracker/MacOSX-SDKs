//
//  GLKMatrixStack.h
//  GLKit
//
//  Copyright (c) 2011-2012, Apple Inc. All rights reserved.
//

#ifndef __GLK_MATRIX_STACK_H
#define __GLK_MATRIX_STACK_H

#include <CoreFoundation/CoreFoundation.h>

#include <GLKit/GLKMathTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 GLKMatrixStack is a CFType that allows for the creation of a 4x4 matrix stack similar to OpenGL's matrix
 stack. Any number of matrix stacks can be created and operated on with functions similar to those found
 in fixed function versions of OpenGL.
 */
    
typedef struct CF_BRIDGED_TYPE(id) _GLKMatrixStack *GLKMatrixStackRef;

/* 
 CFType GLKMatrixStack creation routine. Pass NULL or kCFAllocatorDefault to use the current default
 allocator. A newly created stack is initialized with the identity matrix.
 */
GLKMatrixStackRef __nullable GLKMatrixStackCreate(CFAllocatorRef __nullable alloc);

/*
 Returns the type identifier for the GLKMatrixStack opaque type.
 */
CFTypeID GLKMatrixStackGetTypeID(void);

/*
 Pushes all of the matrices down one level and copies the topmost matrix.
 */
void GLKMatrixStackPush(GLKMatrixStackRef __nonnull stack);
/*
 Pops the topmost matrix off of the stack, moving the rest of the matrices up one level.
 */
void GLKMatrixStackPop(GLKMatrixStackRef __nonnull stack);

/*
 Returns the number of matrices currently on the stack.
 */
int GLKMatrixStackSize(GLKMatrixStackRef __nonnull stack);

/*
 Replaces the topmost matrix with the matrix provided.
 */
void GLKMatrixStackLoadMatrix4(GLKMatrixStackRef __nonnull stack, GLKMatrix4 matrix);

/*
 Returns the 4x4 matrix currently residing on top of the stack.
 */
GLKMatrix4 GLKMatrixStackGetMatrix4(GLKMatrixStackRef __nonnull stack);
/*
 Returns the upper left 3x3 portion of the matrix currently residing on top of the stack.
 */
GLKMatrix3 GLKMatrixStackGetMatrix3(GLKMatrixStackRef __nonnull stack);
/*
 Returns the upper left 2x2 portion of the matrix currently residing on top of the stack.
 */
GLKMatrix2 GLKMatrixStackGetMatrix2(GLKMatrixStackRef __nonnull stack);

/*
 Calculate and return the inverse matrix from the matrix currently residing on top of stack.
 */
GLKMatrix4 GLKMatrixStackGetMatrix4Inverse(GLKMatrixStackRef __nonnull stack);
/*
 Calculate and return the inverse transpose matrix from the matrix currently residing on top of stack.
 */
GLKMatrix4 GLKMatrixStackGetMatrix4InverseTranspose(GLKMatrixStackRef __nonnull stack);

/*
 Calculate and return the upper left 3x3 inverse matrix from the matrix currently residing on top of stack.
 */
GLKMatrix3 GLKMatrixStackGetMatrix3Inverse(GLKMatrixStackRef __nonnull stack);
/*
 Calculate and return the upper left 3x3 inverse transpose matrix from the matrix currently residing on top of stack.
 */
GLKMatrix3 GLKMatrixStackGetMatrix3InverseTranspose(GLKMatrixStackRef __nonnull stack);

/*
 Multiply the topmost matrix with the matrix provided.
 */
void GLKMatrixStackMultiplyMatrix4(GLKMatrixStackRef __nonnull stack, GLKMatrix4 matrix);

/*
 Multiply the topmost matrix of the stackLeft with the topmost matrix of stackRight and store in stackLeft.
 */
void GLKMatrixStackMultiplyMatrixStack(GLKMatrixStackRef __nonnull stackLeft, GLKMatrixStackRef __nonnull stackRight);
    
/*
 Translate the topmost matrix.
 */
void GLKMatrixStackTranslate(GLKMatrixStackRef __nonnull stack, float tx, float ty, float tz);
void GLKMatrixStackTranslateWithVector3(GLKMatrixStackRef __nonnull stack, GLKVector3 translationVector);
void GLKMatrixStackTranslateWithVector4(GLKMatrixStackRef __nonnull stack, GLKVector4 translationVector);
    
/*
 Scale the topmost matrix.
 */
void GLKMatrixStackScale(GLKMatrixStackRef __nonnull stack, float sx, float sy, float sz);
void GLKMatrixStackScaleWithVector3(GLKMatrixStackRef __nonnull stack, GLKVector3 scaleVector);
void GLKMatrixStackScaleWithVector4(GLKMatrixStackRef __nonnull stack, GLKVector4 scaleVector);
    
/*
 Rotate the topmost matrix about the specified axis.
 */
void GLKMatrixStackRotate(GLKMatrixStackRef __nonnull stack, float radians, float x, float y, float z);
void GLKMatrixStackRotateWithVector3(GLKMatrixStackRef __nonnull stack, float radians, GLKVector3 axisVector);
void GLKMatrixStackRotateWithVector4(GLKMatrixStackRef __nonnull stack, float radians, GLKVector4 axisVector);
     
/*
 Rotate the topmost matrix about the x, y, or z axis.
 */
void GLKMatrixStackRotateX(GLKMatrixStackRef __nonnull stack, float radians);
void GLKMatrixStackRotateY(GLKMatrixStackRef __nonnull stack, float radians);
void GLKMatrixStackRotateZ(GLKMatrixStackRef __nonnull stack, float radians);

#ifdef __cplusplus
}
#endif

#endif /* __GLK_MATRIX_STACK_H */
