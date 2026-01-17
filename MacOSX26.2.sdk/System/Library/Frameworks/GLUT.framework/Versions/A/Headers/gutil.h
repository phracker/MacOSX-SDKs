
/*
 * gutil.h
 *
 * FUNCTION:
 * Provide utilities that allow rotation to occur 
 * around any axis.
 * 
 * HISTORY:
 * created by Linas Vepstas  1990
 * added single & double precision, June 1991, Linas Vepstas
 */

#ifndef __GUTIL_H__
#define __GUTIL_H__

#include <OpenGL/OpenGLAvailability.h>

#ifdef __GUTIL_DOUBLE
#define gutDouble double
#else
#define gutDouble float  
#endif


#ifdef _NO_PROTO		/* NO ANSI C PROTOTYPING */

/* Rotation Utilities */
extern void rot_axis_f () OPENGL_DEPRECATED(10_0, 10_9);
extern void rot_about_axis_f () OPENGL_DEPRECATED(10_0, 10_9);
extern void rot_omega_f () OPENGL_DEPRECATED(10_0, 10_9);
extern void urot_axis_f () OPENGL_DEPRECATED(10_0, 10_9);
extern void urot_about_axis_f () OPENGL_DEPRECATED(10_0, 10_9);
extern void urot_omega_f () OPENGL_DEPRECATED(10_0, 10_9);

/* double-precision versions */
extern void rot_axis_d () OPENGL_DEPRECATED(10_0, 10_9);
extern void rot_about_axis_d () OPENGL_DEPRECATED(10_0, 10_9);
extern void rot_omega_d () OPENGL_DEPRECATED(10_0, 10_9);
extern void urot_axis_d () OPENGL_DEPRECATED(10_0, 10_9);
extern void urot_about_axis_d () OPENGL_DEPRECATED(10_0, 10_9);
extern void urot_omega_d () OPENGL_DEPRECATED(10_0, 10_9);

/* viewpoint functions */
extern void uview_direction_d () OPENGL_DEPRECATED(10_0, 10_9);
extern void uview_direction_f () OPENGL_DEPRECATED(10_0, 10_9);
extern void uviewpoint_d () OPENGL_DEPRECATED(10_0, 10_9);
extern void uviewpoint_f () OPENGL_DEPRECATED(10_0, 10_9);

#else /* _NO_PROTO */		/* ANSI C PROTOTYPING */

/* Rotation Utilities */
extern void rot_axis_f (float omega, float axis[3]) OPENGL_DEPRECATED(10_0, 10_9);
extern void rot_about_axis_f (float angle, float axis[3]) OPENGL_DEPRECATED(10_0, 10_9);
extern void rot_omega_f (float axis[3]) OPENGL_DEPRECATED(10_0, 10_9);
extern void urot_axis_f (float m[4][4], float omega, float axis[3]) OPENGL_DEPRECATED(10_0, 10_9);
extern void urot_about_axis_f (float m[4][4], float angle, float axis[3]) OPENGL_DEPRECATED(10_0, 10_9);
extern void urot_omega_f (float m[4][4], float axis[3]) OPENGL_DEPRECATED(10_0, 10_9);

/* double-precision versions */
extern void rot_axis_d (double omega, double axis[3]) OPENGL_DEPRECATED(10_0, 10_9);
extern void rot_about_axis_d (double angle, double axis[3]) OPENGL_DEPRECATED(10_0, 10_9);
extern void rot_omega_d (double axis[3]) OPENGL_DEPRECATED(10_0, 10_9);
extern void urot_axis_d (double m[4][4], double omega, double axis[3]) OPENGL_DEPRECATED(10_0, 10_9);
extern void urot_about_axis_d (double m[4][4], double angle, double axis[3]) OPENGL_DEPRECATED(10_0, 10_9);
extern void urot_omega_d (double m[4][4], double axis[3]) OPENGL_DEPRECATED(10_0, 10_9);

/* viewpoint functions */
extern void uview_direction_d (double m[4][4],		/* returned */
                        double v21[3],		/* input */
                        double up[3]) OPENGL_DEPRECATED(10_0, 10_9);		/* input */

extern void uview_direction_f (float m[4][4],		/* returned */
                        float v21[3],		/* input */
                        float up[3]) OPENGL_DEPRECATED(10_0, 10_9);		/* input */

extern void uviewpoint_d (double m[4][4],		/* returned */
                   double v1[3],		/* input */
                   double v2[3],		/* input */
                   double up[3]) OPENGL_DEPRECATED(10_0, 10_9);		/* input */

extern void uviewpoint_f (float m[4][4],		/* returned */
                   float v1[3],		/* input */
                   float v2[3],		/* input */
                   float up[3]) OPENGL_DEPRECATED(10_0, 10_9);		/* input */

#endif /* _NO_PROTO */

#endif /* _GUTIL_H__ */

/* ------------------- end of file ---------------------- */
