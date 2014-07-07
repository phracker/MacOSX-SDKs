/* $Xorg: XKBgeom.h,v 1.3 2000/08/18 04:05:45 coskrey Exp $ */
/************************************************************
Copyright (c) 1993 by Silicon Graphics Computer Systems, Inc.

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
/* $XFree86: xc/include/extensions/XKBgeom.h,v 3.9 2002/09/18 17:11:40 tsi Exp $ */

#ifndef _XKBGEOM_H_
#define	_XKBGEOM_H_

#include <X11/extensions/XKBstr.h>

#ifdef XKB_IN_SERVER
#define XkbAddGeomKeyAlias 		SrvXkbAddGeomKeyAlias
#define XkbAddGeomColor 		SrvXkbAddGeomColor
#define XkbAddGeomDoodad		SrvXkbAddGeomDoodad
#define XkbAddGeomKey			SrvXkbAddGeomKey
#define XkbAddGeomOutline		SrvXkbAddGeomOutline
#define XkbAddGeomOverlay		SrvXkbAddGeomOverlay
#define XkbAddGeomOverlayRow		SrvXkbAddGeomOverlayRow
#define	XkbAddGeomOverlayKey		SrvXkbAddGeomOverlayKey
#define XkbAddGeomProperty		SrvXkbAddGeomProperty
#define XkbAddGeomRow			SrvXkbAddGeomRow
#define XkbAddGeomSection		SrvXkbAddGeomSection
#define XkbAddGeomShape			SrvXkbAddGeomShape
#define XkbAllocGeomKeyAliases		SrvXkbAllocGeomKeyAliases
#define XkbAllocGeomColors		SrvXkbAllocGeomColors
#define XkbAllocGeomDoodads		SrvXkbAllocGeomDoodads
#define XkbAllocGeomKeys		SrvXkbAllocGeomKeys
#define XkbAllocGeomOutlines		SrvXkbAllocGeomOutlines
#define XkbAllocGeomPoints		SrvXkbAllocGeomPoints
#define XkbAllocGeomProps		SrvXkbAllocGeomProps
#define XkbAllocGeomRows		SrvXkbAllocGeomRows
#define XkbAllocGeomSectionDoodads	SrvXkbAllocGeomSectionDoodads
#define XkbAllocGeomSections		SrvXkbAllocGeomSections
#define	XkbAllocGeomOverlays		SrvXkbAllocGeomOverlays
#define	XkbAllocGeomOverlayRows		SrvXkbAllocGeomOverlayRows
#define	XkbAllocGeomOverlayKeys		SrvXkbAllocGeomOverlayKeys
#define XkbAllocGeomShapes		SrvXkbAllocGeomShapes
#define XkbAllocGeometry		SrvXkbAllocGeometry
#define XkbFreeGeomKeyAliases		SrvXkbFreeGeomKeyAliases
#define XkbFreeGeomColors		SrvXkbFreeGeomColors
#define XkbFreeGeomDoodads		SrvXkbFreeGeomDoodads
#define XkbFreeGeomProperties		SrvXkbFreeGeomProperties
#define	XkbFreeGeomOverlayKeys		SrvXkbFreeGeomOverlayKeys
#define	XkbFreeGeomOverlayRows		SrvXkbFreeGeomOverlayRows
#define	XkbFreeGeomOverlays		SrvXkbFreeGeomOverlays
#define	XkbFreeGeomKeys			SrvXkbFreeGeomKeys
#define	XkbFreeGeomRows			SrvXkbFreeGeomRows
#define XkbFreeGeomSections		SrvXkbFreeGeomSections
#define	XkbFreeGeomPoints		SrvXkbFreeGeomPoints
#define	XkbFreeGeomOutlines		SrvXkbFreeGeomOutlines
#define XkbFreeGeomShapes		SrvXkbFreeGeomShapes
#define XkbFreeGeometry			SrvXkbFreeGeometry
#endif

typedef	struct _XkbProperty {
	char	*name;
	char	*value;
} XkbPropertyRec,*XkbPropertyPtr;

typedef struct _XkbColor {
	unsigned int 	pixel;
	char *		spec;
} XkbColorRec,*XkbColorPtr;

typedef	struct _XkbPoint {
	short	x;
	short	y;
} XkbPointRec, *XkbPointPtr;

typedef struct	_XkbBounds {
	short	x1,y1;
	short	x2,y2;
} XkbBoundsRec, *XkbBoundsPtr;
#define	XkbBoundsWidth(b)	(((b)->x2)-((b)->x1))
#define	XkbBoundsHeight(b)	(((b)->y2)-((b)->y1))

typedef struct _XkbOutline {
	unsigned short	num_points;
	unsigned short	sz_points;
	unsigned short	corner_radius;
	XkbPointPtr	points;
} XkbOutlineRec, *XkbOutlinePtr;

typedef struct _XkbShape {
	Atom	 	 name;
	unsigned short	 num_outlines;
	unsigned short	 sz_outlines;
	XkbOutlinePtr	 outlines;
	XkbOutlinePtr	 approx;
	XkbOutlinePtr	 primary;
	XkbBoundsRec	 bounds;
} XkbShapeRec, *XkbShapePtr;
#define	XkbOutlineIndex(s,o)	((int)((o)-&(s)->outlines[0]))

typedef struct _XkbShapeDoodad {
	Atom		 name;
	unsigned char	 type;
	unsigned char	 priority;
	short		 top;
	short		 left;
	short	 	 angle;
	unsigned short	 color_ndx;
	unsigned short	 shape_ndx;
} XkbShapeDoodadRec, *XkbShapeDoodadPtr;
#define	XkbShapeDoodadColor(g,d)	(&(g)->colors[(d)->color_ndx])
#define	XkbShapeDoodadShape(g,d)	(&(g)->shapes[(d)->shape_ndx])
#define	XkbSetShapeDoodadColor(g,d,c)	((d)->color_ndx= (c)-&(g)->colors[0])
#define	XkbSetShapeDoodadShape(g,d,s)	((d)->shape_ndx= (s)-&(g)->shapes[0])

typedef struct _XkbTextDoodad {
	Atom		 name;
	unsigned char	 type;
	unsigned char	 priority;
	short	 	 top;
	short	 	 left;
	short	 	 angle;
	short	 	 width;
	short		 height;
	unsigned short	 color_ndx;
	char *		 text;
	char *		 font;
} XkbTextDoodadRec, *XkbTextDoodadPtr;
#define	XkbTextDoodadColor(g,d)	(&(g)->colors[(d)->color_ndx])
#define	XkbSetTextDoodadColor(g,d,c)	((d)->color_ndx= (c)-&(g)->colors[0])

typedef struct _XkbIndicatorDoodad {
	Atom		 name;
	unsigned char	 type;
	unsigned char	 priority;
	short	 	 top;
	short	 	 left;
	short		 angle;
	unsigned short	 shape_ndx;
	unsigned short	 on_color_ndx;
	unsigned short	 off_color_ndx;
} XkbIndicatorDoodadRec, *XkbIndicatorDoodadPtr;
#define	XkbIndicatorDoodadShape(g,d)	(&(g)->shapes[(d)->shape_ndx])
#define	XkbIndicatorDoodadOnColor(g,d)	(&(g)->colors[(d)->on_color_ndx])
#define	XkbIndicatorDoodadOffColor(g,d)	(&(g)->colors[(d)->off_color_ndx])
#define	XkbSetIndicatorDoodadOnColor(g,d,c) \
				((d)->on_color_ndx= (c)-&(g)->colors[0])
#define	XkbSetIndicatorDoodadOffColor(g,d,c) \
				((d)->off_color_ndx= (c)-&(g)->colors[0])
#define	XkbSetIndicatorDoodadShape(g,d,s) \
				((d)->shape_ndx= (s)-&(g)->shapes[0])

typedef struct _XkbLogoDoodad {
	Atom		 name;
	unsigned char	 type;
	unsigned char	 priority;
	short		 top;
	short		 left;
	short	 	 angle;
	unsigned short	 color_ndx;
	unsigned short	 shape_ndx;
	char *		 logo_name;
} XkbLogoDoodadRec, *XkbLogoDoodadPtr;
#define	XkbLogoDoodadColor(g,d)		(&(g)->colors[(d)->color_ndx])
#define	XkbLogoDoodadShape(g,d)		(&(g)->shapes[(d)->shape_ndx])
#define	XkbSetLogoDoodadColor(g,d,c)	((d)->color_ndx= (c)-&(g)->colors[0])
#define	XkbSetLogoDoodadShape(g,d,s)	((d)->shape_ndx= (s)-&(g)->shapes[0])

typedef struct _XkbAnyDoodad {
	Atom		 name;
	unsigned char	 type;
	unsigned char	 priority;
	short	 	 top;
	short	 	 left;
	short		 angle;
} XkbAnyDoodadRec, *XkbAnyDoodadPtr;

typedef union _XkbDoodad {
	XkbAnyDoodadRec		any;
	XkbShapeDoodadRec	shape;
	XkbTextDoodadRec	text;
	XkbIndicatorDoodadRec	indicator;
	XkbLogoDoodadRec	logo;
} XkbDoodadRec, *XkbDoodadPtr;

#define	XkbUnknownDoodad	0
#define	XkbOutlineDoodad	1
#define	XkbSolidDoodad		2
#define	XkbTextDoodad		3
#define	XkbIndicatorDoodad	4
#define	XkbLogoDoodad		5

typedef struct _XkbKey {
	XkbKeyNameRec	 name;
	short		 gap;
	unsigned char	 shape_ndx;
	unsigned char	 color_ndx;
} XkbKeyRec, *XkbKeyPtr;
#define	XkbKeyShape(g,k)	(&(g)->shapes[(k)->shape_ndx])
#define	XkbKeyColor(g,k)	(&(g)->colors[(k)->color_ndx])
#define	XkbSetKeyShape(g,k,s)	((k)->shape_ndx= (s)-&(g)->shapes[0])
#define	XkbSetKeyColor(g,k,c)	((k)->color_ndx= (c)-&(g)->colors[0])

typedef struct _XkbRow {
	short	 	top;
	short	 	left;
	unsigned short	num_keys;
	unsigned short	sz_keys;
	int		vertical;
	XkbKeyPtr	keys;
	XkbBoundsRec	bounds;
} XkbRowRec, *XkbRowPtr;

typedef struct _XkbSection {
	Atom		 name;
	unsigned char	 priority;
	short	 	 top;
	short	 	 left;
	unsigned short	 width;
	unsigned short	 height;
	short	 	 angle;
	unsigned short	 num_rows;
	unsigned short	 num_doodads;
	unsigned short	 num_overlays;
	unsigned short	 sz_rows;
	unsigned short	 sz_doodads;
	unsigned short	 sz_overlays;
	XkbRowPtr	 rows;
	XkbDoodadPtr	 doodads;
	XkbBoundsRec	 bounds;
	struct _XkbOverlay *overlays;
} XkbSectionRec, *XkbSectionPtr;

typedef	struct _XkbOverlayKey {
	XkbKeyNameRec	over;
	XkbKeyNameRec	under;
} XkbOverlayKeyRec,*XkbOverlayKeyPtr;

typedef struct _XkbOverlayRow {
	unsigned short		row_under;
	unsigned short		num_keys;
	unsigned short		sz_keys;
	XkbOverlayKeyPtr	keys;
} XkbOverlayRowRec,*XkbOverlayRowPtr;

typedef struct _XkbOverlay {
	Atom			name;
	XkbSectionPtr		section_under;
	unsigned short		num_rows;
	unsigned short		sz_rows;
	XkbOverlayRowPtr	rows;
	XkbBoundsPtr		bounds;
} XkbOverlayRec,*XkbOverlayPtr;

typedef struct _XkbGeometry {
	Atom		 name;
	unsigned short	 width_mm;
	unsigned short	 height_mm;
	char *		 label_font;
	XkbColorPtr	 label_color;
	XkbColorPtr	 base_color;
	unsigned short	 sz_properties;
	unsigned short	 sz_colors;
	unsigned short	 sz_shapes;
	unsigned short   sz_sections;
	unsigned short	 sz_doodads;
	unsigned short	 sz_key_aliases;
	unsigned short	 num_properties;
	unsigned short	 num_colors;
	unsigned short	 num_shapes;
	unsigned short	 num_sections;
	unsigned short	 num_doodads;
	unsigned short	 num_key_aliases;
	XkbPropertyPtr	 properties;
	XkbColorPtr	 colors;
	XkbShapePtr	 shapes;
	XkbSectionPtr	 sections;
	XkbDoodadPtr	 doodads;
	XkbKeyAliasPtr	 key_aliases;
} XkbGeometryRec;
#define	XkbGeomColorIndex(g,c)	((int)((c)-&(g)->colors[0]))

#define	XkbGeomPropertiesMask	(1<<0)
#define	XkbGeomColorsMask	(1<<1)
#define	XkbGeomShapesMask	(1<<2)
#define	XkbGeomSectionsMask	(1<<3)
#define	XkbGeomDoodadsMask	(1<<4)
#define	XkbGeomKeyAliasesMask	(1<<5)
#define	XkbGeomAllMask		(0x3f)

typedef struct _XkbGeometrySizes {
	unsigned int	which;
	unsigned short	num_properties;
	unsigned short	num_colors;
	unsigned short	num_shapes;
	unsigned short	num_sections;
	unsigned short	num_doodads;
	unsigned short	num_key_aliases;
} XkbGeometrySizesRec,*XkbGeometrySizesPtr;

_XFUNCPROTOBEGIN

extern	XkbPropertyPtr
XkbAddGeomProperty(
#if NeedFunctionPrototypes
    XkbGeometryPtr	/* geom */,
    char *		/* name */,
    char *		/* value */
#endif
);

extern	XkbKeyAliasPtr
XkbAddGeomKeyAlias(
#if NeedFunctionPrototypes
    XkbGeometryPtr	/* geom */,
    char *		/* alias */,
    char *		/* real */
#endif
);

extern	XkbColorPtr
XkbAddGeomColor(
#if NeedFunctionPrototypes
    XkbGeometryPtr	/* geom */,
    char *		/* spec */,
    unsigned int	/* pixel */
#endif
);

extern	XkbOutlinePtr
XkbAddGeomOutline(
#if NeedFunctionPrototypes
    XkbShapePtr		/* shape */,
    int			/* sz_points */
#endif
);

extern XkbShapePtr
XkbAddGeomShape(
#if NeedFunctionPrototypes
    XkbGeometryPtr	/* geom */,
    Atom		/* name */,
    int			/* sz_outlines */
#endif
);

extern XkbKeyPtr
XkbAddGeomKey(
#if NeedFunctionPrototypes
    XkbRowPtr		/* row */
#endif
);

extern XkbRowPtr
XkbAddGeomRow(
#if NeedFunctionPrototypes
    XkbSectionPtr	/* section */,
    int			/* sz_keys */
#endif
);

extern XkbSectionPtr
XkbAddGeomSection(
#if NeedFunctionPrototypes
    XkbGeometryPtr	/* geom */,
    Atom		/* name */,
    int			/* sz_rows */,
    int			/* sz_doodads */,
    int			/* sz_overlays */
#endif
);

extern XkbOverlayPtr
XkbAddGeomOverlay(
#if NeedFunctionPrototypes
    XkbSectionPtr	/* section */,
    Atom		/* name */,
    int			/* sz_rows */
#endif
);

extern XkbOverlayRowPtr
XkbAddGeomOverlayRow(
#if NeedFunctionPrototypes
    XkbOverlayPtr	/* overlay */,
    int			/* row_under */,
    int			/* sz_keys */
#endif
);

extern XkbOverlayKeyPtr
XkbAddGeomOverlayKey(
#if NeedFunctionPrototypes
    XkbOverlayPtr	/* overlay */,
    XkbOverlayRowPtr	/* row */,
    char *		/* over */,
    char *		/* under */
#endif
);

extern XkbDoodadPtr
XkbAddGeomDoodad(
#if NeedFunctionPrototypes
    XkbGeometryPtr	/* geom */,
    XkbSectionPtr	/* section */,
    Atom		/* name */
#endif
);


extern void
XkbFreeGeomKeyAliases(
#if NeedFunctionPrototypes
    XkbGeometryPtr	/* geom */,
    int			/* first */,
    int			/* count */,
    Bool		/* freeAll */
#endif
);

extern void
XkbFreeGeomColors(
#if NeedFunctionPrototypes
    XkbGeometryPtr	/* geom */,
    int			/* first */,
    int			/* count */,
    Bool		/* freeAll */
#endif
);

extern void
XkbFreeGeomDoodads(
#if NeedFunctionPrototypes
    XkbDoodadPtr	/* doodads */,
    int			/* nDoodads */,
    Bool		/* freeAll */
#endif
);


extern void
XkbFreeGeomProperties(
#if NeedFunctionPrototypes
    XkbGeometryPtr	/* geom */,
    int			/* first */,
    int			/* count */,
    Bool		/* freeAll */
#endif
);

extern void
XkbFreeGeomOverlayKeys(
#if NeedFunctionPrototypes
    XkbOverlayRowPtr	/* row */,
    int			/* first */,
    int			/* count */,
    Bool		/* freeAll */
#endif
);

extern void
XkbFreeGeomOverlayRows(
#if NeedFunctionPrototypes
    XkbOverlayPtr	/* overlay */,
    int			/* first */,
    int			/* count */,
    Bool		/* freeAll */
#endif
);

extern void
XkbFreeGeomOverlays(
#if NeedFunctionPrototypes
    XkbSectionPtr	/* section */,
    int			/* first */,
    int			/* count */,
    Bool		/* freeAll */
#endif
);

extern void
XkbFreeGeomKeys(
#if NeedFunctionPrototypes
    XkbRowPtr		/* row */,
    int			/* first */,
    int			/* count */,
    Bool		/* freeAll */
#endif
);

extern void
XkbFreeGeomRows(
#if NeedFunctionPrototypes
    XkbSectionPtr	/* section */,
    int			/* first */,
    int			/* count */,
    Bool		/* freeAll */
#endif
);

extern void
XkbFreeGeomSections(
#if NeedFunctionPrototypes
    XkbGeometryPtr	/* geom */,
    int			/* first */,
    int			/* count */,
    Bool		/* freeAll */
#endif
);


extern void
XkbFreeGeomPoints(
#if NeedFunctionPrototypes
    XkbOutlinePtr	/* outline */,
    int			/* first */,
    int			/* count */,
    Bool		/* freeAll */
#endif
);

extern void
XkbFreeGeomOutlines(
#if NeedFunctionPrototypes
    XkbShapePtr		/* shape */,
    int			/* first */,
    int			/* count */,
    Bool		/* freeAll */
#endif
);

extern void
XkbFreeGeomShapes(
#if NeedFunctionPrototypes
    XkbGeometryPtr	/* geom */,
    int			/* first */,
    int			/* count */,
    Bool		/* freeAll */
#endif
);

extern void
XkbFreeGeometry(
#if NeedFunctionPrototypes
    XkbGeometryPtr	/* geom */,
    unsigned int	/* which */,
    Bool		/* freeMap */
#endif
);

extern Status
XkbAllocGeomProps(
#if NeedFunctionPrototypes
    XkbGeometryPtr	/* geom */,
    int			/* nProps */
#endif
);

extern Status
XkbAllocGeomKeyAliases(
#if NeedFunctionPrototypes
    XkbGeometryPtr	/* geom */,
    int			/* nAliases */
#endif
);

extern Status
XkbAllocGeomColors(
#if NeedFunctionPrototypes
    XkbGeometryPtr	/* geom */,
    int			/* nColors */
#endif
);

extern Status
XkbAllocGeomShapes(
#if NeedFunctionPrototypes
    XkbGeometryPtr	/* geom */,
    int			/* nShapes */
#endif
);

extern Status
XkbAllocGeomSections(
#if NeedFunctionPrototypes
    XkbGeometryPtr	/* geom */,
    int			/* nSections */
#endif
);

extern Status
XkbAllocGeomOverlays(
#if NeedFunctionPrototypes
    XkbSectionPtr	/* section */,
    int			/* num_needed */
#endif
);

extern Status
XkbAllocGeomOverlayRows(
#if NeedFunctionPrototypes
    XkbOverlayPtr	/* overlay */,
    int			/* num_needed */
#endif
);

extern Status
XkbAllocGeomOverlayKeys(
#if NeedFunctionPrototypes
    XkbOverlayRowPtr	/* row */,
    int			/* num_needed */
#endif
);

extern Status
XkbAllocGeomDoodads(
#if NeedFunctionPrototypes
    XkbGeometryPtr	/* geom */,
    int			/* nDoodads */
#endif
);

extern Status
XkbAllocGeomSectionDoodads(
#if NeedFunctionPrototypes
    XkbSectionPtr	/* section */,
    int			/* nDoodads */
#endif
);

extern Status
XkbAllocGeomOutlines(
#if NeedFunctionPrototypes
    XkbShapePtr		/* shape */,
    int			/* nOL */
#endif
);

extern Status
XkbAllocGeomRows(
#if NeedFunctionPrototypes
    XkbSectionPtr	/* section */,
    int			/* nRows */
#endif
);

extern Status
XkbAllocGeomPoints(
#if NeedFunctionPrototypes
    XkbOutlinePtr	/* ol */,
    int			/* nPts */
#endif
);

extern Status
XkbAllocGeomKeys(
#if NeedFunctionPrototypes
    XkbRowPtr		/* row */,
    int			/* nKeys */
#endif
);

extern	Status
XkbAllocGeometry(
#if NeedFunctionPrototypes
	XkbDescPtr		/* xkb */,
	XkbGeometrySizesPtr	/* sizes */
#endif
);

extern	Status
XkbSetGeometry(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	unsigned		/* deviceSpec */,
	XkbGeometryPtr		/* geom */
#endif
);

extern	Bool
XkbComputeShapeTop(
#if NeedFunctionPrototypes
	XkbShapePtr		/* shape */,
	XkbBoundsPtr		/* bounds */
#endif
);

extern	Bool
XkbComputeShapeBounds(
#if NeedFunctionPrototypes
	XkbShapePtr		/* shape */
#endif
);

extern	Bool
XkbComputeRowBounds(
#if NeedFunctionPrototypes
	XkbGeometryPtr		/* geom */,
	XkbSectionPtr		/* section */,
	XkbRowPtr		/* row */
#endif
);

extern	Bool
XkbComputeSectionBounds(
#if NeedFunctionPrototypes
	XkbGeometryPtr		/* geom */,
	XkbSectionPtr		/* section */
#endif
);

extern	char *
XkbFindOverlayForKey(
#if NeedFunctionPrototypes
	XkbGeometryPtr		/* geom */,
	XkbSectionPtr		/* wanted */,
	char *			/* under */
#endif
);

extern	Status
XkbGetGeometry(
#if NeedFunctionPrototypes
    Display *			/* dpy */,
    XkbDescPtr			/* xkb */
#endif
);

extern	Status
XkbGetNamedGeometry(
#if NeedFunctionPrototypes
    Display *			/* dpy */,
    XkbDescPtr			/* xkb */,
    Atom			/* name */
#endif
);

_XFUNCPROTOEND

#endif /* _XKBSTR_H_ */
