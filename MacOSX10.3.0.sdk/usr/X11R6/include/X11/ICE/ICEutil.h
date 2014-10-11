/* $Xorg: ICEutil.h,v 1.5 2001/02/09 02:03:26 xorgcvs Exp $ */
/******************************************************************************


Copyright 1993, 1998  The Open Group

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

Author: Ralph Mor, X Consortium
******************************************************************************/
/* $XFree86: xc/lib/ICE/ICEutil.h,v 1.4 2001/12/20 19:40:59 tsi Exp $ */

#ifndef _ICEUTIL_H_
#define _ICEUTIL_H_

#include <X11/Xfuncproto.h>

#include <stdio.h>
#include <X11/Xlib.h>

_XFUNCPROTOBEGIN

/*
 * Data structure for entry in ICE authority file
 */

typedef struct {
    char    	    *protocol_name;
    unsigned short  protocol_data_length;
    char   	    *protocol_data;
    char    	    *network_id;
    char    	    *auth_name;
    unsigned short  auth_data_length;
    char   	    *auth_data;
} IceAuthFileEntry;


/*
 * Authentication data maintained in memory.
 */

typedef struct {
    char    	    *protocol_name;
    char	    *network_id;
    char    	    *auth_name;
    unsigned short  auth_data_length;
    char   	    *auth_data;
} IceAuthDataEntry;


/*
 * Return values from IceLockAuthFile
 */

#define IceAuthLockSuccess	0   /* lock succeeded */
#define IceAuthLockError	1   /* lock unexpectely failed, check errno */
#define IceAuthLockTimeout	2   /* lock failed, timeouts expired */


/*
 * Function Prototypes
 */

extern char *IceAuthFileName (
#if NeedFunctionPrototypes
    void
#endif
);

extern int IceLockAuthFile (
#if NeedFunctionPrototypes
    char *		/* file_name */,
    int			/* retries */,
    int			/* timeout */,
    long		/* dead */
#endif
);

extern void IceUnlockAuthFile (
#if NeedFunctionPrototypes
    char *		/* file_name */
#endif
);

extern IceAuthFileEntry *IceReadAuthFileEntry (
#if NeedFunctionPrototypes
    FILE *		/* auth_file */
#endif
);

extern void IceFreeAuthFileEntry (
#if NeedFunctionPrototypes
    IceAuthFileEntry *	/* auth */
#endif
);

extern Status IceWriteAuthFileEntry (
#if NeedFunctionPrototypes
    FILE *		/* auth_file */,
    IceAuthFileEntry *	/* auth */
#endif
);

extern IceAuthFileEntry *IceGetAuthFileEntry (
#if NeedFunctionPrototypes
    char *		/* protocol_name */,
    char *		/* network_id */,
    char *		/* auth_name */
#endif
);

extern char *IceGenerateMagicCookie (
#if NeedFunctionPrototypes
    int			/* len */
#endif
);

extern void IceSetPaAuthData (
#if NeedFunctionPrototypes
    int			/* numEntries */,
    IceAuthDataEntry *	/* entries */
#endif
);

_XFUNCPROTOEND

#endif /* _ICEUTIL_H_ */
