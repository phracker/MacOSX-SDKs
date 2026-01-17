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

#ifndef _XawTextSrc_h
#define _XawTextSrc_h

#include <X11/Xaw/Text.h>

/* Resources:

 Name		     Class		RepType		Default Value
 ----		     -----		-------		-------------
 callback	     Callback		Callback	NULL
 editType	     EditType		XawTextEditType	XawtextRead
 enableUndo	     Undo		Boolean		False
 sourceChanged	     Changed		Boolean		False

*/
 
/* Class record constants */
extern WidgetClass textSrcObjectClass;

typedef struct _TextSrcClassRec *TextSrcObjectClass;
typedef struct _TextSrcRec      *TextSrcObject;

typedef enum {
    XawstPositions,
    XawstWhiteSpace,
    XawstEOL,
    XawstParagraph,
    XawstAll,
    XawstAlphaNumeric
  } XawTextScanType;

typedef enum {
    Normal,
    Selected
} highlightType;

typedef enum {
    XawsmTextSelect,
    XawsmTextExtend
} XawTextSelectionMode;

typedef enum {
    XawactionStart,
    XawactionAdjust,
    XawactionEnd
} XawTextSelectionAction;

#define XawTextReadError -1
#define XawTextScanError -1

#ifndef OLDXAW
#define XtNenableUndo		"enableUndo"
#define XtCUndo			"Undo"

#define XtNsourceChanged	"sourceChanged"
#define XtCChanged		"Changed"

#define XtNpropertyCallback	"propertyCallback"
#endif

/*
 * Public Functions
 */
_XFUNCPROTOBEGIN

/*
 * Function:
 *	XawTextSourceRead
 *
 * Parameters:
 *	w      - TextSrc Object
 *	pos    - position of the text to retreive
 *	text   - text block that will contain returned text
 *	length - maximum number of characters to read
 *
 * Description:
 *	This function reads the source.
 *
 * Returns:
 *	The number of characters read into the buffer
 */
XawTextPosition XawTextSourceRead
(
 Widget			w,
 XawTextPosition	pos,
 XawTextBlock		*text_return,
 int			length
 );

/*
 * Function:
 *	XawTextSourceReplace
 *
 * Parameters:
 *	src	 - Text Source Object
 *	startPos - ends of text that will be removed
 *	endPos	 - ""
 *	text	 - new text to be inserted into buffer at startPos
 *
 * Description:
 *	Replaces a block of text with new text
 *
 * Returns:
 *	XawEditError or XawEditDone
 */
int XawTextSourceReplace
(
 Widget			w,
 XawTextPosition	start,
 XawTextPosition	end,
 XawTextBlock		*text
 );

/*
 * Function:
 *	XawTextSourceScan
 *
 * Parameters:
 *	w	 - TextSrc Object
 *	position - position to start scanning
 *	type	 - type of thing to scan for
 *	dir	 - direction to scan
 *	count	 - which occurance if this thing to search for
 *	include	 - whether or not to include the character found in
 *		   the position that is returned. 
 *
 * Description:
 *	Scans the text source for the number and type of item specified.
 *
 * Returns:
 *	The position of the text
 */
XawTextPosition XawTextSourceScan
(
 Widget			w,
 XawTextPosition	position,
#if NeedWidePrototypes
 int			type,
 int			dir,
 int			count,
 int			include
#else
 XawTextScanType	type,
 XawTextScanDirection	dir,
 int			count,
 Boolean		include
#endif
 );

/*
 * Function:
 *	XawTextSourceSearch
 *
 * Parameters:
 *	w	 - TextSource Object
 *	position - position to start scanning
 *	dir	 - direction to search
 *	text	 - the text block to search for
 *
 * Description:
 *	Searchs the text source for the text block passed.
 *
 * Returns:
 *	The position of the text we are searching for or XawTextSearchError
 */
XawTextPosition XawTextSourceSearch
(
 Widget			w,
 XawTextPosition	position,
#if NeedWidePrototypes
 int			dir,
#else
 XawTextScanDirection	dir,
#endif
 XawTextBlock		*text
 );

/*
 * Function:
 *	XawTextSourceConvertSelection
 *
 * Parameters:
 *	w	  - TextSrc object
 *	selection - current selection atom
 *	target	  - current target atom
 *	type	  - type to conver the selection to
 *	value	  - return value that has been converted
 *	length	  - ""
 *	format	  - format of the returned value
 *
 * Returns:
 *	True if the selection has been converted
 */
Boolean XawTextSourceConvertSelection
(
 Widget			w,
 Atom			*selection,
 Atom			*target,
 Atom			*type,
 XtPointer		*value_return,
 unsigned long		*length_return,
 int			*format_return
 );

/*
 * Function:
 *	XawTextSourceSetSelection
 *
 * Parameters:
 *	w	  - TextSrc object
 *	left	  - bounds of the selection
 *	right	  - ""
 *	selection - selection atom
 *
 * Description:
 *	Allows special setting of the selection.
 */
void XawTextSourceSetSelection
(
 Widget			w,
 XawTextPosition	start,
 XawTextPosition	end,
 Atom			selection
 );

_XFUNCPROTOEND

#endif /* _XawTextSrc_h */
