#ifndef __glutstroke_h__
#define __glutstroke_h__

#include <OpenGL/OpenGLAvailability.h>

/* Copyright (c) Mark J. Kilgard, 1994. */

/* This program is freely distributable without licensing fees 
   and is provided without guarantee or warrantee expressed or 
   implied. This program is -not- in the public domain. */

#if defined(_WIN32)
#pragma warning (disable:4244)  /* disable bogus conversion warnings */
#pragma warning (disable:4305)  /* VC++ 5.0 version of above warning. */
#endif

typedef struct {
  float x;
  float y;
} CoordRec OPENGL_DEPRECATED(10_0, 10_9), *CoordPtr OPENGL_DEPRECATED(10_0, 10_9);

typedef struct {
  int num_coords;
  const CoordRec *coord;
} StrokeRec OPENGL_DEPRECATED(10_0, 10_9), *StrokePtr OPENGL_DEPRECATED(10_0, 10_9);

typedef struct {
  int num_strokes;
  const StrokeRec *stroke;
  float center;
  float right;
} StrokeCharRec OPENGL_DEPRECATED(10_0, 10_9), *StrokeCharPtr OPENGL_DEPRECATED(10_0, 10_9);

typedef struct {
  const char *name;
  int num_chars;
  const StrokeCharRec *ch;
  float top;
  float bottom;
} StrokeFontRec OPENGL_DEPRECATED(10_0, 10_9), *StrokeFontPtr OPENGL_DEPRECATED(10_0, 10_9);

typedef void *GLUTstrokeFont OPENGL_DEPRECATED(10_0, 10_9);

#endif /* __glutstroke_h__ */
