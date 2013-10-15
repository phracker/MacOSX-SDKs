/*
Copyright 1989, 1994, 1998  The Open Group

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

/*  This is the List widget, it is useful to display a list, without the
 *  overhead of having a widget for each item in the list.  It allows 
 *  the user to select an item in a list and notifies the application through
 *  a callback function.
 *
 *	Created: 	8/13/88
 *	By:		Chris D. Peterson
 *                      MIT X Consortium
 */

#ifndef _XawList_h
#define _XawList_h

#include <X11/Xaw/Simple.h>

/* Resources:

 Name		     Class		RepType		Default Value
 ----		     -----		-------		-------------
 background	     Background		Pixel		XtDefaultBackground
 borderColor	     BorderColor	Pixel		XtDefaultForeground
 borderWidth	     BorderWidth	Dimension	1
 callback            Callback           XtCallbackList  NULL       **6
 columnSpacing       Spacing            Dimension       6
 cursor		     Cursor		Cursor		left_ptr
 cursorName	     Cursor		String		NULL
 defaultColumns      Columns            int             2          **5
 destroyCallback     Callback		Pointer		NULL 
 font		     Font		XFontStruct*	XtDefaultFont
 forceColumns        Columns            Boolean         False      **5
 foreground	     Foreground		Pixel		XtDefaultForeground
 height		     Height		Dimension	0          **1
 insensitiveBorder   Insensitive	Pixmap		Gray
 internalHeight	     Height		Dimension	2
 internalWidth	     Width		Dimension	4
 list		     List		String*		NULL	   **2
 longest             Longest            int             0          **3  **4
 mappedWhenManaged   MappedWhenManaged	Boolean		True
 numberStrings       NumberStrings      int             0          **4
 pasteBuffer         Boolean            Boolean         False
 pointerColor	     Foreground		Pixel		XtDefaultForeground
 pointerColorBackground Background	Pixel		XtDefaultBackground
 rowSpacing          Spacing            Dimension       4
 sensitive	     Sensitive		Boolean		True
 verticalList        Boolean            Boolean         False
 width		     Width		Dimension	0          **1
 x		     Position		Position	0
 y		     Position		Position	0

 **1 - If the Width or Height of the list widget is zero (0) then the value
       is set to the minimum size necessay to fit the entire list.

       If both Width and Height are zero then they are adjusted to fit the
       entire list that is created width the number of default columns 
       specified in the defaultColumns resource.

 **2 - This is an array of strings the specify elements of the list.
       This resource must be specified. 
       (What good is a list widget without a list??  :-)

 **3 - Longest is the length of the widest string in pixels.

 **4 - If either of these values are zero (0) then the list widget calculates
       the correct value. 

       (This allows you to make startup faster if you already have 
        this information calculated)

       NOTE: If the numberStrings value is zero the list must 
             be NULL terminated.

 **5 - By setting the List.Columns resource you can force the application to
       have a given number of columns.	     
        
 **6 - This returns the name and index of the item selected in an 
       XawListReturnStruct that is pointed to by the client_data
       in the CallbackProc.

*/

/*
 * Value returned when there are no highlighted objects
 */
#define XAW_LIST_NONE -1	

#define XtCList "List"
#define XtCSpacing "Spacing"
#define XtCColumns "Columns"
#define XtCLongest "Longest"
#define XtCNumberStrings "NumberStrings"

#define XtNcursor "cursor"
#define XtNcolumnSpacing "columnSpacing"
#define XtNdefaultColumns "defaultColumns"
#define XtNforceColumns "forceColumns"
#define XtNlist "list"
#define XtNlongest "longest"
#define XtNnumberStrings "numberStrings"
#define XtNpasteBuffer "pasteBuffer"
#define XtNrowSpacing "rowSpacing"
#define XtNverticalList "verticalList"
#define XtNshowCurrent "showCurrent"
 
#ifndef XtNfontSet
#define XtNfontSet "fontSet"
#endif

#ifndef XtCFontSet
#define XtCFontSet "FontSet"
#endif

extern WidgetClass listWidgetClass;

typedef struct _ListClassRec *ListWidgetClass;
typedef struct _ListRec      *ListWidget;

/* list return structure */
typedef struct _XawListReturnStruct {
  String string;
  int list_index;
} XawListReturnStruct;

_XFUNCPROTOBEGIN

/*
 * Function:
 *	XawListChange
 *
 * Parameters:
 *	w	- list widget
 *	list	- new list
 *	nitems	- number of items in the list
 *	longest - length (in Pixels) of the longest element in the list
 *	resize	- if True the the list widget will try to resize itself
 *
 * Description:
 *	Changes the list being used and shown.
 *
 * Note:
 *	If nitems of longest are <= 0 then they will be caluculated
 *	If nitems is <= 0 then the list needs to be NULL terminated
 */
void XawListChange
(
 Widget			w,
 String			*list,
 int			nitems,
 int			longest,
#if NeedWidePrototypes
 int			resize
#else
 Boolean		resize
#endif
 );

/*
 * Function:
 *	XawListUnhighlight
 *
 * Parameters:
 *	w - list widget
 *
 * Description:
 *	Unlights the current highlighted element.
 */
void XawListUnhighlight
(
 Widget			w
 );

/*
 * Function:
 *	XawListHighlight
 *
 * Parameters:
 *	w    - list widget
 *	item - item to highlight
 *
 * Description:
 *	Highlights the given item.
 */
void XawListHighlight
(
 Widget			w,
 int			item
 );


/*
 * Function:
 *	XawListShowCurrent
 *
 * Paraneters:
 *	w - list widget
 *
 * Description:
 *	Returns the currently highlighted object.
 *
 * Returns:
 *	The info about the currently highlighted object
 */

XawListReturnStruct *XawListShowCurrent
(
 Widget			w
 );

_XFUNCPROTOEND

#endif /* _XawList_h */
