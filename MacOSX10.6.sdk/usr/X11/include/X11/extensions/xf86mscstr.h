/* $XFree86: xc/include/extensions/xf86mscstr.h,v 3.12 2002/11/20 04:04:56 dawes Exp $ */

/*
 * Copyright (c) 1995, 1996  The XFree86 Project, Inc
 */

/* THIS IS NOT AN X CONSORTIUM STANDARD */

#ifndef _XF86MISCSTR_H_
#define _XF86MISCSTR_H_

#include <X11/extensions/xf86misc.h>

#define XF86MISCNAME		"XFree86-Misc"

#define XF86MISC_MAJOR_VERSION	0	/* current version numbers */
#define XF86MISC_MINOR_VERSION	9

typedef struct _XF86MiscQueryVersion {
    CARD8	reqType;		/* always XF86MiscReqCode */
    CARD8	xf86miscReqType;	/* always X_XF86MiscQueryVersion */
    CARD16	length B16;
} xXF86MiscQueryVersionReq;
#define sz_xXF86MiscQueryVersionReq	4

typedef struct {
    BYTE	type;			/* X_Reply */
    BOOL	pad1;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD16	majorVersion B16;	/* major version of XFree86-Misc */
    CARD16	minorVersion B16;	/* minor version of XFree86-Misc */
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
    CARD32	pad6 B32;
} xXF86MiscQueryVersionReply;
#define sz_xXF86MiscQueryVersionReply	32

#ifdef _XF86MISC_SAVER_COMPAT_
typedef struct _XF86MiscGetSaver {
    CARD8       reqType;                /* always XF86MiscReqCode */
    CARD8       xf86miscReqType;     /* always X_XF86MiscGetSaver */
    CARD16      length B16; 
    CARD16      screen B16;
    CARD16      pad B16;
} xXF86MiscGetSaverReq;
#define sz_xXF86MiscGetSaverReq	8

typedef struct _XF86MiscSetSaver {
    CARD8	reqType;		/* always XF86MiscReqCode */
    CARD8	xf86miscReqType;	/* always X_XF86MiscSetSaver */
    CARD16	length B16;
    CARD16	screen B16;
    CARD16	pad B16;
    CARD32	suspendTime B32;
    CARD32	offTime B32;
} xXF86MiscSetSaverReq;
#define sz_xXF86MiscSetSaverReq	16

typedef struct {
    BYTE	type;
    BOOL	pad1;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD32	suspendTime B32;
    CARD32	offTime B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
} xXF86MiscGetSaverReply;
#define sz_xXF86MiscGetSaverReply	32
#endif

typedef struct _XF86MiscGetMouseSettings {
    CARD8	reqType;		/* always XF86MiscReqCode */
    CARD8	xf86miscReqType;	/* always X_XF86MiscGetMouseSettings */
    CARD16	length B16;
} xXF86MiscGetMouseSettingsReq;
#define sz_xXF86MiscGetMouseSettingsReq	4

typedef struct {
    BYTE	type;			/* X_Reply */
    BOOL	pad1;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD32	mousetype B32;
    CARD32	baudrate B32;
    CARD32	samplerate B32;
    CARD32	resolution B32;
    CARD32	buttons B32;
    BOOL	emulate3buttons;
    BOOL	chordmiddle;
    CARD16	pad2 B16;
    CARD32	emulate3timeout B32;
    CARD32	flags B32;
    CARD32	devnamelen B32;		/* strlen(device)+1 */
} xXF86MiscGetMouseSettingsReply;
#define sz_xXF86MiscGetMouseSettingsReply	44

typedef struct _XF86MiscGetKbdSettings {
    CARD8	reqType;		/* always XF86MiscReqCode */
    CARD8	xf86miscReqType;	/* always X_XF86MiscGetKbdSettings */
    CARD16	length B16;
} xXF86MiscGetKbdSettingsReq;
#define sz_xXF86MiscGetKbdSettingsReq	4

typedef struct {
    BYTE	type;			/* X_Reply */
    BOOL	pad1;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD32	kbdtype B32;
    CARD32	rate B32;
    CARD32	delay B32;
    BOOL	servnumlock;
    BOOL	pad2;
    CARD16	pad3 B16;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
} xXF86MiscGetKbdSettingsReply;
#define sz_xXF86MiscGetKbdSettingsReply	32

typedef struct _XF86MiscSetMouseSettings {
    CARD8	reqType;		/* always XF86MiscReqCode */
    CARD8	xf86miscReqType;	/* always X_XF86MiscSetMouseSettings */
    CARD16	length B16;
    CARD32	mousetype B32;
    CARD32	baudrate B32;
    CARD32	samplerate B32;
    CARD32	resolution B32;
    CARD32	buttons B32;
    BOOL	emulate3buttons;
    BOOL	chordmiddle;
    CARD16	devnamelen B16;
    CARD32	emulate3timeout B32;
    CARD32	flags B32;
} xXF86MiscSetMouseSettingsReq;
#define sz_xXF86MiscSetMouseSettingsReq	36

typedef struct _XF86MiscSetKbdSettings {
    CARD8	reqType;		/* always XF86MiscReqCode */
    CARD8	xf86miscReqType;	/* always X_XF86MiscSetKbdSettings */
    CARD16	length B16;
    CARD32	kbdtype B32;
    CARD32	rate B32;
    CARD32	delay B32;
    BOOL	servnumlock;
    BOOL	pad1;
    CARD16	pad2 B16;
} xXF86MiscSetKbdSettingsReq;
#define sz_xXF86MiscSetKbdSettingsReq	20

typedef struct _XF86MiscSetGrabKeysState {
    CARD8	reqType;		/* always XF86MiscReqCode */
    CARD8	xf86miscReqType;	/* always X_XF86MiscSetKbdSettings */
    CARD16	length B16;
    BOOL	enable;
    BOOL	pad1;
    CARD16	pad2 B16;
} xXF86MiscSetGrabKeysStateReq;
#define sz_xXF86MiscSetGrabKeysStateReq	8

typedef struct {
    BYTE	type;
    BOOL	pad1;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD32	status B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
    CARD32	pad6 B32;
} xXF86MiscSetGrabKeysStateReply;
#define sz_xXF86MiscSetGrabKeysStateReply	32

typedef struct _XF86MiscSetClientVersion {
    CARD8	reqType;		/* always XF86MiscReqCode */
    CARD8	xf86miscReqType;
    CARD16	length B16;
    CARD16	major B16;
    CARD16	minor B16;
} xXF86MiscSetClientVersionReq;
#define sz_xXF86MiscSetClientVersionReq	8

typedef struct _XF86MiscGetFilePaths {
    CARD8	reqType;		/* always XF86MiscReqCode */
    CARD8	xf86miscReqType;	/* always X_XF86MiscGetFilePaths */
    CARD16	length B16;
} xXF86MiscGetFilePathsReq;
#define sz_xXF86MiscGetFilePathsReq	4

typedef struct {
    BYTE	type;			/* X_Reply */
    BOOL	pad1;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD16	configlen B16;
    CARD16	modulelen B16;
    CARD16	loglen B16;
    CARD16	pad2 B16;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
    CARD32	pad6 B32;
} xXF86MiscGetFilePathsReply;
#define sz_xXF86MiscGetFilePathsReply	32

typedef struct _XF86MiscPassMessage {
    CARD8	reqType;		/* always XF86MiscReqCode */
    CARD8	xf86miscReqType;	/* always X_XF86MiscPassMessage */
    CARD16	length B16;
    CARD16	typelen B16;
    CARD16	vallen B16;
    CARD16      screen B16;
    CARD16      pad B16;
} xXF86MiscPassMessageReq;
#define sz_xXF86MiscPassMessageReq	12

typedef struct {
    BYTE	type;			/* X_Reply */
    BYTE	pad1;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD16	mesglen B16;
    CARD16	pad2 B16;
    CARD32	status B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
    CARD32	pad6 B32;
} xXF86MiscPassMessageReply;
#define sz_xXF86MiscPassMessageReply	32

#endif /* _XF86MISCSTR_H_ */
