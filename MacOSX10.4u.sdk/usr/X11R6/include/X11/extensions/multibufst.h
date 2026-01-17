/*
 * $Xorg: multibufst.h,v 1.4 2001/02/09 02:03:24 xorgcvs Exp $
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

/* $XFree86: xc/include/extensions/multibufst.h,v 3.9 2003/11/17 22:20:03 dawes Exp $ */

#ifndef _MULTIBUFST_H_
#define _MULTIBUFST_H_

/*
 * Protocol requests constants and alignment values
 */

#include "multibuf.h"
#ifdef _MULTIBUF_SERVER_
#include "inputstr.h"
#endif

#if !defined(UNIXCPP) || defined(ANSICPP)
#define MbufGetReq(name,req,info) GetReq (name, req); \
	req->reqType = info->codes->major_opcode; \
	req->mbufReqType = X_##name;
#else
#define MbufGetReq(name,req,info) GetReq (name, req); \
	req->reqType = info->codes->major_opcode; \
	req->mbufReqType = X_/**/name;
#endif

#define Window CARD32
#define Drawable CARD32
#define VisualID CARD32
#define Multibuffer CARD32

typedef struct xMbufBufferInfo {
	CARD32	visualID B32;		/* associated visual */
	CARD16	maxBuffers B16;		/* maximum supported buffers */
	CARD8	depth;			/* depth of visual (redundant) */
	CARD8	unused;
} xMbufBufferInfo;
#define sz_xMbufBufferInfo 8

typedef struct {
    BYTE    type;
    BYTE    unused;
    CARD16  sequenceNumber B16;
    CARD32  buffer B32;			/* affected buffer */
    BYTE    state;			/* current status */
    CARD8   unused1;
    CARD16  unused2 B16;
    CARD32  unused3 B32;
    CARD32  unused4 B32;
    CARD32  unused5 B32;
    CARD32  unused6 B32;
    CARD32  unused7 B32;
} xMbufClobberNotifyEvent;

typedef struct {
    BYTE    type;
    BYTE    unused;
    CARD16  sequenceNumber B16;
    CARD32  buffer B32;			/* affected buffer */
    CARD32  timeStamp B32;		/* update time */
    CARD32  unused1 B32;
    CARD32  unused2 B32;
    CARD32  unused3 B32;
    CARD32  unused4 B32;
    CARD32  unused5 B32;
    CARD32  unused6 B32;
} xMbufUpdateNotifyEvent;

typedef struct {
    CARD8	reqType;		/* always codes->major_opcode */
    CARD8	mbufReqType;		/* always X_MbufGetBufferVersion */
    CARD16	length B16;
} xMbufGetBufferVersionReq;
#define sz_xMbufGetBufferVersionReq	4

typedef struct {
    BYTE	type;			/* X_Reply */
    CARD8	unused;			/* not used */
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD8	majorVersion;	/* major version of Multi-Buffering protocol */
    CARD8	minorVersion;	/* minor version of Multi-Buffering protocol */
    CARD16	pad1 B16;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
    CARD32	pad6 B32;
} xMbufGetBufferVersionReply;
#define sz_xMbufGetBufferVersionReply	32

typedef struct {
    CARD8	reqType;	/* always codes->major_opcode */
    CARD8	mbufReqType;	/* always X_MbufCreateImageBuffers */
    CARD16	length B16;
    CARD32	window B32;	/* associated window */
    CARD8	updateAction;	/* action at update */
    CARD8	updateHint;	/* hint as to frequency of updates */
    CARD16	unused;
} xMbufCreateImageBuffersReq;	/* followed by buffer ids */
#define sz_xMbufCreateImageBuffersReq	12

typedef struct {
    BYTE	type;			/* X_Reply */
    CARD8	unused;			/* not used */
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD16	numberBuffer B16;	/* number successfully allocated */
    CARD16	unused1 B16;
    CARD32	unused2 B32;
    CARD32	unused3 B32;
    CARD32	unused4 B32;
    CARD32	unused5 B32;
    CARD32	unused6 B32;
} xMbufCreateImageBuffersReply;
#define sz_xMbufCreateImageBuffersReply 32

typedef struct {
    CARD8	reqType;	/* always codes->major_opcode */
    CARD8	mbufReqType;	/* always X_MbufDestroyImageBuffers */
    CARD16	length B16;
    CARD32	window B32;	/* associated window */
} xMbufDestroyImageBuffersReq;
#define sz_xMbufDestroyImageBuffersReq	8

typedef struct {
    CARD8	reqType;	/* always codes->major_opcode */
    CARD8	mbufReqType;	/* always X_MbufDisplayImageBuffers */
    CARD16	length B16;
    CARD16	minDelay B16;	/* minimum time between last update and now */
    CARD16	maxDelay B16;	/* maximum time between last update and now */
} xMbufDisplayImageBuffersReq;	/* followed by list of buffers */
#define sz_xMbufDisplayImageBuffersReq	8

typedef struct {
    CARD8	reqType;	/* always codes->major_opcode */
    CARD8	mbufReqType;	/* always X_MbufSetMBufferAttributes */
    CARD16	length B16;
    CARD32	window B32;	/* associated window */
    CARD32	valueMask B32;	/* modified entries */
} xMbufSetMBufferAttributesReq;	/* followed by values */
#define sz_xMbufSetMBufferAttributesReq 12

typedef struct {
    CARD8	reqType;	/* always codes->major_opcode */
    CARD8	mbufReqType;	/* always X_MbufGetMBufferAttributes */
    CARD16	length B16;
    CARD32	window B32;	/* associated window */
} xMbufGetMBufferAttributesReq;
#define sz_xMbufGetMBufferAttributesReq 8

typedef struct {
    BYTE	type;			/* X_Reply */
    CARD8	unused;			/* not used */
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD16	displayedBuffer B16;	/* currently visible buffer */
    CARD8	updateAction;
    CARD8	updateHint;
    CARD8	windowMode;
    CARD8	unused0;
    CARD16	unused1 B16;
    CARD32	unused2 B32;
    CARD32	unused3 B32;
    CARD32	unused4 B32;
    CARD32	unused5 B32;
} xMbufGetMBufferAttributesReply;
#define sz_xMbufGetMBufferAttributesReply 32

typedef struct {
    CARD8	reqType;	/* always codes->major_opcode */
    CARD8	mbufReqType;	/* always X_MbufSetBufferAttributes */
    CARD16	length B16;
    CARD32	buffer B32;
    CARD32	valueMask B32;
} xMbufSetBufferAttributesReq;	/* followed by values */
#define sz_xMbufSetBufferAttributesReq 12

typedef struct {
    CARD8	reqType;	/* always codes->major_opcode */
    CARD8	mbufReqType;	/* always X_MbufGetBufferAttributes */
    CARD16	length B16;
    CARD32	buffer B32;
} xMbufGetBufferAttributesReq;
#define sz_xMbufGetBufferAttributesReq 8

typedef struct {
    BYTE	type;			/* X_Reply */
    CARD8	unused;			/* not used */
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD32	window B32;
    CARD32	eventMask B32;
    CARD16	bufferIndex B16;
    CARD8	side;
    CARD8	unused0;
    CARD32	unused1 B32;
    CARD32	unused2 B32;
    CARD32	unused3 B32;
} xMbufGetBufferAttributesReply;
#define sz_xMbufGetBufferAttributesReply 32

typedef struct {
    CARD8	reqType;	/* always codes->major_opcode */
    CARD8	mbufReqType;	/* always X_MbufGetBufferInfo */
    CARD16	length B16;
    Drawable	drawable B32;
} xMbufGetBufferInfoReq;
#define sz_xMbufGetBufferInfoReq 8

typedef struct {
    BYTE	type;			/* X_Reply */
    CARD8	unused;			/* not used */
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD16	normalInfo B16;
    CARD16	stereoInfo B16;
    CARD32	unused1 B32;
    CARD32	unused2 B32;
    CARD32	unused3 B32;
    CARD32	unused4 B32;
    CARD32	unused5 B32;
} xMbufGetBufferInfoReply;			/* followed by buffer infos */
#define sz_xMbufGetBufferInfoReply 32


typedef struct {
    CARD8	reqType;	/* always codes->major_opcode */
    CARD8	mbufReqType;	/* always X_MbufCreateStereoWindow */
    CARD16	length B16;
    CARD8	unused0;
    CARD8	unused1;
    CARD8	unused2;
    CARD8	depth;
    Window	wid B32;
    Window	parent B32;
    Multibuffer	left B32;	/* associated buffers */
    Multibuffer	right B32;
    INT16	x B16;
    INT16	y B16;
    CARD16	width B16;
    CARD16	height B16;
    CARD16	borderWidth B16;  
#if defined(__cplusplus) || defined(c_plusplus)
    CARD16	c_class B16;
#else
    CARD16	class B16;
#endif
    VisualID	visual B32;
    CARD32	mask B32;
} xMbufCreateStereoWindowReq;		/* followed by value list */
#define sz_xMbufCreateStereoWindowReq 44

typedef struct {
    CARD8     reqType;        /* always codes->major_opcode */
    CARD8     mbufReqType;    /* always X_MbufClearImageBufferArea */
    CARD16    length B16;
    Multibuffer       buffer B32;
    INT16     x B16;
    INT16     y B16;
    CARD16    width B16;
    CARD16    height B16;
    CARD8     unused0;
    CARD8     unused1;
    CARD8     unused2;
    BOOL      exposures;
} xMbufClearImageBufferAreaReq;
#define sz_xMbufClearImageBufferAreaReq 20

#undef Window
#undef Drawable
#undef VisualID
#undef Multibuffer


#ifdef _MULTIBUF_SERVER_
/* Macros for wrapping and unwrapping functions */

#define SWAP_FUNC_VECTOR(pSTRUCT1,pSTRUCT2,DATA_TYPE,FUNC_NAME)		\
{									\
    DATA_TYPE (* tmpFn)();						\
    									\
    tmpFn = pSTRUCT1->FUNC_NAME;					\
    pSTRUCT1->FUNC_NAME = pSTRUCT2->FUNC_NAME;				\
    pSTRUCT2->FUNC_NAME = tmpFn;					\
}

#if !defined(UNIXCPP) || defined(ANSICPP)
#define WRAP_SCREEN_FUNC(pSCREEN,pPRIV,FUNC_NAME, PRIV_FUNC_NAME)	\
{									\
    if ((pPRIV->funcsWrapped & FUNC_NAME##Mask) == 0)			\
    {									\
	pPRIV->FUNC_NAME   = pSCREEN->FUNC_NAME;			\
	pSCREEN->FUNC_NAME = PRIV_FUNC_NAME;				\
	pPRIV->funcsWrapped |= FUNC_NAME##Mask;				\
    }									\
}

#define UNWRAP_SCREEN_FUNC(pSCREEN,pPRIV,DATA_TYPE,FUNC_NAME)		\
{									\
    SWAP_FUNC_VECTOR(pSCREEN,pPRIV,DATA_TYPE,FUNC_NAME);		\
    pPRIV->funcsWrapped &= ~(FUNC_NAME##Mask);				\
}

#define REWRAP_SCREEN_FUNC(pSCREEN,pPRIV,DATA_TYPE,FUNC_NAME)		\
{									\
    if (MB_SCREEN_PRIV(pSCREEN)->mbufWindowCount)			\
    {									\
	SWAP_FUNC_VECTOR(pSCREEN,pPRIV,DATA_TYPE,FUNC_NAME);		\
	pPRIV->funcsWrapped |= FUNC_NAME##Mask;				\
    }									\
}
#else
#define WRAP_SCREEN_FUNC(pSCREEN,pPRIV,FUNC_NAME, PRIV_FUNC_NAME)	\
{									\
    if ((pPRIV->funcsWrapped & FUNC_NAME/**/Mask) == 0)			\
    {									\
	pPRIV->FUNC_NAME   = pSCREEN->FUNC_NAME;			\
	pSCREEN->FUNC_NAME = PRIV_FUNC_NAME;				\
	pPRIV->funcsWrapped |= FUNC_NAME/**/Mask;			\
    }									\
}

#define UNWRAP_SCREEN_FUNC(pSCREEN,pPRIV,DATA_TYPE,FUNC_NAME)		\
{									\
    SWAP_FUNC_VECTOR(pSCREEN,pPRIV,DATA_TYPE,FUNC_NAME);		\
    pPRIV->funcsWrapped &= ~(FUNC_NAME/**/Mask);			\
}

#define REWRAP_SCREEN_FUNC(pSCREEN,pPRIV,DATA_TYPE,FUNC_NAME)		\
{									\
    if (MB_SCREEN_PRIV(pSCREEN)->mbufWindowCount)			\
    {									\
	SWAP_FUNC_VECTOR(pSCREEN,pPRIV,DATA_TYPE,FUNC_NAME);		\
	pPRIV->funcsWrapped |= FUNC_NAME/**/Mask;			\
    }									\
}
#endif

/* The _Multibuffer and _Multibuffers structures below refer to each other,
 * so we need this forward declaration
 */
typedef struct _Multibuffers	*MultibuffersPtr;

/*
 * per-Multibuffer data
 */
 
typedef struct _Multibuffer {
    MultibuffersPtr pMultibuffers;  /* associated window data */
    Mask	    eventMask;	    /* MultibufferClobberNotifyMask|ExposureMask|MultibufferUpdateNotifyMask */
    Mask	    otherEventMask; /* mask of all other clients event masks */
    OtherClients    *otherClients;  /* other clients that want events */
    int		    number;	    /* index of this buffer into array */
    int		    side;	    /* always Mono */
    int		    clobber;	    /* Unclobbered, PartiallyClobbered, FullClobbered */
    PixmapPtr	    pPixmap;	    /* associated pixmap */
} MultibufferRec, *MultibufferPtr;

/*
 * per-window data
 */

typedef struct _Multibuffers {
    WindowPtr	pWindow;		/* associated window */
    int		numMultibuffer;		/* count of buffers */
    int		refcnt;			/* ref count for delete */
    int		displayedMultibuffer;	/* currently active buffer */
    int		updateAction;		/* Undefined, Background, Untouched, Copied */
    int		updateHint;		/* Frequent, Intermittent, Static */
    int		windowMode;		/* always Mono */

    TimeStamp	lastUpdate;		/* time of last update */

    unsigned short	width, height;	/* last known window size */
    short		x, y;		/* for static gravity */

    MultibufferPtr	buffers;        /* array of numMultibuffer buffers */
} MultibuffersRec;

/*
 * per-screen data
 */
typedef struct _MultibufferScreen {
    PositionWindowProcPtr PositionWindow;		/* pWin, x,y */
} MultibufferScreenRec, *MultibufferScreenPtr;

/*
 * per display-image-buffers request data.
 */

typedef struct _DisplayRequest {
    struct _DisplayRequest	*next;
    TimeStamp			activateTime;
    ClientPtr			pClient;
    XID				id;
} DisplayRequestRec, *DisplayRequestPtr;

#define DestroyWindowMask		(1L<<0)
#define PositionWindowMask		(1L<<1)
#define PostValidateTreeMask		(1L<<2)
#define ClipNotifyMask			(1L<<3)
#define WindowExposuresMask		(1L<<4)
#define CopyWindowMask			(1L<<5)
#define ClearToBackgroundMask		(1L<<6)
#define ChangeWindowAttributesMask	(1L<<7)    

extern int		MultibufferScreenIndex;
extern int		MultibufferWindowIndex;

extern RESTYPE		MultibufferDrawableResType;

extern void		MultibufferUpdate(	/* pMbuffer, time */
				MultibufferPtr /* pMultibuffer */,
				CARD32 /* time */
				);
extern void		MultibufferExpose(	/* pMbuffer, pRegion */
				MultibufferPtr /* pMultibuffer */,
				RegionPtr /* pRegion */
				);
extern void		MultibufferClobber(	/* pMbuffer */
				MultibufferPtr /* pMultibuffer */
				);

typedef struct _mbufWindow	*mbufWindowPtr;

/*
 * per-buffer data
 */

#define MB_DISPLAYED_BUFFER(pMBWindow) \
    ((pMBWindow)->buffers + (pMBWindow)->displayedMultibuffer)
 
typedef struct _mbufBuffer {
    mbufWindowPtr   pMBWindow;	    /* associated window data */
    Mask	    eventMask;	    /* client event mask */
    Mask	    otherEventMask; /* union of other clients' event masks */
    OtherClientsPtr otherClients;   /* other clients that want events */
    int		    number;	    /* index of this buffer into array */
    int		    side;	    /* stero side: always Mono */
    int		    clobber;	    /* clober state */
    DrawablePtr	    pDrawable;	    /* associated drawable */
} mbufBufferRec, *mbufBufferPtr;


/*
 * per-window data
 */

#define MB_WINDOW_PRIV(pWin) \
    ((mbufWindowPtr)((pWin)->devPrivates[MultibufferWindowIndex].ptr))

typedef struct _mbufWindow {
    WindowPtr	pWindow;		/* associated window */
    int		numMultibuffer;		/* count of buffers */
    mbufBufferPtr buffers;		/* array of (numMultibuffer) buffers */
    int		displayedMultibuffer;	/* currently active buffer */
    int		updateAction;		/* Undefined, Background,
					   Untouched, Copied */
    int		updateHint;		/* Frequent, Intermittent, Static */
    int		windowMode;		/* always Mono */
    TimeStamp	lastUpdate;		/* time of last update */
    short		x, y;		/* for static gravity */
    unsigned short	width, height;	/* last known window size */
    DevUnion		devPrivate;
} mbufWindowRec;


/*
 * per-screen data
 */

#define MB_SCREEN_PRIV(pScreen) \
    ((mbufScreenPtr)((pScreen)->devPrivates[MultibufferScreenIndex].ptr))

typedef struct _mbufScreen {
    long mbufWindowCount;		/* count of multibuffered windows */

    /* Wrap pScreen->DestroyWindow */
    DestroyWindowProcPtr DestroyWindow;
    long funcsWrapped;			/* flags which functions are wrapped */

    /* Initialized by device-dependent section */
    int  nInfo;				/* number of buffer info rec's */
    xMbufBufferInfo *pInfo;		/* buffer info (for Normal buffers) */

    int  (* CreateImageBuffers)(
		WindowPtr		/* pWin */,
		int			/* nbuf */,
		XID *			/* ids */,
		int			/* action */,
		int			/* hint */
    		);
    void (* DestroyImageBuffers)(
		WindowPtr		/* pWin */
    		);
    void (* DisplayImageBuffers)(
		ScreenPtr		/* pScreen */,
		mbufBufferPtr *		/* ppMBBuffer */,
		mbufWindowPtr *		/* ppMBWindow */,
		int			/* nbuf */
    		);
    void (* ClearImageBufferArea)(
		mbufBufferPtr		/* pMBBuffer */,
		short			/* x */,
		short			/* y */,
		unsigned short		/* width */,
		unsigned short		/* height */,
		Bool			/* exposures */
    		);
    Bool (* ChangeMBufferAttributes)(	/* pMBWindow, vmask */ 
    		/* FIXME */
    		);
    Bool (* ChangeBufferAttributes)(	/* pMBBuffer, vmask */
    		/* FIXME */
    		);
    void (* DeleteBufferDrawable)(
		DrawablePtr		/* pDrawable */
    		);
    void (* WrapScreenFuncs)(
		ScreenPtr		/* pScreen */
    		);
    void (* ResetProc)(
		ScreenPtr		/* pScreen */
    		);
    DevUnion	devPrivate;
} mbufScreenRec, *mbufScreenPtr;


/* Privates to mbufScreenRec */

#ifdef _MULTIBUF_PIXMAP_
#define MB_SCREEN_PRIV_PIXMAP(pScreen) \
    ((mbufPixmapPrivPtr) MB_SCREEN_PRIV((pScreen))->devPrivate.ptr)

typedef struct _mbufPixmapPriv
{
    /* Pointers to wrapped functions */
    PositionWindowProcPtr PositionWindow;		/* pWin, x,y */
    long funcsWrapped;			/* flags which functions are wrapped */
} mbufPixmapPrivRec, *mbufPixmapPrivPtr;
#endif /* _MULTIBUF_PIXMAP_ */


#ifdef _MULTIBUF_BUFFER_

extern int frameWindowPrivateIndex;

#define MB_SCREEN_PRIV_BUFFER(pScreen) \
    ((mbufBufferPrivPtr) MB_SCREEN_PRIV((pScreen))->devPrivate.ptr)

typedef struct _mbufBufferPriv
{
    DevUnion	*frameBuffer;	/* Array of screen framebuffers */
    DevUnion	selectPlane;	/* Plane(s) that select displayed buffer */

    /* 
     * Note: subtractRgn and unionRgn may overlap. subtractRgn is a union
     * of all the old clipLists of the windows that are displaying
     * the backbuffer. unionRgn is the union of all the new clipLists
     * of the same windows.
     */

    RegionRec	backBuffer;	/* Area of screen displaying back buffer */
    RegionRec   subtractRgn;	/* Regions lost to backBuffer   */
    RegionRec   unionRgn;	/* Regions gained by backBuffer */
    Bool	rgnChanged;	/* TRUE if "backBuffer" needs to be updated */

    void (* CopyBufferBits)();	/* pMBWindow, srcBufferNum, dstBufferNum */
    void (* DrawSelectPlane)();	/* pScreen, selectPlane, pRegion, bufferNum */

    /* Pointers to wrapped functions */
    PostValidateTreeProcPtr	PostValidateTree; /* pParent, pChild, kind */
    ClipNotifyProcPtr		ClipNotify;       /* pWin, dx, dy */
    WindowExposuresProcPtr	WindowExposures;  /* pWin, pRegion */
    CopyWindowProcPtr		CopyWindow;       /* pWin, oldPt, pOldRegion */
    ClearToBackgroundProcPtr	ClearToBackground; /* pWin, x,y,w,h, sendExpose */
    ChangeWindowAttributesProcPtr ChangeWindowAttributes; /* pWin, vmask */
    long funcsWrapped;			/* flags which functions are wrapped */
    unsigned  inClearToBackground:1;	/* used by WindowExposure */
} mbufBufferPrivRec, *mbufBufferPrivPtr;
#endif /* _MULTIBUF_BUFFER_ */

#endif /* _MULTIBUF_SERVER_ */
#endif /* _MULTIBUFST_H_ */
