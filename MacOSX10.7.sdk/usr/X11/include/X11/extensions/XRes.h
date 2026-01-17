/*
   Copyright (c) 2002  XFree86 Inc
*/

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
   int *event_base_return,
   int *error_base_return
);

Status XResQueryVersion (
   Display *dpy,
   int *major_version_return,
   int *minor_version_return
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
