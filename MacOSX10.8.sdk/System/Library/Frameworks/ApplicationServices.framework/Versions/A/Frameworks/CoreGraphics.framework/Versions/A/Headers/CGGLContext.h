/* CoreGraphics - CGGLContext.h
 * Copyright (c) 2003-2008 Apple Inc.
 * All rights reserved. */

#ifndef CGGLCONTEXT_H_
#define CGGLCONTEXT_H_

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGContext.h>

/* NOTE: The functions declared in this file do not work as expected in Mac
   OS X 10.5 or later. Do not use them. */

/* Create a context from the OpenGL context `glContext'. `size' specifies
   the dimensions of the OpenGL viewport rectangle which the CGContext will
   establish by calling glViewport(3G). If non-NULL, `colorspace' should be
   an RGB profile which specifies the destination space when rendering
   device-independent colors.

   This function does not work as expected in Mac OS X 10.5 or later. Do not
   use it. */

CG_EXTERN CGContextRef CGGLContextCreate(void *glContext, CGSize size,
    CGColorSpaceRef colorspace) CG_AVAILABLE_BUT_DEPRECATED(__MAC_10_3,
	__MAC_10_6, __IPHONE_NA, __IPHONE_NA);

/* Update the OpenGL viewport associated with the OpenGL context `c' to a
   new size. `size' specifies the dimensions of a new OpenGL viewport
   rectangle which the CGContext will establish by calling glViewport(3G).
   This function should be called whenever the size of the OpenGL context
   changes.

   This function does not work expected in Mac OS X 10.5 or later. Do not
   use it. */

CG_EXTERN void CGGLContextUpdateViewportSize(CGContextRef c, CGSize size)
    CG_AVAILABLE_BUT_DEPRECATED(__MAC_10_3, __MAC_10_6, __IPHONE_NA,
	__IPHONE_NA);

#endif	/* CGGLCONTEXT_H_ */
