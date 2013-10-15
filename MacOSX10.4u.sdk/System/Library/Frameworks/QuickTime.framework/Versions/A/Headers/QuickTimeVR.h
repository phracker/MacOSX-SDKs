/*
     File:       QuickTime/QuickTimeVR.h
 
     Contains:   QuickTime VR interfaces
 
     Version:    QuickTime 7.2.1
 
     Copyright:  © 1997-2006 by Apple Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __QUICKTIMEVR__
#define __QUICKTIMEVR__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef __MOVIES__
#include <QuickTime/Movies.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 2)

/* QuickTime is not available to 64-bit clients */

#if !__LP64__

typedef struct OpaqueQTVRInstance*      QTVRInstance;

/* Released API Version numbers */
#define kQTVRAPIMajorVersion05  (0x05)
#define kQTVRAPIMajorVersion02  (0x02)
#define kQTVRAPIMinorVersion00  (0x00)
#define kQTVRAPIMinorVersion01  (0x01)
#define kQTVRAPIMinorVersion10  (0x10)
#define kQTVRAPIMinorVersion20  (0x20)

/* Version numbers for the API described in this header */
#define kQTVRAPIMajorVersion kQTVRAPIMajorVersion05
#define kQTVRAPIMinorVersion kQTVRAPIMinorVersion00


enum {
  kQTVRControllerSubType        = 'ctyp',
  kQTVRQTVRType                 = 'qtvr',
  kQTVRPanoramaType             = 'pano',
  kQTVRObjectType               = 'obje',
  kQTVROldPanoType              = 'STpn', /* Used in QTVR 1.0 release*/
  kQTVROldObjectType            = 'stna' /* Used in QTVR 1.0 release*/
};

#define kQTVRUnknownType '\?\?\?\?' /* Unknown node type */
/* QTVR hot spot types*/
enum {
  kQTVRHotSpotLinkType          = 'link',
  kQTVRHotSpotURLType           = 'url ',
  kQTVRHotSpotUndefinedType     = 'undf'
};

/* Special Values for nodeID in QTVRGoToNodeID*/
enum {
  kQTVRCurrentNode              = 0,
  kQTVRPreviousNode             = (long)0x80000000,
  kQTVRDefaultNode              = (long)0x80000001
};

/* Panorama correction modes used for the kQTVRImagingCorrection imaging property*/
enum {
  kQTVRNoCorrection             = 0,
  kQTVRPartialCorrection        = 1,
  kQTVRFullCorrection           = 2
};

/* Imaging Modes used by QTVRSetImagingProperty, QTVRGetImagingProperty, QTVRUpdate, QTVRBeginUpdate*/
typedef UInt32 QTVRImagingMode;
enum {
  kQTVRStatic                   = 1,
  kQTVRMotion                   = 2,
  kQTVRCurrentMode              = 0,    /* Special Value for QTVRUpdate*/
  kQTVRAllModes                 = 100   /* Special value for QTVRSetProperty*/
};

/* Imaging Properties used by QTVRSetImagingProperty, QTVRGetImagingProperty*/
enum {
  kQTVRImagingCorrection        = 1,
  kQTVRImagingQuality           = 2,
  kQTVRImagingDirectDraw        = 3,
  kQTVRImagingCurrentMode       = 100   /* Get Only*/
};

/* OR the above with kImagingDefaultValue to get/set the default value*/
enum {
  kImagingDefaultValue          = (long)0x80000000
};

/* Transition Types used by QTVRSetTransitionProperty, QTVREnableTransition*/
enum {
  kQTVRTransitionSwing          = 1
};

/* Transition Properties QTVRSetTransitionProperty*/
enum {
  kQTVRTransitionSpeed          = 1,
  kQTVRTransitionDirection      = 2
};

/* Constraint values used to construct value returned by GetConstraintStatus*/
enum {
  kQTVRUnconstrained            = 0L,
  kQTVRCantPanLeft              = 1L << 0,
  kQTVRCantPanRight             = 1L << 1,
  kQTVRCantPanUp                = 1L << 2,
  kQTVRCantPanDown              = 1L << 3,
  kQTVRCantZoomIn               = 1L << 4,
  kQTVRCantZoomOut              = 1L << 5,
  kQTVRCantTranslateLeft        = 1L << 6,
  kQTVRCantTranslateRight       = 1L << 7,
  kQTVRCantTranslateUp          = 1L << 8,
  kQTVRCantTranslateDown        = 1L << 9
};

/* Object-only mouse mode values used to construct value returned by QTVRGetCurrentMouseMode*/
enum {
  kQTVRPanning                  = 1L << 0, /* standard objects, "object only" controllers*/
  kQTVRTranslating              = 1L << 1, /* all objects*/
  kQTVRZooming                  = 1L << 2, /* all objects*/
  kQTVRScrolling                = 1L << 3, /* standard object arrow scrollers and joystick object*/
  kQTVRSelecting                = 1L << 4 /* object absolute controller*/
};

/* Properties for use with QTVRSetInteractionProperty/GetInteractionProperty*/
enum {
  kQTVRInteractionMouseClickHysteresis = 1, /* pixels within which the mouse is considered not to have moved (UInt16)*/
  kQTVRInteractionMouseClickTimeout = 2, /* ticks after which a mouse click times out and turns into panning (UInt32)*/
  kQTVRInteractionPanTiltSpeed  = 3,    /* control the relative pan/tilt speed from 1 (slowest) to 10 (fastest). (UInt32) Default is 5;*/
  kQTVRInteractionZoomSpeed     = 4,    /* control the relative zooming speed from 1 (slowest) to 10 (fastest). (UInt32) Default is 5;*/
  kQTVRInteractionTranslateOnMouseDown = 101, /* Holding MouseDown with this setting translates zoomed object movies (Boolean)*/
  kQTVRInteractionMouseMotionScale = 102, /* The maximum angle of rotation caused by dragging across the display window. (* float)*/
  kQTVRInteractionNudgeMode     = 103   /* A QTVRNudgeMode: rotate, translate, or the same as the current mouse mode. Requires QTVR 2.1*/
};

/* OR the above with kQTVRInteractionDefaultValue to get/set the default value*/
enum {
  kQTVRInteractionDefaultValue  = (long)0x80000000
};


/* Geometry constants used in QTVRSetBackBufferPrefs, QTVRGetBackBufferSettings, QTVRGetBackBufferMemInfo*/
enum {
  kQTVRUseMovieGeometry         = 0,
  kQTVRVerticalCylinder         = 'vcyl',
  kQTVRHorizontalCylinder       = 'hcyl',
  kQTVRCube                     = 'cube'
};

/* Resolution constants used in QTVRSetBackBufferPrefs, QTVRGetBackBufferSettings, QTVRGetBackBufferMemInfo*/
enum {
  kQTVRDefaultRes               = 0,
  kQTVRFullRes                  = 1L << 0,
  kQTVRHalfRes                  = 1L << 1,
  kQTVRQuarterRes               = 1L << 2
};

/* QTVR-specific pixelFormat constants used in QTVRSetBackBufferPrefs, QTVRGetBackBufferSettings, QTVRGetBackBufferMemInfo*/
enum {
  kQTVRUseMovieDepth            = 0
};

/* Cache Size Pref constants used in QTVRSetBackBufferPrefs, QTVRGetBackBufferSettings*/
enum {
  kQTVRMinimumCache             = -1,
  kQTVRSuggestedCache           = 0,
  kQTVRFullCache                = 1
};

/* Angular units used by QTVRSetAngularUnits*/
typedef UInt32 QTVRAngularUnits;
enum {
  kQTVRDegrees                  = 0,
  kQTVRRadians                  = 1
};

/* Values for enableFlag parameter in QTVREnableHotSpot*/
enum {
  kQTVRHotSpotID                = 0,
  kQTVRHotSpotType              = 1,
  kQTVRAllHotSpots              = 2
};

/* Values for viewParameter for QTVRSet/GetViewParameter*/
enum {
  kQTVRPanAngle                 = 0x0100, /* default units; &float, &float*/
  kQTVRTiltAngle                = 0x0101, /* default units; &float, &float*/
  kQTVRFieldOfViewAngle         = 0x0103, /* default units; &float, &float*/
  kQTVRViewCenter               = 0x0104, /* pixels (per object movies); &QTVRFloatPoint, &QTVRFloatPoint*/
  kQTVRHotSpotsVisible          = 0x0200 /* Boolean, &Boolean*/
};

/* Values for flagsIn for QTVRSet/GetViewParameter*/
enum {
  kQTVRValueIsRelative          = 1L << 0, /* Is the value absolute or relative to the current value?*/
  kQTVRValueIsRate              = 1L << 1, /* Is the value absolute or a rate of change to be applied?*/
  kQTVRValueIsUserPrefRelative  = 1L << 2 /* Is the value a percentage of the user rate pref?*/
};

/* Values for kind parameter in QTVRGet/SetConstraints, QTVRGetViewingLimits*/
enum {
  kQTVRPan                      = 0,
  kQTVRTilt                     = 1,
  kQTVRFieldOfView              = 2,
  kQTVRViewCenterH              = 4,    /* WrapAndConstrain only*/
  kQTVRViewCenterV              = 5     /* WrapAndConstrain only*/
};

/* Values for setting parameter in QTVRSetAnimationSetting, QTVRGetAnimationSetting*/
typedef UInt32 QTVRObjectAnimationSetting;
enum {
                                        /* View Frame Animation Settings*/
  kQTVRPalindromeViewFrames     = 1,
  kQTVRStartFirstViewFrame      = 2,
  kQTVRDontLoopViewFrames       = 3,
  kQTVRPlayEveryViewFrame       = 4,    /* Requires QTVR 2.1 (kQTVRAPIMajorVersion02 + kQTVRAPIMinorVersion10)*/
                                        /* View Animation Settings*/
  kQTVRSyncViewToFrameRate      = 16,
  kQTVRPalindromeViews          = 17,
  kQTVRPlayStreamingViews       = 18    /* Requires QTVR 2.1 (kQTVRAPIMajorVersion02 + kQTVRAPIMinorVersion10)*/
};

typedef UInt32 QTVRControlSetting;
enum {
  kQTVRWrapPan                  = 1,
  kQTVRWrapTilt                 = 2,
  kQTVRCanZoom                  = 3,
  kQTVRReverseHControl          = 4,
  kQTVRReverseVControl          = 5,
  kQTVRSwapHVControl            = 6,
  kQTVRTranslation              = 7
};

typedef UInt32 QTVRViewStateType;
enum {
  kQTVRDefault                  = 0,
  kQTVRCurrent                  = 2,
  kQTVRMouseDown                = 3
};

typedef UInt32 QTVRNudgeControl;
enum {
  kQTVRRight                    = 0,
  kQTVRUpRight                  = 45,
  kQTVRUp                       = 90,
  kQTVRUpLeft                   = 135,
  kQTVRLeft                     = 180,
  kQTVRDownLeft                 = 225,
  kQTVRDown                     = 270,
  kQTVRDownRight                = 315
};

typedef UInt32 QTVRNudgeMode;
enum {
  kQTVRNudgeRotate              = 0,
  kQTVRNudgeTranslate           = 1,
  kQTVRNudgeSameAsMouse         = 2
};


/* Flags to control elements of the QTVR control bar (set via mcActionSetFlags) */
enum {
  mcFlagQTVRSuppressBackBtn     = 1L << 16,
  mcFlagQTVRSuppressZoomBtns    = 1L << 17,
  mcFlagQTVRSuppressHotSpotBtn  = 1L << 18,
  mcFlagQTVRSuppressTranslateBtn = 1L << 19,
  mcFlagQTVRSuppressHelpText    = 1L << 20,
  mcFlagQTVRSuppressHotSpotNames = 1L << 21,
  mcFlagQTVRExplicitFlagSet     = 1L << 31 /* bits 0->30 should be interpreted as "explicit on" for the corresponding suppression bits*/
};

/* Cursor types used in type field of QTVRCursorRecord*/
enum {
  kQTVRUseDefaultCursor         = 0,
  kQTVRStdCursorType            = 1,
  kQTVRColorCursorType          = 2
};

/* Values for flags parameter in QTVRMouseOverHotSpot callback*/
enum {
  kQTVRHotSpotEnter             = 0,
  kQTVRHotSpotWithin            = 1,
  kQTVRHotSpotLeave             = 2
};

/* Values for flags parameter in QTVRSetPrescreenImagingCompleteProc*/
enum {
  kQTVRPreScreenEveryIdle       = 1L << 0 /* Requires QTVR 2.1 (kQTVRAPIMajorVersion02 + kQTVRAPIMinorVersion10)*/
};

/* Values for flags field of areasOfInterest in QTVRSetBackBufferImagingProc*/
enum {
  kQTVRBackBufferEveryUpdate    = 1L << 0,
  kQTVRBackBufferEveryIdle      = 1L << 1,
  kQTVRBackBufferAlwaysRefresh  = 1L << 2,
  kQTVRBackBufferHorizontal     = 1L << 3 /* Requires that backbuffer proc be long-rowBytes aware (gestaltQDHasLongRowBytes)*/
};

/* Values for flagsIn parameter in QTVRBackBufferImaging callback*/
enum {
  kQTVRBackBufferRectVisible    = 1L << 0,
  kQTVRBackBufferWasRefreshed   = 1L << 1
};

/* Values for flagsOut parameter in QTVRBackBufferImaging callback*/
enum {
  kQTVRBackBufferFlagDidDraw    = 1L << 0,
  kQTVRBackBufferFlagLastFlag   = 1L << 31
};

/* QTVRCursorRecord used in QTVRReplaceCursor*/
struct QTVRCursorRecord {
  UInt16              theType;                /* field was previously named "type"*/
  SInt16              rsrcID;
  Handle              handle;
};
typedef struct QTVRCursorRecord         QTVRCursorRecord;
struct QTVRFloatPoint {
  float               x;
  float               y;
};
typedef struct QTVRFloatPoint           QTVRFloatPoint;
/* Struct used for areasOfInterest parameter in QTVRSetBackBufferImagingProc*/
struct QTVRAreaOfInterest {
  float               panAngle;
  float               tiltAngle;
  float               width;
  float               height;
  UInt32              flags;
};
typedef struct QTVRAreaOfInterest       QTVRAreaOfInterest;
/*
  =================================================================================================
   Callback routines 
  -------------------------------------------------------------------------------------------------
*/

typedef CALLBACK_API( OSErr , QTVRLeavingNodeProcPtr )(QTVRInstance qtvr, UInt32 fromNodeID, UInt32 toNodeID, Boolean *cancel, SInt32 refCon);
typedef CALLBACK_API( OSErr , QTVREnteringNodeProcPtr )(QTVRInstance qtvr, UInt32 nodeID, SInt32 refCon);
typedef CALLBACK_API( OSErr , QTVRMouseOverHotSpotProcPtr )(QTVRInstance qtvr, UInt32 hotSpotID, UInt32 flags, SInt32 refCon);
typedef CALLBACK_API( OSErr , QTVRImagingCompleteProcPtr )(QTVRInstance qtvr, SInt32 refCon);
typedef CALLBACK_API( OSErr , QTVRBackBufferImagingProcPtr )(QTVRInstance qtvr, Rect *drawRect, UInt16 areaIndex, UInt32 flagsIn, UInt32 *flagsOut, SInt32 refCon);
typedef STACK_UPP_TYPE(QTVRLeavingNodeProcPtr)                  QTVRLeavingNodeUPP;
typedef STACK_UPP_TYPE(QTVREnteringNodeProcPtr)                 QTVREnteringNodeUPP;
typedef STACK_UPP_TYPE(QTVRMouseOverHotSpotProcPtr)             QTVRMouseOverHotSpotUPP;
typedef STACK_UPP_TYPE(QTVRImagingCompleteProcPtr)              QTVRImagingCompleteUPP;
typedef STACK_UPP_TYPE(QTVRBackBufferImagingProcPtr)            QTVRBackBufferImagingUPP;
/*
 *  NewQTVRLeavingNodeUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QTVRLeavingNodeUPP
NewQTVRLeavingNodeUPP(QTVRLeavingNodeProcPtr userRoutine)     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewQTVREnteringNodeUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QTVREnteringNodeUPP
NewQTVREnteringNodeUPP(QTVREnteringNodeProcPtr userRoutine)   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewQTVRMouseOverHotSpotUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QTVRMouseOverHotSpotUPP
NewQTVRMouseOverHotSpotUPP(QTVRMouseOverHotSpotProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewQTVRImagingCompleteUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QTVRImagingCompleteUPP
NewQTVRImagingCompleteUPP(QTVRImagingCompleteProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewQTVRBackBufferImagingUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QTVRBackBufferImagingUPP
NewQTVRBackBufferImagingUPP(QTVRBackBufferImagingProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeQTVRLeavingNodeUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQTVRLeavingNodeUPP(QTVRLeavingNodeUPP userUPP)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeQTVREnteringNodeUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQTVREnteringNodeUPP(QTVREnteringNodeUPP userUPP)       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeQTVRMouseOverHotSpotUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQTVRMouseOverHotSpotUPP(QTVRMouseOverHotSpotUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeQTVRImagingCompleteUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQTVRImagingCompleteUPP(QTVRImagingCompleteUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeQTVRBackBufferImagingUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQTVRBackBufferImagingUPP(QTVRBackBufferImagingUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeQTVRLeavingNodeUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeQTVRLeavingNodeUPP(
  QTVRInstance        qtvr,
  UInt32              fromNodeID,
  UInt32              toNodeID,
  Boolean *           cancel,
  SInt32              refCon,
  QTVRLeavingNodeUPP  userUPP)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeQTVREnteringNodeUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeQTVREnteringNodeUPP(
  QTVRInstance         qtvr,
  UInt32               nodeID,
  SInt32               refCon,
  QTVREnteringNodeUPP  userUPP)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeQTVRMouseOverHotSpotUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeQTVRMouseOverHotSpotUPP(
  QTVRInstance             qtvr,
  UInt32                   hotSpotID,
  UInt32                   flags,
  SInt32                   refCon,
  QTVRMouseOverHotSpotUPP  userUPP)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeQTVRImagingCompleteUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeQTVRImagingCompleteUPP(
  QTVRInstance            qtvr,
  SInt32                  refCon,
  QTVRImagingCompleteUPP  userUPP)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeQTVRBackBufferImagingUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeQTVRBackBufferImagingUPP(
  QTVRInstance              qtvr,
  Rect *                    drawRect,
  UInt16                    areaIndex,
  UInt32                    flagsIn,
  UInt32 *                  flagsOut,
  SInt32                    refCon,
  QTVRBackBufferImagingUPP  userUPP)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

#if __MACH__
  #ifdef __cplusplus
    inline QTVRLeavingNodeUPP                                   NewQTVRLeavingNodeUPP(QTVRLeavingNodeProcPtr userRoutine) { return userRoutine; }
    inline QTVREnteringNodeUPP                                  NewQTVREnteringNodeUPP(QTVREnteringNodeProcPtr userRoutine) { return userRoutine; }
    inline QTVRMouseOverHotSpotUPP                              NewQTVRMouseOverHotSpotUPP(QTVRMouseOverHotSpotProcPtr userRoutine) { return userRoutine; }
    inline QTVRImagingCompleteUPP                               NewQTVRImagingCompleteUPP(QTVRImagingCompleteProcPtr userRoutine) { return userRoutine; }
    inline QTVRBackBufferImagingUPP                             NewQTVRBackBufferImagingUPP(QTVRBackBufferImagingProcPtr userRoutine) { return userRoutine; }
    inline void                                                 DisposeQTVRLeavingNodeUPP(QTVRLeavingNodeUPP) { }
    inline void                                                 DisposeQTVREnteringNodeUPP(QTVREnteringNodeUPP) { }
    inline void                                                 DisposeQTVRMouseOverHotSpotUPP(QTVRMouseOverHotSpotUPP) { }
    inline void                                                 DisposeQTVRImagingCompleteUPP(QTVRImagingCompleteUPP) { }
    inline void                                                 DisposeQTVRBackBufferImagingUPP(QTVRBackBufferImagingUPP) { }
    inline OSErr                                                InvokeQTVRLeavingNodeUPP(QTVRInstance qtvr, UInt32 fromNodeID, UInt32 toNodeID, Boolean * cancel, SInt32 refCon, QTVRLeavingNodeUPP userUPP) { return (*userUPP)(qtvr, fromNodeID, toNodeID, cancel, refCon); }
    inline OSErr                                                InvokeQTVREnteringNodeUPP(QTVRInstance qtvr, UInt32 nodeID, SInt32 refCon, QTVREnteringNodeUPP userUPP) { return (*userUPP)(qtvr, nodeID, refCon); }
    inline OSErr                                                InvokeQTVRMouseOverHotSpotUPP(QTVRInstance qtvr, UInt32 hotSpotID, UInt32 flags, SInt32 refCon, QTVRMouseOverHotSpotUPP userUPP) { return (*userUPP)(qtvr, hotSpotID, flags, refCon); }
    inline OSErr                                                InvokeQTVRImagingCompleteUPP(QTVRInstance qtvr, SInt32 refCon, QTVRImagingCompleteUPP userUPP) { return (*userUPP)(qtvr, refCon); }
    inline OSErr                                                InvokeQTVRBackBufferImagingUPP(QTVRInstance qtvr, Rect * drawRect, UInt16 areaIndex, UInt32 flagsIn, UInt32 * flagsOut, SInt32 refCon, QTVRBackBufferImagingUPP userUPP) { return (*userUPP)(qtvr, drawRect, areaIndex, flagsIn, flagsOut, refCon); }
  #else
    #define NewQTVRLeavingNodeUPP(userRoutine)                  ((QTVRLeavingNodeUPP)userRoutine)
    #define NewQTVREnteringNodeUPP(userRoutine)                 ((QTVREnteringNodeUPP)userRoutine)
    #define NewQTVRMouseOverHotSpotUPP(userRoutine)             ((QTVRMouseOverHotSpotUPP)userRoutine)
    #define NewQTVRImagingCompleteUPP(userRoutine)              ((QTVRImagingCompleteUPP)userRoutine)
    #define NewQTVRBackBufferImagingUPP(userRoutine)            ((QTVRBackBufferImagingUPP)userRoutine)
    #define DisposeQTVRLeavingNodeUPP(userUPP)
    #define DisposeQTVREnteringNodeUPP(userUPP)
    #define DisposeQTVRMouseOverHotSpotUPP(userUPP)
    #define DisposeQTVRImagingCompleteUPP(userUPP)
    #define DisposeQTVRBackBufferImagingUPP(userUPP)
    #define InvokeQTVRLeavingNodeUPP(qtvr, fromNodeID, toNodeID, cancel, refCon, userUPP) (*userUPP)(qtvr, fromNodeID, toNodeID, cancel, refCon)
    #define InvokeQTVREnteringNodeUPP(qtvr, nodeID, refCon, userUPP) (*userUPP)(qtvr, nodeID, refCon)
    #define InvokeQTVRMouseOverHotSpotUPP(qtvr, hotSpotID, flags, refCon, userUPP) (*userUPP)(qtvr, hotSpotID, flags, refCon)
    #define InvokeQTVRImagingCompleteUPP(qtvr, refCon, userUPP) (*userUPP)(qtvr, refCon)
    #define InvokeQTVRBackBufferImagingUPP(qtvr, drawRect, areaIndex, flagsIn, flagsOut, refCon, userUPP) (*userUPP)(qtvr, drawRect, areaIndex, flagsIn, flagsOut, refCon)
  #endif
#endif

/*
  =================================================================================================
    QTVR Intercept Struct, Callback, Routine Descriptors 
  -------------------------------------------------------------------------------------------------
*/

typedef UInt32 QTVRProcSelector;
enum {
  kQTVRSetPanAngleSelector      = 0x2000,
  kQTVRSetTiltAngleSelector     = 0x2001,
  kQTVRSetFieldOfViewSelector   = 0x2002,
  kQTVRSetViewCenterSelector    = 0x2003,
  kQTVRMouseEnterSelector       = 0x2004,
  kQTVRMouseWithinSelector      = 0x2005,
  kQTVRMouseLeaveSelector       = 0x2006,
  kQTVRMouseDownSelector        = 0x2007,
  kQTVRMouseStillDownSelector   = 0x2008,
  kQTVRMouseUpSelector          = 0x2009,
  kQTVRTriggerHotSpotSelector   = 0x200A,
  kQTVRGetHotSpotTypeSelector   = 0x200B, /* Requires QTVR 2.1 (kQTVRAPIMajorVersion02 + kQTVRAPIMinorVersion10)*/
  kQTVRSetViewParameterSelector = 0x200C, /* Requires QTVR 5.0 (kQTVRAPIMajorVersion05 + kQTVRAPIMinorVersion00)*/
  kQTVRGetViewParameterSelector = 0x200D /* Requires QTVR 5.0 (kQTVRAPIMajorVersion05 + kQTVRAPIMinorVersion00)*/
};

struct QTVRInterceptRecord {
  SInt32              reserved1;
  SInt32              selector;

  SInt32              reserved2;
  SInt32              reserved3;

  SInt32              paramCount;
  void *              parameter[6];
};
typedef struct QTVRInterceptRecord      QTVRInterceptRecord;
typedef QTVRInterceptRecord *           QTVRInterceptPtr;
/* Prototype for Intercept Proc callback*/
typedef CALLBACK_API( void , QTVRInterceptProcPtr )(QTVRInstance qtvr, QTVRInterceptPtr qtvrMsg, SInt32 refCon, Boolean *cancel);
typedef STACK_UPP_TYPE(QTVRInterceptProcPtr)                    QTVRInterceptUPP;
/*
 *  NewQTVRInterceptUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QTVRInterceptUPP
NewQTVRInterceptUPP(QTVRInterceptProcPtr userRoutine)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeQTVRInterceptUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQTVRInterceptUPP(QTVRInterceptUPP userUPP)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeQTVRInterceptUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeQTVRInterceptUPP(
  QTVRInstance      qtvr,
  QTVRInterceptPtr  qtvrMsg,
  SInt32            refCon,
  Boolean *         cancel,
  QTVRInterceptUPP  userUPP)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

#if __MACH__
  #ifdef __cplusplus
    inline QTVRInterceptUPP                                     NewQTVRInterceptUPP(QTVRInterceptProcPtr userRoutine) { return userRoutine; }
    inline void                                                 DisposeQTVRInterceptUPP(QTVRInterceptUPP) { }
    inline void                                                 InvokeQTVRInterceptUPP(QTVRInstance qtvr, QTVRInterceptPtr qtvrMsg, SInt32 refCon, Boolean * cancel, QTVRInterceptUPP userUPP) { (*userUPP)(qtvr, qtvrMsg, refCon, cancel); }
  #else
    #define NewQTVRInterceptUPP(userRoutine)                    ((QTVRInterceptUPP)userRoutine)
    #define DisposeQTVRInterceptUPP(userUPP)
    #define InvokeQTVRInterceptUPP(qtvr, qtvrMsg, refCon, cancel, userUPP) (*userUPP)(qtvr, qtvrMsg, refCon, cancel)
  #endif
#endif

/*
  =================================================================================================
    Initialization QTVR calls 
  -------------------------------------------------------------------------------------------------
   Requires QTVR 2.1 (kQTVRAPIMajorVersion02 + kQTVRAPIMinorVersion10) and only work on Non-Macintosh platforms
*/
/*
  =================================================================================================
    General QTVR calls 
  -------------------------------------------------------------------------------------------------
*/
/*
 *  QTVRGetQTVRTrack()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern Track 
QTVRGetQTVRTrack(
  Movie    theMovie,
  SInt32   index)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRGetQTVRInstance()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRGetQTVRInstance(
  QTVRInstance *    qtvr,
  Track             qtvrTrack,
  MovieController   mc)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
  =================================================================================================
    Viewing Angles and Zooming 
  -------------------------------------------------------------------------------------------------
*/

/* QTVRSetViewParameter requires QTVR 5.0 (kQTVRAPIMajorVersion05 + kQTVRAPIMinorVersion00)*/
/*
 *  QTVRSetViewParameter()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 5.0 and later
 *    Windows:          in QTVR.lib 5.0 and later
 */
extern OSErr 
QTVRSetViewParameter(
  QTVRInstance   qtvr,
  UInt32         viewParameter,
  void *         value,
  UInt32         flagsIn)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* QTVRGetViewParameter requires QTVR 5.0 (kQTVRAPIMajorVersion05 + kQTVRAPIMinorVersion00)*/
/*
 *  QTVRGetViewParameter()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 5.0 and later
 *    Windows:          in QTVR.lib 5.0 and later
 */
extern OSErr 
QTVRGetViewParameter(
  QTVRInstance   qtvr,
  UInt32         viewParameter,
  void *         value,
  UInt32         flagsIn,
  UInt32 *       flagsOut)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRSetPanAngle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRSetPanAngle(
  QTVRInstance   qtvr,
  float          panAngle)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRGetPanAngle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern float 
QTVRGetPanAngle(QTVRInstance qtvr)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRSetTiltAngle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRSetTiltAngle(
  QTVRInstance   qtvr,
  float          tiltAngle)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRGetTiltAngle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern float 
QTVRGetTiltAngle(QTVRInstance qtvr)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRSetFieldOfView()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRSetFieldOfView(
  QTVRInstance   qtvr,
  float          fieldOfView)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRGetFieldOfView()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern float 
QTVRGetFieldOfView(QTVRInstance qtvr)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRShowDefaultView()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRShowDefaultView(QTVRInstance qtvr)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Object Specific*/
/*
 *  QTVRSetViewCenter()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRSetViewCenter(
  QTVRInstance            qtvr,
  const QTVRFloatPoint *  viewCenter)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRGetViewCenter()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRGetViewCenter(
  QTVRInstance      qtvr,
  QTVRFloatPoint *  viewCenter)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRNudge()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRNudge(
  QTVRInstance       qtvr,
  QTVRNudgeControl   direction)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* QTVRInteractionNudge requires QTVR 2.1 (kQTVRAPIMajorVersion02 + kQTVRAPIMinorVersion10)*/
/*
 *  QTVRInteractionNudge()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.1 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRInteractionNudge(
  QTVRInstance       qtvr,
  QTVRNudgeControl   direction)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
  =================================================================================================
    Scene and Node Location Information 
  -------------------------------------------------------------------------------------------------
*/

/*
 *  QTVRGetVRWorld()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRGetVRWorld(
  QTVRInstance       qtvr,
  QTAtomContainer *  VRWorld)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRGetNodeInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRGetNodeInfo(
  QTVRInstance       qtvr,
  UInt32             nodeID,
  QTAtomContainer *  nodeInfo)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRGoToNodeID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRGoToNodeID(
  QTVRInstance   qtvr,
  UInt32         nodeID)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRGetCurrentNodeID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern UInt32 
QTVRGetCurrentNodeID(QTVRInstance qtvr)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRGetNodeType()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSType 
QTVRGetNodeType(
  QTVRInstance   qtvr,
  UInt32         nodeID)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
  =================================================================================================
    Hot Spot related calls 
  -------------------------------------------------------------------------------------------------
*/

/*
 *  QTVRPtToHotSpotID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRPtToHotSpotID(
  QTVRInstance   qtvr,
  Point          pt,
  UInt32 *       hotSpotID)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* QTVRGetHotSpotType requires QTVR 2.1 (kQTVRAPIMajorVersion02 + kQTVRAPIMinorVersion10)*/
/*
 *  QTVRGetHotSpotType()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.1 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRGetHotSpotType(
  QTVRInstance   qtvr,
  UInt32         hotSpotID,
  OSType *       hotSpotType)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRTriggerHotSpot()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRTriggerHotSpot(
  QTVRInstance      qtvr,
  UInt32            hotSpotID,
  QTAtomContainer   nodeInfo,
  QTAtom            selectedAtom)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRSetMouseOverHotSpotProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRSetMouseOverHotSpotProc(
  QTVRInstance              qtvr,
  QTVRMouseOverHotSpotUPP   mouseOverHotSpotProc,
  SInt32                    refCon,
  UInt32                    flags)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVREnableHotSpot()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVREnableHotSpot(
  QTVRInstance   qtvr,
  UInt32         enableFlag,
  UInt32         hotSpotValue,
  Boolean        enable)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRGetVisibleHotSpots()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern UInt32 
QTVRGetVisibleHotSpots(
  QTVRInstance   qtvr,
  Handle         hotSpots)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRGetHotSpotRegion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRGetHotSpotRegion(
  QTVRInstance   qtvr,
  UInt32         hotSpotID,
  RgnHandle      hotSpotRegion)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
  =================================================================================================
    Event & Cursor Handling Calls 
  -------------------------------------------------------------------------------------------------
*/

/*
 *  QTVRSetMouseOverTracking()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRSetMouseOverTracking(
  QTVRInstance   qtvr,
  Boolean        enable)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRGetMouseOverTracking()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern Boolean 
QTVRGetMouseOverTracking(QTVRInstance qtvr)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRSetMouseDownTracking()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRSetMouseDownTracking(
  QTVRInstance   qtvr,
  Boolean        enable)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRGetMouseDownTracking()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern Boolean 
QTVRGetMouseDownTracking(QTVRInstance qtvr)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRMouseEnter()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRMouseEnter(
  QTVRInstance   qtvr,
  Point          pt,
  UInt32 *       hotSpotID,
  WindowRef      w)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRMouseWithin()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRMouseWithin(
  QTVRInstance   qtvr,
  Point          pt,
  UInt32 *       hotSpotID,
  WindowRef      w)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRMouseLeave()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRMouseLeave(
  QTVRInstance   qtvr,
  Point          pt,
  WindowRef      w)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRMouseDown()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRMouseDown(
  QTVRInstance   qtvr,
  Point          pt,
  UInt32         when,
  UInt16         modifiers,
  UInt32 *       hotSpotID,
  WindowRef      w)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRMouseStillDown()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRMouseStillDown(
  QTVRInstance   qtvr,
  Point          pt,
  UInt32 *       hotSpotID,
  WindowRef      w)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRMouseUp()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRMouseUp(
  QTVRInstance   qtvr,
  Point          pt,
  UInt32 *       hotSpotID,
  WindowRef      w)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* These require QTVR 2.01 (kQTVRAPIMajorVersion02 + kQTVRAPIMinorVersion01)*/
/*
 *  QTVRMouseStillDownExtended()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0.1 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRMouseStillDownExtended(
  QTVRInstance   qtvr,
  Point          pt,
  UInt32 *       hotSpotID,
  WindowRef      w,
  UInt32         when,
  UInt16         modifiers)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRMouseUpExtended()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0.1 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRMouseUpExtended(
  QTVRInstance   qtvr,
  Point          pt,
  UInt32 *       hotSpotID,
  WindowRef      w,
  UInt32         when,
  UInt16         modifiers)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
  =================================================================================================
    Intercept Routines 
  -------------------------------------------------------------------------------------------------
*/

/*
 *  QTVRInstallInterceptProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRInstallInterceptProc(
  QTVRInstance       qtvr,
  QTVRProcSelector   selector,
  QTVRInterceptUPP   interceptProc,
  SInt32             refCon,
  UInt32             flags)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRCallInterceptedProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRCallInterceptedProc(
  QTVRInstance           qtvr,
  QTVRInterceptRecord *  qtvrMsg)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
  =================================================================================================
    Object Movie Specific Calls 
  -------------------------------------------------------------------------------------------------
   QTVRGetCurrentMouseMode requires QTRVR 2.1 (kQTVRAPIMajorVersion02 + kQTVRAPIMinorVersion10)
*/
/*
 *  QTVRGetCurrentMouseMode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.1 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern UInt32 
QTVRGetCurrentMouseMode(QTVRInstance qtvr)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRSetFrameRate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRSetFrameRate(
  QTVRInstance   qtvr,
  float          rate)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRGetFrameRate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern float 
QTVRGetFrameRate(QTVRInstance qtvr)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRSetViewRate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRSetViewRate(
  QTVRInstance   qtvr,
  float          rate)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRGetViewRate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern float 
QTVRGetViewRate(QTVRInstance qtvr)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRSetViewCurrentTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRSetViewCurrentTime(
  QTVRInstance   qtvr,
  TimeValue      time)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRGetViewCurrentTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern TimeValue 
QTVRGetViewCurrentTime(QTVRInstance qtvr)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRGetCurrentViewDuration()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern TimeValue 
QTVRGetCurrentViewDuration(QTVRInstance qtvr)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
  =================================================================================================
   View State Calls - QTVR Object Only
  -------------------------------------------------------------------------------------------------
*/

/*
 *  QTVRSetViewState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRSetViewState(
  QTVRInstance        qtvr,
  QTVRViewStateType   viewStateType,
  UInt16              state)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRGetViewState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRGetViewState(
  QTVRInstance        qtvr,
  QTVRViewStateType   viewStateType,
  UInt16 *            state)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRGetViewStateCount()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern UInt16 
QTVRGetViewStateCount(QTVRInstance qtvr)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRSetAnimationSetting()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRSetAnimationSetting(
  QTVRInstance                 qtvr,
  QTVRObjectAnimationSetting   setting,
  Boolean                      enable)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRGetAnimationSetting()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRGetAnimationSetting(
  QTVRInstance                 qtvr,
  QTVRObjectAnimationSetting   setting,
  Boolean *                    enable)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRSetControlSetting()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRSetControlSetting(
  QTVRInstance         qtvr,
  QTVRControlSetting   setting,
  Boolean              enable)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRGetControlSetting()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRGetControlSetting(
  QTVRInstance         qtvr,
  QTVRControlSetting   setting,
  Boolean *            enable)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVREnableFrameAnimation()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVREnableFrameAnimation(
  QTVRInstance   qtvr,
  Boolean        enable)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRGetFrameAnimation()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern Boolean 
QTVRGetFrameAnimation(QTVRInstance qtvr)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVREnableViewAnimation()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVREnableViewAnimation(
  QTVRInstance   qtvr,
  Boolean        enable)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRGetViewAnimation()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern Boolean 
QTVRGetViewAnimation(QTVRInstance qtvr)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
  =================================================================================================
    Imaging Characteristics 
  -------------------------------------------------------------------------------------------------
*/

/*
 *  QTVRSetVisible()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRSetVisible(
  QTVRInstance   qtvr,
  Boolean        visible)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRGetVisible()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern Boolean 
QTVRGetVisible(QTVRInstance qtvr)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRSetImagingProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRSetImagingProperty(
  QTVRInstance      qtvr,
  QTVRImagingMode   imagingMode,
  UInt32            imagingProperty,
  SInt32            propertyValue)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRGetImagingProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRGetImagingProperty(
  QTVRInstance      qtvr,
  QTVRImagingMode   imagingMode,
  UInt32            imagingProperty,
  SInt32 *          propertyValue)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRUpdate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRUpdate(
  QTVRInstance      qtvr,
  QTVRImagingMode   imagingMode)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRBeginUpdateStream()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRBeginUpdateStream(
  QTVRInstance      qtvr,
  QTVRImagingMode   imagingMode)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVREndUpdateStream()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVREndUpdateStream(QTVRInstance qtvr)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRSetTransitionProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRSetTransitionProperty(
  QTVRInstance   qtvr,
  UInt32         transitionType,
  UInt32         transitionProperty,
  SInt32         transitionValue)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVREnableTransition()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVREnableTransition(
  QTVRInstance   qtvr,
  UInt32         transitionType,
  Boolean        enable)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
  =================================================================================================
    Basic Conversion and Math Routines 
  -------------------------------------------------------------------------------------------------
*/

/*
 *  QTVRSetAngularUnits()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRSetAngularUnits(
  QTVRInstance       qtvr,
  QTVRAngularUnits   units)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRGetAngularUnits()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern QTVRAngularUnits 
QTVRGetAngularUnits(QTVRInstance qtvr)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Pano specific routines*/
/*
 *  QTVRPtToAngles()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRPtToAngles(
  QTVRInstance   qtvr,
  Point          pt,
  float *        panAngle,
  float *        tiltAngle)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRCoordToAngles()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRCoordToAngles(
  QTVRInstance      qtvr,
  QTVRFloatPoint *  coord,
  float *           panAngle,
  float *           tiltAngle)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRAnglesToCoord()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRAnglesToCoord(
  QTVRInstance      qtvr,
  float             panAngle,
  float             tiltAngle,
  QTVRFloatPoint *  coord)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Object specific routines*/
/*
 *  QTVRPanToColumn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern short 
QTVRPanToColumn(
  QTVRInstance   qtvr,
  float          panAngle)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* zero based   */
/*
 *  QTVRColumnToPan()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern float 
QTVRColumnToPan(
  QTVRInstance   qtvr,
  short          column)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* zero based   */
/*
 *  QTVRTiltToRow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern short 
QTVRTiltToRow(
  QTVRInstance   qtvr,
  float          tiltAngle)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* zero based   */
/*
 *  QTVRRowToTilt()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern float 
QTVRRowToTilt(
  QTVRInstance   qtvr,
  short          row)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* zero based               */
/*
 *  QTVRWrapAndConstrain()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRWrapAndConstrain(
  QTVRInstance   qtvr,
  short          kind,
  float          value,
  float *        result)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
  =================================================================================================
    Interaction Routines 
  -------------------------------------------------------------------------------------------------
*/

/*
 *  QTVRSetEnteringNodeProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRSetEnteringNodeProc(
  QTVRInstance          qtvr,
  QTVREnteringNodeUPP   enteringNodeProc,
  SInt32                refCon,
  UInt32                flags)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRSetLeavingNodeProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRSetLeavingNodeProc(
  QTVRInstance         qtvr,
  QTVRLeavingNodeUPP   leavingNodeProc,
  SInt32               refCon,
  UInt32               flags)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRSetInteractionProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRSetInteractionProperty(
  QTVRInstance   qtvr,
  UInt32         property,
  void *         value)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRGetInteractionProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRGetInteractionProperty(
  QTVRInstance   qtvr,
  UInt32         property,
  void *         value)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRReplaceCursor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRReplaceCursor(
  QTVRInstance        qtvr,
  QTVRCursorRecord *  cursRecord)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
  =================================================================================================
    Viewing Limits and Constraints 
  -------------------------------------------------------------------------------------------------
*/

/*
 *  QTVRGetViewingLimits()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRGetViewingLimits(
  QTVRInstance   qtvr,
  UInt16         kind,
  float *        minValue,
  float *        maxValue)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRGetConstraintStatus()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern UInt32 
QTVRGetConstraintStatus(QTVRInstance qtvr)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRGetConstraints()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRGetConstraints(
  QTVRInstance   qtvr,
  UInt16         kind,
  float *        minValue,
  float *        maxValue)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRSetConstraints()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRSetConstraints(
  QTVRInstance   qtvr,
  UInt16         kind,
  float          minValue,
  float          maxValue)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
  =================================================================================================
    Back Buffer Memory Management 
  -------------------------------------------------------------------------------------------------
*/

/*
 *  QTVRGetAvailableResolutions()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRGetAvailableResolutions(
  QTVRInstance   qtvr,
  UInt16 *       resolutionsMask)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* These require QTVR 2.1 (kQTVRAPIMajorVersion02 + kQTVRAPIMinorVersion10)*/
/*
 *  QTVRGetBackBufferMemInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.1 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRGetBackBufferMemInfo(
  QTVRInstance   qtvr,
  UInt32         geometry,
  UInt16         resolution,
  UInt32         cachePixelFormat,
  SInt32 *       minCacheBytes,
  SInt32 *       suggestedCacheBytes,
  SInt32 *       fullCacheBytes)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRGetBackBufferSettings()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.1 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRGetBackBufferSettings(
  QTVRInstance   qtvr,
  UInt32 *       geometry,
  UInt16 *       resolution,
  UInt32 *       cachePixelFormat,
  SInt16 *       cacheSize)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRSetBackBufferPrefs()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.1 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRSetBackBufferPrefs(
  QTVRInstance   qtvr,
  UInt32         geometry,
  UInt16         resolution,
  UInt32         cachePixelFormat,
  SInt16         cacheSize)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
  =================================================================================================
    Buffer Access 
  -------------------------------------------------------------------------------------------------
*/

/*
 *  QTVRSetPrescreenImagingCompleteProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRSetPrescreenImagingCompleteProc(
  QTVRInstance             qtvr,
  QTVRImagingCompleteUPP   imagingCompleteProc,
  SInt32                   refCon,
  UInt32                   flags)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRSetBackBufferImagingProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRSetBackBufferImagingProc(
  QTVRInstance               qtvr,
  QTVRBackBufferImagingUPP   backBufferImagingProc,
  UInt16                     numAreas,
  QTVRAreaOfInterest         areasOfInterest[],
  SInt32                     refCon)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTVRRefreshBackBuffer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeVRLib 2.0 and later
 *    Windows:          in QTVR.lib 2.1 and later
 */
extern OSErr 
QTVRRefreshBackBuffer(
  QTVRInstance   qtvr,
  UInt32         flags)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
  =================================================================================================
    Old Names
  -------------------------------------------------------------------------------------------------
*/
#if OLDROUTINENAMES
typedef QTVRCursorRecord                CursorRecord;
typedef QTVRAreaOfInterest              AreaOfInterest;
typedef QTVRFloatPoint                  FloatPoint;
typedef QTVRLeavingNodeProcPtr          LeavingNodeProcPtr;
typedef QTVRLeavingNodeUPP              LeavingNodeUPP;
typedef QTVREnteringNodeProcPtr         EnteringNodeProcPtr;
typedef QTVREnteringNodeUPP             EnteringNodeUPP;
typedef QTVRMouseOverHotSpotProcPtr     MouseOverHotSpotProcPtr;
typedef QTVRMouseOverHotSpotUPP         MouseOverHotSpotUPP;
typedef QTVRImagingCompleteProcPtr      ImagingCompleteProcPtr;
typedef QTVRImagingCompleteUPP          ImagingCompleteUPP;
typedef QTVRBackBufferImagingProcPtr    BackBufferImagingProcPtr;
typedef QTVRBackBufferImagingUPP        BackBufferImagingUPP;
#endif  /* OLDROUTINENAMES */



#endif // !__LP64__


#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif /* __QUICKTIMEVR__ */

