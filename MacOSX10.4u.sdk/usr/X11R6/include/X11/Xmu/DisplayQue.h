/* $Xorg: DisplayQue.h,v 1.4 2001/02/09 02:03:52 xorgcvs Exp $ */

/*

Copyright 1994, 1998  The Open Group

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from The Open Group.

*/
/* $XFree86: xc/lib/Xmu/DisplayQue.h,v 1.6 2001/12/14 19:55:40 dawes Exp $ */

#ifndef _XMU_DISPLAYQUE_H_
#define _XMU_DISPLAYQUE_H_

#include <X11/Xmu/CloseHook.h>
#include <X11/Xfuncproto.h>

/*
 *			      Public Entry Points
 * 
 * 
 * XmuDisplayQueue *XmuDQCreate (closefunc, freefunc, data)
 *     XmuCloseDisplayQueueProc closefunc;
 *     XmuFreeDisplayQueueProc freefunc;
 *     XPointer data;
 * 
 *         Creates and returns a queue into which displays may be placed.  When
 *         the display is closed, the closefunc (if non-NULL) is upcalled with
 *         as follows:
 *
 *                 (*closefunc) (queue, entry)
 *
 *         The freeproc, if non-NULL, is called whenever the last display is
 *         closed, notifying the creator that display queue may be released
 *         using XmuDQDestroy.
 *
 *
 * Bool XmuDQDestroy (q, docallbacks)
 *     XmuDisplayQueue *q;
 *     Bool docallbacks;
 * 
 *         Releases all memory for the indicated display queue.  If docallbacks
 *         is true, then the closefunc (if non-NULL) is called for each 
 *         display.
 * 
 * 
 * XmuDisplayQueueEntry *XmuDQLookupDisplay (q, dpy)
 *     XmuDisplayQueue *q;
 *     Display *dpy;
 *
 *         Returns the queue entry for the specified display or NULL if the
 *         display is not in the queue.
 *
 * 
 * XmuDisplayQueueEntry *XmuDQAddDisplay (q, dpy, data)
 *     XmuDisplayQueue *q;
 *     Display *dpy;
 *     XPointer data;
 *
 *         Adds the indicated display to the end of the queue or NULL if it
 *         is unable to allocate memory.  The data field may be used by the
 *         caller to attach arbitrary data to this display in this queue.  The
 *         caller should use XmuDQLookupDisplay to make sure that the display
 *         hasn't already been added.
 * 
 * 
 * Bool XmuDQRemoveDisplay (q, dpy)
 *     XmuDisplayQueue *q;
 *     Display *dpy;
 *
 *         Removes the specified display from the given queue.  If the 
 *         indicated display is not found on this queue, False is returned,
 *         otherwise True is returned.
 */

typedef struct _XmuDisplayQueue XmuDisplayQueue;
typedef struct _XmuDisplayQueueEntry XmuDisplayQueueEntry;

typedef int (*XmuCloseDisplayQueueProc)(XmuDisplayQueue *queue,
					XmuDisplayQueueEntry *entry);

typedef int (*XmuFreeDisplayQueueProc)(XmuDisplayQueue *queue);

struct _XmuDisplayQueueEntry {
    struct _XmuDisplayQueueEntry *prev, *next;
    Display *display;
    CloseHook closehook;
    XPointer data;
};

struct _XmuDisplayQueue {
    int nentries;
    XmuDisplayQueueEntry *head, *tail;
    XmuCloseDisplayQueueProc closefunc;
    XmuFreeDisplayQueueProc freefunc;
    XPointer data;
};

_XFUNCPROTOBEGIN

XmuDisplayQueue *XmuDQCreate
(
 XmuCloseDisplayQueueProc	closefunc,
 XmuFreeDisplayQueueProc	freefunc,
 XPointer			data
 );

Bool XmuDQDestroy
(
 XmuDisplayQueue		*q,
 Bool				docallbacks
 );

XmuDisplayQueueEntry *XmuDQLookupDisplay
(
 XmuDisplayQueue		*q,
 Display			*dpy
 );

XmuDisplayQueueEntry *XmuDQAddDisplay
(
 XmuDisplayQueue		*q,
 Display			*dpy,
 XPointer			data
 );

Bool XmuDQRemoveDisplay
(
 XmuDisplayQueue		*q,
 Display			*dpy
 );

_XFUNCPROTOEND

#define XmuDQNDisplays(q) ((q)->nentries)

#endif /* _XMU_DISPLAYQUE_H_ */
