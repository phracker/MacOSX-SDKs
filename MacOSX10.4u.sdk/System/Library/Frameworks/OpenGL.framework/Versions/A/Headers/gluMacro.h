/*
	Copyright:	(c) 1999 by Apple Computer, Inc., all rights reserved.
*/

#ifndef _GLUMACRO_H
#define _GLUMACRO_H

#include <OpenGL/CGLMacro.h>
#include <OpenGL/gluContext.h>

/********************* GLU Macros *********************/

#define gluBuild1DMipmaps(target, internalFormat, width, format, type, data) \
	gluBuild1DMipmapsCTX(cgl_ctx, target, internalFormat, width, format, type, data)

#define gluBuild2DMipmaps(target, internalFormat, width, height, format, type, data) \
	gluBuild2DMipmapsCTX(cgl_ctx, target, internalFormat, width, height, format, type, data)

#define gluBuild3DMipmaps(target, internalFormat, width, height, depth, format, type, data) \
	gluBuild3DMipmapsCTX(cgl_ctx, target, internalFormat, width, height, depth, format, type, data)

#define gluBuild1DMipmapLevels(target, internalFormat, width, format, type, level, base, max, data) \
	gluBuild1DMipmapLevelsCTX(cgl_ctx, target, internalFormat, width, format, type, level, base, max, data)

#define gluBuild2DMipmapLevels(target, internalFormat, width, height, format, type, level, base, max, data) \
	gluBuild2DMipmapLevelsCTX(cgl_ctx, target, internalFormat, width, height, format, type, level, base, max, data)

#define gluBuild3DMipmapLevels(target, internalFormat, width, height, depth, format, type, level, base, max, data) \
	gluBuild3DMipmapLevelsCTX(cgl_ctx, target, internalFormat, width, height, depth, format, type, level, base, max, data)

#define gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ) \
	gluLookAtCTX(cgl_ctx, eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ)

#define gluNewNurbsRenderer() \
	gluNewNurbsRendererCTX(cgl_ctx)

#define gluNewQuadric() \
	gluNewQuadricCTX(cgl_ctx)

#define gluOrtho2D(left, right, bottom, top) \
	gluOrtho2DCTX(cgl_ctx, left, right, bottom, top)

#define gluPerspective(fovy, aspect, znear, zfar) \
	gluPerspectiveCTX(cgl_ctx, fovy, aspect, znear, zfar)

#define gluPickMatrix(x, y, delx, dely, viewport) \
	gluPickMatrixCTX(cgl_ctx, x, y, delx, dely, viewport)

#define gluScaleImage(format, wIn, hIn, typeIn, dataIn, wOut, hOut, typeOut, dataOut) \
	gluScaleImageCTX(cgl_ctx, format, wIn, hIn, typeIn, dataIn, wOut, hOut, typeOut, dataOut)


#endif /* _GLUMACRO_H */


