/*
	Copyright:	(c) 1999-2012 Apple Inc. All rights reserved.
*/

#ifndef _CGLCURRENT_H
#define _CGLCURRENT_H

#include <OpenGL/CGLTypes.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
** Current context functions
*/
extern CGLError CGLSetCurrentContext(CGLContextObj ctx);
extern CGLContextObj CGLGetCurrentContext(void);


#ifdef __cplusplus
}
#endif

#endif /* _CGLCURRENT_H */

