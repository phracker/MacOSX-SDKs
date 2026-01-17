/* $Xorg: XKBsrv.h,v 1.3 2000/08/18 04:05:45 coskrey Exp $ */
/************************************************************
Copyright (c) 1993 by Silicon Graphics Computer Systems, Inc.

Permission to use, copy, modify, and distribute this
software and its documentation for any purpose and without
fee is hereby granted, provided that the above copyright
notice appear in all copies and that both that copyright
notice and this permission notice appear in supporting
documentation, and that the name of Silicon Graphics not be 
used in advertising or publicity pertaining to distribution 
of the software without specific prior written permission.
Silicon Graphics makes no representation about the suitability 
of this software for any purpose. It is provided "as is"
without any express or implied warranty.

SILICON GRAPHICS DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS 
SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY 
AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL SILICON
GRAPHICS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL 
DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, 
DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE 
OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION  WITH
THE USE OR PERFORMANCE OF THIS SOFTWARE.

********************************************************/
/* $XFree86: xc/include/extensions/XKBsrv.h,v 3.22 2002/11/20 04:49:01 dawes Exp $ */

#ifndef _XKBSRV_H_
#define	_XKBSRV_H_

#ifdef XKB_IN_SERVER
#define XkbAllocClientMap		SrvXkbAllocClientMap
#define XkbAllocServerMap		SrvXkbAllocServerMap
#define XkbChangeTypesOfKey		SrvXkbChangeTypesOfKey
#define	XkbAddKeyType			SrvXkbAddKeyType
#define XkbCopyKeyType			SrvXkbCopyKeyType
#define XkbCopyKeyTypes			SrvXkbCopyKeyTypes
#define XkbFreeClientMap		SrvXkbFreeClientMap
#define XkbFreeServerMap		SrvXkbFreeServerMap
#define XkbInitCanonicalKeyTypes	SrvXkbInitCanonicalKeyTypes
#define	XkbKeyTypesForCoreSymbols	SrvXkbKeyTypesForCoreSymbols
#define	XkbApplyCompatMapToKey		SrvXkbApplyCompatMapToKey
#define	XkbUpdateMapFromCore		SrvXkbUpdateMapFromCore
#define XkbResizeKeyActions		SrvXkbResizeKeyActions
#define XkbResizeKeySyms		SrvXkbResizeKeySyms
#define XkbResizeKeyType		SrvXkbResizeKeyType
#define XkbAllocCompatMap		SrvXkbAllocCompatMap
#define XkbAllocControls		SrvXkbAllocControls
#define XkbAllocIndicatorMaps		SrvXkbAllocIndicatorMaps
#define XkbAllocKeyboard		SrvXkbAllocKeyboard
#define XkbAllocNames			SrvXkbAllocNames
#define XkbFreeCompatMap		SrvXkbFreeCompatMap
#define XkbFreeControls			SrvXkbFreeControls
#define XkbFreeIndicatorMaps		SrvXkbFreeIndicatorMaps
#define XkbFreeKeyboard			SrvXkbFreeKeyboard
#define XkbFreeNames			SrvXkbFreeNames
#define	XkbAddDeviceLedInfo		SrvXkbAddDeviceLedInfo
#define	XkbAllocDeviceInfo		SrvXkbAllocDeviceInfo
#define	XkbFreeDeviceInfo		SrvXkbFreeDeviceInfo
#define	XkbResizeDeviceButtonActions	SrvXkbResizeDeviceButtonActions
#define XkbLatchModifiers		SrvXkbLatchModifiers
#define XkbLatchGroup			SrvXkbLatchGroup
#define XkbVirtualModsToReal		SrvXkbVirtualModsToReal
#define	XkbChangeKeycodeRange		SrvXkbChangeKeycodeRange
#define	XkbApplyVirtualModChanges	SrvXkbApplyVirtualModChanges
#define	XkbUpdateActionVirtualMods	SrvXkbUpdateActionVirtualMods
#define XkbUpdateKeyTypeVirtualMods	SrvXkbUpdateKeyTypeVirtualMods
#endif

#include <X11/extensions/XKBstr.h>
#include <X11/extensions/XKBproto.h>
#include "inputstr.h"

typedef struct _XkbInterest {
	DeviceIntPtr		dev;
	ClientPtr		client;
	XID			resource;
	struct _XkbInterest *	next;
	CARD16			extDevNotifyMask;
	CARD16			stateNotifyMask;
	CARD16			namesNotifyMask;
	CARD32 			ctrlsNotifyMask;
	CARD8			compatNotifyMask;
	BOOL			bellNotifyMask;
	BOOL			actionMessageMask;
	CARD16			accessXNotifyMask;
	CARD32			iStateNotifyMask;
	CARD32			iMapNotifyMask;
	CARD16			altSymsNotifyMask;
	CARD32			autoCtrls;
	CARD32			autoCtrlValues;
} XkbInterestRec,*XkbInterestPtr;

typedef struct _XkbRadioGroup {
	CARD8		flags;
	CARD8		nMembers;
	CARD8		dfltDown;
	CARD8		currentDown;
	CARD8		members[XkbRGMaxMembers];
} XkbRadioGroupRec, *XkbRadioGroupPtr;

typedef struct	_XkbEventCause {
	CARD8		kc;
	CARD8		event;
	CARD8		mjr;
	CARD8		mnr;
	ClientPtr	client;
} XkbEventCauseRec,*XkbEventCausePtr;
#define	XkbSetCauseKey(c,k,e)	{ (c)->kc= (k),(c)->event= (e),\
				  (c)->mjr= (c)->mnr= 0; \
				  (c)->client= NULL; }
#define	XkbSetCauseReq(c,j,n,cl) { (c)->kc= (c)->event= 0,\
				  (c)->mjr= (j),(c)->mnr= (n);\
				  (c)->client= (cl); }
#define	XkbSetCauseCoreReq(c,e,cl) XkbSetCauseReq(c,e,0,cl)
#define	XkbSetCauseXkbReq(c,e,cl)  XkbSetCauseReq(c,XkbReqCode,e,cl)
#define	XkbSetCauseUnknown(c)	   XkbSetCauseKey(c,0,0)

#define	_OFF_TIMER		0
#define	_KRG_WARN_TIMER		1
#define	_KRG_TIMER		2
#define	_SK_TIMEOUT_TIMER	3
#define	_ALL_TIMEOUT_TIMER	4

#define	_BEEP_NONE		0
#define	_BEEP_FEATURE_ON	1
#define	_BEEP_FEATURE_OFF	2
#define	_BEEP_FEATURE_CHANGE	3
#define	_BEEP_SLOW_WARN		4
#define	_BEEP_SLOW_PRESS	5
#define	_BEEP_SLOW_ACCEPT	6
#define	_BEEP_SLOW_REJECT	7
#define	_BEEP_SLOW_RELEASE	8
#define	_BEEP_STICKY_LATCH	9
#define	_BEEP_STICKY_LOCK	10
#define	_BEEP_STICKY_UNLOCK	11
#define	_BEEP_LED_ON		12
#define	_BEEP_LED_OFF		13
#define	_BEEP_LED_CHANGE	14
#define	_BEEP_BOUNCE_REJECT	15

typedef struct _XkbSrvInfo {
	XkbStateRec	 prev_state;
	XkbStateRec	 state;
	XkbDescPtr	 desc;

	DeviceIntPtr	 device;
	KbdCtrlProcPtr	 kbdProc;

	XkbRadioGroupPtr radioGroups;
	CARD8		 nRadioGroups;
	CARD8		 clearMods;
	CARD8		 setMods;
	INT16		 groupChange;

	CARD16		 dfltPtrDelta;

	double		 mouseKeysCurve;
	double		 mouseKeysCurveFactor;
	INT16		 mouseKeysDX;
	INT16		 mouseKeysDY;
	CARD8		 mouseKeysFlags;
	Bool		 mouseKeysAccel;
	CARD8		 mouseKeysCounter;

	CARD8		 lockedPtrButtons;
	CARD8		 shiftKeyCount;
	KeyCode		 mouseKey;
	KeyCode		 inactiveKey;
	KeyCode		 slowKey;
	KeyCode		 repeatKey;
	CARD8		 krgTimerActive;
	CARD8		 beepType;
	CARD8		 beepCount;

	CARD32		 flags;
	CARD32		 lastPtrEventTime;
	CARD32		 lastShiftEventTime;
	OsTimerPtr	 beepTimer;
	OsTimerPtr	 mouseKeyTimer;
	OsTimerPtr	 slowKeysTimer;
	OsTimerPtr	 bounceKeysTimer;
	OsTimerPtr	 repeatKeyTimer;
	OsTimerPtr	 krgTimer;
} XkbSrvInfoRec, *XkbSrvInfoPtr;

#define	XkbSLI_IsDefault	(1L<<0)
#define	XkbSLI_HasOwnState	(1L<<1)

typedef struct	_XkbSrvLedInfo {
	CARD16			flags;
	CARD16			class;
	CARD16			id;
	union {
	    KbdFeedbackPtr	kf;
	    LedFeedbackPtr	lf;
	} 			fb;

	CARD32			physIndicators;
	CARD32			autoState;
	CARD32			explicitState;
	CARD32			effectiveState;

	CARD32			mapsPresent;
	CARD32			namesPresent;
	XkbIndicatorMapPtr	maps;
	Atom *			names;

	CARD32			usesBase;
	CARD32			usesLatched;
	CARD32			usesLocked;
	CARD32			usesEffective;
	CARD32			usesCompat;
	CARD32			usesControls;

	CARD32			usedComponents;
} XkbSrvLedInfoRec, *XkbSrvLedInfoPtr;

/*
 * Settings for xkbClientFlags field (used by DIX)
 * These flags _must_ not overlap with XkbPCF_*
 */
#define	_XkbClientInitialized		(1<<15)

#define	_XkbWantsDetectableAutoRepeat(c)\
	((c)->xkbClientFlags&XkbPCF_DetectableAutoRepeatMask)

/*
 * Settings for flags field
 */
#define	_XkbStateNotifyInProgress	(1<<0)

/***====================================================================***/

#define XkbAX_KRGMask	 (XkbSlowKeysMask|XkbBounceKeysMask)
#define	XkbAllFilteredEventsMask \
	(XkbAccessXKeysMask|XkbRepeatKeysMask|XkbMouseKeysAccelMask|XkbAX_KRGMask)

/***====================================================================***/

extern int	XkbReqCode;
extern int	XkbEventBase;
extern int	XkbKeyboardErrorCode;
extern int	XkbDisableLockActions;
extern char *	XkbBaseDirectory;
extern char *	XkbInitialMap;
extern int	_XkbClientMajor;
extern int	_XkbClientMinor;
extern unsigned	int XkbXIUnsupported;

extern char *	XkbModelUsed,*XkbLayoutUsed,*XkbVariantUsed,*XkbOptionsUsed;
extern Bool	noXkbExtension;
extern Bool	XkbWantRulesProp;

extern pointer	XkbLastRepeatEvent;

extern CARD32	xkbDebugFlags;
extern CARD32	xkbDebugCtrls;

#define	_XkbAlloc(s)		xalloc((s))
#define	_XkbCalloc(n,s)		Xcalloc((n)*(s))
#define	_XkbRealloc(o,s)	Xrealloc((o),(s))
#define	_XkbTypedAlloc(t)	((t *)xalloc(sizeof(t)))
#define	_XkbTypedCalloc(n,t)	((t *)Xcalloc((n)*sizeof(t)))
#define	_XkbTypedRealloc(o,n,t) \
	((o)?(t *)Xrealloc((o),(n)*sizeof(t)):_XkbTypedCalloc(n,t))
#define	_XkbClearElems(a,f,l,t)	bzero(&(a)[f],((l)-(f)+1)*sizeof(t))
#define	_XkbFree(p)		Xfree(p)

#define	_XkbLibError(c,l,d) \
	{ _XkbErrCode= (c); _XkbErrLocation= (l); _XkbErrData= (d); }
#define	_XkbErrCode2(a,b) ((XID)((((unsigned int)(a))<<24)|((b)&0xffffff)))
#define	_XkbErrCode3(a,b,c)	_XkbErrCode2(a,(((unsigned int)(b))<<16)|(c))
#define	_XkbErrCode4(a,b,c,d) _XkbErrCode3(a,b,((((unsigned int)(c))<<8)|(d)))

extern	int	DeviceKeyPress,DeviceKeyRelease;
extern	int	DeviceButtonPress,DeviceButtonRelease;

#ifdef XINPUT
#define	_XkbIsPressEvent(t)	(((t)==KeyPress)||((t)==DeviceKeyPress))
#define	_XkbIsReleaseEvent(t)	(((t)==KeyRelease)||((t)==DeviceKeyRelease))
#else
#define	_XkbIsPressEvent(t)	((t)==KeyPress)
#define	_XkbIsReleaseEvent(t)	((t)==KeyRelease)
#endif

#define	_XkbCoreKeycodeInRange(c,k)	(((k)>=(c)->curKeySyms.minKeyCode)&&\
					 ((k)<=(c)->curKeySyms.maxKeyCode))
#define	_XkbCoreNumKeys(c)	((c)->curKeySyms.maxKeyCode-\
				 (c)->curKeySyms.minKeyCode+1)

#define	XConvertCase(s,l,u)	XkbConvertCase(s,l,u)
#undef	IsKeypadKey
#define	IsKeypadKey(s)		XkbKSIsKeypad(s)

#define	Status		int
#define	XPointer	pointer
#define	Display		struct _XDisplay

#ifndef True
#define	True	1
#define	False	0
#endif

#ifndef PATH_MAX
#ifdef MAXPATHLEN
#define	PATH_MAX MAXPATHLEN
#else
#define	PATH_MAX 1024
#endif
#endif

_XFUNCPROTOBEGIN

extern void XkbUseMsg(
#if NeedFunctionPrototypes
    void
#endif
);

extern int XkbProcessArguments(
#if NeedFunctionPrototypes
    int				/* argc */,
    char **			/* argv */,
    int				/* i */
#endif
);

extern	void	XkbFreeCompatMap(
#if NeedFunctionPrototypes
    XkbDescPtr			/* xkb */,
    unsigned int		/* which */,
    Bool			/* freeMap */
#endif
);

extern	void XkbFreeNames(
#if NeedFunctionPrototypes
	XkbDescPtr		/* xkb */,
	unsigned int		/* which */,
	Bool			/* freeMap */
#endif
);

extern DeviceIntPtr _XkbLookupAnyDevice(
#if NeedFunctionPrototypes
    int			/* id */,
    int *		/* why_rtrn */
#endif
);

extern DeviceIntPtr _XkbLookupKeyboard(
#if NeedFunctionPrototypes
    int			/* id */,
    int *		/* why_rtrn */
#endif
);

extern DeviceIntPtr _XkbLookupBellDevice(
#if NeedFunctionPrototypes
    int			/* id */,
    int *		/* why_rtrn */
#endif
);

extern DeviceIntPtr _XkbLookupLedDevice(
#if NeedFunctionPrototypes
    int			/* id */,
    int *		/* why_rtrn */
#endif
);

extern DeviceIntPtr _XkbLookupButtonDevice(
#if NeedFunctionPrototypes
    int			/* id */,
    int *		/* why_rtrn */
#endif
);

extern	XkbDescPtr XkbAllocKeyboard(
#if NeedFunctionPrototypes
	void
#endif
);

extern	Status XkbAllocClientMap(
#if NeedFunctionPrototypes
	XkbDescPtr		/* xkb */,
	unsigned int		/* which */,
	unsigned int		/* nTypes */
#endif
);

extern	Status XkbAllocServerMap(
#if NeedFunctionPrototypes
	XkbDescPtr		/* xkb */,
	unsigned int		/* which */,
	unsigned int		/* nNewActions */
#endif
);

extern	void	XkbFreeClientMap(
#if NeedFunctionPrototypes
    XkbDescPtr			/* xkb */,
    unsigned int		/* what */,
    Bool			/* freeMap */
#endif
);

extern	void	XkbFreeServerMap(
#if NeedFunctionPrototypes
    XkbDescPtr			/* xkb */,
    unsigned int		/* what */,
    Bool			/* freeMap */
#endif
);

extern	Status XkbAllocIndicatorMaps(
#if NeedFunctionPrototypes
	XkbDescPtr		/* xkb */
#endif
);

extern	Status	XkbAllocCompatMap(
#if NeedFunctionPrototypes
    XkbDescPtr			/* xkb */,
    unsigned int		/* which */,
    unsigned int		/* nInterpret */
#endif
);

extern	Status XkbAllocNames(
#if NeedFunctionPrototypes
	XkbDescPtr		/* xkb */,
	unsigned int		/* which */,
	int			/* nTotalRG */,
	int			/* nTotalAliases */
#endif
);

extern	Status	XkbAllocControls(
#if NeedFunctionPrototypes
	XkbDescPtr		/* xkb */,
	unsigned int		/* which*/
#endif
);

extern	Status	XkbCopyKeyType(
#if NeedFunctionPrototypes
    XkbKeyTypePtr		/* from */,
    XkbKeyTypePtr		/* into */
#endif
);

extern	Status	XkbCopyKeyTypes(
#if NeedFunctionPrototypes
    XkbKeyTypePtr		/* from */,
    XkbKeyTypePtr		/* into */,
    int				/* num_types */
#endif
);

extern	Status	XkbResizeKeyType(
#if NeedFunctionPrototypes
    XkbDescPtr		/* xkb */,
    int			/* type_ndx */,
    int			/* map_count */,
    Bool		/* want_preserve */,
    int			/* new_num_lvls */
#endif
);

extern	void	XkbFreeKeyboard(
#if NeedFunctionPrototypes
	XkbDescPtr		/* xkb */,
	unsigned int		/* which */,
	Bool			/* freeDesc */
#endif
);

extern  void XkbSetActionKeyMods(
#if NeedFunctionPrototypes
	XkbDescPtr		/* xkb */,
	XkbAction *		/* act */,
	unsigned int 		/* mods */
#endif
);

extern Bool XkbCheckActionVMods(
#if NeedFunctionPrototypes
	XkbDescPtr		/* xkb */,
	XkbAction *		/* act */,
	unsigned int 		/* changed */
#endif
);

extern Bool XkbApplyVModChanges(
#if NeedFunctionPrototypes
    XkbSrvInfoPtr	/* xkbi */,
    unsigned int	/* changed */,
    XkbChangesPtr	/* pChanges */,
    unsigned int *	/* needChecksRtrn */,
    XkbEventCausePtr	/* cause */
#endif
);

extern void XkbApplyVModChangesToAllDevices(
#if NeedFunctionPrototypes
    DeviceIntPtr	/* dev */,
    XkbDescPtr 		/* xkb */,
    unsigned int 	/* changed */,
    XkbEventCausePtr	/* cause */
#endif
);

extern	unsigned int XkbMaskForVMask(
#if NeedFunctionPrototypes
    XkbDescPtr		/* xkb */,
    unsigned int	/* vmask */
#endif
);

extern Bool XkbVirtualModsToReal(
#if NeedFunctionPrototypes
	XkbDescPtr	/* xkb */,
	unsigned int	/* virtua_mask */,
	unsigned int *	/* mask_rtrn */
#endif
);

extern	unsigned int	XkbAdjustGroup(
#if NeedFunctionPrototypes
    int			/* group */,
    XkbControlsPtr	/* ctrls */
#endif
);

extern KeySym *XkbResizeKeySyms(
#if NeedFunctionPrototypes
    XkbDescPtr		/* xkb */,
    int 		/* key */,
    int 		/* needed */
#endif
);

extern XkbAction *XkbResizeKeyActions(
#if NeedFunctionPrototypes
    XkbDescPtr		/* xkb */,
    int 		/* key */,
    int 		/* needed */
#endif
);

extern void XkbUpdateKeyTypesFromCore(
#if NeedFunctionPrototypes
    DeviceIntPtr	/* pXDev */,
    KeyCode 		/* first */,
    CARD8 		/* num */,
    XkbChangesPtr	/* pChanges */
#endif
);

extern	void XkbUpdateDescActions(	
#if NeedFunctionPrototypes
    XkbDescPtr		/* xkb */,
    KeyCode		/* first */,
    CARD8		/* num */,
    XkbChangesPtr	/* changes */
#endif
);

extern void XkbUpdateActions(
#if NeedFunctionPrototypes
    DeviceIntPtr	/* pXDev */,
    KeyCode 		/* first */,
    CARD8 		/* num */,
    XkbChangesPtr  	/* pChanges */,
    unsigned int *	/* needChecksRtrn */,
    XkbEventCausePtr	/* cause */
#endif
);

extern void XkbUpdateCoreDescription(
#if NeedFunctionPrototypes
    DeviceIntPtr	/* keybd */,
    Bool		/* resize */
#endif
);

extern void XkbApplyMappingChange(
#if NeedFunctionPrototypes
    DeviceIntPtr	/* pXDev */,
    CARD8 		/* request */,
    KeyCode 		/* firstKey */,
    CARD8 		/* num */,
    ClientPtr		/* client */
#endif
);

extern void XkbSetIndicators(
#if NeedFunctionPrototypes
    DeviceIntPtr		/* pXDev */,
    CARD32			/* affect */,
    CARD32			/* values */,
    XkbEventCausePtr		/* cause */
#endif
);

extern void XkbUpdateIndicators(
#if NeedFunctionPrototypes
    DeviceIntPtr		/* keybd */,
    CARD32		 	/* changed */,
    Bool			/* check_edevs */,
    XkbChangesPtr		/* pChanges */,
    XkbEventCausePtr		/* cause */
#endif
);

extern XkbSrvLedInfoPtr XkbAllocSrvLedInfo(
#if NeedFunctionPrototypes
    DeviceIntPtr		/* dev */,
    KbdFeedbackPtr		/* kf */,
    LedFeedbackPtr		/* lf */,
    unsigned int		/* needed_parts */
#endif
);

extern XkbSrvLedInfoPtr XkbFindSrvLedInfo(
#if NeedFunctionPrototypes
    DeviceIntPtr		/* dev */,
    unsigned int		/* class */,
    unsigned int		/* id */,
    unsigned int		/* needed_parts */
#endif
);

extern void XkbApplyLedNameChanges(
#if NeedFunctionPrototypes
    DeviceIntPtr		/* dev */,
    XkbSrvLedInfoPtr		/* sli */,
    unsigned int		/* changed_names */,
    xkbExtensionDeviceNotify *	/* ed */,
    XkbChangesPtr		/* changes */,
    XkbEventCausePtr		/* cause */
#endif
);

extern void XkbApplyLedMapChanges(
#if NeedFunctionPrototypes
    DeviceIntPtr		/* dev */,
    XkbSrvLedInfoPtr		/* sli */,
    unsigned int		/* changed_maps */,
    xkbExtensionDeviceNotify *	/* ed */,
    XkbChangesPtr		/* changes */,
    XkbEventCausePtr		/* cause */
#endif
);

extern void XkbApplyLedStateChanges(
#if NeedFunctionPrototypes
    DeviceIntPtr		/* dev */,
    XkbSrvLedInfoPtr		/* sli */,
    unsigned int		/* changed_leds */,
    xkbExtensionDeviceNotify *	/* ed */,
    XkbChangesPtr		/* changes */,
    XkbEventCausePtr		/* cause */
#endif
);

extern void XkbUpdateLedAutoState(
#if NeedFunctionPrototypes
    DeviceIntPtr		/* dev */,
    XkbSrvLedInfoPtr		/* sli */,
    unsigned int		/* maps_to_check */,
    xkbExtensionDeviceNotify *	/* ed */,
    XkbChangesPtr		/* changes */,
    XkbEventCausePtr		/* cause */
#endif
);

extern void XkbFlushLedEvents(	
#if NeedFunctionPrototypes
    DeviceIntPtr		/* dev */,
    DeviceIntPtr		/* kbd */,
    XkbSrvLedInfoPtr		/* sli */,
    xkbExtensionDeviceNotify *	/* ed */,
    XkbChangesPtr		/* changes */,
    XkbEventCausePtr		/* cause */
#endif
);

extern void XkbUpdateAllDeviceIndicators(
#if NeedFunctionPrototypes
    XkbChangesPtr		/* changes */,
    XkbEventCausePtr		/* cause */
#endif
);

extern unsigned int XkbIndicatorsToUpdate(
#if NeedFunctionPrototypes
    DeviceIntPtr		/* dev */,
    unsigned long		/* state_changes */,
    Bool			/* enabled_ctrl_changes */
#endif
);

extern void XkbComputeDerivedState(
#if NeedFunctionPrototypes
    XkbSrvInfoPtr		/* xkbi */
#endif
);

extern void XkbCheckSecondaryEffects(
#if NeedFunctionPrototypes
    XkbSrvInfoPtr		/* xkbi */,
    unsigned int		/* which */,
    XkbChangesPtr		/* changes */,
    XkbEventCausePtr		/* cause */
#endif
);

extern void XkbCheckIndicatorMaps(
#if NeedFunctionPrototypes
    DeviceIntPtr		/* dev */,
    XkbSrvLedInfoPtr		/* sli */,
    unsigned int		/* which */
#endif
);

extern unsigned int XkbStateChangedFlags(
#if NeedFunctionPrototypes
    XkbStatePtr			/* old */,
    XkbStatePtr			/* new */
#endif
);

extern	void XkbSendStateNotify(
#if NeedFunctionPrototypes
       DeviceIntPtr	/* kbd */,
       xkbStateNotify *	/* pSN */
#endif
);

extern	void XkbSendMapNotify(
#if NeedFunctionPrototypes
       DeviceIntPtr	/* kbd */,
       xkbMapNotify *	/* ev */
#endif
);

extern	int  XkbComputeControlsNotify(
#if NeedFunctionPrototypes
	DeviceIntPtr		/* kbd */,
	XkbControlsPtr		/* old */,
	XkbControlsPtr		/* new */,
	xkbControlsNotify *	/* pCN */,
        Bool			/* forceCtrlProc */
#endif
);

extern	void XkbSendControlsNotify(
#if NeedFunctionPrototypes
       DeviceIntPtr		/* kbd */,
       xkbControlsNotify *	/* ev */
#endif
);

extern	void XkbSendCompatMapNotify(
#if NeedFunctionPrototypes
	DeviceIntPtr		/* kbd */,
	xkbCompatMapNotify *	/* ev */
#endif
);

extern	void XkbSendIndicatorNotify(
#if NeedFunctionPrototypes
       DeviceIntPtr		/* kbd */,
       int			/* xkbType */,
       xkbIndicatorNotify *	/* ev */
#endif
);

extern	void XkbHandleBell(
#if NeedFunctionPrototypes
       BOOL		/* force */,
       BOOL		/* eventOnly */,
       DeviceIntPtr	/* kbd */,
       CARD8		/* percent */,
       pointer 		/* ctrl */,
       CARD8		/* class */,
       Atom		/* name */,
       WindowPtr	/* pWin */,
       ClientPtr	/* pClient */
#endif
);

extern	void XkbSendAccessXNotify(
#if NeedFunctionPrototypes
       DeviceIntPtr		/* kbd */,
       xkbAccessXNotify *	/* pEv */
#endif
);

extern	void XkbSendNamesNotify(
#if NeedFunctionPrototypes
       DeviceIntPtr	/* kbd */,
       xkbNamesNotify *	/* ev */
#endif
);

extern	void XkbSendCompatNotify(
#if NeedFunctionPrototypes
       DeviceIntPtr		/* kbd */,
       xkbCompatMapNotify *	/* ev */
#endif
);

extern	void XkbSendActionMessage(
#if NeedFunctionPrototypes
       DeviceIntPtr		/* kbd */,
       xkbActionMessage *	/* ev */
#endif
);

extern	void XkbSendExtensionDeviceNotify(
#if NeedFunctionPrototypes
       DeviceIntPtr			/* kbd */,
       ClientPtr			/* client */,
       xkbExtensionDeviceNotify *	/* ev */
#endif
);

extern void XkbSendNotification(
#if NeedFunctionPrototypes
    DeviceIntPtr		/* kbd */,
    XkbChangesPtr		/* pChanges */,
    XkbEventCausePtr		/* cause */
#endif
);

extern void XkbProcessKeyboardEvent(
#if NeedFunctionPrototypes
    struct _xEvent * 		/* xE */,
    DeviceIntPtr		/* keybd */,
    int 			/* count */
#endif
);

extern void XkbProcessOtherEvent(
#if NeedFunctionPrototypes
    struct _xEvent * 		/* xE */,
    DeviceIntPtr		/* keybd */,
    int 			/* count */
#endif
);

extern void XkbHandleActions(
#if NeedFunctionPrototypes
    DeviceIntPtr		/* dev */,
    DeviceIntPtr		/* kbd */,
    struct _xEvent * 		/* xE */,
    int 			/* count */
#endif
);

extern Bool XkbEnableDisableControls(
#if NeedFunctionPrototypes
    XkbSrvInfoPtr	/* xkbi */,
    unsigned long	/* change */,
    unsigned long	/* newValues */,
    XkbChangesPtr	/* changes */,
    XkbEventCausePtr	/* cause */
#endif
);

extern void AccessXInit(
#if NeedFunctionPrototypes
    DeviceIntPtr        /* dev */
#endif
);

extern Bool AccessXFilterPressEvent(
#if NeedFunctionPrototypes
    register struct _xEvent *	/* xE */,
    register DeviceIntPtr	/* keybd */,
    int				/* count */
#endif
);

extern Bool AccessXFilterReleaseEvent(
#if NeedFunctionPrototypes
    register struct _xEvent *	/* xE */,
    register DeviceIntPtr	/* keybd */,
    int				/* count */
#endif
);

extern void AccessXCancelRepeatKey(
#if NeedFunctionPrototypes
    XkbSrvInfoPtr	/* xkbi */,
    KeyCode		/* key */
#endif
);

extern void AccessXComputeCurveFactor(
#if NeedFunctionPrototypes
    XkbSrvInfoPtr	/* xkbi */,
    XkbControlsPtr	/* ctrls */
#endif
);

extern	XkbDeviceLedInfoPtr	XkbAddDeviceLedInfo(
#if NeedFunctionPrototypes
	XkbDeviceInfoPtr	/* devi */,
	unsigned int		/* ledClass */,
	unsigned int		/* ledId */
#endif
);

extern	XkbDeviceInfoPtr	XkbAllocDeviceInfo(
#if NeedFunctionPrototypes
	unsigned int		/* deviceSpec */,
	unsigned int		/* nButtons */,
	unsigned int		/* szLeds */
#endif
);

extern	void XkbFreeDeviceInfo(
#if NeedFunctionPrototypes
	XkbDeviceInfoPtr	/* devi */,
	unsigned int		/* which */,
	Bool			/* freeDevI */
#endif
);

extern Status XkbResizeDeviceButtonActions(
#if NeedFunctionPrototypes
        XkbDeviceInfoPtr        /* devi */,
        unsigned int            /* newTotal */
#endif
);

extern	XkbInterestPtr XkbFindClientResource(
#if NeedFunctionPrototypes
       DevicePtr	/* inDev */,
       ClientPtr	/* client */
#endif
);

extern	XkbInterestPtr XkbAddClientResource(
#if NeedFunctionPrototypes
       DevicePtr	/* inDev */,
       ClientPtr	/* client */,
       XID		/* id */
#endif
);

extern	int XkbRemoveClient(
#if NeedFunctionPrototypes
       DevicePtr	/* inDev */,
       ClientPtr	/* client */
#endif
);

extern	int XkbRemoveResourceClient(
#if NeedFunctionPrototypes
       DevicePtr	/* inDev */,
       XID		/* id */
#endif
);

extern int XkbDDXInitDevice(
#if NeedFunctionPrototypes
    DeviceIntPtr        /* dev */
#endif
);

extern	int XkbDDXAccessXBeep(
#if NeedFunctionPrototypes
    DeviceIntPtr        /* dev */,
    unsigned int	/* what */,
    unsigned int	/* which */
#endif
);

extern	void XkbDDXKeyClick(
#if NeedFunctionPrototypes
    DeviceIntPtr	/* dev */,
    int			/* keycode */,
    int			/* synthetic */
#endif
);

extern 	int XkbDDXUsesSoftRepeat(
#if NeedFunctionPrototypes
    DeviceIntPtr	/* dev */
#endif
);

extern	void XkbDDXKeybdCtrlProc(
#if NeedFunctionPrototypes
	DeviceIntPtr	/* dev */,
	KeybdCtrl *	/* ctrl */
#endif
);

extern void XkbDDXChangeControls(
#if NeedFunctionPrototypes
	DeviceIntPtr	/* dev */,
	XkbControlsPtr 	/* old */,
	XkbControlsPtr 	/* new */
#endif
);

extern void XkbDDXUpdateIndicators(
#if NeedFunctionPrototypes
	DeviceIntPtr	/* keybd */,
	CARD32		/* newState */
#endif
);

extern void XkbDDXUpdateDeviceIndicators(
#if NeedFunctionPrototypes
	DeviceIntPtr		/* dev */,
	XkbSrvLedInfoPtr	/* sli */,
	CARD32			/* newState */
#endif
);

extern void XkbDDXFakePointerButton(
#if NeedFunctionPrototypes
	int 		/* event */,
	int		/* button */
#endif
);

extern void XkbDDXFakePointerMotion(
#if NeedFunctionPrototypes
 	unsigned int	/* flags */,
	int		/* x */,
	int		/* y */
#endif
);

extern void XkbDDXFakeDeviceButton(
#if NeedFunctionPrototypes
	DeviceIntPtr	/* dev */,
	Bool		/* press */,
	int		/* button */
#endif
);

extern int XkbDDXTerminateServer(
#if NeedFunctionPrototypes
	DeviceIntPtr	/* dev */,
	KeyCode		/* key */,
	XkbAction *	/* act */
#endif
);

extern int XkbDDXSwitchScreen(
#if NeedFunctionPrototypes
	DeviceIntPtr	/* dev */,
	KeyCode		/* key */,
	XkbAction *	/* act */
#endif
);

extern int XkbDDXPrivate(
#if NeedFunctionPrototypes
	DeviceIntPtr	/* dev */,
	KeyCode		/* key */,
	XkbAction *	/* act */
#endif
);

extern void XkbDisableComputedAutoRepeats(
#if NeedFunctionPrototypes
	DeviceIntPtr 	/* pXDev */,
	unsigned int	/* key */
#endif
);

extern void XkbSetRepeatKeys(
#if NeedFunctionPrototypes
	DeviceIntPtr 	/* pXDev */,
	int		/* key */,
	int	 	/* onoff */
#endif
);

extern	int XkbLatchModifiers(
#if NeedFunctionPrototypes
	DeviceIntPtr 	/* pXDev */,
	CARD8 		/* mask */,
	CARD8 		/* latches */
#endif
);

extern	int XkbLatchGroup(
#if NeedFunctionPrototypes
	DeviceIntPtr  	/* pXDev */,
	int	  	/* group */
#endif
);

extern	void XkbClearAllLatchesAndLocks(
#if NeedFunctionPrototypes
	DeviceIntPtr		/* dev */,
	XkbSrvInfoPtr		/* xkbi */,
	Bool			/* genEv */,
	XkbEventCausePtr	/* cause */
#endif
);

extern	void	XkbSetRulesDflts(
#if NeedFunctionPrototypes
	char *			/* rulesFile */,
	char *			/* model */,
	char *			/* layout */,
	char *			/* variant */,
	char *			/* options */
#endif
);

extern	void	XkbInitDevice(
#if NeedFunctionPrototypes
	DeviceIntPtr 	/* pXDev */
#endif
);

extern	Bool	XkbInitKeyboardDeviceStruct(
#if NeedFunctionPrototypes
	DeviceIntPtr 		/* pXDev */,
	XkbComponentNamesPtr	/* pNames */,
	KeySymsPtr		/* pSyms */,
	CARD8 			/* pMods */[],
	BellProcPtr		/* bellProc */,
	KbdCtrlProcPtr		/* ctrlProc */
#endif
);

extern	int SProcXkbDispatch(
#if NeedFunctionPrototypes
	ClientPtr		/* client */
#endif
);

extern XkbGeometryPtr XkbLookupNamedGeometry(
#if NeedFunctionPrototypes
	DeviceIntPtr		/* dev */,
	Atom			/* name */,
	Bool *			/* shouldFree */
#endif
);

extern char *	_XkbDupString(
#if NeedFunctionPrototypes
	char *			/* str */
#endif
);

extern void	XkbConvertCase(
#if NeedFunctionPrototypes
	KeySym 			/* sym */,
	KeySym *		/* lower */,
	KeySym *		/* upper */
#endif
);

extern	Status	 XkbChangeKeycodeRange(	
#if NeedFunctionPrototypes
	XkbDescPtr		/* xkb */,
	int 			/* minKC */,
	int 			/* maxKC */,
	XkbChangesPtr		/* changes */
#endif
);

extern int XkbFinishDeviceInit(
#if NeedFunctionPrototypes
	DeviceIntPtr		/* pXDev */
#endif
);

extern void XkbFreeSrvLedInfo(
#if NeedFunctionPrototypes
	XkbSrvLedInfoPtr	/* sli */
#endif
);

extern void XkbFreeInfo(
#if NeedFunctionPrototypes
	XkbSrvInfoPtr		/* xkbi */
#endif
);

extern Status XkbChangeTypesOfKey(
#if NeedFunctionPrototypes
	XkbDescPtr		/* xkb */,
	int			/* key */,
	int			/* nGroups */,
	unsigned int		/* groups */,
	int *			/* newTypesIn */,
	XkbMapChangesPtr	/* changes */
#endif
);

extern XkbKeyTypePtr XkbAddKeyType(
#if NeedFunctionPrototypes
	XkbDescPtr		/* xkb */,
	Atom			/* name */,
	int			/* map_count */,
	Bool			/* want_preserve */,
	int			/* num_lvls */
#endif
);

extern Status XkbInitCanonicalKeyTypes(
#if NeedFunctionPrototypes
	XkbDescPtr		/* xkb */,
	unsigned int		/* which */,
	int			/* keypadVMod */
#endif
);

extern int XkbKeyTypesForCoreSymbols(
#if NeedFunctionPrototypes
	XkbDescPtr		/* xkb */,
	int			/* map_width */,
	KeySym *		/* core_syms */,
	unsigned int		/* protected */,
	int *			/* types_inout */,
	KeySym *		/* xkb_syms_rtrn */
#endif
);

extern Bool XkbApplyCompatMapToKey(
#if NeedFunctionPrototypes
	XkbDescPtr		/* xkb */,
	KeyCode			/* key */,
	XkbChangesPtr		/* changes */
#endif
);

extern Bool XkbUpdateMapFromCore(
#if NeedFunctionPrototypes
	XkbDescPtr		/* xkb */,
	KeyCode			/* first_key */,
	int			/* num_keys */,
	int			/* map_width */,
	KeySym *		/* core_keysyms */,
	XkbChangesPtr		/* changes */
#endif
);

extern void XkbFreeControls(
#if NeedFunctionPrototypes
	XkbDescPtr		/* xkb */,
	unsigned int		/* which */,
	Bool			/* freeMap */
#endif
);

extern void XkbFreeIndicatorMaps(
#if NeedFunctionPrototypes
	XkbDescPtr		/* xkb */
#endif
);

extern Bool XkbApplyVirtualModChanges(
#if NeedFunctionPrototypes
	XkbDescPtr		/* xkb */,
	unsigned int		/* changed */,
	XkbChangesPtr		/* changes */
#endif
);

extern Bool XkbUpdateActionVirtualMods(
#if NeedFunctionPrototypes
	XkbDescPtr		/* xkb */,
	XkbAction *		/* act */,
	unsigned int		/* changed */
#endif
);

extern void XkbUpdateKeyTypeVirtualMods(
#if NeedFunctionPrototypes
	XkbDescPtr		/* xkb */,
	XkbKeyTypePtr		/* type */,
	unsigned int		/* changed */,
	XkbChangesPtr		/* changes */
#endif
);

extern void XkbSendNewKeyboardNotify(
#if NeedFunctionPrototypes
	DeviceIntPtr		/* kbd */,
	xkbNewKeyboardNotify *	/* pNKN */
#endif
);

#ifdef XKBSRV_NEED_FILE_FUNCS

#include <X11/extensions/XKMformat.h>
#include <X11/extensions/XKBfile.h>
#include <X11/extensions/XKBrules.h>

#define	_XkbListKeymaps		0
#define	_XkbListKeycodes	1
#define	_XkbListTypes		2
#define	_XkbListCompat		3
#define	_XkbListSymbols		4
#define	_XkbListGeometry	5
#define	_XkbListNumComponents	6

typedef struct _XkbSrvListInfo {
	int		szPool;
	int		nPool;
	char *		pool;

	int		maxRtrn;
	int		nTotal;

	char *		pattern[_XkbListNumComponents];
	int		nFound[_XkbListNumComponents];
} XkbSrvListInfoRec,*XkbSrvListInfoPtr;

char *
XkbGetRulesDflts(
#if NeedFunctionPrototypes
	XkbRF_VarDefsPtr	/* defs */
#endif
);

extern void	XkbSetRulesUsed(
#if NeedFunctionPrototypes
	XkbRF_VarDefsPtr	/* defs */
#endif
);


extern	Status	XkbDDXList(
#if NeedFunctionPrototypes
	DeviceIntPtr		/* dev */,
	XkbSrvListInfoPtr	/* listing */,
	ClientPtr		/* client */
#endif
);

extern	unsigned int XkbDDXLoadKeymapByNames(
#if NeedFunctionPrototypes
	DeviceIntPtr		/* keybd */,
	XkbComponentNamesPtr	/* names */,
	unsigned int		/* want */,
	unsigned int		/* need */,
	XkbFileInfoPtr		/* finfoRtrn */,
	char *			/* keymapNameRtrn */,
	int 			/* keymapNameRtrnLen */
#endif
);

extern	Bool XkbDDXNamesFromRules(
#if NeedFunctionPrototypes
	DeviceIntPtr		/* keybd */,
	char *			/* rules */,
	XkbRF_VarDefsPtr	/* defs */,
	XkbComponentNamesPtr	/* names */
#endif
);

extern	FILE *XkbDDXOpenConfigFile(
#if NeedFunctionPrototypes
	char *	/* mapName */,
	char *	/* fileNameRtrn */,
	int	/* fileNameRtrnLen */
#endif
);

extern	Bool XkbDDXApplyConfig(
#if NeedFunctionPrototypes
	XPointer	/* cfg_in */,
	XkbSrvInfoPtr	/* xkbi */
#endif
);

extern XPointer XkbDDXPreloadConfig(
#if NeedFunctionPrototypes
	char **			/* rulesFileRtrn */,
	XkbRF_VarDefsPtr	/* defs */,
	XkbComponentNamesPtr	/* names */,
	DeviceIntPtr		/* dev */
#endif
);

extern	int _XkbStrCaseCmp(
#if NeedFunctionPrototypes
	char *			/* str1 */,
	char *			/* str2 */
#endif
);

#endif /* XKBSRV_NEED_FILE_FUNCS */


_XFUNCPROTOEND

#define	XkbAtomGetString(d,s)	NameForAtom(s)

#endif /* _XKBSRV_H_ */


