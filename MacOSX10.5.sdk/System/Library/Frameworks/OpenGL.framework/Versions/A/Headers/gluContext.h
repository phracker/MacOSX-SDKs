/*
	Copyright:	(c) 1999 by Apple Computer, Inc., all rights reserved.
*/

#ifndef _GLUCONTEXT_H
#define _GLUCONTEXT_H

#include <OpenGL/glu.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
** GLU Context routines
*/
extern GLint gluBuild1DMipmapsCTX(      struct _CGLContextObject *ctx,
	GLenum target, GLint internalFormat, GLsizei width, GLenum format, GLenum type, const void *data);
extern GLint gluBuild2DMipmapsCTX(      struct _CGLContextObject *ctx,
	GLenum target, GLint internalFormat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *data);
extern GLint gluBuild3DMipmapsCTX(      struct _CGLContextObject *ctx,
	GLenum target, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *data);
extern GLint gluBuild1DMipmapLevelsCTX (      struct _CGLContextObject *ctx,
        GLenum target, GLint internalFormat, GLsizei width, GLenum format, GLenum type, GLint level, GLint base, GLint max, const void *data);
extern GLint gluBuild2DMipmapLevelsCTX (      struct _CGLContextObject *ctx,
        GLenum target, GLint internalFormat, GLsizei width, GLsizei height, GLenum format, GLenum type, GLint level, GLint base, GLint max, const void *data);
extern GLint gluBuild3DMipmapLevelsCTX (      struct _CGLContextObject *ctx,
        GLenum target, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLint level, GLint base, GLint max, const void *data);

extern void gluLookAtCTX(               struct _CGLContextObject *ctx, GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ,
	GLdouble centerX, GLdouble centerY, GLdouble centerZ, GLdouble upX, GLdouble upY, GLdouble upZ);
extern GLUnurbs* gluNewNurbsRendererCTX(struct _CGLContextObject *ctx);
extern GLUquadric* gluNewQuadricCTX(    struct _CGLContextObject *ctx);
extern GLUtesselator* gluNewTessCTX(    struct _CGLContextObject *ctx);
extern void gluOrtho2DCTX(              struct _CGLContextObject *ctx, GLdouble left, GLdouble right, GLdouble bottom, GLdouble top);
extern void gluPerspectiveCTX(          struct _CGLContextObject *ctx, GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);
extern void gluPickMatrixCTX(           struct _CGLContextObject *ctx, GLdouble x, GLdouble y, GLdouble delX, GLdouble delY, GLint *viewport);
extern GLint gluScaleImageCTX(          struct _CGLContextObject *ctx, GLenum format, GLsizei wIn, GLsizei hIn, GLenum typeIn, const void *dataIn,
	GLsizei wOut, GLsizei hOut, GLenum typeOut, void* dataOut);      


#ifdef __cplusplus
}
#endif

#endif /* _GLUCONTEXT_H */
