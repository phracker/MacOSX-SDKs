/*
 * $Xorg: multibuf.h,v 1.4 2001/02/09 02:03:24 xorgcvs Exp $
 *
Copyright 1989, 1998  The Open Group

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

/* $XFree86: xc/include/extensions/multibuf.h,v 3.4 2001/12/14 19:53:28 dawes Exp $ */

#ifndef _MULTIBUF_H_
#define _MULTIBUF_H_

#include <X11/Xfuncproto.h>

#define MULTIBUFFER_PROTOCOL_NAME "Multi-Buffering"

#define MULTIBUFFER_MAJOR_VERSION	1	/* current version numbers */
#define MULTIBUFFER_MINOR_VERSION	1	/* has ClearImageBufferArea */

#define X_MbufGetBufferVersion		0
#define X_MbufCreateImageBuffers	1
#define X_MbufDestroyImageBuffers	2
#define X_MbufDisplayImageBuffers	3
#define X_MbufSetMBufferAttributes	4
#define X_MbufGetMBufferAttributes	5
#define X_MbufSetBufferAttributes	6
#define X_MbufGetBufferAttributes	7
#define X_MbufGetBufferInfo		8
#define X_MbufCreateStereoWindow	9
#define X_MbufClearImageBufferArea	10

/*
 * update_action field
 */
#define MultibufferUpdateActionUndefined	0
#define MultibufferUpdateActionBackground	1
#define MultibufferUpdateActionUntouched	2
#define MultibufferUpdateActionCopied		3

/*
 * update_hint field
 */
#define MultibufferUpdateHintFrequent		0
#define MultibufferUpdateHintIntermittent	1
#define MultibufferUpdateHintStatic		2

/*
 * valuemask fields
 */
#define MultibufferWindowUpdateHint	(1L << 0)
#define MultibufferBufferEventMask	(1L << 0)

/*
 * mono vs. stereo and left vs. right
 */
#define MultibufferModeMono		0
#define MultibufferModeStereo		1
#define MultibufferSideMono		0
#define MultibufferSideLeft	  	1
#define MultibufferSideRight		2

/*
 * clobber state
 */
#define MultibufferUnclobbered		0
#define MultibufferPartiallyClobbered	1
#define MultibufferFullyClobbered	2

/*
 * event stuff
 */
#define MultibufferClobberNotifyMask	0x02000000
#define MultibufferUpdateNotifyMask	0x04000000

#define MultibufferClobberNotify	0
#define MultibufferUpdateNotify		1
#define MultibufferNumberEvents		(MultibufferUpdateNotify + 1)

#define MultibufferBadBuffer		0
#define MultibufferNumberErrors		(MultibufferBadBuffer + 1)


#ifndef _MULTIBUF_SERVER_
/*
 * Extra definitions that will only be needed in the client
 */
typedef XID Multibuffer;

typedef struct {
    int	type;		    /* of event */
    unsigned long serial;   /* # of last request processed by server */
    int send_event;	    /* true if this came frome a SendEvent request */
    Display *display;	    /* Display the event was read from */
    Multibuffer buffer;	    /* buffer of event */
    int	state;		    /* see Clobbered constants above */
} XmbufClobberNotifyEvent;

typedef struct {
    int	type;		    /* of event */
    unsigned long serial;   /* # of last request processed by server */
    int send_event;	    /* true if this came frome a SendEvent request */
    Display *display;	    /* Display the event was read from */
    Multibuffer buffer;	    /* buffer of event */
} XmbufUpdateNotifyEvent;


/*
 * per-window attributes that can be got
 */
typedef struct {
    int displayed_index;	/* which buffer is being displayed */
    int update_action;		/* Undefined, Background, Untouched, Copied */
    int update_hint;		/* Frequent, Intermittent, Static */
    int window_mode;		/* Mono, Stereo */
    int nbuffers;		/* Number of buffers */
    Multibuffer *buffers;	/* Buffers */
} XmbufWindowAttributes;

/*
 * per-window attributes that can be set
 */
typedef struct {
    int update_hint;		/* Frequent, Intermittent, Static */
} XmbufSetWindowAttributes;


/*
 * per-buffer attributes that can be got
 */
typedef struct {
    Window window;		/* which window this belongs to */
    unsigned long event_mask;	/* events that have been selected */
    int buffer_index;		/* which buffer is this */
    int side;			/* Mono, Left, Right */
} XmbufBufferAttributes;

/*
 * per-buffer attributes that can be set
 */
typedef struct {
    unsigned long event_mask;	/* events that have been selected */
} XmbufSetBufferAttributes;


/*
 * per-screen buffer info (there will be lists of them)
 */
typedef struct {
    VisualID visualid;		/* visual usuable at this depth */
    int max_buffers;		/* most buffers for this visual */
    int depth;			/* depth of buffers to be created */
} XmbufBufferInfo;

_XFUNCPROTOBEGIN

extern Bool XmbufQueryExtension(
#if NeedFunctionPrototypes
    Display*		/* dpy */,
    int*		/* event_base_return */,
    int*		/* error_base_return */
#endif
);

extern Status XmbufGetVersion(
#if NeedFunctionPrototypes
    Display*		/* dpy */,
    int*		/* major_version_return */,
    int*		/* minor_version_return */
#endif
);

extern int XmbufCreateBuffers(
#if NeedFunctionPrototypes
    Display*		/* dpy */,
    Window		/* w */,
    int			/* count */,
    int			/* update_action */,
    int			/* update_hint */,
    Multibuffer*	/* buffers */
#endif
);

extern void XmbufDestroyBuffers(
#if NeedFunctionPrototypes
    Display*		/* dpy */,
    Window		/* window */
#endif
);

extern void XmbufDisplayBuffers(
#if NeedFunctionPrototypes
    Display*		/* dpy */,
    int			/* count */,
    Multibuffer*	/* buffers */,
    int			/* min_delay */,
    int			/* max_delay */
#endif
);

extern Status XmbufGetWindowAttributes(
#if NeedFunctionPrototypes
    Display*			/* dpy */,
    Window			/* w */,
    XmbufWindowAttributes*	/* attr */
#endif
);

extern void XmbufChangeWindowAttributes(
#if NeedFunctionPrototypes
    Display*			/* dpy */,
    Window			/* w */,
    unsigned long		/* valuemask */,
    XmbufSetWindowAttributes*	/* attr */
#endif
);

extern Status XmbufGetBufferAttributes(
#if NeedFunctionPrototypes
    Display*			/* dpy */,
    Multibuffer			/* b */,
    XmbufBufferAttributes*	/* attr */
#endif
);

extern void XmbufChangeBufferAttributes(
#if NeedFunctionPrototypes
    Display*			/* dpy */,
    Multibuffer			/* b */,
    unsigned long		/* valuemask */,
    XmbufSetBufferAttributes*	/* attr */
#endif
);

extern Status XmbufGetScreenInfo(
#if NeedFunctionPrototypes
    Display*			/* dpy */,
    Drawable			/* d */,
    int*			/* nmono_return */,
    XmbufBufferInfo**		/* mono_info_return */,
    int*			/* nstereo_return */,
    XmbufBufferInfo**		/* stereo_info_return */
#endif
);

extern Window XmbufCreateStereoWindow(
#if NeedFunctionPrototypes
    Display*			/* dpy */,
    Window			/* parent */,
    int				/* x */,
    int				/* y */,
    unsigned int		/* width */,
    unsigned int		/* height */,
    unsigned int		/* border_width */,
    int				/* depth */,
    unsigned int		/* class */,
    Visual*			/* visual */,
    unsigned long		/* valuemask */,
    XSetWindowAttributes*	/* attr */,
    Multibuffer*		/* leftp */,
    Multibuffer*		/* rightp */
#endif
);

extern void XmbufClearBufferArea(
#if NeedFunctionPrototypes
    Display*			/* dpy */,
    Multibuffer			/* buffer */,
    int				/* x */,
    int				/* y */,
    unsigned int		/* width */,
    unsigned int		/* height */,
    Bool			/* exposures */
#endif
);

_XFUNCPROTOEND

#else

#include "scrnintstr.h"

typedef Bool	(* mbInitFunc)();

struct _mbufScreen;		/* declared in multibufst.h */

extern void	RegisterMultibufferInit(
#if NeedFunctionPrototypes
    ScreenPtr			/* pScreen */,
    Bool (* /* bufMultibufferInit */)(
#if NeedNestedPrototypes
	ScreenPtr		/* pScreen */,
	struct _mbufScreen *	/* pMBScreen */
#endif
    )
#endif
);

struct xMbufBufferInfo;		/* declared in multibufst.h */

extern void	RegisterDoubleBufferHardware(
#if NeedFunctionPrototypes
    ScreenPtr			/* pScreen */,
    int				/* nInfo */,
    struct xMbufBufferInfo *	/* pInfo */,
    DevUnion *			/* frameBuffer */,
    DevUnion			/* selectPlane */,
    void (* /* CopyBufferBitsFunc */ )(),
    void (* /* DrawSelectPlaneFunc */ )()
#endif
);

extern int	CreateImageBuffers (
#if NeedFunctionPrototypes
    WindowPtr			/* pWin */,
    int				/* nbuf */,
    XID *			/* ids */,
    int				/* action */,
    int				/* hint */
#endif
);
extern void	DestroyImageBuffers (
#if NeedFunctionPrototypes
    WindowPtr			/* pWin */
#endif
);
extern int	DisplayImageBuffers (
#if NeedFunctionPrototypes
    XID *			/* ids */,
    int				/* nbuf */
#endif
);

#endif /* _MULTIBUF_SERVER_ */
#endif /* _MULTIBUF_H_ */
