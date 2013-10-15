/*
	Copyright:	(c) 1999 by Apple Computer, Inc., all rights reserved.
*/

#ifndef _OPENGL_H
#define _OPENGL_H

#include <AvailabilityMacros.h>
#include <OpenGL/CGLCurrent.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
** CGL API version.
*/
#define CGL_VERSION_1_0  1
#define CGL_VERSION_1_1  1


/*
** Pixel format functions
*/
extern CGLError CGLChoosePixelFormat(const CGLPixelFormatAttribute *attribs, CGLPixelFormatObj *pix, long *npix);
extern CGLError CGLDestroyPixelFormat(CGLPixelFormatObj pix);
extern CGLError CGLDescribePixelFormat(CGLPixelFormatObj pix, long pix_num, CGLPixelFormatAttribute attrib, long *value);

/*
** Renderer information functions
*/
extern CGLError CGLQueryRendererInfo(unsigned long display_mask, CGLRendererInfoObj *rend, long *nrend);
extern CGLError CGLDestroyRendererInfo(CGLRendererInfoObj rend);
extern CGLError CGLDescribeRenderer(CGLRendererInfoObj rend, long rend_num, CGLRendererProperty prop, long *value);

/*
** Context functions
*/
extern CGLError CGLCreateContext(CGLPixelFormatObj pix, CGLContextObj share, CGLContextObj *ctx);
extern CGLError CGLDestroyContext(CGLContextObj ctx);
extern CGLError CGLCopyContext(CGLContextObj src, CGLContextObj dst, unsigned long mask);

/*
** PBuffer functions
*/
extern CGLError CGLCreatePBuffer(long width, long height, unsigned long target, unsigned long internalFormat, long max_level, CGLPBufferObj *pbuffer) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

extern CGLError CGLDestroyPBuffer(CGLPBufferObj pbuffer) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

extern CGLError CGLDescribePBuffer(CGLPBufferObj obj, long *width, long *height, unsigned long *target, unsigned long *internalFormat, long *mipmap) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

extern CGLError CGLTexImagePBuffer(CGLContextObj ctx, CGLPBufferObj pbuffer, unsigned long source) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*
** Drawable Functions
*/
extern CGLError CGLSetOffScreen(CGLContextObj ctx, long width, long height, long rowbytes, void *baseaddr);
extern CGLError CGLGetOffScreen(CGLContextObj ctx, long *width, long *height, long *rowbytes, void **baseaddr);
extern CGLError CGLSetFullScreen(CGLContextObj ctx);

extern CGLError CGLSetPBuffer(CGLContextObj ctx, CGLPBufferObj pbuffer, unsigned long face, long level, long screen) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

extern CGLError CGLGetPBuffer(CGLContextObj ctx, CGLPBufferObj *pbuffer, unsigned long *face, long *level, long *screen) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

extern CGLError CGLClearDrawable(CGLContextObj ctx);
extern CGLError CGLFlushDrawable(CGLContextObj ctx);

/*
** Per context enables and parameters
*/
extern CGLError CGLEnable(CGLContextObj ctx, CGLContextEnable pname);
extern CGLError CGLDisable(CGLContextObj ctx, CGLContextEnable pname);
extern CGLError CGLIsEnabled(CGLContextObj ctx, CGLContextEnable pname, long *enable);
extern CGLError CGLSetParameter(CGLContextObj ctx, CGLContextParameter pname, const long *params);
extern CGLError CGLGetParameter(CGLContextObj ctx, CGLContextParameter pname, long *params);

/*
** Virtual screen functions
*/
extern CGLError CGLSetVirtualScreen(CGLContextObj ctx, long screen);
extern CGLError CGLGetVirtualScreen(CGLContextObj ctx, long *screen);

/*
** Global library options
*/
extern CGLError CGLSetOption(CGLGlobalOption pname, long param);
extern CGLError CGLGetOption(CGLGlobalOption pname, long *param);

/*
** Locking functions
*/
extern CGLError CGLLockContext(CGLContextObj ctx) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

extern CGLError CGLUnlockContext(CGLContextObj ctx) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*
** Version numbers
*/
extern void CGLGetVersion(long *majorvers, long *minorvers);

/*
** Convert an error code to a string
*/
const char *CGLErrorString(CGLError error);


#ifdef __cplusplus
}
#endif

#endif /* _OPENGL_H */

