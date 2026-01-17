/* $Xorg: security.h,v 1.4 2001/02/09 02:03:24 xorgcvs Exp $ */
/*
Copyright 1996, 1998  The Open Group

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
/* $XFree86: xc/include/extensions/security.h,v 1.3 2001/12/14 19:53:29 dawes Exp $ */

#ifndef _SECURITY_H
#define _SECURITY_H

#define _XAUTH_STRUCT_ONLY
#include <X11/Xauth.h>

/* constants that server, library, and application all need */

#define XSecurityNumberEvents		1
#define XSecurityNumberErrors		2
#define XSecurityBadAuthorization	0
#define XSecurityBadAuthorizationProtocol 1

/* trust levels */
#define XSecurityClientTrusted		0
#define XSecurityClientUntrusted	1

/* authorization attribute masks */
#define XSecurityTimeout		(1<<0)
#define XSecurityTrustLevel		(1<<1)
#define XSecurityGroup  		(1<<2)
#define XSecurityEventMask		(1<<3)
#define XSecurityAllAuthorizationAttributes \
 (XSecurityTimeout | XSecurityTrustLevel | XSecurityGroup | XSecurityEventMask)

/* event masks */
#define XSecurityAuthorizationRevokedMask (1<<0)
#define XSecurityAllEventMasks XSecurityAuthorizationRevokedMask

/* event offsets */
#define XSecurityAuthorizationRevoked 0
    
#define XSecurityAuthorizationName	"XC-QUERY-SECURITY-1"
#define XSecurityAuthorizationNameLen	19


#ifndef _SECURITY_SERVER

_XFUNCPROTOBEGIN

Status XSecurityQueryExtension (
    Display *dpy,
    int *major_version_return,
    int *minor_version_return);

Xauth *XSecurityAllocXauth(void);

void XSecurityFreeXauth(Xauth *auth);

/* type for returned auth ids */
typedef unsigned long XSecurityAuthorization;

typedef struct {
    unsigned int timeout;
    unsigned int trust_level;
    XID          group;
    long	 event_mask;
} XSecurityAuthorizationAttributes;

Xauth *XSecurityGenerateAuthorization(
    Display *dpy,
    Xauth *auth_in,
    unsigned long valuemask,
    XSecurityAuthorizationAttributes *attributes,
    XSecurityAuthorization *auth_id_return);

Status XSecurityRevokeAuthorization(
    Display *dpy,
    XSecurityAuthorization auth_id);

_XFUNCPROTOEND

typedef struct {
    int type;		      /* event base + XSecurityAuthorizationRevoked */
    unsigned long serial;     /* # of last request processed by server */
    Bool send_event;	      /* true if this came from a SendEvent request */
    Display *display;	      /* Display the event was read from */
    XSecurityAuthorization auth_id; /* revoked authorization id */
} XSecurityAuthorizationRevokedEvent;

#endif /* _SECURITY_SERVER */

#endif /* _SECURITY_H */
