/*
     File:       QD/Displays.h
 
     Contains:   Display Manager Interfaces.
 
     Version:    Quickdraw-96.21~1
 
     Copyright:  © 1993-2002 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __DISPLAYS__
#define __DISPLAYS__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef __VIDEO__
#include <QD/Video.h>
#endif

#ifndef __CMAPPLICATION__
#include <ColorSync/CMApplication.h>
#endif

#ifndef __APPLEEVENTS__
#include <AE/AppleEvents.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=mac68k

typedef void *                          DMProcessInfoPtr;
typedef void *                          DMModalFilterUPP;
enum {
                                        /* AppleEvents Core Suite */
  kAESystemConfigNotice         = 'cnfg', /* Core Suite types */
  kAEDisplayNotice              = 'dspl',
  kAEDisplaySummary             = 'dsum',
  keyDMConfigVersion            = 'dmcv',
  keyDMConfigFlags              = 'dmcf',
  keyDMConfigReserved           = 'dmcr',
  keyDisplayID                  = 'dmid',
  keyDisplayComponent           = 'dmdc',
  keyDisplayDevice              = 'dmdd',
  keyDisplayFlags               = 'dmdf',
  keyDisplayMode                = 'dmdm',
  keyDisplayModeReserved        = 'dmmr',
  keyDisplayReserved            = 'dmdr',
  keyDisplayMirroredId          = 'dmmi',
  keyDeviceFlags                = 'dddf',
  keyDeviceDepthMode            = 'dddm',
  keyDeviceRect                 = 'dddr',
  keyPixMapRect                 = 'dpdr',
  keyPixMapHResolution          = 'dphr',
  keyPixMapVResolution          = 'dpvr',
  keyPixMapPixelType            = 'dppt',
  keyPixMapPixelSize            = 'dpps',
  keyPixMapCmpCount             = 'dpcc',
  keyPixMapCmpSize              = 'dpcs',
  keyPixMapAlignment            = 'dppa',
  keyPixMapResReserved          = 'dprr',
  keyPixMapReserved             = 'dppr',
  keyPixMapColorTableSeed       = 'dpct',
  keySummaryMenubar             = 'dsmb',
  keySummaryChanges             = 'dsch',
  keyDisplayOldConfig           = 'dold',
  keyDisplayNewConfig           = 'dnew'
};

enum {
  dmOnlyActiveDisplays          = true,
  dmAllDisplays                 = false
};


enum {
                                        /* DMSendDependentNotification notifyClass */
  kDependentNotifyClassShowCursor = 'shcr', /* When display mgr shows a hidden cursor during an unmirror */
  kDependentNotifyClassDriverOverride = 'ndrv', /* When a driver is overridden */
  kDependentNotifyClassDisplayMgrOverride = 'dmgr', /* When display manager is upgraded */
  kDependentNotifyClassProfileChanged = 'prof' /* When DMSetProfileByAVID is called */
};


enum {
                                        /* Switch Flags */
  kNoSwitchConfirmBit           = 0,    /* Flag indicating that there is no need to confirm a switch to this mode */
  kDepthNotAvailableBit         = 1,    /* Current depth not available in new mode */
  kShowModeBit                  = 3,    /* Show this mode even though it requires a confirm. */
  kModeNotResizeBit             = 4,    /* Do not use this mode to resize display (for cards that mode drives a different connector). */
  kNeverShowModeBit             = 5     /* This mode should not be shown in the user interface. */
};

/*    Summary Change Flags (sticky bits indicating an operation was performed)
    For example, moving a display then moving it back will still set the kMovedDisplayBit.
*/
enum {
  kBeginEndConfigureBit         = 0,
  kMovedDisplayBit              = 1,
  kSetMainDisplayBit            = 2,
  kSetDisplayModeBit            = 3,
  kAddDisplayBit                = 4,
  kRemoveDisplayBit             = 5,
  kNewDisplayBit                = 6,
  kDisposeDisplayBit            = 7,
  kEnabledDisplayBit            = 8,
  kDisabledDisplayBit           = 9,
  kMirrorDisplayBit             = 10,
  kUnMirrorDisplayBit           = 11
};


enum {
                                        /* Notification Messages for extended call back routines */
  kDMNotifyRequestConnectionProbe = 0,  /* Like kDMNotifyRequestDisplayProbe only not for smart displays (used in wake before all busses are awake) */
  kDMNotifyInstalled            = 1,    /* At install time */
  kDMNotifyEvent                = 2,    /* Post change time */
  kDMNotifyRemoved              = 3,    /* At remove time */
  kDMNotifyPrep                 = 4,    /* Pre change time */
  kDMNotifyExtendEvent          = 5,    /* Allow registrees to extend apple event before it is sent */
  kDMNotifyDependents           = 6,    /* Minor notification check without full update */
  kDMNotifySuspendConfigure     = 7,    /* Temporary end of configuration */
  kDMNotifyResumeConfigure      = 8,    /* Resume configuration */
  kDMNotifyRequestDisplayProbe  = 9,    /* Request smart displays re-probe (used in sleep and hot plugging) */
  kDMNotifyDisplayWillSleep     = 10,   /* Mac OS X only */
  kDMNotifyDisplayDidWake       = 11,   /* Mac OS X only */
                                        /* Notification Flags */
  kExtendedNotificationProc     = (1L << 16)
};


/* types for notifyType */
enum {
  kFullNotify                   = 0,    /* This is the appleevent whole nine yards notify */
  kFullDependencyNotify         = 1     /* Only sends to those who want to know about interrelated functionality (used for updating UI) */
};

/* DisplayID/DeviceID constants */
enum {
  kDummyDeviceID                = 0x00FF, /* This is the ID of the dummy display, used when the last ÒrealÓ display is disabled.*/
  kInvalidDisplayID             = 0x0000, /* This is the invalid ID*/
  kFirstDisplayID               = 0x0100
};

enum {
                                        /* bits for panelListFlags */
  kAllowDuplicatesBit           = 0
};

enum {
                                        /* bits for nameFlags */
  kSuppressNumberBit            = 0,
  kSuppressNumberMask           = 1,
  kForceNumberBit               = 1,
  kForceNumberMask              = 2,
  kSuppressNameBit              = 2,
  kSuppressNameMask             = 4
};

/* DMGetNameByAVID masks*/
enum {
  kDMSupressNumbersMask         = (1 << 0), /* Supress the numbers and return only names*/
  kDMForceNumbersMask           = (1 << 1), /* Force numbers to always be shown (even on single display configs)*/
  kDMSupressNameMask            = (1 << 2) /* Supress the names and return only numbers.*/
};



/* Constants for fidelity checks */
enum {
  kNoFidelity                   = 0,
  kMinimumFidelity              = 1,
  kDefaultFidelity              = 500,  /* I'm just picking a number for Apple default panels and engines*/
  kDefaultManufacturerFidelity  = 1000  /* I'm just picking a number for Manufacturer's panels and engines (overrides apple defaults)*/
};

enum {
  kAnyPanelType                 = 0,    /* Pass to DMNewEngineList for list of all panels (as opposed to specific types)*/
  kAnyEngineType                = 0,    /* Pass to DMNewEngineList for list of all engines*/
  kAnyDeviceType                = 0,    /* Pass to DMNewDeviceList for list of all devices*/
  kAnyPortType                  = 0     /* Pass to DMNewDevicePortList for list of all devices*/
};

/* portListFlags for DM_NewDevicePortList */
enum {
                                        /* Should offline devices be put into the port list (such as dummy display) */
  kPLIncludeOfflineDevicesBit   = 0
};


/* confirmFlags for DMConfirmConfiguration */
enum {
  kForceConfirmBit              = 0,    /* Force a confirm dialog */
  kForceConfirmMask             = (1 << kForceConfirmBit)
};


/* Flags for displayModeFlags */
enum {
  kDisplayModeListNotPreferredBit = 0,
  kDisplayModeListNotPreferredMask = (1 << kDisplayModeListNotPreferredBit)
};


/* Flags for itemFlags */
enum {
  kComponentListNotPreferredBit = 0,
  kComponentListNotPreferredMask = (1 << kComponentListNotPreferredBit)
};

enum {
  kDisplayTimingInfoVersionZero = 1,
  kDisplayTimingInfoReservedCountVersionZero = 16,
  kDisplayModeEntryVersionZero  = 0,    /* displayModeVersion - original version*/
  kDisplayModeEntryVersionOne   = 1     /* displayModeVersion - added displayModeOverrideInfo*/
};


enum {
  kMakeAndModelReservedCount    = 4     /* Number of reserved fields*/
};


/* Display Gestalt for DMDisplayGestalt*/
enum {
  kDisplayGestaltDisplayCommunicationAttr = 'comm',
  kDisplayGestaltForbidI2CMask  = (1 << 0), /* Some displays have firmware problems if they get I2C communication.  If this bit is set, then I2C communication is forbidden*/
  kDisplayGestaltUseI2CPowerMask = (1 << 1), /* Some displays require I2C power settings (most use DPMS).*/
  kDisplayGestaltCalibratorAttr = 'cali',
  kDisplayGestaltBrightnessAffectsGammaMask = (1 << 0), /* Used by default calibrator (should we show brightness panel) */
  kDisplayGestaltViewAngleAffectsGammaMask = (1 << 1) /* Currently not used by color sync*/
};


typedef UInt32                          DMFidelityType;
/*
   AVID is an ID for ports and devices the old DisplayID type
    is carried on for compatibility
*/


typedef void *                          DMListType;
typedef unsigned long                   DMListIndexType;
typedef VDPowerStateRec                 AVPowerStateRec;
typedef VDPowerStateRec *               AVPowerStatePtr;
struct DMDisplayTimingInfoRec {
  UInt32              timingInfoVersion;
  UInt32              timingInfoAttributes;   /* Flags */
  SInt32              timingInfoRelativeQuality; /* quality of the timing */
  SInt32              timingInfoRelativeDefault; /* relative default of the timing */

  UInt32              timingInfoReserved[16]; /* Reserved */
};
typedef struct DMDisplayTimingInfoRec   DMDisplayTimingInfoRec;
typedef DMDisplayTimingInfoRec *        DMDisplayTimingInfoPtr;

struct DMComponentListEntryRec {
  DisplayIDType       itemID;                 /* DisplayID Manager*/
  Component           itemComponent;          /* Component Manager*/
  ComponentDescription  itemDescription;      /* We can always construct this if we use something beyond the compontent mgr.*/

  ResType             itemClass;              /* Class of group to put this panel (eg geometry/color/etc for panels, brightness/contrast for engines, video out/sound/etc for devices)*/
  DMFidelityType      itemFidelity;           /* How good is this item for the specified search?*/
  ResType             itemSubClass;           /* Subclass of group to put this panel.  Can use to do sub-grouping (eg volume for volume panel and mute panel)*/
  Point               itemSort;               /* Set to 0 - future to sort the items in a sub group.*/

  unsigned long       itemFlags;              /* Set to 0 (future expansion)*/
  ResType             itemReserved;           /* What kind of code does the itemReference point to  (right now - kPanelEntryTypeComponentMgr only)*/
  unsigned long       itemFuture1;            /* Set to 0 (future expansion - probably an alternate code style)*/
  unsigned long       itemFuture2;            /* Set to 0 (future expansion - probably an alternate code style)*/
  unsigned long       itemFuture3;            /* Set to 0 (future expansion - probably an alternate code style)*/
  unsigned long       itemFuture4;            /* Set to 0 (future expansion - probably an alternate code style)*/
};
typedef struct DMComponentListEntryRec  DMComponentListEntryRec;
typedef DMComponentListEntryRec *       DMComponentListEntryPtr;
/* ¥¥¥ Move AVLocationRec to AVComponents.i AFTER AVComponents.i is created*/
struct AVLocationRec {
  unsigned long       locationConstant;       /* Set to 0 (future expansion - probably an alternate code style)*/
};
typedef struct AVLocationRec            AVLocationRec;
typedef AVLocationRec *                 AVLocationPtr;
struct DMDepthInfoRec {
  VDSwitchInfoPtr     depthSwitchInfo;        /* This is the switch mode to choose this timing/depth */
  VPBlockPtr          depthVPBlock;           /* VPBlock (including size, depth and format) */
  UInt32              depthFlags;             /* VDVideoParametersInfoRec.csDepthFlags  */
  UInt32              depthReserved1;         /* Reserved */
  UInt32              depthReserved2;         /* Reserved */
};
typedef struct DMDepthInfoRec           DMDepthInfoRec;
typedef DMDepthInfoRec *                DMDepthInfoPtr;
struct DMDepthInfoBlockRec {
  unsigned long       depthBlockCount;        /* How many depths are there? */
  DMDepthInfoPtr      depthVPBlock;           /* Array of DMDepthInfoRec */
  unsigned long       depthBlockFlags;        /* Reserved */
  unsigned long       depthBlockReserved1;    /* Reserved */
  unsigned long       depthBlockReserved2;    /* Reserved */
};
typedef struct DMDepthInfoBlockRec      DMDepthInfoBlockRec;
typedef DMDepthInfoBlockRec *           DMDepthInfoBlockPtr;
struct DMDisplayModeListEntryRec {
  UInt32              displayModeFlags;
  VDSwitchInfoPtr     displayModeSwitchInfo;
  VDResolutionInfoPtr  displayModeResolutionInfo;
  VDTimingInfoPtr     displayModeTimingInfo;
  DMDepthInfoBlockPtr  displayModeDepthBlockInfo; /* Information about all the depths*/
  UInt32              displayModeVersion;     /* What version is this record (now kDisplayModeEntryVersionOne)*/
  StringPtr           displayModeName;        /* Name of the timing mode*/
  DMDisplayTimingInfoPtr  displayModeDisplayInfo; /* Information from the display.*/
};
typedef struct DMDisplayModeListEntryRec DMDisplayModeListEntryRec;
typedef DMDisplayModeListEntryRec *     DMDisplayModeListEntryPtr;

struct DependentNotifyRec {
  ResType             notifyType;             /* What type was the engine that made the change (may be zero)*/
  ResType             notifyClass;            /* What class was the change (eg geometry, color etc)*/
  DisplayIDType       notifyPortID;           /* Which device was touched (kInvalidDisplayID -> all or none)*/
  ComponentInstance   notifyComponent;        /* What engine did it (may be 0)?*/

  unsigned long       notifyVersion;          /* Set to 0 (future expansion)*/
  unsigned long       notifyFlags;            /* Set to 0 (future expansion)*/
  unsigned long       notifyReserved;         /* Set to 0 (future expansion)*/
  unsigned long       notifyFuture;           /* Set to 0 (future expansion)*/
};
typedef struct DependentNotifyRec       DependentNotifyRec;
typedef DependentNotifyRec *            DependentNotifyPtr;

struct DMMakeAndModelRec {
  ResType             manufacturer;
  UInt32              model;
  UInt32              serialNumber;
  UInt32              manufactureDate;

  UInt32              makeReserved[4];
};
typedef struct DMMakeAndModelRec        DMMakeAndModelRec;
typedef DMMakeAndModelRec *             DMMakeAndModelPtr;
/* DMNewDisplayList displayListIncludeFlags*/
enum {
  kIncludeOnlineActiveDisplaysMask = (1 << 0),
  kIncludeOnlineDisabledDisplaysMask = (1 << 1),
  kIncludeOfflineDisplaysMask   = (1 << 2),
  kIncludeOfflineDummyDisplaysMask = (1 << 3),
  kIncludeHardwareMirroredDisplaysMask = (1 << 4)
};


enum {
                                        /* modeListFlags for DMNewDisplayModeList */
  kDMModeListIncludeAllModesMask = (1 << 0), /* Include all timing modes not _explicitly_ excluded (see other bits)*/
  kDMModeListIncludeOfflineModesMask = (1 << 1),
  kDMModeListExcludeDriverModesMask = (1 << 2), /* Exclude old-style timing modes (cscGetNextResolution/kDisplayModeIDFindFirstResolution modes)*/
  kDMModeListExcludeDisplayModesMask = (1 << 3), /* Exclude timing modes that come from the display (always arbritrary timing modes)*/
  kDMModeListExcludeCustomModesMask = (1 << 4), /* Exclude custom modes that came neither from the driver or display (need a better name)*/
  kDMModeListPreferStretchedModesMask = (1 << 5), /* Prefer modes that are stretched over modes that are letterboxed when setting kDisplayModeListNotPreferredBit*/
  kDMModeListPreferSafeModesMask = (1 << 6) /* Prefer modes that are safe over modes that are not when setting kDisplayModeListNotPreferredBit*/
};


/* DMNewDisplayList displayListFlags*/
struct DisplayListEntryRec {
  GDHandle            displayListEntryGDevice;
  DisplayIDType       displayListEntryDisplayID;
  UInt32              displayListEntryIncludeFlags; /* Reason this entry was included*/
  UInt32              displayListEntryReserved1;

  UInt32              displayListEntryReserved2; /* Zero*/
  UInt32              displayListEntryReserved3; /* Zero*/
  UInt32              displayListEntryReserved4; /* Zero*/
  UInt32              displayListEntryReserved5; /* Zero*/
};
typedef struct DisplayListEntryRec      DisplayListEntryRec;
typedef DisplayListEntryRec *           DisplayListEntryPtr;
struct DMProfileListEntryRec {
  CMProfileRef        profileRef;
  Ptr                 profileReserved1;       /* Reserved*/
  Ptr                 profileReserved2;       /* Reserved*/
  Ptr                 profileReserved3;       /* Reserved*/
};
typedef struct DMProfileListEntryRec    DMProfileListEntryRec;
typedef DMProfileListEntryRec *         DMProfileListEntryPtr;
typedef CALLBACK_API( void , DMNotificationProcPtr )(AppleEvent * theEvent);
typedef CALLBACK_API( void , DMExtendedNotificationProcPtr )(void *userData, short theMessage, void *notifyData);
typedef CALLBACK_API( void , DMComponentListIteratorProcPtr )(void *userData, DMListIndexType itemIndex, DMComponentListEntryPtr componentInfo);
typedef CALLBACK_API( void , DMDisplayModeListIteratorProcPtr )(void *userData, DMListIndexType itemIndex, DMDisplayModeListEntryPtr displaymodeInfo);
typedef CALLBACK_API( void , DMProfileListIteratorProcPtr )(void *userData, DMListIndexType itemIndex, DMProfileListEntryPtr profileInfo);
typedef CALLBACK_API( void , DMDisplayListIteratorProcPtr )(void *userData, DMListIndexType itemIndex, DisplayListEntryPtr displaymodeInfo);
typedef STACK_UPP_TYPE(DMNotificationProcPtr)                   DMNotificationUPP;
typedef STACK_UPP_TYPE(DMExtendedNotificationProcPtr)           DMExtendedNotificationUPP;
typedef STACK_UPP_TYPE(DMComponentListIteratorProcPtr)          DMComponentListIteratorUPP;
typedef STACK_UPP_TYPE(DMDisplayModeListIteratorProcPtr)        DMDisplayModeListIteratorUPP;
typedef STACK_UPP_TYPE(DMProfileListIteratorProcPtr)            DMProfileListIteratorUPP;
typedef STACK_UPP_TYPE(DMDisplayListIteratorProcPtr)            DMDisplayListIteratorUPP;
/*
 *  NewDMNotificationUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern DMNotificationUPP
NewDMNotificationUPP(DMNotificationProcPtr userRoutine)       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewDMExtendedNotificationUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern DMExtendedNotificationUPP
NewDMExtendedNotificationUPP(DMExtendedNotificationProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewDMComponentListIteratorUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern DMComponentListIteratorUPP
NewDMComponentListIteratorUPP(DMComponentListIteratorProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewDMDisplayModeListIteratorUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern DMDisplayModeListIteratorUPP
NewDMDisplayModeListIteratorUPP(DMDisplayModeListIteratorProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewDMProfileListIteratorUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern DMProfileListIteratorUPP
NewDMProfileListIteratorUPP(DMProfileListIteratorProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewDMDisplayListIteratorUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern DMDisplayListIteratorUPP
NewDMDisplayListIteratorUPP(DMDisplayListIteratorProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeDMNotificationUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeDMNotificationUPP(DMNotificationUPP userUPP)           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeDMExtendedNotificationUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeDMExtendedNotificationUPP(DMExtendedNotificationUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeDMComponentListIteratorUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeDMComponentListIteratorUPP(DMComponentListIteratorUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeDMDisplayModeListIteratorUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeDMDisplayModeListIteratorUPP(DMDisplayModeListIteratorUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeDMProfileListIteratorUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeDMProfileListIteratorUPP(DMProfileListIteratorUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeDMDisplayListIteratorUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeDMDisplayListIteratorUPP(DMDisplayListIteratorUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeDMNotificationUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeDMNotificationUPP(
  AppleEvent *       theEvent,
  DMNotificationUPP  userUPP)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeDMExtendedNotificationUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeDMExtendedNotificationUPP(
  void *                     userData,
  short                      theMessage,
  void *                     notifyData,
  DMExtendedNotificationUPP  userUPP)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeDMComponentListIteratorUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeDMComponentListIteratorUPP(
  void *                      userData,
  DMListIndexType             itemIndex,
  DMComponentListEntryPtr     componentInfo,
  DMComponentListIteratorUPP  userUPP)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeDMDisplayModeListIteratorUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeDMDisplayModeListIteratorUPP(
  void *                        userData,
  DMListIndexType               itemIndex,
  DMDisplayModeListEntryPtr     displaymodeInfo,
  DMDisplayModeListIteratorUPP  userUPP)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeDMProfileListIteratorUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeDMProfileListIteratorUPP(
  void *                    userData,
  DMListIndexType           itemIndex,
  DMProfileListEntryPtr     profileInfo,
  DMProfileListIteratorUPP  userUPP)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeDMDisplayListIteratorUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeDMDisplayListIteratorUPP(
  void *                    userData,
  DMListIndexType           itemIndex,
  DisplayListEntryPtr       displaymodeInfo,
  DMDisplayListIteratorUPP  userUPP)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DMDisplayGestalt()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DisplayLib 2.1 and later
 */


/*
 *  DMUseScreenPrefs()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DisplayLib 2.1 and later
 */


/*
 *  DMSuspendConfigure()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DisplayLib 2.1 and later
 */


/*
 *  DMResumeConfigure()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DisplayLib 2.1 and later
 */


/*
 *  DMSetGammaByAVID()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DisplayLib 2.1 and later
 */


/*
 *  DMGetGammaByAVID()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DisplayLib 2.1 and later
 */


/*
 *  DMGetMakeAndModelByAVID()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DisplayLib 2.1 and later
 */


/*
 *  DMNewDisplayList()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DisplayLib 2.1 and later
 */


/*
 *  DMGetIndexedDisplayFromList()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DisplayLib 2.1 and later
 */


/*
 *  DMNewProfileListByAVID()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DisplayLib 2.1 and later
 */


/*
 *  DMGetIndexedProfileFromList()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DisplayLib 2.1 and later
 */



/*
 *  DMGetFirstScreenDevice()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern GDHandle 
DMGetFirstScreenDevice(Boolean activeOnly)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMGetNextScreenDevice()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern GDHandle 
DMGetNextScreenDevice(
  GDHandle   theDevice,
  Boolean    activeOnly)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMDrawDesktopRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DMDrawDesktopRect(Rect * globalRect)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMDrawDesktopRegion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DMDrawDesktopRegion(RgnHandle globalRgn)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  DMBeginConfigureDisplays()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
DMBeginConfigureDisplays(Handle * displayState)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMEndConfigureDisplays()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
DMEndConfigureDisplays(Handle displayState)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMAddDisplay()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
DMAddDisplay(
  GDHandle        newDevice,
  short           driver,
  unsigned long   mode,
  unsigned long   reserved,
  unsigned long   displayID,
  Component       displayComponent,
  Handle          displayState)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMMoveDisplay()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
DMMoveDisplay(
  GDHandle   moveDevice,
  short      x,
  short      y,
  Handle     displayState)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMDisableDisplay()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
DMDisableDisplay(
  GDHandle   disableDevice,
  Handle     displayState)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMEnableDisplay()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
DMEnableDisplay(
  GDHandle   enableDevice,
  Handle     displayState)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMRemoveDisplay()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
DMRemoveDisplay(
  GDHandle   removeDevice,
  Handle     displayState)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;





/*
 *  DMSetMainDisplay()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
DMSetMainDisplay(
  GDHandle   newMainDevice,
  Handle     displayState)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMSetDisplayMode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
DMSetDisplayMode(
  GDHandle         theDevice,
  unsigned long    mode,
  unsigned long *  depthMode,
  unsigned long    reserved,
  Handle           displayState)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMCheckDisplayMode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
DMCheckDisplayMode(
  GDHandle         theDevice,
  unsigned long    mode,
  unsigned long    depthMode,
  unsigned long *  switchFlags,
  unsigned long    reserved,
  Boolean *        modeOk)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMGetDeskRegion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
DMGetDeskRegion(RgnHandle * desktopRegion)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMRegisterNotifyProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
DMRegisterNotifyProc(
  DMNotificationUPP   notificationProc,
  DMProcessInfoPtr    whichPSN)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMRemoveNotifyProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
DMRemoveNotifyProc(
  DMNotificationUPP   notificationProc,
  DMProcessInfoPtr    whichPSN)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMQDIsMirroringCapable()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.5 and later
 */
extern OSErr 
DMQDIsMirroringCapable(Boolean * qdIsMirroringCapable)        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMCanMirrorNow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.5 and later
 */
extern OSErr 
DMCanMirrorNow(Boolean * canMirrorNow)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMIsMirroringOn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.5 and later
 */
extern OSErr 
DMIsMirroringOn(Boolean * isMirroringOn)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMMirrorDevices()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.5 and later
 */
extern OSErr 
DMMirrorDevices(
  GDHandle   gD1,
  GDHandle   gD2,
  Handle     displayState)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMUnmirrorDevice()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.5 and later
 */
extern OSErr 
DMUnmirrorDevice(
  GDHandle   gDevice,
  Handle     displayState)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMGetNextMirroredDevice()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.5 and later
 */
extern OSErr 
DMGetNextMirroredDevice(
  GDHandle    gDevice,
  GDHandle *  mirroredDevice)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMBlockMirroring()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.5 and later
 */
extern OSErr 
DMBlockMirroring(void)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMUnblockMirroring()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.5 and later
 */
extern OSErr 
DMUnblockMirroring(void)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMGetDisplayMgrA5World()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.5 and later
 */


/*
 *  DMGetDisplayIDByGDevice()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.5 and later
 */
extern OSErr 
DMGetDisplayIDByGDevice(
  GDHandle         displayDevice,
  DisplayIDType *  displayID,
  Boolean          failToMain)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMGetGDeviceByDisplayID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.5 and later
 */
extern OSErr 
DMGetGDeviceByDisplayID(
  DisplayIDType   displayID,
  GDHandle *      displayDevice,
  Boolean         failToMain)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMSetDisplayComponent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
DMSetDisplayComponent(
  GDHandle    theDevice,
  Component   displayComponent)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMGetDisplayComponent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
DMGetDisplayComponent(
  GDHandle     theDevice,
  Component *  displayComponent)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMNewDisplay()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.5 and later
 */
extern OSErr 
DMNewDisplay(
  GDHandle *      newDevice,
  short           driverRefNum,
  unsigned long   mode,
  unsigned long   reserved,
  DisplayIDType   displayID,
  Component       displayComponent,
  Handle          displayState)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMDisposeDisplay()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.5 and later
 */
extern OSErr 
DMDisposeDisplay(
  GDHandle   disposeDevice,
  Handle     displayState)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMResolveDisplayComponents()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
DMResolveDisplayComponents(void)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMRegisterExtendedNotifyProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DisplayLib 2.0 and later
 */
extern OSErr 
DMRegisterExtendedNotifyProc(
  DMExtendedNotificationUPP   notifyProc,
  void *                      notifyUserData,
  unsigned short              nofifyOnFlags,
  DMProcessInfoPtr            whichPSN)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMRemoveExtendedNotifyProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DisplayLib 2.0 and later
 */
extern OSErr 
DMRemoveExtendedNotifyProc(
  DMExtendedNotificationUPP   notifyProc,
  void *                      notifyUserData,
  DMProcessInfoPtr            whichPSN,
  unsigned short              removeFlags)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMNewAVPanelList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DisplayLib68k 2.0 and later
 */
extern OSErr 
DMNewAVPanelList(
  DisplayIDType      displayID,
  ResType            panelType,
  DMFidelityType     minimumFidelity,
  unsigned long      panelListFlags,
  unsigned long      reserved,
  DMListIndexType *  thePanelCount,
  DMListType *       thePanelList)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMNewAVEngineList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DisplayLib68k 2.0 and later
 */
extern OSErr 
DMNewAVEngineList(
  DisplayIDType      displayID,
  ResType            engineType,
  DMFidelityType     minimumFidelity,
  unsigned long      engineListFlags,
  unsigned long      reserved,
  DMListIndexType *  engineCount,
  DMListType *       engineList)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMNewAVDeviceList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DisplayLib68k 2.0 and later
 */
extern OSErr 
DMNewAVDeviceList(
  ResType            deviceType,
  unsigned long      deviceListFlags,
  unsigned long      reserved,
  DMListIndexType *  deviceCount,
  DMListType *       deviceList)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMNewAVPortListByPortType()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DisplayLib68k 2.0 and later
 */
extern OSErr 
DMNewAVPortListByPortType(
  ResType            subType,
  unsigned long      portListFlags,
  unsigned long      reserved,
  DMListIndexType *  devicePortCount,
  DMListType *       theDevicePortList)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMGetIndexedComponentFromList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DisplayLib68k 2.0 and later
 */
extern OSErr 
DMGetIndexedComponentFromList(
  DMListType                   panelList,
  DMListIndexType              itemIndex,
  unsigned long                reserved,
  DMComponentListIteratorUPP   listIterator,
  void *                       userData)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMDisposeList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DisplayLib 2.0 and later
 */
extern OSErr 
DMDisposeList(DMListType panelList)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMGetNameByAVID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DisplayLib68k 2.0 and later
 */
extern OSErr 
DMGetNameByAVID(
  AVIDType        theID,
  unsigned long   nameFlags,
  Str255          name)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMNewAVIDByPortComponent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DisplayLib68k 2.0 and later
 */
extern OSErr 
DMNewAVIDByPortComponent(
  Component       thePortComponent,
  ResType         portKind,
  unsigned long   reserved,
  AVIDType *      newID)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMGetPortComponentByAVID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DisplayLib68k 2.0 and later
 */
extern OSErr 
DMGetPortComponentByAVID(
  DisplayIDType           thePortID,
  Component *             thePortComponent,
  ComponentDescription *  theDesciption,
  ResType *               thePortKind)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMSendDependentNotification()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DisplayLib 2.0 and later
 */
extern OSErr 
DMSendDependentNotification(
  ResType             notifyType,
  ResType             notifyClass,
  AVIDType            displayID,
  ComponentInstance   notifyComponent)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMDisposeAVComponent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DisplayLib68k 2.0 and later
 */
extern OSErr 
DMDisposeAVComponent(Component theAVComponent)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMSaveScreenPrefs()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DisplayLib68k 2.0 and later
 */
extern OSErr 
DMSaveScreenPrefs(
  unsigned long   reserved1,
  unsigned long   saveFlags,
  unsigned long   reserved2)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMNewAVIDByDeviceComponent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DisplayLib68k 2.0 and later
 */
extern OSErr 
DMNewAVIDByDeviceComponent(
  Component        theDeviceComponent,
  ResType          portKind,
  unsigned long    reserved,
  DisplayIDType *  newID)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMNewAVPortListByDeviceAVID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DisplayLib68k 2.0 and later
 */
extern OSErr 
DMNewAVPortListByDeviceAVID(
  AVIDType           theID,
  DMFidelityType     minimumFidelity,
  unsigned long      portListFlags,
  unsigned long      reserved,
  DMListIndexType *  devicePortCount,
  DMListType *       theDevicePortList)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMGetDeviceComponentByAVID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DisplayLib68k 2.0 and later
 */
extern OSErr 
DMGetDeviceComponentByAVID(
  AVIDType                theDeviceID,
  Component *             theDeviceComponent,
  ComponentDescription *  theDesciption,
  ResType *               theDeviceKind)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMNewDisplayModeList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DisplayLib68k 2.0 and later
 */
extern OSErr 
DMNewDisplayModeList(
  DisplayIDType      displayID,
  unsigned long      modeListFlags,
  unsigned long      reserved,
  DMListIndexType *  thePanelCount,
  DMListType *       thePanelList)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMGetIndexedDisplayModeFromList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DisplayLib68k 2.0 and later
 */
extern OSErr 
DMGetIndexedDisplayModeFromList(
  DMListType                     panelList,
  DMListIndexType                itemIndex,
  unsigned long                  reserved,
  DMDisplayModeListIteratorUPP   listIterator,
  void *                         userData)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMGetGraphicInfoByAVID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DisplayLib68k 2.0 and later
 */
extern OSErr 
DMGetGraphicInfoByAVID(
  AVIDType         theID,
  PicHandle *      theAVPcit,
  Handle *         theAVIconSuite,
  AVLocationRec *  theAVLocation)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMGetAVPowerState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DisplayLib68k 2.0 and later
 */
extern OSErr 
DMGetAVPowerState(
  AVIDType          theID,
  AVPowerStatePtr   getPowerState,
  unsigned long     reserved1)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMSetAVPowerState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DisplayLib68k 2.0 and later
 */
extern OSErr 
DMSetAVPowerState(
  AVIDType          theID,
  AVPowerStatePtr   setPowerState,
  unsigned long     powerFlags,
  Handle            displayState)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMGetDeviceAVIDByPortAVID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DisplayLib68k 2.0 and later
 */
extern OSErr 
DMGetDeviceAVIDByPortAVID(
  AVIDType    portAVID,
  AVIDType *  deviceAVID)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMGetEnableByAVID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DisplayLib68k 2.0 and later
 */
extern OSErr 
DMGetEnableByAVID(
  AVIDType   theAVID,
  Boolean *  isAVIDEnabledNow,
  Boolean *  canChangeEnableNow)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMSetEnableByAVID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DisplayLib68k 2.0 and later
 */
extern OSErr 
DMSetEnableByAVID(
  AVIDType   theAVID,
  Boolean    doEnable,
  Handle     displayState)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMGetDisplayMode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DisplayLib68k 2.0 and later
 */
extern OSErr 
DMGetDisplayMode(
  GDHandle          theDevice,
  VDSwitchInfoPtr   switchInfo)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DMConfirmConfiguration()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DisplayLib 2.1 and later
 */
extern OSErr 
DMConfirmConfiguration(
  DMModalFilterUPP   filterProc,
  UInt32             confirmFlags,
  UInt32             reserved,
  Handle             displayState)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __DISPLAYS__ */

