#ifndef __glutbitmap_h__
#define __glutbitmap_h__

/* Copyright (c) Mark J. Kilgard, 1994. */

/* This program is freely distributable without licensing fees 
   and is provided without guarantee or warrantee expressed or 
   implied. This program is -not- in the public domain. */

#include "glut.h"

typedef struct {
  const GLsizei width;
  const GLsizei height;
  const GLfloat xorig;
  const GLfloat yorig;
  const GLfloat advance;
  const GLubyte *bitmap;
} BitmapCharRec OPENGL_DEPRECATED(10_0, 10_9), *BitmapCharPtr OPENGL_DEPRECATED(10_0, 10_9);

typedef struct {
  const char *name;
  const int num_chars;
  const int first;
  const BitmapCharRec * const *ch;
} BitmapFontRec OPENGL_DEPRECATED(10_0, 10_9), *BitmapFontPtr OPENGL_DEPRECATED(10_0, 10_9);

typedef void *GLUTbitmapFont OPENGL_DEPRECATED(10_0, 10_9);

#endif /* __glutbitmap_h__ */
