/*
 * $Id: compositeproto.h,v 1.4 2004/07/08 07:20:55 keithp Exp $
 *
 *
 * Copyright © 2006 Sun Microsystems
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of Sun Microsystems not be used in
 * advertising or publicity pertaining to distribution of the software without
 * specific, written prior permission.  Sun Microsystems makes no
 * representations about the suitability of this software for any purpose.  It
 * is provided "as is" without express or implied warranty.
 *
 * SUN MICROSYSTEMS DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL SUN MICROSYSTEMS BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 *
 * Copyright © 2003 Keith Packard
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of Keith Packard not be used in
 * advertising or publicity pertaining to distribution of the software without
 * specific, written prior permission.  Keith Packard makes no
 * representations about the suitability of this software for any purpose.  It
 * is provided "as is" without express or implied warranty.
 *
 * KEITH PACKARD DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL KEITH PACKARD BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef _COMPOSITEPROTO_H_
#define _COMPOSITEPROTO_H_

#include <X11/Xmd.h>
#include <X11/extensions/composite.h>

#define Window CARD32
#define Region CARD32

/* 
 * requests and replies
 */
typedef struct {
    CARD8   reqType;
    CARD8   compositeReqType;
    CARD16  length B16;
    CARD32  majorVersion B32;
    CARD32  minorVersion B32;
} xCompositeQueryVersionReq;

#define sz_xCompositeQueryVersionReq   12

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
} xCompositeQueryVersionReply;

#define sz_xCompositeQueryVersionReply	32

typedef struct {
    CARD8   reqType;
    CARD8   compositeReqType;
    CARD16  length B16;
    Window  window B32;
    CARD8   update;
    CARD8   pad1;
    CARD16  pad2 B16;
} xCompositeRedirectWindowReq;

#define sz_xCompositeRedirectWindowReq	12

typedef struct {
    CARD8   reqType;
    CARD8   compositeReqType;
    CARD16  length B16;
    Window  window B32;
    CARD8   update;
    CARD8   pad1;
    CARD16  pad2 B16;
} xCompositeRedirectSubwindowsReq;

#define sz_xCompositeRedirectSubwindowsReq	    12

typedef struct {
    CARD8   reqType;
    CARD8   compositeReqType;
    CARD16  length B16;
    Window  window B32;
    CARD8   update;
    CARD8   pad1;
    CARD16  pad2 B16;
} xCompositeUnredirectWindowReq;

#define sz_xCompositeUnredirectWindowReq    12

typedef struct {
    CARD8   reqType;
    CARD8   compositeReqType;
    CARD16  length B16;
    Window  window B32;
    CARD8   update;
    CARD8   pad1;
    CARD16  pad2 B16;
} xCompositeUnredirectSubwindowsReq;

#define sz_xCompositeUnredirectSubwindowsReq   12

typedef struct {
    CARD8   reqType;
    CARD8   compositeReqType;
    CARD16  length B16;
    Region  region B32;
    Window  window B32;
} xCompositeCreateRegionFromBorderClipReq;

#define sz_xCompositeCreateRegionFromBorderClipReq  12

/* Version 0.2 additions */

typedef struct {
    CARD8   reqType;
    CARD8   compositeReqType;
    CARD16  length;
    Window  window B32;
    Pixmap  pixmap B32;
} xCompositeNameWindowPixmapReq;

#define sz_xCompositeNameWindowPixmapReq	    12

/* Version 0.3 additions */

typedef struct {
    CARD8   reqType;
    CARD8   compositeReqType;
    CARD16  length B16;
    Window  window B32;
} xCompositeGetOverlayWindowReq;

#define sz_xCompositeGetOverlayWindowReq sizeof(xCompositeGetOverlayWindowReq)

typedef struct {
    BYTE    type;   /* X_Reply */
    BYTE    pad1;
    CARD16  sequenceNumber B16;
    CARD32  length B32;
    Window  overlayWin B32;
    CARD32  pad2 B32;
    CARD32  pad3 B32;
    CARD32  pad4 B32;
    CARD32  pad5 B32;
    CARD32  pad6 B32;
} xCompositeGetOverlayWindowReply;

#define sz_xCompositeGetOverlayWindowReply sizeof(xCompositeGetOverlayWindowReply)

typedef struct {
    CARD8   reqType;
    CARD8   compositeReqType;
    CARD16  length B16;
    Window  window B32;
} xCompositeReleaseOverlayWindowReq;

#define sz_xCompositeReleaseOverlayWindowReq sizeof(xCompositeReleaseOverlayWindowReq)

#undef Window
#undef Region

#endif /* _COMPOSITEPROTO_H_ */
