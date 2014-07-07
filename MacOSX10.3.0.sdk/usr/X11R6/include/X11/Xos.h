/*
 * $Xorg: Xos.h,v 1.6 2001/02/09 02:03:22 xorgcvs Exp $
 * 
 * 
Copyright 1987, 1998  The Open Group

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
 * The X Window System is a Trademark of The Open Group.
 *
 */
/* $XFree86: xc/include/Xos.h,v 3.38 2002/05/31 18:45:39 dawes Exp $ */

/* This is a collection of things to try and minimize system dependencies
 * in a "signficant" number of source files.
 */

#ifndef _XOS_H_
#define _XOS_H_

#include <X11/Xosdefs.h>

/*
 * Get major data types (esp. caddr_t)
 */

#ifdef USG
#ifndef __TYPES__
#ifdef CRAY
#define word word_t
#endif /* CRAY */
#include <sys/types.h>			/* forgot to protect it... */
#define __TYPES__
#endif /* __TYPES__ */
#else /* USG */
#if defined(_POSIX_SOURCE) && defined(MOTOROLA)
#undef _POSIX_SOURCE
#include <sys/types.h>
#define _POSIX_SOURCE
#else
#include <sys/types.h>
#endif
#endif /* USG */

#ifdef _SEQUENT_
/*
 * in_systm.h compatibility between SysV and BSD types u_char u_short u_long
 * select.h  for typedef of args to select, fd_set, may use SVR4 later
 */
#include <netinet/in_systm.h>
#include <sys/select.h>
#endif /* _SEQUENT_ */

/*
 * Just about everyone needs the strings routines.  We provide both forms here,
 * index/rindex and strchr/strrchr, so any systems that don't provide them all
 * need to have #defines here.
 *
 * These macros are defined this way, rather than, e.g.:
 *    #defined index(s,c) strchr(s,c)
 * because someone might be using them as function pointers, and such
 * a change would break compatibility for anyone who's relying on them
 * being the way they currently are. So we're stuck with them this way,
 * which can be really inconvenient. :-(
 */

#ifndef X_NOT_STDC_ENV

#include <string.h>
#ifdef __STDC__
#ifndef index
#define index(s,c) (strchr((s),(c)))
#endif
#ifndef rindex
#define rindex(s,c) (strrchr((s),(c)))
#endif
#else
#ifndef index
#define index strchr
#endif
#ifndef rindex
#define rindex strrchr
#endif
#endif

#else

#ifdef SYSV
#if defined(clipper) || defined(__clipper__)
#include <malloc.h>
#endif
#include <string.h>
#define index strchr
#define rindex strrchr
#else
#include <strings.h>
#define strchr index
#define strrchr rindex
#endif

#endif /* X_NOT_STDC_ENV */

/*
 * strerror()
 */
#if (defined(X_NOT_STDC_ENV) || (defined(sun) && !defined(SVR4)) || defined(macII)) && !defined(__GLIBC__)
#ifndef strerror
extern char *sys_errlist[];
extern int sys_nerr;
#define strerror(n) \
    (((n) >= 0 && (n) < sys_nerr) ? sys_errlist[n] : "unknown error")
#endif
#endif

/*
 * Get open(2) constants
 */
#if defined(X_NOT_POSIX)
#include <fcntl.h>
#if defined(USL) || defined(CRAY) || defined(MOTOROLA) || (defined(i386) && (defined(SYSV) || defined(SVR4))) || defined(__sxg__)
#include <unistd.h>
#endif
#ifdef WIN32
#include <X11/Xw32defs.h>
#else
#include <sys/file.h>
#endif
#else /* X_NOT_POSIX */
#if !defined(_POSIX_SOURCE) && defined(macII)
#define _POSIX_SOURCE
#include <fcntl.h>
#include <unistd.h>
#undef _POSIX_SOURCE
#else
#include <fcntl.h>
#include <unistd.h>
#endif
#endif /* X_NOT_POSIX else */

/*
 * Get struct timeval and struct tm
 */

#if defined(SYSV) && !defined(_SEQUENT_)

#ifndef USL
#include <sys/time.h>
#endif
#include <time.h>
#ifdef CRAY
#undef word
#endif /* CRAY */
#if defined(USG) && !defined(CRAY) && !defined(MOTOROLA) && !defined(uniosu) && !defined(__sxg__) && !defined(clipper) && !defined(__clipper__)
struct timeval {
    long tv_sec;
    long tv_usec;
};
#ifndef USL_SHARELIB
struct timezone {
    int tz_minuteswest;
    int tz_dsttime;
};
#endif /* USL_SHARELIB */
#endif /* USG */

#ifdef _SEQUENT_
struct timezone {
    int tz_minuteswest;
    int tz_dsttime;
};
#endif /* _SEQUENT_ */

#else /* not SYSV */

#if defined(_POSIX_SOURCE) && defined(SVR4)
/* need to omit _POSIX_SOURCE in order to get what we want in SVR4 */
#undef _POSIX_SOURCE
#include <sys/time.h>
#define _POSIX_SOURCE
#elif defined(WIN32)
#include <time.h>
#if !defined(_WINSOCKAPI_) && !defined(_WILLWINSOCK_)
struct timeval {
    long    tv_sec;         /* seconds */
    long    tv_usec;        /* and microseconds */
};
#endif
#include <sys/timeb.h>
#define gettimeofday(t) \
{ \
    struct _timeb _gtodtmp; \
    _ftime (&_gtodtmp); \
    (t)->tv_sec = _gtodtmp.time; \
    (t)->tv_usec = _gtodtmp.millitm * 1000; \
}
#elif defined(_SEQUENT_) || defined(Lynx)
#include <time.h>
#elif defined (__QNX__)
typedef unsigned long fd_mask;
/* Make sure we get 256 bit select masks */
#define FD_SETSIZE 256
#include <sys/select.h>
#include <sys/time.h>
#include <time.h>
#else
#include <sys/time.h>
#include <time.h>
#endif /* defined(_POSIX_SOURCE) && defined(SVR4) */

#endif /* SYSV */

/* define X_GETTIMEOFDAY macro, a portable gettimeofday() */
#if defined(_XOPEN_XPG4) || defined(_XOPEN_UNIX) /* _XOPEN_UNIX is XPG4.2 */
#define X_GETTIMEOFDAY(t) gettimeofday(t, (struct timezone*)0)
#else
#if defined(SVR4) || defined(VMS) || defined(WIN32)
#define X_GETTIMEOFDAY(t) gettimeofday(t)
#else
#define X_GETTIMEOFDAY(t) gettimeofday(t, (struct timezone*)0)
#endif
#endif /* XPG4 else */

#ifdef __UNIXOS2__
typedef unsigned long fd_mask;
#include <limits.h>
#define MAX_PATH _POSIX_PATH_MAX
#endif

#ifdef __GNU__
#define PATH_MAX 4096
#define MAXPATHLEN 4096
#define OPEN_MAX 256 /* We define a reasonable limit.  */
#endif

/* use POSIX name for signal */
#if defined(X_NOT_POSIX) && defined(SYSV) && !defined(SIGCHLD) && !defined(ISC)
#define SIGCHLD SIGCLD
#endif

#ifdef ISC
#include <sys/bsdtypes.h>
#include <sys/limits.h>
#define NGROUPS 16
#endif

#if defined(ISC) || \
    (defined(linux) && !defined(__GLIBC__)) || \
    (defined(__QNX__) && !defined(UNIXCONN))
/*
 *	Some OS's may not have this
 */

#define X_NO_SYS_UN 1

struct sockaddr_un {
	short	sun_family;
	char	sun_path[108];
};
#endif

#include <X11/Xarch.h>

#endif /* _XOS_H_ */
