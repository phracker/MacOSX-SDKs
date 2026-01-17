#ifndef __GLX_glx_h__
#define __GLX_glx_h__

/* $XFree86: xc/include/GL/glx.h,v 1.11 2003/09/28 20:14:57 alanh Exp $ */
/*
** License Applicability. Except to the extent portions of this file are
** made subject to an alternative license as permitted in the SGI Free
** Software License B, Version 1.1 (the "License"), the contents of this
** file are subject only to the provisions of the License. You may not use
** this file except in compliance with the License. You may obtain a copy
** of the License at Silicon Graphics, Inc., attn: Legal Services, 1600
** Amphitheatre Parkway, Mountain View, CA 94043-1351, or at:
** 
** http://oss.sgi.com/projects/FreeB
** 
** Note that, as provided in the License, the Software is distributed on an
** "AS IS" basis, with ALL EXPRESS AND IMPLIED WARRANTIES AND CONDITIONS
** DISCLAIMED, INCLUDING, WITHOUT LIMITATION, ANY IMPLIED WARRANTIES AND
** CONDITIONS OF MERCHANTABILITY, SATISFACTORY QUALITY, FITNESS FOR A
** PARTICULAR PURPOSE, AND NON-INFRINGEMENT.
** 
** Original Code. The Original Code is: OpenGL Sample Implementation,
** Version 1.2.1, released January 26, 2000, developed by Silicon Graphics,
** Inc. The Original Code is Copyright (c) 1991-2000 Silicon Graphics, Inc.
** Copyright in any portions created by third parties is as indicated
** elsewhere herein. All Rights Reserved.
** 
** Additional Notice Provisions: The application programming interfaces
** established by SGI in conjunction with the Original Code are The
** OpenGL(R) Graphics System: A Specification (Version 1.2.1), released
** April 1, 1999; The OpenGL(R) Graphics System Utility Library (Version
** 1.3), released November 4, 1998; and OpenGL(R) Graphics with the X
** Window System(R) (Version 1.3), released October 19, 1998. This software
** was created using the OpenGL(R) version 1.2.1 Sample Implementation
** published by SGI, but has not been independently verified as being
** compliant with the OpenGL(R) version 1.2.1 Specification.
*/

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/gl.h>
#include <GL/glxtokens.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
** GLX resources.
*/
typedef XID GLXContextID;
typedef XID GLXPixmap;
typedef XID GLXDrawable;
typedef XID GLXPbuffer;
typedef XID GLXWindow;
typedef XID GLXFBConfigID;

/*
** GLXContext is a pointer to opaque data.
*/
typedef struct __GLXcontextRec *GLXContext;

/*
** GLXFBConfig is a pointer to opaque data.
*/
typedef struct __GLXFBConfigRec *GLXFBConfig;

/************************************************************************/

extern XVisualInfo* glXChooseVisual (Display *dpy, int screen, int *attribList);
extern void glXCopyContext (Display *dpy, GLXContext src, GLXContext dst, unsigned long mask);
extern GLXContext glXCreateContext (Display *dpy, XVisualInfo *vis, GLXContext shareList, Bool direct);
extern GLXPixmap glXCreateGLXPixmap (Display *dpy, XVisualInfo *vis, Pixmap pixmap);
extern void glXDestroyContext (Display *dpy, GLXContext ctx);
extern void glXDestroyGLXPixmap (Display *dpy, GLXPixmap pix);
extern int glXGetConfig (Display *dpy, XVisualInfo *vis, int attrib, int *value);
extern GLXContext glXGetCurrentContext (void);
extern GLXDrawable glXGetCurrentDrawable (void);
extern Bool glXIsDirect (Display *dpy, GLXContext ctx);
extern Bool glXMakeCurrent (Display *dpy, GLXDrawable drawable, GLXContext ctx);
extern Bool glXQueryExtension (Display *dpy, int *errorBase, int *eventBase);
extern Bool glXQueryVersion (Display *dpy, int *major, int *minor);
extern void glXSwapBuffers (Display *dpy, GLXDrawable drawable);
extern void glXUseXFont (Font font, int first, int count, int listBase);
extern void glXWaitGL (void);
extern void glXWaitX (void);
extern const char * glXGetClientString (Display *dpy, int name );
extern const char * glXQueryServerString (Display *dpy, int screen, int name );
extern const char * glXQueryExtensionsString (Display *dpy, int screen );

/* New for GLX 1.3 */
extern GLXFBConfig * glXGetFBConfigs (Display *dpy, int screen, int *nelements);
extern GLXFBConfig * glXChooseFBConfig (Display *dpy, int screen, const int *attrib_list, int *nelements);
extern int glXGetFBConfigAttrib (Display *dpy, GLXFBConfig config, int attribute, int *value);
extern XVisualInfo * glXGetVisualFromFBConfig (Display *dpy, GLXFBConfig config);
extern GLXWindow glXCreateWindow (Display *dpy, GLXFBConfig config, Window win, const int *attrib_list);
extern void glXDestroyWindow (Display *dpy, GLXWindow win);
extern GLXPixmap glXCreatePixmap (Display *dpy, GLXFBConfig config, Pixmap pixmap, const int *attrib_list);
extern void glXDestroyPixmap (Display *dpy, GLXPixmap pixmap);
extern GLXPbuffer glXCreatePbuffer (Display *dpy, GLXFBConfig config, const int *attrib_list);
extern void glXDestroyPbuffer (Display *dpy, GLXPbuffer pbuf);
extern void glXQueryDrawable (Display *dpy, GLXDrawable draw, int attribute, unsigned int *value);
extern GLXContext glXCreateNewContext (Display *dpy, GLXFBConfig config, int render_type, GLXContext share_list, Bool direct);
extern Bool glXMakeContextCurrent (Display *display, GLXDrawable draw, GLXDrawable read, GLXContext ctx);
extern GLXDrawable glXGetCurrentReadDrawable (void);
extern Display * glXGetCurrentDisplay (void);
extern int glXQueryContext (Display *dpy, GLXContext ctx, int attribute, int *value);
extern void glXSelectEvent (Display *dpy, GLXDrawable draw, unsigned long event_mask);
extern void glXGetSelectedEvent (Display *dpy, GLXDrawable draw, unsigned long *event_mask);

/* GLX 1.4 and later */
extern void (*glXGetProcAddress(const GLubyte *procname))(void);


#ifndef GLX_GLXEXT_LEGACY

#include <GL/glxext.h>

#else

/* GLX extensions */
#define GLX_EXT_import_context	1
#define GLX_EXT_visual_info	1
#define GLX_EXT_visual_rating	1
#define GLX_ARB_get_proc_address 1
extern GLXContextID glXGetContextIDEXT (const GLXContext ctx);
extern GLXContext glXImportContextEXT (Display *dpy, GLXContextID contextID);
extern void glXFreeContextEXT (Display *dpy, GLXContext ctx);
extern int glXQueryContextInfoEXT (Display *dpy, GLXContext ctx, int attribute, int *value);
extern Display * glXGetCurrentDisplayEXT (void);
extern void (*glXGetProcAddressARB(const GLubyte *procName))( void );



#endif /* GLX_GLXEXT_LEGACY */


/**
 ** The following aren't in glxext.h yet.
 **/


/*
 * ???. GLX_NV_vertex_array_range
 */
#ifndef GLX_NV_vertex_array_range
#define GLX_NV_vertex_array_range

extern void *glXAllocateMemoryNV(GLsizei size, GLfloat readfreq, GLfloat writefreq, GLfloat priority);
extern void glXFreeMemoryNV(GLvoid *pointer);
typedef void * ( * PFNGLXALLOCATEMEMORYNVPROC) (GLsizei size, GLfloat readfreq, GLfloat writefreq, GLfloat priority);
typedef void ( * PFNGLXFREEMEMORYNVPROC) (GLvoid *pointer);

#endif /* GLX_NV_vertex_array_range */



/*
 * ???. GLX_MESA_agp_offset (deprecated)
 */ 
#ifndef GLX_MESA_agp_offset
#define GLX_MESA_agp_offset 1

extern GLuint glXGetAGPOffsetMESA(const GLvoid *pointer);
typedef GLuint (* PFNGLXGETAGPOFFSETMESAPROC) (const GLvoid *pointer);

#endif /* GLX_MESA_agp_offset */


/*
 * ???. GLX_MESA_allocate_memory
 */ 
#ifndef GLX_MESA_allocate_memory
#define GLX_MESA_allocate_memory 1

extern void *glXAllocateMemoryMESA(Display *dpy, int scrn, size_t size, float readfreq, float writefreq, float priority);
extern void glXFreeMemoryMESA(Display *dpy, int scrn, void *pointer);
extern GLuint glXGetMemoryOffsetMESA(Display *dpy, int scrn, const void *pointer);
typedef void * ( * PFNGLXALLOCATEMEMORYMESAPROC) (Display *dpy, int scrn, size_t size, float readfreq, float writefreq, float priority);
typedef void ( * PFNGLXFREEMEMORYMESAPROC) (Display *dpy, int scrn, void *pointer);
typedef GLuint (* PFNGLXGETMEMORYOFFSETMESAPROC) (Display *dpy, int scrn, const void *pointer);

#endif /* GLX_MESA_allocate_memory */

/*
 * ???. GLX_ARB_render_texture
 */
#ifndef GLX_ARB_render_texture
#define GLX_ARB_render_texture 1

Bool glXBindTexImageARB( Display *dpy, GLXPbuffer pbuffer, int buffer );
Bool glXReleaseTexImageARB(Display *dpy, GLXPbuffer pbuffer, int buffer );
Bool glXDrawableAttribARB( Display *dpy, GLXDrawable draw, const int *attribList );

#endif



/*** Should these go here, or in another header? */
/*
** GLX Events
*/
typedef struct {
    int event_type;		/* GLX_DAMAGED or GLX_SAVED */
    int draw_type;		/* GLX_WINDOW or GLX_PBUFFER */
    unsigned long serial;	/* # of last request processed by server */
    Bool send_event;		/* true if this came for SendEvent request */
    Display *display;		/* display the event was read from */
    GLXDrawable drawable;	/* XID of Drawable */
    unsigned int buffer_mask;	/* mask indicating which buffers are affected */
    unsigned int aux_buffer;	/* which aux buffer was affected */
    int x, y;
    int width, height;
    int count;			/* if nonzero, at least this many more */
} GLXPbufferClobberEvent;

typedef union __GLXEvent {
    GLXPbufferClobberEvent glxpbufferclobber;
    long pad[24];
} GLXEvent;

#ifdef __cplusplus
}
#endif

#endif /* !__GLX_glx_h__ */
