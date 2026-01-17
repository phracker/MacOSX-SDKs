/* CoreGraphics - CGWindow.h
 * Copyright (c) 2006 Apple Computer, Inc.
 * All rights reserved.
 */

#ifndef CGWINDOW_H_
#define CGWINDOW_H_

/*** Basic Types ***/
#include <stdint.h>

/* The CGWindowID contains a unique value within the user session representing a window */
typedef uint32_t CGWindowID;

/* Options for use with these APIs */
typedef uint32_t CGWindowListOption;
typedef uint32_t CGWindowImageOption;

/* Types used with window backing and window sharing values */
typedef uint32_t CGWindowSharingType;
typedef uint32_t CGWindowBackingType;

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGImage.h>
#include <CoreFoundation/CFDictionary.h>
#include <CoreFoundation/CFArray.h>

CG_EXTERN_C_BEGIN

/*** Basic Definitions ***/

/* CFNumberRef encoding appropriate for use with a CGWindowID */
#define kCGWindowIDCFNumberType kCFNumberSInt32Type

/* A guaranteed invalid value for a CGWindowID */
#define kCGNullWindowID ((CGWindowID)0)

/* Values currently used for CGWindowSharingType */
enum {
    kCGWindowSharingNone = 0,
    kCGWindowSharingReadOnly = 1,
    kCGWindowSharingReadWrite = 2
};
/* CFNumberRef encoding appropriate for use with CGWindowSharingType */
#define kCGWindowSharingCFNumberType kCFNumberSInt32Type

/* Values currently used for CGWindowBackingType */
enum {
    kCGBackingStoreRetained	 = 0,
    kCGBackingStoreNonretained	 = 1,
    kCGBackingStoreBuffered	 = 2
};
/* CFNumberRef encoding appropriate for use with CGWindowBackingType */
#define kCGWindowBackingCFNumberType kCFNumberSInt32Type

/*** Keys for the dictionaries in the window list. ***/ 

/* Required: The value for this key is a CFNumberRef encoding with kCGWindowIDCFNumberType
 * the window ID, a unique value within the user session representing a window */
CG_EXTERN const CFStringRef kCGWindowNumber AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Required: The value for this key is a CFNumberRef encoding with kCFNumberIntType
 * NSBackingStoreRetained, NSBackingStoreNonretained, NSBackingStoreBuffered */
CG_EXTERN const CFStringRef kCGWindowStoreType AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*  Required: The value for this key is a CFNumberRef encoding with kCFNumberIntType
 * the window layer number */
CG_EXTERN const CFStringRef kCGWindowLayer AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Required: The value for this key is a CFDictionaryRef encoding the window bounds
 * in screen space, Quadrant IV, origin at upper left of the main display.
 * Decode to a CGRect using CGRectMakeWithDictionaryRepresentation() */
CG_EXTERN const CFStringRef kCGWindowBounds AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Required: The value for this key is a CFNumberRef encoding as a kCFNumberIntType
 * NSWindowSharingPrivate, NSWindowSharingProtected, NSWindowSharingPublic */
CG_EXTERN const CFStringRef kCGWindowSharingState AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Required: The value for this key is a CFNumberRef containint the window alpha fade
 * encoded with kCFNumberFloatType. 1.0 is normal, 0.0 is fully transparent or invisible */
CG_EXTERN const CFStringRef kCGWindowAlpha AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Required: The value for this key is a CFNumberRef encoding as a kCFNumberIntType
 * the process ID that owns the window */
CG_EXTERN const CFStringRef kCGWindowOwnerPID AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Required: The value for this key is a CFNumberRef encoding as a kCFNumberLongLongType
 * an estimate of memory in bytes currently used by the window and supporting data structures */
CG_EXTERN const CFStringRef kCGWindowMemoryUsage AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;



/*** Optional keys ***/

/* Optional: The value for this key is a CFNumberRef encoding as a kCFNumberIntType
 * the workspace the window is associated with. */
CG_EXTERN const CFStringRef kCGWindowWorkspace AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Optional: The value for this key, if present, is a CFStringRef, set if an application name is registered */
CG_EXTERN const CFStringRef kCGWindowOwnerName AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Optional: The value for this key, if present, is a CFStringRef, set if window is assigned a name.
 * Note that currently very few applications set the Quartz window name */
CG_EXTERN const CFStringRef kCGWindowName AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Optional: The value for this key, if present, is a kCFBooleanTrue,  set if window is ordered onscreen,
 * even if covered.  The key is not present if the window is not ordered onscreen */
CG_EXTERN const CFStringRef kCGWindowIsOnscreen AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Optional: The value for this key, if present, is a kCFBooleanTrue,  set if window backing is in video memory
 * The key is not present if the window backing is in main memory */
CG_EXTERN const CFStringRef kCGWindowBackingLocationVideoMemory AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*** CGWindowDescriptionListCreate() and supporting types ***/

/* Values for CGWindowListOption.  These may be ORed together */
enum
{
    /* List all windows in this user session, including both on and off-screen windows.
     * relativeToWindow should be kCGNullWindowID. */
	kCGWindowListOptionAll = 0,

    /* List all on-screen windows in this user session, ordered from front to back.
     * relativeToWindow should be kCGNullWindowID. */
	kCGWindowListOptionOnScreenOnly = (1 << 0),

    /* List all on-screen windows above the specified window ordered from front to back.
     * relativeToWindow should be the window number. */
	kCGWindowListOptionOnScreenAboveWindow = (1 << 1),

    /* List all on-screen windows below the specified window ordered from front to back.
     * relativeToWindow should be the window number. */
	kCGWindowListOptionOnScreenBelowWindow = (1 << 2),

    /* Include the named window in any list,  effectively creating 'at-or-above' or 'at-or-below' lists.
     * relativeToWindow should be the window number. */
	kCGWindowListOptionIncludingWindow = (1 << 3),
    
    /* Exclude any windows from the list that are elements of the desktop, including the background picture and
     * icons on the desktop. */
    kCGWindowListExcludeDesktopElements = (1 << 4)
};

/* CGWindowListCopyWindowInfo
 *  Copy the CFArray of CFDictionaries, with each dictionary containing descriptive information
 *  on a window within the user session.
 *  Returns NULL if called from outside of a GUI security session, or if no window server is running
 *  The returned CFArray may be empty if no windows meet the specified criteria. */
CG_EXTERN CFArrayRef CGWindowListCopyWindowInfo( CGWindowListOption option, CGWindowID relativeToWindow ) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*
 * CGWindowListCreate:
 *  Create a CFArray of CGWindowID values for windows within the user session, using the window
 *  list options and relative window, if needed.
 *  Returns NULL if called from outside of a GUI security session, or if no window server is running
 *  The returned CFArray may be empty if no windows meet the specified criteria. */
CG_EXTERN CFArrayRef CGWindowListCreate( CGWindowListOption option, CGWindowID relativeToWindow ) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* CGWindowListCreateDescriptionFromArray
 *  Create a CFArray of CFDictionaries, with each dictionary containing descriptive information
 *  on a window ID provided in windowArray if the window exists.
 *
 *  Note that there is the potential for a race condition if windows are
 *  destroyed between the generation of the CFArray of window IDs and the
 *  use of the array to generate an image.  Invalid window IDs in the array
 *  will be ignored.
 *
 *  The returned CFArray may be empty if no valid windows are found in windowArray.
 *  Returns NULL if called from outside of a GUI security session, or if no window server is running.
 */
CG_EXTERN CFArrayRef CGWindowListCreateDescriptionFromArray(CFArrayRef windowArray) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/* CGWindowListCreateImage
 *
 * Create a CGImage containing a composite of the specified set of windows
 * Returns a CGImageRef, or NULL if called from outside of a GUI security
 * session, if no window server is running, or no windows can be read.
 * If no windows meet the specified criteria, or the windows are unreadable,
 * then an empty (0 by 0 pixel, or specified size and transparent black) CGImage will be produced.
 *
 * The function takes a rectangle in Quadrant IV screen space, origin at the
 * upper left of the main display and Y value increasing downward.  A rectangle
 * with a value of CGRectInfinite is interpreted to mean the entire desktop space,
 * and will be cropped as such.  A rectangle with a value of CGRectNull is interpreted
 * to mean the bounding box for the windows to be used as the image source.  An option
 * flag allows the shadow area of the windows to be included or ignored.
 *
 * The windows to be used as the image source are specified using a CGWindowListOption and
 * a CGWindowID.
 *
 * kCGWindowListOptionAll or kCGWindowListOptionOnScreenOnly
 *  Use all windows that are on screen in this user session.
 *  The windowID should be kCGNullWindowID.
 *
 * kCGWindowListOptionOnScreenAboveWindow
 *  Use all on-screen windows above the specified window ordered from front to back.
 *  The windowID should be the window number, as from [myWindow windowNumber].
 *
 * kCGWindowListOptionOnScreenBelowWindow
 *  Use all on-screen windows below the specified window ordered from front to back.
 *  The windowID should be the window number, as from [myWindow windowNumber].
 *
 * kCGWindowListOptionIncludingWindow
 *  Use only the specified window to construct the image.
 *  The windowID should be the window number, as from [myWindow windowNumber].
 *
 * (kCGWindowListOptionOnScreenAboveWindow | kCGWindowListOptionIncludingWindow)
 *  Use all on-screen windows including and above the specified window ordered from front to back.
 *  The windowID should be the window number, as from [myWindow windowNumber].
 *
 * (kCGWindowListOptionOnScreenBelowWindow | kCGWindowListOptionIncludingWindow)
 *  Use all on-screen windows including and below the specified window ordered from front to back.
 *  The windowID should be the window number, as from [myWindow windowNumber].
 *
 * Any on-screen window with a CGWindowSharingType of kCGWindowSharingNone will be skipped.
 * If this results in no windows being available in the selected range, NULL is returned.
 *
 * The imageOption allows the caller to specify if the window frame, such as
 * a shaddow or similar effect, should be included or ignored for
 * the bounds calculation if CGRectNull is specified for the window bounds.
 */
enum {
    kCGWindowImageDefault = 0,              /* Default behavior: If a rect of CGRectNull is used
                                             * bounds computation includes the framing effects, such as a shadow. */
    kCGWindowImageBoundsIgnoreFraming = (1 << 0),  /* If a rect of CGRectNull is used,
                                                   * ignore framing effects for bounds computation */
    kCGWindowImageShouldBeOpaque = (1 << 1),  /* The captured image should be
                                              * opaque.  Empty areas are white */
	kCGWindowImageOnlyShadows = (1 << 2)
};

CG_EXTERN CGImageRef CGWindowListCreateImage( CGRect screenBounds,
                                              CGWindowListOption windowOption, CGWindowID windowID,
                                              CGWindowImageOption imageOption ) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* CGWindowListCreateImageFromArray:
 *
 * Create a CGImage containing a composite of the specified list of windows.
 * This function permits an edited list of windows to be used as the image
 * source.
 *
 * Returns a CGImageRef, or NULL if called from outside of a GUI security
 * session, if no window server is running, or no windows can be read.
 *
 * Note that there is the potential for a race condition if windows are
 * destroyed between the generation of the CFArray of window IDs and the
 * use of the array to generate an image.  Invalid window IDs in the array
 * will be ignored. If all the specified windows are unreadable or do not exist,
 * then an empty (0 by 0 pixel, or specified size and transparent black) image will be produced.
 *
 * The function takes a rectangle in Quadrant IV screen space, origin at the
 * upper left of the main display and Y value increasing downward.  A rectangle
 * with a value of CGRectInfinite is interpreted to mean the entire desktop space,
 * and will be cropped as such.  A rectangle with a value of CGRectNull is interpreted
 * to mean the bounding box for the windows to be used as the image source.  An option
 * flag allows the shadow area of the windows to be included or ignored.
 *
 * The windows to be used as the image source are specified as an CFArrayRef windowArray
 * window IDs.  These windows will be composited from first to last as if
 * ordered from front to back.  On-screen ordering is ignored.
 *
 * Invalid windows and any window with a CGWindowSharingType of kCGWindowSharingNone will be skipped.
 * If this results in no windows being available in the selected range, an empty image is returned.
 *
 * The imageOption allows the caller to specify if the window shadow should be included
 * in bounds calculation if CGRectNull is specified for the window bounds.
 */
CG_EXTERN CGImageRef CGWindowListCreateImageFromArray( CGRect screenBounds,
                                                       CFArrayRef windowArray,
                                                       CGWindowImageOption imageOption ) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


CG_EXTERN_C_END

#endif	/* CGWINDOW_H_ */

