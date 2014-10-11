/*
     File:       HIToolbox/Balloons.h
 
     Contains:   Balloon Help Package Interfaces.
 
     Version:    HIToolbox-79.9~1
 
     Copyright:  © 1990-2001 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __BALLOONS__
#define __BALLOONS__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __QUICKDRAW__
#include <QD/Quickdraw.h>
#endif

#ifndef __MENUS__
#include <HIToolbox/Menus.h>
#endif

#ifndef __TEXTEDIT__
#include <HIToolbox/TextEdit.h>
#endif

#ifndef __MACERRORS__
#include <CarbonCore/MacErrors.h>
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

/*
   Carbon clients should use MacHelp. The definitions below will NOT work for Carbon and
   are only defined for those files that need to build pre-Carbon applications.
*/
/* • constants*/

typedef SInt16 BalloonVariant;
enum {
  kTopLeftTipPointsLeftVariant  = 0,
  kTopLeftTipPointsUpVariant    = 1,
  kTopRightTipPointsUpVariant   = 2,
  kTopRightTipPointsRightVariant = 3,
  kBottomRightTipPointsRightVariant = 4,
  kBottomRightTipPointsDownVariant = 5,
  kBottomLeftTipPointsDownVariant = 6,
  kBottomLeftTipPointsLeftVariant = 7,
  kBalloonVariantCount          = 8
};


enum {
  hmBalloonHelpVersion          = 0x0002 /* The real version of the Help Manager */
};

enum {
  kHMHelpMenuID                 = -16490, /* Resource ID and menu ID of help menu */
  kHMAboutHelpItem              = 1,    /* help menu item number of About Balloon Help… */
  kHMShowBalloonsItem           = 3     /* help menu item number of Show/Hide Balloons */
};

enum {
  kHMHelpID                     = -5696, /* ID of various Help Mgr package resources (in Pack14 range) */
  kBalloonWDEFID                = 126   /* Resource ID of the WDEF proc used in standard balloons */
};

enum {
                                        /* Dialog item template type constant */
  helpItem                      = 1     /* key value in DITL template that corresponds to the help item */
};

enum {
                                        /* Options for Help Manager resources in 'hmnu', 'hdlg', 'hrct', 'hovr', & 'hfdr' resources */
  hmDefaultOptions              = 0,    /* default options for help manager resources */
  hmUseSubIDBit                 = 0,
  hmAbsoluteCoordsBit           = 1,
  hmSaveBitsNoWindowBit         = 2,
  hmSaveBitsWindowBit           = 3,
  hmMatchInTitleBit             = 4,
  hmUseSubIDMask                = (1 << hmUseSubIDBit), /* treat resID's in resources as subID's of driver base ID (for Desk Accessories) */
  hmAbsoluteCoordsMask          = (1 << hmAbsoluteCoordsBit), /* ignore window port origin and treat rectangles as absolute coords (local to window) */
  hmSaveBitsNoWindowMask        = (1 << hmSaveBitsNoWindowBit), /* don't create a window, just blast bits on screen. No update event is generated */
  hmSaveBitsWindowMask          = (1 << hmSaveBitsWindowBit), /* create a window, but restore bits behind window when window goes away & generate update event */
  hmMatchInTitleMask            = (1 << hmMatchInTitleBit) /* for hwin resources, match string anywhere in window title string */
};

#if OLDROUTINENAMES
enum {
  hmUseSubID                    = hmUseSubIDMask,
  hmAbsoluteCoords              = hmAbsoluteCoordsMask,
  hmSaveBitsNoWindow            = hmSaveBitsNoWindowMask,
  hmSaveBitsWindow              = hmSaveBitsWindowMask,
  hmMatchInTitle                = hmMatchInTitleMask
};

#endif  /* OLDROUTINENAMES */

enum {
                                        /* Constants for Help Types in 'hmnu', 'hdlg', 'hrct', 'hovr', & 'hfdr' resources */
  kHMStringItem                 = 1,    /* pstring used in resource */
  kHMPictItem                   = 2,    /* 'PICT' ResID used in resource */
  kHMStringResItem              = 3,    /* 'STR#' ResID & index used in resource */
  kHMTEResItem                  = 6,    /* Styled Text Edit ResID used in resource ('TEXT' & 'styl') */
  kHMSTRResItem                 = 7,    /* 'STR ' ResID used in resource */
  kHMSkipItem                   = 256,  /* don't display a balloon */
  kHMCompareItem                = 512,  /* Compare pstring in menu item w/ PString in resource item ('hmnu' only) */
  kHMNamedResourceItem          = 1024, /* Use pstring in menu item to get 'STR#', 'PICT', or 'STR ' resource ('hmnu' only) */
  kHMTrackCntlItem              = 2048  /* Reserved */
};

enum {
                                        /* Constants for hmmHelpType's when filling out HMMessageRecord */
  khmmString                    = 1,    /* help message contains a PString */
  khmmPict                      = 2,    /* help message contains a resource ID to a 'PICT' resource */
  khmmStringRes                 = 3,    /* help message contains a res ID & index to a 'STR#' resource */
  khmmTEHandle                  = 4,    /* help message contains a Text Edit handle */
  khmmPictHandle                = 5,    /* help message contains a Picture handle */
  khmmTERes                     = 6,    /* help message contains a res ID to 'TEXT' & 'styl' resources */
  khmmSTRRes                    = 7,    /* help message contains a res ID to a 'STR ' resource */
  kHMEnabledItem                = 0     /* item is enabled, but not checked or control value = 0 */
};

enum {
                                        /* ResTypes for Styled TE Handles in Resources */
  kHMTETextResType              = 'TEXT', /* Resource Type of text data for styled TE record w/o style info */
  kHMTEStyleResType             = 'styl' /* Resource Type of style information for styled TE record */
};

enum {
  kHMDisabledItem               = 1,    /* item is disabled, grayed in menus or disabled in dialogs */
  kHMCheckedItem                = 2,    /* item is enabled, and checked or control value = 1 */
  kHMOtherItem                  = 3,    /* item is enabled, and control value > 1 */
                                        /* Method parameters to pass to HMShowBalloon */
  kHMRegularWindow              = 0,    /* Create a regular window floating above all windows */
  kHMSaveBitsNoWindow           = 1,    /* Just save the bits and draw (for MDEF calls) */
  kHMSaveBitsWindow             = 2     /* Regular window, save bits behind, AND generate update event */
};

enum {
                                        /* Resource Types for whichType parameter used when extracting 'hmnu' & 'hdlg' messages */
  kHMMenuResType                = 'hmnu', /* ResType of help resource for supporting menus */
  kHMDialogResType              = 'hdlg', /* ResType of help resource for supporting dialogs */
  kHMWindListResType            = 'hwin', /* ResType of help resource for supporting windows */
  kHMRectListResType            = 'hrct', /* ResType of help resource for rectangles in windows */
  kHMOverrideResType            = 'hovr', /* ResType of help resource for overriding system balloons */
  kHMFinderApplResType          = 'hfdr' /* ResType of help resource for custom balloon in Finder */
};

struct HMStringResType {
  short               hmmResID;
  short               hmmIndex;
};
typedef struct HMStringResType          HMStringResType;
struct HMMessageRecord {
  SInt16              hmmHelpType;
  union {
    Str255              hmmString;
    SInt16              hmmPict;
    TEHandle            hmmTEHandle;
    HMStringResType     hmmStringRes;
    SInt16              hmmPictRes;
    PicHandle           hmmPictHandle;
    SInt16              hmmTERes;
    SInt16              hmmSTRRes;
  }                       u;
};
typedef struct HMMessageRecord          HMMessageRecord;
typedef HMMessageRecord *               HMMessageRecPtr;
typedef CALLBACK_API( OSErr , TipFunctionProcPtr )(Point tip, RgnHandle structure, Rect *r, BalloonVariant *balloonVariant);
typedef STACK_UPP_TYPE(TipFunctionProcPtr)                      TipFunctionUPP;
/*
 *  NewTipFunctionUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  DisposeTipFunctionUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  InvokeTipFunctionUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*  Public Interfaces  */
/*
 *  HMGetHelpMenuHandle()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


#define HMGetHelpMenuRef HMGetHelpMenuHandle
/*
 *  HMShowBalloon()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  HMShowMenuBalloon()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  HMRemoveBalloon()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  HMGetIndHelpMsg()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  HMIsBalloon()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  HMGetBalloons()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  HMSetBalloons()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  HMSetFont()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  HMSetFontSize()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  HMGetFont()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  HMGetFontSize()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  HMSetDialogResID()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  HMSetMenuResID()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  HMBalloonRect()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  HMBalloonPict()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  HMScanTemplateItems()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  HMExtractHelpMsg()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  HMGetDialogResID()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  HMGetMenuResID()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  HMGetBalloonWindow()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */







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

#endif /* __BALLOONS__ */

