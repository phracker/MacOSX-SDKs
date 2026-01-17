/* $Xorg: Xpoll.h,v 1.4 2001/02/09 02:03:23 xorgcvs Exp $ */

/*

Copyright 1994, 1998  The Open Group

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall
not be used in advertising or otherwise to promote the sale, use or
other dealings in this Software without prior written authorization
from The Open Group.

*/
/* $XFree86: xc/include/Xpoll.h,v 3.9 2001/12/14 19:53:26 dawes Exp $ */

#ifndef _XPOLL_H_
#define _XPOLL_H_

#ifndef WIN32

#ifndef USE_POLL

#include <X11/Xos.h>
#if !defined(DGUX)
#if (defined(SVR4) || defined(CRAY) || defined(AIXV3)) && !defined(FD_SETSIZE)
#include <sys/select.h>
#ifdef luna
#include <sysent.h>
#endif
#endif
#else /* DGUX  -- No sys/select in Intel DG/ux */
#include <sys/time.h> 
#include <sys/types.h>
#include <unistd.h>
#endif

#ifdef __QNX__  /* Make sure we get 256 bit select masks */
#define FD_SETSIZE 256
#include <sys/select.h>
#endif

/* AIX 4.2 fubar-ed <sys/select.h>, so go to heroic measures to get it */
#if defined(AIXV4) && !defined(NFDBITS)
#include <sys/select.h>
#endif
#include <X11/Xmd.h>
#ifdef CSRG_BASED
#include <sys/param.h>
# if BSD < 199103
typedef long fd_mask;
# endif
#endif

#define XFD_SETSIZE	256
#ifndef FD_SETSIZE
#define FD_SETSIZE	XFD_SETSIZE
#endif

#ifndef NBBY
#define NBBY	8		/* number of bits in a byte */
#endif

#ifndef NFDBITS
#define NFDBITS (sizeof(fd_mask) * NBBY)	/* bits per mask */
#endif

#ifndef howmany
#define howmany(x,y)	(((x)+((y)-1))/(y))
#endif

#ifdef BSD
# if BSD < 198911	/* 198911 == OSF/1, 199103 == CSRG_BASED */
#  ifndef luna		/* and even though on LUNA BSD ==  43, it has it */
typedef struct fd_set {
	fd_mask fds_bits[howmany(FD_SETSIZE, NFDBITS)];
} fd_set;
#  endif
# endif
#endif

#ifndef hpux /* and perhaps old BSD ??? */
# define Select(n,r,w,e,t) select(n,(fd_set*)r,(fd_set*)w,(fd_set*)e,(struct timeval*)t)
#else
# ifndef _XPG4_EXTENDED /* HPUX 9.x and earlier */
#  define Select(n,r,w,e,t) select(n,(int*)r,(int*)w,(int*)e,(struct timeval*)t)
# else
#  define Select(n,r,w,e,t) select(n,(fd_set*)r,(fd_set*)w,(fd_set*)e,(struct timeval*)t)
# endif
#endif

#ifndef FD_SET
#define FD_SET(n, p)    ((p)->fds_bits[(n)/NFDBITS] |= ((fd_mask)1 << ((n) % NFDBITS)))
#endif
#ifndef FD_CLR
#define FD_CLR(n, p)    ((p)->fds_bits[(n)/NFDBITS] &= ~((fd_mask)1 << ((n) % NFDBITS)))
#endif
#ifndef FD_ISSET
#define FD_ISSET(n, p)  ((p)->fds_bits[(n)/NFDBITS] & ((fd_mask)1 << ((n) % NFDBITS)))
#endif
#ifndef FD_ZERO
#define FD_ZERO(p)      bzero((char *)(p), sizeof(*(p)))
#endif

/*
 * The following macros are used by the servers only. There is an
 * explicit assumption that the bit array in the fd_set is at least
 * 256 bits long (8 32-bit words). This is true on most modern POSIX 
 * systems. Note that this is merely an optimization for the servers
 * based on assumptions about the way that file descripters are
 * allocated on POSIX systems. 
 *
 * When porting X to new systems it is important to adjust these
 * macros if the system has fewer than 256 bits in the fd_set bit
 * array.
 */
#define XFD_ANYSET(p) \
		((p)->fds_bits[0] || (p)->fds_bits[1] || \
		(p)->fds_bits[2] || (p)->fds_bits[3] || \
		(p)->fds_bits[4] || (p)->fds_bits[5] || \
		(p)->fds_bits[6] || (p)->fds_bits[7])

#define XFD_COPYSET(src,dst) \
		(dst)->fds_bits[0] = (src)->fds_bits[0]; \
		(dst)->fds_bits[1] = (src)->fds_bits[1]; \
		(dst)->fds_bits[2] = (src)->fds_bits[2]; \
		(dst)->fds_bits[3] = (src)->fds_bits[3]; \
		(dst)->fds_bits[4] = (src)->fds_bits[4]; \
		(dst)->fds_bits[5] = (src)->fds_bits[5]; \
		(dst)->fds_bits[6] = (src)->fds_bits[6]; \
		(dst)->fds_bits[7] = (src)->fds_bits[7];

#define XFD_ANDSET(dst,b1,b2) \
		(dst)->fds_bits[0] = ((b1)->fds_bits[0] & (b2)->fds_bits[0]); \
		(dst)->fds_bits[1] = ((b1)->fds_bits[1] & (b2)->fds_bits[1]); \
		(dst)->fds_bits[2] = ((b1)->fds_bits[2] & (b2)->fds_bits[2]); \
		(dst)->fds_bits[3] = ((b1)->fds_bits[3] & (b2)->fds_bits[3]); \
		(dst)->fds_bits[4] = ((b1)->fds_bits[4] & (b2)->fds_bits[4]); \
		(dst)->fds_bits[5] = ((b1)->fds_bits[5] & (b2)->fds_bits[5]); \
		(dst)->fds_bits[6] = ((b1)->fds_bits[6] & (b2)->fds_bits[6]); \
		(dst)->fds_bits[7] = ((b1)->fds_bits[7] & (b2)->fds_bits[7]);

#define XFD_ORSET(dst,b1,b2) \
		(dst)->fds_bits[0] = ((b1)->fds_bits[0] | (b2)->fds_bits[0]); \
		(dst)->fds_bits[1] = ((b1)->fds_bits[1] | (b2)->fds_bits[1]); \
		(dst)->fds_bits[2] = ((b1)->fds_bits[2] | (b2)->fds_bits[2]); \
		(dst)->fds_bits[3] = ((b1)->fds_bits[3] | (b2)->fds_bits[3]); \
		(dst)->fds_bits[4] = ((b1)->fds_bits[4] | (b2)->fds_bits[4]); \
		(dst)->fds_bits[5] = ((b1)->fds_bits[5] | (b2)->fds_bits[5]); \
		(dst)->fds_bits[6] = ((b1)->fds_bits[6] | (b2)->fds_bits[6]); \
		(dst)->fds_bits[7] = ((b1)->fds_bits[7] | (b2)->fds_bits[7]);

#define XFD_UNSET(dst,b1) \
		(dst)->fds_bits[0] &= ~((b1)->fds_bits[0]); \
		(dst)->fds_bits[1] &= ~((b1)->fds_bits[1]); \
		(dst)->fds_bits[2] &= ~((b1)->fds_bits[2]); \
		(dst)->fds_bits[3] &= ~((b1)->fds_bits[3]); \
		(dst)->fds_bits[4] &= ~((b1)->fds_bits[4]); \
		(dst)->fds_bits[5] &= ~((b1)->fds_bits[5]); \
		(dst)->fds_bits[6] &= ~((b1)->fds_bits[6]); \
		(dst)->fds_bits[7] &= ~((b1)->fds_bits[7]);

#else /* USE_POLL */
#include <sys/poll.h>
#endif /* USE_POLL */

#else /* WIN32 */

#define XFD_SETSIZE	256
#ifndef FD_SETSIZE
#define FD_SETSIZE	XFD_SETSIZE
#endif
#include <X11/Xwinsock.h>

#define Select(n,r,w,e,t) select(0,(fd_set*)r,(fd_set*)w,(fd_set*)e,(struct timeval*)t)

#define XFD_SETCOUNT(p)	(((fd_set FAR *)(p))->fd_count)
#define XFD_FD(p,i) (((fd_set FAR *)(p))->fd_array[i])
#define XFD_ANYSET(p)	XFD_SETCOUNT(p)

#define XFD_COPYSET(src,dst) { \
    u_int __i; \
    FD_ZERO(dst); \
    for (__i = 0; __i < XFD_SETCOUNT(src) ; __i++) { \
        XFD_FD(dst,__i) = XFD_FD(src,__i); \
    } \
    XFD_SETCOUNT(dst) = XFD_SETCOUNT(src); \
}

#define XFD_ANDSET(dst,b1,b2) { \
    u_int __i; \
    FD_ZERO(dst); \
    for (__i = 0; __i < XFD_SETCOUNT(b1) ; __i++) { \
        if (FD_ISSET(XFD_FD(b1,__i), b2)) \
	   FD_SET(XFD_FD(b1,__i), dst); \
    } \
}

#define XFD_ORSET(dst,b1,b2) { \
    u_int __i; \
    XFD_COPYSET(b1,dst); \
    for (__i = 0; __i < XFD_SETCOUNT(b2) ; __i++) { \
        if (!FD_ISSET(XFD_FD(b2,__i), dst)) \
	   FD_SET(XFD_FD(b2,__i), dst); \
    } \
}

/* this one is really sub-optimal */
#define XFD_UNSET(dst,b1) { \
    u_int __i; \
    for (__i = 0; __i < XFD_SETCOUNT(b1) ; __i++) { \
	FD_CLR(XFD_FD(b1,__i), dst); \
    } \
}

/* we have to pay the price of having an array here, unlike with bitmasks
   calling twice FD_SET with the same fd is not transparent, so be careful */
#undef FD_SET
#define FD_SET(fd,set) do { \
    if (XFD_SETCOUNT(set) < FD_SETSIZE && !FD_ISSET(fd,set)) \
        XFD_FD(set,XFD_SETCOUNT(set)++)=(fd); \
} while(0)

#define getdtablesize() FD_SETSIZE 

#endif /* WIN32 */

#endif /* _XPOLL_H_ */
