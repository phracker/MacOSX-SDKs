/*
	Copyright:	(c) 1999 by Apple Computer, Inc., all rights reserved.
*/

#ifndef _OPENGL_H
#define _OPENGL_H

#include <OpenGL/CGLCurrent.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
** CGL API version.
*/
#define CGL_VERSION_1_0  1


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
** Drawable Functions
*/
extern CGLError CGLSetOffScreen(CGLContextObj ctx, long width, long height, long rowbytes, void *baseaddr);
extern CGLError CGLGetOffScreen(CGLContextObj ctx, long *width, long *height, long *rowbytes, void **baseaddr);
extern CGLError CGLSetFullScreen(CGLContextObj ctx);
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

