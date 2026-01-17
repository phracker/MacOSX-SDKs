/* $XFree86: xc/lib/font/include/fontmod.h,v 1.2 1998/07/25 06:57:09 dawes Exp $ */

#ifndef _FONTMOD_H_
#define _FONTMOD_H_

typedef void (*InitFont)(void);

typedef struct {
    InitFont	initFunc;
    char *	name;
    pointer	module;
} FontModule;

extern FontModule *FontModuleList;

#endif /* _FONTMOD_H_ */
