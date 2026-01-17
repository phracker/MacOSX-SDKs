/*
 * Copyright © 2008 Red Hat, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Soft-
 * ware"), to deal in the Software without restriction, including without
 * limitation the rights to use, copy, modify, merge, publish, distribute,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, provided that the above copyright
 * notice(s) and this permission notice appear in all copies of the Soft-
 * ware and that both the above copyright notice(s) and this permission
 * notice appear in supporting documentation.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABIL-
 * ITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY
 * RIGHTS. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR HOLDERS INCLUDED IN
 * THIS NOTICE BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL INDIRECT OR CONSE-
 * QUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFOR-
 * MANCE OF THIS SOFTWARE.
 *
 * Except as contained in this notice, the name of a copyright holder shall
 * not be used in advertising or otherwise to promote the sale, use or
 * other dealings in this Software without prior written authorization of
 * the copyright holder.
 *
 * Authors:
 *   Kristian Høgsberg (krh@redhat.com)
 */

#ifndef _DRI2_PROTO_H_
#define _DRI2_PROTO_H_

#define DRI2_NAME			"DRI2"
#define DRI2_MAJOR			1
#define DRI2_MINOR			0

#define DRI2NumberErrors		0
#define DRI2NumberEvents		0
#define DRI2NumberRequests		6

#define X_DRI2QueryVersion		0
#define X_DRI2Connect			1
#define X_DRI2AuthConnection		2
#define X_DRI2CreateDrawable		3
#define X_DRI2DestroyDrawable		4
#define X_DRI2ReemitDrawableInfo	5

typedef struct {
    CARD8   reqType;
    CARD8   dri2ReqType;
    CARD16  length B16;
    CARD32  majorVersion B32;
    CARD32  minorVersion B32;
} xDRI2QueryVersionReq;
#define sz_xDRI2QueryVersionReq   12

typedef struct {
    BYTE    type;   /* X_Reply */
    BYTE    pad1;
    CARD16  sequenceNumber B16;
    CARD32  length B32;
    CARD32  majorVersion B32;
    CARD32  minorVersion B32;
    CARD32  pad2 B32;
    CARD32  pad3 B32;
    CARD32  pad4 B32;
    CARD32  pad5 B32;
} xDRI2QueryVersionReply;
#define sz_xDRI2QueryVersionReply	32

typedef struct {
    CARD8   reqType;
    CARD8   dri2ReqType;
    CARD16  length B16;
    CARD32  screen B32;
} xDRI2ConnectReq;
#define sz_xDRI2ConnectReq   8

typedef struct {
    BYTE    type;   /* X_Reply */
    BYTE    pad1;
    CARD16  sequenceNumber B16;
    CARD32  length B32;
    CARD32  driverNameLength B32;
    CARD32  busIdLength B32;
    CARD32  sareaHandle B32;
    CARD32  pad2 B32;
    CARD32  pad3 B32;
    CARD32  pad4 B32;
} xDRI2ConnectReply;
#define sz_xDRI2ConnectReply	32

typedef struct {
    CARD8   reqType;
    CARD8   dri2ReqType;
    CARD16  length B16;
    CARD32  screen B32;
    CARD32  magic B32;
} xDRI2AuthConnectionReq;
#define sz_xDRI2AuthConnectionReq   12

typedef struct {
    BYTE    type;   /* X_Reply */
    BYTE    pad1;
    CARD16  sequenceNumber B16;
    CARD32  length B32;
    CARD32  authenticated B32;
    CARD32  pad2 B32;
    CARD32  pad3 B32;
    CARD32  pad4 B32;
    CARD32  pad5 B32;
    CARD32  pad6 B32;
} xDRI2AuthConnectionReply;
#define sz_xDRI2AuthConnectionReply	32

typedef struct {
    CARD8   reqType;
    CARD8   dri2ReqType;
    CARD16  length B16;
    CARD32  drawable B32;
} xDRI2CreateDrawableReq;
#define sz_xDRI2CreateDrawableReq	8

typedef struct {
    BYTE    type;   /* X_Reply */
    BYTE    pad1;
    CARD16  sequenceNumber B16;
    CARD32  length B32;
    CARD32  handle B32;
    CARD32  head B32;
    CARD32  pad2 B32;
    CARD32  pad3 B32;
    CARD32  pad4 B32;
    CARD32  pad5 B32;
} xDRI2CreateDrawableReply;
#define sz_xDRI2CreateDrawableReply	32

typedef struct {
    CARD8   reqType;
    CARD8   dri2ReqType;
    CARD16  length B16;
    CARD32  drawable B32;
} xDRI2DestroyDrawableReq;
#define sz_xDRI2DestroyDrawableReq	8

typedef struct {
    CARD8   reqType;
    CARD8   dri2ReqType;
    CARD16  length B16;
    CARD32  drawable B32;
} xDRI2ReemitDrawableInfoReq;
#define sz_xDRI2ReemitDrawableInfoReq   8

typedef struct {
    BYTE    type;   /* X_Reply */
    BYTE    pad1;
    CARD16  sequenceNumber B16;
    CARD32  length B32;
    CARD32  head B32;
    CARD32  pad2 B32;
    CARD32  pad3 B32;
    CARD32  pad4 B32;
    CARD32  pad5 B32;
    CARD32  pad6 B32;
} xDRI2ReemitDrawableInfoReply;
#define sz_xDRI2ReemitDrawableInfoReply	32

#endif
