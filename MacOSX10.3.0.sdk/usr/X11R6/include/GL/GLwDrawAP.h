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
/* $XFree86: xc/extras/ogl-sample/main/gfx/lib/glw/GLwDrawAP.h,v 1.3 2001/05/02 13:37:45 dawes Exp $ */

#ifndef _GLwDrawAP_h
#define _GLwDrawAP_h

#ifdef __GLX_MOTIF
# ifndef __GLX_INCLUDE_PRIMITIVE_P_H	/* Used during library compilation */
#  include <Xm/PrimitiveP.h>
# endif
# include <GL/GLwMDrawA.h>		/* includes IntrinsicP.h */
#else
# include <X11/IntrinsicP.h>
# include <GL/GLwDrawA.h>
#endif

typedef struct _GLwDrawingAreaClassPart
{
    char* extension;
} GLwDrawingAreaClassPart;

#ifdef __GLX_MOTIF
typedef struct _GLwMDrawingAreaClassRec {
    CoreClassPart		core_class;
    XmPrimitiveClassPart	primitive_class;
    GLwDrawingAreaClassPart	glwDrawingArea_class;
} GLwMDrawingAreaClassRec;

extern GLwMDrawingAreaClassRec glwMDrawingAreaClassRec;

#else /* not __GLX_MOTIF */

typedef struct _GLwDrawingAreaClassRec {
    CoreClassPart		core_class;
    GLwDrawingAreaClassPart	glwDrawingArea_class;
} GLwDrawingAreaClassRec;

extern GLwDrawingAreaClassRec glwDrawingAreaClassRec;
#endif /* __GLX_MOTIF */

typedef struct {
    /* resources */
    int *		attribList;
    XVisualInfo *	visualInfo;
    Boolean		myList;		/* TRUE if we malloced the attribList*/
    Boolean		myVisual;	/* TRUE if we created the visualInfo*/
    Boolean		installColormap;
    Boolean		allocateBackground;
    Boolean		allocateOtherColors;
    Boolean		installBackground;
    XtCallbackList	ginitCallback;
    XtCallbackList	resizeCallback;
    XtCallbackList	exposeCallback;
    XtCallbackList	inputCallback;
    /* specific attributes; add as we get new attributes */
    int			bufferSize;
    int			level;
    Boolean		rgba;
    Boolean		doublebuffer;
    Boolean		stereo;
    int			auxBuffers;
    int			redSize;
    int			greenSize;
    int			blueSize;
    int			alphaSize;
    int			depthSize;
    int			stencilSize;
    int			accumRedSize;
    int			accumGreenSize;
    int			accumBlueSize;
    int			accumAlphaSize;
} GLwDrawingAreaPart;

#ifdef __GLX_MOTIF
typedef struct _GLwMDrawingAreaRec {
    CorePart		core;
    XmPrimitivePart	primitive;
    GLwDrawingAreaPart	glwDrawingArea;
} GLwMDrawingAreaRec;
#else /* not __GLX_MOTIF */
typedef struct _GLwDrawingAreaRec {
    CorePart		core;
    GLwDrawingAreaPart	glwDrawingArea;
} GLwDrawingAreaRec;
#endif /* __GLX_MOTIF */

#endif /* _GLwDrawP_h */
