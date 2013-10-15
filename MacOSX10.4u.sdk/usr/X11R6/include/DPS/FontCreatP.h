/* 
 * FontCreatP.h
 *
 * (c) Copyright 1991-1994 Adobe Systems Incorporated.
 * All rights reserved.
 * 
 * Permission to use, copy, modify, distribute, and sublicense this software
 * and its documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notices appear in all copies and that
 * both those copyright notices and this permission notice appear in
 * supporting documentation and that the name of Adobe Systems Incorporated
 * not be used in advertising or publicity pertaining to distribution of the
 * software without specific, written prior permission.  No trademark license
 * to use the Adobe trademarks is hereby granted.  If the Adobe trademark
 * "Display PostScript"(tm) is used to describe this software, its
 * functionality or for any other purpose, such use shall be limited to a
 * statement that this software works in conjunction with the Display
 * PostScript system.  Proper trademark attribution to reflect Adobe's
 * ownership of the trademark shall be given whenever any such reference to
 * the Display PostScript system is made.
 * 
 * ADOBE MAKES NO REPRESENTATIONS ABOUT THE SUITABILITY OF THE SOFTWARE FOR
 * ANY PURPOSE.  IT IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
 * ADOBE DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NON- INFRINGEMENT OF THIRD PARTY RIGHTS.  IN NO EVENT SHALL ADOBE BE LIABLE
 * TO YOU OR ANY OTHER PARTY FOR ANY SPECIAL, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE, STRICT LIABILITY OR ANY OTHER ACTION ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.  ADOBE WILL NOT
 * PROVIDE ANY TRAINING OR OTHER SUPPORT FOR THE SOFTWARE.
 * 
 * Adobe, PostScript, and Display PostScript are trademarks of Adobe Systems
 * Incorporated which may be registered in certain jurisdictions
 * 
 * Author:  Adobe Systems Incorporated
 */

#ifndef _FontCreatorP_H
#define _FontCreatorP_H

#define MAX_AXES 4

#include <DPS/FontCreato.h>

typedef struct {
    float *sizes;
    int size_count;
    FontSelectionBoxWidget fsb;
    XtCallbackList dismiss_callback;

    Widget pane_child;
    Widget preview_child;
    Widget display_text_child;
    Widget axis_label_child[MAX_AXES];
    Widget axis_scale_child[MAX_AXES];
    Widget axis_min_label_child[MAX_AXES];
    Widget axis_max_label_child[MAX_AXES];
    Widget axis_value_text_child[MAX_AXES];
    Widget face_scrolled_list_child;
    Widget blend_label_child;
    Widget blend_scrolled_list_child;
    Widget size_text_field_child;
    Widget size_option_menu_child;
    Widget generate_button_child;
    Widget name_label_child;
    Widget name_text_child;
    Widget do_all_toggle_child;
    Widget follow_size_toggle_child;

    /* Private fields */

    DPSGState gstate;
    Widget other_size;
    Widget size_menu;
    Widget option_box;
    FontFamilyRec *family;
    FontRec *font;
    int managed_axes;
    Boolean preview_fixed;
} FontCreatorPart;

typedef struct _FontCreatorRec {
    CorePart			core;
    CompositePart		composite;
    ConstraintPart		constraint;
    XmManagerPart		manager;
    FontCreatorPart		creator;
} FontCreatorRec;

typedef struct {
    XtPointer			extension;
} FontCreatorClassPart;

typedef struct _FontCreatorClassRec {
    CoreClassPart		core_class;
    CompositeClassPart		composite_class;
    ConstraintClassPart		constraint_class;
    XmManagerClassPart		manager_class;
    FontCreatorClassPart	creator_class;
} FontCreatorClassRec, *FontCreatorWidgetClass;

extern FontCreatorClassRec fontCreatorClassRec;

#endif /* _FontCreatorP_H */
/* DON'T ADD ANYTHING AFTER THIS #endif */
