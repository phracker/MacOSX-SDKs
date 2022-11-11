/*
	Copyright:	(c) 1999-2012 Apple Inc. All rights reserved.
*/

#ifndef _CGLCURRENT_H
#define _CGLCURRENT_H

#include <OpenGL/CGLTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

OPENGL_ASSUME_NONNULL_BEGIN

/*
** Current context functions
*/
extern CGLError CGLSetCurrentContext(CGLContextObj OPENGL_NULLABLE ctx);
extern CGLContextObj OPENGL_NULLABLE CGLGetCurrentContext(void);

OPENGL_ASSUME_NONNULL_END

#ifdef __cplusplus
}
#endif

#endif /* _CGLCURRENT_H */

