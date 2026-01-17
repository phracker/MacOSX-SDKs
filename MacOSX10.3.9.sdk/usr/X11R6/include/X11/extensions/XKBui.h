#ifndef XKBUI_H
#define	XKBUI_H 1
/* $XConsortium: XKBui.h /main/2 1995/12/07 21:18:19 kaleb $ */
/************************************************************
 Copyright (c) 1996 by Silicon Graphics Computer Systems, Inc.

 Permission to use, copy, modify, and distribute this
 software and its documentation for any purpose and without
 fee is hereby granted, provided that the above copyright
 notice appear in all copies and that both that copyright
 notice and this permission notice appear in supporting
 documentation, and that the name of Silicon Graphics not be 
 used in advertising or publicity pertaining to distribution 
 of the software without specific prior written permission.
 Silicon Graphics makes no representation about the suitability 
 of this software for any purpose. It is provided "as is"
 without any express or implied warranty.
 
 SILICON GRAPHICS DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS 
 SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY 
 AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL SILICON
 GRAPHICS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL 
 DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, 
 DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE 
 OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION  WITH
 THE USE OR PERFORMANCE OF THIS SOFTWARE.

 ********************************************************/

#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <X11/extensions/XKBgeom.h>

typedef struct _XkbUI_View	*XkbUI_ViewPtr;

typedef struct _XkbUI_ViewOpts {
	unsigned int	present;
	unsigned int	fg;
	unsigned int	bg;
	unsigned int	label_mode;
	unsigned int	color_mode;
	XRectangle	viewport;
	unsigned int	margin_width;
	unsigned int	margin_height;
	Colormap	cmap;
} XkbUI_ViewOptsRec,*XkbUI_ViewOptsPtr;

	/*
	 * legal values for present field of a view options
	 */
#define	XkbUI_BackgroundMask	(1<<0)
#define	XkbUI_ForegroundMask	(1<<1)
#define	XkbUI_LabelModeMask	(1<<2)
#define	XkbUI_ColorModeMask	(1<<3)
#define	XkbUI_WidthMask		(1<<4)
#define	XkbUI_HeightMask	(1<<5)
#define	XkbUI_XOffsetMask	(1<<6)
#define	XkbUI_YOffsetMask	(1<<7)
#define	XkbUI_ColormapMask	(1<<8)
#define	XkbUI_MarginWidthMask	(1<<9)
#define	XkbUI_MarginHeightMask	(1<<10)

#define	XkbUI_SizeMask		(XkbUI_WidthMask|XkbUI_HeightMask)
#define	XkbUI_OffsetMask	(XkbUI_XOffsetMask|XkbUI_YOffsetMask)
#define	XkbUI_MarginMask	(XkbUI_MarginWidthMask|XkbUI_MarginHeightMask)
#define	XkbUI_AllViewOptsMask	(0x7ff)

	/*
	 * legal values for the label_mode of a view options
	 */
#define	XkbUI_NoLabels		0
#define	XkbUI_KeyCodes		1
#define	XkbUI_KeyNames		2
#define	XkbUI_StateSyms		3
#define	XkbUI_MultiSyms		4

typedef struct _XkbUI_Select {
	unsigned		type;
	XkbSectionPtr		section;
	XkbKeyPtr		key;
	XkbDoodadPtr		doodad;
} XkbUI_SelectRec,*XkbUI_SelectPtr;

	/*
	 * legal values for 'type' field of a selection report
	 */

#define	XkbUI_Keys		0
#define	XkbUI_Indicators	1
#define	XkbUI_TextLabels	2
#define	XkbUI_SolidShapes	3
#define	XkbUI_Outlines		4
#define	XkbUI_Logos		5
#define	XkbUI_Sections		6

	/*
	 * legal values for 'which' field of a select call
	 */
#define	XkbUI_KeysMask		(1<<0)
#define	XkbUI_IndicatorsMask	(1<<1)
#define	XkbUI_TextLabelsMask	(1<<2)
#define	XkbUI_SolidShapesMask	(1<<3)
#define	XkbUI_OutlinesMask	(1<<4)
#define	XkbUI_LogosMask		(1<<5)
#define	XkbUI_SectionsMask	(1<<6)

	/*
	 * legal values for key appearance flag
	 */
#define	XkbUI_KeyDown		(1<<0)
#define	XkbUI_Highlight		(1<<1)

_XFUNCPROTOBEGIN

extern	XkbUI_ViewPtr XkbUI_SimpleInit(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	Window			/* win */,
	int			/* width */,
	int			/* height */
#endif
);

extern	XkbUI_ViewPtr XkbUI_Init(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	Window			/* win */,
	int			/* width */,
	int			/* height */,
	XkbDescPtr		/* xkb */,
	XkbUI_ViewOptsPtr	/* view */
#endif
);

extern Status XkbUI_SetViewOpts(
#if NeedFunctionPrototypes
	XkbUI_ViewPtr		/* view */,
	XkbUI_ViewOptsPtr	/* opts */
#endif
);

extern Status XbUI_GetViewOpts(
#if NeedFunctionPrototypes
	XkbUI_ViewPtr		/* view */,
	XkbUI_ViewOptsPtr	/* opts_rtrn */
#endif
);

extern	Status XkbUI_SetCanvasSize(
#if NeedFunctionPrototypes
	XkbUI_ViewPtr		/* view */,
	int			/* width */,
	int			/* height */
#endif
);

extern	Status XkbUI_GetCanvasSize(
#if NeedFunctionPrototypes
	XkbUI_ViewPtr		/* view */,
	int *			/* width_rtrn */,
	int *			/* height_rtrn */
#endif
);

extern Bool XkbUI_SetKeyAppearance(
#if NeedFunctionPrototypes
	XkbUI_ViewPtr		/* view */,
	KeyCode			/* kc */,
	unsigned		/* flags */
#endif
);

extern Bool XkbUI_SetKeyAppearanceByName(
#if NeedFunctionPrototypes
	XkbUI_ViewPtr		/* view */,
	XkbKeyNamePtr		/* name */,
	unsigned		/* flags */
#endif
);

extern Bool XkbUI_ResetKeyAppearance(
#if NeedFunctionPrototypes
	XkbUI_ViewPtr		/* view */,
	unsigned int		/* mask */,
	unsigned int		/* values */
#endif
);

extern Bool XkbUI_DrawRegion(
#if NeedFunctionPrototypes
	XkbUI_ViewPtr		/* view */,
	XRectangle *		/* viewport */
#endif
);

extern Bool XkbUI_DrawChanged(
#if NeedFunctionPrototypes
	XkbUI_ViewPtr		/* view */,
	XRectangle *		/* viewport */,
	XkbChangesPtr		/* changes */,
	int			/* num_keys */,
	XkbKeyNamePtr		/* keys */
#endif
);

extern Bool XkbUI_Select(
#if NeedFunctionPrototypes
	XkbUI_ViewPtr		/* view */,
	XPoint *		/* coord */,
	unsigned int		/* which */,
	XkbSectionPtr		/* section */
#endif
);

_XFUNCPROTOEND

#endif /* XKBUI_H */
