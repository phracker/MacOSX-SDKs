#ifndef _XKBFILE_H_
#define	_XKBFILE_H_ 1

/* $Xorg: XKBfile.h,v 1.3 2000/08/17 19:46:43 cpqbld Exp $ */
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

/***====================================================================***/

#define	XkbXKMFile	0
#define	XkbCFile	1
#define	XkbXKBFile	2
#define	XkbMessage	3

#define	XkbMapDefined		(1<<0)
#define	XkbStateDefined		(1<<1)

typedef struct _XkbFileInfo {
    unsigned		type;
    unsigned		defined;
    XkbDescPtr	 	xkb;
} XkbFileInfo,*XkbFileInfoPtr;

typedef void	(*XkbFileAddOnFunc)(
#if NeedFunctionPrototypes
    FILE *		/* file */,
    XkbFileInfo *	/* result */,
    Bool		/* topLevel */,
    Bool		/* showImplicit */,
    int			/* fileSection */,
    void *		/* priv */
#endif
);

/***====================================================================***/

#define	_XkbSuccess			0
#define	_XkbErrMissingNames		1
#define	_XkbErrMissingTypes		2
#define	_XkbErrMissingReqTypes		3
#define	_XkbErrMissingSymbols		4
#define	_XkbErrMissingVMods		5
#define	_XkbErrMissingIndicators	6
#define	_XkbErrMissingCompatMap		7
#define	_XkbErrMissingSymInterps	8
#define	_XkbErrMissingGeometry		9
#define	_XkbErrIllegalDoodad		10
#define	_XkbErrIllegalTOCType		11
#define	_XkbErrIllegalContents		12
#define	_XkbErrEmptyFile		13
#define	_XkbErrFileNotFound		14
#define	_XkbErrFileCannotOpen		15
#define	_XkbErrBadValue			16
#define	_XkbErrBadMatch			17
#define	_XkbErrBadTypeName		18
#define	_XkbErrBadTypeWidth		19
#define	_XkbErrBadFileType		20
#define	_XkbErrBadFileVersion		21
#define	_XkbErrBadFileFormat		22
#define	_XkbErrBadAlloc			23
#define	_XkbErrBadLength		24
#define	_XkbErrXReqFailure		25
#define	_XkbErrBadImplementation	26

extern char *		_XkbErrMessages[];
extern unsigned		_XkbErrCode;
extern char *		_XkbErrLocation;
extern unsigned		_XkbErrData;

/***====================================================================***/

_XFUNCPROTOBEGIN

extern	char *	XkbIndentText(
#if NeedFunctionPrototypes
    unsigned	/* size */
#endif
);

extern	char *	XkbAtomText(
#if NeedFunctionPrototypes
    Display *	/* dpy */,
    Atom 	/* atm */,
    unsigned	/* format */
#endif
);

extern char *	XkbKeysymText(
#if NeedFunctionPrototypes
    KeySym	/* sym */,
    unsigned	/* format */
#endif
);

extern char *	XkbStringText(
#if NeedFunctionPrototypes
    char *	/* str */,
    unsigned	/* format */
#endif
);

extern char *	XkbKeyNameText(
#if NeedFunctionPrototypes
    char *	/* name */,
    unsigned	/* format */
#endif
);

extern char *
XkbModIndexText(
#if NeedFunctionPrototypes
    unsigned	/* ndx */,
    unsigned	/* format */
#endif
);

extern char *
XkbModMaskText(
#if NeedFunctionPrototypes
    unsigned	/* mask */,
    unsigned	/* format */
#endif
);

extern char *	XkbVModIndexText(
#if NeedFunctionPrototypes
    Display *	/* dpy */,
    XkbDescPtr	/* xkb */,
    unsigned	/* ndx */,
    unsigned	/* format */
#endif
);

extern	char *	XkbVModMaskText(
#if NeedFunctionPrototypes
    Display *	/* dpy */,
    XkbDescPtr	/* xkb */,
    unsigned	/* modMask */,
    unsigned	/* mask */,
    unsigned	/* format */
#endif
);

extern char *	XkbConfigText(
#if NeedFunctionPrototypes
    unsigned 	/* config */,
    unsigned 	/* format */
#endif
);

extern char *	XkbSIMatchText(
#if NeedFunctionPrototypes
    unsigned	/* type */,
    unsigned	/* format */
#endif
);

extern char *	XkbIMWhichStateMaskText(
#if NeedFunctionPrototypes
    unsigned	/* use_which */,
    unsigned	/* format */
#endif
);

extern char *	XkbAccessXDetailText(
#if NeedFunctionPrototypes
    unsigned	/* state */,
    unsigned	/* format */
#endif
);

extern char *	XkbNKNDetailMaskText(
#if NeedFunctionPrototypes
    unsigned	/* detail */,
    unsigned	/* format */
#endif
);

extern char *	XkbControlsMaskText(
#if NeedFunctionPrototypes
    unsigned	/* ctrls */,
    unsigned	/* format */
#endif
);

extern char *	XkbGeomFPText(
#if NeedFunctionPrototypes
    int		/* val */,
    unsigned 	/* format */
#endif
);

extern char *	XkbDoodadTypeText(
#if NeedFunctionPrototypes
    unsigned	/* type */,
    unsigned	/* format */
#endif
);

extern char *	XkbActionTypeText(
#if NeedFunctionPrototypes
    unsigned	/* type */,
    unsigned	/* format */
#endif
);

extern char *	XkbActionText(
#if NeedFunctionPrototypes
    Display *	/* dpy */,
    XkbDescPtr	/* xkb */,
    XkbAction *	/* action */,
    unsigned	/* format */
#endif
);

extern char *	XkbBehaviorText(
#if NeedFunctionPrototypes
    XkbDescPtr 		/* xkb */,
    XkbBehavior *	/* behavior */,
    unsigned		/* format */
#endif
);

/***====================================================================***/

#define	_XkbKSLower	(1<<0)
#define	_XkbKSUpper	(1<<1)

#define	XkbKSIsLower(k)		(_XkbKSCheckCase(k)&_XkbKSLower)
#define	XkbKSIsUpper(k)		(_XkbKSCheckCase(k)&_XkbKSUpper)
#define XkbKSIsKeypad(k)	(((k)>=XK_KP_Space)&&((k)<=XK_KP_Equal))
#define	XkbKSIsDeadKey(k)	\
		(((k)>=XK_dead_grave)&&((k)<=XK_dead_semivoiced_sound))

extern	unsigned _XkbKSCheckCase(
#if NeedFunctionPrototypes
   KeySym	/* sym */
#endif
);

extern	int	 XkbFindKeycodeByName(
#if NeedFunctionPrototypes
    XkbDescPtr	/* xkb */,
    char *	/* name */,
    Bool	/* use_aliases */
#endif
);

extern	Bool	XkbLookupGroupAndLevel(
#if NeedFunctionPrototypes
    XkbDescPtr	/* xkb */,
    int		/* key */,
    int	*	/* mods_inout */,
    int *	/* grp_inout */,
    int	*	/* lvl_rtrn */
#endif
);

/***====================================================================***/

#ifndef XKB_IN_SERVER

extern Bool	XkbLookupCanonicalRGBColor(
#if NeedFunctionPrototypes
    char *	/* def */,
    XColor *	/* color */
#endif
);

#endif

/***====================================================================***/

extern	char *	XkbAtomGetString(
#if NeedFunctionPrototypes
    Display *	/* dpy */,
    Atom 	/* atm */
#endif
);

extern	Atom	XkbInternAtom(
#if NeedFunctionPrototypes
    Display *	/* dpy */,
    char *	/* name */,
    Bool	/* onlyIfExists */
#endif
);

extern	Status	XkbChangeKbdDisplay(
#if NeedFunctionPrototypes
    Display *		/* newDpy */,
    XkbFileInfo *	/* result */
#endif
);

extern	Atom	XkbChangeAtomDisplay(
#if NeedFunctionPrototypes
    Display *	/* oldDpy */,
    Display *	/* newDpy */,
    Atom	/* atm */
#endif
);

extern	void	XkbInitAtoms(
#if NeedFunctionPrototypes
    Display *	/* dpy */
#endif
);

/***====================================================================***/

#ifdef _XKBGEOM_H_

#define	XkbDW_Unknown	0
#define	XkbDW_Doodad	1
#define	XkbDW_Section	2
typedef struct _XkbDrawable {
	int		type;
	int		priority;
	union {
	    XkbDoodadPtr	doodad;
	    XkbSectionPtr	section;
	} u;
	struct _XkbDrawable *	next;
} XkbDrawableRec,*XkbDrawablePtr; 

extern	XkbDrawablePtr
XkbGetOrderedDrawables(
#if NeedFunctionPrototypes
    XkbGeometryPtr	/* geom */,
    XkbSectionPtr	/* section */
#endif
);

extern	void
XkbFreeOrderedDrawables(
#if NeedFunctionPrototypes
    XkbDrawablePtr	/* draw */
#endif
);

#endif

/***====================================================================***/

extern	unsigned	XkbConvertGetByNameComponents(
#if NeedFunctionPrototypes
    Bool		/* toXkm */,
    unsigned 		/* orig */
#endif
);

extern	unsigned	XkbConvertXkbComponents(
#if NeedFunctionPrototypes
    Bool		/* toXkm */,
    unsigned 		/* orig */
#endif
);

extern	Bool	XkbDetermineFileType(
#if NeedFunctionPrototypes
    XkbFileInfo *	/* xkb */,
    int			/* format */,
    int *		/* opts_missing */
#endif
);

extern	Bool	XkbNameMatchesPattern(
#if NeedFunctionPrototypes
    char *		/* name */,
    char *		/* pattern */
#endif
);

/***====================================================================***/

extern	Bool	XkbWriteXKBKeycodes(
#if NeedFunctionPrototypes
    FILE *		/* file */,
    XkbFileInfo *	/* result */,
    Bool		/* topLevel */,
    Bool		/* showImplicit */,
    XkbFileAddOnFunc	/* addOn */,
    void *		/* priv */
#endif
);

extern	Bool	XkbWriteXKBKeyTypes(
#if NeedFunctionPrototypes
    FILE *		/* file */,
    XkbFileInfo *	/* result */,
    Bool		/* topLevel */,
    Bool		/* showImplicit */,
    XkbFileAddOnFunc	/* addOn */,
    void *		/* priv */
#endif
);

extern	Bool	XkbWriteXKBCompatMap(
#if NeedFunctionPrototypes
    FILE *		/* file */,
    XkbFileInfo *	/* result */,
    Bool		/* topLevel */,
    Bool		/* showImplicit */,
    XkbFileAddOnFunc	/* addOn */,
    void *		/* priv */
#endif
);

extern	Bool	XkbWriteXKBSymbols(
#if NeedFunctionPrototypes
    FILE *		/* file */,
    XkbFileInfo *	/* result */,
    Bool		/* topLevel */,
    Bool		/* showImplicit */,
    XkbFileAddOnFunc	/* addOn */,
    void *		/* priv */
#endif
);

extern	Bool	XkbWriteXKBGeometry(
#if NeedFunctionPrototypes
    FILE *		/* file */,
    XkbFileInfo *	/* result */,
    Bool		/* topLevel */,
    Bool		/* showImplicit */,
    XkbFileAddOnFunc	/* addOn */,
    void *		/* priv */
#endif
);

extern	Bool	XkbWriteXKBSemantics(
#if NeedFunctionPrototypes
    FILE *		/* file */,
    XkbFileInfo *	/* result */,
    Bool		/* topLevel */,
    Bool		/* showImplicit */,
    XkbFileAddOnFunc	/* addOn */,
    void *		/* priv */
#endif
);

extern	Bool	XkbWriteXKBLayout(
#if NeedFunctionPrototypes
    FILE *		/* file */,
    XkbFileInfo *	/* result */,
    Bool		/* topLevel */,
    Bool		/* showImplicit */,
    XkbFileAddOnFunc	/* addOn */,
    void *		/* priv */
#endif
);

extern	Bool	XkbWriteXKBKeymap(
#if NeedFunctionPrototypes
    FILE *		/* file */,
    XkbFileInfo *	/* result */,
    Bool		/* topLevel */,
    Bool		/* showImplicit */,
    XkbFileAddOnFunc	/* addOn */,
    void *		/* priv */
#endif
);

extern	Bool	XkbWriteXKBFile(
#if NeedFunctionPrototypes
    FILE *		/* file */,
    XkbFileInfo *	/* result */,
    Bool		/* showImplicit */,
    XkbFileAddOnFunc	/* addOn */,
    void *		/* priv */
#endif
);

extern	Bool	XkbWriteCFile(
#if NeedFunctionPrototypes
    FILE *		/* file */,
    char *		/* name */,
    XkbFileInfo *	/* info */
#endif
);

extern	Bool	XkbWriteXKMFile(
#if NeedFunctionPrototypes
    FILE *		/* file */,
    XkbFileInfo *	/* result */
#endif
);

extern	Bool	XkbWriteToServer(
#if NeedFunctionPrototypes
    XkbFileInfo *	/* result */
#endif
);

extern	void	XkbEnsureSafeMapName(
#if NeedFunctionPrototypes
    char *		/* name */
#endif
);

extern	Bool	XkbWriteXKBKeymapForNames(
#if NeedFunctionPrototypes
    FILE *			/* file */,
    XkbComponentNamesPtr	/* names */,
    Display *			/* dpy */,
    XkbDescPtr			/* xkb */,
    unsigned			/* want */,
    unsigned			/* need */
#endif
);

/***====================================================================***/

extern Bool	XkmProbe(
#if NeedFunctionPrototypes
    FILE *		/* file */
#endif
);

extern unsigned XkbReadFromServer(
#if NeedFunctionPrototypes
    Display *		/* dpy */,
    unsigned		/* need */,
    unsigned		/* want */,
    XkbFileInfo *	/* result */
#endif
);

extern unsigned	XkmReadFile(
#if NeedFunctionPrototypes
    FILE *		/* file */,
    unsigned		/* need */,
    unsigned		/* want */,
    XkbFileInfo *	/* result */
#endif
);

#ifdef _XKMFORMAT_H_

extern Bool	XkmReadTOC(
#if NeedFunctionPrototypes
    FILE *              /* file */,
    xkmFileInfo *       /* file_info */,
    int                 /* max_toc */,
    xkmSectionInfo *    /* toc */
#endif
);

extern xkmSectionInfo *XkmFindTOCEntry(
#if NeedFunctionPrototypes
    xkmFileInfo *       /* finfo */,
    xkmSectionInfo *    /* toc */,
    unsigned            /* type */
#endif
);

extern Bool	XkmReadFileSection(
#if NeedFunctionPrototypes
    FILE *              /* file */,
    xkmSectionInfo *    /* toc */,
    XkbFileInfo *       /* result */,
    unsigned *          /* loaded_rtrn */
#endif
);

extern char *	XkmReadFileSectionName(
#if NeedFunctionPrototypes
    FILE *		/* file */,
    xkmSectionInfo *	/* toc */
#endif
);

#endif /* _XKMFORMAT_H  */

_XFUNCPROTOEND

#endif /* _XKBFILE_H_ */
