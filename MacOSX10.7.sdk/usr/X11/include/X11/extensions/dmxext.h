/*
 * Copyright 2002-2004 Red Hat Inc., Durham, North Carolina.
 *
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation on the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NON-INFRINGEMENT.  IN NO EVENT SHALL RED HAT AND/OR THEIR SUPPLIERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
 * Authors:
 *   Rickard E. (Rik) Faith <faith@redhat.com>
 *
 */

/** \file
 * This file describes the interface to the client-side libdmx.a
 * library.  All DMX-aware client-side applications should include this
 * file. */

#ifndef _DMXEXT_H_
#define _DMXEXT_H_

#include <X11/extensions/dmx.h>

/** Client-library screen information structure, returned by
 * #DMXGetScreenAttributes.  */
typedef struct {
    char         *displayName;
    int          logicalScreen;

    unsigned int screenWindowWidth;    /* displayName's coordinate system */
    unsigned int screenWindowHeight;   /* displayName's coordinate system */
    int          screenWindowXoffset;  /* displayName's coordinate system */
    int          screenWindowYoffset;  /* displayName's coordinate system */

    unsigned int rootWindowWidth;      /* screenWindow's coordinate system */
    unsigned int rootWindowHeight;     /* screenWindow's coordinate system */
    int          rootWindowXoffset;    /* screenWindow's coordinate system */
    int          rootWindowYoffset;    /* screenWindow's coordinate system */

    int          rootWindowXorigin;    /* global coordinate system */
    int          rootWindowYorigin;    /* global coordinate system */
} DMXScreenAttributes;

/** Client-library window information structure, returned by
 * #DMXGetWindowAttributes. */
typedef struct {
    int          screen;
    Window       window;
    XRectangle   pos, vis;
} DMXWindowAttributes;

/** Client-library desktop information structure, returned by
 * #DMXGetDesktopAttributes. */
typedef struct {
    unsigned int width;         /* global coordinate system */
    unsigned int height;        /* global coordinate system */
    int          shiftX;        /* global coordinate system */
    int          shiftY;        /* global coordinate system */
} DMXDesktopAttributes;

/** Enumeration for the #inputType field in the #DMXInputAttributes
 * structure. */
typedef enum {
    DMXLocalInputType,
    DMXConsoleInputType,
    DMXBackendInputType
} DMXInputEnum;

/** Client-library input information structure, returned by
 * #DMXGetInputAttributes. */ 
typedef struct {
    DMXInputEnum inputType;
    int          physicalScreen;
    int          physicalId;
    Bool         isCore;
    Bool         sendsCore;
    const char   *name;
    Bool         detached;
} DMXInputAttributes;

_XFUNCPROTOBEGIN

extern Bool DMXQueryExtension(Display *dpy,
                              int *event_basep, int *error_basep);
extern Bool DMXQueryVersion(Display *dpy, int *major_version,
                            int *minor_version, int *patch_version);
extern Bool DMXSync(Display *dpy);
extern Bool DMXForceWindowCreation(Display *dpy, Window window);


extern Bool DMXGetScreenCount(Display *dpy, int *screen_count);
extern Bool DMXGetScreenAttributes(Display *dpy,
                                   int screen,
                                   DMXScreenAttributes *attr);
extern int  DMXChangeScreensAttributes(Display *dpy,
                                       int screen_count,
                                       int *screens,
                                       int mask_count,
                                       unsigned int *masks,
                                       DMXScreenAttributes *attr, /* vector */
                                       int *error_screen);

extern Bool DMXAddScreen(Display *dpy,
                         const char *displayName,
                         unsigned int mask,
                         DMXScreenAttributes *attr,
                         int *screen);
extern Bool DMXRemoveScreen(Display *dpy, int screen);

/* Call DMXGetScreenWindowCount and allocate info to that size.  Pass
 * the size in available_count.  This call can generate a large amount
 * of wire traffic and should not be used called with available_count=0
 * just to determine the screen_count value -- use DMXGetScreenCount
 * instead.  NOTE: Also see DMX protocol specification (DMXSpec.txt) for
 * usage of DMXSync to flush pending commands. */
extern Bool DMXGetWindowAttributes(Display *dpy, Window window,
                                   int *screen_count, int available_count,
                                   DMXWindowAttributes *attr);

extern Bool DMXGetDesktopAttributes(Display *dpy, DMXDesktopAttributes *attr);
extern int  DMXChangeDesktopAttributes(Display *dpy,
                                       unsigned int mask,
                                       DMXDesktopAttributes *attr);

extern Bool DMXGetInputCount(Display *dpy, int *input_count);
extern Bool DMXGetInputAttributes(Display *dpy, int id,
                                  DMXInputAttributes *attr);

extern Bool DMXAddInput(Display *dpy,
                        unsigned int mask,
                        DMXInputAttributes *attr,
                        int *id);
extern Bool DMXRemoveInput(Display *dpy, int id);

/* These are helper functions that call DMXAddInput. */
extern Bool DMXAddBackendInput(Display *dpy, int screen, int sendsCore,
                               int *newId);
extern Bool DMXAddConsoleInput(Display *dpy, const char *name, int sendsCore,
                               int *newId);

_XFUNCPROTOEND
#endif
