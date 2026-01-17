/***********************************************************

Copyright 1987, 1988, 1994, 1998  The Open Group

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


Copyright 1987, 1988 by Digital Equipment Corporation, Maynard, Massachusetts.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the name of Digital not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/

#ifndef _XawTextP_h
#define _XawTextP_h

#include <X11/Xfuncproto.h>

#include <X11/Xaw/Text.h>
#include <X11/Xaw/SimpleP.h>

_XFUNCPROTOBEGIN

#define MAXCUT	30000	/* Maximum number of characters that can be cut */

#define XawTextGetLastPosition(ctx)				\
	XawTextSourceScan((ctx)->text.source, 0,		\
			  XawstAll, XawsdRight, 1, True)
#define GETLASTPOS	XawTextGetLastPosition(ctx)

#define zeroPosition ((XawTextPosition)0)

extern XtActionsRec _XawTextActionsTable[];
extern Cardinal _XawTextActionsTableCount;

extern char _XawDefaultTextTranslations[];

#define XawLF	  0x0a
#define XawCR	  0x0d
#define XawTAB	  0x09
#define XawBS	  0x08
#define XawSP	  0x20
#define XawDEL	  0x7f
#define XawESC	  0x1b
#define XawBSLASH '\\'

/* constants that subclasses may want to know */
#define DEFAULT_TEXT_HEIGHT ((Dimension)~0)
#define DEFAULT_TAB_SIZE	8

/* displayable text management data structures */
typedef struct {
    XawTextPosition position;
    Position y;
#ifndef OLDXAW
    unsigned int textWidth;
#else
    Dimension textWidth;
#endif
} XawTextLineTableEntry, *XawTextLineTableEntryPtr;

typedef struct {
    XawTextPosition left, right;
    XawTextSelectType type;
    Atom *selections;
    int atom_count;
    int array_size;
} XawTextSelection;

typedef struct _XawTextSelectionSalt {
    struct _XawTextSelectionSalt *next;
    XawTextSelection	s;
    /* 
     * The element "contents" stores the CT string which is gotten in the
     * function _XawTextSaltAwaySelection()
    */ 
    char		*contents;
    int			length;
} XawTextSelectionSalt;

#ifndef OLDXAW
typedef struct _XawTextKillRing {
    struct _XawTextKillRing *next;
    char *contents;
    int length;
    unsigned refcount;
    unsigned long format;
} XawTextKillRing;

extern XawTextKillRing *xaw_text_kill_ring;
#endif

/* Line Tables are n+1 long - last position displayed is in last lt entry */
typedef struct {
    XawTextPosition top;	 /* Top of the displayed text */
    int lines;			 /* How many lines in this table */
#ifndef OLDXAW
    int base_line;		 /* line number of first entry */
#endif
    XawTextLineTableEntry *info; /* A dynamic array, one entry per line  */
} XawTextLineTable, *XawTextLineTablePtr;

typedef struct _XawTextMargin {
    Position left, right, top, bottom;
} XawTextMargin;

typedef struct _XmuScanline XmuTextUpdate;

#define VMargins(ctx)  ((ctx)->text.margin.top + (ctx)->text.margin.bottom)
#define HMargins(ctx)  ((ctx)->text.left_margin + (ctx)->text.margin.right)
#define RVMargins(ctx) ((ctx)->text.r_margin.top + (ctx)->text.r_margin.bottom)
#define RHMargins(ctx) ((ctx)->text.r_margin.left + (ctx)->text.r_margin.right)

#define IsPositionVisible(ctx, pos) \
(pos >= ctx->text.lt.info[0].position && \
		 pos < ctx->text.lt.info[ctx->text.lt.lines].position)

/*
 * Search & Replace data structure
 */
struct SearchAndReplace {
    Boolean selection_changed;	/* flag so that the selection cannot be
				   changed out from underneath query-replace.*/
    Widget search_popup;	/* The poppup widget that allows searches.*/
    Widget label1;		/* The label widgets for the search window. */
    Widget label2;
    Widget left_toggle; 	/* The left search toggle radioGroup. */
    Widget right_toggle;	/* The right search toggle radioGroup. */
    Widget rep_label;		/* The Replace label string. */
    Widget rep_text;		/* The Replace text field. */
    Widget search_text; 	/* The Search text field. */
    Widget rep_one;		/* The Replace one button. */
    Widget rep_all;		/* The Replace all button. */
#ifndef OLDXAW
    Widget case_sensitive;	/* The "Case Sensitive" toggle */
#endif
};

/* New fields for the Text widget class record */
typedef struct {
  XtPointer extension;
} TextClassPart;

/* Full class record declaration */
typedef struct _TextClassRec {
    CoreClassPart	core_class;
    SimpleClassPart	simple_class;
    TextClassPart	text_class;
} TextClassRec;

extern TextClassRec textClassRec;

/* New fields for the Text widget record */
typedef struct _TextPart {
    /* resources */
    Widget source, sink;
    XawTextPosition insertPos;
    XawTextSelection s;
    XawTextSelectType *sarray;		     /* Array to cycle for selections */
    XawTextSelectionSalt *salt;		     /* salted away selections */
    int left_margin;
    int dialog_horiz_offset, dialog_vert_offset; /* position for popup dialog */
    Boolean display_caret;		     /* insertion pt visible iff T */
    Boolean auto_fill;			     /* Auto fill mode? */
    XawTextScrollMode scroll_vert, scroll_horiz;
    XawTextWrapMode wrap;		     /* The type of wrapping */
    XawTextResizeMode resize;
    XawTextMargin r_margin;		     /* The real margins */
#ifndef OLDXAW
    XtCallbackList position_callbacks;
#else
    XtPointer pad1;
#endif

    /* private state */
    XawTextMargin margin;		     /* The current margins */
    XawTextLineTable lt;
    XawTextScanDirection extendDir;
    XawTextSelection origSel;		     /* the selection being modified */
    Time lasttime;			     /* timestamp of last processed action */
    Time time;				     /* time of last key or button action */
    Position ev_x, ev_y;		     /* x, y coords for key or button action */
    Widget vbar, hbar;			     /* The scroll bars (none = NULL) */
    struct SearchAndReplace *search;	     /* Search and replace structure */
    Widget file_insert;			     /* The file insert popup widget */
    XmuTextUpdate *update;		     /* Position intervals to update */
#ifndef OLDXAW
    int line_number;
    short column_number;
    unsigned char kill_ring;
    Boolean selection_state;
#else
    XtPointer pad2;
    int pad3;
#endif
    int from_left;			     /* Cursor position */
    XawTextPosition lastPos;		     /* Last position of source */
    GC gc;
    Boolean showposition;		     /* True if we need to show the position */
    Boolean hasfocus;			     /* TRUE if we currently have input focus*/
    Boolean update_disabled;		     /* TRUE if display updating turned off */
    Boolean clear_to_eol;		     /* Clear to eol when painting text? */
    XawTextPosition old_insert;		     /* Last insertPos for batched updates */
    short mult;				     /* Multiplier */
#ifndef OLDXAW
    XawTextKillRing *kill_ring_ptr;
#else
    XtPointer pad4;
#endif

    /* private state, shared w/Source and Sink */
    Boolean redisplay_needed;		     /* in SetValues */
    XawTextSelectionSalt *salt2;	     /* salted away selections */

#ifndef OLDXAW
    char numeric;
    char source_changed;
    Boolean overwrite;                      /* Overwrite mode */

    /* new resources and states, for text edition
     * Note: a fixed width font is required for these resources/states.
     */
    short left_column, right_column;
    XawTextJustifyMode justify;
    XtPointer pad[4];	/* for future use and keep binary compatability */
#endif
} TextPart;

#define XtRWrapMode	"WrapMode"
#define XtRScrollMode	"ScrollMode"
#define XtRResizeMode	"ResizeMode"
#define XtRJustifyMode	"JustifyMode"

/* full instance record */
typedef struct _TextRec {
    CorePart	core;
    SimplePart	simple;
    TextPart	text;
} TextRec;

/*
 * Semi-private functions
 * for use by other Xaw modules only
 */
void _XawTextBuildLineTable
(
 TextWidget		ctx,
 XawTextPosition	top_pos,
 _XtBoolean		force_rebuild
 );

char *_XawTextGetSTRING
(
 TextWidget		ctx,
 XawTextPosition	left,
 XawTextPosition	right
 );

void _XawTextSaltAwaySelection
(
 TextWidget		ctx,
 Atom			*selections,
 int			num_atoms
 );

void _XawTextPosToXY
(
 Widget			w,
 XawTextPosition	pos,
 Position		*x,
 Position		*y
 );

void _XawTextNeedsUpdating
(
 TextWidget		ctx,
 XawTextPosition	left,
 XawTextPosition	right
 );

_XFUNCPROTOEND

#endif /* _XawTextP_h */
