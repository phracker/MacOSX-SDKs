/*
   Copyright (c) 2002  XFree86 Inc
*/
/* $XFree86: xc/include/extensions/XResproto.h,v 1.2 2002/03/10 22:05:51 mvojkovi Exp $ */

#ifndef _XRESPROTO_H
#define _XRESPROTO_H

#define XRES_MAJOR_VERSION 1
#define XRES_MINOR_VERSION 0

#define XRES_NAME "X-Resource"

#define X_XResQueryVersion            0
#define X_XResQueryClients            1
#define X_XResQueryClientResources    2
#define X_XResQueryClientPixmapBytes  3

typedef struct {
   CARD32 resource_base;
   CARD32 resource_mask;
} xXResClient;
#define sz_xXResClient 8

typedef struct {
   CARD32 resource_type;
   CARD32 count;
} xXResType;
#define sz_xXResType 8

/* XResQueryVersion */

typedef struct _XResQueryVersion {
   CARD8   reqType;
   CARD8   XResReqType; 
   CARD16  length B16;
   CARD8   client_major;
   CARD8   client_minor;
   CARD16  unused B16;           
} xXResQueryVersionReq;
#define sz_xXResQueryVersionReq 8

typedef struct {
   CARD8   type;
   CARD8   pad1;
   CARD16  sequenceNumber B16; 
   CARD32  length B32;
   CARD16  server_major B16;      
   CARD16  server_minor B16;      
   CARD32  pad2 B32;
   CARD32  pad3 B32;
   CARD32  pad4 B32;
   CARD32  pad5 B32;
   CARD32  pad6 B32; 
} xXResQueryVersionReply;
#define sz_xXResQueryVersionReply  32

/* XResQueryClients */

typedef struct _XResQueryClients {
   CARD8   reqType;
   CARD8   XResReqType;       
   CARD16  length B16;
} xXResQueryClientsReq;
#define sz_xXResQueryClientsReq 4

typedef struct {
   CARD8   type;
   CARD8   pad1;     
   CARD16  sequenceNumber B16;  
   CARD32  length B32;
   CARD32  num_clients B32;
   CARD32  pad2 B32;
   CARD32  pad3 B32;
   CARD32  pad4 B32;
   CARD32  pad5 B32;
   CARD32  pad6 B32;        
} xXResQueryClientsReply;
#define sz_xXResQueryClientsReply  32

/* XResQueryClientResources */

typedef struct _XResQueryClientResources {
   CARD8   reqType;
   CARD8   XResReqType;
   CARD16  length B16;
   CARD32  xid B32;
} xXResQueryClientResourcesReq;
#define sz_xXResQueryClientResourcesReq 8

typedef struct {
   CARD8   type;
   CARD8   pad1;     
   CARD16  sequenceNumber B16;  
   CARD32  length B32;
   CARD32  num_types B32;
   CARD32  pad2 B32;
   CARD32  pad3 B32;
   CARD32  pad4 B32;
   CARD32  pad5 B32;
   CARD32  pad6 B32;
} xXResQueryClientResourcesReply;
#define sz_xXResQueryClientResourcesReply  32

/* XResQueryClientPixmapBytes */

typedef struct _XResQueryClientPixmapBytes {
   CARD8   reqType;
   CARD8   XResReqType;
   CARD16  length B16;
   CARD32  xid B32;
} xXResQueryClientPixmapBytesReq;
#define sz_xXResQueryClientPixmapBytesReq 8

typedef struct {
   CARD8   type;
   CARD8   pad1;
   CARD16  sequenceNumber B16;
   CARD32  length B32;
   CARD32  bytes B32;
   CARD32  bytes_overflow B32;
   CARD32  pad2 B32;
   CARD32  pad3 B32;
   CARD32  pad4 B32;
   CARD32  pad5 B32;
} xXResQueryClientPixmapBytesReply;
#define sz_xXResQueryClientPixmapBytesReply  32


#endif /* _XRESPROTO_H */
