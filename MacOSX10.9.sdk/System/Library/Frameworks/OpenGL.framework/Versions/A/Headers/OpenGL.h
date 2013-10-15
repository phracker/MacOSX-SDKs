/*
	Copyright:	(c) 1999-2012 Apple Inc. All rights reserved.
*/

#ifndef _OPENGL_H
#define _OPENGL_H

#include <OpenGL/OpenGLAvailability.h>
#include <OpenGL/CGLCurrent.h>
#include <OpenGL/CGLDevice.h>
#include <OpenGL/CGLRenderers.h>
#include <OpenGL/CGLIOSurface.h>
#include <OpenGL/gltypes.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
** CGL API version.
*/
#define CGL_VERSION_1_0  1
#define CGL_VERSION_1_1  1
#define CGL_VERSION_1_2  1
#define CGL_VERSION_1_3  1


/*
** Pixel format functions
*/
extern CGLError CGLChoosePixelFormat(const CGLPixelFormatAttribute *attribs, CGLPixelFormatObj *pix, GLint *npix);
extern CGLError CGLDestroyPixelFormat(CGLPixelFormatObj pix);
extern CGLError CGLDescribePixelFormat(CGLPixelFormatObj pix, GLint pix_num, CGLPixelFormatAttribute attrib, GLint *value);
extern void CGLReleasePixelFormat(CGLPixelFormatObj pix) OPENGL_AVAILABLE(10_5);
extern CGLPixelFormatObj CGLRetainPixelFormat(CGLPixelFormatObj pix) OPENGL_AVAILABLE(10_5);
extern GLuint CGLGetPixelFormatRetainCount(CGLPixelFormatObj pix) OPENGL_AVAILABLE(10_5);

/*
** Renderer information functions
*/
extern CGLError CGLQueryRendererInfo(GLuint display_mask, CGLRendererInfoObj *rend, GLint *nrend);
extern CGLError CGLDestroyRendererInfo(CGLRendererInfoObj rend);
extern CGLError CGLDescribeRenderer(CGLRendererInfoObj rend, GLint rend_num, CGLRendererProperty prop, GLint *value);

/*
** Context functions
*/
extern CGLError CGLCreateContext(CGLPixelFormatObj pix, CGLContextObj share, CGLContextObj *ctx);
extern CGLError CGLDestroyContext(CGLContextObj ctx);
extern CGLError CGLCopyContext(CGLContextObj src, CGLContextObj dst, GLbitfield mask) OPENGL_DEPRECATED(10_0, 10_8);
extern CGLContextObj CGLRetainContext(CGLContextObj ctx) OPENGL_AVAILABLE(10_5);
extern void CGLReleaseContext(CGLContextObj ctx) OPENGL_AVAILABLE(10_5);
extern GLuint CGLGetContextRetainCount(CGLContextObj ctx) OPENGL_AVAILABLE(10_5);
extern CGLPixelFormatObj CGLGetPixelFormat(CGLContextObj ctx) OPENGL_AVAILABLE(10_5);

/*
** PBuffer functions
*/
extern CGLError CGLCreatePBuffer(GLsizei width, GLsizei height, GLenum target, GLenum internalFormat, GLint max_level, CGLPBufferObj *pbuffer) OPENGL_DEPRECATED(10_3, 10_7);
extern CGLError CGLDestroyPBuffer(CGLPBufferObj pbuffer) OPENGL_DEPRECATED(10_3, 10_7);
extern CGLError CGLDescribePBuffer(CGLPBufferObj obj, GLsizei *width, GLsizei *height, GLenum *target, GLenum *internalFormat, GLint *mipmap) OPENGL_DEPRECATED(10_3, 10_7);
extern CGLError CGLTexImagePBuffer(CGLContextObj ctx, CGLPBufferObj pbuffer, GLenum source) OPENGL_DEPRECATED(10_3, 10_7);
extern CGLPBufferObj CGLRetainPBuffer(CGLPBufferObj pbuffer) OPENGL_DEPRECATED(10_5, 10_7);
extern void CGLReleasePBuffer(CGLPBufferObj pbuffer) OPENGL_DEPRECATED(10_5, 10_7);
extern GLuint CGLGetPBufferRetainCount(CGLPBufferObj pbuffer) OPENGL_DEPRECATED(10_5, 10_7);

/*
** Drawable Functions
*/
extern CGLError CGLSetOffScreen(CGLContextObj ctx, GLsizei width, GLsizei height, GLint rowbytes, void *baseaddr) OPENGL_DEPRECATED(10_0, 10_7);
extern CGLError CGLGetOffScreen(CGLContextObj ctx, GLsizei *width, GLsizei *height, GLint *rowbytes, void **baseaddr) OPENGL_DEPRECATED(10_0, 10_7);
extern CGLError CGLSetFullScreen(CGLContextObj ctx) OPENGL_DEPRECATED(10_0, 10_6);
extern CGLError CGLSetFullScreenOnDisplay(CGLContextObj ctx, GLuint display_mask) OPENGL_DEPRECATED(10_5, 10_7);

extern CGLError CGLSetPBuffer(CGLContextObj ctx, CGLPBufferObj pbuffer, GLenum face, GLint level, GLint screen) OPENGL_DEPRECATED(10_3, 10_7);
extern CGLError CGLGetPBuffer(CGLContextObj ctx, CGLPBufferObj *pbuffer, GLenum *face, GLint *level, GLint *screen) OPENGL_DEPRECATED(10_3, 10_7);

extern CGLError CGLClearDrawable(CGLContextObj ctx);
extern CGLError CGLFlushDrawable(CGLContextObj ctx);

/*
** Per context enables and parameters
*/
extern CGLError CGLEnable(CGLContextObj ctx, CGLContextEnable pname);
extern CGLError CGLDisable(CGLContextObj ctx, CGLContextEnable pname);
extern CGLError CGLIsEnabled(CGLContextObj ctx, CGLContextEnable pname, GLint *enable);
extern CGLError CGLSetParameter(CGLContextObj ctx, CGLContextParameter pname, const GLint *params);
extern CGLError CGLGetParameter(CGLContextObj ctx, CGLContextParameter pname, GLint *params);

/*
** Virtual screen functions
*/
extern CGLError CGLSetVirtualScreen(CGLContextObj ctx, GLint screen);
extern CGLError CGLGetVirtualScreen(CGLContextObj ctx, GLint *screen);

extern CGLError CGLUpdateContext(CGLContextObj ctx) OPENGL_AVAILABLE(10_7);

/*
** Global library options
*/
extern CGLError CGLSetGlobalOption(CGLGlobalOption pname, const GLint *params) OPENGL_AVAILABLE(10_6);
extern CGLError CGLGetGlobalOption(CGLGlobalOption pname, GLint *params) OPENGL_AVAILABLE(10_6);

extern CGLError CGLSetOption(CGLGlobalOption pname, GLint param);  /* Use CGLSetGlobalOption */
extern CGLError CGLGetOption(CGLGlobalOption pname, GLint *param); /* Use CGLGetGlobalOption */

/*
** Locking functions
*/
extern CGLError CGLLockContext(CGLContextObj ctx) OPENGL_AVAILABLE(10_4);

extern CGLError CGLUnlockContext(CGLContextObj ctx) OPENGL_AVAILABLE(10_4);

/*
** Version numbers
*/
extern void CGLGetVersion(GLint *majorvers, GLint *minorvers);

/*
** Convert an error code to a string
*/
const char *CGLErrorString(CGLError error);


#ifdef __cplusplus
}
#endif

#endif /* _OPENGL_H */

