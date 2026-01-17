/*

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

/* 
 * Author: Chris D. Peterson
 *         MIT X Consortium
 *         kit@expo.lcs.mit.edu
 *  
 * Date:   January 12, 1989
 *
 */

#ifndef _XawToggleP_h
#define _XawToggleP_h

#include <X11/Xaw/Toggle.h>
#include <X11/Xaw/CommandP.h>

/*
 * Toggle Widget Private Data
 */
#define streq(a, b)	(strcmp((a), (b)) == 0)

typedef struct _RadioGroup {
    struct _RadioGroup *prev, *next; /* Pointers to other elements in group  */
    Widget widget;		     /* Widget corrosponding to this element */
} RadioGroup;

/* New fields for the Toggle widget class */
typedef struct _ToggleClass  {
    XtActionProc Set;
    XtActionProc Unset;
    XtPointer extension;
} ToggleClassPart;

/* class record declaration */
typedef struct _ToggleClassRec {
    CoreClassPart	core_class;
    SimpleClassPart	simple_class;
    LabelClassPart	label_class;
    CommandClassPart	command_class;
    ToggleClassPart	toggle_class;
} ToggleClassRec;

extern ToggleClassRec toggleClassRec;

/* New fields for the Toggle widget */
typedef struct {
    /* resources */
    Widget widget;
    XtPointer radio_data;

    /* private */
    RadioGroup *radio_group;
#ifndef OLDXAW
    XtPointer pad[4];	/* for future use and keep binary compatability */
#endif
} TogglePart;

/* Full widget declaration */
typedef struct _ToggleRec {
    CorePart	core;
    SimplePart	simple;
    LabelPart	label;
    CommandPart	command;
    TogglePart	toggle;
} ToggleRec;

#endif /* _XawToggleP_h */
