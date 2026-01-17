/*
	Copyright:	(c) 1999-2012 Apple Inc. All rights reserved.
*/

#ifndef _OPENGL_H
#define _OPENGL_H

#include <AvailabilityMacros.h>
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
extern void CGLReleasePixelFormat(CGLPixelFormatObj pix) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern CGLPixelFormatObj CGLRetainPixelFormat(CGLPixelFormatObj pix) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern GLuint CGLGetPixelFormatRetainCount(CGLPixelFormatObj pix) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

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
#ifdef AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER
extern CGLError CGLCopyContext(CGLContextObj src, CGLContextObj dst, GLbitfield mask) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;
#else
extern CGLError CGLCopyContext(CGLContextObj src, CGLContextObj dst, GLbitfield mask);
#endif
extern CGLContextObj CGLRetainContext(CGLContextObj ctx) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern void CGLReleaseContext(CGLContextObj ctx) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern GLuint CGLGetContextRetainCount(CGLContextObj ctx) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern CGLPixelFormatObj CGLGetPixelFormat(CGLContextObj ctx) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*
** PBuffer functions
*/
extern CGLError CGLCreatePBuffer(GLsizei width, GLsizei height, GLenum target, GLenum internalFormat, GLint max_level, CGLPBufferObj *pbuffer) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_7;
extern CGLError CGLDestroyPBuffer(CGLPBufferObj pbuffer) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_7;
extern CGLError CGLDescribePBuffer(CGLPBufferObj obj, GLsizei *width, GLsizei *height, GLenum *target, GLenum *internalFormat, GLint *mipmap) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_7;
extern CGLError CGLTexImagePBuffer(CGLContextObj ctx, CGLPBufferObj pbuffer, GLenum source) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_7;
extern CGLPBufferObj CGLRetainPBuffer(CGLPBufferObj pbuffer) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_7;
extern void CGLReleasePBuffer(CGLPBufferObj pbuffer) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_7;
extern GLuint CGLGetPBufferRetainCount(CGLPBufferObj pbuffer) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_7;

/*
** Drawable Functions
*/
extern CGLError CGLSetOffScreen(CGLContextObj ctx, GLsizei width, GLsizei height, GLint rowbytes, void *baseaddr) DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;
extern CGLError CGLGetOffScreen(CGLContextObj ctx, GLsizei *width, GLsizei *height, GLint *rowbytes, void **baseaddr) DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;
extern CGLError CGLSetFullScreen(CGLContextObj ctx) DEPRECATED_IN_MAC_OS_X_VERSION_10_6_AND_LATER;
extern CGLError CGLSetFullScreenOnDisplay(CGLContextObj ctx, GLuint display_mask) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_7;

extern CGLError CGLSetPBuffer(CGLContextObj ctx, CGLPBufferObj pbuffer, GLenum face, GLint level, GLint screen) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_7;
extern CGLError CGLGetPBuffer(CGLContextObj ctx, CGLPBufferObj *pbuffer, GLenum *face, GLint *level, GLint *screen) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_7;

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

extern CGLError CGLUpdateContext(CGLContextObj ctx);

/*
** Global library options
*/
extern CGLError CGLSetGlobalOption(CGLGlobalOption pname, const GLint *params) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
extern CGLError CGLGetGlobalOption(CGLGlobalOption pname, GLint *params) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern CGLError CGLSetOption(CGLGlobalOption pname, GLint param);  /* Use CGLSetGlobalOption */
extern CGLError CGLGetOption(CGLGlobalOption pname, GLint *param); /* Use CGLGetGlobalOption */

/*
** Locking functions
*/
extern CGLError CGLLockContext(CGLContextObj ctx) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

extern CGLError CGLUnlockContext(CGLContextObj ctx) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

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

