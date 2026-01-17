/*
  XDPSproto.h -- protocol requests constants and alignment values,
  		 analogous to Xproto.h
  		 
Copyright 1988-1994 Adobe Systems Incorporated.
Portions Copyright 1988, 1989 Digital Equipment Corporation.

Permission to use, copy, modify, and distribute this software and
its documentation for any purpose and without fee is hereby granted,
provided that the above copyright notices appear in all copies and
that both those copyright notices and this permission notice appear
in supporting documentation, and that the names of Adobe Systems 
Incorporated and Digital Equipment Corporation not be used in 
advertising or publicity pertaining to distribution of the software 
without specific, written prior permission.  Adobe Systems Incorporated
and Digital Equipment Corporation make no representations about the 
suitability of this software for any purpose.  It is provided "as is" 
without express or implied warranty.

ADOBE SYSTEMS INCORPORATED AND DIGITAL EQUIPMENT CORPORATION DISCLAIM
ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL ADOBE
SYSTEMS INCORPORATED AND DIGITAL EQUIPMENT CORPORATION BE LIABLE FOR
ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES 
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN 
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT 
OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

Author: Adobe Systems Incorporated and Digital Equipment Corporation
  
*/

#ifndef _XDPSproto_h
#define _XDPSproto_h

#include <X11/Xmd.h>

/* For the purpose of the structure definitions in this file, we must
   redefine the following types in terms of Xmd.h's types, which may
   include bit fields. All of these are #undef'd at the end of this
   file, restoring the typedefs in X.h.  */

#define Window   CARD32
#define Drawable CARD32
#define Font     CARD32
#define Pixmap   CARD32
#define Cursor   CARD32
#define Colormap CARD32
#define GContext CARD32
#define Atom     CARD32
#define VisualID CARD32
#define Time     CARD32
#define KeyCode  CARD8
#define KeySym   CARD32

/* NOTE: The Digital UWS 2.2 DECWindows/DPS server uses "DPSExtension"
         for the name of the extension.  The name registered with
         the X Consortium is "Adobe-DPS-Extension".  Your client
         should query both names. */

#define DPSNAME			"Adobe-DPS-Extension"
#define DECDPSNAME		"DPSExtension"

#define DPSPROTO_V09		9                        /* L2-DPS Rel 1.0 */
#define DPSPROTO_V08		8                        /* L1-DPS */
#define DPSPROTO_OLDEST		DPSPROTO_V08

#ifndef DPSPROTOCOLVERSION
#define DPSPROTOCOLVERSION	DPSPROTO_V09
#endif

#define CONTEXTXID		CARD32 
#define SPACEXID		CARD32 

#ifndef BYTESPEROUTPUTEVENT
#define BYTESPEROUTPUTEVENT	24
#endif /* Might be fewer for wide architectures with messy padding */

/*
 * Requests:
 */

#define X_PSInit		1
#define X_PSCreateContext	2
#define X_PSCreateSpace		3
#define X_PSGiveInput		4
#define X_PSGetStatus		5
#define X_PSDestroySpace	6
#define X_PSReset		7
#define X_PSNotifyContext	8
#define X_PSCreateContextFromID	9
#define X_PSXIDFromContext	10
#define X_PSContextFromXID	11
#define X_PSSetStatusMask	12
#define X_PSCreateSecureContext	13            /* L2-DPS/PROTO 9 addition */
#define X_PSNotifyWhenReady	14            /* L2-DPS/PROTO 9 addition */

#define PSLASTREQUEST		X_PSNotifyWhenReady
#define PSLASTREQUEST_P8	X_PSSetStatusMask

typedef struct _PSInit {
    CARD8 reqType;		/* always DPSReqCode */
    CARD8 dpsReqType;		/* always X_PSInit */
    CARD16 length B16;		/* length of request */
    CARD32 libraryversion B32;	/* version of protocol implementation */
} xPSInitReq;
#define sz_xPSInitReq	8

typedef struct _PSCreateContext {
    CARD8 reqType;		/* always DPSReqCode */
    CARD8 dpsReqType;		/* always X_PSCreateContext */
    CARD16 length B16;		/* length of request */
    CONTEXTXID cxid B32;	/* XID for context */
    SPACEXID sxid B32;		/* XID for Space to use for new context */
    Drawable drawable B32;	/* Drawable for new context */
    GContext gc B32;		/* GC for new context */
    INT16 x B16;		/* x, initial origin of context's device */
    INT16 y B16;		/* y, initial origin of context's device */
    CARD32 eventmask B32;	/* events that context is interested in */
    Colormap cmap B32;		/* colormap for this context */
    CARD32 redmax B32;		/* color cube */
    CARD32 redmult B32;
    CARD32 greenmax B32;
    CARD32 greenmult B32;
    CARD32 bluemax B32;
    CARD32 bluemult B32;
    CARD32 colorbase B32;
    CARD32 graymax B32;		/* gray ramp */
    CARD32 graymult B32;
    CARD32 graybase B32;
    CARD32 actual B32;              /* actual colors, if any */
} xPSCreateContextReq;
#define sz_xPSCreateContextReq	76

typedef struct _PSCreateSpace {
    CARD8 reqType;		/* always DPSReqCode */
    CARD8 dpsReqType;		/* always X_PSCreateSpace */
    CARD16 length B16;
    SPACEXID sxid B32;		/* Space to be created */
} xPSCreateSpaceReq;
#define sz_xPSCreateSpaceReq	8

typedef struct _PSGiveInput {
    CARD8 reqType;		/* always DPSReqCode */
    CARD8 dpsReqType;		/* always X_PSGiveInput */
    CARD16 length B16;		/* length of request */
    CARD16 nunits B16;          /* number of bytes in following string */
    CARD16 pad B16;
    CONTEXTXID cxid B32;	/* Context for input. */
} xPSGiveInputReq;
#define sz_xPSGiveInputReq	12

typedef struct _PSGetStatus {
    CARD8 reqType;		/* always DPSReqCode */
    CARD8 dpsReqType;		/* always X_PSGetStatus */
    CARD16 length B16;
    CONTEXTXID cxid B32;
    CARD32 notifyIfChange B32;	/* unused */
} xPSGetStatusReq;
#define sz_xPSGetStatusReq	12

typedef struct _PSDestroySpace {
    CARD8 reqType;		/* always DPSReqCode */
    CARD8 dpsReqType;		/* always X_PSDestroySpace */
    CARD16 length B16;
    SPACEXID sxid B32;
} xPSDestroySpaceReq;
#define sz_xPSDestroySpaceReq	8


typedef struct _PSReset {
    CARD8 reqType;		/* always DPSReqCode */
    CARD8 dpsReqType;		/* always X_PSReset */
    CARD16 length B16;
    CONTEXTXID cxid B32;
} xPSResetReq;
#define sz_xPSResetReq	8

typedef struct _PSNotifyContext {
    CARD8 reqType;		/* always DPSReqCode */
    CARD8 dpsReqType;		/* always X_PSNotifyContext */
    CARD16 length B16;
    CONTEXTXID cxid B32;
    CARD8 notifyType;		/* see XDPS.h */
    CARD8 pad1;
    CARD8 pad2;
    CARD8 pad3;
} xPSNotifyContextReq;
#define sz_xPSNotifyContextReq	12


typedef struct _PSCreateContextFromID {
    CARD8 reqType;		/* always DPSReqCode */
    CARD8 dpsReqType;		/* always X_PSCreateContextFromID */
    CARD16 length B16;
    CARD32 cpsid B32;		/* the PostScript context ID */
    CONTEXTXID cxid B32;	/* resource ID to associate with cpsid */
} xPSCreateContextFromIDReq;
#define sz_xPSCreateContextFromIDReq	12


typedef struct _PSXIDFromContext {
    CARD8 reqType;		/* always DPSReqCode */
    CARD8 dpsReqType;		/* always X_PSXIDFromContext */
    CARD16 length B16;
    CARD32 cpsid B32;
} xPSXIDFromContextReq;
#define sz_xPSXIDFromContextReq	8

typedef struct _PSContextFromXID {
    CARD8 reqType;		/* always DPSReqCode */
    CARD8 dpsReqType;		/* always X_PSContextFromXID */
    CARD16 length B16;
    CONTEXTXID cxid B32;
} xPSContextFromXIDReq;
#define sz_xPSContextFromXIDReq	8

typedef struct _PSSetStatusMask {
    CARD8 reqType;		/* always DPSReqCode */
    CARD8 dpsReqType;		/* always X_PSContextFromXID */
    CARD16 length B16;
    CONTEXTXID cxid B32;
    CARD32 enableMask B32;
    CARD32 disableMask B32;
    CARD32 nextMask B32;
} xPSSetStatusMaskReq;
#define sz_xPSSetStatusMaskReq	20

/* L2-DPS/PROTO 9 addition */
typedef struct _PSCreateContext xPSCreateSecureContextReq;
#define sz_xPSCreateSecureContextReq sz_xPSCreateContextReq

/* L2-DPS/PROTO 9 addition */
typedef struct _PSNotifyWhenReady {
    CARD8 reqType;		/* always DPSReqCode */
    CARD8 dpsReqType;		/* always X_PSNotifyWhenReady */
    CARD16 length B16;
    CONTEXTXID cxid B32;
    INT32 val1 B32;
    INT32 val2 B32;
    INT32 val3 B32;
    INT32 val4 B32;
} xPSNotifyWhenReadyReq;
#define sz_xPSNotifyWhenReadyReq 24



/*
 * Replies:
 */

typedef struct {	
    BYTE type;              /* X_Reply */
    BYTE pad;
    CARD16 sequenceNumber B16;  /* of last request received by server */
    CARD32 length B32;      /* 4 byte quantities beyond size of GenericReply */
    CARD32 cpsid B32;
    CARD32 pad1 B32;
    CARD32 pad2 B32;
    CARD32 pad3 B32;
    CARD32 pad4 B32;
    CARD32 pad5 B32;
    } xPSCreateContextReply;      /* use same reply for CreateSecureContext */

typedef struct {
    BYTE type;              /* X_Reply */
    BYTE status;            /* see XDPS.h */
    CARD16 sequenceNumber B16;  /* of last request received by server */
    CARD32 length B32;      /* 4 byte quantities beyond size of GenericReply */
    CARD32 pad0 B32;
    CARD32 pad1 B32;
    CARD32 pad2 B32;
    CARD32 pad3 B32;
    CARD32 pad4 B32;
    CARD32 pad5 B32;
    } xPSGetStatusReply;

typedef struct {	
    BYTE type;              /* X_Reply */
    BYTE pad;
    CARD16 sequenceNumber B16;  /* of last request received by server */
    CARD32 length B32;      /* 4 byte quantities beyond size of GenericReply */
    SPACEXID sxid B32;
    CARD32 pad1 B32;
    CARD32 pad2 B32;
    CARD32 pad3 B32;
    CARD32 pad4 B32;
    CARD32 pad5 B32;
    } xPSCreateContextFromIDReply;

typedef struct {	
    BYTE type;              /* X_Reply */
    BYTE pad;
    CARD16 sequenceNumber B16;  /* of last request received by server */
    CARD32 length B32;      /* 4 byte quantities beyond size of GenericReply */
    CONTEXTXID cxid B32;
    SPACEXID sxid B32;
    CARD32 pad2 B32;
    CARD32 pad3 B32;
    CARD32 pad4 B32;
    CARD32 pad5 B32;
    } xPSXIDFromContextReply;

typedef struct {	
    BYTE type;              /* X_Reply */
    BYTE pad;
    CARD16 sequenceNumber B16;  /* of last request received by server */
    CARD32 length B32;      /* 4 byte quantities beyond size of GenericReply */
    CARD32 cpsid B32;
    CARD32 pad1 B32;
    CARD32 pad2 B32;
    CARD32 pad3 B32;
    CARD32 pad4 B32;
    CARD32 pad5 B32;
    } xPSContextFromXIDReply;

typedef struct {	
    BYTE type;              /* X_Reply */
    BYTE pad;
    CARD16 sequenceNumber B16;  /* of last request received by server */
    CARD32 length B32;      /* 4 byte quantities beyond size of GenericReply */
    CARD32 serverversion B32;	/* version of protocol implementation */
    CARD32 preferredNumberFormat B32; /* that the server wants to use */
    CARD32 floatingNameLength B32; /* length of name of native floating fmt */
    CARD32 pad1 B32;
    CARD32 pad2 B32;
    CARD32 pad3 B32;
    } xPSInitReply;		/* Followed by name of native floating fmt. */



/*
 * Events:
 */

/* NOTE: The useful data in DPS extension events must fit inside
   of the data portion of a ClientMessage event for the sake of
   DPS NX */

typedef struct {
    BYTE type;
    CARD8 length;
    CARD16 sequenceNumber B16;
    CONTEXTXID cxid B32;
    CARD8 data[BYTESPEROUTPUTEVENT];
} PSOutputEvent;


typedef struct  {
    BYTE type;
    BYTE status;		/* see XDPS.h */
    CARD16 sequenceNumber B16;
    CONTEXTXID cxid B32;
    CARD32 pad1 B32;
    CARD32 pad2 B32;
    CARD32 pad3 B32;
    CARD32 pad4 B32;
    CARD32 pad5 B32;
    CARD32 pad6 B32;
} PSStatusEvent;

/* L2-DPS/PROTO 9 addition */
typedef struct  {
    BYTE type;
    BYTE pad;
    CARD16 sequenceNumber B16;
    CONTEXTXID cxid B32;
    INT32 val1 B32;
    INT32 val2 B32;
    INT32 val3 B32;
    INT32 val4 B32;
    CARD32 pad1 B32;
    CARD32 pad2 B32;
} PSReadyEvent;

/* restore these definitions back to the typedefs in X.h */

#undef Window
#undef Drawable
#undef Font
#undef Pixmap
#undef Cursor
#undef Colormap
#undef GContext
#undef Atom
#undef VisualID
#undef Time
#undef KeyCode
#undef KeySym

#endif /* _XDPSproto_h */
