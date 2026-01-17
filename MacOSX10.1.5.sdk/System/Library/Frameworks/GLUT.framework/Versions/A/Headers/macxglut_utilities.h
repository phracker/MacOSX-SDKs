
/* Copyright (c) Dietmar Planitzer, 1998 */

/* This program is freely distributable without licensing fees 
   and is provided without guarantee or warrantee expressed or 
   implied. This program is -not- in the public domain. */


#include <sys/time.h>

#ifndef APIENTRY
#define APIENTRY
#endif



/* *** function prototypes *** */

unsigned int __glutDisplayModeFromString(const char *string);
void		__glutInitTime(struct timeval *beginning);
char *	__glutStrdup(const char *string);
void		__glutWarning(char *format,...);
void		__glutFatalError(char *format,...);
void		__glutFatalUsage(char *format,...);
