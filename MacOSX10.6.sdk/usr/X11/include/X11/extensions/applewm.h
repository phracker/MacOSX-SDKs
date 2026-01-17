/* $XFree86: xc/lib/apple/applewm.h,v 1.1 2003/08/12 23:47:10 torrey Exp $ */
/**************************************************************************

Copyright (c) 2002 Apple Computer, Inc.
All Rights Reserved.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sub license, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice (including the
next paragraph) shall be included in all copies or substantial portions
of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
IN NO EVENT SHALL PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR
ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

**************************************************************************/

#ifndef _APPLEWM_H_
#define _APPLEWM_H_

#include <X11/Xfuncproto.h>

#define X_AppleWMQueryVersion		0
#define X_AppleWMFrameGetRect		1
#define X_AppleWMFrameHitTest		2
#define X_AppleWMFrameDraw		3
#define X_AppleWMDisableUpdate		4
#define X_AppleWMReenableUpdate		5
#define X_AppleWMSelectInput		6
#define X_AppleWMSetWindowMenuCheck	7
#define X_AppleWMSetFrontProcess	8
#define X_AppleWMSetWindowLevel		9
#define X_AppleWMSetCanQuit		10
#define X_AppleWMSetWindowMenu		11
#define X_AppleWMSendPSN		12
#define X_AppleWMAttachTransient	13

/* Events */
#define AppleWMControllerNotify		0
#define AppleWMActivationNotify		1
#define AppleWMPasteboardNotify		2
#define AppleWMNumberEvents		3

#define AppleWMControllerNotifyMask	(1L << 0)
#define AppleWMActivationNotifyMask	(1L << 1)
#define AppleWMPasteboardNotifyMask	(1L << 2)

/* "Kinds" of ControllerNotify events */
#define AppleWMMinimizeWindow		0
#define AppleWMZoomWindow		1
#define AppleWMCloseWindow		2
#define AppleWMBringAllToFront		3
#define AppleWMHideWindow		4
#define AppleWMHideAll			5
#define AppleWMShowAll			6
#define AppleWMWindowMenuItem		9
#define AppleWMWindowMenuNotify		10
#define AppleWMNextWindow		11
#define AppleWMPreviousWindow		12

/* "Kinds" of ActivationNotify events */
#define AppleWMIsActive			0
#define AppleWMIsInactive		1
#define AppleWMReloadPreferences	2

/* "Kinds" of PasteboardNotify events */
#define AppleWMCopyToPasteboard		0

/* Errors */
#define AppleWMClientNotLocal		0
#define AppleWMOperationNotSupported	1
#define AppleWMNumberErrors		(AppleWMOperationNotSupported + 1)

/* Window level ids */
#define AppleWMWindowLevelNormal	0
#define AppleWMWindowLevelFloating	1
#define AppleWMWindowLevelTornOff	2
#define AppleWMWindowLevelDock		3
#define AppleWMWindowLevelDesktop	4
#define AppleWMNumWindowLevels		5

/* Possible value for frame_rect argument to XAppleWMFrameGetRect() */
#define AppleWMFrameRectTitleBar	1
#define AppleWMFrameRectTracking	2
#define AppleWMFrameRectGrowBox		3

/* Window frame classes */
#define AppleWMFrameClassDocument	1 << 0
#define AppleWMFrameClassDialog		1 << 1
#define AppleWMFrameClassModalDialog	1 << 2
#define AppleWMFrameClassSystemModalDialog 1 << 3
#define AppleWMFrameClassUtility	1 << 4
#define AppleWMFrameClassToolbar	1 << 5
#define AppleWMFrameClassMenu		1 << 6
#define AppleWMFrameClassSplash		1 << 7
#define AppleWMFrameClassBorderless	1 << 8

/* Window frame attributes */
#define AppleWMFrameActive		0x0001
#define AppleWMFrameUrgent		0x0002
#define AppleWMFrameTitle		0x0004
#define AppleWMFramePrelight		0x0008
#define AppleWMFrameShaded		0x0010
#define AppleWMFrameCloseBox		0x0100
#define AppleWMFrameCollapseBox		0x0200
#define AppleWMFrameZoomBox		0x0400
#define AppleWMFrameAnyBox		0x0700
#define AppleWMFrameCloseBoxClicked	0x0800
#define AppleWMFrameCollapseBoxClicked	0x1000
#define AppleWMFrameZoomBoxClicked	0x2000
#define AppleWMFrameAnyBoxClicked	0x3800
#define AppleWMFrameGrowBox		0x4000

#ifndef _APPLEWM_SERVER_

typedef struct {
    int	type;		    /* of event */
    unsigned long serial;   /* # of last request processed by server */
    Bool send_event;	    /* true if this came frome a SendEvent request */
    Display *display;	    /* Display the event was read from */
    Window window;	    /* window of event */
    Time time;		    /* server timestamp when event happened */
    int kind;		    /* subtype of event */
    int arg;
} XAppleWMNotifyEvent;

_XFUNCPROTOBEGIN

Bool XAppleWMQueryExtension (Display *dpy, int *event_base, int *error_base);

Bool XAppleWMQueryVersion (Display *dpy, int *majorVersion,
			    int *minorVersion, int *patchVersion);

Bool XAppleWMDisableUpdate (Display *dpy, int screen);

Bool XAppleWMReenableUpdate (Display *dpy, int screen);

Bool XAppleWMSelectInput (Display *dpy, unsigned long mask);

Bool XAppleWMSetWindowMenu (Display *dpy, int nitems, const char **items);
Bool XAppleWMSetWindowMenuWithShortcuts (Display *dpy, int nitems,
                                         const char **items,
                                         const char *shortcuts);

Bool XAppleWMSetWindowMenuCheck (Display *dpy, int index);

Bool XAppleWMSetFrontProcess (Display *dpy);

Bool XAppleWMSetWindowLevel (Display *dpy, Window id, int level);

Bool XAppleWMSendPSN(Display *dpy);

Bool XAppleWMAttachTransient(Display *dpy, Window child, Window parent);

Bool XAppleWMSetCanQuit (Display *dpy, Bool state);

Bool XAppleWMFrameGetRect (Display *dpy,
                           unsigned int frame_class, unsigned int frame_rect,
                           short inner_x, short inner_y,
                           short inner_w, short inner_h,
                           short outer_x, short outer_y,
                           short outer_w, short outer_h,
                           short *ret_x, short *ret_y,
                           short *ret_w, short *ret_h);

unsigned int XAppleWMFrameHitTest (Display *dpy,
                                   unsigned int frame_class,
                                   short point_x, short point_y,
                                   short inner_x, short inner_y,
                                   short inner_w, short inner_h,
                                   short outer_x, short outer_y,
                                   short outer_w, short outer_h);

Bool XAppleWMFrameDraw (Display *dpy, int screen, Window window,
                        unsigned int frame_class, unsigned int frame_attr,
                        short inner_x, short inner_y,
                        short inner_w, short inner_h,
                        short outer_x, short outer_y,
                        short outer_w, short outer_h,
                        unsigned int title_length,
                        const unsigned char * title_bytes);

_XFUNCPROTOEND

#endif /* _APPLEWM_SERVER_ */
#endif /* _APPLEWM_H_ */
