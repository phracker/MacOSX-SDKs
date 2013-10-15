/*
    File:	AGL/glm.h

    Contains:	Basic GLMemoryLibrary data types, constants and function prototypes.

    Version:	Technology:	Mac OS X
                Release:	GM
 
     Copyright:  (c) 2000-2002 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef _GLM_H
#define _GLM_H

#include <OpenGL/gl.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
** Interface version
*/
#define GLM_VERSION_2_0                  1

/*
** Mode types - glmSetMode
*/
#define GLM_OVERRIDE_MODE                0x0001
#define GLM_SYSTEM_HEAP_MODE             0x0002
#define GLM_APPLICATION_HEAP_MODE        0x0003
#define GLM_MULTIPROCESSOR_MODE          0x0004

/*
** Function types - glmSetFunc
*/
#define GLM_PAGE_ALLOCATION_FUNC_PTR     0x0001
#define GLM_PAGE_FREE_FUNC_PTR           0x0002

#define GLM_ZERO_FUNC_PTR                0x0003
#define GLM_COPY_FUNC_PTR                0x0004
#define GLM_SET_UBYTE_FUNC_PTR           0x0005
#define GLM_SET_USHORT_FUNC_PTR          0x0006
#define GLM_SET_UINT_FUNC_PTR            0x0007
#define GLM_SET_DOUBLE_FUNC_PTR          0x0008

/*
** Integer types - glmSetInteger
*/
#define GLM_PAGE_SIZE                    0x0001

/*
** Integer types - glmGetInteger
*/
/*#define GLM_PAGE_SIZE                  0x0001*/
#define GLM_NUMBER_PAGES                 0x0002
#define GLM_CURRENT_MEMORY               0x0003
#define GLM_MAXIMUM_MEMORY               0x0004

/*
** Integer types - glmGetError
*/
#define GLM_NO_ERROR                     0
#define GLM_INVALID_ENUM                 0x0001
#define GLM_INVALID_VALUE                0x0002
#define GLM_INVALID_OPERATION            0x0003
#define GLM_OUT_OF_MEMORY                0x0004

/*
** Function pointer types
*/
typedef GLvoid *(*GLMPageAllocFunc)(GLsizei size);
typedef void (*GLMPageFreeFunc)(GLvoid *ptr);

typedef void (*GLMZeroFunc)(GLubyte *buffer, GLsizei width, GLsizei height, GLsizei skip);
typedef void (*GLMCopyFunc)(const GLubyte *src, GLubyte *dst, GLsizei width, GLsizei height, GLsizei src_skip, GLsizei dst_skip);
typedef void (*GLMSetUByteFunc)(GLubyte *buffer, GLsizei width, GLsizei height, GLsizei skip, GLubyte value);
typedef void (*GLMSetUShortFunc)(GLushort *buffer, GLsizei width, GLsizei height, GLsizei skip, GLushort value);
typedef void (*GLMSetUIntFunc)(GLuint *buffer, GLsizei width, GLsizei height, GLsizei skip, GLuint value);
typedef void (*GLMSetDoubleFunc)(GLdouble *buffer, GLsizei width, GLsizei height, GLsizei skip, GLdouble value);
	
typedef union {
	GLMPageAllocFunc   page_alloc_func;
	GLMPageFreeFunc    page_free_func;
	
	GLMZeroFunc        zero_func;
	GLMCopyFunc        copy_func;
	GLMSetUByteFunc    set_ubyte_func;
	GLMSetUShortFunc   set_ushort_func;
	GLMSetUIntFunc     set_uint_func;
	GLMSetDoubleFunc   set_double_func;
} GLMfunctions;

/*
** Prototypes
*/
extern void glmSetMode(GLenum mode);
extern void glmSetFunc(GLenum type, GLMfunctions func);

extern void glmSetInteger(GLenum param, GLint value);
extern GLint glmGetInteger(GLenum param);

extern void	glmPageFreeAll(void);

extern GLvoid *glmMalloc(GLsizei size);
extern GLvoid *glmCalloc(GLsizei nmemb, GLsizei size);
extern GLvoid *glmRealloc(GLvoid *ptr, GLsizei size);
extern void glmFree(GLvoid *ptr);

/* 16 byte aligned */
extern GLvoid *glmVecAlloc(GLsizei size);
extern void glmVecFree(GLvoid *ptr);

/* 32 byte aligned and 32 byte padded */
extern GLvoid *glmDCBAlloc(GLsizei size);
extern void glmDCBFree(GLvoid *ptr);

extern void glmZero(GLubyte *buffer, GLsizei width, GLsizei height, GLsizei rowbytes);
extern void glmCopy(const GLubyte *src, GLubyte *dst, GLsizei width, GLsizei height, GLsizei src_rowbytes, GLsizei dst_rowbytes);
extern void glmSetUByte(GLubyte *buffer, GLsizei width, GLsizei height, GLsizei row_elems, GLubyte value);
extern void glmSetUShort(GLushort *buffer, GLsizei width, GLsizei height, GLsizei row_elems, GLushort value);
extern void glmSetUInt(GLuint *buffer, GLsizei width, GLsizei height, GLsizei row_elems, GLuint value);
extern void glmSetDouble(GLdouble *buffer, GLsizei width, GLsizei height, GLsizei row_elems, GLdouble value);

extern GLenum glmGetError(void);

#ifdef __cplusplus
}
#endif

#endif /* _GLM_H */
