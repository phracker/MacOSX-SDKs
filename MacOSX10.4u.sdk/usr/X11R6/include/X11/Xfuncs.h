/*
 * $Xorg: Xfuncs.h,v 1.4 2001/02/09 02:03:22 xorgcvs Exp $
 * 
 * 
Copyright 1990, 1998  The Open Group

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from The Open Group.
 *
 */
/* $XFree86: xc/include/Xfuncs.h,v 3.11 2003/12/19 02:05:37 dawes Exp $ */

#ifndef _XFUNCS_H_
#define _XFUNCS_H_

#include <X11/Xosdefs.h>

/* the old Xfuncs.h, for pre-R6 */
#if !(defined(XFree86LOADER) && defined(IN_MODULE))

#ifdef X_USEBFUNCS
void bcopy();
void bzero();
int bcmp();
#else
#if defined(SYSV) && !defined(SCO325)
#include <memory.h>
void bcopy();
#define bzero(b,len) memset(b, 0, len)
#define bcmp(b1,b2,len) memcmp(b1, b2, len)
#else
#include <string.h>
#ifdef SCO325
#include <strings.h>
#endif
#define _XFUNCS_H_INCLUDED_STRING_H
#define bcopy(b1,b2,len) memmove(b2, b1, (size_t)(len))
#define bzero(b,len) memset(b, 0, (size_t)(len))
#define bcmp(b1,b2,len) memcmp(b1, b2, (size_t)(len))
#endif
#endif /* X_USEBFUNCS */

/* the new Xfuncs.h */

#if !defined(X_NOT_STDC_ENV) && (!defined(sun) || defined(SVR4))
/* the ANSI C way */
#ifndef _XFUNCS_H_INCLUDED_STRING_H
#include <string.h>
#endif
#undef bzero
#define bzero(b,len) memset(b,0,len)
#else /* else X_NOT_STDC_ENV or SunOS 4 */
#if defined(SYSV) || defined(luna) || defined(sun) || defined(__sxg__)
#include <memory.h>
#define memmove(dst,src,len) bcopy((char *)(src),(char *)(dst),(int)(len))
#if defined(SYSV) && defined(_XBCOPYFUNC)
#undef memmove
#define memmove(dst,src,len) _XBCOPYFUNC((char *)(src),(char *)(dst),(int)(len))
#define _XNEEDBCOPYFUNC
#endif
#else /* else vanilla BSD */
#define memmove(dst,src,len) bcopy((char *)(src),(char *)(dst),(int)(len))
#define memcpy(dst,src,len) bcopy((char *)(src),(char *)(dst),(int)(len))
#define memcmp(b1,b2,len) bcmp((char *)(b1),(char *)(b2),(int)(len))
#endif /* SYSV else */
#endif /* ! X_NOT_STDC_ENV else */

#if defined(X_NOT_STDC_ENV) || (defined(sun) && !defined(SVR4))
#define atexit(f) on_exit(f, 0)
#endif

#endif /* !(defined(XFree86LOADER) && defined(IN_MODULE)) */

#endif /* _XFUNCS_H_ */
