/*
    File:	AGL/aglContext.h

    Contains:	Data type for internal contexts, for use with internal renderer interface.

    Version:	Technology:	Mac OS 9
                Release:	GM
 
     Copyright:  (c) 2000 - 2003 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef _AGLCONTEXT_H
#define _AGLCONTEXT_H

#include <OpenGL/gliContext.h>
#include <OpenGL/gliDispatch.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
** Opaque declaration for private AGLContext data.
*/
typedef struct __AGLPrivateRec *AGLPrivate;

/*
** AGLContext structure.
*/
struct __AGLContextRec {
	GLIContext           rend;
	GLIFunctionDispatch  disp;
	AGLPrivate           priv;
};


#ifdef __cplusplus
}
#endif

#endif /* _AGLCONTEXT_H */
