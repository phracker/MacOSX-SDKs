/* $Xorg: ThreadsI.h,v 1.4 2001/02/09 02:03:59 xorgcvs Exp $ */

/************************************************************
Copyright 1993 by Sun Microsystems, Inc. Mountain View, CA.

                    All Rights Reserved

Permission  to  use,  copy,  modify,  and  distribute   this
software  and  its documentation for any purpose and without
fee is hereby granted, provided that the above copyright no-
tice  appear  in all copies and that both that copyright no-
tice and this permission notice appear in  supporting  docu-
mentation,  and  that the name Sun not be used in advertising 
or publicity pertaining to distribution  of  the software  
without specific prior written permission. Sun makes no 
representations about the suitability of this software for 
any purpose. It is provided "as is" without any express or 
implied warranty.

SUN DISCLAIMS ALL WARRANTIES WITH REGARD TO  THIS  SOFTWARE,
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FIT-
NESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL SUN BE  LI-
ABLE  FOR  ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,  DATA  OR
PROFITS,  WHETHER  IN  AN  ACTION OF CONTRACT, NEGLIGENCE OR
OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION  WITH
THE USE OR PERFORMANCE OF THIS SOFTWARE.

********************************************************/

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
/* $XFree86: xc/lib/Xt/ThreadsI.h,v 3.5 2001/12/14 19:56:31 dawes Exp $ */

#ifndef _XtThreadsI_h
#define _XtThreadsI_h

#include <X11/XlibConf.h>

#ifdef XTHREADS

typedef struct _LockRec *LockPtr;

typedef void (*ThreadAppProc)(
    XtAppContext /* app */
);

typedef void (*ThreadAppYieldLockProc)(
    XtAppContext, /* app */
    Boolean*, /* push_thread */
    Boolean*, /* pushed_thread */
    int* /* level */
);

typedef void (*ThreadAppRestoreLockProc)(
    XtAppContext /* app */,
    int, /* level */
    Boolean* /* pushed_thread */
);

extern void (*_XtProcessLock)(
    void
);

extern void (*_XtProcessUnlock)(
    void
);

extern void (*_XtInitAppLock)(
    XtAppContext /* app */
);

#define INIT_APP_LOCK(app) if(_XtInitAppLock) (*_XtInitAppLock)(app)
#define FREE_APP_LOCK(app) if(app && app->free_lock)(*app->free_lock)(app)

#define LOCK_PROCESS if(_XtProcessLock)(*_XtProcessLock)()
#define UNLOCK_PROCESS if(_XtProcessUnlock)(*_XtProcessUnlock)()
#define LOCK_APP(app) if(app && app->lock)(*app->lock)(app)
#define UNLOCK_APP(app) if(app && app->unlock)(*app->unlock)(app)

#define YIELD_APP_LOCK(app,push,pushed,level)\
	 if(app && app->yield_lock) (*app->yield_lock)(app,push,pushed,level)
#define RESTORE_APP_LOCK(app,level,pushed)\
	 if(app && app->restore_lock) (*app->restore_lock)(app,level,pushed)

#define WIDGET_TO_APPCON(w) \
    XtAppContext app = (w && _XtProcessLock ? \
	XtWidgetToApplicationContext(w) : NULL)

#define DPY_TO_APPCON(d) \
    XtAppContext app = (_XtProcessLock ? XtDisplayToApplicationContext(d): 0)

#else /* defined(XTHREADS) */

#define LOCK_PROCESS
#define UNLOCK_PROCESS
#define LOCK_APP(app)
#define UNLOCK_APP(app)

#define INIT_APP_LOCK(app)
#define FREE_APP_LOCK(app)

#define WIDGET_TO_APPCON(w)
#define DPY_TO_APPCON(d)

#endif /* !defined(XTHREADS) */
#endif /* _XtThreadsI_h */
