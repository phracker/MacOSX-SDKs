/*
 *
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
 *
 */

/*
 * SimpleMenuP.h - Private Header file for SimpleMenu widget.
 *
 * Date:    April 3, 1989
 *
 * By:      Chris D. Peterson
 *          MIT X Consortium
 *          kit@expo.lcs.mit.edu
 */

#ifndef _SimpleMenuP_h
#define _SimpleMenuP_h

#include <X11/Xaw/SimpleMenu.h>
#include <X11/Xaw/SmeP.h>
#include <X11/ShellP.h>
#include <X11/Xaw/XawInit.h>

typedef struct {
    XtPointer extension;		/* For future needs */
} SimpleMenuClassPart;

typedef struct _SimpleMenuClassRec {
    CoreClassPart	    core_class;
    CompositeClassPart	    composite_class;
    ShellClassPart	    shell_class;
    OverrideShellClassPart  override_shell_class;
    SimpleMenuClassPart	    simpleMenu_class;
} SimpleMenuClassRec;

extern SimpleMenuClassRec simpleMenuClassRec;

typedef struct _SimpleMenuPart {
  /* resources */
    String	label_string;	/* The string for the label or NULL */
    SmeObject	label;		/* If label_string is non-NULL then this is
				   the label widget */
    WidgetClass	label_class;	/* Widget Class of the menu label object */
    Dimension	top_margin;	/* Top and bottom margins */
    Dimension	bottom_margin;
    Dimension	row_height;	/* height of each row (menu entry) */
    Cursor	cursor;		/* The menu's cursor */
    SmeObject	popup_entry;	/* The entry to position the cursor on for
				   when using XawPositionSimpleMenu */
    Boolean	menu_on_screen;	/* Force the menus to be fully on the screen*/
    int		backing_store;	/* What type of backing store to use */

    /* private */
    Boolean	recursive_set_values; /* contain a possible infinite loop */
    Boolean	menu_width;	/* If true then force width to remain 
				   core.width */
    Boolean	menu_height;	/* Just like menu_width, but for height */
    SmeObject	entry_set;	/* The entry that is currently set or
				   highlighted */
#ifndef OLDXAW
    Dimension	left_margin;
    Dimension	right_margin;
    XawDisplayList *display_list;
    Widget	sub_menu;
    unsigned	char state;
    XtPointer pad[4];	/* for future use and keep binary compatability */
#endif
} SimpleMenuPart;

typedef struct _SimpleMenuRec {
    CorePart		core;
    CompositePart 	composite;
    ShellPart		shell;
    OverrideShellPart	override;
    SimpleMenuPart	simple_menu;
} SimpleMenuRec;

#endif /* _SimpleMenuP_h */
