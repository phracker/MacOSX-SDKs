/*
 * Copyright © 2007-2008 Peter Hutterer
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors: Peter Hutterer, University of South Australia, NICTA
 *
 */


/* XGE Client interfaces */

#ifndef _XGE_H_
#define _XGE_H_

#include <X11/Xmd.h>
#include <X11/Xlib.h>
#include <X11/Xfuncproto.h>

_XFUNCPROTOBEGIN

/**
 * Generic Event mask. 
 * To be used whenever a list of masks per extension has to be provided.
 */
typedef struct {
    CARD8       extension;
    CARD8       pad0;
    CARD16      pad1;
    CARD32      evmask;
} XGenericEventMask;

Bool XGEQueryExtension(Display* dpy, int *event_basep, int *err_basep);
Bool XGEQueryVersion(Display* dpy, int *major, int* minor);

_XFUNCPROTOEND

#endif /* _XGE_H_ */
