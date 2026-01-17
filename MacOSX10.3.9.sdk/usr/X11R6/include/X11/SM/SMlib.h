/* $Xorg: SMlib.h,v 1.4 2001/02/09 02:03:30 xorgcvs Exp $ */

/*

Copyright 1993, 1998  The Open Group

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

/*
 * Author: Ralph Mor, X Consortium
 */

#ifndef _SMLIB_H_
#define _SMLIB_H_

#include <X11/SM/SM.h>
#include <X11/ICE/ICElib.h>


/*
 * Generic SM pointer
 */

typedef IcePointer SmPointer;


/*
 * Connection objects.  Defined in SMlibint.h
 */

typedef struct _SmcConn *SmcConn;
typedef struct _SmsConn *SmsConn;


/*
 * Session Management property
 */

typedef struct {
    int		length;		/* length (in bytes) of the value */
    SmPointer   value;		/* the value */
} SmPropValue;

typedef struct {
    char	*name;		/* name of property */
    char	*type;		/* type of property */
    int		num_vals;	/* number of values in property */
    SmPropValue *vals;		/* the values */
} SmProp;



/*
 * SmcCloseConnection status return
 */

typedef enum {
    SmcClosedNow,
    SmcClosedASAP,
    SmcConnectionInUse
} SmcCloseStatus;



/*
 * Client callbacks
 */

typedef void (*SmcSaveYourselfProc) (
#if NeedFunctionPrototypes
    SmcConn		/* smcConn */,
    SmPointer		/* clientData */,
    int  		/* saveType */,
    Bool		/* shutdown */,
    int			/* interactStyle */,
    Bool		/* fast */
#endif
);

typedef void (*SmcSaveYourselfPhase2Proc) (
#if NeedFunctionPrototypes
    SmcConn		/* smcConn */,
    SmPointer		/* clientData */
#endif
);

typedef void (*SmcInteractProc) (
#if NeedFunctionPrototypes
    SmcConn		/* smcConn */,
    SmPointer		/* clientData */
#endif
);

typedef void (*SmcDieProc) (
#if NeedFunctionPrototypes
    SmcConn		/* smcConn */,
    SmPointer		/* clientData */
#endif
);

typedef void (*SmcShutdownCancelledProc) (
#if NeedFunctionPrototypes
    SmcConn		/* smcConn */,
    SmPointer		/* clientData */
#endif
);

typedef void (*SmcSaveCompleteProc) (
#if NeedFunctionPrototypes
    SmcConn		/* smcConn */,
    SmPointer		/* clientData */
#endif
);

typedef void (*SmcPropReplyProc) (
#if NeedFunctionPrototypes
    SmcConn		/* smcConn */,
    SmPointer		/* clientData */,
    int			/* numProps */,
    SmProp **		/* props */
#endif
);


/*
 * Callbacks set up at SmcOpenConnection time
 */

typedef struct {

    struct {
	SmcSaveYourselfProc	 callback;
	SmPointer		 client_data;
    } save_yourself;

    struct {
	SmcDieProc		 callback;
	SmPointer		 client_data;
    } die;

    struct {
	SmcSaveCompleteProc	 callback;
	SmPointer		 client_data;
    } save_complete;

    struct {
	SmcShutdownCancelledProc callback;
	SmPointer		 client_data;
    } shutdown_cancelled;

} SmcCallbacks;

#define SmcSaveYourselfProcMask		(1L << 0)
#define SmcDieProcMask			(1L << 1)
#define SmcSaveCompleteProcMask		(1L << 2)
#define SmcShutdownCancelledProcMask	(1L << 3)



/*
 * Session manager callbacks
 */

typedef Status (*SmsRegisterClientProc) (
#if NeedFunctionPrototypes
    SmsConn 		/* smsConn */,
    SmPointer		/* managerData */,
    char *		/* previousId */				     
#endif
);

typedef void (*SmsInteractRequestProc) (
#if NeedFunctionPrototypes
    SmsConn		/* smsConn */,
    SmPointer		/* managerData */,
    int			/* dialogType */
#endif
);

typedef void (*SmsInteractDoneProc) (
#if NeedFunctionPrototypes
    SmsConn		/* smsConn */,
    SmPointer		/* managerData */,
    Bool		/* cancelShutdown */
#endif
);

typedef void (*SmsSaveYourselfRequestProc) (
#if NeedFunctionPrototypes
    SmsConn		/* smsConn */,
    SmPointer		/* managerData */,
    int  		/* saveType */,
    Bool		/* shutdown */,
    int			/* interactStyle */,
    Bool		/* fast */,
    Bool		/* global */
#endif
);

typedef void (*SmsSaveYourselfPhase2RequestProc) (
#if NeedFunctionPrototypes
    SmsConn		/* smsConn */,
    SmPointer		/* managerData */
#endif
);

typedef void (*SmsSaveYourselfDoneProc) (
#if NeedFunctionPrototypes
    SmsConn		/* smsConn */,
    SmPointer		/* managerData */,
    Bool		/* success */
#endif
);

typedef void (*SmsCloseConnectionProc) (
#if NeedFunctionPrototypes
    SmsConn		/* smsConn */,
    SmPointer		/* managerData */,
    int			/* count */,
    char **		/* reasonMsgs */
#endif
);

typedef void (*SmsSetPropertiesProc) (
#if NeedFunctionPrototypes
    SmsConn		/* smsConn */,
    SmPointer		/* managerData */,
    int			/* numProps */,
    SmProp **		/* props */
#endif
);

typedef void (*SmsDeletePropertiesProc) (
#if NeedFunctionPrototypes
    SmsConn		/* smsConn */,
    SmPointer		/* managerData */,
    int			/* numProps */,
    char **		/* propNames */
#endif
);

typedef void (*SmsGetPropertiesProc) (
#if NeedFunctionPrototypes
    SmsConn		/* smsConn */,
    SmPointer		/* managerData */
#endif
);


/*
 * Callbacks set up by a session manager when a new client connects.
 */

typedef struct {

    struct {
	SmsRegisterClientProc	callback;
	SmPointer		manager_data;
    } register_client;

    struct {
	SmsInteractRequestProc	callback;
	SmPointer		manager_data;
    } interact_request;

    struct {
	SmsInteractDoneProc	callback;
	SmPointer		manager_data;
    } interact_done;

    struct {
	SmsSaveYourselfRequestProc	callback;
	SmPointer			manager_data;
    } save_yourself_request;

    struct {
	SmsSaveYourselfPhase2RequestProc	callback;
	SmPointer				manager_data;
    } save_yourself_phase2_request;

    struct {
	SmsSaveYourselfDoneProc	callback;
	SmPointer		manager_data;
    } save_yourself_done;

    struct {
	SmsCloseConnectionProc	callback;
	SmPointer		manager_data;
    } close_connection;

    struct {
	SmsSetPropertiesProc	callback;
	SmPointer		manager_data;
    } set_properties;

    struct {
	SmsDeletePropertiesProc	callback;
	SmPointer		manager_data;
    } delete_properties;

    struct {
	SmsGetPropertiesProc	callback;
	SmPointer		manager_data;
    } get_properties;

} SmsCallbacks;


#define SmsRegisterClientProcMask		(1L << 0)
#define SmsInteractRequestProcMask		(1L << 1)
#define SmsInteractDoneProcMask			(1L << 2)
#define SmsSaveYourselfRequestProcMask  	(1L << 3)
#define SmsSaveYourselfP2RequestProcMask	(1L << 4)
#define SmsSaveYourselfDoneProcMask		(1L << 5)
#define SmsCloseConnectionProcMask		(1L << 6)
#define SmsSetPropertiesProcMask		(1L << 7)
#define SmsDeletePropertiesProcMask		(1L << 8)
#define SmsGetPropertiesProcMask		(1L << 9)



typedef Status (*SmsNewClientProc) (
#if NeedFunctionPrototypes
    SmsConn 		/* smsConn */,
    SmPointer		/* managerData */,
    unsigned long *	/* maskRet */,
    SmsCallbacks *	/* callbacksRet */,
    char **		/* failureReasonRet */
#endif
);



/*
 * Error handlers
 */

typedef void (*SmcErrorHandler) (
#if NeedFunctionPrototypes
    SmcConn		/* smcConn */,
    Bool		/* swap */,
    int			/* offendingMinorOpcode */,
    unsigned long 	/* offendingSequence */,
    int 		/* errorClass */,
    int			/* severity */,
    SmPointer		/* values */
#endif
);

typedef void (*SmsErrorHandler) (
#if NeedFunctionPrototypes
    SmsConn		/* smsConn */,
    Bool		/* swap */,
    int			/* offendingMinorOpcode */,
    unsigned long 	/* offendingSequence */,
    int 		/* errorClass */,
    int			/* severity */,
    SmPointer		/* values */
#endif
);



/*
 * Function Prototypes
 */

_XFUNCPROTOBEGIN

extern SmcConn SmcOpenConnection (
#if NeedFunctionPrototypes
    char *		/* networkIdsList */,
    SmPointer		/* context */,
    int			/* xsmpMajorRev */,
    int			/* xsmpMinorRev */,
    unsigned long	/* mask */,
    SmcCallbacks *	/* callbacks */,
    char *		/* previousId */,
    char **		/* clientIdRet */,
    int			/* errorLength */,
    char *		/* errorStringRet */
#endif
);

extern SmcCloseStatus SmcCloseConnection (
#if NeedFunctionPrototypes
    SmcConn		/* smcConn */,
    int			/* count */,
    char **		/* reasonMsgs */
#endif
);

extern void SmcModifyCallbacks (
#if NeedFunctionPrototypes
    SmcConn		/* smcConn */,
    unsigned long	/* mask */,
    SmcCallbacks *	/* callbacks */
#endif
);

extern void SmcSetProperties (
#if NeedFunctionPrototypes
    SmcConn		/* smcConn */,
    int      	        /* numProps */,
    SmProp **		/* props */
#endif
);

extern void SmcDeleteProperties (
#if NeedFunctionPrototypes
    SmcConn		/* smcConn */,
    int      	        /* numProps */,
    char **		/* propNames */
#endif
);

extern Status SmcGetProperties (
#if NeedFunctionPrototypes
    SmcConn		/* smcConn */,
    SmcPropReplyProc	/* propReplyProc */,
    SmPointer		/* clientData */
#endif
);

extern Status SmcInteractRequest (
#if NeedFunctionPrototypes
    SmcConn		/* smcConn */,
    int			/* dialogType */,
    SmcInteractProc	/* interactProc */,
    SmPointer		/* clientData */
#endif
);

extern void SmcInteractDone (
#if NeedFunctionPrototypes
    SmcConn		/* smcConn */,
    Bool 		/* cancelShutdown */
#endif
);

extern void SmcRequestSaveYourself (
#if NeedFunctionPrototypes
    SmcConn		/* smcConn */,
    int			/* saveType */,
    Bool 		/* shutdown */,
    int			/* interactStyle */,
    Bool		/* fast */,
    Bool		/* global */
#endif
);

extern Status SmcRequestSaveYourselfPhase2 (
#if NeedFunctionPrototypes
    SmcConn			/* smcConn */,
    SmcSaveYourselfPhase2Proc	/* saveYourselfPhase2Proc */,
    SmPointer			/* clientData */
#endif
);

extern void SmcSaveYourselfDone (
#if NeedFunctionPrototypes
    SmcConn		/* smcConn */,
    Bool		/* success */
#endif
);

extern int SmcProtocolVersion (
#if NeedFunctionPrototypes
    SmcConn		/* smcConn */
#endif
);

extern int SmcProtocolRevision (
#if NeedFunctionPrototypes
    SmcConn		/* smcConn */
#endif
);

extern char *SmcVendor (
#if NeedFunctionPrototypes
    SmcConn		/* smcConn */
#endif
);

extern char *SmcRelease (
#if NeedFunctionPrototypes
    SmcConn		/* smcConn */
#endif
);

extern char *SmcClientID (
#if NeedFunctionPrototypes
    SmcConn		/* smcConn */
#endif
);

extern IceConn SmcGetIceConnection (
#if NeedFunctionPrototypes
    SmcConn		/* smcConn */
#endif
);

extern Status SmsInitialize (
#if NeedFunctionPrototypes
    char *			/* vendor */,
    char *			/* release */,
    SmsNewClientProc		/* newClientProc */,
    SmPointer			/* managerData */,
    IceHostBasedAuthProc	/* hostBasedAuthProc */,
    int				/* errorLength */,
    char *			/* errorStringRet */
#endif
);

extern char *SmsClientHostName (
#if NeedFunctionPrototypes
    SmsConn		/* smsConn */
#endif
);

extern char *SmsGenerateClientID (
#if NeedFunctionPrototypes
    SmsConn		/* smsConn */
#endif
);

extern Status SmsRegisterClientReply (
#if NeedFunctionPrototypes
    SmsConn		/* smsConn */,
    char *		/* clientId */
#endif
);

extern void SmsSaveYourself (
#if NeedFunctionPrototypes
    SmsConn		/* smsConn */,
    int			/* saveType */,
    Bool 		/* shutdown */,
    int			/* interactStyle */,
    Bool		/* fast */
#endif
);

extern void SmsSaveYourselfPhase2 (
#if NeedFunctionPrototypes
    SmsConn		/* smsConn */
#endif
);

extern void SmsInteract (
#if NeedFunctionPrototypes
    SmsConn		/* smsConn */
#endif
);

extern void SmsDie (
#if NeedFunctionPrototypes
    SmsConn		/* smsConn */
#endif
);

extern void SmsSaveComplete (
#if NeedFunctionPrototypes
    SmsConn		/* smsConn */
#endif
);

extern void SmsShutdownCancelled (
#if NeedFunctionPrototypes
    SmsConn		/* smsConn */
#endif
);

extern void SmsReturnProperties (
#if NeedFunctionPrototypes
    SmsConn		/* smsConn */,
    int			/* numProps */,
    SmProp **		/* props */
#endif
);

extern void SmsCleanUp (
#if NeedFunctionPrototypes
    SmsConn		/* smsConn */
#endif
);

extern int SmsProtocolVersion (
#if NeedFunctionPrototypes
    SmsConn		/* smsConn */
#endif
);

extern int SmsProtocolRevision (
#if NeedFunctionPrototypes
    SmsConn		/* smsConn */
#endif
);

extern char *SmsClientID (
#if NeedFunctionPrototypes
    SmsConn		/* smsConn */
#endif
);

extern IceConn SmsGetIceConnection (
#if NeedFunctionPrototypes
    SmsConn		/* smsConn */
#endif
);

extern SmcErrorHandler SmcSetErrorHandler (
#if NeedFunctionPrototypes
    SmcErrorHandler 	/* handler */
#endif
);

extern SmsErrorHandler SmsSetErrorHandler (
#if NeedFunctionPrototypes
    SmsErrorHandler 	/* handler */
#endif
);

extern void SmFreeProperty (
#if NeedFunctionPrototypes
    SmProp *		/* prop */
#endif
);

extern void SmFreeReasons (
#if NeedFunctionPrototypes
    int			/* count */,
    char **		/* reasonMsgs */
#endif
);

_XFUNCPROTOEND

#endif /* _SMLIB_H_ */
