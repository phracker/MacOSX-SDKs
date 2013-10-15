/* $Xorg: sync.h,v 1.4 2001/02/09 02:03:24 xorgcvs Exp $ */
/*

Copyright 1991, 1993, 1994, 1998  The Open Group

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

/***********************************************************
Copyright 1991,1993 by Digital Equipment Corporation, Maynard, Massachusetts,
and Olivetti Research Limited, Cambridge, England.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the names of Digital or Olivetti
not be used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

DIGITAL AND OLIVETTI DISCLAIM ALL WARRANTIES WITH REGARD TO THIS
SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS, IN NO EVENT SHALL THEY BE LIABLE FOR ANY SPECIAL, INDIRECT OR
CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
PERFORMANCE OF THIS SOFTWARE.

******************************************************************/
/* $XFree86: xc/include/extensions/sync.h,v 1.4 2001/12/20 19:40:59 tsi Exp $ */

#ifndef _SYNC_H_
#define _SYNC_H_

#include <X11/Xfuncproto.h>

_XFUNCPROTOBEGIN

#define SYNC_NAME "SYNC"

#define SYNC_MAJOR_VERSION	3
#define SYNC_MINOR_VERSION	0

#define X_SyncInitialize		0
#define X_SyncListSystemCounters	1
#define X_SyncCreateCounter		2
#define X_SyncSetCounter		3
#define X_SyncChangeCounter		4
#define X_SyncQueryCounter              5
#define X_SyncDestroyCounter		6
#define X_SyncAwait			7
#define X_SyncCreateAlarm               8
#define X_SyncChangeAlarm	        9
#define X_SyncQueryAlarm	       10
#define X_SyncDestroyAlarm	       11
#define X_SyncSetPriority   	       12
#define X_SyncGetPriority   	       13

#define XSyncCounterNotify              0
#define XSyncAlarmNotify		1
#define XSyncAlarmNotifyMask 		(1L << XSyncAlarmNotify)

#define XSyncNumberEvents		2L

#define XSyncBadCounter			0L
#define XSyncBadAlarm			1L
#define XSyncNumberErrors		(XSyncBadAlarm + 1)

/*
 * Flags for Alarm Attributes
 */
#define XSyncCACounter			(1L<<0)
#define XSyncCAValueType		(1L<<1)
#define XSyncCAValue			(1L<<2)
#define XSyncCATestType			(1L<<3)
#define XSyncCADelta			(1L<<4)
#define XSyncCAEvents			(1L<<5)

/*
 * Constants for the value_type argument of various requests
 */
typedef enum {
    XSyncAbsolute,
    XSyncRelative
} XSyncValueType;

/*
 * Alarm Test types
 */
typedef enum {
    XSyncPositiveTransition,
    XSyncNegativeTransition,
    XSyncPositiveComparison,
    XSyncNegativeComparison
} XSyncTestType;

/*
 * Alarm state constants
 */
typedef enum {
    XSyncAlarmActive,
    XSyncAlarmInactive,
    XSyncAlarmDestroyed
} XSyncAlarmState;


typedef XID XSyncCounter;
typedef XID XSyncAlarm;
typedef struct _XSyncValue {
    int hi;
    unsigned int lo;
} XSyncValue;

/*
 *   Macros/functions for manipulating 64 bit values
 */

/* have to put these prototypes before the corresponding macro definitions */

extern void XSyncIntToValue(
    XSyncValue* /*pv*/,
    int /*i*/
);

extern void XSyncIntsToValue(
    XSyncValue* /*pv*/,
    unsigned int /*l*/,
    int /*h*/
);

extern Bool XSyncValueGreaterThan(
    XSyncValue /*a*/,
    XSyncValue /*b*/
);

extern Bool XSyncValueLessThan(
    XSyncValue /*a*/,
    XSyncValue /*b*/
);

extern Bool XSyncValueGreaterOrEqual(
    XSyncValue /*a*/,
    XSyncValue /*b*/
);

extern Bool XSyncValueLessOrEqual(
    XSyncValue /*a*/,
    XSyncValue /*b*/
);

extern Bool XSyncValueEqual(
    XSyncValue /*a*/,
    XSyncValue /*b*/
);

extern Bool XSyncValueIsNegative(
    XSyncValue /*v*/
);

extern Bool XSyncValueIsZero(
    XSyncValue /*a*/
);

extern Bool XSyncValueIsPositive(
    XSyncValue /*v*/
);

extern unsigned int XSyncValueLow32(
    XSyncValue /*v*/
);

extern int XSyncValueHigh32(
    XSyncValue /*v*/
);

extern void XSyncValueAdd(
    XSyncValue* /*presult*/,
    XSyncValue /*a*/,
    XSyncValue /*b*/,
    int* /*poverflow*/
);

extern void XSyncValueSubtract(
    XSyncValue* /*presult*/,
    XSyncValue /*a*/,
    XSyncValue /*b*/,
    int* /*poverflow*/
);

extern void XSyncMaxValue(
    XSyncValue* /*pv*/
);

extern void XSyncMinValue(
    XSyncValue* /*pv*/
);

_XFUNCPROTOEND

/*  The _XSync macros below are for library internal use only.  They exist 
 *  so that if we have to make a fix, we can change it in this one place
 *  and have both the macro and function variants inherit the fix.
 */

#define _XSyncIntToValue(pv, i)     ((pv)->hi=((i<0)?~0:0),(pv)->lo=(i))
#define _XSyncIntsToValue(pv, l, h) ((pv)->lo = (l), (pv)->hi = (h))
#define _XSyncValueGreaterThan(a, b)\
    ((a).hi>(b).hi || ((a).hi==(b).hi && (a).lo>(b).lo))
#define _XSyncValueLessThan(a, b)\
    ((a).hi<(b).hi || ((a).hi==(b).hi && (a).lo<(b).lo))
#define _XSyncValueGreaterOrEqual(a, b)\
    ((a).hi>(b).hi || ((a).hi==(b).hi && (a).lo>=(b).lo))
#define _XSyncValueLessOrEqual(a, b)\
    ((a).hi<(b).hi || ((a).hi==(b).hi && (a).lo<=(b).lo))
#define _XSyncValueEqual(a, b)	((a).lo==(b).lo && (a).hi==(b).hi)
#define _XSyncValueIsNegative(v) (((v).hi & 0x80000000) ? 1 : 0)
#define _XSyncValueIsZero(a)	((a).lo==0 && (a).hi==0)
#define _XSyncValueIsPositive(v) (((v).hi & 0x80000000) ? 0 : 1)
#define _XSyncValueLow32(v)	((v).lo)
#define _XSyncValueHigh32(v)	((v).hi)
#define _XSyncValueAdd(presult,a,b,poverflow) {\
	int t = (a).lo;\
	Bool signa = XSyncValueIsNegative(a);\
	Bool signb = XSyncValueIsNegative(b);\
	((presult)->lo = (a).lo + (b).lo);\
	((presult)->hi = (a).hi + (b).hi);\
	if (t>(presult)->lo) (presult)->hi++;\
	*poverflow = ((signa == signb) && !(signa == XSyncValueIsNegative(*presult)));\
     }
#define _XSyncValueSubtract(presult,a,b,poverflow) {\
	int t = (a).lo;\
	Bool signa = XSyncValueIsNegative(a);\
	Bool signb = XSyncValueIsNegative(b);\
	((presult)->lo = (a).lo - (b).lo);\
	((presult)->hi = (a).hi - (b).hi);\
	if (t>(presult)->lo) (presult)->hi--;\
	*poverflow = ((signa == signb) && !(signa == XSyncValueIsNegative(*presult)));\
     }
#define _XSyncMaxValue(pv) ((pv)->hi = 0x7fffffff, (pv)->lo = 0xffffffff)
#define _XSyncMinValue(pv) ((pv)->hi = 0x80000000, (pv)->lo = 0)

/*
 *  These are the publically usable macros.  If you want the function version
 *  of one of these, just #undef the macro to uncover the function.
 *  (This is the same convention that the ANSI C library uses.)
 */

#define XSyncIntToValue(pv, i) _XSyncIntToValue(pv, i)
#define XSyncIntsToValue(pv, l, h) _XSyncIntsToValue(pv, l, h)
#define XSyncValueGreaterThan(a, b) _XSyncValueGreaterThan(a, b)
#define XSyncValueLessThan(a, b) _XSyncValueLessThan(a, b)
#define XSyncValueGreaterOrEqual(a, b) _XSyncValueGreaterOrEqual(a, b)
#define XSyncValueLessOrEqual(a, b) _XSyncValueLessOrEqual(a, b)
#define XSyncValueEqual(a, b) _XSyncValueEqual(a, b)
#define XSyncValueIsNegative(v) _XSyncValueIsNegative(v)
#define XSyncValueIsZero(a) _XSyncValueIsZero(a)
#define XSyncValueIsPositive(v) _XSyncValueIsPositive(v)
#define XSyncValueLow32(v) _XSyncValueLow32(v)
#define XSyncValueHigh32(v) _XSyncValueHigh32(v)
#define XSyncValueAdd(presult,a,b,poverflow) _XSyncValueAdd(presult,a,b,poverflow)
#define XSyncValueSubtract(presult,a,b,poverflow) _XSyncValueSubtract(presult,a,b,poverflow)
#define XSyncMaxValue(pv) _XSyncMaxValue(pv)
#define XSyncMinValue(pv) _XSyncMinValue(pv)

#ifndef _SYNC_SERVER

typedef struct _XSyncSystemCounter {
    char *name;			/* null-terminated name of system counter */
    XSyncCounter counter;	/* counter id of this system counter */
    XSyncValue resolution;	/* resolution of this system counter */
} XSyncSystemCounter;


typedef struct {
    XSyncCounter counter;	/* counter to trigger on */
    XSyncValueType value_type;	/* absolute/relative */
    XSyncValue wait_value;	/* value to compare counter to */
    XSyncTestType test_type;	/* pos/neg comparison/transtion */
} XSyncTrigger;

typedef struct {
    XSyncTrigger trigger;	/* trigger for await */
    XSyncValue event_threshold; /* send event if past threshold */
} XSyncWaitCondition;


typedef struct {
    XSyncTrigger trigger;
    XSyncValue  delta;
    Bool events;
    XSyncAlarmState state;
} XSyncAlarmAttributes;

/*
 *  Events
 */

typedef struct {
    int type;			/* event base + XSyncCounterNotify */
    unsigned long serial;	/* # of last request processed by server */
    Bool send_event;		/* true if this came from a SendEvent request */
    Display *display;		/* Display the event was read from */
    XSyncCounter counter;	/* counter involved in await */
    XSyncValue wait_value;	/* value being waited for */
    XSyncValue counter_value;	/* counter value when this event was sent */
    Time time;			/* milliseconds */
    int count;			/* how many more events to come */
    Bool destroyed;		/* True if counter was destroyed */
} XSyncCounterNotifyEvent;

typedef struct {
    int type;			/* event base + XSyncCounterNotify */
    unsigned long serial;	/* # of last request processed by server */
    Bool send_event;		/* true if this came from a SendEvent request */
    Display *display;		/* Display the event was read from */
    XSyncAlarm alarm;		/* alarm that triggered */
    XSyncValue counter_value;	/* value that triggered the alarm */
    XSyncValue alarm_value;	/* test  value of trigger in alarm */
    Time time;			/* milliseconds */
    XSyncAlarmState state;	/* new state of alarm */
} XSyncAlarmNotifyEvent;

/*
 *  Errors 
 */

typedef struct {
    int type;			
    Display *display;		/* Display the event was read from */
    XSyncAlarm alarm;		/* resource id */
    unsigned long serial;	/* serial number of failed request */
    unsigned char error_code;	/* error base + XSyncBadAlarm */
    unsigned char request_code;	/* Major op-code of failed request */
    unsigned char minor_code;	/* Minor op-code of failed request */
} XSyncAlarmError;

typedef struct {
    int type;			
    Display *display;		/* Display the event was read from */
    XSyncCounter counter;	/* resource id */
    unsigned long serial;	/* serial number of failed request */
    unsigned char error_code;	/* error base + XSyncBadCounter */
    unsigned char request_code;	/* Major op-code of failed request */
    unsigned char minor_code;	/* Minor op-code of failed request */
} XSyncCounterError;

/* 
 *  Prototypes
 */

_XFUNCPROTOBEGIN

extern Status XSyncQueryExtension(
    Display* /*dpy*/,
    int* /*event_base_return*/,
    int* /*error_base_return*/
);

extern Status XSyncInitialize(
    Display* /*dpy*/,
    int* /*major_version_return*/,
    int* /*minor_version_return*/
);

extern XSyncSystemCounter *XSyncListSystemCounters(
    Display* /*dpy*/,
    int* /*n_counters_return*/
);

extern void XSyncFreeSystemCounterList(
    XSyncSystemCounter* /*list*/
);

extern XSyncCounter XSyncCreateCounter(
    Display* /*dpy*/,
    XSyncValue /*initial_value*/
);

extern Status XSyncSetCounter(
    Display* /*dpy*/,
    XSyncCounter /*counter*/,
    XSyncValue /*value*/
);

extern Status XSyncChangeCounter(
    Display* /*dpy*/,
    XSyncCounter /*counter*/,
    XSyncValue /*value*/
);

extern Status XSyncDestroyCounter(
    Display* /*dpy*/,
    XSyncCounter /*counter*/
);

extern Status XSyncQueryCounter(
    Display* /*dpy*/,
    XSyncCounter /*counter*/,
    XSyncValue* /*value_return*/
);

extern Status XSyncAwait(
    Display* /*dpy*/,
    XSyncWaitCondition* /*wait_list*/,
    int /*n_conditions*/
);

extern XSyncAlarm XSyncCreateAlarm(
    Display* /*dpy*/,
    unsigned long /*values_mask*/,
    XSyncAlarmAttributes* /*values*/
);

extern Status XSyncDestroyAlarm(
    Display* /*dpy*/,
    XSyncAlarm /*alarm*/
);

extern Status XSyncQueryAlarm(
    Display* /*dpy*/,
    XSyncAlarm /*alarm*/,
    XSyncAlarmAttributes* /*values_return*/
);

extern Status XSyncChangeAlarm(
    Display* /*dpy*/,
    XSyncAlarm /*alarm*/,
    unsigned long /*values_mask*/,
    XSyncAlarmAttributes* /*values*/
);

extern Status XSyncSetPriority(
    Display* /*dpy*/,
    XID /*client_resource_id*/,
    int /*priority*/
);

extern Status XSyncGetPriority(
    Display* /*dpy*/,
    XID /*client_resource_id*/,
    int* /*return_priority*/
);

#endif /* _SYNC_SERVER */

_XFUNCPROTOEND

#endif /* _SYNC_H_ */
