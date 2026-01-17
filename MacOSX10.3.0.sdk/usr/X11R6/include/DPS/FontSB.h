/* 
 * FontSB.h
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
/* $XFree86: xc/include/DPS/FontSB.h,v 1.2 2000/06/07 22:02:54 tsi Exp $ */

#ifndef _FontSelectionBox_h
#define _FontSelectionBox_h

/* New resouce names and classes */

#define XtNcontext "context"
#define XtCContext "Context"
#define XtNpreviewString "previewString"
#define XtCPreviewString "PreviewString"
#define XtNsizes "sizes"
#define XtCSizes "Sizes"
#define XtNsizeCount "sizeCount"
#define XtCSizeCount "SizeCount"
#define XtNdefaultResourcePath "defaultResourcePath"
#define XtCDefaultResourcePath "DefaultResourcePath"
#define XtNresourcePathOverride "resourcePathOverride"
#define XtCResourcePathOverride "ResourcePathOverride"
#define XtNuseFontName "useFontName"
#define XtCUseFontName "UseFontName"
#define XtNfontName "fontName"
#define XtCFontName "FontName"
#define XtNfontFamily "fontFamily"
#define XtCFontFamily "FontFamily"
#define XtNfontFace "fontFace"
#define XtCFontFace "FontFace"
#define XtNfontSize "fontSize"
#define XtCFontSize "FontSize"
#define XtNfontBlend "fontBlend"
#define XtCFontBlend "FontBlend"
#define XtNfontNameMultiple "fontNameMultiple"
#define XtCFontNameMultiple "FontNameMultiple"
#define XtNfontFamilyMultiple "fontFamilyMultiple"
#define XtCFontFamilyMultiple "FontFamilyMultiple"
#define XtNfontFaceMultiple "fontFaceMultiple"
#define XtCFontFaceMultiple "FontFaceMultiple"
#define XtNfontSizeMultiple "fontSizeMultiple"
#define XtCFontSizeMultiple "FontSizeMultiple"
#define XtNgetServerFonts "getServerFonts"
#define XtCGetServerFonts "GetServerFonts"
#define XtNgetAFM "getAFM"
#define XtCGetAFM "GetAFM"
#define XtNautoPreview "autoPreview"
#define XtCAutoPreview "AutoPreview"
#define XtNpreviewOnChange "previewOnChange"
#define XtCPreviewOnChange "PreviewOnChange"
#define XtNundefUnusedFonts "undefUnusedFonts"
#define XtCUndefUnusedFonts "UndefUnusedFonts"
#define XtNmaxPendingDeletes "maxPendingDeletes"
#define XtCMaxPendingDeletes "MaxPendingDeletes"
#define XtNmakeFontsShared "makeFontsShared"
#define XtCMakeFontsShared "MakeFontsShared"
#define XtNshowSampler "showSampler"
#define XtCShowSampler "ShowSampler"
#define XtNshowSamplerButton "showSamplerButton"
#define XtCShowSamplerButton "ShowSamplerButton"
#define XtNtypographicSort "typographicSort"
#define XtCTypographicSort "TypographicSort"
#define XtNokCallback "okCallback"
#define XtNapplyCallback "applyCallback"
#define XtNresetCallback "resetCallback"
#ifndef XtNcancelCallback
#define XtNcancelCallback "cancelCallback"
#endif
#define XtNvalidateCallback "validateCallback"
#define XtNfaceSelectCallback "faceSelectCallback"
#define XtNvalueChangedCallback "valueChangedCallback"
#define XtNcreateSamplerCallback "createSamplerCallback"
#define XtNcreateCreatorCallback "createCreatorCallback"

/* Read-only resources for all the subwidgets */

#define XtNpaneChild "paneChild"
#define XtNpreviewChild "previewChild"
#define XtNpanelChild "panelChild"
#define XtNfamilyLabelChild "familyLabelChild"
#define XtNfamilyMultipleLabelChild "familyMultipleLabelChild"
#define XtNfamilyScrolledListChild "familyScrolledListChild"
#define XtNfaceLabelChild "faceLabelChild"
#define XtNfaceMultipleLabelChild "faceMultipleLabelChild"
#define XtNfaceScrolledListChild "faceScrolledListChild"
#define XtNsizeLabelChild "sizeLabelChild"
#define XtNsizeTextFieldChild "sizeTextFieldChild"
#define XtNsizeOptionMenuChild "sizeOptionMenuChild"
#define XtNsizeMultipleLabelChild "sizeMultipleLabelChild"
#define XtNsamplerButtonChild "samplerButtonChild"
#define XtNpreviewButtonChild "previewButtonChild"
#define XtNseparatorChild "separatorChild"
#define XtNokButtonChild "okButtonChild"
#define XtNapplyButtonChild "applyButtonChild"
#define XtNresetButtonChild "resetButtonChild"
#define XtNcancelButtonChild "cancelButtonChild"
#define XtNmultipleMasterButtonChild "multipleMasterButtonChild"

/* New resource types */

#define XtRFloatList "FloatList"
#define XtRDPSContext "DPSContext"

/* Class record constants */

extern WidgetClass fontSelectionBoxWidgetClass;

typedef struct _FontSelectionBoxRec *FontSelectionBoxWidget;

typedef enum {FSBNone, FSBOne, FSBMultiple} FSBSelectionType;
typedef enum {FSBOK, FSBApply, FSBReset, FSBCancel,
	      FSBValueChanged} FSBCallbackReason;

typedef struct {
    FSBCallbackReason reason;
    String family;
    String face;
    float size;
    String name;
    String afm_filename;
    FSBSelectionType family_selection;
    FSBSelectionType face_selection;
    FSBSelectionType size_selection;
    FSBSelectionType name_selection;
    Boolean afm_present;
    Boolean unused;
    String blend;
    String base_name;
    float axis_percent[4];
} FSBCallbackRec;

typedef struct {
    FSBCallbackReason reason;
    String family;
    String face;
    float size;
    String name;
    String afm_filename;
    FSBSelectionType family_selection;
    FSBSelectionType face_selection;
    FSBSelectionType size_selection;
    FSBSelectionType name_selection;
    Boolean afm_present;
    Boolean doit;
    String blend;
    String base_name;
    float axis_percent[4];
} FSBValidateCallbackRec;

typedef struct {
    String *available_faces;
    int num_available_faces;
    String current_face;
    String new_face;
} FSBFaceSelectCallbackRec;

typedef struct {
    Widget sampler;
    Widget sampler_shell;
} FSBCreateSamplerCallbackRec;

typedef struct {
    Widget creator;
    Widget creator_shell;
} FSBCreateCreatorCallbackRec;

typedef enum {FSBAddBlend, FSBReplaceBlend, FSBDeleteBlend} FSBBlendAction;

/* Convenience and info routines */

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/* Note use of Bool and double in prototypes:  this makes the library
   work correctly when linked with no-prototype compiled objects */

extern void FSBSetFontName(Widget w,
			   String font_name,
			   Bool font_name_multiple);

extern void FSBSetFontFamilyFace(Widget w,
				 String font_family, String font_face,
				 Bool font_family_multiple,
				 Bool font_face_multiple);

extern void FSBSetFontSize(Widget w, double font_size,
			   Bool font_size_multiple);

extern void FSBRefreshFontList(Widget w);

extern void FSBGetFamilyList(Widget w, int *count_return,
			     String **family_return);

extern void FSBGetFaceList(Widget w, String family, int *count_return,
		      String **face_return, String **font_return);

extern void FSBUndefineUnusedFonts(Widget w);

extern Boolean FSBDownloadFontName(Widget w, String font_name);

extern Boolean FSBMatchFontFace(Widget w, String old_face, String new_family,
				String *new_face);

extern void FSBFontNameToFamilyFace(Widget w, String font_name,
				    String *family, String *face);

extern void FSBFontFamilyFaceToName(Widget w, String family, String face,
				    String *font_name);

extern String FSBFindAFM(Widget w, String font_name);

extern String FSBFindFontFile(Widget w, String font_name);

extern void FSBGetTextDimensions(Widget w, String text, String font,
				 double size, double x, double y,
				 float *dx, float *dy,
				 float *left, float *right,
				 float *top, float *bottom);

extern void FSBSetFontFamilyFaceBlend(Widget w, String family, String face,
				      String blend, Bool family_multiple,
				      Bool face_multiple);

extern void FSBFontNameToFamilyFaceBlend(Widget w, String font_name,
					 String *family, String *face,
					 String *blend);

extern void FSBFontFamilyFaceBlendToName(Widget w, String family, String face,
					 String blend, String *font_name);

extern void FSBGetBlendList(Widget w, String font_name, int *count_return,
			    String **blend_return, String **font_name_return,
			    float **axis_values_return);

extern void FSBGetBlendInfo(Widget w, String name, int *num_axes_return,
			    int *num_designs_return,
			    String **axis_names_return,
			    float **blend_positions_return, 
			    int **blend_map_count_return, 
			    int **blend_design_coords_return,
			    float **blend_normalized_coords_return);

extern Boolean FSBChangeBlends(Widget w, String base_name, String blend_name,
			       FSBBlendAction action, int *axis_values,
			       float *axis_percents);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* _FontSelectionBox_h */
/* DON'T ADD ANYTHING AFTER THIS #endif */
