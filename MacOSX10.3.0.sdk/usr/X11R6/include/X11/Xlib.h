/* $Xorg: Xlib.h,v 1.6 2001/02/09 02:03:38 xorgcvs Exp $ */
/* 

Copyright 1985, 1986, 1987, 1991, 1998  The Open Group

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
/* $XFree86: xc/lib/X11/Xlib.h,v 3.23 2002/05/31 18:45:42 dawes Exp $ */


/*
 *	Xlib.h - Header definition and support file for the C subroutine
 *	interface library (Xlib) to the X Window System Protocol (V11).
 *	Structures and symbols starting with "_" are private to the library.
 */
#ifndef _XLIB_H_
#define _XLIB_H_

#define XlibSpecificationRelease 6

#ifdef USG
#ifndef __TYPES__
#include <sys/types.h>			/* forgot to protect it... */
#define __TYPES__
#endif /* __TYPES__ */
#else
#if defined(_POSIX_SOURCE) && defined(MOTOROLA)
#undef _POSIX_SOURCE
#include <sys/types.h>
#define _POSIX_SOURCE
#else
#include <sys/types.h>
#endif
#endif /* USG */

#include <X11/X.h>

/* applications should not depend on these two headers being included! */
#include <X11/Xfuncproto.h>
#include <X11/Xosdefs.h>

#ifndef X_WCHAR
#ifdef X_NOT_STDC_ENV
#ifndef SCO324
#ifndef ISC
#define X_WCHAR
#endif
#endif
#endif
#endif

#ifndef X_WCHAR
#include <stddef.h>
#else
#ifdef __UNIXOS2__
#include <stdlib.h>
#else
/* replace this with #include or typedef appropriate for your system */
typedef unsigned long wchar_t;
#endif
#endif

#if defined(ISC) && defined(USE_XMBTOWC)
#define wctomb(a,b)	_Xwctomb(a,b)
#define mblen(a,b)	_Xmblen(a,b) 
#ifndef USE_XWCHAR_STRING
#define mbtowc(a,b,c)	_Xmbtowc(a,b,c)
#endif
#endif

/* API mentioning "UTF8" or "utf8" is an XFree86 extension, introduced in
   November 2000. Its presence is indicated through the following macro. */
#define X_HAVE_UTF8_STRING 1

typedef char *XPointer;

#define Bool int
#define Status int
#define True 1
#define False 0

#define QueuedAlready 0
#define QueuedAfterReading 1
#define QueuedAfterFlush 2

#define ConnectionNumber(dpy) 	(((_XPrivDisplay)dpy)->fd)
#define RootWindow(dpy, scr) 	(ScreenOfDisplay(dpy,scr)->root)
#define DefaultScreen(dpy) 	(((_XPrivDisplay)dpy)->default_screen)
#define DefaultRootWindow(dpy) 	(ScreenOfDisplay(dpy,DefaultScreen(dpy))->root)
#define DefaultVisual(dpy, scr) (ScreenOfDisplay(dpy,scr)->root_visual)
#define DefaultGC(dpy, scr) 	(ScreenOfDisplay(dpy,scr)->default_gc)
#define BlackPixel(dpy, scr) 	(ScreenOfDisplay(dpy,scr)->black_pixel)
#define WhitePixel(dpy, scr) 	(ScreenOfDisplay(dpy,scr)->white_pixel)
#define AllPlanes 		((unsigned long)~0L)
#define QLength(dpy) 		(((_XPrivDisplay)dpy)->qlen)
#define DisplayWidth(dpy, scr) 	(ScreenOfDisplay(dpy,scr)->width)
#define DisplayHeight(dpy, scr) (ScreenOfDisplay(dpy,scr)->height)
#define DisplayWidthMM(dpy, scr)(ScreenOfDisplay(dpy,scr)->mwidth)
#define DisplayHeightMM(dpy, scr)(ScreenOfDisplay(dpy,scr)->mheight)
#define DisplayPlanes(dpy, scr) (ScreenOfDisplay(dpy,scr)->root_depth)
#define DisplayCells(dpy, scr) 	(DefaultVisual(dpy,scr)->map_entries)
#define ScreenCount(dpy) 	(((_XPrivDisplay)dpy)->nscreens)
#define ServerVendor(dpy) 	(((_XPrivDisplay)dpy)->vendor)
#define ProtocolVersion(dpy) 	(((_XPrivDisplay)dpy)->proto_major_version)
#define ProtocolRevision(dpy) 	(((_XPrivDisplay)dpy)->proto_minor_version)
#define VendorRelease(dpy) 	(((_XPrivDisplay)dpy)->release)
#define DisplayString(dpy) 	(((_XPrivDisplay)dpy)->display_name)
#define DefaultDepth(dpy, scr) 	(ScreenOfDisplay(dpy,scr)->root_depth)
#define DefaultColormap(dpy, scr)(ScreenOfDisplay(dpy,scr)->cmap)
#define BitmapUnit(dpy) 	(((_XPrivDisplay)dpy)->bitmap_unit)
#define BitmapBitOrder(dpy) 	(((_XPrivDisplay)dpy)->bitmap_bit_order)
#define BitmapPad(dpy) 		(((_XPrivDisplay)dpy)->bitmap_pad)
#define ImageByteOrder(dpy) 	(((_XPrivDisplay)dpy)->byte_order)
#ifdef CRAY /* unable to get WORD64 without pulling in other symbols */
#define NextRequest(dpy)	XNextRequest(dpy)
#else
#define NextRequest(dpy)	(((_XPrivDisplay)dpy)->request + 1)
#endif
#define LastKnownRequestProcessed(dpy)	(((_XPrivDisplay)dpy)->last_request_read)

/* macros for screen oriented applications (toolkit) */
#define ScreenOfDisplay(dpy, scr)(&((_XPrivDisplay)dpy)->screens[scr])
#define DefaultScreenOfDisplay(dpy) ScreenOfDisplay(dpy,DefaultScreen(dpy))
#define DisplayOfScreen(s)	((s)->display)
#define RootWindowOfScreen(s)	((s)->root)
#define BlackPixelOfScreen(s)	((s)->black_pixel)
#define WhitePixelOfScreen(s)	((s)->white_pixel)
#define DefaultColormapOfScreen(s)((s)->cmap)
#define DefaultDepthOfScreen(s)	((s)->root_depth)
#define DefaultGCOfScreen(s)	((s)->default_gc)
#define DefaultVisualOfScreen(s)((s)->root_visual)
#define WidthOfScreen(s)	((s)->width)
#define HeightOfScreen(s)	((s)->height)
#define WidthMMOfScreen(s)	((s)->mwidth)
#define HeightMMOfScreen(s)	((s)->mheight)
#define PlanesOfScreen(s)	((s)->root_depth)
#define CellsOfScreen(s)	(DefaultVisualOfScreen((s))->map_entries)
#define MinCmapsOfScreen(s)	((s)->min_maps)
#define MaxCmapsOfScreen(s)	((s)->max_maps)
#define DoesSaveUnders(s)	((s)->save_unders)
#define DoesBackingStore(s)	((s)->backing_store)
#define EventMaskOfScreen(s)	((s)->root_input_mask)

/*
 * Extensions need a way to hang private data on some structures.
 */
typedef struct _XExtData {
	int number;		/* number returned by XRegisterExtension */
	struct _XExtData *next;	/* next item on list of data for structure */
	int (*free_private)(	/* called to free private storage */
#if NeedFunctionPrototypes
	struct _XExtData *extension
#endif
	);
	XPointer private_data;	/* data private to this extension. */
} XExtData;

/*
 * This file contains structures used by the extension mechanism.
 */
typedef struct {		/* public to extension, cannot be changed */
	int extension;		/* extension number */
	int major_opcode;	/* major op-code assigned by server */
	int first_event;	/* first event number for the extension */
	int first_error;	/* first error number for the extension */
} XExtCodes;

/*
 * Data structure for retrieving info about pixmap formats.
 */

typedef struct {
    int depth;
    int bits_per_pixel;
    int scanline_pad;
} XPixmapFormatValues;


/*
 * Data structure for setting graphics context.
 */
typedef struct {
	int function;		/* logical operation */
	unsigned long plane_mask;/* plane mask */
	unsigned long foreground;/* foreground pixel */
	unsigned long background;/* background pixel */
	int line_width;		/* line width */
	int line_style;	 	/* LineSolid, LineOnOffDash, LineDoubleDash */
	int cap_style;	  	/* CapNotLast, CapButt, 
				   CapRound, CapProjecting */
	int join_style;	 	/* JoinMiter, JoinRound, JoinBevel */
	int fill_style;	 	/* FillSolid, FillTiled, 
				   FillStippled, FillOpaeueStippled */
	int fill_rule;	  	/* EvenOddRule, WindingRule */
	int arc_mode;		/* ArcChord, ArcPieSlice */
	Pixmap tile;		/* tile pixmap for tiling operations */
	Pixmap stipple;		/* stipple 1 plane pixmap for stipping */
	int ts_x_origin;	/* offset for tile or stipple operations */
	int ts_y_origin;
        Font font;	        /* default text font for text operations */
	int subwindow_mode;     /* ClipByChildren, IncludeInferiors */
	Bool graphics_exposures;/* boolean, should exposures be generated */
	int clip_x_origin;	/* origin for clipping */
	int clip_y_origin;
	Pixmap clip_mask;	/* bitmap clipping; other calls for rects */
	int dash_offset;	/* patterned/dashed line information */
	char dashes;
} XGCValues;

/*
 * Graphics context.  The contents of this structure are implementation
 * dependent.  A GC should be treated as opaque by application code.
 */

typedef struct _XGC
#ifdef XLIB_ILLEGAL_ACCESS
{
    XExtData *ext_data;	/* hook for extension to hang data */
    GContext gid;	/* protocol ID for graphics context */
    /* there is more to this structure, but it is private to Xlib */
}
#endif
*GC;

/*
 * Visual structure; contains information about colormapping possible.
 */
typedef struct {
	XExtData *ext_data;	/* hook for extension to hang data */
	VisualID visualid;	/* visual id of this visual */
#if defined(__cplusplus) || defined(c_plusplus)
	int c_class;		/* C++ class of screen (monochrome, etc.) */
#else
	int class;		/* class of screen (monochrome, etc.) */
#endif
	unsigned long red_mask, green_mask, blue_mask;	/* mask values */
	int bits_per_rgb;	/* log base 2 of distinct color values */
	int map_entries;	/* color map entries */
} Visual;

/*
 * Depth structure; contains information for each possible depth.
 */	
typedef struct {
	int depth;		/* this depth (Z) of the depth */
	int nvisuals;		/* number of Visual types at this depth */
	Visual *visuals;	/* list of visuals possible at this depth */
} Depth;

/*
 * Information about the screen.  The contents of this structure are
 * implementation dependent.  A Screen should be treated as opaque
 * by application code.
 */

struct _XDisplay;		/* Forward declare before use for C++ */

typedef struct {
	XExtData *ext_data;	/* hook for extension to hang data */
	struct _XDisplay *display;/* back pointer to display structure */
	Window root;		/* Root window id. */
	int width, height;	/* width and height of screen */
	int mwidth, mheight;	/* width and height of  in millimeters */
	int ndepths;		/* number of depths possible */
	Depth *depths;		/* list of allowable depths on the screen */
	int root_depth;		/* bits per pixel */
	Visual *root_visual;	/* root visual */
	GC default_gc;		/* GC for the root root visual */
	Colormap cmap;		/* default color map */
	unsigned long white_pixel;
	unsigned long black_pixel;	/* White and Black pixel values */
	int max_maps, min_maps;	/* max and min color maps */
	int backing_store;	/* Never, WhenMapped, Always */
	Bool save_unders;	
	long root_input_mask;	/* initial root input mask */
} Screen;

/*
 * Format structure; describes ZFormat data the screen will understand.
 */
typedef struct {
	XExtData *ext_data;	/* hook for extension to hang data */
	int depth;		/* depth of this image format */
	int bits_per_pixel;	/* bits/pixel at this depth */
	int scanline_pad;	/* scanline must padded to this multiple */
} ScreenFormat;

/*
 * Data structure for setting window attributes.
 */
typedef struct {
    Pixmap background_pixmap;	/* background or None or ParentRelative */
    unsigned long background_pixel;	/* background pixel */
    Pixmap border_pixmap;	/* border of the window */
    unsigned long border_pixel;	/* border pixel value */
    int bit_gravity;		/* one of bit gravity values */
    int win_gravity;		/* one of the window gravity values */
    int backing_store;		/* NotUseful, WhenMapped, Always */
    unsigned long backing_planes;/* planes to be preseved if possible */
    unsigned long backing_pixel;/* value to use in restoring planes */
    Bool save_under;		/* should bits under be saved? (popups) */
    long event_mask;		/* set of events that should be saved */
    long do_not_propagate_mask;	/* set of events that should not propagate */
    Bool override_redirect;	/* boolean value for override-redirect */
    Colormap colormap;		/* color map to be associated with window */
    Cursor cursor;		/* cursor to be displayed (or None) */
} XSetWindowAttributes;

typedef struct {
    int x, y;			/* location of window */
    int width, height;		/* width and height of window */
    int border_width;		/* border width of window */
    int depth;          	/* depth of window */
    Visual *visual;		/* the associated visual structure */
    Window root;        	/* root of screen containing window */
#if defined(__cplusplus) || defined(c_plusplus)
    int c_class;		/* C++ InputOutput, InputOnly*/
#else
    int class;			/* InputOutput, InputOnly*/
#endif
    int bit_gravity;		/* one of bit gravity values */
    int win_gravity;		/* one of the window gravity values */
    int backing_store;		/* NotUseful, WhenMapped, Always */
    unsigned long backing_planes;/* planes to be preserved if possible */
    unsigned long backing_pixel;/* value to be used when restoring planes */
    Bool save_under;		/* boolean, should bits under be saved? */
    Colormap colormap;		/* color map to be associated with window */
    Bool map_installed;		/* boolean, is color map currently installed*/
    int map_state;		/* IsUnmapped, IsUnviewable, IsViewable */
    long all_event_masks;	/* set of events all people have interest in*/
    long your_event_mask;	/* my event mask */
    long do_not_propagate_mask; /* set of events that should not propagate */
    Bool override_redirect;	/* boolean value for override-redirect */
    Screen *screen;		/* back pointer to correct screen */
} XWindowAttributes;

/*
 * Data structure for host setting; getting routines.
 *
 */

typedef struct {
	int family;		/* for example FamilyInternet */
	int length;		/* length of address, in bytes */
	char *address;		/* pointer to where to find the bytes */
} XHostAddress;

/*
 * Data structure for "image" data, used by image manipulation routines.
 */
typedef struct _XImage {
    int width, height;		/* size of image */
    int xoffset;		/* number of pixels offset in X direction */
    int format;			/* XYBitmap, XYPixmap, ZPixmap */
    char *data;			/* pointer to image data */
    int byte_order;		/* data byte order, LSBFirst, MSBFirst */
    int bitmap_unit;		/* quant. of scanline 8, 16, 32 */
    int bitmap_bit_order;	/* LSBFirst, MSBFirst */
    int bitmap_pad;		/* 8, 16, 32 either XY or ZPixmap */
    int depth;			/* depth of image */
    int bytes_per_line;		/* accelarator to next line */
    int bits_per_pixel;		/* bits per pixel (ZPixmap) */
    unsigned long red_mask;	/* bits in z arrangment */
    unsigned long green_mask;
    unsigned long blue_mask;
    XPointer obdata;		/* hook for the object routines to hang on */
    struct funcs {		/* image manipulation routines */
#if NeedFunctionPrototypes
	struct _XImage *(*create_image)(
		struct _XDisplay* /* display */,
		Visual*		/* visual */,
		unsigned int	/* depth */,
		int		/* format */,
		int		/* offset */,
		char*		/* data */,
		unsigned int	/* width */,
		unsigned int	/* height */,
		int		/* bitmap_pad */,
		int		/* bytes_per_line */);
	int (*destroy_image)        (struct _XImage *);
	unsigned long (*get_pixel)  (struct _XImage *, int, int);
	int (*put_pixel)            (struct _XImage *, int, int, unsigned long);
	struct _XImage *(*sub_image)(struct _XImage *, int, int, unsigned int, unsigned int);
	int (*add_pixel)            (struct _XImage *, long);
#else
	struct _XImage *(*create_image)();
	int (*destroy_image)();
	unsigned long (*get_pixel)();
	int (*put_pixel)();
	struct _XImage *(*sub_image)();
	int (*add_pixel)();
#endif
	} f;
} XImage;

/* 
 * Data structure for XReconfigureWindow
 */
typedef struct {
    int x, y;
    int width, height;
    int border_width;
    Window sibling;
    int stack_mode;
} XWindowChanges;

/*
 * Data structure used by color operations
 */
typedef struct {
	unsigned long pixel;
	unsigned short red, green, blue;
	char flags;  /* do_red, do_green, do_blue */
	char pad;
} XColor;

/* 
 * Data structures for graphics operations.  On most machines, these are
 * congruent with the wire protocol structures, so reformatting the data
 * can be avoided on these architectures.
 */
typedef struct {
    short x1, y1, x2, y2;
} XSegment;

typedef struct {
    short x, y;
} XPoint;
    
typedef struct {
    short x, y;
    unsigned short width, height;
} XRectangle;
    
typedef struct {
    short x, y;
    unsigned short width, height;
    short angle1, angle2;
} XArc;


/* Data structure for XChangeKeyboardControl */

typedef struct {
        int key_click_percent;
        int bell_percent;
        int bell_pitch;
        int bell_duration;
        int led;
        int led_mode;
        int key;
        int auto_repeat_mode;   /* On, Off, Default */
} XKeyboardControl;

/* Data structure for XGetKeyboardControl */

typedef struct {
        int key_click_percent;
	int bell_percent;
	unsigned int bell_pitch, bell_duration;
	unsigned long led_mask;
	int global_auto_repeat;
	char auto_repeats[32];
} XKeyboardState;

/* Data structure for XGetMotionEvents.  */

typedef struct {
        Time time;
	short x, y;
} XTimeCoord;

/* Data structure for X{Set,Get}ModifierMapping */

typedef struct {
 	int max_keypermod;	/* The server's max # of keys per modifier */
 	KeyCode *modifiermap;	/* An 8 by max_keypermod array of modifiers */
} XModifierKeymap;


/*
 * Display datatype maintaining display specific data.
 * The contents of this structure are implementation dependent.
 * A Display should be treated as opaque by application code.
 */
#ifndef XLIB_ILLEGAL_ACCESS
typedef struct _XDisplay Display;
#endif

struct _XPrivate;		/* Forward declare before use for C++ */
struct _XrmHashBucketRec;

typedef struct 
#ifdef XLIB_ILLEGAL_ACCESS
_XDisplay
#endif
{
	XExtData *ext_data;	/* hook for extension to hang data */
	struct _XPrivate *private1;
	int fd;			/* Network socket. */
	int private2;
	int proto_major_version;/* major version of server's X protocol */
	int proto_minor_version;/* minor version of servers X protocol */
	char *vendor;		/* vendor of the server hardware */
        XID private3;
	XID private4;
	XID private5;
	int private6;
	XID (*resource_alloc)(	/* allocator function */
#if NeedFunctionPrototypes
		struct _XDisplay*
#endif
	);
	int byte_order;		/* screen byte order, LSBFirst, MSBFirst */
	int bitmap_unit;	/* padding and data requirements */
	int bitmap_pad;		/* padding requirements on bitmaps */
	int bitmap_bit_order;	/* LeastSignificant or MostSignificant */
	int nformats;		/* number of pixmap formats in list */
	ScreenFormat *pixmap_format;	/* pixmap format list */
	int private8;
	int release;		/* release of the server */
	struct _XPrivate *private9, *private10;
	int qlen;		/* Length of input event queue */
	unsigned long last_request_read; /* seq number of last event read */
	unsigned long request;	/* sequence number of last request. */
	XPointer private11;
	XPointer private12;
	XPointer private13;
	XPointer private14;
	unsigned max_request_size; /* maximum number 32 bit words in request*/
	struct _XrmHashBucketRec *db;
	int (*private15)(
#if NeedFunctionPrototypes
		struct _XDisplay*
#endif
		);
	char *display_name;	/* "host:display" string used on this connect*/
	int default_screen;	/* default screen for operations */
	int nscreens;		/* number of screens on this server*/
	Screen *screens;	/* pointer to list of screens */
	unsigned long motion_buffer;	/* size of motion buffer */
	unsigned long private16;
	int min_keycode;	/* minimum defined keycode */
	int max_keycode;	/* maximum defined keycode */
	XPointer private17;
	XPointer private18;
	int private19;
	char *xdefaults;	/* contents of defaults from server */
	/* there is more to this structure, but it is private to Xlib */
}
#ifdef XLIB_ILLEGAL_ACCESS
Display, 
#endif
*_XPrivDisplay;

#if NeedFunctionPrototypes	/* prototypes require event type definitions */
#undef _XEVENT_
#endif
#ifndef _XEVENT_
/*
 * Definitions of specific events.
 */
typedef struct {
	int type;		/* of event */
	unsigned long serial;	/* # of last request processed by server */
	Bool send_event;	/* true if this came from a SendEvent request */
	Display *display;	/* Display the event was read from */
	Window window;	        /* "event" window it is reported relative to */
	Window root;	        /* root window that the event occurred on */
	Window subwindow;	/* child window */
	Time time;		/* milliseconds */
	int x, y;		/* pointer x, y coordinates in event window */
	int x_root, y_root;	/* coordinates relative to root */
	unsigned int state;	/* key or button mask */
	unsigned int keycode;	/* detail */
	Bool same_screen;	/* same screen flag */
} XKeyEvent;
typedef XKeyEvent XKeyPressedEvent;
typedef XKeyEvent XKeyReleasedEvent;

typedef struct {
	int type;		/* of event */
	unsigned long serial;	/* # of last request processed by server */
	Bool send_event;	/* true if this came from a SendEvent request */
	Display *display;	/* Display the event was read from */
	Window window;	        /* "event" window it is reported relative to */
	Window root;	        /* root window that the event occurred on */
	Window subwindow;	/* child window */
	Time time;		/* milliseconds */
	int x, y;		/* pointer x, y coordinates in event window */
	int x_root, y_root;	/* coordinates relative to root */
	unsigned int state;	/* key or button mask */
	unsigned int button;	/* detail */
	Bool same_screen;	/* same screen flag */
} XButtonEvent;
typedef XButtonEvent XButtonPressedEvent;
typedef XButtonEvent XButtonReleasedEvent;

typedef struct {
	int type;		/* of event */
	unsigned long serial;	/* # of last request processed by server */
	Bool send_event;	/* true if this came from a SendEvent request */
	Display *display;	/* Display the event was read from */
	Window window;	        /* "event" window reported relative to */
	Window root;	        /* root window that the event occurred on */
	Window subwindow;	/* child window */
	Time time;		/* milliseconds */
	int x, y;		/* pointer x, y coordinates in event window */
	int x_root, y_root;	/* coordinates relative to root */
	unsigned int state;	/* key or button mask */
	char is_hint;		/* detail */
	Bool same_screen;	/* same screen flag */
} XMotionEvent;
typedef XMotionEvent XPointerMovedEvent;

typedef struct {
	int type;		/* of event */
	unsigned long serial;	/* # of last request processed by server */
	Bool send_event;	/* true if this came from a SendEvent request */
	Display *display;	/* Display the event was read from */
	Window window;	        /* "event" window reported relative to */
	Window root;	        /* root window that the event occurred on */
	Window subwindow;	/* child window */
	Time time;		/* milliseconds */
	int x, y;		/* pointer x, y coordinates in event window */
	int x_root, y_root;	/* coordinates relative to root */
	int mode;		/* NotifyNormal, NotifyGrab, NotifyUngrab */
	int detail;
	/*
	 * NotifyAncestor, NotifyVirtual, NotifyInferior, 
	 * NotifyNonlinear,NotifyNonlinearVirtual
	 */
	Bool same_screen;	/* same screen flag */
	Bool focus;		/* boolean focus */
	unsigned int state;	/* key or button mask */
} XCrossingEvent;
typedef XCrossingEvent XEnterWindowEvent;
typedef XCrossingEvent XLeaveWindowEvent;

typedef struct {
	int type;		/* FocusIn or FocusOut */
	unsigned long serial;	/* # of last request processed by server */
	Bool send_event;	/* true if this came from a SendEvent request */
	Display *display;	/* Display the event was read from */
	Window window;		/* window of event */
	int mode;		/* NotifyNormal, NotifyGrab, NotifyUngrab */
	int detail;
	/*
	 * NotifyAncestor, NotifyVirtual, NotifyInferior, 
	 * NotifyNonlinear,NotifyNonlinearVirtual, NotifyPointer,
	 * NotifyPointerRoot, NotifyDetailNone 
	 */
} XFocusChangeEvent;
typedef XFocusChangeEvent XFocusInEvent;
typedef XFocusChangeEvent XFocusOutEvent;

/* generated on EnterWindow and FocusIn  when KeyMapState selected */
typedef struct {
	int type;
	unsigned long serial;	/* # of last request processed by server */
	Bool send_event;	/* true if this came from a SendEvent request */
	Display *display;	/* Display the event was read from */
	Window window;
	char key_vector[32];
} XKeymapEvent;	

typedef struct {
	int type;
	unsigned long serial;	/* # of last request processed by server */
	Bool send_event;	/* true if this came from a SendEvent request */
	Display *display;	/* Display the event was read from */
	Window window;
	int x, y;
	int width, height;
	int count;		/* if non-zero, at least this many more */
} XExposeEvent;

typedef struct {
	int type;
	unsigned long serial;	/* # of last request processed by server */
	Bool send_event;	/* true if this came from a SendEvent request */
	Display *display;	/* Display the event was read from */
	Drawable drawable;
	int x, y;
	int width, height;
	int count;		/* if non-zero, at least this many more */
	int major_code;		/* core is CopyArea or CopyPlane */
	int minor_code;		/* not defined in the core */
} XGraphicsExposeEvent;

typedef struct {
	int type;
	unsigned long serial;	/* # of last request processed by server */
	Bool send_event;	/* true if this came from a SendEvent request */
	Display *display;	/* Display the event was read from */
	Drawable drawable;
	int major_code;		/* core is CopyArea or CopyPlane */
	int minor_code;		/* not defined in the core */
} XNoExposeEvent;

typedef struct {
	int type;
	unsigned long serial;	/* # of last request processed by server */
	Bool send_event;	/* true if this came from a SendEvent request */
	Display *display;	/* Display the event was read from */
	Window window;
	int state;		/* Visibility state */
} XVisibilityEvent;

typedef struct {
	int type;
	unsigned long serial;	/* # of last request processed by server */
	Bool send_event;	/* true if this came from a SendEvent request */
	Display *display;	/* Display the event was read from */
	Window parent;		/* parent of the window */
	Window window;		/* window id of window created */
	int x, y;		/* window location */
	int width, height;	/* size of window */
	int border_width;	/* border width */
	Bool override_redirect;	/* creation should be overridden */
} XCreateWindowEvent;

typedef struct {
	int type;
	unsigned long serial;	/* # of last request processed by server */
	Bool send_event;	/* true if this came from a SendEvent request */
	Display *display;	/* Display the event was read from */
	Window event;
	Window window;
} XDestroyWindowEvent;

typedef struct {
	int type;
	unsigned long serial;	/* # of last request processed by server */
	Bool send_event;	/* true if this came from a SendEvent request */
	Display *display;	/* Display the event was read from */
	Window event;
	Window window;
	Bool from_configure;
} XUnmapEvent;

typedef struct {
	int type;
	unsigned long serial;	/* # of last request processed by server */
	Bool send_event;	/* true if this came from a SendEvent request */
	Display *display;	/* Display the event was read from */
	Window event;
	Window window;
	Bool override_redirect;	/* boolean, is override set... */
} XMapEvent;

typedef struct {
	int type;
	unsigned long serial;	/* # of last request processed by server */
	Bool send_event;	/* true if this came from a SendEvent request */
	Display *display;	/* Display the event was read from */
	Window parent;
	Window window;
} XMapRequestEvent;

typedef struct {
	int type;
	unsigned long serial;	/* # of last request processed by server */
	Bool send_event;	/* true if this came from a SendEvent request */
	Display *display;	/* Display the event was read from */
	Window event;
	Window window;
	Window parent;
	int x, y;
	Bool override_redirect;
} XReparentEvent;

typedef struct {
	int type;
	unsigned long serial;	/* # of last request processed by server */
	Bool send_event;	/* true if this came from a SendEvent request */
	Display *display;	/* Display the event was read from */
	Window event;
	Window window;
	int x, y;
	int width, height;
	int border_width;
	Window above;
	Bool override_redirect;
} XConfigureEvent;

typedef struct {
	int type;
	unsigned long serial;	/* # of last request processed by server */
	Bool send_event;	/* true if this came from a SendEvent request */
	Display *display;	/* Display the event was read from */
	Window event;
	Window window;
	int x, y;
} XGravityEvent;

typedef struct {
	int type;
	unsigned long serial;	/* # of last request processed by server */
	Bool send_event;	/* true if this came from a SendEvent request */
	Display *display;	/* Display the event was read from */
	Window window;
	int width, height;
} XResizeRequestEvent;

typedef struct {
	int type;
	unsigned long serial;	/* # of last request processed by server */
	Bool send_event;	/* true if this came from a SendEvent request */
	Display *display;	/* Display the event was read from */
	Window parent;
	Window window;
	int x, y;
	int width, height;
	int border_width;
	Window above;
	int detail;		/* Above, Below, TopIf, BottomIf, Opposite */
	unsigned long value_mask;
} XConfigureRequestEvent;

typedef struct {
	int type;
	unsigned long serial;	/* # of last request processed by server */
	Bool send_event;	/* true if this came from a SendEvent request */
	Display *display;	/* Display the event was read from */
	Window event;
	Window window;
	int place;		/* PlaceOnTop, PlaceOnBottom */
} XCirculateEvent;

typedef struct {
	int type;
	unsigned long serial;	/* # of last request processed by server */
	Bool send_event;	/* true if this came from a SendEvent request */
	Display *display;	/* Display the event was read from */
	Window parent;
	Window window;
	int place;		/* PlaceOnTop, PlaceOnBottom */
} XCirculateRequestEvent;

typedef struct {
	int type;
	unsigned long serial;	/* # of last request processed by server */
	Bool send_event;	/* true if this came from a SendEvent request */
	Display *display;	/* Display the event was read from */
	Window window;
	Atom atom;
	Time time;
	int state;		/* NewValue, Deleted */
} XPropertyEvent;

typedef struct {
	int type;
	unsigned long serial;	/* # of last request processed by server */
	Bool send_event;	/* true if this came from a SendEvent request */
	Display *display;	/* Display the event was read from */
	Window window;
	Atom selection;
	Time time;
} XSelectionClearEvent;

typedef struct {
	int type;
	unsigned long serial;	/* # of last request processed by server */
	Bool send_event;	/* true if this came from a SendEvent request */
	Display *display;	/* Display the event was read from */
	Window owner;
	Window requestor;
	Atom selection;
	Atom target;
	Atom property;
	Time time;
} XSelectionRequestEvent;

typedef struct {
	int type;
	unsigned long serial;	/* # of last request processed by server */
	Bool send_event;	/* true if this came from a SendEvent request */
	Display *display;	/* Display the event was read from */
	Window requestor;
	Atom selection;
	Atom target;
	Atom property;		/* ATOM or None */
	Time time;
} XSelectionEvent;

typedef struct {
	int type;
	unsigned long serial;	/* # of last request processed by server */
	Bool send_event;	/* true if this came from a SendEvent request */
	Display *display;	/* Display the event was read from */
	Window window;
	Colormap colormap;	/* COLORMAP or None */
#if defined(__cplusplus) || defined(c_plusplus)
	Bool c_new;		/* C++ */
#else
	Bool new;
#endif
	int state;		/* ColormapInstalled, ColormapUninstalled */
} XColormapEvent;

typedef struct {
	int type;
	unsigned long serial;	/* # of last request processed by server */
	Bool send_event;	/* true if this came from a SendEvent request */
	Display *display;	/* Display the event was read from */
	Window window;
	Atom message_type;
	int format;
	union {
		char b[20];
		short s[10];
		long l[5];
		} data;
} XClientMessageEvent;

typedef struct {
	int type;
	unsigned long serial;	/* # of last request processed by server */
	Bool send_event;	/* true if this came from a SendEvent request */
	Display *display;	/* Display the event was read from */
	Window window;		/* unused */
	int request;		/* one of MappingModifier, MappingKeyboard,
				   MappingPointer */
	int first_keycode;	/* first keycode */
	int count;		/* defines range of change w. first_keycode*/
} XMappingEvent;

typedef struct {
	int type;
	Display *display;	/* Display the event was read from */
	XID resourceid;		/* resource id */
	unsigned long serial;	/* serial number of failed request */
	unsigned char error_code;	/* error code of failed request */
	unsigned char request_code;	/* Major op-code of failed request */
	unsigned char minor_code;	/* Minor op-code of failed request */
} XErrorEvent;

typedef struct {
	int type;
	unsigned long serial;	/* # of last request processed by server */
	Bool send_event;	/* true if this came from a SendEvent request */
	Display *display;/* Display the event was read from */
	Window window;	/* window on which event was requested in event mask */
} XAnyEvent;

/*
 * this union is defined so Xlib can always use the same sized
 * event structure internally, to avoid memory fragmentation.
 */
typedef union _XEvent {
        int type;		/* must not be changed; first element */
	XAnyEvent xany;
	XKeyEvent xkey;
	XButtonEvent xbutton;
	XMotionEvent xmotion;
	XCrossingEvent xcrossing;
	XFocusChangeEvent xfocus;
	XExposeEvent xexpose;
	XGraphicsExposeEvent xgraphicsexpose;
	XNoExposeEvent xnoexpose;
	XVisibilityEvent xvisibility;
	XCreateWindowEvent xcreatewindow;
	XDestroyWindowEvent xdestroywindow;
	XUnmapEvent xunmap;
	XMapEvent xmap;
	XMapRequestEvent xmaprequest;
	XReparentEvent xreparent;
	XConfigureEvent xconfigure;
	XGravityEvent xgravity;
	XResizeRequestEvent xresizerequest;
	XConfigureRequestEvent xconfigurerequest;
	XCirculateEvent xcirculate;
	XCirculateRequestEvent xcirculaterequest;
	XPropertyEvent xproperty;
	XSelectionClearEvent xselectionclear;
	XSelectionRequestEvent xselectionrequest;
	XSelectionEvent xselection;
	XColormapEvent xcolormap;
	XClientMessageEvent xclient;
	XMappingEvent xmapping;
	XErrorEvent xerror;
	XKeymapEvent xkeymap;
	long pad[24];
} XEvent;
#endif

#define XAllocID(dpy) ((*((_XPrivDisplay)dpy)->resource_alloc)((dpy)))

/*
 * per character font metric information.
 */
typedef struct {
    short	lbearing;	/* origin to left edge of raster */
    short	rbearing;	/* origin to right edge of raster */
    short	width;		/* advance to next char's origin */
    short	ascent;		/* baseline to top edge of raster */
    short	descent;	/* baseline to bottom edge of raster */
    unsigned short attributes;	/* per char flags (not predefined) */
} XCharStruct;

/*
 * To allow arbitrary information with fonts, there are additional properties
 * returned.
 */
typedef struct {
    Atom name;
    unsigned long card32;
} XFontProp;

typedef struct {
    XExtData	*ext_data;	/* hook for extension to hang data */
    Font        fid;            /* Font id for this font */
    unsigned	direction;	/* hint about direction the font is painted */
    unsigned	min_char_or_byte2;/* first character */
    unsigned	max_char_or_byte2;/* last character */
    unsigned	min_byte1;	/* first row that exists */
    unsigned	max_byte1;	/* last row that exists */
    Bool	all_chars_exist;/* flag if all characters have non-zero size*/
    unsigned	default_char;	/* char to print for undefined character */
    int         n_properties;   /* how many properties there are */
    XFontProp	*properties;	/* pointer to array of additional properties*/
    XCharStruct	min_bounds;	/* minimum bounds over all existing char*/
    XCharStruct	max_bounds;	/* maximum bounds over all existing char*/
    XCharStruct	*per_char;	/* first_char to last_char information */
    int		ascent;		/* log. extent above baseline for spacing */
    int		descent;	/* log. descent below baseline for spacing */
} XFontStruct;

/*
 * PolyText routines take these as arguments.
 */
typedef struct {
    char *chars;		/* pointer to string */
    int nchars;			/* number of characters */
    int delta;			/* delta between strings */
    Font font;			/* font to print it in, None don't change */
} XTextItem;

typedef struct {		/* normal 16 bit characters are two bytes */
    unsigned char byte1;
    unsigned char byte2;
} XChar2b;

typedef struct {
    XChar2b *chars;		/* two byte characters */
    int nchars;			/* number of characters */
    int delta;			/* delta between strings */
    Font font;			/* font to print it in, None don't change */
} XTextItem16;


typedef union { Display *display;
		GC gc;
		Visual *visual;
		Screen *screen;
		ScreenFormat *pixmap_format;
		XFontStruct *font; } XEDataObject;

typedef struct {
    XRectangle      max_ink_extent;
    XRectangle      max_logical_extent;
} XFontSetExtents;

/* unused:
typedef void (*XOMProc)();
 */

typedef struct _XOM *XOM;
typedef struct _XOC *XOC, *XFontSet;

typedef struct {
    char           *chars;
    int             nchars;
    int             delta;
    XFontSet        font_set;
} XmbTextItem;

typedef struct {
    wchar_t        *chars;
    int             nchars;
    int             delta;
    XFontSet        font_set;
} XwcTextItem;

#define XNRequiredCharSet "requiredCharSet"
#define XNQueryOrientation "queryOrientation"
#define XNBaseFontName "baseFontName"
#define XNOMAutomatic "omAutomatic"
#define XNMissingCharSet "missingCharSet"
#define XNDefaultString "defaultString"
#define XNOrientation "orientation"
#define XNDirectionalDependentDrawing "directionalDependentDrawing"
#define XNContextualDrawing "contextualDrawing"
#define XNFontInfo "fontInfo"

typedef struct {
    int charset_count;
    char **charset_list;
} XOMCharSetList;

typedef enum {
    XOMOrientation_LTR_TTB,
    XOMOrientation_RTL_TTB,
    XOMOrientation_TTB_LTR,
    XOMOrientation_TTB_RTL,
    XOMOrientation_Context
} XOrientation;

typedef struct {
    int num_orientation;
    XOrientation *orientation;	/* Input Text description */
} XOMOrientation;

typedef struct {
    int num_font;
    XFontStruct **font_struct_list;
    char **font_name_list;
} XOMFontInfo;

typedef struct _XIM *XIM;
typedef struct _XIC *XIC;

typedef void (*XIMProc)(
#if NeedFunctionPrototypes
    XIM,
    XPointer,
    XPointer
#endif
);

typedef Bool (*XICProc)(
#if NeedFunctionPrototypes
    XIC,
    XPointer,
    XPointer
#endif
);

typedef void (*XIDProc)(
#if NeedFunctionPrototypes
    Display*,
    XPointer,
    XPointer
#endif
);

typedef unsigned long XIMStyle;

typedef struct {
    unsigned short count_styles;
    XIMStyle *supported_styles;
} XIMStyles;

#define XIMPreeditArea		0x0001L
#define XIMPreeditCallbacks	0x0002L
#define XIMPreeditPosition	0x0004L
#define XIMPreeditNothing	0x0008L
#define XIMPreeditNone		0x0010L
#define XIMStatusArea		0x0100L
#define XIMStatusCallbacks	0x0200L
#define XIMStatusNothing	0x0400L
#define XIMStatusNone		0x0800L

#define XNVaNestedList "XNVaNestedList"
#define XNQueryInputStyle "queryInputStyle"
#define XNClientWindow "clientWindow"
#define XNInputStyle "inputStyle"
#define XNFocusWindow "focusWindow"
#define XNResourceName "resourceName"
#define XNResourceClass "resourceClass"
#define XNGeometryCallback "geometryCallback"
#define XNDestroyCallback "destroyCallback"
#define XNFilterEvents "filterEvents"
#define XNPreeditStartCallback "preeditStartCallback"
#define XNPreeditDoneCallback "preeditDoneCallback"
#define XNPreeditDrawCallback "preeditDrawCallback"
#define XNPreeditCaretCallback "preeditCaretCallback"
#define XNPreeditStateNotifyCallback "preeditStateNotifyCallback"
#define XNPreeditAttributes "preeditAttributes"
#define XNStatusStartCallback "statusStartCallback"
#define XNStatusDoneCallback "statusDoneCallback"
#define XNStatusDrawCallback "statusDrawCallback"
#define XNStatusAttributes "statusAttributes"
#define XNArea "area"
#define XNAreaNeeded "areaNeeded"
#define XNSpotLocation "spotLocation"
#define XNColormap "colorMap"
#define XNStdColormap "stdColorMap"
#define XNForeground "foreground"
#define XNBackground "background"
#define XNBackgroundPixmap "backgroundPixmap"
#define XNFontSet "fontSet"
#define XNLineSpace "lineSpace"
#define XNCursor "cursor"

#define XNQueryIMValuesList "queryIMValuesList"
#define XNQueryICValuesList "queryICValuesList"
#define XNVisiblePosition "visiblePosition"
#define XNR6PreeditCallback "r6PreeditCallback"
#define XNStringConversionCallback "stringConversionCallback"
#define XNStringConversion "stringConversion"
#define XNResetState "resetState"
#define XNHotKey "hotKey"
#define XNHotKeyState "hotKeyState"
#define XNPreeditState "preeditState"
#define XNSeparatorofNestedList "separatorofNestedList"

#define XBufferOverflow		-1
#define XLookupNone		1
#define XLookupChars		2
#define XLookupKeySym		3
#define XLookupBoth		4

#if NeedFunctionPrototypes
typedef void *XVaNestedList;
#else
typedef XPointer XVaNestedList;
#endif

typedef struct {
    XPointer client_data;
    XIMProc callback;
} XIMCallback;

typedef struct {
    XPointer client_data;
    XICProc callback;
} XICCallback;

typedef unsigned long XIMFeedback;

#define XIMReverse		1L
#define XIMUnderline		(1L<<1) 
#define XIMHighlight		(1L<<2)
#define XIMPrimary	 	(1L<<5)
#define XIMSecondary		(1L<<6)
#define XIMTertiary	 	(1L<<7)
#define XIMVisibleToForward 	(1L<<8)
#define XIMVisibleToBackword 	(1L<<9)
#define XIMVisibleToCenter 	(1L<<10)

typedef struct _XIMText {
    unsigned short length;
    XIMFeedback *feedback;
    Bool encoding_is_wchar; 
    union {
	char *multi_byte;
	wchar_t *wide_char;
    } string; 
} XIMText;

typedef	unsigned long	 XIMPreeditState;

#define	XIMPreeditUnKnown	0L
#define	XIMPreeditEnable	1L
#define	XIMPreeditDisable	(1L<<1)

typedef	struct	_XIMPreeditStateNotifyCallbackStruct {
    XIMPreeditState state;
} XIMPreeditStateNotifyCallbackStruct;

typedef	unsigned long	 XIMResetState;

#define	XIMInitialState		1L
#define	XIMPreserveState	(1L<<1)

typedef unsigned long XIMStringConversionFeedback;

#define	XIMStringConversionLeftEdge	(0x00000001)
#define	XIMStringConversionRightEdge	(0x00000002)
#define	XIMStringConversionTopEdge	(0x00000004)
#define	XIMStringConversionBottomEdge	(0x00000008)
#define	XIMStringConversionConcealed	(0x00000010)
#define	XIMStringConversionWrapped	(0x00000020)

typedef struct _XIMStringConversionText {
    unsigned short length;
    XIMStringConversionFeedback *feedback;
    Bool encoding_is_wchar; 
    union {
	char *mbs;
	wchar_t *wcs;
    } string; 
} XIMStringConversionText;

typedef	unsigned short	XIMStringConversionPosition;

typedef	unsigned short	XIMStringConversionType;

#define	XIMStringConversionBuffer	(0x0001)
#define	XIMStringConversionLine		(0x0002)
#define	XIMStringConversionWord		(0x0003)
#define	XIMStringConversionChar		(0x0004)

typedef	unsigned short	XIMStringConversionOperation;

#define	XIMStringConversionSubstitution	(0x0001)
#define	XIMStringConversionRetrieval	(0x0002)

typedef enum {
    XIMForwardChar, XIMBackwardChar,
    XIMForwardWord, XIMBackwardWord,
    XIMCaretUp, XIMCaretDown,
    XIMNextLine, XIMPreviousLine,
    XIMLineStart, XIMLineEnd, 
    XIMAbsolutePosition,
    XIMDontChange
} XIMCaretDirection;

typedef struct _XIMStringConversionCallbackStruct {
    XIMStringConversionPosition position;
    XIMCaretDirection direction;
    XIMStringConversionOperation operation;
    unsigned short factor;
    XIMStringConversionText *text;
} XIMStringConversionCallbackStruct;

typedef struct _XIMPreeditDrawCallbackStruct {
    int caret;		/* Cursor offset within pre-edit string */
    int chg_first;	/* Starting change position */
    int chg_length;	/* Length of the change in character count */
    XIMText *text;
} XIMPreeditDrawCallbackStruct;

typedef enum {
    XIMIsInvisible,	/* Disable caret feedback */ 
    XIMIsPrimary,	/* UI defined caret feedback */
    XIMIsSecondary	/* UI defined caret feedback */
} XIMCaretStyle;

typedef struct _XIMPreeditCaretCallbackStruct {
    int position;		 /* Caret offset within pre-edit string */
    XIMCaretDirection direction; /* Caret moves direction */
    XIMCaretStyle style;	 /* Feedback of the caret */
} XIMPreeditCaretCallbackStruct;

typedef enum {
    XIMTextType,
    XIMBitmapType
} XIMStatusDataType;
	
typedef struct _XIMStatusDrawCallbackStruct {
    XIMStatusDataType type;
    union {
	XIMText *text;
	Pixmap  bitmap;
    } data;
} XIMStatusDrawCallbackStruct;

typedef struct _XIMHotKeyTrigger {
    KeySym	 keysym;
    int		 modifier;
    int		 modifier_mask;
} XIMHotKeyTrigger;

typedef struct _XIMHotKeyTriggers {
    int			 num_hot_key;
    XIMHotKeyTrigger	*key;
} XIMHotKeyTriggers;

typedef	unsigned long	 XIMHotKeyState;

#define	XIMHotKeyStateON	(0x0001L)
#define	XIMHotKeyStateOFF	(0x0002L)

typedef struct {
    unsigned short count_values;
    char **supported_values;
} XIMValuesList;

_XFUNCPROTOBEGIN

#if defined(WIN32) && !defined(_XLIBINT_)
#define _Xdebug (*_Xdebug_p)
#endif

extern int _Xdebug;

extern XFontStruct *XLoadQueryFont(
#if NeedFunctionPrototypes
    Display*		/* display */,
    _Xconst char*	/* name */
#endif
);

extern XFontStruct *XQueryFont(
#if NeedFunctionPrototypes
    Display*		/* display */,
    XID			/* font_ID */
#endif
);


extern XTimeCoord *XGetMotionEvents(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    Time		/* start */,
    Time		/* stop */,
    int*		/* nevents_return */
#endif
);

extern XModifierKeymap *XDeleteModifiermapEntry(
#if NeedFunctionPrototypes
    XModifierKeymap*	/* modmap */,
#if NeedWidePrototypes
    unsigned int	/* keycode_entry */,
#else
    KeyCode		/* keycode_entry */,
#endif
    int			/* modifier */
#endif
);

extern XModifierKeymap	*XGetModifierMapping(
#if NeedFunctionPrototypes
    Display*		/* display */
#endif
);

extern XModifierKeymap	*XInsertModifiermapEntry(
#if NeedFunctionPrototypes
    XModifierKeymap*	/* modmap */,
#if NeedWidePrototypes
    unsigned int	/* keycode_entry */,
#else
    KeyCode		/* keycode_entry */,
#endif
    int			/* modifier */    
#endif
);

extern XModifierKeymap *XNewModifiermap(
#if NeedFunctionPrototypes
    int			/* max_keys_per_mod */
#endif
);

extern XImage *XCreateImage(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Visual*		/* visual */,
    unsigned int	/* depth */,
    int			/* format */,
    int			/* offset */,
    char*		/* data */,
    unsigned int	/* width */,
    unsigned int	/* height */,
    int			/* bitmap_pad */,
    int			/* bytes_per_line */
#endif
);
extern Status XInitImage(
#if NeedFunctionPrototypes
    XImage*		/* image */
#endif
);
extern XImage *XGetImage(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* d */,
    int			/* x */,
    int			/* y */,
    unsigned int	/* width */,
    unsigned int	/* height */,
    unsigned long	/* plane_mask */,
    int			/* format */
#endif
);
extern XImage *XGetSubImage(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* d */,
    int			/* x */,
    int			/* y */,
    unsigned int	/* width */,
    unsigned int	/* height */,
    unsigned long	/* plane_mask */,
    int			/* format */,
    XImage*		/* dest_image */,
    int			/* dest_x */,
    int			/* dest_y */
#endif
);

/* 
 * X function declarations.
 */
extern Display *XOpenDisplay(
#if NeedFunctionPrototypes
    _Xconst char*	/* display_name */
#endif
);

extern void XrmInitialize(
#if NeedFunctionPrototypes
    void
#endif
);

extern char *XFetchBytes(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int*		/* nbytes_return */
#endif
);
extern char *XFetchBuffer(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int*		/* nbytes_return */,
    int			/* buffer */
#endif
);
extern char *XGetAtomName(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Atom		/* atom */
#endif
);
extern Status XGetAtomNames(
#if NeedFunctionPrototypes
    Display*		/* dpy */,
    Atom*		/* atoms */,
    int			/* count */,
    char**		/* names_return */
#endif
);
extern char *XGetDefault(
#if NeedFunctionPrototypes
    Display*		/* display */,
    _Xconst char*	/* program */,
    _Xconst char*	/* option */		  
#endif
);
extern char *XDisplayName(
#if NeedFunctionPrototypes
    _Xconst char*	/* string */
#endif
);
extern char *XKeysymToString(
#if NeedFunctionPrototypes
    KeySym		/* keysym */
#endif
);

extern int (*XSynchronize(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Bool		/* onoff */
#endif
))(
#if NeedNestedPrototypes
    Display*		/* display */
#endif
);
extern int (*XSetAfterFunction(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int (*) (
#if NeedNestedPrototypes
	     Display*	/* display */
#endif
            )		/* procedure */
#endif
))(
#if NeedNestedPrototypes
    Display*		/* display */
#endif
);
extern Atom XInternAtom(
#if NeedFunctionPrototypes
    Display*		/* display */,
    _Xconst char*	/* atom_name */,
    Bool		/* only_if_exists */		 
#endif
);
extern Status XInternAtoms(
#if NeedFunctionPrototypes
    Display*		/* dpy */,
    char**		/* names */,
    int			/* count */,
    Bool		/* onlyIfExists */,
    Atom*		/* atoms_return */
#endif
);
extern Colormap XCopyColormapAndFree(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Colormap		/* colormap */
#endif
);
extern Colormap XCreateColormap(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    Visual*		/* visual */,
    int			/* alloc */			 
#endif
);
extern Cursor XCreatePixmapCursor(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Pixmap		/* source */,
    Pixmap		/* mask */,
    XColor*		/* foreground_color */,
    XColor*		/* background_color */,
    unsigned int	/* x */,
    unsigned int	/* y */			   
#endif
);
extern Cursor XCreateGlyphCursor(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Font		/* source_font */,
    Font		/* mask_font */,
    unsigned int	/* source_char */,
    unsigned int	/* mask_char */,
    XColor _Xconst *	/* foreground_color */,
    XColor _Xconst *	/* background_color */
#endif
);
extern Cursor XCreateFontCursor(
#if NeedFunctionPrototypes
    Display*		/* display */,
    unsigned int	/* shape */
#endif
);
extern Font XLoadFont(
#if NeedFunctionPrototypes
    Display*		/* display */,
    _Xconst char*	/* name */
#endif
);
extern GC XCreateGC(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* d */,
    unsigned long	/* valuemask */,
    XGCValues*		/* values */
#endif
);
extern GContext XGContextFromGC(
#if NeedFunctionPrototypes
    GC			/* gc */
#endif
);
extern void XFlushGC(
#if NeedFunctionPrototypes
    Display*		/* display */,
    GC			/* gc */
#endif
);
extern Pixmap XCreatePixmap(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* d */,
    unsigned int	/* width */,
    unsigned int	/* height */,
    unsigned int	/* depth */		        
#endif
);
extern Pixmap XCreateBitmapFromData(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* d */,
    _Xconst char*	/* data */,
    unsigned int	/* width */,
    unsigned int	/* height */
#endif
);
extern Pixmap XCreatePixmapFromBitmapData(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* d */,
    char*		/* data */,
    unsigned int	/* width */,
    unsigned int	/* height */,
    unsigned long	/* fg */,
    unsigned long	/* bg */,
    unsigned int	/* depth */
#endif
);
extern Window XCreateSimpleWindow(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* parent */,
    int			/* x */,
    int			/* y */,
    unsigned int	/* width */,
    unsigned int	/* height */,
    unsigned int	/* border_width */,
    unsigned long	/* border */,
    unsigned long	/* background */
#endif
);
extern Window XGetSelectionOwner(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Atom		/* selection */
#endif
);
extern Window XCreateWindow(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* parent */,
    int			/* x */,
    int			/* y */,
    unsigned int	/* width */,
    unsigned int	/* height */,
    unsigned int	/* border_width */,
    int			/* depth */,
    unsigned int	/* class */,
    Visual*		/* visual */,
    unsigned long	/* valuemask */,
    XSetWindowAttributes*	/* attributes */
#endif
); 
extern Colormap *XListInstalledColormaps(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    int*		/* num_return */
#endif
);
extern char **XListFonts(
#if NeedFunctionPrototypes
    Display*		/* display */,
    _Xconst char*	/* pattern */,
    int			/* maxnames */,
    int*		/* actual_count_return */
#endif
);
extern char **XListFontsWithInfo(
#if NeedFunctionPrototypes
    Display*		/* display */,
    _Xconst char*	/* pattern */,
    int			/* maxnames */,
    int*		/* count_return */,
    XFontStruct**	/* info_return */
#endif
);
extern char **XGetFontPath(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int*		/* npaths_return */
#endif
);
extern char **XListExtensions(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int*		/* nextensions_return */
#endif
);
extern Atom *XListProperties(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    int*		/* num_prop_return */
#endif
);
extern XHostAddress *XListHosts(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int*		/* nhosts_return */,
    Bool*		/* state_return */
#endif
);
extern KeySym XKeycodeToKeysym(
#if NeedFunctionPrototypes
    Display*		/* display */,
#if NeedWidePrototypes
    unsigned int	/* keycode */,
#else
    KeyCode		/* keycode */,
#endif
    int			/* index */
#endif
);
extern KeySym XLookupKeysym(
#if NeedFunctionPrototypes
    XKeyEvent*		/* key_event */,
    int			/* index */
#endif
);
extern KeySym *XGetKeyboardMapping(
#if NeedFunctionPrototypes
    Display*		/* display */,
#if NeedWidePrototypes
    unsigned int	/* first_keycode */,
#else
    KeyCode		/* first_keycode */,
#endif
    int			/* keycode_count */,
    int*		/* keysyms_per_keycode_return */
#endif
);
extern KeySym XStringToKeysym(
#if NeedFunctionPrototypes
    _Xconst char*	/* string */
#endif
);
extern long XMaxRequestSize(
#if NeedFunctionPrototypes
    Display*		/* display */
#endif
);
extern long XExtendedMaxRequestSize(
#if NeedFunctionPrototypes
    Display*		/* display */
#endif
);
extern char *XResourceManagerString(
#if NeedFunctionPrototypes
    Display*		/* display */
#endif
);
extern char *XScreenResourceString(
#if NeedFunctionPrototypes
	Screen*		/* screen */
#endif
);
extern unsigned long XDisplayMotionBufferSize(
#if NeedFunctionPrototypes
    Display*		/* display */
#endif
);
extern VisualID XVisualIDFromVisual(
#if NeedFunctionPrototypes
    Visual*		/* visual */
#endif
);

/* multithread routines */

extern Status XInitThreads(
#if NeedFunctionPrototypes
    void
#endif
);

extern void XLockDisplay(
#if NeedFunctionPrototypes
    Display*		/* display */
#endif
);

extern void XUnlockDisplay(
#if NeedFunctionPrototypes
    Display*		/* display */
#endif
);

/* routines for dealing with extensions */

extern XExtCodes *XInitExtension(
#if NeedFunctionPrototypes
    Display*		/* display */,
    _Xconst char*	/* name */
#endif
);

extern XExtCodes *XAddExtension(
#if NeedFunctionPrototypes
    Display*		/* display */
#endif
);
extern XExtData *XFindOnExtensionList(
#if NeedFunctionPrototypes
    XExtData**		/* structure */,
    int			/* number */
#endif
);
extern XExtData **XEHeadOfExtensionList(
#if NeedFunctionPrototypes
    XEDataObject	/* object */
#endif
);

/* these are routines for which there are also macros */
extern Window XRootWindow(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int			/* screen_number */
#endif
);
extern Window XDefaultRootWindow(
#if NeedFunctionPrototypes
    Display*		/* display */
#endif
);
extern Window XRootWindowOfScreen(
#if NeedFunctionPrototypes
    Screen*		/* screen */
#endif
);
extern Visual *XDefaultVisual(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int			/* screen_number */
#endif
);
extern Visual *XDefaultVisualOfScreen(
#if NeedFunctionPrototypes
    Screen*		/* screen */
#endif
);
extern GC XDefaultGC(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int			/* screen_number */
#endif
);
extern GC XDefaultGCOfScreen(
#if NeedFunctionPrototypes
    Screen*		/* screen */
#endif
);
extern unsigned long XBlackPixel(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int			/* screen_number */
#endif
);
extern unsigned long XWhitePixel(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int			/* screen_number */
#endif
);
extern unsigned long XAllPlanes(
#if NeedFunctionPrototypes
    void
#endif
);
extern unsigned long XBlackPixelOfScreen(
#if NeedFunctionPrototypes
    Screen*		/* screen */
#endif
);
extern unsigned long XWhitePixelOfScreen(
#if NeedFunctionPrototypes
    Screen*		/* screen */
#endif
);
extern unsigned long XNextRequest(
#if NeedFunctionPrototypes
    Display*		/* display */
#endif
);
extern unsigned long XLastKnownRequestProcessed(
#if NeedFunctionPrototypes
    Display*		/* display */
#endif
);
extern char *XServerVendor(
#if NeedFunctionPrototypes
    Display*		/* display */
#endif
);
extern char *XDisplayString(
#if NeedFunctionPrototypes
    Display*		/* display */
#endif
);
extern Colormap XDefaultColormap(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int			/* screen_number */
#endif
);
extern Colormap XDefaultColormapOfScreen(
#if NeedFunctionPrototypes
    Screen*		/* screen */
#endif
);
extern Display *XDisplayOfScreen(
#if NeedFunctionPrototypes
    Screen*		/* screen */
#endif
);
extern Screen *XScreenOfDisplay(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int			/* screen_number */
#endif
);
extern Screen *XDefaultScreenOfDisplay(
#if NeedFunctionPrototypes
    Display*		/* display */
#endif
);
extern long XEventMaskOfScreen(
#if NeedFunctionPrototypes
    Screen*		/* screen */
#endif
);

extern int XScreenNumberOfScreen(
#if NeedFunctionPrototypes
    Screen*		/* screen */
#endif
);

typedef int (*XErrorHandler) (	    /* WARNING, this type not in Xlib spec */
#if NeedFunctionPrototypes
    Display*		/* display */,
    XErrorEvent*	/* error_event */
#endif
);

extern XErrorHandler XSetErrorHandler (
#if NeedFunctionPrototypes
    XErrorHandler	/* handler */
#endif
);


typedef int (*XIOErrorHandler) (    /* WARNING, this type not in Xlib spec */
#if NeedFunctionPrototypes
    Display*		/* display */
#endif
);

extern XIOErrorHandler XSetIOErrorHandler (
#if NeedFunctionPrototypes
    XIOErrorHandler	/* handler */
#endif
);


extern XPixmapFormatValues *XListPixmapFormats(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int*		/* count_return */
#endif
);
extern int *XListDepths(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int			/* screen_number */,
    int*		/* count_return */
#endif
);

/* ICCCM routines for things that don't require special include files; */
/* other declarations are given in Xutil.h                             */
extern Status XReconfigureWMWindow(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    int			/* screen_number */,
    unsigned int	/* mask */,
    XWindowChanges*	/* changes */
#endif
);

extern Status XGetWMProtocols(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    Atom**		/* protocols_return */,
    int*		/* count_return */
#endif
);
extern Status XSetWMProtocols(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    Atom*		/* protocols */,
    int			/* count */
#endif
);
extern Status XIconifyWindow(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    int			/* screen_number */
#endif
);
extern Status XWithdrawWindow(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    int			/* screen_number */
#endif
);
extern Status XGetCommand(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    char***		/* argv_return */,
    int*		/* argc_return */
#endif
);
extern Status XGetWMColormapWindows(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    Window**		/* windows_return */,
    int*		/* count_return */
#endif
);
extern Status XSetWMColormapWindows(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    Window*		/* colormap_windows */,
    int			/* count */
#endif
);
extern void XFreeStringList(
#if NeedFunctionPrototypes
    char**		/* list */
#endif
);
extern int XSetTransientForHint(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    Window		/* prop_window */
#endif
);

/* The following are given in alphabetical order */

extern int XActivateScreenSaver(
#if NeedFunctionPrototypes
    Display*		/* display */
#endif
);

extern int XAddHost(
#if NeedFunctionPrototypes
    Display*		/* display */,
    XHostAddress*	/* host */
#endif
);

extern int XAddHosts(
#if NeedFunctionPrototypes
    Display*		/* display */,
    XHostAddress*	/* hosts */,
    int			/* num_hosts */    
#endif
);

extern int XAddToExtensionList(
#if NeedFunctionPrototypes
    struct _XExtData**	/* structure */,
    XExtData*		/* ext_data */
#endif
);

extern int XAddToSaveSet(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */
#endif
);

extern Status XAllocColor(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Colormap		/* colormap */,
    XColor*		/* screen_in_out */
#endif
);

extern Status XAllocColorCells(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Colormap		/* colormap */,
    Bool	        /* contig */,
    unsigned long*	/* plane_masks_return */,
    unsigned int	/* nplanes */,
    unsigned long*	/* pixels_return */,
    unsigned int 	/* npixels */
#endif
);

extern Status XAllocColorPlanes(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Colormap		/* colormap */,
    Bool		/* contig */,
    unsigned long*	/* pixels_return */,
    int			/* ncolors */,
    int			/* nreds */,
    int			/* ngreens */,
    int			/* nblues */,
    unsigned long*	/* rmask_return */,
    unsigned long*	/* gmask_return */,
    unsigned long*	/* bmask_return */
#endif
);

extern Status XAllocNamedColor(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Colormap		/* colormap */,
    _Xconst char*	/* color_name */,
    XColor*		/* screen_def_return */,
    XColor*		/* exact_def_return */
#endif
);

extern int XAllowEvents(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int			/* event_mode */,
    Time		/* time */
#endif
);

extern int XAutoRepeatOff(
#if NeedFunctionPrototypes
    Display*		/* display */
#endif
);

extern int XAutoRepeatOn(
#if NeedFunctionPrototypes
    Display*		/* display */
#endif
);

extern int XBell(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int			/* percent */
#endif
);

extern int XBitmapBitOrder(
#if NeedFunctionPrototypes
    Display*		/* display */
#endif
);

extern int XBitmapPad(
#if NeedFunctionPrototypes
    Display*		/* display */
#endif
);

extern int XBitmapUnit(
#if NeedFunctionPrototypes
    Display*		/* display */
#endif
);

extern int XCellsOfScreen(
#if NeedFunctionPrototypes
    Screen*		/* screen */
#endif
);

extern int XChangeActivePointerGrab(
#if NeedFunctionPrototypes
    Display*		/* display */,
    unsigned int	/* event_mask */,
    Cursor		/* cursor */,
    Time		/* time */
#endif
);

extern int XChangeGC(
#if NeedFunctionPrototypes
    Display*		/* display */,
    GC			/* gc */,
    unsigned long	/* valuemask */,
    XGCValues*		/* values */
#endif
);

extern int XChangeKeyboardControl(
#if NeedFunctionPrototypes
    Display*		/* display */,
    unsigned long	/* value_mask */,
    XKeyboardControl*	/* values */
#endif
);

extern int XChangeKeyboardMapping(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int			/* first_keycode */,
    int			/* keysyms_per_keycode */,
    KeySym*		/* keysyms */,
    int			/* num_codes */
#endif
);

extern int XChangePointerControl(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Bool		/* do_accel */,
    Bool		/* do_threshold */,
    int			/* accel_numerator */,
    int			/* accel_denominator */,
    int			/* threshold */
#endif
);

extern int XChangeProperty(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    Atom		/* property */,
    Atom		/* type */,
    int			/* format */,
    int			/* mode */,
    _Xconst unsigned char*	/* data */,
    int			/* nelements */
#endif
);

extern int XChangeSaveSet(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    int			/* change_mode */
#endif
);

extern int XChangeWindowAttributes(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    unsigned long	/* valuemask */,
    XSetWindowAttributes* /* attributes */
#endif
);

extern Bool XCheckIfEvent(
#if NeedFunctionPrototypes
    Display*		/* display */,
    XEvent*		/* event_return */,
    Bool (*) (
#if NeedNestedPrototypes
	       Display*			/* display */,
               XEvent*			/* event */,
               XPointer			/* arg */
#endif
             )		/* predicate */,
    XPointer		/* arg */
#endif
);

extern Bool XCheckMaskEvent(
#if NeedFunctionPrototypes
    Display*		/* display */,
    long		/* event_mask */,
    XEvent*		/* event_return */
#endif
);

extern Bool XCheckTypedEvent(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int			/* event_type */,
    XEvent*		/* event_return */
#endif
);

extern Bool XCheckTypedWindowEvent(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    int			/* event_type */,
    XEvent*		/* event_return */
#endif
);

extern Bool XCheckWindowEvent(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    long		/* event_mask */,
    XEvent*		/* event_return */
#endif
);

extern int XCirculateSubwindows(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    int			/* direction */
#endif
);

extern int XCirculateSubwindowsDown(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */
#endif
);

extern int XCirculateSubwindowsUp(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */
#endif
);

extern int XClearArea(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    int			/* x */,
    int			/* y */,
    unsigned int	/* width */,
    unsigned int	/* height */,
    Bool		/* exposures */
#endif
);

extern int XClearWindow(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */
#endif
);

extern int XCloseDisplay(
#if NeedFunctionPrototypes
    Display*		/* display */
#endif
);

extern int XConfigureWindow(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    unsigned int	/* value_mask */,
    XWindowChanges*	/* values */		 
#endif
);

extern int XConnectionNumber(
#if NeedFunctionPrototypes
    Display*		/* display */
#endif
);

extern int XConvertSelection(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Atom		/* selection */,
    Atom 		/* target */,
    Atom		/* property */,
    Window		/* requestor */,
    Time		/* time */
#endif
);

extern int XCopyArea(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* src */,
    Drawable		/* dest */,
    GC			/* gc */,
    int			/* src_x */,
    int			/* src_y */,
    unsigned int	/* width */,
    unsigned int	/* height */,
    int			/* dest_x */,
    int			/* dest_y */
#endif
);

extern int XCopyGC(
#if NeedFunctionPrototypes
    Display*		/* display */,
    GC			/* src */,
    unsigned long	/* valuemask */,
    GC			/* dest */
#endif
);

extern int XCopyPlane(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* src */,
    Drawable		/* dest */,
    GC			/* gc */,
    int			/* src_x */,
    int			/* src_y */,
    unsigned int	/* width */,
    unsigned int	/* height */,
    int			/* dest_x */,
    int			/* dest_y */,
    unsigned long	/* plane */
#endif
);

extern int XDefaultDepth(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int			/* screen_number */
#endif
);

extern int XDefaultDepthOfScreen(
#if NeedFunctionPrototypes
    Screen*		/* screen */
#endif
);

extern int XDefaultScreen(
#if NeedFunctionPrototypes
    Display*		/* display */
#endif
);

extern int XDefineCursor(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    Cursor		/* cursor */
#endif
);

extern int XDeleteProperty(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    Atom		/* property */
#endif
);

extern int XDestroyWindow(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */
#endif
);

extern int XDestroySubwindows(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */
#endif
);

extern int XDoesBackingStore(
#if NeedFunctionPrototypes
    Screen*		/* screen */    
#endif
);

extern Bool XDoesSaveUnders(
#if NeedFunctionPrototypes
    Screen*		/* screen */
#endif
);

extern int XDisableAccessControl(
#if NeedFunctionPrototypes
    Display*		/* display */
#endif
);


extern int XDisplayCells(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int			/* screen_number */
#endif
);

extern int XDisplayHeight(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int			/* screen_number */
#endif
);

extern int XDisplayHeightMM(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int			/* screen_number */
#endif
);

extern int XDisplayKeycodes(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int*		/* min_keycodes_return */,
    int*		/* max_keycodes_return */
#endif
);

extern int XDisplayPlanes(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int			/* screen_number */
#endif
);

extern int XDisplayWidth(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int			/* screen_number */
#endif
);

extern int XDisplayWidthMM(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int			/* screen_number */
#endif
);

extern int XDrawArc(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* d */,
    GC			/* gc */,
    int			/* x */,
    int			/* y */,
    unsigned int	/* width */,
    unsigned int	/* height */,
    int			/* angle1 */,
    int			/* angle2 */
#endif
);

extern int XDrawArcs(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* d */,
    GC			/* gc */,
    XArc*		/* arcs */,
    int			/* narcs */
#endif
);

extern int XDrawImageString(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* d */,
    GC			/* gc */,
    int			/* x */,
    int			/* y */,
    _Xconst char*	/* string */,
    int			/* length */
#endif
);

extern int XDrawImageString16(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* d */,
    GC			/* gc */,
    int			/* x */,
    int			/* y */,
    _Xconst XChar2b*	/* string */,
    int			/* length */
#endif
);

extern int XDrawLine(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* d */,
    GC			/* gc */,
    int			/* x1 */,
    int			/* y1 */,
    int			/* x2 */,
    int			/* y2 */
#endif
);

extern int XDrawLines(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* d */,
    GC			/* gc */,
    XPoint*		/* points */,
    int			/* npoints */,
    int			/* mode */
#endif
);

extern int XDrawPoint(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* d */,
    GC			/* gc */,
    int			/* x */,
    int			/* y */
#endif
);

extern int XDrawPoints(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* d */,
    GC			/* gc */,
    XPoint*		/* points */,
    int			/* npoints */,
    int			/* mode */
#endif
);

extern int XDrawRectangle(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* d */,
    GC			/* gc */,
    int			/* x */,
    int			/* y */,
    unsigned int	/* width */,
    unsigned int	/* height */
#endif
);

extern int XDrawRectangles(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* d */,
    GC			/* gc */,
    XRectangle*		/* rectangles */,
    int			/* nrectangles */
#endif
);

extern int XDrawSegments(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* d */,
    GC			/* gc */,
    XSegment*		/* segments */,
    int			/* nsegments */
#endif
);

extern int XDrawString(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* d */,
    GC			/* gc */,
    int			/* x */,
    int			/* y */,
    _Xconst char*	/* string */,
    int			/* length */
#endif
);

extern int XDrawString16(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* d */,
    GC			/* gc */,
    int			/* x */,
    int			/* y */,
    _Xconst XChar2b*	/* string */,
    int			/* length */
#endif
);

extern int XDrawText(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* d */,
    GC			/* gc */,
    int			/* x */,
    int			/* y */,
    XTextItem*		/* items */,
    int			/* nitems */
#endif
);

extern int XDrawText16(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* d */,
    GC			/* gc */,
    int			/* x */,
    int			/* y */,
    XTextItem16*	/* items */,
    int			/* nitems */
#endif
);

extern int XEnableAccessControl(
#if NeedFunctionPrototypes
    Display*		/* display */
#endif
);

extern int XEventsQueued(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int			/* mode */
#endif
);

extern Status XFetchName(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    char**		/* window_name_return */
#endif
);

extern int XFillArc(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* d */,
    GC			/* gc */,
    int			/* x */,
    int			/* y */,
    unsigned int	/* width */,
    unsigned int	/* height */,
    int			/* angle1 */,
    int			/* angle2 */
#endif
);

extern int XFillArcs(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* d */,
    GC			/* gc */,
    XArc*		/* arcs */,
    int			/* narcs */
#endif
);

extern int XFillPolygon(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* d */,
    GC			/* gc */,
    XPoint*		/* points */,
    int			/* npoints */,
    int			/* shape */,
    int			/* mode */
#endif
);

extern int XFillRectangle(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* d */,
    GC			/* gc */,
    int			/* x */,
    int			/* y */,
    unsigned int	/* width */,
    unsigned int	/* height */
#endif
);

extern int XFillRectangles(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* d */,
    GC			/* gc */,
    XRectangle*		/* rectangles */,
    int			/* nrectangles */
#endif
);

extern int XFlush(
#if NeedFunctionPrototypes
    Display*		/* display */
#endif
);

extern int XForceScreenSaver(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int			/* mode */
#endif
);

extern int XFree(
#if NeedFunctionPrototypes
    void*		/* data */
#endif
);

extern int XFreeColormap(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Colormap		/* colormap */
#endif
);

extern int XFreeColors(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Colormap		/* colormap */,
    unsigned long*	/* pixels */,
    int			/* npixels */,
    unsigned long	/* planes */
#endif
);

extern int XFreeCursor(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Cursor		/* cursor */
#endif
);

extern int XFreeExtensionList(
#if NeedFunctionPrototypes
    char**		/* list */    
#endif
);

extern int XFreeFont(
#if NeedFunctionPrototypes
    Display*		/* display */,
    XFontStruct*	/* font_struct */
#endif
);

extern int XFreeFontInfo(
#if NeedFunctionPrototypes
    char**		/* names */,
    XFontStruct*	/* free_info */,
    int			/* actual_count */
#endif
);

extern int XFreeFontNames(
#if NeedFunctionPrototypes
    char**		/* list */
#endif
);

extern int XFreeFontPath(
#if NeedFunctionPrototypes
    char**		/* list */
#endif
);

extern int XFreeGC(
#if NeedFunctionPrototypes
    Display*		/* display */,
    GC			/* gc */
#endif
);

extern int XFreeModifiermap(
#if NeedFunctionPrototypes
    XModifierKeymap*	/* modmap */
#endif
);

extern int XFreePixmap(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Pixmap		/* pixmap */
#endif
);

extern int XGeometry(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int			/* screen */,
    _Xconst char*	/* position */,
    _Xconst char*	/* default_position */,
    unsigned int	/* bwidth */,
    unsigned int	/* fwidth */,
    unsigned int	/* fheight */,
    int			/* xadder */,
    int			/* yadder */,
    int*		/* x_return */,
    int*		/* y_return */,
    int*		/* width_return */,
    int*		/* height_return */
#endif
);

extern int XGetErrorDatabaseText(
#if NeedFunctionPrototypes
    Display*		/* display */,
    _Xconst char*	/* name */,
    _Xconst char*	/* message */,
    _Xconst char*	/* default_string */,
    char*		/* buffer_return */,
    int			/* length */
#endif
);

extern int XGetErrorText(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int			/* code */,
    char*		/* buffer_return */,
    int			/* length */
#endif
);

extern Bool XGetFontProperty(
#if NeedFunctionPrototypes
    XFontStruct*	/* font_struct */,
    Atom		/* atom */,
    unsigned long*	/* value_return */
#endif
);

extern Status XGetGCValues(
#if NeedFunctionPrototypes
    Display*		/* display */,
    GC			/* gc */,
    unsigned long	/* valuemask */,
    XGCValues*		/* values_return */
#endif
);

extern Status XGetGeometry(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* d */,
    Window*		/* root_return */,
    int*		/* x_return */,
    int*		/* y_return */,
    unsigned int*	/* width_return */,
    unsigned int*	/* height_return */,
    unsigned int*	/* border_width_return */,
    unsigned int*	/* depth_return */
#endif
);

extern Status XGetIconName(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    char**		/* icon_name_return */
#endif
);

extern int XGetInputFocus(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window*		/* focus_return */,
    int*		/* revert_to_return */
#endif
);

extern int XGetKeyboardControl(
#if NeedFunctionPrototypes
    Display*		/* display */,
    XKeyboardState*	/* values_return */
#endif
);

extern int XGetPointerControl(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int*		/* accel_numerator_return */,
    int*		/* accel_denominator_return */,
    int*		/* threshold_return */
#endif
);

extern int XGetPointerMapping(
#if NeedFunctionPrototypes
    Display*		/* display */,
    unsigned char*	/* map_return */,
    int			/* nmap */
#endif
);

extern int XGetScreenSaver(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int*		/* timeout_return */,
    int*		/* interval_return */,
    int*		/* prefer_blanking_return */,
    int*		/* allow_exposures_return */
#endif
);

extern Status XGetTransientForHint(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    Window*		/* prop_window_return */
#endif
);

extern int XGetWindowProperty(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    Atom		/* property */,
    long		/* long_offset */,
    long		/* long_length */,
    Bool		/* delete */,
    Atom		/* req_type */,
    Atom*		/* actual_type_return */,
    int*		/* actual_format_return */,
    unsigned long*	/* nitems_return */,
    unsigned long*	/* bytes_after_return */,
    unsigned char**	/* prop_return */
#endif
);

extern Status XGetWindowAttributes(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    XWindowAttributes*	/* window_attributes_return */
#endif
);

extern int XGrabButton(
#if NeedFunctionPrototypes
    Display*		/* display */,
    unsigned int	/* button */,
    unsigned int	/* modifiers */,
    Window		/* grab_window */,
    Bool		/* owner_events */,
    unsigned int	/* event_mask */,
    int			/* pointer_mode */,
    int			/* keyboard_mode */,
    Window		/* confine_to */,
    Cursor		/* cursor */
#endif
);

extern int XGrabKey(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int			/* keycode */,
    unsigned int	/* modifiers */,
    Window		/* grab_window */,
    Bool		/* owner_events */,
    int			/* pointer_mode */,
    int			/* keyboard_mode */
#endif
);

extern int XGrabKeyboard(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* grab_window */,
    Bool		/* owner_events */,
    int			/* pointer_mode */,
    int			/* keyboard_mode */,
    Time		/* time */
#endif
);

extern int XGrabPointer(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* grab_window */,
    Bool		/* owner_events */,
    unsigned int	/* event_mask */,
    int			/* pointer_mode */,
    int			/* keyboard_mode */,
    Window		/* confine_to */,
    Cursor		/* cursor */,
    Time		/* time */
#endif
);

extern int XGrabServer(
#if NeedFunctionPrototypes
    Display*		/* display */
#endif
);

extern int XHeightMMOfScreen(
#if NeedFunctionPrototypes
    Screen*		/* screen */
#endif
);

extern int XHeightOfScreen(
#if NeedFunctionPrototypes
    Screen*		/* screen */
#endif
);

extern int XIfEvent(
#if NeedFunctionPrototypes
    Display*		/* display */,
    XEvent*		/* event_return */,
    Bool (*) (
#if NeedNestedPrototypes
	       Display*			/* display */,
               XEvent*			/* event */,
               XPointer			/* arg */
#endif
             )		/* predicate */,
    XPointer		/* arg */
#endif
);

extern int XImageByteOrder(
#if NeedFunctionPrototypes
    Display*		/* display */
#endif
);

extern int XInstallColormap(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Colormap		/* colormap */
#endif
);

extern KeyCode XKeysymToKeycode(
#if NeedFunctionPrototypes
    Display*		/* display */,
    KeySym		/* keysym */
#endif
);

extern int XKillClient(
#if NeedFunctionPrototypes
    Display*		/* display */,
    XID			/* resource */
#endif
);

extern Status XLookupColor(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Colormap		/* colormap */,
    _Xconst char*	/* color_name */,
    XColor*		/* exact_def_return */,
    XColor*		/* screen_def_return */
#endif
);

extern int XLowerWindow(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */
#endif
);

extern int XMapRaised(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */
#endif
);

extern int XMapSubwindows(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */
#endif
);

extern int XMapWindow(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */
#endif
);

extern int XMaskEvent(
#if NeedFunctionPrototypes
    Display*		/* display */,
    long		/* event_mask */,
    XEvent*		/* event_return */
#endif
);

extern int XMaxCmapsOfScreen(
#if NeedFunctionPrototypes
    Screen*		/* screen */
#endif
);

extern int XMinCmapsOfScreen(
#if NeedFunctionPrototypes
    Screen*		/* screen */
#endif
);

extern int XMoveResizeWindow(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    int			/* x */,
    int			/* y */,
    unsigned int	/* width */,
    unsigned int	/* height */
#endif
);

extern int XMoveWindow(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    int			/* x */,
    int			/* y */
#endif
);

extern int XNextEvent(
#if NeedFunctionPrototypes
    Display*		/* display */,
    XEvent*		/* event_return */
#endif
);

extern int XNoOp(
#if NeedFunctionPrototypes
    Display*		/* display */
#endif
);

extern Status XParseColor(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Colormap		/* colormap */,
    _Xconst char*	/* spec */,
    XColor*		/* exact_def_return */
#endif
);

extern int XParseGeometry(
#if NeedFunctionPrototypes
    _Xconst char*	/* parsestring */,
    int*		/* x_return */,
    int*		/* y_return */,
    unsigned int*	/* width_return */,
    unsigned int*	/* height_return */
#endif
);

extern int XPeekEvent(
#if NeedFunctionPrototypes
    Display*		/* display */,
    XEvent*		/* event_return */
#endif
);

extern int XPeekIfEvent(
#if NeedFunctionPrototypes
    Display*		/* display */,
    XEvent*		/* event_return */,
    Bool (*) (
#if NeedNestedPrototypes
	       Display*		/* display */,
               XEvent*		/* event */,
               XPointer		/* arg */
#endif
             )		/* predicate */,
    XPointer		/* arg */
#endif
);

extern int XPending(
#if NeedFunctionPrototypes
    Display*		/* display */
#endif
);

extern int XPlanesOfScreen(
#if NeedFunctionPrototypes
    Screen*		/* screen */
    
#endif
);

extern int XProtocolRevision(
#if NeedFunctionPrototypes
    Display*		/* display */
#endif
);

extern int XProtocolVersion(
#if NeedFunctionPrototypes
    Display*		/* display */
#endif
);


extern int XPutBackEvent(
#if NeedFunctionPrototypes
    Display*		/* display */,
    XEvent*		/* event */
#endif
);

extern int XPutImage(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* d */,
    GC			/* gc */,
    XImage*		/* image */,
    int			/* src_x */,
    int			/* src_y */,
    int			/* dest_x */,
    int			/* dest_y */,
    unsigned int	/* width */,
    unsigned int	/* height */	  
#endif
);

extern int XQLength(
#if NeedFunctionPrototypes
    Display*		/* display */
#endif
);

extern Status XQueryBestCursor(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* d */,
    unsigned int        /* width */,
    unsigned int	/* height */,
    unsigned int*	/* width_return */,
    unsigned int*	/* height_return */
#endif
);

extern Status XQueryBestSize(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int			/* class */,
    Drawable		/* which_screen */,
    unsigned int	/* width */,
    unsigned int	/* height */,
    unsigned int*	/* width_return */,
    unsigned int*	/* height_return */
#endif
);

extern Status XQueryBestStipple(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* which_screen */,
    unsigned int	/* width */,
    unsigned int	/* height */,
    unsigned int*	/* width_return */,
    unsigned int*	/* height_return */
#endif
);

extern Status XQueryBestTile(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* which_screen */,
    unsigned int	/* width */,
    unsigned int	/* height */,
    unsigned int*	/* width_return */,
    unsigned int*	/* height_return */
#endif
);

extern int XQueryColor(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Colormap		/* colormap */,
    XColor*		/* def_in_out */
#endif
);

extern int XQueryColors(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Colormap		/* colormap */,
    XColor*		/* defs_in_out */,
    int			/* ncolors */
#endif
);

extern Bool XQueryExtension(
#if NeedFunctionPrototypes
    Display*		/* display */,
    _Xconst char*	/* name */,
    int*		/* major_opcode_return */,
    int*		/* first_event_return */,
    int*		/* first_error_return */
#endif
);

extern int XQueryKeymap(
#if NeedFunctionPrototypes
    Display*		/* display */,
    char [32]		/* keys_return */
#endif
);

extern Bool XQueryPointer(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    Window*		/* root_return */,
    Window*		/* child_return */,
    int*		/* root_x_return */,
    int*		/* root_y_return */,
    int*		/* win_x_return */,
    int*		/* win_y_return */,
    unsigned int*       /* mask_return */
#endif
);

extern int XQueryTextExtents(
#if NeedFunctionPrototypes
    Display*		/* display */,
    XID			/* font_ID */,
    _Xconst char*	/* string */,
    int			/* nchars */,
    int*		/* direction_return */,
    int*		/* font_ascent_return */,
    int*		/* font_descent_return */,
    XCharStruct*	/* overall_return */    
#endif
);

extern int XQueryTextExtents16(
#if NeedFunctionPrototypes
    Display*		/* display */,
    XID			/* font_ID */,
    _Xconst XChar2b*	/* string */,
    int			/* nchars */,
    int*		/* direction_return */,
    int*		/* font_ascent_return */,
    int*		/* font_descent_return */,
    XCharStruct*	/* overall_return */
#endif
);

extern Status XQueryTree(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    Window*		/* root_return */,
    Window*		/* parent_return */,
    Window**		/* children_return */,
    unsigned int*	/* nchildren_return */
#endif
);

extern int XRaiseWindow(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */
#endif
);

extern int XReadBitmapFile(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable 		/* d */,
    _Xconst char*	/* filename */,
    unsigned int*	/* width_return */,
    unsigned int*	/* height_return */,
    Pixmap*		/* bitmap_return */,
    int*		/* x_hot_return */,
    int*		/* y_hot_return */
#endif
);

extern int XReadBitmapFileData(
#if NeedFunctionPrototypes
    _Xconst char*	/* filename */,
    unsigned int*	/* width_return */,
    unsigned int*	/* height_return */,
    unsigned char**	/* data_return */,
    int*		/* x_hot_return */,
    int*		/* y_hot_return */
#endif
);

extern int XRebindKeysym(
#if NeedFunctionPrototypes
    Display*		/* display */,
    KeySym		/* keysym */,
    KeySym*		/* list */,
    int			/* mod_count */,
    _Xconst unsigned char*	/* string */,
    int			/* bytes_string */
#endif
);

extern int XRecolorCursor(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Cursor		/* cursor */,
    XColor*		/* foreground_color */,
    XColor*		/* background_color */
#endif
);

extern int XRefreshKeyboardMapping(
#if NeedFunctionPrototypes
    XMappingEvent*	/* event_map */    
#endif
);

extern int XRemoveFromSaveSet(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */
#endif
);

extern int XRemoveHost(
#if NeedFunctionPrototypes
    Display*		/* display */,
    XHostAddress*	/* host */
#endif
);

extern int XRemoveHosts(
#if NeedFunctionPrototypes
    Display*		/* display */,
    XHostAddress*	/* hosts */,
    int			/* num_hosts */
#endif
);

extern int XReparentWindow(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    Window		/* parent */,
    int			/* x */,
    int			/* y */
#endif
);

extern int XResetScreenSaver(
#if NeedFunctionPrototypes
    Display*		/* display */
#endif
);

extern int XResizeWindow(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    unsigned int	/* width */,
    unsigned int	/* height */
#endif
);

extern int XRestackWindows(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window*		/* windows */,
    int			/* nwindows */
#endif
);

extern int XRotateBuffers(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int			/* rotate */
#endif
);

extern int XRotateWindowProperties(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    Atom*		/* properties */,
    int			/* num_prop */,
    int			/* npositions */
#endif
);

extern int XScreenCount(
#if NeedFunctionPrototypes
    Display*		/* display */
#endif
);

extern int XSelectInput(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    long		/* event_mask */
#endif
);

extern Status XSendEvent(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    Bool		/* propagate */,
    long		/* event_mask */,
    XEvent*		/* event_send */
#endif
);

extern int XSetAccessControl(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int			/* mode */
#endif
);

extern int XSetArcMode(
#if NeedFunctionPrototypes
    Display*		/* display */,
    GC			/* gc */,
    int			/* arc_mode */
#endif
);

extern int XSetBackground(
#if NeedFunctionPrototypes
    Display*		/* display */,
    GC			/* gc */,
    unsigned long	/* background */
#endif
);

extern int XSetClipMask(
#if NeedFunctionPrototypes
    Display*		/* display */,
    GC			/* gc */,
    Pixmap		/* pixmap */
#endif
);

extern int XSetClipOrigin(
#if NeedFunctionPrototypes
    Display*		/* display */,
    GC			/* gc */,
    int			/* clip_x_origin */,
    int			/* clip_y_origin */
#endif
);

extern int XSetClipRectangles(
#if NeedFunctionPrototypes
    Display*		/* display */,
    GC			/* gc */,
    int			/* clip_x_origin */,
    int			/* clip_y_origin */,
    XRectangle*		/* rectangles */,
    int			/* n */,
    int			/* ordering */
#endif
);

extern int XSetCloseDownMode(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int			/* close_mode */
#endif
);

extern int XSetCommand(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    char**		/* argv */,
    int			/* argc */
#endif
);

extern int XSetDashes(
#if NeedFunctionPrototypes
    Display*		/* display */,
    GC			/* gc */,
    int			/* dash_offset */,
    _Xconst char*	/* dash_list */,
    int			/* n */
#endif
);

extern int XSetFillRule(
#if NeedFunctionPrototypes
    Display*		/* display */,
    GC			/* gc */,
    int			/* fill_rule */
#endif
);

extern int XSetFillStyle(
#if NeedFunctionPrototypes
    Display*		/* display */,
    GC			/* gc */,
    int			/* fill_style */
#endif
);

extern int XSetFont(
#if NeedFunctionPrototypes
    Display*		/* display */,
    GC			/* gc */,
    Font		/* font */
#endif
);

extern int XSetFontPath(
#if NeedFunctionPrototypes
    Display*		/* display */,
    char**		/* directories */,
    int			/* ndirs */	     
#endif
);

extern int XSetForeground(
#if NeedFunctionPrototypes
    Display*		/* display */,
    GC			/* gc */,
    unsigned long	/* foreground */
#endif
);

extern int XSetFunction(
#if NeedFunctionPrototypes
    Display*		/* display */,
    GC			/* gc */,
    int			/* function */
#endif
);

extern int XSetGraphicsExposures(
#if NeedFunctionPrototypes
    Display*		/* display */,
    GC			/* gc */,
    Bool		/* graphics_exposures */
#endif
);

extern int XSetIconName(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    _Xconst char*	/* icon_name */
#endif
);

extern int XSetInputFocus(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* focus */,
    int			/* revert_to */,
    Time		/* time */
#endif
);

extern int XSetLineAttributes(
#if NeedFunctionPrototypes
    Display*		/* display */,
    GC			/* gc */,
    unsigned int	/* line_width */,
    int			/* line_style */,
    int			/* cap_style */,
    int			/* join_style */
#endif
);

extern int XSetModifierMapping(
#if NeedFunctionPrototypes
    Display*		/* display */,
    XModifierKeymap*	/* modmap */
#endif
);

extern int XSetPlaneMask(
#if NeedFunctionPrototypes
    Display*		/* display */,
    GC			/* gc */,
    unsigned long	/* plane_mask */
#endif
);

extern int XSetPointerMapping(
#if NeedFunctionPrototypes
    Display*		/* display */,
    _Xconst unsigned char*	/* map */,
    int			/* nmap */
#endif
);

extern int XSetScreenSaver(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int			/* timeout */,
    int			/* interval */,
    int			/* prefer_blanking */,
    int			/* allow_exposures */
#endif
);

extern int XSetSelectionOwner(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Atom	        /* selection */,
    Window		/* owner */,
    Time		/* time */
#endif
);

extern int XSetState(
#if NeedFunctionPrototypes
    Display*		/* display */,
    GC			/* gc */,
    unsigned long 	/* foreground */,
    unsigned long	/* background */,
    int			/* function */,
    unsigned long	/* plane_mask */
#endif
);

extern int XSetStipple(
#if NeedFunctionPrototypes
    Display*		/* display */,
    GC			/* gc */,
    Pixmap		/* stipple */
#endif
);

extern int XSetSubwindowMode(
#if NeedFunctionPrototypes
    Display*		/* display */,
    GC			/* gc */,
    int			/* subwindow_mode */
#endif
);

extern int XSetTSOrigin(
#if NeedFunctionPrototypes
    Display*		/* display */,
    GC			/* gc */,
    int			/* ts_x_origin */,
    int			/* ts_y_origin */
#endif
);

extern int XSetTile(
#if NeedFunctionPrototypes
    Display*		/* display */,
    GC			/* gc */,
    Pixmap		/* tile */
#endif
);

extern int XSetWindowBackground(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    unsigned long	/* background_pixel */
#endif
);

extern int XSetWindowBackgroundPixmap(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    Pixmap		/* background_pixmap */
#endif
);

extern int XSetWindowBorder(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    unsigned long	/* border_pixel */
#endif
);

extern int XSetWindowBorderPixmap(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    Pixmap		/* border_pixmap */
#endif
);

extern int XSetWindowBorderWidth(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    unsigned int	/* width */
#endif
);

extern int XSetWindowColormap(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    Colormap		/* colormap */
#endif
);

extern int XStoreBuffer(
#if NeedFunctionPrototypes
    Display*		/* display */,
    _Xconst char*	/* bytes */,
    int			/* nbytes */,
    int			/* buffer */
#endif
);

extern int XStoreBytes(
#if NeedFunctionPrototypes
    Display*		/* display */,
    _Xconst char*	/* bytes */,
    int			/* nbytes */
#endif
);

extern int XStoreColor(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Colormap		/* colormap */,
    XColor*		/* color */
#endif
);

extern int XStoreColors(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Colormap		/* colormap */,
    XColor*		/* color */,
    int			/* ncolors */
#endif
);

extern int XStoreName(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    _Xconst char*	/* window_name */
#endif
);

extern int XStoreNamedColor(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Colormap		/* colormap */,
    _Xconst char*	/* color */,
    unsigned long	/* pixel */,
    int			/* flags */
#endif
);

extern int XSync(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Bool		/* discard */
#endif
);

extern int XTextExtents(
#if NeedFunctionPrototypes
    XFontStruct*	/* font_struct */,
    _Xconst char*	/* string */,
    int			/* nchars */,
    int*		/* direction_return */,
    int*		/* font_ascent_return */,
    int*		/* font_descent_return */,
    XCharStruct*	/* overall_return */
#endif
);

extern int XTextExtents16(
#if NeedFunctionPrototypes
    XFontStruct*	/* font_struct */,
    _Xconst XChar2b*	/* string */,
    int			/* nchars */,
    int*		/* direction_return */,
    int*		/* font_ascent_return */,
    int*		/* font_descent_return */,
    XCharStruct*	/* overall_return */
#endif
);

extern int XTextWidth(
#if NeedFunctionPrototypes
    XFontStruct*	/* font_struct */,
    _Xconst char*	/* string */,
    int			/* count */
#endif
);

extern int XTextWidth16(
#if NeedFunctionPrototypes
    XFontStruct*	/* font_struct */,
    _Xconst XChar2b*	/* string */,
    int			/* count */
#endif
);

extern Bool XTranslateCoordinates(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* src_w */,
    Window		/* dest_w */,
    int			/* src_x */,
    int			/* src_y */,
    int*		/* dest_x_return */,
    int*		/* dest_y_return */,
    Window*		/* child_return */
#endif
);

extern int XUndefineCursor(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */
#endif
);

extern int XUngrabButton(
#if NeedFunctionPrototypes
    Display*		/* display */,
    unsigned int	/* button */,
    unsigned int	/* modifiers */,
    Window		/* grab_window */
#endif
);

extern int XUngrabKey(
#if NeedFunctionPrototypes
    Display*		/* display */,
    int			/* keycode */,
    unsigned int	/* modifiers */,
    Window		/* grab_window */
#endif
);

extern int XUngrabKeyboard(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Time		/* time */
#endif
);

extern int XUngrabPointer(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Time		/* time */
#endif
);

extern int XUngrabServer(
#if NeedFunctionPrototypes
    Display*		/* display */
#endif
);

extern int XUninstallColormap(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Colormap		/* colormap */
#endif
);

extern int XUnloadFont(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Font		/* font */
#endif
);

extern int XUnmapSubwindows(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */
#endif
);

extern int XUnmapWindow(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */
#endif
);

extern int XVendorRelease(
#if NeedFunctionPrototypes
    Display*		/* display */
#endif
);

extern int XWarpPointer(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* src_w */,
    Window		/* dest_w */,
    int			/* src_x */,
    int			/* src_y */,
    unsigned int	/* src_width */,
    unsigned int	/* src_height */,
    int			/* dest_x */,
    int			/* dest_y */	     
#endif
);

extern int XWidthMMOfScreen(
#if NeedFunctionPrototypes
    Screen*		/* screen */
#endif
);

extern int XWidthOfScreen(
#if NeedFunctionPrototypes
    Screen*		/* screen */
#endif
);

extern int XWindowEvent(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Window		/* w */,
    long		/* event_mask */,
    XEvent*		/* event_return */
#endif
);

extern int XWriteBitmapFile(
#if NeedFunctionPrototypes
    Display*		/* display */,
    _Xconst char*	/* filename */,
    Pixmap		/* bitmap */,
    unsigned int	/* width */,
    unsigned int	/* height */,
    int			/* x_hot */,
    int			/* y_hot */		     
#endif
);

extern Bool XSupportsLocale (void);

extern char *XSetLocaleModifiers(
    const char*		/* modifier_list */
);

extern XOM XOpenOM(
#if NeedFunctionPrototypes
    Display*			/* display */,
    struct _XrmHashBucketRec*	/* rdb */,
    _Xconst char*		/* res_name */,
    _Xconst char*		/* res_class */
#endif
);

extern Status XCloseOM(
#if NeedFunctionPrototypes
    XOM			/* om */
#endif
);

extern char *XSetOMValues(
#if NeedVarargsPrototypes
    XOM			/* om */,
    ...
#endif
);

extern char *XGetOMValues(
#if NeedVarargsPrototypes
    XOM			/* om */,
    ...
#endif
);

extern Display *XDisplayOfOM(
#if NeedFunctionPrototypes
    XOM			/* om */
#endif
);

extern char *XLocaleOfOM(
#if NeedFunctionPrototypes
    XOM			/* om */
#endif
);

extern XOC XCreateOC(
#if NeedVarargsPrototypes
    XOM			/* om */,
    ...
#endif
);

extern void XDestroyOC(
#if NeedFunctionPrototypes
    XOC			/* oc */
#endif
);

extern XOM XOMOfOC(
#if NeedFunctionPrototypes
    XOC			/* oc */
#endif
);

extern char *XSetOCValues(
#if NeedVarargsPrototypes
    XOC			/* oc */,
    ...
#endif
);

extern char *XGetOCValues(
#if NeedVarargsPrototypes
    XOC			/* oc */,
    ...
#endif
);

extern XFontSet XCreateFontSet(
#if NeedFunctionPrototypes
    Display*		/* display */,
    _Xconst char*	/* base_font_name_list */,
    char***		/* missing_charset_list */,
    int*		/* missing_charset_count */,
    char**		/* def_string */
#endif
);

extern void XFreeFontSet(
#if NeedFunctionPrototypes
    Display*		/* display */,
    XFontSet		/* font_set */
#endif
);

extern int XFontsOfFontSet(
#if NeedFunctionPrototypes
    XFontSet		/* font_set */,
    XFontStruct***	/* font_struct_list */,
    char***		/* font_name_list */
#endif
);

extern char *XBaseFontNameListOfFontSet(
#if NeedFunctionPrototypes
    XFontSet		/* font_set */
#endif
);

extern char *XLocaleOfFontSet(
#if NeedFunctionPrototypes
    XFontSet		/* font_set */
#endif
);

extern Bool XContextDependentDrawing(
#if NeedFunctionPrototypes
    XFontSet		/* font_set */
#endif
);

extern Bool XDirectionalDependentDrawing(
#if NeedFunctionPrototypes
    XFontSet		/* font_set */
#endif
);

extern Bool XContextualDrawing(
#if NeedFunctionPrototypes
    XFontSet		/* font_set */
#endif
);

extern XFontSetExtents *XExtentsOfFontSet(
#if NeedFunctionPrototypes
    XFontSet		/* font_set */
#endif
);

extern int XmbTextEscapement(
#if NeedFunctionPrototypes
    XFontSet		/* font_set */,
    _Xconst char*	/* text */,
    int			/* bytes_text */
#endif
);

extern int XwcTextEscapement(
#if NeedFunctionPrototypes
    XFontSet		/* font_set */,
    _Xconst wchar_t*	/* text */,
    int			/* num_wchars */
#endif
);

extern int Xutf8TextEscapement(
#if NeedFunctionPrototypes
    XFontSet		/* font_set */,
    _Xconst char*	/* text */,
    int			/* bytes_text */
#endif
);

extern int XmbTextExtents(
#if NeedFunctionPrototypes
    XFontSet		/* font_set */,
    _Xconst char*	/* text */,
    int			/* bytes_text */,
    XRectangle*		/* overall_ink_return */,
    XRectangle*		/* overall_logical_return */
#endif
);

extern int XwcTextExtents(
#if NeedFunctionPrototypes
    XFontSet		/* font_set */,
    _Xconst wchar_t*	/* text */,
    int			/* num_wchars */,
    XRectangle*		/* overall_ink_return */,
    XRectangle*		/* overall_logical_return */
#endif
);

extern int Xutf8TextExtents(
#if NeedFunctionPrototypes
    XFontSet		/* font_set */,
    _Xconst char*	/* text */,
    int			/* bytes_text */,
    XRectangle*		/* overall_ink_return */,
    XRectangle*		/* overall_logical_return */
#endif
);

extern Status XmbTextPerCharExtents(
#if NeedFunctionPrototypes
    XFontSet		/* font_set */,
    _Xconst char*	/* text */,
    int			/* bytes_text */,
    XRectangle*		/* ink_extents_buffer */,
    XRectangle*		/* logical_extents_buffer */,
    int			/* buffer_size */,
    int*		/* num_chars */,
    XRectangle*		/* overall_ink_return */,
    XRectangle*		/* overall_logical_return */
#endif
);

extern Status XwcTextPerCharExtents(
#if NeedFunctionPrototypes
    XFontSet		/* font_set */,
    _Xconst wchar_t*	/* text */,
    int			/* num_wchars */,
    XRectangle*		/* ink_extents_buffer */,
    XRectangle*		/* logical_extents_buffer */,
    int			/* buffer_size */,
    int*		/* num_chars */,
    XRectangle*		/* overall_ink_return */,
    XRectangle*		/* overall_logical_return */
#endif
);

extern Status Xutf8TextPerCharExtents(
#if NeedFunctionPrototypes
    XFontSet		/* font_set */,
    _Xconst char*	/* text */,
    int			/* bytes_text */,
    XRectangle*		/* ink_extents_buffer */,
    XRectangle*		/* logical_extents_buffer */,
    int			/* buffer_size */,
    int*		/* num_chars */,
    XRectangle*		/* overall_ink_return */,
    XRectangle*		/* overall_logical_return */
#endif
);

extern void XmbDrawText(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* d */,
    GC			/* gc */,
    int			/* x */,
    int			/* y */,
    XmbTextItem*	/* text_items */,
    int			/* nitems */
#endif
);

extern void XwcDrawText(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* d */,
    GC			/* gc */,
    int			/* x */,
    int			/* y */,
    XwcTextItem*	/* text_items */,
    int			/* nitems */
#endif
);

extern void Xutf8DrawText(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* d */,
    GC			/* gc */,
    int			/* x */,
    int			/* y */,
    XmbTextItem*	/* text_items */,
    int			/* nitems */
#endif
);

extern void XmbDrawString(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* d */,
    XFontSet		/* font_set */,
    GC			/* gc */,
    int			/* x */,
    int			/* y */,
    _Xconst char*	/* text */,
    int			/* bytes_text */
#endif
);

extern void XwcDrawString(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* d */,
    XFontSet		/* font_set */,
    GC			/* gc */,
    int			/* x */,
    int			/* y */,
    _Xconst wchar_t*	/* text */,
    int			/* num_wchars */
#endif
);

extern void Xutf8DrawString(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* d */,
    XFontSet		/* font_set */,
    GC			/* gc */,
    int			/* x */,
    int			/* y */,
    _Xconst char*	/* text */,
    int			/* bytes_text */
#endif
);

extern void XmbDrawImageString(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* d */,
    XFontSet		/* font_set */,
    GC			/* gc */,
    int			/* x */,
    int			/* y */,
    _Xconst char*	/* text */,
    int			/* bytes_text */
#endif
);

extern void XwcDrawImageString(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* d */,
    XFontSet		/* font_set */,
    GC			/* gc */,
    int			/* x */,
    int			/* y */,
    _Xconst wchar_t*	/* text */,
    int			/* num_wchars */
#endif
);

extern void Xutf8DrawImageString(
#if NeedFunctionPrototypes
    Display*		/* display */,
    Drawable		/* d */,
    XFontSet		/* font_set */,
    GC			/* gc */,
    int			/* x */,
    int			/* y */,
    _Xconst char*	/* text */,
    int			/* bytes_text */
#endif
);

extern XIM XOpenIM(
#if NeedFunctionPrototypes
    Display*			/* dpy */,
    struct _XrmHashBucketRec*	/* rdb */,
    char*			/* res_name */,
    char*			/* res_class */
#endif
);

extern Status XCloseIM(
#if NeedFunctionPrototypes
    XIM /* im */
#endif
);

extern char *XGetIMValues(
#if NeedVarargsPrototypes
    XIM /* im */, ...
#endif
);

extern char *XSetIMValues(
#if NeedVarargsPrototypes
    XIM /* im */, ...
#endif
);

extern Display *XDisplayOfIM(
#if NeedFunctionPrototypes
    XIM /* im */
#endif
);

extern char *XLocaleOfIM(
#if NeedFunctionPrototypes
    XIM /* im*/
#endif
);

extern XIC XCreateIC(
#if NeedVarargsPrototypes
    XIM /* im */, ...
#endif
);

extern void XDestroyIC(
#if NeedFunctionPrototypes
    XIC /* ic */
#endif
);

extern void XSetICFocus(
#if NeedFunctionPrototypes
    XIC /* ic */
#endif
);

extern void XUnsetICFocus(
#if NeedFunctionPrototypes
    XIC /* ic */
#endif
);

extern wchar_t *XwcResetIC(
#if NeedFunctionPrototypes
    XIC /* ic */
#endif
);

extern char *XmbResetIC(
#if NeedFunctionPrototypes
    XIC /* ic */
#endif
);

extern char *Xutf8ResetIC(
#if NeedFunctionPrototypes
    XIC /* ic */
#endif
);

extern char *XSetICValues(
#if NeedVarargsPrototypes
    XIC /* ic */, ...
#endif
);

extern char *XGetICValues(
#if NeedVarargsPrototypes
    XIC /* ic */, ...
#endif
);

extern XIM XIMOfIC(
#if NeedFunctionPrototypes
    XIC /* ic */
#endif
);

extern Bool XFilterEvent(
#if NeedFunctionPrototypes
    XEvent*	/* event */,
    Window	/* window */
#endif
);

extern int XmbLookupString(
#if NeedFunctionPrototypes
    XIC			/* ic */,
    XKeyPressedEvent*	/* event */,
    char*		/* buffer_return */,
    int			/* bytes_buffer */,
    KeySym*		/* keysym_return */,
    Status*		/* status_return */
#endif
);

extern int XwcLookupString(
#if NeedFunctionPrototypes
    XIC			/* ic */,
    XKeyPressedEvent*	/* event */,
    wchar_t*		/* buffer_return */,
    int			/* wchars_buffer */,
    KeySym*		/* keysym_return */,
    Status*		/* status_return */
#endif
);

extern int Xutf8LookupString(
#if NeedFunctionPrototypes
    XIC			/* ic */,
    XKeyPressedEvent*	/* event */,
    char*		/* buffer_return */,
    int			/* bytes_buffer */,
    KeySym*		/* keysym_return */,
    Status*		/* status_return */
#endif
);

extern XVaNestedList XVaCreateNestedList(
#if NeedVarargsPrototypes
    int /*unused*/, ...
#endif
);

/* internal connections for IMs */

extern Bool XRegisterIMInstantiateCallback(
#if NeedFunctionPrototypes
    Display*			/* dpy */,
    struct _XrmHashBucketRec*	/* rdb */,
    char*			/* res_name */,
    char*			/* res_class */,
    XIDProc			/* callback */,
    XPointer			/* client_data */
#endif
);

extern Bool XUnregisterIMInstantiateCallback(
#if NeedFunctionPrototypes
    Display*			/* dpy */,
    struct _XrmHashBucketRec*	/* rdb */,
    char*			/* res_name */,
    char*			/* res_class */,
    XIDProc			/* callback */,
    XPointer			/* client_data */
#endif
);

typedef void (*XConnectionWatchProc)(
#if NeedFunctionPrototypes
    Display*			/* dpy */,
    XPointer			/* client_data */,
    int				/* fd */,
    Bool			/* opening */,	 /* open or close flag */
    XPointer*			/* watch_data */ /* open sets, close uses */
#endif
);
    

extern Status XInternalConnectionNumbers(
#if NeedFunctionPrototypes
    Display*			/* dpy */,
    int**			/* fd_return */,
    int*			/* count_return */
#endif
);

extern void XProcessInternalConnection(
#if NeedFunctionPrototypes
    Display*			/* dpy */,
    int				/* fd */
#endif
);

extern Status XAddConnectionWatch(
#if NeedFunctionPrototypes
    Display*			/* dpy */,
    XConnectionWatchProc	/* callback */,
    XPointer			/* client_data */
#endif
);

extern void XRemoveConnectionWatch(
#if NeedFunctionPrototypes
    Display*			/* dpy */,
    XConnectionWatchProc	/* callback */,
    XPointer			/* client_data */
#endif
);

extern void XSetAuthorization(
#if NeedFunctionPrototypes
    char *			/* name */,
    int				/* namelen */, 
    char *			/* data */,
    int				/* datalen */
#endif
);

extern int _Xmbtowc(
#if NeedFunctionPrototypes
    wchar_t *			/* wstr */,
#ifdef ISC
    char const *		/* str */,
    size_t			/* len */
#else
    char *			/* str */,
    int				/* len */
#endif
#endif
);

extern int _Xwctomb(
#if NeedFunctionPrototypes
    char *			/* str */,
    wchar_t			/* wc */
#endif
);

_XFUNCPROTOEND

#endif /* _XLIB_H_ */
