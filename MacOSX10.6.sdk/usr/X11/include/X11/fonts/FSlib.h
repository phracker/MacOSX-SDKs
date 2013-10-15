/* $Xorg: FSlib.h,v 1.5 2001/02/09 02:03:25 xorgcvs Exp $ */

/*
 * Copyright 1990 Network Computing Devices;
 * Portions Copyright 1987 by Digital Equipment Corporation
 *
 * Permission to use, copy, modify, distribute, and sell this software 
 * and its documentation for any purpose is hereby granted without fee, 
 * provided that the above copyright notice appear in all copies and 
 * that both that copyright notice and this permission notice appear 
 * in supporting documentation, and that the names of Network Computing 
 * Devices or Digital not be used in advertising or publicity pertaining 
 * to distribution of the software without specific, written prior 
 * permission. Network Computing Devices or Digital make no representations 
 * about the suitability of this software for any purpose.  It is provided 
 * "as is" without express or implied warranty.
 *
 * NETWORK COMPUTING DEVICES AND  DIGITAL DISCLAIM ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL NETWORK COMPUTING DEVICES
 * OR DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES 
 * OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, 
 * WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, 
 * ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS 
 * SOFTWARE.
 */
/* $XFree86: xc/lib/FS/FSlib.h,v 1.6 2001/12/14 19:53:33 dawes Exp $ */

/*

Copyright 1987, 1994, 1998  The Open Group

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

*/

/*
 * Font server C interface library
 */

#ifndef _FSLIB_H_
#define _FSLIB_H_

#include	<X11/Xfuncproto.h>

#include	<X11/fonts/FS.h>
#include	<X11/fonts/FSproto.h>

#define	Bool	int
#define	Status	int
#define	True	1
#define	False	0

#define QueuedAlready 0
#define QueuedAfterReading 1
#define QueuedAfterFlush 2

#define	FSServerString(svr)	((svr)->server_name)
#define	FSVendorRelease(svr)	((svr)->release)
#define	FSProtocolVersion(svr)	((svr)->proto_version)
#define	FSServerVendor(svr)	((svr)->vendor)
#define	FSAuthorizationData(svr)	((svr)->auth_data)
#define	FSAlternateServers(svr)	((svr)->alternate_servers)
#define	FSNumAlternateServers(svr)	((svr)->num_alternates)
#define	FSQLength(svr)		((svr)->qlen)
#define	FSNextRequest(svr)	((svr)->request + 1)
#define FSLastKnownRequestProcessed(svr)   ((svr)->last_request_read)

#define	FSAllocID(svr)		((*(svr)->resource_alloc)((svr)))

typedef struct _alternate {
    Bool        subset;
    char       *name;
}           AlternateServer;

/* extension stuff */
typedef struct _FSExtData {
    int         number;		/* number returned by FSRegisterExtension */
    struct _FSExtData *next;	/* next item on list of data for structure */
    int         (*free_private) (char *); /* called to free private storage */
    char       *private_data;	/* data private to this extension. */
}           FSExtData;


typedef struct {		/* public to extension, cannot be changed */
    int         extension;	/* extension number */
    int         major_opcode;	/* major op-code assigned by server */
    int         first_event;	/* first event number for the extension */
    int         first_error;	/* first error number for the extension */
}           FSExtCodes;

typedef struct _FSServer FSServer;
typedef union _FSEvent FSEvent;

typedef struct _FSExtent {
    struct _FSExtent *next;	/* next in list */
    FSExtCodes  codes;		/* public information, all extension told */
    int         (*close_server) (FSServer *, FSExtCodes *);	/* routine to call when connection
					 * closed */
    int         (*error) (FSServer *, fsError *, FSExtCodes *, int *);	/* who to call when an error occurs */
    int         (*error_string) (FSServer *, int, FSExtCodes *, char *, int);	/* routine to supply error string */
    char       *name;
}           _FSExtension;

typedef int (*FSSyncHandler)(FSServer *);

/* server data structure */
struct _FSServer {
    struct _FSServer *next;
    int         fd;
    int         proto_version;
    char       *vendor;
    int         byte_order;
    int         vnumber;
    int         release;
    int         resource_id;
    struct _FSQEvent *head,
               *tail;
    int         qlen;
    unsigned long last_request_read;
    unsigned long request;
    char       *last_req;
    char       *buffer;
    char       *bufptr;
    char       *bufmax;
    unsigned    max_request_size;
    char       *server_name;
    char       *auth_data;
    AlternateServer *alternate_servers;
    int         num_alternates;
    FSExtData  *ext_data;
    _FSExtension *ext_procs;
    int         ext_number;
    Bool        (*event_vec[132]) (FSServer *, FSEvent *, fsEvent *);
    Status	(*wire_vec[132]) (FSServer *, FSEvent *, fsEvent *);
    char       *scratch_buffer;
    unsigned long scratch_length;
    FSSyncHandler synchandler;
    unsigned long flags;
    struct _XtransConnInfo *trans_conn; /* transport connection object */
};

typedef struct {
    int         type;
    unsigned long serial;
    Bool        send_event;
    FSServer   *server;
}           FSAnyEvent;

typedef struct {
    int         type;
    FSServer   *server;
    FSID        resourceid;
    unsigned long serial;
    unsigned char error_code;
    unsigned char request_code;
    unsigned char minor_code;
}           FSErrorEvent;

union _FSEvent {
    int         type;
    FSAnyEvent  fsany;
};

typedef struct _FSQEvent {
    struct _FSQEvent *next;
    FSEvent     event;
}           _FSQEvent;


/* protocol-related stuctures */

typedef unsigned long  FSBitmapFormat;
typedef unsigned long  FSBitmapFormatMask;

typedef struct _FSChar2b {
    unsigned char       high;
    unsigned char       low;
} FSChar2b;

typedef struct _FSRange {
    FSChar2b    min_char;
    FSChar2b    max_char;
} FSRange;

typedef struct _FSOffset {
    unsigned int position;
    unsigned int length;
} FSOffset;

/* use names as in xCharInfo? */
typedef struct _FSXCharInfo {
    short 	left;
    short       right;
    short 	width;
    short 	ascent;
    short       descent;
    unsigned short 	attributes;
} FSXCharInfo;

typedef struct _FSPropOffset {
    FSOffset	name;
    FSOffset	value;
    unsigned char 	type;
} FSPropOffset;

typedef struct _FSPropInfo {
    unsigned int	num_offsets;
    unsigned int	data_len;
} FSPropInfo;

/* should names match FontInfoRec? */
typedef struct _FSXFontInfoHeader {
    int		flags;
    FSRange     char_range;
    unsigned	draw_direction;
    FSChar2b    default_char;
    FSXCharInfo	min_bounds;
    FSXCharInfo	max_bounds;
    short 	font_ascent;
    short	font_descent;
} FSXFontInfoHeader;



/* function decls */

_XFUNCPROTOBEGIN

extern FSServer * FSOpenServer ( char *server );

extern FSSyncHandler FSSynchronize(FSServer *, int);
extern FSSyncHandler FSSetAfterFunction(FSServer *, FSSyncHandler);

extern char * FSServerName ( char *server );
extern char ** FSListExtensions ( FSServer *svr, int *next );
extern int FSQueryExtension ( FSServer *svr, char *name, int *major_opcode, 
			      int *first_event, int *first_error );

extern char ** FSListCatalogues ( FSServer *svr, char *pattern, 
				  int maxNames, int *actualCount );
extern char ** FSGetCatalogues ( FSServer *svr, int *num );

extern long FSMaxRequestSize ( FSServer *svr );

extern char ** FSListFonts ( FSServer *svr, char *pattern, int maxNames, 
			     int *actualCount );
extern char ** FSListFontsWithXInfo ( FSServer *svr, char *pattern, 
				      int maxNames, int *count, 
				      FSXFontInfoHeader ***info, 
				      FSPropInfo ***pprops, 
				      FSPropOffset ***offsets, 
				      unsigned char ***prop_data );
extern Font FSOpenBitmapFont ( FSServer *svr, FSBitmapFormat hint, 
			       FSBitmapFormatMask fmask, char *name, 
			       Font *otherid );

extern int FSSync ( FSServer *svr, Bool discard );

extern int FSCloseServer ( FSServer *svr );
extern int FSCloseFont ( FSServer *svr, Font fid );
extern int FSGetErrorDatabaseText ( FSServer *svr, char *name, char *type, 
				    char *defaultp, char *buffer, int nbytes );
extern int FSGetErrorText ( FSServer *svr, int code, char *buffer, 
			    
			    int nbytes );
extern int FSFlush ( FSServer *svr );
extern int FSFreeFontNames ( char **list );
extern int FSFreeCatalogues ( char **list );
extern int FSFreeExtensionList ( char **list );
extern int FSNextEvent ( FSServer *svr, FSEvent *event );
extern int FSQueryXBitmaps8 ( FSServer *svr, Font fid, FSBitmapFormat format, 
			      int range_type, unsigned char *str, 
			      unsigned long str_len, FSOffset **offsets, 
			      unsigned char **glyphdata );
extern int FSQueryXBitmaps16 ( FSServer *svr, Font fid, FSBitmapFormat format,
			       int range_type, FSChar2b *str, 
			       unsigned long str_len, FSOffset **offsets, 
			       unsigned char **glyphdata );
extern int FSQueryXExtents8 ( FSServer *svr, Font fid, int range_type, 
			      unsigned char *str, unsigned long str_len, 
			      FSXCharInfo **extents );
extern int FSQueryXExtents16 ( FSServer *svr, Font fid, int range_type, 
			       FSChar2b *str, unsigned long str_len, 
			       FSXCharInfo **extents );
extern int FSQueryXInfo ( FSServer *svr, Font fid, FSXFontInfoHeader *info, 
			  FSPropInfo *props, FSPropOffset **offsets,
			  unsigned char **prop_data );
extern int FSSetCatalogues ( FSServer *svr, int num, char **cats );
extern int FSFree ( char *data );
extern unsigned char * FSMalloc ( unsigned size );

_XFUNCPROTOEND

#endif				/* _FSLIB_H_ */
