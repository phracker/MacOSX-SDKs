/*
 *
Copyright 1989, 1998  The Open Group

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
 *
 * Author:  Jim Fulton, MIT X Consortium
 */

#ifndef _XawRepeaterP_h
#define _XawRepeaterP_h

#include <X11/Xaw/CommandP.h>
#include <X11/Xaw/Repeater.h>

/* new fields in widget class */
typedef struct {
    XtPointer extension;
} RepeaterClassPart;

/* repeater widget class */
typedef struct _RepeaterClassRec {
    CoreClassPart core_class;
    SimpleClassPart simple_class;
    LabelClassPart label_class;
    CommandClassPart command_class;
    RepeaterClassPart repeater_class;
} RepeaterClassRec;

typedef struct {
    /* resources */
    int initial_delay;			/* initialDelay/Delay */
    int repeat_delay;			/* repeatDelay/Delay */
    int minimum_delay;			/* minimumDelay/MinimumDelay */
    int decay;				/* decay to minimum delay */
    Boolean flash;			/* flash/Boolean */
    XtCallbackList start_callbacks;	/* startCallback/StartCallback */
    XtCallbackList stop_callbacks;	/* stopCallback/StopCallback */

    /* private */
    int next_delay;			/* next amount for timer */
    XtIntervalId timer;			/* timer that will fire */
#ifndef OLDXAW
    XtPointer pad[4];	/* for future use and keep binary compatability */
#endif
} RepeaterPart;

typedef struct _RepeaterRec {
    CorePart core;
    SimplePart simple;
    LabelPart label;
    CommandPart command;
    RepeaterPart repeater;
} RepeaterRec;

					/* milliseconds */
#define REP_DEF_DECAY			5
#define REP_DEF_INITIAL_DELAY		200
#define REP_DEF_MINIMUM_DELAY		10
#define REP_DEF_REPEAT_DELAY		50

extern RepeaterClassRec repeaterClassRec;

#endif /* _XawRepeaterP_h */
