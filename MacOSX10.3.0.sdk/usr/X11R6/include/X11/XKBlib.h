/* $Xorg: XKBlib.h,v 1.6 2000/08/17 19:45:03 cpqbld Exp $ */
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
/* $XFree86: xc/lib/X11/XKBlib.h,v 3.3 2001/08/01 00:44:38 tsi Exp $ */

#ifndef _XKBLIB_H_
#define _XKBLIB_H_

#include <X11/Xlib.h>
#include <X11/extensions/XKBstr.h>

typedef struct _XkbAnyEvent {
	int 		type;		/* XkbAnyEvent */
	unsigned long 	serial;		/* # of last req processed by server */
	Bool 		send_event;	/* is this from a SendEvent request? */
	Display *	display;	/* Display the event was read from */
	Time 		time;		/* milliseconds */
	int 		xkb_type;	/* XKB event minor code */
	unsigned int 	device;		/* device ID */
} XkbAnyEvent;

typedef struct _XkbNewKeyboardNotify {
	int 		type;		/* XkbAnyEvent */
	unsigned long 	serial;		/* of last req processed by server */
	Bool 		send_event;	/* is this from a SendEvent request? */
	Display *	display;	/* Display the event was read from */
	Time 		time;		/* milliseconds */
	int 		xkb_type;	/* XkbNewKeyboardNotify */
	int	 	device;		/* device ID */
	int	 	old_device;	/* device ID of previous keyboard */
	int	 	min_key_code;	/* minimum key code */
	int		max_key_code;	/* maximum key code */
	int	 	old_min_key_code;/* min key code of previous kbd */
	int		old_max_key_code;/* max key code of previous kbd */
	unsigned int	changed;	/* changed aspects of the keyboard */
	char	 	req_major;	/* major and minor opcode of req */
	char	 	req_minor;	/* that caused change, if applicable */
} XkbNewKeyboardNotifyEvent;

typedef struct _XkbMapNotifyEvent {
	int 		type;		/* XkbAnyEvent */
	unsigned long 	serial;		/* of last req processed by server */
	Bool 		send_event;	/* is this from a SendEvent request */
	Display *	display;	/* Display the event was read from */
	Time 		time;		/* milliseconds */
	int 		xkb_type;	/* XkbMapNotify */
	int 		device;		/* device ID */
	unsigned int 	changed;	/* fields which have been changed */
	unsigned int 	flags;		/* reserved */
	int 		first_type;	/* first changed key type */
	int 		num_types;	/* number of changed key types */
	KeyCode		min_key_code;
	KeyCode		max_key_code;
	KeyCode		first_key_sym;
	KeyCode		first_key_act;
	KeyCode		first_key_behavior;
	KeyCode		first_key_explicit;
	KeyCode		first_modmap_key;  
	KeyCode		first_vmodmap_key;
	int		num_key_syms;
	int		num_key_acts;
	int		num_key_behaviors;
	int		num_key_explicit;
	int 		num_modmap_keys;
	int 		num_vmodmap_keys;
	unsigned int 	vmods;		/* mask of changed virtual mods */
} XkbMapNotifyEvent;

typedef struct _XkbStateNotifyEvent {
	int 		type;		/* XkbAnyEvent */
	unsigned long 	serial;		/* # of last req processed by server */
	Bool 		send_event;	/* is this from a SendEvent request? */
	Display *	display;	/* Display the event was read from */
	Time 		time;		/* milliseconds */
	int 		xkb_type;	/* XkbStateNotify */
	int 		device;		/* device ID */
	unsigned int 	changed;	/* mask of changed state components */
	int 		group;		/* keyboard group */
	int 		base_group;	/* base keyboard group */
	int 		latched_group;	/* latched keyboard group */
	int 		locked_group;	/* locked keyboard group */
	unsigned int	mods;		/* modifier state */
	unsigned int 	base_mods;	/* base modifier state */
	unsigned int	latched_mods;	/* latched modifiers */
	unsigned int	locked_mods;	/* locked modifiers */
	int 		compat_state;	/* compatibility state */
	unsigned char	grab_mods;	/* mods used for grabs */
	unsigned char	compat_grab_mods;/* grab mods for non-XKB clients */
	unsigned char	lookup_mods;	/* mods sent to clients */
	unsigned char	compat_lookup_mods; /* mods sent to non-XKB clients */
	int 		ptr_buttons;	/* pointer button state */
	KeyCode		keycode;	/* keycode that caused the change */
	char 		event_type;	/* KeyPress or KeyRelease */
	char 		req_major;	/* Major opcode of request */
	char 		req_minor;	/* Minor opcode of request */
} XkbStateNotifyEvent;

typedef struct _XkbControlsNotify {
	int 		type;		/* XkbAnyEvent */
	unsigned long 	serial;		/* of last req processed by server */
	Bool 		send_event;	/* is this from a SendEvent request? */
	Display *	display;	/* Display the event was read from */
	Time 		time;		/* milliseconds */
	int 		xkb_type;	/* XkbControlsNotify */
	int 		device;		/* device ID */
	unsigned int	changed_ctrls;	/* controls with changed sub-values */
	unsigned int 	enabled_ctrls;	/* controls currently enabled */
	unsigned int	enabled_ctrl_changes;/* controls just {en,dis}abled */
	int 		num_groups;	/* total groups on keyboard */
	KeyCode		keycode;	/* key that caused change or 0 */
	char 		event_type;	/* type of event that caused change */
	char 		req_major;	/* if keycode==0, major and minor */
	char 		req_minor;	/* opcode of req that caused change */
} XkbControlsNotifyEvent;

typedef struct _XkbIndicatorNotify {
	int 		type;		/* XkbAnyEvent */
	unsigned long 	serial;		/* of last req processed by server */
	Bool 		send_event;	/* is this from a SendEvent request? */
	Display *	display;	/* Display the event was read from */
	Time 		time;		/* milliseconds */
	int 		xkb_type;	/* XkbIndicatorNotify */
	int 		device;		/* device ID */
	unsigned int	changed;	/* indicators with new state or map */
	unsigned int	state;	 	/* current state of all indicators */
} XkbIndicatorNotifyEvent;

typedef struct _XkbNamesNotify {
	int 		type;		/* XkbAnyEvent */
	unsigned long 	serial;		/* of last req processed by server */
	Bool 		send_event;	/* is this from a SendEvent request? */
	Display *	display;	/* Display the event was read from */
	Time 		time;		/* milliseconds */
	int 		xkb_type;	/* XkbNamesNotify */
	int	 	device;		/* device ID */
	unsigned int 	changed;	/* names that have changed */
	int	 	first_type;	/* first key type with new name */
	int	 	num_types;	/* number of key types with new names */
	int	 	first_lvl;	/* first key type new new level names */
	int	 	num_lvls;	/* # of key types w/new level names */
	int	 	num_aliases;	/* total number of key aliases*/
	int	 	num_radio_groups;/* total number of radio groups */
	unsigned int 	changed_vmods;	/* virtual modifiers with new names */
	unsigned int 	changed_groups;	/* groups with new names */
	unsigned int 	changed_indicators;/* indicators with new names */
	int		first_key;	/* first key with new name */
	int		num_keys;	/* number of keys with new names */
} XkbNamesNotifyEvent;

typedef struct _XkbCompatMapNotify {
	int 		type;		/* XkbAnyEvent */
	unsigned long 	serial;		/* of last req processed by server */
	Bool 		send_event;	/* is this from a SendEvent request? */
	Display *	display;	/* Display the event was read from */
	Time 		time;		/* milliseconds */
	int 		xkb_type;	/* XkbCompatMapNotify */
	int	 	device;		/* device ID */
	unsigned int 	changed_groups; /* groups with new compat maps */
	int	 	first_si;	/* first new symbol interp */
	int	 	num_si;		/* number of new symbol interps */
	int	 	num_total_si;	/* total # of symbol interps */
} XkbCompatMapNotifyEvent;

typedef struct _XkbBellNotify {
	int 		type;		/* XkbAnyEvent */
	unsigned long 	serial;		/* of last req processed by server */
	Bool 		send_event;	/* is this from a SendEvent request? */
	Display *	display;	/* Display the event was read from */
	Time 		time;		/* milliseconds */
	int 		xkb_type;	/* XkbBellNotify */
	int	 	device;		/* device ID */
	int	 	percent;	/* requested volume as a % of maximum */
	int	 	pitch;		/* requested pitch in Hz */
	int	 	duration;	/* requested duration in useconds */
	int	 	bell_class;	/* (input extension) feedback class */
	int	 	bell_id;	/* (input extension) ID of feedback */
	Atom 		name;		/* "name" of requested bell */
	Window 		window;		/* window associated with event */
	Bool		event_only;	/* "event only" requested */
} XkbBellNotifyEvent;

typedef struct _XkbActionMessage {
	int 		type;		/* XkbAnyEvent */
	unsigned long 	serial;		/* of last req processed by server */
	Bool 		send_event;	/* is this from a SendEvent request? */
	Display *	display;	/* Display the event was read from */
	Time 		time;		/* milliseconds */
	int 		xkb_type;	/* XkbActionMessage */
	int	 	device;		/* device ID */
	KeyCode		keycode;	/* key that generated the event */
	Bool 		press;		/* true if act caused by key press */
	Bool 		key_event_follows;/* true if key event also generated */
	int		group;		/* effective group */
	unsigned int	mods;		/* effective mods */
	char 		message[XkbActionMessageLength+1]; 
					/* message -- leave space for NUL */
} XkbActionMessageEvent;

typedef struct _XkbAccessXNotify {
	int 		type;		/* XkbAnyEvent */
	unsigned long 	serial;		/* of last req processed by server */
	Bool 		send_event;	/* is this from a SendEvent request? */
	Display *	display;	/* Display the event was read from */
	Time 		time;		/* milliseconds */
	int 		xkb_type;	/* XkbAccessXNotify */
	int	 	device;		/* device ID */
	int	 	detail;		/* XkbAXN_* */
	int	 	keycode;	/* key of event */
	int	 	sk_delay;	/* current slow keys delay */
	int		debounce_delay;	/* current debounce delay */
} XkbAccessXNotifyEvent;

typedef struct _XkbExtensionDeviceNotify {
	int 		type;		/* XkbAnyEvent */
	unsigned long 	serial;		/* of last req processed by server */
	Bool 		send_event;	/* is this from a SendEvent request? */
	Display *	display;	/* Display the event was read from */
	Time 		time;		/* milliseconds */
	int 		xkb_type;	/* XkbExtensionDeviceNotify */
	int	 	device;		/* device ID */
	unsigned int	reason;		/* reason for the event */	
	unsigned int	supported;	/* mask of supported features */	
	unsigned int	unsupported;	/* mask of unsupported features */
					/* that some app tried to use */
	int	 	first_btn;	/* first button that changed */
	int	 	num_btns;	/* range of buttons changed */
	unsigned int	leds_defined;   /* indicators with names or maps */
	unsigned int	led_state;	/* current state of the indicators */
	int		led_class;	/* feedback class for led changes */
	int		led_id;   	/* feedback id for led changes */
} XkbExtensionDeviceNotifyEvent;

typedef union _XkbEvent {
	int				type;
	XkbAnyEvent			any;
	XkbNewKeyboardNotifyEvent	new_kbd;
	XkbMapNotifyEvent		map;
	XkbStateNotifyEvent		state;
	XkbControlsNotifyEvent		ctrls;
	XkbIndicatorNotifyEvent 	indicators;
	XkbNamesNotifyEvent		names;
	XkbCompatMapNotifyEvent		compat;
	XkbBellNotifyEvent		bell;
	XkbActionMessageEvent		message;
	XkbAccessXNotifyEvent		accessx;
	XkbExtensionDeviceNotifyEvent 	device;
	XEvent				core;
} XkbEvent;

typedef struct	_XkbKbdDpyState	XkbKbdDpyStateRec,*XkbKbdDpyStatePtr;

	/* XkbOpenDisplay error codes */
#define	XkbOD_Success		0
#define	XkbOD_BadLibraryVersion	1
#define	XkbOD_ConnectionRefused	2
#define	XkbOD_NonXkbServer	3
#define	XkbOD_BadServerVersion	4

	/* Values for XlibFlags */
#define	XkbLC_ForceLatin1Lookup		(1<<0)
#define	XkbLC_ConsumeLookupMods		(1<<1)
#define	XkbLC_AlwaysConsumeShiftAndLock (1<<2)
#define	XkbLC_IgnoreNewKeyboards	(1<<3)
#define	XkbLC_ControlFallback		(1<<4)
#define	XkbLC_ConsumeKeysOnComposeFail	(1<<29)
#define	XkbLC_ComposeLED		(1<<30)
#define	XkbLC_BeepOnComposeFail		(1<<31)

#define	XkbLC_AllComposeControls	(0xc0000000)
#define	XkbLC_AllControls		(0xc000001f)

_XFUNCPROTOBEGIN

extern	Bool	XkbIgnoreExtension(
#if NeedFunctionPrototypes
	Bool			/* ignore */
#endif
);

extern	Display *XkbOpenDisplay(
#if NeedFunctionPrototypes
	char *			/* name */,
	int *			/* ev_rtrn */,
	int *			/* err_rtrn */,
	int *			/* major_rtrn */,
	int *			/* minor_rtrn */,
	int *			/* reason */
#endif
);

extern	Bool	XkbQueryExtension(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	int *			/* opcodeReturn */,
	int *			/* eventBaseReturn */,
	int *			/* errorBaseReturn */,
	int *			/* majorRtrn */,
	int *			/* minorRtrn */
#endif
);

extern	Bool	XkbUseExtension(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	int *			/* major_rtrn */,
	int *			/* minor_rtrn */
#endif
);

extern	Bool	XkbLibraryVersion(
#if NeedFunctionPrototypes
	int *			/* libMajorRtrn */,
	int *			/* libMinorRtrn */
#endif
);

extern	unsigned int	XkbSetXlibControls(
#if NeedFunctionPrototypes
	Display*		/* dpy */,
	unsigned int		/* affect */,
	unsigned int		/* values */
#endif
);

extern	unsigned int	XkbGetXlibControls(
#if NeedFunctionPrototypes
	Display*		/* dpy */
#endif
);

typedef	Atom	(*XkbInternAtomFunc)(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	_Xconst char *		/* name */,
	Bool			/* only_if_exists */
#endif
);

typedef char *	(*XkbGetAtomNameFunc)(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	Atom			/* atom */
#endif
);

extern void		XkbSetAtomFuncs(
#if NeedFunctionPrototypes
	XkbInternAtomFunc	/* getAtom */,
	XkbGetAtomNameFunc	/* getName */
#endif
);

extern	KeySym XkbKeycodeToKeysym(
#if NeedFunctionPrototypes
		Display *	/* dpy */,
#if NeedWidePrototypes
		 unsigned int 	/* kc */,
#else
		 KeyCode 	/* kc */,
#endif
		 int 		/* group */,
		 int		/* level */
#endif
);

extern	unsigned int	XkbKeysymToModifiers(
#if NeedFunctionPrototypes
    Display *			/* dpy */,
    KeySym 			/* ks */
#endif
);

extern	Bool		XkbLookupKeySym(
#if NeedFunctionPrototypes
    Display *			/* dpy */,
    KeyCode 			/* keycode */,
    unsigned int 		/* modifiers */,
    unsigned int *		/* modifiers_return */,
    KeySym *			/* keysym_return */
#endif
);

extern	int		XkbLookupKeyBinding(
#if NeedFunctionPrototypes
    Display *			/* dpy */,
    KeySym 			/* sym_rtrn */,
    unsigned int 		/* mods */,
    char *			/* buffer */,
    int 			/* nbytes */,
    int * 			/* extra_rtrn */
#endif
);

extern	Bool		XkbTranslateKeyCode(
#if NeedFunctionPrototypes
    XkbDescPtr			/* xkb */,
    KeyCode 			/* keycode */,
    unsigned int 		/* modifiers */,
    unsigned int *		/* modifiers_return */,
    KeySym *			/* keysym_return */
#endif
);

extern	int		XkbTranslateKeySym(
#if NeedFunctionPrototypes
    Display *			/* dpy */,
    register KeySym *		/* sym_return */,
    unsigned int 		/* modifiers */,
    char *			/* buffer */,
    int 			/* nbytes */,
    int *			/* extra_rtrn */
#endif
);

extern	Bool	XkbSetAutoRepeatRate(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	unsigned int		/* deviceSpec */,
	unsigned int		/* delay */,
	unsigned int		/* interval */
#endif
);

extern	Bool	XkbGetAutoRepeatRate(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	unsigned int		/* deviceSpec */,
	unsigned int *		/* delayRtrn */,
	unsigned int *		/* intervalRtrn */
#endif
);

extern	Bool	XkbChangeEnabledControls(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	unsigned int		/* deviceSpec */,
	unsigned int		/* affect */,
	unsigned int		/* values */
#endif
);

extern	Bool	XkbDeviceBell(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	Window			/* win */,
	int			/* deviceSpec */,
	int			/* bellClass */,
	int			/* bellID */,
	int			/* percent */,
	Atom			/* name */
#endif
);

extern	Bool	XkbForceDeviceBell(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	int			/* deviceSpec */,
	int			/* bellClass */,
	int			/* bellID */,
	int			/* percent */
#endif
);

extern	Bool	XkbDeviceBellEvent(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	Window			/* win */,
	int			/* deviceSpec */,
	int			/* bellClass */,
	int			/* bellID */,
	int			/* percent */,
	Atom			/* name */
#endif
);

extern	Bool	XkbBell(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	Window			/* win */,
	int			/* percent */,
	Atom			/* name */
#endif
);

extern	Bool	XkbForceBell(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	int			/* percent */
#endif
);

extern	Bool	XkbBellEvent(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	Window			/* win */,
	int			/* percent */,
	Atom			/* name */
#endif
);

extern	Bool	XkbSelectEvents(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	unsigned int		/* deviceID */,
	unsigned int 		/* affect */,
	unsigned int 		/* values */
#endif
);

extern	Bool	XkbSelectEventDetails(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	unsigned int 		/* deviceID */,
	unsigned int 		/* eventType */,
	unsigned long 		/* affect */,
	unsigned long 		/* details */
#endif
);

extern	void	XkbNoteMapChanges(
#if NeedFunctionPrototypes
    XkbMapChangesPtr		/* old */,
    XkbMapNotifyEvent	*	/* new */,
    unsigned int	 	/* wanted */
#endif
);

extern	void	XkbNoteNameChanges(
#if NeedFunctionPrototypes
    XkbNameChangesPtr		/* old */,
    XkbNamesNotifyEvent	*	/* new */,
    unsigned int	 	/* wanted */
#endif
);

extern	Status	XkbGetIndicatorState(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	unsigned int		/* deviceSpec */,
	unsigned int *		/* pStateRtrn */
#endif
);

extern	Status	XkbGetDeviceIndicatorState(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	unsigned int		/* deviceSpec */,
	unsigned int		/* ledClass */,
	unsigned int		/* ledID */,
	unsigned int *		/* pStateRtrn */
#endif
);

extern	Status	 XkbGetIndicatorMap(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	unsigned long		/* which */,
	XkbDescPtr		/* desc */
#endif
);

extern	Bool	 XkbSetIndicatorMap(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	unsigned long 		/* which */,
	XkbDescPtr		/* desc */
#endif
);

#define	XkbNoteIndicatorMapChanges(o,n,w) \
				((o)->map_changes|=((n)->map_changes&(w)))
#define	XkbNoteIndicatorStateChanges(o,n,w)\
				((o)->state_changes|=((n)->state_changes&(w)))
#define	XkbGetIndicatorMapChanges(d,x,c) \
				(XkbGetIndicatorMap((d),(c)->map_changes,x)
#define	XkbChangeIndicatorMaps(d,x,c) \
				(XkbSetIndicatorMap((d),(c)->map_changes,x))

extern	Bool	XkbGetNamedIndicator(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	Atom			/* name */,
	int *			/* pNdxRtrn */,
	Bool *			/* pStateRtrn */,
	XkbIndicatorMapPtr	/* pMapRtrn */,
	Bool *			/* pRealRtrn */
#endif
);

extern	Bool	XkbGetNamedDeviceIndicator(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	unsigned int		/* deviceSpec */,
	unsigned int		/* ledClass */,
	unsigned int		/* ledID */,
	Atom			/* name */,
	int *			/* pNdxRtrn */,
	Bool *			/* pStateRtrn */,
	XkbIndicatorMapPtr	/* pMapRtrn */,
	Bool *			/* pRealRtrn */
#endif
);

extern	Bool	XkbSetNamedIndicator(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	Atom			/* name */,
	Bool			/* changeState */,
	Bool 			/* state */,
	Bool			/* createNewMap */,
	XkbIndicatorMapPtr	/* pMap */
#endif
);

extern	Bool	XkbSetNamedDeviceIndicator(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	unsigned int		/* deviceSpec */,
	unsigned int		/* ledClass */,
	unsigned int		/* ledID */,
	Atom			/* name */,
	Bool			/* changeState */,
	Bool 			/* state */,
	Bool			/* createNewMap */,
	XkbIndicatorMapPtr	/* pMap */
#endif
);

extern	Bool	XkbLockModifiers(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	unsigned int 		/* deviceSpec */,
	unsigned int 		/* affect */,
	unsigned int 		/* values */
#endif
);

extern	Bool	XkbLatchModifiers(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	unsigned int 		/* deviceSpec */,
	unsigned int 		/* affect */,
	unsigned int 		/* values */
#endif
);

extern	Bool	XkbLockGroup(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	unsigned int 		/* deviceSpec */,
	unsigned int 		/* group */
#endif
);

extern	Bool	XkbLatchGroup(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	unsigned int 		/* deviceSpec */,
	unsigned int 		/* group */
#endif
);

extern	Bool	XkbSetServerInternalMods(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	unsigned int 		/* deviceSpec */,
	unsigned int 		/* affectReal */,
	unsigned int 		/* realValues */,
	unsigned int		/* affectVirtual */,
	unsigned int		/* virtualValues */
#endif
);

extern	Bool	XkbSetIgnoreLockMods(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	unsigned int 		/* deviceSpec */,
	unsigned int 		/* affectReal */,
	unsigned int 		/* realValues */,
	unsigned int		/* affectVirtual */,
	unsigned int		/* virtualValues */
#endif
);


extern	Bool	XkbVirtualModsToReal(
#if NeedFunctionPrototypes
	XkbDescPtr		/* xkb */,
	unsigned int		/* virtual_mask */,
	unsigned int *		/* mask_rtrn */
#endif
);

extern	Bool	XkbComputeEffectiveMap(
#if NeedFunctionPrototypes
	XkbDescPtr 		/* xkb */,
	XkbKeyTypePtr		/* type */,
	unsigned char *		/* map_rtrn */
#endif
);

extern	Status XkbInitCanonicalKeyTypes(
#if NeedFunctionPrototypes
    XkbDescPtr			/* xkb */,
    unsigned int		/* which */,
    int				/* keypadVMod */
#endif
);

extern	XkbDescPtr XkbAllocKeyboard(
#if NeedFunctionPrototypes
	void
#endif
);

extern	void	XkbFreeKeyboard(
#if NeedFunctionPrototypes
	XkbDescPtr		/* xkb */,
	unsigned int		/* which */,
	Bool			/* freeDesc */
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
	unsigned int		/* nActions */
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

extern	XkbKeyTypePtr	XkbAddKeyType(
#if NeedFunctionPrototypes
    XkbDescPtr			/* xkb */,
    Atom			/* name */,
    int				/* map_count */,
    Bool			/* want_preserve */,
    int				/* num_lvls */
#endif
);

extern	Status XkbAllocIndicatorMaps(
#if NeedFunctionPrototypes
	XkbDescPtr		/* xkb */
#endif
);

extern	void XkbFreeIndicatorMaps(
#if NeedFunctionPrototypes
    XkbDescPtr			/* xkb */
#endif
);

extern	XkbDescPtr XkbGetMap(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	unsigned int 		/* which */,
	unsigned int 		/* deviceSpec */
#endif
);

extern	Status	XkbGetUpdatedMap(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	unsigned int 		/* which */,
	XkbDescPtr		/* desc */
#endif
);

extern	Status	XkbGetMapChanges(
#if NeedFunctionPrototypes
    Display *			/* dpy */,
    XkbDescPtr			/* xkb */,
    XkbMapChangesPtr		/* changes */
#endif
);


extern	Status	XkbRefreshKeyboardMapping(
#if NeedFunctionPrototypes
    XkbMapNotifyEvent *		/* event */
#endif
);

extern	Status	XkbGetKeyTypes(
#if NeedFunctionPrototypes
    Display *			/* dpy */,
    unsigned int		/* first */,
    unsigned int 		/* num */,
    XkbDescPtr			/* xkb */
#endif
);

extern	Status	XkbGetKeySyms(
#if NeedFunctionPrototypes
    Display *			/* dpy */,
    unsigned int		/* first */,
    unsigned int		/* num */,
    XkbDescPtr			/* xkb */
#endif
);

extern	Status	XkbGetKeyActions(
#if NeedFunctionPrototypes
    Display *			/* dpy */,
    unsigned int 		/* first */,
    unsigned int 		/* num */,
    XkbDescPtr			/* xkb */
#endif
);

extern	Status	XkbGetKeyBehaviors(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	unsigned int 		/* firstKey */,
	unsigned int		/* nKeys */,
	XkbDescPtr		/* desc */
#endif
);

extern	Status	XkbGetVirtualMods(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	unsigned int 		/* which */,
	XkbDescPtr		/* desc */
#endif
);

extern	Status	XkbGetKeyExplicitComponents(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	unsigned int 		/* firstKey */,
	unsigned int		/* nKeys */,
	XkbDescPtr		/* desc */
#endif
);

extern	Status	XkbGetKeyModifierMap(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	unsigned int 		/* firstKey */,
	unsigned int		/* nKeys */,
	XkbDescPtr		/* desc */
#endif
);

extern	Status	XkbAllocControls(
#if NeedFunctionPrototypes
	XkbDescPtr		/* xkb */,
	unsigned int		/* which*/
#endif
);

extern	void	XkbFreeControls(
#if NeedFunctionPrototypes
	XkbDescPtr		/* xkb */,
	unsigned int		/* which */,
	Bool			/* freeMap */
#endif
);

extern	Status	XkbGetControls(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	unsigned long		/* which */,
	XkbDescPtr		/* desc */
#endif
);

extern	Bool	XkbSetControls(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	unsigned long		/* which */,
	XkbDescPtr		/* desc */
#endif
);

extern	void	XkbNoteControlsChanges(
#if NeedFunctionPrototypes
    XkbControlsChangesPtr	/* old */,
    XkbControlsNotifyEvent *	/* new */,
    unsigned int	 	/* wanted */
#endif
);

#define	XkbGetControlsChanges(d,x,c)	XkbGetControls(d,(c)->changed_ctrls,x)
#define	XkbChangeControls(d,x,c)	XkbSetControls(d,(c)->changed_ctrls,x)

extern	Status	XkbAllocCompatMap(
#if NeedFunctionPrototypes
    XkbDescPtr			/* xkb */,
    unsigned int		/* which */,
    unsigned int		/* nInterpret */
#endif
);

extern	void	XkbFreeCompatMap(
#if NeedFunctionPrototypes
    XkbDescPtr			/* xkb */,
    unsigned int		/* which */,
    Bool			/* freeMap */
#endif
);

extern Status XkbGetCompatMap(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	unsigned int 		/* which */,
	XkbDescPtr 		/* xkb */
#endif
);

extern Bool XkbSetCompatMap(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	unsigned int 		/* which */,
	XkbDescPtr 		/* xkb */,
	Bool			/* updateActions */
#endif
);

extern	XkbSymInterpretPtr XkbAddSymInterpret(
#if NeedFunctionPrototypes
	XkbDescPtr		/* xkb */,
	XkbSymInterpretPtr	/* si */,
	Bool			/* updateMap */,
	XkbChangesPtr		/* changes */
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

extern	Status	XkbGetNames(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	unsigned int		/* which */,
	XkbDescPtr		/* desc */
#endif
);

extern	Bool	XkbSetNames(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	unsigned int		/* which */,
	unsigned int		/* firstType */,
	unsigned int		/* nTypes */,
	XkbDescPtr		/* desc */
#endif
);

extern	Bool	XkbChangeNames(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	XkbDescPtr		/* xkb */,
	XkbNameChangesPtr	/* changes */
#endif
);

extern	void XkbFreeNames(
#if NeedFunctionPrototypes
	XkbDescPtr		/* xkb */,
	unsigned int		/* which */,
	Bool			/* freeMap */
#endif
);


extern	Status	XkbGetState(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	unsigned int 		/* deviceSpec */,
	XkbStatePtr		/* rtrnState */
#endif
);

extern	Bool	XkbSetMap(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	unsigned int		/* which */,
	XkbDescPtr		/* desc */
#endif
);

extern	Bool	XkbChangeMap(
#if NeedFunctionPrototypes
	Display*		/* dpy */,
	XkbDescPtr		/* desc */,
	XkbMapChangesPtr	/* changes */
#endif
);

extern	Bool	XkbSetDetectableAutoRepeat(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	Bool			/* detectable */,
	Bool *			/* supported */
#endif
);

extern	Bool	XkbGetDetectableAutoRepeat(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	Bool *			/* supported */
#endif
);

extern	Bool	XkbSetAutoResetControls(
#if NeedFunctionPrototypes
    Display *			/* dpy */,
    unsigned int 		/* changes */,
    unsigned int *		/* auto_ctrls */,
    unsigned int *		/* auto_values */
#endif
);

extern	Bool	XkbGetAutoResetControls(
#if NeedFunctionPrototypes
    Display *			/* dpy */,
    unsigned int *		/* auto_ctrls */,
    unsigned int *		/* auto_ctrl_values */
#endif
);

extern	Bool	XkbSetPerClientControls(
#if NeedFunctionPrototypes
    Display *			/* dpy */,
    unsigned int		/* change */,
    unsigned int *		/* values */
#endif
);

extern	Bool	XkbGetPerClientControls(
#if NeedFunctionPrototypes
    Display *			/* dpy */,
    unsigned int *		/* ctrls */
#endif
);

extern Status XkbCopyKeyType(
#if NeedFunctionPrototypes
    XkbKeyTypePtr	/* from */,
    XkbKeyTypePtr	/* into */
#endif
);

extern Status XkbCopyKeyTypes(
#if NeedFunctionPrototypes
    XkbKeyTypePtr	/* from */,
    XkbKeyTypePtr	/* into */,
    int			/* num_types */
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

extern	KeySym *XkbResizeKeySyms(
#if NeedFunctionPrototypes
	XkbDescPtr		/* desc */,
	int 			/* forKey */,
	int 			/* symsNeeded */
#endif
);

extern	XkbAction *XkbResizeKeyActions(
#if NeedFunctionPrototypes
	XkbDescPtr		/* desc */,
	int 			/* forKey */,
	int 			/* actsNeeded */
#endif
);

extern	Status XkbChangeTypesOfKey(
#if NeedFunctionPrototypes
	XkbDescPtr		/* xkb */,
	int 			/* key */,
	int			/* num_groups */,
	unsigned int		/* groups */,
	int *			/* newTypes */,
	XkbMapChangesPtr	/* pChanges */
#endif
);

/***====================================================================***/

extern	XkbComponentListPtr	XkbListComponents(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	unsigned int		/* deviceSpec */,
	XkbComponentNamesPtr	/* ptrns */,
	int *			/* max_inout */
#endif
);

extern	void XkbFreeComponentList(
#if NeedFunctionPrototypes
	XkbComponentListPtr	/* list */
#endif
);

extern	XkbDescPtr XkbGetKeyboard(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	unsigned int 		/* which */,
	unsigned int 		/* deviceSpec */
#endif
);

extern XkbDescPtr XkbGetKeyboardByName(
#if NeedFunctionPrototypes
    Display *			/* dpy */,
    unsigned int		/* deviceSpec */,
    XkbComponentNamesPtr	/* names */,
    unsigned int 		/* want */,
    unsigned int 		/* need */,
    Bool			/* load */
#endif
);

/***====================================================================***/

extern	int	XkbKeyTypesForCoreSymbols(	/* returns # of groups */
#if NeedFunctionPrototypes
    XkbDescPtr	/* xkb */,			/* keyboard device */
    int		/* map_width */,		/* width of core KeySym array */
    KeySym *	/* core_syms */,		/* always mapWidth symbols */
    unsigned int	/* protected */,	/* explicit key types */
    int *	/* types_inout */,		/* always four type indices */
    KeySym * 	/* xkb_syms_rtrn */		/* must have enough space */
#endif
);

extern	Bool	XkbApplyCompatMapToKey(	/* False only on error */
#if NeedFunctionPrototypes
    XkbDescPtr		/* xkb */,		/* keymap to be edited */
    KeyCode		/* key */,		/* key to be updated */
    XkbChangesPtr	/* changes */		/* resulting changes to map */
#endif
);

extern	Bool	XkbUpdateMapFromCore( /* False only on error */
#if NeedFunctionPrototypes
    XkbDescPtr		/* xkb */,		/* XKB keyboard to be edited */
    KeyCode		/* first_key */,	/* first changed key */
    int			/* num_keys */, 	/* number of changed keys */
    int			/* map_width */,	/* width of core keymap */
    KeySym *		/* core_keysyms */,	/* symbols from core keymap */
    XkbChangesPtr	/* changes */		/* resulting changes */
#endif
);

/***====================================================================***/

extern	XkbDeviceLedInfoPtr	XkbAddDeviceLedInfo(
#if NeedFunctionPrototypes
	XkbDeviceInfoPtr	/* devi */,
	unsigned int		/* ledClass */,
	unsigned int		/* ledId */
#endif
);

extern	Status			XkbResizeDeviceButtonActions(
#if NeedFunctionPrototypes
	XkbDeviceInfoPtr	/* devi */,
	unsigned int		/* newTotal */
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

extern	void	XkbNoteDeviceChanges(
#if NeedFunctionPrototypes
    XkbDeviceChangesPtr			/* old */,
    XkbExtensionDeviceNotifyEvent *	/* new */,
    unsigned int	 		/* wanted */
#endif
);

extern	XkbDeviceInfoPtr XkbGetDeviceInfo(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	unsigned int 		/* which */,
	unsigned int		/* deviceSpec */,
	unsigned int		/* ledClass */,
	unsigned int		/* ledID */
#endif
);

extern	Status	XkbGetDeviceInfoChanges(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	XkbDeviceInfoPtr	/* devi */,
	XkbDeviceChangesPtr 	/* changes */
#endif
);

extern	Status	XkbGetDeviceButtonActions(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	XkbDeviceInfoPtr	/* devi */,
	Bool			/* all */,
	unsigned int		/* first */,
	unsigned int		/* nBtns */
#endif
);

extern	Status	XkbGetDeviceLedInfo(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	XkbDeviceInfoPtr	/* devi */,
	unsigned int		/* ledClass (class, XIDflt, XIAll) */,
	unsigned int		/* ledId (id, XIDflt, XIAll) */,
	unsigned int		/* which (XkbXI_Indicator{Names,Map}Mask */
#endif
);

extern	Bool	XkbSetDeviceInfo(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	unsigned int		/* which */,
	XkbDeviceInfoPtr	/* devi */
#endif
);

extern	Bool	XkbChangeDeviceInfo(
#if NeedFunctionPrototypes
	Display*		/* dpy */,
	XkbDeviceInfoPtr	/* desc */,
	XkbDeviceChangesPtr	/* changes */
#endif
);

extern  Bool XkbSetDeviceLedInfo(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	XkbDeviceInfoPtr	/* devi */,
	unsigned int 		/* ledClass */,
	unsigned int		/* ledID */,
	unsigned int		/* which */
#endif
);

extern	Bool XkbSetDeviceButtonActions(
#if NeedFunctionPrototypes
	Display *		/* dpy */,
	XkbDeviceInfoPtr	/* devi */,
	unsigned int		/* first */,
	unsigned int		/* nBtns */
#endif
);

/***====================================================================***/

extern	char	XkbToControl(
#if NeedFunctionPrototypes
	char		/* c */
#endif
);

/***====================================================================***/

extern	Bool XkbSetDebuggingFlags(
#if NeedFunctionPrototypes
    Display *		/* dpy */,
    unsigned int	/* mask */,
    unsigned int	/* flags */,
    char *		/* msg */,
    unsigned int	/* ctrls_mask */,
    unsigned int	/* ctrls */,
    unsigned int *	/* rtrn_flags */,
    unsigned int *	/* rtrn_ctrls */
#endif
);

extern	Bool XkbApplyVirtualModChanges(
#if NeedFunctionPrototypes
   XkbDescPtr		/* xkb */,
   unsigned int		/* changed */,
   XkbChangesPtr	/* changes */
#endif
);

_XFUNCPROTOEND

#endif /* _XKBLIB_H_ */
