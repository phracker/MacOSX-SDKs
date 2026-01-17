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
#include <X11/extensions/applewmconst.h>

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

#endif /* _APPLEWM_H_ */
