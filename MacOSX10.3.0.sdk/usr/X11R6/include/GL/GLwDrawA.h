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
**
*/

/*
** This file has been slightly modified from the original by Carlos A. M. dos
** Santos <casantos@cpmet.ufpel.tche.br> for integration into XFree86 source
** tree and for generating both Motif(TM) 1.2 and 2.x versions of the widgets
** in the same library.
*/
/* $XFree86: xc/extras/ogl-sample/main/gfx/lib/glw/GLwDrawA.h,v 1.4 2002/05/31 16:36:50 dawes Exp $ */

#ifndef _GLwDrawA_h
#define _GLwDrawA_h

#ifdef __GLX_MOTIF
# ifndef __GLX_INCLUDE_XM_H	/* Defined during library compilation */
#  include <Xm/Xm.h>		/* We need to know about XmVERSION early */
# endif
#endif

#include <GL/glx.h>
#include <GL/gl.h>

/****************************************************************
 *
 * GLwDrawingArea widgets
 *
 ****************************************************************/

/* Resources:

 Name		     Class		RepType		Default Value
 ----		     -----		-------		-------------
 attribList	     AttribList		int *		NULL
 visualInfo	     VisualInfo		VisualInfo	NULL
 installColormap     InstallColormap	Boolean		TRUE
 allocateBackground  AllocateColors	Boolean		FALSE
 allocateOtherColors AllocateColors	Boolean		FALSE
 installBackground   InstallBackground	Boolean		TRUE
 exposeCallback      Callback		Pointer		NULL
 ginitCallback       Callback		Pointer		NULL
 inputCallback       Callback		Pointer		NULL
 resizeCallback      Callback		Pointer		NULL

*** The following resources all correspond to the GLX configuration
*** attributes and are used to create the attribList if it is NULL
 bufferSize	     BufferSize		int		0
 level		     Level		int		0
 rgba		     Rgba		Boolean		FALSE
 doublebuffer	     Doublebuffer	Boolean		FALSE
 stereo		     Stereo		Boolean		FALSE
 auxBuffers	     AuxBuffers		int		0
 redSize	     ColorSize		int		1
 greenSize	     ColorSize		int		1
 blueSize	     ColorSize		int		1
 alphaSize	     AlphaSize		int		0
 depthSize	     DepthSize		int		0
 stencilSize	     StencilSize	int		0
 accumRedSize	     AccumColorSize	int		0
 accumGreenSize	     AccumColorSize	int		0
 accumBlueSize	     AccumColorSize	int		0
 accumAlphaSize	     AccumAlphaSize	int		0
*/

#define GLwNattribList		"attribList"
#define GLwCAttribList		"AttribList"
#define GLwNvisualInfo		"visualInfo"
#define GLwCVisualInfo		"VisualInfo"
#define GLwRVisualInfo		"VisualInfo"

#define GLwNinstallColormap	"installColormap"
#define GLwCInstallColormap	"InstallColormap"
#define GLwNallocateBackground	"allocateBackground"
#define GLwNallocateOtherColors	"allocateOtherColors"
#define GLwCAllocateColors	"AllocateColors"
#define GLwNinstallBackground	"installBackground"
#define GLwCInstallBackground	"InstallBackground"

#define GLwCCallback		"Callback"
#define GLwNexposeCallback	"exposeCallback"
#define GLwNginitCallback	"ginitCallback"
#define GLwNresizeCallback	"resizeCallback"
#define GLwNinputCallback	"inputCallback"

#define GLwNbufferSize		"bufferSize"
#define GLwCBufferSize		"BufferSize"
#define GLwNlevel		"level"
#define GLwCLevel		"Level"
#define GLwNrgba		"rgba"
#define GLwCRgba		"Rgba"
#define GLwNdoublebuffer	"doublebuffer"
#define GLwCDoublebuffer	"Doublebuffer"
#define GLwNstereo		"stereo"
#define GLwCStereo		"Stereo"
#define GLwNauxBuffers		"auxBuffers"
#define GLwCAuxBuffers		"AuxBuffers"
#define GLwNredSize		"redSize"
#define GLwNgreenSize		"greenSize"
#define GLwNblueSize		"blueSize"
#define GLwCColorSize		"ColorSize"
#define GLwNalphaSize		"alphaSize"
#define GLwCAlphaSize		"AlphaSize"
#define GLwNdepthSize		"depthSize"
#define GLwCDepthSize		"DepthSize"
#define GLwNstencilSize		"stencilSize"
#define GLwCStencilSize		"StencilSize"
#define GLwNaccumRedSize	"accumRedSize"
#define GLwNaccumGreenSize	"accumGreenSize"
#define GLwNaccumBlueSize	"accumBlueSize"
#define GLwCAccumColorSize	"AccumColorSize"
#define GLwNaccumAlphaSize	"accumAlphaSize"
#define GLwCAccumAlphaSize	"AccumAlphaSize"

#ifdef __GLX_MOTIF

#if XmVERSION == 1
/*
#  define _GLwMDrawingAreaClassRec	_GLwM1DrawingAreaClassRec
#  define _GLwMDrawingAreaRec		_GLwM1DrawingAreaRec
*/
#  define glwMDrawingAreaWidgetClass	glwM1DrawingAreaWidgetClass
#  define glwMDrawingAreaClassRec	glwM1DrawingAreaClassRec
#  define GLwCreateMDrawingArea		GLwCreateM1DrawingArea
#elif XmVERSION == 2
/*
#  define _GLwMDrawingAreaClassRec	_GLwM2DrawingAreaClassRec
#  define _GLwMDrawingAreaRec		_GLwM2DrawingAreaRec
*/
#  define glwMDrawingAreaWidgetClass	glwM2DrawingAreaWidgetClass
#  define glwMDrawingAreaClassRec	glwM2DrawingAreaClassRec
#  define GLwCreateMDrawingArea		GLwCreateM2DrawingArea
#else
#error "Sorry, unknown Motif version."
#endif /* XmVERSION */

typedef struct _GLwMDrawingAreaClassRec	*GLwMDrawingAreaWidgetClass;
typedef struct _GLwMDrawingAreaRec	*GLwMDrawingAreaWidget;

extern WidgetClass glwMDrawingAreaWidgetClass;

#else /* not __GLX_MOTIF */

typedef struct _GLwDrawingAreaClassRec	*GLwDrawingAreaWidgetClass;
typedef struct _GLwDrawingAreaRec	*GLwDrawingAreaWidget;

extern WidgetClass glwDrawingAreaWidgetClass;

#endif /* __GLX_MOTIF */

/* Callback reasons */
#ifdef __GLX_MOTIF
#define GLwCR_EXPOSE	XmCR_EXPOSE
#define GLwCR_RESIZE	XmCR_RESIZE
#define GLwCR_INPUT	XmCR_INPUT
#else /* not __GLX_MOTIF */
/* The same values as Motif, but don't use Motif constants */
#define GLwCR_EXPOSE	38
#define GLwCR_RESIZE	39
#define GLwCR_INPUT	40
#endif /* __GLX_MOTIF */

#define GLwCR_GINIT	32135	/* Arbitrary number that should neverr clash*/

typedef struct
{
    int     reason;
    XEvent  *event;
    Dimension width, height;		/* for resize callback */
} GLwDrawingAreaCallbackStruct;

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/* front ends to glXMakeCurrent and glXSwapBuffers */
extern void GLwDrawingAreaMakeCurrent (Widget w, GLXContext ctx);
extern void GLwDrawingAreaSwapBuffers (Widget w);

#ifdef __GLX_MOTIF
#ifdef _NO_PROTO
extern Widget GLwCreateMDrawingArea ();
#else /* _NO_PROTO */

extern Widget GLwCreateMDrawingArea (Widget parent, char *name,
				     ArgList arglist, Cardinal argcount);
#endif /* _NO_PROTO */

#endif /* __GLX_MOTIF */

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* _GLwDrawA_h */
