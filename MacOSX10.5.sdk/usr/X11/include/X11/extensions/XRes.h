/*
   Copyright (c) 2002  XFree86 Inc
*/
/* $XdotOrg: xc/include/extensions/XRes.h,v 1.4 2003/12/18 05:48:06 dawes Exp $ */
/* $XFree86: xc/include/extensions/XRes.h,v 1.3 2002/03/10 22:05:51 mvojkovi Exp $ */

#ifndef _XRES_H
#define _XRES_H

#include <X11/Xfuncproto.h>

typedef struct {
  XID resource_base;
  XID resource_mask;
} XResClient;

typedef struct {
  Atom resource_type;
  unsigned int count;
} XResType;

_XFUNCPROTOBEGIN


Bool XResQueryExtension (
   Display *dpy,
   int *event_base,
   int *error_base
);

Status XResQueryVersion (
   Display *dpy,
   int *major_versionp,
   int *minor_versionp
);

Status XResQueryClients (
   Display *dpy,
   int *num_clients,
   XResClient **clients
);

Status XResQueryClientResources (
   Display *dpy,
   XID xid,
   int *num_types,
   XResType **types
);

Status XResQueryClientPixmapBytes (
   Display *dpy,
   XID xid,
   unsigned long *bytes
);

_XFUNCPROTOEND

#endif /* _XRES_H */
