/* CoreGraphics - CGGLContext.h
 * Copyright (c) 2003-2007 Apple Inc.
 * All rights reserved.
 */

#ifndef CGGLCONTEXT_H_
#define CGGLCONTEXT_H_

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGContext.h>

/* NOTE: The functions declared in this file do not work as expected in
 * 10.5. Do not use them. */

CG_EXTERN_C_BEGIN

/* Create a context from the OpenGL context `glContext'. `size' specifies
 * the dimensions of the OpenGL viewport rectangle which the CGContext will
 * establish by calling glViewport(3G). If non-NULL, `colorspace' should be
 * an RGB profile which specifies the destination space when rendering
 * device-independent colors. */

/* This function does not work as expected in 10.5. Do not use it. */

CG_EXTERN CGContextRef CGGLContextCreate(void *glContext, CGSize size, CGColorSpaceRef colorspace) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Update the OpenGL viewport associated with the OpenGL context `c' to a
 * new size.  `size' specifies the dimensions of a new OpenGL viewport
 * rectangle which the CGContext will establish by calling glViewport(3G).
 * This function should be called whenever the size of the OpenGL context
 * changes. */

/* This function does not work  expected in 10.5. Do not use it. */

CG_EXTERN void CGGLContextUpdateViewportSize(CGContextRef c, CGSize size) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

CG_EXTERN_C_END

#endif	/* CGGLCONTEXT_H_ */
