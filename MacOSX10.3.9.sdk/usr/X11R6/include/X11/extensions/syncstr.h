/* $Xorg: syncstr.h,v 1.4 2001/02/09 02:03:24 xorgcvs Exp $ */
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

#include "sync.h"

#ifndef _SYNC_OS

/* cover up types from sync.h to make sure they're the right size for
 * protocol packaging.  These will be undef'ed after all the protocol
 * structures are defined.
 */
#define XSyncCounter CARD32
#define XSyncAlarm   CARD32

/*
 * Initialize
 */
typedef struct _xSyncInitialize {
    CARD8	reqType;
    CARD8	syncReqType;
    CARD16	length B16;
    CARD8	majorVersion;
    CARD8	minorVersion;
    CARD16	pad B16;
} xSyncInitializeReq;
#define sz_xSyncInitializeReq		8

typedef struct {
    BYTE	type;
    CARD8	unused;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD8	majorVersion;
    CARD8	minorVersion;
    CARD16	pad B16;
    CARD32	pad0 B32;
    CARD32	pad1 B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
} xSyncInitializeReply;
#define sz_xSyncInitializeReply	32

/*
 * ListSystemCounters
 */
typedef struct _xSyncListSystemCounters
{
    CARD8	reqType;
    CARD8	syncReqType;
    CARD16	length B16;
} xSyncListSystemCountersReq;
#define sz_xSyncListSystemCountersReq	4

typedef struct {
    BYTE	type;
    CARD8	unused;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    INT32	nCounters B32;
    CARD32	pad0 B32;
    CARD32	pad1 B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
} xSyncListSystemCountersReply;
#define sz_xSyncListSystemCountersReply	32

typedef struct {
    XSyncCounter counter B32;
    INT32	resolution_hi B32;
    CARD32	resolution_lo B32;
    CARD16	name_length B16;
} xSyncSystemCounter;
#define sz_xSyncSystemCounter 14

/*
 * Create Counter
 */
typedef struct _xSyncCreateCounterReq {
    CARD8	reqType;
    CARD8	syncReqType;
    CARD16	length B16;
    XSyncCounter cid B32;
    INT32       initial_value_hi B32;
    CARD32	initial_value_lo B32;
} xSyncCreateCounterReq;
#define sz_xSyncCreateCounterReq	16

/*
 * Change Counter
 */
typedef struct _xSyncChangeCounterReq {
    CARD8	reqType;
    CARD8	syncReqType;
    CARD16	length B16;
    XSyncCounter cid B32;
    INT32       value_hi B32;
    CARD32	value_lo B32;
} xSyncChangeCounterReq;
#define sz_xSyncChangeCounterReq	16

/*
 * Set Counter
 */
typedef struct _xSyncSetCounterReq {
    CARD8	reqType;
    CARD8	syncReqType;
    CARD16	length B16;
    XSyncCounter cid B32;
    INT32       value_hi B32;
    CARD32	value_lo B32;
} xSyncSetCounterReq;
#define sz_xSyncSetCounterReq	16

/*
 * Destroy Counter
 */
typedef struct _xSyncDestroyCounterReq {
    CARD8	reqType;
    CARD8	syncReqType;
    CARD16	length B16;
    XSyncCounter counter B32;
} xSyncDestroyCounterReq;
#define sz_xSyncDestroyCounterReq	8

/*
 * Query Counter
 */
typedef struct _xSyncQueryCounterReq {
    CARD8	reqType;
    CARD8	syncReqType;
    CARD16	length B16;
    XSyncCounter counter B32;
} xSyncQueryCounterReq;
#define sz_xSyncQueryCounterReq		8


typedef struct {
    BYTE	type;
    CARD8	unused;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    INT32	value_hi B32;
    CARD32	value_lo B32;
    CARD32	pad0 B32;
    CARD32	pad1 B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
} xSyncQueryCounterReply;
#define sz_xSyncQueryCounterReply	32

/*
 * Await
 */
typedef struct _xSyncAwaitReq {
    CARD8	reqType;
    CARD8	syncReqType;
    CARD16	length B16;
} xSyncAwaitReq;
#define sz_xSyncAwaitReq		4

typedef struct _xSyncWaitCondition {
    XSyncCounter counter B32;
    CARD32	value_type B32;
    INT32       wait_value_hi B32;
    CARD32      wait_value_lo B32;
    CARD32	test_type B32;
    INT32	event_threshold_hi B32;
    CARD32	event_threshold_lo B32;
} xSyncWaitCondition;
#define sz_xSyncWaitCondition		28

/*
 * Create Alarm
 */
typedef struct _xSyncCreateAlarmReq {
    CARD8	reqType;
    CARD8	syncReqType;
    CARD16	length B16;
    XSyncAlarm	id B32;
    CARD32      valueMask B32;
} xSyncCreateAlarmReq;
#define sz_xSyncCreateAlarmReq		12

/*
 * Destroy Alarm
 */
typedef struct _xSyncDestroyAlarmReq {
    CARD8	reqType;
    CARD8	syncReqType;
    CARD16	length B16;
    XSyncAlarm	alarm B32;
} xSyncDestroyAlarmReq;
#define sz_xSyncDestroyAlarmReq		8

/*
 * Query Alarm
 */
typedef struct _xSyncQueryAlarmReq {
    CARD8	reqType;
    CARD8	syncReqType;
    CARD16	length B16;
    XSyncAlarm	alarm B32;
} xSyncQueryAlarmReq;
#define sz_xSyncQueryAlarmReq		8

typedef struct {
    BYTE	type;
    CARD8	unused;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    XSyncCounter counter B32;
    CARD32	value_type B32;
    INT32	wait_value_hi B32;
    CARD32	wait_value_lo B32;
    CARD32	test_type      B32;
    INT32	delta_hi B32;
    CARD32	delta_lo B32;
    BOOL        events;
    BYTE        state;
    BYTE	pad0;
    BYTE	pad1;
} xSyncQueryAlarmReply;
#define sz_xSyncQueryAlarmReply		40

/*
 * Change Alarm
 */
typedef struct _xSyncChangeAlarmReq {
    CARD8	reqType;
    CARD8	syncReqType;
    CARD16	length B16;
    XSyncAlarm	alarm B32;
    CARD32	valueMask B32;
} xSyncChangeAlarmReq;
#define sz_xSyncChangeAlarmReq		12

/*
 * SetPriority
 */
typedef struct _xSyncSetPriority{
    CARD8   	reqType;
    CARD8   	syncReqType;
    CARD16  	length B16;
    CARD32  	id B32;
    INT32  	priority B32;
} xSyncSetPriorityReq;
#define sz_xSyncSetPriorityReq	    	12

/*
 * Get Priority
 */
typedef struct _xSyncGetPriority{
    CARD8   	reqType;
    CARD8   	syncReqType;
    CARD16  	length B16;
    CARD32  	id B32; /*XXX XID? */
} xSyncGetPriorityReq;
#define sz_xSyncGetPriorityReq	    	 8

typedef struct {
    BYTE	type;
    CARD8	unused;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    INT32  	priority B32;
    CARD32  	pad0 B32;
    CARD32  	pad1 B32;
    CARD32  	pad2 B32;
    CARD32  	pad3 B32;
    CARD32  	pad4 B32;
} xSyncGetPriorityReply;
#define sz_xSyncGetPriorityReply	32

/*
 * Events
 */

typedef struct _xSyncCounterNotifyEvent {
    BYTE	type;
    BYTE	kind;
    CARD16	sequenceNumber B16;
    XSyncCounter counter B32;
    INT32	wait_value_hi B32;
    CARD32	wait_value_lo B32;
    INT32	counter_value_hi B32;
    CARD32	counter_value_lo B32;
    CARD32	time B32;
    CARD16	count B16;
    BOOL	destroyed;
    BYTE        pad0;
} xSyncCounterNotifyEvent;

typedef struct _xSyncAlarmNotifyEvent {
    BYTE	type;
    BYTE	kind;
    CARD16	sequenceNumber B16;
    XSyncAlarm	alarm B32;
    INT32	counter_value_hi B32;
    CARD32	counter_value_lo B32;
    INT32	alarm_value_hi B32;
    CARD32	alarm_value_lo B32;
    CARD32	time B32;
    CARD8       state;
    BYTE        pad0;
    BYTE        pad1;
    BYTE        pad2;
} xSyncAlarmNotifyEvent;

#undef XSyncCounter
#undef XSyncAlarm

#endif /* _SYNC_OS */

#ifdef _SYNC_SERVER

#define CARD64 XSyncValue /* XXX temporary! need real 64 bit values for Alpha */

typedef struct _SyncCounter {
    ClientPtr		client;	/* Owning client. 0 for system counters */
    XSyncCounter	id;		/* resource ID */
    CARD64		value;		/* counter value */
    struct _SyncTriggerList *pTriglist;	/* list of triggers */
    Bool		beingDestroyed; /* in process of going away */
    struct _SysCounterInfo *pSysCounterInfo; /* NULL if not a system counter */
} SyncCounter;

/*
 * The System Counter interface
 */

typedef enum {
    XSyncCounterNeverChanges,
    XSyncCounterNeverIncreases,
    XSyncCounterNeverDecreases,
    XSyncCounterUnrestricted
} SyncCounterType;

typedef struct _SysCounterInfo {
    char	*name;
    CARD64	resolution;
    CARD64	bracket_greater;
    CARD64	bracket_less;
    SyncCounterType counterType;  /* how can this counter change */
    void        (*QueryValue)(
#if NeedNestedPrototypes
			      pointer /*pCounter*/,
			      CARD64 * /*freshvalue*/
#endif
);
    void	(*BracketValues)(
#if NeedNestedPrototypes
				 pointer /*pCounter*/,
				 CARD64 * /*lessthan*/,
				 CARD64 * /*greaterthan*/
#endif
);
} SysCounterInfo;



typedef struct _SyncTrigger {
    SyncCounter *pCounter;
    CARD64	wait_value;	/* wait value */
    unsigned int value_type;     /* Absolute or Relative */
    unsigned int test_type;	/* transition or Comparision type */
    CARD64	test_value;	/* trigger event threshold value */
    Bool	(*CheckTrigger)(
#if NeedNestedPrototypes
				struct _SyncTrigger * /*pTrigger*/,
				CARD64 /*newval*/
#endif
				);
    void	(*TriggerFired)(
#if NeedNestedPrototypes
				struct _SyncTrigger * /*pTrigger*/
#endif
				);
    void	(*CounterDestroyed)(
#if NeedNestedPrototypes
				struct _SyncTrigger * /*pTrigger*/
#endif
				    );
} SyncTrigger;

typedef struct _SyncTriggerList {
    SyncTrigger *pTrigger;
    struct _SyncTriggerList *next;
} SyncTriggerList;

typedef struct _SyncAlarmClientList {
    ClientPtr	client;
    XID		delete_id;
    struct _SyncAlarmClientList *next;
} SyncAlarmClientList;

typedef struct _SyncAlarm {
    SyncTrigger trigger;
    ClientPtr	client;
    XSyncAlarm 	alarm_id;
    CARD64	delta;
    int		events;
    int		state;
    SyncAlarmClientList *pEventClients;
} SyncAlarm;

typedef struct {
    ClientPtr	client;
    CARD32 	delete_id;
    int		num_waitconditions;
} SyncAwaitHeader;

typedef struct {
    SyncTrigger trigger;
    CARD64	event_threshold;
    SyncAwaitHeader *pHeader;
} SyncAwait;

typedef union {
    SyncAwaitHeader header;
    SyncAwait	    await;
} SyncAwaitUnion;


extern pointer SyncCreateSystemCounter(
#if NeedFunctionPrototypes
    char *	/* name */,
    CARD64  	/* inital_value */,
    CARD64  	/* resolution */,
    SyncCounterType /* change characterization */,
    void        (* /*QueryValue*/ ) (), /* XXX prototype */
    void        (* /*BracketValues*/) ()
#endif
);

extern void SyncChangeCounter(
#if NeedFunctionPrototypes
    SyncCounter *	/* pCounter*/,
    CARD64  		/* new_value */
#endif
);

extern void SyncDestroySystemCounter(
#if NeedFunctionPrototypes
    pointer pCounter
#endif
);
extern void InitServertime();

#endif /* _SYNC_SERVER */
