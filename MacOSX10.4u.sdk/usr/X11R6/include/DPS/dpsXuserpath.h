/*
 * dpsXuserpath.h
 *
 * (c) Copyright 1990-1994 Adobe Systems Incorporated.
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
/* $XFree86: xc/include/DPS/dpsXuserpath.h,v 1.2 2000/06/07 22:02:56 tsi Exp $ */

#ifndef DPS_X_DOUSERPATH_H
#define DPS_X_DOUSERPATH_H

#include <DPS/dpsXcommon.h>
#include <X11/Xlib.h>
#include <DPS/dpsconfig.h>

/* Should be 1 for high-order byte first, 0 for low-order byte first.  I can
   never rember which is big- and which is little-endian. */

typedef enum _DPSNumberFormat {
#if SWAPBITS == 1
    dps_float = 128+48,
    dps_long = 128,
    dps_short = 128+32
#else /* SWAPBITS */
    dps_float = 48,
    dps_long = 0,
    dps_short = 32
#endif /* SWAPBITS */
} DPSNumberFormat;

/* Constants for DPSDoUserPath describing what type of coordinates are
   being used.  Other legal values are:

   For 32-bit fixed point numbers, use dps_long plus the number of bits
   in the fractional part.

   For 16-bit fixed point numbers, use dps_short plus the number of bits
   in the fractional part.
*/
 
enum _DPSUserPathOp {
    dps_setbbox = 0,
    dps_moveto,
    dps_rmoveto,
    dps_lineto,
    dps_rlineto,
    dps_curveto,
    dps_rcurveto,
    dps_arc,
    dps_arcn,
    dps_arct,
    dps_closepath,
    dps_ucache
};

/* We count on the fact that this is a char, so can't put it in the above
   typedef. */

typedef char DPSUserPathOp;

typedef enum _DPSUserPathAction {
    dps_uappend = 176,
    dps_ufill = 179,
    dps_ueofill = 178,
    dps_ustroke = 183,
    dps_ustrokepath = 364,
    dps_inufill = 93,
    dps_inueofill = 92,
    dps_inustroke = 312,
    dps_infill = 90,
    dps_ineofill = 89,
    dps_instroke = 311,
    dps_def = 51,
    dps_put = 120,
    dps_send = 113	/* This is really the null operator */
} DPSUserPathAction;
 
#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

extern void PSDoUserPath(DPSPointer coords,
			 int numCoords,
			 DPSNumberFormat numType,
			 DPSUserPathOp *ops,
			 int numOp,
			 DPSPointer bbox,
			 DPSUserPathAction action);

extern void DPSDoUserPath(DPSContext ctx,
			  DPSPointer coords,
			  int numCoords,
			  DPSNumberFormat numType,
			  DPSUserPathOp *ops,
			  int numOp,
			  DPSPointer bbox,
			  DPSUserPathAction action);

extern Bool PSHitUserPath(double x, double y,
			  double radius,

			  DPSPointer coords,
			  int numCoords,
			  DPSNumberFormat numType,
			  DPSUserPathOp *ops,
			  int numOp,
			  DPSPointer bbox,
			  DPSUserPathAction action);

extern Bool DPSHitUserPath(DPSContext ctx,
			   double x, double y,
			   double radius,

			   DPSPointer coords,
			   int numCoords,
			   DPSNumberFormat numType,
			   DPSUserPathOp *ops,
			   int numOp,
			   DPSPointer bbox,
			   DPSUserPathAction action);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* DPS_X_DOUSERPATH_H */
