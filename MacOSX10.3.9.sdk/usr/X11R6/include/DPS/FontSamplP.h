/* 
 * FontSamplP.h
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
/* $XFree86: xc/include/DPS/FontSamplP.h,v 1.2 2000/06/07 22:02:55 tsi Exp $ */

#ifndef _FontSamplerP_H
#define _FontSamplerP_H

#include <DPS/FontSample.h>
#include <DPS/FontSB.h>

typedef struct _DisplayedTextRec {
    String str;
    float size;
    struct _DisplayedTextRec *next;
} DisplayedTextRec;

typedef struct _DisplayedFontRec {
    Position l, r, t, b;
    Position x, y;
    FontRec *font;
    BlendRec *blend;
    DisplayedTextRec *text;
    struct _DisplayedFontRec *next;
} DisplayedFontRec;

typedef struct {
    FontSamplerWidget sampler;
    Boolean inited, any_shown;
    Dimension column_width;
    Position x, y;
    Dimension height, width;
    Dimension window_height;
    int depth;
    FontFamilyRec *current_family;
    FontRec *current_font;
    BlendRec *current_blend;
    DisplayedTextRec *text_list;
    DisplayedFontRec *shown_fonts;
} DisplayRecord;

typedef struct {
    float *sizes;
    int size_count;
    FontSelectionBoxWidget fsb;
    XtCallbackList dismiss_callback;
    Dimension minimum_width;
    Dimension minimum_height;
    XmString no_room_message;
    XmString no_font_message;
    XmString no_selected_font_message;
    XmString no_selected_family_message;
    XmString no_family_font_message;
    XmString no_match_message;
    Widget panel_child;
    Widget area_child;
    Widget text_child;
    Widget font_label_child;
    Widget scrolled_window_child;
    Widget display_button_child;
    Widget dismiss_button_child;
    Widget stop_button_child;
    Widget clear_button_child;
    Widget radio_frame_child;
    Widget radio_box_child;
    Widget all_toggle_child;
    Widget selected_toggle_child;
    Widget selected_family_toggle_child;
    Widget filter_toggle_child;
    Widget filter_text_child;
    Widget filter_box_child;
    Widget filter_frame_child;
    Widget size_option_menu_child;
    Widget size_text_field_child;
    Widget size_label_child;

 /* Private fields */

    Widget size_menu;
    Widget other_size;
    Widget *filter_widgets;
    Widget clip_widget;
    Boolean displaying;
    Pixmap pixmap;
    XtWorkProcId current_display_proc;
    DisplayRecord *current_display_info;
    DisplayedFontRec *highlighted_font;
    DPSGState gstate;
    DPSGState pixmap_gstate;
    GC gc;
    char *filter_text;
    Boolean *filter_flags;
    Boolean filters_changed;
    float ctm[6];
    float invctm[6];
} FontSamplerPart;

typedef struct _FontSamplerRec {
    CorePart			core;
    CompositePart		composite;
    ConstraintPart		constraint;
    XmManagerPart		manager;
    FontSamplerPart		sampler;
} FontSamplerRec;

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

typedef void (*FSBCancelProc) (Widget w);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#define InheritCancel ((FSBCancelProc) _XtInherit)

typedef struct {
    FSBCancelProc		cancel;
    XtPointer			extension;
} FontSamplerClassPart;

typedef struct _FontSamplerClassRec {
    CoreClassPart		core_class;
    CompositeClassPart		composite_class;
    ConstraintClassPart		constraint_class;
    XmManagerClassPart		manager_class;
    FontSamplerClassPart	sampler_class;
} FontSamplerClassRec, *FontSamplerWidgetClass;

extern FontSamplerClassRec fontSamplerClassRec;

#endif /* _FontSamplerP_H */
/* DON'T ADD ANYTHING AFTER THIS #endif */
