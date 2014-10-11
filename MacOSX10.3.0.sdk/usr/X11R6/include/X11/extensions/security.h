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
/* $XFree86: xc/include/extensions/security.h,v 1.4 2002/11/08 00:46:27 alanh Exp $ */

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

#else /* _SECURITY_SERVER */

#include "input.h"    /* for DeviceIntPtr */
#include "property.h" /* for PropertyPtr */
#include "pixmap.h"   /* for DrawablePtr */
#include "resource.h" /* for RESTYPE */

/* resource type to pass in LookupIDByType for authorizations */
extern RESTYPE SecurityAuthorizationResType;

/* this is what we store for an authorization */
typedef struct {
    XID id;			/* resource ID */
    CARD32 timeout;	/* how long to live in seconds after refcnt == 0 */
    unsigned int trustLevel;	/* trusted/untrusted */
    XID group;			/* see embedding extension */
    unsigned int refcnt;	/* how many clients connected with this auth */
    unsigned int secondsRemaining; /* overflow time amount for >49 days */
    OsTimerPtr timer;		/* timer for this auth */
    struct _OtherClients *eventClients; /* clients wanting events */
} SecurityAuthorizationRec, *SecurityAuthorizationPtr;

/* The following callback is called when a GenerateAuthorization request
 * is processed to sanity check the group argument.  The call data will
 * be a pointer to a SecurityValidateGroupInfoRec (below).  
 * Functions registered on this callback are expected to examine the
 * group and set the valid field to TRUE if they recognize the group as a
 * legitimate group.  If they don't recognize it, they should not change the
 * valid field.
 */
extern CallbackListPtr SecurityValidateGroupCallback;
typedef struct {
    XID group;	/* the group that was sent in GenerateAuthorization */
    Bool valid; /* did anyone recognize it? if so, set to TRUE */
} SecurityValidateGroupInfoRec;

/* Proc vectors for untrusted clients, swapped and unswapped versions.
 * These are the same as the normal proc vectors except that extensions
 * that haven't declared themselves secure will have ProcBadRequest plugged
 * in for their major opcode dispatcher.  This prevents untrusted clients
 * from guessing extension major opcodes and using the extension even though
 * the extension can't be listed or queried.
 */
extern int (*UntrustedProcVector[256])(ClientPtr client);
extern int (*SwappedUntrustedProcVector[256])(ClientPtr client);

extern Bool SecurityCheckDeviceAccess(ClientPtr client, DeviceIntPtr dev,
			       Bool fromRequest);

extern void SecurityAudit(char *format, ...);

#ifdef LBX
extern Bool SecuritySameLevel(ClientPtr client, XID authId);
#endif

extern int XSecurityOptions(int argc, char **argv, int i);

/* Give this value or higher to the -audit option to get security messages */
#define SECURITY_AUDIT_LEVEL 4

extern void SecurityCensorImage(
    ClientPtr client,
    RegionPtr pVisibleRegion,
    long widthBytesLine,
    DrawablePtr pDraw,
    int x, int y, int w, int h,
    unsigned int format,
    char * pBuf);

#define SecurityAllowOperation  0
#define SecurityIgnoreOperation 1
#define SecurityErrorOperation  2

char
SecurityCheckPropertyAccess(
    ClientPtr client,
    WindowPtr pWin,
    ATOM  propertyName,
    Mask access_mode);

#define SECURITY_POLICY_FILE_VERSION "version-1"

char **SecurityGetSitePolicyStrings(int *n);

#endif /* _SECURITY_SERVER */

#endif /* _SECURITY_H */
