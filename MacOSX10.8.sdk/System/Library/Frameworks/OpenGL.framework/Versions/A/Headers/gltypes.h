/*
	Copyright:	(c) 2010-2012 Apple Inc. All rights reserved.
*/

#ifndef __gltypes_h_
#define __gltypes_h_

#ifndef GLEXT_64_TYPES_DEFINED
/* This code block is duplicated in glxext.h, so must be protected */
#define GLEXT_64_TYPES_DEFINED
/* Define int32_t, int64_t, and uint64_t types for UST/MSC */
/* (as used in the GL_EXT_timer_query extension). */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#include <inttypes.h>
#elif defined(__sun__) || defined(__digital__)
#include <inttypes.h>
#if defined(__STDC__)
#if defined(__arch64__) || defined(_LP64)
typedef long int int64_t;
typedef unsigned long int uint64_t;
#else
typedef long long int int64_t;
typedef unsigned long long int uint64_t;
#endif /* __arch64__ */
#endif /* __STDC__ */
#elif defined( __VMS ) || defined(__sgi)
#include <inttypes.h>
#elif defined(__SCO__) || defined(__USLC__)
#include <stdint.h>
#elif defined(__UNIXOS2__) || defined(__SOL64__)
typedef long int int32_t;
typedef long long int int64_t;
typedef unsigned long long int uint64_t;
#elif defined(_WIN32) && defined(__GNUC__)
#include <stdint.h>
#elif defined(_WIN32)
typedef __int32 int32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
/* Fallback if nothing above works */
#include <inttypes.h>
#endif
#endif


#if !(defined __gl_h_ || defined __gl3_h_ || defined ES1_GL_H_GUARD || defined __gl_es20_h_)
typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef signed char GLbyte;
typedef short GLshort;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned int GLuint;
typedef float GLfloat;
typedef float GLclampf;
typedef void GLvoid;
#endif
#if !(defined __gl_h_ || defined __gl3_h_)
typedef double GLdouble;
typedef double GLclampd;
#endif

#ifndef __gl3_h_

#ifndef GL_VERSION_1_5
/* GL types for handling large vertex buffer objects */
typedef long GLintptr;
typedef long GLsizeiptr;
#endif

#ifndef GL_VERSION_2_0
/* GL type for program/shader text */
typedef char GLchar;
#endif

#if !(defined GL_ARB_half_float_vertex || defined GL_VERSION_3_0)
typedef unsigned short GLhalf;
#endif

#if !(defined GL_ARB_sync || defined GL_VERSION_3_0)
typedef int64_t GLint64;
typedef uint64_t GLuint64;
typedef struct __GLsync *GLsync;
#endif

#endif

#if !(defined GL_ARB_ES2_compatibility)
typedef int GLfixed;
#endif

#ifndef GL_ARB_half_float_pixel
typedef unsigned short GLhalfARB;
#endif

#ifndef GL_ARB_shader_objects
typedef char GLcharARB;
typedef void *GLhandleARB;
#endif

#ifndef GL_ARB_vertex_buffer_object
typedef long GLintptrARB;
typedef long GLsizeiptrARB;
#endif

#ifndef GL_EXT_timer_query
typedef int64_t GLint64EXT;
typedef uint64_t GLuint64EXT;
#endif


#endif //__gltypes_h_

