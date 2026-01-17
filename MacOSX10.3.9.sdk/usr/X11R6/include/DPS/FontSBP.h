/* 
 * FontSBP.h
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
/* $XFree86: xc/include/DPS/FontSBP.h,v 1.2 2000/06/07 22:02:55 tsi Exp $ */

#ifndef _FontSelectionBoxP_H
#define _FontSelectionBoxP_H

#include <DPS/FontSB.h>

/* Typedefs used in private fields */

#define MAX_AXES 4
#define MAX_BLENDS 16	/* = 2**MAX_AXES */

typedef struct _BlendRec {
    char *blend_name;
    char *font_name;
    XmString CS_blend_name;
    XmString CS_space_blend_name;
    float data[MAX_AXES];
    struct _BlendRec *next;
} BlendRec;

typedef struct {
    int num_axes, num_designs;
    int min[MAX_AXES], max[MAX_AXES];
    String name[MAX_AXES];
    int internal_points[MAX_AXES];
    int *internal_break[MAX_AXES];
    float *internal_value[MAX_AXES];
    float *design_positions;
    BlendRec *blends;
} BlendDataRec;

typedef struct _FontRec {
    char *font_name;
    char *face_name;
    XmString CS_face_name;
    char *full_name;
    Boolean resident;
    Boolean temp_resident;
    struct _FontRec *pending_delete_next;
    struct _FontRec *next;
    int blend_count;
    Boolean in_font_creator;
    BlendDataRec *blend_data;
} FontRec;

typedef struct _FontFamilyRec {
    char *family_name;
    char *sort_key;
    FontRec *fonts;
    int font_count;
    struct _FontFamilyRec *next;
    int blend_count;
} FontFamilyRec;

typedef struct {
    DPSContext context;
    String preview_string;
    float *sizes;
    int size_count;
    String default_resource_path;
    String resource_path_override;
    String font_name;
    String font_family;
    String font_face;
    float font_size;
    Boolean use_font_name;
    Boolean font_name_multiple;
    Boolean font_family_multiple;
    Boolean font_face_multiple;
    Boolean font_size_multiple;
    Boolean get_server_fonts;
    Boolean get_afm;
    Boolean auto_preview;
    Boolean preview_on_change;
    Boolean undef_unused_fonts;
    Boolean make_fonts_shared;
    Boolean show_sampler;
    Boolean show_sampler_button;
    Cardinal max_pending_deletes;
    XtCallbackList ok_callback;
    XtCallbackList apply_callback;
    XtCallbackList reset_callback;
    XtCallbackList cancel_callback;
    XtCallbackList validate_callback;
    XtCallbackList face_select_callback;
    XtCallbackList create_sampler_callback;
    Widget pane_child;
    Widget preview_child;
    Widget panel_child;
    Widget family_label_child;
    Widget family_multiple_label_child;
    Widget family_scrolled_list_child;
    Widget face_label_child;
    Widget face_multiple_label_child;
    Widget face_scrolled_list_child;
    Widget size_label_child;
    Widget size_text_field_child;
    Widget size_option_menu_child;
    Widget size_multiple_label_child;
    Widget sampler_button_child;
    Widget preview_button_child;
    Widget separator_child;
    Widget ok_button_child;
    Widget apply_button_child;
    Widget reset_button_child;
    Widget cancel_button_child;

 /* Private fields */

    DPSGState gstate;
    Widget other_size;
    Widget size_menu;
    Widget sampler;
    FontFamilyRec *known_families;
    int family_count;
    Boolean preview_fixed;
    Boolean current_family_multiple, current_face_multiple;
    Boolean current_size_multiple;
    FontRec *pending_delete_font;
    int pending_delete_count;
    FontRec *currently_previewed;
    FontRec *currently_selected_face;
    FontFamilyRec *currently_selected_family;
    float currently_previewed_size;
    float currently_selected_size;

 /* New resource fields */

    String font_blend;
    Boolean typographic_sort;
    XtCallbackList create_creator_callback;
    XtCallbackList value_changed_callback;
    Widget multiple_master_button_child;

 /* New private fields */

    Widget creator, creator_shell;
    BlendRec *currently_previewed_blend;
    BlendRec *currently_selected_blend;
    Boolean blends_changed;
    Boolean old_server;
} FontSelectionBoxPart;

typedef struct _FontSelectionBoxRec {
    CorePart			core;
    CompositePart		composite;
    ConstraintPart		constraint;
    XmManagerPart		manager;
    FontSelectionBoxPart	fsb;
} FontSelectionBoxRec;

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/* Note use of Bool and double in prototypes:  this makes the library
   work correctly when linked with no-prototype compiled objects */

typedef void (*FSBSetFontNameProc) (Widget w,
				    String font_name,
				    Bool font_name_multiple);

typedef void (*FSBSetFontFamilyFaceProc) (Widget w,
					  String font_family,
					  String font_face,
					  Bool font_family_multiple,
					  Bool font_face_multiple);

typedef void (*FSBSetFontSizeProc) (Widget w,
				    double font_size,
				    Bool font_size_multiple);

typedef void (*FSBRefreshFontListProc) (Widget w);

typedef void (*FSBGetFamilyListProc) (Widget w, int *count_return,
				      String **family_return);

typedef void (*FSBGetFaceListProc) (Widget w, String family, int *count_return,
				    String **face_return,
				    String **font_return);

typedef void (*FSBUndefUnusedFontsProc) (Widget w);

typedef Boolean (*FSBDownloadFontNameProc) (Widget w, String font_name);

typedef Boolean (*FSBMatchFontFaceProc) (Widget w, String old_face,
					 String new_family, String *new_face);

typedef void (*FSBFontNameToFamilyFaceProc) (Widget w, String font_name,
					     String *family, String *face);

typedef void (*FSBFontFamilyFaceToNameProc) (Widget w, String family,
					     String face, String *font_name);

typedef String (*FSBFindAFMProc) (Widget w, String font_name);

typedef String (*FSBFindFontFileProc) (Widget w, String font_name);

typedef void (*FSBGetTextDimensionsProc) (Widget w, String text, String font,
					  double size, double x, double y,
					  float *dx, float *dy,
					  float *left, float *right,
					  float *top, float *bottom);

typedef void (*FSBSetFontFamilyFaceBlendProc) (Widget w,
					       String font_family,
					       String font_face,
					       String font_blend,
					       Bool font_family_multiple,
					       Bool font_face_multiple);
typedef void (*FSBFontNameToFamilyFaceBlendProc) (Widget w, String font_name,
						  String *family, String *face,
						  String *blend);
typedef void (*FSBFontFamilyFaceBlendToNameProc) (Widget w, String family,
						  String face, String blend,
						  String *font_name);
typedef void (*FSBGetBlendListProc) (Widget w, String name,
				     int *count_return, String **blend_return,
				     String **font_name_return,
				     float **axis_values_return);
typedef void (*FSBGetBlendInfoProc) (Widget w, String name,
				     int *num_axes_return,
				     int *num_designs_return,
				     String **axis_names_return, 
				     float **blend_positions_return,
				     int **blend_map_count_return,
				     int **blend_design_coords_return,
				     float **blend_normalized_coords_return);
typedef Boolean (*FSBChangeBlendsProc) (Widget w, String base_name,
					String blend_name,
					FSBBlendAction action,
					int *axis_values,
					float *axis_percents);
#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#define InheritSetFontName ((FSBSetFontNameProc) _XtInherit)
#define InheritSetFontFamilyFace ((FSBSetFontFamilyFaceProc) _XtInherit)
#define InheritSetFontSize ((FSBSetFontSizeProc) _XtInherit)
#define InheritRefreshFontList ((FSBRefreshFontListProc) _XtInherit)
#define InheritGetFamilyList ((FSBGetFamilyListProc) _XtInherit)
#define InheritGetFaceList ((FSBGetFaceListProc) _XtInherit)
#define InheritUndefUnusedFonts ((FSBUndefUnusedFontsProc) _XtInherit)
#define InheritDownloadFontName ((FSBDownloadFontNameProc) _XtInherit)
#define InheritMatchFontFace ((FSBMatchFontFaceProc) _XtInherit)
#define InheritFontNameToFamilyFace ((FSBFontNameToFamilyFaceProc) _XtInherit)
#define InheritFontFamilyFaceToName ((FSBFontFamilyFaceToNameProc) _XtInherit)
#define InheritFindAFM ((FSBFindAFMProc) _XtInherit)
#define InheritFindFontFile ((FSBFindFontFileProc) _XtInherit)
#define InheritGetTextDimensions ((FSBGetTextDimensionsProc) _XtInherit)
#define InheritSetFontFamilyFaceBlend \
	((FSBSetFontFamilyFaceBlendProc) _XtInherit)
#define InheritFontNameToFamilyFaceBlend  \
	((FSBFontNameToFamilyFaceBlendProc) _XtInherit)
#define InheritFontFamilyFaceBlendToName \
	((FSBFontFamilyFaceBlendToNameProc) _XtInherit)
#define InheritGetBlendList ((FSBGetBlendListProc) _XtInherit)
#define InheritGetBlendInfo ((FSBGetBlendInfoProc) _XtInherit)
#define InheritChangeBlends ((FSBChangeBlendsProc) _XtInherit)

typedef struct {
    FSBSetFontNameProc		set_font_name;
    FSBSetFontFamilyFaceProc	set_font_family_face;
    FSBSetFontSizeProc		set_font_size;
    FSBRefreshFontListProc	refresh_font_list;
    FSBGetFamilyListProc	get_family_list;
    FSBGetFaceListProc		get_face_list;
    FSBUndefUnusedFontsProc	undef_unused_fonts;
    FSBDownloadFontNameProc	download_font_name;
    FSBMatchFontFaceProc	match_font_face;
    FSBFontNameToFamilyFaceProc font_name_to_family_face;
    FSBFontFamilyFaceToNameProc font_family_face_to_name;
    FSBFindAFMProc		find_afm;
    FSBFindFontFileProc		find_font_file;
    FSBGetTextDimensionsProc	get_text_dimensions;
    FSBSetFontFamilyFaceBlendProc	set_font_family_face_blend;
    FSBFontNameToFamilyFaceBlendProc	font_name_to_family_face_blend;
    FSBFontFamilyFaceBlendToNameProc	font_family_face_blend_to_name;
    FSBGetBlendListProc		get_blend_list;
    FSBGetBlendInfoProc		get_blend_info;
    FSBChangeBlendsProc		change_blends;
    XtPointer			extension;
} FontSelectionBoxClassPart;

typedef struct _FontSelectionBoxClassRec {
    CoreClassPart		core_class;
    CompositeClassPart		composite_class;
    ConstraintClassPart		constraint_class;
    XmManagerClassPart		manager_class;
    FontSelectionBoxClassPart	fsb_class;
} FontSelectionBoxClassRec, *FontSelectionBoxWidgetClass;

extern FontSelectionBoxClassRec fontSelectionBoxClassRec;

#endif /* _FontSelectionBoxP_H */
/* DON'T ADD ANYTHING AFTER THIS #endif */
