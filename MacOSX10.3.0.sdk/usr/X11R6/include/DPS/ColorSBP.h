/* 
 * ColorSBP.h
 *
 * (c) Copyright 1993-1994 Adobe Systems Incorporated.
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
/* $XFree86: xc/include/DPS/ColorSBP.h,v 1.2 2000/06/07 22:02:54 tsi Exp $ */

#ifndef _ColorSelectionBoxP_H
#define _ColorSelectionBoxP_H

#include <DPS/ColorSB.h>

typedef struct {
    float red, green, blue;
    float cyan, magenta, yellow, black;
    float hue, saturation, brightness;
    float gray;
} ColorRec;

/* Redefining PALETTE_MAX requires program alterations. */

#define PALETTE_MAX 10

typedef struct {
    DPSContext context;
    String rgb_labels;
    String cmyk_labels;
    String hsb_labels;
    String gray_labels;
    Dimension cell_size;
    short num_cells;
    short current_palette;
    String fill_me;
    CSBColorSpace current_space;
    CSBRenderingType current_rendering;
    String broken_palette_label;
    String broken_palette_message;

    String palette_label[PALETTE_MAX];
    CSBColorSpace palette_space[PALETTE_MAX];
    Boolean palette_color_dependent[PALETTE_MAX];
    Boolean palette_broken[PALETTE_MAX];
    String palette_function[PALETTE_MAX];

    XtCallbackList ok_callback;
    XtCallbackList apply_callback;
    XtCallbackList reset_callback;
    XtCallbackList cancel_callback;
    XtCallbackList face_select_callback;
    XtCallbackList value_changed_callback;

 /* Subwidgets */
    Widget form_child;
    Widget slider_child[4];
    Widget value_child[4];
    Widget label_child[4];
    Widget model_option_menu_child;
    Widget display_option_menu_child;
    Widget patch_child;
    Widget dock_child;
    Widget palette_option_menu_child;
    Widget palette_child;

 /* Private fields */

    Pixel background;
    Boolean static_visual;
    Boolean no_background;
    Boolean palette_pixmap_valid;
    int visual_class;
    DPSGState base_gstate;
    DPSGState patch_gstate;
    DPSGState dock_gstate;
    ColorRec current_color;
    ColorRec palette_color;
    ColorRec save_color;

    Pixmap red_pixmap;
    Pixmap green_pixmap;
    Pixmap blue_pixmap;
    Pixmap cyan_pixmap;
    Pixmap magenta_pixmap;
    Pixmap yellow_pixmap;
    Pixmap black_pixmap;
    Pixmap hue_pixmap;
    Pixmap sat_pixmap;
    Pixmap bright_pixmap;
    Pixmap gray_pixmap;

    Dimension rgb_slider_width;
    Dimension cmyk_slider_width;
    Dimension hsb_slider_width;
    Dimension gray_slider_width;

    float itransform[6];

    float *dock_cyan, *dock_magenta, *dock_yellow, *dock_black;
    Boolean *dock_used;
    Boolean dock_changed;

    Cursor eyedrop;
    Cursor square;
    Boolean eyedrop_grabbed;
} ColorSelectionBoxPart;

typedef struct _ColorSelectionBoxRec {
    CorePart			core;
    CompositePart		composite;
    ConstraintPart		constraint;
    XmManagerPart		manager;
    ColorSelectionBoxPart	csb;
} ColorSelectionBoxRec;

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/* Note use of Bool and double in prototypes:  this makes the library
   work correctly when linked with no-prototype compiled objects */

typedef Boolean (*CSBSetColorProc) (Widget w, CSBColorSpace space, double c1,
			     double c2, double c3, double c4, Bool setSpace);

typedef void (*CSBGetColorProc) (Widget w, CSBColorSpace space, float *c1,
			     float *c2, float *c3, float *c4);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#define InheritSetColor ((CSBSetColorProc) _XtInherit)
#define InheritGetColor ((CSBGetColorProc) _XtInherit)

typedef struct {
    CSBSetColorProc		set_color;
    CSBGetColorProc		get_color;
    XtPointer			extension;
} ColorSelectionBoxClassPart;

typedef struct _ColorSelectionBoxClassRec {
    CoreClassPart		core_class;
    CompositeClassPart		composite_class;
    ConstraintClassPart		constraint_class;
    XmManagerClassPart		manager_class;
    ColorSelectionBoxClassPart	csb_class;
} ColorSelectionBoxClassRec, *ColorSelectionBoxWidgetClass;

extern ColorSelectionBoxClassRec colorSelectionBoxClassRec;

#endif /* _ColorSelectionBoxP_H */
/* DON'T ADD ANYTHING AFTER THIS #endif */
