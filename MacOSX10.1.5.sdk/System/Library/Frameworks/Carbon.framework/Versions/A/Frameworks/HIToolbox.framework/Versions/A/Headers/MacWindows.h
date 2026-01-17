/*
     File:       HIToolbox/MacWindows.h
 
     Contains:   Window Manager Interfaces
 
     Version:    HIToolbox-79.9~1
 
     Copyright:  © 1997-2001 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __MACWINDOWS__
#define __MACWINDOWS__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __ALIASES__
#include <CarbonCore/Aliases.h>
#endif

#ifndef __APPLEEVENTS__
#include <AE/AppleEvents.h>
#endif

#ifndef __COLLECTIONS__
#include <CarbonCore/Collections.h>
#endif

#ifndef __DRAG__
#include <HIToolbox/Drag.h>
#endif

#ifndef __EVENTS__
#include <HIToolbox/Events.h>
#endif

#ifndef __MENUS__
#include <HIToolbox/Menus.h>
#endif

#ifndef __MIXEDMODE__
#include <CarbonCore/MixedMode.h>
#endif

#ifndef __QDOFFSCREEN__
#include <QD/QDOffscreen.h>
#endif

#ifndef __QUICKDRAW__
#include <QD/Quickdraw.h>
#endif

#ifndef __TEXTCOMMON__
#include <CarbonCore/TextCommon.h>
#endif

#ifndef __ICONS__
#include <HIToolbox/Icons.h>
#endif

#ifndef __MACERRORS__
#include <CarbonCore/MacErrors.h>
#endif

#ifndef __CFSTRING__
#include <CoreFoundation/CFString.h>
#endif



#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if PRAGMA_STRUCT_ALIGN
    #pragma options align=mac68k
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif

/*                                                                                                      */
/* Current documentation for the Mac OS Window Manager is available on the web:                         */
/*  <http://developer.apple.com/techpubs/macos8/HumanInterfaceToolbox/WindowManager/windowmanager.html> */
/*                                                                                                      */
/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Property Types                                                                     */
/*——————————————————————————————————————————————————————————————————————————————————————*/
typedef OSType                          PropertyCreator;
typedef OSType                          PropertyTag;
/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Window Classes                                                                     */
/*——————————————————————————————————————————————————————————————————————————————————————*/
typedef UInt32 WindowClass;
enum {
  kAlertWindowClass             = 1L,   /* “I need your attention now.”*/
  kMovableAlertWindowClass      = 2L,   /* “I need your attention now, but I’m kind enough to let you switch out of this app to do other things.”*/
  kModalWindowClass             = 3L,   /* system modal, not draggable*/
  kMovableModalWindowClass      = 4L,   /* application modal, draggable*/
  kFloatingWindowClass          = 5L,   /* floats above all other application windows*/
  kDocumentWindowClass          = 6L,   /* document windows*/
  kUtilityWindowClass           = 8L,   /* system-wide floating windows (TSM, AppleGuide) (available in CarbonLib 1.1)*/
  kHelpWindowClass              = 10L,  /* help window (no frame; coachmarks, help tags ) (available in CarbonLib 1.1)*/
  kSheetWindowClass             = 11L,  /* sheet windows for dialogs (available in Mac OS X and CarbonLib 1.3)*/
  kToolbarWindowClass           = 12L,  /* toolbar windows (above documents, below floating windows) (available in CarbonLib 1.1)*/
  kPlainWindowClass             = 13L,  /* plain window (in document layer)*/
  kOverlayWindowClass           = 14L,  /* transparent window which allows 'screen' drawing via CoreGraphics (Mac OS X only)*/
  kSheetAlertWindowClass        = 15L,  /* sheet windows for alerts (available in Mac OS X after 10.0.x and CarbonLib 1.3)*/
  kAltPlainWindowClass          = 16L,  /* alternate plain window (in document layer) (available in Mac OS X after 10.0.x and CarbonLib 1.3)*/
  kAllWindowClasses             = (unsigned long)0xFFFFFFFF /* for use with GetFrontWindowOfClass, FindWindowOfClass, GetNextWindowOfClass*/
};


/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Window Attributes                                                                  */
/*——————————————————————————————————————————————————————————————————————————————————————*/

typedef UInt32                          WindowAttributes;

/*
 *  Summary:
 *    Window attributes
 */

  /*
   * A constant with value zero; the lack of any attributes.
   */
enum {
  kWindowNoAttributes           = 0L,

  /*
   * This window has a close box. Available for windows of
   * kDocumentWindowClass, kFloatingWindowClass, and
   * kUtilityWindowClass.
   */
  kWindowCloseBoxAttribute      = (1L << 0),

  /*
   * This window changes width when zooming. Available for windows of
   * kDocumentWindowClass, kFloatingWindowClass, and
   * kUtilityWindowClass.
   */
  kWindowHorizontalZoomAttribute = (1L << 1),

  /*
   * This window changes height when zooming. Available for windows of
   * kDocumentWindowClass, kFloatingWindowClass, and
   * kUtilityWindowClass.
   */
  kWindowVerticalZoomAttribute  = (1L << 2),

  /*
   * This window changes both width and height when zooming. Available
   * for windows of kDocumentWindowClass, kFloatingWindowClass, and
   * kUtilityWindowClass.
   */
  kWindowFullZoomAttribute      = (kWindowVerticalZoomAttribute | kWindowHorizontalZoomAttribute),

  /*
   * This window has a collapse box. Available for windows of
   * kDocumentWindowClass and, on Mac OS 9, kFloatingWindowClass and
   * kUtilityWindowClass; not available for windows of
   * kFloatingWindowClass or kUtilityWindowClass on Mac OS X.
   */
  kWindowCollapseBoxAttribute   = (1L << 3),

  /*
   * This window can be resized. Available for windows of
   * kDocumentWindowClass, kMovableModalWindowClass,
   * kFloatingWindowClass, kUtilityWindowClass, and kSheetWindowClass.
   */
  kWindowResizableAttribute     = (1L << 4),

  /*
   * This window has a vertical titlebar on the side of the window.
   * Available for windows of kFloatingWindowClass and
   * kUtilityWindowClass.
   */
  kWindowSideTitlebarAttribute  = (1L << 5),

  /*
   * This window has a toolbar button. Available for windows of
   * kDocumentWindowClass on Mac OS X.
   */
  kWindowToolbarButtonAttribute = (1L << 6),

  /*
   * This window receives no update events. Available for all windows.
   */
  kWindowNoUpdatesAttribute     = (1L << 16),

  /*
   * This window receives no activate events. Available for all windows.
   */
  kWindowNoActivatesAttribute   = (1L << 17),

  /*
   * This window receives mouse events even for areas of the window
   * that are transparent (have an alpha channel component of zero).
   * Available for windows of kOverlayWindowClass on Mac OS X.
   */
  kWindowOpaqueForEventsAttribute = (1L << 18),

  /*
   * This window has no shadow. Available for all windows on Mac OS X.
   * This attribute is automatically given to windows of
   * kOverlayWindowClass.
   */
  kWindowNoShadowAttribute      = (1L << 21),

  /*
   * This window is automatically hidden on suspend and shown on
   * resume. Available for all windows. This attribute is automatically
   * given to windows of kFloatingWindowClass, kHelpWindowClass, and
   * kToolbarWindowClass.
   */
  kWindowHideOnSuspendAttribute = (1L << 24),

  /*
   * This window has the standard Carbon window event handler
   * installed. Available for all windows.
   */
  kWindowStandardHandlerAttribute = (1L << 25),

  /*
   * This window is automatically hidden during fullscreen mode (when
   * the menubar is invisible) and shown afterwards. Available for all
   * windows. This attribute is automatically given to windows of
   * kUtilityWindowClass.
   */
  kWindowHideOnFullScreenAttribute = (1L << 26),

  /*
   * This window is added to the standard Window menu. Available for
   * windows of kDocumentWindowClass. This attribute is automatically
   * given to windows of kDocumentWindowClass.
   */
  kWindowInWindowMenuAttribute  = (1L << 27),

  /*
   * This window supports live resizing. Available for all windows on
   * Mac OS X.
   */
  kWindowLiveResizeAttribute    = (1L << 28),

  /*
   * This window will not be repositioned by the default
   * kEventWindowConstrain handler in response to changes in monitor
   * size, Dock position, and so on. Available for all windows on Mac
   * OS X after 10.0.x.
   */
  kWindowNoConstrainAttribute   = (unsigned long)((1L << 31)),

  /*
   * The minimum set of window attributes commonly used by document
   * windows.
   */
  kWindowStandardDocumentAttributes = (kWindowCloseBoxAttribute | kWindowFullZoomAttribute | kWindowCollapseBoxAttribute | kWindowResizableAttribute),

  /*
   * The minimum set of window attributes commonly used by floating
   * windows.
   */
  kWindowStandardFloatingAttributes = (kWindowCloseBoxAttribute | kWindowCollapseBoxAttribute)
};


/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Window Definition Type                                                             */
/*——————————————————————————————————————————————————————————————————————————————————————*/
enum {
  kWindowDefProcType            = 'WDEF'
};

/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Mac OS 7.5 Window Definition Resource IDs                                          */
/*——————————————————————————————————————————————————————————————————————————————————————*/
enum {
  kStandardWindowDefinition     = 0,    /* for document windows and dialogs*/
  kRoundWindowDefinition        = 1,    /* old da-style window*/
  kFloatingWindowDefinition     = 124   /* for floating windows*/
};

/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Variant Codes                                                                      */
/*——————————————————————————————————————————————————————————————————————————————————————*/
enum {
                                        /* for use with kStandardWindowDefinition */
  kDocumentWindowVariantCode    = 0,
  kModalDialogVariantCode       = 1,
  kPlainDialogVariantCode       = 2,
  kShadowDialogVariantCode      = 3,
  kMovableModalDialogVariantCode = 5,
  kAlertVariantCode             = 7,
  kMovableAlertVariantCode      = 9,    /* for use with kFloatingWindowDefinition */
  kSideFloaterVariantCode       = 8
};


/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • DefProc IDs                                                                        */
/*——————————————————————————————————————————————————————————————————————————————————————*/
enum {
                                        /* classic ids */
  documentProc                  = 0,
  dBoxProc                      = 1,
  plainDBox                     = 2,
  altDBoxProc                   = 3,
  noGrowDocProc                 = 4,
  movableDBoxProc               = 5,
  zoomDocProc                   = 8,
  zoomNoGrow                    = 12,   /* floating window defproc ids */
  floatProc                     = 1985,
  floatGrowProc                 = 1987,
  floatZoomProc                 = 1989,
  floatZoomGrowProc             = 1991,
  floatSideProc                 = 1993,
  floatSideGrowProc             = 1995,
  floatSideZoomProc             = 1997,
  floatSideZoomGrowProc         = 1999
};

#if CALL_NOT_IN_CARBON
/* The rDocProc (rounded WDEF, ala calculator) is not supported in Carbon.*/
enum {
  rDocProc                      = 16
};

#endif  /* CALL_NOT_IN_CARBON */

enum {
                                        /* Resource IDs for theme-savvy window defprocs */
  kWindowDocumentDefProcResID   = 64,
  kWindowDialogDefProcResID     = 65,
  kWindowUtilityDefProcResID    = 66,
  kWindowUtilitySideTitleDefProcResID = 67,
  kWindowSheetDefProcResID      = 68,
  kWindowSimpleDefProcResID     = 69,
  kWindowSheetAlertDefProcResID = 70
};

enum {
                                        /* Proc IDs for theme-savvy windows */
  kWindowDocumentProc           = 1024,
  kWindowGrowDocumentProc       = 1025,
  kWindowVertZoomDocumentProc   = 1026,
  kWindowVertZoomGrowDocumentProc = 1027,
  kWindowHorizZoomDocumentProc  = 1028,
  kWindowHorizZoomGrowDocumentProc = 1029,
  kWindowFullZoomDocumentProc   = 1030,
  kWindowFullZoomGrowDocumentProc = 1031
};


enum {
                                        /* Proc IDs for theme-savvy dialogs */
  kWindowPlainDialogProc        = 1040,
  kWindowShadowDialogProc       = 1041,
  kWindowModalDialogProc        = 1042,
  kWindowMovableModalDialogProc = 1043,
  kWindowAlertProc              = 1044,
  kWindowMovableAlertProc       = 1045
};


enum {
                                        /* procIDs available from Mac OS 8.1 (Appearance 1.0.1) forward */
  kWindowMovableModalGrowProc   = 1046
};


enum {
                                        /* Proc IDs for top title bar theme-savvy floating windows */
  kWindowFloatProc              = 1057,
  kWindowFloatGrowProc          = 1059,
  kWindowFloatVertZoomProc      = 1061,
  kWindowFloatVertZoomGrowProc  = 1063,
  kWindowFloatHorizZoomProc     = 1065,
  kWindowFloatHorizZoomGrowProc = 1067,
  kWindowFloatFullZoomProc      = 1069,
  kWindowFloatFullZoomGrowProc  = 1071
};


enum {
                                        /* Proc IDs for side title bar theme-savvy floating windows */
  kWindowFloatSideProc          = 1073,
  kWindowFloatSideGrowProc      = 1075,
  kWindowFloatSideVertZoomProc  = 1077,
  kWindowFloatSideVertZoomGrowProc = 1079,
  kWindowFloatSideHorizZoomProc = 1081,
  kWindowFloatSideHorizZoomGrowProc = 1083,
  kWindowFloatSideFullZoomProc  = 1085,
  kWindowFloatSideFullZoomGrowProc = 1087
};


enum {
                                        /* Proc IDs for sheet windows */
  kWindowSheetProc              = 1088, /* available in Mac OS X and CarbonLib 1.3 */
  kWindowSheetAlertProc         = 1120  /* available in Mac OS X after 1.0, and CarbonLib 1.3 */
};



/*
 *  Discussion:
 *    Window defproc IDs for simple windows
 */
enum {
                                        /* Proc IDs for simple windows */

  /*
   * A window that has no structure region; the content covers the
   * entire window.
   */
  kWindowSimpleProc             = 1104,

  /*
   * A window that has a 1-pixel black frame as its structure.
   */
  kWindowSimpleFrameProc        = 1105
};


/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • System 7 Window Positioning Constants                                              */
/*                                                                                      */
/* Passed into StandardAlert and used in ‘WIND’, ‘DLOG’, and ‘ALRT’ templates           */
/* StandardAlert uses zero to specify the default position. Other calls use zero to     */
/* specify “no position”.  Do not pass these constants to RepositionWindow.  Do not     */
/* store these constants in the BasicWindowDescription of a ‘wind’ resource.            */
/*——————————————————————————————————————————————————————————————————————————————————————*/

enum {
  kWindowNoPosition             = 0x0000,
  kWindowDefaultPosition        = 0x0000, /* used by StandardAlert*/
  kWindowCenterMainScreen       = 0x280A,
  kWindowAlertPositionMainScreen = 0x300A,
  kWindowStaggerMainScreen      = 0x380A,
  kWindowCenterParentWindow     = 0xA80A,
  kWindowAlertPositionParentWindow = 0xB00A,
  kWindowStaggerParentWindow    = 0xB80A,
  kWindowCenterParentWindowScreen = 0x680A,
  kWindowAlertPositionParentWindowScreen = 0x700A,
  kWindowStaggerParentWindowScreen = 0x780A
};


/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Window Positioning Methods                                                         */
/*                                                                                      */
/* Positioning methods passed to RepositionWindow.                                      */
/* Do not use them in WIND, ALRT, DLOG templates.                                       */
/* Do not confuse these constants with the constants above                              */
/*——————————————————————————————————————————————————————————————————————————————————————*/
typedef UInt32 WindowPositionMethod;
enum {
  kWindowCenterOnMainScreen     = 0x00000001,
  kWindowCenterOnParentWindow   = 0x00000002,
  kWindowCenterOnParentWindowScreen = 0x00000003,
  kWindowCascadeOnMainScreen    = 0x00000004,
  kWindowCascadeOnParentWindow  = 0x00000005,
  kWindowCascadeOnParentWindowScreen = 0x00000006,
  kWindowAlertPositionOnMainScreen = 0x00000007,
  kWindowAlertPositionOnParentWindow = 0x00000008,
  kWindowAlertPositionOnParentWindowScreen = 0x00000009
};


/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • GetWindowRegion Types                                                              */
/*——————————————————————————————————————————————————————————————————————————————————————*/
typedef UInt16                          WindowRegionCode;
enum {
                                        /* Region values to pass into GetWindowRegion & GetWindowBounds */
  kWindowTitleBarRgn            = 0,
  kWindowTitleTextRgn           = 1,
  kWindowCloseBoxRgn            = 2,
  kWindowZoomBoxRgn             = 3,
  kWindowDragRgn                = 5,
  kWindowGrowRgn                = 6,
  kWindowCollapseBoxRgn         = 7,
  kWindowTitleProxyIconRgn      = 8,    /* Mac OS 8.5 forward*/
  kWindowStructureRgn           = 32,
  kWindowContentRgn             = 33,   /* Content area of the window; empty when the window is collapsed*/
  kWindowUpdateRgn              = 34,   /* Carbon forward*/
  kWindowOpaqueRgn              = 35,   /* Mac OS X: Area of window considered to be opaque. Only valid for windows with alpha channels.*/
  kWindowGlobalPortRgn          = 40    /* Carbon forward - bounds of the window’s port in global coordinates; not affected by CollapseWindow*/
};

/* GetWindowRegionRec - a pointer to this is passed in WDEF param for kWindowMsgGetRegion*/
struct GetWindowRegionRec {
  RgnHandle           winRgn;
  WindowRegionCode    regionCode;
};
typedef struct GetWindowRegionRec       GetWindowRegionRec;
typedef GetWindowRegionRec *            GetWindowRegionPtr;
typedef GetWindowRegionRec *            GetWindowRegionRecPtr;
/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • WDEF Message Types                                                                 */
/*——————————————————————————————————————————————————————————————————————————————————————*/
/*
   SetupWindowProxyDragImageRec - setup the proxy icon drag image
   Both regions are allocated and disposed by the Window Manager.
   The GWorld is disposed of by the Window Manager, but the WDEF must allocate
   it.  See Technote on Drag Manager 1.1 additions for more information and sample code for
   setting up drag images.
*/

struct SetupWindowProxyDragImageRec {
  GWorldPtr           imageGWorld;            /* locked GWorld containing the drag image - output - can be NULL*/
  RgnHandle           imageRgn;               /* image clip region, contains the portion of the image which gets blitted to screen - preallocated output - if imageGWorld is NULL, this is ignored*/
  RgnHandle           outlineRgn;             /* the outline region used on shallow monitors - preallocated output - must always be non-empty*/
};
typedef struct SetupWindowProxyDragImageRec SetupWindowProxyDragImageRec;
/* MeasureWindowTitleRec - a pointer to this is passed in WDEF param for kWindowMsgMeasureTitle*/
struct MeasureWindowTitleRec {
                                              /* output parameters (filled in by the WDEF)*/
  SInt16              fullTitleWidth;         /* text + proxy icon width*/
  SInt16              titleTextWidth;         /* text width*/

                                              /* input parameters*/
  Boolean             isUnicodeTitle;
  Boolean             unused;                 /* future use*/
};
typedef struct MeasureWindowTitleRec    MeasureWindowTitleRec;
typedef MeasureWindowTitleRec *         MeasureWindowTitleRecPtr;
/*
   GetGrowImageRegionRec - generate a region to be xored during GrowWindow and ResizeWindow.
   This is passed along with a kWindowMsgGetGrowImageRegion message. On input, the growRect
   parameter is the window's new bounds in global coordinates. The growImageRegion parameter
   will be allocated and disposed automatically; the window definition should alter the 
   region appropriately.
*/
struct GetGrowImageRegionRec {
  Rect                growRect;
  RgnHandle           growImageRegion;
};
typedef struct GetGrowImageRegionRec    GetGrowImageRegionRec;
/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Standard Window Kinds                                                              */
/*——————————————————————————————————————————————————————————————————————————————————————*/
enum {
  dialogKind                    = 2,
  userKind                      = 8,
  kDialogWindowKind             = 2,
  kApplicationWindowKind        = 8
};


/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • FindWindow Result Codes                                                            */
/*——————————————————————————————————————————————————————————————————————————————————————*/
typedef SInt16 WindowPartCode;
enum {
  inDesk                        = 0,
  inNoWindow                    = 0,
  inMenuBar                     = 1,
  inSysWindow                   = 2,
  inContent                     = 3,
  inDrag                        = 4,
  inGrow                        = 5,
  inGoAway                      = 6,
  inZoomIn                      = 7,
  inZoomOut                     = 8,
  inCollapseBox                 = 11,   /* Mac OS 8.0 forward*/
  inProxyIcon                   = 12,   /* Mac OS 8.5 forward*/
  inToolbarButton               = 13,   /* Mac OS X forward*/
  inStructure                   = 15    /* Mac OS X 10.1 forward*/
};

/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Window Definition Hit Test Result Codes                                            */
/*——————————————————————————————————————————————————————————————————————————————————————*/
typedef SInt16 WindowDefPartCode;
enum {
  wNoHit                        = 0,
  wInContent                    = 1,
  wInDrag                       = 2,
  wInGrow                       = 3,
  wInGoAway                     = 4,
  wInZoomIn                     = 5,
  wInZoomOut                    = 6,
  wInCollapseBox                = 9,    /* Mac OS 8.0 forward*/
  wInProxyIcon                  = 10,   /* Mac OS 8.5 forward*/
  wInToolbarButton              = 11,   /* Mac OS X forward*/
  wInStructure                  = 13    /* Mac OS X 10.1 forward*/
};

/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Window Definition Messages                                                         */
/*——————————————————————————————————————————————————————————————————————————————————————*/

enum {
  kWindowMsgDraw                = 0,
  kWindowMsgHitTest             = 1,
  kWindowMsgCalculateShape      = 2,
  kWindowMsgInitialize          = 3,
  kWindowMsgCleanUp             = 4,
  kWindowMsgDrawGrowOutline     = 5,
  kWindowMsgDrawGrowBox         = 6
};

/* Messages available from Mac OS 8.0 forward*/
enum {
  kWindowMsgGetFeatures         = 7,
  kWindowMsgGetRegion           = 8
};

/* Messages available from Mac OS 8.5 forward*/
enum {
  kWindowMsgDragHilite          = 9,    /* parameter boolean indicating on or off*/
  kWindowMsgModified            = 10,   /* parameter boolean indicating saved (false) or modified (true)*/
  kWindowMsgDrawInCurrentPort   = 11,   /* same as kWindowMsgDraw, but must draw in current port*/
  kWindowMsgSetupProxyDragImage = 12,   /* parameter pointer to SetupWindowProxyDragImageRec*/
  kWindowMsgStateChanged        = 13,   /* something about the window's state has changed*/
  kWindowMsgMeasureTitle        = 14    /* measure and return the ideal title width*/
};

/* Messages only available in Carbon*/
enum {
  kWindowMsgGetGrowImageRegion  = 19    /* get region to xor during grow/resize. parameter pointer to GetGrowImageRegionRec.*/
};

/* old names*/
enum {
  wDraw                         = 0,
  wHit                          = 1,
  wCalcRgns                     = 2,
  wNew                          = 3,
  wDispose                      = 4,
  wGrow                         = 5,
  wDrawGIcon                    = 6
};

/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • State-changed Flags for kWindowMsgStateChanged                                     */
/*——————————————————————————————————————————————————————————————————————————————————————*/
enum {
  kWindowStateTitleChanged      = (1 << 0)
};


/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Window Feature Bits                                                                */
/*——————————————————————————————————————————————————————————————————————————————————————*/
enum {
  kWindowCanGrow                = (1 << 0),
  kWindowCanZoom                = (1 << 1),
  kWindowCanCollapse            = (1 << 2),
  kWindowIsModal                = (1 << 3),
  kWindowCanGetWindowRegion     = (1 << 4),
  kWindowIsAlert                = (1 << 5),
  kWindowHasTitleBar            = (1 << 6)
};

/* Feature bits available from Mac OS 8.5 forward*/
enum {
  kWindowSupportsDragHilite     = (1 << 7), /* window definition supports kWindowMsgDragHilite*/
  kWindowSupportsModifiedBit    = (1 << 8), /* window definition supports kWindowMsgModified*/
  kWindowCanDrawInCurrentPort   = (1 << 9), /* window definition supports kWindowMsgDrawInCurrentPort*/
  kWindowCanSetupProxyDragImage = (1 << 10), /* window definition supports kWindowMsgSetupProxyDragImage*/
  kWindowCanMeasureTitle        = (1 << 11), /* window definition supports kWindowMsgMeasureTitle*/
  kWindowWantsDisposeAtProcessDeath = (1 << 12), /* window definition wants a Dispose message for windows still extant during ExitToShell*/
  kWindowSupportsGetGrowImageRegion = (1 << 13), /* window definition will calculate the grow image region manually.*/
  kWindowDefSupportsColorGrafPort = 0x40000002
};

/* Feature bits for post MacOS 10.0*/
enum {
  kWindowIsOpaque               = (1 << 14) /* Window doesn't need an alpha channel. Saves memory.*/
};

/*
   THIS CONSTANT IS GOING AWAY. IT IS NAMED INCORRECTLY. USE THE GETGROWIMAGE CONSTANT ABOVE INSTEAD.
   DO YOU HEAR ME! AM I YELLING LOUD ENOUGH?!
*/
enum {
  kWindowSupportsSetGrowImageRegion = (1 << 13)
};

/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Desktop Pattern Resource ID                                                        */
/*——————————————————————————————————————————————————————————————————————————————————————*/
enum {
  deskPatID                     = 16
};



/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Window Color Part Codes                                                            */
/*——————————————————————————————————————————————————————————————————————————————————————*/
enum {
  wContentColor                 = 0,
  wFrameColor                   = 1,
  wTextColor                    = 2,
  wHiliteColor                  = 3,
  wTitleBarColor                = 4
};


/*——————————————————————————————————————————————————————————————————————————————————————*/
/*  • Region Dragging Constants                                                         */
/*——————————————————————————————————————————————————————————————————————————————————————*/

enum {
  kMouseUpOutOfSlop             = (long)0x80008000
};


/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Window Color Table                                                                 */
/*——————————————————————————————————————————————————————————————————————————————————————*/
struct WinCTab {
  long                wCSeed;                 /* reserved */
  short               wCReserved;             /* reserved */
  short               ctSize;                 /* usually 4 for windows */
  ColorSpec           ctTable[5];
};
typedef struct WinCTab                  WinCTab;
typedef WinCTab *                       WCTabPtr;
typedef WCTabPtr *                      WCTabHandle;
/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • WindowRecord                                                                       */
/*——————————————————————————————————————————————————————————————————————————————————————*/
#if !OPAQUE_TOOLBOX_STRUCTS
typedef struct WindowRecord             WindowRecord;
typedef WindowRecord *                  WindowPeek;
struct WindowRecord {
  GrafPort            port;                   /* in Carbon use GetWindowPort*/
  short               windowKind;             /* in Carbon use Get/SetWindowKind*/
  Boolean             visible;                /* in Carbon use Hide/ShowWindow, ShowHide, IsWindowVisible*/
  Boolean             hilited;                /* in Carbon use HiliteWindow, IsWindowHilited*/
  Boolean             goAwayFlag;             /* in Carbon use ChangeWindowAttributes*/
  Boolean             spareFlag;              /* in Carbon use ChangeWindowAttributes*/
  RgnHandle           strucRgn;               /* in Carbon use GetWindowRegion*/
  RgnHandle           contRgn;                /* in Carbon use GetWindowRegion*/
  RgnHandle           updateRgn;              /* in Carbon use GetWindowRegion*/
  Handle              windowDefProc;          /* not supported in Carbon */
  Handle              dataHandle;             /* not supported in Carbon */
  StringHandle        titleHandle;            /* in Carbon use Get/SetWTitle */
  short               titleWidth;             /* in Carbon use GetWindowRegion */
  Handle              controlList;            /* in Carbon use GetRootControl */
  WindowPeek          nextWindow;             /* in Carbon use GetNextWindow */
  PicHandle           windowPic;              /* in Carbon use Get/SetWindowPic */
  long                refCon;                 /* in Carbon use Get/SetWRefCon*/
};

#endif  /* !OPAQUE_TOOLBOX_STRUCTS */

/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Color WindowRecord                                                                 */
/*——————————————————————————————————————————————————————————————————————————————————————*/
#if !OPAQUE_TOOLBOX_STRUCTS
typedef struct CWindowRecord            CWindowRecord;
typedef CWindowRecord *                 CWindowPeek;
struct CWindowRecord {
  CGrafPort           port;                   /* in Carbon use GetWindowPort*/
  short               windowKind;             /* in Carbon use Get/SetWindowKind    */
  Boolean             visible;                /* in Carbon use Hide/ShowWindow, ShowHide, IsWindowVisible     */
  Boolean             hilited;                /* in Carbon use HiliteWindow, IsWindowHilited*/
  Boolean             goAwayFlag;             /* in Carbon use ChangeWindowAttributes   */
  Boolean             spareFlag;              /* in Carbon use ChangeWindowAttributes   */
  RgnHandle           strucRgn;               /* in Carbon use GetWindowRegion  */
  RgnHandle           contRgn;                /* in Carbon use GetWindowRegion  */
  RgnHandle           updateRgn;              /* in Carbon use GetWindowRegion  */
  Handle              windowDefProc;          /* not supported in Carbon */
  Handle              dataHandle;             /* not supported in Carbon */
  StringHandle        titleHandle;            /* in Carbon use Get/SetWTitle */
  short               titleWidth;             /* in Carbon use GetWindowRegion */
  Handle              controlList;            /* in Carbon use GetRootControl */
  CWindowPeek         nextWindow;             /* in Carbon use GetNextWindow */
  PicHandle           windowPic;              /* in Carbon use Get/SetWindowPic     */
  long                refCon;                 /* in Carbon use Get/SetWRefCon      */
};

#endif  /* !OPAQUE_TOOLBOX_STRUCTS */

/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • AuxWinHandle                                                                       */
/*——————————————————————————————————————————————————————————————————————————————————————*/
#if !OPAQUE_TOOLBOX_STRUCTS
typedef struct AuxWinRec                AuxWinRec;
typedef AuxWinRec *                     AuxWinPtr;
typedef AuxWinPtr *                     AuxWinHandle;
struct AuxWinRec {
  AuxWinHandle        awNext;                 /* handle to next AuxWinRec, not supported in Carbon*/
  WindowRef           awOwner;                /* not supported in Carbon*/
  CTabHandle          awCTable;               /* color table for this window, use  Get/SetWindowContentColor in Carbon*/
  Handle              reserved;               /* not supported in Carbon*/
  long                awFlags;                /* reserved for expansion, not supported in Carbon*/
  CTabHandle          awReserved;             /* reserved for expansion, not supported in Carbon*/
  long                awRefCon;               /* user constant, in Carbon use Get/SetWindowProperty if you need more refCons*/
};

#endif  /* !OPAQUE_TOOLBOX_STRUCTS */

/*——————————————————————————————————————————————————————————————————————————————————————*/
/*  • BasicWindowDescription                                                            */
/*                                                                                      */
/*  Contains statically-sized basic attributes of the window, for storage in a          */
/*  collection item.                                                                    */
/*——————————————————————————————————————————————————————————————————————————————————————*/
/* constants for the version field*/
enum {
  kWindowDefinitionVersionOne   = 1,
  kWindowDefinitionVersionTwo   = 2
};

/* constants for the stateflags bit field */
enum {
  kWindowIsCollapsedState       = (1 << 0L)
};

struct BasicWindowDescription {
  UInt32              descriptionSize;        /* sizeof(BasicWindowDescription)*/

  Rect                windowContentRect;      /* location on screen*/
  Rect                windowZoomRect;         /* location on screen when zoomed out*/
  UInt32              windowRefCon;           /* the refcon - __avoid saving stale pointers here__  */
  UInt32              windowStateFlags;       /* window state bit flags*/
  WindowPositionMethod  windowPositionMethod; /* method last used by RepositionWindow to position the window (if any)*/

  UInt32              windowDefinitionVersion;
  union {
    struct {
      SInt16              windowDefProc;      /* defProc and variant*/
      Boolean             windowHasCloseBox;
    }                       versionOne;

    struct {
      WindowClass         windowClass;        /* the class*/
      WindowAttributes    windowAttributes;   /* the attributes*/
    }                       versionTwo;

  }                       windowDefinition;
};
typedef struct BasicWindowDescription   BasicWindowDescription;
/*  the window manager stores the default collection items using these IDs*/
enum {
  kStoredWindowSystemTag        = 'appl', /* Only Apple collection items will be of this tag*/
  kStoredBasicWindowDescriptionID = 'sbas', /* BasicWindowDescription*/
  kStoredWindowPascalTitleID    = 's255' /* pascal title string*/
};

enum {
  kStoredWindowUnicodeTitleID   = 'ustr', /* Unicode title string*/
  kStoredWindowTitleCFStringID  = 'cfst' /* CFString title string*/
};

/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Window Class Ordering                                                              */
/*                                                                                      */
/*  Special cases for the “behind” parameter in window creation calls.                  */
/*——————————————————————————————————————————————————————————————————————————————————————*/
#define kFirstWindowOfClass             ((WindowRef)(-1))
#define kLastWindowOfClass              ((WindowRef)0)

/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Zoom Information Handle                                                            */
/*——————————————————————————————————————————————————————————————————————————————————————*/
struct WStateData {
  Rect                userState;              /*user zoom state*/
  Rect                stdState;               /*standard zoom state*/
};
typedef struct WStateData               WStateData;
typedef WStateData *                    WStateDataPtr;
typedef WStateDataPtr *                 WStateDataHandle;
/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • MixedMode & ProcPtrs                                                               */
/*——————————————————————————————————————————————————————————————————————————————————————*/
typedef CALLBACK_API( long , WindowDefProcPtr )(short varCode, WindowRef window, short message, long param);
typedef CALLBACK_API( void , DeskHookProcPtr )(Boolean mouseClick, EventRecord *theEvent);
typedef CALLBACK_API( OSStatus , WindowPaintProcPtr )(GDHandle device, GrafPtr qdContext, WindowRef window, RgnHandle inClientPaintRgn, RgnHandle outSystemPaintRgn, void *refCon);
typedef STACK_UPP_TYPE(WindowDefProcPtr)                        WindowDefUPP;
typedef STACK_UPP_TYPE(DeskHookProcPtr)                         DeskHookUPP;
typedef STACK_UPP_TYPE(WindowPaintProcPtr)                      WindowPaintUPP;
/*
 *  NewWindowDefUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern WindowDefUPP
NewWindowDefUPP(WindowDefProcPtr userRoutine);

/*
 *  NewDeskHookUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  NewWindowPaintUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern WindowPaintUPP
NewWindowPaintUPP(WindowPaintProcPtr userRoutine);

/*
 *  DisposeWindowDefUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeWindowDefUPP(WindowDefUPP userUPP);

/*
 *  DisposeDeskHookUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  DisposeWindowPaintUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeWindowPaintUPP(WindowPaintUPP userUPP);

/*
 *  InvokeWindowDefUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern long
InvokeWindowDefUPP(
  short         varCode,
  WindowRef     window,
  short         message,
  long          param,
  WindowDefUPP  userUPP);

/*
 *  InvokeDeskHookUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  InvokeWindowPaintUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSStatus
InvokeWindowPaintUPP(
  GDHandle        device,
  GrafPtr         qdContext,
  WindowRef       window,
  RgnHandle       inClientPaintRgn,
  RgnHandle       outSystemPaintRgn,
  void *          refCon,
  WindowPaintUPP  userUPP);

/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Window Definition Spec.  Used in Carbon to specify the code that defines a window. */
/*——————————————————————————————————————————————————————————————————————————————————————*/
enum {
  kWindowDefProcPtr             = 0,    /* raw proc-ptr based access*/
  kWindowDefObjectClass         = 1,    /* event-based definition (Carbon 1.1 or later)*/
  kWindowDefProcID              = 2     /* explicit proc ID; overrides the window class default proc ID*/
};

typedef UInt32                          WindowDefType;
struct WindowDefSpec {
  WindowDefType       defType;
  union {
    WindowDefUPP        defProc;
    void *              classRef;
    short               procID;
  }                       u;
};
typedef struct WindowDefSpec            WindowDefSpec;
typedef WindowDefSpec *                 WindowDefSpecPtr;
/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Window Creation & Persistence                                                      */
/*——————————————————————————————————————————————————————————————————————————————————————*/
/*
 *  GetNewCWindow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern WindowRef 
GetNewCWindow(
  short       windowID,
  void *      wStorage,
  WindowRef   behind);


/*
 *  NewWindow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern WindowRef 
NewWindow(
  void *             wStorage,
  const Rect *       boundsRect,
  ConstStr255Param   title,
  Boolean            visible,
  short              theProc,
  WindowRef          behind,
  Boolean            goAwayFlag,
  long               refCon);


/*
 *  GetNewWindow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern WindowRef 
GetNewWindow(
  short       windowID,
  void *      wStorage,
  WindowRef   behind);


/*
 *  NewCWindow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern WindowRef 
NewCWindow(
  void *             wStorage,
  const Rect *       boundsRect,
  ConstStr255Param   title,
  Boolean            visible,
  short              procID,
  WindowRef          behind,
  Boolean            goAwayFlag,
  long               refCon);


/*
 *  DisposeWindow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DisposeWindow(WindowRef window);


/*
 *  [Mac]CloseWindow()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */



/*
   Routines available from Mac OS 8.5 forward
   or from Mac OS 8.1 forward when linking to CarbonLib 1.0 forward
*/

/*
 *  CreateNewWindow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
CreateNewWindow(
  WindowClass        windowClass,
  WindowAttributes   attributes,
  const Rect *       contentBounds,
  WindowRef *        outWindow);


/* Routines available from Mac OS 8.5 forward*/

/* Create a window from a ‘wind’ resource*/
/*
 *  CreateWindowFromResource()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
CreateWindowFromResource(
  SInt16       resID,
  WindowRef *  outWindow);


/* window persistence*/
/*
 *  StoreWindowIntoCollection()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
StoreWindowIntoCollection(
  WindowRef    window,
  Collection   collection);


/*
 *  CreateWindowFromCollection()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
CreateWindowFromCollection(
  Collection   collection,
  WindowRef *  outWindow);


/* window refcounting*/
/*
 *  GetWindowOwnerCount()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
GetWindowOwnerCount(
  WindowRef   window,
  UInt32 *    outCount);


/*
 *  CloneWindow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
CloneWindow(WindowRef window);


/*
 *  GetWindowRetainCount()
 *  
 *  Summary:
 *    Returns the retain count of a window.
 *  
 *  Discussion:
 *    This API is equivalent to GetWindowOwnerCount. For consistency
 *    with CoreFoundation and Carbon Events, it is preferred over
 *    GetWindowOwnerCount. Both APIs will continue to be supported.
 *  
 *  Parameters:
 *    
 *    inWindow:
 *      The window whose retain count to retrieve.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern ItemCount 
GetWindowRetainCount(WindowRef inWindow);


/*
 *  RetainWindow()
 *  
 *  Summary:
 *    Increments the retain count of a window.
 *  
 *  Discussion:
 *    This API is equivalent to CloneWindow. For consistency with
 *    CoreFoundation and Carbon Events, it is preferred over
 *    CloneWindow. Both APIs will continue to be supported.
 *  
 *  Parameters:
 *    
 *    inWindow:
 *      The window whose retain count to increment.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
RetainWindow(WindowRef inWindow);


/*
 *  ReleaseWindow()
 *  
 *  Summary:
 *    Decrements the retain count of a window, and destroys the window
 *    if the retain count falls to zero.
 *  
 *  Discussion:
 *    This API is equivalent to DisposeWindow. For consistency with
 *    CoreFoundation and Carbon Events, it is preferred over
 *    DisposeWindow. Both APIs will continue to be supported.
 *  
 *  Parameters:
 *    
 *    inWindow:
 *      The window whose retain count to decrement.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ReleaseWindow(WindowRef inWindow);



/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Custom Windows                                                                     */
/*——————————————————————————————————————————————————————————————————————————————————————*/
/* Routines available from Mac OS 8.1 forward when linking to CarbonLib 1.0 forward*/

/*
 *  CreateCustomWindow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateCustomWindow(
  const WindowDefSpec *  def,
  WindowClass            windowClass,
  WindowAttributes       attributes,
  const Rect *           contentBounds,
  WindowRef *            outWindow);


/*
 *  ReshapeCustomWindow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ReshapeCustomWindow(WindowRef window);


/*
 *  RegisterWindowDefinition()
 *  
 *  Summary:
 *    Registers or unregisters a binding between a resource ID and a
 *    window definition function.
 *  
 *  Discussion:
 *    In the Mac OS 8.x Window Manager, a 'WIND' resource can contain
 *    an embedded WDEF procID that is used by the Window Manager as the
 *    resource ID of an 'WDEF' resource to lay out and draw the window.
 *    The 'WDEF' resource is loaded by the Window Manager when you load
 *    the menu with GetNewWindow. Since WDEFs can no longer be packaged
 *    as code resources on Carbon, the procID can no longer refer
 *    directly to a WDEF resource. However, using
 *    RegisterWindowDefinition you can instead specify a
 *    UniversalProcPtr pointing to code in your application code
 *    fragment. RegisterWindowDefinition is available when linking to
 *    CarbonLib 1.1 forward.
 *  
 *  Parameters:
 *    
 *    inResID:
 *      A WDEF proc ID, as used in a 'WIND' resource.
 *    
 *    inDefSpec:
 *      Specifies the WindowDefUPP that should be used for windows with
 *      the given WDEF proc ID. Passing NULL allows you to unregister
 *      the window definition that had been associated with the given
 *      WDEF proc ID.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
RegisterWindowDefinition(
  SInt16                 inResID,
  const WindowDefSpec *  inDefSpec);



/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Window part tracking                                                               */
/*——————————————————————————————————————————————————————————————————————————————————————*/
/*
   Routines available from Mac OS 8.5 forward
        (or from Mac OS 8.6 forward when linking to CarbonLib 1.1 forward)
*/


/*
 *  GetWindowWidgetHilite()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
GetWindowWidgetHilite(
  WindowRef            inWindow,
  WindowDefPartCode *  outHilite);



/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Window Metainformation Accessors                                                   */
/*——————————————————————————————————————————————————————————————————————————————————————*/
/*
 *  IsValidWindowClass()
 *  
 *  Summary:
 *    Indicates whether a window class is supported by the Window
 *    Manager.
 *  
 *  Parameters:
 *    
 *    inClass:
 *      The window class.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
IsValidWindowClass(WindowClass inClass);


/*
 *  GetAvailableWindowAttributes()
 *  
 *  Summary:
 *    Returns the window attributes that are valid for a window class.
 *  
 *  Discussion:
 *    This API is useful because some window classes support different
 *    attributes on different platforms (for example, floating windows
 *    can have collapse boxes on 9, but not on X), and the Window
 *    Manager will return an error if you attempt to create a window
 *    with attributes that aren't supported for the requested window
 *    class. You can use this API to remove attributes that are not
 *    supported by the current platform before calling CreateNewWindow.
 *  
 *  Parameters:
 *    
 *    inClass:
 *      The window class.
 *  
 *  Result:
 *    The window attributes that are supported for the specified window
 *    class.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern WindowAttributes 
GetAvailableWindowAttributes(WindowClass inClass);


/*
   Routines available from Mac OS 8.5 forward
   or from Mac OS 8.1 forward when linking to CarbonLib 1.0 forward
*/
/*
 *  GetWindowClass()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
GetWindowClass(
  WindowRef      window,
  WindowClass *  outClass);


/*
 *  GetWindowAttributes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
GetWindowAttributes(
  WindowRef           window,
  WindowAttributes *  outAttributes);


/*
   Routines available from Mac OS 9.0 forward
   or from Mac OS 8.1 forward when linking to CarbonLib 1.0 forward
*/
/*
 *  ChangeWindowAttributes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ChangeWindowAttributes(
  WindowRef          window,
  WindowAttributes   setTheseAttributes,
  WindowAttributes   clearTheseAttributes);


/*
    WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
    WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
    
    SetWindowClass will disappear in the near future. Instead of SetWindowClass,
    you should use SetWindowGroup to move a window into the group of the desired
    class. This API is very dangerous in that is actually does change the class
    of the window, but class was meant to be an immutable property of the window.
    At the very least, this API will be modified to only change the layer of the
    window to match the layer that the specified class normally lives in. Consider
    yourself warned!
    
    WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
    WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
*/
/*
 *  SetWindowClass()
 *  
 *  Summary:
 *    Changes the window class of a window.
 *  
 *  Discussion:
 *    SetWindowClass changes the class of a window. It also changes the
 *    window's z-order so that it is grouped with other windows of the
 *    same class. It does not change the visual appearance of the
 *    window. In CarbonLib, SetWindowClass may not be used to change a
 *    non-utility window to have utility window class, or to make a
 *    utility window have non-utility class. SetWindowClass is
 *    available from CarbonLib 1.1 forward.
 *  
 *  Parameters:
 *    
 *    inWindow:
 *      The window whose class to change.
 *    
 *    inWindowClass:
 *      The new window class.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetWindowClass(
  WindowRef     inWindow,
  WindowClass   inWindowClass);



/*——————————————————————————————————————————————————————————————————————————————————————*/
/*  • Window Modality                                                                   */
/*——————————————————————————————————————————————————————————————————————————————————————*/

/*
 *  WindowModality
 *  
 */

  /*
   * A window does not prevent interaction with any other window in the
   * system.
   */
typedef UInt32 WindowModality;
enum {
  kWindowModalityNone           = 0,

  /*
   * A window prevents interaction with all other windows in the
   * system. Only available in CarbonLib. Mapped to
   * kWindowModalityAppModal in Mac OS X.
   */
  kWindowModalitySystemModal    = 1,

  /*
   * A window prevents interaction with other windows in the same
   * process.
   */
  kWindowModalityAppModal       = 2,

  /*
   * A window prevents interaction with a single other window.
   */
  kWindowModalityWindowModal    = 3
};


/*
 *  SetWindowModality()
 *  
 *  Summary:
 *    Sets the modality of a window.
 *  
 *  Discussion:
 *    The modality of a window is used by the Carbon event manager to
 *    automatically determine appropriate event handling.
 *  
 *  Parameters:
 *    
 *    inWindow:
 *      The window whose modality to set.
 *    
 *    inModalKind:
 *      The new modality for the window.
 *    
 *    inUnavailableWindow:
 *      If the window is becoming window-modal, this parameter
 *      specifies the window to which the inWindow parameter is modal.
 *      The unavailableWindow will not be available while inWindow is
 *      in window-modal state.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetWindowModality(
  WindowRef        inWindow,
  WindowModality   inModalKind,
  WindowRef        inUnavailableWindow);


/*
 *  GetWindowModality()
 *  
 *  Summary:
 *    Retrieves the modality of a window.
 *  
 *  Parameters:
 *    
 *    inWindow:
 *      The window whose modality to retrieve.
 *    
 *    outModalKind:
 *      On exit, contains the modality of the window.
 *    
 *    outUnavailableWindow:
 *      On exit, if the window is window-modal, contains the target
 *      window of the specified window's modality.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetWindowModality(
  WindowRef         inWindow,
  WindowModality *  outModalKind,
  WindowRef *       outUnavailableWindow);      /* can be NULL */



/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Floating Windows                                                                   */
/*——————————————————————————————————————————————————————————————————————————————————————*/
/*
   Routines available from Mac OS 8.6 forward
   or from Mac OS 8.1 forward when linking to CarbonLib 1.0 forward
*/

/*
 *  ShowFloatingWindows()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
ShowFloatingWindows(void);


/*
 *  HideFloatingWindows()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
HideFloatingWindows(void);


/*
 *  AreFloatingWindowsVisible()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern Boolean 
AreFloatingWindowsVisible(void);



/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Window Groups                                                                      */
/*                                                                                      */
/* The Window Group API allows the creation and management of groups of windows,        */
/* allowing control of the z-order, activation, and positioning of the windows.         */
/* Internally to the Window Manager, each of the standard window tiers (document,       */
/* toolbar, floating, modal, utility, help, and overlay) is implemented as a window     */
/* group; you can access the window group for a class with GetWindowGroupOfClass.       */
/* You can create your own window groups, if you would like your windows to float,      */
/* for example, above the floating window layer but below the modal layer. It is        */
/* also possible to create more complex hierarchical arrangements of window groups.     */
/*——————————————————————————————————————————————————————————————————————————————————————*/
typedef struct OpaqueWindowGroupRef*    WindowGroupRef;
/* may be passed as the "behindWindow" parameter to NewCWindow and SendBehind*/
#define kFirstWindowOfGroup             ((WindowRef)(-1))
#define kLastWindowOfGroup              ((WindowRef)NULL)
/* may be passed as the "behindGroup" parameter to SendWindowGroupBehind*/
#define kFirstWindowGroup               ((WindowGroupRef)(-1))
#define kLastWindowGroup                ((WindowGroupRef)NULL)

/*
 *  WindowGroupAttributes
 *  
 *  Summary:
 *    These are attributes that may be applied to a window group.
 */

  /*
   * Makes the group behave somewhat as a layer of windows that move
   * together. When any window in the group is brought to the front of
   * the group, the entire group will also be brought to the front of
   * the containing group's child hierarchy.
   */
typedef UInt32 WindowGroupAttributes;
enum {
  kWindowGroupAttrSelectAsLayer = 1 << 0,

  /*
   * The positions of the contents of this group with respect to each
   * other cannot be changed. When one item moves, all other items are
   * moved simultaneously.
   */
  kWindowGroupAttrMoveTogether  = 1 << 1,

  /*
   * The z-order of the contents of this group with respect to each
   * other cannot be changed. When one item changes z-order, all other
   * items are moved simulataneously. For purposes of z-ordering, the
   * group and all its subgroups are effectively treated as if they
   * were a single window in the parent group of this group.
   */
  kWindowGroupAttrLayerTogether = 1 << 2,

  /*
   * The active state of the windows in this group is shared. The
   * windows in the group are activated or deactivated according to the
   * activation scope of the group, but when any window in the group
   * changes activation, all other windows change to match.
   */
  kWindowGroupAttrSharedActivation = 1 << 3,

  /*
   * When any window in this group is collapsed, all other windows in
   * this group are hidden. All subgroups of this group are also
   * examined for the HideOnCollapse attribute, and any the windows of
   * any subgroup with this attribute are also hidden. All windows will
   * be shown again when the collapsed window is expanded.
   */
  kWindowGroupAttrHideOnCollapse = 1 << 4
};


/*
 *  WindowActivationScope
 *  
 *  Discussion:
 *    Every window has a WindowActivationScope. It defines how windows
 *    are activated by the Window Manager with respect to other windows
 *    in the window’s group and in the current process.
 */

  /*
   * Windows with this scope are never activated by the Window Manager.
   * This should be used when the window’s visual state does not change
   * based on activation (for example, tooltip windows), or when the
   * client wishes to manually control all activation. The window owner
   * is free to explicitly activate windows using the ActivateWindow
   * and DeactivateWindow APIs.
   */
typedef UInt32 WindowActivationScope;
enum {
  kWindowActivationScopeNone    = 0,

  /*
   * Windows with this scope are always active if visible. Windows with
   * this scope are unaffected by the activation state of other
   * windows. This activation scope is automatically used by floating
   * windows.
   */
  kWindowActivationScopeIndependent = 1,

  /*
   * Windows with this scope are activated relative to other windows
   * with the same scope in the current process. Only one window with
   * this scope can be active in the entire process. This activation
   * scope is automatically used by document and dialog windows.
   */
  kWindowActivationScopeAll     = 2
};


/*
 *  Summary:
 *    These are constants that can be used for the inNextGroup
 *    parameter to GetSiblingWindowGroup.
 */

  /*
   * Indicates that GetSiblingWindowGroup should return the next deeper
   * sibling group in the z-order.
   */
enum {
  kNextWindowGroup              = true,

  /*
   * Indicates that GetSiblingWindowGroup should return the next higher
   * sibling group in the z-order.
   */
  kPreviousWindowGroup          = false
};


/*
 *  WindowGroupContentOptions
 *  
 *  Discussion:
 *    Window group contents options are used to control what group
 *    content is counted or returned by the CountWindowGroupContents
 *    and GetWindowGroupContents APIs.
 */

  /*
   * Indicates that Count/GetWindowGroupContents should return the
   * windows in a group. If this option is not set, these APIs return
   * the groups in a group.
   */
typedef UInt32 WindowGroupContentOptions;
enum {
  kWindowGroupContentsReturnWindows = 1 << 0,

  /*
   * Indicates that Count/GetWindowGroupContents should include the
   * contents of groups contained by the specified group. If this
   * option is not set, these APIs only return information about the
   * specified group’s contents.
   */
  kWindowGroupContentsRecurse   = 1 << 1,

  /*
   * Indicates that Count/GetWindowGroupContents should only include
   * visible windows. Only valid when kWindowGroupContentsReturnWindows
   * is specified.
   */
  kWindowGroupContentsVisible   = 1 << 2
};


/*----------------------------------------------------------------------------------*/
/*  • Group creation, destruction, and refcounting                                  */
/*----------------------------------------------------------------------------------*/
/*
 *  CreateWindowGroup()
 *  
 *  Summary:
 *    Creates a new window group.
 *  
 *  Parameters:
 *    
 *    inAttributes:
 *      Attributes for the new window group.
 *    
 *    outGroup:
 *      On exit, contains the new window group.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateWindowGroup(
  WindowGroupAttributes   inAttributes,
  WindowGroupRef *        outGroup);


/*
 *  RetainWindowGroup()
 *  
 *  Summary:
 *    Increments the refcount of a window group.
 *  
 *  Parameters:
 *    
 *    inGroup:
 *      The group whose refcount to increment.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
RetainWindowGroup(WindowGroupRef inGroup);


/*
 *  ReleaseWindowGroup()
 *  
 *  Summary:
 *    Releases a refcount on a window group. If the refcount goes to
 *    zero, the group is destroyed, and a refcount is released from all
 *    contained objects.
 *  
 *  Parameters:
 *    
 *    inGroup:
 *      The group whose refcount to decrement.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ReleaseWindowGroup(WindowGroupRef inGroup);


/*
 *  GetWindowGroupRetainCount()
 *  
 *  Summary:
 *    Returns the refcount of a window group.
 *  
 *  Parameters:
 *    
 *    inGroup:
 *      The group whose refcount to return.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   not available
 */
extern ItemCount 
GetWindowGroupRetainCount(WindowGroupRef inGroup);


/*
 *  GetWindowGroupOfClass()
 *  
 *  Summary:
 *    Gets the window group in which windows of a given class are
 *    placed.
 *  
 *  Discussion:
 *    The Window Manager uses window groups internally to manage the
 *    ordering of windows of different classes. In some cases, multiple
 *    classes are placed within the same group; for example, windows
 *    from all of the modal and alert window classes are placed into
 *    the same modal window group. The refcount of the group returned
 *    by this API is not incremented, and the caller does not need to
 *    release the reference.
 *  
 *  Parameters:
 *    
 *    windowClass:
 *      The class whose window group to retrieve. You may pass
 *      kAllWindowClasses to retrieve the root window group.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   not available
 */
extern WindowGroupRef 
GetWindowGroupOfClass(WindowClass windowClass);



/*----------------------------------------------------------------------------------*/
/*  • Group name, attributes, and level                                             */
/*----------------------------------------------------------------------------------*/
/*
 *  SetWindowGroupName()
 *  
 *  Summary:
 *    Sets the name of a window group.
 *  
 *  Discussion:
 *    The name of a window group is never displayed to the user.
 *    However, it is displayed by debugging functions such as
 *    DebugPrintWindowGroup. This can be very useful when debugging the
 *    structure of your window groups.
 *  
 *  Parameters:
 *    
 *    inGroup:
 *      The group whose name to set.
 *    
 *    inName:
 *      The name of the group.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetWindowGroupName(
  WindowGroupRef   inGroup,
  CFStringRef      inName);


/*
 *  CopyWindowGroupName()
 *  
 *  Summary:
 *    Returns a copy of the name of a window group.
 *  
 *  Parameters:
 *    
 *    inGroup:
 *      The group whose name to retrieve.
 *    
 *    outName:
 *      On exit, contains the name of the group. It is the caller's
 *      responsibility to release the name.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CopyWindowGroupName(
  WindowGroupRef   inGroup,
  CFStringRef *    outName);


/*
 *  GetWindowGroupAttributes()
 *  
 *  Summary:
 *    Retrieves the attributes of a window group.
 *  
 *  Parameters:
 *    
 *    inGroup:
 *      The group whose attributes to retrieve.
 *    
 *    outAttributes:
 *      On exit, the group’s attributes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetWindowGroupAttributes(
  WindowGroupRef           inGroup,
  WindowGroupAttributes *  outAttributes);


/*
 *  ChangeWindowGroupAttributes()
 *  
 *  Summary:
 *    Changes the attributes of a window group.
 *  
 *  Parameters:
 *    
 *    inGroup:
 *      The group whose attributes to change.
 *    
 *    setTheseAttributes:
 *      The attributes to set.
 *    
 *    clearTheseAttributes:
 *      The attributes to clear.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ChangeWindowGroupAttributes(
  WindowGroupRef          inGroup,
  WindowGroupAttributes   setTheseAttributes,
  WindowGroupAttributes   clearTheseAttributes);


/*
 *  SetWindowGroupLevel()
 *  
 *  Summary:
 *    Sets the CoreGraphics window group level of windows in a group.
 *  
 *  Discussion:
 *    CoreGraphics windows (used to implement all windows in Carbon and
 *    Cocoa applications on Mac OS X) are divided into layers specified
 *    by a window level. Standard window levels are listed in
 *    <CoreGraphics/CGWindowLevel.h>. By default, a new window group
 *    has a window level of kCGNormalWindowLevel. When a window is
 *    placed into a window group, its window level is determined by the
 *    window level of its "base group". This is the containing group
 *    that is a child of the root group. For example, if group A is a
 *    child of the root group, and group B is a child of group A, and
 *    window C is in group B, then window C's base group is group A,
 *    and group A's window level determines the level of window C.
 *    SetWindowGroupLevel only allows changing the window level of
 *    groups that are children of the root group. It returns paramErr
 *    for other groups, since a group that is not a child of the root
 *    group is not a base group and changing its level has no effect.
 *    Changing the level of a group also changes the level of all
 *    windows currently contained by the group.
 *  
 *  Parameters:
 *    
 *    inGroup:
 *      The window group whose level to change.
 *    
 *    inLevel:
 *      The new level for the windows in this group.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetWindowGroupLevel(
  WindowGroupRef   inGroup,
  SInt32           inLevel);


/*
 *  GetWindowGroupLevel()
 *  
 *  Summary:
 *    Gets the CoreGraphics window group level of windows in a group.
 *  
 *  Parameters:
 *    
 *    inGroup:
 *      The window group whose level to return.
 *    
 *    outLevel:
 *      On exit, contains the window level of the windows in this group.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetWindowGroupLevel(
  WindowGroupRef   inGroup,
  SInt32 *         outLevel);



/*----------------------------------------------------------------------------------*/
/*  • Group z-ordering                                                              */
/*----------------------------------------------------------------------------------*/
/*
 *  SendWindowGroupBehind()
 *  
 *  Summary:
 *    Changes the z-order of a group, if the group does not have the
 *    kWindowGroupAttributeLayerTogether attribute set.
 *  
 *  Discussion:
 *    SendWindowGroupBehind currently requires that the group being
 *    moved and the behindGroup have the same parent group.
 *  
 *  Parameters:
 *    
 *    inGroup:
 *      The group whose z-order to change.
 *    
 *    behindGroup:
 *      The group behind which to position the specified group.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SendWindowGroupBehind(
  WindowGroupRef   inGroup,
  WindowGroupRef   behindGroup);


/*----------------------------------------------------------------------------------*/
/*  • Group containment hierarchy manipulation                                      */
/*----------------------------------------------------------------------------------*/
/*
 *  GetWindowGroup()
 *  
 *  Summary:
 *    Gets the window group that contains a window.
 *  
 *  Discussion:
 *    The refcount of the group returned by this API is not
 *    incremented, and the caller does not need to release the
 *    reference.
 *  
 *  Parameters:
 *    
 *    inWindow:
 *      The window whose containing group to retrieve.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   not available
 */
extern WindowGroupRef 
GetWindowGroup(WindowRef inWindow);


/*
 *  SetWindowGroup()
 *  
 *  Summary:
 *    Sets the window group that contains a window.
 *  
 *  Discussion:
 *    The window’s z-order relative to windows in the current process
 *    may also be changed by this API. If the new window group is
 *    z-ordered above the window’s current group, the window will be
 *    placed at the end of the new group. If the new window group is
 *    z-ordered below the window’s current group, the window will be
 *    placed at the top of the new group. You may not place a window
 *    directly into the root group.
 *  
 *  Parameters:
 *    
 *    inWindow:
 *      The window whose group to change.
 *    
 *    inNewGroup:
 *      The new containing group.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetWindowGroup(
  WindowRef        inWindow,
  WindowGroupRef   inNewGroup);


/*
 *  IsWindowContainedInGroup()
 *  
 *  Summary:
 *    Indicates whether a window is contained within a group or any of
 *    its subgroups.
 *  
 *  Parameters:
 *    
 *    inWindow:
 *      The window whose containment to examine.
 *    
 *    inGroup:
 *      The group that might contain the window.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
IsWindowContainedInGroup(
  WindowRef        inWindow,
  WindowGroupRef   inGroup);


/*
 *  GetWindowGroupParent()
 *  
 *  Summary:
 *    Gets the window group that contains a group.
 *  
 *  Parameters:
 *    
 *    inGroup:
 *      The group whose containing group to retrieve.
 *    
 *    outGroup:
 *      On exit, the containing window group of the group. The group’s
 *      refcount is not incremented by this API, and the caller does
 *      not need to release the reference.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern WindowGroupRef 
GetWindowGroupParent(WindowGroupRef inGroup);


/*
 *  SetWindowGroupParent()
 *  
 *  Summary:
 *    Sets the window group that contains a group.
 *  
 *  Discussion:
 *    SetWindowGroupParent currently requires that the group have no
 *    windows in it.
 *  
 *  Parameters:
 *    
 *    inGroup:
 *      The group whose containing group to change.
 *    
 *    inNewGroup:
 *      The new containing group.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetWindowGroupParent(
  WindowGroupRef   inGroup,
  WindowGroupRef   inNewGroup);


/*
 *  GetWindowGroupSibling()
 *  
 *  Summary:
 *    Returns the next or previous group of a window group.
 *  
 *  Parameters:
 *    
 *    inGroup:
 *      The group whose sibling to return.
 *    
 *    inNextGroup:
 *      True to return the next sibling, false to return the previous
 *      sibling.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern WindowGroupRef 
GetWindowGroupSibling(
  WindowGroupRef   inGroup,
  Boolean          inNextGroup);


/*
 *  GetWindowGroupOwner()
 *  
 *  Summary:
 *    Returns the window that owns a window group, or NULL if none.
 *  
 *  Discussion:
 *    A window may own one or more window groups. The windows in an
 *    owned window group will always be z-ordered above the owner
 *    window. Whenever the owner window changes z-order, the windows in
 *    the groups owned by the window will be moved also.
 *  
 *  Parameters:
 *    
 *    inGroup:
 *      The group whose owner to retrieve.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern WindowRef 
GetWindowGroupOwner(WindowGroupRef inGroup);


/*
 *  SetWindowGroupOwner()
 *  
 *  Summary:
 *    Sets the window that owns a window group.
 *  
 *  Discussion:
 *    The group and the window must have the same parent group.
 *    SetWindowGroupOwner currently requires that the group have no
 *    windows in it.
 *  
 *  Parameters:
 *    
 *    inGroup:
 *      The group whose owner to set.
 *    
 *    inWindow:
 *      The group's new owner.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetWindowGroupOwner(
  WindowGroupRef   inGroup,
  WindowRef        inWindow);



/*----------------------------------------------------------------------------------*/
/*  • Inspection of group contents                                                  */
/*----------------------------------------------------------------------------------*/

/*
 *  CountWindowGroupContents()
 *  
 *  Summary:
 *    Counts the windows or groups contained in a group.
 *  
 *  Parameters:
 *    
 *    inGroup:
 *      The group whose contents to count.
 *    
 *    inOptions:
 *      Specifies how to count the group’s contents.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   not available
 */
extern ItemCount 
CountWindowGroupContents(
  WindowGroupRef              inGroup,
  WindowGroupContentOptions   inOptions);


/*
 *  GetWindowGroupContents()
 *  
 *  Summary:
 *    Retrieves the windows or groups contained in a group.
 *  
 *  Discussion:
 *    The windows or groups returned by this API will be placed into
 *    the output buffer in z-order, from highest to lowest.
 *  
 *  Parameters:
 *    
 *    inGroup:
 *      The group whose contents to retrieve.
 *    
 *    inOptions:
 *      Specifies which content to retrieve.
 *    
 *    inAllowedItems:
 *      The number of items that will fit in the output buffer.
 *    
 *    outNumItems:
 *      On exit, the number of items that were returned. May be NULL.
 *    
 *    outItems:
 *      On entry, points to enough memory to hold inAllowedSize
 *      WindowRefs or WindowGroupRefs. On exit, contains *outNumItems
 *      WindowRefs or WindowGroupRefs.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetWindowGroupContents(
  WindowGroupRef              inGroup,
  WindowGroupContentOptions   inOptions,
  ItemCount                   inAllowedItems,
  ItemCount *                 outNumItems,          /* can be NULL */
  void **                     outItems);


/*
 *  GetIndexedWindow()
 *  
 *  Summary:
 *    Retrieves a specified window from a group.
 *  
 *  Discussion:
 *    GetIndexedWindow is provided as an easier way to get a particular
 *    window from a group than using GetWindowGroupContents. If you
 *    only need to retrieve, say, the last window in a group, it is
 *    easier and more efficient to use GetIndexedWindow. If you need to
 *    retrieve all the windows in a group, it is more efficient to use
 *    GetWindowGroupContents.
 *  
 *  Parameters:
 *    
 *    inGroup:
 *      The group containing the window to retrieve.
 *    
 *    inIndex:
 *      The index of the window. This parameter may range from 1 to
 *      CountWindowGroupContents( inGroup,
 *      kWindowGroupContentsReturnWindows | inOptions );
 *    
 *    inOptions:
 *      Indicates how to locate the specified window.
 *      kWindowGroupContentsReturnWindows is implied by this API and
 *      does not need to be explicitly specified.
 *    
 *    outWindow:
 *      On exit, the window at the specified index.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetIndexedWindow(
  WindowGroupRef              inGroup,
  UInt32                      inIndex,
  WindowGroupContentOptions   inOptions,
  WindowRef *                 outWindow);


/*
 *  GetWindowIndex()
 *  
 *  Summary:
 *    Retrieves the z-order index of a window inside a group.
 *  
 *  Discussion:
 *    The z-order index of a window is its relative position in z-order
 *    inside a group. The index ranges from 1 to the number of windows
 *    in the group.
 *  
 *  Parameters:
 *    
 *    inWindow:
 *      The window whose z-order index to retrieve.
 *    
 *    inStartGroup:
 *      The group on which to base the z-order index. This should be
 *      either the containing group of the window, or NULL. If NULL,
 *      this API returns the z-order index of the window across the
 *      entire process.
 *    
 *    inOptions:
 *      Indicates how to enumerate the specified window.
 *      kWindowGroupContentsReturnWindows is implied by this API and
 *      does not need to be explicitly specified.
 *    
 *    outIndex:
 *      On exit, contains the window’s z-order index.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetWindowIndex(
  WindowRef                   inWindow,
  WindowGroupRef              inStartGroup,
  WindowGroupContentOptions   inOptions,
  UInt32 *                    outIndex);



/*----------------------------------------------------------------------------------*/
/*  • Window activation                                                             */
/*----------------------------------------------------------------------------------*/
/*
 *  ActiveNonFloatingWindow()
 *  
 *  Summary:
 *    Returns the window, among all windows with activation scope of
 *    kWindowActivationScopeAll, that is considered active.
 *  
 *  Discussion:
 *    The Mac OS 8.5 Window Manager introduced the
 *    FrontNonFloatingWindow API, which was designed to return the
 *    window that should be considered active by the application. With
 *    the advent of window groups, it is now possible to have a window
 *    that looks active (is highlighted, and accepts keyboard input)
 *    but to have other non-floating windows grouped above the active
 *    window. The ActiveNonFloatingWindow API returns the active window
 *    regardless of where it is positioned in the z-order. Most code
 *    that currently uses FrontNonFloatingWindow or
 *    GetFrontWindowOfClass(kDocumentClass) to get the active window
 *    should use ActiveNonFloatingWindow instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   not available
 */
extern WindowRef 
ActiveNonFloatingWindow(void);


/*
 *  IsWindowActive()
 *  
 *  Summary:
 *    Indicates whether a window is active.
 *  
 *  Discussion:
 *    The active state of a window is simply determined by whether its
 *    window frame is drawn using an active appearance. This does not
 *    indicate whether the window has keyboard focus. To get the window
 *    with keyboard focus, use GetUserFocusWindow().
 *  
 *  Parameters:
 *    
 *    inWindow:
 *      The window whose active state to retrieve.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
IsWindowActive(WindowRef inWindow);


/*
 *  ActivateWindow()
 *  
 *  Summary:
 *    Activates or deactivates a window.
 *  
 *  Discussion:
 *    Window activation consists of two steps: hiliting the window
 *    frame and sending an activate event to the window. ActivateWindow
 *    handles both of these steps and also updates internal Window
 *    Manager state. If you just need to hilite the window frame, you
 *    may use HiliteWindow. If you need to send an activate event, you
 *    should always use ActivateWindow rather than creating and sending
 *    the event yourself.
 *  
 *  Parameters:
 *    
 *    inWindow:
 *      The window to activate or deactivate.
 *    
 *    inActivate:
 *      Whether to activate or deactivate the window.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ActivateWindow(
  WindowRef   inWindow,
  Boolean     inActivate);


/*
 *  GetWindowActivationScope()
 *  
 *  Summary:
 *    Retrieves a window’s activation scope.
 *  
 *  Parameters:
 *    
 *    inWindow:
 *      The window whose activation scope to retrieve.
 *    
 *    outScope:
 *      On exit, the window’s activation scope.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetWindowActivationScope(
  WindowRef                inWindow,
  WindowActivationScope *  outScope);


/*
 *  SetWindowActivationScope()
 *  
 *  Summary:
 *    Sets a window’s activation scope.
 *  
 *  Parameters:
 *    
 *    inWindow:
 *      The window whose activation scope to set.
 *    
 *    inScope:
 *      The new activation scope.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetWindowActivationScope(
  WindowRef               inWindow,
  WindowActivationScope   inScope);



/*----------------------------------------------------------------------------------*/
/*  • Debugging Utilities                                                           */
/*----------------------------------------------------------------------------------*/
/*
 *  DebugPrintWindowGroup()
 *  
 *  Summary:
 *    Prints the contents of a window group to stdout.
 *  
 *  Parameters:
 *    
 *    inGroup:
 *      The group whose contents to print.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
DebugPrintWindowGroup(WindowGroupRef inGroup);


/*
 *  DebugPrintAllWindowGroups()
 *  
 *  Summary:
 *    Prints the full window group hierarchy, starting at the root
 *    group.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
DebugPrintAllWindowGroups(void);




/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Background Image                                                                   */
/*——————————————————————————————————————————————————————————————————————————————————————*/
/* SetWinColor is not available in Carbon.*/
/*
 *  SetWinColor()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/* SetDeskCPat is not available in Carbon.*/
/*
 *  SetDeskCPat()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
   Routines available from Mac OS 8.5 forward
   or from Mac OS 8.1 forward when linking to CarbonLib 1.0 forward
*/
/*
 *  SetWindowContentColor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
SetWindowContentColor(
  WindowRef         window,
  const RGBColor *  color);


/*
 *  GetWindowContentColor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
GetWindowContentColor(
  WindowRef   window,
  RGBColor *  color);


/* Routines available from Mac OS 8.5 forward*/
/*
 *  GetWindowContentPattern()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
GetWindowContentPattern(
  WindowRef      window,
  PixPatHandle   outPixPat);


/*
 *  SetWindowContentPattern()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
SetWindowContentPattern(
  WindowRef      window,
  PixPatHandle   pixPat);


/* Routines available from Mac OS 9.0 forward*/
typedef OptionBits                      WindowPaintProcOptions;
enum {
  kWindowPaintProcOptionsNone   = 0
};

/*
 *  InstallWindowContentPaintProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 9.0 and later
 */
extern OSStatus 
InstallWindowContentPaintProc(
  WindowRef                window,
  WindowPaintUPP           paintProc,
  WindowPaintProcOptions   options,
  void *                   refCon);         /* can be NULL */


/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Scrolling Routines                                                                 */
/*——————————————————————————————————————————————————————————————————————————————————————*/
typedef UInt32 ScrollWindowOptions;
enum {
  kScrollWindowNoOptions        = 0,
  kScrollWindowInvalidate       = (1L << 0), /* add the exposed area to the window’s update region*/
  kScrollWindowEraseToPortBackground = (1L << 1) /* erase the exposed area using the background color/pattern of the window’s grafport*/
};


/* Routines available from Mac OS 8.1 forward when linking to CarbonLib 1.0 forward*/

/*
 *  ScrollWindowRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ScrollWindowRect(
  WindowRef             inWindow,
  const Rect *          inScrollRect,
  SInt16                inHPixels,
  SInt16                inVPixels,
  ScrollWindowOptions   inOptions,
  RgnHandle             outExposedRgn);      /* can be NULL */


/*
 *  ScrollWindowRegion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ScrollWindowRegion(
  WindowRef             inWindow,
  RgnHandle             inScrollRgn,
  SInt16                inHPixels,
  SInt16                inVPixels,
  ScrollWindowOptions   inOptions,
  RgnHandle             outExposedRgn);      /* can be NULL */




/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Low-Level Region & Painting Routines                                               */
/*——————————————————————————————————————————————————————————————————————————————————————*/
/*
 *  ClipAbove()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ClipAbove(WindowRef window);


/* SaveOld/DrawNew are not available in Carbon.  Use ReshapeCustomWindow instead.*/
/*
 *  SaveOld()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  DrawNew()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PaintOne()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PaintOne(
  WindowRef   window,             /* can be NULL */
  RgnHandle   clobberedRgn);


/*
 *  PaintBehind()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PaintBehind(
  WindowRef   startWindow,        /* can be NULL */
  RgnHandle   clobberedRgn);


/*
 *  CalcVis()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
CalcVis(WindowRef window);


/*
 *  CalcVisBehind()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
CalcVisBehind(
  WindowRef   startWindow,        /* can be NULL */
  RgnHandle   clobberedRgn);


/*
 *  CheckUpdate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
CheckUpdate(EventRecord * theEvent);



/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Window List                                                                        */
/*——————————————————————————————————————————————————————————————————————————————————————*/
/*
 *  [Mac]FindWindow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacFindWindow FindWindow
#endif
extern WindowPartCode 
MacFindWindow(
  Point        thePoint,
  WindowRef *  window);


/*
 *  FrontWindow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern WindowRef 
FrontWindow(void);


/*
 *  BringToFront()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
BringToFront(WindowRef window);


/*
 *  SendBehind()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SendBehind(
  WindowRef   window,
  WindowRef   behindWindow);


/*
 *  SelectWindow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SelectWindow(WindowRef window);


/*
   Routines available from Mac OS 8.6 forward
   or from Mac OS 8.1 forward when linking to CarbonLib 1.0 forward
*/

/*
 *  FrontNonFloatingWindow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern WindowRef 
FrontNonFloatingWindow(void);


/* Routines available from Mac OS 8.1 forward when linking to CarbonLib 1.0 forward*/

/*
 *  GetNextWindowOfClass()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern WindowRef 
GetNextWindowOfClass(
  WindowRef     inWindow,
  WindowClass   inWindowClass,
  Boolean       mustBeVisible);


/*
 *  GetFrontWindowOfClass()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern WindowRef 
GetFrontWindowOfClass(
  WindowClass   inWindowClass,
  Boolean       mustBeVisible);


/*
 *  FindWindowOfClass()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
FindWindowOfClass(
  const Point *     where,
  WindowClass       inWindowClass,
  WindowRef *       outWindow,
  WindowPartCode *  outWindowPart);      /* can be NULL */



/* Carbon only*/
/*
 *  CreateStandardWindowMenu()
 *  
 *  Discussion:
 *    Creates a standard Window menu for your application. You can call
 *    this to create a window menu for your application and insert it
 *    in your menu bar (typically at the end of your menu list). To
 *    register a window to be tracked by this menu, you either create
 *    your window with CreateNewWindow, passing the
 *    kWindowInWindowMenuAttribute, or you can use
 *    ChangeWindowAttributes after the window is created. The Toolbox
 *    takes care of acting on the standard items such as zoom and
 *    minimize, as well as bringing selected windows to the front. All
 *    you need to do is install it and register your windows and the
 *    Toolbox does the rest.
 *  
 *  Parameters:
 *    
 *    inOptions:
 *      Currently you must pass zero for this parameter.
 *    
 *    outMenu:
 *      Receives a new menu reference which contains the standard
 *      window menu items and commands.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateStandardWindowMenu(
  OptionBits   inOptions,
  MenuRef *    outMenu);


/*
 *  SetWindowAlternateTitle()
 *  
 *  Discussion:
 *    This API sets an alternate title for a window. The alternate
 *    title overrides what is displayed in the Window menu. If you do
 *    not set an alternate title, the normal window title is used. You
 *    would normally use this if the window title was not expressive
 *    enough to be used in the Window menu (or similar text-only
 *    situation).
 *  
 *  Parameters:
 *    
 *    inWindow:
 *      The window to set the alternate title.
 *    
 *    inTitle:
 *      The alternate title for the window. Passing NULL for this
 *      parameter will remove any alternate title that might be present.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetWindowAlternateTitle(
  WindowRef     inWindow,
  CFStringRef   inTitle);


/*
 *  CopyWindowAlternateTitle()
 *  
 *  Discussion:
 *    This API gets the alternate title for a window. See the
 *    discussion of SetWindowAlternateTitle for more info.
 *  
 *  Parameters:
 *    
 *    inWindow:
 *      The window to get the alternate title from.
 *    
 *    outTitle:
 *      Receives the alternate title for the window. If the window does
 *      not have an alternate title, NULL will be returned in outTitle.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CopyWindowAlternateTitle(
  WindowRef      inWindow,
  CFStringRef *  outTitle);


/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Misc Low-Level stuff                                                               */
/*——————————————————————————————————————————————————————————————————————————————————————*/
/*
 *  InitWindows()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*  The window manager port does not exist in Carbon.   */
/*  We are investigating replacement technologies.      */
/*
 *  GetWMgrPort()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  GetCWMgrPort()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
   Routines available from Mac OS 8.5 forward
   or from Mac OS 8.1 forward when linking to CarbonLib 1.0 forward
*/
/*
 *  IsValidWindowPtr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern Boolean 
IsValidWindowPtr(WindowRef possibleWindow);


#define IsValidWindowRef IsValidWindowPtr
/*
   Routines available from Mac OS 8.6 forward
   InitFloatingWindows is not available in Carbon;
   window ordering is always active for Carbon clients
*/
/*
 *  InitFloatingWindows()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */



/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Various & Sundry Window Accessors                                                  */
/*——————————————————————————————————————————————————————————————————————————————————————*/
/*
 *  HiliteWindow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
HiliteWindow(
  WindowRef   window,
  Boolean     fHilite);


/*
 *  SetWRefCon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetWRefCon(
  WindowRef   window,
  long        data);


/*
 *  GetWRefCon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
GetWRefCon(WindowRef window);


/*
 *  SetWindowPic()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetWindowPic(
  WindowRef   window,
  PicHandle   pic);


/*
 *  GetWindowPic()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern PicHandle 
GetWindowPic(WindowRef window);


/*
 *  GetWVariant()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern short 
GetWVariant(WindowRef window);


/* Routines available from Mac OS 8.0 (Appearance 1.0) forward*/
/*
 *  GetWindowFeatures()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSStatus 
GetWindowFeatures(
  WindowRef   window,
  UInt32 *    outFeatures);


/*
 *  GetWindowRegion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSStatus 
GetWindowRegion(
  WindowRef          window,
  WindowRegionCode   inRegionCode,
  RgnHandle          ioWinRgn);


/*
 *  GetWindowStructureWidths()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
GetWindowStructureWidths(
  WindowRef   inWindow,
  Rect *      outRect);



/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Update Events                                                                      */
/*——————————————————————————————————————————————————————————————————————————————————————*/
/*
   These aren't present in Carbon. Please use the InvalWindowRect, etc. routines
   below instead.
*/
/*
 *  InvalRect()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  InvalRgn()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  ValidRect()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  ValidRgn()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  BeginUpdate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
BeginUpdate(WindowRef window);


/*
 *  EndUpdate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
EndUpdate(WindowRef window);


/*
   Routines available from Mac OS 8.5 forward
   or from Mac OS 8.1 forward when linking to CarbonLib 1.0 forward
*/

/*
 *  InvalWindowRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
InvalWindowRgn(
  WindowRef   window,
  RgnHandle   region);


/*
 *  InvalWindowRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
InvalWindowRect(
  WindowRef     window,
  const Rect *  bounds);


/*
 *  ValidWindowRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
ValidWindowRgn(
  WindowRef   window,
  RgnHandle   region);


/*
 *  ValidWindowRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
ValidWindowRect(
  WindowRef     window,
  const Rect *  bounds);



/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • DrawGrowIcon                                                                       */
/*                                                                                      */
/*  DrawGrowIcon is deprecated from Mac OS 8.0 forward.  Theme-savvy window defprocs    */
/*  include the grow box in the window frame.                                           */
/*——————————————————————————————————————————————————————————————————————————————————————*/
/*
 *  DrawGrowIcon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DrawGrowIcon(WindowRef window);


/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Window Titles                                                                      */
/*——————————————————————————————————————————————————————————————————————————————————————*/
/*
 *  SetWTitle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetWTitle(
  WindowRef          window,
  ConstStr255Param   title);


/*
 *  GetWTitle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetWTitle(
  WindowRef   window,
  Str255      title);


/*
 *  SetWindowTitleWithCFString()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetWindowTitleWithCFString(
  WindowRef     inWindow,
  CFStringRef   inString);


/*
 *  CopyWindowTitleAsCFString()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CopyWindowTitleAsCFString(
  WindowRef      inWindow,
  CFStringRef *  outString);



/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Window Proxies                                                                     */
/*——————————————————————————————————————————————————————————————————————————————————————*/
/* Routines available from Mac OS 8.5 forward*/

/*
 *  SetWindowProxyFSSpec()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
SetWindowProxyFSSpec(
  WindowRef       window,
  const FSSpec *  inFile);


/*
 *  GetWindowProxyFSSpec()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
GetWindowProxyFSSpec(
  WindowRef   window,
  FSSpec *    outFile);


/*
 *  SetWindowProxyAlias()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
SetWindowProxyAlias(
  WindowRef     window,
  AliasHandle   alias);


/*
 *  GetWindowProxyAlias()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
GetWindowProxyAlias(
  WindowRef      window,
  AliasHandle *  alias);


/*
 *  SetWindowProxyCreatorAndType()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
SetWindowProxyCreatorAndType(
  WindowRef   window,
  OSType      fileCreator,
  OSType      fileType,
  SInt16      vRefNum);


/*
 *  GetWindowProxyIcon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
GetWindowProxyIcon(
  WindowRef   window,
  IconRef *   outIcon);


/*
 *  SetWindowProxyIcon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
SetWindowProxyIcon(
  WindowRef   window,
  IconRef     icon);


/*
 *  RemoveWindowProxy()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
RemoveWindowProxy(WindowRef window);


/*
 *  BeginWindowProxyDrag()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
BeginWindowProxyDrag(
  WindowRef        window,
  DragReference *  outNewDrag,
  RgnHandle        outDragOutlineRgn);


/*
 *  EndWindowProxyDrag()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
EndWindowProxyDrag(
  WindowRef       window,
  DragReference   theDrag);


/*
 *  TrackWindowProxyFromExistingDrag()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
TrackWindowProxyFromExistingDrag(
  WindowRef       window,
  Point           startPt,
  DragReference   drag,
  RgnHandle       inDragOutlineRgn);


/*
 *  TrackWindowProxyDrag()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
TrackWindowProxyDrag(
  WindowRef   window,
  Point       startPt);


/*
 *  IsWindowModified()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern Boolean 
IsWindowModified(WindowRef window);


/*
 *  SetWindowModified()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
SetWindowModified(
  WindowRef   window,
  Boolean     modified);


/*
 *  IsWindowPathSelectClick()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern Boolean 
IsWindowPathSelectClick(
  WindowRef            window,
  const EventRecord *  event);


/*
 *  WindowPathSelect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
WindowPathSelect(
  WindowRef   window,
  MenuRef     menu,                /* can be NULL */
  SInt32 *    outMenuResult);


/*
 *  IsWindowPathSelectEvent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
IsWindowPathSelectEvent(
  WindowRef   window,
  EventRef    inEvent);



/*——————————————————————————————————————————————————————————————————————————————————————*/
/*  • HiliteWindowFrameForDrag                                                          */
/*                                                                                      */
/*  If you call ShowDragHilite and HideDragHilite, you don’t need to use this routine.  */
/*  If you implement custom drag hiliting, you should call HiliteWindowFrameForDrag     */
/*  when the drag is tracking inside a window with drag-hilited content.                */
/*——————————————————————————————————————————————————————————————————————————————————————*/
/* Routines available from Mac OS 8.5 forward*/

/*
 *  HiliteWindowFrameForDrag()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
HiliteWindowFrameForDrag(
  WindowRef   window,
  Boolean     hilited);



/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Window Transitions                                                                 */
/*                                                                                      */
/*  TransitionWindow displays a window with accompanying animation and sound.           */
/*——————————————————————————————————————————————————————————————————————————————————————*/
typedef UInt32 WindowTransitionEffect;
enum {
  kWindowZoomTransitionEffect   = 1,    /* Finder-like zoom rectangles. Use with Show or Hide transition actions*/
  kWindowSheetTransitionEffect  = 2,    /* Zoom in/out from parent. Use with TransitionWindowAndParent and Show or Hide transition actions*/
  kWindowSlideTransitionEffect  = 3     /* Slide the window into its new position. Use with Move or Resize transition actions*/
};

typedef UInt32 WindowTransitionAction;
enum {
  kWindowShowTransitionAction   = 1,    /* param is rect in global coordinates from which to start the animation*/
  kWindowHideTransitionAction   = 2,    /* param is rect in global coordinates at which to end the animation*/
  kWindowMoveTransitionAction   = 3,    /* param is rect in global coordinates of window's new structure bounds*/
  kWindowResizeTransitionAction = 4     /* param is rect in global coordinates of window's new structure bounds*/
};

/*
 *  TransitionWindow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
TransitionWindow(
  WindowRef                window,
  WindowTransitionEffect   effect,
  WindowTransitionAction   action,
  const Rect *             rect);        /* can be NULL */


/*
 *  TransitionWindowAndParent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
TransitionWindowAndParent(
  WindowRef                window,
  WindowRef                parentWindow,
  WindowTransitionEffect   effect,
  WindowTransitionAction   action,
  const Rect *             rect);              /* can be NULL */



/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Window Positioning                                                                 */
/*——————————————————————————————————————————————————————————————————————————————————————*/

/*
 *  [Mac]MoveWindow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacMoveWindow MoveWindow
#endif
extern void 
MacMoveWindow(
  WindowRef   window,
  short       hGlobal,
  short       vGlobal,
  Boolean     front);


/*
 *  SizeWindow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SizeWindow(
  WindowRef   window,
  short       w,
  short       h,
  Boolean     fUpdate);



/* Note: bBox can only be NULL when linking to CarbonLib 1.0 forward */
/*
 *  GrowWindow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
GrowWindow(
  WindowRef     window,
  Point         startPt,
  const Rect *  bBox);         /* can be NULL */


/* Note: boundsRect can only be NULL when linking to CarbonLib 1.0 forward */
/*
 *  DragWindow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DragWindow(
  WindowRef     window,
  Point         startPt,
  const Rect *  boundsRect);      /* can be NULL */


/*
 *  ZoomWindow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ZoomWindow(
  WindowRef        window,
  WindowPartCode   partCode,
  Boolean          front);


/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Window Collapsing/Expanding                                                        */
/*——————————————————————————————————————————————————————————————————————————————————————*/
/* Routines available from Mac OS 8.0 (Appearance 1.0) forward*/
/*
 *  IsWindowCollapsable()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern Boolean 
IsWindowCollapsable(WindowRef window);


/*
 *  IsWindowCollapsed()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern Boolean 
IsWindowCollapsed(WindowRef window);


/*
 *  CollapseWindow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSStatus 
CollapseWindow(
  WindowRef   window,
  Boolean     collapse);


/*
 *  CollapseAllWindows()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSStatus 
CollapseAllWindows(Boolean collapse);


/* Routines available on Mac OS X*/

/*
 *  CreateQDContextForCollapsedWindowDockTile()
 *  
 *  Discussion:
 *    Creates and returns a CGrafPtr for a collapsed window's tile in
 *    the dock. You can use this port to draw into your window's dock
 *    tile with Quickdraw. You **MUST** call
 *    ReleaseQDContextForCollapsedWindowDockTile and NOT DisposePort
 *    when using this API, as it maintains more state than just the
 *    port. If you call DisposePort, you may leak system resources.
 *  
 *  Parameters:
 *    
 *    inWindow:
 *      The window to create the dock tile port for. If this window is
 *      not collapsed, an error is returned.
 *    
 *    outContext:
 *      The Quickdraw port for you to use to draw into. If you wish to
 *      use CoreGraphics (Quartz) drawing, call CreateCGContextForPort
 *      with this port to obtain a CGContext.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateQDContextForCollapsedWindowDockTile(
  WindowRef   inWindow,
  CGrafPtr *  outContext);


/*
 *  ReleaseQDContextForCollapsedWindowDockTile()
 *  
 *  Discussion:
 *    Releases a port and other state created by the
 *    CreateQDContextForCollapsedWindowDockTile API. You MUST call this
 *    instead of DisposePort directly, or you may leak system resources.
 *  
 *  Parameters:
 *    
 *    inWindow:
 *      The window you created the port for. If this window is not
 *      collapsed, an error is returned.
 *    
 *    inContext:
 *      The Quickdraw context to dispose.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ReleaseQDContextForCollapsedWindowDockTile(
  WindowRef   inWindow,
  CGrafPtr    inContext);


/*
 *  UpdateCollapsedWindowDockTile()
 *  
 *  Discussion:
 *    Automatically updates the image of a particular window in the
 *    dock to the current contents of the window. Use this for periodic
 *    updates, etc. Do not use this for animation purposes, if you want
 *    animation, use the above create/release drawing context APIs.
 *  
 *  Parameters:
 *    
 *    inWindow:
 *      The window to update the dock tile for. If this window is not
 *      collapsed, an error is returned.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
UpdateCollapsedWindowDockTile(WindowRef inWindow);



/*
   Routines available from Mac OS 8.5 forward
   or from Mac OS 8.1 forward when linking to CarbonLib 1.0 forward
*/

/*
 *  GetWindowBounds()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
GetWindowBounds(
  WindowRef          window,
  WindowRegionCode   regionCode,
  Rect *             globalBounds);


/* Note: newContentRect can only be NULL when linking to CarbonLib 1.0 forward */
/*
 *  ResizeWindow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern Boolean 
ResizeWindow(
  WindowRef     window,
  Point         startPoint,
  const Rect *  sizeConstraints,       /* can be NULL */
  Rect *        newContentRect);       /* can be NULL */



/*
   Routines available from Mac OS 8.5 forward,
   or from Mac OS 8.1 forward when linking to CarbonLib 1.0.2 forward
*/

/*
 *  SetWindowBounds()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
SetWindowBounds(
  WindowRef          window,
  WindowRegionCode   regionCode,
  const Rect *       globalBounds);


/* Routines available from Mac OS 8.5 forward*/

/*
 *  RepositionWindow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
RepositionWindow(
  WindowRef              window,
  WindowRef              parentWindow,
  WindowPositionMethod   method);


/*
 *  MoveWindowStructure()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
MoveWindowStructure(
  WindowRef   window,
  short       hGlobal,
  short       vGlobal);


/*
   Routines available from Mac OS 8.5 forward,
   or from Mac OS 8.6 forward when linking to CarbonLib 1.1 forward
*/

/*
 *  IsWindowInStandardState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern Boolean 
IsWindowInStandardState(
  WindowRef   window,
  Point *     idealSize,                /* can be NULL */
  Rect *      idealStandardState);      /* can be NULL */


/*
 *  ZoomWindowIdeal()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
ZoomWindowIdeal(
  WindowRef        window,
  WindowPartCode   partCode,
  Point *          ioIdealSize);


/*
 *  GetWindowIdealUserState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
GetWindowIdealUserState(
  WindowRef   window,
  Rect *      userState);


/*
 *  SetWindowIdealUserState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
SetWindowIdealUserState(
  WindowRef     window,
  const Rect *  userState);


/* Routines available in CarbonLib 1.1 and later*/

/*
 *  GetWindowGreatestAreaDevice()
 *  
 *  Summary:
 *    Returns the graphics device with the greatest area of
 *    intersection with a specified window region.
 *  
 *  Parameters:
 *    
 *    inWindow:
 *      The window to compare against.
 *    
 *    inRegion:
 *      The window region to compare against.
 *    
 *    outGreatestDevice:
 *      On exit, the graphics device with the greatest intersection.
 *      May be NULL.
 *    
 *    outGreatestDeviceRect:
 *      On exit, the bounds of the graphics device with the greatest
 *      intersection. May be NULL. If the device with the greatest
 *      intersection also contains the menu bar, the device rect will
 *      exclude the menu bar area.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetWindowGreatestAreaDevice(
  WindowRef          inWindow,
  WindowRegionCode   inRegion,
  GDHandle *         outGreatestDevice,           /* can be NULL */
  Rect *             outGreatestDeviceRect);      /* can be NULL */



/*
 *  WindowConstrainOptions
 *  
 */

  /*
   * The window may be resized if necessary to make it fit onscreen.
   */
typedef UInt32 WindowConstrainOptions;
enum {
  kWindowConstrainMayResize     = (1L << 0),

  /*
   * The window will be moved even if it doesn't fit entirely onscreen.
   */
  kWindowConstrainMoveRegardlessOfFit = (1L << 1),

  /*
   * Allow partial intersection of the specified window region with the
   * screen, instead of requiring total intersection.
   */
  kWindowConstrainAllowPartial  = (1L << 2),

  /*
   * Only calculate the new window bounds; don't actually move the
   * window.
   */
  kWindowConstrainCalcOnly      = (1L << 3),

  /*
   * The most common options: don't resize the window, move the window
   * regardless of fit to the screen, require total intersection of the
   * specified window region with the screen, and do actually move the
   * window.
   */
  kWindowConstrainStandardOptions = kWindowConstrainMoveRegardlessOfFit
};

/*
 *  ConstrainWindowToScreen()
 *  
 *  Summary:
 *    Moves and resizes a window so that it's contained entirely on a
 *    single screen.
 *  
 *  Parameters:
 *    
 *    inWindowRef:
 *      The window to constrain.
 *    
 *    inRegionCode:
 *      The window region to constrain.
 *    
 *    inOptions:
 *      Flags controlling how the window is constrained.
 *    
 *    inScreenRect:
 *      A rectangle, in global coordinates, in which to constrain the
 *      window. May be NULL. If NULL, the window is constrained to the
 *      screen with the greatest intersection with the specified window
 *      region.
 *    
 *    outStructure:
 *      On exit, contains the new structure bounds of the window, in
 *      global coordinates. May be NULL.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ConstrainWindowToScreen(
  WindowRef                inWindowRef,
  WindowRegionCode         inRegionCode,
  WindowConstrainOptions   inOptions,
  const Rect *             inScreenRect,       /* can be NULL */
  Rect *                   outStructure);      /* can be NULL */


/*
 *  GetAvailableWindowPositioningBounds()
 *  
 *  Summary:
 *    Returns the available window positioning bounds on the given
 *    screen (i.e., the screen rect minus the MenuBar and Dock if
 *    located on that screen).
 *  
 *  Parameters:
 *    
 *    inDevice:
 *      The device for which to find the available bounds.
 *    
 *    availableRect:
 *      On exit, contains the available bounds for the given device.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetAvailableWindowPositioningBounds(
  GDHandle   inDevice,
  Rect *     availableRect);


/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Window Visibility                                                                  */
/*——————————————————————————————————————————————————————————————————————————————————————*/
/*
 *  HideWindow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
HideWindow(WindowRef window);


/*
 *  [Mac]ShowWindow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacShowWindow ShowWindow
#endif
extern void 
MacShowWindow(WindowRef window);


/*
 *  ShowHide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ShowHide(
  WindowRef   window,
  Boolean     showFlag);



/*
 *  [Mac]IsWindowVisible()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later or as macro/inline
 */
#if TARGET_OS_MAC
    #define MacIsWindowVisible IsWindowVisible
#endif
extern Boolean 
MacIsWindowVisible(WindowRef window);


/*
  ——————————————————————————————————————————————————————————————————————————————————————
    • Latent window visibility
  ——————————————————————————————————————————————————————————————————————————————————————
*/


/*
 *  WindowLatentVisibility
 *  
 *  Summary:
 *    Reasons why a window is currently invisible when ordinarily it
 *    would be visible.
 */

  /*
   * Window is a floater and floating windows are hidden
   */
typedef UInt32 WindowLatentVisibility;
enum {
  kWindowLatentVisibleFloater   = 1 << 0,

  /*
   * Window has HideOnSuspend and we are suspended
   */
  kWindowLatentVisibleSuspend   = 1 << 1,

  /*
   * Window has HideOnFullScreen and we are full-screen
   */
  kWindowLatentVisibleFullScreen = 1 << 2,

  /*
   * Window's process is hidden
   */
  kWindowLatentVisibleAppHidden = 1 << 3,

  /*
   * Window is in an owned group and the owner was collapsed
   */
  kWindowLatentVisibleCollapsedOwner = 1 << 4,

  /*
   * Window is in a HideOnCollapse group and another window in the
   * group was collapsed
   */
  kWindowLatentVisibleCollapsedGroup = 1 << 5
};

/*
 *  IsWindowLatentVisible()
 *  
 *  Summary:
 *    Indicates whether a window is visible onscreen and also whether
 *    it is latently visible but not currently onscreen.
 *  
 *  Discussion:
 *    All windows are either onscreen or offscreen. A window that is
 *    offscreen may still be latently visible; this occurs, for
 *    example, when a floating window is hidden as an application is
 *    suspended. The floating window is not visible onscreen, but it is
 *    latently visible and is only hidden due to the suspended state of
 *    the application; when the application becomes active again, the
 *    floating window will be placed back onscreen.
 *    IsWindowLatentVisible may be used to determine both the window's
 *    onscreen/offscreen status and its latent visibility (if the
 *    window is offscreen).
 *  
 *  Parameters:
 *    
 *    inWindow:
 *      The window whose visibility to return.
 *    
 *    outLatentVisible:
 *      If the window is onscreen, the latent visibility is zero. If
 *      the window is offscreen, this parameter is used to return the
 *      latent visibility flags of the window. If any of the flags are
 *      set, then the window is latently visible.
 *  
 *  Result:
 *    Indicates whether the window is currently onscreen.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
IsWindowLatentVisible(
  WindowRef                 inWindow,
  WindowLatentVisibility *  outLatentVisible);      /* can be NULL */



/*——————————————————————————————————————————————————————————————————————————————————————*/
/*
    • Sheets
    
    Sheets are a new user interface object in Mac OS X. A sheet is a modal alert or dialog,
    but unlike a traditional alert or dialog window (which is visually separate from the
    frontmost document window), a sheet appears to be attached to its parent window; it
    moves and z-orders simultaneously with its parent. Furthermore, sheets on Mac OS X
    use a new type of modality called window modality. A traditional alert or dialog is
    app-modal; it prevents user interaction with all other windows in the current application.
    A sheet is window-modal; it only prevents user interaction with its parent window, and
    events continue to flow to other windows in the application.
    
    • Sheet Event Handling
    
    Implementing a sheet window in your application generally requires some modifications
    to your event-handling code. A traditional app-modal window is implemented using a modal
    event loop; your application starts a new event loop (either by processing events itself,
    or by calling ModalDialog), which does not return back to your application's main event
    loop until the app-modal window has closed.
    
    Starting a new event loop doesn't work with sheets, because typically the modal event loop
    will only handle events destined for the sheet, and not events for other windows, but
    a sheet only blocks events for its parent window, and your application must still handle
    events for the rest of its windows as normal. Therefore, you will usually not use a modal
    event loop to handle events in a sheet. Rather, you will show the sheet window, and then
    return directly back to your main event loop. The Carbon Event Manager automatically 
    prevents events in the sheet's parent window from reaching it; events in your application's
    other windows are still returned to you via WaitNextEvent or your application's Carbon
    event handlers, where you can process them as normal.
    
    You have several choices for handling events in the sheet itself. A sheet is, at the most
    basic level, simply another window in your application, and you can use any of the standard
    event-handling APIs to receive events in the sheet. For example, you can:
    
        -   receive events in the sheet via WaitNextEvent, and handle them directly in your
            main event loop
            
        -   create the sheet using Dialog Manager APIs, and use IsDialogEvent and DialogSelect
            to handle events in the sheet
            
        -   install Carbon event handlers on the sheet, and respond to events in your handlers
    
    Which approach you choose is up to you.
    
    • Sheets in CarbonLib
    
    The sheet window class, sheet WDEF procIDs, and ShowSheetWindow, HideSheetWindow, and
    GetSheetWindowParent APIs are implemented in CarbonLib starting with version 1.3. However,
    since Mac OS 8 and 9 do not traditionally support a window-modal user interface, sheet
    windows are displayed as app-modal windows by CarbonLib. From your application's perspective,
    event handling for a sheet in CarbonLib is the same as event handling for a sheet on X;
    ShowSheetWindow still returns immediately, and your application should still return back
    to its main event loop and be prepared to handle events in other windows. On CarbonLib,
    your application will simply never receive an user input in any of your other windows;
    since the sheet has application modality, the Carbon Event Manager will discard events
    in any windows other than the sheet.
    
    • Creating a Sheet
    
    A sheet is just a normal window with a special window class: kSheetWindowClass or
    kSheetAlertWindowClass. As such, it can be created in any of the ways you might create
    a window: NewWindow, NewCWindow, CreateNewWindow, GetNewWindow, GetNewCWindow, 
    CreateWindowFromCollection, CreateWindowFromResource, CreateWindowFromNib, NewDialog,
    NewColorDialog, NewFeaturesDialog, or GetNewDialog.
    
    The Window Manager defines two window classes and two WDEF procIDs for sheets:
        
        -   kSheetWindowClass and kSheetAlertWindowClass
        -   kWindowSheetProc and kWindowSheetAlertProc
        
    The window classes may be used with CreateNewWindow, CreateWindowFromCollection, and
    CreateWindowFromResource; the WDEF procIDs may be used with NewWindow, NewCWindow, NewDialog,
    NewColorDialog, NewFeaturesDialog, and in 'WDEF' and 'DLOG' resources.
    
    The first release of Mac OS X only supports kSheetWindowClass and kWindowSheetProc;
    it does not support kSheetAlertWindowClass or kWindowSheetAlertProc. The latter window
    class and procID were added in CarbonLib 1.3 and will be added to a future version of
    Mac OS X. A new window class and procID were necessary for CarbonLib support because
    sheets can be used for both alerts ("Do you want to save changes before closing this
    window?") and dialogs (a Navigation Services PutFile dialog). On Mac OS X, sheet windows
    have the same appearance when used for either an alert or a dialog, but on Mac OS 8 and 9,
    alert windows have a different appearance from dialog windows. Two separate window classes
    are necessary for CarbonLib to know whether to display a sheet using a movable alert or a
    movable dialog window. Therefore, it is recommended that you use kSheetAlertWindowClass when
    creating a sheet window that will be used to display an alert, although this is not required.
    
    • Displaying a Sheet
    
    A sheet is made visible by calling the ShowSheetWindow API. This API shows the sheet,
    using whatever visual effects are appropriate for the platform, and then returns immediately.
    On Mac OS X, it creates a window group and places the sheet and its parent window into the
    group; it also marks the sheet as window-modal. On CarbonLib, it marks the sheet as app-modal
    but does not create a window group.
    
    On Mac OS X, before the sheet window is actually made visible, ShowSheetWindow sends a 
    kEventWindowDrawContent event to the sheet window, asking it to draw its content into the
    window's offscreen buffer. The sheet must handle this event, or its content area will be
    blank after the sheet becomes visible.
    
    In some cases, this handler is automatically provided for you:
    
        -   If you create your sheet window using the Dialog Manager, the Dialog Manager
            automatically installs a handler for this event that calls DrawDialog, so you
            don't need to install the handler yourself.
            
        -   If you install the standard Carbon window event handler on your sheet window
            (using kWindowStandardHandlerAttribute or InstallStandardEventHandler), the
            standard handler automatically handles this event and calls DrawControls.
            
    Typically, your event handling code (whether it uses WaitNextEvent, the Dialog Manager,
    or Carbon event handlers) will receive and respond to events in the sheet until the
    user does something that should cause the sheet to close. This might be clicking in an
    OK or Cancel button, for example. At that time, your event handling code should call
    HideSheetWindow. The sheet window will hide, but will not be destroyed, so you can use
    it again later if you want.
*/
/*
 *  ShowSheetWindow()
 *  
 *  Summary:
 *    Shows a sheet window using appropriate visual effects.
 *  
 *  Discussion:
 *    ShowSheetWindow is implemented in both CarbonLib 1.3 and Mac OS
 *    X. Since Mac OS 9 does not use a window-modal user interface for
 *    alerts and dialogs, ShowSheetWindow in CarbonLib does not bind
 *    the sheet to the parent window in the same way that it does on
 *    Mac OS X; instead, it shows the sheet like a standard
 *    movable-modal dialog window. Sheet windows must use the window
 *    classes kSheetWindowClass or kSheetAlertWindowClass to get the
 *    right appearance on both platforms.
 *  
 *  Parameters:
 *    
 *    inSheet:
 *      The sheet window to show.
 *    
 *    inParentWindow:
 *      The sheet's parent window.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ShowSheetWindow(
  WindowRef   inSheet,
  WindowRef   inParentWindow);


/*
 *  HideSheetWindow()
 *  
 *  Summary:
 *    Hides a sheet window using appropriate visual effects.
 *  
 *  Parameters:
 *    
 *    inSheet:
 *      The sheet window to hide.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HideSheetWindow(WindowRef inSheet);


/*
 *  GetSheetWindowParent()
 *  
 *  Summary:
 *    Returns the parent window of a sheet.
 *  
 *  Parameters:
 *    
 *    inSheet:
 *      The sheet window whose parent to retrieve.
 *    
 *    outParentWindow:
 *      On exit, contains the parent window of the sheet.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetSheetWindowParent(
  WindowRef    inSheet,
  WindowRef *  outParentWindow);



/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Disabling Screen Redraw                                                            */
/*——————————————————————————————————————————————————————————————————————————————————————*/
/*
   disable and enable screen updates for changes to the current application’s windows
   (OS X only for now)
*/

/*
 *  DisableScreenUpdates()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
DisableScreenUpdates(void);


/*
 *  EnableScreenUpdates()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
EnableScreenUpdates(void);



/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Window Properties                                                                  */
/*——————————————————————————————————————————————————————————————————————————————————————*/
/*
   Routines available from Mac OS 8.5 forward
   or from Mac OS 8.1 forward when linking to CarbonLib 1.0 forward
*/

/*
 *  GetWindowProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
GetWindowProperty(
  WindowRef         window,
  PropertyCreator   propertyCreator,
  PropertyTag       propertyTag,
  UInt32            bufferSize,
  UInt32 *          actualSize,            /* can be NULL */
  void *            propertyBuffer);


/*
 *  GetWindowPropertySize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
GetWindowPropertySize(
  WindowRef         window,
  PropertyCreator   creator,
  PropertyTag       tag,
  UInt32 *          size);


/*
 *  SetWindowProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
SetWindowProperty(
  WindowRef         window,
  PropertyCreator   propertyCreator,
  PropertyTag       propertyTag,
  UInt32            propertySize,
  void *            propertyBuffer);


/*
 *  RemoveWindowProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in WindowsLib 8.5 and later
 */
extern OSStatus 
RemoveWindowProperty(
  WindowRef         window,
  PropertyCreator   propertyCreator,
  PropertyTag       propertyTag);



/* Routines available from Mac OS 8.1 forward when linking to CarbonLib 1.0 forward*/

enum {
  kWindowPropertyPersistent     = 0x00000001 /* whether this property gets saved when flattening the window */
};

/*
 *  GetWindowPropertyAttributes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetWindowPropertyAttributes(
  WindowRef   window,
  OSType      propertyCreator,
  OSType      propertyTag,
  UInt32 *    attributes);


/*
 *  ChangeWindowPropertyAttributes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ChangeWindowPropertyAttributes(
  WindowRef   window,
  OSType      propertyCreator,
  OSType      propertyTag,
  UInt32      attributesToSet,
  UInt32      attributesToClear);


/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Utilities                                                                          */
/*——————————————————————————————————————————————————————————————————————————————————————*/
/*
 *  PinRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
PinRect(
  const Rect *  theRect,
  Point         thePt);



/*
 *  GetGrayRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern RgnHandle 
GetGrayRgn(void);



/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Window Part Tracking                                                               */
/*——————————————————————————————————————————————————————————————————————————————————————*/
/*
 *  TrackBox()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
TrackBox(
  WindowRef        window,
  Point            thePt,
  WindowPartCode   partCode);


/*
 *  TrackGoAway()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
TrackGoAway(
  WindowRef   window,
  Point       thePt);



/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Region Dragging                                                                    */
/*——————————————————————————————————————————————————————————————————————————————————————*/
/*
 *  DragGrayRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
DragGrayRgn(
  RgnHandle        theRgn,
  Point            startPt,
  const Rect *     limitRect,
  const Rect *     slopRect,
  short            axis,
  DragGrayRgnUPP   actionProc);


/*
 *  DragTheRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
DragTheRgn(
  RgnHandle        theRgn,
  Point            startPt,
  const Rect *     limitRect,
  const Rect *     slopRect,
  short            axis,
  DragGrayRgnUPP   actionProc);



/*——————————————————————————————————————————————————————————————————————————————————————*/
/*  • GetAuxWin                                                                         */
/*                                                                                      */
/*  GetAuxWin is not available in Carbon                                                */
/*——————————————————————————————————————————————————————————————————————————————————————*/
#if !OPAQUE_TOOLBOX_STRUCTS
/*
 *  GetAuxWin()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


#endif  /* !OPAQUE_TOOLBOX_STRUCTS */

/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • C Glue                                                                             */
/*——————————————————————————————————————————————————————————————————————————————————————*/
/*
 *  setwtitle()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  trackgoaway()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  findwindow()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  getwtitle()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  growwindow()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  newwindow()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  newcwindow()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  pinrect()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  trackbox()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  draggrayrgn()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  dragwindow()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*——————————————————————————————————————————————————————————————————————————————————————*/
/* • Window Accessors                                                                   */
/*——————————————————————————————————————————————————————————————————————————————————————*/

/*
 *  GetWindowGoAwayFlag()
 *  
 *  Discussion:
 *    use GetWindowAttributes in Carbon
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later or as macro/inline
 */


/*
 *  GetWindowSpareFlag()
 *  
 *  Discussion:
 *    use GetWindowAttributes in Carbon
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later or as macro/inline
 */


/*
 *  GetWindowList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0.2 and later
 */
extern WindowRef 
GetWindowList(void);



/*
 *  GetWindowPort()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later or as macro/inline
 */
extern CGrafPtr 
GetWindowPort(WindowRef window);


/*
 *  GetWindowStructurePort()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern CGrafPtr 
GetWindowStructurePort(WindowRef inWindow);



/*
 *  GetWindowKind()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later or as macro/inline
 */
extern short 
GetWindowKind(WindowRef window);



/*
 *  IsWindowHilited()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later or as macro/inline
 */
extern Boolean 
IsWindowHilited(WindowRef window);



/*
 *  IsWindowUpdatePending()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later or as macro/inline
 */
extern Boolean 
IsWindowUpdatePending(WindowRef window);



/*
 *  [Mac]GetNextWindow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0.2 and later or as macro/inline
 */
#if TARGET_OS_MAC
    #define MacGetNextWindow GetNextWindow
#endif
extern WindowRef 
MacGetNextWindow(WindowRef window);



/*
 *  GetWindowStandardState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later or as macro/inline
 */
extern Rect * 
GetWindowStandardState(
  WindowRef   window,
  Rect *      rect);



/*
 *  GetWindowUserState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later or as macro/inline
 */
extern Rect * 
GetWindowUserState(
  WindowRef   window,
  Rect *      rect);



/*
 *  SetWindowKind()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later or as macro/inline
 */
extern void 
SetWindowKind(
  WindowRef   window,
  short       kind);



/*
 *  SetWindowStandardState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later or as macro/inline
 */
extern void 
SetWindowStandardState(
  WindowRef     window,
  const Rect *  rect);




/*
 *  SetWindowUserState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later or as macro/inline
 */
extern void 
SetWindowUserState(
  WindowRef     window,
  const Rect *  rect);



/*
 *  SetPortWindowPort()
 *  
 *  Discussion:
 *    set the current QuickDraw port to the port associated with the
 *    window
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later or as macro/inline
 */
extern void 
SetPortWindowPort(WindowRef window);




/*
 *  GetWindowPortBounds()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later or as macro/inline
 */
extern Rect * 
GetWindowPortBounds(
  WindowRef   window,
  Rect *      bounds);



/*
 *  GetWindowFromPort()
 *  
 *  Discussion:
 *    Needed to ‘cast up’ to a WindowRef from a GrafPtr
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later or as macro/inline
 */
extern WindowRef 
GetWindowFromPort(CGrafPtr port);






/* old accessors*/

/*
 *  GetWindowDataHandle()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */



/*
 *  SetWindowDataHandle()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */



/*
 *  GetWindowZoomFlag()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */



/*
 *  GetWindowStructureRgn()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */



/*
 *  GetWindowContentRgn()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */



/*
 *  GetWindowUpdateRgn()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */



/*
 *  GetWindowTitleWidth()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */



/*——————————————————————————————————————————————————————————————————————————————————————————————————*/
/* Obsolete symbolic names                                                                          */
/*——————————————————————————————————————————————————————————————————————————————————————————————————*/
enum {
  kWindowGroupAttrSelectable    = kWindowGroupAttrSelectAsLayer,
  kWindowGroupAttrPositionFixed = kWindowGroupAttrMoveTogether,
  kWindowGroupAttrZOrderFixed   = kWindowGroupAttrLayerTogether
};










#if PRAGMA_STRUCT_ALIGN
    #pragma options align=reset
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

#ifdef __cplusplus
}
#endif

#endif /* __MACWINDOWS__ */

