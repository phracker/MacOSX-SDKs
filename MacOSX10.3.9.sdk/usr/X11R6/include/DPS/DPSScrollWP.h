/* 
 * DPSScrollWP.h
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
/* $XFree86: xc/include/DPS/DPSScrollWP.h,v 1.2 2000/06/07 22:02:54 tsi Exp $ */

#ifndef _DPSScrolledWindowP_H
#define _DPSScrolledWindowP_H

#include <DPS/DPSScrollW.h>

typedef enum {DSWStart, DSWDrawingVisible, DSWDrewVisible,
	      DSWDrawingBackground, DSWDone} DSWDrawingStage;

typedef struct {
 /* Resources */
    DPSContext context;
    int area_width;
    int area_height;
    float scale;
    float *ctm_ptr;
    float *inv_ctm_ptr;
    Pixmap backing_pixmap;
    Pixmap feedback_pixmap;
    DPSGState window_gstate;
    DPSGState backing_gstate;
    DPSGState feedback_gstate;
    float *dirty_areas;
    short num_dirty_areas;
    int pixmap_limit;
    int absolute_pixmap_limit;
    int watch_progress_delay;
    Boolean use_backing_pixmap;
    Boolean use_feedback_pixmap;
    Boolean watch_progress;
    Boolean minimal_drawing;
    Boolean document_size_pixmaps;
    Boolean application_scrolling;

    XtCallbackList setup_callback;
    XtCallbackList expose_callback;
    XtCallbackList background_callback;
    XtCallbackList feedback_callback;
    XtCallbackList resize_callback;

 /* Subwidgets */

    Widget scrolled_window;
    Widget h_scroll;
    Widget v_scroll;
    Widget drawing_area;

 /* Private fields */
    float ctm[6];
    float orig_inv_ctm[6];
    float inv_ctm[6];
    int x_offset, y_offset;
    int feedback_width, feedback_height;
    float drawing_width, drawing_height;  /* scaled drawing size in X coords */
    int unscaled_width, unscaled_height;
    int pixmap_width, pixmap_height;
    float scroll_pic_x, scroll_pic_y;
    int scroll_win_x, scroll_win_y;
    int scroll_x, scroll_y;
    int scroll_h_value, scroll_v_value;	/* These may be virtual */
    int scroll_h_size, scroll_v_size;
    int scroll_h_max, scroll_v_max;
    int origin_x, origin_y;		/* origin loc. relative to X offset */
    int *pending_expose;
    short num_pending_expose;
    short pending_expose_size;
    float *pending_dirty;
    short num_pending_dirty;
    short pending_dirty_size;
    float *current_drawing;
    short num_current_drawing;
    short current_drawing_size;
    short dirty_areas_size;
    float *prev_dirty_areas;
    short prev_dirty_areas_size;
    short num_prev_dirty_areas;
    float *scratch;			/* To avoid reallocating buffers */
    short num_scratch;
    short scratch_size;
    GC ge_gc;				/* Generates GraphicsExposes on copy */
    GC no_ge_gc;			/* Generates no GraphicsExposes */
    XtWorkProcId work;
    XtPointer start_feedback_data;
    XtPointer continue_feedback_data;
    DSWDrawingStage drawing_stage;
    Boolean use_saved_scroll;
    Boolean context_inited;
    Boolean doing_feedback;
    Boolean feedback_displayed;
    Boolean big_pixmap;		/* Is the pixmap larger than the window? */
    Boolean scrolling;
} DPSScrolledWindowPart;

typedef struct _DPSScrolledWindowRec {
    CorePart			core;
    CompositePart		composite;
    ConstraintPart		constraint;
    XmManagerPart		manager;
    DPSScrolledWindowPart	sw;
} DPSScrolledWindowRec;

/* Here's a list of the various rectangle lists we use in the widget and
   what they're for.  In all cases _size is the number of slots in the
   list, and num_ is the number of slots currently in use.

   dirty_areas:  A list of all areas of the drawing that either need to
   be drawn or are in the process of being drawn.

   prev_dirty_areas:  Used as a buffer during feedback drawing.

   current_drawing:  A list of all areas of the drawing that are currently
   being drawn.  This is the view clip for any calls to the expose callback.

   pending_dirty:  A list of all areas for which exposures have arrived
   since drawing was begun.  This is only maintained if drawing is
   being done to the window (either watch progress is on, or there is no
   backing pixmap, or we're doing feedback without a feedback pixmap).

   pending_expose:  Same areas as pending_dirty, but kept in X coordinates.
   This is always maintained.

   scratch:  Used to hold temporary copies of rectangle lists.
*/

#if defined(__cplusplus) || defined(c_plusplus)
typedef "C" {
#endif

/* Note use of long and double in prototypes:  this makes the library
   work correctly when linked with no-prototype compiled objects */

typedef void (*DSWSetScaleProc) (Widget w, double scale,
				 long fixedX, long fixedY);
typedef void (*DSWScrollPointProc) (Widget w, double psX, double psY,
				    long xX, long xY);
typedef void (*DSWScrollByProc) (Widget w, long dx, long dy);
typedef void (*DSWScrollToProc) (Widget w, long x, long y);
typedef void (*DSWSetScaleAndScrollProc) (Widget w, double scale,
					  double psX, double psY,
					  long xX, long xY);
typedef void (*DSWConvertXToPSProc) (Widget w, long xX, long xY,
				     float *psX, float *psY);
typedef void (*DSWConvertPSToXProc) (Widget w, double psX, double psY,
				     int *xX, int *xY);
typedef void (*DSWAddToDirtyAreaProc) (Widget w, float *rect, long n);
typedef Boolean (*DSWTakeFeedbackPixmapProc) (Widget w, Pixmap *p,
					      int *width, int *height,
					      int *depth, Screen **screen);
typedef Boolean (*DSWGiveFeedbackPixmapProc) (Widget w, Pixmap p,
					      int width, int height,
					      int depth, Screen *screen);
typedef void (*DSWStartFeedbackDrawingProc) (Widget w,
					     XtPointer start_feedback_data);
typedef void (*DSWEndFeedbackDrawingProc) (Widget w, Bool restore_window);
typedef void (*DSWSetFeedbackDirtyAreaProc) (Widget w, float *rects, int count,
					     XtPointer continue_feedback_data);
typedef void (*DSWFinishPendingDrawingProc) (Widget w);
typedef void (*DSWAbortPendingDrawingProc) (Widget w);
typedef void (*DSWGetDrawingInfoProc) (Widget w, DSWDrawableType *type,
	      Drawable *drawable, DPSGState *gstate, DPSContext *context);
typedef void (*DSWUpdateDrawingProc) (Widget w, float *rects, int count);
typedef void (*DSWGetScrollInfoProc) (Widget w, int *h_value, int *h_size,
				      int *h_max, int *v_value, int *v_size,
				      int *v_max);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#define InheritSetScale ((DSWSetScaleProc) _XtInherit)
#define InheritScrollPoint ((DSWScrollPointProc) _XtInherit)
#define InheritScrollBy ((DSWScrollByProc) _XtInherit)
#define InheritScrollTo ((DSWScrollToProc) _XtInherit)
#define InheritSetScaleAndScroll ((DSWSetScaleAndScrollProc) _XtInherit)
#define InheritConvertXToPS ((DSWConvertXToPSProc) _XtInherit)
#define InheritConvertPSToX ((DSWConvertPSToXProc) _XtInherit)
#define InheritAddToDirtyArea ((DSWAddToDirtyAreaProc) _XtInherit)
#define InheritTakeFeedbackPixmap ((DSWTakeFeedbackPixmapProc) _XtInherit)
#define InheritGiveFeedbackPixmap ((DSWGiveFeedbackPixmapProc) _XtInherit)
#define InheritStartFeedbackDrawing ((DSWStartFeedbackDrawingProc) _XtInherit)
#define InheritEndFeedbackDrawing ((DSWEndFeedbackDrawingProc) _XtInherit)
#define InheritSetFeedbackDirtyArea ((DSWSetFeedbackDirtyAreaProc) _XtInherit)
#define InheritFinishPendingDrawing ((DSWFinishPendingDrawingProc) _XtInherit)
#define InheritAbortPendingDrawing ((DSWAbortPendingDrawingProc) _XtInherit)
#define InheritGetDrawingInfo ((DSWGetDrawingInfoProc) _XtInherit)
#define InheritUpdateDrawing ((DSWUpdateDrawingProc) _XtInherit)
#define InheritGetScrollInfo ((DSWGetScrollInfoProc) _XtInherit)

typedef struct {
    DSWSetScaleProc		set_scale;
    DSWScrollPointProc		scroll_point;
    DSWScrollByProc		scroll_by;
    DSWScrollToProc		scroll_to;
    DSWSetScaleAndScrollProc	set_scale_and_scroll;
    DSWConvertXToPSProc		convert_x_to_ps;
    DSWConvertPSToXProc		convert_ps_to_x;
    DSWAddToDirtyAreaProc	add_to_dirty_area;
    DSWTakeFeedbackPixmapProc	take_feedback_pixmap;
    DSWGiveFeedbackPixmapProc	give_feedback_pixmap;
    DSWStartFeedbackDrawingProc	start_feedback_drawing;
    DSWEndFeedbackDrawingProc	end_feedback_drawing;
    DSWSetFeedbackDirtyAreaProc	set_feedback_dirty_area;
    DSWFinishPendingDrawingProc	finish_pending_drawing;
    DSWAbortPendingDrawingProc	abort_pending_drawing;
    DSWGetDrawingInfoProc	get_drawing_info;
    DSWUpdateDrawingProc	update_drawing;
    DSWGetScrollInfoProc	get_scroll_info;
    XtPointer			extension;
} DPSScrolledWindowClassPart;

typedef struct _DPSScrolledWindowClassRec {
    CoreClassPart		core_class;
    CompositeClassPart		composite_class;
    ConstraintClassPart		constraint_class;
    XmManagerClassPart		manager_class;
    DPSScrolledWindowClassPart	sw_class;
} DPSScrolledWindowClassRec, *DPSScrolledWindowWidgetClass;

extern DPSScrolledWindowClassRec dpsScrolledWindowClassRec;

#endif /* _DPSScrolledWindowP_H */
/* DON'T ADD ANYTHING AFTER THIS #endif */
