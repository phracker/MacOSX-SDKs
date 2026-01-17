/* 
 * ColorSB.h
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
/* $XFree86: xc/include/DPS/ColorSB.h,v 1.2 2000/06/07 22:02:54 tsi Exp $ */

#ifndef _ColorSelectionBox_h
#define _ColorSelectionBox_h

/* New resouce names and classes */

#define XtNcontext "context"
#define XtCContext "Context"
#define XtNrgbLabels "rgbLabels"
#define XtCRgbLabels "RgbLabels"
#define XtNcmykLabels "cmykLabels"
#define XtCCmykLabels "CmykLabels"
#define XtNhsbLabels "hsbLabels"
#define XtCHsbLabels "HsbLabels"
#define XtNgrayLabels "grayLabels"
#define XtCGrayLabels "GrayLabels"
#define XtNcellSize "cellSize"
#define XtCCellSize "CellSize"
#define XtNnumCells "numCells"
#define XtCNumCells "NumCells"
#define XtNfillMe "fillMe"
#define XtCFillMe "FillMe"
#define XtNcurrentSpace "currentSpace"
#define XtCCurrentSpace "CurrentSpace"
#define XtNcurrentRendering "currentRendering"
#define XtCCurrentRendering "CurrentRendering"
#define XtNcurrentPalette "currentPalette"
#define XtCCurrentPalette "CurrentPalette"
#define XtNbrokenPaletteLabel "brokenPaletteLabel"
#define XtCBrokenPaletteLabel "BrokenPaletteLabel"
#define XtNbrokenPaletteMessage "brokenPaletteMessage"
#define XtCBrokenPaletteMessage "BrokenPaletteMessage"

#define XtNpalette0Label "palette0Label"
#define XtNpalette0Space "palette0Space"
#define XtNpalette0ColorDependent "palette0ColorDependent"
#define XtNpalette0Function "palette0Function"
#define XtNpalette1Label "palette1Label"
#define XtNpalette1Space "palette1Space"
#define XtNpalette1ColorDependent "palette1ColorDependent"
#define XtNpalette1Function "palette1Function"
#define XtNpalette2Label "palette2Label"
#define XtNpalette2Space "palette2Space"
#define XtNpalette2ColorDependent "palette2ColorDependent"
#define XtNpalette2Function "palette2Function"
#define XtNpalette3Label "palette3Label"
#define XtNpalette3Space "palette3Space"
#define XtNpalette3ColorDependent "palette3ColorDependent"
#define XtNpalette3Function "palette3Function"
#define XtNpalette4Label "palette4Label"
#define XtNpalette4Space "palette4Space"
#define XtNpalette4ColorDependent "palette4ColorDependent"
#define XtNpalette4Function "palette4Function"
#define XtNpalette5Label "palette5Label"
#define XtNpalette5Space "palette5Space"
#define XtNpalette5ColorDependent "palette5ColorDependent"
#define XtNpalette5Function "palette5Function"
#define XtNpalette6Label "palette6Label"
#define XtNpalette6Space "palette6Space"
#define XtNpalette6ColorDependent "palette6ColorDependent"
#define XtNpalette6Function "palette6Function"
#define XtNpalette7Label "palette7Label"
#define XtNpalette7Space "palette7Space"
#define XtNpalette7ColorDependent "palette7ColorDependent"
#define XtNpalette7Function "palette7Function"
#define XtNpalette8Label "palette8Label"
#define XtNpalette8Space "palette8Space"
#define XtNpalette8ColorDependent "palette8ColorDependent"
#define XtNpalette8Function "palette8Function"
#define XtNpalette9Label "palette9Label"
#define XtNpalette9Space "palette9Space"
#define XtNpalette9ColorDependent "palette9ColorDependent"
#define XtNpalette9Function "palette9Function"

#define XtCPaletteLabel "PaletteLabel"
#define XtCPaletteSpace "PaletteSpace"
#define XtCPaletteColorDependent "PaletteColorDependent"
#define XtCPaletteFunction "PaletteFunction"

#define XtNokCallback "okCallback"
#define XtNapplyCallback "applyCallback"
#define XtNresetCallback "resetCallback"
#ifndef XtNcancelCallback
#define XtNcancelCallback "cancelCallback"
#endif
#define XtNvalueChangedCallback "valueChangedCallback"

/* New resource types */

#define XtRDPSContext "DPSContext"
#define XtRColorSpace "CSBColorSpace"
#define XtRRenderingType "CSBRenderingType"

typedef enum {CSBSpaceRGB, CSBSpaceCMYK, CSBSpaceHSB,
	      CSBSpaceGray} CSBColorSpace;
typedef enum {CSBDisplayX, CSBDisplayDPS, CSBDisplayBoth} CSBRenderingType;
typedef enum {CSBOK, CSBApply, CSBReset,
	      CSBCancel, CSBValueChanged} CSBCallbackReason;

typedef struct {
    CSBCallbackReason reason;
    CSBColorSpace current_space;
    float red, green, blue;
    float cyan, magenta, yellow, black;
    float hue, saturation, brightness;
    float gray;
} CSBCallbackRec;

/* Class record constants */

extern WidgetClass colorSelectionBoxWidgetClass;

typedef struct _ColorSelectionBoxRec *ColorSelectionBoxWidget;

/* Convenience routine */

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/* Note use of Bool and double in prototypes:  this makes the library
   work correctly when linked with no-prototype compiled objects */

extern Boolean CSBSetColor(Widget w, CSBColorSpace space, double c1,
			double c2, double c3, double c4, Bool setSpace);

extern void CSBGetColor(Widget w, CSBColorSpace space, float *c1,
			float *c2, float *c3, float *c4);

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" }
#endif

#endif /* _ColorSelectionBox_h */
/* DON'T ADD ANYTHING AFTER THIS #endif */
