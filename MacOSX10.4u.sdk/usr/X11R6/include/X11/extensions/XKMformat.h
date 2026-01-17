/* $Xorg: XKMformat.h,v 1.3 2000/08/17 19:46:43 cpqbld Exp $ */
/************************************************************
 Copyright (c) 1994 by Silicon Graphics Computer Systems, Inc.

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
/* $XFree86: xc/lib/xkbfile/XKMformat.h,v 1.2 2001/08/01 00:44:44 tsi Exp $ */

#ifndef _XKMFORMAT_H_
#define	_XKMFORMAT_H_ 1

#include <X11/extensions/XKB.h>
#include <X11/extensions/XKBproto.h>
#include <X11/extensions/XKM.h>

typedef	struct _xkmFileInfo {
	CARD8		type;
	CARD8		min_kc;
	CARD8		max_kc;
	CARD8		num_toc;
	CARD16		present B16;
	CARD16		pad B16;
} xkmFileInfo;
#define	sz_xkmFileInfo	8

typedef	struct _xkmSectionInfo {
	CARD16		type B16;
	CARD16		format B16;
	CARD16		size B16;
	CARD16		offset B16;
} xkmSectionInfo;
#define	sz_xkmSectionInfo	8

typedef struct _xkmKeyTypeDesc {
	CARD8		realMods;
	CARD8		numLevels;
	CARD16		virtualMods B16;
	CARD8		nMapEntries;
	CARD8		nLevelNames;
	CARD8		preserve;
	CARD8		pad;
} xkmKeyTypeDesc;
#define	sz_xkmKeyTypeDesc	8

typedef struct _xkmKTMapEntryDesc {
	CARD8		level;
	CARD8		realMods;
	CARD16		virtualMods B16;
} xkmKTMapEntryDesc;
#define	sz_xkmKTMapEntryDesc	4

typedef struct _xkmModsDesc {
	CARD8		realMods;
	CARD8		pad;
	CARD16		virtualMods B16;
} xkmModsDesc;
#define	sz_xkmModsDesc	4

typedef struct _xkmVModMapDesc {
	CARD8		key;
	CARD8		pad;
	CARD16		vmods B16;
} xkmVModMapDesc;
#define	sz_xkmVModMapDesc	4

typedef struct _xkmSymInterpretDesc {
	CARD32		sym B32;
	CARD8		mods;
	CARD8		match;
	CARD8		virtualMod;
	CARD8		flags;
	CARD8		actionType;
	CARD8		actionData[7];
} xkmSymInterpretDesc;
#define	sz_xkmSymInterpretDesc	16

typedef struct _xkmBehaviorDesc {
	CARD8		type;
	CARD8		data;
	CARD16		pad B16;
} xkmBehaviorDesc;
#define	sz_xkmBehaviorDesc	4

typedef struct _xkmActionDesc {
	CARD8		type;
	CARD8		data[7];
} xkmActionDesc;
#define	sz_xkmActionDesc	8

#define	XkmKeyHasTypes		(0x0f)
#define	XkmKeyHasGroup1Type	(1<<0)
#define	XkmKeyHasGroup2Type	(1<<1)
#define	XkmKeyHasGroup3Type	(1<<2)
#define	XkmKeyHasGroup4Type	(1<<3)
#define	XkmKeyHasActions	(1<<4)
#define	XkmKeyHasBehavior	(1<<5)
#define	XkmRepeatingKey		(1<<6)
#define	XkmNonRepeatingKey	(1<<7)

typedef struct _xkmKeySymMapDesc {
	CARD8		width;
	CARD8		num_groups;
	CARD8		modifier_map;
	CARD8		flags;
} xkmKeySymMapDesc;
#define sz_xkmKeySymMapDesc	4

typedef struct _xkmIndicatorMapDesc {
	CARD8		indicator;
	CARD8		flags;
	CARD8		which_mods;
	CARD8		real_mods;
	CARD16		vmods B16;
	CARD8		which_groups;
	CARD8		groups;
	CARD32		ctrls B32;
} xkmIndicatorMapDesc;
#define sz_xkmIndicatorMapDesc	12

typedef struct _xkmGeometryDesc {
	CARD16		width_mm B16;
	CARD16		height_mm B16;
	CARD8		base_color_ndx;
	CARD8		label_color_ndx;
	CARD16		num_properties B16;
	CARD16		num_colors B16;
	CARD16		num_shapes B16;
	CARD16		num_sections B16;
	CARD16		num_doodads B16;
	CARD16		num_key_aliases B16;
	CARD16		pad1 B16;
} xkmGeometryDesc;
#define	sz_xkmGeometryDesc	20

typedef struct _xkmPointDesc {
	INT16		x B16;
	INT16		y B16;
} xkmPointDesc;
#define	sz_xkmPointDesc		4

typedef	struct _xkmOutlineDesc {
	CARD8		num_points;
	CARD8		corner_radius;
	CARD16		pad B16;
} xkmOutlineDesc;
#define	sz_xkmOutlineDesc	4

typedef struct _xkmShapeDesc {
	CARD8		num_outlines;
	CARD8		primary_ndx;
	CARD8		approx_ndx;
	CARD8		pad;
} xkmShapeDesc;	
#define	sz_xkmShapeDesc	4

typedef struct _xkmSectionDesc {
	INT16		top B16;
	INT16		left B16;
	CARD16		width B16;
	CARD16		height B16;
	INT16		angle B16;
	CARD8		priority;
	CARD8		num_rows;
	CARD8		num_doodads;
	CARD8		num_overlays;
	CARD16		pad2 B16;
} xkmSectionDesc;
#define	sz_xkmSectionDesc	16

typedef struct _xkmRowDesc {
	INT16		top B16;
	INT16		left B16;
	CARD8		num_keys;
	BOOL		vertical;
	CARD16		pad B16;
} xkmRowDesc;
#define	sz_xkmRowDesc		8

typedef struct _xkmKeyDesc {
	CARD8		name[XkbKeyNameLength];
	INT16		gap B16;
	CARD8		shape_ndx;
	CARD8		color_ndx;
} xkmKeyDesc;
#define	sz_xkmKeyDesc		8

typedef struct _xkmOverlayDesc {
	CARD8		num_rows;
	CARD8		pad1;
	CARD16		pad2 B16;
} xkmOverlayDesc;
#define	sz_xkmOverlayDesc	4

typedef struct _xkmOverlayRowDesc {
	CARD8		row_under;
	CARD8		num_keys;
	CARD16		pad B16;
} xkmOverlayRowDesc;
#define	sz_xkmOverlayRowDesc	4

typedef struct _xkmOverlayKeyDesc {
	char		over[XkbKeyNameLength];
	char		under[XkbKeyNameLength];
} xkmOverlayKeyDesc;
#define sz_xkmOverlayKeyDesc	8

typedef struct _xkmShapeDoodadDesc {
	CARD8		type;
	CARD8		priority;
	INT16		top B16;
	INT16		left B16;
	INT16		angle B16;
	CARD8		color_ndx;
	CARD8		shape_ndx;
	CARD16		pad B16;
	CARD32		pad1 B32;
} xkmShapeDoodadDesc;
#define	sz_xkmShapeDoodadDesc	16

typedef struct _xkmTextDoodadDesc {
	CARD8	 	type;
	CARD8	 	priority;
	INT16	 	top B16;
	INT16	 	left B16;
	INT16	 	angle B16;
	CARD16		width B16;
	CARD16		height B16;
	CARD8	 	color_ndx;
	CARD8		pad1;
	CARD16		pad2 B16;
} xkmTextDoodadDesc;
#define	sz_xkmTextDoodadDesc	16

typedef struct _xkmIndicatorDoodadDesc {
	CARD8		type;
	CARD8		priority;
	INT16		top B16;
	INT16		left B16;
	CARD8		shape_ndx;
	CARD8		on_color_ndx;
	CARD8		off_color_ndx;
	CARD8		pad1;
	CARD16		pad2 B16;
	CARD32		pad3 B32;
} xkmIndicatorDoodadDesc;
#define	sz_xkmIndicatorDoodadDesc	16

typedef struct _xkmLogoDoodadDesc {
	CARD8		type;
	CARD8		priority;
	INT16		top B16;
	INT16		left B16;
	INT16		angle B16;
	CARD8		color_ndx;
	CARD8		shape_ndx;
	CARD16		pad B16;
	CARD32		pad1 B32;
} xkmLogoDoodadDesc;
#define	sz_xkmLogoDoodadDesc	16

typedef struct _xkmAnyDoodadDesc {
	CARD8		type;
	CARD8		priority;
	INT16		top B16;
	INT16		left B16;
	CARD16		pad1 B16;
	CARD32		pad2 B32;
	CARD32		pad3 B32;
} xkmAnyDoodadDesc;
#define	sz_xkmAnyDoodadDesc		16

typedef union _xkmDoodadDesc {
	xkmAnyDoodadDesc	any;
	xkmShapeDoodadDesc	shape;
	xkmTextDoodadDesc	text;
	xkmIndicatorDoodadDesc	indicator;
	xkmLogoDoodadDesc	logo;
} xkmDoodadDesc;
#define	sz_xkmDoodadDesc		16

#endif /* _XKMFORMAT_H_ */
