/*
 * dpsXshare.h
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
/* $XFree86: xc/include/DPS/dpsXshare.h,v 1.2 2000/06/07 22:02:55 tsi Exp $ */

#ifndef DPS_X_SHARE_H
#define DPS_X_SHARE_H

#include <DPS/dpsXcommon.h>

/* We have to duplicate this to make the _mult fields signed */

typedef struct {
	Colormap colormap;
	unsigned int red_max;
	int red_mult;
	unsigned int green_max;
	int green_mult;
	unsigned int blue_max;
	int blue_mult;
	unsigned int base_pixel;
	unsigned int visualid;
	unsigned int killid;
} XDPSStandardColormap;

typedef unsigned int DPSGState;

#define XDPSContextScreenDepth		(1L<<0)
#define XDPSContextDrawable		(1L<<1)
#define XDPSContextRGBMap		(1L<<2)
#define XDPSContextGrayMap		(1L<<3)

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/* XDPSRegisterContext registers a DPS context with the context sharing
   mangager and enables manipulation of the context through the other
   procedures in this module.  The makeSharedContext parameter establishes
   whether or not the context will be made the shared context for its
   display.  It does not destroy the previous shared context for the
   display, if any.
*/

extern void XDPSRegisterContext(DPSContext context,
				Bool makeSharedContext);

/* XDPSGetSharedContext returns the shared context for its display.  If no
   shared context exists, it creates one.  XDPSGetSharedContext returns NULL
   if the display does not support the DPS extension.  The context is
   initially set to use the default colormap on the default screen with the
   default depth, but is not set to use any drawable.
*/

extern DPSContext XDPSGetSharedContext(Display *display);

/* XDPSDestroySharedContext destroys the shared context for a display.
*/

extern void XDPSDestroySharedContext(DPSContext context);

/* XDPSUnregisterContext frees the context information but doesn't destroy
   the context.
*/

extern void XDPSUnregisterContext(DPSContext context);

/* XDPSFreeDisplayInfo frees the stored display info for a display */

extern void XDPSFreeDisplayInfo(Display *display);

/* XDPSChainTextContext either enables or disables a chained text context
   for a context.  The context must be registered.  The text context will
   be created automatically.
*/

extern int XDPSChainTextContext(DPSContext context,
				Bool enable);

/* XDPSSetContextDepth sets a context for use with a particular screen 
   and depth.
*/

extern int XDPSSetContextDepth(DPSContext context,
			       Screen *screen,
			       int depth);

/* XDPSSetContextDrawable sets a context for use with a particular
   drawable.  The origin is at the lower left corner.
*/

extern int XDPSSetContextDrawable(DPSContext context,
				  Drawable drawable,
				  int height);

/* XDPSSetContextRGBMap sets the RGB map for the context.  The colormap in
   the structure must be appropriate for the current drawable and depth.
   A colormap value of None is allowed when imaging into a pixmap, but the
   ramps must be set to the same values as will be used in the window that
   will ultimately show the pixmap.
*/

extern int XDPSSetContextRGBMap(DPSContext context,
				XDPSStandardColormap *map);

/* XDPSSetContextGrayMap sets the gray map for the context.  The colormap in
   the structure must be appropriate for the current drawable and depth.
   A colormap value of None is allowed when imaging into a pixmap, but the
   ramp must be set to the same values as will be used in the window that
   will ultimately show the pixmap.
*/

extern int XDPSSetContextGrayMap(DPSContext context,
				 XDPSStandardColormap *map);

/* XDPSSetContextParameters sets any of the context parameters.  The flags
   should be a combination of XDPSContextScreenDepth, XDPSContextDrawable,
   XDPSContextRGBMap, and XDPSContextGrayMap.
*/

extern int XDPSSetContextParameters(DPSContext context,
				    Screen *screen,
				    int depth,
				    Drawable drawable,
				    int height,
				    XDPSStandardColormap *rgbMap,
				    XDPSStandardColormap *grayMap,
				    unsigned int flags);

/* XDPSPushContextParameters is identical to XDPSSetContextParameters, but it
   can be undone by passing the returned pushCookieReturn to
   XDPSPopContextParameters.  It is up to the caller to make sure that push
   and pop are called in a stack-oriented fashion.
*/

extern int XDPSPushContextParameters(DPSContext context,
				     Screen *screen,
				     int depth,
				     Drawable drawable,
				     int height,
				     XDPSStandardColormap *rgbMap,
				     XDPSStandardColormap *grayMap,
				     unsigned int flags,
				     DPSPointer *pushCookieReturn);

extern int XDPSPopContextParameters(DPSPointer pushCookie);

/* XDPSCaptureContextGState captures the current graphics state as a gstate
   and returns a handle to this state.  Using this handle with
   XDPSSetContextGState or XDPSPushContextGState is more efficient than 
   using the general routines to return to this state.  Note:  gstates should
   not be used in states that the application doesn't anticipate returning to.
*/

extern int XDPSCaptureContextGState(DPSContext context,
				    DPSGState *gsReturn);

/* XDPSUpdateContextGState updates the saved gstate to correspond to the
   current graphics state.  The previous setting of the gstate is no longer
   accessible.
*/

extern int XDPSUpdateContextGState(DPSContext context,
				   DPSGState gs);

/* XDPSFreeContextGState releases a gstate.
*/

extern int XDPSFreeContextGState(DPSContext context,
				 DPSGState gs);

/* XDPSSetContextGState sets a context to a saved gstate.
*/

extern int XDPSSetContextGState(DPSContext context,
				DPSGState gs);

/* XDPSPushContextGState sets a context to a saved gstate, but it can be
   undone by passing the returned pushCookieReturn to XDPSPopContextGState.
   It is up to the caller to make sure that push and pop are called in a
   stack-oriented fashion.
*/

extern int XDPSPushContextGState(DPSContext context,
				 DPSGState gs,
				 DPSPointer *pushCookieReturn);

extern int XDPSPopContextGState(DPSPointer pushCookie);

/* XDPSExtensionPresent returns whether or not the display supports the DPS
   extension.
*/

extern Bool XDPSExtensionPresent(Display *display);

/* Define, redefine, and undefine user objects.  In all cases the DPS versions
   take a context and the PS versions don't */

extern int PSDefineAsUserObj(void);
extern int DPSDefineAsUserObj(DPSContext context);

extern void PSRedefineUserObj(int userObj);
extern void DPSRedefineUserObj(DPSContext context, int userObj);

extern void PSUndefineUserObj(int userObj);
extern void DPSUndefineUserObj(DPSContext context, int userObj);

/* Reserve a number of user object indices, and then return them */

extern int PSReserveUserObjIndices(int number);
extern int DPSReserveUserObjIndices(DPSContext context, int number);

extern void PSReturnUserObjIndices(int start, int number);
extern void DPSReturnUserObjIndices(DPSContext context, int start, int number);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* DPS_X_SHARE_H */
